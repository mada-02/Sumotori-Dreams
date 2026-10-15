// Scene rendering: per-material batching, DOT3 bump lighting with one
// stencil shadow volume pass per light, HUD text and debug lines.
#include "scene.h"
#include "water.h"
#include "../game/camera.h"
#include "../game/game.h"
#include "../physics/world.h"

static const DWORD kSceneFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1; // @ 0x4536ec
static const DWORD kLineFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;               // @ 0x4536f0
static const DWORD kShadowFvf = D3DFVF_XYZ;                              // @ 0x4536f4

IDirect3DTexture9 *g_materialTextures[MAX_MATERIALS][2]; // @ 0xc0f230
IDirect3DTexture9 *g_fontTexture;                        // @ 0xc0f22c
unsigned g_fadeColor;                                    // @ 0xac66f4
float g_shadowLength;                                    // @ 0xc06808
int g_lightCount = 12;                                   // @ 0x453700
int g_shadowsEnabled = 1;                                // @ 0x4536fc
Vec3 g_lightDir;                                         // @ 0xa466e4
LineVertex *g_lineCursor;                                // @ 0xbe67f8
LineVertex g_lines[0x4000][2];                           // @ 0xa466f0

IDirect3DVertexBuffer9 *g_sceneVB;                       // @ 0xc06800
static IDirect3DVertexBuffer9 *g_shadowVB;               // @ 0xa466e0

static SceneVertex *g_textCursor;                        // @ 0xc06804
static SceneVertex g_textVerts[0x6000];                  // @ 0x9b66e0

static ArrayList<Vec3> g_worldVerts;                     // @ 0xc06810

struct TriangleRef {
    short index;      // index within its material
    short material;
};

static SceneVertex g_triangles[0x8000][3];               // @ 0x7765e0
static SceneVertex *g_triangleCursor;                    // @ 0x7765d8
static Vec3 g_shadowVerts[0x18000];                      // @ 0xac66f8
static Vec3 *g_shadowCursor;                             // @ 0x7765dc
static TriangleRef g_triangleRefs[0x8000];               // @ 0xbe6800
static TriangleRef *g_triangleRefCursor;                 // @ 0xac66f0
static short g_materialCount[MAX_MATERIALS];             // @ 0xbe66f8
static short g_materialStart[MAX_MATERIALS];             // @ 0x9b65e0
static short g_sortedTriangles[0x8000];                  // @ 0x7665d8

// @ 0x40b83f
void createSceneBuffers()
{
    setProjection();
    g_device->CreateVertexBuffer(0x240000, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, kSceneFvf,
                                 D3DPOOL_DEFAULT, &g_sceneVB, nullptr);
    g_device->CreateVertexBuffer(0x120000, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, kShadowFvf,
                                 D3DPOOL_DEFAULT, &g_shadowVB, nullptr);
}

// @ 0x40b88c  Maps a screen position to a point in front of the camera,
// adding the "drunk" wobble of the HUD text.
static Vec3 textWarp(const Vec3 &in)
{
    float t = (float)g_frame * 0.02f;
    float a = (float)(fp::cos(t * 1.37f) + t);
    float b = (float)(fp::sin(t * 1.77f) + t);
    Vec3 p = in;
    p.normalize();
    p.z = 1.0f;
    a = a * 1.1f;
    for (int i = 3; i != 0; --i) {
        p.x = (float)(fp::sin(p.y * 10.0f + b) * 0.004f + p.x);
        p.y = (float)(fp::cos(p.x * 10.0f + a) * 0.004f + p.y);
    }
    return ((p + in) * g_viewRot) + g_viewPos;
}

// @ 0x40b97a
void textBegin()
{
    g_textCursor = g_textVerts;
}

static inline void textVertex(const Vec3 &pos, unsigned color, float u, float v)
{
    g_textCursor->pos = pos;
    g_textCursor->color = color;
    g_textCursor->u = u;
    g_textCursor->v = v;
    ++g_textCursor;
}

// @ 0x40b985  Screen coordinates are in units of the view frustum (x right,
// y up); every glyph is emitted three times: two dark offset copies form the
// drop shadow, the third carries the colour.
void drawText(float x, float y, const char *text, unsigned color)
{
    Vec3 offset = V3(0.004f, 0.004f, 0.0f) * g_viewRot;
    float startX = x;
    unsigned shadow = color & 0xff000000;
    const unsigned char *p = (const unsigned char *)text;
    while (*p != 0) {
        Vec3 c0 = textWarp(V3(x, y, 1.0f));
        float right = x + 0.025f;
        Vec3 c1 = textWarp(V3(right, y, 1.0f));
        float bottom = y - 0.038f;
        Vec3 c2 = textWarp(V3(right, bottom, 1.0f));
        Vec3 c3 = textWarp(V3(x, bottom, 1.0f));
        int row = (int)(signed char)*p / 16;
        float u0 = (float)(int)(signed char)(*p & 0xf) * 0.0625f;
        float v0 = (float)row * 0.0625f;
        float u1 = u0 + 0.0625f;
        float v1 = v0 + 0.0625f;

        textVertex(c0 - offset, shadow, u0, v0);
        textVertex(c1 - offset, shadow, u1, v0);
        textVertex(c3 - offset, shadow, u0, v1);
        textVertex(c1 - offset, shadow, u1, v0);
        textVertex(c2 - offset, shadow, u1, v1);
        textVertex(c3 - offset, shadow, u0, v1);

        textVertex(c0 + offset, shadow, u0, v0);
        textVertex(c1 + offset, shadow, u1, v0);
        textVertex(c3 + offset, shadow, u0, v1);
        textVertex(c1 + offset, shadow, u1, v0);
        textVertex(c2 + offset, shadow, u1, v1);
        textVertex(c3 + offset, shadow, u0, v1);

        textVertex(c0, color, u0, v0);
        textVertex(c1, color, u1, v0);
        textVertex(c3, color, u0, v1);
        textVertex(c1, color, u1, v0);
        textVertex(c2, color, u1, v1);
        textVertex(c3, color, u0, v1);

        x = right;
        ++p;
        if (*p == '\n') {
            x = startX;
            y = bottom;
            ++p;
        }
    }
}

// @ 0x40bfb0
void textFlush()
{
    g_device->SetFVF(kSceneFvf);
    int count = (int)(g_textCursor - g_textVerts);
    if (count != 0) {
        g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        g_device->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        g_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        g_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        g_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        g_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        g_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        g_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        g_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        setTexture(0, g_fontTexture);
        g_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, count / 3, g_textVerts, sizeof(SceneVertex));
    }
}

// @ 0x40c5c7  Emits the lit triangles of a body plus the shadow volume quads
// of its silhouette edges with respect to g_lightDir.
void bodyEmitTriangles(Body *body)
{
    if (body->removed != 0)
        return;

    g_worldVerts.resize((int)(body->vertEnd - body->vertBegin) + 1);
    Vec3 *world = &g_worldVerts.at(0);
    for (Vertex *v = body->vertBegin; v < body->vertEnd; ++v)
        *world++ = (v->pos * body->rot) + body->pos;

    Vec3 light = body->rot * g_lightDir;

    for (Face *f = body->faceBegin; f < body->faceEnd; ++f) {
        f->frontFacing = 0.0f < light.y * f->normal.y + light.z * f->normal.z + light.x * f->normal.x;

        Vec3 n = f->normal;
        n.normalize();
        Vec3 ref = V3(1.0f, 0.0f, 0.0f);
        if (n.x * n.x > n.y * n.y || n.z * n.z > n.y * n.y)
            ref = V3(0.0f, 1.0f, 0.0f);
        Vec3 tangent = ref.cross(n);
        tangent.normalize();
        Vec3 bitangent = tangent.cross(n);

        // Light vector in tangent space, packed into the vertex colour.
        int ln = fp::ftol((light.z * n.z + light.y * n.y + light.x * n.x) * -127.0f + 128.0f);
        int lb = fp::ftol((light.y * bitangent.y + light.z * bitangent.z + light.x * bitangent.x) * 127.0f - 128.0f);
        int lt = fp::ftol(128.0f - (light.y * tangent.y + light.z * tangent.z + light.x * tangent.x) * 127.0f);
        unsigned color = (unsigned)(lt - ((-ln << 8) + lb) * 256);

        tangent.x = tangent.x * body->uvScale;
        tangent.y = tangent.y * body->uvScale;
        tangent.z = tangent.z * body->uvScale;
        bitangent.x = bitangent.x * body->uvScale;
        bitangent.y = bitangent.y * body->uvScale;
        bitangent.z = bitangent.z * body->uvScale;

        for (int k = 2; k < f->count; ++k) {
            int corner[3] = { 0, k - 1, k };
            g_triangleRefCursor->index = g_materialCount[body->material];
            ++g_materialCount[body->material];
            g_triangleRefCursor->material = (short)body->material;
            ++g_triangleRefCursor;
            for (int j = 0; j < 3; ++j) {
                int idx = f->loop[corner[j]].index;
                g_triangleCursor->pos = g_worldVerts.at(idx);
                Vec3 local = body->vertBegin[idx].pos + body->uvOffset;
                g_triangleCursor->u = tangent.z * local.z + tangent.y * local.y + tangent.x * local.x;
                local = body->vertBegin[idx].pos + body->uvOffset;
                g_triangleCursor->v = bitangent.z * local.z + bitangent.y * local.y + bitangent.x * local.x;
                g_triangleCursor->color = color;
                ++g_triangleCursor;
            }
        }
    }

    float extrude = -g_shadowLength;
    Vec3 extrusion = g_lightDir * extrude;
    for (Edge *e = body->edgeBegin; e < body->edgeEnd; ++e) {
        int side;
        if (e->faceA->frontFacing == 0 && e->faceB->frontFacing == 1)
            side = 0;
        else if (e->faceB->frontFacing == 0 && e->faceA->frontFacing == 1)
            side = 1;
        else
            continue;
        Vec3 base[2];
        Vec3 farPt[2];
        base[side ^ 1] = g_worldVerts.at(e->v0);
        base[side] = g_worldVerts.at(e->v1);
        farPt[side ^ 1] = g_worldVerts.at(e->v1) + extrusion;
        farPt[side] = g_worldVerts.at(e->v0) + extrusion;
        *g_shadowCursor++ = base[0];
        *g_shadowCursor++ = base[1];
        *g_shadowCursor++ = farPt[0];
        *g_shadowCursor++ = base[0];
        *g_shadowCursor++ = farPt[0];
        *g_shadowCursor++ = farPt[1];
    }
}

// @ 0x408e2a
void emitAllBodies()
{
    for (Body *b = g_bodies; b < g_bodyEnd; ++b)
        bodyEmitTriangles(b);
}

// @ 0x40cac4
void renderFrame()
{
    IDirect3DDevice9 *d = g_device;
    d->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    d->SetRenderState(D3DRS_LIGHTING, FALSE);
    d->SetRenderState(D3DRS_CLIPPING, TRUE);
    d->SetRenderState(D3DRS_ZENABLE, TRUE);
    d->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    d->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    for (int stage = 0; stage < 6; ++stage) {
        d->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        d->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        d->SetSamplerState(stage, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
    }

    g_renderRot = g_viewRot;
    g_renderPos = g_viewPos;
    applyRenderView();

    d->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
             ((((int)g_fadeColor >> 2) & 0x3f) * 0x80c1) & 0x3f3f3f, 1.0f, 0);
    d->BeginScene();

    bool firstPass = true;
    int passes = g_lightCount;
    int triangleCount = 0;
    if (passes > 0) {
        unsigned passColor = (((0x120 / (passes + 1)) + 8) / 16) * 0x80706;
        float passCount = (float)passes;
        for (int pass = 0; pass < passes; ++pass) {
            g_lightDir = V3(0.3f, 1.0f, 0.5f);
            Vec3 spin = V3(0.0f, (float)pass * 5.2f / passCount, 0.0f);
            g_lightDir.rotate(spin);
            g_lightDir.normalize();

            memset(g_materialCount, 0, sizeof(g_materialCount));
            g_triangleRefCursor = g_triangleRefs;
            g_triangleCursor = &g_triangles[0][0];
            g_shadowCursor = g_shadowVerts;
            emitAllBodies();

            int shadowTriangles = (int)(g_shadowCursor - g_shadowVerts) / 3;
            void *locked;
            int shadowBytes = shadowTriangles * 0x24;
            g_shadowVB->Lock(0, shadowBytes, &locked, D3DLOCK_DISCARD);
            memcpy(locked, g_shadowVerts, shadowBytes);
            g_shadowVB->Unlock();

            int running = 0;
            for (int m = 0; m < MAX_MATERIALS; ++m) {
                g_materialStart[m] = (short)running;
                running += g_materialCount[m];
            }
            triangleCount = running;
            int refs = 0;
            for (TriangleRef *r = g_triangleRefs; r < g_triangleRefCursor; ++r, ++refs)
                g_sortedTriangles[g_materialStart[r->material] + r->index] = (short)refs;

            SceneVertex *dst;
            g_sceneVB->Lock(0, refs * 0x48, (void **)&dst, D3DLOCK_DISCARD);
            for (int i = 0; i < refs; ++i) {
                short t = g_sortedTriangles[i];
                *dst++ = g_triangles[t][0];
                *dst++ = g_triangles[t][1];
                *dst++ = g_triangles[t][2];
            }
            g_sceneVB->Unlock();

            d->SetFVF(kSceneFvf);
            d->SetStreamSource(0, g_sceneVB, 0, sizeof(SceneVertex));
            if (g_shadowsEnabled != 0) {
                d->SetRenderState(D3DRS_STENCILENABLE, TRUE);
                d->SetRenderState(D3DRS_STENCILREF, 8);
                d->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
                d->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
                d->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
                d->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_REPLACE);
                d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
            }
            d->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
            d->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            d->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
            d->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
            if (firstPass) {
                d->SetRenderState(D3DRS_TEXTUREFACTOR, 0x203040);
            } else {
                d->SetRenderState(D3DRS_TEXTUREFACTOR, 0);
                d->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
            }
            if (g_shadowsEnabled != 0 || firstPass)
                d->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangleCount);

            d->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
            d->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
            d->SetRenderState(D3DRS_STENCILENABLE, TRUE);
            d->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
            d->SetRenderState(D3DRS_STENCILREF, 8);
            d->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
            d->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
            d->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCR);
            d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
            if (g_shadowsEnabled != 0) {
                d->SetFVF(kShadowFvf);
                d->SetStreamSource(0, g_shadowVB, 0, sizeof(Vec3));
                d->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
                d->DrawPrimitive(D3DPT_TRIANGLELIST, 0, shadowTriangles);
                d->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
                d->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
                d->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_DECR);
                d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
                d->DrawPrimitive(D3DPT_TRIANGLELIST, 0, shadowTriangles);
            }
            d->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
            if (firstPass) {
                d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
                d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
                firstPass = false;
            }

            d->SetFVF(kSceneFvf);
            d->SetStreamSource(0, g_sceneVB, 0, sizeof(SceneVertex));
            if (g_shadowsEnabled != 0) {
                d->SetRenderState(D3DRS_STENCILENABLE, TRUE);
                d->SetRenderState(D3DRS_STENCILREF, 8);
                d->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
                d->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);
                d->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
                d->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
                d->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
            }
            d->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
            d->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            d->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            d->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
            d->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
            d->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
            d->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
            d->SetRenderState(D3DRS_TEXTUREFACTOR, passColor);
            for (int m = 0; m < MAX_MATERIALS; ++m) {
                if (g_materialCount[m] != 0) {
                    setTexture(0, g_materialTextures[m][0]);
                    d->DrawPrimitive(D3DPT_TRIANGLELIST, g_materialStart[m] * 3, g_materialCount[m]);
                }
            }
            d->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            d->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        }
    }

    // Colour pass: modulate the accumulated lighting with the diffuse maps.
    d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
    d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
    d->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    d->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
    d->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    d->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    d->SetRenderState(D3DRS_TEXTUREFACTOR, g_fadeColor);
    for (int m = 0; m < MAX_MATERIALS; ++m) {
        if (g_materialCount[m] != 0) {
            setTexture(0, g_materialTextures[m][1]);
            d->DrawPrimitive(D3DPT_TRIANGLELIST, g_materialStart[m] * 3, g_materialCount[m]);
        }
    }

    if (g_waterEnabled)
        waterRender();
    d->SetTexture(0, nullptr);
    d->SetTexture(1, nullptr);
    textFlush();

    int lines = (int)(g_lineCursor - &g_lines[0][0]) / 2;
    if (lines != 0) {
        d->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        d->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
        d->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        d->SetRenderState(D3DRS_ZENABLE, FALSE);
        d->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        d->SetFVF(kLineFvf);
        d->DrawPrimitiveUP(D3DPT_LINELIST, lines, g_lines, sizeof(LineVertex));
    }
    d->EndScene();
    d->Present(nullptr, nullptr, nullptr, nullptr);
}
