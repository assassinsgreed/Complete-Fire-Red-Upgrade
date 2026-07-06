#include "defines.h"
#include "../include/menu.h"
#include "../include/pokemon_summary_screen.h"
#include "../include/string_util.h"
#include "../include/task.h"
#include "../include/event_data.h"
#include "../include/constants/flags.h"
#include "../include/new/ram_locs.h"
#include "../include/main.h"
#include "../include/gpu_regs.h"
#include "../include/sprite.h"

extern void LaunchEvIvViewerFromSummaryScreen(void); //from TaskEvIvInit.c
extern const u8 gText_EvIvDetails[];

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

static const struct TextColor sEvIvDetailsTextColour =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_WHITE,
    .shadowColor = TEXT_COLOR_DARK_GREY,
};

static void PrintEvIvDetailsPrompt(void)
{
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    WindowPrint(1, FONT_SMALL, 14, 0, &sEvIvDetailsTextColour, 0, gText_EvIvDetails);
}

static void Task_MonitorSummarySkillsPageForEvIv(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    bool8 switchInProgress;

    if (sMonSummaryScreen->curPageIndex != PSS_PAGE_SKILLS
        || !FlagGet(FLAG_ENABLE_EV_IV_VIEWER)
        || sMonSummaryScreen->mode == PSS_MODE_BOX)
    {
        DestroyTask(taskId);
        return;
    }

    // Re-draw after Pokémon switch: the input handler task (created before ours) redraws
    // key prompts when switchMonTaskState returns to 0. We run after it in the same
    // RunTasks() call, so we can immediately overdraw in the same frame.
    switchInProgress = sMonSummaryScreen->switchMonTaskState != 0;
    if (switchInProgress)
    {
        task->data[1] = 1;
    }
    else if (task->data[1])
    {
        task->data[1] = 0;
        PrintEvIvDetailsPrompt();
    }

    if (JOY_NEW(A_BUTTON) && !switchInProgress
        && sMonSummaryScreen->state3270 == PSS_STATE3270_HANDLEINPUT)
    {
        LaunchEvIvViewerFromSummaryScreen();
        DestroyTask(taskId);
    }
}

// TODO: This works, it just fires after the page is loading and causes the content here to "pop in"
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

    if (FlagGet(FLAG_ENABLE_EV_IV_VIEWER) && sMonSummaryScreen->mode != PSS_MODE_BOX)
    {
        // Write new keyprompts over existing ones
        PrintEvIvDetailsPrompt();

        if (!FuncIsActiveTask(Task_MonitorSummarySkillsPageForEvIv))
            CreateTask(Task_MonitorSummarySkillsPageForEvIv, 0);
    }
}

static void Task_BeginSummaryScreenOnSkillsPage(u8 taskId)
{
    u32 i;

    // This task first runs on the first CB2_RunPokemonSummaryScreen frame, right after the
    // vanilla setup (which laid the BGs out for an info page start) finishes behind the black
    // fade. Replicate the end state of a vanilla info->skills page flip: the vanilla setup
    // already loaded the skills tilemap on BG1 and the info tilemap on BG2, so only the BG
    // priorities, the parked scroll, and the flip bookkeeping need to change.
    SetGpuReg(REG_OFFSET_BG0CNT, (GetGpuReg(REG_OFFSET_BG0CNT) & ~3) | 0);
    SetGpuReg(REG_OFFSET_BG1CNT, (GetGpuReg(REG_OFFSET_BG1CNT) & ~3) | 1); // Skills page art in front
    SetGpuReg(REG_OFFSET_BG2CNT, (GetGpuReg(REG_OFFSET_BG2CNT) & ~3) | 2); // Info page art behind
    SetGpuReg(REG_OFFSET_BG2HOFS, -240); // Park the info art on the blank half of its 512px map
    sMonSummaryScreen->whichBgLayerToTranslate = 1;
    sMonSummaryScreen->flipPagesBgHofs = 240;

    // The HP/EXP bars rest at BG0 priority on the skills page, peeking through
    // the transparent cutout in the skills page art
    for (i = 0; i < MAX_SPRITES; ++i)
    {
        if (gSprites[i].inUse
            && (gSprites[i].template->tileTag == TAG_PSS_UNK_78 || gSprites[i].template->tileTag == TAG_PSS_UNK_82))
            gSprites[i].oam.priority = 0;
    }

    // The vanilla setup prints the page header key prompts after the skills page
    // text, wiping the EV/IV prompt PrintSkillsPage drew - draw it again
    if (FlagGet(FLAG_ENABLE_EV_IV_VIEWER) && sMonSummaryScreen->mode != PSS_MODE_BOX)
        PrintEvIvDetailsPrompt();

    DestroyTask(taskId);
}

void ShowPokemonSummaryScreenOnSkillsPage(struct Pokemon *party, u8 cursorPos, u8 lastIdx, void (*callback)(void), u8 mode)
{
    ShowPokemonSummaryScreen(party, cursorPos, lastIdx, callback, mode);

    if (sMonSummaryScreen == NULL // Alloc failed - the summary screen is already exiting to the callback
        || GetMonData(&party[cursorPos], MON_DATA_IS_EGG, NULL)) // Egg summaries only have the info page
        return;

    // The vanilla setup only supports starting on the info page; force the page index now so
    // the setup creates the skills windows/text, then patch the BG state up once it finishes.
    // The task survives the setup (which never resets tasks) and first runs after it completes.
    sMonSummaryScreen->curPageIndex = PSS_PAGE_SKILLS;
    CreateTask(Task_BeginSummaryScreenOnSkillsPage, 0);
}