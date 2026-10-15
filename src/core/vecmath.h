// 3D vector and 3x3 matrix types (row-major, rows are the basis axes).
//
// Operation order inside each expression follows the original x87 code so that
// results round identically.
#pragma once

#include "common.h"

// Floating point expressions are written so that the additions group exactly
// like the x87 code of the original ((a + b) + c in the order the terms were
// loaded); the game runs with the FPU in 24-bit precision after Direct3D
// device creation, so matching the grouping reproduces the results bit-exactly
// on x86 builds.
struct Vec3 {
    float x, y, z;

    // @ 0x402172
    Vec3 operator+(const Vec3 &o) const
    {
        Vec3 r;
        r.x = o.x + x;
        r.y = o.y + y;
        r.z = o.z + z;
        return r;
    }

    // @ 0x4021a7
    Vec3 operator-(const Vec3 &o) const
    {
        Vec3 r;
        r.x = x - o.x;
        r.y = y - o.y;
        r.z = z - o.z;
        return r;
    }

    // @ 0x4021dc  (this x o)
    Vec3 cross(const Vec3 &o) const
    {
        Vec3 r;
        r.x = y * o.z - o.y * z;
        r.y = o.x * z - x * o.z;
        r.z = o.y * x - y * o.x;
        return r;
    }

    // @ 0x402227
    Vec3 operator*(const float &s) const
    {
        Vec3 r;
        r.x = s * x;
        r.y = y * s;
        r.z = z * s;
        return r;
    }

    // @ 0x40471d  (component-wise product)
    Vec3 mul(const Vec3 &o) const
    {
        Vec3 r;
        r.x = o.x * x;
        r.y = o.y * y;
        r.z = o.z * z;
        return r;
    }

    // @ 0x40225a
    void operator+=(const Vec3 &o)
    {
        x = o.x + x;
        y = o.y + y;
        z = o.z + z;
    }

    // @ 0x407e1c
    void operator-=(const Vec3 &o)
    {
        x = x - o.x;
        y = y - o.y;
        z = z - o.z;
    }

    // @ 0x406e8a
    Vec3 operator-() const
    {
        Vec3 r;
        r.x = -x;
        r.y = -y;
        r.z = -z;
        return r;
    }

    // @ 0x4022a2
    // The original returns the sum in ST(0) without rounding it to float;
    // double keeps (almost all of) that precision for the callers.
    double lengthSq() const { return (double)x * x + (double)y * y + (double)z * z; }

    float dot(const Vec3 &o) const { return x * o.x + y * o.y + z * o.z; }

    // @ 0x4022c1  Returns the applied scale (1/length, or 0 for a null vector).
    // The scale stays on the FPU stack; only the products are rounded.
    double normalize()
    {
        double s = fp::sqrt(lengthSq());
        if (s != 0.0)
            s = 1.0 / s;
        x = (float)(s * x);
        y = (float)(s * y);
        z = (float)(s * z);
        return s;
    }

    // @ 0x402302
    Vec3 normalized() const
    {
        double s = fp::sqrt(lengthSq());
        if (s != 0.0)
            s = 1.0 / s;
        Vec3 r;
        r.x = (float)(x * s);
        r.y = (float)(y * s);
        r.z = (float)(z * s);
        return r;
    }

    // @ 0x402e1d  this = this*c + axis*((axis.this)(1-c)) + (this x axis)*s
    void rotate(const Vec3 &axis, float c, float s)
    {
        float d = (axis.z * z + axis.y * y + axis.x * x) * (1.0f - c);
        Vec3 r = (*this * c + axis * d) + cross(axis) * s;
        *this = r;
    }

    // @ 0x402ea2  Rotates by the axis-angle vector w (angle = |w|).
    void rotate(const Vec3 &w)
    {
        Vec3 axis = w;
        axis.normalize();
        float angle = (float)fp::sqrt(w.lengthSq());
        float c = (float)fp::cos(fp::sqrt(w.lengthSq()));
        float s = (float)fp::sin(angle);
        rotate(axis, c, s);
    }
};

// @ 0x402279
inline Vec3 V3(float x, float y, float z)
{
    Vec3 r;
    r.x = x;
    r.y = y;
    r.z = z;
    return r;
}

// @ 0x404761
inline Vec3 V3(float s)
{
    return V3(s, s, s);
}

struct Mat3 {
    float m[9];

    Vec3 &row(int i) { return *(Vec3 *)&m[i * 3]; }
    const Vec3 &row(int i) const { return *(const Vec3 *)&m[i * 3]; }

    // @ 0x407e3b / 0x407e65 / 0x407e90
    Vec3 row0() const { return V3(m[0], m[1], m[2]); }
    Vec3 row1() const { return V3(m[3], m[4], m[5]); }
    Vec3 row2() const { return V3(m[6], m[7], m[8]); }

    // @ 0x40e687
    Vec3 column1() const { return V3(m[1], m[4], m[7]); }

    // @ 0x402429
    void identity()
    {
        m[8] = 1.0f;
        m[4] = 1.0f;
        m[0] = 1.0f;
        m[7] = 0.0f;
        m[6] = 0.0f;
        m[5] = 0.0f;
        m[3] = 0.0f;
        m[2] = 0.0f;
        m[1] = 0.0f;
    }

    // @ 0x402363  (M * v)
    Vec3 operator*(const Vec3 &v) const
    {
        Vec3 r;
        r.x = m[1] * v.y + m[2] * v.z + v.x * m[0];
        r.y = m[4] * v.y + m[3] * v.x + m[5] * v.z;
        r.z = m[7] * v.y + m[6] * v.x + m[8] * v.z;
        return r;
    }

    // @ 0x407fa6
    Mat3 operator*(const Mat3 &b) const
    {
        Mat3 r;
        r.m[0] = b.m[3] * m[3] + b.m[0] * m[0] + m[6] * b.m[6];
        r.m[1] = m[7] * b.m[6] + b.m[3] * m[4] + m[1] * b.m[0];
        r.m[2] = m[8] * b.m[6] + b.m[0] * m[2] + b.m[3] * m[5];
        r.m[3] = b.m[7] * m[6] + b.m[1] * m[0] + b.m[4] * m[3];
        r.m[4] = b.m[7] * m[7] + b.m[4] * m[4] + b.m[1] * m[1];
        r.m[5] = b.m[1] * m[2] + m[8] * b.m[7] + m[5] * b.m[4];
        r.m[6] = b.m[8] * m[6] + b.m[2] * m[0] + b.m[5] * m[3];
        r.m[7] = b.m[8] * m[7] + b.m[5] * m[4] + b.m[2] * m[1];
        r.m[8] = b.m[2] * m[2] + m[8] * b.m[8] + m[5] * b.m[5];
        return r;
    }

    // @ 0x40809f
    Mat3 operator+(const Mat3 &b) const
    {
        Mat3 r;
        for (int i = 0; i < 9; ++i)
            r.m[i] = b.m[i] + m[i];
        return r;
    }

    // @ 0x40381a
    Mat3 transposed() const
    {
        Mat3 r;
        r.m[0] = m[0];
        r.m[1] = m[3];
        r.m[2] = m[6];
        r.m[3] = m[1];
        r.m[4] = m[4];
        r.m[5] = m[7];
        r.m[6] = m[2];
        r.m[7] = m[5];
        r.m[8] = m[8];
        return r;
    }

    // @ 0x407ebb
    Mat3 inverse() const
    {
        float c1 = m[5] * m[6] - m[8] * m[3];
        float c2 = m[7] * m[3] - m[6] * m[4];
        float c0 = m[8] * m[4] - m[5] * m[7];
        float inv = 1.0f / (c0 * m[0] + c1 * m[1] + c2 * m[2]);
        Mat3 r;
        r.m[0] = c0 * inv;
        r.m[3] = (m[2] * m[7] - m[8] * m[1]) * inv;
        r.m[6] = (m[5] * m[1] - m[2] * m[4]) * inv;
        r.m[1] = c1 * inv;
        r.m[4] = (m[8] * m[0] - m[2] * m[6]) * inv;
        r.m[7] = (m[2] * m[3] - m[5] * m[0]) * inv;
        r.m[2] = c2 * inv;
        r.m[5] = (m[6] * m[1] - m[0] * m[7]) * inv;
        r.m[8] = (m[0] * m[4] - m[3] * m[1]) * inv;
        return r;
    }

    // Rotations applied to the rows (pre-multiplication).
    // @ 0x402456
    void rotateY(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[6];
        m[6] = s * m[0] + c * m[6];
        m[0] = c * m[0] - s * t;
        t = m[7];
        m[7] = c * m[7] + s * m[1];
        m[1] = c * m[1] - s * t;
        t = m[8];
        m[8] = c * m[8] + s * m[2];
        m[2] = c * m[2] - s * t;
    }

    // @ 0x4024da
    void rotateX(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[6];
        m[6] = c * m[6] - s * m[3];
        m[3] = c * m[3] + s * t;
        t = m[7];
        m[7] = c * m[7] - s * m[4];
        m[4] = c * m[4] + s * t;
        t = m[8];
        m[8] = c * m[8] - s * m[5];
        m[5] = c * m[5] + s * t;
    }

    // @ 0x402565
    void rotateZ(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[3];
        m[3] = c * m[3] - s * m[0];
        m[0] = c * m[0] + s * t;
        t = m[4];
        m[4] = c * m[4] - s * m[1];
        m[1] = c * m[1] + s * t;
        t = m[5];
        m[5] = c * m[5] - s * m[2];
        m[2] = c * m[2] + s * t;
    }

    // Rotations applied to the columns (post-multiplication).
    // @ 0x4025ed
    void rotateLocalY(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[2];
        m[2] = s * m[0] + c * m[2];
        m[0] = c * m[0] - s * t;
        t = m[5];
        m[5] = c * m[5] + s * m[3];
        m[3] = c * m[3] - s * t;
        t = m[8];
        m[8] = c * m[8] + s * m[6];
        m[6] = c * m[6] - s * t;
    }

    // @ 0x402671
    void rotateLocalX(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[2];
        m[2] = c * m[2] - s * m[1];
        m[1] = c * m[1] + s * t;
        t = m[5];
        m[5] = c * m[5] - s * m[4];
        m[4] = c * m[4] + s * t;
        t = m[8];
        m[8] = c * m[8] - s * m[7];
        m[7] = c * m[7] + s * t;
    }

    // @ 0x4026fc
    void rotateLocalZ(float a)
    {
        float c = (float)fp::cos(a);
        double s = fp::sin(a); // kept on the FPU stack in the original
        float t = m[1];
        m[1] = c * m[1] - s * m[0];
        m[0] = c * m[0] + s * t;
        t = m[4];
        m[4] = c * m[4] - s * m[3];
        m[3] = c * m[3] + s * t;
        t = m[7];
        m[7] = c * m[7] - s * m[6];
        m[6] = c * m[6] + s * t;
    }

    // @ 0x4090cb  Gram-Schmidt style re-orthonormalisation of the rows.
    void orthonormalize()
    {
        row(0) = row0().normalized();
        row(1) = row1().normalized();
        row(2) = row0().cross(row1());
        row(1) = row2().cross(row0());
    }

    // @ 0x4091b0
    void rotate(const Vec3 &axis, float c, float s)
    {
        Vec3 r0 = row0();
        Vec3 r1 = row1();
        Vec3 r2 = row2();
        r0.rotate(axis, c, s);
        r1.rotate(axis, c, s);
        r2.rotate(axis, c, s);
        row(0) = r0;
        row(1) = r1;
        row(2) = r2;
    }

    // @ 0x40927f
    void rotate(const Vec3 &w)
    {
        Vec3 axis = w;
        axis.normalize();
        float angle = (float)fp::sqrt(w.lengthSq());
        float c = (float)fp::cos(fp::sqrt(w.lengthSq()));
        float s = (float)fp::sin(angle);
        rotate(axis, c, s);
    }
};

// @ 0x4023c6  (v * M, i.e. M^T * v)
inline Vec3 operator*(const Vec3 &v, const Mat3 &mt)
{
    const float *m = mt.m;
    Vec3 r;
    r.x = m[6] * v.z + m[3] * v.y + m[0] * v.x;
    r.y = m[7] * v.z + m[1] * v.x + m[4] * v.y;
    r.z = m[8] * v.z + m[2] * v.x + m[5] * v.y;
    return r;
}

// @ 0x4046b5 (atan2 on floats) / 0x4046eb (wrapper)
inline double atanXY(float y, float x)
{
    return fp::atan2(y, x);
}
