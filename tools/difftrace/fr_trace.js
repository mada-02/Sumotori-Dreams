// Skips the config dialog, starts the hidden part (1 AI sumo) at menu frame 20,
// then writes per physics step: sumo 0's 15 bodies (pos, rot, vel, angVel) and the sumo struct.
const m = Process.enumerateModules()[0];
const ORIG = {
  gameFrame: 0x40e1d2, startMatch: 0x410a7e, physicsStep: 0x40b5f7, configDialog: 0x416461, initDirect3D: 0x403c36,
  seed: 0x40b685, g_sumos: 0xc06b60, g_aiRandom: 0xc06988, g_gameState: 0xc06b50, g_frame: 0xc06978,
  g_playerCount: 0x4535f8, g_humanCount: 0x4eac80, g_currentLevel: 0x4eac70, g_windowed: 0x45733c,
};
const OURS = OURS_TABLE;
const T = OUT_IS_ORIG ? ORIG : OURS;
const A = {};
for (const k in T) A[k] = m.base.add(T[k] - 0x400000);

Interceptor.replace(A.configDialog, new NativeCallback(function (t) { return 1; }, 'int', ['pointer']));
Interceptor.attach(A.initDirect3D, { onEnter() { A.g_windowed.writeU8(1); } });
const seed = new NativeFunction(A.seed, 'void', ['pointer', 'int', 'int'], 'thiscall');
const startMatch = new NativeFunction(A.startMatch, 'void', []);

let started = false, steps = 0;
const FRAMES = N_FRAMES;
const out = new File(OUT_PATH, 'wb');
Interceptor.attach(A.physicsStep, {
  onLeave() {
    if (!started) {
      if (A.g_gameState.readS32() == 10 && A.g_frame.readS32() >= 20) {
        A.g_playerCount.writeS32(1);
        A.g_humanCount.writeS32(0);
        A.g_currentLevel.writeS32(0);
        seed(A.g_aiRandom, 1234, 5678);
        startMatch();
        started = true;
        send({started: true, state: A.g_gameState.readS32()});
      }
      return;
    }
    if (steps >= FRAMES) return;
    const s = A.g_sumos;
    out.write(s.readByteArray(0x730));
    for (let i = 0; i < 15; ++i) {
      const b = s.add(4 * i).readPointer();
      out.write(b.add(0x60).readByteArray(0x48));   // rot, pos, angVel, vel
    }
    if (++steps == FRAMES) { out.flush(); out.close(); send({done: steps}); }
  }
});
