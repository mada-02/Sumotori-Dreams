// Sound effects.
#include "sound.h"
#include "../game/replay.h"
#include "../game/game.h"
#include "../platform/window.h"
#include <msacm.h>

#include "../generated/sound_data.inc"

SoundChannel g_soundChannels[8];
IDirectSound8 *g_directSound;
IDirectSoundBuffer *g_primaryBuffer;
IDirectSoundBuffer **g_slotVoices[8];
char g_soundEnabled;
int g_soundReady;
int g_soundHardware = 1;



// Duplicated voices in creation order; the oldest is released when
// DirectSound runs out of buffers.
static IDirectSoundBuffer **g_voiceQueue[1024];    // @ 0xc0e1f8
static int g_voiceQueueTail;                       // @ 0xc0e1f0
static int g_voiceQueueHead;                       // @ 0xc0f1f8

// @ 0x45386c: the samples, indexed by sound id (null terminated)
static const unsigned char *const kSoundList[] = {
    kWave_4510f0,   // 0
    kWave_44f640,   // 1 breaking
    kWave_4510f0,   // 2
    kWave_4528f0,   // 3
    kWave_44eec0,   // 4
    kWave_4502e0,   // 5
    kWave_44fbf0,   // 6
    nullptr,
};

// @ 0x4151d9
void releaseOldestVoice()
{
    IDirectSoundBuffer **voice = g_voiceQueue[g_voiceQueueTail];
    if (*voice)
        (*voice)->Release();
    *g_voiceQueue[g_voiceQueueTail] = nullptr;
    g_voiceQueueTail = (g_voiceQueueTail + 1) & 0x3ff;
}

// @ 0x415216
int SoundChannel::play(float pitch, float volume, int slot)
{
    if (!g_soundReady)
        return 0;

    // find a voice that is not playing
    for (cursor = 0; buffers[cursor];) {
        DWORD status;
        buffers[cursor]->GetStatus(&status);
        if (!(status & DSBSTATUS_PLAYING))
            break;
        if (++cursor >= SOUND_VOICES)
            break;
    }
    if (cursor == SOUND_VOICES)
        cursor = 0;

    while (buffers[cursor] == nullptr) {
        if (g_directSound->DuplicateSoundBuffer(buffers[0], &buffers[cursor]) != DS_OK) {
            releaseOldestVoice();
        } else {
            g_voiceQueue[g_voiceQueueHead] = &buffers[cursor];
            g_voiceQueueHead = (g_voiceQueueHead + 1) & 0x3ff;
        }
    }

    IDirectSoundBuffer **voice = &buffers[cursor];
    if (*voice) {
        (*voice)->SetFrequency(fp::ftol(frequency * pitch));
        float ln10 = (float)fp::log(10.0);
        buffers[cursor]->SetVolume(fp::ftol(fp::log(volume) / ln10 * 2000.0f));
        buffers[cursor]->SetCurrentPosition(0);
        buffers[cursor]->Play(0, 0, 0);
    }
    if (++cursor == SOUND_VOICES)
        cursor = 0;
    // remembers the voice after the one just started (as the original does)
    g_slotVoices[slot] = &buffers[cursor];
    return 1;
}

// @ 0x41538b
// slot != 0 stops the previous sound started on the same slot.
void playSound(int id, float pitch, float volume, int slot)
{
    replayRecordSound(id, pitch, volume, slot);
    if (slot && g_slotVoices[slot] && *g_slotVoices[slot])
        (*g_slotVoices[slot])->Stop();
    g_soundChannels[id].play(pitch, volume, slot);
}

// @ 0x4153f4
bool loadSounds()
{
    SoundChannel *channel = g_soundChannels;
    for (const unsigned char *const *entry = kSoundList; *entry; ++entry, ++channel) {
        const unsigned char *wave = *entry;
        unsigned char *pcm = (unsigned char *)malloc(0x10000);
        const WAVEFORMATEX *srcFormat = (const WAVEFORMATEX *)(wave + 0x14);

        ACMSTREAMHEADER header;
        memset(&header, 0, sizeof(header));
        header.cbStruct = sizeof(ACMSTREAMHEADER);
        header.pbSrc = (LPBYTE)(wave + 0x3c);
        header.cbSrcLength = *(const DWORD *)(wave + 0x38);
        header.pbDst = pcm;
        header.cbDstLength = 0x10000;

        WAVEFORMATEX format;
        format.cbSize = 0;
        format.wFormatTag = WAVE_FORMAT_PCM;
        format.nChannels = srcFormat->nChannels;
        format.nSamplesPerSec = srcFormat->nSamplesPerSec;
        format.nBlockAlign = (WORD)(format.nChannels * 2);
        format.wBitsPerSample = 16;
        format.nAvgBytesPerSec = format.nBlockAlign * format.nSamplesPerSec;

        // the stream and the decode buffer are never released
        HACMSTREAM stream;
        if (acmStreamOpen(&stream, nullptr, (LPWAVEFORMATEX)srcFormat, &format, nullptr, 0, 0,
                          ACM_STREAMOPENF_NONREALTIME))
            return false;
        if (acmStreamPrepareHeader(stream, &header, 0))
            return false;
        if (acmStreamConvert(stream, &header, ACM_STREAMCONVERTF_START | ACM_STREAMCONVERTF_END))
            return false;

        WAVEFORMATEX bufferFormat = format;
        DWORD rate = format.nSamplesPerSec;
        DSBUFFERDESC desc;
        desc.dwSize = sizeof(DSBUFFERDESC);
        // GETCURRENTPOSITION2 | CTRLVOLUME | CTRLFREQUENCY | CTRL3D | LOCHARDWARE/LOCSOFTWARE
        desc.dwFlags = (g_soundHardware == 0 ? 4 : 0) + 0x100b4;
        desc.dwBufferBytes = header.cbDstLengthUsed;
        desc.dwReserved = 0;
        desc.lpwfxFormat = &bufferFormat;
        desc.guid3DAlgorithm = GUID_NULL;
        if (g_directSound->CreateSoundBuffer(&desc, &channel->buffers[0], nullptr) != DS_OK)
            return false;

        void *p1, *p2;
        DWORD n1, n2;
        channel->buffers[0]->Lock(0, 0, &p1, &n1, &p2, &n2, DSBLOCK_ENTIREBUFFER);
        for (DWORD i = 0; i < header.cbDstLengthUsed; ++i)
            ((unsigned char *)p1)[i] = pcm[i];
        channel->buffers[0]->Unlock(p1, n1, p2, n2);

        memset(&channel->buffers[1], 0, (SOUND_VOICES - 1) * sizeof(IDirectSoundBuffer *));
        channel->cursor = 0;
        channel->frequency = (int)rate / g_timeDivider;
    }
    return true;
}

// @ 0x4155de
bool soundInit()
{
    if (DirectSoundCreate8(nullptr, &g_directSound, nullptr) != DS_OK)
        return false;
    g_directSound->SetCooperativeLevel(g_mainWindow, DSSCL_PRIORITY);

    DSBUFFERDESC desc;
    desc.dwSize = sizeof(DSBUFFERDESC);
    // PRIMARYBUFFER | CTRL3D | LOCHARDWARE/LOCSOFTWARE
    desc.dwFlags = (g_soundHardware == 0 ? 4 : 0) + 0x15;
    desc.dwBufferBytes = 0;
    desc.dwReserved = 0;
    desc.lpwfxFormat = nullptr;
    desc.guid3DAlgorithm = GUID_NULL;
    if (g_directSound->CreateSoundBuffer(&desc, &g_primaryBuffer, nullptr) != DS_OK)
        return false;

    if (!loadSounds()) {
        g_primaryBuffer->Release();
        g_directSound->Release();
        return false;
    }
    g_soundReady = 1;
    return true;
}

// @ 0x41569a
bool soundStart()
{
    if (!g_soundEnabled)
        return false;
    g_soundHardware = 1;
    if (soundInit())
        return true;
    g_soundHardware = 0;
    return soundInit();
}
