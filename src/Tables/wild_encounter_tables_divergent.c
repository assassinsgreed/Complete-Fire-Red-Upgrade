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

const struct WildPokemon gDivergentRubarrDesert_LandMonsDefault[] =
{
	{7, 9, SPECIES_DWEBBLE}, // 20
	{7, 9, SPECIES_MARACTUS}, // 20
	{7, 10, SPECIES_BALTOY}, // 10
	{8, 10, SPECIES_SILICOBRA}, // 10
	{7, 10, SPECIES_SKORUPI}, // 10
	{9, 11, SPECIES_SKORUPI}, // 10
	{8, 11, SPECIES_BALTOY}, // 5
	{7, 11, SPECIES_SILICOBRA}, // 5
	{8, 10, SPECIES_SILICOBRA}, // 4
	{9, 12, SPECIES_CUBONE_A}, // 4
	{10, 12, SPECIES_CUBONE_A}, // 1
	{9, 12, SPECIES_CUBONE_A}, // 1
};

const struct WildPokemon gDivergentRubarrDesert_WaterMonsDefault[] =
{
	{15, 25, SPECIES_BARBOACH}, // 60
	{25, 30, SPECIES_WHISCASH}, // 30
	{20, 25, SPECIES_BARBOACH}, // 5
	{20, 30, SPECIES_BARBOACH}, // 4
	{23, 27, SPECIES_BARBOACH}, // 1
};

const struct WildPokemon gDivergentRubarrDesert_FishingMonsDefault[] =
{
	{3, 7, SPECIES_BARBOACH}, // 70
	{4, 8, SPECIES_FEEBAS}, // 30
	{20, 25, SPECIES_BARBOACH}, // 60
	{20, 25, SPECIES_FEEBAS}, // 20
	{19, 26, SPECIES_FEEBAS}, // 20
	{35, 40, SPECIES_WHISCASH}, // 40
	{33, 41, SPECIES_WHISCASH}, // 40
	{35, 40, SPECIES_FEEBAS}, // 15
	{36, 42, SPECIES_FEEBAS}, // 4
	{38, 44, SPECIES_WHISCASH}, // 1
};

const struct WildPokemon gDivergentRubarrDesertB2f_LandMonsDefault[] =
{
	{49, 54, SPECIES_WOOBAT}, // 20
	{49, 54, SPECIES_SANDACONDA}, // 20
	{50, 55, SPECIES_STEELIX}, // 10
	{50, 55, SPECIES_SWOOBAT}, // 10
	{50, 55, SPECIES_DIGLETT_A}, // 10
	{49, 54, SPECIES_DUGTRIO_A}, // 10
	{49, 54, SPECIES_SANDACONDA}, // 5
	{49, 54, SPECIES_CRUSTLE}, // 5
	{50, 56, SPECIES_CRUSTLE}, // 4
	{50, 56, SPECIES_SANDACONDA}, // 4
	{50, 56, SPECIES_CRUSTLE}, // 1
	{50, 56, SPECIES_CRUSTLE}, // 1
};

const struct WildPokemon gDivergentRubarrDesertB2f_RockMonsDefault[] =
{
	{50, 55, SPECIES_GRAVELER_A}, // 60
	{50, 55, SPECIES_NOSEPASS}, // 30
	{50, 55, SPECIES_CRUSTLE}, // 5
	{50, 55, SPECIES_GOLEM_A}, // 4
	{50, 55, SPECIES_GOLEM_A}, // 1
};

const struct WildPokemon gDivergentTormaCaveB1f_LandMonsDefault[] =
{
	{9, 13, SPECIES_ANORITH}, // 20
	{10, 12, SPECIES_ARON}, // 20
	{11, 14, SPECIES_ARON}, // 10
	{8, 13, SPECIES_WOOBAT}, // 10
	{9, 14, SPECIES_WOOBAT}, // 10
	{10, 13, SPECIES_SHUPPET}, // 10
	{11, 14, SPECIES_MAGNEMITE}, // 5
	{9, 14, SPECIES_SHUPPET}, // 5
	{10, 12, SPECIES_MAGNEMITE}, // 4
	{9, 13, SPECIES_ANORITH}, // 4
	{11, 14, SPECIES_LARVITAR}, // 1
	{12, 13, SPECIES_LARVITAR}, // 1
};

const struct WildPokemon gDivergentTormaCaveB1f_RockMonsDefault[] =
{
	{10, 15, SPECIES_GEODUDE_A}, // 60
	{10, 15, SPECIES_DWEBBLE}, // 30
	{10, 15, SPECIES_GEODUDE_A}, // 5
	{10, 15, SPECIES_ARON}, // 4
	{10, 15, SPECIES_ARON}, // 1
};

const struct WildPokemon gDivergentTormaCaveB1f_WaterMonsDefault[] =
{
	{15, 25, SPECIES_POLIWAG}, // 60
	{25, 30, SPECIES_DEWPIDER}, // 30
	{20, 25, SPECIES_ARAQUANID}, // 5
	{20, 30, SPECIES_POLIWAG}, // 4
	{23, 27, SPECIES_POLIWAG}, // 1
};

const struct WildPokemon gDivergentTormaCaveB1f_FishingMonsDefault[] =
{
	{3, 7, SPECIES_TYMPOLE}, // 70
	{4, 8, SPECIES_TYNAMO}, // 30
	{20, 25, SPECIES_TYNAMO}, // 60
	{20, 25, SPECIES_EELEKTRIK}, // 20
	{19, 26, SPECIES_PALPITOAD}, // 20
	{35, 40, SPECIES_PALPITOAD}, // 40
	{33, 41, SPECIES_PALPITOAD}, // 40
	{35, 40, SPECIES_EELEKTRIK}, // 15
	{36, 42, SPECIES_EELEKTRIK}, // 4
	{38, 44, SPECIES_EELEKTROSS}, // 1
};

const struct WildPokemon gDivergentTormaCaveB2f_LandMonsDefault[] =
{
	{9, 13, SPECIES_VANILLITE}, // 20
	{10, 12, SPECIES_SPHEAL}, // 20
	{11, 14, SPECIES_SMOOCHUM}, // 10
	{8, 13, SPECIES_SWINUB}, // 10
	{9, 14, SPECIES_SANDSHREW_A}, // 10
	{10, 13, SPECIES_VANILLITE}, // 10
	{11, 14, SPECIES_SMOOCHUM}, // 5
	{9, 14, SPECIES_SANDSHREW_A}, // 5
	{10, 12, SPECIES_SANDSHREW_A}, // 4
	{9, 13, SPECIES_SPHEAL}, // 4
	{11, 14, SPECIES_SANDSHREW_A}, // 1
	{12, 13, SPECIES_SPHEAL}, // 1
};

const struct WildPokemon gDivergentTormaCaveB2f_RockMonsDefault[] =
{
	{10, 15, SPECIES_NOSEPASS}, // 60
	{10, 15, SPECIES_ARON}, // 30
	{10, 15, SPECIES_NOSEPASS}, // 5
	{10, 15, SPECIES_ARON}, // 4
	{10, 15, SPECIES_ARON}, // 1
};

const struct WildPokemon gDivergentForgottenManseTunnel_LandMonsDefault[] =
{
	{19, 23, SPECIES_ANORITH}, // 20
	{18, 22, SPECIES_ANORITH}, // 20
	{18, 22, SPECIES_WOOBAT}, // 10
	{19, 23, SPECIES_DREEPY}, // 10
	{18, 22, SPECIES_NOSEPASS}, // 10
	{19, 23, SPECIES_NOSEPASS}, // 10
	{20, 24, SPECIES_NOSEPASS}, // 5
	{20, 24, SPECIES_NOSEPASS}, // 5
	{20, 24, SPECIES_WOOBAT}, // 4
	{20, 24, SPECIES_WOOBAT}, // 4
	{20, 24, SPECIES_WOOBAT}, // 1
	{20, 24, SPECIES_WOOBAT}, // 1
};

const struct WildPokemon gDivergentForgottenManseTunnel_FishingMonsDefault[] =
{
	{5, 15, SPECIES_ANORITH}, // 70
	{5, 15, SPECIES_ANORITH}, // 30
	{20, 24, SPECIES_FEEBAS}, // 60
	{19, 23, SPECIES_FEEBAS}, // 20
	{18, 24, SPECIES_WIMPOD}, // 20
	{38, 39, SPECIES_FEEBAS}, // 40
	{33, 38, SPECIES_ANORITH}, // 40
	{38, 40, SPECIES_ARMALDO}, // 15
	{35, 39, SPECIES_GOLISOPOD}, // 4
	{36, 39, SPECIES_GOLISOPOD}, // 1
};

const struct WildPokemon gDivergentForgottenManseExterior_LandMonsDefault[] =
{
	{19, 23, SPECIES_ORICORIO_S}, // 20
	{19, 23, SPECIES_DRIFLOON}, // 20
	{19, 23, SPECIES_SOLOSIS}, // 10
	{20, 24, SPECIES_INDEEDEE}, // 10
	{19, 25, SPECIES_GASTLY}, // 10
	{19, 24, SPECIES_GASTLY}, // 10
	{20, 24, SPECIES_ORICORIO_S}, // 5
	{20, 24, SPECIES_IMPIDIMP}, // 5
	{20, 24, SPECIES_IMPIDIMP}, // 4
	{20, 23, SPECIES_DUOSION}, // 4
	{20, 25, SPECIES_IMPIDIMP}, // 1
	{20, 24, SPECIES_DUOSION}, // 1
};

const struct WildPokemon gDivergentForgottenManse1f_LandMonsDefault[] =
{
	{22, 25, SPECIES_SHUPPET}, // 20
	{21, 26, SPECIES_SINISTEA}, // 20
	{21, 25, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_SINISTEA}, // 10
	{21, 26, SPECIES_SHUPPET}, // 10
	{22, 26, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_ROTOM}, // 5
	{21, 24, SPECIES_POLTEAGEIST}, // 5
	{21, 25, SPECIES_POLTEAGEIST}, // 4
	{22, 26, SPECIES_POLTEAGEIST}, // 4
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
};

const struct WildPokemon gDivergentForgottenManse2f_LandMonsDefault[] =
{
	{22, 25, SPECIES_SHUPPET}, // 20
	{21, 26, SPECIES_SINISTEA}, // 20
	{21, 25, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_SINISTEA}, // 10
	{21, 26, SPECIES_SHUPPET}, // 10
	{22, 26, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_ROTOM}, // 5
	{21, 24, SPECIES_POLTEAGEIST}, // 5
	{21, 25, SPECIES_POLTEAGEIST}, // 4
	{22, 26, SPECIES_POLTEAGEIST}, // 4
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
};

const struct WildPokemon gDivergentForgottenManseBasement_LandMonsDefault[] =
{
	{22, 25, SPECIES_SHUPPET}, // 20
	{21, 26, SPECIES_SINISTEA}, // 20
	{21, 25, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_SINISTEA}, // 10
	{21, 26, SPECIES_SHUPPET}, // 10
	{22, 26, SPECIES_LITWICK}, // 10
	{22, 25, SPECIES_ROTOM}, // 5
	{21, 24, SPECIES_POLTEAGEIST}, // 5
	{21, 25, SPECIES_POLTEAGEIST}, // 4
	{22, 26, SPECIES_POLTEAGEIST}, // 4
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
	{23, 25, SPECIES_POLTEAGEIST_CHIPPED}, // 1
};

const struct WildPokemon gDivergentDaimynCityFactory_LandMonsDefault[] =
{
	{27, 29, SPECIES_ELEKID}, // 20
	{26, 30, SPECIES_ORICORIO_Y}, // 20
	{27, 30, SPECIES_VOLTORB}, // 10
	{26, 29, SPECIES_VOLTORB}, // 10
	{27, 30, SPECIES_TOGEDEMARU}, // 10
	{26, 30, SPECIES_MACHOKE}, // 10
	{26, 29, SPECIES_TRUBBISH}, // 5
	{27, 30, SPECIES_TRUBBISH}, // 5
	{26, 29, SPECIES_SKIPLOOM}, // 4
	{27, 30, SPECIES_SKIPLOOM}, // 4
	{26, 30, SPECIES_SKIPLOOM}, // 1
	{27, 30, SPECIES_SKIPLOOM}, // 1
};

const struct WildPokemon gDivergentDaimynCityFactory_RockMonsDefault[] =
{
	{25, 30, SPECIES_GEODUDE_A}, // 60
	{24, 29, SPECIES_GRAVELER_A}, // 30
	{24, 28, SPECIES_NOSEPASS}, // 5
	{25, 30, SPECIES_GEODUDE_A}, // 4
	{26, 29, SPECIES_GEODUDE_A}, // 1
};

const struct WildPokemon gDivergentRoute10Cave_LandMonsDefault[] =
{
	{25, 28, SPECIES_ARON}, // 20
	{26, 29, SPECIES_NOSEPASS}, // 20
	{26, 29, SPECIES_ARON}, // 10
	{26, 29, SPECIES_LAIRON}, // 10
	{26, 29, SPECIES_GOLETT}, // 10
	{25, 28, SPECIES_ONIX}, // 10
	{25, 28, SPECIES_ONIX}, // 5
	{25, 28, SPECIES_SHUPPET}, // 5
	{26, 29, SPECIES_SHUPPET}, // 4
	{25, 28, SPECIES_DEINO}, // 4
	{25, 28, SPECIES_DEINO}, // 1
	{26, 29, SPECIES_METANG}, // 1
};

const struct WildPokemon gDivergentRoute10Cave_RockMonsDefault[] =
{
	{22, 28, SPECIES_ARON}, // 60
	{21, 27, SPECIES_LAIRON}, // 30
	{25, 30, SPECIES_ARON}, // 5
	{25, 30, SPECIES_LAIRON}, // 4
	{25, 30, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentLakeLaplaz_LandMonsDefault[] =
{
	{36, 40, SPECIES_STARAVIA}, // 20
	{37, 41, SPECIES_KRICKETUNE}, // 20
	{36, 40, SPECIES_KADABRA}, // 10
	{35, 39, SPECIES_KADABRA}, // 10
	{36, 39, SPECIES_PETILIL}, // 10
	{36, 40, SPECIES_PETILIL}, // 10
	{37, 40, SPECIES_SWANNA}, // 5
	{37, 40, SPECIES_STARAVIA}, // 5
	{36, 41, SPECIES_SWANNA}, // 4
	{35, 40, SPECIES_SWANNA}, // 4
	{36, 40, SPECIES_AUDINO}, // 1
	{36, 41, SPECIES_AUDINO}, // 1
};

const struct WildPokemon gDivergentLakeLaplaz_LandMonsEveningNight[] =
{
	{36, 40, SPECIES_STARAVIA}, // 20
	{37, 41, SPECIES_KRICKETUNE}, // 20
	{36, 40, SPECIES_KADABRA}, // 10
	{35, 39, SPECIES_KADABRA}, // 10
	{36, 39, SPECIES_MURKROW}, // 10
	{36, 40, SPECIES_MURKROW}, // 10
	{37, 40, SPECIES_SWANNA}, // 5
	{37, 40, SPECIES_STARAVIA}, // 5
	{36, 41, SPECIES_SWANNA}, // 4
	{35, 40, SPECIES_SWANNA}, // 4
	{36, 40, SPECIES_AUDINO}, // 1
	{36, 41, SPECIES_AUDINO}, // 1
};

const struct WildPokemon gDivergentLakeLaplaz_WaterMonsDefault[] =
{
	{40, 45, SPECIES_STARYU}, // 60
	{40, 45, SPECIES_SKRELP}, // 30
	{40, 45, SPECIES_QWILFISH}, // 5
	{40, 45, SPECIES_QWILFISH}, // 4
	{40, 45, SPECIES_QWILFISH}, // 1
};

const struct WildPokemon gDivergentLakeLaplaz_FishingMonsDefault[] =
{
	{5, 20, SPECIES_STARYU}, // 70
	{5, 20, SPECIES_SKRELP}, // 30
	{25, 35, SPECIES_STARYU}, // 60
	{25, 35, SPECIES_SKRELP}, // 20
	{25, 35, SPECIES_QWILFISH}, // 20
	{45, 48, SPECIES_STARYU}, // 40
	{46, 50, SPECIES_SKRELP}, // 40
	{45, 49, SPECIES_STARMIE}, // 15
	{45, 48, SPECIES_DRAGALGE}, // 4
	{47, 53, SPECIES_DRAGALGE}, // 1
};

const struct WildPokemon gDivergentPeradonForestCommon_LandMonsDefault[] =
{
	{34, 36, SPECIES_SWADLOON}, // 20
	{34, 37, SPECIES_BUTTERFREE}, // 20
	{34, 35, SPECIES_DEERLING_AUTUMN}, // 10
	{34, 36, SPECIES_SWADLOON}, // 10
	{34, 37, SPECIES_AIPOM}, // 10
	{35, 37, SPECIES_AIPOM}, // 10
	{34, 36, SPECIES_DEERLING_AUTUMN}, // 5
	{34, 36, SPECIES_PANSAGE}, // 5
	{34, 37, SPECIES_PANSAGE}, // 4
	{35, 37, SPECIES_PINSIR}, // 4
	{35, 37, SPECIES_PANSAGE}, // 1
	{34, 36, SPECIES_PINSIR}, // 1
};

const struct WildPokemon gDivergentPeradonForestCommon_LandMonsEveningNight[] =
{
	{34, 36, SPECIES_SWADLOON}, // 20
	{34, 37, SPECIES_BUTTERFREE}, // 20
	{34, 35, SPECIES_MURKROW}, // 10
	{34, 36, SPECIES_SWADLOON}, // 10
	{34, 37, SPECIES_AIPOM}, // 10
	{35, 37, SPECIES_AIPOM}, // 10
	{34, 36, SPECIES_MURKROW}, // 5
	{34, 36, SPECIES_MORGREM}, // 5
	{34, 37, SPECIES_MORGREM}, // 4
	{35, 37, SPECIES_PINSIR}, // 4
	{35, 37, SPECIES_MORGREM}, // 1
	{34, 36, SPECIES_PINSIR}, // 1
};

const struct WildPokemon gDivergentPeradonForestCommon_WaterMonsDefault[] =
{
	{30, 35, SPECIES_MARILL}, // 60
	{30, 35, SPECIES_AZUMARILL}, // 30
	{30, 40, SPECIES_DUCKLETT}, // 5
	{30, 40, SPECIES_DUCKLETT}, // 4
	{30, 40, SPECIES_DUCKLETT}, // 1
};

const struct WildPokemon gDivergentPeradonForestCommon_FishingMonsDefault[] =
{
	{30, 35, SPECIES_POLIWAG}, // 70
	{30, 35, SPECIES_POLIWAG}, // 30
	{33, 37, SPECIES_POLIWAG}, // 60
	{33, 37, SPECIES_POLIWHIRL}, // 20
	{33, 37, SPECIES_MARILL}, // 20
	{40, 45, SPECIES_POLIWHIRL}, // 40
	{40, 45, SPECIES_POLIWHIRL}, // 40
	{40, 45, SPECIES_POLITOED}, // 15
	{40, 45, SPECIES_AZUMARILL}, // 4
	{40, 45, SPECIES_AZUMARILL}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoExterior_LandMonsDefault[] =
{
	{49, 52, SPECIES_VULPIX}, // 20
	{50, 53, SPECIES_STARAPTOR}, // 20
	{49, 52, SPECIES_SIMISEAR}, // 10
	{49, 52, SPECIES_SIMISEAR}, // 10
	{49, 52, SPECIES_PANSEAR}, // 10
	{50, 53, SPECIES_NUMEL}, // 10
	{50, 53, SPECIES_RAPIDASH}, // 5
	{49, 52, SPECIES_RAPIDASH}, // 5
	{50, 53, SPECIES_NUMEL}, // 4
	{49, 52, SPECIES_VULPIX}, // 4
	{49, 52, SPECIES_NUMEL}, // 1
	{50, 53, SPECIES_VULPIX}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoExterior_RockMonsDefault[] =
{
	{48, 53, SPECIES_GRAVELER_A}, // 60
	{48, 53, SPECIES_LAIRON}, // 30
	{48, 53, SPECIES_LAIRON}, // 5
	{48, 53, SPECIES_GRAVELER_A}, // 4
	{48, 53, SPECIES_GRAVELER_A}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF1_LandMonsDefault[] =
{
	{49, 52, SPECIES_MAGMAR}, // 20
	{50, 53, SPECIES_NUMEL}, // 20
	{49, 52, SPECIES_MAGMAR}, // 10
	{49, 52, SPECIES_NUMEL}, // 10
	{49, 52, SPECIES_CAMERUPT}, // 10
	{50, 53, SPECIES_GRAVELER_A}, // 10
	{50, 53, SPECIES_NINETALES}, // 5
	{49, 52, SPECIES_NINETALES}, // 5
	{50, 53, SPECIES_GRAVELER_A}, // 4
	{49, 52, SPECIES_SHELGON}, // 4
	{50, 53, SPECIES_MAGMORTAR}, // 1
	{50, 53, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF1_RockMonsDefault[] =
{
	{48, 53, SPECIES_ARON}, // 60
	{48, 53, SPECIES_LAIRON}, // 30
	{48, 53, SPECIES_LAIRON}, // 5
	{48, 53, SPECIES_ARON}, // 4
	{48, 53, SPECIES_AGGRON}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF1_WaterMonsDefault[] =
{
	{49, 52, SPECIES_MAGBY}, // 60
	{50, 53, SPECIES_MAGMAR}, // 30
	{50, 52, SPECIES_MAGMAR}, // 5
	{50, 53, SPECIES_MAGMAR}, // 4
	{50, 55, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoVolcanionRoom_LandMonsDefault[] =
{
	{49, 52, SPECIES_MAGMAR}, // 20
	{50, 53, SPECIES_NUMEL}, // 20
	{49, 52, SPECIES_MAGMAR}, // 10
	{49, 52, SPECIES_NUMEL}, // 10
	{49, 52, SPECIES_CAMERUPT}, // 10
	{50, 53, SPECIES_GRAVELER_A}, // 10
	{50, 53, SPECIES_NINETALES}, // 5
	{49, 52, SPECIES_NINETALES}, // 5
	{50, 53, SPECIES_GRAVELER_A}, // 4
	{49, 52, SPECIES_SHELGON}, // 4
	{50, 53, SPECIES_MAGMORTAR}, // 1
	{50, 53, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoVolcanionRoom_RockMonsDefault[] =
{
	{48, 53, SPECIES_ARON}, // 60
	{48, 53, SPECIES_LAIRON}, // 30
	{48, 53, SPECIES_LAIRON}, // 5
	{48, 53, SPECIES_ARON}, // 4
	{48, 53, SPECIES_AGGRON}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF2_LandMonsDefault[] =
{
	{49, 52, SPECIES_MAGMAR}, // 20
	{50, 53, SPECIES_NUMEL}, // 20
	{49, 52, SPECIES_MAGMAR}, // 10
	{49, 52, SPECIES_NUMEL}, // 10
	{49, 52, SPECIES_CAMERUPT}, // 10
	{50, 53, SPECIES_GRAVELER_A}, // 10
	{50, 53, SPECIES_NINETALES}, // 5
	{49, 52, SPECIES_NINETALES}, // 5
	{50, 53, SPECIES_GRAVELER_A}, // 4
	{49, 52, SPECIES_SHELGON}, // 4
	{50, 53, SPECIES_MAGMORTAR}, // 1
	{50, 53, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF2_WaterMonsDefault[] =
{
	{49, 52, SPECIES_MAGBY}, // 60
	{50, 53, SPECIES_MAGMAR}, // 30
	{50, 52, SPECIES_MAGMAR}, // 5
	{50, 53, SPECIES_MAGMAR}, // 4
	{50, 55, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoF3_LandMonsDefault[] =
{
	{49, 52, SPECIES_MAGMAR}, // 20
	{50, 53, SPECIES_NUMEL}, // 20
	{49, 52, SPECIES_MAGMAR}, // 10
	{49, 52, SPECIES_NUMEL}, // 10
	{49, 52, SPECIES_CAMERUPT}, // 10
	{50, 53, SPECIES_GRAVELER_A}, // 10
	{50, 53, SPECIES_NINETALES}, // 5
	{49, 52, SPECIES_NINETALES}, // 5
	{50, 53, SPECIES_GRAVELER_A}, // 4
	{49, 52, SPECIES_SHELGON}, // 4
	{50, 53, SPECIES_MAGMORTAR}, // 1
	{50, 53, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentOrichelleGarden_LandMonsDefault[] =
{
	{43, 46, SPECIES_JUMPLUFF}, // 20
	{42, 45, SPECIES_BUTTERFREE}, // 20
	{43, 46, SPECIES_JUMPLUFF}, // 10
	{44, 46, SPECIES_LURANTIS}, // 10
	{43, 46, SPECIES_AROMATISSE}, // 10
	{42, 45, SPECIES_SIMISAGE}, // 10
	{43, 46, SPECIES_SIMISAGE}, // 5
	{42, 45, SPECIES_LILLIGANT}, // 5
	{42, 45, SPECIES_BELLOSSOM}, // 4
	{43, 46, SPECIES_BELLOSSOM}, // 4
	{44, 46, SPECIES_BELLOSSOM}, // 1
	{44, 46, SPECIES_BELLOSSOM}, // 1
};

const struct WildPokemon gDivergentSeppireCoveOverworld_LandMonsDefault[] =
{
	{50, 53, SPECIES_PIDGEOTTO}, // 20
	{49, 52, SPECIES_GRAPPLOCT}, // 20
	{50, 53, SPECIES_LINOONE_G}, // 10
	{51, 53, SPECIES_ZANGOOSE}, // 10
	{50, 53, SPECIES_SEVIPER}, // 10
	{49, 52, SPECIES_DWEBBLE}, // 10
	{50, 53, SPECIES_LINOONE_G}, // 5
	{49, 52, SPECIES_EXEGGCUTE_A}, // 5
	{49, 52, SPECIES_EXEGGCUTE_A}, // 4
	{50, 53, SPECIES_EXEGGUTOR_A}, // 4
	{51, 53, SPECIES_EXEGGCUTE_A}, // 1
	{51, 53, SPECIES_EXEGGUTOR_A}, // 1
};

const struct WildPokemon gDivergentSeppireCoveOverworld_WaterMonsDefault[] =
{
	{45, 48, SPECIES_SKRELP}, // 60
	{46, 49, SPECIES_QWILFISH}, // 30
	{45, 48, SPECIES_DRAGALGE}, // 5
	{46, 49, SPECIES_DRAGALGE}, // 4
	{47, 50, SPECIES_DRAGALGE}, // 1
};

const struct WildPokemon gDivergentSeppireCoveOverworld_FishingMonsDefault[] =
{
	{5, 40, SPECIES_SKRELP}, // 70
	{5, 40, SPECIES_STARYU}, // 30
	{25, 40, SPECIES_SKRELP}, // 60
	{25, 40, SPECIES_SKRELP}, // 20
	{25, 40, SPECIES_STARYU}, // 20
	{45, 55, SPECIES_SKRELP}, // 40
	{45, 55, SPECIES_SKRELP}, // 40
	{45, 55, SPECIES_DRAGALGE}, // 15
	{45, 55, SPECIES_DRAGALGE}, // 4
	{45, 55, SPECIES_DRAGALGE}, // 1
};

const struct WildPokemon gDivergentSeppireCoveCommon_LandMonsDefault[] =
{
	{51, 56, SPECIES_WIMPOD}, // 20
	{51, 56, SPECIES_KRABBY}, // 20
	{52, 57, SPECIES_SIMIPOUR}, // 10
	{52, 57, SPECIES_EELEKTRIK}, // 10
	{52, 57, SPECIES_EELEKTRIK}, // 10
	{51, 56, SPECIES_PALPITOAD}, // 10
	{51, 56, SPECIES_WOOBAT}, // 5
	{51, 56, SPECIES_WOOBAT}, // 5
	{52, 58, SPECIES_GOLISOPOD}, // 4
	{52, 58, SPECIES_SEISMITOAD}, // 4
	{52, 58, SPECIES_GOLISOPOD}, // 1
	{52, 58, SPECIES_SEISMITOAD}, // 1
};

const struct WildPokemon gDivergentSeppireCoveCommon_RockMonsDefault[] =
{
	{50, 55, SPECIES_DWEBBLE}, // 60
	{50, 55, SPECIES_CRUSTLE}, // 30
	{50, 55, SPECIES_CRUSTLE}, // 5
	{50, 55, SPECIES_CRUSTLE}, // 4
	{50, 55, SPECIES_CRUSTLE}, // 1
};

const struct WildPokemon gDivergentSeppireCoveCommon_WaterMonsDefault[] =
{
	{51, 56, SPECIES_KRABBY}, // 60
	{51, 56, SPECIES_KINGLER}, // 30
	{52, 57, SPECIES_DRAGALGE}, // 5
	{52, 57, SPECIES_DRAGALGE}, // 4
	{55, 60, SPECIES_POLITOED}, // 1
};

const struct WildPokemon gDivergentSeppireCoveCommon_FishingMonsDefault[] =
{
	{5, 40, SPECIES_STARYU}, // 70
	{5, 40, SPECIES_SKRELP}, // 30
	{25, 45, SPECIES_STARYU}, // 60
	{25, 45, SPECIES_STARYU}, // 20
	{25, 45, SPECIES_SKRELP}, // 20
	{50, 60, SPECIES_STARYU}, // 40
	{50, 60, SPECIES_SKRELP}, // 40
	{50, 60, SPECIES_KRABBY}, // 15
	{50, 60, SPECIES_KRABBY}, // 4
	{50, 60, SPECIES_KRABBY}, // 1
};

const struct WildPokemon gDivergentMimmettJungleCommon_LandMonsDefault[] =
{
	{46, 49, SPECIES_ARIADOS}, // 20
	{47, 50, SPECIES_ELECTABUZZ}, // 20
	{46, 49, SPECIES_AIPOM}, // 10
	{47, 50, SPECIES_GLOOM}, // 10
	{46, 49, SPECIES_BEEDRILL}, // 10
	{47, 50, SPECIES_AMBIPOM}, // 10
	{47, 50, SPECIES_DRAPION}, // 5
	{46, 49, SPECIES_YANMA}, // 5
	{47, 50, SPECIES_TANGROWTH}, // 4
	{48, 51, SPECIES_VILEPLUME}, // 4
	{47, 50, SPECIES_VILEPLUME}, // 1
	{48, 51, SPECIES_ELECTIVIRE}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoBf1_LandMonsDefault[] =
{
	{49, 52, SPECIES_MAGMAR}, // 20
	{50, 53, SPECIES_NUMEL}, // 20
	{49, 52, SPECIES_MAGMAR}, // 10
	{49, 52, SPECIES_NUMEL}, // 10
	{49, 52, SPECIES_CAMERUPT}, // 10
	{50, 53, SPECIES_GRAVELER_A}, // 10
	{50, 53, SPECIES_NINETALES}, // 5
	{49, 52, SPECIES_NINETALES}, // 5
	{50, 53, SPECIES_GRAVELER_A}, // 4
	{49, 52, SPECIES_SHELGON}, // 4
	{50, 53, SPECIES_MAGMORTAR}, // 1
	{50, 53, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoBf1_RockMonsDefault[] =
{
	{48, 53, SPECIES_ARON}, // 60
	{48, 53, SPECIES_LAIRON}, // 30
	{48, 53, SPECIES_LAIRON}, // 5
	{48, 53, SPECIES_ARON}, // 4
	{48, 53, SPECIES_AGGRON}, // 1
};

const struct WildPokemon gDivergentCarnelidgeVolcanoBf1_WaterMonsDefault[] =
{
	{49, 52, SPECIES_MAGBY}, // 60
	{50, 53, SPECIES_MAGMAR}, // 30
	{50, 52, SPECIES_MAGMAR}, // 5
	{50, 53, SPECIES_MAGMAR}, // 4
	{50, 55, SPECIES_MAGMORTAR}, // 1
};

const struct WildPokemon gDivergentHessonPass1f_LandMonsDefault[] =
{
	{30, 34, SPECIES_CLEFAIRY}, // 20
	{31, 34, SPECIES_LAIRON}, // 20
	{30, 33, SPECIES_EELEKTRIK}, // 10
	{29, 34, SPECIES_HAWLUCHA}, // 10
	{31, 35, SPECIES_MEDICHAM}, // 10
	{30, 34, SPECIES_DIGGERSBY}, // 10
	{31, 33, SPECIES_ANORITH}, // 5
	{30, 34, SPECIES_ANORITH}, // 5
	{31, 33, SPECIES_ANORITH}, // 4
	{30, 35, SPECIES_PUPITAR}, // 4
	{31, 34, SPECIES_ANORITH}, // 1
	{29, 33, SPECIES_PUPITAR}, // 1
};

const struct WildPokemon gDivergentHessonPass1f_RockMonsDefault[] =
{
	{30, 35, SPECIES_GEODUDE_A}, // 60
	{30, 35, SPECIES_GRAVELER_A}, // 30
	{30, 35, SPECIES_GEODUDE_A}, // 5
	{30, 35, SPECIES_GEODUDE_A}, // 4
	{30, 35, SPECIES_GEODUDE_A}, // 1
};

const struct WildPokemon gDivergentHessonPass2f_LandMonsDefault[] =
{
	{52, 54, SPECIES_MEDICHAM}, // 20
	{52, 55, SPECIES_RHYHORN}, // 20
	{51, 53, SPECIES_DRUDDIGON}, // 10
	{51, 53, SPECIES_CLEFABLE}, // 10
	{52, 54, SPECIES_MACHOKE}, // 10
	{51, 54, SPECIES_DRUDDIGON}, // 10
	{51, 53, SPECIES_GOLURK}, // 5
	{50, 53, SPECIES_DOUBLADE}, // 5
	{50, 54, SPECIES_ARMALDO}, // 4
	{51, 54, SPECIES_RHYDON}, // 4
	{52, 55, SPECIES_ARMALDO}, // 1
	{52, 55, SPECIES_RHYDON}, // 1
};

const struct WildPokemon gDivergentHessonPass2f_RockMonsDefault[] =
{
	{50, 55, SPECIES_GRAVELER_A}, // 60
	{50, 55, SPECIES_GRAVELER_A}, // 30
	{50, 55, SPECIES_GOLEM_A}, // 5
	{50, 55, SPECIES_GOLEM_A}, // 4
	{50, 55, SPECIES_GOLEM_A}, // 1
};

const struct WildPokemon gDivergentHessonPassB1f_LandMonsDefault[] =
{
	{30, 34, SPECIES_RHYHORN}, // 20
	{31, 34, SPECIES_CLEFAIRY}, // 20
	{30, 33, SPECIES_MEDICHAM}, // 10
	{29, 34, SPECIES_HONEDGE}, // 10
	{31, 35, SPECIES_GOLETT}, // 10
	{30, 34, SPECIES_ANORITH}, // 10
	{31, 33, SPECIES_ANORITH}, // 5
	{30, 34, SPECIES_GOLETT}, // 5
	{31, 33, SPECIES_CLEFAIRY}, // 4
	{30, 35, SPECIES_PUPITAR}, // 4
	{31, 34, SPECIES_CLEFAIRY}, // 1
	{29, 33, SPECIES_PUPITAR}, // 1
};

const struct WildPokemon gDivergentHessonPassB1f_RockMonsDefault[] =
{
	{30, 35, SPECIES_ARON}, // 60
	{30, 35, SPECIES_ARON}, // 30
	{30, 35, SPECIES_LAIRON}, // 5
	{30, 35, SPECIES_LAIRON}, // 4
	{30, 35, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentCalicinBay_LandMonsDefault[] =
{
	{40, 42, SPECIES_SNOVER}, // 20
	{40, 42, SPECIES_SPHEAL}, // 20
	{41, 44, SPECIES_VANILLISH}, // 10
	{41, 43, SPECIES_SNOVER}, // 10
	{41, 44, SPECIES_ABOMASNOW}, // 10
	{41, 43, SPECIES_SEALEO}, // 10
	{42, 43, SPECIES_VANILLISH}, // 5
	{42, 44, SPECIES_CRYOGONAL}, // 5
	{42, 44, SPECIES_SANDSLASH_A}, // 4
	{42, 44, SPECIES_VANILLUXE}, // 4
	{42, 44, SPECIES_SANDSLASH_A}, // 1
	{42, 44, SPECIES_VANILLUXE}, // 1
};

const struct WildPokemon gDivergentCalicinBay_WaterMonsDefault[] =
{
	{44, 48, SPECIES_SEEL}, // 60
	{45, 49, SPECIES_DEWGONG}, // 30
	{44, 48, SPECIES_SEALEO}, // 5
	{45, 48, SPECIES_WALREIN}, // 4
	{44, 48, SPECIES_WALREIN}, // 1
};

const struct WildPokemon gDivergentCalicinBay_FishingMonsDefault[] =
{
	{5, 40, SPECIES_SEEL}, // 70
	{5, 40, SPECIES_SEEL}, // 30
	{25, 48, SPECIES_SEEL}, // 60
	{25, 48, SPECIES_DEWGONG}, // 20
	{25, 48, SPECIES_SEEL}, // 20
	{45, 55, SPECIES_DEWGONG}, // 40
	{45, 55, SPECIES_DEWGONG}, // 40
	{45, 55, SPECIES_SEEL}, // 15
	{45, 55, SPECIES_SEEL}, // 4
	{45, 55, SPECIES_SEEL}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsOverworld_LandMonsDefault[] =
{
	{53, 56, SPECIES_ELGYEM}, // 20
	{53, 56, SPECIES_DOTTLER}, // 20
	{54, 57, SPECIES_RUNERIGUS}, // 10
	{54, 57, SPECIES_BEHEEYEM}, // 10
	{54, 58, SPECIES_HATTREM}, // 10
	{54, 57, SPECIES_HATTREM}, // 10
	{53, 56, SPECIES_ORBEETLE}, // 5
	{54, 57, SPECIES_ORBEETLE}, // 5
	{54, 57, SPECIES_GARDEVOIR}, // 4
	{54, 58, SPECIES_GARDEVOIR}, // 4
	{54, 58, SPECIES_HATTERENE}, // 1
	{54, 58, SPECIES_HATTERENE}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsOverworld_RockMonsDefault[] =
{
	{55, 60, SPECIES_BOLDORE}, // 60
	{55, 60, SPECIES_GIGALITH}, // 30
	{55, 60, SPECIES_KLINKLANG}, // 5
	{55, 60, SPECIES_KLINKLANG}, // 4
	{55, 60, SPECIES_KLINKLANG}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsCave1f_LandMonsDefault[] =
{
	{53, 56, SPECIES_NOIBAT}, // 20
	{53, 56, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_DRILBUR}, // 10
	{54, 57, SPECIES_DRILBUR}, // 10
	{54, 58, SPECIES_HAKAMO_O}, // 10
	{54, 57, SPECIES_EXCADRILL}, // 10
	{53, 56, SPECIES_KLANG}, // 5
	{54, 57, SPECIES_KLANG}, // 5
	{54, 57, SPECIES_CROBAT}, // 4
	{54, 58, SPECIES_NOIVERN}, // 4
	{54, 58, SPECIES_NOIVERN}, // 1
	{54, 58, SPECIES_CROBAT}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsCave1f_RockMonsDefault[] =
{
	{55, 60, SPECIES_BOLDORE}, // 60
	{55, 60, SPECIES_GIGALITH}, // 30
	{55, 60, SPECIES_KLINKLANG}, // 5
	{55, 60, SPECIES_KLINKLANG}, // 4
	{55, 60, SPECIES_KLINKLANG}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsCave1f_WaterMonsDefault[] =
{
	{52, 56, SPECIES_MAREANIE}, // 60
	{55, 57, SPECIES_CORSOLA_G}, // 30
	{55, 57, SPECIES_TOXAPEX}, // 5
	{57, 58, SPECIES_CORSOLA_G}, // 4
	{56, 59, SPECIES_CORSOLA_G}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsCave1f_FishingMonsDefault[] =
{
	{5, 20, SPECIES_MAGIKARP}, // 70
	{5, 20, SPECIES_MAGIKARP}, // 30
	{30, 40, SPECIES_MAGIKARP}, // 60
	{30, 40, SPECIES_BINACLE}, // 20
	{30, 40, SPECIES_BINACLE}, // 20
	{50, 60, SPECIES_BARBARACLE}, // 40
	{50, 60, SPECIES_GYARADOS}, // 40
	{50, 60, SPECIES_BINACLE}, // 15
	{50, 60, SPECIES_BINACLE}, // 4
	{50, 60, SPECIES_MAGIKARP}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsCave2f_LandMonsDefault[] =
{
	{53, 56, SPECIES_NOIBAT}, // 20
	{53, 56, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_DRILBUR}, // 10
	{54, 57, SPECIES_DRILBUR}, // 10
	{54, 58, SPECIES_HAKAMO_O}, // 10
	{54, 57, SPECIES_EXCADRILL}, // 10
	{53, 56, SPECIES_KLANG}, // 5
	{54, 57, SPECIES_KLANG}, // 5
	{54, 57, SPECIES_CROBAT}, // 4
	{54, 58, SPECIES_NOIVERN}, // 4
	{54, 58, SPECIES_NOIVERN}, // 1
	{54, 58, SPECIES_CROBAT}, // 1
};

const struct WildPokemon gDivergentDaimynFactoryInterior_LandMonsDefault[] =
{
	{51, 56, SPECIES_MACHOKE}, // 20
	{51, 56, SPECIES_MANECTRIC}, // 20
	{52, 57, SPECIES_MAGNETON}, // 10
	{52, 57, SPECIES_ELECTABUZZ}, // 10
	{52, 57, SPECIES_PORYGON2}, // 10
	{51, 56, SPECIES_TRUBBISH}, // 10
	{51, 56, SPECIES_GARBODOR}, // 5
	{51, 56, SPECIES_TRUBBISH}, // 5
	{52, 58, SPECIES_ELECTRODE}, // 4
	{52, 58, SPECIES_ELECTRODE}, // 4
	{52, 58, SPECIES_ELECTRODE}, // 1
	{52, 58, SPECIES_MAGNEZONE}, // 1
};

const struct WildPokemon gDivergentVictoryRoad1f_LandMonsDefault[] =
{
	{54, 57, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_BOLDORE}, // 20
	{55, 58, SPECIES_SCRAFTY}, // 10
	{55, 58, SPECIES_KANGASKHAN}, // 10
	{55, 59, SPECIES_HOUNDOOM}, // 10
	{55, 58, SPECIES_COALOSSAL}, // 10
	{54, 57, SPECIES_KLINKLANG}, // 5
	{55, 58, SPECIES_NOIVERN}, // 5
	{55, 58, SPECIES_CROBAT}, // 4
	{55, 59, SPECIES_MAMOSWINE}, // 4
	{55, 59, SPECIES_GARCHOMP}, // 1
	{55, 59, SPECIES_GARCHOMP}, // 1
};

const struct WildPokemon gDivergentVictoryRoad1f_WaterMonsDefault[] =
{
	{54, 59, SPECIES_MAREANIE}, // 60
	{55, 60, SPECIES_TOXAPEX}, // 30
	{55, 60, SPECIES_DHELMISE}, // 5
	{57, 60, SPECIES_TOXAPEX}, // 4
	{56, 59, SPECIES_TOXAPEX}, // 1
};

const struct WildPokemon gDivergentVictoryRoad1f_FishingMonsDefault[] =
{
	{5, 20, SPECIES_SLOWPOKE}, // 70
	{5, 20, SPECIES_SLOWPOKE}, // 30
	{25, 50, SPECIES_SLOWPOKE}, // 60
	{25, 50, SPECIES_SLOWPOKE}, // 20
	{25, 50, SPECIES_DRATINI}, // 20
	{55, 60, SPECIES_SLOWBRO}, // 40
	{55, 60, SPECIES_DRATINI}, // 40
	{55, 60, SPECIES_DRAGONAIR}, // 15
	{55, 60, SPECIES_DRATINI}, // 4
	{55, 60, SPECIES_DRAGONAIR}, // 1
};

const struct WildPokemon gDivergentVictoryRoad2f_LandMonsDefault[] =
{
	{54, 57, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_BOLDORE}, // 20
	{55, 58, SPECIES_SCRAFTY}, // 10
	{55, 58, SPECIES_KANGASKHAN}, // 10
	{55, 59, SPECIES_HOUNDOOM}, // 10
	{55, 58, SPECIES_COALOSSAL}, // 10
	{54, 57, SPECIES_KLINKLANG}, // 5
	{55, 58, SPECIES_NOIVERN}, // 5
	{55, 58, SPECIES_CROBAT}, // 4
	{55, 59, SPECIES_MAMOSWINE}, // 4
	{55, 59, SPECIES_GARCHOMP}, // 1
	{55, 59, SPECIES_GARCHOMP}, // 1
};

const struct WildPokemon gDivergentVictoryRoad3f_LandMonsDefault[] =
{
	{54, 57, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_BOLDORE}, // 20
	{55, 58, SPECIES_SCRAFTY}, // 10
	{55, 58, SPECIES_KANGASKHAN}, // 10
	{55, 59, SPECIES_HOUNDOOM}, // 10
	{55, 58, SPECIES_COALOSSAL}, // 10
	{54, 57, SPECIES_KLINKLANG}, // 5
	{55, 58, SPECIES_NOIVERN}, // 5
	{55, 58, SPECIES_CROBAT}, // 4
	{55, 59, SPECIES_MAMOSWINE}, // 4
	{55, 59, SPECIES_GARCHOMP}, // 1
	{55, 59, SPECIES_GARCHOMP}, // 1
};

const struct WildPokemon gDivergentVictoryRoadOutside_LandMonsDefault[] =
{
	{54, 57, SPECIES_MIENSHAO}, // 20
	{54, 57, SPECIES_SKARMORY}, // 20
	{55, 58, SPECIES_WEEZING_G}, // 10
	{55, 58, SPECIES_HELIOLISK}, // 10
	{55, 59, SPECIES_MORPEKO}, // 10
	{55, 58, SPECIES_PRIMEAPE}, // 10
	{54, 57, SPECIES_HELIOLISK}, // 5
	{55, 58, SPECIES_CRABOMINABLE}, // 5
	{55, 58, SPECIES_KOMMO_O}, // 4
	{55, 59, SPECIES_HATTERENE}, // 4
	{55, 59, SPECIES_KOMMO_O}, // 1
	{55, 59, SPECIES_HATTERENE}, // 1
};

const struct WildPokemon gDivergentVictoryRoadOutside_WaterMonsDefault[] =
{
	{54, 59, SPECIES_LANTURN}, // 60
	{55, 60, SPECIES_SEADRA}, // 30
	{55, 60, SPECIES_SEADRA}, // 5
	{57, 60, SPECIES_LAPRAS}, // 4
	{56, 59, SPECIES_LAPRAS}, // 1
};

const struct WildPokemon gDivergentVictoryRoadOutside_FishingMonsDefault[] =
{
	{5, 20, SPECIES_SLOWPOKE}, // 70
	{5, 20, SPECIES_SLOWPOKE}, // 30
	{25, 50, SPECIES_SLOWPOKE}, // 60
	{25, 50, SPECIES_SLOWPOKE}, // 20
	{25, 50, SPECIES_DRATINI}, // 20
	{55, 60, SPECIES_SLOWBRO}, // 40
	{55, 60, SPECIES_DRATINI}, // 40
	{55, 60, SPECIES_DRAGONAIR}, // 15
	{55, 60, SPECIES_DRATINI}, // 4
	{55, 60, SPECIES_DRAGONITE}, // 1
};

const struct WildPokemon gDivergentVictoryRoadBackRoom_LandMonsDefault[] =
{
	{54, 57, SPECIES_GOLBAT}, // 20
	{54, 57, SPECIES_BOLDORE}, // 20
	{55, 58, SPECIES_SCRAFTY}, // 10
	{55, 58, SPECIES_KANGASKHAN}, // 10
	{55, 59, SPECIES_HOUNDOOM}, // 10
	{55, 58, SPECIES_COALOSSAL}, // 10
	{54, 57, SPECIES_KLINKLANG}, // 5
	{55, 58, SPECIES_NOIVERN}, // 5
	{55, 58, SPECIES_CROBAT}, // 4
	{55, 59, SPECIES_MAMOSWINE}, // 4
	{55, 59, SPECIES_DURALUDON}, // 1
	{55, 59, SPECIES_DURALUDON}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsChamber1_LandMonsDefault[] =
{
	{53, 56, SPECIES_YAMASK_G}, // 20
	{53, 56, SPECIES_YAMASK_G}, // 20
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 58, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_MIMIKYU}, // 10
	{53, 56, SPECIES_MIMIKYU}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 4
	{54, 58, SPECIES_CARBINK}, // 4
	{54, 58, SPECIES_RUNERIGUS}, // 1
	{54, 58, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsChamber2_LandMonsDefault[] =
{
	{53, 56, SPECIES_YAMASK_G}, // 20
	{53, 56, SPECIES_YAMASK_G}, // 20
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 58, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_MIMIKYU}, // 10
	{53, 56, SPECIES_MIMIKYU}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 4
	{54, 58, SPECIES_CARBINK}, // 4
	{54, 58, SPECIES_RUNERIGUS}, // 1
	{54, 58, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsChamber3_LandMonsDefault[] =
{
	{53, 56, SPECIES_YAMASK_G}, // 20
	{53, 56, SPECIES_YAMASK_G}, // 20
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 58, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_MIMIKYU}, // 10
	{53, 56, SPECIES_MIMIKYU}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 4
	{54, 58, SPECIES_CARBINK}, // 4
	{54, 58, SPECIES_RUNERIGUS}, // 1
	{54, 58, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsChamber4_LandMonsDefault[] =
{
	{53, 56, SPECIES_YAMASK_G}, // 20
	{53, 56, SPECIES_YAMASK_G}, // 20
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 58, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_MIMIKYU}, // 10
	{53, 56, SPECIES_MIMIKYU}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 4
	{54, 58, SPECIES_CARBINK}, // 4
	{54, 58, SPECIES_RUNERIGUS}, // 1
	{54, 58, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentUteyanRuinsChamber5_LandMonsDefault[] =
{
	{53, 56, SPECIES_YAMASK_G}, // 20
	{53, 56, SPECIES_YAMASK_G}, // 20
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_WOBBUFFET}, // 10
	{54, 58, SPECIES_WOBBUFFET}, // 10
	{54, 57, SPECIES_MIMIKYU}, // 10
	{53, 56, SPECIES_MIMIKYU}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 5
	{54, 57, SPECIES_RUNERIGUS}, // 4
	{54, 58, SPECIES_CARBINK}, // 4
	{54, 58, SPECIES_RUNERIGUS}, // 1
	{54, 58, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentRubarrDesertConnectingRooms_LandMonsDefault[] =
{
	{21, 23, SPECIES_WOOBAT}, // 20
	{20, 23, SPECIES_DIGLETT_A}, // 20
	{22, 25, SPECIES_ONIX}, // 10
	{21, 23, SPECIES_WOOBAT}, // 10
	{20, 24, SPECIES_ONIX}, // 10
	{21, 25, SPECIES_DIGLETT_A}, // 10
	{22, 25, SPECIES_DIGLETT_A}, // 5
	{19, 23, SPECIES_ONIX}, // 5
	{22, 24, SPECIES_SWOOBAT}, // 4
	{20, 24, SPECIES_ONIX}, // 4
	{22, 25, SPECIES_SWOOBAT}, // 1
	{23, 26, SPECIES_DIGLETT_A}, // 1
};

const struct WildPokemon gDivergentRubarrDesertConnectingRooms_RockMonsDefault[] =
{
	{25, 35, SPECIES_GEODUDE_A}, // 60
	{23, 35, SPECIES_NOSEPASS}, // 30
	{27, 37, SPECIES_DWEBBLE}, // 5
	{30, 37, SPECIES_GRAVELER_A}, // 4
	{33, 38, SPECIES_GRAVELER_A}, // 1
};

const struct WildPokemon gDivergentRubarrDesertB1f_LandMonsDefault[] =
{
	{49, 54, SPECIES_WOOBAT}, // 20
	{49, 54, SPECIES_SANDACONDA}, // 20
	{50, 55, SPECIES_ONIX}, // 10
	{50, 55, SPECIES_WOOBAT}, // 10
	{50, 55, SPECIES_BALTOY}, // 10
	{49, 54, SPECIES_BALTOY}, // 10
	{49, 54, SPECIES_SANDACONDA}, // 5
	{49, 54, SPECIES_CRUSTLE}, // 5
	{50, 56, SPECIES_CRUSTLE}, // 4
	{50, 56, SPECIES_SANDACONDA}, // 4
	{50, 56, SPECIES_CRUSTLE}, // 1
	{50, 56, SPECIES_CRUSTLE}, // 1
};

const struct WildPokemon gDivergentRubarrDesertB1f_RockMonsDefault[] =
{
	{50, 55, SPECIES_GRAVELER_A}, // 60
	{50, 55, SPECIES_NOSEPASS}, // 30
	{50, 55, SPECIES_CRUSTLE}, // 5
	{50, 55, SPECIES_GOLEM_A}, // 4
	{50, 55, SPECIES_GOLEM_A}, // 1
};

const struct WildPokemon gDivergentRoute18Cave_LandMonsDefault[] =
{
	{40, 47, SPECIES_TYRUNT}, // 20
	{40, 47, SPECIES_SHIELDON}, // 20
	{40, 47, SPECIES_LILEEP}, // 10
	{40, 47, SPECIES_LILEEP}, // 10
	{40, 47, SPECIES_AMAURA}, // 10
	{40, 47, SPECIES_AMAURA}, // 10
	{40, 47, SPECIES_YAMASK_G}, // 5
	{40, 47, SPECIES_YAMASK_G}, // 5
	{40, 47, SPECIES_YAMASK_G}, // 4
	{40, 47, SPECIES_YAMASK_G}, // 4
	{40, 47, SPECIES_YAMASK_G}, // 1
	{40, 47, SPECIES_YAMASK_G}, // 1
};

const struct WildPokemon gDivergentRoute18Cave_RockMonsDefault[] =
{
	{35, 48, SPECIES_ROLYCOLY}, // 60
	{35, 48, SPECIES_CARKOL}, // 30
	{35, 48, SPECIES_CARBINK}, // 5
	{35, 48, SPECIES_CARBINK}, // 4
	{35, 48, SPECIES_CARBINK}, // 1
};

const struct WildPokemon gDivergentRoute13Cave1f_LandMonsDefault[] =
{
	{43, 46, SPECIES_SMOOCHUM}, // 20
	{42, 45, SPECIES_SWOOBAT}, // 20
	{43, 46, SPECIES_SPHEAL}, // 10
	{44, 46, SPECIES_SPHEAL}, // 10
	{43, 46, SPECIES_SEALEO}, // 10
	{42, 45, SPECIES_WOOBAT}, // 10
	{43, 46, SPECIES_DIGLETT_A}, // 5
	{42, 45, SPECIES_DIGLETT_A}, // 5
	{42, 45, SPECIES_WOOBAT}, // 4
	{43, 46, SPECIES_SWOOBAT}, // 4
	{44, 46, SPECIES_SWOOBAT}, // 1
	{44, 46, SPECIES_DUGTRIO_A}, // 1
};

const struct WildPokemon gDivergentRoute13Cave1f_WaterMonsDefault[] =
{
	{44, 48, SPECIES_SEEL}, // 60
	{45, 49, SPECIES_SPHEAL}, // 30
	{44, 48, SPECIES_SEALEO}, // 5
	{45, 48, SPECIES_SEALEO}, // 4
	{44, 48, SPECIES_SEALEO}, // 1
};

const struct WildPokemon gDivergentRoute13Cave1f_FishingMonsDefault[] =
{
	{5, 40, SPECIES_SEEL}, // 70
	{5, 40, SPECIES_SEEL}, // 30
	{25, 48, SPECIES_SEEL}, // 60
	{25, 48, SPECIES_SPHEAL}, // 20
	{25, 48, SPECIES_SPHEAL}, // 20
	{45, 55, SPECIES_SEALEO}, // 40
	{45, 55, SPECIES_SEALEO}, // 40
	{45, 55, SPECIES_SEALEO}, // 15
	{45, 55, SPECIES_DEWGONG}, // 4
	{45, 55, SPECIES_DEWGONG}, // 1
};

const struct WildPokemon gDivergentRoute13CaveB1f_LandMonsDefault[] =
{
	{43, 46, SPECIES_SPHEAL}, // 20
	{42, 45, SPECIES_JYNX}, // 20
	{43, 46, SPECIES_SMOOCHUM}, // 10
	{44, 46, SPECIES_SEALEO}, // 10
	{43, 46, SPECIES_JYNX}, // 10
	{42, 45, SPECIES_JYNX}, // 10
	{43, 46, SPECIES_CRYOGONAL}, // 5
	{42, 45, SPECIES_VANILLISH}, // 5
	{42, 45, SPECIES_VANILLISH}, // 4
	{43, 46, SPECIES_VANILLISH}, // 4
	{44, 46, SPECIES_VANILLUXE}, // 1
	{44, 46, SPECIES_VANILLUXE}, // 1
};

const struct WildPokemon gDivergentRoute13CaveB1f_RockMonsDefault[] =
{
	{40, 50, SPECIES_ARON}, // 60
	{40, 50, SPECIES_LAIRON}, // 30
	{40, 50, SPECIES_LAIRON}, // 5
	{40, 50, SPECIES_ARON}, // 4
	{40, 50, SPECIES_ARON}, // 1
};

const struct WildPokemon gDivergentRoute13CaveB2f_LandMonsDefault[] =
{
	{43, 46, SPECIES_CRYOGONAL}, // 20
	{42, 45, SPECIES_JYNX}, // 20
	{43, 46, SPECIES_SEALEO}, // 10
	{44, 46, SPECIES_SEALEO}, // 10
	{43, 46, SPECIES_JYNX}, // 10
	{42, 45, SPECIES_JYNX}, // 10
	{43, 46, SPECIES_CRYOGONAL}, // 5
	{42, 45, SPECIES_VANILLISH}, // 5
	{42, 45, SPECIES_VANILLISH}, // 4
	{43, 46, SPECIES_VANILLISH}, // 4
	{44, 46, SPECIES_VANILLUXE}, // 1
	{44, 46, SPECIES_VANILLUXE}, // 1
};

const struct WildPokemon gDivergentRoute13CaveB2f_RockMonsDefault[] =
{
	{40, 50, SPECIES_LAIRON}, // 60
	{40, 50, SPECIES_ONIX}, // 30
	{40, 50, SPECIES_LAIRON}, // 5
	{40, 50, SPECIES_LAIRON}, // 4
	{40, 50, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRhodanziCity_WaterMonsDefault[] =
{
	{5, 15, SPECIES_BARBOACH}, // 60
	{5, 20, SPECIES_BARBOACH}, // 30
	{20, 35, SPECIES_WHISCASH}, // 5
	{10, 30, SPECIES_BARBOACH}, // 4
	{10, 30, SPECIES_BARBOACH}, // 1
};

const struct WildPokemon gDivergentRhodanziCity_FishingMonsDefault[] =
{
	{3, 7, SPECIES_KRABBY}, // 70
	{4, 8, SPECIES_BARBOACH}, // 30
	{20, 25, SPECIES_KRABBY}, // 60
	{20, 25, SPECIES_KRABBY}, // 20
	{19, 26, SPECIES_BARBOACH}, // 20
	{35, 40, SPECIES_BARBOACH}, // 40
	{33, 41, SPECIES_KINGLER}, // 40
	{35, 40, SPECIES_BARBOACH}, // 15
	{36, 42, SPECIES_BARBOACH}, // 4
	{38, 44, SPECIES_WHISCASH}, // 1
};

const struct WildPokemon gDivergentLaplazTown_FishingMonsDefault[] =
{
	{5, 10, SPECIES_BARBOACH}, // 70
	{4, 8, SPECIES_WOOPER}, // 30
	{25, 30, SPECIES_WOOPER}, // 60
	{25, 30, SPECIES_BARBOACH}, // 20
	{30, 35, SPECIES_QUAGSIRE}, // 20
	{40, 45, SPECIES_QUAGSIRE}, // 40
	{40, 45, SPECIES_CRAWDAUNT}, // 40
	{40, 45, SPECIES_CRAWDAUNT}, // 15
	{40, 45, SPECIES_CRAWDAUNT}, // 4
	{40, 45, SPECIES_QUAGSIRE}, // 1
};

const struct WildPokemon gDivergentHeleoRanchExterior_LandMonsDefault[] =
{
	{15, 18, SPECIES_CLEFAIRY}, // 20
	{15, 18, SPECIES_POLIWAG}, // 20
	{16, 19, SPECIES_STUFFUL}, // 10
	{16, 18, SPECIES_STUFFUL}, // 10
	{16, 18, SPECIES_SWABLU}, // 10
	{16, 18, SPECIES_CLEFAIRY}, // 10
	{15, 17, SPECIES_BUNNELBY}, // 5
	{13, 16, SPECIES_BUNNELBY}, // 5
	{15, 18, SPECIES_TYROGUE}, // 4
	{15, 18, SPECIES_TYROGUE}, // 4
	{16, 19, SPECIES_AUDINO}, // 1
	{15, 18, SPECIES_AUDINO}, // 1
};

const struct WildPokemon gDivergentHeleoRanchExterior_WaterMonsDefault[] =
{
	{5, 15, SPECIES_POLIWAG}, // 60
	{5, 20, SPECIES_POLIWHIRL}, // 30
	{30, 35, SPECIES_POLIWHIRL}, // 5
	{10, 30, SPECIES_POLIWHIRL}, // 4
	{10, 30, SPECIES_POLIWHIRL}, // 1
};

const struct WildPokemon gDivergentHeleoRanchExterior_FishingMonsDefault[] =
{
	{3, 7, SPECIES_TYMPOLE}, // 70
	{4, 8, SPECIES_POLIWAG}, // 30
	{20, 25, SPECIES_TYMPOLE}, // 60
	{20, 25, SPECIES_POLIWHIRL}, // 20
	{19, 26, SPECIES_POLIWHIRL}, // 20
	{35, 40, SPECIES_PALPITOAD}, // 40
	{33, 41, SPECIES_POLIWHIRL}, // 40
	{35, 40, SPECIES_PALPITOAD}, // 15
	{36, 42, SPECIES_POLIWRATH}, // 4
	{38, 44, SPECIES_POLIWRATH}, // 1
};

const struct WildPokemon gDivergentDaimynCity_LandMonsDefault[] =
{
	{25, 27, SPECIES_LUXIO}, // 20
	{24, 28, SPECIES_MACHOKE}, // 20
	{25, 28, SPECIES_MAGNEMITE}, // 10
	{24, 27, SPECIES_MILCERY}, // 10
	{25, 28, SPECIES_APPLIN}, // 10
	{25, 28, SPECIES_TRUBBISH}, // 10
	{24, 27, SPECIES_TRUBBISH}, // 5
	{25, 28, SPECIES_TRUBBISH}, // 5
	{24, 27, SPECIES_LUXIO}, // 4
	{25, 28, SPECIES_PORYGON}, // 4
	{24, 28, SPECIES_LUXIO}, // 1
	{25, 28, SPECIES_PORYGON}, // 1
};

const struct WildPokemon gDivergentDaimynCity_LandMonsEveningNight[] =
{
	{25, 27, SPECIES_LUXIO}, // 20
	{24, 28, SPECIES_MORGREM}, // 20
	{25, 28, SPECIES_MAGNEMITE}, // 10
	{24, 27, SPECIES_LAMPENT}, // 10
	{25, 28, SPECIES_APPLIN}, // 10
	{25, 28, SPECIES_TRUBBISH}, // 10
	{24, 27, SPECIES_TRUBBISH}, // 5
	{25, 28, SPECIES_TRUBBISH}, // 5
	{24, 27, SPECIES_LUXIO}, // 4
	{25, 28, SPECIES_PORYGON}, // 4
	{24, 28, SPECIES_LUXIO}, // 1
	{25, 28, SPECIES_PORYGON}, // 1
};

const struct WildPokemon gDivergentRoute12West_LandMonsDefault[] =
{
	{39, 41, SPECIES_SPHEAL}, // 20
	{39, 41, SPECIES_DEERLING_WINTER}, // 20
	{40, 43, SPECIES_EISCUE}, // 10
	{40, 42, SPECIES_VANILLISH}, // 10
	{40, 43, SPECIES_SNOVER}, // 10
	{40, 42, SPECIES_SANDSLASH_A}, // 10
	{41, 43, SPECIES_EISCUE}, // 5
	{41, 43, SPECIES_SEALEO}, // 5
	{39, 42, SPECIES_JYNX}, // 4
	{39, 42, SPECIES_SNOVER}, // 4
	{39, 43, SPECIES_SNOVER}, // 1
	{39, 43, SPECIES_SNOVER}, // 1
};

const struct WildPokemon gDivergentRoute12West_RockMonsDefault[] =
{
	{40, 45, SPECIES_ARON}, // 60
	{40, 45, SPECIES_LAIRON}, // 30
	{40, 45, SPECIES_LAIRON}, // 5
	{40, 45, SPECIES_LAIRON}, // 4
	{40, 45, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRoute12West_WaterMonsDefault[] =
{
	{42, 47, SPECIES_SEEL}, // 60
	{42, 47, SPECIES_DEWGONG}, // 30
	{42, 47, SPECIES_SEEL}, // 5
	{42, 47, SPECIES_SEEL}, // 4
	{42, 47, SPECIES_SEEL}, // 1
};

const struct WildPokemon gDivergentRoute12West_FishingMonsDefault[] =
{
	{35, 45, SPECIES_SPHEAL}, // 70
	{35, 45, SPECIES_SEEL}, // 30
	{40, 45, SPECIES_SPHEAL}, // 60
	{40, 45, SPECIES_SEEL}, // 20
	{40, 45, SPECIES_SEEL}, // 20
	{50, 55, SPECIES_SEEL}, // 40
	{50, 55, SPECIES_DEWGONG}, // 40
	{50, 57, SPECIES_SEALEO}, // 15
	{50, 57, SPECIES_SEALEO}, // 4
	{50, 57, SPECIES_SEALEO}, // 1
};

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

const struct WildPokemon gDivergentRoute1_WaterMonsDefault[] =
{
	{43, 46, SPECIES_STARYU}, // 60
	{42, 48, SPECIES_KRABBY}, // 30
	{42, 46, SPECIES_KRABBY}, // 5
	{43, 46, SPECIES_KRABBY}, // 4
	{44, 48, SPECIES_STARYU}, // 1
};

const struct WildPokemon gDivergentRoute1_FishingMonsDefault[] =
{
	{5, 10, SPECIES_SKRELP}, // 70
	{5, 10, SPECIES_SKRELP}, // 30
	{20, 24, SPECIES_QWILFISH}, // 60
	{20, 25, SPECIES_SKRELP}, // 20
	{21, 25, SPECIES_SKRELP}, // 20
	{45, 55, SPECIES_SKRELP}, // 40
	{45, 55, SPECIES_QWILFISH}, // 40
	{45, 55, SPECIES_QWILFISH}, // 15
	{45, 55, SPECIES_DRAGALGE}, // 4
	{45, 55, SPECIES_DRAGALGE}, // 1
};

const struct WildPokemon gDivergentRoute2_LandMonsDefault[] =
{
	{3, 5, SPECIES_KRICKETOT}, // 20
	{2, 4, SPECIES_CHEWTLE}, // 20
	{3, 6, SPECIES_BOUNSWEET}, // 10
	{2, 6, SPECIES_SENTRET}, // 10
	{3, 6, SPECIES_KRICKETOT}, // 10
	{3, 5, SPECIES_PIDGEY}, // 10
	{2, 4, SPECIES_SENTRET}, // 5
	{3, 6, SPECIES_KRICKETOT}, // 5
	{2, 4, SPECIES_SOLOSIS}, // 4
	{3, 5, SPECIES_PIDGEY}, // 4
	{3, 5, SPECIES_SOLOSIS}, // 1
	{3, 5, SPECIES_PIDGEY}, // 1
};

const struct WildPokemon gDivergentRoute2_LandMonsEveningNight[] =
{
	{3, 5, SPECIES_SPINARAK}, // 20
	{2, 4, SPECIES_CHEWTLE}, // 20
	{3, 6, SPECIES_BOUNSWEET}, // 10
	{2, 6, SPECIES_SENTRET}, // 10
	{3, 6, SPECIES_SPINARAK}, // 10
	{3, 5, SPECIES_PIDGEY}, // 10
	{2, 4, SPECIES_SENTRET}, // 5
	{3, 6, SPECIES_SPINARAK}, // 5
	{2, 4, SPECIES_SOLOSIS}, // 4
	{3, 5, SPECIES_PIDGEY}, // 4
	{3, 5, SPECIES_SOLOSIS}, // 1
	{3, 5, SPECIES_PIDGEY}, // 1
};

const struct WildPokemon gDivergentRoute2_WaterMonsDefault[] =
{
	{35, 45, SPECIES_POLIWAG}, // 60
	{35, 45, SPECIES_POLIWHIRL}, // 30
	{35, 45, SPECIES_POLIWHIRL}, // 5
	{35, 45, SPECIES_POLIWRATH}, // 4
	{35, 45, SPECIES_POLIWRATH}, // 1
};

const struct WildPokemon gDivergentRoute2_FishingMonsDefault[] =
{
	{8, 10, SPECIES_POLIWAG}, // 70
	{8, 11, SPECIES_KRABBY}, // 30
	{20, 35, SPECIES_POLIWAG}, // 60
	{20, 35, SPECIES_POLIWHIRL}, // 20
	{23, 35, SPECIES_POLIWHIRL}, // 20
	{40, 45, SPECIES_POLIWHIRL}, // 40
	{40, 50, SPECIES_KRABBY}, // 40
	{40, 50, SPECIES_KRABBY}, // 15
	{40, 50, SPECIES_POLIWRATH}, // 4
	{40, 50, SPECIES_POLIWRATH}, // 1
};

const struct WildPokemon gDivergentRoute3_LandMonsDefault[] =
{
	{7, 9, SPECIES_FOMANTIS}, // 20
	{6, 8, SPECIES_BLITZLE}, // 20
	{7, 9, SPECIES_PIDGEY}, // 10
	{6, 9, SPECIES_MILCERY}, // 10
	{7, 8, SPECIES_FOMANTIS}, // 10
	{6, 8, SPECIES_MILCERY}, // 10
	{6, 8, SPECIES_ABRA}, // 5
	{7, 10, SPECIES_MILCERY}, // 5
	{7, 9, SPECIES_PIDGEY}, // 4
	{6, 9, SPECIES_FOMANTIS}, // 4
	{7, 10, SPECIES_PIDGEY}, // 1
	{5, 8, SPECIES_FOMANTIS}, // 1
};

const struct WildPokemon gDivergentRoute3_RockMonsDefault[] =
{
	{10, 15, SPECIES_GEODUDE_A}, // 60
	{10, 15, SPECIES_DWEBBLE}, // 30
	{10, 15, SPECIES_ANORITH}, // 5
	{10, 15, SPECIES_ANORITH}, // 4
	{10, 15, SPECIES_ANORITH}, // 1
};

const struct WildPokemon gDivergentRoute4_LandMonsDefault[] =
{
	{9, 10, SPECIES_MACHOP}, // 20
	{8, 11, SPECIES_SNUBBULL}, // 20
	{9, 12, SPECIES_MEOWTH_G}, // 10
	{10, 12, SPECIES_NATU}, // 10
	{10, 11, SPECIES_MACHOP}, // 10
	{11, 13, SPECIES_NATU}, // 10
	{9, 12, SPECIES_NATU}, // 5
	{11, 13, SPECIES_KRICKETUNE}, // 5
	{10, 12, SPECIES_KRICKETUNE}, // 4
	{11, 11, SPECIES_KRICKETUNE}, // 1
	{9, 11, SPECIES_SNUBBULL}, // 4
	{10, 12, SPECIES_SNUBBULL}, // 1
};

const struct WildPokemon gDivergentRoute4_RockMonsDefault[] =
{
	{10, 15, SPECIES_GEODUDE_A}, // 60
	{10, 15, SPECIES_ARON}, // 30
	{10, 15, SPECIES_GEODUDE_A}, // 5
	{10, 15, SPECIES_ARON}, // 4
	{10, 15, SPECIES_ARON}, // 1
};

const struct WildPokemon gDivergentRoute5_LandMonsDefault[] =
{
	{12, 15, SPECIES_STARAVIA}, // 20
	{11, 14, SPECIES_ELECTRIKE}, // 20
	{12, 14, SPECIES_PETILIL}, // 10
	{10, 13, SPECIES_STEENEE}, // 10
	{12, 15, SPECIES_APPLIN}, // 10
	{11, 14, SPECIES_TOGEDEMARU}, // 10
	{10, 14, SPECIES_PETILIL}, // 5
	{11, 15, SPECIES_TOGEDEMARU}, // 5
	{11, 15, SPECIES_SWABLU}, // 4
	{12, 14, SPECIES_SWABLU}, // 4
	{10, 14, SPECIES_SWABLU}, // 1
	{11, 15, SPECIES_SWABLU}, // 1
};

const struct WildPokemon gDivergentRoute6_LandMonsDefault[] =
{
	{14, 19, SPECIES_MARILL}, // 20
	{15, 18, SPECIES_PIDGEOTTO}, // 20
	{15, 19, SPECIES_CRAMORANT}, // 10
	{17, 18, SPECIES_ELEKID}, // 10
	{15, 18, SPECIES_PANPOUR}, // 10
	{16, 19, SPECIES_ELEKID}, // 10
	{16, 19, SPECIES_DITTO}, // 5
	{16, 20, SPECIES_DREDNAW}, // 5
	{15, 18, SPECIES_CHEWTLE}, // 4
	{16, 19, SPECIES_CHEWTLE}, // 4
	{15, 18, SPECIES_CRAMORANT_GULPING}, // 1
	{18, 20, SPECIES_CHEWTLE}, // 1
};

const struct WildPokemon gDivergentRoute6_RockMonsDefault[] =
{
	{15, 25, SPECIES_ANORITH}, // 60
	{20, 25, SPECIES_GEODUDE_A}, // 30
	{25, 26, SPECIES_ANORITH}, // 5
	{25, 26, SPECIES_ANORITH}, // 4
	{25, 27, SPECIES_ANORITH}, // 1
};

const struct WildPokemon gDivergentRoute6_WaterMonsDefault[] =
{
	{25, 35, SPECIES_WOOPER}, // 60
	{27, 36, SPECIES_QUAGSIRE}, // 30
	{25, 33, SPECIES_WOOPER}, // 5
	{28, 32, SPECIES_WOOPER}, // 4
	{27, 36, SPECIES_WOOPER}, // 1
};

const struct WildPokemon gDivergentRoute6_FishingMonsDefault[] =
{
	{5, 20, SPECIES_KRABBY}, // 70
	{5, 20, SPECIES_STARYU}, // 30
	{20, 25, SPECIES_KRABBY}, // 60
	{20, 26, SPECIES_STARYU}, // 20
	{23, 25, SPECIES_STARYU}, // 20
	{30, 36, SPECIES_STARYU}, // 40
	{33, 35, SPECIES_KRABBY}, // 40
	{32, 37, SPECIES_KINGLER}, // 15
	{30, 36, SPECIES_STARMIE}, // 4
	{32, 36, SPECIES_STARMIE}, // 1
};

const struct WildPokemon gDivergentRoute7_LandMonsDefault[] =
{
	{6, 9, SPECIES_BUNNELBY}, // 20
	{6, 8, SPECIES_MEDITITE}, // 20
	{6, 9, SPECIES_BUNNELBY}, // 10
	{6, 8, SPECIES_BUNNELBY}, // 10
	{7, 9, SPECIES_MAKUHITA}, // 10
	{6, 9, SPECIES_MEDITITE}, // 10
	{7, 9, SPECIES_MEDITITE}, // 5
	{7, 9, SPECIES_STUNKY}, // 5
	{6, 8, SPECIES_STUNKY}, // 4
	{6, 8, SPECIES_MAKUHITA}, // 4
	{7, 9, SPECIES_STUNKY}, // 1
	{7, 9, SPECIES_MAKUHITA}, // 1
};

const struct WildPokemon gDivergentRoute7_LandMonsEveningNight[] =
{
	{6, 9, SPECIES_BUNNELBY}, // 20
	{6, 8, SPECIES_MEDITITE}, // 20
	{6, 9, SPECIES_BUNNELBY}, // 10
	{6, 8, SPECIES_BUNNELBY}, // 10
	{7, 9, SPECIES_MAKUHITA}, // 10
	{6, 9, SPECIES_MEDITITE}, // 10
	{7, 9, SPECIES_MEDITITE}, // 5
	{7, 9, SPECIES_DRIFLOON}, // 5
	{6, 8, SPECIES_DRIFLOON}, // 4
	{6, 8, SPECIES_MAKUHITA}, // 4
	{7, 9, SPECIES_DRIFLOON}, // 1
	{7, 9, SPECIES_MAKUHITA}, // 1
};

const struct WildPokemon gDivergentRoute8_LandMonsDefault[] =
{
	{19, 23, SPECIES_LINOONE_G}, // 20
	{18, 22, SPECIES_GLOOM}, // 20
	{18, 23, SPECIES_POLIWHIRL}, // 10
	{19, 22, SPECIES_EXEGGCUTE_A}, // 10
	{19, 23, SPECIES_LINOONE_G}, // 10
	{19, 23, SPECIES_GULPIN}, // 10
	{20, 23, SPECIES_WIMPOD}, // 5
	{19, 24, SPECIES_QUAGSIRE}, // 5
	{22, 25, SPECIES_EXEGGCUTE_A}, // 4
	{22, 25, SPECIES_GLOOM}, // 4
	{20, 23, SPECIES_EXEGGCUTE_A}, // 1
	{23, 25, SPECIES_GLOOM}, // 1
};

const struct WildPokemon gDivergentRoute8_RockMonsDefault[] =
{
	{15, 25, SPECIES_DIGLETT_A}, // 60
	{19, 24, SPECIES_ANORITH}, // 30
	{19, 23, SPECIES_ANORITH}, // 5
	{25, 26, SPECIES_DUGTRIO_A}, // 4
	{25, 27, SPECIES_DUGTRIO_A}, // 1
};

const struct WildPokemon gDivergentRoute8_WaterMonsDefault[] =
{
	{43, 46, SPECIES_STARYU}, // 60
	{42, 48, SPECIES_SKRELP}, // 30
	{42, 46, SPECIES_QWILFISH}, // 5
	{43, 46, SPECIES_QWILFISH}, // 4
	{44, 48, SPECIES_QWILFISH}, // 1
};

const struct WildPokemon gDivergentRoute8_FishingMonsDefault[] =
{
	{5, 20, SPECIES_STARYU}, // 70
	{5, 20, SPECIES_KRABBY}, // 30
	{20, 24, SPECIES_STARYU}, // 60
	{20, 25, SPECIES_KRABBY}, // 20
	{21, 25, SPECIES_QWILFISH}, // 20
	{34, 37, SPECIES_QWILFISH}, // 40
	{33, 36, SPECIES_STARYU}, // 40
	{34, 38, SPECIES_STARMIE}, // 15
	{32, 37, SPECIES_KINGLER}, // 4
	{34, 38, SPECIES_KINGLER}, // 1
};

const struct WildPokemon gDivergentRoute9_LandMonsDefault[] =
{
	{25, 28, SPECIES_FURRET}, // 20
	{26, 29, SPECIES_ELECTRIKE}, // 20
	{26, 29, SPECIES_PIDGEOTTO}, // 10
	{26, 29, SPECIES_SMEARGLE}, // 10
	{25, 28, SPECIES_TANGELA}, // 10
	{25, 28, SPECIES_TANGELA}, // 10
	{25, 28, SPECIES_FURRET}, // 5
	{25, 28, SPECIES_MUNCHLAX}, // 5
	{26, 29, SPECIES_FURRET}, // 4
	{25, 28, SPECIES_SMEARGLE}, // 4
	{25, 28, SPECIES_FURRET}, // 1
	{26, 29, SPECIES_SMEARGLE}, // 1
};

const struct WildPokemon gDivergentRoute10_LandMonsDefault[] =
{
	{25, 28, SPECIES_SKIPLOOM}, // 20
	{26, 29, SPECIES_KADABRA}, // 20
	{26, 29, SPECIES_FURRET}, // 10
	{26, 29, SPECIES_FURRET}, // 10
	{25, 28, SPECIES_SPRITZEE}, // 10
	{25, 28, SPECIES_PONYTA}, // 10
	{25, 28, SPECIES_PONYTA}, // 5
	{25, 28, SPECIES_GROWLITHE}, // 5
	{26, 29, SPECIES_GROWLITHE}, // 4
	{25, 28, SPECIES_GROWLITHE}, // 4
	{25, 28, SPECIES_GROWLITHE}, // 1
	{26, 29, SPECIES_GROWLITHE}, // 1
};

const struct WildPokemon gDivergentRoute10_WaterMonsDefault[] =
{
	{36, 43, SPECIES_MARILL}, // 60
	{35, 40, SPECIES_KRABBY}, // 30
	{34, 43, SPECIES_AZUMARILL}, // 5
	{38, 43, SPECIES_KINGLER}, // 4
	{39, 40, SPECIES_KINGLER}, // 1
};

const struct WildPokemon gDivergentRoute10_FishingMonsDefault[] =
{
	{5, 20, SPECIES_AZURILL}, // 70
	{5, 20, SPECIES_MARILL}, // 30
	{20, 25, SPECIES_AZURILL}, // 60
	{20, 25, SPECIES_MARILL}, // 20
	{20, 25, SPECIES_KRABBY}, // 20
	{30, 40, SPECIES_AZUMARILL}, // 40
	{30, 40, SPECIES_KINGLER}, // 40
	{30, 40, SPECIES_MARILL}, // 15
	{30, 40, SPECIES_MARILL}, // 4
	{30, 40, SPECIES_MARILL}, // 1
};

const struct WildPokemon gDivergentRoute11South_LandMonsDefault[] =
{
	{27, 30, SPECIES_CUBONE_A}, // 20
	{26, 29, SPECIES_SKORUPI}, // 20
	{27, 30, SPECIES_PHANPY}, // 10
	{28, 31, SPECIES_GLIGAR}, // 10
	{27, 30, SPECIES_RHYHORN}, // 10
	{28, 31, SPECIES_RHYHORN}, // 10
	{28, 31, SPECIES_PHANPY}, // 5
	{27, 30, SPECIES_HARIYAMA}, // 5
	{28, 31, SPECIES_TYROGUE}, // 4
	{27, 30, SPECIES_TYROGUE}, // 4
	{28, 31, SPECIES_TYROGUE}, // 1
	{27, 30, SPECIES_TYROGUE}, // 1
};

const struct WildPokemon gDivergentRoute11South_RockMonsDefault[] =
{
	{25, 35, SPECIES_ARON}, // 60
	{25, 30, SPECIES_LAIRON}, // 30
	{25, 30, SPECIES_GRAVELER_A}, // 5
	{25, 30, SPECIES_GRAVELER_A}, // 4
	{25, 30, SPECIES_GRAVELER_A}, // 1
};

const struct WildPokemon gDivergentRoute12East_LandMonsDefault[] =
{
	{36, 39, SPECIES_BEWEAR}, // 20
	{35, 38, SPECIES_PANCHAM}, // 20
	{35, 39, SPECIES_DEDENNE}, // 10
	{36, 37, SPECIES_DURANT}, // 10
	{36, 38, SPECIES_DURANT}, // 10
	{36, 39, SPECIES_ELECTRIKE}, // 10
	{35, 38, SPECIES_GLOOM}, // 5
	{36, 39, SPECIES_GLOOM}, // 5
	{35, 37, SPECIES_GLOOM}, // 4
	{36, 38, SPECIES_ABSOL}, // 4
	{35, 38, SPECIES_GLOOM}, // 1
	{36, 39, SPECIES_ABSOL}, // 1
};

const struct WildPokemon gDivergentRoute12East_LandMonsEveningNight[] =
{
	{36, 39, SPECIES_MURKROW}, // 20
	{35, 38, SPECIES_PANCHAM}, // 20
	{35, 39, SPECIES_MURKROW}, // 10
	{36, 37, SPECIES_DURANT}, // 10
	{36, 38, SPECIES_DURANT}, // 10
	{36, 39, SPECIES_ABSOL}, // 10
	{35, 38, SPECIES_HAUNTER}, // 5
	{36, 39, SPECIES_HAUNTER}, // 5
	{35, 37, SPECIES_HAUNTER}, // 4
	{36, 38, SPECIES_ABSOL}, // 4
	{35, 38, SPECIES_HAUNTER}, // 1
	{36, 39, SPECIES_ABSOL}, // 1
};

const struct WildPokemon gDivergentRoute12East_RockMonsDefault[] =
{
	{35, 40, SPECIES_NOSEPASS}, // 60
	{35, 40, SPECIES_ARON}, // 30
	{35, 40, SPECIES_NOSEPASS}, // 5
	{35, 40, SPECIES_LAIRON}, // 4
	{35, 40, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRoute13_LandMonsDefault[] =
{
	{10, 12, SPECIES_ORICORIO}, // 20
	{9, 13, SPECIES_DEERLING_SUMMER}, // 20
	{9, 14, SPECIES_VULPIX}, // 10
	{10, 13, SPECIES_MAGBY}, // 10
	{9, 14, SPECIES_DEERLING_SUMMER}, // 10
	{9, 13, SPECIES_PANSEAR}, // 10
	{10, 14, SPECIES_MAGBY}, // 5
	{10, 13, SPECIES_PONYTA}, // 5
	{15, 15, SPECIES_PONYTA}, // 4
	{13, 15, SPECIES_PONYTA}, // 4
	{13, 15, SPECIES_BAGON}, // 1
	{13, 16, SPECIES_BAGON}, // 1
};

const struct WildPokemon gDivergentRoute13_RockMonsDefault[] =
{
	{18, 25, SPECIES_ANORITH}, // 60
	{20, 23, SPECIES_ANORITH}, // 30
	{20, 25, SPECIES_LAIRON}, // 5
	{18, 23, SPECIES_LAIRON}, // 4
	{20, 25, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRoute13_WaterMonsDefault[] =
{
	{28, 33, SPECIES_MARILL}, // 60
	{27, 34, SPECIES_MARILL}, // 30
	{30, 35, SPECIES_MARILL}, // 5
	{33, 35, SPECIES_AZUMARILL}, // 4
	{34, 36, SPECIES_AZUMARILL}, // 1
};

const struct WildPokemon gDivergentRoute13_FishingMonsDefault[] =
{
	{10, 15, SPECIES_FEEBAS}, // 70
	{8, 15, SPECIES_MARILL}, // 30
	{20, 25, SPECIES_MARILL}, // 60
	{22, 25, SPECIES_FEEBAS}, // 20
	{18, 24, SPECIES_FEEBAS}, // 20
	{34, 40, SPECIES_AZUMARILL}, // 40
	{36, 42, SPECIES_MARILL}, // 40
	{36, 44, SPECIES_MILOTIC}, // 15
	{38, 42, SPECIES_AZUMARILL}, // 4
	{1, 70, SPECIES_FEEBAS}, // 1
};

const struct WildPokemon gDivergentRoute17_LandMonsDefault[] =
{
	{2, 3, SPECIES_AZURILL}, // 20
	{2, 4, SPECIES_HOPPIP}, // 20
	{2, 3, SPECIES_WOOPER}, // 10
	{3, 4, SPECIES_WOOPER}, // 10
	{2, 3, SPECIES_FOMANTIS}, // 10
	{2, 4, SPECIES_AZURILL}, // 10
	{2, 3, SPECIES_HOPPIP}, // 5
	{2, 3, SPECIES_AZURILL}, // 5
	{2, 4, SPECIES_AZURILL}, // 4
	{2, 4, SPECIES_FOMANTIS}, // 4
	{3, 3, SPECIES_AZURILL}, // 1
	{3, 3, SPECIES_FOMANTIS}, // 1
};

const struct WildPokemon gDivergentRoute17_WaterMonsDefault[] =
{
	{5, 15, SPECIES_DEWPIDER}, // 60
	{5, 20, SPECIES_DEWPIDER}, // 30
	{20, 35, SPECIES_POLIWAG}, // 5
	{10, 30, SPECIES_POLIWAG}, // 4
	{10, 30, SPECIES_POLIWAG}, // 1
};

const struct WildPokemon gDivergentRoute17_FishingMonsDefault[] =
{
	{3, 7, SPECIES_POLIWAG}, // 70
	{4, 8, SPECIES_DEWPIDER}, // 30
	{20, 25, SPECIES_POLIWAG}, // 60
	{20, 25, SPECIES_POLIWAG}, // 20
	{19, 26, SPECIES_POLIWAG}, // 20
	{35, 40, SPECIES_POLIWHIRL}, // 40
	{33, 41, SPECIES_POLIWHIRL}, // 40
	{35, 40, SPECIES_POLIWAG}, // 15
	{36, 42, SPECIES_POLIWAG}, // 4
	{38, 44, SPECIES_POLIWHIRL}, // 1
};

const struct WildPokemon gDivergentRoute18_LandMonsDefault[] =
{
	{43, 46, SPECIES_ROSELIA}, // 20
	{42, 45, SPECIES_SHROOMISH}, // 20
	{43, 46, SPECIES_FLOETTE_YELLOW}, // 10
	{44, 46, SPECIES_RIBOMBEE}, // 10
	{43, 46, SPECIES_COMFEY}, // 10
	{42, 45, SPECIES_MORELULL}, // 10
	{43, 46, SPECIES_BRELOOM}, // 5
	{42, 45, SPECIES_MORELULL}, // 5
	{42, 45, SPECIES_CUTIEFLY}, // 4
	{43, 46, SPECIES_FLABEBE_ORANGE}, // 4
	{44, 46, SPECIES_CUTIEFLY}, // 1
	{44, 46, SPECIES_FLABEBE_WHITE}, // 1
};

const struct WildPokemon gDivergentRoute18_WaterMonsDefault[] =
{
	{44, 48, SPECIES_FRILLISH}, // 60
	{45, 48, SPECIES_MAREANIE}, // 30
	{44, 48, SPECIES_FRILLISH}, // 5
	{45, 48, SPECIES_TOXAPEX}, // 4
	{44, 48, SPECIES_TOXAPEX}, // 1
};

const struct WildPokemon gDivergentRoute18_FishingMonsDefault[] =
{
	{5, 40, SPECIES_MAGIKARP}, // 70
	{5, 40, SPECIES_HORSEA}, // 30
	{25, 40, SPECIES_HORSEA}, // 60
	{25, 40, SPECIES_SEADRA}, // 20
	{25, 40, SPECIES_MAGIKARP}, // 20
	{45, 55, SPECIES_GYARADOS}, // 40
	{45, 55, SPECIES_SEADRA}, // 40
	{45, 55, SPECIES_MAGIKARP}, // 15
	{45, 55, SPECIES_HORSEA}, // 4
	{45, 55, SPECIES_HORSEA}, // 1
};

const struct WildPokemon gDivergentRoute19_LandMonsDefault[] =
{
	{45, 48, SPECIES_ZANGOOSE}, // 20
	{45, 48, SPECIES_EXEGGCUTE_A}, // 20
	{44, 47, SPECIES_SEVIPER}, // 10
	{44, 48, SPECIES_TROPIUS}, // 10
	{46, 48, SPECIES_SEVIPER}, // 10
	{45, 48, SPECIES_LINOONE_G}, // 10
	{46, 48, SPECIES_SEVIPER}, // 5
	{45, 47, SPECIES_ZANGOOSE}, // 5
	{44, 47, SPECIES_LINOONE_G}, // 4
	{45, 47, SPECIES_EXEGGUTOR_A}, // 4
	{44, 48, SPECIES_LINOONE_G}, // 1
	{45, 48, SPECIES_EXEGGUTOR_A}, // 1
};

const struct WildPokemon gDivergentRoute20_LandMonsDefault[] =
{
	{46, 48, SPECIES_ZEBSTRIKA}, // 20
	{45, 48, SPECIES_SWALOT}, // 20
	{46, 49, SPECIES_FLAPPLE}, // 10
	{45, 48, SPECIES_TANGELA}, // 10
	{46, 49, SPECIES_PIDGEOTTO}, // 10
	{46, 49, SPECIES_TANGELA}, // 10
	{45, 48, SPECIES_SCYTHER}, // 5
	{45, 49, SPECIES_BOUFFALANT}, // 5
	{46, 49, SPECIES_SCYTHER}, // 4
	{45, 48, SPECIES_SCYTHER}, // 4
	{45, 49, SPECIES_SCYTHER}, // 1
	{44, 48, SPECIES_SCYTHER}, // 1
};

const struct WildPokemon gDivergentRoute21_LandMonsDefault[] =
{
	{47, 50, SPECIES_FALINKS}, // 20
	{48, 51, SPECIES_PRIMEAPE}, // 20
	{47, 50, SPECIES_GOGOAT}, // 10
	{48, 51, SPECIES_GOGOAT}, // 10
	{47, 50, SPECIES_MINIOR_SHIELD}, // 10
	{48, 51, SPECIES_VIBRAVA}, // 10
	{48, 51, SPECIES_PRIMEAPE}, // 5
	{47, 50, SPECIES_FALINKS}, // 5
	{48, 51, SPECIES_VIBRAVA}, // 4
	{49, 52, SPECIES_HELIOLISK}, // 4
	{48, 51, SPECIES_VIBRAVA}, // 1
	{49, 52, SPECIES_HELIOLISK}, // 1
};

const struct WildPokemon gDivergentRoute21_RockMonsDefault[] =
{
	{50, 55, SPECIES_CARBINK}, // 60
	{50, 55, SPECIES_BOLDORE}, // 30
	{50, 55, SPECIES_GIGALITH}, // 5
	{50, 55, SPECIES_BOLDORE}, // 4
	{50, 55, SPECIES_BOLDORE}, // 1
};

const struct WildPokemon gDivergentSecretPath_LandMonsDefault[] =
{
	{47, 50, SPECIES_FALINKS}, // 20
	{48, 51, SPECIES_PRIMEAPE}, // 20
	{47, 50, SPECIES_GOGOAT}, // 10
	{48, 51, SPECIES_GOGOAT}, // 10
	{47, 50, SPECIES_MINIOR_SHIELD}, // 10
	{48, 51, SPECIES_VIBRAVA}, // 10
	{48, 51, SPECIES_PRIMEAPE}, // 5
	{47, 50, SPECIES_FALINKS}, // 5
	{48, 51, SPECIES_VIBRAVA}, // 4
	{49, 52, SPECIES_HELIOLISK}, // 4
	{48, 51, SPECIES_VIBRAVA}, // 1
	{49, 52, SPECIES_HELIOLISK}, // 1
};

const struct WildPokemon gDivergentSecretPath_RockMonsDefault[] =
{
	{50, 55, SPECIES_CARBINK}, // 60
	{50, 55, SPECIES_BOLDORE}, // 30
	{50, 55, SPECIES_GIGALITH}, // 5
	{50, 55, SPECIES_BOLDORE}, // 4
	{50, 55, SPECIES_BOLDORE}, // 1
};

const struct WildPokemon gDivergentRoute22_LandMonsDefault[] =
{
	{47, 50, SPECIES_GRANBULL}, // 20
	{47, 51, SPECIES_SWANNA}, // 20
	{47, 50, SPECIES_TROPIUS}, // 10
	{46, 51, SPECIES_PANGORO}, // 10
	{46, 51, SPECIES_AZUMARILL}, // 10
	{45, 51, SPECIES_PANGORO}, // 10
	{45, 51, SPECIES_GRANBULL}, // 5
	{46, 50, SPECIES_TROPIUS}, // 5
	{47, 51, SPECIES_PANGORO}, // 4
	{46, 50, SPECIES_SWANNA}, // 4
	{47, 52, SPECIES_PANGORO}, // 1
	{47, 52, SPECIES_SWANNA}, // 1
};

const struct WildPokemon gDivergentRoute22_WaterMonsDefault[] =
{
	{47, 50, SPECIES_MARILL}, // 60
	{48, 51, SPECIES_AZUMARILL}, // 30
	{47, 50, SPECIES_AZURILL}, // 5
	{48, 51, SPECIES_AZURILL}, // 4
	{48, 52, SPECIES_AZURILL}, // 1
};

const struct WildPokemon gDivergentRoute22_FishingMonsDefault[] =
{
	{5, 30, SPECIES_AZURILL}, // 70
	{5, 30, SPECIES_MARILL}, // 30
	{25, 40, SPECIES_AZURILL}, // 60
	{25, 40, SPECIES_MARILL}, // 20
	{25, 40, SPECIES_MARILL}, // 20
	{45, 50, SPECIES_MARILL}, // 40
	{45, 50, SPECIES_AZUMARILL}, // 40
	{45, 50, SPECIES_MARILL}, // 15
	{45, 50, SPECIES_MARILL}, // 4
	{45, 50, SPECIES_MARILL}, // 1
};

const struct WildPokemon gDivergentRoute23_LandMonsDefault[] =
{
	{47, 51, SPECIES_MEOWTH_G}, // 20
	{47, 52, SPECIES_STEENEE}, // 20
	{48, 51, SPECIES_LURANTIS}, // 10
	{47, 52, SPECIES_MEOWTH_G}, // 10
	{47, 52, SPECIES_EXEGGCUTE_A}, // 10
	{46, 52, SPECIES_EXEGGCUTE_A}, // 10
	{46, 52, SPECIES_LURANTIS}, // 5
	{47, 51, SPECIES_TROPIUS}, // 5
	{48, 52, SPECIES_BELLOSSOM}, // 4
	{47, 51, SPECIES_EXEGGUTOR_A}, // 4
	{48, 53, SPECIES_BELLOSSOM}, // 1
	{48, 53, SPECIES_EXEGGUTOR_A}, // 1
};

const struct WildPokemon gDivergentRoute24_LandMonsDefault[] =
{
	{53, 56, SPECIES_XATU}, // 20
	{53, 56, SPECIES_MEDICHAM}, // 20
	{54, 57, SPECIES_MUNNA}, // 10
	{54, 57, SPECIES_GOLURK}, // 10
	{54, 58, SPECIES_ZWEILOUS}, // 10
	{54, 57, SPECIES_DONPHAN}, // 10
	{53, 56, SPECIES_DONPHAN}, // 5
	{54, 57, SPECIES_MUNNA}, // 5
	{54, 57, SPECIES_XATU}, // 4
	{54, 58, SPECIES_DONPHAN}, // 4
	{54, 58, SPECIES_XATU}, // 1
	{54, 58, SPECIES_DONPHAN}, // 1
};

const struct WildPokemon gDivergentRoute24_LandMonsEveningNight[] =
{
	{53, 56, SPECIES_DRIFBLIM}, // 20
	{53, 56, SPECIES_MEDICHAM}, // 20
	{54, 57, SPECIES_SKUNTANK}, // 10
	{54, 57, SPECIES_GOLURK}, // 10
	{54, 58, SPECIES_ZWEILOUS}, // 10
	{54, 57, SPECIES_DONPHAN}, // 10
	{53, 56, SPECIES_DONPHAN}, // 5
	{54, 57, SPECIES_SKUNTANK}, // 5
	{54, 57, SPECIES_DRIFBLIM}, // 4
	{54, 58, SPECIES_DONPHAN}, // 4
	{54, 58, SPECIES_DRIFBLIM}, // 1
	{54, 58, SPECIES_DONPHAN}, // 1
};

const struct WildPokemon gDivergentRoute24_RockMonsDefault[] =
{
	{55, 60, SPECIES_GRAVELER_A}, // 60
	{55, 60, SPECIES_GOLEM_A}, // 30
	{55, 60, SPECIES_LAIRON}, // 5
	{55, 60, SPECIES_LAIRON}, // 4
	{55, 60, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRoute24_WaterMonsDefault[] =
{
	{52, 56, SPECIES_DEWPIDER}, // 60
	{55, 57, SPECIES_DEWPIDER}, // 30
	{55, 57, SPECIES_ARAQUANID}, // 5
	{57, 58, SPECIES_ARAQUANID}, // 4
	{56, 59, SPECIES_ARAQUANID}, // 1
};

const struct WildPokemon gDivergentRoute24_FishingMonsDefault[] =
{
	{5, 20, SPECIES_TYMPOLE}, // 70
	{5, 20, SPECIES_BARBOACH}, // 30
	{30, 40, SPECIES_PALPITOAD}, // 60
	{30, 40, SPECIES_WHISCASH}, // 20
	{30, 40, SPECIES_WHISCASH}, // 20
	{50, 60, SPECIES_PALPITOAD}, // 40
	{50, 60, SPECIES_WHISCASH}, // 40
	{50, 60, SPECIES_SEISMITOAD}, // 15
	{50, 60, SPECIES_SEISMITOAD}, // 4
	{50, 60, SPECIES_SEISMITOAD}, // 1
};

const struct WildPokemon gDivergentOceanGeneric_LandMonsDefault[] =
{
	{43, 46, SPECIES_CLOBBOPUS}, // 20
	{42, 45, SPECIES_SEVIPER}, // 20
	{43, 46, SPECIES_POLIWHIRL}, // 10
	{44, 46, SPECIES_JUMPLUFF}, // 10
	{43, 46, SPECIES_ZANGOOSE}, // 10
	{42, 45, SPECIES_BUTTERFREE}, // 10
	{43, 46, SPECIES_BUTTERFREE}, // 5
	{42, 45, SPECIES_EXEGGUTOR_A}, // 5
	{42, 45, SPECIES_EXEGGCUTE_A}, // 4
	{43, 46, SPECIES_EXEGGCUTE_A}, // 4
	{44, 46, SPECIES_EXEGGCUTE_A}, // 1
	{44, 46, SPECIES_EXEGGCUTE_A}, // 1
};

const struct WildPokemon gDivergentOceanGeneric_WaterMonsDefault[] =
{
	{44, 47, SPECIES_STARYU}, // 60
	{45, 47, SPECIES_SKRELP}, // 30
	{44, 48, SPECIES_WISHIWASHI}, // 5
	{45, 48, SPECIES_WISHIWASHI}, // 4
	{46, 49, SPECIES_STARMIE}, // 1
};

const struct WildPokemon gDivergentOceanGeneric_FishingMonsDefault[] =
{
	{5, 40, SPECIES_SKRELP}, // 70
	{5, 40, SPECIES_QWILFISH}, // 30
	{25, 40, SPECIES_SKRELP}, // 60
	{25, 40, SPECIES_SKRELP}, // 20
	{25, 40, SPECIES_QWILFISH}, // 20
	{40, 50, SPECIES_SKRELP}, // 40
	{40, 50, SPECIES_QWILFISH}, // 40
	{40, 50, SPECIES_DRAGALGE}, // 15
	{40, 50, SPECIES_DRAGALGE}, // 4
	{40, 50, SPECIES_DRAGALGE}, // 1
};

const struct WildPokemon gDivergentProfessorsConservatoryGrassArea_LandMonsDefault[] =
{
	{5, 5, SPECIES_TREECKO}, // 20
	{5, 5, SPECIES_TURTWIG}, // 20
	{5, 5, SPECIES_ROWLET}, // 10
	{5, 5, SPECIES_GROOKEY}, // 10
	{5, 5, SPECIES_BULBASAUR}, // 10
	{5, 5, SPECIES_CHIKORITA}, // 10
	{5, 5, SPECIES_ROWLET}, // 5
	{5, 5, SPECIES_GROOKEY}, // 5
	{5, 5, SPECIES_SNIVY}, // 4
	{5, 5, SPECIES_CHESPIN}, // 4
	{5, 5, SPECIES_SNIVY}, // 1
	{5, 5, SPECIES_CHESPIN}, // 1
};

const struct WildPokemon gDivergentProfessorsConservatoryFireArea_LandMonsDefault[] =
{
	{5, 5, SPECIES_CHARMANDER}, // 20
	{5, 5, SPECIES_SCORBUNNY}, // 20
	{5, 5, SPECIES_TORCHIC}, // 10
	{5, 5, SPECIES_FENNEKIN}, // 10
	{5, 5, SPECIES_CHIMCHAR}, // 10
	{5, 5, SPECIES_LITTEN}, // 10
	{5, 5, SPECIES_TORCHIC}, // 5
	{5, 5, SPECIES_FENNEKIN}, // 5
	{5, 5, SPECIES_CYNDAQUIL}, // 4
	{5, 5, SPECIES_TEPIG}, // 4
	{5, 5, SPECIES_CYNDAQUIL}, // 1
	{5, 5, SPECIES_TEPIG}, // 1
};

const struct WildPokemon gDivergentProfessorsConservatoryWaterArea_LandMonsDefault[] =
{
	{5, 5, SPECIES_PIPLUP}, // 20
	{5, 5, SPECIES_OSHAWOTT}, // 20
	{5, 5, SPECIES_SOBBLE}, // 10
	{5, 5, SPECIES_FROAKIE}, // 10
	{5, 5, SPECIES_TOTODILE}, // 10
	{5, 5, SPECIES_MUDKIP}, // 10
	{5, 5, SPECIES_SOBBLE}, // 5
	{5, 5, SPECIES_FROAKIE}, // 5
	{5, 5, SPECIES_POPPLIO}, // 4
	{5, 5, SPECIES_SQUIRTLE}, // 4
	{5, 5, SPECIES_POPPLIO}, // 1
	{5, 5, SPECIES_SQUIRTLE}, // 1
};

const struct WildPokemon gDivergentRoute11North_LandMonsDefault[] =
{
	{31, 34, SPECIES_SKIPLOOM}, // 20
	{30, 33, SPECIES_PETILIL}, // 20
	{29, 33, SPECIES_SWANNA}, // 10
	{32, 33, SPECIES_YANMA}, // 10
	{29, 33, SPECIES_GRANBULL}, // 10
	{30, 33, SPECIES_SWABLU}, // 10
	{29, 33, SPECIES_SWANNA}, // 5
	{30, 33, SPECIES_SWABLU}, // 5
	{29, 32, SPECIES_PANPOUR}, // 4
	{30, 32, SPECIES_PANPOUR}, // 4
	{30, 33, SPECIES_PANPOUR}, // 1
	{29, 32, SPECIES_PANPOUR}, // 1
};

const struct WildPokemon gDivergentRoute15South_LandMonsDefault[] =
{
	{44, 47, SPECIES_MANKEY}, // 20
	{43, 46, SPECIES_VIGOROTH}, // 20
	{44, 47, SPECIES_SUNFLORA}, // 10
	{45, 47, SPECIES_TRUMBEAK}, // 10
	{44, 47, SPECIES_TRUMBEAK}, // 10
	{43, 46, SPECIES_FLOETTE_BLUE}, // 10
	{44, 47, SPECIES_EMOLGA}, // 5
	{43, 46, SPECIES_EMOLGA}, // 5
	{43, 46, SPECIES_SLOWBRO}, // 4
	{44, 47, SPECIES_TOUCANNON}, // 4
	{45, 47, SPECIES_SLOWBRO}, // 1
	{45, 47, SPECIES_TOUCANNON}, // 1
};

const struct WildPokemon gDivergentRoute15South_WaterMonsDefault[] =
{
	{42, 45, SPECIES_CARVANHA}, // 60
	{43, 46, SPECIES_SEADRA}, // 30
	{42, 45, SPECIES_LAPRAS}, // 5
	{43, 46, SPECIES_SHARPEDO}, // 4
	{44, 47, SPECIES_SHARPEDO}, // 1
};

const struct WildPokemon gDivergentRoute15South_FishingMonsDefault[] =
{
	{5, 40, SPECIES_MAGIKARP}, // 70
	{5, 40, SPECIES_SHELLDER}, // 30
	{25, 40, SPECIES_MAGIKARP}, // 60
	{25, 40, SPECIES_SHELLDER}, // 20
	{25, 40, SPECIES_SHELLDER}, // 20
	{45, 55, SPECIES_SHELLDER}, // 40
	{45, 55, SPECIES_DHELMISE}, // 40
	{45, 55, SPECIES_CLOYSTER}, // 15
	{45, 55, SPECIES_GYARADOS}, // 4
	{45, 55, SPECIES_CLOYSTER}, // 1
};

const struct WildPokemon gDivergentRoute23Cave_LandMonsDefault[] =
{
	{47, 51, SPECIES_MEOWTH_G}, // 20
	{47, 52, SPECIES_GEODUDE_A}, // 20
	{48, 51, SPECIES_SWOOBAT}, // 10
	{47, 52, SPECIES_PERRSERKER}, // 10
	{47, 52, SPECIES_GRAVELER_A}, // 10
	{46, 52, SPECIES_GRAVELER_A}, // 10
	{46, 52, SPECIES_GRAVELER_A}, // 5
	{47, 51, SPECIES_SHUPPET}, // 5
	{48, 52, SPECIES_SHUPPET}, // 4
	{47, 51, SPECIES_BANETTE}, // 4
	{48, 53, SPECIES_SHUPPET}, // 1
	{48, 53, SPECIES_BANETTE}, // 1
};

const struct WildPokemon gDivergentRoute23Cave_WaterMonsDefault[] =
{
	{47, 51, SPECIES_WOOPER}, // 60
	{48, 50, SPECIES_QUAGSIRE}, // 30
	{46, 51, SPECIES_QUAGSIRE}, // 5
	{46, 51, SPECIES_WOOPER}, // 4
	{48, 52, SPECIES_SKRELP}, // 1
};

const struct WildPokemon gDivergentRoute23Cave_FishingMonsDefault[] =
{
	{5, 30, SPECIES_WOOPER}, // 70
	{5, 30, SPECIES_SKRELP}, // 30
	{25, 35, SPECIES_SKRELP}, // 60
	{25, 35, SPECIES_WOOPER}, // 20
	{25, 35, SPECIES_WOOPER}, // 20
	{45, 55, SPECIES_QUAGSIRE}, // 40
	{45, 55, SPECIES_QUAGSIRE}, // 40
	{45, 55, SPECIES_SKRELP}, // 15
	{45, 55, SPECIES_SKRELP}, // 4
	{45, 55, SPECIES_QUAGSIRE}, // 1
};

const struct WildPokemon gDivergentRoute20Cave_LandMonsDefault[] =
{
	{46, 48, SPECIES_LUXIO}, // 20
	{45, 48, SPECIES_GRAVELER_A}, // 20
	{46, 49, SPECIES_LUXIO}, // 10
	{45, 48, SPECIES_LUXRAY}, // 10
	{46, 49, SPECIES_SWOOBAT}, // 10
	{46, 49, SPECIES_SWOOBAT}, // 10
	{45, 48, SPECIES_SWOOBAT}, // 5
	{45, 49, SPECIES_DUGTRIO_A}, // 5
	{46, 49, SPECIES_DUGTRIO_A}, // 4
	{45, 48, SPECIES_DUGTRIO_A}, // 4
	{45, 49, SPECIES_DUGTRIO_A}, // 1
	{44, 48, SPECIES_DUGTRIO_A}, // 1
};

const struct WildPokemon gDivergentRoute20Cave_RockMonsDefault[] =
{
	{45, 50, SPECIES_GEODUDE_A}, // 60
	{45, 50, SPECIES_ARON}, // 30
	{45, 50, SPECIES_LAIRON}, // 5
	{45, 50, SPECIES_LAIRON}, // 4
	{45, 50, SPECIES_LAIRON}, // 1
};

const struct WildPokemon gDivergentRoute12ScaldingSpa_LandMonsDefault[] =
{
	{36, 39, SPECIES_HEATMOR}, // 20
	{35, 38, SPECIES_NUMEL}, // 20
	{35, 39, SPECIES_GROWLITHE}, // 10
	{36, 37, SPECIES_HARIYAMA}, // 10
	{36, 38, SPECIES_PANSEAR}, // 10
	{36, 39, SPECIES_VULPIX}, // 10
	{35, 38, SPECIES_VULPIX}, // 5
	{36, 39, SPECIES_NUMEL}, // 5
	{35, 37, SPECIES_NINETALES}, // 4
	{36, 38, SPECIES_NUMEL}, // 4
	{35, 38, SPECIES_PANSEAR}, // 1
	{36, 39, SPECIES_PANSEAR}, // 1
};

const struct WildPokemon gDivergentRoute12ScaldingSpa_RockMonsDefault[] =
{
	{35, 40, SPECIES_NOSEPASS}, // 60
	{35, 40, SPECIES_NOSEPASS}, // 30
	{35, 40, SPECIES_GRAVELER_A}, // 5
	{35, 40, SPECIES_GRAVELER_A}, // 4
	{35, 40, SPECIES_GRAVELER_A}, // 1
};

const struct WildPokemon gDivergentRoute12ScaldingSpa_LandMonsEveningNight[] =
{
	{36, 39, SPECIES_HEATMOR}, // 20
	{35, 38, SPECIES_NUMEL}, // 20
	{35, 39, SPECIES_GROWLITHE}, // 10
	{36, 37, SPECIES_HARIYAMA}, // 10
	{36, 38, SPECIES_MAROWAK_A}, // 10
	{36, 39, SPECIES_VULPIX}, // 10
	{35, 38, SPECIES_VULPIX}, // 5
	{36, 39, SPECIES_NUMEL}, // 5
	{35, 37, SPECIES_NINETALES}, // 4
	{36, 38, SPECIES_NUMEL}, // 4
	{35, 38, SPECIES_MAROWAK_A}, // 1
	{36, 39, SPECIES_MAROWAK_A}, // 1
};

const struct WildPokemon gDivergentRoute17Cave1f_LandMonsDefault[] =
{
	{3, 4, SPECIES_CLOBBOPUS}, // 20
	{3, 3, SPECIES_CLEFFA}, // 20
	{2, 3, SPECIES_WOOBAT}, // 10
	{3, 3, SPECIES_WOOBAT}, // 10
	{2, 4, SPECIES_CLEFFA}, // 10
	{3, 4, SPECIES_CLEFFA}, // 10
	{2, 4, SPECIES_CLOBBOPUS}, // 5
	{3, 4, SPECIES_CLOBBOPUS}, // 5
	{3, 4, SPECIES_CLOBBOPUS}, // 4
	{3, 4, SPECIES_WOOBAT}, // 4
	{2, 4, SPECIES_CLOBBOPUS}, // 1
	{2, 4, SPECIES_WOOBAT}, // 1
};

const struct WildPokemon gDivergentRoute17Cave1f_RockMonsDefault[] =
{
	{35, 45, SPECIES_DWEBBLE}, // 60
	{35, 45, SPECIES_GEODUDE_A}, // 30
	{35, 45, SPECIES_GRAVELER}, // 5
	{35, 45, SPECIES_GRAVELER}, // 4
	{35, 45, SPECIES_GRAVELER}, // 1
};

const struct WildPokemon gDivergentRoute17Cave1f_WaterMonsDefault[] =
{
	{5, 15, SPECIES_WOOPER}, // 60
	{5, 20, SPECIES_WOOPER}, // 30
	{20, 35, SPECIES_QUAGSIRE}, // 5
	{20, 30, SPECIES_QUAGSIRE}, // 4
	{10, 30, SPECIES_QUAGSIRE}, // 1
};

const struct WildPokemon gDivergentRoute17Cave1f_FishingMonsDefault[] =
{
	{8, 10, SPECIES_BARBOACH}, // 70
	{8, 11, SPECIES_BARBOACH}, // 30
	{25, 35, SPECIES_BARBOACH}, // 60
	{25, 35, SPECIES_WOOPER}, // 20
	{25, 35, SPECIES_WOOPER}, // 20
	{40, 50, SPECIES_WOOPER}, // 40
	{40, 50, SPECIES_BARBOACH}, // 40
	{40, 50, SPECIES_QUAGSIRE}, // 15
	{40, 50, SPECIES_WHISCASH}, // 4
	{40, 50, SPECIES_WHISCASH}, // 1
};

const struct WildPokemon gDivergentRoute17Cave1fBackRoom_LandMonsDefault[] =
{
	{43, 45, SPECIES_GEODUDE_A}, // 20
	{42, 45, SPECIES_WOOBAT}, // 20
	{43, 46, SPECIES_WOOBAT}, // 10
	{43, 45, SPECIES_GEODUDE_A}, // 10
	{42, 46, SPECIES_GRAVELER_A}, // 10
	{43, 45, SPECIES_SWOOBAT}, // 10
	{44, 47, SPECIES_GRAVELER_A}, // 5
	{46, 48, SPECIES_DIGLETT_A}, // 5
	{45, 47, SPECIES_DIGLETT_A}, // 4
	{45, 47, SPECIES_DIGLETT_A}, // 4
	{48, 50, SPECIES_DUGTRIO_A}, // 1
	{48, 50, SPECIES_DUGTRIO_A}, // 1
};

const struct WildPokemon gDivergentRoute17CaveB1f_LandMonsDefault[] =
{
	{43, 45, SPECIES_GEODUDE_A}, // 20
	{42, 45, SPECIES_WOOBAT}, // 20
	{43, 46, SPECIES_WOOBAT}, // 10
	{43, 45, SPECIES_GEODUDE_A}, // 10
	{42, 46, SPECIES_GRAVELER_A}, // 10
	{43, 45, SPECIES_SWOOBAT}, // 10
	{44, 47, SPECIES_GRAVELER_A}, // 5
	{46, 48, SPECIES_DIGLETT_A}, // 5
	{45, 47, SPECIES_DIGLETT_A}, // 4
	{45, 47, SPECIES_DIGLETT_A}, // 4
	{48, 50, SPECIES_DUGTRIO_A}, // 1
	{48, 50, SPECIES_DUGTRIO_A}, // 1
};

const struct WildPokemon gDivergentRoute17CaveB1f_RockMonsDefault[] =
{
	{38, 48, SPECIES_DWEBBLE}, // 60
	{38, 48, SPECIES_GRAVELER}, // 30
	{38, 48, SPECIES_CRUSTLE}, // 5
	{38, 48, SPECIES_CRUSTLE}, // 4
	{38, 48, SPECIES_CRUSTLE}, // 1
};

// Backing slots for gDivergentEmpty: a full set of SPECIES_NONE entries so "no
// encounters of this type" iterates cleanly (every slot reads as SPECIES_NONE and
// is skipped) instead of dereferencing a NULL wildPokemon pointer -- the latter made
// the DexNav read garbage and show phantom "?" icons. A plain NULL *info* pointer is
// not an option either: it would make the map fall back to the base-game encounter
// table for that type. Sized to the largest slot count (LAND_WILD_COUNT) so it is
// safe no matter which of the four encounter types points at it.
static const struct WildPokemon gDivergentNoMons[LAND_WILD_COUNT] = {0};
const struct WildPokemonInfo gDivergentEmpty = {0, gDivergentNoMons};

const struct WildPokemonInfo gDivergentVarisiForest_LandMonsDefaultInfo = {14, gDivergentVarisiForest_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesert_LandMonsDefaultInfo = {1, gDivergentRubarrDesert_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesert_WaterMonsDefaultInfo = {50, gDivergentRubarrDesert_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesert_FishingMonsDefaultInfo = {20, gDivergentRubarrDesert_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertB2f_LandMonsDefaultInfo = {5, gDivergentRubarrDesertB2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertB2f_RockMonsDefaultInfo = {50, gDivergentRubarrDesertB2f_RockMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB1f_LandMonsDefaultInfo = {3, gDivergentTormaCaveB1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB1f_RockMonsDefaultInfo = {50, gDivergentTormaCaveB1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB1f_WaterMonsDefaultInfo = {13, gDivergentTormaCaveB1f_WaterMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB1f_FishingMonsDefaultInfo = {20, gDivergentTormaCaveB1f_FishingMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB2f_LandMonsDefaultInfo = {5, gDivergentTormaCaveB2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentTormaCaveB2f_RockMonsDefaultInfo = {50, gDivergentTormaCaveB2f_RockMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManseTunnel_LandMonsDefaultInfo = {10, gDivergentForgottenManseTunnel_LandMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManseTunnel_FishingMonsDefaultInfo = {20, gDivergentForgottenManseTunnel_FishingMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManseExterior_LandMonsDefaultInfo = {21, gDivergentForgottenManseExterior_LandMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManse1f_LandMonsDefaultInfo = {7, gDivergentForgottenManse1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManse2f_LandMonsDefaultInfo = {7, gDivergentForgottenManse2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentForgottenManseBasement_LandMonsDefaultInfo = {7, gDivergentForgottenManseBasement_LandMonsDefault};
const struct WildPokemonInfo gDivergentDaimynCityFactory_LandMonsDefaultInfo = {21, gDivergentDaimynCityFactory_LandMonsDefault};
const struct WildPokemonInfo gDivergentDaimynCityFactory_RockMonsDefaultInfo = {50, gDivergentDaimynCityFactory_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute10Cave_LandMonsDefaultInfo = {5, gDivergentRoute10Cave_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute10Cave_RockMonsDefaultInfo = {50, gDivergentRoute10Cave_RockMonsDefault};
const struct WildPokemonInfo gDivergentLakeLaplaz_LandMonsDefaultInfo = {21, gDivergentLakeLaplaz_LandMonsDefault};
const struct WildPokemonInfo gDivergentLakeLaplaz_LandMonsEveningNightInfo = {21, gDivergentLakeLaplaz_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentLakeLaplaz_WaterMonsDefaultInfo = {1, gDivergentLakeLaplaz_WaterMonsDefault};
const struct WildPokemonInfo gDivergentLakeLaplaz_FishingMonsDefaultInfo = {20, gDivergentLakeLaplaz_FishingMonsDefault};
const struct WildPokemonInfo gDivergentPeradonForestCommon_LandMonsDefaultInfo = {5, gDivergentPeradonForestCommon_LandMonsDefault};
const struct WildPokemonInfo gDivergentPeradonForestCommon_LandMonsEveningNightInfo = {5, gDivergentPeradonForestCommon_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentPeradonForestCommon_WaterMonsDefaultInfo = {1, gDivergentPeradonForestCommon_WaterMonsDefault};
const struct WildPokemonInfo gDivergentPeradonForestCommon_FishingMonsDefaultInfo = {20, gDivergentPeradonForestCommon_FishingMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoExterior_LandMonsDefaultInfo = {21, gDivergentCarnelidgeVolcanoExterior_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoExterior_RockMonsDefaultInfo = {50, gDivergentCarnelidgeVolcanoExterior_RockMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF1_LandMonsDefaultInfo = {3, gDivergentCarnelidgeVolcanoF1_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF1_RockMonsDefaultInfo = {50, gDivergentCarnelidgeVolcanoF1_RockMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF1_WaterMonsDefaultInfo = {13, gDivergentCarnelidgeVolcanoF1_WaterMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoVolcanionRoom_LandMonsDefaultInfo = {3, gDivergentCarnelidgeVolcanoVolcanionRoom_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoVolcanionRoom_RockMonsDefaultInfo = {50, gDivergentCarnelidgeVolcanoVolcanionRoom_RockMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF2_LandMonsDefaultInfo = {3, gDivergentCarnelidgeVolcanoF2_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF2_WaterMonsDefaultInfo = {13, gDivergentCarnelidgeVolcanoF2_WaterMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoF3_LandMonsDefaultInfo = {3, gDivergentCarnelidgeVolcanoF3_LandMonsDefault};
const struct WildPokemonInfo gDivergentOrichelleGarden_LandMonsDefaultInfo = {52, gDivergentOrichelleGarden_LandMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveOverworld_LandMonsDefaultInfo = {5, gDivergentSeppireCoveOverworld_LandMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveOverworld_WaterMonsDefaultInfo = {2, gDivergentSeppireCoveOverworld_WaterMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveOverworld_FishingMonsDefaultInfo = {20, gDivergentSeppireCoveOverworld_FishingMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveCommon_LandMonsDefaultInfo = {5, gDivergentSeppireCoveCommon_LandMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveCommon_RockMonsDefaultInfo = {50, gDivergentSeppireCoveCommon_RockMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveCommon_WaterMonsDefaultInfo = {13, gDivergentSeppireCoveCommon_WaterMonsDefault};
const struct WildPokemonInfo gDivergentSeppireCoveCommon_FishingMonsDefaultInfo = {20, gDivergentSeppireCoveCommon_FishingMonsDefault};
const struct WildPokemonInfo gDivergentMimmettJungleCommon_LandMonsDefaultInfo = {14, gDivergentMimmettJungleCommon_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoBf1_LandMonsDefaultInfo = {3, gDivergentCarnelidgeVolcanoBf1_LandMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoBf1_RockMonsDefaultInfo = {50, gDivergentCarnelidgeVolcanoBf1_RockMonsDefault};
const struct WildPokemonInfo gDivergentCarnelidgeVolcanoBf1_WaterMonsDefaultInfo = {13, gDivergentCarnelidgeVolcanoBf1_WaterMonsDefault};
const struct WildPokemonInfo gDivergentHessonPass1f_LandMonsDefaultInfo = {3, gDivergentHessonPass1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentHessonPass1f_RockMonsDefaultInfo = {50, gDivergentHessonPass1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentHessonPass2f_LandMonsDefaultInfo = {3, gDivergentHessonPass2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentHessonPass2f_RockMonsDefaultInfo = {50, gDivergentHessonPass2f_RockMonsDefault};
const struct WildPokemonInfo gDivergentHessonPassB1f_LandMonsDefaultInfo = {3, gDivergentHessonPassB1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentHessonPassB1f_RockMonsDefaultInfo = {50, gDivergentHessonPassB1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentCalicinBay_LandMonsDefaultInfo = {21, gDivergentCalicinBay_LandMonsDefault};
const struct WildPokemonInfo gDivergentCalicinBay_WaterMonsDefaultInfo = {1, gDivergentCalicinBay_WaterMonsDefault};
const struct WildPokemonInfo gDivergentCalicinBay_FishingMonsDefaultInfo = {20, gDivergentCalicinBay_FishingMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsOverworld_LandMonsDefaultInfo = {21, gDivergentUteyanRuinsOverworld_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsOverworld_RockMonsDefaultInfo = {50, gDivergentUteyanRuinsOverworld_RockMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsCave1f_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsCave1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsCave1f_RockMonsDefaultInfo = {50, gDivergentUteyanRuinsCave1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsCave1f_WaterMonsDefaultInfo = {13, gDivergentUteyanRuinsCave1f_WaterMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsCave1f_FishingMonsDefaultInfo = {20, gDivergentUteyanRuinsCave1f_FishingMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsCave2f_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsCave2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentDaimynFactoryInterior_LandMonsDefaultInfo = {5, gDivergentDaimynFactoryInterior_LandMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoad1f_LandMonsDefaultInfo = {3, gDivergentVictoryRoad1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoad1f_WaterMonsDefaultInfo = {13, gDivergentVictoryRoad1f_WaterMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoad1f_FishingMonsDefaultInfo = {20, gDivergentVictoryRoad1f_FishingMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoad2f_LandMonsDefaultInfo = {3, gDivergentVictoryRoad2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoad3f_LandMonsDefaultInfo = {3, gDivergentVictoryRoad3f_LandMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoadOutside_LandMonsDefaultInfo = {21, gDivergentVictoryRoadOutside_LandMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoadOutside_WaterMonsDefaultInfo = {13, gDivergentVictoryRoadOutside_WaterMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoadOutside_FishingMonsDefaultInfo = {20, gDivergentVictoryRoadOutside_FishingMonsDefault};
const struct WildPokemonInfo gDivergentVictoryRoadBackRoom_LandMonsDefaultInfo = {5, gDivergentVictoryRoadBackRoom_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsChamber1_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsChamber1_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsChamber2_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsChamber2_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsChamber3_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsChamber3_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsChamber4_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsChamber4_LandMonsDefault};
const struct WildPokemonInfo gDivergentUteyanRuinsChamber5_LandMonsDefaultInfo = {7, gDivergentUteyanRuinsChamber5_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertConnectingRooms_LandMonsDefaultInfo = {5, gDivergentRubarrDesertConnectingRooms_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertConnectingRooms_RockMonsDefaultInfo = {50, gDivergentRubarrDesertConnectingRooms_RockMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertB1f_LandMonsDefaultInfo = {5, gDivergentRubarrDesertB1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRubarrDesertB1f_RockMonsDefaultInfo = {50, gDivergentRubarrDesertB1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute18Cave_LandMonsDefaultInfo = {10, gDivergentRoute18Cave_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute18Cave_RockMonsDefaultInfo = {50, gDivergentRoute18Cave_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute13Cave1f_LandMonsDefaultInfo = {3, gDivergentRoute13Cave1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute13Cave1f_WaterMonsDefaultInfo = {1, gDivergentRoute13Cave1f_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute13Cave1f_FishingMonsDefaultInfo = {20, gDivergentRoute13Cave1f_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute13CaveB1f_LandMonsDefaultInfo = {3, gDivergentRoute13CaveB1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute13CaveB1f_RockMonsDefaultInfo = {50, gDivergentRoute13CaveB1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute13CaveB2f_LandMonsDefaultInfo = {3, gDivergentRoute13CaveB2f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute13CaveB2f_RockMonsDefaultInfo = {50, gDivergentRoute13CaveB2f_RockMonsDefault};
const struct WildPokemonInfo gDivergentRhodanziCity_WaterMonsDefaultInfo = {1, gDivergentRhodanziCity_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRhodanziCity_FishingMonsDefaultInfo = {20, gDivergentRhodanziCity_FishingMonsDefault};
const struct WildPokemonInfo gDivergentLaplazTown_FishingMonsDefaultInfo = {20, gDivergentLaplazTown_FishingMonsDefault};
const struct WildPokemonInfo gDivergentHeleoRanchExterior_LandMonsDefaultInfo = {5, gDivergentHeleoRanchExterior_LandMonsDefault};
const struct WildPokemonInfo gDivergentHeleoRanchExterior_WaterMonsDefaultInfo = {13, gDivergentHeleoRanchExterior_WaterMonsDefault};
const struct WildPokemonInfo gDivergentHeleoRanchExterior_FishingMonsDefaultInfo = {20, gDivergentHeleoRanchExterior_FishingMonsDefault};
const struct WildPokemonInfo gDivergentDaimynCity_LandMonsDefaultInfo = {21, gDivergentDaimynCity_LandMonsDefault};
const struct WildPokemonInfo gDivergentDaimynCity_LandMonsEveningNightInfo = {21, gDivergentDaimynCity_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute12West_LandMonsDefaultInfo = {21, gDivergentRoute12West_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute12West_RockMonsDefaultInfo = {50, gDivergentRoute12West_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute12West_WaterMonsDefaultInfo = {13, gDivergentRoute12West_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute12West_FishingMonsDefaultInfo = {20, gDivergentRoute12West_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute1_LandMonsDefaultInfo = {21, gDivergentRoute1_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute1_WaterMonsDefaultInfo = {1, gDivergentRoute1_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute1_FishingMonsDefaultInfo = {20, gDivergentRoute1_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute2_LandMonsDefaultInfo = {21, gDivergentRoute2_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute2_LandMonsEveningNightInfo = {21, gDivergentRoute2_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute2_WaterMonsDefaultInfo = {13, gDivergentRoute2_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute2_FishingMonsDefaultInfo = {20, gDivergentRoute2_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute3_LandMonsDefaultInfo = {21, gDivergentRoute3_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute3_RockMonsDefaultInfo = {50, gDivergentRoute3_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute4_LandMonsDefaultInfo = {21, gDivergentRoute4_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute4_RockMonsDefaultInfo = {50, gDivergentRoute4_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute5_LandMonsDefaultInfo = {21, gDivergentRoute5_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute6_LandMonsDefaultInfo = {21, gDivergentRoute6_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute6_RockMonsDefaultInfo = {50, gDivergentRoute6_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute6_WaterMonsDefaultInfo = {1, gDivergentRoute6_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute6_FishingMonsDefaultInfo = {20, gDivergentRoute6_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute7_LandMonsDefaultInfo = {21, gDivergentRoute7_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute7_LandMonsEveningNightInfo = {21, gDivergentRoute7_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute8_LandMonsDefaultInfo = {21, gDivergentRoute8_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute8_RockMonsDefaultInfo = {50, gDivergentRoute8_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute8_WaterMonsDefaultInfo = {1, gDivergentRoute8_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute8_FishingMonsDefaultInfo = {20, gDivergentRoute8_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute9_LandMonsDefaultInfo = {21, gDivergentRoute9_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute10_LandMonsDefaultInfo = {21, gDivergentRoute10_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute10_WaterMonsDefaultInfo = {2, gDivergentRoute10_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute10_FishingMonsDefaultInfo = {20, gDivergentRoute10_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute11South_LandMonsDefaultInfo = {21, gDivergentRoute11South_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute11South_RockMonsDefaultInfo = {50, gDivergentRoute11South_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute12East_LandMonsDefaultInfo = {21, gDivergentRoute12East_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute12East_LandMonsEveningNightInfo = {21, gDivergentRoute12East_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute12East_RockMonsDefaultInfo = {50, gDivergentRoute12East_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute13_LandMonsDefaultInfo = {5, gDivergentRoute13_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute13_RockMonsDefaultInfo = {50, gDivergentRoute13_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute13_WaterMonsDefaultInfo = {1, gDivergentRoute13_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute13_FishingMonsDefaultInfo = {20, gDivergentRoute13_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute17_LandMonsDefaultInfo = {21, gDivergentRoute17_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute17_WaterMonsDefaultInfo = {13, gDivergentRoute17_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute17_FishingMonsDefaultInfo = {20, gDivergentRoute17_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute18_LandMonsDefaultInfo = {21, gDivergentRoute18_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute18_WaterMonsDefaultInfo = {13, gDivergentRoute18_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute18_FishingMonsDefaultInfo = {20, gDivergentRoute18_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute19_LandMonsDefaultInfo = {21, gDivergentRoute19_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute20_LandMonsDefaultInfo = {21, gDivergentRoute20_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute21_LandMonsDefaultInfo = {21, gDivergentRoute21_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute21_RockMonsDefaultInfo = {50, gDivergentRoute21_RockMonsDefault};
const struct WildPokemonInfo gDivergentSecretPath_LandMonsDefaultInfo = {21, gDivergentSecretPath_LandMonsDefault};
const struct WildPokemonInfo gDivergentSecretPath_RockMonsDefaultInfo = {50, gDivergentSecretPath_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute22_LandMonsDefaultInfo = {21, gDivergentRoute22_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute22_WaterMonsDefaultInfo = {13, gDivergentRoute22_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute22_FishingMonsDefaultInfo = {20, gDivergentRoute22_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute23_LandMonsDefaultInfo = {21, gDivergentRoute23_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute24_LandMonsDefaultInfo = {21, gDivergentRoute24_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute24_LandMonsEveningNightInfo = {21, gDivergentRoute24_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute24_RockMonsDefaultInfo = {50, gDivergentRoute24_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute24_WaterMonsDefaultInfo = {2, gDivergentRoute24_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute24_FishingMonsDefaultInfo = {20, gDivergentRoute24_FishingMonsDefault};
const struct WildPokemonInfo gDivergentOceanGeneric_LandMonsDefaultInfo = {21, gDivergentOceanGeneric_LandMonsDefault};
const struct WildPokemonInfo gDivergentOceanGeneric_WaterMonsDefaultInfo = {2, gDivergentOceanGeneric_WaterMonsDefault};
const struct WildPokemonInfo gDivergentOceanGeneric_FishingMonsDefaultInfo = {20, gDivergentOceanGeneric_FishingMonsDefault};
const struct WildPokemonInfo gDivergentProfessorsConservatoryGrassArea_LandMonsDefaultInfo = {21, gDivergentProfessorsConservatoryGrassArea_LandMonsDefault};
const struct WildPokemonInfo gDivergentProfessorsConservatoryFireArea_LandMonsDefaultInfo = {21, gDivergentProfessorsConservatoryFireArea_LandMonsDefault};
const struct WildPokemonInfo gDivergentProfessorsConservatoryWaterArea_LandMonsDefaultInfo = {21, gDivergentProfessorsConservatoryWaterArea_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute11North_LandMonsDefaultInfo = {21, gDivergentRoute11North_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute15South_LandMonsDefaultInfo = {21, gDivergentRoute15South_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute15South_WaterMonsDefaultInfo = {2, gDivergentRoute15South_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute15South_FishingMonsDefaultInfo = {20, gDivergentRoute15South_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute23Cave_LandMonsDefaultInfo = {21, gDivergentRoute23Cave_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute23Cave_WaterMonsDefaultInfo = {13, gDivergentRoute23Cave_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute23Cave_FishingMonsDefaultInfo = {20, gDivergentRoute23Cave_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute20Cave_LandMonsDefaultInfo = {7, gDivergentRoute20Cave_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute20Cave_RockMonsDefaultInfo = {50, gDivergentRoute20Cave_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute12ScaldingSpa_LandMonsDefaultInfo = {3, gDivergentRoute12ScaldingSpa_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute12ScaldingSpa_LandMonsEveningNightInfo = {3, gDivergentRoute12ScaldingSpa_LandMonsEveningNight};
const struct WildPokemonInfo gDivergentRoute12ScaldingSpa_RockMonsDefaultInfo = {150, gDivergentRoute12ScaldingSpa_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute17Cave1f_LandMonsDefaultInfo = {5, gDivergentRoute17Cave1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute17Cave1f_RockMonsDefaultInfo = {50, gDivergentRoute17Cave1f_RockMonsDefault};
const struct WildPokemonInfo gDivergentRoute17Cave1f_WaterMonsDefaultInfo = {13, gDivergentRoute17Cave1f_WaterMonsDefault};
const struct WildPokemonInfo gDivergentRoute17Cave1f_FishingMonsDefaultInfo = {20, gDivergentRoute17Cave1f_FishingMonsDefault};
const struct WildPokemonInfo gDivergentRoute17Cave1fBackRoom_LandMonsDefaultInfo = {5, gDivergentRoute17Cave1fBackRoom_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute17CaveB1f_LandMonsDefaultInfo = {5, gDivergentRoute17CaveB1f_LandMonsDefault};
const struct WildPokemonInfo gDivergentRoute17CaveB1f_RockMonsDefaultInfo = {50, gDivergentRoute17CaveB1f_RockMonsDefault};

// Evening / Night
const struct WildPokemonInfo gDivergentVarisiForest_LandMonsEveningNightInfo = {14, gDivergentVarisiForest_LandMonsEveningNight};

// Null entries fall back to the first encounter table in the divergentDefault header table, so all must be defined!
const struct WildPokemonHeader gDivergentWildMonDefaultHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_1),
		.mapNum = MAP_NUM(ROUTE_1),
		.landMonsInfo = &gDivergentRoute1_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute1_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute1_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gDivergentVarisiForest_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},

	{
		.mapGroup = MAP_GROUP(RUBARR_DESERT),
		.mapNum = MAP_NUM(RUBARR_DESERT),
		.landMonsInfo = &gDivergentRubarrDesert_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRubarrDesert_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRubarrDesert_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(RUBARR_DESERT_B2F),
		.mapNum = MAP_NUM(RUBARR_DESERT_B2F),
		.landMonsInfo = &gDivergentRubarrDesertB2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRubarrDesertB2f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(TORMA_CAVE_B1F),
		.mapNum = MAP_NUM(TORMA_CAVE_B1F),
		.landMonsInfo = &gDivergentTormaCaveB1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentTormaCaveB1f_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentTormaCaveB1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentTormaCaveB1f_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(TORMA_CAVE_B2F),
		.mapNum = MAP_NUM(TORMA_CAVE_B2F),
		.landMonsInfo = &gDivergentTormaCaveB2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentTormaCaveB2f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_TUNNEL),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_TUNNEL),
		.landMonsInfo = &gDivergentForgottenManseTunnel_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentForgottenManseTunnel_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_EXTERIOR),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_EXTERIOR),
		.landMonsInfo = &gDivergentForgottenManseExterior_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_1F),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_1F),
		.landMonsInfo = &gDivergentForgottenManse1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_2F),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_2F),
		.landMonsInfo = &gDivergentForgottenManse2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(FORGOTTEN_MANSE_BASEMENT),
		.mapNum = MAP_NUM(FORGOTTEN_MANSE_BASEMENT),
		.landMonsInfo = &gDivergentForgottenManseBasement_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(DAIMYN_CITY_FACTORY),
		.mapNum = MAP_NUM(DAIMYN_CITY_FACTORY),
		.landMonsInfo = &gDivergentDaimynCityFactory_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentDaimynCityFactory_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE10_CAVE),
		.mapNum = MAP_NUM(ROUTE10_CAVE),
		.landMonsInfo = &gDivergentRoute10Cave_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute10Cave_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(SEPPIRE_COVE_1F),
		.mapNum = MAP_NUM(SEPPIRE_COVE_1F),
		.landMonsInfo = &gDivergentSeppireCoveCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(LAKE_LAPLAZ),
		.mapNum = MAP_NUM(LAKE_LAPLAZ),
		.landMonsInfo = &gDivergentLakeLaplaz_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentLakeLaplaz_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentLakeLaplaz_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_NORTH),
		.mapNum = MAP_NUM(PERADON_FOREST_NORTH),
		.landMonsInfo = &gDivergentPeradonForestCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentPeradonForestCommon_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentPeradonForestCommon_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_SOUTH),
		.mapNum = MAP_NUM(PERADON_FOREST_SOUTH),
		.landMonsInfo = &gDivergentPeradonForestCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentPeradonForestCommon_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentPeradonForestCommon_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_EXTERIOR),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_EXTERIOR),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoExterior_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentCarnelidgeVolcanoExterior_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_F1),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_F1),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoF1_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentCarnelidgeVolcanoF1_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentCarnelidgeVolcanoF1_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_VOLCANION_ROOM),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_VOLCANION_ROOM),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoVolcanionRoom_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentCarnelidgeVolcanoVolcanionRoom_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_F2),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_F2),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoF2_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentCarnelidgeVolcanoF2_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_F3),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_F3),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoF3_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ORICHELLE_GARDEN),
		.mapNum = MAP_NUM(ORICHELLE_GARDEN),
		.landMonsInfo = &gDivergentOrichelleGarden_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(SEPPIRE_COVE_OVERWORLD),
		.mapNum = MAP_NUM(SEPPIRE_COVE_OVERWORLD),
		.landMonsInfo = &gDivergentSeppireCoveOverworld_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentSeppireCoveOverworld_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentSeppireCoveOverworld_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(SEPPIRE_COVE_B2F),
		.mapNum = MAP_NUM(SEPPIRE_COVE_B2F),
		.landMonsInfo = &gDivergentSeppireCoveCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentSeppireCoveCommon_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentSeppireCoveCommon_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentSeppireCoveCommon_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(SEPPIRE_COVE_B1F),
		.mapNum = MAP_NUM(SEPPIRE_COVE_B1F),
		.landMonsInfo = &gDivergentSeppireCoveCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentSeppireCoveCommon_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(MIMMETT_JUNGLE_CENTER),
		.mapNum = MAP_NUM(MIMMETT_JUNGLE_CENTER),
		.landMonsInfo = &gDivergentMimmettJungleCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(MIMMETT_JUNGLE_SOUTH),
		.mapNum = MAP_NUM(MIMMETT_JUNGLE_SOUTH),
		.landMonsInfo = &gDivergentMimmettJungleCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(MIMMETT_JUNGLE_EAST),
		.mapNum = MAP_NUM(MIMMETT_JUNGLE_EAST),
		.landMonsInfo = &gDivergentMimmettJungleCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(MIMMETT_JUNGLE_NORTH),
		.mapNum = MAP_NUM(MIMMETT_JUNGLE_NORTH),
		.landMonsInfo = &gDivergentMimmettJungleCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(SEPPIRE_COVE_SIDE_ROOM),
		.mapNum = MAP_NUM(SEPPIRE_COVE_SIDE_ROOM),
		.landMonsInfo = &gDivergentSeppireCoveCommon_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentSeppireCoveCommon_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentSeppireCoveCommon_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(CARNELIDGE_VOLCANO_BF1),
		.mapNum = MAP_NUM(CARNELIDGE_VOLCANO_BF1),
		.landMonsInfo = &gDivergentCarnelidgeVolcanoBf1_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentCarnelidgeVolcanoBf1_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentCarnelidgeVolcanoBf1_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(HESSON_PASS_1F),
		.mapNum = MAP_NUM(HESSON_PASS_1F),
		.landMonsInfo = &gDivergentHessonPass1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentHessonPass1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(HESSON_PASS_2F),
		.mapNum = MAP_NUM(HESSON_PASS_2F),
		.landMonsInfo = &gDivergentHessonPass2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentHessonPass2f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(HESSON_PASS_B1F),
		.mapNum = MAP_NUM(HESSON_PASS_B1F),
		.landMonsInfo = &gDivergentHessonPassB1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentHessonPassB1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(CALICIN_BAY),
		.mapNum = MAP_NUM(CALICIN_BAY),
		.landMonsInfo = &gDivergentCalicinBay_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentCalicinBay_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentCalicinBay_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_OVERWORLD),
		.mapNum = MAP_NUM(UTEYAN_RUINS_OVERWORLD),
		.landMonsInfo = &gDivergentUteyanRuinsOverworld_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentUteyanRuinsOverworld_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CAVE_1F),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CAVE_1F),
		.landMonsInfo = &gDivergentUteyanRuinsCave1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentUteyanRuinsCave1f_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentUteyanRuinsCave1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentUteyanRuinsCave1f_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CAVE_2F),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CAVE_2F),
		.landMonsInfo = &gDivergentUteyanRuinsCave2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(DAIMYN_FACTORY_INTERIOR),
		.mapNum = MAP_NUM(DAIMYN_FACTORY_INTERIOR),
		.landMonsInfo = &gDivergentDaimynFactoryInterior_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_1F),
		.mapNum = MAP_NUM(VICTORY_ROAD_1F),
		.landMonsInfo = &gDivergentVictoryRoad1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentVictoryRoad1f_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentVictoryRoad1f_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_2F),
		.mapNum = MAP_NUM(VICTORY_ROAD_2F),
		.landMonsInfo = &gDivergentVictoryRoad2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_3F),
		.mapNum = MAP_NUM(VICTORY_ROAD_3F),
		.landMonsInfo = &gDivergentVictoryRoad3f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_OUTSIDE),
		.mapNum = MAP_NUM(VICTORY_ROAD_OUTSIDE),
		.landMonsInfo = &gDivergentVictoryRoadOutside_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentVictoryRoadOutside_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentVictoryRoadOutside_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(VICTORY_ROAD_BACK_ROOM),
		.mapNum = MAP_NUM(VICTORY_ROAD_BACK_ROOM),
		.landMonsInfo = &gDivergentVictoryRoadBackRoom_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CHAMBER_1),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CHAMBER_1),
		.landMonsInfo = &gDivergentUteyanRuinsChamber1_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CHAMBER_2),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CHAMBER_2),
		.landMonsInfo = &gDivergentUteyanRuinsChamber2_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CHAMBER_3),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CHAMBER_3),
		.landMonsInfo = &gDivergentUteyanRuinsChamber3_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CHAMBER_4),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CHAMBER_4),
		.landMonsInfo = &gDivergentUteyanRuinsChamber4_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(UTEYAN_RUINS_CHAMBER_5),
		.mapNum = MAP_NUM(UTEYAN_RUINS_CHAMBER_5),
		.landMonsInfo = &gDivergentUteyanRuinsChamber5_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(RUBARR_DESERT_CONNECTING_ROOMS),
		.mapNum = MAP_NUM(RUBARR_DESERT_CONNECTING_ROOMS),
		.landMonsInfo = &gDivergentRubarrDesertConnectingRooms_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRubarrDesertConnectingRooms_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(RUBARR_DESERT_B1F),
		.mapNum = MAP_NUM(RUBARR_DESERT_B1F),
		.landMonsInfo = &gDivergentRubarrDesertB1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRubarrDesertB1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE18_CAVE),
		.mapNum = MAP_NUM(ROUTE18_CAVE),
		.landMonsInfo = &gDivergentRoute18Cave_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute18Cave_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE13_CAVE_1F),
		.mapNum = MAP_NUM(ROUTE13_CAVE_1F),
		.landMonsInfo = &gDivergentRoute13Cave1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute13Cave1f_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute13Cave1f_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE13_CAVE_B1F),
		.mapNum = MAP_NUM(ROUTE13_CAVE_B1F),
		.landMonsInfo = &gDivergentRoute13CaveB1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute13CaveB1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE13_CAVE_B2F),
		.mapNum = MAP_NUM(ROUTE13_CAVE_B2F),
		.landMonsInfo = &gDivergentRoute13CaveB2f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute13CaveB2f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(RHODANZI_CITY),
		.mapNum = MAP_NUM(RHODANZI_CITY),
		.landMonsInfo = &gDivergentEmpty,
		.waterMonsInfo = &gDivergentRhodanziCity_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRhodanziCity_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(LAPLAZ_TOWN),
		.mapNum = MAP_NUM(LAPLAZ_TOWN),
		.landMonsInfo = &gDivergentEmpty,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentLaplazTown_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(HELEO_RANCH_EXTERIOR),
		.mapNum = MAP_NUM(HELEO_RANCH_EXTERIOR),
		.landMonsInfo = &gDivergentHeleoRanchExterior_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentHeleoRanchExterior_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentHeleoRanchExterior_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(DAIMYN_CITY),
		.mapNum = MAP_NUM(DAIMYN_CITY),
		.landMonsInfo = &gDivergentDaimynCity_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_12_WEST),
		.mapNum = MAP_NUM(ROUTE_12_WEST),
		.landMonsInfo = &gDivergentRoute12West_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute12West_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute12West_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute12West_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_2),
		.mapNum = MAP_NUM(ROUTE_2),
		.landMonsInfo = &gDivergentRoute2_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute2_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute2_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_3),
		.mapNum = MAP_NUM(ROUTE_3),
		.landMonsInfo = &gDivergentRoute3_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute3_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_4),
		.mapNum = MAP_NUM(ROUTE_4),
		.landMonsInfo = &gDivergentRoute4_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute4_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_5),
		.mapNum = MAP_NUM(ROUTE_5),
		.landMonsInfo = &gDivergentRoute5_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_6),
		.mapNum = MAP_NUM(ROUTE_6),
		.landMonsInfo = &gDivergentRoute6_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute6_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute6_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute6_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_7),
		.mapNum = MAP_NUM(ROUTE_7),
		.landMonsInfo = &gDivergentRoute7_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_8),
		.mapNum = MAP_NUM(ROUTE_8),
		.landMonsInfo = &gDivergentRoute8_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute8_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute8_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute8_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_9),
		.mapNum = MAP_NUM(ROUTE_9),
		.landMonsInfo = &gDivergentRoute9_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_10),
		.mapNum = MAP_NUM(ROUTE_10),
		.landMonsInfo = &gDivergentRoute10_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute10_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute10_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_11_SOUTH),
		.mapNum = MAP_NUM(ROUTE_11_SOUTH),
		.landMonsInfo = &gDivergentRoute11South_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute11South_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_12_EAST),
		.mapNum = MAP_NUM(ROUTE_12_EAST),
		.landMonsInfo = &gDivergentRoute12East_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12East_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_13),
		.mapNum = MAP_NUM(ROUTE_13),
		.landMonsInfo = &gDivergentRoute13_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute13_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute13_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute13_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_14),
		.mapNum = MAP_NUM(ROUTE_14),
		.landMonsInfo = &gDivergentOceanGeneric_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentOceanGeneric_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentOceanGeneric_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_15_NORTH),
		.mapNum = MAP_NUM(ROUTE_15_NORTH),
		.landMonsInfo = &gDivergentOceanGeneric_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentOceanGeneric_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentOceanGeneric_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_16),
		.mapNum = MAP_NUM(ROUTE_16),
		.landMonsInfo = &gDivergentOceanGeneric_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentOceanGeneric_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentOceanGeneric_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_17),
		.mapNum = MAP_NUM(ROUTE_17),
		.landMonsInfo = &gDivergentRoute17_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute17_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute17_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_18),
		.mapNum = MAP_NUM(ROUTE_18),
		.landMonsInfo = &gDivergentRoute18_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute18_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute18_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_19),
		.mapNum = MAP_NUM(ROUTE_19),
		.landMonsInfo = &gDivergentRoute19_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentOceanGeneric_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentOceanGeneric_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_20),
		.mapNum = MAP_NUM(ROUTE_20),
		.landMonsInfo = &gDivergentRoute20_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_21),
		.mapNum = MAP_NUM(ROUTE_21),
		.landMonsInfo = &gDivergentRoute21_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute21_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(SECRET_PATH),
		.mapNum = MAP_NUM(SECRET_PATH),
		.landMonsInfo = &gDivergentSecretPath_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentSecretPath_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_22),
		.mapNum = MAP_NUM(ROUTE_22),
		.landMonsInfo = &gDivergentRoute22_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute22_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute22_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_23),
		.mapNum = MAP_NUM(ROUTE_23),
		.landMonsInfo = &gDivergentRoute23_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentOceanGeneric_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentOceanGeneric_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_24),
		.mapNum = MAP_NUM(ROUTE_24),
		.landMonsInfo = &gDivergentRoute24_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute24_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute24_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute24_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_GRASS_AREA),
		.landMonsInfo = &gDivergentProfessorsConservatoryGrassArea_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_FIRE_AREA),
		.landMonsInfo = &gDivergentProfessorsConservatoryFireArea_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(PROFESSORS_CONSERVATORY_WATER_AREA),
		.mapNum = MAP_NUM(PROFESSORS_CONSERVATORY_WATER_AREA),
		.landMonsInfo = &gDivergentProfessorsConservatoryWaterArea_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_11_NORTH),
		.mapNum = MAP_NUM(ROUTE_11_NORTH),
		.landMonsInfo = &gDivergentRoute11North_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_15_SOUTH),
		.mapNum = MAP_NUM(ROUTE_15_SOUTH),
		.landMonsInfo = &gDivergentRoute15South_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute15South_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute15South_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_23_CAVE),
		.mapNum = MAP_NUM(ROUTE_23_CAVE),
		.landMonsInfo = &gDivergentRoute23Cave_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute23Cave_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute23Cave_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_20_CAVE),
		.mapNum = MAP_NUM(ROUTE_20_CAVE),
		.landMonsInfo = &gDivergentRoute20Cave_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute20Cave_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE12_SCALDING_SPA_BACK_ROOM),
		.mapNum = MAP_NUM(ROUTE12_SCALDING_SPA_BACK_ROOM),
		.landMonsInfo = &gDivergentRoute12ScaldingSpa_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12ScaldingSpa_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE12_SCALDING_SPA_GLASTRIER_HALL),
		.mapNum = MAP_NUM(ROUTE12_SCALDING_SPA_GLASTRIER_HALL),
		.landMonsInfo = &gDivergentRoute12ScaldingSpa_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12ScaldingSpa_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE17_CAVE_1F),
		.mapNum = MAP_NUM(ROUTE17_CAVE_1F),
		.landMonsInfo = &gDivergentRoute17Cave1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentRoute17Cave1f_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute17Cave1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute17Cave1f_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE17_CAVE_1F_BACK_ROOM),
		.mapNum = MAP_NUM(ROUTE17_CAVE_1F_BACK_ROOM),
		.landMonsInfo = &gDivergentRoute17Cave1fBackRoom_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE17_CAVE_B1F),
		.mapNum = MAP_NUM(ROUTE17_CAVE_B1F),
		.landMonsInfo = &gDivergentRoute17CaveB1f_LandMonsDefaultInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute17CaveB1f_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},

	// Terminator -- required so lookups for maps with no entry return NULL
	// (otherwise GetCurrentMapWildMonHeader walks off the end of the array).
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
};

// Null entries will keep regular encounters defined in daytime table
const struct WildPokemonHeader gDivergentWildMonEveningNightHeaders[] =
{
	{
		.mapGroup = MAP_GROUP(ROUTE_2),
		.mapNum = MAP_NUM(ROUTE_2),
		.landMonsInfo = &gDivergentRoute2_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentRoute2_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentRoute2_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(VARISI_FOREST),
		.mapNum = MAP_NUM(VARISI_FOREST),
		.landMonsInfo = &gDivergentVarisiForest_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_7),
		.mapNum = MAP_NUM(ROUTE_7),
		.landMonsInfo = &gDivergentRoute7_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
		{
		.mapGroup = MAP_GROUP(DAIMYN_CITY),
		.mapNum = MAP_NUM(DAIMYN_CITY),
		.landMonsInfo = &gDivergentDaimynCity_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentEmpty,
	},
		{
		.mapGroup = MAP_GROUP(ROUTE_12_EAST),
		.mapNum = MAP_NUM(ROUTE_12_EAST),
		.landMonsInfo = &gDivergentRoute12East_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12East_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(LAKE_LAPLAZ),
		.mapNum = MAP_NUM(LAKE_LAPLAZ),
		.landMonsInfo = &gDivergentLakeLaplaz_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentLakeLaplaz_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentLakeLaplaz_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE12_SCALDING_SPA_BACK_ROOM),
		.mapNum = MAP_NUM(ROUTE12_SCALDING_SPA_BACK_ROOM),
		.landMonsInfo = &gDivergentRoute12ScaldingSpa_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12ScaldingSpa_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE12_SCALDING_SPA_GLASTRIER_HALL),
		.mapNum = MAP_NUM(ROUTE12_SCALDING_SPA_GLASTRIER_HALL),
		.landMonsInfo = &gDivergentRoute12ScaldingSpa_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentEmpty,
		.rockSmashMonsInfo = &gDivergentRoute12ScaldingSpa_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentEmpty,
	},
	{
		.mapGroup = MAP_GROUP(ROUTE_24),
		.mapNum = MAP_NUM(ROUTE_24),
		.landMonsInfo = &gDivergentRoute24_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentRoute24_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentRoute24_RockMonsDefaultInfo,
		.fishingMonsInfo = &gDivergentRoute24_FishingMonsDefaultInfo,
	},
	{
		.mapGroup = MAP_GROUP(PERADON_FOREST_NORTH),
		.mapNum = MAP_NUM(PERADON_FOREST_NORTH),
		.landMonsInfo = &gDivergentPeradonForestCommon_LandMonsEveningNightInfo,
		.waterMonsInfo = &gDivergentPeradonForestCommon_WaterMonsDefaultInfo,
		.rockSmashMonsInfo = &gDivergentEmpty,
		.fishingMonsInfo = &gDivergentPeradonForestCommon_FishingMonsDefaultInfo,
	},

	// Terminator -- required so nighttime lookups for maps with no entry
	// fall through to the default table instead of reading past the array.
	{
		.mapGroup = 0xFF,
		.mapNum = 0xFF,
		.landMonsInfo = NULL,
		.waterMonsInfo = NULL,
		.rockSmashMonsInfo = NULL,
		.fishingMonsInfo = NULL,
	},
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
