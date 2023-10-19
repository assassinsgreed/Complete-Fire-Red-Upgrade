#include "../defines_battle.h"
#include "../../include/pokedex.h"
#include "../../include/constants/species.h"
#include "../../include/constants/items.h"
/*
pokemon_tables.c
	set up tables for pokemon species including:
		-Alternate species sizes
		-Banned moves, abilities, and items for battle facilities
		-etc...

tables to edit:
	gAlternateSpeciesSizeTable
	gSkyBattleBannedSpeciesList
	gUltraBeastList
	gDeerlingForms
	gSawsbuckForms
	gVivillonForms
	gFlabebeForms
	gFloetteForms
	gFlorgesForms
	gFurfrouForms
	gPikachuCapForms
	gAlcremieForms

	gSmogonOU_AbilityBanList
	gSmogonOUDoubles_AbilityBanList
	gBattleTowerStandard_ItemBanList
	gSmogonOU_ItemBanList
	gSmogonNationalDexOU_ItemBanList
	gSmogonOUDoubles_ItemBanList
	gSmogonOUDoubles_MoveBanList
	gSmogon_MoveBanList
	gSmogonLittleCup_MoveBanList
	gSmogonLittleCup_ItemBanList
	gMiddleCup_AbilityBanList
	gMiddleCup_ItemBanList
	gSmogonMonotype_AbilityBanList
	gSmogonMonotype_ItemBanList
	gSmogonAverageMons_ItemBanList
	gSmogonAverageMons_MoveBanList
	gSmogonAverageMons_AbilityBanList
	gSmogon350Cup_ItemBanList
	gSmogon350Cup_AbilityBanList
	gSmogonScalemons_ItemBanList
	gSmogonScalemons_AbilityBanList
	gSmogonUU_ItemBanList
	gSmogonUU_AbilityBanList
	gSmogonRU_ItemBanList
	gSmogonRU_AbilityBanList
	gSmogonNU_ItemBanList
*/

#define ALTERNATE_SIZE(species, height, weight) {species, height * 10, weight * 10}

const struct AlternateSize gAlternateSpeciesSizeTable[] =
{
	ALTERNATE_SIZE(SPECIES_VENUSAUR_MEGA, 2.4, 155.5),
	ALTERNATE_SIZE(SPECIES_CHARIZARD_MEGA_Y, 1.7, 100.5),
	ALTERNATE_SIZE(SPECIES_CHARIZARD_MEGA_X, 1.7, 110.5),
	ALTERNATE_SIZE(SPECIES_BLASTOISE_MEGA, 1.6, 101.1),
	ALTERNATE_SIZE(SPECIES_BEEDRILL_MEGA, 1.4, 40.5),
	ALTERNATE_SIZE(SPECIES_PIDGEOT, 2.2, 50.5),
	ALTERNATE_SIZE(SPECIES_RATTATA_A, 0.3, 3.8),
	ALTERNATE_SIZE(SPECIES_RATICATE_A, 0.7, 25.5),
	ALTERNATE_SIZE(SPECIES_RAICHU_A, 0.7, 21.0),
	ALTERNATE_SIZE(SPECIES_SANDSHREW_A, 0.7, 40.0),
	ALTERNATE_SIZE(SPECIES_SANDSLASH_A, 1.2, 55.0),
	ALTERNATE_SIZE(SPECIES_DIGLETT_A, 0.2, 1.0),
	ALTERNATE_SIZE(SPECIES_DUGTRIO_A, 0.7, 66.6),
	ALTERNATE_SIZE(SPECIES_PERSIAN_A, 1.1, 33.0),
	ALTERNATE_SIZE(SPECIES_ALAKAZAM_MEGA, 1.2, 105.8),
	ALTERNATE_SIZE(SPECIES_GEODUDE_A, 0.4, 20.3),
	ALTERNATE_SIZE(SPECIES_GRAVELER_A, 1.0, 110.0),
	ALTERNATE_SIZE(SPECIES_GOLEM_A, 1.7, 316.0),
	ALTERNATE_SIZE(SPECIES_SLOWBRO_MEGA, 2.0, 120.0),
	ALTERNATE_SIZE(SPECIES_GRIMER_A, 0.7, 42.0),
	ALTERNATE_SIZE(SPECIES_MUK_A, 1.0, 52.0),
	ALTERNATE_SIZE(SPECIES_GENGAR_MEGA, 1.4, 40.5),
	ALTERNATE_SIZE(SPECIES_EXEGGUTOR_A, 10.9, 415.6),
	ALTERNATE_SIZE(SPECIES_MAROWAK_A, 1.0, 34.0),
	ALTERNATE_SIZE(SPECIES_KANGASKHAN_MEGA, 2.2, 100.0),
	ALTERNATE_SIZE(SPECIES_PINSIR_MEGA, 1.7, 59.0),
	ALTERNATE_SIZE(SPECIES_GYARADOS_MEGA, 6.5, 305.0),
	ALTERNATE_SIZE(SPECIES_AERODACTYL_MEGA, 2.1, 79.0),
	ALTERNATE_SIZE(SPECIES_MEWTWO_MEGA_Y, 1.5, 33.0),
	ALTERNATE_SIZE(SPECIES_MEWTWO_MEGA_X, 2.3, 127.0),
	ALTERNATE_SIZE(SPECIES_STEELIX_MEGA, 10.5, 740.0),
	ALTERNATE_SIZE(SPECIES_SCIZOR_MEGA, 2.0, 125.0),
	ALTERNATE_SIZE(SPECIES_HERACROSS_MEGA, 1.7, 62.5),
	ALTERNATE_SIZE(SPECIES_HOUNDOOM_MEGA, 1.9, 49.5),
	ALTERNATE_SIZE(SPECIES_TYRANITAR_MEGA, 2.5, 255.0),
	ALTERNATE_SIZE(SPECIES_SCEPTILE_MEGA, 1.9, 55.2),
	ALTERNATE_SIZE(SPECIES_SWAMPERT_MEGA, 1.9, 102.0),
	ALTERNATE_SIZE(SPECIES_SABLEYE_MEGA, 0.5, 161.0),
	ALTERNATE_SIZE(SPECIES_MAWILE_MEGA, 1.0, 23.5),
	ALTERNATE_SIZE(SPECIES_AGGRON_MEGA, 2.2, 395.0),
	ALTERNATE_SIZE(SPECIES_MANECTRIC_MEGA, 1.8, 44.0),
	ALTERNATE_SIZE(SPECIES_SHARPEDO_MEGA, 2.5, 130.3),
	ALTERNATE_SIZE(SPECIES_CAMERUPT_MEGA, 2.5, 320.5),
	ALTERNATE_SIZE(SPECIES_ALTARIA_MEGA, 1.5, 20.6),
	ALTERNATE_SIZE(SPECIES_BANETTE_MEGA, 1.2, 13.0),
	ALTERNATE_SIZE(SPECIES_ABSOL_MEGA, 1.2, 49.0),
	ALTERNATE_SIZE(SPECIES_GLALIE_MEGA, 2.1, 350.2),
	ALTERNATE_SIZE(SPECIES_SALAMENCE_MEGA, 1.8, 112.6),
	ALTERNATE_SIZE(SPECIES_METAGROSS_MEGA, 2.5, 942.9),
	ALTERNATE_SIZE(SPECIES_LATIAS_MEGA, 1.8, 52.0),
	ALTERNATE_SIZE(SPECIES_LATIOS_MEGA, 2.3, 70.0),
	ALTERNATE_SIZE(SPECIES_KYOGRE_PRIMAL, 9.8, 430.0),
	ALTERNATE_SIZE(SPECIES_GROUDON_PRIMAL, 5.0, 999.7),
	ALTERNATE_SIZE(SPECIES_RAYQUAZA_MEGA, 10.8, 392.0),
	ALTERNATE_SIZE(SPECIES_LOPUNNY_MEGA, 1.3, 28.3),
	ALTERNATE_SIZE(SPECIES_LUCARIO_MEGA, 1.3, 57.5),
	ALTERNATE_SIZE(SPECIES_ABOMASNOW_MEGA, 2.7, 185.0),
	ALTERNATE_SIZE(SPECIES_GALLADE_MEGA, 1.6, 56.4),
	ALTERNATE_SIZE(SPECIES_DIALGA_ORIGIN, 7.0, 850.0),
	ALTERNATE_SIZE(SPECIES_PALKIA_ORIGIN, 6.3, 660.0),
	ALTERNATE_SIZE(SPECIES_GIRATINA_ORIGIN, 6.9, 650.0),
	ALTERNATE_SIZE(SPECIES_SHAYMIN_SKY, 0.4, 5.2),
	ALTERNATE_SIZE(SPECIES_AUDINO_MEGA, 1.5, 32.0),
	ALTERNATE_SIZE(SPECIES_TORNADUS_THERIAN, 1.4, 63.0),
	ALTERNATE_SIZE(SPECIES_THUNDURUS_THERIAN, 3.0, 61.0),
	ALTERNATE_SIZE(SPECIES_LANDORUS_THERIAN, 1.3, 68.0),
	ALTERNATE_SIZE(SPECIES_KYUREM_BLACK, 3.3, 325.0),
	ALTERNATE_SIZE(SPECIES_KYUREM_WHITE, 3.6, 325.0),
	ALTERNATE_SIZE(SPECIES_PUMPKABOO_M, 0.4, 5.0),
	ALTERNATE_SIZE(SPECIES_PUMPKABOO_L, 0.5, 7.5),
	ALTERNATE_SIZE(SPECIES_PUMPKABOO_XL, 0.8, 15.0),
	ALTERNATE_SIZE(SPECIES_GOURGEIST_M, 0.9, 12.5),
	ALTERNATE_SIZE(SPECIES_GOURGEIST_L, 1.1, 14.0),
	ALTERNATE_SIZE(SPECIES_GOURGEIST_XL, 1.7, 39.0),
	ALTERNATE_SIZE(SPECIES_ZYGARDE_10, 1.2, 33.5),
	ALTERNATE_SIZE(SPECIES_ZYGARDE_COMPLETE, 4.5, 610.0),
	ALTERNATE_SIZE(SPECIES_DIANCIE_MEGA, 1.1, 27.8),
	ALTERNATE_SIZE(SPECIES_HOOPA_UNBOUND, 6.5, 490.0),
	ALTERNATE_SIZE(SPECIES_LYCANROC_N, 1.1, 25.0),
	ALTERNATE_SIZE(SPECIES_WISHIWASHI_S, 8.2, 78.6),
	ALTERNATE_SIZE(SPECIES_MINIOR_RED, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_BLUE, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_ORANGE, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_YELLOW, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_INDIGO, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_GREEN, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_MINIOR_VIOLET, 0.3, 0.3),
	ALTERNATE_SIZE(SPECIES_NECROZMA_DAWN_WINGS, 4.2, 350.0),
	ALTERNATE_SIZE(SPECIES_NECROZMA_DUSK_MANE, 3.8, 460.0),
	ALTERNATE_SIZE(SPECIES_NECROZMA_ULTRA, 7.5, 230.0),
	ALTERNATE_SIZE(SPECIES_ZACIAN_CROWNED, 2.8, 355.0),
	ALTERNATE_SIZE(SPECIES_ZAMAZENTA_CROWNED, 2.9, 785.0),
	ALTERNATE_SIZE(SPECIES_ETERNATUS_ETERNAMAX, 100.0, 999.9),
	ALTERNATE_SIZE(SPECIES_CALYREX_ICE_RIDER, 2.4, 809.1),
	ALTERNATE_SIZE(SPECIES_CALYREX_SHADOW_RIDER, 2.4, 53.6),
	ALTERNATE_SIZE(SPECIES_MEOWTH_G, 0.4, 7.5),
	ALTERNATE_SIZE(SPECIES_PONYTA_G, 0.8, 24.0),
	ALTERNATE_SIZE(SPECIES_RAPIDASH_G, 1.7, 80.0),
	ALTERNATE_SIZE(SPECIES_SLOWBRO_G, 1.6, 70.5),
	ALTERNATE_SIZE(SPECIES_FARFETCHD_G, 0.8, 42.0),
	ALTERNATE_SIZE(SPECIES_WEEZING_G, 3.0, 16.0),
	ALTERNATE_SIZE(SPECIES_MR_MIME_G, 1.4, 56.8),
	ALTERNATE_SIZE(SPECIES_ARTICUNO_G, 1.7, 50.9),
	ALTERNATE_SIZE(SPECIES_ZAPDOS_G, 1.6, 58.2),
	ALTERNATE_SIZE(SPECIES_MOLTRES_G, 2.0, 66.0),
	ALTERNATE_SIZE(SPECIES_SLOWKING_G, 1.8, 79.5),
	ALTERNATE_SIZE(SPECIES_CORSOLA_G, 0.6, 0.5),
	ALTERNATE_SIZE(SPECIES_DARUMAKA_G, 0.7, 40.0),
	ALTERNATE_SIZE(SPECIES_DARMANITAN_G, 1.7, 120),
	ALTERNATE_SIZE(SPECIES_DARMANITAN_G_ZEN, 1.7, 120),
	ALTERNATE_SIZE(SPECIES_STUNFISK_G, 0.7, 20.5),
	ALTERNATE_SIZE(SPECIES_GROWLITHE_H, 0.8, 22.7),
	ALTERNATE_SIZE(SPECIES_ARCANINE_H, 2.0, 168.0),
	ALTERNATE_SIZE(SPECIES_VOLTORB_H, 0.5, 13.0),
	ALTERNATE_SIZE(SPECIES_ELECTRODE_H, 1.2, 71.0),
	ALTERNATE_SIZE(SPECIES_TYPHLOSION_H, 1.6, 69.8),
	ALTERNATE_SIZE(SPECIES_SNEASEL_H, 0.9, 27.0),
	ALTERNATE_SIZE(SPECIES_SAMUROTT_H, 1.5, 58.2),
	ALTERNATE_SIZE(SPECIES_LILLIGANT_H, 1.2, 19.2),
	ALTERNATE_SIZE(SPECIES_ZOROARK_H, 1.6, 73.0),
	ALTERNATE_SIZE(SPECIES_BRAVIARY_H, 1.6, 43.4),
	ALTERNATE_SIZE(SPECIES_SLIGGOO_H, 0.7, 68.5),
	ALTERNATE_SIZE(SPECIES_GOODRA_H, 1.7, 334.1),
	ALTERNATE_SIZE(SPECIES_AVALUGG_H, 1.4, 262.4),
	ALTERNATE_SIZE(SPECIES_DECIDUEYE_H, 1.6, 37.0),

	ALTERNATE_SIZE(SPECIES_TABLES_TERMIN, 0, 0),
};

const species_t gSkyBattleBannedSpeciesList[] =
{
#ifndef UNBOUND
	SPECIES_SPEAROW,
	// SPECIES_FARFETCHD,
	// SPECIES_HOOTHOOT,
	SPECIES_NATU,
	SPECIES_MURKROW,
	SPECIES_DELIBIRD,
	SPECIES_TAILLOW,
	SPECIES_STARLY,
	SPECIES_CHATOT,
	SPECIES_SHAYMIN_SKY,
	SPECIES_PIDOVE,
	SPECIES_ARCHEN,
	SPECIES_DUCKLETT,
	SPECIES_RUFFLET,
	// SPECIES_VULLABY,
	// SPECIES_FLETCHLING,
	SPECIES_HAWLUCHA,
	// SPECIES_ROWLET,
	// SPECIES_PIKIPEK,
#endif
	SPECIES_GENGAR,
	SPECIES_SILVALLY_FLYING,
	SPECIES_DODUO,
	SPECIES_DODRIO,
	SPECIES_TABLES_TERMIN
};

//For the purposes of the Beast Ball
const species_t gUltraBeastList[] =
{
	SPECIES_NIHILEGO,
	SPECIES_BUZZWOLE,
	SPECIES_PHEROMOSA,
	SPECIES_XURKITREE,
	SPECIES_CELESTEELA,
	SPECIES_KARTANA,
	SPECIES_GUZZLORD,
	SPECIES_POIPOLE,
	SPECIES_NAGANADEL,
	SPECIES_STAKATAKA,
	SPECIES_BLACEPHALON,
	SPECIES_TABLES_TERMIN
};

const species_t gDeerlingForms[] =
{
	SPECIES_DEERLING,
	SPECIES_DEERLING_SUMMER,
	SPECIES_DEERLING_AUTUMN,
	SPECIES_DEERLING_WINTER,
	//No termin here
};

const u8 gNumDeerlingForms = NELEMS(gDeerlingForms);

const species_t gSawsbuckForms[] =
{
	SPECIES_SAWSBUCK,
	SPECIES_SAWSBUCK_SUMMER,
	SPECIES_SAWSBUCK_AUTUMN,
	SPECIES_SAWSBUCK_WINTER,
	//No termin here
};

const u8 gNumSawsbuckForms = NELEMS(gSawsbuckForms);

const species_t gVivillonForms[] =
{
	SPECIES_VIVILLON,
	SPECIES_VIVILLON_ARCHIPELAGO,
	SPECIES_VIVILLON_CONTINENTAL,
	SPECIES_VIVILLON_ELEGANT,
	SPECIES_VIVILLON_GARDEN,
	SPECIES_VIVILLON_FANCY,
	SPECIES_VIVILLON_HIGH_PLAINS,
	SPECIES_VIVILLON_ICY_SNOW,
	SPECIES_VIVILLON_JUNGLE,
	SPECIES_VIVILLON_MARINE,
	SPECIES_VIVILLON_MODERN,
	SPECIES_VIVILLON_MONSOON,
	SPECIES_VIVILLON_OCEAN,
	SPECIES_VIVILLON_POKEBALL,
	SPECIES_VIVILLON_POLAR,
	SPECIES_VIVILLON_RIVER,
	SPECIES_VIVILLON_SANDSTORM,
	SPECIES_VIVILLON_SAVANNA,
	SPECIES_VIVILLON_SUN,
	SPECIES_VIVILLON_TUNDRA,
	//No termin here
};

const u8 gNumVivillonForms = NELEMS(gVivillonForms);

const species_t gFlabebeForms[] =
{
	SPECIES_FLABEBE,
	SPECIES_FLABEBE_BLUE,
	SPECIES_FLABEBE_ORANGE,
	SPECIES_FLABEBE_YELLOW,
	SPECIES_FLABEBE_WHITE,
	//No termin here
};

const u8 gNumFlabebeForms = NELEMS(gFlabebeForms);

const species_t gFloetteForms[] =
{
	SPECIES_FLOETTE,
	SPECIES_FLOETTE_BLUE,
	SPECIES_FLOETTE_ORANGE,
	SPECIES_FLOETTE_YELLOW,
	SPECIES_FLOETTE_WHITE,
	//No termin here
};

const u8 gNumFloetteForms = NELEMS(gFloetteForms);

const species_t gFlorgesForms[] =
{
	SPECIES_FLORGES,
	SPECIES_FLORGES_BLUE,
	SPECIES_FLORGES_ORANGE,
	SPECIES_FLORGES_YELLOW,
	SPECIES_FLORGES_WHITE,
	//No termin here
};

const u8 gNumFlorgesForms = NELEMS(gFlorgesForms);

const species_t gFurfrouForms[] =
{
	SPECIES_FURFROU,
	SPECIES_FURFROU_HEART,
	SPECIES_FURFROU_DIAMOND,
	SPECIES_FURFROU_STAR,
	SPECIES_FURFROU_PHAROAH,
	SPECIES_FURFROU_KABUKI,
	SPECIES_FURFROU_LA_REINE,
	SPECIES_FURFROU_MATRON,
	SPECIES_FURFROU_DANDY,
	SPECIES_FURFROU_DEBUTANTE,
	//No termin here
};

const u8 gNumFurfrouForms = NELEMS(gFurfrouForms);

const species_t gPikachuCapForms[] =
{
	SPECIES_PIKACHU_CAP_ORIGINAL,
	SPECIES_PIKACHU_CAP_HOENN,
	SPECIES_PIKACHU_CAP_SINNOH,
	SPECIES_PIKACHU_CAP_UNOVA,
	SPECIES_PIKACHU_CAP_KALOS,
	SPECIES_PIKACHU_CAP_ALOLA,
	SPECIES_PIKACHU_CAP_PARTNER,
	//No termin here
};

const u8 gNumPikachuCapForms = NELEMS(gPikachuCapForms);

const species_t gAlcremieForms[] =
{
	SPECIES_ALCREMIE_STRAWBERRY,
	SPECIES_ALCREMIE_BERRY,
	SPECIES_ALCREMIE_CLOVER,
	SPECIES_ALCREMIE_FLOWER,
	SPECIES_ALCREMIE_LOVE,
	SPECIES_ALCREMIE_RIBBON,
	SPECIES_ALCREMIE_STAR,
	//No termin here
};

const u8 gNumAlcremieForms = NELEMS(gAlcremieForms);

const ability_t gSmogonOU_AbilityBanList[] =
{
	ABILITY_ARENATRAP,
	ABILITY_SHADOWTAG,
	ABILITY_POWERCONSTRUCT,
	ABILITY_MOODY,
	ABILITY_TABLES_TERMIN
};

const ability_t gSmogonOUDoubles_AbilityBanList[] =
{
	ABILITY_POWERCONSTRUCT,
	ABILITY_MOODY,
	ABILITY_TABLES_TERMIN
};

const item_t gBattleTowerStandard_ItemBanList[] =
{
	#ifdef OLD_SOUL_DEW_EFFECT
	ITEM_SOUL_DEW,
	#endif
	ITEM_TABLES_TERMIN
};

const move_t gRingChallenge_MoveBanList[] =
{
	MOVE_SELFDESTRUCT,
	MOVE_EXPLOSION,
	MOVE_MISTYEXPLOSION,
	MOVE_PERISHSONG,
	MOVE_DESTINYBOND,
};

const item_t gSmogonOU_ItemBanList[] =
{
	ITEM_BLAZIKENITE,
	ITEM_GENGARITE,
	ITEM_LUCARIONITE,
	ITEM_KANGASKHANITE,
	ITEM_METAGROSSITE,
	ITEM_SALAMENCITE,
	ITEM_RED_ORB,
	ITEM_BLUE_ORB,
	#ifdef OLD_SOUL_DEW_EFFECT
	ITEM_SOUL_DEW,
	#endif
	ITEM_TABLES_TERMIN
};

const item_t gSmogonNationalDexOU_ItemBanList[] =
{
	ITEM_BLAZIKENITE,
	ITEM_GENGARITE,
	ITEM_LUCARIONITE,
	ITEM_KANGASKHANITE,
	ITEM_SALAMENCITE,
	ITEM_RED_ORB,
	ITEM_BLUE_ORB,
	#ifdef OLD_SOUL_DEW_EFFECT
	ITEM_SOUL_DEW,
	#endif
	ITEM_TABLES_TERMIN
};

const item_t gSmogonOUDoubles_ItemBanList[] =
{
	ITEM_GENGARITE,
	ITEM_EEVIUM_Z,
	ITEM_KANGASKHANITE,
	ITEM_RED_ORB,
	ITEM_BLUE_ORB,
	#ifdef OLD_SOUL_DEW_EFFECT
	ITEM_SOUL_DEW,
	#endif
	ITEM_TABLES_TERMIN
};

const move_t gSmogonOUDoubles_MoveBanList[] =
{
	MOVE_DARKVOID,
	MOVE_SWAGGER,
	MOVE_TABLES_TERMIN
};

const move_t gSmogon_MoveBanList[] =
{
	MOVE_DOUBLETEAM,
	MOVE_MINIMIZE,
	MOVE_FISSURE,
	MOVE_GUILLOTINE,
	MOVE_HORNDRILL,
	MOVE_SHEERCOLD,
	MOVE_TABLES_TERMIN
};

const move_t gSmogonLittleCup_MoveBanList[] =
{
	MOVE_DRAGONRAGE,
	MOVE_SONICBOOM,
	MOVE_SWAGGER,
	MOVE_TABLES_TERMIN
};

const item_t gSmogonLittleCup_ItemBanList[] =
{
	ITEM_EEVIUM_Z,
	ITEM_TABLES_TERMIN
};

const ability_t gMiddleCup_AbilityBanList[] =
{
	ABILITY_CONTRARY,
	ABILITY_PROTEAN,
	ABILITY_TABLES_TERMIN
};

const species_t gMiddleCup_ItemBanList[] =
{
	ITEM_LIGHT_BALL,
	ITEM_EVIOLITE,
	ITEM_TABLES_TERMIN
};

const ability_t gSmogonMonotype_AbilityBanList[] =
{
	ABILITY_BATTLEBOND,
	ABILITY_SHADOWTAG,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonMonotype_ItemBanList[] =
{
	ITEM_DAMP_ROCK,
	ITEM_GENGARITE,
	ITEM_KANGASKHANITE,
	ITEM_LUCARIONITE,
	ITEM_MAWILITE,
	ITEM_MEDICHAMITE,
	ITEM_METAGROSSITE,
	ITEM_SALAMENCITE,
	ITEM_SMOOTH_ROCK,
	ITEM_TERRAIN_EXTENDER,
	ITEM_RED_ORB,
	ITEM_BLUE_ORB,
	#ifdef OLD_SOUL_DEW_EFFECT
	ITEM_SOUL_DEW,
	#endif
	ITEM_TABLES_TERMIN
};

const item_t gSmogonAverageMons_ItemBanList[] =
{
	ITEM_THICK_CLUB,
	ITEM_DEEP_SEA_TOOTH,
	ITEM_LIGHT_BALL,
	ITEM_EVIOLITE,
	ITEM_MAWILITE,
	ITEM_MEDICHAMITE,
	ITEM_GENGARITE,
	ITEM_TABLES_TERMIN
};

const move_t gSmogonAverageMons_MoveBanList[] =
{
	MOVE_CHATTER,
	MOVE_BATONPASS,
	MOVE_TABLES_TERMIN
};

const u8 gSmogonAverageMons_AbilityBanList[] =
{
	ABILITY_HUGEPOWER,
	#ifdef ABILITY_PUREPOWER
	ABILITY_PUREPOWER,
	#endif
	ABILITY_SHADOWTAG,
	ABILITY_ARENATRAP,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogon350Cup_ItemBanList[] =
{
	ITEM_DEEP_SEA_TOOTH,
	ITEM_LIGHT_BALL,
	ITEM_EVIOLITE,
	ITEM_EEVIUM_Z,
	ITEM_TABLES_TERMIN
};

const u8 gSmogon350Cup_AbilityBanList[] =
{
	ABILITY_SHADOWTAG,
	ABILITY_ARENATRAP,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonScalemons_ItemBanList[] =
{
	ITEM_DEEP_SEA_SCALE,
	ITEM_DEEP_SEA_TOOTH,
	ITEM_EEVIUM_Z,
	ITEM_EVIOLITE,
	ITEM_LIGHT_BALL,
	ITEM_THICK_CLUB,
	ITEM_MAWILITE,
	ITEM_MEDICHAMITE,
	ITEM_GENGARITE,
	ITEM_TABLES_TERMIN
};

const u8 gSmogonScalemons_AbilityBanList[] =
{
	ABILITY_ARENATRAP,
	ABILITY_SHADOWTAG,
	ABILITY_HUGEPOWER,
	ABILITY_MOODY,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonMetronome_ItemBanList[] =
{
	ITEM_ABOMASITE,
	ITEM_AGUAV_BERRY,
	ITEM_ASSAULT_VEST,
	ITEM_BERRY_JUICE,
	ITEM_BLACK_SLUDGE,
	ITEM_ENIGMA_BERRY,
	ITEM_FIGY_BERRY,
	ITEM_IAPAPA_BERRY,
	ITEM_KANGASKHANITE,
	ITEM_LEFTOVERS,
	ITEM_MAGO_BERRY,
	ITEM_MEDICHAMITE,
	ITEM_ORAN_BERRY,
	ITEM_ROCKY_HELMET,
	ITEM_SHELL_BELL,
	ITEM_SITRUS_BERRY,
	ITEM_WIKI_BERRY,
};

const ability_t gSmogonMetronome_AbilityBanList[] =
{
	ABILITY_BATTLEBOND,
	ABILITY_CHEEKPOUCH,
	ABILITY_CURSEDBODY,
	ABILITY_DESOLATELAND,
	ABILITY_DRYSKIN,
	ABILITY_FLUFFY,
	ABILITY_FURCOAT,
	ABILITY_GORILLATACTICS,
	ABILITY_GRASSYSURGE,
	ABILITY_HUGEPOWER,
	ABILITY_ICEBODY,
	#ifdef ABILITY_IRONBARBS
	ABILITY_IRONBARBS,
	#endif
	#ifdef ABILITY_LIBERO
	ABILITY_LIBERO,
	#endif
	ABILITY_MOODY,
	ABILITY_PARENTALBOND,
	ABILITY_PERISHBODY,
	ABILITY_POISONHEAL,
	ABILITY_POWERCONSTRUCT,
	ABILITY_PRESSURE,
	ABILITY_PRIMORDIALSEA,
	ABILITY_PROTEAN,
	#ifdef ABILITY_PUREPOWER
	ABILITY_PUREPOWER,
	#endif
	ABILITY_RAINDISH,
	ABILITY_ROUGHSKIN,
	ABILITY_SANDSPIT,
	ABILITY_SANDSTREAM,
	ABILITY_SNOWWARNING,
	ABILITY_STAMINA,
	ABILITY_VOLTABSORB,
	ABILITY_WATERABSORB,
	ABILITY_WONDERGUARD,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonUU_ItemBanList[] =
{
	ITEM_ALAKAZITE,
	ITEM_CHARIZARDITE_X,
	ITEM_CHARIZARDITE_Y,
	ITEM_DIANCITE,
	ITEM_GARCHOMPITE,
	ITEM_GYARADOSITE,
	ITEM_LATIASITE,
	ITEM_LOPUNNITE,
	ITEM_MAWILITE,
	ITEM_MEDICHAMITE,
	ITEM_SABLENITE,
	ITEM_SCIZORITE,
	ITEM_SWAMPERTITE,
	ITEM_TYRANITARITE,
	ITEM_GALLADITE,
	ITEM_GARDEVOIRITE,
	ITEM_HERACRONITE,
	ITEM_LATIOSITE,
	ITEM_PINSIRITE,
	ITEM_VENUSAURITE,
	ITEM_KOMMONIUM_Z,
	ITEM_MEWNIUM_Z,
	ITEM_TABLES_TERMIN
};

const ability_t gSmogonUU_AbilityBanList[] =
{
	ABILITY_DRIZZLE,
	ABILITY_DROUGHT,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonRU_ItemBanList[] =
{
	ITEM_AERODACTYLITE,
	ITEM_AGGRONITE,
	ITEM_ALTARIANITE,
	ITEM_BEEDRILLITE,
	ITEM_MANECTITE,
	ITEM_PIDGEOTITE,
	ITEM_SHARPEDONITE,
	ITEM_STEELIXITE,
	ITEM_ABSOLITE,
	ITEM_HOUNDOOMINITE,
	ITEM_SLOWBRONITE,
	ITEM_TABLES_TERMIN
};

const ability_t gSmogonRU_AbilityBanList[] =
{
	ABILITY_DRIZZLE,
	ABILITY_TABLES_TERMIN
};

const item_t gSmogonNU_ItemBanList[] =
{
	ITEM_AMPHAROSITE,
	ITEM_BANETTITE,
	ITEM_BLASTOISINITE,
	ITEM_SCEPTILITE,
	ITEM_CAMERUPTITE,
	ITEM_TABLES_TERMIN
};
