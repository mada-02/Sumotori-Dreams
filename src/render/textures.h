// Texture set-up: the procedural material textures, the menu signs and the
// font atlas.
#pragma once

#include "d3d.h"

extern IDirect3DTexture9 *g_gradientTexture;   // @ 0xc0f228 64x16 (never used)
extern IDirect3DTexture9 *g_rampTexture;       // @ 0xd0f338 32x1 (never used)

void createGradientTexture();                  // @ 0x4157bd
void createRampTexture();                      // @ 0x4156c8
void loadTextures();                           // @ 0x4158ca
