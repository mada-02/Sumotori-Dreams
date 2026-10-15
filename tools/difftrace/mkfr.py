import re, sys, os
# usage: mkfr.py <map file or ORIG> <out trace path> <frames> <script out>
mapf, outp, frames, scr = sys.argv[1:5]
src = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'fr_trace.js')).read()
syms = {
    'gameFrame': '?gameFrame@@YAXD@Z', 'startMatch': '?startMatch@@YAXXZ', 'physicsStep': '?physicsStep@@YAXXZ',
    'configDialog': '?configDialog@@YAHPBD@Z', 'initDirect3D': '?initDirect3D@@YAXXZ', 'seed': '?seed@Random@@QAEXHH@Z',
    'g_sumos': '?g_sumos@@3PAUSumo@@A', 'g_aiRandom': '?g_aiRandom@@3URandom@@A', 'g_gameState': '?g_gameState@@3HA',
    'g_frame': '?g_frame@@3HA', 'g_playerCount': '?g_playerCount@@3HA', 'g_humanCount': '?g_humanCount@@3HA',
    'g_currentLevel': '?g_currentLevel@@3HA', 'g_windowed': '?g_windowed@@3DA',
}
table = '{}'
orig = mapf == 'ORIG'
if not orig:
    m = {}
    for line in open(mapf):
        p = line.split()
        if len(p) >= 3 and p[1] in syms.values():
            m[p[1]] = int(p[2], 16)
    table = '{' + ', '.join('%s: 0x%x' % (k, m[v]) for k, v in syms.items()) + '}'
src = src.replace('OURS_TABLE', table).replace('OUT_IS_ORIG', 'true' if orig else 'false')
src = src.replace('N_FRAMES', frames).replace('OUT_PATH', repr(outp.replace(chr(92), '/')))
open(scr, 'w').write(src)
print(table)
