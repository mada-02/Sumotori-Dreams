// Arbitrary precision integer used by the licence key check.
// Magnitude is stored as little-endian 32-bit words, sign is +1 / -1.
#pragma once

#include "../core/common.h"

class BigInt {
public:
    ArrayList<uint32_t> words;
    int sign;

    BigInt();                                   // @ 0x401360
    BigInt(int value);                          // @ 0x401206
    BigInt(const BigInt &other);                // @ 0x401247
    BigInt(const char *text, int length,        // @ 0x40180e
           const char *digits, int base);
    ~BigInt() { words.release(); }              // @ 0x404f9c

    BigInt &operator=(const BigInt &other);     // @ 0x4011b6

    void trim();                                // @ 0x40106c
    void invert();                              // @ 0x4010ac
    bool testBit(unsigned bit);                 // @ 0x4010d6
    void copyWords(const BigInt &other);        // @ 0x40114e
    void ensureSize(unsigned count);            // @ 0x4011d1
    void setWord(uint32_t value);               // @ 0x40126c
    void setBit(unsigned bit, int value);       // @ 0x401290
    void incrementMagnitude();                  // @ 0x401301
    void appendWord(uint32_t value);            // @ 0x401348

    void operator-=(const BigInt &o);           // @ 0x401391
    void operator+=(const BigInt &o);           // @ 0x401482
    BigInt operator*(const BigInt &o);          // @ 0x40155e
    BigInt operator<<(int bits);                // @ 0x401680
    BigInt operator+(const BigInt &o);          // @ 0x401764
    BigInt operator-(const BigInt &o);          // @ 0x4017b9
    bool operator==(const BigInt &o);           // @ 0x401948
    bool operator>(const BigInt &o);            // @ 0x401980
    BigInt operator%(const BigInt &o);          // @ 0x401adb
    BigInt operator/(const BigInt &o);          // @ 0x401b5c

    int log(const BigInt &base);                // @ 0x401bb9  floor(log_base(this))
    BigInt pow(int exponent);                   // @ 0x401cff
    void setPowMod(const BigInt &base,          // @ 0x401e60
                   const BigInt &exponent,
                   const BigInt &modulus);
    void toString(char *out, int outSize,       // @ 0x401fb4
                  const char *digits, int base, int groupedDigits);

    unsigned wordCount() const { return words.usize(); }
    uint32_t &word(unsigned i) { return words.at(i); }

    // @ 0x4019b1  q = a / b (both non-negative), schoolbook bitwise division.
    static void divide(BigInt &a, BigInt &b, BigInt &q);
};
