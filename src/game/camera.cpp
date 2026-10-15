#include "camera.h"
#include "game.h"
#include "sumo.h"
#include "../platform/input.h"

Vec3 g_viewPos;          // @ 0xc06948
Mat3 g_viewRot;          // @ 0xc06954
Vec3 g_viewFocus;        // @ 0xc06820
int g_cameraMode;        // @ 0xc0682c

// ---------------------------------------------------------------------------
// Free camera (replay mode 3).  A developer tool: it also appends key frames to
// camera.dat every 50 frames or whenever space is pressed.

static Vec3 g_freePos;           // @ 0x454fec
static Mat3 g_freeRot;           // @ 0x454ff8
static Vec3 g_freeVel;           // @ 0x45501c
static float g_freeYaw;          // @ 0x455034
static float g_freeRoll;         // @ 0x455058
static float g_freeYawVel;       // @ 0x45505c
static float g_freeRollVel;      // @ 0x455060
static float g_freePitchVel;     // @ 0x455080
static float g_freePitch;        // @ 0x455084
static int g_cameraLogCreated;   // @ 0x455088
static int g_cameraLogFrame;     // @ 0x4533d4

static const float kFreeTurnDamping = 0.995f;     // @ 0x4533b0
static const float kFreeTurnSpeed = 0.00002f;     // @ 0x4533b4
static const float kFreeMoveDamping = 0.995f;     // @ 0x4533b8
static const float kFreeMoveSpeed = 0.00014f;     // @ 0x4533bc

// Up, Down, Left, Right, Home, PgUp, A, D, W, S, Enter, Ins, F, H, T, G, R, Y, E
static const signed char kFreeCameraKeys[20] = {  // @ 0x4533c0
    0x48, 0x50, 0x4b, 0x4d, 0x47, 0x49, 0x1e, 0x20, 0x11, 0x1f,
    0x1c, 0x52, 0x21, 0x23, 0x14, 0x22, 0x13, 0x15, 0x12, 0x00,
};

// @ 0x402784
void freeCameraReset()
{
    g_freeYaw = 1.5707964f;
    g_freeRot.m[0] = 1.0f;
    g_freePitch = 0.157f;
    g_freePos.x = -30.0f;
    g_freeRot.m[1] = 0.0f;
    g_freePos.y = 40.0f;
    g_freeRot.m[2] = 0.0f;
    g_freeRot.m[3] = 0.0f;
    g_freeRot.m[4] = 1.0f;
    g_freeRot.m[5] = 0.0f;
    g_freeRot.m[6] = 0.0f;
    g_freeRot.m[7] = 0.0f;
    g_freeRot.m[8] = 1.0f;
    g_freePos.z = 0.0f;
}

// @ 0x4027fd
void freeCameraSet(const Vec3 &pos, float yaw)
{
    g_freeRoll = 0.0f;
    g_freePitch = 0.0f;
    g_freePos = pos;
    g_freeYaw = yaw;
}

// @ 0x402827
void freeCameraResetAt(const Vec3 &pos, float yaw)
{
    freeCameraReset();
    g_freePos = pos;
    g_freeYaw = yaw;
}

// @ 0x402846
int freeCameraUpdate(int frames)
{
    if (g_cameraLogCreated == 0) {
        fclose(fopen("camera.dat", "w"));
        g_cameraLogCreated = 1;
    }

    float dt = (float)frames;
    float turnDamping = (float)fp::exp(fp::log(kFreeTurnDamping) * dt);
    float moveDamping = (float)fp::exp(fp::log(kFreeMoveDamping) * dt);
    float turn = dt * kFreeTurnSpeed;
    float move = dt * kFreeMoveSpeed;

    char key[20];
    for (unsigned i = 0; i < 19; ++i)
        key[i] = g_keyDown[kFreeCameraKeys[i]] != 0;
    if (key[18])
        move = move * 10.0f;

    if (key[0]) g_freePitchVel = g_freePitchVel + turn;
    if (key[1]) g_freePitchVel = g_freePitchVel - turn;
    if (key[4]) g_freeRollVel = g_freeRollVel - turn;
    if (key[5]) g_freeRollVel = g_freeRollVel + turn;
    if (key[3]) g_freeYawVel = g_freeYawVel - turn;
    if (key[2]) g_freeYawVel = g_freeYawVel + turn;

    // Steer gently towards the replay focus point.
    Vec3 focus = g_freeRot * (g_viewFocus - g_freePos);
    g_freeRollVel = g_freeRollVel * turnDamping;
    double invZ = 1.0 / focus.z;
    g_freePitchVel = (float)(((focus.y * invZ * -0.1f - g_freePitchVel) * 0.4f + g_freePitchVel) * turnDamping);
    g_freeYawVel = (float)(((invZ * focus.x * -0.1f - g_freeYawVel) * 0.4f + g_freeYawVel) * turnDamping);

    g_freeRoll = g_freeRoll - dt * g_freeRollVel;
    g_freePitch = dt * g_freePitchVel + g_freePitch;
    g_freeYaw = g_freeYaw - dt * g_freeYawVel;

    g_freeRot.identity();
    g_freeRot.rotateY(g_freeYaw);
    g_freeRot.rotateX(g_freePitch);
    g_freeRot.rotateZ(g_freeRoll);

    if (key[6]) {
        g_freeVel.x = g_freeVel.x - g_freeRot.m[0] * move;
        g_freeVel.y = g_freeVel.y - g_freeRot.m[1] * move;
        g_freeVel.z = g_freeVel.z - g_freeRot.m[2] * move;
    }
    if (key[7]) {
        g_freeVel.x = g_freeRot.m[0] * move + g_freeVel.x;
        g_freeVel.y = g_freeRot.m[1] * move + g_freeVel.y;
        g_freeVel.z = g_freeRot.m[2] * move + g_freeVel.z;
    }
    if (key[8]) {
        g_freeVel.x = g_freeRot.m[6] * move + g_freeVel.x;
        g_freeVel.y = g_freeRot.m[7] * move + g_freeVel.y;
        g_freeVel.z = g_freeRot.m[8] * move + g_freeVel.z;
    }
    if (key[9]) {
        g_freeVel.x = g_freeVel.x - g_freeRot.m[6] * move;
        g_freeVel.y = g_freeVel.y - g_freeRot.m[7] * move;
        g_freeVel.z = g_freeVel.z - g_freeRot.m[8] * move;
    }
    if (key[11]) {
        g_freeVel.x = g_freeVel.x - g_freeRot.m[3] * move;
        g_freeVel.y = g_freeVel.y - g_freeRot.m[4] * move;
        g_freeVel.z = g_freeVel.z - g_freeRot.m[5] * move;
    }
    if (key[10]) {
        g_freeVel.x = g_freeRot.m[3] * move + g_freeVel.x;
        g_freeVel.y = g_freeRot.m[4] * move + g_freeVel.y;
        g_freeVel.z = g_freeRot.m[5] * move + g_freeVel.z;
    }

    ++g_cameraLogFrame;
    bool spacePressed = g_keyDown[0x39] != 0;
    g_freeVel.x = g_freeVel.x * moveDamping;
    g_viewRot = g_freeRot;
    g_freeVel.y = g_freeVel.y * moveDamping;
    g_freeVel.z = g_freeVel.z * moveDamping;
    g_freePos.x = dt * g_freeVel.x + g_freePos.x;
    g_freePos.y = dt * g_freeVel.y + g_freePos.y;
    g_freePos.z = dt * g_freeVel.z + g_freePos.z;
    g_viewPos = g_freePos;

    int result = g_cameraLogFrame / 50;
    if (spacePressed || g_cameraLogFrame % 50 == 0) {
        g_keyDown[0x39] = 0;
        FILE *f = fopen("camera.dat", "a");
        const float posScale = 32.0f;        // @ 0x42b27c
        const float angleScale = 40.743664f; // @ 0x42b278  (256 / 2pi)
        fprintf(f, "{%d,%d,%d,%d,%d,%d,%d},\n",
                fp::ftol(g_freeRoll * angleScale), fp::ftol(g_freePitch * angleScale),
                fp::ftol(g_freeYaw * angleScale), fp::ftol(g_freePos.x * posScale),
                fp::ftol(g_freePos.y * posScale), fp::ftol(g_freePos.z * posScale),
                g_cameraLogFrame);
        result = fclose(f);
        g_cameraLogFrame = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// Gameplay camera.

Vec3 g_camPos;                   // @ 0x454fe0
static Vec3 g_camVel;            // @ 0x455028
static float g_camUnused;        // @ 0x455038
Vec3 g_camAngles;                // @ 0x45503c
static float g_camYawOffset;     // @ 0x455048
static Vec3 g_camPrevTarget;     // @ 0x45504c
static Vec3 g_camAngleVel;       // @ 0x455068
static Vec3 g_camCenter;         // @ 0x455074 minimax centre of all wrestlers
static float g_camZoomVel;       // @ 0x455090
float g_camPitch = 1.5f;         // @ 0x4533d8
float g_camPitchOffset = 0.5f;   // @ 0x4533dc
float g_camDistance = 10.0f;     // @ 0x4533e0

// @ 0x402d01
void gameCameraReset()
{
    g_camYawOffset = 0.0f;
    g_camUnused = 0.0f;
    g_camDistance = 10.0f;
    g_camPitch = 1.5f;
    g_camPitchOffset = 0.5f;
    g_camPos.x = 0.0f;
    g_camPos.y = 15.0f;
    g_camPos.z = -100.0f;
    if (g_attractMode != 0) {
        g_camPos.x = -100.0f;
        g_camPos.y = 7.0f;
        g_camPos.z = 0.0f;
    }
    g_camAngles.y = 0.0f;
    if (g_cameraMode != 0) {
        g_camPos.x = -100.0f;
        g_camPos.y = 7.0f;
        g_camPos.z = 0.0f;
        g_camAngles.y = -1.5707964f;
    }
    g_camAngles.z = 0.0f;
    g_camAngles.x = 0.0f;
    g_camAngleVel.z = 0.0f;
    g_camAngleVel.y = 0.0f;
    g_camAngleVel.x = 0.0f;
    g_camVel.z = 0.0f;
    g_camVel.y = 0.0f;
    g_camVel.x = 0.0f;
    g_camPrevTarget.z = 0.0f;
    g_camPrevTarget.y = 0.0f;
    g_camPrevTarget.x = 0.0f;
}

// @ 0x402f1b
void gameCameraUpdate()
{
    const Vec3 zero = V3(0.0f, 0.0f, 0.0f);
    Vec3 center = zero;
    float spread = 50.0f;
    int sumoCount = (int)(g_sumoEnd - g_sumos);

    // Iteratively search the point minimising the largest distance to any
    // wrestler (approximate smallest enclosing sphere).
    if (sumoCount > 0) {
        center = g_camCenter;
        Vec3 dir = zero;
        Vec3 prevCenter = center;
        Vec3 prevDir = zero;
        float step = 0.1f;
        float best = 1e35f;
        float worst = 0.0f;
        for (int iter = 64; iter != 0; --iter) {
            worst = 0.0f;
            dir = zero;
            for (Sumo *s = g_sumos; s < g_sumoEnd; ++s) {
                if (worst < (s->centerOfMass - center).lengthSq()) {
                    worst = (s->centerOfMass - center).lengthSq();
                    dir = (s->centerOfMass - center).normalized();
                }
            }
            float factor;
            if (worst <= best) {
                factor = 1.1f;
                best = worst;
            } else {
                factor = 0.7f;
                center = prevCenter;
                dir = prevDir;
            }
            step = step * factor;
            prevCenter = center;
            prevDir = dir;
            Vec3 d = dir * step;
            center.x = center.x + d.x;
            center.y = center.y + d.y;
            center.z = center.z + d.z;
        }
        center = prevCenter;
        spread = (float)fp::sqrt(worst);
    }

    float yawDelta = 0.0f;
    g_camCenter = center;
    int state = g_gameState;
    if ((state == GAME_OVER || state == GAME_HIDDEN || g_cameraMode == 3) && g_cameraMode != 1) {
        g_camPitchOffset = 0.0f;
        float speed = 0.008f;
        if (state == GAME_HIDDEN)
            speed = 0.02f;
        if (g_keyDown[0x49])   // Page Up
            yawDelta = speed;
        if (g_keyDown[0x47])   // Home
            yawDelta = yawDelta - speed;
    } else {
        g_camPitchOffset = 0.0f;
        if (state == GAME_RUNNING && g_attractMode == 0)
            g_camPitchOffset = 0.5f;
    }

    float zoom = g_camZoomVel;
    if (g_keyDown[0x4e])   // numpad +
        zoom = zoom - 0.017f;
    if (g_keyDown[0x4a])   // numpad -
        zoom = zoom + 0.017f;
    g_camZoomVel = zoom * 0.9f;
    g_camDistance = g_camDistance + g_camZoomVel;
    if (g_camDistance < 5.0f)
        g_camDistance = 5.0f;
    g_camYawOffset = g_camYawOffset + yawDelta;

    Vec3 smoothFocus = zero;
    Vec3 target = V3(0.0f, 40.0f, -100.0f);
    Vec3 dir = V3(0.0f, 40.0f, -100.0f);

    if (g_sumos < g_sumoEnd) {
        int n = (int)(g_sumoEnd - g_sumos);
        Vec3 a = g_sumos[0].centerOfMass;
        Vec3 b = zero;
        float dist = 0.0f;
        if (n >= 0) {
            if (n < 2) {
                dist = 50.0f;
                b = a;
            } else if (n == 2) {
                b = sumoCenterOfMass(&g_sumos[1]);
                float d = (float)fp::sqrt((a - b).lengthSq());
                dist = (g_camDistance * 3.0f + d * 1.37f) - 20.0f;
            } else if (n < 5) {
                a = center;
                dist = g_camDistance * 0.1f * spread * 2.8f;
                b = center;
            }
        }
        if (dist < g_camDistance * 4.0f)
            dist = g_camDistance * 4.0f;

        dir = b - a;
        dir.y = 0.0f;
        if (dir.z * dir.z + dir.x * dir.x < 0.0001f)
            dir = V3(-1.0f, 0.0f, 1.0f);
        dir.normalize();
        if (g_cameraMode == 3)
            dir = V3(0.0f, 0.0f, 1.0f);

        float pitch = g_camPitch - g_camPitchOffset;
        Vec3 offset = V3((float)fp::cos(pitch), 0.0f, (float)fp::sin(pitch));
        offset = offset.cross(V3(0.0f, 0.75f, 0.0f));
        g_camPitch = ((offset.z * dir.z + offset.x * dir.x + offset.y * dir.y) / dist) * 0.9f + g_camPitch;
        offset.rotate(V3(0.0f, g_camYawOffset + g_camPitchOffset, 0.0f));
        offset.x = offset.x * dist;
        offset.y = offset.y * dist;
        offset.z = offset.z * dist;
        const float half = 0.5f;
        smoothFocus = (a + b) * half;
        target = smoothFocus + offset;
        target.y = (dist - 45.0f) * 0.3f + center.y + 11.0f;
    }

    state = g_gameState;
    float stiffness = 0.0003f;
    if (state == GAME_OVER) {
        if ((target - g_camPos).lengthSq() > 100.0)
            stiffness = 0.002f;
    }
    const float thirty = 30.0f;
    g_camVel += (((target - g_camPrevTarget) - g_camVel) * stiffness) * thirty;
    Vec3 sideways = V3(yawDelta * 0.6f, 0.0f, 0.0f) * g_viewRot;
    g_camVel += ((target - g_camPos) + sideways) * stiffness;
    g_camVel.x = g_camVel.x * 0.98f;
    g_camVel.y = g_camVel.y * 0.98f;
    g_camVel.z = g_camVel.z * 0.98f;
    g_camPrevTarget = target;

    const float follow = 0.01f;
    Vec3 pull = (target - g_camPos) * follow;
    g_camPos.x = g_camPos.x + pull.x;
    g_camPos.y = g_camPos.y + pull.y;
    g_camPos.z = g_camPos.z + pull.z;
    g_camPos.x = g_camPos.x + g_camVel.x;
    g_camPos.y = g_camPos.y + g_camVel.y;
    g_camPos.z = g_camPos.z + g_camVel.z;

    if (state == GAME_MENU) {
        g_camPos = V3(-129.0f, 17.0f, 6.0f);
        g_camAngles = V3(0.05f, -1.6650441f, 0.0f);
    }

    g_viewPos = g_camPos;
    g_viewRot.identity();
    g_viewRot.rotateLocalX(g_camAngles.x);
    g_viewRot.rotateLocalY(g_camAngles.y);
    g_viewRot.rotateLocalZ(g_camAngles.z);

    Vec3 look = g_viewRot * (smoothFocus - g_camPos);
    double inv = 1.0f / fp::sqrt(look.x * look.x + look.y * look.y + look.z * look.z);
    double ax = (g_camAngleVel.x - look.y * inv * -0.016f) * 0.8f;
    double ay = (g_camAngleVel.y - look.x * inv * 0.016f) * 0.8f;
    g_camAngleVel.x = (float)ax;
    g_camAngleVel.y = (float)ay;
    g_camAngleVel.z = g_camAngleVel.z * 0.8f;
    g_camAngles.x = g_camAngleVel.x + g_camAngles.x;
    g_camAngles.y = g_camAngleVel.y + g_camAngles.y;
    g_camAngles.z = g_camAngleVel.z + g_camAngles.z;
}
