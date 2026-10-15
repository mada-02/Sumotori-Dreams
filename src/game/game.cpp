// Global game state and the per-frame update / HUD.
#include "game.h"
#include "camera.h"
#include "menu.h"
#include "replay.h"
#include "sumo.h"
#include "../audio/music.h"
#include "../core/common.h"
#include "../physics/world.h"
#include "../platform/input.h"
#include "../platform/window.h"
#include "../render/d3d.h"
#include "../render/scene.h"

int g_editorMode = SUMO_EDITOR_DEFAULT;

int g_gameState;
int g_attractMode;
int g_frame;
int g_matchStartFrame;
int g_framesSinceStart;
int g_scoreBlue;
int g_scoreGrey;
int g_standingCount;
int g_ranking[4];
int g_resetScores;
int g_demoState;
int g_paused;
int g_currentLevel;
int g_playerCount = 3;
int g_humanCount;
int g_menuPage;
int g_aiStands;
int g_menuSelection;

float g_gravity = -0.0098f;
float g_ringRadius = 27.0f;
float g_waterLevel = -2000.0f;
int g_ticksPerSecond = 120;
int g_timeDivider = 1;

// @ 0x40e1d2
// One frame: camera, physics step, menu / hidden part logic and, when
// rendering, the HUD and the scene.
void gameFrame(char render)
{
    setFpuControl();
    ++g_frame;
    int screenshot = 0;
    g_lineCursor = &g_lines[0][0];
    if (g_cameraMode >= 0) {
        if (g_cameraMode <= 2)
            gameCameraUpdate();
        else if (g_cameraMode == 3)
            freeCameraUpdate(4);
    }
    textBegin();
    if (!g_paused)
        physicsStep();

    if (g_gameState == GAME_MENU) {
        menuUpdate(render);
    } else {
        if (g_gameState == GAME_HIDDEN)
            hiddenPartUpdate();
        doNothing();
        if (g_escapePressed) {
            g_escapePressed = 0;
            musicPlay(3);
            buildMenu();
        }
    }
    if (!render)
        return;

    if (g_keyPressed[7]) {   // '6': high quality screenshot
        g_keyPressed[7] = 0;
        screenshot = 1;
        g_lightCount = 12;
        g_shadowsEnabled = 1;
    }

    if (g_cameraMode == 0) {
        static const char kNames[8][25] = {
            "Blue guy", "Grey guy", "Brown guy", "Green guy", "Blue guy (player)", "Grey guy (player2)",
        };
        unsigned colors[4] = {0xe08080ff, 0xc0ffffff, 0xe0c08000, 0xc020e020};
        float y = 0.5f;
        if (g_gameState != GAME_HIDDEN) {
            for (int i = 0; i < (int)(g_sumoEnd - g_sumos); ++i) {
                int s = g_ranking[i];
                if (s == -1)
                    continue;
                char place[2] = {(char)('1' + i), 0};
                drawText(-0.2f, y, place, colors[s]);
                const char *name = g_sumos[s].controller == 1 ? kNames[4 + s] : kNames[s];
                drawText(-0.15f, y, name, colors[s]);
                y = y - 0.05f;
            }
        }
        if (g_gameState == GAME_OVER) {
            int gameOver = 0;
            if ((g_scoreBlue >= 5 || g_scoreGrey >= 5) &&
                (g_scoreBlue >= g_scoreGrey + 2 || g_scoreBlue <= g_scoreGrey - 2)) {
                gameOver = 1;
                static const char kWinner[2][16] = {" Game \n  ->  ", " Game \n  <-  "};
                int greyWins = g_scoreGrey > g_scoreBlue ? 1 : 0;
                drawText(-0.1f, 0.42f, kWinner[greyWins], colors[greyWins]);
                drawText(-0.1f, 0.1f, "           \n Game Over \n           ", 0xc0ffff00);
            }
            drawText(-0.8f, 0.55f, "Space to restart game", 0xc0c0c0c0);
            if (g_keyPressed[0x39]) {
                if (gameOver)
                    buildMenu();
                else
                    startMatch();
            }
        }
        if (g_gameState == GAME_WAITING) {
            drawText(0.2f, 0.6f,
                     "Controls:\n DOWN      - start match\n UP        - walk forward\n BACKSPACE - Push\n ENTER     - Push 1 hand",
                     0xb0ffffff);
            if (g_attractMode != 0 || g_humanCount >= 2)
                drawText(-0.8f, 0.6f,
                         "Controls:\n S         - start match\n W         - walk forward\n SHIFT     - Push\n CTRL      - Push 1 hand",
                         0xb0ffffff);
        }
    } else {
        if (g_keyPressed[0x39])
            startMatch();
        if ((g_cameraMode == 1 || g_cameraMode == 3 || g_cameraMode == 20) && g_replayFrames != 0) {
            char text[1024];
            sprintf(text, "%2d.%2d", g_replayFrames / 100, g_replayFrames % 100);
            drawText(-0.8f, 0.6f, text, 0xc0c0c0c0);
        }
    }
    g_keyPressed[0x39] = 0;

    if (g_demoState == 2) {
        drawText(-0.45f, 0.2f,
                 "              demo time out\n      please purchase a licence at\nhttp://www.gravitysensation.com/sumotori/\n"
                 " \n \n \nCopy the licence-key from the e-mail into the\nbox in the settings dialog at startup.\n"
                 "press ESC to quit\n",
                 0xc0ffffff);
        g_fadeColor = 0x505050;
        g_paused = 1;
    }
    renderFrame();
    setFpuControl();
    if (screenshot)
        saveScreenshotAs("sumotori", 0);
}
