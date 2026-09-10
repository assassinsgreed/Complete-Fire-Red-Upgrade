#include "../defines_battle.h"
#include "../../include/battle.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/opponents.h"
#include "../../include/constants/battle_ai.h"
#include "../../include/constants/items.h"
#include "../../include/easy_text.h"
#include "../../include/new/build_pokemon_2.h"

// NOTE: The trainers here are overrides for those found in trainer_tables.c, loaded when
// FLAG_DIVERGENT_WILD_ENCOUNTERS is set and FLAG_HARD_MODE is NOT (see hard_divergent_trainer_tables.c
// for the Hard + Divergent combination). If a trainer is not present here, the lookup falls back to
// the standard trainer in trainer_tables.c. See GetTrainerData() in build_pokemon.c for the priority
// order, and battle.h for the list of struct types that can be used.
//
// These are a 1:1 copy of trainer_tables.c with each party renamed with a _Divergent suffix so the
// teams can be edited independently. Everything else (name, class, items, AI flags, etc.) is unchanged.

#define TrainerAIFlags_Youngster_Standard       (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Lass_Standard            (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Burglar_Standard         (AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Swimmer_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY)
#define TrainerAIFlags_CoolTrainer_Standard     (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_BugCatcher_Standard      (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Camper_Standard          (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Picnicker_Standard       (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_SrAndJr_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_DOUBLE_BATTLE)
#define TrainerAIFlags_NinjaBoy_Standard        (AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Guitarist_Standard       (AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Nurse_Standard           (AI_SCRIPT_HP_AWARE)
#define TrainerAIFlags_BirdKeeper_Standard      (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_RuinManiac_Standard      (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_BlackBelt_Standard       (AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_PREFER_STRONGEST_MOVE)
#define TrainerAIFlags_Psychic_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE)
#define TrainerAIFlags_Beauty_Standard          (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE)
#define TrainerAIFlags_Lady_Standard            (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN)
#define TrainerAIFlags_CrushGirl_Standard       (AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Gentleman_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_Fisherman_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_Hiker_Standard           (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE)
#define TrainerAIFlags_Engineer_Standard        (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Pokefan_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_Gambler_Standard         (AI_SCRIPT_RISKY)
#define TrainerAIFlags_Collector_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE)
#define TrainerAIFlags_PokemonBreeder_Standard  (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_SuperNerd_Standard       (AI_SCRIPT_SEMI_SMART)
#define TrainerAIFlags_ParasolLady_Standard     (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE)
#define TrainerAIFlags_Channeler_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY)
#define TrainerAIFlags_Tuber_Standard           (AI_SCRIPT_CHECK_BAD_MOVE)
#define TrainerAIFlags_Scientist_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_Painter_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART)
#define TrainerAIFlags_Triathlete_Standard      (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Juggler_Standard         (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN)
#define TrainerAIFlags_Skier_Standard           (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_DragonTamer_Standard     (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_TRY_TO_FAINT)
#define TrainerAIFlags_Disciple_Standard        (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_Developer_Standard       (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SEMI_SMART)
#define TrainerAIFlags_GymTrainees_Standard     (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY)
#define TrainerAIFlags_AscensionTower_Standard  (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART)
#define TrainerAIFlags_GymLeaderRematches_Standard (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SEMI_SMART)

#define NO_NAME                                                                                      \
    {                                                                                                \
        _END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE \
    }

// #region Trainer Structs

// #region Important trainers
const struct TrainerMonNoItemCustomMoves sParty_Rival1_Divergent[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_EEVEE,
        .moves = { MOVE_TACKLE, MOVE_TAILWHIP, MOVE_NONE, MOVE_NONE },
        .ability = Ability_1 // Run Away, for first fight
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_Rival2_Divergent[] = {
    { .lvl = 12, .species = SPECIES_PIDGEY },
    { .lvl = 14, .species = SPECIES_EEVEE },
};

const struct TrainerMonNoItemCustomMoves sParty_PartnerRival1_Divergent[] = {
    {
        .lvl = 13,
        .species = SPECIES_PIDGEY,
        .moves = { MOVE_TACKLE, MOVE_SANDATTACK, MOVE_GUST, MOVE_QUICKATTACK },
        .ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 15,
        .species = SPECIES_EEVEE,
        .moves = { MOVE_QUICKATTACK, MOVE_HELPINGHAND, MOVE_TAILWHIP, MOVE_SANDATTACK },
        .ability = Ability_2 // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival3_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_MILCERY,
        .moves = { MOVE_ACIDARMOR, MOVE_DRAININGKISS, MOVE_ATTRACT, MOVE_AROMATHERAPY },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 30,
        .species = SPECIES_PIDGEOTTO,
        .moves = { MOVE_FEATHERDANCE, MOVE_TWISTER, MOVE_GUST, MOVE_WHIRLWIND },
        .ability = Ability_Hidden // Big Pecks 
    },
    {
        .lvl = 32,
        .species = SPECIES_EEVEE,
        .moves = { MOVE_BITE, MOVE_COVET, MOVE_DOUBLEKICK, MOVE_BABYDOLLEYES },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_2 // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_Casey1_Divergent[] = {
    {
        .lvl = 15,
        .species = SPECIES_MUNNA,
        .moves = { MOVE_PSYBEAM, MOVE_DEFENSECURL, MOVE_STOREDPOWER, MOVE_HYPNOSIS},
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 17,
        .species = SPECIES_MURKROW,
        .moves = { MOVE_GUST, MOVE_HAZE, MOVE_CALMMIND, MOVE_WINGATTACK },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_2 // Super Luck
    }
};

const struct TrainerMonItemCustomMoves sParty_Casey2_Divergent[] = {
    {
        .lvl = 33,
        .species = SPECIES_MUSHARNA,
        .moves = { MOVE_CALMMIND, MOVE_MOONBLAST, MOVE_STOREDPOWER, MOVE_MOONLIGHT},
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 35,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_TAILWIND, MOVE_NASTYPLOT, MOVE_DARKPULSE, MOVE_PSYCHIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Vaporeon_Divergent[] = {
	{
		.lvl = 34,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_WATERPULSE, MOVE_AURORABEAM, MOVE_CHARM, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Jolteon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERWAVE, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_DOUBLEKICK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Flareon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FIREFANG, MOVE_BITE, MOVE_SUNNYDAY, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Espeon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_PSYBEAM, MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Umbreon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_SNARL, MOVE_MOONLIGHT, MOVE_CONFUSERAY, MOVE_DIG },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Leafeon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_LEECHSEED, MOVE_RAZORLEAF, MOVE_AERIALACE, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Glaceon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_HAIL, MOVE_AURORAVEIL, MOVE_ICEFANG, MOVE_ROCKSMASH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Sylveon_Divergent[] = {
    {
		.lvl = 34,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
	{
		.lvl = 34,
		.species = SPECIES_PIDGEOTTO,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.ability = Ability_Hidden // Big Pecks
	},
    {
        .lvl = 36,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_DRAININGKISS, MOVE_COVET, MOVE_LIGHTSCREEN, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11_Alistair_Divergent[] = {
    {
        .lvl = 34,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 34,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_UTURN },
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 36,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Vaporeon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_WATERPULSE, MOVE_AURORABEAM, MOVE_CHARM, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Jolteon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERWAVE, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_DOUBLEKICK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Flareon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FIREFANG, MOVE_BITE, MOVE_SUNNYDAY, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Espeon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_PSYBEAM, MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Umbreon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_SNARL, MOVE_MOONLIGHT, MOVE_CONFUSERAY, MOVE_DIG },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Leafeon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_LEECHSEED, MOVE_RAZORLEAF, MOVE_AERIALACE, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Glaceon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_HAIL, MOVE_AURORAVEIL, MOVE_ICEFANG, MOVE_ROCKSMASH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Sylveon_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 36,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 37,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_DRAININGKISS, MOVE_COVET, MOVE_LIGHTSCREEN, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Vaporeon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_MUDDYWATER, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Jolteon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_RAINDANCE, MOVE_WEATHERBALL, MOVE_SHADOWBALL },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Flareon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_WILLOWISP, MOVE_DIG, MOVE_FLAREBLITZ, MOVE_SUNNYDAY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Espeon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_MORNINGSUN, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Umbreon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_CURSE, MOVE_MOONLIGHT, MOVE_TOXIC, MOVE_DARKPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Leafeon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_LEECHSEED },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Glaceon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_BLIZZARD, MOVE_HAIL, MOVE_AURORAVEIL, MOVE_MUDSHOT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Sylveon_Divergent[] = {
    {
        .lvl = 44,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 43,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_WINGATTACK, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 45,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_MOONBLAST, MOVE_WISH, MOVE_DIG, MOVE_PROTECT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival_EmraldinQuayEvent_Divergent[] = {
    {
        .lvl = 51,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_FLASHCANNON, MOVE_DISCHARGE, MOVE_MAGNETRISE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 51,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BRINE, MOVE_REVERSAL, MOVE_THUNDERPUNCH, MOVE_CURSE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 52,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_SLUDGEBOMB, MOVE_POWERWHIP },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 53,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 54,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_POISONJAB, MOVE_LUNGE, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Rival_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 54,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 55,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 55,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 56,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_PartnerRival_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 55,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 56,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Alistair_Divergent[] = {
    {
        .lvl = 55,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 54,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_ACROBATICS },
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 56,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 57,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_ROCKSLIDE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    }
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Vaporeon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_SCALD, MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_FLIPTURN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Jolteon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERBOLT, MOVE_VOLTSWITCH, MOVE_SHADOWBALL, MOVE_METALSOUND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Flareon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_BODYSLAM, MOVE_DIG, MOVE_LASTRESORT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Flash Fire
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Espeon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Umbreon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_SNARL, MOVE_TOXIC, MOVE_MEANLOOK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Leafeon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_SYNTHESIS, MOVE_AERIALACE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Glaceon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_FREEZEDRY, MOVE_HAIL, MOVE_AURORAVEIL, MOVE_SHADOWBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Sylveon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 65,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 65,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 65,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 66,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_MOONBLAST, MOVE_WISH, MOVE_PSYSHOCK, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_ExhibitionBattle_SecondaryTeam_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_FLASHCANNON, MOVE_DISCHARGE, MOVE_MAGNETRISE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 65,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BRINE, MOVE_REVERSAL, MOVE_THUNDERPUNCH, MOVE_CURSE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 65,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_SLUDGEBOMB, MOVE_POWERWHIP },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 65,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 66,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_POISONJAB, MOVE_LUNGE, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_PostCredits_Alistair_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 70,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 70,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_STONEEDGE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 72,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Vaporeon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_SCALD, MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_FLIPTURN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Jolteon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERBOLT, MOVE_VOLTSWITCH, MOVE_SHADOWBALL, MOVE_METALSOUND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Flareon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_BODYSLAM, MOVE_DIG, MOVE_LASTRESORT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Flash Fire
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Espeon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Umbreon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_SNARL, MOVE_TOXIC, MOVE_MEANLOOK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Leafeon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_SYNTHESIS, MOVE_AERIALACE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Glaceon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_FREEZEDRY, MOVE_HAIL, MOVE_AURORAVEIL, MOVE_SHADOWBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Sylveon_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 71,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 71,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 73,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_MOONBLAST, MOVE_WISH, MOVE_PSYSHOCK, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_FLASHCANNON, MOVE_DISCHARGE, MOVE_MAGNETRISE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 71,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BRINE, MOVE_REVERSAL, MOVE_THUNDERPUNCH, MOVE_CURSE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 71,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_SLUDGEBOMB, MOVE_POWERWHIP },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 72,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 73,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_POISONJAB, MOVE_LUNGE, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

// #endregion

// #region Route 1 
const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterPeter_Divergent[] = {
    { .iv = 0, .lvl = 3, .species = SPECIES_ZIGZAGOON_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_LassHelena_Divergent[] = {
    { .lvl = 3, .species = SPECIES_STARLY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterHarlan_Divergent[] = {
    { .lvl = 4, .species = SPECIES_SHINX },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_BurglarBryce_Divergent[] = {
    { .lvl = 48, .species = SPECIES_TRUBBISH },
    { .lvl = 48, .species = SPECIES_PANCHAM },
    { .lvl = 50, .species = SPECIES_PANGORO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_SwimmerRebecca_Divergent[] = {
    { .lvl = 50, .species = SPECIES_STARYU },
    { .lvl = 51, .species = SPECIES_STARMIE },
};
// #endregion

// #region Route 2
const struct TrainerMonNoItemDefaultMoves sParty_Route2_YoungsterJoey_Divergent[] = {
    { .lvl = 5, .species = SPECIES_ZIGZAGOON_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassKimberly_Divergent[] = {
    { .lvl = 4, .species = SPECIES_SOLOSIS },
    { .lvl = 4, .species = SPECIES_CATERPIE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassRikki_Divergent[] = {
    { .lvl = 7, .species = SPECIES_ZIGZAGOON_G },
    { .lvl = 7, .species = SPECIES_ZIGZAGOON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_CoolTrainerAndy_Divergent[] = {
    { .lvl = 50, .species = SPECIES_ZWEILOUS },
    { .lvl = 50, .species = SPECIES_GRAPPLOCT },
    { .lvl = 52, .species = SPECIES_ARMALDO },
};
// #endregion

// #region Varisi Forest
const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherKendell_Divergent[] = {
    { .lvl = 4, .species = SPECIES_CATERPIE },
    { .lvl = 5, .species = SPECIES_WEEDLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherBraden_Divergent[] = {
    { .lvl = 4, .species = SPECIES_KRICKETOT },
    { .lvl = 5, .species = SPECIES_SEWADDLE },
    { .lvl = 5, .species = SPECIES_SEWADDLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassBreanna_Divergent[] = {
    { .lvl = 5, .species = SPECIES_CHEWTLE },
    { .lvl = 6, .species = SPECIES_BOUNSWEET },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassMimi_Divergent[] = {
    { .lvl = 5, .species = SPECIES_BUNNELBY },
    { .lvl = 6, .species = SPECIES_PIDGEY },
    { .lvl = 7, .species = SPECIES_ODDISH },
};
// #endregion

// #region Rhodanzi City
const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Alonso_Divergent[] = {
    {
        .lvl = 9,
        .species = SPECIES_SPRITZEE,
        .moves = { MOVE_MISTYTERRAIN, MOVE_FAIRYWIND, MOVE_FAKETEARS, MOVE_NONE },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 8,
        .species = SPECIES_MEDITITE,
        .moves = { MOVE_PSYCHICTERRAIN, MOVE_CONFUSION, MOVE_WORKUP, MOVE_NONE },
        .ability = Ability_1 // Pure Power
    },
};

const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Brandon_Divergent[] = {
    {
        .lvl = 10,
        .species = SPECIES_ELECTRIKE,
        .moves = { MOVE_ELECTRICTERRAIN, MOVE_THUNDERSHOCK, MOVE_THUNDERWAVE, MOVE_NONE },
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_RhodanziCity_LeaderTerrence_Divergent[] = {
    {
        .lvl = 11,
        .species = SPECIES_GROOKEY,
        .moves = { MOVE_SCRATCH, MOVE_BRANCHPOKE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 13,
        .species = SPECIES_DEERLING,
        .moves = { MOVE_GRASSKNOT, MOVE_LEECHSEED, MOVE_DOUBLEKICK, MOVE_NONE },
		.heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_2 // Sap Sipper
    }
};
// #endregion

// #region Route 3
const struct TrainerMonNoItemDefaultMoves sParty_Route3_PicknickerTana_Divergent[] = {
    { .lvl = 9, .species = SPECIES_MILCERY },
    { .lvl = 10, .species = SPECIES_PIDGEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_BugCatcherIrwin_Divergent[] = {
    { .lvl = 8, .species = SPECIES_WEEDLE },
    { .lvl = 8, .species = SPECIES_KAKUNA },
    { .lvl = 10, .species = SPECIES_BEEDRILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_YoungsterLogan_Divergent[] = {
    { .lvl = 10, .species = SPECIES_DIGLETT_A },
    { .lvl = 11, .species = SPECIES_SOLOSIS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TwinsNinaAndMeg_Divergent[] = {
    { .lvl = 12, .species = SPECIES_POLIWAG },
    { .lvl = 10, .species = SPECIES_SEWADDLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_NinjaBoyBotan_Divergent[] = {
    { .lvl = 11, .species = SPECIES_STUNKY },
    { .lvl = 11, .species = SPECIES_SPINARAK },
    { .lvl = 11, .species = SPECIES_KRICKETUNE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_RockerJude_Divergent[] = {
    { .lvl = 13, .species = SPECIES_GROOKEY },
    { .lvl = 14, .species = SPECIES_WOOBAT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TeamPlutoRaul_Divergent[] = {
    { .lvl = 12, .species = SPECIES_STUNKY },
    { .lvl = 13, .species = SPECIES_CHEWTLE }
};
// #endregion

// #region Rubarr Desert
const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_NurseJaina_Divergent[] = {
    { .lvl = 12, .species = SPECIES_CLEFFA },
    { .lvl = 13, .species = SPECIES_CLEFAIRY },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_BirdKeeperNolan_Divergent[] = {
    { .lvl = 13, .species = SPECIES_STARLY },
    { .lvl = 13, .species = SPECIES_NATU },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacKent_Divergent[] = {
    { .lvl = 12, .species = SPECIES_BALTOY },
    { .lvl = 12, .species = SPECIES_BALTOY },
    { .lvl = 13, .species = SPECIES_SILICOBRA },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_BlackbeltKobiyashi_Divergent[] = {
    { .lvl = 13, .species = SPECIES_MAKUHITA },
    { .lvl = 14, .species = SPECIES_MACHOP },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacAlbert_Divergent[] = {
    { .lvl = 14, .species = SPECIES_BALTOY },
    { .lvl = 14, .species = SPECIES_DIGLETT_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMika_Divergent[] = {
    { .lvl = 12, .species = SPECIES_STUNKY },
    { .lvl = 12, .species = SPECIES_TRUBBISH },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMarcel_Divergent[] = {
    { .lvl = 11, .species = SPECIES_WOOBAT },
    { .lvl = 11, .species = SPECIES_DRIFLOON },
    { .lvl = 13, .species = SPECIES_SOLOSIS },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoTana_Divergent[] = {
    { .lvl = 12, .species = SPECIES_CHEWTLE },
    { .lvl = 12, .species = SPECIES_ANORITH },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoClancy_Divergent[] = {
    { .lvl = 14, .species = SPECIES_SNUBBULL },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoEna_Divergent[] = {
    { .lvl = 12, .species = SPECIES_SPINARAK },
    { .lvl = 13, .species = SPECIES_FOMANTIS },
};

const struct TrainerMonNoItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene_Divergent[] = {
    {
        .lvl = 14,
        .species = SPECIES_IMPIDIMP,
        .moves = { MOVE_FAKEOUT, MOVE_BITE, MOVE_FLATTER, MOVE_NONE },
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 14,
        .species = SPECIES_TYNAMO,
        .moves = { MOVE_TACKLE, MOVE_THUNDERWAVE, MOVE_SPARK, MOVE_CHARGEBEAM },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 15,
        .species = SPECIES_NUMEL,
        .moves = { MOVE_EMBER, MOVE_BULLDOZE, MOVE_FOCUSENERGY, MOVE_GROWL },
        .ability = Ability_1 // Oblivious
    },
};
// #endregion

// #region Route 4
const struct TrainerMonNoItemDefaultMoves sParty_Route4_Camper_Pietro_Divergent[] = {
    { .lvl = 12, .species = SPECIES_GROWLITHE },
    { .lvl = 12, .species = SPECIES_SENTRET },
    { .lvl = 13, .species = SPECIES_CHEWTLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Psychic_Adriano_Divergent[] = {
    { .lvl = 13, .species = SPECIES_SOLOSIS },
    { .lvl = 13, .species = SPECIES_MEDITITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Beauty_Beatrice_Divergent[] = {
    { .lvl = 13, .species = SPECIES_BOUNSWEET },
    { .lvl = 14, .species = SPECIES_BUNNELBY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Lady_Alda_Divergent[] = {
    { .lvl = 14, .species = SPECIES_WOOPER },
    { .lvl = 14, .species = SPECIES_PIDGEY },
    { .lvl = 14, .species = SPECIES_MEOWTH_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Lass_Isabela_Divergent[] = {
    { .lvl = 15, .species = SPECIES_VULPIX },
    { .lvl = 15, .species = SPECIES_HOPPIP },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Rowley_Divergent[] = {
    { .lvl = 17, .species = SPECIES_DARTRIX }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Crush_Girl_Elise_Divergent[] = {
    { .lvl = 14, .species = SPECIES_MAKUHITA },
    { .lvl = 15, .species = SPECIES_TYROGUE },
    { .lvl = 15, .species = SPECIES_MACHOP }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Gentleman_Porter_Divergent[] = {
    { .lvl = 15, .species = SPECIES_APPLIN },
    { .lvl = 16, .species = SPECIES_STUFFUL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Luca_Divergent[] = {
    { .lvl = 15, .species = SPECIES_DUCKLETT },
    { .lvl = 17, .species = SPECIES_PIDGEOTTO },
};
// #endregion

// #region Torma Cave
const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Fisherman_Alfie_Divergent[] = {
    { .lvl = 15, .species = SPECIES_FEEBAS },
    { .lvl = 15, .species = SPECIES_FEEBAS },
    { .lvl = 15, .species = SPECIES_FEEBAS },
    { .lvl = 15, .species = SPECIES_FEEBAS },
    { .lvl = 15, .species = SPECIES_FEEBAS },
    { .lvl = 15, .species = SPECIES_FEEBAS }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Nob_Divergent[] = {
    { .lvl = 13, .species = SPECIES_GEODUDE_A },
    { .lvl = 14, .species = SPECIES_ARON },
    { .lvl = 15, .species = SPECIES_GEODUDE_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Saul_Divergent[] = {
    { .lvl = 16, .species = SPECIES_NOSEPASS }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Wyatt_Divergent[] = {
    { .lvl = 14, .species = SPECIES_TYNAMO },
    { .lvl = 14, .species = SPECIES_MAGNEMITE }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Shane_Divergent[] = {
    { .lvl = 14, .species = SPECIES_BLITZLE },
    { .lvl = 14, .species = SPECIES_MAGNEMITE },
    { .lvl = 14, .species = SPECIES_DIGLETT_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Pokefan_Corey_Divergent[] = {
    { .lvl = 16, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Lass_Harmony_Divergent[] = {
    { .lvl = 15, .species = SPECIES_MARILL },
    { .lvl = 15, .species = SPECIES_BUTTERFREE },
};
// #endregion

// #region Route 7
const struct TrainerMonNoItemDefaultMoves sParty_Route7_CamperCarlisle_Divergent[] = {
    { .lvl = 8, .species = SPECIES_ZIGZAGOON_G },
    { .lvl = 10, .species = SPECIES_DRIFLOON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_RockerJonas_Divergent[] = {
    { .lvl = 17, .species = SPECIES_KRICKETOT },
    { .lvl = 18, .species = SPECIES_KRICKETUNE },
    { .lvl = 19, .species = SPECIES_THWACKEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_LassEden_Divergent[] = {
    { .lvl = 17, .species = SPECIES_SOLOSIS },
    { .lvl = 18, .species = SPECIES_MARILL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_HikerDanny_Divergent[] = {
    { .lvl = 18, .species = SPECIES_ANORITH },
    { .lvl = 18, .species = SPECIES_CUBONE_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_CrushGirlEden_Divergent[] = {
    { .lvl = 18, .species = SPECIES_SPRITZEE },
    { .lvl = 19, .species = SPECIES_CLEFAIRY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_PsychicIshaan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_SMOOCHUM },
    { .lvl = 19, .species = SPECIES_KADABRA },
};
// endregion

// #endregion

// #region Route 13
const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerDalton_Divergent[] = {
    { .lvl = 14, .species = SPECIES_ELEKID },
    { .lvl = 14, .species = SPECIES_MAGBY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorCharlie_Divergent[] = {
    { .lvl = 16, .species = SPECIES_BAGON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_HikerDwayne_Divergent[] = {
    { .lvl = 15, .species = SPECIES_NOSEPASS },
    { .lvl = 16, .species = SPECIES_PIGNITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BlackBeltHector_Divergent[] = {
    { .lvl = 14, .species = SPECIES_CLOBBOPUS },
    { .lvl = 14, .species = SPECIES_CLOBBOPUS },
    { .lvl = 15, .species = SPECIES_TYROGUE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_PicknickerEtie_Divergent[] = {
    { .lvl = 16, .species = SPECIES_PANPOUR },
    { .lvl = 16, .species = SPECIES_PETILIL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BeautyCandice_Divergent[] = {
    { .lvl = 28, .species = SPECIES_HAUNTER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerOwain_Divergent[] = {
    { .lvl = 26, .species = SPECIES_MEOWTH_G },
    { .lvl = 27, .species = SPECIES_ORICORIO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorBenji_Divergent[] = {
    { .lvl = 47, .species = SPECIES_SHELGON },
    { .lvl = 48, .species = SPECIES_XATU },
    { .lvl = 50, .species = SPECIES_SNORLAX },
};
// #endregion

// #region Ferrox Village
const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLaurena_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_SMOOCHUM,
        .moves = { MOVE_LICK, MOVE_COPYCAT, MOVE_SING, MOVE_ATTRACT },
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 17,
        .species = SPECIES_SHUPPET,
        .moves = { MOVE_ASTONISH, MOVE_WILLOWISP, MOVE_SPITE, MOVE_SCREECH },
        .ability = Ability_Hidden // Cursed Body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLona_Divergent[] = {
    {
        .lvl = 19,
        .species = SPECIES_BUTTERFREE,
        .moves = { MOVE_CONFUSION, MOVE_POISONPOWDER, MOVE_STUNSPORE, MOVE_SLEEPPOWDER },
        .ability = Ability_1 // Compound Eyes
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerChet_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_DEDENNE,
        .moves = { MOVE_NUZZLE, MOVE_THUNDERSHOCK, MOVE_CHARGE, MOVE_TAILWHIP },
        .ability = Ability_1 // Cheek Pouch
    },
    {
        .lvl = 18,
        .species = SPECIES_SKRELP,
        .moves = { MOVE_POISONTAIL, MOVE_ACID, MOVE_WATERGUN, MOVE_SMOKESCREEN },
        .ability = Ability_1 // Poison Point
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerVincent_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_LITWICK,
        .moves = { MOVE_ASTONISH, MOVE_CURSE, MOVE_CONFUSERAY, MOVE_WILLOWISP },
        .ability = Ability_1 // Flash Fire
    },
    {
        .lvl = 17,
        .species = SPECIES_NOSEPASS,
        .moves = { MOVE_THUNDERWAVE, MOVE_BLOCK, MOVE_ROCKTHROW, MOVE_TACKLE },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 18,
        .species = SPECIES_SKIPLOOM,
        .moves = { MOVE_LEECHSEED, MOVE_POISONPOWDER, MOVE_FAIRYWIND, MOVE_STUNSPORE },
        .ability = Ability_1 // Chlorophyll
    }
};

const struct TrainerMonItemCustomMoves sParty_FerroxGym_GymLeaderStella_Divergent[] = {
    {
        .lvl = 19,
        .species = SPECIES_SKORUPI,
        .moves = { MOVE_FELLSTINGER, MOVE_VENOSHOCK, MOVE_TOXIC, MOVE_BUGBITE },
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 19,
        .species = SPECIES_LAMPENT,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_CONFUSERAY, MOVE_EMBER },
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 20,
        .species = SPECIES_GLOOM,
        .moves = { MOVE_STUNSPORE, MOVE_SLEEPPOWDER, MOVE_GIGADRAIN, MOVE_POISONPOWDER },
        .ability = Ability_Hidden // Stench
    }
};
// #endregion

// #region Route 5
const struct TrainerMonNoItemDefaultMoves sParty_Route5_LadyFaith_Divergent[] = {
    { .lvl = 17, .species = SPECIES_APPLIN },
    { .lvl = 17, .species = SPECIES_PETILIL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_BugCatcher_Ben_Divergent[] = {
    { .lvl = 17, .species = SPECIES_DWEBBLE },
    { .lvl = 17, .species = SPECIES_DEWPIDER },
    { .lvl = 18, .species = SPECIES_BEEDRILL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Psychic_Alyssia_Divergent[] = {
    { .lvl = 18, .species = SPECIES_MUNNA },
    { .lvl = 18, .species = SPECIES_KADABRA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Breeder_Brenda_Divergent[] = {
    { .lvl = 12, .species = SPECIES_CLEFFA },
    { .lvl = 12, .species = SPECIES_MAGBY },
    { .lvl = 12, .species = SPECIES_ELEKID },
    { .lvl = 12, .species = SPECIES_SMOOCHUM },
    { .lvl = 12, .species = SPECIES_TYROGUE },
    { .lvl = 12, .species = SPECIES_MUNCHLAX },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Blackbelt_Raheem_Divergent[] = {
    { .lvl = 18, .species = SPECIES_CLOBBOPUS },
    { .lvl = 19, .species = SPECIES_MACHOP },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gambler_Dominik_Divergent[] = {
    { .lvl = 18, .species = SPECIES_ARON },
    { .lvl = 18, .species = SPECIES_TYMPOLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Lady_Juliet_Divergent[] = {
    { .lvl = 17, .species = SPECIES_STUFFUL },
    { .lvl = 17, .species = SPECIES_CLEFAIRY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gentleman_Marcus_Divergent[] = {
    { .lvl = 18, .species = SPECIES_PIDGEOTTO },
    { .lvl = 18, .species = SPECIES_QUILLADIN },
};
// #endregion

// #region Heleo Ranch
const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Burglar_Cole_Divergent[] = {
    { .lvl = 18, .species = SPECIES_TRUBBISH },
    { .lvl = 17, .species = SPECIES_PANCHAM },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Camper_Troy_Divergent[] = {
    { .lvl = 17, .species = SPECIES_LUXIO },
    { .lvl = 17, .species = SPECIES_STUNKY },
    { .lvl = 18, .species = SPECIES_STARAVIA },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Breeder_Laura_Divergent[] = {
    { .lvl = 14, .species = SPECIES_MUNNA },
    { .lvl = 14, .species = SPECIES_BOUNSWEET },
    { .lvl = 14, .species = SPECIES_CLEFFA },
    { .lvl = 14, .species = SPECIES_NATU },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Picknicker_Carly_Divergent[] = {
    { .lvl = 18, .species = SPECIES_DUCKLETT },
    { .lvl = 18, .species = SPECIES_MARACTUS },
    { .lvl = 19, .species = SPECIES_MILCERY }
};
// #endregion

// #region Route 6
const struct TrainerMonNoItemDefaultMoves sParty_Route6_Youngster_Ned_Divergent[] = {
    { .lvl = 19, .species = SPECIES_SKIPLOOM },
    { .lvl = 20, .species = SPECIES_FURRET }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_NinjaBoy_Rajan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_STUNKY },
    { .lvl = 19, .species = SPECIES_DRIFLOON },
    { .lvl = 19, .species = SPECIES_SPINARAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Hiker_Romero_Divergent[] = {
    { .lvl = 19, .species = SPECIES_NOSEPASS },
    { .lvl = 19, .species = SPECIES_DWEBBLE },
    { .lvl = 20, .species = SPECIES_ARON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Estevan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_KADABRA },
    { .lvl = 20, .species = SPECIES_DEERLING_WINTER },
    { .lvl = 21, .species = SPECIES_DEINO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Engineer_Harry_Divergent[] = {
    { .lvl = 20, .species = SPECIES_MAGNEMITE },
    { .lvl = 20, .species = SPECIES_ELEKID },
    { .lvl = 20, .species = SPECIES_DEDENNE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gambler_Mick_Divergent[] = {
    { .lvl = 24, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Fisherman_Taylor_Divergent[] = {
    { .lvl = 20, .species = SPECIES_KRABBY },
    { .lvl = 20, .species = SPECIES_STARYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Nurse_Leanne_Divergent[] = {
    { .lvl = 20, .species = SPECIES_BRAIXEN },
    { .lvl = 20, .species = SPECIES_AUDINO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Dante_Divergent[] = {
    { .lvl = 28, .species = SPECIES_DEWOTT },
    { .lvl = 28, .species = SPECIES_KLEFKI },
    { .lvl = 28, .species = SPECIES_LINOONE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BugCatcher_Billie_Divergent[] = {
    { .lvl = 30, .species = SPECIES_LEAVANNY },
    { .lvl = 30, .species = SPECIES_PINSIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gentleman_Lincoln_Divergent[] = {
    { .lvl = 28, .species = SPECIES_GROWLITHE },
    { .lvl = 29, .species = SPECIES_SPHEAL },
    { .lvl = 29, .species = SPECIES_QUILAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BlackBelt_Raphael_Divergent[] = {
    { .lvl = 30, .species = SPECIES_PIGNITE },
    { .lvl = 31, .species = SPECIES_MACHOKE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Lass_Anna_Divergent[] = {
    { .lvl = 29, .species = SPECIES_TYROGUE },
    { .lvl = 29, .species = SPECIES_DIGGERSBY },
    { .lvl = 29, .species = SPECIES_LILLIGANT },
    { .lvl = 30, .species = SPECIES_SPRITZEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Swimmer_Danika_Divergent[] = {
    { .lvl = 48, .species = SPECIES_SKRELP },
    { .lvl = 48, .species = SPECIES_AZUMARILL },
    { .lvl = 50, .species = SPECIES_DRAGALGE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SrAndJr_SueAndKat_Divergent[] = {
    { .lvl = 29, .species = SPECIES_PHANPY },
    { .lvl = 30, .species = SPECIES_ELECTRODE },
    { .lvl = 29, .species = SPECIES_GASTLY },
    { .lvl = 30, .species = SPECIES_GLOOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_HikerDarryl_Divergent[] = {
    { .lvl = 55, .species = SPECIES_GRAVELER_A },
    { .lvl = 55, .species = SPECIES_SEISMITOAD },
    { .lvl = 56, .species = SPECIES_AERODACTYL },
    { .lvl = 56, .species = SPECIES_HAWLUCHA }
};
// #endregion

// #region Heleo City
const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_PsychicBianca_Divergent[] = { // Unchanged
    { .lvl = 1, .species = SPECIES_BULBASAUR },
    { .lvl = 1, .species = SPECIES_CHARMANDER },
    { .lvl = 1, .species = SPECIES_SQUIRTLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_SupernerdGalen_Divergent[] = {
    { .lvl = 1, .species = SPECIES_MACHOP },
    { .lvl = 1, .species = SPECIES_PIDGEY },
    { .lvl = 1, .species = SPECIES_IMPIDIMP }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_CoolTrainerJet_Divergent[] = {
    { .lvl = 1, .species = SPECIES_VANILLITE },
    { .lvl = 1, .species = SPECIES_SOLOSIS },
    { .lvl = 1, .species = SPECIES_KRICKETUNE }
};

const struct TrainerMonNoItemCustomMoves sParty_HeleoCityGym_SwimmerTessa_Divergent[] = {
    {
        .lvl = 25,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_RAINDANCE, MOVE_SUNNYDAY, MOVE_HAIL, MOVE_WEATHERBALL },
        .ability = Ability_2 // Technician
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerByron_Divergent[] = {
    {
        .lvl = 23,
        .species = SPECIES_NINETALES,
        .moves = { MOVE_CONFUSERAY, MOVE_INCINERATE, MOVE_QUICKATTACK, MOVE_SAFEGUARD },
        .heldItem = ITEM_HEAT_ROCK,
        .ability = Ability_Hidden // Drought
    },
    {
        .lvl = 23,
        .species = SPECIES_DEERLING_SUMMER,
        .moves = { MOVE_GROWTH, MOVE_SYNTHESIS, MOVE_BULLETSEED, MOVE_DOUBLEKICK },
        .ability = Ability_1 // Cholorophyll
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerDanette_Divergent[] = {
    {
        .lvl = 22,
        .species = SPECIES_SNOVER,
        .moves = { MOVE_ICYWIND, MOVE_RAZORLEAF, MOVE_AURORAVEIL, MOVE_AVALANCHE },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 23,
        .species = SPECIES_SANDSHREW_A,
        .moves = { MOVE_METALCLAW, MOVE_RAPIDSPIN, MOVE_FURYCUTTER, MOVE_DEFENSECURL },
        .ability = Ability_Hidden // Slush Rush
    },
    {
        .lvl = 23,
        .species = SPECIES_SEEL,
        .moves = { MOVE_HEADBUTT, MOVE_WATERGUN, MOVE_ICESHARD, MOVE_HAIL },
        .ability = Ability_Hidden // Ice Body
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerMaisey_Divergent[] = {
    {
        .lvl = 23,
        .species = SPECIES_SILICOBRA,
        .moves = { MOVE_WRAP, MOVE_BULLDOZE, MOVE_HEADBUTT, MOVE_POISONTAIL },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Spit
    },
    {
        .lvl = 23,
        .species = SPECIES_NOSEPASS,
        .moves = { MOVE_THUNDERWAVE, MOVE_ROCKSLIDE, MOVE_SANDTOMB, MOVE_ROLLOUT },
        .ability = Ability_Hidden // Sand Force
    },
    {
        .lvl = 23,
        .species = SPECIES_DIGLETT_A,
        .moves = { MOVE_METALCLAW, MOVE_BULLDOZE, MOVE_SUCKERPUNCH, MOVE_SANDSTORM },
        .ability = Ability_1 // Sand Veil
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine_Divergent[] = {
    {
        .lvl = 25,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_BUBBLEBEAM, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 24,
        .species = SPECIES_MAGNEMITE,
        .moves = { MOVE_THUNDER, MOVE_GYROBALL, MOVE_MAGNETRISE, MOVE_SUPERSONIC },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 26,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_CONFUSION, MOVE_ATTRACT, MOVE_FAKETEARS },
        .ability = Ability_Hidden // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine2_Divergent[] = {
    {
        .lvl = 31,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_SURF, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 31,
        .species = SPECIES_MAGNETON,
        .moves = { MOVE_THUNDER, MOVE_GYROBALL, MOVE_MAGNETRISE, MOVE_TRIATTACK },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 33,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_CONFUSION, MOVE_ATTRACT, MOVE_FAKETEARS },
        .ability = Ability_Hidden // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine3_Divergent[] = {
    {
        .lvl = 39,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_SURF, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 40,
        .species = SPECIES_MAGNETON,
        .moves = { MOVE_THUNDER, MOVE_FLASHCANNON, MOVE_MAGNETRISE, MOVE_TRIATTACK },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 40,
        .species = SPECIES_ARMALDO,
        .moves = { MOVE_CRUSHCLAW, MOVE_ROCKBLAST, MOVE_AQUATAIL, MOVE_BRINE },
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 41,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_PSYCHIC, MOVE_ATTRACT, MOVE_FAKETEARS },
        .ability = Ability_Hidden // Dry Skin
    }
};
// #endregion

// #region Route 8
const struct TrainerMonNoItemDefaultMoves sParty_Route8_Camper_Drew_Divergent[] = {
    { .lvl = 25, .species = SPECIES_GULPIN },
    { .lvl = 25, .species = SPECIES_DIGGERSBY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyZeke_Divergent[] = {
    { .lvl = 23, .species = SPECIES_KRICKETUNE },
    { .lvl = 24, .species = SPECIES_FROGADIER },
    { .lvl = 25, .species = SPECIES_HONEDGE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SuperNerdSaul_Divergent[] = {
    { .lvl = 24, .species = SPECIES_TANGELA },
    { .lvl = 24, .species = SPECIES_PORYGON },
    { .lvl = 25, .species = SPECIES_KLEFKI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_RockerParker_Divergent[] = {
    { .lvl = 25, .species = SPECIES_ELEKID },
    { .lvl = 26, .species = SPECIES_MARACTUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ParasolLadyAnnabelle_Divergent[] = {
    { .lvl = 28, .species = SPECIES_GRANBULL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ChannelerMorgan_Divergent[] = {
    { .lvl = 25, .species = SPECIES_SHUPPET },
    { .lvl = 25, .species = SPECIES_SINISTEA },
    { .lvl = 26, .species = SPECIES_SHUPPET }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_BugCatcherArnold_Divergent[] = {
    { .lvl = 24, .species = SPECIES_BEEDRILL },
    { .lvl = 26, .species = SPECIES_ARIADOS },
    { .lvl = 26, .species = SPECIES_WIMPOD }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_LassLilian_Divergent[] = {
    { .lvl = 26, .species = SPECIES_PETILIL },
    { .lvl = 27, .species = SPECIES_BAYLEEF }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyNatto_Divergent[] = {
    { .lvl = 24, .species = SPECIES_SKORUPI },
    { .lvl = 25, .species = SPECIES_DWEBBLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberMicah_Divergent[] = {
    { .lvl = 25, .species = SPECIES_CLEFFA },
    { .lvl = 25, .species = SPECIES_TYROGUE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberNancy_Divergent[] = {
    { .lvl = 25, .species = SPECIES_DRIFLOON },
    { .lvl = 25, .species = SPECIES_SKIPLOOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerMaya_Divergent[] = {
    { .lvl = 26, .species = SPECIES_AZUMARILL },
    { .lvl = 26, .species = SPECIES_MARILL },
    { .lvl = 26, .species = SPECIES_AZUMARILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerHuey_Divergent[] = {
    { .lvl = 47, .species = SPECIES_SKRELP },
    { .lvl = 48, .species = SPECIES_PRIMARINA },
    { .lvl = 48, .species = SPECIES_DRAGALGE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerBob_Divergent[] = {
    { .lvl = 48, .species = SPECIES_WHISCASH },
    { .lvl = 48, .species = SPECIES_CRAMORANT },
    { .lvl = 51, .species = SPECIES_SWANNA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_CoolTrainerHarriet_Divergent[] = {
    { .lvl = 50, .species = SPECIES_DRAPION },
    { .lvl = 52, .species = SPECIES_PUPITAR },
    { .lvl = 52, .species = SPECIES_GOLEM_A }
};
// #endregion

// #region Forgotten Manse
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_ChannelerMona_Divergent[] = {
    { .lvl = 25, .species = SPECIES_KADABRA },
    { .lvl = 25, .species = SPECIES_SHUPPET },
    { .lvl = 25, .species = SPECIES_SINISTEA }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BurglarChad_Divergent[] = {
    { .lvl = 27, .species = SPECIES_TRUBBISH },
    { .lvl = 27, .species = SPECIES_GROWLITHE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_NurseLucy_Divergent[] = {
    { .lvl = 25, .species = SPECIES_AUDINO }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_BeautyLulu_Divergent[] = {
    { .lvl = 26, .species = SPECIES_SOLOSIS },
    { .lvl = 27, .species = SPECIES_BRAIXEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_ChannelerEsther_Divergent[] = {
    { .lvl = 26, .species = SPECIES_BALTOY },
    { .lvl = 26, .species = SPECIES_JYNX }
};

const struct TrainerMonNoItemCustomMoves sParty_ForgottenManse_1F_SuperNerdAustin_Divergent[] = {
    {
        .lvl = 27,
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 27,
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Imposter
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_BurglarJacques_Divergent[] = {
    { .lvl = 25, .species = SPECIES_PANCHAM },
    { .lvl = 25, .species = SPECIES_PANCHAM },
    { .lvl = 26, .species = SPECIES_SKORUPI },
    { .lvl = 26, .species = SPECIES_LARVITAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_PsychicCorbin_Divergent[] = {
    { .lvl = 27, .species = SPECIES_ALAKAZAM }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_BurglarBarry_Divergent[] = {
    { .lvl = 27, .species = SPECIES_PANSAGE },
    { .lvl = 28, .species = SPECIES_PANPOUR },
    { .lvl = 29, .species = SPECIES_PANSEAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_YoungsterChester_Divergent[] = {
    { .lvl = 27, .species = SPECIES_DREEPY },
    { .lvl = 27, .species = SPECIES_DREEPY }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_ChannelerElaine_Divergent[] = {
    { .lvl = 32, .species = SPECIES_INDEEDEE_FEMALE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_SuperNerdGlenn_Divergent[] = {
    { .lvl = 27, .species = SPECIES_MEOWTH_G },
    { .lvl = 27, .species = SPECIES_MEOWTH }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_BurglarPavle_Divergent[] = {
    { .lvl = 25, .species = SPECIES_STUNKY },
    { .lvl = 31, .species = SPECIES_ELECTRODE }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_PsychicNoelle_Divergent[] = {
    { .lvl = 27, .species = SPECIES_NATU },
    { .lvl = 28, .species = SPECIES_SWOOBAT },
    { .lvl = 28, .species = SPECIES_BRAIXEN },
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_ChannelerSana_Divergent[] = {
    { .lvl = 30, .species = SPECIES_MORGREM },
    { .lvl = 30, .species = SPECIES_MAROWAK_A }
};
// #endregion

// #region Daimyn Factory
const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BirdkeeperMarius_Divergent[] = {
    { .lvl = 34, .species = SPECIES_STARAPTOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_RockerBenson_Divergent[] = {
    { .lvl = 29, .species = SPECIES_ELECTRIKE },
    { .lvl = 31, .species = SPECIES_ELECTABUZZ }
};

const struct TrainerMonItemCustomMoves sParty_DaimynFactory_LassNatalie_Divergent[] = {
    {
        .lvl = 31,
        .species = SPECIES_GROTLE,
        .moves = { MOVE_LEECHSEED, MOVE_CURSE, MOVE_SANDTOMB, MOVE_RAZORLEAF },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 31,
        .species = SPECIES_POLTEAGEIST,
        .moves = { MOVE_STRENGTHSAP, MOVE_HEX, MOVE_WILLOWISP, MOVE_MEGADRAIN },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Cursed Body
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerJamison_Divergent[] = {
    { .lvl = 29, .species = SPECIES_DIGLETT_A },
    { .lvl = 28, .species = SPECIES_ZEBSTRIKA },
    { .lvl = 30, .species = SPECIES_VOLTORB }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_HikerPercy_Divergent[] = {
    { .lvl = 31, .species = SPECIES_MEOWTH_G },
    { .lvl = 31, .species = SPECIES_ONIX },
    { .lvl = 31, .species = SPECIES_GRAVELER_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BlackbeltRory_Divergent[] = {
    { .lvl = 33, .species = SPECIES_MAKUHITA },
    { .lvl = 34, .species = SPECIES_HITMONCHAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerWilson_Divergent[] = {
    { .lvl = 32, .species = SPECIES_TOGEDEMARU },
    { .lvl = 34, .species = SPECIES_MAGNETON }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_YoungsterNate_Divergent[] = {
    { .lvl = 32, .species = SPECIES_SEALEO },
    { .lvl = 34, .species = SPECIES_LAIRON }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_PicknickerShanna_Divergent[] = {
    { .lvl = 32, .species = SPECIES_NUMEL },
    { .lvl = 34, .species = SPECIES_APPLETUN }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerKliff_Divergent[] = {
    { .lvl = 32, .species = SPECIES_ELECTRIKE },
    { .lvl = 34, .species = SPECIES_PORYGON },
    { .lvl = 34, .species = SPECIES_MANECTRIC }
};
// #endregion

// #region Daimyn City
const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_YoungsterJacob_Divergent[] = {
    {
        .lvl = 10,
        .species = SPECIES_SILICOBRA,
        .moves = { MOVE_BRUTALSWING, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Spit
    },
    {
        .lvl = 1,
        .species = SPECIES_ARON,
        .moves = { MOVE_ENDEAVOR, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_SHELL_BELL,
        .ability = Ability_1 // Sturdy
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_PokefanKanesha_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_DOUBLADE,
        .moves = { MOVE_POWERTRICK, MOVE_SHADOWSNEAK, MOVE_PSYCHOCUT, MOVE_IRONDEFENSE },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_Hidden // No Guard
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_BeautyEmilie_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_HAUNTER,
        .moves = { MOVE_PERISHSONG, MOVE_SPITE, MOVE_CURSE, MOVE_HEX },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 30,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SNARL, MOVE_PERISHSONG, MOVE_DETECT, MOVE_DOUBLETEAM },
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_BeautyLeanne_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_CLEFAIRY,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 30,
        .species = SPECIES_POLIWHIRL,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Damp
    },
    {
        .lvl = 30,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_ChannelerRosita_Divergent[] = {
    {
        .lvl = 28,
        .species = SPECIES_EXEGGCUTE_A,
        .moves = { MOVE_TRICKROOM, MOVE_HYPNOSIS, MOVE_LEECHSEED, MOVE_REFLECT },
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 29,
        .species = SPECIES_NUMEL,
        .moves = { MOVE_EARTHPOWER, MOVE_CURSE, MOVE_LAVAPLUME, MOVE_AMNESIA },
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 28,
        .species = SPECIES_DEWOTT,
        .moves = { MOVE_RETALIATE, MOVE_FURYCUTTER, MOVE_AQUAJET, MOVE_RAZORSHELL },
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 28,
        .species = SPECIES_AROMATISSE,
        .moves = { MOVE_TRICKROOM, MOVE_DAZZLINGGLEAM, MOVE_FAKETEARS, MOVE_WISH },
        .ability = Ability_1 // Healer
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_GamblerChuck_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_JUMPLUFF,
        .moves = { MOVE_ACROBATICS, MOVE_MEGADRAIN, MOVE_UTURN, MOVE_POISONPOWDER },
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 30,
        .species = SPECIES_GROWLITHE,
        .moves = { MOVE_RETALIATE, MOVE_ROAR, MOVE_BITE, MOVE_FLAMEWHEEL },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 31,
        .species = SPECIES_RABOOT,
        .moves = { MOVE_ELECTROBALL, MOVE_FLAMECHARGE, MOVE_DOUBLEKICK, MOVE_GROWL },
        .ability = Ability_1 // Blaze
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_BurglarDexter_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_AZUMARILL,
        .moves = { MOVE_BELLYDRUM, MOVE_AQUAJET, MOVE_NONE, MOVE_NONE },
        .ability = Ability_2 // Huge Power
    },
    {
        .lvl = 30,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_REST, MOVE_SLEEPTALK, MOVE_LICK, MOVE_BITE },
        .ability = Ability_1 // Immunity
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance_Divergent[] = {
    {
        .lvl = 31,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_THUNDERWAVE, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 31,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_SHOCKWAVE, MOVE_FIREFANG, MOVE_THUNDERWAVE },
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 33,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_RAZORSHELL, MOVE_SUCKERPUNCH, MOVE_SLASH },
        .ability = Ability_1 // Emergency Exit
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance2_Divergent[] = {
    {
        .lvl = 39,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_THUNDERWAVE, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 40,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_DISCHARGE, MOVE_FIREFANG, MOVE_THUNDERWAVE },
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 40,
        .species = SPECIES_INCINEROAR,
        .moves = { MOVE_PARTINGSHOT, MOVE_KNOCKOFF, MOVE_FAKEOUT, MOVE_FLAMETHROWER },
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 41,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_RAZORSHELL, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .ability = Ability_1 // Emergency Exit
    }
};
// #endregion

// #region Route 9
const struct TrainerMonNoItemDefaultMoves sParty_Route9_Collector_Marshall_Divergent[] = {
    { .lvl = 30, .species = SPECIES_ALCREMIE_BERRY },
    { .lvl = 31, .species = SPECIES_ALCREMIE_CLOVER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Andrea_Divergent[] = {
    { .lvl = 31, .species = SPECIES_PINSIR },
    { .lvl = 31, .species = SPECIES_MAGMAR },
    { .lvl = 31, .species = SPECIES_IVYSAUR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Fisherman_Yusuf_Divergent[] = {
    { .lvl = 30, .species = SPECIES_CRAMORANT },
    { .lvl = 30, .species = SPECIES_BARBOACH },
};

const struct TrainerMonNoItemCustomMoves sParty_Route9_Gentleman_Gavin_Divergent[] = {
    {
        .lvl = 31,
        .species = SPECIES_RHYHORN,
        .moves = { MOVE_BULLDOZE, MOVE_ROCKBLAST, MOVE_STOMP, MOVE_TAILWHIP },
        .ability = Ability_1 // Lightning Rod
    },
    {
        .lvl = 31,
        .species = SPECIES_ARAQUANID,
        .moves = { MOVE_WIDEGUARD, MOVE_BUBBLEBEAM, MOVE_CRUNCH, MOVE_HEADBUTT },
        .ability = Ability_1 // Water Bubble
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_NinjaBoy_Ayrton_Divergent[] = {
    { .lvl = 29, .species = SPECIES_BAGON },
    { .lvl = 29, .species = SPECIES_WIMPOD },
    { .lvl = 31, .species = SPECIES_SWOOBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Breeder_Talia_Divergent[] = {
    { .lvl = 28, .species = SPECIES_STUFFUL },
    { .lvl = 29, .species = SPECIES_ODDISH },
    { .lvl = 30, .species = SPECIES_GLOOM },
    { .lvl = 30, .species = SPECIES_AIPOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Picknicker_Zoe_Divergent[] = {
    { .lvl = 31, .species = SPECIES_BUTTERFREE },
    { .lvl = 32, .species = SPECIES_GROVYLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Kingsley_Divergent[] = {
    { .lvl = 33, .species = SPECIES_DRAMPA },
    { .lvl = 33, .species = SPECIES_MILOTIC },
    { .lvl = 34, .species = SPECIES_MURKROW },
};
// #endregion

// #region Route 10
const struct TrainerMonNoItemDefaultMoves sParty_Route10_PsychicDarius_Divergent[] = {
    { .lvl = 29, .species = SPECIES_DUOSION },
    { .lvl = 30, .species = SPECIES_JYNX },
    { .lvl = 30, .species = SPECIES_XATU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_BirdKeeperMario_Divergent[] = {
    { .lvl = 30, .species = SPECIES_ORICORIO_Y },
    { .lvl = 30, .species = SPECIES_STARAVIA },
    { .lvl = 30, .species = SPECIES_MURKROW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_GamblerDarren_Divergent[] = {
    { .lvl = 32, .species = SPECIES_DONPHAN },
    { .lvl = 32, .species = SPECIES_DITTO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_ParasolLadyGwen_Divergent[] = {
    { .lvl = 34, .species = SPECIES_LILLIGANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_CamperJackson_Divergent[] = {
    { .lvl = 32, .species = SPECIES_PONYTA },
    { .lvl = 34, .species = SPECIES_CHESNAUGHT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_RockerBert_Divergent[] = {
    { .lvl = 31, .species = SPECIES_THWACKEY },
    { .lvl = 31, .species = SPECIES_ROTOM },
    { .lvl = 33, .species = SPECIES_MARACTUS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerAlberto_Divergent[] = {
    { .lvl = 47, .species = SPECIES_WARTORTLE },
    { .lvl = 47, .species = SPECIES_KRABBY },
    { .lvl = 48, .species = SPECIES_SKRELP },
    { .lvl = 48, .species = SPECIES_KINGLER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerRosie_Divergent[] = {
    { .lvl = 52, .species = SPECIES_WISHIWASHI },
    { .lvl = 53, .species = SPECIES_SIMIPOUR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerDoug_Divergent[] = {
    { .lvl = 49, .species = SPECIES_POLIWHIRL },
    { .lvl = 50, .species = SPECIES_SWANNA },
    { .lvl = 50, .species = SPECIES_BLASTOISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_HikerHarley_Divergent[] = {
    { .lvl = 30, .species = SPECIES_GRAVELER_A },
    { .lvl = 30, .species = SPECIES_MACHOKE },
    { .lvl = 32, .species = SPECIES_LAIRON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_BlackbeltXavier_Divergent[] = {
    { .lvl = 31, .species = SPECIES_MONFERNO },
    { .lvl = 32, .species = SPECIES_MACHAMP },
};

// #endregion

// #region Route 11 South
const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Ross_Divergent[] = {
    { .lvl = 33, .species = SPECIES_MORGREM },
    { .lvl = 34, .species = SPECIES_DRIFBLIM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Greta_Divergent[] = {
    { .lvl = 32, .species = SPECIES_SKORUPI },
    { .lvl = 33, .species = SPECIES_WOOBAT },
    { .lvl = 33, .species = SPECIES_SWOOBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Nellie_Divergent[] = {
    { .lvl = 31, .species = SPECIES_DUOSION },
    { .lvl = 31, .species = SPECIES_DEINO },
    { .lvl = 32, .species = SPECIES_STUNKY },
    { .lvl = 33, .species = SPECIES_STUNKY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Helga_Divergent[] = {
    { .lvl = 34, .species = SPECIES_ELECTABUZZ },
    { .lvl = 35, .species = SPECIES_SWALOT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Kareem_Divergent[] = {
    { .lvl = 33, .species = SPECIES_LAMPENT },
    { .lvl = 33, .species = SPECIES_GLOOM },
    { .lvl = 35, .species = SPECIES_VILEPLUME },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Chung_Divergent[] = {
    { .lvl = 35, .species = SPECIES_PANCHAM },
    { .lvl = 35, .species = SPECIES_GOLETT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Lass_Tabitha_Divergent[] = {
    { .lvl = 33, .species = SPECIES_STARYU },
    { .lvl = 34, .species = SPECIES_MANECTRIC },
    { .lvl = 34, .species = SPECIES_BELLOSSOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_CrushGirl_Alisa_Divergent[] = {
    { .lvl = 36, .species = SPECIES_HARIYAMA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Engineer_Dale_Divergent[] = {
    { .lvl = 35, .species = SPECIES_VOLTORB },
    { .lvl = 35, .species = SPECIES_ELECTRODE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Collector_Orville_Divergent[] = {
    { .lvl = 34, .species = SPECIES_EISCUE },
    { .lvl = 34, .species = SPECIES_PORYGON },
    { .lvl = 35, .species = SPECIES_MUSHARNA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoClancy_Divergent[] = {
    { .lvl = 35, .species = SPECIES_GOLETT },
    { .lvl = 35, .species = SPECIES_GRANBULL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoEna_Divergent[] = {
    { .lvl = 36, .species = SPECIES_ARIADOS },
    { .lvl = 36, .species = SPECIES_LURANTIS },
};

const struct TrainerMonNoItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald_Divergent[] = {
    {
        .lvl = 35,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYBEAM, MOVE_THUNDERWAVE, MOVE_SHADOWBALL, MOVE_ICYWIND },
        .ability = Ability_2 // Download
    },
    {
        .lvl = 35,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_BRICKBREAK, MOVE_SUCKERPUNCH, MOVE_RAPIDSPIN },
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 36,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 37,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_ENDEAVOR },
        .ability = Ability_1 // Water Absorb
    }
};
// #endregion

// #region Hesson Pass
const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_HikerLuke_Divergent[] = {
    { .lvl = 37, .species = SPECIES_GOLEM_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_ScientistHarvey_Divergent[] = {
    { .lvl = 34, .species = SPECIES_PORYGON },
    { .lvl = 34, .species = SPECIES_DURANT },
    { .lvl = 35, .species = SPECIES_CLAYDOL }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_PsychicKimiko_Divergent[] = {
    { .lvl = 57, .species = SPECIES_MEDICHAM },
    { .lvl = 57, .species = SPECIES_MORGREM },
    { .lvl = 59, .species = SPECIES_ALAKAZAM }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CoolTrainerColt_Divergent[] = {
    { .lvl = 58, .species = SPECIES_CRYOGONAL },
    { .lvl = 58, .species = SPECIES_STARAPTOR },
    { .lvl = 60, .species = SPECIES_METAGROSS }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_BlackbeltHaytham_Divergent[] = {
    { .lvl = 35, .species = SPECIES_HITMONTOP },
    { .lvl = 36, .species = SPECIES_BLAZIKEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CollectorZeus_Divergent[] = {
    { .lvl = 57, .species = SPECIES_MAROWAK_A },
    { .lvl = 57, .species = SPECIES_MAROWAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_NurseMina_Divergent[] = {
    { .lvl = 55, .species = SPECIES_CLEFABLE },
    { .lvl = 57, .species = SPECIES_ALCREMIE_STAR },
    { .lvl = 59, .species = SPECIES_AUDINO }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_GentlemanGordy_Divergent[] = {
    { .lvl = 57, .species = SPECIES_ARCANINE },
    { .lvl = 58, .species = SPECIES_DOUBLADE }
};
// #endregion

// #region Route 11 North
const struct TrainerMonNoItemCustomMoves sParty_Route11North_PainterIsobel_Divergent[] = {
    {
        .lvl = 35,
        .species = SPECIES_IVYSAUR,
        .moves = { MOVE_SYNTHESIS, MOVE_SWEETSCENT, MOVE_TAKEDOWN, MOVE_SEEDBOMB },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 36,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_SHELLSMASH, MOVE_EXPLOSION, MOVE_DRAINPUNCH, MOVE_PROTECT },
        .ability = Ability_Random_1_2
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanClint_Divergent[] = {
    { .lvl = 35, .species = SPECIES_FEEBAS },
    { .lvl = 35, .species = SPECIES_WARTORTLE },
    { .lvl = 36, .species = SPECIES_QUAGSIRE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ChanellerKatya_Divergent[] = {
    { .lvl = 36, .species = SPECIES_BANETTE },
    { .lvl = 38, .species = SPECIES_HAUNTER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_RockerNathaniel_Divergent[] = {
    { .lvl = 36, .species = SPECIES_RILLABOOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_NinjaBoyYao_Divergent[] = {
    { .lvl = 34, .species = SPECIES_SKRELP },
    { .lvl = 34, .species = SPECIES_ARIADOS },
    { .lvl = 36, .species = SPECIES_GRENINJA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ParaoslLadyTina_Divergent[] = {
    { .lvl = 34, .species = SPECIES_SEEL },
    { .lvl = 35, .species = SPECIES_BRAIXEN },
    { .lvl = 35, .species = SPECIES_LILLIGANT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanJonah_Divergent[] = {
    { .lvl = 36, .species = SPECIES_BARBOACH },
    { .lvl = 38, .species = SPECIES_WHISCASH }
};

// #endregion

// #region Laplaz Town
const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_BirdKeeperToby_Divergent[] = {
    { .lvl = 1, .species = SPECIES_PIDGEOTTO },
    { .lvl = 1, .species = SPECIES_DUCKLETT },
    { .lvl = 1, .species = SPECIES_NATU }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CollectorDirk_Divergent[] = {
    { .lvl = 1, .species = SPECIES_BALTOY },
    { .lvl = 1, .species = SPECIES_EELEKTRIK },
    { .lvl = 1, .species = SPECIES_HAUNTER }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CoolTrainerVanessa_Divergent[] = {
    { .lvl = 1, .species = SPECIES_DRIFLOON },
    { .lvl = 1, .species = SPECIES_SKIPLOOM },
    { .lvl = 1, .species = SPECIES_ROTOM }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_PsychicJeremiah_Divergent[] = {
    {
        .lvl = 38,
        .species = SPECIES_MACHOKE,
        .moves = { MOVE_BULKUP, MOVE_ROCKSMASH, MOVE_POWERUPPUNCH, MOVE_BRUTALSWING },
        .ability = Ability_Hidden // Steadfast
    },
    {
        .lvl = 38,
        .species = SPECIES_ELECTRODE,
        .moves = { MOVE_ELECTROBALL, MOVE_AGILITY, MOVE_CHARGE, MOVE_SWIFT },
        .ability = Ability_2 // Static
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_PicnickerExie_Divergent[] = {
    {
        .lvl = 37,
        .species = SPECIES_TORRACAT,
        .moves = { MOVE_FAKEOUT, MOVE_SWORDSDANCE, MOVE_FLAMECHARGE, MOVE_PARTINGSHOT },
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 37,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_SWAGGER, MOVE_FOULPLAY, MOVE_REFLECT, MOVE_SUBSTITUTE },
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 37,
        .species = SPECIES_ARIADOS,
        .moves = { MOVE_STICKYWEB, MOVE_SHADOWSNEAK, MOVE_NIGHTSLASH, MOVE_SWORDSDANCE },
        .ability = Ability_1 // Swarm
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ChannelerVirginia_Divergent[] = {
    {
        .lvl = 37,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_COTTONGUARD, MOVE_DRAGONDANCE, MOVE_DRAGONBREATH, MOVE_PLUCK },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 37,
        .species = SPECIES_SERPERIOR,
        .moves = { MOVE_COIL, MOVE_LEAFBLADE, MOVE_SLAM, MOVE_DRAGONTAIL },
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 38,
        .species = SPECIES_LAIRON,
        .moves = { MOVE_IRONDEFENSE, MOVE_HEAVYSLAM, MOVE_ROCKTOMB, MOVE_HEADBUTT },
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_LadyNisha_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_DEFENSECURL, MOVE_ROLLOUT, MOVE_SCREECH, MOVE_CRUNCH },
        .ability = Ability_2 // Thick Fat
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ScientistKent_Divergent[] = {
    {
        .lvl = 37,
        .species = SPECIES_VANILLISH,
        .moves = { MOVE_ICYWIND, MOVE_PROTECT, MOVE_ACIDARMOR, MOVE_SELFDESTRUCT },
        .ability = Ability_Hidden // Weak Armor
    },
    {
        .lvl = 37,
        .species = SPECIES_CRUSTLE,
        .moves = { MOVE_SHELLSMASH, MOVE_ROCKSLIDE, MOVE_BUGBITE, MOVE_DIG },
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 37,
        .species = SPECIES_DARTRIX,
        .moves = { MOVE_NASTYPLOT, MOVE_AIRCUTTER, MOVE_MAGICALLEAF, MOVE_KNOCKOFF },
        .ability = Ability_Hidden // Long Reach
    },
    {
        .lvl = 38,
        .species = SPECIES_STARMIE,
        .moves = { MOVE_PSYCHIC, MOVE_MINIMIZE, MOVE_POWERGEM, MOVE_SWIFT },
        .ability = Ability_2 // Natural Cure
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_RockerTrent_Divergent[] = {
    {
        .lvl = 38,
        .species = SPECIES_SWOOBAT,
        .moves = { MOVE_AMNESIA, MOVE_CALMMIND, MOVE_AIRCUTTER, MOVE_ASSURANCE },
        .ability = Ability_Hidden // Simple
    },
    {
        .lvl = 38,
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_STOCKPILE, MOVE_TAILWIND, MOVE_STRENGTHSAP, MOVE_SHADOWBALL },
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 39,
        .species = SPECIES_QUILLADIN,
        .moves = { MOVE_BELLYDRUM, MOVE_NEEDLEARM, MOVE_BITE, MOVE_LEECHSEED },
        .ability = Ability_1 // Overgrow
    }
};

const struct TrainerMonItemCustomMoves sParty_LaplazTownGym_LeaderCasey_Divergent[] = {
    {
        .lvl = 39,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_SPORE, MOVE_ACUPRESSURE, MOVE_SUBSTITUTE, MOVE_BATONPASS },
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 40,
        .species = SPECIES_PANCHAM,
        .moves = { MOVE_BULKUP, MOVE_DRAINPUNCH, MOVE_ICEPUNCH, MOVE_BODYSLAM },
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 40,
        .species = SPECIES_MUSHARNA,
        .moves = { MOVE_CALMMIND, MOVE_STOREDPOWER, MOVE_PSYCHIC, MOVE_MOONBLAST },
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 41,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NASTYPLOT, MOVE_DARKPULSE, MOVE_HEATWAVE, MOVE_AIRCUTTER },
        .ability = Ability_2 // Super Luck
    }
};

// #endregion

// #region Peradon Forest
const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_PokefanClark_Divergent[] = {
    { .lvl = 38, .species = SPECIES_TOGEDEMARU },
    { .lvl = 38, .species = SPECIES_QUAGSIRE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CollectorFernando_Divergent[] = {
    { .lvl = 39, .species = SPECIES_SHELGON },
    { .lvl = 39, .species = SPECIES_NINETALES_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BugCatcherLyle_Divergent[] = {
   { .lvl = 37, .species = SPECIES_ARIADOS },
   { .lvl = 38, .species = SPECIES_SCYTHER },
   { .lvl = 38, .species = SPECIES_KRICKETUNE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BeautyErica_Divergent[] = {
    { .lvl = 40, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemCustomMoves sParty_PeradonForest_PainterSheena_Divergent[] = {
    {
        .lvl = 38,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_QUIVERDANCE, MOVE_GIGADRAIN, MOVE_ANCIENTPOWER, MOVE_PROTECT },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 38,
        .species = SPECIES_BELLOSSOM,
        .moves = { MOVE_PETALBLIZZARD, MOVE_MOONLIGHT, MOVE_POISONPOWDER, MOVE_QUIVERDANCE },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CamperRupert_Divergent[] = {
    { .lvl = 40, .species = SPECIES_VENUSAUR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ScientistSean_Divergent[] = {
    { .lvl = 39, .species = SPECIES_MAGNETON },
    { .lvl = 39, .species = SPECIES_DRAMPA },
    { .lvl = 39, .species = SPECIES_METANG },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RockerRaphael_Divergent[] = {
    { .lvl = 40, .species = SPECIES_MARACTUS },
    { .lvl = 40, .species = SPECIES_RILLABOOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ChannelerRenee_Divergent[] = {
    { .lvl = 37, .species = SPECIES_GASTLY },
    { .lvl = 37, .species = SPECIES_DUOSION },
    { .lvl = 38, .species = SPECIES_MORGREM },
    { .lvl = 38, .species = SPECIES_GENGAR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BlackbeltBrad_Divergent[] = {
    { .lvl = 39, .species = SPECIES_MEDICHAM },
    { .lvl = 40, .species = SPECIES_HITMONCHAN },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RuinManiacAlex_Divergent[] = {
    { .lvl = 39, .species = SPECIES_GEODUDE_A },
    { .lvl = 40, .species = SPECIES_NOSEPASS },
    { .lvl = 41, .species = SPECIES_PROBOPASS },
};
// #endregion

// #region Route 12 & Scalding Spa
const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteJoanne_Divergent[] = {
    { .lvl = 39, .species = SPECIES_STUFFUL },
    { .lvl = 40, .species = SPECIES_MANECTRIC },
    { .lvl = 40, .species = SPECIES_ABSOL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_PsychicTony_Divergent[] = {
    { .lvl = 40, .species = SPECIES_MUSHARNA },
    { .lvl = 42, .species = SPECIES_ALAKAZAM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_HikerDwight_Divergent[] = {
    { .lvl = 39, .species = SPECIES_GEODUDE_A },
    { .lvl = 39, .species = SPECIES_DIGLETT_A },
    { .lvl = 41, .species = SPECIES_CRUSTLE },
    { .lvl = 42, .species = SPECIES_DUGTRIO_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteTrixie_Divergent[] = {
    { .lvl = 41, .species = SPECIES_INCINEROAR },
    { .lvl = 41, .species = SPECIES_AMBIPOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_GentlemanGeoffrey_Divergent[] = {
    { .lvl = 41, .species = SPECIES_PIDGEOT },
    { .lvl = 41, .species = SPECIES_DOUBLADE },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_HikerEugene_Divergent[] = {
    { .lvl = 43, .species = SPECIES_GRAVELER_A },
    { .lvl = 43, .species = SPECIES_RHYDON },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_SupernerdStephen_Divergent[] = {
    { .lvl = 42, .species = SPECIES_EXEGGUTOR },
    { .lvl = 44, .species = SPECIES_PERSIAN },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_JugglerJohan_Divergent[] = {
    { .lvl = 41, .species = SPECIES_MONFERNO },
    { .lvl = 41, .species = SPECIES_ARCANINE },
    { .lvl = 42, .species = SPECIES_MAGMAR },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_BlackbeltKieran_Divergent[] = {
    { .lvl = 44, .species = SPECIES_EMBOAR },
};

const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena_Divergent[] = {
    {
        .lvl = 42,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_AURORAVEIL, MOVE_BLIZZARD, MOVE_RAZORLEAF, MOVE_INGRAIN },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 42,
        .species = SPECIES_ARCTOZOLT,
        .moves = { MOVE_FREEZEDRY, MOVE_ANCIENTPOWER, MOVE_SURF, MOVE_THUNDERBOLT },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Slush Rush
    },
    {
        .lvl = 42,
        .species = SPECIES_VANILLISH,
        .moves = { MOVE_ICEBEAM, MOVE_ACIDARMOR, MOVE_FLASHCANNON, MOVE_HAIL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Snow Cloak
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_BugCatcherBrenan_Divergent[] = {
    { .lvl = 42, .species = SPECIES_SNOVER },
    { .lvl = 43, .species = SPECIES_VANILLISH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierChantal_Divergent[] = {
    { .lvl = 41, .species = SPECIES_SEEL },
    { .lvl = 42, .species = SPECIES_DEWGONG },
    { .lvl = 42, .species = SPECIES_JYNX },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_HikerKumar_Divergent[] = {
    { .lvl = 45, .species = SPECIES_EISCUE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierAubrey_Divergent[] = {
    { .lvl = 43, .species = SPECIES_SEALEO },
    { .lvl = 43, .species = SPECIES_VANILLISH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierLenora_Divergent[] = {
    { .lvl = 42, .species = SPECIES_SANDSHREW_A },
    { .lvl = 42, .species = SPECIES_SANDSHREW_A },
    { .lvl = 43, .species = SPECIES_SANDSLASH_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierMegan_Divergent[] = {
    { .lvl = 43, .species = SPECIES_VANILLITE },
    { .lvl = 44, .species = SPECIES_WALREIN },
    { .lvl = 45, .species = SPECIES_VANILLISH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SwimmerMGreg_Divergent[] = {
    { .lvl = 49, .species = SPECIES_CRYOGONAL },
    { .lvl = 49, .species = SPECIES_DEWGONG },
    { .lvl = 51, .species = SPECIES_SEALEO },
};

// #endregion

// #region Bruccie Village & Calicin Bay
const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_LassMel_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_TANGROWTH,
        .moves = { MOVE_ANCIENTPOWER, MOVE_SLAM, MOVE_GIGADRAIN, MOVE_NONE },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 43,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_UTURN, MOVE_WATERPLEDGE, MOVE_ICYWIND, MOVE_WATERSHURIKEN },
        .ability = Ability_Hidden // Protean
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_BirdKeeperOwen_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_PINSIR,
        .moves = { MOVE_XSCISSOR, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_AERIALACE },
        .ability = Ability_Hidden // Moxie
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_EngineerTommy_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_SPIRITOMB,
        .moves = { MOVE_SUBSTITUTE, MOVE_SUCKERPUNCH, MOVE_WILLOWISP, MOVE_PSYSHOCK },
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 43,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_PROTECT, MOVE_RECOVER, MOVE_AQUAJET, MOVE_HAZE },
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_HikerJoel_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SHADOWBALL, MOVE_IRONHEAD, MOVE_SHADOWSNEAK },
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 43,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_SANDSTORM, MOVE_EARTHPOWER, MOVE_STONEEDGE, MOVE_DISCHARGE },
        .ability = Ability_Hidden // Sand Force
    },
    {
        .lvl = 44,
        .species = SPECIES_CRAMORANT_GULPING,
        .moves = { MOVE_SURF, MOVE_DIVE, MOVE_DRILLPECK, MOVE_STOCKPILE },
        .ability = Ability_1 // Gulp Missile
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_CrushGirlEllie_Divergent[] = {
    {
        .lvl = 44, 
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_DRILLRUN, MOVE_LEECHLIFE, MOVE_AQUAJET },
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 44,
        .species = SPECIES_AMBIPOM,
        .moves = { MOVE_FURYSWIPES, MOVE_DOUBLEHIT, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Skill Link
    }
};

const struct TrainerMonItemCustomMoves sParty_BruccieVillageGym_LeaderAbby_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_ROLEPLAY, MOVE_PSYCHIC, MOVE_FOCUSBLAST, MOVE_RECOVER },
        .ability = Ability_Hidden // Magic Guard
    },
    {
        .lvl = 46,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_SUPERPOWER, MOVE_LEAFBLADE, MOVE_XSCISSOR, MOVE_SYNTHESIS },
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 46,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_COIL, MOVE_WILDCHARGE, MOVE_CRUNCH, MOVE_FLAMETHROWER },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 47,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_CALMMIND, MOVE_MOONBLAST, MOVE_MOONLIGHT, MOVE_FLAMETHROWER },
        .ability = Ability_Hidden // Unaware
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SkierRita_Divergent[] = {
    { .lvl = 42, .species = SPECIES_SPHEAL },
    { .lvl = 42, .species = SPECIES_SPHEAL },
    { .lvl = 43, .species = SPECIES_EISCUE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFFran_Divergent[] = {
    { .lvl = 50, .species = SPECIES_ABOMASNOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMAngelo_Divergent[] = {
    { .lvl = 47, .species = SPECIES_DEWGONG },
    { .lvl = 48, .species = SPECIES_DRAGALGE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMSebastian_Divergent[] = {
    { .lvl = 47, .species = SPECIES_SEALEO },
    { .lvl = 47, .species = SPECIES_WALREIN }
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFCorrine_Divergent[] = {
    { .lvl = 49, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_FishermanOliver_Divergent[] = {
    { .lvl = 42, .species = SPECIES_SKRELP },
    { .lvl = 42, .species = SPECIES_SKRELP },
    { .lvl = 44, .species = SPECIES_KINGLER },
    { .lvl = 44, .species = SPECIES_WISHIWASHI },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoHugo_Divergent[] = {
    { .lvl = 45, .species = SPECIES_SKUNTANK },
    { .lvl = 46, .species = SPECIES_DRIFBLIM },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoAnise_Divergent[] = {
    { .lvl = 44, .species = SPECIES_SWOOBAT },
    { .lvl = 45, .species = SPECIES_DRUDDIGON },
    { .lvl = 45, .species = SPECIES_PANGORO },
};

const struct TrainerMonItemCustomMoves sParty_CalicinBay_TeamPlutoYolena_Divergent[] = {
    {
        .lvl = 46,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_AURORAVEIL, MOVE_BLIZZARD, MOVE_WOODHAMMER, MOVE_INGRAIN },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 46,
        .species = SPECIES_ARCTOZOLT,
        .moves = { MOVE_FREEZEDRY, MOVE_ANCIENTPOWER, MOVE_SURF, MOVE_THUNDERBOLT },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Slush Rush
    },
    {
        .lvl = 47,
        .species = SPECIES_VANILLUXE,
        .moves = { MOVE_ICEBEAM, MOVE_ACIDARMOR, MOVE_FLASHCANNON, MOVE_HAIL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Snow Warning
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoClancy_Divergent[] = {
    { .lvl = 45, .species = SPECIES_GRANBULL },
    { .lvl = 46, .species = SPECIES_GOLURK },
    { .lvl = 47, .species = SPECIES_DRAGALGE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoEna_Divergent[] = {
    { .lvl = 45, .species = SPECIES_ARIADOS },
    { .lvl = 46, .species = SPECIES_LURANTIS },
    { .lvl = 47, .species = SPECIES_CHANDELURE },
};
// #endregion

// #region Pluto HQ
const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoHeathcliff_Divergent[] = {
    { .lvl = 45, .species = SPECIES_SKUNTANK },
    { .lvl = 45, .species = SPECIES_AGGRON },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B1F_ScientistSeamus_Divergent[] = {
    { .lvl = 44, .species = SPECIES_ROTOM_FAN },
    { .lvl = 44, .species = SPECIES_PORYGON_Z },
    { .lvl = 45, .species = SPECIES_EXEGGUTOR_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoColton_Divergent[] = {
    { .lvl = 46, .species = SPECIES_DRUDDIGON },
    { .lvl = 46, .species = SPECIES_ELECTRODE },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B2F_ScientistWayne_Divergent[] = {
    { .lvl = 45, .species = SPECIES_DRIFLOON },
    { .lvl = 44, .species = SPECIES_SHUPPET },
    { .lvl = 44, .species = SPECIES_LINOONE_G },
    { .lvl = 45, .species = SPECIES_DRAGALGE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoDenise_Divergent[] = {
    { .lvl = 45, .species = SPECIES_SWOOBAT },
    { .lvl = 46, .species = SPECIES_GRAVELER_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoTheodore_Divergent[] = {
    { .lvl = 47, .species = SPECIES_OBSTAGOON },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B3F_TeamPlutoYeon_Divergent[] = {
    { .lvl = 47, .species = SPECIES_ZWEILOUS },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMatty_Divergent[] = {
    { .lvl = 46, .species = SPECIES_KINGLER },
    { .lvl = 46, .species = SPECIES_DRAKLOAK },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B4F_ScientistGary_Divergent[] = {
    { .lvl = 45, .species = SPECIES_PANCHAM },
    { .lvl = 46, .species = SPECIES_KLEFKI },
    { .lvl = 45, .species = SPECIES_TANGROWTH },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMay_Divergent[] = {
    { .lvl = 44, .species = SPECIES_GLOOM },
    { .lvl = 44, .species = SPECIES_DRIFLOON },
    { .lvl = 44, .species = SPECIES_SANDSLASH_A },
    { .lvl = 44, .species = SPECIES_VILEPLUME },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoClay_Divergent[] = {
    { .lvl = 46, .species = SPECIES_AMBIPOM },
    { .lvl = 47, .species = SPECIES_AGGRON },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoVictor_Divergent[] = {
    { .lvl = 44, .species = SPECIES_LINOONE_G },
    { .lvl = 46, .species = SPECIES_WOOBAT },
    { .lvl = 46, .species = SPECIES_SWOOBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoPaula_Divergent[] = {
    { .lvl = 46, .species = SPECIES_MORGREM },
    { .lvl = 46, .species = SPECIES_MURKROW },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoGiana_Divergent[] = {
    { .lvl = 44, .species = SPECIES_SKORUPI },
    { .lvl = 45, .species = SPECIES_SKORUPI },
    { .lvl = 46, .species = SPECIES_DRAPION },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B6F_ScientistOrson_Divergent[] = {
    { .lvl = 47, .species = SPECIES_ROTOM_WASH },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoQuinn_Divergent[] = {
    { .lvl = 44, .species = SPECIES_STUNKY },
    { .lvl = 44, .species = SPECIES_GROWLITHE },
    { .lvl = 44, .species = SPECIES_TRUBBISH },
    { .lvl = 45, .species = SPECIES_GARBODOR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoLayla_Divergent[] = {
    { .lvl = 47, .species = SPECIES_INCINEROAR },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B7F_ScientistNico_Divergent[] = {
    { .lvl = 45, .species = SPECIES_DUOSION },
    { .lvl = 45, .species = SPECIES_GRIMMSNARL },
    { .lvl = 46, .species = SPECIES_POLTEAGEIST },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoMitch_Divergent[] = {
    { .lvl = 46, .species = SPECIES_SHUPPET },
    { .lvl = 46, .species = SPECIES_BANETTE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoRichard_Divergent[] = {
    { .lvl = 46, .species = SPECIES_SWOOBAT },
    { .lvl = 47, .species = SPECIES_DRAPION },
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_BULKUP, MOVE_SUCKERPUNCH },
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 48,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_CRUNCH },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 48,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_EARTHPOWER, MOVE_LAVAPLUME, MOVE_SUNNYDAY, MOVE_IRONHEAD },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 49,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SUBSTITUTE, MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_UTURN },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYSHOCK, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_RECOVER },
        .ability = Ability_2 // Download
    },
    {
        .lvl = 48,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_CLOSECOMBAT, MOVE_SUCKERPUNCH, MOVE_RAPIDSPIN },
        .heldItem = ITEM_FIGHTING_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 48,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_NIGHTSLASH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 49,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_DRAINPUNCH },
        .ability = Ability_1 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Divergent[] = {
    {
        .lvl = 49,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_IRONHEAD, MOVE_SACREDSWORD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 49,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_HEAVYSLAM, MOVE_ROCKSLIDE, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 49,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 49,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_MUDDYWATER, MOVE_RECOVER, MOVE_DAZZLINGGLEAM, MOVE_BLIZZARD },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 50,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_DARKPULSE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    },
};
// #endregion

// #region Route 18
const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJasper_Divergent[] = {
    { .lvl = 46, .species = SPECIES_MARSHTOMP },
    { .lvl = 46, .species = SPECIES_KRABBY },
    { .lvl = 47, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_TriathleteDeborah_Divergent[] = {
    { .lvl = 47, .species = SPECIES_CINDERACE },
    { .lvl = 47, .species = SPECIES_AMBIPOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJudie_Divergent[] = {
    { .lvl = 49, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BirdKeeperKirk_Divergent[] = {
    { .lvl = 47, .species = SPECIES_DECIDUEYE },
    { .lvl = 48, .species = SPECIES_PIDGEOT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_LassEmma_Divergent[] = {
    { .lvl = 46, .species = SPECIES_FURRET },
    { .lvl = 47, .species = SPECIES_ALCREMIE_RIBBON },
    { .lvl = 47, .species = SPECIES_FLAPPLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BlackbeltRohan_Divergent[] = {
    { .lvl = 49, .species = SPECIES_MACHAMP }
};
// #endregion

// #region Route 16
const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerGale_Divergent[] = {
    { .lvl = 51, .species = SPECIES_SKRELP },
    { .lvl = 51, .species = SPECIES_SKRELP },
    { .lvl = 52, .species = SPECIES_DRAGALGE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerAmy_Divergent[] = {
    { .lvl = 54, .species = SPECIES_WISHIWASHI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_BirdKeeperTrevor_Divergent[] = {
    { .lvl = 48, .species = SPECIES_PIDGEOTTO },
    { .lvl = 48, .species = SPECIES_STARAVIA },
    { .lvl = 49, .species = SPECIES_HAWLUCHA },
    { .lvl = 49, .species = SPECIES_ORICORIO_S }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_LadyMaria_Divergent[] = {
    { .lvl = 55, .species = SPECIES_TSAREENA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerChristina_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CROCONAW },
    { .lvl = 53, .species = SPECIES_SWANNA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerPhillip_Divergent[] = {
    { .lvl = 50, .species = SPECIES_AZUMARILL },
    { .lvl = 51, .species = SPECIES_SEEL },
    { .lvl = 52, .species = SPECIES_DEWGONG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerLester_Divergent[] = {
    { .lvl = 54, .species = SPECIES_DRAGALGE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerWendy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_SKRELP },
    { .lvl = 52, .species = SPECIES_GRAPPLOCT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberCody_Divergent[] = {
    { .lvl = 51, .species = SPECIES_MAGMAR },
    { .lvl = 52, .species = SPECIES_CHESNAUGHT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberLeslie_Divergent[] = {
    { .lvl = 51, .species = SPECIES_DUOSION },
    { .lvl = 52, .species = SPECIES_DIGGERSBY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerClementine_Divergent[] = {
    { .lvl = 52, .species = SPECIES_KINGLER },
    { .lvl = 52, .species = SPECIES_FERALIGATR }
};
// #endregion

// #region Route 14
const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerIvan_Divergent[] = {
    { .lvl = 48, .species = SPECIES_FEEBAS },
    { .lvl = 48, .species = SPECIES_MARSHTOMP },
    { .lvl = 48, .species = SPECIES_WHISCASH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_HikerClifford_Divergent[] = {
    { .lvl = 47, .species = SPECIES_GRAVELER_A },
    { .lvl = 48, .species = SPECIES_NOSEPASS },
    { .lvl = 49, .species = SPECIES_MAROWAK_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanEsteban_Divergent[] = {
    { .lvl = 48, .species = SPECIES_CLOBBOPUS },
    { .lvl = 49, .species = SPECIES_GRAPPLOCT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanTucker_Divergent[] = {
    { .lvl = 50, .species = SPECIES_WISHIWASHI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerEleanor_Divergent[] = {
    { .lvl = 46, .species = SPECIES_SKRELP },
    { .lvl = 46, .species = SPECIES_SKRELP },
    { .lvl = 46, .species = SPECIES_AZUMARILL },
    { .lvl = 47, .species = SPECIES_MARILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_BlackbeltJoaquin_Divergent[] = {
    { .lvl = 47, .species = SPECIES_MEDICHAM },
    { .lvl = 48, .species = SPECIES_EMBOAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerChris_Divergent[] = {
    { .lvl = 47, .species = SPECIES_BARBOACH },
    { .lvl = 47, .species = SPECIES_ARAQUANID },
    { .lvl = 48, .species = SPECIES_SWANNA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_YoungsterFreddie_Divergent[] = {
    { .lvl = 46, .species = SPECIES_ZIGZAGOON_G },
    { .lvl = 46, .species = SPECIES_LINOONE_G },
    { .lvl = 46, .species = SPECIES_MANECTRIC },
    { .lvl = 47, .species = SPECIES_STARAVIA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_PsychicTobin_Divergent[] = {
    { .lvl = 48, .species = SPECIES_DUOSION },
    { .lvl = 48, .species = SPECIES_JYNX },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerMacie_Divergent[] = {
    { .lvl = 46, .species = SPECIES_SEEL },
    { .lvl = 47, .species = SPECIES_OSHAWOTT },
    { .lvl = 47, .species = SPECIES_DEWOTT }
};

// #endregion

// #region Route 15 North and South
const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerMiles_Divergent[] = {
    { .lvl = 50, .species = SPECIES_SPHEAL },
    { .lvl = 49, .species = SPECIES_SPHEAL },
    { .lvl = 50, .species = SPECIES_WALREIN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerFiona_Divergent[] = {
    { .lvl = 52, .species = SPECIES_DEWGONG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_HikerKlaus_Divergent[] = {
    { .lvl = 50, .species = SPECIES_GRAVELER_A },
    { .lvl = 50, .species = SPECIES_AGGRON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerUrsula_Divergent[] = {
    { .lvl = 50, .species = SPECIES_BARBOACH },
    { .lvl = 51, .species = SPECIES_WHISCASH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerQuincy_Divergent[] = {
    { .lvl = 51, .species = SPECIES_PRINPLUP },
    { .lvl = 52, .species = SPECIES_AZUMARILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_CoolTrainerWesley_Divergent[] = {
    { .lvl = 52, .species = SPECIES_ROTOM_HEAT },
    { .lvl = 52, .species = SPECIES_PUPITAR },
    { .lvl = 53, .species = SPECIES_LILLIGANT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SuperNerdEthan_Divergent[] = {
    { .lvl = 52, .species = SPECIES_DRAKLOAK },
    { .lvl = 52, .species = SPECIES_EXEGGUTOR_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_ChannelerLila_Divergent[] = {
    { .lvl = 49, .species = SPECIES_SHUPPET },
    { .lvl = 49, .species = SPECIES_SINISTEA },
    { .lvl = 50, .species = SPECIES_KLEFKI },
    { .lvl = 50, .species = SPECIES_BANETTE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerGerald_Divergent[] = {
    { .lvl = 51, .species = SPECIES_FERALIGATR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerAlexandra_Divergent[] = {
    { .lvl = 49, .species = SPECIES_MARILL },
    { .lvl = 49, .species = SPECIES_DUCKLETT },
    { .lvl = 50, .species = SPECIES_WHISCASH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerBernard_Divergent[] = {
    { .lvl = 52, .species = SPECIES_SEISMITOAD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerHarold_Divergent[] = {
    { .lvl = 49, .species = SPECIES_PALPITOAD },
    { .lvl = 51, .species = SPECIES_MARSHTOMP },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerMelinda_Divergent[] = {
    { .lvl = 48, .species = SPECIES_SQUIRTLE },
    { .lvl = 48, .species = SPECIES_SKRELP },
    { .lvl = 48, .species = SPECIES_CLOBBOPUS },
    { .lvl = 50, .species = SPECIES_SWAMPERT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_BlackbeltFranklin_Divergent[] = {
    { .lvl = 50, .species = SPECIES_MACHOKE },
    { .lvl = 51, .species = SPECIES_PANGORO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerPatricia_Divergent[] = {
    { .lvl = 50, .species = SPECIES_WIMPOD },
    { .lvl = 52, .species = SPECIES_GOLISOPOD },
};
// #endregion

// #region Seppire Cove
const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerValerie_Divergent[] = {
    { .lvl = 52, .species = SPECIES_DEWGONG },
    { .lvl = 52, .species = SPECIES_WHISCASH },
    { .lvl = 53, .species = SPECIES_SEALEO },
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerIchabod_Divergent[] = {
    { .lvl = 54, .species = SPECIES_DRAKLOAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_RuinManiacCarter_Divergent[] = {
    { .lvl = 53, .species = SPECIES_GRAVELER_A },
    { .lvl = 53, .species = SPECIES_DUGTRIO_A },
};
// #endregion

// #region Route 19
const struct TrainerMonNoItemDefaultMoves sParty_Route19_LassSamantha_Divergent[] = {
    { .lvl = 48, .species = SPECIES_BELLOSSOM },
    { .lvl = 49, .species = SPECIES_BUTTERFREE },
    { .lvl = 48, .species = SPECIES_JYNX }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_CoolTrainerRose_Divergent[] = {
    { .lvl = 50, .species = SPECIES_ARCANINE },
    { .lvl = 50, .species = SPECIES_METANG },
    { .lvl = 50, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhineas_Divergent[] = {
    { .lvl = 49, .species = SPECIES_DRAGALGE },
    { .lvl = 50, .species = SPECIES_DRAMPA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhoebe_Divergent[] = {
    { .lvl = 49, .species = SPECIES_FURRET },
    { .lvl = 50, .species = SPECIES_GRIMMSNARL }
};
// #endregion

// #region Emraldin Quay
const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_ChannelerMarguerite_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_QUILLADIN, // Steel / Ground
        .moves = { MOVE_METALCLAW, MOVE_BULLDOZE, MOVE_BRICKBREAK, MOVE_SPIKES },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_HARIYAMA, // Ghost / Dark
        .moves = { MOVE_CURSE, MOVE_KNOCKOFF, MOVE_BRINE, MOVE_CLOSECOMBAT },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_PINSIR, // Fighting / Bug
        .moves = { MOVE_DETECT, MOVE_XSCISSOR, MOVE_OUTRAGE, MOVE_IRONDEFENSE },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_NinjaBoyJulien_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_ANORITH, // Normal / Ghost
        .moves = { MOVE_CURSE, MOVE_CRUSHCLAW, MOVE_BUGBITE, MOVE_SMACKDOWN },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_SEEL, // Ground / Fairy
        .moves = { MOVE_DRILLRUN, MOVE_CHARM, MOVE_WATERFALL, MOVE_AVALANCHE },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_OBSTAGOON, // Fire / Ice
        .moves = { MOVE_FIREPUNCH, MOVE_ICEBEAM, MOVE_THIEF, MOVE_STOMPINGTANTRUM },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_BugCatcherPerry_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_ELECTRODE, // Steel
        .moves = { MOVE_GYROBALL, MOVE_METALSOUND, MOVE_DISCHARGE, MOVE_SELFDESTRUCT },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_TROPIUS, // Grass / Dragon
        .moves = { MOVE_MAGICALLEAF, MOVE_OUTRAGE, MOVE_BODYSLAM, MOVE_AIRSLASH },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_SALAMENCE, // Dark / Dragon
        .moves = { MOVE_CRUNCH, MOVE_DRAGONBREATH, MOVE_FLY, MOVE_FLAMETHROWER },
        .ability = Ability_Random_1_2
    },
};
// #endregion

// #region Route 23
const struct TrainerMonNoItemDefaultMoves sParty_Route23_BirdKeeperTyrone_Divergent[] = {
    { .lvl = 52, .species = SPECIES_SWANNA },
    { .lvl = 52, .species = SPECIES_PIDGEOTTO },
    { .lvl = 53, .species = SPECIES_DECIDUEYE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GamblerGordon_Divergent[] = {
    { .lvl = 50, .species = SPECIES_DITTO },
    { .lvl = 50, .species = SPECIES_MEDICHAM },
    { .lvl = 51, .species = SPECIES_PINSIR },
    { .lvl = 51, .species = SPECIES_PORYGON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_SuperNerdEmmett_Divergent[] = {
    { .lvl = 53, .species = SPECIES_SHELGON },
    { .lvl = 53, .species = SPECIES_WISHIWASHI },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GentlemanRussell_Divergent[] = {
    { .lvl = 53, .species = SPECIES_PERRSERKER },
    { .lvl = 53, .species = SPECIES_HONCHKROW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_CrushGirlLily_Divergent[] = {
    { .lvl = 50, .species = SPECIES_MEDITITE },
    { .lvl = 51, .species = SPECIES_MACHOKE },
    { .lvl = 52, .species = SPECIES_MACHAMP },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_BeautyMiranda_Divergent[] = {
    { .lvl = 52, .species = SPECIES_PONYTA },
    { .lvl = 52, .species = SPECIES_PONYTA_G },
    { .lvl = 53, .species = SPECIES_PONYTA },
};
// #endregion

// #region Route 20
const struct TrainerMonNoItemDefaultMoves sParty_Route20_PsychicMcKenzie_Divergent[] = {
    { .lvl = 49, .species = SPECIES_RAPIDASH_G },
    { .lvl = 50, .species = SPECIES_REUNICLUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_PicknickerWhitney_Divergent[] = {
    { .lvl = 48, .species = SPECIES_BELLOSSOM },
    { .lvl = 48, .species = SPECIES_AROMATISSE },
    { .lvl = 50, .species = SPECIES_QWILFISH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_TriathleteLena_Divergent[] = {
    { .lvl = 50, .species = SPECIES_MEGANIUM },
    { .lvl = 50, .species = SPECIES_LILLIGANT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_EngineerHomer_Divergent[] = {
    { .lvl = 50, .species = SPECIES_DUGTRIO_A },
    { .lvl = 51, .species = SPECIES_GRAVELER_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_CrushGirlRoxy_Divergent[] = {
    { .lvl = 53, .species = SPECIES_EMBOAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_HikerRoyce_Divergent[] = {
    { .lvl = 50, .species = SPECIES_NOSEPASS },
    { .lvl = 50, .species = SPECIES_RHYDON },
    { .lvl = 51, .species = SPECIES_PROBOPASS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_SuperNerdElliot_Divergent[] = {
    { .lvl = 52, .species = SPECIES_SCYTHER },
    { .lvl = 52, .species = SPECIES_SCIZOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_YoungsterDewey_Divergent[] = {
    { .lvl = 50, .species = SPECIES_MANECTRIC },
    { .lvl = 50, .species = SPECIES_ABSOL },
    { .lvl = 51, .species = SPECIES_ZANGOOSE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_JugglerHiram_Divergent[] = {
    { .lvl = 52, .species = SPECIES_HEATMOR },
    { .lvl = 53, .species = SPECIES_DURANT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_NurseJudy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_MILCERY },
    { .lvl = 52, .species = SPECIES_AUDINO }
};
// #endregion

// #region Route 22
const struct TrainerMonNoItemDefaultMoves sParty_Route22_CoolTrainer_Gail_Divergent[] = {
    { .lvl = 51, .species = SPECIES_SEISMITOAD },
    { .lvl = 52, .species = SPECIES_RAPIDASH },
    { .lvl = 53, .species = SPECIES_ZWEILOUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_ScientistLarry_Divergent[] = {
    { .lvl = 52, .species = SPECIES_DWEBBLE },
    { .lvl = 52, .species = SPECIES_PORYGON_Z }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_SrAndJr_AlmaAndMai_Divergent[] = {
    { .lvl = 51, .species = SPECIES_GRANBULL },
    { .lvl = 51, .species = SPECIES_YANMA },
    { .lvl = 52, .species = SPECIES_TANGELA },
    { .lvl = 52, .species = SPECIES_AZUMARILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_JugglerChauncy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_BRIONNE },
    { .lvl = 52, .species = SPECIES_KLEFKI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_BurglarMose_Divergent[] = {
    { .lvl = 53, .species = SPECIES_PANGORO },
    { .lvl = 54, .species = SPECIES_GARBODOR },
    { .lvl = 54, .species = SPECIES_GRAPPLOCT }
};
// #endregion

// #region Route 21
const struct TrainerMonNoItemDefaultMoves sParty_Route21_PokefanWalter_Divergent[] = {
    { .lvl = 51, .species = SPECIES_SIMISEAR },
    { .lvl = 51, .species = SPECIES_PIGNITE },
    { .lvl = 52, .species = SPECIES_KLEFKI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_CollectorEric_Divergent[] = {
    { .lvl = 53, .species = SPECIES_ROTOM },
    { .lvl = 53, .species = SPECIES_TANGROWTH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_HikerRicardo_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CRUSTLE },
    { .lvl = 53, .species = SPECIES_GRAPPLOCT },
    { .lvl = 52, .species = SPECIES_RHYDON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_DragonTamerTanner_Divergent[] = {
    { .lvl = 55, .species = SPECIES_TYRANITAR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_ParasolLadyKatrina_Divergent[] = {
    { .lvl = 52, .species = SPECIES_ORICORIO_P },
    { .lvl = 52, .species = SPECIES_SAWSBUCK_WINTER },
    { .lvl = 53, .species = SPECIES_FURRET }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_NinjaBoyIshan_Divergent[] = {
    { .lvl = 51, .species = SPECIES_SCYTHER },
    { .lvl = 51, .species = SPECIES_MORGREM },
    { .lvl = 52, .species = SPECIES_DRAPION },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_RockerAxel_Divergent[] = {
    { .lvl = 51, .species = SPECIES_MARACTUS },
    { .lvl = 51, .species = SPECIES_XATU },
    { .lvl = 52, .species = SPECIES_RILLABOOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_NurseBenedikta_Divergent[] = {
    { .lvl = 53, .species = SPECIES_ALCREMIE_CLOVER }
};
// #endregion

// #region Secret Trail
const struct TrainerMonNoItemDefaultMoves sParty_SecretTrail_ChannelerHeather_Divergent[] = {
    { .lvl = 54, .species = SPECIES_ORICORIO_S },
    { .lvl = 54, .species = SPECIES_HAUNTER },
    { .lvl = 54, .species = SPECIES_BANETTE }
};
// #endregion

// #region Mimmett Jungle
const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ScientistSilas_Divergent[] = {
    { .lvl = 51, .species = SPECIES_REUNICLUS },
    { .lvl = 52, .species = SPECIES_SERPERIOR },
    { .lvl = 52, .species = SPECIES_VANILLISH }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_RuinManiacWinston_Divergent[] = {
    { .lvl = 51, .species = SPECIES_XATU },
    { .lvl = 53, .species = SPECIES_RHYDON }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BlackbeltLouis_Divergent[] = {
    { .lvl = 54, .species = SPECIES_HARIYAMA }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ChannelerFreyja_Divergent[] = {
    { .lvl = 51, .species = SPECIES_GASTLY },
    { .lvl = 51, .species = SPECIES_GASTLY },
    { .lvl = 52, .species = SPECIES_DRAKLOAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BugCatcherNeil_Divergent[] = {
    { .lvl = 52, .species = SPECIES_ARIADOS },
    { .lvl = 53, .species = SPECIES_YANMEGA }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_FishermanJerry_Divergent[] = {
    { .lvl = 52, .species = SPECIES_DRAGALGE },
    { .lvl = 53, .species = SPECIES_WHISCASH }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PokefanSusan_Divergent[] = {
    { .lvl = 52, .species = SPECIES_BUNNELBY },
    { .lvl = 53, .species = SPECIES_CRYOGONAL }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PsychicWanda_Divergent[] = {
    { .lvl = 54, .species = SPECIES_ALAKAZAM }
};
// #endregion

// #region Tsarvosa City
const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_StatsDojo_Kaito_Divergent[] = {
    {
        .lvl = 51,
        .species = SPECIES_CRUSTLE,
        .moves = { MOVE_XSCISSOR, MOVE_ROCKSLIDE, MOVE_SHELLSMASH, MOVE_SHADOWCLAW },
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 52,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_SHADOWPUNCH, MOVE_HIGHHORSEPOWER, MOVE_MEGAPUNCH, MOVE_HAMMERARM },
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 52,
        .species = SPECIES_DRAMPA,
        .moves = { MOVE_HYPERVOICE, MOVE_DRAGONPULSE, MOVE_LIGHTSCREEN, MOVE_GLARE },
        .ability = Ability_1 // Berserk
    },
    {
        .lvl = 53,
        .species = SPECIES_HITMONTOP,
        .moves = { MOVE_TRIPLEKICK, MOVE_QUICKATTACK, MOVE_BULLDOZE, MOVE_BRUTALSWING },
        .ability = Ability_2 // Technician
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_MAKUHITA },
    { .lvl = 15, .species = SPECIES_GULPIN },
    { .lvl = 15, .species = SPECIES_DRIFLOON }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_SWALOT },
    { .lvl = 30, .species = SPECIES_TROPIUS },
    { .lvl = 30, .species = SPECIES_QUAGSIRE }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_WALREIN },
    { .lvl = 45, .species = SPECIES_SEISMITOAD },
    { .lvl = 45, .species = SPECIES_AZUMARILL }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_GROWLITHE },
    { .lvl = 15, .species = SPECIES_MUDKIP },
    { .lvl = 15, .species = SPECIES_SENTRET }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_FLAPPLE },
    { .lvl = 30, .species = SPECIES_MARSHTOMP },
    { .lvl = 30, .species = SPECIES_TOGEDEMARU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_TSAREENA },
    { .lvl = 45, .species = SPECIES_SWAMPERT },
    { .lvl = 45, .species = SPECIES_STARAPTOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_GEODUDE_A },
    { .lvl = 15, .species = SPECIES_CHESPIN },
    { .lvl = 15, .species = SPECIES_GLIGAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_DOUBLADE },
    { .lvl = 30, .species = SPECIES_QUILLADIN },
    { .lvl = 30, .species = SPECIES_GOLISOPOD }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_OBSTAGOON },
    { .lvl = 45, .species = SPECIES_CHESNAUGHT },
    { .lvl = 45, .species = SPECIES_POLIWRATH }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_BULBASAUR },
    { .lvl = 15, .species = SPECIES_VANILLITE },
    { .lvl = 15, .species = SPECIES_NATU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_DRAMPA },
    { .lvl = 30, .species = SPECIES_LAMPENT },
    { .lvl = 30, .species = SPECIES_MAGMAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_GENGAR },
    { .lvl = 45, .species = SPECIES_PORYGON_Z },
    { .lvl = 45, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_SEEL },
    { .lvl = 15, .species = SPECIES_CLEFFA },
    { .lvl = 15, .species = SPECIES_MILCERY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_CRAMORANT },
    { .lvl = 30, .species = SPECIES_HITMONCHAN },
    { .lvl = 30, .species = SPECIES_ARAQUANID }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_BELLOSSOM },
    { .lvl = 45, .species = SPECIES_BLASTOISE },
    { .lvl = 45, .species = SPECIES_POLITOED }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed1_Divergent[] = {
    { .lvl = 15, .species = SPECIES_SNIVY },
    { .lvl = 15, .species = SPECIES_STARYU },
    { .lvl = 15, .species = SPECIES_YANMA }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed2_Divergent[] = {
    { .lvl = 30, .species = SPECIES_SERVINE },
    { .lvl = 30, .species = SPECIES_DEDENNE },
    { .lvl = 30, .species = SPECIES_MANECTRIC }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed3_Divergent[] = {
    { .lvl = 45, .species = SPECIES_SERPERIOR },
    { .lvl = 45, .species = SPECIES_JUMPLUFF },
    { .lvl = 45, .species = SPECIES_PIDGEOT }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin1_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FERALIGATR,
        .moves = { MOVE_DRAGONDANCE, MOVE_ICEPUNCH, MOVE_CRUNCH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_THUNDERPUNCH, MOVE_STONEEDGE, MOVE_EARTHQUAKE, MOVE_HEAVYSLAM },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_FREEZEDRY, MOVE_EXTRASENSORY, MOVE_NASTYPLOT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_ICEBEAM, MOVE_THUNDERBOLT, MOVE_RECOVER },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_DRAGONCLAW, MOVE_CRUNCH, MOVE_PROTECT },
        .heldItem = ITEM_SALAMENCITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin2_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_DRAGONPULSE, MOVE_HURRICANE },
        .heldItem = ITEM_ALTARIANITE,
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_BULKUP, MOVE_CRUNCH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARCANINE,
        .moves = { MOVE_EXTREMESPEED, MOVE_CRUNCH, MOVE_PLAYROUGH, MOVE_SNARL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STARMIE,
        .moves = { MOVE_PSYCHIC, MOVE_ICEBEAM, MOVE_THUNDER, MOVE_SCALD },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_HIGHJUMPKICK, MOVE_DAZZLINGGLEAM, MOVE_STOMP },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_2 // Queenly Majesty
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal1_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_SWORDSDANCE, MOVE_ACROBATICS, MOVE_HIGHJUMPKICK, MOVE_SUBSTITUTE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RILLABOOM,
        .moves = { MOVE_SWORDSDANCE, MOVE_GRASSYGLIDE, MOVE_KNOCKOFF, MOVE_WOODHAMMER },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_ICEBEAM, MOVE_DRAGONTAIL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CINDERACE,
        .moves = { MOVE_PYROBALL, MOVE_UTURN, MOVE_SUCKERPUNCH, MOVE_GUNKSHOT },
        .heldItem = ITEM_CINDERITE,
        .ability = Ability_Hidden // Libero
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SWORDSDANCE, MOVE_EARTHQUAKE, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal2_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_HEAVYSLAM, MOVE_KNOCKOFF, MOVE_EARTHQUAKE, MOVE_BULLETPUNCH },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_CURSE, MOVE_BODYSLAM, MOVE_HEATCRASH, MOVE_REST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BULKUP, MOVE_DRAINPUNCH, MOVE_KNOCKOFF, MOVE_BULLETPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_BONEMERANG, MOVE_STEALTHROCK, MOVE_FIREBLAST },
        .heldItem = ITEM_THICK_CLUB,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GENGAR,
        .moves = { MOVE_NASTYPLOT, MOVE_SHADOWBALL, MOVE_SLUDGEWAVE, MOVE_FOCUSBLAST },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Noam_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STARAPTOR,
        .moves = { MOVE_BRAVEBIRD, MOVE_CLOSECOMBAT, MOVE_AERIALACE, MOVE_UTURN },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAMPA,
        .moves = { MOVE_HYPERVOICE, MOVE_DRAGONPULSE, MOVE_FLY, MOVE_ROCKSLIDE },
        .ability = Ability_1 // Berserk
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_CURSE, MOVE_REST, MOVE_BODYSLAM, MOVE_CRUNCH },
        .ability = Ability_1 // Immunity
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ashley_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_LAVAPLUME, MOVE_EARTHPOWER, MOVE_ROCKSLIDE, MOVE_YAWN },
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARCANINE,
        .moves = { MOVE_EXTREMESPEED, MOVE_FLAMETHROWER, MOVE_SNARL, MOVE_PLAYROUGH },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HEATMOR,
        .moves = { MOVE_FIRELASH, MOVE_HONECLAWS, MOVE_THUNDERPUNCH, MOVE_DRAINPUNCH },
        .ability = Ability_Hidden // White Smoke
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_LAVAPLUME, MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_WILLOWISP },
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Chelsea_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AZUMARILL,
        .moves = { MOVE_BELLYDRUM, MOVE_AQUAJET, MOVE_PLAYROUGH, MOVE_SUPERPOWER },
        .ability = Ability_2 // Huge Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_DRAGONTAIL, MOVE_SURF, MOVE_RECOVER, MOVE_RAINDANCE },
        .ability = Ability_2 // Competitive
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DREDNAW,
        .moves = { MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_SHELLSMASH, MOVE_POISONJAB },
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_AQUARING, MOVE_AQUATAIL, MOVE_REST, MOVE_ICEBEAM },
        .ability = Ability_1 // Schooling
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Buddy_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_HIGHJUMPKICK, MOVE_ACROBATICS, MOVE_UTURN },
        .ability = Ability_2 // Queenly Majesty
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SAWSBUCK_AUTUMN,
        .moves = { MOVE_MEGAHORN, MOVE_ENERGYBALL, MOVE_CHARM, MOVE_DOUBLEEDGE },
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JUMPLUFF,
        .moves = { MOVE_BOUNCE, MOVE_GIGADRAIN, MOVE_REFLECT, MOVE_TAILWIND },
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .ability = Ability_1 // Frisk
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Gawain_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BEWEAR,
        .moves = { MOVE_HAMMERARM, MOVE_TAKEDOWN, MOVE_THUNDERPUNCH, MOVE_BULLDOZE },
        .ability = Ability_1 // Fluffy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MEDICHAM,
        .moves = { MOVE_FIREPUNCH, MOVE_ZENHEADBUTT, MOVE_RECOVER, MOVE_HIGHJUMPKICK },
        .ability = Ability_1 // Pure Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_DYNAMICPUNCH, MOVE_EARTHPOWER, MOVE_LIQUIDATION, MOVE_MINDREADER },
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MACHAMP,
        .moves = { MOVE_KNOCKOFF, MOVE_DYNAMICPUNCH, MOVE_BULLETPUNCH, MOVE_BULKUP },
        .ability = Ability_2 // No Guard
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Skylar_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_SHADOWBALL, MOVE_STRENGTHSAP, MOVE_TAILWIND, MOVE_THUNDERBOLT },
        .ability = Ability_1 // Aftermath
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_MOONBLAST, MOVE_PLUCK, MOVE_DRAGONBREATH, MOVE_COTTONGUARD },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TROPIUS,
        .moves = { MOVE_SYNTHESIS, MOVE_OUTRAGE, MOVE_AIRSLASH, MOVE_ZENHEADBUTT },
        .ability = Ability_2 // Solar Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SWANNA,
        .moves = { MOVE_HURRICANE, MOVE_TAILWIND, MOVE_RAINDANCE, MOVE_SURF },
        .ability = Ability_1 // Keen Eye
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Bella_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SEVIPER,
        .moves = { MOVE_GLARE, MOVE_CRUNCH, MOVE_COIL, MOVE_POISONJAB },
        .ability = Ability_1 // Shed Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VILEPLUME,
        .moves = { MOVE_TOXIC, MOVE_GIGADRAIN, MOVE_MOONBLAST, MOVE_SLUDGEBOMB },
        .ability = Ability_Hidden // Effect Spore
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SWALOT,
        .moves = { MOVE_SLUDGEBOMB, MOVE_BODYSLAM, MOVE_KNOCKOFF, MOVE_THUNDERPUNCH },
        .ability = Ability_1 // Liquid Ooze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARBODOR,
        .moves = { MOVE_SLUDGEBOMB, MOVE_BRUTALSWING, MOVE_THUNDERBOLT, MOVE_MUDSHOT },
        .ability = Ability_Hidden // Aftermath
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Flash_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_FLAMETHROWER, MOVE_SNARL, MOVE_DISCHARGE },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LUXRAY,
        .moves = { MOVE_CRUNCH, MOVE_ELECTRICTERRAIN, MOVE_THUNDERFANG, MOVE_PLAYROUGH },
        .ability = Ability_2 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_DISCHARGE, MOVE_CRUNCH, MOVE_HEADBUTT, MOVE_LIQUIDATION },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_DISCHARGE, MOVE_LIGHTSCREEN, MOVE_FIREPUNCH, MOVE_ROCKSLIDE },
        .ability = Ability_1 // Motor Drive
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Terra_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_EARTHQUAKE, MOVE_MUDDYWATER, MOVE_ROCKTOMB, MOVE_DRAINPUNCH },
        .ability = Ability_2 // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_THUNDERFANG, MOVE_IRONHEAD, MOVE_POISONTAIL, MOVE_EARTHQUAKE },
        .ability = Ability_1 // Sand Spit
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DONPHAN,
        .moves = { MOVE_FIREFANG, MOVE_KNOCKOFF, MOVE_EARTHQUAKE, MOVE_SEEDBOMB },
        .ability = Ability_Hidden // Sand Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_ACROBATICS, MOVE_NIGHTSLASH, MOVE_UTURN, MOVE_ICEFANG },
        .ability = Ability_2 // Sand Veil
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Seifa_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_INDEEDEE_FEMALE,
        .moves = { MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_SHADOWBALL },
        .ability = Ability_Hidden // Psychic Surge
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_XATU,
        .moves = { MOVE_PSYCHIC, MOVE_AIRSLASH, MOVE_TAILWIND, MOVE_NIGHTSHADE },
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STARMIE,
        .moves = { MOVE_POWERGEM, MOVE_SURF, MOVE_RECOVER, MOVE_THUNDERBOLT },
        .ability = Ability_2 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYCHIC, MOVE_SHADOWBALL, MOVE_NASTYPLOT, MOVE_DAZZLINGGLEAM },
        .ability = Ability_1 // Synchronize
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Rocco_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARMALDO,
        .moves = { MOVE_XSCISSOR, MOVE_CRUSHCLAW, MOVE_ROCKSLIDE, MOVE_BULLDOZE },
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_DOUBLEEDGE, MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_STOMPINGTANTRUM },
        .ability = Ability_Hidden // Galvanize
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AERODACTYL,
        .moves = { MOVE_IRONHEAD, MOVE_CRUNCH, MOVE_ROCKSLIDE, MOVE_DRAGONCLAW },
        .ability = Ability_1 // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RHYPERIOR,
        .moves = { MOVE_MEGAHORN, MOVE_HAMMERARM, MOVE_DRILLRUN, MOVE_THUNDERFANG },
        .ability = Ability_2 // Solid Rock
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Janice_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_WOODHAMMER, MOVE_BLIZZARD, MOVE_BRICKBREAK, MOVE_ROCKTOMB },
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRYOGONAL,
        .moves = { MOVE_FREEZEDRY, MOVE_NIGHTSLASH, MOVE_RECOVER, MOVE_ACIDARMOR },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EISCUE,
        .moves = { MOVE_AURORAVEIL, MOVE_HAIL, MOVE_HEADBUTT, MOVE_SURF },
        .ability = Ability_1 // Ice Face
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SANDSLASH_A,
        .moves = { MOVE_ICICLECRASH, MOVE_IRONHEAD, MOVE_ROCKSLIDE, MOVE_XSCISSOR },
        .ability = Ability_Hidden // Slush Rush
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Antoinette_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARAQUANID,
        .moves = { MOVE_BUGBITE, MOVE_LIQUIDATION, MOVE_LEECHLIFE, MOVE_HEADBUTT },
        .ability = Ability_1 // Water Bubble
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCYTHER,
        .moves = { MOVE_WINGATTACK, MOVE_THIEF, MOVE_COUNTER, MOVE_XSCISSOR },
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_YANMEGA,
        .moves = { MOVE_BUGBITE, MOVE_UTURN, MOVE_AIRSLASH, MOVE_CRUNCH },
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_DRILLRUN, MOVE_LIQUIDATION, MOVE_LEECHLIFE },
        .ability = Ability_1 // Emergency Exit
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ryu_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAGALGE,
        .moves = { MOVE_DRAGONPULSE, MOVE_AQUATAIL, MOVE_SLUDGEBOMB, MOVE_THUNDERBOLT },
        .ability = Ability_Hidden // Adaptability
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLAPPLE,
        .moves = { MOVE_DRAGONRUSH, MOVE_GRAVAPPLE, MOVE_IRONDEFENSE, MOVE_DRAGONDANCE },
        .ability = Ability_1 // Ripen
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRUDDIGON,
        .moves = { MOVE_OUTRAGE, MOVE_IRONHEAD, MOVE_HONECLAWS, MOVE_CRUNCH },
        .ability = Ability_1 // Rough Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DRAGONCLAW, MOVE_ZENHEADBUTT, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Caspar_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE },
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_POLTEAGEIST,
        .moves = { MOVE_STRENGTHSAP, MOVE_GIGADRAIN, MOVE_NASTYPLOT, MOVE_SHADOWBALL },
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SPIRITOMB,
        .moves = { MOVE_DARKPULSE, MOVE_PSYSHOCK, MOVE_WILLOWISP, MOVE_ICYWIND },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SHADOWBALL, MOVE_IRONHEAD, MOVE_SHADOWSNEAK },
        .ability = Ability_1 // Stance Change
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Darcy_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER },
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NIGHTSLASH, MOVE_ACROBATICS, MOVE_ROOST, MOVE_HEATWAVE },
        .ability = Ability_Hidden // Moxie
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ABSOL,
        .moves = { MOVE_NIGHTSLASH, MOVE_AIRSLASH, MOVE_THUNDERBOLT, MOVE_KNOCKOFF },
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_OBSTRUCT, MOVE_CROSSCHOP, MOVE_NIGHTSLASH, MOVE_XSCISSOR },
        .ability = Ability_Hidden // Defiant
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Mason_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STEELIX,
        .moves = { MOVE_IRONTAIL, MOVE_STONEEDGE, MOVE_DRAGONBREATH, MOVE_EARTHQUAKE },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_IRONHEAD, MOVE_UTURN, MOVE_CRUNCH, MOVE_PLAYROUGH },
        .ability = Ability_2 // Tough Claws
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AGGRON,
        .moves = { MOVE_IRONHEAD, MOVE_HEADSMASH, MOVE_DOUBLEEDGE, MOVE_IRONDEFENSE },
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_DISCHARGE, MOVE_FLASHCANNON, MOVE_THUNDERWAVE, MOVE_HIDDENPOWER },
        .ability = Ability_Hidden // Analytic
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Faye_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_MOONBLAST, MOVE_METEORMASH, MOVE_WISH, MOVE_AROMATHERAPY },
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_ENERGYBALL, MOVE_CALMMIND, MOVE_RECOVER },
        .ability = Ability_2 // Aroma Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_THUNDERWAVE, MOVE_FLASHCANNON, MOVE_PLAYROUGH, MOVE_REFLECT },
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_FLING, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_STOMPINGTANTRUM },
        .ability = Ability_Hidden // Pickpocket
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_PokefanMarci_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_TRICK, MOVE_PSYSHOCK, MOVE_SHADOWBALL, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 54,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_MUDDYWATER, MOVE_EARTHQUAKE, MOVE_GRASSKNOT },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Poison Touch
    },
    {
        .lvl = 54,
        .species = SPECIES_BANETTE,
        .moves = { MOVE_TRICK, MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_THIEF },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_2 // Frisk
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_ChannelerJamila_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_KINGLER,
        .moves = { MOVE_CRABHAMMER, MOVE_METALCLAW, MOVE_SWORDSDANCE, MOVE_PROTECT },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Sheer Force
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_CoolTrainerNorbert_Divergent[] = {
    {
        .lvl = 55,
        .species = SPECIES_ELECTRODE,
        .moves = { MOVE_ELECTROBALL, MOVE_HIDDENPOWER, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Aftermath
    },
    {
        .lvl = 55,
        .species = SPECIES_MACHAMP,
        .moves = { MOVE_BRICKBREAK, MOVE_POWERUPPUNCH, MOVE_BULKUP, MOVE_ICEPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Guts
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_BurglarMarion_Divergent[] = {
    {
        .lvl = 53,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_SLASH, MOVE_ROCKSLIDE, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 53,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_INCINERATE, MOVE_CURSE, MOVE_ROCKSLIDE, MOVE_TAKEDOWN },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 54,
        .species = SPECIES_EISCUE,
        .moves = { MOVE_FREEZEDRY, MOVE_SURF, MOVE_REFLECT, MOVE_FLIPTURN },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Ice Face
    },
    {
        .lvl = 54,
        .species = SPECIES_SCEPTILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_LEAFBLADE, MOVE_XSCISSOR },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Unburden
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LassAlanah_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_FACADE, MOVE_CRABHAMMER, MOVE_THUNDERFANG, MOVE_UTURN },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 54,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_DISCHARGE, MOVE_TRIATTACK, MOVE_PSYCHIC, MOVE_ICEBEAM },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Download
    },
    {
        .lvl = 54,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_NIGHTSLASH, MOVE_INGRAIN, MOVE_SYNTHESIS, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Contrary
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_GentlemanPaul_Divergent[] = {
    {
        .lvl = 53,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_LIGHTSCREEN, MOVE_REFLECT, MOVE_THUNDERWAVE, MOVE_PLAYROUGH },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 54,
        .species = SPECIES_MAGNETON,
        .moves = { MOVE_HIDDENPOWER, MOVE_THUNDERBOLT, MOVE_METALSOUND, MOVE_FLASHCANNON },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_1 // Magnet Pull
    },
    {
        .lvl = 53,
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_FLYINGPRESS, MOVE_LUNGE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Limber
    },
    {
        .lvl = 54,
        .species = SPECIES_GARBODOR,
        .moves = { MOVE_POISONJAB, MOVE_METALCLAW, MOVE_THUNDERBOLT, MOVE_NONE },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Aftermath
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LeaderIris_Divergent[] = {
    {
        .lvl = 55,
        .species = SPECIES_DRUDDIGON,
        .moves = { MOVE_FIREPUNCH, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_ROCKSLIDE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Sheer Force
    },
    {
        .lvl = 55,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_FACADE, MOVE_KNOCKOFF, MOVE_CROSSCHOP, MOVE_GUNKSHOT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 56,
        .species = SPECIES_DOUBLADE,
        .moves = { MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SHADOWSNEAK, MOVE_SACREDSWORD },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // No Guard
    },
    {
        .lvl = 58,
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_BRUTALSWING, MOVE_IRONHEAD },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Spit
    },
};
// #endregion

// #region Daimyn City Restaurant event
const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Iris_Divergent[] = {
    {
        .lvl = 57,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_FACADE, MOVE_KNOCKOFF, MOVE_CROSSCHOP, MOVE_GUNKSHOT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 58,
        .species = SPECIES_DOUBLADE,
        .moves = { MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SHADOWSNEAK, MOVE_SACREDSWORD },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // No Guard
    },
    {
        .lvl = 59,
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_BRUTALSWING, MOVE_IRONHEAD },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Spit
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Stella_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_DRAPION,
        .moves = { MOVE_THUNDERFANG, MOVE_CROSSPOISON, MOVE_CRUNCH, MOVE_TOXICSPIKES },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 57,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_SHADOWBALL, MOVE_FLAMETHROWER },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 58,
        .species = SPECIES_BELLOSSOM,
        .moves = { MOVE_STUNSPORE, MOVE_QUIVERDANCE, MOVE_GIGADRAIN, MOVE_MOONBLAST },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Stench
    },
};
// #endregion

// #region Daimyn Factory
const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BurglarSly_Divergent[] = {
    { .lvl = 54, .species = SPECIES_PANCHAM },
    { .lvl = 55, .species = SPECIES_ABSOL }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerHasan_Divergent[] = {
    { .lvl = 54, .species = SPECIES_MAGNEMITE },
    { .lvl = 54, .species = SPECIES_MAGNETON },
    { .lvl = 54, .species = SPECIES_MAGNEZONE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BurglarWill_Divergent[] = {
    { .lvl = 53, .species = SPECIES_SKORUPI },
    { .lvl = 54, .species = SPECIES_GROWLITHE },
    { .lvl = 55, .species = SPECIES_SERPERIOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerElroy_Divergent[] = {
    { .lvl = 54, .species = SPECIES_EELEKTRIK },
    { .lvl = 54, .species = SPECIES_MANECTRIC }
};
// #endregion

// #region Carnelidge Volcano
const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerBjorn_Divergent[] = {
    { .lvl = 54, .species = SPECIES_GRAVELER_A },
    { .lvl = 54, .species = SPECIES_MACHOKE },
    { .lvl = 54, .species = SPECIES_SANDACONDA },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ChannelerKelsey_Divergent[] = {
    { .lvl = 53, .species = SPECIES_SHUPPET },
    { .lvl = 53, .species = SPECIES_MORGREM },
    { .lvl = 53, .species = SPECIES_HAUNTER },
    { .lvl = 54, .species = SPECIES_BANETTE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_JugglerSeth_Divergent[] = {
    { .lvl = 55, .species = SPECIES_FURRET },
    { .lvl = 55, .species = SPECIES_DELPHOX },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_DragonTamerFlynn_Divergent[] = {
    { .lvl = 54, .species = SPECIES_ZWEILOUS },
    { .lvl = 55, .species = SPECIES_SHELGON },
    { .lvl = 55, .species = SPECIES_TYRANITAR },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_BirdKeepeFalco_Divergent[] = {
    { .lvl = 55, .species = SPECIES_PIDGEOTTO },
    { .lvl = 55, .species = SPECIES_STARAPTOR },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_CrushGirlEunice_Divergent[] = {
    { .lvl = 56, .species = SPECIES_HAWLUCHA },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_SuperNerdNathan_Divergent[] = {
    { .lvl = 54, .species = SPECIES_GRANBULL },
    { .lvl = 54, .species = SPECIES_SANDSLASH },
    { .lvl = 55, .species = SPECIES_BEWEAR },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerHugh_Divergent[] = {
    { .lvl = 55, .species = SPECIES_DUGTRIO_A },
    { .lvl = 56, .species = SPECIES_AGGRON },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ScientistXander_Divergent[] = {
    { .lvl = 55, .species = SPECIES_ARCTOZOLT },
    { .lvl = 55, .species = SPECIES_PORYGON2 },
    { .lvl = 55, .species = SPECIES_HITMONTOP },
};
// #endregion

// #region Uteya Village
const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_PicknickerLisa_Divergent[] = {
    { .lvl = 1, .species = SPECIES_BANETTE },
    { .lvl = 1, .species = SPECIES_LILLIGANT },
    { .lvl = 1, .species = SPECIES_ALAKAZAM }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_SwimmerTyson_Divergent[] = {
    { .lvl = 1, .species = SPECIES_CLAYDOL },
    { .lvl = 1, .species = SPECIES_DRAPION },
    { .lvl = 1, .species = SPECIES_SEISMITOAD }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_ScientistWilford_Divergent[] = {
    { .lvl = 1, .species = SPECIES_HARIYAMA },
    { .lvl = 1, .species = SPECIES_MAGNEZONE },
    { .lvl = 1, .species = SPECIES_DECIDUEYE }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Michael_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_TORTERRA,
        .moves = { MOVE_ROCKSLIDE, MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_STEALTHROCK },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Overgrow
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Leo_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_HITMONCHAN,
        .moves = { MOVE_ROCKSLIDE, MOVE_HELPINGHAND, MOVE_COACHING, MOVE_BRICKBREAK },
        .ability = Ability_2 // Iron Fist
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Bonnie_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_WIDEGUARD, MOVE_BLOCK, MOVE_ROCKSLIDE, MOVE_DISCHARGE },
        .ability = Ability_2 // Magnet Pull
    },
    {
        .lvl = 59,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_EXTRASENSORY, MOVE_HAIL, MOVE_BLIZZARD, MOVE_AURORAVEIL },
        .ability = Ability_Hidden // Snow Warning
    },
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Clyde_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_BRICKBREAK, MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_ACROBATICS },
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 60,
        .species = SPECIES_VANILLUXE,
        .moves = { MOVE_WEATHERBALL, MOVE_RAINDANCE, MOVE_UPROAR, MOVE_ACIDARMOR },
        .ability = Ability_1 // Ice Body
    },
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Jessie_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_AQUATAIL, MOVE_HELPINGHAND, MOVE_BULLDOZE, MOVE_IRONTAIL },
        .ability = Ability_1 // Schooling
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_James_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_FOLLOWME, MOVE_WISH, MOVE_PROTECT, MOVE_NONE },
        .ability = Ability_2 // Magic Guard
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Mike_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_CRAMORANT,
        .moves = { MOVE_DRILLPECK, MOVE_SURF, MOVE_ICYWIND, MOVE_TAILWIND },
        .ability = Ability_1 // Gulp Missile
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Diane_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_BULLDOZE, MOVE_SWORDSDANCE, MOVE_SHADOWBONE, MOVE_ICYWIND },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Hannibal_Divergent[] = {
    {
        .lvl = 58,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_HEATWAVE, MOVE_TAILWIND, MOVE_AIRCUTTER, MOVE_ICYWIND },
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 59,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DECORATE, MOVE_AROMATICMIST, MOVE_DAZZLINGGLEAM, MOVE_LIGHTSCREEN },
        .ability = Ability_Hidden // Aroma Veil
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Clarice_Divergent[] = {
    {
        .lvl = 58,
        .species = SPECIES_BELLOSSOM,
        .moves = { MOVE_QUIVERDANCE, MOVE_SLEEPPOWDER, MOVE_GIGADRAIN, MOVE_HELPINGHAND },
        .ability = Ability_Hidden // Healer
    },
    {
        .lvl = 59,
        .species = SPECIES_ORICORIO,
        .moves = { MOVE_REVELATIONDANCE, MOVE_AIRSLASH, MOVE_CALMMIND, MOVE_ROOST },
        .ability = Ability_1 // Dancer
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_LeadersDennisAndDee_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_SCALD, MOVE_ICYWIND, MOVE_RECOVER, MOVE_HELPINGHAND },
        .ability = Ability_2 // Competitive
    },
    {
        .lvl = 61,
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_SWORDSDANCE, MOVE_ACROBATICS, MOVE_HIGHJUMPKICK, MOVE_ROOST },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 60,
        .species = SPECIES_INDEEDEE,
        .moves = { MOVE_HELPINGHAND, MOVE_DAZZLINGGLEAM, MOVE_PSYCHIC, MOVE_HEALINGWISH },
        .ability = Ability_Hidden // Psychic Surge
    },
    {
        .lvl = 62,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_HELPINGHAND, MOVE_BLIZZARD, MOVE_LIGHTSCREEN, MOVE_DISCHARGE },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 63,
        .species = SPECIES_RHYPERIOR,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_MEGAHORN, MOVE_HAMMERARM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Lightning Rod
    }
};

// #endregion

// #region Route 24
const struct TrainerMonNoItemDefaultMoves sParty_Route24_PsychicRaya_Divergent[] = {
    { .lvl = 60, .species = SPECIES_DUOSION },
    { .lvl = 61, .species = SPECIES_ALAKAZAM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_DragonTamerDavid_Divergent[] = {
    { .lvl = 61, .species = SPECIES_DRAMPA },
    { .lvl = 61, .species = SPECIES_SALAMENCE },
    { .lvl = 62, .species = SPECIES_CHARIZARD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_PsychicJeff_Divergent[] = {
    { .lvl = 61, .species = SPECIES_INDEEDEE },
    { .lvl = 61, .species = SPECIES_MUSHARNA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_FishermanHumphrey_Divergent[] = {
    { .lvl = 63, .species = SPECIES_GRAPPLOCT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_TriathleteWillow_Divergent[] = {
    { .lvl = 60, .species = SPECIES_BEEDRILL },
    { .lvl = 61, .species = SPECIES_DIGGERSBY },
    { .lvl = 61, .species = SPECIES_LILLIGANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_BlackbeltIrvine_Divergent[] = {
    { .lvl = 58, .species = SPECIES_MEDITITE },
    { .lvl = 58, .species = SPECIES_MEDITITE },
    { .lvl = 59, .species = SPECIES_HITMONLEE },
    { .lvl = 60, .species = SPECIES_HITMONCHAN },
};
// #endregion

// #region Uteyan Ruins
const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacKristian_Divergent[] = {
    { .lvl = 59, .species = SPECIES_DUGTRIO_A },
    { .lvl = 60, .species = SPECIES_GOLURK }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_PsychicHaley_Divergent[] = {
    { .lvl = 63, .species = SPECIES_STARMIE }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacCyril_Divergent[] = {
    { .lvl = 58, .species = SPECIES_GOLETT },
    { .lvl = 59, .species = SPECIES_CHANDELURE },
    { .lvl = 60, .species = SPECIES_GRAVELER_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_SuperNerdMorty_Divergent[] = {
    { .lvl = 59, .species = SPECIES_ZWEILOUS },
    { .lvl = 59, .species = SPECIES_PORYGON2 },
    { .lvl = 59, .species = SPECIES_RAPIDASH }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_ChannelerAgatha_Divergent[] = {
    { .lvl = 60, .species = SPECIES_KLEFKI },
    { .lvl = 60, .species = SPECIES_HONCHKROW }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_LassDorothy_Divergent[] = {
    { .lvl = 57, .species = SPECIES_MANECTRIC },
    { .lvl = 57, .species = SPECIES_KADABRA },
    { .lvl = 58, .species = SPECIES_KRICKETUNE },
    { .lvl = 59, .species = SPECIES_BELLOSSOM },
};
// #endregion

// #region Victory Road
const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerTimothy_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_DREDNAW,
        .moves = { MOVE_HEADBUTT, MOVE_LIQUIDATION, MOVE_HEADSMASH, MOVE_COUNTER },
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 60,
        .species = SPECIES_TORTERRA,
        .moves = { MOVE_WOODHAMMER, MOVE_LEECHSEED, MOVE_CRUNCH, MOVE_HEADLONGRUSH },
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 62,
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_HYDROCANNON, MOVE_RAINDANCE, MOVE_IRONDEFENSE, MOVE_ICEBEAM },
        .ability = Ability_Hidden // Rain dish
    },
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerJonathan_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_ARAQUANID,
        .moves = { MOVE_LIQUIDATION, MOVE_LEECHLIFE, MOVE_HEADBUTT, MOVE_CRUNCH },
        .ability = Ability_1 // Water Bubble
    },
    {
        .lvl = 61,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_BODYSLAM, MOVE_REST, MOVE_SLEEPTALK, MOVE_HIGHHORSEPOWER },
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 62,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_STONEEDGE, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .ability = Ability_1 // Sand Stream
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerSatoshi_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_LEAVANNY,
        .moves = { MOVE_XSCISSOR, MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_FELLSTINGER },
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 61,
        .species = SPECIES_STARAPTOR,
        .moves = { MOVE_BRAVEBIRD, MOVE_ROOST, MOVE_CLOSECOMBAT, MOVE_QUICKATTACK },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 61,
        .species = SPECIES_KINGLER,
        .moves = { MOVE_CRABHAMMER, MOVE_SWORDSDANCE, MOVE_HAMMERARM, MOVE_ROCKSLIDE },
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 62,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_SUPERFANG, MOVE_CRUNCH, MOVE_STOMP },
        .ability = Ability_2 // Strong Jaw
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerCourtney_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_PSYCHIC, MOVE_PERISHSONG, MOVE_DRAININGKISS },
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 59,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_AERIALACE, MOVE_PSYCHOCUT, MOVE_HEADSMASH },
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 59,
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_ZENHEADBUTT, MOVE_UTURN, MOVE_TEETERDANCE },
        .ability = Ability_2 // Queenly Majesty
    },
    {
        .lvl = 60,
        .species = SPECIES_EMPOLEON,
        .moves = { MOVE_DRILLPECK, MOVE_BRINE, MOVE_FLASHCANNON, MOVE_ICEBEAM },
        .ability = Ability_Hidden // Competitive
    },
    {
        .lvl = 61,
        .species = SPECIES_SERPERIOR,
        .moves = { MOVE_LEAFSTORM, MOVE_GIGADRAIN, MOVE_DRAGONPULSE, MOVE_REFLECT },
        .ability = Ability_Hidden // Contrary
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerTheresa_Divergent[] = {
    {
        .lvl = 62,
        .species = SPECIES_PIDGEOT,
        .moves = { MOVE_BRAVEBIRD, MOVE_FEATHERDANCE, MOVE_ROOST, MOVE_HEATWAVE },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 62,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_FLAMETHROWER, MOVE_THUNDER, MOVE_ICEFANG },
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 63,
        .species = SPECIES_BOUFFALANT,
        .moves = { MOVE_MEGAHORN, MOVE_SWORDSDANCE, MOVE_HEADCHARGE, MOVE_ROCKSLIDE },
        .ability = Ability_2 // Sap Sipper
    },
    {
        .lvl = 63,
        .species = SPECIES_BLAZIKEN,
        .moves = { MOVE_BLAZEKICK, MOVE_BOUNCE, MOVE_SKYUPPERCUT, MOVE_FEATHERDANCE },
        .ability = Ability_Hidden // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerAbdul_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_AGGRON,
        .moves = { MOVE_HEADSMASH, MOVE_DOUBLEEDGE, MOVE_IRONTAIL, MOVE_IRONDEFENSE },
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 62,
        .species = SPECIES_DRAPION,
        .moves = { MOVE_THUNDERFANG, MOVE_TOXICSPIKES, MOVE_NIGHTSLASH, MOVE_CROSSPOISON },
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 62,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_WILDCHARGE, MOVE_COIL, MOVE_HEADBUTT, MOVE_FLAMETHROWER },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 62,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_RAINDANCE, MOVE_BLIZZARD },
        .ability = Ability_Hidden // Cute Charm
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerArthur_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_HIGHHORSEPOWER, MOVE_AMNESIA, MOVE_CRUNCH, MOVE_BRICKBREAK },
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 60,
        .species = SPECIES_RHYPERIOR,
        .moves = { MOVE_DRILLRUN, MOVE_MEGAHORN, MOVE_THUNDERPUNCH, MOVE_POISONJAB },
        .ability = Ability_1 // Lightning Rod
    },
    {
        .lvl = 61,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_STEALTHROCK, MOVE_BREAKINGSWIPE, MOVE_ROCKSLIDE, MOVE_IRONTAIL },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 61,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_DOUBLEEDGE, MOVE_UTURN, MOVE_ICEBEAM },
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 61,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_THUNDERWAVE, MOVE_HIDDENPOWER, MOVE_DISCHARGE, MOVE_ROCKSLIDE },
        .ability = Ability_2 // Magnet Pull
    },
    {
        .lvl = 62,
        .species = SPECIES_ELECTRODE,
        .moves = { MOVE_ELECTROBALL, MOVE_EXPLOSION, MOVE_MIRRORCOAT, MOVE_THIEF },
        .ability = Ability_1 // Soundproof
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerKelly_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_ORICORIO_Y,
        .moves = { MOVE_ACROBATICS, MOVE_QUIVERDANCE, MOVE_ICYWIND, MOVE_HURRICANE },
        .ability = Ability_1 // Dancer
    },
    {
        .lvl = 60,
        .species = SPECIES_DONPHAN,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_KNOCKOFF, MOVE_ROCKTOMB, MOVE_ICEFANG },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 61,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_DETECT, MOVE_FLAREBLITZ, MOVE_SWORDSDANCE },
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 62,
        .species = SPECIES_DEWGONG,
        .moves = { MOVE_ICEBEAM, MOVE_AQUATAIL, MOVE_DIVE, MOVE_SHEERCOLD },
        .ability = Ability_1 // Thick Fat
    },
    {
        .lvl = 63,
        .species = SPECIES_MACHAMP,
        .moves = { MOVE_DYNAMICPUNCH, MOVE_HEAVYSLAM, MOVE_POWERUPPUNCH, MOVE_THUNDERPUNCH },
        .ability = Ability_2 // No Guard
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLydia_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_THUNDERPUNCH, MOVE_DOUBLEEDGE, MOVE_EARTHQUAKE, MOVE_EXPLOSION },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 61,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_DISCHARGE, MOVE_THIEF, MOVE_BRICKBREAK, MOVE_FEINT },
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 63,
        .species = SPECIES_TROPIUS,
        .moves = { MOVE_AIRSLASH, MOVE_LEAFSTORM, MOVE_OUTRAGE, MOVE_SYNTHESIS },
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 63,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_MEGAPUNCH, MOVE_SHADOWPUNCH, MOVE_DYNAMICPUNCH, MOVE_FOCUSPUNCH },
        .ability = Ability_1 // Iron Fist
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerRobin_Divergent[] = {
    {
        .lvl = 62,
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 63,
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 62,
        .species = SPECIES_GRAPPLOCT,
        .moves = { MOVE_CIRCLETHROW, MOVE_KNOCKOFF, MOVE_MUDSHOT, MOVE_DUALCHOP },
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 64,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYCHIC, MOVE_REFLECT, MOVE_RECOVER, MOVE_SHADOWBALL },
        .ability = Ability_1 // Overcoat
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLuigi_Divergent[] = {
    { // Unchanged
        .lvl = 63,
        .species = SPECIES_RILLABOOM,
        .moves = { MOVE_DRUMBEATING, MOVE_BOOMBURST, MOVE_DRAINPUNCH, MOVE_SCREECH },
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 64,
        .species = SPECIES_CINDERACE,
        .moves = { MOVE_PYROBALL, MOVE_COUNTER, MOVE_BOUNCE, MOVE_QUICKATTACK },
        .ability = Ability_Hidden // Libero
    },
    {
        .lvl = 64,
        .species = SPECIES_INTELEON,
        .moves = { MOVE_SNIPESHOT, MOVE_UTURN, MOVE_SHADOWBALL, MOVE_ICEBEAM },
        .ability = Ability_Hidden // Sniper
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerDahlia_Divergent[] = {
    {
        .lvl = 63,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_PETALBLIZZARD, MOVE_SYNTHESIS, MOVE_SUNNYDAY },
        .ability = Ability_2 // Own Tempo
    },
    {
        .lvl = 64,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_FLAMETHROWER, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_NIGHTSLASH },
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 64,
        .species = SPECIES_HITMONTOP,
        .moves = { MOVE_TRIPLEKICK, MOVE_SUCKERPUNCH, MOVE_CLOSECOMBAT, MOVE_COUNTER },
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_NurseCelia_Divergent[] = {
    {
        .lvl = 63,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_HYPERVOICE, MOVE_WISH, MOVE_ZENHEADBUTT, MOVE_REFLECT },
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 64,
        .species = SPECIES_MEGANIUM,
        .moves = { MOVE_SUNNYDAY, MOVE_SOLARBEAM, MOVE_SYNTHESIS, MOVE_BODYSLAM },
        .ability = Ability_1 // Overgrow
    }
};
// #endregion

// #region Ascension Tower
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Hannah_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_STEALTHROCK, MOVE_THUNDERWAVE, MOVE_HEAVYSLAM, MOVE_DISCHARGE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Magnet Pull
    },
    {
        .lvl = 65,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_SUBSTITUTE, MOVE_UTURN },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 66,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_FIREPUNCH, MOVE_EARTHQUAKE, MOVE_WILDCHARGE, MOVE_BRICKBREAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 66,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_NIGHTSLASH, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_SLASH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 67,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_XSCISSOR, MOVE_POISONJAB, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Lucas_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYSHOCK, MOVE_CALMMIND, MOVE_SHADOWBALL, MOVE_ENERGYBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 66,
        .species = SPECIES_YANMEGA,
        .moves = { MOVE_BUGBUZZ, MOVE_AIRSLASH, MOVE_UTURN, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 67,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_CRUNCH, MOVE_DRAGONRUSH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Strong Jaw
    },
    {
        .lvl = 67,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_WOODHAMMER, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 68,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_FLAMETHROWER, MOVE_VOLTSWITCH, MOVE_SNARL, MOVE_DISCHARGE },
        .heldItem = ITEM_MANECTITE,
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Jenna_Divergent[] = {
    {
        .lvl = 67,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_FAKEOUT, MOVE_HIGHJUMPKICK, MOVE_BLAZEKICK, MOVE_KNOCKOFF },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 67,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SACREDSWORD, MOVE_IRONHEAD, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 68,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 68,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_DARKPULSE, MOVE_DESTINYBOND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 69,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_HYPERVOICE, MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_ROOST },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Thomas_Divergent[] = {
    {
        .lvl = 68,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 68,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NASTYPLOT, MOVE_ROOST, MOVE_DARKPULSE, MOVE_HEATWAVE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 69,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 69,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_DISCHARGE, MOVE_TRIATTACK, MOVE_ICEBEAM },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 70,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_SANDSTORM, MOVE_CURSE, MOVE_IRONTAIL, MOVE_EARTHQUAKE },
        .heldItem = ITEM_STEELIXITE,
        .ability = Ability_2 // Sturdy
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_Champion_Selene_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_SYNTHESIS, MOVE_ENERGYBALL, MOVE_POLLENPUFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 72,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 72,
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRAGONDARTS, MOVE_UTURN, MOVE_PHANTOMFORCE, MOVE_DRACOMETEOR },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 72,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_METEORMASH, MOVE_BULLETPUNCH, MOVE_ZENHEADBUTT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_METAGROSSITE,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 73,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_WATERSHURIKEN, MOVE_SCALD, MOVE_DARKPULSE, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Battle Bond
    },
    {
        .lvl = 74,
        .species = SPECIES_VICTINI,
        .moves = { MOVE_VCREATE, MOVE_WILDCHARGE, MOVE_ZENHEADBUTT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_1 // Victory Star
    }
};

// #endregion

// #region Gym Leader Rematches
const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_RILLABOOM,
        .moves = { MOVE_BOOMBURST, MOVE_DRUMBEATING, MOVE_GRASSYGLIDE, MOVE_GRASSYTERRAIN },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 70,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_KNOCKOFF, MOVE_BLAZEKICK, MOVE_FAKEOUT, MOVE_HIGHJUMPKICK },
        .heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 70,
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_GRASSYGLIDE, MOVE_HIGHJUMPKICK, MOVE_PLAYROUGH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Queenly Majesty
    },
    {
        .lvl = 70,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_TERRAINPULSE, MOVE_REST, MOVE_BODYSLAM, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 72,
        .species = SPECIES_TANGROWTH,
        .moves = { MOVE_LEECHSEED, MOVE_ANCIENTPOWER, MOVE_KNOCKOFF, MOVE_GRASSYTERRAIN },
        .heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_Hidden // Regenerator
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_DISCHARGE, MOVE_FLASHCANNON, MOVE_ELECTRICTERRAIN, MOVE_HIDDENPOWER },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 70,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_THUNDERPUNCH, MOVE_LIGHTSCREEN, MOVE_ROCKTOMB, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 70,
        .species = SPECIES_LUXRAY,
        .moves = { MOVE_DISCHARGE, MOVE_FIREFANG, MOVE_ELECTRICTERRAIN, MOVE_CRUNCH },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_2 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_ARCTOZOLT,
        .moves = { MOVE_FREEZEDRY, MOVE_BOLTBEAK, MOVE_ICICLECRASH, MOVE_PLUCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Static
    },
    {
        .lvl = 72,
        .species = SPECIES_AGGRON,
        .moves = { MOVE_SURF, MOVE_DOUBLEEDGE, MOVE_HEADSMASH, MOVE_POWERUPPUNCH },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_2 // Rock Head
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_INDEEDEE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_MYSTICALFIRE, MOVE_DRAINPUNCH },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Psychic Surge
    },
    {
        .lvl = 70,
        .species = SPECIES_DELPHOX,
        .moves = { MOVE_PSYCHICTERRAIN, MOVE_WILLOWISP, MOVE_LIGHTSCREEN, MOVE_FLAMETHROWER },
        .heldItem = ITEM_PSYCHIC_SEED,
        .ability = Ability_Hidden // Magician
    },
    {
        .lvl = 70,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYSHOCK, MOVE_EXPANDINGFORCE, MOVE_RECOVER, MOVE_SHADOWBALL },
        .heldItem = ITEM_PSYCHIC_SEED,
        .ability = Ability_Hidden // Magic Guard
    },
    {
        .lvl = 70,
        .species = SPECIES_RAPIDASH_G,
        .moves = { MOVE_MEGAHORN, MOVE_PSYCHICTERRAIN, MOVE_DAZZLINGGLEAM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Anticipation
    },
    {
        .lvl = 72,
        .species = SPECIES_XATU,
        .moves = { MOVE_AIRSLASH, MOVE_PSYCHIC, MOVE_WISH, MOVE_UTURN },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_AROMATISSE,
        .moves = { MOVE_MISTYTERRAIN, MOVE_DAZZLINGGLEAM, MOVE_CHARM, MOVE_HEALBLOCK },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 70,
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_TERRAINPULSE, MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_BRICKBREAK },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 70,
        .species = SPECIES_VILEPLUME,
        .moves = { MOVE_PETALDANCE, MOVE_SLUDGEBOMB, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Effect Spore
    },
    {
        .lvl = 70,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_MISTYTERRAIN, MOVE_HYPERVOICE, MOVE_WISH, MOVE_PROTECT },
        .heldItem = ITEM_MISTY_SEED,
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 72,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_THRASH, MOVE_IRONHEAD, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Steely Spirit
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_ROTOM_HEAT,
        .moves = { MOVE_WILLOWISP, MOVE_FIREBLAST, MOVE_DISCHARGE, MOVE_PAINSPLIT },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 70,
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_SCALD, MOVE_RECOVER, MOVE_EARTHPOWER, MOVE_ICYWIND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Unaware
    },
    {
        .lvl = 70,
        .species = SPECIES_NINETALES,
        .moves = { MOVE_BURNINGJEALOUSY, MOVE_EXTRASENSORY, MOVE_NASTYPLOT, MOVE_HEX },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Drought
    },
    {
        .lvl = 70,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_FLING, MOVE_NIGHTSLASH, MOVE_SCREECH, MOVE_CROSSCHOP },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 72,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_FLAMETHROWER, MOVE_ENERGYBALL },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Flame Body
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_TOGEDEMARU,
        .moves = { MOVE_NUZZLE, MOVE_ZINGZAP, MOVE_SPIKYSHIELD, MOVE_IRONTAIL },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 70,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_FORCEPALM, MOVE_SMELLINGSALTS, MOVE_BRINE, MOVE_SEISMICTOSS },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 70,
        .species = SPECIES_AGGRON,
        .moves = { MOVE_SMELLINGSALTS, MOVE_THUNDERWAVE, MOVE_IRONHEAD, MOVE_NONE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 70,
        .species = SPECIES_DRAMPA,
        .moves = { MOVE_GLARE, MOVE_OUTRAGE, MOVE_ICYWIND, MOVE_THUNDERBOLT },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_2 // Sap Sipper
    },
    {
        .lvl = 72,
        .species = SPECIES_SAWSBUCK_SUMMER,
        .moves = { MOVE_THUNDERWAVE, MOVE_SWORDSDANCE, MOVE_ZENHEADBUTT, MOVE_HEADBUTT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Serene Grace
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_SPORE, MOVE_DREAMEATER, MOVE_NIGHTMARE, MOVE_RECOVER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 70,
        .species = SPECIES_MUSHARNA,
        .moves = { MOVE_HYPNOSIS, MOVE_DREAMEATER, MOVE_MOONBLAST, MOVE_PSYCHIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 70,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_YAWN, MOVE_REST, MOVE_SNORE, MOVE_SLEEPTALK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 70,
        .species = SPECIES_JYNX,
        .moves = { MOVE_HYPNOSIS, MOVE_PERISHSONG, MOVE_MEANLOOK, MOVE_PSYCHIC },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_2 // Forewarn
    },
    {
        .lvl = 72,
        .species = SPECIES_TANGROWTH,
        .moves = { MOVE_SLEEPPOWDER, MOVE_ANCIENTPOWER, MOVE_KNOCKOFF, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Regenerator
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_QWILFISH,
        .moves = { MOVE_TOXIC, MOVE_TOXICSPIKES, MOVE_AQUATAIL, MOVE_VENOSHOCK },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Point
    },
    {
        .lvl = 70,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_TOXIC, MOVE_HEX, MOVE_SHADOWBALL, MOVE_DARKPULSE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 70,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_SCREECH, MOVE_POISONJAB, MOVE_MUDDYWATER, MOVE_ROCKSLIDE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_2 // Poison Touch
    },
    {
        .lvl = 70,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_HAMMERARM, MOVE_LIGHTSCREEN, MOVE_REFLECT, MOVE_SPIRITBREAK },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 72,
        .species = SPECIES_MACHAMP,
        .moves = { MOVE_FACADE, MOVE_DRAINPUNCH, MOVE_STONEEDGE, MOVE_BULKUP },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Guts
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_NINETALES,
        .moves = { MOVE_FLAMETHROWER, MOVE_WILLOWISP, MOVE_EXTRASENSORY, MOVE_SHADOWBALL },
        .heldItem = ITEM_HEAT_ROCK,
        .ability = Ability_Hidden // Drought
    },
    {
        .lvl = 70,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_TAILWIND, MOVE_HEATWAVE, MOVE_ACROBATICS, MOVE_SUNNYDAY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // MOXIE
    },
    {
        .lvl = 70,
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_SOLARBEAM, MOVE_SLUDGEBOMB, MOVE_SYNTHESIS, MOVE_GROWTH },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Chlorophyll
    },
    {
        .lvl = 70,
        .species = SPECIES_CHARIZARD,
        .moves = { MOVE_SUNNYDAY, MOVE_FLAREBLITZ, MOVE_SOLARBEAM, MOVE_AIRSLASH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Solar Power
    },
    {
        .lvl = 72,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_GROWTH, MOVE_SUNNYDAY, MOVE_SOLARBEAM, MOVE_SYNTHESIS },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_SURF, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 70,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_THUNDER, MOVE_FLASHCANNON, MOVE_MAGNETRISE, MOVE_TRIATTACK },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 70,
        .species = SPECIES_STARMIE,
        .moves = { MOVE_PSYCHIC, MOVE_THUNDER, MOVE_SURF, MOVE_RECOVER },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_2 // Natural Cure
    },
    {
        .lvl = 70,
        .species = SPECIES_ARMALDO,
        .moves = { MOVE_CRUSHCLAW, MOVE_ROCKBLAST, MOVE_AQUATAIL, MOVE_BRINE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 72,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_PSYCHIC, MOVE_ATTRACT, MOVE_FAKETEARS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_EARTHQUAKE, MOVE_STONEEDGE, MOVE_FIREFANG, MOVE_CRUNCH },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 70,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DISCHARGE, MOVE_POWERGEM, MOVE_FLASHCANNON },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Sand Force
    },
    {
        .lvl = 70,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_CRUNCH, MOVE_LEECHLIFE, MOVE_OUTRAGE },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_Hidden // Sand Rush
    },
    {
        .lvl = 70,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SANDSTORM, MOVE_UTURN, MOVE_CRABHAMMER, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Sand Veil
    },
    {
        .lvl = 72,
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_BULLDOZE, MOVE_WRAP, MOVE_THUNDERFANG, MOVE_ROCKSLIDE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Spit
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_DAZZLINGGLEAM, MOVE_FREEZEDRY },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 70,
        .species = SPECIES_ARCTOZOLT,
        .moves = { MOVE_ICICLECRASH, MOVE_BOLTBEAK, MOVE_ELECTROBALL, MOVE_IRONTAIL },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Slush Rush
    },
    {
        .lvl = 70,
        .species = SPECIES_SANDSLASH_A,
        .moves = { MOVE_IRONHEAD, MOVE_HAIL, MOVE_ICICLESPEAR, MOVE_SWORDSDANCE },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Snow Cloak
    },
    {
        .lvl = 70,
        .species = SPECIES_SHELGON,
        .moves = { MOVE_CRUNCH, MOVE_FLAMETHROWER, MOVE_DRAGONCLAW, MOVE_THUNDERFANG },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 72,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_WOODHAMMER, MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_BRICKBREAK },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Snow Warning
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_XATU,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_PSYCHIC, MOVE_UTURN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 70,
        .species = SPECIES_SWANNA,
        .moves = { MOVE_TAILWIND, MOVE_ROOST, MOVE_BRAVEBIRD, MOVE_HURRICANE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Big Pecks
    },
    {
        .lvl = 70,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_ACIDARMOR, MOVE_RECOVER, MOVE_PSYSHOCK, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 70,
        .species = SPECIES_RAPIDASH_G,
        .moves = { MOVE_HEALINGWISH, MOVE_PSYCHOCUT, MOVE_MEGAHORN, MOVE_MISTYTERRAIN },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_2 // Pastel Veil
    },
    {
        .lvl = 72,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_WISH, MOVE_SAFEGUARD, MOVE_SURF, MOVE_PROTECT },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_2 // Regenerator
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_TRICKROOM, MOVE_DRAGONHAMMER, MOVE_SEEDBOMB, MOVE_LEECHSEED },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Frisk
    },
    {
        .lvl = 70,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYCHIC, MOVE_RECOVER, MOVE_LIGHTSCREEN, MOVE_FIREPUNCH },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 70,
        .species = SPECIES_ARCANINE,
        .moves = { MOVE_BURNUP, MOVE_FLAMETHROWER, MOVE_PLAYROUGH, MOVE_MORNINGSUN },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_DOUBLADE,
        .moves = { MOVE_SACREDSWORD, MOVE_SWORDSDANCE, MOVE_NIGHTSLASH, MOVE_AERIALACE },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // No Guard
    },
    {
        .lvl = 72,
        .species = SPECIES_XATU,
        .moves = { MOVE_PSYSHOCK, MOVE_CALMMIND, MOVE_TRICKROOM, MOVE_AIRSLASH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_PERISHSONG, MOVE_ICEBEAM, MOVE_HYDROPUMP, MOVE_PROTECT },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_DUGTRIO,
        .moves = { MOVE_NIGHTSLASH, MOVE_EARTHQUAKE, MOVE_THIEF, MOVE_STEALTHROCK },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_2 // Arena Trap
    },
    {
        .lvl = 70,
        .species = SPECIES_BANETTE,
        .moves = { MOVE_SHADOWBALL, MOVE_CURSE, MOVE_SUCKERPUNCH, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Perish Body
    },
    {
        .lvl = 70,
        .species = SPECIES_JYNX,
        .moves = { MOVE_MEANLOOK, MOVE_LOVELYKISS, MOVE_PERISHSONG, MOVE_DRAININGKISS },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Forewarn
    },
    {
        .lvl = 72,
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_DESTINYBOND, MOVE_TAILWIND, MOVE_STRENGTHSAP, MOVE_SHADOWBALL },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Aftermath
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Tough Claws
    },
    {
        .lvl = 70,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 70,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 70,
        .species = SPECIES_SWALOT,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Liquid Ooze
    },
    {
        .lvl = 72,
        .species = SPECIES_INTELEON,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Sniper
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_COSMICPOWER, MOVE_STOREDPOWER, MOVE_WISH, MOVE_THUNDERBOLT },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_2 // Magic Guard
    },
    {
        .lvl = 70,
        .species = SPECIES_DRAPION,
        .moves = { MOVE_ACUPRESSURE, MOVE_CROSSPOISON, MOVE_XSCISSOR, MOVE_CRUNCH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Sniper
    },
    {
        .lvl = 70,
        .species = SPECIES_INCINEROAR,
        .moves = { MOVE_PARTINGSHOT, MOVE_FAKEOUT, MOVE_DARKESTLARIAT, MOVE_CROSSCHOP },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_SWORDSDANCE, MOVE_LIQUIDATION, MOVE_LEECHLIFE },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 72,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_CALMMIND, MOVE_RECOVER, MOVE_CHARM, MOVE_PSYCHIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Overcoat
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_ORICORIO,
        .moves = { MOVE_BATONPASS, MOVE_QUIVERDANCE, MOVE_REVELATIONDANCE, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Dancer
    },
    {
        .lvl = 70,
        .species = SPECIES_AMBIPOM,
        .moves = { MOVE_BATONPASS, MOVE_NASTYPLOT, MOVE_BRICKBREAK, MOVE_ICEPUNCH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Technician
    },
    {
        .lvl = 70,
        .species = SPECIES_BLAZIKEN,
        .moves = { MOVE_BATONPASS, MOVE_FOCUSENERGY, MOVE_BULKUP, MOVE_BLAZEKICK },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 70,
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_BATONPASS, MOVE_SUBSTITUTE, MOVE_STOCKPILE, MOVE_SHADOWBALL },
        .heldItem = ITEM_GHOST_GEM,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 72,
        .species = SPECIES_FURRET,
        .moves = { MOVE_BATONPASS, MOVE_AMNESIA, MOVE_COIL, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Keen Eye
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_MEDICHAM,
        .moves = { MOVE_PSYCHUP, MOVE_HIGHJUMPKICK, MOVE_ZENHEADBUTT, MOVE_FIREPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Pure Power
    },
    {
        .lvl = 70,
        .species = SPECIES_AROMATISSE,
        .moves = { MOVE_PSYCHUP, MOVE_DAZZLINGGLEAM, MOVE_FAKETEARS, MOVE_PSYCHIC },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 70,
        .species = SPECIES_BUTTERFREE,
        .moves = { MOVE_PSYCHUP, MOVE_QUIVERDANCE, MOVE_AIRSLASH, MOVE_BUGBUZZ },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 70,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYCHUP, MOVE_CALMMIND, MOVE_FOCUSBLAST, MOVE_CHARGEBEAM },
        .heldItem = ITEM_PSYCHIC_GEM,
        .ability = Ability_Hidden // Magic Guard
    },
    {
        .lvl = 72,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_PSYCHUP, MOVE_BLIZZARD, MOVE_TRICK, MOVE_DISCHARGE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_SWOOBAT,
        .moves = { MOVE_AMNESIA, MOVE_AIRSLASH, MOVE_AMNESIA, MOVE_PSYCHIC },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_Hidden // Simple
    },
    {
        .lvl = 70,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_PROTECT, MOVE_DRAGONDANCE, MOVE_FIERYDANCE, MOVE_DRAINPUNCH },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 70,
        .species = SPECIES_CRUSTLE,
        .moves = { MOVE_SHELLSMASH, MOVE_XSCISSOR, MOVE_ROCKWRECKER, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Weak Armor
    },
    {
        .lvl = 70,
        .species = SPECIES_SERPERIOR,
        .moves = { MOVE_LEAFSTORM, MOVE_LEECHSEED, MOVE_DRAGONPULSE, MOVE_KNOCKOFF },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 72,
        .species = SPECIES_DRAPION,
        .moves = { MOVE_NIGHTSLASH, MOVE_CROSSPOISON, MOVE_KNOCKOFF, MOVE_AGILITY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Sniper
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FLAREBLITZ, MOVE_BRUTALSWING, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 70,
        .species = SPECIES_PINSIR,
        .moves = { MOVE_CLOSECOMBAT, MOVE_LUNGE, MOVE_AERIALACE, MOVE_ROCKTOMB },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Mold Breaker
    },
    {
        .lvl = 70,
        .species = SPECIES_DREDNAW,
        .moves = { MOVE_LIQUIDATION, MOVE_JAWLOCK, MOVE_HEADSMASH, MOVE_COUNTER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 70,
        .species = SPECIES_CRAMORANT,
        .moves = { MOVE_DIVE, MOVE_SURF, MOVE_ROOST, MOVE_AERIALACE },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 72,
        .species = SPECIES_EISCUE,
        .moves = { MOVE_SURF, MOVE_BLIZZARD, MOVE_BODYSLAM, MOVE_FLIPTURN },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Ice Face
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_AZUMARILL,
        .moves = { MOVE_PLAYROUGH, MOVE_AQUATAIL, MOVE_GRASSKNOT, MOVE_ICYWIND },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Sap Sipper
    },
    {
        .lvl = 70,
        .species = SPECIES_ROTOM_HEAT,
        .moves = { MOVE_OVERHEAT, MOVE_VOLTSWITCH, MOVE_THUNDERWAVE, MOVE_HEX },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 70,
        .species = SPECIES_MARACTUS,
        .moves = { MOVE_GIGADRAIN, MOVE_COTTONGUARD, MOVE_SPIKYSHIELD, MOVE_LEECHSEED },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 70,
        .species = SPECIES_TYPHLOSION,
        .moves = { MOVE_FLAMETHROWER, MOVE_EXTRASENSORY, MOVE_HIDDENPOWER, MOVE_WILLOWISP },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Flash Fire
    },
    {
        .lvl = 72,
        .species = SPECIES_ZEBSTRIKA,
        .moves = { MOVE_DISCHARGE, MOVE_STOMP, MOVE_FLAMECHARGE, MOVE_DOUBLEKICK },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Motor Drive
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_VILEPLUME,
        .moves = { MOVE_LEECHSEED, MOVE_TOXIC, MOVE_MOONBLAST, MOVE_PETALDANCE },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Effect Spore
    },
    {
        .lvl = 70,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_DRAGONPULSE, MOVE_ROOST },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 70,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SURF, MOVE_FLIPTURN, MOVE_ICEBEAM },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_Hidden // Cute Charm
    },
    {
        .lvl = 70,
        .species = SPECIES_POLTEAGEIST,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_SHELLSMASH, MOVE_STRENGTHSAP },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 72,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_PROTECT, MOVE_DETECT, MOVE_RECOVER, MOVE_BODYSLAM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_UTURN, MOVE_CRABHAMMER, MOVE_SUBSTITUTE },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 70,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_HEADLONGRUSH, MOVE_FORCEPALM, MOVE_KNOCKOFF, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 70,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_LASTRESORT, MOVE_CHARM, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Quick Feet
    },
    {
        .lvl = 70,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_LEECHSEED, MOVE_GIGADRAIN, MOVE_DRAGONHAMMER, MOVE_PSYSHOCK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_EARTHQUAKE, MOVE_ICYWIND },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_SWANNA,
        .moves = { MOVE_HURRICANE, MOVE_RAINDANCE, MOVE_SURF, MOVE_ROOST },
        .heldItem = ITEM_CELL_BATTERY,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 70,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_EARTHQUAKE, MOVE_YAWN, MOVE_ROCKSLIDE, MOVE_ERUPTION },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 70,
        .species = SPECIES_SANDSLASH_A,
        .moves = { MOVE_ICICLESPEAR, MOVE_RAPIDSPIN, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Snow Cloak
    },
    {
        .lvl = 72,
        .species = SPECIES_HYDREIGON,
        .moves = { MOVE_DRAGONDANCE, MOVE_CRUNCH, MOVE_OUTRAGE, MOVE_ICEFANG },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_DELPHOX,
        .moves = { MOVE_SWITCHEROO, MOVE_FUTURESIGHT, MOVE_FIREBLAST, MOVE_PSYCHIC },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Magician
    },
    {
        .lvl = 70,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_REST, MOVE_HEX, MOVE_STUNSPORE, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 70,
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_THIEF, MOVE_FLING, MOVE_FLYINGPRESS, MOVE_BOUNCE },
        .heldItem = ITEM_RAZOR_CLAW,
        .ability = Ability_2 // UNBURDEN
    },
    {
        .lvl = 70,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_REST, MOVE_RECYCLE, MOVE_CURSE, MOVE_BODYSLAM },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 72,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_TRICK, MOVE_CALMMIND, MOVE_SHADOWBALL, MOVE_PSYCHIC },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Magic Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_ZANGOOSE,
        .moves = { MOVE_EMBARGO, MOVE_XSCISSOR, MOVE_DETECT, MOVE_CRUSHCLAW },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Toxic Boost
    },
    {
        .lvl = 70,
        .species = SPECIES_CHARIZARD,
        .moves = { MOVE_DRAGONCLAW, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_WILLOWISP },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 70,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_THIEF, MOVE_FLING, MOVE_ACROBATICS, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_Hidden // Protean
    },
    {
        .lvl = 70,
        .species = SPECIES_GRAPPLOCT,
        .moves = { MOVE_KNOCKOFF, MOVE_DOUBLEHIT, MOVE_TOPSYTURVY, MOVE_OCTOLOCK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 72,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_EMBARGO, MOVE_KNOCKOFF, MOVE_SHADOWBALL, MOVE_HAZE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Cursed Body
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_SWITCHEROO, MOVE_THUNDERWAVE, MOVE_DRAININGKISS, MOVE_FLASHCANNON },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 70,
        .species = SPECIES_BANETTE,
        .moves = { MOVE_TRICK, MOVE_SHADOWBALL, MOVE_SHADOWSNEAK, MOVE_WILLOWISP },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Frisk
    },
    {
        .lvl = 70,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_TRICK, MOVE_WISH, MOVE_MOONBLAST, MOVE_METRONOME },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Magic Guard
    },
    {
        .lvl = 70,
        .species = SPECIES_FURRET,
        .moves = { MOVE_TRICK, MOVE_HYPERVOICE, MOVE_SURF, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_Hidden // Frisk
    },
    {
        .lvl = 72,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_TRICK, MOVE_CHARM, MOVE_RECOVER, MOVE_THUNDERBOLT },
        .heldItem = ITEM_STICKY_BARB,
        .ability = Ability_1 // Overcoat
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_ROTOM_FAN,
        .moves = { MOVE_DISCHARGE, MOVE_AIRSLASH, MOVE_SUBSTITUTE, MOVE_DARKPULSE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 70,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_EARTHQUAKE, MOVE_DRAINPUNCH, MOVE_HYPERVOICE, MOVE_STEALTHROCK },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Poison Touch
    },
    {
        .lvl = 70,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_TAILWIND, MOVE_ROOST, MOVE_ACROBATICS, MOVE_HEATWAVE },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_1 // Insomnia
    },
    {
        .lvl = 70,
        .species = SPECIES_MARACTUS,
        .moves = { MOVE_SPIKES, MOVE_SUCKERPUNCH, MOVE_SPIKYSHIELD, MOVE_SYNTHESIS },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 72,
        .species = SPECIES_STARMIE,
        .moves = { MOVE_SURF, MOVE_CHARGEBEAM, MOVE_BLIZZARD, MOVE_WHIRLPOOL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Natural Cure
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_HITMONCHAN,
        .moves = { MOVE_FAKEOUT, MOVE_QUICKGUARD, MOVE_BULLETPUNCH, MOVE_FIREPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Iron Fist
    },
    {
        .lvl = 70,
        .species = SPECIES_ARCANINE,
        .moves = { MOVE_HELPINGHAND, MOVE_FLAREBLITZ, MOVE_SNARL, MOVE_WILDCHARGE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_XATU,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_NIGHTSHADE, MOVE_TAILWIND },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 70,
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_STRENGTHSAP, MOVE_SHADOWBALL, MOVE_TAILWIND, MOVE_THUNDERBOLT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_Hidden // Flare Boost
    },
    {
        .lvl = 72,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_METEORMASH, MOVE_FOLLOWME, MOVE_LIFEDEW, MOVE_SAFEGUARD },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Unaware
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_DEDENNE,
        .moves = { MOVE_DISCHARGE, MOVE_PLAYROUGH, MOVE_PARABOLICCHARGE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Plus
    },
    {
        .lvl = 70,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_DISCHARGE, MOVE_ROAR, MOVE_OVERHEAT, MOVE_SNARL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Minus
    },
    {
        .lvl = 70,
        .species = SPECIES_ARCTOZOLT,
        .moves = { MOVE_ICYWIND, MOVE_BLIZZARD, MOVE_HYPERVOICE, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_EXPLOSION, MOVE_EARTHQUAKE, MOVE_DISCHARGE, MOVE_CURSE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Galvanize
    },
    {
        .lvl = 72,
        .species = SPECIES_ELECTRODE,
        .moves = { MOVE_EXPLOSION, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Aftermath
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PRIMARINA,
        .moves = { MOVE_SPARKLINGARIA, MOVE_HYPERVOICE, MOVE_DAZZLINGGLEAM, MOVE_ENERGYBALL },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Liquid Voice
    },
    {
        .lvl = 70,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_HEATWAVE, MOVE_POLTERGEIST, MOVE_DARKPULSE, MOVE_HEALBLOCK },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 70,
        .species = SPECIES_RILLABOOM,
        .moves = { MOVE_BOOMBURST, MOVE_ROCKSLIDE, MOVE_KNOCKOFF, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 70,
        .species = SPECIES_CHESNAUGHT,
        .moves = { MOVE_ROCKSLIDE, MOVE_GRASSPLEDGE, MOVE_SPIKYSHIELD, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 72,
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_WATERSPOUT, MOVE_ICYWIND, MOVE_ROCKSLIDE, MOVE_WATERPLEDGE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Rain Dish
    }
};
// #endregion
// #region Route 13 Cave
const struct TrainerMonItemCustomMoves sParty_Route13Cave_TeamPlutoLeaderKurtis_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_IRONHEAD, MOVE_SACREDSWORD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 72,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_HEAVYSLAM, MOVE_ROCKSLIDE, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 72,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 72,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_ROOST, MOVE_NASTYPLOT, MOVE_HEATWAVE, MOVE_DARKPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 73,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_MUDDYWATER, MOVE_RECOVER, MOVE_DAZZLINGGLEAM, MOVE_BLIZZARD },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 74,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_DARKPULSE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    },
};
// #endregion
// #region Elite Four Rematches
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_HannahRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_STEALTHROCK, MOVE_THUNDERWAVE, MOVE_HEAVYSLAM, MOVE_DISCHARGE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Magnet Pull
    },
    {
        .lvl = 72,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_SUBSTITUTE, MOVE_UTURN },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 72,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_FIREPUNCH, MOVE_EARTHQUAKE, MOVE_WILDCHARGE, MOVE_BRICKBREAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 72,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_NIGHTSLASH, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_SLASH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 73,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_XSCISSOR, MOVE_POISONJAB, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_LucasRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_SHADOWBALL, MOVE_ENERGYBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 72,
        .species = SPECIES_YANMEGA,
        .moves = { MOVE_BUGBUZZ, MOVE_AIRSLASH, MOVE_UTURN, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 72,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_CRUNCH, MOVE_DRAGONRUSH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Strong Jaw
    },
    {
        .lvl = 72,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_WOODHAMMER, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_FLAMETHROWER, MOVE_VOLTSWITCH, MOVE_SNARL, MOVE_DISCHARGE },
        .heldItem = ITEM_MANECTITE,
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_JennaRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_FAKEOUT, MOVE_HIGHJUMPKICK, MOVE_BLAZEKICK, MOVE_KNOCKOFF },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 72,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SACREDSWORD, MOVE_IRONHEAD, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 72,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 72,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_DARKPULSE, MOVE_DESTINYBOND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 73,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_HYPERVOICE, MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_ROOST },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_ThomasRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 72,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NASTYPLOT, MOVE_ROOST, MOVE_DARKPULSE, MOVE_HEATWAVE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 72,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 72,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_DISCHARGE, MOVE_TRIATTACK, MOVE_ICEBEAM },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 73,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_SANDSTORM, MOVE_CURSE, MOVE_IRONTAIL, MOVE_EARTHQUAKE },
        .heldItem = ITEM_STEELIXITE,
        .ability = Ability_2 // Sturdy
    }
};
// #endregion
// #region Title Defense
const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_MUDDYWATER, MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_SHADOWBALL },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Jolteon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_HIDDENPOWER, MOVE_VOLTSWITCH, MOVE_SHADOWBALL },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Flareon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_BODYSLAM, MOVE_DIG, MOVE_WILLOWISP },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Guts
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Espeon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_PSYCHIC, MOVE_MORNINGSUN, MOVE_PSYCHUP, MOVE_SHADOWBALL },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Magic Bounce
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Umbreon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_SNARL, MOVE_TOXIC, MOVE_ROAR },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Leafeon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SYNTHESIS, MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Glaceon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_HAIL, MOVE_AURORAVEIL, MOVE_FREEZEDRY, MOVE_CHARM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Sylveon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 75,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_WISH, MOVE_LIGHTSCREEN, MOVE_SHADOWBALL, MOVE_PLAYROUGH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_YoungsterJoey_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ZIGZAGOON,
        .moves = { MOVE_HEADBUTT, MOVE_BELLYDRUM, MOVE_FLAIL, MOVE_THUNDER },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Quick Feet
    },
    {
        .lvl = 73,
        .species = SPECIES_ZIGZAGOON_G,
        .moves = { MOVE_SURF, MOVE_ICEBEAM, MOVE_IRONTAIL, MOVE_SEEDBOMB },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Gluttony
    },
    {
        .lvl = 73,
        .species = SPECIES_LINOONE,
        .moves = { MOVE_SLASH, MOVE_SWITCHEROO, MOVE_HONECLAWS, MOVE_FLING },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 73,
        .species = SPECIES_LINOONE_G,
        .moves = { MOVE_NIGHTSLASH, MOVE_HONECLAWS, MOVE_GIGAIMPACT, MOVE_THIEF },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 74,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_DOUBLEEDGE, MOVE_PINMISSILE, MOVE_NIGHTSLASH, MOVE_CROSSCHOP },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 75,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_OBSTRUCT, MOVE_CROSSPOISON, MOVE_XSCISSOR, MOVE_KNOCKOFF },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_WithVictini_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_SYNTHESIS, MOVE_ENERGYBALL, MOVE_POLLENPUFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 73,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 73,
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRAGONDARTS, MOVE_UTURN, MOVE_PHANTOMFORCE, MOVE_DRACOMETEOR },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 73,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_METEORMASH, MOVE_BULLETPUNCH, MOVE_ZENHEADBUTT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_METAGROSSITE,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 74,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_WATERSHURIKEN, MOVE_SCALD, MOVE_DARKPULSE, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Battle Bond
    },
    {
        .lvl = 75,
        .species = SPECIES_VICTINI,
        .moves = { MOVE_VCREATE, MOVE_WILDCHARGE, MOVE_ZENHEADBUTT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_1 // Victory Star
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_Divergent[] = {
    {
        .lvl = 75,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_DAZZLINGGLEAM, MOVE_NASTYPLOT },
        .heldItem = ITEM_BABIRI_BERRY,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 73,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_SYNTHESIS, MOVE_ENERGYBALL, MOVE_POLLENPUFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 73,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 73,
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRAGONDARTS, MOVE_UTURN, MOVE_PHANTOMFORCE, MOVE_DRACOMETEOR },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 74,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_METEORMASH, MOVE_BULLETPUNCH, MOVE_ZENHEADBUTT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_METAGROSSITE,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 75,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_WATERSHURIKEN, MOVE_SCALD, MOVE_DARKPULSE, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Battle Bond
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Alistair_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 73,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 73,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 73,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_DISCHARGE, MOVE_FLAMETHROWER, MOVE_LIQUIDATION, MOVE_ROCKTOMB },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 74,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_STONEEDGE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 75,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Hawthorne_Divergent[] = {
    { // No Changes, here for completeness
        .lvl = 73,
        .species = SPECIES_CHESNAUGHT,
        .moves = { MOVE_SEEDBOMB, MOVE_SPIKYSHIELD, MOVE_BULKUP, MOVE_HAMMERARM },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Bulletproof
    },
    {
        .lvl = 73,
        .species = SPECIES_INCINEROAR,
        .moves = { MOVE_PARTINGSHOT, MOVE_FLAREBLITZ, MOVE_DARKESTLARIAT, MOVE_FAKEOUT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 73,
        .species = SPECIES_INTELEON,
        .moves = { MOVE_SNIPESHOT, MOVE_ICEBEAM, MOVE_DARKPULSE, MOVE_HYPERBEAM },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Sniper
    },
    {
        .lvl = 73,
        .species = SPECIES_TORTERRA,
        .moves = { MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_WOODHAMMER, MOVE_SYNTHESIS },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Shell Armor
    },
    {
        .lvl = 74,
        .species = SPECIES_SWAMPERT,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHQUAKE, MOVE_ICEBEAM, MOVE_ROCKSLIDE },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 75,
        .species = SPECIES_CHARIZARD,
        .moves = { MOVE_DRAGONCLAW, MOVE_EARTHQUAKE, MOVE_FLAREBLITZ, MOVE_DRAGONDANCE },
        .heldItem = ITEM_CHARIZARDITE_X,
        .ability = Ability_1 // Blaze
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Clancy_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_MEMENTO, MOVE_FLAMETHROWER, MOVE_TOXIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 73,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_ENCORE, MOVE_RECOVER, MOVE_PSYSHOCK, MOVE_FLASHCANNON },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Magic Guard
    },
    {
        .lvl = 73,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_HAMMERARM, MOVE_SHADOWPUNCH, MOVE_MEGAPUNCH, MOVE_FIREPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 73,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_PLAYROUGH, MOVE_OUTRAGE, MOVE_ICEFANG, MOVE_CHARM },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 74,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_BULLETPUNCH, MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_SWORDSDANCE },
        .heldItem = ITEM_SCIZORITE,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 75,
        .species = SPECIES_DRAGALGE,
        .moves = { MOVE_SLUDGEBOMB, MOVE_AQUATAIL, MOVE_THUNDERBOLT, MOVE_FOCUSBLAST },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Poison Point
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ena_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ARIADOS,
        .moves = { MOVE_CROSSPOISON, MOVE_STICKYWEB, MOVE_TOXICTHREAD, MOVE_PINMISSILE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 73,
        .species = SPECIES_WALREIN,
        .moves = { MOVE_BLIZZARD, MOVE_BRINE, MOVE_BODYSLAM, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Thick Fat
    },
    {
        .lvl = 73,
        .species = SPECIES_AMBIPOM,
        .moves = { MOVE_DOUBLEHIT, MOVE_ACROBATICS, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_1 // Technician
    },
    {
        .lvl = 73,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_SOLARBLADE, MOVE_LEAFBLADE, MOVE_XSCISSOR, MOVE_SYNTHESIS },
        .heldItem = ITEM_POWER_HERB,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 74,
        .species = SPECIES_AERODACTYL,
        .moves = { MOVE_STONEEDGE, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_ICEFANG },
        .heldItem = ITEM_AERODACTYLITE,
        .ability = Ability_2 // Pressure
    },
    {
        .lvl = 75,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_FLAMETHROWER, MOVE_HEX, MOVE_ENERGYBALL },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Infiltrator
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Copycat_Divergent[] = {
    // This trainer's Pokemon are replaced by the player's team
    {
        .lvl = 100,
        .species = SPECIES_BIDOOF,
        .moves = { MOVE_VCREATE, MOVE_JUDGMENT, MOVE_BOLTSTRIKE, MOVE_BLUEFLARE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Felix_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_ORBEETLE,
        .moves = { MOVE_UTURN, MOVE_REFLECT, MOVE_PSYCHIC, MOVE_BUGBUZZ },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 73,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_ICEFANG, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 73,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_RAINDANCE, MOVE_ROOST, MOVE_HURRICANE, MOVE_THUNDER },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Multiscale
    },
    {
        .lvl = 73,
        .species = SPECIES_TYRANTRUM,
        .moves = { MOVE_HEADSMASH, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_FIREFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 74,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_QUIVERDANCE, MOVE_BUGBUZZ, MOVE_GIGADRAIN },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 75,
        .species = SPECIES_DURALUDON,
        .moves = { MOVE_FLASHCANNON, MOVE_DRAGONCLAW, MOVE_IRONDEFENSE, MOVE_BREAKINGSWIPE },
        .heldItem = ITEM_DURALUDITE,
        .ability = Ability_Hidden // Stalwart
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Collin_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_PSYCHIC, MOVE_FIREBLAST, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 73,
        .species = SPECIES_FERALIGATR,
        .moves = { MOVE_DRAGONDANCE, MOVE_ICEPUNCH, MOVE_CRUNCH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 73,
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_THUNDERPUNCH, MOVE_STONEEDGE, MOVE_EARTHQUAKE, MOVE_HEAVYSLAM },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 73,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_FREEZEDRY, MOVE_EXTRASENSORY, MOVE_NASTYPLOT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 74,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_ICEBEAM, MOVE_THUNDERBOLT, MOVE_RECOVER },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 75,
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_DRAGONCLAW, MOVE_CRUNCH, MOVE_PROTECT },
        .heldItem = ITEM_SALAMENCITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Crystal_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_SPIKES, MOVE_TOXIC, MOVE_EARTHQUAKE, MOVE_RECOVER },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Unaware
    },
    {
        .lvl = 73,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_HEAVYSLAM, MOVE_KNOCKOFF, MOVE_EARTHQUAKE, MOVE_BULLETPUNCH },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 73,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_CURSE, MOVE_BODYSLAM, MOVE_HEATCRASH, MOVE_REST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 73,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BULKUP, MOVE_DRAINPUNCH, MOVE_KNOCKOFF, MOVE_BULLETPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 74,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_BONEMERANG, MOVE_STEALTHROCK, MOVE_FIREBLAST },
        .heldItem = ITEM_THICK_CLUB,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 75,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_NASTYPLOT, MOVE_SHADOWBALL, MOVE_SLUDGEWAVE, MOVE_FOCUSBLAST },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Irene_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_BULKUP, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 73,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_CRUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 73,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_EARTHPOWER, MOVE_LAVAPLUME, MOVE_SUNNYDAY, MOVE_IRONHEAD },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 73,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_PLAYROUGH, MOVE_CRUNCH, MOVE_FIREFANG, MOVE_OUTRAGE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 74,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SUBSTITUTE, MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_UTURN },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 75,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYSHOCK, MOVE_SHADOWBALL, MOVE_CALMMIND, MOVE_FOCUSBLAST },
        .heldItem = ITEM_ALAKAZITE,
        .ability = Ability_1 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ronald_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYSHOCK, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_RECOVER },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Download
    },
    {
        .lvl = 73,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_CLOSECOMBAT, MOVE_SUCKERPUNCH, MOVE_RAPIDSPIN },
        .heldItem = ITEM_FIGHTING_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 73,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_NIGHTSLASH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 73,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_SHADOWPUNCH, MOVE_IRONDEFENSE, MOVE_HAMMERARM, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 74,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_DRAINPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 75,
        .species = SPECIES_PINSIR,
        .moves = { MOVE_SWORDSDANCE, MOVE_XSCISSOR, MOVE_CLOSECOMBAT, MOVE_GIGAIMPACT },
        .heldItem = ITEM_PINSIRITE,
        .ability = Ability_Hidden // Moxie
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Kurtis_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_IRONHEAD, MOVE_SACREDSWORD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 73,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_HEAVYSLAM, MOVE_ROCKSLIDE, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 73,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 73,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_ROOST, MOVE_NASTYPLOT, MOVE_HEATWAVE, MOVE_DARKPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 74,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_MUDDYWATER, MOVE_RECOVER, MOVE_DAZZLINGGLEAM, MOVE_BLIZZARD },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 75,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_DARKPULSE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    },
};
// #endregion
// #region Heleo City (Postgame)
const struct TrainerMonNoItemCustomMoves sParty_HeleoCity_NurseBrianne_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 1,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_TACKLE, MOVE_GROWL, MOVE_REFLECT, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Healer
    },
};
// #endregion
// #endregion

// #region Trainer Definitions 
const struct Trainer gDivergentTrainers[] = {
    [TRAINER_NONE] = {
        .trainerName = NO_NAME,
    },
    // #region Important trainers
    [TRAINER_RIVAL1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_FIRST_BATTLE,
        .partySize = NELEMS(sParty_Rival1_Divergent),
        .party = {.NoItemCustomMoves = sParty_Rival1_Divergent}
    },
    [TRAINER_RIVAL2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Rival2_Divergent}
    },
    [TRAINER_RUBARR_DESERT_PARTNER_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_PartnerRival1_Divergent),
        .party = {.NoItemCustomMoves = sParty_PartnerRival1_Divergent}
    },
    [TRAINER_RIVAL3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival3_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival3_Divergent}
    },
    [TRAINER_TORMA_CAVE_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey1_Divergent}
    },
    [TRAINER_TORMA_CAVE_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey1_Divergent}
    },
    [TRAINER_ROUTE_10_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey2_Divergent}
    },
    [TRAINER_ROUTE_10_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey2_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Vaporeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Jolteon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Flareon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Espeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Umbreon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Leafeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Glaceon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Sylveon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAKE, // Do not see his front at this time
        .trainerName = { _A, _l, _i, _s, _t, _a, _i, _r, _END },
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Route11_Alistair_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11_Alistair_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Vaporeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Jolteon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Flareon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Espeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Umbreon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Leafeon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Glaceon_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Sylveon_Divergent}
    },

    [TRAINER_BRUCCIE_VILLAGE_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Vaporeon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Jolteon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Flareon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Espeon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Umbreon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Leafeon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Glaceon_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Sylveon_Divergent}
    },
    [TRAINER_EMRALDIN_QUAY_OPTIONAL_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_EmraldinQuayEvent_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_EmraldinQuayEvent_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_3,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Rival_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Rival_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_ALISTAIR,
        .trainerName = {_A, _l, _i, _s, _t, _a, _i, _r, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Alistair_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Alistair_Divergent}
    },
    // #endregion
    // #region Route 1
    [TRAINER_ROUTE_1_YOUNGSTER_PETER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_P, _e, _t, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route1_YoungsterPeter_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterPeter_Divergent}
    },
    [TRAINER_ROUTE_1_LASS_HELENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_H, _e, _l, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route1_LassHelena_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route1_LassHelena_Divergent}
    },
    [TRAINER_ROUTE_1_YOUNGSTER_HARLAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_H, _a, _r, _l, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route1_YoungsterHarlan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterHarlan_Divergent}
    },
    [TRAINER_ROUTE_1_BURGLAR_BRYCE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_B, _r, _y, _c, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_Route1_BurglarBryce_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route1_BurglarBryce_Divergent}
    },
    [TRAINER_ROUTE_1_SWIMMER_REBECCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_R, _e, _b, _e, _c, _c, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route1_SwimmerRebecca_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route1_SwimmerRebecca_Divergent}
    },
    // #endregion
    // #region Route 2
    [TRAINER_ROUTE_2_YOUNGSTER_JOEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_J, _o, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route2_YoungsterJoey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route2_YoungsterJoey_Divergent}
    },
    [TRAINER_ROUTE_2_LASS_KIMBERLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_K, _i, _m, _b, _e, _r, _l, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route2_LassKimberly_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route2_LassKimberly_Divergent}
    },
    [TRAINER_ROUTE_2_LASS_RIKKI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_R, _i, _k, _k, _i, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route2_LassRikki_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route2_LassRikki_Divergent}
    },
    [TRAINER_ROUTE_2_COOL_TRAINER_ANDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _n, _d, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route2_CoolTrainerAndy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route2_CoolTrainerAndy_Divergent}
    },
    // #endregion
    // #region Varisi Forest
    [TRAINER_VARISI_FOREST_BUG_CATCHER_KENDELL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_K, _e, _n, _d, _e, _l, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_VarisiForest_BugCatcherKendell_Divergent),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_BugCatcherKendell_Divergent}
    },
    [TRAINER_VARISI_FOREST_BUG_CATCHER_BRADEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _r, _a, _d, _e, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_VarisiForest_BugCatcherBraden_Divergent),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_BugCatcherBraden_Divergent}
    },
    [TRAINER_VARISI_FOREST_LASS_BREANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_B, _r, _e, _a, _n, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_VarisiForest_LassBreanna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_LassBreanna_Divergent}
    },
    [TRAINER_VARISI_FOREST_LASS_MIMI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_M, _i, _m, _i, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_VarisiForest_LassMimi_Divergent),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_LassMimi_Divergent}
    },
    // #endregion
    // #region Rhodanzi City
    [TRAINER_RHODANZI_GYM_ALONSO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_A, _l, _o, _n, _s, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_RhodanziCity_Alonso_Divergent),
        .party = {.NoItemCustomMoves = sParty_RhodanziCity_Alonso_Divergent}
    },
    [TRAINER_RHODANZI_GYM_BRANDON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_B, _r, _a, _n, _d, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_RhodanziCity_Brandon_Divergent),
        .party = {.NoItemCustomMoves = sParty_RhodanziCity_Brandon_Divergent}
    },
    [TRAINER_RHODANZI_GYM_LEADER_TERRENCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_RhodanziCity_LeaderTerrence_Divergent),
        .party = {.ItemCustomMoves = sParty_RhodanziCity_LeaderTerrence_Divergent}
    },
    // #endregion
    // #region Route 3
    [TRAINER_ROUTE_3_PICKNICKER_TANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_T, _a, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route3_PicknickerTana_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_PicknickerTana_Divergent}
    },
    [TRAINER_ROUTE_3_BUG_CATCHER_IRWIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_I, _r, _w, _i, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route3_BugCatcherIrwin_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_BugCatcherIrwin_Divergent}
    },
    [TRAINER_ROUTE_3_YOUNGSTER_LOGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_L, _o, _g, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route3_YoungsterLogan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_YoungsterLogan_Divergent}
    },
    [TRAINER_ROUTE_3_TWINS_NINA_AND_MEG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_N, _i, _n, _a, _SPACE, _AMPERSAND, _SPACE, _M, _e, _g, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route3_TwinsNinaAndMeg_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_TwinsNinaAndMeg_Divergent}
    },
    [TRAINER_ROUTE_3_NINJA_BOY_BOTAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_B, _o, _t, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route3_NinjaBoyBotan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_NinjaBoyBotan_Divergent}
    },
    [TRAINER_ROUTE_3_ROCKER_JUDE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_J, _u, _d, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route3_RockerJude_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_RockerJude_Divergent}
    },
    [TRAINER_ROUTE_3_TEAM_PLUTO_RAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _a, _u, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_Route3_TeamPlutoRaul_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route3_TeamPlutoRaul_Divergent}
    },
    // #endregion
    // #region Rubarr Desert
    [TRAINER_RUBARR_DESERT_NURSE_JAINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_J, _a, _i, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_NurseJaina_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_NurseJaina_Divergent}
    },
    [TRAINER_RUBARR_DESERT_BIRD_KEEPER_NOLAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_N, _o, _l, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_BirdKeeperNolan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_BirdKeeperNolan_Divergent}
    },
    [TRAINER_RUBARR_DESERT_RUIN_MANIAC_KENT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_K, _e, _n, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_RuinManiacKent_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_RuinManiacKent_Divergent}
    },
    [TRAINER_RUBARR_DESERT_BLACK_BELT_KOBIYASHI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_K, _o, _b, _i, _y, _a, _s, _h, _i, _END},
        .gender = MALE,
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_BlackbeltKobiyashi_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_BlackbeltKobiyashi_Divergent}
    },
    [TRAINER_RUBARR_DESERT_RUIN_MANIAC_ALBERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_A, _l, _b, _e, _r, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_RuinManiacAlbert_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_RuinManiacAlbert_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_MIKA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_M, _i, _k, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoMika_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoMika_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_MARCEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _a, _r, _c, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoMarcel_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoMarcel_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_TANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_T, _a, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoTana_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoTana_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoClancy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoClancy_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoEna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoEna_Divergent}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoAdminIrene_Divergent),
        .party = {.NoItemCustomMoves = sParty_RubarrDesert_TeamPlutoAdminIrene_Divergent}
    },
    // #endregion
    // #region Route 4
    [TRAINER_ROUTE_4_CAMPER_PIETRO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_P, _i, _e, _t, _r, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route4_Camper_Pietro_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Camper_Pietro_Divergent}
    },
    [TRAINER_ROUTE_4_PSYCHIC_ADRIANO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_A, _d, _r, _i, _a, _n, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route4_Psychic_Adriano_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Psychic_Adriano_Divergent}
    },
    [TRAINER_ROUTE_4_BEAUTY_BEATRICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_B, _e, _a, _t, _r, _i, _c, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route4_Beauty_Beatrice_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Beauty_Beatrice_Divergent}
    },
    [TRAINER_ROUTE_4_LADY_ALDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_A, _l, _d, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route4_Lady_Alda_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Lady_Alda_Divergent}
    },
    [TRAINER_ROUTE_4_LASS_ISABELA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_I, _s, _a, _b, _e, _l, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route4_Lass_Isabela_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Lass_Isabela_Divergent}
    },
    [TRAINER_ROUTE_4_BIRD_KEEPER_ROWLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_R, _o, _w, _l, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route4_Bird_Keeper_Rowley_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Bird_Keeper_Rowley_Divergent}
    },
    [TRAINER_ROUTE_4_CRUSH_GIRL_ELISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _l, _i, _s, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route4_Crush_Girl_Elise_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Crush_Girl_Elise_Divergent}
    },
    [TRAINER_ROUTE_4_GENTLEMAN_PORTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_P, _o, _r, _t, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route4_Gentleman_Porter_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Gentleman_Porter_Divergent}
    },
    [TRAINER_ROUTE_4_BIRD_KEEPER_LUCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_L, _u, _c, _a, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route4_Bird_Keeper_Luca_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route4_Bird_Keeper_Luca_Divergent}
    },
    // #endregion
    // #region Torma Cave
    [TRAINER_TORMA_CAVE_FISHERMAN_ALFIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_A, _l, _f, _i, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_TormaCave_Fisherman_Alfie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Fisherman_Alfie_Divergent}
    },
    [TRAINER_TORMA_CAVE_HIKER_NOB] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_N, _o, _b, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_TormaCave_Hiker_Nob_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Hiker_Nob_Divergent}
    },
    [TRAINER_TORMA_CAVE_HIKER_SAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_S, _a, _u, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_TormaCave_Hiker_Saul_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Hiker_Saul_Divergent}
    },
    [TRAINER_TORMA_CAVE_ENGINEER_WYATT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_W, _y, _a, _t, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_TormaCave_Engineer_Wyatt_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Engineer_Wyatt_Divergent}
    },
    [TRAINER_TORMA_CAVE_ENGINEER_SHANE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_S, _h, _a, _n, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_TormaCave_Engineer_Shane_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Engineer_Shane_Divergent}
    },
    [TRAINER_TORMA_CAVE_POKEFAN_COREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_C, _o, _r, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_TormaCave_Pokefan_Corey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Pokefan_Corey_Divergent}
    },
    [TRAINER_TORMA_CAVE_LASS_HARMONY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_H, _a, _r, _m, _o, _n, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_TormaCave_Lass_Harmony_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Lass_Harmony_Divergent}
    },
    // #endregion
    // #region Route 7
    [TRAINER_ROUTE_7_CAMPER_CARLISLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_C, _a, _r, _l, _i, _s, _l, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route7_CamperCarlisle_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_CamperCarlisle_Divergent}
    },    
    // #endregion
    // #region Route 13
    [TRAINER_ROUTE_13_GAMBLER_DALTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _a, _l, _t, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route13_GamblerDalton_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_GamblerDalton_Divergent}
    },
    [TRAINER_ROUTE_13_COLLECTOR_CHARLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_C, _h, _a, _r, _l, _i, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route13_CollectorCharlie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_CollectorCharlie_Divergent}
    },
    [TRAINER_ROUTE_13_HIKER_DWAYNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _w, _a, _y, _n, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route13_HikerDwayne_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_HikerDwayne_Divergent}
    },
    [TRAINER_ROUTE_13_BLACK_BELT_HECTOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_H, _e, _c, _t, _o, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route13_BlackBeltHector_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_BlackBeltHector_Divergent}
    },
    [TRAINER_ROUTE_13_PICKNICKER_ETIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_E, _t, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route13_PicknickerEtie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_PicknickerEtie_Divergent}
    },
    [TRAINER_ROUTE_13_BEAUTY_CANDICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_C, _a, _n, _d, _i, _c, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route13_BeautyCandice_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_BeautyCandice_Divergent}
    },
    [TRAINER_ROUTE_13_GAMBLER_OWAIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_O, _w, _a, _i, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route13_GamblerOwain_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_GamblerOwain_Divergent}
    },
    [TRAINER_ROUTE_13_COLLECTOR_BENJI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_B, _e, _n, _j, _i, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route13_CollectorBenji_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route13_CollectorBenji_Divergent}
    },
    // #endregion
    // #region Ferrox Village
    [TRAINER_FERROX_LIBRARY_LAURENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _a, _u, _r, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerLaurena_Divergent),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerLaurena_Divergent}
    },
    [TRAINER_FERROX_LIBRARY_LONA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_L, _o, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerLona_Divergent),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerLona_Divergent}
    },
    [TRAINER_FERROX_LIBRARY_CHET] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_C, _h, _e, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerChet_Divergent),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerChet_Divergent}
    },
    [TRAINER_FERROX_LIBRARY_VINCENT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_V, _i, _n, _c, _e, _n, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerVincent_Divergent),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerVincent_Divergent}
    },
    [TRAINER_FERROX_GYM_LEADER_STELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_FerroxGym_GymLeaderStella_Divergent),
        .party = {.ItemCustomMoves = sParty_FerroxGym_GymLeaderStella_Divergent}
    },
    // #endregion
    // #region Route 5
    [TRAINER_ROUTE_5_LADY_FAITH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_F, _a, _i, _t, _h, _END},
        .gender = FEMALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route5_LadyFaith_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_LadyFaith_Divergent}
    },
    [TRAINER_ROUTE_5_BUG_CATCHER_BEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _e, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route5_BugCatcher_Ben_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_BugCatcher_Ben_Divergent}
    },
    [TRAINER_ROUTE_5_PSYCHIC_ALYSSIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_A, _l, _y, _s, _s, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route5_Psychic_Alyssia_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Psychic_Alyssia_Divergent}
    },
    [TRAINER_ROUTE_5_BREEDER_BRENDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_B, _r, _e, _n, _d, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_Route5_Breeder_Brenda_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Breeder_Brenda_Divergent}
    },
    [TRAINER_ROUTE_5_BLACKBELT_RAHEEM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _a, _h, _e, _e, _m, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route5_Blackbelt_Raheem_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Blackbelt_Raheem_Divergent}
    },
    [TRAINER_ROUTE_5_GAMBLER_DOMINIK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _o, _m, _i, _n, _i, _k, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route5_Gambler_Dominik_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Gambler_Dominik_Divergent}
    },
    [TRAINER_ROUTE_5_LADY_JULIET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_J, _u, _l, _i, _e, _t, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route5_Lady_Juliet_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Lady_Juliet_Divergent}
    },
    [TRAINER_ROUTE_5_GENTLEMAN_MARCUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_M, _a, _r, _c, _u, _s, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route5_Gentleman_Marcus_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route5_Gentleman_Marcus_Divergent}
    },
    // #endregion
    // #region Heleo Ranch
    [TRAINER_HELEO_RANCH_BURGLAR_COLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _o, _l, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Burglar_Cole_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Burglar_Cole_Divergent}
    },
    [TRAINER_HELEO_RANCH_CAMPER_TROY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_T, _r, _o, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Camper_Troy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Camper_Troy_Divergent}
    },
    [TRAINER_HELEO_RANCH_BREEDER_LAURA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_L, _a, _u, _r, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Breeder_Laura_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Breeder_Laura_Divergent}
    },
    [TRAINER_HELEO_RANCH_PICKNICKER_CARLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_C, _a, _r, _l, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Picknicker_Carly_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Picknicker_Carly_Divergent}
    },
    // #endregion
    // #region Route 7 (Continued)
    [TRAINER_ROUTE_7_ROCKER_JONAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_J, _o, _n, _a, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route7_RockerJonas_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_RockerJonas_Divergent}
    },
    [TRAINER_ROUTE_7_LASS_EDEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_E, _d, _e, _n, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route7_LassEden_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_LassEden_Divergent}
    },
    [TRAINER_ROUTE_7_HIKER_DANNY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _a, _n, _n, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route7_HikerDanny_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_HikerDanny_Divergent}
    },
    [TRAINER_ROUTE_7_CRUSH_GIRL_ERIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _r, _i, _n, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route7_CrushGirlEden_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_CrushGirlEden_Divergent}
    },
    [TRAINER_ROUTE_7_PSYCHIC_ISHAAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_I, _s, _h, _a, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route7_PsychicIshaan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route7_PsychicIshaan_Divergent}
    },
    // #endregion
    // #region Route 6
    [TRAINER_ROUTE_6_YOUNGSTER_NED] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_N, _e, _d, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route6_Youngster_Ned_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Youngster_Ned_Divergent}
    },
    [TRAINER_ROUTE_6_NINJABOY_RAJAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_R, _a, _j, _a, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route6_NinjaBoy_Rajan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_NinjaBoy_Rajan_Divergent}
    },
    [TRAINER_ROUTE_6_HIKER_ROMERO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _m, _e, _r, _o, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route6_Hiker_Romero_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Hiker_Romero_Divergent}
    },
    [TRAINER_ROUTE_6_SUPERNERD_ESTEVAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _s, _t, _e, _v, _a, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route6_SuperNerd_Estevan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_SuperNerd_Estevan_Divergent}
    },
    [TRAINER_ROUTE_6_ENGINEER_HARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _a, _r, _r, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route6_Engineer_Harry_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Engineer_Harry_Divergent}
    },
    [TRAINER_ROUTE_6_GAMBLER_MICK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_M, _i, _c, _k, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route6_Gambler_Mick_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Gambler_Mick_Divergent}
    },
    [TRAINER_ROUTE_6_FISHERMAN_TAYLOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_T, _a, _y, _l, _o, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route6_Fisherman_Taylor_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Fisherman_Taylor_Divergent}
    },
    [TRAINER_ROUTE_6_NURSE_LEANNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_L, _e, _a, _n, _n, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_Route6_Nurse_Leanne_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Nurse_Leanne_Divergent}
    },
    [TRAINER_ROUTE_6_SUPERNERD_DANTE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_D, _a, _n, _t, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route6_SuperNerd_Dante_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_SuperNerd_Dante_Divergent}
    },
    [TRAINER_ROUTE_6_BUGCATCHER_BILIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _i, _l, _l, _i, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route6_BugCatcher_Billie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_BugCatcher_Billie_Divergent}
    },
    [TRAINER_ROUTE_6_GENTLEMAN_LINCOLN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_L, _i, _n, _c, _o, _l, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route6_Gentleman_Lincoln_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Gentleman_Lincoln_Divergent}
    },
    [TRAINER_ROUTE_6_BLACKBELT_RAFAEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _a, _f, _a, _e, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route6_BlackBelt_Raphael_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_BlackBelt_Raphael_Divergent}
    },
    [TRAINER_ROUTE_6_LASS_ANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_A, _n, _n, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route6_Lass_Anna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Lass_Anna_Divergent}
    },
    [TRAINER_ROUTE_6_SWIMMER_DANIKA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_D, _a, _n, _i, _k, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route6_Swimmer_Danika_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_Swimmer_Danika_Divergent}
    },
    [TRAINER_ROUTE_6_SRANDJR_SUEANDKAT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_S, _u, _e, _SPACE, _AMPERSAND, _SPACE, _K, _a, _t, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route6_SrAndJr_SueAndKat_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_SrAndJr_SueAndKat_Divergent}
    },
    [TRAINER_ROUTE_6_HIKER_DARRYL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _a, _r, _r, _y, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route6_HikerDarryl_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route6_HikerDarryl_Divergent}
    },
    // #endregion
    // #region Heleo City
    [TRAINER_HELEO_TRAINER_HOUSE_PSYCHIC_BIANCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_B, _i, _a, _n, _c, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_PsychicBianca_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_PsychicBianca_Divergent}
    },
    [TRAINER_HELEO_TRAINER_HOUSE_SUPERNERD_GALEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_G, _a, _l, _e, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_SupernerdGalen_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_SupernerdGalen_Divergent}
    },
    [TRAINER_HELEO_TRAINER_HOUSE_COOL_TRAINER_JET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _e, _t, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_CoolTrainerJet_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_CoolTrainerJet_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_TESSA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_T, _e, _s, _s, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerTessa_Divergent),
        .party = {.NoItemCustomMoves = sParty_HeleoCityGym_SwimmerTessa_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_BYRON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _y, _r, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerByron_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerByron_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_DANETTE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_D, _a, _n, _e, _t, _t, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerDanette_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerDanette_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_MAISEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _i, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerMaisey_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerMaisey_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine2_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine2_Divergent}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine3_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine3_Divergent}
    },
    // #endregion
    // #region Route 8
    [TRAINER_ROUTE_8_CAMPER_DREW] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_D, _r, _e, _w, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route8_Camper_Drew_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_Camper_Drew_Divergent}
    },
    [TRAINER_ROUTE_8_NINJA_BOY_ZEKE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_Z, _e, _k, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route8_NinjaBoyZeke_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_NinjaBoyZeke_Divergent}
    },
    [TRAINER_ROUTE_8_SUPER_NERD_SAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_S, _a, _u, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route8_SuperNerdSaul_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_SuperNerdSaul_Divergent}
    },
    [TRAINER_ROUTE_8_ROCKER_PARKER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_P, _a, _r, _k, _e, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route8_RockerParker_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_RockerParker_Divergent}
    },
    [TRAINER_ROUTE_8_PARASOL_LADY_ANNABELLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_A, _n, _n, _a, _b, _e, _l, _l, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route8_ParasolLadyAnnabelle_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_ParasolLadyAnnabelle_Divergent}
    },
    [TRAINER_ROUTE_8_CHANNELER_MORGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _o, _r, _g, _a, _n, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route8_ChannelerMorgan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_ChannelerMorgan_Divergent}
    },
    [TRAINER_ROUTE_8_BUG_CATCHER_ARNOLD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_A, _r, _n, _o, _l, _d, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route8_BugCatcherArnold_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_BugCatcherArnold_Divergent}
    },
    [TRAINER_ROUTE_8_LASS_LILIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_L, _i, _l, _i, _a, _n, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route8_LassLilian_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_LassLilian_Divergent}
    },
    [TRAINER_ROUTE_8_NINJA_BOY_NATTO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_N, _a, _t, _t, _o, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route8_NinjaBoyNatto_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_NinjaBoyNatto_Divergent}
    },
    [TRAINER_ROUTE_8_TUBER_MICAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_MALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = {_M, _i, _c, _a, _h, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route8_TuberMicah_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_TuberMicah_Divergent}
    },
    [TRAINER_ROUTE_8_TUBER_NANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_FEMALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = {_N, _a, _n, _c, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route8_TuberNancy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_TuberNancy_Divergent}
    },
    [TRAINER_ROUTE_8_SWIMMER_MAYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _y, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerMaya_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerMaya_Divergent}
    },
    [TRAINER_ROUTE_8_SWIMMER_HUEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_H, _u, _e, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerHuey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerHuey_Divergent}
    },
    [TRAINER_ROUTE_8_SWIMMER_BOB] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _o, _b, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerBob_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerBob_Divergent}
    },
    [TRAINER_ROUTE_8_COOL_TRAINER_HARRIET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_H, _a, _r, _r, _i, _e, _t, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route8_CoolTrainerHarriet_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route8_CoolTrainerHarriet_Divergent}
    },
    // #endregion
    // #region Forgotten Manse
    [TRAINER_FORGOTTEN_MANSE_CHANNELER_MONA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _o, _n, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_ChannelerMona_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_ChannelerMona_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_BURGLAR_CHAD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _h, _a, _d, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BurglarChad_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BurglarChad_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_NURSE_LUCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_L, _u, _c, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_NurseLucy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_NurseLucy_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_BEAUTY_LULU] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _u, _l, _u, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_BeautyLulu_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_BeautyLulu_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_CHANNELER_ESTHER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_E, _s, _t, _h, _e, _r, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_ChannelerEsther_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_ChannelerEsther_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_SUPERNERD_AUSTIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_A, _u, _s, _t, _i, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_SuperNerdAustin_Divergent),
        .party = {.NoItemCustomMoves = sParty_ForgottenManse_1F_SuperNerdAustin_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_BURGLAR_JACQUES] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_J, _a, _c, _q, _u, _e, _s, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_BurglarJacques_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_BurglarJacques_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_PYSCHIC_CORBIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_C, _o, _r, _b, _i, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_PsychicCorbin_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_PsychicCorbin_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_BURGLAR_BARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_B, _a, _r, _r, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_BurglarBarry_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_BurglarBarry_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_YOUNGSTER_CHESTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_C, _h, _e, _s, _t, _e, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_YoungsterChester_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_YoungsterChester_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_CHANNELER_ELAINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_E, _l, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_ChannelerElaine_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_ChannelerElaine_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_SUPERNERD_GLENN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_G, _l, _e, _n, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_SuperNerdGlenn_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_SuperNerdGlenn_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_BURGLAR_PAVLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_P, _a, _v, _l, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_BurglarPavle_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_BurglarPavle_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_PSYCHIC_NOELLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_N, _o, _e, _l, _l, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_PsychicNoelle_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_PsychicNoelle_Divergent}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_CHANNELER_SANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_S, _a, _n, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_ChannelerSana_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_ChannelerSana_Divergent}
    },
    // #endregion
    // #region Daimyn Factory
    [TRAINER_DAIMYN_FACTORY_BIRDKEEPER_MARIUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_M, _a, _r, _i, _u, _s, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BirdkeeperMarius_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BirdkeeperMarius_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ROCKER_BENSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_B, _e, _n, _s, _o, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_RockerBenson_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_RockerBenson_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_LASS_NATALIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_N, _a, _t, _a, _l, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynFactory_LassNatalie_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynFactory_LassNatalie_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_JAMISON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_J, _a, _m, _i, _s, _o, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerJamison_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerJamison_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_HIKER_PERCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_P, _e, _r, _c, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_HikerPercy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_HikerPercy_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_BLACKBELT_RORY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _o, _r, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BlackbeltRory_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BlackbeltRory_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_WILSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_W, _i, _l, _s, _o, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerWilson_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerWilson_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_YOUNGSTER_NATE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_N, _a, _t, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_YoungsterNate_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_YoungsterNate_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_PICKNICKER_SHANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_S, _h, _a, _n, _n, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_PicknickerShanna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_PicknickerShanna_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_KLIFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_K, _l, _i, _f, _f, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerKliff_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerKliff_Divergent}
    },
    // #endregion
    // #region Daimyn City Gym
    [TRAINER_DAIMYN_CITY_GYM_YOUNGSTER_JACOB] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_J, _a, _c, _o, _b, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_YoungsterJacob_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_YoungsterJacob_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_POKEFAN_KANESHA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_K, _a, _n, _e, _s, _h, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_PokefanKanesha_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_PokefanKanesha_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_BEAUTY_EMILIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_E, _m, _i, _l, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_BeautyEmilie_Divergent),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_BeautyEmilie_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_BEAUTY_LEANNE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _e, _a, _n, _n, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_BeautyLeanne_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_BeautyLeanne_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_CHANNELER_ROSITA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_R, _o, _s, _i, _t, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_ChannelerRosita_Divergent),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_ChannelerRosita_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_GAMBLER_CHUCK] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_C, _h, _u, _c, _k, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_GamblerChuck_Divergent),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_GamblerChuck_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_BURGLAR_DEXTER] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_D, _e, _x, _t, _e, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_DaimynCityGym_BurglarDexter_Divergent),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_BurglarDexter_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_LEADER_CHANCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance_Divergent}
    },
    [TRAINER_DAIMYN_CITY_GYM_LEADER_CHANCE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance2_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance2_Divergent}
    },
    // #endregion
    // #region Route 9
    [TRAINER_ROUTE_9_COLLECTOR_MARSHALL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_M, _a, _r, _s, _h, _a, _l, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route9_Collector_Marshall_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_Collector_Marshall_Divergent}
    },
    [TRAINER_ROUTE_9_COOL_TRAINER_ANDREA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_A, _n, _d, _r, _e, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route9_CoolTrainer_Andrea_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_CoolTrainer_Andrea_Divergent}
    },
    [TRAINER_ROUTE_9_FISHERMAN_YUSUF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_Y, _u, _s, _u, _f, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route9_Fisherman_Yusuf_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_Fisherman_Yusuf_Divergent}
    },
    [TRAINER_ROUTE_9_GENTLEMAN_GAVIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _a, _v, _i, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route9_Gentleman_Gavin_Divergent),
        .party = {.NoItemCustomMoves = sParty_Route9_Gentleman_Gavin_Divergent}
    },
    [TRAINER_ROUTE_9_NINJA_BOY_AYRTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_A, _y, _r, _t, _o, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route9_NinjaBoy_Ayrton_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_NinjaBoy_Ayrton_Divergent}
    },
    [TRAINER_ROUTE_9_BREEDER_TALIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_T, _a, _l, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_Route9_Breeder_Talia_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_Breeder_Talia_Divergent}
    },
    [TRAINER_ROUTE_9_PICKNICKER_ZOE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_Z, _o, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route9_Picknicker_Zoe_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_Picknicker_Zoe_Divergent}
    },
    [TRAINER_ROUTE_9_COOL_TRAINER_KINGSLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_K, _i, _n, _g, _s, _l, _e, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route9_CoolTrainer_Kingsley_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route9_CoolTrainer_Kingsley_Divergent}
    },
    // #endregion
    // #region Route 10
    [TRAINER_ROUTE_10_PSYCHIC_DARIUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_D, _a, _r, _i, _u, _s, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route10_PsychicDarius_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_PsychicDarius_Divergent}
    },
    [TRAINER_ROUTE_10_BIRDKEEPER_MARIO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_M, _a, _r, _i, _o, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route10_BirdKeeperMario_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_BirdKeeperMario_Divergent}
    },
    [TRAINER_ROUTE_10_GAMBLER_DARREN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _a, _r, _r, _e, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route10_GamblerDarren_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_GamblerDarren_Divergent}
    },
    [TRAINER_ROUTE_10_PARASOLLADY_GWEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_G, _w, _e, _n, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route10_ParasolLadyGwen_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_ParasolLadyGwen_Divergent}
    },
    [TRAINER_ROUTE_10_CAMPER_JACKSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_J, _a, _c, _k, _s, _o, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route10_CamperJackson_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_CamperJackson_Divergent}
    },
    [TRAINER_ROUTE_10_ROCKER_BERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_B, _e, _r, _t, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route10_RockerBert_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_RockerBert_Divergent}
    },
    [TRAINER_ROUTE_10_SWIMMER_ALBERTO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_A, _l, _b, _e, _r, _t, _o, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerAlberto_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerAlberto_Divergent}
    },
    [TRAINER_ROUTE_10_SWIMMER_ROSIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_R, _o, _s, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerRosie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerRosie_Divergent}
    },
    [TRAINER_ROUTE_10_SWIMMER_DOUG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_D, _o, _u, _g, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerDoug_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerDoug_Divergent}
    },
    [TRAINER_ROUTE_10_CAVE_HIKER_HARLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_H, _a, _r, _l, _e, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route10Cave_HikerHarley_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10Cave_HikerHarley_Divergent}
    },
    [TRAINER_ROUTE_10_CAVE_BLACKBELT_XAVIER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_X, _a, _v, _i, _e, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route10Cave_BlackbeltXavier_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route10Cave_BlackbeltXavier_Divergent}
    },
    // #endregion
    // #region Route 11 South
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_ROSS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _o, _s, _s, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Ross_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Ross_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_GRETA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_G, _r, _e, _t, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Greta_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Greta_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_NELLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_N, _e, _l, _l, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Nellie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Nellie_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_HELGA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_H, _e, _l, _g, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Helga_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Helga_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_KAREEM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_K, _a, _r, _e, _e, _m, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Kareem_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Kareem_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_CHUNG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _h, _u, _n, _g, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Chung_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Chung_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_LASS_TABITHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_T, _a, _b, _i, _t, _h, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route11South_Lass_Tabitha_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Lass_Tabitha_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_CRUSH_GIRL_ALISA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_A, _l, _i, _s, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route11South_CrushGirl_Alisa_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_CrushGirl_Alisa_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_ENGINEER_DALE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_D, _a, _l, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route11South_Engineer_Dale_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Engineer_Dale_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_COLLECTOR_ORVILLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_O, _r, _v, _i, _l, _l, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route11South_Collector_Orville_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Collector_Orville_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoClancy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPlutoClancy_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoEna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPlutoEna_Divergent}
    },
    [TRAINER_ROUTE_11_SOUTH_PLUTO_ADMIN_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoAdminRonald_Divergent),
        .party = {.NoItemCustomMoves = sParty_Route11South_TeamPlutoAdminRonald_Divergent}
    },
    // #endregion
    // #region Hesson Pass
    [TRAINER_HESSON_PASS_HIKER_LUKE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_L, _u, _k, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_HessonPass_HikerLuke_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_HikerLuke_Divergent}
    },
    [TRAINER_HESSON_PASS_SCIENTIST_HARVEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_H, _a, _r, _v, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_HessonPass_ScientistHarvey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_ScientistHarvey_Divergent}
    },
    [TRAINER_HESSON_PASS_PSYCHIC_KIMIKO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_K, _i, _m, _i, _k, _o, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_HessonPass_PsychicKimiko_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_PsychicKimiko_Divergent}
    },
    [TRAINER_HESSON_PASS_COOL_TRAINER_COLT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _t, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_HessonPass_CoolTrainerColt_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_CoolTrainerColt_Divergent}
    },
    [TRAINER_HESSON_PASS_BLACK_BELT_HAYTHAM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_H, _a, _y, _t, _h, _a, _m, _END},
        .gender = MALE,
        .items = { ITEM_DIRE_HIT },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_HessonPass_BlackbeltHaytham_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_BlackbeltHaytham_Divergent}
    },
    [TRAINER_HESSON_PASS_COLLECTOR_ZEUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_Z, _e, _u, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_HessonPass_CollectorZeus_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_CollectorZeus_Divergent}
    },
    [TRAINER_HESSON_PASS_NURSE_MINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_M, _i, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_HessonPass_NurseMina_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_NurseMina_Divergent}
    },
    [TRAINER_HESSON_PASS_GENTLEMAN_GORDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _o, _r, _d, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_HessonPass_GentlemanGordy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_GentlemanGordy_Divergent}
    },
    // #endregion
    // #region Route 11 North
    [TRAINER_ROUTE_11_NORTH_PAINTER_ISOBEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_I, _s, _o, _b, _e, _l, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_Route11North_PainterIsobel_Divergent),
        .party = {.NoItemCustomMoves = sParty_Route11North_PainterIsobel_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_FISHERMAN_CLINT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_C, _l, _i, _n, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route11North_FishermanClint_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_FishermanClint_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_PARASOL_LADY_TINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_T, _i, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route11North_ParaoslLadyTina_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_ParaoslLadyTina_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_CHANNELER_KATYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_K, _a, _t, _y, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route11North_ChanellerKatya_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_ChanellerKatya_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_ROCKER_NATHANIEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_N, _a, _t, _h, _a, _n, _i, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_Route11North_RockerNathaniel_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_RockerNathaniel_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_NINJA_BOY_YAO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_Y, _a, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route11North_NinjaBoyYao_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_NinjaBoyYao_Divergent}
    },
    [TRAINER_ROUTE_11_NORTH_FISHERMAN_JONAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_J, _o, _n, _a, _h, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route11North_FishermanJonah_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_FishermanJonah_Divergent}
    },
    // #endregion
    // #region Laplaz Town
    [TRAINER_LAPLAZ_TRAINER_HOUSE_BIRD_KEEPER_TOBY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _o, _b, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_BirdKeeperToby_Divergent),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_BirdKeeperToby_Divergent}
    },
    [TRAINER_LAPLAZ_TRAINER_HOUSE_COLLECTOR_DIRK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_D, _i, _r, _k, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_CollectorDirk_Divergent),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_CollectorDirk_Divergent}
    },
    [TRAINER_LAPLAZ_TRAINER_HOUSE_COOL_TRAINER_VANESSA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_V, _a, _n, _e, _s, _s, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_CoolTrainerVanessa_Divergent),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_CoolTrainerVanessa_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_JEREMIAH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_J, _e, _r, _e, _m, _i, _a, _h, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_PsychicJeremiah_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_PsychicJeremiah_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_EXIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_E, _x, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_PicnickerExie_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_PicnickerExie_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_VIRGINIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_V, _i, _r, _g, _i, _n, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_ChannelerVirginia_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_ChannelerVirginia_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_NISHA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_N, _i, _s, _h, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_LadyNisha_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_LadyNisha_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_KENT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_K, _e, _n, _t, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_ScientistKent_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_ScientistKent_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_TRENT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_T, _r, _e, _n, _t, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_RockerTrent_Divergent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_RockerTrent_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_LEADER_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey_Divergent),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey_Divergent}
    },
    [TRAINER_LAPLAZ_GYM_LEADER_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey_Divergent),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey_Divergent}
    },
    // #endregion
    // #region Peradon Forest
    [TRAINER_PERADON_FOREST_POKEFAN_CLARK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_C, _l, _a, _r, _k, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_PeradonForest_PokefanClark_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_PokefanClark_Divergent}
    },
    [TRAINER_PERADON_FOREST_COLLECTOR_FERNANDO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_F, _e, _r, _n, _a, _n, _d, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_PeradonForest_CollectorFernando_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_CollectorFernando_Divergent}
    },
    [TRAINER_PERADON_FOREST_BUG_CATCHER_LYLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_L, _y, _l, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_PeradonForest_BugCatcherLyle_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BugCatcherLyle_Divergent}
    },
    [TRAINER_PERADON_FOREST_BEAUTY_ERICA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_E, _r, _i, _c, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_PeradonForest_BeautyErica_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BeautyErica_Divergent}
    },
    [TRAINER_PERADON_FOREST_PAINTER_SHEENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_S, _h, _e, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_PeradonForest_PainterSheena_Divergent),
        .party = {.NoItemCustomMoves = sParty_PeradonForest_PainterSheena_Divergent}
    },
    [TRAINER_PERADON_FOREST_CAMPER_RUPERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_R, _u, _p, _e, _r, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_PeradonForest_CamperRupert_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_CamperRupert_Divergent}
    },
    [TRAINER_PERADON_FOREST_SCIENTIST_SEAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _e, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_PeradonForest_ScientistSean_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_ScientistSean_Divergent}
    },
    [TRAINER_PERADON_FOREST_ROCKER_RAPHAEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_R, _a, _p, _h, _a, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_PeradonForest_RockerRaphael_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_RockerRaphael_Divergent}
    },
    [TRAINER_PERADON_FOREST_CHANNELER_RENEE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_R, _e, _n, _e, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_PeradonForest_ChannelerRenee_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_ChannelerRenee_Divergent}
    },
    [TRAINER_PERADON_FOREST_BLACKBELT_BRAD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_B, _r, _a, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_PeradonForest_BlackbeltBrad_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BlackbeltBrad_Divergent}
    },
    [TRAINER_PERADON_FOREST_RUIN_MANIAC_ALEX] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_A, _l, _e, _x, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_PeradonForest_RuinManiacAlex_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_RuinManiacAlex_Divergent}
    },
    // #endregion
    // #region Route 12 & Scalding Spa
    [TRAINER_ROUTE_12_EAST_TRIATHLETE_JOANNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_J, _o, _a, _n, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route12East_TriathleteJoanne_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12East_TriathleteJoanne_Divergent}
    },
    [TRAINER_ROUTE_12_EAST_PSYCHIC_TONY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_T, _o, _n, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route12East_PsychicTony_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12East_PsychicTony_Divergent}
    },
    [TRAINER_ROUTE_12_EAST_HIKER_DWIGHT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _w, _i, _g, _h, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route12East_HikerDwight_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12East_HikerDwight_Divergent}
    },
    [TRAINER_ROUTE_12_EAST_TRIATHLETE_TRIXIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_T, _r, _i, _x, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route12East_TriathleteTrixie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12East_TriathleteTrixie_Divergent}
    },
    [TRAINER_ROUTE_12_EAST_GENTLEMAN_GEOFFREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _e, _o, _f, _f, _r, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route12East_GentlemanGeoffrey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12East_GentlemanGeoffrey_Divergent}
    },
    [TRAINER_SCALDING_SPA_HIKER_EUGENE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_E, _u, _g, _e, _n, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_HikerEugene_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_HikerEugene_Divergent}
    },
    [TRAINER_SCALDING_SPA_SUPERNERD_STEPHEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_S, _t, _e, _p, _h, _e, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_SupernerdStephen_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_SupernerdStephen_Divergent}
    },
    [TRAINER_SCALDING_SPA_JUGGLER_JOHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_J, _o, _h, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_ScaldingSpa_JugglerJohan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_JugglerJohan_Divergent}
    },
    [TRAINER_SCALDING_SPA_BLACKBELT_KIERAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_K, _i, _e, _r, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_ScaldingSpa_BlackbeltKieran_Divergent),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_BlackbeltKieran_Divergent}
    },
    [TRAINER_SCALDING_SPA_TEAM_PLUTO_YOLENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_Y, _o, _l, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_TeamPlutoYolena_Divergent),
        .party = {.ItemCustomMoves = sParty_ScaldingSpa_TeamPlutoYolena_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_BUG_CATCHER_BRENDAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _r, _e, _n, _d, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route12West_BugCatcherBrenan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_BugCatcherBrenan_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_CHANTAL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_C, _h, _a, _n, _t, _a, _l, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierChantal_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierChantal_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_HIKER_KUMAR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_K, _u, _m, _a, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route12West_HikerKumar_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_HikerKumar_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_AUBREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_A, _u, _b, _r, _e, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierAubrey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierAubrey_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_LENORA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_L, _e, _n, _o, _r, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierLenora_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierLenora_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_MEGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_M, _e, _g, _a, _n, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierMegan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierMegan_Divergent}
    },
    [TRAINER_ROUTE_12_WEST_SWIMMER_M_GREG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _r, _e, _g, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route12West_SwimmerMGreg_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SwimmerMGreg_Divergent}
    },
    // #endregion
    // #region Bruccie Village & Calicin Bay
    [TRAINER_BRUCCIE_VILLAGE_GYM_MEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_M, _e, _l, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_LassMel_Divergent),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_LassMel_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_OWEN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_O, _w, _e, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_BirdKeeperOwen_Divergent),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_BirdKeeperOwen_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_TOMMY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_T, _o, _m, _m, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_EngineerTommy_Divergent),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_EngineerTommy_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_JOEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_J, _o, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_HikerJoel_Divergent),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_HikerJoel_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_ELLIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _l, _l, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_CrushGirlEllie_Divergent),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_CrushGirlEllie_Divergent}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_LEADER_ABBY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_BruccieVillageGym_LeaderAbby_Divergent),
        .party = {.ItemCustomMoves = sParty_BruccieVillageGym_LeaderAbby_Divergent}
    },
    [TRAINER_CALICIN_BAY_SKIER_RITA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_R, _i, _t, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SkierRita_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SkierRita_Divergent}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_F_FRAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_F, _r, _a, _n, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerFFran_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerFFran_Divergent}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_M_ANGELO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_A, _n, _g, _e, _l, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerMAngelo_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerMAngelo_Divergent}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_M_SEBASTIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_S, _e, _b, _a, _s, _t, _i, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerMSebastian_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerMSebastian_Divergent}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_F_CORRINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _o, _r, _r, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerFCorrine_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerFCorrine_Divergent}
    },
    [TRAINER_CALICIN_BAY_FISHERMAN_OLIVER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_O, _l, _i, _v, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_CalicinBay_FishermanOliver_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_FishermanOliver_Divergent}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_HUGO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_H, _u, _g, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoHugo_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoHugo_Divergent}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_ANISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_A, _n, _i, _s, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoAnise_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoAnise_Divergent}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_YOLENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_Y, _o, _l, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoYolena_Divergent),
        .party = {.ItemCustomMoves = sParty_CalicinBay_TeamPlutoYolena_Divergent}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoClancy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoClancy_Divergent}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoEna_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoEna_Divergent}
    },
    // #endregion
    // #region Pluto HQ
    [TRAINER_PLUTO_HQ_B1F_TEAM_PLUTO_HEATHCLIFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_H, _e, _a, _t, _h, _c, _l, _i, _f, _f, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoHeathcliff_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B1F_TeamPlutoHeathcliff_Divergent}
    },
    [TRAINER_PLUTO_HQ_B1F_SCIENTIST_SEAMUS] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _e, _a, _m, _u, _s, _END},
        .gender = MALE,
        .items = { ITEM_X_SP_ATK },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_ScientistSeamus_Divergent),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B1F_ScientistSeamus_Divergent}
    },
    [TRAINER_PLUTO_HQ_B1F_TEAM_PLUTO_COLTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _o, _l, _t, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoColton_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B1F_TeamPlutoColton_Divergent}
    },
    [TRAINER_PLUTO_HQ_B2F_SCIENTIST_WAYNE] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_W, _a, _y, _n, _e, _END},
        .gender = MALE,
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_ScientistWayne_Divergent),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B2F_ScientistWayne_Divergent}
    },
    [TRAINER_PLUTO_HQ_B2F_TEAM_PLUTO_DENISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_D, _e, _n, _i, _s, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_TeamPlutoDenise_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B2F_TeamPlutoDenise_Divergent}
    },
    [TRAINER_PLUTO_HQ_B2F_TEAM_PLUTO_THEODORE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_T, _h, _e, _o, _d, _o, _r, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_TeamPlutoTheodore_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B2F_TeamPlutoTheodore_Divergent}
    },
    [TRAINER_PLUTO_HQ_B3F_TEAM_PLUTO_YEON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_Y, _e, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B3F_TeamPlutoYeon_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B3F_TeamPlutoYeon_Divergent}
    },
    [TRAINER_PLUTO_HQ_B4F_TEAM_PLUTO_MATTY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _a, _t, _t, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoMatty_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B4F_TeamPlutoMatty_Divergent}
    },
    [TRAINER_PLUTO_HQ_B4F_SCIENTIST_GARY] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_G, _a, _r, _y, _END},
        .gender = MALE,
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_ScientistGary_Divergent),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B4F_ScientistGary_Divergent}
    },
    [TRAINER_PLUTO_HQ_B4F_TEAM_PLUTO_MAY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_M, _a, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoMay_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B4F_TeamPlutoMay_Divergent}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_CLAY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoClay_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoClay_Divergent}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_VICTOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_V, _i, _c, _t, _o, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoVictor_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoVictor_Divergent}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_PAULA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_P, _a, _u, _l, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoPaula_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoPaula_Divergent}
    },
    [TRAINER_PLUTO_HQ_B6F_TEAM_PLUTO_GIANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_G, _i, _a, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_TeamPlutoGiana_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B6F_TeamPlutoGiana_Divergent}
    },
    [TRAINER_PLUTO_HQ_B6F_SCIENTIST_ORSON] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_O, _r, _s, _o, _n, _END},
        .gender = MALE,
        .items = { ITEM_X_SP_ATK },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_ScientistOrson_Divergent),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B6F_ScientistOrson_Divergent}
    },
    [TRAINER_PLUTO_HQ_B6F_TEAM_PLUTO_QUINN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_Q, _u, _i, _n, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_TeamPlutoQuinn_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B6F_TeamPlutoQuinn_Divergent}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_LAYLA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_L, _a, _y, _l, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoLayla_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoLayla_Divergent}
    },
    [TRAINER_PLUTO_HQ_B7F_SCIENTIST_NICO] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_N, _i, _c, _o, _END},
        .gender = MALE,
        .items = { ITEM_X_SP_DEF },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_ScientistNico_Divergent),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B7F_ScientistNico_Divergent}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_MITCH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _i, _t, _c, _h, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoMitch_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoMitch_Divergent}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_RICHARD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _i, _c, _h, _a, _r, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoRichard_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoRichard_Divergent}
    },
    [TRAINER_PLUTO_HQ_B4F_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Divergent}
    },
    [TRAINER_PLUTO_HQ_B7F_PLUTO_ADMIN_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Divergent}
    },
    [TRAINER_PLUTO_HQ_B1F_PLUTO_LEADER_KURTIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_LEADER,
        .trainerPic = TRAINER_PIC_PLUTO_LEADER_KURTIS,
        .trainerName = {_K, _u, _r, _t, _i, _s, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_MEGA_RING },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Divergent}
    },
    // #endregion
    // #region Route 18
    [TRAINER_ROUTE_18_SWIMMER_JASPER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_J, _a, _s, _p, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route18_SwimmerJasper_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_SwimmerJasper_Divergent}
    },
    [TRAINER_ROUTE_18_TRIATHLETE_DEBORAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_D, _e, _b, _o, _r, _a, _h, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route18_TriathleteDeborah_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_TriathleteDeborah_Divergent}
    },
    [TRAINER_ROUTE_18_SWIMMER_JUDIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_J, _u, _d, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route18_SwimmerJudie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_SwimmerJudie_Divergent}
    },
    [TRAINER_ROUTE_18_BIRD_KEEPER_KIRK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_K, _i, _r, _k, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route18_BirdKeeperKirk_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_BirdKeeperKirk_Divergent}
    },
    [TRAINER_ROUTE_18_LASS_EMMA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_E, _m, _m, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route18_LassEmma_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_LassEmma_Divergent}
    },
    [TRAINER_ROUTE_18_CAVE_BLACKBELT_ROHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _o, _h, _a, _n, _END},
        .gender = MALE,
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route18_BlackbeltRohan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route18_BlackbeltRohan_Divergent}
    },
    // #endregion
    // #region Route 16
    [TRAINER_ROUTE_16_SWIMMER_M_GALE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _a, _l, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerGale_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerGale_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_AMY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_A, _m, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerAmy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerAmy_Divergent}
    },
    [TRAINER_ROUTE_16_BIRD_KEEPER_TREVOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _r, _e, _v, _o, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route16_BirdKeeperTrevor_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_BirdKeeperTrevor_Divergent}
    },
    [TRAINER_ROUTE_16_LADY_MARIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_M, _a, _r, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route16_LadyMaria_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_LadyMaria_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_CHRISTINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _h, _r, _i, _s, _t, _i, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerChristina_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerChristina_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_M_PHILLIP] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_P, _h, _i, _l, _l, _i, _p, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerPhillip_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerPhillip_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_M_LESTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_L, _e, _s, _t, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerLester_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerLester_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_WENDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_W, _e, _n, _d, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerWendy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerWendy_Divergent}
    },
    [TRAINER_ROUTE_16_TUBER_CODY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_MALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = {_C, _o, _d, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route16_TuberCody_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_TuberCody_Divergent}
    },
    [TRAINER_ROUTE_16_TUBER_LESLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_FEMALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = {_L, _e, _s, _l, _i, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route16_TuberLeslie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_TuberLeslie_Divergent}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_CLEMENTINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _l, _e, _m, _e, _n, _t, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerClementine_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerClementine_Divergent}
    },
    // #endregion
    // #region Route 14
    [TRAINER_ROUTE_14_SWIMMER_M_IVAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_I, _v, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerIvan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerIvan_Divergent}
    },
    [TRAINER_ROUTE_14_HIKER_CLIFFORD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_C, _l, _i, _f, _f, _o, _r, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route14_HikerClifford_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_HikerClifford_Divergent}
    },
    [TRAINER_ROUTE_14_FISHERMAN_ESTEBAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_E, _s, _t, _e, _b, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route14_FishermanEsteban_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_FishermanEsteban_Divergent}
    },
    [TRAINER_ROUTE_14_FISHERMAN_TUCKER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_T, _u, _c, _k, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route14_FishermanTucker_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_FishermanTucker_Divergent}
    },
    [TRAINER_ROUTE_14_SWIMMER_F_ELEANOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_E, _l, _e, _a, _n, _o, _r, _END},
        .gender = FEMALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerEleanor_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerEleanor_Divergent}
    },
    [TRAINER_ROUTE_14_BLACKBELT_JOAQUIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_J, _o, _a, _q, _u, _i, _n, _END},
        .gender = MALE,
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route14_BlackbeltJoaquin_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_BlackbeltJoaquin_Divergent}
    },
    [TRAINER_ROUTE_14_SWIMMER_M_CHRIS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_C, _h, _r, _i, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerChris_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerChris_Divergent}
    },
    [TRAINER_ROUTE_14_YOUNGSTER_FREDDIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_F, _r, _e, _d, _d, _i, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route14_YoungsterFreddie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_YoungsterFreddie_Divergent}
    },
    [TRAINER_ROUTE_14_PSYCHIC_TOBIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_T, _o, _b, _i, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route14_PsychicTobin_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_PsychicTobin_Divergent}
    },
    [TRAINER_ROUTE_14_SWIMMER_F_MACIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _c, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerMacie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerMacie_Divergent}
    },    
    // #endregion
    // #region Route 15 North and South
    [TRAINER_ROUTE_15_NORTH_SWIMMER_MILES] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_M, _i, _l, _e, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerMiles_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerMiles_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_FIONA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_F, _i, _o, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerFiona_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerFiona_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_HIKER_KLAUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_K, _l, _a, _u, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route15North_HikerKlaus_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_HikerKlaus_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_URSULA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_U, _r, _s, _u, _l, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerUrsula_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerUrsula_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_QUINCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_Q, _u, _i, _n, _c, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerQuincy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerQuincy_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_COOL_TRAINER_WESLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_W, _e, _s, _l, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route15North_CoolTrainerWesley_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_CoolTrainerWesley_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_SUPER_NERD_ETHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _t, _h, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route15North_SuperNerdEthan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SuperNerdEthan_Divergent}
    },
    [TRAINER_ROUTE_15_NORTH_CHANNELER_LILA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_L, _i, _l, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route15North_ChannelerLila_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15North_ChannelerLila_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_GERALD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _e, _r, _a, _l, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerGerald_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerGerald_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_ALEXANDRA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_A, _l, _e, _x, _a, _n, _d, _r, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerAlexandra_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerAlexandra_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_BERNARD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _e, _r, _n, _a, _r, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerBernard_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerBernard_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_HAROLD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_H, _a, _r, _o, _l, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerHarold_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerHarold_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_MELINDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _e, _l, _i, _n, _d, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerMelinda_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerMelinda_Divergent}
    },
    [TRAINER_ROUTE_15_SOUTH_BLACKBELT_FRANKLIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_F, _r, _a, _n, _k, _l, _i, _n, _END},
        .gender = MALE,
        .items = {ITEM_X_DEFEND},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route15South_BlackbeltFranklin_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_BlackbeltFranklin_Divergent}
    },    
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_PATRICIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_P, _a, _t, _r, _i, _c, _i, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerPatricia_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerPatricia_Divergent}
    },
    // #endregion
    // #region Seppire Cove
    [TRAINER_SEPPIRE_COVE_SWIMMER_VALERIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_V, _a, _l, _e, _r, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_SeppireCove_SwimmerValerie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_SwimmerValerie_Divergent}
    },
    [TRAINER_SEPPIRE_COVE_SWIMMER_ICHABOD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_I, _c, _h, _a, _b, _o, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_SeppireCove_SwimmerIchabod_Divergent),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_SwimmerIchabod_Divergent}
    },
    [TRAINER_SEPPIRE_COVE_RUIN_MANIAC_CARTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_C, _a, _r, _t, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_SeppireCove_RuinManiacCarter_Divergent),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_RuinManiacCarter_Divergent}
    },    
    // #endregion
    // #region Route 19
    [TRAINER_ROUTE_19_LASS_SAMANTHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_S, _a, _m, _a, _n, _t, _h, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route19_LassSamantha_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route19_LassSamantha_Divergent}
    },
    [TRAINER_ROUTE_19_COOLTRAINER_ROSE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_R, _o, _s, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route19_CoolTrainerRose_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route19_CoolTrainerRose_Divergent}
    },
    [TRAINER_ROUTE_19_POKEFAN_PHINEAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_P, _h, _i, _n, _e, _a, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route19_PokefanPhineas_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route19_PokefanPhineas_Divergent}
    },
    [TRAINER_ROUTE_19_POKEFAN_PHOEBE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_P, _h, _o, _e, _b, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route19_PokefanPhoebe_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route19_PokefanPhoebe_Divergent}
    },
    // #endregion
    // #region Emraldin Quay
    [TRAINER_EMRALDIN_TRAINER_HOUSE_CHANNELER_MARGUERITE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _a, _r, _g, _u, _e, _r, _i, _t, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_ChannelerMarguerite_Divergent),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_ChannelerMarguerite_Divergent}
    },
    [TRAINER_EMRALDIN_TRAINER_HOUSE_NINJA_BOY_JULIEN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_J, _u, _l, _i, _e, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_NinjaBoyJulien_Divergent),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_NinjaBoyJulien_Divergent}
    },
    [TRAINER_EMRALDIN_TRAINER_HOUSE_BUG_CATCHER_PERRY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_P, _e, _r, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_BugCatcherPerry_Divergent),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_BugCatcherPerry_Divergent}
    },    
    // #endregion
    // #region Route 23
    [TRAINER_ROUTE_23_BIRD_KEEPER_TYRONE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _y, _r, _o, _n, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route23_BirdKeeperTyrone_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_BirdKeeperTyrone_Divergent}
    },
    [TRAINER_ROUTE_23_GAMBLER_GORDON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_G, _o, _r, _d, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route23_GamblerGordon_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_GamblerGordon_Divergent}
    },
    [TRAINER_ROUTE_23_SUPER_NERD_EMMETT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _m, _m, _e, _t, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route23_SuperNerdEmmett_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_SuperNerdEmmett_Divergent}
    },
    [TRAINER_ROUTE_23_GENTLEMAN_RUSSELL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_R, _u, _s, _s, _e, _l, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route23_GentlemanRussell_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_GentlemanRussell_Divergent}
    },
    [TRAINER_ROUTE_23_CRUSH_GIRL_LILY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_L, _i, _l, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route23_CrushGirlLily_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_CrushGirlLily_Divergent}
    },
    [TRAINER_ROUTE_23_BEAUTY_MIRANDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_M, _i, _r, _a, _n, _d, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route23_BeautyMiranda_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route23_BeautyMiranda_Divergent}
    },
    // #endregion
    // #region Route 20
    [TRAINER_ROUTE_20_PSYCHIC_MCKENZIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_M, _c, _K, _e, _n, _z, _i, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route20_PsychicMcKenzie_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_PsychicMcKenzie_Divergent}
    },
    [TRAINER_ROUTE_20_PICNICKER_WHITNEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_W, _h, _i, _t, _n, _e, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route20_PicknickerWhitney_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_PicknickerWhitney_Divergent}
    },
    [TRAINER_ROUTE_20_TRIATHLETE_LENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_L, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route20_TriathleteLena_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_TriathleteLena_Divergent}
    },
    [TRAINER_ROUTE_20_ENGINEER_HOMER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _o, _m, _e, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route20_EngineerHomer_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_EngineerHomer_Divergent}
    },
    [TRAINER_ROUTE_20_CRUSH_GIRL_ROXY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_R, _o, _x, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_X_SPEED },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route20_CrushGirlRoxy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_CrushGirlRoxy_Divergent}
    },
    [TRAINER_ROUTE_20_HIKER_ROYCE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _y, _c, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route20_HikerRoyce_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_HikerRoyce_Divergent}
    },
    [TRAINER_ROUTE_20_SUPER_NERD_ELLIOT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _l, _l, _i, _o, _t, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route20_SuperNerdElliot_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_SuperNerdElliot_Divergent}
    },
    [TRAINER_ROUTE_20_YOUNGSTER_DEWEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_D, _e, _w, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route20_YoungsterDewey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_YoungsterDewey_Divergent}
    },
    [TRAINER_ROUTE_20_JUGGLER_HIRAM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_H, _i, _r, _a, _m, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_Route20_JugglerHiram_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_JugglerHiram_Divergent}
    },
    [TRAINER_ROUTE_20_NURSE_JUDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_J, _u, _d, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_Route20_NurseJudy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route20_NurseJudy_Divergent}
    },
    // #endregion
    // #region Route 22
    [TRAINER_ROUTE_22_COOL_TRAINER_GAIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_G, _a, _i, _l, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route22_CoolTrainer_Gail_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route22_CoolTrainer_Gail_Divergent}
    },
    [TRAINER_ROUTE_22_SCIENTIST_LARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_L, _a, _r, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_Route22_ScientistLarry_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route22_ScientistLarry_Divergent}
    },
    [TRAINER_ROUTE_22_SRANDJR_ALMA_AND_MAI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_A, _l, _m, _a, _SPACE, _AMPERSAND, _SPACE, _M, _a, _i, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route22_SrAndJr_AlmaAndMai_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route22_SrAndJr_AlmaAndMai_Divergent}
    },
    [TRAINER_ROUTE_22_JUGGLER_CHAUNCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_C, _h, _a, _u, _n, _c, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_Route22_JugglerChauncy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route22_JugglerChauncy_Divergent}
    },
    [TRAINER_ROUTE_22_BURGLAR_MOSE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_M, _o, _s, _e, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_Route22_BurglarMose_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route22_BurglarMose_Divergent}
    },
    // #endregion
    // #region Route 21
    [TRAINER_ROUTE_21_POKEFAN_WALTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_W, _a, _l, _t, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_Route21_PokefanWalter_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_PokefanWalter_Divergent}
    },
    [TRAINER_ROUTE_21_COLLECTOR_ERIC] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_E, _r, _i, _c, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route21_CollectorEric_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_CollectorEric_Divergent}
    },
    [TRAINER_ROUTE_21_HIKER_RICARDO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _i, _c, _a, _r, _d, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route21_HikerRicardo_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_HikerRicardo_Divergent}
    },
    [TRAINER_ROUTE_21_DRAGON_TAMER_TANNER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_T, _a, _n, _n, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_Route21_DragonTamerTanner_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_DragonTamerTanner_Divergent}
    },
    [TRAINER_ROUTE_21_PARASOL_LADY_KATRINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_K, _a, _t, _r, _i, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route21_ParasolLadyKatrina_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_ParasolLadyKatrina_Divergent}
    },
    [TRAINER_ROUTE_21_NINJA_BOY_ISHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_I, _s, _h, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route21_NinjaBoyIshan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_NinjaBoyIshan_Divergent}
    },
    [TRAINER_ROUTE_21_ROCKER_AXEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_A, _x, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route21_RockerAxel_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_RockerAxel_Divergent}
    },
    [TRAINER_ROUTE_21_NURSE_BENEDIKTA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_B, _e, _n, _e, _d, _i, _k, _t, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_Route21_NurseBenedikta_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route21_NurseBenedikta_Divergent}
    },
    // #endregion
    // #region Secret Trail
    [TRAINER_SECRET_TRAIL_CHANNELER_HEATHER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_H, _e, _a, _t, _h, _e, _r, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_SecretTrail_ChannelerHeather_Divergent),
        .party = {.NoItemDefaultMoves = sParty_SecretTrail_ChannelerHeather_Divergent}
    },
    // #endregion
    // #region Mimmett Jungle
    [TRAINER_MIMMETT_JUNGLE_SCIENTIST_SILAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _i, _l, _a, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_ScientistSilas_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_ScientistSilas_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_RUIN_MANIAC_WINSTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_W, _i, _n, _s, _t, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_RuinManiacWinston_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_RuinManiacWinston_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_BLACKBELT_LOUIS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_L, _o, _u, _i, _s, _END},
        .gender = MALE,
        .items = { ITEM_X_SP_DEF },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_BlackbeltLouis_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_BlackbeltLouis_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_CHANNELER_FREYJA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_F, _r, _e, _y, _j, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_ChannelerFreyja_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_ChannelerFreyja_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_BUG_CATCHER_NEIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_N, _e, _i, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_BugCatcherNeil_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_BugCatcherNeil_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_FISHERMAN_JERRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_J, _e, _r, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_FishermanJerry_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_FishermanJerry_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_POKEFAN_SUSAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_S, _u, _s, _a, _n, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_PokefanSusan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_PokefanSusan_Divergent}
    },
    [TRAINER_MIMMETT_JUNGLE_PSYCHIC_WANDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_W, _a, _n, _d, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_PsychicWanda_Divergent),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_PsychicWanda_Divergent}
    },
    // #endregion
    // #region Tsarvosa City
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_KAITO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SENSEI,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerName = {_K, _a, _i, _t, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_Kaito_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_StatsDojo_Kaito_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed2_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed3_Divergent),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed3_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_COLLIN_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _l, _i, _n, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin1_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_COLLIN_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _l, _i, _n, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin2_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_CRYSTAL_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = {_C, _r, _y, _s, _t, _a, _l, _END },
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal1_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal1_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_CRYSTAL_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = {_C, _r, _y, _s, _t, _a, _l, _END },
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal2_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal2_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_NOAM] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_N, _o, _a, _m, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Noam_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Noam_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ASHLEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_A, _s, _h, _l, _e, _y, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ashley_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ashley_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CHELSEA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _h, _e, _l, _s, _e, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Chelsea_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Chelsea_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BUDDY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _u, _d, _d, _y, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Buddy_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Buddy_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_GAWAIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_G, _a, _w, _a, _i, _n, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Gawain_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Gawain_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SKYLAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_S, _k, _y, _l, _a, _r, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Skylar_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Skylar_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_B, _e, _l, _l, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Bella_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Bella_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FLASH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_F, _l, _a, _s, _h, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Flash_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Flash_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_TERRA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_RANGER_F,
        .trainerName = {_T, _e, _r, _r, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Terra_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Terra_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SEIFA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_S, _e, _i, _f, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Seifa_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Seifa_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ROCCO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _c, _c, _o, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Rocco_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Rocco_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_JANICE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_J, _a, _n, _i, _c, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Janice_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Janice_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ANTOINETTE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_A, _n, _t, _o, _i, _n, _e, _t, _t, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Antoinette_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Antoinette_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_RYU] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_R, _y, _u, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ryu_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ryu_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CASPAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_C, _a, _s, _p, _a, _r, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Caspar_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Caspar_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_DARCY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_D, _a, _r, _c, _y, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Darcy_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Darcy_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_MASON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_M, _a, _s, _o, _n, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Mason_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Mason_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FAYE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_F, _a, _y, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Faye_Divergent),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Faye_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_MARCI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_M, _a, _r, _c, _i, _END },
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_TsarvosaCityGym_PokefanMarci_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_PokefanMarci_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_JAMILA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_J, _a, _m, _i, _l, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_MAX_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_TsarvosaCityGym_ChannelerJamila_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_ChannelerJamila_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_NORBERT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_N, _o, _r, _b, _e, _r, _t, _END },
        .gender = MALE,
        .items = { ITEM_X_SP_ATK, ITEM_LEMONADE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_CoolTrainerNorbert_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_CoolTrainerNorbert_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_MARION] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_M, _a, _r, _i, _o, _n, _END },
        .gender = MALE,
        .items = { ITEM_MOOMOO_MILK, ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_TsarvosaCityGym_BurglarMarion_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_BurglarMarion_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_ALANAH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_A, _l, _a, _n, _a, _h, _END },
        .gender = FEMALE,
        .items = { ITEM_MOOMOO_MILK, ITEM_FULL_HEAL },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_LassAlanah_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_LassAlanah_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_PAUL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_P, _a, _u, _l, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_HP_AWARE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_GentlemanPaul_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_GentlemanPaul_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_LEADER_IRIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END },
        .gender = FEMALE,
        .items = { ITEM_MAX_POTION, ITEM_FULL_HEAL },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_TsarvosaCityGym_LeaderIris_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_LeaderIris_Divergent}
    },
    // #endregion
    // #region Daimyn City Restaurant
    [TRAINER_DAIMYN_CITY_RESTAURANT_IRIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Iris_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Iris_Divergent}
    },
    [TRAINER_DAIMYN_CITY_RESTAURANT_STELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_HEAL },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Stella_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Stella_Divergent}
    },
    // #endregion
    // #region Daimyn Factory
    [TRAINER_DAIMYN_FACTORY_BURGLAR_SLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_S, _l, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BurglarSly_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BurglarSly_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_HASAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _a, _s, _a, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerHasan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerHasan_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_BURGLAR_WILL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_W, _i, _l, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BurglarWill_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BurglarWill_Divergent}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_ELROY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_E, _l, _r, _o, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerElroy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerElroy_Divergent}
    },
    // #endregion
    // #region Carnelidge Volcano
    [TRAINER_CARNELIDGE_VOLCANO_HIKER_BJORN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_B, _j, _o, _r, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_HikerBjorn_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_HikerBjorn_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_CHANNELER_KELSEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_K, _e, _l, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_ChannelerKelsey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_ChannelerKelsey_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_JUGGLER_SETH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_S, _e, _t, _h, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_JugglerSeth_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_JugglerSeth_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_DRAGON_TAMER_FLYNN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_F, _l, _y, _n, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_DragonTamerFlynn_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_DragonTamerFlynn_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_BIRD_KEEPER_FALCO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_F, _a, _l, _c, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_BirdKeepeFalco_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_BirdKeepeFalco_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_CRUSH_GIRL_EUNICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _u, _n, _i, _c, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_X_SPEED },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_CrushGirlEunice_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_CrushGirlEunice_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_SUPER_NERD_NATHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_N, _a, _t, _h, _a, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_SuperNerdNathan_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_SuperNerdNathan_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_HIKER_HUGH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_H, _u, _g, _h, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_HikerHugh_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_HikerHugh_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_SCIENTIST_XANDER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_X, _a, _n, _d, _e, _r, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_ScientistXander_Divergent),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_ScientistXander_Divergent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_PARTNER_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_SEMI_SMART | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_PartnerRival_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_PartnerRival_Divergent}
    },
    // #endregion
    // #region Uteya Village
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_PICKNICKER_LISA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_L, _i, _s, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_PicknickerLisa_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_PicknickerLisa_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_SWIMMER_TYSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_T, _y, _s, _o, _n, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_SwimmerTyson_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_SwimmerTyson_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_SCIENTIST_WILFORD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_W, _i, _l, _f, _o, _r, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_ScientistWilford_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_ScientistWilford_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_MICHAEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_M, _i, _c, _h, _a, _e, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Michael_Divergent),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Michael_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_LEO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_L, _e, _o, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Leo_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Leo_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_BONNIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_B, _o, _n, _n, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Bonnie_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Bonnie_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_CLYDE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _l, _y, _d, _e, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Clyde_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Clyde_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_JESSIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_J, _e, _s, _s, _i, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Jessie_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Jessie_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_JAMES] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _a, _m, _e, _s, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_James_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_James_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_MIKE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_M, _i, _k, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Mike_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Mike_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_DIANE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_D, _i, _a, _n, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Diane_Divergent),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Diane_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_HANNIBAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_H, _a, _n, _n, _i, _b, _a, _l, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Hannibal_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Hannibal_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_CLARICE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_C, _l, _a, _r, _i, _c, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Clarice_Divergent),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Clarice_Divergent}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_LEADERS_DENNIS_AND_DEE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // Gender omitted; chosen randomly between the two
        .items = {ITEM_MAX_POTION},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SEMI_SMART | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_LeadersDennisAndDee_Divergent),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_LeadersDennisAndDee_Divergent}
    },
    // #endregion
    // #region Route 24
    [TRAINER_ROUTE_24_PSYCHIC_RAYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_R, _a, _y, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route24_PsychicRaya_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_PsychicRaya_Divergent}
    },
    [TRAINER_ROUTE_24_DRAGON_TAMER_DAVID] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_D, _a, _v, _i, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_Route24_DragonTamerDavid_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_DragonTamerDavid_Divergent}
    },
    [TRAINER_ROUTE_24_PSYCHIC_JEFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_J, _e, _f, _f, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route24_PsychicJeff_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_PsychicJeff_Divergent}
    },
    [TRAINER_ROUTE_24_FISHERMAN_HUMPHREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_H, _u, _m, _p, _h, _r, _e, _y, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route24_FishermanHumphrey_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_FishermanHumphrey_Divergent}
    },
    [TRAINER_ROUTE_24_TRIATHLETE_WILLOW] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_W, _i, _l, _l, _o, _w, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route24_TriathleteWillow_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_TriathleteWillow_Divergent}
    },
    [TRAINER_ROUTE_24_BLACKBELT_IRVINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_I, _r, _v, _i, _n, _e, _END},
        .gender = MALE,
        .items = { ITEM_DIRE_HIT },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route24_BlackbeltIrvine_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route24_BlackbeltIrvine_Divergent}
    },
    // #endregion
    // #region Uteyan Ruins
    [TRAINER_UTEYAN_RUINS_RUIN_MANIAC_KRISTIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_K, _r, _i, _s, _t, _i, _a, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_RuinManiacKristian_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_RuinManiacKristian_Divergent}
    },
    [TRAINER_UTEYAN_RUINS_PSYCHIC_HALEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_H, _a, _l, _e, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_PsychicHaley_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_PsychicHaley_Divergent}
    },
    [TRAINER_UTEYAN_RUINS_RUIN_MANIAC_CYRIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_C, _y, _r, _i, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_RuinManiacCyril_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_RuinManiacCyril_Divergent}
    },
    [TRAINER_UTEYAN_RUINS_SUPER_NERD_MORTY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_M, _o, _r, _t, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_SuperNerdMorty_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_SuperNerdMorty_Divergent}
    },
    [TRAINER_UTEYAN_RUINS_CHANNELER_AGATHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_A, _g, _a, _t, _h, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_ChannelerAgatha_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_ChannelerAgatha_Divergent}
    },
    [TRAINER_UTEYAN_RUINS_LASS_DOROTHY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_D, _o, _r, _o, _t, _h, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_LassDorothy_Divergent),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_LassDorothy_Divergent}
    },
    // #endregion
    // #region Victory Road
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_TIMOTHY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_T, _i, _m, _o, _t, _h, _y, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerTimothy_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerTimothy_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_JONATHAN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _o, _n, _a, _t, _h, _a, _n, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerJonathan_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerJonathan_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_SATOSHI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_S, _a, _t, _o, _s, _h, _i, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerSatoshi_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerSatoshi_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_COURTNEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_C, _o, _u, _r, _t, _n, _e, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerCourtney_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerCourtney_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_THERESA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_T, _h, _e, _r, _e, _s, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerTheresa_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerTheresa_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ABDUL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _b, _d, _u, _l, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerAbdul_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerAbdul_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ARTHUR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _r, _t, _h, _u, _r, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerArthur_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerArthur_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_KELLY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_K, _e, _l, _l, _y, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerKelly_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerKelly_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_LYDIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_L, _y, _d, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerLydia_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerLydia_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ROBIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_R, _o, _b, _i, _n, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerRobin_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerRobin_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_LUIGI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_L, _u, _i, _g, _i, _END},
        .gender = MALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerLuigi_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerLuigi_Divergent}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_DAHLIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_D, _a, _h, _l, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerDahlia_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerDahlia_Divergent}
    },
    [TRAINER_VICTORY_ROAD_NURSE_CELIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_C, _e, _l, _i, _a, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_NurseCelia_Divergent),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_NurseCelia_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Vaporeon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Jolteon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Flareon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Espeon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Umbreon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Leafeon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Glaceon_Divergent}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Sylveon_Divergent}
    },
    // #endregion
    // #region Ascension Tower & Post Credits
    [TRAINER_DAIMYN_CITY_RIVAL_EXHIBITION_BATTLE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_ExhibitionBattle_SecondaryTeam_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_ExhibitionBattle_SecondaryTeam_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_HANNAH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_HANNAH,
        .trainerName = {_H, _a, _n, _n, _a, _h, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Hannah_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Hannah_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_LUCAS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_LUCAS,
        .trainerName = {_L, _u, _c, _a, _s, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Lucas_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Lucas_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_JENNA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_JENNA,
        .trainerName = {_J, _e, _n, _n, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Jenna_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Jenna_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_THOMAS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_THOMAS,
        .trainerName = {_T, _h, _o, _m, _a, _s, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Thomas_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Thomas_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_CHAMPION_SELENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHAMPION,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_CHAMPION_SELENE,
        .trainerName = {_S, _e, _l, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_Champion_Selene_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_Champion_Selene_Divergent}
    },
    [TRAINER_ANTHRA_TOWN_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_ALISTAIR,
        .trainerName = {_A, _l, _i, _s, _t, _a, _i, _r, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_PostCredits_Alistair_Divergent),
        .party = {.ItemCustomMoves = sParty_PostCredits_Alistair_Divergent}
    },
    // #endregion
    // #region Gym Leader Rematches
    [TRAINER_LEADER_TERRENCE_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Terrence_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Terrence_1_Divergent}
    },
    [TRAINER_LEADER_TERRENCE_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Terrence_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Terrence_2_Divergent}
    },
    [TRAINER_LEADER_TERRENCE_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Terrence_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Terrence_3_Divergent}
    },
    [TRAINER_LEADER_TERRENCE_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Terrence_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Terrence_4_Divergent}
    },
    [TRAINER_LEADER_STELLA_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Stella_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Stella_1_Divergent}
    },
    [TRAINER_LEADER_STELLA_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Stella_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Stella_2_Divergent}
    },
    [TRAINER_LEADER_STELLA_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Stella_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Stella_3_Divergent}
    },
    [TRAINER_LEADER_STELLA_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Stella_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Stella_4_Divergent}
    },
    [TRAINER_LEADER_RAINE_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Raine_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Raine_1_Divergent}
    },
    [TRAINER_LEADER_RAINE_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Raine_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Raine_2_Divergent}
    },
    [TRAINER_LEADER_RAINE_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Raine_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Raine_3_Divergent}
    },
    [TRAINER_LEADER_RAINE_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Raine_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Raine_4_Divergent}
    },
    [TRAINER_LEADER_CHANCE_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Chance_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Chance_1_Divergent}
    },
    [TRAINER_LEADER_CHANCE_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Chance_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Chance_2_Divergent}
    },
    [TRAINER_LEADER_CHANCE_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Chance_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Chance_3_Divergent}
    },
    [TRAINER_LEADER_CHANCE_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Chance_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Chance_4_Divergent}
    },
    [TRAINER_LEADER_CASEY_F_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_1_Divergent}
    },
    [TRAINER_LEADER_CASEY_F_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_2_Divergent}
    },
    [TRAINER_LEADER_CASEY_F_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_3_Divergent}
    },
    [TRAINER_LEADER_CASEY_F_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_4_Divergent}
    },
    [TRAINER_LEADER_CASEY_M_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_1_Divergent}
    },
    [TRAINER_LEADER_CASEY_M_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_2_Divergent}
    },
    [TRAINER_LEADER_CASEY_M_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_3_Divergent}
    },
    [TRAINER_LEADER_CASEY_M_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_GymLeaderRematches_Casey_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Casey_4_Divergent}
    },
    [TRAINER_LEADER_ABBY_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Abby_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Abby_1_Divergent}
    },
    [TRAINER_LEADER_ABBY_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Abby_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Abby_2_Divergent}
    },
    [TRAINER_LEADER_ABBY_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Abby_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Abby_3_Divergent}
    },
    [TRAINER_LEADER_ABBY_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Abby_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Abby_4_Divergent}
    },
    [TRAINER_LEADER_IRIS_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Iris_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Iris_1_Divergent}
    },
    [TRAINER_LEADER_IRIS_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Iris_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Iris_2_Divergent}
    },
    [TRAINER_LEADER_IRIS_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Iris_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Iris_3_Divergent}
    },
    [TRAINER_LEADER_IRIS_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END},
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard,
        .partySize = NELEMS(sParty_GymLeaderRematches_Iris_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_Iris_4_Divergent}
    },
    [TRAINER_LEADERS_DENNIS_AND_DEE_REMATCH_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // No gender set; chosen at random
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_GymLeaderRematches_DennisAndDee_1_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_DennisAndDee_1_Divergent}
    },
    [TRAINER_LEADERS_DENNIS_AND_DEE_REMATCH_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // No gender set; chosen at random
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_GymLeaderRematches_DennisAndDee_2_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_DennisAndDee_2_Divergent}
    },
    [TRAINER_LEADERS_DENNIS_AND_DEE_REMATCH_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // No gender set; chosen at random
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_GymLeaderRematches_DennisAndDee_3_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_DennisAndDee_3_Divergent}
    },
    [TRAINER_LEADERS_DENNIS_AND_DEE_REMATCH_4] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // No gender set; chosen at random
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_GymLeaderRematches_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_GymLeaderRematches_DennisAndDee_4_Divergent),
        .party = {.ItemCustomMoves = sParty_GymLeaderRematches_DennisAndDee_4_Divergent}
    },
    // #endregion
    // #region Route 13 Cave
    [TRAINER_ROUTE_13_CAVE_PLUTO_LEADER_KURTIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_LEADER,
        .trainerPic = TRAINER_PIC_PLUTO_LEADER_KURTIS,
        .trainerName = {_K, _u, _r, _t, _i, _s, _END},
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_MEGA_RING },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route13Cave_TeamPlutoLeaderKurtis_Divergent),
        .party = {.ItemCustomMoves = sParty_Route13Cave_TeamPlutoLeaderKurtis_Divergent}
    },
    // #region Elite Four Rematches
    [TRAINER_ASCENSION_TOWER_E4_HANNAH_REMATCH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_HANNAH,
        .trainerName = {_H, _a, _n, _n, _a, _h, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_HannahRematch_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_HannahRematch_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_LUCAS_REMATCH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_LUCAS,
        .trainerName = {_L, _u, _c, _a, _s, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_LucasRematch_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_LucasRematch_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_JENNA_REMATCH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_JENNA,
        .trainerName = {_J, _e, _n, _n, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_JennaRematch_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_JennaRematch_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_E4_THOMAS_REMATCH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_ELITE_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_E4_THOMAS,
        .trainerName = {_T, _h, _o, _m, _a, _s, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_ThomasRematch_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_ThomasRematch_Divergent}
    },
    // #endregion
    // #region Title Defense
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Jolteon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Flareon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Espeon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Umbreon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Leafeon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Glaceon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Sylveon_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_JOEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_J, _o, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_YoungsterJoey_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_YoungsterJoey_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_SELENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHAMPION_SELENE,
        .trainerName = {_S, _e, _l, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Selene_WithVictini_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Selene_WithVictini_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_SELENE_AFTER_VICTINI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHAMPION_SELENE,
        .trainerName = {_S, _e, _l, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Selene_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Selene_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ALISTAIR,
        .trainerName = {_A, _l, _i, _s, _t, _a, _i, _r, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Alistair_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Alistair_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_HAWTHORNE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PROF_HAWTHORNE,
        .trainerName = {_H, _a, _w, _t, _h, _o, _r, _n, _e, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Hawthorne_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Hawthorne_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_CLANCY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Clancy_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Clancy_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_ENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_E, _n, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Ena_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Ena_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_COPYCAT_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PLAYER_M,
        .trainerName = {_C, _a, _l, _e, _b, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Copycat_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Copycat_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_COPYCAT_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PLAYER_F,
        .trainerName = {_E, _m, _i, _l, _y, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Copycat_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Copycat_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_FOREIGNER] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_F, _e, _l, _i, _x, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Felix_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Felix_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_COLLIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _l, _i, _n, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Collin_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Collin_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_CRYSTAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = {_C, _r, _y, _s, _t, _a, _l, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Crystal_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Crystal_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Irene_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Irene_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Ronald_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Ronald_Divergent}
    },
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_KURTIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PLUTO_LEADER_KURTIS,
        .trainerName = {_K, _u, _r, _t, _i, _s, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Standard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Kurtis_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Kurtis_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Vaporeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Vaporeon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Jolteon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Jolteon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Flareon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Flareon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Espeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Espeon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Umbreon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Umbreon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Leafeon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Leafeon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Glaceon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Glaceon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Sylveon_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Sylveon_Divergent}
    },
    [TRAINER_POSTGAME_RIVAL_EXHIBITION_BATTLE_EMRALDIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Divergent}
    },
    // #endregion
    // #region Ferrox Village (Postgame)
    [TRAINER_HELEO_CITY_NURSE_BRIANNE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_B, _r, _i, _a, _n, _n, _e, _END},
        .gender = FEMALE,
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_NurseBrianne_Divergent),
        .party = {.NoItemCustomMoves = sParty_HeleoCity_NurseBrianne_Divergent}
    }
    // #endregion
    // #endregion
};
// #endregion
