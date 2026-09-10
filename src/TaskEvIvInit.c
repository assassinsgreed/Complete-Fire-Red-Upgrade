#include "../include/global.h"
#include "../include/pokemon.h"
#include "../include/bg.h"
#include "../include/window.h"
#include "../include/sprite.h"
#include "../include/palette.h"
#include "../include/task.h"
#include "../include/scanline_effect.h"
#include "../include/new/dns.h"
#include "../include/main.h"
#include "../include/new/Vanilla_Functions.h"
#include "../include/new/ram_locs.h"
#include "../include/gpu_regs.h"
#include "../include/overworld.h"
#include "../include/malloc.h"
#include "../include/sound.h"
#include "../include/constants/pokemon.h"
#include "../include/string_util.h"
#include "../include/menu.h"
#include "../include/party_menu.h"
#include "../include/constants/species.h"
#include "../include/field_weather.h"
#include "../include/text_window.h"
#include "../include/new/util.h"
#include "../include/new/util2.h"
#include "../include/constants/songs.h"
#include "../include/new/ability_util.h"
#include "../include/item.h"
#include "../include/pokemon_summary_screen.h"

// 1 = ON, 0 = OFF.  Activates or deactivates the sprite jump
#define SPRITE_JUMP             0

// 1 = FROM RIGHT TO LEFT, 0 = IN THE CENTER -1 = FROM LEFT TO RIGHT.
#define SPRITE_JUMP_DIRECTION   1

// 1 = RIGHT, 0 = LEFT.
#define SPRITE_VIEW_DIRECTION   0

// x/y coordinate of the pokemon sprite, measured in tiles of 8 pixels
#define PICMON_X    18
#define PICMON_Y     5

void CB2_ShowEvIv(void);
static void Task_EvIvInit(u8);
static u8 EvIvLoadGfx(void);
static void EvIvVblankHandler(void);
static void Task_WaitForExit(u8);
static void Task_EvIvExit(u8);
static void ShowSprite(struct Pokemon *mon);
static void EvIvPrintText(struct Pokemon *mon);
static void ShowPokemonPic2(u16 species, u32 otId, u32 personality, u8 x, u8 y);
static void Task_ScriptShowMonPic(u8 taskId);
static void HidePokemonPic2(u8 taskId);
static void PrintGenderText(struct Pokemon *mon);

static void PrintStat(u8 nature, u8 stat);
static u8 GetDigits(u16 num);
static u8 GetColorByNature(u8 nature, u8 stat);

extern const u8 bgEvIvTiles[];
extern const u8 bgEvIvMap[];
extern const u8 bgEvIvPal[];

enum
{
    WIN_POKEMON_NAME,
    WIN_STATS,
    WIN_BOTTOM_BOX
};

static const struct BgTemplate bg_Templates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 22,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 1,
    }, {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 19,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    }
};

#define WINDOW0_WIDTH   29
#define WINDOW0_HEIGTH  4

#define WINDOW1_WIDTH   17
#define WINDOW1_HEIGTH  11
#define WINDOW1_BASEBLOCK  (WINDOW0_WIDTH * WINDOW0_HEIGTH)

#define WINDOW2_WIDTH   29
#define WINDOW2_HEIGTH  5
#define WINDOW2_BASEBLOCK WINDOW1_WIDTH * WINDOW1_HEIGTH + WINDOW1_BASEBLOCK

static const struct WindowTemplate windows_templates[] = {
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 2,
        .width = WINDOW0_WIDTH,
        .height = WINDOW0_HEIGTH,
        .paletteNum = 15,
        .baseBlock = 0x000
    },{
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 4,
        .width = WINDOW1_WIDTH,
        .height = WINDOW1_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW1_BASEBLOCK
    },{
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = WINDOW2_WIDTH,
        .height = WINDOW2_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW2_BASEBLOCK
    }, DUMMY_WIN_TEMPLATE
};

struct EvIv
{
    u8 state;
    u8 gfxStep;
    u8 callbackStep;
    u8 currentMon;
    u8 spriteTaskId;
    u8 stats_ev[NUM_STATS];
    u8 stats_iv[NUM_STATS];
    u8 stats_bs[NUM_STATS];
    u16 totalStatsEV;
    u16 totalStatsIV;
    u16 totalStatsBS;
    u16 tilemapBuffer[0x400];
    u16 monSpriteId;
    MainCallback summaryCallback; //where the summary screen the viewer was opened from would have returned to
    u8 summaryMode;
};

extern struct EvIv *gEvIv;

#define gState              gEvIv->state
#define gGfxStep            gEvIv->gfxStep
#define gCallbackStep       gEvIv->callbackStep
#define gCurrentMon         gEvIv->currentMon
#define gSpriteTaskId       gEvIv->spriteTaskId
#define gStats_ev           gEvIv->stats_ev
#define gStats_iv           gEvIv->stats_iv
#define gStats_bs           gEvIv->stats_bs
#define gTotalStatsEV       gEvIv->totalStatsEV
#define gTotalStatsIV       gEvIv->totalStatsIV
#define gTotalStatsBS       gEvIv->totalStatsBS

static void PrintWindow0(struct Pokemon *mon);
static void PrintWindow1(u8 nature, u8 isEgg);
static void PrintWindow2(u16 species, u8 isEgg, u8 friendship, u8 ability);

#define PS_X        6
#define BS_X        50
#define EV_X        BS_X + 24
#define IV_X        EV_X + 20

#define HP_Y        3
#define ATK_Y       HP_Y + 14
#define DEF_Y       ATK_Y + 14
#define SPATK_Y     DEF_Y + 14
#define SPDEF_Y     SPATK_Y + 14
#define SPEED_Y     SPDEF_Y + 14

#define ABILITY_X        IV_X + 50
#define ABILITY_Y        SPEED_Y

static const u8 gBlackTextColor[3]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GREY,   TEXT_COLOR_LIGHT_GREY};
static const u8 gBlueTextColor[3]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,        TEXT_COLOR_LIGHT_GREY};
static const u8 gRedTextColor[3]    = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,         TEXT_COLOR_LIGHT_GREY};
static const u8 gGrayTextColor[3]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_LIGHT_GREY,  TEXT_COLOR_DARK_GREY};

static const u8 *const gTextColorByNature[] =
{
    gBlackTextColor,
    gRedTextColor,
    gBlueTextColor
};

extern const u8 gText_Slash[];
extern const u8 gText_CensorEgg[];

extern const u8 gText_Bs[];
extern const u8 gText_Ev[];
extern const u8 gText_Iv[];

extern const u8 gText_Total[];

extern const u8 gText_Is[];
extern const u8 gText_Happy[];

extern const u8 gText_Less_Than[];
extern const u8 gText_Steps_to_hatching[];
extern const u8 gText_EvLv[];

extern const u8 sGenderColors[2][3];
extern const u8 gText_MaleSymbol[];
extern const u8 gText_FemaleSymbol[];

static void PrintGenderText(struct Pokemon *mon)
{
    u8 genderSymbol[2];

    StringCopy(genderSymbol, gText_MaleSymbol);
    u8 gender = GetGenderFromSpeciesAndPersonality(mon->species, mon->personality);
    u8 isEgg = GetMonData(mon, MON_DATA_IS_EGG, NULL);

    if (gender != MON_GENDERLESS && !isEgg)
    {
        if (gender == MON_FEMALE)
        {
            StringCopy(genderSymbol, gText_FemaleSymbol);
            gender = FEMALE;
        }
        AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, 216, 2, sGenderColors[gender], 0, genderSymbol);
    }
}

static void EvIvBgInit(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static void CB2_EvIv(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

//Called from Task_MonitorSummarySkillsPageForEvIv in pokemon_summary_screen.c.
//Routes the launch through the summary screen's own teardown (which frees all of
//its resources) instead of hijacking the main callback out from under it, and
//stashes where that summary screen would have returned to so the viewer can
//reopen it on exit.
void LaunchEvIvViewerFromSummaryScreen(void)
{
    gEvIv = AllocZeroed(sizeof(*gEvIv));
    gEvIv->summaryCallback = sMonSummaryScreen->savedCallback;
    gEvIv->summaryMode = sMonSummaryScreen->mode;

    sMonSummaryScreen->savedCallback = CB2_ShowEvIv;
    sMonSummaryScreen->state3270 = PSS_STATE3270_ATEXIT_FADEOUT;
}

void CB2_ShowEvIv(void)
{
    if (gEvIv == NULL) //not launched from the summary screen
        gEvIv = AllocZeroed(sizeof(*gEvIv));
    gState = 0;
    gGfxStep = 0;
    gCallbackStep = 0;
    gCurrentMon = sLastViewedMonIndex;
    if (gCurrentMon >= gPlayerPartyCount) //stale summary/party cursor can point past the live party
        gCurrentMon = 0;
    EvIvBgInit();
    CreateTask(Task_EvIvInit, 0);
    SetMainCallback2(CB2_EvIv);
}

static void VCBC_EvIvOam(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_EvIvInit(u8 taskId)
{
    switch (gCallbackStep)
    {
    case 0:
        SetVBlankCallback(NULL);
        break;
    case 1:
        EvIvVblankHandler();
        break;
    case 2:
        if (!EvIvLoadGfx())
        {
            return;
        }
        break;
    case 3:
        CopyToBgTilemapBuffer(1, bgEvIvMap, 0, 0);
        break;
    case 4:
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        break;
    case 5:
        ShowSprite(&gPlayerParty[gCurrentMon]);
        EvIvPrintText(&gPlayerParty[gCurrentMon]);
        PrintGenderText(&gPlayerParty[gCurrentMon]);
        break;
    case 6:
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        break;
    case 7:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        break;
    case 8:
        SetVBlankCallback(VCBC_EvIvOam);
        break;
    default:
        if (gPaletteFade->active)
        {
            break;
        }
        gTasks[taskId].func = Task_WaitForExit;
    }
    gCallbackStep++;
}

static void Task_WaitForExit(u8 taskId)
{
    switch (gState)
    {
    case 0:
        gState++;
        break;
    case 1:
        if (JOY_NEW(A_BUTTON) || JOY_NEW(B_BUTTON))
        {
            PlaySE(242);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            gState++;
        }
        if (JOY_REPT(DPAD_DOWN) && gPlayerPartyCount > 1)
        {
            if (gCurrentMon >= (gPlayerPartyCount - 1)) // >= so a stale index self-corrects instead of running off the end
                gCurrentMon = 0;
            else
                gCurrentMon++;
            HidePokemonPic2(gSpriteTaskId);
            ShowSprite(&gPlayerParty[gCurrentMon]);
            EvIvPrintText(&gPlayerParty[gCurrentMon]);
            PrintGenderText(&gPlayerParty[gCurrentMon]);
        }
        if (JOY_REPT(DPAD_UP) && gPlayerPartyCount > 1)
        {
            if (gCurrentMon == 0 || gCurrentMon >= gPlayerPartyCount) // || so a stale index snaps back to the last valid slot
                gCurrentMon = (gPlayerPartyCount - 1);
            else
                gCurrentMon--;
            HidePokemonPic2(gSpriteTaskId);
            ShowSprite(&gPlayerParty[gCurrentMon]);
            EvIvPrintText(&gPlayerParty[gCurrentMon]);
            PrintGenderText(&gPlayerParty[gCurrentMon]);
        }
        break;
    case 2:
        if (!IsCryPlaying())
        {
            HidePokemonPic2(gSpriteTaskId); //have Task_ScriptShowMonPic free the mon pic resources
            gState++;
        }
        break;
    case 3:
        if (!gPaletteFade->active && !FuncIsActiveTask(Task_ScriptShowMonPic))
            Task_EvIvExit(taskId);
        break;
    }
}

static void Task_EvIvExit(u8 taskId)
{
    MainCallback summaryCallback = gEvIv->summaryCallback;
    u8 summaryMode = gEvIv->summaryMode;
    u8 cursorPos = gCurrentMon;

    DestroyTask(taskId);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(gEvIv);

    if (summaryCallback == NULL) //viewer wasn't opened from the summary screen
        SetMainCallback2(CB2_ReturnToFieldFromDiploma);
    else //return to the summary screen's skills page for the mon the viewer was showing
        ShowPokemonSummaryScreenOnSkillsPage(gPlayerParty, cursorPos, gPlayerPartyCount - 1, summaryCallback, summaryMode);
}

static void ResetBGPos(void)
{
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
}

static void ResetGpu(void)
{
    void *vram = (void *)VRAM;
    DmaClearLarge16(3, vram, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

static void EvIvVblankHandler(void)
{
    ResetGpu();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, bg_Templates, 2);
    ResetBGPos();
    InitWindows(windows_templates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetBgTilemapBuffer(1, gEvIv->tilemapBuffer);
    ShowBg(0);
    ShowBg(1);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
}

static u8 EvIvLoadGfx(void)
{
    switch (gGfxStep)
    {
    case 0:
        ResetTempTileDataBuffers();
        break;
    case 1:
        DecompressAndCopyTileDataToVram(1, bgEvIvTiles, 0, 0, 0);
        break;
    case 2:
        if (!(FreeTempTileDataBuffersIfPossible() == 1))
        {
            break;
        }
        return 0;
    case 3:
        LoadCompressedPalette(bgEvIvPal, 0, 0x20);
        LoadPalette(stdpal_get(0), 0xf0, 0x20);
        break;
    default:
        return 1;
    }
    gGfxStep++;
    return 0;
}

static void ShowSprite(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 isEgg    = GetMonData(mon, MON_DATA_IS_EGG, NULL);
    u32 otId = GetMonData(mon, MON_DATA_OT_ID, NULL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);

    if (!isEgg)
    {
        ShowPokemonPic2(species, otId, personality, PICMON_X, PICMON_Y);
        PlayCry7(species, 0);
    }else
        ShowPokemonPic2(SPECIES_EGG, 0, 0x8000, PICMON_X, PICMON_Y);
}

static void HidePokemonPic2(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    task->data[0]++;
}

static u8 CreateMonSprite_Field(u16 species, u32 otId, u32 personality, s16 x, s16 y)
{
    const struct CompressedSpritePalette * spritePalette = GetMonSpritePalStructFromOtIdPersonality(species, otId, personality);
    u16 spriteId = CreateMonPicSprite_HandleDeoxys(species, otId, personality, 1, x, y, 0, spritePalette->tag);
    PreservePaletteInWeather(IndexOfSpritePaletteTag(spritePalette->tag) + 0x10);
    if (spriteId == 0xFFFF)
        return MAX_SPRITES;
    else
        return spriteId;
}

static void ShowPokemonPic2(u16 species, u32 otId, u32 personality, u8 x, u8 y)
{
    u8 spriteId;

    spriteId = CreateMonSprite_Field(species, otId, personality, 8 * x + 40, 8 * y + 40);
    gSpriteTaskId = CreateTask(Task_ScriptShowMonPic, 80);

    gSprites[spriteId].hFlip = SPRITE_VIEW_DIRECTION;
    gSprites[spriteId].pos1.x -= 2;

#if SPRITE_JUMP == 1
    gSprites[spriteId].pos1.y -= 32;
    gSprites[spriteId].pos1.x += 48 * SPRITE_JUMP_DIRECTION;
#endif

    gTasks[gSpriteTaskId].data[0] = 0;
    gTasks[gSpriteTaskId].data[1] = species;
    gTasks[gSpriteTaskId].data[2] = spriteId;
    gTasks[gSpriteTaskId].data[3] = 0;
    gSprites[spriteId].callback = SpriteCallbackDummy;
    gSprites[spriteId].oam.priority = 0;
}

static void Task_ScriptShowMonPic(u8 taskId)
{
    struct Task * task = &gTasks[taskId];

#if SPRITE_JUMP == 1
    task->data[3]++;
    if (task->data[3] > 0x7FF0)
        task->data[3] = 0xFF;
#endif

    switch (task->data[0])
    {
    case 0:
        task->data[0]++;
        break;
    case 1:

#if SPRITE_JUMP == 1
        if (task->data[3] < 10)
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        else if (task->data[3] < 18)
        {
            gSprites[task->data[2]].pos1.y += 1;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 24)
        {
            gSprites[task->data[2]].pos1.y += 2;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 28)
        {
            gSprites[task->data[2]].pos1.y += 3;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 30)
        {
            gSprites[task->data[2]].pos1.y -= 3;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 32)
        {
            gSprites[task->data[2]].pos1.y -= 2;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 36)
        {
            gSprites[task->data[2]].pos1.y -= 1;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 40)
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        else if (task->data[3] < 44)
        {
            gSprites[task->data[2]].pos1.y += 1;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 46)
        {
            gSprites[task->data[2]].pos1.y += 2;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
        else if (task->data[3] < 48)
        {
            gSprites[task->data[2]].pos1.y += 3;
            gSprites[task->data[2]].pos1.x -= 1 * SPRITE_JUMP_DIRECTION;
        }
#endif

        break;
    case 2:
        FreeResourcesAndDestroySprite(&gSprites[task->data[2]], task->data[2]);
        task->data[0]++;
        break;
    case 3:
        DestroyTask(taskId);
        break;
    }
}

static void PrintStat(u8 nature, u8 stat)
{
    u8 color = GetColorByNature(nature, stat);

    ConvertIntToDecimalStringN(gStringVar1, gStats_bs[stat], STR_CONV_MODE_RIGHT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, gStats_ev[stat], STR_CONV_MODE_RIGHT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, gStats_iv[stat], STR_CONV_MODE_RIGHT_ALIGN, 2);

    switch (stat)
    {
        case STAT_HP:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, HP_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, HP_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, HP_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        case STAT_ATK:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, ATK_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, ATK_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, ATK_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        case STAT_DEF:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, DEF_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, DEF_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, DEF_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        case STAT_SPATK:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, SPATK_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, SPATK_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, SPATK_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        case STAT_SPDEF:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, SPDEF_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, SPDEF_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, SPDEF_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        case STAT_SPEED:
            AddTextPrinterParameterized3(WIN_STATS, 2, BS_X + 3, SPEED_Y, gTextColorByNature[color], 0, gStringVar1);
            AddTextPrinterParameterized3(WIN_STATS, 2, EV_X + 3, SPEED_Y, gTextColorByNature[color], 0, gStringVar2);
            AddTextPrinterParameterized3(WIN_STATS, 2, IV_X + 9, SPEED_Y, gTextColorByNature[color], 0, gStringVar3);
            break;
        default:
            break;
    }
}

static void PrintWindow0(struct Pokemon *mon)
{
    u8 temp;
    u8 leftAlignedText;
    leftAlignedText = 152;

    // Party position counter "1/6"
    temp = gCurrentMon + 1;
    ConvertIntToDecimalStringN(gStringVar4, temp, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringAppend(gStringVar4, gText_Slash);
    temp = gPlayerPartyCount;
    ConvertIntToDecimalStringN(gStringVar1, temp, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringAppend(gStringVar4, gStringVar1);
    AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, 0, 4, gGrayTextColor, 0, gStringVar4);

    // Nickname: moved right to avoid overlapping BS/EV/IV column headers (which end ~x=106)
    GetMonNickname(mon, gStringVar4);
    AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, leftAlignedText, 2, gBlackTextColor, 0, gStringVar4);

    // Level at y=2 immediately after nickname (y=16 is hidden by WIN_STATS tilemap overlap)
    StringCopy(gStringVar1, gText_EvLv);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(mon, MON_DATA_LEVEL, NULL), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(gStringVar1, gStringVar2);
    AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, leftAlignedText, 14, gBlackTextColor, 0, gStringVar1);
}

static void PrintWindow1(u8 nature, u8 isEgg)
{
    if (!isEgg)
    {
        PrintStat(nature, STAT_HP);
        PrintStat(nature, STAT_ATK);
        PrintStat(nature, STAT_DEF);
        PrintStat(nature, STAT_SPATK);
        PrintStat(nature, STAT_SPDEF);
        PrintStat(nature, STAT_SPEED);
    }
    else
    {
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, HP_Y,    gBlackTextColor, 0, gText_CensorEgg);
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, ATK_Y,   gBlackTextColor, 0, gText_CensorEgg);
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, DEF_Y,   gBlackTextColor, 0, gText_CensorEgg);
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, SPATK_Y, gBlackTextColor, 0, gText_CensorEgg);
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, SPDEF_Y, gBlackTextColor, 0, gText_CensorEgg);
        AddTextPrinterParameterized3(WIN_STATS, 2, BS_X, SPEED_Y, gBlackTextColor, 0, gText_CensorEgg);
    }
}

static void PrintWindow2(u16 species, u8 isEgg, u8 friendship, u8 ability)
{
    u16 temp = 0;

    if(!isEgg)
    {
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, 12, 4, gBlackTextColor, 0, gText_Total);

        ConvertIntToDecimalStringN(gStringVar1, gTotalStatsBS, STR_CONV_MODE_RIGHT_ALIGN, 3);
        ConvertIntToDecimalStringN(gStringVar2, gTotalStatsEV, STR_CONV_MODE_RIGHT_ALIGN, 3);
        ConvertIntToDecimalStringN(gStringVar3, gTotalStatsIV, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, BS_X + 12, 4, gBlackTextColor, 0, gStringVar1);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, EV_X + 12, 4, gBlackTextColor, 0, gStringVar2);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, IV_X + 12, 4, gBlackTextColor, 0, gStringVar3);

        StringCopy(gStringVar1, gText_Bs);
        StringCopy(gStringVar2, gText_Ev);
        StringCopy(gStringVar3, gText_Iv);
        AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, BS_X + 12, 4, gBlackTextColor, 0, gStringVar1);
        AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, EV_X + 12, 4, gBlackTextColor, 0, gStringVar2);
        AddTextPrinterParameterized3(WIN_POKEMON_NAME, 2, IV_X + 12, 4, gBlackTextColor, 0, gStringVar3);

        GetSpeciesName(gStringVar1, species);
        StringCopy(gStringVar4, gStringVar1);
        StringAppend(gStringVar4, gText_Is);
        temp = friendship;

        ConvertIntToDecimalStringN(gStringVar2, temp, STR_CONV_MODE_LEFT_ALIGN, 3);
        StringAppend(gStringVar4, gStringVar2);
        StringAppend(gStringVar4, gText_Happy);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, 12, 18, gBlackTextColor, 0, gStringVar4);

        CopyAbilityName(gStringVar1, ability, species);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, ABILITY_X, 4, gBlackTextColor, 0, gStringVar1);
    }
    else
    {
        StringCopy(gStringVar4, gText_Less_Than);
        temp = (friendship + 1) * 0xFF;
        ConvertIntToDecimalStringN(gStringVar2, temp, STR_CONV_MODE_LEFT_ALIGN, GetDigits(temp));
        StringAppend(gStringVar4, gStringVar2);
        StringAppend(gStringVar4, gText_Steps_to_hatching);
        AddTextPrinterParameterized3(WIN_BOTTOM_BOX, 2, 6, 18, gBlackTextColor, 0, gStringVar4);
    }
}

static void EvIvPrintText(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, 0);
    u8 nature   = GetNature(mon);
    u8 isEgg    = GetMonData(mon, MON_DATA_IS_EGG, 0);
    u8 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, 0);
    u8 ability = GetMonAbility(mon);

    gTotalStatsEV = 0;
    gTotalStatsIV = 0;
    gTotalStatsBS = 0;

    gStats_bs[STAT_HP]    = GetVisualBaseStat(STAT_HP,    species);
    gStats_ev[STAT_HP]    = GetMonData(mon, MON_DATA_HP_EV, 0);
    gStats_iv[STAT_HP]    = GetMonData(mon, MON_DATA_HP_IV, 0);

    gStats_bs[STAT_ATK]   = GetVisualBaseStat(STAT_ATK,   species);
    gStats_ev[STAT_ATK]   = GetMonData(mon, MON_DATA_ATK_EV,  0);
    gStats_iv[STAT_ATK]   = GetMonData(mon, MON_DATA_ATK_IV,  0);

    gStats_bs[STAT_DEF]   = GetVisualBaseStat(STAT_DEF,   species);
    gStats_ev[STAT_DEF]   = GetMonData(mon, MON_DATA_DEF_EV,  0);
    gStats_iv[STAT_DEF]   = GetMonData(mon, MON_DATA_DEF_IV,  0);

    gStats_bs[STAT_SPATK] = GetVisualBaseStat(STAT_SPATK, species);
    gStats_ev[STAT_SPATK] = GetMonData(mon, MON_DATA_SPATK_EV, 0);
    gStats_iv[STAT_SPATK] = GetMonData(mon, MON_DATA_SPATK_IV, 0);

    gStats_bs[STAT_SPDEF] = GetVisualBaseStat(STAT_SPDEF, species);
    gStats_ev[STAT_SPDEF] = GetMonData(mon, MON_DATA_SPDEF_EV, 0);
    gStats_iv[STAT_SPDEF] = GetMonData(mon, MON_DATA_SPDEF_IV, 0);

    gStats_bs[STAT_SPEED] = GetVisualBaseStat(STAT_SPEED, species);
    gStats_ev[STAT_SPEED] = GetMonData(mon, MON_DATA_SPEED_EV, 0);
    gStats_iv[STAT_SPEED] = GetMonData(mon, MON_DATA_SPEED_IV, 0);

    for (int i = 0; i < NUM_STATS; i++)
    {
        gTotalStatsEV += gStats_ev[i];
        gTotalStatsIV += gStats_iv[i];
        gTotalStatsBS += gStats_bs[i];
    }

    FillWindowPixelBuffer(0, 0);
    FillWindowPixelBuffer(1, 0);
    FillWindowPixelBuffer(2, 0);

    PrintWindow0(mon);
    PrintWindow1(nature, isEgg);
    PrintWindow2(species, isEgg, friendship, ability);

    PutWindowTilemap(0);
    PutWindowTilemap(1);
    PutWindowTilemap(2);
}

static u8 GetDigits(u16 num)
{
    if (num < 10)
        return 1;
    else if (num < 100)
        return 2;
    else if (num < 1000)
        return 3;
    else if (num < 10000)
        return 4;
    else
        return 5;
}

static u8 GetColorByNature(u8 nature, u8 stat)
{
    switch (stat)
    {
    case STAT_ATK:
        switch (nature)
        {
        case NATURE_LONELY:
        case NATURE_BRAVE:
        case NATURE_ADAMANT:
        case NATURE_NAUGHTY:
            return 1;
        case NATURE_BOLD:
        case NATURE_TIMID:
        case NATURE_MODEST:
        case NATURE_CALM:
            return 2;
        default:
            return 0;
        }
    case STAT_DEF:
        switch (nature)
        {
        case NATURE_BOLD:
        case NATURE_RELAXED:
        case NATURE_IMPISH:
        case NATURE_LAX:
            return 1;
        case NATURE_LONELY:
        case NATURE_HASTY:
        case NATURE_MILD:
        case NATURE_GENTLE:
            return 2;
        default:
            return 0;
        }
    case STAT_SPATK:
        switch (nature)
        {
        case NATURE_MODEST:
        case NATURE_MILD:
        case NATURE_QUIET:
        case NATURE_RASH:
            return 1;
        case NATURE_ADAMANT:
        case NATURE_IMPISH:
        case NATURE_JOLLY:
        case NATURE_CAREFUL:
            return 2;
        default:
            return 0;
        }
    case STAT_SPDEF:
        switch (nature)
        {
        case NATURE_CALM:
        case NATURE_GENTLE:
        case NATURE_SASSY:
        case NATURE_CAREFUL:
            return 1;
        case NATURE_NAUGHTY:
        case NATURE_LAX:
        case NATURE_NAIVE:
        case NATURE_RASH:
            return 2;
        default:
            return 0;
        }
    case STAT_SPEED:
        switch (nature)
        {
        case NATURE_TIMID:
        case NATURE_HASTY:
        case NATURE_JOLLY:
        case NATURE_NAIVE:
            return 1;
        case NATURE_BRAVE:
        case NATURE_RELAXED:
        case NATURE_QUIET:
        case NATURE_SASSY:
            return 2;
        default:
            return 0;
        }
    case STAT_HP:
    default:
        return 0;
    }
}
