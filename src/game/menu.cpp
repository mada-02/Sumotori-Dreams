// The 3D menu, the hidden part and the frame fade.
#include "menu.h"
#include "camera.h"
#include "game.h"
#include "level.h"
#include "sumo.h"
#include "../core/common.h"
#include "../physics/world.h"
#include "../platform/input.h"
#include "../platform/window.h"
#include "../render/d3d.h"
#include "../render/scene.h"

char g_menuBuilt;
int g_clickTimer;
int g_menuFade;

static int g_unk4536d8 = 1;       // @ 0x4536d8 written only
static int g_unk4536dc;           // @ 0x4536dc written only
static int g_unk511df0;           // @ 0x511df0 written only

// @ 0x453600
static const char kWarningText[] =
    "WARNING: The characters in the game were performed by\ntrained professionals!!! Do not try this at home!!!\n"
    " \nRules: When you hit the ground, you loose\nwinner is the one, who stays on feet for the longest\n";

static void linkRope(Body *a, const Vec3 &anchorA, const Vec3 &axisA, const Vec3 &refA,
                     const Vec3 &anchorB, const Vec3 &axisB, const Vec3 &refB, float limitCos)
{
    Joint *j = g_jointEnd;
    j->a = a;
    j->anchorA = anchorA;
    j->axisA = axisA;
    j->refA = refA;
    j->b = g_bodyEnd - 1;
    j->anchorB = anchorB;
    j->axisB = axisB;
    j->refB = refB;
    j->limitCos = limitCos;
    j->limitTwist = 1.21f;
    j->hinge = 0.0f;
    ++g_jointEnd;
}

// @ 0x406eba
// Builds the menu page: a gallows with signs hanging from two ropes each.
// Sign tags are column * 16 + row + 1.
void buildMenu()
{
    if (g_editorMode) {
        if (g_menuBuilt)
            g_quit = 1;
        g_menuBuilt = 1;
        g_attractMode = 0;
        startLevel(nullptr);
        return;
    }

    g_frame = 0;
    showCursor(1);
    g_mouseX = -1;
    g_gameState = GAME_MENU;
    buildDojo(0);
    g_shadowLength = 80.0f;
    g_menuSelection = 0;

    float ropeZ[4] = {-7.0f, 7.0f, 7.0f, 0.0f};          // [EBP]
    int segments[4] = {3, 3, 4, 0};                       // [EBP-0x54]
    int rows[4] = {4, 4, 3, 0};                           // [EBP+0x10]

    for (int i = -4; i < 5; ++i) {
        Body *post = createBox(V3(1.0f, -25.0f, 1.0f), V3(-80.0f, 15.0f, i * 7.0f), 1, 0.125f);
        post->makeStatic();
    }
    Body *beam = createBox(V3(4.0f, -1.5f, 30.0f), V3(-80.0f, 40.0f, 0.0f), 1, 0.125f);
    beam->makeStatic();

    Vec3 offset = V3(0.0f, 0.0f, 0.0f);                   // [EBP+0x4c]
    int material = g_menuPage + 4;                        // [EBP+0x3c]
    int rowShift = 0;                                     // [EBP+0x40]
    int columns = 1;                                      // [EBP+0x6c]
    if (g_menuPage == 0) {
        columns = 3;
        offset.z = 20.0f;
    }
    if (g_menuPage == 3) {
        columns = 2;
        rows[0] = 0;
        rowShift = 2;
        material = 4;
    }
    if (g_menuPage == 1) {
        offset.z = 10.0f;
        columns = 2;
        rows[1] = 2;
        rowShift = 0;
        material = 7;
    }

    for (int col = 0; col < columns; ++col) {
        Body *hang[2] = {beam, beam};                     // [EBP+0x20]
        Vec3 attach[2];                                   // [EBP-0xcc]
        attach[0] = V3(-5.0f, 0.0f, -7.0f) + offset;
        attach[1] = V3(-5.0f, 0.0f, 7.0f) + offset;
        float y = 40.0f;                                  // [EBP+0x64]
        for (int row = 0; row < rows[col]; ++row) {
            for (int seg = 0; seg < segments[col]; ++seg) {
                float linkY = y + 0.9f;
                float turn = (float)seg * 0.0f;
                for (int k = 0; k < 2; ++k) {
                    Vec3 p = V3(-85.0f, linkY, ropeZ[k]) + offset;
                    Body *link = createBox(V3(0.5f, -0.9f, 0.5f), p, 0, 0.125f);
                    link->rot.rotateLocalY(turn);
                    link->inertia = link->inertia * 3.0f;
                    link->invInertia = link->invInertia * 0.333333343f;
                    Vec3 axisA = V3(0.0f, 1.0f, 0.0f);
                    if (seg == 0 && row == 0)
                        axisA = V3(0.0f, -1.0f, 0.0f);
                    linkRope(hang[k], attach[k], axisA, V3(1.0f, 0.0f, 0.0f),
                             V3(0.0f, -0.9f, 0.0f), V3(0.0f, 1.0f, 0.0f), V3(1.0f, 0.0f, 0.0f), 0.81f);
                    attach[k] = V3(0.0f, 0.9f, 0.0f);
                    hang[k] = link;
                }
                y = y + 1.8f;
            }

            float half = 1.8f;                            // [EBP+0x44]
            if (col == 2) {
                half = 1.9f;
                if (row == 1 && g_aiStands)
                    rowShift = 1;
                if (row == 2 && !g_aiStands)
                    rowShift = 1;
            }
            Vec3 p = V3(-85.0f, half + y, 0.0f) + offset;
            Body *sign = createBox(V3(0.6f, -half, 9.0f), p, material + col, -0.0555555560f);
            sign->tag = col * 16 + 1 + row;
            int textRow = row + rowShift;
            sign->uvOffset = -V3(0.6f, -half - (float)textRow * 2.953125f, 9.0f);
            sign->mass = sign->mass * 0.03f;
            sign->invMass = sign->invMass * 33.3333359f;
            sign->density = sign->density * 0.03f;
            sign->inertia = sign->inertia * 0.03f;
            sign->sound = 2;
            sign->invInertia = sign->invInertia * 33.3333359f;
            sign->soundVolume = 3.0f;
            float r1 = (float)(g_random.next() * 0.26);
            float r2 = (float)((g_random.next() + 1.0f) * -0.04);
            sign->vel = V3(r2, r1, 0.0f);
            y = half + half + y;
            sign->breakThreshold = 15.0f;
            float top = -half;
            for (int k = 0; k < 2; ++k) {
                linkRope(hang[k], attach[k], V3(0.0f, 1.0f, 0.0f), V3(1.0f, 0.0f, 0.0f),
                         V3(0.0f, top, ropeZ[k]), V3(0.0f, 1.0f, 0.0f), V3(1.0f, 0.0f, 0.0f), 0.80999994f);
                attach[k] = V3(0.0f, half, ropeZ[k]);
                hang[k] = sign;
            }
        }
        offset.z = offset.z - 20.0f;
    }
    rebuildJointLinks();
}

// @ 0x407794
Vec3 pickRay()
{
    Vec3 v = V3((g_mouseX + g_pickOffsetX) * g_pickScaleX, -((g_mouseY + g_pickOffsetY) * g_pickScaleY), 1.0f);
    v = v * g_viewRot;
    v.normalize();
    return v;
}

// @ 0x407818
// The hidden part: one computer wrestler to throw boxes at.
void hiddenPartUpdate()
{
    --g_clickTimer;
    if (g_mouseX != -1) {
        if (g_clickTimer <= 0) {
            g_clickTimer = 60;
            Vec3 dir = pickRay();
            float k = 50.0f;
            Vec3 target = g_viewPos + dir * k;
            Vec3 from = g_viewPos + V3(5.0f, 0.0f, 4.0f) * g_viewRot;
            throwBox(from, target, 30.0f, 2);
        }
        g_mouseX = -1;
    }
    drawText(-0.2f, 0.55f, "Hidden Part", 0xb08f8fff);
    if (g_frame < 1000)
        drawText(0.2f, 0.6f, "Controls:\nHome/PageUp = Move Camera\nMouse Click = Punish!!!\nEsc      = leave",
                 0xb0ffffff);
    if ((char *)g_bodyEnd > (char *)g_bodies + 0x189c0)
        buildMenu();
}

// @ 0x40795f
// Menu frame: reacts to the sign that was hit (g_menuSelection is set when a
// sign breaks) after the fade out.
void menuUpdate(char drawTexts)
{
    if ((char *)g_bodyEnd > (char *)g_bodies + 0xc4e0)
        buildMenu();

    int sel = g_menuSelection;
    if (sel == 0) {
        g_menuFade = 0xff;
    } else {
        g_menuFade -= 2;
        if (g_menuFade <= 0) {
            if (g_menuPage == 0) {
                bool start = true;
                switch (sel) {
                case 1:  g_humanCount = 2; g_playerCount = 2; break;
                case 2:  g_humanCount = 2; g_playerCount = 3; break;
                case 3:  g_humanCount = 2; g_playerCount = 4; break;
                case 4:  g_humanCount = 0; g_playerCount = 4; break;
                case 6:  g_humanCount = 0; g_playerCount = 1; break;
                case 17: g_playerCount = 2; g_humanCount = 1; break;
                case 18: g_playerCount = 3; g_humanCount = 1; break;
                case 19: g_playerCount = 4; g_humanCount = 1; break;
                case 20: g_humanCount = 0; g_playerCount = 2; break;
                case 33: g_menuPage = 1; buildMenu(); start = false; break;
                case 34: g_aiStands ^= 1; buildMenu(); start = false; break;
                case 35: g_quit = 1; start = false; break;
                default: start = false; break;
                }
                if (start)
                    startMatch();
            } else if (g_menuPage == 1) {
                g_modTextPtr = nullptr;
                g_menuPage = 0;
                g_currentLevel = sel % 16 - 1 + sel / 16 * 4;
                buildMenu();
            }
        }
        g_fadeColor = fp::ftol(fp::sqrt((double)(g_menuFade << 8))) * 0x10101;
    }

    --g_clickTimer;
    if (g_mouseX != -1) {
        if (g_clickTimer <= 0) {
            g_clickTimer = 60;
            Vec3 dir = pickRay();
            float k = (g_viewPos.x + 84.0f) / dir.x;
            Vec3 target = g_viewPos - dir * k;
            throwBox(V3(-120.0f, 10.0f, 0.0f), target, 30.0f, 2);
        }
        g_mouseX = -1;
    }
    if (g_escapePressed)
        g_quit = 1;

    if (drawTexts) {
        if (g_menuPage == 3) {
            drawText(-0.85f, 0.4f, kWarningText, 0xc0ffffff);
            unsigned c = g_fadeColor;
            g_fadeColor = (((int)(c & 0xff00) * 3 / 4) & 0xff00) + (((int)c / 2) & 0x7f007f);
        }
        drawText(-0.2f, 0.56f, "Sumotori Dreams Full", 0xc08080ff);
        drawText(0.27f, -0.5f, "\"Tested on party animals\"", 0xc0ffffff);
        drawText(-0.85f, -0.5f, "www.gravitysensation.com/sumotori", 0xc0ffffff);
    }
}

// @ 0x407db4
void resetView()
{
    g_frame = 0;
    g_unk4536d8 = -1;
    g_unk511df0 = 0;
    g_unk4536dc = 1;
    gameCameraReset();
}

// @ 0x407dd8
void setFade(int level)
{
    if (level > 255)
        level = 255;
    if (g_editorMode)
        level = 255;
    g_fadeColor = ((level * level) >> 8) * 0x101 + (level << 16);
}

// @ 0x407e0c
void updateFade()
{
    setFade(g_frame << 3);
}
