# sumo-recomp

A function-by-function C++ reconstruction of **Sumotori Dreams** (2007):
`sumofull.exe` (the game) and `sumoeditor.exe` (the level editor build).
The original was built with MSVC 7.1 for x86. Every reconstructed function
carries the address of its original as a `// @ 0x......` comment.
[`docs/FUNCTION_MAP.md`](docs/FUNCTION_MAP.md) lists all 391 functions of the
game code range (0x401000–0x41c550). The rest of the image is the
statically linked MSVC runtime.

## Layout

| Directory | Contents |
|---|---|
| `src/core` | shared definitions, `ArrayList`, `Vec3`/`Mat3`, x87 math helpers |
| `src/license` | big-integer licence key check |
| `src/physics` | rigid boxes, joints, contact solver, fracture |
| `src/game` | sumo characters and AI, camera, arenas/levels, menu, replays, game loop |
| `src/script` | compiler and evaluator for the arena description language (.smo mods) |
| `src/render` | Direct3D 9 renderer, water, procedural "ATG" texture generator |
| `src/audio` | DirectSound + ACM sound effects, MiniFMOD-style XM player and mixer |
| `src/platform` | WinMain, window procedure, input, configuration dialog |
| `src/generated` | assets extracted from the original executable (see below) |
| `reference` | Ghidra pseudocode and disassembly of the game code (used for the work) |
| `docs` | function map and decoding notes |
| `tools` | asset extractor, function-map generator, standalone texture generator test, Frida trace comparison against the original (`tools/difftrace`) |

## Building

Requirements: Visual Studio 2026 (toolset v145) with the Windows SDK. Only
**Win32 (x86)** is supported. The audio mixer is a transcription of the
original inline assembly, and the floating-point code needs the x87 FPU
(`/arch:IA32`) to give the original's results.

```
msbuild sumo-recomp.vcxproj -p:Configuration=Release -p:Platform=Win32
```

| Configuration | Output |
|---|---|
| `Release`, `Debug` | `bin\<config>\sumofull.exe` |
| `Release Editor`, `Debug Editor` | `bin\<config>\sumoeditor.exe` (`SUMO_EDITOR` defined) |

The two executables share the same source. The only difference in the
originals is the initial value of the editor-mode flag.

### Assets

The music (XM module), sound effects (GSM 6.10 WAVs) and texture programs are
embedded in the original executable's data section. They are pre-extracted
into `src/generated/*.inc`. To regenerate them from your own copy of the game:

```
python -I tools/extract_assets.py path\to\sumofull.exe
```

## Notes on accuracy

* The game never sets the FPU control word. Direct3D 9 switches the FPU to
  24-bit precision when the device is created, and everything after that
  (texture generation, physics) runs in that mode. The reconstruction keeps
  the original's operation order and the float/double width of every
  constant, so the x87 build reproduces the same rounding.
* `sin`, `cos`, `sqrt`, `tan` and `atan2` (texture generator) use the FPU
  instructions directly, like the original runtime did.
* `Vec3::lengthSq` and `normalize` return/keep `double`: the original leaves
  these results unrounded on the FPU stack.
* The original also has C++ dynamic initializers that the CRT runs before
  `WinMain` (table at 0x436004). One of them computes
  `g_penetrationScale = g_gravity * -0.05`. Without it, bodies are never
  pushed out of each other, and the wrestlers lean and fall.
* Like the original, the game caches its generated textures as
  `tex00000.tga`…`tex00022.tga` in the working directory and loads them from
  there on later starts.

### Checking the texture generator

`tools/texgen_dump.cpp` runs the texture generator outside the game, in the
same FPU mode, and writes the same `tex000NN.tga` files the game writes on
its first start (build instructions are in the file). Compare its output
with the files the original `sumofull.exe` writes when it is started for the
first time in an empty folder.
