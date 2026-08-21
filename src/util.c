#include "defines.h"
#include "../include/random.h"
#include "../include/constants/abilities.h"
#include "../include/constants/items.h"

#include "../include/new/ability_tables.h"
#include "../include/new/damage_calc.h"
#include "../include/new/evolution.h"
#include "../include/new/frontier.h"
#include "../include/new/mega.h"
#include "../include/new/util.h"
#include "../include/money.h"
#include "../include/string_util.h"

/*
util.c
	general utility functions
*/

//This file's functions:
static u8 TryRandomizeAbility(u8 ability, unusedArg u16 species);

u32 MathMax(u32 num1, u32 num2)
{
	if (num1 > num2)
		return num1;

	return num2;
}

u32 MathMin(u32 num1, u32 num2)
{
	if (num1 < num2)
		return num1;

	return num2;
}

u16 RandRange(u16 min, u16 max)
{
	if (min == max)
		return min;

	return (Random() % (max - min)) + min;
}

bool8 CheckTableForMove(u16 move, const u16 table[])
{
	for (u32 i = 0; table[i] != MOVE_TABLES_TERMIN; ++i)
	{
		if (move == table[i])
			return TRUE;
	}

	return FALSE;
}

bool8 CheckTableForMovesEffect(u16 move, const u8 table[])
{
	for (u32 i = 0; table[i] != MOVE_EFFECT_TABLES_TERMIN; ++i)
	{
		if (gBattleMoves[move].effect == table[i])
			return TRUE;
	}

	return FALSE;
}

bool8 CheckTableForAbility(u8 ability, const u8 table[])
{
	for (u32 i = 0; table[i] != ABILITY_TABLES_TERMIN; ++i)
	{
		if (ability == table[i])
			return TRUE;
	}

	return FALSE;
}

bool8 CheckTableForSpecialMoveEffect(u8 effect, const u8 table[])
{
	for (u32 i = 0; table[i] != ABILITY_TABLES_TERMIN; ++i)
	{
		if (effect == table[i])
			return TRUE;
	}

	return FALSE;
}

bool8 CheckTableForSpecies(u16 species, const u16 table[])
{
	for (u32 i = 0; table[i] != SPECIES_TABLES_TERMIN; ++i)
	{
		if (species == table[i])
			return TRUE;
	}

	return FALSE;
}

bool8 CheckTableForItem(u16 item, const u16 table[])
{
	for (u32 i = 0; table[i] != ITEM_TABLES_TERMIN; ++i)
	{
		if (item == table[i])
			return TRUE;
	}

	return FALSE;
}

u8 ViableMonCount(struct Pokemon* party)
{
	u8 count = 0;

	for (u32 i = 0; i < PARTY_SIZE; ++i)
	{
		//Don't use GetMonData because time saving is important
		if (party[i].species != SPECIES_NONE
		&&  party[i].hp > 0
		&& !party[i].isEgg)
			++count;
	}

	return count;
}

void HealMon(struct Pokemon* mon)
{
	u32 none = 0;
	u16 maxHP = GetMonData(mon, MON_DATA_MAX_HP, NULL);

	//Restore HP.
	SetMonData(mon, MON_DATA_HP, &maxHP);

	//Restore PP.
	MonRestorePP(mon);

	//Restore Status.
	SetMonData(mon, MON_DATA_STATUS, &none);
}

void SetMonPokedexFlags(struct Pokemon* mon)
{
	if (!GetMonData(mon, MON_DATA_IS_EGG, NULL))
	{
		u16 dexNum = SpeciesToNationalPokedexNum(GetMonData(mon, MON_DATA_SPECIES, NULL));
		u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
		GetSetPokedexFlag(dexNum, FLAG_SET_SEEN);
		HandleSetPokedexFlag(dexNum, FLAG_SET_CAUGHT, personality);
	}
}

// The dex changes dynamically between standard and divergent mode.
// Instead of counting the correct dex's caught pokemon in multiple places (Ex. trainer card & critical captures)
// it is computed here, based on actual caught flags for the active dex.
#define GetRegionalDexCount ((u16 (*)(u8 caseId)) (0x08088EDC | 1))
u16 GetNationalPokedexCount(u8 caseID)
{
	return GetRegionalDexCount((caseID == FLAG_GET_SEEN) ? FLAG_GET_SEEN : FLAG_GET_CAUGHT);
}

// The species lists behind each mode's dex, laid out as a u16 count followed by that many species.
// The two modes do not share dex numbers - standard species map to 1 - 390 and divergent-exclusive
// ones to 391 - 780 - so flags set for one mode never collide with the other's.
// These are the same two tables GetRegionalDexCount picks between off FLAG_DIVERGENT_WILD_ENCOUNTERS.
#define sRegionalDexTableStandard  ((const u16*) 0x09C1CE00)
#define sRegionalDexTableDivergent ((const u16*) 0x09C1BEB4)

const u16* GetRegionalDexSpeciesTable(bool8 divergent, u16* count)
{
	const u16* table = divergent ? sRegionalDexTableDivergent : sRegionalDexTableStandard;

	*count = table[0];
	return &table[1];
}

// Checks the dex for the active mode only
bool8 IsPokedexComplete(void)
{
	for (u32 divergent = FALSE; divergent <= TRUE; ++divergent)
	{
		u16 count;
		const u16* speciesTable = GetRegionalDexSpeciesTable(divergent, &count);
		bool8 complete = TRUE;

		for (u32 i = 0; i < count && complete; ++i)
			complete = GetSetPokedexFlag(SpeciesToNationalPokedexNum(speciesTable[i]), FLAG_GET_CAUGHT);

		if (complete)
			return TRUE;
	}

	return FALSE;
}

// Checks if items from start to end index are held in the bag
static bool8 AreAllItemsInRangeObtained(u16 startRange, u16 endRange)
{
	for (u32 i = startRange; i <= endRange; ++i)
	{
		if (!CheckBagHasItem(i, 1))
			return FALSE;
	}

	return TRUE;
}

// Reminder: TMs are in split ranges and HMs 5 and 7 are unused.
bool8 HasEveryTMAndHM(void)
{
	return AreAllItemsInRangeObtained(ITEM_TM01_WORK_UP, ITEM_TM50_OVERHEAT)
	    && AreAllItemsInRangeObtained(ITEM_TM51_STEEL_WING, ITEM_TM58_ENDURE)
	    && AreAllItemsInRangeObtained(ITEM_TM59_BRUTAL_SWING, ITEM_TM100_CONFIDE)
	    && AreAllItemsInRangeObtained(ITEM_HM01_CUT, ITEM_HM04_STRENGTH)
	    && CheckBagHasItem(ITEM_HM06_ROCK_SMASH, 1)
	    && CheckBagHasItem(ITEM_HM08_ROCK_CLIMB, 1);
}

bool8 SpeciesWithDexNumOnTeam(u16 dexNum)
{
	u32 i;

	for (i = 0; i < PARTY_SIZE; ++i)
	{
		u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL);

		if (species != SPECIES_NONE
		&& species != SPECIES_EGG
		&& SpeciesToNationalPokedexNum(species) == dexNum)
			return TRUE;
	}

	return FALSE;
}

bool8 CanSpeciesEvolve(u16 species)
{
	const struct Evolution* evolutions = gEvolutionTable[species];

	for (u32 i = 0; i < EVOS_PER_MON; ++i)
	{
		if (evolutions[i].method == EVO_NONE) //Most likely end of entries
			break; //Break now to save time
		else if (evolutions[i].method != MEGA_EVOLUTION && evolutions[i].method != EVO_GIGANTAMAX)
			return TRUE;
	}

	return FALSE;
}

bool8 CanEvolve(struct Pokemon* mon)
{
	return CanSpeciesEvolve(GetMonData(mon, MON_DATA_SPECIES, NULL));
}

bool8 CouldHaveEvolvedViaLevelUp(struct Pokemon* mon)
{
	u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
	const struct Evolution* evolutions = gEvolutionTable[species];

	for (u32 i = 0; i < EVOS_PER_MON; ++i)
	{
		if (evolutions[i].method == EVO_NONE) //Most likely end of entries
			break; //Break now to save time
		else if (IsLevelUpEvolutionMethod(evolutions[i].method) && mon->level >= evolutions[i].param)
			return TRUE;
	}

	return FALSE;
}

bool8 EvolveSpeciesByLevel(u16* species, u8 level)
{
	const struct Evolution* evolutions;
	bool8 evolved = FALSE;

	START:
	evolutions = gEvolutionTable[*species];

	for (u32 i = 0; i < EVOS_PER_MON; ++i)
	{
		if (evolutions[i].method == EVO_NONE) //Most likely end of entries
			break; //Break now to save time
		else if ((IsLevelUpEvolutionMethod(evolutions[i].method) && level >= evolutions[i].param)
		||  (IsOtherEvolutionMethod(evolutions[i].method) && level >= 40)
		||  (IsItemEvolutionMethod(evolutions[i].method) && level >= 45)
		||  (IsFriendshipEvolutionMethod(evolutions[i].method) && level >= 55))
		{
			*species = evolutions[i].targetSpecies;
			evolved = TRUE;
			goto START; //Evolve until it can't evolve any more
		}
	}

	return evolved;
}

u32 GetBaseStatsTotal(const u16 species)
{
	u32 sum = 0;
	u8* ptr = &gBaseStats[species].baseHP;

	for (int i = 0; i < NUM_STATS; ++i)
		sum += ptr[i];

	return sum;
}

static u8 TryRandomizeAbility(u8 originalAbility, unusedArg u16 species)
{
	u32 newAbility = originalAbility;

	#ifdef FLAG_ABILITY_RANDOMIZER
	if (FlagGet(FLAG_ABILITY_RANDOMIZER) && !FlagGet(FLAG_BATTLE_FACILITY)
	&& !gSpecialAbilityFlags[originalAbility].gRandomizerBannedOriginalAbilities) //This Ability can be changed
	{
		u32 id = T1_READ_32(gSaveBlock2->playerTrainerId);
		u16 startAt = (id & 0xFFFF) % (u32) ABILITIES_COUNT + species;
		u16 xorVal = (id >> 16) % (u32) 0xFF; //Only set the bits likely to be in the ability
		u32 numAttempts = 0;

		newAbility = originalAbility + startAt;
		if (newAbility >= ABILITIES_COUNT)
		{
			u16 overflow = newAbility - (ABILITIES_COUNT - 2);
			newAbility = overflow;
		}

		newAbility ^= xorVal;
		newAbility %= (u32) ABILITIES_COUNT; //Prevent overflow

		while (gSpecialAbilityFlags[newAbility].gRandomizerBannedNewAbilities && numAttempts < 100)
		{
			newAbility *= xorVal; //Multiply this time
			newAbility %= (u32) ABILITIES_COUNT;
			++numAttempts;
		}

		if (numAttempts >= 100 && gSpecialAbilityFlags[newAbility].gRandomizerBannedNewAbilities) //If the Ability is still banned
			newAbility = originalAbility; //Just use the original ability
		else if (newAbility == ABILITY_NONE) //Somehow wound up with no Ability
			newAbility = originalAbility; //Just use the original ability
	}
	#endif

	return newAbility;
}

u8 GetAbility1(const u16 species)
{
	return TryRandomizeAbility(gBaseStats[species].ability1, species);
}

u8 GetAbility2(const u16 species)
{
	return TryRandomizeAbility(gBaseStats[species].ability2, species);
}

u8 GetHiddenAbility(const u16 species)
{
	return TryRandomizeAbility(gBaseStats[species].hiddenAbility, species);
}

u8 FindMovePositionInMonMoveset(u16 move, struct Pokemon* mon)
{
	u8 i;

	for (i = 0; i < MAX_MON_MOVES; ++i)
	{
		if (GetMonData(mon, MON_DATA_MOVE1 + i, NULL) == move)
			break;
	}

	return i;
}

bool8 MoveInMonMoveset(u16 move, struct Pokemon* mon)
{
	return FindMovePositionInMonMoveset(move, mon) < MAX_MON_MOVES;
}

bool8 AllHittingMoveWithTypeInMonMoveset(struct Pokemon* mon, u8 moveType)
{
	for (u32 i = 0; i < MAX_MON_MOVES; ++i)
	{
		u16 move = GetMonData(mon, MON_DATA_MOVE1 + i, NULL);

		if (gBattleMoves[move].target & MOVE_TARGET_ALL
		&& GetMonMoveTypeSpecial(mon, move) == moveType)
			return TRUE;
	}

	return FALSE;
}

u8 GetMonType(struct Pokemon* mon, u8 typeId)
{
	u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);

	if (typeId == 0)
		return (ShouldReplaceTypesWithCamomons()) ? GetCamomonsTypeByMon(mon, 0) : gBaseStats[species].type1;
	else
		return (ShouldReplaceTypesWithCamomons()) ? GetCamomonsTypeByMon(mon, 1) : gBaseStats[species].type2;
}

bool8 IsMonOfType(struct Pokemon* mon, u8 type)
{
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	return type1 == type || type2 == type;
}

bool8 IsSpeciesOfType(u16 species, u8 type)
{
	return gBaseStats[species].type1 == type || gBaseStats[species].type2 == type;
}

bool8 IsSpeciesAffectedByScalemons(u16 species)
{
	if (species == SPECIES_SHEDINJA) //Shedinja would get OP stats because of its low HP and BST
		return FALSE;

	if (IsOnlyScalemonsGame() && CanSpeciesEvolve(species))
		return FALSE; //Only Pokemon that are fully evolved are affected by the scaling outside of the Frontier

	return TRUE;
}

u8 GetVisualBaseStat(u8 statId, u16 species) //For the Pokedex screen
{
	u16 base = ((u8*) (&gBaseStats[species].baseHP))[statId];

	if (statId != STAT_HP && IsScaleMonsBattle() && IsSpeciesAffectedByScalemons(species))
	{
		u8 baseHP = gBaseStats[species].baseHP;
		base = MathMin((base * (600 - baseHP)) / (GetBaseStatsTotal(species) - baseHP), 255); //Max 255
	}

	return base;
}

/*#define TILE_SIZE 32
#define SPRITE_RAM 0x6010000
#define sSpriteTileAllocBitmap ((u8*) 0x2021B48)
#define FREE_SPRITE_TILE(n) (sSpriteTileAllocBitmap[(n) / 8] &= ~(1 << ((n) % 8)))

void DestroyMonIconSprite(struct Sprite* sprite)
{
	u16 tile = sprite->oam.tileNum;
	u8* tiles = (u8*)((tile * TILE_SIZE) + SPRITE_RAM);
	Memset(tiles, 0, 0x200);

	for (int i = tile; i < tile + 16; ++i)
		FREE_SPRITE_TILE(i);

	ResetSprite(sprite);
}*/

bool8 CanPartyMonBeGeneralStatused(struct Pokemon* mon)
{
	u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	#ifdef SPECIES_MINIOR_SHIELD
	if (species == SPECIES_MINIOR_SHIELD)
		return FALSE;
	#endif

	switch (GetMonAbility(mon)) {
		case ABILITY_COMATOSE:
			return FALSE;

		case ABILITY_FLOWERVEIL:
			if (type1 == TYPE_GRASS
			||  type2 == TYPE_GRASS)
				return FALSE;
	}

	return TRUE;
}

bool8 CanPartyMonBePutToSleep(struct Pokemon* mon)
{
	if (!CanPartyMonBeGeneralStatused(mon))
		return FALSE;

	switch (GetMonAbility(mon)) {
		case ABILITY_INSOMNIA:
		#ifdef ABILITY_VITALSPIRIT
		case ABILITY_VITALSPIRIT:
		#endif
		case ABILITY_SWEETVEIL:
			return FALSE;
	}

	return TRUE;
}

bool8 CanPartyMonBePoisoned(struct Pokemon* mon)
{
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	if (!CanPartyMonBeGeneralStatused(mon))
		return FALSE;

	switch (GetMonAbility(mon)) {
		case ABILITY_IMMUNITY:
		case ABILITY_PASTELVEIL:
			return FALSE;
	}

	if (type1 == TYPE_POISON
	||  type2 == TYPE_POISON
	||  type1 == TYPE_STEEL
	||  type2 == TYPE_STEEL)
		return FALSE;

	return TRUE;
}

bool8 CanPartyMonBeParalyzed(struct Pokemon* mon)
{
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	if (!CanPartyMonBeGeneralStatused(mon))
		return FALSE;

	switch (GetMonAbility(mon)) {
		case ABILITY_LIMBER:
			return FALSE;
	}

	if (type1 == TYPE_ELECTRIC
	||  type2 == TYPE_ELECTRIC)
		return FALSE;

	return TRUE;
}

bool8 CanPartyMonBeBurned(struct Pokemon* mon)
{
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	if (!CanPartyMonBeGeneralStatused(mon))
		return FALSE;

	switch (GetMonAbility(mon)) {
		case ABILITY_WATERVEIL:
		case ABILITY_WATERBUBBLE:
			return FALSE;
	}

	if (type1 == TYPE_FIRE
	||  type2 == TYPE_FIRE)
		return FALSE;

	return TRUE;
}

bool8 CanPartyMonBeFrozen(struct Pokemon* mon)
{
	u8 type1 = GetMonType(mon, 0);
	u8 type2 = GetMonType(mon, 1);

	if (!CanPartyMonBeGeneralStatused(mon))
		return FALSE;

	switch (GetMonAbility(mon)) {
		case ABILITY_MAGMAARMOR:
			return FALSE;
	}

	if (type1 == TYPE_ICE
	||  type2 == TYPE_ICE)
		return FALSE;

	return TRUE;
}

// Stores the requested game stat in var 800D (LASTRESULT) based on the value in var 8004
void StoreGameStat()
{
	Var800D = GetGameStat(Var8004);
}

/// @brief Stores the player's steps into LASTRESULT, with the number of times they've surpassed the u16 limit (65, 535) in 0x4000
void StoreStepsGameStat()
{
	u32 steps = GetGameStat(GAME_STAT_STEPS);
	gSpecialVar_LastResult = steps % 65535;
	VarSet(VAR_TEMP_0, steps / 65535);
}

/// @brief Gets the Hall of Fame save time game stat into string buffers 0 and 1. This is needed because the time value is stored as an integer and needs to be converted, with leading zeroes.
void StoreHoFTimeGameStat()
{
	u32 stat = GetGameStat(GAME_STAT_FIRST_HOF_PLAY_TIME);
	u16 hours = stat >> 16;
	u16 minutes = (stat >> 8) & 0xFF;

	// Store formatted hours and minutes into string buffers
	ConvertIntToDecimalStringN(gStringVar1, hours, STR_CONV_MODE_RIGHT_ALIGN, 2); //Hour - 12hr format
	ConvertIntToDecimalStringN(gStringVar2, minutes, STR_CONV_MODE_LEADING_ZEROS, 2); //Minute
}

// Checks if the player has enough money from var 0x8004 and stores the result in 0x800D (LASTRESULT)
void CheckMoneyFromVar()
{
	Var800D = Var8004 <= GetMoney(&gSaveBlock1->money);
}

// Removes money from the player, based on the value in var 0x8004
void RemoveMoneyFromVar()
{
	RemoveMoney(&gSaveBlock1->money, Var8004);
}

void InitializeTreasureBeach()
{
	// Collect random treasure flags
	int treasureFlags[61] = {
		// Group A - 60% (9)
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_ULTRABALL2,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_HYPER_POTION3,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_POKECHIP3,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_POKECHIP4,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_STARDUST2,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_TINYMUSHROOM3,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_TINYMUSHROOM4,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_PEARL2,
		HIDDEN_ITEM_RECURRING60_TREASURE_BEACH_STARDUST4,
		// Group B - 30% (34)
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_REVIVE1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_HP_UP,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_PROTEIN,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_IRON,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_CARBOS,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_CALCIUM,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_BOTTLECAP1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_BOTTLECAP2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_ZINC,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_PP_UP,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_HYPER_POTION1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_ULTRABALL1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_QUICK_BALL,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_DUSK_BALL,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_TIMER_BALL,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_ULTRABALL3,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_HYPER_POTION4,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_REVIVE2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_POKECHIP2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_TINYMUSHROOM1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_BALMMUSHROOM,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_NUGGET1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_RARE_BONE1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_TINYMUSHROOM2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_STARDUST3,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_PEARL1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_FULL_RESTORE2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_POKECHIP5,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_POKECHIP6,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_ULTRABALL4,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_PEARLSTRING,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_BIGPEARL2,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_BIGMUSHROOM1,
		HIDDEN_ITEM_RECURRING30_TREASURE_BEACH_RARE_BONE3,
		// Group C - 10% (18)
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_COMET_SHARD,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_BIG_NUGGET,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_STARDUST1,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_MAX_REVIVE,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_RARE_CANDY,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_GOLD_BOTTLECAP,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_LUXURY_BALL,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_HYPER_POTION2,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_POKECHIP_1,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_NUGGET2,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_BOTTLECAP3,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_FULL_RESTORE1,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_PEARL3,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_BIGPEARL1,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_STARPIECE1,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_BIGMUSHROOM2,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_STARPIECE2,
		HIDDEN_ITEM_RECURRING10_TREASURE_BEACH_RARE_BONE2,
	};

	// All flags set by default (i.e. item cannot be found)
	for (int i = 0; i < 61; i++) {
		FlagSet(FLAG_HIDDEN_ITEMS_START + treasureFlags[i]);
	}

	// Pick 5 randomly to clear (i.e. make available), to start
	for (int i = 0; i < 5; ++i) {
		int randomIndex = Random() % 61;
		FlagClear(FLAG_HIDDEN_ITEMS_START + treasureFlags[randomIndex]);
	}
}

// Caps for boss's next ace
const u8 EqualLevelCaps_Standard[] =
{
	13, // Before Gym 1's badge
	15, // Before Irene
	17, // Before Casey
	20, // Before Gym 2's badge
	26, // Before Gym 3's badge
	33, // Before Gym 4's badge
	37, // Before Ronald
	41, // Before Gym 5's badge
	47, // Before Gym 6's badge
	50, // Before Kurtis
	58, // Before Gym 7's badge & Carnelidge events
	63, // Before Gym 8's badge
	66, // Before Elite Four
	74, // Before Champion
	100, // Postgame
};

const u8 EqualLevelCaps_HardModes[] =
{
	13, // Before Gym 1's badge
	16, // Before Irene
	17, // Before Casey
	21, // Before Gym 2's badge
	27, // Before Gym 3's badge
	34, // Before Gym 4's badge
	39, // Before Ronald
	42, // Before Gym 5's badge
	48, // Before Gym 6's badge
	52, // Before Kurtis
	58, // Before Gym 7's badge & Carnelidge events
	64, // Before Gym 8's badge
	68, // Before Elite Four
	75, // Before Champion
	100, // Postgame
};

extern u8 GetCurrentLevelCap(void);
u8 GetCurrentLevelCap()
{
	u8 cap = 0;

	if (FlagGet(FLAG_DEFEATED_TERRENCE))
		cap++;
	if (FlagGet(FLAG_BEAT_IRENE_IN_RUBARR_DESERT))
		cap++;
	if (FlagGet(0x255)) // Torma Cave Casey
		cap++;
	if (FlagGet(FLAG_DEFEATED_STELLA))
		cap++;
	if (FlagGet(FLAG_DEFEATED_RAINE))
		cap++;
	if (FlagGet(FLAG_DEFEATED_CHANCE))
		cap++;
	if (FlagGet(0x41)) // Ronald
		cap++;
	if (FlagGet(FLAG_DEFEATED_CASEY))
		cap++;
	if (FlagGet(FLAG_DEFEATED_ABBY))
		cap++;
	if (FlagGet(0x4A)) // Kurtis
		cap++;
	if (FlagGet(0x273)) // Carnelidge Volcano Story
		cap++;
	if (FlagGet(FLAG_DEFEATED_DENNIS_AND_DEE))
		cap++;
	if (FlagGet(0x72)) // Rival on Victory Road
		cap++;
	if (FlagGet(FLAG_DEFEATED_CHAMPION_SELENE))
		cap++;

	u8 levelCap = 0;
	if (VarGet(VAR_DIFFICULTY_SETTING) >= OPTIONS_AMETHYST_HARD_DIFFICULTY) // Hard mode sometimes has raised caps
		levelCap = EqualLevelCaps_HardModes[cap];
	else // Standard
		levelCap = EqualLevelCaps_Standard[cap];

	if (VarGet(VAR_LEVEL_CAPS) == OPTIONS_AMETHYST_EXTRA_HARD_LEVEL_CAPS && !FlagGet(FLAG_SYS_GAME_CLEAR))
		levelCap = levelCap - 2; // Extra hard level cap reduced by 2 if game isn't beaten

	return levelCap;
}

void GetLevelCapIntoLastResult(void)
{
	gSpecialVar_LastResult = GetCurrentLevelCap();
}

/// @brief Sets LastResult to TRUE if all pokemon in the party have the type set in Var4005
void CheckIfPartyIsSameType(void)
{
	gSpecialVar_LastResult = TRUE;

	for (u8 i = 0; i < PARTY_SIZE; i++)
	{
		struct Pokemon* mon = &gPlayerParty[i];
		u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);

		if (species != SPECIES_NONE && species != SPECIES_EGG)
		{
			u8 type1 = GetMonType(mon, 0);
			u8 type2 = GetMonType(mon, 1);
			if (type1 != VarGet(VAR_TEMP_5) && type2 != VarGet(VAR_TEMP_5))
			{
				gSpecialVar_LastResult = FALSE;
				break;
			}
		}
	}
}

/// @brief Cleanup vars used by various scripts (any multichoice). Not doing so can result in crashes when using Fly after accessing any multichoice. 
void ClearOutCalculationVars(void)
{
	VarSet(VAR_TEMP_0, 0x0);
	VarSet(VAR_TEMP_1, 0x0);
	VarSet(VAR_TEMP_2, 0x0);
	VarSet(VAR_TEMP_3, 0x0);
	VarSet(VAR_TEMP_4, 0x0);
	VarSet(VAR_TEMP_5, 0x0);
	VarSet(VAR_TEMP_6, 0x0);
	VarSet(VAR_TEMP_7, 0x0);
	VarSet(VAR_TEMP_8, 0x0);
	VarSet(VAR_TEMP_9, 0x0);
	VarSet(VAR_TEMP_A, 0x0);
	VarSet(VAR_TEMP_B, 0x0);
	VarSet(VAR_TEMP_C, 0x0);
	VarSet(VAR_TEMP_D, 0x0);
	VarSet(VAR_0x8000, 0x0);
	VarSet(VAR_0x8001, 0x0);
	VarSet(VAR_0x8002, 0x0);
	VarSet(VAR_0x8003, 0x0);
	VarSet(VAR_0x8004, 0x0);
	VarSet(VAR_0x8005, 0x0);
	VarSet(VAR_0x8006, 0x0);
	VarSet(VAR_0x8007, 0x0);
	VarSet(VAR_0x8008, 0x0);
	VarSet(VAR_0x8009, 0x0);
	VarSet(VAR_0x800A, 0x0);
	VarSet(VAR_0x800B, 0x0);
	VarSet(gSpecialVar_LastResult, 0x0);
}
