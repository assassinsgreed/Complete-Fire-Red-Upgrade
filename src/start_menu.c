#include "defines.h"
#include "../include/link.h"
#include "../include/menu.h"
#include "../include/menu_helpers.h"
#include "../include/new_menu_helpers.h"
#include "../include/rtc.h"
#include "../include/safari_zone.h"
#include "../include/script.h"
#include "../include/start_menu.h"
#include "../include/constants/flags.h"
#include "../include/constants/songs.h"
#include "../include/field_weather.h"

#include "../include/new/dexnav.h"
#include "../include/string_util.h"
#include "../include/new/dns.h"
#include "../include/item_menu.h" // For auto-sort
#include "../include/new/item.h" // For auto-sort

#ifndef UNBOUND
/*
start_menu.c
	Functions to redo how the start menu is generated, and
	associated functions such as safari steps/ball count.
*/

enum
{
	STARTMENU_POKEDEX,
	STARTMENU_POKEMON,
	STARTMENU_BAG,
	STARTMENU_PLAYER,
	STARTMENU_SAVE,
	STARTMENU_OPTION,
	STARTMENU_EXIT,
	STARTMENU_RETIRE_SAFARI,
	STARTMENU_PLAYER_LINK,
	STARTMENU_DEXNAV,
	STARTMENU_POCKETPC,
	STARTMENU_POKEVIAL,
	STARTMENU_INFINITE_REPEL,
	STARTMENU_EXIT_RIGHT,
	STARTMENU_EXIT_LEFT,
	MAX_STARTMENU_ITEMS
};

enum STARTMENU_TOOLS
{
	START_MENU_NORMAL,
	START_MENU_TOOLS,
};

extern const u8 gText_MenuPokedex[];
extern const u8 gText_MenuPokemon[];
extern const u8 gText_MenuPlayer[];
extern const u8 gText_MenuSave[];
extern const u8 gText_MenuOption[];
extern const u8 gText_MenuExit[];
extern const u8 gText_MenuExitRight[];
extern const u8 gText_MenuExitLeft[];
extern const u8 gText_MenuRetire[];
extern const u8 gText_MenuDexNav[];
extern const u8 gText_MenuPocketPC[];
extern const u8 gText_MenuPokeVial[];
extern const u8 gText_MenuInfiniteRepel[];
extern const u8 gText_MenuBag[];
extern const u8 gText_MenuCube[];
extern const u8 gText_Time[];
#ifdef UNBOUND
#define gText_MenuBag gText_MenuCube
#endif

extern const u8 gText_PokedexDescription[];
extern const u8 gText_PokemonDescription[];
extern const u8 gText_BagDescription[];
extern const u8 gText_PlayerDescription[];
extern const u8 gText_SaveDescription[];
extern const u8 gText_OptionDescription[];
extern const u8 gText_ExitDescription[];
extern const u8 gText_RetireDescription[];
extern const u8 gText_PlayerDescription[];
extern const u8 gText_DexNavDescription[];
extern const u8 gText_PocketPCDescription[];
extern const u8 gText_PokeVialDescription[];
extern const u8 gText_InfiniteRepelDescription[];

extern bool8 (*sStartMenuCallback)(void);
extern u8 sStartMenuCursorPos;
extern u8 sNumStartMenuItems;
extern u8 sStartMenuOrder[];
extern s8 sDrawStartMenuState[2];
extern u8 sStartMenuOpen;

// Timebox
extern u8 sTimeWindowId;
void DrawTime(void);
static void UpdateTimeText(void);
static void RemoveTimeBox(void);

//Vanilla functions:
void __attribute__((long_call)) SetUpStartMenu_Link(void);
void __attribute__((long_call)) SetUpStartMenu_UnionRoom(void);
void __attribute__((long_call)) DestroyHelpMessageWindow_(void);
void __attribute__((long_call)) HideStartMenu(void);
bool8 __attribute__((long_call)) StartMenuPokedexCallback(void);
bool8 __attribute__((long_call)) StartMenuPokemonCallback(void);
bool8 __attribute__((long_call)) StartMenuBagCallback(void);
bool8 __attribute__((long_call)) StartMenuPlayerCallback(void);
bool8 __attribute__((long_call)) StartMenuSaveCallback(void);
bool8 __attribute__((long_call)) StartMenuOptionCallback(void);
bool8 __attribute__((long_call)) StartMenuExitCallback(void);
bool8 __attribute__((long_call)) StartMenuSafariZoneRetireCallback(void);
bool8 __attribute__((long_call)) StartMenuLinkModePlayerCallback(void);
bool8 __attribute__((long_call)) StartMenuQuestLogCallback(void);
void __attribute__((long_call)) AppendToStartMenuItems(u8 action);
void __attribute__((long_call)) DestroySafariZoneStatsWindow(void);
s8 __attribute__((long_call)) PrintStartMenuItems(s8* cursor_p, u8 nitems);
void __attribute__((long_call)) StartMenu_FadeScreenIfLeavingOverworld(void);
bool8 __attribute__((long_call)) StartMenuPokedexSanityCheck(void);
void __attribute__((long_call)) CloseStartMenu(void);
void __attribute__((long_call)) PrintTextOnHelpMessageWindow(const u8 * text, u8 mode);

//Exported functions:
void BuildStartMenuActions(void);

//This file's functions:
static void SetUpStartMenu_NormalField(void);
static void SetUpStartMenu_SafariZone(void);
static void BuildPokeToolsMenu(void);
static bool8 CloseAndReloadStartMenu(void);
static bool8 ReloadStartMenu(void);
static bool8 ReloadStartMenuItems(void);
bool8 StartMenuPocketPCCallback(void);
bool8 StartMenuPokeVialCallback(void);
bool8 StartMenuInfiniteRepelCallback(void);

const struct MenuAction sStartMenuActionTable[] =
{
	[STARTMENU_POKEDEX] = {gText_MenuPokedex, {.u8_void = StartMenuPokedexCallback}},
	[STARTMENU_POKEMON] = {gText_MenuPokemon, {.u8_void = StartMenuPokemonCallback}},
	[STARTMENU_BAG] = {gText_MenuBag, {.u8_void = StartMenuBagCallback}},
	[STARTMENU_PLAYER] = {gText_MenuPlayer, {.u8_void = StartMenuPlayerCallback}},
	[STARTMENU_SAVE] = {gText_MenuSave, {.u8_void = StartMenuSaveCallback}},
	[STARTMENU_OPTION] = {gText_MenuOption, {.u8_void = StartMenuOptionCallback}},
	[STARTMENU_EXIT] = {gText_MenuExit, {.u8_void = StartMenuExitCallback}},
	[STARTMENU_RETIRE_SAFARI] = {gText_MenuRetire, {.u8_void = StartMenuSafariZoneRetireCallback}},
	[STARTMENU_PLAYER_LINK] = {gText_MenuPlayer, {.u8_void = StartMenuLinkModePlayerCallback}},
	[STARTMENU_DEXNAV] = {gText_MenuDexNav, {.u8_void = StartMenuDexNavCallback}},
	[STARTMENU_POCKETPC] = {gText_MenuPocketPC, {.u8_void = StartMenuPocketPCCallback}},
	[STARTMENU_POKEVIAL] = {gText_MenuPokeVial, {.u8_void = StartMenuPokeVialCallback}},
	[STARTMENU_INFINITE_REPEL] = {gText_MenuInfiniteRepel, {.u8_void = StartMenuInfiniteRepelCallback}},
	[STARTMENU_EXIT_RIGHT] = {gText_MenuExitRight, {.u8_void = StartMenuExitCallback}},
	[STARTMENU_EXIT_LEFT] = {gText_MenuExitLeft, {.u8_void = StartMenuExitCallback}},
};

const u8* const sStartMenuDescPointers[] =
{
	gText_PokedexDescription,
	gText_PokemonDescription,
	gText_BagDescription,
	gText_PlayerDescription,
	gText_SaveDescription,
	gText_OptionDescription,
	gText_ExitDescription,
	gText_RetireDescription,
	gText_PlayerDescription,
	gText_DexNavDescription,
	gText_PocketPCDescription,
	gText_PokeVialDescription,
	gText_InfiniteRepelDescription,
	// NULL,
	gText_ExitDescription,
	gText_ExitDescription,
};

static const struct WindowTemplate sTimeBoxWindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 14,
	.height = 2,
	.paletteNum = 15,
	.baseBlock = 0x008
};

static bool8 CanSetUpSecondaryStartMenu(void)
{
	#ifdef FLAG_SYS_DEXNAV
	if (FlagGet(FLAG_SYS_DEXNAV) && FlagGet(FLAG_SYS_POKEDEX_GET))
		return TRUE;
	#endif

	if (FlagGet(0x828)) // Pokemon menu enabled
	{
		#ifdef FLAG_SYS_POCKETPC
		if (FlagGet(FLAG_SYS_POCKETPC))
			return TRUE;
		#endif

		#ifdef FLAG_SYS_POKE_VIAL
		if (FlagGet(FLAG_SYS_POKE_VIAL))
			return TRUE;
		#endif

		#ifdef FLAG_SYS_INFINITE_REPEL
		if (FlagGet(FLAG_SYS_INFINITE_REPEL))
			return TRUE;
		#endif
	}

	#ifdef FLAG_SYS_QUEST_LOG
	if (FlagGet(FLAG_SYS_QUEST_LOG))
		return TRUE;
	#endif

	return FALSE;
}

static void SetUpStartMenu_NormalField(void)
{
	if (FlagGet(FLAG_SYS_POKEDEX_GET))
		AppendToStartMenuItems(STARTMENU_POKEDEX);

	if (FlagGet(FLAG_SYS_POKEMON_GET))
		AppendToStartMenuItems(STARTMENU_POKEMON);

	#ifdef FLAG_SYS_BAG_HIDE
		if (!FlagGet(FLAG_SYS_BAG_HIDE))
	#endif
			AppendToStartMenuItems(STARTMENU_BAG);

	#ifdef FLAG_SYS_PLAYER_HIDE
		if (!FlagGet(FLAG_SYS_PLAYER_HIDE))
	#endif
			AppendToStartMenuItems(STARTMENU_PLAYER);

	#ifdef FLAG_SYS_SAVE_HIDE
		if (!FlagGet(FLAG_SYS_SAVE_HIDE))
	#endif
			AppendToStartMenuItems(STARTMENU_SAVE);

	//These two are always present
	AppendToStartMenuItems(STARTMENU_OPTION);

	if  (sStartMenuOpen == START_MENU_NORMAL && CanSetUpSecondaryStartMenu())
		AppendToStartMenuItems(STARTMENU_EXIT_RIGHT);
	else
		AppendToStartMenuItems(STARTMENU_EXIT);

	DrawTime();
}

static void SetUpStartMenu_SafariZone(void)
{
	AppendToStartMenuItems(STARTMENU_RETIRE_SAFARI);

	if (FlagGet(FLAG_SYS_POKEDEX_GET))
		AppendToStartMenuItems(STARTMENU_POKEDEX);

	#ifdef FLAG_SYS_POKEMON_GET
	if (FlagGet(FLAG_SYS_POKEMON_GET))
	#endif
		AppendToStartMenuItems(STARTMENU_POKEMON);

	#ifdef FLAG_SYS_BAG_GET
		if (FlagGet(FLAG_SYS_BAG_GET))
	#endif
			AppendToStartMenuItems(STARTMENU_BAG);

	#ifdef FLAG_SYS_PLAYER_GET
		if (FlagGet(FLAG_SYS_PLAYER_GET))
	#endif
			AppendToStartMenuItems(STARTMENU_PLAYER);

	AppendToStartMenuItems(STARTMENU_OPTION);

	if  (sStartMenuOpen == START_MENU_NORMAL && CanSetUpSecondaryStartMenu())
		AppendToStartMenuItems(STARTMENU_EXIT_RIGHT);
	else
		AppendToStartMenuItems(STARTMENU_EXIT);
}

static void BuildPokeToolsMenu(void)
{
	sNumStartMenuItems = 0;

	#ifdef FLAG_SYS_DEXNAV
	if (FlagGet(FLAG_SYS_DEXNAV) && FlagGet(FLAG_SYS_POKEDEX_GET))
	#endif
		AppendToStartMenuItems(STARTMENU_DEXNAV);

	if (FlagGet(0x828)) // Pokemon menu enabled
	{
		#ifdef FLAG_SYS_POCKETPC
		if (FlagGet(FLAG_SYS_POCKETPC))
			AppendToStartMenuItems(STARTMENU_POCKETPC);
		#endif

		#ifdef FLAG_SYS_POKE_VIAL
		if (FlagGet(FLAG_SYS_POKE_VIAL))
			AppendToStartMenuItems(STARTMENU_POKEVIAL);
		#endif

		#ifdef FLAG_SYS_INFINITE_REPEL
		if (FlagGet(FLAG_SYS_INFINITE_REPEL))
			AppendToStartMenuItems(STARTMENU_INFINITE_REPEL);
		#endif

		#ifdef FLAG_SYS_QUEST_LOG
		if (FlagGet(FLAG_SYS_QUEST_LOG))
			AppendToStartMenuItems(STARTMENU_QUEST_LOG);
		#endif	
	}

	AppendToStartMenuItems(STARTMENU_EXIT_LEFT);
	DrawTime();
}

void SetUpStartMenu(void)
{
	sNumStartMenuItems = 0;

	if (IsUpdateLinkStateCBActive())
		SetUpStartMenu_Link();
	else if (InUnionRoom())
		SetUpStartMenu_UnionRoom();
	else if (GetSafariZoneFlag())
		SetUpStartMenu_SafariZone();
	else if (sStartMenuOpen == START_MENU_TOOLS)
		BuildPokeToolsMenu();
	else
		SetUpStartMenu_NormalField();
}

bool8 StartCB_HandleInput(void)
{
	ForceClockUpdate(); //To help with the clock in the start menu routine

	if (!FlagGet(FLAG_SYS_SAFARI_MODE) && sTimeWindowId != 0xFF)
		UpdateTimeText();

	if (JOY_NEW(DPAD_UP))
	{
		PlaySE(SE_SELECT);
		sStartMenuCursorPos = Menu_MoveCursor(-1);
		#ifndef UNBOUND
		if (!MenuHelpers_LinkSomething() && !InUnionRoom())
		{
			PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
		}
		#endif
	}
	else if (JOY_NEW(DPAD_DOWN))
	{
		PlaySE(SE_SELECT);
		sStartMenuCursorPos = Menu_MoveCursor(+1);
		#ifndef UNBOUND
		if (!MenuHelpers_LinkSomething() && !InUnionRoom())
		{
			PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
		}
		#endif
	}
	else if (JOY_NEW(DPAD_RIGHT))
	{
		if (sStartMenuOpen == START_MENU_NORMAL && CanSetUpSecondaryStartMenu())
		{
			PlaySE(SE_SELECT);
			sStartMenuCursorPos = 0; //Reset cursor position
			sStartMenuOpen = START_MENU_TOOLS;
			sStartMenuCallback = CloseAndReloadStartMenu;
		}
	}
	else if (JOY_NEW(DPAD_LEFT))
	{
		if (sStartMenuOpen == START_MENU_TOOLS)
		{
			PlaySE(SE_SELECT);
			sStartMenuCursorPos = 0; //Reset cursor position
			sStartMenuOpen = START_MENU_NORMAL;
			sStartMenuCallback = CloseAndReloadStartMenu;
		}
	}
	else if (JOY_NEW(A_BUTTON))
	{
		PlaySE(SE_SELECT);
		if (!StartMenuPokedexSanityCheck())
			return FALSE;
		sStartMenuCallback = sStartMenuActionTable[sStartMenuOrder[sStartMenuCursorPos]].func.u8_void;

		if (sStartMenuCursorPos==STARTMENU_EXIT ||
			sStartMenuCallback == StartMenuPocketPCCallback ||
		    sStartMenuCallback == StartMenuPokeVialCallback ||
		    sStartMenuCallback == StartMenuInfiniteRepelCallback
		)
		    RemoveTimeBox();

		// Do not fade the screen when using certain tools
		if(sStartMenuCallback != StartMenuPocketPCCallback &&
		   sStartMenuCallback != StartMenuPokeVialCallback &&
		   sStartMenuCallback != StartMenuInfiniteRepelCallback)
		{
			StartMenu_FadeScreenIfLeavingOverworld();    
		}
		return FALSE;
	}
	else if (JOY_NEW(B_BUTTON | START_BUTTON))
	{
		RemoveTimeBox();
		DestroySafariZoneStatsWindow();
		DestroyHelpMessageWindow_();
		CloseStartMenu();
		return TRUE;
	}

	return FALSE;
}

static bool8 CloseAndReloadStartMenu(void)
{
	ClearStdWindowAndFrame(GetStartMenuWindowId(), TRUE);
	RemoveStartMenuWindow();
	sStartMenuCallback = ReloadStartMenu;
	return FALSE;
}

static bool8 ReloadStartMenu(void)
{
	SetUpStartMenu();
	DrawStdWindowFrame(CreateStartMenuWindow(sNumStartMenuItems), FALSE);
	CopyWindowToVram(GetStartMenuWindowId(), 1);
	sDrawStartMenuState[1] = 0;
	sStartMenuCallback = ReloadStartMenuItems;
	return FALSE;
}

static bool8 ReloadStartMenuItems(void)
{
	if (PrintStartMenuItems(&sDrawStartMenuState[1], 2))
	{
		sStartMenuCursorPos = Menu_InitCursor(GetStartMenuWindowId(), 2, 0, 0, 15, sNumStartMenuItems, sStartMenuCursorPos);
		#ifndef UNBOUND
		if (!MenuHelpers_LinkSomething() && InUnionRoom() != TRUE)
		{
			DrawHelpMessageWindowWithText(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]]);
		}
		#endif
		CopyWindowToVram(GetStartMenuWindowId(), 1);
		sStartMenuCallback = StartCB_HandleInput;
	}

	return FALSE;
}

extern u8 EventScript_Common_PocketPC[];
extern u8 EventScript_Common_PokeVial[];
extern u8 EventScript_Common_InfiniteRepel[];

static bool8 StartMenuCommonCallback(const u8* script)
{
	if (!gPaletteFade->active)
	{
		PlayRainStoppingSoundEffect();
		DestroySafariZoneStatsWindow();
		ClearStdWindowAndFrame(GetStartMenuWindowId(), TRUE);
		RemoveStartMenuWindow();
		ScriptContext1_SetupScript(script);
		return TRUE;
	}
	return FALSE;
}

bool8 StartMenuPocketPCCallback(void)
{
	return StartMenuCommonCallback(EventScript_Common_PocketPC);
}

bool8 StartMenuPokeVialCallback(void)
{
	return StartMenuCommonCallback(EventScript_Common_PokeVial);
}

bool8 StartMenuInfiniteRepelCallback(void)
{
	return StartMenuCommonCallback(EventScript_Common_InfiniteRepel);
}

// Timebox
void DrawTime(void)
{
	sTimeWindowId = AddWindow(&sTimeBoxWindowTemplate);
	
	if (sTimeWindowId != 0xFF)
	{
		DrawStdWindowFrame(sTimeWindowId, FALSE);
		PutWindowTilemap(sTimeWindowId);
		FillWindowPixelBuffer(sTimeWindowId, PIXEL_FILL(1));
	}

	//Print Text
	UpdateTimeText();
}

extern u8 gText_StartMenu_TimeBase[];
extern u8 gText_StartMenu_TimeBase_12Hr[];
extern u8 gText_StartMenu_AM[];
extern u8 gText_StartMenu_PM[];
extern u8 gText_StartMenu_Morning[];
extern u8 gText_StartMenu_Day[];
extern u8 gText_StartMenu_Evening[];
extern u8 gText_StartMenu_Night[];
extern u8 gText_StartMenu_RedText[];
extern u8 gText_StartMenu_NormalText[];
extern u8 gText_StartMenu_Sunday[];
extern u8 gText_StartMenu_Monday[];
extern u8 gText_StartMenu_Tuesday[];
extern u8 gText_StartMenu_Wednesday[];
extern u8 gText_StartMenu_Thursday[];
extern u8 gText_StartMenu_Friday[];
extern u8 gText_StartMenu_Saturday[];
extern u8 gText_StartMenu_Error[];


static u8* sDayNames[] =
{
    gText_StartMenu_Sunday,
    gText_StartMenu_Monday,
    gText_StartMenu_Tuesday,
    gText_StartMenu_Wednesday,
    gText_StartMenu_Thursday,
    gText_StartMenu_Friday,
    gText_StartMenu_Saturday,
};

static void UpdateTimeText()
{
	//Prepare string: "DOW. HH:MM AM (TimeOfDay)"
	const u8* amPMString = (gClock.hour >= 12) ? gText_StartMenu_PM : gText_StartMenu_AM;
	const u8* timeOfDayString = gText_StartMenu_Day;
	if (IsMorning())
		timeOfDayString = gText_StartMenu_Morning;
	else if (IsEvening())
		timeOfDayString = gText_StartMenu_Evening;
	else if (IsNightTime())
		timeOfDayString = gText_StartMenu_Night;
	StringCopy(gStringVar3, amPMString);
	StringAppend(gStringVar3, timeOfDayString);

	// HH:MM
	ConvertIntToDecimalStringN(gStringVar1, (gClock.hour == 0) ? 12 : (gClock.hour > 12) ? gClock.hour - 12 : gClock.hour, STR_CONV_MODE_RIGHT_ALIGN, 2); //Hour - 12hr format
	ConvertIntToDecimalStringN(gStringVar2, gClock.minute, STR_CONV_MODE_LEADING_ZEROS, 2); //Minute
	StringCopy(gStringVarC, (gClock.dayOfWeek >= 7) ? gText_StartMenu_Error : sDayNames[gClock.dayOfWeek]); //Day of Week
	StringExpandPlaceholders(gStringVar4, gText_StartMenu_TimeBase_12Hr);

	AddTextPrinterParameterized(sTimeWindowId, 2, gStringVar4, 4, 3, 0xFF, NULL);
	CopyWindowToVram(sTimeWindowId, COPYWIN_GFX);
}

static void RemoveTimeBox(void)
{
	if (sTimeWindowId != 0xFF)
	{
		ClearStdWindowAndFrameToTransparent(sTimeWindowId, FALSE);
		CopyWindowToVram(sTimeWindowId, COPYWIN_GFX);
		RemoveWindow(sTimeWindowId);
	}
}

enum
{
	SORT_ALPHABETICALLY,
	SORT_BY_TYPE,
	SORT_BY_LEAST,
	SORT_BY_MOST,
	SORT_BY_AMOUNT,
};
bool8 StartMenuBagCallback(void)
{
    if (!gPaletteFade->active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_BagMenuFromStartMenu);
		if(VarGet(VAR_AUTO_SORT_BAG) != 0)
		{
			switch(VarGet(VAR_AUTO_SORT_BAG))
			{
				case 1:
					SortItemsInBag(POCKET_ITEMS - 1, SORT_ALPHABETICALLY);
					SortItemsInBag(POCKET_KEYITEMS - 1, SORT_ALPHABETICALLY);
					SortItemsInBag(POCKET_POKEBALLS - 1, SORT_ALPHABETICALLY);
					break;
				case 2:
					SortItemsInBag(POCKET_ITEMS - 1, SORT_BY_TYPE);
					break;
				case 3:
					SortItemsInBag(POCKET_ITEMS - 1, SORT_BY_AMOUNT);
					SortItemsInBag(POCKET_POKEBALLS - 1, SORT_BY_AMOUNT);
					break;
			}
		}
        return TRUE;
    }
    return FALSE;
}
#endif
