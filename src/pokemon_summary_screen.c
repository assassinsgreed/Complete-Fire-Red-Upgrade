#include "defines.h"
#include "../include/menu.h"
#include "../include/pokemon_summary_screen.h"
#include "../include/string_util.h"

// From pokeemerald wiki

static const s8 sNatureStatTable[NUM_NATURES][NUM_NATURE_STATS] =
{                      // Attack  Defense  Speed  Sp.Atk  Sp.Def
    [NATURE_HARDY]   = {    0,      0,      0,      0,      0   },
    [NATURE_LONELY]  = {   +1,     -1,      0,      0,      0   },
    [NATURE_BRAVE]   = {   +1,      0,     -1,      0,      0   },
    [NATURE_ADAMANT] = {   +1,      0,      0,     -1,      0   },
    [NATURE_NAUGHTY] = {   +1,      0,      0,      0,     -1   },
    [NATURE_BOLD]    = {   -1,     +1,      0,      0,      0   },
    [NATURE_DOCILE]  = {    0,      0,      0,      0,      0   },
    [NATURE_RELAXED] = {    0,     +1,     -1,      0,      0   },
    [NATURE_IMPISH]  = {    0,     +1,      0,     -1,      0   },
    [NATURE_LAX]     = {    0,     +1,      0,      0,     -1   },
    [NATURE_TIMID]   = {   -1,      0,     +1,      0,      0   },
    [NATURE_HASTY]   = {    0,     -1,     +1,      0,      0   },
    [NATURE_SERIOUS] = {    0,      0,      0,      0,      0   },
    [NATURE_JOLLY]   = {    0,      0,     +1,     -1,      0   },
    [NATURE_NAIVE]   = {    0,      0,     +1,      0,     -1   },
    [NATURE_MODEST]  = {   -1,      0,      0,     +1,      0   },
    [NATURE_MILD]    = {    0,     -1,      0,     +1,      0   },
    [NATURE_QUIET]   = {    0,      0,     -1,     +1,      0   },
    [NATURE_BASHFUL] = {    0,      0,      0,      0,      0   },
    [NATURE_RASH]    = {    0,      0,      0,     +1,     -1   },
    [NATURE_CALM]    = {   -1,      0,      0,      0,     +1   },
    [NATURE_GENTLE]  = {    0,     -1,      0,      0,     +1   },
    [NATURE_SASSY]   = {    0,      0,     -1,      0,     +1   },
    [NATURE_CAREFUL] = {    0,      0,      0,     -1,     +1   },
    [NATURE_QUIRKY]  = {    0,      0,      0,      0,      0   },
};

static const u8 sNatureTextColors[][3] =
{
    {0, 14, 10}, // Dark Grey - Neutral
    {0, 1, 10}, // Red - Up
    {0, 7, 10}, // Blue - Down
};

static u8 GetStatColor(s8 natureMod)
{
    if (natureMod == 0)
        return 0;
    else if (natureMod > 0)
        return 1;
    else
        return 2;
}

static const u8 sIVTextColors[][3] =
{
    {0, 1, 10}, // Red - F
    {0, 2, 10}, // Orange - E/E+
    {0, 3, 10}, // Orangish Yellow - D/D+ 
    {0, 4, 10}, // Yellow - C/C+
    {0, 5, 10}, // Green - B/B+
    {0, 7, 10}, // Blue - A/A+
    {0, 6, 10}, // Teal - S/S+
};

static u8 GetIVColor(s32 ivNum)
{
    if (ivNum <= 1) return 0;
    if (ivNum <= 4) return 1;
    if (ivNum <= 6) return 1;
    if (ivNum <= 8) return 2;
    if (ivNum <= 11) return 2;
    if (ivNum <= 14) return 3;
    if (ivNum <= 17) return 3;
    if (ivNum <= 20) return 4;
    if (ivNum <= 23) return 4;
    if (ivNum <= 26) return 5;
    if (ivNum <= 29) return 5;
    if (ivNum == 30) return 6;
    return 6;
}

static u8 * GetIVAssessment(s32 ivNum)
{
    if (ivNum <= 1) return gText_IVRating_F;
    if (ivNum <= 4) return gText_IVRating_E;
    if (ivNum <= 6) return gText_IVRating_EPlus;
    if (ivNum <= 8) return gText_IVRating_D;
    if (ivNum <= 11) return gText_IVRating_DPlus;
    if (ivNum <= 14) return gText_IVRating_C;
    if (ivNum <= 17) return gText_IVRating_CPlus;
    if (ivNum <= 20) return gText_IVRating_B;
    if (ivNum <= 23) return gText_IVRating_BPlus;
    if (ivNum <= 26) return gText_IVRating_A;
    if (ivNum <= 29) return gText_IVRating_APlus;
    if (ivNum == 30) return gText_IVRating_S;
    return gText_IVRating_SPlus;
}

void PrintSkillsPage(void)
{
    // Display Nature colored stats
    const s8 *natureMod = sNatureStatTable[GetNature(&sMonSummaryScreen->currentMon)];
    u16 curHpStr = GetNumberRightAlign63(sMonSummaryScreen->summary.curHpStrBuf);
    u16 atkStr = GetNumberRightAlign27(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK]);
    u16 defStr = GetNumberRightAlign27(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF]);
    u16 spAStr = GetNumberRightAlign27(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA]);
    u16 spDStr = GetNumberRightAlign27(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD]);
    u16 speStr = GetNumberRightAlign27(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE]);
    u16 expStr = GetNumberRightAlign63(sMonSummaryScreen->summary.expPointsStrBuf);
    u16 toNextLevel = GetNumberRightAlign63(sMonSummaryScreen->summary.expToNextLevelStrBuf);

    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 35 + curHpStr, 0, sNatureTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.curHpStrBuf);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 60 + atkStr, 19, sNatureTextColors[GetStatColor(natureMod[STAT_ATK - 1])], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 60 + defStr, 32, sNatureTextColors[GetStatColor(natureMod[STAT_DEF - 1])], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 60 + spAStr, 44, sNatureTextColors[GetStatColor(natureMod[STAT_SPATK - 1])], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 60 + spDStr, 56, sNatureTextColors[GetStatColor(natureMod[STAT_SPDEF - 1])], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 60 + speStr, 68, sNatureTextColors[GetStatColor(natureMod[STAT_SPD - 1])], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 0 + expStr, 92, sNatureTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.expPointsStrBuf);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + toNextLevel, 92, sNatureTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.expToNextLevelStrBuf);

    // Display Pokemon IVs
    if (FlagGet(FLAG_SHOW_IVS_IN_SUMMARY))
    {
        s32 ivNum;
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 0, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ATK_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 19, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_DEF_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 32, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPATK_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 44, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPDEF_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 56, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
        ivNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPEED_IV, 0);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_SMALL, 44, 68, sIVTextColors[GetIVColor(ivNum)], TEXT_SKIP_DRAW, GetIVAssessment(ivNum));
    }
}