import struct, sys
sys.path.insert(0, __import__('os').path.dirname(__file__))
REC = 0x730 + 15 * 0x48
a = open(sys.argv[1], 'rb').read(); b = open(sys.argv[2], 'rb').read()
lo, hi = int(sys.argv[3]), int(sys.argv[4])
src = open(__import__('os').path.join(__import__('os').path.dirname(__file__), 'cmptr.py')).read()
ns = {}
exec(src[src.index('names ='):src.index('first = None')], ns)
fname, skip, INTS = ns['fname'], ns['skip'], ns['INTS']
for f in range(lo, hi):
    ra = a[f * REC:(f + 1) * REC]; rb = b[f * REC:(f + 1) * REC]
    fa = struct.unpack('<%df' % (REC // 4), ra); fb = struct.unpack('<%df' % (REC // 4), rb)
    ia = struct.unpack('<%di' % (REC // 4), ra); ib = struct.unpack('<%di' % (REC // 4), rb)
    ints = [(fname(i), ia[i], ib[i]) for i in range(REC // 4) if i in INTS and ia[i] != ib[i]]
    d = sorted(((abs(fb[i] - fa[i]), i) for i in range(REC // 4) if i not in skip and i not in INTS and fa[i] == fa[i]), reverse=True)[:4]
    print(f, ' '.join('%s %.3g(%.5g/%.5g)' % (fname(i), x, fa[i], fb[i]) for x, i in d), ints)
