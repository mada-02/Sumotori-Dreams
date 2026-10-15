// Arenas: the built-in level scripts, MOD files and the level editor window.
#include "level.h"
#include "game.h"
#include "camera.h"
#include "menu.h"
#include "replay.h"
#include "sumo.h"
#include "../audio/music.h"
#include "../physics/world.h"
#include "../platform/input.h"
#include "../platform/window.h"
#include "../render/scene.h"
#include "../script/script.h"

#include "level_scripts.inc"

char g_modText[0x10000];
char *g_modTextPtr;
HWND g_editorEdit;
Body *g_currentBox;
Vec3 g_spawnPos[9];
char g_editorText[0x80000];
int g_spawnCount;
float g_spawnAngle[9];
HWND g_editorWindow;

// @ 0x453408: index 0 is the default dojo (built in code)
static const char *const kLevelScripts[6] = {
    nullptr, kLevelKitchen, kLevelRoof, kLevelSeesaw, kLevelStage, kLevelDownstairs,
};

// @ 0x403fa8
const char *levelScript(int level)
{
    if (g_modTextPtr)
        return g_modTextPtr;
    return kLevelScripts[level];
}

// @ 0x403fbd
void loadModFile(const char *fileName)
{
    FILE *f = fopen(fileName, "rb");
    if (!f)
        return;
    size_t n = fread(g_modText, 1, 0xffff, f);
    g_modText[n] = 0;
    fclose(f);
    g_currentLevel = -1;
    g_modTextPtr = g_modText;
}

// @ 0x4083d2
static void freeAllBodies()
{
    for (Body *b = g_bodies; b < g_bodyEnd; ++b)
        b->freeGeometry();
    g_bodyEnd = g_bodies;
}

// @ 0x4069a7
// Clears the world and runs a level script.  In the editor the text comes
// from the edit control (and is saved to edited.txt).
void loadLevel(const char *text)
{
    g_spawnCount = 0;
    g_gameState = GAME_WAITING;
    g_matchStartFrame = 0;
    g_frame = 0;
    g_framesSinceStart = 0;
    g_ranking[0] = -1;
    g_ranking[1] = -1;
    g_ranking[2] = -1;
    g_ranking[3] = -1;
    freeAllBodies();
    memset(g_joints, 0, sizeof(g_joints));
    g_jointEnd = g_joints;
    g_sumoEnd = g_sumos;

    g_currentBox = createBox(V3(100.0f, -10.0f, 100.0f), V3(0.0f, -20.0f, 0.0f), 1, 0.0625f);
    g_currentBox->makeStatic();
    g_currentBox = nullptr;

    if (g_editorMode) {
        GetWindowTextA(g_editorEdit, g_editorText, 0x80000);
        FILE *f = fopen("edited.txt", "wb");
        fwrite(g_editorText, 1, strlen(g_editorText), f);
        fclose(f);
        text = g_editorText;
    }

    g_script.clearVariables();
    g_script.addMathConstants();
    g_script.locals = nullptr;
    g_script.compile(text);
    if (!g_editorMode) {
        if (g_script.failed)
            MessageBoxA(nullptr, g_script.error, "Error in MOD file", MB_ICONWARNING);
    } else if (!g_script.failed) {
        SetWindowTextA(g_editorWindow, "Sumotori Dreams level editor");
        g_script.link();
        Vec3 result;
        g_script.evaluate(&result);
    } else {
        SetWindowTextA(g_editorWindow, g_script.error);
    }

    if (g_currentBox) {
        Mat3 rot = g_currentBox->rot;
        float threshold = g_currentBox->breakThreshold;
        char isStatic = g_currentBox->isStatic;
        g_currentBox->rebuildAfterCut(1);
        g_currentBox->computeMassProperties();
        g_currentBox->recenter();
        g_currentBox->init();
        if (isStatic)
            g_currentBox->makeStatic();
        g_currentBox->rot = rot;
        g_currentBox->breakThreshold = threshold;
    }

    for (Sumo *s = g_sumos; s < g_sumoEnd; ++s) {
        Vec3 zero = V3(0.0f, 0.0f, 0.0f);
        Vec3 zero2 = V3(0.0f, 0.0f, 0.0f);
        s->opponent = s->findOpponent(zero, zero2);
    }

    if (g_script.failed) {
        g_jointEnd = g_joints;
        g_sumoEnd = g_sumos;
        g_bodyEnd = g_bodies;
    }
    rebuildJointLinks();
}

// @ 0x406c59
void startLevel(const char *text)
{
    replayRecordFrameMarker();
    g_shadowLength = 150.0f;
    scriptInitLevelBuiltins();
    showCursor(1);
    musicPlay(6);
    freeCameraResetAt(V3(60.0f, 35.0f, -97.0f), 0.0f);
    resetView();
    loadLevel(text);
}

// @ 0x406cd2
LRESULT CALLBACK editorWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_SIZE) {
        MoveWindow(g_editorEdit, 0, 0, LOWORD(lParam) - 30, HIWORD(lParam), TRUE);
    } else {
        if (msg == WM_CLOSE) {
            g_quit = 1;
            return 0;
        }
        if (msg == WM_COMMAND && HIWORD(wParam) == EN_CHANGE)
            loadLevel(nullptr);
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

// @ 0x406d45
void createEditorWindow(HINSTANCE instance)
{
    FILE *f = fopen("edited.txt", "rb");
    if (f) {
        size_t n = fread(g_editorText, 1, 0x7ffff, f);
        g_editorText[n] = 0;
        fclose(f);
    }

    WNDCLASSEXA wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = editorWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(0x504030);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = "gameeditor";
    wc.hIconSm = nullptr;
    RegisterClassExA(&wc);

    g_editorWindow = CreateWindowExA(0, "gameeditor", "Sumotori Editor", WS_OVERLAPPEDWINDOW, 200, 700, 800, 300,
                                     GetDesktopWindow(), nullptr, instance, nullptr);
    g_editorEdit = CreateWindowExA(0, "edit", g_editorText,
                                   WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
                                   20, 20, 400, 150, g_editorWindow, nullptr, instance, nullptr);
    HFONT font = CreateFontA(13, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY,
                             VARIABLE_PITCH, "Lucida Console");
    SendMessageA(g_editorEdit, WM_SETFONT, (WPARAM)font, TRUE);
    ShowWindow(g_editorWindow, SW_SHOWNORMAL);
}
