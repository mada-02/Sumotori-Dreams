// Sumotori Dreams - recompilation
// Common definitions shared by every translation unit.
//
// Original: sumofull.exe / sumoeditor.exe (MSVC 7.1, x86, 2010).
// Every function carries the address of its original counterpart in a
// "// @ 0x......" comment; see docs/FUNCTION_MAP.md for the complete table.
#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "fpmath.h"

// The only difference between the two shipped executables: the level editor
// build initialises this flag to 1 (it lives in .data at 0x453cd8 there),
// the game build leaves it zero (.bss at 0xd0f9f8).
#ifdef SUMO_EDITOR
#define SUMO_EDITOR_DEFAULT 1
#else
#define SUMO_EDITOR_DEFAULT 0
#endif
extern int g_editorMode;   // @ 0xd0f9f8 (full) / 0x453cd8 (editor)

// @ 0x404752
// The original "assert": on failure it deliberately walks a null pointer
// forward writing 0x7f until the process faults.
inline void sumoAssert(bool condition)
{
    if (!condition) {
        volatile unsigned char *p = nullptr;
        for (;;) {
            ++p;
            *p = 0x7f;
        }
    }
}

// Growable array used by every container in the game (always POD elements,
// grown with realloc by count/8 + 1).  Instantiated for element sizes 1, 4, 8,
// 12, 16, 24, 28 and 48 in the original image.
template <class T>
struct ArrayList {
    T *first = nullptr;
    T *last = nullptr;
    T *capacityEnd = nullptr;

    int size() const { return (int)(last - first); }
    unsigned usize() const { return (unsigned)(last - first); }
    bool empty() const { return last == first; }

    // @ 0x401000 (uint32), 0x404fee (12), 0x405285 (24), 0x4052a9 (8), 0x405308 (1),
    //   0x408f5e (4), 0x40c109 (12), 0x40d558 (4)
    T &at(unsigned index)
    {
        sumoAssert(index * sizeof(T) < (unsigned)((char *)last - (char *)first));
        return first[index];
    }

    // @ 0x401021 (4), 0x405034 (28), 0x40507d (24), 0x4050ca (8), 0x405110 (12),
    //   0x4052ca (1), 0x40533e (48), 0x40c12b (12), 0x40d579 (4), 0x416594 (4)
    void grow()
    {
        unsigned count = usize();
        unsigned newSize = ((count >> 3) + 1 + count) * (unsigned)sizeof(T);
        sumoAssert(newSize < 0x10000000);
        T *mem = (T *)realloc(first, newSize);
        first = mem;
        capacityEnd = (T *)((char *)mem + newSize);
        last = mem + count;
    }

    // @ 0x401193 (4), 0x40556c (28), 0x405594 (24), 0x4055bc (8), 0x4055e5 (12), 0x4056c6 (1), 0x4057a8 (48)
    void push_back(const T &value)
    {
        if (capacityEnd <= last)
            grow();
        *last = value;
        ++last;
    }

    // @ 0x401111 (4), 0x40c56a (12), 0x40d644 (4), 0x4167d2 (4)
    // Sets the element count; newly exposed elements are zero-filled.
    void resize(int count)
    {
        T *oldFirst = first;
        T *oldLast = last;
        last = first + count;
        if (capacityEnd < last) {
            grow();
            oldLast = first + (oldLast - oldFirst);
        }
        for (; oldLast < last; ++oldLast)
            memset(oldLast, 0, sizeof(T));
    }

    // @ 0x404f9c (also used through the 0x401067 thunk as a destructor)
    void release()
    {
        if (first) {
            free(first);
            first = nullptr;
        }
    }
};

template <class T>
inline T sumoMin(T a, T b) { return b < a ? b : a; }
template <class T>
inline T sumoMax(T a, T b) { return a < b ? b : a; }
