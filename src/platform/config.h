// Startup settings dialog ("System Settings") and its registry storage.
#pragma once

#include "../core/common.h"

// Stored as REG_BINARY "configf" under HKCU\Software\Archee\Sumotori.
struct Config {
    int width;        // 0 x 0 = windowed
    int height;
    int bits;
    int refresh;
    int lights;       // 0 = no shadow, 1 = 2 lights, 2 = 4 lights, 3 = 12 lights
    int sound;        // 0 = off, 1 = on
};
static_assert(sizeof(Config) == 0x18, "Config layout");

extern Config g_config;                 // @ 0xd0f350

void configSetDefaults();               // @ 0x415c2e
void configApply(const Config *config); // @ 0x415c68
void configReadControls();              // @ 0x415cf8
void configShowThanks();                // @ 0x415d81
void configLicenseAccepted();           // @ 0x415df1
void configSave();                      // @ 0x415e35
void configLoad();                      // @ 0x415e74
LRESULT CALLBACK configWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // @ 0x415ed4
void configCreateControls();            // @ 0x4160fe
// Runs the dialog modally; returns 1 = play, 2 = quit, 0 = class
// registration failed.
int configDialog(const char *title);    // @ 0x416461
