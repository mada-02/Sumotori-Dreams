// Debug log ("debug.!").
#pragma once

// @ 0x416945
// Appends "<text> <value>" to debug.!; the file is truncated on the first
// call of the session.
void debugPrint(const char *text, int value);
