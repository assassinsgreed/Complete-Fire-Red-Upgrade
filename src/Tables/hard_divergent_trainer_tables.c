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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVISQUIRE,
        .moves = { MOVE_DRILLPECK, MOVE_ROCKSMASH, MOVE_TAILWIND, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 37,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_KNOCKOFF, MOVE_IRONDEFENSE, MOVE_BRICKBREAK, MOVE_FIRSTIMPRESSION },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 37,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONPULSE, MOVE_POWERGEM, MOVE_ELECTROBALL },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_ROOST, MOVE_IRONDEFENSE, MOVE_IRONHEAD },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 44,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FLING, MOVE_THIEF, MOVE_ICEPUNCH, MOVE_HONECLAWS },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_BRICKBREAK, MOVE_KNOCKOFF, MOVE_FIRSTIMPRESSION, MOVE_LEAFBLADE },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 45,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_POWERGEM, MOVE_DRAGONPULSE, MOVE_COTTONGUARD, MOVE_THUNDERBOLT },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_SPIKES, MOVE_TOXICSPIKES, MOVE_RAZORSHELL, MOVE_ICICLECRASH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 51,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AURASPHERE, MOVE_AIRSLASH, MOVE_TRIATTACK, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 53,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_SCORCHINGSANDS },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 53,
        .species = SPECIES_RAICHU_A,
        .moves = { MOVE_ELECTRICTERRAIN, MOVE_ELECTROBALL, MOVE_PSYCHIC, MOVE_SURF },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Surge Surfer
    },
    {
        .lvl = 54,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_FIREFANG, MOVE_SCALESHOT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    },
    {
        .lvl = 55,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_SWORDSDANCE, MOVE_METEORMASH, MOVE_CLOSECOMBAT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LUCARIONITE,
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Rival_Hard_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 54,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 55,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_COUNTER, MOVE_HEAVYSLAM, MOVE_CURSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 55,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 56,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 57,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_NIGHTSLASH, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_PartnerRival_Hard_Divergent[] = {
    {
        .lvl = 54,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 56,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 57,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_IRONHEAD, MOVE_RETALIATE, MOVE_NIGHTSLASH, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Alistair_Hard_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_GOLBAT,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_LEECHLIFE, MOVE_MEANLOOK },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 55,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_INGRAIN, MOVE_GIGADRAIN, MOVE_SUBSTITUTE, MOVE_CLEARSMOG },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 57,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 58,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_SUNNYDAY, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_SUPERPOWER, MOVE_HEAVYSLAM, MOVE_REST },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 67,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 67,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_SPIKES, MOVE_TOXICSPIKES, MOVE_RAZORSHELL, MOVE_ICICLECRASH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 66,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AURASPHERE, MOVE_AIRSLASH, MOVE_TRIATTACK, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 66,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_SCORCHINGSANDS },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 67,
        .species = SPECIES_RAICHU_A,
        .moves = { MOVE_ELECTRICTERRAIN, MOVE_ELECTROBALL, MOVE_PSYCHIC, MOVE_SURF },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Surge Surfer
    },
    {
        .lvl = 67,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_FIREFANG, MOVE_SCALESHOT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    },
    {
        .lvl = 68,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_SWORDSDANCE, MOVE_METEORMASH, MOVE_CLOSECOMBAT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LUCARIONITE,
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonItemCustomMoves sParty_PostCredits_Alistair_Hard_Divergent[] = {
    {
        .lvl = 72,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_CROSSPOISON, MOVE_HAZE },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 72,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_SPORE, MOVE_TOXIC, MOVE_BODYSLAM, MOVE_PROTECT },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 72,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 72,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_SUNNYDAY, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Jolteon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Flareon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Espeon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Umbreon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Leafeon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Glaceon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_Sylveon_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_ROOST },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 71,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_SCREECH, MOVE_ICICLECRASH, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
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
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
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

const struct TrainerMonItemCustomMoves sParty_Rival_PostgameExhibitionBattle_SecondaryTeam_Hard_Divergent[] = {
    {
        .lvl = 71,
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_SPIKES, MOVE_TOXICSPIKES, MOVE_RAZORSHELL, MOVE_ICICLECRASH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 71,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AURASPHERE, MOVE_AIRSLASH, MOVE_TRIATTACK, MOVE_DAZZLINGGLEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 71,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_STEALTHROCK, MOVE_STONEEDGE, MOVE_SCORCHINGSANDS },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 72,
        .species = SPECIES_RAICHU_A,
        .moves = { MOVE_ELECTRICTERRAIN, MOVE_ELECTROBALL, MOVE_PSYCHIC, MOVE_SURF },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Surge Surfer
    },
    {
        .lvl = 72,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_FIREFANG, MOVE_SCALESHOT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    },
    {
        .lvl = 73,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_SWORDSDANCE, MOVE_METEORMASH, MOVE_CLOSECOMBAT, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LUCARIONITE,
        .ability = Ability_Hidden // Justified
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
        .species = SPECIES_NICKIT,
        .moves = { MOVE_SNARL, MOVE_QUICKATTACK, MOVE_TORMENT, MOVE_FOULPLAY },
        .heldItem = ITEM_GRASSY_SEED,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 13,
        .species = SPECIES_SKIDDO,
        .moves = { MOVE_LEECHSEED, MOVE_VINEWHIP, MOVE_TAILWHIP, MOVE_GROWTH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Grass Pelt
    }
};
// #endregion

// #region Rubarr Desert
const struct TrainerMonItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene_Hard_Divergent[] = {
    {
        .lvl = 14,
        .species = SPECIES_NICKIT,
        .moves = { MOVE_SNARL, MOVE_BEATUP, MOVE_HONECLAWS, MOVE_QUICKATTACK },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Stakeout
    },
    {
        .lvl = 15,
        .species = SPECIES_BONSLY,
        .moves = { MOVE_ROCKTHROW, MOVE_BLOCK, MOVE_CURSE, MOVE_FLAIL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 15,
        .species = SPECIES_SANDILE,
        .moves = { MOVE_BITE, MOVE_HONECLAWS, MOVE_SANDTOMB, MOVE_MEANLOOK },
        .heldItem = ITEM_BLACK_GLASSES,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 16,
        .species = SPECIES_SALANDIT,
        .moves = { MOVE_EMBER, MOVE_SMOG, MOVE_FAKEOUT, MOVE_SCRATCH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Corrosion
    },
};
// #endregion

// #region Ferrox Village
const struct TrainerMonItemCustomMoves sParty_FerroxGym_GymLeaderStella_Hard_Divergent[] = {
    {
        .lvl = 19,
        .species = SPECIES_MAREANIE,
        .moves = { MOVE_TOXIC, MOVE_TOXICSPIKES, MOVE_VENOSHOCK, MOVE_SCALD },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 20,
        .species = SPECIES_CORSOLA_G,
        .moves = { MOVE_SAFEGUARD, MOVE_ANCIENTPOWER, MOVE_REFLECT, MOVE_ATTRACT },
        .heldItem = ITEM_FOCUS_BAND,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 20,
        .species = SPECIES_CARKOL,
        .moves = { MOVE_WILLOWISP, MOVE_STEALTHROCK, MOVE_FLAMECHARGE, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_PASSHO_BERRY,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 21,
        .species = SPECIES_TOGETIC,
        .moves = { MOVE_THUNDERWAVE, MOVE_AIRSLASH, MOVE_FAIRYWIND, MOVE_MAGICALLEAF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Serene Grace
    }
};
// #endregion

// #region Heleo City
const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine_Hard_Divergent[] = {
    {
        .lvl = 26,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_WINGATTACK, MOVE_WATERPULSE, MOVE_SUPERSONIC, MOVE_PROTECT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 25,
        .species = SPECIES_FERROSEED,
        .moves = { MOVE_HARDEN, MOVE_INGRAIN, MOVE_PINMISSILE, MOVE_IRONHEAD },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 26,
        .species = SPECIES_CASTFORM,
        .moves = { MOVE_WEATHERBALL, MOVE_RAINDANCE, MOVE_WORKUP, MOVE_THUNDER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Forecast
    },
    {
        .lvl = 27,
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_BULLDOZE, MOVE_THUNDER, MOVE_THUNDERWAVE, MOVE_RAINDANCE },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine2_Hard_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_WINGATTACK, MOVE_WATERPULSE, MOVE_SOAK, MOVE_PROTECT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 32,
        .species = SPECIES_FERROSEED,
        .moves = { MOVE_IRONHEAD, MOVE_KNOCKOFF, MOVE_BULLETSEED, MOVE_LEECHSEED },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 33,
        .species = SPECIES_CASTFORM,
        .moves = { MOVE_WEATHERBALL, MOVE_RAINDANCE, MOVE_WORKUP, MOVE_THUNDER },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Forecast
    },
    {
        .lvl = 34,
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_BULLDOZE, MOVE_THUNDER, MOVE_THUNDERWAVE, MOVE_RAINDANCE },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine3_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_PELIPPER,
        .moves = { MOVE_AIRSLASH, MOVE_WATERPULSE, MOVE_SOAK, MOVE_PROTECT },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 40,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_IRONHEAD, MOVE_CURSE, MOVE_POWERWHIP, MOVE_LEECHSEED },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 41,
        .species = SPECIES_BEARTIC,
        .moves = { MOVE_SLASH, MOVE_AQUAJET, MOVE_AERIALACE, MOVE_BRICKBREAK },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 41,
        .species = SPECIES_SLIGGOO,
        .moves = { MOVE_ACIDARMOR, MOVE_ACIDSPRAY, MOVE_DRAGONPULSE, MOVE_WATERPULSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Hydration
    },
    {
        .lvl = 42,
        .species = SPECIES_HELIOLISK,
        .moves = { MOVE_BULLDOZE, MOVE_THUNDER, MOVE_THUNDERWAVE, MOVE_RAINDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Dry Skin
    }
};
// #endregion

// #region Daimyn City
const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance_Hard_Divergent[] = {
    {
        .lvl = 32,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_UTURN, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Shields Down
    },
    {
        .lvl = 32,
        .species = SPECIES_LANTURN,
        .moves = { MOVE_SOAK, MOVE_DISCHARGE, MOVE_BRINE, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 33,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND, MOVE_ENCORE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 34,
        .species = SPECIES_DUSCLOPS,
        .moves = { MOVE_PAINSPLIT, MOVE_TRICKROOM, MOVE_WILLOWISP, MOVE_HEX },
        .heldItem = ITEM_FOCUS_BAND,
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance2_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = { MOVE_REFLECT, MOVE_LIGHTSCREEN, MOVE_UTURN, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Shields Down
    },
    {
        .lvl = 40,
        .species = SPECIES_LANTURN,
        .moves = { MOVE_SUCKERPUNCH, MOVE_DISCHARGE, MOVE_BRINE, MOVE_VOLTSWITCH },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 41,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND, MOVE_ENCORE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
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
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_PAINSPLIT, MOVE_CURSE, MOVE_WILLOWISP, MOVE_HEX },
        .heldItem = ITEM_FOCUS_BAND,
        .ability = Ability_1 // Pressure
    }
};
// #endregion

// #region Route 11 South
const struct TrainerMonItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald_Hard_Divergent[] = {
    {
        .lvl = 36,
        .species = SPECIES_KROKOROK,
        .moves = { MOVE_CRUNCH, MOVE_DIG, MOVE_AQUATAIL, MOVE_TAUNT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 36,
        .species = SPECIES_SNEASEL,
        .moves = { MOVE_ICESHARD, MOVE_METALCLAW, MOVE_FAKEOUT, MOVE_ICEPUNCH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 37,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_IRONHEAD, MOVE_CURSE, MOVE_LEECHSEED, MOVE_POWERWHIP },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 37,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_DYNAMICPUNCH, MOVE_BULKUP, MOVE_ROCKSLIDE, MOVE_REVERSAL },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 39,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_POWERUPPUNCH, MOVE_SWAGGER, MOVE_SNARL, MOVE_PROTECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shed Skin
    }
};
// #endregion

// #region Laplaz Town
const struct TrainerMonItemCustomMoves sParty_LaplazTownGym_LeaderCasey_Hard_Divergent[] = {
    {
        .lvl = 40,
        .species = SPECIES_NINJASK,
        .moves = { MOVE_XSCISSOR, MOVE_BATONPASS, MOVE_PROTECT, MOVE_SWORDSDANCE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 40,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_POWERUPPUNCH, MOVE_SNARL, MOVE_DRAINPUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 41,
        .species = SPECIES_BEHEEYEM,
        .moves = { MOVE_CALMMIND, MOVE_STOREDPOWER, MOVE_COSMICPOWER, MOVE_THUNDERBOLT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize 
    },
    {
        .lvl = 41,
        .species = SPECIES_FALINKS,
        .moves = { MOVE_FIRSTIMPRESSION, MOVE_NORETREAT, MOVE_BRICKBREAK, MOVE_SMARTSTRIKE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Battle Armor
    },
    {
        .lvl = 42,
        .species = SPECIES_KINGDRA,
        .moves = { MOVE_FOCUSENERGY, MOVE_SCALD, MOVE_DRAGONBREATH, MOVE_ICYWIND },
        .heldItem = ITEM_SCOPE_LENS,
        .ability = Ability_2 // Sniper
    }
};
// #endregion

// #region Scalding Spa
const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena_Hard_Divergent[] = {
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
        .lvl = 43,
        .species = SPECIES_BEARTIC,
        .moves = { MOVE_THRASH, MOVE_ICICLECRASH, MOVE_LIQUIDATION, MOVE_NIGHTSLASH },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 43,
        .species = SPECIES_SLIGGOO,
        .moves = { MOVE_ROCKSLIDE, MOVE_DRAGONBREATH, MOVE_THUNDERBOLT, MOVE_MUDDYWATER },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};
// #endregion

// #region Bruccie Village & Calicin Bay
const struct TrainerMonItemCustomMoves sParty_BruccieVillageGym_LeaderAbby_Hard_Divergent[] = {
    {
        .lvl = 46,
        .species = SPECIES_RUNERIGUS,
        .moves = { MOVE_PROTECT, MOVE_DESTINYBOND, MOVE_SHADOWCLAW, MOVE_EARTHQUAKE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 46,
        .species = SPECIES_MALAMAR,
        .moves = { MOVE_SUPERPOWER, MOVE_HYPNOSIS, MOVE_PLUCK, MOVE_KNOCKOFF },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_1 // Contrary
    },
    {
        .lvl = 47,
        .species = SPECIES_JELLICENT_F,
        .moves = { MOVE_ACIDARMOR, MOVE_SCALD, MOVE_SHADOWBALL, MOVE_RECOVER },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Cursed Body
    },
    {
        .lvl = 47,
        .species = SPECIES_DARMANITAN_G,
        .moves = { MOVE_ICICLECRASH, MOVE_SUNNYDAY, MOVE_FIREPUNCH, MOVE_BULKUP },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Zen Mode
    },
    {
        .lvl = 48,
        .species = SPECIES_TREVENANT,
        .moves = { MOVE_WILLOWISP, MOVE_HORNLEECH, MOVE_HEX, MOVE_LEECHSEED },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    }
};

const struct TrainerMonItemCustomMoves sParty_CalicinBay_TeamPlutoYolena_Hard_Divergent[] = {
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
        .species = SPECIES_BEARTIC,
        .moves = { MOVE_THRASH, MOVE_ICICLECRASH, MOVE_LIQUIDATION, MOVE_NIGHTSLASH },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Swift Swim
    },
    {
        .lvl = 47,
        .species = SPECIES_SLIGGOO,
        .moves = { MOVE_ROCKSLIDE, MOVE_DRAGONPULSE, MOVE_THUNDER, MOVE_MUDDYWATER },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};
// #endregion

// #region Pluto HQ
const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B4F_TeamPlutoAdminIrene_Hard_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_NOCTOWL,
        .moves = { MOVE_ROOST, MOVE_MOONBLAST, MOVE_AIRSLASH, MOVE_NIGHTSHADE },
        .heldItem = ITEM_FAIRY_GEM,
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
        .lvl = 49,
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_MYSTICALFIRE, MOVE_SHADOWBALL, MOVE_PSYSHOCK, MOVE_DESTINYBOND },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 49,
        .species = SPECIES_SUDOWOODO,
        .moves = { MOVE_HEADSMASH, MOVE_LOWKICK, MOVE_WOODHAMMER, MOVE_ICEPUNCH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Rock Head
    },
    {
        .lvl = 50,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_FLAMETHROWER, MOVE_TOXIC, MOVE_VENOSHOCK },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Corrosion
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B7F_TeamPlutoAdminRonald_Hard_Divergent[] = {
    {
        .lvl = 48,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERFANG, MOVE_STEALTHROCK },
        .heldItem = ITEM_MUSCLE_BAND,
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
        .lvl = 49,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_FAKEOUT, MOVE_ICICLECRASH, MOVE_THROATCHOP, MOVE_AERIALACE },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 49,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_HAMMERARM, MOVE_BULKUP, MOVE_STONEEDGE, MOVE_REVERSAL },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 50,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_DRAGONDANCE, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_POISONJAB },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Shed Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis_Hard_Divergent[] = {
    {
        .lvl = 50,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_CLEARSMOG, MOVE_SPORE, MOVE_SYNTHESIS, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_BELLYDRUM, MOVE_DRAGONCLAW, MOVE_POISONJAB, MOVE_CLOSECOMBAT },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 50,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWPUNCH, MOVE_BRICKBREAK, MOVE_LEECHLIFE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 51,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_ROCKSLIDE, MOVE_IRONHEAD},
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 51,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 52,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_ICEFANG, MOVE_CRUNCH },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion

// #region Tsarvosa City
const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_StatsDojo_Kaito_Hard_Divergent[] = {
    {
        .lvl = 52,
        .species = SPECIES_GOGOAT,
        .moves = { MOVE_SEEDBOMB, MOVE_BULKUP, MOVE_HORNLEECH, MOVE_BULLDOZE },
        .ability = Ability_1 // Sap Sipper
    },
    {
        .lvl = 52,
        .species = SPECIES_GLALIE,
        .moves = { MOVE_PROTECT, MOVE_ICEFANG, MOVE_BULLDOZE, MOVE_SUBSTITUTE },
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 53,
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SHELLTRAP, MOVE_FLAMETHROWER, MOVE_OUTRAGE, MOVE_IRONDEFENSE },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 53,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_NIGHTSLASH, MOVE_IRONHEAD, MOVE_XSCISSOR },
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 54,
        .species = SPECIES_CONKELDURR,
        .moves = { MOVE_STONEEDGE, MOVE_HAMMERARM, MOVE_BULKUP, MOVE_FIREPUNCH },
        .ability = Ability_2 // Sheer Force
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin1_Hard_Divergent[] = {
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
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_ROOST, MOVE_DRILLPECK, MOVE_STEELWING, MOVE_IRONDEFENSE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_2 // Unnerve
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin2_Hard_Divergent[] = {
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
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_SHADOWBALL, MOVE_HIDDENPOWER, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BLASTOISE,
        .moves = { MOVE_WAVECRASH, MOVE_SHELLSMASH, MOVE_CRUNCH, MOVE_EARTHQUAKE },
        .heldItem = ITEM_BLASTOISINITE_G,
        .ability = Ability_Hidden // Rain Dish
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal1_Hard_Divergent[] = {
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
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SCALD, MOVE_PSYCHIC, MOVE_SLACKOFF, MOVE_TRICKROOM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_BRAVEBIRD, MOVE_UTURN, MOVE_TAUNT, MOVE_ROOST },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal2_Hard_Divergent[] = {
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
        .species = SPECIES_SHIINOTIC,
        .moves = { MOVE_SPORE, MOVE_STRENGTHSAP, MOVE_LEECHSEED, MOVE_MOONBLAST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Effect Spore
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYCHIC, MOVE_HIDDENPOWER, MOVE_PROTECT },
        .heldItem = ITEM_GARDEVOIRITE,
        .ability = Ability_Hidden // Telepathy
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Noam_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DITTO,
        .moves = { MOVE_TRANSFORM, MOVE_NONE, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STOUTLAND,
        .moves = { MOVE_RETALIATE, MOVE_FIREFANG, MOVE_PLAYROUGH, MOVE_ROAR },
        .heldItem = ITEM_SILK_SCARF,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_REVERSAL, MOVE_HEADBUTT, MOVE_REST, MOVE_SLEEPTALK },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CHANSEY,
        .moves = { MOVE_THUNDERWAVE, MOVE_SEISMICTOSS, MOVE_SOFTBOILED, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_CRUNCH, MOVE_FAKEOUT, MOVE_BODYSLAM, MOVE_WORKUP },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Scrappy
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ashley_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGCARGO,
        .moves = { MOVE_SHELLSMASH, MOVE_ROCKSLIDE, MOVE_RECOVER, MOVE_FLAMETHROWER },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_NASTYPLOT, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_MUDSHOT },
        .heldItem = ITEM_CHARCOAL,
        .ability = Ability_Hidden // Unnerve
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_FIREBLAST, MOVE_TOXIC, MOVE_DRAGONPULSE, MOVE_VENOSHOCK },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PYROAR,
        .moves = { MOVE_HYPERVOICE, MOVE_CRUNCH, MOVE_FLAMETHROWER, MOVE_NOBLEROAR },
        .heldItem = ITEM_METRONOME,
        .ability = Ability_1 // Rivalry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLAREON,
        .moves = { MOVE_FLAREBLITZ, MOVE_LASTRESORT, MOVE_DIG, MOVE_WILLOWISP },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_Hidden // Guts
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Chelsea_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BIBAREL,
        .moves = { MOVE_CURSE, MOVE_SUPERFANG, MOVE_AQUATAIL, MOVE_AQUAJET },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_RAINDANCE, MOVE_HURRICANE, MOVE_WATERFALL, MOVE_ICEFANG },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GASTRODON,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_BODYSLAM },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRAWDAUNT,
        .moves = { MOVE_LIQUIDATION, MOVE_NIGHTSLASH, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Adaptability
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_ICEBEAM, MOVE_RAINDANCE, MOVE_HYDROPUMP, MOVE_DRAGONPULSE },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_Hidden // Hydration
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Buddy_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CACTURNE,
        .moves = { MOVE_LEECHSEED, MOVE_SPIKYSHIELD, MOVE_SUCKERPUNCH, MOVE_SPIKES },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_TOXICSPIKES, MOVE_GIGADRAIN, MOVE_SWIFT, MOVE_VENOSHOCK },
        .heldItem = ITEM_POISON_BARB,
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRADILY,
        .moves = { MOVE_ANCIENTPOWER, MOVE_AMNESIA, MOVE_GIGADRAIN, MOVE_WRAP },
        .heldItem = ITEM_BIG_ROOT,
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CARNIVINE,
        .moves = { MOVE_SEEDBOMB, MOVE_STOCKPILE, MOVE_CRUNCH, MOVE_LEECHSEED },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DHELMISE,
        .moves = { MOVE_ANCHORSHOT, MOVE_WHIRLPOOL, MOVE_SHADOWCLAW, MOVE_LIQUIDATION },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Steelworker
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Gawain_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FALINKS,
        .moves = { MOVE_NORETREAT, MOVE_CLOSECOMBAT, MOVE_FIRSTIMPRESSION, MOVE_HEADBUTT },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PRIMEAPE,
        .moves = { MOVE_STOMPINGTANTRUM, MOVE_CROSSCHOP, MOVE_FOCUSENERGY, MOVE_SCREECH },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Anger Point
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIENSHAO,
        .moves = { MOVE_UTURN, MOVE_DRAINPUNCH, MOVE_BOUNCE, MOVE_DETECT },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BRELOOM,
        .moves = { MOVE_SEEDBOMB, MOVE_BRICKBREAK, MOVE_PROTECT, MOVE_STUNSPORE },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Poison Heal
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_SWORDSDANCE, MOVE_BRICKBREAK, MOVE_BRUTALSWING, MOVE_STEELWING },
        .heldItem = ITEM_LEEK,
        .ability = Ability_Hidden // Scrappy
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Skylar_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EMOLGA,
        .moves = { MOVE_VOLTSWITCH, MOVE_LIGHTSCREEN, MOVE_DISCHARGE, MOVE_ACROBATICS },
        .heldItem = ITEM_MAGNET,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOUCANNON,
        .moves = { MOVE_ROOST, MOVE_BULLETSEED, MOVE_ROCKBLAST, MOVE_DRILLPECK },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MANDIBUZZ,
        .moves = { MOVE_DARKPULSE, MOVE_AIRSLASH, MOVE_IRONDEFENSE, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Overcoat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MINIOR_SHIELD,
        .moves = { MOVE_SHELLSMASH, MOVE_POWERGEM, MOVE_IRONHEAD, MOVE_EXPLOSION },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Shields Down
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_AERIALACE, MOVE_FLAREBLITZ, MOVE_TAILWIND, MOVE_STEELWING },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Bella_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CROBAT,
        .moves = { MOVE_CROSSPOISON, MOVE_TAILWIND, MOVE_LEECHLIFE, MOVE_ACROBATICS },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Inflitrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_TOXIC, MOVE_GIGADRAIN, MOVE_CLEARSMOG, MOVE_ASTONISH },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_POISONJAB, MOVE_SUCKERPUNCH, MOVE_ROCKSLIDE, MOVE_PROTECT },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_Hidden // Poison Touch
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
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_BANEFULBUNKER, MOVE_TOXICSPIKES, MOVE_RECOVER, MOVE_SURF },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Merciless
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Flash_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RAICHU,
        .moves = { MOVE_NASTYPLOT, MOVE_DISCHARGE, MOVE_LIGHTSCREEN, MOVE_IRONTAIL },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GALVANTULA,
        .moves = { MOVE_THUNDER, MOVE_SUCKERPUNCH, MOVE_BUGBUZZ, MOVE_THUNDERWAVE },
        .heldItem = ITEM_ELECTRIC_GEM,
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = { MOVE_CHARGE, MOVE_DISCHARGE, MOVE_POISONJAB, MOVE_BOOMBURST },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Punk Rock
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JOLTEON,
        .moves = { MOVE_DISCHARGE, MOVE_SHADOWBALL, MOVE_HIDDENPOWER, MOVE_HYPERVOICE },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VIKAVOLT,
        .moves = { MOVE_CRUNCH, MOVE_THUNDERBOLT, MOVE_BUGBUZZ, MOVE_FLY },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Terra_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HIPPOWDON_F,
        .moves = { MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_ICEFANG, MOVE_YAWN },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_HEAVYSLAM, MOVE_HIGHHORSEPOWER, MOVE_STOMP, MOVE_STEALTHROCK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STUNFISK_G,
        .moves = { MOVE_SNAPTRAP, MOVE_MUDDYWATER, MOVE_BOUNCE, MOVE_IRONDEFENSE },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SWAMPERT,
        .moves = { MOVE_MUDDYWATER, MOVE_AMNESIA, MOVE_EARTHQUAKE, MOVE_COUNTER },
        .heldItem = ITEM_RINDO_BERRY,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLYGON,
        .moves = { MOVE_DRAGONCLAW, MOVE_DRAGONDANCE, MOVE_EARTHQUAKE, MOVE_BUGBUZZ },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Seifa_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MALAMAR,
        .moves = { MOVE_SUPERPOWER, MOVE_PSYCHOCUT, MOVE_NIGHTSLASH, MOVE_LIQUIDATION },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Contrary
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_ENCORE, MOVE_SAFEGUARD },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MR_RIME,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_MISTYTERRAIN, MOVE_FREEZEDRY, MOVE_PSYCHIC },
        .heldItem = ITEM_ICE_GEM,
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SLOWKING,
        .moves = { MOVE_SCALD, MOVE_PSYCHIC, MOVE_POWERGEM, MOVE_SHADOWBALL },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Oblivious
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ESPEON,
        .moves = { MOVE_MORNINGSUN, MOVE_PSYCHIC, MOVE_PSYCHUP, MOVE_SHADOWBALL },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Rocco_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LYCANROC_DUSK,
        .moves = { MOVE_ACCELEROCK, MOVE_STEALTHROCK, MOVE_CRUNCH, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_ROCK_GEM,
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_IRONHEAD, MOVE_IRONDEFENSE, MOVE_PROTECT, MOVE_BULLDOZE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_HEATCRASH, MOVE_TARSHOT, MOVE_SMACKDOWN, MOVE_BODYPRESS },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BARBARACLE,
        .moves = { MOVE_FLING, MOVE_CROSSCHOP, MOVE_RAZORSHELL, MOVE_SHELLSMASH },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STONJOURNER,
        .moves = { MOVE_ROCKSLIDE, MOVE_BODYSLAM, MOVE_SANDTOMB, MOVE_CURSE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Power Spot
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Janice_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CLOYSTER,
        .moves = { MOVE_ICICLESPEAR, MOVE_RAZORSHELL, MOVE_SHELLSMASH, MOVE_TOXICSPIKES },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AVALUGG,
        .moves = { MOVE_HAIL, MOVE_BLIZZARD, MOVE_RECOVER, MOVE_CRUNCH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_EARTHQUAKE, MOVE_ICESHARD, MOVE_ICEFANG, MOVE_KNOCKOFF },
        .heldItem = ITEM_MUSCLE_BAND,
        .ability = Ability_2 // Snow Cloak
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRABOMINABLE,
        .moves = { MOVE_ICEHAMMER, MOVE_CLOSECOMBAT, MOVE_AVALANCHE, MOVE_ZENHEADBUTT },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Iron Fist
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AURORUS,
        .moves = { MOVE_AURORAVEIL, MOVE_THUNDERWAVE, MOVE_FREEZEDRY, MOVE_ANCIENTPOWER },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_Hidden // Snow Warning
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Antoinette_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VESPIQUEN,
        .moves = { MOVE_DEFENDORDER, MOVE_ATTACKORDER, MOVE_POWERGEM, MOVE_AIRSLASH },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_BRICKBREAK, MOVE_MEGAHORN, MOVE_THROATCHOP, MOVE_SWORDSDANCE },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_BUGBITE, MOVE_BATONPASS },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ORBEETLE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_STRUGGLEBUG, MOVE_STICKYWEB },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_2 // Frisk
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FROSMOTH,
        .moves = { MOVE_STRUGGLEBUG, MOVE_AURORABEAM, MOVE_QUIVERDANCE, MOVE_STUNSPORE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Ice Scales
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ryu_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TURTONATOR,
        .moves = { MOVE_SMOG, MOVE_FLAMETHROWER, MOVE_SHELLSMASH, MOVE_DRAGONPULSE },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NOIVERN,
        .moves = { MOVE_DRAGONPULSE, MOVE_MOONLIGHT, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYRANTRUM,
        .moves = { MOVE_CRUNCH, MOVE_DRAGONCLAW, MOVE_FIREFANG, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DRAGONAIR,
        .moves = { MOVE_THUNDERWAVE, MOVE_DRAGONTAIL, MOVE_EXTREMESPEED, MOVE_WATERPULSE },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_1 // Shed Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_DRAGONDANCE, MOVE_DRAGONCLAW, MOVE_EARTHQUAKE, MOVE_POISONJAB },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Caspar_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JELLICENT,
        .moves = { MOVE_RECOVER, MOVE_WILLOWISP, MOVE_HEX, MOVE_SCALD },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_2 // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RUNERIGUS,
        .moves = { MOVE_SHADOWCLAW, MOVE_CURSE, MOVE_EARTHQUAKE, MOVE_ENERGYBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROTOM,
        .moves = { MOVE_REST, MOVE_DISCHARGE, MOVE_HEX, MOVE_WILLOWISP },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SHEDINJA,
        .moves = { MOVE_SHADOWBALL, MOVE_SHADOWSNEAK, MOVE_DIG, MOVE_SWORDSDANCE },
        .heldItem = ITEM_SAFETY_GOGGLES,
        .ability = Ability_1 // Wonder Guard
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_SHADOWBALL, MOVE_FUTURESIGHT, MOVE_THUNDERPUNCH, MOVE_ICEPUNCH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Frisk
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Darcy_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_BEATUP, MOVE_METALCLAW, MOVE_KNOCKOFF },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_HONECLAWS, MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_FIREFANG },
        .heldItem = ITEM_BLACK_GLASSES,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUK_A,
        .moves = { MOVE_GUNKSHOT, MOVE_CRUNCH, MOVE_TOXIC, MOVE_MINIMIZE },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_THIEVUL,
        .moves = { MOVE_TAILSLAP, MOVE_THIEF, MOVE_UTURN, MOVE_THUNDERFANG },
        // No held item to support thief
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BISHARP,
        .moves = { MOVE_SLASH, MOVE_IRONDEFENSE, MOVE_NIGHTSLASH, MOVE_FURYCUTTER },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_1 // Defiant
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Mason_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_SPIKES, MOVE_ROOST, MOVE_DRILLPECK, MOVE_STEELWING },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_POWERWHIP, MOVE_CURSE, MOVE_GYROBALL, MOVE_INGRAIN },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KLINKLANG,
        .moves = { MOVE_SHIFTGEAR, MOVE_GEARGRIND, MOVE_CHARGEBEAM, MOVE_METALSOUND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Clear Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAWILE,
        .moves = { MOVE_IRONHEAD, MOVE_PLAYROUGH, MOVE_BRICKBREAK, MOVE_ASTONISH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_AURASPHERE, MOVE_METEORMASH, MOVE_BONERUSH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Steadfast
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_GymTrainees_Faye_Hard_Divergent[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLORGES_YELLOW,
        .moves = { MOVE_MOONBLAST, MOVE_SYNTHESIS, MOVE_PETALDANCE, MOVE_MISTYTERRAIN },
        .heldItem = ITEM_GRASS_GEM,
        .ability = Ability_1 // Flower Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_STRANGESTEAM, MOVE_TOXIC, MOVE_SLUDGEBOMB, MOVE_HEATWAVE },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Neutralizing Gas
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_THUNDERWAVE, MOVE_AIRSLASH, MOVE_MOONBLAST, MOVE_CALMMIND },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SHIINOTIC,
        .moves = { MOVE_SPORE, MOVE_MOONBLAST, MOVE_GIGADRAIN, MOVE_STRENGTHSAP },
        .heldItem = ITEM_BIG_ROOT,
        .ability = Ability_2 // Effect Spore
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIMIKYU,
        .moves = { MOVE_WOODHAMMER, MOVE_SHADOWCLAW, MOVE_CHARM, MOVE_PLAYROUGH },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Disguise
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LeaderIris_Hard_Divergent[] = {
    {
        .lvl = 56,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_CURSE, MOVE_IRONHEAD, MOVE_POWERWHIP, MOVE_SPIKES },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 56,
        .species = SPECIES_CHANSEY,
        .moves = { MOVE_MINIMIZE, MOVE_THUNDERWAVE, MOVE_ECHOEDVOICE, MOVE_SEISMICTOSS },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 57,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_WATERFALL, MOVE_BULLDOZE, MOVE_IRONHEAD, MOVE_DRAGONDANCE },
        .heldItem = ITEM_CELL_BATTERY,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 57,
        .species = SPECIES_PALOSSAND,
        .moves = { MOVE_GIGADRAIN, MOVE_SHADOWBALL, MOVE_IRONDEFENSE, MOVE_SCORCHINGSANDS },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Water Compaction
    },
    {
        .lvl = 58,
        .species = SPECIES_GIGALITH,
        .moves = { MOVE_ROCKSLIDE, MOVE_FACADE, MOVE_IRONHEAD, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sand Stream
    },
};
// #endregion

// #region Daimyn City Restaurant event
const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Iris_Hard_Divergent[] = {
    {
        .lvl = 58,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_CURSE, MOVE_GYROBALL, MOVE_POWERWHIP, MOVE_SPIKES },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 59,
        .species = SPECIES_CHANSEY,
        .moves = { MOVE_MINIMIZE, MOVE_THUNDERWAVE, MOVE_SOFTBOILED, MOVE_SEISMICTOSS },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 60,
        .species = SPECIES_GIGALITH,
        .moves = { MOVE_ROCKSLIDE, MOVE_FACADE, MOVE_IRONHEAD, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sand Stream
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Stella_Hard_Divergent[] = {
    {
        .lvl = 57,
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_SCALD, MOVE_BANEFULBUNKER, MOVE_TOXICSPIKES, MOVE_VENOSHOCK },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 58,
        .species = SPECIES_COALOSSAL,
        .moves = { MOVE_TARSHOT, MOVE_HEATCRASH, MOVE_STONEEDGE, MOVE_WILLOWISP },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 59,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_THUNDERWAVE, MOVE_FOLLOWME, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Serene Grace
    },
};
// #endregion

// #region Uteya Village
const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_LeadersDennisAndDee_Hard_Divergent[] = {
    {
        .lvl = 62,
        .species = SPECIES_KLINKLANG,
        .moves = { MOVE_MAGNETICFLUX, MOVE_GEARUP, MOVE_ZAPCANNON, MOVE_GEARGRIND },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Minus
    },
    {
        .lvl = 62,
        .species = SPECIES_TOXTRICITY,
        .moves = { MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_OVERDRIVE, MOVE_BOOMBURST },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Plus
    },
    {
        .lvl = 61,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_FOLLOWME, MOVE_QUICKGUARD, MOVE_HEALPULSE, MOVE_BRICKBREAK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 63,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_HELPINGHAND, MOVE_BLIZZARD, MOVE_LIGHTSCREEN, MOVE_DISCHARGE },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 63,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_RAGEPOWDER, MOVE_INGRAIN, MOVE_TOXIC, MOVE_POLLENPUFF },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Effect Spore
    },
    {
        .lvl = 64,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCKSLIDE, MOVE_POISONJAB, MOVE_DRAGONCLAW },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Rough Skin
    }
};

// #endregion

// #region Ascension Tower
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Hannah_Hard_Divergent[] = {
    {
        .lvl = 67,
        .species = SPECIES_WHIMSICOTT,
        .moves = { MOVE_LEECHSEED, MOVE_SUBSTITUTE, MOVE_COTTONGUARD, MOVE_GIGADRAIN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 67,
        .species = SPECIES_GASTRODON_EAST,
        .moves = { MOVE_MUDDYWATER, MOVE_EARTHPOWER, MOVE_RECOVER, MOVE_SLUDGEWAVE },
        .heldItem = ITEM_BRIGHT_POWDER,
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 67,
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_CLOSECOMBAT, MOVE_MEGAHORN, MOVE_DOUBLEEDGE, MOVE_NIGHTSLASH },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 68,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_ROOST, MOVE_TAILWIND, MOVE_FLAREBLITZ, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 68,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE, MOVE_TRICK },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 69,
        .species = SPECIES_MAWILE,
        .moves = { MOVE_IRONHEAD, MOVE_PLAYROUGH, MOVE_ICEPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_MAWILITE,
        .ability = Ability_2 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Lucas_Hard_Divergent[] = {
    {
        .lvl = 68,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_SPIKES, MOVE_POWERWHIP, MOVE_GYROBALL },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 68,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_TOXIC, MOVE_VENOSHOCK, MOVE_FLAMETHROWER },
        .heldItem = ITEM_FIRE_GEM,
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 68,
        .species = SPECIES_FROSLASS,
        .moves = { MOVE_DESTINYBOND, MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_FROSTBREATH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 69,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AIRSLASH, MOVE_ROOST, MOVE_THUNDERWAVE, MOVE_AURASPHERE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 69,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_NOBLEROAR, MOVE_ICEPUNCH, MOVE_CLOSECOMBAT, MOVE_OUTRAGE },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 70,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Jenna_Hard_Divergent[] = {
    {
        .lvl = 69,
        .species = SPECIES_TOXAPEX,
        .moves = { MOVE_TOXICSPIKES, MOVE_BANEFULBUNKER, MOVE_LIQUIDATION, MOVE_RECOVER },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 69,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_NIGHTSLASH, MOVE_IRONHEAD, MOVE_SWORDSDANCE, MOVE_PSYCHOCUT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 69,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_QUIVERDANCE, MOVE_BUGBUZZ, MOVE_HURRICANE },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 70,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 70,
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_ICESHARD, MOVE_EARTHQUAKE, MOVE_ICICLECRASH, MOVE_STONEEDGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 71,
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_FAKEOUT, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_FACADE },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_Hidden // Inner Focus
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_Thomas_Hard_Divergent[] = {
    {
        .lvl = 70,
        .species = SPECIES_VENUSAUR,
        .moves = { MOVE_LEECHSEED, MOVE_SLUDGEBOMB, MOVE_SYNTHESIS, MOVE_GIGADRAIN },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 70,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_STONEEDGE, MOVE_OUTRAGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 70,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_TOXIC, MOVE_SNARL, MOVE_MEANLOOK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 71,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 71,
        .species = SPECIES_ROTOM_WASH,
        .moves = { MOVE_REST, MOVE_WILLOWISP, MOVE_VOLTSWITCH, MOVE_HYDROPUMP },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 72,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SLACKOFF, MOVE_CALMMIND, MOVE_PSYSHOCK, MOVE_SCALD },
        .heldItem = ITEM_SLOWBRONITE,
        .ability = Ability_1 // Oblivious
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_Champion_Selene_Hard_Divergent[] = {
    {
        .lvl = 72,
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
    }
};

// #endregion

// #region Elite Four Rematches
const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_HannahRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_HERACROSS,
        .moves = { MOVE_CLOSECOMBAT, MOVE_MEGAHORN, MOVE_DOUBLEEDGE, MOVE_NIGHTSLASH },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 74,
        .species = SPECIES_TALONFLAME,
        .moves = { MOVE_ROOST, MOVE_TAILWIND, MOVE_FLAREBLITZ, MOVE_BRAVEBIRD },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 74,
        .species = SPECIES_COFAGRIGUS,
        .moves = { MOVE_WILLOWISP, MOVE_HEX, MOVE_DARKPULSE, MOVE_TRICK },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 75,
        .species = SPECIES_MAWILE,
        .moves = { MOVE_IRONHEAD, MOVE_PLAYROUGH, MOVE_ICEPUNCH, MOVE_SWORDSDANCE },
        .heldItem = ITEM_MAWILITE,
        .ability = Ability_2 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_LucasRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_FROSLASS,
        .moves = { MOVE_DESTINYBOND, MOVE_WILLOWISP, MOVE_SHADOWBALL, MOVE_FROSTBREATH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    },
    {
        .lvl = 74,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_AIRSLASH, MOVE_ROOST, MOVE_THUNDERWAVE, MOVE_AURASPHERE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 74,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_NOBLEROAR, MOVE_ICEPUNCH, MOVE_CLOSECOMBAT, MOVE_OUTRAGE },
        .heldItem = ITEM_WHITE_HERB,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 75,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_EARTHQUAKE, MOVE_WATERFALL, MOVE_CRUNCH, MOVE_DRAGONDANCE },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_JennaRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_QUIVERDANCE, MOVE_BUGBUZZ, MOVE_HURRICANE },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 74,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_DAZZLINGGLEAM, MOVE_MYSTICALFIRE },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 74,
        .species = SPECIES_MAMOSWINE,
        .moves = { MOVE_ICESHARD, MOVE_EARTHQUAKE, MOVE_ICICLECRASH, MOVE_STONEEDGE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 75,
        .species = SPECIES_KANGASKHAN,
        .moves = { MOVE_FAKEOUT, MOVE_POWERUPPUNCH, MOVE_CRUNCH, MOVE_FACADE },
        .heldItem = ITEM_KANGASKHANITE,
        .ability = Ability_Hidden // Inner Focus
    }
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_EliteFour_ThomasRematch_Hard_Divergent[] = {
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
        .lvl = 73,
        .species = SPECIES_UMBREON,
        .moves = { MOVE_MOONLIGHT, MOVE_TOXIC, MOVE_SNARL, MOVE_MEANLOOK },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 74,
        .species = SPECIES_INFERNAPE,
        .moves = { MOVE_MACHPUNCH, MOVE_FLAREBLITZ, MOVE_THUNDERPUNCH, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 74,
        .species = SPECIES_ROTOM_WASH,
        .moves = { MOVE_REST, MOVE_WILLOWISP, MOVE_VOLTSWITCH, MOVE_HYDROPUMP },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 75,
        .species = SPECIES_SLOWBRO,
        .moves = { MOVE_SLACKOFF, MOVE_CALMMIND, MOVE_PSYSHOCK, MOVE_SCALD },
        .heldItem = ITEM_SLOWBRONITE,
        .ability = Ability_1 // Oblivious
    }
};
// #endregion

// #region Title Defense
const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Rival_Vaporeon_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_CORVIKNIGHT,
        .moves = { MOVE_DRILLPECK, MOVE_IRONDEFENSE, MOVE_BODYPRESS, MOVE_ROOST },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Mirror Armor
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_ICESHARD, MOVE_POISONJAB, MOVE_ICICLECRASH, MOVE_FLING },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 78,
        .species = SPECIES_MUDSDALE,
        .moves = { MOVE_REST, MOVE_HIGHHORSEPOWER, MOVE_HEAVYSLAM, MOVE_SUPERPOWER },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 78,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_LEAFBLADE, MOVE_SWORDSDANCE, MOVE_METEORBEAM, MOVE_KNOCKOFF },
        .heldItem = ITEM_LEEK,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 79,
        .species = SPECIES_AMPHAROS,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_DISCHARGE, MOVE_COTTONGUARD, MOVE_DRAGONPULSE },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
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
        .species = SPECIES_RATTATA,
        .moves = { MOVE_SUPERFANG, MOVE_SUCKERPUNCH, MOVE_FACADE, MOVE_THUNDERBOLT },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 78,
        .species = SPECIES_RATTATA_A,
        .moves = { MOVE_PURSUIT, MOVE_CRUNCH, MOVE_SUPERFANG, MOVE_DOUBLEEDGE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Gluttony
    },
    {
        .lvl = 78,
        .species = SPECIES_RATTATA,
        .moves = { MOVE_QUICKATTACK, MOVE_LASTRESORT, MOVE_NONE, MOVE_NONE },
        .heldItem = ITEM_WIDE_LENS,
        .ability = Ability_Hidden // Hustle
    },
    {
        .lvl = 78,
        .species = SPECIES_RATTATA_A,
        .moves = { MOVE_TOXIC, MOVE_UTURN, MOVE_WILDCHARGE, MOVE_SHADOWBALL },
        .heldItem = ITEM_CHOPLE_BERRY,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 79,
        .species = SPECIES_RATICATE,
        .moves = { MOVE_DOUBLEEDGE, MOVE_QUICKATTACK, MOVE_CRUNCH, MOVE_PLUCK },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 80,
        .species = SPECIES_RATICATE_A,
        .moves = { MOVE_SUCKERPUNCH, MOVE_UTURN, MOVE_WILDCHARGE, MOVE_SHADOWCLAW },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Hustle
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_WithVictini_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_SKARMORY,
        .moves = { MOVE_BRAVEBIRD, MOVE_SPIKES, MOVE_IRONHEAD, MOVE_ROOST },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 78,
        .species = SPECIES_ROSERADE,
        .moves = { MOVE_TOXICSPIKES, MOVE_LEECHSEED, MOVE_GIGADRAIN, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Poison Point
    },
    {
        .lvl = 78,
        .species = SPECIES_LOPUNNY,
        .moves = { MOVE_HIGHJUMPKICK, MOVE_FAKEOUT, MOVE_RETURN, MOVE_ICEPUNCH },
        .heldItem = ITEM_LOPUNNITE,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 78,
        .species = SPECIES_SYLVEON,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYSHOCK, MOVE_WISH, MOVE_PROTECT },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Pixelate
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
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Selene_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_POWERWHIP, MOVE_GYROBALL, MOVE_LEECHSEED, MOVE_KNOCKOFF },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 78,
        .species = SPECIES_NIDOKING,
        .moves = { MOVE_EARTHPOWER, MOVE_SLUDGEWAVE, MOVE_THUNDERBOLT, MOVE_SHADOWBALL },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 78,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_HYPERVOICE, MOVE_PSYSHOCK, MOVE_CALMMIND, MOVE_THUNDERBOLT },
        .heldItem = ITEM_GARDEVOIRITE,
        .ability = Ability_2 // Trace
    },
    {
        .lvl = 78,
        .species = SPECIES_VOLCARONA,
        .moves = { MOVE_FIERYDANCE, MOVE_BUGBUZZ, MOVE_QUIVERDANCE, MOVE_HURRICANE },
        .heldItem = ITEM_HEAVY_DUTY_BOOTS,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 79,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_DRAGONDANCE, MOVE_FIREPUNCH, MOVE_DRAGONCLAW, MOVE_ROOST },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Multiscale
    },
    {
        .lvl = 80,
        .species = SPECIES_GRENINJA,
        .moves = { MOVE_ICEBEAM, MOVE_SCALD, MOVE_DARKPULSE, MOVE_HIDDENPOWER },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Battle Bond
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Alistair_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_CROSSPOISON, MOVE_HAZE },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 78,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_SPORE, MOVE_TOXIC, MOVE_BODYSLAM, MOVE_PROTECT },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 78,
        .species = SPECIES_GALLADE,
        .moves = { MOVE_CLOSECOMBAT, MOVE_LEAFBLADE, MOVE_PSYCHOCUT, MOVE_SWORDSDANCE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Justified
    },
    {
        .lvl = 78,
        .species = SPECIES_SHARPEDO,
        .moves = { MOVE_AQUAJET, MOVE_LIQUIDATION, MOVE_CRUNCH, MOVE_ICEFANG },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 79,
        .species = SPECIES_HOUNDOOM,
        .moves = { MOVE_DESTINYBOND, MOVE_DARKPULSE, MOVE_FLAMETHROWER, MOVE_THUNDERFANG },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
    },
    {
        .lvl = 80,
        .species = SPECIES_EMBOAR,
        .moves = { MOVE_HEADSMASH, MOVE_FLAREBLITZ, MOVE_WILDCHARGE, MOVE_TAKEDOWN },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Reckless
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Hawthorne_Hard_Divergent[] = {
    {
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
        .species = SPECIES_THIEVUL,
        .moves = { MOVE_PARTINGSHOT, MOVE_SUCKERPUNCH, MOVE_KNOCKOFF, MOVE_PLAYROUGH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Unburden
    },
    {
        .lvl = 78,
        .species = SPECIES_WOBBUFFET,
        .moves = { MOVE_ENCORE, MOVE_COUNTER, MOVE_MIRRORCOAT, MOVE_DESTINYBOND },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 78,
        .species = SPECIES_TOXICROAK,
        .moves = { MOVE_SLUDGEBOMB, MOVE_DRAINPUNCH, MOVE_TOXIC, MOVE_THUNDERPUNCH },
        .heldItem = ITEM_PAYAPA_BERRY,
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 78,
        .species = SPECIES_CARNIVINE,
        .moves = { MOVE_CRUNCH, MOVE_SEEDBOMB, MOVE_STOCKPILE, MOVE_INGRAIN },
        .heldItem = ITEM_BIG_ROOT,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 79,
        .species = SPECIES_COPPERAJAH,
        .moves = { MOVE_PLAYROUGH, MOVE_IRONHEAD, MOVE_HEAVYSLAM, MOVE_IRONDEFENSE },
        .heldItem = ITEM_COPPERITE,
        .ability = Ability_1 // Sheer Force
    },
    {
        .lvl = 80,
        .species = SPECIES_WEEZING_G,
        .moves = { MOVE_HEATWAVE, MOVE_SLUDGEBOMB, MOVE_EXPLOSION, MOVE_STRANGESTEAM },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Neutralizing Gas
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ena_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_PAINSPLIT, MOVE_WILLOWISP, MOVE_SHADOWSNEAK, MOVE_FUTURESIGHT },
        .heldItem = ITEM_LUM_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 78,
        .species = SPECIES_BASTIODON,
        .moves = { MOVE_IRONHEAD, MOVE_FACADE, MOVE_ROCKTOMB, MOVE_EARTHQUAKE },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Soundproof
    },
    {
        .lvl = 78,
        .species = SPECIES_CROBAT,
        .moves = { MOVE_CROSSPOISON, MOVE_ACROBATICS, MOVE_LEECHLIFE, MOVE_MEANLOOK },
        .heldItem = ITEM_FLYING_GEM,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 78,
        .species = SPECIES_PYROAR,
        .moves = { MOVE_OVERHEAT, MOVE_HYPERVOICE, MOVE_CRUNCH, MOVE_WILDCHARGE },
        .heldItem = ITEM_FIRE_GEM,
        .ability = Ability_1 // Rivalry
    },
    {
        .lvl = 79,
        .species = SPECIES_LAPRAS,
        .moves = { MOVE_PERISHSONG, MOVE_ICEBEAM, MOVE_DRAGONPULSE, MOVE_SCALD },
        .heldItem = ITEM_LAPRASITE,
        .ability = Ability_1 // Water Absorb
    },
    {
        .lvl = 80,
        .species = SPECIES_SCOLIPEDE,
        .moves = { MOVE_PROTECT, MOVE_MEGAHORN, MOVE_TOXIC, MOVE_VENOSHOCK },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Speed Boost
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Felix_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_KLEFKI,
        .moves = { MOVE_THUNDERWAVE, MOVE_REFLECT, MOVE_SPIKES, MOVE_PLAYROUGH },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 78,
        .species = SPECIES_EXEGGUTOR_A,
        .moves = { MOVE_SEEDBOMB, MOVE_DRAGONHAMMER, MOVE_PSYSHOCK, MOVE_CURSE },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 78,
        .species = SPECIES_CHANDELURE,
        .moves = { MOVE_SHADOWBALL, MOVE_WILLOWISP, MOVE_FLAMETHROWER, MOVE_ENERGYBALL },
        .heldItem = ITEM_CHARCOAL,
        .ability = Ability_1 // Flash Fire
    },
    {
        .lvl = 78,
        .species = SPECIES_PORYGON_Z,
        .moves = { MOVE_TRIATTACK, MOVE_THUNDERBOLT, MOVE_PSYSHOCK, MOVE_BLIZZARD },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_1 // Adaptability
    },
    {
        .lvl = 79,
        .species = SPECIES_TYRANITAR,
        .moves = { MOVE_STONEEDGE, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_THUNDERFANG },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 80,
        .species = SPECIES_MILOTIC,
        .moves = { MOVE_RECOVER, MOVE_SCALD, MOVE_ICEBEAM, MOVE_DRAGONBREATH },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Marvel Scale
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Collin_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_CACTURNE,
        .moves = { MOVE_SPIKYSHIELD, MOVE_DRAINPUNCH, MOVE_NEEDLEARM, MOVE_FEINTATTACK },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Sand Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_CENTISKORCH,
        .moves = { MOVE_FIRELASH, MOVE_LUNGE, MOVE_COIL, MOVE_CRUNCH },
        .heldItem = ITEM_CENTISKORITE,
        .ability = Ability_1 // Flash Fire
    },
    {
        .lvl = 78,
        .species = SPECIES_ROTOM_FROST,
        .moves = { MOVE_DISCHARGE, MOVE_BLIZZARD, MOVE_DOUBLETEAM, MOVE_OMINOUSWIND },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 78,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_SMARTSTRIKE, MOVE_SLASH, MOVE_EARTHQUAKE, MOVE_ROCKSLIDE },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Sand Force
    },
    {
        .lvl = 79,
        .species = SPECIES_EMPOLEON,
        .moves = { MOVE_AQUAJET, MOVE_ICEBEAM, MOVE_WATERPLEDGE, MOVE_FLASHCANNON },
        .heldItem = ITEM_MYSTIC_WATER,
        .ability = Ability_1 // Torrent
    },
    {
        .lvl = 80,
        .species = SPECIES_SIRFETCHD,
        .moves = { MOVE_SWORDSDANCE, MOVE_METEORASSAULT, MOVE_KNOCKOFF, MOVE_FURYCUTTER },
        .heldItem = ITEM_LEEK, // Stick, in game
        .ability = Ability_1 // Steadfast
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Crystal_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_GALVANTULA,
        .moves = { MOVE_GASTROACID, MOVE_SUCKERPUNCH, MOVE_DISCHARGE, MOVE_SIGNALBEAM },
        .heldItem = ITEM_SILVER_POWDER,
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 78,
        .species = SPECIES_TOGEKISS,
        .moves = { MOVE_ENCORE, MOVE_EXTRASENSORY, MOVE_AURASPHERE, MOVE_YAWN },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 78,
        .species = SPECIES_GARCHOMP,
        .moves = { MOVE_DRAGONRUSH, MOVE_CRUNCH, MOVE_DRAGONCLAW, MOVE_EARTHQUAKE },
        .heldItem = ITEM_DRAGON_FANG,
        .ability = Ability_1 // Sand Veil
    },
    {
        .lvl = 78,
        .species = SPECIES_DRAGONITE,
        .moves = { MOVE_DRAGONDANCE, MOVE_DRAGONTAIL, MOVE_ROOST, MOVE_AQUATAIL },
        .heldItem = ITEM_MYSTIC_WATER,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 79,
        .species = SPECIES_GARDEVOIR,
        .moves = { MOVE_MAGICALLEAF, MOVE_PSYCHIC, MOVE_MOONBLAST, MOVE_CALMMIND },
        .heldItem = ITEM_SAFETY_GOGGLES,
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 80,
        .species = SPECIES_BLAZIKEN,
        .moves = { MOVE_BRICKBREAK, MOVE_AERIALACE, MOVE_BLAZEKICK, MOVE_FLAREBLITZ },
        .heldItem = ITEM_BLAZIKENITE,
        .ability = Ability_1 // Blaze
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Irene_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_NOCTOWL,
        .moves = { MOVE_EXTRASENSORY, MOVE_MOONBLAST, MOVE_ROOST, MOVE_AIRSLASH },
        .heldItem = ITEM_FAIRY_GEM,
        .ability = Ability_Hidden // Tinted Lens
    },
    {
        .lvl = 78,
        .species = SPECIES_MUK_A,
        .moves = { MOVE_MINIMIZE, MOVE_KNOCKOFF, MOVE_TOXIC, MOVE_POISONJAB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 78,
        .species = SPECIES_MISMAGIUS,
        .moves = { MOVE_MYSTICALFIRE, MOVE_POWERGEM, MOVE_NASTYPLOT, MOVE_SHADOWBALL },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 78,
        .species = SPECIES_KINGDRA,
        .moves = { MOVE_DRAGONPULSE, MOVE_HYDROPUMP, MOVE_ICEBEAM, MOVE_FLASHCANNON },
        .heldItem = ITEM_CHOICE_SPECS,
        .ability = Ability_2 // Sniper
    },
    {
        .lvl = 79,
        .species = SPECIES_HATTERENE,
        .moves = { MOVE_DAZZLINGGLEAM, MOVE_PSYCHIC, MOVE_CALMMIND, MOVE_THUNDERWAVE },
        .heldItem = ITEM_HATTERITE,
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 80,
        .species = SPECIES_SALAZZLE,
        .moves = { MOVE_NASTYPLOT, MOVE_FLAMETHROWER, MOVE_DRAGONPULSE, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Corrosion
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Ronald_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_KROOKODILE,
        .moves = { MOVE_SANDSTORM, MOVE_EARTHQUAKE, MOVE_CRUNCH, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 78,
        .species = SPECIES_FERROTHORN,
        .moves = { MOVE_LEECHSEED, MOVE_CURSE, MOVE_GYROBALL, MOVE_EXPLOSION },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 78,
        .species = SPECIES_LUCARIO,
        .moves = { MOVE_EXTREMESPEED, MOVE_SWORDSDANCE, MOVE_METEORMASH, MOVE_CLOSECOMBAT },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 78,
        .species = SPECIES_WEAVILE,
        .moves = { MOVE_SCREECH, MOVE_NIGHTSLASH, MOVE_ICESHARD, MOVE_ICICLECRASH },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 79,
        .species = SPECIES_GLALIE,
        .moves = { MOVE_CRUNCH, MOVE_BODYSLAM, MOVE_FREEZEDRY, MOVE_LIGHTSCREEN },
        .heldItem = ITEM_GLALITITE,
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 80,
        .species = SPECIES_SCRAFTY,
        .moves = { MOVE_POISONJAB, MOVE_DRAINPUNCH, MOVE_CRUNCH, MOVE_POWERUPPUNCH },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_1 // Shed Skin
    },
};

const struct TrainerMonItemCustomMoves sParty_AscensionTower_TitleDefense_Kurtis_Hard_Divergent[] = {
    {
        .lvl = 78,
        .species = SPECIES_AMOONGUSS,
        .moves = { MOVE_CLEARSMOG, MOVE_SPORE, MOVE_SYNTHESIS, MOVE_SLUDGEBOMB },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 78,
        .species = SPECIES_KOMMO_O,
        .moves = { MOVE_BELLYDRUM, MOVE_DRAGONCLAW, MOVE_POISONJAB, MOVE_DRAINPUNCH },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 78,
        .species = SPECIES_DUSKNOIR,
        .moves = { MOVE_WILLOWISP, MOVE_SHADOWPUNCH, MOVE_BRICKBREAK, MOVE_LEECHLIFE },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 78,
        .species = SPECIES_BISHARP,
        .moves = { MOVE_RETALIATE, MOVE_SWORDSDANCE, MOVE_IRONHEAD, MOVE_SUCKERPUNCH },
        .heldItem = ITEM_NORMAL_GEM,
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 79,
        .species = SPECIES_EXCADRILL,
        .moves = { MOVE_EARTHQUAKE, MOVE_SWORDSDANCE, MOVE_ROCKSLIDE, MOVE_IRONHEAD },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 80,
        .species = SPECIES_GYARADOS,
        .moves = { MOVE_DRAGONDANCE, MOVE_WATERFALL, MOVE_ICEFANG, MOVE_CRUNCH },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion
// #region Postgame
// Identical to normal mode but for some reason will crash if not defined
const struct TrainerMonNoItemCustomMoves sParty_HeleoCity_NurseBrianne_Hard_Divergent[] = {
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
