// Built-in functions and operators of the level language.
#include "script.h"
#include "../game/level.h"
#include "../game/sumo.h"
#include "../physics/world.h"

// @ 0x4046d0
double fmodf2(float a, float b)
{
    return fp::fmod(a, b);
}

// @ 0x404704
static double fmodWrapper(float a, float b)
{
    return fmodf2(a, b);
}

// @ 0x404ab9
// a^b, defined for negative bases through cos(b*pi).
double powSigned(float a, float b)
{
    if (!(a < 0.0f))
        return fp::exp(fp::log(a) * b);
    float l = (float)(fp::log(-a) * b);
    float c = (float)fp::cos(b * 3.14159274f);
    return fp::exp(l) * c;
}

// @ 0x40479a
static void fnAtanXY(Vec3 **a)
{
    *a[0] = V3((float)atanXY(a[1]->x, a[1]->y));
}

// @ 0x4047e0
static void fnAbs(Vec3 **a)
{
    *a[0] = V3((float)fp::sqrt(a[1]->lengthSq()));
}

// @ 0x404828
static void fnVec(Vec3 **a)
{
    *a[0] = V3(a[1]->x, a[2]->x, a[3]->x);
}

// @ 0x404872
static void fnSelX(Vec3 **a)
{
    Vec3 *src = a[1]->x <= 0.0f ? a[3] : a[2];
    *a[0] = *src;
}

// @ 0x40489a
static void fnMod(Vec3 **a)
{
    float z = (float)fmodWrapper(a[1]->z, a[2]->z);
    float y = (float)fmodWrapper(a[1]->y, a[2]->y);
    float x = (float)fmodWrapper(a[1]->x, a[2]->x);
    *a[0] = V3(x, y, z);
}

// @ 0x40491b
// Registered for cos, sin, tan and atan alike: all of them compute cos.
static void fnCos(Vec3 **a)
{
    float z = a[1]->z;
    float y = (float)fp::cos(a[1]->y);
    float x = (float)fp::cos(a[1]->x);
    *a[0] = V3(x, y, (float)fp::cos(z));
}

// @ 0x40498d
static void fnDot(Vec3 **a)
{
    Vec3 *u = a[1];
    Vec3 *v = a[2];
    *a[0] = V3(v->z * u->z + v->y * u->y + v->x * u->x);
}

// @ 0x4049d7
static void fnNormalize(Vec3 **a)
{
    *a[0] = a[1]->normalized();
}

// @ 0x40538d
// rot(v, w): v rotated by the axis-angle vector w
static void fnRot(Vec3 **a)
{
    Vec3 v = *a[1];
    v.rotate(*a[2]);
    *a[0] = v;
}

// @ 0x4049f9
static void opAdd(Vec3 **a)
{
    *a[0] = *a[1] + *a[2];
}

// @ 0x404a1e
static void opSub(Vec3 **a)
{
    *a[0] = *a[1] - *a[2];
}

// @ 0x404a43
static void opMul(Vec3 **a)
{
    *a[0] = a[1]->mul(*a[2]);
}

// @ 0x404a68
static void opDiv(Vec3 **a)
{
    Vec3 *u = a[1];
    Vec3 *v = a[2];
    *a[0] = V3(u->x / v->x, u->y / v->y, u->z / v->z);
}

// @ 0x404b20
static void opPow(Vec3 **a)
{
    float z = (float)powSigned(a[1]->z, a[2]->z);
    float y = (float)powSigned(a[1]->y, a[2]->y);
    float x = (float)powSigned(a[1]->x, a[2]->x);
    *a[0] = V3(x, y, z);
}

// The box being built: addbox() finalises the previous one before creating
// the next; the level loader finalises the last.
static void finishBox()
{
    Body *b = g_currentBox;
    Mat3 rot = b->rot;
    float threshold = b->breakThreshold;
    char isStatic = b->isStatic;
    b->rebuildAfterCut(1);
    g_currentBox->computeMassProperties();
    g_currentBox->recenter();
    g_currentBox->init();
    if (isStatic)
        g_currentBox->makeStatic();
    g_currentBox->rot = rot;
    g_currentBox->breakThreshold = threshold;
}

// @ 0x404bd6
// addbox(size, position, material, static)
static void fnAddBox(Vec3 **a)
{
    *a[0] = V3(0.0f, 0.0f, 0.0f);
    if (g_currentBox)
        finishBox();
    Vec3 half = *a[1];
    half.y = half.y * -1.0f;
    int material = fp::ftol(a[3]->x);
    if (material < 0)
        material = 0;
    if (material >= 31)
        material = 31;
    g_currentBox = createBox(half, *a[2], material, 0.0625f);
    if (fp::ftol(a[4]->x) != 0)
        g_currentBox->makeStatic();
}

// @ 0x404ce4
static void fnBreakability(Vec3 **a)
{
    *a[0] = V3(0.0f, 0.0f, 0.0f);
    float minimum = 10.0f;
    if (g_currentBox) {
        g_currentBox->breakThreshold = a[1]->x;
        if (g_currentBox->breakThreshold < minimum)
            g_currentBox->breakThreshold = minimum;
    }
}

// @ 0x404d26
static void fnRandom(Vec3 **a)
{
    float z = g_random.next() * 2.0f - 1.0f;
    float y = g_random.next() * 2.0f - 1.0f;
    float x = g_random.next() * 2.0f - 1.0f;
    *a[0] = V3(x, y, z);
}

// @ 0x404d8f
// turnto(direction): orients the current box
static void fnTurnTo(Vec3 **a)
{
    *a[0] = V3(0.0f, 0.0f, 0.0f);
    if (!g_currentBox)
        return;
    g_currentBox->rot.rotateY((float)atanXY(a[1]->x, a[1]->z));
    Vec3 flat = V3(a[1]->x, a[1]->z, 0.0f);
    float len = (float)fp::sqrt(flat.z * flat.z + flat.y * flat.y + flat.x * flat.x);
    g_currentBox->rot.rotateX((float)atanXY(a[1]->y, len));
}

// @ 0x404e53
// man(position, direction, kind): a wrestler start point.  In the editor the
// wrestler is created at once (kind 3 = player one, 2 = player two, else AI).
static void fnMan(Vec3 **a)
{
    *a[0] = V3(0.0f, 0.0f, 0.0f);
    if (g_editorMode) {
        if (g_sumoEnd < g_sumos + 4) {
            int kind = fp::ftol(a[3]->x);
            g_sumoEnd->create(a[1], (float)atanXY(a[2]->x, a[2]->z), kind, 0);
            g_sumoEnd->mode = 0;
            g_sumoEnd->controller = 2;
            if (fp::ftol(a[3]->x) == 3)
                g_sumoEnd->controller = 1;
            if (fp::ftol(a[3]->x) == 2)
                g_sumoEnd->controller = 0;
            g_sumoEnd->mode = 1;
            ++g_sumoEnd;
        }
    } else if ((unsigned)g_spawnCount <= 8) {
        g_spawnPos[g_spawnCount] = *a[1];
        g_spawnAngle[g_spawnCount++] = (float)atanXY(a[2]->x, a[2]->z);
    }
}

// @ 0x404f6c
// cutplane(normal, offset): cuts the current box
static void fnCutPlane(Vec3 **a)
{
    *a[0] = V3(0.0f, 0.0f, 0.0f);
    if (g_currentBox)
        g_currentBox->cut(*a[1], a[2]->x);
}

const ScriptBuiltin kMathBuiltins[12] = {   // @ 0x453420
    {"atanxy", 1, fnAtanXY},
    {"abs", 1, fnAbs},
    {"vec", 3, fnVec},
    {"selx", 3, fnSelX},
    {"cos", 1, fnCos},
    {"sin", 1, fnCos},
    {"tan", 1, fnCos},
    {"atan", 1, fnCos},
    {"rot", 2, fnRot},
    {"dot", 2, fnDot},
    {"normalize", 1, fnNormalize},
    {"mod", 2, fnMod},
};

const ScriptBuiltin kLevelBuiltins[6] = {   // @ 0x453568
    {"addbox", 4, fnAddBox},
    {"cutplane", 2, fnCutPlane},
    {"random", 1, fnRandom},
    {"turnto", 1, fnTurnTo},
    {"man", 3, fnMan},
    {"breakability", 1, fnBreakability},
};

const ScriptOperator kOperators[5] = {      // @ 0x453540
    {'+', 0, {0, 0}, opAdd},
    {'-', 0, {0, 0}, opSub},
    {'*', 1, {0, 0}, opMul},
    {'/', 1, {0, 0}, opDiv},
    {'^', 2, {0, 0}, opPow},
};
