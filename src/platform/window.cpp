// Window procedure, message pump, timing and shutdown.
#include "window.h"
#include "input.h"
#include "../audio/music.h"
#include "../game/game.h"
#include <float.h>

HWND g_mainWindow;
HINSTANCE g_instance;
char *g_commandLineFile;
int g_lastTick;

char g_keyDown[256];
char g_keyPressed[256];
int g_mouseX = -1;
int g_mouseY;
int g_escapePressed;
int g_quit;

static char g_cursorVisible = 1;   // @ 0x453ce4

// @ 0x4168c7
void pumpMessages()
{
    MSG msg;
    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

// @ 0x416900
void setFpuControl()
{
    // FLDCW 0x77f: 64-bit (extended) precision, round to nearest, all
    // exceptions masked. Direct3D is created without FPU_PRESERVE, so this is
    // re-applied at the start and end of every frame.
#if defined(_M_IX86)
    unsigned short cw = 0x77f;
    __asm fldcw cw
#else
    _controlfp(_PC_64 | _RC_NEAR | _MCW_EM, _MCW_PC | _MCW_RC | _MCW_EM);
#endif
}

// @ 0x41690d
unsigned getTicks()
{
    return timeGetTime() * (unsigned)g_ticksPerSecond / 1000u / (unsigned)g_timeDivider;
}

// @ 0x41692c
void shutdown()
{
    DestroyWindow(g_mainWindow);
    musicStop();
    exit(0);
}

// @ 0x4169a7
void showCursor(char show)
{
    if (g_cursorVisible == show)
        return;
    g_cursorVisible = show;
    ShowCursor((unsigned char)show);
}

// @ 0x4169c3
LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CLOSE:
        return 0;
    case WM_KEYDOWN: {
        int scan = ((int)lParam >> 16) & 0xff;
        if (scan == 1)
            g_escapePressed = 1;
        g_keyDown[scan] = 1;
        g_keyPressed[scan] = 1;
        break;
    }
    case WM_KEYUP:
        g_keyDown[(lParam >> 16) & 0xff] = 0;
        break;
    case WM_LBUTTONDOWN:
        g_mouseX = lParam & 0xffff;
        g_mouseY = (unsigned)lParam >> 16;
        break;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}
