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

const struct WildPokemon gRoute21AndSecretTrail_LandMonsNight[] = 
{
	{47, 50, SPECIES_FALINKS},
	{48, 51, SPECIES_PRIMEAPE},
	{47, 50, SPECIES_GOGOAT},
	{48, 51, SPECIES_GOGOAT},
	{47, 50, SPECIES_MINIOR_SHIELD},
	{48, 51, SPECIES_VIBRAVA},
	{48, 51, SPECIES_PRIMEAPE},
	{47, 50, SPECIES_FALINKS},
	{48, 51, SPECIES_VIBRAVA},
	{49, 52, SPECIES_MANDIBUZZ},
	{48, 51, SPECIES_VIBRAVA},
	{49, 52, SPECIES_MANDIBUZZ}
};

const struct WildPokemon gRoute24_LandMonsNight[] =
{
	{53, 56, SPECIES_GRIMER_A},
	{53, 56, SPECIES_PAWNIARD},
	{54, 57, SPECIES_STOUTLAND},
	{54, 57, SPECIES_SUDOWOODO},
	{54, 58, SPECIES_MUK_A},
	{54, 57, SPECIES_CORVIKNIGHT},
	{53, 56, SPECIES_MIMIKYU},
	{54, 57, SPECIES_MIMIKYU},
	{54, 57, SPECIES_LYCANROC_N},
	{54, 58, SPECIES_MANDIBUZZ},
	{54, 58, SPECIES_CONKELDURR}, 
	{54, 58, SPECIES_MANDIBUZZ}
};

const struct WildPokemon gUteyanRuins_LandMonsNight[] =
{
	{53, 56, SPECIES_ELGYEM},
	{53, 56, SPECIES_DOTTLER},
	{54, 57, SPECIES_RUNERIGUS},
	{54, 57, SPECIES_BEHEEYEM},
	{54, 58, SPECIES_MISDREAVUS},
	{54, 57, SPECIES_MISDREAVUS},
	{53, 56, SPECIES_ORBEETLE},
	{54, 57, SPECIES_ORBEETLE},
	{54, 57, SPECIES_DUSCLOPS},
	{54, 58, SPECIES_DUSCLOPS},
	{54, 58, SPECIES_MISMAGIUS}, 
	{54, 58, SPECIES_MISMAGIUS}
};

const struct WildPokemon gVictoryRoad_LandMonsNight[] =
{
	{54, 57, SPECIES_MIENSHAO},
	{54, 57, SPECIES_SKARMORY},
	{55, 58, SPECIES_WEEZING_G},
	{55, 58, SPECIES_MANDIBUZZ},
	{55, 59, SPECIES_MORPEKO},
	{55, 58, SPECIES_PRIMEAPE},
	{54, 57, SPECIES_MANDIBUZZ},
	{55, 58, SPECIES_CRABOMINABLE},
	{55, 58, SPECIES_KOMMO_O},
	{55, 59, SPECIES_TREVENANT},
	{55, 59, SPECIES_KOMMO_O}, 
	{55, 59, SPECIES_TREVENANT}
};

const struct WildPokemon gProfessorsConservatory_Grass_LandMonsMorning[] =
{
	{5, 5, SPECIES_BULBASAUR},
	{5, 5, SPECIES_CHIKORITA},
	{5, 5, SPECIES_TREECKO},
	{5, 5, SPECIES_TURTWIG},
	{5, 5, SPECIES_SNIVY},
	{5, 5, SPECIES_CHESPIN},
	{5, 5, SPECIES_TREECKO},
	{5, 5, SPECIES_TURTWIG},
	{5, 5, SPECIES_ROWLET},
	{5, 5, SPECIES_GROOKEY},
	{5, 5, SPECIES_ROWLET}, 
	{5, 5, SPECIES_GROOKEY}
};

const struct WildPokemon gProfessorsConservatory_Grass_LandMonsEvening[] =
{
	{5, 5, SPECIES_SNIVY},
	{5, 5, SPECIES_CHESPIN},
	{5, 5, SPECIES_BULBASAUR},
	{5, 5, SPECIES_CHIKORITA},
	{5, 5, SPECIES_ROWLET},
	{5, 5, SPECIES_GROOKEY},
	{5, 5, SPECIES_BULBASAUR},
	{5, 5, SPECIES_CHIKORITA},
	{5, 5, SPECIES_TREECKO},
	{5, 5, SPECIES_TURTWIG},
	{5, 5, SPECIES_TREECKO}, 
	{5, 5, SPECIES_TURTWIG}
};

const struct WildPokemon gProfessorsConservatory_Grass_LandMonsNight[] =
{
	{5, 5, SPECIES_ROWLET},
	{5, 5, SPECIES_GROOKEY},
	{5, 5, SPECIES_SNIVY},
	{5, 5, SPECIES_CHESPIN},
	{5, 5, SPECIES_TREECKO},
	{5, 5, SPECIES_TURTWIG},
	{5, 5, SPECIES_SNIVY},
	{5, 5, SPECIES_CHESPIN},
	{5, 5, SPECIES_BULBASAUR},
	{5, 5, SPECIES_CHIKORITA},
	{5, 5, SPECIES_BULBASAUR}, 
	{5, 5, SPECIES_CHIKORITA}
};

const struct WildPokemon gProfessorsConservatory_Fire_LandMonsMorning[] =
{
	{5, 5, SPECIES_TORCHIC},
	{5, 5, SPECIES_FENNEKIN},
	{5, 5, SPECIES_CHIMCHAR},
	{5, 5, SPECIES_LITTEN},
	{5, 5, SPECIES_CYNDAQUIL},
	{5, 5, SPECIES_TEPIG},
	{5, 5, SPECIES_CHIMCHAR},
	{5, 5, SPECIES_LITTEN},
	{5, 5, SPECIES_CHARMANDER},
	{5, 5, SPECIES_SCORBUNNY},
	{5, 5, SPECIES_CHARMANDER}, 
	{5, 5, SPECIES_SCORBUNNY}
};

const struct WildPokemon gProfessorsConservatory_Fire_LandMonsEvening[] =
{
	{5, 5, SPECIES_CYNDAQUIL},
	{5, 5, SPECIES_TEPIG},
	{5, 5, SPECIES_CHARMANDER},
	{5, 5, SPECIES_SCORBUNNY},
	{5, 5, SPECIES_TORCHIC},
	{5, 5, SPECIES_FENNEKIN},
	{5, 5, SPECIES_CHARMANDER},
	{5, 5, SPECIES_SCORBUNNY},
	{5, 5, SPECIES_CHIMCHAR},
	{5, 5, SPECIES_LITTEN},
	{5, 5, SPECIES_CHIMCHAR}, 
	{5, 5, SPECIES_LITTEN}
};

const struct WildPokemon gProfessorsConservatory_Fire_LandMonsNight[] =
{
	{5, 5, SPECIES_CHIMCHAR},
	{5, 5, SPECIES_LITTEN},
	{5, 5, SPECIES_CYNDAQUIL},
	{5, 5, SPECIES_TEPIG},
	{5, 5, SPECIES_CHARMANDER},
	{5, 5, SPECIES_SCORBUNNY},
	{5, 5, SPECIES_CYNDAQUIL},
	{5, 5, SPECIES_TEPIG},
	{5, 5, SPECIES_TORCHIC},
	{5, 5, SPECIES_FENNEKIN},
	{5, 5, SPECIES_TORCHIC}, 
	{5, 5, SPECIES_FENNEKIN}
};

const struct WildPokemon gProfessorsConservatory_Water_LandMonsMorning[] =
{
	{5, 5, SPECIES_POPPLIO},
	{5, 5, SPECIES_SQUIRTLE},
	{5, 5, SPECIES_TOTODILE},
	{5, 5, SPECIES_MUDKIP},
	{5, 5, SPECIES_PIPLUP},
	{5, 5, SPECIES_OSHAWOTT},
	{5, 5, SPECIES_TOTODILE},
	{5, 5, SPECIES_MUDKIP},
	{5, 5, SPECIES_SOBBLE},
	{5, 5, SPECIES_FROAKIE},
	{5, 5, SPECIES_SOBBLE}, 
	{5, 5, SPECIES_FROAKIE}
};

const struct WildPokemon gProfessorsConservatory_Water_LandMonsEvening[] =
{
	{5, 5, SPECIES_TOTODILE},
	{5, 5, SPECIES_MUDKIP},
	{5, 5, SPECIES_POPPLIO},
	{5, 5, SPECIES_SQUIRTLE},
	{5, 5, SPECIES_SOBBLE},
	{5, 5, SPECIES_FROAKIE},
	{5, 5, SPECIES_POPPLIO},
	{5, 5, SPECIES_SQUIRTLE},
	{5, 5, SPECIES_PIPLUP},
	{5, 5, SPECIES_OSHAWOTT},
	{5, 5, SPECIES_PIPLUP}, 
	{5, 5, SPECIES_OSHAWOTT}
};

const struct WildPokemon gProfessorsConservatory_Water_LandMonsNight[] =
{
	{5, 5, SPECIES_SOBBLE},
	{5, 5, SPECIES_FROAKIE},
	{5, 5, SPECIES_PIPLUP},
	{5, 5, SPECIES_OSHAWOTT},
	{5, 5, SPECIES_POPPLIO},
	{5, 5, SPECIES_SQUIRTLE},
	{5, 5, SPECIES_PIPLUP},
	{5, 5, SPECIES_OSHAWOTT},
	{5, 5, SPECIES_TOTODILE},
	{5, 5, SPECIES_MUDKIP},
	{5, 5, SPECIES_TOTODILE}, 
	{5, 5, SPECIES_MUDKIP}
};

const struct WildPokemonInfo gVarisiForest_LandMonsNightInfo = {14, gVarisiForest_LandMonsNight};
const struct WildPokemonInfo gRubarrDesert_LandMonsNightInfo = {1, gRubarrDesert_LandMonsNight};
const struct WildPokemonInfo gHeleoRanch_LandMonsNightInfo = {21, gHeleoRanch_LandMonsNight};
const struct WildPokemonInfo gForgottenManseExterior_LandMonsNightInfo = {21, gForgottenManseExterior_LandMonsNight};
const struct WildPokemonInfo gDaimynCity_LandMonsNightInfo = {21, gDaimynCity_LandMonsNight};
const struct WildPokemonInfo gRoute10Cave_LandMonsNightInfo = {5, gRoute10Cave_LandMonsNight};
const struct WildPokemonInfo gRoute11North_LandMonsNightInfo = {21, gRoute11North_LandMonsNight};
const struct WildPokemonInfo gPeradonForest_LandMonsNightInfo = {14, gPeradonForest_LandMonsNight};
const struct WildPokemonInfo gLakeLaplaz_LandMonsNightInfo = {21, gLakeLaplaz_LandMonsNight};
const struct WildPokemonInfo gRoute12West_LandMonsNightInfo = {21, gRoute12West_LandMonsNight};
const struct WildPokemonInfo gCalicinBay_LandMonsNightInfo = {21, gCalicinBay_LandMonsNight};
const struct WildPokemonInfo gRoute21AndSecretTrail_LandMonsNightInfo = {21, gRoute21AndSecretTrail_LandMonsNight};
const struct WildPokemonInfo gRoute24_LandMonsNightInfo = {21, gRoute24_LandMonsNight};
const struct WildPokemonInfo gUteyanRuins_LandMonsNightInfo = {21, gUteyanRuins_LandMonsNight};
const struct WildPokemonInfo gVictoryRoad_LandMonsNightInfo = {21, gVictoryRoad_LandMonsNight};
const struct WildPokemonInfo gProfessorsConservatory_Grass_LandMonsMorningInfo = {21, gProfessorsConservatory_Grass_LandMonsMorning};
const struct WildPokemonInfo gProfessorsConservatory_Grass_LandMonsEveningInfo = {21, gProfessorsConservatory_Grass_LandMonsEvening};
const struct WildPokemonInfo gProfessorsConservatory_Grass_LandMonsNightInfo = {21, gProfessorsConservatory_Grass_LandMonsNight};
const struct WildPokemonInfo gProfessorsConservatory_Fire_LandMonsMorningInfo = {21, gProfessorsConservatory_Fire_LandMonsMorning};
const struct WildPokemonInfo gProfessorsConservatory_Fire_LandMonsEveningInfo = {21, gProfessorsConservatory_Fire_LandMonsEvening};
const struct WildPokemonInfo gProfessorsConservatory_Fire_LandMonsNightInfo = {21, gProfessorsConservatory_Fire_LandMonsNight};
const struct WildPokemonInfo gProfessorsConservatory_Water_LandMonsMorningInfo = {21, gProfessorsConservatory_Water_LandMonsMorning};
const struct WildPokemonInfo gProfessorsConservatory_Water_LandMonsEveningInfo = {21, gProfessorsConservatory_Water_LandMonsEvening};
const struct WildPokemonInfo gProfessorsConservatory_Water_LandMonsNightInfo = {21, gProfessorsConservatory_Water_LandMonsNight};

const struct WildPokemonHeader gWildMonMorningHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.landMonsInfo = &gProfessorsConservatory_Grass_LandMonsMorningInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.landMonsInfo = &gProfessorsConservatory_Fire_LandMonsMorningInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_WATER_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_WATER_AREA),
		.landMonsInfo = &gProfessorsConservatory_Water_LandMonsMorningInfo,
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
		.mapGroup = MAP_GROUP(ROUTE_21),
		.mapNum = MAP_NUM(ROUTE_21),
		.landMonsInfo = &gRoute21AndSecretTrail_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(SECRET_PATH),
		.mapNum = MAP_NUM(SECRET_PATH),
		.landMonsInfo = &gRoute21AndSecretTrail_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_24),
		.mapNum = MAP_NUM(ROUTE_24),
		.landMonsInfo = &gRoute24_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_OVERWORLD),
		.mapNum = MAP_NUM(UTEYAN_RUINS_OVERWORLD),
		.landMonsInfo = &gUteyanRuins_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_OUTSIDE),
		.mapNum = MAP_NUM(VICTORY_ROAD_OUTSIDE),
		.landMonsInfo = &gVictoryRoad_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.landMonsInfo = &gProfessorsConservatory_Grass_LandMonsEveningInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.landMonsInfo = &gProfessorsConservatory_Fire_LandMonsEveningInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_WATER_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_WATER_AREA),
		.landMonsInfo = &gProfessorsConservatory_Water_LandMonsEveningInfo,
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
		.mapGroup = MAP_GROUP(ROUTE_21),
		.mapNum = MAP_NUM(ROUTE_21),
		.landMonsInfo = &gRoute21AndSecretTrail_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(SECRET_PATH),
		.mapNum = MAP_NUM(SECRET_PATH),
		.landMonsInfo = &gRoute21AndSecretTrail_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_24),
		.mapNum = MAP_NUM(ROUTE_24),
		.landMonsInfo = &gRoute24_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_OVERWORLD),
		.mapNum = MAP_NUM(UTEYAN_RUINS_OVERWORLD),
		.landMonsInfo = &gUteyanRuins_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_OUTSIDE),
		.mapNum = MAP_NUM(VICTORY_ROAD_OUTSIDE),
		.landMonsInfo = &gVictoryRoad_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.landMonsInfo = &gProfessorsConservatory_Grass_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.landMonsInfo = &gProfessorsConservatory_Fire_LandMonsNightInfo,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_WATER_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_WATER_AREA),
		.landMonsInfo = &gProfessorsConservatory_Water_LandMonsNightInfo,
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
