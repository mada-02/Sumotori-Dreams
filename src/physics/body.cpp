// Rigid body geometry, mass properties and integration.
#include "body.h"
#include "world.h"
#include "../core/common.h"
#include "../game/game.h"
#include "../render/water.h"
#include "../audio/sound.h"
#include "../platform/debug.h"

// @ 0x4083ab
void Body::freeGeometry()
{
    free(vertBegin);
    free(loopBegin);
    free(faceBegin);
    free(edgeBegin);
}

// @ 0x408401
// Velocity of the body at a world space point.  angVel holds the negated
// angular velocity, hence r x angVel.
Vec3 Body::velocityAt(const Vec3 &point) const
{
    if (isStatic)
        return V3(0.0f, 0.0f, 0.0f);
    return vel + (point - pos).cross(angVel);
}

// @ 0x40846d
void Body::applyAngularImpulse(const Vec3 &j)
{
    if (!isStatic)
        angVel -= j * invInertia;
}

// @ 0x4084a3
// Velocity change at `point` caused by `impulse` applied at `at`.
Vec3 Body::response(const Vec3 &at, const Vec3 &impulse, const Vec3 &point) const
{
    Vec3 rPoint = point - pos;
    return impulse * invMass + (at - pos).cross(impulse).cross(rPoint) * invInertia;
}

// @ 0x408520
Mat3 Body::responseMatrix(const Vec3 &at, const Vec3 &point) const
{
    Mat3 r;
    r.row(0) = response(at, V3(1.0f, 0.0f, 0.0f), point);
    r.row(1) = response(at, V3(0.0f, 1.0f, 0.0f), point);
    r.row(2) = response(at, V3(0.0f, 0.0f, 1.0f), point);
    return r;
}

// @ 0x408612
void Body::applyImpulse(const Vec3 &point, const Vec3 &j)
{
    if (!isStatic) {
        Vec3 w = (point - pos).cross(j) * invInertia;
        angVel.x = angVel.x - w.x;
        angVel.y = angVel.y - w.y;
        angVel.z = angVel.z - w.z;
        vel += j * invMass;
    }
}

// @ 0x4086a6
void jointApplyTorque(Body **pair, const Vec3 &j)
{
    Vec3 neg = -j;
    pair[0]->applyAngularImpulse(neg);
    pair[1]->applyAngularImpulse(j);
}

// Volume integration helper of computeMassProperties.
struct MassAccumulator {
    float volume;
    Vec3 sum;

    // @ 0x40810c
    MassAccumulator()
    {
        volume = 0.0f;
        sum = V3(0.0f, 0.0f, 0.0f);
    }

    // @ 0x408136
    // Adds the prism between triangle (a, b, c) and its projection onto the
    // z = 0 plane, as three tetrahedra (signed volumes are 6x the real ones).
    void addTriangle(const Vec3 &a, const Vec3 &b, const Vec3 &c, float /*weight*/)
    {
        Vec3 a0 = a;
        a0.z = 0.0f;
        Vec3 b0 = b;
        b0.z = 0.0f;
        Vec3 c0 = c;
        c0.z = 0.0f;
        float quarter = 0.25f;

        Vec3 e = a0 - b;
        Vec3 f = (c0 - b).cross(b0 - b);
        float v = e.z * f.z + e.y * f.y + e.x * f.x;
        Vec3 center = (((c0 + b) + a0) + b0) * quarter;
        volume = v + volume;
        sum += center * v;

        e = a0 - b;
        f = (a - b).cross(c0 - b);
        v = e.z * f.z + e.y * f.y + e.x * f.x;
        center = (((a + b) + c0) + a0) * quarter;
        volume = v + volume;
        sum += center * v;

        e = c0 - b;
        f = (a - b).cross(c - b);
        v = e.z * f.z + e.y * f.y + e.x * f.x;
        center = (((a + b) + c0) + c) * quarter;
        volume = v + volume;
        sum += center * v;
    }
};

// @ 0x4086da
void Body::computeMassProperties()
{
    MassAccumulator acc;
    surfaceSum = V3(0.0f, 0.0f, 0.0f);
    for (Face *f = faceBegin; f < faceEnd; ++f) {
        surfaceSum += f->normal * f->weight;
        if (f->count > 2) {
            Vertex *first = f->loop[0].vertex;
            for (int i = 1; i < f->count - 1; ++i)
                acc.addTriangle(first->pos, f->loop[i].vertex->pos, f->loop[i + 1].vertex->pos, f->weight);
        }
    }
    float inv = 1.0f / acc.volume;
    volume = acc.volume;
    centroid.x = acc.sum.x * inv;
    centroid.y = acc.sum.y * inv;
    centroid.z = acc.sum.z * inv;
}

// @ 0x4087a4
void Body::recenter()
{
    for (Vertex *v = vertBegin; v < vertEnd; ++v)
        v->pos -= centroid;
    centroid.z = 0.0f;
    centroid.y = 0.0f;
    centroid.x = 0.0f;
}

// @ 0x4087d6
// Reserves four times the requested room: clipping can only grow the shape
// by a bounded amount and is never checked against these sizes.
void Body::allocGeometry(int vertices, int loops, int faces)
{
    vertBegin = (Vertex *)malloc(vertices << 6);
    loopBegin = (FaceVertex *)malloc(loops << 5);
    faceBegin = (Face *)malloc(faces * 0x90);
}

// @ 0x408812
// Area weighted normal and plane offset of a face.
void facePlane(Face *f)
{
    Vec3 n = V3(0.0f, 0.0f, 0.0f);
    for (int i = 2; i < f->count; ++i) {
        Vec3 *v0 = &f->loop[0].vertex->pos;
        Vec3 e1 = f->loop[i - 1].vertex->pos - *v0;
        Vec3 c = (f->loop[i].vertex->pos - *v0).cross(e1);
        n.x = n.x + c.x;
        n.y = n.y + c.y;
        n.z = n.z + c.z;
    }
    f->normal = n;
    Vec3 &p = f->loop[0].vertex->pos;
    f->d = p.z * f->normal.z + p.y * f->normal.y + f->normal.x * p.x;
}

// @ 0x4088b5
void Body::scaleMass(float k)
{
    mass = k * mass;
    float inv = 1.0f / k;
    invMass = inv * invMass;
    density = k * density;
    inertia = k * inertia;
    invInertia = inv * invInertia;
}

// @ 0x4088fe
// faces: vertex indices, each face terminated by a negative value.
void Body::build(const Vec3 *vertices, int vertexCount, const int *faces, int faceData)
{
    allocGeometry(0x200, 0x800, 0x200);

    Vertex *v = vertBegin;
    for (int i = 0; i < vertexCount; ++i) {
        v->pos = vertices[i];
        v->created = 0;
        ++v;
    }
    vertEnd = v;

    FaceVertex *loop = loopBegin;
    Face *face = faceBegin;
    int count = 0;
    for (const int *p = faces; p < faces + faceData; ++p) {
        if (*p < 0) {
            face->count = count;
            face->weight = 1.0f;
            face->loop = loop - count;
            face->textured = 1;
            facePlane(face);
            ++face;
            count = 0;
        } else {
            loop->index = *p;
            loop->vertex = &vertBegin[*p];
            ++count;
            ++loop;
        }
    }
    loopEnd = loop;
    faceEnd = face;
}

// @ 0x4089b4
void Body::makeStatic()
{
    isStatic = 1;
    invMass = 0.0f;
    mass = 1e36f;
    invInertia = 0.0f;
    inertia = 1e36f;
}

// @ 0x4089de
// Every edge is stored once, owned by the face that walks it from the higher
// to the lower vertex index.
void Body::buildEdges()
{
    edgeBegin = (Edge *)malloc((loopEnd - loopBegin) * sizeof(Edge));
    edgeEnd = edgeBegin;

    for (Face *f = faceBegin; f < faceEnd; ++f) {
        int prev = f->count - 1;
        for (int i = 0; i < f->count; ++i) {
            if (f->loop[i].index > f->loop[prev].index) {
                edgeEnd->v0 = f->loop[i].index;
                edgeEnd->v1 = f->loop[prev].index;
                edgeEnd->faceA = f;
                edgeEnd->faceB = nullptr;
                ++edgeEnd;
            }
            prev = i;
        }
    }

    for (Face *f = faceBegin; f < faceEnd; ++f) {
        int prev = f->count - 1;
        for (int i = 0; i < f->count; ++i) {
            if (f->loop[i].index < f->loop[prev].index) {
                Edge *e = edgeBegin;
                while (e->v0 != f->loop[prev].index || e->v1 != f->loop[i].index)
                    ++e;
                e->faceB = f;
            }
            prev = i;
        }
    }
}

// @ 0x408ace
void Body::finishShape()
{
    buildEdges();
    invMass = 1.0f / mass;
    invInertia = 1.0f / inertia;
    radius = 0.0f;
    for (Vertex *v = vertBegin; v < vertEnd; ++v) {
        if (v->pos.lengthSq() > radius)
            radius = v->pos.lengthSq();
    }
    radius = (float)fp::sqrt(radius);
}

// @ 0x408b34
void Body::init()
{
    computeMassProperties();
    finishShape();
    density = 1.0f;
    tag = 0;
    mass = volume;
    recorded = 0;
    contactIterations = 3;
    removed = 0;
    inertia = radius * 0.4f * (radius * 0.4f) * volume;
    invMass = 1.0f / volume;
    invInertia = 1.0f / (radius * 0.4f * (radius * 0.4f) * volume);
    angVel = V3(0.0f, 0.0f, 0.0f);
    vel = V3(0.0f, 0.0f, 0.0f);
    rot.identity();
    isStatic = 0;
    contacts = nullptr;
    breakThreshold = 100000.0f;
    joints = nullptr;
    sound = 0;
    uvOffset = V3(0.0f, 0.0f, 0.0f);
    soundVolume = 0.0f;
    soundScale = 170.0f;
}

// @ 0x408d37
void Body::clear()
{
    memset(this, 0, sizeof(Body));
    lastContactFrame = 0;
    lastHeavyContactFrame = 0;
    lastFarContactFrame = 0;
}

// @ 0x408e51
// Moves the origin to the centroid and turns cut surfaces into regular ones
// with the given texture flag.
void Body::rebuildAfterCut(int textured)
{
    for (Vertex *v = vertBegin; v < vertEnd; ++v)
        v->pos -= centroid;
    for (Face *f = faceBegin; f < faceEnd; ++f) {
        if (f->weight < 0.0f)
            f->textured = textured;
        f->weight = 1.0f;
        facePlane(f);
    }
}

// @ 0x408eab
// True when the point is on the inner side of every face plane.
bool Body::contains(const Vec3 &p) const
{
    for (Face *f = faceBegin; f < faceEnd; ++f) {
        if (f->normal.y * p.y + f->normal.z * p.z + f->normal.x * p.x < f->d)
            return false;
    }
    return true;
}

// Edge crossing record of clipFrom: the new vertex created on the edge
// (prev -> cur) and the next crossing along the cap polygon.
struct ClipCrossing {
    int key;            // (prev << 16) + cur, looked up as (cur << 16) + prev
    int vertexIndex;
    ClipCrossing *next;
};

// @ 0x4092f8
// Replaces this body's geometry with the part of `src` where n.v > d.  The
// open side is closed by a cap face (weight -1) chained from the crossings.
void Body::clipFrom(Body *src, const Vec3 &n, float d)
{
    ClipCrossing table[1024];

    if ((((char *)src->vertEnd - (char *)src->vertBegin) & ~15) > 0x1000 ||
        (int)(src->faceEnd - src->faceBegin) > 0x100) {
        faceEnd = faceBegin;
        vertEnd = vertBegin;
        return;
    }

    char anyAbove = 0;
    for (Vertex *v = src->vertBegin; v < src->vertEnd; ++v) {
        char above = 1;
        if (!(v->pos.z * n.z + v->pos.y * n.y + v->pos.x * n.x > d))
            above = 0;
        v->newIndex = -1;
        v->above = above;
        anyAbove |= above;
    }
    if (!anyAbove) {
        faceEnd = faceBegin;
        return;
    }

    Vertex *vOut = vertBegin;
    int vertexCount = 0;
    ClipCrossing *tableEnd = table;
    Face *faceOut = faceBegin;
    FaceVertex *loopOut = loopBegin;
    if (!loopOut)
        return;

    for (Face *f = src->faceBegin; f < src->faceEnd; ++f) {
        FaceVertex *cur = f->loop;
        FaceVertex *prev = &f->loop[f->count - 1];
        ClipCrossing *entering = nullptr;
        ClipCrossing *leaving = nullptr;
        faceOut->loop = loopOut;
        int count = 0;
        if (f->count <= 0)
            continue;

        for (int i = 0; i < f->count; ++i, prev = cur, ++cur) {
            if (cur->vertex->above != prev->vertex->above) {
                int key = (cur->index << 16) + prev->index;
                ClipCrossing *x = table;
                while (x < tableEnd && key != x->key)
                    ++x;
                if (x == tableEnd) {
                    tableEnd->key = (prev->index << 16) + cur->index;
                    tableEnd->vertexIndex = vertexCount;
                    tableEnd->next = nullptr;
                    ++tableEnd;

                    Vertex *a = prev->vertex;
                    Vertex *b = cur->vertex;
                    float t = (float)((a->pos.z * n.z + a->pos.y * n.y + a->pos.x * n.x - d) /
                                      (a->pos.z * n.z + a->pos.y * n.y + n.x * a->pos.x -
                                       (b->pos.z * n.z + b->pos.y * n.y + n.x * b->pos.x)));
                    vOut->pos = a->pos - (a->pos - b->pos) * t;
                    vOut->created = 1;
                    ++vOut;
                    ++vertexCount;
                }
                if (cur->vertex->above)
                    entering = x;
                else
                    leaving = x;
                loopOut->index = x->vertexIndex;
                loopOut->vertex = &vertBegin[x->vertexIndex];
                ++loopOut;
                ++count;
            }
            if (cur->vertex->above) {
                if (cur->vertex->newIndex == -1) {
                    *vOut++ = *cur->vertex;
                    cur->vertex->newIndex = (short)vertexCount++;
                }
                loopOut->index = cur->vertex->newIndex;
                loopOut->vertex = &vertBegin[cur->vertex->newIndex];
                ++loopOut;
                ++count;
            }
        }

        if (count >= 3) {
            faceOut->count = count;
            faceOut->textured = f->textured;
            faceOut->normal = f->normal;
            faceOut->d = f->d;
            faceOut->weight = f->weight;
            if (entering) {
                entering->next = leaving;
                facePlane(faceOut);
            }
            ++faceOut;
        }
    }

    if (tableEnd != table) {
        // close the hole with a single cap face following the crossing chains
        int count = 0;
        faceOut->loop = loopOut;
        for (ClipCrossing *start = table; start < tableEnd; ++start) {
            if (start->vertexIndex == -1)
                continue;
            ClipCrossing *x = start;
            do {
                loopOut->index = x->vertexIndex;
                loopOut->vertex = &vertBegin[x->vertexIndex];
                x->vertexIndex = -1;
                x = x->next;
                ++loopOut;
                ++count;
            } while (x != start && x != nullptr);
            if (x == nullptr) {
                faceEnd = faceBegin;
                return;
            }
        }
        faceOut->count = count;
        facePlane(faceOut);
        faceOut->weight = -1.0f;
        ++faceOut;
    }

    faceEnd = faceOut;
    loopEnd = loopOut;
    vertEnd = vOut;
}

// @ 0x409679
void Body::cut(const Vec3 &n, float d)
{
    Vec3 up = V3(0.0f, 0.0f, 1.0f);
    g_scratch[0].clipFrom(this, up, -1000.0f);
    clipFrom(&g_scratch[0], n, d);
}

// @ 0x4096d2
// Water: lift and drag below the surface; bodies crossing the surface push
// the surrounding water cells.
void Body::applyBuoyancy()
{
    if (!g_waterEnabled)
        return;
    if (!(g_waterLevel + 3.0f > pos.y))
        return;

    int gx = fp::ftol(g_waterInvCell * pos.x);
    int gz = fp::ftol(g_waterInvCell * pos.z);
    if (gx >= g_waterGridW || gx < 0 || gz >= g_waterGridH || gz < 0)
        return;

    float depth = g_waterHeight.at(gz * g_waterGridW + gx) - pos.y + 1.3f;
    if (depth > 1.0f)
        depth = 1.0f;
    if (!(depth > 0.0f))
        return;

    if (depth < 1.0f) {
        float wave = (float)fp::sqrt(volume) * depth * -0.023f;
        float waveSide = wave * 1.5f;
        int W = g_waterGridW;
        int H = g_waterGridH;
        float *h;
        h = &g_waterVelocity.at(((gz + 1) % H) * W + (gx + 1) % W);
        *h = wave * vel.y + *h;
        h = &g_waterVelocity.at(((gz + 1) % H) * W + (W + gx - 1) % W);
        *h = wave * vel.y + *h;
        h = &g_waterVelocity.at(((H + gz - 1) % H) * W + (gx + 1) % W);
        *h = wave * vel.y + *h;
        h = &g_waterVelocity.at(((H + gz - 1) % H) * W + (W + gx - 1) % W);
        *h = wave * vel.y + *h;
        h = &g_waterVelocity.at((gz % H) * W + (gx + 1) % W);
        *h = waveSide * vel.y + *h;
        h = &g_waterVelocity.at((gz % H) * W + (W + gx - 1) % W);
        *h = waveSide * vel.y + *h;
        h = &g_waterVelocity.at(((H + gz - 1) % H) * W + gx % W);
        *h = waveSide * vel.y + *h;
        h = &g_waterVelocity.at(((gz + 1) % H) * W + gx % W);
        *h = waveSide * vel.y + *h;
        vel.y = vel.y * 0.93f;
    }

    vel.y = vel.y - g_gravity * depth * 1.4f;
    vel.x = vel.x * 0.95f;
    vel.y = vel.y * 0.95f;
    vel.z = vel.z * 0.95f;

    // tilt the body upright
    Vec3 side = V3(0.01f, 0.0f, 0.0f);
    Vec3 down = V3(0.0f, g_gravity, 0.0f);
    angVel += down.cross(side * rot);
    angVel.x = angVel.x * 0.995f;
    angVel.y = angVel.y * 0.995f;
    angVel.z = angVel.z * 0.995f;
}

// @ 0x409a6c
void Body::integrate()
{
    if (removed || isStatic)
        return;
    if (!sleeping) {
        rot.rotate(angVel);
        rot.orthonormalize();
        pos += vel;
        applyBuoyancy();
        if (joints == nullptr) {
            float v2 = vel.lengthSq();
            if ((angVel.lengthSq() + v2) * 111111.11f < 1.0f) {
                if (++sleepCounter > 30)
                    sleeping = 1;
            } else {
                sleepCounter = 0;
            }
        }
        if (!sleeping)
            vel.y = g_gravity + vel.y;
    }
    impact = impact * 0.94f;
}

// @ 0x409b35
// Shatters the body into (up to) five Voronoi cells around random points near
// the impact.  Joints attached to the body move to the nearest fragment.
bool Body::fracture(const Vec3 &impactPoint)
{
    if (removed || g_bodyEnd > g_bodyPoolLimit - 10)
        return false;

    Body *scratchA = &g_scratch[0];
    Body *scratchB = &g_scratch[1];
    Vec3 local = rot * (impactPoint - pos);

    playSound(1, (float)fp::exp(fp::log(volume * (1.0f / 140.0f)) * -0.25f), 0.25f, 0);
    if (g_menuSelection == 0)
        g_menuSelection = tag;

    Vec3 seeds[5];
    float spread = 0.3f;
    for (int i = 0; i < 5; ++i) {
        do {
            float z = g_random.next() * 2.0f - 1.0f;
            float y = g_random.next() * 2.0f - 1.0f;
            float x = g_random.next() * 2.0f - 1.0f;
            seeds[i] = V3(x, y, z) * spread * radius + local;
        } while (!contains(seeds[i]));
    }

    for (int k = 0; k < 5; ++k) {
        Body *src = this;
        for (int i = 0; i < 5; ++i) {
            if (k == i)
                continue;
            Body *dst = scratchA;
            if (i == 4 || (i == 3 && k == 4)) {
                // the last cut of a cell writes straight into the new body
                dst = g_bodyEnd;
                dst->allocGeometry(0x100, 0x400, 0x100);
            }
            Vec3 n = -seeds[i] + seeds[k];
            Vec3 mid = seeds[i] + seeds[k];
            dst->clipFrom(src, n, (n.y * mid.y + n.z * mid.z + n.x * mid.x) * 0.5f);
            src = scratchA;
            Body *t = scratchA;
            scratchA = scratchB;
            scratchB = t;
        }

        Body *piece = g_bodyEnd;
        if (piece->faceEnd == piece->faceBegin) {
            debugPrint("halott", 0); // "dead"
            continue;
        }

        piece->material = material;
        piece->uvScale = uvScale;
        piece->init();
        piece->rebuildAfterCut(-1);
        Vec3 offset = piece->centroid;
        float push = 1.01f;
        piece->pos = pos + (offset * push) * rot;
        piece->init();
        piece->scaleMass(density);
        piece->vel = vel;
        piece->angVel = angVel;
        piece->rot = rot;
        piece->contacts = nullptr;
        piece->uvOffset = uvOffset + offset;
        piece->sound = sound;
        piece->soundVolume = soundVolume;
        if (g_fragmentHardening)
            piece->breakThreshold = breakThreshold * 3.0f;

        for (Joint *j = g_joints; j < g_jointEnd; ++j) {
            for (int side = 0; side < 2; ++side) {
                Body **body = side ? &j->b : &j->a;
                Vec3 *anchor = side ? &j->anchorB : &j->anchorA;
                if (*body != this)
                    continue;
                int nearest = -1;
                float best = 1e36f;
                for (int m = 0; m < 5; ++m) {
                    float d2 = (seeds[m] - *anchor).lengthSq();
                    if (d2 < best) {
                        best = d2;
                        nearest = m;
                    }
                }
                if (nearest == k) {
                    *body = piece;
                    anchor->x = anchor->x - offset.x;
                    anchor->y = anchor->y - offset.y;
                    anchor->z = anchor->z - offset.z;
                }
            }
        }
        ++g_bodyEnd;
    }

    removed = 1;
    return true;
}
