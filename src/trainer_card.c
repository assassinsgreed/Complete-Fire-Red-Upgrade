#include "defines.h"
#include "../include/constants/items.h"
#include "../include/constants/vars.h"
#include "../include/menu.h"
#include "../include/pokemon_storage_system.h"
#include "../include/string_util.h"

#include "../include/new/frontier.h"
#include "../include/new/pokemon_storage_system.h"
#include "../include/new/util.h"

/*
trainer_card.c
	replaces the vanilla star criteria (Hall of Fame / Kanto dex / National dex / Pokemon Jump +
	Berry Picking) and the back page stat rows with Amethyst's own
*/

/* ---------------------------------------------------------------------------------------------
	Stars
--------------------------------------------------------------------------------------------- */

//The vanilla routine's own star arithmetic lives at 0x08089960 - 0x08089989 and is skipped
//entirely; see TrainerCardStarHook below.
#define TRAINER_CARD_STARS_OFFSET 0x1

#define ZCRYSTAL_COUNT (ITEM_FAIRIUM_Z - ITEM_NORMALIUM_Z + 1)
#define ALL_ZCRYSTALS_MASK ((1 << ZCRYSTAL_COUNT) - 1)

/* ---------------------------------------------------------------------------------------------
	Back page
--------------------------------------------------------------------------------------------- */

//The vanilla back page has five 16px-tall rows. Row 1 (Hall Of Fame Debut) is left to the vanilla
//routine, which already formats the h:mm:ss out of the card; the other four are replaced wholesale.
//Their vanilla contents were Link Battles W/L, Pokemon Trades, Union Trades & Battles and Berry
//Crush, none of which this hack can produce.
#define TRAINER_CARD_ROW_2_Y 0x33
#define TRAINER_CARD_ROW_3_Y 0x43
#define TRAINER_CARD_ROW_4_Y 0x53
#define TRAINER_CARD_ROW_5_Y 0x63

#define TRAINER_CARD_WINDOW 1
#define TRAINER_CARD_FONT 2
#define TRAINER_CARD_VALUE_X 186
#define TRAINER_CARD_VALUE_DIGITS 5

//sTrainerCardData, the malloc'd struct the whole trainer card screen works out of
#define sTrainerCardData (*(u8**) 0x020397A4)

//Byte selecting which of the two card layouts is in use; indexes the label column table
#define TRAINER_CARD_LAYOUT_OFFSET 0x457

//Scratch string slots inside sTrainerCardData. Vanilla fills these for the rows being replaced, so
//they are free to reuse - each is 0x46 bytes and only ever holds one row's text.
#define TRAINER_CARD_SCRATCH_1 0x0D9
#define TRAINER_CARD_SCRATCH_2 0x11F
#define TRAINER_CARD_SCRATCH_3 0x165
#define TRAINER_CARD_SCRATCH_4 0x1AB

//Vanilla tables the replaced rows were already reading
#define sTrainerCardLabelColumn ((const u8*) 0x083CD940) //Indexed by the layout byte
#define sTrainerCardLabelColor ((const u8*) 0x083CD8E0)
#define sTrainerCardValueColor ((const u8*) 0x083CD8E3)

//Vanilla page 2 steps that are kept as-is: the "<name>'s Trainer Card" header, the Hall Of Fame
//Debut row, and the two that stamp the row separator rules and the bottom decoration
#define PrintNameOnTrainerCardBack ((void (*)(void)) (0x0808A4FC | 1))
#define PrintHallOfFameDebutOnCard ((void (*)(void)) (0x0808A654 | 1))
#define PrintTrainerCardBackRules ((void (*)(void)) (0x0808AA78 | 1))
#define PrintTrainerCardBackTrim ((void (*)(void)) (0x0808ABE0 | 1))

extern const u8 gText_TrainerCardTitleDefenses[];
extern const u8 gText_TrainerCardEggsHatched[];
extern const u8 gText_TrainerCardPokemonCaught[];
extern const u8 gText_TrainerCardCenterHeals[];

//This file's functions:
static bool8 HasBecomeTheChampion(void);
static bool8 HasCompletedThePokedex(void);
static bool8 HasMilestoneStreakAtAnyFacility(void);
static bool8 HasEveryGymTraineeZCrystal(void);
static u32 AddZCrystalToMask(u32 mask, u16 item);
static void PrintTrainerCardStatRow(u8 y, const u8* label, u32 value, u16 scratchOffset);
static u32 GetTimesChampionTitleDefended(void);

void CountTrainerCardStars(u8* trainerCard);
bool8 PrintAllOnTrainerCardBack(void);

static bool8 HasBecomeTheChampion(void)
{
	return FlagGet(FLAG_SYS_GAME_CLEAR);
}

static bool8 HasCompletedThePokedex(void)
{
	//Standard and divergent mode share a species count, so this needs no mode check
	return GetNationalPokedexCount(FLAG_GET_CAUGHT) >= NATIONAL_DEX_COUNT;
}

static bool8 HasMilestoneStreakAtAnyFacility(void)
{
	for (u8 facility = 0; facility < NUM_BATTLE_FACILITIES; ++facility)
	{
		for (u8 format = 0; format < NUM_FRONTIER_FORMATS; ++format)
		{
			if (GetFrontierStreak(facility, format, MAX_STREAK) >= FRONTIER_SECOND_MILESTONE_STREAK)
				return TRUE;
		}
	}

	return FALSE;
}

static u32 AddZCrystalToMask(u32 mask, u16 item)
{
	if (item >= ITEM_NORMALIUM_Z && item <= ITEM_FAIRIUM_Z)
		mask |= 1 << (item - ITEM_NORMALIUM_Z);

	return mask;
}

static bool8 HasEveryGymTraineeZCrystal(void)
{
	u32 mask = 0;

	// We record that all Z-Crystals are obtained once we find them all in the bag/party/box Pokemon.
	// After that has been proven, we set a flag so we don't do the expensive check anymore.
	// This also means that tossing a Z-Crystal after getting the star doesn't cause the star to be revoked.
	if (FlagGet(FLAG_ALL_ZCRYSTALS_OBTAINED))
		return TRUE;

	// No trainee hands out a crystal before this, so the box sweep below can be skipped outright
	if (!FlagGet(FLAG_DEFEATED_ULTRA_NECROZMA))
		return FALSE;

	for (u16 item = ITEM_NORMALIUM_Z; item <= ITEM_FAIRIUM_Z; ++item)
	{
		if (CheckBagHasItem(item, 1))
			mask |= 1 << (item - ITEM_NORMALIUM_Z);
	}

	for (u8 i = 0; i < PARTY_SIZE && mask != ALL_ZCRYSTALS_MASK; ++i)
		mask = AddZCrystalToMask(mask, GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, NULL));

	for (u8 box = 0; box < TOTAL_BOXES_COUNT && mask != ALL_ZCRYSTALS_MASK; ++box)
	{
		for (u8 pos = 0; pos < IN_BOX_COUNT && mask != ALL_ZCRYSTALS_MASK; ++pos)
			mask = AddZCrystalToMask(mask, GetBoxMonDataAt(box, pos, MON_DATA_HELD_ITEM));
	}

	if (mask != ALL_ZCRYSTALS_MASK)
		return FALSE;

	FlagSet(FLAG_ALL_ZCRYSTALS_OBTAINED);
	return TRUE;
}

//Four criteria is the hard ceiling: the card's background palette tables at 0x083CD8B8 and
//0x083CD8CC are indexed by the star count and only hold five entries (0 - 4 stars).
void CountTrainerCardStars(u8* trainerCard)
{
	u8 stars = 0;

	if (HasBecomeTheChampion())
		++stars;

	if (HasCompletedThePokedex())
		++stars;

	if (HasMilestoneStreakAtAnyFacility())
		++stars;

	if (HasEveryGymTraineeZCrystal())
		++stars;

	trainerCard[TRAINER_CARD_STARS_OFFSET] = stars;
}

// Hooked at 0x08089960, inside TrainerCard_GenerateCardForPlayer, at the point where every other
// field of the card has been filled in and the vanilla routine starts counting its own stars.
// r5 holds the TrainerCard; 0x0808998A is where that star arithmetic ends.
void __attribute__((naked)) TrainerCardStarHook(void)
{
	asm_unified(
		"push {lr}\n"
		"adds r0, r5, #0\n"
		"bl CountTrainerCardStars\n"
		"pop {r0}\n"
		"mov lr, r0\n"
		"ldr r0, =(0x0808998A + 1)\n"
		"bx r0\n"
		".pool\n"
	);
}

static void PrintTrainerCardStatRow(u8 y, const u8* label, u32 value, u16 scratchOffset)
{
	u8* data = sTrainerCardData;
	u8* valueText = data + scratchOffset;
	u8 labelX = sTrainerCardLabelColumn[data[TRAINER_CARD_LAYOUT_OFFSET]];

	ConvertIntToDecimalStringN(valueText, value, STR_CONV_MODE_RIGHT_ALIGN, TRAINER_CARD_VALUE_DIGITS);

	AddTextPrinterParameterized3(TRAINER_CARD_WINDOW, TRAINER_CARD_FONT, labelX, y, sTrainerCardLabelColor, -1, label);
	AddTextPrinterParameterized3(TRAINER_CARD_WINDOW, TRAINER_CARD_FONT, TRAINER_CARD_VALUE_X, y, sTrainerCardValueColor, -1, valueText);
}

static u32 GetTimesChampionTitleDefended(void)
{
	// Every Hall of Fame registration bumps this stat, including HallOfFame_RegistrationTitleDefense, so entries past the first are actual defences
	u32 hallOfFameEntries = GetGameStat(GAME_STAT_ENTERED_HOF);

	if (hallOfFameEntries == 0)
		return 0;

	return hallOfFameEntries - 1;
}

// Replaces the vanilla eight-step page 2 printer at 0x08089E40. Returning TRUE means "done", which
// the caller polls for, so drawing every row in one go is fine - all of these print instantly.
bool8 PrintAllOnTrainerCardBack(void)
{
	PrintNameOnTrainerCardBack();
	PrintHallOfFameDebutOnCard();

	PrintTrainerCardStatRow(TRAINER_CARD_ROW_2_Y, gText_TrainerCardTitleDefenses,
		GetTimesChampionTitleDefended(), TRAINER_CARD_SCRATCH_1);

	PrintTrainerCardStatRow(TRAINER_CARD_ROW_3_Y, gText_TrainerCardEggsHatched,
		GetGameStat(GAME_STAT_HATCHED_EGGS), TRAINER_CARD_SCRATCH_2);

	PrintTrainerCardStatRow(TRAINER_CARD_ROW_4_Y, gText_TrainerCardPokemonCaught,
		GetGameStat(GAME_STAT_POKEMON_CAPTURES), TRAINER_CARD_SCRATCH_3);

	PrintTrainerCardStatRow(TRAINER_CARD_ROW_5_Y, gText_TrainerCardCenterHeals,
		GetGameStat(GAME_STAT_USED_POKECENTER_OR_NURSE), TRAINER_CARD_SCRATCH_4);

	PrintTrainerCardBackRules();
	PrintTrainerCardBackTrim();

	return TRUE;
}

/* ---------------------------------------------------------------------------------------------
	Party icons in the six pokeball slots
--------------------------------------------------------------------------------------------- */

void PrintPartyOnTrainerCard(void)
{
	for (u8 i = 0; i < PARTY_SIZE; ++i)
	{
		// SPECIES2 so an egg shows the egg icon instead of giving away what's inside
		u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL);

		VarSet(VAR_TRAINER_CARD_MON_ICON_1 + i, species);
	}
}

void ErasePartyFromTrainerCard(void)
{
	for (u8 i = 0; i < PARTY_SIZE; ++i)
		VarSet(VAR_TRAINER_CARD_MON_ICON_1 + i, SPECIES_NONE);
}
