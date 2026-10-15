#pragma once

#include "../core/common.h"

extern char g_licenseKey[0x800];

// Validates a user supplied key; returns 0 = ok, 1 = empty, 2 = invalid.
int licenseEnterKey(const char *input, bool store);
// Checks the stored key (memory or registry).
bool licenseIsValid();
