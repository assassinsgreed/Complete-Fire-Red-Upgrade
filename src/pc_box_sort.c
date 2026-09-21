#include "defines.h"
#include "../include/malloc.h"
#include "../include/menu.h"
#include "../include/new_menu_helpers.h"
#include "../include/pokemon.h"
#include "../include/pokemon_storage_system.h"
#include "../include/text.h"
#include "../include/window.h"

#include "../include/new/pokemon_storage_system.h"
#include "../include/new/util.h"

#define PC_SLOT_COUNT (TOTAL_BOXES_COUNT * IN_BOX_COUNT)
#define COMPRESSED_IS_EGG_BIT (1 << 30) //substruct3.isEgg, as it sits in the compressed record's packed IV word

//Reused verbatim from the ROM's own PC menu builder at 0x0808C72C. Neither has a BPRE.ld symbol.
#define PrintMenuActionTexts ((void (*)(u8 windowId, u8 fontId, u8 left, u8 top, u8 lineHeight, u8 itemCount, const struct MenuAction* actions)) (0x0810FB6C | 1))
#define Menu_GetCursorPos ((u8 (*)(void)) (0x0810F98C | 1))
#define Task_PCMainMenu ((TaskFunc) (0x0808C39C | 1))

#define PC_MENU_FONT 2

//Font 2's line advance. Must match the row pitch bytereplacement patches into the ROM's builder, or the cursor drifts away from the text it points at.
#define PC_MENU_LINE_HEIGHT 14
#define PC_MENU_TEXT_TOP 2

//The sort list's 7 rows do not fit at the parent menu's pitch inside the tallest window whose bottom frame row still clears the message box's own frame row
#define PC_SORT_LIST_LINE_HEIGHT 13

//Row the cursor must return to, since Sort Boxes is what the player was last on
#define PC_MENU_ROW_SORT 4

enum
{
	PC_BOX_SORT_SPECIES_AZ,
	PC_BOX_SORT_SPECIES_ZA,
	PC_BOX_SORT_DEX_LOW_HIGH,
	PC_BOX_SORT_DEX_HIGH_LOW,
	PC_BOX_SORT_LEVEL_LOW_HIGH,
	PC_BOX_SORT_LEVEL_HIGH_LOW,
	PC_BOX_SORT_NEVERMIND,
	PC_BOX_SORT_ROW_COUNT,
};

enum
{
	SORTMENU_DRAW_LIST,
	SORTMENU_LIST_INPUT,
	SORTMENU_DRAW_CONFIRM,
	SORTMENU_CONFIRM_INPUT,
	SORTMENU_START_SORT,
	SORTMENU_RUN_SORT,
	SORTMENU_WAIT_FOR_ACK,
	SORTMENU_RETURN_TO_PC_MENU,
};

//Eggs go to the very end and are never affected by the chosen direction, so that sorting cannot reveal what's inside
enum
{
	BOXSORT_GROUP_MAIN,
	BOXSORT_GROUP_TAIL,
};

//The PC menu's tables are {name, description} pairs
struct PCMenuEntry
{
	const u8* name;
	const u8* description;
};

#define tState        data[0]
#define tPCMenuRow    data[1]
#define tSortRow      data[4]
#define tSortOption   data[5]
#define tShownRow     data[6]
#define tYesNoWindow  data[7]
#define tTimer        data[8]
#define tMenuWindow   data[15]

extern const u8 gText_PCBoxSortMenuName[];
extern const u8 gText_PCBoxSortMenuDescription[];
extern const u8 gText_PCBoxSortSpeciesAZ[];
extern const u8 gText_PCBoxSortSpeciesAZDescription[];
extern const u8 gText_PCBoxSortSpeciesZA[];
extern const u8 gText_PCBoxSortSpeciesZADescription[];
extern const u8 gText_PCBoxSortDexLowHigh[];
extern const u8 gText_PCBoxSortDexLowHighDescription[];
extern const u8 gText_PCBoxSortDexHighLow[];
extern const u8 gText_PCBoxSortDexHighLowDescription[];
extern const u8 gText_PCBoxSortLevelLowHigh[];
extern const u8 gText_PCBoxSortLevelLowHighDescription[];
extern const u8 gText_PCBoxSortLevelHighLow[];
extern const u8 gText_PCBoxSortLevelHighLowDescription[];
extern const u8 gText_PCBoxSortNevermindDescription[];
extern const u8 gText_PCBoxSortConfirm[];
extern const u8 gText_PCBoxSortWorking[];
extern const u8 gText_PCBoxSortDone[];
extern const u8 gText_PCBoxSortNothingToDo[];
extern const u8 gText_PCBoxSortFailed[];

extern const u8 gText_Yes[];
extern const u8 gText_No[];
extern const u8 gText_ChangeMind[];

//Vanilla PC menu strings, kept by address because they live in the base ROM
#define sText_WithdrawName     ((const u8*) 0x0841856C)
#define sText_WithdrawDesc     ((const u8*) 0x084185AD)
#define sText_DepositName      ((const u8*) 0x0841857D)
#define sText_DepositDesc      ((const u8*) 0x084185E2)
#define sText_MovePokemonName  ((const u8*) 0x0841858D)
#define sText_MovePokemonDesc  ((const u8*) 0x08418611)
#define sText_MoveItemsName    ((const u8*) 0x0841859A)
#define sText_MoveItemsDesc    ((const u8*) 0x08418642)
#define sText_SeeYaName        ((const u8*) 0x084185A5)
#define sText_SeeYaDesc        ((const u8*) 0x08418681)

//Repointed over the base ROM's table at 0x083CDA20. Row order here is what
//pcBoxMenu_RemapInput converts back into BOX_OPTION values, so the two must agree.
const struct PCMenuEntry pcBoxMenu_ReorderedTexts[] =
{
	{sText_MovePokemonName,      sText_MovePokemonDesc},			//-> BOX_OPTION 2
	{sText_MoveItemsName,        sText_MoveItemsDesc},				//-> BOX_OPTION 3
	{sText_WithdrawName,         sText_WithdrawDesc},				//-> BOX_OPTION 0
	{sText_DepositName,          sText_DepositDesc},				//-> BOX_OPTION 1
	{gText_PCBoxSortMenuName,    gText_PCBoxSortMenuDescription},	//-> sentinel 5
	{sText_SeeYaName,            sText_SeeYaDesc},					//-> BOX_OPTION 4 (exit)
};

static const struct PCMenuEntry sSortMenuEntries[PC_BOX_SORT_ROW_COUNT] =
{
	[PC_BOX_SORT_SPECIES_AZ]     = {gText_PCBoxSortSpeciesAZ,    gText_PCBoxSortSpeciesAZDescription},
	[PC_BOX_SORT_SPECIES_ZA]     = {gText_PCBoxSortSpeciesZA,    gText_PCBoxSortSpeciesZADescription},
	[PC_BOX_SORT_DEX_LOW_HIGH]   = {gText_PCBoxSortDexLowHigh,   gText_PCBoxSortDexLowHighDescription},
	[PC_BOX_SORT_DEX_HIGH_LOW]   = {gText_PCBoxSortDexHighLow,   gText_PCBoxSortDexHighLowDescription},
	[PC_BOX_SORT_LEVEL_LOW_HIGH] = {gText_PCBoxSortLevelLowHigh, gText_PCBoxSortLevelLowHighDescription},
	[PC_BOX_SORT_LEVEL_HIGH_LOW] = {gText_PCBoxSortLevelHighLow, gText_PCBoxSortLevelHighLowDescription},
	[PC_BOX_SORT_NEVERMIND]      = {gText_ChangeMind,            gText_PCBoxSortNevermindDescription},
};

enum
{
	SORT_CONFIRM_YES,
	SORT_CONFIRM_NO,
};

static const struct PCMenuEntry sSortConfirmEntries[] =
{
	[SORT_CONFIRM_YES] = {gText_Yes, NULL},
	[SORT_CONFIRM_NO]  = {gText_No, NULL},
};

// Trims down the PC Box options menu so it doesn't overlap the textbox.
static const struct WindowTemplate sSortListWindow __attribute__((aligned(4))) =
{
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 17,
	.height = 12,
	.paletteNum = 15,
	.baseBlock = 1,
};

//Appears to the right of the sort list.
static const struct WindowTemplate sSortConfirmWindow __attribute__((aligned(4))) =
{
	.bg = 0,
	.tilemapLeft = 22,
	.tilemapTop = 1,
	.width = 6,
	.height = 4,
	.paletteNum = 15,
	.baseBlock = 222,
};

struct BoxSortWork
{
	u16 dest[PC_SLOT_COUNT];			//dest[i] = the origin slot whose Pokemon belongs at flat slot i
	u16 aux[PC_SLOT_COUNT];
	u16 key[PC_SLOT_COUNT];				//key[origin slot] = that Pokemon's primary sort key
	u16 slotOfOrigin[PC_SLOT_COUNT];	//origin slot -> where its Pokemon currently sits
	u16 originOfSlot[PC_SLOT_COUNT];	//physical slot -> which origin's Pokemon sits there
	u8 group[PC_SLOT_COUNT];
	u8 seen[(PC_SLOT_COUNT + 7) / 8];
	u16 count;
	u8 option;
};

//This file's functions:
static struct CompressedPokemon* GetPCSlotPtr(u16 slot);
static void SwapPCSlots(u16 slotA, u16 slotB);
static u8 GetPCSlotLevel(struct CompressedPokemon* mon);
static s32 CompareSpeciesNames(u16 speciesA, u16 speciesB);
static bool8 IsSpeciesNameSort(u8 option);
static bool8 IsDescendingSort(u8 option);
static void BoxSortCollectAndKey(struct BoxSortWork* work);
static bool8 BoxSortOriginPlacedBefore(struct BoxSortWork* work, u16 originA, u16 originB);
static void BoxSortMerge(struct BoxSortWork* work, u16 lo, u16 mid, u16 hi);
static void BoxSortRun(struct BoxSortWork* work);
static bool8 BoxSortPermutationIsValid(struct BoxSortWork* work);
static void BoxSortApply(struct BoxSortWork* work);
static s16 SortAllPCBoxes(u8 option);
static void DrawPCSortList(u8 windowId, const struct PCMenuEntry* entries, u8 count, u8 lineHeight, u8 cursorPos);
static void PrintPCSortMessage(const u8* text);
static void ClosePCSortConfirmWindow(struct Task* task);
static void Task_PCBoxSortMenu(u8 taskId);

static struct CompressedPokemon* GetPCSlotPtr(u16 slot)
{
	//Boxes 20 - 25 live at scavenged EWRAM addresses, and the slots where box 20 would
	//sit in the original array now hold the wallpapers and names for boxes 15 - 25, so
	//box storage must never be walked as one flat array
	return GetCompressedMonPtr(slot / IN_BOX_COUNT, slot % IN_BOX_COUNT);
}

static void SwapPCSlots(u16 slotA, u16 slotB)
{
	struct CompressedPokemon* a = GetPCSlotPtr(slotA);
	struct CompressedPokemon* b = GetPCSlotPtr(slotB);
	struct CompressedPokemon temp = *a;

	*a = *b;
	*b = temp;
}

static u8 GetPCSlotLevel(struct CompressedPokemon* mon)
{
	struct BoxPokemon boxMon;

	//Read-only decode. The record is never written back, so none of the fields the
	//compressed format drops can be lost here.
	CreateBoxMonFromCompressedMon(&boxMon, mon);
	return GetLevelFromBoxMonExp(&boxMon);
}

//Not StringCompare, which returns EOS minus the other character and so places a name
//after every name it is a prefix of - "Mew" after "Mewtwo"
static s32 CompareSpeciesNames(u16 speciesA, u16 speciesB)
{
	const u8* a = gSpeciesNames[speciesA];
	const u8* b = gSpeciesNames[speciesB];

	for (u32 i = 0; i <= POKEMON_NAME_LENGTH; ++i)
	{
		if (a[i] == b[i])
		{
			if (a[i] == EOS)
				return 0;

			continue;
		}

		if (a[i] == EOS)
			return -1;

		if (b[i] == EOS)
			return 1;

		return (s32) a[i] - (s32) b[i];
	}

	return 0;
}

static bool8 IsSpeciesNameSort(u8 option)
{
	return option == PC_BOX_SORT_SPECIES_AZ || option == PC_BOX_SORT_SPECIES_ZA;
}

static bool8 IsDescendingSort(u8 option)
{
	return option == PC_BOX_SORT_SPECIES_ZA
		|| option == PC_BOX_SORT_DEX_HIGH_LOW
		|| option == PC_BOX_SORT_LEVEL_HIGH_LOW;
}

static void BoxSortCollectAndKey(struct BoxSortWork* work)
{
	u16 lastSpecies = SPECIES_NONE;
	u16 lastDexNum = 0;
	u16 slot = 0;

	for (u32 boxId = 0; boxId < TOTAL_BOXES_COUNT; ++boxId)
	{
		for (u32 pos = 0; pos < IN_BOX_COUNT; ++pos, ++slot)
		{
			struct CompressedPokemon* mon = GetCompressedMonPtr(boxId, pos);
			u16 species = mon->substruct0.species;

			work->slotOfOrigin[slot] = slot;
			work->originOfSlot[slot] = slot;

			if (species == SPECIES_NONE)
				continue;

			work->dest[work->count++] = slot;

			if (mon->ivs & COMPRESSED_IS_EGG_BIT)
			{
				work->group[slot] = BOXSORT_GROUP_TAIL;
				continue;
			}

			switch (work->option) {
				case PC_BOX_SORT_SPECIES_AZ:
				case PC_BOX_SORT_SPECIES_ZA:
					work->key[slot] = species;
					break;

				case PC_BOX_SORT_DEX_LOW_HIGH:
				case PC_BOX_SORT_DEX_HIGH_LOW:
					//GetDisplayedPokedexNum scans up to 390 entries, and both dexes on a
					//miss, so it is called once per Pokemon here and never per comparison
					if (species != lastSpecies)
					{
						lastSpecies = species;
						lastDexNum = GetDisplayedPokedexNum(species);
					}

					//Species in neither mode's dex come back as 0, which is also the number
					//the game displays for them, so 0 sorts as an ordinary low number
					work->key[slot] = lastDexNum;
					break;

				case PC_BOX_SORT_LEVEL_LOW_HIGH:
				case PC_BOX_SORT_LEVEL_HIGH_LOW:
					work->key[slot] = GetPCSlotLevel(mon);
					break;
			}
		}
	}
}

static bool8 BoxSortOriginPlacedBefore(struct BoxSortWork* work, u16 originA, u16 originB)
{
	if (work->group[originA] != work->group[originB])
		return work->group[originA] < work->group[originB];

	if (work->group[originA] == BOXSORT_GROUP_MAIN)
	{
		s32 cmp;

		if (IsSpeciesNameSort(work->option))
			cmp = CompareSpeciesNames(work->key[originA], work->key[originB]);
		else
			cmp = (s32) work->key[originA] - (s32) work->key[originB];

		if (IsDescendingSort(work->option))
			cmp = -cmp;

		if (cmp != 0)
			return cmp < 0;
	}

	//Ascending in both directions, so equal Pokemon keep their relative order instead of
	//flipping when the player sorts the other way. Origin slots are unique, so this also
	//makes the comparison a total order.
	return originA < originB;
}

static void BoxSortMerge(struct BoxSortWork* work, u16 lo, u16 mid, u16 hi)
{
	u16 i = lo;
	u16 j = mid;

	for (u32 k = lo; k < hi; ++k)
		work->aux[k] = work->dest[k];

	for (u32 k = lo; k < hi; ++k)
	{
		if (i >= mid)
			work->dest[k] = work->aux[j++];
		else if (j >= hi)
			work->dest[k] = work->aux[i++];
		else if (BoxSortOriginPlacedBefore(work, work->aux[j], work->aux[i]))
			work->dest[k] = work->aux[j++];
		else
			work->dest[k] = work->aux[i++];
	}
}

//Bottom-up, so the stack depth does not grow with the number of Pokemon
static void BoxSortRun(struct BoxSortWork* work)
{
	for (u32 width = 1; width < work->count; width *= 2)
	{
		for (u32 lo = 0; lo < work->count; lo += width * 2)
		{
			u32 mid = lo + width;
			u32 hi = lo + (width * 2);

			if (mid >= work->count)
				break;

			if (hi > work->count)
				hi = work->count;

			BoxSortMerge(work, lo, mid, hi);
		}
	}
}

//Nothing is written until this passes, so a bug in the ordering logic cannot lose, duplicate, or alter a Pokemon
static bool8 BoxSortPermutationIsValid(struct BoxSortWork* work)
{
	for (u32 i = 0; i < work->count; ++i)
	{
		u16 slot = work->dest[i];

		if (slot >= PC_SLOT_COUNT)
			return FALSE;

		if (work->seen[slot / 8] & (1 << (slot % 8)))
			return FALSE;

		if (GetPCSlotPtr(slot)->substruct0.species == SPECIES_NONE)
			return FALSE;

		work->seen[slot / 8] |= 1 << (slot % 8);
	}

	return TRUE;
}

static void BoxSortApply(struct BoxSortWork* work)
{
	for (u16 i = 0; i < work->count; ++i)
	{
		u16 origin = work->dest[i];
		u16 src = work->slotOfOrigin[origin];
		u16 displaced;

		if (src == i)
			continue;

		//src can never be below i: slots below i already hold their final Pokemon, whose
		//origins are dest[0 .. i-1], and origin is not among those. So a finalised slot
		//is never disturbed, and because the only mutation is a swap of whole records the
		//set of Pokemon in the PC is invariant.
		SwapPCSlots(i, src);

		displaced = work->originOfSlot[i];
		work->originOfSlot[i] = origin;
		work->slotOfOrigin[origin] = i;
		work->originOfSlot[src] = displaced;
		work->slotOfOrigin[displaced] = src;
	}
}

//Returns how many Pokemon were placed, or -1 if nothing was touched
static s16 SortAllPCBoxes(u8 option)
{
	s16 result;
	struct BoxSortWork* work = AllocZeroed(sizeof(struct BoxSortWork));

	if (work == NULL)
		return -1;

	work->option = option;
	BoxSortCollectAndKey(work);

	if (work->count == 0)
	{
		Free(work);
		return 0;
	}

	BoxSortRun(work);

	if (!BoxSortPermutationIsValid(work))
	{
		Free(work);
		return -1;
	}

	BoxSortApply(work);
	result = work->count;
	Free(work);
	return result;
}

static void DrawPCSortList(u8 windowId, const struct PCMenuEntry* entries, u8 count, u8 lineHeight, u8 cursorPos)
{
	DrawStdWindowFrame(windowId, FALSE);
	PrintMenuActionTexts(windowId, PC_MENU_FONT, GetMenuCursorDimensionByFont(PC_MENU_FONT, 0),
						 PC_MENU_TEXT_TOP, lineHeight, count, (const struct MenuAction*) entries);
	Menu_InitCursor(windowId, PC_MENU_FONT, 0, PC_MENU_TEXT_TOP, lineHeight, count, cursorPos);
	CopyWindowToVram(windowId, 3);
}

static void PrintPCSortMessage(const u8* text)
{
	FillWindowPixelBuffer(0, PIXEL_FILL(1));
	AddTextPrinterParameterized2(0, PC_MENU_FONT, text, 0, NULL, 2, 1, 3);
	CopyWindowToVram(0, 3);
}

static void ClosePCSortConfirmWindow(struct Task* task)
{
	ClearStdWindowAndFrame(task->tYesNoWindow, TRUE);
	RemoveWindow(task->tYesNoWindow);
	task->tYesNoWindow = 0;
}

//Entered from pcBoxMenu_CheckSortSelection, which hands the live PC menu task over
//instead of creating a new one, so the overworld script waiting on the PC stays parked
//and the menu's window can be reused as is.
void Task_PCBoxSortMenuInit(u8 taskId)
{
	struct Task* task = &gTasks[taskId];

	ClearStdWindowAndFrame(task->tMenuWindow, TRUE);
	RemoveWindow(task->tMenuWindow);
	task->tMenuWindow = AddWindow(&sSortListWindow);

	task->tState = SORTMENU_DRAW_LIST;
	task->tSortRow = 0;
	task->tYesNoWindow = 0;
	task->func = Task_PCBoxSortMenu;
	Task_PCBoxSortMenu(taskId);
}

static void Task_PCBoxSortMenu(u8 taskId)
{
	struct Task* task = &gTasks[taskId];

	switch (task->tState) {
		case SORTMENU_DRAW_LIST:
			task->tShownRow = task->tSortRow;
			DrawPCSortList(task->tMenuWindow, sSortMenuEntries, PC_BOX_SORT_ROW_COUNT,
						   PC_SORT_LIST_LINE_HEIGHT, task->tSortRow);
			PrintPCSortMessage(sSortMenuEntries[task->tSortRow].description);
			task->tState = SORTMENU_LIST_INPUT;
			break;

		case SORTMENU_LIST_INPUT:
		{
			s8 input = Menu_ProcessInput();

			if (input == MENU_NOTHING_CHOSEN)
			{
				u8 row = Menu_GetCursorPos();

				if (row != task->tShownRow)
				{
					task->tShownRow = row;
					PrintPCSortMessage(sSortMenuEntries[row].description);
				}
			}
			else if (input == MENU_B_PRESSED || input == PC_BOX_SORT_NEVERMIND)
				task->tState = SORTMENU_RETURN_TO_PC_MENU;
			else
			{
				task->tSortOption = input;
				task->tState = SORTMENU_DRAW_CONFIRM;
			}
			break;
		}

		case SORTMENU_DRAW_CONFIRM:
			task->tYesNoWindow = AddWindow(&sSortConfirmWindow);
			PrintPCSortMessage(gText_PCBoxSortConfirm);
			DrawPCSortList(task->tYesNoWindow, sSortConfirmEntries, ARRAY_COUNT(sSortConfirmEntries),
						   PC_SORT_LIST_LINE_HEIGHT, 0);
			task->tState = SORTMENU_CONFIRM_INPUT;
			break;

		case SORTMENU_CONFIRM_INPUT:
		{
			s8 input = Menu_ProcessInput();

			if (input == MENU_NOTHING_CHOSEN)
				break;

			ClosePCSortConfirmWindow(task);

			if (input == SORT_CONFIRM_YES)
				task->tState = SORTMENU_START_SORT;
			else
			{
				task->tSortRow = task->tSortOption;
				task->tState = SORTMENU_DRAW_LIST;
			}
			break;
		}

		case SORTMENU_START_SORT:
			PrintPCSortMessage(gText_PCBoxSortWorking);
			task->tTimer = 0;
			task->tState = SORTMENU_RUN_SORT;
			break;

		case SORTMENU_RUN_SORT:
			//Keying every Pokemon blocks for up to half a second, so let the message
			//reach the screen first
			if (++task->tTimer < 3)
				break;

			{
				s16 sorted = SortAllPCBoxes(task->tSortOption);

				if (sorted > 0)
					PrintPCSortMessage(gText_PCBoxSortDone);
				else if (sorted == 0)
					PrintPCSortMessage(gText_PCBoxSortNothingToDo);
				else
					PrintPCSortMessage(gText_PCBoxSortFailed);
			}

			task->tState = SORTMENU_WAIT_FOR_ACK;
			break;

		case SORTMENU_WAIT_FOR_ACK:
			if (JOY_NEW(A_BUTTON | B_BUTTON))
				task->tState = SORTMENU_RETURN_TO_PC_MENU;
			break;

		case SORTMENU_RETURN_TO_PC_MENU:
			//Task_PCMainMenu's state 0 re-adds the menu window and redraws the frame and
			//description from scratch, so drop ours or the window slot leaks
			ClearStdWindowAndFrame(task->tMenuWindow, TRUE);
			RemoveWindow(task->tMenuWindow);
			task->tState = 0;
			task->tPCMenuRow = PC_MENU_ROW_SORT;
			task->func = Task_PCMainMenu;
			break;
	}
}
