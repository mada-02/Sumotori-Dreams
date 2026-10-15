// Replay recording and playback.
#include "replay.h"
#include "camera.h"
#include "game.h"
#include "menu.h"
#include "sumo.h"
#include "../physics/world.h"
#include "../platform/input.h"
#include "../platform/window.h"
#include "../render/water.h"
#include "../audio/sound.h"

Replay g_replayIn;
Replay g_replayOut;
char g_recording;
int g_replayFrames;

// @ 0x407ca6
void doNothing()
{
}

// @ 0x40d785
Replay::Replay()
{
    data.first = nullptr;
    data.last = nullptr;
    data.capacityEnd = nullptr;
    reset();
}

// @ 0x40d487
void Replay::readFrameCount(const char *name)
{
    FILE *f = fopen(name, "rb");
    frameCount = 0;
    if (f) {
        int value;
        fread(&value, 1, 4, f);
        frameCount = value;
        fclose(f);
    }
}

// @ 0x40d5bf
void Replay::save(const char *name)
{
    if (frameCount == 0)
        return;
    FILE *f = fopen(name, "ab");
    ftell(f);
    fwrite(&data.at(0), 1, (cursor - &data.at(0)) * 4, f);
    fclose(f);
}

// @ 0x40d681
void Replay::reserve(int words)
{
    int used = (int)(cursor - &data.at(0));
    if ((unsigned)data.size() < (unsigned)(words + used)) {
        data.resize(words + used);
        end = nullptr;
        cursor = &data.at(0) + used;
    }
}

// @ 0x40d6cd
void Replay::load(const char *name)
{
    FILE *f = fopen(name, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned words = (unsigned)size >> 2;
    data.resize(words);
    fread(&data.at(0), 1, size, f);
    fclose(f);
    cursor = &data.at(0);
    end = cursor + words;
}

// @ 0x40d74b
void Replay::reset()
{
    data.last = data.first;
    data.resize(0x40000);
    end = nullptr;
    cursor = &data.at(0);
    reserve(0x10000);
    frameCount = 0;
}

// @ 0x40d4c8
void replayRecordFrameMarker()
{
    if (g_recording)
        *g_replayOut.cursor++ = 4;
}

// @ 0x40d4e3
void replayRecordSound(int id, float pitch, float volume, int slot)
{
    if ((g_cameraMode == 1 || g_cameraMode == 3) && g_recording) {
        *g_replayOut.cursor++ = 7;
        *g_replayOut.cursor++ = id;
        *(float *)g_replayOut.cursor++ = pitch;
        *(float *)g_replayOut.cursor++ = volume;
        *g_replayOut.cursor++ = slot;
    }
}

// @ 0x40d623
void replayStopRecording()
{
    g_replayOut.save("out.dat");
    g_replayOut.cursor = g_replayOut.end;
    g_recording = 0;
}

// @ 0x40d79c
void replayStartRecording()
{
    g_replayOut.reset();
    g_recording = 1;
    g_replayOut.readFrameCount("out.dat");
    *g_replayOut.cursor++ = 4;
}

static int readWord()
{
    return *g_replayIn.cursor++;
}

static float readFloat()
{
    return *(float *)g_replayIn.cursor++;
}

// @ 0x40d7cf
// Called once per simulation step: handles the replay keys ('3', '4', '5'),
// records the world while recording and steps the playback.
void replayUpdate()
{
    if (g_keyPressed[5]) {
        g_keyPressed[5] = 0;
        if (g_recording)
            replayStopRecording();
        else
            replayStartRecording();
    }
    if (g_keyPressed[4] && g_cameraMode == 1) {
        g_keyPressed[4] = 0;
        if (g_editorMode) {
            g_keyPressed[0x3c] = 1;   // F2: reload the level
            doNothing();
        } else {
            startMatch();
        }
        g_replayOut.reset();
        g_replayOut.frameCount = 0;
        g_recording = 0;
    }
    if (g_keyPressed[6]) {
        g_keyPressed[6] = 0;
        if (g_recording)
            replayStopRecording();
        g_keyPressed[0x3c] = 1;
        doNothing();
        replayStartRecording();
    }

    if ((g_cameraMode == 1 || g_cameraMode == 3) && g_recording) {
        g_replayOut.reserve(0x10000);
        int index = 0;
        for (Body *b = g_bodies; b < g_bodyEnd; ++b, ++index) {
            int *&out = g_replayOut.cursor;
            if (!b->removed) {
                if (!b->recorded) {
                    b->recorded = 1;
                    *out++ = 3;
                    *out++ = index;
                    int vertices = (int)(b->vertEnd - b->vertBegin);
                    *out++ = vertices;
                    for (int i = 0; i < vertices; ++i) {
                        const int *src = (const int *)&b->vertBegin[i].pos;
                        for (int k = 0; k < 3; ++k)
                            *out++ = src[k];
                    }
                    *out++ = (int)(b->loopEnd - b->loopBegin);
                    int faces = (int)(b->faceEnd - b->faceBegin);
                    *out++ = faces;
                    for (int i = 0; i < faces; ++i) {
                        Face *f = &b->faceBegin[i];
                        *out++ = f->count;
                        for (int k = 0; k < f->count; ++k)
                            *out++ = f->loop[k].index;
                    }
                    *out++ = b->material;
                    *(float *)out++ = b->uvScale;
                    const int *uv = (const int *)&b->uvOffset;
                    for (int k = 0; k < 3; ++k)
                        *out++ = uv[k];
                    *(float *)out++ = b->breakThreshold;
                }
                if ((b->recordedPos - b->pos).lengthSq() > 1e-6f) {
                    b->recordedPos = b->pos;
                    *out++ = 2;
                    *out++ = index;
                    const int *p = (const int *)&b->pos;
                    for (int k = 0; k < 3; ++k)
                        *out++ = p[k];
                    const int *r = (const int *)&b->rot;
                    for (int k = 0; k < 9; ++k)
                        *out++ = r[k];
                }
            } else if (b->recorded == 1) {
                b->recorded = 0;
                *out++ = 5;
                *out++ = index;
            }
        }
        int *&out = g_replayOut.cursor;
        *out++ = 1;
        *out++ = 6;
        const int *p = (const int *)&g_viewPos;
        for (int k = 0; k < 3; ++k)
            *out++ = p[k];
        const int *r = (const int *)&g_viewRot;
        for (int k = 0; k < 9; ++k)
            *out++ = r[k];
        ++g_replayOut.frameCount;
    }

    if (g_cameraMode == 2 || g_cameraMode == 3) {
        // F3 = half speed, F4 = double speed
        if ((g_frame + 1) % 2 == 0 || !g_keyDown[0x3d]) {
            int steps = 1;
            if (g_keyDown[0x3e])
                steps = 2;
            do {
                if (g_replayIn.cursor >= g_replayIn.end)
                    g_replayIn.load(*g_commandLineFile ? g_commandLineFile : "in.dat");

                Vec3 sum = V3(0.0f, 0.0f, 0.0f);
                float moved = 0.0f;
                int op;
                do {
                    op = 1;
                    if (g_replayIn.cursor >= g_replayIn.end) {
                        g_quit = 1;
                    } else {
                        op = readWord();
                        if (op < 0 || op > 7)
                            g_replayIn.cursor = g_replayIn.end;
                    }
                    switch (op) {
                    case 2: {
                        Body *b = &g_bodies[readWord()];
                        Vec3 old = b->pos;
                        int *p = (int *)&b->pos;
                        for (int k = 0; k < 3; ++k)
                            p[k] = readWord();
                        int *r = (int *)&b->rot;
                        for (int k = 0; k < 9; ++k)
                            r[k] = readWord();
                        b->vel = b->pos - old;
                        sum.x = sum.x + b->pos.x;
                        sum.y = sum.y + b->pos.y;
                        sum.z = sum.z + b->pos.z;
                        moved = moved + 1.0f;
                        break;
                    }
                    case 3: {
                        int index = readWord();
                        Body *b = &g_bodies[index];
                        while (g_bodyEnd <= b) {
                            g_bodyEnd->removed = 1;
                            ++g_bodyEnd;
                        }
                        b->removed = 0;

                        int vertices = readWord();
                        sumoAssert(vertices <= 100 && vertices >= 0);
                        b->vertBegin = (Vertex *)malloc(vertices * sizeof(Vertex));
                        sumoAssert(b->vertBegin != nullptr);
                        b->vertEnd = b->vertBegin + vertices;
                        for (int i = 0; i < vertices; ++i) {
                            int *p = (int *)&b->vertBegin[i].pos;
                            for (int k = 0; k < 3; ++k)
                                p[k] = readWord();
                            b->vertBegin[i].above = 0;
                            b->vertBegin[i].created = 0;
                            b->vertBegin[i].newIndex = 0;
                        }

                        int loops = readWord();
                        int faces = readWord();
                        sumoAssert(loops <= 100 && loops >= 0);
                        sumoAssert(faces <= 100 && faces >= 0);
                        b->faceBegin = (Face *)malloc(faces * sizeof(Face));
                        b->faceEnd = b->faceBegin + faces;
                        b->loopBegin = (FaceVertex *)malloc(loops * sizeof(FaceVertex));
                        b->loopEnd = b->loopBegin + loops;
                        FaceVertex *loop = b->loopBegin;
                        for (int i = 0; i < faces; ++i) {
                            Face *f = &b->faceBegin[i];
                            f->count = readWord();
                            f->loop = loop;
                            f->normal.z = 0.0f;
                            f->normal.y = 0.0f;
                            f->normal.x = 0.0f;
                            for (int k = 0; k < f->count; ++k) {
                                loop->index = readWord();
                                sumoAssert(f->loop[k].index >= 0);
                                sumoAssert(f->loop[k].index < (int)(b->vertEnd - b->vertBegin));
                                f->loop[k].vertex = &b->vertBegin[f->loop[k].index];
                                ++loop;
                            }
                            facePlane(f);
                        }
                        b->material = readWord();
                        b->uvScale = readFloat();
                        b->init();
                        int *uv = (int *)&b->uvOffset;
                        for (int k = 0; k < 3; ++k)
                            uv[k] = readWord();
                        b->breakThreshold = readFloat();
                        b->pos = V3((float)(index * 2 + 12), (float)(index + 12), (float)(index + 12));
                        b->rot.identity();
                        b->isStatic = 1;
                        break;
                    }
                    case 4:
                        waterCreate();
                        buildDojo(0);
                        g_frame = 0;
                        replayRecordFrameMarker();
                        freeCameraSet(V3(40.0f, 35.0f, -10.0f), 0.0f);
                        break;
                    case 5:
                        g_bodies[readWord()].removed = 1;
                        break;
                    case 6:
                        if (g_cameraMode == 3) {
                            int skipped[12];
                            for (int k = 0; k < 12; ++k)
                                skipped[k] = readWord();
                        } else {
                            int *p = (int *)&g_viewPos;
                            for (int k = 0; k < 3; ++k)
                                p[k] = readWord();
                            int *r = (int *)&g_viewRot;
                            for (int k = 0; k < 9; ++k)
                                r[k] = readWord();
                        }
                        break;
                    case 7: {
                        int id = readWord();
                        float pitch = readFloat();
                        float volume = readFloat();
                        int slot = readWord();
                        playSound(id, pitch, volume, slot);
                        break;
                    }
                    }
                } while (op != 1);

                // the free camera follows the centre of everything that moved
                float inv = 1.0f / moved;
                sum.x = sum.x * inv;
                sum.y = sum.y * inv;
                sum.z = sum.z * inv;
                float k = 0.02f;
                Vec3 step = (sum - g_viewFocus) * k;
                g_viewFocus.x = g_viewFocus.x + step.x;
                g_viewFocus.y = g_viewFocus.y + step.y;
                g_viewFocus.z = g_viewFocus.z + step.z;
            } while (--steps > 0);
        }
    }

    g_replayFrames = g_replayOut.frameCount;
}
