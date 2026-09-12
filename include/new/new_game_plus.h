#pragma once

#include "../global.h"
#include "../../src/config.h"
#include "../pokemon_storage_system.h"
#include "pokemon_storage_system.h"

/**
 * \file new_game_plus.h
 * \brief New Game+ : starts a fresh save that inherits the PC boxes, the Pokedex,
 *		  every bag pocket except key items, money, the game modifiers and the trainer ID
 *		  from a save that has already beaten the game.
 */

// The 25 boxes are not one contiguous block. Their contents, names and wallpapers each sit
// in several disjointed regions, zeroed by different mechanisms during new-game init, so
// every box is snapshotted. The snapshot is flat and is filled a box at a time through the
// storage system's own pointer tables, so it never has to name those regions itself.
#define NGP_BOX_MON_COUNT     (TOTAL_BOXES_COUNT * IN_BOX_COUNT)
#define NGP_BOX_NAME_BYTES    9 // Eight characters plus the terminator, the width the storage system stores

// Bag pocket sizes.
#define NGP_BAG_ITEMS_COUNT   450
#define NGP_BAG_BALLS_COUNT   50
#define NGP_TMHM_COUNT        106
#define NGP_BAG_BERRIES_COUNT 75

#define NGP_DEX_FLAG_BYTES    125 // (999 / 8) + 1, matching SaveBlock1's dex arrays

// Game Modifier unlock flags (22 currently) plus the active modifier flags, packed into 48 bits. The
// active count mirrors gFrontierOverriddenModifierFlags; frontier_challenge.c asserts it.
//The options the player can set. Three bytes of SaveBlock2 hold vanilla FR's six usual ones;
//Amethyst's custom ones are covered by vars and flags, listed in src/new_game_plus.c.
#define NGP_OPTION_BYTES      3
#define NGP_OPTION_VAR_COUNT  5
#define NGP_OPTION_FLAG_COUNT 8

#define NGP_ACTIVE_FLAG_COUNT 26
#define NGP_MODIFIER_FLAG_WORDS 2

struct NewGamePlusBackup
{
	struct CompressedPokemon boxes[NGP_BOX_MON_COUNT];
	u8 boxNames[TOTAL_BOXES_COUNT][NGP_BOX_NAME_BYTES];
	u8 boxWallpapers[TOTAL_BOXES_COUNT];
	u8 dexSeen[NGP_DEX_FLAG_BYTES];
	u8 dexCaught[NGP_DEX_FLAG_BYTES];
	// Key items are deliberately absent.
	struct ItemSlot bagItems[NGP_BAG_ITEMS_COUNT];
	struct ItemSlot bagBalls[NGP_BAG_BALLS_COUNT];
	struct ItemSlot bagTMHM[NGP_TMHM_COUNT];
	struct ItemSlot bagBerries[NGP_BAG_BERRIES_COUNT];
	u32 modifierFlags[NGP_MODIFIER_FLAG_WORDS];
	u32 money;
	u16 instantWeather;
	u16 instantTerrain;
	u8 trainerId[4];
	u8 options[NGP_OPTION_BYTES];
	u16 optionVars[NGP_OPTION_VAR_COUNT];
	u32 optionFlags;
};

// Set when the player picks New Game Plus at the main menu, read at new-game init.
// Used to determine whether or not the data wipe needs to occur in new games (regular) or not (NG+).
extern bool8 sNewGamePlusPending;
extern struct NewGamePlusBackup* sNewGamePlusBackup;

// Exported Functions
void NewGamePlusBegin(void);
void NewGamePlusClearPending(void);
void NewGamePlusCapture(void);
void NewGamePlusRestore(void);
const u8* GetMainMenuNewGameLabel(void);
bool8 NewGamePlusNewGameRowSelected(u8 taskId);
void Task_NewGamePlusConfirm(u8 taskId);
