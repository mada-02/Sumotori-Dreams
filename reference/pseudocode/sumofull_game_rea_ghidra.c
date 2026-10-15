// ==== 0x401000 ====

int FUN_00401000(int param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  int extraout_EDX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        (uint)(param_1 << 2) < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + extraout_EDX;
}



// ==== 0x401021 ====

void FUN_00401021(void)

{
  int iVar1;
  void *pvVar2;
  int *in_ECX;
  uint _NewSize;
  uint uVar3;
  
  uVar3 = in_ECX[1] - *in_ECX >> 2;
  iVar1 = (uVar3 >> 3) + 1 + uVar3;
  _NewSize = iVar1 * 4;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar2 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar2;
  in_ECX[2] = (int)(_NewSize + (int)pvVar2);
  in_ECX[1] = (int)((int)pvVar2 + uVar3 * 4);
  return;
}



// ==== 0x401067 ====

void thunk_FUN_00404f9c(void)

{
  FUN_00404f9c();
  return;
}



// ==== 0x40106c ====

void FUN_0040106c(void)

{
  int *piVar1;
  uint uVar2;
  uint *in_ECX;
  uint uVar3;
  
  uVar2 = *in_ECX;
  uVar3 = in_ECX[1] - uVar2;
  while( true ) {
    if ((uVar3 & 0xfffffffc) == 0) {
      return;
    }
    piVar1 = (int *)FUN_00401000(((int)(in_ECX[1] - uVar2) >> 2) + -1);
    if (*piVar1 != 0) break;
    uVar2 = *in_ECX;
    if (uVar2 < in_ECX[1]) {
      in_ECX[1] = in_ECX[1] - 4;
    }
    uVar3 = in_ECX[1] - *in_ECX;
  }
  return;
}



// ==== 0x4010ac ====

void FUN_004010ac(void)

{
  uint *puVar1;
  int *in_ECX;
  uint uVar2;
  
  uVar2 = 0;
  if (in_ECX[1] - *in_ECX >> 2 != 0) {
    do {
      puVar1 = (uint *)FUN_00401000(uVar2);
      *puVar1 = ~*puVar1;
      uVar2 = uVar2 + 1;
    } while (uVar2 < (uint)(in_ECX[1] - *in_ECX >> 2));
  }
  return;
}



// ==== 0x4010d6 ====

bool FUN_004010d6(uint param_1)

{
  uint *puVar1;
  int *in_ECX;
  bool bVar2;
  
  if (param_1 < (uint)((in_ECX[1] - *in_ECX >> 2) << 5)) {
    puVar1 = (uint *)FUN_00401000((int)param_1 / 0x20);
    bVar2 = (1 << ((byte)((int)param_1 % 0x20) & 0x1f) & *puVar1) != 0;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 0x401111 ====

void FUN_00401111(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *in_ECX;
  
  iVar2 = *in_ECX;
  puVar3 = (undefined4 *)in_ECX[1];
  uVar1 = iVar2 + param_1 * 4;
  in_ECX[1] = uVar1;
  if ((uint)in_ECX[2] < uVar1) {
    FUN_00401021();
    puVar3 = (undefined4 *)(*in_ECX + ((int)puVar3 - iVar2 >> 2) * 4);
  }
  for (; puVar3 < (undefined4 *)in_ECX[1]; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  return;
}



// ==== 0x40114e ====

void FUN_0040114e(int *param_1)

{
  undefined4 *puVar1;
  int *in_ECX;
  uint uVar2;
  
  FUN_00401111(param_1[1] - *param_1 >> 2);
  uVar2 = 0;
  if (param_1[1] - *param_1 >> 2 != 0) {
    do {
      puVar1 = (undefined4 *)FUN_00401000(uVar2);
      *(undefined4 *)(*in_ECX + uVar2 * 4) = *puVar1;
      uVar2 = uVar2 + 1;
    } while (uVar2 < (uint)(param_1[1] - *param_1 >> 2));
  }
  return;
}



// ==== 0x401193 ====

void FUN_00401193(undefined4 *param_1)

{
  int in_ECX;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_00401021();
  }
  **(undefined4 **)(in_ECX + 4) = *param_1;
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 4;
  return;
}



// ==== 0x4011b6 ====

void FUN_004011b6(int param_1)

{
  int in_ECX;
  
  FUN_0040114e(param_1);
  *(undefined4 *)(in_ECX + 0xc) = *(undefined4 *)(param_1 + 0xc);
  return;
}



// ==== 0x4011d1 ====

void FUN_004011d1(uint param_1)

{
  int *in_ECX;
  undefined4 local_8;
  
  if ((uint)(in_ECX[1] - *in_ECX >> 2) < param_1) {
    local_8 = 0;
    do {
      FUN_00401193(&local_8);
    } while ((uint)(in_ECX[1] - *in_ECX >> 2) < param_1);
  }
  return;
}



// ==== 0x401206 ====

void FUN_00401206(int param_1)

{
  int *piVar1;
  undefined4 *in_ECX;
  
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0;
  FUN_00401111(1);
  piVar1 = (int *)FUN_00401000(0);
  if (param_1 < 0) {
    *piVar1 = -param_1;
    in_ECX[3] = 0xffffffff;
  }
  else {
    *piVar1 = param_1;
    in_ECX[3] = 1;
  }
  return;
}



// ==== 0x401247 ====

void FUN_00401247(int param_1)

{
  undefined4 *in_ECX;
  
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0;
  FUN_0040114e(param_1);
  in_ECX[3] = *(undefined4 *)(param_1 + 0xc);
  return;
}



// ==== 0x40126c ====

void FUN_0040126c(undefined4 param_1)

{
  undefined4 *puVar1;
  int in_ECX;
  
  FUN_00401111(1);
  puVar1 = (undefined4 *)FUN_00401000(0);
  *puVar1 = param_1;
  *(undefined4 *)(in_ECX + 0xc) = 1;
  return;
}



// ==== 0x401290 ====

void FUN_00401290(uint param_1,int param_2)

{
  uint *puVar1;
  int *in_ECX;
  
  if (param_2 == 0) {
    if (param_1 < (uint)((in_ECX[1] - *in_ECX >> 2) << 5)) {
      puVar1 = (uint *)FUN_00401000((int)param_1 / 0x20);
      *puVar1 = *puVar1 & ~(1 << ((byte)((int)param_1 % 0x20) & 0x1f));
    }
  }
  else if (param_2 == 1) {
    FUN_004011d1((int)param_1 / 0x20 + 1);
    puVar1 = (uint *)FUN_00401000((int)param_1 / 0x20);
    *puVar1 = *puVar1 | 1 << ((byte)((int)param_1 % 0x20) & 0x1f);
  }
  return;
}



// ==== 0x401301 ====

void FUN_00401301(void)

{
  int *piVar1;
  int *in_ECX;
  uint uVar2;
  undefined4 local_8;
  
  uVar2 = 0xffffffff;
  do {
    uVar2 = uVar2 + 1;
    if ((uint)(in_ECX[1] - *in_ECX >> 2) <= uVar2) {
      local_8 = 1;
      FUN_00401193(&local_8);
      return;
    }
    piVar1 = (int *)FUN_00401000(uVar2);
    *piVar1 = *piVar1 + 1;
    piVar1 = (int *)FUN_00401000(uVar2);
  } while (*piVar1 == 0);
  return;
}



// ==== 0x401348 ====

void FUN_00401348(void)

{
  FUN_0040106c();
  FUN_00401193(&stack0x00000004);
  return;
}



// ==== 0x401360 ====

void FUN_00401360(void)

{
  undefined4 *in_ECX;
  void *local_14;
  
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0;
  FUN_00401206(0);
  if (local_14 != (void *)0x0) {
    _free(local_14);
  }
  return;
}



// ==== 0x401391 ====

void FUN_00401391(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  int *in_ECX;
  uint uVar7;
  int iVar8;
  
  if (in_ECX[3] == param_1[3]) {
    uVar3 = param_1[1] - *param_1 >> 2;
    uVar7 = in_ECX[1] - *in_ECX >> 2;
    if (uVar3 < uVar7) {
      uVar3 = uVar7;
    }
    FUN_004011d1(uVar3 + 1);
    if ((param_1[1] - *param_1 & 0xfffffffcU) != 0) {
      puVar4 = (uint *)FUN_00401000(0);
      puVar5 = (uint *)FUN_00401000(0);
      iVar6 = param_1[1] - *param_1 >> 2;
      iVar8 = (in_ECX[1] - *in_ECX >> 2) - iVar6;
      if (iVar6 != 0) {
        uVar3 = 0;
        do {
          uVar2 = *puVar4;
          uVar7 = *puVar5;
          *puVar5 = *puVar5 - uVar3;
          uVar1 = *puVar5;
          *puVar5 = *puVar5 - uVar2;
          uVar3 = (uint)(uVar7 < uVar3) + (uint)(uVar1 < uVar2);
          puVar5 = puVar5 + 1;
          puVar4 = puVar4 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        do {
          uVar7 = *puVar5;
          *puVar5 = *puVar5 - uVar3;
          uVar3 = (uint)(uVar7 < uVar3);
          puVar5 = puVar5 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        if (uVar3 != 0) {
          in_ECX[3] = -in_ECX[3];
          FUN_004010ac();
          FUN_00401301(0);
        }
      }
      FUN_0040106c();
    }
  }
  else {
    in_ECX[3] = -in_ECX[3];
    FUN_00401482(param_1);
    in_ECX[3] = -in_ECX[3];
  }
  return;
}



// ==== 0x401482 ====

void FUN_00401482(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  int *in_ECX;
  uint uVar7;
  int iVar8;
  
  FUN_00404752(param_1 != in_ECX);
  if (in_ECX[3] == param_1[3]) {
    uVar3 = param_1[1] - *param_1 >> 2;
    uVar7 = in_ECX[1] - *in_ECX >> 2;
    if (uVar3 < uVar7) {
      uVar3 = uVar7;
    }
    FUN_004011d1(uVar3 + 1);
    if ((param_1[1] - *param_1 & 0xfffffffcU) != 0) {
      puVar4 = (uint *)FUN_00401000(0);
      puVar5 = (uint *)FUN_00401000(0);
      iVar6 = param_1[1] - *param_1 >> 2;
      iVar8 = (in_ECX[1] - *in_ECX >> 2) - iVar6;
      if (iVar6 != 0) {
        uVar3 = 0;
        do {
          uVar2 = *puVar4;
          uVar7 = *puVar5;
          *puVar5 = *puVar5 + uVar3;
          uVar1 = *puVar5;
          *puVar5 = *puVar5 + uVar2;
          uVar3 = (uint)CARRY4(uVar7,uVar3) + (uint)CARRY4(uVar1,uVar2);
          puVar5 = puVar5 + 1;
          puVar4 = puVar4 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        do {
          uVar7 = *puVar5;
          *puVar5 = *puVar5 + uVar3;
          uVar3 = (uint)CARRY4(uVar7,uVar3);
          puVar5 = puVar5 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      FUN_0040106c();
    }
  }
  else {
    in_ECX[3] = -in_ECX[3];
    FUN_00401391(param_1);
    in_ECX[3] = -in_ECX[3];
  }
  return;
}



// ==== 0x40155e ====

undefined4 FUN_0040155e(undefined4 param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  int *in_ECX;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  void *local_2c [3];
  int local_20;
  int local_1c;
  uint *local_18;
  uint *local_14;
  uint local_10;
  int *local_c;
  uint local_8;
  
  local_1c = 0;
  local_c = in_ECX;
  FUN_00401360();
  FUN_004011d1((param_2[1] - *param_2 >> 2) + (in_ECX[1] - *in_ECX >> 2));
  local_8 = 0;
  if (in_ECX[1] - *in_ECX >> 2 != 0) {
    do {
      local_1c = param_2[1] - *param_2 >> 2;
      if (local_1c == 0) {
        FUN_00401206(0);
        goto LAB_0040165d;
      }
      local_18 = (uint *)FUN_00401000(local_8);
      local_14 = (uint *)FUN_00401000(0);
      puVar4 = (uint *)FUN_00401000(local_8);
      local_10 = *puVar4;
      iVar6 = local_1c;
      puVar4 = local_14;
      puVar8 = local_18;
      do {
        uVar7 = (uint)((ulonglong)*puVar4 * (ulonglong)local_10 >> 0x20);
        uVar5 = (uint)((ulonglong)*puVar4 * (ulonglong)local_10);
        uVar2 = *puVar8;
        *puVar8 = *puVar8 + uVar5;
        puVar9 = puVar8 + 1;
        uVar5 = (uint)CARRY4(uVar2,uVar5);
        uVar2 = *puVar9;
        uVar3 = *puVar9 + uVar7;
        *puVar9 = uVar3 + uVar5;
        puVar9 = puVar8;
        if (CARRY4(uVar2,uVar7) || CARRY4(uVar3,uVar5)) {
          do {
            puVar1 = puVar9 + 2;
            uVar2 = *puVar1;
            *puVar1 = *puVar1 + 1;
            puVar9 = puVar9 + 1;
          } while (0xfffffffe < uVar2);
        }
        puVar8 = puVar8 + 1;
        puVar4 = puVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      local_8 = local_8 + 1;
      in_ECX = local_c;
    } while (local_8 < (uint)(local_c[1] - *local_c >> 2));
  }
  local_20 = param_2[3] * in_ECX[3];
  FUN_0040106c();
  if (DAT_004533ac != 0) {
    DAT_004533ac = 1;
  }
  FUN_00401247(local_2c);
LAB_0040165d:
  if (local_2c[0] != (void *)0x0) {
    _free(local_2c[0]);
  }
  return param_1;
}



// ==== 0x401680 ====

undefined4 FUN_00401680(undefined4 param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint *puVar4;
  uint *puVar5;
  int *in_ECX;
  void *local_1c [3];
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  FUN_00401360();
  FUN_004011d1((in_ECX[1] - *in_ECX >> 2) * 0x20 + (int)(param_2 + 0x1f) / 0x20);
  local_c = (int)param_2 / 0x20;
  local_8 = (int)param_2 % 0x20;
  param_2 = 0;
  if (in_ECX[1] - *in_ECX >> 2 != 0) {
    do {
      iVar1 = param_2 + local_c;
      piVar2 = (int *)FUN_00401000(iVar1);
      piVar3 = (int *)FUN_00401000(param_2);
      *piVar2 = *piVar2 + (*piVar3 << ((byte)local_8 & 0x1f));
      if (local_8 != 0) {
        puVar4 = (uint *)FUN_00401000(param_2);
        puVar5 = (uint *)FUN_00401000(iVar1 + 1);
        *puVar5 = *puVar4 >> (0x20U - (char)local_8 & 0x1f);
      }
      param_2 = param_2 + 1;
    } while (param_2 < (uint)(in_ECX[1] - *in_ECX >> 2));
  }
  FUN_0040106c();
  local_10 = in_ECX[3];
  FUN_00401247(local_1c);
  if (local_1c[0] != (void *)0x0) {
    _free(local_1c[0]);
  }
  return param_1;
}



// ==== 0x401764 ====

undefined4 FUN_00401764(void)

{
  undefined4 extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  FUN_00401247(extraout_ECX);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00401482(*(undefined4 *)(unaff_EBP + 0xc));
  FUN_00401247(unaff_EBP + -0x20);
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x4017b9 ====

undefined4 FUN_004017b9(void)

{
  undefined4 extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  FUN_00401247(extraout_ECX);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00401391(*(undefined4 *)(unaff_EBP + 0xc));
  FUN_00401247(unaff_EBP + -0x20);
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x40180e ====

undefined4 * FUN_0040180e(void)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *extraout_ECX;
  int unaff_EBP;
  int iVar4;
  
  FUN_0041cc3c();
  *(undefined4 **)(unaff_EBP + -0x10) = extraout_ECX;
  *extraout_ECX = 0;
  extraout_ECX[1] = 0;
  extraout_ECX[2] = 0;
  iVar4 = *(int *)(unaff_EBP + 0xc);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if (iVar4 == 0) {
    for (pcVar1 = *(char **)(unaff_EBP + 8); *pcVar1 != '\0'; pcVar1 = pcVar1 + 1) {
      iVar4 = iVar4 + 1;
    }
  }
  if (*(int *)(unaff_EBP + 0x10) == 0) {
    *(undefined1 **)(unaff_EBP + 0x10) = &DAT_0042b24c;
  }
  FUN_0040126c(0);
  FUN_00401206(1);
  *(int *)(unaff_EBP + 8) = *(int *)(unaff_EBP + 8) + iVar4;
  *(undefined1 *)(unaff_EBP + -4) = 1;
  if (0 < iVar4) {
    do {
      *(int *)(unaff_EBP + 8) = *(int *)(unaff_EBP + 8) + -1;
      iVar2 = 0;
      if (0 < *(int *)(unaff_EBP + 0x14)) {
        do {
          if (*(char *)(iVar2 + *(int *)(unaff_EBP + 0x10)) == **(char **)(unaff_EBP + 8)) {
            uVar3 = FUN_00401206(iVar2);
            uVar3 = FUN_0040155e(unaff_EBP + -0x30,uVar3);
            *(undefined1 *)(unaff_EBP + -4) = 3;
            FUN_00401482(uVar3);
            if (*(int *)(unaff_EBP + -0x30) != 0) {
              _free(*(void **)(unaff_EBP + -0x30));
              *(undefined4 *)(unaff_EBP + -0x30) = 0;
            }
            *(undefined1 *)(unaff_EBP + -4) = 1;
            if (*(int *)(unaff_EBP + -0x40) != 0) {
              _free(*(void **)(unaff_EBP + -0x40));
              *(undefined4 *)(unaff_EBP + -0x40) = 0;
            }
            uVar3 = FUN_00401206(*(undefined4 *)(unaff_EBP + 0x14));
            uVar3 = FUN_0040155e(unaff_EBP + -0x50,uVar3);
            FUN_004011b6(uVar3);
            if (*(int *)(unaff_EBP + -0x50) != 0) {
              _free(*(void **)(unaff_EBP + -0x50));
              *(undefined4 *)(unaff_EBP + -0x50) = 0;
            }
            if (*(int *)(unaff_EBP + -0x60) != 0) {
              _free(*(void **)(unaff_EBP + -0x60));
              *(undefined4 *)(unaff_EBP + -0x60) = 0;
            }
            break;
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(unaff_EBP + 0x14));
      }
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return extraout_ECX;
}



// ==== 0x401948 ====

char FUN_00401948(undefined4 param_1)

{
  void *local_14;
  int local_10;
  
  FUN_004017b9(&local_14,param_1);
  if (local_14 != (void *)0x0) {
    _free(local_14);
  }
  return '\x01' - ((local_10 - (int)local_14 & 0xfffffffcU) != 0);
}



// ==== 0x401980 ====

bool FUN_00401980(void)

{
  undefined4 in_ECX;
  void *local_14 [3];
  int local_8;
  
  FUN_004017b9(local_14,in_ECX);
  if (local_14[0] != (void *)0x0) {
    _free(local_14[0]);
  }
  return local_8 == -1;
}



// ==== 0x4019b1 ====

void FUN_004019b1(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  int extraout_ECX;
  int *extraout_ECX_00;
  undefined1 *puVar7;
  int unaff_EBP;
  
  FUN_0041cc3c();
  piVar1 = *(int **)(unaff_EBP + 8);
  puVar7 = (undefined1 *)0x0;
  if ((*(int **)(unaff_EBP + 0x10) == piVar1) ||
     (*(int *)(unaff_EBP + 0x10) == *(int *)(unaff_EBP + 0xc))) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  FUN_00404752(uVar6);
  if ((piVar1[3] == 1) && (*(int *)(extraout_ECX + 0xc) == 1)) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  FUN_00404752(uVar6);
  iVar5 = extraout_ECX_00[1] - *extraout_ECX_00 >> 2;
  if (iVar5 == 0) {
    do {
      puVar7 = puVar7 + 1;
      *puVar7 = 0x7f;
    } while( true );
  }
  iVar2 = piVar1[1];
  iVar3 = *piVar1;
  FUN_0040126c(0);
  iVar5 = (((iVar2 - iVar3 >> 2) - iVar5) + 1) * 0x20 + -1;
  FUN_00401206(0);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  while (-1 < iVar5) {
    FUN_00401290(iVar5,1);
    FUN_00401247(unaff_EBP + -0x1c);
    uVar6 = FUN_00401680(unaff_EBP + -0x3c,iVar5);
    *(undefined1 *)(unaff_EBP + -4) = 2;
    FUN_00401482(uVar6);
    *(undefined1 *)(unaff_EBP + -4) = 1;
    if (*(int *)(unaff_EBP + -0x3c) != 0) {
      _free(*(void **)(unaff_EBP + -0x3c));
      *(undefined4 *)(unaff_EBP + -0x3c) = 0;
    }
    cVar4 = FUN_00401980(piVar1);
    if (cVar4 != '\0') {
      FUN_00401290(iVar5,0);
      FUN_004011b6(unaff_EBP + -0x2c);
    }
    iVar5 = iVar5 + -1;
    *(undefined1 *)(unaff_EBP + -4) = 0;
    if (*(int *)(unaff_EBP + -0x2c) != 0) {
      _free(*(void **)(unaff_EBP + -0x2c));
      *(undefined4 *)(unaff_EBP + -0x2c) = 0;
    }
  }
  FUN_0040106c();
  if (*(int *)(unaff_EBP + -0x1c) != 0) {
    _free(*(void **)(unaff_EBP + -0x1c));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



// ==== 0x401adb ====

undefined4 FUN_00401adb(void)

{
  undefined4 uVar1;
  undefined4 extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  FUN_00401360();
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_004019b1(extraout_ECX,*(undefined4 *)(unaff_EBP + 0xc),unaff_EBP + -0x20);
  uVar1 = FUN_0040155e(unaff_EBP + -0x30,*(undefined4 *)(unaff_EBP + 0xc));
  *(undefined1 *)(unaff_EBP + -4) = 1;
  FUN_004017b9(*(undefined4 *)(unaff_EBP + 8),uVar1);
  if (*(int *)(unaff_EBP + -0x30) != 0) {
    _free(*(void **)(unaff_EBP + -0x30));
    *(undefined4 *)(unaff_EBP + -0x30) = 0;
  }
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x401b5c ====

undefined4 FUN_00401b5c(void)

{
  undefined4 extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  FUN_00401360();
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_004019b1(extraout_ECX,*(undefined4 *)(unaff_EBP + 0xc),unaff_EBP + -0x20);
  FUN_00401247(unaff_EBP + -0x20);
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x401bb9 ====

uint FUN_00401bb9(void)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  int unaff_EBP;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = extraout_ECX;
  _eh_vector_constructor_iterator_
            ((void *)(unaff_EBP + -0x230),0x10,0x20,FUN_00401360,thunk_FUN_00404f9c);
  uVar4 = 0;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_004011b6(*(undefined4 *)(unaff_EBP + 8));
  cVar2 = FUN_00401980(*(undefined4 *)(unaff_EBP + -0x10));
  if (cVar2 == '\0') {
    iVar5 = unaff_EBP + -0x230;
    iVar1 = 0;
    do {
      iVar6 = iVar1;
      uVar3 = FUN_0040155e(unaff_EBP + -0x20,iVar5);
      FUN_004011b6(uVar3);
      if (*(int *)(unaff_EBP + -0x20) != 0) {
        _free(*(void **)(unaff_EBP + -0x20));
        *(undefined4 *)(unaff_EBP + -0x20) = 0;
      }
      iVar5 = iVar5 + 0x10;
      cVar2 = FUN_00401980(*(undefined4 *)(unaff_EBP + -0x10));
      iVar1 = iVar6 + 1;
    } while (cVar2 == '\0');
    iVar5 = unaff_EBP + -0x230 + iVar6 * 0x10;
    FUN_00401247(iVar5);
    uVar4 = 1 << ((byte)iVar6 & 0x1f);
    while (0 < iVar6) {
      iVar5 = iVar5 + -0x10;
      iVar6 = iVar6 + -1;
      FUN_0040155e(unaff_EBP + -0x30,iVar5);
      *(undefined1 *)(unaff_EBP + -4) = 2;
      cVar2 = FUN_00401980(*(undefined4 *)(unaff_EBP + -0x10));
      if (cVar2 == '\0') {
        uVar4 = uVar4 | 1 << ((byte)iVar6 & 0x1f);
        FUN_004011b6(unaff_EBP + -0x30);
      }
      if (*(int *)(unaff_EBP + -0x30) != 0) {
        _free(*(void **)(unaff_EBP + -0x30));
        *(undefined4 *)(unaff_EBP + -0x30) = 0;
      }
    }
    if (*(int *)(unaff_EBP + -0x20) != 0) {
      _free(*(void **)(unaff_EBP + -0x20));
    }
  }
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  _eh_vector_destructor_iterator_((void *)(unaff_EBP + -0x230),0x10,0x20,thunk_FUN_00404f9c);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return uVar4;
}



// ==== 0x401cff ====

undefined4 FUN_00401cff(void)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  FUN_00401360();
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_0040126c(1);
  FUN_00401247(extraout_ECX);
  FUN_00401206(1);
  uVar1 = *(uint *)(unaff_EBP + 0xc);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  do {
    if ((uVar1 & 1 << ((byte)*(undefined4 *)(unaff_EBP + -0x10) & 0x1f)) != 0) {
      uVar3 = FUN_0040155e(unaff_EBP + -0x60,unaff_EBP + -0x30);
      FUN_004011b6(uVar3);
      if (*(int *)(unaff_EBP + -0x60) != 0) {
        _free(*(void **)(unaff_EBP + -0x60));
        *(undefined4 *)(unaff_EBP + -0x60) = 0;
      }
    }
    *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 1;
    uVar3 = FUN_00401764(unaff_EBP + -0x70,unaff_EBP + -0x20);
    FUN_004011b6(uVar3);
    if (*(int *)(unaff_EBP + -0x70) != 0) {
      _free(*(void **)(unaff_EBP + -0x70));
      *(undefined4 *)(unaff_EBP + -0x70) = 0;
    }
    uVar3 = FUN_0040155e(unaff_EBP + -0x80,unaff_EBP + -0x30);
    FUN_004011b6(uVar3);
    if (*(int *)(unaff_EBP + -0x80) != 0) {
      _free(*(void **)(unaff_EBP + -0x80));
      *(undefined4 *)(unaff_EBP + -0x80) = 0;
    }
    FUN_00401206(uVar1);
    *(undefined1 *)(unaff_EBP + -4) = 3;
    cVar2 = FUN_00401980(unaff_EBP + -0x50);
    *(undefined1 *)(unaff_EBP + -4) = 2;
    if (*(int *)(unaff_EBP + -0x50) != 0) {
      _free(*(void **)(unaff_EBP + -0x50));
      *(undefined4 *)(unaff_EBP + -0x50) = 0;
    }
  } while (cVar2 == '\0');
  FUN_00401247(unaff_EBP + -0x40);
  if (*(int *)(unaff_EBP + -0x20) != 0) {
    _free(*(void **)(unaff_EBP + -0x20));
    *(undefined4 *)(unaff_EBP + -0x20) = 0;
  }
  if (*(int *)(unaff_EBP + -0x30) != 0) {
    _free(*(void **)(unaff_EBP + -0x30));
  }
  if (*(int *)(unaff_EBP + -0x40) != 0) {
    _free(*(void **)(unaff_EBP + -0x40));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x401e60 ====

void FUN_00401e60(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int unaff_EBP;
  
  FUN_0041cc3c();
  FUN_0040126c(1);
  FUN_00401247(*(undefined4 *)(unaff_EBP + 8));
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00401206(1);
  *(undefined1 *)(unaff_EBP + -4) = 1;
  iVar4 = 0;
  do {
    iVar2 = FUN_004010d6(iVar4);
    if (iVar2 != 0) {
      FUN_0040155e(unaff_EBP + -0x4c,unaff_EBP + -0x2c);
      *(undefined1 *)(unaff_EBP + -4) = 2;
      uVar3 = FUN_00401adb(unaff_EBP + -0x3c,*(undefined4 *)(unaff_EBP + 0x10));
      FUN_004011b6(uVar3);
      if (*(int *)(unaff_EBP + -0x3c) != 0) {
        _free(*(void **)(unaff_EBP + -0x3c));
        *(undefined4 *)(unaff_EBP + -0x3c) = 0;
      }
      *(undefined1 *)(unaff_EBP + -4) = 1;
      if (*(int *)(unaff_EBP + -0x4c) != 0) {
        _free(*(void **)(unaff_EBP + -0x4c));
        *(undefined4 *)(unaff_EBP + -0x4c) = 0;
      }
    }
    iVar4 = iVar4 + 1;
    uVar3 = FUN_00401764(unaff_EBP + -0x5c,unaff_EBP + -0x1c);
    FUN_004011b6(uVar3);
    if (*(int *)(unaff_EBP + -0x5c) != 0) {
      _free(*(void **)(unaff_EBP + -0x5c));
      *(undefined4 *)(unaff_EBP + -0x5c) = 0;
    }
    FUN_0040155e(unaff_EBP + -0x7c,unaff_EBP + -0x2c);
    *(undefined1 *)(unaff_EBP + -4) = 3;
    uVar3 = FUN_00401adb(unaff_EBP + -0x6c,*(undefined4 *)(unaff_EBP + 0x10));
    FUN_004011b6(uVar3);
    if (*(int *)(unaff_EBP + -0x6c) != 0) {
      _free(*(void **)(unaff_EBP + -0x6c));
      *(undefined4 *)(unaff_EBP + -0x6c) = 0;
    }
    *(undefined1 *)(unaff_EBP + -4) = 1;
    if (*(int *)(unaff_EBP + -0x7c) != 0) {
      _free(*(void **)(unaff_EBP + -0x7c));
      *(undefined4 *)(unaff_EBP + -0x7c) = 0;
    }
    cVar1 = FUN_00401980(*(undefined4 *)(unaff_EBP + 0xc));
  } while (cVar1 == '\0');
  if (*(int *)(unaff_EBP + -0x1c) != 0) {
    _free(*(void **)(unaff_EBP + -0x1c));
    *(undefined4 *)(unaff_EBP + -0x1c) = 0;
  }
  if (*(int *)(unaff_EBP + -0x2c) != 0) {
    _free(*(void **)(unaff_EBP + -0x2c));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



// ==== 0x401fb4 ====

void FUN_00401fb4(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 extraout_ECX;
  int unaff_EBP;
  undefined1 *puVar5;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x10) = extraout_ECX;
  if (*(int *)(unaff_EBP + 0x10) == 0) {
    *(undefined1 **)(unaff_EBP + 0x10) = &DAT_0042b24c;
  }
  puVar5 = *(undefined1 **)(unaff_EBP + 8);
  *(undefined1 **)(unaff_EBP + 0xc) = puVar5 + *(int *)(unaff_EBP + 0xc) + -1;
  FUN_00401206(*(undefined4 *)(unaff_EBP + 0x14));
  *(undefined4 *)(unaff_EBP + -4) = 0;
  iVar1 = FUN_00401bb9(unaff_EBP + -0x30);
  if (*(int *)(unaff_EBP + -0x30) != 0) {
    _free(*(void **)(unaff_EBP + -0x30));
  }
  if ((*(int *)(unaff_EBP + 0x18) != 0) && (iVar2 = *(int *)(unaff_EBP + 0x18) + -1, iVar1 < iVar2))
  {
    iVar1 = iVar2;
  }
  FUN_00401206(*(undefined4 *)(unaff_EBP + 0x14));
  *(undefined4 *)(unaff_EBP + -4) = 1;
  FUN_00401cff(unaff_EBP + -0x30,iVar1);
  if (*(int *)(unaff_EBP + -0x70) != 0) {
    _free(*(void **)(unaff_EBP + -0x70));
  }
  FUN_00401247(*(undefined4 *)(unaff_EBP + -0x10));
  *(undefined1 *)(unaff_EBP + -4) = 4;
  *(undefined4 *)(unaff_EBP + 8) = 0;
  if (-1 < iVar1) {
    iVar1 = iVar1 + 1;
    do {
      FUN_00401b5c(unaff_EBP + -0x20,unaff_EBP + -0x30);
      iVar2 = 0;
      if ((*(int *)(unaff_EBP + -0x1c) - *(int *)(unaff_EBP + -0x20) & 0xfffffffcU) != 0) {
        piVar3 = (int *)FUN_00401000(0);
        iVar2 = *piVar3;
      }
      if (puVar5 < *(undefined1 **)(unaff_EBP + 0xc)) {
        if ((*(int *)(unaff_EBP + 8) == 5) && (*(int *)(unaff_EBP + 0x18) != 0)) {
          *puVar5 = 0x2d;
          *(undefined4 *)(unaff_EBP + 8) = 0;
          puVar5 = puVar5 + 1;
        }
        *puVar5 = *(undefined1 *)(iVar2 + *(int *)(unaff_EBP + 0x10));
        puVar5 = puVar5 + 1;
        *(int *)(unaff_EBP + 8) = *(int *)(unaff_EBP + 8) + 1;
      }
      uVar4 = FUN_0040155e(unaff_EBP + -0x50,unaff_EBP + -0x20);
      *(undefined1 *)(unaff_EBP + -4) = 6;
      FUN_00401391(uVar4);
      if (*(int *)(unaff_EBP + -0x50) != 0) {
        _free(*(void **)(unaff_EBP + -0x50));
        *(undefined4 *)(unaff_EBP + -0x50) = 0;
      }
      uVar4 = FUN_00401206(*(undefined4 *)(unaff_EBP + 0x14));
      *(undefined1 *)(unaff_EBP + -4) = 7;
      uVar4 = FUN_00401b5c(unaff_EBP + -0x60,uVar4);
      FUN_004011b6(uVar4);
      if (*(int *)(unaff_EBP + -0x60) != 0) {
        _free(*(void **)(unaff_EBP + -0x60));
        *(undefined4 *)(unaff_EBP + -0x60) = 0;
      }
      if (*(int *)(unaff_EBP + -0x70) != 0) {
        _free(*(void **)(unaff_EBP + -0x70));
        *(undefined4 *)(unaff_EBP + -0x70) = 0;
      }
      *(undefined1 *)(unaff_EBP + -4) = 4;
      if (*(int *)(unaff_EBP + -0x20) != 0) {
        _free(*(void **)(unaff_EBP + -0x20));
        *(undefined4 *)(unaff_EBP + -0x20) = 0;
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  iVar1 = *(int *)(unaff_EBP + -0x40);
  *puVar5 = 0;
  if (iVar1 != 0) {
    _free(*(void **)(unaff_EBP + -0x40));
    *(undefined4 *)(unaff_EBP + -0x40) = 0;
  }
  if (*(int *)(unaff_EBP + -0x30) != 0) {
    _free(*(void **)(unaff_EBP + -0x30));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



// ==== 0x402172 ====

void FUN_00402172(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *in_ECX;
  
  fVar1 = param_2[1];
  fVar2 = in_ECX[1];
  fVar3 = param_2[2];
  fVar4 = in_ECX[2];
  *param_1 = *param_2 + *in_ECX;
  param_1[1] = fVar1 + fVar2;
  param_1[2] = fVar3 + fVar4;
  return;
}



// ==== 0x4021a7 ====

void FUN_004021a7(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *in_ECX;
  
  fVar1 = in_ECX[1];
  fVar2 = param_2[1];
  fVar3 = in_ECX[2];
  fVar4 = param_2[2];
  *param_1 = *in_ECX - *param_2;
  param_1[1] = fVar1 - fVar2;
  param_1[2] = fVar3 - fVar4;
  return;
}



// ==== 0x4021dc ====

void FUN_004021dc(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *in_ECX;
  
  fVar1 = *param_2;
  fVar2 = in_ECX[2];
  fVar3 = *in_ECX;
  fVar4 = param_2[2];
  fVar5 = param_2[1];
  fVar6 = *in_ECX;
  fVar7 = in_ECX[1];
  fVar8 = *param_2;
  *param_1 = in_ECX[1] * param_2[2] - param_2[1] * in_ECX[2];
  param_1[1] = fVar1 * fVar2 - fVar3 * fVar4;
  param_1[2] = fVar5 * fVar6 - fVar7 * fVar8;
  return;
}



// ==== 0x402227 ====

void FUN_00402227(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *in_ECX;
  
  fVar1 = in_ECX[1];
  fVar2 = *param_2;
  fVar3 = in_ECX[2];
  fVar4 = *param_2;
  *param_1 = *param_2 * *in_ECX;
  param_1[1] = fVar1 * fVar2;
  param_1[2] = fVar3 * fVar4;
  return;
}



// ==== 0x40225a ====

void FUN_0040225a(float *param_1)

{
  float *in_ECX;
  
  *in_ECX = *param_1 + *in_ECX;
  in_ECX[1] = param_1[1] + in_ECX[1];
  in_ECX[2] = param_1[2] + in_ECX[2];
  return;
}



// ==== 0x402279 ====

void FUN_00402279(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  return;
}



// ==== 0x4022a2 ====

void FUN_004022a2(void)

{
  return;
}



// ==== 0x4022c1 ====

void FUN_004022c1(void)

{
  float *in_ECX;
  float10 fVar1;
  
  fVar1 = (float10)FUN_004022a2();
  fVar1 = (float10)FUN_0041d134((double)fVar1);
  if (fVar1 != (float10)0.0) {
    fVar1 = (float10)1 / fVar1;
  }
  *in_ECX = (float)(fVar1 * (float10)*in_ECX);
  in_ECX[1] = (float)(fVar1 * (float10)in_ECX[1]);
  in_ECX[2] = (float)(fVar1 * (float10)in_ECX[2]);
  return;
}



// ==== 0x402302 ====

void FUN_00402302(float *param_1)

{
  float fVar1;
  float fVar2;
  float *in_ECX;
  float10 fVar3;
  
  fVar3 = (float10)FUN_004022a2();
  fVar3 = (float10)FUN_0041d134((double)fVar3);
  if (fVar3 != (float10)0.0) {
    fVar3 = (float10)1 / fVar3;
  }
  fVar1 = in_ECX[1];
  fVar2 = in_ECX[2];
  *param_1 = (float)((float10)*in_ECX * fVar3);
  param_1[1] = (float)((float10)fVar1 * fVar3);
  param_1[2] = (float)((float10)fVar2 * fVar3);
  return;
}



// ==== 0x402363 ====

void FUN_00402363(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float *in_ECX;
  
  fVar1 = in_ECX[4];
  fVar2 = param_2[1];
  fVar3 = in_ECX[3];
  fVar4 = *param_2;
  fVar5 = in_ECX[5];
  fVar6 = param_2[2];
  fVar7 = in_ECX[7];
  fVar8 = param_2[1];
  fVar9 = in_ECX[6];
  fVar10 = *param_2;
  fVar11 = in_ECX[8];
  fVar12 = param_2[2];
  *param_1 = *param_2 * *in_ECX + in_ECX[2] * param_2[2] + in_ECX[1] * param_2[1];
  param_1[1] = fVar5 * fVar6 + fVar3 * fVar4 + fVar1 * fVar2;
  param_1[2] = fVar11 * fVar12 + fVar9 * fVar10 + fVar7 * fVar8;
  return;
}



// ==== 0x4023c6 ====

void FUN_004023c6(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float *in_ECX;
  
  fVar1 = param_2[7];
  fVar2 = in_ECX[2];
  fVar3 = param_2[1];
  fVar4 = *in_ECX;
  fVar5 = param_2[4];
  fVar6 = in_ECX[1];
  fVar7 = param_2[8];
  fVar8 = in_ECX[2];
  fVar9 = param_2[2];
  fVar10 = *in_ECX;
  fVar11 = param_2[5];
  fVar12 = in_ECX[1];
  *param_1 = *param_2 * *in_ECX + param_2[3] * in_ECX[1] + param_2[6] * in_ECX[2];
  param_1[1] = fVar5 * fVar6 + fVar3 * fVar4 + fVar1 * fVar2;
  param_1[2] = fVar11 * fVar12 + fVar9 * fVar10 + fVar7 * fVar8;
  return;
}



// ==== 0x402429 ====

void FUN_00402429(void)

{
  undefined4 *in_ECX;
  
  in_ECX[8] = 0x3f800000;
  in_ECX[4] = 0x3f800000;
  *in_ECX = 0x3f800000;
  in_ECX[7] = 0;
  in_ECX[6] = 0;
  in_ECX[5] = 0;
  in_ECX[3] = 0;
  in_ECX[2] = 0;
  in_ECX[1] = 0;
  return;
}



// ==== 0x402456 ====

void FUN_00402456(float param_1)

{
  float fVar1;
  float *in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = in_ECX[6];
  in_ECX[6] = (float)(fVar3 * (float10)*in_ECX + fVar4 * (float10)in_ECX[6]);
  *in_ECX = (float)(fVar4 * (float10)*in_ECX - fVar3 * (float10)fVar1);
  fVar1 = in_ECX[7];
  in_ECX[7] = (float)(fVar4 * (float10)in_ECX[7] + fVar3 * (float10)in_ECX[1]);
  in_ECX[1] = (float)(fVar4 * (float10)in_ECX[1] - fVar3 * (float10)fVar1);
  fVar1 = in_ECX[8];
  in_ECX[8] = (float)((float10)(float)fVar2 * (float10)in_ECX[8] + fVar3 * (float10)in_ECX[2]);
  in_ECX[2] = (float)(fVar4 * (float10)in_ECX[2] - fVar3 * (float10)fVar1);
  return;
}



// ==== 0x4024da ====

void FUN_004024da(float param_1)

{
  float fVar1;
  int in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = *(float *)(in_ECX + 0x18);
  *(float *)(in_ECX + 0x18) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x18) -
              fVar3 * (float10)*(float *)(in_ECX + 0xc));
  *(float *)(in_ECX + 0xc) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0xc) + fVar3 * (float10)fVar1);
  fVar1 = *(float *)(in_ECX + 0x1c);
  *(float *)(in_ECX + 0x1c) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x1c) -
              fVar3 * (float10)*(float *)(in_ECX + 0x10));
  *(float *)(in_ECX + 0x10) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x10) + fVar3 * (float10)fVar1);
  fVar1 = *(float *)(in_ECX + 0x20);
  *(float *)(in_ECX + 0x20) =
       (float)((float10)(float)fVar2 * (float10)*(float *)(in_ECX + 0x20) -
              fVar3 * (float10)*(float *)(in_ECX + 0x14));
  *(float *)(in_ECX + 0x14) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x14) + fVar3 * (float10)fVar1);
  return;
}



// ==== 0x402565 ====

void FUN_00402565(float param_1)

{
  float fVar1;
  float *in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = in_ECX[3];
  in_ECX[3] = (float)(fVar4 * (float10)in_ECX[3] - fVar3 * (float10)*in_ECX);
  *in_ECX = (float)(fVar4 * (float10)*in_ECX + fVar3 * (float10)fVar1);
  fVar1 = in_ECX[4];
  in_ECX[4] = (float)(fVar4 * (float10)in_ECX[4] - fVar3 * (float10)in_ECX[1]);
  in_ECX[1] = (float)(fVar4 * (float10)in_ECX[1] + fVar3 * (float10)fVar1);
  fVar1 = in_ECX[5];
  in_ECX[5] = (float)((float10)(float)fVar2 * (float10)in_ECX[5] - fVar3 * (float10)in_ECX[2]);
  in_ECX[2] = (float)(fVar4 * (float10)in_ECX[2] + fVar3 * (float10)fVar1);
  return;
}



// ==== 0x4025ed ====

void FUN_004025ed(float param_1)

{
  float fVar1;
  float *in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = in_ECX[2];
  in_ECX[2] = (float)(fVar3 * (float10)*in_ECX + fVar4 * (float10)in_ECX[2]);
  *in_ECX = (float)(fVar4 * (float10)*in_ECX - fVar3 * (float10)fVar1);
  fVar1 = in_ECX[5];
  in_ECX[5] = (float)(fVar4 * (float10)in_ECX[5] + fVar3 * (float10)in_ECX[3]);
  in_ECX[3] = (float)(fVar4 * (float10)in_ECX[3] - fVar3 * (float10)fVar1);
  fVar1 = in_ECX[8];
  in_ECX[8] = (float)((float10)(float)fVar2 * (float10)in_ECX[8] + fVar3 * (float10)in_ECX[6]);
  in_ECX[6] = (float)(fVar4 * (float10)in_ECX[6] - fVar3 * (float10)fVar1);
  return;
}



// ==== 0x402671 ====

void FUN_00402671(float param_1)

{
  float fVar1;
  int in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = *(float *)(in_ECX + 8);
  *(float *)(in_ECX + 8) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 8) - fVar3 * (float10)*(float *)(in_ECX + 4));
  *(float *)(in_ECX + 4) = (float)(fVar4 * (float10)*(float *)(in_ECX + 4) + fVar3 * (float10)fVar1)
  ;
  fVar1 = *(float *)(in_ECX + 0x14);
  *(float *)(in_ECX + 0x14) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x14) -
              fVar3 * (float10)*(float *)(in_ECX + 0x10));
  *(float *)(in_ECX + 0x10) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x10) + fVar3 * (float10)fVar1);
  fVar1 = *(float *)(in_ECX + 0x20);
  *(float *)(in_ECX + 0x20) =
       (float)((float10)(float)fVar2 * (float10)*(float *)(in_ECX + 0x20) -
              fVar3 * (float10)*(float *)(in_ECX + 0x1c));
  *(float *)(in_ECX + 0x1c) =
       (float)(fVar4 * (float10)*(float *)(in_ECX + 0x1c) + fVar3 * (float10)fVar1);
  return;
}



// ==== 0x4026fc ====

void FUN_004026fc(float param_1)

{
  float fVar1;
  float *in_ECX;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar2 = (float10)FUN_0041cd94((double)param_1);
  fVar3 = (float10)FUN_0041d084((double)param_1);
  fVar4 = (float10)(float)fVar2;
  fVar1 = in_ECX[1];
  in_ECX[1] = (float)(fVar4 * (float10)in_ECX[1] - fVar3 * (float10)*in_ECX);
  *in_ECX = (float)(fVar4 * (float10)*in_ECX + fVar3 * (float10)fVar1);
  fVar1 = in_ECX[4];
  in_ECX[4] = (float)(fVar4 * (float10)in_ECX[4] - fVar3 * (float10)in_ECX[3]);
  in_ECX[3] = (float)(fVar4 * (float10)in_ECX[3] + fVar3 * (float10)fVar1);
  fVar1 = in_ECX[7];
  in_ECX[7] = (float)((float10)(float)fVar2 * (float10)in_ECX[7] - fVar3 * (float10)in_ECX[6]);
  in_ECX[6] = (float)(fVar4 * (float10)in_ECX[6] + fVar3 * (float10)fVar1);
  return;
}



// ==== 0x402784 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402784(void)

{
  _DAT_00455034 = 0x3fc90fdb;
  DAT_00454ff8 = 0x3f800000;
  _DAT_00455084 = 0x3e20d97c;
  DAT_00454fec = 0xc1f00000;
  DAT_00454ffc = 0;
  DAT_00454ff0 = 0x42200000;
  _DAT_00455000 = 0;
  _DAT_00455004 = 0;
  _DAT_00455008 = 0x3f800000;
  _DAT_0045500c = 0;
  _DAT_00455010 = 0;
  _DAT_00455014 = 0;
  _DAT_00455018 = 0x3f800000;
  DAT_00454ff4 = 0;
  return;
}



// ==== 0x4027fd ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004027fd(undefined4 *param_1,undefined4 param_2)

{
  _DAT_00455058 = 0;
  _DAT_00455084 = 0;
  DAT_00454fec = *param_1;
  DAT_00454ff0 = param_1[1];
  DAT_00454ff4 = param_1[2];
  _DAT_00455034 = param_2;
  return;
}



// ==== 0x402827 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402827(undefined4 *param_1,undefined4 param_2)

{
  FUN_00402784();
  DAT_00454fec = *param_1;
  DAT_00454ff0 = param_1[1];
  DAT_00454ff4 = param_1[2];
  _DAT_00455034 = param_2;
  return;
}



// ==== 0x402846 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00402846(float param_1)

{
  float fVar1;
  FILE *pFVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  bool bVar8;
  float10 fVar9;
  undefined1 local_4c [12];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  char local_28 [32];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  if (DAT_00455088 == 0) {
    pFVar2 = (FILE *)FUN_0041d331("camera.dat",&DAT_0042b29c);
    _fclose(pFVar2);
    DAT_00455088 = 1;
  }
  local_2c = (float)(int)param_1;
  fVar9 = (float10)FUN_0041cf20((double)_DAT_004533b0);
  fVar9 = (float10)FUN_0041ce90((double)(fVar9 * (float10)local_2c));
  local_34 = (float)fVar9;
  fVar9 = (float10)FUN_0041cf20((double)_DAT_004533b8);
  fVar9 = (float10)FUN_0041ce90((double)(fVar9 * (float10)local_2c));
  local_30 = (float)fVar9;
  fVar1 = local_2c * _DAT_004533b4;
  uVar3 = 0;
  param_1 = local_2c * _DAT_004533bc;
  do {
    local_28[uVar3] = (&DAT_00d0f3e0)[(char)(&DAT_004533c0)[uVar3]] != '\0';
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x13);
  if (local_28[0x12] != '\0') {
    param_1 = param_1 * 10.0;
  }
  if (local_28[0] != '\0') {
    _DAT_00455080 = _DAT_00455080 + fVar1;
  }
  if (local_28[1] != '\0') {
    _DAT_00455080 = _DAT_00455080 - fVar1;
  }
  if (local_28[4] != '\0') {
    _DAT_00455060 = _DAT_00455060 - fVar1;
  }
  if (local_28[5] != '\0') {
    _DAT_00455060 = _DAT_00455060 + fVar1;
  }
  if (local_28[3] != '\0') {
    _DAT_0045505c = _DAT_0045505c - fVar1;
  }
  if (local_28[2] != '\0') {
    _DAT_0045505c = _DAT_0045505c + fVar1;
  }
  local_40 = DAT_00c06820;
  local_3c = DAT_00c06824;
  local_38 = DAT_00c06828;
  uVar4 = FUN_004021a7(local_4c,&DAT_00454fec);
  FUN_00402363(&local_40,uVar4);
  _DAT_00455060 = _DAT_00455060 * local_34;
  _DAT_00455080 =
       ((local_3c * (1.0 / local_38) * -0.1 - _DAT_00455080) * 0.4 + _DAT_00455080) * local_34;
  _DAT_0045505c =
       (((1.0 / local_38) * local_40 * -0.1 - _DAT_0045505c) * 0.4 + _DAT_0045505c) * local_34;
  _DAT_00455058 = _DAT_00455058 - local_2c * _DAT_00455060;
  _DAT_00455084 = local_2c * _DAT_00455080 + _DAT_00455084;
  _DAT_00455034 = _DAT_00455034 - local_2c * _DAT_0045505c;
  FUN_00402429();
  FUN_00402456(_DAT_00455034);
  FUN_004024da(_DAT_00455084);
  FUN_00402565(_DAT_00455058);
  if (local_28[6] != '\0') {
    _DAT_0045501c = _DAT_0045501c - DAT_00454ff8 * param_1;
    _DAT_00455020 = _DAT_00455020 - DAT_00454ffc * param_1;
    _DAT_00455024 = _DAT_00455024 - _DAT_00455000 * param_1;
  }
  if (local_28[7] != '\0') {
    _DAT_0045501c = DAT_00454ff8 * param_1 + _DAT_0045501c;
    _DAT_00455020 = DAT_00454ffc * param_1 + _DAT_00455020;
    _DAT_00455024 = _DAT_00455000 * param_1 + _DAT_00455024;
  }
  if (local_28[8] != '\0') {
    _DAT_0045501c = _DAT_00455010 * param_1 + _DAT_0045501c;
    _DAT_00455020 = _DAT_00455014 * param_1 + _DAT_00455020;
    _DAT_00455024 = _DAT_00455018 * param_1 + _DAT_00455024;
  }
  if (local_28[9] != '\0') {
    _DAT_0045501c = _DAT_0045501c - _DAT_00455010 * param_1;
    _DAT_00455020 = _DAT_00455020 - _DAT_00455014 * param_1;
    _DAT_00455024 = _DAT_00455024 - _DAT_00455018 * param_1;
  }
  if (local_28[0xb] != '\0') {
    _DAT_0045501c = _DAT_0045501c - _DAT_00455004 * param_1;
    _DAT_00455020 = _DAT_00455020 - _DAT_00455008 * param_1;
    _DAT_00455024 = _DAT_00455024 - _DAT_0045500c * param_1;
  }
  if (local_28[10] != '\0') {
    _DAT_0045501c = _DAT_00455004 * param_1 + _DAT_0045501c;
    _DAT_00455020 = _DAT_00455008 * param_1 + _DAT_00455020;
    _DAT_00455024 = _DAT_0045500c * param_1 + _DAT_00455024;
  }
  DAT_004533d4 = DAT_004533d4 + 1;
  bVar8 = DAT_00d0f419 != '\0';
  _DAT_0045501c = _DAT_0045501c * local_30;
  puVar6 = &DAT_00454ff8;
  puVar7 = &DAT_00c06954;
  for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  _DAT_00455020 = _DAT_00455020 * local_30;
  _DAT_00455024 = _DAT_00455024 * local_30;
  DAT_00454fec = local_2c * _DAT_0045501c + DAT_00454fec;
  DAT_00454ff0 = local_2c * _DAT_00455020 + DAT_00454ff0;
  DAT_00454ff4 = local_2c * _DAT_00455024 + DAT_00454ff4;
  DAT_00c06948 = DAT_00454fec;
  DAT_00c0694c = DAT_00454ff0;
  DAT_00c06950 = DAT_00454ff4;
  if ((bVar8) || (iVar5 = DAT_004533d4 / 0x32, DAT_004533d4 % 0x32 == 0)) {
    DAT_00d0f419 = '\0';
    pFVar2 = (FILE *)FUN_0041d331("camera.dat",&DAT_0042b280);
    uVar4 = FUN_0041d384(DAT_004533d4);
    uVar4 = FUN_0041d384(uVar4);
    uVar4 = FUN_0041d384(uVar4);
    uVar4 = FUN_0041d384(uVar4);
    uVar4 = FUN_0041d384(uVar4);
    uVar4 = FUN_0041d384(uVar4);
    _fprintf(pFVar2,"{%d,%d,%d,%d,%d,%d,%d},\n",uVar4);
    iVar5 = _fclose(pFVar2);
    DAT_004533d4 = 0;
  }
  return iVar5;
}



// ==== 0x402d01 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402d01(void)

{
  _DAT_00455048 = 0;
  _DAT_00455038 = 0;
  _DAT_004533e0 = 0x41200000;
  _DAT_004533d8 = 0x3fc00000;
  _DAT_004533dc = 0x3f000000;
  DAT_00454fe0 = 0;
  DAT_00454fe4 = 0x41700000;
  DAT_00454fe8 = 0xc2c80000;
  if (DAT_00c06b38 != 0) {
    DAT_00454fe0 = 0xc2c80000;
    DAT_00454fe4 = 0x40e00000;
    DAT_00454fe8 = 0;
  }
  DAT_00455040 = 0;
  if (DAT_00c0682c != 0) {
    DAT_00454fe0 = 0xc2c80000;
    DAT_00454fe4 = 0x40e00000;
    DAT_00454fe8 = 0;
    DAT_00455040 = 0xbfc90fdb;
  }
  DAT_00455044 = 0;
  DAT_0045503c = 0;
  _DAT_00455070 = 0;
  _DAT_0045506c = 0;
  _DAT_00455068 = 0;
  _DAT_00455030 = 0;
  _DAT_0045502c = 0;
  _DAT_00455028 = 0;
  DAT_00455054 = 0;
  DAT_00455050 = 0;
  DAT_0045504c = 0;
  return;
}



// ==== 0x402e1d ====

void FUN_00402e1d(float *param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float *pfVar3;
  float *in_ECX;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 local_4c [12];
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  undefined1 local_10 [12];
  
  pfVar3 = param_1;
  puVar5 = &stack0x0000000c;
  puVar4 = local_10;
  param_1 = (float *)((1.0 - param_2) *
                     (*param_1 * *in_ECX + param_1[1] * in_ECX[1] + param_1[2] * in_ECX[2]));
  FUN_004021dc(local_1c,pfVar3);
  uVar1 = FUN_00402227(puVar4,puVar5);
  puVar5 = local_28;
  uVar2 = FUN_00402227(local_34,&param_1);
  puVar4 = local_40;
  FUN_00402227(local_4c,&param_2);
  FUN_00402172(puVar4,uVar2);
  pfVar3 = (float *)FUN_00402172(puVar5,uVar1);
  *in_ECX = *pfVar3;
  in_ECX[1] = pfVar3[1];
  in_ECX[2] = pfVar3[2];
  return;
}



// ==== 0x402ea2 ====

void FUN_00402ea2(undefined4 *param_1)

{
  float10 fVar1;
  float10 fVar2;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  float local_8;
  
  local_14 = *param_1;
  uStack_10 = param_1[1];
  uStack_c = param_1[2];
  FUN_004022c1();
  fVar1 = (float10)FUN_004022a2();
  fVar1 = (float10)FUN_0041d134((double)fVar1);
  local_8 = (float)fVar1;
  fVar1 = (float10)FUN_004022a2();
  fVar1 = (float10)FUN_0041d134((double)fVar1);
  fVar1 = (float10)FUN_0041cd94((double)fVar1);
  fVar2 = (float10)FUN_0041d084((double)local_8);
  FUN_00402e1d(&local_14,(float)fVar1,(float)fVar2);
  return;
}



// ==== 0x402f1b ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402f1b(void)

{
  float fVar1;
  float *pfVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float *pfVar9;
  undefined *puVar10;
  undefined1 *puVar11;
  undefined8 uVar12;
  undefined1 local_9c [12];
  float local_90;
  float fStack_8c;
  float fStack_88;
  float local_84;
  float fStack_80;
  float local_7c;
  float local_78;
  float fStack_74;
  float fStack_70;
  float local_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined1 local_60 [12];
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  undefined4 *local_8;
  
  local_50 = 0.0;
  local_4c = 0.0;
  local_48 = 0.0;
  local_c = 50.0;
  if (0 < (int)(PTR_DAT_00453858 + -0xc06b60) / 0x730) {
    local_50 = DAT_00455074;
    local_4c = DAT_00455078;
    local_48 = DAT_0045507c;
    local_1c = 0.0;
    local_18 = 0.0;
    local_2c = DAT_00455074;
    local_14 = 0.0;
    local_28 = DAT_00455078;
    local_24 = DAT_0045507c;
    local_90 = 0.0;
    fStack_8c = 0.0;
    local_20 = 0.1;
    local_54 = 1e+35;
    fStack_88 = 0.0;
    local_c = 8.96831e-44;
    do {
      local_10 = 0.0;
      local_38 = local_1c;
      local_34 = local_18;
      local_30 = local_14;
      if (&DAT_00c06b60 < PTR_DAT_00453858) {
        local_8 = &DAT_00c06c28;
        do {
          FUN_004021a7(&local_6c,&local_50);
          fVar7 = (float10)FUN_004022a2();
          if ((float10)local_10 < fVar7) {
            FUN_004021a7(&local_44,&local_50);
            fVar7 = (float10)FUN_004022a2();
            local_10 = (float)fVar7;
            FUN_004021a7(local_9c,&local_50);
            pfVar2 = (float *)FUN_00402302();
            local_38 = *pfVar2;
            local_34 = pfVar2[1];
            local_30 = pfVar2[2];
          }
          puVar5 = local_8 + 0x1cc;
          puVar3 = local_8 + 0x19a;
          local_8 = puVar5;
        } while (puVar3 < PTR_DAT_00453858);
      }
      if (local_10 <= local_54) {
        fVar1 = 1.1;
        local_54 = local_10;
      }
      else {
        fVar1 = 0.7;
        local_50 = local_2c;
        local_4c = local_28;
        local_48 = local_24;
        local_38 = local_90;
        local_34 = fStack_8c;
        local_30 = fStack_88;
      }
      local_20 = local_20 * fVar1;
      local_2c = local_50;
      local_28 = local_4c;
      local_24 = local_48;
      local_90 = local_38;
      fStack_8c = local_34;
      fStack_88 = local_30;
      pfVar2 = (float *)FUN_00402227(local_60,&local_20);
      local_c = (float)((int)local_c + -1);
      local_50 = local_50 + *pfVar2;
      local_4c = local_4c + pfVar2[1];
      local_48 = local_48 + pfVar2[2];
    } while (local_c != 0.0);
    local_50 = local_2c;
    local_4c = local_28;
    local_48 = local_24;
    fVar7 = (float10)FUN_0041d134((double)local_10);
    local_c = (float)fVar7;
  }
  local_10 = 0.0;
  DAT_00455074 = local_50;
  DAT_00455078 = local_4c;
  DAT_0045507c = local_48;
  if ((((DAT_00c06b50 == 2) || (DAT_00c06b50 == 0xb)) || (DAT_00c0682c == 3)) && (DAT_00c0682c != 1)
     ) {
    _DAT_004533dc = 0.0;
    fVar1 = 0.008;
    if (DAT_00c06b50 == 0xb) {
      fVar1 = 0.02;
    }
    if (DAT_00d0f429 != '\0') {
      local_10 = fVar1;
    }
    if (DAT_00d0f427 != '\0') {
      local_10 = local_10 - fVar1;
    }
  }
  else {
    _DAT_004533dc = 0.0;
    if ((DAT_00c06b50 == 1) && (DAT_00c06b38 == 0)) {
      _DAT_004533dc = 0.5;
    }
  }
  if (DAT_00d0f42e != '\0') {
    _DAT_00455090 = _DAT_00455090 - 0.017;
  }
  if (DAT_00d0f42a != '\0') {
    _DAT_00455090 = _DAT_00455090 + 0.017;
  }
  _DAT_00455090 = _DAT_00455090 * 0.9;
  _DAT_004533e0 = _DAT_004533e0 + _DAT_00455090;
  if (_DAT_004533e0 < 5.0) {
    _DAT_004533e0 = 5.0;
  }
  _DAT_00455048 = _DAT_00455048 + local_10;
  local_18 = 40.0;
  local_14 = -100.0;
  local_90 = 0.0;
  local_1c = 0.0;
  fStack_8c = 0.0;
  fStack_88 = 0.0;
  local_38 = 0.0;
  local_34 = 40.0;
  local_30 = -100.0;
  if (PTR_DAT_00453858 < (undefined *)((int)&DAT_00c06b60 + 1U)) goto LAB_004034d8;
  iVar4 = (int)(PTR_DAT_00453858 + -0xc06b60) / 0x730;
  local_84 = DAT_00c06c28;
  fStack_80 = DAT_00c06c2c;
  local_7c = DAT_00c06c30;
  if (-1 < iVar4) {
    if (iVar4 < 2) {
      pfVar2 = &local_84;
      local_8 = (undefined4 *)0x42480000;
LAB_004032e6:
      local_78 = *pfVar2;
      fStack_74 = pfVar2[1];
      fStack_70 = pfVar2[2];
    }
    else if (iVar4 == 2) {
      pfVar2 = (float *)FUN_0040e7c8();
      local_78 = *pfVar2;
      fStack_74 = pfVar2[1];
      fStack_70 = pfVar2[2];
      FUN_004021a7(local_9c,&local_78);
      fVar7 = (float10)FUN_004022a2();
      fVar7 = (float10)FUN_0041d134((double)fVar7);
      local_8 = (undefined4 *)
                (float)(((float10)_DAT_004533e0 * (float10)3.0 + fVar7 * (float10)1.37) -
                       (float10)20.0);
    }
    else if ((2 < iVar4) && (iVar4 < 5)) {
      local_84 = local_50;
      fStack_80 = local_4c;
      local_7c = local_48;
      local_8 = (undefined4 *)(_DAT_004533e0 * 0.1 * local_c * 2.8);
      pfVar2 = &local_50;
      goto LAB_004032e6;
    }
  }
  if ((float)local_8 < _DAT_004533e0 * 4.0) {
    local_8 = (undefined4 *)(_DAT_004533e0 * 4.0);
  }
  FUN_004021a7(&local_1c,&local_84);
  if (local_1c * local_1c + local_14 * local_14 < 0.0001) {
    local_2c = -1.0;
    local_28 = 0.0;
    local_24 = 1.0;
    local_1c = -1.0;
    local_14 = 1.0;
  }
  local_18 = 0.0;
  FUN_004022c1();
  if (DAT_00c0682c == 3) {
    local_2c = 0.0;
    local_28 = 0.0;
    local_24 = 1.0;
    local_1c = 0.0;
    local_18 = 0.0;
    local_14 = 1.0;
  }
  local_c = _DAT_004533d8 - _DAT_004533dc;
  fVar7 = (float10)FUN_0041cd94((double)local_c);
  local_54 = (float)fVar7;
  fVar7 = (float10)FUN_0041d084((double)local_c);
  pfVar2 = (float *)FUN_00402279(local_60,local_54,0,(float)fVar7);
  local_44 = 0.0;
  local_2c = *pfVar2;
  local_3c = 0;
  local_28 = pfVar2[1];
  local_24 = pfVar2[2];
  local_40 = 0.75;
  local_6c = 0.0;
  fStack_68 = 0.75;
  uStack_64 = 0;
  pfVar2 = (float *)FUN_004021dc(local_60,&local_6c);
  local_2c = *pfVar2;
  local_28 = pfVar2[1];
  local_24 = pfVar2[2];
  _DAT_004533d8 =
       ((local_28 * local_18 + local_2c * local_1c + local_24 * local_14) / (float)local_8) * 0.9 +
       _DAT_004533d8;
  local_44 = 0.0;
  fStack_68 = _DAT_00455048 + _DAT_004533dc;
  local_3c = 0;
  local_6c = 0.0;
  uStack_64 = 0;
  local_40 = fStack_68;
  FUN_00402ea2();
  local_2c = local_2c * (float)local_8;
  local_28 = local_28 * (float)local_8;
  uVar12 = CONCAT44(&local_c,local_60);
  local_24 = local_24 * (float)local_8;
  local_c = 0.5;
  FUN_00402172(local_9c,&local_78);
  puVar5 = (undefined4 *)FUN_00402227(uVar12);
  local_90 = (float)*puVar5;
  fStack_8c = (float)puVar5[1];
  fStack_88 = (float)puVar5[2];
  puVar5 = (undefined4 *)FUN_00402172(local_60,&local_2c);
  local_38 = (float)*puVar5;
  local_30 = (float)puVar5[2];
  local_34 = ((float)local_8 - 45.0) * 0.3 + local_4c + 11.0;
LAB_004034d8:
  iVar4 = DAT_00c06b50;
  local_20 = 0.0003;
  if (DAT_00c06b50 == 2) {
    FUN_004021a7(local_60,&DAT_00454fe0);
    fVar7 = (float10)FUN_004022a2();
    if ((float10)100.0 < fVar7) {
      local_20 = 0.002;
    }
  }
  uVar12 = CONCAT44(&local_c,local_60);
  pfVar2 = &local_20;
  puVar11 = local_9c;
  puVar10 = &DAT_00455028;
  pfVar9 = &local_78;
  local_c = 30.0;
  FUN_004021a7(&local_6c,&DAT_0045504c);
  FUN_004021a7(pfVar9,puVar10);
  FUN_00402227(puVar11,pfVar2);
  pfVar2 = (float *)FUN_00402227(uVar12);
  _DAT_00455028 = _DAT_00455028 + *pfVar2;
  _DAT_0045502c = _DAT_0045502c + pfVar2[1];
  _DAT_00455030 = _DAT_00455030 + pfVar2[2];
  uVar12 = CONCAT44(&local_20,&local_1c);
  local_6c = local_10 * 0.6;
  local_40 = 0.0;
  local_3c = 0;
  fStack_68 = 0.0;
  uStack_64 = 0;
  local_44 = local_6c;
  uVar6 = FUN_004023c6(local_60,&DAT_00c06954);
  puVar11 = local_9c;
  FUN_004021a7(&local_78,&DAT_00454fe0);
  FUN_00402172(puVar11,uVar6);
  pfVar2 = (float *)FUN_00402227(uVar12);
  _DAT_00455028 = (_DAT_00455028 + *pfVar2) * 0.98;
  _DAT_0045502c = (_DAT_0045502c + pfVar2[1]) * 0.98;
  _DAT_00455030 = (_DAT_00455030 + pfVar2[2]) * 0.98;
  DAT_0045504c = local_38;
  DAT_00455050 = local_34;
  uVar12 = CONCAT44(&local_c,local_60);
  DAT_00455054 = local_30;
  local_c = 0.01;
  FUN_004021a7(local_9c,&DAT_00454fe0);
  pfVar2 = (float *)FUN_00402227(uVar12);
  DAT_00454fe0 = DAT_00454fe0 + *pfVar2 + _DAT_00455028;
  DAT_00454fe4 = DAT_00454fe4 + pfVar2[1] + _DAT_0045502c;
  DAT_00454fe8 = DAT_00454fe8 + pfVar2[2] + _DAT_00455030;
  if (iVar4 == 10) {
    DAT_00454fe0 = -129.0;
    DAT_00454fe4 = 17.0;
    DAT_00454fe8 = 6.0;
    local_3c = 0;
    local_44 = 0.05;
    local_40 = -1.6650441;
    DAT_0045503c = 0.05;
    DAT_00455040 = -1.6650441;
    DAT_00455044 = 0.0;
  }
  DAT_00c06948 = DAT_00454fe0;
  DAT_00c0694c = DAT_00454fe4;
  DAT_00c06950 = DAT_00454fe8;
  FUN_00402429();
  FUN_00402671();
  FUN_004025ed();
  FUN_004026fc();
  uVar6 = FUN_004021a7(local_60,&DAT_00454fe0);
  FUN_00402363(&local_1c,uVar6);
  fVar7 = (float10)FUN_0041d134((double)(local_1c * local_1c +
                                        local_18 * local_18 + local_14 * local_14));
  fVar8 = (float10)0.8;
  _DAT_00455068 =
       (float)(((float10)_DAT_00455068 -
               (float10)local_18 * ((float10)1.0 / fVar7) * (float10)-0.016) * fVar8);
  _DAT_0045506c =
       (float)(((float10)_DAT_0045506c - (float10)local_1c * ((float10)1.0 / fVar7) * (float10)0.016
               ) * fVar8);
  _DAT_00455070 = (float)((float10)_DAT_00455070 * fVar8);
  DAT_0045503c = _DAT_00455068 + DAT_0045503c;
  DAT_00455040 = _DAT_0045506c + DAT_00455040;
  DAT_00455044 = _DAT_00455070 + DAT_00455044;
  return;
}



// ==== 0x40381a ====

void FUN_0040381a(undefined4 *param_1)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_28 [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_28[0] = *in_ECX;
  local_28[1] = in_ECX[3];
  local_28[2] = in_ECX[6];
  local_28[3] = in_ECX[1];
  local_18 = in_ECX[4];
  local_14 = in_ECX[7];
  local_10 = in_ECX[2];
  local_c = in_ECX[5];
  local_8 = in_ECX[8];
  puVar2 = local_28;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x40386a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040386a(void)

{
  float10 fVar1;
  float10 fVar2;
  float local_48 [6];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  float local_8;
  
  local_8 = DAT_004533f0;
  fVar1 = (float10)FUN_0041d414(0x3fe4f1a6d0000000);
  local_8 = (float)(fVar1 / (float10)local_8);
  fVar2 = (float10)0.55;
  if ((float10)local_8 < fVar2) {
    fVar1 = (fVar1 / (float10)local_8) * fVar2;
    local_8 = (float)fVar2;
  }
  local_20 = 0x3f8000d2;
  local_10 = 0xbdccce1d;
  local_48[5] = 1.0 / local_8;
  _DAT_0045509c = (float)((float10)-0.5 * (float10)DAT_004533e4);
  _DAT_00455094 = (float)DAT_004533e8 * -0.5;
  _DAT_004550a0 = (float)(((float10)2.0 / ((float10)1 / fVar1)) / (float10)DAT_004533e4);
  _DAT_00455098 = (2.0 / local_48[5]) / (float)DAT_004533e8;
  local_48[0] = (float)((float10)1 / fVar1);
  local_48[4] = 0.0;
  local_28 = 0;
  local_18 = 0;
  local_48[1] = 0.0;
  local_24 = 0;
  local_14 = 0;
  local_48[2] = 0.0;
  local_30 = 0;
  local_48[3] = 0.0;
  local_2c = 0;
  local_1c = 0x3f800000;
  local_c = 0;
  (**(code **)(*DAT_004571ec + 0xb0))(DAT_004571ec,3,local_48);
  return;
}



// ==== 0x403975 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_0040386a(void)

{
  float10 fVar1;
  float10 fVar2;
  float afStack_48 [6];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  float fStack_8;
  
  fStack_8 = DAT_004533f0;
  fVar1 = (float10)FUN_0041d414(0x3fe4f1a6d0000000);
  fStack_8 = (float)(fVar1 / (float10)fStack_8);
  fVar2 = (float10)0.55;
  if ((float10)fStack_8 < fVar2) {
    fVar1 = (fVar1 / (float10)fStack_8) * fVar2;
    fStack_8 = (float)fVar2;
  }
  uStack_20 = 0x3f8000d2;
  uStack_10 = 0xbdccce1d;
  afStack_48[5] = 1.0 / fStack_8;
  _DAT_0045509c = (float)((float10)-0.5 * (float10)DAT_004533e4);
  _DAT_00455094 = (float)DAT_004533e8 * -0.5;
  _DAT_004550a0 = (float)(((float10)2.0 / ((float10)1 / fVar1)) / (float10)DAT_004533e4);
  _DAT_00455098 = (2.0 / afStack_48[5]) / (float)DAT_004533e8;
  afStack_48[0] = (float)((float10)1 / fVar1);
  afStack_48[4] = 0.0;
  uStack_28 = 0;
  uStack_18 = 0;
  afStack_48[1] = 0.0;
  uStack_24 = 0;
  uStack_14 = 0;
  afStack_48[2] = 0.0;
  uStack_30 = 0;
  afStack_48[3] = 0.0;
  uStack_2c = 0;
  uStack_1c = 0x3f800000;
  uStack_c = 0;
  (**(code **)(*DAT_004571ec + 0xb0))(DAT_004571ec,3,afStack_48);
  return;
}



// ==== 0x40397a ====

void FUN_0040397a(void)

{
  undefined4 *in_EAX;
  float *in_ECX;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  
  local_44 = *in_EAX;
  local_38 = 0;
  local_40 = in_EAX[3];
  local_28 = 0;
  local_3c = in_EAX[6];
  local_34 = in_EAX[1];
  local_18 = 0;
  local_30 = in_EAX[4];
  local_14 = -*in_ECX;
  local_2c = in_EAX[7];
  local_10 = -in_ECX[1];
  local_24 = in_EAX[2];
  local_20 = in_EAX[5];
  local_c = -in_ECX[2];
  local_1c = in_EAX[8];
  local_8 = 0x3f800000;
  (**(code **)(*DAT_004571ec + 0xb0))(DAT_004571ec,2,&local_44);
  return;
}



// ==== 0x4039f6 ====

void FUN_004039f6(void)

{
  undefined1 local_10 [12];
  
  FUN_00402363(local_10,&DAT_004550a4);
  FUN_0040397a();
  return;
}



// ==== 0x403a1e ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int FUN_00403a1e(void *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 local_454 [1080];
  undefined1 local_1c [20];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  DAT_0045715c = (**(code **)(*param_2 + 0x10))(param_2);
  iVar2 = 0;
  if (0 < DAT_0045715c) {
    do {
      (**(code **)(*param_2 + 0x14))(param_2,iVar2,0,local_454);
      iVar1 = _memcmp(local_1c,param_1,0x10);
      if (iVar1 == 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < DAT_0045715c);
  }
  return -1;
}



// ==== 0x403a86 ====

void FUN_00403a86(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int local_3c [6];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  piVar3 = (int *)Direct3DCreate9(0x20);
  iVar6 = 0;
  local_3c[0] = 0x16;
  local_3c[1] = 0x15;
  local_3c[2] = 0x16;
  local_3c[3] = 0x14;
  local_3c[4] = 0x17;
  uVar2 = 0;
  if (param_1 == 0) {
    local_8 = 0;
    iVar8 = local_14;
  }
  else {
    local_8 = FUN_00403a1e(param_1,piVar3);
    iVar8 = local_14;
  }
  do {
    local_14 = iVar8;
    uVar7 = uVar2;
    local_14 = (**(code **)(*piVar3 + 0x18))(piVar3,local_8,local_3c[uVar7]);
    if (local_14 != 0) break;
    uVar2 = uVar7 + 1;
    iVar8 = 0;
  } while (uVar7 + 1 < 5);
  pvVar4 = _realloc(DAT_00457158,local_14 << 4);
  local_c = 0;
  local_10 = 0;
  param_1 = 0;
  DAT_00457158 = pvVar4;
  if (0 < local_14) {
    local_18 = local_3c[uVar7];
    iVar8 = 0;
    do {
      (**(code **)(*piVar3 + 0x1c))(piVar3,local_8,local_18,param_1,local_3c + 5);
      pvVar4 = DAT_00457158;
      iVar5 = 0;
      if (local_1c == 0x14) {
        iVar5 = 0x18;
LAB_00403b56:
        if ((local_1c == 0x16) || (local_1c == 0x15)) {
LAB_00403b62:
          if ((iVar6 != local_3c[5]) || (local_10 != local_24)) {
            local_c = local_c + 1;
            piVar1 = (int *)(iVar8 + (int)DAT_00457158);
            piVar1[2] = iVar5;
            *piVar1 = local_3c[5];
            piVar1[1] = local_24;
            piVar1[3] = local_20;
            local_10 = local_24;
            iVar8 = iVar8 + 0x10;
            iVar6 = local_3c[5];
          }
        }
      }
      else {
        if (local_1c == 0x16) {
          iVar5 = 0x20;
          goto LAB_00403b62;
        }
        if ((local_1c != 0x17) && (local_1c != 0x18)) goto LAB_00403b56;
      }
      param_1 = param_1 + 1;
    } while (param_1 < local_14);
  }
  *param_2 = (int)pvVar4;
  *param_3 = local_c;
  (**(code **)(*piVar3 + 8))(piVar3);
  return;
}



// ==== 0x403bb8 ====

void FUN_00403bb8(HINSTANCE param_1)

{
  HWND pHVar1;
  HMENU hMenu;
  LPVOID lpParam;
  
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  if (DAT_0045733c != '\0') {
    pHVar1 = GetDesktopWindow();
    CreateWindowExA(0,"archee","Sumotori",0xcf0000,0,0,DAT_004533e4,DAT_004533e8,pHVar1,hMenu,
                    param_1,lpParam);
    return;
  }
  pHVar1 = GetDesktopWindow();
  CreateWindowExA(0,"archee","Sumotori",0x87000000,0,0,2000,2000,pHVar1,hMenu,param_1,lpParam);
  DAT_004533e4 = DAT_00457334;
  DAT_004533e8 = DAT_00457338;
  return;
}



// ==== 0x403c36 ====

void FUN_00403c36(void)

{
  HWND hWnd;
  HDC hdc;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  HWND local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [12];
  undefined4 local_8;
  
  DAT_004571e4 = (int *)Direct3DCreate9(0x20);
  hWnd = GetDesktopWindow();
  hdc = GetWindowDC(hWnd);
  if (DAT_00457338 * DAT_00457334 == 0) {
    DAT_00457334 = GetDeviceCaps(hdc,8);
    DAT_00457338 = GetDeviceCaps(hdc,10);
  }
  DAT_004533f0 = (float)DAT_00457334 / (float)DAT_00457338;
  ReleaseDC(hWnd,hdc);
  local_64 = DAT_00457334;
  local_60 = DAT_00457338;
  local_5c = 0x15;
  local_58 = 1;
  local_54 = 0;
  local_50 = 0;
  local_4c = 1;
  local_48 = DAT_00d0f4f0;
  local_44 = 0;
  local_40 = 1;
  local_3c = 0x4b;
  local_38 = 0;
  local_34 = 0;
  local_30 = 1;
  DAT_004571ec = (int *)0x0;
  if ((DAT_0045733c != '\0') ||
     (((**(code **)(*DAT_004571e4 + 0x40))
                 (DAT_004571e4,0,1,DAT_00d0f4f0,0x40,&local_64,&DAT_004571ec),
      DAT_004571ec == (int *)0x0 &&
      ((**(code **)(*DAT_004571e4 + 0x40))
                 (DAT_004571e4,0,1,DAT_00d0f4f0,0x20,&local_64,&DAT_004571ec),
      DAT_004571ec == (int *)0x0)))) {
    ShowWindow(DAT_00d0f4f0,1);
    DAT_004533f0 = 1.3333;
    local_34 = 0;
    local_30 = 0;
    local_44 = 1;
    (**(code **)(*DAT_004571e4 + 0x20))(DAT_004571e4,0,local_14);
    local_5c = local_8;
    if ((DAT_004571ec == (int *)0x0) &&
       ((**(code **)(*DAT_004571e4 + 0x40))
                  (DAT_004571e4,0,1,DAT_00d0f4f0,0x40,&local_64,&DAT_004571ec),
       DAT_004571ec == (int *)0x0)) {
      (**(code **)(*DAT_004571e4 + 0x40))
                (DAT_004571e4,0,1,DAT_00d0f4f0,0x20,&local_64,&DAT_004571ec);
    }
  }
  (**(code **)(*DAT_004571ec + 0x48))(DAT_004571ec,0,0,0,&DAT_004571e0);
  local_1c = 0;
  local_24 = DAT_00457334;
  local_18 = 0x3f800000;
  local_20 = DAT_00457338;
  local_2c = 0;
  local_28 = 0;
  (**(code **)(*DAT_004571ec + 0xbc))(DAT_004571ec,&local_2c);
  (**(code **)(*DAT_004571ec + 0x1c))(DAT_004571ec,&DAT_00457200);
  return;
}



// ==== 0x403e16 ====

undefined4
FUN_00403e16(int param_1,char *param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,uint param_9,uint param_10,LPCSTR param_11)

{
  HDC hdc;
  HBITMAP h;
  int iVar1;
  size_t c;
  byte *pbVar2;
  byte bVar3;
  int nDenominator;
  INT *lpDx;
  BITMAPINFO local_3c;
  byte *local_c;
  HFONT local_8;
  
  _memset(&local_3c,0,0x28);
  local_3c.bmiHeader.biWidth = param_6;
  local_3c.bmiHeader.biHeight = -param_7;
  local_3c.bmiHeader.biSize = 0x28;
  local_3c.bmiHeader.biPlanes = 1;
  local_3c.bmiHeader.biCompression = 0;
  local_3c.bmiHeader.biBitCount = 0x20;
  hdc = CreateCompatibleDC((HDC)0x0);
  h = CreateDIBSection(hdc,&local_3c,0,&local_c,(HANDLE)0x0,0);
  SetMapMode(hdc,1);
  nDenominator = 0x48;
  iVar1 = GetDeviceCaps(hdc,0x5a);
  iVar1 = MulDiv(param_8,iVar1,nDenominator);
  local_8 = CreateFontA(iVar1,0,0,0,700,0,0,0,1,0,0,4,2,param_11);
  if (local_8 != (HFONT)0x0) {
    SelectObject(hdc,h);
    SelectObject(hdc,local_8);
    SetTextColor(hdc,param_9 ^ 0xffffff);
    SetBkColor(hdc,param_10 ^ 0xffffff);
    SetTextAlign(hdc,0);
    lpDx = (INT *)0x0;
    c = _strlen(param_2);
    ExtTextOutA(hdc,0,0,2,(RECT *)0x0,param_2,c,lpDx);
    pbVar2 = (byte *)(param_1 + (param_4 * param_5 + param_3) * 4);
    if (0 < param_7) {
      local_8 = (HFONT)param_7;
      do {
        if (0 < param_6) {
          param_7 = param_6;
          do {
            *pbVar2 = (byte)((0xff - (uint)*local_c) * (uint)*pbVar2 >> 8);
            pbVar2[1] = (byte)((0xff - (uint)local_c[1]) * (uint)pbVar2[1] >> 8);
            bVar3 = (byte)((0xff - (uint)local_c[2]) * (uint)pbVar2[2] >> 8);
            pbVar2[2] = bVar3;
            pbVar2[3] = (byte)((0xff - (uint)local_c[2]) * (uint)bVar3 >> 8);
            local_c = local_c + 4;
            pbVar2 = pbVar2 + 4;
            param_7 = param_7 + -1;
          } while (param_7 != 0);
        }
        pbVar2 = pbVar2 + (param_5 - param_6) * 4;
        local_8 = (HFONT)((int)local_8 + -1);
      } while (local_8 != (HFONT)0x0);
    }
  }
  return 0;
}



// ==== 0x403fa8 ====

int FUN_00403fa8(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_00467340;
  if (DAT_00467340 == 0) {
    iVar1 = *(int *)(&DAT_00453408 + param_1 * 4);
  }
  return iVar1;
}



// ==== 0x403fbd ====

void FUN_00403fbd(undefined4 param_1)

{
  FILE *_File;
  size_t sVar1;
  
  _File = (FILE *)FUN_0041d331(param_1,&DAT_0042c278);
  if (_File != (FILE *)0x0) {
    sVar1 = _fread(&DAT_00457340,1,0xffff,_File);
    (&DAT_00457340)[sVar1] = 0;
    _fclose(_File);
    DAT_004eac70 = 0xffffffff;
    DAT_00467340 = &DAT_00457340;
  }
  return;
}



// ==== 0x404008 ====

undefined4 FUN_00404008(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 *)(unaff_EBP + -0x18) = 0;
  *(undefined4 *)(unaff_EBP + -4) = 1;
  FUN_00401206(*(undefined4 *)(unaff_EBP + 0x1c));
  *(undefined1 *)(unaff_EBP + -4) = 2;
  FUN_00401adb(unaff_EBP + -0x9c,unaff_EBP + -0x5c);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  *(undefined4 *)(unaff_EBP + -0x2c) = 0x666;
  FUN_00401206(2);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  iVar2 = FUN_00401bb9(unaff_EBP + -0x28);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (*(int *)(unaff_EBP + -0x28) != 0) {
    _free(*(void **)(unaff_EBP + -0x28));
  }
  FUN_00401206(0x10000);
  *(undefined1 *)(unaff_EBP + -4) = 5;
  iVar3 = FUN_00401bb9(unaff_EBP + -0x28);
  *(undefined1 *)(unaff_EBP + -4) = 3;
  if (*(int *)(unaff_EBP + -0x28) != 0) {
    _free(*(void **)(unaff_EBP + -0x28));
  }
  FUN_00401206(0);
  *(undefined4 *)(unaff_EBP + -0x14) = 0xffffffff;
  *(undefined1 *)(unaff_EBP + -4) = 6;
  if (-1 < iVar2 + 1) {
    do {
      if (*(int *)(unaff_EBP + -0x14) == -1) {
        *(undefined1 *)(unaff_EBP + -0xd) = 1;
      }
      else {
        iVar4 = FUN_004010d6(*(undefined4 *)(unaff_EBP + -0x14));
        *(bool *)(unaff_EBP + -0xd) = iVar4 != 0;
      }
      FUN_00401206(1);
      *(undefined1 *)(unaff_EBP + -4) = 7;
      if (0 < iVar3 + 1) {
        *(int *)(unaff_EBP + -0x18) = iVar3 + 1;
        do {
          iVar4 = *(int *)(unaff_EBP + -0x2c) * 0x343fd + 0x269ec3;
          *(int *)(unaff_EBP + -0x2c) = iVar4;
          if (*(char *)(unaff_EBP + -0xd) != '\0') {
            uVar5 = FUN_00401206(iVar4 >> 0x10 & 0x7fff);
            *(undefined1 *)(unaff_EBP + -4) = 8;
            uVar5 = FUN_0040155e(unaff_EBP + -0x7c,uVar5);
            *(undefined1 *)(unaff_EBP + -4) = 9;
            FUN_00401482(uVar5);
            if (*(int *)(unaff_EBP + -0x7c) != 0) {
              _free(*(void **)(unaff_EBP + -0x7c));
              *(undefined4 *)(unaff_EBP + -0x7c) = 0;
            }
            *(undefined1 *)(unaff_EBP + -4) = 7;
            if (*(int *)(unaff_EBP + -0x6c) != 0) {
              _free(*(void **)(unaff_EBP + -0x6c));
              *(undefined4 *)(unaff_EBP + -0x6c) = 0;
            }
            FUN_00401206(0x10000);
            *(undefined1 *)(unaff_EBP + -4) = 10;
            uVar5 = FUN_0040155e(unaff_EBP + -0x3c,unaff_EBP + -0x28);
            FUN_004011b6(uVar5);
            if (*(int *)(unaff_EBP + -0x3c) != 0) {
              _free(*(void **)(unaff_EBP + -0x3c));
              *(undefined4 *)(unaff_EBP + -0x3c) = 0;
            }
            *(undefined1 *)(unaff_EBP + -4) = 7;
            if (*(int *)(unaff_EBP + -0x28) != 0) {
              _free(*(void **)(unaff_EBP + -0x28));
              *(undefined4 *)(unaff_EBP + -0x28) = 0;
            }
          }
          piVar1 = (int *)(unaff_EBP + -0x18);
          *piVar1 = *piVar1 + -1;
        } while (*piVar1 != 0);
      }
      *(undefined1 *)(unaff_EBP + -4) = 6;
      if (*(int *)(unaff_EBP + -0x8c) != 0) {
        _free(*(void **)(unaff_EBP + -0x8c));
        *(undefined4 *)(unaff_EBP + -0x8c) = 0;
      }
      *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 1;
    } while (*(int *)(unaff_EBP + -0x14) < iVar2 + 1);
  }
  uVar5 = FUN_00401adb(unaff_EBP + -0x3c,unaff_EBP + 0x20);
  FUN_004011b6(uVar5);
  if (*(int *)(unaff_EBP + -0x3c) != 0) {
    _free(*(void **)(unaff_EBP + -0x3c));
  }
  FUN_00401b5c(unaff_EBP + -0x7c,unaff_EBP + -0x5c);
  *(undefined1 *)(unaff_EBP + -4) = 0xb;
  FUN_0040155e(unaff_EBP + -0x6c,unaff_EBP + -0x5c);
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  uVar5 = FUN_00401764(unaff_EBP + -0x3c,unaff_EBP + -0x9c);
  FUN_004011b6(uVar5);
  if (*(int *)(unaff_EBP + -0x3c) != 0) {
    _free(*(void **)(unaff_EBP + -0x3c));
    *(undefined4 *)(unaff_EBP + -0x3c) = 0;
  }
  if (*(int *)(unaff_EBP + -0x6c) != 0) {
    _free(*(void **)(unaff_EBP + -0x6c));
    *(undefined4 *)(unaff_EBP + -0x6c) = 0;
  }
  *(undefined1 *)(unaff_EBP + -4) = 6;
  if (*(int *)(unaff_EBP + -0x7c) != 0) {
    _free(*(void **)(unaff_EBP + -0x7c));
  }
  FUN_00401247(unaff_EBP + -0x4c);
  if (*(int *)(unaff_EBP + -0x4c) != 0) {
    _free(*(void **)(unaff_EBP + -0x4c));
    *(undefined4 *)(unaff_EBP + -0x4c) = 0;
  }
  if (*(int *)(unaff_EBP + -0x9c) != 0) {
    _free(*(void **)(unaff_EBP + -0x9c));
    *(undefined4 *)(unaff_EBP + -0x9c) = 0;
  }
  if (*(int *)(unaff_EBP + -0x5c) != 0) {
    _free(*(void **)(unaff_EBP + -0x5c));
    *(undefined4 *)(unaff_EBP + -0x5c) = 0;
  }
  if (*(int *)(unaff_EBP + 0xc) != 0) {
    _free(*(void **)(unaff_EBP + 0xc));
    *(undefined4 *)(unaff_EBP + 0xc) = 0;
  }
  if (*(int *)(unaff_EBP + 0x20) != 0) {
    _free(*(void **)(unaff_EBP + 0x20));
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}



// ==== 0x40431c ====

undefined4 FUN_0040431c(void)

{
  undefined1 uVar1;
  char cVar2;
  undefined4 uVar3;
  int unaff_EBP;
  undefined1 auStack_98 [12];
  undefined4 uStack_8c;
  undefined *puStack_88;
  undefined4 uStack_84;
  char *pcStack_80;
  char *pcStack_7c;
  
  FUN_0041cc3c();
  pcStack_7c = (char *)0x404336;
  FUN_00401206();
  *(undefined4 *)(unaff_EBP + -4) = 0;
  pcStack_7c = (char *)0x404346;
  FUN_00401348();
  pcStack_7c = (char *)0x404353;
  FUN_00401348();
  pcStack_7c = (char *)0x404360;
  FUN_00401348();
  pcStack_7c = (char *)0x40436d;
  FUN_00401348();
  pcStack_7c = (char *)0x404377;
  FUN_00401206();
  pcStack_7c = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  pcStack_80 = *(char **)(unaff_EBP + 0xc);
  uStack_84 = *(undefined4 *)(unaff_EBP + 8);
  *(undefined1 *)(unaff_EBP + -4) = 1;
  puStack_88 = (undefined *)0x404391;
  FUN_0040180e();
  *(undefined1 *)(unaff_EBP + -4) = 2;
  pcStack_7c = (char *)0x40439e;
  FUN_00401206();
  *(undefined1 *)(unaff_EBP + -4) = 3;
  pcStack_7c = (char *)0x4043ae;
  uVar1 = FUN_00401948();
  *(undefined1 *)(unaff_EBP + -0xd) = uVar1;
  *(undefined1 *)(unaff_EBP + -4) = 2;
  if (*(int *)(unaff_EBP + -0x78) != 0) {
    pcStack_7c = (char *)0x4043c2;
    _free(*(void **)(unaff_EBP + -0x78));
  }
  if (*(char *)(unaff_EBP + -0xd) == '\0') {
    FUN_00401360();
    *(undefined1 *)(unaff_EBP + -4) = 4;
    if (*(int *)(unaff_EBP + 0x10) == 0) {
      pcStack_7c = (char *)(unaff_EBP + -0x58);
      pcStack_80 = (char *)(unaff_EBP + -0x28);
      uStack_84 = 0x4043f1;
      FUN_00401e60();
    }
    else {
      pcStack_7c = (char *)0x4043fc;
      FUN_004011b6();
    }
    puStack_88 = (undefined *)(unaff_EBP + -0x38);
    *(undefined4 **)(unaff_EBP + -0x14) = &uStack_84;
    uStack_8c = 0x40440d;
    FUN_00401247();
    puStack_88 = &DAT_0076adf1;
    *(undefined1 **)(unaff_EBP + -0x18) = auStack_98;
    *(undefined1 *)(unaff_EBP + -4) = 5;
    FUN_00401247(unaff_EBP + -0x48);
    *(undefined1 *)(unaff_EBP + -4) = 4;
    FUN_00404008(unaff_EBP + -0x68);
    *(undefined1 *)(unaff_EBP + -4) = 6;
    pcStack_7c = (char *)0x404447;
    cVar2 = FUN_00401948();
    if (cVar2 != '\0') {
      if (*(int *)(unaff_EBP + 0x14) != 0) {
        pcStack_7c = (char *)0x24;
        pcStack_80 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        uStack_84 = 200;
        puStack_88 = *(undefined **)(unaff_EBP + 0x14);
        uStack_8c = 0x404464;
        FUN_00401fb4();
      }
      if (*(int *)(unaff_EBP + -0x68) != 0) {
        pcStack_7c = (char *)0x404471;
        _free(*(void **)(unaff_EBP + -0x68));
        *(undefined4 *)(unaff_EBP + -0x68) = 0;
      }
      if (*(int *)(unaff_EBP + -0x48) != 0) {
        pcStack_7c = (char *)0x404482;
        _free(*(void **)(unaff_EBP + -0x48));
        *(undefined4 *)(unaff_EBP + -0x48) = 0;
      }
      if (*(int *)(unaff_EBP + -0x28) != 0) {
        pcStack_7c = (char *)0x404493;
        _free(*(void **)(unaff_EBP + -0x28));
        *(undefined4 *)(unaff_EBP + -0x28) = 0;
      }
      if (*(int *)(unaff_EBP + -0x58) != 0) {
        pcStack_7c = (char *)0x4044a4;
        _free(*(void **)(unaff_EBP + -0x58));
        *(undefined4 *)(unaff_EBP + -0x58) = 0;
      }
      if (*(int *)(unaff_EBP + -0x38) != 0) {
        pcStack_7c = (char *)0x4044b5;
        _free(*(void **)(unaff_EBP + -0x38));
      }
      uVar3 = 1;
      goto LAB_0040450e;
    }
    if (*(int *)(unaff_EBP + -0x68) != 0) {
      pcStack_7c = (char *)0x4044c7;
      _free(*(void **)(unaff_EBP + -0x68));
      *(undefined4 *)(unaff_EBP + -0x68) = 0;
    }
    if (*(int *)(unaff_EBP + -0x48) != 0) {
      pcStack_7c = (char *)0x4044d8;
      _free(*(void **)(unaff_EBP + -0x48));
      *(undefined4 *)(unaff_EBP + -0x48) = 0;
    }
  }
  if (*(int *)(unaff_EBP + -0x28) != 0) {
    pcStack_7c = (char *)0x4044e9;
    _free(*(void **)(unaff_EBP + -0x28));
    *(undefined4 *)(unaff_EBP + -0x28) = 0;
  }
  if (*(int *)(unaff_EBP + -0x58) != 0) {
    pcStack_7c = (char *)0x4044fa;
    _free(*(void **)(unaff_EBP + -0x58));
    *(undefined4 *)(unaff_EBP + -0x58) = 0;
  }
  if (*(int *)(unaff_EBP + -0x38) != 0) {
    pcStack_7c = (char *)0x40450b;
    _free(*(void **)(unaff_EBP + -0x38));
  }
  uVar3 = 0;
LAB_0040450e:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return uVar3;
}



// ==== 0x40451c ====

void FUN_0040451c(BYTE *param_1)

{
  LSTATUS LVar1;
  size_t cbData;
  HKEY local_8;
  
  FUN_0041d7b0(&DAT_00467348,param_1);
  LVar1 = RegCreateKeyA((HKEY)0x80000001,"Software\\Archee\\Sumotori",&local_8);
  if (LVar1 == 0) {
    cbData = _strlen((char *)param_1);
    RegSetValueExA(local_8,"settings",0,3,param_1,cbData);
    RegCloseKey(local_8);
  }
  return;
}



// ==== 0x404571 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_00404571(char *param_1,char param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char local_134 [300];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  iVar3 = 0;
  do {
    while( true ) {
      cVar1 = *param_1;
      if ((((cVar1 == '\0') || (('`' < cVar1 && (cVar1 < '{')))) || (('@' < cVar1 && (cVar1 < '[')))
          ) || (('/' < cVar1 && (cVar1 < ':')))) break;
      param_1 = param_1 + 1;
    }
    cVar1 = *param_1;
    local_134[iVar3] = cVar1;
    if (('`' < cVar1) && (cVar1 < '{')) {
      local_134[iVar3] = cVar1 + -0x20;
    }
    if (cVar1 != '\0') {
      param_1 = param_1 + 1;
    }
    iVar4 = iVar3 + 1;
    local_134[iVar3 + 1] = '\0';
    iVar3 = iVar4;
  } while (iVar4 < 0x19);
  if (local_134[0] == '\0') {
    uVar2 = 1;
  }
  else {
    cVar1 = FUN_0040431c(local_134,0,0,local_134);
    if (cVar1 == '\0') {
      uVar2 = 2;
    }
    else {
      if (param_2 != '\0') {
        FUN_0040451c(local_134);
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}



// ==== 0x40461e ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 FUN_0040461e(void)

{
  undefined1 uVar1;
  LSTATUS LVar2;
  BYTE *pBVar3;
  DWORD local_d8;
  HKEY local_d4;
  BYTE local_d0 [25];
  undefined1 local_b7;
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  if (DAT_00467348 == '\0') {
    LVar2 = RegOpenKeyExA((HKEY)0x80000001,"Software\\Archee\\Sumotori",0,0x20019,&local_d4);
    if (LVar2 != 0) {
      return 0;
    }
    local_d8 = 0x19;
    RegQueryValueExA(local_d4,"settings",(LPDWORD)0x0,(LPDWORD)0x0,local_d0,&local_d8);
    local_b7 = 0;
    RegCloseKey(local_d4);
    pBVar3 = local_d0;
  }
  else {
    pBVar3 = (BYTE *)&DAT_00467348;
  }
  uVar1 = FUN_0040431c(pBVar3,0,1,0);
  return uVar1;
}



// ==== 0x4046b5 ====

void FUN_004046b5(float param_1,float param_2)

{
  FUN_0041d9d0((double)param_1,(double)param_2);
  return;
}



// ==== 0x4046d0 ====

void FUN_004046d0(float param_1,float param_2)

{
  FUN_0041d9f0((double)param_1,(double)param_2);
  return;
}



// ==== 0x4046eb ====

void FUN_004046eb(undefined4 param_1,undefined4 param_2)

{
  FUN_004046b5(param_1,param_2);
  return;
}



// ==== 0x404704 ====

void FUN_00404704(undefined4 param_1,undefined4 param_2)

{
  FUN_004046d0(param_1,param_2);
  return;
}



// ==== 0x40471d ====

void FUN_0040471d(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *in_ECX;
  
  fVar1 = param_2[1];
  fVar2 = in_ECX[1];
  fVar3 = param_2[2];
  fVar4 = in_ECX[2];
  *param_1 = *param_2 * *in_ECX;
  param_1[1] = fVar1 * fVar2;
  param_1[2] = fVar3 * fVar4;
  return;
}



// ==== 0x404752 ====

void FUN_00404752(char param_1)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0x0;
  if (param_1 == '\0') {
    do {
      puVar1 = puVar1 + 1;
      *puVar1 = 0x7f;
    } while( true );
  }
  return;
}



// ==== 0x404761 ====

void FUN_00404761(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_00402279(local_10,param_2,param_2,param_2);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x40479a ====

void FUN_0040479a(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1c [24];
  
  fVar4 = (float10)FUN_004046eb(*(undefined4 *)param_1[1],((undefined4 *)param_1[1])[1]);
  puVar3 = (undefined4 *)FUN_00404761(local_1c,(float)fVar4);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x4047e0 ====

void FUN_004047e0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1c [24];
  
  fVar4 = (float10)FUN_004022a2();
  fVar4 = (float10)FUN_0041d134((double)fVar4);
  puVar3 = (undefined4 *)FUN_00404761(local_1c,(float)fVar4);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x404828 ====

void FUN_00404828(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_1c [24];
  
  puVar3 = (undefined4 *)
           FUN_00402279(local_1c,*(undefined4 *)param_1[1],*(undefined4 *)param_1[2],
                        *(undefined4 *)param_1[3]);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x40489a ====

void FUN_0040489a(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1c [24];
  
  fVar4 = (float10)FUN_00404704(*(undefined4 *)(param_1[1] + 8),*(undefined4 *)(param_1[2] + 8));
  fVar4 = (float10)FUN_00404704(*(undefined4 *)(param_1[1] + 4),*(undefined4 *)(param_1[2] + 4),
                                (float)fVar4);
  fVar4 = (float10)FUN_00404704(*(undefined4 *)param_1[1],*(undefined4 *)param_1[2],(float)fVar4);
  puVar3 = (undefined4 *)FUN_00402279(local_1c,(float)fVar4);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x40491b ====

void FUN_0040491b(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_24 [24];
  float local_c;
  float local_8;
  
  fVar3 = *(float *)(param_1[1] + 8);
  fVar5 = (float10)FUN_0041cd94((double)*(float *)(param_1[1] + 4));
  local_8 = (float)fVar5;
  fVar5 = (float10)FUN_0041cd94((double)*(float *)param_1[1]);
  local_c = (float)fVar5;
  fVar5 = (float10)FUN_0041cd94((double)fVar3);
  puVar4 = (undefined4 *)FUN_00402279(local_24,local_c,local_8,(float)fVar5);
  uVar1 = puVar4[1];
  uVar2 = puVar4[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar4;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x40498d ====

void FUN_0040498d(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float *pfVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined1 local_1c [24];
  
  pfVar3 = (float *)param_1[2];
  pfVar4 = (float *)param_1[1];
  puVar5 = (undefined4 *)
           FUN_00404761(local_1c,*pfVar3 * *pfVar4 + pfVar3[1] * pfVar4[1] + pfVar3[2] * pfVar4[2]);
  uVar1 = puVar5[1];
  uVar2 = puVar5[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar5;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x4049d7 ====

void FUN_004049d7(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_00402302(local_10);
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x4049f9 ====

void FUN_004049f9(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_00402172(local_10,param_1[2]);
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x404a1e ====

void FUN_00404a1e(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_004021a7(local_10,param_1[2]);
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x404a43 ====

void FUN_00404a43(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_0040471d(local_10,param_1[2]);
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x404a68 ====

void FUN_00404a68(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float *pfVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined1 local_1c [24];
  
  pfVar3 = (float *)param_1[1];
  pfVar4 = (float *)param_1[2];
  puVar5 = (undefined4 *)
           FUN_00402279(local_1c,*pfVar3 / *pfVar4,pfVar3[1] / pfVar4[1],pfVar3[2] / pfVar4[2]);
  uVar1 = puVar5[1];
  uVar2 = puVar5[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar5;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x404ab9 ====

float10 FUN_00404ab9(float param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if (0.0 <= param_1) {
    fVar1 = (float10)FUN_0041cf20((double)param_1);
    fVar1 = (float10)FUN_0041ce90((double)(fVar1 * (float10)param_2));
  }
  else {
    fVar1 = (float10)FUN_0041cf20((double)-param_1);
    fVar2 = (float10)FUN_0041cd94((double)(param_2 * 3.1415927));
    fVar1 = (float10)FUN_0041ce90((double)(float)(fVar1 * (float10)param_2));
    fVar1 = fVar1 * (float10)(float)fVar2;
  }
  return fVar1;
}



// ==== 0x404b20 ====

void FUN_00404b20(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1c [24];
  
  fVar4 = (float10)FUN_00404ab9(*(undefined4 *)(param_1[1] + 8),*(undefined4 *)(param_1[2] + 8));
  fVar4 = (float10)FUN_00404ab9(*(undefined4 *)(param_1[1] + 4),*(undefined4 *)(param_1[2] + 4),
                                (float)fVar4);
  fVar4 = (float10)FUN_00404ab9(*(undefined4 *)param_1[1],*(undefined4 *)param_1[2],(float)fVar4);
  puVar3 = (undefined4 *)FUN_00402279(local_1c,(float)fVar4);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x404ba1 ====

void FUN_00404ba1(undefined4 *param_1,double param_2)

{
  float fVar1;
  undefined4 *puVar2;
  undefined1 local_10 [12];
  
  fVar1 = (float)param_2;
  puVar2 = (undefined4 *)FUN_00402279(local_10,fVar1,fVar1,fVar1);
  *param_1 = *puVar2;
  param_1[1] = puVar2[1];
  param_1[2] = puVar2[2];
  return;
}



// ==== 0x404bd6 ====

void FUN_00404bd6(undefined4 *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_38 [9];
  undefined4 local_14;
  float local_10;
  undefined4 uStack_c;
  undefined4 local_8;
  
  puVar3 = (undefined4 *)*param_1;
  puVar3[2] = 0;
  puVar3[1] = 0;
  *puVar3 = 0;
  if (DAT_00467b4c != 0) {
    puVar3 = (undefined4 *)(DAT_00467b4c + 0x60);
    puVar4 = local_38;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    local_8 = *(undefined4 *)(DAT_00467b4c + 0x54);
    cVar1 = *(char *)(DAT_00467b4c + 0xd0);
    FUN_00408e51(1);
    FUN_004086da();
    FUN_004087a4();
    FUN_00408b34();
    if (cVar1 != '\0') {
      FUN_004089b4();
    }
    puVar3 = local_38;
    puVar4 = (undefined4 *)(DAT_00467b4c + 0x60);
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(DAT_00467b4c + 0x54) = local_8;
  }
  puVar3 = (undefined4 *)param_1[1];
  local_14 = *puVar3;
  uStack_c = puVar3[2];
  local_10 = (float)puVar3[1] * -1.0;
  iVar2 = FUN_0041d384();
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (0x1e < iVar2) {
    iVar2 = 0x1f;
  }
  puVar3 = (undefined4 *)param_1[2];
  DAT_00467b4c = FUN_00408d57(local_14,local_10,uStack_c,*puVar3,puVar3[1],puVar3[2],iVar2,
                              0x3d800000);
  iVar2 = FUN_0041d384();
  if (iVar2 != 0) {
    FUN_004089b4();
  }
  return;
}



// ==== 0x404d26 ====

void FUN_00404d26(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_1c [24];
  
  fVar4 = (float10)FUN_0040b798();
  fVar4 = (float10)FUN_0040b798((float)((fVar4 + fVar4) - (float10)1.0));
  fVar4 = (float10)FUN_0040b798((float)((fVar4 + fVar4) - (float10)1.0));
  puVar3 = (undefined4 *)FUN_00402279(local_1c,(float)((fVar4 + fVar4) - (float10)1.0));
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  param_1 = (undefined4 *)*param_1;
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x404d8f ====

void FUN_00404d8f(undefined4 *param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_1c [12];
  float local_10;
  float local_c;
  float local_8;
  
  puVar1 = (undefined4 *)*param_1;
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  if (DAT_00467b4c != 0) {
    FUN_004046eb(*(undefined4 *)param_1[1],((undefined4 *)param_1[1])[2]);
    FUN_00402456();
    pfVar2 = (float *)FUN_00402279(local_1c,*(undefined4 *)param_1[1],((undefined4 *)param_1[1])[2],
                                   0);
    local_10 = *pfVar2;
    local_c = pfVar2[1];
    local_8 = pfVar2[2];
    fVar3 = (float10)FUN_0041d134((double)(local_10 * local_10 +
                                          local_c * local_c + local_8 * local_8));
    FUN_004046eb(*(undefined4 *)(param_1[1] + 4),(float)fVar3);
    FUN_004024da();
  }
  return;
}



// ==== 0x404f9c ====

void FUN_00404f9c(void)

{
  undefined4 *in_ECX;
  
  if ((void *)*in_ECX != (void *)0x0) {
    _free((void *)*in_ECX);
    *in_ECX = 0;
  }
  return;
}



// ==== 0x404fb1 ====

void FUN_00404fb1(void)

{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  int in_ECX;
  
  puVar3 = operator_new(0x2c);
  piVar1 = (int *)(in_ECX + 0x305c);
  iVar2 = *piVar1;
  *(undefined4 *)(puVar3 + 0x28) = 0;
  *(int *)(puVar3 + 0x24) = iVar2;
  if (*piVar1 != 0) {
    *(undefined1 **)(*piVar1 + 0x28) = puVar3;
  }
  *piVar1 = (int)puVar3;
  *(undefined4 *)(puVar3 + 0x20) = 0;
  *(undefined4 *)(puVar3 + 0x10) = 0xffffffff;
  *(undefined4 *)(puVar3 + 0x14) = *(undefined4 *)(in_ECX + 0x10);
  *(undefined4 *)(puVar3 + 0x18) = *(undefined4 *)(in_ECX + 0x14);
  *(undefined4 *)(puVar3 + 0x1c) = *(undefined4 *)(in_ECX + 0x18);
  *puVar3 = 0;
  return;
}



// ==== 0x404fee ====

int FUN_00404fee(int param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  int extraout_EDX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        (uint)(param_1 * 0xc) < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + extraout_EDX;
}



// ==== 0x405012 ====

void FUN_00405012(undefined4 *param_1)

{
  char cVar1;
  
  while( true ) {
    cVar1 = *(char *)*param_1;
    if ((((cVar1 != ' ') && (cVar1 != '\t')) && (cVar1 != '\r')) && (cVar1 != '\n')) break;
    *param_1 = (char *)*param_1 + 1;
  }
  return;
}



// ==== 0x405034 ====

void FUN_00405034(void)

{
  uint uVar1;
  void *pvVar2;
  int *in_ECX;
  uint _NewSize;
  
  uVar1 = (in_ECX[1] - *in_ECX) / 0x1c;
  _NewSize = ((uVar1 >> 3) + 1 + uVar1) * 0x1c;
  FUN_00404752(CONCAT31((uint3)(uVar1 >> 0xb),_NewSize < 0x10000000));
  pvVar2 = _realloc((void *)*in_ECX,_NewSize);
  in_ECX[1] = (int)(uVar1 * 0x1c + (int)pvVar2);
  in_ECX[2] = (int)(_NewSize + (int)pvVar2);
  *in_ECX = (int)pvVar2;
  return;
}



// ==== 0x40507d ====

void FUN_0040507d(void)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  int *in_ECX;
  uint _NewSize;
  
  uVar2 = (in_ECX[1] - *in_ECX) / 0x18;
  iVar1 = (uVar2 >> 3) + 1 + uVar2;
  _NewSize = iVar1 * 0x18;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar3 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar3;
  in_ECX[2] = (int)(_NewSize + (int)pvVar3);
  in_ECX[1] = (int)((int)pvVar3 + uVar2 * 0x18);
  return;
}



// ==== 0x4050ca ====

void FUN_004050ca(void)

{
  int iVar1;
  void *pvVar2;
  int *in_ECX;
  uint _NewSize;
  uint uVar3;
  
  uVar3 = in_ECX[1] - *in_ECX >> 3;
  iVar1 = (uVar3 >> 3) + 1 + uVar3;
  _NewSize = iVar1 * 8;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar2 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar2;
  in_ECX[2] = (int)(_NewSize + (int)pvVar2);
  in_ECX[1] = (int)((int)pvVar2 + uVar3 * 8);
  return;
}



// ==== 0x405110 ====

void FUN_00405110(void)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  int *in_ECX;
  uint _NewSize;
  
  uVar2 = (in_ECX[1] - *in_ECX) / 0xc;
  iVar1 = (uVar2 >> 3) + 1 + uVar2;
  _NewSize = iVar1 * 0xc;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar3 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar3;
  in_ECX[2] = (int)(_NewSize + (int)pvVar3);
  in_ECX[1] = (int)((int)pvVar3 + uVar2 * 0xc);
  return;
}



// ==== 0x40515d ====

undefined4 FUN_0040515d(char param_1)

{
  undefined4 uVar1;
  
  if ((((param_1 < 'a') || ('z' < param_1)) && ((param_1 < 'A' || ('Z' < param_1)))) &&
     (param_1 != '_')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 0x40517f ====

char * FUN_0040517f(char *param_1)

{
  int iVar1;
  int in_ECX;
  char *pcVar2;
  
  for (pcVar2 = *(char **)(in_ECX + 0x3060); pcVar2 != (char *)0x0;
      pcVar2 = *(char **)(pcVar2 + 0x24)) {
    iVar1 = _strcmp(param_1,pcVar2);
    if (iVar1 == 0) {
      return pcVar2;
    }
  }
  pcVar2 = *(char **)(in_ECX + 0x305c);
  while( true ) {
    if (pcVar2 == (char *)0x0) {
      return (char *)0x0;
    }
    iVar1 = _strcmp(param_1,pcVar2);
    if (iVar1 == 0) break;
    pcVar2 = *(char **)(pcVar2 + 0x24);
  }
  return pcVar2;
}



// ==== 0x4051cc ====

char * FUN_004051cc(char *param_1)

{
  char *pcVar1;
  int in_ECX;
  
  pcVar1 = param_1;
  if (param_1 == (char *)0x0) {
    return (char *)0x0;
  }
  do {
    if (*pcVar1 != ';') break;
    pcVar1 = pcVar1 + 1;
  } while (pcVar1 != (char *)0x0);
  while( true ) {
    if (pcVar1 == (char *)0x0) {
      return (char *)0x0;
    }
    if (*pcVar1 == '}') {
      return pcVar1;
    }
    if (*pcVar1 == '\0') {
      return pcVar1;
    }
    if (*(char *)(in_ECX + 0xc) != '\0') break;
    param_1 = (char *)FUN_00406306(pcVar1);
    if (*(char *)(in_ECX + 0xc) != '\0') {
      return (char *)0x0;
    }
    for (; (param_1 != (char *)0x0 && (*param_1 == ';')); param_1 = param_1 + 1) {
    }
    FUN_00405012(&param_1);
    pcVar1 = param_1;
  }
  return pcVar1;
}



// ==== 0x40522e ====

undefined4 FUN_0040522e(char param_1)

{
  undefined4 uVar1;
  
  if (((((param_1 < 'a') || ('z' < param_1)) && ((param_1 < 'A' || ('Z' < param_1)))) &&
      (param_1 != '_')) && ((param_1 < '0' || ('9' < param_1)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 0x405258 ====

char * FUN_00405258(char *param_1)

{
  int iVar1;
  int in_ECX;
  char *_Str1;
  
  _Str1 = *(char **)(in_ECX + 0x3074);
  while( true ) {
    if (_Str1 == (char *)0x0) {
      return (char *)0x0;
    }
    iVar1 = _strcmp(_Str1,param_1);
    if (iVar1 == 0) break;
    _Str1 = *(char **)(_Str1 + 0x120);
  }
  return _Str1;
}



// ==== 0x405285 ====

int FUN_00405285(int param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  int extraout_EDX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        (uint)(param_1 * 0x18) < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + extraout_EDX;
}



// ==== 0x4052a9 ====

int FUN_004052a9(int param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  int extraout_EDX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        (uint)(param_1 << 3) < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + extraout_EDX;
}



// ==== 0x4052ca ====

void FUN_004052ca(void)

{
  uint _NewSize;
  void *pvVar1;
  int *in_ECX;
  uint uVar2;
  
  uVar2 = in_ECX[1] - *in_ECX;
  _NewSize = (uVar2 >> 3) + 1 + uVar2;
  FUN_00404752(CONCAT31((uint3)(uVar2 >> 0xb),_NewSize < 0x10000000));
  pvVar1 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar1;
  in_ECX[2] = (int)pvVar1 + _NewSize;
  in_ECX[1] = (int)pvVar1 + uVar2;
  return;
}



// ==== 0x405308 ====

int FUN_00405308(uint param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        param_1 < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + param_1;
}



// ==== 0x405326 ====

undefined4 FUN_00405326(char param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < '0') || ('9' < param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 0x40533e ====

void FUN_0040533e(void)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  int *in_ECX;
  uint _NewSize;
  
  uVar2 = (in_ECX[1] - *in_ECX) / 0x30;
  iVar1 = (uVar2 >> 3) + 1 + uVar2;
  _NewSize = iVar1 * 0x30;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar3 = _realloc((void *)*in_ECX,_NewSize);
  in_ECX[2] = (int)(_NewSize + (int)pvVar3);
  *in_ECX = (int)pvVar3;
  in_ECX[1] = (int)(uVar2 * 0x30 + (int)pvVar3);
  return;
}



// ==== 0x40538d ====

void FUN_0040538d(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)param_1[1];
  uVar1 = *puVar4;
  uVar2 = puVar4[1];
  uVar3 = puVar4[2];
  FUN_00402ea2(param_1[2]);
  param_1 = (undefined4 *)*param_1;
  *param_1 = uVar1;
  param_1[1] = uVar2;
  param_1[2] = uVar3;
  return;
}



// ==== 0x4053ba ====

void FUN_004053ba(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_FUN_0042c3c0;
  in_ECX[0xc0c] = 0;
  in_ECX[0xc0d] = 0;
  in_ECX[0xc0e] = 0;
  in_ECX[0xc0f] = 0;
  in_ECX[0xc10] = 0;
  in_ECX[0xc11] = 0;
  in_ECX[0xc1a] = 0;
  in_ECX[0xc1b] = 0;
  in_ECX[0xc1c] = 0;
  in_ECX[0xc1f] = 0;
  in_ECX[0xc20] = 0;
  in_ECX[0xc21] = 0;
  in_ECX[0xc22] = 0;
  in_ECX[0xc23] = 0;
  in_ECX[0xc24] = 0;
  return;
}



// ==== 0x40540b ====

void FUN_0040540b(void)

{
  FUN_00404f9c();
  FUN_00404f9c();
  FUN_00404f9c();
  FUN_00404f9c();
  FUN_00404f9c();
  return;
}



// ==== 0x40544b ====

void FUN_0040544b(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = FUN_00404fb1();
  *(undefined4 *)(iVar1 + 0x20) = 1;
  FUN_0041d7b0(iVar1,param_1);
  *(undefined4 *)(iVar1 + 0x10) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0x14) = param_2;
  *(undefined4 *)(iVar1 + 0x18) = param_3;
  *(undefined4 *)(iVar1 + 0x1c) = param_4;
  return;
}



// ==== 0x40547a ====

void FUN_0040547a(void)

{
  int *piVar1;
  int iVar2;
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x305c) = 0;
  if (*(char *)(in_ECX + 0xc) != '\0') {
    *(undefined1 *)(in_ECX + 0xc) = 0;
  }
  *(undefined4 *)(in_ECX + 0x3034) = *(undefined4 *)(in_ECX + 0x3030);
  *(undefined4 *)(in_ECX + 0x3040) = *(undefined4 *)(in_ECX + 0x303c);
  *(undefined4 *)(in_ECX + 0x2c) = 0;
  iVar2 = FUN_00404fb1();
  piVar1 = (int *)(in_ECX + 0x3064);
  *piVar1 = iVar2;
  *(undefined4 *)(iVar2 + 0x20) = 1;
  FUN_0041d7b0(*piVar1,&PTR_DAT_0042c2d8);
  *(undefined4 *)(*piVar1 + 0x10) = 0xffffffff;
  iVar2 = *piVar1;
  *(undefined4 *)(iVar2 + 0x14) = *(undefined4 *)(in_ECX + 0x10);
  *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)(in_ECX + 0x14);
  *(undefined4 *)(iVar2 + 0x1c) = *(undefined4 *)(in_ECX + 0x18);
  return;
}



// ==== 0x4054df ====

void FUN_004054df(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int in_ECX;
  int *piVar2;
  
  *(undefined4 *)(in_ECX + 0x305c) = 0;
  if (*(char *)(in_ECX + 0xc) != '\0') {
    *(undefined1 *)(in_ECX + 0xc) = 0;
  }
  *(undefined4 *)(in_ECX + 0x3034) = *(undefined4 *)(in_ECX + 0x3030);
  *(undefined4 *)(in_ECX + 0x3040) = *(undefined4 *)(in_ECX + 0x303c);
  *(undefined4 *)(in_ECX + 0x1c) = 0xffffffff;
  *(undefined4 *)(in_ECX + 0x10) = param_1;
  *(undefined4 *)(in_ECX + 0x14) = param_2;
  *(undefined4 *)(in_ECX + 0x18) = param_3;
  *(undefined4 *)(in_ECX + 0x20) = param_1;
  *(undefined4 *)(in_ECX + 0x24) = param_2;
  *(undefined4 *)(in_ECX + 0x3078) = 0;
  *(undefined4 *)(in_ECX + 0x2c) = 0;
  *(undefined4 *)(in_ECX + 0x28) = param_3;
  iVar1 = FUN_00404fb1();
  piVar2 = (int *)(in_ECX + 0x3064);
  *piVar2 = iVar1;
  *(undefined4 *)(iVar1 + 0x20) = 1;
  FUN_0041d7b0(*piVar2,&PTR_DAT_0042c2d8);
  *(undefined4 *)(*piVar2 + 0x10) = 0xffffffff;
  iVar1 = *piVar2;
  *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(in_ECX + 0x10);
  *(undefined4 *)(iVar1 + 0x18) = *(undefined4 *)(in_ECX + 0x14);
  *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(in_ECX + 0x18);
  return;
}



// ==== 0x40556c ====

void FUN_0040556c(undefined4 *param_1)

{
  int in_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_00405034();
  }
  puVar2 = *(undefined4 **)(in_ECX + 4);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 0x1c;
  return;
}



// ==== 0x405594 ====

void FUN_00405594(undefined4 *param_1)

{
  int in_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_0040507d();
  }
  puVar2 = *(undefined4 **)(in_ECX + 4);
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 0x18;
  return;
}



// ==== 0x4055bc ====

void FUN_004055bc(undefined4 *param_1)

{
  undefined4 *puVar1;
  int in_ECX;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_004050ca();
  }
  puVar1 = *(undefined4 **)(in_ECX + 4);
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 8;
  return;
}



// ==== 0x4055e5 ====

void FUN_004055e5(undefined4 *param_1)

{
  undefined4 *puVar1;
  int in_ECX;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_00405110();
  }
  puVar1 = *(undefined4 **)(in_ECX + 4);
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  puVar1[2] = param_1[2];
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 0xc;
  return;
}



// ==== 0x40560b ====

undefined1 * FUN_0040560b(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  undefined1 *puVar4;
  
  puVar4 = param_1;
  if (param_2 == (undefined1 *)0x0) {
    iVar2 = FUN_0040515d(*param_1);
    if (iVar2 != 0) {
      iVar2 = 0xe;
      while( true ) {
        param_1 = param_1 + 1;
        iVar3 = FUN_0040522e(*param_1);
        if (iVar3 == 0) break;
        if (iVar2 == 0) {
          if (*(char *)(in_ECX + 0xc) != '\0') {
            return param_1;
          }
          *(undefined1 *)(in_ECX + 0xc) = 1;
          *(char **)(in_ECX + 8) = "identifier too long";
          return param_1;
        }
        iVar2 = iVar2 + -1;
      }
    }
  }
  else {
    uVar1 = *param_1;
    iVar2 = FUN_0040515d(uVar1);
    if (iVar2 != 0) {
      *param_2 = uVar1;
      param_1 = (undefined1 *)0xe;
      while( true ) {
        puVar4 = puVar4 + 1;
        param_2 = param_2 + 1;
        uVar1 = *puVar4;
        iVar2 = FUN_0040522e(uVar1);
        if (iVar2 == 0) break;
        if (param_1 == (undefined1 *)0x0) {
          *param_2 = 0;
          if (*(char *)(in_ECX + 0xc) != '\0') {
            return puVar4;
          }
          *(undefined1 *)(in_ECX + 0xc) = 1;
          *(char **)(in_ECX + 8) = "identifier too long";
          return puVar4;
        }
        *param_2 = uVar1;
        param_1 = (undefined1 *)((int)param_1 + -1);
      }
    }
    param_1 = puVar4;
    *param_2 = 0;
  }
  return param_1;
}



// ==== 0x4056c6 ====

void FUN_004056c6(undefined1 *param_1)

{
  int in_ECX;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_004052ca();
  }
  **(undefined1 **)(in_ECX + 4) = *param_1;
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 1;
  return;
}



// ==== 0x4056e8 ====

void FUN_004056e8(void)

{
  int *piVar1;
  undefined1 *puVar2;
  int in_ECX;
  
  puVar2 = _malloc(0x128);
  piVar1 = (int *)(in_ECX + 0x3074);
  *(int *)(puVar2 + 0x120) = *piVar1;
  *(undefined4 *)(puVar2 + 0x124) = 0;
  if (*piVar1 != 0) {
    *(undefined1 **)(*piVar1 + 0x124) = puVar2;
  }
  *piVar1 = (int)puVar2;
  *(undefined4 *)(puVar2 + 0x110) = 0;
  *puVar2 = 0;
  *(undefined4 *)(puVar2 + 0x114) = 0;
  *(undefined4 *)(puVar2 + 0x118) = 0;
  *(undefined4 *)(puVar2 + 0x11c) = 0;
  return;
}



// ==== 0x405734 ====

int FUN_00405734(char param_1)

{
  char *pcVar1;
  int in_ECX;
  int iVar2;
  
  iVar2 = 0;
  if (0 < (int)(*(int *)(in_ECX + 0x3080) - *(int *)(in_ECX + 0x307c) & 0xfffffff8U)) {
    do {
      pcVar1 = (char *)FUN_004052a9(iVar2);
      if (param_1 == *pcVar1) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(in_ECX + 0x3080) - *(int *)(in_ECX + 0x307c) >> 3);
  }
  return -1;
}



// ==== 0x405773 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00405773(undefined4 param_1)

{
  undefined1 local_18 [16];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  FUN_0040560b(param_1,local_18);
  FUN_0040517f(local_18);
  return;
}



// ==== 0x4057a8 ====

void FUN_004057a8(undefined4 *param_1)

{
  int in_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)(in_ECX + 8) <= *(uint *)(in_ECX + 4)) {
    FUN_0040533e();
  }
  puVar2 = *(undefined4 **)(in_ECX + 4);
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 0x30;
  return;
}



// ==== 0x4057d0 ====

void FUN_004057d0(void)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)FUN_00404761(local_10,0x40490fdb);
  FUN_0040544b(&DAT_0042c2f4,*puVar1,puVar1[1],puVar1[2]);
  fVar2 = (float10)FUN_0041ce90(0x3ff0000000000000);
  puVar1 = (undefined4 *)FUN_00404761(local_10,(float)fVar2);
  FUN_0040544b(&DAT_0042c2f0,*puVar1,puVar1[1],puVar1[2]);
  return;
}



// ==== 0x40583a ====

void FUN_0040583a(int param_1,int param_2)

{
  if (0 < param_1) {
    do {
      FUN_00405594(param_2);
      param_2 = param_2 + 0x18;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  return;
}



// ==== 0x405863 ====

void FUN_00405863(int param_1,int param_2)

{
  int in_ECX;
  char *pcVar1;
  
  if (0 < param_1) {
    pcVar1 = (char *)(param_2 + 1);
    do {
      if (*(int *)(in_ECX + 0x3078) < (int)*pcVar1) {
        *(int *)(in_ECX + 0x3078) = (int)*pcVar1;
      }
      FUN_004055bc(pcVar1 + -1);
      pcVar1 = pcVar1 + 8;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  return;
}



// ==== 0x4058aa ====

void FUN_004058aa(undefined4 *param_1)

{
  int in_ECX;
  undefined4 *puVar1;
  
  if (*(int *)(in_ECX + 0x2c) == 0) {
    puVar1 = (undefined4 *)(in_ECX + 0x10);
  }
  else {
    for (puVar1 = *(undefined4 **)(in_ECX + 0x3030); puVar1 < *(undefined4 **)(in_ECX + 0x3034);
        puVar1 = puVar1 + 7) {
      (*(code *)*puVar1)(puVar1 + 1);
    }
    puVar1 = (undefined4 *)(in_ECX + (*(int *)(in_ECX + 0x3048) + 4) * 0xc);
  }
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}



// ==== 0x4058f0 ====

void FUN_004058f0(undefined4 param_1)

{
  FILE *_File;
  int *piVar1;
  int in_ECX;
  int iVar2;
  float *pfVar3;
  uint uVar4;
  int local_8;
  
  _File = (FILE *)FUN_0041d331(param_1);
  iVar2 = 0;
  if (0 < *(int *)(in_ECX + 0x2c)) {
    pfVar3 = (float *)(in_ECX + 0x34);
    do {
      piVar1 = (int *)FUN_00404fee();
      if (*piVar1 == -1) {
        _fprintf(_File,"Const: r%d = %g,%g,%g\n",iVar2,(double)pfVar3[-1],(double)*pfVar3,
                 (double)pfVar3[1]);
      }
      iVar2 = iVar2 + 1;
      pfVar3 = pfVar3 + 3;
    } while (iVar2 < *(int *)(in_ECX + 0x2c));
  }
  for (uVar4 = *(uint *)(in_ECX + 0x303c); uVar4 < *(uint *)(in_ECX + 0x3040); uVar4 = uVar4 + 0x30)
  {
    _fprintf(_File,"%s r%d, ",uVar4 + 0x20);
    local_8 = 0;
    if (0 < *(int *)(uVar4 + 4)) {
      do {
        _fprintf(_File,(char *)&PTR_DAT_0042c30c);
        if (local_8 != *(int *)(uVar4 + 4) + -1) {
          _fprintf(_File,",");
        }
        local_8 = local_8 + 1;
      } while (local_8 < *(int *)(uVar4 + 4));
    }
    _fprintf(_File,"\n");
  }
  _fprintf(_File,"RESULT: r%d\n");
  _fclose(_File);
  return;
}



// ==== 0x4059f9 ====

char * FUN_004059f9(char *param_1,char *param_2,char *param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  
  iVar4 = 0;
  if (0 < (*(int *)(in_ECX + 0x306c) - *(int *)(in_ECX + 0x3068)) / 0x18) {
    do {
      pcVar2 = (char *)FUN_00405285(iVar4);
      iVar3 = _strcmp(param_1,pcVar2);
      if (iVar3 == 0) {
        if (*(char *)(in_ECX + 0xc) != '\0') {
          return (char *)0x0;
        }
        *(char **)(in_ECX + 8) = "Default function cannot be overriden";
        goto LAB_00405ba1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (*(int *)(in_ECX + 0x306c) - *(int *)(in_ECX + 0x3068)) / 0x18);
  }
  iVar4 = FUN_00405258(param_1);
  if (iVar4 == 0) {
    iVar4 = FUN_004056e8();
  }
  FUN_0041d7b0(iVar4,param_1);
  FUN_00405012(&param_2);
  *(undefined4 *)(iVar4 + 0x110) = 0;
  pcVar2 = param_2;
  do {
    if ((*pcVar2 == ')') || (*pcVar2 == '\0')) {
      FUN_00405012(&param_3);
      if (*param_3 == '{') {
        param_3 = param_3 + 1;
        FUN_00405012(&param_3);
        pcVar2 = param_3;
        *(undefined4 *)(iVar4 + 0x118) = *(undefined4 *)(iVar4 + 0x114);
        param_3 = (char *)0x0;
        cVar1 = *pcVar2;
        while ((cVar1 != '\0' && ((cVar1 != '}' || (param_3 != (char *)0x0))))) {
          if (cVar1 == '{') {
            param_3 = (char *)((int)param_3 + 1);
          }
          if (cVar1 == '}') {
            param_3 = (char *)((int)param_3 - 1);
          }
          FUN_004056c6(pcVar2);
          pcVar2 = pcVar2 + 1;
          cVar1 = *pcVar2;
        }
        param_3 = (char *)((uint)param_3 & 0xffffff);
        FUN_004056c6((int)&param_3 + 3);
        if (*pcVar2 != '\0') {
          return pcVar2 + 1;
        }
        if (*(char *)(in_ECX + 0xc) != '\0') {
          return (char *)0x0;
        }
        *(char **)(in_ECX + 8) = "function definition not closed by }";
      }
      else {
        if (*(char *)(in_ECX + 0xc) != '\0') {
          return (char *)0x0;
        }
        *(char **)(in_ECX + 8) = "{ expected to define function";
      }
LAB_00405ba1:
      *(undefined1 *)(in_ECX + 0xc) = 1;
      return (char *)0x0;
    }
    iVar3 = *(int *)(iVar4 + 0x110);
    *(int *)(iVar4 + 0x110) = iVar3 + 1;
    param_2 = (char *)FUN_0040560b(pcVar2,(iVar3 + 1) * 0x10 + iVar4);
    FUN_00405012(&param_2);
    cVar1 = *param_2;
    if (((cVar1 != ')') && (cVar1 != ',')) ||
       (*(char *)(*(int *)(iVar4 + 0x110) * 0x10 + iVar4) == '\0')) {
      *(undefined4 *)(iVar4 + 0x110) = 0;
      *(undefined4 *)(iVar4 + 0x118) = *(undefined4 *)(iVar4 + 0x114);
      if (*(char *)(in_ECX + 0xc) != '\0') {
        return (char *)0x0;
      }
      *(char **)(in_ECX + 8) = "Parameter variables exlected";
      goto LAB_00405ba1;
    }
    pcVar2 = param_2;
    if (cVar1 == ',') {
      pcVar2 = param_2 + 1;
    }
  } while( true );
}



// ==== 0x405bb3 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00405bb3(int *param_1,code *param_2,int param_3,int *param_4,undefined4 param_5)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  int *piVar6;
  int local_9c [15];
  int *local_60;
  undefined4 auStack_5c [5];
  int local_48;
  int local_44;
  int iStack_40;
  int iStack_3c;
  code *local_38;
  int local_34;
  int local_30;
  int aiStack_2c [5];
  undefined1 local_18 [16];
  undefined4 local_8;
  
  iVar5 = 0;
  local_8 = DAT_00453d68;
  if (0 < param_3) {
    piVar3 = local_9c;
    piVar6 = param_4;
    do {
      if (*piVar6 != -1) break;
      *piVar3 = piVar6[1];
      piVar2 = piVar3 + 2;
      piVar1 = piVar6 + 3;
      piVar3[1] = piVar6[2];
      auStack_5c[iVar5] = piVar3;
      iVar5 = iVar5 + 1;
      piVar6 = piVar6 + 4;
      piVar3 = piVar3 + 3;
      *piVar2 = *piVar1;
    } while (iVar5 < param_3);
  }
  local_60 = &local_44;
  if (iVar5 == param_3) {
    local_48 = -1;
    (*param_2)(&local_60);
  }
  else {
    iVar5 = 0;
    local_38 = param_2;
    if (0 < param_3) {
      do {
        iVar4 = *param_4;
        if (iVar4 == -1) {
          iVar4 = *(int *)(in_ECX + 0x2c);
          piVar3 = (int *)(in_ECX + (iVar4 * 3 + 0xc) * 4);
          *piVar3 = param_4[1];
          piVar3[1] = param_4[2];
          piVar3[2] = param_4[3];
          *(int *)(in_ECX + 0x2c) = *(int *)(in_ECX + 0x2c) + 1;
        }
        aiStack_2c[iVar5] = iVar4;
        iVar5 = iVar5 + 1;
        param_4 = param_4 + 4;
      } while (iVar5 < param_3);
    }
    FUN_0041d7b0(local_18,param_5);
    local_34 = param_3;
    local_48 = *(int *)(in_ECX + 0x2c);
    piVar3 = (int *)(in_ECX + (local_48 * 3 + 0xc) * 4);
    *piVar3 = *(int *)(in_ECX + 0x10);
    piVar3[1] = *(int *)(in_ECX + 0x14);
    piVar3[2] = *(int *)(in_ECX + 0x18);
    *(int *)(in_ECX + 0x2c) = *(int *)(in_ECX + 0x2c) + 1;
    local_44 = *(int *)(in_ECX + 0x10);
    iStack_40 = *(int *)(in_ECX + 0x14);
    iStack_3c = *(int *)(in_ECX + 0x18);
    local_30 = local_48;
    FUN_004057a8(&local_38);
  }
  *param_1 = local_48;
  param_1[1] = local_44;
  param_1[2] = iStack_40;
  param_1[3] = iStack_3c;
  return;
}



// ==== 0x405ca7 ====

void FUN_00405ca7(void)

{
  FUN_004054df(0,0,0);
  FUN_00405863(5,&DAT_00453540);
  FUN_0040583a(0xc,s_atanxy_00453420);
  return;
}



// ==== 0x405cf2 ====

undefined4 * FUN_00405cf2(void)

{
  undefined4 *extraout_ECX;
  int unaff_EBP;
  
  FUN_0041cc3c();
  *(undefined4 **)(unaff_EBP + -0x10) = extraout_ECX;
  FUN_004053ba();
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *extraout_ECX = &PTR_FUN_0042c3c0;
  FUN_00405ca7();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return extraout_ECX;
}



// ==== 0x405d28 ====

void FUN_00405d28(void)

{
  if (DAT_004eac6c == '\0') {
    FUN_00405ca7();
    FUN_0040583a(6,s_addbox_00453568);
    DAT_004eac6c = '\x01';
  }
  return;
}



// ==== 0x405d55 ====

void FUN_00405d55(void)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int in_ECX;
  int iVar5;
  uint uVar6;
  int local_3c;
  int local_38;
  int aiStack_34 [5];
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int *local_14;
  int *local_10;
  int local_c;
  int *local_8;
  
  *(undefined4 *)(in_ECX + 0x3034) = *(undefined4 *)(in_ECX + 0x3030);
  *(int *)(in_ECX + 0x308c) = *(int *)(in_ECX + 0x3088);
  iVar5 = 0;
  if (*(int *)(in_ECX + 0x2c) == 0) {
    *(undefined4 *)(in_ECX + 0x3048) = 0;
  }
  else {
    if (0 < *(int *)(in_ECX + 0x2c)) {
      local_20 = 0xffffffff;
      local_1c = 0xffffffff;
      do {
        local_18 = iVar5;
        FUN_004055e5(&local_20);
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(in_ECX + 0x2c));
    }
    uVar6 = *(uint *)(in_ECX + 0x303c);
    local_c = 0;
    if (uVar6 < *(uint *)(in_ECX + 0x3040)) {
      do {
        piVar1 = (int *)FUN_00404fee(*(undefined4 *)(uVar6 + 8));
        if (*piVar1 == -1) {
          piVar1 = (int *)FUN_00404fee(*(undefined4 *)(uVar6 + 8));
          *piVar1 = local_c;
        }
        local_10 = (int *)0x0;
        if (0 < *(int *)(uVar6 + 4)) {
          local_8 = (int *)(uVar6 + 0xc);
          do {
            iVar5 = FUN_00404fee(*local_8);
            local_10 = (int *)((int)local_10 + 1);
            local_8 = local_8 + 1;
            *(int *)(iVar5 + 4) = local_c;
          } while ((int)local_10 < *(int *)(uVar6 + 4));
        }
        local_c = local_c + 1;
        uVar6 = uVar6 + 0x30;
      } while (uVar6 < *(uint *)(in_ECX + 0x3040));
    }
    if (*(int *)(in_ECX + 0x3048) < (*(int *)(in_ECX + 0x308c) - *(int *)(in_ECX + 0x3088)) / 0xc) {
      iVar5 = FUN_00404fee(*(int *)(in_ECX + 0x3048));
      *(int *)(iVar5 + 4) = local_c;
    }
    else {
      *(undefined4 *)(in_ECX + 0x3048) = 0;
    }
    local_c = 0;
    if (*(uint *)(in_ECX + 0x303c) < *(uint *)(in_ECX + 0x3040)) {
      piVar1 = (int *)(*(uint *)(in_ECX + 0x303c) + 8);
      do {
        local_3c = piVar1[-2];
        local_8 = (int *)0x0;
        local_14 = piVar1;
        if (0 < piVar1[-1]) {
          local_10 = piVar1 + 1;
          do {
            iVar5 = FUN_00404fee(*local_10);
            iVar5 = *(int *)(iVar5 + 8);
            *local_10 = iVar5;
            aiStack_34[(int)local_8] = in_ECX + (iVar5 + 4) * 0xc;
            local_8 = (int *)((int)local_8 + 1);
            local_10 = local_10 + 1;
          } while ((int)local_8 < piVar1[-1]);
        }
        iVar5 = FUN_00404fee(*piVar1);
        local_10 = *(int **)(iVar5 + 8);
        local_8 = (int *)0x0;
        if (0 < *(int *)(in_ECX + 0x2c)) {
          do {
            iVar5 = FUN_00404fee(local_8);
            if (*(int *)(iVar5 + 4) <= local_c) {
              piVar2 = (int *)FUN_00404fee(local_8);
              if ((-1 < *piVar2) && (local_8 != local_10)) {
                iVar5 = FUN_00404fee(local_8);
                if (*(int *)(iVar5 + 4) != -1) {
                  puVar3 = (undefined4 *)FUN_00404fee(local_10);
                  puVar4 = (undefined4 *)FUN_00404fee(local_8);
                  *puVar4 = *puVar3;
                  puVar4[1] = puVar3[1];
                  puVar4[2] = puVar3[2];
                  iVar5 = FUN_00404fee(local_10);
                  *(int **)(iVar5 + 8) = local_8;
                  local_8 = *(int **)(in_ECX + 0x2c);
                  piVar1 = local_14;
                }
              }
            }
            local_8 = (int *)((int)local_8 + 1);
          } while ((int)local_8 < *(int *)(in_ECX + 0x2c));
        }
        iVar5 = FUN_00404fee(*piVar1);
        iVar5 = *(int *)(iVar5 + 8);
        *piVar1 = iVar5;
        local_38 = in_ECX + (iVar5 * 3 + 0xc) * 4;
        FUN_0040556c(&local_3c);
        local_c = local_c + 1;
        local_14 = piVar1 + 0xc;
        piVar2 = piVar1 + 10;
        piVar1 = local_14;
      } while (piVar2 < *(int **)(in_ECX + 0x3040));
    }
    iVar5 = FUN_00404fee(*(undefined4 *)(in_ECX + 0x3048));
    *(undefined4 *)(in_ECX + 0x3048) = *(undefined4 *)(iVar5 + 8);
    FUN_004058f0("asm.txt");
  }
  return;
}



// ==== 0x405fb5 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00405fb5(undefined4 *param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int in_ECX;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined4 local_498 [4];
  undefined4 local_488 [252];
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 local_78 [16];
  int local_68;
  int local_64;
  undefined4 local_60;
  int local_5c;
  int local_58;
  undefined4 *local_54;
  int local_50;
  undefined4 local_4c;
  char local_48 [64];
  undefined4 local_8;
  
  local_50 = 0;
  local_8 = DAT_00453d68;
  local_4c = local_498;
  do {
    puVar2 = (undefined4 *)FUN_00406587(local_78,param_2);
    puVar6 = local_4c;
    cVar1 = *(char *)(in_ECX + 0xc);
    puVar7 = local_4c + 1;
    *local_4c = *puVar2;
    *puVar7 = puVar2[1];
    puVar6[2] = puVar2[2];
    puVar6[3] = puVar2[3];
    if (cVar1 != '\0') goto LAB_004061f0;
    puVar7 = (undefined4 *)(in_ECX + 4);
    FUN_00405012(puVar7);
    cVar1 = *(char *)*puVar7;
    if ((((cVar1 != '\0') && (cVar1 != ';')) && (cVar1 != ')')) && (cVar1 != ',')) {
      *puVar7 = (char *)*puVar7 + 1;
      cVar1 = FUN_00405734(cVar1);
      local_48[local_50] = cVar1;
      if (cVar1 == -1) {
        if (*(char *)(in_ECX + 0xc) == '\0') {
          *(undefined1 *)(in_ECX + 0xc) = 1;
          *(char **)(in_ECX + 8) = "Operator expected";
        }
        goto LAB_004061f0;
      }
    }
    local_50 = local_50 + 1;
    local_4c = local_4c + 4;
  } while (((*(char *)(in_ECX + 0xc) == '\0') && (cVar1 = *(char *)*puVar7, cVar1 != '\0')) &&
          ((cVar1 != ';' && ((cVar1 != ')' && (cVar1 != ','))))));
  cVar1 = **(char **)(in_ECX + 4);
  if (cVar1 == ')') {
    if (param_2 == 0) {
      if (*(char *)(in_ECX + 0xc) == '\0') {
        *(undefined1 *)(in_ECX + 0xc) = 1;
        *(char **)(in_ECX + 8) = "Unexpected )";
      }
    }
    else {
LAB_004060c1:
      *(char **)(in_ECX + 4) = *(char **)(in_ECX + 4) + 1;
LAB_004060c5:
      local_5c = *(int *)(in_ECX + 0x3078);
      while (-1 < local_5c) {
        local_58 = 1;
        param_2 = 1;
        if (1 < local_50) {
          local_54 = local_488;
          local_4c = local_498;
          local_64 = (int)&local_4c + 3;
          do {
            puVar7 = local_4c;
            local_68 = (int)*(char *)(local_64 + param_2);
            iVar3 = FUN_004052a9(local_68);
            puVar6 = local_54;
            iVar5 = local_58;
            if (*(char *)(iVar3 + 1) == local_5c) {
              local_98 = *puVar7;
              uStack_94 = puVar7[1];
              uStack_90 = puVar7[2];
              uStack_8c = puVar7[3];
              local_88 = *local_54;
              uStack_84 = local_54[1];
              uStack_80 = local_54[2];
              uStack_7c = local_54[3];
              local_60 = &DAT_0058706f;
              puVar4 = (undefined1 *)FUN_004052a9(local_68);
              local_60._0_3_ = CONCAT12(*puVar4,(undefined2)local_60);
              puVar7 = &local_60;
              puVar6 = &local_98;
              uVar8 = 2;
              iVar5 = FUN_004052a9(local_68);
              puVar6 = (undefined4 *)
                       FUN_00405bb3(local_78,*(undefined4 *)(iVar5 + 4),uVar8,puVar6,puVar7);
              local_54 = local_54 + 4;
              *(char *)(local_64 + local_58) = local_48[param_2];
              puVar7 = local_4c;
            }
            else {
              puVar7 = puVar7 + 4;
              local_54 = local_54 + 4;
              local_58 = local_58 + 1;
              local_4c = local_4c + 4;
              local_48[iVar5] = local_48[param_2];
            }
            iVar5 = local_50;
            param_2 = param_2 + 1;
            *puVar7 = *puVar6;
            puVar7[1] = puVar6[1];
            puVar7[2] = puVar6[2];
            puVar7[3] = puVar6[3];
          } while (param_2 < iVar5);
        }
        local_5c = local_5c + -1;
        local_50 = local_58;
      }
      if (local_50 != 1) {
        if (*(char *)(in_ECX + 0xc) != '\0') goto LAB_004061f0;
        *(undefined1 *)(in_ECX + 0xc) = 1;
        *(char **)(in_ECX + 8) = "Unknown Error";
      }
      if (*(char *)(in_ECX + 0xc) == '\0') {
        puVar7 = local_498;
        goto LAB_004061fb;
      }
    }
  }
  else {
    if (param_2 == 0) {
      if (cVar1 == ')') goto LAB_004060c1;
      goto LAB_004060c5;
    }
    if (*(char *)(in_ECX + 0xc) == '\0') {
      *(undefined1 *)(in_ECX + 0xc) = 1;
      *(char **)(in_ECX + 8) = "Expected )";
    }
  }
LAB_004061f0:
  puVar7 = (undefined4 *)(in_ECX + 0x1c);
LAB_004061fb:
  *param_1 = *puVar7;
  param_1[1] = puVar7[1];
  param_1[2] = puVar7[2];
  param_1[3] = puVar7[3];
  return;
}



// ==== 0x406216 ====

undefined4 FUN_00406216(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int in_ECX;
  undefined1 local_24 [16];
  int local_14;
  
  *(undefined4 *)(in_ECX + 4) = param_1;
  piVar4 = (int *)FUN_00405fb5(local_24,0);
  local_14 = *piVar4;
  iVar1 = piVar4[1];
  iVar2 = piVar4[2];
  iVar3 = piVar4[3];
  *(int *)(in_ECX + 0x304c) = local_14;
  *(int *)(in_ECX + 0x3050) = iVar1;
  *(int *)(in_ECX + 0x3054) = iVar2;
  *(int *)(in_ECX + 0x3058) = iVar3;
  if (local_14 == -1) {
    local_14 = *(int *)(in_ECX + 0x2c);
    piVar4 = (int *)(in_ECX + (local_14 * 3 + 0xc) * 4);
    *piVar4 = iVar1;
    piVar4[1] = iVar2;
    piVar4[2] = iVar3;
    *(int *)(in_ECX + 0x2c) = *(int *)(in_ECX + 0x2c) + 1;
  }
  *(int *)(in_ECX + 0x3048) = local_14;
  return *(undefined4 *)(in_ECX + 4);
}



// ==== 0x406277 ====

int FUN_00406277(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int in_ECX;
  undefined1 local_28 [16];
  undefined1 local_18 [16];
  int local_8;
  
  local_8 = 0;
  while( true ) {
    param_2 = param_2 + -1;
    if (param_2 < 1) {
      puVar1 = (undefined4 *)FUN_00405fb5(local_28,1);
      *param_1 = *puVar1;
      param_1[1] = puVar1[1];
      param_1[2] = puVar1[2];
      param_1[3] = puVar1[3];
    }
    else {
      puVar1 = (undefined4 *)FUN_00405fb5(local_18,0);
      *param_1 = *puVar1;
      param_1[1] = puVar1[1];
      param_1[2] = puVar1[2];
      param_1[3] = puVar1[3];
      if (**(char **)(in_ECX + 4) != ',') {
        if (*(char *)(in_ECX + 0xc) != '\0') {
          return 0;
        }
        *(undefined1 *)(in_ECX + 0xc) = 1;
        *(char **)(in_ECX + 8) = "More parameters expected";
        return 0;
      }
      *(char **)(in_ECX + 4) = *(char **)(in_ECX + 4) + 1;
    }
    local_8 = local_8 + 1;
    param_1 = param_1 + 4;
    if (*(char *)(in_ECX + 0xc) != '\0') break;
    if (param_2 == 0) {
      return local_8;
    }
  }
  return 0;
}



// ==== 0x406306 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * FUN_00406306(char *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char cVar5;
  int iVar6;
  char *pcVar7;
  undefined4 *puVar8;
  int in_ECX;
  char *pcVar9;
  char *pcVar10;
  int local_6c [12];
  undefined1 local_3c [32];
  char *local_1c;
  char local_18 [16];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  if (*param_1 == '\0') {
    return (char *)0x0;
  }
  FUN_00405012(&param_1);
  pcVar7 = param_1;
  iVar6 = FUN_0040515d(*param_1);
  if (iVar6 == 0) {
    pcVar7 = (char *)FUN_00406216(pcVar7);
    return pcVar7;
  }
  local_1c = (char *)FUN_0040560b(pcVar7,local_18);
  FUN_00405012(&local_1c);
  iVar6 = _strcmp(local_18,"repeat");
  pcVar9 = local_1c;
  if (iVar6 == 0) {
    if (*local_1c == '(') {
      local_1c = local_1c + 1;
      FUN_00405012(&local_1c);
      piVar1 = (int *)(in_ECX + 4);
      *piVar1 = (int)local_1c;
      FUN_00406277(local_6c,1);
      if (local_6c[0] == -1) {
        param_1 = (char *)FUN_0041d384();
        if ((int)param_1 < 0) {
          if (*(char *)(in_ECX + 0xc) != '\0') {
            return (char *)0x0;
          }
          *(char **)(in_ECX + 8) = "Parameter of repeat cannot be negative";
        }
        else {
          FUN_00405012(piVar1);
          if (*(char *)*piVar1 == '{') {
            pcVar7 = (char *)*piVar1 + 1;
            *piVar1 = (int)pcVar7;
            if (0 < (int)param_1) {
              do {
                *piVar1 = (int)pcVar7;
                iVar6 = FUN_004051cc(pcVar7);
                param_1 = (char *)((int)param_1 + -1);
                *piVar1 = iVar6;
              } while (param_1 != (char *)0x0);
            }
            if (*(char *)*piVar1 == '}') {
              pcVar7 = (char *)*piVar1 + 1;
              *piVar1 = (int)pcVar7;
              return pcVar7;
            }
            if (*(char *)(in_ECX + 0xc) != '\0') {
              return (char *)0x0;
            }
            *(char **)(in_ECX + 8) = "{ for repeat must be closed by }";
          }
          else {
            if (*(char *)(in_ECX + 0xc) != '\0') {
              return (char *)0x0;
            }
            *(char **)(in_ECX + 8) = "{ expected for repeat";
          }
        }
      }
      else {
        if (*(char *)(in_ECX + 0xc) != '\0') {
          return (char *)0x0;
        }
        *(char **)(in_ECX + 8) = "Parameter of repeat must be definit";
      }
    }
    else {
      if (*(char *)(in_ECX + 0xc) != '\0') {
        return (char *)0x0;
      }
      *(char **)(in_ECX + 8) = "( expected after repeat";
    }
  }
  else {
    if (*local_1c != '=') {
      if (*local_1c == '(') {
        pcVar10 = local_1c + 1;
        cVar5 = *pcVar10;
        pcVar9 = pcVar10;
        while ((cVar5 != '\0' && (cVar5 != '('))) {
          if (cVar5 == ')') goto LAB_004064f2;
          pcVar9 = pcVar9 + 1;
          cVar5 = *pcVar9;
        }
        if (*pcVar9 == ')') {
LAB_004064f2:
          local_1c = pcVar9 + 1;
          FUN_00405012(&local_1c);
          if (*local_1c == '=') {
            pcVar7 = (char *)FUN_004059f9(local_18,pcVar10,local_1c + 1);
            return pcVar7;
          }
        }
      }
      pcVar7 = (char *)FUN_00406216(pcVar7);
      return pcVar7;
    }
    local_1c = (char *)FUN_0040517f(local_18);
    if (local_1c == (char *)0x0) {
      local_1c = (char *)FUN_00404fb1();
      FUN_0041d7b0(local_1c,local_18);
    }
    if ((local_1c[0x20] & 1U) == 0) {
      *(char **)(in_ECX + 4) = pcVar9 + 1;
      puVar8 = (undefined4 *)FUN_00405fb5(local_3c,0);
      uVar2 = puVar8[1];
      uVar3 = puVar8[2];
      uVar4 = puVar8[3];
      *(undefined4 *)(local_1c + 0x10) = *puVar8;
      *(undefined4 *)(local_1c + 0x14) = uVar2;
      *(undefined4 *)(local_1c + 0x18) = uVar3;
      *(undefined4 *)(local_1c + 0x1c) = uVar4;
      return *(char **)(in_ECX + 4);
    }
    if (*(char *)(in_ECX + 0xc) != '\0') {
      return (char *)0x0;
    }
    *(char **)(in_ECX + 8) = "Constant cannot be modified";
  }
  *(undefined1 *)(in_ECX + 0xc) = 1;
  return (char *)0x0;
}



// ==== 0x40652f ====

void FUN_0040652f(char *param_1)

{
  char *pcVar1;
  int in_ECX;
  
  pcVar1 = param_1;
  if (param_1 != (char *)0x0) {
    do {
      if (*pcVar1 != ';') break;
      pcVar1 = pcVar1 + 1;
    } while (pcVar1 != (char *)0x0);
    while ((((pcVar1 != (char *)0x0 && (*pcVar1 != '\0')) && (*(char *)(in_ECX + 0xc) == '\0')) &&
           (param_1 = (char *)FUN_00406306(pcVar1), *(char *)(in_ECX + 0xc) == '\0'))) {
      for (; (param_1 != (char *)0x0 && (*param_1 == ';')); param_1 = param_1 + 1) {
      }
      FUN_00405012(&param_1);
      pcVar1 = param_1;
    }
  }
  return;
}



// ==== 0x406587 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * FUN_00406587(undefined4 *param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 *in_ECX;
  int iVar7;
  undefined8 uVar8;
  undefined4 local_414 [64];
  undefined4 local_314;
  undefined4 local_310;
  undefined4 uStack_30c;
  undefined4 uStack_308;
  undefined1 local_304 [4];
  undefined1 local_300 [4];
  undefined8 local_2fc;
  undefined4 *local_2f4;
  int local_2f0;
  undefined8 local_2ec;
  char *local_2e4;
  undefined4 *local_2e0;
  byte local_2d9;
  undefined1 local_2d8 [16];
  char local_2c8 [688];
  char local_18 [16];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  local_2e0 = in_ECX + 7;
  local_314 = *local_2e0;
  local_310 = in_ECX[8];
  uStack_30c = in_ECX[9];
  uStack_308 = in_ECX[10];
  local_2d9 = 0;
  piVar1 = in_ECX + 1;
  while (pcVar4 = (char *)*piVar1, *pcVar4 == ' ') {
    *piVar1 = *piVar1 + 1;
  }
  cVar2 = *pcVar4;
  if (cVar2 == '(') {
    *piVar1 = (int)(pcVar4 + 1);
    FUN_00405fb5(param_1,param_2 + 1);
    return param_1;
  }
  while (cVar2 == '-') {
    local_2d9 = local_2d9 ^ 1;
    *piVar1 = *piVar1 + 1;
    FUN_00405012();
    cVar2 = *(char *)*piVar1;
  }
  iVar7 = *piVar1;
  iVar3 = FUN_0040515d();
  if (iVar3 == 0) {
    iVar7 = FUN_00405326();
    if (iVar7 != 0) {
      local_2ec = 1.0;
      local_2fc = 0.0;
      do {
        pcVar4 = (char *)*piVar1;
        cVar2 = *pcVar4;
        *piVar1 = (int)(pcVar4 + 1);
        local_2fc = local_2fc * 10.0 + (double)(cVar2 + -0x30);
        iVar7 = FUN_00405326();
      } while (iVar7 != 0);
      if (pcVar4[1] == '.') {
        pcVar4 = pcVar4 + 2;
        *piVar1 = (int)pcVar4;
        while (iVar7 = FUN_00405326(), iVar7 != 0) {
          cVar2 = *pcVar4;
          local_2ec = local_2ec * 0.1;
          pcVar4 = pcVar4 + 1;
          *piVar1 = (int)pcVar4;
          local_2fc = (double)(cVar2 + -0x30) * local_2ec + local_2fc;
        }
      }
      if (local_2d9 != 0) {
        local_2fc = -local_2fc;
      }
      local_314 = 0xffffffff;
      puVar5 = (undefined4 *)(**(code **)*in_ECX)(local_300,local_2fc);
      local_310 = *puVar5;
      uStack_30c = puVar5[1];
      uStack_308 = puVar5[2];
LAB_00406980:
      local_2e0 = &local_314;
      goto LAB_00406983;
    }
    if (*(char *)(in_ECX + 3) != '\0') goto LAB_00406983;
    in_ECX[2] = "Value or ( expected";
  }
  else {
    local_2e4 = (char *)FUN_0040560b(iVar7,local_18);
    FUN_00405012();
    if (*local_2e4 == '(') {
      *piVar1 = (int)(local_2e4 + 1);
      iVar7 = 0;
      if (0 < (int)(in_ECX[0xc1b] - in_ECX[0xc1a]) / 0x18) {
        do {
          pcVar4 = (char *)FUN_00405285();
          iVar3 = _strcmp(local_18,pcVar4);
          if (iVar3 == 0) {
            iVar3 = FUN_00405285();
            FUN_00406277(local_414,*(undefined4 *)(iVar3 + 0x10));
            if (*(char *)(in_ECX + 3) != '\0') goto LAB_00406983;
            uVar6 = FUN_00405285();
            uVar8 = CONCAT44(uVar6,local_414);
            iVar3 = FUN_00405285(iVar7);
            uVar6 = *(undefined4 *)(iVar3 + 0x10);
            iVar7 = FUN_00405285(iVar7);
            puVar5 = (undefined4 *)FUN_00405bb3(local_304,*(undefined4 *)(iVar7 + 0x14),uVar6,uVar8)
            ;
            goto LAB_0040683c;
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < (int)(in_ECX[0xc1b] - in_ECX[0xc1a]) / 0x18);
      }
      iVar7 = FUN_00405258();
      local_2ec = (double)CONCAT44(iVar7,(undefined4)local_2ec);
      if (iVar7 == 0) {
        if (*(char *)(in_ECX + 3) != '\0') goto LAB_00406983;
        in_ECX[2] = "Undefined Function";
      }
      else {
        uVar6 = in_ECX[0xc18];
        local_2fc._4_4_ = uVar6;
        if (*(int *)(iVar7 + 0x110) == 0) {
          FUN_00405012();
          pcVar4 = (char *)in_ECX[1];
          if (*pcVar4 != ')') {
            if (*(char *)(in_ECX + 3) == '\0') {
              *(undefined1 *)(in_ECX + 3) = 1;
              in_ECX[2] = "No parameter expected";
            }
            in_ECX[0xc18] = local_2fc._4_4_;
            goto LAB_00406983;
          }
          in_ECX[1] = pcVar4 + 1;
        }
        else {
          FUN_00406277(local_414,*(int *)(iVar7 + 0x110));
          if (*(char *)(in_ECX + 3) != '\0') {
            in_ECX[0xc18] = uVar6;
            goto LAB_00406983;
          }
          iVar3 = 0;
          param_2 = 0;
          if (0 < *(int *)(iVar7 + 0x110)) {
            local_2e4 = local_2c8;
            local_2f0 = iVar7 + 0x10;
            local_2f4 = local_414;
            do {
              pcVar4 = local_2e4;
              FUN_0041d7b0(local_2e4 + -0x10,local_2f0);
              local_2e4[0x10] = '\0';
              local_2e4[0x11] = '\0';
              local_2e4[0x12] = '\0';
              local_2e4[0x13] = '\0';
              local_2e4[0x18] = '\0';
              local_2e4[0x19] = '\0';
              local_2e4[0x1a] = '\0';
              local_2e4[0x1b] = '\0';
              iVar3 = param_2 + 1;
              local_2f0 = local_2f0 + 0x10;
              puVar5 = local_2f4 + 4;
              *(undefined4 *)pcVar4 = *local_2f4;
              *(undefined4 *)(pcVar4 + 4) = local_2f4[1];
              *(char **)(local_2e4 + 0x14) = local_2e4 + 0x1c;
              *(undefined4 *)(pcVar4 + 8) = local_2f4[2];
              local_2e4 = local_2e4 + 0x2c;
              *(undefined4 *)(pcVar4 + 0xc) = local_2f4[3];
              param_2 = iVar3;
              local_2f4 = puVar5;
            } while (iVar3 < *(int *)(local_2ec._4_4_ + 0x110));
          }
          (&local_2e0)[iVar3 * 0xb] = (undefined4 *)0x0;
          in_ECX[0xc18] = local_2d8;
        }
        local_2ec._4_4_ = in_ECX[1];
        uVar6 = FUN_00405308();
        in_ECX[1] = uVar6;
        FUN_0040652f();
        in_ECX[1] = local_2ec._4_4_;
        puVar5 = in_ECX + 0xc13;
        in_ECX[0xc18] = local_2fc._4_4_;
LAB_0040683c:
        local_314 = *puVar5;
        local_310 = puVar5[1];
        uStack_30c = puVar5[2];
        uStack_308 = puVar5[3];
        if (local_2d9 == 0) goto LAB_00406980;
        if (*(char *)(in_ECX + 3) != '\0') goto LAB_00406983;
        in_ECX[2] = "minus not supported now";
      }
    }
    else {
      iVar7 = FUN_00405773();
      if (iVar7 != 0) {
        iVar3 = FUN_0040560b(*piVar1,0);
        *piVar1 = iVar3;
        local_2e0 = (undefined4 *)(iVar7 + 0x10);
        goto LAB_00406983;
      }
      if (*(char *)(in_ECX + 3) != '\0') goto LAB_00406983;
      in_ECX[2] = "No such command or variable";
    }
  }
  *(undefined1 *)(in_ECX + 3) = 1;
LAB_00406983:
  *param_1 = *local_2e0;
  param_1[1] = local_2e0[1];
  param_1[2] = local_2e0[2];
  param_1[3] = local_2e0[3];
  return param_1;
}



// ==== 0x4069a7 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004069a7(undefined *param_1)

{
  FILE *_File;
  size_t _Count;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  FILE *_File_00;
  undefined4 local_60 [9];
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 *local_c;
  char local_5;
  
  DAT_004e7bb0 = 0;
  DAT_00c06b50 = 0;
  DAT_00c06b58 = 0;
  DAT_00c06978 = 0;
  DAT_00c06b5c = 0;
  DAT_00c06b40 = 0xffffffff;
  DAT_00c06b44 = 0xffffffff;
  _DAT_00c06b48 = 0xffffffff;
  _DAT_00c06b4c = 0xffffffff;
  FUN_004083d2();
  _memset(&DAT_00521e00,0,0xf400);
  local_18 = 0;
  DAT_00561404 = &DAT_00521e00;
  local_10 = 0;
  local_14 = 0xc1a00000;
  local_24 = 0x42c80000;
  local_20 = 0xc1200000;
  local_1c = 0x42c80000;
  PTR_DAT_00453858 = (undefined *)&DAT_00c06b60;
  DAT_00467b4c = FUN_00408d57(0x42c80000,0xc1200000,0x42c80000,0,0xc1a00000,0,1,0x3d800000);
  FUN_004089b4();
  DAT_00467b4c = 0;
  if (DAT_00d0f9f8 != 0) {
    GetWindowTextA(DAT_00467b48,&DAT_00467bb0,0x80000);
    _File = (FILE *)FUN_0041d331("edited.txt",&DAT_0042c5b4);
    _File_00 = _File;
    _Count = _strlen(&DAT_00467bb0);
    _fwrite(&DAT_00467bb0,1,_Count,_File_00);
    _fclose(_File);
    param_1 = &DAT_00467bb0;
  }
  FUN_0040547a();
  FUN_004057d0();
  _DAT_004eac38 = 0;
  FUN_0040652f(param_1);
  if (DAT_00d0f9f8 == 0) {
    if (DAT_004e7be4 != '\0') {
      MessageBoxA((HWND)0x0,DAT_004e7be0,"Error in MOD file",0x30);
    }
  }
  else if (DAT_004e7be4 == '\0') {
    SetWindowTextA(DAT_004e7bd4,"Sumotori Dreams level editor");
    FUN_00405d55();
    FUN_004058aa(&local_3c);
  }
  else {
    SetWindowTextA(DAT_004e7bd4,DAT_004e7be0);
  }
  if (DAT_00467b4c != 0) {
    puVar3 = (undefined4 *)(DAT_00467b4c + 0x60);
    puVar4 = local_60;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    local_c = *(undefined4 **)(DAT_00467b4c + 0x54);
    local_5 = *(char *)(DAT_00467b4c + 0xd0);
    FUN_00408e51(1);
    FUN_004086da();
    FUN_004087a4();
    FUN_00408b34();
    if (local_5 != '\0') {
      FUN_004089b4();
    }
    puVar3 = local_60;
    puVar4 = (undefined4 *)(DAT_00467b4c + 0x60);
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 **)(DAT_00467b4c + 0x54) = local_c;
  }
  local_c = &DAT_00c06b60;
  if (&DAT_00c06b60 < PTR_DAT_00453858) {
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    do {
      local_30 = local_24;
      uStack_2c = local_20;
      uStack_28 = local_1c;
      local_3c = local_18;
      uStack_38 = local_14;
      uStack_34 = local_10;
      uVar1 = FUN_0041041d(&local_3c,&local_30);
      local_c[0x1c0] = uVar1;
      local_c = local_c + 0x1cc;
    } while (local_c < PTR_DAT_00453858);
  }
  if (DAT_004e7be4 != '\0') {
    DAT_00561404 = &DAT_00521e00;
    PTR_DAT_00453858 = (undefined *)&DAT_00c06b60;
    DAT_00561408 = &DAT_00746c30;
  }
  thunk_FUN_00408c36();
  return;
}



// ==== 0x406c59 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406c59(undefined4 param_1)

{
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0040d4c8();
  _DAT_00c06808 = 0x43160000;
  FUN_00405d28();
  FUN_004169a7(1);
  FUN_00407d7a(6);
  local_10 = 0x42700000;
  local_c = 0x420c0000;
  local_8 = 0xc2c20000;
  local_1c = 0x42700000;
  uStack_18 = 0x420c0000;
  uStack_14 = 0xc2c20000;
  FUN_00402827(&local_1c,0,0);
  FUN_00407db4();
  _DAT_00511dfc = 4;
  FUN_004069a7(param_1);
  return;
}



// ==== 0x406cd2 ====

LRESULT FUN_00406cd2(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  LRESULT LVar1;
  
  if (param_2 == 5) {
    MoveWindow(DAT_00467b48,0,0,(param_4 & 0xffff) - 0x1e,param_4 >> 0x10,1);
  }
  else {
    if (param_2 == 0x10) {
      DAT_00d0f9fc = 1;
      return 0;
    }
    if ((param_2 == 0x111) && ((short)(param_3 >> 0x10) == 0x300)) {
      FUN_004069a7(0);
    }
  }
  LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar1;
}



// ==== 0x406d45 ====

void FUN_00406d45(HINSTANCE param_1)

{
  FILE *_File;
  size_t sVar1;
  HWND hWndParent;
  HFONT wParam;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  WNDCLASSEXA local_34;
  
  _File = (FILE *)FUN_0041d331("edited.txt",&DAT_0042c278);
  if (_File != (FILE *)0x0) {
    sVar1 = _fread(&DAT_00467bb0,1,0x7ffff,_File);
    (&DAT_00467bb0)[sVar1] = 0;
    _fclose(_File);
  }
  local_34.cbSize = 0x30;
  local_34.style = 0x40;
  local_34.lpfnWndProc = FUN_00406cd2;
  local_34.cbClsExtra = 0;
  local_34.cbWndExtra = 0;
  local_34.hInstance = GetModuleHandleA((LPCSTR)0x0);
  local_34.hIcon = (HICON)0x0;
  local_34.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_34.hbrBackground = CreateSolidBrush(0x504030);
  local_34.lpszMenuName = (LPCSTR)0x0;
  local_34.lpszClassName = "gameeditor";
  local_34.hIconSm = (HICON)0x0;
  RegisterClassExA(&local_34);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = param_1;
  hWndParent = GetDesktopWindow();
  DAT_004e7bd4 = CreateWindowExA(0,"gameeditor","Sumotori Editor",0xcf0000,200,700,800,300,
                                 hWndParent,hMenu,hInstance,lpParam);
  DAT_00467b48 = CreateWindowExA(0,"edit",&DAT_00467bb0,0x50300004,0x14,0x14,400,0x96,DAT_004e7bd4,
                                 (HMENU)0x0,param_1,(LPVOID)0x0);
  wParam = CreateFontA(0xd,0,0,0,700,0,0,0,1,0,0,4,2,"Lucida Console");
  SendMessageA(DAT_00467b48,0x30,(WPARAM)wParam,1);
  ShowWindow(DAT_004e7bd4,1);
  return;
}



// ==== 0x406e8a ====

void FUN_00406e8a(float *param_1)

{
  float fVar1;
  float fVar2;
  float *in_ECX;
  
  fVar1 = in_ECX[1];
  fVar2 = in_ECX[2];
  *param_1 = -*in_ECX;
  param_1[1] = -fVar1;
  param_1[2] = -fVar2;
  return;
}



// ==== 0x406eba ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406eba(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  float10 fVar10;
  undefined1 local_214 [12];
  undefined1 local_208 [12];
  undefined1 local_1fc [12];
  undefined1 local_1f0 [12];
  undefined1 local_1e4 [12];
  undefined1 local_1d8 [12];
  undefined1 local_1cc [12];
  undefined1 local_1c0 [12];
  undefined1 local_1b4 [12];
  undefined4 local_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 local_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  int local_190;
  int iStack_18c;
  int iStack_188;
  undefined4 local_184;
  float fStack_180;
  undefined4 uStack_17c;
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  int local_16c;
  int iStack_168;
  int iStack_164;
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 local_154;
  float fStack_150;
  undefined4 uStack_14c;
  undefined4 local_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  int local_120;
  int local_11c;
  int local_118;
  int local_114;
  int local_110;
  int local_10c;
  int local_108;
  int local_104;
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  int local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  undefined4 local_dc;
  float local_d8;
  undefined4 local_d4;
  int local_d0 [4];
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  float local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  float local_7c [4];
  int local_6c [4];
  int local_5c;
  int local_58;
  float local_54;
  int local_50;
  int local_4c;
  int local_48;
  float local_44;
  int local_40;
  int local_3c;
  float local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  int local_20 [2];
  float local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  if (DAT_00d0f9f8 == 0) {
    DAT_00c06978 = 0;
    FUN_004169a7(1);
    DAT_00453ce0 = 0xffffffff;
    DAT_00c06b50 = 10;
    FUN_00410527(0);
    local_24 = 0x3f800000;
    local_20[1] = 0x3f800000;
    _DAT_00c06808 = 0x42a00000;
    DAT_00562c10 = 0;
    local_7c[0] = -7.0;
    local_7c[1] = 7.0;
    local_7c[2] = 7.0;
    local_d0[0] = 3;
    local_d0[1] = 3;
    local_d0[2] = 4;
    local_6c[0] = 4;
    local_6c[1] = 4;
    local_6c[2] = 3;
    local_10 = -4;
    local_30 = 0xc2a00000;
    local_2c = 0x41700000;
    local_20[0] = -0x3e380000;
    do {
      local_28 = (float)local_10 * 7.0;
      FUN_00408d57(local_24,local_20[0],local_20[1],local_30,local_2c,local_28,1,0x3e000000);
      FUN_004089b4();
      local_10 = local_10 + 1;
    } while (local_10 < 5);
    local_28 = 0.0;
    local_30 = 0xc2a00000;
    local_2c = 0x42200000;
    local_24 = 0x40800000;
    local_20[0] = -0x40400000;
    local_20[1] = 0x41f00000;
    iVar6 = FUN_00408d57(0x40800000,0xbfc00000,0x41f00000,0xc2a00000,0x42200000,0,1,0x3e000000);
    FUN_004089b4();
    local_28 = 0.0;
    local_2c = 0;
    local_40 = DAT_004eac7c + 4;
    local_30 = 0;
    local_3c = 0;
    local_10 = 1;
    if (DAT_004eac7c == 0) {
      local_10 = 3;
      local_28 = 20.0;
    }
    if (DAT_004eac7c == 3) {
      local_10 = 2;
      local_6c[0] = 0;
      local_3c = 2;
      local_40 = 4;
    }
    if (DAT_004eac7c == 1) {
      local_28 = 10.0;
      local_10 = 2;
      local_6c[1] = 2;
      local_3c = 0;
      local_40 = 7;
    }
    local_48 = 0;
    local_5c = iVar6;
    if (local_10 != 0) {
      local_148 = 0xc0a00000;
      uStack_144 = 0;
      uStack_140 = 0xc0e00000;
      local_24 = 0xc0a00000;
      local_1a8 = 0xc0a00000;
      uStack_1a4 = 0;
      uStack_1a0 = 0x40e00000;
      do {
        iVar6 = local_48;
        local_20[0] = local_5c;
        local_20[1] = local_5c;
        piVar7 = (int *)FUN_00402172(local_214,&local_30);
        local_16c = *piVar7;
        iStack_168 = piVar7[1];
        iStack_164 = piVar7[2];
        puVar8 = (undefined4 *)FUN_00402172(local_1b4,&local_30);
        local_14 = 0;
        local_160 = *puVar8;
        uStack_15c = puVar8[1];
        uStack_158 = puVar8[2];
        local_18 = 40.0;
        local_50 = local_6c[iVar6];
        if (0 < local_6c[iVar6]) {
          local_a4 = 0;
          local_4c = local_d0[iVar6];
          local_d0[3] = 0x3f19999a;
          local_bc = 0x41100000;
          local_ac = 0xc2aa0000;
          local_dc = 0x3f19999a;
          local_6c[3] = local_40 + iVar6;
          local_58 = iVar6 * 0x10 + 1;
          local_d4 = 0x41100000;
          local_f4 = 0;
          local_f0 = 0x3f800000;
          local_ec = 0;
          local_10c = 0x3f800000;
          local_108 = 0;
          local_104 = 0;
          local_124 = 0;
          local_120 = 0x3f800000;
          local_11c = 0;
          local_13c = 0x3f800000;
          local_138 = 0;
          local_134 = 0;
          do {
            local_34 = 0;
            if (0 < local_4c) {
              local_12c = 0x3f666666;
              local_a0 = 0x3f000000;
              local_9c = 0xbf666666;
              local_98 = 0x3f000000;
              local_118 = 0;
              local_114 = 0x3f800000;
              local_110 = 0;
              local_100 = 0x3f800000;
              local_fc = 0;
              local_f8 = 0;
              local_88 = 0;
              local_84 = -0x4099999a;
              local_80 = 0;
              local_130 = 0;
              local_128 = 0;
              local_e8 = 0;
              local_e4 = 0x3f800000;
              local_e0 = 0;
              local_94 = 0x3f800000;
              local_90 = 0;
              local_8c = 0;
              do {
                local_c = 0;
                local_8 = &local_16c;
                local_54 = local_18 + 0.9;
                local_44 = (float)local_34 * 0.0;
                do {
                  puVar8 = (undefined4 *)
                           FUN_00402279(local_1f0,0xc2aa0000,local_54,
                                        *(undefined4 *)((int)local_7c + local_c));
                  local_19c = *puVar8;
                  uStack_198 = puVar8[1];
                  uStack_194 = puVar8[2];
                  puVar8 = (undefined4 *)FUN_00402172(local_1d8,&local_30);
                  iVar6 = FUN_00408d57(local_a0,local_9c,local_98,*puVar8,puVar8[1],puVar8[2],0,
                                       0x3e000000);
                  FUN_004025ed(local_44);
                  piVar9 = local_8;
                  *(float *)(iVar6 + 0xb4) = *(float *)(iVar6 + 0xb4) * 3.0;
                  *(float *)(iVar6 + 0xb8) = *(float *)(iVar6 + 0xb8) * 0.33333334;
                  piVar7 = (int *)((int)local_20 + local_c);
                  *DAT_00561404 = *piVar7;
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 3;
                  DAT_00561404[2] = *local_8;
                  *piVar3 = local_8[1];
                  piVar4[4] = local_8[2];
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 9;
                  DAT_00561404[8] = local_118;
                  *piVar3 = local_114;
                  piVar4[10] = local_110;
                  piVar3 = DAT_00561404;
                  if ((local_34 == 0) && (local_14 == 0)) {
                    local_b8 = 0;
                    local_b4 = 0xbf800000;
                    local_b0 = 0;
                    piVar4 = DAT_00561404 + 9;
                    DAT_00561404[8] = 0;
                    *piVar4 = -0x40800000;
                    piVar3[10] = 0;
                  }
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 0xf;
                  DAT_00561404[0xe] = local_100;
                  *piVar3 = local_fc;
                  piVar4[0x10] = local_f8;
                  DAT_00561404[1] = DAT_00561408 + -0xfc;
                  piVar4 = DAT_00561404;
                  piVar3 = DAT_00561404 + 6;
                  DAT_00561404[5] = local_88;
                  *piVar3 = local_84;
                  piVar4[7] = local_80;
                  piVar4 = DAT_00561404;
                  piVar3 = local_8 + 1;
                  *local_8 = local_130;
                  *piVar3 = local_12c;
                  piVar9[2] = local_128;
                  piVar3 = DAT_00561404 + 0xc;
                  DAT_00561404[0xb] = local_e8;
                  *piVar3 = local_e4;
                  piVar4[0xd] = local_e0;
                  piVar4 = DAT_00561404;
                  local_c = local_c + 4;
                  local_8 = local_8 + 3;
                  piVar3 = DAT_00561404 + 0x12;
                  DAT_00561404[0x11] = local_94;
                  *piVar3 = local_90;
                  piVar4[0x13] = local_8c;
                  *piVar7 = iVar6;
                  DAT_00561404[0x15] = 0x3f4f5c29;
                  DAT_00561404[0x16] = 0x3f9ae148;
                  DAT_00561404[0x14] = 0;
                  DAT_00561404 = DAT_00561404 + 0x3d;
                } while (local_c < 8);
                local_34 = local_34 + 1;
                local_18 = local_18 + 1.8;
              } while (local_34 < local_4c);
            }
            local_38 = 1.8;
            if (local_48 == 2) {
              local_38 = 1.9;
              if (local_14 == 1) {
                if (DAT_004eac84 == 0) goto LAB_00407494;
                local_3c = 1;
              }
              if ((local_14 == 2) && (DAT_004eac84 == 0)) {
                local_3c = 1;
              }
            }
LAB_00407494:
            fStack_180 = local_38 + local_18;
            local_184 = local_ac;
            local_c0 = -local_38;
            uStack_17c = local_a4;
            local_a8 = fStack_180;
            local_8 = (int *)local_c0;
            puVar8 = (undefined4 *)FUN_00402172(local_208,&local_30);
            iVar6 = FUN_00408d57(local_d0[3],local_c0,local_bc,*puVar8,puVar8[1],puVar8[2],
                                 local_6c[3],0xbd638e39);
            *(int *)(iVar6 + 0xbc) = local_58 + local_14;
            local_44 = (float)(local_14 + local_3c);
            fStack_150 = (float)local_8 - (float)(int)local_44 * 2.953125;
            local_154 = local_dc;
            uStack_14c = local_d4;
            local_d8 = fStack_150;
            puVar8 = (undefined4 *)FUN_00406e8a(local_1c0);
            *(undefined4 *)(iVar6 + 0x20) = *puVar8;
            *(undefined4 *)(iVar6 + 0x24) = puVar8[1];
            *(undefined4 *)(iVar6 + 0x28) = puVar8[2];
            *(float *)(iVar6 + 0xac) = *(float *)(iVar6 + 0xac) * 0.03;
            *(float *)(iVar6 + 0xb0) = *(float *)(iVar6 + 0xb0) * 33.333336;
            *(float *)(iVar6 + 0xa8) = *(float *)(iVar6 + 0xa8) * 0.03;
            *(float *)(iVar6 + 0xb4) = *(float *)(iVar6 + 0xb4) * 0.03;
            *(undefined4 *)(iVar6 + 0xc0) = 2;
            *(float *)(iVar6 + 0xb8) = *(float *)(iVar6 + 0xb8) * 33.333336;
            *(undefined4 *)(iVar6 + 0xc4) = 0x40400000;
            fVar10 = (float10)FUN_0040b798(0);
            fVar10 = (float10)FUN_0040b798((float)(fVar10 * (float10)0.26));
            puVar8 = (undefined4 *)
                     FUN_00402279(local_1cc,(float)((fVar10 + (float10)1.0) * (float10)-0.04));
            local_178 = *puVar8;
            uStack_174 = puVar8[1];
            local_18 = local_38 + local_38 + local_18;
            uStack_170 = puVar8[2];
            *(undefined4 *)(iVar6 + 0x9c) = local_178;
            local_7c[3] = (float)local_8;
            *(undefined4 *)(iVar6 + 0xa0) = uStack_174;
            local_8 = &local_16c;
            *(undefined4 *)(iVar6 + 0xa4) = uStack_170;
            *(undefined4 *)(iVar6 + 0x54) = 0x41700000;
            local_c = 0;
            do {
              uVar2 = *(undefined4 *)((int)local_7c + local_c);
              *DAT_00561404 = *(int *)((int)local_20 + local_c);
              piVar3 = DAT_00561404;
              piVar7 = DAT_00561404 + 3;
              DAT_00561404[2] = *local_8;
              *piVar7 = local_8[1];
              piVar3[4] = local_8[2];
              piVar3 = DAT_00561404;
              piVar7 = DAT_00561404 + 9;
              DAT_00561404[8] = local_f4;
              *piVar7 = local_f0;
              piVar3[10] = local_ec;
              piVar3 = DAT_00561404;
              piVar7 = DAT_00561404 + 0xf;
              DAT_00561404[0xe] = local_10c;
              *piVar7 = local_108;
              piVar3[0x10] = local_104;
              DAT_00561404[1] = DAT_00561408 + -0xfc;
              piVar7 = (int *)FUN_00402279(local_1e4,0,local_7c[3],uVar2);
              piVar3 = DAT_00561404;
              uVar2 = *(undefined4 *)((int)local_7c + local_c);
              local_190 = *piVar7;
              iStack_18c = piVar7[1];
              iStack_188 = piVar7[2];
              piVar7 = DAT_00561404 + 6;
              DAT_00561404[5] = local_190;
              *piVar7 = iStack_18c;
              piVar3[7] = iStack_188;
              piVar9 = (int *)FUN_00402279(local_1fc,0,local_38,uVar2);
              piVar4 = local_8;
              piVar3 = DAT_00561404;
              piVar7 = local_8 + 1;
              *local_8 = *piVar9;
              *piVar7 = piVar9[1];
              piVar4[2] = piVar9[2];
              iVar5 = local_c;
              piVar7 = DAT_00561404 + 0xc;
              DAT_00561404[0xb] = local_124;
              *piVar7 = local_120;
              piVar3[0xd] = local_11c;
              piVar3 = DAT_00561404;
              piVar7 = DAT_00561404 + 0x12;
              DAT_00561404[0x11] = local_13c;
              *piVar7 = local_138;
              piVar3[0x13] = local_134;
              DAT_00561404[0x15] = 0x3f4f5c28;
              DAT_00561404[0x16] = 0x3f9ae148;
              local_8 = local_8 + 3;
              DAT_00561404[0x14] = 0;
              iVar1 = local_c + 4;
              local_c = iVar1;
              DAT_00561404 = DAT_00561404 + 0x3d;
              *(int *)((int)local_20 + iVar5) = iVar6;
            } while (iVar1 < 8);
            local_14 = local_14 + 1;
          } while (local_14 < local_50);
        }
        local_28 = local_28 - 20.0;
        local_48 = local_48 + 1;
      } while (local_48 < local_10);
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



// ==== 0x407794 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407794(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  puVar1 = (undefined4 *)
           FUN_00402279(local_1c,((float)DAT_00453ce0 + _DAT_0045509c) * _DAT_004550a0,
                        -(((float)_DAT_00d0fa04 + _DAT_00455094) * _DAT_00455098),0x3f800000);
  local_10 = *puVar1;
  uStack_c = puVar1[1];
  uStack_8 = puVar1[2];
  puVar1 = (undefined4 *)FUN_004023c6(local_1c,&DAT_00c06954);
  local_10 = *puVar1;
  uStack_c = puVar1[1];
  uStack_8 = puVar1[2];
  FUN_004022c1();
  *param_1 = local_10;
  param_1[1] = uStack_c;
  param_1[2] = uStack_8;
  return;
}



// ==== 0x407818 ====

void FUN_00407818(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004eac74 = DAT_004eac74 + -1;
  if (DAT_00453ce0 != -1) {
    if (DAT_004eac74 < 1) {
      DAT_004eac74 = 0x3c;
      puVar1 = (undefined4 *)FUN_00407794(&local_2c);
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      local_8 = 0x42480000;
      uVar2 = FUN_00402227(&local_20,&local_8);
      FUN_00402172(&local_2c,uVar2);
      local_14 = 0x40a00000;
      local_10 = 0;
      local_c = 0x40800000;
      local_20 = 0x40a00000;
      uStack_1c = 0;
      uStack_18 = 0x40800000;
      uVar2 = FUN_004023c6(&local_14,&DAT_00c06954);
      FUN_00402172(&local_20,uVar2);
      FUN_00410342(local_20,uStack_1c,uStack_18,local_2c,uStack_28,uStack_24,0x41f00000,2);
    }
    DAT_00453ce0 = -1;
  }
  FUN_0040b985(0xbe4ccccd,0x3f0ccccd,"Hidden Part",0xb08f8fff);
  if (DAT_00c06978 < 1000) {
    FUN_0040b985(0x3e4ccccd,0x3f19999a,
                 "Controls:\nHome/PageUp = Move Camera\nMouse Click = Punish!!!\nEsc      = leave",
                 0xb0ffffff);
  }
  if (&DAT_0075f5f0 < DAT_00561408) {
    FUN_00406eba();
  }
  return;
}



// ==== 0x40795f ====

void FUN_0040795f(char param_1)

{
  undefined4 uVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  if (&DAT_00753110 < DAT_00561408) {
    FUN_00406eba();
  }
  uVar4 = 2;
  if (DAT_00562c10 == 0) {
    DAT_004eac78 = 0xff;
    goto LAB_00407ae5;
  }
  DAT_004eac78 = DAT_004eac78 + -2;
  if (DAT_004eac78 < 1) {
    if (DAT_004eac7c == 0) {
      if (DAT_00562c10 < 0x13) {
        if (DAT_00562c10 == 0x12) {
          DAT_004535f8 = 3;
          uVar4 = DAT_004535f8;
          goto LAB_00407aa0;
        }
        if (DAT_00562c10 == 1) {
LAB_00407a92:
          DAT_004eac80 = uVar4;
          DAT_004535f8 = 2;
          uVar1 = DAT_004535f8;
          uVar4 = DAT_004eac80;
        }
        else if (DAT_00562c10 == 2) {
          DAT_004535f8 = 3;
          uVar1 = DAT_004535f8;
        }
        else {
          uVar1 = 4;
          if (DAT_00562c10 != 3) {
            if (DAT_00562c10 == 4) {
              DAT_004eac80 = 0;
              uVar4 = DAT_004eac80;
            }
            else {
              if (DAT_00562c10 != 6) {
                if (DAT_00562c10 != 0x11) goto LAB_00407aaf;
                goto LAB_00407aa0;
              }
              DAT_004eac80 = 0;
              DAT_004535f8 = 1;
              uVar1 = DAT_004535f8;
              uVar4 = DAT_004eac80;
            }
          }
        }
      }
      else {
        if (DAT_00562c10 != 0x13) {
          if (DAT_00562c10 == 0x14) {
            DAT_004eac80 = 0;
            uVar4 = DAT_004eac80;
            goto LAB_00407a92;
          }
          if (DAT_00562c10 == 0x21) {
            DAT_004eac7c = 1;
          }
          else {
            if (DAT_00562c10 != 0x22) {
              if (DAT_00562c10 == 0x23) {
                DAT_00d0f9fc = 1;
              }
              goto LAB_00407aaf;
            }
            DAT_004eac84 = DAT_004eac84 ^ 1;
          }
          goto LAB_004079cc;
        }
        DAT_004535f8 = 4;
        uVar4 = DAT_004535f8;
LAB_00407aa0:
        DAT_004535f8 = uVar4;
        DAT_004eac80 = 1;
        uVar1 = DAT_004535f8;
        uVar4 = DAT_004eac80;
      }
      DAT_004eac80 = uVar4;
      DAT_004535f8 = uVar1;
      FUN_00410a7e();
    }
    else if (DAT_004eac7c == 1) {
      DAT_00467340 = 0;
      DAT_004eac7c = 0;
      DAT_004eac70 = DAT_00562c10 % 0x10 + -1 + (DAT_00562c10 / 0x10) * 4;
LAB_004079cc:
      FUN_00406eba();
    }
  }
LAB_00407aaf:
  local_8 = (float)(DAT_004eac78 << 8);
  FUN_0041d134((double)(int)local_8);
  iVar2 = FUN_0041d384();
  DAT_00ac66f4 = iVar2 * 0x10101;
LAB_00407ae5:
  DAT_004eac74 = DAT_004eac74 + -1;
  if (DAT_00453ce0 != -1) {
    if (DAT_004eac74 < 1) {
      DAT_004eac74 = 0x3c;
      pfVar3 = (float *)FUN_00407794();
      local_14 = *pfVar3;
      local_10 = pfVar3[1];
      local_c = pfVar3[2];
      local_8 = (DAT_00c06948 + 84.0) / local_14;
      uVar4 = FUN_00402227(local_2c,&local_8);
      FUN_004021a7(&local_20,uVar4);
      local_c = 0.0;
      local_14 = -120.0;
      local_10 = 10.0;
      FUN_00410342(0xc2f00000,0x41200000,0,local_20,uStack_1c,uStack_18,0x41f00000);
    }
    DAT_00453ce0 = -1;
  }
  if (DAT_00d0fa08 != 0) {
    DAT_00d0f9fc = 1;
  }
  if (param_1 != '\0') {
    if (DAT_004eac7c == 3) {
      FUN_0040b985(0xbf59999a,0x3ecccccd);
      DAT_00ac66f4 = (((DAT_00ac66f4 & 0xff00) * 3) / 4 & 0xff00) +
                     ((int)DAT_00ac66f4 / 2 & 0x7f007fU);
    }
    FUN_0040b985(0xbe4ccccd,0x3f0f5c29,"Sumotori Dreams Full",0xc08080ff);
    FUN_0040b985(0x3e8a3d71,0xbf000000,"\"Tested on party animals\"",0xc0ffffff);
    FUN_0040b985(0xbf59999a,0xbf000000,"www.gravitysensation.com/sumotori",0xc0ffffff);
  }
  return;
}



// ==== 0x407ca6 ====

void FUN_00407ca6(void)

{
  return;
}



// ==== 0x407ca7 ====

size_t FUN_00407ca7(void *param_1,size_t param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = param_3[1];
  if (*param_3 <= (int)(iVar1 + param_2)) {
    param_2 = *param_3 - iVar1;
  }
  _memcpy(param_1,(void *)(param_3[2] + iVar1),param_2);
  param_3[1] = param_3[1] + param_2;
  return param_2;
}



// ==== 0x407cdc ====

void FUN_00407cdc(int *param_1,int param_2,char param_3)

{
  if (param_3 != '\0') {
    if (param_3 == '\x01') {
      param_1[1] = param_1[1] + param_2;
      goto LAB_00407d09;
    }
    if (param_3 != '\x02') goto LAB_00407d09;
    param_2 = *param_1 + param_2;
  }
  param_1[1] = param_2;
LAB_00407d09:
  if (*param_1 < param_1[1]) {
    param_1[1] = *param_1;
  }
  return;
}



// ==== 0x407d1d ====

void FUN_00407d1d(void)

{
  if (DAT_00c0f220 != '\0') {
    FUN_00419023(&LAB_00407c85,FUN_00407ca6,FUN_00407ca7,FUN_00407cdc,&LAB_00407d15);
    FUN_004171d9(0xac44,0);
    DAT_004eacd0 = FUN_00416f38(&DAT_0042c718,0);
    FUN_00416d7e(DAT_004eacd0);
  }
  return;
}



// ==== 0x407d6b ====

void FUN_00407d6b(void)

{
  DAT_00d0fa18 = 3;
  FUN_00407d1d();
  return;
}



// ==== 0x407d7a ====

void FUN_00407d7a(undefined4 param_1)

{
  if (DAT_00c0f220 != '\0') {
    FUN_00416cad(DAT_004eacd0);
    FUN_00416f90();
    DAT_00d0fa18 = param_1;
    FUN_00407d1d();
    return;
  }
  return;
}



// ==== 0x407da3 ====

void FUN_00407da3(void)

{
  FUN_00416c19(DAT_004eacd0);
  FUN_00416f90();
  return;
}



// ==== 0x407db4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407db4(void)

{
  DAT_00c06978 = 0;
  _DAT_004536d8 = 0xffffffff;
  _DAT_00511df0 = 0;
  _DAT_004536dc = 1;
  FUN_00402d01();
  return;
}



// ==== 0x407dd8 ====

void FUN_00407dd8(int param_1)

{
  if (0xff < param_1) {
    param_1 = 0xff;
  }
  if (DAT_00d0f9f8 != 0) {
    param_1 = 0xff;
  }
  DAT_00ac66f4 = (param_1 * param_1 >> 8) * 0x101 + param_1 * 0x10000;
  return;
}



// ==== 0x407e0c ====

void FUN_00407e0c(void)

{
  FUN_00407dd8(DAT_00c06978 << 3);
  return;
}



// ==== 0x407e1c ====

void FUN_00407e1c(float *param_1)

{
  float *in_ECX;
  
  *in_ECX = *in_ECX - *param_1;
  in_ECX[1] = in_ECX[1] - param_1[1];
  in_ECX[2] = in_ECX[2] - param_1[2];
  return;
}



// ==== 0x407e3b ====

void FUN_00407e3b(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *in_ECX;
  
  uVar1 = in_ECX[1];
  uVar2 = in_ECX[2];
  *param_1 = *in_ECX;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x407e65 ====

void FUN_00407e65(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int in_ECX;
  
  uVar1 = *(undefined4 *)(in_ECX + 0x10);
  uVar2 = *(undefined4 *)(in_ECX + 0x14);
  *param_1 = *(undefined4 *)(in_ECX + 0xc);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x407e90 ====

void FUN_00407e90(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int in_ECX;
  
  uVar1 = *(undefined4 *)(in_ECX + 0x1c);
  uVar2 = *(undefined4 *)(in_ECX + 0x20);
  *param_1 = *(undefined4 *)(in_ECX + 0x18);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x407ebb ====

void FUN_00407ebb(float *param_1)

{
  float fVar1;
  float fVar2;
  float *in_ECX;
  int iVar3;
  float *pfVar4;
  float local_30 [4];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  fVar1 = in_ECX[5] * in_ECX[6] - in_ECX[8] * in_ECX[3];
  local_c = in_ECX[7] * in_ECX[3] - in_ECX[6] * in_ECX[4];
  local_8 = in_ECX[8] * in_ECX[4] - in_ECX[5] * in_ECX[7];
  fVar2 = 1.0 / (local_c * in_ECX[2] + fVar1 * in_ECX[1] + local_8 * *in_ECX);
  local_30[0] = local_8 * fVar2;
  local_30[3] = (in_ECX[2] * in_ECX[7] - in_ECX[8] * in_ECX[1]) * fVar2;
  local_18 = (in_ECX[5] * in_ECX[1] - in_ECX[2] * in_ECX[4]) * fVar2;
  local_30[1] = fVar1 * fVar2;
  local_20 = (in_ECX[8] * *in_ECX - in_ECX[2] * in_ECX[6]) * fVar2;
  local_14 = (in_ECX[2] * in_ECX[3] - in_ECX[5] * *in_ECX) * fVar2;
  local_30[2] = local_c * fVar2;
  local_1c = (in_ECX[6] * in_ECX[1] - *in_ECX * in_ECX[7]) * fVar2;
  local_10 = (*in_ECX * in_ECX[4] - in_ECX[3] * in_ECX[1]) * fVar2;
  pfVar4 = local_30;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x407fa6 ====

void FUN_00407fa6(float *param_1,float *param_2)

{
  float *in_ECX;
  int iVar1;
  float *pfVar2;
  float local_28 [4];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_28[0] = in_ECX[6] * param_2[6] + *param_2 * *in_ECX + param_2[3] * in_ECX[3];
  local_28[1] = in_ECX[1] * *param_2 + param_2[3] * in_ECX[4] + in_ECX[7] * param_2[6];
  local_28[2] = param_2[3] * in_ECX[5] + *param_2 * in_ECX[2] + in_ECX[8] * param_2[6];
  local_28[3] = param_2[4] * in_ECX[3] + param_2[1] * *in_ECX + param_2[7] * in_ECX[6];
  local_18 = param_2[1] * in_ECX[1] + param_2[4] * in_ECX[4] + param_2[7] * in_ECX[7];
  local_14 = in_ECX[5] * param_2[4] + in_ECX[8] * param_2[7] + param_2[1] * in_ECX[2];
  local_10 = param_2[5] * in_ECX[3] + param_2[2] * *in_ECX + param_2[8] * in_ECX[6];
  local_c = param_2[2] * in_ECX[1] + param_2[5] * in_ECX[4] + param_2[8] * in_ECX[7];
  local_8 = in_ECX[5] * param_2[5] + in_ECX[8] * param_2[8] + param_2[2] * in_ECX[2];
  pfVar2 = local_28;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x40809f ====

void FUN_0040809f(float *param_1,float *param_2)

{
  float *in_ECX;
  int iVar1;
  float *pfVar2;
  float local_28 [4];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_28[0] = *param_2 + *in_ECX;
  local_28[1] = param_2[1] + in_ECX[1];
  local_28[2] = param_2[2] + in_ECX[2];
  local_28[3] = param_2[3] + in_ECX[3];
  local_18 = param_2[4] + in_ECX[4];
  local_14 = param_2[5] + in_ECX[5];
  local_10 = param_2[6] + in_ECX[6];
  local_c = param_2[7] + in_ECX[7];
  local_8 = param_2[8] + in_ECX[8];
  pfVar2 = local_28;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x40810c ====

void FUN_0040810c(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0;
  in_ECX[3] = 0;
  return;
}



// ==== 0x408136 ====

void FUN_00408136(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  float *pfVar1;
  undefined4 uVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float *in_ECX;
  undefined1 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  float **ppfVar11;
  undefined1 local_ac [12];
  undefined1 local_a0 [12];
  undefined1 local_94 [12];
  undefined1 local_88 [12];
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  undefined1 local_40 [12];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  float *local_c;
  float local_8;
  
  local_30 = *param_1;
  uStack_2c = param_1[1];
  local_28 = 0;
  local_18 = *param_2;
  uStack_14 = param_2[1];
  local_10 = 0;
  local_24 = *param_3;
  uStack_20 = param_3[1];
  local_1c = 0;
  pfVar1 = (float *)FUN_004021a7(local_ac,param_2);
  uVar2 = FUN_004021a7(local_94,param_2);
  puVar10 = local_64;
  FUN_004021a7(local_70,param_2);
  pfVar3 = (float *)FUN_004021dc(puVar10,uVar2);
  local_c = (float *)0x3e800000;
  ppfVar11 = &local_c;
  puVar10 = local_58;
  local_8 = *pfVar1 * *pfVar3 + pfVar1[1] * pfVar3[1] + pfVar1[2] * pfVar3[2];
  puVar4 = &local_18;
  puVar8 = local_40;
  puVar6 = &local_30;
  puVar5 = local_70;
  FUN_00402172(local_64,param_2);
  FUN_00402172(puVar5,puVar6);
  FUN_00402172(puVar8,puVar4);
  puVar4 = (undefined4 *)FUN_00402227(puVar10,ppfVar11);
  local_18 = *puVar4;
  uStack_14 = puVar4[1];
  local_10 = puVar4[2];
  *in_ECX = local_8 + *in_ECX;
  local_c = in_ECX + 1;
  uVar2 = FUN_00402227(local_40,&local_8);
  FUN_0040225a(uVar2);
  puVar9 = param_2;
  pfVar1 = (float *)FUN_004021a7(local_40,param_2);
  uVar2 = FUN_004021a7(local_58,puVar9);
  puVar10 = local_70;
  FUN_004021a7(local_64,puVar9);
  pfVar3 = (float *)FUN_004021dc(puVar10,uVar2);
  local_34 = 0x3e800000;
  puVar4 = &local_34;
  puVar10 = local_7c;
  local_8 = *pfVar1 * *pfVar3 + pfVar1[1] * pfVar3[1] + pfVar1[2] * pfVar3[2];
  puVar6 = &local_30;
  puVar8 = local_4c;
  puVar7 = &local_24;
  puVar5 = local_40;
  FUN_00402172(local_58,puVar9);
  FUN_00402172(puVar5,puVar7);
  FUN_00402172(puVar8,puVar6);
  puVar4 = (undefined4 *)FUN_00402227(puVar10,puVar4);
  local_18 = *puVar4;
  uStack_14 = puVar4[1];
  local_10 = puVar4[2];
  *in_ECX = local_8 + *in_ECX;
  uVar2 = FUN_00402227(local_4c,&local_8);
  FUN_0040225a(uVar2);
  puVar7 = param_2;
  pfVar1 = (float *)FUN_004021a7(local_4c,param_2);
  uVar2 = FUN_004021a7(local_7c,puVar7);
  puVar10 = local_40;
  FUN_004021a7(local_58,puVar7);
  pfVar3 = (float *)FUN_004021dc(puVar10,uVar2);
  param_2 = (undefined4 *)0x3e800000;
  puVar4 = &param_2;
  puVar10 = local_a0;
  local_8 = *pfVar1 * *pfVar3 + pfVar1[1] * pfVar3[1] + pfVar1[2] * pfVar3[2];
  puVar8 = local_88;
  puVar6 = &local_24;
  puVar5 = local_4c;
  puVar9 = param_3;
  FUN_00402172(local_7c,puVar7);
  FUN_00402172(puVar5,puVar6);
  FUN_00402172(puVar8,puVar9);
  puVar4 = (undefined4 *)FUN_00402227(puVar10,puVar4);
  local_18 = *puVar4;
  uStack_14 = puVar4[1];
  local_10 = puVar4[2];
  *in_ECX = local_8 + *in_ECX;
  uVar2 = FUN_00402227(local_88,&local_8);
  FUN_0040225a(uVar2);
  return;
}



// ==== 0x4083ab ====

void FUN_004083ab(void)

{
  undefined4 *in_ECX;
  
  _free((void *)*in_ECX);
  _free((void *)in_ECX[2]);
  _free((void *)in_ECX[4]);
  _free((void *)in_ECX[6]);
  return;
}



// ==== 0x4083d2 ====

void FUN_004083d2(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_00746c30;
  if (&DAT_00746c30 < DAT_00561408) {
    do {
      FUN_004083ab();
      puVar1 = puVar1 + 0x3f;
    } while (puVar1 < DAT_00561408);
  }
  DAT_00561408 = &DAT_00746c30;
  return;
}



// ==== 0x408401 ====

undefined4 * FUN_00408401(undefined4 *param_1)

{
  undefined4 uVar1;
  int in_ECX;
  undefined1 *puVar2;
  int iVar3;
  undefined1 local_1c [12];
  undefined1 local_10 [12];
  
  if (*(char *)(in_ECX + 0xd0) == '\0') {
    iVar3 = in_ECX + 0x90;
    puVar2 = local_10;
    FUN_004021a7(local_1c,in_ECX + 0x84);
    uVar1 = FUN_004021dc(puVar2,iVar3);
    FUN_00402172(param_1,uVar1);
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return param_1;
}



// ==== 0x40846d ====

void FUN_0040846d(void)

{
  undefined4 uVar1;
  int in_ECX;
  undefined1 local_10 [12];
  
  if (*(char *)(in_ECX + 0xd0) == '\0') {
    uVar1 = FUN_00402227(local_10,in_ECX + 0xb8);
    FUN_00407e1c(uVar1);
  }
  return;
}



// ==== 0x4084a3 ====

undefined4 FUN_004084a3(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined1 local_4c [12];
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  undefined1 local_10 [12];
  
  iVar6 = in_ECX + 0xb8;
  puVar5 = local_10;
  uVar1 = FUN_004021a7(local_1c,in_ECX + 0x84);
  puVar4 = local_28;
  puVar3 = local_34;
  FUN_004021a7(local_40,in_ECX + 0x84);
  FUN_004021dc(puVar3,param_3);
  FUN_004021dc(puVar4,uVar1);
  uVar2 = FUN_00402227(puVar5,iVar6);
  uVar1 = param_1;
  FUN_00402227(local_4c,in_ECX + 0xb0);
  FUN_00402172(uVar1,uVar2);
  return param_1;
}



// ==== 0x408520 ====

void FUN_00408520(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_4c [4];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28 [12];
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0x3f800000;
  local_c = 0;
  local_8 = 0;
  local_1c = 0x3f800000;
  uStack_18 = 0;
  uStack_14 = 0;
  puVar1 = (undefined4 *)FUN_004084a3(local_28,param_2,&local_1c,param_3);
  local_4c[0] = *puVar1;
  local_4c[1] = puVar1[1];
  local_4c[2] = puVar1[2];
  local_10 = 0;
  local_c = 0x3f800000;
  local_8 = 0;
  local_1c = 0;
  uStack_18 = 0x3f800000;
  uStack_14 = 0;
  puVar1 = (undefined4 *)FUN_004084a3(local_28,param_2,&local_1c,param_3);
  local_4c[3] = *puVar1;
  local_3c = puVar1[1];
  local_38 = puVar1[2];
  local_10 = 0;
  local_c = 0;
  local_8 = 0x3f800000;
  local_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  puVar1 = (undefined4 *)FUN_004084a3(local_28,param_2,&local_1c,param_3);
  local_10 = *puVar1;
  local_c = puVar1[1];
  local_8 = puVar1[2];
  local_34 = *puVar1;
  local_30 = puVar1[1];
  local_2c = puVar1[2];
  puVar1 = local_4c;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x408612 ====

void FUN_00408612(undefined4 param_1,undefined4 param_2)

{
  float *pfVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  float local_10;
  float local_c;
  float local_8;
  
  if (*(char *)(in_ECX + 0xd0) == '\0') {
    iVar5 = in_ECX + 0xb8;
    puVar4 = local_1c;
    puVar3 = local_28;
    FUN_004021a7(local_34,in_ECX + 0x84);
    FUN_004021dc(puVar3,param_2);
    pfVar1 = (float *)FUN_00402227(puVar4,iVar5);
    local_10 = *pfVar1;
    local_c = pfVar1[1];
    local_8 = pfVar1[2];
    *(float *)(in_ECX + 0x90) = *(float *)(in_ECX + 0x90) - local_10;
    *(float *)(in_ECX + 0x94) = *(float *)(in_ECX + 0x94) - local_c;
    *(float *)(in_ECX + 0x98) = *(float *)(in_ECX + 0x98) - local_8;
    uVar2 = FUN_00402227(local_34,in_ECX + 0xb0);
    FUN_0040225a(uVar2);
  }
  return;
}



// ==== 0x4086a6 ====

void FUN_004086a6(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_10 [12];
  
  uVar1 = FUN_00406e8a(local_10);
  FUN_0040846d(local_10,uVar1);
  FUN_0040846d(local_10,param_2);
  return;
}



// ==== 0x4086da ====

void FUN_004086da(void)

{
  float fVar1;
  undefined4 uVar2;
  int in_ECX;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = in_ECX;
  FUN_0040810c();
  local_1c = 0;
  uVar3 = *(uint *)(in_ECX + 0x10);
  local_18 = 0;
  local_14 = 0;
  *(undefined4 *)(in_ECX + 0x48) = 0;
  *(undefined4 *)(in_ECX + 0x4c) = 0;
  *(undefined4 *)(in_ECX + 0x50) = 0;
  if (uVar3 < *(uint *)(local_8 + 0x14)) {
    puVar4 = (undefined4 *)(uVar3 + 0x14);
    do {
      uVar2 = FUN_00402227(&local_1c,puVar4);
      FUN_0040225a(uVar2);
      if (2 < (int)puVar4[2]) {
        local_10 = *(undefined4 *)puVar4[-1];
        local_c = puVar4[2] + -2;
        puVar5 = (undefined4 *)puVar4[-1] + 4;
        do {
          FUN_00408136(local_10,puVar5[-2],*puVar5,*puVar4);
          puVar5 = puVar5 + 2;
          local_c = local_c + -1;
        } while (local_c != 0);
      }
      uVar3 = uVar3 + 0x24;
      puVar4 = puVar4 + 9;
    } while (uVar3 < *(uint *)(local_8 + 0x14));
  }
  fVar1 = 1.0 / local_2c;
  *(float *)(local_8 + 0x38) = local_2c;
  *(float *)(local_8 + 0x3c) = local_28 * fVar1;
  *(float *)(local_8 + 0x40) = local_24 * fVar1;
  *(float *)(local_8 + 0x44) = local_20 * fVar1;
  return;
}



// ==== 0x4087a4 ====

void FUN_004087a4(void)

{
  uint *in_ECX;
  uint uVar1;
  
  uVar1 = *in_ECX;
  if (uVar1 < in_ECX[1]) {
    do {
      FUN_00407e1c(in_ECX + 0xf);
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < in_ECX[1]);
  }
  in_ECX[0x11] = 0;
  in_ECX[0x10] = 0;
  in_ECX[0xf] = 0;
  return;
}



// ==== 0x4087d6 ====

void FUN_004087d6(int param_1,int param_2,int param_3)

{
  void *pvVar1;
  undefined4 *in_ECX;
  
  pvVar1 = operator_new(param_1 << 6);
  *in_ECX = pvVar1;
  pvVar1 = operator_new(param_2 << 5);
  in_ECX[2] = pvVar1;
  pvVar1 = operator_new(param_3 * 0x90);
  in_ECX[4] = pvVar1;
  return;
}



// ==== 0x408812 ====

void FUN_00408812(float *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0.0;
  local_c = 0.0;
  local_8 = 0.0;
  iVar4 = 2;
  if (2 < (int)param_1[7]) {
    puVar1 = (undefined4 *)param_1[4];
    do {
      uVar2 = FUN_004021a7(&local_1c,*puVar1);
      puVar5 = local_28;
      FUN_004021a7(local_34,*puVar1);
      pfVar3 = (float *)FUN_004021dc(puVar5,uVar2);
      local_10 = local_10 + *pfVar3;
      iVar4 = iVar4 + 1;
      local_c = local_c + pfVar3[1];
      local_8 = local_8 + pfVar3[2];
    } while (iVar4 < (int)param_1[7]);
  }
  *param_1 = local_10;
  param_1[1] = local_c;
  param_1[2] = local_8;
  pfVar3 = *(float **)param_1[4];
  param_1[3] = *param_1 * *pfVar3 + pfVar3[1] * param_1[1] + pfVar3[2] * param_1[2];
  return;
}



// ==== 0x4088b5 ====

void FUN_004088b5(float param_1)

{
  int in_ECX;
  
  *(float *)(in_ECX + 0xac) = param_1 * *(float *)(in_ECX + 0xac);
  *(float *)(in_ECX + 0xb0) = (1.0 / param_1) * *(float *)(in_ECX + 0xb0);
  *(float *)(in_ECX + 0xa8) = param_1 * *(float *)(in_ECX + 0xa8);
  *(float *)(in_ECX + 0xb4) = param_1 * *(float *)(in_ECX + 0xb4);
  *(float *)(in_ECX + 0xb8) = (1.0 / param_1) * *(float *)(in_ECX + 0xb8);
  return;
}



// ==== 0x4088fe ====

void FUN_004088fe(int *param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *in_ECX;
  int iVar4;
  int *piVar5;
  
  FUN_004087d6(0x200,0x800,0x200);
  puVar2 = (undefined4 *)*in_ECX;
  if (0 < param_2) {
    do {
      *puVar2 = *param_1;
      puVar2[1] = param_1[1];
      puVar2[2] = param_1[2];
      *(undefined1 *)((int)puVar2 + 0xd) = 0;
      puVar2 = puVar2 + 4;
      param_2 = param_2 + -1;
      param_1 = param_1 + 3;
    } while (param_2 != 0);
  }
  piVar5 = (int *)in_ECX[2];
  iVar4 = in_ECX[4];
  piVar1 = param_3 + param_4;
  in_ECX[1] = (int)puVar2;
  iVar3 = 0;
  while (param_3 < piVar1) {
    if (*param_3 < 0) {
      *(int *)(iVar4 + 0x1c) = iVar3;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(int **)(iVar4 + 0x10) = piVar5 + iVar3 * -2;
      *(undefined4 *)(iVar4 + 0x18) = 1;
      FUN_00408812(iVar4);
      iVar4 = iVar4 + 0x24;
      iVar3 = 0;
    }
    else {
      piVar5[1] = *param_3;
      iVar3 = iVar3 + 1;
      *piVar5 = *param_3 * 0x10 + *in_ECX;
      piVar5 = piVar5 + 2;
    }
    param_1 = param_3 + 1;
    param_3 = param_1;
  }
  in_ECX[3] = (int)piVar5;
  in_ECX[5] = iVar4;
  return;
}



// ==== 0x4089b4 ====

void FUN_004089b4(void)

{
  int in_ECX;
  
  *(undefined1 *)(in_ECX + 0xd0) = 1;
  *(undefined4 *)(in_ECX + 0xb0) = 0;
  *(undefined4 *)(in_ECX + 0xac) = 0x7b4097ce;
  *(undefined4 *)(in_ECX + 0xb8) = 0;
  *(undefined4 *)(in_ECX + 0xb4) = 0x7b4097ce;
  return;
}



// ==== 0x4089de ====

void FUN_004089de(void)

{
  void *pvVar1;
  uint uVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_8;
  
  pvVar1 = operator_new((*(int *)(in_ECX + 0xc) - *(int *)(in_ECX + 8) >> 3) << 4);
  *(void **)(in_ECX + 0x18) = pvVar1;
  *(void **)(in_ECX + 0x1c) = pvVar1;
  for (uVar2 = *(uint *)(in_ECX + 0x10); uVar2 < *(uint *)(in_ECX + 0x14); uVar2 = uVar2 + 0x24) {
    local_8 = 0;
    if (0 < *(int *)(uVar2 + 0x1c)) {
      iVar4 = *(int *)(uVar2 + 0x1c) * 8 + -8;
      do {
        iVar6 = *(int *)(uVar2 + 0x10);
        iVar3 = local_8 * 8;
        if (*(int *)(iVar4 + 4 + iVar6) < *(int *)(iVar6 + 4 + iVar3)) {
          **(undefined4 **)(in_ECX + 0x1c) = *(undefined4 *)(iVar6 + 4 + iVar3);
          *(undefined4 *)(*(int *)(in_ECX + 0x1c) + 4) =
               *(undefined4 *)(*(int *)(uVar2 + 0x10) + 4 + iVar4);
          *(uint *)(*(int *)(in_ECX + 0x1c) + 8) = uVar2;
          *(undefined4 *)(*(int *)(in_ECX + 0x1c) + 0xc) = 0;
          *(int *)(in_ECX + 0x1c) = *(int *)(in_ECX + 0x1c) + 0x10;
        }
        local_8 = local_8 + 1;
        iVar4 = iVar3;
      } while (local_8 < *(int *)(uVar2 + 0x1c));
    }
  }
  for (uVar2 = *(uint *)(in_ECX + 0x10); uVar2 < *(uint *)(in_ECX + 0x14); uVar2 = uVar2 + 0x24) {
    local_8 = 0;
    if (0 < *(int *)(uVar2 + 0x1c)) {
      iVar4 = *(int *)(uVar2 + 0x1c) * 8 + -8;
      iVar6 = 0;
      do {
        if (*(int *)(iVar6 + 4 + *(int *)(uVar2 + 0x10)) <
            *(int *)(iVar4 + 4 + *(int *)(uVar2 + 0x10))) {
          for (piVar5 = *(int **)(in_ECX + 0x18);
              (*piVar5 != *(int *)(iVar4 + 4 + *(int *)(uVar2 + 0x10)) ||
              (piVar5[1] != *(int *)(iVar6 + 4 + *(int *)(uVar2 + 0x10)))); piVar5 = piVar5 + 4) {
          }
          piVar5[3] = uVar2;
        }
        local_8 = local_8 + 1;
        iVar4 = iVar6;
        iVar6 = iVar6 + 8;
      } while (local_8 < *(int *)(uVar2 + 0x1c));
    }
  }
  return;
}



// ==== 0x408ace ====

void FUN_00408ace(void)

{
  uint *in_ECX;
  uint uVar1;
  float10 fVar2;
  
  FUN_004089de();
  uVar1 = *in_ECX;
  in_ECX[0x2c] = (uint)(1.0 / (float)in_ECX[0x2b]);
  in_ECX[0x2e] = (uint)(1.0 / (float)in_ECX[0x2d]);
  in_ECX[0xb] = 0;
  for (; uVar1 < in_ECX[1]; uVar1 = uVar1 + 0x10) {
    fVar2 = (float10)FUN_004022a2();
    if ((float10)(float)in_ECX[0xb] < fVar2) {
      fVar2 = (float10)FUN_004022a2();
      in_ECX[0xb] = (uint)(float)fVar2;
    }
  }
  fVar2 = (float10)FUN_0041d134((double)(float)in_ECX[0xb]);
  in_ECX[0xb] = (uint)(float)fVar2;
  return;
}



// ==== 0x408b34 ====

void FUN_00408b34(void)

{
  float fVar1;
  float fVar2;
  int in_ECX;
  
  FUN_004086da();
  FUN_00408ace();
  *(undefined4 *)(in_ECX + 0xa8) = 0x3f800000;
  *(undefined4 *)(in_ECX + 0xbc) = 0;
  fVar1 = *(float *)(in_ECX + 0x38);
  *(float *)(in_ECX + 0xac) = fVar1;
  fVar2 = *(float *)(in_ECX + 0x2c) * 0.4;
  *(undefined1 *)(in_ECX + 0xec) = 0;
  *(undefined4 *)(in_ECX + 0xe0) = 3;
  *(undefined1 *)(in_ECX + 0x58) = 0;
  fVar2 = fVar2 * fVar2 * fVar1;
  *(float *)(in_ECX + 0xb4) = fVar2;
  *(float *)(in_ECX + 0xb0) = 1.0 / fVar1;
  *(float *)(in_ECX + 0xb8) = 1.0 / fVar2;
  *(undefined4 *)(in_ECX + 0x90) = 0;
  *(undefined4 *)(in_ECX + 0x94) = 0;
  *(undefined4 *)(in_ECX + 0x98) = 0;
  *(undefined4 *)(in_ECX + 0x9c) = 0;
  *(undefined4 *)(in_ECX + 0xa0) = 0;
  *(undefined4 *)(in_ECX + 0xa4) = 0;
  FUN_00402429();
  *(undefined1 *)(in_ECX + 0xd0) = 0;
  *(undefined4 *)(in_ECX + 0xe4) = 0;
  *(undefined4 *)(in_ECX + 0x54) = 0x47c35000;
  *(undefined4 *)(in_ECX + 0xe8) = 0;
  *(undefined4 *)(in_ECX + 0xc0) = 0;
  *(undefined4 *)(in_ECX + 0x20) = 0;
  *(undefined4 *)(in_ECX + 0xc4) = 0;
  *(undefined4 *)(in_ECX + 0x24) = 0;
  *(undefined4 *)(in_ECX + 0x28) = 0;
  *(undefined4 *)(in_ECX + 200) = 0x432a0000;
  return;
}



// ==== 0x408c36 ====

void FUN_00408c36(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar2 = DAT_00561408;
  for (puVar4 = &DAT_00746c30; puVar4 < puVar2; puVar4 = puVar4 + 0x3f) {
    puVar4[0x3a] = 0;
  }
  DAT_0056140c = &DAT_00561410;
  if (&DAT_00521e00 < DAT_00561404) {
    puVar4 = &DAT_00521e68;
    do {
      puVar4[0x22] = 0;
      puVar4[-3] = 0;
      puVar2 = DAT_0056140c;
      puVar4[0x20] = 0;
      puVar4[0x21] = 0;
      puVar4[1] = 0;
      *puVar4 = 0;
      puVar4[-1] = 0;
      puVar4[0x19] = 0;
      puVar4[0x18] = 0;
      puVar4[0x17] = 0;
      puVar4[0x16] = 0;
      puVar4[0x15] = 0;
      puVar4[0x14] = 0;
      puVar2[2] = puVar4[-0x19];
      piVar1 = puVar4 + -0x1a;
      DAT_0056140c[1] = piVar1;
      puVar2 = DAT_0056140c;
      iVar3 = *piVar1;
      *DAT_0056140c = *(undefined4 *)(iVar3 + 0xe8);
      *(undefined4 *)(iVar3 + 0xe8) = puVar2;
      puVar2 = DAT_0056140c;
      DAT_0056140c = DAT_0056140c + 3;
      puVar2[5] = *piVar1;
      DAT_0056140c[1] = piVar1;
      puVar2 = DAT_0056140c;
      iVar3 = puVar4[-0x19];
      *DAT_0056140c = *(undefined4 *)(iVar3 + 0xe8);
      *(undefined4 *)(iVar3 + 0xe8) = puVar2;
      DAT_0056140c = DAT_0056140c + 3;
      puVar2 = puVar4 + 0x23;
      puVar4 = puVar4 + 0x3d;
    } while (puVar2 < DAT_00561404);
  }
  return;
}



// ==== 0x408d37 ====

void FUN_00408d37(void)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = in_ECX;
  for (iVar1 = 0x3f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  in_ECX[0x35] = 0;
  in_ECX[0x36] = 0;
  in_ECX[0x37] = 0;
  return;
}



// ==== 0x408d57 ====

int FUN_00408d57(float param_1,float param_2,float param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  float local_70 [24];
  float local_10;
  float local_c;
  float local_8;
  
  iVar2 = DAT_00561408;
  FUN_00408d37();
  uVar3 = 0;
  pfVar4 = local_70;
  do {
    local_10 = param_1;
    local_c = param_2;
    local_8 = param_3;
    if ((uVar3 & 1) != 0) {
      local_10 = param_1 * -1.0;
    }
    if ((uVar3 & 2) == 0) {
      local_c = param_2 * -1.0;
    }
    if ((uVar3 & 4) != 0) {
      local_8 = param_3 * -1.0;
    }
    *pfVar4 = local_10;
    pfVar1 = pfVar4 + 2;
    pfVar4[1] = local_c;
    uVar3 = uVar3 + 1;
    pfVar4 = pfVar4 + 3;
    *pfVar1 = local_8;
  } while ((int)uVar3 < 8);
  FUN_004088fe(local_70,8,&DAT_00453708,0x1e);
  FUN_00408b34();
  *(undefined4 *)(iVar2 + 0x84) = param_4;
  *(undefined4 *)(iVar2 + 0x88) = param_5;
  *(undefined4 *)(iVar2 + 0x30) = param_7;
  *(undefined4 *)(iVar2 + 0x8c) = param_6;
  *(undefined4 *)(iVar2 + 0x34) = param_8;
  DAT_00561408 = DAT_00561408 + 0xfc;
  return iVar2;
}



// ==== 0x408dfc ====

void thunk_FUN_00408c36(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar2 = DAT_00561408;
  for (puVar4 = &DAT_00746c30; puVar4 < puVar2; puVar4 = puVar4 + 0x3f) {
    puVar4[0x3a] = 0;
  }
  DAT_0056140c = &DAT_00561410;
  if (&DAT_00521e00 < DAT_00561404) {
    puVar4 = &DAT_00521e68;
    do {
      puVar4[0x22] = 0;
      puVar4[-3] = 0;
      puVar2 = DAT_0056140c;
      puVar4[0x20] = 0;
      puVar4[0x21] = 0;
      puVar4[1] = 0;
      *puVar4 = 0;
      puVar4[-1] = 0;
      puVar4[0x19] = 0;
      puVar4[0x18] = 0;
      puVar4[0x17] = 0;
      puVar4[0x16] = 0;
      puVar4[0x15] = 0;
      puVar4[0x14] = 0;
      puVar2[2] = puVar4[-0x19];
      piVar1 = puVar4 + -0x1a;
      DAT_0056140c[1] = piVar1;
      puVar2 = DAT_0056140c;
      iVar3 = *piVar1;
      *DAT_0056140c = *(undefined4 *)(iVar3 + 0xe8);
      *(undefined4 *)(iVar3 + 0xe8) = puVar2;
      puVar2 = DAT_0056140c;
      DAT_0056140c = DAT_0056140c + 3;
      puVar2[5] = *piVar1;
      DAT_0056140c[1] = piVar1;
      puVar2 = DAT_0056140c;
      iVar3 = puVar4[-0x19];
      *DAT_0056140c = *(undefined4 *)(iVar3 + 0xe8);
      *(undefined4 *)(iVar3 + 0xe8) = puVar2;
      DAT_0056140c = DAT_0056140c + 3;
      puVar2 = puVar4 + 0x23;
      puVar4 = puVar4 + 0x3d;
    } while (puVar2 < DAT_00561404);
  }
  return;
}



// ==== 0x408e01 ====

void FUN_00408e01(void)

{
  FUN_004087d6(0x200,0x800,0x200);
  FUN_004087d6(0x200,0x800,0x200);
  return;
}



// ==== 0x408e2a ====

void FUN_00408e2a(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_00746c30;
  if (&DAT_00746c30 < DAT_00561408) {
    do {
      FUN_0040c5c7();
      puVar1 = puVar1 + 0x3f;
    } while (puVar1 < DAT_00561408);
  }
  return;
}



// ==== 0x408e51 ====

void FUN_00408e51(undefined4 param_1)

{
  uint *in_ECX;
  uint uVar1;
  
  uVar1 = *in_ECX;
  if (uVar1 < in_ECX[1]) {
    do {
      FUN_00407e1c(in_ECX + 0xf);
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < in_ECX[1]);
  }
  for (uVar1 = in_ECX[4]; uVar1 < in_ECX[5]; uVar1 = uVar1 + 0x24) {
    if (*(float *)(uVar1 + 0x14) < 0.0) {
      *(undefined4 *)(uVar1 + 0x18) = param_1;
    }
    *(undefined4 *)(uVar1 + 0x14) = 0x3f800000;
    FUN_00408812(uVar1);
  }
  return;
}



// ==== 0x408eab ====

undefined2 FUN_00408eab(float *param_1)

{
  int in_ECX;
  float *pfVar1;
  
  pfVar1 = *(float **)(in_ECX + 0x10);
  while( true ) {
    if (*(float **)(in_ECX + 0x14) <= pfVar1) {
      return 1;
    }
    if (*pfVar1 * *param_1 + pfVar1[2] * param_1[2] + pfVar1[1] * param_1[1] < pfVar1[3]) break;
    pfVar1 = pfVar1 + 9;
  }
  return 0;
}



// ==== 0x408ee9 ====

void FUN_00408ee9(void)

{
  float fVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  fVar1 = 1e+36;
  pcVar5 = (char *)0x0;
  iVar4 = 0;
  if (&DAT_00746c30 < DAT_00561408) {
    pcVar2 = &DAT_00746d00;
    iVar3 = ((int)DAT_00561408 - 0x746c31U) / 0xfc + 1;
    do {
      if (((*(int *)(pcVar2 + 0x18) == 0) && (*pcVar2 == '\0')) && (pcVar2[-0x78] == '\0')) {
        if (*(float *)(pcVar2 + -0x24) < fVar1) {
          pcVar5 = pcVar2 + -0xd0;
          fVar1 = *(float *)(pcVar2 + -0x24);
        }
        iVar4 = iVar4 + 1;
      }
      pcVar2 = pcVar2 + 0xfc;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if ((0x5a < iVar4) && (pcVar5 != (char *)0x0)) {
      pcVar5[0x58] = '\x01';
    }
  }
  return;
}



// ==== 0x408f5e ====

int FUN_00408f5e(int param_1)

{
  undefined1 *puVar1;
  int *in_ECX;
  
  if ((uint)(in_ECX[1] - *in_ECX) <= (uint)(param_1 * 4)) {
    puVar1 = (undefined1 *)0x0;
    do {
      puVar1 = puVar1 + 1;
      *puVar1 = 0x7f;
    } while( true );
  }
  return *in_ECX + param_1 * 4;
}



// ==== 0x408f7d ====

void FUN_00408f7d(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int in_ECX;
  undefined4 *puVar9;
  
  puVar9 = (undefined4 *)(*(int *)(in_ECX + 0x2000) * 0x10 + in_ECX);
  *puVar9 = param_1;
  puVar9[1] = param_2;
  puVar9[2] = param_3;
  puVar9[3] = param_4;
  *(int *)(in_ECX + 0x2000) = *(int *)(in_ECX + 0x2000) + 1;
  iVar7 = *(int *)(in_ECX + 0x2000) + -1;
  while( true ) {
    if (iVar7 == 0) {
      return;
    }
    iVar8 = (iVar7 + -1) / 2;
    pfVar1 = (float *)(iVar8 * 0x10 + in_ECX);
    pfVar2 = (float *)(iVar7 * 0x10 + in_ECX);
    if (*pfVar1 <= *pfVar2) break;
    fVar3 = *pfVar1;
    fVar4 = pfVar1[1];
    fVar5 = pfVar1[2];
    fVar6 = pfVar1[3];
    *pfVar1 = *pfVar2;
    pfVar1[1] = pfVar2[1];
    pfVar1[2] = pfVar2[2];
    pfVar1[3] = pfVar2[3];
    *pfVar2 = fVar3;
    pfVar2[1] = fVar4;
    pfVar2[2] = fVar5;
    pfVar2[3] = fVar6;
    iVar7 = iVar8;
  }
  return;
}



// ==== 0x409004 ====

void FUN_00409004(undefined4 *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *in_ECX;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  float *local_8;
  
  iVar5 = in_ECX[0x800];
  iVar8 = 1;
  puVar9 = in_ECX + 1;
  if (iVar5 < 2) {
    if (iVar5 == 0) goto LAB_004090bc;
    local_14 = *puVar9;
    uStack_10 = in_ECX[2];
    uStack_c = in_ECX[3];
  }
  else {
    local_14 = *puVar9;
    uStack_10 = in_ECX[2];
    uStack_c = in_ECX[3];
    puVar9 = in_ECX + iVar5 * 4 + -4;
    *in_ECX = *puVar9;
    in_ECX[1] = puVar9[1];
    in_ECX[2] = puVar9[2];
    in_ECX[3] = puVar9[3];
    iVar5 = 0;
    if (1 < (int)in_ECX[0x800]) {
      do {
        iVar7 = in_ECX[0x800];
        if ((iVar8 < iVar7 + -1) && ((float)(in_ECX + iVar8 * 4)[4] < (float)in_ECX[iVar8 * 4])) {
          iVar8 = iVar8 + 1;
        }
        local_8 = (float *)(in_ECX + iVar8 * 4);
        pfVar6 = (float *)(in_ECX + iVar5 * 4);
        if (*local_8 < *pfVar6) {
          fVar1 = *pfVar6;
          fVar2 = pfVar6[1];
          fVar3 = pfVar6[2];
          fVar4 = pfVar6[3];
          *pfVar6 = *local_8;
          pfVar6[1] = local_8[1];
          pfVar6[2] = local_8[2];
          pfVar6[3] = local_8[3];
          *local_8 = fVar1;
          local_8[1] = fVar2;
          local_8[2] = fVar3;
          local_8[3] = fVar4;
          iVar7 = iVar8;
        }
        iVar8 = iVar7 * 2 + 1;
        iVar5 = iVar7;
      } while (iVar8 < (int)in_ECX[0x800]);
    }
  }
  in_ECX[0x800] = in_ECX[0x800] + -1;
  puVar9 = &local_14;
LAB_004090bc:
  *param_1 = *puVar9;
  param_1[1] = puVar9[1];
  param_1[2] = puVar9[2];
  return;
}



// ==== 0x4090cb ====

void FUN_004090cb(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *in_ECX;
  undefined1 *puVar4;
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  puVar4 = local_1c;
  FUN_00407e3b(local_28);
  puVar2 = (undefined4 *)FUN_00402302(puVar4);
  local_10 = *puVar2;
  local_c = puVar2[1];
  local_8 = puVar2[2];
  *in_ECX = local_10;
  in_ECX[1] = local_c;
  in_ECX[2] = local_8;
  puVar4 = local_34;
  FUN_00407e65(local_28);
  puVar2 = (undefined4 *)FUN_00402302(puVar4);
  local_10 = *puVar2;
  local_c = puVar2[1];
  local_8 = puVar2[2];
  in_ECX[3] = local_10;
  in_ECX[4] = local_c;
  in_ECX[5] = local_8;
  uVar3 = FUN_00407e65(local_34);
  puVar4 = local_28;
  FUN_00407e3b(local_1c);
  puVar2 = (undefined4 *)FUN_004021dc(puVar4,uVar3);
  local_10 = *puVar2;
  local_c = puVar2[1];
  local_8 = puVar2[2];
  in_ECX[6] = local_10;
  in_ECX[7] = local_c;
  in_ECX[8] = local_8;
  uVar3 = FUN_00407e3b(local_34);
  puVar4 = local_28;
  FUN_00407e90(local_1c);
  puVar2 = (undefined4 *)FUN_004021dc(puVar4,uVar3);
  uVar3 = puVar2[1];
  uVar1 = puVar2[2];
  in_ECX[3] = *puVar2;
  in_ECX[4] = uVar3;
  in_ECX[5] = uVar1;
  return;
}



// ==== 0x4091b0 ====

void FUN_004091b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *in_ECX;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  FUN_00407e3b(&local_1c);
  FUN_00407e65(&local_28);
  FUN_00407e90(&local_34);
  FUN_00402e1d(param_1,param_2,param_3);
  FUN_00402e1d(param_1,param_2,param_3);
  FUN_00402e1d(param_1,param_2,param_3);
  *in_ECX = local_1c;
  in_ECX[1] = uStack_18;
  in_ECX[2] = uStack_14;
  in_ECX[3] = local_28;
  in_ECX[4] = uStack_24;
  in_ECX[5] = uStack_20;
  in_ECX[6] = local_34;
  in_ECX[7] = uStack_30;
  in_ECX[8] = uStack_2c;
  return;
}



// ==== 0x40927f ====

void FUN_0040927f(undefined4 *param_1)

{
  float10 fVar1;
  float10 fVar2;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  float local_8;
  
  local_14 = *param_1;
  uStack_10 = param_1[1];
  uStack_c = param_1[2];
  FUN_004022c1();
  fVar1 = (float10)FUN_004022a2();
  fVar1 = (float10)FUN_0041d134((double)fVar1);
  local_8 = (float)fVar1;
  fVar1 = (float10)FUN_004022a2();
  fVar1 = (float10)FUN_0041d134((double)fVar1);
  fVar1 = (float10)FUN_0041cd94((double)fVar1);
  fVar2 = (float10)FUN_0041d084((double)local_8);
  FUN_004091b0(&local_14,(float)fVar1,(float)fVar2);
  return;
}



// ==== 0x4092f8 ====

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_004092f8(undefined4 *param_1,float *param_2,float param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float fVar5;
  bool bVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  float *pfVar9;
  int *in_ECX;
  int *piVar10;
  float *pfVar11;
  float *pfVar12;
  int *piVar13;
  bool bVar14;
  undefined1 *puVar15;
  float local_3060 [3072];
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined1 local_48 [12];
  float *local_3c;
  float *local_38;
  float *local_34;
  int local_30;
  float local_2c;
  int *local_28;
  int *local_24;
  float *local_20;
  int *local_1c;
  undefined4 *local_18;
  int local_14;
  int *local_10;
  float local_c;
  undefined4 *local_8;
  
  pfVar12 = param_2;
  pfVar9 = (float *)*param_1;
  local_10 = in_ECX;
  if (((int)(param_1[1] - (int)pfVar9 & 0xfffffff0U) < 0x1001) &&
     ((int)(param_1[5] - param_1[4]) / 0x24 < 0x101)) {
    bVar6 = false;
    if (pfVar9 < (float *)param_1[1]) {
      do {
        bVar14 = param_3 < *pfVar9 * *param_2 + pfVar9[1] * param_2[1] + pfVar9[2] * param_2[2];
        *(undefined2 *)((int)pfVar9 + 0xe) = 0xffff;
        *(bool *)(pfVar9 + 3) = bVar14;
        pfVar9 = pfVar9 + 4;
        bVar6 = (bool)(bVar6 | bVar14);
      } while (pfVar9 < (float *)param_1[1]);
      if (bVar6) {
        local_8 = (undefined4 *)*in_ECX;
        piVar13 = (int *)in_ECX[2];
        local_c = 0.0;
        param_2 = (float *)in_ECX[4];
        pfVar9 = local_3060;
        if (piVar13 == (int *)0x0) {
          return;
        }
        local_18 = (undefined4 *)param_1[4];
        local_34 = pfVar9;
        local_1c = piVar13;
        if (local_18 < (undefined4 *)param_1[5]) {
          do {
            piVar10 = (int *)local_18[4];
            local_3c = (float *)0x0;
            local_38 = (float *)0x0;
            local_24 = piVar10 + local_18[7] * 2 + -2;
            param_2[4] = (float)piVar13;
            local_14 = 0;
            local_30 = 0;
            if (0 < (int)local_18[7]) {
              do {
                local_28 = piVar10;
                if (*(char *)(*local_28 + 0xc) != *(char *)(*local_24 + 0xc)) {
                  iVar2 = local_24[1];
                  local_2c = (float)(local_28[1] * 0x10000 + iVar2);
                  for (local_20 = local_3060; (local_20 < pfVar9 && (local_2c != *local_20));
                      local_20 = local_20 + 3) {
                  }
                  if (local_20 == pfVar9) {
                    iVar3 = local_28[1];
                    pfVar9[2] = 0.0;
                    *pfVar9 = (float)(iVar2 * 0x10000 + iVar3);
                    pfVar9[1] = local_c;
                    local_34 = pfVar9 + 3;
                    pfVar11 = (float *)*local_24;
                    pfVar4 = (float *)*local_28;
                    pfVar9 = &local_2c;
                    puVar15 = local_48;
                    local_2c = ((*pfVar11 * *pfVar12 +
                                pfVar11[1] * pfVar12[1] + pfVar11[2] * pfVar12[2]) - param_3) /
                               ((*pfVar12 * *pfVar11 +
                                pfVar11[1] * pfVar12[1] + pfVar11[2] * pfVar12[2]) -
                               (*pfVar12 * *pfVar4 + pfVar4[1] * pfVar12[1] + pfVar4[2] * pfVar12[2]
                               ));
                    FUN_004021a7(local_60,pfVar4);
                    uVar7 = FUN_00402227(puVar15,pfVar9);
                    puVar8 = (undefined4 *)FUN_004021a7(local_54,uVar7);
                    local_c = (float)((int)local_c + 1);
                    *local_8 = *puVar8;
                    local_8[1] = puVar8[1];
                    local_8[2] = puVar8[2];
                    *(undefined1 *)((int)local_8 + 0xd) = 1;
                    pfVar9 = local_34;
                    piVar13 = local_1c;
                    local_8 = local_8 + 4;
                  }
                  pfVar11 = local_20;
                  if (*(char *)(*local_28 + 0xc) != '\0') {
                    local_3c = local_20;
                    pfVar11 = local_38;
                  }
                  local_38 = pfVar11;
                  fVar5 = local_20[1];
                  piVar13[1] = (int)fVar5;
                  *piVar13 = (int)fVar5 * 0x10 + *local_10;
                  piVar13 = piVar13 + 2;
                  local_14 = local_14 + 1;
                  local_1c = piVar13;
                }
                puVar8 = (undefined4 *)*local_28;
                if (*(char *)(puVar8 + 3) != '\0') {
                  if (*(short *)((int)puVar8 + 0xe) == -1) {
                    *local_8 = *puVar8;
                    local_8[1] = puVar8[1];
                    local_8[2] = puVar8[2];
                    local_8[3] = puVar8[3];
                    *(undefined2 *)(*local_28 + 0xe) = local_c._0_2_;
                    piVar13 = local_1c;
                    local_c = (float)((int)local_c + 1);
                    local_8 = local_8 + 4;
                  }
                  sVar1 = *(short *)(*local_28 + 0xe);
                  piVar13[1] = (int)sVar1;
                  *piVar13 = sVar1 * 0x10 + *local_10;
                  piVar13 = piVar13 + 2;
                  local_14 = local_14 + 1;
                  local_1c = piVar13;
                }
                piVar10 = local_28 + 2;
                local_30 = local_30 + 1;
                local_24 = local_28;
              } while (local_30 < (int)local_18[7]);
              if (2 < local_14) {
                param_2[7] = (float)local_14;
                param_2[6] = (float)local_18[6];
                *param_2 = (float)*local_18;
                param_2[1] = (float)local_18[1];
                param_2[2] = (float)local_18[2];
                param_2[3] = (float)local_18[3];
                param_2[5] = (float)local_18[5];
                if (local_3c != (float *)0x0) {
                  local_3c[2] = (float)local_38;
                  local_28 = piVar10;
                  FUN_00408812(param_2);
                  pfVar9 = local_34;
                  piVar10 = local_28;
                }
                local_28 = piVar10;
                param_2 = param_2 + 9;
                piVar13 = local_1c;
                piVar10 = local_28;
              }
            }
            local_28 = piVar10;
            local_18 = local_18 + 9;
          } while (local_18 < (undefined4 *)param_1[5]);
          if (pfVar9 != local_3060) {
            param_3 = 0.0;
            param_2[4] = (float)piVar13;
            for (pfVar12 = local_3060; pfVar12 < pfVar9; pfVar12 = pfVar12 + 3) {
              pfVar11 = pfVar12;
              if (pfVar12[1] != -NAN) {
                do {
                  fVar5 = pfVar11[1];
                  piVar13[1] = (int)fVar5;
                  *piVar13 = (int)fVar5 * 0x10 + *local_10;
                  pfVar11[1] = -NAN;
                  pfVar11 = (float *)pfVar11[2];
                  piVar13 = piVar13 + 2;
                  param_3 = (float)((int)param_3 + 1);
                  if (pfVar11 == pfVar12) break;
                } while (pfVar11 != (float *)0x0);
                in_ECX = local_10;
                if (pfVar11 == (float *)0x0) goto LAB_00409651;
              }
            }
            param_2[7] = param_3;
            FUN_00408812(param_2);
            param_2[5] = -1.0;
            param_2 = param_2 + 9;
          }
        }
        local_10[5] = (int)param_2;
        local_10[3] = (int)piVar13;
        goto LAB_0040966f;
      }
    }
LAB_00409651:
    in_ECX[5] = in_ECX[4];
  }
  else {
    in_ECX[5] = in_ECX[4];
    local_8 = (undefined4 *)*in_ECX;
LAB_0040966f:
    local_10[1] = (int)local_8;
  }
  return;
}



// ==== 0x409679 ====

void FUN_00409679(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_ECX;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0;
  local_c = 0;
  local_8 = 0x3f800000;
  local_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  FUN_004092f8(in_ECX,&local_1c,0xc47a0000);
  FUN_004092f8(&DAT_00531200,param_1,param_2);
  return;
}



// ==== 0x4096d2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004096d2(void)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int in_ECX;
  float10 fVar5;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_18;
  int local_14;
  int local_10;
  float local_c;
  float local_8;
  
  if ((DAT_00d0f3b8 != '\0') && (*(float *)(in_ECX + 0x88) < _DAT_00453cd4 + 3.0)) {
    iVar1 = FUN_0041d384();
    local_14 = iVar1;
    iVar2 = FUN_0041d384();
    if ((iVar1 < DAT_00453cc8) && (((-1 < iVar1 && (iVar2 < DAT_00453ccc)) && (-1 < iVar2)))) {
      local_10 = iVar2;
      pfVar3 = (float *)FUN_00408f5e();
      local_8 = (*pfVar3 - *(float *)(in_ECX + 0x88)) + 1.3;
      if (1.0 < local_8) {
        local_8 = 1.0;
      }
      if (0.0 < local_8) {
        if (local_8 < 1.0) {
          fVar5 = (float10)FUN_0041d134((double)*(float *)(in_ECX + 0x38));
          local_1c = iVar2 + 1;
          local_24 = iVar1 + 1;
          fVar5 = fVar5 * (float10)local_8 * (float10)-0.023;
          local_c = (float)fVar5;
          local_18 = (float)(fVar5 * (float10)1.5);
          local_20 = (local_1c % DAT_00453ccc) * DAT_00453cc8;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_c * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_c * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_c * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_c * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_18 * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_18 * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_18 * *(float *)(in_ECX + 0xa0) + *pfVar3;
          pfVar3 = (float *)FUN_00408f5e();
          *pfVar3 = local_18 * *(float *)(in_ECX + 0xa0) + *pfVar3;
          *(float *)(in_ECX + 0xa0) = *(float *)(in_ECX + 0xa0) * 0.93;
        }
        *(float *)(in_ECX + 0xa0) = *(float *)(in_ECX + 0xa0) - DAT_004536e0 * local_8 * 1.4;
        *(float *)(in_ECX + 0x9c) = *(float *)(in_ECX + 0x9c) * 0.95;
        *(float *)(in_ECX + 0xa0) = *(float *)(in_ECX + 0xa0) * 0.95;
        *(float *)(in_ECX + 0xa4) = *(float *)(in_ECX + 0xa4) * 0.95;
        local_3c = 0x3c23d70a;
        uStack_38 = 0;
        uStack_34 = 0;
        local_30 = 0;
        local_2c = DAT_004536e0;
        local_28 = 0;
        uVar4 = FUN_004023c6(&local_30,in_ECX + 0x60);
        FUN_004021dc(&local_3c,uVar4);
        FUN_0040225a();
        *(float *)(in_ECX + 0x90) = *(float *)(in_ECX + 0x90) * 0.995;
        *(float *)(in_ECX + 0x94) = *(float *)(in_ECX + 0x94) * 0.995;
        *(float *)(in_ECX + 0x98) = *(float *)(in_ECX + 0x98) * 0.995;
      }
    }
  }
  return;
}



// ==== 0x409a6c ====

void FUN_00409a6c(void)

{
  int in_ECX;
  float10 fVar1;
  float10 fVar2;
  
  if ((*(char *)(in_ECX + 0x58) == '\0') && (*(char *)(in_ECX + 0xd0) == '\0')) {
    if (*(char *)(in_ECX + 0x59) == '\0') {
      FUN_0040927f(in_ECX + 0x90);
      FUN_004090cb();
      FUN_0040225a(in_ECX + 0x9c);
      FUN_004096d2();
      if (*(int *)(in_ECX + 0xe8) == 0) {
        fVar1 = (float10)FUN_004022a2();
        fVar2 = (float10)FUN_004022a2();
        if ((float10)1.0 <= (fVar2 + (float10)(float)fVar1) * (float10)111111.11) {
          *(undefined4 *)(in_ECX + 0x5c) = 0;
        }
        else {
          *(int *)(in_ECX + 0x5c) = *(int *)(in_ECX + 0x5c) + 1;
          if (0x1e < *(int *)(in_ECX + 0x5c)) {
            *(undefined1 *)(in_ECX + 0x59) = 1;
          }
        }
      }
      if (*(char *)(in_ECX + 0x59) == '\0') {
        *(float *)(in_ECX + 0xa0) = DAT_004536e0 + *(float *)(in_ECX + 0xa0);
      }
    }
    *(float *)(in_ECX + 0xcc) = *(float *)(in_ECX + 0xcc) * 0.94;
  }
  return;
}



// ==== 0x409b35 ====

undefined4 FUN_00409b35(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_EBX;
  int *piVar6;
  undefined4 *puVar7;
  float *pfVar8;
  float10 fVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined4 local_220 [96];
  undefined1 local_a0 [12];
  undefined1 local_94 [12];
  undefined1 local_88 [12];
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  int *local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  int *local_20;
  int *local_1c;
  int local_18;
  undefined4 *local_14;
  undefined4 *local_c;
  int *local_8;
  
  if ((*(char *)(unaff_EBX + 0x58) == '\0') && (DAT_00561408 <= PTR_DAT_004536e4 + -0x9d8)) {
    local_24 = &DAT_00531200;
    local_28 = &DAT_00531300;
    uVar2 = FUN_004021a7(&local_38,unaff_EBX + 0x84);
    FUN_00402363(&local_44,uVar2);
    fVar9 = (float10)FUN_0041cf20((double)(*(float *)(unaff_EBX + 0x38) * 0.007142857));
    fVar9 = (float10)FUN_0041ce90((double)(fVar9 * (float10)-0.25),0x3e800000);
    FUN_0041538b(1,(float)fVar9);
    if (DAT_00562c10 == 0) {
      DAT_00562c10 = *(int *)(unaff_EBX + 0xbc);
    }
    local_8 = local_220;
    local_c = (undefined4 *)0x0;
    local_20 = (int *)0x3e99999a;
    do {
      do {
        FUN_0040b798();
        fVar9 = (float10)FUN_0040b798();
        fVar9 = (float10)FUN_0040b798((float)((fVar9 + fVar9) - (float10)1.0));
        puVar3 = (undefined4 *)FUN_00402279(local_7c,(float)((fVar9 + fVar9) - (float10)1.0));
        uVar11 = CONCAT44(&local_44,local_70);
        local_38 = *puVar3;
        uVar10 = CONCAT44(unaff_EBX + 0x2c,local_64);
        local_34 = puVar3[1];
        local_30 = puVar3[2];
        FUN_00402227(local_58,&local_20);
        FUN_00402227(uVar10);
        puVar3 = (undefined4 *)FUN_00402172(uVar11);
        *local_8 = *puVar3;
        local_8[1] = puVar3[1];
        local_8[2] = puVar3[2];
        cVar1 = FUN_00408eab();
      } while (cVar1 == '\0');
      local_c = (undefined4 *)((int)local_c + 1);
      local_8 = local_8 + 3;
    } while ((int)local_c < 5);
    local_8 = (int *)0x0;
    local_c = local_220;
    do {
      piVar6 = (int *)0x0;
      puVar3 = DAT_00561408;
      do {
        if (local_8 != piVar6) {
          local_14 = local_24;
          if ((piVar6 == (int *)0x4) || ((piVar6 == (int *)0x3 && (local_8 == (int *)0x4)))) {
            local_14 = puVar3;
            FUN_004087d6();
          }
          uVar10 = CONCAT44(local_c,&local_38);
          FUN_00406e8a();
          FUN_00402172(uVar10);
          FUN_00402172(local_64,local_c);
          FUN_004092f8();
          puVar3 = local_24;
          local_24 = local_28;
          local_28 = puVar3;
          puVar3 = DAT_00561408;
        }
        piVar6 = (int *)((int)piVar6 + 1);
      } while ((int)piVar6 < 5);
      if (puVar3[5] == puVar3[4]) {
        FUN_00416945("halott");
      }
      else {
        puVar3[0xc] = *(undefined4 *)(unaff_EBX + 0x30);
        DAT_00561408[0xd] = *(undefined4 *)(unaff_EBX + 0x34);
        FUN_00408b34();
        FUN_00408e51();
        local_44 = (float)DAT_00561408[0xf];
        uVar10 = CONCAT44(unaff_EBX + 0x60,local_70);
        local_40 = (float)DAT_00561408[0x10];
        local_3c = (float)DAT_00561408[0x11];
        local_48 = 0x3f8147ae;
        FUN_00402227(local_7c,&local_48);
        uVar2 = FUN_004023c6(uVar10);
        puVar4 = (undefined4 *)FUN_00402172(local_88,uVar2);
        puVar7 = DAT_00561408;
        puVar3 = DAT_00561408 + 0x22;
        DAT_00561408[0x21] = *puVar4;
        *puVar3 = puVar4[1];
        puVar7[0x23] = puVar4[2];
        FUN_00408b34();
        FUN_004088b5();
        puVar7 = DAT_00561408;
        puVar3 = DAT_00561408 + 0x28;
        DAT_00561408[0x27] = *(undefined4 *)(unaff_EBX + 0x9c);
        *puVar3 = *(undefined4 *)(unaff_EBX + 0xa0);
        puVar7[0x29] = *(undefined4 *)(unaff_EBX + 0xa4);
        puVar7 = DAT_00561408;
        puVar3 = DAT_00561408 + 0x25;
        DAT_00561408[0x24] = *(undefined4 *)(unaff_EBX + 0x90);
        *puVar3 = *(undefined4 *)(unaff_EBX + 0x94);
        puVar7[0x26] = *(undefined4 *)(unaff_EBX + 0x98);
        puVar3 = (undefined4 *)(unaff_EBX + 0x60);
        puVar7 = DAT_00561408 + 0x18;
        for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
        DAT_00561408[0x39] = 0;
        puVar4 = (undefined4 *)FUN_00402172(local_a0,&local_44);
        puVar7 = DAT_00561408;
        puVar3 = DAT_00561408 + 9;
        DAT_00561408[8] = *puVar4;
        *puVar3 = puVar4[1];
        puVar7[10] = puVar4[2];
        DAT_00561408[0x30] = *(undefined4 *)(unaff_EBX + 0xc0);
        DAT_00561408[0x31] = *(undefined4 *)(unaff_EBX + 0xc4);
        if (DAT_00746c28 != '\0') {
          DAT_00561408[0x15] = *(float *)(unaff_EBX + 0x54) * 3.0;
        }
        puVar3 = DAT_00561408;
        local_14 = &DAT_00521e00;
        if (&DAT_00521e00 < DAT_00561404) {
          do {
            local_18 = 0;
            pfVar8 = (float *)(local_14 + 4);
            do {
              local_4c = local_14 + local_18;
              if (*local_4c == unaff_EBX) {
                local_20 = (int *)0xffffffff;
                local_1c = (int *)0x0;
                local_2c = 1e+36;
                do {
                  FUN_004021a7(local_94,pfVar8 + -2);
                  fVar9 = (float10)FUN_004022a2();
                  if (fVar9 < (float10)local_2c) {
                    local_2c = (float)fVar9;
                    local_20 = local_1c;
                  }
                  local_1c = (int *)((int)local_1c + 1);
                } while ((int)local_1c < 5);
                if (local_20 == local_8) {
                  *local_4c = (int)puVar3;
                  pfVar8[-2] = pfVar8[-2] - local_44;
                  pfVar8[-1] = pfVar8[-1] - local_40;
                  *pfVar8 = *pfVar8 - local_3c;
                }
              }
              local_18 = local_18 + 1;
              pfVar8 = pfVar8 + 3;
            } while (local_18 < 2);
            local_14 = local_14 + 0x3d;
          } while (local_14 < DAT_00561404);
        }
        DAT_00561408 = puVar3 + 0x3f;
      }
      local_8 = (int *)((int)local_8 + 1);
      local_c = local_c + 3;
    } while ((int)local_8 < 5);
    *(undefined1 *)(unaff_EBX + 0x58) = 1;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 0x409fce ====

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x0040a0d8) */
/* WARNING: Removing unreachable block (ram,0x0040a11e) */
/* WARNING: Removing unreachable block (ram,0x0040a130) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00409fce(float *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float *pfVar3;
  int *piVar4;
  undefined4 *puVar5;
  float fVar6;
  int iVar7;
  undefined4 *puVar8;
  float10 fVar9;
  undefined1 *puVar10;
  float *pfVar11;
  undefined1 local_e0 [36];
  undefined1 local_bc [36];
  undefined1 local_98 [36];
  undefined4 local_74 [9];
  undefined1 local_50 [12];
  undefined1 local_44 [12];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  int *local_10;
  float *local_c;
  undefined4 *local_8;
  
  for (puVar2 = (undefined4 *)param_1[0x3a]; puVar2 != (undefined4 *)0x0;
      puVar2 = (undefined4 *)*puVar2) {
    if (puVar2[2] == param_2) {
      return 0;
    }
  }
  local_10 = &DAT_00531200;
  local_8 = &DAT_00531300;
  uVar1 = FUN_0040381a(local_98);
  puVar10 = local_e0;
  FUN_0040381a(local_bc);
  puVar2 = (undefined4 *)FUN_00407fa6(puVar10,uVar1);
  puVar8 = local_74;
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar8 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar8 = puVar8 + 1;
  }
  uVar1 = FUN_004021a7(&local_38,param_2 + 0x84);
  pfVar3 = (float *)FUN_00402363(&local_2c,uVar1);
  local_c = *(float **)(param_2 + 0x10);
  local_20 = *pfVar3;
  local_1c = pfVar3[1];
  local_18 = pfVar3[2];
  if (local_c < *(float **)(param_2 + 0x14)) {
    do {
      puVar2 = (undefined4 *)FUN_00402363(&local_38,local_c);
      pfVar3 = local_c;
      FUN_00408f7d(-(local_c[3] -
                    (local_20 * *local_c + local_18 * local_c[2] + local_1c * local_c[1])),*puVar2,
                   puVar2[1],puVar2[2]);
      local_c = pfVar3 + 9;
    } while (local_c < *(float **)(param_2 + 0x14));
  }
  local_c = param_1;
  FUN_004086da();
  FUN_004023c6(&local_20,param_1 + 0x18);
  if (1e-20 <= local_20 * local_20 + local_1c * local_1c + local_18 * local_18) {
    FUN_004022c1();
    piVar4 = (int *)param_1[0x39];
    local_8 = (undefined4 *)0x0;
    for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[0x32]) {
      if (*piVar4 == param_2) {
        local_10 = piVar4 + 2;
        local_8 = (undefined4 *)piVar4[1];
        break;
      }
    }
    pfVar3 = param_1;
    for (local_14 = *param_1; (uint)local_14 < (uint)pfVar3[1];
        local_14 = (float)((int)local_14 + 0x10)) {
      if (*(char *)((int)local_14 + 0xd) != '\0') {
        pfVar3 = param_1 + 0x21;
        puVar2 = &local_38;
        FUN_004023c6(local_50,param_1 + 0x18);
        puVar5 = (undefined4 *)FUN_00402172(puVar2,pfVar3);
        puVar8 = DAT_00562c18;
        puVar2 = DAT_00562c18 + 1;
        *DAT_00562c18 = *puVar5;
        *puVar2 = puVar5[1];
        puVar8[2] = puVar5[2];
        puVar5 = (undefined4 *)FUN_00406e8a(local_44);
        puVar8 = DAT_00562c18;
        local_2c = 0;
        puVar2 = DAT_00562c18 + 4;
        DAT_00562c18[3] = *puVar5;
        local_28 = 0;
        *puVar2 = puVar5[1];
        local_24 = 0;
        puVar8[5] = puVar5[2];
        DAT_00562c18[9] = param_1;
        DAT_00562c18[10] = param_2;
        puVar8 = DAT_00562c18;
        puVar2 = DAT_00562c18 + 7;
        DAT_00562c18[6] = 0;
        *puVar2 = 0;
        puVar8[8] = 0;
        fVar6 = param_1[0x38];
        if ((int)param_1[0x38] <= (int)*(float *)(param_2 + 0xe0)) {
          fVar6 = *(float *)(param_2 + 0xe0);
        }
        DAT_00562c18[0x14] = fVar6;
        *(undefined1 *)(DAT_00562c18 + 0x15) = 0;
        if (local_8 != (undefined4 *)0x0) {
          local_8 = (undefined4 *)((int)local_8 + -1);
          *(undefined1 *)(DAT_00562c18 + 0x15) = 1;
          puVar2 = DAT_00562c18;
          piVar4 = DAT_00562c18 + 7;
          DAT_00562c18[6] = *local_10;
          *piVar4 = local_10[1];
          puVar2[8] = local_10[2];
          local_10 = local_10 + 3;
        }
        DAT_00562c18 = DAT_00562c18 + 0x18;
        pfVar3 = local_c;
      }
    }
    if (1e-09 < pfVar3[0xe]) {
      pfVar11 = param_1 + 0x21;
      puVar2 = &local_38;
      FUN_004023c6(local_44,param_1 + 0x18);
      FUN_00402172(puVar2,pfVar11);
      local_14 = (pfVar3[0xe] / (param_1[0x2c] + *(float *)(param_2 + 0xb0))) * _DAT_007665d4;
      FUN_00402227(&local_2c,&local_14);
      puVar8 = DAT_00562c14;
      puVar2 = DAT_00562c14 + 4;
      DAT_00562c14[3] = local_2c;
      *puVar2 = local_28;
      puVar8[5] = local_24;
      puVar8 = DAT_00562c14;
      puVar2 = DAT_00562c14 + 1;
      *DAT_00562c14 = local_38;
      *puVar2 = uStack_34;
      puVar8[2] = uStack_30;
      DAT_00562c14[6] = param_1;
      DAT_00562c14[7] = param_2;
      DAT_00562c14 = DAT_00562c14 + 8;
      if ((*(int *)(param_2 + 0xe8) == 0) && (200.0 < *(float *)(param_2 + 0x38))) {
        local_28 = 0x40a00000;
        local_2c = 0;
        local_24 = 0;
        local_8 = (undefined4 *)(_DAT_0045385c + 1.0);
        local_20 = 0.0;
        local_1c = 5.0;
        local_18 = 0.0;
        FUN_004021a7(local_44,&local_20);
        fVar9 = (float10)FUN_004022a2();
        if ((float10)(float)local_8 * (float10)(float)local_8 < fVar9) {
          param_1[0x37] = DAT_00c06978;
        }
        param_1[0x36] = DAT_00c06978;
      }
      if ((param_1[0x3a] == 0.0) && (200.0 < param_1[0xe])) {
        local_28 = 0x40a00000;
        local_2c = 0;
        local_24 = 0;
        local_8 = (undefined4 *)(_DAT_0045385c + 1.0);
        local_20 = 0.0;
        local_1c = 5.0;
        local_18 = 0.0;
        FUN_004021a7(local_44,&local_20);
        fVar9 = (float10)FUN_004022a2();
        if ((float10)(float)local_8 * (float10)(float)local_8 < fVar9) {
          *(float *)(param_2 + 0xdc) = DAT_00c06978;
        }
        *(float *)(param_2 + 0xd8) = DAT_00c06978;
      }
      param_1[0x35] = DAT_00c06978;
      *(float *)(param_2 + 0xd4) = DAT_00c06978;
      if (*(char *)(param_2 + 0xd0) == '\0') {
        param_1[0x17] = 0.0;
      }
      if (*(char *)(param_1 + 0x34) == '\0') {
        *(undefined4 *)(param_2 + 0x5c) = 0;
      }
      *(undefined1 *)((int)param_1 + 0x59) = 0;
      *(undefined1 *)(param_2 + 0x59) = 0;
    }
  }
  return 1;
}



// ==== 0x40a477 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040a477(void)

{
  undefined *puVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  undefined *puVar12;
  float *pfVar13;
  char *pcVar14;
  undefined4 *puVar15;
  bool bVar16;
  float10 fVar17;
  undefined8 uVar18;
  undefined1 local_23c [36];
  undefined1 local_218 [36];
  undefined1 local_1f4 [36];
  undefined4 local_1d0 [9];
  undefined1 local_1ac [12];
  undefined1 local_1a0 [12];
  undefined1 local_194 [12];
  undefined1 local_188 [12];
  undefined1 local_17c [12];
  undefined1 local_170 [12];
  undefined1 local_164 [12];
  undefined1 local_158 [12];
  undefined1 local_14c [12];
  undefined1 local_140 [12];
  undefined1 local_134 [12];
  undefined1 local_128 [12];
  undefined1 local_11c [12];
  undefined1 local_110 [12];
  undefined1 local_104 [12];
  undefined1 local_f8 [12];
  undefined1 local_ec [12];
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined1 local_80 [12];
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined1 local_68 [12];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float fStack_4c;
  float fStack_48;
  undefined1 local_44 [15];
  char local_35;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float *local_18;
  float *local_14;
  float local_10;
  char *local_c;
  float local_8;
  
  DAT_00562c18 = (float *)&DAT_00531400;
  DAT_00562c14 = &DAT_00511e00;
  if (&DAT_00746c30 < DAT_00561408) {
    local_8 = -NAN;
    local_c = &DAT_00746c88;
    pcVar14 = &DAT_00746d00;
    do {
      if (*local_c == '\0') {
        if ((*pcVar14 == '\0') && (pcVar14[-0x77] == '\0')) {
          if (&DAT_00746c30 < pcVar14 + -0xd0) {
            puVar11 = &DAT_00746cb4;
            local_10 = (float)((uint)local_8 / 0xfc + 1);
            do {
              if ((*(char *)(puVar11 + -0xb) == '\0') && (*pcVar14 == '\0')) {
                local_14 = (float *)((float)puVar11[-0x16] + *(float *)(pcVar14 + -0xa4));
                FUN_004021a7(local_bc,puVar11);
                fVar17 = (float10)FUN_004022a2();
                if (fVar17 < (float10)(float)local_14 * (float10)(float)local_14) {
                  FUN_00409fce();
                }
              }
              puVar11 = puVar11 + 0x3f;
              local_10 = (float)((int)local_10 + -1);
            } while (local_10 != 0.0);
            local_10 = 0.0;
          }
        }
        else if (&DAT_00746c30 < pcVar14 + -0xd0) {
          pcVar10 = &DAT_00746c89;
          local_14 = (float *)((uint)local_8 / 0xfc + 1);
          do {
            if (((pcVar10[-1] == '\0') && (*pcVar10 == '\0')) && (pcVar10[0x77] == '\0')) {
              local_10 = *(float *)(pcVar10 + -0x2d) + *(float *)(pcVar14 + -0xa4);
              FUN_004021a7(local_80,pcVar10 + 0x2b);
              fVar17 = (float10)FUN_004022a2();
              if (fVar17 < (float10)local_10 * (float10)local_10) {
                FUN_00409fce();
              }
            }
            pcVar10 = pcVar10 + 0xfc;
            local_14 = (float *)((int)local_14 + -1);
          } while (local_14 != (float *)0x0);
        }
      }
      local_c = local_c + 0xfc;
      local_8 = (float)((int)local_8 + 0xfc);
      pcVar10 = pcVar14 + 0x2c;
      pcVar14 = pcVar14 + 0xfc;
    } while (pcVar10 < DAT_00561408);
  }
  if (&DAT_00521e00 < DAT_00561404) {
    puVar12 = &DAT_00521e14;
    local_18 = (float *)(((int)DAT_00561404 - 0x521e01U) / 0xf4 + 1);
    do {
      iVar9 = *(int *)(puVar12 + -0x14);
      if ((*(char *)(iVar9 + 0x58) == '\0') &&
         (iVar2 = *(int *)(puVar12 + -0x10), *(char *)(iVar2 + 0x58) == '\0')) {
        FUN_004021a7(local_bc,iVar2 + 0x90);
        local_10 = -0.2 / (*(float *)(iVar9 + 0xb8) + *(float *)(iVar2 + 0xb8));
        FUN_00402227(local_164,&local_10);
        FUN_004086a6(puVar12 + -0x14);
        local_10 = *(float *)(puVar12 + -0x14);
        *(undefined4 *)(puVar12 + 0xdc) = 0;
        uVar18 = CONCAT44((int)local_10 + 0x84,local_68);
        FUN_004023c6(local_110,(int)local_10 + 0x60);
        FUN_00402172(uVar18);
        uVar18 = CONCAT44(*(int *)(puVar12 + -0x10) + 0x84,local_44);
        FUN_004023c6(local_194,*(int *)(puVar12 + -0x10) + 0x60);
        FUN_00402172(uVar18);
        FUN_00408520(local_23c,local_44,local_44);
        puVar6 = local_1f4;
        FUN_00408520(local_218,local_68,local_68);
        FUN_0040809f(puVar6);
        puVar11 = (undefined4 *)FUN_00407ebb();
        puVar15 = (undefined4 *)(puVar12 + 0x5c);
        for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar15 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar15 = puVar15 + 1;
        }
        local_c = (char *)0x3f800000;
        puVar11 = (undefined4 *)FUN_00402227(local_17c,&local_c);
        local_b0 = *puVar11;
        uStack_ac = puVar11[1];
        uStack_a8 = puVar11[2];
        if (*(char *)((int)local_10 + 0xd0) == '\0') {
          uVar5 = FUN_00406e8a();
          FUN_00408612(local_68,uVar5);
        }
        if (*(char *)(*(int *)(puVar12 + -0x10) + 0xd0) == '\0') {
          FUN_00408612(local_44,&local_b0);
        }
        FUN_004023c6(&local_a0,*(int *)(puVar12 + -0x14) + 0x60);
        FUN_004023c6(&local_8c,*(int *)(puVar12 + -0x10) + 0x60);
        FUN_004021dc(&local_34,&local_8c);
        local_50 = local_34;
        fStack_4c = local_30;
        fStack_48 = local_2c;
        local_14 = (float *)(local_30 * local_30 + local_2c * local_2c + local_34 * local_34);
        FUN_004022c1();
        FUN_004023c6(&local_5c,*(int *)(puVar12 + -0x14) + 0x60);
        FUN_004023c6(local_80,*(int *)(puVar12 + -0x10) + 0x60);
        FUN_004021dc(&local_28,local_80);
        if (*(float *)(puVar12 + 0x3c) == 0.0) {
          fVar17 = (float10)FUN_0041d134((double)(float)local_14);
          fVar17 = (float10)FUN_004046eb((float)fVar17,
                                         local_88 * local_9c +
                                         local_84 * local_98 + local_8c * local_a0);
          local_c = (char *)(float)-fVar17;
          fVar17 = (float10)FUN_0041cd94((double)-fVar17);
          local_10 = (float)fVar17;
          fVar17 = (float10)FUN_0041d084((double)(float)local_c);
          FUN_00402e1d(&local_50,local_10,(float)fVar17);
          local_1c = local_24 * local_24 + local_20 * local_20 + local_28 * local_28;
          if (*(float *)(puVar12 + 0x44) < local_1c) {
            *(uint *)(puVar12 + 0xdc) = *(uint *)(puVar12 + 0xdc) | 2;
            FUN_004021dc(&local_74,local_80);
            local_10 = (float)local_c * -0.5;
            fVar17 = (float10)FUN_0041cd94((double)local_10);
            local_c = (char *)(float)fVar17;
            fVar17 = (float10)FUN_0041d084((double)local_10);
            FUN_00402e1d(&local_50,local_c,(float)fVar17);
            FUN_004022c1();
            *(undefined4 *)(puVar12 + 200) = local_74;
            *(undefined4 *)(puVar12 + 0xcc) = uStack_70;
            *(undefined4 *)(puVar12 + 0xd0) = uStack_6c;
            fVar17 = (float10)FUN_0041d134((double)*(float *)(puVar12 + 0x44));
            iVar9 = *(int *)(puVar12 + -0x14);
            local_10 = (float)fVar17;
            fVar17 = (float10)FUN_0041d134((double)local_1c);
            local_10 = (float)(((fVar17 - (float10)local_10) * (float10)0.04) /
                               ((float10)*(float *)(iVar9 + 0xb8) +
                               (float10)*(float *)(*(int *)(puVar12 + -0x10) + 0xb8)) +
                              (float10)*(float *)(puVar12 + 0xd8));
            uVar5 = FUN_00402227(local_188,&local_10);
            FUN_0040846d(local_68,uVar5);
            uVar18 = CONCAT44(&local_10,local_e0);
            puVar6 = local_c8;
            goto LAB_0040a8df;
          }
          *(undefined4 *)(puVar12 + 0xd8) = 0;
        }
        else {
          local_8 = 0.01;
          uVar5 = FUN_00402227(local_128,&local_8);
          FUN_0040846d(local_68,uVar5);
          uVar18 = CONCAT44(&local_8,local_170);
          FUN_00406e8a(local_1ac);
          uVar5 = FUN_00402227(uVar18);
          FUN_0040846d(local_44,uVar5);
          *(uint *)(puVar12 + 0xdc) = *(uint *)(puVar12 + 0xdc) | 4;
          FUN_004022c1();
          local_8 = *(float *)(puVar12 + 0xd8);
          *(float *)(puVar12 + 200) = local_28;
          *(float *)(puVar12 + 0xcc) = local_24;
          *(float *)(puVar12 + 0xd0) = local_20;
          uVar5 = FUN_00402227(local_134,&local_8);
          FUN_0040846d(local_68,uVar5);
          uVar18 = CONCAT44(&local_8,local_1a0);
          puVar6 = local_14c;
LAB_0040a8df:
          FUN_00406e8a(puVar6);
          uVar5 = FUN_00402227(uVar18);
          FUN_0040846d(local_44,uVar5);
        }
        if (*(float *)(puVar12 + 0x40) <= (float)local_14) {
          *(uint *)(puVar12 + 0xdc) = *(uint *)(puVar12 + 0xdc) | 1;
          *(float *)(puVar12 + 0xbc) = local_50;
          *(float *)(puVar12 + 0xc0) = fStack_4c;
          *(float *)(puVar12 + 0xc4) = fStack_48;
          fVar17 = (float10)FUN_0041d134((double)*(float *)(puVar12 + 0x40));
          iVar9 = *(int *)(puVar12 + -0x14);
          local_1c = (float)fVar17;
          fVar17 = (float10)FUN_0041d134((double)(float)local_14);
          local_10 = (float)(((fVar17 - (float10)local_1c) * (float10)0.2) /
                             ((float10)*(float *)(iVar9 + 0xb8) +
                             (float10)*(float *)(*(int *)(puVar12 + -0x10) + 0xb8)) +
                            (float10)*(float *)(puVar12 + 0xd4));
          uVar5 = FUN_00402227(local_d4,&local_10);
          FUN_0040846d(local_68,uVar5);
          uVar18 = CONCAT44(&local_10,local_ec);
          FUN_00406e8a(local_104);
          uVar5 = FUN_00402227(uVar18);
          FUN_0040846d(local_44,uVar5);
        }
      }
      puVar12 = puVar12 + 0xf4;
      local_18 = (float *)((int)local_18 + -1);
    } while (local_18 != (float *)0x0);
  }
  pfVar13 = (float *)&DAT_00531400;
  _DAT_00511df8 = &DAT_00562c20;
  if (&DAT_00531400 < DAT_00562c18) {
    do {
      pfVar13[0x16] = (float)&DAT_00562c20;
      puVar11 = (undefined4 *)FUN_00408520(local_218,pfVar13,pfVar13);
      puVar15 = local_1d0;
      for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar15 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar15 = puVar15 + 1;
      }
      uVar5 = FUN_00408520(local_1f4,CONCAT44(pfVar13,pfVar13));
      puVar11 = (undefined4 *)FUN_0040809f(local_23c,uVar5);
      puVar15 = local_1d0;
      for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar15 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar15 = puVar15 + 1;
      }
      pfVar13[0x17] = (float)&DAT_00562c20;
      DAT_00766432 = 0;
      pfVar7 = (float *)FUN_00407ebb();
      pfVar8 = pfVar13 + 0xb;
      pfVar13 = pfVar13 + 0x18;
      bVar16 = pfVar13 < DAT_00562c18;
      for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar8 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar8 = pfVar8 + 1;
      }
    } while (bVar16);
  }
  local_14 = (float *)0x0;
  do {
    if (&DAT_00531400 < DAT_00562c18) {
      pfVar13 = (float *)&DAT_0053141c;
      do {
        if (pfVar13[0xd] != 0.0) {
          pfVar13[0xd] = (float)((int)pfVar13[0xd] + -1);
          if (local_14 == (float *)0x0) {
            local_34 = pfVar13[-1];
            local_30 = *pfVar13;
            local_2c = pfVar13[1];
          }
          else {
            uVar5 = FUN_00408401(local_104,pfVar13 + -7);
            uVar18 = CONCAT44(uVar5,local_bc);
            FUN_00408401(local_ec,pfVar13 + -7);
            FUN_004021a7(uVar18);
            pfVar8 = (float *)FUN_004023c6(local_d4,pfVar13 + 4);
            local_34 = *pfVar8 + pfVar13[-1];
            local_30 = pfVar8[1] + *pfVar13;
            local_2c = pfVar8[2] + pfVar13[1];
            local_8 = local_34 * pfVar13[-4] + local_30 * pfVar13[-3] + local_2c * pfVar13[-2];
            uVar5 = FUN_00402227(local_c8,&local_8);
            FUN_004021a7(&local_28,uVar5);
            if (0.0 <= local_8) {
              fVar3 = local_28 * local_28 + local_24 * local_24 + local_20 * local_20;
              if ((fVar3 != 0.0) && (local_8 * local_8 * 0.80999994 < fVar3)) {
                fVar17 = (float10)FUN_0041d134((double)fVar3);
                fVar17 = ((float10)local_8 / fVar17) * (float10)0.9;
                local_28 = (float)((float10)local_28 * fVar17);
                local_24 = (float)((float10)local_24 * fVar17);
                local_20 = (float)((float10)local_20 * fVar17);
              }
              uVar5 = FUN_00402227(local_e0,&local_8);
              pfVar8 = (float *)FUN_00402172(local_188,uVar5);
            }
            else {
              pfVar8 = &local_5c;
              local_5c = 0.0;
              local_58 = 0.0;
              local_54 = 0.0;
            }
            local_34 = *pfVar8;
            local_30 = pfVar8[1];
            local_34 = *pfVar8 - pfVar13[-1];
            local_30 = pfVar8[1] - *pfVar13;
            local_2c = pfVar8[2] - pfVar13[1];
            pfVar13[-1] = local_34 + pfVar13[-1];
            *pfVar13 = local_30 + *pfVar13;
            pfVar13[1] = local_2c + pfVar13[1];
          }
          if (*(char *)((int)pfVar13[2] + 0xd0) == '\0') {
            uVar5 = FUN_00406e8a();
            FUN_00408612(pfVar13 + -7,uVar5);
          }
          if (*(char *)((int)pfVar13[3] + 0xd0) == '\0') {
            FUN_00408612(pfVar13 + -7,&local_34);
          }
          *(undefined4 *)((int)pfVar13[2] + 0xe4) = 0;
        }
        pfVar8 = pfVar13 + 0x11;
        pfVar13 = pfVar13 + 0x18;
      } while (pfVar8 < DAT_00562c18);
    }
    if (&DAT_00521e00 < DAT_00561404) {
      pfVar13 = (float *)&DAT_00521ee4;
      do {
        fVar3 = pfVar13[-0x39];
        if ((*(char *)((int)fVar3 + 0x58) == '\0') &&
           (fVar4 = pfVar13[-0x38], *(char *)((int)fVar4 + 0x58) == '\0')) {
          uVar18 = CONCAT44((int)fVar3 + 0x84,&local_50);
          FUN_004023c6(local_1a0,(int)fVar3 + 0x60);
          FUN_00402172(uVar18);
          uVar18 = CONCAT44((int)fVar4 + 0x84,local_44);
          FUN_004023c6(local_134,(int)fVar4 + 0x60);
          FUN_00402172(uVar18);
          uVar5 = FUN_00408401(local_1ac,local_44);
          uVar18 = CONCAT44(uVar5,&local_b0);
          FUN_00408401(local_170,&local_50);
          FUN_004021a7(uVar18);
          uVar18 = CONCAT44(pfVar13 + -0x1d,local_80);
          pfVar8 = &local_1c;
          puVar6 = local_128;
          local_1c = 0.03;
          FUN_004021a7(local_11c,&local_50);
          uVar5 = FUN_00402227(puVar6,pfVar8);
          FUN_004021a7(local_17c,uVar5);
          FUN_004023c6(uVar18);
          if (*(char *)((int)fVar3 + 0xd0) == '\0') {
            uVar5 = FUN_00406e8a();
            FUN_00408612(&local_50,uVar5);
          }
          if (*(char *)((int)pfVar13[-0x38] + 0xd0) == '\0') {
            FUN_00408612(local_44,local_80);
          }
          if (((uint)pfVar13[3] & 4) != 0) {
            fVar3 = pfVar13[-0x38];
            fVar4 = pfVar13[-0x39];
            pfVar8 = (float *)FUN_004021a7(local_110,(int)fVar3 + 0x90);
            fVar3 = (*pfVar8 * pfVar13[-2] + pfVar8[2] * *pfVar13 + pfVar8[1] * pfVar13[-1]) *
                    (0.9 / (*(float *)((int)fVar4 + 0xb8) + *(float *)((int)fVar3 + 0xb8))) +
                    pfVar13[2];
            if (fVar3 < 0.0) {
              fVar3 = 0.0;
            }
            local_c = (char *)(fVar3 - pfVar13[2]);
            pfVar13[2] = (float)local_c + pfVar13[2];
            uVar5 = FUN_00402227(local_164,&local_c);
            FUN_0040846d(&local_50,uVar5);
            local_18 = (float *)-(float)local_c;
            uVar5 = FUN_00402227(&local_a0,&local_18);
            FUN_0040846d(local_44,uVar5);
          }
          if (((uint)pfVar13[3] & 1) != 0) {
            fVar3 = pfVar13[-0x38];
            fVar4 = pfVar13[-0x39];
            pfVar8 = (float *)FUN_004021a7(&local_8c,(int)fVar3 + 0x90);
            fVar3 = (*pfVar8 * pfVar13[-5] + pfVar8[1] * pfVar13[-4] + pfVar13[-3] * pfVar8[2]) *
                    (0.9 / (*(float *)((int)fVar4 + 0xb8) + *(float *)((int)fVar3 + 0xb8))) +
                    pfVar13[1];
            if (fVar3 < 0.0) {
              fVar3 = 0.0;
            }
            local_c = (char *)(fVar3 - pfVar13[1]);
            pfVar13[1] = (float)local_c + pfVar13[1];
            uVar5 = FUN_00402227(&local_74,&local_c);
            FUN_0040846d(&local_50,uVar5);
            local_18 = (float *)-(float)local_c;
            uVar5 = FUN_00402227(local_68,&local_18);
            FUN_0040846d(local_44,uVar5);
          }
          if (((uint)pfVar13[3] & 2) != 0) {
            fVar3 = pfVar13[-0x38];
            fVar4 = pfVar13[-0x39];
            pfVar8 = (float *)FUN_004021a7(local_140,(int)fVar3 + 0x90);
            fVar3 = (pfVar13[-2] * *pfVar8 + pfVar8[2] * *pfVar13 + pfVar8[1] * pfVar13[-1]) *
                    (0.9 / (*(float *)((int)fVar4 + 0xb8) + *(float *)((int)fVar3 + 0xb8))) +
                    pfVar13[2];
            if (fVar3 < 0.0) {
              fVar3 = 0.0;
            }
            local_c = (char *)(fVar3 - pfVar13[2]);
            pfVar13[2] = (float)local_c + pfVar13[2];
            uVar5 = FUN_00402227(local_158,&local_c);
            FUN_0040846d(&local_50,uVar5);
            local_18 = (float *)-(float)local_c;
            uVar5 = FUN_00402227(local_f8,&local_18);
            FUN_0040846d(local_44,uVar5);
          }
        }
        pfVar8 = pfVar13 + 4;
        pfVar13 = pfVar13 + 0x3d;
      } while (pfVar8 < DAT_00561404);
    }
    FUN_0040fd42();
    pcVar14 = DAT_00561408;
    local_14 = (float *)((int)local_14 + 1);
  } while ((int)local_14 < 0x28);
  for (pcVar10 = (char *)&DAT_00746c30; pcVar10 < pcVar14; pcVar10 = pcVar10 + 0xfc) {
    pcVar10[0xe4] = '\0';
    pcVar10[0xe5] = '\0';
    pcVar10[0xe6] = '\0';
    pcVar10[0xe7] = '\0';
  }
  DAT_00561400 = (float *)&DAT_005aec28;
  DAT_00562c18[10] = 0.0;
  pfVar13 = (float *)&DAT_00531400;
  if (&DAT_00531400 < DAT_00562c18) {
    local_5c = 0.0;
    local_58 = 0.0;
    local_54 = 0.0;
    do {
      DAT_00561400[1] = 0.0;
      local_8 = 0.0;
      local_18 = (float *)pfVar13[10];
      local_c = (char *)0x0;
      local_28 = local_5c;
      local_1c = pfVar13[9];
      local_24 = local_58;
      local_35 = *(char *)(pfVar13 + 0x15);
      local_20 = local_54;
      local_14 = pfVar13;
      do {
        pfVar8 = pfVar13;
        if ((pfVar13[9] != local_1c) || (0xf < (int)DAT_00561400[1])) break;
        fVar17 = (float10)FUN_004022a2();
        fVar17 = (float10)FUN_0041d134((double)fVar17);
        local_c = local_c + 1;
        local_8 = (float)(fVar17 + (float10)local_8);
        local_28 = local_28 + *pfVar13;
        pfVar7 = DAT_00561400 + (int)DAT_00561400[1] * 3 + 2;
        pfVar8 = pfVar13 + 0x18;
        local_24 = local_24 + pfVar13[1];
        local_20 = local_20 + pfVar13[2];
        *pfVar7 = pfVar13[6];
        pfVar7[1] = pfVar13[7];
        pfVar7[2] = pfVar13[8];
        DAT_00561400[1] = (float)((int)DAT_00561400[1] + 1);
        pfVar7 = pfVar13 + 0x22;
        pfVar13 = pfVar8;
      } while ((float *)*pfVar7 == local_18);
      pfVar13 = pfVar8 + -0x18;
      local_18 = pfVar13;
      if ((0.3 < local_8) && (local_35 == '\0')) {
        fVar3 = pfVar8[-0xf];
        if ((*(float *)((int)fVar3 + 0xac) * 0.04 < local_8) &&
           ((*(int *)((int)fVar3 + 0xc0) != 0 && (*(float *)((int)fVar3 + 0xcc) * 3.0 < local_8))))
        {
          fVar17 = (float10)FUN_0041cf20((double)(*(float *)((int)fVar3 + 0x38) /
                                                 *(float *)((int)fVar3 + 200)));
          fVar17 = (float10)FUN_0041ce90((double)(fVar17 * (float10)-0.25));
          FUN_0041538b(*(undefined4 *)((int)pfVar8[-0xf] + 0xc0),(float)fVar17,
                       local_8 * *(float *)((int)pfVar8[-0xf] + 0xc4),0);
        }
        if (*(float *)((int)pfVar8[-0xf] + 0xcc) < local_8) {
          *(float *)((int)pfVar8[-0xf] + 0xcc) = local_8;
        }
        fVar3 = pfVar8[-0xe];
        if (((*(float *)((int)fVar3 + 0xac) * 0.04 < local_8) && (*(int *)((int)fVar3 + 0xc0) != 0))
           && (*(float *)((int)fVar3 + 0xcc) * 3.0 < local_8)) {
          fVar17 = (float10)FUN_0041cf20((double)(*(float *)((int)fVar3 + 0x38) /
                                                 *(float *)((int)fVar3 + 200)));
          fVar17 = (float10)FUN_0041ce90((double)(fVar17 * (float10)-0.25));
          FUN_0041538b(*(undefined4 *)((int)pfVar8[-0xe] + 0xc0),(float)fVar17,
                       local_8 * *(float *)((int)pfVar8[-0xe] + 0xc4),0);
        }
        if (*(float *)((int)pfVar8[-0xe] + 0xcc) < local_8) {
          *(float *)((int)pfVar8[-0xe] + 0xcc) = local_8;
        }
      }
      if (*(float *)((int)pfVar8[-0xf] + 0x54) < local_8) {
        pfVar8 = local_14;
        if (local_14 < pfVar13) {
          local_10 = 0.25;
          local_90 = 0x3e800000;
          do {
            uVar5 = FUN_00402227(local_f8,&local_10);
            FUN_00408612(pfVar8,uVar5);
            uVar18 = CONCAT44(&local_90,local_158);
            FUN_00406e8a(local_140);
            uVar5 = FUN_00402227(uVar18);
            FUN_00408612(pfVar8,uVar5);
            pfVar8 = pfVar8 + 0x18;
          } while (pfVar8 < pfVar13);
        }
        local_14 = pfVar8;
        local_1c = 1.0 / (float)(int)local_c;
        FUN_00402227(local_104,&local_1c);
        FUN_00409b35();
        pfVar13 = local_18;
      }
      if (*(float *)((int)pfVar13[10] + 0x54) < local_8) {
        if (local_14 < pfVar13) {
          local_94 = 0x3e800000;
          local_a4 = 0x3e800000;
          pfVar8 = local_14;
          do {
            uVar5 = FUN_00402227(local_ec,&local_94);
            FUN_00408612(pfVar8,uVar5);
            uVar18 = CONCAT44(&local_a4,local_d4);
            FUN_00406e8a(local_c8);
            uVar5 = FUN_00402227(uVar18);
            FUN_00408612(pfVar8,uVar5);
            pfVar8 = pfVar8 + 0x18;
          } while (pfVar8 < pfVar13);
        }
        local_1c = 1.0 / (float)(int)local_c;
        FUN_00402227(local_e0,&local_1c);
        FUN_00409b35();
        pfVar13 = local_18;
      }
      DAT_00561400[0x32] = *(float *)((int)pfVar13[9] + 0xe4);
      *DAT_00561400 = pfVar13[10];
      *(float **)((int)pfVar13[9] + 0xe4) = DAT_00561400;
      DAT_00561400 = DAT_00561400 + 0x33;
      pfVar13 = pfVar13 + 0x18;
    } while (pfVar13 < DAT_00562c18);
  }
  if (&DAT_00511e00 < DAT_00562c14) {
    puVar12 = &DAT_00511e0c;
    do {
      FUN_00408612(puVar12 + -0xc,puVar12);
      uVar5 = FUN_00406e8a();
      FUN_00408612(puVar12 + -0xc,uVar5);
      puVar1 = puVar12 + 0x14;
      puVar12 = puVar12 + 0x20;
    } while (puVar1 < DAT_00562c14);
  }
  return;
}



// ==== 0x40b5aa ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040b5aa(void)

{
  undefined4 *puVar1;
  float10 fVar2;
  
  _DAT_005aec20 = 1.0 / _DAT_00453cd0;
  puVar1 = &DAT_00746c30;
  if (&DAT_00746c30 < DAT_00561408) {
    do {
      fVar2 = (float10)FUN_004022a2();
      if ((float10)1e-05 < fVar2) {
        FUN_004096d2();
      }
      puVar1 = puVar1 + 0x3f;
    } while (puVar1 < DAT_00561408);
  }
  return;
}



// ==== 0x40b5f7 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040b5f7(void)

{
  undefined4 *puVar1;
  
  FUN_00408ee9();
  FUN_00407e0c();
  if (DAT_00c0682c < 2) {
    if (DAT_00766434 == 0) {
      _DAT_005aec20 = 1.0 / _DAT_00453cd0;
      DAT_004536e8 = 1;
      FUN_0040a477();
      puVar1 = &DAT_00746c30;
      if (&DAT_00746c30 < DAT_00561408) {
        do {
          FUN_00409a6c();
          puVar1 = puVar1 + 0x3f;
        } while (puVar1 < DAT_00561408);
      }
      FUN_00414edb();
    }
    DAT_00766434 = 0;
    DAT_00746c28 = 1;
    if (DAT_00c0682c < 2) goto LAB_0040b674;
  }
  FUN_0040b5aa();
LAB_0040b674:
  FUN_0040d7cf();
  FUN_004165db();
  _DAT_00511dec = _DAT_00511dec + 1;
  return;
}



// ==== 0x40b685 ====

void FUN_0040b685(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 local_8;
  
  if ((((param_1 < 0) || (0x7a60 < param_1)) || (param_2 < 0)) || (0x7581 < param_2)) {
    param_1 = 0x4cf;
    param_2 = 0x1cba;
  }
  iVar3 = param_1 / 0xb1;
  iVar5 = param_1 % 0xb1;
  param_1 = 1;
  iVar5 = iVar5 + 2;
  iVar4 = param_2 / 0xa9;
  param_2 = param_2 % 0xa9;
  iVar6 = iVar3 % 0xb1 + 2;
  iVar3 = iVar4 % 0xb2 + 1;
  do {
    fVar2 = 0.0;
    local_8 = 0x18;
    iVar4 = iVar5;
    iVar7 = iVar6;
    fVar1 = 0.5;
    do {
      iVar5 = iVar3;
      iVar6 = iVar4;
      iVar3 = (((iVar6 * iVar7) % 0xb3) * iVar5) % 0xb3;
      param_2 = (param_2 * 0x35 + 1) % 0xa9;
      if (0x1f < (iVar3 * param_2) % 0x40) {
        fVar2 = fVar1 + fVar2;
      }
      local_8 = local_8 + -1;
      fVar1 = fVar1 * 0.5;
      iVar4 = iVar5;
      iVar7 = iVar6;
    } while (local_8 != 0);
    iVar4 = param_1 + 1;
    *(float *)(in_ECX + param_1 * 4) = fVar2;
    param_1 = iVar4;
  } while (iVar4 < 0x62);
  *(undefined4 *)(in_ECX + 0x188) = 0x3cb0f880;
  *(undefined4 *)(in_ECX + 0x18c) = 0x3ee99762;
  *(undefined4 *)(in_ECX + 400) = 0x3f7ffffd;
  *(undefined4 *)(in_ECX + 0x194) = 0x61;
  *(undefined4 *)(in_ECX + 0x198) = 0x21;
  return;
}



// ==== 0x40b798 ====

float10 FUN_0040b798(void)

{
  int *piVar1;
  float *pfVar2;
  float fVar3;
  int in_ECX;
  float10 fVar4;
  
  pfVar2 = (float *)(in_ECX + *(int *)(in_ECX + 0x194) * 4);
  fVar4 = (float10)*pfVar2 - (float10)*(float *)(in_ECX + *(int *)(in_ECX + 0x198) * 4);
  if (fVar4 < (float10)0.0) {
    fVar4 = fVar4 + (float10)1.0;
  }
  *pfVar2 = (float)fVar4;
  piVar1 = (int *)(in_ECX + 0x194);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    *(undefined4 *)(in_ECX + 0x194) = 0x61;
  }
  piVar1 = (int *)(in_ECX + 0x198);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    *(undefined4 *)(in_ECX + 0x198) = 0x61;
  }
  fVar3 = *(float *)(in_ECX + 0x188) - *(float *)(in_ECX + 0x18c);
  *(float *)(in_ECX + 0x188) = fVar3;
  if (fVar3 < 0.0) {
    *(float *)(in_ECX + 0x188) = fVar3 + *(float *)(in_ECX + 400);
  }
  fVar4 = fVar4 - (float10)*(float *)(in_ECX + 0x188);
  if (fVar4 < (float10)0.0) {
    fVar4 = fVar4 + (float10)1.0;
  }
  return fVar4;
}



// ==== 0x40b83f ====

void FUN_0040b83f(void)

{
  thunk_FUN_0040386a();
  (**(code **)(*DAT_004571ec + 0x68))(DAT_004571ec,0x240000,0x208,DAT_004536ec,0,&DAT_00c06800,0);
  (**(code **)(*DAT_004571ec + 0x68))(DAT_004571ec,0x120000,0x208,DAT_004536f4,0,&DAT_00a466e0,0);
  return;
}



// ==== 0x40b88c ====

void FUN_0040b88c(undefined4 *param_1,float *param_2)

{
  int iVar1;
  float10 fVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  undefined1 local_30 [12];
  undefined1 local_24 [12];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_8 = (float)DAT_00c06978 * 0.02;
  fVar2 = (float10)FUN_0041cd94((double)(local_8 * 1.37));
  local_c = (float)(fVar2 + (float10)local_8);
  fVar2 = (float10)FUN_0041d084();
  local_18 = *param_2;
  local_14 = param_2[1];
  local_8 = (float)(fVar2 + (float10)local_8);
  local_10 = param_2[2];
  FUN_004022c1();
  iVar1 = 3;
  local_10 = 1.0;
  local_c = local_c * 1.1;
  do {
    fVar2 = (float10)FUN_0041d084((double)(local_14 * 10.0 + local_8));
    fVar2 = fVar2 * (float10)0.004 + (float10)local_18;
    local_18 = (float)fVar2;
    fVar2 = (float10)FUN_0041cd94((double)(fVar2 * (float10)10.0 + (float10)local_c));
    iVar1 = iVar1 + -1;
    local_14 = (float)(fVar2 * (float10)0.004 + (float10)local_14);
  } while (iVar1 != 0);
  uVar5 = CONCAT44(&DAT_00c06948,&local_18);
  puVar4 = &DAT_00c06954;
  puVar3 = local_24;
  FUN_00402172(local_30,param_2);
  FUN_004023c6(puVar3,puVar4);
  puVar4 = (undefined4 *)FUN_00402172(uVar5);
  *param_1 = *puVar4;
  param_1[1] = puVar4[1];
  param_1[2] = puVar4[2];
  return;
}



// ==== 0x40b97a ====

void FUN_0040b97a(void)

{
  DAT_00c06804 = &DAT_009b66e0;
  return;
}



// ==== 0x40b985 ====

void FUN_0040b985(float param_1,float param_2,byte *param_3,uint param_4)

{
  undefined4 *puVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined1 local_17c [12];
  undefined1 local_170 [12];
  undefined1 local_164 [12];
  undefined1 local_158 [12];
  undefined1 local_14c [12];
  undefined1 local_140 [12];
  undefined1 local_134 [12];
  undefined1 local_128 [12];
  undefined1 local_11c [12];
  undefined1 local_110 [12];
  undefined1 local_104 [12];
  undefined1 local_f8 [12];
  undefined1 local_ec [12];
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [12];
  undefined1 local_b0 [12];
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_20 = 0x3b83126f;
  local_1c = 0x3b83126f;
  local_18 = 0;
  local_68 = 0x3b83126f;
  uStack_64 = 0x3b83126f;
  uStack_60 = 0;
  FUN_004023c6(&local_20,&DAT_00c06954);
  local_2c = param_1;
  uVar5 = param_4 & 0xff000000;
  pbVar2 = param_3;
  while (param_3 = pbVar2, *param_3 != 0) {
    puVar3 = (undefined4 *)FUN_00402279(local_c8,param_1,param_2,0x3f800000);
    local_68 = *puVar3;
    uStack_64 = puVar3[1];
    uStack_60 = puVar3[2];
    puVar3 = (undefined4 *)FUN_0040b88c(local_17c,&local_68);
    local_24 = param_1 + 0.025;
    local_5c = *puVar3;
    uStack_58 = puVar3[1];
    uStack_54 = puVar3[2];
    puVar3 = (undefined4 *)FUN_00402279(local_b0,local_24,param_2,0x3f800000);
    local_8c = *puVar3;
    uStack_88 = puVar3[1];
    uStack_84 = puVar3[2];
    puVar3 = (undefined4 *)FUN_0040b88c(local_170,&local_8c);
    local_28 = param_2 - 0.038;
    local_50 = *puVar3;
    uStack_4c = puVar3[1];
    uStack_48 = puVar3[2];
    puVar3 = (undefined4 *)FUN_00402279(local_98,local_24,local_28,0x3f800000);
    local_74 = *puVar3;
    uStack_70 = puVar3[1];
    local_6c = puVar3[2];
    puVar3 = (undefined4 *)FUN_0040b88c(local_128,&local_74);
    local_44 = *puVar3;
    uStack_40 = puVar3[1];
    uStack_3c = puVar3[2];
    puVar3 = (undefined4 *)FUN_00402279(local_e0,param_1,local_28,0x3f800000);
    local_80 = *puVar3;
    uStack_7c = puVar3[1];
    uStack_78 = puVar3[2];
    puVar3 = (undefined4 *)FUN_0040b88c(local_158,&local_80);
    local_8 = (float)((int)(char)*param_3 / 0x10);
    local_10 = (float)(int)(char)(*param_3 & 0xf) * 0.0625;
    local_38 = *puVar3;
    uStack_34 = puVar3[1];
    uStack_30 = puVar3[2];
    local_c = (float)(int)local_8 * 0.0625;
    puVar4 = (undefined4 *)FUN_004021a7(local_f8,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_004021a7(local_140,&local_20);
    puVar1 = DAT_00c06804;
    local_14 = local_10 + 0.0625;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_004021a7(local_110,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    local_8 = local_c + 0.0625;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_004021a7(local_a4,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_004021a7(local_bc,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_004021a7(local_d4,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_ec,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_104,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_11c,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_134,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_14c,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    puVar4 = (undefined4 *)FUN_00402172(local_164,&local_20);
    puVar1 = DAT_00c06804;
    puVar3 = DAT_00c06804 + 1;
    *DAT_00c06804 = *puVar4;
    *puVar3 = puVar4[1];
    puVar1[2] = puVar4[2];
    DAT_00c06804[3] = uVar5;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_8;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_5c;
    puVar3[7] = uStack_58;
    puVar3[8] = uStack_54;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_c;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_50;
    puVar3[7] = uStack_4c;
    puVar3[8] = uStack_48;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_38;
    puVar3[7] = uStack_34;
    puVar3[8] = uStack_30;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_8;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_50;
    puVar3[7] = uStack_4c;
    puVar3[8] = uStack_48;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_c;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_44;
    puVar3[7] = uStack_40;
    puVar3[8] = uStack_3c;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_14;
    DAT_00c06804[5] = local_8;
    puVar3 = DAT_00c06804;
    DAT_00c06804 = DAT_00c06804 + 6;
    *DAT_00c06804 = local_38;
    puVar3[7] = uStack_34;
    puVar3[8] = uStack_30;
    DAT_00c06804[3] = param_4;
    DAT_00c06804[4] = local_10;
    DAT_00c06804[5] = local_8;
    DAT_00c06804 = DAT_00c06804 + 6;
    param_1 = local_24;
    pbVar2 = param_3 + 1;
    if (param_3[1] == 10) {
      param_1 = local_2c;
      param_2 = local_28;
      pbVar2 = param_3 + 2;
    }
  }
  return;
}



// ==== 0x40bfb0 ====

void FUN_0040bfb0(void)

{
  (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536ec);
  if ((DAT_00c06804 + -0x9b66e0) / 0x18 != 0) {
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x1b,1);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x13,5);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x14,6);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x16,1);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,7,0);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,2);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,0);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,2);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,1,1);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,4,4);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,5,2);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,6,0);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,4,1);
    FUN_00415c17(0,DAT_00c0f22c);
    (**(code **)(*DAT_004571ec + 0x14c))
              (DAT_004571ec,4,(DAT_00c06804 + -0x9b66e0) / 0x48,&DAT_009b66e0,0x18);
  }
  return;
}



// ==== 0x40c109 ====

int FUN_0040c109(int param_1)

{
  undefined1 *puVar1;
  int *in_ECX;
  
  if ((uint)(in_ECX[1] - *in_ECX) <= (uint)(param_1 * 0xc)) {
    puVar1 = (undefined1 *)0x0;
    do {
      puVar1 = puVar1 + 1;
      *puVar1 = 0x7f;
    } while( true );
  }
  return param_1 * 0xc + *in_ECX;
}



// ==== 0x40c12b ====

void FUN_0040c12b(void)

{
  uint uVar1;
  undefined1 *puVar2;
  void *pvVar3;
  undefined4 *in_ECX;
  uint _NewSize;
  
  uVar1 = (in_ECX[1] - (int)*in_ECX) / 0xc;
  _NewSize = ((uVar1 >> 3) + 1 + uVar1) * 0xc;
  if (0xfffffff < _NewSize) {
    puVar2 = (undefined1 *)0x0;
    do {
      puVar2 = puVar2 + 1;
      *puVar2 = 0x7f;
    } while( true );
  }
  pvVar3 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = pvVar3;
  in_ECX[2] = (void *)(_NewSize + (int)pvVar3);
  in_ECX[1] = (void *)((int)pvVar3 + uVar1 * 0xc);
  return;
}



// ==== 0x40c179 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040c179(void)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_d0 [12];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  undefined1 local_ac [12];
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined1 local_94 [12];
  int local_88 [5];
  int local_74;
  int local_70 [12];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  int local_1c;
  float *local_18;
  int local_14;
  float *local_10;
  undefined4 *local_c;
  int local_8;
  
  if (DAT_00d0f3bc < DAT_00d0f3c0) {
    local_88[4] = DAT_00453cc8 + 1;
    local_88[2] = DAT_00453cc8;
    local_74 = DAT_00453cc8;
    local_88[0] = 0;
    local_88[1] = 1;
    local_88[3] = 1;
    local_70[0] = 0;
    local_70[1] = 1;
    local_70[2] = 0;
    local_70[3] = 1;
    local_70[4] = 1;
    local_70[5] = 0;
    local_70[6] = 0;
    local_70[7] = 0;
    local_70[8] = 1;
    local_70[9] = 0;
    local_70[10] = 1;
    local_70[0xb] = 1;
    (**(code **)(*DAT_00c06800 + 0x2c))
              (DAT_00c06800,0,DAT_00453ccc * DAT_00453cc8 * 0x90,&local_c,0x2000);
    local_8 = 0;
    local_14 = 0;
    if (DAT_00453ccc != 1 && -1 < DAT_00453ccc + -1) {
      do {
        local_1c = 0;
        if (DAT_00453cc8 != 1 && -1 < DAT_00453cc8 + -1) {
          local_34 = (float)local_14;
          do {
            pfVar2 = (float *)FUN_00408f5e(local_8);
            local_10 = (float *)FUN_00408f5e(local_8 + DAT_00453cc8);
            local_18 = (float *)FUN_00408f5e(local_8);
            local_30 = local_8 + 1;
            pfVar3 = (float *)FUN_00408f5e(local_30);
            pfVar2 = (float *)FUN_00402279(local_ac,*local_18 - *pfVar3,_DAT_00453cd0,
                                           *pfVar2 - *local_10);
            local_2c = *pfVar2;
            local_28 = pfVar2[1];
            local_24 = pfVar2[2];
            FUN_004022c1();
            puVar4 = (undefined4 *)FUN_00408f5e(local_8);
            puVar4 = (undefined4 *)
                     FUN_00402279(local_c4,(float)local_1c * _DAT_00453cd0,*puVar4,
                                  local_34 * _DAT_00453cd0);
            local_a0 = *puVar4;
            uStack_9c = puVar4[1];
            uStack_98 = puVar4[2];
            FUN_004021a7(&local_40,&DAT_00c06948);
            fVar1 = local_40 * local_2c + local_3c * local_28 + local_38 * local_24;
            local_18 = (float *)(fVar1 + fVar1);
            uVar5 = FUN_00402227(local_b8,&local_18);
            FUN_004021a7(local_94,uVar5);
            FUN_004022c1();
            iVar6 = FUN_0041d384();
            local_18 = (float *)(iVar6 * 0x1030401 + 0xc0);
            local_10 = (float *)0x0;
            do {
              pfVar2 = local_10;
              local_c[3] = local_18;
              puVar4 = (undefined4 *)FUN_00408f5e(*(int *)((int)local_88 + (int)local_10) + local_8)
              ;
              iVar6 = *(int *)((int)local_70 + (int)pfVar2 + 0x18) + local_14;
              local_20 = iVar6;
              local_20 = *(int *)((int)local_70 + (int)pfVar2) + local_1c;
              puVar4 = (undefined4 *)
                       FUN_00402279(local_d0,(float)local_20 * _DAT_00453cd0,*puVar4,
                                    (float)iVar6 * _DAT_00453cd0);
              local_10 = (float *)((int)local_10 + 4);
              *local_c = *puVar4;
              local_c[1] = puVar4[1];
              local_c[2] = puVar4[2];
              local_c[4] = 0;
              local_c[5] = 0;
              local_c = local_c + 6;
            } while ((int)local_10 < 0x18);
            local_8 = local_30;
            local_1c = local_1c + 1;
          } while (local_1c < DAT_00453cc8 + -1);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
      } while (local_14 < DAT_00453ccc + -1);
    }
    (**(code **)(*DAT_00c06800 + 0x30))(DAT_00c06800);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,0);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,1,1);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,4,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,5,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,6,0);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,4,1);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x1b,1);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x13,6);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x14,5);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x16,1);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x34,0);
    (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536ec);
    (**(code **)(*DAT_004571ec + 0x144))
              (DAT_004571ec,4,0,(DAT_00453ccc + -1) * (DAT_00453cc8 + -1) * 2);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x16,3);
  }
  return;
}



// ==== 0x40c56a ====

void FUN_0040c56a(int param_1)

{
  uint uVar1;
  int iVar2;
  int *in_ECX;
  undefined4 *puVar3;
  
  iVar2 = *in_ECX;
  puVar3 = (undefined4 *)in_ECX[1];
  uVar1 = iVar2 + param_1 * 0xc;
  in_ECX[1] = uVar1;
  if ((uint)in_ECX[2] < uVar1) {
    FUN_0040c12b();
    puVar3 = (undefined4 *)(*in_ECX + (((int)puVar3 - iVar2) / 0xc) * 0xc);
  }
  for (; puVar3 < (undefined4 *)in_ECX[1]; puVar3 = puVar3 + 3) {
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
  }
  return;
}



// ==== 0x40c5c7 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040c5c7(void)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  float fVar3;
  undefined4 *puVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  float *pfVar10;
  undefined4 *puVar11;
  uint *in_ECX;
  uint uVar12;
  int *piVar13;
  undefined1 *puVar14;
  uint *puVar15;
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  undefined4 local_b4 [4];
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 local_9c [6];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  int local_54 [2];
  undefined4 *local_4c;
  int local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined4 *local_c;
  float *local_8;
  
  if ((char)in_ECX[0x16] == '\0') {
    FUN_0040c56a(((int)(in_ECX[1] - *in_ECX) >> 4) + 1);
    local_c = (undefined4 *)FUN_0040c109(0);
    local_8 = (float *)*in_ECX;
    if (local_8 < in_ECX[1]) {
      do {
        puVar15 = in_ECX + 0x21;
        piVar13 = local_54;
        FUN_004023c6(&local_60,in_ECX + 0x18);
        puVar4 = (undefined4 *)FUN_00402172(piVar13,puVar15);
        local_8 = (float *)((int)local_8 + 0x10);
        puVar11 = local_c + 3;
        *local_c = *puVar4;
        local_c[1] = puVar4[1];
        local_c[2] = puVar4[2];
        local_c = puVar11;
      } while (local_8 < in_ECX[1]);
    }
    FUN_00402363(&local_2c,&DAT_00a466e4);
    local_8 = (float *)in_ECX[4];
    if (local_8 < (float *)in_ECX[5]) {
      do {
        *(bool *)(local_8 + 8) =
             0.0 < local_2c * *local_8 + local_24 * local_8[2] + local_28 * local_8[1];
        local_44 = *local_8;
        local_40 = local_8[1];
        local_3c = local_8[2];
        FUN_004022c1();
        if (local_44 * local_44 <= local_40 * local_40) {
          local_78 = 0x3f800000;
          local_74 = 0;
          local_70 = 0;
          local_60 = 0x3f800000;
          uStack_5c = 0;
          uStack_58 = 0;
          if (local_40 * local_40 < local_3c * local_3c) {
            puVar11 = &local_84;
            local_84 = 0;
            local_80 = 0x3f800000;
            local_7c = 0;
            goto LAB_0040c711;
          }
        }
        else {
          puVar11 = &local_6c;
          local_6c = 0;
          local_68 = 0x3f800000;
          local_64 = 0;
LAB_0040c711:
          local_60 = *puVar11;
          uStack_5c = puVar11[1];
          uStack_58 = puVar11[2];
        }
        pfVar5 = (float *)FUN_004021dc(local_e4,&local_44);
        local_1c = *pfVar5;
        local_18 = pfVar5[1];
        local_14 = pfVar5[2];
        FUN_004022c1();
        pfVar5 = (float *)FUN_004021dc(local_d8,&local_44);
        local_38 = *pfVar5;
        local_34 = pfVar5[1];
        local_30 = pfVar5[2];
        iVar6 = FUN_0041d384();
        iVar7 = FUN_0041d384();
        iVar8 = FUN_0041d384();
        local_10 = (float)(iVar8 + (iVar6 * -0x100 + iVar7) * -0x100);
        local_1c = local_1c * (float)in_ECX[0xd];
        local_18 = local_18 * (float)in_ECX[0xd];
        local_14 = local_14 * (float)in_ECX[0xd];
        local_38 = local_38 * (float)in_ECX[0xd];
        local_c = (undefined4 *)0x2;
        local_34 = local_34 * (float)in_ECX[0xd];
        local_30 = local_30 * (float)in_ECX[0xd];
        if (2 < (int)local_8[7]) {
          local_54[0] = 0;
          do {
            local_4c = local_c;
            local_54[1] = (int)local_c + -1;
            *DAT_00ac66f0 = (&DAT_00be66f8)[in_ECX[0xc]];
            puVar2 = DAT_00ac66f0;
            (&DAT_00be66f8)[in_ECX[0xc]] = (&DAT_00be66f8)[in_ECX[0xc]] + 1;
            puVar2[1] = (short)in_ECX[0xc];
            DAT_00ac66f0 = DAT_00ac66f0 + 2;
            local_20 = 0;
            do {
              local_48 = local_54[local_20] * 8;
              puVar9 = (undefined4 *)FUN_0040c109(*(undefined4 *)(local_48 + 4 + (int)local_8[4]));
              pfVar5 = local_8;
              puVar4 = DAT_007765d8;
              puVar11 = DAT_007765d8 + 1;
              *DAT_007765d8 = *puVar9;
              *puVar11 = puVar9[1];
              puVar4[2] = puVar9[2];
              pfVar10 = (float *)FUN_00402172(local_c0,in_ECX + 8);
              DAT_007765d8[4] = local_1c * *pfVar10 + local_18 * pfVar10[1] + local_14 * pfVar10[2];
              pfVar10 = (float *)FUN_00402172(local_cc,in_ECX + 8);
              DAT_007765d8[5] = local_38 * *pfVar10 + local_34 * pfVar10[1] + local_30 * pfVar10[2];
              DAT_007765d8[3] = local_10;
              DAT_007765d8 = DAT_007765d8 + 6;
              local_20 = local_20 + 1;
            } while (local_20 < 3);
            local_c = (undefined4 *)((int)local_c + 1);
          } while ((int)local_c < (int)pfVar5[7]);
        }
        local_8 = local_8 + 9;
      } while (local_8 < (float *)in_ECX[5]);
    }
    local_10 = -_DAT_00c06808;
    FUN_00402227(local_54,&local_10);
    for (local_8 = (float *)in_ECX[6]; local_8 < (undefined4 *)in_ECX[7]; local_8 = local_8 + 4) {
      if ((*(char *)((int)local_8[2] + 0x20) == '\0') &&
         (*(char *)((int)local_8[3] + 0x20) == '\x01')) {
        local_c = (undefined4 *)0x0;
LAB_0040c99d:
        puVar11 = (undefined4 *)FUN_0040c109(*local_8);
        uVar12 = (uint)local_c ^ 1;
        uVar1 = local_8[1];
        local_b4[uVar12 * 3] = *puVar11;
        local_b4[uVar12 * 3 + 1] = puVar11[1];
        local_10 = (float)(uVar12 * 0xc);
        local_b4[uVar12 * 3 + 2] = puVar11[2];
        puVar4 = (undefined4 *)FUN_0040c109(uVar1);
        puVar11 = local_c;
        iVar7 = (int)local_c * 0xc;
        iVar6 = (int)local_c * 3;
        local_b4[(int)local_c * 3] = *puVar4;
        piVar13 = local_54;
        puVar14 = local_cc;
        uVar1 = local_8[1];
        local_b4[iVar6 + 1] = puVar4[1];
        local_48 = iVar7;
        local_b4[(int)puVar11 * 3 + 2] = puVar4[2];
        FUN_0040c109(uVar1);
        puVar11 = (undefined4 *)FUN_00402172(puVar14,piVar13);
        fVar3 = local_10;
        iVar6 = (int)local_10 + 4;
        *(undefined4 *)((int)local_9c + (int)local_10) = *puVar11;
        piVar13 = local_54;
        puVar14 = local_c0;
        uVar1 = *local_8;
        *(undefined4 *)((int)local_9c + iVar6) = puVar11[1];
        *(undefined4 *)((int)local_9c + (int)fVar3 + 8) = puVar11[2];
        FUN_0040c109(uVar1);
        puVar11 = (undefined4 *)FUN_00402172(puVar14,piVar13);
        iVar7 = local_48;
        puVar4 = DAT_007765dc;
        iVar6 = local_48 + 4;
        *(undefined4 *)((int)local_9c + local_48) = *puVar11;
        *(undefined4 *)((int)local_9c + iVar6) = puVar11[1];
        *(undefined4 *)((int)local_9c + iVar7 + 8) = puVar11[2];
        puVar11 = DAT_007765dc + 1;
        *DAT_007765dc = local_b4[0];
        *puVar11 = local_b4[1];
        puVar4[2] = local_b4[2];
        puVar11 = DAT_007765dc;
        DAT_007765dc = DAT_007765dc + 3;
        *DAT_007765dc = local_b4[3];
        puVar11[4] = uStack_a4;
        puVar11[5] = uStack_a0;
        puVar11 = DAT_007765dc;
        DAT_007765dc = DAT_007765dc + 3;
        *DAT_007765dc = local_9c[0];
        puVar11[4] = local_9c[1];
        puVar11[5] = local_9c[2];
        puVar11 = DAT_007765dc;
        DAT_007765dc = DAT_007765dc + 3;
        *DAT_007765dc = local_b4[0];
        puVar11[4] = local_b4[1];
        puVar11[5] = local_b4[2];
        puVar11 = DAT_007765dc;
        DAT_007765dc = DAT_007765dc + 3;
        *DAT_007765dc = local_9c[0];
        puVar11[4] = local_9c[1];
        puVar11[5] = local_9c[2];
        puVar11 = DAT_007765dc;
        DAT_007765dc = DAT_007765dc + 3;
        *DAT_007765dc = local_9c[3];
        puVar11[4] = local_9c[4];
        puVar11[5] = local_9c[5];
        DAT_007765dc = DAT_007765dc + 3;
      }
      else if ((*(char *)((int)local_8[3] + 0x20) == '\0') &&
              (*(char *)((int)local_8[2] + 0x20) == '\x01')) {
        local_c = (undefined4 *)0x1;
        goto LAB_0040c99d;
      }
    }
  }
  return;
}



// ==== 0x40cac4 ====

void FUN_0040cac4(void)

{
  short *psVar1;
  float fVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  size_t _Size;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  char cVar14;
  char cVar15;
  undefined4 uVar16;
  int iVar17;
  undefined4 *puStack_c8;
  int *piStack_c4;
  int *piStack_c0;
  int iStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  int *piStack_b0;
  void *pvStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_98;
  int *piStack_94;
  int iStack_90;
  undefined4 uStack_8c;
  int *piStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  int *piStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  int *piStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  int *piStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  
  uStack_5c = 0;
  uStack_60 = 0x1b;
  piStack_64 = DAT_004571ec;
  uStack_68 = 0x40cadd;
  (**(code **)(*DAT_004571ec + 0xe4))();
  uStack_68 = 0;
  uStack_6c = 0x89;
  piStack_70 = DAT_004571ec;
  uStack_74 = 0x40caf1;
  (**(code **)(*DAT_004571ec + 0xe4))();
  uStack_74 = 1;
  uStack_78 = 0x88;
  piStack_7c = DAT_004571ec;
  uStack_80 = 0x40cb08;
  (**(code **)(*DAT_004571ec + 0xe4))();
  uStack_80 = 1;
  uStack_84 = 7;
  piStack_88 = DAT_004571ec;
  uStack_8c = 0x40cb19;
  (**(code **)(*DAT_004571ec + 0xe4))();
  uStack_8c = 1;
  iStack_90 = 0xe;
  piStack_94 = DAT_004571ec;
  uStack_98 = 0x40cb2a;
  (**(code **)(*DAT_004571ec + 0xe4))();
  uStack_98 = 3;
  (**(code **)(*DAT_004571ec + 0xe4))();
  iVar6 = 0;
  do {
    uStack_a8 = 5;
    piStack_b0 = DAT_004571ec;
    uStack_b4 = 0x40cb51;
    pvStack_ac = (void *)iVar6;
    (**(code **)(*DAT_004571ec + 0x114))();
    uStack_b4 = 2;
    uStack_b8 = 6;
    piStack_c0 = DAT_004571ec;
    piStack_c4 = (int *)0x40cb64;
    iStack_bc = iVar6;
    (**(code **)(*DAT_004571ec + 0x114))();
    piStack_c4 = (int *)0x1;
    puStack_c8 = (undefined4 *)0x7;
    (**(code **)(*DAT_004571ec + 0x114))(DAT_004571ec,iVar6);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 6);
  puVar10 = &DAT_00c06954;
  puVar8 = &DAT_004550b0;
  for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar8 = puVar8 + 1;
  }
  DAT_004550a4 = DAT_00c06948;
  DAT_004550a8 = DAT_00c0694c;
  DAT_004550ac = DAT_00c06950;
  uStack_a8 = 0x40cb9e;
  FUN_004039f6();
  uStack_a8 = 0;
  piStack_b0 = (int *)((DAT_00ac66f4 >> 2 & 0x3fU) * 0x80c1 & 0x3f3f3f);
  pvStack_ac = (void *)0x3f800000;
  uStack_b4 = 7;
  uStack_b8 = 0;
  iStack_bc = 0;
  piStack_c0 = DAT_004571ec;
  piStack_c4 = (int *)0x40cbd0;
  (**(code **)(*DAT_004571ec + 0xac))();
  piStack_c4 = DAT_004571ec;
  puStack_c8 = (undefined4 *)0x40cbde;
  (**(code **)(*DAT_004571ec + 0xa4))();
  iVar6 = DAT_00453700;
  uStack_b4 = CONCAT13(1,(undefined3)uStack_b4);
  pvStack_ac = (void *)0x0;
  if (0 < DAT_00453700) {
    piStack_88 = (int *)0x3f800000;
    uStack_80 = 0;
    fVar2 = (float)DAT_00453700;
    uStack_78 = 0;
    uStack_8c = 0x3e99999a;
    uStack_84 = 0x3f000000;
    iStack_90 = (((int)(0x120 / (longlong)(DAT_00453700 + 1)) + 8) / 0x10) * 0x80706;
    do {
      DAT_00a466e4 = uStack_8c;
      DAT_00a466e8 = piStack_88;
      piStack_7c = (int *)(((float)(int)pvStack_ac * 5.2) / fVar2);
      DAT_00a466ec = uStack_84;
      puStack_c8 = &uStack_74;
      uStack_74 = uStack_80;
      uStack_6c = uStack_78;
      piStack_70 = piStack_7c;
      FUN_00402ea2();
      puStack_c8 = (undefined4 *)0x40cc81;
      FUN_004022c1();
      puVar10 = (undefined4 *)&DAT_00be66f8;
      for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      puStack_c8 = (undefined4 *)0x0;
      DAT_00ac66f0 = &DAT_00be6800;
      DAT_007765d8 = &DAT_007765e0;
      DAT_007765dc = &DAT_00ac66f8;
      FUN_00408e2a();
      puStack_c8 = (undefined4 *)0x2000;
      _Size = ((int)(DAT_007765dc + -0xac66f8) / 0x24) * 0x24;
      iVar17 = 0;
      (**(code **)(*DAT_00a466e0 + 0x2c))(DAT_00a466e0,0,_Size,&uStack_98);
      _memcpy(pvStack_ac,&DAT_00ac66f8,_Size);
      piVar11 = DAT_00a466e0;
      (**(code **)(*DAT_00a466e0 + 0x30))();
      pvStack_ac = (void *)0x0;
      iVar4 = 0;
      do {
        *(short *)((int)&DAT_009b65e0 + iVar4) = (short)pvStack_ac;
        psVar1 = DAT_00ac66f0;
        pvStack_ac = (void *)((int)pvStack_ac + (int)*(short *)((int)&DAT_00be66f8 + iVar4));
        iVar4 = iVar4 + 2;
      } while (iVar4 < 0x100);
      piVar7 = (int *)0x0;
      for (psVar3 = &DAT_00be6800; psVar3 < psVar1; psVar3 = psVar3 + 2) {
        (&DAT_007665d8)[(int)(short)(&DAT_009b65e0)[psVar3[1]] + (int)*psVar3] = (short)piVar7;
        piVar7 = (int *)((int)piVar7 + 1);
      }
      piStack_c0 = piVar7;
      (**(code **)(*DAT_00c06800 + 0x2c))(DAT_00c06800,0,(int)piVar7 * 0x48,&puStack_c8,0x2000);
      iVar4 = 0;
      if (0 < (int)piVar7) {
        do {
          psVar1 = &DAT_007665d8 + iVar4;
          piVar7 = (int *)(&DAT_007765e0 + *psVar1 * 0x48);
          piVar9 = piVar11;
          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
            *piVar9 = *piVar7;
            piVar7 = piVar7 + 1;
            piVar9 = piVar9 + 1;
          }
          piVar7 = (int *)(&DAT_007765f8 + *psVar1 * 0x48);
          piVar9 = piVar11 + 6;
          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
            *piVar9 = *piVar7;
            piVar7 = piVar7 + 1;
            piVar9 = piVar9 + 1;
          }
          piVar7 = (int *)(&DAT_00776610 + *psVar1 * 0x48);
          piVar9 = piVar11 + 0xc;
          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
            *piVar9 = *piVar7;
            piVar7 = piVar7 + 1;
            piVar9 = piVar9 + 1;
          }
          piVar11 = piVar11 + 0x12;
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar17);
      }
      (**(code **)(*DAT_00c06800 + 0x30))(DAT_00c06800);
      (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536ec);
      (**(code **)(*DAT_004571ec + 400))(DAT_004571ec,0,DAT_00c06800,0,0x18);
      if (DAT_004536fc != 0) {
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x34,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x39,8);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xb9,0);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x38,8);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x36,3);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x35,3);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x37,3);
      }
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,3);
      uVar16 = 0;
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,0);
      piVar11 = DAT_004571ec;
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,3);
      cVar15 = (char)((uint)piVar11 >> 0x18);
      cVar14 = '\0';
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,1,1);
      iVar4 = *DAT_004571ec;
      if (cVar15 == '\0') {
        (**(code **)(iVar4 + 0xe4))(DAT_004571ec,0x3c,0);
        iVar4 = *DAT_004571ec;
        uVar13 = 0;
        uVar12 = 0xe;
      }
      else {
        uVar13 = 0x203040;
        uVar12 = 0x3c;
      }
      (**(code **)(iVar4 + 0xe4))(DAT_004571ec,uVar12,uVar13);
      if ((DAT_004536fc != 0) || (cVar14 != '\0')) {
        (**(code **)(*DAT_004571ec + 0x144))(DAT_004571ec,4,0,uVar16);
      }
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xe,0);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xa8,0);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x34,1);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xb9,0);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x39,8);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x38,8);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x36,1);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x35,7);
      cVar14 = '\0';
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x37,7);
      if (DAT_004536fc != 0) {
        piVar11 = DAT_004571ec;
        (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536f4);
        (**(code **)(*DAT_004571ec + 400))(DAT_004571ec,0,DAT_00a466e0,0,0xc);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x16,2);
        (**(code **)(*DAT_004571ec + 0x144))(DAT_004571ec,4,0,piVar11);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x16,3);
        uVar16 = 1;
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x36,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x35,8);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x37,8);
        (**(code **)(*DAT_004571ec + 0x144))(DAT_004571ec,4,0,uVar16);
      }
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xa8,0xf);
      if (cVar14 != '\0') {
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x1b,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x13,2);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x14,2);
      }
      (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536ec);
      (**(code **)(*DAT_004571ec + 400))(DAT_004571ec,0,DAT_00c06800,0,0x18);
      if (DAT_004536fc != 0) {
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x34,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x39,8);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xb9,0);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x38,7);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x36,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x35,1);
        (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x37,1);
      }
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,0x18);
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,0);
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,2);
      uVar16 = 1;
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,1,4);
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,2,1);
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,3,3);
      (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,2,1,1);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x3c,uVar16);
      puVar10 = &DAT_00c0f230;
      iVar4 = 0;
      do {
        if (*(short *)((int)&DAT_00be66f8 + iVar4) != 0) {
          FUN_00415c17(0,*puVar10);
          (**(code **)(*DAT_004571ec + 0x144))
                    (DAT_004571ec,4,*(short *)((int)&DAT_009b65e0 + iVar4) * 3,
                     (int)*(short *)((int)&DAT_00be66f8 + iVar4));
        }
        puVar10 = puVar10 + 2;
        iVar4 = iVar4 + 2;
      } while ((int)puVar10 < 0xc0f630);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0xe,1);
      (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x34,0);
      pvStack_ac = (void *)((int)pvStack_ac + 1);
    } while ((int)pvStack_ac < iVar6);
  }
  puStack_c8 = (undefined4 *)0x1;
  (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x1b);
  (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x13,9);
  (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x14,3);
  (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,4);
  (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,3);
  (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,2);
  (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,1,1,1);
  (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x3c,DAT_00ac66f4);
  puVar10 = &DAT_00c0f234;
  iVar6 = 0;
  do {
    if (*(short *)((int)&DAT_00be66f8 + iVar6) != 0) {
      FUN_00415c17(0,*puVar10);
      (**(code **)(*DAT_004571ec + 0x144))
                (DAT_004571ec,4,*(short *)((int)&DAT_009b65e0 + iVar6) * 3,
                 (int)*(short *)((int)&DAT_00be66f8 + iVar6));
    }
    puVar10 = puVar10 + 2;
    iVar6 = iVar6 + 2;
  } while ((int)puVar10 < 0xc0f634);
  if (DAT_00d0f3b8 != '\0') {
    FUN_0040c179();
  }
  (**(code **)(*DAT_004571ec + 0x104))(DAT_004571ec,0,0);
  (**(code **)(*DAT_004571ec + 0x104))(DAT_004571ec,1,0);
  FUN_0040bfb0();
  if ((DAT_00be67f8 - 0xa466f0U & 0xffffffe0) != 0) {
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,1,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,2,3);
    (**(code **)(*DAT_004571ec + 0x10c))(DAT_004571ec,0,3,0);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,7,0);
    (**(code **)(*DAT_004571ec + 0xe4))(DAT_004571ec,0x1b,0);
    (**(code **)(*DAT_004571ec + 0x164))(DAT_004571ec,DAT_004536f0);
    (**(code **)(*DAT_004571ec + 0x14c))
              (DAT_004571ec,2,DAT_00be67f8 + -0xa466f0 >> 5,&DAT_00a466f0,0x10);
  }
  (**(code **)(*DAT_004571ec + 0xa8))(DAT_004571ec);
  (**(code **)(*DAT_004571ec + 0x44))(DAT_004571ec,0,0,0,0);
  return;
}



// ==== 0x40d487 ====

void FUN_0040d487(undefined4 param_1)

{
  FILE *_File;
  undefined4 *in_ECX;
  
  _File = (FILE *)FUN_0041d331(param_1,&DAT_0042c278);
  *in_ECX = 0;
  if (_File != (FILE *)0x0) {
    _fread(&param_1,1,4,_File);
    *in_ECX = param_1;
    _fclose(_File);
  }
  return;
}



// ==== 0x40d4c8 ====

void FUN_0040d4c8(void)

{
  if (DAT_00c06864 != '\0') {
    *DAT_00c0685c = 4;
    DAT_00c0685c = DAT_00c0685c + 1;
  }
  return;
}



// ==== 0x40d4e3 ====

void FUN_0040d4e3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (((DAT_00c0682c == 1) || (DAT_00c0682c == 3)) && (DAT_00c06864 != '\0')) {
    *DAT_00c0685c = 7;
    DAT_00c0685c = DAT_00c0685c + 1;
    *DAT_00c0685c = param_1;
    DAT_00c0685c = DAT_00c0685c + 1;
    *DAT_00c0685c = param_2;
    DAT_00c0685c = DAT_00c0685c + 1;
    *DAT_00c0685c = param_3;
    DAT_00c0685c = DAT_00c0685c + 1;
    *DAT_00c0685c = param_4;
    DAT_00c0685c = DAT_00c0685c + 1;
  }
  return;
}



// ==== 0x40d558 ====

int FUN_0040d558(int param_1)

{
  int *in_ECX;
  int *extraout_ECX;
  int extraout_EDX;
  
  FUN_00404752(CONCAT31((int3)((uint)(in_ECX[1] - *in_ECX) >> 8),
                        (uint)(param_1 << 2) < (uint)(in_ECX[1] - *in_ECX)));
  return *extraout_ECX + extraout_EDX;
}



// ==== 0x40d579 ====

void FUN_0040d579(void)

{
  int iVar1;
  void *pvVar2;
  int *in_ECX;
  uint _NewSize;
  uint uVar3;
  
  uVar3 = in_ECX[1] - *in_ECX >> 2;
  iVar1 = (uVar3 >> 3) + 1 + uVar3;
  _NewSize = iVar1 * 4;
  FUN_00404752(CONCAT31((int3)((uint)iVar1 >> 8),_NewSize < 0x10000000));
  pvVar2 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = (int)pvVar2;
  in_ECX[2] = (int)(_NewSize + (int)pvVar2);
  in_ECX[1] = (int)((int)pvVar2 + uVar3 * 4);
  return;
}



// ==== 0x40d5bf ====

void FUN_0040d5bf(undefined4 param_1)

{
  FILE *_File;
  int iVar1;
  void *_Str;
  int *in_ECX;
  size_t _Count;
  size_t _Size;
  FILE *_File_00;
  
  if (*in_ECX != 0) {
    _File = (FILE *)FUN_0041d331(param_1,&DAT_0042c798);
    _ftell(_File);
    _File_00 = _File;
    iVar1 = FUN_0040d558(0);
    _Count = (in_ECX[4] - iVar1 >> 2) << 2;
    _Size = 1;
    _Str = (void *)FUN_0040d558(0);
    _fwrite(_Str,_Size,_Count,_File_00);
    _fclose(_File);
  }
  return;
}



// ==== 0x40d623 ====

void FUN_0040d623(void)

{
  FUN_0040d5bf("out.dat");
  DAT_00c0685c = DAT_00c06860;
  DAT_00c06864 = 0;
  return;
}



// ==== 0x40d644 ====

void FUN_0040d644(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *in_ECX;
  
  iVar2 = *in_ECX;
  puVar3 = (undefined4 *)in_ECX[1];
  uVar1 = iVar2 + param_1 * 4;
  in_ECX[1] = uVar1;
  if ((uint)in_ECX[2] < uVar1) {
    FUN_0040d579();
    puVar3 = (undefined4 *)(*in_ECX + ((int)puVar3 - iVar2 >> 2) * 4);
  }
  for (; puVar3 < (undefined4 *)in_ECX[1]; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  return;
}



// ==== 0x40d681 ====

void FUN_0040d681(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int in_ECX;
  
  iVar1 = FUN_0040d558(0);
  iVar1 = *(int *)(in_ECX + 0x10) - iVar1 >> 2;
  uVar2 = param_1 + iVar1;
  if ((uint)(*(int *)(in_ECX + 8) - *(int *)(in_ECX + 4) >> 2) < uVar2) {
    FUN_0040d644(uVar2);
    iVar3 = FUN_0040d558(0);
    *(undefined4 *)(in_ECX + 0x14) = 0;
    *(int *)(in_ECX + 0x10) = iVar3 + iVar1 * 4;
  }
  return;
}



// ==== 0x40d6cd ====

void FUN_0040d6cd(undefined4 param_1)

{
  FILE *_File;
  uint _Count;
  void *_DstBuf;
  int iVar1;
  int in_ECX;
  uint uVar2;
  size_t _ElementSize;
  FILE *_File_00;
  
  _File = (FILE *)FUN_0041d331(param_1,&DAT_0042c278);
  _fseek(_File,0,2);
  _Count = _ftell(_File);
  _fseek(_File,0,0);
  uVar2 = _Count >> 2;
  FUN_0040d644(uVar2);
  _ElementSize = 1;
  _File_00 = _File;
  _DstBuf = (void *)FUN_0040d558(0);
  _fread(_DstBuf,_ElementSize,_Count,_File_00);
  _fclose(_File);
  iVar1 = FUN_0040d558(0);
  *(int *)(in_ECX + 0x10) = iVar1;
  *(uint *)(in_ECX + 0x14) = iVar1 + uVar2 * 4;
  return;
}



// ==== 0x40d74b ====

void FUN_0040d74b(void)

{
  undefined4 uVar1;
  undefined4 *in_ECX;
  
  in_ECX[2] = in_ECX[1];
  FUN_0040d644(0x40000);
  uVar1 = FUN_0040d558(0);
  in_ECX[5] = 0;
  in_ECX[4] = uVar1;
  FUN_0040d681(0x10000);
  *in_ECX = 0;
  return;
}



// ==== 0x40d785 ====

void FUN_0040d785(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 4) = 0;
  *(undefined4 *)(in_ECX + 8) = 0;
  *(undefined4 *)(in_ECX + 0xc) = 0;
  FUN_0040d74b();
  return;
}



// ==== 0x40d79c ====

void FUN_0040d79c(void)

{
  FUN_0040d74b();
  DAT_00c06864 = 1;
  FUN_0040d487("out.dat");
  *DAT_00c0685c = 4;
  DAT_00c0685c = DAT_00c0685c + 1;
  return;
}



// ==== 0x40d7cf ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_0040d7cf(void)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  void *pvVar5;
  undefined4 *puVar6;
  int *piVar7;
  float *pfVar8;
  undefined1 *puVar9;
  float *pfVar10;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar11;
  uint uVar12;
  float fVar13;
  float10 fVar14;
  char *pcVar15;
  undefined1 local_498 [12];
  undefined1 local_48c [12];
  undefined1 local_480 [12];
  undefined1 local_474 [12];
  undefined4 local_468;
  undefined4 uStack_464;
  undefined4 uStack_460;
  int local_45c;
  int iStack_458;
  int iStack_454;
  float local_450;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined4 local_444;
  undefined4 local_440;
  undefined4 local_43c;
  float local_438;
  undefined4 local_434;
  float local_430;
  float local_42c;
  float local_428;
  float local_424;
  int *local_420;
  undefined4 *local_41c;
  float *local_418;
  int local_414;
  float local_410;
  void *local_40c;
  float local_408 [256];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  if (DAT_00d0f4fd != '\0') {
    DAT_00d0f4fd = '\0';
    if (DAT_00c06864 == '\0') {
      FUN_0040d79c();
    }
    else {
      FUN_0040d623();
    }
  }
  if ((DAT_00d0f4fc != '\0') && (DAT_00c0682c == 1)) {
    DAT_00d0f4fc = '\0';
    if (DAT_00d0f9f8 == 0) {
      FUN_00410a7e();
    }
    else {
      DAT_00d0f534 = 1;
      FUN_00407ca6();
    }
    FUN_0040d74b();
    DAT_00c0684c = 0;
    DAT_00c06864 = '\0';
  }
  if (DAT_00d0f4fe != '\0') {
    DAT_00d0f4fe = '\0';
    if (DAT_00c06864 != '\0') {
      FUN_0040d623();
    }
    DAT_00d0f534 = 1;
    FUN_00407ca6();
    FUN_0040d79c();
  }
  if (((DAT_00c0682c == 1) || (DAT_00c0682c == 3)) && (DAT_00c06864 != '\0')) {
    FUN_0040d681(0x10000);
    local_40c = (void *)0x0;
    if (&DAT_00746c30 < DAT_00561408) {
      piVar7 = &DAT_00746c34;
      do {
        piVar1 = piVar7 + 0x3a;
        if ((char)piVar7[0x15] == '\0') {
          if ((char)*piVar1 == '\0') {
            *(char *)piVar1 = '\x01';
            *DAT_00c0685c = 4.2039e-45;
            DAT_00c0685c = DAT_00c0685c + 1;
            *DAT_00c0685c = (float)local_40c;
            DAT_00c0685c = DAT_00c0685c + 1;
            fVar3 = (float)(*piVar7 - piVar7[-1] >> 4);
            *DAT_00c0685c = fVar3;
            DAT_00c0685c = DAT_00c0685c + 1;
            if (0 < (int)fVar3) {
              local_414 = 0;
              local_410 = fVar3;
              do {
                pfVar10 = (float *)(piVar7[-1] + local_414);
                iVar11 = 3;
                do {
                  *DAT_00c0685c = *pfVar10;
                  DAT_00c0685c = DAT_00c0685c + 1;
                  pfVar10 = pfVar10 + 1;
                  iVar11 = iVar11 + -1;
                } while (iVar11 != 0);
                local_414 = local_414 + 0x10;
                local_410 = (float)((int)local_410 + -1);
              } while (local_410 != 0.0);
            }
            *DAT_00c0685c = (float)(piVar7[2] - piVar7[1] >> 3);
            fVar3 = (float)((piVar7[4] - piVar7[3]) / 0x24);
            DAT_00c0685c = DAT_00c0685c + 1;
            *DAT_00c0685c = fVar3;
            DAT_00c0685c = DAT_00c0685c + 1;
            if (0 < (int)fVar3) {
              iVar11 = 0;
              local_410 = fVar3;
              do {
                *DAT_00c0685c = *(float *)(iVar11 + 0x1c + piVar7[3]);
                DAT_00c0685c = DAT_00c0685c + 1;
                iVar4 = 0;
                if (0 < *(int *)(iVar11 + 0x1c + piVar7[3])) {
                  do {
                    *DAT_00c0685c = *(float *)(*(int *)(iVar11 + 0x10 + piVar7[3]) + 4 + iVar4 * 8);
                    DAT_00c0685c = DAT_00c0685c + 1;
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < *(int *)(iVar11 + 0x1c + piVar7[3]));
                }
                iVar11 = iVar11 + 0x24;
                local_410 = (float)((int)local_410 + -1);
              } while (local_410 != 0.0);
            }
            *DAT_00c0685c = (float)piVar7[0xb];
            DAT_00c0685c = DAT_00c0685c + 1;
            *DAT_00c0685c = (float)piVar7[0xc];
            DAT_00c0685c = DAT_00c0685c + 1;
            pfVar10 = (float *)(piVar7 + 7);
            iVar11 = 3;
            do {
              *DAT_00c0685c = *pfVar10;
              DAT_00c0685c = DAT_00c0685c + 1;
              pfVar10 = pfVar10 + 1;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
            *DAT_00c0685c = (float)piVar7[0x14];
            DAT_00c0685c = DAT_00c0685c + 1;
          }
          FUN_004021a7(&local_450,piVar7 + 0x20);
          fVar14 = (float10)FUN_004022a2();
          pfVar10 = DAT_00c0685c;
          if ((float10)1.0000001e-06 < fVar14) {
            pfVar8 = (float *)(piVar7 + 0x20);
            piVar7[0x3b] = (int)*pfVar8;
            piVar7[0x3c] = piVar7[0x21];
            piVar7[0x3d] = piVar7[0x22];
            *pfVar10 = 2.8026e-45;
            DAT_00c0685c = DAT_00c0685c + 1;
            *DAT_00c0685c = (float)local_40c;
            DAT_00c0685c = DAT_00c0685c + 1;
            iVar11 = 3;
            do {
              *DAT_00c0685c = *pfVar8;
              DAT_00c0685c = DAT_00c0685c + 1;
              pfVar8 = pfVar8 + 1;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
            pfVar10 = (float *)(piVar7 + 0x17);
            iVar11 = 9;
            do {
              *DAT_00c0685c = *pfVar10;
              DAT_00c0685c = DAT_00c0685c + 1;
              pfVar10 = pfVar10 + 1;
              iVar11 = iVar11 + -1;
            } while (iVar11 != 0);
          }
        }
        else if ((char)*piVar1 == '\x01') {
          *(char *)piVar1 = '\0';
          *DAT_00c0685c = 7.00649e-45;
          DAT_00c0685c = DAT_00c0685c + 1;
          *DAT_00c0685c = (float)local_40c;
          DAT_00c0685c = DAT_00c0685c + 1;
        }
        local_40c = (void *)((int)local_40c + 1);
        piVar1 = piVar7 + 0x3e;
        piVar7 = piVar7 + 0x3f;
      } while (piVar1 < DAT_00561408);
    }
    *DAT_00c0685c = 1.4013e-45;
    DAT_00c0685c = DAT_00c0685c + 1;
    *DAT_00c0685c = 8.40779e-45;
    DAT_00c0685c = DAT_00c0685c + 1;
    pfVar10 = (float *)&DAT_00c06948;
    iVar11 = 3;
    do {
      *DAT_00c0685c = *pfVar10;
      DAT_00c0685c = DAT_00c0685c + 1;
      pfVar10 = pfVar10 + 1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    pfVar10 = (float *)&DAT_00c06954;
    iVar11 = 9;
    do {
      *DAT_00c0685c = *pfVar10;
      DAT_00c0685c = DAT_00c0685c + 1;
      pfVar10 = pfVar10 + 1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    DAT_00c0684c = DAT_00c0684c + 1;
  }
  if (((DAT_00c0682c == 2) || (DAT_00c0682c == 3)) &&
     (((DAT_00c06978 + 1) % 2 == 0 || (DAT_00d0f41d == '\0')))) {
    local_414 = 1;
    pfVar10 = DAT_00c06840;
    if (DAT_00d0f41e != '\0') {
      local_414 = 2;
    }
    do {
      if (DAT_00c06844 <= pfVar10) {
        pcVar15 = DAT_00d0f3d8;
        if (*DAT_00d0f3d8 == '\0') {
          pcVar15 = "in.dat";
        }
        FUN_0040d6cd(pcVar15);
        pfVar10 = DAT_00c06840;
      }
      local_424 = 0.0;
      local_428 = 0.0;
      local_42c = 0.0;
      local_410 = 0.0;
LAB_0040dbf6:
      do {
        local_420 = (int *)0x1;
        if (pfVar10 < DAT_00c06844) {
          local_420 = (int *)*pfVar10;
          DAT_00c06840 = pfVar10 + 1;
          if (((int)local_420 < 0) || (pfVar10 = DAT_00c06840, 7 < (int)local_420)) {
            DAT_00c06840 = DAT_00c06844;
            pfVar10 = DAT_00c06844;
          }
        }
        else {
          DAT_00d0f9fc = 1;
        }
        if (local_420 == (int *)0x2) {
          fVar3 = *pfVar10;
          pfVar10 = pfVar10 + 1;
          local_41c = &DAT_00746c30 + (int)fVar3 * 0x3f;
          local_418 = (float *)(&DAT_00746cb4 + (int)fVar3 * 0x3f);
          local_450 = *local_418;
          uStack_44c = (&DAT_00746cb8)[(int)fVar3 * 0x3f];
          uStack_448 = (&DAT_00746cbc)[(int)fVar3 * 0x3f];
          iVar11 = 3;
          pfVar8 = local_418;
          do {
            *pfVar8 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            pfVar8 = pfVar8 + 1;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          pfVar8 = (float *)(&DAT_00746c90 + (int)fVar3 * 0x3f);
          iVar11 = 9;
          do {
            *pfVar8 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            pfVar8 = pfVar8 + 1;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          DAT_00c06840 = pfVar10;
          puVar6 = (undefined4 *)FUN_004021a7(local_474,&local_450);
          local_41c[0x27] = *puVar6;
          local_41c[0x28] = puVar6[1];
          local_41c[0x29] = puVar6[2];
          local_42c = local_42c + *local_418;
          local_428 = local_428 + local_418[1];
          local_424 = local_424 + local_418[2];
          local_410 = local_410 + 1.0;
        }
        else {
          if (local_420 == (int *)0x3) {
            fVar3 = *pfVar10;
            piVar7 = &DAT_00746c30 + (int)fVar3 * 0x3f;
            DAT_00c06840 = pfVar10 + 1;
            for (; DAT_00561408 <= piVar7; DAT_00561408 = DAT_00561408 + 0x3f) {
              *(undefined1 *)(DAT_00561408 + 0x16) = 1;
            }
            (&DAT_00746c88)[(int)fVar3 * 0xfc] = 0;
            fVar13 = *DAT_00c06840;
            DAT_00c06840 = DAT_00c06840 + 1;
            if ((100 < (int)fVar13) || ((int)fVar13 < 0)) {
              puVar9 = (undefined1 *)0x0;
              do {
                puVar9 = puVar9 + 1;
                *puVar9 = 0x7f;
              } while( true );
            }
            local_420 = piVar7;
            local_41c = (undefined4 *)fVar3;
            pvVar5 = operator_new((int)fVar13 * 0x10);
            *piVar7 = (int)pvVar5;
            FUN_00404752(pvVar5 != (void *)0x0);
            (&DAT_00746c34)[(int)fVar3 * 0x3f] = *piVar7 + (int)fVar13 * 0x10;
            if (0 < (int)fVar13) {
              iVar11 = 0;
              do {
                pfVar10 = (float *)(*piVar7 + iVar11);
                iVar4 = 3;
                do {
                  *pfVar10 = *DAT_00c06840;
                  DAT_00c06840 = DAT_00c06840 + 1;
                  pfVar10 = pfVar10 + 1;
                  iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
                *(undefined1 *)(*piVar7 + 0xc + iVar11) = 0;
                *(undefined1 *)(*piVar7 + 0xd + iVar11) = 0;
                *(undefined2 *)(*piVar7 + 0xe + iVar11) = 0;
                iVar11 = iVar11 + 0x10;
                fVar13 = (float)((int)fVar13 + -1);
              } while (fVar13 != 0.0);
            }
            local_418 = (float *)*DAT_00c06840;
            pfVar10 = (float *)DAT_00c06840[1];
            DAT_00c06840 = DAT_00c06840 + 2;
            if ((100 < (int)local_418) || ((int)local_418 < 0)) {
              puVar9 = (undefined1 *)0x0;
              do {
                puVar9 = puVar9 + 1;
                *puVar9 = 0x7f;
              } while( true );
            }
            if ((100 < (int)pfVar10) || ((int)pfVar10 < 0)) {
              puVar9 = (undefined1 *)0x0;
              do {
                puVar9 = puVar9 + 1;
                *puVar9 = 0x7f;
              } while( true );
            }
            pvVar5 = operator_new((int)pfVar10 * 0x24);
            (&DAT_00746c40)[(int)fVar3 * 0x3f] = pvVar5;
            uVar12 = (int)local_418 * 8;
            (&DAT_00746c44)[(int)fVar3 * 0x3f] = (void *)((int)pvVar5 + (int)pfVar10 * 0x24);
            local_40c = operator_new(uVar12);
            (&DAT_00746c38)[(int)fVar3 * 0x3f] = local_40c;
            (&DAT_00746c3c)[(int)fVar3 * 0x3f] = (void *)((int)local_40c + uVar12);
            if (0 < (int)pfVar10) {
              iVar11 = 0;
              local_418 = pfVar10;
              do {
                *(float *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x1c + iVar11) = *DAT_00c06840;
                DAT_00c06840 = DAT_00c06840 + 1;
                *(void **)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x10 + iVar11) = local_40c;
                puVar6 = (undefined4 *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + iVar11);
                puVar6[2] = 0;
                iVar4 = 0;
                puVar6[1] = 0;
                *puVar6 = 0;
                if (0 < *(int *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x1c + iVar11)) {
                  do {
                    *(float *)((int)local_40c + 4) = *DAT_00c06840;
                    DAT_00c06840 = DAT_00c06840 + 1;
                    iVar2 = *(int *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x10 + iVar11);
                    FUN_00404752(CONCAT31((int3)((uint)iVar2 >> 8),
                                          -1 < *(int *)(iVar2 + 4 + iVar4 * 8)));
                    iVar4 = *(int *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x10 + iVar11);
                    FUN_00404752(CONCAT31((int3)((uint)iVar4 >> 8),
                                          *(int *)(iVar4 + 4 + extraout_ECX * 8) <
                                          (&DAT_00746c34)[(int)fVar3 * 0x3f] - *piVar7 >> 4));
                    local_40c = (void *)((int)local_40c + 8);
                    piVar1 = (int *)(*(int *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x10 + iVar11) +
                                    extraout_ECX_00 * 8);
                    *piVar1 = piVar1[1] * 0x10 + *piVar7;
                    iVar4 = extraout_ECX_00 + 1;
                  } while (iVar4 < *(int *)((&DAT_00746c40)[(int)fVar3 * 0x3f] + 0x1c + iVar11));
                }
                FUN_00408812((&DAT_00746c40)[(int)fVar3 * 0x3f] + iVar11);
                iVar11 = iVar11 + 0x24;
                local_418 = (float *)((int)local_418 + -1);
              } while (local_418 != (float *)0x0);
            }
            (&DAT_00746c60)[(int)fVar3 * 0x3f] = *DAT_00c06840;
            (&DAT_00746c64)[(int)fVar3 * 0x3f] = DAT_00c06840[1];
            DAT_00c06840 = DAT_00c06840 + 2;
            FUN_00408b34();
            pfVar8 = (float *)(&DAT_00746c50 + (int)fVar3 * 0x3f);
            iVar11 = 3;
            do {
              pfVar10 = DAT_00c06840;
              *pfVar8 = *pfVar10;
              pfVar8 = pfVar8 + 1;
              iVar11 = iVar11 + -1;
              DAT_00c06840 = pfVar10 + 1;
            } while (iVar11 != 0);
            local_420[0x15] = (int)pfVar10[1];
            iVar11 = (int)local_41c + 0xc;
            local_41c = (undefined4 *)((int)local_41c * 2 + 0xc);
            pfVar10 = pfVar10 + 2;
            DAT_00c06840 = pfVar10;
            piVar7 = (int *)FUN_00402279(local_498,(float)(int)local_41c,(float)iVar11,(float)iVar11
                                        );
            local_45c = *piVar7;
            iStack_458 = piVar7[1];
            iStack_454 = piVar7[2];
            local_420[0x21] = local_45c;
            local_420[0x22] = iStack_458;
            local_420[0x23] = iStack_454;
            FUN_00402429();
            *(undefined1 *)(local_420 + 0x34) = 1;
            goto LAB_0040dbf6;
          }
          if (local_420 == (int *)0x4) {
            FUN_00416810();
            FUN_00410527(0);
            DAT_00c06978 = 0;
            FUN_0040d4c8();
            local_444 = 0x42200000;
            local_440 = 0x420c0000;
            local_43c = 0xc1200000;
            local_468 = 0x42200000;
            uStack_464 = 0x420c0000;
            uStack_460 = 0xc1200000;
            FUN_004027fd(&local_468,0,0);
            pfVar10 = DAT_00c06840;
            goto LAB_0040dbf6;
          }
          if (local_420 == (int *)0x5) {
            DAT_00c06840 = pfVar10 + 1;
            (&DAT_00746c88)[(int)*pfVar10 * 0xfc] = 1;
            pfVar10 = pfVar10 + 1;
            goto LAB_0040dbf6;
          }
          if (local_420 == (int *)0x6) {
            iVar11 = 3;
            if (DAT_00c0682c == 3) {
              pfVar8 = local_408;
              iVar11 = 0xc;
              do {
                *pfVar8 = *pfVar10;
                pfVar10 = pfVar10 + 1;
                pfVar8 = pfVar8 + 1;
                iVar11 = iVar11 + -1;
                DAT_00c06840 = pfVar10;
              } while (iVar11 != 0);
            }
            else {
              pfVar8 = (float *)&DAT_00c06948;
              do {
                *pfVar8 = *pfVar10;
                pfVar10 = pfVar10 + 1;
                pfVar8 = pfVar8 + 1;
                iVar11 = iVar11 + -1;
              } while (iVar11 != 0);
              pfVar8 = (float *)&DAT_00c06954;
              iVar11 = 9;
              do {
                *pfVar8 = *pfVar10;
                pfVar10 = pfVar10 + 1;
                pfVar8 = pfVar8 + 1;
                iVar11 = iVar11 + -1;
                DAT_00c06840 = pfVar10;
              } while (iVar11 != 0);
            }
            goto LAB_0040dbf6;
          }
          if (local_420 == (int *)0x7) {
            local_430 = pfVar10[1];
            local_438 = pfVar10[2];
            DAT_00c06840 = pfVar10 + 4;
            FUN_0041538b(*pfVar10,local_430,local_438,pfVar10[3]);
            pfVar10 = DAT_00c06840;
            goto LAB_0040dbf6;
          }
        }
      } while (local_420 != (int *)0x1);
      puVar6 = &local_434;
      fVar3 = 1.0 / local_410;
      puVar9 = local_48c;
      local_434 = 0x3ca3d70a;
      local_42c = local_42c * fVar3;
      local_428 = local_428 * fVar3;
      local_424 = local_424 * fVar3;
      FUN_004021a7(local_480,&DAT_00c06820);
      pfVar8 = (float *)FUN_00402227(puVar9,puVar6);
      DAT_00c06820 = DAT_00c06820 + *pfVar8;
      local_414 = local_414 + -1;
      DAT_00c06824 = DAT_00c06824 + pfVar8[1];
      DAT_00c06828 = DAT_00c06828 + pfVar8[2];
    } while (0 < local_414);
  }
  DAT_00c0681c = DAT_00c0684c;
  return;
}



// ==== 0x40e188 ====

void FUN_0040e188(void)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  FUN_0040b685(DVar1 & 0x3fff,((int)DVar1 >> 8) + 1000U & 0x3fff);
  return;
}



// ==== 0x40e1af ====

void FUN_0040e1af(void)

{
  FUN_0040e188();
  FUN_00402784();
  FUN_004158ca();
  FUN_0040b83f();
  FUN_00408e01();
  FUN_00407db4();
  FUN_00406eba();
  return;
}



// ==== 0x40e1d2 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_0040e1d2(uint param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  int local_4d8 [5];
  float local_4c4;
  char local_4c0 [1024];
  char local_c0 [152];
  char local_28 [32];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  FUN_00416900();
  iVar3 = 0;
  DAT_00c06978 = DAT_00c06978 + 1;
  local_4d8[4] = 0;
  DAT_00be67f8 = &DAT_00a466f0;
  if (-1 < DAT_00c0682c) {
    if (DAT_00c0682c < 3) {
      FUN_00402f1b();
    }
    else if (DAT_00c0682c == 3) {
      FUN_00402846(4);
    }
  }
  FUN_0040b97a();
  if (DAT_00d0fa10 == 0) {
    FUN_0040b5f7();
  }
  if (DAT_00c06b50 == 10) {
    FUN_0040795f(param_1);
  }
  else {
    if (DAT_00c06b50 == 0xb) {
      FUN_00407818();
    }
    FUN_00407ca6();
    if (DAT_00d0fa08 != 0) {
      DAT_00d0fa08 = 0;
      FUN_00407d7a(3);
      FUN_00406eba();
    }
  }
  if ((char)param_1 == '\0') {
    return;
  }
  if (DAT_00d0f4ff != '\0') {
    DAT_00d0f4ff = '\0';
    local_4d8[4] = 1;
    DAT_00453700 = 0xc;
    DAT_004536fc = 1;
  }
  if (DAT_00c0682c == 0) {
    builtin_strncpy(local_c0,"Blue guy",9);
    local_c0[9] = '\0';
    local_c0[10] = '\0';
    local_c0[0xb] = '\0';
    local_c0[0xc] = '\0';
    local_c0[0xd] = '\0';
    local_c0[0xe] = '\0';
    local_c0[0xf] = '\0';
    local_c0[0x10] = '\0';
    local_c0[0x11] = '\0';
    local_c0[0x12] = '\0';
    local_c0[0x13] = '\0';
    local_c0[0x14] = '\0';
    local_c0[0x15] = '\0';
    local_c0[0x16] = '\0';
    local_c0[0x17] = '\0';
    local_c0[0x18] = '\0';
    local_c0[0x19] = 'G';
    local_c0[0x1a] = 'r';
    local_c0[0x1b] = 'e';
    local_c0[0x1c] = 'y';
    local_c0[0x1d] = ' ';
    local_c0[0x1e] = 'g';
    local_c0[0x1f] = 'u';
    local_c0[0x20] = 'y';
    local_c0[0x21] = '\0';
    local_c0[0x22] = '\0';
    local_c0[0x23] = '\0';
    local_c0[0x24] = '\0';
    local_c0[0x25] = '\0';
    local_c0[0x26] = '\0';
    local_c0[0x27] = '\0';
    local_c0[0x28] = '\0';
    local_c0[0x29] = '\0';
    local_c0[0x2a] = '\0';
    local_c0[0x2b] = '\0';
    local_c0[0x2c] = '\0';
    local_c0[0x2d] = '\0';
    local_c0[0x2e] = '\0';
    local_c0[0x2f] = '\0';
    local_c0[0x30] = '\0';
    local_c0[0x31] = '\0';
    local_c0[0x32] = 'B';
    local_c0[0x33] = 'r';
    local_c0[0x34] = 'o';
    local_c0[0x35] = 'w';
    local_c0[0x36] = 'n';
    local_c0[0x37] = ' ';
    local_c0[0x38] = 'g';
    local_c0[0x39] = 'u';
    local_c0[0x3a] = 'y';
    local_c0[0x3b] = '\0';
    local_c0[0x3c] = '\0';
    local_c0[0x3d] = '\0';
    local_c0[0x3e] = '\0';
    local_c0[0x3f] = '\0';
    local_c0[0x40] = '\0';
    local_c0[0x41] = '\0';
    local_c0[0x42] = '\0';
    local_c0[0x43] = '\0';
    local_c0[0x44] = '\0';
    local_c0[0x45] = '\0';
    local_c0[0x46] = '\0';
    local_c0[0x47] = '\0';
    local_c0[0x48] = '\0';
    local_c0[0x49] = '\0';
    local_c0[0x4a] = 0;
    local_c0[0x4b] = 'G';
    local_c0[0x4c] = 'r';
    local_c0[0x4d] = 'e';
    local_c0[0x4e] = 'e';
    local_c0[0x4f] = 'n';
    local_c0[0x50] = ' ';
    local_c0[0x51] = 'g';
    local_c0[0x52] = 'u';
    local_c0[0x53] = 'y';
    local_c0[0x54] = '\0';
    local_c0[0x55] = '\0';
    local_c0[0x56] = '\0';
    local_c0[0x57] = '\0';
    local_c0[0x58] = '\0';
    local_c0[0x59] = '\0';
    local_c0[0x5a] = '\0';
    local_c0[0x5b] = '\0';
    local_c0[0x5c] = '\0';
    local_c0[0x5d] = '\0';
    local_c0[0x5e] = '\0';
    local_c0[0x5f] = '\0';
    local_c0[0x60] = '\0';
    local_c0[0x61] = '\0';
    local_c0[0x62] = '\0';
    local_c0[99] = 0;
    local_c0[100] = 'B';
    local_c0[0x65] = 'l';
    local_c0[0x66] = 'u';
    local_c0[0x67] = 'e';
    local_c0[0x68] = ' ';
    local_c0[0x69] = 'g';
    local_c0[0x6a] = 'u';
    local_c0[0x6b] = 'y';
    local_c0[0x6c] = ' ';
    local_c0[0x6d] = '(';
    local_c0[0x6e] = 'p';
    local_c0[0x6f] = 'l';
    local_c0[0x70] = 'a';
    local_c0[0x71] = 'y';
    local_c0[0x72] = 'e';
    local_c0[0x73] = 'r';
    local_c0[0x74] = ')';
    local_c0[0x75] = '\0';
    local_c0[0x76] = '\0';
    local_c0[0x77] = '\0';
    local_c0[0x78] = '\0';
    local_c0[0x79] = '\0';
    local_c0[0x7a] = '\0';
    local_c0[0x7b] = '\0';
    local_c0[0x7c] = 0;
    local_c0[0x7d] = 'G';
    local_c0[0x7e] = 'r';
    local_c0[0x7f] = 'e';
    local_c0[0x80] = 'y';
    local_c0[0x81] = ' ';
    local_c0[0x82] = 'g';
    local_c0[0x83] = 'u';
    local_c0[0x84] = 'y';
    local_c0[0x85] = ' ';
    local_c0[0x86] = '(';
    local_c0[0x87] = 'p';
    local_c0[0x88] = 'l';
    local_c0[0x89] = 'a';
    local_c0[0x8a] = 'y';
    local_c0[0x8b] = 'e';
    local_c0[0x8c] = 'r';
    local_c0[0x8d] = '2';
    local_c0[0x8e] = ')';
    local_c0[0x8f] = '\0';
    local_c0[0x90] = '\0';
    local_c0[0x91] = '\0';
    local_c0[0x92] = '\0';
    local_c0[0x93] = '\0';
    local_4d8[0] = -0x1f7f7f01;
    local_4d8[1] = 0xc0ffffff;
    local_4d8[2] = 0xe0c08000;
    local_4d8[3] = 0xc020e020;
    local_c0[0x94] = '\0';
    local_c0[0x95] = '\0';
    local_4c4 = 0.5;
    if ((DAT_00c06b50 != 0xb) && (0 < (int)(PTR_DAT_00453858 + -0xc06b60) / 0x730)) {
      do {
        iVar1 = (&DAT_00c06b40)[iVar3];
        if (iVar1 != -1) {
          param_1 = (uint)CONCAT12((char)iVar3 + '1',(short)param_1);
          FUN_0040b985(0xbe4ccccd,local_4c4,(int)&param_1 + 2,local_4d8[iVar1]);
          iVar1 = (&DAT_00c06b40)[iVar3];
          if ((&DAT_00c0725c)[iVar1 * 0x1cc] == 1) {
            pcVar4 = local_c0 + iVar1 * 0x19 + 100;
          }
          else {
            pcVar4 = local_c0 + iVar1 * 0x19;
          }
          FUN_0040b985(0xbe19999a,local_4c4,pcVar4,local_4d8[iVar1]);
          local_4c4 = local_4c4 - 0.05;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)(PTR_DAT_00453858 + -0xc06b60) / 0x730);
    }
    if (DAT_00c06b50 == 2) {
      bVar2 = false;
      if (((4 < DAT_00c06b28) || (4 < DAT_00c06b2c)) &&
         ((DAT_00c06b2c + 2 <= DAT_00c06b28 || (DAT_00c06b28 <= DAT_00c06b2c + -2)))) {
        bVar2 = true;
        builtin_strncpy(local_28," Game \n  -> ",0xc);
        local_28[0xc] = ' ';
        local_28[0xd] = '\0';
        local_28[0xe] = '\0';
        local_28[0xf] = '\0';
        local_28[0x10] = ' ';
        local_28[0x11] = 'G';
        local_28[0x12] = 'a';
        local_28[0x13] = 'm';
        local_28[0x14] = 'e';
        local_28[0x15] = ' ';
        local_28[0x16] = '\n';
        local_28[0x17] = ' ';
        local_28[0x18] = ' ';
        local_28[0x19] = '<';
        local_28[0x1a] = '-';
        local_28[0x1b] = ' ';
        local_28[0x1c] = ' ';
        local_28[0x1d] = '\0';
        local_28[0x1e] = '\0';
        local_28[0x1f] = '\0';
        FUN_0040b985(0xbdcccccd,0x3ed70a3d,local_28 + (uint)(DAT_00c06b28 < DAT_00c06b2c) * 0x10,
                     local_4d8[DAT_00c06b28 < DAT_00c06b2c]);
        FUN_0040b985(0xbdcccccd,0x3dcccccd,"           \n Game Over \n           ",0xc0ffff00);
      }
      FUN_0040b985(0xbf4ccccd,0x3f0ccccd,"Space to restart game",0xc0c0c0c0);
      if (DAT_00d0f531 != '\0') {
        if (bVar2) {
          FUN_00406eba();
        }
        else {
          FUN_00410a7e();
        }
      }
    }
    if ((DAT_00c06b50 != 0) ||
       ((FUN_0040b985(0x3e4ccccd,0x3f19999a,
                      "Controls:\n DOWN      - start match\n UP        - walk forward\n BACKSPACE - Push\n ENTER     - Push 1 hand"
                      ,0xb0ffffff), DAT_00c06b38 == 0 && (DAT_004eac80 < 2)))) goto LAB_0040e60e;
    uVar5 = 0xb0ffffff;
    pcVar4 = 
    "Controls:\n S         - start match\n W         - walk forward\n SHIFT     - Push\n CTRL      - Push 1 hand"
    ;
  }
  else {
    if (DAT_00d0f531 != '\0') {
      FUN_00410a7e();
    }
    if ((((DAT_00c0682c != 1) && (DAT_00c0682c != 3)) && (DAT_00c0682c != 0x14)) ||
       (DAT_00c0681c == 0)) goto LAB_0040e60e;
    _sprintf(local_4c0,"%2d.%2d",DAT_00c0681c / 100,DAT_00c0681c % 100);
    uVar5 = 0xc0c0c0c0;
    pcVar4 = local_4c0;
  }
  FUN_0040b985(0xbf4ccccd,0x3f19999a,pcVar4,uVar5);
LAB_0040e60e:
  DAT_00d0f531 = 0;
  if (DAT_00c06984 == 2) {
    FUN_0040b985(0xbee66666,0x3e4ccccd,s_demo_time_out_please_purchase_a_l_00453780,0xc0ffffff);
    DAT_00ac66f4 = &DAT_00505050;
    DAT_00d0fa10 = 1;
  }
  FUN_0040cac4();
  FUN_00416900();
  if (local_4d8[4] != 0) {
    FUN_004151c2("sumotori",0);
  }
  return;
}



// ==== 0x40e687 ====

void FUN_0040e687(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int in_ECX;
  
  uVar1 = *(undefined4 *)(in_ECX + 0x10);
  uVar2 = *(undefined4 *)(in_ECX + 0x1c);
  *param_1 = *(undefined4 *)(in_ECX + 4);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}



// ==== 0x40e6b2 ====

void FUN_0040e6b2(int param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  undefined1 local_10 [12];
  
  uVar4 = param_2 ^ 1;
  puVar3 = (undefined4 *)(*(int *)(param_1 + param_2 * 4) + 0x60);
  puVar6 = (undefined4 *)(*(int *)(param_1 + uVar4 * 4) + 0x60);
  for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  iVar1 = *(int *)(param_1 + param_2 * 4);
  iVar5 = iVar1 + 0x84;
  puVar7 = local_10;
  FUN_004023c6(local_1c,iVar1 + 0x60);
  FUN_00402172(puVar7,iVar5);
  iVar5 = *(int *)(param_1 + uVar4 * 4);
  uVar2 = FUN_00402363(local_1c,param_1 + 8 + uVar4 * 0xc);
  puVar3 = (undefined4 *)FUN_004021a7(local_28,uVar2);
  *(undefined4 *)(iVar5 + 0x84) = *puVar3;
  *(undefined4 *)(iVar5 + 0x88) = puVar3[1];
  *(undefined4 *)(iVar5 + 0x8c) = puVar3[2];
  return;
}



// ==== 0x40e73a ====

void FUN_0040e73a(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int in_ECX;
  undefined4 *puVar3;
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined1 local_20 [12];
  undefined1 local_14 [12];
  undefined4 *local_8;
  
  puVar3 = (undefined4 *)(param_1 + 0x3c);
  param_1 = 0xe;
  local_8 = (undefined4 *)(in_ECX + 0x24);
  do {
    uVar1 = FUN_004023c6(local_14,*(int *)*puVar3 + 0x60);
    puVar2 = (undefined4 *)FUN_00402363(local_20,uVar1);
    local_8[-3] = *puVar2;
    local_8[-2] = puVar2[1];
    local_8[-1] = puVar2[2];
    uVar1 = FUN_004023c6(local_2c,*(int *)*puVar3 + 0x60);
    puVar2 = (undefined4 *)FUN_00402363(local_38,uVar1);
    *local_8 = *puVar2;
    local_8[1] = puVar2[1];
    puVar3 = puVar3 + 1;
    param_1 = param_1 + -1;
    local_8[2] = puVar2[2];
    local_8 = local_8 + 0xd;
  } while (param_1 != 0);
  return;
}



// ==== 0x40e7c8 ====

void FUN_0040e7c8(float *param_1)

{
  float *pfVar1;
  int in_ECX;
  int iVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0.0;
  local_8 = 0.0;
  local_10 = 0.0;
  local_c = 0.0;
  iVar2 = 0;
  do {
    pfVar1 = (float *)(*(int *)(in_ECX + iVar2 * 4) + 0xac);
    local_8 = local_8 + *pfVar1;
    pfVar1 = (float *)FUN_00402227(&local_20,pfVar1);
    local_14 = local_14 + *pfVar1;
    iVar2 = iVar2 + 1;
    local_10 = local_10 + pfVar1[1];
    local_c = local_c + pfVar1[2];
  } while (iVar2 < 0xf);
  local_8 = 1.0 / local_8;
  local_14 = local_14 * local_8;
  local_10 = local_10 * local_8;
  local_c = local_c * local_8;
  if (1e+06 < local_10 * local_10 + local_14 * local_14 + local_c * local_c) {
    local_c = 0.0;
    local_10 = 0.0;
    local_14 = 0.0;
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  return;
}



// ==== 0x40e896 ====

void FUN_0040e896(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    FUN_004022a2();
    FUN_004022a2();
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xf);
  return;
}



// ==== 0x40e8f0 ====

void FUN_0040e8f0(float *param_1)

{
  float *pfVar1;
  int in_ECX;
  int iVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0.0;
  local_8 = 0.0;
  local_10 = 0.0;
  local_c = 0.0;
  iVar2 = 0;
  do {
    pfVar1 = (float *)(*(int *)(in_ECX + iVar2 * 4) + 0xac);
    local_8 = local_8 + *pfVar1;
    pfVar1 = (float *)FUN_00402227(&local_20,pfVar1);
    local_14 = local_14 + *pfVar1;
    iVar2 = iVar2 + 1;
    local_10 = local_10 + pfVar1[1];
    local_c = local_c + pfVar1[2];
  } while (iVar2 < 0xf);
  local_8 = 1.0 / local_8;
  *param_1 = local_14 * local_8;
  param_1[1] = local_10 * local_8;
  param_1[2] = local_c * local_8;
  return;
}



// ==== 0x40e98c ====

void FUN_0040e98c(float *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float *pfVar3;
  int in_ECX;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  undefined1 local_28 [12];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0.0;
  local_c = 0.0;
  local_8 = 0.0;
  iVar4 = 0;
  do {
    iVar7 = *(int *)(in_ECX + iVar4 * 4);
    uVar1 = FUN_00402227(&local_1c,iVar7 + 0xb4);
    puVar8 = local_28;
    iVar7 = iVar7 + 0xac;
    puVar6 = local_34;
    uVar2 = FUN_004021a7(local_40,param_2);
    puVar5 = local_4c;
    FUN_004021a7(local_58,param_3);
    FUN_004021dc(puVar5,uVar2);
    FUN_00402227(puVar6,iVar7);
    pfVar3 = (float *)FUN_00402172(puVar8,uVar1);
    local_10 = local_10 + *pfVar3;
    iVar4 = iVar4 + 1;
    local_c = local_c + pfVar3[1];
    local_8 = local_8 + pfVar3[2];
  } while (iVar4 < 0xf);
  *param_1 = local_10;
  param_1[1] = local_c;
  param_1[2] = local_8;
  return;
}



// ==== 0x40ea52 ====

void FUN_0040ea52(int param_1)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int in_ECX;
  int *piVar4;
  float10 fVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  undefined1 local_44 [12];
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_1c = 0x3ecccccd;
  local_20 = 0x3e800000;
  piVar4 = (int *)(in_ECX + 0x3c);
  param_1 = param_1 + 0x18;
  local_18 = 0xe;
  do {
    fVar1 = *(float *)(param_1 + 0x18);
    local_14 = (float)(*(int *)(*piVar4 + 4) + 0x60);
    FUN_004023c6(local_44,local_14);
    FUN_004023c6(local_38,*(int *)*piVar4 + 0x60);
    uVar8 = CONCAT44(&local_1c,&local_10);
    FUN_004021dc(local_74,local_38);
    FUN_00402227(uVar8);
    FUN_004023c6(local_50,local_14);
    FUN_004023c6(local_2c,*(int *)*piVar4 + 0x60);
    uVar8 = CONCAT44(&local_20,local_5c);
    puVar7 = &local_1c;
    puVar6 = local_8c;
    FUN_004021dc(local_68,local_2c);
    FUN_00402227(puVar6,puVar7);
    pfVar3 = (float *)FUN_00402227(uVar8);
    local_10 = local_10 + *pfVar3;
    local_c = local_c + pfVar3[1];
    local_8 = local_8 + pfVar3[2];
    pfVar3 = (float *)FUN_004021a7(local_80,*(int *)(*piVar4 + 4) + 0x90);
    local_10 = local_10 - *pfVar3;
    local_c = local_c - pfVar3[1];
    local_8 = local_8 - pfVar3[2];
    fVar2 = local_10 * local_10 + local_c * local_c + local_8 * local_8;
    if (fVar1 * fVar1 < fVar2) {
      fVar5 = (float10)FUN_0041d134((double)fVar2);
      fVar5 = (float10)fVar1 / fVar5;
      local_10 = (float)((float10)local_10 * fVar5);
      local_c = (float)((float10)local_c * fVar5);
      local_8 = (float)((float10)local_8 * fVar5);
    }
    local_14 = 0.7 / (*(float *)(((int *)*piVar4)[1] + 0xb8) + *(float *)(*(int *)*piVar4 + 0xb8));
    FUN_00402227(local_98,&local_14);
    FUN_004086a6();
    piVar4 = piVar4 + 1;
    param_1 = param_1 + 0x34;
    local_18 = local_18 + -1;
  } while (local_18 != 0);
  return;
}



// ==== 0x40ec0d ====

void FUN_0040ec0d(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  float fVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int *in_ECX;
  int iVar5;
  int *piVar6;
  float10 fVar7;
  undefined1 local_1bc [12];
  undefined1 local_1b0 [12];
  undefined1 local_1a4 [12];
  undefined1 local_198 [12];
  undefined1 local_18c [12];
  float local_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  float local_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  float local_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  int local_15c;
  int iStack_158;
  int iStack_154;
  int local_150;
  int iStack_14c;
  int iStack_148;
  int local_144;
  int local_140;
  float local_13c;
  int local_138;
  int local_134;
  float local_130;
  int local_12c;
  int local_128;
  float local_124;
  int local_120;
  int local_11c;
  float local_118;
  int local_114;
  int local_110;
  int local_10c;
  int local_108;
  int local_104;
  float local_100;
  int local_fc;
  int local_f8;
  float local_f4;
  int local_f0;
  int local_ec;
  float local_e8;
  int local_e4;
  int local_e0;
  float local_dc;
  int local_d8;
  int local_d4;
  float local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  float local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  float local_a0;
  int local_9c;
  int local_98;
  float local_94;
  int local_90;
  int local_8c;
  float local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  float local_58;
  int local_54;
  int local_50;
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  float local_38;
  int *local_34;
  int local_30;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  float local_10;
  int local_c;
  int local_8;
  
  piVar6 = in_ECX;
  for (iVar5 = 0x1cc; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  local_34 = in_ECX;
  _memset(in_ECX,0,0x730);
  FUN_0040b798();
  iVar5 = FUN_0041d384();
  in_ECX[0x1c6] = iVar5;
  FUN_0040b798();
  iVar5 = FUN_0041d384();
  in_ECX[0x1c7] = iVar5;
  FUN_0040b798();
  iVar5 = FUN_0041d384();
  in_ECX[0x1cb] = 0;
  in_ECX[0x1ca] = iVar5;
  fVar7 = (float10)FUN_0040b798();
  if (((fVar7 < (float10)0.5) && (param_4 != 0)) && (*(int *)(param_4 + 0x6fc) == 2)) {
    FUN_0040b798();
    iVar5 = FUN_0041d384();
    in_ECX[0x1cb] = iVar5;
  }
  fVar7 = (float10)FUN_0040b798();
  in_ECX[0x1c9] = (uint)(fVar7 < (float10)0.3);
  local_2c = 0.0;
  local_28 = 0x415ccccd;
  local_24 = 0;
  local_1c = 0x40333333;
  local_18 = 0xc00ccccd;
  local_14 = 0x40000000;
  puVar3 = (undefined4 *)FUN_00402172(&local_150,param_1);
  iVar5 = FUN_00408d57(local_1c,local_18,local_14,*puVar3,puVar3[1],puVar3[2],param_3,0x3e000000);
  *(undefined4 *)(iVar5 + 0xe0) = 0x28;
  local_140 = iVar5;
  FUN_00402456();
  local_14 = 0x3dcccccd;
  local_1c = 0;
  local_18 = 0;
  local_2c = 0.0;
  local_28 = 0;
  local_24 = 0x3dcccccd;
  FUN_00402363(&local_15c,&local_2c);
  FUN_0040225a();
  local_1c = 0;
  local_18 = 0x41f00000;
  local_14 = 0;
  *(undefined4 *)(iVar5 + 0xc0) = 4;
  *(undefined4 *)(iVar5 + 0xc4) = 0x3c23d70a;
  local_10 = 2.7;
  local_c = 0xc00ccccd;
  local_8 = 0x3fc00000;
  local_3c = FUN_00408d57(0x402ccccd,0xc00ccccd,0x3fc00000,0,0x41f00000,0,param_3,0x3e000000);
  local_c = 0x42100000;
  local_10 = 0.0;
  local_18 = 0xbfc00000;
  local_8 = 0;
  *(undefined4 *)(local_3c + 0xe0) = 0x28;
  local_1c = 0x3f99999a;
  *(undefined4 *)(local_3c + 0xc0) = 4;
  local_14 = 0x3f99999a;
  *(undefined4 *)(local_3c + 0xc4) = 0x3c23d70a;
  iVar4 = FUN_00408d57(0x3f99999a,0xbfc00000,0x3f99999a,0,0x42100000,0,param_3,0x3e000000);
  *(undefined4 *)(iVar4 + 0xe0) = 0x28;
  *DAT_00561404 = iVar5;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 3;
  DAT_00561404[2] = 0;
  *piVar6 = 0x4019999a;
  piVar2[4] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 9;
  DAT_00561404[8] = 0;
  *piVar6 = -0x40800000;
  piVar2[10] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 0xf;
  DAT_00561404[0xe] = 0x3f800000;
  *piVar6 = 0;
  piVar2[0x10] = 0;
  DAT_00561404[1] = local_3c;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 6;
  DAT_00561404[5] = 0;
  *piVar6 = -0x3ff33333;
  piVar2[7] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 0xc;
  DAT_00561404[0xb] = 0;
  *piVar6 = -0x40800000;
  piVar2[0xd] = 0;
  piVar2 = DAT_00561404;
  local_10 = 1.0;
  local_c = 0;
  local_8 = 0;
  piVar6 = DAT_00561404 + 0x12;
  DAT_00561404[0x11] = 0x3f800000;
  *piVar6 = 0;
  piVar2[0x13] = 0;
  DAT_00561404[0x15] = 0x3db851ec;
  DAT_00561404[0x16] = 0x3e23d70b;
  DAT_00561404[0x14] = 0;
  *(undefined1 *)(DAT_00561404 + 0x18) = 1;
  FUN_0040e6b2(DAT_00561404,0);
  DAT_00561404 = DAT_00561404 + 0x3d;
  *DAT_00561404 = local_3c;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 3;
  DAT_00561404[2] = 0;
  *piVar6 = 0x402ccccd;
  piVar2[4] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 9;
  DAT_00561404[8] = 0;
  *piVar6 = -0x40800000;
  piVar2[10] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 0xf;
  DAT_00561404[0xe] = 0x3f800000;
  *piVar6 = 0;
  piVar2[0x10] = 0;
  DAT_00561404[1] = iVar4;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 6;
  DAT_00561404[5] = 0;
  *piVar6 = -0x40400000;
  piVar2[7] = 0;
  piVar2 = DAT_00561404;
  piVar6 = DAT_00561404 + 0xc;
  DAT_00561404[0xb] = 0;
  *piVar6 = -0x40800000;
  piVar2[0xd] = 0;
  piVar2 = DAT_00561404;
  local_10 = 1.0;
  local_c = 0;
  local_8 = 0;
  piVar6 = DAT_00561404 + 0x12;
  DAT_00561404[0x11] = 0x3f800000;
  *piVar6 = 0;
  piVar2[0x13] = 0;
  DAT_00561404[0x15] = 0x3efae147;
  DAT_00561404[0x16] = 0x3f4f5c28;
  DAT_00561404[0x14] = 0;
  *(undefined1 *)(DAT_00561404 + 0x18) = 0;
  FUN_0040e6b2(DAT_00561404,0);
  param_2 = 1.0;
  DAT_00561404 = DAT_00561404 + 0x3d;
  local_8 = 0x3f800000;
  local_c = 0x3f333333;
  local_18 = 0xbf333333;
  local_1c = 0x3f99999a;
  local_14 = 0x40000000;
  local_6c = 0xc0133333;
  local_d8 = 0x400ccccd;
  local_d4 = 0;
  local_70 = 0x3f800000;
  local_68 = 0x3f800000;
  local_f0 = 0x400ccccd;
  local_ec = 0;
  local_84 = 0xc0400000;
  local_88 = 1.2;
  local_b4 = -0x40000000;
  local_134 = 0x3dcccccd;
  local_80 = 0x3f99999a;
  local_c8 = -0x40e66666;
  local_48 = 0x40133333;
  local_10c = 0;
  local_fc = -0x3fe00000;
  local_12c = -0x41b33333;
  local_a8 = -0x4019999a;
  local_108 = 0x400ccccd;
  local_104 = 0;
  local_a0 = 0.0;
  local_9c = -0x40800000;
  local_98 = 0;
  local_120 = 0;
  local_11c = 0;
  local_b0 = 0;
  local_138 = -0x40800000;
  local_cc = 0;
  local_4c = 0.0;
  local_44 = 0;
  local_e8 = 0.0;
  local_e4 = -0x40800000;
  local_e0 = 0;
  local_114 = 0;
  local_110 = 0;
  local_100 = 0.0;
  local_f8 = 0;
  local_130 = 0.0;
  local_128 = -0x40800000;
  local_54 = 0;
  local_50 = 0;
  local_64 = 0;
  local_60 = 0x3f800000;
  local_5c = -0x40800000;
  local_7c = 0;
  local_78 = -0x40800000;
  local_74 = 0;
  local_90 = 0;
  local_8c = 0;
  local_ac = 0;
  local_a4 = 0;
  local_c4 = 0;
  local_c0 = -0x40800000;
  local_bc = 0;
  local_30 = 2;
  local_28 = 0;
  local_24 = 0;
  do {
    local_180 = param_2 * 1.5;
    uStack_17c = local_c;
    uStack_178 = local_8;
    local_38 = local_180;
    local_10 = local_180;
    puVar3 = (undefined4 *)FUN_00402172(local_18c,param_1);
    iVar5 = FUN_00408d57(local_1c,local_18,local_14,*puVar3,puVar3[1],puVar3[2],param_3,0x3e000000);
    local_40 = iVar5;
    FUN_004088b5();
    *(undefined4 *)(iVar5 + 0xe0) = 0x28;
    *(undefined4 *)(iVar5 + 0xc0) = 3;
    *(undefined4 *)(iVar5 + 0xc4) = 0x3b03126f;
    *(float *)(iVar5 + 0xb4) = *(float *)(iVar5 + 0xb4) * 0.5;
    fVar1 = *(float *)(iVar5 + 0xb8);
    *(undefined4 *)(iVar5 + 200) = 0x43c80000;
    *(float *)(iVar5 + 0xb8) = fVar1 + fVar1;
    local_dc = local_38;
    local_174 = local_38;
    uStack_170 = local_d8;
    uStack_16c = local_d4;
    puVar3 = (undefined4 *)FUN_00402172(local_1b0,param_1);
    iVar5 = FUN_00408d57(local_70,local_6c,local_68,*puVar3,puVar3[1],puVar3[2],param_3,0x3e000000);
    local_20 = iVar5;
    FUN_004088b5();
    local_168 = param_2 * 3.0;
    *(undefined4 *)(iVar5 + 0xe0) = 0x28;
    *(undefined4 *)(iVar5 + 0xc0) = 4;
    *(undefined4 *)(iVar5 + 0xc4) = 0x3ba3d70a;
    uStack_164 = local_f0;
    uStack_160 = local_ec;
    local_f4 = local_168;
    puVar3 = (undefined4 *)FUN_00402172(local_198,param_1);
    local_144 = FUN_00408d57(local_88,local_84,local_80,*puVar3,puVar3[1],puVar3[2],param_3,
                             0x3e000000);
    *(undefined4 *)(local_144 + 0xe0) = 0x28;
    *(undefined4 *)(local_144 + 0xc0) = 4;
    *(undefined4 *)(local_144 + 0xc4) = 0x3ba3d70a;
    *DAT_00561404 = local_144;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = local_10c;
    *piVar6 = local_108;
    piVar2[4] = local_104;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = (int)local_a0;
    *piVar6 = local_9c;
    piVar2[10] = local_98;
    piVar2 = DAT_00561404;
    local_124 = param_2;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = (int)param_2;
    *piVar6 = local_120;
    piVar2[0x10] = local_11c;
    local_15c = DAT_00561404[2];
    iStack_158 = DAT_00561404[3];
    iStack_154 = DAT_00561404[4];
    DAT_00561404[1] = local_140;
    piVar2 = DAT_00561404;
    local_b8 = local_38;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = (int)local_38;
    *piVar6 = local_b4;
    piVar2[7] = local_b0;
    piVar2 = DAT_00561404;
    local_13c = param_2 * 0.8;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = (int)local_13c;
    *piVar6 = local_138;
    piVar2[0xd] = local_134;
    FUN_004022c1();
    piVar2 = DAT_00561404;
    local_d0 = param_2;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = (int)param_2;
    *piVar6 = local_cc;
    piVar2[0x13] = local_c8;
    FUN_004022c1();
    DAT_00561404[0x15] = 0x3f23d70b;
    DAT_00561404[0x16] = 0x3eb851ec;
    DAT_00561404[0x14] = 0;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_0040e6b2(DAT_00561404,1);
    DAT_00561404 = DAT_00561404 + 0x3d;
    *DAT_00561404 = local_20;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = (int)local_4c;
    *piVar6 = local_48;
    piVar2[4] = local_44;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = (int)local_e8;
    *piVar6 = local_e4;
    piVar2[10] = local_e0;
    piVar2 = DAT_00561404;
    local_118 = param_2;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = (int)param_2;
    *piVar6 = local_114;
    piVar2[0x10] = local_110;
    local_150 = DAT_00561404[2];
    iStack_14c = DAT_00561404[3];
    iStack_148 = DAT_00561404[4];
    DAT_00561404[1] = local_144;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = (int)local_100;
    *piVar6 = local_fc;
    piVar2[7] = local_f8;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = (int)local_130;
    *piVar6 = local_12c;
    piVar2[0xd] = local_128;
    FUN_004022c1();
    piVar2 = DAT_00561404;
    local_58 = param_2;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = (int)param_2;
    *piVar6 = local_54;
    piVar2[0x13] = local_50;
    DAT_00561404[0x15] = 0x3f75dcc7;
    DAT_00561404[0x16] = 0x3e800000;
    DAT_00561404[0x14] = 0x3f800000;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_004021a7(local_1a4,DAT_00561404 + 5);
    fVar7 = (float10)FUN_004022a2();
    fVar7 = (float10)FUN_0041d134((double)fVar7);
    local_34[0x1d] = (int)(float)fVar7;
    FUN_0040e6b2(DAT_00561404,1);
    DAT_00561404 = DAT_00561404 + 0x3d;
    local_94 = param_2;
    *DAT_00561404 = local_40;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = local_64;
    *piVar6 = local_60;
    piVar2[4] = local_5c;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = local_7c;
    *piVar6 = local_78;
    piVar2[10] = local_74;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = (int)param_2;
    *piVar6 = local_90;
    piVar2[0x10] = local_8c;
    DAT_00561404[1] = local_20;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = local_ac;
    *piVar6 = local_a8;
    piVar2[7] = local_a4;
    piVar2 = DAT_00561404;
    local_2c = param_2;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = local_c4;
    *piVar6 = local_c0;
    piVar2[0xd] = local_bc;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = (int)param_2;
    *piVar6 = local_28;
    piVar2[0x13] = local_24;
    DAT_00561404[0x15] = 0x3efae147;
    DAT_00561404[0x16] = 0x3e800000;
    DAT_00561404[0x14] = 0;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_004021a7(local_1bc,DAT_00561404 + 5);
    FUN_004022a2();
    fVar7 = (float10)FUN_0041d134();
    local_34[0x1e] = (int)(float)fVar7;
    FUN_0040e6b2(DAT_00561404,1);
    DAT_00561404 = DAT_00561404 + 0x3d;
    local_30 = local_30 + -1;
    param_2 = -1.0;
  } while (local_30 != 0);
  local_c0 = 0xbf4ccccd;
  param_2 = 1.0;
  local_90 = 0xbf333333;
  local_8c = 0x3f4ccccd;
  local_2c = 0.0;
  local_64 = 0x3fb33333;
  local_60 = 0xbe99999a;
  local_54 = 0x40000000;
  local_28 = 0;
  local_128 = 0x3e4ccccd;
  local_c8 = -0x41666666;
  local_24 = 0;
  local_c4 = 0x3ff33333;
  local_bc = 0x3f8ccccd;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_94 = 1.9;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_5c = 0x3f8ccccd;
  local_50 = 0x3dcccccd;
  local_12c = 0;
  local_fc = 0x3f800000;
  local_f8 = 0;
  local_114 = 0;
  local_110 = 0;
  local_e4 = 0;
  local_e0 = 0;
  local_48 = 0x3f800000;
  local_44 = 0;
  local_cc = 0;
  local_138 = 0;
  local_134 = 0x3f800000;
  local_b8 = 0.0;
  local_b4 = 0x3f800000;
  local_b0 = 0;
  local_120 = 0;
  local_11c = 0;
  local_9c = 0;
  local_98 = 0;
  local_10c = 0;
  local_108 = 0x3f800000;
  local_30 = 2;
  local_104 = 0;
  local_84 = 0;
  local_80 = 0x3dcccccd;
  local_f0 = 0;
  local_ec = 0;
  local_70 = 0;
  local_6c = 0x3f800000;
  local_68 = 0;
  local_d8 = 0;
  local_d4 = 0;
  local_c = 0;
  local_8 = 0;
  local_1c = 0;
  local_18 = 0x3f800000;
  local_14 = 0;
  do {
    iVar5 = FUN_00408d57(local_c4,local_c0,local_bc,local_2c,local_28,local_24,param_3,0x3e000000);
    *(undefined4 *)(iVar5 + 0xe0) = 0x28;
    local_20 = FUN_00408d57(local_94,local_90,local_8c,local_ac,local_a8,local_a4,param_3);
    *(undefined4 *)(local_20 + 0xe0) = 0x28;
    local_40 = FUN_00408d57(local_64,local_60,local_5c,local_7c,local_78,local_74,param_3);
    *(undefined4 *)(local_40 + 0xc4) = 0x3ba3d70a;
    *(undefined4 *)(local_40 + 0xc0) = 4;
    *(undefined4 *)(local_40 + 0xe0) = 0x28;
    *(undefined4 *)(local_20 + 0xc4) = 0x3ba3d70a;
    *(undefined4 *)(local_20 + 0xc0) = 4;
    *(undefined4 *)(iVar5 + 0xc4) = 0x3ba3d70a;
    *(undefined4 *)(iVar5 + 0xc0) = 4;
    FUN_004088b5();
    FUN_004088b5();
    DAT_00561404[1] = local_3c;
    piVar2 = DAT_00561404;
    local_58 = param_2 * 3.2;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = (int)local_58;
    *piVar6 = local_54;
    local_100 = param_2 * 0.0;
    piVar2[7] = local_50;
    piVar2 = DAT_00561404;
    local_130 = param_2;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = (int)param_2;
    *piVar6 = local_12c;
    piVar2[0xd] = local_128;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = (int)local_100;
    *piVar6 = local_fc;
    piVar2[0x13] = local_f8;
    FUN_004022c1();
    *DAT_00561404 = iVar5;
    piVar2 = DAT_00561404;
    local_118 = param_2 * -1.5;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = (int)local_118;
    local_4c = param_2 * 0.5;
    *piVar6 = local_114;
    piVar2[4] = local_110;
    piVar2 = DAT_00561404;
    local_e8 = param_2;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = (int)param_2;
    *piVar6 = local_e4;
    piVar2[10] = local_e0;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = (int)local_4c;
    *piVar6 = local_48;
    piVar2[0x10] = local_44;
    FUN_004022c1();
    DAT_00561404[0x15] = 0x3f75dcc7;
    DAT_00561404[0x16] = 0x3efae147;
    DAT_00561404[0x14] = 0;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_0040e6b2(DAT_00561404);
    DAT_00561404 = DAT_00561404 + 0x3d;
    local_d0 = param_2 * 1.5;
    *DAT_00561404 = iVar5;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = (int)local_d0;
    local_13c = param_2 * 0.6;
    *piVar6 = local_cc;
    piVar2[4] = local_c8;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = (int)local_13c;
    *piVar6 = local_138;
    piVar2[10] = local_134;
    local_38 = local_d0;
    FUN_004022c1();
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = (int)local_b8;
    local_124 = param_2 * -1.8;
    *piVar6 = local_b4;
    local_a0 = param_2;
    piVar2[0x10] = local_b0;
    DAT_00561404[1] = local_20;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = (int)local_124;
    *piVar6 = local_120;
    piVar2[7] = local_11c;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = (int)param_2;
    *piVar6 = local_9c;
    piVar2[0xd] = local_98;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = local_10c;
    *piVar6 = local_108;
    piVar2[0x13] = local_104;
    DAT_00561404[0x15] = 0x3f41c433;
    DAT_00561404[0x16] = 0x3e800000;
    DAT_00561404[0x14] = 0x3f800000;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_0040e6b2();
    DAT_00561404 = DAT_00561404 + 0x3d;
    *DAT_00561404 = local_20;
    piVar2 = DAT_00561404;
    local_88 = local_38;
    piVar6 = DAT_00561404 + 3;
    DAT_00561404[2] = (int)local_38;
    *piVar6 = local_84;
    local_f4 = param_2;
    piVar2[4] = local_80;
    piVar2 = DAT_00561404;
    local_dc = param_2 * -1.1;
    local_10 = param_2;
    piVar6 = DAT_00561404 + 9;
    DAT_00561404[8] = (int)param_2;
    *piVar6 = local_f0;
    piVar2[10] = local_ec;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xf;
    DAT_00561404[0xe] = local_70;
    *piVar6 = local_6c;
    piVar2[0x10] = local_68;
    DAT_00561404[1] = local_40;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 6;
    DAT_00561404[5] = (int)local_dc;
    *piVar6 = local_d8;
    piVar2[7] = local_d4;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0xc;
    DAT_00561404[0xb] = (int)param_2;
    *piVar6 = local_c;
    piVar2[0xd] = local_8;
    piVar2 = DAT_00561404;
    piVar6 = DAT_00561404 + 0x12;
    DAT_00561404[0x11] = local_1c;
    *piVar6 = local_18;
    piVar2[0x13] = local_14;
    DAT_00561404[0x15] = 0x3e800000;
    DAT_00561404[0x16] = 0x3f23d70b;
    DAT_00561404[0x14] = 0;
    *(undefined1 *)(DAT_00561404 + 0x18) = 0;
    FUN_0040e6b2(DAT_00561404,0);
    DAT_00561404 = DAT_00561404 + 0x3d;
    local_30 = local_30 + -1;
    param_2 = -1.0;
  } while (local_30 != 0);
  iVar5 = -0xec4;
  piVar6 = local_34;
  do {
    *piVar6 = DAT_00561408 + iVar5;
    iVar5 = iVar5 + 0xfc;
    piVar6 = piVar6 + 1;
  } while (iVar5 < 0);
  iVar5 = -0xd58;
  piVar6 = local_34 + 0xf;
  do {
    *piVar6 = (int)DAT_00561404 + iVar5;
    iVar5 = iVar5 + 0xf4;
    piVar6 = piVar6 + 1;
  } while (iVar5 < 0);
  local_34[0x3c] = -0x3f033333;
  local_34[0x1f] = 0x3f000000;
  local_34[0x20] = -0x3f033333;
  local_34[0x21] = 0;
  local_28 = 0xc0fccccd;
  local_24 = 0;
  local_2c = -0.5;
  local_34[0x22] = -0x41000000;
  local_34[0x23] = -0x3f033333;
  local_34[0x24] = 0;
  FUN_0040e73a();
  FUN_0040e73a();
  local_34[0x1c0] = param_4;
  return;
}



// ==== 0x40fd42 ====

void FUN_0040fd42(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_00c06b60;
  if (&DAT_00c06b60 < PTR_DAT_00453858) {
    do {
      FUN_0040ea52(puVar1 + 0x53);
      puVar1 = puVar1 + 0x1cc;
    } while (puVar1 < PTR_DAT_00453858);
  }
  return;
}



// ==== 0x40fd6e ====

float10 FUN_0040fd6e(float param_1,float param_2,float param_3)

{
  float10 fVar1;
  float10 fVar2;
  
  if (param_1 + param_2 < param_3 != (param_1 + param_2 == param_3)) {
    return (float10)1.0;
  }
  if (param_1 + param_3 < param_2) {
    return (float10)-1.0;
  }
  fVar1 = ((float10)1 / (float10)param_1) * (float10)param_2;
  fVar2 = (float10)(float)((float10)1 / (float10)param_1) * (float10)param_3;
  return -(((fVar1 * fVar1 - fVar2 * fVar2) + (float10)1.0) / (fVar1 + fVar1));
}



// ==== 0x40fdd0 ====

void FUN_0040fdd0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = 0xbf800000;
  uStack_18 = 0;
  uStack_14 = 0xbf800000;
  local_10 = 0x3f800000;
  local_c = 0;
  local_8 = 0x3f800000;
  local_28 = 0x3f800000;
  uStack_24 = 0;
  uStack_20 = 0x3f800000;
  uVar3 = param_2;
  uVar1 = FUN_00402172(&local_10,&local_1c);
  uVar2 = FUN_00402172(&local_1c,&local_28);
  FUN_00407ca6(uVar2,uVar1,uVar3);
  local_28 = 0xbf800000;
  uStack_24 = 0;
  uStack_20 = 0x3f800000;
  local_10 = 0x3f800000;
  local_c = 0;
  local_8 = 0xbf800000;
  local_1c = 0x3f800000;
  uStack_18 = 0;
  uStack_14 = 0xbf800000;
  uVar3 = FUN_00402172(&local_10,&local_28);
  uVar1 = FUN_00402172(&local_28,&local_1c);
  FUN_00407ca6(uVar1,uVar3,param_2);
  return;
}



// ==== 0x40fe9b ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_0040fe9b(void)

{
  uint uVar1;
  int in_ECX;
  int iVar2;
  uint uVar3;
  char local_18 [16];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  uVar1 = 0;
  builtin_strncpy(local_18,"KMHP\x0e\x1c",7);
  local_18[7] = '\0';
  local_18[8] = 0x1e;
  local_18[9] = 0x20;
  local_18[10] = 0x11;
  local_18[0xb] = 0x1f;
  local_18[0xc] = 0x2a;
  local_18[0xd] = 0x1d;
  uVar3 = 1;
  local_18[0xe] = '\0';
  local_18[0xf] = '\0';
  iVar2 = 0;
  do {
    if ((&DAT_00d0f3e0)[local_18[iVar2 + in_ECX * 8]] != '\0') {
      uVar1 = uVar1 | uVar3;
    }
    uVar3 = uVar3 * 2;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 6);
  return uVar1;
}



// ==== 0x40ff13 ====

void FUN_0040ff13(int param_1,uint param_2)

{
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x140) = 8;
  FUN_0041538b(5,0x3f800000,0x3f400000,param_2 ^ 3);
  return;
}



// ==== 0x40ff4c ====

uint FUN_0040ff4c(int param_1)

{
  int *piVar1;
  bool bVar2;
  float *pfVar3;
  float *pfVar4;
  int *in_ECX;
  float10 fVar5;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  float local_40;
  float local_3c;
  float local_38;
  float local_34 [4];
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  uint local_c;
  char local_6;
  char local_5;
  
  if (DAT_00c06b50 == 0xb) {
    if ((((*(int *)(*in_ECX + 0xd4) == DAT_00c06978) && (10 < DAT_00c06978)) && (in_ECX[0x29] == 0))
       && (in_ECX[0x50] == 0)) {
      FUN_0040ff13();
    }
    local_c = 0;
  }
  else {
    FUN_0040e8f0(local_4c);
    FUN_0040e8f0(local_58);
    local_40 = 1.0;
    local_c = 0;
    local_3c = 0.0;
    local_38 = 0.0;
    local_34[0] = 1.0;
    local_34[1] = 0.0;
    local_34[2] = 0.0;
    FUN_004023c6(&local_40,*in_ECX + 0x60);
    local_3c = 0.0;
    FUN_004022c1();
    local_34[0] = 0.0;
    local_34[1] = 1.0;
    local_34[2] = 0.0;
    local_64 = 0;
    uStack_60 = 0x3f800000;
    uStack_5c = 0;
    FUN_004021dc(local_34 + 3,&local_64);
    FUN_004021a7(local_34,*in_ECX + 0x84);
    local_18 = local_34[3] * (float)in_ECX[0x49] +
               local_20 * (float)in_ECX[0x4b] + local_24 * (float)in_ECX[0x4a];
    local_10 = local_3c * 0.0 + local_40 * local_34[0] + local_38 * local_34[2];
    local_6 = *(int *)(param_1 + 0x130) != 0;
    local_14 = local_24 * 0.0 + local_34[0] * local_34[3] + local_34[2] * local_20;
    fVar5 = (float10)FUN_004022a2();
    local_5 = (float10)25.0 < fVar5;
    fVar5 = (float10)FUN_004022a2();
    bVar2 = fVar5 < (float10)0.040000003;
    local_1c = local_10 * local_10;
    if ((((local_1c < (local_34[0] * local_34[0] + local_34[2] * local_34[2]) * 0.25) ||
         (local_1c < 16.0)) &&
        ((fVar5 = (float10)FUN_004022a2(), fVar5 < (float10)16.0 &&
         ((0.0 < local_14 && (local_5 == '\0')))))) &&
       ((in_ECX[0x1c5] < 0xa0 ||
        (-2.0 < local_34[3] * (float)in_ECX[0x49] +
                local_20 * (float)in_ECX[0x4b] + local_24 * (float)in_ECX[0x4a])))) {
      local_10 = 1.6;
      if (bVar2) {
        local_10 = 1.4;
      }
      if (in_ECX[0x50] == 3) {
        local_10 = (float)in_ECX[0x51] * local_10 * 0.0015384615;
      }
      if (in_ECX[0x1ca] < DAT_00c06978 - DAT_00c06b58) {
        fVar5 = (float10)FUN_004022a2();
        if (fVar5 < (float10)local_10 * (float10)local_10) {
          local_c = 4;
        }
      }
      else if (DAT_00c06978 - DAT_00c06b58 < in_ECX[0x1cb]) {
        local_c = 1;
      }
    }
    local_10 = 5.1;
    if ((bVar2) && (local_10 = 4.8, local_6 != '\0')) {
      local_10 = 8.0;
    }
    pfVar3 = (float *)FUN_004021a7(&local_64,local_4c);
    pfVar4 = (float *)FUN_004021a7(&local_40,local_4c);
    if (((local_10 * local_10 <=
          ((local_34[3] * *pfVar4 + local_20 * pfVar4[2] + local_24 * pfVar4[1]) * 50.0 + local_14)
          * ((local_34[3] * *pfVar3 + local_20 * pfVar3[2] + local_24 * pfVar3[1]) * 50.0 + local_14
            )) || (local_18 <= -0.5)) || (64.0 <= local_1c)) {
      piVar1 = in_ECX + 0x1c5;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        *piVar1 = 0;
      }
    }
    else {
      if (((10 < in_ECX[0x1c5]) || (7.5 < local_10)) || (in_ECX[0x1c9] != 0)) {
        local_c = local_c | 0x20;
      }
      else {
        local_c = local_c | 0x10;
      }
      if (bVar2) {
        local_c = local_c & 0xfffffffb;
      }
      in_ECX[0x1c5] = in_ECX[0x1c5] + 8;
    }
    if (DAT_00c06b50 == 0) {
      if (DAT_00c06978 <= in_ECX[0x1c6]) {
        if (DAT_00c06978 <= in_ECX[0x1c7]) {
          return local_c;
        }
        if (in_ECX[0x1c7] + 8 <= DAT_00c06978) {
          return local_c;
        }
      }
      local_c = 8;
    }
    if (DAT_00c06b50 == 2) {
      if (DAT_004eac84 == 0) {
        if (200 < DAT_00c06978 % 400) {
          local_c = local_c | 4;
        }
      }
      else {
        local_c = local_c & 0xfffffffb;
      }
    }
  }
  return local_c;
}



// ==== 0x410342 ====

void FUN_00410342(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  float in_stack_0000001c;
  undefined4 in_stack_00000020;
  float *pfVar3;
  undefined1 local_20 [12];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  float local_8;
  
  local_14 = 0x3f99999a;
  local_c = 0x3f99999a;
  local_10 = 0xbf99999a;
  iVar1 = FUN_00408d57(0x3f99999a,0xbf99999a,0x3f99999a,param_1,param_2,param_3,in_stack_00000020,
                       0x3e000000);
  FUN_004088b5(0x40400000);
  pfVar3 = &local_8;
  local_8 = 1.0 / in_stack_0000001c;
  puVar2 = &local_14;
  FUN_004021a7(local_20,iVar1 + 0x84);
  puVar2 = (undefined4 *)FUN_00402227(puVar2,pfVar3);
  *(undefined4 *)(iVar1 + 0x9c) = *puVar2;
  *(undefined4 *)(iVar1 + 0xa0) = puVar2[1];
  *(undefined4 *)(iVar1 + 0xa4) = puVar2[2];
  in_stack_0000001c = DAT_004536e0 * in_stack_0000001c;
  *(undefined4 *)(iVar1 + 0xc0) = 6;
  *(undefined4 *)(iVar1 + 0xc4) = 0x3c23d70a;
  *(float *)(iVar1 + 0xa0) = *(float *)(iVar1 + 0xa0) - in_stack_0000001c * 0.5;
  *(undefined4 *)(iVar1 + 0x90) = 0x3dcccccd;
  *(undefined4 *)(iVar1 + 0x94) = 0x3dcccccd;
  *(undefined4 *)(iVar1 + 0x98) = 0x3dcccccd;
  return;
}



// ==== 0x41041d ====

int * FUN_0041041d(float *param_1,float *param_2)

{
  float fVar1;
  float *pfVar2;
  int *in_ECX;
  float10 fVar3;
  double dVar4;
  float local_20;
  float local_1c;
  float local_18;
  int *local_14;
  int *local_10;
  float local_c;
  int *local_8;
  
  pfVar2 = param_2;
  local_10 = (int *)0x0;
  local_c = 1e+36;
  local_8 = &DAT_00c06b60;
  local_14 = in_ECX;
  if (&DAT_00c06b60 < PTR_DAT_00453858) {
    do {
      if (local_8 != local_14) {
        FUN_004021a7(&local_20,*local_14 + 0x84);
        fVar1 = -(local_20 * *param_1 + local_18 * param_1[2] + local_1c * param_1[1]);
        dVar4 = _fabs((double)(local_20 * *pfVar2 + local_18 * pfVar2[2] + local_1c * pfVar2[1]));
        param_2 = (float *)((float)dVar4 * 4.0);
        if ((float)dVar4 * 4.0 < fVar1) {
          param_2 = (float *)fVar1;
        }
        fVar3 = (float10)FUN_0041d134();
        if (fVar3 + (float10)(float)param_2 < (float10)local_c) {
          local_c = (float)(fVar3 + (float10)(float)param_2);
          local_10 = local_8;
        }
      }
      local_8 = local_8 + 0x1cc;
    } while (local_8 < PTR_DAT_00453858);
  }
  return local_10;
}



// ==== 0x410527 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410527(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_58;
  float fStack_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  float local_10;
  int local_c;
  int local_8;
  
  _memset(&DAT_00521e00,0,0xf400);
  local_1c = 0.0;
  DAT_00561404 = &DAT_00521e00;
  local_14 = 0;
  local_18 = -4.0;
  local_28 = 0x43340000;
  local_24 = -3.0;
  local_20 = 0x43340000;
  PTR_DAT_00453858 = (undefined *)&DAT_00c06b60;
  DAT_00561408 = &DAT_00746c30;
  FUN_00408d57(0x43340000,0xc0400000,0x43340000,0,0xc0800000,0,1,0x3d000000);
  FUN_004089b4();
  local_28 = 0;
  local_24 = 2.0;
  local_20 = 0;
  puVar2 = (undefined4 *)FUN_00402279(&local_58,0x41f80000,0xc0400000,0x41f80000);
  piVar3 = (int *)FUN_00408d57(*puVar2,puVar2[1],puVar2[2],local_28,local_24,local_20,param_1,
                               0x3d800000);
  iVar4 = 0;
  do {
    iVar1 = iVar4 + *piVar3;
    if (*(float *)(iVar1 + 4) < 0.0) {
      *(float *)(iVar1 + 8) = *(float *)(iVar1 + 8) * 1.1548387;
    }
    iVar4 = iVar4 + 0x10;
  } while (iVar4 < 0x80);
  FUN_00408e51(1);
  FUN_00408b34();
  FUN_004089b4();
  local_c = 0;
  local_40 = 0;
  local_18 = 3.0;
  local_38 = 0;
  local_14 = 0x42580000;
  local_34 = 0x41000000;
  local_30 = 0xc0800000;
  local_28 = 0;
  local_2c = 0x3f000000;
  local_20 = 0;
  do {
    local_8 = 0;
    fStack_54 = (float)local_c * 1.5707964;
    local_58 = local_28;
    uStack_50 = local_20;
    local_24 = fStack_54;
    local_10 = fStack_54;
    do {
      local_1c = ((float)local_8 - 2.5) * 18.0;
      iVar4 = FUN_00408d57(local_34,local_30,local_2c,local_1c,local_18,local_14,param_1,0x3d800000)
      ;
      local_3c = local_10;
      local_4c = local_40;
      fStack_48 = local_10;
      uStack_44 = local_38;
      FUN_0040927f(&local_4c);
      FUN_00402ea2(&local_58);
      FUN_004089b4();
      *(undefined4 *)(iVar4 + 0x54) = 0x42200000;
      *(undefined4 *)(iVar4 + 0xa8) = 0x40400000;
      *(undefined4 *)(iVar4 + 0xc0) = 2;
      *(undefined4 *)(iVar4 + 0xc4) = 0x3f19999a;
      if ((((DAT_00c06b50 == 10) && (local_c == 2)) && (local_8 == 4)) && (DAT_004eac7c == 0)) {
        *(undefined4 *)(iVar4 + 0xbc) = 6;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 6);
    local_c = local_c + 1;
  } while (local_c < 4);
  local_8 = 0;
  local_3c = 5.0;
  local_40 = 0;
  local_34 = 0x40266666;
  local_30 = 0xbe4ccccd;
  local_2c = 0x3ee66666;
  local_38 = _DAT_0045385c;
  local_28 = 0;
  local_20 = 0;
  local_1c = 0.0;
  local_14 = 0;
  do {
    FUN_00408d57(local_34,local_30,local_2c,local_40,local_3c,local_38,param_1,0x3e000000);
    fStack_54 = (float)local_8 * 0.2026834;
    local_58 = local_28;
    uStack_50 = local_20;
    local_24 = fStack_54;
    local_10 = fStack_54;
    FUN_0040927f(&local_58);
    local_18 = local_10;
    local_4c = local_1c;
    fStack_48 = local_10;
    uStack_44 = local_14;
    FUN_00402ea2(&local_4c);
    FUN_004024da(0xbf490fdb);
    FUN_004089b4();
    local_8 = local_8 + 1;
  } while (local_8 < 0x1f);
  _DAT_00c06808 = 0x42200000;
  if (DAT_00d0f9f8 != 0) {
    _DAT_00c06808 = 0x43480000;
  }
  return;
}



// ==== 0x410885 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410885(void)

{
  int iVar1;
  float fVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  undefined4 local_64 [5];
  float fStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  undefined4 *local_10;
  int local_c;
  bool local_5;
  
  iVar5 = DAT_004eac80;
  iVar1 = DAT_004535f8;
  local_c = DAT_004535f8;
  local_1c = DAT_004eac80;
  if (DAT_00c06980 != 0) {
    DAT_00c06b28 = 0;
    DAT_00c06b2c = 0;
  }
  DAT_00c06b40 = 0xffffffff;
  DAT_00c06b44 = 0xffffffff;
  _DAT_00c06b48 = 0xffffffff;
  _DAT_00c06b4c = 0xffffffff;
  DAT_00c06b3c = DAT_004535f8;
  FUN_0040d4c8();
  DAT_00c06978 = 0;
  local_18 = &DAT_00c06b60;
  local_20 = 0.0;
  if (0 < iVar1) {
    local_14 = -2 - iVar5;
    local_30 = 0;
    local_24 = (float)local_c;
    local_2c = 0x40a00000;
    local_28 = 0xc1700000;
    local_64[0] = 2;
    local_64[1] = 3;
    local_64[2] = 1;
    local_64[3] = 9;
    local_3c = 0;
    local_10 = &DAT_00467b50;
    local_34 = 0;
    do {
      fVar2 = local_20;
      local_48 = local_30;
      uStack_44 = local_2c;
      uStack_40 = local_28;
      fStack_50 = ((float)(int)local_20 / local_24) * 6.2831855;
      local_64[4] = local_3c;
      uStack_4c = local_34;
      local_38 = fStack_50;
      local_20 = fStack_50;
      FUN_00402ea2(local_64 + 4);
      puVar3 = local_18;
      iVar1 = local_1c;
      if ((int)fVar2 < local_1c) {
        uVar4 = (int)fVar2 + local_1c;
        if (local_c <= (int)uVar4) {
          uVar4 = local_c - 1;
        }
      }
      else {
        uVar4 = 0;
      }
      if (((local_c == 4) && (uVar4 = local_14 + (int)fVar2 + local_1c & 3, local_1c == 1)) &&
         (0x467b50 < (int)local_10)) {
        uVar4 = 0;
      }
      local_5 = false;
      if (DAT_004eac70 == 0) {
LAB_004109f8:
        FUN_0040ec0d(&local_48,-local_20,local_64[(int)fVar2],&DAT_00c06b60 + uVar4 * 0x1cc);
        bVar6 = DAT_00c06b50 == 0xb;
        puVar3[0x50] = 4;
        if (bVar6) {
          puVar3[0x50] = 0;
        }
        if ((int)fVar2 < iVar1) {
          puVar3[0x1bf] = fVar2;
        }
        else {
          puVar3[0x1bf] = 2;
        }
        local_18 = puVar3 + 0x1cc;
      }
      else {
        if ((int)fVar2 < DAT_004e7bb0) {
          local_48 = *local_10;
          local_20 = -(float)(&DAT_004e7bb4)[(int)fVar2];
          uStack_44 = local_10[1];
          uStack_40 = local_10[2];
        }
        else {
          local_5 = true;
        }
        local_5 = (int)fVar2 >= DAT_004e7bb0;
        iVar5 = (int)uVar4 % DAT_004e7bb0;
        if ((float)iVar5 == fVar2) {
          iVar5 = (iVar5 + 1) % DAT_004e7bb0;
        }
        uVar4 = iVar5 % local_c;
        if (!local_5) goto LAB_004109f8;
      }
      local_10 = local_10 + 3;
      local_20 = (float)((int)fVar2 + 1);
    } while ((int)local_20 < local_c);
  }
  PTR_DAT_00453858 = (undefined *)local_18;
  DAT_00453cd8 = 0x78;
  return;
}



// ==== 0x410a7e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410a7e(void)

{
  undefined4 uVar1;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_004169a7(0);
  _DAT_00511dfc = 4;
  FUN_00407d7a(6);
  local_10 = 0x42200000;
  local_c = 0x420c0000;
  local_8 = 0xc2c80000;
  local_1c = 0x42200000;
  uStack_18 = 0x420c0000;
  uStack_14 = 0xc2c80000;
  FUN_00402827(&local_1c,0,0);
  FUN_00407db4();
  FUN_0040b685(0x59a,0x191f);
  DAT_00c06b50 = 0;
  if ((DAT_004535f8 == 1) && (DAT_004eac80 == 0)) {
    DAT_00c06b50 = 0xb;
    FUN_004169a7(1);
  }
  if (DAT_004eac70 == 0) {
    DAT_00453860 = 0;
    FUN_00410527(0);
  }
  else {
    uVar1 = FUN_00403fa8(DAT_004eac70);
    FUN_00406c59(uVar1);
    if ((DAT_004535f8 == 1) && (DAT_004eac80 == 0)) {
      DAT_00c06b50 = 0xb;
    }
  }
  FUN_00410885();
  thunk_FUN_00408c36();
  return;
}



// ==== 0x410b60 ====

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410b60(int *param_1)

{
  float fVar1;
  int *piVar2;
  undefined4 uVar3;
  float *pfVar4;
  float fVar5;
  float *pfVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  int *in_ECX;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  bool bVar14;
  float10 fVar15;
  double dVar16;
  float *pfVar17;
  undefined1 *puVar18;
  undefined1 *puVar19;
  float **ppfVar20;
  int **ppiVar21;
  int **ppiVar22;
  float fVar23;
  float **ppfVar24;
  undefined1 local_560 [12];
  undefined1 local_554 [12];
  undefined1 local_548 [12];
  undefined1 local_53c [12];
  undefined1 local_530 [12];
  undefined1 local_524 [12];
  undefined1 local_518 [12];
  undefined1 local_50c [12];
  undefined1 local_500 [12];
  undefined1 local_4f4 [12];
  undefined1 local_4e8 [12];
  undefined1 local_4dc [12];
  undefined1 local_4d0 [12];
  undefined1 local_4c4 [12];
  undefined1 local_4b8 [12];
  undefined1 local_4ac [12];
  undefined1 local_4a0 [12];
  undefined1 local_494 [12];
  undefined1 local_488 [12];
  undefined1 local_47c [12];
  undefined1 local_470 [12];
  undefined1 local_464 [12];
  undefined1 local_458 [12];
  undefined1 local_44c [12];
  undefined1 local_440 [12];
  undefined1 local_434 [12];
  undefined1 local_428 [12];
  undefined1 local_41c [12];
  undefined1 local_410 [12];
  undefined1 local_404 [12];
  undefined1 local_3f8 [12];
  undefined1 local_3ec [12];
  undefined1 local_3e0 [12];
  undefined1 local_3d4 [12];
  undefined1 local_3c8 [12];
  undefined1 local_3bc [12];
  undefined1 local_3b0 [12];
  undefined1 local_3a4 [12];
  undefined1 local_398 [12];
  undefined1 local_38c [12];
  undefined1 local_380 [12];
  undefined1 local_374 [12];
  undefined1 local_368 [12];
  undefined1 local_35c [12];
  undefined1 local_350 [12];
  undefined1 local_344 [12];
  undefined1 local_338 [12];
  undefined1 local_32c [12];
  undefined1 local_320 [12];
  undefined1 local_314 [12];
  undefined1 local_308 [12];
  undefined1 local_2fc [12];
  undefined1 local_2f0 [12];
  undefined1 local_2e4 [12];
  undefined1 local_2d8 [12];
  undefined1 local_2cc [12];
  undefined1 local_2c0 [12];
  undefined1 local_2b4 [12];
  undefined1 local_2a8 [12];
  undefined1 local_29c [12];
  undefined1 local_290 [12];
  undefined1 local_284 [12];
  undefined1 local_278 [12];
  undefined1 local_26c [12];
  undefined1 local_260 [12];
  undefined1 local_254 [12];
  undefined1 local_248 [12];
  undefined1 local_23c [12];
  undefined1 local_230 [12];
  undefined1 local_224 [12];
  undefined1 local_218 [12];
  undefined1 local_20c [12];
  undefined1 local_200 [12];
  undefined1 local_1f4 [12];
  undefined1 local_1e8 [12];
  undefined1 local_1dc [12];
  float local_1d0;
  float fStack_1cc;
  float local_1c8;
  undefined4 local_1ac;
  undefined4 uStack_1a8;
  float local_1a4;
  undefined1 local_1a0 [12];
  undefined1 local_194 [12];
  float local_188 [6];
  int local_170 [4];
  int iStack_160;
  int iStack_15c;
  float local_158 [4];
  int *local_148;
  float local_144 [4];
  float local_134 [7];
  int *local_118;
  float local_114;
  float *local_110;
  int *local_10c;
  float fStack_108;
  float fStack_104;
  undefined4 local_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  char local_a5;
  float local_a4;
  float fStack_a0;
  float fStack_9c;
  float *local_98;
  int *local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  char local_7d;
  float *local_7c;
  int *local_78;
  float fStack_74;
  float fStack_70;
  uint local_6c;
  int *local_68;
  float local_64;
  float local_60;
  float local_5c;
  int *local_58;
  float local_54;
  float *local_50;
  int *local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  char local_25;
  int *local_24;
  float local_20;
  float *local_1c;
  int *local_18;
  float *local_14;
  float *local_10;
  int *local_c;
  float *local_8;
  
  local_88 = 0.0;
  local_98 = (float *)0x0;
  FUN_0040e7c8(&local_94);
  FUN_0040e8f0(&local_3c);
  FUN_0040e98c(&local_e8,&local_94,&local_3c);
  in_ECX[0x32] = (int)local_94;
  in_ECX[0x33] = (int)local_90;
  in_ECX[0x34] = (int)local_8c;
  local_58 = (int *)0x1;
  if (1 < ((int)param_1 - (int)in_ECX) / 0x730) {
    local_58 = (int *)0x2;
  }
  if (param_1 == (int *)0x0) {
    param_1 = in_ECX;
  }
  if (DAT_00c06b58 < DAT_00c06978 + -0x32) {
    local_54 = 0.0;
    do {
      if ((((DAT_00c06978 + -1 <= *(int *)(in_ECX[(int)local_54] + 0xd8)) &&
           (local_54 != 4.2039e-45)) && (local_54 != 8.40779e-45)) &&
         (((local_54 != 5.60519e-45 && (local_54 != 9.80909e-45)) && (DAT_00c06b50 != 0)))) {
        if (in_ECX[0x1c4] == 0) {
          in_ECX[0x1c4] = 1;
          DAT_00c06b3c = DAT_00c06b3c + -1;
          bVar14 = DAT_00c06b3c == 1;
          (&DAT_00c06b40)[DAT_00c06b3c] = (int)(in_ECX + -0x301ad8) / 0x730;
          if (bVar14) {
            DAT_00c06b5c = 0;
            DAT_00c06b50 = 2;
          }
        }
        in_ECX[0x50] = 5;
        param_1[0x50] = 5;
      }
      local_54 = (float)((int)local_54 + 1);
    } while ((int)local_54 < 0xf);
    if ((DAT_00c06b50 == 2) && (in_ECX[0x1c4] == 0)) {
      DAT_00c06b40 = (int)(in_ECX + -0x301ad8) / 0x730;
    }
  }
  DAT_00c06b5c = DAT_00c06b5c + 1;
  local_24 = (int *)0x3f800000;
  local_20 = 0.0;
  local_1c = (float *)0x0;
  local_78 = (int *)0x3f800000;
  fStack_74 = 0.0;
  fStack_70 = 0.0;
  FUN_004023c6(&local_cc,*in_ECX + 0x60);
  local_c8 = 0.0;
  FUN_004022c1();
  local_24 = (int *)0x0;
  local_20 = 1.0;
  local_1c = (float *)0x0;
  local_78 = (int *)0x0;
  fStack_74 = 1.0;
  fStack_70 = 0.0;
  FUN_004021dc(&local_b4,&local_78);
  if ((0x168 < DAT_00c06978 - DAT_00c06b58) &&
     (piVar2 = (int *)FUN_0041041d(&local_b4,&local_cc), piVar2 != (int *)0x0)) {
    in_ECX[0x1c0] = (int)piVar2;
    param_1 = piVar2;
  }
  iVar10 = in_ECX[0x1bf];
  local_6c = 0;
  if (-1 < iVar10) {
    if (iVar10 < 2) {
      local_6c = FUN_0040fe9b();
    }
    else if (iVar10 == 2) {
      local_6c = FUN_0040ff4c(param_1);
    }
  }
  iVar10 = DAT_00c06b50;
  if (DAT_00c0682c == 1) {
    if ((in_ECX[0x1bf] == 2) && (DAT_00c06b50 != 1)) {
      local_6c = FUN_0040fe9b();
    }
  }
  else {
    iVar11 = in_ECX[0x50];
    if (((iVar11 != 0) && (iVar11 != 3)) && (iVar11 != 5)) {
      local_6c = local_6c & 8;
    }
  }
  if (((DAT_00c06b5c < 200) && (iVar10 == 2)) ||
     ((param_1 != (int *)0x0 && ((param_1[0x29] == 3 && (iVar10 == 0)))))) {
    ppiVar21 = &local_94;
    pfVar4 = &local_dc;
    FUN_0040e7c8(&local_a4);
    FUN_004021a7(pfVar4,ppiVar21);
    local_d8 = 0.0;
    local_40 = 0.0;
    if ((local_d4 * local_d4 + local_dc * local_dc < 1600.0) &&
       (fVar15 = (float10)FUN_004022a2(), (float10)0.16000001 < fVar15)) {
      local_40 = 3.5;
    }
    ppfVar24 = &local_50;
    local_50 = (float *)(local_40 * 0.04000002);
    pfVar4 = &local_a4;
    FUN_00402302(&local_100);
    uVar3 = FUN_00402227(pfVar4,ppfVar24);
    FUN_0040225a(uVar3);
  }
  local_14 = (float *)0x0;
  dVar16 = _fabs((double)(float)local_94);
  if ((((double)_DAT_0045385c - 5.0 < dVar16) &&
      (dVar16 = _fabs((double)(float)local_94), dVar16 < (double)_DAT_0045385c + 18.0)) ||
     ((dVar16 = _fabs((double)local_8c), (double)_DAT_0045385c - 5.0 < dVar16 &&
      (dVar16 = _fabs((double)local_8c), dVar16 < (double)_DAT_0045385c + 18.0)))) {
    local_14 = (float *)0x3fc00000;
  }
  if ((((DAT_00c06b50 == 2) && (300 < DAT_00c06b5c)) &&
      (fVar15 = (float10)FUN_004022a2(), (float10)0.64000005 < fVar15)) &&
     ((in_ECX[0x29] != 0xc && (in_ECX[0x29] != 0xd)))) {
    local_14 = (float *)0x3f19999a;
  }
  local_4c = local_94;
  local_44 = local_8c;
  local_48 = 0.0;
  if ((DAT_00d0f9f8 == 0) && (DAT_004eac70 == 0)) {
    ppfVar24 = &local_50;
    pfVar4 = &local_a4;
    ppfVar20 = &local_14;
    puVar8 = &local_100;
    local_50 = (float *)0x3d23d710;
    FUN_00402302(&local_10c);
    FUN_00402227(puVar8,ppfVar20);
    uVar3 = FUN_00402227(pfVar4,ppfVar24);
    FUN_0040225a(uVar3);
  }
  local_148 = in_ECX + 0x5f;
  local_54 = 0.1;
  iVar10 = 0;
  piVar2 = local_148;
  do {
    iVar11 = 0x3dcccccd;
    if (7 < iVar10) {
      iVar11 = 0x3ca3d70a;
    }
    *piVar2 = iVar11;
    iVar10 = iVar10 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar10 < 0xe);
  in_ECX[0xe1] = 0x3ca3d70a;
  local_20 = -1e-05;
  in_ECX[0x108] = 0x3ca3d70a;
  local_24 = (int *)0x0;
  local_1c = (float *)0x0;
  local_78 = (int *)0x0;
  fStack_74 = -1e-05;
  in_ECX[0x6c] = 0x3b449ba6;
  fStack_70 = 0.0;
  pfVar4 = (float *)FUN_004021dc(&local_a4,&local_78);
  local_3c = local_3c + *pfVar4;
  local_38 = local_38 + pfVar4[1];
  local_34 = local_34 + pfVar4[2];
  local_84 = 0.0;
  if ((local_6c & 4) != 0) {
    local_50 = (float *)0x3d031273;
    uVar3 = FUN_00402227(&local_a4,&local_50);
    FUN_0040225a(uVar3);
  }
  fVar5 = 0.0;
  if ((local_6c & 1) != 0) {
    fVar5 = 0.06;
  }
  if ((local_6c & 2) != 0) {
    fVar5 = fVar5 - 0.06;
  }
  iVar10 = in_ECX[0x29];
  pfVar4 = (float *)(in_ECX + 0x1c1);
  local_7d = '\0';
  local_25 = '\0';
  local_50 = (float *)((fVar5 - *pfVar4) * 0.1 + *pfVar4);
  *pfVar4 = (float)local_50;
  local_134[0] = 0.0;
  local_134[3] = 0.0;
  local_158[0] = 1.5;
  local_158[3] = 1.5;
  local_144[0] = 0.2;
  local_144[3] = 0.2;
  if ((iVar10 == 3) && (in_ECX[0x50] < 5)) {
    in_ECX[0x50] = 0;
  }
  local_d0 = 0.0;
  switch(in_ECX[0x50]) {
  case 0:
    break;
  case 1:
    local_5c = (float)in_ECX[0x51];
    local_6c = 0;
    local_25 = '\x01';
    local_18 = (int *)((float)(int)local_5c * 0.016666668);
    if (0x3c < (int)local_5c) {
      local_18 = (int *)0x3f800000;
    }
    if ((local_5c == 9.80909e-44) || (local_5c == 5.60519e-45)) {
      fStack_74 = (float)in_ECX[0x3c];
      local_1c = (float *)0x0;
      local_24 = (int *)0x3fa66666;
      local_78 = (int *)0x3fa66666;
      fStack_70 = 0.0;
      local_20 = fStack_74;
      FUN_004021a7(&local_a4,&local_78);
      fVar15 = (float10)FUN_004022a2();
      if ((float10)0.16000001 < fVar15) {
        local_7d = '\x01';
      }
    }
    if (local_5c == 1.12104e-43) {
      in_ECX[0x51] = 0;
      in_ECX[0x4c] = 3;
      in_ECX[0x50] = 2;
    }
    fVar5 = (float)local_18 * (float)local_18 * (float)local_18;
    local_84 = ((float)local_18 * (float)local_18 * 3.0 - (fVar5 + fVar5)) * 1.2;
    local_8 = (float *)((1.0 - (float)local_18) * (float)local_18 * 0.4);
    pfVar4 = (float *)FUN_00402227(&local_100,&local_8);
    local_94 = (int *)((float)local_94 - *pfVar4);
    local_90 = local_90 - pfVar4[1];
    local_8c = local_8c - pfVar4[2];
    if (in_ECX[0x29] == 0) break;
    iVar10 = in_ECX[0x51];
    if (0x5a < iVar10) {
      in_ECX[0x51] = 0x5a;
      goto switchD_00411120_default;
    }
    if (iVar10 < 1) goto switchD_00411120_default;
    iVar10 = iVar10 + -1;
    goto LAB_00411288;
  case 2:
    local_5c = (float)in_ECX[0x51];
    local_25 = '\x01';
    local_40 = (float)(int)local_5c * 0.011111111;
    if (0x5a < (int)local_5c) {
      local_40 = 1.0;
    }
    in_ECX[0x51] = (int)local_5c + 1;
    fVar5 = local_40 * local_40 * local_40;
    local_84 = 1.25;
    local_8 = (float *)0xbc8b4396;
    local_88 = local_40 * local_40 * 3.0 - (fVar5 + fVar5);
    local_54 = local_88 * 0.7;
    local_88 = local_88 * 1.1;
    pfVar4 = (float *)FUN_00402227(&local_10c,&local_8);
    local_24 = (int *)0xbdcccccd;
    local_3c = local_3c + *pfVar4;
    local_38 = local_38 + pfVar4[1];
    local_34 = local_34 + pfVar4[2];
    local_20 = 0.0;
    local_1c = (float *)0x3f800000;
    local_1d0 = -0.1;
    fStack_1cc = 0.0;
    local_1c8 = 1.0;
    FUN_004022c1();
    local_24 = (int *)0x3dcccccd;
    local_20 = 0.0;
    local_1c = (float *)0x3f800000;
    local_1ac = 0x3dcccccd;
    uStack_1a8 = 0;
    local_1a4 = 1.0;
    FUN_004022c1();
    local_158[0] = 0.0;
    local_158[3] = 0.0;
    fVar5 = 0.0;
    if (((local_6c & 8) != 0) || (700 < in_ECX[0x51])) {
      fVar5 = 1.0;
    }
    if (DAT_00c06b50 == 1) {
      in_ECX[0x4c] = 0;
      in_ECX[0x51] = 0;
      in_ECX[0x50] = 3;
    }
    iVar10 = DAT_00c06978 + -0x14;
    if (((iVar10 < *(int *)(in_ECX[0xb] + 0xd4)) || (iVar10 < *(int *)(in_ECX[0xe] + 0xd8))) &&
       ((iVar10 < *(int *)(param_1[0xb] + 0xd8) || (iVar10 < *(int *)(param_1[0xe] + 0xd8))))) {
      DAT_00c06b50 = 1;
      DAT_00c06b58 = DAT_00c06978;
    }
    pfVar4 = (float *)(in_ECX + 0x52);
    local_6c = 0;
    fVar5 = (fVar5 - *pfVar4) * 0.16 + *pfVar4;
    *pfVar4 = fVar5;
    local_144[0] = (1.0 - fVar5 * fVar5 * fVar5 * fVar5) * 1.5;
    local_134[0] = local_40 * 0.6;
    local_144[3] = local_144[0];
    local_134[3] = local_134[0];
    goto switchD_00411120_default;
  case 3:
    local_6c = local_6c & 0xfffffff7;
    local_8 = (float *)0x0;
    pfVar4 = (float *)FUN_00402227(local_134 + 4,&local_8);
    local_3c = local_3c - *pfVar4;
    local_38 = local_38 - pfVar4[1];
    local_34 = local_34 - pfVar4[2];
    fVar5 = (float)in_ECX[0x51];
    fVar23 = (float)(int)fVar5 * 0.015384615;
    if (0x41 < (int)fVar5) {
      in_ECX[0x50] = 0;
      fVar23 = 1.0;
    }
    fVar1 = fVar23 * fVar23 * fVar23;
    local_88 = 1.0 - (fVar23 * fVar23 * 3.0 - (fVar1 + fVar1));
    local_84 = local_88 * 1.2;
    local_54 = local_88 * 0.7;
    local_88 = local_88 * 1.1;
    local_5c = fVar5;
    goto LAB_004115ec;
  case 4:
    local_6c = 0;
    fVar15 = (float10)FUN_004022a2();
    piVar2 = in_ECX + 0x51;
    if ((float10)0.36 <= fVar15) {
LAB_00411158:
      *piVar2 = 0;
    }
    else if (100 < *piVar2) {
      in_ECX[0x50] = 1;
      goto LAB_00411158;
    }
    *piVar2 = *piVar2 + 1;
    goto switchD_00411120_default;
  case 5:
    fVar15 = (float10)FUN_004022a2();
    if (((float10)0.36 <= fVar15) || (iVar10 != 0)) {
      in_ECX[0x51] = 0;
    }
    if (((100 < in_ECX[0x51]) &&
        (((iVar10 = param_1[0x51], 100 < iVar10 || ((iVar10 < -10 && (-200 < iVar10)))) &&
         (param_1[0x50] != 7)))) || (param_1[0x50] == 6)) {
      in_ECX[0x51] = 0;
      in_ECX[0x50] = 6;
    }
    if (700 < in_ECX[0x51]) {
      in_ECX[0x51] = 0;
      in_ECX[0x50] = 7;
    }
    break;
  case 6:
    fVar15 = (float10)FUN_0041cd94((double)((float)in_ECX[0x51] * 0.007142857 * 6.2831855));
    fVar5 = (float)in_ECX[0x51];
    fVar15 = ((float10)1.0 - fVar15) * (float10)0.4;
    local_88 = (float)fVar15;
    in_ECX[0x35] = (int)(float)((float10)1.5 * fVar15);
    local_98 = (float *)(float)(fVar15 * (float10)-1.0);
    if (0x8c < (int)fVar5) {
      in_ECX[0x50] = 0;
      local_88 = 0.0;
      in_ECX[0x35] = 0;
    }
LAB_004115ec:
    iVar10 = (int)fVar5 + 1;
LAB_00411288:
    in_ECX[0x51] = iVar10;
    goto switchD_00411120_default;
  case 7:
    fVar15 = (float10)FUN_0041d084((double)((float)in_ECX[0x51] * 0.007142857 * 12.566371));
    fVar15 = fVar15 * (float10)-0.5;
    local_88 = (float)fVar15;
    in_ECX[0x35] = (int)(float)((float10)1.8 * fVar15);
    local_98 = (float *)(float)(fVar15 * (float10)-1.0);
    if (0x8c < in_ECX[0x51]) {
      in_ECX[0x50] = 5;
      local_88 = 0.0;
      in_ECX[0x51] = -500;
      in_ECX[0x35] = 0;
    }
    break;
  case 8:
    fVar15 = (float10)FUN_0041cd94((double)((float)in_ECX[0x51] * 0.013333334 * 25.132742));
    fVar15 = (fVar15 - (float10)1.0) * (float10)-0.15;
    local_84 = (float)fVar15;
    in_ECX[0x35] = (int)(float)-fVar15;
    local_98 = (float *)(float)((fVar15 - (float10)0.15) + (fVar15 - (float10)0.15));
    if (0x4b < in_ECX[0x51]) {
      in_ECX[0x50] = 5;
      if ((DAT_00c06b50 == 0xb) || (DAT_00d0f9f8 != 0)) {
        in_ECX[0x50] = 0;
      }
      in_ECX[0x51] = -200;
      in_ECX[0x35] = 0;
      local_84 = 0.0;
    }
    break;
  default:
    goto switchD_00411120_default;
  }
  in_ECX[0x51] = in_ECX[0x51] + 1;
switchD_00411120_default:
  do {
    iVar10 = in_ECX[0x4c];
    local_a5 = '\0';
    if (iVar10 != 0) {
      if (iVar10 == 1) {
        in_ECX[199] = 0x3e0f5c29;
        in_ECX[0xd4] = 0x3e0f5c29;
        in_ECX[0xee] = 0x3e0f5c29;
        in_ECX[0xfb] = 0x3e0f5c29;
        local_d0 = 0.5;
        local_2c = -1.3;
        FUN_004021a7(&local_4c,in_ECX[1] + 0x84);
        local_48 = 0.0;
        FUN_004022c1();
        if (DAT_00c06978 + -10 < *(int *)(in_ECX[0xe] + 0xd4)) {
          local_2c = -2.0;
        }
        if (DAT_00c06978 + -10 < *(int *)(in_ECX[0xb] + 0xd4)) {
          local_2c = local_2c - 0.7;
        }
        pfVar4 = (float *)FUN_00402227(&local_10c,&local_2c);
        local_94 = (int *)((float)local_94 + *pfVar4);
        local_90 = local_90 + pfVar4[1];
        local_8c = local_8c + pfVar4[2];
        iVar10 = in_ECX[0x4d];
        fVar5 = (float)(iVar10 + -8) * 0.033333335;
        if (iVar10 < 8) {
          fVar5 = 0.0;
        }
        if (0x26 < iVar10) {
          fVar5 = 1.0;
          if (0x2b < iVar10) {
            in_ECX[0x4c] = 0;
            in_ECX[0x4d] = 0;
            fVar5 = 1.0;
          }
        }
        local_10 = (float *)(param_1[1] + 0x84);
        local_2c = 0.0;
        local_14 = local_188;
        local_88 = fVar5 * fVar5 * 0.4 + local_88;
        local_8 = (float *)(fVar5 * 0.3 + 0.7);
        fVar5 = 1.0 - fVar5 * fVar5;
        local_40 = -4.0;
        local_c = (int *)(fVar5 * 2.7);
        local_24 = (int *)0x0;
        fStack_74 = 2.0 - fVar5 * 4.0;
        local_1c = (float *)0x0;
        local_78 = (int *)0x0;
        fStack_70 = 0.0;
        local_20 = fStack_74;
        do {
          fVar5 = local_2c;
          *(float **)((int)local_134 + (int)local_2c) = local_8;
          *(int **)((int)local_144 + (int)fVar5) = local_c;
          *(undefined4 *)((int)local_158 + (int)fVar5) = 0x3fc00000;
          uVar3 = FUN_00402227(local_134 + 4,&local_40);
          pfVar4 = &local_f4;
          FUN_00402172(local_134 + 7,&local_78);
          pfVar7 = (float *)FUN_00402172(pfVar4,uVar3);
          pfVar6 = local_14;
          fVar5 = (float)((int)local_2c + 0xc);
          pfVar4 = local_14 + 1;
          local_2c = fVar5;
          pfVar17 = local_14 + 9;
          *local_14 = *pfVar7;
          local_14 = pfVar17;
          *pfVar4 = pfVar7[1];
          pfVar6[2] = pfVar7[2];
        } while ((int)fVar5 < 0xd);
        in_ECX[0x4d] = in_ECX[0x4d] + 1;
      }
      else if (iVar10 == 2) {
        local_14 = (float *)(in_ECX[0x4e] * 3);
        in_ECX[199] = 0x3d75c28f;
        in_ECX[0xd4] = 0x3d75c28f;
        in_ECX[0xee] = 0x3d75c28f;
        in_ECX[0xfb] = 0x3d75c28f;
        local_8 = (float *)0xbf333333;
        pfVar6 = (float *)FUN_00402227(&local_a4,&local_8);
        pfVar4 = local_14;
        local_94 = (int *)((float)local_94 + *pfVar6);
        local_90 = local_90 + pfVar6[1];
        local_8c = local_8c + pfVar6[2];
        local_c = (int *)in_ECX[0x4d];
        fVar5 = (float)(int)local_c * 0.05;
        if (0x14 < (int)local_c) {
          in_ECX[0x4c] = 0;
          in_ECX[0x4d] = 0;
          in_ECX[0x4f] = 10;
          local_a5 = '\x01';
        }
        local_10 = (float *)(fVar5 * fVar5);
        local_20 = -2.0;
        local_40 = 1.0 - fVar5;
        local_88 = local_40 * fVar5 * 0.1 + local_88;
        local_134[(int)local_14] = fVar5 * 0.3 + 0.7;
        local_144[(int)pfVar4] = (1.0 - (float)local_10) * 2.7;
        local_158[(int)pfVar4] = 1.3;
        local_24 = (int *)0x0;
        local_1c = (float *)0x0;
        local_78 = (int *)0x0;
        fStack_74 = local_20;
        fStack_70 = 0.0;
        FUN_00402172(&local_4c,&local_78);
        pfVar4 = local_14;
        iVar10 = in_ECX[0x4f];
        iVar11 = (int)local_14 * 3;
        local_188[(int)local_14 * 3] = (float)local_4c;
        local_188[iVar11 + 1] = local_48;
        local_188[(int)pfVar4 * 3 + 2] = local_44;
        if (200 < iVar10) {
          fVar5 = local_40 * 0.3;
          iVar10 = 3 - (int)local_14;
          local_188[iVar10 * 3] = (float)local_4c;
          local_134[iVar10] = fVar5 + 0.7;
          pfVar4 = local_10;
          local_188[iVar10 * 3 + 1] = local_48;
          local_144[iVar10] = (float)pfVar4 * 2.7;
          local_188[iVar10 * 3 + 2] = local_44;
          local_158[iVar10] = 1.3;
        }
        in_ECX[0x4d] = in_ECX[0x4d] + 1;
        goto LAB_0041192f;
      }
      break;
    }
    if ((local_6c & 0x10) != 0) {
      in_ECX[0x4d] = 0;
      in_ECX[0x4c] = 1;
    }
    if ((local_6c & 0x20) == 0) break;
    in_ECX[0x4d] = 0;
    in_ECX[0x4c] = 2;
    in_ECX[0x4e] = 1;
    pfVar4 = (float *)FUN_004021a7(&local_100,in_ECX[0xe] + 0x84);
    if (local_b4 * *pfVar4 + local_ac * pfVar4[2] + local_b0 * pfVar4[1] < 0.0) {
      in_ECX[0x4e] = 0;
    }
    if (in_ECX[0x4f] < 1) break;
    in_ECX[0x4f] = 1000;
LAB_0041192f:
  } while (local_a5 != '\0');
  in_ECX[0x4f] = in_ECX[0x4f] + -1;
  if (in_ECX[0x4c] != 3) {
    local_24 = (int *)0x40600000;
    local_1c = (float *)0x3f800000;
    local_20 = 2.4;
    local_78 = (int *)0x40600000;
    fStack_74 = 2.4;
    fStack_70 = 1.0;
    uVar3 = FUN_004023c6(&local_a4,in_ECX[1] + 0x60);
    uVar3 = FUN_00402172(&local_100,uVar3);
    uVar3 = FUN_004021a7(&local_10c,uVar3);
    pfVar4 = (float *)FUN_00402363(local_134 + 4,uVar3);
    local_1d0 = *pfVar4;
    fStack_1cc = pfVar4[1];
    local_1c8 = pfVar4[2];
    if (local_1c8 < 0.0) {
      local_1c8 = 0.0;
    }
    FUN_004022c1();
    local_24 = (int *)0xc0600000;
    local_1c = (float *)0x3f800000;
    local_20 = 2.4;
    local_78 = (int *)0xc0600000;
    fStack_74 = 2.4;
    fStack_70 = 1.0;
    uVar3 = FUN_004023c6(&local_a4,in_ECX[1] + 0x60);
    uVar3 = FUN_00402172(&local_100,uVar3);
    uVar3 = FUN_004021a7(&local_10c,uVar3);
    puVar8 = (undefined4 *)FUN_00402363(local_134 + 4,uVar3);
    local_1ac = *puVar8;
    uStack_1a8 = puVar8[1];
    local_1a4 = (float)puVar8[2];
    if (local_1a4 < 0.0) {
      local_1a4 = 0.0;
    }
    FUN_004022c1();
  }
  local_8 = (float *)0x3dcccccd;
  pfVar4 = (float *)FUN_00402227(&local_a4,&local_8);
  local_3c = local_3c - *pfVar4;
  local_38 = local_38 - pfVar4[1];
  local_34 = local_34 - pfVar4[2];
  in_ECX[0x40] = (int)((float)in_ECX[0x40] * 0.96);
  in_ECX[0x41] = (int)((float)in_ECX[0x41] * 0.96);
  in_ECX[0x42] = (int)((float)in_ECX[0x42] * 0.96);
  FUN_0040e7c8(&local_dc);
  local_d8 = 5.0;
  FUN_0040fdd0(&local_dc,0xff0000);
  local_40 = (float)in_ECX[0x3b];
  local_24 = (int *)0x0;
  local_1c = (float *)0xbecccccd;
  local_20 = 0.0;
  local_78 = (int *)0x0;
  fStack_74 = 0.0;
  fStack_70 = -0.4;
  local_c = (int *)in_ECX[0x13];
  uVar3 = FUN_004023c6(&local_a4,*local_c + 0x60);
  piVar2 = (int *)FUN_00402172(&local_100,uVar3);
  local_24 = (int *)0x0;
  local_170[0] = *piVar2;
  local_20 = 0.0;
  local_170[1] = piVar2[1];
  local_170[2] = piVar2[2];
  local_1c = (float *)0xbecccccd;
  local_78 = (int *)0x0;
  fStack_74 = 0.0;
  fStack_70 = -0.4;
  uVar3 = FUN_004023c6(&local_a4,*(int *)in_ECX[0x16] + 0x60);
  puVar8 = (undefined4 *)FUN_00402172(&local_10c,uVar3);
  local_8 = (float *)(1.0 - local_40);
  local_170[3] = *puVar8;
  iStack_160 = puVar8[1];
  iStack_15c = puVar8[2];
  ppfVar24 = &local_8;
  pfVar4 = local_134 + 4;
  local_78 = (int *)0x0;
  fStack_74 = -1.0;
  fStack_70 = 0.02;
  local_24 = (int *)0x0;
  local_20 = -1.0;
  local_1c = (float *)0x3ca3d70a;
  local_4c = (int *)0x0;
  local_48 = -1.0;
  local_44 = 0.02;
  uVar3 = FUN_004023c6(&local_a4,*(int *)in_ECX[0x16] + 0x60);
  FUN_00402172(&local_f4,uVar3);
  uVar3 = FUN_00402227(pfVar4,ppfVar24);
  pfVar4 = &local_c0;
  pfVar6 = &local_40;
  pfVar17 = local_134 + 7;
  uVar9 = FUN_004023c6(&local_68,*local_c + 0x60);
  FUN_00402172(local_230,uVar9);
  FUN_00402227(pfVar17,pfVar6);
  FUN_00402172(pfVar4,uVar3);
  local_dc = local_c0;
  local_d4 = local_b8;
  local_d8 = 5.0;
  FUN_0040fdd0(&local_dc,0xffff00);
  local_18 = (int *)(((float)in_ECX[0x27] - 0.5) + ((float)in_ECX[0x27] - 0.5));
  local_54 = local_54 -
             (local_b4 * (float)in_ECX[0x40] +
             local_ac * (float)in_ECX[0x42] + local_b0 * (float)in_ECX[0x41]) * 0.15;
  in_ECX[0x48] = 0;
  if ((((*(float *)(in_ECX[2] + 0x88) < local_bc + 9.3) && (iVar10 = in_ECX[0x29], iVar10 != 0xc))
      && (iVar10 != 0xd)) &&
     (((iVar10 != 0xe && (iVar10 != 3)) && (in_ECX[0x29] = 3, &DAT_00c06b60 < PTR_DAT_00453858)))) {
    piVar2 = &DAT_00c06b68;
    do {
      if ((((piVar2 + -2 != in_ECX) &&
           (((*(float *)(piVar2[4] + 0x88) + *(float *)(piVar2[1] + 0x88)) * 0.5 + 3.0 <
             *(float *)(*piVar2 + 0x88) ||
            ((DAT_00d0f9f8 != 0 && (*(float *)(*piVar2 + 0x88) < _DAT_00453cd4 - 1.0)))))) &&
          ((DAT_00c06b50 == 2 || (DAT_00d0f9f8 != 0)))) &&
         ((((piVar2[0x4e] == 5 || (piVar2[0x4e] == 7)) || (DAT_00d0f9f8 != 0)) &&
          (fVar15 = (float10)FUN_004022a2(), fVar15 < (float10)1.9599999)))) {
        FUN_0040ff13(piVar2 + -2,local_58);
      }
      piVar12 = piVar2 + 0x1ca;
      piVar2 = piVar2 + 0x1cc;
    } while (piVar12 < PTR_DAT_00453858);
  }
  iVar10 = 0xe;
  if (*(float *)(*in_ECX + 0x88) < _DAT_00453cd4 + 1.5) {
    in_ECX[0x29] = 0xe;
  }
  switch(in_ECX[0x29]) {
  case 0:
    in_ECX[0x3b] = 0x3f000000;
    if (DAT_00d0f3e3 != '\0') {
      in_ECX[0x3b] = 0x3f800000;
    }
    in_ECX[0x28] = in_ECX[0x28] + 1;
    in_ECX[0x20] = in_ECX[0x3c];
    in_ECX[0x23] = in_ECX[0x3c];
    local_8 = (float *)0x41980000;
    uVar3 = FUN_00402227(local_230,&local_8);
    uVar3 = FUN_00402172(local_4ac,uVar3);
    FUN_004021a7(&local_68,uVar3);
    local_8 = (float *)0x40400000;
    pfVar4 = (float *)FUN_00402227(local_428,&local_8);
    local_68 = (int *)((float)local_68 - *pfVar4);
    local_60 = local_60 - pfVar4[2];
    if (((0xfa < DAT_00c06978) || ((DAT_00d0f9f8 != 0 && (100 < DAT_00c06978)))) &&
       ((DAT_00c06978 + -0x1e < *(int *)(in_ECX[3] + 0xd4) ||
        (DAT_00c06978 + -0x1e < *(int *)(in_ECX[6] + 0xd4))))) {
      fVar5 = 0.9;
      if (DAT_00c06b50 == 2) {
        fVar5 = 1.5;
      }
      if ((fVar5 * fVar5 <
           local_60 * local_60 + (float)local_68 * (float)local_68 + -pfVar4[1] * -pfVar4[1]) &&
         (local_25 == '\0')) {
        local_8 = (float *)0x41200000;
        uVar3 = FUN_00402227(local_440,&local_8);
        uVar3 = FUN_00402172(local_458,uVar3);
        pfVar4 = (float *)FUN_004021a7(local_470,uVar3);
        local_68 = (int *)*pfVar4;
        local_64 = pfVar4[1];
        local_60 = pfVar4[2];
        local_14 = (float *)(local_60 * local_60 + (float)local_68 * (float)local_68);
        fVar15 = (float10)FUN_0041d134((double)(float)local_14);
        local_2c = (float)(fVar15 * (float10)1.5);
        if (fVar15 * (float10)1.5 < (float10)1.4) {
          local_2c = 1.4;
        }
        in_ECX[0x28] = 0;
        in_ECX[0x29] = 8;
        fVar15 = (float10)FUN_0041d134((double)(float)local_14);
        local_8 = (float *)(float)fVar15;
        fVar15 = (float10)FUN_0041d134((double)(float)local_14);
        local_58 = (int *)(local_cc * (float)local_68);
        local_10 = (float *)(local_c8 * 0.0);
        local_14 = (float *)(local_c4 * local_60);
        pfVar4 = (float *)FUN_00402279(local_488,
                                       (float)(((float10)(float)local_10 + (float10)(float)local_14
                                               + (float10)(float)local_58) *
                                              ((float10)local_2c / fVar15) * (float10)-0.6),0,
                                       -(local_2c / (float)local_8) *
                                       (local_b0 * 0.0 +
                                       local_60 * local_ac + (float)local_68 * local_b4));
        local_78 = (int *)*pfVar4;
        fStack_74 = pfVar4[1];
        fStack_70 = pfVar4[2];
        in_ECX[0x2f] = (int)local_78;
        in_ECX[0x30] = (int)fStack_74;
        in_ECX[0x31] = (int)fStack_70;
        fVar15 = (float10)FUN_004022a2();
        fVar15 = (float10)FUN_0041d134((double)fVar15);
        pfVar4 = (float *)(in_ECX + 0x1f);
        in_ECX[0x2a] = (int)(float)(fVar15 * (float10)0.8 + (float10)0.5);
        pfVar6 = (float *)FUN_004021a7(local_4a0,pfVar4);
        if (((float)in_ECX[0x27] - 0.5) * 0.0 + (float)local_10 + (float)local_14 + (float)local_58
            <= (float)in_ECX[0x2f] * *pfVar6 +
               pfVar6[1] * (float)in_ECX[0x30] + pfVar6[2] * (float)in_ECX[0x31]) {
          in_ECX[0x27] = 0;
        }
        else {
          in_ECX[0x27] = 1;
        }
        pfVar6 = (float *)(in_ECX + 0x2f);
        if (in_ECX[0x27] == 0) {
          if (*pfVar4 + *pfVar6 < 0.25) {
            fVar5 = 0.25 - *pfVar4;
            goto LAB_00412318;
          }
        }
        else if (*pfVar4 - *pfVar6 < 0.25) {
          fVar5 = *pfVar4 - 0.25;
LAB_00412318:
          *pfVar6 = fVar5;
        }
        fVar5 = (*pfVar4 - 0.5) * 0.2 - 0.16;
        if (in_ECX[0x27] == 0) {
          fVar5 = *pfVar6 - fVar5;
        }
        else {
          fVar5 = fVar5 + *pfVar6;
        }
        *pfVar6 = fVar5;
      }
      if ((in_ECX[0x28] == 0x5a) ||
         (((10 < in_ECX[0x28] && ((float)in_ECX[0x1f] < 0.25)) || (local_7d != '\0')))) {
        fStack_74 = (float)in_ECX[0x3c];
        local_1c = (float *)0x0;
        local_24 = (int *)0x3f8ccccd;
        local_78 = (int *)0x3f8ccccd;
        fStack_70 = 0.0;
        local_20 = fStack_74;
        piVar2 = (int *)FUN_004021a7(local_4b8,in_ECX + 0x1f);
        in_ECX[0x2f] = *piVar2;
        in_ECX[0x30] = piVar2[1];
        in_ECX[0x31] = piVar2[2];
        fVar15 = (float10)FUN_004022a2();
        if (((float10)0.16000001 < fVar15) || (local_7d != '\0')) {
          in_ECX[0x27] = 0;
          in_ECX[0x29] = 8;
          fVar15 = (float10)FUN_004022a2();
          fVar15 = (float10)FUN_0041d134((double)fVar15);
          in_ECX[0x2a] = (int)(float)(fVar15 * (float10)0.3 + (float10)0.5);
          if ((float)in_ECX[0x31] < 0.1) {
            in_ECX[0x27] = 1;
            in_ECX[0x2f] = (int)((float)in_ECX[0x2f] * -1.0);
            in_ECX[0x30] = (int)((float)in_ECX[0x30] * -1.0);
            in_ECX[0x31] = (int)((float)in_ECX[0x31] * -1.0);
          }
        }
      }
    }
    goto LAB_00412435;
  case 1:
    local_c = (int *)((float)in_ECX[0x28] * 0.09239978);
    if (3.1415927 < (float)local_c) {
      in_ECX[0x27] = in_ECX[0x27] ^ 1;
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 2;
    }
    if (in_ECX[0x27] == 0) {
      fVar23 = 1.0;
      fVar5 = (float)in_ECX[0x28] * 0.01764706;
    }
    else {
      fVar23 = -1.0;
      fVar5 = 1.0 - (float)in_ECX[0x28] * 0.01764706;
    }
    in_ECX[0x3b] = (int)fVar5;
    local_78 = (int *)(fVar23 * 0.03);
    local_20 = 0.0;
    local_1c = (float *)0x3cf5c28f;
    fStack_74 = 0.0;
    fStack_70 = 0.03;
    local_24 = local_78;
    FUN_004023c6(&local_4c,*in_ECX + 0x60);
    ppfVar24 = &local_8;
    puVar19 = local_548;
    local_48 = 0.0;
    local_8 = (float *)0x3d75c28f;
    FUN_004021a7(local_560,in_ECX + 0x2b);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_0040225a(uVar3);
    local_3c = local_3c - (float)in_ECX[0x2b];
    local_38 = local_38 - (float)in_ECX[0x2c];
    local_34 = local_34 - (float)in_ECX[0x2d];
    in_ECX[(in_ECX[0x27] + 0xb) * 3] = (int)((float)in_ECX[(in_ECX[0x27] + 0xb) * 3] + 0.05882353);
    local_10 = (float *)((float)local_c + (float)local_c);
    fVar15 = (float10)FUN_0041cd94((double)(float)local_10);
    in_ECX[in_ECX[0x27] * 3 + 0x20] =
         (int)(float)(((float10)1.0 - fVar15) * (float10)1.1 - (float10)8.5);
    fVar15 = (float10)FUN_0041cd94((double)(float)local_10);
    in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x20] =
         (int)(float)((float10)-8.5 - ((float10)1.0 - fVar15) * (float10)0.3);
    in_ECX[((in_ECX[0x27] ^ 1U) + 0xb) * 3] =
         (int)((float)in_ECX[((in_ECX[0x27] ^ 1U) + 0xb) * 3] - 0.05882353);
    goto LAB_00414064;
  case 2:
    if ((float)in_ECX[0x3b] < (float)in_ECX[0x27]) {
      in_ECX[0x3b] = (int)((float)in_ECX[0x3b] + 0.01);
    }
    if ((float)in_ECX[0x27] < (float)in_ECX[0x3b]) {
      in_ECX[0x3b] = (int)((float)in_ECX[0x3b] - 0.01);
    }
    local_8 = (float *)0x41f00000;
    uVar3 = FUN_00402227(local_4d0,&local_8);
    uVar3 = FUN_00402172(local_4e8,uVar3);
    FUN_004021a7(&local_68,uVar3);
    in_ECX[0x28] = in_ECX[0x28] + -1;
    local_64 = 0.0;
    iVar10 = in_ECX[0x28];
    if (((float)in_ECX[0x3b] < 0.1) || (0.9 < (float)in_ECX[0x3b])) {
      if ((local_60 * local_60 + (float)local_68 * (float)local_68 < 1.6899998) ||
         (iVar11 = FUN_00402363(local_500,&local_68), *(float *)(iVar11 + 8) < -0.2)) {
        if (0 < iVar10) goto LAB_00412544;
        in_ECX[0x29] = 1;
      }
      in_ECX[0x28] = 0;
    }
LAB_00412544:
    local_24 = (int *)0x0;
    local_1c = (float *)0x3c23d70a;
    local_20 = 0.0;
    local_78 = (int *)0x0;
    fStack_74 = 0.0;
    fStack_70 = 0.01;
    FUN_004023c6(&local_4c,*in_ECX + 0x60);
    ppfVar24 = &local_8;
    puVar19 = local_518;
    local_48 = 0.0;
    local_8 = (float *)0x3d75c28f;
    FUN_004021a7(local_530,in_ECX + 0x2b);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_0040225a(uVar3);
    local_3c = local_3c - (float)in_ECX[0x2b];
    local_38 = local_38 - (float)in_ECX[0x2c];
    local_34 = local_34 - (float)in_ECX[0x2d];
    break;
  case 3:
    piVar2 = in_ECX + 0x5c;
    local_24 = (int *)0x0;
    local_20 = 0.0;
    local_1c = (float *)0x0;
    local_e8 = 0.0;
    local_e4 = 0.0;
    local_e0 = 0.0;
    do {
      piVar2[3] = 0;
      piVar2[-3] = 0;
      piVar2[-2] = 0;
      piVar2[-1] = 0;
      *piVar2 = 0;
      piVar12 = piVar2 + 2;
      piVar2[1] = 0;
      piVar2 = piVar2 + 0xd;
      iVar10 = iVar10 + -1;
      *piVar12 = 0;
    } while (iVar10 != 0);
    if ((7999 < in_ECX[0x28]) || (fVar15 = (float10)FUN_0040e896(), fVar15 < (float10)2.0)) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 0xc;
    }
    if ((*(int *)(in_ECX[1] + 0xd8) < DAT_00c06978 + -100) &&
       (*(int *)(in_ECX[2] + 0xd8) < DAT_00c06978 + -100)) {
      param_1 = in_ECX + 0xd4;
      local_50 = (float *)(local_bc + 3.0);
      local_98 = (float *)(in_ECX + 0xb);
      local_40 = 2.8026e-45;
      do {
        if (*(float *)((int)*local_98 + 0x88) < (float)local_50) {
          local_24 = (int *)0x0;
          local_20 = 1.0;
          param_1[-0xd] = 0x3c23d70a;
          *param_1 = 0x3c23d70a;
          local_1c = (float *)0x0;
          local_78 = (int *)0x0;
          fStack_74 = 1.0;
          fStack_70 = 0.0;
          piVar2 = (int *)FUN_00402363(local_254,&local_78);
          param_1[-0x13] = *piVar2;
          param_1[-0x12] = piVar2[1];
          param_1[-0x11] = piVar2[2];
          param_1[-6] = param_1[0xb0];
          param_1[-5] = param_1[0xb1];
          param_1[-4] = param_1[0xb2];
        }
        local_98 = local_98 + 3;
        param_1 = param_1 + 0x27;
        local_40 = (float)((int)local_40 + -1);
      } while (local_40 != 0.0);
    }
    in_ECX[0x28] = in_ECX[0x28] + 1;
    return;
  case 4:
    in_ECX[0x28] = in_ECX[0x28] + 1;
    local_14 = (float *)in_ECX[0x28];
    local_84 = (float)(int)local_14 * 0.04;
    if (1.2 < local_84) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 5;
    }
    goto LAB_004129cc;
  case 5:
    local_78 = (int *)((float)local_18 * 0.2);
    in_ECX[0x28] = in_ECX[0x28] + 1;
    local_20 = 0.0;
    local_1c = (float *)0x0;
    local_84 = 1.2;
    fStack_74 = 0.0;
    fStack_70 = 0.0;
    local_24 = local_78;
    FUN_004023c6(&local_4c,*in_ECX + 0x60);
    local_3c = local_3c - (float)local_4c;
    local_34 = local_34 - local_44;
    if (10 < in_ECX[0x28]) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 6;
    }
    break;
  case 6:
    in_ECX[0x28] = in_ECX[0x28] + 1;
    local_14 = (float *)in_ECX[0x28];
    local_84 = 1.2 - (float)(int)local_14 * (float)(int)local_14 * 0.02028;
    in_ECX[in_ECX[0x27] * 3 + 0x20] = -0x3f000000;
    if (local_84 < 0.0) {
      in_ECX[0x29] = 0;
      in_ECX[0x28] = 0;
      in_ECX[in_ECX[0x27] * 3 + 0x20] = -0x3ef4cccd;
    }
LAB_004129cc:
    local_78 = (int *)((float)local_18 * 0.2);
    local_20 = 0.0;
    local_1c = (float *)0x0;
    fStack_74 = 0.0;
    fStack_70 = 0.0;
    local_24 = local_78;
    FUN_004023c6(&local_4c,*in_ECX + 0x60);
    local_3c = local_3c - (float)local_4c;
    local_34 = local_34 - local_44;
    break;
  case 7:
    if (in_ECX[0x28] < 0x78) {
      in_ECX[0x28] = in_ECX[0x28] + 1;
    }
    else {
      in_ECX[0x28] = 0;
    }
    local_20 = 0.0;
    local_24 = (int *)0x3d4ccccd;
    local_1c = (float *)0x0;
    local_78 = (int *)0x3d4ccccd;
    fStack_74 = 0.0;
    fStack_70 = 0.0;
    FUN_004023c6(&local_4c,*in_ECX + 0x60);
    local_3c = local_3c - (float)local_4c;
    ppfVar24 = &local_8;
    puVar19 = local_554;
    local_34 = local_34 - local_44;
    local_8 = (float *)0x3f000000;
    local_c = (int *)0x42200000;
    FUN_00402172(local_26c,local_170 + (in_ECX[0x27] ^ 1U) * 3);
    FUN_00402227(puVar19,ppfVar24);
    uVar3 = FUN_00402227(local_3ec,&local_c);
    FUN_00402172(local_284,uVar3);
    fVar15 = (float10)FUN_0041d084((double)((float)in_ECX[0x28] * 0.02617994));
    in_ECX[in_ECX[0x27] * 3 + 0x20] = (int)(float)(fVar15 - (float10)8.7);
    break;
  case 8:
    in_ECX[in_ECX[0x27] * 3 + 0x20] = (int)((float)in_ECX[0x3c] - (float)in_ECX[0x28] * 0.05);
    in_ECX[0x28] = in_ECX[0x28] + 1;
    if (5 < in_ECX[0x28]) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 9;
    }
    ppfVar24 = &local_8;
    local_8 = (float *)0x0;
    puVar19 = local_23c;
    local_c = (int *)0x3d4ccccd;
    FUN_00402227(local_29c,&local_c);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_0040225a(uVar3);
    ppfVar24 = &local_8;
    local_8 = (float *)0x0;
    puVar19 = local_404;
    local_c = (int *)0x3d4ccccd;
    FUN_00402227(local_2b4,&local_c);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_00407e1c(uVar3);
    ppfVar24 = &local_8;
    puVar19 = local_50c;
    local_8 = (float *)((float)in_ECX[0x28] * 0.049999997);
    FUN_00402227(local_2cc,in_ECX + 0x31);
    pfVar4 = (float *)FUN_00402227(puVar19,ppfVar24);
    local_c0 = local_c0 - *pfVar4;
    local_8 = (float *)0xbccccccd;
    local_bc = local_bc - pfVar4[1];
    local_b8 = local_b8 - pfVar4[2];
    ppfVar24 = &local_8;
    puVar19 = local_41c;
    FUN_00402227(local_2e4,in_ECX + 0x31);
    pfVar4 = (float *)FUN_00402227(puVar19,ppfVar24);
    local_3c = local_3c + *pfVar4;
    local_38 = local_38 + pfVar4[1];
    local_34 = local_34 + pfVar4[2];
    if (DAT_00c06b50 != 1) break;
LAB_00412435:
    local_d0 = 1.0;
    break;
  case 9:
    fVar5 = (float)in_ECX[0x28] * 0.05;
    local_10 = (float *)((1.0 - fVar5) * fVar5 * 6.0);
    fVar23 = fVar5 * fVar5 * fVar5;
    local_2c = fVar5 * fVar5 * 3.0 - (fVar23 + fVar23);
    local_14 = (float *)(local_2c * 3.1415927);
    fVar15 = (float10)FUN_0041d084((double)(float)local_14);
    in_ECX[in_ECX[0x27] * 3 + 0x20] =
         (int)(float)((float10)(float)local_14 * (float10)0.09549297 +
                     ((fVar15 * (float10)(float)in_ECX[0x2a] + (float10)(float)in_ECX[0x3c]) -
                     (float10)0.3));
    fVar15 = (float10)FUN_0041d084((double)(float)local_14);
    in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x20] =
         (int)(float)((float10)(float)in_ECX[0x3c] -
                     fVar15 * (float10)(float)in_ECX[0x2a] * (float10)0.2);
    ppfVar24 = &local_10;
    puVar19 = local_4c4;
    local_8 = (float *)0x3f800000;
    ppfVar20 = &local_8;
    puVar18 = local_2fc;
    local_c = (int *)0x3d4ccccd;
    FUN_00402227(local_434,&local_c);
    FUN_00402227(puVar18,ppfVar20);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_0040225a(uVar3);
    local_8 = (float *)0x3f800000;
    local_c = (int *)0x3d4ccccd;
    ppfVar24 = &local_10;
    puVar19 = local_314;
    ppfVar20 = &local_8;
    puVar18 = local_53c;
    FUN_00402227(local_32c,&local_c);
    FUN_00402227(puVar18,ppfVar20);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_00407e1c(uVar3);
    in_ECX[0x28] = in_ECX[0x28] + 1;
    if (0x13 < in_ECX[0x28]) {
      in_ECX[0x27] = in_ECX[0x27] ^ 1;
      in_ECX[0x29] = 0;
      in_ECX[0x28] = 0;
      in_ECX[in_ECX[0x27] * 3 + 0x20] = in_ECX[0x3c];
      in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x20] = in_ECX[0x3c];
    }
    ppfVar24 = &local_8;
    puVar19 = local_44c;
    ppiVar21 = &local_c;
    puVar18 = local_344;
    local_c = (int *)(((float)in_ECX[0x28] + 6.0) * 0.03846154 - local_2c);
    local_8 = (float *)0x3fa66666;
    FUN_00402227(local_4dc,in_ECX + 0x31);
    FUN_00402227(puVar18,ppiVar21);
    pfVar4 = (float *)FUN_00402227(puVar19,ppfVar24);
    local_c0 = local_c0 - *pfVar4;
    local_8 = (float *)0xbccccccd;
    local_bc = local_bc - pfVar4[1];
    local_b8 = local_b8 - pfVar4[2];
    ppfVar24 = &local_8;
    puVar19 = local_35c;
    FUN_00402227(local_464,in_ECX + 0x31);
    pfVar4 = (float *)FUN_00402227(puVar19,ppfVar24);
    local_3c = local_3c + *pfVar4;
    local_38 = local_38 + pfVar4[1];
    local_34 = local_34 + pfVar4[2];
    local_d0 = 0.0;
    break;
  case 10:
    in_ECX[0x3b] = 0x3f000000;
    local_14 = (float *)((float)in_ECX[0x28] * 0.033333335);
    local_10 = (float *)((float)local_14 * 3.1415927);
    fVar15 = (float10)FUN_0041d084((double)(float)local_10);
    local_8 = (float *)0xbd4ccccd;
    in_ECX[in_ECX[0x27] * 3 + 0x20] =
         (int)(float)(fVar15 + fVar15 + (float10)(float)in_ECX[0x3c] + (float10)(float)local_14);
    in_ECX[in_ECX[0x27] * 3 + 0x1f] = (int)((float)in_ECX[in_ECX[0x27] * 3 + 0x1f] + 0.11);
    in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x1f] =
         (int)((float)in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x1f] - 0.11);
    fVar15 = (float10)FUN_0041d084((double)(float)local_10);
    ppfVar24 = &local_8;
    puVar19 = local_374;
    local_c = (int *)(float)fVar15;
    FUN_00402227(local_524,&local_c);
    pfVar4 = (float *)FUN_00402227(puVar19,ppfVar24);
    local_3c = local_3c + *pfVar4;
    local_38 = local_38 + pfVar4[1];
    local_34 = local_34 + pfVar4[2];
    in_ECX[0x28] = in_ECX[0x28] + 1;
    if (1.0 < (float)local_14) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 0xb;
    }
    break;
  case 0xb:
    iVar10 = in_ECX[0x28];
    in_ECX[0x3b] = 0x3f000000;
    in_ECX[in_ECX[0x27] * 3 + 0x20] = (int)((1.0 - (float)iVar10 * 0.1) + (float)in_ECX[0x3c]);
    in_ECX[in_ECX[0x27] * 3 + 0x1f] = (int)((float)in_ECX[in_ECX[0x27] * 3 + 0x1f] - 0.32999998);
    in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x1f] =
         (int)((float)in_ECX[(in_ECX[0x27] ^ 1U) * 3 + 0x1f] + 0.32999998);
    if (1.0 < (float)iVar10 * 0.1) {
      in_ECX[0x29] = 0;
    }
    goto LAB_00414064;
  case 0xc:
    in_ECX[0x40] = 0;
    in_ECX[0x41] = 0;
    fVar5 = (float)in_ECX[0x28] * 0.00025;
    in_ECX[0x42] = 0;
    if (0.05 < fVar5) {
      fVar5 = 0.05;
    }
    piVar2 = in_ECX + 0x53;
    iVar10 = 0xe;
    do {
      piVar12 = piVar2 + 0xb6;
      piVar13 = piVar2;
      for (iVar11 = 0xd; iVar11 != 0; iVar11 = iVar11 + -1) {
        *piVar13 = *piVar12;
        piVar12 = piVar12 + 1;
        piVar13 = piVar13 + 1;
      }
      piVar2[0xc] = (int)fVar5;
      piVar2 = piVar2 + 0xd;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    local_18 = (int *)in_ECX[0x28];
    local_5c = (float)(int)local_18 * 0.018 - 0.5;
    if (local_5c < 0.0) {
      local_5c = 0.0;
    }
    if (2.0 < local_5c) {
      local_5c = 2.0;
    }
    local_14 = (float *)0x3f800000;
    local_25 = '\0';
    local_8 = (float *)0x0;
    local_58 = (int *)0x0;
    local_2c = 0.0;
    if (local_18 == (int *)0x64) {
      local_24 = (int *)0x0;
      local_20 = 0.0;
      local_1c = (float *)0x3f800000;
      local_78 = (int *)0x0;
      fStack_74 = 0.0;
      fStack_70 = 1.0;
      iVar10 = FUN_004023c6(local_38c,*in_ECX + 0x60);
      if (0.0 < *(float *)(iVar10 + 4)) {
        in_ECX[0x46] = in_ECX[0x46] ^ 1;
        in_ECX[0x28] = 0;
        in_ECX[0x44] = 0;
        in_ECX[0x29] = 0xd;
      }
    }
    local_18 = (int *)in_ECX[0x28];
    if (100 < (int)local_18) {
      iVar10 = *in_ECX;
      local_4c = (int *)0x3f800000;
      local_48 = 0.0;
      local_44 = 0.0;
      local_24 = (int *)0x3f800000;
      local_20 = 0.0;
      local_1c = (float *)0x0;
      local_78 = (int *)0x3f800000;
      fStack_74 = 0.0;
      fStack_70 = 0.0;
      iVar11 = FUN_004023c6(local_47c,iVar10 + 0x60);
      iVar10 = FUN_004023c6(local_3a4,iVar10 + 0x60);
      if ((0.25 < *(float *)(iVar11 + 4) * *(float *)(iVar10 + 4)) && (300 < (int)local_18)) {
        local_25 = '\x01';
      }
      fVar23 = (float)(int)local_18;
      fVar5 = (fVar23 - 100.0) * 0.01;
      if (1.0 < fVar5) {
        fVar5 = 1.0;
      }
      fVar1 = fVar5 * fVar5 * fVar5;
      local_58 = (int *)((fVar5 * fVar5 * 3.0 - (fVar1 + fVar1)) * 2.5);
      local_2c = (float)local_58;
      if (0xaa < (int)local_18) {
        fVar5 = (fVar23 - 170.0) * 0.006666667;
        if (1.0 < fVar5) {
          fVar5 = 1.0;
        }
        fVar1 = fVar5 * fVar5 * fVar5;
        fVar5 = fVar5 * fVar5 * 3.0 - (fVar1 + fVar1);
        local_5c = 2.0 - fVar5 * 1.8;
        local_14 = (float *)(1.0 - fVar5 * 2.5);
        if ((int)local_18 < 0x12d) {
          in_ECX[0x43] = (int)local_58;
          in_ECX[0x44] = (int)local_58;
        }
        else {
          local_10 = (float *)((fVar23 - 300.0) * 0.01);
          if (1.0 < (float)local_10) {
            local_10 = (float *)0x3f800000;
          }
          pfVar4 = &local_c0;
          puVar19 = local_4f4;
          local_c = (int *)0x43480000;
          uVar3 = FUN_00402227(local_3bc,&local_c);
          FUN_00402172(local_494,uVar3);
          FUN_004021a7(puVar19,pfVar4);
          pfVar4 = &local_c0;
          puVar19 = local_3d4;
          local_c = (int *)0x41a00000;
          uVar3 = FUN_00402227(local_248,&local_c);
          FUN_00402172(local_260,uVar3);
          pfVar4 = (float *)FUN_004021a7(puVar19,pfVar4);
          local_7c = (float *)(local_b4 * *pfVar4 + local_ac * pfVar4[2] + local_b0 * pfVar4[1]);
          fVar15 = (float10)FUN_0041ce90((double)((float)local_10 * -2.0));
          local_2c = (float)in_ECX[0x44];
          local_18 = (int *)in_ECX[0x28];
          fVar15 = (float10)(float)in_ECX[0x43] -
                   ((float10)1 - fVar15) * (float10)(float)in_ECX[0x43] * (float10)0.02;
          local_10 = (float *)(float)fVar15;
          in_ECX[0x43] = (int)(float)fVar15;
          local_58 = (int *)(float)fVar15;
          if ((int)local_18 < 0x2711) {
            pfVar4 = &local_c0;
            local_c = (int *)0x41a00000;
            puVar19 = local_278;
            local_10 = (float *)0x41a00000;
            uVar3 = FUN_00402227(local_290,&local_c);
            FUN_00402172(local_2a8,uVar3);
            FUN_004021a7(puVar19,pfVar4);
            pfVar4 = &local_c0;
            puVar19 = local_2c0;
            uVar3 = FUN_00402227(local_2d8,&local_10);
            FUN_00402172(local_2f0,uVar3);
            FUN_004021a7(puVar19,pfVar4);
          }
          else {
            fVar5 = ((float)(int)local_18 - 20000.0) * 0.006666667;
            if (1.0 < fVar5) {
              fVar5 = 1.0;
            }
            fVar23 = fVar5 * fVar5 * fVar5;
            fVar23 = fVar5 * fVar5 * 3.0 - (fVar23 + fVar23);
            local_5c = fVar23 * 0.6 + local_5c;
            local_14 = (float *)(fVar23 * 2.7 + (float)local_14);
            local_8 = (float *)(fVar23 * 2.5);
            if ((*(int *)(in_ECX[3] + 0xd8) < DAT_00c06978 + -300) ||
               (*(int *)(in_ECX[6] + 0xd8) < DAT_00c06978 + -300)) {
              local_25 = '\x01';
            }
            local_58 = (int *)((((float)local_7c * 0.002 +
                                ((float)local_7c - (float)in_ECX[0x45]) * 0.1) -
                               (0.2 - (float)local_10) * 0.01) + (float)local_10);
            in_ECX[0x43] = (int)local_58;
            if ((float)local_58 < 0.1) {
              local_25 = '\x01';
            }
            if ((float)in_ECX[0x44] <= 0.22) {
              local_25 = '\x01';
            }
            else {
              fVar5 = ((float)in_ECX[0x44] - 0.05) *
                      (1.0 / ((float)local_7c * (float)local_7c * 3.0 + 1.0)) * fVar5 * fVar5 * 0.35
              ;
              if (0.05 < fVar5) {
                fVar5 = 0.05;
              }
              in_ECX[0x44] = (int)((float)in_ECX[0x44] - fVar5);
            }
            if (2.5 < (float)in_ECX[0x44]) {
              in_ECX[0x44] = 0x40200000;
            }
            local_2c = (float)in_ECX[0x44];
          }
          local_c = (int *)0x41a00000;
          uVar3 = FUN_00402227(local_308,&local_c);
          FUN_00402172(&local_4c,uVar3);
          local_24 = (int *)0x0;
          local_20 = -5.0;
          local_1c = (float *)0x0;
          local_78 = (int *)0x0;
          fStack_74 = -5.0;
          local_c = (int *)0xbdcccccd;
          fStack_70 = 0.0;
          uVar3 = FUN_00402227(local_320,&local_c);
          ppiVar21 = &local_68;
          puVar19 = local_338;
          ppiVar22 = &local_78;
          FUN_004021a7(local_350,&local_4c);
          FUN_00402172(puVar19,ppiVar22);
          FUN_00402172(ppiVar21,uVar3);
          FUN_004022c1();
          fVar15 = (float10)FUN_0041cd94(0xa0000000,0x3fb99999);
          if (((float10)local_64 < -fVar15) && (in_ECX[0x28] < 20000)) {
            in_ECX[0x28] = 20000;
          }
          fVar15 = (float10)FUN_0041cd94(0x40000000,0x3fd33333);
          if (-fVar15 < (float10)local_64) {
            fVar15 = (float10)FUN_0041d414(0x40000000,0x3fd33333);
            local_c = (int *)(float)fVar15;
            fVar15 = (float10)FUN_0041d134((double)(1.0 - local_64 * local_64));
            local_64 = (float)(((float10)-1.0 / (float10)(float)local_c) * fVar15);
            FUN_004022c1();
            if (600 < in_ECX[0x28]) {
              local_25 = '\x01';
            }
          }
          local_18 = in_ECX + 0x13;
          local_c = (int *)0x2;
          local_10 = (float *)(in_ECX + 0x8d);
          do {
            FUN_00402363(&local_24,&local_68);
            fVar15 = (float10)FUN_0041cd94(0,0x3fe00000);
            if (-fVar15 < (float10)local_20) {
              fVar15 = (float10)FUN_0041d414(0,0x3fe00000);
              local_30 = (float)fVar15;
              fVar15 = (float10)FUN_0041d134((double)(1.0 - local_20 * local_20));
              local_20 = (float)(((float10)-1.0 / (float10)local_30) * fVar15);
              FUN_004022c1();
            }
            local_18 = local_18 + 3;
            local_c = (int *)((int)local_c + -1);
            *local_10 = (float)local_24;
            local_10[1] = local_20;
            local_10[2] = (float)local_1c;
            local_10 = local_10 + 0x27;
          } while (local_c != (int *)0x0);
          in_ECX[0x45] = (int)local_7c;
        }
      }
      if (local_25 != '\0') {
        in_ECX[0x47] = 0;
        in_ECX[0x29] = 0;
        in_ECX[0x1f] = 0x3e99999a;
        in_ECX[0x20] = in_ECX[0x3c];
        in_ECX[0x21] = 0;
        in_ECX[0x22] = -0x41666666;
        in_ECX[0x23] = in_ECX[0x3c];
        in_ECX[0x24] = 0;
        if (*(float *)(in_ECX[2] + 0x88) < local_bc + 10.0) {
          in_ECX[0x29] = 3;
        }
        in_ECX[0x28] = 0;
        in_ECX[0x36] = 0;
        in_ECX[0x3b] = 0x3f000000;
        in_ECX[0x39] = 0;
        in_ECX[0x38] = 0;
        in_ECX[0x37] = 0;
        in_ECX[0x3a] = 0;
      }
    }
    local_7c = (float *)0x3f800000;
    local_68 = (int *)0x0;
    local_c = (int *)0x2;
    local_60 = 0.0;
    local_118 = (int *)0x0;
    local_114 = 0.0;
    local_f4 = 0.0;
    local_ec = 0.0;
    local_4c = (int *)0x0;
    local_44 = 0.0;
    local_100 = 0x3f800000;
    local_10 = (float *)-(float)local_58;
    uStack_fc = 0;
    uStack_f8 = 0;
    local_24 = (int *)0x3f800000;
    local_20 = 0.0;
    local_1c = (float *)0x0;
    local_a4 = 1.0;
    fStack_a0 = 0.0;
    fStack_9c = 0.0;
    local_58 = in_ECX + 0xc1;
    do {
      fStack_74 = (float)local_7c * -1.0;
      local_78 = local_68;
      fStack_70 = local_60;
      local_64 = fStack_74;
      local_30 = fStack_74;
      uVar3 = FUN_00402227(local_368,&local_14);
      FUN_00402ea2(uVar3);
      local_110 = local_7c;
      local_24 = local_118;
      local_20 = local_114;
      local_1c = local_7c;
      uVar3 = FUN_00402227(local_380,&local_8);
      FUN_00402ea2(uVar3);
      local_f0 = local_30;
      local_134[4] = local_f4;
      local_134[5] = local_30;
      local_134[6] = local_ec;
      uVar3 = FUN_00402227(local_398,&local_5c);
      FUN_00402ea2(uVar3);
      ppiVar21 = &local_10c;
      fStack_108 = (float)local_7c * -0.3;
      local_10c = local_4c;
      puVar19 = local_3b0;
      fStack_104 = local_44;
      local_48 = fStack_108;
      FUN_00402227(local_3c8,&local_2c);
      uVar3 = FUN_00402172(puVar19,ppiVar21);
      piVar2 = local_58;
      FUN_00402ea2(uVar3);
      uVar3 = FUN_00402227(local_3e0,&local_10);
      FUN_00402ea2(uVar3);
      local_58 = piVar2 + 0x27;
      local_c = (int *)((int)local_c + -1);
      local_7c = (float *)0xbf800000;
    } while (local_c != (int *)0x0);
    local_c = (int *)0x0;
    goto LAB_00414064;
  case 0xd:
    fVar5 = (float)in_ECX[0x28] * 0.00025;
    if (0.05 < fVar5) {
      fVar5 = 0.05;
    }
    piVar2 = in_ECX + 0x53;
    do {
      piVar12 = piVar2 + 0xb6;
      piVar13 = piVar2;
      for (iVar11 = 0xd; iVar11 != 0; iVar11 = iVar11 + -1) {
        *piVar13 = *piVar12;
        piVar12 = piVar12 + 1;
        piVar13 = piVar13 + 1;
      }
      piVar2[0xc] = (int)fVar5;
      piVar2 = piVar2 + 0xd;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    local_4c = (int *)0x0;
    local_48 = 0.0;
    local_44 = 1.0;
    local_a4 = 0.0;
    fStack_a0 = 0.0;
    fStack_9c = 1.0;
    FUN_004023c6(&local_24,*in_ECX + 0x60);
    if ((float)local_1c * (float)local_1c + (float)local_24 * (float)local_24 <= 0.36) {
      if (0.0 < (float)in_ECX[0x44]) {
        fVar5 = (float)in_ECX[0x44] - 0.08;
        goto LAB_00413ac5;
      }
    }
    else {
      fVar5 = (float)in_ECX[0x44] + 0.04;
LAB_00413ac5:
      in_ECX[0x44] = (int)fVar5;
    }
    if ((4.6 < (float)in_ECX[0x44]) || (600 < in_ECX[0x28])) {
      in_ECX[0x28] = 0;
      in_ECX[0x29] = 3;
    }
    local_10 = (float *)(1.0 - (float)in_ECX[0x44]);
    local_8 = (float *)0x3;
    local_30 = (float)in_ECX[0x44] * 0.3 + 1.0;
    local_5c = 1.0;
    iVar10 = 0;
    if (in_ECX[0x46] == 0) {
      local_8 = (float *)0x0;
      local_5c = -1.0;
      iVar10 = 3;
    }
    local_4c = (int *)0x0;
    fStack_a0 = local_5c * -1.0;
    local_44 = 0.0;
    local_a4 = 0.0;
    local_c = in_ECX + iVar10 * 0xd;
    fStack_9c = 0.0;
    pfVar4 = &local_30;
    puVar19 = local_3f8;
    local_14 = (float *)0xbf800000;
    local_48 = fStack_a0;
    FUN_00402227(local_410,&local_14);
    uVar3 = FUN_00402227(puVar19,pfVar4);
    FUN_00402ea2(uVar3);
    pfVar4 = (float *)FUN_00402279(local_224,local_5c * (float)in_ECX[0x44] * -0.2,
                                   (float)in_ECX[0x44] * 0.5,0);
    local_4c = (int *)*pfVar4;
    local_48 = pfVar4[1];
    local_44 = pfVar4[2];
    local_c[0xc1] = (int)((float)local_4c + (float)local_c[0xc1]);
    local_c[0xc2] = (int)(local_48 + (float)local_c[0xc2]);
    local_c[0xc3] = (int)(local_44 + (float)local_c[0xc3]);
    FUN_004022c1();
    local_48 = local_5c;
    local_4c = (int *)0x0;
    local_44 = 0.0;
    local_a4 = 0.0;
    fStack_a0 = local_5c;
    fStack_9c = 0.0;
    local_8 = (float *)(in_ECX + (int)local_8 * 0xd);
    local_30 = 1.1;
    ppfVar24 = &local_10;
    puVar19 = local_218;
    FUN_00402227(local_1f4,&local_30);
    uVar3 = FUN_00402227(puVar19,ppfVar24);
    FUN_00402ea2(uVar3);
    pfVar4 = (float *)FUN_00402279(local_20c,0.9 - (float)in_ECX[0x44],
                                   local_5c * (float)in_ECX[0x44] * 1.5,local_5c * -1.2);
    local_a4 = *pfVar4;
    fStack_a0 = pfVar4[1];
    fStack_9c = pfVar4[2];
    FUN_00402ea2(&local_a4);
    local_4c = (int *)0xbe99999a;
    local_48 = 0.0;
    local_44 = 0.0;
    local_a4 = -0.3;
    fStack_a0 = 0.0;
    fStack_9c = 0.0;
    uVar3 = FUN_00402227(local_1e8,&local_10);
    FUN_00402ea2(uVar3);
    iVar10 = in_ECX[0x28];
    if ((100 < iVar10) && (fVar15 = (float10)FUN_0040e896(), fVar15 < (float10)0.5)) {
      in_ECX[0x28] = iVar10 + 10;
    }
    goto LAB_00414064;
  case 0xe:
    piVar2 = in_ECX + 0x53;
    do {
      piVar12 = piVar2 + 0xb6;
      piVar13 = piVar2;
      for (iVar11 = 0xd; iVar11 != 0; iVar11 = iVar11 + -1) {
        *piVar13 = *piVar12;
        piVar12 = piVar12 + 1;
        piVar13 = piVar13 + 1;
      }
      piVar2[0xc] = 0x3ba3d70a;
      piVar2 = piVar2 + 0xd;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    in_ECX[0x44] = (int)((float)in_ECX[0x44] - *(float *)(in_ECX[2] + 0x7c) * 0.05);
    local_2c = *(float *)(in_ECX[2] + 0x7c);
    local_10 = (float *)0x0;
    local_7c = (float *)0x0;
    local_58 = (int *)0x0;
    dVar16 = _fabs((double)local_2c);
    if (0.30000001192092896 <= dVar16) {
      fVar15 = (float10)FUN_0041d134((double)(local_2c * local_2c));
      fVar15 = (float10)local_2c - ((float10)local_2c / fVar15) * (float10)0.3;
      if (fVar15 < (float10)0.0) {
        local_7c = (float *)(float)((float10)-1.5 * fVar15);
        local_10 = (float *)(float)((float10)0.4 * fVar15);
        local_58 = (int *)(float)((float10)0.6 * fVar15);
      }
      if ((float10)0.0 < fVar15) {
        local_7c = (float *)0x0;
        local_10 = (float *)(float)((float10)1.5 * fVar15);
        local_58 = (int *)(float)(fVar15 * (float10)0.3);
      }
    }
    local_18 = (int *)0x3f800000;
    local_14 = (float *)(in_ECX + 0x80);
    local_f4 = 0.0;
    local_8 = (float *)0x2;
    local_ec = 0.0;
    local_100 = 0x3f800000;
    uStack_fc = 0;
    uStack_f8 = 0;
    local_4c = (int *)0x3f800000;
    local_48 = 0.0;
    local_44 = 0.0;
    local_10c = (int *)0x3f800000;
    fStack_108 = 0.0;
    fStack_104 = 0.0;
    do {
      local_f0 = (float)local_18 * -0.3;
      local_a4 = local_f4;
      fStack_9c = local_ec;
      fStack_a0 = local_f0;
      fVar15 = (float10)FUN_0041d084((double)(float)in_ECX[0x44]);
      pfVar4 = &local_a4;
      puVar19 = local_200;
      local_30 = (float)(fVar15 * (float10)(float)local_18 * (float10)0.3 + (float10)(float)local_10
                        );
      FUN_00402227(local_1dc,&local_30);
      uVar3 = FUN_00402172(puVar19,pfVar4);
      FUN_00402ea2(uVar3);
      fVar15 = (float10)FUN_0041d084((double)(float)in_ECX[0x44]);
      local_30 = (float)(fVar15 * (float10)(float)local_18 * (float10)0.3 - (float10)(float)local_7c
                        );
      uVar3 = FUN_00402227(local_1a0,&local_30);
      FUN_00402ea2(uVar3);
      local_14 = local_14 + 0x27;
      local_8 = (float *)((int)local_8 + -1);
      local_18 = (int *)0xbf800000;
    } while (local_8 != (float *)0x0);
    fVar15 = (float10)FUN_0041cd94((double)(float)local_58);
    local_30 = (float)fVar15;
    fVar15 = (float10)FUN_0041d084((double)(float)local_58);
    pfVar4 = (float *)FUN_00402279(local_194,0,local_30 * -1.0,(float)fVar15);
    local_a4 = *pfVar4;
    fStack_a0 = pfVar4[1];
    fStack_9c = pfVar4[2];
    in_ECX[0x66] = (int)local_a4;
    in_ECX[0x67] = (int)fStack_a0;
    in_ECX[0x68] = (int)fStack_9c;
    FUN_004022c1();
    local_2c = 0.0;
    local_14 = (float *)(in_ECX + 0xc1);
    in_ECX[0x6c] = 0x3a51b717;
    local_18 = (int *)0x3f800000;
    local_48 = 0.0;
    local_44 = 0.0;
    do {
      local_144[(int)local_2c] = 0.0;
      local_8 = (float *)in_ECX[0x44];
      fVar15 = (float10)FUN_0041cd94((double)(float)local_8);
      local_30 = (float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)(float)local_8);
      pfVar6 = (float *)FUN_00402279(local_170 + 3,(float)local_18 * 0.4,
                                     -((float)local_18 * local_30),
                                     (float)((float10)0.5 - fVar15 * (float10)(float)local_18));
      pfVar4 = local_14;
      *local_14 = *pfVar6;
      local_14[1] = pfVar6[1];
      local_14[2] = pfVar6[2];
      FUN_004022c1();
      FUN_004022c1();
      local_4c = local_18;
      pfVar4[0x1a] = (float)local_18;
      pfVar4[0x1b] = local_48;
      pfVar4[0x1c] = local_44;
      FUN_004022c1();
      local_2c = (float)((int)local_2c + 3);
      local_14 = local_14 + 0x27;
      local_18 = (int *)0xbf800000;
    } while ((int)local_2c < 4);
LAB_00414064:
    in_ECX[0x28] = in_ECX[0x28] + 1;
  }
  iVar10 = in_ECX[0x29];
  if (((iVar10 != 0xc) && (iVar10 != 0xd)) && (iVar10 != 0xe)) {
    FUN_004021a7(&local_68,*in_ECX + 0x84);
    if (6.25 < (float)in_ECX[0x21] * (float)in_ECX[0x21]) {
      local_d0 = 0.0;
    }
    fVar15 = (float10)FUN_0041d134((double)(local_64 * local_64 +
                                           local_60 * local_60 + (float)local_68 * (float)local_68))
    ;
    fVar15 = ((float10)local_60 * (float10)local_c4 +
             (float10)(float)local_68 * (float10)local_cc + (float10)local_64 * (float10)local_c8) *
             ((float10)1.0 / fVar15) * (float10)-0.1;
    in_ECX[0x48] = (int)(float)fVar15;
    if ((float10)0.0016 < fVar15 * fVar15) {
      dVar16 = _fabs((double)fVar15);
      in_ECX[0x48] = (int)(((float)in_ECX[0x48] / (float)dVar16) * 0.04);
    }
    if ((100.0 <= (float)in_ECX[0x48]) && ((float)in_ECX[0x48] <= 100.0)) {
      in_ECX[0x48] = 0;
    }
    in_ECX[0x48] = (int)((float)local_50 + (float)in_ECX[0x48]);
    if ((((in_ECX[0x1bf] != 2) || (iVar10 = in_ECX[0x50], iVar10 == 4)) || (iVar10 == 1)) ||
       (iVar10 == 2)) {
      in_ECX[0x48] = (int)local_50;
    }
    fVar5 = local_d0 * (float)in_ECX[0x48];
    local_170[0] = in_ECX[0x1f];
    local_170[1] = in_ECX[0x20];
    in_ECX[0x48] = (int)fVar5;
    local_170[2] = in_ECX[0x21];
    local_170[3] = in_ECX[0x22];
    iStack_160 = in_ECX[0x23];
    iStack_15c = in_ECX[0x24];
    fVar15 = (float10)FUN_0041d084((double)fVar5);
    local_30 = (float)fVar15;
    fVar15 = (float10)FUN_0041cd94((double)fVar5);
    local_10 = (float *)(float)((float10)local_30 * (float10)(float)in_ECX[0x21] +
                               fVar15 * (float10)(float)in_ECX[0x1f]);
    fVar15 = (float10)FUN_0041d084((double)fVar5);
    local_30 = (float)fVar15;
    fVar15 = (float10)FUN_0041cd94((double)fVar5);
    fVar5 = (float)in_ECX[0x1f];
    in_ECX[0x1f] = (int)local_10;
    in_ECX[0x21] = (int)(float)(fVar15 * (float10)(float)in_ECX[0x21] -
                               (float10)local_30 * (float10)fVar5);
    in_ECX[0x22] = (int)-(float)local_10;
    in_ECX[0x24] = (int)-(float)in_ECX[0x21];
    if ((float)local_10 < 0.2) {
      in_ECX[0x1f] = local_170[0];
      in_ECX[0x20] = local_170[1];
      in_ECX[0x21] = local_170[2];
      in_ECX[0x22] = local_170[3];
      in_ECX[0x23] = iStack_160;
      in_ECX[0x24] = iStack_15c;
    }
    fVar5 = local_84 * 0.1;
    local_f4 = local_c0;
    local_f0 = local_bc;
    local_54 = fVar5 + local_54;
    local_ec = local_b8;
    local_dc = local_c0;
    local_d4 = local_b8;
    local_d8 = 5.0;
    FUN_0040fdd0(&local_dc,0xff00);
    local_30 = 20.0;
    uVar3 = FUN_00402227(local_170 + 3,&local_30);
    FUN_00402172(&local_78,uVar3);
    FUN_004021a7(&local_4c,&local_c0);
    local_48 = 0.0;
    pfVar4 = (float *)(in_ECX + 0x47);
    in_ECX[0x49] = (int)local_4c;
    in_ECX[0x4a] = 0;
    local_50 = (float *)((1.0 - *pfVar4) * 0.01 + *pfVar4);
    in_ECX[0x4b] = (int)local_44;
    *pfVar4 = (float)local_50;
    pfVar4 = &local_f4;
    puVar19 = local_194;
    local_30 = 15.0;
    uVar3 = FUN_00402227(local_170 + 3,&local_30);
    FUN_00402172(local_1a0,uVar3);
    pfVar4 = (float *)FUN_004021a7(puVar19,pfVar4);
    fVar15 = (((float10)local_e0 * (float10)local_c4 +
              (float10)local_e8 * (float10)local_cc + (float10)local_e4 * (float10)local_c8) *
              (float10)4e-05 +
             ((float10)local_b4 * (float10)*pfVar4 +
             (float10)local_ac * (float10)pfVar4[2] +
             (float10)local_b0 * (float10)pfVar4[1] +
             ((float10)(float)in_ECX[0x37] * (float10)10.0 + (float10)(float)in_ECX[0x36]) *
             (float10)0.1) * (float10)0.04) - (float10)(float)in_ECX[0x38];
    local_30 = (float)(fVar15 * fVar15);
    if ((float10)0.09 < fVar15 * fVar15) {
      fVar15 = (float10)FUN_0041d134((double)local_30);
      fVar15 = fVar15 * (float10)0.3;
    }
    in_ECX[0x37] = (int)(float)((fVar15 * (float10)(float)local_50 - (float10)(float)in_ECX[0x37]) *
                                (float10)0.01 + (float10)(float)in_ECX[0x37]);
    fVar15 = (fVar15 * (float10)(float)local_50 + (float10)fVar5 + (float10)(float)in_ECX[0x36]) *
             (float10)0.8;
    in_ECX[0x36] = (int)(float)fVar15;
    in_ECX[0x38] = (int)(float)(((fVar15 - (float10)local_54) - (float10)(float)in_ECX[0x38]) *
                                (float10)0.004 + (float10)(float)in_ECX[0x38]);
    pfVar4 = (float *)FUN_004021a7(local_170 + 3,&local_f4);
    fVar15 = ((float10)local_e8 * (float10)local_b4 +
             (float10)local_e0 * (float10)local_ac + (float10)local_e4 * (float10)local_b0) *
             (float10)3e-05 +
             (((float10)local_c4 * (float10)local_34 +
              (float10)local_38 * (float10)local_c8 + (float10)local_cc * (float10)local_3c) *
              (float10)20.0 +
             (float10)local_cc * (float10)*pfVar4 +
             (float10)local_c8 * (float10)pfVar4[1] + (float10)local_c4 * (float10)pfVar4[2]) *
             (float10)0.002;
    if ((float10)0.09 < fVar15 * fVar15) {
      fVar15 = (float10)FUN_0041d134((double)(float)(fVar15 * fVar15));
      fVar15 = fVar15 * (float10)0.3;
    }
    local_54 = 0.0;
    local_10 = (float *)(in_ECX + 0x13);
    local_110 = (float *)0xbdcccccd;
    in_ECX[0x39] = (int)(float)((float10)(float)in_ECX[0x48] * (float10)0.37600002 +
                               ((float10)local_40 - (float10)0.5) * (float10)0.0047 +
                               (fVar15 * (float10)(float)local_50 + (float10)(float)in_ECX[0x39]) *
                               (float10)0.94);
    local_18 = (int *)0x3f800000;
    local_f4 = 0.0;
    local_14 = (float *)(local_84 + local_84);
    local_ec = 0.0;
    local_100 = 0x3f800000;
    uStack_fc = 0;
    uStack_f8 = 0;
    local_10c = (int *)0x0;
    local_114 = 0.0;
    fStack_108 = 0.0;
    fStack_104 = 1.0;
    local_4c = (int *)0x0;
    local_48 = 1.0;
    local_44 = 0.0;
    local_134[4] = 0.0;
    local_134[5] = 1.0;
    local_134[6] = 0.0;
    param_1 = in_ECX + 0x73;
    do {
      local_30 = (float)in_ECX[0x36];
      fVar15 = (float10)FUN_0041cd94((double)(float)in_ECX[0x36]);
      local_8 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041cd94((double)(float)in_ECX[0x39]);
      local_50 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)(float)in_ECX[0x39]);
      local_c = (int *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)local_30);
      piVar2 = (int *)FUN_00402279(local_170 + 3,(float)local_18 * 0.04 + (float)local_c,
                                   -((float)local_50 * (float)local_8),(float)fVar15);
      *param_1 = *piVar2;
      param_1[1] = piVar2[1];
      param_1[2] = piVar2[2];
      local_50 = (float *)(in_ECX + ((int)local_54 / 3) * 3 + 0x1f);
      local_dc = *local_50;
      local_d8 = local_50[1];
      local_d4 = local_50[2];
      pfVar4 = (float *)FUN_00402279(local_194,local_dc,0,local_d4);
      local_24 = (int *)*pfVar4;
      local_20 = pfVar4[1];
      local_1c = (float *)pfVar4[2];
      pfVar6 = (float *)FUN_0040e687(local_1a0);
      pfVar4 = &local_a4;
      ppiVar21 = &local_68;
      local_f0 = (local_20 * local_20 +
                 (float)local_1c * (float)local_1c + (float)local_24 * (float)local_24) * 0.0 +
                 ((pfVar6[1] * 0.0 +
                  (float)local_18 * (float)in_ECX[0x39] * 0.5 +
                  (local_dc * *pfVar6 + local_d4 * pfVar6[2]) * 0.7) - (float)local_14);
      local_a4 = local_f4;
      fStack_9c = local_ec;
      fStack_a0 = local_f0;
      FUN_00406e8a(local_1dc);
      FUN_00402172(ppiVar21,pfVar4);
      if (local_54 != 0.0) {
        local_60 = local_60 - _DAT_00c0a4e0;
        local_64 = local_64 - _DAT_00c0a4e0;
      }
      fVar15 = (float10)FUN_0041d134((double)((float)local_68 * (float)local_68 +
                                             local_60 * local_60 + local_64 * local_64));
      local_50 = (float *)(float)fVar15;
      local_8 = (float *)(local_88 + (float)in_ECX[0x36]);
      fVar15 = (float10)FUN_0041cd94((double)(float)local_8);
      local_c = (int *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)(float)local_8);
      FUN_00402e1d(&local_100,local_c,(float)fVar15);
      local_2c = (float)in_ECX[0x39];
      fVar15 = (float10)FUN_0041cd94((double)(float)in_ECX[0x39]);
      local_8 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)local_2c);
      FUN_00402e1d(&local_10c,local_8,(float)-fVar15);
      piVar2 = (int *)FUN_00406e8a(local_200);
      *param_1 = *piVar2;
      param_1[1] = piVar2[1];
      param_1[2] = piVar2[2];
      FUN_004022c1();
      fVar15 = (float10)FUN_0040fd6e(in_ECX[0x1d],in_ECX[0x1e],local_50);
      local_8 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d134((double)((float10)1.0 - fVar15 * fVar15));
      piVar2 = (int *)FUN_00402279(local_1e8,0,-(float)local_8,(float)-fVar15);
      param_1[0xd] = *piVar2;
      param_1[0xe] = piVar2[1];
      param_1[0xf] = piVar2[2];
      FUN_004022c1();
      fVar15 = (float10)FUN_0040fd6e(in_ECX[0x1d],local_50,in_ECX[0x1e]);
      local_40 = (float)fVar15;
      local_118 = local_18;
      param_1[3] = (int)local_18;
      param_1[4] = (int)local_114;
      param_1[5] = (int)local_110;
      FUN_004022c1();
      fVar15 = (float10)FUN_0041d134((double)(1.0 - local_40 * local_40));
      fVar5 = (float)fVar15;
      fVar23 = -local_40;
      uVar3 = FUN_00402227(local_20c,&local_18);
      FUN_00402e1d(uVar3,fVar23,fVar5);
      FUN_004022c1();
      pfVar6 = local_134 + 4;
      pfVar4 = &local_e8;
      FUN_004021a7(local_1f4,&local_78);
      FUN_00402172(pfVar4,pfVar6);
      FUN_004022c1();
      fVar15 = (float10)FUN_0041cd94(0x40000000,0x3fd33333);
      if (-fVar15 < (float10)local_e4) {
        fVar15 = (float10)FUN_0041d414(0x40000000,0x3fd33333);
        local_50 = (float *)(float)fVar15;
        fVar15 = (float10)FUN_0041d134((double)(1.0 - local_e4 * local_e4));
        local_e4 = (float)(((float10)-1.0 / (float10)(float)local_50) * fVar15);
        FUN_004022c1();
      }
      piVar2 = (int *)FUN_00402363(local_218,&local_e8);
      local_54 = (float)((int)local_54 + 3);
      local_10 = local_10 + 3;
      param_1[0x1a] = *piVar2;
      param_1[0x1b] = piVar2[1];
      param_1[0x1c] = piVar2[2];
      local_18 = (int *)0xbf800000;
      param_1 = param_1 + 0x27;
    } while ((int)local_54 < 4);
    iVar10 = FUN_004021a7(local_170 + 3,in_ECX + 0x1f);
    local_50 = *(float **)(iVar10 + 8);
    if (16.0 < (float)local_50 * (float)local_50) {
      if (0.0 <= (float)local_50) {
        local_50 = (float *)0x40800000;
      }
      else {
        local_50 = (float *)0xc0800000;
      }
    }
    fVar5 = (float)in_ECX[0x36];
    fVar15 = (float10)FUN_0041cd94((double)(fVar5 * 0.25));
    local_8 = (float *)(float)fVar15;
    fVar15 = (float10)FUN_0041cd94((double)((float)in_ECX[0x39] * 0.25));
    local_30 = (float)fVar15;
    fVar15 = (float10)FUN_0041d084((double)((float)in_ECX[0x39] * 0.25));
    local_c = (int *)(float)fVar15;
    fVar15 = (float10)FUN_0041d084((double)(fVar5 * 0.25));
    pfVar4 = (float *)FUN_00402279(local_170 + 3,local_c,local_30 * (float)local_8 * -1.0,
                                   (float)fVar15);
    local_a4 = *pfVar4;
    fStack_a0 = pfVar4[1];
    fStack_9c = pfVar4[2];
    in_ECX[0x59] = (int)local_a4;
    in_ECX[0x5a] = (int)fStack_a0;
    in_ECX[0x5b] = (int)fStack_9c;
    FUN_004022c1();
    local_4c = (int *)0x42200000;
    local_48 = 0.0;
    local_44 = -(float)local_50;
    in_ECX[0x5c] = 0x42200000;
    in_ECX[0x5d] = 0;
    in_ECX[0x5e] = (int)local_44;
    FUN_004022c1();
    fVar5 = ((float)in_ECX[0x36] * 0.25 - local_88 * 0.9) - (float)local_98;
    fVar15 = (float10)FUN_0041cd94((double)fVar5);
    local_8 = (float *)(float)fVar15;
    fVar15 = (float10)FUN_0041cd94((double)((float)in_ECX[0x39] * 0.25));
    local_30 = (float)fVar15;
    fVar15 = (float10)FUN_0041d084((double)((float)in_ECX[0x39] * 0.25));
    local_c = (int *)(float)fVar15;
    fVar15 = (float10)FUN_0041d084((double)fVar5);
    pfVar4 = (float *)FUN_00402279(local_170 + 3,local_c,local_30 * (float)local_8 * -1.0,
                                   (float)fVar15);
    local_a4 = *pfVar4;
    fStack_a0 = pfVar4[1];
    fStack_9c = pfVar4[2];
    in_ECX[0x66] = (int)local_a4;
    in_ECX[0x67] = (int)fStack_a0;
    in_ECX[0x68] = (int)fStack_9c;
    FUN_004022c1();
    local_54 = 0.0;
    in_ECX[0x2e] = (int)local_84;
    local_18 = (int *)0x3f800000;
    local_98 = &local_1d0;
    local_30 = local_88 + local_88;
    param_1 = in_ECX + 0xc1;
    local_14 = (float *)(local_84 * 0.4);
    local_48 = 0.0;
    local_44 = 0.0;
    do {
      local_8 = (float *)(((((float)in_ECX[0x36] - 0.08) * 3.0 + (float)in_ECX[0x35]) - local_30) -
                         (float)local_14);
      fVar15 = (float10)FUN_0041cd94((double)(float)local_8);
      local_10 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)((float)in_ECX[0x39] * 4.0));
      local_2c = (float)fVar15;
      local_c = (int *)((float)local_50 * (float)local_18);
      local_40 = (float)local_c * 0.05;
      fVar15 = (float10)FUN_0041d084((double)(float)local_8);
      piVar2 = (int *)FUN_00402279(local_170 + 3,(float)local_18 * 0.3,
                                   -(float)local_10 - local_2c * (float)local_18,
                                   (float)((float10)local_40 - fVar15));
      *param_1 = *piVar2;
      param_1[1] = piVar2[1];
      param_1[2] = piVar2[2];
      FUN_004022c1();
      fVar5 = local_54;
      local_78 = (int *)*local_98;
      fStack_74 = local_98[1];
      fStack_70 = local_98[2];
      local_8 = (float *)((float)local_18 * *(float *)((int)local_144 + (int)local_54) * -0.75);
      uVar3 = FUN_00402227(local_194,&local_8);
      FUN_00402ea2(uVar3);
      local_10 = (float *)(1.0 - *(float *)((int)local_134 + (int)fVar5));
      local_8 = local_10;
      uVar3 = FUN_00402227(local_1a0,(float *)((int)local_134 + (int)fVar5));
      puVar19 = local_1dc;
      FUN_00402227(local_200,&local_8);
      piVar2 = (int *)FUN_00402172(puVar19,uVar3);
      *param_1 = *piVar2;
      param_1[1] = piVar2[1];
      param_1[2] = piVar2[2];
      FUN_004022c1();
      fVar5 = local_54;
      local_40 = 0.65999997 - (float)local_c * 0.2;
      if (1.66 < local_40) {
        local_40 = 1.66;
      }
      pfVar4 = (float *)((int)local_144 + (int)local_54);
      fVar15 = (float10)FUN_0041cd94((double)*pfVar4);
      local_8 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)*pfVar4);
      local_c = (int *)(float)fVar15;
      fVar15 = (float10)FUN_0041cd94((double)*pfVar4);
      local_2c = (float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)*pfVar4);
      piVar2 = (int *)FUN_00402279(local_1e8,
                                   (float)(((fVar15 * (float10)1.66 + (float10)local_2c) *
                                            (float10)*(float *)((int)local_134 + (int)fVar5) +
                                           (float10)(float)local_10) * (float10)(float)local_18),0,
                                   (float)local_10 * local_40 +
                                   ((float)local_8 * 1.66 - (float)local_c) *
                                   *(float *)((int)local_134 + (int)fVar5));
      param_1[0xd] = *piVar2;
      param_1[0xe] = piVar2[1];
      param_1[0xf] = piVar2[2];
      FUN_004022c1();
      local_4c = local_18;
      param_1[0x1a] = (int)local_18;
      local_58 = *(int **)((int)local_158 + (int)local_54);
      param_1[0x1b] = (int)local_48;
      fVar5 = *(float *)((int)local_158 + (int)local_54);
      param_1[0x1c] = (int)local_44;
      fVar15 = (float10)FUN_0041cd94((double)fVar5);
      local_8 = (float *)(float)fVar15;
      fVar15 = (float10)FUN_0041d084((double)(float)local_58,0);
      pfVar4 = (float *)FUN_00402279(local_20c,(float)local_8 * (float)local_18,(float)-fVar15);
      local_a4 = *pfVar4;
      local_7c = local_10;
      fStack_a0 = pfVar4[1];
      fStack_9c = pfVar4[2];
      uVar3 = FUN_00402227(local_1f4,(int)local_134 + (int)local_54);
      puVar19 = local_218;
      FUN_00402227(local_224,&local_7c);
      piVar2 = (int *)FUN_00402172(puVar19,uVar3);
      param_1[0x1a] = *piVar2;
      param_1[0x1b] = piVar2[1];
      param_1[0x1c] = piVar2[2];
      FUN_004022c1();
      local_54 = (float)((int)local_54 + 0xc);
      local_98 = local_98 + 9;
      param_1 = param_1 + 0x27;
      local_18 = (int *)0xbf800000;
    } while ((int)local_54 < 0xd);
    if (((in_ECX[0x50] == 0) || (in_ECX[0x50] == 5)) && ((local_6c & 8) != 0)) {
      iVar10 = 8;
      do {
        *local_148 = 0;
        local_148 = local_148 + 0xd;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
  }
  return;
}



// ==== 0x414edb ====

void FUN_00414edb(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00c06b60;
  if (&DAT_00c06b60 < PTR_DAT_00453858) {
    do {
      FUN_00410b60(puVar2[0x1c0]);
      puVar2 = puVar2 + 0x1cc;
      DAT_00c0a4e4 = DAT_00c0a4e4 + 1;
      if (DAT_00c0a4e4 == 0x708) {
        iVar1 = FUN_0040461e();
        if (iVar1 == 0) {
          DAT_00c06984 = 2;
        }
      }
    } while (puVar2 < PTR_DAT_00453858);
  }
  return;
}



// ==== 0x414f2b ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00414f2b(void)

{
  FILE *pFVar1;
  int iVar2;
  int local_164;
  void *local_160;
  void *local_15c;
  int local_158;
  int *local_154;
  int local_150;
  void *local_14c;
  int local_148;
  char local_144 [260];
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined2 local_2e;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined2 local_2a;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  undefined1 local_c;
  undefined1 local_b;
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  do {
    _sprintf(local_144,"%s%d.bmp",PTR_s_shot_0042cb0f_1_00453864,DAT_00c0a4e8);
    pFVar1 = (FILE *)FUN_0041d331(local_144,&DAT_0042c278);
    if (pFVar1 != (FILE *)0x0) {
      _fclose(pFVar1);
    }
    DAT_00c0a4e8 = DAT_00c0a4e8 + 1;
  } while (pFVar1 != (FILE *)0x0);
  iVar2 = (**(code **)(*DAT_004571ec + 0x48))(DAT_004571ec,0,0,0,&local_154);
  if (-1 < iVar2) {
    local_14c = operator_new(DAT_00457338 * DAT_00457334 * 4);
    (**(code **)(*local_154 + 0x34))(local_154,&local_164,0,0);
    local_15c = operator_new((DAT_00457338 * local_164) / 4 << 2);
    _memcpy(local_15c,local_160,DAT_00457338 * local_164);
    (**(code **)(*local_154 + 0x38))(local_154);
    iVar2 = DAT_00457338;
    local_158 = DAT_00457334;
    local_148 = 0;
    if (0 < DAT_00457338) {
      local_150 = DAT_00457338 + -1;
      do {
        _memcpy((void *)((int)local_14c + DAT_00457334 * local_148 * 4),
                (void *)((int)local_15c + ((local_150 * local_164) / 4) * 4),DAT_00457334 << 2);
        local_148 = local_148 + 1;
        local_150 = local_150 + -1;
      } while (local_148 < iVar2);
    }
    local_2e = (undefined2)local_158;
    local_40 = 0x42;
    local_3f = 0x4d;
    local_3e = 0x36;
    local_3d = 0x30;
    local_3c = 0;
    local_3b = 0;
    local_3a = 0;
    local_39 = 0;
    local_38 = 0;
    local_37 = 0;
    local_36 = 0x36;
    local_35 = 0;
    local_34 = 0;
    local_33 = 0;
    local_32 = 0x28;
    local_31 = 0;
    local_30 = 0;
    local_2f = 0;
    local_2c = 0;
    local_2b = 0;
    local_28 = 0;
    local_27 = 0;
    local_26 = 1;
    local_25 = 0;
    local_24 = 0x20;
    local_23 = 0;
    local_22 = 0;
    local_21 = 0;
    local_20 = 0;
    local_1f = 0;
    local_1e = 0;
    local_1d = 0x1e;
    local_1c = 0;
    local_1b = 0;
    local_1a = 0xc6;
    local_19 = 0x11;
    local_18 = 0;
    local_17 = 0;
    local_16 = 0xc6;
    local_15 = 0x11;
    local_14 = 0;
    local_13 = 0;
    local_12 = 0;
    local_11 = 0;
    local_10 = 0;
    local_f = 0;
    local_e = 0;
    local_d = 0;
    local_c = 0;
    local_b = 0;
    local_2a = (undefined2)iVar2;
    pFVar1 = (FILE *)FUN_0041d331(local_144,&DAT_0042c5b4);
    _fwrite(&local_40,1,0x36,pFVar1);
    _fwrite(local_14c,1,iVar2 * local_158 * 4,pFVar1);
    _fclose(pFVar1);
    _free(local_15c);
    _free(local_14c);
  }
  (**(code **)(*local_154 + 8))(local_154);
  return;
}



// ==== 0x4151c2 ====

void FUN_004151c2(undefined *param_1,undefined4 param_2)

{
  DAT_00c0a4e8 = param_2;
  PTR_s_shot_0042cb0f_1_00453864 = param_1;
  FUN_00414f2b();
  return;
}



// ==== 0x4151d9 ====

void FUN_004151d9(void)

{
  int *piVar1;
  
  if (**(int **)(&DAT_00c0e1f8 + DAT_00c0e1f0 * 4) != 0) {
    piVar1 = (int *)**(int **)(&DAT_00c0e1f8 + DAT_00c0e1f0 * 4);
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  **(undefined4 **)(&DAT_00c0e1f8 + DAT_00c0e1f0 * 4) = 0;
  DAT_00c0e1f0 = DAT_00c0e1f0 + 1 & 0x3ff;
  return;
}



// ==== 0x415216 ====

int FUN_00415216(undefined4 param_1,float param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  uint in_ECX;
  int iVar4;
  uint local_8;
  
  if (DAT_00c0f224 == 0) {
    iVar2 = 0;
  }
  else {
    *(undefined4 *)(in_ECX + 0x1e4) = 0;
    local_8 = in_ECX;
    while (piVar1 = (int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4), *piVar1 != 0) {
      piVar1 = (int *)*piVar1;
      (**(code **)(*piVar1 + 0x24))(piVar1,&local_8);
      if (((local_8 & 1) == 0) ||
         (*(int *)(in_ECX + 0x1e4) = *(int *)(in_ECX + 0x1e4) + 1, 0x77 < *(int *)(in_ECX + 0x1e4)))
      break;
    }
    if (*(int *)(in_ECX + 0x1e4) == 0x78) {
      *(undefined4 *)(in_ECX + 0x1e4) = 0;
    }
    while (*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4) == 0) {
      iVar2 = (**(code **)(*DAT_00c0f1fc + 0x14))
                        (DAT_00c0f1fc,*(undefined4 *)(in_ECX + 4),
                         in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4);
      if (iVar2 == 0) {
        *(uint *)(&DAT_00c0e1f8 + DAT_00c0f1f8 * 4) = in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4;
        DAT_00c0f1f8 = DAT_00c0f1f8 + 1 & 0x3ff;
      }
      else {
        FUN_004151d9();
      }
    }
    piVar1 = (int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4);
    if (*piVar1 != 0) {
      piVar1 = (int *)*piVar1;
      iVar2 = *piVar1;
      uVar3 = FUN_0041d384();
      (**(code **)(iVar2 + 0x44))(piVar1,uVar3);
      FUN_0041cf20(0x4024000000000000);
      iVar2 = **(int **)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4);
      FUN_0041cf20((double)param_2);
      uVar3 = FUN_0041d384();
      (**(code **)(iVar2 + 0x3c))(*(undefined4 *)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4),uVar3);
      piVar1 = *(int **)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4);
      (**(code **)(*piVar1 + 0x34))(piVar1,0);
      piVar1 = *(int **)(in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4);
      (**(code **)(*piVar1 + 0x30))(piVar1,0,0,0);
    }
    iVar2 = in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4;
    iVar4 = *(int *)(in_ECX + 0x1e4) + 1;
    *(int *)(in_ECX + 0x1e4) = iVar4;
    if (iVar4 == 0x78) {
      *(undefined4 *)(in_ECX + 0x1e4) = 0;
    }
    *(uint *)(&DAT_00c0f200 + param_3 * 4) = in_ECX + 4 + *(int *)(in_ECX + 0x1e4) * 4;
  }
  return iVar2;
}



// ==== 0x41538b ====

void FUN_0041538b(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  
  FUN_0040d4e3(param_1,param_2,param_3,param_4);
  if (((param_4 != 0) && (piVar1 = *(int **)(&DAT_00c0f200 + param_4 * 4), piVar1 != (int *)0x0)) &&
     (*piVar1 != 0)) {
    (**(code **)(*(int *)*piVar1 + 0x48))((int *)*piVar1);
  }
  FUN_00415216(param_2,param_3,param_4);
  return;
}



// ==== 0x4153f4 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_004153f4(void)

{
  undefined *puVar1;
  ushort uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined **ppuVar6;
  undefined4 *puVar7;
  undefined4 local_d0;
  undefined4 uStack_cc;
  int iStack_c8;
  undefined4 uStack_c4;
  undefined2 uStack_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined *local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  void *local_a0;
  undefined4 local_9c;
  int local_98;
  undefined4 local_94;
  undefined4 local_68;
  int local_64;
  undefined4 local_60;
  void *local_5c;
  undefined4 local_58;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 uStack_50;
  undefined2 uStack_4e;
  int local_4c;
  undefined4 local_48;
  undefined2 local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 *local_38;
  int local_34;
  undefined **local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined **local_8;
  
  local_8 = DAT_00453d68;
  local_30 = &PTR_WAVE_0045386c;
  ppuVar6 = DAT_00453d68;
  if (PTR_WAVE_0045386c != (undefined *)0x0) {
    local_38 = &DAT_00c0a4f4;
    do {
      puVar1 = *local_30;
      local_a0 = operator_new(0x10000);
      local_ac = *(undefined4 *)(puVar1 + 0x38);
      local_b0 = puVar1 + 0x3c;
      local_bc = 0x54;
      local_b8 = 0;
      local_b4 = 0;
      local_a8 = 0;
      local_a4 = 0;
      local_9c = 0x10000;
      local_98 = 0;
      local_94 = 0;
      local_44 = 0;
      local_54 = 1;
      local_52 = *(undefined2 *)(puVar1 + 0x16);
      local_4c = *(int *)(puVar1 + 0x18);
      uStack_50 = (undefined2)local_4c;
      uStack_4e = (undefined2)((uint)local_4c >> 0x10);
      uVar2 = (short)*(undefined4 *)(puVar1 + 0x16) * 2;
      local_4c = (uint)uVar2 * local_4c;
      local_48 = CONCAT22(0x10,uVar2);
      local_5c = local_a0;
      uVar4 = acmStreamOpen(&local_40,0,puVar1 + 0x14,&local_54,0,0,0,4);
      if (((uVar4 != 0) || (uVar4 = acmStreamPrepareHeader(local_40,&local_bc,0), uVar4 != 0)) ||
         (uVar4 = acmStreamConvert(local_40,&local_bc,0x30), puVar3 = local_38, uVar4 != 0)) {
LAB_004155da:
        return uVar4 & 0xffffff00;
      }
      local_64 = CONCAT22(uStack_4e,uStack_50);
      local_d0 = CONCAT22(local_52,local_54);
      uStack_cc = CONCAT22(uStack_4e,uStack_50);
      iStack_c8 = local_4c;
      uStack_c4 = local_48;
      uStack_c0 = local_44;
      local_24 = local_98;
      local_3c = local_98;
      local_2c = 0x24;
      local_20 = 0;
      local_28 = (uint)(DAT_00453868 == 0) * 4 + 0x100b4;
      local_1c = &local_d0;
      local_18 = 0;
      uStack_14 = 0;
      uStack_10 = 0;
      uStack_c = 0;
      uVar4 = (**(code **)(*DAT_00c0f1fc + 0xc))(DAT_00c0f1fc,&local_2c,local_38,0);
      if (uVar4 != 0) goto LAB_004155da;
      (**(code **)(*(int *)*puVar3 + 0x2c))
                ((int *)*puVar3,0,0,&local_34,&local_60,&local_68,&local_58,2);
      iVar5 = 0;
      if (0 < local_3c) {
        do {
          *(undefined1 *)(iVar5 + local_34) = *(undefined1 *)(iVar5 + (int)local_5c);
          iVar5 = iVar5 + 1;
        } while (iVar5 < local_3c);
      }
      (**(code **)(*(int *)*puVar3 + 0x4c))((int *)*puVar3,local_34,local_60,local_68,local_58);
      puVar7 = puVar3;
      for (iVar5 = 0x77; puVar7 = puVar7 + 1, iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = 0;
      }
      iVar5 = local_64 / DAT_00453cdc;
      ppuVar6 = local_30 + 1;
      puVar3[0x78] = 0;
      local_38 = puVar3 + 0x7a;
      puVar3[-1] = iVar5;
      local_30 = ppuVar6;
    } while (*ppuVar6 != (undefined *)0x0);
  }
  return CONCAT31((int3)((uint)ppuVar6 >> 8),1);
}



// ==== 0x4155de ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_004155de(void)

{
  char cVar1;
  uint uVar2;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  uVar2 = DirectSoundCreate8(0,&DAT_00c0f1fc,0);
  if (uVar2 == 0) {
    (**(code **)(*DAT_00c0f1fc + 0x18))(DAT_00c0f1fc,DAT_00d0f4f0,2);
    local_2c = 0x24;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_28 = (uint)(DAT_00453868 == 0) * 4 + 0x15;
    local_18 = 0;
    uStack_14 = 0;
    uStack_10 = 0;
    uStack_c = 0;
    uVar2 = (**(code **)(*DAT_00c0f1fc + 0xc))(DAT_00c0f1fc,&local_2c,&DAT_00c0e1f4,0);
    if (uVar2 == 0) {
      cVar1 = FUN_004153f4();
      if (cVar1 != '\0') {
        DAT_00c0f224 = 1;
        return 1;
      }
      (**(code **)(*DAT_00c0e1f4 + 8))(DAT_00c0e1f4);
      uVar2 = (**(code **)(*DAT_00c0f1fc + 8))(DAT_00c0f1fc);
    }
  }
  return uVar2 & 0xffffff00;
}



// ==== 0x41569a ====

undefined1 FUN_0041569a(void)

{
  char cVar1;
  undefined1 uVar2;
  
  if (DAT_00c0f220 == '\0') {
    return 0;
  }
  DAT_00453868 = 1;
  cVar1 = FUN_004155de();
  if (cVar1 != '\0') {
    return 1;
  }
  DAT_00453868 = 0;
  uVar2 = FUN_004155de();
  return uVar2;
}



// ==== 0x4156c8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004156c8(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  int local_8;
  
  piVar4 = &DAT_00c0f338;
  fVar5 = (float10)FUN_0041cf20(0x3f947ae140000000);
  FUN_0041ce90((double)(fVar5 * (float10)0.03125));
  fVar5 = (float10)FUN_0041cf20(0x3f947ae140000000);
  FUN_0041ce90((double)(fVar5 * (float10)0.03125));
  fVar5 = (float10)FUN_0041cf20(0x3f947ae140000000);
  FUN_0041ce90((double)(fVar5 * (float10)0.03125));
  local_8 = 0x20;
  do {
    iVar1 = FUN_0041d384();
    iVar2 = FUN_0041d384();
    iVar3 = FUN_0041d384();
    *piVar4 = (iVar1 * 0x100 + iVar2) * 0x100 + iVar3;
    piVar4 = piVar4 + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  _DAT_00d0f338 = FUN_00415a5c(&DAT_00c0f338,0x20,1,1);
  return;
}



// ==== 0x4157bd ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004157bd(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  int local_14;
  int local_8;
  
  local_8 = 0;
  piVar4 = &DAT_00c0f338;
  do {
    fVar5 = (float10)FUN_0041cf20(0x3f847ae140000000);
    FUN_0041ce90((double)(fVar5 * (float10)0.015625));
    fVar5 = (float10)FUN_0041cf20(0x3f947ae140000000);
    FUN_0041ce90((double)(fVar5 * (float10)0.015625));
    fVar5 = (float10)FUN_0041cf20(0x3fa99999a0000000);
    FUN_0041ce90((double)(fVar5 * (float10)0.015625));
    local_14 = 0x40;
    do {
      iVar1 = FUN_0041d384();
      iVar2 = FUN_0041d384();
      iVar3 = FUN_0041d384();
      *piVar4 = (iVar1 * 0x100 + iVar2) * 0x100 + iVar3;
      piVar4 = piVar4 + 1;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
    local_8 = local_8 + 1;
  } while (local_8 < 0x10);
  _DAT_00c0f228 = FUN_00415a5c(&DAT_00c0f338,0x40,0x10,0);
  return;
}



// ==== 0x4158ca ====

void FUN_004158ca(void)

{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int local_c;
  int local_8;
  undefined4 local_4;
  
  FUN_004157bd();
  FUN_004156c8();
  DAT_00d102d1 = 1;
  DAT_00d102d0 = 1;
  iVar1 = FUN_00419980(&PTR_DAT_00453890,&DAT_004158c7);
  uVar4 = 0;
  if (PTR_DAT_00453890 != (undefined *)0x0) {
    local_c = iVar1 + -0xc0f230;
    do {
      local_4 = *(undefined4 *)((int)&DAT_00c0f230 + uVar4 * 4 + local_c);
      iVar1 = (int)uVar4 / 2 + -4;
      if (((7 < (int)uVar4) && ((int)uVar4 < 0x12)) &&
         (pcVar6 = s_2_players_duel_004538f0 + iVar1 * 0x90, *pcVar6 != '\0')) {
        local_8 = 6;
        pcVar5 = s_2_players_duel_004538f0 + iVar1 * 0x90;
        do {
          FUN_00403e16(local_4,pcVar6,10,local_8,0x100,0xf6,0x20,0x18,(uVar4 & 1) * 0x7f7f7f,
                       0xffffff,"Times New Roman");
          local_8 = local_8 + 0x2a;
          pcVar6 = pcVar5 + 0x18;
          pcVar5 = pcVar6;
        } while (*pcVar6 != '\0');
      }
      if ((uVar4 & 1) == 0) {
        uVar2 = FUN_00415ae1(local_4,0x100,0x100,0xffffff9c);
      }
      else {
        uVar2 = FUN_00415a5c(local_4,0x100,0x100,0);
      }
      (&DAT_00c0f230)[uVar4] = uVar2;
      uVar4 = uVar4 + 1;
    } while ((&PTR_DAT_00453890)[uVar4] != (undefined *)0x0);
  }
  puVar7 = &DAT_00c0f338;
  for (iVar1 = 0x10000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar7 = 0xffffffff;
    puVar7 = puVar7 + 1;
  }
  uVar4 = 0;
  do {
    local_c._0_2_ = (ushort)(byte)uVar4;
    FUN_00403e16(&DAT_00c0f338,&local_c,(uVar4 & 0xf) << 4,(int)uVar4 / 0x10 << 4,0x100,0x10,0x10,
                 0xc,0,0xffffff,"Lucida Console");
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x100);
  puVar3 = &DAT_00c0f338;
  do {
    *puVar3 = ~*puVar3;
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0xc4f338);
  DAT_00c0f22c = FUN_00415a5c(&DAT_00c0f338,0x100,0x100,0);
  return;
}



// ==== 0x415a5c ====

int * FUN_00415a5c(void *param_1,int param_2,int param_3,int *param_4)

{
  void *_Dst;
  int local_14;
  void *local_10;
  int local_c;
  size_t local_8;
  
  (**(code **)(*DAT_004571ec + 0x5c))
            (DAT_004571ec,param_2,param_3,param_4,((uint)param_4 ^ 1) << 10,0x15,1,&param_4,0);
  (**(code **)(*param_4 + 0x4c))(param_4,0,&local_14,0,0);
  if (0 < param_3) {
    local_8 = param_2 << 2;
    local_c = param_3;
    _Dst = local_10;
    do {
      _memcpy(_Dst,param_1,local_8);
      _Dst = (void *)((int)_Dst + local_14);
      param_1 = (void *)((int)param_1 + local_8);
      local_c = local_c + -1;
    } while (local_c != 0);
  }
  (**(code **)(*param_4 + 0x50))(param_4,0);
  return param_4;
}



// ==== 0x415ae1 ====

undefined4 FUN_00415ae1(byte *param_1,int param_2,int param_3,int param_4)

{
  char *_Memory;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  char *pcVar7;
  int iVar8;
  int local_10;
  int local_c;
  
  _Memory = operator_new(param_2 * param_3 * 4);
  if (0 < param_3) {
    iVar1 = param_2 << 2;
    local_10 = param_3;
    pbVar5 = param_1 + (param_3 + -1) * param_2 * 4;
    pcVar7 = _Memory;
    do {
      if (0 < param_2) {
        pbVar4 = param_1 + iVar1 + -4;
        pbVar6 = param_1;
        local_c = param_2;
        do {
          iVar8 = (uint)*pbVar6 - (uint)*pbVar4;
          iVar1 = (uint)*pbVar6 - (uint)pbVar6[(int)pbVar5 - (int)param_1];
          FUN_0041d134((double)(iVar8 * iVar8 + iVar1 * iVar1 + param_4 * param_4));
          iVar2 = FUN_0041d384();
          *pcVar7 = (char)((iVar8 * 0x100) / iVar2) + '\x7f';
          pcVar7[1] = (char)((iVar1 * 0x100) / iVar2) + '\x7f';
          pcVar7[2] = (char)((param_4 << 8) / iVar2) + '\x7f';
          pcVar7[3] = '\0';
          pcVar7 = pcVar7 + 4;
          local_c = local_c + -1;
          pbVar4 = pbVar6;
          pbVar6 = pbVar6 + 4;
        } while (local_c != 0);
      }
      iVar1 = param_2 * 4;
      local_10 = local_10 + -1;
      pbVar5 = param_1;
      param_1 = param_1 + iVar1;
    } while (local_10 != 0);
  }
  uVar3 = FUN_00415a5c(_Memory,param_2,param_3,0);
  _free(_Memory);
  return uVar3;
}



// ==== 0x415c17 ====

void FUN_00415c17(undefined4 param_1,undefined4 param_2)

{
  (**(code **)(*DAT_004571ec + 0x104))(DAT_004571ec,param_1,param_2);
  return;
}



// ==== 0x415c2e ====

void FUN_00415c2e(void)

{
  DAT_00d0f35c = 0;
  DAT_00d0f350 = 0x280;
  DAT_00d0f354 = 0x1e0;
  DAT_00d0f358 = 0x20;
  DAT_00d0f360 = 2;
  DAT_00d0f364 = 1;
  return;
}



// ==== 0x415c68 ====

void FUN_00415c68(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 local_14 [4];
  
  piVar2 = param_1;
  piVar3 = &DAT_00d0f390;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar3 = piVar3 + 1;
  }
  local_14[0] = 1;
  DAT_00c0f220 = param_1[5] != 0;
  local_14[1] = 2;
  local_14[2] = 4;
  local_14[3] = 0xc;
  DAT_00453700 = local_14[param_1[4]];
  DAT_004536fc = (uint)(param_1[4] != 0);
  DAT_00457334 = *param_1;
  DAT_00457338 = param_1[1];
  DAT_004571f4 = param_1[2];
  DAT_004571f0 = param_1[3];
  DAT_0045733c = '\x01' - (param_1[1] * *param_1 != 0);
  return;
}



// ==== 0x415cf8 ====

void FUN_00415cf8(void)

{
  LRESULT LVar1;
  undefined4 *puVar2;
  
  DAT_0045733c = 0;
  LVar1 = SendMessageA(DAT_00d0f388,0x188,0,0);
  if (LVar1 + -1 == -1) {
    DAT_00d0f350 = 0;
    DAT_00d0f354 = 0;
    DAT_00d0f358 = 0;
    DAT_00d0f35c = 0;
  }
  else {
    puVar2 = (undefined4 *)((LVar1 + -1) * 0x10 + DAT_00d0f368);
    DAT_00d0f350 = *puVar2;
    DAT_00d0f354 = puVar2[1];
    DAT_00d0f358 = puVar2[2];
    DAT_00d0f35c = puVar2[3];
  }
  DAT_00d0f360 = SendMessageA(DAT_00d0f344,0x188,0,0);
  DAT_00d0f364 = SendMessageA(DAT_00d0f36c,0x188,0,0);
  FUN_00415c68(&DAT_00d0f350);
  return;
}



// ==== 0x415d81 ====

void FUN_00415d81(void)

{
  DAT_00d0f37c = CreateWindowExA(0,"edit","Homepage: http://www.gravitysensation.com/sumotori/",
                                 0x50000800,10,0x145,500,0x19,DAT_00d0f33c,(HMENU)0x0,DAT_00d0f4e8,
                                 (LPVOID)0x0);
  DAT_00d0f380 = CreateWindowExA(0,"edit","Thanks for purchasing Sumotori Dreams!   ENJOY!",
                                 0x50000800,10,300,500,0x19,DAT_00d0f33c,(HMENU)0x0,DAT_00d0f4e8,
                                 (LPVOID)0x0);
  return;
}



// ==== 0x415df1 ====

void FUN_00415df1(void)

{
  if (DAT_00d0f34c != (HWND)0x0) {
    DestroyWindow(DAT_00d0f37c);
    DAT_00d0f37c = (HWND)0x0;
    DestroyWindow(DAT_00d0f380);
    DAT_00d0f380 = (HWND)0x0;
    DestroyWindow(DAT_00d0f34c);
    DAT_00d0f34c = (HWND)0x0;
    FUN_00415d81();
    return;
  }
  return;
}



// ==== 0x415e35 ====

void FUN_00415e35(void)

{
  LSTATUS LVar1;
  HKEY local_8;
  
  LVar1 = RegCreateKeyA((HKEY)0x80000001,"Software\\Archee\\Sumotori",&local_8);
  if (LVar1 == 0) {
    RegSetValueExA(local_8,"configf",0,3,(BYTE *)&DAT_00d0f350,0x18);
    RegCloseKey(local_8);
  }
  return;
}



// ==== 0x415e74 ====

void FUN_00415e74(void)

{
  LSTATUS LVar1;
  DWORD local_c;
  HKEY local_8;
  
  FUN_00415c2e();
  LVar1 = RegOpenKeyExA((HKEY)0x80000001,"Software\\Archee\\Sumotori",0,0x20019,&local_8);
  if (LVar1 == 0) {
    local_c = 0x18;
    RegQueryValueExA(local_8,"configf",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&DAT_00d0f350,&local_c);
    RegCloseKey(local_8);
  }
  FUN_00415c68(&DAT_00d0f350);
  return;
}



// ==== 0x4160fe ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004160fe(void)

{
  int iVar1;
  char *local_110;
  int *local_10c;
  WPARAM local_108;
  char local_104 [256];
  undefined4 local_4;
  
  local_4 = DAT_00453d68;
  _DAT_00d0f38c =
       CreateWindowExA(0,"edit","System Settings",0x50000800,10,0,0x17c,0x14,DAT_00d0f33c,(HMENU)0x0
                       ,DAT_00d0f4e8,(LPVOID)0x0);
  DAT_00d0f388 = CreateWindowExA(0,"listbox","drivers",0x50200001,400,10,0xb4,0x118,DAT_00d0f33c,
                                 (HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  DAT_00d0f344 = CreateWindowExA(0,"listbox","drivers",0x50200001,10,0x1e,0x17c,0x78,DAT_00d0f33c,
                                 (HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  DAT_00d0f36c = CreateWindowExA(0,"listbox","sound",0x50200001,10,0xbe,0xb4,0x3c,DAT_00d0f33c,
                                 (HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  SendMessageA(DAT_00d0f36c,0x180,0,0x42cce8);
  SendMessageA(DAT_00d0f36c,0x180,0,0x42ccdc);
  FUN_00403a86(0,&DAT_00d0f368,&DAT_00d0f3a8);
  SendMessageA(DAT_00d0f388,0x180,0,0x42ccc8);
  local_108 = 0;
  local_10c = DAT_00d0f368;
  local_110 = (char *)0x0;
  if (0 < DAT_00d0f3a8) {
    do {
      _sprintf(local_104,"%dx%d %dbpp",*local_10c,local_10c[1],local_10c[2],local_10c[3]);
      SendMessageA(DAT_00d0f388,0x180,0,(LPARAM)local_104);
      if ((((*local_10c == DAT_00457334) && (local_10c[1] == DAT_00457338)) &&
          (local_10c[2] == DAT_004571f4)) && (local_10c[3] == DAT_004571f0)) {
        local_108 = (int)local_110 + 1;
      }
      local_10c = local_10c + 4;
      local_110 = (char *)((int)local_110 + 1);
    } while ((int)local_110 < DAT_00d0f3a8);
  }
  SendMessageA(DAT_00d0f388,0x186,local_108,local_108);
  local_110 = s_No_Shadow_00453bc8;
  do {
    SendMessageA(DAT_00d0f344,0x180,0,(LPARAM)local_110);
    local_110 = local_110 + 0x40;
  } while ((int)local_110 < 0x453cc8);
  SendMessageA(DAT_00d0f344,0x186,DAT_00d0f360,DAT_00d0f360);
  SendMessageA(DAT_00d0f36c,0x186,DAT_00d0f364,DAT_00d0f364);
  DAT_00d0f384 = CreateWindowExA(0,"button","PLAY MOD",0x50000000,0x1cc,0x172,0x78,0x14,DAT_00d0f33c
                                 ,(HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  DAT_00d0f378 = CreateWindowExA(0,"button","PLAY GAME",0x50000000,300,0x19a,0xb4,0x14,DAT_00d0f33c,
                                 (HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  DAT_00d0f374 = CreateWindowExA(0,"button","QUIT",0x50000000,500,0x19a,0x50,0x14,DAT_00d0f33c,
                                 (HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  iVar1 = FUN_0040461e();
  if (iVar1 == 0) {
    DAT_00d0f380 = CreateWindowExA(0,"edit",
                                   "Visit http://www.gravitysensation.com/sumotori/ to get a license."
                                   ,0x50000800,10,300,500,0x19,DAT_00d0f33c,(HMENU)0x0,DAT_00d0f4e8,
                                   (LPVOID)0x0);
    DAT_00d0f37c = CreateWindowExA(0,"edit","Type the license key below:",0x50000800,10,0x145,500,
                                   0x19,DAT_00d0f33c,(HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
    DAT_00d0f34c = CreateWindowExA(0,"edit","",0x50000008,10,0x168,400,0x19,DAT_00d0f33c,(HMENU)0x0,
                                   DAT_00d0f4e8,(LPVOID)0x0);
  }
  else {
    FUN_00415d81();
  }
  return;
}



// ==== 0x416461 ====

int FUN_00416461(LPCSTR param_1)

{
  int iVar1;
  ATOM AVar2;
  WNDCLASSA local_58;
  MSG local_30;
  tagRECT local_14;
  
  if (DAT_00d0f3b0 == 0) {
    DAT_00d0f3b0 = 1;
    local_58.style = 8;
    local_58.lpfnWndProc = (WNDPROC)&LAB_00415ed4;
    local_58.cbClsExtra = 0;
    local_58.cbWndExtra = 0;
    local_58.hInstance = DAT_00d0f4e8;
    local_58.hIcon = (HICON)0x0;
    local_58.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_58.hbrBackground = CreateSolidBrush(0xd0c0c0);
    local_58.lpszMenuName = (LPCSTR)0x0;
    local_58.lpszClassName = "archeecfg";
    AVar2 = RegisterClassA(&local_58);
    if (AVar2 == 0) {
      return 0;
    }
  }
  local_14.left = 0;
  local_14.right = 600;
  local_14.bottom = 0x1cc;
  local_14.top = 0;
  AdjustWindowRect(&local_14,0xca0000,0);
  DAT_00d0f33c = CreateWindowExA(0x40000,"archeecfg",param_1,0xca0000,-0x80000000,-0x80000000,
                                 local_14.right - local_14.left,local_14.bottom - local_14.top,
                                 (HWND)0x0,(HMENU)0x0,DAT_00d0f4e8,(LPVOID)0x0);
  ShowWindow(DAT_00d0f33c,1);
  SetCursor((HCURSOR)0x0);
  FUN_004160fe();
  DAT_00d0f3ac = 0;
  while (GetMessageA(&local_30,(HWND)0x0,0,0), iVar1 = DAT_00d0f3ac, DAT_00d0f3ac == 0) {
    TranslateMessage(&local_30);
    DispatchMessageA(&local_30);
  }
  DestroyWindow(DAT_00d0f33c);
  return iVar1;
}



// ==== 0x416594 ====

void FUN_00416594(void)

{
  undefined1 *puVar1;
  void *pvVar2;
  undefined4 *in_ECX;
  uint _NewSize;
  uint uVar3;
  
  uVar3 = in_ECX[1] - (int)*in_ECX >> 2;
  _NewSize = ((uVar3 >> 3) + 1 + uVar3) * 4;
  if (0xfffffff < _NewSize) {
    puVar1 = (undefined1 *)0x0;
    do {
      puVar1 = puVar1 + 1;
      *puVar1 = 0x7f;
    } while( true );
  }
  pvVar2 = _realloc((void *)*in_ECX,_NewSize);
  *in_ECX = pvVar2;
  in_ECX[2] = (void *)(_NewSize + (int)pvVar2);
  in_ECX[1] = (void *)((int)pvVar2 + uVar3 * 4);
  return;
}



// ==== 0x4165db ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_004165db(void)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_8;
  
  uVar5 = DAT_00c06978 / 3;
  if ((DAT_00c06978 % 3 == 0) && (uVar5 = DAT_00d0f3c0, DAT_00d0f3bc < DAT_00d0f3c0)) {
    local_8 = 0;
    iVar2 = DAT_00453cc8;
    iVar6 = DAT_00453ccc;
    if (DAT_00453ccc != 1 && -1 < DAT_00453ccc + -1) {
      iVar7 = DAT_00453cc8 + -1;
      do {
        iVar8 = 0;
        if (0 < iVar7) {
          do {
            pfVar3 = (float *)FUN_00408f5e(iVar2 * local_8 + iVar8);
            pfVar4 = (float *)FUN_00408f5e(DAT_00453cc8 * local_8 + 1 + iVar8);
            fVar1 = (*pfVar3 - *pfVar4) * 0.09;
            pfVar3 = (float *)FUN_00408f5e(DAT_00453cc8 * local_8 + iVar8);
            *pfVar3 = *pfVar3 - fVar1;
            pfVar3 = (float *)FUN_00408f5e(DAT_00453cc8 * local_8 + 1 + iVar8);
            *pfVar3 = fVar1 + *pfVar3;
            pfVar3 = (float *)FUN_00408f5e(DAT_00453cc8 * local_8 + iVar8);
            pfVar4 = (float *)FUN_00408f5e((local_8 + 1) * DAT_00453cc8 + iVar8);
            fVar1 = (*pfVar3 - *pfVar4) * 0.09;
            pfVar3 = (float *)FUN_00408f5e(DAT_00453cc8 * local_8 + iVar8);
            *pfVar3 = *pfVar3 - fVar1;
            pfVar3 = (float *)FUN_00408f5e((local_8 + 1) * DAT_00453cc8 + iVar8);
            iVar8 = iVar8 + 1;
            *pfVar3 = fVar1 + *pfVar3;
            iVar7 = DAT_00453cc8 + -1;
            iVar2 = DAT_00453cc8;
            iVar6 = DAT_00453ccc;
          } while (iVar8 < iVar7);
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar6 + -1);
    }
    local_8 = 0;
    fVar1 = 0.0;
    if (0 < iVar2 * iVar6) {
      do {
        pfVar3 = (float *)FUN_00408f5e(local_8);
        fVar1 = *pfVar3 + fVar1;
        pfVar3 = (float *)FUN_00408f5e(local_8);
        pfVar4 = (float *)FUN_00408f5e(local_8);
        *pfVar3 = *pfVar3 + *pfVar4 + _DAT_00d0f3b4;
        pfVar3 = (float *)FUN_00408f5e(local_8);
        local_8 = local_8 + 1;
        *pfVar3 = *pfVar3 * 0.997;
        iVar2 = DAT_00453cc8;
        iVar6 = DAT_00453ccc;
      } while (local_8 < DAT_00453cc8 * DAT_00453ccc);
    }
    uVar5 = iVar2 * iVar6;
    _DAT_00d0f3b4 = (_DAT_00453cd4 - fVar1 / (float)(int)uVar5) * 0.1;
  }
  return uVar5;
}



// ==== 0x4167d2 ====

void FUN_004167d2(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *in_ECX;
  
  iVar2 = *in_ECX;
  puVar3 = (undefined4 *)in_ECX[1];
  uVar1 = iVar2 + param_1 * 4;
  in_ECX[1] = uVar1;
  if ((uint)in_ECX[2] < uVar1) {
    FUN_00416594();
    puVar3 = (undefined4 *)(*in_ECX + ((int)puVar3 - iVar2 >> 2) * 4);
  }
  for (; puVar3 < (undefined4 *)in_ECX[1]; puVar3 = puVar3 + 1) {
    *puVar3 = 0;
  }
  return;
}



// ==== 0x416810 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00416810(void)

{
  float *pfVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined4 local_8;
  
  _DAT_00453cd4 = 23.0;
  DAT_00d0f3b8 = 1;
  FUN_004167d2();
  FUN_004167d2();
  local_8 = 0;
  if (0 < DAT_00453ccc * DAT_00453cc8) {
    do {
      fVar3 = (float10)FUN_0041d084((double)((float)local_8 * 0.5));
      pfVar1 = (float *)FUN_00408f5e();
      *pfVar1 = (float)fVar3 * 0.04 + _DAT_00453cd4;
      puVar2 = (undefined4 *)FUN_00408f5e();
      local_8 = local_8 + 1;
      *puVar2 = 0;
    } while (local_8 < DAT_00453ccc * DAT_00453cc8);
  }
  return;
}



// ==== 0x4168c7 ====

void FUN_004168c7(void)

{
  BOOL BVar1;
  MSG local_20;
  
  while( true ) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return;
}



// ==== 0x416900 ====

void FUN_00416900(void)

{
  return;
}



// ==== 0x41690d ====

undefined4 FUN_0041690d(void)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  return (int)((((longlong)(int)DVar1 * (longlong)DAT_00453cd8 & 0xffffffffU) / 1000) /
              (ulonglong)DAT_00453cdc);
}



// ==== 0x41692c ====

void FUN_0041692c(void)

{
  DestroyWindow(DAT_00d0f4f0);
  FUN_00407da3();
                    /* WARNING: Subroutine does not return */
  _exit(0);
}



// ==== 0x416945 ====

void FUN_00416945(undefined4 param_1,undefined4 param_2)

{
  if (DAT_00d0fa00 == '\0') {
    DAT_00d0fa00 = '\x01';
    DAT_00d0f3dc = (FILE *)FUN_0041d331("debug.!",&DAT_0042b29c);
    _fclose(DAT_00d0f3dc);
  }
  DAT_00d0f3dc = (FILE *)FUN_0041d331("debug.!",&DAT_0042b280);
  _fprintf(DAT_00d0f3dc,"%s %d\n",param_1,param_2);
  _fclose(DAT_00d0f3dc);
  return;
}



// ==== 0x4169a7 ====

void FUN_004169a7(byte param_1)

{
  if (DAT_00453ce4 != param_1) {
    DAT_00453ce4 = param_1;
    ShowCursor((uint)param_1);
  }
  return;
}



// ==== 0x4169c3 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT FUN_004169c3(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  uint uVar1;
  LRESULT LVar2;
  
  if (param_2 == 0x10) {
    LVar2 = 0;
  }
  else {
    if (param_2 == 0x100) {
      uVar1 = (int)param_4 >> 0x10 & 0xff;
      if (uVar1 == 1) {
        DAT_00d0fa08 = 1;
      }
      (&DAT_00d0f3e0)[uVar1] = 1;
      (&DAT_00d0f4f8)[uVar1] = 1;
    }
    else if (param_2 == 0x101) {
      (&DAT_00d0f3e0)[param_4 >> 0x10 & 0xff] = 0;
    }
    else if (param_2 == 0x201) {
      DAT_00453ce0 = param_4 & 0xffff;
      _DAT_00d0fa04 = param_4 >> 0x10;
    }
    LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  return LVar2;
}



// ==== 0x416a3e ====

undefined4 FUN_00416a3e(undefined4 param_1,undefined4 param_2,char *param_3)

{
  code *pcVar1;
  HANDLE hProcess;
  int iVar2;
  HWND hWnd;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  DWORD dwPriorityClass;
  WNDCLASSEXA local_34;
  
  DAT_00d0f4e8 = param_1;
  if ((DAT_00d0f3d8 != (char *)0x0) && (*DAT_00d0f3d8 != '\0')) {
    FUN_00403fbd(DAT_00d0f3d8);
  }
  dwPriorityClass = 0x80;
  hProcess = GetCurrentProcess();
  SetPriorityClass(hProcess,dwPriorityClass);
  if (DAT_00d0f9f8 == 0) {
    FUN_00415e74();
    iVar2 = FUN_00416461("Sumotori Dreams Full Version");
    if (iVar2 == 2) {
      return 0;
    }
    if (DAT_00d0f9f8 == 0) goto LAB_00416aaf;
  }
  DAT_0045733c = 1;
LAB_00416aaf:
  if (*param_3 == '_') {
    DAT_00453700 = 2;
    DAT_004536fc = 0;
  }
  local_34.cbSize = 0x30;
  local_34.style = 0x40;
  local_34.lpfnWndProc = FUN_004169c3;
  local_34.cbClsExtra = 0;
  local_34.cbWndExtra = 0;
  local_34.hInstance = GetModuleHandleA((LPCSTR)0x0);
  local_34.hIcon = (HICON)0x0;
  local_34.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_34.hbrBackground = (HBRUSH)0x0;
  local_34.lpszMenuName = (LPCSTR)0x0;
  local_34.lpszClassName = "archee";
  local_34.hIconSm = (HICON)0x0;
  RegisterClassExA(&local_34);
  hWnd = (HWND)FUN_00403bb8(param_1);
  DAT_00d0f4f0 = hWnd;
  ShowWindow(hWnd,1);
  UpdateWindow(hWnd);
  FUN_004168c7();
  FUN_00403c36();
  FUN_0041569a();
  if (DAT_00d0f9f8 != 0) {
    FUN_00406d45(param_1);
  }
  FUN_00407d6b();
  FUN_0040e1af();
  iVar2 = DAT_00d0f4ec;
  while (DAT_00d0f9fc == 0) {
    iVar3 = FUN_0041690d();
    if (iVar2 < iVar3) {
      if (DAT_00d0f3ea != '\0') {
        FUN_0040e1d2(0);
        FUN_0040e1d2(0);
        FUN_0040e1d2(0);
      }
      iVar4 = iVar3 - (iVar2 + 1);
      iVar2 = iVar2 + 1;
      if (0x14 < iVar4) {
        iVar2 = iVar3;
      }
      FUN_0040e1d2(CONCAT31((int3)((uint)iVar4 >> 8),iVar2 == iVar3));
      if (DAT_00d0f3e9 != '\0') {
        iVar2 = iVar2 + 3;
      }
      if (DAT_00d0f500 != '\0') {
        DAT_00d0fa10 = DAT_00d0fa10 ^ 1;
        DAT_00d0f500 = '\0';
      }
    }
    else {
      Sleep(0);
    }
    FUN_004168c7();
  }
  FUN_0040d623();
  FUN_0041692c();
  pcVar1 = (code *)swi(3);
  uVar5 = (*pcVar1)();
  return uVar5;
}



// ==== 0x416be4 ====

void FUN_00416be4(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x13c) = param_2;
  uVar1 = FUN_0041d384();
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  return;
}



// ==== 0x416c19 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00416c19(int param_1)

{
  if (param_1 != 0) {
    DAT_00d0fe20 = 1;
    do {
    } while (DAT_00d0fe21 != '\0');
    if (DAT_00d0fe24 != 0) {
      while (DAT_00453cec == '\0') {
        Sleep(0x32);
      }
      DAT_00d0fe24 = 0;
    }
    if (DAT_00d15fc8 != (void *)0x0) {
      _free(DAT_00d15fc8);
      DAT_00d15fc8 = (void *)0x0;
    }
    if (DAT_00d17720 != 0) {
      waveOutUnprepareHeader(DAT_00d17744,(LPWAVEHDR)&DAT_00d17720,0x20);
      _DAT_00d17730 = _DAT_00d17730 & 0xfffffffd;
    }
    DAT_00d0fa14 = 0;
    if (DAT_00d175b0 != (void *)0x0) {
      _free(DAT_00d175b0);
      DAT_00d175b0 = (void *)0x0;
    }
    return 1;
  }
  return 0;
}



// ==== 0x416cad ====

undefined4 FUN_00416cad(int *param_1)

{
  undefined4 *_Memory;
  void *_Memory_00;
  int *piVar1;
  int *_Memory_01;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int local_c;
  int local_8;
  
  _Memory_01 = param_1;
  if (param_1 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    do {
    } while (DAT_00d0fe21 != '\0');
    FUN_00416c19(param_1);
    if ((param_1[1] != 0) && (local_c = 0, 0 < (short)param_1[8])) {
      local_8 = 0;
      do {
        piVar3 = (int *)(_Memory_01[1] + local_8);
        param_1 = (int *)0x0;
        piVar1 = piVar3;
        if (0 < *piVar3) {
          do {
            _Memory = (undefined4 *)piVar1[1];
            if (_Memory != (undefined4 *)0x0) {
              _free((void *)*_Memory);
              _free(_Memory);
            }
            param_1 = (int *)((int)param_1 + 1);
            piVar1 = piVar1 + 1;
          } while ((int)param_1 < *piVar3);
        }
        local_c = local_c + 1;
        local_8 = local_8 + 0x154;
      } while (local_c < (short)_Memory_01[8]);
    }
    if ((void *)_Memory_01[1] != (void *)0x0) {
      _free((void *)_Memory_01[1]);
    }
    if (*_Memory_01 != 0) {
      iVar4 = 0;
      if (0 < _Memory_01[7]) {
        do {
          _Memory_00 = *(void **)(*_Memory_01 + 4 + iVar4 * 8);
          if (_Memory_00 != (void *)0x0) {
            _free(_Memory_00);
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < _Memory_01[7]);
      }
      if ((void *)*_Memory_01 != (void *)0x0) {
        _free((void *)*_Memory_01);
      }
    }
    _free(_Memory_01);
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 0x416d7e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00416d7e(DWORD param_1)

{
  DWORD DVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  size_t _Count;
  
  DVar1 = param_1;
  iVar2 = DAT_00d17560 / DAT_00d15fc4;
  if (param_1 == 0) {
    uVar3 = 0;
  }
  else {
    FUN_00416c19(param_1);
    *(uint *)(DVar1 + 300) = (uint)*(byte *)(DVar1 + 0x128);
    *(int *)(DVar1 + 0x138) = (int)*(short *)(DVar1 + 0x24);
    *(undefined4 *)(DVar1 + 0x140) = 0;
    uVar3 = DAT_00d0fa18;
    *(undefined4 *)(DVar1 + 0x150) = 0xffffffff;
    *(undefined4 *)(DVar1 + 0x14c) = 0xffffffff;
    *(undefined4 *)(DVar1 + 0x144) = uVar3;
    *(undefined4 *)(DVar1 + 8) = 0;
    *(undefined4 *)(DVar1 + 0x134) = 0;
    *(undefined4 *)(DVar1 + 0x148) = 0;
    *(undefined4 *)(DVar1 + 0x154) = 0;
    if (*(code **)(DVar1 + 0x158) != (code *)0x0) {
      (**(code **)(DVar1 + 0x158))(DVar1);
    }
    FUN_00416be4(DVar1,(int)*(short *)(DVar1 + 0x26));
    _memset(&DAT_00d15fe0,0,*(short *)(DVar1 + 0x14) * 0xac);
    param_1 = 0;
    if (0 < *(short *)(DVar1 + 0x14)) {
      puVar5 = &DAT_00d15fe4;
      puVar4 = &DAT_00d107c0;
      do {
        param_1 = param_1 + 1;
        *puVar5 = puVar4;
        puVar4 = puVar4 + 0x16;
        puVar5 = puVar5 + 0x2b;
      } while ((int)param_1 < (int)*(short *)(DVar1 + 0x14));
    }
    DAT_00d0fa14 = DVar1;
    DAT_00d175b0 = _calloc(iVar2 * 6,1);
    _Count = DAT_00d17560 << 2;
    DAT_00d17720 = _calloc(_Count,1);
    _DAT_00d17734 = 0xffffffff;
    _DAT_00d17730 = 0xc;
    _DAT_00d17728 = 0;
    _DAT_00d1772c = 0;
    _DAT_00d17724 = _Count;
    DAT_00d17740 = DAT_00d17720;
    waveOutPrepareHeader(DAT_00d17744,(LPWAVEHDR)&DAT_00d17720,0x20);
    DAT_00d15fc8 = _calloc(DAT_00d17560 * 8 + 0x100,1);
    DAT_00d15fc0 = (int)DAT_00d15fc8 + 0xfU & 0xfffffff0;
    DAT_00d0fe28 = 0;
    do {
      FUN_00416fa9();
    } while (DAT_00d0fe28 != 0);
    waveOutWrite(DAT_00d17744,(LPWAVEHDR)&DAT_00d17720,0x20);
    DAT_00d0fe20 = 0;
    DAT_00d0fe24 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00417121,(LPVOID)0x0,0,&param_1);
    SetThreadPriority(DAT_00d0fe24,0xf);
    uVar3 = 1;
  }
  return uVar3;
}



// ==== 0x416f38 ====

void * FUN_00416f38(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  
  pvVar2 = _calloc(0x164,1);
  iVar3 = FUN_00419090(param_1,0,0);
  if (iVar3 != 0) {
    *(undefined4 *)((int)pvVar2 + 0x160) = param_2;
    cVar1 = FUN_0041897e(pvVar2,iVar3);
    FUN_004190cc(iVar3);
    if (cVar1 != '\0') {
      return pvVar2;
    }
    FUN_00416cad(pvVar2);
  }
  return (void *)0x0;
}



// ==== 0x416f90 ====

void FUN_00416f90(void)

{
  waveOutReset(DAT_00d17744);
  waveOutClose(DAT_00d17744);
  return;
}



// ==== 0x416fa9 ====

void FUN_00416fa9(void)

{
  void *_Dst;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *local_c;
  int local_8;
  
  iVar2 = DAT_00d17560 / (int)DAT_00d15fc4;
  iVar5 = DAT_00d0fe28 * DAT_00d15fc4;
  _Dst = (void *)(DAT_00d15fc0 + iVar5 * 8);
  _memset(_Dst,0,DAT_00d15fc4 << 3);
  local_8 = 0;
  iVar4 = *(int *)(DAT_00d0fa14 + 8);
  local_c = _Dst;
  if (0 < (int)DAT_00d15fc4) {
    do {
      if (iVar4 == 0) {
        (**(code **)(DAT_00d0fa14 + 0x15c))(DAT_00d0fa14);
        iVar4 = *(int *)(DAT_00d0fa14 + 0xc);
      }
      iVar3 = iVar4;
      if ((int)DAT_00d15fc4 < iVar4 + local_8) {
        iVar3 = DAT_00d15fc4 - local_8;
      }
      FUN_00417379(local_c,iVar3,0);
      iVar1 = DAT_00d0fa14;
      local_8 = local_8 + iVar3;
      local_c = (void *)((int)local_c + iVar3 * 8);
      iVar4 = iVar4 - iVar3;
      iVar3 = FUN_0041d384();
      *(int *)(iVar1 + 0x154) = *(int *)(iVar1 + 0x154) + iVar3;
    } while (local_8 < (int)DAT_00d15fc4);
  }
  *(undefined4 *)(DAT_00d175b0 + 2 + DAT_00d0fe28 * 6) = *(undefined4 *)(DAT_00d0fa14 + 0x154);
  *(undefined1 *)(DAT_00d175b0 + 1 + DAT_00d0fe28 * 6) = *(undefined1 *)(DAT_00d0fa14 + 0x140);
  *(undefined1 *)(DAT_00d175b0 + DAT_00d0fe28 * 6) = *(undefined1 *)(DAT_00d0fa14 + 0x144);
  *(int *)(DAT_00d0fa14 + 8) = iVar4;
  FUN_00417320(DAT_00d17740 + iVar5 * 4,_Dst,DAT_00d15fc4 & 0x3fffffff);
  DAT_00d0fe28 = DAT_00d0fe28 + 1;
  if (iVar2 <= DAT_00d0fe28) {
    DAT_00d0fe28 = 0;
  }
  return;
}



// ==== 0x417121 ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_00417121(void)

{
  int iVar1;
  int iVar2;
  mmtime_tag local_14;
  undefined4 local_8;
  
  iVar1 = DAT_00d17560 / DAT_00d15fc4;
  DAT_00453cec = 0;
  local_8 = DAT_00453d68;
  while (DAT_00d0fe20 == '\0') {
    local_14.wType = 4;
    waveOutGetPosition(DAT_00d17744,&local_14,0xc);
    local_14.u.ms = local_14.u.ms >> 2;
    iVar2 = ((int)local_14.u.ms % DAT_00d17560) / DAT_00d15fc4;
    while (DAT_00d0fe28 != iVar2) {
      DAT_00d0fe21 = 1;
      FUN_00416fa9();
      DAT_00d0fe2c = DAT_00d0fe2c + 1;
      if (iVar1 <= DAT_00d0fe2c) {
        DAT_00d0fe2c = 0;
      }
      DAT_00d0fe21 = 0;
    }
    Sleep(5);
  }
  DAT_00453cec = 1;
  return 0;
}



// ==== 0x4171d9 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_004171d9(int param_1)

{
  uint in_EAX;
  undefined4 *puVar1;
  int iVar2;
  WAVEFORMATEX local_1c;
  int local_8;
  
  iVar2 = 0;
  if ((((DAT_00d0fe8c != 0) && (DAT_00d0fe90 != 0)) && (DAT_00d0fe94 != 0)) &&
     ((DAT_00d0fe98 != 0 && (DAT_00d0fe9c != 0)))) {
    FUN_00416f90();
    DAT_00d175b4 = param_1;
    local_1c.nSamplesPerSec = param_1 / DAT_00453cdc;
    local_1c.wFormatTag = 1;
    local_1c.nChannels = 2;
    local_1c.wBitsPerSample = 0x10;
    local_1c.nBlockAlign = 4;
    local_1c.cbSize = 0;
    local_1c.nAvgBytesPerSec = local_1c.nSamplesPerSec << 2;
    in_EAX = waveOutOpen((LPHWAVEOUT)&DAT_00d17744,0xffffffff,&local_1c,0,0,0);
    if (in_EAX == 0) {
      _DAT_00d15fcc = 1.0 / (float)param_1;
      DAT_00d15fc4 = (DAT_00d175b4 * 0x14) / 1000 + 3U & 0xfffffffc;
      DAT_00d17560 = (DAT_00453ce8 / 0x14) * DAT_00d15fc4 * 2;
      DAT_00d0fe84 = (DAT_00d175b4 << 7) / 0xac44;
      _DAT_00d0fe88 = (float)DAT_00d0fe84;
      if (DAT_00d0fe84 < 0) {
        _DAT_00d0fe88 = _DAT_00d0fe88 + 4.2949673e+09;
      }
      _DAT_00d0fe88 = 1.0 / _DAT_00d0fe88;
      local_8 = DAT_00d0fe84;
      _memset(&DAT_00d107c0,0,0x5800);
      puVar1 = &DAT_00d107f4;
      do {
        puVar1[-0xd] = iVar2;
        *puVar1 = 1;
        puVar1 = puVar1 + 0x16;
        iVar2 = iVar2 + 1;
      } while ((int)puVar1 < 0xd15ff4);
      return CONCAT31((int3)((uint)puVar1 >> 8),1);
    }
  }
  return in_EAX & 0xffffff00;
}



// ==== 0x417320 ====

void FUN_00417320(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  int iVar2;
  undefined2 *puVar3;
  
  puVar3 = (undefined2 *)param_1;
  param_1 = param_2;
  if ((((0 < param_3) && (puVar3 != (undefined2 *)0x0)) && (param_2 != (float *)0x0)) &&
     (param_3 = param_3 * 2, 0 < param_3)) {
    do {
      fVar1 = *param_1;
      param_1 = param_1 + 1;
      iVar2 = (int)ROUND(fVar1);
      if (iVar2 < -0x8000) {
        iVar2 = -0x8000;
      }
      else if (0x7fff < iVar2) {
        iVar2 = 0x7fff;
      }
      *puVar3 = (short)iVar2;
      puVar3 = puVar3 + 1;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}



// ==== 0x417379 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00417379(float *param_1,undefined4 *param_2)

{
  int *piVar1;
  short sVar2;
  short sVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  int iVar6;
  short *psVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  uint uVar14;
  undefined4 *puVar15;
  uint uVar16;
  uint uVar17;
  uint *puVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  float *pfVar23;
  float *pfVar24;
  bool bVar25;
  
  if (0 < (int)param_2) {
    DAT_00d0fe3c = (uint)param_2;
    DAT_00d0fe44 = param_1 + (int)param_2 * 2;
    DAT_00d0fe40 = param_1;
    param_2 = &DAT_00d107c0;
    _DAT_00d0fe34 = 0x40;
    do {
      DAT_00d0fe38 = (uint)param_2;
      DAT_00d0fe48 = DAT_00d0fe40;
      DAT_00d0fe54 = DAT_00d0fe38;
      if ((param_2 != (undefined4 *)0x0) &&
         (puVar18 = (uint *)param_2[7], DAT_00d0fe50 = puVar18, puVar18 != (uint *)0x0)) {
        DAT_00d0fe5c = *puVar18;
        uVar19 = DAT_00d0fe3c;
        puVar15 = param_2;
LAB_004173f9:
        do {
          uVar16 = DAT_00d0fe54;
          DAT_00d0fe4c = 0;
          if (puVar15[0xe] == 1) {
            uVar14 = -puVar15[0xb];
            uVar17 = ((puVar18[2] + puVar18[3]) - puVar15[10]) - (uint)(puVar15[0xb] != 0);
          }
          else {
            uVar14 = puVar15[0xb];
            uVar17 = puVar15[10] - puVar18[2];
          }
          DAT_00d0fe58 = uVar19;
          if (uVar17 < 0x1000000) {
            uVar4 = (ulonglong)(puVar15[0xd] << 0x18 | (uint)puVar15[0xc] >> 8);
            uVar5 = CONCAT44(uVar17 >> 8,uVar14 >> 8 | uVar17 << 0x18);
            uVar14 = (uint)(uVar5 / uVar4);
            if ((int)(uVar5 % uVar4) != 0) {
              uVar14 = uVar14 + 1;
            }
            if (uVar14 <= uVar19) {
              DAT_00d0fe4c = 1;
              DAT_00d0fe58 = uVar14;
            }
          }
          DAT_00d0fe7c = 0.0;
          DAT_00d0fe80 = 0.0;
          DAT_00d0fe6c = DAT_00d0fe58;
          DAT_00d0fe78 = 0;
          if (((*(int *)(DAT_00d0fe54 + 0x54) == 0) ||
              (*(int *)(DAT_00d0fe54 + 0x20) != *(int *)(DAT_00d0fe54 + 0x3c))) ||
             (*(int *)(DAT_00d0fe54 + 0x24) != *(int *)(DAT_00d0fe54 + 0x40))) {
            piVar1 = (int *)(DAT_00d0fe54 + 0x20);
            puVar18 = (uint *)(DAT_00d0fe54 + 0x44);
            *(int *)(DAT_00d0fe54 + 0x3c) = *piVar1;
            iVar21 = *piVar1 - (*puVar18 >> 8);
            if (iVar21 != 0) {
              DAT_00d0fe7c = (float)iVar21 * 0.003921569 * _DAT_00d0fe88;
              *(float *)(uVar16 + 0x4c) = DAT_00d0fe7c;
              DAT_00d0fe78 = DAT_00d0fe84;
            }
            *(int *)(uVar16 + 0x40) = *(int *)(uVar16 + 0x24);
            iVar21 = *(int *)(uVar16 + 0x24) - (*(uint *)(uVar16 + 0x48) >> 8);
            if (iVar21 != 0) {
              DAT_00d0fe80 = (float)iVar21 * 0.003921569 * _DAT_00d0fe88;
              *(float *)(uVar16 + 0x50) = DAT_00d0fe80;
              DAT_00d0fe78 = DAT_00d0fe84;
            }
          }
          else {
            DAT_00d0fe78 = *(uint *)(DAT_00d0fe54 + 0x54);
            DAT_00d0fe7c = *(float *)(DAT_00d0fe54 + 0x4c);
            DAT_00d0fe80 = *(float *)(DAT_00d0fe54 + 0x50);
          }
          uVar19 = DAT_00d0fe78;
          if ((0 < (int)DAT_00d0fe78) &&
             (*(uint *)(uVar16 + 0x54) = DAT_00d0fe78, uVar19 < DAT_00d0fe58)) {
            DAT_00d0fe58 = uVar19;
          }
          _DAT_00d0fe64 = (float)*(int *)(DAT_00d0fe54 + 0x24) * 0.003921569;
          _DAT_00d0fe60 = (float)*(int *)(DAT_00d0fe54 + 0x20) * 0.003921569;
          DAT_00d0fe74 = (float)*(int *)(DAT_00d0fe54 + 0x48) * 0.00390625 * 0.003921569;
          _DAT_00d0fe68 = *(uint *)(DAT_00d0fe54 + 0x44);
          DAT_00d0fe70 = (float)(int)_DAT_00d0fe68 * 0.00390625 * 0.003921569;
          uVar19 = *(uint *)(DAT_00d0fe54 + 0x30);
          uVar16 = *(uint *)(DAT_00d0fe54 + 0x34);
          uVar14 = *(uint *)(DAT_00d0fe54 + 0x2c);
          if (*(int *)(DAT_00d0fe54 + 0x38) != 1) {
            uVar17 = uVar19 ^ 0xffffffff;
            uVar19 = uVar17 + 1;
            uVar16 = (uVar16 ^ 0xffffffff) + (uint)(0xfffffffe < uVar17);
          }
          iVar21 = *(int *)(DAT_00d0fe54 + 0x28) + (DAT_00d0fe5c >> 1);
          uVar17 = DAT_00d0fe58;
          pfVar23 = DAT_00d0fe48;
          if (DAT_00d0fe78 == 0) {
            uVar17 = DAT_00d0fe58 >> 1;
            if (uVar17 != 0) {
              iVar6 = iVar21 * 2;
              psVar7 = (short *)(iVar21 * 2);
              uVar20 = (uVar14 >> 1) * 2;
              iVar22 = iVar21 + uVar16 + (uint)CARRY4(uVar20,uVar19);
              _DAT_00d0fe68 = uVar20 + uVar19 >> 1;
              uVar20 = _DAT_00d0fe68 * 2;
              iVar21 = iVar22 + uVar16 + (uint)CARRY4(uVar20,uVar19);
              fVar8 = ((float)*(short *)(iVar6 + 2) - (float)*psVar7) *
                      (float)(uVar14 >> 1) * 4.656613e-10 + (float)*psVar7;
              fVar9 = fVar8 * _DAT_00d0fe60;
              fVar11 = ((float)*(short *)(iVar22 * 2 + 2) - (float)*(short *)(iVar22 * 2)) *
                       (float)_DAT_00d0fe68 * 4.656613e-10 + (float)*(short *)(iVar22 * 2);
              pfVar24 = DAT_00d0fe48;
              while( true ) {
                pfVar23 = pfVar24 + 4;
                uVar14 = uVar20 + uVar19;
                fVar12 = fVar11 * _DAT_00d0fe64;
                fVar10 = fVar8 * _DAT_00d0fe64 + pfVar24[1];
                fVar11 = fVar11 * _DAT_00d0fe60 + pfVar24[2];
                *pfVar24 = fVar9 + *pfVar24;
                fVar12 = fVar12 + pfVar24[3];
                uVar17 = uVar17 - 1;
                if (uVar17 == 0) break;
                iVar6 = iVar21 * 2;
                psVar7 = (short *)(iVar21 * 2);
                uVar20 = (uVar14 >> 1) * 2;
                iVar21 = iVar21 + uVar16 + (uint)CARRY4(uVar20,uVar19);
                _DAT_00d0fe68 = uVar20 + uVar19 >> 1;
                fVar13 = (float)_DAT_00d0fe68;
                sVar2 = *(short *)(iVar21 * 2 + 2);
                uVar20 = _DAT_00d0fe68 * 2;
                sVar3 = *(short *)(iVar21 * 2);
                iVar21 = iVar21 + uVar16 + (uint)CARRY4(uVar20,uVar19);
                fVar8 = (float)*psVar7 +
                        ((float)*(short *)(iVar6 + 2) - (float)*psVar7) *
                        (float)(uVar14 >> 1) * 4.656613e-10;
                pfVar24[1] = fVar10;
                pfVar24[2] = fVar11;
                fVar9 = fVar8 * _DAT_00d0fe60;
                fVar11 = ((float)sVar2 - (float)sVar3) * fVar13 * 4.656613e-10 + (float)sVar3;
                pfVar24[3] = fVar12;
                pfVar24 = pfVar23;
              }
              pfVar24[1] = fVar10;
              pfVar24[2] = fVar11;
              pfVar24[3] = fVar12;
            }
            uVar17 = DAT_00d0fe58 & 1;
          }
          pfVar24 = pfVar23;
          if (uVar17 != 0) {
            do {
              _DAT_00d0fe68 = uVar14 >> 1;
              pfVar24 = pfVar23 + 2;
              iVar6 = iVar21 * 2;
              psVar7 = (short *)(iVar21 * 2);
              uVar14 = _DAT_00d0fe68 * 2 + uVar19;
              iVar21 = iVar21 + uVar16 + (uint)CARRY4(_DAT_00d0fe68 * 2,uVar19);
              fVar9 = (float)*psVar7 +
                      ((float)*(short *)(iVar6 + 2) - (float)*psVar7) *
                      (float)_DAT_00d0fe68 * 4.656613e-10;
              fVar8 = fVar9 * DAT_00d0fe70;
              DAT_00d0fe70 = DAT_00d0fe70 + DAT_00d0fe7c;
              fVar9 = fVar9 * DAT_00d0fe74;
              DAT_00d0fe74 = DAT_00d0fe74 + DAT_00d0fe80;
              *pfVar23 = fVar8 + *pfVar23;
              pfVar23[1] = fVar9 + pfVar23[1];
              uVar17 = uVar17 - 1;
              pfVar23 = pfVar24;
            } while (uVar17 != 0);
            DAT_00d0fe70 = (float)(int)ROUND(DAT_00d0fe70 * 255.0 * 256.0);
            DAT_00d0fe74 = (float)(int)ROUND(DAT_00d0fe74 * 255.0 * 256.0);
          }
          puVar15 = (undefined4 *)DAT_00d0fe54;
          puVar18 = DAT_00d0fe50;
          uVar16 = iVar21 - (DAT_00d0fe5c >> 1);
          if (DAT_00d0fe78 != 0) {
            *(float *)(DAT_00d0fe54 + 0x44) = DAT_00d0fe70;
            *(float *)((int)puVar15 + 0x48) = DAT_00d0fe74;
            uVar19 = DAT_00d0fe58;
            uVar17 = DAT_00d0fe78 - DAT_00d0fe58;
            DAT_00d0fe7c = 0.0;
            DAT_00d0fe80 = 0.0;
            DAT_00d0fe78 = uVar17;
            *(uint *)((int)puVar15 + 0x54) = uVar17;
            if (uVar17 == 0) {
              *(undefined4 *)((int)puVar15 + 0x4c) = 0;
              *(undefined4 *)((int)puVar15 + 0x50) = 0;
              *(int *)((int)puVar15 + 0x44) = *(int *)((int)puVar15 + 0x20) << 8;
              *(int *)((int)puVar15 + 0x48) = *(int *)((int)puVar15 + 0x24) << 8;
              if (DAT_00d0fe6c != uVar19) {
                *(uint *)((int)puVar15 + 0x28) = uVar16;
                *(uint *)((int)puVar15 + 0x2c) = uVar14;
                uVar19 = (uint)((int)DAT_00d0fe44 - (int)pfVar24) >> 3;
                DAT_00d0fe48 = pfVar24;
                if (uVar19 != 0) goto LAB_004173f9;
              }
            }
          }
          puVar15 = (undefined4 *)DAT_00d0fe54;
          puVar18 = DAT_00d0fe50;
          if (DAT_00d0fe4c == 0) break;
          if ((*(byte *)((int)DAT_00d0fe50 + 0x1d) & 2) == 0) {
            if ((*(byte *)((int)DAT_00d0fe50 + 0x1d) & 4) == 0) {
              uVar14 = 0;
              uVar16 = 0;
              *(undefined4 *)(DAT_00d0fe54 + 0x1c) = 0;
              break;
            }
            if (*(int *)(DAT_00d0fe54 + 0x38) == 1) goto LAB_0041795f;
            do {
              uVar14 = -uVar14 - 1;
              uVar16 = ((puVar18[2] - 1) - uVar16) + puVar18[2];
              *(undefined4 *)((int)puVar15 + 0x38) = 1;
              if ((int)uVar16 < (int)(puVar18[2] + puVar18[3])) break;
LAB_0041795f:
              bVar25 = uVar14 != 0;
              iVar21 = -uVar14;
              uVar14 = iVar21 - 1;
              uVar16 = (((puVar18[2] + puVar18[3]) - uVar16) - (uint)bVar25) +
                       puVar18[2] + puVar18[3] + -1 + (uint)(iVar21 != 0);
              *(undefined4 *)((int)puVar15 + 0x38) = 2;
            } while ((int)uVar16 < (int)puVar18[2]);
            *(uint *)((int)puVar15 + 0x28) = uVar16;
            *(uint *)((int)puVar15 + 0x2c) = uVar14;
            uVar19 = (uint)((int)DAT_00d0fe44 - (int)pfVar24) >> 3;
            DAT_00d0fe48 = pfVar24;
            if (uVar19 == 0) break;
            goto LAB_004173f9;
          }
          do {
            uVar16 = uVar16 - DAT_00d0fe50[3];
          } while (DAT_00d0fe50[2] + DAT_00d0fe50[3] <= uVar16);
          *(uint *)(DAT_00d0fe54 + 0x28) = uVar16;
          *(uint *)((int)puVar15 + 0x2c) = uVar14;
          uVar19 = (uint)((int)DAT_00d0fe44 - (int)pfVar24) >> 3;
          DAT_00d0fe48 = pfVar24;
        } while (uVar19 != 0);
        uVar19 = DAT_00d0fe54;
        *(uint *)(DAT_00d0fe54 + 0x2c) = uVar14;
        *(uint *)(uVar19 + 0x28) = uVar16;
      }
      param_2 = param_2 + 0x16;
    } while ((int)param_2 < 0xd11dc0);
  }
  return;
}



// ==== 0x4179d8 ====

void FUN_004179d8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x80);
  if (iVar2 < iVar1) {
    iVar2 = iVar2 + (uint)*(byte *)(param_1 + 0x84) * 4;
    *(int *)(param_1 + 0xc) = iVar2;
    if (iVar2 <= iVar1) goto LAB_00417a15;
  }
  else if ((iVar2 <= iVar1) ||
          (iVar2 = iVar2 + (uint)*(byte *)(param_1 + 0x84) * -4, *(int *)(param_1 + 0xc) = iVar2,
          iVar1 <= iVar2)) goto LAB_00417a15;
  *(int *)(param_1 + 0xc) = iVar1;
LAB_00417a15:
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 1;
  return;
}



// ==== 0x417a1b ====

void FUN_00417a1b(uint param_1)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  float10 fVar4;
  
  bVar2 = *(byte *)(param_1 + 0xa2);
  if ((bVar2 & 3) == 0) {
    fVar4 = (float10)FUN_0041d084(((double)(int)*(char *)(param_1 + 0x85) +
                                  (double)(int)*(char *)(param_1 + 0x85)) * 0.049087375);
    _fabs((double)(fVar4 * (float10)256.0));
    uVar3 = FUN_0041d384();
  }
  else if ((bVar2 & 3) == 1) {
    cVar1 = *(char *)(param_1 + 0x85);
    bVar2 = cVar1 * '\b';
    if (cVar1 < '\0') {
      bVar2 = cVar1 * -8 - 1;
    }
    uVar3 = (uint)bVar2;
  }
  else {
    uVar3 = param_1;
    if (((bVar2 & 3) != 0) && ((bVar2 & 3) < 4)) {
      uVar3 = 0xff;
    }
  }
  uVar3 = (int)(*(byte *)(param_1 + 0x87) * uVar3) >> 5 & 0xfffffffc;
  if (-1 < *(char *)(param_1 + 0x85)) {
    uVar3 = -uVar3;
  }
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 1;
  *(uint *)(param_1 + 0x1c) = uVar3;
  return;
}



// ==== 0x417abb ====

void FUN_00417abb(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_2 + 0x14e);
  if (cVar1 == '\0') {
    FUN_0041d084((double)((float)*(int *)(param_1 + 0x5c) * 0.024543688));
    iVar2 = FUN_0041d384();
  }
  else if (cVar1 == '\x01') {
    iVar2 = ((0x7f < *(int *)(param_1 + 0x5c)) - 1 & 0x80) - 0x40;
  }
  else if (cVar1 == '\x02') {
    iVar2 = 0x80 - (*(int *)(param_1 + 0x5c) + 0x80) % 0x100 >> 1;
  }
  else {
    iVar2 = param_2;
    if (cVar1 == '\x03') {
      iVar2 = 0x80 - (0x180 - *(int *)(param_1 + 0x5c)) % 0x100 >> 1;
    }
  }
  iVar2 = (uint)*(byte *)(param_2 + 0x150) * iVar2;
  if (*(byte *)(param_2 + 0x14f) != 0) {
    iVar2 = (*(int *)(param_1 + 0x60) * iVar2) / (int)(uint)*(byte *)(param_2 + 0x14f);
  }
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + (iVar2 >> 6);
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  if ((int)(uint)*(byte *)(param_2 + 0x14f) < *(int *)(param_1 + 0x60)) {
    *(uint *)(param_1 + 0x60) = (uint)*(byte *)(param_2 + 0x14f);
  }
  *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + (uint)*(byte *)(param_2 + 0x151);
  if (0xff < *(int *)(param_1 + 0x5c)) {
    *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + -0x100;
  }
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 1;
  return;
}



// ==== 0x417bac ====

void FUN_00417bac(int param_1,uint *param_2,uint *param_3,byte param_4,int param_5,int param_6,
                 byte param_7,byte param_8,byte param_9,uint *param_10,int *param_11,
                 undefined1 *param_12,int *param_13,byte param_14)

{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar3 = *param_2;
  if ((int)uVar3 < param_5) {
    if (*param_3 == (uint)*(ushort *)(param_6 + uVar3 * 4)) {
      if (((param_4 & 4) != 0) && (uVar3 == param_7)) {
        *param_2 = (uint)param_8;
        *param_3 = (uint)*(ushort *)(param_6 + (uint)param_8 * 4);
      }
      uVar3 = *param_2;
      puVar1 = (ushort *)(param_6 + uVar3 * 4);
      uVar5 = (uint)puVar1[1];
      puVar2 = (ushort *)(param_6 + 4 + uVar3 * 4);
      if (uVar3 == param_5 - 1U) {
        *param_10 = uVar5;
        *param_12 = 1;
        *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | param_14;
        return;
      }
      if ((((param_4 & 2) != 0) && (uVar3 == param_9)) && (*(char *)(param_1 + 0x65) == '\0')) {
        *param_10 = uVar5;
        goto LAB_00417c94;
      }
      iVar4 = (uint)*puVar2 - (uint)*puVar1;
      if (iVar4 == 0) {
        *param_13 = 0;
      }
      else {
        *param_13 = (int)((uint)puVar2[1] * 0x10000 + uVar5 * -0x10000) / iVar4;
      }
      *param_11 = uVar5 * 0x10000;
      *param_2 = *param_2 + 1;
    }
    else {
      *param_11 = *param_11 + *param_13;
    }
  }
  *param_10 = (int)*(short *)((int)param_11 + 2);
  *param_3 = *param_3 + 1;
LAB_00417c94:
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | param_14;
  return;
}



// ==== 0x417c9f ====

void FUN_00417c9f(int param_1,byte param_2)

{
  int *piVar1;
  uint uVar2;
  
  if ((0xf < param_2) && (param_2 < 0x51)) {
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 2;
    *(uint *)(param_1 + 0x10) = param_2 - 0x10;
    return;
  }
  uVar2 = (uint)param_2;
  switch(param_2 >> 4) {
  case 6:
  case 8:
    piVar1 = (int *)(param_1 + 0x10);
    *piVar1 = *piVar1 - (uVar2 & 0xf);
    if (*piVar1 < 0) {
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    goto LAB_00417d03;
  case 7:
  case 9:
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + (uVar2 & 0xf);
    if (0x40 < *(int *)(param_1 + 0x10)) {
      *(undefined4 *)(param_1 + 0x10) = 0x40;
    }
LAB_00417d03:
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 2;
    return;
  case 10:
    *(byte *)(param_1 + 0x86) = param_2 & 0xf;
    return;
  case 0xb:
    *(byte *)(param_1 + 0x87) = param_2 & 0xf;
    return;
  case 0xc:
    *(uint *)(param_1 + 0x14) = (uVar2 & 0xf) << 4;
    break;
  case 0xd:
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) - (uVar2 & 0xf);
    break;
  case 0xe:
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (uVar2 & 0xf);
    break;
  case 0xf:
    if ((param_2 & 0xf) != 0) {
      *(byte *)(param_1 + 0x84) = param_2 << 4;
    }
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xf7;
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_1 + 0x68);
  default:
    return;
  }
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 4;
  return;
}



// ==== 0x417d95 ====

void FUN_00417d95(uint param_1,int param_2,int param_3)

{
  uint *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *local_8;
  
  iVar6 = param_1;
  local_8 = *(int **)(param_1 + 4);
  if (local_8 != (int *)0x0) {
    param_1 = *local_8;
  }
  iVar7 = param_1;
  if (*(int *)(iVar6 + 0xc) + *(int *)(iVar6 + 0x1c) == 0) {
    *(byte *)(iVar6 + 2) = *(byte *)(iVar6 + 2) & 0xfe;
  }
  if ((*(byte *)(iVar6 + 2) & 8) != 0) {
    iVar8 = param_1 * 0x58;
    iVar4 = param_1 * 0x16;
    local_8 = &DAT_00d107c0 + iVar4;
    if ((&DAT_00d107dc)[param_1 * 0x16] != 0) {
      if ((int)param_1 < 0x20) {
        param_1 = param_1 + 0x20;
      }
      else {
        param_1 = param_1 + -0x20;
      }
      local_8 = &DAT_00d107c0 + param_1 * 0x16;
      _memcpy(local_8,&DAT_00d107c0 + iVar4,0x58);
      *local_8 = param_1;
      *(undefined4 *)(&DAT_00d107d0 + iVar8) = 0;
      *(undefined4 *)(&DAT_00d107c4 + iVar8) = 0;
      (&DAT_00d107e0)[iVar7 * 0x16] = 0;
      (&DAT_00d107e4)[iVar7 * 0x16] = 0;
      *(int **)(iVar6 + 4) = local_8;
    }
    local_8[7] = param_2;
    puVar1 = (uint *)(local_8 + 6);
    if ((uint)(*(int *)(param_2 + 0xc) + *(int *)(param_2 + 8)) <= *puVar1) {
      *puVar1 = 0;
    }
    local_8[10] = *puVar1;
    local_8[0xb] = 0;
    local_8[0xe] = 1;
    *puVar1 = 0;
    local_8[0x11] = 0;
    local_8[0x12] = 0;
    local_8[0x15] = 0;
  }
  if ((*(byte *)(iVar6 + 2) & 2) != 0) {
    iVar7 = FUN_0041d384();
    if (local_8 != (int *)0x0) {
      local_8[4] = iVar7;
      local_8[1] = iVar7;
      local_8[8] = (local_8[5] * iVar7) / 0xff;
      local_8[9] = ((0xff - local_8[5]) * iVar7) / 0xff;
    }
  }
  if ((*(byte *)(iVar6 + 2) & 4) != 0) {
    iVar7 = FUN_0041ddb6();
    iVar7 = ((0x80 - iVar7) / 0x20) * (*(int *)(iVar6 + 0x4c) + -0x20) + *(int *)(iVar6 + 0x14);
    if (iVar7 < 0) {
      iVar7 = 0;
    }
    if (0xff < iVar7) {
      iVar7 = 0xff;
    }
    if (local_8 != (int *)0x0) {
      local_8[5] = iVar7;
      local_8[3] = iVar7;
      local_8[8] = (local_8[4] * iVar7) / 0xff;
      local_8[9] = ((0xff - iVar7) * local_8[4]) / 0xff;
    }
  }
  if ((*(byte *)(iVar6 + 2) & 1) != 0) {
    if ((*(byte *)(param_3 + 0x22) & 1) == 0) {
      param_1 = (uint)(0xda7600 / (longlong)(*(int *)(iVar6 + 0xc) + *(int *)(iVar6 + 0x1c)));
    }
    else {
      FUN_0041e780(0x4000000000000000);
      param_1 = FUN_0041d384();
    }
    local_8[2] = param_1;
    uVar5 = DAT_00d175b4;
    if ((int)param_1 < 100) {
      param_1 = 100;
    }
    uVar2 = (ulonglong)DAT_00d175b4;
    uVar3 = param_1 / uVar2;
    local_8[0xd] = (int)uVar3;
    local_8[0xc] = (int)(((ulonglong)param_1 % uVar2 << 0x20 | uVar3) / (ulonglong)uVar5);
  }
  if ((*(byte *)(iVar6 + 2) & 0x20) != 0) {
    local_8[0xb] = 0;
    local_8[10] = 0;
    local_8[6] = 0;
  }
  return;
}



// ==== 0x417fab ====

void FUN_00417fab(int param_1,int param_2)

{
  *(uint *)(param_1 + 0x10) = (uint)*(byte *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x34) = 0x40;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0x20;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined1 *)(param_1 + 0x65) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0x10000;
  *(undefined1 *)(param_1 + 0x3c) = 0;
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  if ((*(byte *)(param_1 + 0xa2) & 0xf) < 4) {
    *(undefined1 *)(param_1 + 0x85) = 0;
  }
  if ((*(byte *)(param_1 + 0xa2) & 0xf0) < 0x40) {
    *(undefined1 *)(param_1 + 0x89) = 0;
  }
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 6;
  *(undefined1 *)(param_1 + 0x92) = 0;
  return;
}



// ==== 0x418029 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00418029(int *param_1)

{
  byte *pbVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  undefined *puVar10;
  byte *pbVar11;
  char *pcVar12;
  int local_10;
  undefined *local_c;
  
  param_1[0x54] = -1;
  param_1[0x53] = -1;
  pcVar12 = (char *)(param_1[0x50] * (int)(short)param_1[5] * 5 +
                    *(int *)(*param_1 + 4 + (uint)*(byte *)(param_1[0x51] + 0x28 + (int)param_1) * 8
                            ));
  if ((pcVar12 != (char *)0x0) && (local_10 = 0, 0 < (short)param_1[5])) {
    pbVar11 = &DAT_00d16046;
    do {
      bVar7 = pcVar12[4] & 0xf;
      bVar8 = (byte)pcVar12[4] >> 4;
      if ((pcVar12[3] == '\x03') || (bVar6 = false, pcVar12[3] == '\x05')) {
        bVar6 = true;
      }
      if ((pcVar12[1] != '\0') && (!bVar6)) {
        *pbVar11 = pcVar12[1] - 1;
      }
      cVar2 = *pcVar12;
      if (((cVar2 != '\0') && (cVar2 != -1)) && (!bVar6)) {
        pbVar11[-0x66] = cVar2 - 1;
      }
      if ((int)(uint)*pbVar11 < (int)(short)param_1[8]) {
        puVar10 = (undefined *)((uint)*pbVar11 * 0x154 + param_1[1]);
        if ((byte)puVar10[pbVar11[-0x66] + 0x44] < 0x10) {
          local_c = *(undefined **)(puVar10 + (uint)(byte)puVar10[pbVar11[-0x66] + 0x44] * 4 + 4);
        }
        else {
          local_c = &DAT_00d17580;
        }
        if (!bVar6) {
          *(undefined **)(pbVar11 + -0x5e) = local_c;
        }
      }
      else {
        _DAT_00d17580 = 0;
        puVar10 = &DAT_00d175c0;
        local_c = &DAT_00d17580;
      }
      uVar3 = *(undefined4 *)(pbVar11 + -0x5a);
      iVar4 = *(int *)(pbVar11 + -0x56);
      uVar5 = *(undefined4 *)(pbVar11 + -0x52);
      if ((pbVar11[6] == 7) && (pcVar12[3] != '\a')) {
        *(int *)(pbVar11 + -0x56) = *(int *)(pbVar11 + -0x4e) + iVar4;
      }
      bVar9 = pcVar12[3];
      pbVar11[-0xffffffff0000004e] = 0;
      pbVar11[-0xffffffff0000004d] = 0;
      pbVar11[-0xffffffff0000004c] = 0;
      pbVar11[-0xffffffff0000004b] = 0;
      pbVar11[6] = bVar9;
      pbVar11[-100] = 0;
      cVar2 = *pcVar12;
      if ((cVar2 != '\0') && (cVar2 != -1)) {
        bVar9 = (local_c[0x1f] + cVar2) - 1;
        pbVar11[1] = bVar9;
        if ((*(byte *)((int)param_1 + 0x22) & 1) != 0) {
          *(uint *)(pbVar11 + 2) = ((uint)bVar9 * -0x40 - (int)(char)local_c[0x11] / 2) + 0x1e00;
        }
        if (!bVar6) {
          *(undefined4 *)(pbVar11 + -0x5a) = *(undefined4 *)(pbVar11 + 2);
        }
        pbVar11[-100] = 8;
      }
      pbVar11[-0xffffffff0000004a] = 0;
      pbVar11[-0xffffffff00000049] = 0;
      pbVar11[-0xffffffff00000048] = 0;
      pbVar11[-0xffffffff00000047] = 0;
      pbVar11[-100] = pbVar11[-100] | 3;
      if (pcVar12[1] != '\0') {
        FUN_00417fab(pbVar11 + -0x66,local_c);
      }
      if (pcVar12[2] != '\0') {
        FUN_00417c9f(pbVar11 + -0x66,pcVar12[2]);
      }
      if ((*pcVar12 == -1) || (pcVar12[3] == '\x14')) {
        pbVar11[-1] = 1;
      }
      if ((puVar10[0x14c] & 1) == 0) {
        if (pbVar11[-1] != 0) {
          pbVar11[-0xffffffff00000032] = 0;
          pbVar11[-0xffffffff00000031] = 0;
          pbVar11[-0xffffffff00000030] = 0;
          pbVar11[-0xffffffff0000002f] = 0;
        }
      }
      else if (pbVar11[-0x2a] == 0) {
        FUN_00417bac(pbVar11 + -0x66,pbVar11 + -0x3a,pbVar11 + -0x3e,puVar10[0x14c],puVar10[0x144],
                     puVar10 + 0xa4,puVar10[0x148],puVar10[0x147],puVar10[0x146],pbVar11 + -0x32,
                     pbVar11 + -0x36,pbVar11 + -0x2a,pbVar11 + -0x2e,2);
      }
      if (((puVar10[0x14d] & 1) != 0) && (pbVar11[-0x12] == 0)) {
        FUN_00417bac(pbVar11 + -0x66,pbVar11 + -0x22,pbVar11 + -0x26,puVar10[0x14d],puVar10[0x145],
                     puVar10 + 0xf4,puVar10[0x14b],puVar10[0x14a],puVar10[0x149],pbVar11 + -0x1a,
                     pbVar11 + -0x1e,pbVar11 + -0x12,pbVar11 + -0x16,4);
      }
      if (pbVar11[-1] != 0) {
        pbVar1 = pbVar11 + -0xe;
        *(uint *)pbVar1 = *(int *)pbVar1 - (uint)*(ushort *)(puVar10 + 0x152);
        if (*(int *)pbVar1 < 0) {
          pbVar11[-0xffffffff0000000e] = 0;
          pbVar11[-0xffffffff0000000d] = 0;
          pbVar11[-0xffffffff0000000c] = 0;
          pbVar11[-0xffffffff0000000b] = 0;
        }
        pbVar11[-100] = pbVar11[-100] | 2;
      }
      bVar9 = pcVar12[3];
      if (bVar9 < 10) {
        if (bVar9 == 9) {
          if (pcVar12[4] != 0) {
            *(uint *)(pbVar11 + 10) = (uint)(byte)pcVar12[4];
          }
          if (*(int *)(pbVar11 + -0x62) != 0) {
            if ((uint)(*(int *)(pbVar11 + 10) << 8) <
                (uint)(*(int *)(local_c + 0xc) + *(int *)(local_c + 8))) {
              *(int *)(*(int *)(pbVar11 + -0x62) + 0x18) = *(int *)(pbVar11 + 10) << 8;
            }
            else {
              pbVar11[-100] = pbVar11[-100] & 0xf7 | 0x20;
            }
          }
        }
        else if (bVar9 == 1) {
          if (pcVar12[4] != 0) {
            pbVar11[0x13] = pcVar12[4];
          }
        }
        else if (bVar9 == 2) {
          if (pcVar12[4] != 0) {
            pbVar11[0x12] = pcVar12[4];
          }
        }
        else if (bVar9 == 3) {
          if (pcVar12[4] != 0) {
            pbVar11[0x1e] = pcVar12[4];
          }
          pbVar11[-100] = pbVar11[-100] & 0xf6;
          *(undefined4 *)(pbVar11 + 0x1a) = *(undefined4 *)(pbVar11 + 2);
        }
        else if (bVar9 == 4) {
          if (bVar8 != 0) {
            pbVar11[0x20] = bVar8;
          }
          if (bVar7 != 0) {
            pbVar11[0x21] = bVar7;
          }
          FUN_00417a1b(pbVar11 + -0x66);
        }
      }
      else if (bVar9 == 0xe) {
        if (bVar8 == 2) {
          if (bVar7 != 0) {
            pbVar11[0x43] = bVar7;
          }
          *(uint *)(pbVar11 + -0x5a) = *(int *)(pbVar11 + -0x5a) + (uint)pbVar11[0x43] * 4;
        }
        else if (bVar8 == 0xd) {
          pbVar11[-100] = pbVar11[-100] & 0xf0;
          *(int *)(pbVar11 + -0x56) = iVar4;
          *(undefined4 *)(pbVar11 + -0x5a) = uVar3;
          *(undefined4 *)(pbVar11 + -0x52) = uVar5;
        }
      }
      else if (bVar9 == 0xf) {
        bVar7 = pcVar12[4];
        if (bVar7 < 0x20) {
          param_1[0x4e] = (uint)bVar7;
        }
        else {
          FUN_00416be4(param_1,(uint)bVar7);
        }
      }
      else if ((bVar9 == 0x1b) && (pcVar12[4] != '\0')) {
        pbVar11[0x18] = bVar8;
        pbVar11[0x19] = bVar7;
      }
      FUN_00417abb(pbVar11 + -0x66,puVar10);
      FUN_00417d95(pbVar11 + -0x66,local_c,param_1);
      local_10 = local_10 + 1;
      pbVar11 = pbVar11 + 0xac;
      pcVar12 = pcVar12 + 5;
    } while (local_10 < (short)param_1[5]);
  }
  return;
}



// ==== 0x418446 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00418446(int *param_1)

{
  int *piVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  int *piVar11;
  undefined *puVar12;
  byte *local_c;
  undefined *local_8;
  int local_4;
  
  iVar8 = param_1[0x50] * (int)(short)param_1[5] * 5 +
          *(int *)(*param_1 + 4 + (uint)*(byte *)(param_1[0x51] + 0x28 + (int)param_1) * 8);
  if ((iVar8 != 0) && (local_4 = 0, 0 < (short)param_1[5])) {
    local_c = (byte *)(iVar8 + 2);
    piVar11 = &DAT_00d15ff0;
    do {
      if ((int)(uint)*(byte *)((int)piVar11 + 0x56) < (int)(short)param_1[8]) {
        puVar12 = (undefined *)((uint)*(byte *)((int)piVar11 + 0x56) * 0x154 + param_1[1]);
        if ((0xf < (byte)puVar12[*(byte *)(piVar11 + -4) + 0x44]) ||
           (local_8 = *(undefined **)
                       (puVar12 + (uint)(byte)puVar12[*(byte *)(piVar11 + -4) + 0x44] * 4 + 4),
           local_8 == (undefined *)0x0)) goto LAB_004184d6;
      }
      else {
        _DAT_00d17580 = 0;
        puVar12 = &DAT_00d175c0;
LAB_004184d6:
        local_8 = &DAT_00d17580;
      }
      bVar2 = local_c[1];
      bVar3 = local_c[2];
      piVar11[2] = 0;
      piVar11[3] = 0;
      uVar9 = CONCAT31((int3)((uint)local_c >> 8),bVar3) & 0xffffff0f;
      bVar6 = (byte)uVar9;
      *(undefined1 *)((int)piVar11 + -0xe) = 0;
      bVar10 = bVar3 >> 4;
      if (((puVar12[0x14c] & 1) != 0) && ((char)piVar11[0xb] == '\0')) {
        FUN_00417bac(piVar11 + -4,piVar11 + 7,piVar11 + 6,
                     CONCAT31((int3)(uVar9 >> 8),puVar12[0x14c]),puVar12[0x144],puVar12 + 0xa4,
                     puVar12[0x148],puVar12[0x147],puVar12[0x146],piVar11 + 9,piVar11 + 8,
                     piVar11 + 0xb,piVar11 + 10,2);
      }
      if (((puVar12[0x14d] & 1) != 0) && ((char)piVar11[0x11] == '\0')) {
        FUN_00417bac(piVar11 + -4,piVar11 + 0xd,piVar11 + 0xc,puVar12[0x14d],puVar12[0x145],
                     puVar12 + 0xf4,puVar12[0x14b],puVar12[0x14a],puVar12[0x149],piVar11 + 0xf,
                     piVar11 + 0xe,piVar11 + 0x11,piVar11 + 0x10,4);
      }
      if (*(char *)((int)piVar11 + 0x55) != '\0') {
        piVar1 = piVar11 + 0x12;
        *piVar1 = *piVar1 - (uint)*(ushort *)(puVar12 + 0x152);
        if (*piVar1 < 0) {
          piVar11[0x12] = 0;
        }
        *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 2;
      }
      bVar4 = *local_c;
      uVar9 = (uint)bVar4;
      bVar5 = bVar4 >> 4;
      if (bVar5 == 6) {
        *piVar11 = *piVar11 - (uVar9 & 0xf);
        if (*piVar11 < 0) {
          *piVar11 = 0;
        }
LAB_00418661:
        *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 2;
      }
      else {
        if (bVar5 == 7) {
          *piVar11 = *piVar11 + (uVar9 & 0xf);
          if (0x40 < *piVar11) {
            *piVar11 = 0x40;
          }
          goto LAB_00418661;
        }
        if (bVar5 == 0xb) {
          *(byte *)((int)piVar11 + 0x77) = bVar4 & 0xf;
          FUN_00417a1b(piVar11 + -4);
          cVar7 = *(char *)((int)piVar11 + 0x76) + *(char *)((int)piVar11 + 0x75);
          *(char *)((int)piVar11 + 0x75) = cVar7;
          if ('\x1f' < cVar7) {
            *(char *)((int)piVar11 + 0x75) = cVar7 + -0x40;
          }
        }
        else {
          if (bVar5 == 0xd) {
            piVar11[1] = piVar11[1] - (uVar9 & 0xf);
          }
          else {
            if (bVar5 != 0xe) {
              if (bVar5 == 0xf) {
                FUN_004179d8(piVar11 + -4);
              }
              goto LAB_00418665;
            }
            piVar11[1] = piVar11[1] + (uVar9 & 0xf);
          }
          *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 4;
        }
      }
LAB_00418665:
      if (bVar2 == 0) {
        if (local_c[2] == 0) goto LAB_0041884a;
        if (param_1[0x4d] % 3 == 1) {
          bVar2 = *(byte *)((int)param_1 + 0x22);
          bVar6 = bVar10;
        }
        else {
          if (param_1[0x4d] % 3 != 2) goto LAB_00418846;
          bVar2 = *(byte *)((int)param_1 + 0x22);
        }
        if ((bVar2 & 1) != 0) {
          piVar11[3] = (uint)bVar6 << 6;
        }
LAB_00418846:
        *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 1;
        goto LAB_0041884a;
      }
      if (bVar2 == 1) {
        piVar11[-1] = piVar11[-1] + (uint)*(byte *)((int)piVar11 + 0x69) * -4;
        piVar11[3] = 0;
        if (piVar11[-1] < 0x38) {
          piVar11[-1] = 0x38;
        }
        goto LAB_00418846;
      }
      if (bVar2 == 2) {
        piVar11[-1] = piVar11[-1] + (uint)*(byte *)(piVar11 + 0x1a) * 4;
        piVar11[3] = 0;
        goto LAB_00418846;
      }
      if (bVar2 == 3) {
        piVar11[3] = 0;
        FUN_004179d8(piVar11 + -4);
        goto LAB_0041884a;
      }
      if (bVar2 == 4) {
        FUN_00417a1b(piVar11 + -4);
        cVar7 = *(char *)((int)piVar11 + 0x76) + *(char *)((int)piVar11 + 0x75);
        *(char *)((int)piVar11 + 0x75) = cVar7;
        if ('\x1f' < cVar7) {
          *(char *)((int)piVar11 + 0x75) = cVar7 + -0x40;
        }
        goto LAB_0041884a;
      }
      if (bVar2 == 0xe) {
        if (bVar10 == 0xc) {
          if (param_1[0x4d] == (bVar3 & 0xf)) {
            *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 2;
            *piVar11 = 0;
          }
        }
        else if (bVar10 == 0xd) {
          if (param_1[0x4d] == (bVar3 & 0xf)) {
            FUN_00417fab(piVar11 + -4,local_8);
            *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 1;
            piVar11[-1] = piVar11[0x16];
            if (*local_c != 0) {
              FUN_00417c9f(piVar11 + -4,*local_c);
            }
            goto LAB_0041878a;
          }
          *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) & 0xf0;
        }
        goto LAB_0041884a;
      }
      if (((bVar2 != 0x1b) || (*(byte *)((int)piVar11 + 0x6f) == 0)) ||
         (param_1[0x4d] % (int)(uint)*(byte *)((int)piVar11 + 0x6f) != 0)) goto LAB_0041884a;
      if (*(char *)((int)piVar11 + 0x6e) == '\0') goto LAB_0041878a;
      switch(*(char *)((int)piVar11 + 0x6e)) {
      case '\x01':
        *piVar11 = *piVar11 + -1;
        break;
      case '\x02':
        *piVar11 = *piVar11 + -2;
        break;
      case '\x03':
        *piVar11 = *piVar11 + -4;
        break;
      case '\x04':
        *piVar11 = *piVar11 + -8;
        break;
      case '\x05':
        *piVar11 = *piVar11 + -0x10;
        break;
      case '\x06':
        iVar8 = (*piVar11 << 1) / 3;
        goto LAB_00418726;
      case '\a':
        *piVar11 = *piVar11 >> 1;
        break;
      case '\t':
        *piVar11 = *piVar11 + 1;
        break;
      case '\n':
        *piVar11 = *piVar11 + 2;
        break;
      case '\v':
        *piVar11 = *piVar11 + 4;
        break;
      case '\f':
        *piVar11 = *piVar11 + 8;
        break;
      case '\r':
        *piVar11 = *piVar11 + 0x10;
        break;
      case '\x0e':
        iVar8 = (*piVar11 * 3) / 2;
LAB_00418726:
        *piVar11 = iVar8;
        break;
      case '\x0f':
        *piVar11 = *piVar11 << 1;
      }
      if (0x40 < *piVar11) {
        *piVar11 = 0x40;
      }
      if (*piVar11 < 0) {
        *piVar11 = 0;
      }
      *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 2;
LAB_0041878a:
      *(byte *)((int)piVar11 + -0xe) = *(byte *)((int)piVar11 + -0xe) | 8;
LAB_0041884a:
      FUN_00417abb(piVar11 + -4,puVar12);
      FUN_00417d95(piVar11 + -4,local_8,param_1);
      local_c = local_c + 5;
      local_4 = local_4 + 1;
      piVar11 = piVar11 + 0x2b;
    } while (local_4 < (short)param_1[5]);
  }
  return;
}



// ==== 0x41897e ====

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_0041897e(int *param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  int *piVar2;
  short sVar3;
  uint uVar4;
  byte *pbVar5;
  void *pvVar6;
  int iVar7;
  undefined4 *puVar8;
  short *psVar9;
  uint *puVar10;
  uint *puVar11;
  undefined4 uVar12;
  undefined1 local_138 [4];
  int local_134;
  int local_130;
  uint local_12c;
  uint *local_128;
  byte *local_124;
  undefined4 local_120;
  uint local_11c;
  ushort local_118 [3];
  byte local_111;
  byte *local_110;
  byte local_109;
  char local_108 [256];
  undefined4 local_8;
  
  local_8 = DAT_00453d68;
  local_12c = 0;
  FUN_00419106(param_2,0,0);
  FUN_004190e8(local_108,0x11,param_2);
  uVar4 = 0;
  do {
    if (local_108[uVar4] != "1Extended Module: "[uVar4 + 1]) {
      return uVar4 & 0xffffff00;
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x11);
  param_1[0x57] = (int)&LAB_004188c7;
  *(undefined1 *)(param_1 + 0x4a) = 0x40;
  FUN_00419106(param_2,0x3c,0);
  FUN_004190e8(&local_134,4,param_2);
  piVar2 = param_1 + 4;
  FUN_004190e8(piVar2,6,param_2);
  FUN_004190e8(&local_12c,2,param_2);
  FUN_004190e8(param_1 + 8,0x108,param_2);
  FUN_00419106(param_2,local_134 + 0x3c,0);
  param_1[6] = 0;
  if (0 < (short)*piVar2) {
    local_110 = (byte *)(-0x28 - (int)param_1);
    pbVar5 = (byte *)(param_1 + 10);
    do {
      if (param_1[6] <= (int)(uint)*pbVar5) {
        param_1[6] = *pbVar5 + 1;
      }
      pbVar5 = pbVar5 + 1;
    } while ((int)(local_110 + (int)pbVar5) < (int)(short)*piVar2);
  }
  uVar4 = local_12c & 0xffff;
  if ((int)(local_12c & 0xffff) < param_1[6]) {
    uVar4 = param_1[6];
  }
  param_1[7] = uVar4;
  pvVar6 = _calloc(uVar4 << 3,1);
  local_11c = 0;
  *param_1 = (int)pvVar6;
  if ((short)local_12c != 0) {
    do {
      puVar10 = (uint *)(*param_1 + local_11c * 8);
      local_111 = 0;
      FUN_004190e8(&local_130,4,param_2);
      FUN_004190e8(&local_111,1,param_2);
      FUN_004190e8(local_118,2,param_2);
      *puVar10 = (uint)local_118[0];
      FUN_004190e8((int)&local_120 + 2,2,param_2);
      pbVar5 = _calloc((int)(short)param_1[5] * *puVar10 * 5,1);
      puVar10[1] = (uint)pbVar5;
      if ((local_120._2_2_ != 0) &&
         (local_128 = (uint *)0x0, local_110 = pbVar5, 0 < (int)((int)(short)param_1[5] * *puVar10))
         ) {
        local_124 = pbVar5 + 1;
        do {
          FUN_004190e8(&local_109,1,param_2);
          if ((char)local_109 < '\0') {
            if ((local_109 & 1) != 0) {
              FUN_004190e8(local_110,1,param_2);
            }
            if ((local_109 & 2) != 0) {
              FUN_004190e8(local_124,1,param_2);
            }
            if ((local_109 & 4) != 0) {
              FUN_004190e8(local_124 + 1,1,param_2);
            }
            if ((local_109 & 8) != 0) {
              FUN_004190e8(local_124 + 2,1,param_2);
            }
            if ((local_109 & 0x10) != 0) {
              uVar12 = 1;
              pbVar5 = local_124 + 3;
              goto LAB_00418ba9;
            }
          }
          else {
            if (local_109 != 0) {
              *local_110 = local_109;
            }
            uVar12 = 4;
            pbVar5 = local_124;
LAB_00418ba9:
            FUN_004190e8(pbVar5,uVar12,param_2);
          }
          if (*local_110 == 0x61) {
            *local_110 = 0xff;
          }
          if (0x80 < *local_124) {
            *local_124 = 0;
          }
          local_124 = local_124 + 5;
          local_110 = local_110 + 5;
          local_128 = (uint *)((int)local_128 + 1);
        } while ((int)local_128 < (int)((int)(short)param_1[5] * *puVar10));
      }
      local_11c = local_11c + 1;
    } while ((int)local_11c < (int)(local_12c & 0xffff));
  }
  uVar4 = local_12c & 0xffff;
  if ((int)(local_12c & 0xffff) < param_1[6]) {
    do {
      local_11c = uVar4;
      puVar8 = (undefined4 *)(*param_1 + local_11c * 8);
      *puVar8 = 0x40;
      pvVar6 = _calloc((short)param_1[5] * 0x140,1);
      local_11c = local_11c + 1;
      puVar8[1] = pvVar6;
      uVar4 = local_11c;
    } while ((int)local_11c < param_1[6]);
  }
  pvVar6 = _calloc((short)param_1[8] * 0x154,1);
  param_1[1] = (int)pvVar6;
  iVar7 = 0;
  local_11c = 0;
  if (0 < (short)param_1[8]) {
    local_124 = (byte *)0x0;
    do {
      puVar10 = (uint *)(param_1[1] + (int)local_124);
      local_110 = (byte *)FUN_00419123(param_2);
      FUN_004190e8(&local_130,4,param_2);
      local_110 = (byte *)((int)local_110 + local_130);
      FUN_00419106(param_2,0x17,1);
      uVar4 = FUN_004190e8(local_118,2,param_2);
      if (0x10 < local_118[0]) {
        return uVar4 & 0xffffff00;
      }
      *puVar10 = (uint)local_118[0];
      if (local_118[0] == 0) {
        for (iVar7 = 0x10; puVar10 = puVar10 + 1, iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar10 = (uint)&DAT_00d17580;
        }
        FUN_00419106(param_2,local_110,0);
      }
      else {
        local_109 = 0;
        FUN_004190e8(local_138,4,param_2);
        FUN_004190e8(puVar10 + 0x11,0x60,param_2);
        FUN_004190e8(puVar10 + 0x29,0x30,param_2);
        FUN_004190e8(puVar10 + 0x3d,0x30,param_2);
        FUN_004190e8(puVar10 + 0x51,0x10,param_2);
        *(short *)((int)puVar10 + 0x152) = *(short *)((int)puVar10 + 0x152) << 1;
        if ((byte)puVar10[0x51] < 2) {
          *(undefined1 *)(puVar10 + 0x53) = 0;
        }
        if (*(byte *)((int)puVar10 + 0x145) < 2) {
          *(undefined1 *)((int)puVar10 + 0x14d) = 0;
        }
        FUN_00419106(param_2,local_110,0);
        local_120 = 0;
        if (local_118[0] == 0) {
LAB_00418e78:
          puVar11 = puVar10 + local_120 + 1;
          for (iVar7 = 0x10 - local_120; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar11 = (uint)&DAT_00d17580;
            puVar11 = puVar11 + 1;
          }
        }
        else {
          local_128 = puVar10 + 1;
          do {
            puVar8 = _calloc(0x30,1);
            *local_128 = (uint)puVar8;
            FUN_004190e8(puVar8 + 1,0xe,param_2);
            *(undefined1 *)((int)puVar8 + 0x1d) = 1;
            *(undefined1 *)(puVar8 + 7) = 8;
            FUN_004190e8(&local_111,1,param_2);
            if ((local_111 & 1) != 0) {
              *(byte *)((int)puVar8 + 0x1d) = *(byte *)((int)puVar8 + 0x1d) & 0xfe | 2;
            }
            if ((local_111 & 2) != 0) {
              *(byte *)((int)puVar8 + 0x1d) = *(byte *)((int)puVar8 + 0x1d) & 0xfc | 4;
            }
            if ((local_111 & 0x10) != 0) {
              *(undefined1 *)(puVar8 + 7) = 0x10;
            }
            if ((*(byte *)((int)puVar8 + 0x1d) & 1) != 0) {
              puVar8[2] = 0;
              puVar8[3] = puVar8[1];
            }
            if (*(char *)(puVar8 + 7) == '\x10') {
              puVar8[1] = (uint)puVar8[1] >> 1;
              puVar8[2] = (uint)puVar8[2] >> 1;
              puVar8[3] = (uint)puVar8[3] >> 1;
            }
            if (puVar8[3] == 0) {
              puVar8[2] = 0;
              puVar8[3] = puVar8[1];
              *(undefined1 *)((int)puVar8 + 0x1d) = 1;
            }
            FUN_004190e8(&local_109,1,param_2);
            puVar8[6] = (uint)local_109;
            FUN_004190e8(&local_109,1,param_2);
            *(byte *)((int)puVar8 + 0x1f) = local_109;
            FUN_00419106(param_2,0x17,1);
            local_110 = (byte *)(puVar8[1] << 1);
            if ((void *)*puVar8 != (void *)0x0) {
              _free((void *)*puVar8);
            }
            if (local_110 == (byte *)0x0) {
              *puVar8 = 0;
            }
            else {
              pvVar6 = _calloc((size_t)(local_110 + 0x10),1);
              *puVar8 = pvVar6;
            }
            local_120 = local_120 + 1;
            local_128 = local_128 + 1;
          } while (local_120 < local_118[0]);
          if (local_120 < 0x10) goto LAB_00418e78;
        }
        local_120 = 0;
        if (local_118[0] != 0) {
          local_128 = puVar10 + 1;
          do {
            piVar2 = (int *)*local_128;
            iVar7 = piVar2[1];
            uVar4 = (uint)*(byte *)(piVar2 + 7) * iVar7 >> 3;
            if (iVar7 != 0) {
              local_110 = _calloc(iVar7 * 2 + 0x10,1);
              if ((code *)param_1[0x58] == (code *)0x0) {
                FUN_004190e8(local_110,uVar4,param_2);
              }
              else {
                (*(code *)param_1[0x58])(local_110,uVar4,(char)piVar2[7],local_11c,local_120);
                FUN_00419106(param_2,uVar4,1);
              }
              if ((char)piVar2[7] == '\b') {
                psVar9 = (short *)*piVar2;
                iVar7 = 0;
                if (0 < piVar2[1]) {
                  do {
                    *psVar9 = (ushort)local_110[iVar7] << 8;
                    psVar9 = psVar9 + 1;
                    iVar7 = iVar7 + 1;
                  } while (iVar7 < piVar2[1]);
                }
                *(undefined1 *)(piVar2 + 7) = 0x10;
                _free(local_110);
              }
              else {
                _free((void *)*piVar2);
                *piVar2 = (int)local_110;
              }
              FUN_00407ca6(piVar2,piVar2,local_11c,local_120);
              sVar3 = 0;
              if (param_1[0x58] == 0) {
                psVar9 = (short *)*piVar2;
                uVar4 = 0;
                if (piVar2[1] != 0) {
                  do {
                    sVar3 = *psVar9 + sVar3;
                    *psVar9 = sVar3;
                    psVar9 = psVar9 + 1;
                    uVar4 = uVar4 + 1;
                  } while (uVar4 < (uint)piVar2[1]);
                }
              }
              iVar7 = *piVar2;
              if (*(char *)((int)piVar2 + 0x1d) == '\x04') {
                puVar1 = (undefined2 *)(iVar7 + (piVar2[3] + piVar2[2]) * 2);
                *puVar1 = puVar1[-1];
              }
              else if (*(char *)((int)piVar2 + 0x1d) == '\x02') {
                *(undefined2 *)(iVar7 + (piVar2[3] + piVar2[2]) * 2) =
                     *(undefined2 *)(iVar7 + piVar2[2] * 2);
              }
            }
            local_120 = local_120 + 1;
            local_128 = local_128 + 1;
          } while (local_120 < local_118[0]);
        }
      }
      iVar7 = (int)(short)param_1[8];
      local_11c = local_11c + 1;
      local_124 = (byte *)((int)local_124 + 0x154);
    } while ((int)local_11c < iVar7);
  }
  return CONCAT31((int3)((uint)iVar7 >> 8),1);
}



// ==== 0x419023 ====

void FUN_00419023(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  if ((((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) || ((param_4 == 0 || (param_5 == 0))))
  {
    DAT_00d0fe8c = 0;
    DAT_00d0fe90 = 0;
    DAT_00d0fe94 = 0;
    DAT_00d0fe98 = 0;
    DAT_00d0fe9c = 0;
  }
  else {
    DAT_00d0fe8c = param_1;
    DAT_00d0fe90 = param_2;
    DAT_00d0fe94 = param_3;
    DAT_00d0fe98 = param_4;
    DAT_00d0fe9c = param_5;
  }
  return;
}



// ==== 0x419090 ====

undefined1 * FUN_00419090(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *_Memory;
  int iVar1;
  
  _Memory = _calloc(0x18,1);
  *_Memory = param_2;
  *(undefined4 *)(_Memory + 0x14) = param_3;
  iVar1 = (*DAT_00d0fe8c)(param_1);
  *(int *)(_Memory + 0x10) = iVar1;
  if (iVar1 == 0) {
    _free(_Memory);
    return (undefined1 *)0x0;
  }
  return _Memory;
}



// ==== 0x4190cc ====

void FUN_004190cc(void *param_1)

{
  if (param_1 != (void *)0x0) {
    (*DAT_00d0fe90)(*(undefined4 *)((int)param_1 + 0x10));
    _free(param_1);
  }
  return;
}



// ==== 0x4190e8 ====

void FUN_004190e8(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (param_3 == 0) {
    return;
  }
  (*DAT_00d0fe94)(param_1,param_2,*(undefined4 *)(param_3 + 0x10));
  return;
}



// ==== 0x419106 ====

void FUN_00419106(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (param_1 != 0) {
    (*DAT_00d0fe98)(*(undefined4 *)(param_1 + 0x10),param_2,param_3);
  }
  return;
}



// ==== 0x419123 ====

void FUN_00419123(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  (*DAT_00d0fe9c)(*(undefined4 *)(param_1 + 0x10));
  return;
}



// ==== 0x419138 ====

void Direct3DCreate9(void)

{
                    /* WARNING: Could not recover jumptable at 0x00419138. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  Direct3DCreate9();
  return;
}



// ==== 0x41913e ====

void DirectSoundCreate8(void)

{
                    /* WARNING: Could not recover jumptable at 0x0041913e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DirectSoundCreate8();
  return;
}



// ==== 0x419144 ====

void acmStreamConvert(void)

{
                    /* WARNING: Could not recover jumptable at 0x00419144. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  acmStreamConvert();
  return;
}



// ==== 0x41914a ====

void acmStreamPrepareHeader(void)

{
                    /* WARNING: Could not recover jumptable at 0x0041914a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  acmStreamPrepareHeader();
  return;
}



// ==== 0x419150 ====

void acmStreamOpen(void)

{
                    /* WARNING: Could not recover jumptable at 0x00419150. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  acmStreamOpen();
  return;
}



// ==== 0x419160 ====

void FUN_00419160(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  DAT_00d102c4 = _malloc(0x10000);
  iVar3 = 0;
  do {
    iVar2 = 0;
    uVar4 = 0;
    do {
      *(char *)((int)DAT_00d102c4 + iVar2 + iVar3 * 0x100) = (char)(uVar4 / 0x7f);
      iVar2 = iVar2 + 1;
      uVar4 = uVar4 + iVar3;
    } while (iVar2 < 0x100);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x80);
  iVar3 = 0x8000;
  do {
    iVar2 = 0;
    do {
      uVar1 = __ftol();
      iVar2 = iVar2 + 1;
      *(undefined1 *)((int)DAT_00d102c4 + iVar2 + iVar3 + -1) = uVar1;
    } while (iVar2 < 0x100);
    iVar3 = iVar3 + 0x100;
  } while (iVar3 < 0x10000);
  DAT_00d102c8 = _malloc(0x40000);
  DAT_00d102cc = _malloc(0x40000);
  DAT_00d102ac = _malloc(0x40000);
  DAT_00d102b0 = _malloc(0x40000);
  DAT_00d102b4 = _malloc(0x40000);
  DAT_00d102b8 = _malloc(0x40000);
  DAT_00d0fea8 = _malloc(0x40000);
  DAT_00d0fea4 = _malloc(0x10000);
  return;
}



// ==== 0x4192a0 ====

/* WARNING: Type propagation algorithm not settling */

void FUN_004192a0(int param_1)

{
  undefined4 uVar1;
  HANDLE hFile;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  DWORD local_20 [5];
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_20[4] = DAT_00453d00;
  local_20[1] = 0x100;
  local_20[3] = 0x18;
  local_c = DAT_00453d04;
  local_8 = DAT_00453d08;
  local_4 = DAT_00453d0c;
  hFile = CreateFileA(s_tex00000_tga_00453cf0,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,
                      (HANDLE)0x0);
  WriteFile(hFile,local_20 + 4,0xc,local_20,(LPOVERLAPPED)0x0);
  WriteFile(hFile,local_20 + 1,2,local_20,(LPOVERLAPPED)0x0);
  WriteFile(hFile,local_20 + 1,2,local_20,(LPOVERLAPPED)0x0);
  WriteFile(hFile,local_20 + 3,2,local_20,(LPOVERLAPPED)0x0);
  iVar2 = 0;
  local_20[2] = 0x100;
  puVar4 = (undefined4 *)(param_1 + 0x3fc00);
  do {
    iVar3 = 0x100;
    puVar5 = puVar4;
    do {
      uVar1 = *puVar5;
      puVar5 = puVar5 + 1;
      *(char *)((int)DAT_00d0fea8 + iVar2) = (char)uVar1;
      *(char *)((int)DAT_00d0fea8 + iVar2 + 1) = (char)((uint)uVar1 >> 8);
      *(char *)((int)DAT_00d0fea8 + iVar2 + 2) = (char)((uint)uVar1 >> 0x10);
      iVar2 = iVar2 + 3;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar4 = puVar4 + -0x100;
    local_20[2] = local_20[2] + -1;
  } while (local_20[2] != 0);
  WriteFile(hFile,DAT_00d0fea8,0x30000,local_20,(LPOVERLAPPED)0x0);
  CloseHandle(hFile);
  s_tex00000_tga_00453cf0[7] = s_tex00000_tga_00453cf0[7] + '\x01';
  if (s_tex00000_tga_00453cf0[7] == ':') {
    s_tex00000_tga_00453cf0[7] = '0';
    s_tex00000_tga_00453cf0[6] = s_tex00000_tga_00453cf0[6] + '\x01';
  }
  return;
}



// ==== 0x419400 ====

undefined4 FUN_00419400(LPCSTR param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  HANDLE hFile;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  int iVar7;
  DWORD local_4;
  
  hFile = CreateFileA(param_1,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    return 0;
  }
  SetFilePointer(hFile,0x12,(PLONG)0x0,0);
  ReadFile(hFile,DAT_00d0fea8,0x30000,&local_4,(LPOVERLAPPED)0x0);
  CloseHandle(hFile);
  iVar3 = 0;
  param_1 = (LPCSTR)0x100;
  puVar5 = (uint *)(param_2 + 0x3fc00);
  do {
    iVar7 = 0x100;
    puVar6 = puVar5;
    do {
      puVar1 = (undefined1 *)((int)DAT_00d0fea8 + iVar3);
      iVar4 = iVar3 + 2;
      iVar2 = iVar3 + 1;
      iVar3 = iVar3 + 3;
      iVar7 = iVar7 + -1;
      *puVar6 = (uint)CONCAT21(CONCAT11(*(undefined1 *)((int)DAT_00d0fea8 + iVar4),
                                        *(undefined1 *)((int)DAT_00d0fea8 + iVar2)),*puVar1);
      puVar6 = puVar6 + 1;
    } while (iVar7 != 0);
    puVar5 = puVar5 + -0x100;
    param_1 = (LPCSTR)((int)param_1 + -1);
  } while (param_1 != (LPCSTR)0x0);
  s_tex00000_tga_00453cf0[7] = s_tex00000_tga_00453cf0[7] + '\x01';
  if (s_tex00000_tga_00453cf0[7] == ':') {
    s_tex00000_tga_00453cf0[7] = '0';
    s_tex00000_tga_00453cf0[6] = s_tex00000_tga_00453cf0[6] + '\x01';
  }
  return 1;
}



// ==== 0x4194f0 ====

void FUN_004194f0(void)

{
  if (DAT_00d102cc != (void *)0x0) {
    _free(DAT_00d102cc);
  }
  if (DAT_00d102c8 != (void *)0x0) {
    _free(DAT_00d102c8);
  }
  if (DAT_00d102ac != (void *)0x0) {
    _free(DAT_00d102ac);
  }
  if (DAT_00d102b0 != (void *)0x0) {
    _free(DAT_00d102b0);
  }
  if (DAT_00d102b4 != (void *)0x0) {
    _free(DAT_00d102b4);
  }
  if (DAT_00d102b8 != (void *)0x0) {
    _free(DAT_00d102b8);
  }
  if (DAT_00d0fea8 != (void *)0x0) {
    _free(DAT_00d0fea8);
  }
  if (DAT_00d0fea4 != (void *)0x0) {
    _free(DAT_00d0fea4);
  }
  return;
}



// ==== 0x419580 ====

uint FUN_00419580(undefined4 param_1,float param_2,float param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  for (; param_2 < 0.0; param_2 = param_2 + 256.0) {
  }
  for (; 256.0 <= param_2; param_2 = param_2 - 256.0) {
  }
  for (; param_3 < 0.0; param_3 = param_3 + 256.0) {
  }
  for (; 256.0 <= param_3; param_3 = param_3 - 256.0) {
  }
  FUN_0041ec50((double)param_2);
  __ftol();
  FUN_0041ec50((double)param_3);
  __ftol();
  iVar1 = __ftol();
  uVar2 = __ftol();
  uVar3 = __ftol();
  return uVar3 | (iVar1 << 8 | uVar2) << 8;
}



// ==== 0x419840 ====

undefined4 FUN_00419840(int param_1,float param_2,float param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  short sVar11;
  unkbyte10 in_ST0;
  short sVar12;
  unkbyte10 in_ST1;
  short sVar15;
  short sVar16;
  short sVar17;
  unkbyte10 in_ST2;
  unkbyte10 Var13;
  short sVar18;
  short sVar19;
  ushort uVar20;
  unkbyte10 in_ST4;
  unkbyte10 in_ST5;
  ushort uVar21;
  ushort uVar22;
  ushort uVar23;
  ushort uVar24;
  ushort uVar25;
  ushort uVar26;
  ushort uVar27;
  unkbyte10 Var14;
  
  iVar5 = ((int)ROUND(param_2 * 256.0) & 0xffU) * 0x10101;
  iVar6 = ((int)ROUND(param_3 * 256.0) & 0xffU) * 0x10101;
  uVar10 = (int)ROUND(param_3 * 256.0) & 0xff00;
  uVar8 = ((int)ROUND(param_2 * 256.0) & 0xff00U) >> 8;
  uVar1 = *(undefined4 *)(param_1 + (uVar8 + uVar10) * 4);
  uVar7 = CONCAT31((uint3)(ushort)((unkuint10)in_ST4 >> 0x40) << 8,(char)((uint)uVar1 >> 0x18));
  uVar9 = uVar8 + 1 & 0xff;
  uVar2 = *(undefined4 *)(param_1 + (uVar9 + uVar10) * 4);
  uVar25 = (ushort)((unkuint10)in_ST5 >> 0x40);
  uVar10 = uVar10 + 0x100 & 0xff00;
  uVar3 = *(undefined4 *)(param_1 + (uVar9 + uVar10) * 4);
  uVar4 = *(undefined4 *)(param_1 + (uVar8 + uVar10) * 4);
  uVar8 = CONCAT31((uint3)(ushort)((unkuint10)in_ST0 >> 0x40) << 8,(char)((uint)iVar5 >> 0x18));
  uVar21 = (ushort)(byte)iVar5;
  Var14 = CONCAT37((int3)(((unkuint10)(ushort)((unkuint10)in_ST2 >> 0x40) << 0x40) >> 0x38),
                   0xff0000ffffffff);
  Var13 = CONCAT55((int5)(((unkuint10)(uint)((unkuint10)Var14 >> 0x30) << 0x30) >> 0x28),
                   0xffffffffff);
  uVar9 = CONCAT31((uint3)(ushort)((unkuint10)in_ST1 >> 0x40) << 8,(char)((uint)iVar6 >> 0x18));
  uVar23 = (ushort)(byte)iVar6;
  uVar22 = (ushort)(byte)((uint)iVar5 >> 8);
  sVar18 = (short)(CONCAT73((int7)(((unkuint10)(uint6)((unkuint10)Var13 >> 0x20) << 0x20) >> 0x18),
                            0xffffff) >> 0x10);
  sVar15 = sVar18 - uVar22;
  sVar11 = (short)(CONCAT55((uint5)uVar8 << 8,CONCAT14((char)((uint)iVar5 >> 0x10),iVar5)) >> 0x20);
  sVar19 = (short)((unkuint10)Var13 >> 0x20);
  sVar16 = sVar19 - sVar11;
  sVar17 = (short)((unkuint10)Var14 >> 0x30);
  uVar24 = (ushort)(byte)((uint)iVar6 >> 8);
  sVar18 = sVar18 - uVar24;
  sVar12 = (short)(CONCAT55((uint5)uVar9 << 8,CONCAT14((char)((uint)iVar6 >> 0x10),iVar6)) >> 0x20);
  sVar19 = sVar19 - sVar12;
  uVar20 = ((ushort)((short)uVar7 * (sVar17 - (short)uVar8)) >> 8) * (sVar17 - (short)uVar9);
  uVar21 = ((ushort)((byte)uVar3 * uVar21) >> 8) * uVar23 +
           ((ushort)((byte)uVar4 * uVar23) >> 8) * (0xff - uVar21) +
           ((ushort)((byte)uVar2 * uVar21) >> 8) * (0xff - uVar23) +
           ((ushort)((ushort)(byte)uVar1 * (0xff - uVar21)) >> 8) * (0xff - uVar23);
  uVar23 = ((ushort)((byte)((uint)uVar3 >> 8) * uVar22) >> 8) * uVar24 +
           ((ushort)((byte)((uint)uVar4 >> 8) * uVar24) >> 8) * sVar15 +
           ((ushort)((byte)((uint)uVar2 >> 8) * uVar22) >> 8) * sVar18 +
           ((ushort)((ushort)(byte)((uint)uVar1 >> 8) * sVar15) >> 8) * sVar18;
  uVar25 = ((ushort)((short)(CONCAT55((uint5)uVar25 << 0x18,
                                      CONCAT14((char)((uint)uVar3 >> 0x10),uVar3)) >> 0x20) * sVar11
                    ) >> 8) * sVar12 +
           ((ushort)((short)(CONCAT55((uint5)uVar25 << 0x18,
                                      CONCAT14((char)((uint)uVar4 >> 0x10),uVar4)) >> 0x20) * sVar12
                    ) >> 8) * sVar16 +
           ((ushort)((short)(CONCAT55((uint5)uVar25 << 0x18,
                                      CONCAT14((char)((uint)uVar2 >> 0x10),uVar2)) >> 0x20) * sVar11
                    ) >> 8) * sVar19 +
           ((ushort)((short)(CONCAT55((uint5)uVar7 << 8,CONCAT14((char)((uint)uVar1 >> 0x10),uVar1))
                            >> 0x20) * sVar16) >> 8) * sVar19;
  uVar22 = uVar21 >> 8;
  uVar24 = uVar23 >> 8;
  uVar26 = uVar25 >> 8;
  uVar27 = uVar20 >> 8;
  return CONCAT13((uVar27 != 0) * (uVar27 < 0x100) * (char)(uVar20 >> 8) - (0xff < uVar27),
                  CONCAT12((uVar26 != 0) * (uVar26 < 0x100) * (char)(uVar25 >> 8) - (0xff < uVar26),
                           CONCAT11((uVar24 != 0) * (uVar24 < 0x100) * (char)(uVar23 >> 8) -
                                    (0xff < uVar24),
                                    (uVar22 != 0) * (uVar22 < 0x100) * (char)(uVar21 >> 8) -
                                    (0xff < uVar22))));
}



// ==== 0x419950 ====

void FUN_00419950(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (DAT_00d102d0 != '\0') {
    FUN_00419840();
    return;
  }
  FUN_00419580(param_1,param_2,param_3);
  return;
}



// ==== 0x419980 ====

undefined4 * FUN_00419980(int *param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  
  if (DAT_00d102d2 == '\0') {
    FUN_00419160();
    DAT_00d102d2 = '\x01';
  }
  DAT_00d0fea0 = param_2;
  iVar7 = 0;
  piVar2 = param_1;
  do {
    piVar1 = piVar2 + 1;
    piVar2 = piVar2 + 1;
    iVar7 = iVar7 + 1;
  } while (*piVar1 != 0);
  DAT_00d102d4 = 0;
  DAT_00d102d8 = 0;
  piVar2 = param_1;
  iVar5 = iVar7;
  if (0 < iVar7) {
    do {
      DAT_00d102d4 = DAT_00d102d4 + (uint)*(byte *)(*piVar2 + 3);
      iVar5 = iVar5 + -1;
      piVar2 = piVar2 + 1;
    } while (iVar5 != 0);
  }
  puVar3 = _malloc(iVar7 * 4);
  if (0 < iVar7) {
    puVar6 = puVar3;
    do {
      uVar4 = FUN_00419a30(*(undefined4 *)((int)puVar6 + ((int)param_1 - (int)puVar3)));
      *puVar6 = uVar4;
      puVar6 = puVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  DAT_00d102d4 = 0;
  DAT_00d102d8 = 0;
  FUN_004194f0();
  return puVar3;
}



// ==== 0x419a30 ====

void * FUN_00419a30(undefined4 param_1)

{
  void *pvVar1;
  
  pvVar1 = _malloc(0x40000);
  FUN_00419a50(param_1,pvVar1);
  return pvVar1;
}



// ==== 0x419a50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00419a50(uint *param_1,undefined4 *param_2)

{
  char cVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar3 = param_1;
  if ((param_1 != (uint *)0x0) && (param_2 != (undefined4 *)0x0)) {
    if (DAT_00d102c8 == 0) {
      FUN_00419160();
    }
    if ((DAT_00d102d1 != '\0') &&
       (iVar4 = FUN_00419400(s_tex00000_tga_00453cf0,param_2), iVar4 != 0)) {
      DAT_00d102d8 = DAT_00d102d8 + (uint)*(byte *)((int)param_1 + 3);
      (*DAT_00d0fea0)((float)DAT_00d102d8 / (float)DAT_00d102d4);
      return;
    }
    *DAT_00d0fea4 = *param_1;
    FUN_0041a0f0(DAT_00d102c8);
    FUN_0041a0f0(DAT_00d102cc);
    FUN_0041a0f0(DAT_00d102ac);
    FUN_0041a0f0(DAT_00d102b0);
    FUN_0041a0f0(DAT_00d102b4);
    FUN_0041a0f0(DAT_00d102b8);
    if ((undefined *)(*DAT_00d0fea4 & 0xffffff) == &DAT_00475441) {
      param_1 = (uint *)((int)*DAT_00d0fea4 >> 0x18);
      iVar4 = 4;
      if (0 < (int)param_1) {
        iVar6 = 0;
        do {
          pcVar5 = (char *)(iVar4 + iVar6 + (int)puVar3);
          cVar1 = *pcVar5;
          _DAT_00d102bc = (byte *)(pcVar5 + 1);
          bVar2 = *_DAT_00d102bc;
          if (bVar2 < 4) {
            if (cVar1 == '\x01') {
              FUN_0041a740(bVar2,pcVar5[2],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7]);
            }
            else if (cVar1 == '\x02') {
              FUN_0041aa30(bVar2,pcVar5[8],pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5]);
            }
            else if (cVar1 == '\x03') {
              FUN_0041a830(bVar2,pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7],
                           pcVar5[8]);
            }
            else if (cVar1 == '\x04') {
              FUN_0041ab20(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '\x05') {
              FUN_0041a420(bVar2,pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7]);
            }
            else if (cVar1 == '\x06') {
              FUN_0041a0f0((&DAT_00d102ac)[bVar2]);
            }
            else if (cVar1 == '\n') {
              FUN_0041ac40(bVar2,pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7]);
            }
            else if (cVar1 == '\v') {
              FUN_0041aec0(bVar2,pcVar5[2],pcVar5[3]);
            }
            else if (cVar1 == '\f') {
              FUN_0041ad80(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x0e') {
              FUN_0041af40(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x0f') {
              FUN_0041b870(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x11') {
              FUN_0041aff0(bVar2,pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7]);
            }
            else if (cVar1 == '\x12') {
              FUN_0041ba40(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '\x14') {
              FUN_0041b150(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '\x15') {
              FUN_0041b270(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x17') {
              FUN_0041b360(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '\x18') {
              FUN_0041b420(bVar2,pcVar5[2],pcVar5[3]);
            }
            else if (cVar1 == '\x19') {
              FUN_0041b4c0(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x1a') {
              FUN_0041bbf0(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x1b') {
              FUN_0041bc90(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x1e') {
              FUN_0041b570(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\x1f') {
              FUN_0041b540(bVar2);
            }
            else if (cVar1 == ' ') {
              FUN_0041b2c0(bVar2,pcVar5[2],pcVar5[3]);
            }
            else if (cVar1 == '!') {
              FUN_0041b670(bVar2,pcVar5[2]);
            }
            else if (cVar1 == '\"') {
              FUN_0041b6d0(bVar2,pcVar5[2],pcVar5[3]);
            }
            else if (cVar1 == '#') {
              FUN_0041b770(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '$') {
              FUN_0041c0a0(bVar2,pcVar5[2],pcVar5[3]);
            }
            else if (cVar1 == '%') {
              FUN_0041c180(bVar2,pcVar5[2],pcVar5[3],pcVar5[4],pcVar5[5],pcVar5[6],pcVar5[7],
                           pcVar5[8]);
            }
            else if (cVar1 == '&') {
              FUN_0041c2a0(bVar2,pcVar5[2],pcVar5[3],pcVar5[4]);
            }
            else if (cVar1 == '\'') {
              FUN_0041c3d0(bVar2);
            }
            else if (cVar1 == '(') {
              FUN_0041b820(bVar2,pcVar5 + 9,
                           ((uint)(byte)pcVar5[2] * 0x100 + (uint)(byte)pcVar5[3]) * 0x100 +
                           (uint)(byte)pcVar5[4],
                           ((uint)(byte)pcVar5[5] * 0x100 + (uint)(byte)pcVar5[6]) * 0x100 +
                           (uint)(byte)pcVar5[7]);
              iVar4 = iVar4 + 0x2000;
            }
          }
          DAT_00d102d8 = DAT_00d102d8 + 1;
          (*DAT_00d0fea0)((float)DAT_00d102d8 / (float)DAT_00d102d4);
          iVar6 = iVar6 + 9;
          param_1 = (uint *)((int)param_1 + -1);
        } while (param_1 != (uint *)0x0);
      }
      puVar7 = DAT_00d102ac;
      for (iVar4 = 0x10000; iVar4 != 0; iVar4 = iVar4 + -1) {
        *param_2 = *puVar7;
        puVar7 = puVar7 + 1;
        param_2 = param_2 + 1;
      }
      if (DAT_00d102d1 != '\0') {
        FUN_004192a0(DAT_00d102ac);
      }
    }
  }
  return;
}



// ==== 0x41a0f0 ====

void FUN_0041a0f0(undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = 0x10000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}



// ==== 0x41a100 ====

int FUN_0041a100(uint param_1)

{
  param_1 = param_1 << 0xd ^ param_1;
  return (int)((param_1 * param_1 * 0x3d73 + 0xc0ae5) * (DAT_00d102c0 + param_1) + 0x5208dd0d) /
         0x3047;
}



// ==== 0x41a150 ====

float10 FUN_0041a150(float param_1,float param_2,float param_3,float param_4,float param_5,
                    float param_6)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)param_5 / (float10)param_6;
  fVar2 = ((float10)param_4 - (float10)param_3) - ((float10)param_1 - (float10)param_2);
  return ((float10)param_3 - (float10)param_1) * fVar1 +
         fVar1 * fVar1 * fVar1 * fVar2 +
         (((float10)param_1 - (float10)param_2) - fVar2) * fVar1 * fVar1 + (float10)param_2;
}



// ==== 0x41a1a0 ====

void FUN_0041a1a0(float *param_1,int param_2,float *param_3)

{
  float fVar1;
  float *pfVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  float *pfVar9;
  float *pfVar10;
  float10 fVar11;
  float *local_1c;
  float *local_18;
  float *local_14;
  float *local_10;
  int local_c;
  
  pfVar2 = param_1;
  fVar1 = (float)param_3 * 0.00390625;
  local_14 = (float *)0x0;
  for (iVar5 = 0x10000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_1 = 0.0;
    param_1 = param_1 + 1;
  }
  param_1 = (float *)0x0;
  param_3 = pfVar2;
  do {
    iVar5 = 0;
    pfVar9 = param_3;
    do {
      iVar6 = (int)local_14 + 1;
      bVar3 = FUN_0041a100(local_14);
      iVar5 = iVar5 + param_2;
      *pfVar9 = (float)bVar3 * fVar1;
      pfVar9 = pfVar9 + param_2;
      local_14 = (float *)iVar6;
    } while (iVar5 < 0x100);
    param_1 = (float *)((int)param_1 + param_2);
    param_3 = param_3 + param_2 * 0x100;
  } while ((int)param_1 < 0x100);
  iVar5 = 0;
  do {
    uVar8 = 0;
    do {
      if (uVar8 != 0) {
        uVar4 = 0x100U - param_2 & uVar8;
        uVar7 = uVar4 + param_2 & 0xff;
        fVar11 = (float10)FUN_0041a150(pfVar2[(uVar4 - param_2 & 0xff) + iVar5],
                                       pfVar2[uVar4 + iVar5],pfVar2[iVar5 + uVar7],
                                       pfVar2[(uVar7 + param_2 & 0xff) + iVar5],
                                       (float)(int)(param_2 - 1U & uVar8),(float)param_2);
        pfVar2[iVar5 + uVar8] = (float)fVar11;
      }
      uVar8 = uVar8 + 1;
    } while ((int)uVar8 < 0x100);
    iVar5 = iVar5 + param_2 * 0x100;
  } while (iVar5 < 0x10000);
  local_14 = pfVar2;
  param_1 = (float *)0x0;
  do {
    if (param_1 != (float *)0x0) {
      uVar8 = 0x100U - param_2 & (uint)param_1;
      uVar4 = uVar8 + param_2 & 0xff;
      local_1c = pfVar2 + uVar4 * 0x100;
      local_18 = pfVar2 + (uVar4 + param_2 & 0xff) * 0x100;
      local_10 = local_14;
      pfVar9 = pfVar2 + uVar8 * 0x100;
      pfVar10 = pfVar2 + (uVar8 - param_2 & 0xff) * 0x100;
      local_c = 0x100;
      do {
        fVar11 = (float10)FUN_0041a150(*pfVar10,*pfVar9,*local_1c,*local_18,
                                       (float)(int)(param_2 - 1U & (uint)param_1),(float)param_2);
        *local_10 = (float)fVar11;
        local_1c = local_1c + 1;
        local_10 = local_10 + 1;
        pfVar10 = pfVar10 + 1;
        pfVar9 = pfVar9 + 1;
        local_18 = local_18 + 1;
        local_c = local_c + -1;
      } while (local_c != 0);
    }
    param_1 = (float *)((int)param_1 + 1);
    local_14 = local_14 + 0x100;
  } while ((int)param_1 < 0x100);
  return;
}



// ==== 0x41a420 ====

void FUN_0041a420(int param_1,char param_2,int param_3,int param_4,uint param_5,uint param_6,
                 uint param_7)

{
  uint uVar1;
  void *_Memory;
  int iVar2;
  byte bVar3;
  uint *puVar4;
  
  if (param_3 != 0) {
    DAT_00d102c0 = ((param_4 << 8 | param_5) << 8 | param_6) << 8 | param_7;
    _Memory = _malloc(0x40000);
    FUN_0041a1a0(_Memory,param_3,0x437f0000);
    bVar3 = ('\x02' - param_2) * '\b';
    param_3 = 0x10000;
    puVar4 = (uint *)(&DAT_00d102ac)[param_1];
    do {
      uVar1 = *puVar4;
      iVar2 = __ftol();
      if (iVar2 < 0x100) {
        if (iVar2 < 0) {
          iVar2 = 0;
        }
      }
      else {
        iVar2 = 0xff;
      }
      *puVar4 = iVar2 << (bVar3 & 0x1f) | uVar1 & 0xffffffU - (0xff << (bVar3 & 0x1f));
      param_3 = param_3 + -1;
      puVar4 = puVar4 + 1;
    } while (param_3 != 0);
    _free(_Memory);
  }
  return;
}



// ==== 0x41a500 ====

void FUN_0041a500(int *param_1,int param_2)

{
  int iVar1;
  
  param_2 = param_2 - (int)param_1;
  iVar1 = 0x10000;
  do {
    *param_1 = *param_1 + *(int *)(param_2 + (int)param_1);
    param_1 = param_1 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



// ==== 0x41a530 ====

void FUN_0041a530(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int *piVar13;
  undefined4 *puVar14;
  float10 fVar15;
  float10 extraout_ST0;
  int *piStack0000000c;
  int local_10;
  int local_c;
  
  iVar2 = (int)param_2;
  piVar1 = param_1;
  local_10 = 0;
  for (iVar10 = 0x10000; iVar10 != 0; iVar10 = iVar10 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  param_1 = (int *)0x0;
  piStack0000000c = piVar1;
  do {
    iVar10 = 0;
    piVar6 = piStack0000000c;
    do {
      iVar11 = local_10 + 1;
      FUN_0041a100(local_10);
      iVar3 = __ftol();
      *piVar6 = iVar3 << 0x10;
      iVar10 = iVar10 + (int)param_2;
      piVar6 = piVar6 + (int)param_2;
      local_10 = iVar11;
    } while (iVar10 < 0x100);
    param_1 = (int *)((int)param_1 + (int)param_2);
    piStack0000000c = piStack0000000c + (int)param_2 * 0x100;
  } while ((int)param_1 < 0x100);
  param_1 = (int *)0x0;
  if (0 < (int)param_2) {
    fVar15 = (float10)(int)param_2;
    puVar14 = &DAT_00d0feac;
    do {
      fcos(((float10)(int)param_1 * (float10)3.1415927410125732) / fVar15);
      uVar4 = __ftol();
      *puVar14 = uVar4;
      param_1 = (int *)((int)param_1 + 1);
      puVar14 = puVar14 + 1;
      fVar15 = extraout_ST0;
    } while ((int)param_1 < (int)param_2);
  }
  iVar3 = 0;
  uVar5 = 0x100 - (int)param_2;
  iVar10 = (int)param_2 * 0x100;
  piVar6 = piVar1;
  do {
    uVar12 = 0;
    param_2 = piVar6;
    do {
      uVar7 = uVar5 & uVar12;
      uVar8 = iVar2 - 1U & uVar12;
      uVar12 = uVar12 + 1;
      *param_2 = ((piVar1[(uVar7 + iVar2 & 0xff) + iVar3] - piVar1[iVar3 + uVar7]) *
                  (&DAT_00d0feac)[uVar8] >> 8) + piVar1[iVar3 + uVar7];
      param_2 = param_2 + 1;
    } while ((int)uVar12 < 0x100);
    iVar3 = iVar3 + iVar10;
    piVar6 = piVar6 + iVar2 * 0x100;
  } while (iVar3 < 0x10000);
  param_2 = piVar1;
  param_1 = (int *)0x0;
  do {
    if (param_1 != (int *)0x0) {
      uVar12 = uVar5 & (uint)param_1;
      local_c = 0x100;
      piVar6 = piVar1 + (uVar12 + iVar2 & 0xff) * 0x100;
      piVar9 = piVar1 + uVar12 * 0x100;
      piVar13 = param_2;
      do {
        iVar10 = *piVar6;
        piVar6 = piVar6 + 1;
        *piVar13 = ((iVar10 - *piVar9) * (&DAT_00d0feac)[iVar2 - 1U & (uint)param_1] >> 8) + *piVar9
        ;
        local_c = local_c + -1;
        piVar9 = piVar9 + 1;
        piVar13 = piVar13 + 1;
      } while (local_c != 0);
    }
    param_1 = (int *)((int)param_1 + 1);
    param_2 = param_2 + 0x100;
  } while ((int)param_1 < 0x100);
  return;
}



// ==== 0x41a740 ====

void FUN_0041a740(float param_1,char param_2,int param_3,uint param_4,uint param_5,uint param_6)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  
  iVar1 = (&DAT_00d102ac)[(int)param_1];
  DAT_00d102c0 = ((param_3 << 8 | param_4) << 8 | param_5) << 8 | param_6;
  bVar3 = ('\x02' - param_2) * '\b';
  FUN_0041a530(DAT_00d102c8,0x80,0x43000000);
  iVar4 = 0x40;
  param_1 = 64.0;
  do {
    FUN_0041a530(DAT_00d102cc,iVar4,param_1);
    FUN_0041a500(DAT_00d102c8,DAT_00d102cc);
    param_1 = param_1 * 0.5;
    iVar4 = iVar4 / 2;
  } while (0 < iVar4);
  iVar4 = 0;
  do {
    iVar2 = iVar4 + 4;
    *(uint *)(iVar4 + iVar1) =
         (*(uint *)(iVar4 + DAT_00d102c8) >> 0x10) << (bVar3 & 0x1f) |
         *(uint *)(iVar4 + iVar1) & 0xffffffU - (0xff << (bVar3 & 0x1f));
    iVar4 = iVar2;
  } while (iVar2 < 0x40000);
  return;
}



// ==== 0x41a830 ====

void FUN_0041a830(int param_1,char param_2,int param_3,undefined4 param_4,int param_5,uint param_6,
                 uint param_7,uint param_8)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 *_Memory;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  int local_c;
  
  _Memory = _malloc(0x40000);
  local_c = 0;
  puVar13 = _Memory;
  do {
    param_4 = 0;
    do {
      uVar5 = __ftol();
      *puVar13 = uVar5;
      param_4 = param_4 + 1;
      puVar13 = puVar13 + 1;
    } while (param_4 < 0x100);
    local_c = local_c + 1;
  } while (local_c < 0x100);
  DAT_00d102c0 = ((param_5 << 8 | param_6) << 8 | param_7) << 8 | param_8;
  iVar14 = 0;
  do {
    iVar6 = iVar14 + 4;
    *(undefined4 *)(iVar14 + DAT_00d102c8) = 0xff;
    iVar14 = iVar6;
  } while (iVar6 < 0x40000);
  iVar14 = 0;
  if (0 < param_3) {
    param_4 = param_3;
    do {
      iVar6 = iVar14 + 1;
      uVar7 = FUN_0041a100(iVar14);
      iVar14 = iVar14 + 2;
      uVar8 = FUN_0041a100(iVar6);
      iVar10 = 0;
      uVar12 = (uVar8 & 0xff) - 0x80;
      iVar6 = (uVar8 & 0xff) + 0x80;
      if ((int)uVar12 < iVar6) {
        uVar8 = (uVar7 & 0xff) - 0x80;
        iVar1 = (uVar7 & 0xff) + 0x80;
        do {
          if ((int)uVar8 < iVar1) {
            puVar11 = _Memory + iVar10;
            iVar10 = iVar10 + (iVar1 - uVar8);
            uVar7 = uVar8;
            do {
              uVar4 = *puVar11;
              puVar11 = puVar11 + 1;
              puVar3 = (uint *)(DAT_00d102c8 + ((uVar7 & 0xff) + (uVar12 & 0xff) * 0x100) * 4);
              if (uVar4 < *puVar3) {
                *puVar3 = uVar4;
              }
              uVar7 = uVar7 + 1;
            } while ((int)uVar7 < iVar1);
          }
          uVar12 = uVar12 + 1;
        } while ((int)uVar12 < iVar6);
      }
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  bVar9 = ('\x02' - param_2) * '\b';
  iVar14 = 0;
  do {
    *(uint *)((&DAT_00d102ac)[param_1] + iVar14) =
         *(uint *)((&DAT_00d102ac)[param_1] + iVar14) & 0xffffffU - (0xff << (bVar9 & 0x1f));
    piVar2 = (int *)(iVar14 + DAT_00d102c8);
    puVar11 = (uint *)((&DAT_00d102ac)[param_1] + iVar14);
    iVar14 = iVar14 + 4;
    *puVar11 = *puVar11 | *piVar2 << (bVar9 & 0x1f);
  } while (iVar14 < 0x40000);
  _free(_Memory);
  return;
}



// ==== 0x41aa30 ====

void FUN_0041aa30(int param_1,char param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 extraout_ST1;
  
  fVar7 = (float10)param_3;
  iVar1 = (&DAT_00d102ac)[param_1];
  bVar3 = param_2 * -8 + 0x10;
  fVar8 = (float10)param_4;
  iVar6 = 0;
  _param_2 = 0;
  do {
    iVar5 = 0;
    fsin((float10)(_param_2 + param_6) * fVar8 * (float10)0.02454369328916073);
    do {
      fsin((float10)(iVar5 + param_5) * fVar7 * (float10)0.02454369328916073);
      fVar7 = fVar8;
      iVar2 = __ftol();
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 1;
      *(int *)(DAT_00d102c8 + -4 + iVar6 * 4) = iVar2 << (bVar3 & 0x1f);
      fVar8 = extraout_ST1;
    } while (iVar5 < 0x100);
    _param_2 = _param_2 + 1;
  } while (_param_2 < 0x100);
  iVar6 = 0;
  do {
    iVar5 = iVar6 + 4;
    uVar4 = *(uint *)(iVar6 + iVar1) & 0xffffffU - (0xff << (bVar3 & 0x1f));
    *(uint *)(iVar6 + iVar1) = uVar4;
    *(uint *)(iVar6 + iVar1) = *(uint *)(iVar6 + DAT_00d102c8) | uVar4;
    iVar6 = iVar5;
  } while (iVar5 < 0x40000);
  return;
}



// ==== 0x41ab20 ====

void FUN_0041ab20(int param_1,int param_2,char param_3)

{
  uint uVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  uint *puStack00000010;
  
  puStack00000010 = (uint *)(&DAT_00d102ac)[param_1];
  bVar2 = ('\x02' - param_3) * '\b';
  param_1 = 0;
  do {
    iVar4 = 0;
    puVar3 = puStack00000010;
    puStack00000010 = puStack00000010 + 0x100;
    do {
      uVar1 = __ftol();
      if ((int)uVar1 < 0) {
        uVar1 = 0;
      }
      else if (0xff < (int)uVar1) {
        uVar1 = 0xff;
      }
      if (param_2 == 0) {
        *puVar3 = (uVar1 << 8 | uVar1) << 8 | uVar1;
      }
      else if (param_2 == 1) {
        *puVar3 = *puVar3 & 0xffffffU - (0xff << (bVar2 & 0x1f)) | uVar1 << (bVar2 & 0x1f);
      }
      puVar3 = puVar3 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x100);
    param_1 = param_1 + 1;
  } while (param_1 < 0x100);
  return;
}



// ==== 0x41ac40 ====

void FUN_0041ac40(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  undefined4 uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float local_41c;
  int local_418;
  float local_414;
  float local_400 [256];
  
  puVar6 = (undefined4 *)(&DAT_00d102ac)[param_1];
  iVar3 = 0;
  local_41c = 0.0;
  pfVar2 = local_400;
  do {
    fVar7 = (float10)(int)local_41c;
    local_41c = (float)((int)local_41c + 1);
    fVar7 = (float10)fcos((float10)param_3 * (fVar7 + (float10)param_7) *
                          (float10)0.02454369328916073);
    *pfVar2 = (float)((float10)param_5 * fVar7);
    pfVar2 = pfVar2 + 1;
  } while ((int)local_41c < 0x100);
  local_41c = 0.0;
  local_418 = 0;
  do {
    local_414 = 0.0;
    pfVar2 = local_400;
    iVar4 = 0x100;
    fVar7 = (float10)fsin(((float10)local_418 + (float10)param_6) * (float10)param_2 *
                          (float10)0.02454369328916073);
    do {
      uVar1 = FUN_00419950(puVar6,local_414 + (float)(fVar7 * (float10)param_4),local_41c + *pfVar2)
      ;
      local_414 = local_414 + 1.0;
      DAT_00d102c8[iVar3] = uVar1;
      iVar3 = iVar3 + 1;
      pfVar2 = pfVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    local_41c = local_41c + 1.0;
    local_418 = local_418 + 1;
  } while (local_418 < 0x100);
  puVar5 = DAT_00d102c8;
  for (iVar3 = 0x10000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  return;
}



// ==== 0x41ad80 ====

void FUN_0041ad80(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  float10 fVar9;
  float local_8;
  
  puVar7 = (undefined4 *)(&DAT_00d102ac)[param_1];
  local_8 = -1.0;
  fVar2 = ((float)param_2 - 127.5) * 0.03125;
  if (fVar2 <= 0.0) {
    local_8 = 1.0;
  }
  iVar5 = 0;
  param_2 = 0;
  do {
    param_1 = 0;
    fVar3 = (float)param_2 - 127.5;
    do {
      fVar8 = (float10)param_1 - (float10)127.5;
      fVar1 = (float)SQRT(fVar8 * fVar8 + (float10)(fVar3 * fVar3));
      fVar8 = (float10)fpatan(fVar8,(float10)fVar3);
      if ((float10)0.0 <= (float10)128.0 - (float10)fVar1) {
        fVar9 = (float10)fcos(((float10)128.0 - (float10)fVar1) * (float10)fVar2 *
                              (float10)0.012271847);
        fVar9 = fVar9 * (float10)128.0 + (float10)128.0;
      }
      else {
        fVar9 = (float10)0.0;
      }
      fVar8 = (fVar9 * (float10)local_8 + fVar8 * (float10)40.74366429772945) *
              (float10)0.02454369328916073;
      fVar9 = (float10)fcos(fVar8);
      fVar8 = (float10)fsin(fVar8);
      uVar4 = FUN_00419950(puVar7,(float)(fVar8 * (float10)fVar1 + (float10)128.0),
                           (float)(fVar9 * (float10)fVar1 + (float10)128.0));
      DAT_00d102c8[iVar5] = uVar4;
      iVar5 = iVar5 + 1;
      param_1 = param_1 + 1;
    } while (param_1 < 0x100);
    param_2 = param_2 + 1;
  } while (param_2 < 0x100);
  puVar6 = DAT_00d102c8;
  for (iVar5 = 0x10000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  return;
}



// ==== 0x41aec0 ====

void FUN_0041aec0(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)(&DAT_00d102ac)[param_1];
  param_1 = 0;
  do {
    iVar2 = 0;
    iVar3 = param_1 << 10;
    do {
      uVar1 = iVar2 + param_2;
      iVar2 = iVar2 + 1;
      *(undefined4 *)(iVar3 + (int)DAT_00d102c8) =
           puVar5[(uVar1 & 0xff) + (param_3 + param_1 & 0xffU) * 0x100];
      iVar3 = iVar3 + 4;
    } while (iVar2 < 0x100);
    param_1 = param_1 + 1;
  } while (param_1 < 0x100);
  puVar4 = DAT_00d102c8;
  for (iVar3 = 0x10000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}



// ==== 0x41af40 ====

void FUN_0041af40(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  puVar7 = (undefined4 *)(&DAT_00d102ac)[param_1];
  iVar5 = 0;
  do {
    uVar2 = puVar7[param_2 * 0x101 + iVar5 & 0xffff];
    uVar1 = puVar7[iVar5];
    iVar3 = (uVar2 >> 0x10 & 0xff) - (uVar1 >> 0x10 & 0xff);
    uVar4 = (uVar2 >> 8 & 0xff) - (uVar1 >> 8 & 0xff);
    uVar2 = (uVar2 & 0xff) - (uVar1 & 0xff);
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    if ((int)uVar4 < 0) {
      uVar4 = 0;
    }
    if ((int)uVar2 < 0) {
      uVar2 = 0;
    }
    DAT_00d102c8[iVar5] = (iVar3 << 8 | uVar4) << 8 | uVar2;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x10000);
  puVar6 = DAT_00d102c8;
  for (iVar5 = 0x10000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  return;
}



// ==== 0x41aff0 ====

void FUN_0041aff0(int param_1,int param_2,char param_3,int param_4,int param_5,char param_6,
                 int param_7)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  puVar7 = (undefined4 *)(&DAT_00d102ac)[param_1];
  iVar3 = (&DAT_00d102ac)[param_2];
  iVar1 = (&DAT_00d102ac)[param_5];
  iVar4 = 0;
  param_1 = 0;
  do {
    param_2 = 0;
    puVar5 = (uint *)(iVar1 + iVar4 * 4);
    do {
      uVar2 = FUN_00419950(puVar7,(float)(*(uint *)((iVar3 - iVar1) + (int)puVar5) >>
                                          (param_3 * -8 + 0x10U & 0x1f) & 0xff) *
                                  (float)param_4 * 0.00390625 + (float)param_2,
                           (float)(*puVar5 >> (param_6 * -8 + 0x10U & 0x1f) & 0xff) *
                           (float)param_7 * 0.00390625 + (float)param_1);
      puVar5 = puVar5 + 1;
      DAT_00d102c8[iVar4] = uVar2;
      iVar4 = iVar4 + 1;
      param_2 = param_2 + 1;
    } while (param_2 < 0x100);
    param_1 = param_1 + 1;
  } while (param_1 < 0x100);
  puVar6 = DAT_00d102c8;
  for (iVar3 = 0x10000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  return;
}



// ==== 0x41b150 ====

void FUN_0041b150(int param_1,char param_2,int param_3,char param_4)

{
  uint *puVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  
  iVar6 = (&DAT_00d102ac)[param_1];
  bVar2 = param_2 * -8 + 0x10;
  bVar3 = param_4 * -8 + 0x10;
  iVar5 = 0;
  do {
    iVar4 = iVar5 + 4;
    *(uint *)(iVar5 + DAT_00d102c8) =
         (*(uint *)((&DAT_00d102ac)[param_3] + -4 + iVar4) >> (bVar3 & 0x1f) & 0xff) <<
         (bVar2 & 0x1f);
    iVar5 = iVar4;
  } while (iVar4 < 0x40000);
  iVar5 = 0;
  do {
    iVar4 = iVar5 + 4;
    *(uint *)(iVar5 + DAT_00d102cc) =
         (*(uint *)(iVar5 + iVar6) >> (bVar2 & 0x1f) & 0xff) << (bVar3 & 0x1f);
    iVar5 = iVar4;
  } while (iVar4 < 0x40000);
  iVar5 = 0;
  do {
    iVar4 = iVar5 + 4;
    uVar7 = *(uint *)(iVar5 + iVar6) & 0xffffffU - (0xff << (bVar2 & 0x1f));
    *(uint *)(iVar5 + iVar6) = uVar7;
    *(uint *)(iVar5 + iVar6) = *(uint *)(iVar5 + DAT_00d102c8) | uVar7;
    iVar5 = iVar4;
  } while (iVar4 < 0x40000);
  iVar6 = 0;
  do {
    *(uint *)((&DAT_00d102ac)[param_3] + iVar6) =
         *(uint *)((&DAT_00d102ac)[param_3] + iVar6) & 0xffffffU - (0xff << (bVar3 & 0x1f));
    puVar8 = (uint *)((&DAT_00d102ac)[param_3] + iVar6);
    puVar1 = (uint *)(iVar6 + DAT_00d102cc);
    iVar6 = iVar6 + 4;
    *puVar8 = *puVar8 | *puVar1;
  } while (iVar6 < 0x40000);
  return;
}



// ==== 0x41b270 ====

void FUN_0041b270(int param_1,char param_2)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  iVar3 = 0x10000;
  puVar2 = (uint *)(&DAT_00d102ac)[param_1];
  do {
    uVar1 = *puVar2 >> (param_2 * -8 + 0x10U & 0x1f) & 0xff;
    iVar3 = iVar3 + -1;
    *puVar2 = (uVar1 << 8 | uVar1) << 8 | uVar1;
    puVar2 = puVar2 + 1;
  } while (iVar3 != 0);
  return;
}



// ==== 0x41b2c0 ====

void FUN_0041b2c0(int param_1,int param_2,char param_3)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  puVar1 = (uint *)(&DAT_00d102ac)[param_1];
  iVar2 = (&DAT_00d102ac)[param_2];
  param_1 = 0x10000;
  puVar5 = puVar1;
  do {
    uVar3 = *puVar5;
    iVar4 = (*(uint *)((iVar2 - (int)puVar1) + (int)puVar5) >> (param_3 * -8 + 0x10U & 0x1f) & 0xff)
            * 0x100;
    *puVar5 = (uint)CONCAT21(CONCAT11(*(undefined1 *)((uVar3 >> 0x10 & 0xff) + iVar4 + DAT_00d102c4)
                                      ,*(undefined1 *)((uVar3 >> 8 & 0xff) + iVar4 + DAT_00d102c4)),
                             *(undefined1 *)((uVar3 & 0xff) + iVar4 + DAT_00d102c4));
    param_1 = param_1 + -1;
    puVar5 = puVar5 + 1;
  } while (param_1 != 0);
  return;
}



// ==== 0x41b360 ====

void FUN_0041b360(int param_1,char param_2,uint param_3,char param_4)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar1 = (&DAT_00d102ac)[param_1];
  bVar2 = param_2 * -8 + 0x10;
  iVar4 = 0;
  do {
    iVar3 = iVar4 + 4;
    *(uint *)(iVar4 + DAT_00d102c8) =
         (*(uint *)(iVar4 + (&DAT_00d102ac)[param_3 & 0xff]) >> (param_4 * -8 + 0x10U & 0x1f) & 0xff
         ) << (bVar2 & 0x1f);
    iVar4 = iVar3;
  } while (iVar3 < 0x40000);
  iVar4 = 0;
  do {
    iVar3 = iVar4 + 4;
    uVar5 = *(uint *)(iVar4 + iVar1) & 0xffffffU - (0xff << (bVar2 & 0x1f));
    *(uint *)(iVar4 + iVar1) = uVar5;
    *(uint *)(iVar4 + iVar1) = *(uint *)(iVar4 + DAT_00d102c8) | uVar5;
    iVar4 = iVar3;
  } while (iVar3 < 0x40000);
  return;
}



// ==== 0x41b420 ====

void FUN_0041b420(int param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  
  pbVar2 = (byte *)(&DAT_00d102ac)[param_1];
  pbVar6 = (byte *)(&DAT_00d102ac)[param_2];
  iVar7 = (param_3 & 0xfffffffe) * 0x80 + DAT_00d102c4;
  iVar4 = DAT_00d102c4 + (param_3 & 0xfffffffe) * -0x80 + 0x7f00;
  param_1 = 0x10000;
  pbVar3 = pbVar2;
  do {
    *pbVar3 = *(char *)((uint)*pbVar6 + iVar4) + *(char *)((uint)*pbVar2 + iVar7);
    pbVar1 = pbVar2 + 2;
    pbVar5 = pbVar6 + 2;
    pbVar3[1] = *(char *)((uint)pbVar6[1] + iVar4) + *(char *)((uint)pbVar2[1] + iVar7);
    pbVar2 = pbVar2 + 4;
    pbVar6 = pbVar6 + 4;
    pbVar3[2] = *(char *)((uint)*pbVar5 + iVar4) + *(char *)((uint)*pbVar1 + iVar7);
    param_1 = param_1 + -1;
    pbVar3 = pbVar3 + 4;
  } while (param_1 != 0);
  return;
}



// ==== 0x41b4c0 ====

void FUN_0041b4c0(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar1 = (uint *)(&DAT_00d102ac)[param_1];
  iVar2 = (&DAT_00d102ac)[param_2];
  param_1 = 0x10000;
  puVar5 = puVar1;
  do {
    uVar3 = *puVar5;
    uVar4 = *(uint *)((iVar2 - (int)puVar1) + (int)puVar5);
    *puVar5 = ((int)((uVar4 >> 8 & 0xff) * (uVar3 >> 8 & 0xff)) >> 8 |
              (((int)uVar4 >> 0x10) * ((int)uVar3 >> 0x10) >> 8) << 8) << 8 |
              (int)((uVar4 & 0xff) * (uVar3 & 0xff)) >> 8;
    param_1 = param_1 + -1;
    puVar5 = puVar5 + 1;
  } while (param_1 != 0);
  return;
}



// ==== 0x41b540 ====

void FUN_0041b540(int param_1)

{
  int iVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(&DAT_00d102ac)[param_1];
  iVar1 = 0x10000;
  do {
    *pbVar2 = *pbVar2 ^ 0xff;
    pbVar2 = pbVar2 + 4;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



// ==== 0x41b570 ====

void FUN_0041b570(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iStack00000008;
  
  puVar5 = (uint *)(&DAT_00d102ac)[param_1];
  param_1 = 0x10000;
  do {
    uVar1 = *puVar5;
    iStack00000008 = (uVar1 >> 0x10 & 0xff) - 0x80;
    iVar2 = __ftol();
    iStack00000008 = (uVar1 >> 8 & 0xff) - 0x80;
    iVar3 = __ftol();
    iStack00000008 = (uVar1 & 0xff) - 0x80;
    iVar4 = __ftol();
    if (0x7f < iVar2) {
      iVar2 = 0x7f;
    }
    if (0x7f < iVar3) {
      iVar3 = 0x7f;
    }
    if (0x7f < iVar4) {
      iVar4 = 0x7f;
    }
    if (iVar2 < -0x7f) {
      iVar2 = -0x7f;
    }
    if (iVar3 < -0x7f) {
      iVar3 = -0x7f;
    }
    if (iVar4 < -0x7f) {
      iVar4 = -0x7f;
    }
    *puVar5 = (iVar3 + 0x80) * 0x100 | (iVar2 + 0x80) * 0x10000 | iVar4 + 0x80U;
    puVar5 = puVar5 + 1;
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return;
}



// ==== 0x41b670 ====

void FUN_0041b670(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  
  iVar2 = 0x10000;
  param_2 = param_2 * 0x100;
  puVar3 = (uint *)(&DAT_00d102ac)[param_1];
  do {
    uVar1 = *puVar3;
    iVar2 = iVar2 + -1;
    *puVar3 = (uint)CONCAT21(CONCAT11(*(undefined1 *)
                                       ((uVar1 >> 0x10 & 0xff) + DAT_00d102c4 + param_2),
                                      *(undefined1 *)((uVar1 >> 8 & 0xff) + DAT_00d102c4 + param_2))
                             ,*(undefined1 *)((uVar1 & 0xff) + DAT_00d102c4 + param_2));
    puVar3 = puVar3 + 1;
  } while (iVar2 != 0);
  return;
}



// ==== 0x41b6d0 ====

void FUN_0041b6d0(int param_1,char param_2,int param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  uint *puVar5;
  float10 fVar6;
  float10 extraout_ST0;
  
  bVar4 = param_2 * -8 + 0x10;
  puVar1 = &DAT_00d102ac + param_1;
  param_1 = 0x10000;
  fVar6 = (float10)param_3 * (float10)6.2831854820251465 * (float10)0.00390625;
  puVar5 = (uint *)*puVar1;
  do {
    uVar2 = *puVar5;
    fcos((float10)(uVar2 >> (bVar4 & 0x1f) & 0xff) * fVar6);
    iVar3 = __ftol();
    *puVar5 = uVar2 & 0xffffffU - (0xff << (bVar4 & 0x1f)) | iVar3 << (bVar4 & 0x1f);
    param_1 = param_1 + -1;
    puVar5 = puVar5 + 1;
    fVar6 = extraout_ST0;
  } while (param_1 != 0);
  return;
}



// ==== 0x41b770 ====

void FUN_0041b770(int param_1,char param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  uint *puVar4;
  int iStack0000000c;
  
  bVar3 = param_2 * -8 + 0x10;
  iStack0000000c = 0x10000;
  puVar4 = (uint *)(&DAT_00d102ac)[param_1];
  do {
    uVar1 = *puVar4;
    iVar2 = __ftol();
    *puVar4 = iVar2 << (bVar3 & 0x1f) | uVar1 & 0xffffffU - (0xff << (bVar3 & 0x1f));
    iStack0000000c = iStack0000000c + -1;
    puVar4 = puVar4 + 1;
  } while (iStack0000000c != 0);
  return;
}



// ==== 0x41b820 ====

void FUN_0041b820(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = (&DAT_00d102ac)[param_1];
  iVar3 = 0;
  iVar7 = 0;
  do {
    puVar2 = (undefined4 *)(iVar1 + iVar3 * 4);
    iVar6 = 8;
    bVar4 = *(byte *)(iVar7 + param_2);
    do {
      uVar5 = param_3;
      if ((bVar4 & 1) != 0) {
        uVar5 = param_4;
      }
      *puVar2 = uVar5;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
      bVar4 = bVar4 >> 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x2000);
  return;
}



// ==== 0x41b870 ====

void FUN_0041b870(int param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  int local_2c;
  int local_20;
  uint local_10;
  int local_c;
  
  puVar1 = (uint *)(&DAT_00d102ac)[param_1];
  if (0 < param_2) {
    local_c = param_2;
    do {
      local_20 = 0;
      local_10 = 1;
      local_2c = 0;
      puVar12 = puVar1;
      do {
        puVar9 = puVar1 + (local_10 - 2 & 0xff) * 0x100;
        puVar8 = puVar1 + (local_10 & 0xff) * 0x100;
        uVar11 = 1;
        do {
          uVar2 = *puVar9;
          uVar3 = *puVar8;
          uVar4 = puVar1[(uVar11 - 2 & 0xff) + local_2c];
          uVar5 = puVar1[(uVar11 & 0xff) + local_2c];
          uVar6 = *puVar12;
          DAT_00d102c8[local_20] =
               (((int)((uVar5 >> 0x10 & 0xff) + (uVar6 >> 0x10 & 0xff) * 4 + (uVar2 >> 0x10 & 0xff)
                       + (uVar4 >> 0x10 & 0xff) + (uVar3 >> 0x10 & 0xff)) >> 3) << 8 |
               (int)((uVar5 >> 8 & 0xff) + (uVar6 >> 8 & 0xff) * 4 + (uVar2 >> 8 & 0xff) +
                     (uVar4 >> 8 & 0xff) + (uVar3 >> 8 & 0xff)) >> 3) << 8 |
               (int)((uVar5 & 0xff) + (uVar6 & 0xff) * 4 + (uVar2 & 0xff) + (uVar4 & 0xff) +
                    (uVar3 & 0xff)) >> 3;
          local_20 = local_20 + 1;
          puVar9 = puVar9 + 1;
          puVar8 = puVar8 + 1;
          puVar12 = puVar12 + 1;
          bVar7 = (int)uVar11 < 0x100;
          uVar11 = uVar11 + 1;
        } while (bVar7);
        local_2c = local_2c + 0x100;
        bVar7 = (int)local_10 < 0x100;
        local_10 = local_10 + 1;
      } while (bVar7);
      local_c = local_c + -1;
      puVar12 = DAT_00d102c8;
      puVar8 = puVar1;
      for (iVar10 = 0x10000; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar8 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar8 = puVar8 + 1;
      }
    } while (local_c != 0);
  }
  return;
}



// ==== 0x41ba40 ====

void FUN_0041ba40(int param_1,int param_2,char param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float10 fVar7;
  int local_18;
  int local_14;
  
  iVar3 = (&DAT_00d102ac)[param_2];
  puVar6 = (undefined4 *)(&DAT_00d102ac)[param_1];
  local_14 = 0;
  local_18 = 0;
  do {
    param_2 = 0;
    do {
      fVar7 = (float10)(*(uint *)(iVar3 + local_14 * 4) >> (('\x02' - param_3) * '\b' & 0x1fU) &
                       0xff) * (float10)0.02454369328916073;
      fsin(fVar7);
      fcos(fVar7);
      iVar4 = param_4;
      if (0 < param_4) {
        do {
          __ftol();
          __ftol();
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      iVar4 = __ftol();
      uVar1 = __ftol();
      uVar2 = __ftol();
      DAT_00d102c8[local_14] = (iVar4 << 8 | uVar1) << 8 | uVar2;
      local_14 = local_14 + 1;
      param_2 = param_2 + 1;
    } while (param_2 < 0x100);
    local_18 = local_18 + 1;
  } while (local_18 < 0x100);
  puVar5 = DAT_00d102c8;
  for (iVar3 = 0x10000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  FUN_0041b870(param_1,2);
  return;
}



// ==== 0x41bbf0 ====

void FUN_0041bbf0(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  
  puVar1 = (uint *)(&DAT_00d102ac)[param_1];
  iVar2 = (&DAT_00d102ac)[param_2];
  param_1 = 0x10000;
  puVar7 = puVar1;
  do {
    uVar4 = *puVar7;
    uVar3 = *(uint *)((int)puVar7 + (iVar2 - (int)puVar1));
    iVar6 = ((int)uVar3 >> 0x10) + ((int)uVar4 >> 0x10);
    uVar5 = (uVar3 >> 8 & 0xff) + (uVar4 >> 8 & 0xff);
    uVar4 = (uVar3 & 0xff) + (uVar4 & 0xff);
    if (0xff < iVar6) {
      iVar6 = 0xff;
    }
    if (0xff < uVar5) {
      uVar5 = 0xff;
    }
    if (0xff < uVar4) {
      uVar4 = 0xff;
    }
    *puVar7 = (iVar6 << 8 | uVar5) << 8 | uVar4;
    param_1 = param_1 + -1;
    puVar7 = puVar7 + 1;
  } while (param_1 != 0);
  return;
}



// ==== 0x41bc90 ====

void FUN_0041bc90(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  
  puVar8 = (uint *)(&DAT_00d102ac)[param_1];
  iVar4 = (&DAT_00d102ac)[param_2] - (int)puVar8;
  param_1 = 0x10000;
  do {
    uVar1 = *puVar8;
    uVar2 = *(uint *)(iVar4 + (int)puVar8);
    uVar5 = uVar1 >> 0x10 & 0xff;
    uVar6 = uVar1 >> 8 & 0xff;
    uVar7 = uVar2 >> 0x10 & 0xff;
    uVar3 = uVar2 >> 8 & 0xff;
    if (uVar7 < uVar5) {
      uVar7 = uVar5;
    }
    if (uVar3 < uVar6) {
      uVar3 = uVar6;
    }
    uVar5 = uVar2 & 0xff;
    if ((uVar2 & 0xff) < (uVar1 & 0xff)) {
      uVar5 = uVar1 & 0xff;
    }
    *puVar8 = (uVar7 << 8 | uVar3) << 8 | uVar5;
    puVar8 = puVar8 + 1;
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return;
}



// ==== 0x41bd30 ====

uint FUN_0041bd30(float param_1,float param_2,float param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar5;
  undefined8 uVar6;
  
  if (param_2 != 0.0) {
    for (; 360.0 <= param_1; param_1 = param_1 - 360.0) {
    }
    for (; param_1 < 0.0; param_1 = param_1 + 360.0) {
    }
    fVar5 = (float10)FUN_0041ec50((double)(param_1 * 0.016666668));
    uVar1 = __ftol((1.0 - param_2) * param_3,
                   (float)(((float10)1.0 -
                           ((float10)(param_1 * 0.016666668) - fVar5) * (float10)param_2) *
                          (float10)param_3));
    switch(uVar1) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
    }
  }
  uVar6 = CONCAT44(unaff_ESI,unaff_EDI);
  iVar2 = __ftol();
  uVar3 = __ftol(uVar6);
  uVar4 = __ftol();
  if (0xff < iVar2) {
    iVar2 = 0xff;
  }
  if (0xff < (int)uVar3) {
    uVar3 = 0xff;
  }
  if (0xff < (int)uVar4) {
    uVar4 = 0xff;
  }
  return (iVar2 << 8 | uVar3) << 8 | uVar4;
}



// ==== 0x41bf10 ====

void FUN_0041bf10(float param_1,float param_2,float param_3,float *param_4,float *param_5,
                 float *param_6)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_2;
  if (param_2 < param_1) {
    fVar1 = param_1;
  }
  if (fVar1 < param_3) {
    fVar1 = param_3;
  }
  fVar2 = param_2;
  if (param_1 < param_2) {
    fVar2 = param_1;
  }
  if (param_3 < fVar2) {
    fVar2 = param_3;
  }
  *param_6 = fVar1;
  *param_5 = 0.0;
  if (fVar1 != 0.0) {
    *param_5 = (fVar1 - fVar2) / fVar1;
  }
  if (*param_5 == 0.0) {
    *param_4 = -1.0;
    return;
  }
  fVar2 = fVar1 - fVar2;
  if (param_1 == fVar1) {
    fVar2 = ((fVar1 - param_3) - (fVar1 - param_2)) / fVar2;
  }
  else if (param_2 == fVar1) {
    fVar2 = ((fVar1 - param_1) - (fVar1 - param_3)) / fVar2 + 2.0;
  }
  else {
    if (param_3 != fVar1) goto LAB_0041c044;
    fVar2 = ((fVar1 - param_2) - (fVar1 - param_1)) / fVar2 + 4.0;
  }
  *param_4 = fVar2;
LAB_0041c044:
  fVar1 = *param_4 * 60.0;
  *param_4 = fVar1;
  while (fVar1 < 0.0) {
    fVar1 = *param_4 + 360.0;
    *param_4 = fVar1;
  }
  fVar1 = *param_4;
  while (360.0 <= fVar1) {
    fVar1 = *param_4 - 360.0;
    *param_4 = fVar1;
  }
  return;
}



// ==== 0x41c0a0 ====

void FUN_0041c0a0(float param_1,float param_2,uint param_3)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  undefined4 local_4;
  
  fVar1 = (float)(int)param_2;
  puVar4 = (uint *)(&DAT_00d102ac)[(int)param_1];
  param_1 = (float)(0xff - param_3);
  iVar5 = 0x10000;
  fVar2 = (float)(int)param_1;
  do {
    uVar3 = *puVar4;
    param_3 = uVar3 >> 0x10 & 0xff;
    FUN_0041bf10((float)param_3,(float)(uVar3 >> 8 & 0xff),(float)(uVar3 & 0xff),&param_2,&param_1,
                 &local_4);
    param_2 = param_2 + fVar1 * 1.40625;
    param_1 = param_1 * fVar2 * 0.003921569;
    uVar3 = FUN_0041bd30(param_2,param_1,local_4);
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}



// ==== 0x41c180 ====

void FUN_0041c180(int param_1,char param_2)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  uint local_400 [256];
  
  iVar6 = 0;
  puVar5 = local_400;
  do {
    iVar2 = __ftol();
    uVar3 = __ftol();
    uVar4 = __ftol();
    iVar6 = iVar6 + 1;
    *puVar5 = (iVar2 << 8 | uVar3) << 8 | uVar4;
    puVar5 = puVar5 + 1;
  } while (iVar6 < 0x100);
  iVar6 = 0;
  do {
    puVar5 = (uint *)((&DAT_00d102ac)[param_1] + iVar6);
    puVar1 = (uint *)((&DAT_00d102ac)[param_1] + iVar6);
    iVar6 = iVar6 + 4;
    *puVar1 = local_400[*puVar5 >> (('\x02' - param_2) * '\b' & 0x1fU) & 0xff];
  } while (iVar6 < 0x40000);
  return;
}



// ==== 0x41c2a0 ====

void FUN_0041c2a0(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iStack0000000c;
  
  puVar4 = (uint *)(&DAT_00d102ac)[param_1];
  iStack0000000c = 0x10000;
  do {
    iVar1 = __ftol();
    uVar2 = __ftol();
    uVar3 = __ftol();
    *puVar4 = (iVar1 << 8 | uVar2) << 8 | uVar3;
    puVar4 = puVar4 + 1;
    iStack0000000c = iStack0000000c + -1;
  } while (iStack0000000c != 0);
  return;
}



// ==== 0x41c3d0 ====

void FUN_0041c3d0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  char local_20 [4];
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  local_20[0] = -1;
  local_20[1] = 0;
  local_20[2] = 1;
  local_18 = 0;
  local_8 = 0;
  do {
    local_1c = 0;
    local_c = 1;
    do {
      iVar2 = 0;
      local_14 = 0;
      iVar3 = 0;
      local_10 = 0;
      local_4 = (&DAT_00d102ac)[param_1];
      do {
        uVar1 = local_1c - 1;
        do {
          iVar4 = (int)local_20[uVar1 + local_c];
          uVar5 = *(uint *)((&DAT_00d102ac)[param_1] +
                           ((uVar1 & 0xff) + (local_18 + -1 + local_10 & 0xffU) * 0x100) * 4);
          iVar3 = iVar3 + (uVar5 >> 0x10) * iVar4;
          iVar2 = iVar2 + (uVar5 >> 8 & 0xff) * iVar4;
          local_14 = local_14 + (uVar5 & 0xff) * iVar4;
          uVar1 = uVar1 + 1;
        } while ((int)(local_c + uVar1) < 3);
        local_10 = local_10 + 1;
      } while (local_10 < 3);
      iVar3 = iVar3 + 0x80;
      uVar1 = iVar2 + 0x80;
      uVar5 = local_14 + 0x80;
      if (0xff < iVar3) {
        iVar3 = 0xff;
      }
      if (0xff < (int)uVar1) {
        uVar1 = 0xff;
      }
      if (0xff < (int)uVar5) {
        uVar5 = 0xff;
      }
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      if ((int)uVar1 < 0) {
        uVar1 = 0;
      }
      if ((int)uVar5 < 0) {
        uVar5 = 0;
      }
      iVar2 = local_8 + local_1c;
      local_c = local_c + -1;
      local_1c = local_1c + 1;
      DAT_00d102c8[iVar2] = (iVar3 << 8 | uVar1) << 8 | uVar5;
    } while (-0xff < local_c);
    local_8 = local_8 + 0x100;
    local_18 = local_18 + 1;
  } while (local_8 < 0x10000);
  puVar6 = DAT_00d102c8;
  puVar7 = (undefined4 *)(&DAT_00d102ac)[param_1];
  for (iVar2 = 0x10000; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  return;
}



