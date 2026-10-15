// Runs the texture generator outside the game and writes the same
// tex00000.tga .. tex00022.tga cache files the game writes on first start
// (into the current directory), for comparison with the original's output.
//
// Build (x86 developer prompt), from the repository root:
//   cl /nologo /O2 /arch:IA32 /fp:precise /EHsc /D_CRT_SECURE_NO_WARNINGS ^
//      tools\texgen_dump.cpp src\render\texgen.cpp /Fe:texgen_dump.exe
#include "../src/render/texgen.h"
#include "../src/generated/texture_programs.inc"

#include <float.h>

static const unsigned char *const kPrograms[] = {
    kAtg_44eae0, kAtg_44ebc0, kAtg_44f4b0, kAtg_44e830, kAtg_44ecb0, kAtg_44ed50,
    kAtg_44ecb0, kAtg_44edd0, kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740,
    kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740,
    kAtg_44ecb0, kAtg_44ee40, kAtg_44e9f0, kAtg_44f550, kAtg_44e520, nullptr,
};

static void __stdcall progress(float f)
{
    printf("\r%3d%%", (int)(f * 100.0f));
}

int main(int argc, char **argv)
{
    // The FPU state Direct3D 9 sets up when the device is created.
    unsigned int cw;
    _controlfp_s(&cw, _PC_24 | _RC_NEAR, _MCW_PC | _MCW_RC);
    g_texgenCacheTga = 1;
    g_texgenMmxSampler = argc > 1 && strcmp(argv[1], "-float") == 0 ? 0 : 1;
    texgenGenerate(kPrograms, progress);
    printf("\ndone\n");
    return 0;
}
