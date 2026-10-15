// Rigid body world: convex polyhedra, joints and contacts.
//
// All objects live in fixed pools exactly like the original (no heap churn
// apart from the per-body geometry arrays).  Field offsets of the original
// 32-bit layout are given in the comments.
#pragma once

#include "../core/vecmath.h"

struct Body;
struct Joint;
struct Face;

// 16 bytes
struct Vertex {
    Vec3 pos;                 // +0x00 (body space)
    char above;               // +0x0c set by the plane splitter
    char created;             // +0x0d vertex created by a cut
    short newIndex;           // +0x0e
};

// 8 bytes - entries of a face's vertex loop
struct FaceVertex {
    Vertex *vertex;           // +0x00
    int index;                // +0x04
};

// 0x24 bytes
struct Face {
    Vec3 normal;              // +0x00 area weighted normal
    float d;                  // +0x0c plane offset (normal . v0)
    FaceVertex *loop;         // +0x10
    float weight;             // +0x14 1 = original surface, -1 = cut surface
    int textured;             // +0x18
    int count;                // +0x1c
    char frontFacing;         // +0x20 computed while rendering
    char pad[3];
};

// 16 bytes
struct Edge {
    int v0;                   // +0x00
    int v1;                   // +0x04
    Face *faceA;              // +0x08
    Face *faceB;              // +0x0c
};

// 12 bytes, node of a body's joint list
struct JointLink {
    JointLink *next;          // +0x00
    Joint *joint;             // +0x04
    Body *other;              // +0x08
};

// 0xcc bytes, collision impulse record kept per body pair for warm starting
struct ContactCache {
    Body *other;              // +0x00
    int count;                // +0x04
    Vec3 impulse[16];         // +0x08
    ContactCache *next;       // +0xc8
};

// 0xfc bytes
struct Body {
    Vertex *vertBegin;        // +0x00
    Vertex *vertEnd;          // +0x04
    FaceVertex *loopBegin;    // +0x08
    FaceVertex *loopEnd;      // +0x0c
    Face *faceBegin;          // +0x10
    Face *faceEnd;            // +0x14
    Edge *edgeBegin;          // +0x18
    Edge *edgeEnd;            // +0x1c
    Vec3 uvOffset;            // +0x20
    float radius;             // +0x2c bounding sphere radius
    int material;             // +0x30 texture / colour slot
    float uvScale;            // +0x34
    float volume;             // +0x38
    Vec3 centroid;            // +0x3c
    Vec3 surfaceSum;          // +0x48
    float breakThreshold;     // +0x54
    char removed;             // +0x58
    char sleeping;            // +0x59
    char pad5a[2];
    int sleepCounter;         // +0x5c
    Mat3 rot;                 // +0x60
    Vec3 pos;                 // +0x84
    Vec3 angVel;              // +0x90 (treated with a scalar inertia)
    Vec3 vel;                 // +0x9c
    float density;            // +0xa8
    float mass;               // +0xac
    float invMass;            // +0xb0
    float inertia;            // +0xb4
    float invInertia;         // +0xb8
    int tag;                  // +0xbc menu item / user tag
    int sound;                // +0xc0 impact sound id (0 = silent)
    float soundVolume;        // +0xc4
    float soundScale;         // +0xc8
    float impact;             // +0xcc
    char isStatic;            // +0xd0
    char padd1[3];
    int lastContactFrame;     // +0xd4
    int lastHeavyContactFrame;// +0xd8
    int lastFarContactFrame;  // +0xdc
    int contactIterations;    // +0xe0
    ContactCache *contacts;   // +0xe4
    JointLink *joints;        // +0xe8
    char recorded;            // +0xec replay: geometry already written
    char padd[3];
    Vec3 recordedPos;         // +0xf0 replay: last written position

    void freeGeometry();                                           // @ 0x4083ab
    Vec3 velocityAt(const Vec3 &point) const;                      // @ 0x408401
    void applyAngularImpulse(const Vec3 &j);                       // @ 0x40846d
    Vec3 response(const Vec3 &at, const Vec3 &impulse, const Vec3 &point) const; // @ 0x4084a3
    Mat3 responseMatrix(const Vec3 &at, const Vec3 &point) const;  // @ 0x408520
    void applyImpulse(const Vec3 &point, const Vec3 &j);           // @ 0x408612
    void computeMassProperties();                                  // @ 0x4086da
    void recenter();                                               // @ 0x4087a4
    void allocGeometry(int vertices, int loops, int faces);        // @ 0x4087d6
    void scaleMass(float k);                                       // @ 0x4088b5
    void build(const Vec3 *vertices, int vertexCount, const int *faces, int faceData); // @ 0x4088fe
    void makeStatic();                                             // @ 0x4089b4
    void buildEdges();                                             // @ 0x4089de
    void finishShape();                                            // @ 0x408ace
    void init();                                                   // @ 0x408b34
    void clear();                                                  // @ 0x408d37
    void rebuildAfterCut(int textured);                            // @ 0x408e51
    bool contains(const Vec3 &p) const;                            // @ 0x408eab
    void clipFrom(Body *src, const Vec3 &n, float d);              // @ 0x4092f8
    void cut(const Vec3 &n, float d);                              // @ 0x409679
    void applyBuoyancy();                                          // @ 0x4096d2
    void integrate();                                              // @ 0x409a6c
    bool fracture(const Vec3 &impactPoint);                        // @ 0x409b35
};

void facePlane(Face *f);                                           // @ 0x408812
void jointApplyTorque(Body **pair, const Vec3 &j);                 // @ 0x4086a6

// 0xf4 bytes
struct Joint {
    Body *a;                  // +0x00
    Body *b;                  // +0x04
    Vec3 anchorA;             // +0x08
    Vec3 anchorB;             // +0x14
    Vec3 axisA;               // +0x20
    Vec3 axisB;               // +0x2c
    Vec3 refA;                // +0x38
    Vec3 refB;                // +0x44
    float hinge;              // +0x50 0 = cone/twist limit, otherwise hinge
    float limitCos;           // +0x54
    float limitTwist;         // +0x58
    float unk5c;              // +0x5c
    char alignChild;          // +0x60
    char pad61[3];
    Vec3 unk64;               // +0x64
    Mat3 massMatrix;          // +0x70
    float unk94[9];           // +0x94
    Vec3 linearImpulse;       // +0xb8 warm start of the anchor constraint
    Vec3 unkc4;               // +0xc4
    Vec3 limitAxis;           // +0xd0
    Vec3 twistAxis;           // +0xdc
    float limitImpulse;       // +0xe8
    float twistImpulse;       // +0xec
    unsigned flags;           // +0xf0
};

// 0x60 bytes
struct Contact {
    Vec3 point;               // +0x00
    Vec3 normal;              // +0x0c
    Vec3 impulse;             // +0x18
    Body *a;                  // +0x24
    Body *b;                  // +0x28
    Mat3 massMatrix;          // +0x2c
    int iterations;           // +0x50
    char warmStarted;         // +0x54
    char pad[3];
    void *tagA;               // +0x58 always &g_contactTag
    void *tagB;               // +0x5c always &g_contactTag
};

// 0x20 bytes
struct Penetration {
    Vec3 point;               // +0x00
    Vec3 push;                // +0x0c
    Body *a;                  // +0x18
    Body *b;                  // +0x1c
};

enum {
    MAX_BODIES = 512,         // pool 0x746c30 .. 0x766430
    MAX_JOINTS = 256,         // pool 0x521e00 .. 0x531200
    MAX_CONTACTS = 2048,      // pool 0x531400 .. 0x561400
    MAX_PENETRATIONS = 2048,  // pool 0x511e00 .. 0x521e00
    MAX_JOINT_LINKS = 512,    // pool 0x561410 .. 0x562c10
    MAX_CONTACT_CACHES = 8192,// pool 0x5aec28 .. 0x746c28
};
