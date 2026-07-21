#include "../include/global.h"

// The vanilla FireRed diploma (shown by special 0x108) chooses its region name by
// calling HasAllMons() at 0x080F502A: if the National dex is complete it prints the
// "National" string, otherwise the "Kanto" string. We replace that decision so the
// region name follows the divergent-mode flag instead:
//
//   FLAG_DIVERGENT_WILD_ENCOUNTERS (0x945) set   -> "Kulure (Divergent)"
//   flag clear                                   -> "Kulure (Standard)"
//
// Hooked in place of "bl HasAllMons" (see hooks file). Placeholder slot 0 (the player
// name) has already been set by the caller; we only set slot 1 (the region), then jump
// back to 0x080F5050, where the two original branches rejoined.

extern const u8 gText_DiplomaRegion_KulureDivergent[];
extern const u8 gText_DiplomaRegion_KulureStandard[];

void __attribute__((naked)) DiplomaChooseRegionNameByMode(void)
{
    asm_unified(
        "ldr r0, =0x945\n"                  // FLAG_DIVERGENT_WILD_ENCOUNTERS
        "ldr r3, =(0x0806E6D0 + 1)\n"       // FlagGet
        "bl .LcallR3\n"
        "cmp r0, #0\n"
        "beq .Lstandard\n"
        "ldr r1, =gText_DiplomaRegion_KulureDivergent\n"
        "b .LsetPtr\n"
        ".Lstandard:\n"
        "ldr r1, =gText_DiplomaRegion_KulureStandard\n"
        ".LsetPtr:\n"
        "movs r0, #1\n"                     // placeholder slot 1 (the [F7][01] region)
        "ldr r3, =(0x0813CCAC + 1)\n"       // DynamicPlaceholderTextUtil_SetPlaceholderPtr
        "bl .LcallR3\n"
        "ldr r0, =(0x080F5050 + 1)\n"       // rejoin the vanilla diploma routine
        "bx r0\n"
        ".LcallR3:\n"
        "bx r3\n"
        ".pool\n"
    );
}

// The diploma background is a single double-width tilemap holding both layouts side by
// side; the vanilla code picks between them with BG1's horizontal scroll, gated on
// HasAllMons() (National dex complete -> hofs 0x100 = National half, else hofs 0 = Kanto
// half). We replace that call at 0x080F4CDC so the background follows the mode flag:
//
//   FLAG_DIVERGENT_WILD_ENCOUNTERS (0x945) set   -> Kanto half    (BG1HOFS = 0)
//   flag clear                                   -> National half (BG1HOFS = 0x100)
//
// We set the scroll ourselves and jump back to 0x080F4D50, where both branches rejoined.
void __attribute__((naked)) DiplomaSetBackgroundByMode(void)
{
    asm_unified(
        "ldr r0, =0x945\n"                  // FLAG_DIVERGENT_WILD_ENCOUNTERS
        "ldr r3, =(0x0806E6D0 + 1)\n"       // FlagGet
        "bl .LcallR3b\n"
        "movs r1, #0\n"                     // divergent (flag set) -> Kanto half, hofs 0
        "cmp r0, #0\n"
        "bne .LsetBg\n"
        "ldr r1, =0x100\n"                  // standard (flag clear) -> National half, hofs 0x100
        ".LsetBg:\n"
        "movs r0, #0x14\n"                  // REG_OFFSET_BG1HOFS
        "ldr r3, =(0x08000A38 + 1)\n"       // SetGpuReg
        "bl .LcallR3b\n"
        "ldr r0, =(0x080F4D50 + 1)\n"       // rejoin the vanilla diploma routine
        "bx r0\n"
        ".LcallR3b:\n"
        "bx r3\n"
        ".pool\n"
    );
}
