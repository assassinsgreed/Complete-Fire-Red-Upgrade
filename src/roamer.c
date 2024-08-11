#include "defines.h"
#include "defines_battle.h"
#include "../include/event_data.h"
#include "../include/event_object_movement.h"
#include "../include/field_player_avatar.h"
#include "../include/overworld.h"
#include "../include/random.h"
#include "../include/region_map.h"
#include "../include/script.h"
#include "../include/pokemon_icon.h"
#include "../include/constants/maps.h"
#include "../include/constants/region_map_sections.h"
#include "../include/constants/species.h"

#include "../include/new/battle_start_turn_start.h"
#include "../include/new/util.h"
#include "../include/new/roamer.h"
#include "../include/new/wild_encounter.h"
/*
roamer.c
	handles roaming pokemon and relevant functions/hooks
*/

//TODO: Do Pokedex area screen / Get icons on the region map

enum
{
	MAP_GRP = 0, // map group
	MAP_NUM = 1, // map number
};

//static u8 sLocationHistory[3][2]; //0x203F3A8
//static u8 sRoamerLocation[2] //0x203F3AE

#define ROAMING_MAP_BANK 3
#define NUM_MAPS_IN_SET 7

#ifndef UNBOUND //Modify this

//WARNING! Make sure there are always at least two maps in a set, or the game may crash when changing maps!

static const u8 sMainlandRoamerLocations[][NUM_MAPS_IN_SET] = //0x8466C58 in FR
{
	{MAP_NUM(ROUTE_1),	MAP_NUM(ROUTE_2),	MAP_NUM(ROUTE_17),  0xFF,   0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_2),	MAP_NUM(ROUTE_1),	MAP_NUM(ROUTE_3),	MAP_NUM(ROUTE_7),   0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_3),	MAP_NUM(ROUTE_2),	MAP_NUM(ROUTE_4),	MAP_NUM(ROUTE_7), MAP_NUM(RUBARR_DESERT), 0xFF, 0xFF},
	{MAP_NUM(ROUTE_4),	MAP_NUM(ROUTE_3),	MAP_NUM(ROUTE_5),	MAP_NUM(ROUTE_13),	MAP_NUM(ROUTE_11_SOUTH),   MAP_NUM(RUBARR_DESERT), 0xFF},
	{MAP_NUM(ROUTE_5),	MAP_NUM(ROUTE_4),	MAP_NUM(ROUTE_11_SOUTH),	MAP_NUM(HELEO_RANCH_EXTERIOR),	MAP_NUM(ROUTE_6),	0xFF,	0xFF},
	{MAP_NUM(ROUTE_6),	MAP_NUM(ROUTE_5),	MAP_NUM(ROUTE_7),	MAP_NUM(ROUTE_8),	MAP_NUM(HELEO_RANCH_EXTERIOR),   MAP_NUM(DAIMYN_CITY), 0xFF},
	{MAP_NUM(ROUTE_7),	MAP_NUM(ROUTE_6),	MAP_NUM(ROUTE_2),	MAP_NUM(ROUTE_3),	MAP_NUM(ROUTE_8),   0xFF, 0xFF},
	{MAP_NUM(ROUTE_8),	MAP_NUM(ROUTE_7),	MAP_NUM(ROUTE_6),	MAP_NUM(DAIMYN_CITY),	0xFF,   0xFF,   0xFF},
	{MAP_NUM(DAIMYN_CITY),	  MAP_NUM(ROUTE_6),	MAP_NUM(ROUTE_8),	MAP_NUM(ROUTE_9),   MAP_NUM(ROUTE_10),   MAP_NUM(DAIMYN_CITY_FACTORY), 0xFF},
	{MAP_NUM(ROUTE_9),  MAP_NUM(DAIMYN_CITY),	MAP_NUM(DAIMYN_CITY_FACTORY),	MAP_NUM(ROUTE_12_EAST),   MAP_NUM(ROUTE_10), MAP_NUM(ROUTE_6), MAP_NUM(ROUTE_8)},
	{MAP_NUM(ROUTE_10), MAP_NUM(DAIMYN_CITY),	MAP_NUM(DAIMYN_CITY_FACTORY),   MAP_NUM(HELEO_RANCH_EXTERIOR), MAP_NUM(ROUTE_11_SOUTH), 0xFF, 0xFF},
	{MAP_NUM(ROUTE_11_SOUTH), MAP_NUM(ROUTE_10),   MAP_NUM(ROUTE_11_NORTH),   0xFF,   0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_11_NORTH), MAP_NUM(ROUTE_11_SOUTH),   0xFF,   0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_12_EAST),	MAP_NUM(ROUTE_12_WEST),	MAP_NUM(ROUTE_9),   0xFF,   0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_13), MAP_NUM(ROUTE_4),   0xFF,   0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_17), MAP_NUM(ROUTE_2),	MAP_NUM(ROUTE_1),   MAP_NUM(ROUTE_18), 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_18), MAP_NUM(ROUTE_17),   0xFF,   0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_24_WEST), MAP_NUM(ROUTE_24_NORTH),   MAP_NUM(ROUTE_11_SOUTH),   0xFF,   0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_24_WEST), MAP_NUM(ROUTE_24_NORTH),   0xFF,   0xFF,   0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Must be present, table termination
};

static const u8 sIslandRoamerLocations[][NUM_MAPS_IN_SET] =
{
	{MAP_NUM(ROUTE_19), MAP_NUM(ROUTE_20), 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_20), MAP_NUM(ROUTE_20), MAP_NUM(ROUTE_21), 0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_21), MAP_NUM(ROUTE_20), MAP_NUM(SECRET_PATH), 0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(SECRET_PATH), MAP_NUM(ROUTE_21), MAP_NUM(ROUTE_22), 0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_22), MAP_NUM(SECRET_PATH), MAP_NUM(ROUTE_23), 0xFF, 0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_23), MAP_NUM(ROUTE_22), 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // Must be present, table termination
};

#else //For Pokemon Unbound

static const u8 sRoamerLocations[][NUM_MAPS_IN_SET] =
{
	{MAP_NUM(ROUTE_2),	  MAP_NUM(ROUTE_3),	   MAP_NUM(ROUTE_4),           0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_2),	  MAP_NUM(ROUTE_3),	   MAP_NUM(ROUTE_4),           MAP_NUM(ROUTE_5),  0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_6),    MAP_NUM(ROUTE_7),    MAP_NUM(ROUTE_8),           0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_6),    MAP_NUM(ROUTE_7),    MAP_NUM(ROUTE_9),           MAP_NUM(ROUTE_10), MAP_NUM(AUBURN_WATERWAY_B), 0xFF, 0xFF},
	{MAP_NUM(ROUTE_9),    MAP_NUM(ROUTE_10),   MAP_NUM(AUBURN_WATERWAY_B), 0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_9),    MAP_NUM(ROUTE_10),   MAP_NUM(ROUTE_11),          0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_11),   MAP_NUM(ROUTE_12),   0xFF,                       0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_12),   MAP_NUM(ROUTE_14_B), MAP_NUM(ROUTE_14_C),        MAP_NUM(ROUTE_6),  0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_16),   MAP_NUM(ROUTE_17),   0xFF,                       0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(ROUTE_16),   MAP_NUM(ROUTE_18_B),                0xFF,                       0xFF,              0xFF, 0xFF, 0xFF},
	{MAP_NUM(COOTES_BOG), MAP_NUM(MAGNOLIA_FIELDS), 0xFF,                  0xFF,              0xFF, 0xFF, 0xFF},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

#endif

//This file's functions:
static void CreateInitialRoamerMon(u16 species, u8 level, bool8 allowedOnLand, bool8 allowedOnWater);
static bool8 IsRoamerAt(u8 mapGroup, u8 mapNum, u8 id);
static void CreateRoamerMonInstance(u8 id);

void ClearRoamersData(void)
{
	memset(gRoamers, 0, sizeof(struct Roamer) * MAX_NUM_ROAMERS);
}

static void CreateInitialRoamerMon(u16 species, u8 level, bool8 allowedOnLand, bool8 allowedOnWater)
{
	int i;
	struct Roamer roamer;

	if (species == 0xFFFF) //FRLGSytle
	{
		switch(GetStarterChoice()) { //0x80CBDB0
			case SPECIES_BULBASAUR:
				species = SPECIES_ENTEI;
				break;
			case SPECIES_CHARMANDER:
				species = SPECIES_SUICUNE;
				break;
			default:
				species = SPECIES_RAIKOU;
		}
	}

	if (IsSpeciesRoaming(species)) //Only one of each species may roam at a time.
	{
		gSpecialVar_LastResult = 0;
		return;
	}

	CreateMon(&gEnemyParty[0], species, level, 0x20, 0, 0, 0, 0);

	#ifdef CREATE_ROAMER_WITH_X_PERFECT_IVS
	{
		u8 numPerfectStats = 0;
		u8 perfect = 31;
		bool8 perfectStats[NUM_STATS] = {0};

		//Count pre-existing perfect stats
		for (int i = 0; i < NUM_STATS; ++i)
		{
			if (GetMonData(&gEnemyParty[0], MON_DATA_HP_IV + i, NULL) >= 31)
			{
				perfectStats[i] = TRUE;
				++numPerfectStats;
			}
		}

		//Add more perfect stats up to max
		while (numPerfectStats < MathMin(CREATE_ROAMER_WITH_X_PERFECT_IVS, NUM_STATS)) //Error prevention
		{
			u8 statId = Random() % NUM_STATS;
			if (!perfectStats[statId]) //Must be unique
			{
				perfectStats[statId] = TRUE;
				++numPerfectStats;
				SetMonData(&gEnemyParty[0], MON_DATA_HP_IV + statId, &perfect);
			}
		}
		
		HealMon(&gEnemyParty[0]);
	}
	#endif

	roamer.level = level;
	roamer.status = 0;
	roamer.ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS, NULL);
	roamer.personality = gEnemyParty[0].personality;
	roamer.species = species;
	roamer.hp = gEnemyParty[0].hp;
	roamer.canAppearOnLand = allowedOnLand;
	roamer.canAppearOnWater = allowedOnWater;
	roamer.location[MAP_GRP] = ROAMING_MAP_BANK;
	roamer.location[MAP_NUM] =
		species == SPECIES_ZERAORA ?
			sIslandRoamerLocations[Random() % (ARRAY_COUNT(sIslandRoamerLocations) - 1)][0] :
			sMainlandRoamerLocations[Random() % (ARRAY_COUNT(sMainlandRoamerLocations) - 1)][0];

	for (i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		if (gRoamers[i].species == SPECIES_NONE) //Fill in empty spot
		{
			gRoamers[i] = roamer;
			break;
		}
	}

	if (i == MAX_NUM_ROAMERS)
		gSpecialVar_LastResult = 0; //Too many roamers
	else
		gSpecialVar_LastResult = 1; //Success
}

// Inputs:
//		Var8000: Species
//		Var8001: Level
//		Var8002: 0x0 = Roamer Not Allowed On Land
//		Var8003: 0x0 = Roamer Not Allowed On Water
// Returns: To LastResult 0 if failed.
void sp129_InitRoamer(void)
{
	#ifdef FRLG_ROAMING
		CreateInitialRoamerMon(0xFFFF, 50, TRUE, TRUE);
	#else
		CreateInitialRoamerMon(Var8000, Var8001, Var8002, Var8003);
	#endif
}

void UpdateLocationHistoryForRoamers(void)
{
	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		struct Roamer* roamer = &gRoamers[i];

		if (roamer->species != SPECIES_NONE)
		{
			roamer->locationHistory[2][MAP_GRP] = roamer->locationHistory[1][MAP_GRP];
			roamer->locationHistory[2][MAP_NUM] = roamer->locationHistory[1][MAP_NUM];

			roamer->locationHistory[1][MAP_GRP] = roamer->locationHistory[0][MAP_GRP];
			roamer->locationHistory[1][MAP_NUM] = roamer->locationHistory[0][MAP_NUM];

			roamer->locationHistory[0][MAP_GRP] = gSaveBlock1->location.mapGroup;
			roamer->locationHistory[0][MAP_NUM] = gSaveBlock1->location.mapNum;
		}
	}
}

void RoamersMoveToOtherLocationSet(void)
{
	u8 mapNum = 0;

	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		struct Roamer* roamer = &gRoamers[i];

		if (roamer->species != SPECIES_NONE)
		{
			roamer->location[MAP_GRP] = ROAMING_MAP_BANK;

			while (TRUE)
			{
				mapNum =
					roamer->species == SPECIES_ZERAORA ?
						sIslandRoamerLocations[Random() % (ARRAY_COUNT(sIslandRoamerLocations) - 1)][0] :
						sMainlandRoamerLocations[Random() % (ARRAY_COUNT(sMainlandRoamerLocations) - 1)][0];
				if (roamer->location[MAP_NUM] != mapNum)
				{
					roamer->location[MAP_NUM] = mapNum;
					break;
				}
			}
		}
	}
}

void RoamersMove(void)
{
	u8 locSet = 0;

	if ((Random() % 16) == 0)
	{
		RoamersMoveToOtherLocationSet();
	}
	else
	{
		for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
		{
			struct Roamer* roamer = &gRoamers[i];

			if (roamer->species != SPECIES_NONE)
			{
				u8 count = roamer->species == SPECIES_ZERAORA ? (ARRAY_COUNT(sIslandRoamerLocations) - 1) : (ARRAY_COUNT(sMainlandRoamerLocations) - 1);
				while (locSet < count)
				{
					u8 location = roamer->species == SPECIES_ZERAORA ? sIslandRoamerLocations[locSet][0] : sMainlandRoamerLocations[locSet][0];
					if (roamer->location[MAP_NUM] == location)
					{
						u8 mapNum;
						while (TRUE)
						{
							mapNum = roamer->species == SPECIES_ZERAORA ? sIslandRoamerLocations[locSet][Random() % NUM_MAPS_IN_SET] : sMainlandRoamerLocations[locSet][Random() % NUM_MAPS_IN_SET];
							if (!(roamer->locationHistory[2][MAP_GRP] == ROAMING_MAP_BANK && roamer->locationHistory[2][MAP_NUM] == mapNum) && mapNum != 0xFF)
								break;
						}
						roamer->location[MAP_NUM] = mapNum;
						break;
					}
					locSet++;
				}
			}
		}
	}
}

static bool8 IsRoamerAt(u8 mapGroup, u8 mapNum, u8 id)
{
	struct Roamer* roamer = &gRoamers[id];

	return roamer->species != SPECIES_NONE && mapGroup == roamer->location[MAP_GRP] && mapNum == roamer->location[MAP_NUM];
}

static void CreateRoamerMonInstance(u8 id)
{
	struct Pokemon* mon = &gEnemyParty[0];
	struct Roamer* roamer = &gRoamers[id];

	ZeroEnemyPartyMons();
	CreateMonWithIVsPersonality(mon, roamer->species, roamer->level, roamer->ivs, roamer->personality);
	mon->condition = roamer->status;
	mon->hp = roamer->hp;
}

bool8 TryStartRoamerEncounter(u8 environment)
{
	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		if (IsRoamerAt(gSaveBlock1->location.mapGroup, gSaveBlock1->location.mapNum, i) && (Random() % 4) == 0)
		{
			switch (environment) {
				case ENCOUNTER_TYPE_LAND:
					if (!gRoamers[i].canAppearOnLand)
						continue;
					break;
				case ENCOUNTER_TYPE_WATER:
					if (!gRoamers[i].canAppearOnWater)
						continue;
					break;
			}

			CreateRoamerMonInstance(i);
			gLastSelectedRoamer = i;
			return TRUE;
		}
	}

	return FALSE;
}

void UpdateFoughtRoamerHPStatus(struct Pokemon* mon)
{
	gRoamers[gLastSelectedRoamer].hp = mon->hp;
	gRoamers[gLastSelectedRoamer].status = mon->condition;

	RoamersMoveToOtherLocationSet();
}

void SetFoughtRoamerInactive(void)
{
	memset(&gRoamers[gLastSelectedRoamer], 0, sizeof(struct Roamer));
}

//HOOK
void GetRoamerLocation(u8* mapGroup, u8* mapNum, u8 id)
{
	*mapGroup = gRoamers[id].location[MAP_GRP];
	*mapNum = gRoamers[id].location[MAP_NUM];
}

bool8 IsSpeciesRoaming(u16 species)
{
	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		if (gRoamers[i].species == species)
			return TRUE;
	}

	return FALSE;
}

void GetMapGroupAndMapNumOfRoamer(u16 species, u8* mapGroup, u8* mapNum)
{
	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		if (gRoamers[i].species == species)
		{
			*mapGroup = gRoamers[i].location[MAP_GRP];
			*mapNum = gRoamers[i].location[MAP_NUM];
		}
	}
}

void BattleSetup_StartRoamerBattle(void)
{
	ScriptContext2_Enable();
	FreezeEventObjects();
	StopPlayerAvatar();
	gMain.savedCallback = CB2_EndWildBattle;
	gBattleTypeFlags = BATTLE_TYPE_ROAMER;
	CreateBattleStartTask(GetWildBattleTransition(), GetMUS_ForBattle());
	IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
	IncrementGameStat(GAME_STAT_WILD_BATTLES);
}


/*static const union AffineAnimCmd sSpriteAffineAnim_RegionMapRoamer[] =
{
	AFFINEANIMCMD_FRAME(-128, -128, 0, 1), //Half size
	AFFINEANIMCMD_END,
};

static const union AffineAnimCmd* const sSpriteAffineAnimTable_RegionMapRoamer[] =
{
	sSpriteAffineAnim_RegionMapRoamer,
};*/

extern const u16 sMapSectionTopLeftCorners[][2];
extern const u16 sMapSectionDimensions[][2];
void CreateTownMapRoamerSprites(void)
{
	if (GetSelectedRegionMap() != 0 || FlagGet(FLAG_IN_THE_EMPTY_WORLD))
		return; //Roaming only tracked on the main map, or in the empty world

	for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
	{
		//FlagSet(FLAG_SYS_SEVII_MAP_123); //For debugging
		if (gRoamers[i].species != SPECIES_NONE)
		{
			LoadMonIconPalettes();
			u8 mapGroup = gRoamers[i].location[MAP_GRP];
			u8 mapNum = gRoamers[i].location[MAP_NUM];
			const struct MapHeader* mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
			u8 regionMapSecId = mapHeader->regionMapSectionId - (MAPSEC_DYNAMIC + 1);

			s16 x = 8 * sMapSectionTopLeftCorners[regionMapSecId][0];
			s16 y = 8 * sMapSectionTopLeftCorners[regionMapSecId][1];

			if (sMapSectionDimensions[regionMapSecId][0] > 1)
				x += 4 * sMapSectionDimensions[regionMapSecId][0];
			if (sMapSectionDimensions[regionMapSecId][1] > 1)
				y += 4 * sMapSectionDimensions[regionMapSecId][1];

			u8 spriteId = CreateMonIcon(gRoamers[i].species, SpriteCB_PokeIcon, x + 36, y + 36 - 8, 0, gRoamers[i].personality, FALSE);
			if (spriteId < MAX_SPRITES)
			{
				struct Sprite* sprite = &gSprites[spriteId];
			
				sprite->oam.priority = 2;
				sprite->invisible = TRUE;
				/*sprite->oam.affineMode = ST_OAM_AFFINE_NORMAL;
				sprite->affineAnims = sSpriteAffineAnimTable_RegionMapRoamer;
				CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, sprite->oam.affineMode);
				InitSpriteAffineAnim(sprite);*/
			}
		}
	}
}

void DestroyTownMapRoamerSprites(void)
{
	u32 i, j;
	
	for (i = 0; i < MAX_SPRITES; ++i)
	{
		for (j = 0; j < MAX_NUM_ROAMERS; ++j)
		{
			if (gRoamers[j].species != SPECIES_NONE
			&&  (void*) gSprites[i].images == (void*) GetMonIconTiles(gRoamers[j].species, FALSE))
			{
				FreeSpriteOamMatrix(&gSprites[i]);
				DestroyMonIcon(&gSprites[i]);
			}
		}
	}
}

void HideOrShowTownMapRoamerSprites(bool8 invisible)
{
	u32 i, j;

	for (i = 0; i < MAX_SPRITES; ++i)
	{
		if (gSprites[i].inUse)
		{
			for (j = 0; j < MAX_NUM_ROAMERS; ++j)
			{
				if (gRoamers[j].species != SPECIES_NONE
				&&  (void*) gSprites[i].images == (void*) GetMonIconTiles(gRoamers[j].species, FALSE))
				{
					gSprites[i].invisible = invisible;
				}
			}
		}
	}
}
