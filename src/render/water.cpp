// The water height field.
#include "water.h"
#include "scene.h"
#include "../game/camera.h"
#include "../game/game.h"

char g_waterEnabled;
float g_waterBias;
ArrayList<float> g_waterHeight;
ArrayList<float> g_waterVelocity;
int g_waterGridW = 128;
int g_waterGridH = 64;
float g_waterCellSize = 1.0f;

// @ 0x40c179
// Two triangles per cell, shaded by the reflected view vector, alpha blended
// over the scene.
void waterRender()
{
    if (g_waterHeight.empty())
        return;

    const int W = g_waterGridW;
    const int cornerIndex[6] = {0, 1, W, 1, W + 1, W};
    const int cornerX[6] = {0, 1, 0, 1, 1, 0};
    const int cornerZ[6] = {0, 0, 1, 0, 1, 1};

    SceneVertex *v;
    g_sceneVB->Lock(0, g_waterGridH * g_waterGridW * 6 * sizeof(SceneVertex), (void **)&v, D3DLOCK_DISCARD);
    int index = 0;
    for (int z = 0; z < g_waterGridH - 1; ++z) {
        for (int x = 0; x < g_waterGridW - 1; ++x) {
            float zf = (float)z;
            float h = g_waterHeight.at(index);
            float hDown = g_waterHeight.at(index + g_waterGridW);
            float h0 = g_waterHeight.at(index);
            float hRight = g_waterHeight.at(index + 1);
            Vec3 n = V3(h0 - hRight, g_waterCellSize, h - hDown);
            n.normalize();

            Vec3 p = V3(x * g_waterCellSize, g_waterHeight.at(index), zf * g_waterCellSize);
            Vec3 eye = p - g_viewPos;
            float d = (eye.z * n.z + eye.y * n.y + eye.x * n.x) * 2.0f;
            Vec3 r = eye - n * d;
            r.normalize();
            unsigned color = fp::ftol(r.y * 31.0f + 32.0f) * 0x1030401 + 0xc0;

            for (int k = 0; k < 6; ++k) {
                v->color = color;
                float hk = g_waterHeight.at(cornerIndex[k] + index);
                int zk = cornerZ[k] + z;
                int xk = cornerX[k] + x;
                v->pos = V3(xk * g_waterCellSize, hk, zk * g_waterCellSize);
                v->u = 0.0f;
                v->v = 0.0f;
                ++v;
            }
            ++index;
        }
        ++index;
    }
    g_sceneVB->Unlock();

    IDirect3DDevice9 *d = g_device;
    d->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    d->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
    d->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    d->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    d->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
    d->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
    d->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    d->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
    d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
    d->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    d->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    d->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    d->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (g_waterGridH - 1) * (g_waterGridW - 1) * 2);
    d->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

// @ 0x4165db
void waterUpdate()
{
    if (g_frame % 3 != 0)
        return;
    if (g_waterHeight.empty())
        return;

    for (int z = 0; z < g_waterGridH - 1; ++z) {
        for (int x = 0; x < g_waterGridW - 1; ++x) {
            float *h = &g_waterHeight.at(g_waterGridW * z + x);
            float flow = (*h - g_waterHeight.at(g_waterGridW * z + x + 1)) * 0.09f;
            float *v = &g_waterVelocity.at(g_waterGridW * z + x);
            *v = *v - flow;
            v = &g_waterVelocity.at(g_waterGridW * z + x + 1);
            *v = flow + *v;

            h = &g_waterHeight.at(g_waterGridW * z + x);
            flow = (*h - g_waterHeight.at((z + 1) * g_waterGridW + x)) * 0.09f;
            v = &g_waterVelocity.at(g_waterGridW * z + x);
            *v = *v - flow;
            v = &g_waterVelocity.at((z + 1) * g_waterGridW + x);
            *v = flow + *v;
        }
    }

    double sum = 0.0;
    for (int i = 0; i < g_waterGridW * g_waterGridH; ++i) {
        sum = g_waterHeight.at(i) + sum;
        float *h = &g_waterHeight.at(i);
        *h = *h + g_waterVelocity.at(i) + g_waterBias;
        float *v = &g_waterVelocity.at(i);
        *v = *v * 0.997f;
    }
    int cells = g_waterGridW * g_waterGridH;
    g_waterBias = (float)((g_waterLevel - sum / cells) * 0.10000000149011612);
}

// @ 0x416810
void waterCreate()
{
    g_waterLevel = 23.0f;
    g_waterEnabled = 1;
    g_waterHeight.resize(g_waterGridH * g_waterGridW);
    g_waterVelocity.resize(g_waterGridH * g_waterGridW);
    for (int i = 0; i < g_waterGridH * g_waterGridW; ++i) {
        float s = (float)fp::sin(i * 0.5f);
        g_waterHeight.at(i) = (float)(s * 0.04 + g_waterLevel);
        g_waterVelocity.at(i) = 0.0f;
    }
}
