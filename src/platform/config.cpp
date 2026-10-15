// Startup settings dialog and registry storage.
#include "config.h"
#include "window.h"
#include "../audio/sound.h"
#include "../game/game.h"
#include "../game/level.h"
#include "../license/license.h"
#include "../render/d3d.h"
#include "../render/scene.h"
#include <commdlg.h>

Config g_config;

static Config g_configApplied;          // @ 0xd0f390 written only
static HWND g_configWindow;             // @ 0xd0f33c
static HWND g_keyEdit;                  // @ 0xd0f34c
static HWND g_lightsList;               // @ 0xd0f344
static DisplayMode *g_modes;            // @ 0xd0f368
static HWND g_soundList;                // @ 0xd0f36c
static HWND g_quitButton;               // @ 0xd0f374
static HWND g_playButton;               // @ 0xd0f378
static HWND g_infoText2;                // @ 0xd0f37c
static HWND g_infoText1;                // @ 0xd0f380
static HWND g_playModButton;            // @ 0xd0f384
static HWND g_modeList;                 // @ 0xd0f388
static HWND g_titleText;                // @ 0xd0f38c
static int g_modeCount;                 // @ 0xd0f3a8
static int g_configResult;              // @ 0xd0f3ac
static int g_configClassRegistered;     // @ 0xd0f3b0

// @ 0x453bc8
static char kLightOptions[4][64] = {"No Shadow", "2  Lights", "4  Lights", "12 Lights"};

static const char kRegistryKey[] = "Software\\Archee\\Sumotori";

// @ 0x415c2e
void configSetDefaults()
{
    g_config.refresh = 0;
    g_config.width = 640;
    g_config.height = 480;
    g_config.bits = 32;
    g_config.lights = 2;
    g_config.sound = 1;
}

// @ 0x415c68
void configApply(const Config *config)
{
    g_configApplied = *config;
    g_soundEnabled = config->sound != 0;
    int lightCounts[4] = {1, 2, 4, 12};
    g_lightCount = lightCounts[config->lights];
    g_shadowsEnabled = config->lights != 0;
    g_screenWidth = config->width;
    g_screenHeight = config->height;
    g_screenBits = config->bits;
    g_screenRefresh = config->refresh;
    g_windowed = config->width * config->height == 0;
}

// @ 0x415cf8
void configReadControls()
{
    g_windowed = 0;
    int mode = (int)SendMessageA(g_modeList, LB_GETCURSEL, 0, 0) - 1;
    if (mode == -1) {
        g_config.width = 0;
        g_config.height = 0;
        g_config.bits = 0;
        g_config.refresh = 0;
    } else {
        memcpy(&g_config, &g_modes[mode], sizeof(DisplayMode));
    }
    g_config.lights = (int)SendMessageA(g_lightsList, LB_GETCURSEL, 0, 0);
    g_config.sound = (int)SendMessageA(g_soundList, LB_GETCURSEL, 0, 0);
    configApply(&g_config);
}

// @ 0x415d81
void configShowThanks()
{
    g_infoText2 = CreateWindowExA(0, "edit", "Homepage: http://www.gravitysensation.com/sumotori/",
                                  WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 325, 500, 25, g_configWindow,
                                  nullptr, g_instance, nullptr);
    g_infoText1 = CreateWindowExA(0, "edit", "Thanks for purchasing Sumotori Dreams!   ENJOY!",
                                  WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 300, 500, 25, g_configWindow,
                                  nullptr, g_instance, nullptr);
}

// @ 0x415df1
// A valid key was typed: the license controls are replaced by the thanks text.
void configLicenseAccepted()
{
    if (!g_keyEdit)
        return;
    DestroyWindow(g_infoText2);
    g_infoText2 = nullptr;
    DestroyWindow(g_infoText1);
    g_infoText1 = nullptr;
    DestroyWindow(g_keyEdit);
    g_keyEdit = nullptr;
    configShowThanks();
}

// @ 0x415e35
void configSave()
{
    HKEY key;
    if (RegCreateKeyA(HKEY_CURRENT_USER, kRegistryKey, &key) == ERROR_SUCCESS) {
        RegSetValueExA(key, "configf", 0, REG_BINARY, (const BYTE *)&g_config, sizeof(Config));
        RegCloseKey(key);
    }
}

// @ 0x415e74
void configLoad()
{
    configSetDefaults();
    HKEY key;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, kRegistryKey, 0, KEY_READ, &key) == ERROR_SUCCESS) {
        DWORD size = sizeof(Config);
        RegQueryValueExA(key, "configf", nullptr, nullptr, (BYTE *)&g_config, &size);
        RegCloseKey(key);
    }
    configApply(&g_config);
}

// @ 0x415ed4
LRESULT CALLBACK configWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    char key[200];

    switch (msg) {
    case WM_DESTROY:
        g_configWindow = nullptr;
        g_configResult = 2;
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_CLOSE:
        g_configResult = 2;
        return 0;

    case WM_COMMAND: {
        unsigned notify = (unsigned)wParam >> 16;
        if (notify != 0) {
            if (notify == EN_CHANGE) {
                GetWindowTextA(g_keyEdit, key, 199);
                if (licenseEnterKey(key, true) == 0 && g_keyEdit)
                    configLicenseAccepted();
            }
            break;
        }

        // BN_CLICKED
        if ((HWND)lParam == g_playModButton) {
            char path[260];
            GetCurrentDirectoryA(252, path);
            strcat(path, "\\*.smo");
            OPENFILENAMEA ofn;
            memset(&ofn, 0, sizeof(ofn));
            ofn.lpstrFile = path;
            ofn.lStructSize = sizeof(OPENFILENAMEA);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFilter = "Sumotori Mods (*.smo)\0*.smo\0All Files (*.*)\0*.*\0";
            ofn.nMaxFile = 260;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
            ofn.lpstrDefExt = "smo";
            if (GetOpenFileNameA(&ofn))
                loadModFile(ofn.lpstrFile);
            // a mod was loaded: continue as if PLAY GAME was pressed
            if (g_currentLevel == -1)
                lParam = (LPARAM)g_playButton;
        }
        if ((HWND)lParam == g_playButton) {
            if (!licenseIsValid()) {
                GetWindowTextA(g_keyEdit, key, 199);
                if (key[0] && key[1] && key[2] && licenseEnterKey(key, true) != 0)
                    MessageBoxA(g_configWindow, "Invalid license key", "Error", MB_OK);
            }
            configReadControls();
            configSave();
            g_configResult = 1;
        }
        if ((HWND)lParam == g_quitButton) {
            configReadControls();
            g_configResult = 2;
        }
        break;
    }
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

// @ 0x4160fe
void configCreateControls()
{
    char text[256];

    g_titleText = CreateWindowExA(0, "edit", "System Settings", WS_CHILD | WS_VISIBLE | ES_READONLY,
                                  10, 0, 380, 20, g_configWindow, nullptr, g_instance, nullptr);
    const DWORD listStyle = WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY;
    g_modeList = CreateWindowExA(0, "listbox", "drivers", listStyle, 400, 10, 180, 280, g_configWindow,
                                 nullptr, g_instance, nullptr);
    g_lightsList = CreateWindowExA(0, "listbox", "drivers", listStyle, 10, 30, 380, 120, g_configWindow,
                                   nullptr, g_instance, nullptr);
    g_soundList = CreateWindowExA(0, "listbox", "sound", listStyle, 10, 190, 180, 60, g_configWindow,
                                  nullptr, g_instance, nullptr);
    SendMessageA(g_soundList, LB_ADDSTRING, 0, (LPARAM) "SOUND OFF");
    SendMessageA(g_soundList, LB_ADDSTRING, 0, (LPARAM) "SOUND ON");

    enumerateDisplayModes(nullptr, &g_modes, &g_modeCount);
    SendMessageA(g_modeList, LB_ADDSTRING, 0, (LPARAM) "WINDOWED MODE ***");
    int selected = 0;
    DisplayMode *mode = g_modes;
    for (int i = 0; i < g_modeCount; ++i, ++mode) {
        sprintf(text, "%dx%d %dbpp", mode->width, mode->height, mode->bitsPerPixel, mode->refreshRate);
        SendMessageA(g_modeList, LB_ADDSTRING, 0, (LPARAM)text);
        if (mode->width == g_screenWidth && mode->height == g_screenHeight &&
            mode->bitsPerPixel == g_screenBits && mode->refreshRate == g_screenRefresh)
            selected = i + 1;
    }
    SendMessageA(g_modeList, LB_SETCURSEL, selected, selected);

    for (char(*option)[64] = kLightOptions; option < kLightOptions + 4; ++option)
        SendMessageA(g_lightsList, LB_ADDSTRING, 0, (LPARAM)*option);
    SendMessageA(g_lightsList, LB_SETCURSEL, g_config.lights, g_config.lights);
    SendMessageA(g_soundList, LB_SETCURSEL, g_config.sound, g_config.sound);

    g_playModButton = CreateWindowExA(0, "button", "PLAY MOD", WS_CHILD | WS_VISIBLE, 460, 370, 120, 20,
                                      g_configWindow, nullptr, g_instance, nullptr);
    g_playButton = CreateWindowExA(0, "button", "PLAY GAME", WS_CHILD | WS_VISIBLE, 300, 410, 180, 20,
                                   g_configWindow, nullptr, g_instance, nullptr);
    g_quitButton = CreateWindowExA(0, "button", "QUIT", WS_CHILD | WS_VISIBLE, 500, 410, 80, 20,
                                   g_configWindow, nullptr, g_instance, nullptr);

    if (!licenseIsValid()) {
        const DWORD textStyle = WS_CHILD | WS_VISIBLE | ES_READONLY;
        g_infoText1 = CreateWindowExA(0, "edit", "Visit http://www.gravitysensation.com/sumotori/ to get a license.",
                                      textStyle, 10, 300, 500, 25, g_configWindow, nullptr, g_instance, nullptr);
        g_infoText2 = CreateWindowExA(0, "edit", "Type the license key below:", textStyle, 10, 325, 500, 25,
                                      g_configWindow, nullptr, g_instance, nullptr);
        g_keyEdit = CreateWindowExA(0, "edit", "", WS_CHILD | WS_VISIBLE | ES_UPPERCASE, 10, 360, 400, 25,
                                    g_configWindow, nullptr, g_instance, nullptr);
    } else {
        configShowThanks();
    }
}

// @ 0x416461
int configDialog(const char *title)
{
    if (!g_configClassRegistered) {
        g_configClassRegistered = 1;
        WNDCLASSA wc;
        wc.style = CS_DBLCLKS;
        wc.lpfnWndProc = configWindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = g_instance;
        wc.hIcon = nullptr;
        wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
        wc.hbrBackground = CreateSolidBrush(0xd0c0c0);
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = "archeecfg";
        if (!RegisterClassA(&wc))
            return 0;
    }

    const DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;   // 0xca0000
    RECT rect = {0, 0, 600, 460};
    AdjustWindowRect(&rect, style, FALSE);
    g_configWindow = CreateWindowExA(WS_EX_APPWINDOW, "archeecfg", title, style, CW_USEDEFAULT, CW_USEDEFAULT,
                                     rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr,
                                     g_instance, nullptr);
    ShowWindow(g_configWindow, SW_SHOWNORMAL);
    SetCursor(nullptr);
    configCreateControls();

    g_configResult = 0;
    MSG msg;
    for (;;) {
        GetMessageA(&msg, nullptr, 0, 0);
        if (g_configResult)
            break;
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    int result = g_configResult;
    DestroyWindow(g_configWindow);
    return result;
}
