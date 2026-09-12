#include "defines.h"
#include "../include/money.h"
#include "../include/new/item.h"
#include "../include/new/new_game_plus.h"
#include "../include/constants/flags.h"
#include "../include/constants/items.h"
#include "../include/constants/vars.h"
#include "../include/constants/songs.h"
#include "../include/palette.h"
#include "../include/event_data.h"
#include "../include/gpu_regs.h"
#include "../include/menu.h"
#include "../include/sound.h"
#include "../include/sprite.h"
#include "../include/task.h"
#include "../include/text.h"
#include "../include/window.h"

/*
new_game_plus.c
	New Game Plus: the main menu gate, and the capture/restore pair that carries a finished
	save's boxes, Pokedex, bag and money into a fresh one.

	Capture runs at the entry to new-game init, which is the only moment every source
	region is simultaneously valid. Restore runs at that same function's conclusion, after
	all four of the clears that between them cover the boxes have run.
*/

//Box contents, names and wallpapers each live in several disjointed RAM regions.
//src/pokemon_storage_system.c already maps all three, so borrow its tables instead of
//naming those addresses a second time.
extern struct CompressedPokemon* const sPokemonBoxPtrs[TOTAL_BOXES_COUNT];
extern u8 (* const sPokemonBoxNamePtrs[TOTAL_BOXES_COUNT])[NGP_BOX_NAME_BYTES];
extern u8* const sPokemonBoxWallpaperPtrs[TOTAL_BOXES_COUNT];

extern const struct BagPockets sBagPocketArrangement;

//The 22 modifier unlock flags occupy one contiguous run, so they are handled by range.
#define NGP_FIRST_UNLOCK_FLAG FLAG_GAMEMODIFIER_RANDOMIZERSPECIES_UNLOCKED
#define NGP_LAST_UNLOCK_FLAG  FLAG_GAMEMODIFIER_REPEATED_MEGA_EVOLUTION_UNLOCKED
#define NGP_UNLOCK_FLAG_COUNT (NGP_LAST_UNLOCK_FLAG - NGP_FIRST_UNLOCK_FLAG + 1)

//The active toggles are not contiguous. Reuse the frontier's list rather than duplicating it;
//src/frontier_challenge.c asserts NGP_ACTIVE_FLAG_COUNT still matches its length.
extern const u16 gFrontierOverriddenModifierFlags[];

//The backup packs both the unlock flags and toggles into one bit field: the unlock flags first, then the toggles.
#define NGP_MODIFIER_FLAG_COUNT (NGP_UNLOCK_FLAG_COUNT + NGP_ACTIVE_FLAG_COUNT)

//The options the player can set outside SaveBlock2, all written by the new Options Menu code.
static const u16 sNewGamePlusOptionVars[] =
{
	VAR_AUTO_SORT_BAG,
	VAR_DIFFICULTY_SETTING,
	VAR_LEVEL_CAPS,
	VAR_OVERWORLD_SPEED,
	VAR_BATTLE_SPEED,
};

//The first two are derived from two of the vars above, but only when the option menu is
//closed, so carrying the vars alone would leave them stale for the whole run.
static const u16 sNewGamePlusOptionFlags[] =
{
	FLAG_HARD_MODE,
	FLAG_HARD_LEVEL_CAP,
	FLAG_SKIP_CUTSCENES,
	FLAG_DONT_OFFER_NICKNAMES_BATTLE,
	FLAG_OPTIONS_LAST_USED_BALL,
	FLAG_OPTIONS_SHORT_NURSE_HEAL,
	FLAG_DIVERGENT_WILD_ENCOUNTERS,
	FLAG_DIVERGENT_WILD_ENCOUNTERS_OPTION_SHOWN,
};

_Static_assert(ARRAY_COUNT(sNewGamePlusOptionVars) == NGP_OPTION_VAR_COUNT, "NGP_OPTION_VAR_COUNT is stale");
_Static_assert(ARRAY_COUNT(sNewGamePlusOptionFlags) == NGP_OPTION_FLAG_COUNT, "NGP_OPTION_FLAG_COUNT is stale");

_Static_assert(NGP_MODIFIER_FLAG_COUNT <= NGP_MODIFIER_FLAG_WORDS * 32, "modifierFlags cannot hold this many flags");
_Static_assert(sizeof(gSaveBlock1->dexSeenFlags) == NGP_DEX_FLAG_BYTES, "NGP_DEX_FLAG_BYTES is stale");
_Static_assert(sizeof(gSaveBlock1->dexCaughtFlags) == NGP_DEX_FLAG_BYTES, "NGP_DEX_FLAG_BYTES is stale");
//The options are copied as a byte run, so they have to stay a byte run that stops short of the Pokedex.
_Static_assert(offsetof(struct SaveBlock2, pokedex) - offsetof(struct SaveBlock2, optionsButtonMode) >= NGP_OPTION_BYTES, "the options no longer fit before the Pokedex");

void NewGamePlusBegin(void)
{
	sNewGamePlusPending = TRUE;
}

//Required, not a nicety: sNewGamePlusPending is uninitialised at boot, so an ordinary New Game must clear it or stale RAM could trigger a spurious transfer.
void NewGamePlusClearPending(void)
{
	sNewGamePlusPending = FALSE;
}

static u16 GetModifierFlagByIndex(u32 i)
{
	if (i < NGP_UNLOCK_FLAG_COUNT)
		return NGP_FIRST_UNLOCK_FLAG + i;

	return gFrontierOverriddenModifierFlags[i - NGP_UNLOCK_FLAG_COUNT];
}

static void CaptureModifierFlags(struct NewGamePlusBackup* backup)
{
	u32 i;

	for (i = 0; i < NGP_MODIFIER_FLAG_WORDS; ++i)
		backup->modifierFlags[i] = 0;

	//1u, not 1: the packed runs reach bit 31 of the first word.
	for (i = 0; i < NGP_MODIFIER_FLAG_COUNT; ++i)
	{
		if (FlagGet(GetModifierFlagByIndex(i)))
			backup->modifierFlags[i / 32] |= 1u << (i % 32);
	}
}

static void RestoreModifierFlags(struct NewGamePlusBackup* backup)
{
	u32 i;

	for (i = 0; i < NGP_MODIFIER_FLAG_COUNT; ++i)
	{
		if (backup->modifierFlags[i / 32] & (1u << (i % 32)))
			FlagSet(GetModifierFlagByIndex(i));
	}
}

static void CaptureBoxes(struct NewGamePlusBackup* backup)
{
	u32 box;

	for (box = 0; box < TOTAL_BOXES_COUNT; ++box)
	{
		Memcpy(&backup->boxes[box * IN_BOX_COUNT], sPokemonBoxPtrs[box], IN_BOX_COUNT * sizeof(struct CompressedPokemon));
		Memcpy(backup->boxNames[box], sPokemonBoxNamePtrs[box], NGP_BOX_NAME_BYTES);
		backup->boxWallpapers[box] = *sPokemonBoxWallpaperPtrs[box];
	}
}

static void RestoreBoxes(struct NewGamePlusBackup* backup)
{
	u32 box;

	for (box = 0; box < TOTAL_BOXES_COUNT; ++box)
	{
		Memcpy(sPokemonBoxPtrs[box], &backup->boxes[box * IN_BOX_COUNT], IN_BOX_COUNT * sizeof(struct CompressedPokemon));
		Memcpy(sPokemonBoxNamePtrs[box], backup->boxNames[box], NGP_BOX_NAME_BYTES);
		*sPokemonBoxWallpaperPtrs[box] = backup->boxWallpapers[box];
	}
}

void NewGamePlusCapture(void)
{
	struct NewGamePlusBackup* backup;
	u32 i;

	sNewGamePlusBackup = NULL;

	if (!sNewGamePlusPending)
		return;

	backup = Malloc(sizeof(struct NewGamePlusBackup));
	if (backup == NULL)
		return; //Transfer is skipped and the run proceeds as a plain New Game

	// Copy all 25 boxes, with their names and wallpapers. The player party is intentionally not copied
	CaptureBoxes(backup);

	// Copy dex seen/caught flags
	Memcpy(backup->dexSeen, gSaveBlock1->dexSeenFlags, sizeof(backup->dexSeen));
	Memcpy(backup->dexCaught, gSaveBlock1->dexCaughtFlags, sizeof(backup->dexCaught));

	// Copy player bag contents, minus key items. Verbatim is safe because bag quantities are plaintext
	Memcpy(backup->bagItems, sBagPocketArrangement.itemRam, sizeof(backup->bagItems));
	Memcpy(backup->bagBalls, sBagPocketArrangement.pokeBallRam, sizeof(backup->bagBalls));
	Memcpy(backup->bagTMHM, sBagPocketArrangement.tmRam, sizeof(backup->bagTMHM));
	Memcpy(backup->bagBerries, sBagPocketArrangement.berryRam, sizeof(backup->bagBerries));

	CaptureModifierFlags(backup);

	// Copy player money
	backup->money = GetMoney(&gSaveBlock1->money);

	// Copy Game Modifier weather/terrain, if it has been set previously
	backup->instantWeather = VarGet(VAR_INSTANT_BATTLE_WEATHER);
	backup->instantTerrain = VarGet(VAR_INSTANT_BATTLE_TERRAIN);

	// Copy Trainer ID, but not name & gender so those can change
	Memcpy(backup->trainerId, gSaveBlock2->playerTrainerId, sizeof(backup->trainerId));

	// Copy player's selected options, from both vanilla Fire Red's options and Amethyst's custom ones.
	Memcpy(backup->options, &gSaveBlock2->optionsButtonMode, sizeof(backup->options));

	for (i = 0; i < NGP_OPTION_VAR_COUNT; ++i)
		backup->optionVars[i] = VarGet(sNewGamePlusOptionVars[i]);

	backup->optionFlags = 0;
	for (i = 0; i < NGP_OPTION_FLAG_COUNT; ++i)
	{
		if (FlagGet(sNewGamePlusOptionFlags[i]))
			backup->optionFlags |= 1 << i;
	}

	sNewGamePlusBackup = backup;
}

void NewGamePlusRestore(void)
{
	struct NewGamePlusBackup* backup = sNewGamePlusBackup;
	u32 currentMoney;
	u32 i;

	sNewGamePlusPending = FALSE;
	sNewGamePlusBackup = NULL;

	if (backup == NULL)
		return;

	RestoreBoxes(backup);

	Memcpy(gSaveBlock1->dexSeenFlags, backup->dexSeen, sizeof(backup->dexSeen));
	Memcpy(gSaveBlock1->dexCaughtFlags, backup->dexCaught, sizeof(backup->dexCaught));

	Memcpy(sBagPocketArrangement.itemRam, backup->bagItems, sizeof(backup->bagItems));
	Memcpy(sBagPocketArrangement.pokeBallRam, backup->bagBalls, sizeof(backup->bagBalls));
	Memcpy(sBagPocketArrangement.tmRam, backup->bagTMHM, sizeof(backup->bagTMHM));
	Memcpy(sBagPocketArrangement.berryRam, backup->bagBerries, sizeof(backup->bagBerries));

	// Both are key items and must be given so their "pouches" are accessible
	AddBagItem(ITEM_TM_CASE, 1);
	AddBagItem(ITEM_BERRY_POUCH, 1);
	FlagSet(FLAG_SYS_GOT_BERRY_POUCH);

	RestoreModifierFlags(backup);

	// Restore money from the copied state, without adding any money normally added from a fresh save
	currentMoney = GetMoney(&gSaveBlock1->money);
	if (currentMoney > 0)
		RemoveMoney(&gSaveBlock1->money, currentMoney);
	AddMoney(&gSaveBlock1->money, backup->money);

	VarSet(VAR_INSTANT_BATTLE_WEATHER, backup->instantWeather);
	VarSet(VAR_INSTANT_BATTLE_TERRAIN, backup->instantTerrain);

	Memcpy(gSaveBlock2->playerTrainerId, backup->trainerId, sizeof(backup->trainerId));

	Memcpy(&gSaveBlock2->optionsButtonMode, backup->options, sizeof(backup->options));

	for (i = 0; i < NGP_OPTION_VAR_COUNT; ++i)
		VarSet(sNewGamePlusOptionVars[i], backup->optionVars[i]);

	for (i = 0; i < NGP_OPTION_FLAG_COUNT; ++i)
	{
		//Cleared as well as set, because a new game starts these at defaults.
		if (backup->optionFlags & (1 << i))
			FlagSet(sNewGamePlusOptionFlags[i]);
		else
			FlagClear(sNewGamePlusOptionFlags[i]);
	}

	FlagSet(FLAG_DISABLE_OBEDIENCE_CHECKS);

	Free(backup);
}

// The base ROM leaves these main menu routines unnamed, so BPRE.ld names them. The first
// draws the frame around a window template, the second blanks it again, and the last is
// what the New Game row goes on to call.
void __attribute__((long_call)) MainMenuDrawMessageFrame(const struct WindowTemplate* template);
void __attribute__((long_call)) MainMenuEraseMessageFrame(const struct WindowTemplate* template);
void __attribute__((long_call)) StartNewGameIntro(void);

extern const u8 gText_MainMenuNewGameOrPlus[];
extern const u8 gText_NewGamePlusConfirm[];
extern const u8 gText_NewGamePlusChoices[];
extern const u8 gText_NewGamePlusStartingNewGame[];
extern const u8 gText_NewGamePlusStartingNewGamePlus[];
extern const u8 gText_NewGamePlusReturning[];

#define NGP_VANILLA_NEW_GAME_LABEL ((const u8*) 0x08415A6E)
#define NGP_MENU_BORDER_TILE    0x1B1
#define NGP_MENU_BORDER_PALETTE 2

// Text colours and window fill the menu uses for every box it draws.
#define NGP_MENU_TEXT_COLOURS ((const u8*) 0x08234688)
#define NGP_MENU_WINDOW_FILL  0xAA

static const u8 sNewGamePlusChoiceColours[3] = {1, 2, 3};

// Both vanilla ways out of the menu zero this, New Game at 0x800CB2E and Continue at 0x800CB48.
#define NGP_MENU_EXIT_BYTE (*((u8*) 0x02037DE0))

// Hand the task back here and the menu redraws itself from scratch, so cancelling has nothing to clean up.
#define NGP_MENU_REBUILD_TASK ((TaskFunc) (0x0800C780 | 1))
#define NGP_STATE(taskId) (gTasks[taskId].data[9])
#define NGP_PROMPT_WINDOW_ID(taskId) (gTasks[taskId].data[10])
#define NGP_CHOICE_WINDOW_ID(taskId) (gTasks[taskId].data[11])
#define NGP_PENDING_EXIT(taskId) (gTasks[taskId].data[12])

enum
{
	NGP_STATE_OPEN_PROMPT,
	NGP_STATE_WAIT_FADE_IN,
	NGP_STATE_READ_PROMPT,
	NGP_STATE_AWAIT_CHOICE,
	NGP_STATE_FADE_TO_NEW_GAME,
	NGP_STATE_FADE_TO_MAIN_MENU,
	NGP_STATE_PRINT_CHOICE_MADE,
	NGP_STATE_AWAIT_DISMISS,
};

enum
{
	NGP_CHOICE_NEW_GAME,
	NGP_CHOICE_NEW_GAME_PLUS,
	NGP_CHOICE_CANCEL,
};

enum
{
	NGP_EXIT_NEW_GAME,
	NGP_EXIT_MAIN_MENU,
};

static const struct WindowTemplate sNewGamePlusScreenClear __attribute__((aligned(4))) =
{
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 30,
	.height = 20,
	.paletteNum = 0,
	.baseBlock = 0,
};

static const struct WindowTemplate sNewGamePlusPromptWindow __attribute__((aligned(4))) =
{
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 15,
	.width = 28,
	.height = 4,
	.paletteNum = 15,
	.baseBlock = 0x200,
};

static const struct WindowTemplate sNewGamePlusChoiceWindow __attribute__((aligned(4))) =
{
	.bg = 0,
	.tilemapLeft = 14,
	.tilemapTop = 6,
	.width = 14,
	.height = 6,
	.paletteNum = NGP_MENU_BORDER_PALETTE,
	.baseBlock = 0x280,
};

// The menu prints its New Game row from this. Once the game is beaten the row doubles as the way into New Game Plus.
const u8* GetMainMenuNewGameLabel(void)
{
	if (FlagGet(FLAG_SYS_GAME_CLEAR))
		return gText_MainMenuNewGameOrPlus;

	return NGP_VANILLA_NEW_GAME_LABEL;
}

static void PrintPrompt(u8 windowId, const u8* str)
{
	FillWindowPixelBuffer(windowId, NGP_MENU_WINDOW_FILL);
	MainMenuDrawMessageFrame(&sNewGamePlusPromptWindow);
	AddTextPrinterParameterized3(windowId, 2, 0, 0, NGP_MENU_TEXT_COLOURS, 2, str);
	PutWindowTilemap(windowId);
	CopyWindowToVram(windowId, 3);
}

static void OpenPrompt(u8 taskId)
{
	u8 windowId = AddWindow(&sNewGamePlusPromptWindow);

	NGP_PROMPT_WINDOW_ID(taskId) = windowId;
	PrintPrompt(windowId, gText_NewGamePlusConfirm);
}

static void OpenChoiceBox(u8 taskId)
{
	u8 windowId = AddWindow(&sNewGamePlusChoiceWindow);

	NGP_CHOICE_WINDOW_ID(taskId) = windowId;
	DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, NGP_MENU_BORDER_TILE, NGP_MENU_BORDER_PALETTE);
	FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
	// Speed -1 prints the whole list at once, the way the menu prints its own rows.
	AddTextPrinterParameterized3(windowId, 2, 8, 2, sNewGamePlusChoiceColours, -1, gText_NewGamePlusChoices);
	Menu_InitCursor(windowId, 2, 0, 2, GetFontAttribute(2, FONTATTR_MAX_LETTER_HEIGHT), 3, NGP_CHOICE_CANCEL);
	PutWindowTilemap(windowId);
	CopyWindowToVram(windowId, 3);
}

// The menu is a screen the prompt borrows rather than replaces, so elements like the party icon need to be cleared.
static void ClearMainMenuScreen(void)
{
	// The menu highlights its selected row by darkening everything window 0 does not cover.
	SetGpuReg(REG_OFFSET_BLDCNT, 0);
	ResetSpriteData();
	MainMenuEraseMessageFrame(&sNewGamePlusScreenClear);
}

// Reads the choice back in the box the question was asked in. The choice box only ever sat
// on bare backdrop, so blanking its rect clears it; that rect overruns into the prompt box
// below it, which is why the reprint has to come second.
static void ShowChoiceMade(u8 taskId, const u8* str)
{
	MainMenuEraseMessageFrame(&sNewGamePlusChoiceWindow);
	PrintPrompt(NGP_PROMPT_WINDOW_ID(taskId), str);
	NGP_STATE(taskId) = NGP_STATE_PRINT_CHOICE_MADE;
}

static void ClosePrompt(u8 taskId)
{
	RemoveWindow(NGP_CHOICE_WINDOW_ID(taskId));
	RemoveWindow(NGP_PROMPT_WINDOW_ID(taskId));
	ClearMainMenuScreen();
}

// The intro expects to start from black.
static void StartFadeToNewGame(u8 taskId)
{
	BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
	NGP_STATE(taskId) = NGP_STATE_FADE_TO_NEW_GAME;
}

static void StartFadeToMainMenu(u8 taskId)
{
	BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_WHITE);
	NGP_STATE(taskId) = NGP_STATE_FADE_TO_MAIN_MENU;
}

// Leaves the menu exactly the way the New Game row does at 0x800CB38.
static void EnterNewGame(u8 taskId)
{
	NGP_MENU_EXIT_BYTE = 0;
	FreeAllWindowBuffers();
	DestroyTask(taskId);
	StartNewGameIntro();
}

// Called from the New Game row hook. Returns TRUE when it has taken the row over, which
// tells the hook to leave the menu running instead of starting a new game.
bool8 NewGamePlusNewGameRowSelected(u8 taskId)
{
	if (!FlagGet(FLAG_SYS_GAME_CLEAR))
	{
		// Required, not tidiness: sNewGamePlusPending is uninitialised at boot, so a stale
		// non-zero value here would make an ordinary new game transfer a save.
		NewGamePlusClearPending();
		NGP_MENU_EXIT_BYTE = 0;
		FreeAllWindowBuffers();
		return FALSE;
	}

	NGP_STATE(taskId) = NGP_STATE_OPEN_PROMPT;
	gTasks[taskId].func = Task_NewGamePlusConfirm;
	return TRUE;
}

void Task_NewGamePlusConfirm(u8 taskId)
{
	switch (NGP_STATE(taskId))
	{
		case NGP_STATE_OPEN_PROMPT:
			ClearMainMenuScreen();
			OpenPrompt(taskId);
			BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
			NGP_STATE(taskId) = NGP_STATE_WAIT_FADE_IN;
			break;

		case NGP_STATE_WAIT_FADE_IN:
			if (!gPaletteFade->active)
				NGP_STATE(taskId) = NGP_STATE_READ_PROMPT;
			break;

		case NGP_STATE_READ_PROMPT:
			// The explanation is several pages long, so this waits out a few A presses.
			RunTextPrinters();
			if (!IsTextPrinterActive(NGP_PROMPT_WINDOW_ID(taskId)))
			{
				// The cursor starts on Cancel on purpose. Someone mashing A through the pages then backs out instead of wiping a cleared save.
				OpenChoiceBox(taskId);
				NGP_STATE(taskId) = NGP_STATE_AWAIT_CHOICE;
			}
			break;

		case NGP_STATE_AWAIT_CHOICE:
			switch (Menu_ProcessInput())
			{
				case NGP_CHOICE_NEW_GAME:
					PlaySE(SE_SELECT);
					NewGamePlusClearPending();
					NGP_PENDING_EXIT(taskId) = NGP_EXIT_NEW_GAME;
					ShowChoiceMade(taskId, gText_NewGamePlusStartingNewGame);
					break;

				case NGP_CHOICE_NEW_GAME_PLUS:
					PlaySE(SE_SELECT);
					NewGamePlusBegin();
					NGP_PENDING_EXIT(taskId) = NGP_EXIT_NEW_GAME;
					ShowChoiceMade(taskId, gText_NewGamePlusStartingNewGamePlus);
					break;

				case MENU_B_PRESSED:
				case NGP_CHOICE_CANCEL:
					PlaySE(SE_SELECT);
					NewGamePlusClearPending();
					NGP_PENDING_EXIT(taskId) = NGP_EXIT_MAIN_MENU;
					ShowChoiceMade(taskId, gText_NewGamePlusReturning);
					break;
			}
			break;

		case NGP_STATE_FADE_TO_NEW_GAME:
			if (!gPaletteFade->active)
				EnterNewGame(taskId);
			break;

		case NGP_STATE_FADE_TO_MAIN_MENU:
			if (!gPaletteFade->active)
			{
				ClosePrompt(taskId);
				gTasks[taskId].func = NGP_MENU_REBUILD_TASK;
			}
			break;

		case NGP_STATE_PRINT_CHOICE_MADE:
			RunTextPrinters();
			if (!IsTextPrinterActive(NGP_PROMPT_WINDOW_ID(taskId)))
				NGP_STATE(taskId) = NGP_STATE_AWAIT_DISMISS;
			break;

		case NGP_STATE_AWAIT_DISMISS:
			// The message is a single page, so it is on this to wait rather than the text
			// engine. Without it the whole thing would be gone in a quarter of a second.
			if (gMain.newKeys & (A_BUTTON | B_BUTTON))
			{
				PlaySE(SE_SELECT);

				if (NGP_PENDING_EXIT(taskId) == NGP_EXIT_NEW_GAME)
					StartFadeToNewGame(taskId);
				else
					StartFadeToMainMenu(taskId);
			}
			break;
	}
}
