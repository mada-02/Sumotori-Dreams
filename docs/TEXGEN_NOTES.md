# ATG texture generator (0x419160–0x41c543) — decoding notes

Status: implemented in `src/render/texgen.cpp` (op dispatcher 0x419a50) and
`src/render/textures.cpp` (0x4158ca); `tools/texgen_dump.cpp` runs it standalone. All texgen runs under the
FPU control word Direct3D leaves (24-bit precision), so matching operation order is enough;
float/double spills are exact. `ftol` = truncation (0x41ec28 / 0x41d384), 0x41ec50 = floor,
0x41cf20 = log, 0x41ce90 = exp.

Globals: buffers[4] @0xd102ac..b8 (256x256 u32 each), tmp1 @0xd102c8, tmp2 @0xd102cc,
mulTable @0xd102c4 (0x10000 bytes), tgaBuf @0xd0fea8 (0x40000), header copy @0xd0fea4,
seed @0xd102c0, progress cb @0xd0fea0, done/total @0xd102d8/d4, cacheTga flag @0xd102d1,
mmxBilinear flag @0xd102d0, initialised @0xd102d2, cos table int[] @0xd0feac,
tga name "tex00000.tga" @0x453cf0 (digit [7] incremented, carry to [6]; load and save both increment).

* 0x419160 init: mulTable[r*256+x] = x*r/127 (r<128); rows 128..255: t=1-r'*0.007874015748031496,
  v=ftol(255-(255-x)*t). malloc tmp1,tmp2,buffers[0..3],tgaBuf(0x40000), header(0x10000).
* 0x4192a0 save TGA: 12 header bytes {0,0,2,0,...0}, w=256,h=256 (u16), 0x0018; rows bottom-up BGR.
* 0x419400 load TGA: skip 0x12, read 0x30000, rows bottom-up -> B|G<<8|R<<16; returns 0 if open fails.
* 0x419580 float bilinear: wrap u,v into [0,256); iu=ftol(floor u), fu=u-iu; c00,c10,c01,c11 with &0xff
  wrap; top=c00+(c10-c00)*fu, bottom=c01+(c11-c01)*fu, out=ftol(top+(bottom-top)*fv) per channel.
* 0x419840 MMX bilinear: transcribe asm verbatim (FISTP u*256, v*256; PMULLW/PSRLW; PACKUSWB).
* 0x419950 sample: flag d102d0 ? 419840 : 419580.
* 0x419980 generate(programs[], cb): init once, total=sum(prog[3]); per program 0x419a30 (malloc 0x40000 + 0x419a50); free all (0x4194f0).
* 0x419a50 run: if cacheTga && load ok -> done+=prog[3], cb(done/total), return. Else header copy,
  clear tmp1,tmp2,buffers; check 'ATG' (0x475441), count=hdr>>24, 9-byte instructions from +4:
  [op][dst][a2..a8] (bytes unsigned). ops: 1 perlin(ch=a2,seed=a4..a7) 0x41a740; 2 sine(ch=a8,fx=a2,fy=a3,ox=a4,oy=a5) 0x41aa30;
  3 cells(ch=a2,count=a3,size=a4,seed=a5..a8) 0x41a830; 4 gradient(mode=a2,ch=a3,p=a4) 0x41ab20;
  5 cubic(ch=a2,step=a3,seed=a4..a7) 0x41a420; 6 clear; 10 wave(a2..a7) 0x41ac40; 11 offset(a2,a3) 0x41aec0;
  12 twirl(a2) 0x41ad80; 14 emboss(a2) 0x41af40; 15 blur(n=a2) 0x41b870; 17 displace(srcU=a2,chU=a3,ampU=a4,srcV=a5,chV=a6,ampV=a7) 0x41aff0;
  18 radialSmear(src=a2,ch=a3,n=a4) 0x41ba40; 20 swapChannel(chA=a2,src=a3,chB=a4) 0x41b150; 21 grey(ch=a2) 0x41b270;
  23 copyChannel(chDst=a2,src=a3,chSrc=a4) 0x41b360; 24 blend(src=a2,w=a3) 0x41b420; 25 multiply(src=a2) 0x41b4c0;
  26 addSat(src=a2) 0x41bbf0; 27 max(src=a2) 0x41bc90; 30 normalScale(a2) 0x41b570; 31 xorBlue 0x41b540;
  32 curveBy(src=a2,ch=a3) 0x41b2c0; 33 curve(row=a2) 0x41b670; 34 cosRemap(ch=a2,f=a3) 0x41b6d0;
  35 levels(ch=a2,lo=a3,hi=a4) 0x41b770; 36 hsv(hue=a2,sat=a3) 0x41c0a0; 37 colorMap(ch=a2,r0,r1,g0,g1,b0,b1=a3..a8) 0x41c180;
  38 lerp(B=a2,M=a3,ch=a4) 0x41c2a0; 39 hDerivative 0x41c3d0; 40 bitmap(c1=a2..a4,c2=a5..a7,bits=+9, skip 0x2000) 0x41b820.
  After each: done++, cb(done/total). End: copy buffers[0] to output; if cacheTga save TGA.
  channel shift = (2-ch)*8, keep-mask = 0xffffff-(0xff<<shift) (alpha cleared).
* hash 0x41a100: x=(x<<13)^x; v=(x*x*15731+789221)*(seed+x)+1376312589 (u32 wrap); return (int)v/12359.
* cubic 0x41a150(p0,p1,p2,p3,x,n): t=x/n; a=p0-p1; P=(p3-p2)-a; t2=t*t; ((a-P)*t2 + t2*t*P) + (p2-p0)*t + p1.
* 0x41a1a0 cubic noise(buf,step,amp): grid hash(counter++)&0xff * (amp/256) row-major every step; horizontal pass on grid rows (x!=0),
  vertical pass all rows y!=0, in place, idx i0=x&(256-step), i1=(i0+step)&0xff, prev/next &0xff, frac=(step-1)&x.
* 0x41a420: cubic noise amp 255 -> clamp ftol 0..255 into channel.
* 0x41a530 cos noise(int buf,step,amp): scale=(float)(amp*1/256); grid ftol((hash&0xff)*scale)<<16;
  tbl[i]=ftol((1-cos(i*3.1415927410125732/step))*0.5*256); h pass on grid rows, v pass y!=0: a+((b-a)*tbl>>8).
* 0x41a740 perlin: cosnoise(tmp1,128,128.0); step=64,amp=64; loop {cosnoise(tmp2,step,amp); tmp1+=tmp2; amp*=0.5; step/=2} while step>0;
  channel = tmp1>>16 (unsigned).
* 0x41a830 cells: scale=(float)(size*0.0390625); disc[y][x]=ftol(min(sqrt((x-128)^2+(y-128)^2)*scale, 255 if >255));
  tmp1=255; count times: cx=hash(k)&0xff, cy=hash(k+1)&0xff (k+=2); stamp disc centred (cx,cy) wrap with min; channel=tmp1.
* 0x41aa30 sine: sy=sin((y+oy)*fy*K); v=ftol((sin((x+ox)*fx*K)+sy)*63+127), K=0.02454369328916073.
* 0x41ab20 gradient: scale = mode0:1.0, mode1: p/256+0.8, else bits of mode as float; v=ftol(255-2*sqrt(dx²+dy²)*scale) clamp;
  mode0 grey all, mode1 channel, else nothing.
* 0x41ac40 wave(fy=a2,fx=a3,ampY=a4,ampX=a5,offY=a6,offX=a7): tbl[x]=(float)(cos((x+a7)*a3*K)*a5); s=(float)(sin((y+a6)*a2*K)*a4);
  sample(dst, x+s, y+tbl[x]) -> tmp, copy back.
* 0x41ad80 twirl(a): k=(float)((a-127.5)/32); sign=k>0?-1:1; dy=y-127.5(float), r=(float)sqrt(dx²+dy²); ang=atan2(dx,dy)*40.74366429772945;
  t=128-r; w = t<0 ? 0 : cos(t*k*0.012271847f)*128+128; a=(ang + w*sign)*K; sample(dst, sin(a)*r+128, cos(a)*r+128).
* 0x41aec0 offset: tmp[y][x]=src[(y+dy)&0xff][(x+dx)&0xff].  0x41af40 emboss: other=src[(i+p*0x101)&0xffff], per-channel max(other-this,0).
* 0x41aff0 displace: u=((srcU>>shU)&0xff)*(ampU/256)+x, v=((srcV>>shV)&0xff)*(ampV/256)+y (floats), sample.
* 0x41b4c0 multiply: R=((int)b>>16)*((int)a>>16)>>8, G,B=(b*a)>>8. 0x41bbf0 addSat: R uses SAR, clamp>255 only. 0x41bc90 max per channel.
* 0x41b570: k=a*0.03125; c=ftol((ch-128)*k) clamp ±127 (>127 first), +128.  0x41b6d0: f=a*6.2831854820251465/256; v=ftol(127-cos(c*f)*127).
* 0x41b770: range=hi-lo (0->1); v=ftol(lo + c*(range/256)).  0x41b870 blur n times: (l+4c+r+u+d)>>3 per channel, wrap, via tmp1.
* 0x41ba40: a=((src>>sh)&0xff)*K; S=(float)sin a, C=(float)cos a; k=0,2,4..: ty=ftol(k*C+y), tx=ftol(k*S+x); sums of
  (int)p>>16, G, B from dst; out=ftol(sum/(float)n) packed; copy tmp->dst then blur(dst,2).
* 0x41bf10 rgb->hsv and 0x41bd30 hsv->rgb (case table 0..5: (v,t,p),(q,v,p),(p,v,t),(p,q,v),(t,p,v),(v,p,q); default (v,h/60,v)),
  clamp >255 only. 0x41c0a0: h+=(float)(a2*1.40625), s*=(float)((255-a3)/255).
* 0x41c180: tbl[i]=(ftol(i*(r1-r0)/256+r0)<<8|g)<<8|b; dst=tbl[(dst>>sh)&0xff].
* 0x41c2a0: w=255-((M>>sh)&0xff); out=ftol((b-a)*w/256+a) per channel into A.
* 0x41c3d0: sum_j sum_i k[i]*p(x-1+i, y-1+j), k={-1,0,1}, +128, clamp 0..255 (R uses p>>16).
* 0x4158ca loadTextures: gradient textures 0x4157bd (16 rows x64, k=exp(log(.01|.02|.05)/64), rows>8 swap) -> 0xc0f228,
  0x4156c8 (32px, k=exp(log(.02)/32) x3, minus 5.1) -> 0xd0f338 (both unused; loops keep values on the x87 stack);
  set d102d1=d102d0=1; generate(table @0x453890, nop cb 0x4158c7); signs 8..17 get menu text
  (5 groups x 6 lines x 24 chars @0x4538f0, Times New Roman 24pt, x10 y6+42n, w246 h32, color (i&1)*0x7f7f7f);
  even -> createNormalMap(p,256,256,-100), odd -> createTexture(p,256,256,0) into g_materialTextures;
  font: 0xffffffff fill, 256 glyphs Lucida Console 12 at (i&15)*16,(i/16)*16 16x16, invert, createTexture -> g_fontTexture.
