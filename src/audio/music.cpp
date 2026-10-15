// Background music: MiniFMOD reading the XM module from memory.
#include "music.h"
#include "minifmod.h"
#include "sound.h"

#include "../generated/music_data.inc"

struct MemoryFile {
    int length;                  // @ 0x4eacc0
    int pos;                     // @ 0x4eacc4
    const unsigned char *data;   // @ 0x4eacc8
};

static MemoryFile g_xmFile;      // @ 0x4eacc0
static FMUSIC_MODULE *g_song;    // @ 0x4eacd0

// The original declares the memory file 0x20000 bytes long, which runs past
// the module into unrelated image data; the loader never reads that far, so
// bytes beyond the module read back as zeros here.
static void copyFromImage(void *dest, int offset, int size)
{
    int available = (int)sizeof(kXmSong) - offset;
    if (available < 0)
        available = 0;
    int copied = size < available ? size : available;
    if (copied > 0)
        memcpy(dest, kXmSong + offset, copied);
    if (size > copied)
        memset((char *)dest + copied, 0, size - copied);
}

// @ 0x407c85
static unsigned int memOpen(const char *)
{
    g_xmFile.pos = 0;
    g_xmFile.data = kXmSong;
    g_xmFile.length = 0x20000;
    return (unsigned int)(uintptr_t)&g_xmFile;
}

// @ 0x407ca6
static void memClose(unsigned int)
{
}

// @ 0x407ca7
static int memRead(void *buffer, int size, unsigned int handle)
{
    MemoryFile *file = (MemoryFile *)(uintptr_t)handle;
    if (file->pos + size >= file->length)
        size = file->length - file->pos;
    copyFromImage(buffer, file->pos, size);
    file->pos += size;
    return size;
}

// @ 0x407cdc
static void memSeek(unsigned int handle, int pos, signed char mode)
{
    MemoryFile *file = (MemoryFile *)(uintptr_t)handle;
    if (mode == SEEK_SET)
        file->pos = pos;
    else if (mode == SEEK_CUR)
        file->pos += pos;
    else if (mode == SEEK_END)
        file->pos = file->length + pos;
    if (file->pos > file->length)
        file->pos = file->length;
}

// @ 0x407d15
static int memTell(unsigned int handle)
{
    return ((MemoryFile *)(uintptr_t)handle)->pos;
}

// @ 0x407d1d
void musicStart()
{
    if (!g_soundEnabled)
        return;
    FSOUND_File_SetCallbacks(memOpen, memClose, memRead, memSeek, memTell);
    FSOUND_Init(44100, 0);
    g_song = FMUSIC_LoadSong("f.xm", nullptr);
    FMUSIC_PlaySong(g_song);
}

// @ 0x407d6b
void musicStartDefault()
{
    g_musicOrder = 3;
    musicStart();
}

// @ 0x407d7a
void musicPlay(int order)
{
    if (!g_soundEnabled)
        return;
    FMUSIC_FreeSong(g_song);
    FSOUND_Close();
    g_musicOrder = order;
    musicStart();
}

// @ 0x407da3
void musicStop()
{
    FMUSIC_FreeSong(g_song);
    FSOUND_Close();
}
