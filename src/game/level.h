// Arenas: the built-in level scripts, MOD files and the level editor window.
#pragma once

#include "../core/common.h"
#include "../core/vecmath.h"

struct Body;

extern char g_modText[0x10000];        // @ 0x457340 contents of a loaded MOD file
extern char *g_modTextPtr;             // @ 0x467340 non-null once a MOD file is loaded
extern HWND g_editorEdit;              // @ 0x467b48 edit control of the editor window
extern Body *g_currentBox;             // @ 0x467b4c box being built by addbox()
extern Vec3 g_spawnPos[9];             // @ 0x467b50 man() start points (game build)
extern char g_editorText[0x80000];     // @ 0x467bb0
extern int g_spawnCount;               // @ 0x4e7bb0
extern float g_spawnAngle[9];          // @ 0x4e7bb4
extern HWND g_editorWindow;            // @ 0x4e7bd4

const char *levelScript(int level);                     // @ 0x403fa8
void loadModFile(const char *fileName);                 // @ 0x403fbd
void loadLevel(const char *text);                       // @ 0x4069a7
void startLevel(const char *text);                      // @ 0x406c59
LRESULT CALLBACK editorWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // @ 0x406cd2
void createEditorWindow(HINSTANCE instance);            // @ 0x406d45
