#pragma once

#include "d3d.h"

struct Body;

// FVF 0x142: XYZ | DIFFUSE | TEX1
struct SceneVertex {
    Vec3 pos;
    unsigned color;
    float u, v;
};

// FVF 0x42: XYZ | DIFFUSE
struct LineVertex {
    Vec3 pos;
    unsigned color;
};

enum { MAX_MATERIALS = 128 };

extern IDirect3DTexture9 *g_materialTextures[MAX_MATERIALS][2]; // @ 0xc0f230 [normal map, diffuse]
extern IDirect3DTexture9 *g_fontTexture;     // @ 0xc0f22c
extern unsigned g_fadeColor;                 // @ 0xac66f4 texture factor of the colour pass
extern float g_shadowLength;                 // @ 0xc06808
extern int g_lightCount;                     // @ 0x453700
extern int g_shadowsEnabled;                 // @ 0x4536fc
extern Vec3 g_lightDir;                      // @ 0xa466e4
extern LineVertex *g_lineCursor;             // @ 0xbe67f8
extern LineVertex g_lines[0x4000][2];        // @ 0xa466f0
extern IDirect3DVertexBuffer9 *g_sceneVB;    // @ 0xc06800 dynamic triangle list (SceneVertex)

void createSceneBuffers();                                   // @ 0x40b83f
void textBegin();                                            // @ 0x40b97a
void drawText(float x, float y, const char *text, unsigned color); // @ 0x40b985
void textFlush();                                            // @ 0x40bfb0
void bodyEmitTriangles(Body *body);                          // @ 0x40c5c7
void emitAllBodies();                                        // @ 0x408e2a
void renderFrame();                                          // @ 0x40cac4
