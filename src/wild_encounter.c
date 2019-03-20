#include "defines.h"
#include "helper_functions.h"

#define TILE_FLAG_ENCOUNTER_TILE 1
#define TILE_FLAG_SURFABLE 2
#define TILE_FLAG_WILD_DOUBLE 4
#define TILE_FLAG_SHAKING 8

//Do shaking grass/dust clouds/water ripples
//Chain Fishing

struct EncounterRate
{
	u32 randomNum;
	u16 previousMetatileBehavior;
	u16 rateBonus;
	u8 maxNoEncounterStepCounter;
	u8 abilityRateModifier;
	u16 firstMonHeldItem;
};

extern struct EncounterRate gEncounterRate;

extern const struct WildPokemonHeader gWildMonMorningHeaders[];
extern const struct WildPokemonHeader gWildMonEveningHeaders[];
extern const struct WildPokemonHeader gWildMonNightHeaders[];
extern const struct SwarmData gSwarmTable[];

extern u16 GetMUS_ForBattle(void);
extern void BuildTrainerPartySetup(void);

u8 ChooseWildMonLevel(const struct WildPokemon* wildPokemon);
const struct WildPokemonHeader* GetCurrentMapWildMonHeaderId(void);
const struct WildPokemonHeader* GetCurrentMapWildMonDaytimeHeader(void);
u8 PickWildMonNature(void);
void CreateWildMon(u16 species, u8 level, u8 monHeaderIndex, bool8 purgeParty);
bool8 TryGenerateWildMon(const struct WildPokemonInfo* wildMonInfo, u8 area, u8 flags);
static species_t GenerateFishingWildMon(const struct WildPokemonInfo* wildMonInfo, u8 rod);
void FishingWildEncounter(u8 rod);
bool8 DoesCurrentMapHaveFishingMons(void);
bool8 DoWildEncounterRateTest(u32 encounterRate, bool8 ignoreAbility);
bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior);
bool8 DoWildEncounterRateDiceRoll(u16 encounterRate);
void RockSmashWildEncounter(void);
bool8 SweetScentWildEncounter(void);
bool8 IsAbilityAllowingEncounter(u8 level);
bool8 TryGetRandomWildMonIndexByType(const struct WildPokemon* wildMon, u8 type, u8 numMon, u8* monIndex);
bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon* wildMon, u8 type, u8 ability, u8* monIndex);
void DoStandardWildBattle(void);

u8 ChooseWildMonLevel(const struct WildPokemon* wildPokemon)
{
    u8 min;
    u8 max;
    u8 range;
    u8 rand;
	u8 fluteBonus;

    // Make sure minimum level is less than maximum level
    if (wildPokemon->maxLevel >= wildPokemon->minLevel)
    {
        min = wildPokemon->minLevel;
        max = wildPokemon->maxLevel;
    }
    else
    {
        min = wildPokemon->maxLevel;
        max = wildPokemon->minLevel;
    }
    range = max - min + 1;
    rand = Random() % range;
	
	if (FlagGet(FLAG_SYS_BLACK_FLUTE))
	{
		fluteBonus = (Random() % 3 + 1);
		max = MathMin(MAX_LEVEL, max + fluteBonus);
		min = MathMin(MAX_LEVEL, min + fluteBonus);
	}
	else if (FlagGet(FLAG_SYS_WHITE_FLUTE))
	{
		fluteBonus = (Random() % 3 + 1);
		
		if (fluteBonus < max)
			max -= fluteBonus;
		else
			max = 1;
			
		if (fluteBonus < min)
			min -= fluteBonus;
		else
			min = 1;
	}

    // check ability for max level mon
    if (!GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL))
    {
        u8 ability = GetPartyAbility(&gPlayerParty[0]);
        if (ability == ABILITY_HUSTLE || ability == ABILITY_VITALSPIRIT || ability == ABILITY_PRESSURE)
        {
            if (Random() % 2 == 0)
                return max;

            if (rand != 0)
                --rand;
        }
    }

    return min + rand;
}

#define MAP_ALTERING_CAVE ((1 << 8) | 122)

const struct WildPokemonHeader* GetCurrentMapWildMonHeaderId(void)
{
	#ifdef TIME_ENABLED
		u32 i;
		
		const struct WildPokemonHeader* headerTable = NULL;
		
		if (Clock->hour >= TIME_NIGHT_START || Clock->hour < TIME_MORNING_START)
			headerTable = gWildMonNightHeaders;
		else if (Clock->hour < TIME_DAY_START)
			headerTable = gWildMonMorningHeaders;
		else if (Clock->hour >= TIME_EVENING_START)
			headerTable = gWildMonEveningHeaders;
			
		if (headerTable != NULL) //Not Daytime
		{
			for (i = 0; headerTable[i].mapGroup != 0xFF; ++i)
			{
				if (headerTable[i].mapGroup == gSaveBlock1->location.mapGroup
				&&  headerTable[i].mapNum == gSaveBlock1->location.mapNum)
					return &headerTable[i];
			}
		}
	#endif

	return GetCurrentMapWildMonDaytimeHeader();
}

const struct WildPokemonHeader* GetCurrentMapWildMonDaytimeHeader(void)
{
	u32 i;
	
    for (i = 0; gWildMonHeaders[i].mapGroup != 0xFF; ++i)
    {
        const struct WildPokemonHeader* wildHeader = &gWildMonHeaders[i];
		
        if (wildHeader->mapGroup == gSaveBlock1->location.mapGroup
        &&  wildHeader->mapNum   == gSaveBlock1->location.mapNum)
        {
			#ifdef ALTERING_CAVE_ENABLED
            if (gSaveBlock1->location.mapGroup == MAP_GROUP(ALTERING_CAVE)
            &&  gSaveBlock1->location.mapNum == MAP_NUM(ALTERING_CAVE))
            {
                u16 alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
                if (alteringCaveId > 8)
                    alteringCaveId = 0;

                i += alteringCaveId;
            }
			#endif
			
			#ifdef TANOBY_RUINS_ENABLED
			if (!CanEncounterUnownInTanobyRuins()) //A function that returns true if the
				return NULL;					 //Tanoby Key flag has been set.
			#endif								 //If it hasn't, and you're in the ruins, then
												 //return false to indicate no Pokemon can be found.
            return &gWildMonHeaders[i];
        }
    }

    return NULL;
}


u8 PickWildMonNature(void)
{
    //Check Synchronize for a pokemon with the same ability
    if (!GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL)
    &&  GetPartyAbility(&gPlayerParty[0]) == ABILITY_SYNCHRONIZE
    &&  umodsi(Random(), 2) == 0)
    {
        return umodsi(gPlayerParty[0].personality, 25);
    }

    // random nature
    return umodsi(Random(), 25);
}

#define NUM_TANOBY_CHAMBERS 7
void CreateWildMon(u16 species, u8 level, u8 monHeaderIndex, bool8 purgeParty)
{
    u8 enemyMonIndex = 0;
	bool8 checkCuteCharm = TRUE;

	if (purgeParty)
		ZeroEnemyPartyMons();
	else
		enemyMonIndex = 1;
	
    switch (gBaseStats[species].genderRatio) {
		case MON_MALE:
		case MON_FEMALE:
		case MON_GENDERLESS:
			checkCuteCharm = FALSE;
			break;
    }

    if (checkCuteCharm
    && !GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL)
    &&  GetPartyAbility(&gPlayerParty[0]) == ABILITY_CUTECHARM
    &&  umodsi(Random(), 3))
    {
        u16 leadingMonSpecies = gPlayerParty[0].species;
        u32 leadingMonPersonality = gPlayerParty[0].species;
        u8 gender = GetGenderFromSpeciesAndPersonality(leadingMonSpecies, leadingMonPersonality);

        if (gender == MON_FEMALE)
            gender = MON_MALE;
        else if (gender == MON_MALE)
            gender = MON_FEMALE;
		else //Genderless
			goto REGULAR_NATURE_CREATION;

		CreateMonWithGenderNatureLetter(&gEnemyParty[enemyMonIndex], species, level, 32, gender, PickWildMonNature(), 0);
		goto ASSIGN_HIDDEN_ABILITY;
    }
	REGULAR_NATURE_CREATION:
	#ifdef TANOBY_RUINS_ENABLED
		if (species == PKMN_UNOWN)
		{
			u32 personality;
			u8 room = gSaveBlock1->location.mapNum - 0x1B;
			
			if (room >= NUM_TANOBY_CHAMBERS)
				personality = PickWildMonNature();
			else
				personality = GenerateUnownPersonality(gUnownDistributionByChamber[room][monHeaderIndex]);
			
			CreateMonWithNature(&gEnemyParty[enemyMonIndex], species, level, 32, personality);
			goto ASSIGN_HIDDEN_ABILITY;
		}
	#else
		++monHeaderIndex; //So the compiler doesn't complain
	#endif

	CreateMonWithNature(&gEnemyParty[enemyMonIndex], species, level, 32, PickWildMonNature());
	
	ASSIGN_HIDDEN_ABILITY:
	if (FlagGet(HIDDEN_ABILITY_FLAG))
		gEnemyParty[enemyMonIndex].hiddenAbility = TRUE;
}

enum
{
    WILD_AREA_LAND,
    WILD_AREA_WATER,
    WILD_AREA_ROCKS,
    WILD_AREA_FISHING,
};

#define WILD_CHECK_REPEL    0x1
#define WILD_CHECK_KEEN_EYE 0x2

bool8 TryGenerateSwarmMon(u8 level, u8 wildMonIndex, bool8 purgeParty)
{
	int i;
	
	if (VarGet(SWARM_MAP_NAME_VAR) == gCurrentMapName
	&&  umodsi(Random(), 100) < SWARM_CHANCE)
	{
		for (i = 0; gSwarmTable[i].species != 0xFFFF; ++i)
		{
			if (gSwarmTable[i].mapName == gCurrentMapName)
			{
				CreateWildMon(VarGet(SWARM_SPECIES_VAR), level, wildMonIndex, purgeParty);
				return TRUE;
			}
		}
	}

	return FALSE;
}

bool8 TryGenerateWildMon(const struct WildPokemonInfo* wildMonInfo, u8 area, u8 flags)
{
    u8 wildMonIndex = 0;
    u8 level;

	if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_STEEL, ABILITY_MAGNETPULL, &wildMonIndex))
		goto SKIP_INDEX_SEARCH;
	if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
		goto SKIP_INDEX_SEARCH;
			
    switch (area) {
		case WILD_AREA_LAND:
			wildMonIndex = ChooseWildMonIndex_Land();
			break;
		case WILD_AREA_WATER:
			wildMonIndex = ChooseWildMonIndex_WaterRock();
			break;
		case WILD_AREA_ROCKS:
			wildMonIndex = ChooseWildMonIndex_WaterRock();
			break;
    }
	
SKIP_INDEX_SEARCH:

    level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);
	
    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
        return FALSE;
	
    else if (flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
        return FALSE;

	else if (!TryGenerateSwarmMon(level, wildMonIndex, TRUE))
		CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level, wildMonIndex, TRUE);
	
	if (FlagGet(DOUBLE_WILD_BATTLE_FLAG))
	{
		wildMonIndex = 0;

		if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_STEEL, ABILITY_MAGNETPULL, &wildMonIndex))
			goto SKIP_INDEX_SEARCH_2;
		if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
			goto SKIP_INDEX_SEARCH_2;
				
		switch (area) {
			case WILD_AREA_LAND:
				wildMonIndex = ChooseWildMonIndex_Land();
				break;
			case WILD_AREA_WATER:
				wildMonIndex = ChooseWildMonIndex_WaterRock();
				break;
			case WILD_AREA_ROCKS:
				wildMonIndex = ChooseWildMonIndex_WaterRock();
				break;
		}
		
		SKIP_INDEX_SEARCH_2:
		level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);
		if (!TryGenerateSwarmMon(level, wildMonIndex, FALSE))
			CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level, wildMonIndex, FALSE);
	}
	
    return TRUE;
}

static species_t GenerateFishingWildMon(const struct WildPokemonInfo* wildMonInfo, u8 rod)
{
    u8 wildMonIndex = ChooseWildMonIndex_Fishing(rod);
    u8 level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);

    CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level, wildMonIndex, TRUE);
	
	if (FlagGet(DOUBLE_WILD_BATTLE_FLAG))
	{
		u8 wildMonIndex = ChooseWildMonIndex_Fishing(rod);
		u8 level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);
		CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level, wildMonIndex, FALSE);
	}
	
    return wildMonInfo->wildPokemon[wildMonIndex].species;
}

void FishingWildEncounter(u8 rod)
{
	const struct WildPokemonHeader* header = GetCurrentMapWildMonHeaderId();
	
	if (header->fishingMonsInfo == NULL)
		header = GetCurrentMapWildMonDaytimeHeader(); //Existence check done prior
	
    GenerateFishingWildMon(header->fishingMonsInfo, rod);
    IncrementGameStat(GAME_STAT_FISHING_CAPTURES);
    BattleSetup_StartWildBattle();
}

bool8 DoesCurrentMapHaveFishingMons(void)
{
    const struct WildPokemonHeader* header = GetCurrentMapWildMonHeaderId();

	if (header == NULL)
		return FALSE;
	
	if (header->fishingMonsInfo == NULL)
	{
		#ifdef TIME_ENABLED
			header = GetCurrentMapWildMonDaytimeHeader();
			if (header->fishingMonsInfo == NULL)
				return FALSE;
		#else
			return FALSE;
		#endif
	}

    return TRUE;
}


bool8 DoWildEncounterRateTest(u32 encounterRate, bool8 ignoreAbility)
{
    encounterRate *= 16;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
	{
        encounterRate = encounterRate * 80 / 100;
	}
		
	//encounterRate += (gEncounterRate.rateBonus * 16 / 200);
		
	gEncounterRate.firstMonHeldItem = gPlayerParty[0].item;
    //ApplyFluteEncounterRateMod(&encounterRate);
    ApplyCleanseTagEncounterRateMod(&encounterRate);
	
    if (!ignoreAbility && !GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL))
    {
        u32 ability = GetPartyAbility(&gPlayerParty[0]);
		
		switch (ability) {
			case ABILITY_WHITESMOKE:
			case ABILITY_STENCH:
			case ABILITY_QUICKFEET:
				encounterRate /= 2;
				break;
			case ABILITY_ARENATRAP:
			case ABILITY_ILLUMINATE:
			case ABILITY_NOGUARD:
			case ABILITY_SWARM:
				encounterRate *= 2;
				break;
			case ABILITY_SANDVEIL:
				if (GetCurrentWeather() == WEATHER_SANDSTORM)
					encounterRate /= 2;
				break;
			case ABILITY_SNOWCLOAK:
				if (GetCurrentWeather() == WEATHER_STEADY_SNOW)
					encounterRate /= 2;
				break;
		}
            
    }
	
    if (encounterRate > 2880)
        encounterRate = 2880;
	
    return DoWildEncounterRateDiceRoll(encounterRate);
}

bool8 DoWildEncounterRateDiceRoll(u16 encounterRate)
{
    if (Random() % 2880 < encounterRate)
        return TRUE;
    else
        return FALSE;
}

bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior)
{
    const struct WildPokemonHeader* header;
    struct Roamer *roamer;
	bool8 clearDoubleFlag = FALSE;

    if (sWildEncountersDisabled == TRUE)
        return FALSE;

    header = GetCurrentMapWildMonHeaderId();
    if (header == NULL
	||  FlagGet(NO_RANDOM_WILD_ENCOUNTERS_FLAG))
    {
        return FALSE;
    }
    else
    {
        if (MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 4) & TILE_FLAG_ENCOUNTER_TILE)
        { 
		RETRY_LAND_HEADER:
            if (header->landMonsInfo == NULL)
			{
				#ifdef TIME_ENABLED
					header = GetCurrentMapWildMonDaytimeHeader();
					if (header->landMonsInfo == NULL)
						return FALSE;
					goto RETRY_LAND_HEADER;
				#else
					return FALSE;
				#endif
			}
            else if (MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 0) != previousMetaTileBehavior && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(header->landMonsInfo->encounterRate, FALSE) != TRUE)
			{
				IncrementEncounterProbabilityBonus(header->landMonsInfo->encounterRate);
                return FALSE;
			}

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else
            {
                //Try a regular wild land encounter
				if (!FlagGet(DOUBLE_WILD_BATTLE_FLAG) //Flag hasn't already been set by user
				&&  ViableMonCount(gPlayerParty) >= 2
				&&  MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 4) & TILE_FLAG_WILD_DOUBLE
				&&  Random() % 100 < WILD_DOUBLE_RANDOM_CHANCE)
				{
					FlagSet(DOUBLE_WILD_BATTLE_FLAG);
					clearDoubleFlag = TRUE;
				}
				
                if (TryGenerateWildMon(header->landMonsInfo, WILD_AREA_LAND, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }
				
				if (clearDoubleFlag)
					FlagClear(DOUBLE_WILD_BATTLE_FLAG); //Battle didn't start so restart the flag

				IncrementEncounterProbabilityBonus(header->landMonsInfo->encounterRate);
                return FALSE;
            }
        }
        else if (MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 4) & TILE_FLAG_SURFABLE
             &&  TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
        {
		RETRY_WATER_HEADER:
            if (header->waterMonsInfo == NULL)
			{
                #ifdef TIME_ENABLED
					header = GetCurrentMapWildMonDaytimeHeader();
					if (header->waterMonsInfo == NULL)
						return FALSE;
					goto RETRY_WATER_HEADER;
				#else
					return FALSE;
				#endif
			}
            else if (previousMetaTileBehavior != MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 0) && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(header->waterMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else // try a regular surfing encounter
            {
				if (!FlagGet(DOUBLE_WILD_BATTLE_FLAG) //Flag hasn't already been set by user
				&&  ViableMonCount(gPlayerParty) >= 2
				&&  MetatileBehavior_GetLowerBytes(currMetaTileBehavior, 4) & TILE_FLAG_WILD_DOUBLE
				&&  Random() % 100 < WILD_DOUBLE_RANDOM_CHANCE)
				{
					FlagSet(DOUBLE_WILD_BATTLE_FLAG);
					clearDoubleFlag = TRUE;
				}
				
                if (TryGenerateWildMon(header->waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }
				
				if (clearDoubleFlag)
					FlagClear(DOUBLE_WILD_BATTLE_FLAG); //Battle didn't start so restart the flag

                return FALSE;
            }
        }
    }

    return FALSE;
}

bool8 CheckStandardWildEncounter(u16 metatileBehavior)
{
    if (StandardWildEncounter(metatileBehavior, gEncounterRate.previousMetatileBehavior) == TRUE)
    {
		gEncounterRate.rateBonus = 0;
		gEncounterRate.maxNoEncounterStepCounter = 0;
        gEncounterRate.previousMetatileBehavior = MetatileBehavior_GetLowerBytes(metatileBehavior, 0);
        return TRUE;
    }

    gEncounterRate.previousMetatileBehavior = MetatileBehavior_GetLowerBytes(metatileBehavior, 0);
    return FALSE;
}

void RockSmashWildEncounter(void)
{
    const struct WildPokemonHeader* header = GetCurrentMapWildMonHeaderId();

    if (header != NULL)
    {
        const struct WildPokemonInfo* wildPokemonInfo = header->rockSmashMonsInfo;
		
	RETRY_ROCK_HEADER:
        if (wildPokemonInfo == NULL)
        {
			#ifdef TIME_ENABLED
				header = GetCurrentMapWildMonDaytimeHeader();
				if (header->rockSmashMonsInfo == NULL)
					gSpecialVar_LastResult = FALSE;
				else
					goto RETRY_ROCK_HEADER;
			#else
				gSpecialVar_LastResult = FALSE;
			#endif
        }
        else if (DoWildEncounterRateTest(wildPokemonInfo->encounterRate, 1) == TRUE
              && TryGenerateWildMon(wildPokemonInfo, 2, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
        {
            BattleSetup_StartWildBattle();
            gSpecialVar_LastResult = TRUE;
        }
        else
        {
            gSpecialVar_LastResult = FALSE;
        }
    }
    else
    {
        gSpecialVar_LastResult = FALSE;
    }
}

bool8 SweetScentWildEncounter(void)
{
    s16 x, y;
	const struct WildPokemonHeader* header;

	#ifdef SWEET_SCENT_ONLY_IN_CLEAR_WEATHER
		switch (GetCurrentWeather()) {
			case WEATHER_NONE:
			case WEATHER_CLOUDS:
			case WEATHER_SUNNY:
			case WEATHER_SHADE:
			case WEATHER_DROUGHT:
				break;
			default:
				return FALSE;
		}
	#endif

    PlayerGetDestCoords(&x, &y);
    header = GetCurrentMapWildMonHeaderId();
    if (header != NULL)
    {
        if (MapGridGetMetatileField(x, y, 4) == 1)
        {
            if (header->landMonsInfo == NULL)
            {
			RETRY_LAND_HEADER:
				#ifdef TIME_ENABLED
					header = GetCurrentMapWildMonDaytimeHeader();
					if (header->landMonsInfo == NULL)
						return FALSE;
					goto RETRY_LAND_HEADER;
				#else
					return FALSE;
				#endif
			}

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            TryGenerateWildMon(header->landMonsInfo, WILD_AREA_LAND, 0);

            BattleSetup_StartWildBattle();
            return TRUE;
        }
        else if (MapGridGetMetatileField(x, y, 4) == 2)
        {
		RETRY_WATER_HEADER:
            if (header->waterMonsInfo == NULL)
            {
                #ifdef TIME_ENABLED
					header = GetCurrentMapWildMonDaytimeHeader();
					if (header->waterMonsInfo == NULL)
						return FALSE;
					goto RETRY_WATER_HEADER;
				#else
					return FALSE;
				#endif
			}

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            TryGenerateWildMon(header->waterMonsInfo, WILD_AREA_WATER, 0);
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }

    return FALSE;
}

 bool8 IsAbilityAllowingEncounter(u8 level)
{
    u8 ability;

    if (GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL))
        return TRUE;

    ability = GetPartyAbility(&gPlayerParty[0]);
    if (ability == ABILITY_KEENEYE || ability == ABILITY_INTIMIDATE)
    {
        u8 playerMonLevel = gPlayerParty[0].level;
        if (playerMonLevel > 5 && level <= playerMonLevel - 5 && !umodsi(Random(), 2))
            return FALSE;
    }

    return TRUE;
}

bool8 TryGetRandomWildMonIndexByType(const struct WildPokemon* wildMon, u8 type, u8 numMon, u8* monIndex)
{
    u8 validIndexes[numMon]; // variable length array, an interesting feature
    u8 i, validMonCount;

    for (i = 0; i < numMon; i++)
        validIndexes[i] = 0;

    for (validMonCount = 0, i = 0; i < numMon; i++)
    {
        if (gBaseStats[wildMon[i].species].type1 == type || gBaseStats[wildMon[i].species].type2 == type)
            validIndexes[validMonCount++] = i;
    }

    if (validMonCount == 0 || validMonCount == numMon)
        return FALSE;

    *monIndex = validIndexes[umodsi(Random(), validMonCount)];
    return TRUE;
}

bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon* wildMon, u8 type, u8 ability, u8* monIndex)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, NULL))
        return FALSE;
    else if (GetPartyAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (umodsi(Random(), 2) != 0)
        return FALSE;

    return TryGetRandomWildMonIndexByType(wildMon, type, LAND_WILD_COUNT, monIndex);
}

void DoStandardWildBattle(void)
{
    ScriptContext2_Enable();
    FreezeEventObjects();
    sub_805C780();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
	
    if (FlagGet(DOUBLE_WILD_BATTLE_FLAG))
    {
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
		
		if (FlagGet(TAG_BATTLE_FLAG))
		{
			gBattleTypeFlags |=  BATTLE_TYPE_INGAME_PARTNER;
		}
    }	
	
    CreateBattleStartTask(GetWildBattleTransition(), GetMUS_ForBattle());
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}