// ==== 0x404872 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404872(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)*param_1;
  if (*(float *)param_1[1] <= _DAT_004343cc) {
    puVar2 = (undefined4 *)param_1[3];
  }
  else {
    puVar2 = (undefined4 *)param_1[2];
  }
  *puVar1 = *puVar2;
  puVar1[1] = puVar2[1];
  puVar1[2] = puVar2[2];
  return;
}


// ==== 0x404ce4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404ce4(undefined4 *param_1)

{
  undefined4 *puVar1;
  float fVar2;
  
  puVar1 = (undefined4 *)*param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  fVar2 = _DAT_0042b28c;
  if ((DAT_00467b4c != 0) &&
     (*(undefined4 *)(DAT_00467b4c + 0x54) = *(undefined4 *)param_1[1],
     *(float *)(DAT_00467b4c + 0x54) < fVar2)) {
    *(float *)(DAT_00467b4c + 0x54) = fVar2;
    return;
  }
  return;
}


// ==== 0x404e53 ====

void FUN_00404e53(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined4 uVar6;
  
  puVar1 = (undefined4 *)*param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  uVar2 = DAT_004e7bb0;
  if (DAT_00d0f9f8 == 0) {
    if (DAT_004e7bb0 < 9) {
      puVar1 = (undefined4 *)param_1[1];
      iVar4 = DAT_004e7bb0 * 3;
      (&DAT_00467b50)[DAT_004e7bb0 * 3] = *puVar1;
      (&DAT_00467b54)[iVar4] = puVar1[1];
      (&DAT_00467b58)[uVar2 * 3] = puVar1[2];
      fVar5 = (float10)FUN_004046eb(*(undefined4 *)param_1[2],((undefined4 *)param_1[2])[2]);
      uVar2 = DAT_004e7bb0;
      DAT_004e7bb0 = DAT_004e7bb0 + 1;
      (&DAT_004e7bb4)[uVar2] = (float)fVar5;
    }
  }
  else if (PTR_DAT_00453858 < &DAT_00c08820) {
    puVar1 = (undefined4 *)param_1[2];
    uVar6 = 0;
    uVar3 = FUN_0041d384(0);
    fVar5 = (float10)FUN_004046eb(*puVar1,puVar1[2],uVar3);
    FUN_0040ec0d(param_1[1],(float)fVar5,uVar3,uVar6);
    *(undefined4 *)(PTR_DAT_00453858 + 0x140) = 0;
    *(undefined4 *)(PTR_DAT_00453858 + 0x6fc) = 2;
    iVar4 = FUN_0041d384();
    if (iVar4 == 3) {
      *(undefined4 *)(PTR_DAT_00453858 + 0x6fc) = 1;
    }
    iVar4 = FUN_0041d384();
    if (iVar4 == 2) {
      *(undefined4 *)(PTR_DAT_00453858 + 0x6fc) = 0;
    }
    *(undefined4 *)(PTR_DAT_00453858 + 0x140) = 1;
    PTR_DAT_00453858 = PTR_DAT_00453858 + 0x730;
  }
  return;
}


// ==== 0x404f6c ====

void FUN_00404f6c(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  if (DAT_00467b4c != 0) {
    FUN_00409679(param_1[1],*(undefined4 *)param_1[2]);
  }
  return;
}


// ==== 0x40778f ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_00406eba(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  int *piVar11;
  float10 fVar12;
  undefined1 auStack_214 [12];
  undefined1 auStack_208 [12];
  undefined1 auStack_1fc [12];
  undefined1 auStack_1f0 [12];
  undefined1 auStack_1e4 [12];
  undefined1 auStack_1d8 [12];
  undefined1 auStack_1cc [12];
  undefined1 auStack_1c0 [12];
  undefined1 auStack_1b4 [12];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  int iStack_190;
  int iStack_18c;
  int iStack_188;
  undefined4 uStack_184;
  float fStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  int iStack_16c;
  int iStack_168;
  int iStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  float fStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  int iStack_13c;
  int iStack_138;
  int iStack_134;
  int iStack_130;
  int iStack_12c;
  int iStack_128;
  int iStack_124;
  int iStack_120;
  int iStack_11c;
  int iStack_118;
  int iStack_114;
  int iStack_110;
  int iStack_10c;
  int iStack_108;
  int iStack_104;
  int iStack_100;
  int iStack_fc;
  int iStack_f8;
  int iStack_f4;
  int iStack_f0;
  int iStack_ec;
  int iStack_e8;
  int iStack_e4;
  int iStack_e0;
  undefined4 uStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  int aiStack_d0 [4];
  float fStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  int iStack_9c;
  undefined4 uStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  float afStack_7c [4];
  int aiStack_6c [4];
  int iStack_5c;
  int iStack_58;
  float fStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  float fStack_44;
  int iStack_40;
  int iStack_3c;
  float fStack_38;
  int iStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  int aiStack_20 [2];
  float fStack_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  int *piStack_8;
  
  if (DAT_00d0f9f8 == 0) {
    DAT_00c06978 = 0;
    FUN_004169a7(1);
    DAT_00453ce0 = 0xffffffff;
    DAT_00c06b50 = 10;
    FUN_00410527(0);
    uStack_24 = 0x3f800000;
    aiStack_20[1] = 0x3f800000;
    _DAT_00c06808 = 0x42a00000;
    DAT_00562c10 = 0;
    afStack_7c[0] = -7.0;
    afStack_7c[1] = 7.0;
    afStack_7c[2] = 7.0;
    aiStack_d0[0] = 3;
    aiStack_d0[1] = 3;
    aiStack_d0[2] = 4;
    aiStack_6c[0] = 4;
    aiStack_6c[1] = 4;
    aiStack_6c[2] = 3;
    iStack_10 = -4;
    uStack_30 = 0xc2a00000;
    uStack_2c = 0x41700000;
    aiStack_20[0] = -0x3e380000;
    do {
      fStack_28 = (float)iStack_10 * _DAT_0042c640;
      FUN_00408d57(uStack_24,aiStack_20[0],aiStack_20[1],uStack_30,uStack_2c,fStack_28,1,
                   _DAT_0042c63c);
      FUN_004089b4();
      iStack_10 = iStack_10 + 1;
    } while (iStack_10 < 5);
    fStack_28 = 0.0;
    uStack_30 = 0xc2a00000;
    uStack_2c = 0x42200000;
    uStack_24 = 0x40800000;
    aiStack_20[0] = -0x40400000;
    aiStack_20[1] = 0x41f00000;
    iVar8 = FUN_00408d57(0x40800000,0xbfc00000,0x41f00000,0xc2a00000,0x42200000,0,1,_DAT_0042c63c);
    FUN_004089b4();
    fStack_28 = 0.0;
    uStack_2c = 0;
    iStack_40 = DAT_004eac7c + 4;
    uStack_30 = 0;
    iStack_3c = 0;
    iStack_10 = 1;
    if (DAT_004eac7c == 0) {
      iStack_10 = 3;
      fStack_28 = 20.0;
    }
    if (DAT_004eac7c == 3) {
      iStack_10 = 2;
      aiStack_6c[0] = 0;
      iStack_3c = 2;
      iStack_40 = 4;
    }
    if (DAT_004eac7c == 1) {
      fStack_28 = 10.0;
      iStack_10 = 2;
      aiStack_6c[1] = 2;
      iStack_3c = 0;
      iStack_40 = 7;
    }
    iStack_48 = 0;
    iStack_5c = iVar8;
    if (iStack_10 != 0) {
      uStack_148 = _DAT_0042c638;
      uStack_144 = 0;
      uStack_140 = 0xc0e00000;
      uStack_24 = _DAT_0042c638;
      uStack_1a8 = _DAT_0042c638;
      uStack_1a4 = 0;
      uStack_1a0 = 0x40e00000;
      do {
        iVar8 = iStack_48;
        aiStack_20[0] = iStack_5c;
        aiStack_20[1] = iStack_5c;
        piVar9 = (int *)FUN_00402172(auStack_214,&uStack_30);
        iStack_16c = *piVar9;
        iStack_168 = piVar9[1];
        iStack_164 = piVar9[2];
        puVar10 = (undefined4 *)FUN_00402172(auStack_1b4,&uStack_30);
        iStack_14 = 0;
        uStack_160 = *puVar10;
        uStack_15c = puVar10[1];
        uStack_158 = puVar10[2];
        fStack_18 = 40.0;
        iStack_50 = aiStack_6c[iVar8];
        if (0 < aiStack_6c[iVar8]) {
          uStack_a4 = 0;
          iStack_4c = aiStack_d0[iVar8];
          aiStack_d0[3] = _DAT_0042b2b8;
          uStack_bc = _DAT_0042c634;
          uStack_ac = 0xc2aa0000;
          uStack_dc = _DAT_0042b2b8;
          aiStack_6c[3] = iStack_40 + iVar8;
          iStack_58 = iVar8 * 0x10 + 1;
          uStack_d4 = _DAT_0042c634;
          iStack_f4 = 0;
          iStack_f0 = 0x3f800000;
          iStack_ec = 0;
          iStack_10c = 0x3f800000;
          iStack_108 = 0;
          iStack_104 = 0;
          iStack_124 = 0;
          iStack_120 = 0x3f800000;
          iStack_11c = 0;
          iStack_13c = 0x3f800000;
          iStack_138 = 0;
          iStack_134 = 0;
          do {
            iStack_34 = 0;
            if (0 < iStack_4c) {
              iStack_12c = 0x3f666666;
              uStack_a0 = _DAT_0042c630;
              iStack_9c = _DAT_0042c62c;
              uStack_98 = _DAT_0042c630;
              iStack_118 = 0;
              iStack_114 = 0x3f800000;
              iStack_110 = 0;
              iStack_100 = 0x3f800000;
              iStack_fc = 0;
              iStack_f8 = 0;
              iStack_88 = 0;
              iStack_84 = _DAT_0042c62c;
              iStack_80 = 0;
              iStack_130 = 0;
              iStack_128 = 0;
              iStack_e8 = 0;
              iStack_e4 = 0x3f800000;
              iStack_e0 = 0;
              iStack_94 = 0x3f800000;
              iStack_90 = 0;
              iStack_8c = 0;
              do {
                iStack_c = 0;
                piStack_8 = &iStack_16c;
                fStack_54 = fStack_18 + _DAT_0042b2f4;
                fStack_44 = (float)iStack_34 * _DAT_004343cc;
                do {
                  puVar10 = (undefined4 *)
                            FUN_00402279(auStack_1f0,_DAT_0042c628,fStack_54,
                                         *(undefined4 *)((int)afStack_7c + iStack_c));
                  uStack_19c = *puVar10;
                  uStack_198 = puVar10[1];
                  uStack_194 = puVar10[2];
                  puVar10 = (undefined4 *)FUN_00402172(auStack_1d8,&uStack_30);
                  iVar8 = FUN_00408d57(uStack_a0,iStack_9c,uStack_98,*puVar10,puVar10[1],puVar10[2],
                                       0,_DAT_0042c63c);
                  FUN_004025ed(fStack_44);
                  piVar11 = piStack_8;
                  *(float *)(iVar8 + 0xb4) = *(float *)(iVar8 + 0xb4) * _DAT_0042b2e0;
                  *(float *)(iVar8 + 0xb8) = *(float *)(iVar8 + 0xb8) * _DAT_0042c624;
                  piVar9 = (int *)((int)aiStack_20 + iStack_c);
                  *DAT_00561404 = *piVar9;
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 3;
                  DAT_00561404[2] = *piStack_8;
                  *piVar3 = piStack_8[1];
                  piVar4[4] = piStack_8[2];
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 9;
                  DAT_00561404[8] = iStack_118;
                  *piVar3 = iStack_114;
                  piVar4[10] = iStack_110;
                  piVar3 = DAT_00561404;
                  if ((iStack_34 == 0) && (iStack_14 == 0)) {
                    uStack_b8 = 0;
                    uStack_b4 = 0xbf800000;
                    uStack_b0 = 0;
                    piVar4 = DAT_00561404 + 9;
                    DAT_00561404[8] = 0;
                    *piVar4 = -0x40800000;
                    piVar3[10] = 0;
                  }
                  piVar4 = DAT_00561404;
                  iVar1 = _DAT_0042c620;
                  piVar3 = DAT_00561404 + 0xf;
                  DAT_00561404[0xe] = iStack_100;
                  *piVar3 = iStack_fc;
                  piVar4[0x10] = iStack_f8;
                  DAT_00561404[1] = DAT_00561408 + -0xfc;
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 6;
                  DAT_00561404[5] = iStack_88;
                  *piVar3 = iStack_84;
                  piVar4[7] = iStack_80;
                  piVar4 = DAT_00561404;
                  piVar3 = piStack_8 + 1;
                  *piStack_8 = iStack_130;
                  *piVar3 = iStack_12c;
                  piVar11[2] = iStack_128;
                  piVar3 = DAT_00561404 + 0xc;
                  DAT_00561404[0xb] = iStack_e8;
                  *piVar3 = iStack_e4;
                  piVar4[0xd] = iStack_e0;
                  piVar4 = DAT_00561404;
                  iStack_c = iStack_c + 4;
                  piStack_8 = piStack_8 + 3;
                  piVar3 = DAT_00561404 + 0x12;
                  DAT_00561404[0x11] = iStack_94;
                  *piVar3 = iStack_90;
                  piVar4[0x13] = iStack_8c;
                  *piVar9 = iVar8;
                  DAT_00561404[0x15] = iVar1;
                  DAT_00561404[0x16] = _DAT_0042c61c;
                  DAT_00561404[0x14] = 0;
                  DAT_00561404 = DAT_00561404 + 0x3d;
                } while (iStack_c < 8);
                iStack_34 = iStack_34 + 1;
                fStack_18 = fStack_18 + _DAT_0042c618;
              } while (iStack_34 < iStack_4c);
            }
            fStack_38 = 1.8;
            if (iStack_48 == 2) {
              fStack_38 = 1.9;
              if (iStack_14 == 1) {
                if (DAT_004eac84 == 0) goto LAB_00407494;
                iStack_3c = 1;
              }
              if ((iStack_14 == 2) && (DAT_004eac84 == 0)) {
                iStack_3c = 1;
              }
            }
LAB_00407494:
            fStack_180 = fStack_38 + fStack_18;
            uStack_184 = uStack_ac;
            fStack_c0 = -fStack_38;
            uStack_17c = uStack_a4;
            fStack_a8 = fStack_180;
            piStack_8 = (int *)fStack_c0;
            puVar10 = (undefined4 *)FUN_00402172(auStack_208,&uStack_30);
            iVar8 = FUN_00408d57(aiStack_d0[3],fStack_c0,uStack_bc,*puVar10,puVar10[1],puVar10[2],
                                 aiStack_6c[3],_DAT_0042c614);
            *(int *)(iVar8 + 0xbc) = iStack_58 + iStack_14;
            fStack_44 = (float)(iStack_14 + iStack_3c);
            fStack_150 = (float)piStack_8 - (float)(int)fStack_44 * _DAT_0042c610;
            uStack_154 = uStack_dc;
            uStack_14c = uStack_d4;
            fStack_d8 = fStack_150;
            puVar10 = (undefined4 *)FUN_00406e8a(auStack_1c0);
            fVar6 = _DAT_0042c60c;
            *(undefined4 *)(iVar8 + 0x20) = *puVar10;
            *(undefined4 *)(iVar8 + 0x24) = puVar10[1];
            *(undefined4 *)(iVar8 + 0x28) = puVar10[2];
            *(float *)(iVar8 + 0xac) = *(float *)(iVar8 + 0xac) * fVar6;
            fVar5 = _DAT_0042c608;
            *(float *)(iVar8 + 0xb0) = *(float *)(iVar8 + 0xb0) * _DAT_0042c608;
            *(float *)(iVar8 + 0xa8) = *(float *)(iVar8 + 0xa8) * fVar6;
            *(float *)(iVar8 + 0xb4) = *(float *)(iVar8 + 0xb4) * fVar6;
            *(undefined4 *)(iVar8 + 0xc0) = 2;
            *(float *)(iVar8 + 0xb8) = *(float *)(iVar8 + 0xb8) * fVar5;
            *(undefined4 *)(iVar8 + 0xc4) = 0x40400000;
            fVar12 = (float10)FUN_0040b798(0);
            fVar12 = (float10)FUN_0040b798((float)(fVar12 * (float10)_DAT_0042c600));
            puVar10 = (undefined4 *)
                      FUN_00402279(auStack_1cc,
                                   (float)((fVar12 + (float10)_DAT_0042b2b0) *
                                          (float10)_DAT_0042c5f8));
            uStack_178 = *puVar10;
            uStack_174 = puVar10[1];
            fStack_18 = fStack_38 + fStack_38 + fStack_18;
            uStack_170 = puVar10[2];
            *(undefined4 *)(iVar8 + 0x9c) = uStack_178;
            afStack_7c[3] = (float)piStack_8;
            *(undefined4 *)(iVar8 + 0xa0) = uStack_174;
            piStack_8 = &iStack_16c;
            *(undefined4 *)(iVar8 + 0xa4) = uStack_170;
            *(undefined4 *)(iVar8 + 0x54) = 0x41700000;
            iStack_c = 0;
            do {
              uVar2 = *(undefined4 *)((int)afStack_7c + iStack_c);
              *DAT_00561404 = *(int *)((int)aiStack_20 + iStack_c);
              piVar3 = DAT_00561404;
              piVar9 = DAT_00561404 + 3;
              DAT_00561404[2] = *piStack_8;
              *piVar9 = piStack_8[1];
              piVar3[4] = piStack_8[2];
              piVar3 = DAT_00561404;
              piVar9 = DAT_00561404 + 9;
              DAT_00561404[8] = iStack_f4;
              *piVar9 = iStack_f0;
              piVar3[10] = iStack_ec;
              piVar3 = DAT_00561404;
              piVar9 = DAT_00561404 + 0xf;
              DAT_00561404[0xe] = iStack_10c;
              *piVar9 = iStack_108;
              piVar3[0x10] = iStack_104;
              DAT_00561404[1] = DAT_00561408 + -0xfc;
              piVar9 = (int *)FUN_00402279(auStack_1e4,0,afStack_7c[3],uVar2);
              piVar3 = DAT_00561404;
              uVar2 = *(undefined4 *)((int)afStack_7c + iStack_c);
              iStack_190 = *piVar9;
              iStack_18c = piVar9[1];
              iStack_188 = piVar9[2];
              piVar9 = DAT_00561404 + 6;
              DAT_00561404[5] = iStack_190;
              *piVar9 = iStack_18c;
              piVar3[7] = iStack_188;
              piVar11 = (int *)FUN_00402279(auStack_1fc,0,fStack_38,uVar2);
              piVar4 = piStack_8;
              piVar3 = DAT_00561404;
              iVar1 = _DAT_0042c5f0;
              piVar9 = piStack_8 + 1;
              *piStack_8 = *piVar11;
              *piVar9 = piVar11[1];
              piVar4[2] = piVar11[2];
              iVar7 = iStack_c;
              piVar9 = DAT_00561404 + 0xc;
              DAT_00561404[0xb] = iStack_124;
              *piVar9 = iStack_120;
              piVar3[0xd] = iStack_11c;
              piVar3 = DAT_00561404;
              piVar9 = DAT_00561404 + 0x12;
              DAT_00561404[0x11] = iStack_13c;
              *piVar9 = iStack_138;
              piVar3[0x13] = iStack_134;
              DAT_00561404[0x15] = iVar1;
              DAT_00561404[0x16] = _DAT_0042c61c;
              piStack_8 = piStack_8 + 3;
              DAT_00561404[0x14] = 0;
              iVar1 = iStack_c + 4;
              iStack_c = iVar1;
              DAT_00561404 = DAT_00561404 + 0x3d;
              *(int *)((int)aiStack_20 + iVar7) = iVar8;
            } while (iVar1 < 8);
            iStack_14 = iStack_14 + 1;
          } while (iStack_14 < iStack_50);
        }
        fStack_28 = fStack_28 - _DAT_0042b2dc;
        iStack_48 = iStack_48 + 1;
      } while (iStack_48 < iStack_10);
    }
    thunk_FUN_00408c36();
  }
  else {
    if (DAT_004eac88 != '\0') {
      DAT_00d0f9fc = 1;
    }
    DAT_004eac88 = '\x01';
    DAT_00c06b38 = 0;
    FUN_00406c59(0);
  }
  return;
}


// ==== 0x407c85 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00407c85(void)

{
  _DAT_004eacc4 = 0;
  _DAT_004eacc8 = &DAT_00436070;
  _DAT_004eacc0 = 0x20000;
  return &DAT_004eacc0;
}


// ==== 0x407d15 ====

undefined4 FUN_00407d15(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


// ==== 0x4158c7 ====

void FUN_004158c7(void)

{
  return;
}


// ==== 0x415ed4 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

LRESULT FUN_00415ed4(HWND param_1,UINT param_2,uint param_3,int param_4)

{
  int iVar1;
  BOOL BVar2;
  LRESULT LVar3;
  tagOFNA local_260 [3];
  tagPAINTSTRUCT local_110;
  char local_d0;
  char local_cf;
  char local_ce;
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  if (param_2 == 2) {
    DAT_00d0f33c = (HWND)0x0;
LAB_004160d6:
    DAT_00d0f3ac = 2;
LAB_004160dc:
    LVar3 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  else {
    if (param_2 == 0xf) {
      BeginPaint(param_1,&local_110);
      EndPaint(param_1,&local_110);
    }
    else {
      if (param_2 != 0x10) {
        if (param_2 == 0x111) {
          if (param_3 >> 0x10 == 0) {
            if (param_4 == DAT_00d0f384) {
              GetCurrentDirectoryA(0xfc,(LPSTR)&local_260[0].pvReserved);
              FUN_0041d7c0(&local_260[0].pvReserved,"\\*.smo");
              _memset(local_260,0,0x4c);
              local_260[0].lpstrFile = (LPSTR)&local_260[0].pvReserved;
              local_260[0].lStructSize = 0x4c;
              local_260[0].hwndOwner = (HWND)0x0;
              local_260[0].lpstrFilter = "Sumotori Mods (*.smo)";
              local_260[0].nMaxFile = 0x104;
              local_260[0].Flags = 0x81000;
              local_260[0].lpstrDefExt = (LPCSTR)&PTR_DAT_0042cbf4;
              BVar2 = GetOpenFileNameA(local_260);
              if (BVar2 != 0) {
                FUN_00403fbd(local_260[0].lpstrFile);
              }
              if (DAT_004eac70 == -1) {
                param_4 = DAT_00d0f378;
              }
            }
            if (param_4 == DAT_00d0f378) {
              iVar1 = FUN_0040461e();
              if (iVar1 == 0) {
                GetWindowTextA(DAT_00d0f34c,&local_d0,199);
                if (((local_d0 != '\0') && (local_cf != '\0')) && (local_ce != '\0')) {
                  iVar1 = FUN_00404571(&local_d0,1);
                  if (iVar1 != 0) {
                    MessageBoxA(DAT_00d0f33c,"Invalid license key","Error",0);
                  }
                }
              }
              FUN_00415cf8();
              FUN_00415e35();
              DAT_00d0f3ac = 1;
            }
            if (param_4 == DAT_00d0f374) {
              FUN_00415cf8();
              goto LAB_004160d6;
            }
          }
          else if (param_3 >> 0x10 == 0x400) {
            GetWindowTextA(DAT_00d0f34c,&local_d0,199);
            iVar1 = FUN_00404571(&local_d0,1);
            if ((iVar1 == 0) && (DAT_00d0f34c != (HWND)0x0)) {
              FUN_00415df1();
            }
          }
        }
        goto LAB_004160dc;
      }
      DAT_00d0f3ac = 2;
    }
    LVar3 = 0;
  }
  return LVar3;
}


// ==== 0x4188c7 ====

void FUN_004188c7(int *param_1)

{
  int iVar1;
  
  if (param_1[0x4d] == 0) {
    if (-1 < param_1[0x54]) {
      param_1[0x51] = param_1[0x54];
    }
    if (-1 < param_1[0x53]) {
      param_1[0x50] = param_1[0x53];
    }
    FUN_00418029(param_1);
    if (param_1[0x53] == -1) {
      param_1[0x53] = param_1[0x50] + 1;
      if (*(int *)(*param_1 + (uint)*(byte *)(param_1[0x51] + 0x28 + (int)param_1) * 8) <=
          param_1[0x50] + 1) {
        iVar1 = param_1[0x51] + 1;
        param_1[0x54] = iVar1;
        if ((short)param_1[4] <= iVar1) {
          param_1[0x54] = (int)*(short *)((int)param_1 + 0x12);
        }
        param_1[0x53] = 0;
      }
    }
  }
  else {
    FUN_00418446(param_1);
  }
  param_1[0x4d] = param_1[0x4d] + 1;
  if (param_1[0x52] + param_1[0x4e] <= param_1[0x4d]) {
    param_1[0x52] = 0;
    param_1[0x4d] = param_1[0x4d] - param_1[0x4e];
  }
  return;
}


