#include "../config.h"
#include "../../include/global.h"
#include "../../include/constants/maps.h"
#include "../../include/wild_encounter.h"
#include "../../include/constants/region_map_sections.h"
#include "../../include/constants/species.h"

/*
wild_encounter_tables.c
	day/night and/or regular map wild encounter species

tables to edit:
	gWildMonMorningHeaders
	gWildMonEveningHeaders
	gWildMonNightHeaders
	gSwarmTable

*/

#ifndef UNBOUND //Modify this section

// #region Route structs
const struct WildPokemon gRoute1_LandMons[] =
{
	{2, 3, SPECIES_BIDOOF},
	{2, 3, SPECIES_WINGULL},
	{2, 4, SPECIES_BIDOOF},
	{2, 4, SPECIES_WINGULL},
	{2, 3, SPECIES_SUNKERN},
	{2, 3, SPECIES_SUNKERN},
	{2, 4, SPECIES_YAMPER},
	{2, 4, SPECIES_YAMPER},
	{3, 4, SPECIES_BIDOOF},
	{3, 4, SPECIES_WINGULL},
	{4, 4, SPECIES_BIDOOF},
	{4, 4, SPECIES_WINGULL},
};

const struct WildPokemon gRoute1_FishingMons[] = 
{
	{8, 10, SPECIES_MAGIKARP}, 	// Old Rod
	{8, 11, SPECIES_MAGIKARP}, 	// Old Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
};

const struct WildPokemon gRoute2_LandMons[] =
{
	{3, 5, SPECIES_BUDEW},
	{2, 4, SPECIES_GRUBBIN},
	{3, 6, SPECIES_ROCKRUFF},
	{2, 6, SPECIES_NICKIT},
	{3, 6, SPECIES_NIDORAN_M},
	{3, 5, SPECIES_ROOKIDEE},
	{2, 5, SPECIES_NICKIT},
	{3, 6, SPECIES_NIDORAN_M},
	{2, 4, SPECIES_ROCKRUFF},
	{3, 5, SPECIES_ROOKIDEE},
	{3, 5, SPECIES_ROCKRUFF},
	{3, 5, SPECIES_ROOKIDEE},
};

const struct WildPokemon gRoute2_FishingMons[] = 
{
	{8, 10, SPECIES_MAGIKARP}, 	// Old Rod
	{8, 11, SPECIES_MAGIKARP}, 	// Old Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
};

const struct WildPokemon gRoute17_LandMons[] =
{
	{2, 3, SPECIES_FLABEBE},
	{2, 4, SPECIES_FLETCHLING},
	{2, 3, SPECIES_RALTS},
	{3, 4, SPECIES_RALTS},
	{2, 3, SPECIES_FLETCHLING},
	{2, 4, SPECIES_CUTIEFLY},
	{2, 3, SPECIES_CUTIEFLY},
	{2, 3, SPECIES_GRUBBIN},
	{2, 4, SPECIES_GRUBBIN},
	{2, 4, SPECIES_FLABEBE},
	{3, 3, SPECIES_GRUBBIN},
	{3, 3, SPECIES_FLABEBE},
};

const struct WildPokemon gRoute17_Cave1F_LandMons[] =
{
	{3, 4, SPECIES_DRILBUR},
	{3, 3, SPECIES_DRILBUR},
	{2, 3, SPECIES_ZUBAT},
	{3, 3, SPECIES_ZUBAT},
	{2, 4, SPECIES_ROGGENROLA},
	{3, 4, SPECIES_BONSLY},
	{2, 4, SPECIES_ZUBAT},
	{3, 4, SPECIES_NOIBAT},
	{3, 4, SPECIES_ZUBAT},
	{3, 4, SPECIES_ROGGENROLA},
	{2, 4, SPECIES_ZUBAT},
	{2, 4, SPECIES_ROGGENROLA},
};

const struct WildPokemon gRoute17_FishingMons[] = 
{
	{8, 10, SPECIES_MAGIKARP}, 	// Old Rod
	{8, 11, SPECIES_MAGIKARP}, 	// Old Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Good Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
	{1, 1, SPECIES_NONE},		// Super Rod
};

// #endregion

// #region Dungeon Structs
const struct WildPokemon gVarisiForest_LandMons[] =
{
	{3, 6, SPECIES_BLIPBUG},
	{3, 6, SPECIES_PIKIPEK},
	{3, 7, SPECIES_MORELULL},
	{2, 6, SPECIES_PICHU},
	{3, 6, SPECIES_BUNEARY},
	{3, 7, SPECIES_SHROOMISH},
	{3, 7, SPECIES_BUDEW},
	{4, 7, SPECIES_BONSLY},
	{3, 6, SPECIES_VENIPEDE},
	{3, 7, SPECIES_VENIPEDE},
	{4, 6, SPECIES_SLAKOTH},
	{4, 7, SPECIES_SLAKOTH},
};

const struct WildPokemon gVarisiForest_LandMonsNight[] =
{
	{3, 6, SPECIES_BLIPBUG},
	{3, 6, SPECIES_HOOTHOOT},
	{3, 7, SPECIES_MORELULL},
	{2, 6, SPECIES_PICHU},
	{3, 6, SPECIES_BUNEARY},
	{3, 7, SPECIES_SHROOMISH},
	{3, 7, SPECIES_BUDEW},
	{4, 7, SPECIES_BONSLY},
	{3, 6, SPECIES_VENIPEDE},
	{3, 7, SPECIES_VENIPEDE},
	{4, 6, SPECIES_SLAKOTH},
	{4, 7, SPECIES_SLAKOTH},
};
// #endregion

// #region Town Structs
const struct WildPokemon gRhodanziCity_WaterMons[] =
{
	{5, 15, SPECIES_CHINCHOU},
	{5, 20, SPECIES_CHINCHOU},
	{20, 35, SPECIES_LANTURN},
	{10, 30, SPECIES_CHINCHOU},
	{10, 30, SPECIES_CHINCHOU},
};

const struct WildPokemon gRhodanziCity_FishingMons[] = 
{
	{3, 7, SPECIES_MAGIKARP}, 		// Old Rod
	{4, 8, SPECIES_CORPHISH}, 		// Old Rod
	{20, 25, SPECIES_CORPHISH},		// Good Rod
	{20, 25, SPECIES_MAGIKARP},		// Good Rod
	{19, 26, SPECIES_MAGIKARP},		// Good Rod
	{35, 40, SPECIES_GYARADOS},		// Super Rod
	{33, 41, SPECIES_CRAWDAUNT},	// Super Rod
	{35, 40, SPECIES_SLOWPOKE},		// Super Rod
	{36, 42, SPECIES_SLOWPOKE},		// Super Rod
	{38, 44, SPECIES_SLOWBRO},		// Super Rod
};
// #endregion

// #region Encounter Rate Structs
const struct WildPokemonInfo gRoute1_LandMonsInfo = {21, gRoute1_LandMons};
const struct WildPokemonInfo gRoute1_FishingMonsInfo = {20, gRoute1_FishingMons};
const struct WildPokemonInfo gRoute2_LandMonsInfo = {21, gRoute2_LandMons};
const struct WildPokemonInfo gRoute2_FishingMonsInfo = {20, gRoute2_FishingMons};
const struct WildPokemonInfo gRoute17_LandMonsInfo = {21, gRoute17_LandMons};
const struct WildPokemonInfo gRoute17_Cave1F_LandMonsInfo = {21, gRoute17_Cave1F_LandMons};
const struct WildPokemonInfo gRoute17_FishingMonsInfo = {20, gRoute17_FishingMons};
const struct WildPokemonInfo gVarisiForest_LandMonsInfo = {21, gVarisiForest_LandMons};
const struct WildPokemonInfo gVarisiForest_LandMonsNightInfo = {21, gVarisiForest_LandMonsNight};
const struct WildPokemonInfo gRhodanziCity_WaterMonsInfo = {21, gRhodanziCity_WaterMons};
const struct WildPokemonInfo gRhodanziCity_FishingMonsInfo = {20, gRhodanziCity_FishingMons};
// #endregion

const struct WildPokemonHeader gWildMonRegularHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_1),
		.mapNum = MAP_NUM(ROUTE_1),
		.landMonsInfo = &gRoute1_LandMonsInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = &gRoute1_FishingMonsInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_2),
		.mapNum = MAP_NUM(ROUTE_2),
		.landMonsInfo = &gRoute2_LandMonsInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = &gRoute2_FishingMonsInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_17),
		.mapNum = MAP_NUM(ROUTE_17),
		.landMonsInfo = &gRoute17_LandMonsInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = &gRoute17_FishingMonsInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE17_CAVE_1F),
		.mapNum = MAP_NUM(ROUTE17_CAVE_1F),
		.landMonsInfo = &gRoute17_Cave1F_LandMonsInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gVarisiForest_LandMonsInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(RHODANZI_CITY),
		.mapNum = MAP_NUM(RHODANZI_CITY),
		.landMonsInfo = NULL,
		.waterMonsInfo = &gRhodanziCity_WaterMonsInfo,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = &gRhodanziCity_FishingMonsInfo,
	},
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct WildPokemonHeader gWildMonMorningHeaders[] =
{
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct WildPokemonHeader gWildMonEveningHeaders[] =
{
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct WildPokemonHeader gWildMonNightHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gVarisiForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct SwarmData gSwarmTable[] =
{
	/*{
		.mapName = 0xFF,
		.species = 0xFFFF,
	},*/
};

#else //Below is for Pokemon Unbound. Feel free to remove.

static const struct WildPokemon sRoute2_LandMonsNight[] =
{
	{9, 11, SPECIES_HOOTHOOT},
	{9, 11, SPECIES_RATTATA},
	{9, 11, SPECIES_RATTATA},
	{9, 11, SPECIES_HOOTHOOT},
	{9, 11, SPECIES_ELECTRIKE},
	{9, 11, SPECIES_AZURILL},
	{9, 11, SPECIES_STUFFUL},
	{9, 11, SPECIES_STUFFUL},
	{10, 11, SPECIES_SCRAGGY},
	{10, 11, SPECIES_RIOLU},
	{11, 11, SPECIES_SCRAGGY},
	{11, 11, SPECIES_RIOLU},
};

static const struct WildPokemonInfo sRoute2_LandMonsInfoNight = {20, sRoute2_LandMonsNight};

static const struct WildPokemon sRoute3_LandMonsNight[] =
{
	{10, 12, SPECIES_WINGULL},
	{10, 12, SPECIES_SENTRET},
	{10, 12, SPECIES_BIDOOF},
	{10, 12, SPECIES_BIDOOF},
	{10, 12, SPECIES_BUIZEL},
	{10, 12, SPECIES_SHELLOS},
	{10, 12, SPECIES_SURSKIT},
	{10, 12, SPECIES_KRABBY},
	{11, 12, SPECIES_KRABBY},
	{11, 12, SPECIES_KRABBY},
	{12, 12, SPECIES_KRABBY},
	{12, 12, SPECIES_KRABBY},
};

static const struct WildPokemonInfo sRoute3_LandMonsInfoNight = {20, sRoute3_LandMonsNight};

static const struct WildPokemon sRoute4_LandMonsNight[] =
{
	{15, 17, SPECIES_HOOTHOOT},
	{15, 17, SPECIES_HOOTHOOT},
	{15, 17, SPECIES_LILLIPUP},
	{15, 17, SPECIES_LILLIPUP},
	{15, 17, SPECIES_EKANS},
	{15, 17, SPECIES_NUMEL},
	{15, 17, SPECIES_MANKEY},
	{15, 17, SPECIES_MANKEY},
	{15, 17, SPECIES_NUMEL},
	{15, 17, SPECIES_RALTS},
	{17, 17, SPECIES_NUMEL},
	{17, 17, SPECIES_RALTS},
};

static const struct WildPokemonInfo sRoute4_LandMonsInfoNight = {20, sRoute4_LandMonsNight};

static const struct WildPokemon sGrimWoods_LandMonsNight[] =
{
	{13, 16, SPECIES_WEEDLE},
	{14, 16, SPECIES_SEEDOT},
	{14, 16, SPECIES_PUMPKABOO},
	{14, 16, SPECIES_PUMPKABOO_M},
	{14, 16, SPECIES_PUMPKABOO_L},
	{14, 16, SPECIES_PUMPKABOO_XL},
	{15, 16, SPECIES_GASTLY},
	{15, 16, SPECIES_SHUPPET},
	{15, 16, SPECIES_DUSKULL},
	{15, 16, SPECIES_PHANTUMP},
	{16, 16, SPECIES_DUSKULL},
	{16, 16, SPECIES_PHANTUMP},
};

static const struct WildPokemonInfo sGrimWoods_LandMonsInfoNight = {20, sGrimWoods_LandMonsNight};

static const struct WildPokemon sRoute5_LandMonsNight[] =
{
	{15, 18, SPECIES_MURKROW},
	{15, 18, SPECIES_ZUBAT},
	{15, 18, SPECIES_NIDORAN_M},
	{15, 18, SPECIES_NIDORAN_F},
	{16, 19, SPECIES_HOUNDOUR},
	{15, 18, SPECIES_ZUBAT},
	{15, 18, SPECIES_NIDORAN_M},
	{15, 18, SPECIES_NIDORAN_F},
	{17, 19, SPECIES_MURKROW},
	{17, 19, SPECIES_DEDENNE},
	{19, 19, SPECIES_NIDORINA},
	{19, 19, SPECIES_NIDORINO},
};

static const struct WildPokemonInfo sRoute5_LandMonsInfoNight = {20, sRoute5_LandMonsNight};

static const struct WildPokemon sRoute6_LandMonsMorning[] =
{
	{20, 22, SPECIES_ZIGZAGOON},
	{20, 22, SPECIES_LEDYBA},
	{20, 22, SPECIES_SHINX},
	{20, 22, SPECIES_DEERLING},
	{20, 22, SPECIES_ZIGZAGOON},
	{20, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_DEERLING},
	{21, 22, SPECIES_KRICKETOT},
	{22, 22, SPECIES_LEDIAN},
	{22, 22, SPECIES_LUXIO},
};

static const struct WildPokemonInfo sRoute6_LandMonsInfoMorning = {20, sRoute6_LandMonsMorning};

static const struct WildPokemon sRoute6_LandMonsNight[] =
{
	{20, 22, SPECIES_ZIGZAGOON},
	{20, 22, SPECIES_SPINARAK},
	{20, 22, SPECIES_SHINX},
	{20, 22, SPECIES_DEERLING},
	{20, 22, SPECIES_ZIGZAGOON},
	{20, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_DEERLING},
	{21, 22, SPECIES_KRICKETOT},
	{22, 22, SPECIES_ARIADOS},
	{22, 22, SPECIES_LUXIO},
};

static const struct WildPokemonInfo sRoute6_LandMonsInfoNight = {20, sRoute6_LandMonsNight};

static const struct WildPokemon sRoute7_LandMonsNight[] =
{
	{21, 23, SPECIES_RATTATA_A},
	{21, 23, SPECIES_HOOTHOOT},
	{21, 23, SPECIES_BUNEARY},
	{21, 23, SPECIES_DROWZEE},
	{21, 23, SPECIES_ABRA},
	{21, 23, SPECIES_MAREEP},
	{21, 23, SPECIES_SHINX},
	{21, 23, SPECIES_SHINX},
	{22, 23, SPECIES_RATTATA_A},
	{22, 23, SPECIES_BUNEARY},
	{23, 23, SPECIES_LUXIO},
	{23, 23, SPECIES_RATICATE_A},
};

static const struct WildPokemonInfo sRoute7_LandMonsInfoNight = {20, sRoute7_LandMonsNight};

static const struct WildPokemon sRoute8_LandMonsNight[] =
{
	{22, 25, SPECIES_SNOVER},
	{22, 25, SPECIES_SNORUNT},
	{22, 25, SPECIES_SNEASEL},
	{22, 25, SPECIES_SNORUNT},
	{22, 25, SPECIES_CUBCHOO},
	{22, 25, SPECIES_DEERLING_WINTER},
	{22, 25, SPECIES_FURRET},
	{22, 25, SPECIES_FLAAFFY},
	{23, 25, SPECIES_SNOVER},
	{23, 25, SPECIES_SNORUNT},
	{23, 25, SPECIES_MINIOR_SHIELD},
	{23, 25, SPECIES_MINIOR_SHIELD},
};

static const struct WildPokemonInfo sRoute8_LandMonsInfoNight = {20, sRoute8_LandMonsNight};

static const struct WildPokemon sFrozenForest_LandMonsNight[] =
{
	{23, 26, SPECIES_SNOVER},
	{23, 26, SPECIES_SNOVER},
	{23, 26, SPECIES_SNEASEL},
	{23, 26, SPECIES_CUBCHOO},
	{23, 26, SPECIES_CUBCHOO},
	{23, 26, SPECIES_CUBCHOO},
	{23, 26, SPECIES_SNOVER},
	{23, 26, SPECIES_SNEASEL},
	{23, 26, SPECIES_CUBCHOO},
	{23, 26, SPECIES_CUBCHOO},
	{26, 26, SPECIES_CUBCHOO},
	{26, 26, SPECIES_CUBCHOO},
};

static const struct WildPokemonInfo sFrozenForest_LandMonsInfoNight = {20, sFrozenForest_LandMonsNight};

static const struct WildPokemon sRoute11_LandMonsNight[] =
{
	{26, 29, SPECIES_EXEGGCUTE},
	{26, 29, SPECIES_MEOWTH},
	{26, 29, SPECIES_VENONAT},
	{26, 29, SPECIES_VENONAT},
	{26, 29, SPECIES_SPOINK},
	{26, 29, SPECIES_MEDITITE},
	{27, 29, SPECIES_SPOINK},
	{27, 29, SPECIES_MEDITITE},
	{29, 29, SPECIES_PERSIAN},
	{29, 29, SPECIES_ABSOL},
	{29, 29, SPECIES_PERSIAN},
	{29, 29, SPECIES_ABSOL},
};

static const struct WildPokemonInfo sRoute11_LandMonsInfoNight = {20, sRoute11_LandMonsNight};

static const struct WildPokemon sRoute12_LandMonsNight[] =
{
	{29, 32, SPECIES_HOOTHOOT},
	{33, 36, SPECIES_ROCKRUFF},
	{33, 36, SPECIES_INKAY},
	{33, 36, SPECIES_MIENFOO},
	{33, 36, SPECIES_PONYTA},
	{33, 36, SPECIES_SNUBBULL},
	{34, 36, SPECIES_INKAY},
	{34, 36, SPECIES_MIENFOO},
	{34, 36, SPECIES_NOCTOWL},
	{33, 36, SPECIES_TOGEDEMARU},
	{34, 36, SPECIES_NOCTOWL},
	{35, 36, SPECIES_TOGEDEMARU},
};

static const struct WildPokemonInfo sRoute12_LandMonsInfoNight = {20, sRoute12_LandMonsNight};

static const struct WildPokemon sRoute14_LandMonsNight[] =
{
	{37, 40, SPECIES_PELIPPER},
	{37, 40, SPECIES_BIBAREL},
	{37, 40, SPECIES_GOLDUCK},
	{37, 40, SPECIES_GASTRODON},
	{37, 40, SPECIES_FLOATZEL},
	{36, 40, SPECIES_SLOWPOKE},
	{37, 40, SPECIES_GLOOM},
	{37, 40, SPECIES_GLOOM},
	{38, 40, SPECIES_FLOATZEL},
	{37, 40, SPECIES_SLOWPOKE},
	{25, 30, SPECIES_ODDISH},
	{25, 30, SPECIES_ODDISH},
};

static const struct WildPokemonInfo sRoute14_LandMonsInfoNight = {20, sRoute14_LandMonsNight};

static const struct WildPokemon sVivillWoods_LandMonsNight[] =
{
	{30, 35, SPECIES_WEEDLE},
	{30, 35, SPECIES_WURMPLE},
	{30, 35, SPECIES_SCATTERBUG},
	{38, 41, SPECIES_COTTONEE},
	{39, 41, SPECIES_SWADLOON},
	{38, 41, SPECIES_PETILIL},
	{39, 41, SPECIES_SPEWPA},
	{39, 41, SPECIES_KAKUNA},
	{39, 41, SPECIES_SILCOON},
	{39, 41, SPECIES_CASCOON},
	{39, 41, SPECIES_SILCOON},
	{39, 41, SPECIES_CASCOON},
};

static const struct WildPokemonInfo sVivillWoods_LandMonsInfoNight = {20, sVivillWoods_LandMonsNight};

static const struct WildPokemon sRoute17_LandMonsNight[] =
{
	{47, 50, SPECIES_NOCTOWL},
	{47, 50, SPECIES_PELIPPER},
	{47, 50, SPECIES_NOCTOWL},
	{47, 50, SPECIES_PELIPPER},
	{47, 50, SPECIES_NOCTOWL},
	{47, 50, SPECIES_NOCTOWL},
	{47, 50, SPECIES_NOCTOWL},
	{47, 50, SPECIES_NOCTOWL},
	{48, 50, SPECIES_ZANGOOSE},
	{48, 50, SPECIES_SEVIPER},
	{40, 45, SPECIES_BAGON},
	{40, 45, SPECIES_BAGON},
};

static const struct WildPokemonInfo sRoute17_LandMonsInfoNight = {20, sRoute17_LandMonsNight};

static const struct WildPokemon sCootesBog_LandMonsNight[] =
{
	{48, 52, SPECIES_CROAGUNK},
	{49, 52, SPECIES_QUAGSIRE},
	{48, 52, SPECIES_CROAGUNK},
	{50, 52, SPECIES_SLIGGOO},
	{50, 52, SPECIES_SLIGGOO},
	{51, 52, SPECIES_DRAPION},
	{49, 52, SPECIES_CARNIVINE},
	{49, 52, SPECIES_GLOOM},
	{49, 52, SPECIES_GLOOM},
	{52, 52, SPECIES_TOXICROAK},
	{49, 52, SPECIES_GLOOM},
	{52, 52, SPECIES_TOXICROAK},
};

static const struct WildPokemonInfo sCootesBog_LandMonsInfoNight = {20, sCootesBog_LandMonsNight};

static const struct WildPokemon sRoute18_LandMonsNight[] =
{
	{53, 57, SPECIES_NOCTOWL},
	{53, 57, SPECIES_SKUNTANK},
	{53, 57, SPECIES_NOCTOWL},
	{53, 57, SPECIES_SKUNTANK},
	{53, 57, SPECIES_BOUFFALANT},
	{53, 57, SPECIES_BOUFFALANT},
	{53, 57, SPECIES_NOCTOWL},
	{53, 57, SPECIES_SKUNTANK},
	{53, 57, SPECIES_SUDOWOODO},
	{53, 57, SPECIES_AUDINO},
	{53, 57, SPECIES_SUDOWOODO},
	{53, 57, SPECIES_AUDINO},
};

static const struct WildPokemonInfo sRoute18_LandMonsInfoNight = {20, sRoute18_LandMonsNight};

const struct WildPokemonHeader gWildMonMorningHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_6),
		.mapNum = MAP_NUM(ROUTE_6),
		.landMonsInfo = &sRoute6_LandMonsInfoMorning,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct WildPokemonHeader gWildMonEveningHeaders[] =
{
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct WildPokemonHeader gWildMonNightHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_2),
		.mapNum = MAP_NUM(ROUTE_2),
		.landMonsInfo = &sRoute2_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_3),
		.mapNum = MAP_NUM(ROUTE_3),
		.landMonsInfo = &sRoute3_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_4),
		.mapNum = MAP_NUM(ROUTE_4),
		.landMonsInfo = &sRoute4_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(GRIM_WOODS),
		.mapNum = MAP_NUM(GRIM_WOODS),
		.landMonsInfo = &sGrimWoods_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_5),
		.mapNum = MAP_NUM(ROUTE_5),
		.landMonsInfo = &sRoute5_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_6),
		.mapNum = MAP_NUM(ROUTE_6),
		.landMonsInfo = &sRoute6_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_7),
		.mapNum = MAP_NUM(ROUTE_7),
		.landMonsInfo = &sRoute7_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_8),
		.mapNum = MAP_NUM(ROUTE_8),
		.landMonsInfo = &sRoute8_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(FROZEN_FOREST),
		.mapNum = MAP_NUM(FROZEN_FOREST),
		.landMonsInfo = &sFrozenForest_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_11),
		.mapNum = MAP_NUM(ROUTE_11),
		.landMonsInfo = &sRoute11_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_12),
		.mapNum = MAP_NUM(ROUTE_12),
		.landMonsInfo = &sRoute12_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_14_B),
		.mapNum = MAP_NUM(ROUTE_14_B),
		.landMonsInfo = &sRoute14_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_14_C),
		.mapNum = MAP_NUM(ROUTE_14_C),
		.landMonsInfo = &sRoute14_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(VIVILL_WOODS),
		.mapNum = MAP_NUM(VIVILL_WOODS),
		.landMonsInfo = &sVivillWoods_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_17),
		.mapNum = MAP_NUM(ROUTE_17),
		.landMonsInfo = &sRoute17_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(COOTES_BOG),
		.mapNum = MAP_NUM(COOTES_BOG),
		.landMonsInfo = &sCootesBog_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_18_B),
		.mapNum = MAP_NUM(ROUTE_18_B),
		.landMonsInfo = &sRoute18_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	}
};

const struct SwarmData gSwarmTable[] =
{
	{
		.mapName = MAPSEC_ROUTE_1,
		.species = SPECIES_SNEASEL,
	},
	{
		.mapName = MAPSEC_ROUTE_2,
		.species = SPECIES_BURMY,
	},
	{
		.mapName = MAPSEC_FLOWER_PARADISE,
		.species = SPECIES_CHERUBI,
	},
	{
		.mapName = MAPSEC_GRIM_WOODS,
		.species = SPECIES_NINCADA,
	},
	{
		.mapName = MAPSEC_ROUTE_4,
		.species = SPECIES_LITLEO,
	},
	{
		.mapName = MAPSEC_CINDER_VOLCANO,
		.species = SPECIES_VULPIX,
	},
	{
		.mapName = MAPSEC_ROUTE_5,
		.species = SPECIES_PURRLOIN,
	},
	{
		.mapName = MAPSEC_ROUTE_5,
		.species = SPECIES_ELGYEM,
	},
	{
		.mapName = MAPSEC_VALLEY_CAVE,
		.species = SPECIES_DUNSPARCE,
	},
	{
		.mapName = MAPSEC_ROUTE_6,
		.species = SPECIES_SMEARGLE,
	},
	{
		.mapName = MAPSEC_ROUTE_7,
		.species = SPECIES_MR_MIME,
	},
	{
		.mapName = MAPSEC_ROUTE_8,
		.species = SPECIES_STANTLER,
	},
	{
		.mapName = MAPSEC_ROUTE_9,
		.species = SPECIES_KARRABLAST,
	},
	{
		.mapName = MAPSEC_ROUTE_10,
		.species = SPECIES_SHELMET,
	},
	{
		.mapName = MAPSEC_ROUTE_11,
		.species = SPECIES_GLAMEOW,
	},
	{
		.mapName = MAPSEC_THUNDERCAP_MOUNTAIN,
		.species = SPECIES_JOLTIK,
	},
	{
		.mapName = MAPSEC_THUNDERCAP_MOUNTAIN,
		.species = SPECIES_FERROSEED,
	},
	{
		.mapName = MAPSEC_ROUTE_12,
		.species = SPECIES_SWIRLIX,
	},
	{
		.mapName = MAPSEC_ROUTE_12,
		.species = SPECIES_SPRITZEE,
	},
	{
		.mapName = MAPSEC_VIVILL_WOODS,
		.species = SPECIES_PIKACHU,
	},
	{
		.mapName = MAPSEC_ROUTE_16,
		.species = SPECIES_GOTHORITA,
	},
	{
		.mapName = MAPSEC_ROUTE_16,
		.species = SPECIES_DUOSION,
	},
	{
		.mapName = MAPSEC_ROUTE_17,
		.species = SPECIES_VOLBEAT,
	},
	{
		.mapName = MAPSEC_ROUTE_17,
		.species = SPECIES_ILLUMISE,
	},
	{
		.mapName = MAPSEC_COOTES_BOG,
		.species = SPECIES_CROCONAW,
	},
	{
		.mapName = MAPSEC_ROUTE_18,
		.species = SPECIES_BAYLEEF,
	}
};

#endif

const u16 gSwarmTableLength = NELEMS(gSwarmTable);
