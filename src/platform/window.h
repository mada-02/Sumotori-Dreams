// Main window, message pump, timing and process shutdown.
#pragma once

#include "../core/common.h"

extern HWND g_mainWindow;               // @ 0xd0f4f0
extern HINSTANCE g_instance;            // @ 0xd0f4e8
extern char *g_commandLineFile;         // @ 0xd0f3d8 mod file to load at startup (never set)
extern int g_lastTick;                  // @ 0xd0f4ec

void pumpMessages();                    // @ 0x4168c7
void setFpuControl();                   // @ 0x416900 64-bit precision, all exceptions masked
unsigned getTicks();                    // @ 0x41690d simulation ticks since boot
[[noreturn]] void shutdown();           // @ 0x41692c
void showCursor(char show);             // @ 0x4169a7
LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);   // @ 0x4169c3
