// "ATG" procedural texture generator (0x419160 - 0x41c543).
#pragma once

#include "../core/common.h"

// Progress callback, called with done/total after every instruction.
typedef void(__stdcall *TexgenProgress)(float fraction);

extern char g_texgenMmxSampler;  // @ 0xd102d0 use the MMX bilinear sampler
extern char g_texgenCacheTga;    // @ 0xd102d1 load/save generated textures as texNNNNN.tga

// Runs every program of the null terminated list and returns a malloc'd array
// with one malloc'd 256x256 X8R8G8B8 image per program (never freed).
unsigned **texgenGenerate(const unsigned char *const *programs, TexgenProgress progress); // @ 0x419980
