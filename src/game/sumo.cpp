// The sumo wrestler.
#include "sumo.h"
#include "game.h"
#include "camera.h"
#include "level.h"
#include "menu.h"
#include "replay.h"
#include "../core/common.h"
#include "../platform/input.h"
#include "../platform/window.h"
#include "../audio/sound.h"
#include "../audio/music.h"
#include "../license/license.h"
#include "../render/scene.h"
#include "../render/textures.h"

Sumo g_sumos[MAX_SUMOS];
Sumo *g_sumoEnd = g_sumos;
Random g_aiRandom;
int g_licenseTicks;
float g_legTweak;
static char g_dojoFlag;             // @ 0x453860 written only

// @ 0x40e6b2
// Moves the body on the other side of the joint so that the joint closes.
void alignJointBody(Joint *j, int side)
{
    Body **pair = &j->a;
    Vec3 *anchors = &j->anchorA;
    Body *src = pair[side];
    int other = side ^ 1;
    pair[other]->rot = src->rot;
    Vec3 w = anchors[side] * src->rot + src->pos;
    Body *dst = pair[other];
    dst->pos = w - dst->rot * anchors[other];
}

// @ 0x40e73a
// Stores the current relative orientation of every joint as motor target.
void Sumo::captureMotorTargets(JointMotor *motors) const
{
    for (int i = 0; i < 14; ++i) {
        Joint *j = joint[i];
        motors[i].refA = j->b->rot * (j->axisA * j->a->rot);
        motors[i].refB = j->b->rot * (j->refA * j->a->rot);
    }
}

// @ 0x40e7c8
Vec3 Sumo::centerOfMassOf() const
{
    Vec3 sum = V3(0.0f, 0.0f, 0.0f);
    float mass = 0.0f;
    for (int i = 0; i < 15; ++i) {
        Body *b = body[i];
        mass = mass + b->mass;
        Vec3 m = b->pos * b->mass;
        sum.x = sum.x + m.x;
        sum.y = sum.y + m.y;
        sum.z = sum.z + m.z;
    }
    double inv = 1.0 / mass;
    sum.x = (float)(sum.x * inv);
    sum.y = (float)(sum.y * inv);
    sum.z = (float)(sum.z * inv);
    if (sum.z * sum.z + sum.x * sum.x + sum.y * sum.y > 1000000.0f)
        sum = V3(0.0f, 0.0f, 0.0f);
    return sum;
}

Vec3 sumoCenterOfMass(Sumo *s)
{
    return s->centerOfMassOf();
}

// @ 0x40e896
float Sumo::kineticEnergy() const
{
    float e = 0.0f;
    for (int i = 0; i < 15; ++i) {
        Body *b = body[i];
        float linear = b->vel.lengthSq() * b->mass;
        e = b->angVel.lengthSq() * b->inertia + linear + e;
    }
    return e;
}

// @ 0x40e8f0
Vec3 Sumo::averageVelocity() const
{
    Vec3 sum = V3(0.0f, 0.0f, 0.0f);
    float mass = 0.0f;
    for (int i = 0; i < 15; ++i) {
        Body *b = body[i];
        mass = mass + b->mass;
        Vec3 m = b->vel * b->mass;
        sum.x = sum.x + m.x;
        sum.y = sum.y + m.y;
        sum.z = sum.z + m.z;
    }
    double inv = 1.0 / mass;
    sum.x = (float)(sum.x * inv);
    sum.y = (float)(sum.y * inv);
    sum.z = (float)(sum.z * inv);
    return sum;
}

// @ 0x40e98c
Vec3 Sumo::angularMomentum(const Vec3 &point, const Vec3 &velocity) const
{
    Vec3 sum = V3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 15; ++i) {
        Body *b = body[i];
        Vec3 spin = b->angVel * b->inertia;
        Vec3 l = (b->vel - velocity).cross(b->pos - point) * b->mass + spin;
        sum.x = sum.x + l.x;
        sum.y = sum.y + l.y;
        sum.z = sum.z + l.z;
    }
    return sum;
}

// @ 0x40ea52
// Drives every joint towards its motor target with a clamped torque.
void Sumo::applyMotors(JointMotor *motors)
{
    float k1 = 0.4f;
    float k2 = 0.25f;
    for (int i = 0; i < 14; ++i) {
        JointMotor *m = &motors[i];
        Joint *j = joint[i];
        float strength = m->strength;
        Vec3 t = (m->refA * j->b->rot).cross(j->axisA * j->a->rot) * k1;
        Vec3 u = ((m->refB * j->b->rot).cross(j->refA * j->a->rot) * k1) * k2;
        t.x = t.x + u.x;
        t.y = t.y + u.y;
        t.z = t.z + u.z;
        Vec3 dw = j->a->angVel - j->b->angVel;
        t.x = t.x - dw.x;
        t.y = t.y - dw.y;
        t.z = t.z - dw.z;
        double len2 = (double)t.z * t.z + (double)t.y * t.y + (double)t.x * t.x;
        if (len2 > strength * strength) {
            double s = strength / fp::sqrt(len2);
            t.x = (float)(t.x * s);
            t.y = (float)(t.y * s);
            t.z = (float)(t.z * s);
        }
        float k = 0.7f / (j->b->invInertia + j->a->invInertia);
        jointApplyTorque(&j->a, t * k);
    }
}

// @ 0x40fd42
void sumoApplyMotors()
{
    for (Sumo *s = g_sumos; s < g_sumoEnd; ++s)
        s->applyMotors(s->motor);
}

// @ 0x40fd6e
// Cosine-rule helper for the two bone leg: returns -cos of the angle between
// a and b in a triangle with sides a, b, c (clamped to +-1).
float lawOfCosines(float a, float b, float c)
{
    if (a + b <= c)
        return 1.0f;
    if (a + c < b)
        return -1.0f;
    double inv = 1.0 / a;
    double p = inv * b;
    double q = (float)inv * c;
    return (float)-((p * p - q * q + 1.0f) / (p + p));
}

// @ 0x40fdd0
// Debug marker: two crossed lines, drawn by a stub in the release build.
void debugCross(const Vec3 &pos, unsigned color)
{
    Vec3 a = V3(-1.0f, 0.0f, -1.0f);
    Vec3 b = V3(1.0f, 0.0f, 1.0f);
    doNothing();
    a = V3(-1.0f, 0.0f, 1.0f);
    b = V3(1.0f, 0.0f, -1.0f);
    doNothing();
    (void)pos;
    (void)color;
}

// @ 0x40fe9b
// Bit 0 turn left, 1 turn right, 2 walk, 3 start / stand, 4 push, 5 push with one hand.
unsigned Sumo::keyboardInput() const
{
    static const unsigned char kKeys[2][8] = {
        {0x4b, 0x4d, 0x48, 0x50, 0x0e, 0x1c, 0, 0},   // arrows, backspace, enter
        {0x1e, 0x20, 0x11, 0x1f, 0x2a, 0x1d, 0, 0},   // A D W S, shift, ctrl
    };
    unsigned bits = 0;
    unsigned bit = 1;
    for (int i = 0; i < 6; ++i) {
        if (g_keyDown[kKeys[controller][i]])
            bits |= bit;
        bit *= 2;
    }
    return bits;
}

// @ 0x40ff13
void Sumo::cheer(int slot)
{
    modeTimer = 0;
    mode = 8;
    playSound(5, 1.0f, 0.75f, slot ^ 3);
}

// @ 0x40ff4c
// The computer opponent: walks at the opponent and pushes when close.
unsigned Sumo::aiInput(Sumo *opp)
{
    if (g_gameState == GAME_HIDDEN) {
        if (body[0]->lastContactFrame == g_frame && g_frame > 10 && stepState == 0 && mode == 0)
            cheer(1);
        return 0;
    }

    Vec3 myVel = averageVelocity();                       // [EBP-0x48]
    Vec3 oppVel = opp->averageVelocity();                 // [EBP-0x54]
    unsigned bits = 0;
    Vec3 forward = V3(1.0f, 0.0f, 0.0f) * body[0]->rot;   // [EBP-0x3c]
    forward.y = 0.0f;
    forward.normalize();
    Vec3 side = forward.cross(V3(0.0f, 1.0f, 0.0f));      // [EBP-0x24]
    Vec3 d = opp->body[0]->pos - body[0]->pos;            // [EBP-0x30]
    float facing = side.y * tilt.y + side.z * tilt.z + side.x * tilt.x;          // [EBP-0x14]
    float ahead = forward.z * d.z + forward.x * d.x + forward.y * 0.0f;          // [EBP-0xc]
    char oppPushing = opp->armAction != 0;                // [EBP-2]
    float across = d.z * side.z + d.x * side.x + side.y * 0.0f;                  // [EBP-0x10]
    char oppStumbling = opp->tilt.lengthSq() > 25.0f;     // [EBP-1]
    char steady = opp->pushImpulse.lengthSq() < 0.04f;    // [EBP+0xb]
    float ahead2 = ahead * ahead;                         // [EBP-0x18]

    if ((ahead2 < (d.z * d.z + d.x * d.x) * 0.25f || ahead2 < 16.0f) && tilt.lengthSq() < 16.0f &&
        across > 0.0f && !oppStumbling &&
        (aiPressure < 160 || side.y * tilt.y + side.z * tilt.z + side.x * tilt.x > -2.0f)) {
        float range = 1.6f;
        if (steady)
            range = 1.4f;
        if (mode == 3)
            range = (float)modeTimer * range * 0.00153846154f;
        if (aiWalkDelay < g_frame - g_matchStartFrame) {
            if (range * range > pushImpulse.lengthSq())
                bits = 4;
        } else if (aiStandDelay > g_frame - g_matchStartFrame) {
            bits = 1;
        }
    }

    float reach = 5.1f;
    if (steady) {
        reach = 4.8f;
        if (oppPushing)
            reach = 8.0f;
    }
    Vec3 rel1 = oppVel - myVel;
    Vec3 rel2 = oppVel - myVel;
    float closing = ((side.y * rel1.y + side.z * rel1.z + side.x * rel1.x) * 50.0f + across) *
                    ((side.y * rel2.y + side.z * rel2.z + side.x * rel2.x) * 50.0f + across);
    if (reach * reach > closing && facing > -0.5f && ahead2 < 64.0f) {
        if (aiPressure > 10 || reach > 7.5f || aiAggressive)
            bits |= 0x20;
        else
            bits |= 0x10;
        if (steady)
            bits &= ~4u;
        aiPressure = aiPressure + 8;
    } else if (--aiPressure < 0) {
        aiPressure = 0;
    }

    if (g_gameState == GAME_WAITING) {
        if (g_frame > aiStartFrame || (g_frame > aiPauseFrame && g_frame < aiPauseFrame + 8))
            bits = 8;
    } else if (g_gameState == GAME_OVER) {
        if (g_aiStands)
            bits &= ~4u;
        else if (g_frame % 400 > 200)
            bits |= 4;
    }
    return bits;
}

// @ 0x41041d
// Picks the wrestler that is closest, preferring ones in front.
Sumo *Sumo::findOpponent(const Vec3 &side, const Vec3 &forward)
{
    Sumo *best = nullptr;
    float bestScore = 1e36f;
    for (Sumo *s = g_sumos; s < g_sumoEnd; ++s) {
        if (s == this)
            continue;
        Vec3 d = s->body[0]->pos - body[0]->pos;
        float behind = -(d.y * side.y + d.z * side.z + d.x * side.x);
        float across = (float)(fp::fabs(d.y * forward.y + d.z * forward.z + d.x * forward.x) * 4.0f);
        float penalty = across;
        if (behind > across)
            penalty = behind;
        double score = fp::sqrt(d.y * d.y + d.z * d.z + d.x * d.x) + penalty;
        if (score < bestScore) {
            bestScore = (float)score;
            best = s;
        }
    }
    return best;
}

static Joint *newJoint(Body *a, Vec3 anchorA, Vec3 axisA, Vec3 refA,
                       Body *b, Vec3 anchorB, Vec3 axisB, Vec3 refB,
                       float limitCos, float limitTwist, float hinge, char alignChild)
{
    Joint *j = g_jointEnd;
    j->a = a;
    j->anchorA = anchorA;
    j->axisA = axisA;
    j->refA = refA;
    j->b = b;
    j->anchorB = anchorB;
    j->axisB = axisB;
    j->refB = refB;
    j->limitCos = limitCos;
    j->limitTwist = limitTwist;
    j->hinge = hinge;
    j->alignChild = alignChild;
    return j;
}

static Vec3 unit(Vec3 v)
{
    v.normalize();
    return v;
}

// @ 0x40ec0d
// Builds a wrestler standing at pos, facing angle.
void Sumo::create(const Vec3 *pos, float angle, int material, Sumo *opp)
{
    memset(this, 0, sizeof(Sumo));

    aiStartFrame = fp::ftol((g_aiRandom.next() + 1.0f) * 300.0f);
    aiPauseFrame = fp::ftol((g_aiRandom.next() + 1.0f) * 300.0f);
    aiStandDelay = 0;
    aiWalkDelay = fp::ftol(g_aiRandom.next() * 180.0f);
    if (g_aiRandom.next() < 0.5f && opp && opp->controller == 2)
        aiStandDelay = fp::ftol(g_aiRandom.next() * 120.0f);
    aiAggressive = g_aiRandom.next() < 0.3f ? 1 : 0;

    const float uv = 0.125f;
    Body *torso = createBox(V3(2.8f, -2.2f, 2.0f), V3(0.0f, 13.8f, 0.0f) + *pos, material, uv);
    torso->contactIterations = 40;
    torso->rot.rotateY(angle);
    torso->vel += torso->rot * V3(0.0f, 0.0f, 0.1f);
    torso->sound = 4;
    torso->soundVolume = 0.01f;
    Body *chest = createBox(V3(2.7f, -2.2f, 1.5f), V3(0.0f, 30.0f, 0.0f), material, uv);
    chest->contactIterations = 40;
    chest->sound = 4;
    chest->soundVolume = 0.01f;
    Body *head = createBox(V3(1.2f, -1.5f, 1.2f), V3(0.0f, 36.0f, 0.0f), material, uv);
    head->contactIterations = 40;

    Vec3 down = V3(0.0f, -1.0f, 0.0f);
    Vec3 xAxis = V3(1.0f, 0.0f, 0.0f);
    Joint *j = newJoint(torso, V3(0.0f, 2.4f, 0.0f), down, xAxis,
                        chest, V3(0.0f, -2.2f, 0.0f), down, xAxis, 0.09f, 0.16f, 0.0f, 1);
    alignJointBody(j, 0);
    ++g_jointEnd;
    j = newJoint(chest, V3(0.0f, 2.7f, 0.0f), down, xAxis,
                 head, V3(0.0f, -1.5f, 0.0f), down, xAxis, 0.49f, 0.81f, 0.0f, 0);
    alignJointBody(j, 0);
    ++g_jointEnd;

    // legs
    float side = 1.0f;
    for (int n = 2; n > 0; --n) {
        Body *foot = createBox(V3(1.2f, -0.7f, 2.0f), V3(side * 1.5f, 0.7f, 1.0f) + *pos, material, uv);
        foot->scaleMass(3.0f);
        foot->contactIterations = 40;
        foot->sound = 3;
        foot->soundVolume = 0.002f;
        foot->inertia = foot->inertia * 0.5f;
        foot->soundScale = 400.0f;
        foot->invInertia = foot->invInertia + foot->invInertia;
        Body *shin = createBox(V3(1.0f, -2.3f, 1.0f), V3(side * 1.5f, 2.2f, 0.0f) + *pos, material, uv);
        shin->scaleMass(1.7f);
        shin->contactIterations = 40;
        shin->sound = 4;
        shin->soundVolume = 0.005f;
        Body *thigh = createBox(V3(1.2f, -3.0f, 1.2f), V3(side * 3.0f, 2.2f, 0.0f) + *pos, material, uv);
        thigh->contactIterations = 40;
        thigh->sound = 4;
        thigh->soundVolume = 0.005f;

        Vec3 sideAxis = V3(side, 0.0f, 0.0f);
        Joint *hip = newJoint(thigh, V3(0.0f, 2.2f, 0.0f), down, sideAxis,
                              torso, V3(side * 1.5f, -2.0f, 0.0f), unit(V3(side * 0.8f, -1.0f, 0.1f)),
                              unit(V3(side, 0.0f, -0.6f)), 0.64f, 0.36f, 0.0f, 0);
        alignJointBody(hip, 1);
        ++g_jointEnd;
        Joint *knee = newJoint(shin, V3(0.0f, 2.3f, 0.0f), down, sideAxis,
                               thigh, V3(0.0f, -2.5f, 0.0f), unit(V3(0.0f, -0.2f, -1.0f)), sideAxis,
                               0.9604f, 0.25f, 1.0f, 0);
        upperLegLength = (float)fp::sqrt((hip->anchorA - knee->anchorB).lengthSq());
        alignJointBody(knee, 1);
        ++g_jointEnd;
        Joint *ankle = newJoint(foot, V3(0.0f, 1.0f, -1.0f), down, sideAxis,
                                shin, V3(0.0f, -1.8f, 0.0f), down, sideAxis, 0.49f, 0.25f, 0.0f, 0);
        lowerLegLength = (float)fp::sqrt((knee->anchorA - ankle->anchorB).lengthSq());
        alignJointBody(ankle, 1);
        ++g_jointEnd;
        side = -1.0f;
    }

    // arms
    side = 1.0f;
    for (int n = 2; n > 0; --n) {
        Vec3 origin = V3(0.0f, 0.0f, 0.0f);
        Body *upper = createBox(V3(1.9f, -0.8f, 1.1f), origin, material, uv);
        upper->contactIterations = 40;
        Body *fore = createBox(V3(1.9f, -0.7f, 0.8f), origin, material, uv);
        fore->contactIterations = 40;
        Body *hand = createBox(V3(1.4f, -0.3f, 1.1f), origin, material, uv);
        hand->soundVolume = 0.005f;
        hand->sound = 4;
        hand->contactIterations = 40;
        fore->soundVolume = 0.005f;
        fore->sound = 4;
        upper->soundVolume = 0.005f;
        upper->sound = 4;
        hand->scaleMass(2.0f);
        fore->scaleMass(1.5f);

        Vec3 sideAxis = V3(side, 0.0f, 0.0f);
        Vec3 up = V3(0.0f, 1.0f, 0.0f);
        Joint *shoulder = newJoint(upper, V3(side * -1.5f, 0.0f, 0.0f), sideAxis, unit(V3(side * 0.5f, 1.0f, 0.0f)),
                                   chest, V3(side * 3.2f, 2.0f, 0.1f), V3(side, 0.0f, 0.2f),
                                   unit(V3(side * 0.0f, 1.0f, 0.0f)), 0.9604f, 0.49f, 0.0f, 0);
        alignJointBody(shoulder, 1);
        ++g_jointEnd;
        Joint *elbow = newJoint(upper, V3(side * 1.5f, 0.0f, -0.3f), unit(V3(side * 0.6f, 0.0f, 1.0f)), up,
                                fore, V3(-1.8f * side, 0.0f, 0.0f), sideAxis, up, 0.7569f, 0.25f, 1.0f, 0);
        alignJointBody(elbow, 0);
        ++g_jointEnd;
        Joint *wrist = newJoint(fore, V3(side * 1.5f, 0.0f, 0.1f), sideAxis, up,
                                hand, V3(-1.1f * side, 0.0f, 0.0f), sideAxis, up, 0.25f, 0.64f, 0.0f, 0);
        alignJointBody(wrist, 0);
        ++g_jointEnd;
        side = -1.0f;
    }

    for (int i = 0; i < 15; ++i)
        body[i] = g_bodyEnd - 15 + i;
    for (int i = 0; i < 14; ++i)
        joint[i] = g_jointEnd - 14 + i;

    footHeight = -7.9f;
    foot[0] = V3(0.5f, -7.9f, 0.0f);
    foot[1] = V3(-0.5f, -7.9f, 0.0f);
    captureMotorTargets(motor);
    captureMotorTargets(restMotor);
    opponent = opp;
}
// @ 0x410b60
// One simulation step of the wrestler: rules, input, balance and the
// procedural stepping / arm animation, then the joint motor targets.
void Sumo::update(Sumo *opp)
{
    float liftScale = 0.0f;        // [EBP-0x10]
    float bendBlend = 0.0f;        // [EBP-0x20]
    Vec3 com = centerOfMassOf();   // [EBP-0x1c]
    Vec3 avgVel = averageVelocity(); // [EBP+0x3c]
    Vec3 momentum = angularMomentum(com, avgVel); // [EBP-0x70]
    centerOfMass = com;

    int slot = 1;                  // [EBP+0x20] sound slot
    if ((int)(opp - this) > 1)
        slot = 2;
    if (!opp)
        opp = this;

    // a wrestler that touches the floor with anything but feet/shins loses
    if (g_matchStartFrame < g_frame - 50) {
        for (int i = 0; i < 15; ++i) {
            if (body[i]->lastHeavyContactFrame >= g_frame - 1 && i != 3 && i != 6 && i != 4 && i != 7 &&
                g_gameState != 0) {
                if (!lost) {
                    lost = 1;
                    --g_standingCount;
                    g_ranking[g_standingCount] = (int)(this - g_sumos);
                    if (g_standingCount == 1) {
                        g_framesSinceStart = 0;
                        g_gameState = GAME_OVER;
                    }
                }
                mode = 5;
                opp->mode = 5;
            }
        }
        if (g_gameState == GAME_OVER && !lost)
            g_ranking[0] = (int)(this - g_sumos);
    }
    ++g_framesSinceStart;

    Vec3 forward = V3(1.0f, 0.0f, 0.0f) * body[0]->rot;   // [EBP-0x54]
    forward.y = 0.0f;
    forward.normalize();
    Vec3 up = V3(0.0f, 1.0f, 0.0f);
    Vec3 side = forward.cross(up);                        // [EBP-0x3c]

    if (g_frame - g_matchStartFrame > 360) {
        Sumo *nearest = findOpponent(side, forward);
        if (nearest) {
            opp = nearest;
            opponent = nearest;
        }
    }

    unsigned input = 0;                                   // [EBP+0xc]
    if (controller >= 0) {
        if (controller <= 1)
            input = keyboardInput();
        else if (controller == 2)
            input = aiInput(opp);
    }
    int state = g_gameState;
    if (g_cameraMode == 1) {
        if (controller == 2 && state != GAME_RUNNING)
            input = keyboardInput();
    } else if (mode != 0 && mode != 3 && mode != 5) {
        input &= 8;
    }

    // pull the wrestlers together after a match / before the start
    if ((g_framesSinceStart < 200 && state == GAME_OVER) ||
        (opp && opp->stepState == 3 && state == GAME_WAITING)) {
        Vec3 d = opp->centerOfMassOf() - com;            // [EBP-0x64]
        d.y = 0.0f;
        float pull = 0.0f;                                // [EBP+0x38]
        if (d.x * d.x + d.z * d.z < 1600.0f && tilt.lengthSq() > 0.16f)
            pull = 3.5f;
        float k = pull * 0.04000002f;
        pushImpulse += d.normalized() * k;
    }

    // stay away from the edge of the dohyo
    float edgePush = 0.0f;                                // [EBP+0x64]
    if ((g_ringRadius - 5.0f < fp::fabs(com.x) && g_ringRadius + 18.0f > fp::fabs(com.x)) ||
        (g_ringRadius - 5.0f < fp::fabs(com.z) && g_ringRadius + 18.0f > fp::fabs(com.z)))
        edgePush = 1.5f;
    if (g_gameState == GAME_OVER && g_framesSinceStart > 300 && tilt.lengthSq() > 0.64f &&
        stepState != 12 && stepState != 13)
        edgePush = 0.6f;
    Vec3 flat = com;                                      // [EBP+0x2c]
    flat.y = 0.0f;
    if (!g_editorMode && g_currentLevel == 0) {
        float k = 0.04000002f;
        pushImpulse += (flat.normalized() * edgePush) * k;
    }

    for (int i = 0; i < 14; ++i)
        motor[i].strength = i < 8 ? 0.1f : 0.02f;
    motor[10].strength = 0.02f;
    motor[13].strength = 0.02f;
    float k24 = 0.1f;                                     // [EBP+0x24]
    motor[1].strength = 0.003f;
    avgVel += momentum.cross(V3(0.0f, -1e-5f, 0.0f));

    float crouch = 0.0f;                                  // [EBP-0xc]
    if (input & 4) {
        float k = 0.032f;
        pushImpulse += side * k;
    }
    float turn = 0.0f;
    if (input & 1)
        turn = 0.06f;
    if (input & 2)
        turn = turn - 0.06f;
    char stepNow = 0;                                     // [EBP-5]
    char posing = 0;                                      // [EBP+0x53]
    turnInput = (turn - turnInput) * 0.1f + turnInput;
    float turnCmd = turnInput;                            // [EBP+0x28]
    float armReach[6], armRaise[6], armBend[6];           // [EBP-0xe0], [EBP-0xcc], [EBP-0xbc]
    armBend[0] = 0.0f;
    armBend[3] = 0.0f;
    armReach[0] = 1.5f;
    armReach[3] = 1.5f;
    armRaise[0] = 0.2f;
    armRaise[3] = 0.2f;
    if (stepState == 3 && mode < 5)
        mode = 0;

    float lean = 0.0f;                                    // [EBP-0x58]
    Vec3 bowAxisA, bowAxisB;                              // [EBP-0x158], [EBP-0x134]
    switch (mode) {
    case 4:   // knocked over: wait until upright
        input = 0;
        if (tilt.lengthSq() < 0.36f) {
            if (modeTimer > 100) {
                mode = 1;
                modeTimer = 0;
            }
        } else {
            modeTimer = 0;
        }
        ++modeTimer;
        break;

    case 1: { // standing up into the bow
        int n = modeTimer;
        input = 0;
        posing = 1;
        float s = n * (1.0f / 60.0f);                     // [EBP+0x60]
        if (n > 60)
            s = 1.0f;
        if (n == 70 || n == 4) {
            Vec3 rest = V3(1.3f, footHeight, 0.0f);
            if ((foot[0] - rest).lengthSq() > 0.16f)
                stepNow = 1;
        }
        if (n == 80) {
            modeTimer = 0;
            armAction = 3;
            mode = 2;
        }
        crouch = (s * s * 3.0f - s * s * s * 2.0f) * 1.2f;
        float k = (1.0f - s) * s * 0.4f;
        Vec3 shift = side * k;
        com.x = com.x - shift.x;
        com.y = com.y - shift.y;
        com.z = com.z - shift.z;
        if (stepState == 0) {
            ++modeTimer;
        } else if (modeTimer > 90) {
            modeTimer = 90;
        } else if (modeTimer > 0) {
            --modeTimer;
        }
        break;
    }

    case 2: { // bowing: wait for both wrestlers to touch the floor
        int n = modeTimer;
        posing = 1;
        float s = n * (1.0f / 90.0f);                     // [EBP+0x38]
        if (n > 90)
            s = 1.0f;
        modeTimer = n + 1;
        float h = s * s * 3.0f - s * s * s * 2.0f;
        crouch = 1.25f;
        float back = -0.017f;
        k24 = 0.7f * h;
        liftScale = h * 1.1f;
        Vec3 drift = side * back;
        avgVel.x = avgVel.x + drift.x;
        avgVel.y = avgVel.y + drift.y;
        avgVel.z = avgVel.z + drift.z;
        bowAxisA = V3(-0.1f, 0.0f, 1.0f);
        bowAxisA.normalize();
        bowAxisB = V3(0.1f, 0.0f, 1.0f);
        bowAxisB.normalize();
        armReach[0] = 0.0f;
        armReach[3] = 0.0f;
        float target = 0.0f;
        if ((input & 8) || modeTimer > 700)
            target = 1.0f;
        if (g_gameState == GAME_RUNNING) {
            armAction = 0;
            modeTimer = 0;
            mode = 3;
        }
        int f = g_frame - 20;
        if (body[11]->lastContactFrame > f || body[14]->lastHeavyContactFrame > f ||
            opp->body[11]->lastHeavyContactFrame > f || opp->body[14]->lastHeavyContactFrame > f) {
            g_gameState = GAME_RUNNING;
            g_matchStartFrame = g_frame;
        }
        input = 0;
        modeBlend = (target - modeBlend) * 0.16f + modeBlend;
        double b2 = (double)modeBlend * modeBlend;
        float raise = (float)((1.0 - b2 * b2) * 1.5f);
        armRaise[0] = raise;
        armRaise[3] = raise;
        armBend[0] = s * 0.6f;
        armBend[3] = s * 0.6f;
        break;
    }

    case 3: { // rising from the bow into the fight
        input &= ~8u;
        float zero = 0.0f;
        Vec3 drift = side * zero;
        avgVel.x = avgVel.x - drift.x;
        avgVel.y = avgVel.y - drift.y;
        avgVel.z = avgVel.z - drift.z;
        int n = modeTimer;
        float s = n * (1.0f / 65.0f);
        if (n > 65) {
            mode = 0;
            s = 1.0f;
        }
        double h = 1.0 - ((double)s * s * 3.0f - (double)s * s * s * 2.0);
        crouch = (float)(1.2f * h);
        k24 = (float)(0.7f * h);
        liftScale = (float)(h * 1.1f);
        modeTimer = n + 1;
        break;
    }

    case 5:   // match over: idle, then celebrate or sulk
        if (!(tilt.lengthSq() < 0.36f) || stepState != 0)
            modeTimer = 0;
        if (modeTimer > 100) {
            int t = opp->modeTimer;
            if ((t > 100 || (t < -10 && t > -200)) && opp->mode != 7) {
                modeTimer = 0;
                mode = 6;
            } else if (opp->mode == 6) {
                modeTimer = 0;
                mode = 6;
            }
        } else if (opp->mode == 6) {
            modeTimer = 0;
            mode = 6;
        }
        if (modeTimer > 700) {
            modeTimer = 0;
            mode = 7;
        }
        ++modeTimer;
        break;

    case 6: { // bow to the opponent
        int n = modeTimer;
        liftScale = (float)((1.0 - fp::cos(n * (1.0f / 140.0f) * 6.28318548f)) * 0.4f);
        spineBend = 1.5f * liftScale;
        bendBlend = liftScale * -1.0f;
        if (n > 140) {
            mode = 0;
            liftScale = 0.0f;
            spineBend = 0.0f;
        }
        modeTimer = n + 1;
        break;
    }

    case 7: { // stretching
        liftScale = (float)(fp::sin(modeTimer * (1.0f / 140.0f) * 12.566371f) * -0.5f);
        spineBend = 1.8f * liftScale;
        bendBlend = liftScale * -1.0f;
        if (modeTimer > 140) {
            mode = 5;
            liftScale = 0.0f;
            modeTimer = -500;
            spineBend = 0.0f;
        }
        ++modeTimer;
        break;
    }

    case 8: { // shaking off a defeat
        crouch = (float)((fp::cos(modeTimer * (1.0f / 75.0f) * 25.132742f) - 1.0f) * -0.15f);
        spineBend = -crouch;
        bendBlend = (crouch - 0.15f) * 2.0f;
        if (modeTimer > 75) {
            mode = 5;
            if (g_gameState == GAME_HIDDEN || g_editorMode)
                mode = 0;
            modeTimer = -200;
            spineBend = 0.0f;
            crouch = 0.0f;
        }
        ++modeTimer;
        break;
    }

    case 0:
        ++modeTimer;
        break;
    }

    // arm actions: 0 idle, 1 two handed push, 2 one handed push, 3 bow
    Vec3 points[6];               // [EBP-0x110]: arm targets at [side*3], foot positions at [2+leg]
    char again;                   // [EBP-0x2d]
    do {
        again = 0;
        if (armAction == 0) {
            if (input & 0x10) {
                armTimer = 0;
                armAction = 1;
            }
            if (input & 0x20) {
                Vec3 hands = body[11]->pos - body[14]->pos;
                armTimer = 0;
                armAction = 2;
                armSide = 1;
                if (side.y * hands.y + side.z * hands.z + side.x * hands.x < 0.0f)
                    armSide = 0;
                if (armCooldown > 0)
                    armCooldown = 1000;
            }
        } else if (armAction == 1) {
            float push = 0.14f;
            motor[8].strength = push;
            motor[9].strength = push;
            motor[11].strength = push;
            motor[12].strength = push;
            lean = 0.5f;
            float shift = -1.3f;                          // [EBP+0x4c]
            Vec3 dir = opp->body[1]->pos - body[1]->pos;
            dir.y = 0.0f;
            dir.normalize();
            int f = g_frame - 10;
            if (body[14]->lastContactFrame > f)
                shift = -2.0f;
            if (body[11]->lastContactFrame > f)
                shift = shift - 0.7f;
            Vec3 d = side * shift;
            com.x = com.x + d.x;
            com.y = com.y + d.y;
            com.z = com.z + d.z;
            int n = armTimer;
            float t = (n - 8) * (1.0f / 30.0f);
            if (n < 8)
                t = 0.0f;
            if (n > 38) {
                t = 1.0f;
                if (n > 43) {
                    armAction = 0;
                    armTimer = 0;
                }
            }
            float t2 = t * t;
            liftScale = t2 * 0.4f + liftScale;
            float bend = t * 0.3f + 0.7f;
            float raise = 2.7f * (1.0f - t2);
            float back = -4.0f;
            Vec3 offset = V3(0.0f, 2.0f - (1.0f - t2) * 4.0f, 0.0f);
            for (int k = 0; k < 2; ++k) {
                armBend[k * 3] = bend;
                armRaise[k * 3] = raise;
                armReach[k * 3] = 1.5f;
                points[k * 3] = (opp->body[1]->pos + offset) + tilt * back;
            }
            ++armTimer;
        } else if (armAction == 2) {
            int idx = armSide * 3;
            float push = 0.06f;
            motor[8].strength = push;
            motor[9].strength = push;
            motor[11].strength = push;
            motor[12].strength = push;
            float k = -0.7f;
            Vec3 d = side * k;
            com.x = com.x + d.x;
            com.y = com.y + d.y;
            com.z = com.z + d.z;
            int n = armTimer;
            float t = n * 0.05f;
            if (n > 20) {
                armAction = 0;
                armTimer = 0;
                armCooldown = 10;
                again = 1;
            }
            float t2 = t * t;
            Vec3 drop = V3(0.0f, -2.0f, 0.0f);
            float u = 1.0f - t;
            liftScale = u * t * 0.1f + liftScale;
            armBend[idx] = t * 0.3f + 0.7f;
            armRaise[idx] = (1.0f - t2) * 2.7f;
            armReach[idx] = 1.3f;
            Vec3 target = opp->body[2]->pos + drop;
            points[idx] = target;
            if (armCooldown > 200) {
                int other = 3 - idx;
                points[other] = target;
                armBend[other] = u * 0.3f + 0.7f;
                armRaise[other] = t2 * 2.7f;
                armReach[other] = 1.3f;
            }
            ++armTimer;
        }
    } while (again);
    --armCooldown;

    if (armAction != 3) {
        Vec3 shoulder = V3(3.5f, 2.4f, 1.0f);
        bowAxisA = body[1]->rot * (points[0] - (body[1]->pos + shoulder * body[1]->rot));
        if (bowAxisA.z < 0.0f)
            bowAxisA.z = 0.0f;
        bowAxisA.normalize();
        shoulder = V3(-3.5f, 2.4f, 1.0f);
        bowAxisB = body[1]->rot * (points[3] - (body[1]->pos + shoulder * body[1]->rot));
        if (bowAxisB.z < 0.0f)
            bowAxisB.z = 0.0f;
        bowAxisB.normalize();
    }

    {
        float k = 0.1f;
        Vec3 d = pushImpulse * k;
        avgVel.x = avgVel.x - d.x;
        avgVel.y = avgVel.y - d.y;
        avgVel.z = avgVel.z - d.z;
        pushImpulse.x = pushImpulse.x * 0.96f;
        pushImpulse.y = pushImpulse.y * 0.96f;
        pushImpulse.z = pushImpulse.z * 0.96f;
    }
    Vec3 marker = centerOfMassOf();                       // [EBP-0x64]
    marker.y = 5.0f;
    debugCross(marker, 0xff0000);

    // support point between the feet, weighted by weightShift
    float w = weightShift;                                // [EBP+0x38]
    Vec3 sole = V3(0.0f, 0.0f, -0.4f);
    Body *foot0 = joint[4]->a;
    points[2] = sole * foot0->rot + foot0->pos;
    Body *foot1 = joint[7]->a;
    points[3] = sole * foot1->rot + foot1->pos;
    float w1 = 1.0f - w;
    Vec3 toe = V3(0.0f, -1.0f, 0.02f);
    Vec3 support = ((toe * foot0->rot + foot0->pos) * w) + ((toe * foot1->rot + foot1->pos) * w1); // [EBP-0x48]
    marker = support;
    marker.y = 5.0f;
    debugCross(marker, 0xffff00);

    float stepSide = ((float)stepLeg - 0.5f) * 2.0f;      // [EBP+0x60]
    k24 = k24 - (side.y * pushImpulse.y + side.z * pushImpulse.z + side.x * pushImpulse.x) * 0.15f;
    turnRate = 0.0f;

    if (support.y + 9.3f > body[2]->pos.y) {
        // the head is low: fallen over
        if (stepState != 12 && stepState != 13 && stepState != 14 && stepState != 3) {
            stepState = 3;
            for (Sumo *s = g_sumos; s < g_sumoEnd; ++s) {
                if (s == this)
                    continue;
                if (!((s->body[6]->pos.y + s->body[3]->pos.y) * 0.5f + 3.0f < s->body[2]->pos.y)) {
                    if (!g_editorMode)
                        continue;
                    if (!(g_waterLevel - 1.0f > s->body[2]->pos.y))
                        continue;
                }
                if (g_gameState != GAME_OVER && !g_editorMode)
                    continue;
                if (s->mode != 5 && s->mode != 7 && !g_editorMode)
                    continue;
                if (!(s->tilt.lengthSq() < 1.96f))
                    continue;
                s->cheer(slot);
            }
        }
    }
    if (g_waterLevel + 1.5f > body[0]->pos.y)
        stepState = 14;   // drowning

    // stepping state machine
    switch (stepState) {
    case 0: { // standing: decide whether to take a step
        weightShift = 0.5f;
        if (g_keyDown[3])
            weightShift = 1.0f;
        foot[0].y = footHeight;
        foot[1].y = footHeight;
        ++stepTimer;
        float k = 19.0f;
        Vec3 d = support - (com + avgVel * k);            // [EBP+0x10]
        k = 3.0f;
        Vec3 p = pushImpulse * k;
        d.x = d.x - p.x;
        float dy = -p.y;
        d.z = d.z - p.z;
        if (g_frame > 250 || (g_editorMode && g_frame > 100)) {
            int f = g_frame - 30;
            if (body[3]->lastContactFrame > f || body[6]->lastContactFrame > f) {
                float reach = g_gameState == GAME_OVER ? 1.5f : 0.9f;
                if (reach * reach < dy * dy + d.x * d.x + d.z * d.z && !posing) {
                    // off balance: step towards the support point
                    k = 10.0f;
                    d = support - (com + avgVel * k);
                    float dd = d.x * d.x + d.z * d.z;
                    float len = (float)(fp::sqrt(dd) * 1.5f);   // [EBP+0x4c]
                    if (len < 1.4f)
                        len = 1.4f;
                    stepTimer = 0;
                    stepState = 8;
                    float s = (float)fp::sqrt(dd);
                    double s2 = fp::sqrt(dd);
                    float fx = forward.x * d.x;
                    float fy = forward.y * 0.0f;
                    float fz = forward.z * d.z;
                    float z = (d.x * side.x + d.z * side.z + side.y * 0.0f) * -(len / s);
                    float x = (float)((fy + fz + fx) * (len / s2 * -0.6f));
                    stepVector = V3(x, 0.0f, z);
                    stepLift = (float)(fp::sqrt(stepVector.lengthSq()) * 0.8f + 0.5f);
                    Vec3 q = foot[1] - foot[0];
                    if (((float)stepLeg - 0.5f) * 0.0f + fy + fz + fx >
                        q.z * stepVector.z + q.y * stepVector.y + stepVector.x * q.x)
                        stepLeg = 1;
                    else
                        stepLeg = 0;
                    if (stepLeg) {
                        if (foot[0].x - stepVector.x < 0.25f)
                            stepVector.x = foot[0].x - 0.25f;
                    } else {
                        if (foot[0].x + stepVector.x < 0.25f)
                            stepVector.x = 0.25f - foot[0].x;
                    }
                    float v = (foot[0].x - 0.5f) * 0.2f - 0.16f;
                    if (stepLeg)
                        stepVector.x = v + stepVector.x;
                    else
                        stepVector.x = stepVector.x - v;
                }
                // bring the feet back together after a while
                int t = stepTimer;
                if (t == 90 || (t > 10 && foot[0].x < 0.25f) || stepNow) {
                    Vec3 rest = V3(1.1f, footHeight, 0.0f);
                    stepVector = rest - foot[0];
                    if (stepVector.lengthSq() > 0.16f || stepNow) {
                        stepLeg = 0;
                        stepState = 8;
                        stepLift = (float)(fp::sqrt(stepVector.lengthSq()) * 0.3f + 0.5f);
                        if (stepVector.z < 0.1f) {
                            stepLeg = 1;
                            stepVector.x = stepVector.x * -1.0f;
                            stepVector.y = stepVector.y * -1.0f;
                            stepVector.z = stepVector.z * -1.0f;
                        }
                    }
                }
                lean = 1.0f;
                break;
            }
        }
        lean = 1.0f;
        break;
    }

    case 2: { // shifting the weight onto the standing leg
        float l = (float)stepLeg;
        if (l > weightShift)
            weightShift = weightShift + 0.01f;
        if (l < weightShift)
            weightShift = weightShift - 0.01f;
        float k = 30.0f;
        Vec3 d = support - (com + avgVel * k);
        d.y = 0.0f;
        int t = --stepTimer;
        if (weightShift < 0.1f || weightShift > 0.9f) {
            bool go;
            if (d.x * d.x + d.z * d.z < 1.69f) {
                go = true;
            } else {
                Vec3 q = body[0]->rot * d;
                go = q.z < -0.2f;
            }
            if (go) {
                if (t <= 0) {
                    stepState = 1;
                    stepTimer = 0;
                }
            } else {
                stepTimer = 0;
            }
        }
        Vec3 drift = V3(0.0f, 0.0f, 0.01f) * body[0]->rot;
        drift.y = 0.0f;
        float rate = 0.06f;
        stepOrigin += (drift - stepOrigin) * rate;
        avgVel.x = avgVel.x - stepOrigin.x;
        avgVel.y = avgVel.y - stepOrigin.y;
        avgVel.z = avgVel.z - stepOrigin.z;
        break;
    }

    case 1: { // shuffling: lift one foot after the other
        float a = stepTimer * 0.0923997834f;              // [EBP+0x6c]
        if (a > 3.14159274f) {
            stepLeg ^= 1;
            stepTimer = 0;
            stepState = 2;
        }
        float sgn;
        if (stepLeg == 0) {
            sgn = 1.0f;
            weightShift = stepTimer * 0.0176470596f;
        } else {
            sgn = -1.0f;
            weightShift = 1.0f - stepTimer * 0.0176470596f;
        }
        float c = 0.03f;
        Vec3 drift = V3(sgn * c, 0.0f, c) * body[0]->rot;
        drift.y = 0.0f;
        float rate = 0.06f;
        stepOrigin += (drift - stepOrigin) * rate;
        avgVel.x = avgVel.x - stepOrigin.x;
        avgVel.y = avgVel.y - stepOrigin.y;
        avgVel.z = avgVel.z - stepOrigin.z;
        foot[stepLeg].z = foot[stepLeg].z + 0.0588235296f;
        float a2 = a + a;
        foot[stepLeg].y = (float)((1.0f - fp::cos(a2)) * 1.1f - 8.5f);
        foot[stepLeg ^ 1].y = (float)(-8.5f - (1.0f - fp::cos(a2)) * 0.3f);
        foot[stepLeg ^ 1].z = foot[stepLeg ^ 1].z - 0.0588235296f;
        ++stepTimer;
        break;
    }

    case 3: { // fallen: go limp until still, then get up
        Vec3 zero = V3(0.0f, 0.0f, 0.0f);
        momentum = zero;
        for (int i = 0; i < 14; ++i) {
            motor[i].strength = 0.0f;
            motor[i].refA = zero;
            motor[i].refB = momentum;
        }
        if (stepTimer >= 8000 || kineticEnergy() < 2.0f) {
            stepTimer = 0;
            stepState = 12;
        }
        int f = g_frame - 100;
        if (body[1]->lastHeavyContactFrame < f && body[2]->lastHeavyContactFrame < f) {
            float h = support.y + 3.0f;
            for (int k = 0; k < 2; ++k) {
                if (body[11 + 3 * k]->pos.y < h) {
                    motor[8 + 3 * k].strength = 0.01f;
                    motor[9 + 3 * k].strength = 0.01f;
                    motor[8 + 3 * k].refA = body[1]->rot * V3(0.0f, 1.0f, 0.0f);
                    motor[9 + 3 * k].refA = restMotor[9 + 3 * k].refA;
                }
            }
        }
        ++stepTimer;
        return;
    }

    case 4: // crouch before a jump step
        ++stepTimer;
        crouch = stepTimer * 0.04f;
        if (crouch > 1.2f) {
            stepTimer = 0;
            stepState = 5;
        }
        {
            Vec3 d = V3(stepSide * 0.2f, 0.0f, 0.0f) * body[0]->rot;
            avgVel.x = avgVel.x - d.x;
            avgVel.z = avgVel.z - d.z;
        }
        break;

    case 5: {
        Vec3 d = V3(stepSide * 0.2f, 0.0f, 0.0f) * body[0]->rot;
        ++stepTimer;
        crouch = 1.2f;
        avgVel.x = avgVel.x - d.x;
        avgVel.z = avgVel.z - d.z;
        if (stepTimer > 10) {
            stepTimer = 0;
            stepState = 6;
        }
        break;
    }

    case 6: {
        ++stepTimer;
        float t = (float)stepTimer;
        crouch = 1.2f - t * t * 0.0202799998f;
        foot[stepLeg].y = -8.0f;
        if (crouch < 0.0f) {
            stepState = 0;
            stepTimer = 0;
            foot[stepLeg].y = -8.7f;
        }
        {
            Vec3 d = V3(stepSide * 0.2f, 0.0f, 0.0f) * body[0]->rot;
            avgVel.x = avgVel.x - d.x;
            avgVel.z = avgVel.z - d.z;
        }
        break;
    }

    case 7: { // stamping
        if (stepTimer < 120)
            ++stepTimer;
        else
            stepTimer = 0;
        Vec3 d = V3(0.05f, 0.0f, 0.0f) * body[0]->rot;
        avgVel.x = avgVel.x - d.x;
        avgVel.z = avgVel.z - d.z;
        foot[stepLeg].y = (float)(fp::sin(stepTimer * 0.0261799395f) - 8.7f);
        break;
    }

    case 8: { // step: lift-off
        float rate = 0.05f;
        foot[stepLeg].y = footHeight - stepTimer * rate;
        ++stepTimer;
        if (stepTimer >= 6) {
            stepTimer = 0;
            stepState = 9;
        }
        float zero = 0.0f;
        foot[stepLeg] += (stepVector * rate) * zero;
        foot[stepLeg ^ 1] -= (stepVector * rate) * zero;
        float k = stepTimer * 0.049999997f;
        Vec3 s = (side * stepVector.z) * k;
        support.x = support.x - s.x;
        support.y = support.y - s.y;
        support.z = support.z - s.z;
        k = -0.025f;
        Vec3 v = (side * stepVector.z) * k;
        avgVel.x = avgVel.x + v.x;
        avgVel.y = avgVel.y + v.y;
        avgVel.z = avgVel.z + v.z;
        if (g_gameState == GAME_RUNNING)
            lean = 1.0f;
        break;
    }

    case 9: { // step: swing
        float t = stepTimer * 0.05f;
        float speed = (1.0f - t) * t * 6.0f;              // [EBP+0x68]
        float h = t * t * 3.0f - t * t * t * 2.0f;        // [EBP+0x4c]
        float hp = h * 3.14159274f;                       // [EBP+0x64]
        foot[stepLeg].y = (float)(fp::sin(hp) * stepLift + footHeight - 0.3f + hp * 0.0954929665f);
        foot[stepLeg ^ 1].y = (float)(footHeight - fp::sin(hp) * stepLift * 0.2f);
        float one = 1.0f;
        float rate = 0.05f;
        foot[stepLeg] += ((stepVector * rate) * one) * speed;
        foot[stepLeg ^ 1] -= ((stepVector * rate) * one) * speed;
        ++stepTimer;
        if (stepTimer >= 20) {
            stepLeg ^= 1;
            stepState = 0;
            stepTimer = 0;
            foot[stepLeg].y = footHeight;
            foot[stepLeg ^ 1].y = footHeight;
        }
        float k = (stepTimer + 6.0f) * 0.0384615399f - h;
        float k2 = 1.3f;
        Vec3 s = ((side * stepVector.z) * k) * k2;
        support.x = support.x - s.x;
        support.y = support.y - s.y;
        support.z = support.z - s.z;
        k2 = -0.025f;
        Vec3 v = (side * stepVector.z) * k2;
        avgVel.x = avgVel.x + v.x;
        avgVel.y = avgVel.y + v.y;
        avgVel.z = avgVel.z + v.z;
        lean = 0.0f;
        break;
    }

    case 10: { // jump: up
        weightShift = 0.5f;
        float p = stepTimer * (1.0f / 30.0f);             // [EBP+0x64]
        float q = p * 3.14159274f;                        // [EBP+0x68]
        float back = -0.05f;
        double sq = fp::sin(q);
        foot[stepLeg].y = (float)(sq + sq + footHeight + p);
        foot[stepLeg].x = foot[stepLeg].x + 0.11f;
        foot[stepLeg ^ 1].x = foot[stepLeg ^ 1].x - 0.11f;
        float s = (float)fp::sin(q);
        Vec3 v = (forward * s) * back;
        avgVel.x = avgVel.x + v.x;
        avgVel.y = avgVel.y + v.y;
        avgVel.z = avgVel.z + v.z;
        ++stepTimer;
        if (p > 1.0f) {
            stepTimer = 0;
            stepState = 11;
        }
        break;
    }

    case 11: { // jump: down
        weightShift = 0.5f;
        float f = stepTimer * 0.1f;
        foot[stepLeg].y = 1.0f - f + footHeight;
        foot[stepLeg].x = foot[stepLeg].x - 0.33f;
        foot[stepLeg ^ 1].x = foot[stepLeg ^ 1].x + 0.33f;
        if (f > 1.0f)
            stepState = 0;
        ++stepTimer;
        break;
    }

    case 12: { // getting up from the floor
        pushImpulse = V3(0.0f, 0.0f, 0.0f);
        float strength = stepTimer * 0.00025f;
        if (strength > 0.05f)
            strength = 0.05f;
        for (int i = 0; i < 14; ++i) {
            motor[i] = restMotor[i];
            motor[i].strength = strength;
        }
        int n = stepTimer;
        float shoulderBend = n * 0.018f - 0.5f;           // [EBP+0x1c]
        if (shoulderBend < 0.0f)
            shoulderBend = 0.0f;
        if (shoulderBend > 2.0f)
            shoulderBend = 2.0f;
        if (n == 100) {
            Vec3 probe = V3(0.0f, 0.0f, 1.0f) * body[0]->rot;
            if (probe.y > 0.0f) {
                fallSide ^= 1;
                stepTimer = 0;
                fallTwist = 0.0f;
                stepState = 13;
            }
        }
        float elbowTwist = 1.0f;                          // [EBP+0x64]
        posing = 0;
        float push = 0.0f;                                // [EBP+0x70]
        float bend = 0.0f;                                // [EBP+0x20]
        float twist = 0.0f;                               // [EBP+0x4c]
        n = stepTimer;
        if (n > 100) {
            Vec3 a = V3(1.0f, 0.0f, 0.0f);
            Vec3 b = V3(1.0f, 0.0f, 0.0f);
            Vec3 ra = b * body[0]->rot;
            Vec3 rb = a * body[0]->rot;
            if (ra.y * rb.y > 0.25f && n > 300)
                posing = 1;
            float u = (n - 100.0f) * 0.01f;
            if (u > 1.0f)
                u = 1.0f;
            float h = (u * u * 3.0f - u * u * u * 2.0f) * 2.5f;
            twist = h;
            bend = h;
            if (n > 170) {
                float v = (n - 170.0f) * 0.00666666683f;
                if (v > 1.0f)
                    v = 1.0f;
                double h2 = (double)v * v * 3.0f - (double)v * v * v * 2.0;
                shoulderBend = (float)(2.0f - 1.8f * h2);
                elbowTwist = (float)(1.0f - h2 * 2.5f);
                if (n > 300) {
                    float w = (n - 300) * 0.01f;
                    if (w > 1.0f)
                        w = 1.0f;
                    float k = 20.0f;
                    Vec3 ahead = (com + avgVel * k) - support;
                    float drift = side.y * ahead.y + side.z * ahead.z + side.x * ahead.x;   // [EBP-4]
                    double e = fp::exp(w * -2.0f);
                    twist = fallTwist;
                    float angle = (float)(fallAngle - (1.0 - e) * fallAngle * 0.02f);
                    fallAngle = angle;
                    bend = angle;
                    if (n > 10000) {
                        float z = (n - 20000.0f) * 0.00666666683f;
                        if (z > 1.0f)
                            z = 1.0f;
                        int f = g_frame - 300;
                        double h3 = (double)z * z * 3.0f - (double)z * z * z * 2.0;
                        shoulderBend = (float)(0.6f * h3 + shoulderBend);
                        elbowTwist = (float)(2.7f * h3 + elbowTwist);
                        push = (float)(h3 * 2.5f);
                        if (body[3]->lastHeavyContactFrame < f || body[6]->lastHeavyContactFrame < f)
                            posing = 1;
                        float next = (drift - fallRate) * 0.1f + drift * 0.002f - (0.2f - angle) * 0.01f + angle;
                        fallAngle = next;
                        if (next < 0.1f)
                            posing = 1;
                        if (fallTwist > 0.22f) {
                            float y = (float)((fallTwist - 0.05f) * (1.0f / (drift * drift * 3.0f + 1.0f)) * z * z * 0.35f);
                            if (y > 0.05f)
                                y = 0.05f;
                            fallTwist = fallTwist - y;
                        } else {
                            posing = 1;
                        }
                        if (2.5f < fallTwist)
                            fallTwist = 2.5f;
                        bend = next;
                        twist = fallTwist;
                    }

                    // lean the upper arms towards the support point
                    k = 20.0f;
                    Vec3 predicted = com + avgVel * k;
                    Vec3 down = V3(0.0f, -5.0f, 0.0f);
                    float sideways = -0.1f;
                    Vec3 dir = ((support - predicted) + down) + side * sideways;
                    dir.normalize();
                    if (dir.y < -fp::cos(0.10000000149011612) && stepTimer < 20000)
                        stepTimer = 20000;
                    if (dir.y > -fp::cos(0.30000001192092896)) {
                        float t = (float)fp::tan(0.30000001192092896);
                        dir.y = (float)(fp::sqrt(1.0f - dir.y * dir.y) * (-1.0f / t));
                        dir.normalize();
                        if (stepTimer > 600)
                            posing = 1;
                    }
                    for (int k2 = 0; k2 < 2; ++k2) {
                        Vec3 v2 = joint[4 + 3 * k2]->b->rot * dir;
                        if (v2.y > -fp::cos(0.5)) {
                            float t = (float)fp::tan(0.5);
                            v2.y = (float)(fp::sqrt(1.0f - v2.y * v2.y) * (-1.0f / t));
                            v2.normalize();
                        }
                        motor[4 + 3 * k2].refA = v2;
                    }
                    fallRate = drift;
                } else {
                    fallAngle = bend;
                    fallTwist = twist;
                }
            }
            if (posing) {
                // standing again
                fallBlend = 0.0f;
                stepState = 0;
                foot[0] = V3(0.3f, footHeight, 0.0f);
                foot[1] = V3(-0.3f, footHeight, 0.0f);
                if (support.y + 10.0f > body[2]->pos.y)
                    stepState = 3;
                stepTimer = 0;
                leanX = 0.0f;
                weightShift = 0.5f;
                leanZ = 0.0f;
                leanXBias = 0.0f;
                leanXVel = 0.0f;
                leanZBias = 0.0f;
            }
        }

        // arms push the body up
        float sgn = 1.0f;                                 // [EBP-4]
        Vec3 xAxis = V3(1.0f, 0.0f, 0.0f);                // [EBP-0x88]
        float negBend = -bend;                            // [EBP+0x68]
        Vec3 xAxis2 = V3(1.0f, 0.0f, 0.0f);               // [EBP-0x2c]
        for (int k = 0; k < 2; ++k) {
            float m = sgn * -1.0f;
            Vec3 w = V3(0.0f, m, 0.0f);
            motor[8 + 3 * k].refA.rotate(w * elbowTwist);
            Vec3 zAxis = V3(0.0f, 0.0f, sgn);
            motor[8 + 3 * k].refA.rotate(zAxis * push);
            Vec3 yAxis = V3(0.0f, m, 0.0f);
            motor[9 + 3 * k].refA.rotate(yAxis * shoulderBend);
            Vec3 lift = V3(0.0f, sgn * -0.3f, 0.0f);
            motor[2 + 3 * k].refA.rotate(xAxis * twist + lift);
            motor[3 + 3 * k].refA.rotate(xAxis2 * negBend);
            sgn = -1.0f;
        }
        ++stepTimer;
        break;
    }

    case 13: { // lying on the back: roll over
        float strength = stepTimer * 0.00025f;
        if (strength > 0.05f)
            strength = 0.05f;
        for (int i = 0; i < 14; ++i) {
            motor[i] = restMotor[i];
            motor[i].strength = strength;
        }
        Vec3 up = V3(0.0f, 0.0f, 1.0f) * body[0]->rot;
        if (up.x * up.x + up.z * up.z > 0.36f)
            fallTwist = fallTwist + 0.04f;
        else if (fallTwist > 0.0f)
            fallTwist = fallTwist - 0.08f;
        if (fallTwist > 4.6f || stepTimer > 600) {
            stepTimer = 0;
            stepState = 3;
        }
        int other = 3;                                    // [EBP+0x70]
        float rest = 1.0f - fallTwist;                    // [EBP+0x68]
        float swing = fallTwist * 0.3f + 1.0f;            // [EBP+0x48]
        float dirSign = 1.0f;                             // [EBP+0x1c]
        int arm = 0;
        if (fallSide == 0) {
            other = 0;
            arm = 3;
            dirSign = -1.0f;
        }
        Vec3 axis = V3(0.0f, dirSign * -1.0f, 0.0f);
        float neg = -1.0f;
        motor[8 + arm].refA.rotate((axis * neg) * swing);
        Vec3 add2 = V3(dirSign * fallTwist * -0.2f, (float)(fallTwist * 0.5), 0.0f);
        motor[8 + arm].refA += add2;
        motor[8 + arm].refA.normalize();
        axis = V3(0.0f, dirSign, 0.0f);
        swing = 1.1f;
        motor[8 + other].refA.rotate((axis * swing) * rest);
        Vec3 legTurn = V3((float)(0.9 - fallTwist), (float)(dirSign * fallTwist * 1.5), (float)(dirSign * -1.2));
        motor[2 + arm].refA.rotate(legTurn);
        Vec3 bendAxis = V3(-0.3f, 0.0f, 0.0f);
        motor[2 + other].refA.rotate(bendAxis * rest);
        if (stepTimer > 100 && kineticEnergy() < 0.5f)
            stepTimer = stepTimer + 10;
        ++stepTimer;
        break;
    }

    case 14: { // drowning: paddle
        for (int i = 0; i < 14; ++i) {
            motor[i] = restMotor[i];
            motor[i].strength = 0.005f;
        }
        fallTwist = fallTwist - body[2]->rot.m[7] * 0.05f;
        float tilt7 = body[2]->rot.m[7];                  // [EBP+0x4c]
        float hip = 0.0f;                                 // [EBP+0x68]
        float knee = 0.0f;                                // [EBP-4]
        float neck = 0.0f;                                // [EBP+0x20]
        if (!(fp::fabs(tilt7) < 0.3f)) {
            float r = (float)(tilt7 - tilt7 / fp::sqrt(tilt7 * tilt7) * 0.3f);
            if (r < 0.0f) {
                knee = -1.5f * r;
                hip = 0.4f * r;
                neck = 0.6f * r;
            }
            if (r > 0.0f) {
                knee = 0.0f;
                hip = 1.5f * r;
                neck = r * 0.3f;
            }
        }
        float sgn = 1.0f;                                 // [EBP+0x60]
        Vec3 xAxis = V3(1.0f, 0.0f, 0.0f);                // [EBP-0x88]
        Vec3 xAxis2 = V3(1.0f, 0.0f, 0.0f);               // [EBP-0x94]
        for (int k = 0; k < 2; ++k) {
            Vec3 lift = V3(0.0f, sgn * -0.3f, 0.0f);
            float a = (float)(fp::sin(fallTwist) * sgn * 0.3 + hip);
            motor[2 + 3 * k].refA.rotate(xAxis * a + lift);
            a = (float)(fp::sin(fallTwist) * sgn * 0.3 - knee);
            motor[3 + 3 * k].refA.rotate(xAxis2 * a);
            sgn = -1.0f;
        }
        float c = (float)fp::cos(neck);
        motor[1].refA = V3(0.0f, c * -1.0f, (float)fp::sin(neck));
        motor[1].refA.normalize();
        motor[1].strength = 0.0008f;
        sgn = 1.0f;
        for (int k3 = 0; k3 <= 3; k3 += 3) {
            armRaise[k3] = 0.0f;
            float ft = fallTwist;
            float cf = (float)fp::cos(ft);
            Vec3 &hand = motor[8 + k3].refA;
            hand = V3(sgn * 0.4f, -(sgn * cf), (float)(0.5f - fp::sin(ft) * sgn));
            hand.normalize();
            hand.normalize();
            motor[10 + k3].refA = V3(sgn, 0.0f, 0.0f);
            motor[10 + k3].refA.normalize();
            sgn = -1.0f;
        }
        ++stepTimer;
        break;
    }
    }

    if (stepState == 12 || stepState == 13 || stepState == 14)
        return;

    // turn towards the opponent
    Vec3 toOpp = opp->body[0]->pos - body[0]->pos;      // [EBP+0x10]
    if (foot[0].z * foot[0].z > 6.25f)
        lean = 0.0f;
    turnRate = (float)(1.0 / fp::sqrt(toOpp.x * toOpp.x + toOpp.z * toOpp.z + toOpp.y * toOpp.y) *
                       (toOpp.y * forward.y + toOpp.x * forward.x + toOpp.z * forward.z) * -0.1f);
    {
        float tr = turnRate;
        if (tr * tr > 0.0016f)
            turnRate = (float)(turnRate / fp::fabs(tr) * 0.04f);
    }
    if (!(turnRate < 100.0f) && !(turnRate > 100.0f))
        turnRate = 0.0f;   // NaN guard
    turnRate = turnCmd + turnRate;
    if (controller != 2 || mode == 4 || mode == 1 || mode == 2)
        turnRate = turnCmd;
    turnRate = lean * turnRate;
    float angle = turnRate;                               // [EBP+0x7c]

    // rotate the foot targets about the vertical axis
    points[2] = foot[0];
    points[3] = foot[1];
    {
        float s = (float)fp::sin(angle);
        float x = (float)(fp::cos(angle) * foot[0].x + s * foot[0].z);   // [EBP+0x68]
        s = (float)fp::sin(angle);
        double c = fp::cos(angle);
        float oldX = foot[0].x;
        foot[0].x = x;
        foot[0].z = (float)(c * foot[0].z - s * oldX);
        foot[1].x = -x;
        foot[1].z = -foot[0].z;
        if (x < 0.2f) {
            foot[0] = points[2];
            foot[1] = points[3];
        }
    }

    float crouchLean = crouch * 0.1f;                     // [EBP+0x7c]
    k24 = crouchLean + k24;
    Vec3 supportCopy = support;                           // [EBP-0x7c]
    marker = support;
    marker.y = 5.0f;
    debugCross(marker, 0xff00);
    float k = 20.0f;
    Vec3 ahead = com + avgVel * k;                        // [EBP]
    Vec3 offset = ahead - support;                        // [EBP+0x2c]
    offset.y = 0.0f;
    tilt = offset;
    fallBlend = (1.0f - fallBlend) * 0.01f + fallBlend;
    float blend = fallBlend;                              // [EBP+0x28]

    // balance: lean forward/backward
    k = 15.0f;
    Vec3 c15 = (com + avgVel * k) - supportCopy;
    double lx = (double)((leanXVel * 10.0f + leanX) * 0.1f + side.y * c15.y + side.z * c15.z + side.x * c15.x) * 0.04f +
                (double)(momentum.y * forward.y + momentum.x * forward.x + momentum.z * forward.z) * 3.99999990e-05f -
                leanXBias;
    float sq = (float)(lx * lx);
    if (sq > 0.09f)
        lx = fp::sqrt(sq) * 0.3f;
    lx = lx * blend;
    leanXVel = (float)((lx - leanXVel) * 0.01f + leanXVel);
    leanX = (float)((lx + crouchLean + leanX) * 0.8f);
    leanXBias = (leanX - k24 - leanXBias) * 0.004f + leanXBias;

    // balance: lean sideways
    Vec3 d2 = com - supportCopy;
    double lz = ((double)(forward.z * d2.z + forward.y * d2.y + forward.x * d2.x) +
                 (double)(forward.x * avgVel.x + avgVel.y * forward.y + forward.z * avgVel.z) * 20.0f) * 0.002f +
                (double)(momentum.y * side.y + momentum.z * side.z + momentum.x * side.x) * 2.99999992e-05f;
    float sq2 = (float)(lz * lz);
    if (sq2 > 0.09f)
        lz = fp::sqrt(sq2) * 0.3f;
    lz = lz * blend;
    k24 = 0.0f;
    leanZ = (float)((lz + leanZ) * 0.94f + (w - 0.5f) * 0.0047f + turnRate * 0.376f);

    // legs: hip orientation and knee bend from the foot targets
    float sgn = 1.0f;                                     // [EBP+0x60]
    float drop = crouch + crouch;                         // [EBP+0x64]
    Vec3 xAxis = V3(1.0f, 0.0f, 0.0f);                    // [EBP-0x88]
    Vec3 zAxis = V3(0.0f, 0.0f, 1.0f);                    // [EBP-0x94]
    Vec3 kneeAxis = V3(sgn, 0.0f, -0.1f);                 // [EBP-0xa0]
    Vec3 yAxis = V3(0.0f, 1.0f, 0.0f);                    // [EBP-0xac]
    for (int k3 = 0; k3 <= 3; k3 += 3) {
        JointMotor *hip = &motor[2 + k3];
        float lxv = leanX;
        float cx = (float)fp::cos(lxv);
        float cz = (float)fp::cos(leanZ);
        float sz = (float)fp::sin(leanZ);
        hip->refA = V3(sgn * 0.04f + sz, -(cz * cx), (float)fp::sin(lxv));

        Vec3 *target = &foot[k3 / 3];
        Vec3 f = *target;
        Vec3 flat = V3(f.x, 0.0f, f.z);
        Vec3 col = body[0]->rot.column1();
        float y = (f.z * col.z + f.x * col.x) * 0.7f + sgn * leanZ * 0.5f + col.y * 0.0f - drop +
                  (flat.x * flat.x + flat.z * flat.z + flat.y * flat.y) * 0.0f;
        Vec3 raise = V3(0.0f, y, 0.0f);
        Vec3 leg = -*target + raise;                      // [EBP+0x10]
        if (k3 != 0) {
            float t = g_legTweak;
            leg.z = leg.z - t;
            leg.y = leg.y - t;
        }
        float len = (float)fp::sqrt(leg.y * leg.y + leg.z * leg.z + leg.x * leg.x);
        float a = liftScale + leanX;
        float ca = (float)fp::cos(a);
        leg.rotate(xAxis, ca, (float)fp::sin(a));
        float cz2 = (float)fp::cos(leanZ);
        leg.rotate(zAxis, cz2, (float)-fp::sin(leanZ));
        hip->refA = -leg;
        hip->refA.normalize();

        float c1 = lawOfCosines(upperLegLength, lowerLegLength, len);
        motor[3 + k3].refA = V3(0.0f, -c1, (float)-fp::sqrt(1.0f - c1 * c1));
        motor[3 + k3].refA.normalize();
        float c2 = lawOfCosines(upperLegLength, len, lowerLegLength);
        kneeAxis.x = sgn;
        hip->refB = kneeAxis;
        hip->refB.normalize();
        hip->refA.rotate(hip->refB * sgn, -c2, (float)fp::sqrt(1.0f - c2 * c2));
        hip->refA.normalize();

        // feet stay level, pointing at the support point
        Vec3 dir = (support - ahead) + yAxis;             // [EBP-0x70]
        dir.normalize();
        if (dir.y > -fp::cos(0.30000001192092896)) {
            float t = (float)fp::tan(0.30000001192092896);
            dir.y = (float)(fp::sqrt(1.0f - dir.y * dir.y) * (-1.0f / t));
            dir.normalize();
        }
        momentum = dir;
        motor[4 + k3].refA = joint[4 + k3]->b->rot * dir;
        sgn = -1.0f;
    }

    // spine and neck
    Vec3 between = foot[1] - foot[0];
    float twist = between.z;                              // [EBP+0x28]
    if (twist * twist > 16.0f)
        twist = twist < 0.0f ? -4.0f : 4.0f;
    {
        float a = leanX * 0.25f;
        float ca = (float)fp::cos(a);
        float cz = (float)fp::cos(leanZ * 0.25f);
        float sz = (float)fp::sin(leanZ * 0.25f);
        motor[0].refA = V3(sz, cz * ca * -1.0f, (float)fp::sin(a));
        motor[0].refA.normalize();
        motor[0].refB = V3(40.0f, 0.0f, -twist);
        motor[0].refB.normalize();
        a = leanX * 0.25f - liftScale * 0.9f - bendBlend;
        ca = (float)fp::cos(a);
        cz = (float)fp::cos(leanZ * 0.25f);
        sz = (float)fp::sin(leanZ * 0.25f);
        motor[1].refA = V3(sz, cz * ca * -1.0f, (float)fp::sin(a));
        motor[1].refA.normalize();
    }
    bodyLift = crouch;

    // arms
    sgn = 1.0f;
    Vec3 *bowAxis = &bowAxisA;
    float lift2 = liftScale + liftScale;                  // [EBP+0x48]
    float crouch4 = crouch * 0.4f;                        // [EBP+0x64]
    for (int s3 = 0; s3 <= 3; s3 += 3) {
        JointMotor *upper = &motor[8 + s3];
        float t = (leanX - 0.08f) * 3.0f + spineBend - lift2 - crouch4;
        float ct = (float)fp::cos(t);
        float sz4 = (float)fp::sin(leanZ * 4.0f);
        float tw = twist * sgn;                           // [EBP+0x6c]
        float tw5 = tw * 0.05f;
        upper->refA = V3(sgn * 0.3f, -ct - sz4 * sgn, (float)(tw5 - fp::sin(t)));
        upper->refA.normalize();

        Vec3 aim = *bowAxis;                              // [EBP]
        float r = sgn * armRaise[s3] * -0.75f;
        aim.rotate(upper->refB * r);
        float m = 1.0f - armBend[s3];
        upper->refA = upper->refA * m + aim * armBend[s3];
        upper->refA.normalize();

        float q = 0.66f - tw * 0.2f;
        if (q > 1.66f)
            q = 1.66f;
        float raise = armRaise[s3];
        float cr = (float)fp::cos(raise);
        float sr = (float)fp::sin(raise);
        float cr2 = (float)fp::cos(raise);
        double sr2 = fp::sin(raise);
        float y = (cr * 1.66f - sr) * armBend[s3] + m * q;
        float x = (float)(((sr2 * 1.66f + cr2) * armBend[s3] + m) * sgn);
        motor[9 + s3].refA = V3(x, 0.0f, y);
        motor[9 + s3].refA.normalize();

        motor[10 + s3].refA = V3(sgn, 0.0f, 0.0f);
        float reach = armReach[s3];
        float crch = (float)fp::cos(reach);
        Vec3 wrist = V3(crch * sgn, (float)-fp::sin(reach), 0.0f);
        motor[10 + s3].refA = motor[10 + s3].refA * m + wrist * armBend[s3];
        motor[10 + s3].refA.normalize();

        bowAxis = &bowAxisB;
        sgn = -1.0f;
    }

    if ((mode == 0 || mode == 5) && (input & 8)) {
        for (int i = 0; i < 8; ++i)
            motor[i].strength = 0.0f;
    }
}

// @ 0x410342
// Throws a box from `from` so that it reaches `to` after `time` steps (the
// mouse click "punishment" of the hidden part / menu).
void throwBox(Vec3 from, Vec3 to, float time, int material)
{
    Body *b = createBox(V3(1.2f, -1.2f, 1.2f), from, material, 0.125f);
    b->scaleMass(3.0f);
    float inv = 1.0f / time;
    b->vel = (to - b->pos) * inv;
    b->sound = 6;
    b->soundVolume = 0.01f;
    b->vel.y = b->vel.y - g_gravity * time * 0.5f;
    float spin = 0.1f;
    b->angVel = V3(spin, spin, spin);
}

// @ 0x410527
// The default arena: floor, dohyo (ring) with tapered sides, straw bales
// around the ring and the 31 poles of the ring border.
void buildDojo(int material)
{
    memset(g_joints, 0, sizeof(g_joints));
    g_jointEnd = g_joints;
    g_sumoEnd = g_sumos;
    g_bodyEnd = g_bodies;

    Body *floor = createBox(V3(180.0f, -3.0f, 180.0f), V3(0.0f, -4.0f, 0.0f), 1, 0.03125f);
    floor->makeStatic();

    Body *ring = createBox(V3(31.0f, -3.0f, 31.0f), V3(0.0f, 2.0f, 0.0f), material, 0.0625f);
    for (int i = 0; i < 8; ++i) {
        Vertex *v = &ring->vertBegin[i];
        if (v->pos.y < 0.0f)
            v->pos.z = v->pos.z * 1.15483868f;
    }
    ring->rebuildAfterCut(1);
    ring->init();
    ring->makeStatic();

    for (int side = 0; side < 4; ++side) {
        float a = side * 1.57079637f;
        for (int k = 0; k < 6; ++k) {
            float x = ((float)k - 2.5f) * 18.0f;
            Body *b = createBox(V3(8.0f, -4.0f, 0.5f), V3(x, 3.0f, 54.0f), material, 0.0625f);
            b->rot.rotate(V3(0.0f, a, 0.0f));
            b->pos.rotate(V3(0.0f, a, 0.0f));
            b->makeStatic();
            b->breakThreshold = 40.0f;
            b->density = 3.0f;
            b->sound = 2;
            b->soundVolume = 0.6f;
            if (g_gameState == GAME_MENU && side == 2 && k == 4 && g_menuPage == 0)
                b->tag = 6;   // "Hidden Part" bale
        }
    }

    for (int i = 0; i < 31; ++i) {
        Body *b = createBox(V3(2.6f, -0.2f, 0.45f), V3(0.0f, 5.0f, g_ringRadius), material, 0.125f);
        float a = i * 0.202683404f;
        b->rot.rotate(V3(0.0f, a, 0.0f));
        b->pos.rotate(V3(0.0f, a, 0.0f));
        b->rot.rotateX(-0.785398185f);
        b->makeStatic();
    }

    g_shadowLength = 40.0f;
    if (g_editorMode)
        g_shadowLength = 200.0f;
}

// @ 0x410885
// Places the wrestlers around the ring (or at the level's start points) and
// pairs them with opponents.
void spawnSumos()
{
    int count = g_playerCount;
    int humans = g_humanCount;
    if (g_resetScores) {
        g_scoreBlue = 0;
        g_scoreGrey = 0;
    }
    g_ranking[0] = -1;
    g_ranking[1] = -1;
    g_ranking[2] = -1;
    g_ranking[3] = -1;
    g_standingCount = count;
    replayRecordFrameMarker();
    g_frame = 0;

    Sumo *s = g_sumos;
    static const int kMaterials[4] = {2, 3, 1, 9};
    for (int i = 0; i < count; ++i) {
        Vec3 pos = V3(0.0f, 5.0f, -15.0f);
        float angle = (float)i / (float)count * 6.28318548f;
        pos.rotate(V3(0.0f, angle, 0.0f));

        int target;
        if (i < humans) {
            target = i + humans;
            if (target >= count)
                target = count - 1;
        } else {
            target = 0;
        }
        if (count == 4) {
            target = (i - 2) & 3;
            if (humans == 1 && i > 0)
                target = 0;
        }

        if (g_currentLevel != 0) {
            char skip = 0;
            if (i >= g_spawnCount) {
                skip = 1;
            } else {
                pos = g_spawnPos[i];
                angle = -g_spawnAngle[i];
            }
            target = target % g_spawnCount;
            if (target == i)
                target = (target + 1) % g_spawnCount;
            target = target % count;
            if (skip)
                continue;
        }

        s->create(&pos, -angle, kMaterials[i], &g_sumos[target]);
        s->mode = 4;
        if (g_gameState == GAME_HIDDEN)
            s->mode = 0;
        s->controller = i < humans ? i : 2;
        ++s;
    }
    g_sumoEnd = s;
    g_ticksPerSecond = 120;
}

static int g_unk511dfc;           // @ 0x511dfc written only

// @ 0x410a7e
void startMatch()
{
    showCursor(0);
    g_unk511dfc = 4;
    musicPlay(6);
    freeCameraResetAt(V3(40.0f, 35.0f, -100.0f), 0.0f);
    resetView();
    g_random.seed(1434, 6431);
    g_gameState = GAME_WAITING;
    if (g_playerCount == 1 && g_humanCount == 0) {
        g_gameState = GAME_HIDDEN;
        showCursor(1);
    }
    if (g_currentLevel == 0) {
        g_dojoFlag = 0;
        buildDojo(0);
    } else {
        startLevel(levelScript(g_currentLevel));
        if (g_playerCount == 1 && g_humanCount == 0)
            g_gameState = GAME_HIDDEN;
    }
    spawnSumos();
    rebuildJointLinks();
}

// @ 0x414edb
void sumoUpdateAll()
{
    for (Sumo *s = g_sumos; s < g_sumoEnd; ++s) {
        s->update(s->opponent);
        if (++g_licenseTicks == 1800 && !licenseIsValid())
            g_demoState = 2;
    }
}

// @ 0x40e188
void seedAiRandom()
{
    int t = (int)timeGetTime();
    g_aiRandom.seed(t & 0x3fff, ((t >> 8) + 1000) & 0x3fff);
}

// @ 0x40e1af
void gameInit()
{
    seedAiRandom();
    freeCameraReset();
    loadTextures();
    createSceneBuffers();
    allocScratchBodies();
    resetView();
    buildMenu();
}
