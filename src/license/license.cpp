// Licence key verification.
//
// A key is a base-36 number x.  The program computes y = x^97 mod N and accepts
// the key when a keyed hash of y reproduces y.  The decoded value y (again in
// base 36) is what gets written to HKCU\Software\Archee\Sumotori\settings and
// re-validated (without the exponentiation) on later runs.
#include "license.h"
#include "bigint.h"

static const char kBase36Digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // @ 0x42c27c
static const char kRegistryPath[] = "Software\\Archee\\Sumotori";             // @ 0x42c2b0

char g_licenseKey[0x800]; // @ 0x467348

// @ 0x404008
static BigInt licenseHash(BigInt value, int key, BigInt modulus)
{
    BigInt keyNumber(key);
    BigInt low = value % keyNumber;
    int seed = 0x666;
    int bits = keyNumber.log(BigInt(2)) + 1;
    int chunks = modulus.log(BigInt(0x10000)) + 1;
    BigInt acc(0);
    for (int i = -1; i < bits; ++i) {
        bool use = (i == -1) ? true : low.testBit(i);
        BigInt factor(1);
        for (int j = chunks; j > 0; --j) {
            seed = seed * 0x343fd + 0x269ec3;
            int r = (seed >> 16) & 0x7fff;
            if (use) {
                acc += factor * BigInt(r);
                factor = factor * BigInt(0x10000);
            }
        }
    }
    acc = acc % modulus;
    acc = (acc / keyNumber) * keyNumber + low;
    return BigInt(acc);
}

// @ 0x40431c
static bool licenseCheck(const char *text, int length, int alreadyDecoded, char *decodedOut)
{
    BigInt modulus(0);
    modulus.appendWord(0x623b462f);
    modulus.appendWord(0x04142647);
    modulus.appendWord(0xf92f9f8f);
    modulus.appendWord(0xda9d272f);
    BigInt exponent(0x61);
    BigInt x(text, length, kBase36Digits, 36);
    if (x == BigInt(0))
        return false;

    BigInt y;
    if (alreadyDecoded == 0)
        y.setPowMod(x, exponent, modulus);
    else
        y = x;

    BigInt h = licenseHash(y, 0x76adf1, modulus);
    if (h == y) {
        if (decodedOut != nullptr)
            y.toString(decodedOut, 200, kBase36Digits, 36, 0);
        return true;
    }
    return false;
}

// @ 0x40451c
static void licenseStore(const char *key)
{
    HKEY hkey;
    strcpy(g_licenseKey, key);
    if (RegCreateKeyA(HKEY_CURRENT_USER, kRegistryPath, &hkey) == ERROR_SUCCESS) {
        RegSetValueExA(hkey, "settings", 0, REG_BINARY, (const BYTE *)key, (DWORD)strlen(key));
        RegCloseKey(hkey);
    }
}

// @ 0x404571
int licenseEnterKey(const char *input, bool store)
{
    char key[300];
    int i = 0;
    do {
        for (;;) {
            char c = *input;
            if (c == '\0' || (c > '`' && c < '{') || (c > '@' && c < '[') || (c > '/' && c < ':'))
                break;
            ++input;
        }
        char c = *input;
        key[i] = c;
        if (c > '`' && c < '{')
            key[i] = c - 0x20;
        if (c != '\0')
            ++input;
        key[i + 1] = '\0';
        ++i;
    } while (i < 25);

    if (key[0] == '\0')
        return 1;
    if (!licenseCheck(key, 0, 0, key))
        return 2;
    if (store)
        licenseStore(key);
    return 0;
}

// @ 0x40461e
bool licenseIsValid()
{
    BYTE stored[200];
    const char *key;
    if (g_licenseKey[0] == '\0') {
        HKEY hkey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, kRegistryPath, 0, KEY_READ, &hkey) != ERROR_SUCCESS)
            return false;
        DWORD size = 25;
        RegQueryValueExA(hkey, "settings", nullptr, nullptr, stored, &size);
        stored[25] = 0;
        RegCloseKey(hkey);
        key = (const char *)stored;
    } else {
        key = g_licenseKey;
    }
    return licenseCheck(key, 0, 1, nullptr);
}
