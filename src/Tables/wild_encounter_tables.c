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

const struct WildPokemon gRubarrDesert_LandMonsNight[] =
{
	{8, 10, SPECIES_CACNEA},
	{8, 10, SPECIES_VULLABY},
	{8, 11, SPECIES_TRAPINCH},
	{9, 11, SPECIES_SANDILE},
	{8, 11, SPECIES_VULLABY},
	{10, 12, SPECIES_CASTFORM},
	{9, 12, SPECIES_TRAPINCH},
	{8, 12, SPECIES_SANDILE},
	{9, 11, SPECIES_VULLABY},
	{10, 13, SPECIES_HIPPOPOTAS},
	{11, 13, SPECIES_MANDIBUZZ}, 
	{10, 13, SPECIES_MANDIBUZZ}
};

const struct WildPokemon gHeleoRanch_LandMonsNight[] =
{
	{15, 18, SPECIES_LILLIPUP},
	{15, 18, SPECIES_SKIDDO},
	{16, 19, SPECIES_EEVEE},
	{16, 18, SPECIES_HERDIER},
	{16, 18, SPECIES_RIOLU},
	{16, 18, SPECIES_PIKACHU},
	{15, 17, SPECIES_ROCKRUFF},
	{13, 16, SPECIES_TOGEPI},
	{15, 18, SPECIES_TOGEPI},
	{15, 18, SPECIES_CUTIEFLY},
	{16, 19, SPECIES_HAPPINY}, 
	{15, 18, SPECIES_HAPPINY}
};

const struct WildPokemon gForgottenManseExterior_LandMonsNight[] =
{
	{19, 23, SPECIES_YAMASK},
	{19, 23, SPECIES_PHANTUMP},
	{19, 23, SPECIES_DUSKULL},
	{20, 24, SPECIES_DUSKULL},
	{19, 25, SPECIES_DUSKULL},
	{19, 24, SPECIES_RATTATA_A},
	{20, 24, SPECIES_YAMASK},
	{20, 24, SPECIES_PHANTUMP},
	{20, 24, SPECIES_RATTATA_A},
	{20, 23, SPECIES_SHEDINJA},
	{20, 25, SPECIES_RATTATA_A}, 
	{20, 24, SPECIES_SHEDINJA}
};

const struct WildPokemon gDaimynCity_LandMonsNight[] =
{
	{25, 27, SPECIES_YAMPER},
	{24, 28, SPECIES_GRUBBIN},
	{25, 28, SPECIES_BOLTUND},
	{24, 27, SPECIES_CHARJABUG},
	{25, 28, SPECIES_GRIMER_A},
	{25, 28, SPECIES_GURDURR},
	{24, 27, SPECIES_KOFFING_G},
	{25, 28, SPECIES_KOFFING_G},
	{24, 27, SPECIES_MIMIKYU},
	{25, 28, SPECIES_MIMIKYU},
	{24, 28, SPECIES_MIMIKYU}, 
	{25, 28, SPECIES_MIMIKYU}
};

const struct WildPokemon gRoute10Cave_LandMonsNight[] =
{
	{25, 28, SPECIES_ZUBAT},
	{26, 29, SPECIES_ZUBAT},
	{26, 29, SPECIES_ROCKRUFF},
	{26, 29, SPECIES_ROCKRUFF},
	{26, 29, SPECIES_ROCKRUFF},
	{25, 28, SPECIES_GOLBAT},
	{25, 28, SPECIES_LYCANROC_N},
	{25, 28, SPECIES_GOLBAT},
	{26, 29, SPECIES_GOLBAT},
	{25, 28, SPECIES_LYCANROC_N},
	{25, 28, SPECIES_LYCANROC_N}, 
	{26, 29, SPECIES_GOLBAT}
};

const struct WildPokemon gRoute11North_LandMonsNight[] =
{
	{31, 34, SPECIES_STUNFISK_G},
	{30, 33, SPECIES_WHIRLIPEDE},
	{29, 33, SPECIES_TIMBURR},
	{32, 33, SPECIES_PHANTUMP},
	{29, 33, SPECIES_FLOETTE_WHITE},
	{30, 33, SPECIES_THIEVUL},
	{29, 33, SPECIES_GURDURR},
	{30, 33, SPECIES_GURDURR},
	{29, 32, SPECIES_PHANTUMP},
	{30, 32, SPECIES_STUNFISK_G},
	{30, 33, SPECIES_PHANTUMP}, 
	{29, 32, SPECIES_STUNFISK_G}
};

const struct WildPokemon gPeradonForest_LandMonsNight[] =
{
	{34, 36, SPECIES_JOLTIK},
	{34, 37, SPECIES_PHANTUMP},
	{34, 35, SPECIES_SHIINOTIC},
	{34, 36, SPECIES_VIGOROTH},
	{34, 37, SPECIES_MANKEY},
	{35, 37, SPECIES_TRUMBEAK},
	{34, 36, SPECIES_SUDOWOODO},
	{34, 36, SPECIES_LOPUNNY},
	{34, 37, SPECIES_NOCTOWL},
	{35, 37, SPECIES_HERACROSS},
	{35, 37, SPECIES_NOCTOWL}, 
	{34, 36, SPECIES_HERACROSS}
};

const struct WildPokemon gLakeLaplaz_LandMonsNight[] =
{
	{36, 40, SPECIES_MORELULL},
	{37, 41, SPECIES_DOTTLER},
	{36, 40, SPECIES_ZORUA},
	{35, 39, SPECIES_MORPEKO},
	{36, 39, SPECIES_MISDREAVUS},
	{36, 40, SPECIES_YAMASK},
	{37, 40, SPECIES_ZORUA},
	{37, 40, SPECIES_SHIINOTIC},
	{36, 41, SPECIES_ZOROARK},
	{35, 40, SPECIES_ZOROARK},
	{36, 40, SPECIES_CHANSEY}, 
	{36, 41, SPECIES_CHANSEY}
};

const struct WildPokemon gRoute12West_LandMonsNight[] =
{
	{39, 41, SPECIES_DARUMAKA_G},
	{39, 41, SPECIES_CUBCHOO},
	{40, 43, SPECIES_DELIBIRD},
	{40, 42, SPECIES_AMAURA},
	{40, 43, SPECIES_STONJOURNER},
	{40, 42, SPECIES_CASTFORM},
	{41, 43, SPECIES_FROSLASS},
	{41, 43, SPECIES_FROSMOTH},
	{39, 42, SPECIES_BEARTIC},
	{39, 42, SPECIES_DARMANITAN_G},
	{39, 43, SPECIES_BEARTIC}, 
	{39, 43, SPECIES_DARMANITAN_G}
};

const struct WildPokemon gCalicinBay_LandMonsNight[] =
{
	{40, 42, SPECIES_SNEASEL},
	{40, 42, SPECIES_BERGMITE},
	{41, 44, SPECIES_AMAURA},
	{41, 43, SPECIES_CRABOMINABLE},
	{41, 44, SPECIES_SNOM},
	{41, 43, SPECIES_CORVISQUIRE},
	{42, 43, SPECIES_AVALUGG},
	{42, 44, SPECIES_WEAVILE},
	{42, 44, SPECIES_AURORUS},
	{42, 44, SPECIES_MAMOSWINE},
	{42, 44, SPECIES_AURORUS}, 
	{42, 44, SPECIES_MAMOSWINE}
};

const struct WildPokemonInfo gVarisiForest_LandMonsNightInfo = {14, gVarisiForest_LandMonsNight};
const struct WildPokemonInfo gRubarrDesert_LandMonsNightInfo = {3, gRubarrDesert_LandMonsNight};
const struct WildPokemonInfo gHeleoRanch_LandMonsNightInfo = {21, gHeleoRanch_LandMonsNight};
const struct WildPokemonInfo gForgottenManseExterior_LandMonsNightInfo = {21, gForgottenManseExterior_LandMonsNight};
const struct WildPokemonInfo gDaimynCity_LandMonsNightInfo = {21, gDaimynCity_LandMonsNight};
const struct WildPokemonInfo gRoute10Cave_LandMonsNightInfo = {5, gRoute10Cave_LandMonsNight};
const struct WildPokemonInfo gRoute11North_LandMonsNightInfo = {21, gRoute11North_LandMonsNight};
const struct WildPokemonInfo gPeradonForest_LandMonsNightInfo = {14, gPeradonForest_LandMonsNight};
const struct WildPokemonInfo gLakeLaplaz_LandMonsNightInfo = {21, gLakeLaplaz_LandMonsNight};
const struct WildPokemonInfo gRoute12West_LandMonsNightInfo = {21, gRoute12West_LandMonsNight};
const struct WildPokemonInfo gCalicinBay_LandMonsNightInfo = {21, gCalicinBay_LandMonsNight};

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
	// Null entries will keep regular encounters defined in WildEncounters.json
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gVarisiForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(RUBARR_DESERT),
		.mapNum = MAP_NUM(RUBARR_DESERT),
		.landMonsInfo = &gRubarrDesert_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(HELEO_RANCH_EXTERIOR),
		.mapNum = MAP_NUM(HELEO_RANCH_EXTERIOR),
		.landMonsInfo = &gHeleoRanch_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_EXTERIOR),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_EXTERIOR),
		.landMonsInfo = &gForgottenManseExterior_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(DAIMYN_CITY),
		.mapNum = MAP_NUM(DAIMYN_CITY),
		.landMonsInfo = &gDaimynCity_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE10_CAVE),
		.mapNum = MAP_NUM(ROUTE10_CAVE),
		.landMonsInfo = &gRoute10Cave_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_11_NORTH),
		.mapNum = MAP_NUM(ROUTE_11_NORTH),
		.landMonsInfo = &gRoute11North_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_NORTH),
		.mapNum = MAP_NUM(PERADON_FOREST_NORTH),
		.landMonsInfo = &gPeradonForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_SOUTH),
		.mapNum = MAP_NUM(PERADON_FOREST_SOUTH),
		.landMonsInfo = &gPeradonForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(LAKE_LAPLAZ),
		.mapNum = MAP_NUM(LAKE_LAPLAZ),
		.landMonsInfo = &gLakeLaplaz_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_12_WEST),
		.mapNum = MAP_NUM(ROUTE_12_WEST),
		.landMonsInfo = &gRoute12West_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(CALICIN_BAY),
		.mapNum = MAP_NUM(CALICIN_BAY),
		.landMonsInfo = &gCalicinBay_LandMonsNightInfo,
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
		.mapGroup = MAP_GROUP(RUBARR_DESERT),
		.mapNum = MAP_NUM(RUBARR_DESERT),
		.landMonsInfo = &gRubarrDesert_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(HELEO_RANCH_EXTERIOR),
		.mapNum = MAP_NUM(HELEO_RANCH_EXTERIOR),
		.landMonsInfo = &gHeleoRanch_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_EXTERIOR),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_EXTERIOR),
		.landMonsInfo = &gForgottenManseExterior_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(DAIMYN_CITY),
		.mapNum = MAP_NUM(DAIMYN_CITY),
		.landMonsInfo = &gDaimynCity_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE10_CAVE),
		.mapNum = MAP_NUM(ROUTE10_CAVE),
		.landMonsInfo = &gRoute10Cave_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_11_NORTH),
		.mapNum = MAP_NUM(ROUTE_11_NORTH),
		.landMonsInfo = &gRoute11North_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_NORTH),
		.mapNum = MAP_NUM(PERADON_FOREST_NORTH),
		.landMonsInfo = &gPeradonForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_SOUTH),
		.mapNum = MAP_NUM(PERADON_FOREST_SOUTH),
		.landMonsInfo = &gPeradonForest_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(LAKE_LAPLAZ),
		.mapNum = MAP_NUM(LAKE_LAPLAZ),
		.landMonsInfo = &gLakeLaplaz_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_12_WEST),
		.mapNum = MAP_NUM(ROUTE_12_WEST),
		.landMonsInfo = &gRoute12West_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(CALICIN_BAY),
		.mapNum = MAP_NUM(CALICIN_BAY),
		.landMonsInfo = &gCalicinBay_LandMonsNightInfo,
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
		.mapName = MAPSEC_ROUTE_3,
		.species = SPECIES_RATTATA,
	},
	{
		.mapName = MAPSEC_FORGOTTEN_MANSE,
		.species = SPECIES_RATICATE,
	},
	{
		.mapName = MAPSEC_ROUTE_14,
		.species = SPECIES_RAICHU_A,
	},
	{
		.mapName = MAPSEC_DAIMYN_CITY,
		.species = SPECIES_GRIMER,
	},
	{
		.mapName = MAPSEC_ROUTE_24,
		.species = SPECIES_MUK,
	},
	{
		.mapName = MAPSEC_ROUTE_8,
		.species = SPECIES_SLOWPOKE_G,
	},
	{
		.mapName = MAPSEC_ROUTE_22,
		.species = SPECIES_SLOWBRO_G,
	},
	{
		.mapName = MAPSEC_SEPPIRE_COVE,
		.species = SPECIES_SLOWKING_G,
	},
	{
		.mapName = MAPSEC_ROUTE_7,
		.species = SPECIES_FARFETCHD,
	},
	{
		.mapName = MAPSEC_DAIMYN_CITY,
		.species = SPECIES_KOFFING,
	},
	{
		.mapName = MAPSEC_VICTORY_ROAD,
		.species = SPECIES_WEEZING,
	},
	{
		.mapName = MAPSEC_ROUTE_6,
		.species = SPECIES_MIME_JR,
	},
	{
		.mapName = MAPSEC_ROUTE_9,
		.species = SPECIES_MR_MIME,
	},
	{
		.mapName = MAPSEC_ROUTE_16,
		.species = SPECIES_CORSOLA,
	},
	{
		.mapName = MAPSEC_TORMA_CAVE,
		.species = SPECIES_DARUMAKA,
	},
	{
		.mapName = MAPSEC_ROUTE_12_WEST,
		.species = SPECIES_DARMANITAN,
	},
	{
		.mapName = MAPSEC_ROUTE_11_SOUTH,
		.species = SPECIES_STUNFISK,
	},
};

#else //Below is for Pokemon Unbound. Feel free to remove.

static const struct WildPokemon sRoute2_LandMonsNight[] =
{
	{9, 11, SPECIES_HOOTHOOT},
	{9, 11, SPECIES_RATTATA},
	{9, 11, SPECIES_INKAY},
	{9, 11, SPECIES_MINCCINO},
	{9, 11, SPECIES_ELECTRIKE},
	{9, 11, SPECIES_AZURILL},
	{9, 11, SPECIES_STUFFUL},
	{9, 11, SPECIES_STUFFUL},
	{10, 11, SPECIES_SCRAGGY},
	{10, 11, SPECIES_RIOLU},
	{11, 11, SPECIES_SCRAGGY},
	{11, 11, SPECIES_RIOLU},
};

static const struct WildPokemonInfo sRoute2_LandMonsInfoNight = {15, sRoute2_LandMonsNight};

static const struct WildPokemon sRoute3_LandMonsNight[] =
{
	{9, 12, SPECIES_WINGULL},
	{9, 12, SPECIES_BIDOOF},
	{9, 12, SPECIES_SLOWPOKE},
	{9, 12, SPECIES_SLOWPOKE},
	{9, 12, SPECIES_SHELLOS},
	{9, 12, SPECIES_SURSKIT},
	{9, 12, SPECIES_SURSKIT},
	{9, 12, SPECIES_BUIZEL},
	{10, 12, SPECIES_POLIWAG},
	{10, 12, SPECIES_POLIWAG},
	{10, 12, SPECIES_POLIWAG},
	{10, 12, SPECIES_POLIWAG},
};

static const struct WildPokemonInfo sRoute3_LandMonsInfoNight = {15, sRoute3_LandMonsNight};

static const struct WildPokemon sRoute4_LandMonsNight[] =
{
	{15, 17, SPECIES_HOOTHOOT},
	{15, 17, SPECIES_HOOTHOOT},
	{15, 17, SPECIES_LILLIPUP},
	{15, 17, SPECIES_LILLIPUP},
	{15, 17, SPECIES_EKANS},
	{15, 17, SPECIES_NUMEL},
	{15, 17, SPECIES_BUDEW},
	{15, 17, SPECIES_BUDEW},
	{15, 17, SPECIES_MANKEY},
	{15, 17, SPECIES_RALTS},
	{17, 17, SPECIES_MANKEY},
	{17, 17, SPECIES_RALTS},
};

static const struct WildPokemonInfo sRoute4_LandMonsInfoNight = {15, sRoute4_LandMonsNight};

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

static const struct WildPokemonInfo sGrimWoods_LandMonsInfoNight = {15, sGrimWoods_LandMonsNight};

static const struct WildPokemon sRoute5_LandMonsNight[] =
{
	{15, 18, SPECIES_PURRLOIN},
	{15, 19, SPECIES_MURKROW},
	{15, 18, SPECIES_NIDORAN_M},
	{15, 18, SPECIES_NIDORAN_F},
	{16, 19, SPECIES_HOUNDOUR},
	{15, 18, SPECIES_PURRLOIN},
	{16, 19, SPECIES_LICKITUNG},
	{16, 19, SPECIES_LICKITUNG},
	{17, 19, SPECIES_VENONAT},
	{17, 19, SPECIES_VENONAT},
	{19, 19, SPECIES_DITTO},
	{19, 19, SPECIES_DITTO},
};

static const struct WildPokemonInfo sRoute5_LandMonsInfoNight = {15, sRoute5_LandMonsNight};

static const struct WildPokemon sRoute6_LandMonsMorning[] =
{
	{20, 22, SPECIES_BUNNELBY},
	{20, 22, SPECIES_LEDYBA},
	{20, 22, SPECIES_SHINX},
	{20, 22, SPECIES_DEERLING},
	{20, 22, SPECIES_BUNNELBY},
	{20, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_DEERLING},
	{21, 22, SPECIES_KRICKETOT},
	{22, 22, SPECIES_LEDIAN},
	{22, 22, SPECIES_LUXIO},
};

static const struct WildPokemonInfo sRoute6_LandMonsInfoMorning = {15, sRoute6_LandMonsMorning};

static const struct WildPokemon sRoute6_LandMonsNight[] =
{
	{20, 22, SPECIES_BUNNELBY},
	{20, 22, SPECIES_SPINARAK},
	{20, 22, SPECIES_SHINX},
	{20, 22, SPECIES_DEERLING},
	{20, 22, SPECIES_BUNNELBY},
	{20, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_KRICKETOT},
	{21, 22, SPECIES_DEERLING},
	{21, 22, SPECIES_KRICKETOT},
	{22, 22, SPECIES_ARIADOS},
	{22, 22, SPECIES_LUXIO},
};

static const struct WildPokemonInfo sRoute6_LandMonsInfoNight = {15, sRoute6_LandMonsNight};

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

static const struct WildPokemonInfo sRoute7_LandMonsInfoNight = {15, sRoute7_LandMonsNight};

static const struct WildPokemon sRoute8_LandMonsNight[] =
{
	{22, 25, SPECIES_SNOVER},
	{22, 25, SPECIES_SNORUNT},
	{22, 25, SPECIES_SNEASEL},
	{22, 25, SPECIES_SNORUNT},
	{22, 25, SPECIES_CUBCHOO},
	{22, 25, SPECIES_DEERLING_WINTER},
	{22, 25, SPECIES_DEERLING_WINTER},
	{22, 25, SPECIES_FLAAFFY},
	{23, 25, SPECIES_SNOVER},
	{23, 25, SPECIES_SNORUNT},
	{23, 25, SPECIES_MINIOR_SHIELD},
	{23, 25, SPECIES_MINIOR_SHIELD},
};

static const struct WildPokemonInfo sRoute8_LandMonsInfoNight = {15, sRoute8_LandMonsNight};

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

static const struct WildPokemonInfo sFrozenForest_LandMonsInfoNight = {15, sFrozenForest_LandMonsNight};

static const struct WildPokemon sRoute11_LandMonsNight[] =
{
	{26, 29, SPECIES_NOCTOWL},
	{26, 29, SPECIES_EXEGGCUTE},
	{26, 29, SPECIES_SPOINK},
	{26, 29, SPECIES_SPOINK},
	{26, 29, SPECIES_GULPIN},
	{26, 29, SPECIES_MEDITITE},
	{26, 29, SPECIES_MEDITITE},
	{27, 29, SPECIES_TOGEDEMARU},
	{29, 29, SPECIES_NOCTOWL},
	{29, 29, SPECIES_GULPIN},
	{29, 29, SPECIES_NOCTOWL},
	{29, 29, SPECIES_GULPIN},
};

static const struct WildPokemonInfo sRoute11_LandMonsInfoNight = {15, sRoute11_LandMonsNight};

static const struct WildPokemon sRoute12_LandMonsNight[] =
{
	{29, 32, SPECIES_HOOTHOOT},
	{33, 36, SPECIES_ROCKRUFF},
	{33, 36, SPECIES_GOTHITA},
	{33, 36, SPECIES_MIENFOO},
	{33, 36, SPECIES_PONYTA},
	{33, 36, SPECIES_SNUBBULL},
	{34, 36, SPECIES_GOTHITA},
	{34, 36, SPECIES_MIENFOO},
	{34, 36, SPECIES_DEERLING_SUMMER},
	{33, 36, SPECIES_DEERLING_SUMMER},
	{34, 36, SPECIES_NOCTOWL},
	{35, 36, SPECIES_DEDENNE},
};

static const struct WildPokemonInfo sRoute12_LandMonsInfoNight = {15, sRoute12_LandMonsNight};

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

static const struct WildPokemonInfo sRoute14_LandMonsInfoNight = {15, sRoute14_LandMonsNight};

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

static const struct WildPokemonInfo sVivillWoods_LandMonsInfoNight = {15, sVivillWoods_LandMonsNight};

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

static const struct WildPokemonInfo sRoute17_LandMonsInfoNight = {15, sRoute17_LandMonsNight};

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

static const struct WildPokemonInfo sCootesBog_LandMonsInfoNight = {15, sCootesBog_LandMonsNight};

static const struct WildPokemon sMagnoliaFields_LandMonsNight[] =
{
	{49, 53, SPECIES_NOCTOWL},
	{49, 53, SPECIES_FURFROU},
	{49, 53, SPECIES_TRANQUILL},
	{49, 53, SPECIES_MUDSDALE},
	{49, 53, SPECIES_MUDSDALE},
	{49, 53, SPECIES_GOGOAT},
	{49, 53, SPECIES_FURFROU},
	{49, 53, SPECIES_GOGOAT},
	{50, 53, SPECIES_MILTANK},
	{50, 53, SPECIES_MILTANK},
	{50, 53, SPECIES_MILTANK},
	{50, 53, SPECIES_TAUROS},
};

static const struct WildPokemonInfo sMagnoliaFields_LandMonsInfoNight = {15, sMagnoliaFields_LandMonsNight};

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
	{53, 57, SPECIES_SUDOWOODO},
	{53, 57, SPECIES_SUDOWOODO},
	{53, 57, SPECIES_HAPPINY},
};

static const struct WildPokemonInfo sRoute18_LandMonsInfoNight = {15, sRoute18_LandMonsNight};

static const struct WildPokemon sRedwoodForest_LandMonsNight[] =
{
	{55, 65, SPECIES_ARIADOS},
	{55, 65, SPECIES_VIGOROTH},
	{55, 65, SPECIES_ARIADOS},
	{55, 65, SPECIES_VIGOROTH},
	{55, 65, SPECIES_URSARING},
	{55, 65, SPECIES_URSARING},
	{60, 65, SPECIES_HERACROSS},
	{60, 65, SPECIES_KOMALA},
	{60, 65, SPECIES_KOMALA},
	{60, 65, SPECIES_KOMALA},
	{60, 65, SPECIES_PASSIMIAN},
	{60, 65, SPECIES_ORANGURU},
};

static const struct WildPokemonInfo sRedwoodForest_LandMonsInfoNight = {15, sRedwoodForest_LandMonsNight};

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
		.mapGroup = MAP_GROUP(MAGNOLIA_FIELDS),
		.mapNum = MAP_NUM(MAGNOLIA_FIELDS),
		.landMonsInfo = &sMagnoliaFields_LandMonsInfoNight,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(REDWOOD_FOREST),
		.mapNum = MAP_NUM(REDWOOD_FOREST),
		.landMonsInfo = &sRedwoodForest_LandMonsInfoNight,
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
		.mapName = MAPSEC_ROUTE_2,
		.species = SPECIES_POOCHYENA,
	},
	{
		.mapName = MAPSEC_ROUTE_3,
		.species = SPECIES_SENTRET,
	},
	{
		.mapName = MAPSEC_ROUTE_4,
		.species = SPECIES_BURMY,
	},
	{
		.mapName = MAPSEC_CINDER_VOLCANO,
		.species = SPECIES_VULPIX,
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
		.mapName = MAPSEC_ANTISIS_SEWERS,
		.species = SPECIES_WHIRLIPEDE,
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
		.mapName = MAPSEC_MAGNOLIA_FIELDS,
		.species = SPECIES_QUILAVA,
	},
	{
		.mapName = MAPSEC_ROUTE_18,
		.species = SPECIES_BAYLEEF,
	},
	{
		.mapName = MAPSEC_REDWOOD_FOREST,
		.species = SPECIES_NINCADA,
	},
};

#endif

#ifdef SWARM_CHANGE_HOURLY
const u8 gSwarmOrders[31][24] =
{
	{2, 1, 14, 21, 5, 16, 3, 23, 7, 4, 18, 19, 13, 17, 6, 0, 8, 9, 20, 22, 10, 11, 15, 12},
	{16, 19, 13, 23, 7, 9, 21, 17, 22, 8, 4, 3, 6, 0, 11, 20, 12, 1, 10, 2, 15, 14, 18, 5},
	{17, 8, 16, 6, 12, 19, 18, 3, 14, 22, 13, 11, 23, 2, 7, 21, 20, 10, 5, 15, 9, 0, 1, 4},
	{13, 6, 15, 3, 14, 12, 0, 18, 10, 5, 2, 17, 16, 7, 9, 1, 4, 19, 11, 23, 21, 8, 20, 22},
	{12, 7, 18, 13, 10, 2, 5, 14, 11, 23, 20, 22, 8, 15, 17, 4, 19, 16, 0, 6, 21, 1, 9, 3},
	{8, 18, 12, 15, 20, 0, 1, 13, 5, 11, 14, 21, 17, 10, 4, 16, 22, 6, 2, 19, 23, 3, 7, 9},
	{13, 11, 7, 20, 22, 3, 14, 10, 18, 6, 5, 12, 15, 23, 19, 17, 21, 0, 9, 8, 2, 16, 4, 1},
	{11, 20, 4, 2, 16, 17, 13, 12, 0, 10, 15, 14, 1, 19, 5, 8, 9, 18, 7, 21, 3, 6, 22, 23},
	{22, 18, 11, 17, 2, 9, 20, 16, 0, 13, 1, 6, 3, 14, 15, 10, 5, 8, 23, 4, 12, 21, 19, 7},
	{2, 5, 11, 7, 3, 23, 19, 1, 9, 16, 13, 15, 21, 8, 20, 12, 18, 4, 14, 10, 6, 17, 22, 0},
	{10, 18, 5, 1, 13, 15, 22, 2, 4, 3, 17, 9, 19, 21, 0, 8, 16, 11, 12, 14, 7, 23, 6, 20},
	{6, 13, 0, 4, 22, 10, 23, 17, 8, 1, 5, 11, 2, 3, 12, 19, 15, 20, 18, 9, 14, 7, 21, 16},
	{0, 22, 17, 11, 8, 15, 9, 4, 2, 7, 21, 13, 12, 6, 14, 18, 10, 23, 1, 3, 5, 20, 16, 19},
	{15, 16, 20, 5, 4, 6, 2, 21, 3, 19, 7, 8, 14, 13, 10, 23, 11, 18, 22, 0, 17, 12, 1, 9},
	{7, 12, 2, 0, 18, 4, 16, 8, 20, 17, 22, 23, 9, 1, 5, 14, 6, 21, 15, 3, 13, 19, 10, 11},
	{21, 4, 8, 14, 15, 7, 17, 19, 6, 0, 9, 1, 20, 11, 2, 23, 12, 18, 3, 16, 22, 13, 5, 10},
	{5, 3, 9, 19, 6, 14, 15, 10, 21, 7, 12, 0, 20, 16, 23, 13, 1, 22, 8, 11, 4, 2, 17, 18},
	{18, 0, 1, 19, 16, 21, 4, 5, 2, 9, 23, 7, 20, 12, 22, 15, 3, 6, 8, 11, 13, 17, 14, 10},
	{15, 16, 21, 9, 19, 6, 12, 20, 13, 18, 8, 0, 10, 22, 3, 7, 23, 5, 4, 17, 11, 2, 14, 1},
	{3, 14, 20, 16, 15, 13, 8, 4, 1, 21, 10, 5, 12, 9, 23, 6, 0, 17, 19, 7, 11, 22, 2, 18},
	{9, 7, 23, 12, 0, 1, 4, 15, 19, 17, 10, 2, 22, 5, 16, 11, 3, 6, 21, 13, 20, 18, 8, 14},
	{1, 21, 19, 17, 15, 23, 10, 6, 9, 12, 11, 0, 4, 3, 8, 22, 7, 14, 16, 20, 18, 5, 13, 2},
	{4, 9, 22, 12, 23, 11, 7, 5, 6, 2, 21, 20, 18, 14, 1, 10, 3, 15, 13, 17, 16, 19, 8, 0},
	{1, 2, 3, 10, 17, 5, 4, 22, 12, 20, 14, 9, 0, 18, 23, 15, 7, 13, 21, 11, 8, 19, 16, 6},
	{20, 23, 0, 19, 8, 18, 11, 22, 15, 14, 6, 2, 4, 12, 13, 3, 17, 7, 21, 16, 1, 9, 5, 10},
	{23, 10, 17, 19, 9, 14, 6, 7, 16, 12, 15, 18, 0, 4, 11, 2, 1, 3, 8, 5, 20, 22, 13, 21},
	{15, 21, 6, 18, 11, 22, 8, 4, 1, 7, 19, 16, 5, 20, 3, 10, 14, 2, 17, 12, 0, 9, 23, 13},
	{14, 17, 10, 9, 1, 8, 11, 7, 23, 15, 0, 5, 20, 19, 2, 16, 13, 3, 6, 18, 22, 4, 12, 21},
	{19, 15, 6, 22, 0, 20, 23, 11, 17, 14, 13, 16, 10, 1, 21, 9, 2, 12, 4, 7, 18, 5, 3, 8},
	{6, 4, 19, 16, 21, 22, 23, 9, 8, 20, 3, 10, 11, 12, 18, 5, 14, 2, 13, 1, 7, 15, 0, 17},
	{3, 18, 22, 8, 6, 1, 2, 0, 12, 14, 16, 4, 7, 9, 5, 13, 23, 17, 21, 20, 19, 10, 11, 15},
};
#endif

const u16 gSwarmTableLength = NELEMS(gSwarmTable);
