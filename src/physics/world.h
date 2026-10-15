// The physics world: object pools, collision detection and the solver.
#pragma once

#include "body.h"

// Marsaglia's universal random number generator ("RANMAR"), single precision.
// 0x19c bytes; u[0] is unused.
struct Random {
    float u[98];              // +0x000
    float c;                  // +0x188
    float cd;                 // +0x18c
    float cm;                 // +0x190
    int i97;                  // +0x194
    int j97;                  // +0x198

    Random() { seed(17985, 21338); }   // @ 0x40b829
    void seed(int ij, int kl);         // @ 0x40b685
    float next();                      // @ 0x40b798 uniform in [0, 1)
};

extern Random g_random;                      // @ 0x766438

extern Body g_bodies[MAX_BODIES];            // @ 0x746c30
extern Body *g_bodyEnd;                      // @ 0x561408
extern Body *const g_bodyPoolLimit;          // @ 0x4536e4 (= g_bodies + MAX_BODIES)
extern Body g_scratch[2];                    // @ 0x531200, 0x531300 clipping work bodies

extern Joint g_joints[MAX_JOINTS];           // @ 0x521e00
extern Joint *g_jointEnd;                    // @ 0x561404
extern JointLink g_jointLinks[MAX_JOINT_LINKS]; // @ 0x561410
extern JointLink *g_jointLinkEnd;            // @ 0x56140c

extern Contact g_contacts[MAX_CONTACTS + 1]; // @ 0x531400 (+1: end sentinel)
extern Contact *g_contactEnd;                // @ 0x562c18
extern Penetration g_penetrations[MAX_PENETRATIONS]; // @ 0x511e00
extern Penetration *g_penetrationEnd;        // @ 0x562c14
extern ContactCache g_contactCaches[MAX_CONTACT_CACHES]; // @ 0x5aec28
extern ContactCache *g_contactCacheEnd;      // @ 0x561400

extern float g_waterInvCell;                 // @ 0x5aec20 1 / water cell size
extern char g_fragmentHardening;             // @ 0x746c28 fragments are 3x harder to break
extern float g_penetrationScale;             // @ 0x7665d4 = g_gravity * -0.05 (0.00049)
extern int g_skipPhysics;                    // @ 0x766434 never set by the game
extern int g_physicsFrame;                   // @ 0x511dec
extern char g_physicsStarted;                // @ 0x4536e8

void rebuildJointLinks();                                            // @ 0x408c36
Body *createBox(Vec3 half, Vec3 pos, int material, float uvScale);  // @ 0x408d57
void allocScratchBodies();                                           // @ 0x408e01
void removeExcessDebris();                                           // @ 0x408ee9
int collide(Body *a, Body *b);                                       // @ 0x409fce
void solve();                                                        // @ 0x40a477
void replayPhysicsStep();                                            // @ 0x40b5aa
void physicsStep();                                                  // @ 0x40b5f7
