#include "bigint.h"

// Set by nothing else in the program; the multiplication resets it to 1 if it
// was ever non-zero.  Kept because the original reads and writes it.
static int g_bigIntFlag = 1; // @ 0x4533ac

// @ 0x401360
// The original constructor only constructs (and immediately destroys) a
// temporary BigInt(0); the object itself is left empty with an undefined sign.
// Every caller assigns a value before using the sign.
BigInt::BigInt()
{
    BigInt zero(0);
    (void)zero;
}

// @ 0x401206
BigInt::BigInt(int value)
{
    words.resize(1);
    uint32_t &w = words.at(0);
    if (value < 0) {
        w = (uint32_t)-value;
        sign = -1;
    } else {
        w = (uint32_t)value;
        sign = 1;
    }
}

// @ 0x401247
BigInt::BigInt(const BigInt &other)
{
    copyWords(other);
    sign = other.sign;
}

// @ 0x4011b6
BigInt &BigInt::operator=(const BigInt &other)
{
    copyWords(other);
    sign = other.sign;
    return *this;
}

// @ 0x40106c  Removes leading zero words.
void BigInt::trim()
{
    while (words.usize() != 0) {
        if (words.at(words.usize() - 1) != 0)
            break;
        if (words.first < words.last)
            --words.last;
    }
}

// @ 0x4010ac
void BigInt::invert()
{
    for (unsigned i = 0; i < words.usize(); ++i) {
        uint32_t &w = words.at(i);
        w = ~w;
    }
}

// @ 0x4010d6
bool BigInt::testBit(unsigned bit)
{
    if (bit < words.usize() << 5)
        return ((1u << ((int)bit % 32)) & words.at((int)bit / 32)) != 0;
    return false;
}

// @ 0x40114e
void BigInt::copyWords(const BigInt &other)
{
    BigInt &src = const_cast<BigInt &>(other);
    words.resize(src.words.size());
    for (unsigned i = 0; i < src.words.usize(); ++i)
        words.first[i] = src.words.at(i);
}

// @ 0x4011d1
void BigInt::ensureSize(unsigned count)
{
    if (words.usize() < count) {
        uint32_t zero = 0;
        do {
            words.push_back(zero);
        } while (words.usize() < count);
    }
}

// @ 0x40126c
void BigInt::setWord(uint32_t value)
{
    words.resize(1);
    words.at(0) = value;
    sign = 1;
}

// @ 0x401290
void BigInt::setBit(unsigned bit, int value)
{
    if (value == 0) {
        if (bit < words.usize() << 5)
            words.at((int)bit / 32) &= ~(1u << ((int)bit % 32));
    } else if (value == 1) {
        ensureSize((int)bit / 32 + 1);
        words.at((int)bit / 32) |= 1u << ((int)bit % 32);
    }
}

// @ 0x401301
void BigInt::incrementMagnitude()
{
    for (unsigned i = 0; i < words.usize(); ++i) {
        ++words.at(i);
        if (words.at(i) != 0)
            return;
    }
    uint32_t one = 1;
    words.push_back(one);
}

// @ 0x401348
void BigInt::appendWord(uint32_t value)
{
    trim();
    words.push_back(value);
}

// @ 0x401391
void BigInt::operator-=(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    if (sign == o.sign) {
        unsigned n = o.words.usize();
        if (n < words.usize())
            n = words.usize();
        ensureSize(n + 1);
        if (o.words.usize() != 0) {
            uint32_t *src = &o.words.at(0);
            uint32_t *dst = &words.at(0);
            int count = o.words.size();
            int rest = words.size() - count;
            if (count != 0) {
                uint32_t borrow = 0;
                do {
                    uint32_t s = *src;
                    uint32_t d = *dst;
                    uint32_t t = d - borrow;
                    *dst = t - s;
                    borrow = (uint32_t)(d < borrow) + (uint32_t)(t < s);
                    ++dst;
                    ++src;
                } while (--count != 0);
                do {
                    uint32_t d = *dst;
                    *dst = d - borrow;
                    borrow = (uint32_t)(d < borrow);
                    ++dst;
                } while (--rest != 0);
                if (borrow != 0) {
                    sign = -sign;
                    invert();
                    incrementMagnitude();
                }
            }
            trim();
        }
    } else {
        sign = -sign;
        *this += o;
        sign = -sign;
    }
}

// @ 0x401482
void BigInt::operator+=(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    sumoAssert(&o != this);
    if (sign == o.sign) {
        unsigned n = o.words.usize();
        if (n < words.usize())
            n = words.usize();
        ensureSize(n + 1);
        if (o.words.usize() != 0) {
            uint32_t *src = &o.words.at(0);
            uint32_t *dst = &words.at(0);
            int count = o.words.size();
            int rest = words.size() - count;
            if (count != 0) {
                uint32_t carry = 0;
                do {
                    uint32_t s = *src;
                    uint32_t d = *dst;
                    uint32_t t = d + carry;
                    *dst = t + s;
                    carry = (uint32_t)(t < d) + (uint32_t)(t + s < t);
                    ++dst;
                    ++src;
                } while (--count != 0);
                do {
                    uint32_t d = *dst;
                    *dst = d + carry;
                    carry = (uint32_t)(d + carry < d);
                    ++dst;
                } while (--rest != 0);
            }
            trim();
        }
    } else {
        sign = -sign;
        *this -= o;
        sign = -sign;
    }
}

// @ 0x40155e
BigInt BigInt::operator*(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    BigInt r;
    r.ensureSize(o.words.usize() + words.usize());
    for (unsigned i = 0; i < words.usize(); ++i) {
        int n = o.words.size();
        if (n == 0)
            return BigInt(0);
        uint32_t *dst = &r.words.at(i);
        uint32_t *src = &o.words.at(0);
        uint32_t factor = words.at(i);
        do {
            uint64_t p = (uint64_t)*src * factor;
            uint32_t lo = (uint32_t)p;
            uint32_t hi = (uint32_t)(p >> 32);
            uint32_t old0 = dst[0];
            dst[0] = old0 + lo;
            uint32_t c = (uint32_t)(dst[0] < old0);
            uint64_t s1 = (uint64_t)dst[1] + hi + c;
            dst[1] = (uint32_t)s1;
            if (s1 >> 32) {
                uint32_t *q = dst + 1;
                do {
                    ++q;
                    ++*q;
                } while (*q == 0);
            }
            ++dst;
            ++src;
        } while (--n != 0);
    }
    r.sign = o.sign * sign;
    r.trim();
    if (g_bigIntFlag != 0)
        g_bigIntFlag = 1;
    return BigInt(r);
}

// @ 0x401680
BigInt BigInt::operator<<(int bits)
{
    BigInt r;
    // The original over-allocates (word count * 32); kept for fidelity.
    r.ensureSize(words.usize() * 32 + (bits + 31) / 32);
    int wordShift = bits / 32;
    int bitShift = bits % 32;
    for (unsigned i = 0; i < words.usize(); ++i) {
        unsigned target = i + wordShift;
        uint32_t &dst = r.words.at(target);
        dst += words.at(i) << bitShift;
        if (bitShift != 0) {
            uint32_t &src = words.at(i);
            r.words.at(target + 1) = src >> (32 - bitShift);
        }
    }
    r.trim();
    r.sign = sign;
    return BigInt(r);
}

// @ 0x401764
BigInt BigInt::operator+(const BigInt &o)
{
    BigInt t(*this);
    t += o;
    return BigInt(t);
}

// @ 0x4017b9
BigInt BigInt::operator-(const BigInt &o)
{
    BigInt t(*this);
    t -= o;
    return BigInt(t);
}

// @ 0x40180e
BigInt::BigInt(const char *text, int length, const char *digits, int base)
{
    if (length == 0) {
        for (const char *p = text; *p != '\0'; ++p)
            ++length;
    }
    if (digits == nullptr)
        digits = "0123456789";
    setWord(0);
    BigInt place(1);
    const char *p = text + length;
    for (int remaining = length; remaining > 0; --remaining) {
        --p;
        for (int d = 0; d < base; ++d) {
            if (digits[d] == *p) {
                *this += place * BigInt(d);
                place = place * BigInt(base);
                break;
            }
        }
    }
}

// @ 0x401948
bool BigInt::operator==(const BigInt &o)
{
    BigInt d = *this - o;
    return d.words.usize() == 0;
}

// @ 0x401980  (evaluated as (o - this) < 0)
bool BigInt::operator>(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    BigInt d = o - *this;
    return d.sign == -1;
}

// @ 0x4019b1
void BigInt::divide(BigInt &a, BigInt &b, BigInt &q)
{
    sumoAssert(&q != &a && &q != &b);
    sumoAssert(a.sign == 1 && b.sign == 1);
    int bWords = b.words.size();
    if (bWords == 0)
        sumoAssert(false);
    int bit = (a.words.size() - bWords + 1) * 32 - 1;
    q.setWord(0);
    BigInt product(0);
    while (bit >= 0) {
        q.setBit(bit, 1);
        BigInt saved(product);
        product += b << bit;
        if (product > a) {
            q.setBit(bit, 0);
            product = saved;
        }
        --bit;
    }
    q.trim();
}

// @ 0x401adb
BigInt BigInt::operator%(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    BigInt q;
    divide(*this, o, q);
    return *this - q * o;
}

// @ 0x401b5c
BigInt BigInt::operator/(const BigInt &other)
{
    BigInt &o = const_cast<BigInt &>(other);
    BigInt q;
    divide(*this, o, q);
    return BigInt(q);
}

// @ 0x401bb9
int BigInt::log(const BigInt &base)
{
    // powers[k] = base^(2^k)
    BigInt powers[32];
    int result = 0;
    powers[0] = base;
    if (!(powers[0] > *this)) {
        int k = 0;
        BigInt *p = &powers[0];
        do {
            p[1] = *p * *p;
            ++p;
            ++k;
        } while (!(*p > *this));
        --k;
        BigInt acc(powers[k]);
        result = 1 << k;
        while (k > 0) {
            --k;
            BigInt t = acc * powers[k];
            if (!(t > *this)) {
                result |= 1 << k;
                acc = t;
            }
        }
    }
    return result;
}

// @ 0x401cff
BigInt BigInt::pow(int exponent)
{
    BigInt result;
    result.setWord(1);
    BigInt square(*this);
    BigInt mask(1);
    int i = 0;
    bool more;
    do {
        if (exponent & (1 << i))
            result = result * square;
        ++i;
        mask = mask + mask;
        square = square * square;
        more = !(mask > BigInt(exponent));
    } while (more);
    return BigInt(result);
}

// @ 0x401e60
void BigInt::setPowMod(const BigInt &base, const BigInt &exponent, const BigInt &modulus)
{
    BigInt &e = const_cast<BigInt &>(exponent);
    BigInt &m = const_cast<BigInt &>(modulus);
    setWord(1);
    BigInt square(base);
    BigInt mask(1);
    unsigned bit = 0;
    do {
        if (e.testBit(bit))
            *this = (*this * square) % m;
        ++bit;
        mask = mask + mask;
        square = (square * square) % m;
    } while (!(mask > e));
}

// @ 0x401fb4
void BigInt::toString(char *out, int outSize, const char *digits, int base, int groupedDigits)
{
    if (digits == nullptr)
        digits = "0123456789";
    char *end = out + outSize - 1;
    int n = log(BigInt(base));
    if (groupedDigits != 0 && n < groupedDigits - 1)
        n = groupedDigits - 1;
    BigInt divisor = BigInt(base).pow(n);
    BigInt rest(*this);
    int column = 0;
    if (n >= 0) {
        for (int count = n + 1; count != 0; --count) {
            BigInt q = rest / divisor;
            uint32_t d = 0;
            if (q.words.usize() != 0)
                d = q.words.at(0);
            if (out < end) {
                if (column == 5 && groupedDigits != 0) {
                    *out++ = '-';
                    column = 0;
                }
                *out++ = digits[d];
                ++column;
            }
            rest -= divisor * q;
            divisor = divisor / BigInt(base);
        }
    }
    *out = '\0';
}
