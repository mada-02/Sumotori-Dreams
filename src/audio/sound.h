// Sound effects: GSM 6.10 samples decoded with the ACM into DirectSound
// buffers, played through pools of duplicated buffers.
#pragma once

#define DIRECTSOUND_VERSION 0x0800
#include "../core/common.h"
#include <mmreg.h>
#include <dsound.h>

enum { SOUND_VOICES = 120 };

// 0x1e8 bytes
struct SoundChannel {
    int frequency;                                 // +0x000 base playback rate
    IDirectSoundBuffer *buffers[SOUND_VOICES];     // +0x004 [0] = decoded sample, others duplicates
    int cursor;                                    // +0x1e4

    int play(float pitch, float volume, int slot); // @ 0x415216
};

extern SoundChannel g_soundChannels[8];            // @ 0xc0a4f0
extern IDirectSound8 *g_directSound;               // @ 0xc0f1fc
extern IDirectSoundBuffer *g_primaryBuffer;        // @ 0xc0e1f4
extern IDirectSoundBuffer **g_slotVoices[8];       // @ 0xc0f200 voice to stop when a slot is reused
extern char g_soundEnabled;                        // @ 0xc0f220 user option
extern int g_soundReady;                           // @ 0xc0f224
extern int g_soundHardware;                        // @ 0x453868 1 = try hardware buffers first

void releaseOldestVoice();                                    // @ 0x4151d9
void playSound(int id, float pitch, float volume, int slot);  // @ 0x41538b
bool loadSounds();                                            // @ 0x4153f4
bool soundInit();                                             // @ 0x4155de
bool soundStart();                                            // @ 0x41569a
