# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A function-by-function C++ reconstruction of **Sumotori Dreams** (2010, MSVC 7.1, x86). It covers `sumofull.exe` (the game) and `sumoeditor.exe` (the level editor build). The goal is behaviour that matches the original one for one, not a modernised port. The original executables are outside the repo, in `..\sumofull\sumofull.exe` and `..\sumoeditor\sumoeditor.exe`.

## Build

Visual Studio 2026 (toolset v145) plus the Windows SDK. **Win32 only.**

```
"C:/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/MSBuild.exe" sumo-recomp.vcxproj "-p:Configuration=Release" -p:Platform=Win32 -m -nologo -v:minimal
```

| Configuration | Output |
|---|---|
| `Release`, `Debug` | `bin\<cfg>\sumofull.exe` |
| `Release Editor`, `Debug Editor` | `bin\<cfg>\sumoeditor.exe` (defines `SUMO_EDITOR`) |

- Every configuration also writes a linker `.map` file, which `tools/difftrace` uses.
- There is no test suite. Verification means comparing against the original executable:
  - texture generator: `tools/texgen_dump.cpp`; build instructions are in the file.
  - physics and game logic, step by step: `tools/difftrace/`; see its README.
- The known warning `config.cpp:224` (sprintf with too many arguments) is faithful to the original.

## Running

- `sumofull.exe` blocks on its settings dialog at startup.
- `sumoeditor.exe` skips the dialog and runs windowed, so it can be started unattended (for example, run it for a few seconds, then `taskkill //IM sumoeditor.exe //F`).
- On first start the game writes its generated textures to `tex00000.tga`…`tex00022.tga` in the working directory and loads them from there afterwards. Delete them to force regeneration. They are byte-identical to the original's output.

## Reconstruction conventions

- Every function has a `// @ 0x......` comment giving its original address. Globals carry their original addresses in the same way.
- `docs/FUNCTION_MAP.md` maps addresses to symbols for the game code range 0x401000–0x41c550 (391 functions; the rest of the image is the static MSVC CRT). Regenerate it with `python -I tools/gen_function_map.py` after adding or moving annotated code.
- `reference/` holds Ghidra pseudocode and `reference/disasm/sumofull_game.asm`. **Trust the disassembly over the pseudocode** for operation order and float/double widths.
- Struct layouts match the original 32-bit layouts exactly (offsets in comments, `static_assert`s in `sumo.h`). Tools and Frida scripts rely on this, so never reorder fields.
- Both executables share one source tree. The only difference between them is the initial value of `g_editorMode` (`SUMO_EDITOR_DEFAULT`).
- Assets (XM music, GSM sound effects, ATG texture programs) are pre-extracted into `src/generated/*.inc` by `tools/extract_assets.py <path to sumofull.exe>`.
- Fixed-size object pools mirror the original's static arrays (`world.h`: `MAX_BODIES`, `MAX_CONTACTS`, and so on). Do not replace them with heap containers.

## Floating point (most bugs come from here)

The original's results depend on x87 behaviour, so `/arch:IA32 /fp:precise` are required.

- **FPU control word.** Direct3D switches the FPU to 24-bit precision when the device is created; the texture generator runs in that mode. `gameFrame` calls `setFpuControl()` (0x77f: 64-bit precision) at the start and end of every frame, so physics and game logic run at extended precision.
- **Operation order matters.** Keep the original's grouping of additions and multiplications, and keep each constant's width as in the disassembly (`float` vs `double` literal). Narrowing warnings 4244/4305 are disabled on purpose.
- **Values the original never rounded.** Where the original leaves a result on the FPU stack without rounding, the reconstruction uses `double`. Examples: `Vec3::lengthSq` returns `double`, and `normalize` keeps its scale in `double`.
- **`core/fpmath.h` helpers.** `fp::sin/cos/sqrt/tan/fpatan` are inline-asm x87 wrappers that return through ST(0). They must stay `__declspec(noinline)` (`SUMO_X87_FN`). When MSVC inlined them, it read garbage and leaked the FPU stack, which blanked the screen in Release builds.
- **CRT dynamic initializers.** The original runs C++ dynamic initializers before `WinMain`; their table is at 0x436004..0x436028. The table is outside the game code range, so check it whenever a global looks "never written". Example: `g_penetrationScale = g_gravity * -0.05f`. Missing it made every wrestler lean and fall.

## Architecture overview

- **Main loop** (`platform/main.cpp`). A fixed 120 Hz tick: one `gameFrame()` per tick, and only the last frame of a catch-up burst is rendered. The simulation is deterministic given the inputs and the random seeds (`g_random` is seeded per match; `g_aiRandom` is seeded from `timeGetTime`).
- **`gameFrame`** (`game/game.cpp`) runs, in order: camera, `physicsStep()`, menu or Hidden Part logic, HUD text, `renderFrame()`.
- **`physicsStep`** (`physics/world.cpp`): `solve()`, then `Body::integrate` for each body, then `sumoUpdateAll()`.
- **`solve()`** works in phases:
  1. broad phase and `collide()`: convex clipping against each face plane of the other body; the clipped vertices become contacts;
  2. joint set-up;
  3. 40 sequential-impulse iterations over contacts and joints, with `sumoApplyMotors()` called once per iteration;
  4. the contact cache for warm starting, impact sounds and fracture;
  5. penetration pushes.
- **Sumo wrestlers** (`game/sumo.{h,cpp}`). Each is 15 boxes joined by 14 joints. `Sumo::update` (0x410b60, about 17 KB in the original) is the stepping and balance controller. It sets the targets of each joint's `JointMotor`, and the solver applies them through `applyMotors`.
- **Menu.** The 3D menu is itself a physics scene (`game/menu.cpp`): signs hang from rope joints, and hitting a sign selects it.
- **Levels** come from scripts compiled by `script/` (built-in arenas live in `game/level_scripts.inc`; `.smo` mod files are loaded from the command line).
- **Other modules:**
  - `render/`: the Direct3D 9 renderer, water, and the procedural ATG texture generator (`docs/TEXGEN_NOTES.md`).
  - `audio/`: DirectSound plus ACM sound effects, and a MiniFMOD-style XM player whose mixer is an inline-asm transcription.
  - `license/`: big-integer licence-key check.
  - `game/replay`: `in.dat`/`out.dat` replays.

## Debugging divergences from the original

Use `tools/difftrace` (Frida). It spawns both executables the same way: the config dialog is skipped, the Hidden Part starts on a fixed frame, and the AI seed is fixed. It records the sumo's state for every physics step, then the scripts compare the two recordings.

- Rounding-level differences (around 1e-7) that grow slowly are expected.
- A jump of several orders of magnitude within one step is a real bug. Bisect it inside that step by hooking `solve`, `sumoApplyMotors` (once per solver iteration) and `collide`.
- Our addresses come from `bin\<cfg>\*.map`. The original's addresses are the `@` comments; it loads at 0x400000.
- Hook a function only at an address taken from the map of the exact build being run. A wrong address corrupts the process silently.

## Shell notes (Windows)

- Git Bash mangles `/D`-style flags; pass compiler defines through the environment as `CL=-DFOO`.
- Use `vcvars32.bat` from a `.bat` file to get a `cl` environment.
- Many sources use CRLF line endings. Preserve them when editing with scripts.
