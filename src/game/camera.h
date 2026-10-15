#pragma once

#include "../core/vecmath.h"

// Active view used by the renderer and the HUD.
extern Vec3 g_viewPos;           // @ 0xc06948
extern Mat3 g_viewRot;           // @ 0xc06954
extern Vec3 g_viewFocus;         // @ 0xc06820 replay focus point (free camera steers towards it)
extern int g_cameraMode;         // @ 0xc0682c 0 game, 1 record, 2 playback, 3 free-camera playback

// Gameplay camera state
extern Vec3 g_camPos;            // @ 0x454fe0
extern Vec3 g_camAngles;         // @ 0x45503c
extern float g_camPitch;         // @ 0x4533d8
extern float g_camPitchOffset;   // @ 0x4533dc
extern float g_camDistance;      // @ 0x4533e0

void freeCameraReset();                              // @ 0x402784
void freeCameraSet(const Vec3 &pos, float yaw);      // @ 0x4027fd
void freeCameraResetAt(const Vec3 &pos, float yaw);  // @ 0x402827
int freeCameraUpdate(int frames);                    // @ 0x402846
void gameCameraReset();                              // @ 0x402d01
void gameCameraUpdate();                             // @ 0x402f1b
