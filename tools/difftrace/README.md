# difftrace: step-by-step comparison against the original

The physics is deterministic, so the original `sumofull.exe` and the
reconstruction should produce the same state for every physics step when they
start the same way. These scripts record that state from both executables with
Frida and compare it.

`fr_trace.js` is a template that `mkfr.py` fills in. The generated script:

1. replaces the config dialog with "OK" and forces windowed mode;
2. starts the Hidden Part (one computer wrestler, default dojo) on menu frame 20
   from inside `physicsStep`, after seeding the AI random generator with a
   fixed value;
3. writes, after every physics step, the `Sumo` struct (0x730 bytes) and
   rot/pos/angVel/vel of its 15 bodies.

The struct layouts are the same in both executables, so the records compare
directly.

```
python -I mkfr.py ORIG  <dir>\orig.bin 1200 orig.js
python -I mkfr.py ..\..\bin\Release\sumofull.map <dir>\ours.bin 1200 ours.js
# run each with Frida (spawn the exe, load the script, ~20 s), then:
python -I cmptr.py orig.bin ours.bin            # first difference + summary
python -I cmpgrow.py orig.bin ours.bin 0 60     # largest differences per step
```

Our addresses come from the linker map (`GenerateMapFile` is on for all
configurations). Run each exe from a folder that holds the `tex000NN.tga` cache
so that start-up is fast.

Expected result: rounding-level differences (1e-7) that grow slowly as
the simulation amplifies them. A jump of several orders of magnitude within
one step points to a real bug. To find it, split the step further by hooking
`solve`, `sumoApplyMotors` (called once per solver iteration) or `collide`.
