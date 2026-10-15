// MiniFMOD 1.7 (modified): file layer, waveOut output, song control and the
// XM replayer.
#include "minifmod.h"
#include "../game/game.h"

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------
FSOUND_CHANNEL FSOUND_Channel[256];                         // @ 0xd107c0
int FSOUND_MixRate;                                         // @ 0xd175b4
unsigned int mix_volumerampsteps;                           // @ 0xd0fe84
float mix_1overvolumerampsteps;                             // @ 0xd0fe88
int g_musicOrder;                                           // @ 0xd0fa18

static FSOUND_OpenCallback FSOUND_File_OpenCallback;        // @ 0xd0fe8c
static FSOUND_CloseCallback FSOUND_File_CloseCallback;      // @ 0xd0fe90
static FSOUND_ReadCallback FSOUND_File_ReadCallback;        // @ 0xd0fe94
static FSOUND_SeekCallback FSOUND_File_SeekCallback;        // @ 0xd0fe98
static FSOUND_TellCallback FSOUND_File_TellCallback;        // @ 0xd0fe9c

static FMUSIC_MODULE *FMUSIC_PlayingSong;                   // @ 0xd0fa14
static FMUSIC_CHANNEL FMUSIC_Channel[32];                   // @ 0xd15fe0
static FMUSIC_TIMEINFO *FMUSIC_TimeInfo;                    // @ 0xd175b0
static FSOUND_SAMPLE FMUSIC_DummySample;                    // @ 0xd17580
static FMUSIC_INSTRUMENT FMUSIC_DummyInstrument;            // @ 0xd175c0

static HWAVEOUT FSOUND_WaveOutHandle;                       // @ 0xd17744
static WAVEHDR FSOUND_BufferMem;                            // @ 0xd17720
static void *FSOUND_BufferMemData;                          // @ 0xd17740
static void *FSOUND_MixBufferMem;                           // @ 0xd15fc8
static void *FSOUND_MixBuffer;                              // @ 0xd15fc0 16 byte aligned
static float FSOUND_OOMixRate;                              // @ 0xd15fcc
static int FSOUND_BlockSize;                                // @ 0xd15fc4 samples per block
static int FSOUND_BufferSize;                               // @ 0xd17560 samples in the ring buffer
static int FSOUND_BufferSizeMs = 1000;                      // @ 0x453ce8

static volatile char FSOUND_Software_Exit;                  // @ 0xd0fe20
static volatile char FSOUND_Software_UpdateMutex;           // @ 0xd0fe21
static HANDLE FSOUND_Software_hThread;                      // @ 0xd0fe24
static int FSOUND_Software_FillBlock;                       // @ 0xd0fe28
static int FSOUND_Software_RealBlock;                       // @ 0xd0fe2c
static volatile char FSOUND_Software_ThreadFinished = 1;    // @ 0x453cec

#define FSOUND_LATENCY 20

// ---------------------------------------------------------------------------
// File layer
// ---------------------------------------------------------------------------

// @ 0x419023
void FSOUND_File_SetCallbacks(FSOUND_OpenCallback open, FSOUND_CloseCallback close, FSOUND_ReadCallback read,
                              FSOUND_SeekCallback seek, FSOUND_TellCallback tell)
{
    if (!open || !close || !read || !seek || !tell) {
        FSOUND_File_OpenCallback = nullptr;
        FSOUND_File_CloseCallback = nullptr;
        FSOUND_File_ReadCallback = nullptr;
        FSOUND_File_SeekCallback = nullptr;
        FSOUND_File_TellCallback = nullptr;
    } else {
        FSOUND_File_OpenCallback = open;
        FSOUND_File_CloseCallback = close;
        FSOUND_File_ReadCallback = read;
        FSOUND_File_SeekCallback = seek;
        FSOUND_File_TellCallback = tell;
    }
}

// @ 0x419090
FSOUND_FILE_HANDLE *FSOUND_File_Open(const char *name, signed char type, int length)
{
    FSOUND_FILE_HANDLE *handle = (FSOUND_FILE_HANDLE *)calloc(sizeof(FSOUND_FILE_HANDLE), 1);
    handle->type = type;
    handle->length = length;
    handle->userhandle = FSOUND_File_OpenCallback(name);
    if (!handle->userhandle) {
        free(handle);
        return nullptr;
    }
    return handle;
}

// @ 0x4190cc
void FSOUND_File_Close(FSOUND_FILE_HANDLE *handle)
{
    if (!handle)
        return;
    FSOUND_File_CloseCallback(handle->userhandle);
    free(handle);
}

// @ 0x4190e8
int FSOUND_File_Read(void *buffer, int size, FSOUND_FILE_HANDLE *handle)
{
    if (!handle)
        return 0;
    return FSOUND_File_ReadCallback(buffer, size, handle->userhandle);
}

// @ 0x419106
void FSOUND_File_Seek(FSOUND_FILE_HANDLE *handle, int pos, signed char mode)
{
    if (!handle)
        return;
    FSOUND_File_SeekCallback(handle->userhandle, pos, mode);
}

// @ 0x419123
int FSOUND_File_Tell(FSOUND_FILE_HANDLE *handle)
{
    if (!handle)
        return 0;
    return FSOUND_File_TellCallback(handle->userhandle);
}

// ---------------------------------------------------------------------------
// Output
// ---------------------------------------------------------------------------

// @ 0x4171d9
signed char FSOUND_Init(int mixrate, int)
{
    if (!FSOUND_File_OpenCallback || !FSOUND_File_CloseCallback || !FSOUND_File_ReadCallback ||
        !FSOUND_File_SeekCallback || !FSOUND_File_TellCallback)
        return 0;

    FSOUND_Close();
    FSOUND_MixRate = mixrate;

    WAVEFORMATEX pcmwf;
    pcmwf.wFormatTag = WAVE_FORMAT_PCM;
    pcmwf.nChannels = 2;
    pcmwf.wBitsPerSample = 16;
    pcmwf.nBlockAlign = 4;
    pcmwf.cbSize = 0;
    // the device runs slower together with the game when g_timeDivider > 1
    pcmwf.nSamplesPerSec = mixrate / g_timeDivider;
    pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * 4;
    if (waveOutOpen(&FSOUND_WaveOutHandle, WAVE_MAPPER, &pcmwf, 0, 0, 0))
        return 0;

    FSOUND_OOMixRate = 1.0f / mixrate;
    FSOUND_BlockSize = (FSOUND_MixRate * FSOUND_LATENCY / 1000 + 3) & ~3;
    FSOUND_BufferSize = FSOUND_BufferSizeMs / FSOUND_LATENCY * FSOUND_BlockSize * 2;
    mix_volumerampsteps = FSOUND_MixRate * 128 / 44100;
    mix_1overvolumerampsteps = 1.0f / mix_volumerampsteps;

    memset(FSOUND_Channel, 0, sizeof(FSOUND_Channel));
    for (int count = 0; count < 256; ++count) {
        FSOUND_Channel[count].index = count;
        FSOUND_Channel[count].speedhi = 1;
    }
    return 1;
}

// @ 0x416f90
void FSOUND_Close()
{
    waveOutReset(FSOUND_WaveOutHandle);
    waveOutClose(FSOUND_WaveOutHandle);
}

// @ 0x416fa9
// Mixes one block of the ring buffer, running the replayer whenever a tick
// worth of samples has been mixed.
void FSOUND_Software_Fill()
{
    int totalblocks = FSOUND_BufferSize / FSOUND_BlockSize;
    int mixpos = FSOUND_Software_FillBlock * FSOUND_BlockSize;
    char *mixbuffer = (char *)FSOUND_MixBuffer + mixpos * 8;
    memset(mixbuffer, 0, FSOUND_BlockSize * 8);

    int MixedSoFar = 0;
    int MixedLeft = FMUSIC_PlayingSong->mixer_samplesleft;
    char *MixPtr = mixbuffer;
    while (MixedSoFar < FSOUND_BlockSize) {
        int SamplesToMix;
        if (!MixedLeft) {
            FMUSIC_PlayingSong->Update(FMUSIC_PlayingSong);
            SamplesToMix = FMUSIC_PlayingSong->mixer_samplespertick;
            MixedLeft = SamplesToMix;
        } else {
            SamplesToMix = MixedLeft;
        }
        if (MixedSoFar + SamplesToMix > FSOUND_BlockSize)
            SamplesToMix = FSOUND_BlockSize - MixedSoFar;

        FSOUND_Mixer_FPU_Ramp(MixPtr, SamplesToMix, 0);
        MixedSoFar += SamplesToMix;
        MixPtr += SamplesToMix * 8;
        MixedLeft -= SamplesToMix;
        FMUSIC_PlayingSong->time_ms += fp::ftol(SamplesToMix * FSOUND_OOMixRate * 1000.0f);
    }

    FMUSIC_TimeInfo[FSOUND_Software_FillBlock].ms = FMUSIC_PlayingSong->time_ms;
    FMUSIC_TimeInfo[FSOUND_Software_FillBlock].row = (unsigned char)FMUSIC_PlayingSong->row;
    FMUSIC_TimeInfo[FSOUND_Software_FillBlock].order = (unsigned char)FMUSIC_PlayingSong->order;
    FMUSIC_PlayingSong->mixer_samplesleft = MixedLeft;

    FSOUND_MixerClipCopy_Float32((char *)FSOUND_BufferMemData + mixpos * 4, mixbuffer,
                                 ((unsigned)FSOUND_BlockSize << 2) >> 2);

    if (++FSOUND_Software_FillBlock >= totalblocks)
        FSOUND_Software_FillBlock = 0;
}

// @ 0x417121
// Keeps the blocks behind the play cursor filled.
DWORD WINAPI FSOUND_Software_DoubleBufferThread(LPVOID)
{
    int totalblocks = FSOUND_BufferSize / FSOUND_BlockSize;
    FSOUND_Software_ThreadFinished = 0;
    while (!FSOUND_Software_Exit) {
        MMTIME mmt;
        mmt.wType = TIME_BYTES;
        waveOutGetPosition(FSOUND_WaveOutHandle, &mmt, sizeof(MMTIME));
        mmt.u.cb >>= 2;
        int cursorblock = (int)mmt.u.cb % FSOUND_BufferSize / FSOUND_BlockSize;
        while (FSOUND_Software_FillBlock != cursorblock) {
            FSOUND_Software_UpdateMutex = 1;
            FSOUND_Software_Fill();
            if (++FSOUND_Software_RealBlock >= totalblocks)
                FSOUND_Software_RealBlock = 0;
            FSOUND_Software_UpdateMutex = 0;
        }
        Sleep(5);
    }
    FSOUND_Software_ThreadFinished = 1;
    return 0;
}

// ---------------------------------------------------------------------------
// Song control
// ---------------------------------------------------------------------------

// @ 0x416be4
void FMUSIC_SetBPM(FMUSIC_MODULE *mod, int bpm)
{
    mod->bpm = bpm;
    // hz = bpm * 2 / 5
    mod->mixer_samplespertick = fp::ftol(1000.0f / (bpm * 0.4f) * FSOUND_MixRate * 0.001f);
}

// @ 0x416c19
signed char FMUSIC_StopSong(FMUSIC_MODULE *mod)
{
    if (!mod)
        return 0;

    FSOUND_Software_Exit = 1;
    while (FSOUND_Software_UpdateMutex)
        ;
    if (FSOUND_Software_hThread) {
        while (!FSOUND_Software_ThreadFinished)
            Sleep(50);
        FSOUND_Software_hThread = nullptr;
    }
    if (FSOUND_MixBufferMem) {
        free(FSOUND_MixBufferMem);
        FSOUND_MixBufferMem = nullptr;
    }
    // the output buffer itself is never freed
    if (FSOUND_BufferMem.lpData) {
        waveOutUnprepareHeader(FSOUND_WaveOutHandle, &FSOUND_BufferMem, sizeof(WAVEHDR));
        FSOUND_BufferMem.dwFlags &= ~WHDR_PREPARED;
    }
    FMUSIC_PlayingSong = nullptr;
    if (FMUSIC_TimeInfo) {
        free(FMUSIC_TimeInfo);
        FMUSIC_TimeInfo = nullptr;
    }
    return 1;
}

// @ 0x416cad
signed char FMUSIC_FreeSong(FMUSIC_MODULE *mod)
{
    if (!mod)
        return 0;

    while (FSOUND_Software_UpdateMutex)
        ;
    FMUSIC_StopSong(mod);

    if (mod->instrument) {
        for (int count = 0; count < mod->numinsts; ++count) {
            FMUSIC_INSTRUMENT *iptr = &mod->instrument[count];
            for (int count2 = 0; count2 < iptr->numsamples; ++count2) {
                FSOUND_SAMPLE *sptr = iptr->sample[count2];
                if (sptr) {
                    free(sptr->buff);
                    free(sptr);
                }
            }
        }
    }
    if (mod->instrument)
        free(mod->instrument);

    if (mod->pattern) {
        for (int count = 0; count < mod->numpatternsmem; ++count) {
            if (mod->pattern[count].data)
                free(mod->pattern[count].data);
        }
        if (mod->pattern)
            free(mod->pattern);
    }
    free(mod);
    return 1;
}

// @ 0x416d7e
signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod)
{
    int totalblocks = FSOUND_BufferSize / FSOUND_BlockSize;
    if (!mod)
        return 0;

    FMUSIC_StopSong(mod);

    mod->globalvolume = mod->defaultglobalvolume;
    mod->speed = mod->defaultspeed;
    mod->row = 0;
    mod->order = g_musicOrder;
    mod->nextorder = -1;
    mod->nextrow = -1;
    mod->mixer_samplesleft = 0;
    mod->tick = 0;
    mod->patterndelay = 0;
    mod->time_ms = 0;
    if (mod->initCallback)
        mod->initCallback(mod);
    FMUSIC_SetBPM(mod, mod->defaultbpm);

    memset(FMUSIC_Channel, 0, mod->numchannels * sizeof(FMUSIC_CHANNEL));
    for (int count = 0; count < mod->numchannels; ++count)
        FMUSIC_Channel[count].cptr = &FSOUND_Channel[count];

    FMUSIC_PlayingSong = mod;
    FMUSIC_TimeInfo = (FMUSIC_TIMEINFO *)calloc(totalblocks * sizeof(FMUSIC_TIMEINFO), 1);

    // looping output buffer
    int length = FSOUND_BufferSize * 4;
    FSOUND_BufferMem.lpData = (LPSTR)calloc(length, 1);
    FSOUND_BufferMem.dwBufferLength = length;
    FSOUND_BufferMem.dwBytesRecorded = 0;
    FSOUND_BufferMem.dwUser = 0;
    FSOUND_BufferMem.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
    FSOUND_BufferMem.dwLoops = (DWORD)-1;
    FSOUND_BufferMemData = FSOUND_BufferMem.lpData;
    waveOutPrepareHeader(FSOUND_WaveOutHandle, &FSOUND_BufferMem, sizeof(WAVEHDR));

    FSOUND_MixBufferMem = calloc(FSOUND_BufferSize * 8 + 256, 1);
    FSOUND_MixBuffer = (void *)(((uintptr_t)FSOUND_MixBufferMem + 15) & ~(uintptr_t)15);

    // prefill the whole ring buffer
    FSOUND_Software_FillBlock = 0;
    do {
        FSOUND_Software_Fill();
    } while (FSOUND_Software_FillBlock);

    waveOutWrite(FSOUND_WaveOutHandle, &FSOUND_BufferMem, sizeof(WAVEHDR));

    FSOUND_Software_Exit = 0;
    DWORD threadId;
    FSOUND_Software_hThread = CreateThread(nullptr, 0, FSOUND_Software_DoubleBufferThread, nullptr, 0, &threadId);
    SetThreadPriority(FSOUND_Software_hThread, THREAD_PRIORITY_TIME_CRITICAL);
    return 1;
}

// @ 0x416f38
FMUSIC_MODULE *FMUSIC_LoadSong(const char *name, FMUSIC_SAMPLELOADCALLBACK callback)
{
    FMUSIC_MODULE *mod = (FMUSIC_MODULE *)calloc(sizeof(FMUSIC_MODULE), 1);
    FSOUND_FILE_HANDLE *fp = FSOUND_File_Open(name, 0, 0);
    if (!fp)
        return nullptr;
    mod->samplecallback = callback;
    signed char ok = FMUSIC_LoadXM(mod, fp);
    FSOUND_File_Close(fp);
    if (!ok) {
        FMUSIC_FreeSong(mod);
        return nullptr;
    }
    return mod;
}

// ---------------------------------------------------------------------------
// XM effects
// ---------------------------------------------------------------------------

// @ 0x4179d8
void FMUSIC_XM_Portamento(FMUSIC_CHANNEL *cptr)
{
    if (cptr->freq < cptr->portatarget) {
        cptr->freq += cptr->portaspeed * 4;
        if (cptr->freq > cptr->portatarget)
            cptr->freq = cptr->portatarget;
    } else if (cptr->freq > cptr->portatarget) {
        cptr->freq -= cptr->portaspeed * 4;
        if (cptr->freq < cptr->portatarget)
            cptr->freq = cptr->portatarget;
    }
    cptr->notectrl |= FMUSIC_FREQ;
}

// @ 0x417a1b
void FMUSIC_XM_Vibrato(FMUSIC_CHANNEL *cptr)
{
    int delta;
    switch (cptr->wavecontrol & 3) {
    case 0:
        delta = fp::ftol(fp::fabs(fp::sin(cptr->vibpos * 2.0 * 0.049087375) * 256.0));
        break;
    case 1: {
        unsigned char ramp = (unsigned char)(cptr->vibpos * 8);
        if (cptr->vibpos < 0)
            ramp = (unsigned char)(255 - ramp);
        delta = ramp;
        break;
    }
    default:
        delta = 255;
        break;
    }
    delta = (cptr->vibdepth * delta) >> 5 & ~3;
    if (cptr->vibpos >= 0)
        delta = -delta;
    cptr->notectrl |= FMUSIC_FREQ;
    cptr->freqdelta = delta;
}

// @ 0x417abb
void FMUSIC_XM_InstrumentVibrato(FMUSIC_CHANNEL *cptr, FMUSIC_INSTRUMENT *iptr)
{
    int delta;
    switch (iptr->VIBtype) {
    case 0:
        delta = fp::ftol(fp::sin(cptr->ivibpos * 0.0245436877f) * 64.0);
        break;
    case 1:
        delta = cptr->ivibpos < 128 ? 64 : -64;
        break;
    case 2:
        delta = (128 - (cptr->ivibpos + 128) % 256) >> 1;
        break;
    case 3:
        delta = (128 - (384 - cptr->ivibpos) % 256) >> 1;
        break;
    default:
        // not reachable with valid XM data; the original uses the pointer
        delta = (int)(intptr_t)iptr;
        break;
    }
    delta *= iptr->VIBdepth;
    if (iptr->VIBsweep)
        delta = cptr->ivibsweeppos * delta / iptr->VIBsweep;
    cptr->freqdelta += delta >> 6;

    if (++cptr->ivibsweeppos > iptr->VIBsweep)
        cptr->ivibsweeppos = iptr->VIBsweep;
    cptr->ivibpos += iptr->VIBrate;
    if (cptr->ivibpos > 255)
        cptr->ivibpos -= 256;
    cptr->notectrl |= FMUSIC_FREQ;
}

// @ 0x417bac
void FMUSIC_XM_ProcessEnvelope(FMUSIC_CHANNEL *cptr, int *pos, int *tick, unsigned char type, int numpoints,
                               unsigned short *points, unsigned char loopend, unsigned char loopstart,
                               unsigned char sustain, int *value, int *valfrac, unsigned char *envstopped,
                               int *envdelta, unsigned char control)
{
    if (*pos < numpoints) {
        if (*tick == points[*pos << 1]) {
            if ((type & 4) && *pos == loopend) {
                *pos = loopstart;
                *tick = points[loopstart << 1];
            }
            int currpos = *pos;
            unsigned short *point = &points[currpos << 1];
            unsigned short *next = &points[(currpos + 1) << 1];
            int currval = point[1];

            // reached the last point
            if ((unsigned)currpos == (unsigned)(numpoints - 1)) {
                *value = currval;
                *envstopped = 1;
                cptr->notectrl |= control;
                return;
            }
            // sustain point
            if ((type & 2) && (unsigned)currpos == sustain && !cptr->keyoff) {
                *value = currval;
                cptr->notectrl |= control;
                return;
            }
            int tickdiff = next[0] - point[0];
            *envdelta = tickdiff ? (int)((unsigned)next[1] * 0x10000u - (unsigned)currval * 0x10000u) / tickdiff : 0;
            *valfrac = currval * 0x10000;
            ++*pos;
        } else {
            *valfrac += *envdelta;
        }
    }
    *value = (short)(*valfrac >> 16);
    ++*tick;
    cptr->notectrl |= control;
}

// @ 0x417c9f
void FMUSIC_XM_ProcessVolumeByte(FMUSIC_CHANNEL *cptr, unsigned char volume)
{
    if (volume >= 0x10 && volume <= 0x50) {
        cptr->notectrl |= FMUSIC_VOLUME;
        cptr->volume = volume - 0x10;
        return;
    }
    int param = volume & 0xf;
    switch (volume >> 4) {
    case 0x6:
    case 0x8:
        cptr->volume -= param;
        if (cptr->volume < 0)
            cptr->volume = 0;
        cptr->notectrl |= FMUSIC_VOLUME;
        return;
    case 0x7:
    case 0x9:
        cptr->volume += param;
        if (cptr->volume > 0x40)
            cptr->volume = 0x40;
        cptr->notectrl |= FMUSIC_VOLUME;
        return;
    case 0xa:
        cptr->vibspeed = (unsigned char)param;
        return;
    case 0xb:
        cptr->vibdepth = (unsigned char)param;
        return;
    case 0xc:
        cptr->pan = param << 4;
        break;
    case 0xd:
        cptr->pan -= param;
        break;
    case 0xe:
        cptr->pan += param;
        break;
    case 0xf:
        if (param)
            cptr->portaspeed = (unsigned char)(volume << 4);
        cptr->notectrl &= ~FMUSIC_TRIGGER;
        cptr->portatarget = cptr->period;
        return;
    default:
        return;
    }
    cptr->notectrl |= FMUSIC_PAN;
}

// @ 0x417d95
// Pushes the music channel state to its mixer channel. A retriggered note
// moves to the twin channel 32 slots away so the old one can ramp out.
void FMUSIC_UpdateFlags(FMUSIC_CHANNEL *cptr, FSOUND_SAMPLE *sptr, FMUSIC_MODULE *mod)
{
    FSOUND_CHANNEL *ccptr = cptr->cptr;
    int channel = (int)(intptr_t)cptr;   // only meaningful when ccptr is set
    if (ccptr)
        channel = ccptr->index;

    if (cptr->freq + cptr->freqdelta == 0)
        cptr->notectrl &= ~FMUSIC_FREQ;

    if (cptr->notectrl & FMUSIC_TRIGGER) {
        ccptr = &FSOUND_Channel[channel];
        if (ccptr->sptr) {
            FSOUND_CHANNEL *old = ccptr;
            if (channel < 32)
                channel += 32;
            else
                channel -= 32;
            ccptr = &FSOUND_Channel[channel];
            memcpy(ccptr, old, sizeof(FSOUND_CHANNEL));
            ccptr->index = channel;
            old->actualvolume = 0;
            old->volume = 0;
            old->leftvolume = 0;
            old->rightvolume = 0;
            cptr->cptr = ccptr;
        }
        ccptr->sptr = sptr;
        if (ccptr->sampleoffset >= sptr->loopstart + sptr->looplen)
            ccptr->sampleoffset = 0;
        ccptr->mixpos = ccptr->sampleoffset;
        ccptr->mixposlo = 0;
        ccptr->speeddir = 1;
        ccptr->sampleoffset = 0;
        ccptr->ramp_leftvolume = 0;
        ccptr->ramp_rightvolume = 0;
        ccptr->ramp_count = 0;
    }

    if (cptr->notectrl & FMUSIC_VOLUME) {
        int volume = fp::ftol((double)(cptr->volume + cptr->voldelta) * cptr->envvol * cptr->fadeoutvol *
                              mod->globalvolume * 7.4214767664670944e-9f);
        if (ccptr) {
            ccptr->actualvolume = volume;
            ccptr->volume = volume;
            ccptr->leftvolume = ccptr->actualpan * volume / 255;
            ccptr->rightvolume = (255 - ccptr->actualpan) * volume / 255;
        }
    }

    if (cptr->notectrl & FMUSIC_PAN) {
        int pan = (128 - abs(cptr->pan - 128)) / 32 * (cptr->envpan - 32) + cptr->pan;
        if (pan < 0)
            pan = 0;
        if (pan > 255)
            pan = 255;
        if (ccptr) {
            ccptr->actualpan = pan;
            ccptr->pan = pan;
            ccptr->leftvolume = ccptr->actualvolume * pan / 255;
            ccptr->rightvolume = (255 - pan) * ccptr->actualvolume / 255;
        }
    }

    if (cptr->notectrl & FMUSIC_FREQ) {
        int freq;
        if (mod->flags & 1)
            freq = fp::ftol(fp::pow(2.0, (4608.0f - cptr->freq + cptr->freqdelta) * 0.0013020833721384406f) * 8363.0);
        else
            freq = 14317056 / (cptr->freq + cptr->freqdelta);

        // FSOUND_SetFrequency
        ccptr->frequency = freq;
        if (freq < 100)
            freq = 100;
        unsigned int quotient = (unsigned)freq / (unsigned)FSOUND_MixRate;
        unsigned int remainder = (unsigned)freq % (unsigned)FSOUND_MixRate;
        ccptr->speedhi = quotient;
        // the second DIV of the original divides remainder:quotient
        ccptr->speedlo = (unsigned)((((unsigned long long)remainder << 32) | quotient) / (unsigned)FSOUND_MixRate);
    }

    if (cptr->notectrl & FMUSIC_STOP) {
        ccptr->mixposlo = 0;
        ccptr->mixpos = 0;
        ccptr->sampleoffset = 0;
    }
}

// @ 0x417fab
void FMUSIC_XM_Resetcptr(FMUSIC_CHANNEL *cptr, FSOUND_SAMPLE *sptr)
{
    cptr->volume = sptr->defvol;
    cptr->pan = sptr->defpan;
    cptr->envvol = 64;
    cptr->envvolpos = 0;
    cptr->envvoltick = 0;
    cptr->envvoldelta = 0;
    cptr->envpan = 32;
    cptr->envpanpos = 0;
    cptr->envpantick = 0;
    cptr->envpandelta = 0;
    cptr->keyoff = 0;
    cptr->fadeoutvol = 0x10000;
    cptr->envvolstopped = 0;
    cptr->envpanstopped = 0;
    cptr->ivibsweeppos = 0;
    cptr->ivibpos = 0;
    // retrigger tremolo and vibrato waveforms
    if ((cptr->wavecontrol & 0xf) < 4)
        cptr->vibpos = 0;
    if ((cptr->wavecontrol & 0xf0) < 0x40)
        cptr->trempos = 0;
    cptr->notectrl |= FMUSIC_VOLUME | FMUSIC_PAN;
    cptr->tremorpos = 0;
}

// Looks up the instrument and sample a channel plays.
static FMUSIC_INSTRUMENT *instrumentOf(FMUSIC_MODULE *mod, FMUSIC_CHANNEL *cptr, FSOUND_SAMPLE **sptr,
                                       bool nullIsDummy)
{
    if (cptr->inst < mod->numinsts) {
        FMUSIC_INSTRUMENT *iptr = &mod->instrument[cptr->inst];
        unsigned char sample = iptr->keymap[cptr->note];
        *sptr = sample < 16 ? iptr->sample[sample] : &FMUSIC_DummySample;
        if (nullIsDummy && !*sptr)
            *sptr = &FMUSIC_DummySample;
        return iptr;
    }
    FMUSIC_DummySample.buff = nullptr;
    *sptr = &FMUSIC_DummySample;
    return &FMUSIC_DummyInstrument;
}

// @ 0x418029
// Tick 0: reads a new row.
void FMUSIC_UpdateXMNote(FMUSIC_MODULE *mod)
{
    mod->nextorder = -1;
    mod->nextrow = -1;

    FMUSIC_NOTE *current = mod->pattern[mod->orderlist[mod->order]].data + mod->row * mod->numchannels;
    if (!current)
        return;

    FMUSIC_CHANNEL *cptr = FMUSIC_Channel;
    for (int count = 0; count < mod->numchannels; ++count, ++cptr, ++current) {
        unsigned char paramx = current->eparam >> 4;
        unsigned char paramy = current->eparam & 0xf;
        bool porta = current->effect == 3 || current->effect == 5;

        if (current->number && !porta)
            cptr->inst = current->number - 1;
        if (current->note && current->note != 0xff && !porta)
            cptr->note = current->note - 1;

        FSOUND_SAMPLE *sptr;
        FMUSIC_INSTRUMENT *iptr;
        if (cptr->inst < mod->numinsts) {
            iptr = &mod->instrument[cptr->inst];
            unsigned char sample = iptr->keymap[cptr->note];
            sptr = sample < 16 ? iptr->sample[sample] : &FMUSIC_DummySample;
            if (!porta)
                cptr->sptr = sptr;
        } else {
            FMUSIC_DummySample.buff = nullptr;
            iptr = &FMUSIC_DummyInstrument;
            sptr = &FMUSIC_DummySample;
        }

        int oldfreq = cptr->freq;
        int oldvolume = cptr->volume;
        int oldpan = cptr->pan;

        // leftover of the (removed) tremolo: keep the modulated volume
        if (cptr->recenteffect == 7 && current->effect != 7)
            cptr->volume = cptr->voldelta + oldvolume;
        cptr->voldelta = 0;
        cptr->recenteffect = current->effect;
        cptr->notectrl = 0;

        if (current->note && current->note != 0xff) {
            cptr->realnote = (unsigned char)(current->note + sptr->relative - 1);
            if (mod->flags & 1)
                cptr->period = 7680 - cptr->realnote * 64 - sptr->finetune / 2;
            if (!porta)
                cptr->freq = cptr->period;
            cptr->notectrl = FMUSIC_TRIGGER;
        }
        cptr->freqdelta = 0;
        cptr->notectrl |= FMUSIC_FREQ | FMUSIC_VOLUME;

        if (current->number)
            FMUSIC_XM_Resetcptr(cptr, sptr);
        if (current->volume)
            FMUSIC_XM_ProcessVolumeByte(cptr, current->volume);
        if (current->note == 0xff || current->effect == 0x14)
            cptr->keyoff = 1;

        if (!(iptr->VOLtype & 1)) {
            if (cptr->keyoff)
                cptr->envvol = 0;
        } else if (!cptr->envvolstopped) {
            FMUSIC_XM_ProcessEnvelope(cptr, &cptr->envvolpos, &cptr->envvoltick, iptr->VOLtype, iptr->VOLnumpoints,
                                      iptr->VOLPoints, iptr->VOLLoopEnd, iptr->VOLLoopStart, iptr->VOLsustain,
                                      &cptr->envvol, &cptr->envvolfrac, &cptr->envvolstopped, &cptr->envvoldelta,
                                      FMUSIC_VOLUME);
        }
        if ((iptr->PANtype & 1) && !cptr->envpanstopped) {
            FMUSIC_XM_ProcessEnvelope(cptr, &cptr->envpanpos, &cptr->envpantick, iptr->PANtype, iptr->PANnumpoints,
                                      iptr->PANPoints, iptr->PANLoopEnd, iptr->PANLoopStart, iptr->PANsustain,
                                      &cptr->envpan, &cptr->envpanfrac, &cptr->envpanstopped, &cptr->envpandelta,
                                      FMUSIC_PAN);
        }

        // fade out after key off
        if (cptr->keyoff) {
            cptr->fadeoutvol -= iptr->VOLfade;
            if (cptr->fadeoutvol < 0)
                cptr->fadeoutvol = 0;
            cptr->notectrl |= FMUSIC_VOLUME;
        }

        switch (current->effect) {
        case 0x1:   // porta up
            if (current->eparam)
                cptr->portaup = current->eparam;
            break;
        case 0x2:   // porta down
            if (current->eparam)
                cptr->portadown = current->eparam;
            break;
        case 0x3:   // tone portamento
            if (current->eparam)
                cptr->portaspeed = current->eparam;
            cptr->notectrl &= ~(FMUSIC_FREQ | FMUSIC_TRIGGER);
            cptr->portatarget = cptr->period;
            break;
        case 0x4:   // vibrato
            if (paramx)
                cptr->vibspeed = paramx;
            if (paramy)
                cptr->vibdepth = paramy;
            FMUSIC_XM_Vibrato(cptr);
            break;
        case 0x9:   // sample offset
            if (current->eparam)
                cptr->sampleoffset = current->eparam;
            if (cptr->cptr) {
                if (cptr->sampleoffset << 8 < sptr->loopstart + sptr->looplen)
                    cptr->cptr->sampleoffset = cptr->sampleoffset << 8;
                else
                    cptr->notectrl = (cptr->notectrl & ~FMUSIC_TRIGGER) | FMUSIC_STOP;
            }
            break;
        case 0xe:
            if (paramx == 0x2) {          // fine porta down
                if (paramy)
                    cptr->fineportadown = paramy;
                cptr->freq += cptr->fineportadown * 4;
            } else if (paramx == 0xd) {   // note delay
                cptr->notectrl &= 0xf0;
                cptr->volume = oldvolume;
                cptr->freq = oldfreq;
                cptr->pan = oldpan;
            }
            break;
        case 0xf:   // speed / tempo
            if (current->eparam < 0x20)
                mod->speed = current->eparam;
            else
                FMUSIC_SetBPM(mod, current->eparam);
            break;
        case 0x1b:  // multi retrig
            if (current->eparam) {
                cptr->retrigx = paramx;
                cptr->retrigy = paramy;
            }
            break;
        }

        FMUSIC_XM_InstrumentVibrato(cptr, iptr);
        FMUSIC_UpdateFlags(cptr, sptr, mod);
    }
}

// @ 0x418446
// Ticks after the first: running effects.
void FMUSIC_UpdateXMEffects(FMUSIC_MODULE *mod)
{
    FMUSIC_NOTE *current = mod->pattern[mod->orderlist[mod->order]].data + mod->row * mod->numchannels;
    if (!current)
        return;

    FMUSIC_CHANNEL *cptr = FMUSIC_Channel;
    for (int count = 0; count < mod->numchannels; ++count, ++cptr, ++current) {
        FSOUND_SAMPLE *sptr;
        FMUSIC_INSTRUMENT *iptr = instrumentOf(mod, cptr, &sptr, true);

        unsigned char effect = current->effect;
        unsigned char paramx = current->eparam >> 4;
        unsigned char paramy = current->eparam & 0xf;

        cptr->voldelta = 0;
        cptr->freqdelta = 0;
        cptr->notectrl = 0;

        if ((iptr->VOLtype & 1) && !cptr->envvolstopped) {
            FMUSIC_XM_ProcessEnvelope(cptr, &cptr->envvolpos, &cptr->envvoltick, iptr->VOLtype, iptr->VOLnumpoints,
                                      iptr->VOLPoints, iptr->VOLLoopEnd, iptr->VOLLoopStart, iptr->VOLsustain,
                                      &cptr->envvol, &cptr->envvolfrac, &cptr->envvolstopped, &cptr->envvoldelta,
                                      FMUSIC_VOLUME);
        }
        if ((iptr->PANtype & 1) && !cptr->envpanstopped) {
            FMUSIC_XM_ProcessEnvelope(cptr, &cptr->envpanpos, &cptr->envpantick, iptr->PANtype, iptr->PANnumpoints,
                                      iptr->PANPoints, iptr->PANLoopEnd, iptr->PANLoopStart, iptr->PANsustain,
                                      &cptr->envpan, &cptr->envpanfrac, &cptr->envpanstopped, &cptr->envpandelta,
                                      FMUSIC_PAN);
        }
        if (cptr->keyoff) {
            cptr->fadeoutvol -= iptr->VOLfade;
            if (cptr->fadeoutvol < 0)
                cptr->fadeoutvol = 0;
            cptr->notectrl |= FMUSIC_VOLUME;
        }

        // volume column
        unsigned char volume = current->volume;
        switch (volume >> 4) {
        case 0x6:   // volume slide down
            cptr->volume -= volume & 0xf;
            if (cptr->volume < 0)
                cptr->volume = 0;
            cptr->notectrl |= FMUSIC_VOLUME;
            break;
        case 0x7:   // volume slide up
            cptr->volume += volume & 0xf;
            if (cptr->volume > 0x40)
                cptr->volume = 0x40;
            cptr->notectrl |= FMUSIC_VOLUME;
            break;
        case 0xb:   // vibrato
            cptr->vibdepth = volume & 0xf;
            FMUSIC_XM_Vibrato(cptr);
            cptr->vibpos += cptr->vibspeed;
            if (cptr->vibpos > 31)
                cptr->vibpos -= 64;
            break;
        case 0xd:   // pan slide left
            cptr->pan -= volume & 0xf;
            cptr->notectrl |= FMUSIC_PAN;
            break;
        case 0xe:   // pan slide right
            cptr->pan += volume & 0xf;
            cptr->notectrl |= FMUSIC_PAN;
            break;
        case 0xf:   // tone portamento
            FMUSIC_XM_Portamento(cptr);
            break;
        }

        bool trigger = false;
        switch (effect) {
        case 0x0:   // arpeggio
            if (current->eparam) {
                switch (mod->tick % 3) {
                case 1:
                    if (mod->flags & 1)
                        cptr->freqdelta = paramx << 6;
                    break;
                case 2:
                    if (mod->flags & 1)
                        cptr->freqdelta = paramy << 6;
                    break;
                }
                cptr->notectrl |= FMUSIC_FREQ;
            }
            break;
        case 0x1:   // porta up
            cptr->freq -= cptr->portaup * 4;
            cptr->freqdelta = 0;
            if (cptr->freq < 56)
                cptr->freq = 56;
            cptr->notectrl |= FMUSIC_FREQ;
            break;
        case 0x2:   // porta down
            cptr->freq += cptr->portadown * 4;
            cptr->freqdelta = 0;
            cptr->notectrl |= FMUSIC_FREQ;
            break;
        case 0x3:   // tone portamento
            cptr->freqdelta = 0;
            FMUSIC_XM_Portamento(cptr);
            break;
        case 0x4:   // vibrato
            FMUSIC_XM_Vibrato(cptr);
            cptr->vibpos += cptr->vibspeed;
            if (cptr->vibpos > 31)
                cptr->vibpos -= 64;
            break;
        case 0xe:
            if (paramx == 0xc) {          // note cut
                if (mod->tick == paramy) {
                    cptr->notectrl |= FMUSIC_VOLUME;
                    cptr->volume = 0;
                }
            } else if (paramx == 0xd) {   // note delay
                if (mod->tick == paramy) {
                    FMUSIC_XM_Resetcptr(cptr, sptr);
                    cptr->notectrl |= FMUSIC_FREQ;
                    cptr->freq = cptr->period;
                    if (current->volume)
                        FMUSIC_XM_ProcessVolumeByte(cptr, current->volume);
                    trigger = true;
                } else {
                    cptr->notectrl &= 0xf0;
                }
            }
            break;
        case 0x1b:  // multi retrig
            if (!cptr->retrigy || mod->tick % cptr->retrigy)
                break;
            if (cptr->retrigx) {
                switch (cptr->retrigx) {
                case 0x1: cptr->volume -= 1; break;
                case 0x2: cptr->volume -= 2; break;
                case 0x3: cptr->volume -= 4; break;
                case 0x4: cptr->volume -= 8; break;
                case 0x5: cptr->volume -= 16; break;
                case 0x6: cptr->volume = cptr->volume * 2 / 3; break;
                case 0x7: cptr->volume >>= 1; break;
                case 0x9: cptr->volume += 1; break;
                case 0xa: cptr->volume += 2; break;
                case 0xb: cptr->volume += 4; break;
                case 0xc: cptr->volume += 8; break;
                case 0xd: cptr->volume += 16; break;
                case 0xe: cptr->volume = cptr->volume * 3 / 2; break;
                case 0xf: cptr->volume <<= 1; break;
                }
                if (cptr->volume > 64)
                    cptr->volume = 64;
                if (cptr->volume < 0)
                    cptr->volume = 0;
                cptr->notectrl |= FMUSIC_VOLUME;
            }
            trigger = true;
            break;
        }
        if (trigger)
            cptr->notectrl |= FMUSIC_TRIGGER;

        FMUSIC_XM_InstrumentVibrato(cptr, iptr);
        FMUSIC_UpdateFlags(cptr, sptr, mod);
    }
}

// @ 0x4188c7
void FMUSIC_UpdateXM(FMUSIC_MODULE *mod)
{
    if (mod->tick == 0) {
        if (mod->nextorder >= 0)
            mod->order = mod->nextorder;
        if (mod->nextrow >= 0)
            mod->row = mod->nextrow;

        FMUSIC_UpdateXMNote(mod);

        if (mod->nextrow == -1) {
            mod->nextrow = mod->row + 1;
            if (mod->nextrow >= mod->pattern[mod->orderlist[mod->order]].rows) {
                mod->nextorder = mod->order + 1;
                if (mod->nextorder >= mod->numorders)
                    mod->nextorder = mod->restart;
                mod->nextrow = 0;
            }
        }
    } else {
        FMUSIC_UpdateXMEffects(mod);
    }

    ++mod->tick;
    if (mod->tick >= mod->speed + mod->patterndelay) {
        mod->patterndelay = 0;
        mod->tick -= mod->speed;
    }
}

// The sample-loaded hook of the original is an empty function (folded with
// the memory file close callback at 0x407ca6).
static void sampleLoaded(FSOUND_SAMPLE *, FSOUND_SAMPLE *, int, int)
{
}

// @ 0x41897e
signed char FMUSIC_LoadXM(FMUSIC_MODULE *mod, FSOUND_FILE_HANDLE *fp)
{
    char str[256];
    unsigned short numpatterns = 0;
    int headersize;
    int patternheadersize;

    FSOUND_File_Seek(fp, 0, SEEK_SET);
    FSOUND_File_Read(str, 17, fp);
    for (int count = 0; count < 17; ++count) {
        if (str[count] != "Extended Module: "[count])
            return 0;
    }

    mod->Update = FMUSIC_UpdateXM;
    mod->defaultglobalvolume = 64;

    FSOUND_File_Seek(fp, 60, SEEK_SET);
    FSOUND_File_Read(&headersize, 4, fp);
    FSOUND_File_Read(&mod->numorders, 6, fp);          // numorders, restart, numchannels
    FSOUND_File_Read(&numpatterns, 2, fp);
    FSOUND_File_Read(&mod->numinsts, 0x108, fp);       // numinsts, flags, speed, bpm, orderlist
    FSOUND_File_Seek(fp, headersize + 60, SEEK_SET);

    // patterns referenced by the order list
    mod->numpatterns = 0;
    for (int count = 0; count < mod->numorders; ++count) {
        if (mod->orderlist[count] >= mod->numpatterns)
            mod->numpatterns = mod->orderlist[count] + 1;
    }
    mod->numpatternsmem = numpatterns < mod->numpatterns ? mod->numpatterns : numpatterns;
    mod->pattern = (FMUSIC_PATTERN *)calloc(mod->numpatternsmem * sizeof(FMUSIC_PATTERN), 1);

    // ===== PATTERNS =====
    for (int count = 0; count < numpatterns; ++count) {
        FMUSIC_PATTERN *pptr = &mod->pattern[count];
        unsigned char packingtype = 0;
        unsigned short rows;
        unsigned short patternsize;

        FSOUND_File_Read(&patternheadersize, 4, fp);
        FSOUND_File_Read(&packingtype, 1, fp);
        FSOUND_File_Read(&rows, 2, fp);
        pptr->rows = rows;
        FSOUND_File_Read(&patternsize, 2, fp);

        pptr->data = (FMUSIC_NOTE *)calloc(mod->numchannels * pptr->rows * sizeof(FMUSIC_NOTE), 1);
        if (!patternsize)
            continue;

        FMUSIC_NOTE *nptr = pptr->data;
        for (int count2 = 0; count2 < mod->numchannels * pptr->rows; ++count2, ++nptr) {
            unsigned char dat;
            FSOUND_File_Read(&dat, 1, fp);
            if (dat & 0x80) {
                if (dat & 1)
                    FSOUND_File_Read(&nptr->note, 1, fp);
                if (dat & 2)
                    FSOUND_File_Read(&nptr->number, 1, fp);
                if (dat & 4)
                    FSOUND_File_Read(&nptr->volume, 1, fp);
                if (dat & 8)
                    FSOUND_File_Read(&nptr->effect, 1, fp);
                if (dat & 16)
                    FSOUND_File_Read(&nptr->eparam, 1, fp);
            } else {
                if (dat)
                    nptr->note = dat;
                FSOUND_File_Read(&nptr->number, 4, fp);
            }
            if (nptr->note == 97)
                nptr->note = 0xff;   // key off
            if (nptr->number > 0x80)
                nptr->number = 0;
        }
    }

    // empty patterns referenced by the order list but not stored
    for (int count = numpatterns; count < mod->numpatterns; ++count) {
        FMUSIC_PATTERN *pptr = &mod->pattern[count];
        pptr->rows = 64;
        pptr->data = (FMUSIC_NOTE *)calloc(mod->numchannels * 64 * sizeof(FMUSIC_NOTE), 1);
    }

    // ===== INSTRUMENTS =====
    mod->instrument = (FMUSIC_INSTRUMENT *)calloc(mod->numinsts * sizeof(FMUSIC_INSTRUMENT), 1);
    for (int count = 0; count < mod->numinsts; ++count) {
        FMUSIC_INSTRUMENT *iptr = &mod->instrument[count];
        unsigned short numsamples;
        int instrumentsize;

        int firstsampleoffset = FSOUND_File_Tell(fp);
        FSOUND_File_Read(&instrumentsize, 4, fp);
        firstsampleoffset += instrumentsize;
        FSOUND_File_Seek(fp, 23, SEEK_CUR);   // name and type
        FSOUND_File_Read(&numsamples, 2, fp);
        if (numsamples > 16)
            return 0;
        iptr->numsamples = numsamples;

        if (!numsamples) {
            for (int count2 = 0; count2 < 16; ++count2)
                iptr->sample[count2] = &FMUSIC_DummySample;
            FSOUND_File_Seek(fp, firstsampleoffset, SEEK_SET);
            continue;
        }

        int sampleheadersize;
        FSOUND_File_Read(&sampleheadersize, 4, fp);
        FSOUND_File_Read(iptr->keymap, 96, fp);
        FSOUND_File_Read(iptr->VOLPoints, 48, fp);
        FSOUND_File_Read(iptr->PANPoints, 48, fp);
        FSOUND_File_Read(&iptr->VOLnumpoints, 16, fp);   // counts, sustain/loop points, types, vibrato, fade
        iptr->VOLfade *= 2;
        if (iptr->VOLnumpoints < 2)
            iptr->VOLtype = 0;
        if (iptr->PANnumpoints < 2)
            iptr->PANtype = 0;
        FSOUND_File_Seek(fp, firstsampleoffset, SEEK_SET);

        // sample headers
        unsigned int count2 = 0;
        for (; count2 < numsamples; ++count2) {
            FSOUND_SAMPLE *sptr = (FSOUND_SAMPLE *)calloc(sizeof(FSOUND_SAMPLE), 1);
            iptr->sample[count2] = sptr;
            FSOUND_File_Read(&sptr->length, 14, fp);     // length, loop, volume, finetune
            sptr->loopmode = FSOUND_LOOP_OFF;
            sptr->bits = 8;

            unsigned char dat;
            FSOUND_File_Read(&dat, 1, fp);
            if (dat & 1)
                sptr->loopmode = (sptr->loopmode & ~FSOUND_LOOP_OFF) | FSOUND_LOOP_NORMAL;
            if (dat & 2)
                sptr->loopmode = (sptr->loopmode & ~(FSOUND_LOOP_OFF | FSOUND_LOOP_NORMAL)) | FSOUND_LOOP_BIDI;
            if (dat & 16)
                sptr->bits = 16;

            if (sptr->loopmode & FSOUND_LOOP_OFF) {
                sptr->loopstart = 0;
                sptr->looplen = sptr->length;
            }
            if (sptr->bits == 16) {
                sptr->length >>= 1;
                sptr->loopstart >>= 1;
                sptr->looplen >>= 1;
            }
            if (!sptr->looplen) {
                sptr->loopstart = 0;
                sptr->looplen = sptr->length;
                sptr->loopmode = FSOUND_LOOP_OFF;
            }

            unsigned char pan;
            FSOUND_File_Read(&pan, 1, fp);
            sptr->defpan = pan;
            unsigned char relative;
            FSOUND_File_Read(&relative, 1, fp);
            sptr->relative = (signed char)relative;
            FSOUND_File_Seek(fp, 23, SEEK_CUR);   // reserved and name

            unsigned int size = sptr->length * 2;
            if (sptr->buff)
                free(sptr->buff);
            sptr->buff = size ? (short *)calloc(size + 16, 1) : nullptr;
        }
        for (; count2 < 16; ++count2)
            iptr->sample[count2] = &FMUSIC_DummySample;

        // sample data
        for (unsigned int s = 0; s < numsamples; ++s) {
            FSOUND_SAMPLE *sptr = iptr->sample[s];
            unsigned int length = sptr->length;
            unsigned int bytes = sptr->bits * length >> 3;
            if (!length)
                continue;

            unsigned char *buff = (unsigned char *)calloc(length * 2 + 16, 1);
            if (mod->samplecallback) {
                mod->samplecallback(buff, bytes, (char)sptr->bits, count, s);
                FSOUND_File_Seek(fp, bytes, SEEK_CUR);
            } else {
                FSOUND_File_Read(buff, bytes, fp);
            }

            if (sptr->bits == 8) {
                short *wptr = sptr->buff;
                for (int i = 0; i < (int)sptr->length; ++i)
                    *wptr++ = (short)(buff[i] << 8);
                sptr->bits = 16;
                free(buff);
            } else {
                free(sptr->buff);
                sptr->buff = (short *)buff;
            }
            sampleLoaded(sptr, sptr, count, s);

            // delta decode
            if (!mod->samplecallback) {
                short previous = 0;
                short *wptr = sptr->buff;
                for (unsigned int i = 0; i < sptr->length; ++i) {
                    previous = (short)(*wptr + previous);
                    *wptr++ = previous;
                }
            }

            // extra sample past the loop end for the interpolating mixer
            short *data = sptr->buff;
            if (sptr->loopmode == FSOUND_LOOP_BIDI)
                data[sptr->loopstart + sptr->looplen] = data[sptr->loopstart + sptr->looplen - 1];
            else if (sptr->loopmode == FSOUND_LOOP_NORMAL)
                data[sptr->loopstart + sptr->looplen] = data[sptr->loopstart];
        }
    }
    return 1;
}
