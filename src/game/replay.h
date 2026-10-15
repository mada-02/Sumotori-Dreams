// Replay recording (out.dat) and playback (in.dat or the file given on the
// command line).  A replay is a stream of 32-bit words:
//   1                      end of frame
//   2 body pos[3] rot[9]   body moved
//   3 body ...             body created (vertices, faces, material, uv offset, break threshold)
//   4                      start of a recording
//   5 body                 body removed
//   6 pos[3] rot[9]        camera
//   7 id pitch volume slot sound
#pragma once

#include "../core/common.h"

// 0x18 bytes
struct Replay {
    int frameCount;           // +0x00
    ArrayList<int> data;      // +0x04
    int *cursor;              // +0x10
    int *end;                 // +0x14

    Replay();                              // @ 0x40d785
    void readFrameCount(const char *name); // @ 0x40d487
    void save(const char *name);           // @ 0x40d5bf
    void reserve(int words);               // @ 0x40d681
    void load(const char *name);           // @ 0x40d6cd
    void reset();                          // @ 0x40d74b
};

extern Replay g_replayIn;          // @ 0xc06830
extern Replay g_replayOut;         // @ 0xc0684c
extern char g_recording;           // @ 0xc06864
extern int g_replayFrames;         // @ 0xc0681c frames recorded so far

void replayRecordFrameMarker();                                      // @ 0x40d4c8
void replayRecordSound(int id, float pitch, float volume, int slot); // @ 0x40d4e3
void replayStopRecording();                                          // @ 0x40d623
void replayStartRecording();                                         // @ 0x40d79c
void replayUpdate();                                                 // @ 0x40d7cf
void doNothing();                                                    // @ 0x407ca6
