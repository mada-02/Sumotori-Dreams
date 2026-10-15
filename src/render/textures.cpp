// Texture set-up: the procedural material textures, the menu signs and the
// font atlas.
#include "textures.h"
#include "scene.h"
#include "texgen.h"

#include "../generated/texture_programs.inc"

IDirect3DTexture9 *g_gradientTexture;           // @ 0xc0f228
IDirect3DTexture9 *g_rampTexture;               // @ 0xd0f338

static unsigned s_pixels[0x10000];              // @ 0xc0f338 scratch image

// @ 0x453890
// Material textures in pairs (normal map source, diffuse).
static const unsigned char *const kTexturePrograms[] = {
    kAtg_44eae0, kAtg_44ebc0, kAtg_44f4b0, kAtg_44e830, kAtg_44ecb0, kAtg_44ed50,
    kAtg_44ecb0, kAtg_44edd0, kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740,
    kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740, kAtg_44e7c0, kAtg_44e740,
    kAtg_44ecb0, kAtg_44ee40, kAtg_44e9f0, kAtg_44f550, kAtg_44e520, nullptr,
};

// @ 0x4538f0
// Text painted onto the menu signs (textures 8..17, one group per pair).
static const char kSignText[5][6][24] = {
    {"2 players duel", "2 players & 1 comp.", "2 player & 2 comp.", "4 computers"},
    {"You vs. Computer", "You and 2 comp.", "You & 3 comp.", "2 Computers"},
    {"Arena selection", "AI mode: walk", "AI mode: stand", "Quit"},
    {"Default dojo", "Kitchen party", "Roof dancers", "play seesaw"},
    {"Up on the stage", "I go downstairs"},
};

// @ 0x4157bd
// 16 rows of 64 texels fading from white with per-channel factors.
void createGradientTexture()
{
    unsigned *p = s_pixels;
    for (int row = 0; row < 16; ++row) {
        float r = 255.0f, g = 255.0f, b = 255.0f;
        float kr = (float)fp::exp(fp::log(0.009999999776482582) * 0.015625f);
        float kg = (float)fp::exp(fp::log(0.019999999552965164) * 0.015625f);
        float kb = (float)fp::exp(fp::log(0.05000000074505806) * 0.015625f);
        if (row > 8) {
            kg = kb;
            kb = kr;
        }
        for (int x = 0x40; x != 0; --x) {
            unsigned c = fp::ftol(r);
            c = (c << 8) + fp::ftol(g);
            c = (c << 8) + fp::ftol(b);
            *p++ = c;
            r *= kr;
            g *= kg;
            b *= kb;
        }
    }
    g_gradientTexture = createTexture(s_pixels, 0x40, 0x10, 0);
}

// @ 0x4156c8
void createRampTexture()
{
    float r = 255.0f, g = 255.0f, b = 255.0f;
    float kr = (float)fp::exp(fp::log(0.019999999552965164) * 0.03125f);
    float kg = (float)fp::exp(fp::log(0.019999999552965164) * 0.03125f);
    float kb = (float)fp::exp(fp::log(0.019999999552965164) * 0.03125f);
    unsigned *p = s_pixels;
    for (int x = 0x20; x != 0; --x) {
        unsigned c = fp::ftol(r - 5.1f);
        c = (c << 8) + fp::ftol(g - 5.1f);
        c = (c << 8) + fp::ftol(b - 5.1f);
        *p++ = c;
        r *= kr;
        g *= kg;
        b *= kb;
    }
    g_rampTexture = createTexture(s_pixels, 0x20, 1, 1);
}

// @ 0x4158c7
static void __stdcall ignoreProgress(float) {}

// @ 0x4158ca
void loadTextures()
{
    createGradientTexture();
    createRampTexture();
    g_texgenCacheTga = 1;
    g_texgenMmxSampler = 1;
    unsigned **images = texgenGenerate(kTexturePrograms, ignoreProgress);

    IDirect3DTexture9 **slot = &g_materialTextures[0][0];
    for (int i = 0; kTexturePrograms[i]; ++i) {
        unsigned *pixels = images[i];
        if (i > 7 && i < 18) {
            const char *line = kSignText[i / 2 - 4][0];
            if (*line) {
                int y = 6;
                do {
                    renderTextToBitmap(pixels, line, 10, y, 0x100, 0xf6, 0x20, 0x18,
                                       (i & 1) * 0x7f7f7f, 0xffffff, "Times New Roman");
                    y += 0x2a;
                    line += 24;
                } while (*line);
            }
        }
        if ((i & 1) == 0)
            slot[i] = createNormalMap((const unsigned char *)pixels, 0x100, 0x100, -100);
        else
            slot[i] = createTexture(pixels, 0x100, 0x100, 0);
    }

    // Font atlas: 16x16 cells of Lucida Console 12, black on white, inverted.
    for (int i = 0; i < 0x10000; ++i)
        s_pixels[i] = 0xffffffff;
    for (int c = 0; c < 0x100; ++c) {
        char text[2] = {(char)c, 0};
        renderTextToBitmap(s_pixels, text, (c & 15) << 4, (c / 16) << 4, 0x100, 0x10, 0x10, 0xc,
                           0, 0xffffff, "Lucida Console");
    }
    for (unsigned *p = s_pixels; p < s_pixels + 0x10000; ++p)
        *p = ~*p;
    g_fontTexture = createTexture(s_pixels, 0x100, 0x100, 0);
}
