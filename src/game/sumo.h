// The sumo wrestler: 15 boxes connected by 14 joints, driven by a procedural
// stepping / balancing controller and a simple computer opponent.
//
// Bodies:  0 torso, 1 chest, 2 head, 3/6 feet, 4/7 shins, 5/8 thighs,
//          9/12 upper arms, 10/13 forearms, 11/14 hands (right side first).
// Joints:  0 waist, 1 neck, 2/5 hips, 3/6 knees, 4/7 ankles,
//          8/11 shoulders, 9/12 elbows, 10/13 wrists.
#pragma once

#include "../physics/body.h"
#include "../physics/world.h"
#include <cstddef>

// Per-joint motor (13 dwords).  The motor turns the joint so that the joint
// axis / reference vectors of body A, expressed in body B space, match
// targetAxis / targetRef.
struct JointMotor {
    Vec3 unused0;         // +0x00
    Vec3 unused1;         // +0x0c
    Vec3 refA;            // +0x18 target of joint.axisA (body B space)
    Vec3 refB;            // +0x24 target of joint.refA (body B space)
    float strength;       // +0x30 maximum angular impulse per step
};

// 0x730 bytes (0x1cc dwords) - field comments give the dword index.
struct Sumo {
    Body *body[15];              // [0x000]
    Joint *joint[14];            // [0x00f]
    float upperLegLength;        // [0x01d]
    float lowerLegLength;        // [0x01e]
    Vec3 foot[2];                // [0x01f] foot targets (pelvis space)
    int unk25;                   // [0x025]
    int unk26;                   // [0x026]
    int stepLeg;                 // [0x027] leg currently stepping
    int stepTimer;               // [0x028]
    int stepState;               // [0x029] see update()
    float stepLift;              // [0x02a]
    Vec3 stepOrigin;             // [0x02b] drift while shuffling
    float bodyLift;              // [0x02e]
    Vec3 stepVector;             // [0x02f]
    Vec3 centerOfMass;           // [0x032]
    float spineBend;             // [0x035]
    float leanX;                 // [0x036] forward / backward balance lean
    float leanXVel;              // [0x037]
    float leanXBias;             // [0x038]
    float leanZ;                 // [0x039] sideways balance lean
    float leanZBias;             // [0x03a]
    float weightShift;           // [0x03b] 0 = on the left foot, 1 = on the right
    float footHeight;            // [0x03c]
    int unk3d[3];                // [0x03d]
    Vec3 pushImpulse;            // [0x040] external push applied to the balance
    float fallAngle;             // [0x043]
    float fallTwist;             // [0x044]
    float fallRate;              // [0x045]
    int fallSide;                // [0x046]
    float fallBlend;             // [0x047]
    float turnRate;              // [0x048]
    Vec3 tilt;                   // [0x049] horizontal offset of the predicted centre of mass
    int armAction;               // [0x04c] 0 idle, 1 two handed push, 2 one handed push, 3 bow
    int armTimer;                // [0x04d]
    int armSide;                 // [0x04e]
    int armCooldown;             // [0x04f]
    int mode;                    // [0x050] 0 fight, 1 stand up, 2 bow, 3 rise, 4 settle, 5 match over,
                                 //         6 bow to opponent, 7 stretch, 8 cheer
    int modeTimer;               // [0x051]
    float modeBlend;             // [0x052]
    JointMotor motor[14];        // [0x053]
    JointMotor restMotor[14];    // [0x109] pose captured at creation
    int controller;              // [0x1bf] 0 / 1 = keyboard player, 2 = computer
    Sumo *opponent;              // [0x1c0]
    float turnInput;             // [0x1c1]
    int unk1c2;                  // [0x1c2]
    int unk1c3;                  // [0x1c3]
    int lost;                    // [0x1c4]
    int aiPressure;              // [0x1c5]
    int aiStartFrame;            // [0x1c6]
    int aiPauseFrame;            // [0x1c7]
    int unk1c8;                  // [0x1c8]
    int aiAggressive;            // [0x1c9]
    int aiWalkDelay;             // [0x1ca]
    int aiStandDelay;            // [0x1cb]

    void captureMotorTargets(JointMotor *motors) const;       // @ 0x40e73a (called on the motor array)
    Vec3 centerOfMassOf() const;                              // @ 0x40e7c8
    float kineticEnergy() const;                              // @ 0x40e896
    Vec3 averageVelocity() const;                             // @ 0x40e8f0
    Vec3 angularMomentum(const Vec3 &point, const Vec3 &velocity) const; // @ 0x40e98c
    void applyMotors(JointMotor *motors);                     // @ 0x40ea52
    void create(const Vec3 *pos, float angle, int material, Sumo *opp); // @ 0x40ec0d
    unsigned keyboardInput() const;                           // @ 0x40fe9b
    void cheer(int slot);                                     // @ 0x40ff13
    unsigned aiInput(Sumo *opp);                              // @ 0x40ff4c
    Sumo *findOpponent(const Vec3 &side, const Vec3 &forward); // @ 0x41041d
    void update(Sumo *opp);                                   // @ 0x410b60
};

static_assert(sizeof(JointMotor) == 0x34, "JointMotor layout");
#if !defined(_WIN64)
static_assert(sizeof(Sumo) == 0x730, "Sumo layout");
static_assert(offsetof(Sumo, stepState) == 0xa4, "Sumo layout");
static_assert(offsetof(Sumo, tilt) == 0x124, "Sumo layout");
static_assert(offsetof(Sumo, motor) == 0x14c, "Sumo layout");
static_assert(offsetof(Sumo, controller) == 0x6fc, "Sumo layout");
#endif

enum { MAX_SUMOS = 8 };

extern Sumo g_sumos[MAX_SUMOS];  // @ 0xc06b60
extern Sumo *g_sumoEnd;          // @ 0x453858
extern Random g_aiRandom;        // @ 0xc06988
extern int g_licenseTicks;       // @ 0xc0a4e4
extern float g_legTweak;         // @ 0xc0a4e0 never written (0)

Vec3 sumoCenterOfMass(Sumo *s);                                   // @ 0x40e7c8
void alignJointBody(Joint *j, int side);                          // @ 0x40e6b2
float lawOfCosines(float a, float b, float c);                    // @ 0x40fd6e
void debugCross(const Vec3 &pos, unsigned color);                 // @ 0x40fdd0
void sumoApplyMotors();                                           // @ 0x40fd42
void throwBox(Vec3 from, Vec3 to, float time, int material);      // @ 0x410342
void buildDojo(int material);                                     // @ 0x410527
void spawnSumos();                                                // @ 0x410885
void startMatch();                                                // @ 0x410a7e
void sumoUpdateAll();                                             // @ 0x414edb
void seedAiRandom();                                              // @ 0x40e188
void gameInit();                                                  // @ 0x40e1af
