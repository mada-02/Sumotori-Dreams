#include "debug.h"
#include "../core/common.h"

static char g_debugStarted;   // @ 0xd0fa00
static FILE *g_debugFile;     // @ 0xd0f3dc

// @ 0x416945
void debugPrint(const char *text, int value)
{
    if (!g_debugStarted) {
        g_debugStarted = 1;
        g_debugFile = fopen("debug.!", "w");
        fclose(g_debugFile);
    }
    g_debugFile = fopen("debug.!", "a");
    fprintf(g_debugFile, "%s %d\n", text, value);
    fclose(g_debugFile);
}
