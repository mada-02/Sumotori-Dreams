#pragma once

// Keyboard state indexed by scan code, maintained by the main window procedure.
extern char g_keyDown[256];      // @ 0xd0f3e0 held keys
extern char g_keyPressed[256];   // @ 0xd0f4f8 latched key presses (cleared by consumers)
extern int g_mouseX;             // @ 0x453ce0 -1 = no pending click
extern int g_mouseY;             // @ 0xd0fa04
extern int g_escapePressed;      // @ 0xd0fa08
extern int g_quit;               // @ 0xd0f9fc
