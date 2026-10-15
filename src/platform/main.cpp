// Program entry point and main loop.
#include "config.h"
#include "input.h"
#include "window.h"
#include "../audio/music.h"
#include "../audio/sound.h"
#include "../game/game.h"
#include "../game/level.h"
#include "../game/replay.h"
#include "../game/sumo.h"
#include "../render/d3d.h"
#include "../render/scene.h"

// @ 0x416a3e
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR commandLine, int)
{
    g_instance = instance;
    if (g_commandLineFile && *g_commandLineFile)
        loadModFile(g_commandLineFile);
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

    if (!g_editorMode) {
        configLoad();
        if (configDialog("Sumotori Dreams Full Version") == 2)
            return 0;
    }
    if (g_editorMode)
        g_windowed = 1;

    // "_" on the command line: low quality (2 lights, no shadows)
    if (commandLine[0] == '_') {
        g_lightCount = 2;
        g_shadowsEnabled = 0;
    }

    WNDCLASSEXA wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = mainWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = "archee";
    wc.hIconSm = nullptr;
    RegisterClassExA(&wc);

    HWND window = createMainWindow(instance);
    g_mainWindow = window;
    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);
    pumpMessages();
    initDirect3D();
    soundStart();
    if (g_editorMode)
        createEditorWindow(instance);
    musicStartDefault();
    gameInit();

    // Fixed rate simulation: one gameFrame per tick, only the last of a
    // catch-up burst is rendered; more than 20 ticks behind drops the backlog.
    int last = g_lastTick;
    while (!g_quit) {
        int now = (int)getTicks();
        if (now > last) {
            ++last;
            if (g_keyDown[0x0a]) {   // '9': fast forward
                gameFrame(0);
                gameFrame(0);
                gameFrame(0);
            }
            if (now - last > 20)
                last = now;
            gameFrame(last == now);
            if (g_keyDown[0x09])     // '8': slow motion
                last += 3;
            if (g_keyPressed[0x08]) { // '7': pause
                g_paused ^= 1;
                g_keyPressed[0x08] = 0;
            }
        } else {
            Sleep(0);
        }
        pumpMessages();
    }
    replayStopRecording();
    shutdown();
}
