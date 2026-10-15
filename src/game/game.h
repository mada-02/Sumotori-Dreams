// Global game state shared between modules.
#pragma once

#include "../core/vecmath.h"

enum GameState {
    GAME_WAITING = 0,   // wrestlers placed, waiting for the match to start
    GAME_RUNNING = 1,
    GAME_OVER = 2,
    GAME_MENU = 10,     // 3D menu built from boxes
    GAME_HIDDEN = 11,   // the "Hidden Part" (single computer opponent arena)
};

extern int g_gameState;          // @ 0xc06b50
extern int g_attractMode;        // @ 0xc06b38
extern int g_frame;              // @ 0xc06978 frames since the match was (re)started
extern int g_matchStartFrame;    // @ 0xc06b58
extern int g_framesSinceStart;   // @ 0xc06b5c
extern int g_scoreBlue;          // @ 0xc06b28
extern int g_scoreGrey;          // @ 0xc06b2c
extern int g_standingCount;      // @ 0xc06b3c
extern int g_ranking[4];         // @ 0xc06b40 sumo index per final rank, -1 = none
extern int g_resetScores;        // @ 0xc06980
extern int g_demoState;          // @ 0xc06984 2 = demo time out
extern int g_paused;             // @ 0xd0fa10
extern int g_currentLevel;       // @ 0x4eac70 0 = default dojo, -1 = loaded mod
extern int g_playerCount;        // @ 0x4535f8 wrestlers in the arena
extern int g_humanCount;         // @ 0x4eac80
extern int g_menuPage;           // @ 0x4eac7c
extern int g_aiStands;           // @ 0x4eac84
extern int g_menuSelection;      // @ 0x562c10 tag of the last broken menu box

extern float g_gravity;          // @ 0x4536e0
extern float g_ringRadius;       // @ 0x45385c dohyo radius (27)
extern float g_waterLevel;       // @ 0x453cd4 (-2000 = no water)
extern int g_ticksPerSecond;     // @ 0x453cd8 simulation rate (120 Hz)
extern int g_timeDivider;        // @ 0x453cdc

void gameFrame(char render);     // @ 0x40e1d2
