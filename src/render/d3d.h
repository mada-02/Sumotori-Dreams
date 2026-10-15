#pragma once

#include "../core/vecmath.h"
#include <d3d9.h>

struct DisplayMode {
    int width;
    int height;
    int bitsPerPixel;
    int refreshRate;
};

extern IDirect3D9 *g_d3d;                 // @ 0x4571e4
extern IDirect3DDevice9 *g_device;        // @ 0x4571ec
extern IDirect3DSurface9 *g_backBuffer;   // @ 0x4571e0
extern D3DCAPS9 g_caps;                   // @ 0x457200
extern int g_screenWidth;                 // @ 0x457334
extern int g_screenHeight;                // @ 0x457338
extern int g_screenBits;                  // @ 0x4571f4
extern int g_screenRefresh;               // @ 0x4571f0
extern char g_windowed;                   // @ 0x45733c
extern int g_windowWidth;                 // @ 0x4533e4
extern int g_windowHeight;                // @ 0x4533e8
extern float g_aspect;                    // @ 0x4533f0

// Picking helpers derived from the projection.
extern float g_pickOffsetX;               // @ 0x45509c
extern float g_pickOffsetY;               // @ 0x455094
extern float g_pickScaleX;                // @ 0x4550a0
extern float g_pickScaleY;                // @ 0x455098

extern Vec3 g_renderPos;                  // @ 0x4550a4
extern Mat3 g_renderRot;                  // @ 0x4550b0

void setProjection();                                         // @ 0x40386a
void setViewTransform(const Vec3 &translation, const Mat3 &rot); // @ 0x40397a
void applyRenderView();                                       // @ 0x4039f6
void enumerateDisplayModes(const GUID *adapter, DisplayMode **modes, int *count); // @ 0x403a86
HWND createMainWindow(HINSTANCE instance);                    // @ 0x403bb8
void initDirect3D();                                          // @ 0x403c36
int renderTextToBitmap(unsigned *pixels, const char *text, int x, int y, int pitch,
                       int width, int height, int pointSize, unsigned color,
                       unsigned background, const char *font); // @ 0x403e16

IDirect3DTexture9 *createTexture(const void *pixels, int width, int height, int levels); // @ 0x415a5c
IDirect3DTexture9 *createNormalMap(const unsigned char *pixels, int width, int height, int depth); // @ 0x415ae1
void setTexture(int stage, IDirect3DTexture9 *texture);      // @ 0x415c17
void saveScreenshot();                                        // @ 0x414f2b
void saveScreenshotAs(const char *prefix, int startIndex);    // @ 0x4151c2
