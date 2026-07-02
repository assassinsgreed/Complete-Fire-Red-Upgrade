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
const struct TrainerMonNoItemDefaultMoves sParty_Rival1_Divergent[] = {
    { .iv = 0, .lvl = 5, .species = SPECIES_EEVEE }, // Identical to base, but kept in for simplicity
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
        .species = SPECIES_GOLBAT,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_LEECHLIFE, MOVE_MEANLOOK },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 54,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_INGRAIN, MOVE_GIGADRAIN, MOVE_SUBSTITUTE, MOVE_CLEARSMOG },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 56,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 57,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_SUNNYDAY, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Vaporeon_Divergent[] = {
    {
        .lvl = 65,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 65,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 65,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 65,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CROBAT,
        .moves = { MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_CROSSPOISON, MOVE_HAZE },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 70,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_SPORE, MOVE_TOXIC, MOVE_BODYSLAM, MOVE_PROTECT },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 70,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 70,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_DESTINYBOND, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 71,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 72,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
    { .iv = 0, .lvl = 3, .species = SPECIES_BIDOOF },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_LassHelena_Divergent[] = {
    { .lvl = 3, .species = SPECIES_FLETCHLING },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterHarlan_Divergent[] = {
    { .lvl = 4, .species = SPECIES_YAMPER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_BurglarBryce_Divergent[] = {
    { .lvl = 48, .species = SPECIES_GRIMER_A },
    { .lvl = 48, .species = SPECIES_KOFFING_G },
    { .lvl = 50, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_SwimmerRebecca_Divergent[] = {
    { .lvl = 50, .species = SPECIES_FRILLISH_F },
    { .lvl = 51, .species = SPECIES_JELLICENT_F },
};
// #endregion

// #region Route 2
const struct TrainerMonNoItemDefaultMoves sParty_Route2_YoungsterJoey_Divergent[] = {
    { .lvl = 5, .species = SPECIES_RATTATA_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassKimberly_Divergent[] = {
    { .lvl = 4, .species = SPECIES_RALTS },
    { .lvl = 4, .species = SPECIES_CUTIEFLY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassRikki_Divergent[] = {
    { .lvl = 7, .species = SPECIES_FLABEBE_BLUE },
    { .lvl = 7, .species = SPECIES_FLABEBE_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_CoolTrainerAndy_Divergent[] = {
    { .lvl = 50, .species = SPECIES_TORKOAL },
    { .lvl = 50, .species = SPECIES_CRAWDAUNT },
    { .lvl = 52, .species = SPECIES_SLAKING },
};
// #endregion

// #region Varisi Forest
const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherKendell_Divergent[] = {
    { .lvl = 4, .species = SPECIES_BLIPBUG },
    { .lvl = 5, .species = SPECIES_BLIPBUG },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherBraden_Divergent[] = {
    { .lvl = 4, .species = SPECIES_BLIPBUG },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassBreanna_Divergent[] = {
    { .lvl = 5, .species = SPECIES_PICHU },
    { .lvl = 6, .species = SPECIES_BUDEW },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassMimi_Divergent[] = {
    { .lvl = 5, .species = SPECIES_BUNEARY },
    { .lvl = 6, .species = SPECIES_PIKIPEK },
    { .lvl = 7, .species = SPECIES_SHROOMISH },
};
// #endregion

// #region Rhodanzi City
const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Alonso_Divergent[] = {
    {
        .lvl = 9,
        .species = SPECIES_MIME_JR_G,
        .moves = { MOVE_MISTYTERRAIN, MOVE_PSYCHICTERRAIN, MOVE_CONFUSION, MOVE_NONE },
        .ability = Ability_1 // Soundproof
    },
    {
        .lvl = 8,
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_TERRAINPULSE, MOVE_WATERGUN, MOVE_MUDSLAP, MOVE_NONE },
        .ability = Ability_1 // Mimicry
    },
};

const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Brandon_Divergent[] = {
    {
        .lvl = 10,
        .species = SPECIES_PINCURCHIN,
        .moves = { MOVE_CHARGE, MOVE_THUNDERSHOCK, MOVE_PECK, MOVE_NONE },
        .ability = Ability_Hidden // Electric Surge
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
    { .lvl = 9, .species = SPECIES_NIDORAN_M },
    { .lvl = 10, .species = SPECIES_PIKIPEK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_BugCatcherIrwin_Divergent[] = {
    { .lvl = 8, .species = SPECIES_GRUBBIN },
    { .lvl = 8, .species = SPECIES_BLIPBUG },
    { .lvl = 10, .species = SPECIES_DOTTLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_YoungsterLogan_Divergent[] = {
    { .lvl = 10, .species = SPECIES_DRILBUR },
    { .lvl = 11, .species = SPECIES_ROCKRUFF }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TwinsNinaAndMeg_Divergent[] = {
    { .lvl = 12, .species = SPECIES_MORELULL },
    { .lvl = 10, .species = SPECIES_COMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_NinjaBoyBotan_Divergent[] = {
    { .lvl = 11, .species = SPECIES_NINCADA },
    { .lvl = 11, .species = SPECIES_FERROSEED },
    { .lvl = 11, .species = SPECIES_FARFETCHD_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_RockerJude_Divergent[] = {
    { .lvl = 13, .species = SPECIES_GROOKEY },
    { .lvl = 14, .species = SPECIES_TOXEL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TeamPlutoRaul_Divergent[] = {
    { .lvl = 12, .species = SPECIES_NICKIT },
    { .lvl = 13, .species = SPECIES_ZUBAT }
};
// #endregion

// #region Rubarr Desert
const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_NurseJaina_Divergent[] = {
    { .lvl = 12, .species = SPECIES_HAPPINY },
    { .lvl = 13, .species = SPECIES_TOGEPI },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_BirdKeeperNolan_Divergent[] = {
    { .lvl = 13, .species = SPECIES_ROOKIDEE },
    { .lvl = 13, .species = SPECIES_VULLABY },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacKent_Divergent[] = {
    { .lvl = 12, .species = SPECIES_ROGGENROLA },
    { .lvl = 12, .species = SPECIES_ROGGENROLA },
    { .lvl = 13, .species = SPECIES_ROGGENROLA },
};

const struct TrainerMonItemDefaultMoves sParty_RubarrDesert_BlackbeltKobiyashi_Divergent[] = {
    { .lvl = 13, .species = SPECIES_FARFETCHD_G },
    { .lvl = 14, .species = SPECIES_SCRAGGY },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacAlbert_Divergent[] = {
    { .lvl = 14, .species = SPECIES_BONSLY },
    { .lvl = 14, .species = SPECIES_YAMASK_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMika_Divergent[] = {
    { .lvl = 12, .species = SPECIES_NICKIT },
    { .lvl = 12, .species = SPECIES_NICKIT },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMarcel_Divergent[] = {
    { .lvl = 11, .species = SPECIES_ZUBAT },
    { .lvl = 11, .species = SPECIES_ZUBAT },
    { .lvl = 13, .species = SPECIES_SANDILE },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoTana_Divergent[] = {
    { .lvl = 12, .species = SPECIES_SANDILE },
    { .lvl = 12, .species = SPECIES_KOFFING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoClancy_Divergent[] = {
    { .lvl = 14, .species = SPECIES_CROAGUNK },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoEna_Divergent[] = {
    { .lvl = 12, .species = SPECIES_ZUBAT },
    { .lvl = 13, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene_Divergent[] = {
    {
        .lvl = 14,
        .species = SPECIES_NICKIT,
        .moves = { MOVE_SNARL, MOVE_BEATUP, MOVE_HONECLAWS, MOVE_QUICKATTACK },
        .ability = Ability_Hidden // Stakeout
    },
    {
        .lvl = 14,
        .species = SPECIES_SANDILE,
        .moves = { MOVE_BITE, MOVE_HONECLAWS, MOVE_SANDTOMB, MOVE_MEANLOOK },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 15,
        .species = SPECIES_SALANDIT,
        .moves = { MOVE_EMBER, MOVE_SMOG, MOVE_FAKEOUT, MOVE_SCRATCH },
        .ability = Ability_1 // Corrosion
    },
};
// #endregion

// #region Route 4
const struct TrainerMonNoItemDefaultMoves sParty_Route4_Camper_Pietro_Divergent[] = {
    { .lvl = 12, .species = SPECIES_FLETCHLING },
    { .lvl = 12, .species = SPECIES_NIDORAN_M },
    { .lvl = 13, .species = SPECIES_WYNAUT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Psychic_Adriano_Divergent[] = {
    { .lvl = 13, .species = SPECIES_RALTS },
    { .lvl = 13, .species = SPECIES_INKAY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Beauty_Beatrice_Divergent[] = {
    { .lvl = 13, .species = SPECIES_CUTIEFLY },
    { .lvl = 14, .species = SPECIES_BUNEARY },
};

const struct TrainerMonItemDefaultMoves sParty_Route4_Lady_Alda_Divergent[] = {
    { .lvl = 14, .species = SPECIES_BUDEW },
    { .lvl = 14, .species = SPECIES_COMBEE },
    { .lvl = 14, .species = SPECIES_FLABEBE_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Lass_Isabela_Divergent[] = {
    { .lvl = 15, .species = SPECIES_YAMPER },
    { .lvl = 15, .species = SPECIES_SLAKOTH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Rowley_Divergent[] = {
    { .lvl = 17, .species = SPECIES_DARTRIX }
};

const struct TrainerMonItemDefaultMoves sParty_Route4_Crush_Girl_Elise_Divergent[] = {
    { .lvl = 14, .species = SPECIES_CROAGUNK },
    { .lvl = 15, .species = SPECIES_FARFETCHD_G },
    { .lvl = 15, .species = SPECIES_TIMBURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Gentleman_Porter_Divergent[] = {
    { .lvl = 15, .species = SPECIES_MIME_JR_G },
    { .lvl = 16, .species = SPECIES_HERDIER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Luca_Divergent[] = {
    { .lvl = 15, .species = SPECIES_HOOTHOOT },
    { .lvl = 17, .species = SPECIES_FLETCHINDER },
};
// #endregion

// #region Torma Cave
const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Fisherman_Alfie_Divergent[] = {
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Nob_Divergent[] = {
    { .lvl = 13, .species = SPECIES_BONSLY },
    { .lvl = 14, .species = SPECIES_SHUCKLE },
    { .lvl = 15, .species = SPECIES_RIOLU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Saul_Divergent[] = {
    { .lvl = 16, .species = SPECIES_ROLYCOLY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Wyatt_Divergent[] = {
    { .lvl = 14, .species = SPECIES_PIKACHU },
    { .lvl = 14, .species = SPECIES_CHINCHOU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Shane_Divergent[] = {
    { .lvl = 14, .species = SPECIES_PINCURCHIN },
    { .lvl = 14, .species = SPECIES_KLINK },
    { .lvl = 14, .species = SPECIES_MAWILE },
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Pokefan_Corey_Divergent[] = {
    { .lvl = 16, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Lass_Harmony_Divergent[] = {
    { .lvl = 15, .species = SPECIES_BUNEARY },
    { .lvl = 15, .species = SPECIES_ROSELIA },
};
// #endregion

// #region Route 7
const struct TrainerMonNoItemDefaultMoves sParty_Route7_CamperCarlisle_Divergent[] = {
    { .lvl = 8, .species = SPECIES_NIDORAN_M },
    { .lvl = 10, .species = SPECIES_DOTTLER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_RockerJonas_Divergent[] = {
    { .lvl = 17, .species = SPECIES_TOXEL },
    { .lvl = 18, .species = SPECIES_TRAPINCH },
    { .lvl = 19, .species = SPECIES_THWACKEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_LassEden_Divergent[] = {
    { .lvl = 17, .species = SPECIES_HATENNA },
    { .lvl = 18, .species = SPECIES_SLOWPOKE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_HikerDanny_Divergent[] = {
    { .lvl = 18, .species = SPECIES_TYRUNT },
    { .lvl = 18, .species = SPECIES_MUDBRAY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_CrushGirlEden_Divergent[] = {
    { .lvl = 18, .species = SPECIES_COMBUSKEN },
    { .lvl = 19, .species = SPECIES_TIMBURR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_PsychicIshaan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_ELGYEM },
    { .lvl = 19, .species = SPECIES_INKAY },
};
// endregion

// #endregion

// #region Route 13
const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerDalton_Divergent[] = {
    { .lvl = 14, .species = SPECIES_ZORUA },
    { .lvl = 14, .species = SPECIES_TOXEL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorCharlie_Divergent[] = {
    { .lvl = 16, .species = SPECIES_LARVESTA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_HikerDwayne_Divergent[] = {
    { .lvl = 15, .species = SPECIES_ROLYCOLY },
    { .lvl = 16, .species = SPECIES_PIGNITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BlackBeltHector_Divergent[] = {
    { .lvl = 14, .species = SPECIES_TIMBURR },
    { .lvl = 14, .species = SPECIES_TIMBURR },
    { .lvl = 15, .species = SPECIES_MIENFOO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_PicknickerEtie_Divergent[] = {
    { .lvl = 16, .species = SPECIES_SKIDDO },
    { .lvl = 16, .species = SPECIES_NIDORINO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BeautyCandice_Divergent[] = {
    { .lvl = 28, .species = SPECIES_LYCANROC_DUSK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerOwain_Divergent[] = {
    { .lvl = 26, .species = SPECIES_PIKACHU },
    { .lvl = 27, .species = SPECIES_LUCARIO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorBenji_Divergent[] = {
    { .lvl = 47, .species = SPECIES_HAKAMO_O },
    { .lvl = 48, .species = SPECIES_SABLEYE },
    { .lvl = 50, .species = SPECIES_SHEDINJA },
};
// #endregion

// #region Ferrox Village
const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLaurena_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_FLABEBE_ORANGE,
        .moves = { MOVE_FAIRYWIND, MOVE_LUCKYCHANT, MOVE_RAZORLEAF, MOVE_ATTRACT },
        .ability = Ability_1 // Flower Veil
    },
    {
        .lvl = 17,
        .species = SPECIES_PHANTUMP,
        .moves = { MOVE_ASTONISH, MOVE_CONFUSERAY, MOVE_BRANCHPOKE, MOVE_NONE },
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLona_Divergent[] = {
    {
        .lvl = 19,
        .species = SPECIES_MORELULL,
        .moves = { MOVE_CONFUSERAY, MOVE_ASTONISH, MOVE_ABSORB, MOVE_SLEEPPOWDER },
        .ability = Ability_2 // Effect Spore
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerChet_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_PIKACHU,
        .moves = { MOVE_NUZZLE, MOVE_THUNDERSHOCK, MOVE_SWEETKISS, MOVE_QUICKATTACK },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 18,
        .species = SPECIES_NIDORINO,
        .moves = { MOVE_POISONTAIL, MOVE_PECK, MOVE_FOCUSENERGY, MOVE_LEER },
        .ability = Ability_1 // Poison Point
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerVincent_Divergent[] = {
    {
        .lvl = 17,
        .species = SPECIES_DUSKULL,
        .moves = { MOVE_ASTONISH, MOVE_DISABLE, MOVE_CONFUSERAY, MOVE_CURSE },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 17,
        .species = SPECIES_SHROOMISH,
        .moves = { MOVE_ABSORB, MOVE_LEECHSEED, MOVE_STUNSPORE, MOVE_HEADBUTT },
        .ability = Ability_1 // Effect Spore
    },
    {
        .lvl = 18,
        .species = SPECIES_JOLTIK,
        .moves = { MOVE_ELECTROWEB, MOVE_BUGBITE, MOVE_THUNDERWAVE, MOVE_ABSORB },
        .ability = Ability_1 // Compound Eyes
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
const struct TrainerMonItemDefaultMoves sParty_Route5_LadyFaith_Divergent[] = {
    { .lvl = 17, .species = SPECIES_ROSELIA },
    { .lvl = 17, .species = SPECIES_COTTONEE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_BugCatcher_Ben_Divergent[] = {
    { .lvl = 17, .species = SPECIES_DOTTLER },
    { .lvl = 17, .species = SPECIES_CHARJABUG },
    { .lvl = 18, .species = SPECIES_NINCADA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Psychic_Alyssia_Divergent[] = {
    { .lvl = 18, .species = SPECIES_KIRLIA },
    { .lvl = 18, .species = SPECIES_HATENNA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Breeder_Brenda_Divergent[] = {
    { .lvl = 12, .species = SPECIES_BUDEW },
    { .lvl = 12, .species = SPECIES_WYNAUT },
    { .lvl = 12, .species = SPECIES_BONSLY },
    { .lvl = 12, .species = SPECIES_MIME_JR_G },
    { .lvl = 12, .species = SPECIES_PICHU },
    { .lvl = 12, .species = SPECIES_HAPPINY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Blackbelt_Raheem_Divergent[] = {
    { .lvl = 18, .species = SPECIES_TIMBURR },
    { .lvl = 19, .species = SPECIES_RIOLU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gambler_Dominik_Divergent[] = {
    { .lvl = 18, .species = SPECIES_ZORUA },
    { .lvl = 18, .species = SPECIES_CROAGUNK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Lady_Juliet_Divergent[] = {
    { .lvl = 17, .species = SPECIES_PIKACHU },
    { .lvl = 17, .species = SPECIES_EEVEE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gentleman_Marcus_Divergent[] = {
    { .lvl = 18, .species = SPECIES_CORVISQUIRE },
    { .lvl = 18, .species = SPECIES_QUILLADIN },
};
// #endregion

// #region Heleo Ranch
const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Burglar_Cole_Divergent[] = {
    { .lvl = 18, .species = SPECIES_KOFFING_G },
    { .lvl = 17, .species = SPECIES_NICKIT },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Camper_Troy_Divergent[] = {
    { .lvl = 17, .species = SPECIES_LILLIPUP },
    { .lvl = 17, .species = SPECIES_BIBAREL },
    { .lvl = 18, .species = SPECIES_CORVISQUIRE },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Breeder_Laura_Divergent[] = {
    { .lvl = 14, .species = SPECIES_SUNKERN },
    { .lvl = 14, .species = SPECIES_RALTS },
    { .lvl = 14, .species = SPECIES_TOGEPI },
    { .lvl = 14, .species = SPECIES_PICHU },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Picknicker_Carly_Divergent[] = {
    { .lvl = 18, .species = SPECIES_FLETCHLING },
    { .lvl = 18, .species = SPECIES_CACNEA },
    { .lvl = 19, .species = SPECIES_FLOETTE_WHITE }
};
// #endregion

// #region Route 6
const struct TrainerMonNoItemDefaultMoves sParty_Route6_Youngster_Ned_Divergent[] = {
    { .lvl = 19, .species = SPECIES_TRUMBEAK },
    { .lvl = 20, .species = SPECIES_RATICATE_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_NinjaBoy_Rajan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_NINCADA },
    { .lvl = 19, .species = SPECIES_SUDOWOODO },
    { .lvl = 19, .species = SPECIES_TRAPINCH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Hiker_Romero_Divergent[] = {
    { .lvl = 19, .species = SPECIES_CARBINK },
    { .lvl = 19, .species = SPECIES_SHUCKLE },
    { .lvl = 20, .species = SPECIES_MAWILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Estevan_Divergent[] = {
    { .lvl = 19, .species = SPECIES_ROCKRUFF },
    { .lvl = 20, .species = SPECIES_VIGOROTH },
    { .lvl = 21, .species = SPECIES_DRATINI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Engineer_Harry_Divergent[] = {
    { .lvl = 20, .species = SPECIES_CHARJABUG },
    { .lvl = 20, .species = SPECIES_KLINK },
    { .lvl = 20, .species = SPECIES_PACHIRISU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gambler_Mick_Divergent[] = {
    { .lvl = 24, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Fisherman_Taylor_Divergent[] = {
    { .lvl = 20, .species = SPECIES_CHINCHOU },
    { .lvl = 20, .species = SPECIES_SHELLDER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Nurse_Leanne_Divergent[] = {
    { .lvl = 20, .species = SPECIES_BRAIXEN },
    { .lvl = 20, .species = SPECIES_CHANSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Dante_Divergent[] = {
    { .lvl = 28, .species = SPECIES_DEWOTT },
    { .lvl = 28, .species = SPECIES_MAWILE },
    { .lvl = 28, .species = SPECIES_FARFETCHD }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BugCatcher_Billie_Divergent[] = {
    { .lvl = 30, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 30, .species = SPECIES_VESPIQUEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gentleman_Lincoln_Divergent[] = {
    { .lvl = 28, .species = SPECIES_LYCANROC_N },
    { .lvl = 29, .species = SPECIES_HERDIER },
    { .lvl = 29, .species = SPECIES_QUILAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BlackBelt_Raphael_Divergent[] = {
    { .lvl = 30, .species = SPECIES_PIGNITE },
    { .lvl = 31, .species = SPECIES_GURDURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Lass_Anna_Divergent[] = {
    { .lvl = 29, .species = SPECIES_RIOLU },
    { .lvl = 29, .species = SPECIES_TOGETIC },
    { .lvl = 29, .species = SPECIES_COTTONEE },
    { .lvl = 30, .species = SPECIES_RIBOMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Swimmer_Danika_Divergent[] = {
    { .lvl = 48, .species = SPECIES_DRATINI },
    { .lvl = 48, .species = SPECIES_SEADRA },
    { .lvl = 50, .species = SPECIES_SHARPEDO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SrAndJr_SueAndKat_Divergent[] = {
    { .lvl = 29, .species = SPECIES_EEVEE },
    { .lvl = 30, .species = SPECIES_BRELOOM },
    { .lvl = 29, .species = SPECIES_MISDREAVUS },
    { .lvl = 30, .species = SPECIES_LOPUNNY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_HikerDarryl_Divergent[] = {
    { .lvl = 55, .species = SPECIES_BOLDORE },
    { .lvl = 55, .species = SPECIES_BARBARACLE },
    { .lvl = 56, .species = SPECIES_TYRANTRUM },
    { .lvl = 56, .species = SPECIES_CONKELDURR }
};
// #endregion

// #region Heleo City
const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_PsychicBianca_Divergent[] = {
    { .lvl = 1, .species = SPECIES_BULBASAUR },
    { .lvl = 1, .species = SPECIES_CHARMANDER },
    { .lvl = 1, .species = SPECIES_SQUIRTLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_SupernerdGalen_Divergent[] = {
    { .lvl = 1, .species = SPECIES_TIMBURR },
    { .lvl = 1, .species = SPECIES_HOOTHOOT },
    { .lvl = 1, .species = SPECIES_HOUNDOUR }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_CoolTrainerJet_Divergent[] = {
    { .lvl = 1, .species = SPECIES_DARUMAKA_G },
    { .lvl = 1, .species = SPECIES_RALTS },
    { .lvl = 1, .species = SPECIES_BLIPBUG }
};

const struct TrainerMonNoItemCustomMoves sParty_HeleoCityGym_SwimmerTessa_Divergent[] = {
    {
        .lvl = 25,
        .species = SPECIES_CASTFORM,
        .moves = {
            MOVE_RAINDANCE,
            MOVE_SUNNYDAY,
            MOVE_HAIL,
            MOVE_WEATHERBALL
        },
        .ability = Ability_1 // Forecast
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerByron_Divergent[] = {
    {
        .lvl = 23,
        .species = SPECIES_TORKOAL,
        .moves = { MOVE_SMOG, MOVE_FLAMEWHEEL, MOVE_WITHDRAW, MOVE_SMOKESCREEN },
        .heldItem = ITEM_HEAT_ROCK,
        .ability = Ability_2 // Drought
    },
    {
        .lvl = 23,
        .species = SPECIES_SUNFLORA,
        .moves = { MOVE_GROWTH, MOVE_SYNTHESIS, MOVE_RAZORLEAF, MOVE_GIGADRAIN },
        .ability = Ability_2 // Solar Power
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerDanette_Divergent[] = {
    {
        .lvl = 22,
        .species = SPECIES_AMAURA,
        .moves = { MOVE_ICYWIND, MOVE_ANCIENTPOWER, MOVE_AURORAVEIL, MOVE_ROUND },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 23,
        .species = SPECIES_BERGMITE,
        .moves = { MOVE_CURSE, MOVE_AVALANCHE, MOVE_POWDERSNOW, MOVE_HAIL },
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 23,
        .species = SPECIES_CUBCHOO,
        .moves = { MOVE_BRINE, MOVE_FROSTBREATH, MOVE_CHARM, MOVE_HAIL },
        .ability = Ability_2 // Slush Rush
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerMaisey_Divergent[] = {
    {
        .lvl = 23,
        .species = SPECIES_HIPPOPOTAS_F,
        .moves = { MOVE_CRUNCH, MOVE_SANDTOMB, MOVE_YAWN, MOVE_DIG },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 23,
        .species = SPECIES_HERDIER,
        .moves = { MOVE_FIREFANG, MOVE_THUNDERFANG, MOVE_RETALIATE, MOVE_WORKUP },
        .ability = Ability_2 // Sand Rush
    },
    {
        .lvl = 23,
        .species = SPECIES_CACNEA,
        .moves = { MOVE_NEEDLEARM, MOVE_FEINTATTACK, MOVE_INGRAIN, MOVE_SANDSTORM },
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
    { .lvl = 25, .species = SPECIES_EMOLGA },
    { .lvl = 25, .species = SPECIES_BIBAREL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyZeke_Divergent[] = {
    { .lvl = 23, .species = SPECIES_NINCADA },
    { .lvl = 24, .species = SPECIES_NINJASK },
    { .lvl = 25, .species = SPECIES_SHEDINJA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SuperNerdSaul_Divergent[] = {
    { .lvl = 24, .species = SPECIES_DRILBUR },
    { .lvl = 24, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 25, .species = SPECIES_CRABRAWLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_RockerParker_Divergent[] = {
    { .lvl = 25, .species = SPECIES_CASTFORM },
    { .lvl = 26, .species = SPECIES_KLINK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ParasolLadyAnnabelle_Divergent[] = {
    { .lvl = 28, .species = SPECIES_KIRLIA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ChannelerMorgan_Divergent[] = {
    { .lvl = 25, .species = SPECIES_DUSKULL },
    { .lvl = 25, .species = SPECIES_YAMASK },
    { .lvl = 26, .species = SPECIES_YAMASK_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_BugCatcherArnold_Divergent[] = {
    { .lvl = 24, .species = SPECIES_SNOM },
    { .lvl = 26, .species = SPECIES_LARVESTA },
    { .lvl = 26, .species = SPECIES_CHARJABUG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_LassLilian_Divergent[] = {
    { .lvl = 26, .species = SPECIES_COTTONEE },
    { .lvl = 27, .species = SPECIES_BAYLEEF }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyNatto_Divergent[] = {
    { .lvl = 24, .species = SPECIES_STUNFISK_G },
    { .lvl = 25, .species = SPECIES_SNEASEL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberMicah_Divergent[] = {
    { .lvl = 25, .species = SPECIES_PICHU },
    { .lvl = 25, .species = SPECIES_EEVEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberNancy_Divergent[] = {
    { .lvl = 25, .species = SPECIES_SANDYGAST },
    { .lvl = 25, .species = SPECIES_COMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerMaya_Divergent[] = {
    { .lvl = 26, .species = SPECIES_SHELLDER },
    { .lvl = 26, .species = SPECIES_HORSEA },
    { .lvl = 26, .species = SPECIES_HORSEA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerHuey_Divergent[] = {
    { .lvl = 47, .species = SPECIES_BINACLE },
    { .lvl = 48, .species = SPECIES_CORSOLA_G },
    { .lvl = 48, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerBob_Divergent[] = {
    { .lvl = 48, .species = SPECIES_LANTURN },
    { .lvl = 48, .species = SPECIES_SHELLDER },
    { .lvl = 51, .species = SPECIES_PELIPPER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_CoolTrainerHarriet_Divergent[] = {
    { .lvl = 50, .species = SPECIES_UMBREON },
    { .lvl = 52, .species = SPECIES_GASTRODON_EAST },
    { .lvl = 52, .species = SPECIES_CROBAT }
};
// #endregion

// #region Forgotten Manse
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_ChannelerMona_Divergent[] = {
    { .lvl = 25, .species = SPECIES_HATENNA },
    { .lvl = 25, .species = SPECIES_DUSKULL },
    { .lvl = 25, .species = SPECIES_MISDREAVUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BurglarChad_Divergent[] = {
    { .lvl = 27, .species = SPECIES_SNEASEL },
    { .lvl = 27, .species = SPECIES_BOLTUND }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_NurseLucy_Divergent[] = {
    { .lvl = 25, .species = SPECIES_TOGETIC },
    { .lvl = 25, .species = SPECIES_COMFEY },
    { .lvl = 26, .species = SPECIES_FLOETTE_YELLOW }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_BeautyLulu_Divergent[] = {
    { .lvl = 26, .species = SPECIES_KIRLIA },
    { .lvl = 27, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_ChannelerEsther_Divergent[] = {
    { .lvl = 26, .species = SPECIES_MISDREAVUS },
    { .lvl = 26, .species = SPECIES_SANDYGAST }
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
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 26, .species = SPECIES_TIMBURR },
    { .lvl = 26, .species = SPECIES_THIEVUL }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_PsychicCorbin_Divergent[] = {
    { .lvl = 27, .species = SPECIES_GALLADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_BurglarBarry_Divergent[] = {
    { .lvl = 27, .species = SPECIES_CROAGUNK },
    { .lvl = 28, .species = SPECIES_GRIMER_A },
    { .lvl = 29, .species = SPECIES_SCRAGGY }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_YoungsterChester_Divergent[] = {
    { .lvl = 27, .species = SPECIES_CORSOLA_G },
    { .lvl = 27, .species = SPECIES_CORSOLA_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_ChannelerElaine_Divergent[] = {
    { .lvl = 32, .species = SPECIES_SABLEYE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_SuperNerdGlenn_Divergent[] = {
    { .lvl = 27, .species = SPECIES_SLOWPOKE },
    { .lvl = 27, .species = SPECIES_SLOWPOKE_G }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_BurglarPavle_Divergent[] = {
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 31, .species = SPECIES_THIEVUL }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_PsychicNoelle_Divergent[] = {
    { .lvl = 27, .species = SPECIES_HATENNA },
    { .lvl = 28, .species = SPECIES_KIRLIA },
    { .lvl = 28, .species = SPECIES_BRAIXEN },
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_ChannelerSana_Divergent[] = {
    { .lvl = 30, .species = SPECIES_PHANTUMP },
    { .lvl = 30, .species = SPECIES_SANDYGAST }
};
// #endregion

// #region Daimyn Factory
const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BirdkeeperMarius_Divergent[] = {
    { .lvl = 33, .species = SPECIES_NOCTOWL }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_RockerBenson_Divergent[] = {
    { .lvl = 29, .species = SPECIES_KLINK },
    { .lvl = 31, .species = SPECIES_CHARJABUG }
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
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_CALMMIND, MOVE_DESTINYBOND },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerJamison_Divergent[] = {
    { .lvl = 29, .species = SPECIES_MAWILE },
    { .lvl = 28, .species = SPECIES_FLAAFFY },
    { .lvl = 30, .species = SPECIES_JOLTIK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_HikerPercy_Divergent[] = {
    { .lvl = 31, .species = SPECIES_CUFANT },
    { .lvl = 31, .species = SPECIES_DRILBUR },
    { .lvl = 31, .species = SPECIES_CARBINK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BlackbeltRory_Divergent[] = {
    { .lvl = 33, .species = SPECIES_MIENFOO },
    { .lvl = 34, .species = SPECIES_HAKAMO_O }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerWilson_Divergent[] = {
    { .lvl = 32, .species = SPECIES_PACHIRISU },
    { .lvl = 34, .species = SPECIES_HELIOPTILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_YoungsterNate_Divergent[] = {
    { .lvl = 32, .species = SPECIES_VIGOROTH },
    { .lvl = 34, .species = SPECIES_VIBRAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_PicknickerShanna_Divergent[] = {
    { .lvl = 32, .species = SPECIES_FRILLISH_F },
    { .lvl = 34, .species = SPECIES_GARDEVOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerKliff_Divergent[] = {
    { .lvl = 32, .species = SPECIES_EMOLGA },
    { .lvl = 34, .species = SPECIES_RAICHU },
    { .lvl = 34, .species = SPECIES_STUNFISK_G }
};
// #endregion

// #region Daimyn City
const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_YoungsterJacob_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_RATTATA_A,
        .moves = { MOVE_ENDEAVOR, MOVE_QUICKATTACK, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Thick Fat
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_PokefanKanesha_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_SHUCKLE,
        .moves = { MOVE_POWERTRICK, MOVE_ROCKTHROW, MOVE_STRUGGLEBUG, MOVE_NONE },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_BeautyEmilie_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_ZOROARK,
        .moves = { MOVE_TAUNT, MOVE_KNOCKOFF, MOVE_DETECT, MOVE_SUCKERPUNCH },
        .ability = Ability_1 // Illusion
    },
    {
        .lvl = 30,
        .species = SPECIES_CROAGUNK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_SWAGGER, MOVE_REVENGE, MOVE_VENOSHOCK },
        .ability = Ability_Hidden // Poison Touch
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_BeautyLeanne_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_TOGETIC,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 30,
        .species = SPECIES_CHANSEY,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 30,
        .species = SPECIES_HATTREM,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Anticipation
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_ChannelerRosita_Divergent[] = {
    {
        .lvl = 28,
        .species = SPECIES_DOTTLER,
        .moves = { MOVE_TRICKROOM, MOVE_STRUGGLEBUG, MOVE_CONFUSION, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 29,
        .species = SPECIES_CUFANT,
        .moves = { MOVE_IRONDEFENSE, MOVE_STOMP, MOVE_BULLDOZE, MOVE_ROCKSMASH },
        .ability = Ability_1 // Sheer Force
    },
    {
        .lvl = 28,
        .species = SPECIES_GURDURR,
        .moves = { MOVE_RETALIATE, MOVE_ROCKSLIDE, MOVE_LOWKICK, MOVE_BULKUP },
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 28,
        .species = SPECIES_CARBINK,
        .moves = { MOVE_TRICKROOM, MOVE_ANCIENTPOWER, MOVE_SMACKDOWN, MOVE_DAZZLINGGLEAM },
        .ability = Ability_1 // Clear body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_GamblerChuck_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_FLETCHINDER,
        .moves = { MOVE_ACROBATICS, MOVE_TAILWIND, MOVE_FLAMECHARGE, MOVE_UTURN },
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 30,
        .species = SPECIES_BOLTUND,
        .moves = { MOVE_ELECTROBALL, MOVE_ROAR, MOVE_BITE, MOVE_FLAMECHARGE },
        .ability = Ability_Hidden // Competitive
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
        .species = SPECIES_MISDREAVUS,
        .moves = { MOVE_PSYBEAM, MOVE_PERISHSONG, MOVE_MEANLOOK, MOVE_ASTONISH },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 30,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_SWAGGER, MOVE_FOULPLAY, MOVE_SANDATTACK, MOVE_ASSURANCE },
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 31,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_ENCORE, MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND },
        .ability = Ability_1 // Shadow Tag
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
    { .lvl = 30, .species = SPECIES_MR_MIME },
    { .lvl = 31, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Andrea_Divergent[] = {
    { .lvl = 31, .species = SPECIES_HERACROSS },
    { .lvl = 31, .species = SPECIES_TOUCANNON },
    { .lvl = 31, .species = SPECIES_TORRACAT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Fisherman_Yusuf_Divergent[] = {
    { .lvl = 30, .species = SPECIES_GYARADOS },
    { .lvl = 30, .species = SPECIES_GASTRODON },
};

const struct TrainerMonNoItemCustomMoves sParty_Route9_Gentleman_Gavin_Divergent[] = {
    {
        .lvl = 31,
        .species = SPECIES_RAICHU,
        .moves = { MOVE_HELPINGHAND, MOVE_THUNDERBOLT, MOVE_ELECTROBALL, MOVE_DRAININGKISS },
        .ability = Ability_Hidden // Lightningrod
    },
    {
        .lvl = 31,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_BULLETPUNCH, MOVE_FORCEPALM, MOVE_QUICKGUARD, MOVE_HELPINGHAND },
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_NinjaBoy_Ayrton_Divergent[] = {
    { .lvl = 29, .species = SPECIES_NINJASK },
    { .lvl = 29, .species = SPECIES_KROKOROK },
    { .lvl = 31, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Breeder_Talia_Divergent[] = {
    { .lvl = 28, .species = SPECIES_PIKACHU },
    { .lvl = 29, .species = SPECIES_TOGETIC },
    { .lvl = 30, .species = SPECIES_ESPEON },
    { .lvl = 30, .species = SPECIES_UMBREON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Picknicker_Zoe_Divergent[] = {
    { .lvl = 31, .species = SPECIES_VESPIQUEN },
    { .lvl = 32, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Kingsley_Divergent[] = {
    { .lvl = 33, .species = SPECIES_DECIDUEYE },
    { .lvl = 33, .species = SPECIES_VIBRAVA },
    { .lvl = 34, .species = SPECIES_SIRFETCHD },
};
// #endregion

// #region Route 10
const struct TrainerMonNoItemDefaultMoves sParty_Route10_PsychicDarius_Divergent[] = {
    { .lvl = 29, .species = SPECIES_KIRLIA },
    { .lvl = 30, .species = SPECIES_MR_MIME_G },
    { .lvl = 30, .species = SPECIES_WOBBUFFET },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_BirdKeeperMario_Divergent[] = {
    { .lvl = 30, .species = SPECIES_NOCTOWL },
    { .lvl = 30, .species = SPECIES_PELIPPER },
    { .lvl = 30, .species = SPECIES_SKARMORY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_GamblerDarren_Divergent[] = {
    { .lvl = 32, .species = SPECIES_LILEEP },
    { .lvl = 32, .species = SPECIES_GLACEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_ParasolLadyGwen_Divergent[] = {
    { .lvl = 34, .species = SPECIES_FLORGES_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_CamperJackson_Divergent[] = {
    { .lvl = 32, .species = SPECIES_NIDORINO },
    { .lvl = 34, .species = SPECIES_CHESNAUGHT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_RockerBert_Divergent[] = {
    { .lvl = 31, .species = SPECIES_THWACKEY },
    { .lvl = 31, .species = SPECIES_NOIBAT },
    { .lvl = 33, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerAlberto_Divergent[] = {
    { .lvl = 47, .species = SPECIES_CORSOLA_G },
    { .lvl = 47, .species = SPECIES_CORPHISH },
    { .lvl = 48, .species = SPECIES_CURSOLA },
    { .lvl = 48, .species = SPECIES_CRAWDAUNT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerRosie_Divergent[] = {
    { .lvl = 52, .species = SPECIES_JELLICENT_F },
    { .lvl = 53, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerDoug_Divergent[] = {
    { .lvl = 49, .species = SPECIES_CARVANHA },
    { .lvl = 50, .species = SPECIES_SLOWBRO },
    { .lvl = 50, .species = SPECIES_BLASTOISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_HikerHarley_Divergent[] = {
    { .lvl = 30, .species = SPECIES_BOLDORE },
    { .lvl = 30, .species = SPECIES_CARKOL },
    { .lvl = 32, .species = SPECIES_GIGALITH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_BlackbeltXavier_Divergent[] = {
    { .lvl = 31, .species = SPECIES_MONFERNO },
    { .lvl = 32, .species = SPECIES_GURDURR },
};

// #endregion

// #region Route 11 South
const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Ross_Divergent[] = {
    { .lvl = 33, .species = SPECIES_KOFFING_G },
    { .lvl = 34, .species = SPECIES_KROKOROK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Greta_Divergent[] = {
    { .lvl = 32, .species = SPECIES_SNEASEL },
    { .lvl = 33, .species = SPECIES_ZUBAT },
    { .lvl = 33, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Nellie_Divergent[] = {
    { .lvl = 31, .species = SPECIES_ZUBAT },
    { .lvl = 31, .species = SPECIES_SANDILE },
    { .lvl = 32, .species = SPECIES_KOFFING_G },
    { .lvl = 33, .species = SPECIES_SNEASEL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Helga_Divergent[] = {
    { .lvl = 34, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 35, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Kareem_Divergent[] = {
    { .lvl = 33, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 33, .species = SPECIES_CROAGUNK },
    { .lvl = 35, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Chung_Divergent[] = {
    { .lvl = 35, .species = SPECIES_SCRAGGY },
    { .lvl = 35, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Lass_Tabitha_Divergent[] = {
    { .lvl = 33, .species = SPECIES_AMAURA },
    { .lvl = 34, .species = SPECIES_STOUTLAND },
    { .lvl = 34, .species = SPECIES_VESPIQUEN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_CrushGirl_Alisa_Divergent[] = {
    { .lvl = 36, .species = SPECIES_SIRFETCHD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Engineer_Dale_Divergent[] = {
    { .lvl = 35, .species = SPECIES_PINCURCHIN },
    { .lvl = 35, .species = SPECIES_EMOLGA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Collector_Orville_Divergent[] = {
    { .lvl = 34, .species = SPECIES_LILEEP },
    { .lvl = 34, .species = SPECIES_SLIGGOO },
    { .lvl = 35, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoClancy_Divergent[] = {
    { .lvl = 35, .species = SPECIES_THIEVUL },
    { .lvl = 35, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoEna_Divergent[] = {
    { .lvl = 36, .species = SPECIES_GOLBAT },
    { .lvl = 36, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald_Divergent[] = {
    {
        .lvl = 35,
        .species = SPECIES_KROKOROK,
        .moves = { MOVE_CRUNCH, MOVE_DIG, MOVE_AQUATAIL, MOVE_TAUNT },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 35,
        .species = SPECIES_SNEASEL,
        .moves = { MOVE_ICESHARD, MOVE_METALCLAW, MOVE_FAKEOUT, MOVE_ICEPUNCH },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 36,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_IRONHEAD, MOVE_CURSE, MOVE_LEECHSEED, MOVE_POWERWHIP },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 37,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_POWERUPPUNCH, MOVE_SWAGGER, MOVE_SNARL, MOVE_PROTECT },
        .ability = Ability_1 // Shed Skin
    }
};
// #endregion

// #region Hesson Pass
const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_HikerLuke_Divergent[] = {
    { .lvl = 37, .species = SPECIES_GIGALITH }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_ScientistHarvey_Divergent[] = {
    { .lvl = 34, .species = SPECIES_BERGMITE },
    { .lvl = 34, .species = SPECIES_LILEEP },
    { .lvl = 35, .species = SPECIES_CACTURNE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_PsychicKimiko_Divergent[] = {
    { .lvl = 57, .species = SPECIES_HATTREM },
    { .lvl = 57, .species = SPECIES_MORPEKO },
    { .lvl = 59, .species = SPECIES_MANDIBUZZ }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CoolTrainerColt_Divergent[] = {
    { .lvl = 58, .species = SPECIES_GLALIE },
    { .lvl = 58, .species = SPECIES_TOUCANNON },
    { .lvl = 60, .species = SPECIES_MAMOSWINE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_BlackbeltHaytham_Divergent[] = {
    { .lvl = 35, .species = SPECIES_CRABRAWLER },
    { .lvl = 36, .species = SPECIES_BLAZIKEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CollectorZeus_Divergent[] = {
    { .lvl = 57, .species = SPECIES_COFAGRIGUS },
    { .lvl = 57, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_NurseMina_Divergent[] = {
    { .lvl = 55, .species = SPECIES_HAPPINY },
    { .lvl = 57, .species = SPECIES_CHANSEY },
    { .lvl = 59, .species = SPECIES_BLISSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_GentlemanGordy_Divergent[] = {
    { .lvl = 57, .species = SPECIES_BOLTUND },
    { .lvl = 58, .species = SPECIES_STOUTLAND }
};
// #endregion

// #region Route 11 North
const struct TrainerMonNoItemDefaultMoves sParty_Route11North_PainterIsobel_Divergent[] = {
    { .lvl = 35, .species = SPECIES_IVYSAUR },
    { .lvl = 36, .species = SPECIES_GLACEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanClint_Divergent[] = {
    { .lvl = 35, .species = SPECIES_HORSEA },
    { .lvl = 35, .species = SPECIES_WARTORTLE },
    { .lvl = 36, .species = SPECIES_GASTRODON_EAST }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ChanellerKatya_Divergent[] = {
    { .lvl = 36, .species = SPECIES_SABLEYE },
    { .lvl = 38, .species = SPECIES_DUSKNOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_RockerNathaniel_Divergent[] = {
    { .lvl = 36, .species = SPECIES_VIBRAVA },
    { .lvl = 36, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_NinjaBoyYao_Divergent[] = {
    { .lvl = 34, .species = SPECIES_CARVANHA },
    { .lvl = 34, .species = SPECIES_EMOLGA },
    { .lvl = 36, .species = SPECIES_MALAMAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ParaoslLadyTina_Divergent[] = {
    { .lvl = 34, .species = SPECIES_FLOETTE_ORANGE },
    { .lvl = 35, .species = SPECIES_BRAIXEN },
    { .lvl = 35, .species = SPECIES_RIBOMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanJonah_Divergent[] = {
    { .lvl = 36, .species = SPECIES_MAGIKARP },
    { .lvl = 38, .species = SPECIES_GYARADOS }
};

// #endregion

// #region Laplaz Town
const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_BirdKeeperToby_Divergent[] = {
    { .lvl = 1, .species = SPECIES_CORVISQUIRE },
    { .lvl = 1, .species = SPECIES_NOCTOWL },
    { .lvl = 1, .species = SPECIES_FLETCHINDER }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CollectorDirk_Divergent[] = {
    { .lvl = 1, .species = SPECIES_MISDREAVUS },
    { .lvl = 1, .species = SPECIES_DUSKULL },
    { .lvl = 1, .species = SPECIES_VIBRAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CoolTrainerVanessa_Divergent[] = {
    { .lvl = 1, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 1, .species = SPECIES_SKARMORY },
    { .lvl = 1, .species = SPECIES_ROTOM }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_PsychicJeremiah_Divergent[] = {
    {
        .lvl = 38,
        .species = SPECIES_FALINKS,
        .moves = { MOVE_BULKUP, MOVE_ROCKSMASH, MOVE_NORETREAT, MOVE_HEADBUTT },
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 38,
        .species = SPECIES_EMOLGA,
        .moves = { MOVE_ELECTROBALL, MOVE_AGILITY, MOVE_CHARGE, MOVE_ACROBATICS },
        .ability = Ability_1 // Static
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
        .species = SPECIES_SABLEYE,
        .moves = { MOVE_SWAGGER, MOVE_FOULPLAY, MOVE_KNOCKOFF, MOVE_SHADOWSNEAK },
        .ability = Ability_Hidden // Prankster
    },
    {
        .lvl = 37,
        .species = SPECIES_ORBEETLE,
        .moves = { MOVE_STICKYWEB, MOVE_CALMMIND, MOVE_PSYBEAM, MOVE_STRUGGLEBUG },
        .ability = Ability_2 // Frisk
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ChannelerVirginia_Divergent[] = {
    {
        .lvl = 37,
        .species = SPECIES_JANGMO_O,
        .moves = { MOVE_SCREECH, MOVE_DRAGONDANCE, MOVE_HEADBUTT, MOVE_SCALESHOT },
        .ability = Ability_1 // Bulletproof
    },
    {
        .lvl = 37,
        .species = SPECIES_CENTISKORCH,
        .moves = { MOVE_COIL, MOVE_BUGBITE, MOVE_SMOKESCREEN, MOVE_FIRELASH },
        .ability = Ability_2 // White Smoke
    },
    {
        .lvl = 38,
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_IRONDEFENSE, MOVE_ANCIENTPOWER, MOVE_METALSOUND, MOVE_HEADBUTT },
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_LadyNisha_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_DEFENSECURL, MOVE_ROLLOUT, MOVE_SCREECH, MOVE_POISONTAIL },
        .ability = Ability_Hidden // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ScientistKent_Divergent[] = {
    {
        .lvl = 37,
        .species = SPECIES_SNORUNT,
        .moves = { MOVE_ICYWIND, MOVE_PROTECT, MOVE_ASTONISH, MOVE_LEER },
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 37,
        .species = SPECIES_BINACLE,
        .moves = { MOVE_SHELLSMASH, MOVE_ANCIENTPOWER, MOVE_SLASH, MOVE_WATERGUN },
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 37,
        .species = SPECIES_SALANDIT,
        .moves = { MOVE_NASTYPLOT, MOVE_EMBER, MOVE_OVERHEAT, MOVE_POISONFANG },
        .ability = Ability_Hidden // Oblivious
    },
    {
        .lvl = 38,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_MINIMIZE, MOVE_ACIDARMOR, MOVE_TOXIC, MOVE_MUDSHOT },
        .ability = Ability_1 // Poison Touch
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_RockerTrent_Divergent[] = {
    {
        .lvl = 38,
        .species = SPECIES_BIBAREL,
        .moves = { MOVE_AMNESIA, MOVE_CURSE, MOVE_SUPERFANG, MOVE_WATERPULSE },
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 38,
        .species = SPECIES_WHIMSICOTT,
        .moves = { MOVE_COTTONGUARD, MOVE_TAILWIND, MOVE_SUBSTITUTE, MOVE_GIGADRAIN },
        .ability = Ability_1 // Prankster
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
    { .lvl = 38, .species = SPECIES_MIMIKYU },
    { .lvl = 38, .species = SPECIES_SLIGGOO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CollectorFernando_Divergent[] = {
    { .lvl = 39, .species = SPECIES_DHELMISE },
    { .lvl = 39, .species = SPECIES_RAICHU_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BugCatcherLyle_Divergent[] = {
   { .lvl = 37, .species = SPECIES_JOLTIK },
   { .lvl = 38, .species = SPECIES_SHIINOTIC },
   { .lvl = 38, .species = SPECIES_VIBRAVA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BeautyErica_Divergent[] = {
    { .lvl = 40, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_PainterSheena_Divergent[] = {
    { .lvl = 38, .species = SPECIES_ESPEON },
    { .lvl = 38, .species = SPECIES_MORPEKO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CamperRupert_Divergent[] = {
    { .lvl = 40, .species = SPECIES_VENUSAUR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ScientistSean_Divergent[] = {
    { .lvl = 39, .species = SPECIES_BEARTIC },
    { .lvl = 39, .species = SPECIES_BARBARACLE },
    { .lvl = 39, .species = SPECIES_KROKOROK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RockerRaphael_Divergent[] = {
    { .lvl = 40, .species = SPECIES_VIBRAVA },
    { .lvl = 40, .species = SPECIES_RILLABOOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ChannelerRenee_Divergent[] = {
    { .lvl = 37, .species = SPECIES_DUSKULL },
    { .lvl = 37, .species = SPECIES_SABLEYE },
    { .lvl = 38, .species = SPECIES_PHANTUMP },
    { .lvl = 38, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BlackbeltBrad_Divergent[] = {
    { .lvl = 39, .species = SPECIES_TIMBURR },
    { .lvl = 40, .species = SPECIES_HERACROSS },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RuinManiacAlex_Divergent[] = {
    { .lvl = 39, .species = SPECIES_VULLABY },
    { .lvl = 40, .species = SPECIES_RUNERIGUS },
    { .lvl = 41, .species = SPECIES_EXCADRILL },
};
// #endregion

// #region Route 12 & Scalding Spa
const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteJoanne_Divergent[] = {
    { .lvl = 39, .species = SPECIES_PACHIRISU },
    { .lvl = 40, .species = SPECIES_HAKAMO_O },
    { .lvl = 40, .species = SPECIES_MAGCARGO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_PsychicTony_Divergent[] = {
    { .lvl = 40, .species = SPECIES_MR_MIME_G },
    { .lvl = 42, .species = SPECIES_MR_RIME },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_HikerDwight_Divergent[] = {
    { .lvl = 39, .species = SPECIES_ROGGENROLA },
    { .lvl = 39, .species = SPECIES_DRILBUR },
    { .lvl = 41, .species = SPECIES_CARBINK },
    { .lvl = 42, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteTrixie_Divergent[] = {
    { .lvl = 41, .species = SPECIES_INCINEROAR },
    { .lvl = 41, .species = SPECIES_KANGASKHAN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_GentlemanGeoffrey_Divergent[] = {
    { .lvl = 41, .species = SPECIES_STOUTLAND },
    { .lvl = 41, .species = SPECIES_BOLTUND },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_HikerEugene_Divergent[] = {
    { .lvl = 43, .species = SPECIES_TORKOAL },
    { .lvl = 43, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_SupernerdStephen_Divergent[] = {
    { .lvl = 42, .species = SPECIES_HAKAMO_O },
    { .lvl = 44, .species = SPECIES_CURSOLA },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_JugglerJohan_Divergent[] = {
    { .lvl = 41, .species = SPECIES_ROLYCOLY },
    { .lvl = 41, .species = SPECIES_SALAZZLE },
    { .lvl = 42, .species = SPECIES_TURTONATOR },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_BlackbeltKieran_Divergent[] = {
    { .lvl = 44, .species = SPECIES_EMBOAR },
};

const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena_Divergent[] = {
    {
        .lvl = 42,
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_POISONJAB, MOVE_VENOSHOCK, MOVE_PROTECT, MOVE_DRAINPUNCH },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Dry Skin
    },
    {
        .lvl = 42,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_SURF, MOVE_STOCKPILE, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 42,
        .species = SPECIES_SLIGGOO,
        .moves = { MOVE_ROCKSLIDE, MOVE_DRAGONBREATH, MOVE_THUNDERBOLT, MOVE_MUDDYWATER },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_BugCatcherBrenan_Divergent[] = {
    { .lvl = 42, .species = SPECIES_SNOM },
    { .lvl = 43, .species = SPECIES_FROSMOTH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierChantal_Divergent[] = {
    { .lvl = 41, .species = SPECIES_BERGMITE },
    { .lvl = 42, .species = SPECIES_SWINUB },
    { .lvl = 42, .species = SPECIES_BERGMITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_HikerKumar_Divergent[] = {
    { .lvl = 45, .species = SPECIES_STONJOURNER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierAubrey_Divergent[] = {
    { .lvl = 43, .species = SPECIES_SNEASEL },
    { .lvl = 43, .species = SPECIES_GLACEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierLenora_Divergent[] = {
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 43, .species = SPECIES_DELIBIRD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierMegan_Divergent[] = {
    { .lvl = 43, .species = SPECIES_SNORUNT },
    { .lvl = 44, .species = SPECIES_PILOSWINE },
    { .lvl = 45, .species = SPECIES_FROSLASS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SwimmerMGreg_Divergent[] = {
    { .lvl = 49, .species = SPECIES_FRILLISH },
    { .lvl = 49, .species = SPECIES_BINACLE },
    { .lvl = 51, .species = SPECIES_JELLICENT },
};

// #endregion

// #region Bruccie Village & Calicin Bay
const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_LassMel_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_MIENSHAO,
        .moves = { MOVE_UTURN, MOVE_FAKEOUT, MOVE_FORCEPALM, MOVE_NONE },
        .ability = Ability_2 // Regenerator
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
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_WATERFALL, MOVE_CRUNCH, MOVE_RAINDANCE, MOVE_DRAGONDANCE },
        .ability = Ability_Hidden // Moxie
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_EngineerTommy_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_SHEDINJA,
        .moves = { MOVE_SHADOWCLAW, MOVE_MUDSLAP, MOVE_CONFUSERAY, MOVE_BUGBUZZ },
        .ability = Ability_1 // Wonder Guard
    },
    {
        .lvl = 43,
        .species = SPECIES_BIBAREL,
        .moves = { MOVE_YAWN, MOVE_HYPERFANG, MOVE_CRUNCH, MOVE_AQUAJET },
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_HikerJoel_Divergent[] = {
    {
        .lvl = 43,
        .species = SPECIES_MORPEKO,
        .moves = { MOVE_SPARK, MOVE_BITE, MOVE_BULLETSEED, MOVE_TORMENT },
        .ability = Ability_1 // Hunger Switch
    },
    {
        .lvl = 43,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_SANDSTORM, MOVE_ROCKSLIDE, MOVE_DIG, MOVE_METALCLAW },
        .ability = Ability_2 // Sand Force
    },
    {
        .lvl = 44,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_COUNTER, MOVE_EARTHQUAKE, MOVE_HEAVYSLAM, MOVE_IRONDEFENSE },
        .ability = Ability_2 // Stamina
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_CrushGirlEllie_Divergent[] = {
    {
        .lvl = 44, 
        .species = SPECIES_MIMIKYU,
        .moves = { MOVE_COPYCAT, MOVE_SUBSTITUTE, MOVE_DRAININGKISS, MOVE_GIGADRAIN },
        .ability = Ability_1 // Disguise
    },
    {
        .lvl = 44,
        .species = SPECIES_TOUCANNON,
        .moves = { MOVE_ROCKBLAST, MOVE_FURYATTACK, MOVE_BULLETSEED, MOVE_BEAKBLAST },
        .ability = Ability_2 // Skill Link
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
    { .lvl = 42, .species = SPECIES_BERGMITE },
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 43, .species = SPECIES_CRABOMINABLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFFran_Divergent[] = {
    { .lvl = 50, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMAngelo_Divergent[] = {
    { .lvl = 47, .species = SPECIES_SHELLDER },
    { .lvl = 47, .species = SPECIES_BARBARACLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMSebastian_Divergent[] = {
    { .lvl = 47, .species = SPECIES_SEADRA },
    { .lvl = 47, .species = SPECIES_GASTRODON_EAST }
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFCorrine_Divergent[] = {
    { .lvl = 49, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_FishermanOliver_Divergent[] = {
    { .lvl = 42, .species = SPECIES_MAGIKARP },
    { .lvl = 42, .species = SPECIES_MAGIKARP },
    { .lvl = 44, .species = SPECIES_DRIZZILE },
    { .lvl = 44, .species = SPECIES_GYARADOS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoHugo_Divergent[] = {
    { .lvl = 45, .species = SPECIES_THIEVUL },
    { .lvl = 46, .species = SPECIES_MANDIBUZZ },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoAnise_Divergent[] = {
    { .lvl = 44, .species = SPECIES_GOLBAT },
    { .lvl = 45, .species = SPECIES_HAKAMO_O },
    { .lvl = 45, .species = SPECIES_SCRAFTY },
};

const struct TrainerMonItemCustomMoves sParty_CalicinBay_TeamPlutoYolena_Divergent[] = {
    {
        .lvl = 46,
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_POISONJAB, MOVE_VENOSHOCK, MOVE_PROTECT, MOVE_DRAINPUNCH },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Dry Skin
    },
    {
        .lvl = 46,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_SURF, MOVE_STOCKPILE, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 47,
        .species = SPECIES_SLIGGOO,
        .moves = { MOVE_ROCKSLIDE, MOVE_DRAGONPULSE, MOVE_THUNDER, MOVE_MUDDYWATER },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoClancy_Divergent[] = {
    { .lvl = 45, .species = SPECIES_THIEVUL },
    { .lvl = 46, .species = SPECIES_TOXICROAK },
    { .lvl = 47, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoEna_Divergent[] = {
    { .lvl = 45, .species = SPECIES_DUSKNOIR },
    { .lvl = 46, .species = SPECIES_SCOLIPEDE },
    { .lvl = 47, .species = SPECIES_CROBAT },
};
// #endregion

// #region Pluto HQ
const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoHeathcliff_Divergent[] = {
    { .lvl = 45, .species = SPECIES_NOIBAT },
    { .lvl = 45, .species = SPECIES_KLANG },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B1F_ScientistSeamus_Divergent[] = {
    { .lvl = 44, .species = SPECIES_ROTOM_FAN },
    { .lvl = 44, .species = SPECIES_HIPPOWDON_F },
    { .lvl = 45, .species = SPECIES_SLOWBRO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoColton_Divergent[] = {
    { .lvl = 46, .species = SPECIES_TURTONATOR },
    { .lvl = 46, .species = SPECIES_THIEVUL },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B2F_ScientistWayne_Divergent[] = {
    { .lvl = 45, .species = SPECIES_GRIMER_A },
    { .lvl = 44, .species = SPECIES_GRIMER_A },
    { .lvl = 44, .species = SPECIES_RATICATE_A },
    { .lvl = 45, .species = SPECIES_PILOSWINE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoDenise_Divergent[] = {
    { .lvl = 45, .species = SPECIES_SALANDIT },
    { .lvl = 46, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoTheodore_Divergent[] = {
    { .lvl = 47, .species = SPECIES_NOIVERN },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B3F_TeamPlutoYeon_Divergent[] = {
    { .lvl = 47, .species = SPECIES_KLINKLANG },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMatty_Divergent[] = {
    { .lvl = 46, .species = SPECIES_MORPEKO },
    { .lvl = 46, .species = SPECIES_TOXAPEX },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B4F_ScientistGary_Divergent[] = {
    { .lvl = 45, .species = SPECIES_PINCURCHIN },
    { .lvl = 46, .species = SPECIES_PAWNIARD },
    { .lvl = 45, .species = SPECIES_STUNFISK_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMay_Divergent[] = {
    { .lvl = 44, .species = SPECIES_KOFFING_G },
    { .lvl = 44, .species = SPECIES_DRILBUR },
    { .lvl = 44, .species = SPECIES_SNEASEL },
    { .lvl = 44, .species = SPECIES_CACTURNE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoClay_Divergent[] = {
    { .lvl = 46, .species = SPECIES_ZOROARK },
    { .lvl = 47, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoVictor_Divergent[] = {
    { .lvl = 44, .species = SPECIES_KOFFING_G },
    { .lvl = 46, .species = SPECIES_ZUBAT },
    { .lvl = 46, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoPaula_Divergent[] = {
    { .lvl = 46, .species = SPECIES_KROKOROK },
    { .lvl = 46, .species = SPECIES_THIEVUL },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoGiana_Divergent[] = {
    { .lvl = 44, .species = SPECIES_VENIPEDE },
    { .lvl = 45, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 46, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B6F_ScientistOrson_Divergent[] = {
    { .lvl = 47, .species = SPECIES_ROTOM_WASH },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoQuinn_Divergent[] = {
    { .lvl = 44, .species = SPECIES_SNEASEL },
    { .lvl = 44, .species = SPECIES_SALANDIT },
    { .lvl = 44, .species = SPECIES_SANDILE },
    { .lvl = 45, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoLayla_Divergent[] = {
    { .lvl = 47, .species = SPECIES_INCINEROAR },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B7F_ScientistNico_Divergent[] = {
    { .lvl = 45, .species = SPECIES_GRIMER_A },
    { .lvl = 45, .species = SPECIES_EMOLGA },
    { .lvl = 46, .species = SPECIES_TOXTRICITY },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoMitch_Divergent[] = {
    { .lvl = 46, .species = SPECIES_INKAY },
    { .lvl = 46, .species = SPECIES_MR_RIME },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoRichard_Divergent[] = {
    { .lvl = 46, .species = SPECIES_LUCARIO },
    { .lvl = 47, .species = SPECIES_MALAMAR },
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_NOCTOWL,
        .moves = { MOVE_ROOST, MOVE_MOONBLAST, MOVE_AIRSLASH, MOVE_NIGHTSHADE },
        .ability = Ability_Hidden // Tinted Lens
    },
    {
        .lvl = 48,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_KNOCKOFF, MOVE_ACIDARMOR, MOVE_POISONJAB, MOVE_ICEPUNCH },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 48,
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_MYSTICALFIRE, MOVE_SHADOWBALL, MOVE_PSYSHOCK, MOVE_DESTINYBOND },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 49,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_FLAMETHROWER, MOVE_TOXIC, MOVE_VENOSHOCK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Corrosion
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERFANG, MOVE_STEALTHROCK },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 48,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_CURSE, MOVE_GYROBALL, MOVE_POWERWHIP },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 48,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FAKEOUT, MOVE_ICICLECRASH, MOVE_THROATCHOP, MOVE_AERIALACE },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 49,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_DRAGONDANCE, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_POISONJAB },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Shed Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Divergent[] = {
    {
        .lvl = 49,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_CLEARSMOG, MOVE_SPORE, MOVE_SYNTHESIS, MOVE_SLUDGEBOMB },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 49,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_BELLYDRUM, MOVE_DRAGONCLAW, MOVE_POISONJAB, MOVE_CLOSECOMBAT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 49,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWPUNCH, MOVE_BRICKBREAK, MOVE_LEECHLIFE },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 49,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_ROCKSLIDE, MOVE_IRONHEAD},
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 50,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_ICEFANG, MOVE_CRUNCH },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion

// #region Route 18
const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJasper_Divergent[] = {
    { .lvl = 46, .species = SPECIES_MARSHTOMP },
    { .lvl = 46, .species = SPECIES_LANTURN },
    { .lvl = 47, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_TriathleteDeborah_Divergent[] = {
    { .lvl = 47, .species = SPECIES_CINDERACE },
    { .lvl = 47, .species = SPECIES_PASSIMIAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJudie_Divergent[] = {
    { .lvl = 49, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BirdKeeperKirk_Divergent[] = {
    { .lvl = 47, .species = SPECIES_DECIDUEYE },
    { .lvl = 48, .species = SPECIES_TALONFLAME }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_LassEmma_Divergent[] = {
    { .lvl = 46, .species = SPECIES_CUTIEFLY },
    { .lvl = 47, .species = SPECIES_FLOETTE_BLUE },
    { .lvl = 47, .species = SPECIES_SYLVEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BlackbeltRohan_Divergent[] = {
    { .lvl = 49, .species = SPECIES_CONKELDURR }
};
// #endregion

// #region Route 16
const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerGale_Divergent[] = {
    { .lvl = 51, .species = SPECIES_CARVANHA },
    { .lvl = 51, .species = SPECIES_CARVANHA },
    { .lvl = 52, .species = SPECIES_SHARPEDO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerAmy_Divergent[] = {
    { .lvl = 54, .species = SPECIES_LAPRAS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_BirdKeeperTrevor_Divergent[] = {
    { .lvl = 48, .species = SPECIES_HOOTHOOT },
    { .lvl = 48, .species = SPECIES_NOCTOWL },
    { .lvl = 49, .species = SPECIES_CORVISQUIRE },
    { .lvl = 49, .species = SPECIES_SKARMORY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_LadyMaria_Divergent[] = {
    { .lvl = 55, .species = SPECIES_ROSERADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerChristina_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CROCONAW },
    { .lvl = 53, .species = SPECIES_PELIPPER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerPhillip_Divergent[] = {
    { .lvl = 50, .species = SPECIES_SEADRA },
    { .lvl = 51, .species = SPECIES_SHELLDER },
    { .lvl = 52, .species = SPECIES_CLOYSTER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerLester_Divergent[] = {
    { .lvl = 54, .species = SPECIES_JELLICENT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerWendy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_MAREANIE },
    { .lvl = 52, .species = SPECIES_CURSOLA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberCody_Divergent[] = {
    { .lvl = 51, .species = SPECIES_LYCANROC },
    { .lvl = 52, .species = SPECIES_CHESNAUGHT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberLeslie_Divergent[] = {
    { .lvl = 51, .species = SPECIES_KIRLIA },
    { .lvl = 52, .species = SPECIES_VESPIQUEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerClementine_Divergent[] = {
    { .lvl = 52, .species = SPECIES_GASTRODON_EAST },
    { .lvl = 52, .species = SPECIES_GASTRODON }
};
// #endregion

// #region Route 14
const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerIvan_Divergent[] = {
    { .lvl = 48, .species = SPECIES_MAGIKARP },
    { .lvl = 48, .species = SPECIES_MARSHTOMP },
    { .lvl = 48, .species = SPECIES_GYARADOS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_HikerClifford_Divergent[] = {
    { .lvl = 47, .species = SPECIES_ROGGENROLA },
    { .lvl = 48, .species = SPECIES_CARBINK },
    { .lvl = 49, .species = SPECIES_MUDSDALE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanEsteban_Divergent[] = {
    { .lvl = 48, .species = SPECIES_DRATINI },
    { .lvl = 49, .species = SPECIES_DRAGONAIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanTucker_Divergent[] = {
    { .lvl = 50, .species = SPECIES_TOXAPEX }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerEleanor_Divergent[] = {
    { .lvl = 46, .species = SPECIES_HORSEA },
    { .lvl = 46, .species = SPECIES_HORSEA },
    { .lvl = 46, .species = SPECIES_CHINCHOU },
    { .lvl = 47, .species = SPECIES_SEADRA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_BlackbeltJoaquin_Divergent[] = {
    { .lvl = 47, .species = SPECIES_PASSIMIAN },
    { .lvl = 48, .species = SPECIES_CRABRAWLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerChris_Divergent[] = {
    { .lvl = 47, .species = SPECIES_BINACLE },
    { .lvl = 47, .species = SPECIES_LANTURN },
    { .lvl = 48, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_YoungsterFreddie_Divergent[] = {
    { .lvl = 46, .species = SPECIES_RATTATA_A },
    { .lvl = 46, .species = SPECIES_RATICATE_A },
    { .lvl = 46, .species = SPECIES_BOLTUND },
    { .lvl = 47, .species = SPECIES_TRUMBEAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_PsychicTobin_Divergent[] = {
    { .lvl = 48, .species = SPECIES_ELGYEM },
    { .lvl = 48, .species = SPECIES_ORANGURU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerMacie_Divergent[] = {
    { .lvl = 46, .species = SPECIES_SHELLDER },
    { .lvl = 47, .species = SPECIES_OSHAWOTT },
    { .lvl = 47, .species = SPECIES_DEWOTT }
};

// #endregion

// #region Route 15 North and South
const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerMiles_Divergent[] = {
    { .lvl = 50, .species = SPECIES_SHELLDER },
    { .lvl = 49, .species = SPECIES_SHELLDER },
    { .lvl = 50, .species = SPECIES_CLOYSTER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerFiona_Divergent[] = {
    { .lvl = 52, .species = SPECIES_LAPRAS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_HikerKlaus_Divergent[] = {
    { .lvl = 50, .species = SPECIES_STONJOURNER },
    { .lvl = 50, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerUrsula_Divergent[] = {
    { .lvl = 50, .species = SPECIES_CARVANHA },
    { .lvl = 51, .species = SPECIES_SHARPEDO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerQuincy_Divergent[] = {
    { .lvl = 51, .species = SPECIES_PRINPLUP },
    { .lvl = 52, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_CoolTrainerWesley_Divergent[] = {
    { .lvl = 52, .species = SPECIES_ROTOM_HEAT },
    { .lvl = 52, .species = SPECIES_GARCHOMP },
    { .lvl = 53, .species = SPECIES_TOGEKISS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SuperNerdEthan_Divergent[] = {
    { .lvl = 52, .species = SPECIES_GOODRA },
    { .lvl = 52, .species = SPECIES_RAICHU_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_ChannelerLila_Divergent[] = {
    { .lvl = 49, .species = SPECIES_MISDREAVUS },
    { .lvl = 49, .species = SPECIES_MISDREAVUS },
    { .lvl = 50, .species = SPECIES_SABLEYE },
    { .lvl = 50, .species = SPECIES_CURSOLA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerGerald_Divergent[] = {
    { .lvl = 51, .species = SPECIES_FERALIGATR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerAlexandra_Divergent[] = {
    { .lvl = 49, .species = SPECIES_CHINCHOU },
    { .lvl = 49, .species = SPECIES_WINGULL },
    { .lvl = 50, .species = SPECIES_LANTURN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerBernard_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CRABOMINABLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerHarold_Divergent[] = {
    { .lvl = 49, .species = SPECIES_CORPHISH },
    { .lvl = 51, .species = SPECIES_CRAWDAUNT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerMelinda_Divergent[] = {
    { .lvl = 48, .species = SPECIES_SQUIRTLE },
    { .lvl = 48, .species = SPECIES_HORSEA },
    { .lvl = 48, .species = SPECIES_BINACLE },
    { .lvl = 50, .species = SPECIES_SWAMPERT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_BlackbeltFranklin_Divergent[] = {
    { .lvl = 50, .species = SPECIES_FALINKS },
    { .lvl = 51, .species = SPECIES_SCRAFTY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerPatricia_Divergent[] = {
    { .lvl = 50, .species = SPECIES_DRATINI },
    { .lvl = 52, .species = SPECIES_DRAGONAIR },
};
// #endregion

// #region Seppire Cove
const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerValerie_Divergent[] = {
    { .lvl = 52, .species = SPECIES_LAPRAS },
    { .lvl = 52, .species = SPECIES_PINCURCHIN },
    { .lvl = 53, .species = SPECIES_CLOYSTER },
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerIchabod_Divergent[] = {
    { .lvl = 54, .species = SPECIES_DHELMISE }
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_RuinManiacCarter_Divergent[] = {
    { .lvl = 53, .species = SPECIES_COFAGRIGUS },
    { .lvl = 53, .species = SPECIES_STONJOURNER },
};
// #endregion

// #region Route 19
const struct TrainerMonNoItemDefaultMoves sParty_Route19_LassSamantha_Divergent[] = {
    { .lvl = 48, .species = SPECIES_COMFEY },
    { .lvl = 49, .species = SPECIES_VESPIQUEN },
    { .lvl = 48, .species = SPECIES_FROSMOTH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_CoolTrainerRose_Divergent[] = {
    { .lvl = 50, .species = SPECIES_SALAZZLE },
    { .lvl = 50, .species = SPECIES_DRAGONAIR },
    { .lvl = 50, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhineas_Divergent[] = {
    { .lvl = 49, .species = SPECIES_JELLICENT },
    { .lvl = 50, .species = SPECIES_TURTONATOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhoebe_Divergent[] = {
    { .lvl = 49, .species = SPECIES_JELLICENT_F },
    { .lvl = 50, .species = SPECIES_ORANGURU }
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
        .species = SPECIES_PRIMEAPE, // Bug / Dark
        .moves = { MOVE_UTURN, MOVE_THROATCHOP, MOVE_SCREECH, MOVE_CROSSCHOP },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_MISMAGIUS, // Fire / Fairy
        .moves = { MOVE_MYSTICALFIRE, MOVE_DAZZLINGGLEAM, MOVE_NASTYPLOT, MOVE_POWERGEM },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_NinjaBoyJulien_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_LILEEP, // Normal / Ghost
        .moves = { MOVE_CURSE, MOVE_ATTRACT, MOVE_GIGADRAIN, MOVE_BULLDOZE },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_FRILLISH, // Ice / Poison
        .moves = { MOVE_ICEBEAM, MOVE_TOXIC, MOVE_RAINDANCE, MOVE_BRINE },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_NIDOKING, // Water / Fighting
        .moves = { MOVE_SURF, MOVE_BRICKBREAK, MOVE_BODYSLAM, MOVE_SUBSTITUTE },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_BugCatcherPerry_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_SUNFLORA, // Grass / Fire
        .moves = { MOVE_SYNTHESIS, MOVE_SUNNYDAY, MOVE_WEATHERBALL, MOVE_SOLARBEAM },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_SLOWBRO, // Electric / Fire
        .moves = { MOVE_THUNDERWAVE, MOVE_FLAMETHROWER, MOVE_SURF, MOVE_PSYSHOCK },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_FLYGON, // Bug / Dragon
        .moves = { MOVE_BUGBITE, MOVE_DRAGONDANCE, MOVE_THUNDERPUNCH, MOVE_EARTHQUAKE },
        .ability = Ability_Random_1_2
    },
};
// #endregion

// #region Route 23
const struct TrainerMonNoItemDefaultMoves sParty_Route23_BirdKeeperTyrone_Divergent[] = {
    { .lvl = 52, .species = SPECIES_PELIPPER },
    { .lvl = 52, .species = SPECIES_FLETCHINDER },
    { .lvl = 53, .species = SPECIES_DECIDUEYE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GamblerGordon_Divergent[] = {
    { .lvl = 50, .species = SPECIES_YAMASK_G },
    { .lvl = 50, .species = SPECIES_GURDURR },
    { .lvl = 51, .species = SPECIES_HERACROSS },
    { .lvl = 51, .species = SPECIES_MIMIKYU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_SuperNerdEmmett_Divergent[] = {
    { .lvl = 53, .species = SPECIES_DRAGONAIR },
    { .lvl = 53, .species = SPECIES_DHELMISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GentlemanRussell_Divergent[] = {
    { .lvl = 53, .species = SPECIES_STOUTLAND },
    { .lvl = 53, .species = SPECIES_MANDIBUZZ },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_CrushGirlLily_Divergent[] = {
    { .lvl = 50, .species = SPECIES_SCRAGGY },
    { .lvl = 51, .species = SPECIES_FALINKS },
    { .lvl = 52, .species = SPECIES_CONKELDURR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_BeautyMiranda_Divergent[] = {
    { .lvl = 52, .species = SPECIES_SLOWPOKE },
    { .lvl = 52, .species = SPECIES_SLOWPOKE_G },
    { .lvl = 53, .species = SPECIES_SLOWPOKE },
};
// #endregion

// #region Route 20
const struct TrainerMonNoItemDefaultMoves sParty_Route20_PsychicMcKenzie_Divergent[] = {
    { .lvl = 49, .species = SPECIES_BEHEEYEM },
    { .lvl = 50, .species = SPECIES_ORBEETLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_PicknickerWhitney_Divergent[] = {
    { .lvl = 48, .species = SPECIES_FLETCHINDER },
    { .lvl = 48, .species = SPECIES_RIBOMBEE },
    { .lvl = 50, .species = SPECIES_TOXICROAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_TriathleteLena_Divergent[] = {
    { .lvl = 50, .species = SPECIES_MEGANIUM },
    { .lvl = 50, .species = SPECIES_WHIMSICOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_EngineerHomer_Divergent[] = {
    { .lvl = 50, .species = SPECIES_HELIOLISK },
    { .lvl = 51, .species = SPECIES_KLINKLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_CrushGirlRoxy_Divergent[] = {
    { .lvl = 53, .species = SPECIES_LUCARIO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_HikerRoyce_Divergent[] = {
    { .lvl = 50, .species = SPECIES_CARBINK },
    { .lvl = 50, .species = SPECIES_SHUCKLE },
    { .lvl = 51, .species = SPECIES_STUNFISK_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_SuperNerdElliot_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CARNIVINE },
    { .lvl = 52, .species = SPECIES_KANGASKHAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_YoungsterDewey_Divergent[] = {
    { .lvl = 50, .species = SPECIES_HERDIER },
    { .lvl = 50, .species = SPECIES_LYCANROC_N },
    { .lvl = 51, .species = SPECIES_VIKAVOLT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_JugglerHiram_Divergent[] = {
    { .lvl = 52, .species = SPECIES_MAWILE },
    { .lvl = 53, .species = SPECIES_MR_MIME_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_NurseJudy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_COMFEY },
    { .lvl = 52, .species = SPECIES_CHANSEY }
};
// #endregion

// #region Route 22
const struct TrainerMonNoItemDefaultMoves sParty_Route22_CoolTrainer_Gail_Divergent[] = {
    { .lvl = 51, .species = SPECIES_GASTRODON },
    { .lvl = 52, .species = SPECIES_SKARMORY },
    { .lvl = 53, .species = SPECIES_GARCHOMP }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_ScientistLarry_Divergent[] = {
    { .lvl = 52, .species = SPECIES_WEEZING_G },
    { .lvl = 52, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_SrAndJr_AlmaAndMai_Divergent[] = {
    { .lvl = 51, .species = SPECIES_LEAFEON },
    { .lvl = 51, .species = SPECIES_ORANGURU },
    { .lvl = 52, .species = SPECIES_RIBOMBEE },
    { .lvl = 52, .species = SPECIES_SABLEYE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_JugglerChauncy_Divergent[] = {
    { .lvl = 52, .species = SPECIES_BRIONNE },
    { .lvl = 52, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_BurglarMose_Divergent[] = {
    { .lvl = 53, .species = SPECIES_BISHARP },
    { .lvl = 54, .species = SPECIES_TOXICROAK },
    { .lvl = 54, .species = SPECIES_SCRAFTY }
};
// #endregion

// #region Route 21
const struct TrainerMonNoItemDefaultMoves sParty_Route21_PokefanWalter_Divergent[] = {
    { .lvl = 51, .species = SPECIES_BIBAREL },
    { .lvl = 51, .species = SPECIES_PIGNITE },
    { .lvl = 52, .species = SPECIES_MAGCARGO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_CollectorEric_Divergent[] = {
    { .lvl = 53, .species = SPECIES_ROTOM },
    { .lvl = 53, .species = SPECIES_KANGASKHAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_HikerRicardo_Divergent[] = {
    { .lvl = 52, .species = SPECIES_CARKOL },
    { .lvl = 53, .species = SPECIES_GOGOAT },
    { .lvl = 52, .species = SPECIES_MUDSDALE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_DragonTamerTanner_Divergent[] = {
    { .lvl = 55, .species = SPECIES_DRAGONITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_ParasolLadyKatrina_Divergent[] = {
    { .lvl = 52, .species = SPECIES_FLAAFFY },
    { .lvl = 52, .species = SPECIES_EMOLGA },
    { .lvl = 53, .species = SPECIES_SYLVEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_NinjaBoyIshan_Divergent[] = {
    { .lvl = 51, .species = SPECIES_MIMIKYU },
    { .lvl = 51, .species = SPECIES_WOBBUFFET },
    { .lvl = 52, .species = SPECIES_SUDOWOODO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_RockerAxel_Divergent[] = {
    { .lvl = 51, .species = SPECIES_VIBRAVA },
    { .lvl = 51, .species = SPECIES_TOXTRICITY },
    { .lvl = 52, .species = SPECIES_RILLABOOM }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_NurseBenedikta_Divergent[] = {
    { .lvl = 53, .species = SPECIES_HATTERENE }
};
// #endregion

// #region Secret Trail
const struct TrainerMonNoItemDefaultMoves sParty_SecretTrail_ChannelerHeather_Divergent[] = {
    { .lvl = 54, .species = SPECIES_NOCTOWL },
    { .lvl = 54, .species = SPECIES_PHANTUMP },
    { .lvl = 54, .species = SPECIES_SABLEYE }
};
// #endregion

// #region Mimmett Jungle
const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ScientistSilas_Divergent[] = {
    { .lvl = 51, .species = SPECIES_ESPEON },
    { .lvl = 52, .species = SPECIES_SERPERIOR },
    { .lvl = 52, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_RuinManiacWinston_Divergent[] = {
    { .lvl = 51, .species = SPECIES_VULLABY },
    { .lvl = 53, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BlackbeltLouis_Divergent[] = {
    { .lvl = 54, .species = SPECIES_CONKELDURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ChannelerFreyja_Divergent[] = {
    { .lvl = 51, .species = SPECIES_MISDREAVUS },
    { .lvl = 51, .species = SPECIES_MISDREAVUS },
    { .lvl = 52, .species = SPECIES_SABLEYE },
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BugCatcherNeil_Divergent[] = {
    { .lvl = 52, .species = SPECIES_GALVANTULA },
    { .lvl = 53, .species = SPECIES_VIKAVOLT }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_FishermanJerry_Divergent[] = {
    { .lvl = 52, .species = SPECIES_JELLICENT },
    { .lvl = 53, .species = SPECIES_GASTRODON }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PokefanSusan_Divergent[] = {
    { .lvl = 52, .species = SPECIES_LOPUNNY },
    { .lvl = 53, .species = SPECIES_FROSMOTH }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PsychicWanda_Divergent[] = {
    { .lvl = 54, .species = SPECIES_HATTERENE }
};
// #endregion

// #region Tsarvosa City
const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_StatsDojo_Kaito_Divergent[] = {
    {
        .lvl = 51,
        .species = SPECIES_GOGOAT,
        .moves = { MOVE_SEEDBOMB, MOVE_BULKUP, MOVE_HORNLEECH, MOVE_BULLDOZE },
        .ability = Ability_1 // Sap Sipper
    },
    {
        .lvl = 52,
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SHELLTRAP, MOVE_FLAMETHROWER, MOVE_OUTRAGE, MOVE_IRONDEFENSE },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 52,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_NIGHTSLASH, MOVE_IRONHEAD, MOVE_XSCISSOR },
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 53,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_STONEEDGE, MOVE_HAMMERARM, MOVE_BULKUP, MOVE_FIREPUNCH },
        .ability = Ability_2 // Sheer Force
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_SLAKOTH },
    { .lvl = 1, .species = SPECIES_SHROOMISH },
    { .lvl = 1, .species = SPECIES_HAPPINY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_NOCTOWL },
    { .lvl = 1, .species = SPECIES_VAPOREON },
    { .lvl = 1, .species = SPECIES_CHANSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_SLAKING },
    { .lvl = 1, .species = SPECIES_SLAKING },
    { .lvl = 1, .species = SPECIES_BLISSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_NIDORAN_M },
    { .lvl = 1, .species = SPECIES_MUDKIP },
    { .lvl = 1, .species = SPECIES_PIKIPEK }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_NIDORINO },
    { .lvl = 1, .species = SPECIES_MARSHTOMP },
    { .lvl = 1, .species = SPECIES_TRUMBEAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_NIDOKING },
    { .lvl = 1, .species = SPECIES_SWAMPERT },
    { .lvl = 1, .species = SPECIES_TOUCANNON }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_KLINK },
    { .lvl = 1, .species = SPECIES_CHESPIN },
    { .lvl = 1, .species = SPECIES_ROLYCOLY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_KLANG },
    { .lvl = 1, .species = SPECIES_QUILLADIN },
    { .lvl = 1, .species = SPECIES_CARKOL }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_KLINKLANG },
    { .lvl = 1, .species = SPECIES_CHESNAUGHT },
    { .lvl = 1, .species = SPECIES_COALOSSAL }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_MAREEP },
    { .lvl = 1, .species = SPECIES_RALTS },
    { .lvl = 1, .species = SPECIES_OSHAWOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_FLAAFFY },
    { .lvl = 1, .species = SPECIES_KIRLIA },
    { .lvl = 1, .species = SPECIES_DEWOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_AMPHAROS },
    { .lvl = 1, .species = SPECIES_GARDEVOIR },
    { .lvl = 1, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_FLABEBE_ORANGE },
    { .lvl = 1, .species = SPECIES_BLIPBUG },
    { .lvl = 1, .species = SPECIES_GOOMY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_FLOETTE_ORANGE },
    { .lvl = 1, .species = SPECIES_DOTTLER },
    { .lvl = 1, .species = SPECIES_SLIGGOO }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_FLORGES_ORANGE },
    { .lvl = 1, .species = SPECIES_ORBEETLE },
    { .lvl = 1, .species = SPECIES_GOODRA }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed1_Divergent[] = {
    { .lvl = 1, .species = SPECIES_SNIVY },
    { .lvl = 1, .species = SPECIES_ZUBAT },
    { .lvl = 1, .species = SPECIES_SCORBUNNY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed2_Divergent[] = {
    { .lvl = 1, .species = SPECIES_SERVINE },
    { .lvl = 1, .species = SPECIES_GOLBAT },
    { .lvl = 1, .species = SPECIES_RABOOT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed3_Divergent[] = {
    { .lvl = 1, .species = SPECIES_SERPERIOR },
    { .lvl = 1, .species = SPECIES_CROBAT },
    { .lvl = 1, .species = SPECIES_CINDERACE }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin1_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYPHLOSION,
        .moves = { MOVE_LAVAPLUME, MOVE_HIDDENPOWER, MOVE_AERIALACE, MOVE_EXTRASENSORY },
        .heldItem = ITEM_CHARCOAL,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GALLADE,
        .moves = { MOVE_PSYCHOCUT, MOVE_LEAFBLADE, MOVE_CLOSECOMBAT, MOVE_SWORDSDANCE },
        .heldItem = ITEM_GALLADITE,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NIDOKING,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_DRILLRUN, MOVE_SURF },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Rivalry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JELLICENT,
        .moves = { MOVE_SCALD, MOVE_ICEBEAM, MOVE_OMINOUSWIND, MOVE_RECOVER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SHIINOTIC,
        .moves = { MOVE_GIGADRAIN, MOVE_MOONBLAST, MOVE_CHARGEBEAM, MOVE_STRENGTHSAP },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Effect Spore
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin2_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_EARTHQUAKE, MOVE_ICICLECRASH, MOVE_ICESHARD, MOVE_ROCKTOMB },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TREVENANT,
        .moves = { MOVE_WILLOWISP, MOVE_HORNLEECH, MOVE_SHADOWCLAW, MOVE_GROWTH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_QUIVERDANCE, MOVE_BUGBUZZ, MOVE_HURRICANE },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYRANTRUM,
        .moves = { MOVE_HEADSMASH, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_DRAGONCLAW },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_WAVECRASH, MOVE_SHELLSMASH, MOVE_CRUNCH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_BLASTOISINITE_G,
        .ability = Ability_Hidden // Rain Dish
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal1_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AIRSLASH, MOVE_DAZZLINGGLEAM, MOVE_FIREBLAST, MOVE_NASTYPLOT },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_GIGADRAIN, MOVE_SLUDGEBOMB, MOVE_TOXIC, MOVE_PROTECT },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Chlorophyll
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CHARIZARD,
        .moves = { MOVE_FLAMETHROWER, MOVE_SOLARBEAM, MOVE_TAILWIND, MOVE_PROTECT },
        .heldItem = ITEM_CHARIZARDITE_Y,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_SCALESHOT, MOVE_EARTHQUAKE, MOVE_FIREFANG, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_UTURN, MOVE_TAUNT, MOVE_ROOST },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal2_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_FLAREBLITZ, MOVE_SUPERPOWER, MOVE_HEADSMASH, MOVE_WILDCHARGE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Reckless
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_WATERFALL, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_CRUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Moxie
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROTOM_WASH,
        .moves = { MOVE_HYDROPUMP, MOVE_VOLTSWITCH, MOVE_NASTYPLOT, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_GIGADRAIN, MOVE_SPORE, MOVE_RAGEPOWDER, MOVE_PROTECT },
        .heldItem = ITEM_MENTAL_HERB,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYCHIC, MOVE_HIDDENPOWER, MOVE_PROTECT },
        .heldItem = ITEM_GARDEVOIRITE,
        .ability = Ability_Hidden // Telepathy
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
        .species = SPECIES_STOUTLAND,
        .moves = { MOVE_RETALIATE, MOVE_FIREFANG, MOVE_PLAYROUGH, MOVE_ROAR },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_REVERSAL, MOVE_HEADBUTT, MOVE_REST, MOVE_SLEEPTALK },
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_CRUNCH, MOVE_FAKEOUT, MOVE_BODYSLAM, MOVE_WORKUP },
        .ability = Ability_2 // Scrappy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ashley_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGCARGO,
        .moves = { MOVE_SHELLSMASH, MOVE_ROCKSLIDE, MOVE_RECOVER, MOVE_FLAMETHROWER },
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_NASTYPLOT, MOVE_CRUNCH, MOVE_FLAMETHROWER, MOVE_MUDSHOT },
        .ability = Ability_Hidden // Unnerve
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_FIREBLAST, MOVE_TOXIC, MOVE_DRAGONPULSE, MOVE_VENOSHOCK },
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_LASTRESORT, MOVE_DIG, MOVE_WILLOWISP },
        .ability = Ability_Hidden // Guts
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Chelsea_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BIBAREL,
        .moves = { MOVE_CURSE, MOVE_SUPERFANG, MOVE_AQUATAIL, MOVE_AQUAJET },
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_RAINDANCE, MOVE_HURRICANE, MOVE_WATERFALL, MOVE_ICEFANG },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GASTRODON,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_BODYSLAM },
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_ICEBEAM, MOVE_RAINDANCE, MOVE_HYDROPUMP, MOVE_DRAGONPULSE },
        .ability = Ability_Hidden // Hydration
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Buddy_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CACTURNE,
        .moves = { MOVE_LEECHSEED, MOVE_SPIKYSHIELD, MOVE_SUCKERPUNCH, MOVE_SPIKES },
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_TOXICSPIKES, MOVE_GIGADRAIN, MOVE_SWIFT, MOVE_VENOSHOCK },
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRADILY,
        .moves = { MOVE_ANCIENTPOWER, MOVE_AMNESIA, MOVE_GIGADRAIN, MOVE_WRAP },
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DHELMISE,
        .moves = { MOVE_ANCHORSHOT, MOVE_WHIRLPOOL, MOVE_SHADOWCLAW, MOVE_LIQUIDATION },
        .ability = Ability_1 // Steelworker
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Gawain_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FALINKS,
        .moves = { MOVE_NORETREAT, MOVE_CLOSECOMBAT, MOVE_FIRSTIMPRESSION, MOVE_HEADBUTT },
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PRIMEAPE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_CROSSCHOP, MOVE_FOCUSENERGY, MOVE_SCREECH },
        .ability = Ability_2 // Anger Point
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIENSHAO,
        .moves = { MOVE_UTURN, MOVE_DRAINPUNCH, MOVE_BOUNCE, MOVE_DETECT },
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRUTALSWING, MOVE_STEELWING },
        .ability = Ability_Hidden // Scrappy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Skylar_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EMOLGA,
        .moves = { MOVE_VOLTSWITCH, MOVE_LIGHTSCREEN, MOVE_DISCHARGE, MOVE_ACROBATICS },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOUCANNON,
        .moves = { MOVE_ROOST, MOVE_BULLETSEED, MOVE_ROCKBLAST, MOVE_DRILLPECK },
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MANDIBUZZ,
        .moves = { MOVE_DARKPULSE, MOVE_AIRSLASH, MOVE_IRONDEFENSE, MOVE_KNOCKOFF },
        .ability = Ability_2 // Overcoat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_AERIALACE, MOVE_FLAREBLITZ, MOVE_TAILWIND, MOVE_STEELWING },
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Bella_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CROBAT,
        .moves = { MOVE_CROSSPOISON, MOVE_TAILWIND, MOVE_LEECHLIFE, MOVE_ACROBATICS },
        .ability = Ability_Hidden // Inflitrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_TOXIC, MOVE_GIGADRAIN, MOVE_CLEARSMOG, MOVE_ASTONISH },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_POISONJAB, MOVE_SUCKERPUNCH, MOVE_ROCKSLIDE, MOVE_PROTECT },
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_BANEFULBUNKER, MOVE_TOXICSPIKES, MOVE_RECOVER, MOVE_SURF },
        .ability = Ability_1 // Merciless
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Flash_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RAICHU,
        .moves = { MOVE_NASTYPLOT, MOVE_DISCHARGE, MOVE_LIGHTSCREEN, MOVE_IRONTAIL },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GALVANTULA,
        .moves = { MOVE_THUNDER, MOVE_SUCKERPUNCH, MOVE_BUGBUZZ, MOVE_THUNDERWAVE },
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = { MOVE_CHARGE, MOVE_DISCHARGE, MOVE_POISONJAB, MOVE_BOOMBURST },
        .ability = Ability_1 // Punk Rock
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VIKAVOLT,
        .moves = { MOVE_CRUNCH, MOVE_THUNDERBOLT, MOVE_BUGBUZZ, MOVE_FLY },
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Terra_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HIPPOWDON_F,
        .moves = { MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_ICEFANG, MOVE_YAWN },
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_HEAVYSLAM, MOVE_HIGHHORSEPOWER, MOVE_STOMP, MOVE_STEALTHROCK },
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_SNAPTRAP, MOVE_MUDDYWATER, MOVE_BOUNCE, MOVE_IRONDEFENSE },
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLYGON,
        .moves = { MOVE_DRAGONCLAW, MOVE_DRAGONDANCE, MOVE_EARTHQUAKE, MOVE_BUGBUZZ },
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Seifa_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MALAMAR,
        .moves = { MOVE_SUPERPOWER, MOVE_PSYCHOCUT, MOVE_NIGHTSLASH, MOVE_LIQUIDATION },
        .ability = Ability_1 // Contrary
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_ENCORE, MOVE_SAFEGUARD },
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_MISTYTERRAIN, MOVE_FREEZEDRY, MOVE_PSYCHIC},
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_PSYCHIC, MOVE_PSYCHUP, MOVE_SHADOWBALL },
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Rocco_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LYCANROC_DUSK,
        .moves = { MOVE_ACCELEROCK, MOVE_STEALTHROCK, MOVE_CRUNCH, MOVE_SUCKERPUNCH },
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_PROTECT, MOVE_BULLDOZE },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_TARSHOT, MOVE_SMACKDOWN, MOVE_BODYPRESS },
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STONJOURNER,
        .moves = { MOVE_ROCKSLIDE, MOVE_BODYSLAM, MOVE_SANDTOMB, MOVE_CURSE },
        .ability = Ability_1 // Power Spot
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Janice_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_ICICLESPEAR, MOVE_RAZORSHELL, MOVE_SHELLSMASH, MOVE_TOXICSPIKES },
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AVALUGG,
        .moves = { MOVE_HAIL, MOVE_BLIZZARD, MOVE_RECOVER, MOVE_CRUNCH },
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_EARTHQUAKE, MOVE_ICESHARD, MOVE_ICEFANG, MOVE_KNOCKOFF },
        .ability = Ability_2 // Snow Cloak
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AURORUS,
        .moves = { MOVE_AURORAVEIL, MOVE_THUNDERWAVE, MOVE_FREEZEDRY, MOVE_ANCIENTPOWER },
        .ability = Ability_Hidden // Snow Warning
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Antoinette_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VESPIQUEN,
        .moves = { MOVE_DEFENDORDER, MOVE_ATTACKORDER, MOVE_POWERGEM, MOVE_AIRSLASH },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_BRICKBREAK, MOVE_MEGAHORN, MOVE_THROATCHOP, MOVE_SWORDSDANCE },
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_BUGBITE, MOVE_BATONPASS },
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FROSMOTH,
        .moves = { MOVE_STRUGGLEBUG, MOVE_AURORABEAM, MOVE_QUIVERDANCE, MOVE_STUNSPORE },
        .ability = Ability_Hidden // Ice Scales
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ryu_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SMOG, MOVE_FLAMETHROWER, MOVE_SHELLSMASH, MOVE_DRAGONPULSE },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NOIVERN,
        .moves = { MOVE_DRAGONPULSE, MOVE_MOONLIGHT, MOVE_ROOST, MOVE_AIRSLASH },
        .ability = Ability_2 // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYRANTRUM,
        .moves = { MOVE_CRUNCH, MOVE_DRAGONCLAW, MOVE_FIREFANG, MOVE_THUNDERFANG },
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_DRAGONDANCE, MOVE_DRAGONCLAW, MOVE_EARTHQUAKE, MOVE_POISONJAB },
        .ability = Ability_Hidden // Rough Skin
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Caspar_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JELLICENT,
        .moves = { MOVE_RECOVER, MOVE_WILLOWISP, MOVE_HEX, MOVE_SCALD },
        .ability = Ability_2 // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RUNERIGUS,
        .moves = { MOVE_SHADOWCLAW, MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_ENERGYBALL },
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROTOM,
        .moves = { MOVE_REST, MOVE_DISCHARGE, MOVE_HEX, MOVE_WILLOWISP },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_SHADOWBALL, MOVE_FUTURESIGHT, MOVE_THUNDERPUNCH, MOVE_ICEPUNCH },
        .ability = Ability_Hidden // Frisk
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Darcy_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_BEATUP, MOVE_METALCLAW, MOVE_KNOCKOFF },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_HONECLAWS, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_FIREFANG },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUK_A,
        .moves = { MOVE_GUNKSHOT, MOVE_CRUNCH, MOVE_TOXIC, MOVE_MINIMIZE },
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BISHARP,
        .moves = { MOVE_SLASH, MOVE_IRONDEFENSE, MOVE_NIGHTSLASH, MOVE_FURYCUTTER },
        .ability = Ability_1 // Defiant
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Mason_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_SPIKES, MOVE_ROOST, MOVE_DRILLPECK, MOVE_STEELWING },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_POWERWHIP, MOVE_CURSE, MOVE_GYROBALL, MOVE_INGRAIN },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KLINKLANG,
        .moves = { MOVE_SHIFTGEAR, MOVE_GEARGRIND, MOVE_CHARGEBEAM, MOVE_METALSOUND },
        .ability = Ability_Hidden // Clear Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_AURASPHERE, MOVE_METEORMASH, MOVE_BONERUSH, MOVE_SWORDSDANCE },
        .ability = Ability_1 // Steadfast
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Faye_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLORGES_YELLOW,
        .moves = { MOVE_MOONBLAST, MOVE_SYNTHESIS, MOVE_PETALDANCE, MOVE_MISTYTERRAIN },
        .ability = Ability_1 // Flower Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_STRANGESTEAM, MOVE_TOXIC, MOVE_SLUDGEBOMB, MOVE_HEATWAVE },
        .ability = Ability_2 // Neutralizing Gas
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_THUNDERWAVE, MOVE_AIRSLASH, MOVE_MOONBLAST, MOVE_CALMMIND },
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIMIKYU,
        .moves = { MOVE_WOODHAMMER, MOVE_SHADOWCLAW, MOVE_CHARM, MOVE_PLAYROUGH },
        .ability = Ability_1 // Disguise
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_PokefanMarci_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_DELPHOX,
        .moves = { MOVE_TRICK, MOVE_PSYSHOCK, MOVE_MYSTICALFIRE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 54,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_SUCKERPUNCH, MOVE_NIGHTSLASH, MOVE_EMBARGO, MOVE_METALBURST },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 54,
        .species = SPECIES_MR_MIME_G,
        .moves = { MOVE_TRICK, MOVE_RECYCLE, MOVE_FLING, MOVE_FREEZEDRY },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Screen Cleaner
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_ChannelerJamila_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_FROSLASS,
        .moves = { MOVE_FROSTBREATH, MOVE_DESTINYBOND, MOVE_CRUNCH, MOVE_SHADOWBALL },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_CoolTrainerNorbert_Divergent[] = {
    {
        .lvl = 55,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_ELECTROBALL, MOVE_HIDDENPOWER, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 55,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_HAMMERARM, MOVE_ROCKSLIDE, MOVE_BULKUP, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Guts
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_BurglarMarion_Divergent[] = {
    {
        .lvl = 53,
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_SPIKES, MOVE_TOXICSPIKES, MOVE_BUGBITE, MOVE_POISONTAIL },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Poison Point
    },
    {
        .lvl = 53,
        .species = SPECIES_BARBARACLE,
        .moves = { MOVE_RAZORSHELL, MOVE_ROCKPOLISH, MOVE_SLASH, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 54,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_DISABLE, MOVE_MEANLOOK },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Mummy
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
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_FACADE, MOVE_PLAYROUGH, MOVE_UTURN, MOVE_RETALIATE },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 54,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_TARSHOT, MOVE_INCINERATE, MOVE_STEALTHROCK, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 54,
        .species = SPECIES_SHIINOTIC,
        .moves = { MOVE_STRENGTHSAP, MOVE_SPORE, MOVE_DAZZLINGGLEAM, MOVE_SWAGGER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Effect Spore
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_GentlemanPaul_Divergent[] = {
    {
        .lvl = 53,
        .species = SPECIES_CARBINK,
        .moves = { MOVE_LIGHTSCREEN, MOVE_REFLECT, MOVE_STEALTHROCK, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 54,
        .species = SPECIES_RAICHU,
        .moves = { MOVE_NUZZLE, MOVE_THUNDERBOLT, MOVE_IRONTAIL, MOVE_NASTYPLOT },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 53,
        .species = SPECIES_DARMANITAN_G,
        .moves = { MOVE_ICEPUNCH, MOVE_EARTHQUAKE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Gorilla Tactics
    },
    {
        .lvl = 54,
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_POISONJAB, MOVE_SUCKERPUNCH, MOVE_DRAINPUNCH, MOVE_NONE },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Poison Touch
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
    { .lvl = 54, .species = SPECIES_CROAGUNK },
    { .lvl = 55, .species = SPECIES_WEAVILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerHasan_Divergent[] = {
    { .lvl = 54, .species = SPECIES_KLINK },
    { .lvl = 54, .species = SPECIES_KLANG },
    { .lvl = 54, .species = SPECIES_KLINKLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BurglarWill_Divergent[] = {
    { .lvl = 53, .species = SPECIES_SCRAGGY },
    { .lvl = 54, .species = SPECIES_THIEVUL },
    { .lvl = 55, .species = SPECIES_SERPERIOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerElroy_Divergent[] = {
    { .lvl = 54, .species = SPECIES_MAWILE },
    { .lvl = 54, .species = SPECIES_RAICHU }
};
// #endregion

// #region Carnelidge Volcano
const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerBjorn_Divergent[] = {
    { .lvl = 54, .species = SPECIES_STONJOURNER },
    { .lvl = 54, .species = SPECIES_GURDURR },
    { .lvl = 54, .species = SPECIES_MUDSDALE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ChannelerKelsey_Divergent[] = {
    { .lvl = 53, .species = SPECIES_DUSKULL },
    { .lvl = 53, .species = SPECIES_MISDREAVUS },
    { .lvl = 53, .species = SPECIES_SABLEYE },
    { .lvl = 54, .species = SPECIES_MISMAGIUS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_JugglerSeth_Divergent[] = {
    { .lvl = 55, .species = SPECIES_MR_MIME_G },
    { .lvl = 55, .species = SPECIES_DELPHOX },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_DragonTamerFlynn_Divergent[] = {
    { .lvl = 54, .species = SPECIES_SLIGGOO },
    { .lvl = 55, .species = SPECIES_GABITE },
    { .lvl = 55, .species = SPECIES_DRAGONITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_BirdKeepeFalco_Divergent[] = {
    { .lvl = 55, .species = SPECIES_CORVISQUIRE },
    { .lvl = 55, .species = SPECIES_TALONFLAME },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_CrushGirlEunice_Divergent[] = {
    { .lvl = 56, .species = SPECIES_SIRFETCHD },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_SuperNerdNathan_Divergent[] = {
    { .lvl = 54, .species = SPECIES_PINCURCHIN },
    { .lvl = 54, .species = SPECIES_CRABOMINABLE },
    { .lvl = 55, .species = SPECIES_SKARMORY },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerHugh_Divergent[] = {
    { .lvl = 55, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 56, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ScientistXander_Divergent[] = {
    { .lvl = 55, .species = SPECIES_LILEEP },
    { .lvl = 55, .species = SPECIES_WEEZING_G },
    { .lvl = 55, .species = SPECIES_LUCARIO },
};
// #endregion

// #region Uteya Village
const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_PicknickerLisa_Divergent[] = {
    { .lvl = 1, .species = SPECIES_CURSOLA },
    { .lvl = 1, .species = SPECIES_BRELOOM },
    { .lvl = 1, .species = SPECIES_MR_RIME }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_SwimmerTyson_Divergent[] = {
    { .lvl = 1, .species = SPECIES_FLAREON },
    { .lvl = 1, .species = SPECIES_NINJASK },
    { .lvl = 1, .species = SPECIES_FLORGES }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_ScientistWilford_Divergent[] = {
    { .lvl = 1, .species = SPECIES_KROOKODILE },
    { .lvl = 1, .species = SPECIES_NOIVERN },
    { .lvl = 1, .species = SPECIES_DECIDUEYE }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Michael_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_CARBINK,
        .moves = { MOVE_ROCKSLIDE, MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_STEALTHROCK },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Clear Body
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Leo_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_ROCKSLIDE, MOVE_SNARL, MOVE_COACHING, MOVE_BRICKBREAK },
        .ability = Ability_Hidden // Intimidate
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Bonnie_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_STONJOURNER,
        .moves = { MOVE_WIDEGUARD, MOVE_BLOCK, MOVE_ROCKSLIDE, MOVE_CURSE },
        .ability = Ability_1 // Power Spot
    },
    {
        .lvl = 59,
        .species = SPECIES_FROSMOTH,
        .moves = { MOVE_TAILWIND, MOVE_HAIL, MOVE_BLIZZARD, MOVE_AURORAVEIL },
        .ability = Ability_Hidden // Ice Scales
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
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_SAFEGUARD, MOVE_REFLECT, MOVE_PSYCHIC, MOVE_FREEZEDRY },
        .ability = Ability_Hidden // Ice Body
    },
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Jessie_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_SLAKING,
        .moves = { MOVE_KNOCKOFF, MOVE_GIGAIMPACT, MOVE_HAMMERARM, MOVE_PLAYROUGH },
        .ability = Ability_1 // Truant
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_James_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_AROMATICMIST, MOVE_AROMATHERAPY, MOVE_HEATWAVE, MOVE_STRANGESTEAM },
        .ability = Ability_2 // Neutralizing Gas
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Mike_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_WATERFALL, MOVE_ICEFANG, MOVE_DRAGONDANCE, MOVE_EARTHQUAKE },
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Diane_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_PINCURCHIN,
        .moves = { MOVE_RECOVER, MOVE_PROTECT, MOVE_ZINGZAP, MOVE_ELECTRICTERRAIN },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_1 // Lightning Rod
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Hannibal_Divergent[] = {
    {
		// TODO: Update this
        .lvl = 58,
        .species = SPECIES_FLYGON,
        .moves = { MOVE_HEATWAVE, MOVE_BUGBUZZ, MOVE_EARTHQUAKE, MOVE_DRAGONPULSE },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 59,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DECORATE, MOVE_AROMATICMIST, MOVE_DAZZLINGGLEAM, MOVE_LIGHTSCREEN },
        .ability = Ability_Hidden // Aroma Veil
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Clarice_Divergent[] = {
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
    { .lvl = 60, .species = SPECIES_HATTREM },
    { .lvl = 61, .species = SPECIES_HATTERENE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_DragonTamerDavid_Divergent[] = {
    { .lvl = 61, .species = SPECIES_TURTONATOR },
    { .lvl = 61, .species = SPECIES_TYRANTRUM },
    { .lvl = 62, .species = SPECIES_CHARIZARD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_PsychicJeff_Divergent[] = {
    { .lvl = 61, .species = SPECIES_WOBBUFFET },
    { .lvl = 61, .species = SPECIES_BEHEEYEM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_FishermanHumphrey_Divergent[] = {
    { .lvl = 63, .species = SPECIES_DHELMISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_TriathleteWillow_Divergent[] = {
    { .lvl = 60, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 61, .species = SPECIES_LOPUNNY },
    { .lvl = 61, .species = SPECIES_WHIMSICOTT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_BlackbeltIrvine_Divergent[] = {
    { .lvl = 58, .species = SPECIES_MIENFOO },
    { .lvl = 58, .species = SPECIES_MIENFOO },
    { .lvl = 59, .species = SPECIES_MIENFOO },
    { .lvl = 60, .species = SPECIES_MIENSHAO },
};
// #endregion

// #region Uteyan Ruins
const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacKristian_Divergent[] = {
    { .lvl = 59, .species = SPECIES_STONJOURNER },
    { .lvl = 60, .species = SPECIES_WOBBUFFET }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_PsychicHaley_Divergent[] = {
    { .lvl = 63, .species = SPECIES_ESPEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacCyril_Divergent[] = {
    { .lvl = 58, .species = SPECIES_YAMASK_G },
    { .lvl = 59, .species = SPECIES_COFAGRIGUS },
    { .lvl = 60, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_SuperNerdMorty_Divergent[] = {
    { .lvl = 59, .species = SPECIES_GOGOAT },
    { .lvl = 59, .species = SPECIES_DRAGONAIR },
    { .lvl = 59, .species = SPECIES_GALLADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_ChannelerAgatha_Divergent[] = {
    { .lvl = 60, .species = SPECIES_MIMIKYU },
    { .lvl = 60, .species = SPECIES_UMBREON }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_LassDorothy_Divergent[] = {
    { .lvl = 57, .species = SPECIES_FLAAFFY },
    { .lvl = 57, .species = SPECIES_KIRLIA },
    { .lvl = 58, .species = SPECIES_RIBOMBEE },
    { .lvl = 59, .species = SPECIES_WHIMSICOTT },
};
// #endregion

// #region Victory Road
const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerTimothy_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_TORKOAL,
        .moves = { MOVE_BODYSLAM, MOVE_AMNESIA, MOVE_HEATWAVE, MOVE_PROTECT },
        .ability = Ability_1 // White smoke
    },
    {
        .lvl = 60,
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SHELLTRAP, MOVE_SHELLSMASH, MOVE_EXPLOSION, MOVE_FLAIL },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 60,
        .species = SPECIES_TORTERRA,
        .moves = { MOVE_WOODHAMMER, MOVE_LEECHSEED, MOVE_CRUNCH, MOVE_HEADLONGRUSH },
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 61,
        .species = SPECIES_SHUCKLE,
        .moves = { MOVE_POWERSPLIT, MOVE_ROCKSLIDE, MOVE_INFESTATION, MOVE_STICKYWEB },
        .ability = Ability_1 // Sturdy
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
        .species = SPECIES_CRAWDAUNT,
        .moves = { MOVE_SWORDSDANCE, MOVE_CRABHAMMER, MOVE_CRUNCH, MOVE_DIG },
        .ability = Ability_Hidden // Adaptability
    },
    {
        .lvl = 61,
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_ICICLECRASH, MOVE_EARTHQUAKE, MOVE_FLAIL, MOVE_ROCKTOMB },
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 62,
        .species = SPECIES_DELIBIRD,
        .moves = { MOVE_DRILLPECK, MOVE_ICYWIND, MOVE_SEEDBOMB, MOVE_SPIKES },
        .ability = Ability_1 // Vital Spirit
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerSatoshi_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_MUK,
        .moves = { MOVE_TOXIC, MOVE_ACIDARMOR, MOVE_SLUDGEBOMB, MOVE_ZENHEADBUTT },
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 61,
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_MEGAHORN, MOVE_BRICKBREAK, MOVE_THROATCHOP, MOVE_SWORDSDANCE },
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 61,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_CRUNCH, MOVE_SANDSTORM, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 62,
        .species = SPECIES_NOIVERN,
        .moves = { MOVE_BOOMBURST, MOVE_HURRICANE, MOVE_ROOST, MOVE_TAILWIND },
        .ability = Ability_2 // Infiltrator
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerCourtney_Divergent[] = {
    {
        .lvl = 59,
        .species = SPECIES_PALOSSAND,
        .moves = { MOVE_SHOREUP, MOVE_SHADOWBALL, MOVE_EARTHPOWER, MOVE_GIGADRAIN },
        .ability = Ability_1 // Water Compaction
    },
    {
        .lvl = 59,
        .species = SPECIES_SLOWKING,
        .moves = { MOVE_POWERGEM, MOVE_FUTURESIGHT, MOVE_SURF, MOVE_PSYCHUP },
        .ability = Ability_2 // Own Tempo
    },
    {
        .lvl = 59,
        .species = SPECIES_VESPIQUEN,
        .moves = { MOVE_STRUGGLEBUG, MOVE_ROOST, MOVE_TOXIC, MOVE_DEFENDORDER },
        .ability = Ability_Hidden // Unnerve
    },
    {
        .lvl = 60,
        .species = SPECIES_GALLADE,
        .moves = { MOVE_LEAFBLADE, MOVE_SACREDSWORD, MOVE_NIGHTSLASH, MOVE_THUNDERPUNCH },
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 60,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_NIGHTSLASH, MOVE_IRONDEFENSE, MOVE_FURYCUTTER, MOVE_POISONJAB },
        .ability = Ability_Hidden // Pressure
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
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_COUNTER, MOVE_EARTHQUAKE, MOVE_IRONHEAD, MOVE_ROCKSLIDE },
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 62,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_COTTONGUARD, MOVE_DAZZLINGGLEAM, MOVE_THUNDER, MOVE_RAINDANCE },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 63,
        .species = SPECIES_STOUTLAND,
        .moves = { MOVE_PLAYROUGH, MOVE_TAKEDOWN, MOVE_ICEFANG, MOVE_FIREFANG },
        .ability = Ability_Hidden // Scrappy
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
        .species = SPECIES_NIDOKING,
        .moves = { MOVE_SLUDGEBOMB, MOVE_HIGHHORSEPOWER, MOVE_SHADOWBALL, MOVE_THROATCHOP },
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 62,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_LIQUIDATION, MOVE_AGILITY, MOVE_CRUNCH, MOVE_SWAGGER },
        .ability = Ability_1 // Rough Skin
    },
    {
        .lvl = 62,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_LEECHLIFE, MOVE_CROSSPOISON, MOVE_MEANLOOK, MOVE_BRAVEBIRD },
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 62,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_EARTHQUAKE, MOVE_ICEFANG },
        .ability = Ability_Hidden // Moxie
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerArthur_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_SOFTBOILED, MOVE_LIGHTSCREEN, MOVE_THUNDERWAVE, MOVE_SEISMICTOSS },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 60,
        .species = SPECIES_SLAKING,
        .moves = { MOVE_SLACKOFF, MOVE_YAWN, MOVE_COVET, MOVE_FLING },
        .ability = Ability_1 // Truant
    },
    {
        .lvl = 61,
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_ANCIENTPOWER, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_SCORCHINGSANDS },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 61,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_SHADOWBALL },
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 61,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_SHADOWPUNCH, MOVE_WILLOWISP, MOVE_HEX, MOVE_MEANLOOK },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 62,
        .species = SPECIES_NINJASK,
        .moves = { MOVE_BATONPASS, MOVE_SWORDSDANCE, MOVE_XSCISSOR, MOVE_SLASH },
        .ability = Ability_1 // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerKelly_Divergent[] = {
    {
        .lvl = 60,
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_MIRRORCOAT, MOVE_FREEZEDRY, MOVE_PSYCHIC, MOVE_TEETERDANCE },
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 60,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER, MOVE_NASTYPLOT },
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 61,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_HAMMERARM, MOVE_STONEEDGE, MOVE_FOCUSPUNCH, MOVE_ROCKTOMB },
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 62,
        .species = SPECIES_PRIMARINA,
        .moves = { MOVE_HYPERVOICE, MOVE_MOONBLAST, MOVE_SPARKLINGARIA, MOVE_ENERGYBALL },
        .ability = Ability_Hidden // Liquid Voice
    },
    {
        .lvl = 63,
        .species = SPECIES_COPPERAJAH,
        .moves = { MOVE_IRONHEAD, MOVE_BULLDOZE, MOVE_PLAYROUGH, MOVE_HIGHHORSEPOWER },
        .ability = Ability_1 // Sheer Force
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLydia_Divergent[] = {
    {
        .lvl = 61,
        .species = SPECIES_CARBINK,
        .moves = { MOVE_LIGHTSCREEN, MOVE_POWERGEM, MOVE_STEALTHROCK, MOVE_FLASHCANNON },
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 61,
        .species = SPECIES_DHELMISE,
        .moves = { MOVE_SHADOWCLAW, MOVE_ENERGYBALL, MOVE_ANCHORSHOT, MOVE_BULLDOZE },
        .ability = Ability_1 // Steelworker
    },
    {
        .lvl = 62,
        .species = SPECIES_ROTOM_MOW,
        .moves = { MOVE_LEAFSTORM, MOVE_DISCHARGE, MOVE_HEX, MOVE_WILLOWISP },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 62,
        .species = SPECIES_FALINKS,
        .moves = { MOVE_NORETREAT, MOVE_FIRSTIMPRESSION, MOVE_MEGAHORN, MOVE_HEADBUTT },
        .ability = Ability_Hidden // Battle Armor
    },
    {
        .lvl = 63,
        .species = SPECIES_SHEDINJA,
        .moves = { MOVE_CONFUSERAY, MOVE_MUDSLAP, MOVE_GRUDGE, MOVE_LEECHLIFE },
        .ability = Ability_1 // Wonder Guard
    },
    {
        .lvl = 63,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = { MOVE_EXPLOSION, MOVE_SHELLSMASH, MOVE_POWERGEM, MOVE_COSMICPOWER },
        .ability = Ability_1 // Shields Down
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
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_COPYCAT, MOVE_BONERUSH, MOVE_SWORDSDANCE, MOVE_FORCEPALM },
        .ability = Ability_Hidden // Justified
    },
    {
        .lvl = 64,
        .species = SPECIES_SUDOWOODO,
        .moves = { MOVE_MIMIC, MOVE_HAMMERARM, MOVE_STONEEDGE, MOVE_WOODHAMMER },
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLuigi_Divergent[] = {
    {
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
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_TOXIC, MOVE_SLUDGEBOMB, MOVE_HEX, MOVE_REST },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 64,
        .species = SPECIES_BRELOOM,
        .moves = { MOVE_FORCEPALM, MOVE_BULLETSEED, MOVE_MACHPUNCH, MOVE_ROCKTOMB },
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 64,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_BRAVEBIRD, MOVE_FIRSTIMPRESSION, MOVE_KNOCKOFF },
        .ability = Ability_1 // Steadfast
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_NurseCelia_Divergent[] = {
    {
        .lvl = 63,
        .species = SPECIES_CHANSEY,
        .moves = { MOVE_SWEETKISS, MOVE_COVET, MOVE_SOFTBOILED, MOVE_SING },
        .ability = Ability_Hidden // Healer
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
        .species = SPECIES_WHIMSICOTT,
        .moves = { MOVE_LEECHSEED, MOVE_SUBSTITUTE, MOVE_COTTONGUARD, MOVE_GIGADRAIN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 65,
        .species = SPECIES_GASTRODON_EAST,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_SLUDGEWAVE },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 66,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_ROOST, MOVE_TAILWIND, MOVE_FLAREBLITZ, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 66,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE, MOVE_TRICK },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 67,
        .species = SPECIES_MAWILE,
        .moves = { MOVE_IRONHEAD, MOVE_PLAYROUGH, MOVE_ICEPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_MAWILITE,
        .ability = Ability_2 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Lucas_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_SPIKES, MOVE_POWERWHIP, MOVE_GYROBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 66,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 67,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AIRSLASH, MOVE_ROOST, MOVE_THUNDERWAVE, MOVE_AURASPHERE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 67,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_NOBLEROAR, MOVE_ICEPUNCH, MOVE_CLOSECOMBAT, MOVE_OUTRAGE },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 68,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Jenna_Divergent[] = {
    {
        .lvl = 67,
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_TOXICSPIKES, MOVE_BANEFULBUNKER, MOVE_LIQUIDATION, MOVE_RECOVER },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 67,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_NIGHTSLASH, MOVE_IRONHEAD, MOVE_SWORDSDANCE, MOVE_PSYCHOCUT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 68,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 68,
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_ICESHARD, MOVE_EARTHQUAKE, MOVE_ICICLECRASH, MOVE_STONEEDGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 69,
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_FAKEOUT, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_FACADE },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_Hidden // Inner Focus
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Thomas_Divergent[] = {
    {
        .lvl = 68,
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_LEECHSEED, MOVE_SLUDGEBOMB, MOVE_SYNTHESIS, MOVE_GIGADRAIN },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 68,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_STONEEDGE, MOVE_OUTRAGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Intimidate
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
        .species = SPECIES_ROTOM_WASH,
        .moves = { MOVE_REST, MOVE_WILLOWISP, MOVE_VOLTSWITCH, MOVE_HYDROPUMP },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 70,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SLACKOFF, MOVE_CALMMIND, MOVE_PSYSHOCK, MOVE_SCALD },
        .heldItem = ITEM_SLOWBRONITE,
        .ability = Ability_1 // Oblivious
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_Champion_Selene_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_BRAVEBIRD, MOVE_SPIKES, MOVE_IRONHEAD, MOVE_ROOST },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 72,
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_TOXICSPIKES, MOVE_LEECHSEED, MOVE_GIGADRAIN, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Poison Point
    },
    {
        .lvl = 72,
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_HIGHJUMPKICK, MOVE_FAKEOUT, MOVE_RETURN, MOVE_ICEPUNCH },
        .heldItem = ITEM_LOPUNNITE,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 72,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYSHOCK, MOVE_WISH, MOVE_PROTECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Pixelate
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
        .species = SPECIES_THIEVUL,
        .moves = { MOVE_KNOCKOFF, MOVE_PARTINGSHOT, MOVE_ACROBATICS, MOVE_FIREFANG },
        .heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 70,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_GRASSYGLIDE, MOVE_BRICKBREAK, MOVE_COUNTER },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Scrafty
    },
    {
        .lvl = 70,
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_TERRAINPULSE, MOVE_MUDDYWATER, MOVE_DISCHARGE, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 72,
        .species = SPECIES_GOGOAT,
        .moves = { MOVE_HORNLEECH, MOVE_MILKDRINK, MOVE_BULKUP, MOVE_GRASSYTERRAIN },
        .heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_Hidden // Grass Pelt
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PINCURCHIN,
        .moves = { MOVE_ZINGZAP, MOVE_POISONJAB, MOVE_ELECTRICTERRAIN, MOVE_TOXICSPIKES },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Electric Surge
    },
    {
        .lvl = 70,
        .species = SPECIES_SCEPTILE,
        .moves = { MOVE_SCREECH, MOVE_XSCISSOR, MOVE_LEAFBLADE, MOVE_ACROBATICS },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 70,
        .species = SPECIES_LANTURN,
        .moves = { MOVE_RISINGVOLTAGE, MOVE_SCALD, MOVE_ELECTRICTERRAIN, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_TERRAINPULSE, MOVE_MUDDYWATER, MOVE_DISCHARGE, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 72,
        .species = SPECIES_RAICHU_A,
        .moves = { MOVE_SURF, MOVE_RISINGVOLTAGE, MOVE_PSYCHIC, MOVE_NASTYPLOT },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Surge Surfer
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_DELPHOX,
        .moves = { MOVE_PSYCHICTERRAIN, MOVE_WILLOWISP, MOVE_LIGHTSCREEN, MOVE_FLAMETHROWER },
        .heldItem = ITEM_PSYCHIC_SEED,
        .ability = Ability_Hidden // Magician
    },
    {
        .lvl = 70,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_HIGHJUMPKICK, MOVE_DRAGONDANCE, MOVE_ZENHEADBUTT, MOVE_KNOCKOFF },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYSHOCK, MOVE_HEALINGWISH, MOVE_DAZZLINGGLEAM, MOVE_CALMMIND },
        .heldItem = ITEM_PSYCHIC_SEED,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 70,
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_TERRAINPULSE, MOVE_MUDDYWATER, MOVE_DISCHARGE, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 72,
        .species = SPECIES_SLOWKING_G,
        .moves = { MOVE_EXPANDINGFORCE, MOVE_SLACKOFF, MOVE_PSYCHICTERRAIN, MOVE_TOXIC },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Terrence_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_HEATWAVE, MOVE_SLUDGEBOMB, MOVE_THUNDERBOLT, MOVE_PAINSPLIT },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Misty Surge
    },
    {
        .lvl = 70,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_TERRAINPULSE, MOVE_EXTREMESPEED, MOVE_METEORMASH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Justified
    },
    {
        .lvl = 70,
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_PETALDANCE, MOVE_SLUDGEBOMB, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Poison Point
    },
    {
        .lvl = 70,
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_TERRAINPULSE, MOVE_MUDDYWATER, MOVE_DISCHARGE, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 72,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_PSYCHIC, MOVE_MISTYTERRAIN, MOVE_MISTYEXPLOSION, MOVE_MOONBLAST },
        .heldItem = ITEM_MISTY_SEED,
        .ability = Ability_Hidden // Pixelate
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
        .species = SPECIES_GASTRODON_EAST,
        .moves = { MOVE_SCALD, MOVE_RECOVER, MOVE_EARTHPOWER, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 70,
        .species = SPECIES_TOUCANNON,
        .moves = { MOVE_BEAKBLAST, MOVE_ROCKBLAST, MOVE_BULLETSEED, MOVE_FURYATTACK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 70,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_NIGHTSLASH, MOVE_SCREECH, MOVE_ICICLECRASH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 72,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_TARSHOT, MOVE_HEATCRASH, MOVE_STEALTHROCK, MOVE_STONEEDGE },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Flame Body
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = { MOVE_NUZZLE, MOVE_THUNDERFANG, MOVE_SHIFTGEAR, MOVE_POISONJAB },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 70,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_FORCEPALM, MOVE_SMELLINGSALTS, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 70,
        .species = SPECIES_PRIMEAPE,
        .moves = { MOVE_SMELLINGSALTS, MOVE_BODYSLAM, MOVE_CROSSCHOP, MOVE_THUNDERBOLT },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_2 // Anger Point
    },
    {
        .lvl = 70,
        .species = SPECIES_STUNFISK,
        .moves = { MOVE_BOUNCE, MOVE_THUNDERBOLT, MOVE_MUDDYWATER, MOVE_THUNDERWAVE },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 72,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_THUNDERWAVE, MOVE_AIRSLASH, MOVE_ANCIENTPOWER, MOVE_AURASPHERE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Serene Grace
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_SHIINOTIC,
        .moves = { MOVE_SPORE, MOVE_DREAMEATER, MOVE_MOONBLAST, MOVE_GIGADRAIN },
        .heldItem = ITEM_BIG_ROOT,
        .ability = Ability_2 // Effect Spore
    },
    {
        .lvl = 70,
        .species = SPECIES_BRELOOM,
        .moves = { MOVE_SPORE, MOVE_SEEDBOMB, MOVE_MACHPUNCH, MOVE_LEECHSEED },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Poison Heal
    },
    {
        .lvl = 70,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_HYPNOSIS, MOVE_NIGHTMARE, MOVE_MOONBLAST, MOVE_PSYCHIC },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 70,
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_HYPNOSIS, MOVE_DREAMEATER, MOVE_FREEZEDRY, MOVE_REFLECT },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 72,
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_REST, MOVE_SLEEPTALK, MOVE_FREEZEDRY, MOVE_CHARM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Shell Armor
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Stella_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_BANEFULBUNKER, MOVE_TOXICSPIKES, MOVE_RECOVER, MOVE_VENOSHOCK },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 70,
        .species = SPECIES_CURSOLA,
        .moves = { MOVE_STRENGTHSAP, MOVE_HEX, MOVE_TOXIC, MOVE_SURF },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Perish Body
    },
    {
        .lvl = 70,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_SCREECH, MOVE_GUNKSHOT, MOVE_ICEPUNCH, MOVE_METRONOME },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 70,
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_TOXICSPIKES, MOVE_LIGHTSCREEN, MOVE_RAZORSHELL, MOVE_DRILLRUN },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 72,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_FACADE, MOVE_DRAINPUNCH, MOVE_STONEEDGE, MOVE_BULKUP },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Guts
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_TORKOAL,
        .moves = { MOVE_SHELLSMASH, MOVE_HEATWAVE, MOVE_EARTHPOWER, MOVE_STEALTHROCK },
        .heldItem = ITEM_HEAT_ROCK,
        .ability = Ability_2 // Drought
    },
    {
        .lvl = 70,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_TAILWIND, MOVE_STEELWING, MOVE_ACROBATICS, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Gale Wings
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
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_SUNNYDAY, MOVE_THUNDERBOLT, MOVE_WEATHERBALL, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Solar Power
    },
    {
        .lvl = 72,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_MORNINGSUN, MOVE_SOLARBEAM, MOVE_SUNNYDAY },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_HURRICANE, MOVE_ROOST, MOVE_SCALD, MOVE_RAINDANCE },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 70,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_POWERWHIP, MOVE_CURSE, MOVE_GYROBALL, MOVE_LEECHSEED },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 70,
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_WEATHERBALL, MOVE_IRONDEFENSE, MOVE_AQUATAIL, MOVE_FLASHCANNON },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Rain Dish
    },
    {
        .lvl = 70,
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_THUNDER, MOVE_BULLDOZE, MOVE_SURF, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Dry Skin
    },
    {
        .lvl = 72,
        .species = SPECIES_BEARTIC,
        .moves = { MOVE_AQUAJET, MOVE_ICICLECRASH, MOVE_EARTHQUAKE, MOVE_AVALANCHE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Swift Swim
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_HIPPOWDON_F,
        .moves = { MOVE_SLACKOFF, MOVE_YAWN, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 70,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_SANDSTORM, MOVE_DRILLRUN, MOVE_ROCKSLIDE, MOVE_RAPIDSPIN },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Sand Force
    },
    {
        .lvl = 70,
        .species = SPECIES_STOUTLAND,
        .moves = { MOVE_ICEFANG, MOVE_RETALIATE, MOVE_CRUNCH, MOVE_THUNDERWAVE },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_2 // Sand Rush
    },
    {
        .lvl = 70,
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_SANDSTORM, MOVE_PARABOLICCHARGE, MOVE_WEATHERBALL, MOVE_LOWKICK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Sand Veil
    },
    {
        .lvl = 72,
        .species = SPECIES_GIGALITH,
        .moves = { MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_IRONDEFENSE, MOVE_BULLDOZE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sand Stream
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Raine_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_AURORUS,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_THUNDERWAVE, MOVE_ROCKSLIDE },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 70,
        .species = SPECIES_BEARTIC,
        .moves = { MOVE_ICICLECRASH, MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_NIGHTSLASH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Slush Rush
    },
    {
        .lvl = 70,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_BLIZZARD, MOVE_HAIL, MOVE_FREEZEDRY, MOVE_SHADOWBALL },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Snow Cloak
    },
    {
        .lvl = 70,
        .species = SPECIES_MANDIBUZZ,
        .moves = { MOVE_KNOCKOFF, MOVE_TOXIC, MOVE_ROOST, MOVE_AERIALACE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Overcoat
    },
    {
        .lvl = 72,
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_PSYCHIC, MOVE_DAZZLINGGLEAM, MOVE_MIRRORCOAT, MOVE_HAIL },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Ice Body
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_PSYCHIC, MOVE_MORNINGSUN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 70,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_TAILWIND, MOVE_UTURN, MOVE_CROSSPOISON, MOVE_HAZE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 70,
        .species = SPECIES_RIBOMBEE,
        .moves = { MOVE_AROMATHERAPY, MOVE_TAILWIND, MOVE_BUGBUZZ, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Sweet Veil
    },
    {
        .lvl = 70,
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_HEALINGWISH, MOVE_HIGHJUMPKICK, MOVE_PLAYROUGH, MOVE_UTURN },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 72,
        .species = SPECIES_FLORGES_YELLOW,
        .moves = { MOVE_WISH, MOVE_SAFEGUARD, MOVE_MOONBLAST, MOVE_ENERGYBALL },
        .heldItem = ITEM_KEBIA_BERRY,
        .ability = Ability_1 // Flower Veil
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_MIMIKYU,
        .moves = { MOVE_TRICKROOM, MOVE_WILLOWISP, MOVE_SHADOWCLAW, MOVE_PAINSPLIT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Disguise
    },
    {
        .lvl = 70,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_PSYCHIC, MOVE_SCALD, MOVE_YAWN, MOVE_SLACKOFF },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 70,
        .species = SPECIES_RUNERIGUS,
        .moves = { MOVE_SHADOWCLAW, MOVE_POWERSPLIT, MOVE_EARTHQUAKE, MOVE_DESTINYBOND },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 70,
        .species = SPECIES_DUSCLOPS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_TRICKROOM, MOVE_PAINSPLIT },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 72,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYSHOCK, MOVE_CALMMIND, MOVE_TRICKROOM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_PERISHSONG, MOVE_ICEBEAM, MOVE_BRINE, MOVE_BODYSLAM },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 70,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND, MOVE_ENCORE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 70,
        .species = SPECIES_CURSOLA,
        .moves = { MOVE_PERISHSONG, MOVE_STRENGTHSAP, MOVE_MIRRORCOAT, MOVE_SPITE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Perish Body
    },
    {
        .lvl = 70,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_MEANLOOK, MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_DESTINYBOND },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 72,
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_PERISHSONG, MOVE_MEANLOOK, MOVE_MYSTICALFIRE, MOVE_SHADOWBALL },
        .heldItem = ITEM_COLBUR_BERRY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Chance_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_PRIMEAPE,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 70,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 70,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 70,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 72,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_METRONOME, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Super Luck
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_BEHEEYEM,
        .moves = { MOVE_COSMICPOWER, MOVE_STOREDPOWER, MOVE_RECOVER, MOVE_THUNDERBOLT },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 70,
        .species = SPECIES_SHUCKLE,
        .moves = { MOVE_ACUPRESSURE, MOVE_REST, MOVE_ROCKSLIDE, MOVE_WRAP },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Sturdy
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
        .species = SPECIES_FALINKS,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_NORETREAT, MOVE_CLOSECOMBAT, MOVE_MEGAHORN },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 72,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_CLANGOROUSSOUL, MOVE_NOBLEROAR, MOVE_CLOSECOMBAT, MOVE_BOOMBURST },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_BATONPASS, MOVE_ACIDARMOR, MOVE_AQUARING, MOVE_MUDDYWATER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_NINJASK,
        .moves = { MOVE_BATONPASS, MOVE_PROTECT, MOVE_SWORDSDANCE, MOVE_XSCISSOR },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Speed Boost
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
        .species = SPECIES_THIEVUL,
        .moves = { MOVE_BATONPASS, MOVE_SUBSTITUTE, MOVE_NASTYPLOT, MOVE_SHADOWBALL },
        .heldItem = ITEM_GHOST_GEM,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 72,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_BATONPASS, MOVE_FLING, MOVE_SWORDSDANCE, MOVE_ICICLECRASH },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Casey_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_BEHEEYEM,
        .moves = { MOVE_PSYCHUP, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_THUNDERBOLT },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 70,
        .species = SPECIES_MIENSHAO,
        .moves = { MOVE_PSYCHUP, MOVE_HIGHJUMPKICK, MOVE_BOUNCE, MOVE_FAKEOUT },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 70,
        .species = SPECIES_STONJOURNER,
        .moves = { MOVE_PSYCHUP, MOVE_STONEEDGE, MOVE_ROCKPOLISH, MOVE_BODYSLAM },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Power Spot
    },
    {
        .lvl = 70,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_PSYCHUP, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_WISH },
        .heldItem = ITEM_PSYCHIC_GEM,
        .ability = Ability_2 // Trace
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
        .species = SPECIES_BIBAREL,
        .moves = { MOVE_AMNESIA, MOVE_SWORDSDANCE, MOVE_AQUAJET, MOVE_CRUNCH },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 70,
        .species = SPECIES_GLALIE,
        .moves = { MOVE_PROTECT, MOVE_ICEFANG, MOVE_HEADBUTT, MOVE_SUBSTITUTE },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 70,
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_ROOST, MOVE_DRILLPECK, MOVE_SPIKES, MOVE_IRONDEFENSE },
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
        .species = SPECIES_KINGDRA,
        .moves = { MOVE_FOCUSENERGY, MOVE_DRAGONPULSE, MOVE_SCALD, MOVE_AGILITY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Sniper
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_JELLICENT_F,
        .moves = { MOVE_WHIRLPOOL, MOVE_DESTINYBOND, MOVE_SHADOWBALL, MOVE_RECOVER },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 70,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_DRILLRUN, MOVE_SWORDSDANCE, MOVE_RAPIDSPIN, MOVE_CRUSHCLAW },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 70,
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SHELLTRAP, MOVE_OVERHEAT, MOVE_BODYSLAM, MOVE_EXPLOSION },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 70,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_SHADOWCLAW, MOVE_DISABLE },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 72,
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_STRANGESTEAM, MOVE_SLUDGEBOMB, MOVE_EXPLOSION, MOVE_MEMENTO },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Neutralizing Gas
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_GOGOAT,
        .moves = { MOVE_SEEDBOMB, MOVE_MILKDRINK, MOVE_AERIALACE, MOVE_EARTHQUAKE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Sap Sipper
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
        .species = SPECIES_CRADILY,
        .moves = { MOVE_GIGADRAIN, MOVE_ANCIENTPOWER, MOVE_STOCKPILE, MOVE_LEECHSEED },
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
        .species = SPECIES_RAICHU,
        .moves = { MOVE_NASTYPLOT, MOVE_THUNDERBOLT, MOVE_NUZZLE, MOVE_IRONTAIL },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_LEECHSEED, MOVE_CLEARSMOG, MOVE_GROWTH, MOVE_GIGADRAIN },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Effect Spore
    },
    {
        .lvl = 70,
        .species = SPECIES_COMFEY,
        .moves = { MOVE_PLAYROUGH, MOVE_SWEETKISS, MOVE_PETALBLIZZARD, MOVE_CHARM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Natural Cure
    },
    {
        .lvl = 70,
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_BOUNCE, MOVE_HIGHJUMPKICK, MOVE_HEADBUTT, MOVE_QUICKATTACK },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 70,
        .species = SPECIES_FROSLASS,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_ICYWIND, MOVE_CRUNCH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 72,
        .species = SPECIES_GLALIE,
        .moves = { MOVE_PROTECT, MOVE_HAIL, MOVE_FREEZEDRY, MOVE_CRUNCH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Abby_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_BRELOOM,
        .moves = { MOVE_MACHPUNCH, MOVE_SPORE, MOVE_SEEDBOMB, MOVE_HEADBUTT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Poison Heal
    },
    {
        .lvl = 70,
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_THROATCHOP, MOVE_MEGAHORN, MOVE_CLOSECOMBAT, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 70,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_ELECTROBALL, MOVE_AGILITY, MOVE_SANDATTACK, MOVE_SHADOWBALL },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 70,
        .species = SPECIES_TREVENANT,
        .moves = { MOVE_WILLOWISP, MOVE_HORNLEECH, MOVE_HEX, MOVE_LEECHSEED },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 72,
        .species = SPECIES_BARBARACLE,
        .moves = { MOVE_FLING, MOVE_ROCKPOLISH, MOVE_RAZORSHELL, MOVE_CROSSCHOP },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_1_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_GASTRODON,
        .moves = { MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_MUDDYWATER, MOVE_ICYWIND },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_1 // Sticky Hold
    },
    {
        .lvl = 70,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_WATERFALL, MOVE_BULLDOZE, MOVE_IRONHEAD, MOVE_DRAGONDANCE },
        .heldItem = ITEM_CELL_BATTERY,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_STEALTHROCK, MOVE_ROCKSLIDE, MOVE_HIGHHORSEPOWER },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 70,
        .species = SPECIES_AURORUS,
        .moves = { MOVE_HYPERBEAM, MOVE_FREEZEDRY, MOVE_THUNDERWAVE, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Refrigerate
    },
    {
        .lvl = 72,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_ROOST, MOVE_EXTREMESPEED, MOVE_OUTRAGE, MOVE_AQUATAIL },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Multiscale
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_DHELMISE,
        .moves = { MOVE_SWITCHEROO, MOVE_POWERWHIP, MOVE_ANCHORSHOT, MOVE_FACADE },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Steelworker
    },
    {
        .lvl = 70,
        .species = SPECIES_TREVENANT,
        .moves = { MOVE_REST, MOVE_HEX, MOVE_WILLOWISP, MOVE_WOODHAMMER },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 70,
        .species = SPECIES_BARBARACLE,
        .moves = { MOVE_THIEF, MOVE_FLING, MOVE_RAZORSHELL, MOVE_ROCKSLIDE },
        .heldItem = ITEM_RAZOR_CLAW,
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 70,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SLACKOFF, MOVE_RECYCLE, MOVE_FUTURESIGHT, MOVE_SURF },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 72,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_TRICK, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM, MOVE_PSYCHIC },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_EMBARGO, MOVE_SANDSTORM, MOVE_EARTHQUAKE, MOVE_CRUNCH },
        .heldItem = ITEM_BLACK_GLASSES,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_CENTISKORCH,
        .moves = { MOVE_BUGBITE, MOVE_COIL, MOVE_FIRELASH, MOVE_LUNGE },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flash Fire
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
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_KNOCKOFF, MOVE_SLUDGEBOMB, MOVE_BELCH, MOVE_DRAINPUNCH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Anticipation
    },
    {
        .lvl = 72,
        .species = SPECIES_ZOROARK,
        .moves = { MOVE_EMBARGO, MOVE_KNOCKOFF, MOVE_UTURN, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Illusion
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_Iris_4_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_BARBARACLE,
        .moves = { MOVE_SWITCHEROO, MOVE_SHELLSMASH, MOVE_BRICKBREAK, MOVE_DRAGONCLAW },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_2 // Sniper
    },
    {
        .lvl = 70,
        .species = SPECIES_JELLICENT_F,
        .moves = { MOVE_TRICK, MOVE_SHADOWBALL, MOVE_BRINE, MOVE_WILLOWISP },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Water Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_TRICK, MOVE_PSYCHIC, MOVE_HEX, MOVE_FUTURESIGHT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 70,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_TRICK, MOVE_WILLOWISP, MOVE_HEX, MOVE_FUTURESIGHT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_Hidden // Frisk
    },
    {
        .lvl = 72,
        .species = SPECIES_MALAMAR,
        .moves = { MOVE_SWITCHEROO, MOVE_SUPERPOWER, MOVE_NIGHTSLASH, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_STICKY_BARB,
        .ability = Ability_1 // Contrary
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
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_EARTHQUAKE, MOVE_THUNDERFANG, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_TAILWIND, MOVE_ROOST, MOVE_ACROBATICS, MOVE_FLAREBLITZ },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 70,
        .species = SPECIES_CACTURNE,
        .moves = { MOVE_SPIKES, MOVE_SUCKERPUNCH, MOVE_SPIKYSHIELD, MOVE_DRAINPUNCH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 72,
        .species = SPECIES_LANTURN,
        .moves = { MOVE_SURF, MOVE_CHARGEBEAM, MOVE_BLIZZARD, MOVE_CHARGE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_2_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_MIENSHAO,
        .moves = { MOVE_FAKEOUT, MOVE_QUICKGUARD, MOVE_UTURN, MOVE_DRAINPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 70,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_HELPINGHAND, MOVE_CHARM, MOVE_SNARL, MOVE_COPYCAT },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 70,
        .species = SPECIES_CARBINK,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_ROCKSLIDE, MOVE_SANDTOMB },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 70,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_FOLLOWME, MOVE_ROOST, MOVE_AIRSLASH, MOVE_LIFEDEW },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 72,
        .species = SPECIES_GALLADE,
        .moves = { MOVE_QUICKGUARD, MOVE_SACREDSWORD, MOVE_LIFEDEW, MOVE_WIDEGUARD },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonItemCustomMoves sParty_GymLeaderRematches_DennisAndDee_3_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_LIGHTSCREEN, MOVE_FIREPUNCH },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Plus
    },
    {
        .lvl = 70,
        .species = SPECIES_KLINKLANG,
        .moves = { MOVE_GEARUP, MOVE_SHIFTGEAR, MOVE_CHARGEBEAM, MOVE_METALSOUND },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Minus
    },
    {
        .lvl = 70,
        .species = SPECIES_LANTURN,
        .moves = { MOVE_HYDROPUMP, MOVE_THUNDERBOLT, MOVE_CURSE, MOVE_ICYWIND },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 70,
        .species = SPECIES_WEEZING,
        .moves = { MOVE_EXPLOSION, MOVE_HEATWAVE, MOVE_SLUDGEBOMB, MOVE_WILLOWISP },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Neutralizing Gas
    },
    {
        .lvl = 72,
        .species = SPECIES_SLAKING,
        .moves = { MOVE_THROATCHOP, MOVE_XSCISSOR, MOVE_ICEPUNCH, MOVE_GIGAIMPACT },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Truant
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
        .species = SPECIES_CROBAT,
        .moves = { MOVE_HEATWAVE, MOVE_AIRSLASH, MOVE_MEANLOOK, MOVE_ROUND },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 70,
        .species = SPECIES_FLYGON,
        .moves = { MOVE_BULLDOZE, MOVE_EARTHQUAKE, MOVE_BOOMBURST, MOVE_UTURN },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Levitate
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
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_CLEARSMOG, MOVE_SPORE, MOVE_SYNTHESIS, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 72,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_BELLYDRUM, MOVE_DRAGONCLAW, MOVE_POISONJAB, MOVE_CLOSECOMBAT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 72,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWPUNCH, MOVE_BRICKBREAK, MOVE_LEECHLIFE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 73,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_ROCKSLIDE, MOVE_IRONHEAD },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 74,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_ICEFANG, MOVE_CRUNCH },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion
// #region Elite Four Rematches
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_HannahRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_WHIMSICOTT,
        .moves = { MOVE_LEECHSEED, MOVE_SUBSTITUTE, MOVE_COTTONGUARD, MOVE_GIGADRAIN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 72,
        .species = SPECIES_GASTRODON_EAST,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_SLUDGEWAVE },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 72,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_ROOST, MOVE_TAILWIND, MOVE_FLAREBLITZ, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 72,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE, MOVE_TRICK },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 73,
        .species = SPECIES_MAWILE,
        .moves = { MOVE_IRONHEAD, MOVE_PLAYROUGH, MOVE_ICEPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_MAWILITE,
        .ability = Ability_2 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_LucasRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_SPIKES, MOVE_POWERWHIP, MOVE_GYROBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 72,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 72,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AIRSLASH, MOVE_ROOST, MOVE_THUNDERWAVE, MOVE_AURASPHERE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 72,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_NOBLEROAR, MOVE_ICEPUNCH, MOVE_CLOSECOMBAT, MOVE_OUTRAGE },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 73,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_JennaRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_TOXICSPIKES, MOVE_BANEFULBUNKER, MOVE_LIQUIDATION, MOVE_RECOVER },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 72,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_NIGHTSLASH, MOVE_IRONHEAD, MOVE_SWORDSDANCE, MOVE_PSYCHOCUT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 72,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 72,
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_ICESHARD, MOVE_EARTHQUAKE, MOVE_ICICLECRASH, MOVE_STONEEDGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 73,
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_FAKEOUT, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_FACADE },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_Hidden // Inner Focus
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_ThomasRematch_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_LEECHSEED, MOVE_SLUDGEBOMB, MOVE_SYNTHESIS, MOVE_GIGADRAIN },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 72,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_STONEEDGE, MOVE_OUTRAGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Intimidate
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
        .species = SPECIES_ROTOM_WASH,
        .moves = { MOVE_REST, MOVE_WILLOWISP, MOVE_VOLTSWITCH, MOVE_HYDROPUMP },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 73,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SLACKOFF, MOVE_CALMMIND, MOVE_PSYSHOCK, MOVE_SCALD },
        .heldItem = ITEM_SLOWBRONITE,
        .ability = Ability_1 // Oblivious
    }
};
// #endregion
// #region Title Defense
const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 74,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 75,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 73,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_SUCKERPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 74,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_RATTATA,
        .moves = { MOVE_SUPERFANG, MOVE_SUCKERPUNCH, MOVE_FACADE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 73,
        .species = SPECIES_RATTATA_A,
        .moves = { MOVE_PURSUIT, MOVE_CRUNCH, MOVE_SUPERFANG, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Gluttony
    },
    {
        .lvl = 73,
        .species = SPECIES_RATTATA,
        .moves = { MOVE_QUICKATTACK, MOVE_LASTRESORT, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_Hidden // Hustle
    },
    {
        .lvl = 73,
        .species = SPECIES_RATTATA_A,
        .moves = { MOVE_TOXIC, MOVE_UTURN, MOVE_WILDCHARGE, MOVE_SHADOWBALL },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 74,
        .species = SPECIES_RATICATE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_QUICKATTACK, MOVE_CRUNCH, MOVE_PLUCK },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 75,
        .species = SPECIES_RATICATE_A,
        .moves = { MOVE_SUCKERPUNCH, MOVE_UTURN, MOVE_WILDCHARGE, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Hustle
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_WithVictini_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_BRAVEBIRD, MOVE_SPIKES, MOVE_IRONHEAD, MOVE_ROOST },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 73,
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_TOXICSPIKES, MOVE_LEECHSEED, MOVE_GIGADRAIN, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Poison Point
    },
    {
        .lvl = 73,
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_HIGHJUMPKICK, MOVE_FAKEOUT, MOVE_RETURN, MOVE_ICEPUNCH },
        .heldItem = ITEM_LOPUNNITE,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 73,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYSHOCK, MOVE_WISH, MOVE_PROTECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Pixelate
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
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_POWERWHIP, MOVE_GYROBALL, MOVE_LEECHSEED, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 73,
        .species = SPECIES_NIDOKING,
        .moves = { MOVE_EARTHPOWER, MOVE_SLUDGEWAVE, MOVE_THUNDERBOLT, MOVE_SHADOWBALL },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 73,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYSHOCK, MOVE_CALMMIND, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GARDEVOIRITE,
        .ability = Ability_2 // Trace
    },
    {
        .lvl = 73,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_BUGBUZZ, MOVE_QUIVERDANCE, MOVE_HURRICANE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 74,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_DRAGONDANCE, MOVE_FIREPUNCH, MOVE_DRAGONCLAW, MOVE_ROOST },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Multiscale
    },
    {
        .lvl = 75,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_ICEBEAM, MOVE_SCALD, MOVE_DARKPULSE, MOVE_HIDDENPOWER },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Battle Bond
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Alistair_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_CROSSPOISON, MOVE_HAZE },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 73,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_SPORE, MOVE_TOXIC, MOVE_BODYSLAM, MOVE_PROTECT },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 73,
        .species = SPECIES_GALLADE,
        .moves = { MOVE_CLOSECOMBAT, MOVE_LEAFBLADE, MOVE_PSYCHOCUT, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Justified
    },
    {
        .lvl = 73,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 74,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_DESTINYBOND, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
    },
    {
        .lvl = 75,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Hawthorne_Divergent[] = {
    {
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
        .species = SPECIES_THIEVUL,
        .moves = { MOVE_PARTINGSHOT, MOVE_SUCKERPUNCH, MOVE_KNOCKOFF, MOVE_PLAYROUGH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 73,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_ENCORE, MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 73,
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_SLUDGEBOMB, MOVE_DRAINPUNCH, MOVE_TOXIC, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_PAYAPA_BERRY,
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 73,
        .species = SPECIES_CARNIVINE,
        .moves = { MOVE_CRUNCH, MOVE_SEEDBOMB, MOVE_STOCKPILE, MOVE_INGRAIN },
        .heldItem = ITEM_BIG_ROOT,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 74,
        .species = SPECIES_COPPERAJAH,
        .moves = { MOVE_PLAYROUGH, MOVE_IRONHEAD, MOVE_HEAVYSLAM, MOVE_IRONDEFENSE },
        .heldItem = ITEM_COPPERITE,
        .ability = Ability_1 // Sheer Force
    },
    {
        .lvl = 75,
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_HEATWAVE, MOVE_SLUDGEBOMB, MOVE_EXPLOSION, MOVE_STRANGESTEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Neutralizing Gas
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ena_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_PAINSPLIT, MOVE_WILLOWISP, MOVE_SHADOWSNEAK, MOVE_FUTURESIGHT },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 73,
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_IRONHEAD, MOVE_FACADE, MOVE_ROCKTOMB, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Soundproof
    },
    {
        .lvl = 73,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_CROSSPOISON, MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_MEANLOOK },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 73,
        .species = SPECIES_PYROAR,
        .moves = { MOVE_OVERHEAT, MOVE_HYPERVOICE, MOVE_CRUNCH, MOVE_WILDCHARGE },
        .heldItem = ITEM_FIRE_GEM,
        .ability = Ability_1 // Rivalry
    },
    {
        .lvl = 74,
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_PERISHSONG, MOVE_ICEBEAM, MOVE_DRAGONPULSE, MOVE_SCALD },
        .heldItem = ITEM_LAPRASITE,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 75,
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_PROTECT, MOVE_MEGAHORN, MOVE_TOXIC, MOVE_VENOSHOCK },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Speed Boost
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
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_THUNDERWAVE, MOVE_REFLECT, MOVE_SPIKES, MOVE_PLAYROUGH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_DRAGONHAMMER, MOVE_PSYSHOCK, MOVE_CURSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 73,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_FLAMETHROWER, MOVE_ENERGYBALL },
        .heldItem = ITEM_CHARCOAL,
        .ability = Ability_1 // Flash Fire
    },
    {
        .lvl = 73,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_TRIATTACK, MOVE_THUNDERBOLT, MOVE_PSYSHOCK, MOVE_BLIZZARD },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 74,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_STONEEDGE, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 75,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_ICEBEAM, MOVE_DRAGONBREATH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Collin_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_CACTURNE,
        .moves = { MOVE_SPIKYSHIELD, MOVE_DRAINPUNCH, MOVE_NEEDLEARM, MOVE_FEINTATTACK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Sand Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_CENTISKORCH,
        .moves = { MOVE_FIRELASH, MOVE_LUNGE, MOVE_COIL, MOVE_CRUNCH },
        .heldItem = ITEM_CENTISKORITE,
        .ability = Ability_1 // Flash Fire
    },
    {
        .lvl = 73,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_DISCHARGE, MOVE_BLIZZARD, MOVE_DOUBLETEAM, MOVE_OMINOUSWIND },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 73,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_SMARTSTRIKE, MOVE_SLASH, MOVE_EARTHQUAKE, MOVE_ROCKSLIDE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Sand Force
    },
    {
        .lvl = 74,
        .species = SPECIES_EMPOLEON,
        .moves = { MOVE_AQUAJET, MOVE_ICEBEAM, MOVE_WATERPLEDGE, MOVE_FLASHCANNON },
        .heldItem = ITEM_MYSTIC_WATER,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 75,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_SWORDSDANCE, MOVE_METEORASSAULT, MOVE_KNOCKOFF, MOVE_FURYCUTTER },
        .heldItem = ITEM_LEEK, // Stick, in game
        .ability = Ability_1 // Steadfast
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Crystal_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_GALVANTULA,
        .moves = { MOVE_GASTROACID, MOVE_SUCKERPUNCH, MOVE_DISCHARGE, MOVE_SIGNALBEAM },
        .heldItem = ITEM_SILVER_POWDER,
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 73,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_ENCORE, MOVE_EXTRASENSORY, MOVE_AURASPHERE, MOVE_YAWN },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 73,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_DRAGONRUSH, MOVE_CRUNCH, MOVE_DRAGONCLAW, MOVE_EARTHQUAKE },
        .heldItem = ITEM_DRAGON_FANG,
        .ability = Ability_1 // Sand Veil
    },
    {
        .lvl = 73,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_DRAGONDANCE, MOVE_DRAGONTAIL, MOVE_ROOST, MOVE_AQUATAIL },
        .heldItem = ITEM_MYSTIC_WATER,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 74,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_MAGICALLEAF, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_CALMMIND },
        .heldItem = ITEM_SAFETY_GOGGLES,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 75,
        .species = SPECIES_BLAZIKEN,
        .moves = { MOVE_BRICKBREAK, MOVE_AERIALACE, MOVE_BLAZEKICK, MOVE_FLAREBLITZ },
        .heldItem = ITEM_BLAZIKENITE,
        .ability = Ability_1 // Blaze
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Irene_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_NOCTOWL,
        .moves = { MOVE_EXTRASENSORY, MOVE_MOONBLAST, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_FAIRY_GEM,
        .ability = Ability_Hidden // Tinted Lens
    },
    {
        .lvl = 73,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_MINIMIZE, MOVE_KNOCKOFF, MOVE_TOXIC, MOVE_POISONJAB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 73,
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_MYSTICALFIRE, MOVE_POWERGEM, MOVE_NASTYPLOT, MOVE_SHADOWBALL },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 73,
        .species = SPECIES_KINGDRA,
        .moves = { MOVE_DRAGONPULSE, MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_FLASHCANNON },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Sniper
    },
    {
        .lvl = 74,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_THUNDERWAVE },
        .heldItem = ITEM_HATTERITE,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 75,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_FLAMETHROWER, MOVE_DRAGONPULSE, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Corrosion
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ronald_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_SANDSTORM, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 73,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_CURSE, MOVE_GYROBALL, MOVE_EXPLOSION },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 73,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_EXTREMESPEED, MOVE_SWORDSDANCE, MOVE_METEORMASH, MOVE_CLOSECOMBAT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 73,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_SCREECH, MOVE_NIGHTSLASH, MOVE_ICESHARD, MOVE_ICICLECRASH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 74,
        .species = SPECIES_GLALIE,
        .moves = { MOVE_CRUNCH, MOVE_BODYSLAM, MOVE_FREEZEDRY, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_GLALITITE,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 75,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_POISONJAB, MOVE_DRAINPUNCH, MOVE_CRUNCH, MOVE_POWERUPPUNCH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Shed Skin
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Kurtis_Divergent[] = {
    {
        .lvl = 73,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_CLEARSMOG, MOVE_SPORE, MOVE_SYNTHESIS, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 73,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_BELLYDRUM, MOVE_DRAGONCLAW, MOVE_POISONJAB, MOVE_DRAINPUNCH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 73,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWPUNCH, MOVE_BRICKBREAK, MOVE_LEECHLIFE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 73,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 74,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_ROCKSLIDE, MOVE_IRONHEAD },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 75,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_ICEFANG, MOVE_CRUNCH },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion
// #region Heleo City (Postgame)
const struct TrainerMonNoItemCustomMoves sParty_HeleoCity_NurseBrianne_Divergent[] = {
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 1,
        .species = SPECIES_BLISSEY,
        .moves = { MOVE_POUND, MOVE_SING, MOVE_HEALPULSE, MOVE_LIGHTSCREEN },
        .ability = Ability_1 // Natural Cure
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
        .partyFlags = 0,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_FIRST_BATTLE,
        .partySize = NELEMS(sParty_Rival1_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Rival1_Divergent}
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
        .party = {.ItemDefaultMoves = sParty_RubarrDesert_BlackbeltKobiyashi_Divergent}
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
        .party = {.ItemDefaultMoves = sParty_Route4_Lady_Alda_Divergent}
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
        .party = {.ItemDefaultMoves = sParty_Route4_Crush_Girl_Elise_Divergent}
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
        .party = {.ItemDefaultMoves = sParty_Route5_LadyFaith_Divergent}
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
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
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
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
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
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
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
        .partyFlags = 0,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_I, _s, _o, _b, _e, _l, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_Route11North_PainterIsobel_Divergent),
        .party = {.NoItemDefaultMoves = sParty_Route11North_PainterIsobel_Divergent}
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
        .partyFlags = 0,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_S, _h, _e, _e, _n, _a, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_PeradonForest_PainterSheena_Divergent),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_PainterSheena_Divergent}
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
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
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
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
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
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Clarice_Divergent}
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
