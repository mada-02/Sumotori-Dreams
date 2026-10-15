import struct, sys
REC = 0x730 + 15 * 0x48
a = open(sys.argv[1], 'rb').read()
b = open(sys.argv[2], 'rb').read()
n = min(len(a), len(b)) // REC
names = {0x1d: 'upperLegLength', 0x1e: 'lowerLegLength', 0x1f: 'foot0', 0x22: 'foot1', 0x25: 'unk25', 0x26: 'unk26',
         0x27: 'stepLeg', 0x28: 'stepTimer', 0x29: 'stepState', 0x2a: 'stepLift', 0x2b: 'stepOrigin', 0x2e: 'bodyLift',
         0x2f: 'stepVector', 0x32: 'centerOfMass', 0x35: 'spineBend', 0x36: 'leanX', 0x37: 'leanXVel', 0x38: 'leanXBias',
         0x39: 'leanZ', 0x3a: 'leanZBias', 0x3b: 'weightShift', 0x3c: 'footHeight', 0x3d: 'unk3d', 0x40: 'pushImpulse',
         0x43: 'fallAngle', 0x44: 'fallTwist', 0x45: 'fallRate', 0x46: 'fallSide', 0x47: 'fallBlend', 0x48: 'turnRate',
         0x49: 'tilt', 0x4c: 'armAction', 0x4d: 'armTimer', 0x4e: 'armSide', 0x4f: 'armCooldown', 0x50: 'mode',
         0x51: 'modeTimer', 0x52: 'modeBlend', 0x53: 'motor', 0x109: 'restMotor', 0x1bf: 'controller', 0x1c0: 'opponent'}
def fname(i):
    if i >= 0x1cc:
        j = i - 0x1cc
        bi, k = divmod(j, 18)
        return 'body%d.%s[%d]' % (bi, (['rot'] * 9 + ['pos'] * 3 + ['angVel'] * 3 + ['vel'] * 3)[k], k % 3)
    best = max(k for k in names if k <= i)
    return '%s+%d' % (names[best], i - best)
skip = set(range(0, 0x1d)) | {0x1c0}
INTS = set([0x25, 0x26, 0x27, 0x28, 0x29, 0x3d, 0x3e, 0x3f, 0x46, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x1bf] + list(range(0x1c1, 0x1cc)))
first = None
for f in range(n):
    ra = a[f * REC:(f + 1) * REC]; rb = b[f * REC:(f + 1) * REC]
    if ra == rb:
        continue
    fa = struct.unpack('<%di' % (REC // 4), ra); fb = struct.unpack('<%di' % (REC // 4), rb)
    ffa = struct.unpack('<%df' % (REC // 4), ra); ffb = struct.unpack('<%df' % (REC // 4), rb)
    diffs = [i for i in range(REC // 4) if fa[i] != fb[i] and i not in skip]
    if not diffs:
        continue
    if first is None:
        first = f
        print('first differing step', f)
        for i in diffs[:60]:
            if i in INTS:
                print('  %-22s %d %d' % (fname(i), fa[i], fb[i]))
            else:
                print('  %-22s %.9g %.9g  d=%.3g' % (fname(i), ffa[i], ffb[i], ffb[i] - ffa[i]))
        print('  ... %d differing fields' % len(diffs))
    if f in (first + 1, first + 5, first + 20, 60, 120, 240, 480, 900, 1199) or f == n - 1:
        tor = 0x1cc + 9
        md = max(abs(ffb[i] - ffa[i]) for i in diffs if i not in INTS)
        print('step %4d: %3d fields differ, max |d| %.3g | torso pos A %s B %s | mode %d %d stepState %d %d' % (
            f, len(diffs), md, ['%.3f' % x for x in ffa[tor:tor + 3]], ['%.3f' % x for x in ffb[tor:tor + 3]],
            fa[0x50], fb[0x50], fa[0x29], fb[0x29]))
print('steps compared', n)
