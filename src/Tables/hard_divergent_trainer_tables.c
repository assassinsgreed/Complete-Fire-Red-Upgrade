#include "../defines_battle.h"
#include "../../include/battle.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/opponents.h"
#include "../../include/constants/battle_ai.h"
#include "../../include/constants/items.h"
#include "../../include/easy_text.h"
#include "../../include/new/build_pokemon_2.h"

// NOTE: The trainers here are overrides loaded only when BOTH FLAG_HARD_MODE and
// FLAG_DIVERGENT_WILD_ENCOUNTERS are set. This is the highest-priority set. If a trainer is not present
// here, the lookup falls back (in order) to the Divergent set (divergent_trainer_tables.c), then the
// Hard set (hard_trainer_tables.c), then the standard trainer in trainer_tables.c. See GetTrainerData()
// in build_pokemon.c for the priority order, and battle.h for the list of struct types that can be used.
//
// These are a 1:1 copy of hard_trainer_tables.c with each party renamed with a _Divergent suffix (so the
// names read sParty_..._Hard_Divergent) so the teams can be edited independently. Everything else (name,
// class, items, AI flags, etc.) is unchanged.

#define TrainerAIFlags_HardBaseline             (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SEMI_SMART)
#define TrainerAIFlags_Developer_Hard           (TrainerAIFlags_HardBaseline)
#define TrainerAIFlags_GymTrainees_Hard         (TrainerAIFlags_HardBaseline)
#define TrainerAIFlags_AscensionTower_Hard      (TrainerAIFlags_HardBaseline | AI_SCRIPT_HP_AWARE | AI_SCRIPT_TRY_TO_FAINT)

#define NO_NAME                                                                                      \
    {                                                                                                \
        _END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE \
    }

// #region Trainer Structs

// #region Important trainers
const struct TrainerMonItemCustomMoves sParty_Rival2_Hard_Divergent[] = {
    {
        .lvl = 12,
        .species = SPECIES_MILCERY,
        .moves = { MOVE_SWEETSCENT, MOVE_TACKLE, MOVE_AROMATICMIST, MOVE_SWEETKISS },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 13,
        .species = SPECIES_PIDGEY,
        .moves = { MOVE_GUST, MOVE_TACKLE, MOVE_QUICKATTACK, MOVE_GROWL },
        .heldItem = ITEM_SILK_SCARF,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 14,
        .species = SPECIES_EEVEE,
        .moves = { MOVE_QUICKATTACK, MOVE_TICKLE, MOVE_SANDATTACK, MOVE_YAWN },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_2 // Adaptability
    },
};

const struct TrainerMonItemCustomMoves sParty_PartnerRival1_Hard_Divergent[] = {
    {
        .lvl = 13,
        .species = SPECIES_MILCERY,
        .moves = { MOVE_SWEETSCENT, MOVE_TACKLE, MOVE_AROMATICMIST, MOVE_SWEETKISS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 14,
        .species = SPECIES_PIDGEY,
        .moves = { MOVE_GUST, MOVE_TACKLE, MOVE_QUICKATTACK, MOVE_GROWL },
        .heldItem = ITEM_SILK_SCARF,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 15,
        .species = SPECIES_EEVEE,
        .moves = { MOVE_QUICKATTACK, MOVE_TICKLE, MOVE_SANDATTACK, MOVE_YAWN },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_2 // Adaptability
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival3_Hard_Divergent[] = {
    {
        .lvl = 30,
        .species = SPECIES_MILCERY,
        .moves = { MOVE_ACIDARMOR, MOVE_DRAININGKISS, MOVE_ATTRACT, MOVE_AROMATHERAPY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 30,
        .species = SPECIES_CUBONE_A,
        .moves = { MOVE_HEADBUTT, MOVE_DETECT, MOVE_BULLDOZE, MOVE_BRUTALSWING },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 30,
        .species = SPECIES_PIDGEOTTO,
        .moves = { MOVE_FEATHERDANCE, MOVE_TWISTER, MOVE_GUST, MOVE_WHIRLWIND },
        .heldItem = ITEM_SHARP_BEAK,
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

const struct TrainerMonItemCustomMoves sParty_Casey1_Hard_Divergent[] = {
    {
        .lvl = 15,
        .species = SPECIES_MUNNA,
        .moves = { MOVE_PSYBEAM, MOVE_DEFENSECURL, MOVE_STOREDPOWER, MOVE_HYPNOSIS},
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 16,
        .species = SPECIES_PANCHAM,
        .moves = { MOVE_TACKLE, MOVE_TAUNT, MOVE_BRICKBREAK, MOVE_LEER },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 17,
        .species = SPECIES_MURKROW,
        .moves = { MOVE_GUST, MOVE_HAZE, MOVE_CALMMIND, MOVE_WINGATTACK },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_2 // Super Luck
    }
};

const struct TrainerMonItemCustomMoves sParty_Casey2_Hard_Divergent[] = {
    {
        .lvl = 33,
        .species = SPECIES_MUSHARNA,
        .moves = { MOVE_CALMMIND, MOVE_MOONBLAST, MOVE_STOREDPOWER, MOVE_MOONLIGHT},
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 34,
        .species = SPECIES_PANGORO,
        .moves = { MOVE_NIGHTSLASH, MOVE_BULLETPUNCH, MOVE_PARTINGSHOT, MOVE_BULKUP},
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 35,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_TAILWIND, MOVE_NASTYPLOT, MOVE_DARKPULSE, MOVE_PSYCHIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_WATERPULSE, MOVE_AURORABEAM, MOVE_CHARM, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Jolteon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERWAVE, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_DOUBLEKICK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Flareon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FIREFANG, MOVE_BITE, MOVE_SUNNYDAY, MOVE_WILLOWISP },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Espeon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_PSYCHIC, MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Umbreon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_SNARL, MOVE_MOONLIGHT, MOVE_TOXIC, MOVE_DIG },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Leafeon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_LEECHSEED, MOVE_RAZORLEAF, MOVE_AERIALACE, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Glaceon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_HAIL, MOVE_AURORAVEIL, MOVE_ICEFANG, MOVE_ROCKSMASH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Sylveon_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_ATTRACT, MOVE_ACIDARMOR },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 37,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_TWISTER, MOVE_AIRSLASH, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 38,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_DRAININGKISS, MOVE_COVET, MOVE_LIGHTSCREEN, MOVE_ATTRACT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_MUDDYWATER, MOVE_RAINDANCE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Jolteon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_RAINDANCE, MOVE_WEATHERBALL, MOVE_SHADOWBALL },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Flareon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_WILLOWISP, MOVE_DIG, MOVE_FLAREBLITZ, MOVE_SUNNYDAY },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Espeon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_MORNINGSUN, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Umbreon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_CURSE, MOVE_MOONLIGHT, MOVE_TOXIC, MOVE_DARKPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Leafeon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_LEECHSEED },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Glaceon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_BLIZZARD, MOVE_HAIL, MOVE_AURORAVEIL, MOVE_MUDSHOT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Sylveon_Hard_Divergent[] = {
    {
        .lvl = 45,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 44,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 44,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 45,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 46,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_MOONBLAST, MOVE_WISH, MOVE_TOXIC, MOVE_PROTECT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival_EmraldinQuayEvent_Hard_Divergent[] = {
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
        .lvl = 53,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_SLUDGEBOMB, MOVE_POWERWHIP },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 53,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_WOODHAMMER, MOVE_LEECHSEED },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 54,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 55,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_POISONJAB, MOVE_LUNGE, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Rival_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 55,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 55,
        .species = SPECIES_ZWEILOUS,
        .moves = { MOVE_CRUNCH, MOVE_BODYSLAM, MOVE_FIREFANG, MOVE_DOUBLEHIT },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Hustle
    },
    {
        .lvl = 56,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 57,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_PartnerRival_Hard_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 56,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 57,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Alistair_Hard_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 55,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 57,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 58,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_ROCKSLIDE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    }
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_SCALD, MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_FLIPTURN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Jolteon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_THUNDERBOLT, MOVE_VOLTSWITCH, MOVE_SHADOWBALL, MOVE_METALSOUND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Flareon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_BODYSLAM, MOVE_DIG, MOVE_LASTRESORT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Flash Fire
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Espeon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Umbreon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_SNARL, MOVE_TOXIC, MOVE_MEANLOOK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Leafeon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_SYNTHESIS, MOVE_AERIALACE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Glaceon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_FREEZEDRY, MOVE_HAIL, MOVE_AURORAVEIL, MOVE_SHADOWBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Sylveon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 66,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 66,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 67,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 67,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 68,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_MOONBLAST, MOVE_WISH, MOVE_PSYSHOCK, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_ExhibitionBattle_SecondaryTeam_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_FLASHCANNON, MOVE_DISCHARGE, MOVE_MAGNETRISE, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 66,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BRINE, MOVE_REVERSAL, MOVE_THUNDERPUNCH, MOVE_CURSE },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 66,
        .species = SPECIES_SEISMITOAD,
        .moves = { MOVE_DRAINPUNCH, MOVE_SCALD, MOVE_SLUDGEBOMB, MOVE_POWERWHIP },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 67,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_WOODHAMMER, MOVE_LEECHSEED },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 67,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_FLAMETHROWER, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 68,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_POISONJAB, MOVE_LUNGE, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_PostCredits_Alistair_Hard_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 72,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 72,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 72,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_STONEEDGE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 73,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Vaporeon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Jolteon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Flareon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Espeon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Umbreon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Leafeon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Glaceon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Sylveon_Hard_Divergent[] = {
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
        .moves = { MOVE_SHADOWBONE, MOVE_FIREPUNCH, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
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
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Hard_Divergent[] = {
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
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_WOODHAMMER, MOVE_LEECHSEED },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
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

// #region Rhodanzi City
const struct TrainerMonItemCustomMoves sParty_RhodanziCity_LeaderTerrence_Hard_Divergent[] = {
    {
        .lvl = 12,
        .species = SPECIES_GROOKEY,
        .moves = { MOVE_SCRATCH, MOVE_BRANCHPOKE, MOVE_FAKEOUT, MOVE_WORRYSEED },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 12,
        .species = SPECIES_PANPOUR,
        .moves = { MOVE_AQUARING, MOVE_WATERGUN, MOVE_LICK, MOVE_LEER },
        .heldItem = ITEM_PETAYA_BERRY,
        .ability = Ability_1 // Gluttony
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

// #region Rubarr Desert
const struct TrainerMonItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene_Hard_Divergent[] = {
    {
        .lvl = 14,
        .species = SPECIES_IMPIDIMP,
        .moves = { MOVE_FAKEOUT, MOVE_BITE, MOVE_FLATTER, MOVE_NONE },
        .heldItem = ITEM_BLACK_GLASSES,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 15,
        .species = SPECIES_TYNAMO,
        .moves = { MOVE_TACKLE, MOVE_THUNDERWAVE, MOVE_SPARK, MOVE_CHARGEBEAM },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 15,
        .species = SPECIES_GLIGAR,
        .moves = { MOVE_QUICKATTACK, MOVE_KNOCKOFF, MOVE_POISONSTING, MOVE_HARDEN },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_2 // Sand Veil
    },
    {
        .lvl = 16,
        .species = SPECIES_NUMEL,
        .moves = { MOVE_EMBER, MOVE_BULLDOZE, MOVE_FOCUSENERGY, MOVE_GROWL },
        .heldItem = ITEM_FIRE_GEM,
        .ability = Ability_1 // Oblivious
    },
};
// #endregion

// #region Ferrox Village
const struct TrainerMonItemCustomMoves sParty_FerroxGym_GymLeaderStella_Hard_Divergent[] = {
    {
        .lvl = 19,
        .species = SPECIES_SKORUPI,
        .moves = { MOVE_FELLSTINGER, MOVE_VENOSHOCK, MOVE_TOXIC, MOVE_BUGBITE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 20,
        .species = SPECIES_LAMPENT,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_CONFUSERAY, MOVE_EMBER },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 20,
        .species = SPECIES_AUDINO,
        .moves = { MOVE_ATTRACT, MOVE_THUNDERWAVE, MOVE_POWERUPPUNCH, MOVE_ICYWIND },
        .heldItem = ITEM_FOCUS_BAND,
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 21,
        .species = SPECIES_GLOOM,
        .moves = { MOVE_STUNSPORE, MOVE_SLEEPPOWDER, MOVE_GIGADRAIN, MOVE_POISONPOWDER },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_Hidden // Stench
    }
};
// #endregion

// #region Heleo City
const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine_Hard_Divergent[] = {
    {
        .lvl = 26,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_BUBBLEBEAM, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 25,
        .species = SPECIES_MAGNEMITE,
        .moves = { MOVE_THUNDER, MOVE_GYROBALL, MOVE_MAGNETRISE, MOVE_SUPERSONIC },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 26,
        .species = SPECIES_SEEL,
        .moves = { MOVE_WEATHERBALL, MOVE_CHARM, MOVE_RAINDANCE, MOVE_HEADBUTT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Hydration
    },
    {
        .lvl = 27,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_CONFUSION, MOVE_ATTRACT, MOVE_FAKETEARS },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_Hidden // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine2_Hard_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_BUBBLEBEAM, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 32,
        .species = SPECIES_MAGNETON,
        .moves = { MOVE_THUNDER, MOVE_GYROBALL, MOVE_MAGNETRISE, MOVE_SUPERSONIC },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 33,
        .species = SPECIES_SEEL,
        .moves = { MOVE_WEATHERBALL, MOVE_CHARM, MOVE_RAINDANCE, MOVE_HEADBUTT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Hydration
    },
    {
        .lvl = 34,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_PSYCHIC, MOVE_ATTRACT, MOVE_FAKETEARS },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_Hidden // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine3_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_POLITOED,
        .moves = { MOVE_BUBBLEBEAM, MOVE_HYPNOSIS, MOVE_RAINDANCE, MOVE_MUDSHOT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Drizzle
    },
    {
        .lvl = 40,
        .species = SPECIES_MAGNETON,
        .moves = { MOVE_THUNDER, MOVE_GYROBALL, MOVE_MAGNETRISE, MOVE_SUPERSONIC },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 41,
        .species = SPECIES_DEWGONG,
        .moves = { MOVE_WEATHERBALL, MOVE_CHARM, MOVE_RAINDANCE, MOVE_HEADBUTT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Hydration
    },
    {
        .lvl = 41,
        .species = SPECIES_ARMALDO,
        .moves = { MOVE_CRUSHCLAW, MOVE_ROCKBLAST, MOVE_AQUATAIL, MOVE_BRINE },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 42,
        .species = SPECIES_JYNX,
        .moves = { MOVE_ICEBEAM, MOVE_PSYCHIC, MOVE_ATTRACT, MOVE_FAKETEARS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Dry Skin
    }
};
// #endregion

// #region Daimyn City
const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance_Hard_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_THUNDERWAVE, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 32,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_SHOCKWAVE, MOVE_FIREFANG, MOVE_THUNDERWAVE },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 33,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_DARKVOID, MOVE_DREAMEATER, MOVE_TAILWIND, MOVE_PARTINGSHOT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Own Tempo
    },
    {
        .lvl = 34,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_RAZORSHELL, MOVE_SUCKERPUNCH, MOVE_SLASH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Emergency Exit
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance2_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_THUNDERWAVE, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 40,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_THUNDERBOLT, MOVE_FIREFANG, MOVE_THUNDERWAVE },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 41,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_DARKVOID, MOVE_DREAMEATER, MOVE_TAILWIND, MOVE_PARTINGSHOT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Own Tempo
    },
    {
        .lvl = 41,
        .species = SPECIES_INCINEROAR,
        .moves = { MOVE_PARTINGSHOT, MOVE_KNOCKOFF, MOVE_FAKEOUT, MOVE_FLAMETHROWER },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 42,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_RAZORSHELL, MOVE_SUCKERPUNCH, MOVE_DRILLRUN },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Emergency Exit
    }
};
// #endregion

// #region Route 11 South
const struct TrainerMonItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYBEAM, MOVE_THUNDERWAVE, MOVE_SHADOWBALL, MOVE_ICYWIND },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Download
    },
    {
        .lvl = 36,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_BRICKBREAK, MOVE_SUCKERPUNCH, MOVE_FAKEOUT },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 37,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 37,
        .species = SPECIES_GOLETT,
        .moves = { MOVE_NIGHTSHADE, MOVE_MEGAPUNCH, MOVE_IRONDEFENSE, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 39,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_ENDEAVOR },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Water Absorb
    }
};
// #endregion

// #region Laplaz Town
const struct TrainerMonItemCustomMoves sParty_LaplazTownGym_LeaderCasey_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_SMEARGLE,
        .moves = { MOVE_SPORE, MOVE_ACUPRESSURE, MOVE_SUBSTITUTE, MOVE_BATONPASS },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 40,
        .species = SPECIES_PANGORO,
        .moves = { MOVE_BULKUP, MOVE_DRAINPUNCH, MOVE_ICEPUNCH, MOVE_BODYSLAM },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 41,
        .species = SPECIES_MUSHARNA,
        .moves = { MOVE_CALMMIND, MOVE_STOREDPOWER, MOVE_PSYCHIC, MOVE_MOONBLAST },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 41,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_GIGADRAIN, MOVE_LEECHSEED, MOVE_POLLENPUFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 42,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NASTYPLOT, MOVE_DARKPULSE, MOVE_HEATWAVE, MOVE_AIRCUTTER },
        .heldItem = ITEM_SCOPE_LENS,
        .ability = Ability_2 // Super Luck
    }
};
// #endregion

// #region Scalding Spa
const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena_Hard_Divergent[] = {
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
        .lvl = 43,
        .species = SPECIES_SEALEO,
        .moves = { MOVE_BODYSLAM, MOVE_BLIZZARD, MOVE_ROLLOUT, MOVE_WATERPULSE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 43,
        .species = SPECIES_VANILLISH,
        .moves = { MOVE_ICEBEAM, MOVE_ACIDARMOR, MOVE_FLASHCANNON, MOVE_HAIL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Snow Cloak
    },
};
// #endregion

// #region Bruccie Village & Calicin Bay
const struct TrainerMonItemCustomMoves sParty_BruccieVillageGym_LeaderAbby_Hard_Divergent[] = {
    {
        .lvl = 46,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_ROLEPLAY, MOVE_PSYCHIC, MOVE_FOCUSBLAST, MOVE_RECOVER },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Magic Guard
    },
    {
        .lvl = 46,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_SUPERPOWER, MOVE_LEAFBLADE, MOVE_XSCISSOR, MOVE_SYNTHESIS },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 47,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_COIL, MOVE_WILDCHARGE, MOVE_CRUNCH, MOVE_FLAMETHROWER },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 47,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_IRONHEAD, MOVE_SLASH, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 48,
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_CALMMIND, MOVE_MOONBLAST, MOVE_MOONLIGHT, MOVE_FLAMETHROWER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Unaware
    }
};

const struct TrainerMonItemCustomMoves sParty_CalicinBay_TeamPlutoYolena_Hard_Divergent[] = {
    {
        .lvl = 46,
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_AURORAVEIL, MOVE_BLIZZARD, MOVE_RAZORLEAF, MOVE_INGRAIN },
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
        .species = SPECIES_WALREIN,
        .moves = { MOVE_BODYSLAM, MOVE_BLIZZARD, MOVE_ROLLOUT, MOVE_WATERPULSE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 47,
        .species = SPECIES_VANILLISH,
        .moves = { MOVE_ICEBEAM, MOVE_ACIDARMOR, MOVE_FLASHCANNON, MOVE_HAIL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Snow Cloak
    },
};
// #endregion

// #region Pluto HQ
const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Hard_Divergent[] = {
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
        .lvl = 49,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_PLAYROUGH, MOVE_THUNDERFANG, MOVE_FIREFANG, MOVE_OUTRAGE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 49,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_EARTHPOWER, MOVE_LAVAPLUME, MOVE_SUNNYDAY, MOVE_IRONHEAD },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 50,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SUBSTITUTE, MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_UTURN },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Hard_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYCHIC, MOVE_THUNDERWAVE, MOVE_SHADOWBALL, MOVE_ICEBEAM },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Download
    },
    {
        .lvl = 48,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_BRICKBREAK, MOVE_SUCKERPUNCH, MOVE_FAKEOUT },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 49,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 49,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_SHADOWPUNCH, MOVE_MEGAPUNCH, MOVE_HEAVYSLAM, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 50,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_DRAINPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Hard_Divergent[] = {
    {
        .lvl = 50,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_IRONHEAD, MOVE_SACREDSWORD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 50,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_HEAVYSLAM, MOVE_ROCKSLIDE, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 50,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 51,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_ROOST, MOVE_NASTYPLOT, MOVE_HEATWAVE, MOVE_SNARL },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 51,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_MUDDYWATER, MOVE_RECOVER, MOVE_DAZZLINGGLEAM, MOVE_BLIZZARD },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 52,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_DARKPULSE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    },
};
// #endregion

// #region Tsarvosa City
const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_StatsDojo_Kaito_Hard_Divergent[] = {
    {
        .lvl = 52,
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
        .lvl = 53,
        .species = SPECIES_DRAMPA,
        .moves = { MOVE_HYPERVOICE, MOVE_DRAGONPULSE, MOVE_LIGHTSCREEN, MOVE_GLARE },
        .ability = Ability_1 // Berserk
    },
    {
        .lvl = 53,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_DISCHARGE, MOVE_POWERGEM, MOVE_SANDSTORM, MOVE_EARTHPOWER },
        .ability = Ability_Hidden // Sand Force
    },
    {
        .lvl = 54,
        .species = SPECIES_HITMONTOP,
        .moves = { MOVE_TRIPLEKICK, MOVE_QUICKATTACK, MOVE_BULLDOZE, MOVE_BRUTALSWING },
        .ability = Ability_2 // Technician
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin1_Hard_Divergent[] = {
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
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_PSYCHIC, MOVE_FLAMETHROWER, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_DRAGONCLAW, MOVE_CRUNCH, MOVE_PROTECT },
        .heldItem = ITEM_SALAMENCITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin2_Hard_Divergent[] = {
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
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_DISCHARGE, MOVE_FLASHCANNON, MOVE_METALSOUND, MOVE_HIDDENPOWER },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Analytic
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_HIGHJUMPKICK, MOVE_DAZZLINGGLEAM, MOVE_STOMP },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_2 // Queenly Majesty
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal1_Hard_Divergent[] = {
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
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRACOMETEOR, MOVE_HEX, MOVE_THUNDERWAVE, MOVE_UTURN },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SWORDSDANCE, MOVE_EARTHQUAKE, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal2_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_SPIKES, MOVE_TOXIC, MOVE_EARTHQUAKE, MOVE_RECOVER },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Unaware
    },
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

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Noam_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STARAPTOR,
        .moves = { MOVE_BRAVEBIRD, MOVE_CLOSECOMBAT, MOVE_AERIALACE, MOVE_UTURN },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAMPA,
        .moves = { MOVE_HYPERVOICE, MOVE_DRAGONPULSE, MOVE_FLY, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SILK_SCARF,
        .ability = Ability_1 // Berserk
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMBIPOM,
        .moves = { MOVE_DOUBLEHIT, MOVE_NASTYPLOT, MOVE_SHADOWBALL, MOVE_THUNDERBOLT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_CURSE, MOVE_REST, MOVE_BODYSLAM, MOVE_CRUNCH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Immunity
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ashley_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_LAVAPLUME, MOVE_EARTHPOWER, MOVE_ROCKSLIDE, MOVE_YAWN },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARCANINE,
        .moves = { MOVE_EXTREMESPEED, MOVE_FLAMETHROWER, MOVE_SNARL, MOVE_PLAYROUGH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HEATMOR,
        .moves = { MOVE_FIRELASH, MOVE_HONECLAWS, MOVE_THUNDERPUNCH, MOVE_DRAINPUNCH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // White Smoke
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RAPIDASH,
        .moves = { MOVE_MEGAHORN, MOVE_SMARTSTRIKE, MOVE_POISONJAB, MOVE_FLAMECHARGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_LAVAPLUME, MOVE_THUNDERBOLT, MOVE_PSYCHIC, MOVE_WILLOWISP },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Chelsea_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AZUMARILL,
        .moves = { MOVE_BELLYDRUM, MOVE_AQUAJET, MOVE_PLAYROUGH, MOVE_SUPERPOWER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Huge Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_DRAGONTAIL, MOVE_SURF, MOVE_RECOVER, MOVE_RAINDANCE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Competitive
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DREDNAW,
        .moves = { MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_SHELLSMASH, MOVE_POISONJAB },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SIMIPOUR,
        .moves = { MOVE_HYDROPUMP, MOVE_CRUNCH, MOVE_FOCUSBLAST, MOVE_FLIPTURN },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Torrent
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_AQUARING, MOVE_AQUATAIL, MOVE_REST, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Schooling
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Buddy_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TSAREENA,
        .moves = { MOVE_TROPKICK, MOVE_HIGHJUMPKICK, MOVE_ACROBATICS, MOVE_UTURN },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_2 // Queenly Majesty
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SAWSBUCK_AUTUMN,
        .moves = { MOVE_MEGAHORN, MOVE_ENERGYBALL, MOVE_CHARM, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JUMPLUFF,
        .moves = { MOVE_BOUNCE, MOVE_GIGADRAIN, MOVE_REFLECT, MOVE_TAILWIND },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_SOLARBLADE, MOVE_LEAFBLADE, MOVE_XSCISSOR, MOVE_SYNTHESIS },
        .heldItem = ITEM_POWER_HERB,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Frisk
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Gawain_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BEWEAR,
        .moves = { MOVE_HAMMERARM, MOVE_TAKEDOWN, MOVE_THUNDERPUNCH, MOVE_BULLDOZE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Fluffy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MEDICHAM,
        .moves = { MOVE_FIREPUNCH, MOVE_ZENHEADBUTT, MOVE_RECOVER, MOVE_HIGHJUMPKICK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Pure Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_DYNAMICPUNCH, MOVE_EARTHPOWER, MOVE_LIQUIDATION, MOVE_MINDREADER },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_FLYINGPRESS, MOVE_ROOST, MOVE_AERIALACE, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FIGHTING_GEM,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MACHAMP,
        .moves = { MOVE_KNOCKOFF, MOVE_DYNAMICPUNCH, MOVE_BULLETPUNCH, MOVE_BULKUP },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // No Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Skylar_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRIFBLIM,
        .moves = { MOVE_SHADOWBALL, MOVE_STRENGTHSAP, MOVE_TAILWIND, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GHOST_GEM,
        .ability = Ability_1 // Aftermath
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_MOONBLAST, MOVE_PLUCK, MOVE_DRAGONBREATH, MOVE_COTTONGUARD },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TROPIUS,
        .moves = { MOVE_SYNTHESIS, MOVE_OUTRAGE, MOVE_AIRSLASH, MOVE_ZENHEADBUTT },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_2 // Solar Power
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ORICORIO,
        .moves = { MOVE_REVELATIONDANCE, MOVE_HURRICANE, MOVE_TEETERDANCE, MOVE_FEATHERDANCE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Dancer
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SWANNA,
        .moves = { MOVE_HURRICANE, MOVE_TAILWIND, MOVE_RAINDANCE, MOVE_SURF },
        .heldItem = ITEM_CELL_BATTERY,
        .ability = Ability_1 // Keen Eye
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Bella_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SEVIPER,
        .moves = { MOVE_GLARE, MOVE_CRUNCH, MOVE_COIL, MOVE_POISONJAB },
        .heldItem = ITEM_BLACK_SLUDGE,
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
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Liquid Ooze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_SEEDBOMB, MOVE_SYNTHESIS, MOVE_POISONPOWDER, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARBODOR,
        .moves = { MOVE_SLUDGEBOMB, MOVE_BRUTALSWING, MOVE_THUNDERBOLT, MOVE_MUDSHOT },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Aftermath
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Flash_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_VOLTSWITCH, MOVE_FLAMETHROWER, MOVE_SNARL, MOVE_DISCHARGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ZEBSTRIKA,
        .moves = { MOVE_FLAMECHARGE, MOVE_DISCHARGE, MOVE_QUICKATTACK, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_FOCUS_BAND,
        .ability = Ability_Hidden // Sap Sipper
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LUXRAY,
        .moves = { MOVE_CRUNCH, MOVE_ELECTRICTERRAIN, MOVE_THUNDERFANG, MOVE_PLAYROUGH },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_2 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_DISCHARGE, MOVE_CRUNCH, MOVE_HEADBUTT, MOVE_LIQUIDATION },
        .heldItem = ITEM_ELECTRIC_GEM,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_DISCHARGE, MOVE_LIGHTSCREEN, MOVE_FIREPUNCH, MOVE_ROCKSLIDE },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Motor Drive
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Terra_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_EARTHQUAKE, MOVE_MUDDYWATER, MOVE_ROCKTOMB, MOVE_DRAINPUNCH },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_2 // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_THUNDERFANG, MOVE_IRONHEAD, MOVE_POISONTAIL, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Spit
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DONPHAN,
        .moves = { MOVE_FIREFANG, MOVE_KNOCKOFF, MOVE_EARTHQUAKE, MOVE_SEEDBOMB },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Sand Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DUGTRIO_A,
        .moves = { MOVE_EARTHQUAKE, MOVE_IRONHEAD, MOVE_SUCKERPUNCH, MOVE_NIGHTSLASH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_2 // Tangling Hair
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_ACROBATICS, MOVE_NIGHTSLASH, MOVE_UTURN, MOVE_ICEFANG },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_2 // Sand Veil
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Seifa_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_INDEEDEE_FEMALE,
        .moves = { MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_SHADOWBALL },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Psychic Surge
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_XATU,
        .moves = { MOVE_PSYCHIC, MOVE_AIRSLASH, MOVE_TAILWIND, MOVE_NIGHTSHADE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STARMIE,
        .moves = { MOVE_POWERGEM, MOVE_SURF, MOVE_RECOVER, MOVE_THUNDERBOLT },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYCHIC, MOVE_RECOVER, MOVE_REFLECT, MOVE_ENERGYBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYCHIC, MOVE_SHADOWBALL, MOVE_NASTYPLOT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Rocco_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARMALDO,
        .moves = { MOVE_XSCISSOR, MOVE_CRUSHCLAW, MOVE_ROCKSLIDE, MOVE_BULLDOZE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_DOUBLEEDGE, MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Galvanize
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AERODACTYL,
        .moves = { MOVE_IRONHEAD, MOVE_CRUNCH, MOVE_ROCKSLIDE, MOVE_DRAGONCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ONIX,
        .moves = { MOVE_SANDSTORM, MOVE_CURSE, MOVE_BREAKINGSWIPE, MOVE_SELFDESTRUCT },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RHYPERIOR,
        .moves = { MOVE_MEGAHORN, MOVE_HAMMERARM, MOVE_DRILLRUN, MOVE_THUNDERFANG },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Janice_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ABOMASNOW,
        .moves = { MOVE_WOODHAMMER, MOVE_BLIZZARD, MOVE_BRICKBREAK, MOVE_ROCKTOMB },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Snow Warning
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRYOGONAL,
        .moves = { MOVE_FREEZEDRY, MOVE_NIGHTSLASH, MOVE_RECOVER, MOVE_ACIDARMOR },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EISCUE,
        .moves = { MOVE_AURORAVEIL, MOVE_HAIL, MOVE_HEADBUTT, MOVE_SURF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Ice Face
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VANILLUXE,
        .moves = { MOVE_BLIZZARD, MOVE_EXPLOSION, MOVE_FREEZEDRY, MOVE_FLASHCANNON },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Ice Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SANDSLASH_A,
        .moves = { MOVE_ICICLECRASH, MOVE_IRONHEAD, MOVE_ROCKSLIDE, MOVE_XSCISSOR },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Slush Rush
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Antoinette_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ARAQUANID,
        .moves = { MOVE_BUGBITE, MOVE_LIQUIDATION, MOVE_LEECHLIFE, MOVE_HEADBUTT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Water Bubble
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCYTHER,
        .moves = { MOVE_WINGATTACK, MOVE_THIEF, MOVE_COUNTER, MOVE_XSCISSOR },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_YANMEGA,
        .moves = { MOVE_BUGBITE, MOVE_UTURN, MOVE_AIRSLASH, MOVE_CRUNCH },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DURANT,
        .moves = { MOVE_ENTRAINMENT, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_GUILLOTINE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Truant
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_DRILLRUN, MOVE_LIQUIDATION, MOVE_LEECHLIFE },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Emergency Exit
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ryu_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAGALGE,
        .moves = { MOVE_DRAGONPULSE, MOVE_AQUATAIL, MOVE_SLUDGEBOMB, MOVE_THUNDERBOLT },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Adaptability
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLAPPLE,
        .moves = { MOVE_DRAGONRUSH, MOVE_GRAVAPPLE, MOVE_IRONDEFENSE, MOVE_DRAGONDANCE },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Ripen
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRUDDIGON,
        .moves = { MOVE_OUTRAGE, MOVE_IRONHEAD, MOVE_HONECLAWS, MOVE_CRUNCH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Rough Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_STOMP, MOVE_SUPERFANG, MOVE_CRUNCH, MOVE_FISHIOUSREND },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DRAGONCLAW, MOVE_ZENHEADBUTT, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Caspar_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_POLTEAGEIST,
        .moves = { MOVE_STRENGTHSAP, MOVE_GIGADRAIN, MOVE_NASTYPLOT, MOVE_SHADOWBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SPIRITOMB,
        .moves = { MOVE_DARKPULSE, MOVE_PSYSHOCK, MOVE_WILLOWISP, MOVE_ICYWIND },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BANETTE,
        .moves = { MOVE_SHADOWSNEAK, MOVE_KNOCKOFF, MOVE_WILLOWISP, MOVE_TRICK },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SHADOWBALL, MOVE_IRONHEAD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Stance Change
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Darcy_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NIGHTSLASH, MOVE_ACROBATICS, MOVE_ROOST, MOVE_HEATWAVE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Moxie
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ABSOL,
        .moves = { MOVE_NIGHTSLASH, MOVE_AIRSLASH, MOVE_THUNDERBOLT, MOVE_KNOCKOFF },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAPION,
        .moves = { MOVE_KNOCKOFF, MOVE_NIGHTSLASH, MOVE_CROSSPOISON, MOVE_XSCISSOR },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sniper
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_OBSTRUCT, MOVE_CROSSCHOP, MOVE_NIGHTSLASH, MOVE_XSCISSOR },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Defiant
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Mason_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STEELIX,
        .moves = { MOVE_IRONTAIL, MOVE_STONEEDGE, MOVE_DRAGONBREATH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_IRONHEAD, MOVE_UTURN, MOVE_CRUNCH, MOVE_PLAYROUGH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Tough Claws
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AGGRON,
        .moves = { MOVE_IRONHEAD, MOVE_HEADSMASH, MOVE_DOUBLEEDGE, MOVE_IRONDEFENSE },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_IRONHEAD, MOVE_XSCISSOR, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGNEZONE,
        .moves = { MOVE_DISCHARGE, MOVE_FLASHCANNON, MOVE_THUNDERWAVE, MOVE_HIDDENPOWER },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Analytic
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Faye_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CLEFABLE,
        .moves = { MOVE_MOONBLAST, MOVE_METEORMASH, MOVE_WISH, MOVE_AROMATHERAPY },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_ENERGYBALL, MOVE_CALMMIND, MOVE_RECOVER },
        .heldItem = ITEM_FAIRY_GEM,
        .ability = Ability_2 // Aroma Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_THUNDERWAVE, MOVE_FLASHCANNON, MOVE_PLAYROUGH, MOVE_REFLECT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AROMATISSE,
        .moves = { MOVE_MOONBLAST, MOVE_CALMMIND, MOVE_PSYCHIC, MOVE_HEALBLOCK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Aroma Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_FLING, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Pickpocket
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LeaderIris_Hard_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_DRUDDIGON,
        .moves = { MOVE_FIREPUNCH, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_ROCKSLIDE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Sheer Force
    },
    {
        .lvl = 56,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_FACADE, MOVE_KNOCKOFF, MOVE_CROSSCHOP, MOVE_GUNKSHOT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 57,
        .species = SPECIES_CRAMORANT,
        .moves = { MOVE_SURF, MOVE_DRILLPECK, MOVE_STOCKPILE, MOVE_SWALLOW },
        .heldItem = ITEM_CELL_BATTERY,
        .ability = Ability_1 // Gulp Missile
    },
    {
        .lvl = 57,
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
const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Iris_Hard_Divergent[] = {
    {
        .lvl = 58,
        .species = SPECIES_DRUDDIGON,
        .moves = { MOVE_FIREPUNCH, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_ROCKSLIDE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Sheer Force
    },
    {
        .lvl = 59,
        .species = SPECIES_DOUBLADE,
        .moves = { MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SHADOWSNEAK, MOVE_SACREDSWORD },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // No Guard
    },
    {
        .lvl = 60,
        .species = SPECIES_SANDACONDA,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_BRUTALSWING, MOVE_IRONHEAD },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Spit
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Stella_Hard_Divergent[] = {
    {
        .lvl = 57,
        .species = SPECIES_DRAPION,
        .moves = { MOVE_THUNDERFANG, MOVE_CROSSPOISON, MOVE_CRUNCH, MOVE_TOXICSPIKES },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 58,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_SHADOWBALL, MOVE_FLAMETHROWER },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 59,
        .species = SPECIES_BELLOSSOM,
        .moves = { MOVE_STUNSPORE, MOVE_QUIVERDANCE, MOVE_GIGADRAIN, MOVE_MOONBLAST },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Stench
    },
};
// #endregion

// #region Uteya Village
const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_LeadersDennisAndDee_Hard_Divergent[] = {
    {
        .lvl = 62,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_SCALD, MOVE_ICYWIND, MOVE_RECOVER, MOVE_HELPINGHAND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Competitive
    },
    {
        .lvl = 62,
        .species = SPECIES_HAWLUCHA,
        .moves = { MOVE_SWORDSDANCE, MOVE_ACROBATICS, MOVE_HIGHJUMPKICK, MOVE_ROOST },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 61,
        .species= SPECIES_INDEEDEE,
        .moves = { MOVE_HELPINGHAND, MOVE_DAZZLINGGLEAM, MOVE_PSYCHIC, MOVE_HEALINGWISH },
        .heldItem = ITEM_PSYCHIC_SEED,
        .ability = Ability_Hidden // Psychic Surge
    },
    {
        .lvl = 63,
        .species= SPECIES_AUDINO,
        .moves = { MOVE_ICYWIND, MOVE_WISH, MOVE_LIGHTSCREEN, MOVE_BLIZZARD },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Healer
    },
    {
        .lvl = 63,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_HELPINGHAND, MOVE_BLIZZARD, MOVE_LIGHTSCREEN, MOVE_DISCHARGE },
        .heldItem = ITEM_SCOPE_LENS,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 64,
        .species = SPECIES_RHYPERIOR,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_MEGAHORN, MOVE_HAMMERARM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Lightning Rod
    }
};

// #endregion

// #region Ascension Tower
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Hannah_Hard_Divergent[] = {
    {
        .lvl = 67,
        .species = SPECIES_PROBOPASS,
        .moves = { MOVE_STEALTHROCK, MOVE_THUNDERWAVE, MOVE_HEAVYSLAM, MOVE_DISCHARGE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Magnet Pull
    },
    {
        .lvl = 67,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_SUBSTITUTE, MOVE_UTURN },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 67,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_FIREPUNCH, MOVE_EARTHQUAKE, MOVE_WILDCHARGE, MOVE_BRICKBREAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 68,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_NIGHTSLASH, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_SLASH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 68,
        .species = SPECIES_HITMONTOP,
        .moves = { MOVE_TRIPLEKICK, MOVE_RAPIDSPIN, MOVE_FAKEOUT, MOVE_AERIALACE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 69,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_XSCISSOR, MOVE_POISONJAB, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Lucas_Hard_Divergent[] = {
    {
        .lvl = 68,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_SHADOWBALL, MOVE_ENERGYBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 68,
        .species = SPECIES_YANMEGA,
        .moves = { MOVE_BUGBUZZ, MOVE_AIRSLASH, MOVE_UTURN, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 68,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_CRUNCH, MOVE_DRAGONRUSH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Strong Jaw
    },
    {
        .lvl = 69,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_WOODHAMMER, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 69,
        .species = SPECIES_CRUSTLE,
        .moves = { MOVE_SHELLSMASH, MOVE_ROCKSLIDE, MOVE_STEALTHROCK, MOVE_XSCISSOR },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 70,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_FLAMETHROWER, MOVE_VOLTSWITCH, MOVE_SNARL, MOVE_DISCHARGE },
        .heldItem = ITEM_MANECTITE,
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Jenna_Hard_Divergent[] = {
    {
        .lvl = 69,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_FAKEOUT, MOVE_HIGHJUMPKICK, MOVE_BLAZEKICK, MOVE_KNOCKOFF },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 69,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_SACREDSWORD, MOVE_IRONHEAD, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 69,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 70,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_DARKPULSE, MOVE_DESTINYBOND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 70,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_ICEBEAM, MOVE_MUDSHOT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 71,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_HYPERVOICE, MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_ROOST },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Thomas_Hard_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_GOLISOPOD,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Emergency Exit
    },
    {
        .lvl = 70,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_NASTYPLOT, MOVE_ROOST, MOVE_DARKPULSE, MOVE_HEATWAVE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 70,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 71,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_DISCHARGE, MOVE_TRIATTACK, MOVE_ICEBEAM },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 71,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_AQUATAIL, MOVE_EARTHQUAKE, MOVE_WHIRLPOOL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 72,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_SANDSTORM, MOVE_CURSE, MOVE_IRONTAIL, MOVE_EARTHQUAKE },
        .heldItem = ITEM_STEELIXITE,
        .ability = Ability_2 // Sturdy
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_Champion_Selene_Hard_Divergent[] = {
    {
        .lvl = 72,
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

// #endregion

// #region Elite Four Rematches
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_HannahRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_ELECTIVIRE,
        .moves = { MOVE_FIREPUNCH, MOVE_EARTHQUAKE, MOVE_WILDCHARGE, MOVE_BRICKBREAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Motor Drive
    },
    {
        .lvl = 74,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_NIGHTSLASH, MOVE_LEAFBLADE, MOVE_KNOCKOFF, MOVE_SLASH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 74,
        .species = SPECIES_HITMONTOP,
        .moves = { MOVE_TRIPLEKICK, MOVE_RAPIDSPIN, MOVE_FAKEOUT, MOVE_AERIALACE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 75,
        .species = SPECIES_BEEDRILL,
        .moves = { MOVE_PROTECT, MOVE_XSCISSOR, MOVE_POISONJAB, MOVE_DRILLRUN },
        .heldItem = ITEM_BEEDRILLITE,
        .ability = Ability_Hidden // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_LucasRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_DRACOVISH,
        .moves = { MOVE_FISHIOUSREND, MOVE_CRUNCH, MOVE_DRAGONRUSH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Strong Jaw
    },
    {
        .lvl = 74,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_DRAGONHAMMER, MOVE_WOODHAMMER, MOVE_PSYSHOCK, MOVE_SYNTHESIS },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 74,
        .species = SPECIES_CRUSTLE,
        .moves = { MOVE_SHELLSMASH, MOVE_ROCKSLIDE, MOVE_STEALTHROCK, MOVE_XSCISSOR },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Shell Armor
    },
    {
        .lvl = 75,
        .species = SPECIES_MANECTRIC,
        .moves = { MOVE_FLAMETHROWER, MOVE_VOLTSWITCH, MOVE_SNARL, MOVE_DISCHARGE },
        .heldItem = ITEM_MANECTITE,
        .ability = Ability_2 // Lightning Rod
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_JennaRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 74,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_DARKPULSE, MOVE_DESTINYBOND, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 74,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_ICEBEAM, MOVE_MUDSHOT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 75,
        .species = SPECIES_ALTARIA,
        .moves = { MOVE_HYPERVOICE, MOVE_MOONBLAST, MOVE_COTTONGUARD, MOVE_ROOST },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_ThomasRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 74,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_DISCHARGE, MOVE_TRIATTACK, MOVE_ICEBEAM },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 74,
        .species = SPECIES_WISHIWASHI,
        .moves = { MOVE_HYDROPUMP, MOVE_AQUATAIL, MOVE_EARTHQUAKE, MOVE_WHIRLPOOL },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Schooling
    },
    {
        .lvl = 75,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_SANDSTORM, MOVE_CURSE, MOVE_IRONTAIL, MOVE_EARTHQUAKE },
        .heldItem = ITEM_STEELIXITE,
        .ability = Ability_2 // Sturdy
    }
};
// #endregion

// #region Title Defense
const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_VAPOREON,
        .moves = { MOVE_MUDDYWATER, MOVE_ACIDARMOR, MOVE_ICEBEAM, MOVE_SHADOWBALL },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Jolteon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_STAR,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_HIDDENPOWER, MOVE_VOLTSWITCH, MOVE_SHADOWBALL },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Flareon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_STRAWBERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_BODYSLAM, MOVE_DIG, MOVE_WILLOWISP },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Guts
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Espeon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_LOVE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_ESPEON,
        .moves = { MOVE_PSYCHIC, MOVE_MORNINGSUN, MOVE_PSYCHUP, MOVE_SHADOWBALL },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Magic Bounce
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Umbreon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_FLOWER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_SNARL, MOVE_TOXIC, MOVE_ROAR },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Leafeon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_CLOVER,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_LEAFEON,
        .moves = { MOVE_SYNTHESIS, MOVE_SWORDSDANCE, MOVE_LEAFBLADE, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Glaceon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_BERRY,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_GLACEON,
        .moves = { MOVE_HAIL, MOVE_AURORAVEIL, MOVE_FREEZEDRY, MOVE_CHARM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Sylveon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ALCREMIE_RIBBON,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYSHOCK, MOVE_RECOVER, MOVE_ACIDARMOR },
		.heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Aroma Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_STOMPINGTANTRUM, MOVE_WILLOWISP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_PSYSHOCK, MOVE_LEECHSEED, MOVE_DRAGONHAMMER },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_ABSOL,
        .moves = { MOVE_SHADOWCLAW, MOVE_SWORDSDANCE, MOVE_KNOCKOFF, MOVE_THUNDERWAVE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_PIDGEOT,
		.moves = { MOVE_ROOST, MOVE_HURRICANE, MOVE_DEFOG, MOVE_UTURN },
		.heldItem = ITEM_PIDGEOTITE,
		.ability = Ability_Hidden // Big Pecks
    },
    {
        .lvl = 80,
        .species = SPECIES_FLAREON,
        .moves = { MOVE_WISH, MOVE_LIGHTSCREEN, MOVE_SHADOWBALL, MOVE_PLAYROUGH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_YoungsterJoey_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ZIGZAGOON,
        .moves = { MOVE_HEADBUTT, MOVE_BELLYDRUM, MOVE_FLAIL, MOVE_THUNDER },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Quick Feet
    },
    {
        .lvl = 78,
        .species = SPECIES_ZIGZAGOON_G,
        .moves = { MOVE_SURF, MOVE_ICEBEAM, MOVE_IRONTAIL, MOVE_SEEDBOMB },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Gluttony
    },
    {
        .lvl = 78,
        .species = SPECIES_LINOONE,
        .moves = { MOVE_SLASH, MOVE_SWITCHEROO, MOVE_HONECLAWS, MOVE_FLING },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 78,
        .species = SPECIES_LINOONE_G,
        .moves = { MOVE_NIGHTSLASH, MOVE_HONECLAWS, MOVE_GIGAIMPACT, MOVE_THIEF },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 79,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_DOUBLEEDGE, MOVE_PINMISSILE, MOVE_NIGHTSLASH, MOVE_CROSSCHOP },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 80,
        .species = SPECIES_OBSTAGOON,
        .moves = { MOVE_OBSTRUCT, MOVE_CROSSPOISON, MOVE_XSCISSOR, MOVE_KNOCKOFF },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_WithVictini_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_SYNTHESIS, MOVE_ENERGYBALL, MOVE_POLLENPUFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 78,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 78,
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRAGONDARTS, MOVE_UTURN, MOVE_PHANTOMFORCE, MOVE_DRACOMETEOR },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 78,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_METEORMASH, MOVE_BULLETPUNCH, MOVE_ZENHEADBUTT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_METAGROSSITE,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 79,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_WATERSHURIKEN, MOVE_SCALD, MOVE_DARKPULSE, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Battle Bond
    },
    {
        .lvl = 80,
        .species = SPECIES_VICTINI,
        .moves = { MOVE_VCREATE, MOVE_WILDCHARGE, MOVE_ZENHEADBUTT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_1 // Victory Star
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_BLIZZARD, MOVE_AURORAVEIL, MOVE_DAZZLINGGLEAM, MOVE_NASTYPLOT },
        .heldItem = ITEM_BABIRI_BERRY,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 78,
        .species = SPECIES_LILLIGANT,
        .moves = { MOVE_QUIVERDANCE, MOVE_SYNTHESIS, MOVE_ENERGYBALL, MOVE_POLLENPUFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Chlorophyll
    },
    {
        .lvl = 78,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_BULLETPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Technician
    },
    {
        .lvl = 78,
        .species = SPECIES_DRAGAPULT,
        .moves = { MOVE_DRAGONDARTS, MOVE_UTURN, MOVE_PHANTOMFORCE, MOVE_DRACOMETEOR },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 79,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_METEORMASH, MOVE_BULLETPUNCH, MOVE_ZENHEADBUTT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_METAGROSSITE,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 80,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_WATERSHURIKEN, MOVE_SCALD, MOVE_DARKPULSE, MOVE_ICEBEAM },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Battle Bond
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Alistair_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_PERRSERKER,
        .moves = { MOVE_FAKEOUT, MOVE_IRONHEAD, MOVE_SCREECH, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Steely Spirit
    },
    {
        .lvl = 78,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_KNOCKOFF, MOVE_PROTECT },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 78,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_CIRCLETHROW, MOVE_WORKUP, MOVE_ROCKSLIDE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 78,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_DISCHARGE, MOVE_FLAMETHROWER, MOVE_LIQUIDATION, MOVE_ROCKTOMB },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 79,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_CRUNCH, MOVE_ICEFANG, MOVE_EARTHQUAKE, MOVE_STONEEDGE },
        .heldItem = ITEM_TYRANITARITE,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 80,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Hawthorne_Hard_Divergent[] = {
    { // Unchanged in divergent; kept here for simplicity
        .lvl = 78,
        .species = SPECIES_CHESNAUGHT,
        .moves = { MOVE_SEEDBOMB, MOVE_SPIKYSHIELD, MOVE_BULKUP, MOVE_HAMMERARM },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_Hidden // Bulletproof
    },
    {
        .lvl = 78,
        .species = SPECIES_INCINEROAR,
        .moves = { MOVE_PARTINGSHOT, MOVE_FLAREBLITZ, MOVE_DARKESTLARIAT, MOVE_FAKEOUT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 78,
        .species = SPECIES_INTELEON,
        .moves = { MOVE_SNIPESHOT, MOVE_ICEBEAM, MOVE_DARKPULSE, MOVE_HYPERBEAM },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Sniper
    },
    {
        .lvl = 78,
        .species = SPECIES_TORTERRA,
        .moves = { MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_WOODHAMMER, MOVE_SYNTHESIS },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Shell Armor
    },
    {
        .lvl = 79,
        .species = SPECIES_SWAMPERT,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHQUAKE, MOVE_ICEBEAM, MOVE_ROCKSLIDE },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 80,
        .species = SPECIES_CHARIZARD,
        .moves = { MOVE_DRAGONCLAW, MOVE_EARTHQUAKE, MOVE_FLAREBLITZ, MOVE_DRAGONDANCE },
        .heldItem = ITEM_CHARIZARDITE_X,
        .ability = Ability_1 // Blaze
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Clancy_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_SUCKERPUNCH, MOVE_MEMENTO, MOVE_FLAMETHROWER, MOVE_TOXIC },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 78,
        .species = SPECIES_REUNICLUS,
        .moves = { MOVE_ENCORE, MOVE_RECOVER, MOVE_PSYSHOCK, MOVE_FLASHCANNON },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Magic Guard
    },
    {
        .lvl = 78,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_HAMMERARM, MOVE_SHADOWPUNCH, MOVE_MEGAPUNCH, MOVE_FIREPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 78,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_PLAYROUGH, MOVE_OUTRAGE, MOVE_ICEFANG, MOVE_CHARM },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 79,
        .species = SPECIES_SCIZOR,
        .moves = { MOVE_BULLETPUNCH, MOVE_XSCISSOR, MOVE_IRONHEAD, MOVE_SWORDSDANCE },
        .heldItem = ITEM_SCIZORITE,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 80,
        .species = SPECIES_DRAGALGE,
        .moves = { MOVE_SLUDGEBOMB, MOVE_AQUATAIL, MOVE_THUNDERBOLT, MOVE_FOCUSBLAST },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Poison Point
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ena_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ARIADOS,
        .moves = { MOVE_CROSSPOISON, MOVE_STICKYWEB, MOVE_TOXICTHREAD, MOVE_PINMISSILE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 78,
        .species = SPECIES_WALREIN,
        .moves = { MOVE_BLIZZARD, MOVE_BRINE, MOVE_BODYSLAM, MOVE_STOMPINGTANTRUM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Thick Fat
    },
    {
        .lvl = 78,
        .species = SPECIES_AMBIPOM,
        .moves = { MOVE_DOUBLEHIT, MOVE_ACROBATICS, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_1 // Technician
    },
    {
        .lvl = 78,
        .species = SPECIES_LURANTIS,
        .moves = { MOVE_SOLARBLADE, MOVE_LEAFBLADE, MOVE_XSCISSOR, MOVE_SYNTHESIS },
        .heldItem = ITEM_POWER_HERB,
        .ability = Ability_Hidden // Contrary
    },
    {
        .lvl = 79,
        .species = SPECIES_AERODACTYL,
        .moves = { MOVE_STONEEDGE, MOVE_CRUNCH, MOVE_IRONHEAD, MOVE_ICEFANG },
        .heldItem = ITEM_AERODACTYLITE,
        .ability = Ability_2 // Pressure
    },
    {
        .lvl = 80,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_FLAMETHROWER, MOVE_HEX, MOVE_ENERGYBALL },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Infiltrator
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Felix_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_ORBEETLE,
        .moves = { MOVE_UTURN, MOVE_REFLECT, MOVE_PSYCHIC, MOVE_BUGBUZZ },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 78,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_ICEFANG, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 78,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_RAINDANCE, MOVE_ROOST, MOVE_HURRICANE, MOVE_THUNDER },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Multiscale
    },
    {
        .lvl = 78,
        .species = SPECIES_TYRANTRUM,
        .moves = { MOVE_HEADSMASH, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_FIREFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 79,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_QUIVERDANCE, MOVE_BUGBUZZ, MOVE_GIGADRAIN },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 80,
        .species = SPECIES_DURALUDON,
        .moves = { MOVE_FLASHCANNON, MOVE_DRAGONCLAW, MOVE_IRONDEFENSE, MOVE_BREAKINGSWIPE },
        .heldItem = ITEM_DURALUDITE,
        .ability = Ability_Hidden // Stalwart
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Collin_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_MAGMORTAR,
        .moves = { MOVE_PSYCHIC, MOVE_FIREBLAST, MOVE_THUNDERBOLT, MOVE_HYPERVOICE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 78,
        .species = SPECIES_FERALIGATR,
        .moves = { MOVE_DRAGONDANCE, MOVE_ICEPUNCH, MOVE_CRUNCH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 78,
        .species = SPECIES_GOLEM_A,
        .moves = { MOVE_THUNDERPUNCH, MOVE_STONEEDGE, MOVE_EARTHQUAKE, MOVE_HEAVYSLAM },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 78,
        .species = SPECIES_NINETALES_A,
        .moves = { MOVE_FREEZEDRY, MOVE_EXTRASENSORY, MOVE_NASTYPLOT, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 79,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_HYPERBEAM, MOVE_ICEBEAM, MOVE_THUNDERBOLT, MOVE_RECOVER },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 80,
        .species = SPECIES_SALAMENCE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_DRAGONCLAW, MOVE_CRUNCH, MOVE_PROTECT },
        .heldItem = ITEM_SALAMENCITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Crystal_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_QUAGSIRE,
        .moves = { MOVE_SPIKES, MOVE_TOXIC, MOVE_EARTHQUAKE, MOVE_RECOVER },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_Hidden // Unaware
    },
    {
        .lvl = 78,
        .species = SPECIES_METAGROSS,
        .moves = { MOVE_HEAVYSLAM, MOVE_KNOCKOFF, MOVE_EARTHQUAKE, MOVE_BULLETPUNCH },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 78,
        .species = SPECIES_SNORLAX,
        .moves = { MOVE_CURSE, MOVE_BODYSLAM, MOVE_HEATCRASH, MOVE_REST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Thick Fat
    },
    {
        .lvl = 78,
        .species = SPECIES_HARIYAMA,
        .moves = { MOVE_BULKUP, MOVE_DRAINPUNCH, MOVE_KNOCKOFF, MOVE_BULLETPUNCH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 79,
        .species = SPECIES_MAROWAK_A,
        .moves = { MOVE_SHADOWBONE, MOVE_BONEMERANG, MOVE_STEALTHROCK, MOVE_FIREBLAST },
        .heldItem = ITEM_THICK_CLUB,
        .ability = Ability_2 // Lightning Rod
    },
    {
        .lvl = 80,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_NASTYPLOT, MOVE_SHADOWBALL, MOVE_SLUDGEWAVE, MOVE_FOCUSBLAST },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Irene_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_BULKUP, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 78,
        .species = SPECIES_EELEKTROSS,
        .moves = { MOVE_FLAMETHROWER, MOVE_DISCHARGE, MOVE_LIQUIDATION, MOVE_CRUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 78,
        .species = SPECIES_CAMERUPT,
        .moves = { MOVE_EARTHPOWER, MOVE_LAVAPLUME, MOVE_SUNNYDAY, MOVE_IRONHEAD },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Solid Rock
    },
    {
        .lvl = 78,
        .species = SPECIES_GRANBULL,
        .moves = { MOVE_PLAYROUGH, MOVE_CRUNCH, MOVE_FIREFANG, MOVE_OUTRAGE },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 79,
        .species = SPECIES_GLISCOR,
        .moves = { MOVE_SUBSTITUTE, MOVE_THUNDERFANG, MOVE_POISONJAB, MOVE_UTURN },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Poison Heal
    },
    {
        .lvl = 80,
        .species = SPECIES_ALAKAZAM,
        .moves = { MOVE_PSYSHOCK, MOVE_SHADOWBALL, MOVE_CALMMIND, MOVE_FOCUSBLAST },
        .heldItem = ITEM_ALAKAZITE,
        .ability = Ability_1 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ronald_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_PORYGON2,
        .moves = { MOVE_PSYSHOCK, MOVE_THUNDERBOLT, MOVE_SHADOWBALL, MOVE_RECOVER },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Download
    },
    {
        .lvl = 78,
        .species = SPECIES_HITMONLEE,
        .moves = { MOVE_BLAZEKICK, MOVE_CLOSECOMBAT, MOVE_SUCKERPUNCH, MOVE_RAPIDSPIN },
        .heldItem = ITEM_FIGHTING_GEM,
        .ability = Ability_Hidden // Unburden
    },
    {
        .lvl = 78,
        .species = SPECIES_SKUNTANK,
        .moves = { MOVE_NIGHTSLASH, MOVE_MEMENTO, MOVE_POISONJAB, MOVE_FLAMETHROWER },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Aftermath
    },
    {
        .lvl = 78,
        .species = SPECIES_GOLURK,
        .moves = { MOVE_SHADOWPUNCH, MOVE_IRONDEFENSE, MOVE_HAMMERARM, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Iron Fist
    },
    {
        .lvl = 79,
        .species = SPECIES_POLIWRATH,
        .moves = { MOVE_BODYSLAM, MOVE_BELLYDRUM, MOVE_LIQUIDATION, MOVE_DRAINPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 80,
        .species = SPECIES_PINSIR,
        .moves = { MOVE_SWORDSDANCE, MOVE_XSCISSOR, MOVE_CLOSECOMBAT, MOVE_GIGAIMPACT },
        .heldItem = ITEM_PINSIRITE,
        .ability = Ability_Hidden // Moxie
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Kurtis_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_AEGISLASH,
        .moves = { MOVE_KINGSSHIELD, MOVE_IRONHEAD, MOVE_SACREDSWORD, MOVE_SHADOWSNEAK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Stance Change
    },
    {
        .lvl = 78,
        .species = SPECIES_STEELIX,
        .moves = { MOVE_HEAVYSLAM, MOVE_ROCKSLIDE, MOVE_EARTHQUAKE, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 78,
        .species = SPECIES_GRIMMSNARL,
        .moves = { MOVE_THUNDERWAVE, MOVE_SPIRITBREAK, MOVE_SUCKERPUNCH, MOVE_REFLECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 78,
        .species = SPECIES_HONCHKROW,
        .moves = { MOVE_ROOST, MOVE_NASTYPLOT, MOVE_HEATWAVE, MOVE_DARKPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Super Luck
    },
    {
        .lvl = 79,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_MUDDYWATER, MOVE_RECOVER, MOVE_DAZZLINGGLEAM, MOVE_BLIZZARD },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
    {
        .lvl = 80,
        .species = SPECIES_GENGAR,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_DARKPULSE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GENGARITE,
        .ability = Ability_1 // Cursed Body
    },
};
// #endregion
// #region Postgame
// Identical to normal mode but for some reason will crash if not defined
const struct TrainerMonNoItemCustomMoves sParty_HeleoCity_NurseBrianne_Hard_Divergent[] = {
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
const struct Trainer gHardDivergentTrainers[] = {
    // #region Important trainers
    [TRAINER_RIVAL2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival2_Hard_Divergent}
    },
    [TRAINER_RUBARR_DESERT_PARTNER_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_PartnerRival1_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_PartnerRival1_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival3_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival3_Hard_Divergent}
    },
    [TRAINER_TORMA_CAVE_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey1_Hard_Divergent}
    },
    [TRAINER_TORMA_CAVE_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey1_Hard_Divergent}
    },
    [TRAINER_ROUTE_10_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey2_Hard_Divergent}
    },
    [TRAINER_ROUTE_10_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Casey2_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Vaporeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Vaporeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Jolteon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Jolteon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Flareon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Flareon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Espeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Espeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Umbreon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Umbreon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Leafeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Leafeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Glaceon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Glaceon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival4_Sylveon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival4_Sylveon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Vaporeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Vaporeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Jolteon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Jolteon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Flareon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Flareon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Espeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Espeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Umbreon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Umbreon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Leafeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Leafeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Glaceon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Glaceon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival5_Sylveon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival5_Sylveon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_EmraldinQuayEvent_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_EmraldinQuayEvent_Hard_Divergent}
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
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Rival_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Rival_Hard_Divergent}
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
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Alistair_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Alistair_Hard_Divergent}
    },
    // #endregion
    // #region Rhodanzi City
    [TRAINER_RHODANZI_GYM_LEADER_TERRENCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline,
        .partySize = NELEMS(sParty_RhodanziCity_LeaderTerrence_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_RhodanziCity_LeaderTerrence_Hard_Divergent}
    },
    // #endregion
    // #region Rubarr Desert
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoAdminIrene_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_RubarrDesert_TeamPlutoAdminIrene_Hard_Divergent}
    },
    // #endregion
    // #region Ferrox Gym
    [TRAINER_FERROX_GYM_LEADER_STELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .gender = FEMALE,
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline,
        .partySize = NELEMS(sParty_FerroxGym_GymLeaderStella_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_FerroxGym_GymLeaderStella_Hard_Divergent}
    },
    // #endregion
    // #region Heleo City Gym
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_HardBaseline,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine2_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_HardBaseline,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine3_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine3_Hard_Divergent}
    },
    // #endregion
    // #region Daimyn City Gym
    [TRAINER_DAIMYN_CITY_GYM_LEADER_CHANCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .gender = MALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance2_Hard_Divergent}
    },
    // #endregion
    // #region Route 11 South
    [TRAINER_ROUTE_11_SOUTH_PLUTO_ADMIN_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .gender = MALE,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoAdminRonald_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Route11South_TeamPlutoAdminRonald_Hard_Divergent}
    },
    // #endregion
    // #region Laplaz Town Gym
    [TRAINER_LAPLAZ_GYM_LEADER_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey_Hard_Divergent}
    },
    // #endregion
    // #region Scalding Spa
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
        .partySize = NELEMS(sParty_ScaldingSpa_TeamPlutoYolena_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_ScaldingSpa_TeamPlutoYolena_Hard_Divergent}
    },
    // #endregion
    // #region Bruccie Village Gym
    [TRAINER_BRUCCIE_VILLAGE_GYM_LEADER_ABBY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_LeaderAbby_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_BruccieVillageGym_LeaderAbby_Hard_Divergent}
    },
    // #endregion
    // #region Calicin Bay
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
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoYolena_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_CalicinBay_TeamPlutoYolena_Hard_Divergent}
    },
    // #endregion
    // #region Pluto HQ
    [TRAINER_PLUTO_HQ_B4F_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .gender = FEMALE,
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Hard_Divergent}
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
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Hard_Divergent}
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
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Hard_Divergent}
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
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_Kaito_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_StatsDojo_Kaito_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_Developer_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin1_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin1_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_Developer_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin2_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_Developer_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal1_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal1_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_Developer_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal2_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal2_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_NOAM] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_N, _o, _a, _m, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Noam_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Noam_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ASHLEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_A, _s, _h, _l, _e, _y, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ashley_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ashley_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CHELSEA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _h, _e, _l, _s, _e, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Chelsea_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Chelsea_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BUDDY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _u, _d, _d, _y, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Buddy_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Buddy_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_GAWAIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_G, _a, _w, _a, _i, _n, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Gawain_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Gawain_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SKYLAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_S, _k, _y, _l, _a, _r, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Skylar_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Skylar_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_B, _e, _l, _l, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Bella_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Bella_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FLASH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_F, _l, _a, _s, _h, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Flash_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Flash_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_TERRA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_RANGER_F,
        .trainerName = {_T, _e, _r, _r, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Terra_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Terra_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SEIFA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_S, _e, _i, _f, _a, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Seifa_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Seifa_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ROCCO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _c, _c, _o, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Rocco_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Rocco_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_JANICE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_J, _a, _n, _i, _c, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Janice_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Janice_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ANTOINETTE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_A, _n, _t, _o, _i, _n, _e, _t, _t, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Antoinette_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Antoinette_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_RYU] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_R, _y, _u, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ryu_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ryu_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CASPAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_C, _a, _s, _p, _a, _r, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Caspar_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Caspar_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_DARCY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_D, _a, _r, _c, _y, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Darcy_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Darcy_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_MASON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_M, _a, _s, _o, _n, _END },
        .gender = MALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Mason_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Mason_Hard_Divergent}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FAYE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_F, _a, _y, _e, _END },
        .gender = FEMALE,
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Hard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Faye_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Faye_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_HP_AWARE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_LeaderIris_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_LeaderIris_Hard_Divergent}
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
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Iris_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Iris_Hard_Divergent}
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
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Stella_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Stella_Hard_Divergent}
    },
    // #endregion
    // #region Carnelidge Volcano
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
        .partySize = NELEMS(sParty_CarnelidgeVolcano_PartnerRival_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_PartnerRival_Hard_Divergent}
    },
    // #endregion
    // #region Uteya Village
    [TRAINER_UTEYA_VILLAGE_GYM_LEADERS_DENNIS_AND_DEE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        // No gender set, chosen at random
        .items = {ITEM_MAX_POTION},
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_HardBaseline | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_LeadersDennisAndDee_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_LeadersDennisAndDee_Hard_Divergent}
    },
    // #endregion
    // #region Victory Road
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Vaporeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Vaporeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Jolteon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Jolteon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Flareon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Flareon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Espeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Espeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Umbreon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Umbreon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Leafeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Leafeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Glaceon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Glaceon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Sylveon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Sylveon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_ExhibitionBattle_SecondaryTeam_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_ExhibitionBattle_SecondaryTeam_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Hannah_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Hannah_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Lucas_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Lucas_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Jenna_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Jenna_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_Thomas_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_Thomas_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_Champion_Selene_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_Champion_Selene_Hard_Divergent}
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
        .partySize = NELEMS(sParty_PostCredits_Alistair_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_PostCredits_Alistair_Hard_Divergent}
    },
    // #endregion
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_HannahRematch_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_HannahRematch_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_LucasRematch_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_LucasRematch_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_JennaRematch_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_JennaRematch_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_EliteFour_ThomasRematch_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_EliteFour_ThomasRematch_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Jolteon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Jolteon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Flareon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Flareon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Espeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Espeon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Umbreon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Umbreon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Leafeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Leafeon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Glaceon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Glaceon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Rival_Sylveon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Rival_Sylveon_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_YoungsterJoey_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_YoungsterJoey_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Selene_WithVictini_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Selene_WithVictini_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Selene_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Selene_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Alistair_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Alistair_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Hawthorne_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Hawthorne_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Clancy_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Clancy_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Ena_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Ena_Hard_Divergent}
    },
    // Copycat identical between all difficulty modes
    [TRAINER_ASCENSION_TOWER_TITLE_DEFENSE_FOREIGNER] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHALLENGER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_F, _e, _l, _i, _x, _END},
        .gender = MALE,
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Felix_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Felix_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Collin_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Collin_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Crystal_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Crystal_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Irene_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Irene_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Ronald_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Ronald_Hard_Divergent}
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
        .aiFlags = TrainerAIFlags_AscensionTower_Hard,
        .partySize = NELEMS(sParty_AscensionTower_TitleDefense_Kurtis_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_AscensionTower_TitleDefense_Kurtis_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Vaporeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Vaporeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Jolteon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Jolteon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Flareon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Flareon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Espeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Espeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Umbreon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Umbreon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Leafeon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Leafeon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Glaceon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Glaceon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_Sylveon_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_Sylveon_Hard_Divergent}
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
        .partySize = NELEMS(sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Hard_Divergent),
        .party = {.ItemCustomMoves = sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Hard_Divergent}
    },
    // #endregion
    // #region Postgame
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
        .partySize = NELEMS(sParty_HeleoCity_NurseBrianne_Hard_Divergent),
        .party = {.NoItemCustomMoves = sParty_HeleoCity_NurseBrianne_Hard_Divergent}
    }
    // #endregion
    // #endregion
};
// #endregion
