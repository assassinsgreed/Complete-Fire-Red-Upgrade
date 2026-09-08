#include "defines.h"
#include "../include/random.h"
#include "../include/constants/abilities.h"
#include "../include/constants/items.h"

#include "../include/new/ability_tables.h"
#include "../include/new/damage_calc.h"
#include "../include/new/evolution.h"
#include "../include/new/frontier.h"
#include "../include/new/build_pokemon.h"
#include "../include/new/catching.h"
#include "../include/new/mega.h"
#include "../include/new/util.h"
#include "../include/money.h"
#include "../include/pokemon_storage_system.h"
#include "../include/string_util.h"
#include "../include/text.h"
#include "../include/new/pokemon_storage_system.h"

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
// Their addresses come from DPE's offsets.ini via BPRE.ld, so a rebuilt base ROM cannot silently
// move them out from under this file - see SyncRegionalDexTables in scripts/make.py.
extern const u16 gRegionalDexTableStandard[];
extern const u16 gRegionalDexTableDivergent[];

const u16* GetRegionalDexSpeciesTable(bool8 divergent, u16* count)
{
	const u16* table = divergent ? gRegionalDexTableDivergent : gRegionalDexTableStandard;

	*count = table[0];
	return &table[1];
}

// A species' position in a dex, or 0 if not in the dex doesn't list it.
// Used to ensure divergent mons show the right dex number.
static u16 GetPositionInRegionalDex(u16 dexNum, bool8 divergent)
{
	u16 count;
	const u16* speciesTable = GetRegionalDexSpeciesTable(divergent, &count);

	for (u32 i = 0; i < count; ++i)
	{
		if (SpeciesToNationalPokedexNum(speciesTable[i]) == dexNum)
			return i + 1;
	}

	return 0;
}

// The number the summary screen and the Hall of Fame print for a Pokemon.
u16 GetDisplayedPokedexNum(u16 species)
{
	bool8 divergent = FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS);
	u16 dexNum = SpeciesToNationalPokedexNum(species);
	u16 position;

	if (dexNum == 0)
		return 0; // Nothing to search the dexes for

	position = GetPositionInRegionalDex(dexNum, divergent);
	if (position == 0)
		position = GetPositionInRegionalDex(dexNum, !divergent);

	// Species in neither dex (evolutions that don't count towards completion, like Kleavor) appear as 0.
	return position;
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

// Starter mega stones are shared between Standard and Divergent modes
static const u16 sSharedMegaStones[] =
{
	ITEM_VENUSAURITE,
	ITEM_CHARIZARDITE_X,
	ITEM_CHARIZARDITE_Y,
	ITEM_BLASTOISINITE,
	ITEM_SCEPTILITE,
	ITEM_BLAZIKENITE,
	ITEM_SWAMPERTITE,
	ITEM_VENUSAURITE_G,
	ITEM_CHARIZARDITE_G,
	ITEM_BLASTOISINITE_G,
	ITEM_RILLABITE,
	ITEM_CINDERITE,
	ITEM_INTELLEITE,
};

static const u16 sStandardOnlyMegaStones[] =
{
	ITEM_AMPHAROSITE,
	ITEM_SABLENITE,
	ITEM_LOPUNNITE,
	ITEM_MAWILITE,
	ITEM_GARCHOMPITE,
	ITEM_GLALITITE,
	ITEM_LUCARIONITE,
	ITEM_HERACRONITE,
	ITEM_SLOWBRONITE,
	ITEM_SHARPEDONITE,
	ITEM_GALLADITE,
	ITEM_KANGASKHANITE,
	ITEM_GARDEVOIRITE,
	ITEM_GYARADOSITE,
	ITEM_HOUNDOOMINITE,
	ITEM_LAPRASITE,
	ITEM_MELMETALITE,
	ITEM_CORVIKNITE,
	ITEM_ORBEETLITE,
	ITEM_COALOSSITE,
	ITEM_TOXTRICITE,
	ITEM_CENTISKORITE,
	ITEM_HATTERITE,
	ITEM_COPPERITE,
	ITEM_DURALUDITE,
};

static const u16 sDivergentOnlyMegaStones[] =
{
	ITEM_PIDGEOTITE,
	ITEM_BANETTITE,
	ITEM_MANECTITE,
	ITEM_MEDICHAMITE,
	ITEM_AERODACTYLITE,
	ITEM_STEELIXITE,
	ITEM_METAGROSSITE,
	ITEM_PINSIRITE,
	ITEM_ABOMASITE,
	ITEM_SALAMENCITE,
	ITEM_ABSOLITE,
	ITEM_SCIZORITE,
	ITEM_ALAKAZITE,
	ITEM_GENGARITE,
	ITEM_TYRANITARITE,
	ITEM_BEEDRILLITE,
	ITEM_AGGRONITE,
	ITEM_CAMERUPTITE,
	ITEM_ALTARIANITE,
	ITEM_AUDINITE,
	ITEM_BUTTERFRITE,
	ITEM_MACHAMPITE,
	ITEM_GENGARITE_G,
	ITEM_KINGLERITE,
	ITEM_SNORLAXITE,
	ITEM_GARBODORITE,
	ITEM_DREDNAWITE,
	ITEM_APPLITE,
	ITEM_SANDACONDITE,
	ITEM_GRIMMSNARITE,
	ITEM_ALCREMITE,
	ITEM_URSHIFITE,
};

// Sized for whichever mode list is longer (in case future changes make Divergent have less)
#define NUM_MODE_MEGA_STONES (ARRAY_COUNT(sStandardOnlyMegaStones) > ARRAY_COUNT(sDivergentOnlyMegaStones) \
	? ARRAY_COUNT(sStandardOnlyMegaStones) : ARRAY_COUNT(sDivergentOnlyMegaStones))
#define MAX_REQUIRED_MEGA_STONES (ARRAY_COUNT(sSharedMegaStones) + NUM_MODE_MEGA_STONES)

// Appends the stones from the given list that aren't sitting in the bag, returning the new total
static u32 AddMegaStonesMissingFromBag(const u16* stones, u32 numStones, u16* missing, u32 numMissing)
{
	for (u32 i = 0; i < numStones; ++i)
	{
		if (!CheckBagHasItem(stones[i], 1))
			missing[numMissing++] = stones[i];
	}

	return numMissing;
}

// Drops item from the missing list if it's on it, returning how many are still unaccounted for
static u32 RemoveMegaStoneFromMissingList(u16* missing, u32 numMissing, u16 item)
{
	for (u32 i = 0; i < numMissing; ++i)
	{
		if (missing[i] == item)
		{
			missing[i] = missing[--numMissing]; // Order doesn't matter, so backfill from the end
			break;
		}
	}

	return numMissing;
}

bool8 HasEveryMegaStoneForCurrentMode(void)
{
	u16 missing[MAX_REQUIRED_MEGA_STONES];
	const u16* modeStones;
	u32 numModeStones, numMissing;

	if (FlagGet(FLAG_DIVERGENT_WILD_ENCOUNTERS))
	{
		modeStones = sDivergentOnlyMegaStones;
		numModeStones = ARRAY_COUNT(sDivergentOnlyMegaStones);
	}
	else
	{
		modeStones = sStandardOnlyMegaStones;
		numModeStones = ARRAY_COUNT(sStandardOnlyMegaStones);
	}

	numMissing = AddMegaStonesMissingFromBag(sSharedMegaStones, ARRAY_COUNT(sSharedMegaStones), missing, 0);
	numMissing = AddMegaStonesMissingFromBag(modeStones, numModeStones, missing, numMissing);

	// Anything not in the bag can still be held by a Pokemon, so sweep the party and the boxes for it
	for (u32 i = 0; i < PARTY_SIZE && numMissing > 0; ++i)
		numMissing = RemoveMegaStoneFromMissingList(missing, numMissing, GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, NULL));

	for (u32 box = 0; box < TOTAL_BOXES_COUNT && numMissing > 0; ++box)
	{
		for (u32 pos = 0; pos < IN_BOX_COUNT && numMissing > 0; ++pos)
			numMissing = RemoveMegaStoneFromMissingList(missing, numMissing, GetBoxMonDataAt(box, pos, MON_DATA_HELD_ITEM));
	}

	return numMissing == 0;
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

static const u8 sBoxName_Singles[] = {CHAR_S, CHAR_i, CHAR_n, CHAR_g, CHAR_l, CHAR_e, CHAR_s, EOS};
static const u8 sBoxName_Doubles[] = {CHAR_D, CHAR_o, CHAR_u, CHAR_b, CHAR_l, CHAR_e, CHAR_s, EOS};

static bool8 IsSpeciesInList(u16 species, const u16* list, u32 count)
{
	for (u32 i = 0; i < count; ++i)
	{
		if (list[i] == species)
			return TRUE;
	}

	return FALSE;
}

enum FrontierSpreadFormats
{
	FRONTIER_SPREAD_ANY_FORMAT,
	FRONTIER_SPREAD_SINGLES,
	FRONTIER_SPREAD_DOUBLES,
};

// Walks the spread table from a random point so each pick is effectively random, but still
// terminates once every spread has been rejected. usedSpecies rejects repeats and may be NULL
// when they don't matter. Returns 0xFFFF when nothing is left to pick.
static u16 PickRandomFrontierSpread(u8 format, const u16* usedSpecies, u32 numUsed)
{
	u16 start = Random() % gNumFrontierSpreads;

	for (u32 i = 0; i < gNumFrontierSpreads; ++i)
	{
		u16 index = (start + i) % gNumFrontierSpreads;
		const struct BattleTowerSpread* spread = &gFrontierSpreads[index];

		if (format == FRONTIER_SPREAD_SINGLES && !spread->forSingles)
			continue;

		if (format == FRONTIER_SPREAD_DOUBLES && !spread->forDoubles)
			continue;

		if (!IsSpeciesInList(spread->species, usedSpecies, numUsed))
			return index;
	}

	return 0xFFFF;
}

// Overwrites every slot in the box, so whatever was in it is discarded
static void FillBoxWithFrontierSpreads(u8 boxId, u8 format, const u8* boxName)
{
	u16 usedSpecies[IN_BOX_COUNT];
	u32 numUsed = 0;

	for (u32 pos = 0; pos < IN_BOX_COUNT; ++pos)
	{
		struct Pokemon mon;
		u16 index = PickRandomFrontierSpread(format, usedSpecies, numUsed);

		if (index == 0xFFFF) // Ran out of unique species for this format
		{
			ZeroBoxMonAt(boxId, pos);
			continue;
		}

		usedSpecies[numUsed++] = gFrontierSpreads[index].species;
		CreateFrontierMon(&mon, 50, &gFrontierSpreads[index], 0, 0, 0, TRUE);
		SetBoxMonAt(boxId, pos, (struct BoxPokemon*) &mon);
	}

	StringCopy(GetBoxNamePtr(boxId), boxName);
}

/// Stocks the first two PC boxes with random Battle Frontier spreads for the sandbox - 30 Singles
///	legal ones in box 1 and 30 Doubles legal ones in box 2, renaming both boxes to match.
///	Species are unique within a box, but the same species can appear in both.
void FillBoxesWithFrontierSpreads(void)
{
	FillBoxWithFrontierSpreads(0, FRONTIER_SPREAD_SINGLES, sBoxName_Singles);
	FillBoxWithFrontierSpreads(1, FRONTIER_SPREAD_DOUBLES, sBoxName_Doubles);
}

/// Hands the player a random Battle Frontier ready Pokemon for the Wonder Pick (minus legendaries).
///	The script charges for the pick and reports the outcome, so nothing here touches the player's PokeChips.
/// Returns LASTRESULT: TRUE if the Pokemon is received, FALSE if it isn't so the script can refund.
///	        BUFFER1: the name of the Pokemon picked.
///	        Var 0x8000: its species, for the script to show off with showpokepic and cry.
void WonderPickFrontierMon(void)
{
	struct Pokemon mon;
	u16 species;
	u16 index = PickRandomFrontierSpread(FRONTIER_SPREAD_ANY_FORMAT, NULL, 0);

	gSpecialVar_LastResult = FALSE;

	// The script checks for room first, but bailing here too stops a full party from quietly
	// diverting a paid-for pick into the PC, where the script's refund would double up on it
	if (index == 0xFFFF || GetMonData(&gPlayerParty[PARTY_SIZE - 1], MON_DATA_SPECIES, NULL) != SPECIES_NONE)
		return;

	CreateFrontierMon(&mon, 50, &gFrontierSpreads[index], 0, 0, 0, TRUE);

	// Read back off the mon rather than the spread, since aesthetic forms are picked during creation
	species = GetMonData(&mon, MON_DATA_SPECIES, NULL);
	StringCopy(gStringVar1, gSpeciesNames[species]);
	VarSet(VAR_0x8000, species);

	SetMonPokedexFlags(&mon);
	gSpecialVar_LastResult = GiveMonToPlayer(&mon) == MON_GIVEN_TO_PARTY;
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
