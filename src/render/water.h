// The water of the "I go downstairs" style arenas: a 128 x 64 height field
// relaxed every third frame and coupled with floating bodies.
#pragma once

#include "../core/common.h"

extern char g_waterEnabled;                // @ 0xd0f3b8
extern float g_waterBias;                  // @ 0xd0f3b4 keeps the mean height at g_waterLevel
extern ArrayList<float> g_waterHeight;     // @ 0xd0f3bc
extern ArrayList<float> g_waterVelocity;   // @ 0xd0f3c8
extern int g_waterGridW;                   // @ 0x453cc8 (128)
extern int g_waterGridH;                   // @ 0x453ccc (64)
extern float g_waterCellSize;              // @ 0x453cd0 (1.0)

void waterRender();                        // @ 0x40c179
void waterUpdate();                        // @ 0x4165db
void waterCreate();                        // @ 0x416810
