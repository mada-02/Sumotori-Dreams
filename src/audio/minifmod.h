// Statically linked MiniFMOD 1.7 XM player (waveOut output), as modified for
// Sumotori Dreams: unused effects are compiled out, only linear frequency
// tables are supported, 256 mixer channels are allocated and FMUSIC_PlaySong
// starts at the order in g_musicOrder.
//
// Names follow the MiniFMOD sources; layouts and behaviour follow the binary.
#pragma once

#include "../core/common.h"
#include <mmsystem.h>

// ---------------------------------------------------------------------------
// File callbacks
// ---------------------------------------------------------------------------
typedef unsigned int (*FSOUND_OpenCallback)(const char *name);
typedef void (*FSOUND_CloseCallback)(unsigned int handle);
typedef int (*FSOUND_ReadCallback)(void *buffer, int size, unsigned int handle);
typedef void (*FSOUND_SeekCallback)(unsigned int handle, int pos, signed char mode);
typedef int (*FSOUND_TellCallback)(unsigned int handle);

struct FSOUND_FILE_HANDLE {
    unsigned char type;           // 0x00
    unsigned char pad[15];
    unsigned int userhandle;      // 0x10
    int length;                   // 0x14
};
static_assert(sizeof(FSOUND_FILE_HANDLE) == 0x18, "FSOUND_FILE_HANDLE");

// ---------------------------------------------------------------------------
// Samples and mixer channels
// ---------------------------------------------------------------------------
enum {
    FSOUND_LOOP_OFF = 1,
    FSOUND_LOOP_NORMAL = 2,
    FSOUND_LOOP_BIDI = 4,
};

struct FSOUND_SAMPLE {
    short *buff;                  // 0x00 16 bit sample data
    unsigned int length;          // 0x04 in samples
    unsigned int loopstart;       // 0x08
    unsigned int looplen;         // 0x0c
    unsigned char defvol;         // 0x10
    signed char finetune;         // 0x11
    unsigned char pad12[2];
    int deffreq;                  // 0x14
    int defpan;                   // 0x18
    unsigned char bits;           // 0x1c
    unsigned char loopmode;       // 0x1d
    unsigned char globalvol;      // 0x1e
    signed char relative;         // 0x1f
    int middlec;                  // 0x20
    unsigned int susloopbegin;    // 0x24
    unsigned int susloopend;      // 0x28
    unsigned char vibspeed;       // 0x2c
    unsigned char vibdepth;       // 0x2d
    unsigned char vibtype;        // 0x2e
    unsigned char vibrate;        // 0x2f
};
static_assert(sizeof(FSOUND_SAMPLE) == 0x30, "FSOUND_SAMPLE");

struct FSOUND_CHANNEL {
    int index;                    // 0x00
    int volume;                   // 0x04
    int frequency;                // 0x08
    int pan;                      // 0x0c
    int actualvolume;             // 0x10
    int actualpan;                // 0x14
    unsigned int sampleoffset;    // 0x18
    FSOUND_SAMPLE *sptr;          // 0x1c
    unsigned int leftvolume;      // 0x20
    unsigned int rightvolume;     // 0x24
    unsigned int mixpos;          // 0x28 32:32 fixed point position
    unsigned int mixposlo;        // 0x2c
    unsigned int speedlo;         // 0x30
    unsigned int speedhi;         // 0x34
    unsigned int speeddir;        // 0x38 1 = forwards, 2 = backwards
    unsigned int ramp_lefttarget; // 0x3c
    unsigned int ramp_righttarget;// 0x40
    unsigned int ramp_leftvolume; // 0x44 8 bit fixed point
    unsigned int ramp_rightvolume;// 0x48
    float ramp_leftspeed;         // 0x4c
    float ramp_rightspeed;        // 0x50
    unsigned int ramp_count;      // 0x54
};
static_assert(sizeof(FSOUND_CHANNEL) == 0x58, "FSOUND_CHANNEL");

// ---------------------------------------------------------------------------
// Music
// ---------------------------------------------------------------------------
struct FMUSIC_NOTE {
    unsigned char note;           // 0 = none, 0xff = key off
    unsigned char number;         // instrument number
    unsigned char volume;         // volume column
    unsigned char effect;
    unsigned char eparam;
};
static_assert(sizeof(FMUSIC_NOTE) == 5, "FMUSIC_NOTE");

struct FMUSIC_PATTERN {
    int rows;
    FMUSIC_NOTE *data;
};

struct FMUSIC_INSTRUMENT {
    int numsamples;               // 0x000
    FSOUND_SAMPLE *sample[16];    // 0x004
    unsigned char keymap[96];     // 0x044
    unsigned short VOLPoints[40]; // 0x0a4 position / value pairs
    unsigned short PANPoints[40]; // 0x0f4
    unsigned char VOLnumpoints;   // 0x144
    unsigned char PANnumpoints;   // 0x145
    unsigned char VOLsustain;     // 0x146
    unsigned char VOLLoopStart;   // 0x147
    unsigned char VOLLoopEnd;     // 0x148
    unsigned char PANsustain;     // 0x149
    unsigned char PANLoopStart;   // 0x14a
    unsigned char PANLoopEnd;     // 0x14b
    unsigned char VOLtype;        // 0x14c 1 = on, 2 = sustain, 4 = loop
    unsigned char PANtype;        // 0x14d
    unsigned char VIBtype;        // 0x14e
    unsigned char VIBsweep;       // 0x14f
    unsigned char VIBdepth;       // 0x150
    unsigned char VIBrate;        // 0x151
    unsigned short VOLfade;       // 0x152
};
static_assert(sizeof(FMUSIC_INSTRUMENT) == 0x154, "FMUSIC_INSTRUMENT");

enum {
    FMUSIC_FREQ = 1,
    FMUSIC_VOLUME = 2,
    FMUSIC_PAN = 4,
    FMUSIC_TRIGGER = 8,
    FMUSIC_STOP = 0x20,
};

struct FMUSIC_CHANNEL {
    unsigned char note;           // 0x00
    unsigned char unused01;
    unsigned char notectrl;       // 0x02 FMUSIC_* flags
    unsigned char unused03;
    FSOUND_CHANNEL *cptr;         // 0x04
    FSOUND_SAMPLE *sptr;          // 0x08
    int freq;                     // 0x0c period
    int volume;                   // 0x10
    int pan;                      // 0x14
    int voldelta;                 // 0x18
    int freqdelta;                // 0x1c
    int pandelta;                 // 0x20
    int unused24;
    int envvoltick;               // 0x28
    int envvolpos;                // 0x2c
    int envvolfrac;               // 0x30
    int envvol;                   // 0x34
    int envvoldelta;              // 0x38
    unsigned char envvolstopped;  // 0x3c
    unsigned char pad3d[3];
    int envpantick;               // 0x40
    int envpanpos;                // 0x44
    int envpanfrac;               // 0x48
    int envpan;                   // 0x4c
    int envpandelta;              // 0x50
    unsigned char envpanstopped;  // 0x54
    unsigned char pad55[3];
    int fadeoutvol;               // 0x58
    int ivibpos;                  // 0x5c
    int ivibsweeppos;             // 0x60
    unsigned char unused64;
    unsigned char keyoff;         // 0x65
    unsigned char inst;           // 0x66
    unsigned char realnote;       // 0x67
    int period;                   // 0x68
    unsigned char recenteffect;   // 0x6c
    unsigned char pad6d[3];
    unsigned int sampleoffset;    // 0x70
    unsigned char unused74[4];
    unsigned char portadown;      // 0x78
    unsigned char portaup;        // 0x79
    unsigned char unused7a[4];
    unsigned char retrigx;        // 0x7e
    unsigned char retrigy;        // 0x7f
    int portatarget;              // 0x80
    unsigned char portaspeed;     // 0x84
    signed char vibpos;           // 0x85
    unsigned char vibspeed;       // 0x86
    unsigned char vibdepth;       // 0x87
    unsigned char unused88;
    signed char trempos;          // 0x89
    unsigned char unused8a[8];
    unsigned char tremorpos;      // 0x92
    unsigned char unused93[15];
    unsigned char wavecontrol;    // 0xa2
    unsigned char unuseda3[6];
    unsigned char fineportadown;  // 0xa9
    unsigned char unusedaa[2];
};
static_assert(sizeof(FMUSIC_CHANNEL) == 0xac, "FMUSIC_CHANNEL");

struct FMUSIC_MODULE;
typedef void (*FMUSIC_UPDATECALLBACK)(FMUSIC_MODULE *mod);
typedef void (*FMUSIC_SAMPLELOADCALLBACK)(void *buff, int length, int bits, int instno, int sampno);

struct FMUSIC_MODULE {
    FMUSIC_PATTERN *pattern;          // 0x000
    FMUSIC_INSTRUMENT *instrument;    // 0x004
    int mixer_samplesleft;            // 0x008
    int mixer_samplespertick;         // 0x00c
    short numorders;                  // 0x010
    short restart;                    // 0x012
    short numchannels;                // 0x014
    short pad16;
    int numpatterns;                  // 0x018
    int numpatternsmem;               // 0x01c
    short numinsts;                   // 0x020
    unsigned short flags;             // 0x022 bit 0: linear frequency table
    short defaultspeed;               // 0x024
    short defaultbpm;                 // 0x026
    unsigned char orderlist[256];     // 0x028
    unsigned char defaultglobalvolume;// 0x128
    unsigned char pad129[3];
    int globalvolume;                 // 0x12c
    int unused130;
    int tick;                         // 0x134
    int speed;                        // 0x138
    int bpm;                          // 0x13c
    int row;                          // 0x140
    int order;                        // 0x144
    int patterndelay;                 // 0x148
    int nextrow;                      // 0x14c
    int nextorder;                    // 0x150
    int time_ms;                      // 0x154
    FMUSIC_UPDATECALLBACK initCallback;      // 0x158 never set
    FMUSIC_UPDATECALLBACK Update;            // 0x15c
    FMUSIC_SAMPLELOADCALLBACK samplecallback;// 0x160
};
static_assert(sizeof(FMUSIC_MODULE) == 0x164, "FMUSIC_MODULE");

#pragma pack(push, 1)
struct FMUSIC_TIMEINFO {
    unsigned char order;
    unsigned char row;
    unsigned int ms;
};
#pragma pack(pop)

// ---------------------------------------------------------------------------
// Globals shared with the mixer
// ---------------------------------------------------------------------------
extern FSOUND_CHANNEL FSOUND_Channel[256];  // @ 0xd107c0
extern int FSOUND_MixRate;                  // @ 0xd175b4
extern unsigned int mix_volumerampsteps;    // @ 0xd0fe84
extern float mix_1overvolumerampsteps;      // @ 0xd0fe88
extern int g_musicOrder;                    // @ 0xd0fa18 order FMUSIC_PlaySong starts at

// ---------------------------------------------------------------------------
// API
// ---------------------------------------------------------------------------
void FSOUND_File_SetCallbacks(FSOUND_OpenCallback open, FSOUND_CloseCallback close, FSOUND_ReadCallback read,
                              FSOUND_SeekCallback seek, FSOUND_TellCallback tell);       // @ 0x419023
FSOUND_FILE_HANDLE *FSOUND_File_Open(const char *name, signed char type, int length);   // @ 0x419090
void FSOUND_File_Close(FSOUND_FILE_HANDLE *handle);                                      // @ 0x4190cc
int FSOUND_File_Read(void *buffer, int size, FSOUND_FILE_HANDLE *handle);                // @ 0x4190e8
void FSOUND_File_Seek(FSOUND_FILE_HANDLE *handle, int pos, signed char mode);            // @ 0x419106
int FSOUND_File_Tell(FSOUND_FILE_HANDLE *handle);                                        // @ 0x419123

signed char FSOUND_Init(int mixrate, int vcmmode);                                       // @ 0x4171d9
void FSOUND_Close();                                                                     // @ 0x416f90
void FSOUND_Software_Fill();                                                             // @ 0x416fa9
DWORD WINAPI FSOUND_Software_DoubleBufferThread(LPVOID param);                           // @ 0x417121
void FSOUND_MixerClipCopy_Float32(void *dest, void *src, int len);                       // @ 0x417320
void FSOUND_Mixer_FPU_Ramp(void *mixptr, int len, char returnaddress);                   // @ 0x417379

void FMUSIC_SetBPM(FMUSIC_MODULE *mod, int bpm);                                         // @ 0x416be4
signed char FMUSIC_StopSong(FMUSIC_MODULE *mod);                                         // @ 0x416c19
signed char FMUSIC_FreeSong(FMUSIC_MODULE *mod);                                         // @ 0x416cad
signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod);                                         // @ 0x416d7e
FMUSIC_MODULE *FMUSIC_LoadSong(const char *name, FMUSIC_SAMPLELOADCALLBACK callback);    // @ 0x416f38

void FMUSIC_XM_Portamento(FMUSIC_CHANNEL *cptr);                                         // @ 0x4179d8
void FMUSIC_XM_Vibrato(FMUSIC_CHANNEL *cptr);                                            // @ 0x417a1b
void FMUSIC_XM_InstrumentVibrato(FMUSIC_CHANNEL *cptr, FMUSIC_INSTRUMENT *iptr);         // @ 0x417abb
void FMUSIC_XM_ProcessEnvelope(FMUSIC_CHANNEL *cptr, int *pos, int *tick, unsigned char type, int numpoints,
                               unsigned short *points, unsigned char loopend, unsigned char loopstart,
                               unsigned char sustain, int *value, int *valfrac, unsigned char *envstopped,
                               int *envdelta, unsigned char control);                    // @ 0x417bac
void FMUSIC_XM_ProcessVolumeByte(FMUSIC_CHANNEL *cptr, unsigned char volume);            // @ 0x417c9f
void FMUSIC_UpdateFlags(FMUSIC_CHANNEL *cptr, FSOUND_SAMPLE *sptr, FMUSIC_MODULE *mod);  // @ 0x417d95
void FMUSIC_XM_Resetcptr(FMUSIC_CHANNEL *cptr, FSOUND_SAMPLE *sptr);                     // @ 0x417fab
void FMUSIC_UpdateXMNote(FMUSIC_MODULE *mod);                                            // @ 0x418029
void FMUSIC_UpdateXMEffects(FMUSIC_MODULE *mod);                                         // @ 0x418446
void FMUSIC_UpdateXM(FMUSIC_MODULE *mod);                                                // @ 0x4188c7
signed char FMUSIC_LoadXM(FMUSIC_MODULE *mod, FSOUND_FILE_HANDLE *fp);                   // @ 0x41897e
