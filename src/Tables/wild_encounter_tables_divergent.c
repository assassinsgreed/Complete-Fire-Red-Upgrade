#include "../config.h"
#include "../../include/global.h"
#include "../../include/constants/maps.h"
#include "../../include/wild_encounter.h"
#include "../../include/constants/region_map_sections.h"
#include "../../include/constants/species.h"

/*
USED WHEN FLAG_DIVERGENT_WILD_ENCOUNTERS IS ON!
Replaces standard encounters with an alternate pokedex for every encounter table, providing a fresh experience

wild_encounter_tables_divergent.c
	day/night and/or regular map wild encounter species

tables to edit:
	gDivergentWildMonDefaultHeaders
	gDivergentWildMonEveningNightHeaders
	gDivergentSwarmTable

*/

// TODO: All. For maps that don't have a specific encounter type (ex. towns, or routes without water, etc) they need to make sure nothing appears in the dexnav

const struct WildPokemon gDivergentRoute1_LandMonsDefault[] =
{
	{2, 3, SPECIES_ZIGZAGOON_G}, // 20
	{2, 3, SPECIES_STARLY}, // 20
	{2, 4, SPECIES_ZIGZAGOON_G}, // 10
	{2, 4, SPECIES_STARLY}, // 10
	{2, 3, SPECIES_DUCKLETT}, // 10
	{2, 3, SPECIES_SHINX}, // 10
	{2, 4, SPECIES_DUCKLETT}, // 5
	{2, 4, SPECIES_DUCKLETT}, // 5
	{3, 4, SPECIES_SHINX}, // 4
	{3, 4, SPECIES_ZIGZAGOON_G}, // 4
	{4, 4, SPECIES_ZIGZAGOON_G}, // 1
	{4, 4, SPECIES_SHINX}, // 1
};

const struct WildPokemon gDivergentVarisiForest_LandMonsDefault[] =
{
	{3, 6, SPECIES_CATERPIE}, // 20
	{3, 6, SPECIES_ODDISH}, // 20
	{3, 7, SPECIES_METAPOD}, // 10
	{2, 6, SPECIES_PANSAGE}, // 10
	{3, 6, SPECIES_SEWADDLE}, // 10
	{3, 7, SPECIES_BUNNELBY}, // 10
	{3, 7, SPECIES_SEWADDLE}, // 5
	{4, 7, SPECIES_STUNKY}, // 5
	{3, 6, SPECIES_MUNNA}, // 4
	{3, 7, SPECIES_MUNNA}, // 4
	{4, 6, SPECIES_MUNNA}, // 1
	{4, 7, SPECIES_MUNNA}, // 1
};

const struct WildPokemon gDivergentVarisiForest_LandMonsEveningNight[] =
{
	{3, 6, SPECIES_WEEDLE}, // 20
	{3, 6, SPECIES_ODDISH}, // 20
	{3, 7, SPECIES_KAKUNA}, // 10
	{2, 6, SPECIES_PANSAGE}, // 10
	{3, 6, SPECIES_SEWADDLE}, // 10
	{3, 7, SPECIES_BUNNELBY}, // 10
	{3, 7, SPECIES_SEWADDLE}, // 5
	{4, 7, SPECIES_STUNKY}, // 5
	{3, 6, SPECIES_MUNNA}, // 4
	{3, 7, SPECIES_MUNNA}, // 4
	{4, 6, SPECIES_MUNNA}, // 1
	{4, 7, SPECIES_MUNNA}, // 1
};

const struct WildPokemonInfo gDivergentEmpty = {0, NULL};

// Default
const struct WildPokemonInfo gDivergentRoute1_LandMonsDefaultInfo = {21, gDivergentRoute1_LandMonsDefault};
const struct WildPokemonInfo gDivergentVarisiForest_LandMonsDefaultInfo = {14, gDivergentVarisiForest_LandMonsDefault};

// Evening / Night
const struct WildPokemonInfo gDivergentVarisiForest_LandMonsEveningNightInfo = {14, gDivergentVarisiForest_LandMonsEveningNight};

// Null entries fall back to the first encounter table in the divergentDefault header table, so all must be defined!
const struct WildPokemonHeader gDivergentWildMonDefaultHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_1),
		.mapNum = MAP_NUM(ROUTE_1),
		.landMonsInfo = &gDivergentRoute1_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gDivergentVarisiForest_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	}
};

// Null entries will keep regular encounters defined in daytime table
const struct WildPokemonHeader gDivergentWildMonEveningNightHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gDivergentVarisiForest_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	}
};

const struct SwarmData gDivergentSwarmTable[] =
{
	// {
	// 	.mapName = MAPSEC_ROUTE_3,
	// 	.species = SPECIES_RATTATA,
	// },
};

#ifdef SWARM_CHANGE_HOURLY
// Same as base swarms
#endif

const u16 gDivergentSwarmTableLength = NELEMS(gDivergentSwarmTable);
