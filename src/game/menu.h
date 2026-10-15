// The 3D menu (signs hanging from ropes), the hidden part and the frame
// fade.
#pragma once

#include "../core/vecmath.h"

extern char g_menuBuilt;          // @ 0x4eac88 editor: level already shown once
extern int g_clickTimer;          // @ 0x4eac74 frames until the next thrown box
extern int g_menuFade;            // @ 0x4eac78

void buildMenu();                 // @ 0x406eba
Vec3 pickRay();                   // @ 0x407794 view ray through the mouse position
void hiddenPartUpdate();          // @ 0x407818
void menuUpdate(char drawTexts);  // @ 0x40795f
void resetView();                 // @ 0x407db4
void setFade(int level);          // @ 0x407dd8
void updateFade();                // @ 0x407e0c
