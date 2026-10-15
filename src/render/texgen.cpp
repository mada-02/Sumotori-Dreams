// "ATG" procedural texture generator.
//
// A program is the 4 byte header 'A','T','G',count followed by count 9 byte
// instructions [op][dst][a2..a8] working on four 256x256 X8R8G8B8 buffers; the
// result is buffer 0.  Channel arguments select a byte of the pixel through
// shift (2 - ch) * 8, i.e. 0 = red, 1 = green, 2 = blue.
//
// Everything here runs with the FPU control word Direct3D leaves behind
// (24-bit precision), so the operation order and the float/double type of
// every constant follow the original exactly.
#include "texgen.h"

char g_texgenMmxSampler;                 // @ 0xd102d0
char g_texgenCacheTga;                   // @ 0xd102d1

static unsigned *s_buffers[4];           // @ 0xd102ac
static const unsigned char *s_instr;     // @ 0xd102bc (dst byte of the current instruction)
static unsigned s_seed;                  // @ 0xd102c0
static unsigned char *s_mulTable;        // @ 0xd102c4 [256][256]
static unsigned *s_tmp1;                 // @ 0xd102c8
static unsigned *s_tmp2;                 // @ 0xd102cc
static char s_initialised;               // @ 0xd102d2
static int s_total;                      // @ 0xd102d4
static int s_done;                       // @ 0xd102d8
static TexgenProgress s_progress;        // @ 0xd0fea0
static unsigned *s_header;               // @ 0xd0fea4
static unsigned char *s_tgaBuffer;       // @ 0xd0fea8
static int s_cosTable[256];              // @ 0xd0feac
static char s_tgaName[] = "tex00000.tga"; // @ 0x453cf0

static const double kAngle = 0.02454369328916073; // 2*pi/256

static inline unsigned channelShift(int ch) { return (unsigned)((2 - ch) * 8) & 31; }
static inline unsigned keepMask(unsigned shift) { return 0xffffffu - (0xffu << shift); }

// @ 0x419160
static void texgenInit()
{
    s_mulTable = (unsigned char *)malloc(0x10000);
    // Rows 0..127 scale by row/127, rows 128..255 brighten towards white.
    for (int r = 0; r < 128; ++r) {
        unsigned acc = 0;
        for (int x = 0; x < 256; ++x) {
            s_mulTable[r * 256 + x] = (unsigned char)(acc / 127);
            acc += r;
        }
    }
    int r = 0;
    for (int row = 0x8000; row < 0x10000; row += 0x100) {
        double t = 1.0 - (double)r * 0.007874015748031496;
        for (int x = 0; x < 256; ++x)
            s_mulTable[row + x] = (unsigned char)fp::ftol(255.0 - (255.0 - x) * t);
        ++r;
    }
    s_tmp1 = (unsigned *)malloc(0x40000);
    s_tmp2 = (unsigned *)malloc(0x40000);
    s_buffers[0] = (unsigned *)malloc(0x40000);
    s_buffers[1] = (unsigned *)malloc(0x40000);
    s_buffers[2] = (unsigned *)malloc(0x40000);
    s_buffers[3] = (unsigned *)malloc(0x40000);
    s_tgaBuffer = (unsigned char *)malloc(0x40000);
    s_header = (unsigned *)malloc(0x10000);
}

static void nextTgaName()
{
    if (++s_tgaName[7] == ':') {
        s_tgaName[7] = '0';
        ++s_tgaName[6];
    }
}

// @ 0x4192a0
static void saveTga(const unsigned *pixels)
{
    unsigned char header[12];
    memcpy(header, "\0\0\2\0\0\0\0\0\0\0\0\0", 12); // @ 0x453d00
    unsigned short size = 256;
    unsigned short bits = 0x18;
    DWORD written;
    HANDLE file = CreateFileA(s_tgaName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    WriteFile(file, header, 12, &written, nullptr);
    WriteFile(file, &size, 2, &written, nullptr);
    WriteFile(file, &size, 2, &written, nullptr);
    WriteFile(file, &bits, 2, &written, nullptr);
    int out = 0;
    const unsigned *row = pixels + 255 * 256;
    for (int y = 256; y != 0; --y) {
        const unsigned *p = row;
        for (int x = 256; x != 0; --x) {
            unsigned c = *p++;
            s_tgaBuffer[out] = (unsigned char)c;
            s_tgaBuffer[out + 1] = (unsigned char)(c >> 8);
            s_tgaBuffer[out + 2] = (unsigned char)(c >> 16);
            out += 3;
        }
        row -= 256;
    }
    WriteFile(file, s_tgaBuffer, 0x30000, &written, nullptr);
    CloseHandle(file);
    nextTgaName();
}

// @ 0x419400
static int loadTga(const char *name, unsigned *pixels)
{
    HANDLE file = CreateFileA(name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
        return 0;
    DWORD read;
    SetFilePointer(file, 0x12, nullptr, FILE_BEGIN);
    ReadFile(file, s_tgaBuffer, 0x30000, &read, nullptr);
    CloseHandle(file);
    int in = 0;
    unsigned *row = pixels + 255 * 256;
    for (int y = 256; y != 0; --y) {
        unsigned *p = row;
        for (int x = 256; x != 0; --x) {
            *p++ = s_tgaBuffer[in] | (s_tgaBuffer[in + 1] << 8) | (s_tgaBuffer[in + 2] << 16);
            in += 3;
        }
        row -= 256;
    }
    nextTgaName();
    return 1;
}

// @ 0x4194f0
// Frees the work buffers.  The pointers (and the "initialised" flag) are left
// as they are, and the multiply table is kept.
static void texgenFree()
{
    if (s_tmp2) free(s_tmp2);
    if (s_tmp1) free(s_tmp1);
    if (s_buffers[0]) free(s_buffers[0]);
    if (s_buffers[1]) free(s_buffers[1]);
    if (s_buffers[2]) free(s_buffers[2]);
    if (s_buffers[3]) free(s_buffers[3]);
    if (s_tgaBuffer) free(s_tgaBuffer);
    if (s_header) free(s_header);
}

// @ 0x419580
// Bilinear sample with float weights; coordinates wrap.
static unsigned sampleFloat(const unsigned *src, float u, float v)
{
    while (u < 0.0f)
        u += 256.0f;
    while (u >= 256.0)
        u -= 256.0f;
    while (v < 0.0f)
        v += 256.0f;
    while (v >= 256.0)
        v -= 256.0f;
    int iu = fp::ftol(fp::floor(u));
    int iv = fp::ftol(fp::floor(v));
    unsigned row0 = (unsigned)(iv & 0xff) << 8;
    unsigned row1 = (unsigned)((iv + 1) << 8) & 0xff00;
    unsigned col0 = iu & 0xff;
    unsigned col1 = (iu + 1) & 0xff;
    float fu = u - iu;
    unsigned c00 = src[col0 + row0];
    unsigned c10 = src[col1 + row0];
    unsigned c01 = src[col0 + row1];
    unsigned c11 = src[col1 + row1];
    float fv = v - iv;

    int r00 = (c00 >> 16) & 0xff, g00 = (c00 >> 8) & 0xff, b00 = c00 & 0xff;
    int r10 = (c10 >> 16) & 0xff, g10 = (c10 >> 8) & 0xff, b10 = c10 & 0xff;
    int r01 = (c01 >> 16) & 0xff, g01 = (c01 >> 8) & 0xff, b01 = c01 & 0xff;
    int r11 = (c11 >> 16) & 0xff, g11 = (c11 >> 8) & 0xff, b11 = c11 & 0xff;

    float topR = (float)(r10 - r00) * fu + r00;
    float topG = (float)(g10 - g00) * fu + g00;
    float topB = (float)(b10 - b00) * fu + b00;
    float g01f = (float)g01;
    float b01f = (float)b01;

    int r = fp::ftol((((float)(r11 - r01) * fu + r01) - topR) * fv + topR);
    int g = fp::ftol((((g11 - g01f) * fu + g01f) - topG) * fv + topG);
    int b = fp::ftol((((b11 - b01f) * fu + b01f) - topB) * fv + topB);
    return (unsigned)b | (((unsigned)r << 8 | (unsigned)g) << 8);
}

// @ 0x419840
// The MMX sampler: 8.8 fixed point coordinates (rounded with FISTP, no
// wrapping of the input), per-lane 16-bit PMULLW/PSRLW arithmetic.
static unsigned sampleMmx(const unsigned *src, float u, float v)
{
    int U = fp::fistp(u * 256.0f);
    int V = fp::fistp(v * 256.0f);
    unsigned fu = (unsigned)U & 0xff;
    unsigned fv = (unsigned)V & 0xff;
    unsigned row0 = (unsigned)V & 0xff00;
    unsigned col0 = ((unsigned)U & 0xff00) >> 8;
    unsigned col1 = (col0 + 1) & 0xff;
    unsigned row1 = (row0 + 0x100) & 0xff00;
    unsigned c00 = src[col0 + row0];
    unsigned c10 = src[col1 + row0];
    unsigned c11 = src[col1 + row1];
    unsigned c01 = src[col0 + row1];

    unsigned result = 0;
    for (int lane = 0; lane < 4; ++lane) {
        unsigned s = lane * 8;
        unsigned wu = lane < 3 ? fu : 0;      // the weights' alpha byte is zero
        unsigned wv = lane < 3 ? fv : 0;
        unsigned iu = 0xff - wu;
        unsigned iv = 0xff - wv;
        unsigned p00 = (c00 >> s) & 0xff, p10 = (c10 >> s) & 0xff;
        unsigned p01 = (c01 >> s) & 0xff, p11 = (c11 >> s) & 0xff;
        unsigned sum = ((((p11 * wu) & 0xffff) >> 8) * wv) & 0xffff;
        sum = (sum + (((((p01 * wv) & 0xffff) >> 8) * iu) & 0xffff)) & 0xffff;
        sum = (sum + (((((p10 * wu) & 0xffff) >> 8) * iv) & 0xffff)) & 0xffff;
        sum = (sum + (((((p00 * iu) & 0xffff) >> 8) * iv) & 0xffff)) & 0xffff;
        sum >>= 8; // PACKUSWB never saturates after this shift
        result |= sum << s;
    }
    return result;
}

// @ 0x419950
static unsigned sample(const unsigned *src, float u, float v)
{
    if (g_texgenMmxSampler)
        return sampleMmx(src, u, v);
    return sampleFloat(src, u, v);
}

// @ 0x41a0f0
static void clearBuffer(unsigned *buffer)
{
    for (int i = 0x10000; i != 0; --i)
        *buffer++ = 0;
}

static void copyFromTmp1(unsigned *dst)
{
    memcpy(dst, s_tmp1, 0x40000);
}

// @ 0x41a100
static int noiseHash(unsigned x)
{
    x = (x << 13) ^ x;
    unsigned v = (x * x * 15731 + 789221) * (s_seed + x) + 1376312589;
    return (int)v / 12359;
}

// @ 0x41a150
static float cubic(float p0, float p1, float p2, float p3, float x, float n)
{
    float t = x / n;
    float a = p0 - p1;
    float p = (p3 - p2) - a;
    float t2 = t * t;
    return ((a - p) * t2 + t2 * t * p) + (p2 - p0) * t + p1;
}

// @ 0x41a1a0
// Value noise on a step x step lattice with cubic interpolation.
static void cubicNoise(float *buffer, int step, float amplitude)
{
    float scale = (float)(amplitude * 0.00390625);
    int counter = 0;
    memset(buffer, 0, 0x40000);
    for (int y = 0; y < 256; y += step)
        for (int x = 0; x < 256; x += step)
            buffer[y * 256 + x] = (float)(noiseHash(counter++) & 0xff) * scale;

    for (int row = 0; row < 0x10000; row += step * 256) {
        for (unsigned x = 0; (int)x < 256; ++x) {
            if (x == 0)
                continue;
            unsigned i0 = (256u - step) & x;
            unsigned i1 = (i0 + step) & 0xff;
            buffer[row + x] = cubic(buffer[row + ((i0 - step) & 0xff)], buffer[row + i0],
                                    buffer[row + i1], buffer[row + ((i1 + step) & 0xff)],
                                    (float)(int)((step - 1u) & x), (float)step);
        }
    }
    for (unsigned y = 0; (int)y < 256; ++y) {
        if (y == 0)
            continue;
        unsigned i0 = (256u - step) & y;
        unsigned i1 = (i0 + step) & 0xff;
        const float *pm = buffer + ((i0 - step) & 0xff) * 256;
        const float *p0 = buffer + i0 * 256;
        const float *p1 = buffer + i1 * 256;
        const float *pp = buffer + ((i1 + step) & 0xff) * 256;
        float *out = buffer + y * 256;
        float frac = (float)(int)((step - 1u) & y);
        for (int x = 0; x < 256; ++x)
            out[x] = cubic(pm[x], p0[x], p1[x], pp[x], frac, (float)step);
    }
}

// @ 0x41a420  (op 5)
static void opCubicNoise(int dst, int ch, int step, int s0, int s1, int s2, int s3)
{
    if (step == 0)
        return;
    s_seed = ((((unsigned)s0 << 8 | s1) << 8 | s2) << 8) | s3;
    float *noise = (float *)malloc(0x40000);
    cubicNoise(noise, step, 255.0f);
    unsigned shift = channelShift(ch);
    unsigned keep = keepMask(shift);
    unsigned *p = s_buffers[dst];
    for (int i = 0; i < 0x10000; ++i) {
        unsigned old = p[i];
        int v = fp::ftol(noise[i]);
        if (v > 255)
            v = 255;
        else if (v < 0)
            v = 0;
        p[i] = (unsigned)v << shift | (old & keep);
    }
    free(noise);
}

// @ 0x41a500
static void addBuffers(int *dst, const int *src)
{
    for (int i = 0; i < 0x10000; ++i)
        dst[i] += src[i];
}

// @ 0x41a530
// Value noise in 16.16 fixed point with cosine interpolation.
static void cosNoise(int *buffer, int step, float amplitude)
{
    float scale = (float)(amplitude * 0.00390625);
    int counter = 0;
    memset(buffer, 0, 0x40000);
    for (int y = 0; y < 256; y += step)
        for (int x = 0; x < 256; x += step)
            buffer[y * 256 + x] = fp::ftol((float)(noiseHash(counter++) & 0xff) * scale) << 16;

    for (int i = 0; i < step; ++i)
        s_cosTable[i] = fp::ftol((1.0 - fp::cos(i * 3.1415927410125732 / step)) * 0.5 * 256.0);

    unsigned mask = 256u - step;
    for (int row = 0; row < 0x10000; row += step * 256) {
        for (unsigned x = 0; (int)x < 256; ++x) {
            unsigned i0 = mask & x;
            int a = buffer[row + i0];
            int b = buffer[row + ((i0 + step) & 0xff)];
            buffer[row + x] = ((b - a) * s_cosTable[(step - 1u) & x] >> 8) + a;
        }
    }
    for (unsigned y = 0; (int)y < 256; ++y) {
        if (y == 0)
            continue;
        unsigned i0 = mask & y;
        const int *pa = buffer + i0 * 256;
        const int *pb = buffer + ((i0 + step) & 0xff) * 256;
        int *out = buffer + y * 256;
        int w = s_cosTable[(step - 1u) & y];
        for (int x = 0; x < 256; ++x)
            out[x] = ((pb[x] - pa[x]) * w >> 8) + pa[x];
    }
}

// @ 0x41a740  (op 1)
// Fractal sum of cosine noise octaves (step 128 amplitude 128 down to step 1).
static void opPerlin(int dst, int ch, int s0, int s1, int s2, int s3)
{
    unsigned *p = s_buffers[dst];
    s_seed = ((((unsigned)s0 << 8 | s1) << 8 | s2) << 8) | s3;
    unsigned shift = channelShift(ch);
    cosNoise((int *)s_tmp1, 128, 128.0f);
    int step = 64;
    float amplitude = 64.0f;
    do {
        cosNoise((int *)s_tmp2, step, amplitude);
        addBuffers((int *)s_tmp1, (const int *)s_tmp2);
        amplitude = (float)(amplitude * 0.5);
        step /= 2;
    } while (step > 0);
    unsigned keep = keepMask(shift);
    for (int i = 0; i < 0x10000; ++i)
        p[i] = (s_tmp1[i] >> 16) << shift | (p[i] & keep);
}

// @ 0x41a830  (op 3)
// Distance field of "count" random points (cones of slope size/25.6).
static void opCells(int dst, int ch, int count, int size, int s0, int s1, int s2, int s3)
{
    float scale = (float)(size * 0.0390625);
    unsigned *disc = (unsigned *)malloc(0x40000);
    unsigned *d = disc;
    for (int y = 0; y < 256; ++y) {
        double dy = y - 128.0;
        double dy2 = dy * dy;
        for (int x = 0; x < 256; ++x) {
            double dx = x - 128.0;
            double dist = fp::sqrt(dx * dx + dy2) * scale;
            if (dist > 255.0f)
                dist = 255.0f;
            *d++ = (unsigned)fp::ftol(dist);
        }
    }
    s_seed = ((((unsigned)s0 << 8 | s1) << 8 | s2) << 8) | s3;
    for (int i = 0; i < 0x10000; ++i)
        s_tmp1[i] = 0xff;

    int k = 0;
    for (int n = 0; n < count; ++n) {
        unsigned cx = noiseHash(k);
        unsigned cy = noiseHash(k + 1);
        k += 2;
        int discIndex = 0;
        int rowEnd = (int)(cy & 0xff) + 0x80;
        int colStart = (int)(cx & 0xff) - 0x80;
        int colEnd = (int)(cx & 0xff) + 0x80;
        for (int row = (int)(cy & 0xff) - 0x80; row < rowEnd; ++row) {
            for (int col = colStart; col < colEnd; ++col) {
                unsigned v = disc[discIndex++];
                unsigned *t = &s_tmp1[(col & 0xff) + (row & 0xff) * 256];
                if (v < *t)
                    *t = v;
            }
        }
    }

    unsigned shift = channelShift(ch);
    unsigned *p = s_buffers[dst];
    for (int i = 0; i < 0x10000; ++i) {
        p[i] &= keepMask(shift);
        p[i] |= s_tmp1[i] << shift;
    }
    free(disc);
}

// @ 0x41aa30  (op 2)
static void opSine(int dst, int ch, int fx, int fy, int ox, int oy)
{
    unsigned *p = s_buffers[dst];
    unsigned shift = channelShift(ch);
    int i = 0;
    for (int y = 0; y < 256; ++y) {
        double sy = fp::sin((double)(y + oy) * fy * kAngle);
        for (int x = 0; x < 256; ++x)
            s_tmp1[i++] = (unsigned)fp::ftol((fp::sin((double)(x + ox) * fx * kAngle) + sy) * 63.0 + 127.0) << shift;
    }
    unsigned keep = keepMask(shift);
    for (int j = 0; j < 0x10000; ++j) {
        p[j] &= keep;
        p[j] = s_tmp1[j] | p[j];
    }
}

// @ 0x41ab20  (op 4)
// Radial gradient.  Mode 0 writes grey, mode 1 one channel, any other mode
// writes nothing (its scale is the mode's bit pattern read as a float).
static void opGradient(int dst, int mode, int ch, int param)
{
    unsigned *p = s_buffers[dst];
    double scale;
    if (mode == 0) {
        scale = 1.0f;
    } else if (mode == 1) {
        scale = param * 0.00390625 + 0.8;
    } else {
        float bits;
        memcpy(&bits, &mode, sizeof(bits));
        scale = bits;
    }
    unsigned shift = channelShift(ch);
    unsigned keep = keepMask(shift);
    for (int y = 0; y < 256; ++y) {
        double dy = y - 0x80;
        double dy2 = dy * dy;
        for (int x = 0; x < 256; ++x) {
            double dx = x - 0x80;
            double s = fp::sqrt(dx * dx + dy2) * scale;
            int v = fp::ftol(255.0 - (s + s));
            if (v < 0)
                v = 0;
            else if (v > 255)
                v = 255;
            if (mode == 0)
                *p = ((unsigned)v << 8 | v) << 8 | v;
            else if (mode == 1)
                *p = (*p & keep) | (unsigned)v << shift;
            ++p;
        }
    }
}

// @ 0x41ac40  (op 10)
static void opWave(int dst, int fy, int fx, int ampY, int ampX, int offY, int offX)
{
    unsigned *p = s_buffers[dst];
    float table[256];
    float ampYf = (float)ampY;
    float fyf = (float)fy;
    float offYf = (float)offY;
    for (int x = 0; x < 256; ++x)
        table[x] = (float)(fp::cos((double)(x + offX) * fx * kAngle) * ampX);

    int index = 0;
    float yf = 0.0f;
    for (int y = 0; y < 256; ++y) {
        float s = (float)(fp::sin((y + offYf) * fyf * kAngle) * ampYf);
        float xf = 0.0f;
        for (int x = 0; x < 256; ++x) {
            s_tmp1[index++] = sample(p, xf + s, yf + table[x]);
            xf = xf + 1.0f;
        }
        yf = yf + 1.0f;
    }
    copyFromTmp1(p);
}

// @ 0x41ad80  (op 12)
static void opTwirl(int dst, int amount)
{
    unsigned *p = s_buffers[dst];
    float k = (float)((amount - 127.5) * 0.03125);
    float sign = -1.0f;
    if (k <= 0.0f)
        sign = 1.0f;
    int index = 0;
    for (int y = 0; y < 256; ++y) {
        float dy = (float)(y - 127.5);
        float dy2 = dy * dy;
        for (int x = 0; x < 256; ++x) {
            double dx = x - 127.5;
            float r = (float)fp::sqrt(dx * dx + dy2);
            double angle = fp::fpatan(dx, dy) * 40.74366429772945;
            double t = 128.0f - r;
            double w;
            if (t < 0.0f)
                w = 0.0f;
            else
                w = fp::cos(t * k * 0.012271847f) * 128.0 + 128.0;
            double a = (angle + w * sign) * kAngle;
            float v = (float)(fp::cos(a) * r + 128.0);
            float u = (float)(fp::sin(a) * r + 128.0);
            s_tmp1[index++] = sample(p, u, v);
        }
    }
    copyFromTmp1(p);
}

// @ 0x41aec0  (op 11)
static void opOffset(int dst, int dx, int dy)
{
    unsigned *p = s_buffers[dst];
    for (int y = 0; y < 256; ++y)
        for (int x = 0; x < 256; ++x)
            s_tmp1[y * 256 + x] = p[((x + dx) & 0xff) + ((dy + y) & 0xffu) * 256];
    copyFromTmp1(p);
}

// @ 0x41af40  (op 14)
static void opEmboss(int dst, int offset)
{
    unsigned *p = s_buffers[dst];
    for (int i = 0; i < 0x10000; ++i) {
        unsigned other = p[(offset * 0x101 + i) & 0xffff];
        unsigned self = p[i];
        int r = (int)((other >> 16) & 0xff) - (int)((self >> 16) & 0xff);
        int g = (int)((other >> 8) & 0xff) - (int)((self >> 8) & 0xff);
        int b = (int)(other & 0xff) - (int)(self & 0xff);
        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        s_tmp1[i] = ((unsigned)r << 8 | g) << 8 | b;
    }
    copyFromTmp1(p);
}

// @ 0x41aff0  (op 17)
static void opDisplace(int dst, int srcU, int chU, int ampU, int srcV, int chV, int ampV)
{
    unsigned *p = s_buffers[dst];
    const unsigned *bu = s_buffers[srcU];
    const unsigned *bv = s_buffers[srcV];
    float scaleU = (float)(ampU * 0.00390625);
    float scaleV = (float)(ampV * 0.00390625);
    unsigned shiftU = channelShift(chU);
    unsigned shiftV = channelShift(chV);
    int index = 0;
    for (int y = 0; y < 256; ++y) {
        float yf = (float)y;
        for (int x = 0; x < 256; ++x) {
            float u = (float)((bu[index] >> shiftU) & 0xff) * scaleU + x;
            float v = (float)((bv[index] >> shiftV) & 0xff) * scaleV + yf;
            s_tmp1[index] = sample(p, u, v);
            ++index;
        }
    }
    copyFromTmp1(p);
}

// @ 0x41b150  (op 20)
static void opSwapChannel(int dst, int chA, int src, int chB)
{
    unsigned *a = s_buffers[dst];
    unsigned shiftA = channelShift(chA);
    unsigned shiftB = channelShift(chB);
    for (int i = 0; i < 0x10000; ++i)
        s_tmp1[i] = ((s_buffers[src][i] >> shiftB) & 0xff) << shiftA;
    for (int i = 0; i < 0x10000; ++i)
        s_tmp2[i] = ((a[i] >> shiftA) & 0xff) << shiftB;
    for (int i = 0; i < 0x10000; ++i) {
        a[i] &= keepMask(shiftA);
        a[i] = s_tmp1[i] | a[i];
    }
    for (int i = 0; i < 0x10000; ++i) {
        s_buffers[src][i] &= keepMask(shiftB);
        s_buffers[src][i] |= s_tmp2[i];
    }
}

// @ 0x41b270  (op 21)
static void opGrey(int dst, int ch)
{
    unsigned *p = s_buffers[dst];
    unsigned shift = channelShift(ch);
    for (int i = 0; i < 0x10000; ++i) {
        unsigned c = (p[i] >> shift) & 0xff;
        p[i] = (c << 8 | c) << 8 | c;
    }
}

static inline unsigned mapBytes(unsigned c, const unsigned char *row)
{
    return (unsigned)row[c & 0xff] | (unsigned)row[(c >> 8) & 0xff] << 8 | (unsigned)row[(c >> 16) & 0xff] << 16;
}

// @ 0x41b2c0  (op 32)
// Scales each pixel by the multiply-table row picked by a channel of src.
static void opCurveBy(int dst, int src, int ch)
{
    unsigned *p = s_buffers[dst];
    const unsigned *s = s_buffers[src];
    unsigned shift = channelShift(ch);
    for (int i = 0; i < 0x10000; ++i)
        p[i] = mapBytes(p[i], s_mulTable + ((s[i] >> shift) & 0xff) * 0x100);
}

// @ 0x41b360  (op 23)
static void opCopyChannel(int dst, int chDst, unsigned src, int chSrc)
{
    unsigned *p = s_buffers[dst];
    unsigned shift = channelShift(chDst);
    unsigned shiftSrc = channelShift(chSrc);
    for (int i = 0; i < 0x10000; ++i)
        s_tmp1[i] = ((s_buffers[src & 0xff][i] >> shiftSrc) & 0xff) << shift;
    for (int i = 0; i < 0x10000; ++i) {
        p[i] &= keepMask(shift);
        p[i] = s_tmp1[i] | p[i];
    }
}

// @ 0x41b420  (op 24)
// Byte-wise cross fade through the multiply table; alpha is left alone.
static void opBlend(int dst, int src, unsigned weight)
{
    unsigned char *d = (unsigned char *)s_buffers[dst];
    const unsigned char *s = (const unsigned char *)s_buffers[src];
    const unsigned char *rowDst = s_mulTable + (weight & ~1u) * 0x80;
    const unsigned char *rowSrc = s_mulTable + (0x7f00 - (weight & ~1u) * 0x80);
    for (int i = 0x10000; i != 0; --i) {
        d[0] = (unsigned char)(rowSrc[s[0]] + rowDst[d[0]]);
        d[1] = (unsigned char)(rowSrc[s[1]] + rowDst[d[1]]);
        d[2] = (unsigned char)(rowSrc[s[2]] + rowDst[d[2]]);
        d += 4;
        s += 4;
    }
}

// @ 0x41b4c0  (op 25)
static void opMultiply(int dst, int src)
{
    unsigned *p = s_buffers[dst];
    const unsigned *s = s_buffers[src];
    for (int i = 0; i < 0x10000; ++i) {
        unsigned a = p[i];
        unsigned b = s[i];
        int r = ((int)b >> 16) * ((int)a >> 16) >> 8;
        int g = (int)(((b >> 8) & 0xff) * ((a >> 8) & 0xff)) >> 8;
        int bl = (int)((b & 0xff) * (a & 0xff)) >> 8;
        p[i] = ((unsigned)g | (unsigned)r << 8) << 8 | (unsigned)bl;
    }
}

// @ 0x41b540  (op 31)
static void opInvertBlue(int dst)
{
    unsigned char *p = (unsigned char *)s_buffers[dst];
    for (int i = 0x10000; i != 0; --i) {
        *p ^= 0xff;
        p += 4;
    }
}

// @ 0x41b570  (op 30)
// Scales the signed (c - 128) components of a normal-style image.
static void opNormalScale(int dst, int amount)
{
    unsigned *p = s_buffers[dst];
    double k = amount * 0.03125;
    for (int i = 0; i < 0x10000; ++i) {
        unsigned c = p[i];
        int r = fp::ftol((int)(((c >> 16) & 0xff) - 0x80) * k);
        int g = fp::ftol((int)(((c >> 8) & 0xff) - 0x80) * k);
        int b = fp::ftol((int)((c & 0xff) - 0x80) * k);
        if (r > 127) r = 127;
        if (g > 127) g = 127;
        if (b > 127) b = 127;
        if (r < -127) r = -127;
        if (g < -127) g = -127;
        if (b < -127) b = -127;
        p[i] = (unsigned)(g + 0x80) * 0x100 | (unsigned)(r + 0x80) * 0x10000 | (unsigned)(b + 0x80);
    }
}

// @ 0x41b670  (op 33)
static void opCurve(int dst, int row)
{
    unsigned *p = s_buffers[dst];
    const unsigned char *table = s_mulTable + row * 0x100;
    for (int i = 0; i < 0x10000; ++i)
        p[i] = mapBytes(p[i], table);
}

// @ 0x41b6d0  (op 34)
static void opCosRemap(int dst, int ch, int frequency)
{
    unsigned shift = channelShift(ch);
    unsigned *p = s_buffers[dst];
    double f = frequency * 6.2831854820251465 * 0.00390625;
    unsigned keep = keepMask(shift);
    for (int i = 0; i < 0x10000; ++i) {
        unsigned c = p[i];
        int v = fp::ftol(127.0 - fp::cos(((c >> shift) & 0xff) * f) * 127.0);
        p[i] = (c & keep) | (unsigned)v << shift;
    }
}

// @ 0x41b770  (op 35)
static void opLevels(int dst, int ch, int lo, int hi)
{
    unsigned shift = channelShift(ch);
    unsigned *p = s_buffers[dst];
    int range = hi - lo;
    if (range == 0)
        range = 1;
    double scale = range * 0.00390625;
    unsigned keep = keepMask(shift);
    for (int i = 0; i < 0x10000; ++i) {
        unsigned c = p[i];
        int v = fp::ftol(lo + ((c >> shift) & 0xff) * scale);
        p[i] = (unsigned)v << shift | (c & keep);
    }
}

// @ 0x41b820  (op 40)
// 1 bit per pixel image (0x2000 bytes following the instruction, LSB first).
static void opBitmap(int dst, const unsigned char *bits, unsigned color0, unsigned color1)
{
    unsigned *p = s_buffers[dst];
    for (int i = 0; i < 0x2000; ++i) {
        unsigned char b = bits[i];
        for (int k = 8; k != 0; --k) {
            *p++ = (b & 1) ? color1 : color0;
            b >>= 1;
        }
    }
}

// @ 0x41b870  (op 15)
// (left + right + up + down + 4 * centre) / 8, wrapping, n passes.
static void opBlur(int dst, int passes)
{
    unsigned *p = s_buffers[dst];
    for (int n = passes; n > 0; --n) {
        int out = 0;
        for (int y = 0; y < 256; ++y) {
            const unsigned *up = p + ((y - 1) & 0xff) * 256;
            const unsigned *down = p + ((y + 1) & 0xff) * 256;
            const unsigned *row = p + y * 256;
            for (int x = 0; x < 256; ++x) {
                unsigned u = up[x], d = down[x], c = row[x];
                unsigned l = row[(x - 1) & 0xff];
                unsigned r = row[(x + 1) & 0xff];
                int rr = (int)(((r >> 16) & 0xff) + ((c >> 16) & 0xff) * 4 + ((u >> 16) & 0xff) + ((l >> 16) & 0xff) + ((d >> 16) & 0xff)) >> 3;
                int gg = (int)(((r >> 8) & 0xff) + ((c >> 8) & 0xff) * 4 + ((u >> 8) & 0xff) + ((l >> 8) & 0xff) + ((d >> 8) & 0xff)) >> 3;
                int bb = (int)((r & 0xff) + (c & 0xff) * 4 + (u & 0xff) + (l & 0xff) + (d & 0xff)) >> 3;
                s_tmp1[out++] = ((unsigned)rr << 8 | gg) << 8 | bb;
            }
        }
        copyFromTmp1(p);
    }
}

// @ 0x41ba40  (op 18)
// Averages "count" samples of dst along the direction given by a channel of
// src (radius 0, 2, 4, ...), then blurs twice.
static void opSmear(int dst, int src, int ch, int count)
{
    const unsigned *s = s_buffers[src];
    unsigned *p = s_buffers[dst];
    unsigned shift = channelShift(ch);
    int index = 0;
    for (int y = 0; y < 256; ++y) {
        for (int x = 0; x < 256; ++x) {
            double sumR = 0.0f, sumG = 0.0f, sumB = 0.0f;
            double a = ((s[index] >> shift) & 0xff) * kAngle;
            float sn = (float)fp::sin(a);
            float cs = (float)fp::cos(a);
            int radius = 0;
            for (int n = count; n > 0; --n) {
                double rf = radius;
                int ty = fp::ftol(rf * cs + y);
                int tx = fp::ftol(rf * sn + x);
                unsigned c = p[(tx & 0xff) + ((ty & 0xff) << 8)];
                sumR += (int)c >> 16;
                sumG += ((int)c >> 8) & 0xff;
                sumB += c & 0xff;
                radius += 2;
            }
            float n = (float)count;
            int r = fp::ftol(sumR / n);
            int g = fp::ftol(sumG / n);
            int b = fp::ftol(sumB / n);
            s_tmp1[index] = ((unsigned)r << 8 | (unsigned)g) << 8 | (unsigned)b;
            ++index;
        }
    }
    copyFromTmp1(p);
    opBlur(dst, 2);
}

// @ 0x41bbf0  (op 26)
static void opAddSaturate(int dst, int src)
{
    unsigned *p = s_buffers[dst];
    const unsigned *s = s_buffers[src];
    for (int i = 0; i < 0x10000; ++i) {
        unsigned a = p[i];
        unsigned b = s[i];
        int r = ((int)b >> 16) + ((int)a >> 16);
        unsigned g = ((b >> 8) & 0xff) + ((a >> 8) & 0xff);
        unsigned bl = (b & 0xff) + (a & 0xff);
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (bl > 255) bl = 255;
        p[i] = ((unsigned)r << 8 | g) << 8 | bl;
    }
}

// @ 0x41bc90  (op 27)
static void opMax(int dst, int src)
{
    unsigned *p = s_buffers[dst];
    const unsigned *s = s_buffers[src];
    for (int i = 0; i < 0x10000; ++i) {
        unsigned a = p[i];
        unsigned b = s[i];
        unsigned r = sumoMax((b >> 16) & 0xff, (a >> 16) & 0xff);
        unsigned g = sumoMax((b >> 8) & 0xff, (a >> 8) & 0xff);
        unsigned bl = sumoMax(b & 0xff, a & 0xff);
        p[i] = (r << 8 | g) << 8 | bl;
    }
}

// @ 0x41bd30
static unsigned hsvToRgb(float h, float s, float v)
{
    float r, g, b;
    if (s == 0.0) {
        r = g = b = v;
    } else {
        while (h >= 360.0)
            h = (float)(h - 360.0);
        while (h < 0.0)
            h = (float)(h + 360.0);
        float hs = (float)(h * 0.016666666666666666);
        double sector = fp::floor(hs);
        double f = hs - sector;
        float pv = (float)((1.0 - s) * v);
        float qv = (float)((1.0 - f * s) * v);
        float tv = (float)((1.0 - (1.0 - f) * s) * v);
        switch (fp::ftol(sector)) {
        case 0: r = v; g = tv; b = pv; break;
        case 1: r = qv; g = v; b = pv; break;
        case 2: r = pv; g = v; b = tv; break;
        case 3: r = pv; g = qv; b = v; break;
        case 4: r = tv; g = pv; b = v; break;
        case 5: r = v; g = pv; b = qv; break;
        default: r = v; g = hs; b = v; break;
        }
    }
    int ri = fp::ftol(r);
    int gi = fp::ftol(g);
    int bi = fp::ftol(b);
    if (ri > 255) ri = 255;
    if (gi > 255) gi = 255;
    if (bi > 255) bi = 255;
    return ((unsigned)ri << 8 | (unsigned)gi) << 8 | (unsigned)bi;
}

// @ 0x41bf10
// Hue in degrees (-1 for grey); leaves *h untouched if no component equals
// the maximum (cannot happen for finite input).
static void rgbToHsv(float r, float g, float b, float *h, float *s, float *v)
{
    float mx = r > g ? r : g;
    if (b > mx)
        mx = b;
    float mn = r < g ? r : g;
    if (b < mn)
        mn = b;
    *v = mx;
    *s = 0.0f;
    if (mx != 0.0)
        *s = (mx - mn) / mx;
    if (*s == 0.0) {
        *h = -1.0f;
        return;
    }
    float delta = mx - mn;
    float dr = mx - r;
    float dg = mx - g;
    float db = mx - b;
    if (r == mx)
        *h = (db - dg) / delta;
    else if (g == mx)
        *h = (float)((dr - db) / delta + 2.0);
    else if (b == mx)
        *h = (float)((dg - dr) / delta + 4.0);
    *h = (float)(*h * 60.0);
    while (*h < 0.0)
        *h = (float)(*h + 360.0);
    while (*h >= 360.0)
        *h = (float)(*h - 360.0);
}

// @ 0x41c0a0  (op 36)
static void opHueSaturation(int dst, int hue, unsigned saturation)
{
    float hueAdd = (float)(hue * 1.40625);
    unsigned *p = s_buffers[dst];
    float satScale = (float)((int)(0xff - saturation) * 0.00392156862745098);
    float h = 0.0f, s, v;
    for (int i = 0x10000; i != 0; --i) {
        unsigned c = *p;
        rgbToHsv((float)((c >> 16) & 0xff), (float)((c >> 8) & 0xff), (float)(c & 0xff), &h, &s, &v);
        h = h + hueAdd;
        s = s * satScale;
        *p++ = hsvToRgb(h, s, v);
    }
}

// @ 0x41c180  (op 37)
// Maps a channel through a linear ramp between two colours.
static void opColorMap(int dst, int ch, int r0, int r1, int g0, int g1, int b0, int b1)
{
    unsigned table[256];
    unsigned shift = channelShift(ch);
    int dr = r1 - r0;
    int dg = g1 - g0;
    int db = b1 - b0;
    for (int i = 0; i < 256; ++i) {
        int r = fp::ftol((double)i * dr * 0.00390625f + r0);
        int g = fp::ftol((double)dg * i * 0.00390625f + g0);
        int b = fp::ftol((double)db * i * 0.00390625f + b0);
        table[i] = ((unsigned)r << 8 | (unsigned)g) << 8 | (unsigned)b;
    }
    unsigned *p = s_buffers[dst];
    for (int i = 0; i < 0x10000; ++i)
        p[i] = table[(p[i] >> shift) & 0xff];
}

// @ 0x41c2a0  (op 38)
// dst = lerp(dst, b, (255 - mask channel) / 256).
static void opLerp(int dst, int src, int maskSrc, int ch)
{
    const unsigned *b = s_buffers[src];
    unsigned *a = s_buffers[dst];
    const unsigned *m = s_buffers[maskSrc];
    unsigned shift = channelShift(ch);
    for (int i = 0; i < 0x10000; ++i) {
        unsigned bc = b[i];
        double w = (int)(0xff - ((m[i] >> shift) & 0xff));
        unsigned ac = a[i];
        int ar = (ac >> 16) & 0xff, ag = (ac >> 8) & 0xff, ab = ac & 0xff;
        int r = fp::ftol((int)(((bc >> 16) & 0xff) - ar) * w * 0.00390625f + ar);
        int g = fp::ftol((int)(((bc >> 8) & 0xff) - ag) * w * 0.00390625f + ag);
        int bl = fp::ftol((int)((bc & 0xff) - ab) * w * 0.00390625f + ab);
        a[i] = ((unsigned)r << 8 | (unsigned)g) << 8 | (unsigned)bl;
    }
}

// @ 0x41c3d0  (op 39)
// Horizontal derivative (3x3 kernel with columns -1, 0, 1) + 128.
static void opDerivative(int dst)
{
    static const signed char kernel[3] = {-1, 0, 1};
    for (int y = 0; y < 256; ++y) {
        for (int x = 0; x < 256; ++x) {
            const unsigned *p = s_buffers[dst];
            int r = 0, g = 0, b = 0;
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 3; ++i) {
                    int k = kernel[i];
                    unsigned c = p[((x - 1 + i) & 0xff) + ((y - 1 + j) & 0xffu) * 256];
                    r += (int)((c >> 16) * k);
                    g += (int)(((c >> 8) & 0xff) * k);
                    b += (int)((c & 0xff) * k);
                }
            }
            r += 0x80;
            g += 0x80;
            b += 0x80;
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (b < 0) b = 0;
            s_tmp1[y * 256 + x] = ((unsigned)r << 8 | (unsigned)g) << 8 | (unsigned)b;
        }
    }
    copyFromTmp1(s_buffers[dst]);
}

// @ 0x419a50
static void runProgram(const unsigned char *program, unsigned *output)
{
    if (!program || !output)
        return;
    if (!s_tmp1)
        texgenInit();
    if (g_texgenCacheTga && loadTga(s_tgaName, output)) {
        s_done += program[3];
        s_progress((float)s_done / (float)s_total);
        return;
    }
    memcpy(s_header, program, 4);
    clearBuffer(s_tmp1);
    clearBuffer(s_tmp2);
    clearBuffer(s_buffers[0]);
    clearBuffer(s_buffers[1]);
    clearBuffer(s_buffers[2]);
    clearBuffer(s_buffers[3]);
    if ((*s_header & 0xffffff) != 0x475441) // "ATG"
        return;

    int count = (int)*s_header >> 24;
    int base = 4;
    for (int n = 0; n < count; ++n) {
        const unsigned char *in = program + base + n * 9;
        unsigned op = in[0];
        s_instr = in + 1;
        unsigned d = in[1];
        const unsigned char *a = in; // a[2]..a[8] are the arguments
        if (d < 4) {
            switch (op) {
            case 1:  opPerlin(d, a[2], a[4], a[5], a[6], a[7]); break;
            case 2:  opSine(d, a[8], a[2], a[3], a[4], a[5]); break;
            case 3:  opCells(d, a[2], a[3], a[4], a[5], a[6], a[7], a[8]); break;
            case 4:  opGradient(d, a[2], a[3], a[4]); break;
            case 5:  opCubicNoise(d, a[2], a[3], a[4], a[5], a[6], a[7]); break;
            case 6:  clearBuffer(s_buffers[d]); break;
            case 10: opWave(d, a[2], a[3], a[4], a[5], a[6], a[7]); break;
            case 11: opOffset(d, a[2], a[3]); break;
            case 12: opTwirl(d, a[2]); break;
            case 14: opEmboss(d, a[2]); break;
            case 15: opBlur(d, a[2]); break;
            case 17: opDisplace(d, a[2], a[3], a[4], a[5], a[6], a[7]); break;
            case 18: opSmear(d, a[2], a[3], a[4]); break;
            case 20: opSwapChannel(d, a[2], a[3], a[4]); break;
            case 21: opGrey(d, a[2]); break;
            case 23: opCopyChannel(d, a[2], a[3], a[4]); break;
            case 24: opBlend(d, a[2], a[3]); break;
            case 25: opMultiply(d, a[2]); break;
            case 26: opAddSaturate(d, a[2]); break;
            case 27: opMax(d, a[2]); break;
            case 30: opNormalScale(d, a[2]); break;
            case 31: opInvertBlue(d); break;
            case 32: opCurveBy(d, a[2], a[3]); break;
            case 33: opCurve(d, a[2]); break;
            case 34: opCosRemap(d, a[2], a[3]); break;
            case 35: opLevels(d, a[2], a[3], a[4]); break;
            case 36: opHueSaturation(d, a[2], a[3]); break;
            case 37: opColorMap(d, a[2], a[3], a[4], a[5], a[6], a[7], a[8]); break;
            case 38: opLerp(d, a[2], a[3], a[4]); break;
            case 39: opDerivative(d); break;
            case 40:
                opBitmap(d, in + 9, ((unsigned)a[2] * 0x100 + a[3]) * 0x100 + a[4],
                         ((unsigned)a[5] * 0x100 + a[6]) * 0x100 + a[7]);
                base += 0x2000;
                break;
            }
        }
        ++s_done;
        s_progress((float)s_done / (float)s_total);
    }
    memcpy(output, s_buffers[0], 0x40000);
    if (g_texgenCacheTga)
        saveTga(s_buffers[0]);
}

// @ 0x419a30
static unsigned *generateOne(const unsigned char *program)
{
    unsigned *pixels = (unsigned *)malloc(0x40000);
    runProgram(program, pixels);
    return pixels;
}

// @ 0x419980
unsigned **texgenGenerate(const unsigned char *const *programs, TexgenProgress progress)
{
    if (!s_initialised) {
        texgenInit();
        s_initialised = 1;
    }
    s_progress = progress;
    int count = 0;
    do
        ++count;
    while (programs[count]);
    s_total = 0;
    s_done = 0;
    for (int i = 0; i < count; ++i)
        s_total += programs[i][3];
    unsigned **images = (unsigned **)malloc(count * sizeof(unsigned *));
    for (int i = 0; i < count; ++i)
        images[i] = generateOne(programs[i]);
    s_total = 0;
    s_done = 0;
    texgenFree();
    return images;
}
