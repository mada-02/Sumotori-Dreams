// The physics world: object pools, collision detection and the solver.
#include "world.h"
#include "../core/common.h"
#include "../game/game.h"
#include "../game/sumo.h"
#include "../game/replay.h"
#include "../game/camera.h"
#include "../game/menu.h"
#include "../render/water.h"
#include "../audio/sound.h"

Random g_random;
Body g_bodies[MAX_BODIES];
Body *g_bodyEnd = g_bodies;
Body *const g_bodyPoolLimit = g_bodies + MAX_BODIES;
Body g_scratch[2];
Joint g_joints[MAX_JOINTS];
Joint *g_jointEnd = g_joints;
JointLink g_jointLinks[MAX_JOINT_LINKS];
JointLink *g_jointLinkEnd;
Contact g_contacts[MAX_CONTACTS + 1];
Contact *g_contactEnd;
Penetration g_penetrations[MAX_PENETRATIONS];
Penetration *g_penetrationEnd;
ContactCache g_contactCaches[MAX_CONTACT_CACHES];
ContactCache *g_contactCacheEnd;
float g_waterInvCell;
char g_fragmentHardening;
float g_penetrationScale;
int g_skipPhysics;
int g_physicsFrame;
char g_physicsStarted;

// Dead stores of the original solver, kept for completeness.
static int g_contactTag;                  // @ 0x562c20
static int *g_lastContactTag;             // @ 0x511df8
static char g_unk766432;                  // @ 0x766432

// @ 0x40b685
void Random::seed(int ij, int kl)
{
    if (ij < 0 || ij > 31328 || kl < 0 || kl > 30081) {
        ij = 1231;
        kl = 5818;
    }
    int i = ij / 177 % 177 + 2;
    int j = ij % 177 + 2;
    int k = kl / 169 % 178 + 1;
    int l = kl % 169;
    for (int ii = 1; ii <= 97; ++ii) {
        double s = 0.0;
        double t = 0.5;
        for (int jj = 0; jj < 24; ++jj) {
            int m = i * j % 179 * k % 179;
            i = j;
            j = k;
            k = m;
            l = (53 * l + 1) % 169;
            if (l * m % 64 >= 32)
                s += t;
            t *= 0.5;
        }
        u[ii] = (float)s;
    }
    c = 362436.0f / 16777216.0f;
    cd = 7654321.0f / 16777216.0f;
    cm = 16777213.0f / 16777216.0f;
    i97 = 97;
    j97 = 33;
}

// @ 0x40b798
float Random::next()
{
    float uni = u[i97] - u[j97];
    if (uni < 0.0f)
        uni = uni + 1.0f;
    u[i97] = uni;
    if (--i97 == 0)
        i97 = 97;
    if (--j97 == 0)
        j97 = 97;
    c = c - cd;
    if (c < 0.0f)
        c = c + cm;
    uni = uni - c;
    if (uni < 0.0f)
        uni = uni + 1.0f;
    return uni;
}

// @ 0x408c36
// Clears the joint warm starting state and rebuilds every body's list of
// joints (one link per joint end).
void rebuildJointLinks()
{
    for (Body *b = g_bodies; b < g_bodyEnd; ++b)
        b->joints = nullptr;

    g_jointLinkEnd = g_jointLinks;
    for (Joint *j = g_joints; j < g_jointEnd; ++j) {
        j->flags = 0;
        j->unk5c = 0.0f;
        j->limitImpulse = 0.0f;
        j->twistImpulse = 0.0f;
        j->unk64.z = 0.0f;
        j->unk64.y = 0.0f;
        j->unk64.x = 0.0f;
        j->unkc4.z = 0.0f;
        j->unkc4.y = 0.0f;
        j->unkc4.x = 0.0f;
        j->linearImpulse.z = 0.0f;
        j->linearImpulse.y = 0.0f;
        j->linearImpulse.x = 0.0f;

        JointLink *link = g_jointLinkEnd;
        link->other = j->b;
        link->joint = j;
        link->next = j->a->joints;
        j->a->joints = link;
        ++g_jointLinkEnd;

        link = g_jointLinkEnd;
        link->other = j->a;
        link->joint = j;
        link->next = j->b->joints;
        j->b->joints = link;
        ++g_jointLinkEnd;
    }
}

static const int kBoxFaces[30] = {   // @ 0x453708
    2, 3, 7, 6, -1,
    3, 1, 5, 7, -1,
    0, 1, 3, 2, -1,
    0, 2, 6, 4, -1,
    1, 0, 4, 5, -1,
    6, 7, 5, 4, -1,
};

// @ 0x408d57
Body *createBox(Vec3 half, Vec3 pos, int material, float uvScale)
{
    Body *b = g_bodyEnd;
    b->clear();

    Vec3 corners[8];
    for (int i = 0; i < 8; ++i) {
        Vec3 v = half;
        if (i & 1)
            v.x = v.x * -1.0f;
        if (!(i & 2))
            v.y = v.y * -1.0f;
        if (i & 4)
            v.z = v.z * -1.0f;
        corners[i] = v;
    }
    b->build(corners, 8, kBoxFaces, 30);
    b->init();
    b->pos = pos;
    b->material = material;
    b->uvScale = uvScale;
    ++g_bodyEnd;
    return b;
}

// @ 0x408e01
void allocScratchBodies()
{
    g_scratch[0].allocGeometry(0x200, 0x800, 0x200);
    g_scratch[1].allocGeometry(0x200, 0x800, 0x200);
}

// @ 0x408ee9
// Keeps the number of loose pieces at 90 by deleting the lightest one.
void removeExcessDebris()
{
    float lightest = 1e36f;
    Body *victim = nullptr;
    int count = 0;
    for (Body *b = g_bodies; b < g_bodyEnd; ++b) {
        if (b->joints == nullptr && !b->isStatic && !b->removed) {
            if (lightest > b->mass) {
                victim = b;
                lightest = b->mass;
            }
            ++count;
        }
    }
    if (count > 90 && victim)
        victim->removed = 1;
}

// Binary min-heap of separating plane candidates used by collide().
struct PlaneHeap {
    struct Entry {
        float key;
        Vec3 normal;
    };
    Entry entries[512];
    int count;

    // @ 0x408f7d
    void push(float key, Vec3 normal)
    {
        Entry e;
        e.key = key;
        e.normal = normal;
        entries[count] = e;
        ++count;
        int i = count - 1;
        while (i != 0) {
            int parent = (i - 1) / 2;
            if (!(entries[parent].key > entries[i].key))
                break;
            Entry t = entries[parent];
            entries[parent] = entries[i];
            entries[i] = t;
            i = parent;
        }
    }

    // @ 0x409004
    // The sift-down still sees the moved last entry because the count is
    // only decremented at the end (as in the original).
    Vec3 pop()
    {
        Vec3 top;
        if (count > 1) {
            top = entries[0].normal;
            entries[0] = entries[count - 1];
            int i = 0;
            for (int child = 1; child < count; child = 2 * i + 1) {
                if (child < count - 1 && entries[child].key > entries[child + 1].key)
                    ++child;
                if (entries[child].key < entries[i].key) {
                    Entry t = entries[i];
                    entries[i] = entries[child];
                    entries[child] = t;
                    i = child;
                } else {
                    i = count;
                }
            }
            --count;
        } else if (count != 0) {
            top = entries[0].normal;
            --count;
        } else {
            top = entries[0].normal;
        }
        return top;
    }
};

// @ 0x409fce
// Intersects body a with body b by clipping a against b's face planes (most
// separating first).  The vertices created by the clipping become contacts;
// the intersection volume becomes a penetration push.  Returns 0 when the
// bodies are jointed together or do not overlap.
int collide(Body *a, Body *b)
{
    for (JointLink *l = a->joints; l; l = l->next) {
        if (l->other == b)
            return 0;
    }

    PlaneHeap heap;
    heap.count = 0;
    Body *dst = &g_scratch[0];
    Body *spare = &g_scratch[1];

    Mat3 toA = b->rot.transposed() * a->rot.transposed();
    Vec3 rel = b->rot * (a->pos - b->pos);
    for (Face *f = b->faceBegin; f < b->faceEnd; ++f) {
        Vec3 n = toA * f->normal;
        heap.push(-(f->d - (rel.y * f->normal.y + rel.z * f->normal.z + rel.x * f->normal.x)), n);
    }

    Body *src = a;
    while (heap.count != 0) {
        float d = -heap.entries[0].key;
        Vec3 n = heap.entries[0].normal;
        heap.pop();
        dst->clipFrom(src, n, d);
        if (dst->faceEnd == dst->faceBegin)
            return 0;
        src = dst;
        dst = spare;
        spare = src;
    }

    src->computeMassProperties();
    Vec3 normal = src->surfaceSum * a->rot;
    if (normal.z * normal.z + normal.y * normal.y + normal.x * normal.x < 1e-20f)
        return 1;
    normal.normalize();

    // warm start impulses stored by the previous step for this pair
    Vec3 *cached = nullptr;
    int cachedCount = 0;
    for (ContactCache *c = a->contacts; c; c = c->next) {
        if (c->other == b) {
            cached = c->impulse;
            cachedCount = c->count;
            break;
        }
    }

    for (Vertex *v = src->vertBegin; v < src->vertEnd; ++v) {
        if (!v->created)
            continue;
        Contact *c = g_contactEnd;
        c->point = v->pos * a->rot + a->pos;
        c->normal = -normal;
        Vec3 zero = V3(0.0f, 0.0f, 0.0f);
        c->a = a;
        c->b = b;
        c->impulse = zero;
        int iterations = a->contactIterations;
        if (!(iterations > b->contactIterations))
            iterations = b->contactIterations;
        c->iterations = iterations;
        c->warmStarted = 0;
        if (cachedCount != 0) {
            c->warmStarted = 1;
            --cachedCount;
            c->impulse = *cached++;
        }
        ++g_contactEnd;
    }

    if (!(src->volume > 1e-9f))
        return 1;

    Vec3 center = src->centroid * a->rot + a->pos;
    float scale = src->volume / (a->invMass + b->invMass) * g_penetrationScale;
    Penetration *p = g_penetrationEnd;
    p->push = normal * scale;
    p->point = center;
    p->a = a;
    p->b = b;
    ++g_penetrationEnd;

    // remember when a body last touched something heavy (the floor) and
    // whether that happened outside the ring
    if (b->joints == nullptr && b->volume > 200.0f) {
        Vec3 ringCenter = V3(0.0f, 5.0f, 0.0f);
        float r = g_ringRadius + 1.0f;
        if (r * r < (center - ringCenter).lengthSq())
            a->lastFarContactFrame = g_frame;
        a->lastHeavyContactFrame = g_frame;
    }
    if (a->joints == nullptr && a->volume > 200.0f) {
        Vec3 ringCenter = V3(0.0f, 5.0f, 0.0f);
        float r = g_ringRadius + 1.0f;
        if (r * r < (center - ringCenter).lengthSq())
            b->lastFarContactFrame = g_frame;
        b->lastHeavyContactFrame = g_frame;
    }
    a->lastContactFrame = g_frame;
    b->lastContactFrame = g_frame;
    if (!b->isStatic)
        a->sleepCounter = 0;
    if (!a->isStatic)
        b->sleepCounter = 0;
    a->sleeping = 0;
    b->sleeping = 0;
    return 1;
}

// @ 0x40a477
// One simulation step of the constraint solver: broad phase and collision,
// joint and contact set-up, 40 sequential impulse iterations, then impact
// sounds, breaking and the penetration pushes.
void solve()
{
    g_contactEnd = g_contacts;
    g_penetrationEnd = g_penetrations;

    // broad phase (bounding spheres) against all earlier bodies
    for (Body *a = g_bodies; a < g_bodyEnd; ++a) {
        if (a->removed)
            continue;
        if (!a->isStatic && !a->sleeping) {
            if (a <= g_bodies)
                continue;
            for (Body *b = g_bodies; b < a; ++b) {
                if (b->removed || a->isStatic)
                    continue;
                float r = b->radius + a->radius;
                if (r * r > (a->pos - b->pos).lengthSq())
                    collide(a, b);
            }
        } else {
            if (a <= g_bodies)
                continue;
            for (Body *b = g_bodies; b < a; ++b) {
                if (b->removed || b->sleeping || b->isStatic)
                    continue;
                float r = b->radius + a->radius;
                if (r * r > (a->pos - b->pos).lengthSq())
                    collide(a, b);
            }
        }
    }

    // joint set-up
    for (Joint *j = g_joints; j < g_jointEnd; ++j) {
        if (j->a->removed || j->b->removed)
            continue;

        // angular damping between the two parts
        float damp = -0.2f / (j->a->invInertia + j->b->invInertia);
        jointApplyTorque(&j->a, (j->a->angVel - j->b->angVel) * damp);
        j->flags = 0;

        Body *A = j->a;
        Body *B = j->b;
        Vec3 wA = j->anchorA * A->rot + A->pos;
        Vec3 wB = j->anchorB * B->rot + B->pos;
        j->massMatrix = (A->responseMatrix(wA, wA) + B->responseMatrix(wB, wB)).inverse();

        float one = 1.0f;
        Vec3 warm = j->linearImpulse * one;
        if (!A->isStatic)
            A->applyImpulse(wA, -warm);
        if (!B->isStatic)
            B->applyImpulse(wB, warm);

        Vec3 axisA = j->axisA * j->a->rot;
        Vec3 axisB = j->axisB * j->b->rot;
        Vec3 bend = axisA.cross(axisB);
        Vec3 bendAxis = bend;
        float bendSq = bend.x * bend.x + bend.z * bend.z + bend.y * bend.y;
        bendAxis.normalize();

        A = j->a;
        Vec3 refA = j->refA * A->rot;
        Vec3 refB = j->refB * j->b->rot;
        Vec3 twist = refA.cross(refB);

        if (j->hinge != 0.0f) {
            // hinge: keep the reference vectors aligned
            float k = 0.01f;
            A->applyAngularImpulse(twist * k);
            j->b->applyAngularImpulse(-twist * k);
            j->flags |= 4;
            twist.normalize();
            j->twistAxis = twist;
            k = j->twistImpulse;
            j->a->applyAngularImpulse(twist * k);
            j->b->applyAngularImpulse(-twist * k);
        } else {
            // cone: undo the bend, then limit the remaining twist
            float angle = -(float)atanXY((float)fp::sqrt(bendSq),
                                         axisB.x * axisA.x + axisB.z * axisA.z + axisB.y * axisA.y);
            float c = (float)fp::cos(angle);
            refA.rotate(bendAxis, c, (float)fp::sin(angle));
            // measured on the cross product taken before the correction
            float twistSq = twist.x * twist.x + twist.z * twist.z + twist.y * twist.y;
            if (twistSq > j->limitTwist) {
                j->flags |= 2;
                Vec3 axis = refA.cross(refB);
                float half = angle * -0.5f;
                float hc = (float)fp::cos(half);
                axis.rotate(bendAxis, hc, (float)fp::sin(half));
                axis.normalize();
                j->twistAxis = axis;
                float limit = (float)fp::sqrt(j->limitTwist);
                A = j->a;
                float k = (float)((fp::sqrt(twistSq) - limit) * 0.04f /
                                  (A->invInertia + j->b->invInertia) + j->twistImpulse);
                A->applyAngularImpulse(axis * k);
                j->b->applyAngularImpulse(-axis * k);
            } else {
                j->twistImpulse = 0.0f;
            }
        }

        if (!(bendSq < j->limitCos)) {
            j->flags |= 1;
            j->limitAxis = bendAxis;
            float limit = (float)fp::sqrt(j->limitCos);
            A = j->a;
            float k = (float)((fp::sqrt(bendSq) - limit) * 0.2f /
                              (A->invInertia + j->b->invInertia) + j->limitImpulse);
            A->applyAngularImpulse(bendAxis * k);
            j->b->applyAngularImpulse(-bendAxis * k);
        }
    }

    // contact set-up
    g_lastContactTag = &g_contactTag;
    for (Contact *c = g_contacts; c < g_contactEnd; ++c) {
        c->tagA = &g_contactTag;
        Mat3 k = c->a->responseMatrix(c->point, c->point);
        k = k + c->b->responseMatrix(c->point, c->point);
        c->tagB = &g_contactTag;
        g_unk766432 = 0;
        c->massMatrix = k.inverse();
    }

    for (int iteration = 0; iteration < 40; ++iteration) {
        for (Contact *c = g_contacts; c < g_contactEnd; ++c) {
            if (c->iterations == 0)
                continue;
            --c->iterations;

            Vec3 applied;
            if (iteration != 0) {
                Vec3 vb = c->b->velocityAt(c->point);
                Vec3 dv = c->a->velocityAt(c->point) - vb;
                Vec3 total = dv * c->massMatrix;
                total.x = total.x + c->impulse.x;
                total.y = total.y + c->impulse.y;
                total.z = total.z + c->impulse.z;
                const Vec3 &n = c->normal;
                float normalPart = total.z * n.z + total.y * n.y + total.x * n.x;
                Vec3 tangent = total - n * normalPart;
                if (normalPart < 0.0f) {
                    total = V3(0.0f, 0.0f, 0.0f);   // separating
                } else {
                    float t2 = tangent.z * tangent.z + tangent.y * tangent.y + tangent.x * tangent.x;
                    if (t2 != 0.0f && normalPart * normalPart * 0.81f < t2) {
                        // friction cone
                        float s = (float)(normalPart / fp::sqrt(t2) * 0.9f);
                        tangent.x = tangent.x * s;
                        tangent.y = tangent.y * s;
                        tangent.z = tangent.z * s;
                    }
                    total = tangent + n * normalPart;
                }
                applied.x = total.x - c->impulse.x;
                applied.y = total.y - c->impulse.y;
                applied.z = total.z - c->impulse.z;
                c->impulse.x = applied.x + c->impulse.x;
                c->impulse.y = applied.y + c->impulse.y;
                c->impulse.z = applied.z + c->impulse.z;
            } else {
                applied = c->impulse;   // warm start
            }
            if (!c->a->isStatic)
                c->a->applyImpulse(c->point, -applied);
            if (!c->b->isStatic)
                c->b->applyImpulse(c->point, applied);
            c->a->contacts = nullptr;
        }

        for (Joint *j = g_joints; j < g_jointEnd; ++j) {
            Body *A = j->a;
            if (A->removed)
                continue;
            Body *B = j->b;
            if (B->removed)
                continue;

            Vec3 wA = j->anchorA * A->rot + A->pos;
            Vec3 wB = j->anchorB * B->rot + B->pos;
            Vec3 vB = B->velocityAt(wB);
            Vec3 dv = A->velocityAt(wA) - vB;
            float k = 0.03f;
            Vec3 imp = (dv - (wB - wA) * k) * j->massMatrix;
            if (!A->isStatic)
                A->applyImpulse(wA, -imp);
            if (!j->b->isStatic)
                j->b->applyImpulse(wB, imp);

            if (j->flags & 4) {
                B = j->b;
                A = j->a;
                Vec3 dw = A->angVel - B->angVel;
                const Vec3 &axis = j->twistAxis;
                float x = (float)(0.9f / (A->invInertia + B->invInertia) *
                                      (dw.y * axis.y + dw.z * axis.z + dw.x * axis.x) +
                                  j->twistImpulse);
                if (x < 0.0f)
                    x = 0.0f;
                float delta = x - j->twistImpulse;
                j->twistImpulse = delta + j->twistImpulse;
                A->applyAngularImpulse(axis * delta);
                float neg = -delta;
                j->b->applyAngularImpulse(axis * neg);
            }
            if (j->flags & 1) {
                B = j->b;
                A = j->a;
                Vec3 dw = A->angVel - B->angVel;
                const Vec3 &axis = j->limitAxis;
                float x = (float)(0.9f / (A->invInertia + B->invInertia) *
                                      (axis.z * dw.z + dw.y * axis.y + axis.x * dw.x) +
                                  j->limitImpulse);
                if (x < 0.0f)
                    x = 0.0f;
                float delta = x - j->limitImpulse;
                j->limitImpulse = delta + j->limitImpulse;
                A->applyAngularImpulse(axis * delta);
                float neg = -delta;
                j->b->applyAngularImpulse(axis * neg);
            }
            if (j->flags & 2) {
                B = j->b;
                A = j->a;
                Vec3 dw = A->angVel - B->angVel;
                const Vec3 &axis = j->twistAxis;
                float x = (float)(0.9f / (A->invInertia + B->invInertia) *
                                      (dw.y * axis.y + dw.z * axis.z + axis.x * dw.x) +
                                  j->twistImpulse);
                if (x < 0.0f)
                    x = 0.0f;
                float delta = x - j->twistImpulse;
                j->twistImpulse = delta + j->twistImpulse;
                A->applyAngularImpulse(axis * delta);
                float neg = -delta;
                j->b->applyAngularImpulse(axis * neg);
            }
        }

        sumoApplyMotors();
    }

    // store the impulses for warm starting, play impact sounds and break
    for (Body *b = g_bodies; b < g_bodyEnd; ++b)
        b->contacts = nullptr;
    g_contactCacheEnd = g_contactCaches;
    g_contactEnd->b = nullptr;   // sentinel ending the last group

    for (Contact *c = g_contacts; c < g_contactEnd;) {
        ContactCache *cache = g_contactCacheEnd;
        Vec3 zero = V3(0.0f, 0.0f, 0.0f);
        cache->count = 0;
        float total = 0.0f;
        int count = 0;
        Vec3 pointSum = zero;
        Body *groupB = c->b;
        Body *groupA = c->a;
        char warm = c->warmStarted;
        Contact *first = c;
        do {
            if (c->a != groupA || g_contactCacheEnd->count >= 16)
                break;
            total = (float)(fp::sqrt(c->impulse.lengthSq()) + total);
            ++count;
            pointSum.x = pointSum.x + c->point.x;
            pointSum.y = pointSum.y + c->point.y;
            pointSum.z = pointSum.z + c->point.z;
            g_contactCacheEnd->impulse[g_contactCacheEnd->count] = c->impulse;
            ++c;
            ++g_contactCacheEnd->count;
        } while (c->b == groupB);
        Contact *last = c - 1;

        if (total > 0.3f && !warm) {
            for (int side = 0; side < 2; ++side) {
                Body *body = side ? last->b : last->a;
                if (body->mass * 0.04f < total && body->sound != 0 && body->impact * 3.0f < total) {
                    float pitch = (float)fp::exp(fp::log(body->volume / body->soundScale) * -0.25f);
                    playSound(body->sound, pitch, total * body->soundVolume, 0);
                }
                if (total > body->impact)
                    body->impact = total;
            }
        }

        Contact *release = first;
        if (total > last->a->breakThreshold) {
            for (; release < last; ++release) {
                float k = 0.25f;
                release->a->applyImpulse(release->point, release->impulse * k);
                float k2 = 0.25f;
                release->b->applyImpulse(release->point, -release->impulse * k2);
            }
            float inv = 1.0f / (float)count;
            last->a->fracture(pointSum * inv);
        }
        if (total > last->b->breakThreshold) {
            for (; release < last; ++release) {
                float k = 0.25f;
                release->a->applyImpulse(release->point, release->impulse * k);
                float k2 = 0.25f;
                release->b->applyImpulse(release->point, -release->impulse * k2);
            }
            float inv = 1.0f / (float)count;
            last->b->fracture(pointSum * inv);
        }

        cache->next = last->a->contacts;
        g_contactCacheEnd->other = last->b;
        last->a->contacts = g_contactCacheEnd;
        ++g_contactCacheEnd;
        c = last + 1;
    }

    for (Penetration *p = g_penetrations; p < g_penetrationEnd; ++p) {
        p->a->applyImpulse(p->point, p->push);
        p->b->applyImpulse(p->point, -p->push);
    }
}

// @ 0x40b5aa
// Replay playback: bodies are positioned by the replay, only the water
// interaction is simulated.
void replayPhysicsStep()
{
    g_waterInvCell = 1.0f / g_waterCellSize;
    for (Body *b = g_bodies; b < g_bodyEnd; ++b) {
        if (b->vel.lengthSq() > 1e-5f)
            b->applyBuoyancy();
    }
}

// @ 0x40b5f7
void physicsStep()
{
    removeExcessDebris();
    updateFade();
    if (g_cameraMode < 2) {
        if (g_skipPhysics == 0) {
            g_physicsStarted = 1;
            g_waterInvCell = 1.0f / g_waterCellSize;
            solve();
            for (Body *b = g_bodies; b < g_bodyEnd; ++b)
                b->integrate();
            sumoUpdateAll();
        }
        g_skipPhysics = 0;
        g_fragmentHardening = 1;
        if (g_cameraMode >= 2)
            replayPhysicsStep();
    } else {
        replayPhysicsStep();
    }
    replayUpdate();
    waterUpdate();
    ++g_physicsFrame;
}
