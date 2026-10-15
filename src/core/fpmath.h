// Floating point helpers matching the MSVC 7.1 runtime used by the original.
//
// The original binary links the x87 CRT: cos (0x41cd94), sin (0x41d084),
// sqrt (0x41d134) and tan (0x41d414) evaluate straight on the FPU with
// FCOS/FSIN/FSQRT/FPTAN.  On the x86 build the same instructions are used here
// so that results are bit-identical to the original; other targets fall back
// to the C runtime.  log (0x41cf20), exp (0x41ce90), pow (0x41e780),
// floor (0x41ec50), atan2 (0x41d9d0), fmod (0x41d9f0) and fabs (0x41e420)
// dispatch to SSE2/x87 library code in the original and map to the CRT here.
#pragma once

#include <cmath>

#if defined(_M_IX86) && !defined(SUMO_NO_X87)
#define SUMO_X87 1
#endif

namespace fp {

#ifdef SUMO_X87
#pragma warning(push)
#pragma warning(disable : 4035) // no return statement: the result is left in ST(0)
// Never inline these: the result is only returned through ST(0) by the
// calling convention. When MSVC inlines a function like this it ignores ST(0)
// (and leaks it on the FPU stack), which broke every optimized build.
#define SUMO_X87_FN inline __declspec(noinline)
SUMO_X87_FN double cos(double x) { __asm { fld x } __asm { fcos } }
SUMO_X87_FN double sin(double x) { __asm { fld x } __asm { fsin } }
SUMO_X87_FN double sqrt(double x) { __asm { fld x } __asm { fsqrt } }
SUMO_X87_FN double tan(double x) { __asm { fld x } __asm { fptan } __asm { fstp st(0) } }
// FPATAN: atan2(y, x) evaluated on the FPU (used by the texture generator).
SUMO_X87_FN double fpatan(double y, double x) { __asm { fld y } __asm { fld x } __asm { fpatan } }
#pragma warning(pop)
#else
inline double cos(double x) { return std::cos(x); }
inline double sin(double x) { return std::sin(x); }
inline double sqrt(double x) { return std::sqrt(x); }
inline double tan(double x) { return std::tan(x); }
inline double fpatan(double y, double x) { return std::atan2(y, x); }
#endif

inline double log(double x) { return std::log(x); }
inline double exp(double x) { return std::exp(x); }
inline double pow(double x, double y) { return std::pow(x, y); }
inline double floor(double x) { return std::floor(x); }
inline double atan2(double y, double x) { return std::atan2(y, x); }
inline double fmod(double x, double y) { return std::fmod(x, y); }
inline double fabs(double x) { return std::fabs(x); }

// @ 0x41d384 (_ftol2): truncating float to int conversion.
inline int ftol(double x) { return (int)x; }

// FISTP: float to int conversion in the current rounding mode (round to
// nearest even; Direct3D leaves the FPU in that mode).
inline int fistp(double x) { return (int)std::lrint(x); }

} // namespace fp
