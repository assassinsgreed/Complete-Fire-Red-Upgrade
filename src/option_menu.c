#include "defines.h"
#include "defines_battle.h"
#include "../include/option_menu.h"
#include "../include/battle_setup.h"
#include "../include/event_data.h"
#include "../include/pokemon.h"
#include "../include/pokemon_storage_system.h"
#include "../include/random.h"
#include "../include/script.h"
#include "../include/string_util.h"
#include "../include/wild_encounter.h"
#include "../include/constants/event_objects.h"
#include "../include/constants/items.h"
#include "../include/constants/maps.h"
#include "../include/constants/pokedex.h"
#include "../include/constants/region_map_sections.h"
#include "../include/constants/species.h"
#include "../include/constants/trainer_classes.h"
#include "../include/constants/trainers.h"
#include "../include/constants/tutors.h"
#include "../include/new/ability_tables.h"
#include "../include/new/ai_advanced.h"
#include "../include/new/build_pokemon.h"
#include "../include/new/build_pokemon_2.h"
#include "../include/new/catching.h"
#include "../include/new/dexnav.h"
#include "../include/new/dynamax.h"
#include "../include/new/form_change.h"
#include "../include/new/frontier.h"
#include "../include/new/item.h"
#include "../include/new/learn_move.h"
#include "../include/new/mega.h"
#include "../include/new/multi.h"
#include "../include/new/pokemon_storage_system.h"
#include "../include/new/util2.h"
#include "../include/text.h"
#include "../include/overworld.h"
#include "../include/tm_case.h"
#include "../include/text_window.h"
#include "../include/bg.h"
#include "../include/pokemon_summary_screen.h"
#include "../include/menu.h"
#include "../include/new/battle_strings.h"
#include "../include/pokedex.h"
#include "../include/menu_helpers.h"
#include "../include/gba/m4a_internal.h"
#include "../include/malloc.h"
#include "../include/mgba.h"
#include "../include/sound.h"
#include "../include/constants/songs.h"

void CB2_OptionMenu(void);
bool8 LoadOptionMenuPalette(void);
void LoadOptionMenuItemNames(void);
void Task_OptionMenu(u8 taskId);
void CloseAndSaveOptionMenu(u8 taskId);
u8 OptionMenu_ProcessInput(void);
void BufferOptionMenuString(u8 selection);
void OptionMenu_PickSwitchCancel(void);

// Menu items
enum
{
    MENUITEM_TEXTSPEED = 0,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

enum
{
    MENUITEM_AUTOSORTBAG,
    MENUITEM_SKIP_CUTSCENES,
    MENUITEM_SKIP_NICKNAMING,
    MENUITEM_BALL_SHORTCUT,
    MENUITEM_NURSE_HEALING,
    MENUITEM_WILD_ENCOUNTERS,
    MENUITEM_CANCEL_PAGE_2,
    MENUITEM_PAGE2_COUNT,
};

enum
{
	MENUITEM_GAME_DIFFICULTY,
    MENUITEM_LEVEL_CAPS,
    MENUITEM_OVERWORLD_SPEED,
    MENUITEM_BATTLE_SPEED,
    MENUITEM_CANCEL_PAGE_3,
    MENUITEM_PAGE3_COUNT,
};

#define OPTION_MENU_PAGE_COUNT 3

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

struct OptionMenu
{
    /*0x00*/ u16 option[MENUITEM_COUNT];
    /*0x??*/ u16 cursorPos;
    /*0x??*/ u8 loadState;
    /*0x??*/ u8 state;
    /*0x??*/ u8 loadPaletteState;
    /*0x??*/ u8 page;
    /*0x??*/ u16 option_secondPage[MENUITEM_PAGE2_COUNT];
    /*0x??*/ u16 option_thirdPage[MENUITEM_PAGE3_COUNT];
};

extern struct OptionMenu *sOptionMenuPtr;
extern const u8 gText_TextSpeed[];
extern const u8 gText_BattleScene[];
extern const u8 gText_BattleStyle[];
extern const u8 gText_Sound[];
extern const u8 gText_ButtonMode[];
extern const u8 gText_Frame[];
extern const u8 gText_OptionMenuCancel[];
extern const u8 gText_RButtonMode[];
extern const u8 gText_BattleMusic[];
extern const u8 gText_WildLevelScaling[];
extern const u8 gText_OptionsMenu_AutoSortBag[];
extern const u8 gText_OptionsMenu_GameDifficulty[];
extern const u8 gText_OptionsMenu_LevelCaps[];
extern const u8 gText_OptionsMenu_OverworldSpeed[];
extern const u8 gText_OptionsMenu_BattleSpeed[];
extern const u8 gText_OptionsMenu_SkipCutscenes[];
extern const u8 gText_OptionsMenu_SkipNicknaming[];
extern const u8 gText_OptionsMenu_BallShortcut[];
extern const u8 gText_OptionsMenu_NurseHealing[];
extern const u8 gText_OptionsMenu_PokemonSelection[];

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = gText_TextSpeed,
    [MENUITEM_BATTLESCENE] = gText_BattleScene,
    [MENUITEM_BATTLESTYLE] = gText_BattleStyle,
    [MENUITEM_SOUND]       = gText_Sound,
    [MENUITEM_BUTTONMODE]  = gText_ButtonMode,
    [MENUITEM_FRAMETYPE]   = gText_Frame,
    [MENUITEM_CANCEL]      = gText_OptionMenuCancel,
};
static const u8 *const sOptionMenuItemsNames_SecondPage[MENUITEM_PAGE2_COUNT] =
{
    [MENUITEM_AUTOSORTBAG] = gText_OptionsMenu_AutoSortBag,
    [MENUITEM_SKIP_CUTSCENES] = gText_OptionsMenu_SkipCutscenes,
    [MENUITEM_SKIP_NICKNAMING] = gText_OptionsMenu_SkipNicknaming,
    [MENUITEM_BALL_SHORTCUT] = gText_OptionsMenu_BallShortcut,
    [MENUITEM_NURSE_HEALING] = gText_OptionsMenu_NurseHealing,
    [MENUITEM_WILD_ENCOUNTERS] = gText_OptionsMenu_PokemonSelection,
    [MENUITEM_CANCEL_PAGE_2] = gText_OptionMenuCancel,
};
static const u8 *const sOptionMenuItemsNames_ThirdPage[MENUITEM_PAGE3_COUNT] =
{
	[MENUITEM_GAME_DIFFICULTY] = gText_OptionsMenu_GameDifficulty,
    [MENUITEM_LEVEL_CAPS] = gText_OptionsMenu_LevelCaps,
    [MENUITEM_OVERWORLD_SPEED] = gText_OptionsMenu_OverworldSpeed,
    [MENUITEM_BATTLE_SPEED] = gText_OptionsMenu_BattleSpeed,
    [MENUITEM_CANCEL_PAGE_3] = gText_OptionMenuCancel,
};

extern const u8 gText_TextSpeedSlow[];
extern const u8 gText_TextSpeedMid[];
extern const u8 gText_TextSpeedFast[];
extern const u8 gText_BattleSceneOn[];
extern const u8 gText_BattleSceneOff[];
extern const u8 gText_BattleStyleShift[];
extern const u8 gText_BattleStyleSet[];
extern const u8 gText_SoundMono[];
extern const u8 gText_SoundStereo[];
extern const u8 gText_ButtonTypeHelp[];
extern const u8 gText_ButtonTypeLR[];
extern const u8 gText_ButtonTypeLEqualsA[];
extern const u8 gText_MenuOption[];
extern const u8 gText_FrameType[];
extern const u8 gText_OptionsMenu_On[];
extern const u8 gText_OptionsMenu_Off[];
extern const u8 gText_OptionsMenu_AutoSortBag_ByName[];
extern const u8 gText_OptionsMenu_AutoSortBag_ByType[];
extern const u8 gText_OptionsMenu_AutoSortBag_ByAmount[];
extern const u8 gText_OptionsMenu_GameDifficulty_Standard[];
extern const u8 gText_OptionsMenu_GameDifficulty_Hard[];
extern const u8 gText_OptionsMenu_GameDifficulty_ExtraHard[];
extern const u8 gText_OptionsMenu_LevelCaps_Soft[];
extern const u8 gText_OptionsMenu_LevelCaps_Hard[];
extern const u8 gText_OptionsMenu_LevelCaps_ExtraHard[];
extern const u8 gText_OptionsMenu_BallShortcut_Optimal[];
extern const u8 gText_OptionsMenu_BallShortcut_LastUsed[];
extern const u8 gText_OptionsMenu_NurseHealing_Default[];
extern const u8 gText_OptionsMenu_NurseHealing_Short[];
extern const u8 gText_OptionsMenu_PokemonSelection_Standard[];
extern const u8 gText_OptionsMenu_PokemonSelection_Divergent[];
extern const u8 gText_OptionsMenu_OverworldSpeed_Normal[];
extern const u8 gText_OptionsMenu_OverworldSpeed_2x[];
extern const u8 gText_OptionsMenu_OverworldSpeed_3x[];
extern const u8 gText_OptionsMenu_OverworldSpeed_4x[];
extern const u8 gText_OptionsMenu_BattleSpeed_Normal[];
extern const u8 gText_OptionsMenu_BattleSpeed_2x[];
extern const u8 gText_OptionsMenu_BattleSpeed_3x[];
extern const u8 gText_OptionsMenu_BattleSpeed_4x[];

static const u8 *const sTextSpeedOptions[] =
{
    gText_TextSpeedSlow, 
    gText_TextSpeedMid, 
    gText_TextSpeedFast
};
static const u8 *const sBattleSceneOptions[] =
{
    gText_BattleSceneOn, 
    gText_BattleSceneOff
};
static const u8 *const sBattleStyleOptions[] =
{
    gText_BattleStyleShift,
    gText_BattleStyleSet
};
static const u8 *const sSoundOptions[] =
{
    gText_SoundMono, 
    gText_SoundStereo
};
static const u8 *const sButtonTypeOptions[] =
{
    gText_ButtonTypeHelp,
	gText_ButtonTypeLR,
	gText_ButtonTypeLEqualsA
};

static const u8 *const sAutoSortBagOptions[] =
{
    gText_OptionsMenu_Off,
	gText_OptionsMenu_AutoSortBag_ByName,
    gText_OptionsMenu_AutoSortBag_ByType,
    gText_OptionsMenu_AutoSortBag_ByAmount,
};
static const u8 *const sGameDifficultyOptions[] =
{
	gText_OptionsMenu_GameDifficulty_Standard,
	gText_OptionsMenu_GameDifficulty_Hard,
	gText_OptionsMenu_GameDifficulty_ExtraHard,
};
static const u8 *const sLevelCapsOptions[] =
{
	gText_OptionsMenu_LevelCaps_Soft,
	gText_OptionsMenu_LevelCaps_Hard,
	gText_OptionsMenu_LevelCaps_ExtraHard,
};
static const u8 *const sSkipCutscenesOptions[] =
{
    gText_OptionsMenu_Off,
    gText_OptionsMenu_On,
};
static const u8 *const sSkipNicknamingOptions[] =
{
    gText_OptionsMenu_Off,
    gText_OptionsMenu_On,
};
static const u8 *const sBallShortcutOptions[] =
{
    gText_OptionsMenu_BallShortcut_Optimal,
    gText_OptionsMenu_BallShortcut_LastUsed,
};
static const u8 *const sNurseHealingOptions[] =
{
    gText_OptionsMenu_NurseHealing_Default,
    gText_OptionsMenu_NurseHealing_Short,
};
static const u8 *const sOverworldSpeedOptions[] =
{
    [OPTIONS_OVERWORLD_SPEED_NORMAL] = gText_OptionsMenu_OverworldSpeed_Normal,
    [OPTIONS_OVERWORLD_SPEED_2X] = gText_OptionsMenu_OverworldSpeed_2x,
    [OPTIONS_OVERWORLD_SPEED_3X] = gText_OptionsMenu_OverworldSpeed_3x,
    [OPTIONS_OVERWORLD_SPEED_4X] = gText_OptionsMenu_OverworldSpeed_4x,
};
static const u8 *const sBattleSpeedOptions[] =
{
    [OPTIONS_BATTLE_SPEED_NORMAL] = gText_OptionsMenu_BattleSpeed_Normal,
    [OPTIONS_BATTLE_SPEED_2X] = gText_OptionsMenu_BattleSpeed_2x,
    [OPTIONS_BATTLE_SPEED_3X] = gText_OptionsMenu_BattleSpeed_3x,
    [OPTIONS_BATTLE_SPEED_4X] = gText_OptionsMenu_BattleSpeed_4x,
};
static const u8 *const sWildEncountersOptions[] =
{
    gText_OptionsMenu_PokemonSelection_Standard,
    gText_OptionsMenu_PokemonSelection_Divergent,
};

// The frame type row builds its text at runtime, so it has no table here
static const u8 *const *const sOptionMenuItemChoices[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = sTextSpeedOptions,
    [MENUITEM_BATTLESCENE] = sBattleSceneOptions,
    [MENUITEM_BATTLESTYLE] = sBattleStyleOptions,
    [MENUITEM_SOUND]       = sSoundOptions,
    [MENUITEM_BUTTONMODE]  = sButtonTypeOptions,
    [MENUITEM_FRAMETYPE]   = NULL,
    [MENUITEM_CANCEL]      = NULL,
};
static const u8 *const *const sOptionMenuItemChoices_SecondPage[MENUITEM_PAGE2_COUNT] =
{
    [MENUITEM_AUTOSORTBAG] = sAutoSortBagOptions,
    [MENUITEM_SKIP_CUTSCENES] = sSkipCutscenesOptions,
    [MENUITEM_SKIP_NICKNAMING] = sSkipNicknamingOptions,
    [MENUITEM_BALL_SHORTCUT] = sBallShortcutOptions,
    [MENUITEM_NURSE_HEALING] = sNurseHealingOptions,
    [MENUITEM_WILD_ENCOUNTERS] = sWildEncountersOptions,
    [MENUITEM_CANCEL_PAGE_2] = NULL,
};
static const u8 *const *const sOptionMenuItemChoices_ThirdPage[MENUITEM_PAGE3_COUNT] =
{
	[MENUITEM_GAME_DIFFICULTY] = sGameDifficultyOptions,
    [MENUITEM_LEVEL_CAPS] = sLevelCapsOptions,
    [MENUITEM_OVERWORLD_SPEED] = sOverworldSpeedOptions,
    [MENUITEM_BATTLE_SPEED] = sBattleSpeedOptions,
    [MENUITEM_CANCEL_PAGE_3] = NULL,
};

// # of choices per option, not counting cancel
static const u16 sOptionMenuItemCounts[MENUITEM_COUNT] = {3, 2, 2, 2, 3, 10, 0};
static const u16 sOptionMenuItemCounts_SecondPage[MENUITEM_PAGE2_COUNT] = {4, 2, 2, 2, 2, 2, 0};
static const u16 sOptionMenuItemCounts_ThirdPage[MENUITEM_PAGE3_COUNT] = {3, 3, OPTIONS_OVERWORLD_SPEED_COUNT, OPTIONS_BATTLE_SPEED_COUNT, 0};

static u16 *GetPageOptions(u8 page)
{
    switch (page)
    {
        case 1:  return sOptionMenuPtr->option_secondPage;
        case 2:  return sOptionMenuPtr->option_thirdPage;
        default: return sOptionMenuPtr->option;
    }
}

static const u8 *const *GetPageItemNames(u8 page)
{
    switch (page)
    {
        case 1:  return sOptionMenuItemsNames_SecondPage;
        case 2:  return sOptionMenuItemsNames_ThirdPage;
        default: return sOptionMenuItemsNames;
    }
}

static const u8 *const *const *GetPageItemChoices(u8 page)
{
    switch (page)
    {
        case 1:  return sOptionMenuItemChoices_SecondPage;
        case 2:  return sOptionMenuItemChoices_ThirdPage;
        default: return sOptionMenuItemChoices;
    }
}

static const u16 *GetPageItemCounts(u8 page)
{
    switch (page)
    {
        case 1:  return sOptionMenuItemCounts_SecondPage;
        case 2:  return sOptionMenuItemCounts_ThirdPage;
        default: return sOptionMenuItemCounts;
    }
}

static u8 GetPageItemCount(u8 page) // Rows on the page, including cancel
{
    switch (page)
    {
        case 1:  return MENUITEM_PAGE2_COUNT;
        case 2:  return MENUITEM_PAGE3_COUNT;
        default: return MENUITEM_COUNT;
    }
}

static bool8 IsPageRowHidden(u8 page, u8 menuItem)
{
    return page == 1
        && menuItem == MENUITEM_WILD_ENCOUNTERS
        && !FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS_OPTION_SHOWN);
}

static u8 GetPageVisualRow(u8 page, u8 menuItem) // Rows below a hidden one move up to close the gap
{
    if (page == 1 && !FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS_OPTION_SHOWN) && menuItem > MENUITEM_WILD_ENCOUNTERS)
        return menuItem - 1;
    return menuItem;
}

void CB2_OptionsMenuFromStartMenu(void)
{
    u8 i;
    
    if (gMain.savedCallback == NULL)
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
    sOptionMenuPtr = AllocZeroed(sizeof(struct OptionMenu));
    sOptionMenuPtr->loadState = 0;
    sOptionMenuPtr->loadPaletteState = 0;
    sOptionMenuPtr->state = 0;
    sOptionMenuPtr->cursorPos = 0;
    sOptionMenuPtr->option[MENUITEM_TEXTSPEED] = gSaveBlock2->optionsTextSpeed;
    sOptionMenuPtr->option[MENUITEM_BATTLESCENE] = gSaveBlock2->optionsBattleSceneOff;
    sOptionMenuPtr->option[MENUITEM_BATTLESTYLE] = gSaveBlock2->optionsBattleStyle;
    sOptionMenuPtr->option[MENUITEM_SOUND] = gSaveBlock2->optionsSound;
    sOptionMenuPtr->option[MENUITEM_BUTTONMODE] = gSaveBlock2->optionsButtonMode;
    sOptionMenuPtr->option[MENUITEM_FRAMETYPE] = gSaveBlock2->optionsWindowFrameType;
    sOptionMenuPtr->option_secondPage[MENUITEM_AUTOSORTBAG] = VarGet(VAR_AUTO_SORT_BAG);
    sOptionMenuPtr->option_secondPage[MENUITEM_SKIP_CUTSCENES] = FlagGet(FLAG_SKIP_CUTSCENES) ? 1 : 0;
    sOptionMenuPtr->option_secondPage[MENUITEM_SKIP_NICKNAMING] = FlagGet(FLAG_DONT_OFFER_NICKNAMES_BATTLE) ? 1 : 0;
    sOptionMenuPtr->option_secondPage[MENUITEM_BALL_SHORTCUT] = FlagGet(FLAG_OPTIONS_LAST_USED_BALL) ? 1 : 0;
    sOptionMenuPtr->option_secondPage[MENUITEM_NURSE_HEALING] = FlagGet(FLAG_OPTIONS_SHORT_NURSE_HEAL) ? 1 : 0;
    sOptionMenuPtr->option_secondPage[MENUITEM_WILD_ENCOUNTERS] = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? 1 : 0;
    sOptionMenuPtr->option_thirdPage[MENUITEM_GAME_DIFFICULTY] = VarGet(VAR_DIFFICULTY_SETTING);
    sOptionMenuPtr->option_thirdPage[MENUITEM_LEVEL_CAPS] = VarGet(VAR_LEVEL_CAPS);
    sOptionMenuPtr->option_thirdPage[MENUITEM_OVERWORLD_SPEED] = VarGet(VAR_OVERWORLD_SPEED);
    if (sOptionMenuPtr->option_thirdPage[MENUITEM_OVERWORLD_SPEED] >= OPTIONS_OVERWORLD_SPEED_COUNT)
        sOptionMenuPtr->option_thirdPage[MENUITEM_OVERWORLD_SPEED] = OPTIONS_OVERWORLD_SPEED_NORMAL;
    sOptionMenuPtr->option_thirdPage[MENUITEM_BATTLE_SPEED] = VarGet(VAR_BATTLE_SPEED);
    if (sOptionMenuPtr->option_thirdPage[MENUITEM_BATTLE_SPEED] >= OPTIONS_BATTLE_SPEED_COUNT)
        sOptionMenuPtr->option_thirdPage[MENUITEM_BATTLE_SPEED] = OPTIONS_BATTLE_SPEED_NORMAL;

    VarSet(VAR_TEMP_2, VarGet(VAR_LEVEL_CAPS));
    FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS) ? FlagSet(FLAG_TEMP_C) : FlagClear(FLAG_TEMP_C);
    
    for (i = 0; i < MENUITEM_COUNT - 1; i++)
    {
        if (sOptionMenuPtr->option[i] > (sOptionMenuItemCounts[i]) - 1)
            sOptionMenuPtr->option[i] = 0;
    }
    SetMainCallback2(CB2_OptionMenu);
}

void Task_OptionMenu(u8 taskId)
{
    u8 i;
    switch (sOptionMenuPtr->loadState)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, RGB_BLACK);
        OptionMenu_SetVBlankCallback();
        sOptionMenuPtr->loadState++;
        break;
    case 1:
        if (gPaletteFade->active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 2:
        if (((bool32)MenuHelpers_CallLinkSomething()) == TRUE)
            break;
        switch (OptionMenu_ProcessInput())
        {
        case 0:
            break;
        case 1:
            sOptionMenuPtr->loadState++;
            break;
        case 2:
            LoadBgTiles(1, GetUserFrameGraphicsInfo(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
            LoadPalette(GetUserFrameGraphicsInfo(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
            BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
        case 3:
            UpdateSettingSelectionDisplay(GetPageVisualRow(sOptionMenuPtr->page, sOptionMenuPtr->cursorPos));
            break;
        case 4:
            BufferOptionMenuString(sOptionMenuPtr->cursorPos);
            break;
        case 5: // The page changed, so redraw whichever one is now current
            LoadOptionMenuItemNames();
            for (i = 0; i < GetPageItemCount(sOptionMenuPtr->page); i++)
                BufferOptionMenuString(i);
            sOptionMenuPtr->cursorPos = 0;
            UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
            OptionMenu_PickSwitchCancel();
            break;
        }
        break;
    case 3:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        sOptionMenuPtr->loadState++;
        break;
    case 4:
        if (gPaletteFade->active)
            return;
        sOptionMenuPtr->loadState++;
        break;
    case 5:
        CloseAndSaveOptionMenu(taskId);
        break;
    }
}

extern const u8 EventScript_NotifyLevelCapChange[];

void CloseAndSaveOptionMenu(u8 taskId)
{
    bool8 levelCapChanged;
    bool8 pokemonSelectionChanged;

    FreeAllWindowBuffers();
    gSaveBlock2->optionsTextSpeed = sOptionMenuPtr->option[MENUITEM_TEXTSPEED];
    gSaveBlock2->optionsBattleSceneOff = sOptionMenuPtr->option[MENUITEM_BATTLESCENE];
    gSaveBlock2->optionsBattleStyle = sOptionMenuPtr->option[MENUITEM_BATTLESTYLE];
    gSaveBlock2->optionsSound = sOptionMenuPtr->option[MENUITEM_SOUND];
    gSaveBlock2->optionsButtonMode = sOptionMenuPtr->option[MENUITEM_BUTTONMODE];
    gSaveBlock2->optionsWindowFrameType = sOptionMenuPtr->option[MENUITEM_FRAMETYPE];
    VarSet(VAR_AUTO_SORT_BAG, sOptionMenuPtr->option_secondPage[MENUITEM_AUTOSORTBAG]);
    VarSet(VAR_DIFFICULTY_SETTING, sOptionMenuPtr->option_thirdPage[MENUITEM_GAME_DIFFICULTY]);
    VarSet(VAR_LEVEL_CAPS, sOptionMenuPtr->option_thirdPage[MENUITEM_LEVEL_CAPS]);
    VarSet(VAR_OVERWORLD_SPEED, sOptionMenuPtr->option_thirdPage[MENUITEM_OVERWORLD_SPEED]);
    VarSet(VAR_BATTLE_SPEED, sOptionMenuPtr->option_thirdPage[MENUITEM_BATTLE_SPEED]);
    // Cleanup difficulty / level cap vars to flags
    sOptionMenuPtr->option_thirdPage[MENUITEM_GAME_DIFFICULTY] >= OPTIONS_AMETHYST_HARD_DIFFICULTY ? FlagSet(FLAG_HARD_MODE) : FlagClear(FLAG_HARD_MODE);
    sOptionMenuPtr->option_thirdPage[MENUITEM_LEVEL_CAPS] >= OPTIONS_AMETHYST_HARD_LEVEL_CAPS ? FlagSet(FLAG_HARD_LEVEL_CAP) : FlagClear(FLAG_HARD_LEVEL_CAP);
    sOptionMenuPtr->option_secondPage[MENUITEM_SKIP_CUTSCENES] == 1 ? FlagSet(FLAG_SKIP_CUTSCENES) : FlagClear(FLAG_SKIP_CUTSCENES);
    sOptionMenuPtr->option_secondPage[MENUITEM_SKIP_NICKNAMING] == 1 ? FlagSet(FLAG_DONT_OFFER_NICKNAMES_BATTLE) : FlagClear(FLAG_DONT_OFFER_NICKNAMES_BATTLE);
    sOptionMenuPtr->option_secondPage[MENUITEM_BALL_SHORTCUT] == 1 ? FlagSet(FLAG_OPTIONS_LAST_USED_BALL) : FlagClear(FLAG_OPTIONS_LAST_USED_BALL);
    sOptionMenuPtr->option_secondPage[MENUITEM_NURSE_HEALING] == 1 ? FlagSet(FLAG_OPTIONS_SHORT_NURSE_HEAL) : FlagClear(FLAG_OPTIONS_SHORT_NURSE_HEAL);
    if (FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS_OPTION_SHOWN))
        sOptionMenuPtr->option_secondPage[MENUITEM_WILD_ENCOUNTERS] == 1 ? FlagSet(FLAG_DIVERGENT_WILD_ENCOUNTERS) : FlagClear(FLAG_DIVERGENT_WILD_ENCOUNTERS);

    levelCapChanged = (VarGet(VAR_TEMP_2) != VarGet(VAR_LEVEL_CAPS));
    pokemonSelectionChanged = (FlagGet(FLAG_TEMP_C) != FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS));

    if (levelCapChanged)
    {
        // Set up the script before switching callbacks. CB2_ReturnToFieldContinueScript
        // will call ScriptContext2_Enable() after field init, which picks up the script
        // we've placed here. This mirrors how the underground mining game returns to a
        // running script: the script pointer survives the callback transition.
        ScriptContext1_SetupScript(EventScript_NotifyLevelCapChange);
        gFieldCallback = FieldCB_DefaultWarpExit;
        SetMainCallback2(CB2_ReturnToFieldContinueScript);
    }
    else
    {
        gFieldCallback = FieldCB_DefaultWarpExit;
        SetMainCallback2(gMain.savedCallback);
    }

    if (pokemonSelectionChanged)
    {
        // Mega Stones
        FlagClear(FLAG_HIDE_MIMMETT_JUNGLE_VENUSAURITE);
        FlagClear(FLAG_HIDE_HESSON_PASS_BF1_CHARIZARDITE_X);
        FlagClear(FLAG_HIDE_CARNELIDGE_VOLCANO_OVERWORLD_CHARIZARDITE_Y);
        FlagClear(FLAG_HIDE_ROUTE_6_BLASTOISINITE);
        FlagClear(FLAG_HIDE_ROUTE9_SCEPTILITE);
        FlagClear(FLAG_HIDE_SCALDING_SPA_BLAZIKENITE);
        FlagClear(FLAG_HIDE_ROUTE8_SWAMPERTITE);
        FlagClear(FLAG_HIDE_HELEO_RANCH_AMPHAROSITE_OR_PIDGEOTITE);
        FlagClear(FLAG_HIDE_FORGOTTEN_MANSE_1F_SABLENITE_OR_BANETTITE);
        FlagClear(FLAG_HIDE_ROUTE10_LOPUNNITE_OR_MANECTITE);
        FlagClear(FLAG_HIDE_ROUTE11_SOUTH_MAWILITE_OR_MEDICHAMITE);
        FlagClear(FLAG_HIDE_RUBARR_DESERT_BF1_GARCHOMPITE_OR_AERODACTYLITE);
        FlagClear(FLAG_HIDE_TORMA_CAVE_BF1_GLALITITE_OR_STEELIXITE);
        FlagClear(FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_LUCARIONITE_OR_METAGROSSITE);
        FlagClear(FLAG_HIDE_PERADON_FOREST_HERACRONITE_OR_PINSIRITE);
        FlagClear(FLAG_HIDE_ROUTE_12_WEST_SLOWBRONITE_OR_ABOMASITE);
        FlagClear(FLAG_HIDE_ROUTE16_SHARPEDONITE_OR_SALAMENCITE);
        FlagClear(FLAG_HIDE_ROUTE18_GALLADITE_OR_ABSOLITE);
        FlagClear(FLAG_HIDE_ROUTE20_KANGASKHANITE_OR_SCIZORITE);
        FlagClear(FLAG_HIDE_UTEYAN_RUINS_GARDEVOIRITE_OR_ALAKAZITE);

        // Give story mega stones (Houndoominite / Tyranitarite) if past carnelidge volcano and swapping, and they aren't in the bag
        if (FlagGet(FLAG_COMPLETED_CARNELIDGE_VOLCANO_STORY))
        {
            if (FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS))
            {
                if (!CheckBagHasItem(ITEM_TYRANITARITE, 1))
                    AddBagItem(ITEM_TYRANITARITE, 1);
            }
            else
            {
                if (!CheckBagHasItem(ITEM_HOUNDOOMINITE, 1))
                    AddBagItem(ITEM_HOUNDOOMINITE, 1);

                }
            }
            
        /*
            Beedrillnite, Aggronite, Cameruptite, Altarianite, and Audinite are Divergent-only and are hidden in
            overworld.c, so they are hidden in historic saves in standard mode
        */
        if (FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS))
        {
            // Reenable Divergent-only mode stones
            FlagClear(FLAG_ROUTE11_NORTH_BEEDRILLITE);
            FlagClear(FLAG_ROUTE20CAVE_AGGRONITE);
            FlagClear(FLAG_ROUTE13_CAMERUPTITE);
            FlagClear(FLAG_ROUTE19_ALTARIANITE);
            FlagClear(FLAG_ROUTE16_AUDINITE);
        }

        // Only restore Gyaradosite/Gengarite when Pluto HQ is completed
        if (VarGet(VAR_MAP_SCENE_PLUTO_HQ_EVENTS) >= 4) // Pluto HQ complete
            FlagClear(FLAG_HIDE_PLUTO_HQ_GYARADOSITE_OR_GENGARITE);
        
        // Held Items & Key Items
        FlagClear(FLAG_HIDE_ROUTE_7_STICK_OR_SACHET);
        FlagClear(FLAG_HIDE_ROUTE11_NORTH_REAPER_CLOTH_OR_DUBIOUS_DISC);
        FlagClear(FLAG_HIDE_DAIMYN_FACTORY_RUSTED_DATA_OR_DRIVES);
        FlagClear(FLAG_HIDE_UTEYAN_RUINS_RED_ORB_OR_PRISON_BOTTLE);
        FlagClear(FLAG_HIDE_UTEYAN_RUINS_BLUE_ORB_OR_REVEAL_GLASS);

        // Trades
        FlagClear(FLAG_DID_COSMO_OR_TOMMY_TRADE);
        FlagClear(FLAG_DID_STARTER_BASED_TRADE);
        FlagClear(FLAG_DID_BORIS_OR_TINA_TRADE);

        // Restore legendaries
        FlagClear(FLAG_HIDE_SHAYMIN); // Xerneas in divergent
        FlagClear(FLAG_HIDE_KYOGRE); // Lugia in divergent
        FlagClear(FLAG_HIDE_GROUDON); // Hoopa in divergent
        FlagClear(FLAG_HIDE_VOLCANION); // Heatran in divergent
        FlagClear(FLAG_HIDE_GLASTRIER); // Spectrier in divergent
        FlagClear(FLAG_HIDE_DAIMYN_FACTORY_MELTAN); // Genesect in divergent
        FlagClear(FLAG_CAUGHT_DARKRAI); // n/a in standard (slot is Melmetal)

        if (FlagGet(FLAG_COMPLETED_CARNELIDGE_VOLCANO_STORY))
            FlagClear(FLAG_HIDE_JIRACHI_ON_CARNELIDGE_VOLCANO_ON_BY_DEFAULT); // Jirachi in both
    }

    SetPokemonCryStereo(gSaveBlock2->optionsSound);
    FREE_AND_SET_NULL(sOptionMenuPtr);    
    DestroyTask(taskId);  
}

void CB2_OptionMenu(void)
{  
    u8 i, state;
    state = sOptionMenuPtr->state;    
    switch (state)
    {
    case 0:
        OptionMenu_InitCallbacks();
        break;
    case 1:
        InitOptionMenuBg();
        break;
    case 2:
        OptionMenu_ResetSpriteData();
        break;
    case 3:
        if (LoadOptionMenuPalette() != TRUE)
            return;
        break;
    case 4:
        PrintOptionMenuHeader();
        break;
    case 5:
        DrawOptionMenuBg();
        break;
    case 6:
        LoadOptionMenuItemNames();
        break;
    case 7:
        for (i = 0; i < MENUITEM_COUNT; i++)
            BufferOptionMenuString(i);
        break;
    case 8:
        UpdateSettingSelectionDisplay(sOptionMenuPtr->cursorPos);
        break;
    case 9:
        OptionMenu_PickSwitchCancel();
        break;
    default:
        SetOptionMenuTask();
		break;
    }
    sOptionMenuPtr->state++;
}

static const u8 sOptionMenuPickSwitchCancelTextColor[] = {TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GREY};
static const u8 sOptionMenuTextColor[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED};

void BufferOptionMenuString(u8 selection)
{
    u8 str[20];
    u8 buf[12];
    u8 dst[3];
    u8 x, y, page;
    const u8 *const *choices;

    page = sOptionMenuPtr->page;
    if (IsPageRowHidden(page, selection))
        return;

    memcpy(dst, sOptionMenuTextColor, 3);
    x = 0x82;
    y = ((GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT) - 1) * GetPageVisualRow(page, selection)) + 2;
    FillWindowPixelRect(1, 1, x, y, 0x46, GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT));

    if (page == 0 && selection == MENUITEM_FRAMETYPE)
    {
        StringCopy(str, gText_FrameType);
        ConvertIntToDecimalStringN(buf, sOptionMenuPtr->option[selection] + 1, 1, 2);
        StringAppendN(str, buf, 3);
        AddTextPrinterParameterized3(1, 2, x, y, dst, -1, str);
    }
    else
    {
        choices = GetPageItemChoices(page)[selection];
        if (choices != NULL) // Cancel has no value to show
            AddTextPrinterParameterized3(1, 2, x, y, dst, -1, choices[GetPageOptions(page)[selection]]);
    }

    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_BOTH);
}

u8 OptionMenu_ProcessInput(void)
{
    u8 page = sOptionMenuPtr->page;
    u16* options = GetPageOptions(page);
    const u16* counts = GetPageItemCounts(page);
    u8 cursorPos = sOptionMenuPtr->cursorPos;
    u8 lastItem = GetPageItemCount(page) - 1; // The cancel row

    if (JOY_REPT(DPAD_RIGHT))
    {
        if (counts[cursorPos] == 0) // Cancel has nothing to cycle through
            return 0;

        if (options[cursorPos] == counts[cursorPos] - 1)
            options[cursorPos] = 0;
        else
            options[cursorPos]++;

        return (page == 0 && cursorPos == MENUITEM_FRAMETYPE) ? 2 : 4;
    }
    else if (JOY_REPT(DPAD_LEFT))
    {
        if (counts[cursorPos] == 0)
            return 0;

        if (options[cursorPos] == 0)
            options[cursorPos] = counts[cursorPos] - 1;
        else
            options[cursorPos]--;

        return (page == 0 && cursorPos == MENUITEM_FRAMETYPE) ? 2 : 4;
    }
    else if (JOY_REPT(DPAD_UP))
    {
        if (cursorPos == 0)
            sOptionMenuPtr->cursorPos = lastItem;
        else
        {
            sOptionMenuPtr->cursorPos--;
            if (IsPageRowHidden(page, sOptionMenuPtr->cursorPos))
                sOptionMenuPtr->cursorPos--;
        }
        return 3;
    }
    else if (JOY_REPT(DPAD_DOWN))
    {
        if (cursorPos == lastItem)
            sOptionMenuPtr->cursorPos = 0;
        else
        {
            sOptionMenuPtr->cursorPos++;
            if (IsPageRowHidden(page, sOptionMenuPtr->cursorPos))
                sOptionMenuPtr->cursorPos++;
        }
        return 3;
    }
    else if (JOY_NEW(R_BUTTON))
    {
        sOptionMenuPtr->page = (page + 1) % OPTION_MENU_PAGE_COUNT;
        PlaySE(SE_SELECT);
        return 5;
    }
    else if (JOY_NEW(L_BUTTON))
    {
        sOptionMenuPtr->page = (page + OPTION_MENU_PAGE_COUNT - 1) % OPTION_MENU_PAGE_COUNT;
        PlaySE(SE_SELECT);
        return 5;
    }
    else if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
extern const u16 sOptionMenuPalette[];
bool8 LoadOptionMenuPalette(void)
{
    switch (sOptionMenuPtr->loadPaletteState)
    {
    case 0:
        LoadBgTiles(1, GetUserFrameGraphicsInfo(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->tiles, 0x120, 0x1AA);
        break;
    case 1:
        LoadPalette(GetUserFrameGraphicsInfo(sOptionMenuPtr->option[MENUITEM_FRAMETYPE])->palette, 0x20, 0x20);
        break;
    case 2:
        LoadPalette(sOptionMenuPalette, 0x10, 0x20);
        LoadPalette(stdpal_get(2), 0xF0, 0x20);
        break;
    case 3:
        DrawWindowBorderWithStdpal3(1, 0x1B3, 0x30);
        break;
    default:
        return TRUE;
    }
    sOptionMenuPtr->loadPaletteState++;
    return FALSE;
}
void LoadOptionMenuItemNames(void)
{
    u8 i, row, page;
    const u8 *const *names;

    page = sOptionMenuPtr->page;
    names = GetPageItemNames(page);

    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    for (i = 0, row = 0; i < GetPageItemCount(page); i++)
    {
        if (IsPageRowHidden(page, i))
            continue;
        AddTextPrinterParameterized(WIN_OPTIONS, 2, names[i], 8, (u8)((row * (GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT))) + 2) - row, TEXT_SPEED_FF, NULL);
        row++;
    }
}

extern const u8 gText_PickSwitchCancel_Page1[];
extern const u8 gText_PickSwitchCancel_Page2[];
extern const u8 gText_PickSwitchCancel_Page3[];

static const u8 *const sPickSwitchCancelTexts[OPTION_MENU_PAGE_COUNT] =
{
    gText_PickSwitchCancel_Page1,
    gText_PickSwitchCancel_Page2,
    gText_PickSwitchCancel_Page3,
};

void OptionMenu_PickSwitchCancel(void)
{
    s32 x;
    const u8 *text = sPickSwitchCancelTexts[sOptionMenuPtr->page];

    x = 0xE4 - GetStringWidth(0, text, 0);
    FillWindowPixelBuffer(2, PIXEL_FILL(15));
    AddTextPrinterParameterized3(2, 0, x, 0, sOptionMenuPickSwitchCancelTextColor, 0, text);
    PutWindowTilemap(2);
    CopyWindowToVram(2, COPYWIN_BOTH);
}