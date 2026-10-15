// MiniFMOD software mixer: interpolating, volume ramping x87 mixer and the
// float to 16 bit clip/copy. Both are hand written assembly in MiniFMOD; the
// mixer below is a transcription of the shipped code (labels carry the
// original addresses).
#include "minifmod.h"

#if !defined(_M_IX86)
#error The MiniFMOD mixer is x86 inline assembly; build for Win32.
#endif

#pragma warning(disable : 4731)   // EBP is used as a general register below

static unsigned int mix_channelsleft;          // @ 0xd0fe34 set, never read
static unsigned int mix_channel;               // @ 0xd0fe38
static unsigned int mix_numsamples;            // @ 0xd0fe3c
static unsigned int mix_mixptr;                // @ 0xd0fe40
static unsigned int mix_mixbuffend;            // @ 0xd0fe44
static unsigned int mix_mixbuffptr;            // @ 0xd0fe48
static unsigned int mix_endflag;               // @ 0xd0fe4c
static unsigned int mix_sptr;                  // @ 0xd0fe50
static unsigned int mix_cptr;                  // @ 0xd0fe54
static unsigned int mix_count;                 // @ 0xd0fe58
static unsigned int mix_samplebuff;            // @ 0xd0fe5c
static float mix_leftvol;                      // @ 0xd0fe60
static float mix_rightvol;                     // @ 0xd0fe64
static unsigned int mix_temp1;                 // @ 0xd0fe68
static unsigned int mix_count_old;             // @ 0xd0fe6c
static unsigned int mix_rampleftvol;           // @ 0xd0fe70 float while mixing, 24.8 fixed afterwards
static unsigned int mix_ramprightvol;          // @ 0xd0fe74
static unsigned int mix_rampcount;             // @ 0xd0fe78
static float mix_rampleftvoldelta;             // @ 0xd0fe7c
static float mix_ramprightvoldelta;            // @ 0xd0fe80

static const float mix_255 = 255.0f;                       // @ 0x42cd7c
static const float mix_256 = 256.0f;                       // @ 0x42cd80
static const float mix_1over255 = 1.0f / 255.0f;           // @ 0x42cd84
static const float mix_1over256 = 1.0f / 256.0f;           // @ 0x42cd88
static const float mix_1over2gig = 1.0f / 2147483648.0f;   // @ 0x42cd8c

// @ 0x417320
void FSOUND_MixerClipCopy_Float32(void *dest, void *src, int len)
{
    short *destptr = (short *)dest;
    float *srcptr = (float *)src;
    if (len <= 0 || !dest || !src)
        return;
    for (int count = len * 2; count > 0; --count) {
        int val;
        __asm {
            mov eax, srcptr
            fld dword ptr [eax]
            add srcptr, 4
            fistp val
        }
        if (val < -32768)
            val = -32768;
        else if (val > 32767)
            val = 32767;
        *destptr++ = (short)val;
    }
}

// @ 0x417379
// Mixes len stereo float samples of the first 64 channels into mixptr.
// FSOUND_CHANNEL offsets: 0x1c sptr, 0x20/0x24 left/right volume, 0x28/0x2c
// mixpos, 0x30/0x34 speed, 0x38 direction, 0x3c..0x54 ramp state.
// FSOUND_SAMPLE offsets: 0x00 buff, 0x08 loopstart, 0x0c looplen, 0x1d loopmode.
void FSOUND_Mixer_FPU_Ramp(void *mixptr, int len, char)
{
    __asm {
        mov eax, len
        test eax, eax
        jle MixExit
        mov ecx, mixptr
        mov mix_numsamples, eax
        lea eax, [ecx + eax * 8]
        mov mix_mixptr, ecx
        mov mix_mixbuffend, eax
        lea eax, FSOUND_Channel
        mov len, eax                        // len is reused as the channel cursor
        mov mix_channelsleft, 64

    ChannelLoop:                            // 4173b1
        mov eax, len
        mov mix_channel, eax
        push ebp
        mov ebx, mix_mixptr
        mov mix_mixbuffptr, ebx
        mov ecx, mix_channel
        mov mix_cptr, ecx
        cmp ecx, 0
        je MixExitChannel
        mov ebx, [ecx + 0x1c]
        mov mix_sptr, ebx
        cmp ebx, 0
        je MixExitChannel
        mov eax, [ebx]
        mov mix_samplebuff, eax
        mov eax, mix_numsamples

        // ===== samples until the loop / sample end =====
    CalculateLoopCount:                     // 4173f9
        mov mix_count, eax
        mov esi, [ecx + 0x28]
        mov ebp, 0
        mov mix_endflag, ebp
        cmp dword ptr [ecx + 0x38], 1
        jne SamplesLeftBackwards
        mov edx, [ebx + 0x8]
        add edx, [ebx + 0xc]
        sub edx, esi
        mov eax, [ecx + 0x2c]
        xor ebp, ebp
        sub ebp, eax
        sbb edx, 0
        mov eax, ebp
        jmp SamplesLeftOK
    SamplesLeftBackwards:                   // 417428
        mov edx, [ecx + 0x28]
        mov eax, [ecx + 0x2c]
        sub eax, 0
        sbb edx, [ebx + 0x8]
    SamplesLeftOK:                          // 417434
        cmp edx, 0x1000000
        jae DontCalcCount
        shrd eax, edx, 8
        shr edx, 8
        mov ebp, [ecx + 0x34]
        mov edi, [ecx + 0x30]
        shl ebp, 24
        shr edi, 8
        and edi, 0xffffff
        or ebp, edi
        div ebp
        or edx, edx
        jz NoRemainder
        inc eax
    NoRemainder:                            // 41745e
        cmp eax, mix_count
        ja DontCalcCount
        mov mix_count, eax
        mov edx, 1
        mov mix_endflag, edx

        // ===== volume ramp setup =====
    DontCalcCount:                          // 417476
        mov ecx, mix_cptr
        mov dword ptr mix_rampleftvoldelta, 0
        mov dword ptr mix_ramprightvoldelta, 0
        mov eax, mix_count
        mov mix_count_old, eax
        mov mix_rampcount, 0
        cmp dword ptr [ecx + 0x54], 0
        je RampSetup
        mov eax, [ecx + 0x20]
        mov edx, [ecx + 0x3c]
        cmp eax, edx
        jne RampSetup
        mov eax, [ecx + 0x24]
        mov edx, [ecx + 0x40]
        cmp eax, edx
        jne RampSetup
        // continue an unfinished ramp towards the same target
        mov eax, [ecx + 0x54]
        mov mix_rampcount, eax
        mov eax, [ecx + 0x4c]
        mov dword ptr mix_rampleftvoldelta, eax
        mov eax, [ecx + 0x50]
        mov dword ptr mix_ramprightvoldelta, eax
        jmp RampDone
    RampSetup:                              // 4174db
        mov eax, [ecx + 0x20]
        mov edx, [ecx + 0x44]
        shr edx, 8
        mov [ecx + 0x3c], eax
        sub eax, edx
        cmp eax, 0
        je NoLeftRamp
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over255
        fmul dword ptr mix_1overvolumerampsteps
        fstp dword ptr mix_rampleftvoldelta
        mov eax, dword ptr mix_rampleftvoldelta
        mov [ecx + 0x4c], eax
        mov eax, mix_volumerampsteps
        mov mix_rampcount, eax
    NoLeftRamp:                             // 41751d
        mov eax, [ecx + 0x24]
        mov edx, [ecx + 0x48]
        shr edx, 8
        mov [ecx + 0x40], eax
        sub eax, edx
        cmp eax, 0
        je RampDone
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over255
        fmul dword ptr mix_1overvolumerampsteps
        fstp dword ptr mix_ramprightvoldelta
        mov eax, dword ptr mix_ramprightvoldelta
        mov [ecx + 0x50], eax
        mov eax, mix_volumerampsteps
        mov mix_rampcount, eax
    RampDone:                               // 41755f
        mov eax, mix_rampcount
        cmp eax, 0
        jle NoRamp
        mov [ecx + 0x54], eax
        cmp mix_count, eax
        jbe NoRamp
        mov mix_count, eax
    NoRamp:                                 // 417579
        mov ecx, mix_cptr
        mov eax, [ecx + 0x24]
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over255
        fstp dword ptr mix_rightvol
        mov eax, [ecx + 0x20]
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over255
        fstp dword ptr mix_leftvol
        mov eax, [ecx + 0x48]
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over256
        fmul dword ptr mix_1over255
        fstp dword ptr mix_ramprightvol
        mov eax, [ecx + 0x44]
        mov mix_temp1, eax
        fild dword ptr mix_temp1
        fmul dword ptr mix_1over256
        fmul dword ptr mix_1over255
        fstp dword ptr mix_rampleftvol

        // ===== mix =====
        mov eax, mix_cptr
        mov ebx, [eax + 0x30]
        mov ecx, [eax + 0x34]
        mov ebp, [eax + 0x2c]
        mov esi, [eax + 0x28]
        mov edi, mix_mixbuffptr
        cmp dword ptr [eax + 0x38], 1
        je NoChangeSpeed
        xor ebx, 0xffffffff
        xor ecx, 0xffffffff
        add ebx, 1
        adc ecx, 0
    NoChangeSpeed:                          // 41761c
        mov eax, mix_samplebuff
        shr eax, 1
        add esi, eax
        mov edx, mix_count
        cmp mix_rampcount, 0
        jne MixLoopStart1

        // two samples per iteration, no ramping
        shr edx, 1
        or edx, edx
        jz MixLoopStartOdd
        shr ebp, 1
        add edi, 16
        fild word ptr [esi + esi + 2]
        mov mix_temp1, ebp
        fild word ptr [esi + esi]
        fild dword ptr mix_temp1
        add ebp, ebp
        add ebp, ebx
        adc esi, ecx
        fmul dword ptr mix_1over2gig
        fild word ptr [esi + esi + 2]
        shr ebp, 1
        mov mix_temp1, ebp
        fild dword ptr mix_temp1
        fild word ptr [esi + esi]
        fxch st(5)
        fsub st(0), st(4)
        shl ebp, 1
        fmulp st(3), st(0)
        fmul dword ptr mix_1over2gig
        fxch st(1)
        fsub st(0), st(4)
        add ebp, ebx
        adc esi, ecx
        fmulp st(1), st(0)
        fxch st(1)
        faddp st(2), st(0)
        fld st(1)
        fmul dword ptr mix_leftvol
        fxch st(1)
        faddp st(3), st(0)
        fxch st(1)
        jmp MixLoopMid
    MixLoop16:                              // 4176a9
        shr ebp, 1
        mov mix_temp1, ebp
        fild word ptr [esi + esi + 2]
        fild word ptr [esi + esi]
        fild dword ptr mix_temp1
        add ebp, ebp
        add ebp, ebx
        adc esi, ecx
        add edi, 16
        fmul dword ptr mix_1over2gig
        shr ebp, 1
        mov mix_temp1, ebp
        fild dword ptr mix_temp1
        fild word ptr [esi + esi + 2]
        fxch st(4)
        fsub st(0), st(3)
        shl ebp, 1
        fmulp st(2), st(0)
        fild word ptr [esi + esi]
        fxch st(1)
        fmul dword ptr mix_1over2gig
        fxch st(4)
        fsub st(0), st(1)
        add ebp, ebx
        adc esi, ecx
        fmulp st(4), st(0)
        fxch st(2)
        faddp st(1), st(0)
        fxch st(4)
        fstp dword ptr [edi - 0x1c]
        fxch st(4)
        fstp dword ptr [edi - 0x18]
        fld st(2)
        fmul dword ptr mix_leftvol
        fxch st(1)
        faddp st(4), st(0)
        fxch st(1)
        fstp dword ptr [edi - 0x14]
        fxch st(1)
    MixLoopMid:                             // 41771d
        fmul dword ptr mix_rightvol
        fxch st(2)
        fld st(0)
        fmul dword ptr mix_leftvol
        fxch st(1)
        fmul dword ptr mix_rightvol
        fxch st(2)
        fadd dword ptr [edi - 0x10]
        fxch st(3)
        fadd dword ptr [edi - 0xc]
        fxch st(1)
        fadd dword ptr [edi - 0x8]
        fxch st(3)
        fstp dword ptr [edi - 0x10]
        fxch st(1)
        fadd dword ptr [edi - 0x4]
        dec edx
        jnz MixLoop16
        fxch st(1)
        fstp dword ptr [edi - 0xc]
        fxch st(1)
        fstp dword ptr [edi - 0x8]
        fstp dword ptr [edi - 0x4]

    MixLoopStartOdd:                        // 417762
        mov edx, mix_count
        and edx, 1

        // one sample per iteration with volume ramping
    MixLoopStart1:                          // 41776b
        or edx, edx
        jz MixLoopEnd
        fld dword ptr mix_rampleftvoldelta
        fld dword ptr mix_ramprightvoldelta
        fld dword ptr mix_rampleftvol
        fld dword ptr mix_ramprightvol
        jmp MixLoop1
    MixLoop1:                               // 417799
        shr ebp, 1
        add edi, 8
        fild word ptr [esi + esi + 2]
        mov mix_temp1, ebp
        fild word ptr [esi + esi]
        fild dword ptr mix_temp1
        shl ebp, 1
        add ebp, ebx
        adc esi, ecx
        fmul dword ptr mix_1over2gig
        fxch st(2)
        fsub st(0), st(1)
        fmulp st(2), st(0)
        faddp st(1), st(0)
        fld st(0)
        fmul st(0), st(3)
        fxch st(3)
        fadd st(0), st(5)
        fxch st(1)
        fmul st(0), st(2)
        fxch st(2)
        fadd st(0), st(4)
        fxch st(3)
        fadd dword ptr [edi - 0x8]
        fxch st(2)
        fadd dword ptr [edi - 0x4]
        fxch st(2)
        fstp dword ptr [edi - 0x8]
        fxch st(1)
        fstp dword ptr [edi - 0x4]
        fxch st(1)
        dec edx
        jnz MixLoop1
        fxch st(2)
        fstp dword ptr mix_ramprightvoldelta
        fxch st(2)
        fstp dword ptr mix_rampleftvoldelta
        fmul dword ptr mix_255
        fmul dword ptr mix_256
        fxch st(1)
        fmul dword ptr mix_255
        fmul dword ptr mix_256
        xor eax, eax
        fistp dword ptr mix_rampleftvol
        fistp dword ptr mix_ramprightvol

    MixLoopEnd:                             // 417826
        mov eax, mix_samplebuff
        shr eax, 1
        sub esi, eax
        cmp mix_rampcount, 0
        je MixRampEnd
        mov ebx, mix_sptr
        mov ecx, mix_cptr
        mov eax, mix_rampleftvol
        mov [ecx + 0x44], eax
        mov eax, mix_ramprightvol
        mov [ecx + 0x48], eax
        mov eax, mix_count
        mov edx, mix_rampcount
        sub edx, eax
        mov dword ptr mix_rampleftvoldelta, 0
        mov dword ptr mix_ramprightvoldelta, 0
        mov mix_rampcount, edx
        mov [ecx + 0x54], edx
        cmp edx, 0
        jne MixRampEnd
        // ramp finished: snap to the target volume
        mov dword ptr [ecx + 0x4c], 0
        mov dword ptr [ecx + 0x50], 0
        mov edx, [ecx + 0x20]
        shl edx, 8
        mov [ecx + 0x44], edx
        mov edx, [ecx + 0x24]
        shl edx, 8
        mov [ecx + 0x48], edx
        cmp mix_count_old, eax
        je MixRampEnd
        mov [ecx + 0x28], esi
        mov [ecx + 0x2c], ebp
        mov eax, mix_mixbuffend
        sub eax, edi
        shr eax, 3
        mov mix_mixbuffptr, edi
        cmp eax, 0
        jne CalculateLoopCount

        // ===== loop handling =====
    MixRampEnd:                             // 4178ce
        cmp mix_endflag, 0
        je FinishUpChannel
        mov ebx, mix_sptr
        mov ecx, mix_cptr
        mov dl, [ebx + 0x1d]
        test dl, 2
        jz CheckBidi
        mov eax, [ebx + 0x8]
        add eax, [ebx + 0xc]
    RewindSample:                           // 4178f5
        sub esi, [ebx + 0xc]
        cmp esi, eax
        jae RewindSample
        mov [ecx + 0x28], esi
        mov [ecx + 0x2c], ebp
        mov eax, mix_mixbuffend
        sub eax, edi
        shr eax, 3
        mov mix_mixbuffptr, edi
        cmp eax, 0
        je FinishUpChannel
        jmp CalculateLoopCount
    CheckBidi:                              // 417920
        test dl, 4
        jz NoLoop
        cmp dword ptr [ecx + 0x38], 1
        je BidiForward
    BidiBackwards:                          // 41792f
        mov eax, [ebx + 0x8]
        dec eax
        mov edx, 0xffffffff
        sub edx, ebp
        sbb eax, esi
        mov esi, eax
        mov ebp, edx
        mov eax, [ebx + 0x8]
        mov edx, 0
        add ebp, edx
        adc esi, eax
        mov dword ptr [ecx + 0x38], 1
        mov eax, [ebx + 0x8]
        add eax, [ebx + 0xc]
        cmp esi, eax
        jge BidiForward
        jmp BidiFinish
    BidiForward:                            // 41795f
        mov eax, [ebx + 0x8]
        add eax, [ebx + 0xc]
        mov edx, 0
        sub edx, ebp
        sbb eax, esi
        mov esi, eax
        mov ebp, edx
        mov eax, [ebx + 0x8]
        add eax, [ebx + 0xc]
        dec eax
        mov edx, 0xffffffff
        add ebp, edx
        adc esi, eax
        mov dword ptr [ecx + 0x38], 2
        cmp esi, [ebx + 0x8]
        jl BidiBackwards
    BidiFinish:                             // 41798e
        mov [ecx + 0x28], esi
        mov [ecx + 0x2c], ebp
        mov eax, mix_mixbuffend
        sub eax, edi
        shr eax, 3
        mov mix_mixbuffptr, edi
        cmp eax, 0
        je FinishUpChannel
        jmp CalculateLoopCount
    NoLoop:                                 // 4179ae
        xor ebp, ebp
        xor esi, esi
        mov [ecx + 0x1c], esi
    FinishUpChannel:                        // 4179b5
        mov ecx, mix_cptr
        mov [ecx + 0x2c], ebp
        mov [ecx + 0x28], esi
    MixExitChannel:                         // 4179c1
        pop ebp
        add len, 0x58
        lea eax, FSOUND_Channel[64 * 0x58]
        cmp len, eax
        jl ChannelLoop
    MixExit:
    }
}
