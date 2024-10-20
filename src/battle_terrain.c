#include "defines.h"
#include "defines_battle.h"
#include "../include/bg.h"
#include "../include/event_data.h"
#include "../include/evolution_scene.h"
#include "../include/gpu_regs.h"
#include "../include/fieldmap.h"
#include "../include/field_player_avatar.h"
#include "../include/metatile_behavior.h"
#include "../include/overworld.h"
#include "../include/constants/maps.h"
#include "../include/constants/metatile_behaviors.h"
#include "../include/constants/region_map_sections.h"
#include "../include/constants/trainer_classes.h"

#include "../include/new/battle_terrain.h"
#include "../include/new/dns.h"
#include "../include/new/frontier.h"
#include "../include/new/multi.h"
#include "../include/new/overworld.h"
#include "../include/new/util.h"
/*
battle_terrain.c
	functions responsible for checking/loading/removing battle terrain
*/

#define gBattleTerrainTable ((struct BattleBackground*) *((u32*) 0x800F320))
#ifdef NEW_BATTLE_BACKGROUNDS
extern struct BattleBackground gBattleTerrainTableMorning[];
extern struct BattleBackground gBattleTerrainTableEvening[];
extern struct BattleBackground gBattleTerrainTableNight[];
#endif

extern const struct BattleBackground gAttackTerrainTable[];

//This file's functions:
static void LoadBattleBG_EntryOverlay(u8 terrainId);
static u8 TryLoadAlternateAreaTerrain(u8 terrain);

u8 BattleSetup_GetTerrainId(void)
{
	u16 tileBehavior;
	s16 x, y;
	u8 terrain = BATTLE_TERRAIN_PLAIN;

	PlayerGetDestCoords(&x, &y);
	tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

	#ifdef VAR_BATTLE_BG
	if (VarGet(VAR_BATTLE_BG))
		terrain = VarGet(VAR_BATTLE_BG);
	else
	#endif
	{
		//Maybe add check for fishing byte?
		if (MetatileBehavior_IsTallGrass(tileBehavior))
		{
			#ifdef UNBOUND
			if (IsCurrentAreaAutumn())
				terrain = BATTLE_TERRAIN_AUTUMN_GRASS;
			else if (IsCurrentAreaWinter())
				terrain = BATTLE_TERRAIN_SNOW_GRASS;
			else
			#endif
				terrain = BATTLE_TERRAIN_GRASS;
		}
		else if (tileBehavior == MB_VERY_TALL_GRASS) //The old useless function for this check just returns 0
			terrain = BATTLE_TERRAIN_LONG_GRASS;
		else if (MetatileBehavior_IsSandOrShallowFlowingWater(tileBehavior))
			terrain = BATTLE_TERRAIN_SAND;
		else if (MetatileBehavior_IsMountain(tileBehavior))
			if (MAP_IS(CARNELIDGE_VOLCANO_PEAK))
					terrain = BATTLE_TERRAIN_CARNELIDGE_PEAK;
				else 
					terrain = BATTLE_TERRAIN_MOUNTAIN;

		#ifdef BRIDGE_FIX
			else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
			{
				#ifdef UNBOUND
				if (MetatileBehavior_IsFastCurrent(tileBehavior))
					terrain = BATTLE_TERRAIN_POND;
				else
				#endif
				if (MetatileBehavior_IsDeepOrOceanWater(tileBehavior))
					terrain = BATTLE_TERRAIN_WATER;
				else if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
					terrain = BATTLE_TERRAIN_POND;
			}
		#else
			else if (MetatileBehavior_IsDeepOrOceanWater(tileBehavior))
				terrain = BATTLE_TERRAIN_WATER;
			else if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
				terrain = BATTLE_TERRAIN_POND;
		#endif

		switch (GetCurrentMapType()) {
			case MAP_TYPE_UNDERGROUND:
				if (MetatileBehavior_IsIndoorEncounter(tileBehavior))
				{
					terrain = BATTLE_TERRAIN_INSIDE;
					break;
				}

				#ifdef UNBOUND
					terrain = BATTLE_TERRAIN_CAVE;
				#else
					if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
						terrain = BATTLE_TERRAIN_POND;
					else
						terrain = BATTLE_TERRAIN_CAVE;
				#endif
				break;

			case MAP_TYPE_INDOOR:
			case MAP_TYPE_SECRET_BASE:
				terrain = BATTLE_TERRAIN_INSIDE;
				break;

			// case MAP_TYPE_UNDERWATER:
			// 	terrain = BATTLE_TERRAIN_UNDERWATER;
			// 	break;

			case MAP_TYPE_6:
				if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
					terrain = BATTLE_TERRAIN_WATER;
				else
					terrain = BATTLE_TERRAIN_PLAIN;
		}
	}

	terrain = TryLoadAlternateAreaTerrain(terrain); //Loads special BG's if you're surfing
	return terrain;
}

u8 GetBattleTerrainOverride(void)
{
	u8 terrain = gBattleTerrain;

	if (gMain.callback2 == CB2_EvolutionSceneLoadGraphics
	|| gMain.callback2 == CB2_BeginEvolutionScene
	|| gMain.callback2 == CB2_EvolutionSceneUpdate
	|| gMain.callback2 == CB2_TradeEvolutionSceneUpdate)
	{
		bool8 wasRoamerBattle = (gBattleTypeFlags & BATTLE_TYPE_ROAMER) != 0;
		bool8 wasTwoOpponentBattle = IsTwoOpponentBattle();
		gBattleTypeFlags = 0;

		if (wasRoamerBattle)
			gBattleTypeFlags |= BATTLE_TYPE_ROAMER; //Needed otherwise the Roamer may not disappear when caught

		if (wasTwoOpponentBattle)
			gBattleTypeFlags |= (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS); //Needed otherwise the second opponent will battle the player again

		gBattleTerrain = BattleSetup_GetTerrainId();
	}

	if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER))
	{
		#ifdef UNBOUND
			terrain = BATTLE_TERRAIN_INSIDE;
		#else
			terrain = BATTLE_TERRAIN_INSIDE_2;
		#endif
	}
	else if (gBattleTypeFlags & BATTLE_TYPE_POKE_DUDE)
	{
		gBattleTerrain = 0;
		terrain = 0;
	}
	#ifdef VAR_BATTLE_BG
	else if (VarGet(VAR_BATTLE_BG))
	{
		terrain = VarGet(VAR_BATTLE_BG);
	}
	#endif
	else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
	{
		#ifdef OVERWRITE_BG_FOR_LEADER_CHAMPION
			u8 trainerClass = GetFrontierTrainerClassId(gTrainerBattleOpponent_A, 0);
			u8 trainerClassB = GetFrontierTrainerClassId(SECOND_OPPONENT, 1);
			if (trainerClass == CLASS_LEADER || trainerClassB == CLASS_LEADER)
			{
				terrain = BATTLE_TERRAIN_INSIDE_4;
			}
			else if (trainerClass == CLASS_CHAMPION || trainerClassB == CLASS_CHAMPION)
			{
				terrain = BATTLE_TERRAIN_CHAMPION;
			}
			else
		#elif (defined UNBOUND)
			if (MAP_IS(POKEMON_LEAGUE_CHAMP_ROOM))
			{
				terrain = BATTLE_TERRAIN_CHAMPION;
			}
			else
		#endif
			if (GetCurrentMapBattleScene() != 0)
				terrain = GetBattleTerrainByMapScene(GetCurrentMapBattleScene());
			else
				terrain = gBattleTerrain;
	}
	else
	{
		if (GetCurrentMapBattleScene() != 0)
			terrain = GetBattleTerrainByMapScene(GetCurrentMapBattleScene());
		else
			terrain = gBattleTerrain;
	}

	terrain = TryLoadAlternateAreaTerrain(terrain);
	return terrain;
}

void DrawBattleEntryBackground(void)
{
	if (gBattleTypeFlags & BATTLE_TYPE_LINK)
	{
		LZDecompressVram((void*) 0x8E7737C, (void*) (BG_CHAR_ADDR(1)));
		LZDecompressVram((void*) 0x08E77598, (void*) (VRAM + 0x10000));
		LoadCompressedPalette((void*) 0x8E77570, 0x60, 0x20);
		SetBgAttribute(1, BG_ATTR_SCREENSIZE, 1);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(0) | BGCNT_CHARBASE(1) | BGCNT_16COLOR | BGCNT_SCREENBASE(28) | BGCNT_TXT512x256);
        CopyToBgTilemapBuffer(1, (void*) 0x8E77464, 0, 0);
		CopyToBgTilemapBuffer(2, (void*) 0x8E77464, 0, 0);
		CopyBgTilemapBufferToVram(1);
		CopyBgTilemapBufferToVram(2);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        gBattle_BG1_Y = -164;
        gBattle_BG2_Y = -164;
		LoadCompressedSpriteSheetUsingHeap((void*) 0x8248318);
	}
	else
	{
		u8 terrain = GetBattleTerrainOverride();
		LoadBattleBG_EntryOverlay(terrain);
	}
}

void LoadBattleTerrainGfx(u8 terrainId)
{
	struct BattleBackground* table = gBattleTerrainTable;

	if (gTerrainType) //A terrain like Electric Terrain is active
	{
		LZDecompressVram(gAttackTerrainTable[gTerrainType - 1].tileset, (void*) 0x6008000);
		LZDecompressVram(gAttackTerrainTable[gTerrainType - 1].tilemap, (void*) 0x600d000);
		LoadCompressedPalette(gAttackTerrainTable[gTerrainType - 1].palette, 0x20, 0x60);
		return;
	}

	#ifdef NEW_BATTLE_BACKGROUNDS //Load different BGs depending on time of day
		u8 mapType = GetCurrentMapType();
		if (!IsMapTypeIndoors(mapType) && IsMapTypeOutdoors(mapType))
		{
			if (IsMorning())
				table = gBattleTerrainTableMorning;
			else if (IsNightTime())
				table = gBattleTerrainTableNight;
			else if (IsEvening())
				table = gBattleTerrainTableEvening;
		}
	#endif

	LZDecompressVram(table[terrainId].tileset, (void*) 0x6008000);
	LZDecompressVram(table[terrainId].tilemap, (void*) 0x600d000);
	LoadCompressedPalette(table[terrainId].palette, 0x20, 0x60);

	#ifdef DNS_IN_BATTLE
		DNSBattleBGPalFade();
	#endif
}

static void LoadBattleBG_EntryOverlay(u8 terrainId)
{
	struct BattleBackground* table = gBattleTerrainTable;

	#ifdef NEW_BATTLE_BACKGROUNDS //Load different BGs depending on time of day
	u8 mapType = GetCurrentMapType();
	if (!IsMapTypeIndoors(mapType) && IsMapTypeOutdoors(mapType))
	{
		if (IsMorning())
			table = gBattleTerrainTableMorning;
		else if (IsNightTime())
			table = gBattleTerrainTableNight;
		else if (IsEvening())
			table = gBattleTerrainTableEvening;
	}
	#endif

	LZDecompressVram(table[terrainId].entryTileset, (void*) 0x6004000);
	LZDecompressVram(table[terrainId].entryTilemap, (void*) 0x600E000);
}

static u8 TryLoadAlternateAreaTerrain(u8 terrain)
{
#ifdef NEW_BATTLE_BACKGROUNDS
	u16 tileBehavior;
	s16 x, y;
	u8 mapSec = GetCurrentRegionMapSectionId();

	PlayerGetDestCoords(&x, &y);
	tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

	switch (terrain) {
		// case BATTLE_TERRAIN_SNOW_CAVE:
		// 	if (MetatileBehavior_IsIce(tileBehavior))
		// 		terrain = BATTLE_TERRAIN_ICE_IN_CAVE;
		// 	break;
		// case BATTLE_TERRAIN_PLAIN:
		// 	if (IsCurrentAreaAutumn())
		// 		terrain = BATTLE_TERRAIN_AUTUMN_PLAIN;
		// 	else if (IsCurrentAreaWinter())
		// 		terrain = BATTLE_TERRAIN_SNOW_FIELD;
		// 	else if (IsCurrentAreaDesert())
		// 		terrain = BATTLE_TERRAIN_DESERT;
		// 	else if (mapSec == MAPSEC_DEHARA_CITY)
		// 		terrain = BATTLE_TERRAIN_SAND;
		// 	else if (mapSec == MAPSEC_ANTISIS_CITY || mapSec == MAPSEC_ANTISIS_PORT)
		// 		terrain = BATTLE_TERRAIN_ANTISIS_CITY;
		// 	else if (IsCurrentAreaSwamp())
		// 		terrain = BATTLE_TERRAIN_BOG;
		// 	break;
		case BATTLE_TERRAIN_SAND: // Hacky fix for Route 12 West & Calicin Bay which are technically covered in "sand" due to the footprints metabehavior
			if (IsCurrentAreaWinter())
				terrain = BATTLE_TERRAIN_SNOWY;
			else if (IsCurrentAreaHotCave())
				terrain = BATTLE_TERRAIN_SCALDING_SPA;
			break;
		case BATTLE_TERRAIN_CAVE:
			if (MAP_IS(TORMA_CAVE_B1F) || MAP_IS(ROUTE10_CAVE) || MAP_IS(ROUTE13_CAVE_1F))
				terrain = BATTLE_TERRAIN_TORMA;
			else if (MAP_IS(TORMA_CAVE_B2F) || mapSec == MAPSEC_ROUTE_13) // All non B1F caves on Route 13 use the depths background
				terrain = BATTLE_TERRAIN_TORMA_DEPTHS;
			else if (IsCurrentAreaHotCave())
				terrain = BATTLE_TERRAIN_SCALDING_SPA;
			else if (mapSec == MAPSEC_UTEYAN_RUINS || mapSec == MAPSEC_VICTORY_ROAD)
				terrain = BATTLE_TERRAIN_CAVE_UTEYA;
			else if (mapSec == MAPSEC_SEPPIRE_COVE)
			{
				if (MAP_IS(SEPPIRE_COVE_KYOGRE_ROOM))
					terrain = BATTLE_TERRAIN_POND_CAVE_SEPPIRE;
				else
					terrain = BATTLE_TERRAIN_CAVE_SEPPIRE;
			}
			break;
		case BATTLE_TERRAIN_GRASS:
			if (IsCurrentAreaWinter())
				terrain = BATTLE_TERRAIN_SNOWY;
			else if (MetatileBehavior_IsMountain(tileBehavior) || mapSec == MAPSEC_CARNELIDGE_VOLCANO || mapSec == MAPSEC_VICTORY_ROAD)
				terrain = BATTLE_TERRAIN_MOUNTAIN;
			else if (IsCurrentAreaOpenOcean())
				terrain = BATTLE_TERRAIN_SAND;
			else if (mapSec == MAPSEC_VARISI_FOREST)
				terrain = BATTLE_TERRAIN_FOREST;
			else if (mapSec == MAPSEC_PERADON_FOREST)
				terrain = BATTLE_TERRAIN_FOREST_PERADON;
			else if (mapSec == MAPSEC_MIMMETT_JUNGLE)
				terrain = BATTLE_TERRAIN_JUNGLE;
			break;
		case BATTLE_TERRAIN_POND:
			if (MAP_IS(ROUTE17_CAVE_1F) || mapSec == MAPSEC_FORGOTTEN_MANSE)
				terrain = BATTLE_TERRAIN_POND_CAVE;
			else if (mapSec == MAPSEC_TORMA_CAVE || MAP_IS(ROUTE13_CAVE_1F))
				terrain = BATTLE_TERRAIN_POND_CAVE_TORMA;
			else if (mapSec == MAPSEC_SEPPIRE_COVE)
				terrain = BATTLE_TERRAIN_POND_CAVE_SEPPIRE;
			else if (mapSec == MAPSEC_UTEYAN_RUINS || MAP_IS(VICTORY_ROAD_1F))
				terrain = BATTLE_TERRAIN_POND_CAVE_UTEYA;
			break;
		case BATTLE_TERRAIN_PLAIN:
			if (IsCurrentAreaWinter())
				terrain = BATTLE_TERRAIN_SNOWY;
			else if (IsCurrentAreaOpenOcean())
				terrain = BATTLE_TERRAIN_SAND;
			else if (mapSec == MAPSEC_VARISI_FOREST)
				terrain = BATTLE_TERRAIN_FOREST;
			else if (mapSec == MAPSEC_PERADON_FOREST)
				terrain = BATTLE_TERRAIN_FOREST_PERADON;
			else if (MetatileBehavior_IsMountain(tileBehavior) || mapSec == MAPSEC_CARNELIDGE_VOLCANO || mapSec == MAPSEC_VICTORY_ROAD)
			{
				if (MAP_IS(CARNELIDGE_VOLCANO_PEAK))
					terrain = BATTLE_TERRAIN_CARNELIDGE_PEAK;
				else 
					terrain = BATTLE_TERRAIN_MOUNTAIN;
			}
			else if (mapSec == MAPSEC_MIMMETT_JUNGLE)
				terrain = BATTLE_TERRAIN_JUNGLE;
			break;
		case BATTLE_TERRAIN_INSIDE:
			if (mapSec == MAPSEC_FORGOTTEN_MANSE || mapSec == MAPSEC_UTEYAN_RUINS)
				terrain = BATTLE_TERRAIN_SPOOKY;
			else if (MAP_IS(PLUTO_HQ_KURTIS_OFFICE))
				terrain = BATTLE_TERRAIN_PLUTO_LEADER;
			break;
		case BATTLE_TERRAIN_INSIDE_3:	// Battles when the map has the Gym Style battle type set
			if (MAP_IS(TSARVOSA_CITY))
				terrain = BATTLE_TERRAIN_GRASS;
			break;
		case BATTLE_TERRAIN_INSIDE_4:
			terrain = BATTLE_TERRAIN_GYM;
			if (MAP_IS(TSARVOSA_CITY))
				terrain = BATTLE_TERRAIN_GRASS;
			else if (MAP_IS(DAIMYN_RESTAURANT))
				terrain = BATTLE_TERRAIN_INSIDE;
			break;
	}

	// if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
	// {
	// 	switch (terrain) {
	// 		case BATTLE_TERRAIN_CAVE:
	// 			terrain = BATTLE_TERRAIN_WATER_IN_CAVE;
	// 			break;
	// 		case BATTLE_TERRAIN_VOLCANO:
	// 			terrain = BATTLE_TERRAIN_LAVA_IN_VOLCANO;
	// 			break;
	// 		case BATTLE_TERRAIN_FOREST:
	// 			terrain = BATTLE_TERRAIN_WATER_IN_FOREST;
	// 			break;
	// 		case BATTLE_TERRAIN_DARK_CAVE:
	// 			terrain = BATTLE_TERRAIN_DARK_CAVE_WATER;
	// 			break;
	// 		case BATTLE_TERRAIN_SNOW_CAVE:
	// 			terrain = BATTLE_TERRAIN_WATER_IN_SNOW_CAVE;
	// 			break;
	// 		case BATTLE_TERRAIN_CRYSTAL_PEAK:
	// 			terrain = BATTLE_TERRAIN_CRYSTAL_PEAK_WATER;
	// 			break;
	// 		case BATTLE_TERRAIN_ANTISIS_SEWERS:
	// 			terrain = BATTLE_TERRAIN_ANTISIS_SEWERS_WATER;
	// 			break;
	// 		case BATTLE_TERRAIN_BOG:
	// 			terrain = BATTLE_TERRAIN_BOG_WATER;
	// 			break;
	// 	}
	// }

	if (MetatileBehavior_IsSand(tileBehavior) && IsCurrentAreaDesert())
		terrain = BATTLE_TERRAIN_DESERT;

	if (tileBehavior == MB_LAVA)
		terrain = BATTLE_TERRAIN_LAVA_POOL;
#endif

	return terrain;
}

bool8 MetatileBehavior_IsSand(u8 metatileBehavior)
{
	return metatileBehavior == MB_SAND_CAVE;
}

bool8 MetatileBehavior_IsIce(u8 metatileBehavior)
{
	if (metatileBehavior == MB_ICE
	||  metatileBehavior == MB_THIN_ICE
	||  metatileBehavior == MB_CRACKED_ICE)
		return TRUE;
	else
		return FALSE;
}

bool8 MetatileBehavior_IsDeepOrOceanWater(u8 metatileBehavior)
{
	return metatileBehavior == MB_SPLASHING_WATER
		|| metatileBehavior == MB_DIVEABLE;
}

bool8 IsTerrainMoveIndoors(void)
{
	if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER))
		return TRUE;

	return FALSE;
}
