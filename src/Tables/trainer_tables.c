#include "../defines_battle.h"
#include "../../include/battle.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/opponents.h"
#include "../../include/constants/battle_ai.h"
#include "../../include/constants/items.h"
#include "../../include/easy_text.h"
#include "../../include/new/build_pokemon_2.h"

// See battle.h for a list of struct types that can be used

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

// #region Trainer Structs

// #region Important trainers
const struct TrainerMonNoItemDefaultMoves sParty_Rival1[] = {
    { .iv = 0, .lvl = 5, .species = SPECIES_EEVEE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Rival2[] = {
    { .lvl = 12, .species = SPECIES_ROOKIDEE },
    { .lvl = 14, .species = SPECIES_EEVEE },
};

const struct TrainerMonNoItemCustomMoves sParty_PartnerRival1[] = {
    {
        .lvl = 13,
        .species = SPECIES_ROOKIDEE,
        .moves = {
            MOVE_FURYATTACK,
            MOVE_HONECLAWS,
            MOVE_PECK,
            MOVE_ROCKSMASH
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 15,
        .species = SPECIES_EEVEE,
        .moves = {
            MOVE_QUICKATTACK,
            MOVE_HELPINGHAND,
            MOVE_TAILWHIP,
            MOVE_SANDATTACK
        },
        .ability = Ability_2 // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival3[] = {
    {
        .lvl = 30,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_TAUNT,
            MOVE_PLUCK,
            MOVE_TAILWIND,
            MOVE_FURYATTACK
        },
        .ability = Ability_1 // Keen Eye 
    },
    {
        .lvl = 30,
        .species = SPECIES_FLAAFFY,
        .moves = {
            MOVE_ELECTROBALL,
            MOVE_THUNDERWAVE,
            MOVE_FIREPUNCH,
            MOVE_TAKEDOWN
        },
        .ability = Ability_1 // Static 
    },
    {
        .lvl = 32,
        .species = SPECIES_EEVEE,
        .moves = {
            MOVE_BITE,
            MOVE_COVET,
            MOVE_DOUBLEKICK,
            MOVE_BABYDOLLEYES
        },
        .heldItem = ITEM_BERRY_JUICE,
        .ability = Ability_2 // Adaptability
    }
};

const struct TrainerMonItemCustomMoves sParty_Casey1[] = {
    {
        .lvl = 15,
        .species = SPECIES_ELGYEM,
        .moves = {
            MOVE_CONFUSION,
            MOVE_GROWL,
            MOVE_IMPRISON,
            MOVE_DISABLE
        },
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 17,
        .species = SPECIES_HORSEA,
        .moves = {
            MOVE_OCTAZOOKA,
            MOVE_SMOKESCREEN,
            MOVE_FOCUSENERGY,
            MOVE_SCALESHOT
        },
        .heldItem = ITEM_ORAN_BERRY,
        .ability = Ability_2 // Sniper
    }
};

const struct TrainerMonItemCustomMoves sParty_Casey2[] = {
    {
        .lvl = 33,
        .species = SPECIES_ELGYEM,
        .moves = {
            MOVE_THUNDERBOLT,
            MOVE_PSYCHIC,
            MOVE_COSMICPOWER,
            MOVE_AGILITY
        },
        .ability = Ability_2 // Synchronize
    },
    {
        .lvl = 35,
        .species = SPECIES_SEADRA,
        .moves = {
            MOVE_FOCUSENERGY,
            MOVE_MUDDYWATER,
            MOVE_ICYWIND,
            MOVE_CLEARSMOG
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Sniper
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Vaporeon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_VAPOREON,
        .moves = {
            MOVE_WATERPULSE,
            MOVE_AURORABEAM,
            MOVE_CHARM,
            MOVE_RAINDANCE
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Jolteon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_JOLTEON,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_THUNDERBOLT,
            MOVE_SHADOWBALL,
            MOVE_DOUBLEKICK
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Flareon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_FLAREON,
        .moves = {
            MOVE_FIREFANG,
            MOVE_BITE,
            MOVE_SUNNYDAY,
            MOVE_WILLOWISP
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Espeon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_PSYBEAM,
            MOVE_MORNINGSUN,
            MOVE_CALMMIND,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Umbreon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_UMBREON,
        .moves = {
            MOVE_SNARL,
            MOVE_MOONLIGHT,
            MOVE_CONFUSERAY,
            MOVE_DIG
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Leafeon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_LEAFEON,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_RAZORLEAF,
            MOVE_AERIALACE,
            MOVE_ATTRACT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Glaceon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_GLACEON,
        .moves = {
            MOVE_HAIL,
            MOVE_AURORAVEIL,
            MOVE_ICEFANG,
            MOVE_ROCKSMASH
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Sylveon[] = {
    {
        .lvl = 34,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 34,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 36,
        .species = SPECIES_SYLVEON,
        .moves = {
            MOVE_DRAININGKISS,
            MOVE_COVET,
            MOVE_LIGHTSCREEN,
            MOVE_ATTRACT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Route11_Alistair[] = {
    {
        .lvl = 34,
        .species = SPECIES_GOLBAT,
        .moves = {
            MOVE_WINGATTACK,
            MOVE_POISONFANG,
            MOVE_ROOST,
            MOVE_MEANLOOK
        },
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 34,
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_CLEARSMOG,
            MOVE_TOXIC,
            MOVE_VENOSHOCK
        },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 36,
        .species = SPECIES_SHARPEDO,
        .moves = {
            MOVE_ICEFANG,
            MOVE_CRUNCH,
            MOVE_AQUAJET,
            MOVE_FOCUSENERGY
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Speed Boost
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Vaporeon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_VAPOREON,
        .moves = {
            MOVE_WATERPULSE,
            MOVE_AURORABEAM,
            MOVE_CHARM,
            MOVE_RAINDANCE
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Jolteon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_JOLTEON,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_THUNDERBOLT,
            MOVE_SHADOWBALL,
            MOVE_DOUBLEKICK
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Flareon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_FLAREON,
        .moves = {
            MOVE_FIREFANG,
            MOVE_BITE,
            MOVE_SUNNYDAY,
            MOVE_WILLOWISP
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Espeon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_PSYBEAM,
            MOVE_MORNINGSUN,
            MOVE_CALMMIND,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Umbreon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_UMBREON,
        .moves = {
            MOVE_SNARL,
            MOVE_MOONLIGHT,
            MOVE_CONFUSERAY,
            MOVE_DIG
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Leafeon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_LEAFEON,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_RAZORLEAF,
            MOVE_AERIALACE,
            MOVE_ATTRACT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Glaceon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_GLACEON,
        .moves = {
            MOVE_HAIL,
            MOVE_AURORAVEIL,
            MOVE_ICEFANG,
            MOVE_ROCKSMASH
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival4_Sylveon[] = {
    {
        .lvl = 36,
        .species = SPECIES_CORVISQUIRE,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROCKSMASH,
            MOVE_TAILWIND,
            MOVE_TAUNT
        },
        .ability = Ability_1 // Keen Eye
    },
    {
        .lvl = 36,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_POWERGEM,
            MOVE_ELECTROBALL
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 37,
        .species = SPECIES_SYLVEON,
        .moves = {
            MOVE_DRAININGKISS,
            MOVE_COVET,
            MOVE_LIGHTSCREEN,
            MOVE_ATTRACT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Vaporeon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_VAPOREON,
        .moves = {
            MOVE_ACIDARMOR,
            MOVE_ICEBEAM,
            MOVE_MUDDYWATER,
            MOVE_RAINDANCE
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Water Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Jolteon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_JOLTEON,
        .moves = {
            MOVE_DISCHARGE,
            MOVE_RAINDANCE,
            MOVE_WEATHERBALL,
            MOVE_SHADOWBALL
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Volt Absorb
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Flareon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_FLAREON,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_DIG,
            MOVE_FLAREBLITZ,
            MOVE_SUNNYDAY
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Espeon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_CALMMIND,
            MOVE_PSYCHIC,
            MOVE_MORNINGSUN,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Umbreon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_UMBREON,
        .moves = {
            MOVE_CURSE,
            MOVE_MOONLIGHT,
            MOVE_TOXIC,
            MOVE_DARKPULSE
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Synchronize
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Leafeon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_LEAFEON,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_LEAFBLADE,
            MOVE_KNOCKOFF,
            MOVE_LEECHSEED
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Leaf Guard
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Glaceon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_GLACEON,
        .moves = {
            MOVE_BLIZZARD,
            MOVE_HAIL,
            MOVE_AURORAVEIL,
            MOVE_MUDSHOT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Snow Cloak
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival5_Sylveon[] = {
    {
        .lvl = 44,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ROOST,
            MOVE_IRONDEFENSE,
            MOVE_IRONHEAD
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 43,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_ICEPUNCH,
            MOVE_HONECLAWS
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 44,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_DRAGONPULSE,
            MOVE_COTTONGUARD,
            MOVE_THUNDERBOLT
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 45,
        .species = SPECIES_SYLVEON,
        .moves = {
            MOVE_MOONBLAST,
            MOVE_WISH,
            MOVE_DIG,
            MOVE_PROTECT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Cute Charm
    }
};

const struct TrainerMonItemCustomMoves sParty_Rival_EmraldinQuayEvent[] = {
    {
        .lvl = 51,
        .species = SPECIES_CLOYSTER,
        .moves = {
            MOVE_SPIKES,
            MOVE_TOXICSPIKES,
            MOVE_RAZORSHELL,
            MOVE_ICICLECRASH
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 51,
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_AURASPHERE,
            MOVE_AIRSLASH,
            MOVE_TRIATTACK,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 52,
        .species = SPECIES_COALOSSAL,
        .moves = {
            MOVE_HEATCRASH,
            MOVE_STEALTHROCK,
            MOVE_STONEEDGE,
            MOVE_SCORCHINGSANDS
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 53,
        .species = SPECIES_RAICHU_A,
        .moves = {
            MOVE_ELECTRICTERRAIN,
            MOVE_ELECTROBALL,
            MOVE_PSYCHIC,
            MOVE_SURF
        },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Surge Surfer
    },
    {
        .lvl = 54,
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_METEORMASH,
            MOVE_CLOSECOMBAT,
            MOVE_EARTHQUAKE
        },
        .heldItem = ITEM_LUCARIONITE,
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Rival[] = {
    {
        .lvl = 54,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 54,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 55,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_COUNTER,
            MOVE_HEAVYSLAM,
            MOVE_CURSE
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 55,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 56,
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_RETALIATE,
            MOVE_NIGHTSLASH,
            MOVE_SUCKERPUNCH
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_PartnerRival[] = {
    {
        .lvl = 54,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 55,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 56,
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_RETALIATE,
            MOVE_NIGHTSLASH,
            MOVE_SUCKERPUNCH
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_1 // Defiant
    },
};

const struct TrainerMonItemCustomMoves sParty_CarnelidgeVolcano_Alistair[] = {
    {
        .lvl = 55,
        .species = SPECIES_GOLBAT,
        .moves = {
            MOVE_TOXIC,
            MOVE_VENOSHOCK,
            MOVE_LEECHLIFE,
            MOVE_MEANLOOK
        },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 54,
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_INGRAIN,
            MOVE_GIGADRAIN,
            MOVE_SUBSTITUTE,
            MOVE_CLEARSMOG
        },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 56,
        .species = SPECIES_SHARPEDO,
        .moves = {
            MOVE_AQUAJET,
            MOVE_LIQUIDATION,
            MOVE_CRUNCH,
            MOVE_ICEFANG
        },
        .heldItem = ITEM_WATER_GEM,
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 57,
        .species = SPECIES_HOUNDOOM,
        .moves = {
            MOVE_SUNNYDAY,
            MOVE_DARKPULSE,
            MOVE_FLAMETHROWER,
            MOVE_THUNDERFANG
        },
        .heldItem = ITEM_HOUNDOOMINITE,
        .ability = Ability_2 // Flash Fire
    }
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Vaporeon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_VAPOREON,
        .moves = {
            MOVE_SCALD,
            MOVE_ACIDARMOR,
            MOVE_ICEBEAM,
            MOVE_FLIPTURN
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Water Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Jolteon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_JOLTEON,
        .moves = {
            MOVE_THUNDERBOLT,
            MOVE_VOLTSWITCH,
            MOVE_SHADOWBALL,
            MOVE_METALSOUND
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Volt Absorb
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Flareon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_FLAREON,
        .moves = {
            MOVE_FLAREBLITZ,
            MOVE_BODYSLAM,
            MOVE_DIG,
            MOVE_LASTRESORT
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Flash Fire
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Espeon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_MORNINGSUN,
            MOVE_CALMMIND,
            MOVE_PSYCHIC,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Umbreon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_UMBREON,
        .moves = {
            MOVE_MOONLIGHT,
            MOVE_SNARL,
            MOVE_TOXIC,
            MOVE_MEANLOOK
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Synchronize
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Leafeon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_LEAFEON,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_LEAFBLADE,
            MOVE_SYNTHESIS,
            MOVE_AERIALACE
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Leaf Guard
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Glaceon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_GLACEON,
        .moves = {
            MOVE_FREEZEDRY,
            MOVE_HAIL,
            MOVE_AURORAVEIL,
            MOVE_SHADOWBALL
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Snow Cloak
    },
};

const struct TrainerMonItemCustomMoves sParty_VictoryRoad_Rival_Sylveon[] = {
    {
        .lvl = 66,
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_ROOST
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_Hidden // Mirror Coat
    },
    {
        .lvl = 66,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_SCREECH,
            MOVE_ICICLECRASH,
            MOVE_KNOCKOFF
        },
        .heldItem = ITEM_KINGS_ROCK,
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 66,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_SUPERPOWER,
            MOVE_HEAVYSLAM,
            MOVE_REST
        },
        .heldItem = ITEM_CHESTO_BERRY,
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 66,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_DISCHARGE,
            MOVE_COTTONGUARD,
            MOVE_DRAGONPULSE
        },
        .heldItem = ITEM_AMPHAROSITE,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 68,
        .species = SPECIES_SYLVEON,
        .moves = {
            MOVE_MOONBLAST,
            MOVE_WISH,
            MOVE_PSYSHOCK,
            MOVE_REFLECT
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cute Charm
    },
};

const struct TrainerMonItemCustomMoves sParty_Rival_ExhibitionBattle_SecondaryTeam[] = {
    {
        .lvl = 66,
        .species = SPECIES_CLOYSTER,
        .moves = {
            MOVE_SPIKES,
            MOVE_TOXICSPIKES,
            MOVE_RAZORSHELL,
            MOVE_ICICLECRASH
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 66,
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_AURASPHERE,
            MOVE_AIRSLASH,
            MOVE_TRIATTACK,
            MOVE_DAZZLINGGLEAM
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 66,
        .species = SPECIES_COALOSSAL,
        .moves = {
            MOVE_HEATCRASH,
            MOVE_STEALTHROCK,
            MOVE_STONEEDGE,
            MOVE_SCORCHINGSANDS
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 66,
        .species = SPECIES_RAICHU_A,
        .moves = {
            MOVE_ELECTRICTERRAIN,
            MOVE_ELECTROBALL,
            MOVE_PSYCHIC,
            MOVE_SURF
        },
        .heldItem = ITEM_ELECTRIC_SEED,
        .ability = Ability_1 // Surge Surfer
    },
    {
        .lvl = 68,
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_METEORMASH,
            MOVE_CLOSECOMBAT,
            MOVE_EARTHQUAKE
        },
        .heldItem = ITEM_LUCARIONITE,
        .ability = Ability_Hidden // Justified
    }
};
// #endregion

// #region Route 1 
const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterPeter[] = {
    { .iv = 0, .lvl = 3, .species = SPECIES_BIDOOF },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_LassHelena[] = {
    { .lvl = 3, .species = SPECIES_FLETCHLING },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterHarlan[] = {
    { .lvl = 4, .species = SPECIES_YAMPER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_BurglarBryce[] = {
    { .lvl = 48, .species = SPECIES_GRIMER_A },
    { .lvl = 48, .species = SPECIES_KOFFING_G },
    { .lvl = 50, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_SwimmerRebecca[] = {
    { .lvl = 50, .species = SPECIES_FRILLISH_F },
    { .lvl = 51, .species = SPECIES_JELLICENT_F },
};
// #endregion

// #region Route 2
const struct TrainerMonNoItemDefaultMoves sParty_Route2_YoungsterJoey[] = {
    { .lvl = 5, .species = SPECIES_RATTATA_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassKimberly[] = {
    { .lvl = 4, .species = SPECIES_RALTS },
    { .lvl = 4, .species = SPECIES_CUTIEFLY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassRikki[] = {
    { .lvl = 7, .species = SPECIES_FLABEBE_BLUE },
    { .lvl = 7, .species = SPECIES_FLABEBE_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_CoolTrainerAndy[] = {
    { .lvl = 50, .species = SPECIES_TORKOAL },
    { .lvl = 50, .species = SPECIES_CRAWDAUNT },
    { .lvl = 52, .species = SPECIES_SLAKING },
};
// #endregion

// #region Varisi Forest
const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherKendell[] = {
    { .lvl = 4, .species = SPECIES_BLIPBUG },
    { .lvl = 5, .species = SPECIES_BLIPBUG },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherBraden[] = {
    { .lvl = 4, .species = SPECIES_BLIPBUG },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassBreanna[] = {
    { .lvl = 5, .species = SPECIES_PICHU },
    { .lvl = 6, .species = SPECIES_BUDEW },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassMimi[] = {
    { .lvl = 5, .species = SPECIES_BUNEARY },
    { .lvl = 6, .species = SPECIES_PIKIPEK },
    { .lvl = 7, .species = SPECIES_SHROOMISH },
};
// #endregion

// #region Rhodanzi City
const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Alonso[] = {
    {
        .lvl = 9,
        .species = SPECIES_MIME_JR_G,
        .moves = {
            MOVE_MISTYTERRAIN,
            MOVE_PSYCHICTERRAIN,
            MOVE_CONFUSION,
            MOVE_NONE
        },
        .ability = Ability_1 // Soundproof
    },
    {
        .lvl = 8,
        .species = SPECIES_STUNFISK_G,
        .moves = {
            MOVE_TERRAINPULSE,
            MOVE_WATERGUN,
            MOVE_MUDSLAP,
            MOVE_NONE
        },
        .ability = Ability_1 // Mimicry
    },
};

const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Brandon[] = {
    {
        .lvl = 10,
        .species = SPECIES_PINCURCHIN,
        .moves = {
            MOVE_CHARGE,
            MOVE_THUNDERSHOCK,
            MOVE_PECK,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Electric Surge
    }
};

const struct TrainerMonItemCustomMoves sParty_RhodanziCity_LeaderTerrence[] = {
    {
        .lvl = 11,
        .species = SPECIES_GROOKEY,
        .moves = {
            MOVE_SCRATCH,
            MOVE_BRANCHPOKE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 13,
        .species = SPECIES_SKIDDO,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_VINEWHIP,
            MOVE_TAILWHIP,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Grass Pelt
    }
};
// #endregion

// #region Route 3
const struct TrainerMonNoItemDefaultMoves sParty_Route3_PicknickerTana[] = {
    { .lvl = 9, .species = SPECIES_NIDORAN_M },
    { .lvl = 10, .species = SPECIES_PIKIPEK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_BugCatcherIrwin[] = {
    { .lvl = 8, .species = SPECIES_GRUBBIN },
    { .lvl = 8, .species = SPECIES_BLIPBUG },
    { .lvl = 10, .species = SPECIES_DOTTLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_YoungsterLogan[] = {
    { .lvl = 10, .species = SPECIES_DRILBUR },
    { .lvl = 11, .species = SPECIES_ROCKRUFF }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TwinsNinaAndMeg[] = {
    { .lvl = 12, .species = SPECIES_MORELULL },
    { .lvl = 10, .species = SPECIES_COMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_NinjaBoyBotan[] = {
    { .lvl = 11, .species = SPECIES_NINCADA },
    { .lvl = 11, .species = SPECIES_FERROSEED },
    { .lvl = 11, .species = SPECIES_FARFETCHD_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_RockerJude[] = {
    { .lvl = 13, .species = SPECIES_GROOKEY },
    { .lvl = 14, .species = SPECIES_TOXEL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route3_TeamPlutoRaul[] = {
    { .lvl = 12, .species = SPECIES_NICKIT },
    { .lvl = 13, .species = SPECIES_ZUBAT }
};
// #endregion

// #region Rubarr Desert
const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_NurseJaina[] = {
    { .lvl = 12, .species = SPECIES_HAPPINY },
    { .lvl = 13, .species = SPECIES_TOGEPI },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_BirdKeeperNolan[] = {
    { .lvl = 13, .species = SPECIES_ROOKIDEE },
    { .lvl = 13, .species = SPECIES_VULLABY },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacKent[] = {
    { .lvl = 12, .species = SPECIES_ROGGENROLA },
    { .lvl = 12, .species = SPECIES_ROGGENROLA },
    { .lvl = 13, .species = SPECIES_ROGGENROLA },
};

const struct TrainerMonItemDefaultMoves sParty_RubarrDesert_BlackbeltKobiyashi[] = {
    { .lvl = 13, .species = SPECIES_FARFETCHD_G },
    { .lvl = 14, .species = SPECIES_SCRAGGY },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_RuinManiacAlbert[] = {
    { .lvl = 14, .species = SPECIES_BONSLY },
    { .lvl = 14, .species = SPECIES_YAMASK_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMika[] = {
    { .lvl = 12, .species = SPECIES_NICKIT },
    { .lvl = 12, .species = SPECIES_NICKIT },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoMarcel[] = {
    { .lvl = 11, .species = SPECIES_ZUBAT },
    { .lvl = 11, .species = SPECIES_ZUBAT },
    { .lvl = 13, .species = SPECIES_SANDILE },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoTana[] = {
    { .lvl = 12, .species = SPECIES_SANDILE },
    { .lvl = 12, .species = SPECIES_KOFFING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoClancy[] = {
    { .lvl = 14, .species = SPECIES_CROAGUNK },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoEna[] = {
    { .lvl = 12, .species = SPECIES_ZUBAT },
    { .lvl = 13, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene[] = {
    {
        .lvl = 14,
        .species = SPECIES_NICKIT,
        .moves = {
            MOVE_SNARL,
            MOVE_BEATUP,
            MOVE_HONECLAWS,
            MOVE_QUICKATTACK
        },
        .ability = Ability_Hidden // Stakeout
    },
    {
        .lvl = 14,
        .species = SPECIES_SANDILE,
        .moves = {
            MOVE_BITE,
            MOVE_HONECLAWS,
            MOVE_SANDTOMB,
            MOVE_MEANLOOK
        },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 15,
        .species = SPECIES_SALANDIT,
        .moves = {
            MOVE_EMBER,
            MOVE_SMOG,
            MOVE_FAKEOUT,
            MOVE_SCRATCH
        },
        .ability = Ability_1 // Corrosion
    },
};
// #endregion

// #region Route 4
const struct TrainerMonNoItemDefaultMoves sParty_Route4_Camper_Pietro[] = {
    { .lvl = 12, .species = SPECIES_FLETCHLING },
    { .lvl = 12, .species = SPECIES_NIDORAN_M },
    { .lvl = 13, .species = SPECIES_WYNAUT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Psychic_Adriano[] = {
    { .lvl = 13, .species = SPECIES_RALTS },
    { .lvl = 13, .species = SPECIES_INKAY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Beauty_Beatrice[] = {
    { .lvl = 13, .species = SPECIES_CUTIEFLY },
    { .lvl = 14, .species = SPECIES_BUNEARY },
};

const struct TrainerMonItemDefaultMoves sParty_Route4_Lady_Alda[] = {
    { .lvl = 14, .species = SPECIES_BUDEW },
    { .lvl = 14, .species = SPECIES_COMBEE },
    { .lvl = 14, .species = SPECIES_FLABEBE_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Lass_Isabela[] = {
    { .lvl = 15, .species = SPECIES_YAMPER },
    { .lvl = 15, .species = SPECIES_SLAKOTH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Rowley[] = {
    { .lvl = 17, .species = SPECIES_DARTRIX }
};

const struct TrainerMonItemDefaultMoves sParty_Route4_Crush_Girl_Elise[] = {
    { .lvl = 14, .species = SPECIES_CROAGUNK },
    { .lvl = 15, .species = SPECIES_FARFETCHD_G },
    { .lvl = 15, .species = SPECIES_TIMBURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Gentleman_Porter[] = {
    { .lvl = 15, .species = SPECIES_MIME_JR_G },
    { .lvl = 16, .species = SPECIES_HERDIER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route4_Bird_Keeper_Luca[] = {
    { .lvl = 15, .species = SPECIES_HOOTHOOT },
    { .lvl = 17, .species = SPECIES_FLETCHINDER },
};
// #endregion

// #region Torma Cave
const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Fisherman_Alfie[] = {
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP },
    { .lvl = 15, .species = SPECIES_MAGIKARP }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Nob[] = {
    { .lvl = 13, .species = SPECIES_BONSLY },
    { .lvl = 14, .species = SPECIES_SHUCKLE },
    { .lvl = 15, .species = SPECIES_RIOLU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Hiker_Saul[] = {
    { .lvl = 16, .species = SPECIES_ROLYCOLY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Wyatt[] = {
    { .lvl = 14, .species = SPECIES_PIKACHU },
    { .lvl = 14, .species = SPECIES_CHINCHOU }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Engineer_Shane[] = {
    { .lvl = 14, .species = SPECIES_PINCURCHIN },
    { .lvl = 14, .species = SPECIES_KLINK },
    { .lvl = 14, .species = SPECIES_MAWILE },
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Pokefan_Corey[] = {
    { .lvl = 16, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_TormaCave_Lass_Harmony[] = {
    { .lvl = 15, .species = SPECIES_BUNEARY },
    { .lvl = 15, .species = SPECIES_ROSELIA },
};
// #endregion

// #region Route 7
const struct TrainerMonNoItemDefaultMoves sParty_Route7_CamperCarlisle[] = {
    { .lvl = 8, .species = SPECIES_NIDORAN_M },
    { .lvl = 10, .species = SPECIES_DOTTLER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_RockerJonas[] = {
    { .lvl = 17, .species = SPECIES_TOXEL },
    { .lvl = 18, .species = SPECIES_TRAPINCH },
    { .lvl = 19, .species = SPECIES_THWACKEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_LassEden[] = {
    { .lvl = 17, .species = SPECIES_HATENNA },
    { .lvl = 18, .species = SPECIES_SLOWPOKE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_HikerDanny[] = {
    { .lvl = 18, .species = SPECIES_TYRUNT },
    { .lvl = 18, .species = SPECIES_MUDBRAY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_CrushGirlEden[] = {
    { .lvl = 18, .species = SPECIES_COMBUSKEN },
    { .lvl = 19, .species = SPECIES_TIMBURR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route7_PsychicIshaan[] = {
    { .lvl = 19, .species = SPECIES_ELGYEM },
    { .lvl = 19, .species = SPECIES_INKAY },
};
// endregion

// #endregion

// #region Route 13
const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerDalton[] = {
    { .lvl = 14, .species = SPECIES_ZORUA },
    { .lvl = 14, .species = SPECIES_TOXEL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorCharlie[] = {
    { .lvl = 16, .species = SPECIES_LARVESTA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_HikerDwayne[] = {
    { .lvl = 15, .species = SPECIES_ROLYCOLY },
    { .lvl = 16, .species = SPECIES_PIGNITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BlackBeltHector[] = {
    { .lvl = 14, .species = SPECIES_TIMBURR },
    { .lvl = 14, .species = SPECIES_TIMBURR },
    { .lvl = 15, .species = SPECIES_MIENFOO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_PicknickerEtie[] = {
    { .lvl = 16, .species = SPECIES_SKIDDO },
    { .lvl = 16, .species = SPECIES_NIDORINO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_BeautyCandice[] = {
    { .lvl = 28, .species = SPECIES_LYCANROC_DUSK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_GamblerOwain[] = {
    { .lvl = 26, .species = SPECIES_PIKACHU },
    { .lvl = 27, .species = SPECIES_LUCARIO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route13_CollectorBenji[] = {
    { .lvl = 47, .species = SPECIES_HAKAMO_O },
    { .lvl = 48, .species = SPECIES_SABLEYE },
    { .lvl = 50, .species = SPECIES_SHEDINJA },
};
// #endregion

// #region Ferrox Village
const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLaurena[] = {
    {
        .lvl = 17,
        .species = SPECIES_FLABEBE_ORANGE,
        .moves = {
            MOVE_FAIRYWIND,
            MOVE_LUCKYCHANT,
            MOVE_RAZORLEAF,
            MOVE_ATTRACT
        },
        .ability = Ability_1 // Flower Veil
    },
    {
        .lvl = 17,
        .species = SPECIES_PHANTUMP,
        .moves = {
            MOVE_ASTONISH,
            MOVE_CONFUSERAY,
            MOVE_BRANCHPOKE,
            MOVE_NONE
        },
        .ability = Ability_1 // Natural Cure
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerLona[] = {
    {
        .lvl = 19,
        .species = SPECIES_MORELULL,
        .moves = {
            MOVE_CONFUSERAY,
            MOVE_ASTONISH,
            MOVE_ABSORB,
            MOVE_SLEEPPOWDER
        },
        .ability = Ability_2 // Effect Spore
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerChet[] = {
    {
        .lvl = 17,
        .species = SPECIES_PIKACHU,
        .moves = {
            MOVE_NUZZLE,
            MOVE_THUNDERSHOCK,
            MOVE_SWEETKISS,
            MOVE_QUICKATTACK
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 18,
        .species = SPECIES_NIDORINO,
        .moves = {
            MOVE_POISONTAIL,
            MOVE_PECK,
            MOVE_FOCUSENERGY,
            MOVE_LEER
        },
        .ability = Ability_1 // Poison Point
    }
};

const struct TrainerMonNoItemCustomMoves sParty_FerroxGym_PokemonTrainerVincent[] = {
    {
        .lvl = 17,
        .species = SPECIES_DUSKULL,
        .moves = {
            MOVE_ASTONISH,
            MOVE_DISABLE,
            MOVE_CONFUSERAY,
            MOVE_CURSE
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 17,
        .species = SPECIES_SHROOMISH,
        .moves = {
            MOVE_ABSORB,
            MOVE_LEECHSEED,
            MOVE_STUNSPORE,
            MOVE_HEADBUTT
        },
        .ability = Ability_1 // Effect Spore
    },
    {
        .lvl = 18,
        .species = SPECIES_JOLTIK,
        .moves = {
            MOVE_ELECTROWEB,
            MOVE_BUGBITE,
            MOVE_THUNDERWAVE,
            MOVE_ABSORB
        },
        .ability = Ability_1 // Compound Eyes
    }
};

const struct TrainerMonItemCustomMoves sParty_FerroxGym_GymLeaderStella[] = {
    {
        .lvl = 19,
        .species = SPECIES_MAREANIE,
        .moves = {
            MOVE_TOXIC,
            MOVE_TOXICSPIKES,
            MOVE_VENOSHOCK,
            MOVE_SCALD
        },
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 19,
        .species = SPECIES_CARKOL,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_STEALTHROCK,
            MOVE_FLAMECHARGE,
            MOVE_ANCIENTPOWER
        },
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 20,
        .species = SPECIES_TOGETIC,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_AIRSLASH,
            MOVE_FAIRYWIND,
            MOVE_MAGICALLEAF
        },
        .ability = Ability_2 // Serene Grace
    }
};
// #endregion

// #region Route 5
const struct TrainerMonItemDefaultMoves sParty_Route5_LadyFaith[] = {
    { .lvl = 17, .species = SPECIES_ROSELIA },
    { .lvl = 17, .species = SPECIES_COTTONEE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_BugCatcher_Ben[] = {
    { .lvl = 17, .species = SPECIES_DOTTLER },
    { .lvl = 17, .species = SPECIES_CHARJABUG },
    { .lvl = 18, .species = SPECIES_NINCADA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Psychic_Alyssia[] = {
    { .lvl = 18, .species = SPECIES_KIRLIA },
    { .lvl = 18, .species = SPECIES_HATENNA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Breeder_Brenda[] = {
    { .lvl = 12, .species = SPECIES_BUDEW },
    { .lvl = 12, .species = SPECIES_WYNAUT },
    { .lvl = 12, .species = SPECIES_BONSLY },
    { .lvl = 12, .species = SPECIES_MIME_JR_G },
    { .lvl = 12, .species = SPECIES_PICHU },
    { .lvl = 12, .species = SPECIES_HAPPINY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Blackbelt_Raheem[] = {
    { .lvl = 18, .species = SPECIES_TIMBURR },
    { .lvl = 19, .species = SPECIES_RIOLU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gambler_Dominik[] = {
    { .lvl = 18, .species = SPECIES_ZORUA },
    { .lvl = 18, .species = SPECIES_CROAGUNK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Lady_Juliet[] = {
    { .lvl = 17, .species = SPECIES_PIKACHU },
    { .lvl = 17, .species = SPECIES_EEVEE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route5_Gentleman_Marcus[] = {
    { .lvl = 18, .species = SPECIES_CORVISQUIRE },
    { .lvl = 18, .species = SPECIES_QUILLADIN },
};
// #endregion

// #region Heleo Ranch
const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Burglar_Cole[] = {
    { .lvl = 18, .species = SPECIES_KOFFING_G },
    { .lvl = 17, .species = SPECIES_NICKIT },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Camper_Troy[] = {
    { .lvl = 17, .species = SPECIES_LILLIPUP },
    { .lvl = 17, .species = SPECIES_BIBAREL },
    { .lvl = 18, .species = SPECIES_CORVISQUIRE },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Breeder_Laura[] = {
    { .lvl = 14, .species = SPECIES_SUNKERN },
    { .lvl = 14, .species = SPECIES_RALTS },
    { .lvl = 14, .species = SPECIES_TOGEPI },
    { .lvl = 14, .species = SPECIES_PICHU },
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoRanch_Picknicker_Carly[] = {
    { .lvl = 18, .species = SPECIES_FLETCHLING },
    { .lvl = 18, .species = SPECIES_CACNEA },
    { .lvl = 19, .species = SPECIES_FLOETTE_WHITE }
};
// #endregion

// #region Route 6
const struct TrainerMonNoItemDefaultMoves sParty_Route6_Youngster_Ned[] = {
    { .lvl = 19, .species = SPECIES_TRUMBEAK },
    { .lvl = 20, .species = SPECIES_RATICATE_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_NinjaBoy_Rajan[] = {
    { .lvl = 19, .species = SPECIES_NINCADA },
    { .lvl = 19, .species = SPECIES_SUDOWOODO },
    { .lvl = 19, .species = SPECIES_TRAPINCH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Hiker_Romero[] = {
    { .lvl = 19, .species = SPECIES_CARBINK },
    { .lvl = 19, .species = SPECIES_SHUCKLE },
    { .lvl = 20, .species = SPECIES_MAWILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Estevan[] = {
    { .lvl = 19, .species = SPECIES_ROCKRUFF },
    { .lvl = 20, .species = SPECIES_VIGOROTH },
    { .lvl = 21, .species = SPECIES_DRATINI }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Engineer_Harry[] = {
    { .lvl = 20, .species = SPECIES_CHARJABUG },
    { .lvl = 20, .species = SPECIES_KLINK },
    { .lvl = 20, .species = SPECIES_PACHIRISU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gambler_Mick[] = {
    { .lvl = 24, .species = SPECIES_DITTO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Fisherman_Taylor[] = {
    { .lvl = 20, .species = SPECIES_CHINCHOU },
    { .lvl = 20, .species = SPECIES_SHELLDER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Nurse_Leanne[] = {
    { .lvl = 20, .species = SPECIES_BRAIXEN },
    { .lvl = 20, .species = SPECIES_CHANSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SuperNerd_Dante[] = {
    { .lvl = 28, .species = SPECIES_DEWOTT },
    { .lvl = 28, .species = SPECIES_MAWILE },
    { .lvl = 28, .species = SPECIES_FARFETCHD }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BugCatcher_Billie[] = {
    { .lvl = 30, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 30, .species = SPECIES_VESPIQUEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Gentleman_Lincoln[] = {
    { .lvl = 28, .species = SPECIES_LYCANROC_N },
    { .lvl = 29, .species = SPECIES_HERDIER },
    { .lvl = 29, .species = SPECIES_QUILAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_BlackBelt_Raphael[] = {
    { .lvl = 30, .species = SPECIES_PIGNITE },
    { .lvl = 31, .species = SPECIES_GURDURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Lass_Anna[] = {
    { .lvl = 29, .species = SPECIES_RIOLU },
    { .lvl = 29, .species = SPECIES_TOGETIC },
    { .lvl = 29, .species = SPECIES_COTTONEE },
    { .lvl = 30, .species = SPECIES_RIBOMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_Swimmer_Danika[] = {
    { .lvl = 48, .species = SPECIES_DRATINI },
    { .lvl = 48, .species = SPECIES_SEADRA },
    { .lvl = 50, .species = SPECIES_SHARPEDO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SrAndJr_SueAndKat[] = {
    { .lvl = 29, .species = SPECIES_EEVEE },
    { .lvl = 30, .species = SPECIES_BRELOOM },
    { .lvl = 29, .species = SPECIES_MISDREAVUS },
    { .lvl = 30, .species = SPECIES_LOPUNNY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_HikerDarryl[] = {
    { .lvl = 55, .species = SPECIES_BOLDORE },
    { .lvl = 55, .species = SPECIES_BARBARACLE },
    { .lvl = 56, .species = SPECIES_TYRANTRUM },
    { .lvl = 56, .species = SPECIES_CONKELDURR }
};
// #endregion

// #region Heleo City
const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_PsychicBianca[] = {
    { .lvl = 1, .species = SPECIES_BULBASAUR },
    { .lvl = 1, .species = SPECIES_CHARMANDER },
    { .lvl = 1, .species = SPECIES_SQUIRTLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_SupernerdGalen[] = {
    { .lvl = 1, .species = SPECIES_TIMBURR },
    { .lvl = 1, .species = SPECIES_HOOTHOOT },
    { .lvl = 1, .species = SPECIES_HOUNDOUR }
};

const struct TrainerMonNoItemDefaultMoves sParty_HeleoCity_CoolTrainerJet[] = {
    { .lvl = 1, .species = SPECIES_DARUMAKA_G },
    { .lvl = 1, .species = SPECIES_RALTS },
    { .lvl = 1, .species = SPECIES_BLIPBUG }
};

const struct TrainerMonNoItemCustomMoves sParty_HeleoCityGym_SwimmerTessa[] = {
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

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerByron[] = {
    {
        .lvl = 23,
        .species = SPECIES_TORKOAL,
        .moves = {
            MOVE_SMOG,
            MOVE_FLAMEWHEEL,
            MOVE_WITHDRAW,
            MOVE_SMOKESCREEN
        },
        .heldItem = ITEM_HEAT_ROCK,
        .ability = Ability_2 // Drought
    },
    {
        .lvl = 23,
        .species = SPECIES_SUNFLORA,
        .moves = {
            MOVE_GROWTH,
            MOVE_SYNTHESIS,
            MOVE_RAZORLEAF,
            MOVE_GIGADRAIN
        },
        .ability = Ability_2 // Solar Power
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerDanette[] = {
    {
        .lvl = 22,
        .species = SPECIES_AMAURA,
        .moves = {
            MOVE_ICYWIND,
            MOVE_ANCIENTPOWER,
            MOVE_AURORAVEIL,
            MOVE_ROUND
        },
        .heldItem = ITEM_ICY_ROCK,
        .ability = Ability_Hidden // Snow Warning
    },
    {
        .lvl = 23,
        .species = SPECIES_BERGMITE,
        .moves = {
            MOVE_CURSE,
            MOVE_AVALANCHE,
            MOVE_POWDERSNOW,
            MOVE_HAIL
        },
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 23,
        .species = SPECIES_CUBCHOO,
        .moves = {
            MOVE_BRINE,
            MOVE_FROSTBREATH,
            MOVE_CHARM,
            MOVE_HAIL
        },
        .ability = Ability_2 // Slush Rush
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_SwimmerMaisey[] = {
    {
        .lvl = 23,
        .species = SPECIES_HIPPOPOTAS_F,
        .moves = {
            MOVE_CRUNCH,
            MOVE_SANDTOMB,
            MOVE_YAWN,
            MOVE_DIG
        },
        .heldItem = ITEM_SMOOTH_ROCK,
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 23,
        .species = SPECIES_HERDIER,
        .moves = {
            MOVE_FIREFANG,
            MOVE_THUNDERFANG,
            MOVE_RETALIATE,
            MOVE_WORKUP
        },
        .ability = Ability_2 // Sand Rush
    },
    {
        .lvl = 23,
        .species = SPECIES_CACNEA,
        .moves = {
            MOVE_NEEDLEARM,
            MOVE_FEINTATTACK,
            MOVE_INGRAIN,
            MOVE_SANDSTORM
        },
        .ability = Ability_1 // Sand Veil
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine[] = {
    {
        .lvl = 25,
        .species = SPECIES_PELIPPER,
        .moves = {
            MOVE_WINGATTACK,
            MOVE_WATERPULSE,
            MOVE_SUPERSONIC,
            MOVE_PROTECT
        },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 24,
        .species = SPECIES_FERROSEED,
        .moves = {
            MOVE_HARDEN,
            MOVE_INGRAIN,
            MOVE_PINMISSILE,
            MOVE_METALCLAW
        },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 26,
        .species = SPECIES_HELIOLISK,
        .moves = {
            MOVE_BULLDOZE,
            MOVE_THUNDER,
            MOVE_THUNDERWAVE,
            MOVE_RAINDANCE
        },
        .ability = Ability_1 // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine2[] = {
    {
        .lvl = 31,
        .species = SPECIES_PELIPPER,
        .moves = {
            MOVE_WINGATTACK,
            MOVE_WATERPULSE,
            MOVE_SOAK,
            MOVE_PROTECT
        },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 31,
        .species = SPECIES_FERROSEED,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_INGRAIN,
            MOVE_BULLETSEED,
            MOVE_LEECHSEED
        },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 33,
        .species = SPECIES_HELIOLISK,
        .moves = {
            MOVE_BULLDOZE,
            MOVE_THUNDER,
            MOVE_THUNDERWAVE,
            MOVE_RAINDANCE
        },
        .ability = Ability_1 // Dry Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_HeleoCityGym_LeaderRaine3[] = {
    {
        .lvl = 39,
        .species = SPECIES_PELIPPER,
        .moves = {
            MOVE_AIRSLASH,
            MOVE_WATERPULSE,
            MOVE_SOAK,
            MOVE_PROTECT
        },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 40,
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_CURSE,
            MOVE_POWERWHIP,
            MOVE_LEECHSEED
        },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 40,
        .species = SPECIES_SLIGGOO,
        .moves = {
            MOVE_ACIDARMOR,
            MOVE_ACIDSPRAY,
            MOVE_DRAGONPULSE,
            MOVE_WATERPULSE
        },
        .ability = Ability_2 // Hydration
    },
    {
        .lvl = 41,
        .species = SPECIES_HELIOLISK,
        .moves = {
            MOVE_BULLDOZE,
            MOVE_THUNDER,
            MOVE_THUNDERWAVE,
            MOVE_RAINDANCE
        },
        .ability = Ability_1 // Dry Skin
    }
};
// #endregion

// #region Route 8
const struct TrainerMonNoItemDefaultMoves sParty_Route8_Camper_Drew[] = {
    { .lvl = 25, .species = SPECIES_EMOLGA },
    { .lvl = 25, .species = SPECIES_BIBAREL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyZeke[] = {
    { .lvl = 23, .species = SPECIES_NINCADA },
    { .lvl = 24, .species = SPECIES_NINJASK },
    { .lvl = 25, .species = SPECIES_SHEDINJA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SuperNerdSaul[] = {
    { .lvl = 24, .species = SPECIES_DRILBUR },
    { .lvl = 24, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 25, .species = SPECIES_CRABRAWLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_RockerParker[] = {
    { .lvl = 25, .species = SPECIES_CASTFORM },
    { .lvl = 26, .species = SPECIES_KLINK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ParasolLadyAnnabelle[] = {
    { .lvl = 28, .species = SPECIES_KIRLIA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_ChannelerMorgan[] = {
    { .lvl = 25, .species = SPECIES_DUSKULL },
    { .lvl = 25, .species = SPECIES_YAMASK },
    { .lvl = 26, .species = SPECIES_YAMASK_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_BugCatcherArnold[] = {
    { .lvl = 24, .species = SPECIES_SNOM },
    { .lvl = 26, .species = SPECIES_LARVESTA },
    { .lvl = 26, .species = SPECIES_CHARJABUG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_LassLilian[] = {
    { .lvl = 26, .species = SPECIES_COTTONEE },
    { .lvl = 27, .species = SPECIES_BAYLEEF }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_NinjaBoyNatto[] = {
    { .lvl = 24, .species = SPECIES_STUNFISK_G },
    { .lvl = 25, .species = SPECIES_SNEASEL }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberMicah[] = {
    { .lvl = 25, .species = SPECIES_PICHU },
    { .lvl = 25, .species = SPECIES_EEVEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_TuberNancy[] = {
    { .lvl = 25, .species = SPECIES_SANDYGAST },
    { .lvl = 25, .species = SPECIES_COMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerMaya[] = {
    { .lvl = 26, .species = SPECIES_SHELLDER },
    { .lvl = 26, .species = SPECIES_HORSEA },
    { .lvl = 26, .species = SPECIES_HORSEA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerHuey[] = {
    { .lvl = 47, .species = SPECIES_BINACLE },
    { .lvl = 48, .species = SPECIES_CORSOLA_G },
    { .lvl = 48, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerBob[] = {
    { .lvl = 48, .species = SPECIES_LANTURN },
    { .lvl = 48, .species = SPECIES_SHELLDER },
    { .lvl = 51, .species = SPECIES_PELIPPER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_CoolTrainerHarriet[] = {
    { .lvl = 50, .species = SPECIES_UMBREON },
    { .lvl = 52, .species = SPECIES_GASTRODON_EAST },
    { .lvl = 52, .species = SPECIES_CROBAT }
};
// #endregion

// #region Forgotten Manse
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_ChannelerMona[] = {
    { .lvl = 25, .species = SPECIES_HATENNA },
    { .lvl = 25, .species = SPECIES_DUSKULL },
    { .lvl = 25, .species = SPECIES_MISDREAVUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BurglarChad[] = {
    { .lvl = 27, .species = SPECIES_SNEASEL },
    { .lvl = 27, .species = SPECIES_BOLTUND }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_NurseLucy[] = {
    { .lvl = 25, .species = SPECIES_TOGETIC },
    { .lvl = 25, .species = SPECIES_COMFEY },
    { .lvl = 26, .species = SPECIES_FLOETTE_YELLOW }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_BeautyLulu[] = {
    { .lvl = 26, .species = SPECIES_KIRLIA },
    { .lvl = 27, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_ChannelerEsther[] = {
    { .lvl = 26, .species = SPECIES_MISDREAVUS },
    { .lvl = 26, .species = SPECIES_SANDYGAST }
};

const struct TrainerMonNoItemCustomMoves sParty_ForgottenManse_1F_SuperNerdAustin[] = {
    {
        .lvl = 27,
        .species = SPECIES_DITTO,
        .moves = {
            MOVE_TRANSFORM,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 27,
        .species = SPECIES_DITTO,
        .moves = {
            MOVE_TRANSFORM,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Imposter
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_BurglarJacques[] = {
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 26, .species = SPECIES_TIMBURR },
    { .lvl = 26, .species = SPECIES_THIEVUL }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_1F_PsychicCorbin[] = {
    { .lvl = 27, .species = SPECIES_GALLADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_BurglarBarry[] = {
    { .lvl = 27, .species = SPECIES_CROAGUNK },
    { .lvl = 28, .species = SPECIES_GRIMER_A },
    { .lvl = 29, .species = SPECIES_SCRAGGY }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_YoungsterChester[] = {
    { .lvl = 27, .species = SPECIES_CORSOLA_G },
    { .lvl = 27, .species = SPECIES_CORSOLA_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_2F_ChannelerElaine[] = {
    { .lvl = 32, .species = SPECIES_SABLEYE }
};

const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_SuperNerdGlenn[] = {
    { .lvl = 27, .species = SPECIES_SLOWPOKE },
    { .lvl = 27, .species = SPECIES_SLOWPOKE_G }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_BurglarPavle[] = {
    { .lvl = 25, .species = SPECIES_NICKIT },
    { .lvl = 31, .species = SPECIES_THIEVUL }
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_PsychicNoelle[] = {
    { .lvl = 27, .species = SPECIES_HATENNA },
    { .lvl = 28, .species = SPECIES_KIRLIA },
    { .lvl = 28, .species = SPECIES_BRAIXEN },
};
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_ChannelerSana[] = {
    { .lvl = 30, .species = SPECIES_PHANTUMP },
    { .lvl = 30, .species = SPECIES_SANDYGAST }
};
// #endregion

// #region Daimyn Factory
const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BirdkeeperMarius[] = {
    { .lvl = 33, .species = SPECIES_NOCTOWL }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_RockerBenson[] = {
    { .lvl = 29, .species = SPECIES_KLINK },
    { .lvl = 31, .species = SPECIES_CHARJABUG }
};

const struct TrainerMonItemCustomMoves sParty_DaimynFactory_LassNatalie[] = {
    {
        .lvl = 31,
        .species = SPECIES_GROTLE,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_CURSE,
            MOVE_SANDTOMB,
            MOVE_RAZORLEAF
        },
        .heldItem = ITEM_YACHE_BERRY,
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 31,
        .species = SPECIES_MISMAGIUS,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_HEX,
            MOVE_CALMMIND,
            MOVE_DESTINYBOND
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerJamison[] = {
    { .lvl = 29, .species = SPECIES_MAWILE },
    { .lvl = 28, .species = SPECIES_FLAAFFY },
    { .lvl = 30, .species = SPECIES_JOLTIK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_HikerPercy[] = {
    { .lvl = 31, .species = SPECIES_CUFANT },
    { .lvl = 31, .species = SPECIES_DRILBUR },
    { .lvl = 31, .species = SPECIES_CARBINK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BlackbeltRory[] = {
    { .lvl = 33, .species = SPECIES_MIENFOO },
    { .lvl = 34, .species = SPECIES_HAKAMO_O }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerWilson[] = {
    { .lvl = 32, .species = SPECIES_PACHIRISU },
    { .lvl = 34, .species = SPECIES_HELIOPTILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_YoungsterNate[] = {
    { .lvl = 32, .species = SPECIES_VIGOROTH },
    { .lvl = 34, .species = SPECIES_VIBRAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_PicknickerShanna[] = {
    { .lvl = 32, .species = SPECIES_FRILLISH_F },
    { .lvl = 34, .species = SPECIES_GARDEVOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerKliff[] = {
    { .lvl = 32, .species = SPECIES_EMOLGA },
    { .lvl = 34, .species = SPECIES_RAICHU },
    { .lvl = 34, .species = SPECIES_STUNFISK_G }
};
// #endregion

// #region Daimyn City
const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_YoungsterJacob[] = {
    {
        .lvl = 1,
        .species = SPECIES_RATTATA_A,
        .moves = {
            MOVE_ENDEAVOR,
            MOVE_QUICKATTACK,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Thick Fat
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_PokefanKanesha[] = {
    {
        .lvl = 32,
        .species = SPECIES_SHUCKLE,
        .moves = {
            MOVE_POWERTRICK,
            MOVE_ROCKTHROW,
            MOVE_STRUGGLEBUG,
            MOVE_NONE
        },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_BeautyEmilie[] = {
    {
        .lvl = 30,
        .species = SPECIES_ZOROARK,
        .moves = {
            MOVE_TAUNT,
            MOVE_KNOCKOFF,
            MOVE_DETECT,
            MOVE_SUCKERPUNCH
        },
        .ability = Ability_1 // Illusion
    },
    {
        .lvl = 30,
        .species = SPECIES_CROAGUNK,
        .moves = {
            MOVE_SUCKERPUNCH,
            MOVE_SWAGGER,
            MOVE_REVENGE,
            MOVE_VENOSHOCK
        },
        .ability = Ability_Hidden // Poison Touch
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_BeautyLeanne[] = {
    {
        .lvl = 30,
        .species = SPECIES_TOGETIC,
        .moves = {
            MOVE_METRONOME,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 30,
        .species = SPECIES_CHANSEY,
        .moves = {
            MOVE_METRONOME,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 30,
        .species = SPECIES_HATTREM,
        .moves = {
            MOVE_METRONOME,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_LEPPA_BERRY,
        .ability = Ability_2 // Anticipation
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_ChannelerRosita[] = {
    {
        .lvl = 28,
        .species = SPECIES_DOTTLER,
        .moves = {
            MOVE_TRICKROOM,
            MOVE_STRUGGLEBUG,
            MOVE_CONFUSION,
            MOVE_LIGHTSCREEN
        },
        .ability = Ability_1 // Swarm
    },
    {
        .lvl = 29,
        .species = SPECIES_CUFANT,
        .moves = {
            MOVE_IRONDEFENSE,
            MOVE_STOMP,
            MOVE_BULLDOZE,
            MOVE_ROCKSMASH
        },
        .ability = Ability_1 // Sheer Force
    },
    {
        .lvl = 28,
        .species = SPECIES_GURDURR,
        .moves = {
            MOVE_RETALIATE,
            MOVE_ROCKSLIDE,
            MOVE_LOWKICK,
            MOVE_BULKUP
        },
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 28,
        .species = SPECIES_CARBINK,
        .moves = {
            MOVE_TRICKROOM,
            MOVE_ANCIENTPOWER,
            MOVE_SMACKDOWN,
            MOVE_DAZZLINGGLEAM
        },
        .ability = Ability_1 // Clear body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_GamblerChuck[] = {
    {
        .lvl = 30,
        .species = SPECIES_FLETCHINDER,
        .moves = {
            MOVE_ACROBATICS,
            MOVE_TAILWIND,
            MOVE_FLAMECHARGE,
            MOVE_UTURN
        },
        .ability = Ability_Hidden // Gale Wings
    },
    {
        .lvl = 30,
        .species = SPECIES_BOLTUND,
        .moves = {
            MOVE_ELECTROBALL,
            MOVE_ROAR,
            MOVE_BITE,
            MOVE_FLAMECHARGE
        },
        .ability = Ability_Hidden // Competitive
    },
    {
        .lvl = 31,
        .species = SPECIES_RABOOT,
        .moves = {
            MOVE_ELECTROBALL,
            MOVE_FLAMECHARGE,
            MOVE_DOUBLEKICK,
            MOVE_GROWL
        },
        .ability = Ability_1 // Blaze
    }
};

const struct TrainerMonNoItemCustomMoves sParty_DaimynCityGym_BurglarDexter[] = {
    {
        .lvl = 30,
        .species = SPECIES_MISDREAVUS,
        .moves = {
            MOVE_PSYBEAM,
            MOVE_PERISHSONG,
            MOVE_MEANLOOK,
            MOVE_ASTONISH
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 30,
        .species = SPECIES_UMBREON,
        .moves = {
            MOVE_SWAGGER,
            MOVE_FOULPLAY,
            MOVE_SANDATTACK,
            MOVE_ASSURANCE
        },
        .ability = Ability_1 // Synchronize
    },
    {
        .lvl = 31,
        .species = SPECIES_WOBBUFFET,
        .moves = {
            MOVE_ENCORE,
            MOVE_COUNTER,
            MOVE_MIRRORCOAT,
            MOVE_DESTINYBOND
        },
        .ability = Ability_1 // Shadow Tag
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance[] = {
    {
        .lvl = 31,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = {
            MOVE_REFLECT,
            MOVE_LIGHTSCREEN,
            MOVE_UTURN,
            MOVE_ANCIENTPOWER
        },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Shields Down
    },
    {
        .lvl = 31,
        .species = SPECIES_LANTURN,
        .moves = {
            MOVE_SOAK,
            MOVE_SPARK,
            MOVE_BRINE,
            MOVE_VOLTSWITCH
        },
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 33,
        .species = SPECIES_DUSCLOPS,
        .moves = {
            MOVE_PAINSPLIT,
            MOVE_TRICKROOM,
            MOVE_WILLOWISP,
            MOVE_HEX
        },
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityGym_LeaderChance2[] = {
    {
        .lvl = 39,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = {
            MOVE_REFLECT,
            MOVE_LIGHTSCREEN,
            MOVE_UTURN,
            MOVE_ANCIENTPOWER
        },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Shields Down
    },
    {
        .lvl = 40,
        .species = SPECIES_LANTURN,
        .moves = {
            MOVE_SUCKERPUNCH,
            MOVE_DISCHARGE,
            MOVE_BRINE,
            MOVE_VOLTSWITCH
        },
        .ability = Ability_1 // Volt Absorb
    },
    {
        .lvl = 40,
        .species = SPECIES_INCINEROAR,
        .moves = {
            MOVE_PARTINGSHOT,
            MOVE_KNOCKOFF,
            MOVE_FAKEOUT,
            MOVE_FLAMETHROWER
        },
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 41,
        .species = SPECIES_DUSKNOIR,
        .moves = {
            MOVE_PAINSPLIT,
            MOVE_CURSE,
            MOVE_WILLOWISP,
            MOVE_HEX
        },
        .ability = Ability_1 // Pressure
    }
};
// #endregion

// #region Route 9
const struct TrainerMonNoItemDefaultMoves sParty_Route9_Collector_Marshall[] = {
    { .lvl = 30, .species = SPECIES_MR_MIME },
    { .lvl = 31, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Andrea[] = {
    { .lvl = 31, .species = SPECIES_HERACROSS },
    { .lvl = 31, .species = SPECIES_TOUCANNON },
    { .lvl = 31, .species = SPECIES_TORRACAT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Fisherman_Yusuf[] = {
    { .lvl = 30, .species = SPECIES_GYARADOS },
    { .lvl = 30, .species = SPECIES_GASTRODON },
};

const struct TrainerMonNoItemCustomMoves sParty_Route9_Gentleman_Gavin[] = {
    {
        .lvl = 31,
        .species = SPECIES_RAICHU,
        .moves = {
            MOVE_HELPINGHAND,
            MOVE_THUNDERBOLT,
            MOVE_ELECTROBALL,
            MOVE_DRAININGKISS
        },
        .ability = Ability_Hidden // Lightningrod
    },
    {
        .lvl = 31,
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_BULLETPUNCH,
            MOVE_FORCEPALM,
            MOVE_QUICKGUARD,
            MOVE_HELPINGHAND
        },
        .ability = Ability_Hidden // Justified
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_NinjaBoy_Ayrton[] = {
    { .lvl = 29, .species = SPECIES_NINJASK },
    { .lvl = 29, .species = SPECIES_KROKOROK },
    { .lvl = 31, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Breeder_Talia[] = {
    { .lvl = 28, .species = SPECIES_PIKACHU },
    { .lvl = 29, .species = SPECIES_TOGETIC },
    { .lvl = 30, .species = SPECIES_ESPEON },
    { .lvl = 30, .species = SPECIES_UMBREON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Picknicker_Zoe[] = {
    { .lvl = 31, .species = SPECIES_VESPIQUEN },
    { .lvl = 32, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Kingsley[] = {
    { .lvl = 33, .species = SPECIES_DECIDUEYE },
    { .lvl = 33, .species = SPECIES_VIBRAVA },
    { .lvl = 34, .species = SPECIES_SIRFETCHD },
};
// #endregion

// #region Route 10
const struct TrainerMonNoItemDefaultMoves sParty_Route10_PsychicDarius[] = {
    { .lvl = 29, .species = SPECIES_KIRLIA },
    { .lvl = 30, .species = SPECIES_MR_MIME_G },
    { .lvl = 30, .species = SPECIES_WOBBUFFET },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_BirdKeeperMario[] = {
    { .lvl = 30, .species = SPECIES_NOCTOWL },
    { .lvl = 30, .species = SPECIES_PELIPPER },
    { .lvl = 30, .species = SPECIES_SKARMORY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_GamblerDarren[] = {
    { .lvl = 32, .species = SPECIES_LILEEP },
    { .lvl = 32, .species = SPECIES_GLACEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_ParasolLadyGwen[] = {
    { .lvl = 34, .species = SPECIES_FLORGES_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_CamperJackson[] = {
    { .lvl = 32, .species = SPECIES_NIDORINO },
    { .lvl = 34, .species = SPECIES_CHESNAUGHT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_RockerBert[] = {
    { .lvl = 31, .species = SPECIES_THWACKEY },
    { .lvl = 31, .species = SPECIES_NOIBAT },
    { .lvl = 33, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerAlberto[] = {
    { .lvl = 47, .species = SPECIES_CORSOLA_G },
    { .lvl = 47, .species = SPECIES_CORPHISH },
    { .lvl = 48, .species = SPECIES_CURSOLA },
    { .lvl = 48, .species = SPECIES_CRAWDAUNT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerRosie[] = {
    { .lvl = 52, .species = SPECIES_JELLICENT_F },
    { .lvl = 53, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerDoug[] = {
    { .lvl = 49, .species = SPECIES_CARVANHA },
    { .lvl = 50, .species = SPECIES_SLOWBRO },
    { .lvl = 50, .species = SPECIES_BLASTOISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_HikerHarley[] = {
    { .lvl = 30, .species = SPECIES_BOLDORE },
    { .lvl = 30, .species = SPECIES_CARKOL },
    { .lvl = 32, .species = SPECIES_GIGALITH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_BlackbeltXavier[] = {
    { .lvl = 31, .species = SPECIES_MONFERNO },
    { .lvl = 32, .species = SPECIES_GURDURR },
};

// #endregion

// #region Route 11 South
const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Ross[] = {
    { .lvl = 33, .species = SPECIES_KOFFING_G },
    { .lvl = 34, .species = SPECIES_KROKOROK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Greta[] = {
    { .lvl = 32, .species = SPECIES_SNEASEL },
    { .lvl = 33, .species = SPECIES_ZUBAT },
    { .lvl = 33, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Nellie[] = {
    { .lvl = 31, .species = SPECIES_ZUBAT },
    { .lvl = 31, .species = SPECIES_SANDILE },
    { .lvl = 32, .species = SPECIES_KOFFING_G },
    { .lvl = 33, .species = SPECIES_SNEASEL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Helga[] = {
    { .lvl = 34, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 35, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Kareem[] = {
    { .lvl = 33, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 33, .species = SPECIES_CROAGUNK },
    { .lvl = 35, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Chung[] = {
    { .lvl = 35, .species = SPECIES_SCRAGGY },
    { .lvl = 35, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Lass_Tabitha[] = {
    { .lvl = 33, .species = SPECIES_AMAURA },
    { .lvl = 34, .species = SPECIES_STOUTLAND },
    { .lvl = 34, .species = SPECIES_VESPIQUEN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_CrushGirl_Alisa[] = {
    { .lvl = 36, .species = SPECIES_SIRFETCHD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Engineer_Dale[] = {
    { .lvl = 35, .species = SPECIES_PINCURCHIN },
    { .lvl = 35, .species = SPECIES_EMOLGA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Collector_Orville[] = {
    { .lvl = 34, .species = SPECIES_LILEEP },
    { .lvl = 34, .species = SPECIES_SLIGGOO },
    { .lvl = 35, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoClancy[] = {
    { .lvl = 35, .species = SPECIES_THIEVUL },
    { .lvl = 35, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoEna[] = {
    { .lvl = 36, .species = SPECIES_GOLBAT },
    { .lvl = 36, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald[] = {
    {
        .lvl = 35,
        .species = SPECIES_KROKOROK,
        .moves = {
            MOVE_CRUNCH,
            MOVE_DIG,
            MOVE_AQUATAIL,
            MOVE_TAUNT
        },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 35,
        .species = SPECIES_SNEASEL,
        .moves = {
            MOVE_ICESHARD,
            MOVE_METALCLAW,
            MOVE_FAKEOUT,
            MOVE_ICEPUNCH
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 36,
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_CURSE,
            MOVE_LEECHSEED,
            MOVE_POWERWHIP
        },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 37,
        .species = SPECIES_SCRAFTY,
        .moves = {
            MOVE_POWERUPPUNCH,
            MOVE_SWAGGER,
            MOVE_SNARL,
            MOVE_PROTECT
        },
        .ability = Ability_1 // Shed Skin
    }
};
// #endregion

// #region Hesson Pass
const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_HikerLuke[] = {
    { .lvl = 37, .species = SPECIES_GIGALITH }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_ScientistHarvey[] = {
    { .lvl = 34, .species = SPECIES_BERGMITE },
    { .lvl = 34, .species = SPECIES_LILEEP },
    { .lvl = 35, .species = SPECIES_CACTURNE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_PsychicKimiko[] = {
    { .lvl = 57, .species = SPECIES_HATTREM },
    { .lvl = 57, .species = SPECIES_MORPEKO },
    { .lvl = 59, .species = SPECIES_MANDIBUZZ }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CoolTrainerColt[] = {
    { .lvl = 58, .species = SPECIES_GLALIE },
    { .lvl = 58, .species = SPECIES_TOUCANNON },
    { .lvl = 60, .species = SPECIES_MAMOSWINE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_BlackbeltHaytham[] = {
    { .lvl = 35, .species = SPECIES_CRABRAWLER },
    { .lvl = 36, .species = SPECIES_BLAZIKEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CollectorZeus[] = {
    { .lvl = 57, .species = SPECIES_COFAGRIGUS },
    { .lvl = 57, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_NurseMina[] = {
    { .lvl = 55, .species = SPECIES_HAPPINY },
    { .lvl = 57, .species = SPECIES_CHANSEY },
    { .lvl = 59, .species = SPECIES_BLISSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_GentlemanGordy[] = {
    { .lvl = 57, .species = SPECIES_BOLTUND },
    { .lvl = 58, .species = SPECIES_STOUTLAND }
};
// #endregion

// #region Route 11 North
const struct TrainerMonNoItemDefaultMoves sParty_Route11North_PainterIsobel[] = {
    { .lvl = 35, .species = SPECIES_IVYSAUR },
    { .lvl = 36, .species = SPECIES_GLACEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanClint[] = {
    { .lvl = 35, .species = SPECIES_HORSEA },
    { .lvl = 35, .species = SPECIES_WARTORTLE },
    { .lvl = 36, .species = SPECIES_GASTRODON_EAST }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ChanellerKatya[] = {
    { .lvl = 36, .species = SPECIES_SABLEYE },
    { .lvl = 38, .species = SPECIES_DUSKNOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_RockerNathaniel[] = {
    { .lvl = 36, .species = SPECIES_VIBRAVA },
    { .lvl = 36, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_NinjaBoyYao[] = {
    { .lvl = 34, .species = SPECIES_CARVANHA },
    { .lvl = 34, .species = SPECIES_EMOLGA },
    { .lvl = 36, .species = SPECIES_MALAMAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ParaoslLadyTina[] = {
    { .lvl = 34, .species = SPECIES_FLOETTE_ORANGE },
    { .lvl = 35, .species = SPECIES_BRAIXEN },
    { .lvl = 35, .species = SPECIES_RIBOMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanJonah[] = {
    { .lvl = 36, .species = SPECIES_MAGIKARP },
    { .lvl = 38, .species = SPECIES_GYARADOS }
};

// #endregion

// #region Laplaz Town
const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_BirdKeeperToby[] = {
    { .lvl = 1, .species = SPECIES_CORVISQUIRE },
    { .lvl = 1, .species = SPECIES_NOCTOWL },
    { .lvl = 1, .species = SPECIES_FLETCHINDER }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CollectorDirk[] = {
    { .lvl = 1, .species = SPECIES_MISDREAVUS },
    { .lvl = 1, .species = SPECIES_DUSKULL },
    { .lvl = 1, .species = SPECIES_VIBRAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_LaplazTown_CoolTrainerVanessa[] = {
    { .lvl = 1, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 1, .species = SPECIES_SKARMORY },
    { .lvl = 1, .species = SPECIES_ROTOM }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_PsychicJeremiah[] = {
    {
        .lvl = 38,
        .species = SPECIES_FALINKS,
        .moves = {
            MOVE_BULKUP,
            MOVE_ROCKSMASH,
            MOVE_NORETREAT,
            MOVE_HEADBUTT
        },
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 38,
        .species = SPECIES_EMOLGA,
        .moves = {
            MOVE_ELECTROBALL,
            MOVE_AGILITY,
            MOVE_CHARGE,
            MOVE_ACROBATICS
        },
        .ability = Ability_1 // Static
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_PicnickerExie[] = {
    {
        .lvl = 37,
        .species = SPECIES_TORRACAT,
        .moves = {
            MOVE_FAKEOUT,
            MOVE_SWORDSDANCE,
            MOVE_FLAMECHARGE,
            MOVE_PARTINGSHOT
        },
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 37,
        .species = SPECIES_SABLEYE,
        .moves = {
            MOVE_SWAGGER,
            MOVE_FOULPLAY,
            MOVE_KNOCKOFF,
            MOVE_SHADOWSNEAK
        },
        .ability = Ability_Hidden // Prankster
    },
    {
        .lvl = 37,
        .species = SPECIES_ORBEETLE,
        .moves = {
            MOVE_STICKYWEB,
            MOVE_CALMMIND,
            MOVE_PSYBEAM,
            MOVE_STRUGGLEBUG
        },
        .ability = Ability_2 // Frisk
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ChannelerVirginia[] = {
    {
        .lvl = 37,
        .species = SPECIES_JANGMO_O,
        .moves = {
            MOVE_SCREECH,
            MOVE_DRAGONDANCE,
            MOVE_HEADBUTT,
            MOVE_SCALESHOT
        },
        .ability = Ability_1 // Bulletproof
    },
    {
        .lvl = 37,
        .species = SPECIES_CENTISKORCH,
        .moves = {
            MOVE_COIL,
            MOVE_BUGBITE,
            MOVE_SMOKESCREEN,
            MOVE_FIRELASH
        },
        .ability = Ability_2 // White Smoke
    },
    {
        .lvl = 38,
        .species = SPECIES_BASTIODON,
        .moves = {
            MOVE_IRONDEFENSE,
            MOVE_ANCIENTPOWER,
            MOVE_METALSOUND,
            MOVE_HEADBUTT
        },
        .ability = Ability_1 // STurdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_LadyNisha[] = {
    {
        .lvl = 40,
        .species = SPECIES_SCOLIPEDE,
        .moves = {
            MOVE_DEFENSECURL,
            MOVE_ROLLOUT,
            MOVE_SCREECH,
            MOVE_POISONTAIL
        },
        .ability = Ability_Hidden // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_ScientistKent[] = {
    {
        .lvl = 37,
        .species = SPECIES_SNORUNT,
        .moves = {
            MOVE_ICYWIND,
            MOVE_PROTECT,
            MOVE_ASTONISH,
            MOVE_LEER
        },
        .ability = Ability_Hidden // Moody
    },
    {
        .lvl = 37,
        .species = SPECIES_BINACLE,
        .moves = {
            MOVE_SHELLSMASH,
            MOVE_ANCIENTPOWER,
            MOVE_SLASH,
            MOVE_WATERGUN
        },
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 37,
        .species = SPECIES_SALANDIT,
        .moves = {
            MOVE_NASTYPLOT,
            MOVE_EMBER,
            MOVE_OVERHEAT,
            MOVE_POISONFANG
        },
        .ability = Ability_Hidden // Oblivious
    },
    {
        .lvl = 38,
        .species = SPECIES_MUK_A,
        .moves = {
            MOVE_MINIMIZE,
            MOVE_ACIDARMOR,
            MOVE_TOXIC,
            MOVE_MUDSHOT
        },
        .ability = Ability_1 // Poison Touch
    }
};

const struct TrainerMonNoItemCustomMoves sParty_LaplazTownGym_RockerTomas[] = {
    {
        .lvl = 38,
        .species = SPECIES_BIBAREL,
        .moves = {
            MOVE_AMNESIA,
            MOVE_CURSE,
            MOVE_SUPERFANG,
            MOVE_WATERPULSE
        },
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 38,
        .species = SPECIES_WHIMSICOTT,
        .moves = {
            MOVE_COTTONGUARD,
            MOVE_TAILWIND,
            MOVE_SUBSTITUTE,
            MOVE_GIGADRAIN
        },
        .ability = Ability_1 // Prankster
    },
    {
        .lvl = 39,
        .species = SPECIES_QUILLADIN,
        .moves = {
            MOVE_BELLYDRUM,
            MOVE_NEEDLEARM,
            MOVE_BITE,
            MOVE_LEECHSEED
        },
        .ability = Ability_1 // Overgrow
    }
};

const struct TrainerMonItemCustomMoves sParty_LaplazTownGym_LeaderCasey[] = {
    {
        .lvl = 39,
        .species = SPECIES_NINJASK,
        .moves = {
            MOVE_XSCISSOR,
            MOVE_BATONPASS,
            MOVE_PROTECT,
            MOVE_SWORDSDANCE
        },
        .ability = Ability_1 // Speed Boost
    },
    {
        .lvl = 40,
        .species = SPECIES_SCRAGGY,
        .moves = {
            MOVE_POWERUPPUNCH,
            MOVE_SNARL,
            MOVE_DRAINPUNCH,
            MOVE_DRAGONDANCE
        },
        .ability = Ability_Hidden // Intimidate
    },
    {
        .lvl = 40,
        .species = SPECIES_BEHEEYEM,
        .moves = {
            MOVE_CALMMIND,
            MOVE_STOREDPOWER,
            MOVE_MIRACLEEYE,
            MOVE_THUNDERBOLT
        },
        .ability = Ability_2 // Synchronize 
    },
    {
        .lvl = 41,
        .species = SPECIES_KINGDRA,
        .moves = {
            MOVE_FOCUSENERGY,
            MOVE_SCALD,
            MOVE_TWISTER,
            MOVE_ICYWIND
        },
        .ability = Ability_2 // Sniper
    }
};

// #endregion

// #region Peradon Forest
const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_PokefanClark[] = {
    { .lvl = 38, .species = SPECIES_MIMIKYU },
    { .lvl = 38, .species = SPECIES_SLIGGOO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CollectorFernando[] = {
    { .lvl = 39, .species = SPECIES_DHELMISE },
    { .lvl = 39, .species = SPECIES_RAICHU_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BugCatcherLyle[] = {
   { .lvl = 37, .species = SPECIES_JOLTIK },
   { .lvl = 38, .species = SPECIES_SHIINOTIC },
   { .lvl = 38, .species = SPECIES_VIBRAVA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BeautyErica[] = {
    { .lvl = 40, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_PainterSheena[] = {
    { .lvl = 38, .species = SPECIES_ESPEON },
    { .lvl = 38, .species = SPECIES_MORPEKO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CamperRupert[] = {
    { .lvl = 40, .species = SPECIES_VENUSAUR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ScientistSean[] = {
    { .lvl = 39, .species = SPECIES_BEARTIC },
    { .lvl = 39, .species = SPECIES_BARBARACLE },
    { .lvl = 39, .species = SPECIES_KROKOROK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RockerRaphael[] = {
    { .lvl = 40, .species = SPECIES_VIBRAVA },
    { .lvl = 40, .species = SPECIES_RILLABOOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ChannelerRenee[] = {
    { .lvl = 37, .species = SPECIES_DUSKULL },
    { .lvl = 37, .species = SPECIES_SABLEYE },
    { .lvl = 38, .species = SPECIES_PHANTUMP },
    { .lvl = 38, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BlackbeltBrad[] = {
    { .lvl = 39, .species = SPECIES_TIMBURR },
    { .lvl = 40, .species = SPECIES_HERACROSS },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RuinManiacAlex[] = {
    { .lvl = 39, .species = SPECIES_VULLABY },
    { .lvl = 40, .species = SPECIES_RUNERIGUS },
    { .lvl = 41, .species = SPECIES_EXCADRILL },
};
// #endregion

// #region Route 12 & Scalding Spa
const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteJoanne[] = {
    { .lvl = 39, .species = SPECIES_PACHIRISU },
    { .lvl = 40, .species = SPECIES_HAKAMO_O },
    { .lvl = 40, .species = SPECIES_MAGCARGO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_PsychicTony[] = {
    { .lvl = 40, .species = SPECIES_MR_MIME_G },
    { .lvl = 42, .species = SPECIES_MR_RIME },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_HikerDwight[] = {
    { .lvl = 39, .species = SPECIES_ROGGENROLA },
    { .lvl = 39, .species = SPECIES_DRILBUR },
    { .lvl = 41, .species = SPECIES_CARBINK },
    { .lvl = 42, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteTrixie[] = {
    { .lvl = 41, .species = SPECIES_INCINEROAR },
    { .lvl = 41, .species = SPECIES_KANGASKHAN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_GentlemanGeoffrey[] = {
    { .lvl = 41, .species = SPECIES_STOUTLAND },
    { .lvl = 41, .species = SPECIES_BOLTUND },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_HikerEugene[] = {
    { .lvl = 43, .species = SPECIES_TORKOAL },
    { .lvl = 43, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_SupernerdStephen[] = {
    { .lvl = 42, .species = SPECIES_HAKAMO_O },
    { .lvl = 44, .species = SPECIES_CURSOLA },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_JugglerJohan[] = {
    { .lvl = 41, .species = SPECIES_ROLYCOLY },
    { .lvl = 41, .species = SPECIES_SALAZZLE },
    { .lvl = 42, .species = SPECIES_TURTONATOR },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_BlackbeltKieran[] = {
    { .lvl = 44, .species = SPECIES_EMBOAR },
};

const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena[] = {
    {
        .lvl = 42,
        .species = SPECIES_TOXICROAK,
        .moves = {
            MOVE_POISONJAB,
            MOVE_VENOSHOCK,
            MOVE_PROTECT,
            MOVE_DRAINPUNCH
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Dry Skin
    },
    {
        .lvl = 42,
        .species = SPECIES_PELIPPER,
        .moves = {
            MOVE_SURF,
            MOVE_STOCKPILE,
            MOVE_ROOST,
            MOVE_AIRSLASH
        },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 42,
        .species = SPECIES_SLIGGOO,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_DRAGONBREATH,
            MOVE_THUNDERBOLT,
            MOVE_MUDDYWATER
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_BugCatcherBrenan[] = {
    { .lvl = 42, .species = SPECIES_SNOM },
    { .lvl = 43, .species = SPECIES_FROSMOTH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierChantal[] = {
    { .lvl = 41, .species = SPECIES_BERGMITE },
    { .lvl = 42, .species = SPECIES_SWINUB },
    { .lvl = 42, .species = SPECIES_BERGMITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_HikerKumar[] = {
    { .lvl = 45, .species = SPECIES_STONJOURNER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierAubrey[] = {
    { .lvl = 43, .species = SPECIES_SNEASEL },
    { .lvl = 43, .species = SPECIES_GLACEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierLenora[] = {
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 43, .species = SPECIES_DELIBIRD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SkierMegan[] = {
    { .lvl = 43, .species = SPECIES_SNORUNT },
    { .lvl = 44, .species = SPECIES_PILOSWINE },
    { .lvl = 45, .species = SPECIES_FROSLASS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12West_SwimmerMGreg[] = {
    { .lvl = 49, .species = SPECIES_FRILLISH },
    { .lvl = 49, .species = SPECIES_BINACLE },
    { .lvl = 51, .species = SPECIES_JELLICENT },
};

// #endregion

// #region Bruccie Village & Calicin Bay
const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_LassMel[] = {
    {
        .lvl = 43,
        .species = SPECIES_MIENSHAO,
        .moves = {
            MOVE_UTURN,
            MOVE_FAKEOUT,
            MOVE_FORCEPALM,
            MOVE_NONE
        },
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 43,
        .species = SPECIES_GRENINJA,
        .moves = {
            MOVE_UTURN,
            MOVE_WATERPLEDGE,
            MOVE_ICYWIND,
            MOVE_WATERSHURIKEN
        },
        .ability = Ability_Hidden // Protean
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_BirdKeeperOwen[] = {
    {
        .lvl = 45,
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_WATERFALL,
            MOVE_CRUNCH,
            MOVE_RAINDANCE,
            MOVE_DRAGONDANCE
        },
        .ability = Ability_Hidden // Moxie
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_EngineerTommy[] = {
    {
        .lvl = 43,
        .species = SPECIES_SHEDINJA,
        .moves = {
            MOVE_SHADOWCLAW,
            MOVE_MUDSLAP,
            MOVE_CONFUSERAY,
            MOVE_BUGBUZZ
        },
        .ability = Ability_1 // Wonder Guard
    },
    {
        .lvl = 43,
        .species = SPECIES_BIBAREL,
        .moves = {
            MOVE_YAWN,
            MOVE_HYPERFANG,
            MOVE_CRUNCH,
            MOVE_AQUAJET
        },
        .ability = Ability_Hidden // Moody
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_HikerJoel[] = {
    {
        .lvl = 43,
        .species = SPECIES_MORPEKO,
        .moves = {
            MOVE_SPARK,
            MOVE_BITE,
            MOVE_BULLETSEED,
            MOVE_TORMENT
        },
        .ability = Ability_1 // Hunger Switch
    },
    {
        .lvl = 43,
        .species = SPECIES_EXCADRILL,
        .moves = {
            MOVE_SANDSTORM,
            MOVE_ROCKSLIDE,
            MOVE_DIG,
            MOVE_METALCLAW
        },
        .ability = Ability_2 // Sand Force
    },
    {
        .lvl = 44,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_COUNTER,
            MOVE_EARTHQUAKE,
            MOVE_HEAVYSLAM,
            MOVE_IRONDEFENSE
        },
        .ability = Ability_2 // Stamina
    }
};

const struct TrainerMonNoItemCustomMoves sParty_BruccieVillageGym_CrushGirlEllie[] = {
    {
        .lvl = 44, 
        .species = SPECIES_MIMIKYU,
        .moves = {
            MOVE_COPYCAT,
            MOVE_SUBSTITUTE,
            MOVE_DRAININGKISS,
            MOVE_GIGADRAIN
        },
        .ability = Ability_1 // Disguise
    },
    {
        .lvl = 44,
        .species = SPECIES_TOUCANNON,
        .moves = {
            MOVE_ROCKBLAST,
            MOVE_FURYATTACK,
            MOVE_BULLETSEED,
            MOVE_BEAKBLAST
        },
        .ability = Ability_2 // Skill Link
    }
};

const struct TrainerMonItemCustomMoves sParty_BruccieVillageGym_LeaderAbby[] = {
    {
        .lvl = 45,
        .species = SPECIES_RUNERIGUS,
        .moves = {
            MOVE_PROTECT,
            MOVE_DESTINYBOND,
            MOVE_SHADOWCLAW,
            MOVE_EARTHQUAKE
        },
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 46,
        .species = SPECIES_MALAMAR,
        .moves = {
            MOVE_SUPERPOWER,
            MOVE_HYPNOSIS,
            MOVE_PLUCK,
            MOVE_KNOCKOFF
        },
        .ability = Ability_1 // Contrary
    },
    {
        .lvl = 46,
        .species = SPECIES_DARMANITAN_G,
        .moves = {
            MOVE_ICICLECRASH,
            MOVE_SUNNYDAY,
            MOVE_FIREPUNCH,
            MOVE_BULKUP
        },
        .ability = Ability_Hidden // Zen Mode
    },
    {
        .lvl = 47,
        .species = SPECIES_TREVENANT,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_HORNLEECH,
            MOVE_HEX,
            MOVE_LEECHSEED
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SkierRita[] = {
    { .lvl = 42, .species = SPECIES_BERGMITE },
    { .lvl = 42, .species = SPECIES_DELIBIRD },
    { .lvl = 43, .species = SPECIES_CRABOMINABLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFFran[] = {
    { .lvl = 50, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMAngelo[] = {
    { .lvl = 47, .species = SPECIES_SHELLDER },
    { .lvl = 47, .species = SPECIES_BARBARACLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerMSebastian[] = {
    { .lvl = 47, .species = SPECIES_SEADRA },
    { .lvl = 47, .species = SPECIES_GASTRODON_EAST }
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_SwimmerFCorrine[] = {
    { .lvl = 49, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_FishermanOliver[] = {
    { .lvl = 42, .species = SPECIES_MAGIKARP },
    { .lvl = 42, .species = SPECIES_MAGIKARP },
    { .lvl = 44, .species = SPECIES_DRIZZILE },
    { .lvl = 44, .species = SPECIES_GYARADOS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoHugo[] = {
    { .lvl = 45, .species = SPECIES_THIEVUL },
    { .lvl = 46, .species = SPECIES_MANDIBUZZ },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoAnise[] = {
    { .lvl = 44, .species = SPECIES_GOLBAT },
    { .lvl = 45, .species = SPECIES_HAKAMO_O },
    { .lvl = 45, .species = SPECIES_SCRAFTY },
};

const struct TrainerMonItemCustomMoves sParty_CalicinBay_TeamPlutoYolena[] = {
    {
        .lvl = 46,
        .species = SPECIES_TOXICROAK,
        .moves = {
            MOVE_POISONJAB,
            MOVE_VENOSHOCK,
            MOVE_PROTECT,
            MOVE_DRAINPUNCH
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_2 // Dry Skin
    },
    {
        .lvl = 46,
        .species = SPECIES_PELIPPER,
        .moves = {
            MOVE_SURF,
            MOVE_STOCKPILE,
            MOVE_ROOST,
            MOVE_AIRSLASH
        },
        .heldItem = ITEM_DAMP_ROCK,
        .ability = Ability_2 // Drizzle
    },
    {
        .lvl = 47,
        .species = SPECIES_SLIGGOO,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_DRAGONPULSE,
            MOVE_THUNDER,
            MOVE_MUDDYWATER
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Hydration
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoClancy[] = {
    { .lvl = 45, .species = SPECIES_THIEVUL },
    { .lvl = 46, .species = SPECIES_TOXICROAK },
    { .lvl = 47, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_CalicinBay_TeamPlutoEna[] = {
    { .lvl = 45, .species = SPECIES_DUSKNOIR },
    { .lvl = 46, .species = SPECIES_SCOLIPEDE },
    { .lvl = 47, .species = SPECIES_CROBAT },
};
// #endregion

// #region Pluto HQ
const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoHeathcliff[] = {
    { .lvl = 45, .species = SPECIES_NOIBAT },
    { .lvl = 45, .species = SPECIES_KLANG },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B1F_ScientistSeamus[] = {
    { .lvl = 44, .species = SPECIES_ROTOM_FAN },
    { .lvl = 44, .species = SPECIES_HIPPOWDON_F },
    { .lvl = 45, .species = SPECIES_SLOWBRO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B1F_TeamPlutoColton[] = {
    { .lvl = 46, .species = SPECIES_TURTONATOR },
    { .lvl = 46, .species = SPECIES_THIEVUL },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B2F_ScientistWayne[] = {
    { .lvl = 45, .species = SPECIES_GRIMER_A },
    { .lvl = 44, .species = SPECIES_GRIMER_A },
    { .lvl = 44, .species = SPECIES_RATICATE_A },
    { .lvl = 45, .species = SPECIES_PILOSWINE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoDenise[] = {
    { .lvl = 45, .species = SPECIES_SALANDIT },
    { .lvl = 46, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B2F_TeamPlutoTheodore[] = {
    { .lvl = 47, .species = SPECIES_NOIVERN },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B3F_TeamPlutoYeon[] = {
    { .lvl = 47, .species = SPECIES_KLINKLANG },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMatty[] = {
    { .lvl = 46, .species = SPECIES_MORPEKO },
    { .lvl = 46, .species = SPECIES_TOXAPEX },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B4F_ScientistGary[] = {
    { .lvl = 45, .species = SPECIES_PINCURCHIN },
    { .lvl = 46, .species = SPECIES_PAWNIARD },
    { .lvl = 45, .species = SPECIES_STUNFISK_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B4F_TeamPlutoMay[] = {
    { .lvl = 44, .species = SPECIES_KOFFING_G },
    { .lvl = 44, .species = SPECIES_DRILBUR },
    { .lvl = 44, .species = SPECIES_SNEASEL },
    { .lvl = 44, .species = SPECIES_CACTURNE },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoClay[] = {
    { .lvl = 46, .species = SPECIES_ZOROARK },
    { .lvl = 47, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoVictor[] = {
    { .lvl = 44, .species = SPECIES_KOFFING_G },
    { .lvl = 46, .species = SPECIES_ZUBAT },
    { .lvl = 46, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B5F_TeamPlutoPaula[] = {
    { .lvl = 46, .species = SPECIES_KROKOROK },
    { .lvl = 46, .species = SPECIES_THIEVUL },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoGiana[] = {
    { .lvl = 44, .species = SPECIES_VENIPEDE },
    { .lvl = 45, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 46, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B6F_ScientistOrson[] = {
    { .lvl = 47, .species = SPECIES_ROTOM_WASH },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B6F_TeamPlutoQuinn[] = {
    { .lvl = 44, .species = SPECIES_SNEASEL },
    { .lvl = 44, .species = SPECIES_SALANDIT },
    { .lvl = 44, .species = SPECIES_SANDILE },
    { .lvl = 45, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoLayla[] = {
    { .lvl = 47, .species = SPECIES_INCINEROAR },
};

const struct TrainerMonItemDefaultMoves sParty_PlutoHQ_B7F_ScientistNico[] = {
    { .lvl = 45, .species = SPECIES_GRIMER_A },
    { .lvl = 45, .species = SPECIES_EMOLGA },
    { .lvl = 46, .species = SPECIES_TOXTRICITY },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoMitch[] = {
    { .lvl = 46, .species = SPECIES_INKAY },
    { .lvl = 46, .species = SPECIES_MR_RIME },
};

const struct TrainerMonNoItemDefaultMoves sParty_PlutoHQ_B7F_TeamPlutoRichard[] = {
    { .lvl = 46, .species = SPECIES_LUCARIO },
    { .lvl = 47, .species = SPECIES_MALAMAR },
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B4F_TeamPlutoAdminIrene[] = {
    {
        .lvl = 48,
        .species = SPECIES_NOCTOWL,
        .moves = {
            MOVE_ROOST,
            MOVE_MOONBLAST,
            MOVE_AIRSLASH,
            MOVE_NIGHTSHADE
        },
        .ability = Ability_Hidden // Tinted Lens
    },
    {
        .lvl = 48,
        .species = SPECIES_MUK_A,
        .moves = {
            MOVE_KNOCKOFF,
            MOVE_ACIDARMOR,
            MOVE_POISONJAB,
            MOVE_ICEPUNCH
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 48,
        .species = SPECIES_MISMAGIUS,
        .moves = {
            MOVE_MYSTICALFIRE,
            MOVE_SHADOWBALL,
            MOVE_PSYSHOCK,
            MOVE_DESTINYBOND
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 49,
        .species = SPECIES_SALAZZLE,
        .moves = {
            MOVE_NASTYPLOT,
            MOVE_FLAMETHROWER,
            MOVE_TOXIC,
            MOVE_VENOSHOCK
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Corrosion
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B7F_TeamPlutoAdminRonald[] = {
    {
        .lvl = 48,
        .species = SPECIES_KROOKODILE,
        .moves = {
            MOVE_CRUNCH,
            MOVE_EARTHQUAKE,
            MOVE_THUNDERFANG,
            MOVE_STEALTHROCK
        },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 48,
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_CURSE,
            MOVE_GYROBALL,
            MOVE_POWERWHIP
        },
        .heldItem = ITEM_OCCA_BERRY,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 48,
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_FAKEOUT,
            MOVE_ICICLECRASH,
            MOVE_THROATCHOP,
            MOVE_AERIALACE
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 49,
        .species = SPECIES_SCRAFTY,
        .moves = {
            MOVE_DRAGONDANCE,
            MOVE_POWERUPPUNCH,
            MOVE_CRUNCH,
            MOVE_POISONJAB
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Shed Skin
    }
};

const struct TrainerMonItemCustomMoves sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis[] = {
    {
        .lvl = 49,
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_CLEARSMOG,
            MOVE_SPORE,
            MOVE_SYNTHESIS,
            MOVE_SLUDGEBOMB
        },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 49,
        .species = SPECIES_KOMMO_O,
        .moves = {
            MOVE_BELLYDRUM,
            MOVE_DRAGONCLAW,
            MOVE_POISONJAB,
            MOVE_CLOSECOMBAT
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Overcoat
    },
    {
        .lvl = 49,
        .species = SPECIES_DUSKNOIR,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_SHADOWPUNCH,
            MOVE_BRICKBREAK,
            MOVE_LEECHLIFE
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 49,
        .species = SPECIES_EXCADRILL,
        .moves = {
            MOVE_EARTHQUAKE,
            MOVE_SWORDSDANCE,
            MOVE_ROCKSLIDE,
            MOVE_IRONHEAD
        },
        .ability = Ability_Hidden // Mold Breaker
    },
    {
        .lvl = 50,
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_DRAGONDANCE,
            MOVE_WATERFALL,
            MOVE_ICEFANG,
            MOVE_CRUNCH
        },
        .heldItem = ITEM_GYARADOSITE,
        .ability = Ability_1 // Intimidate
    },
};
// #endregion

// #region Route 18
const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJasper[] = {
    { .lvl = 46, .species = SPECIES_MARSHTOMP },
    { .lvl = 46, .species = SPECIES_LANTURN },
    { .lvl = 47, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_TriathleteDeborah[] = {
    { .lvl = 47, .species = SPECIES_CINDERACE },
    { .lvl = 47, .species = SPECIES_PASSIMIAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_SwimmerJudie[] = {
    { .lvl = 49, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BirdKeeperKirk[] = {
    { .lvl = 47, .species = SPECIES_DECIDUEYE },
    { .lvl = 48, .species = SPECIES_TALONFLAME }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_LassEmma[] = {
    { .lvl = 46, .species = SPECIES_CUTIEFLY },
    { .lvl = 47, .species = SPECIES_FLOETTE_BLUE },
    { .lvl = 47, .species = SPECIES_SYLVEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route18_BlackbeltRohan[] = {
    { .lvl = 49, .species = SPECIES_CONKELDURR }
};
// #endregion

// #region Route 16
const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerGale[] = {
    { .lvl = 51, .species = SPECIES_CARVANHA },
    { .lvl = 51, .species = SPECIES_CARVANHA },
    { .lvl = 52, .species = SPECIES_SHARPEDO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerAmy[] = {
    { .lvl = 54, .species = SPECIES_LAPRAS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_BirdKeeperTrevor[] = {
    { .lvl = 48, .species = SPECIES_HOOTHOOT },
    { .lvl = 48, .species = SPECIES_NOCTOWL },
    { .lvl = 49, .species = SPECIES_CORVISQUIRE },
    { .lvl = 49, .species = SPECIES_SKARMORY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_LadyMaria[] = {
    { .lvl = 55, .species = SPECIES_ROSERADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerChristina[] = {
    { .lvl = 52, .species = SPECIES_CROCONAW },
    { .lvl = 53, .species = SPECIES_PELIPPER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerPhillip[] = {
    { .lvl = 50, .species = SPECIES_SEADRA },
    { .lvl = 51, .species = SPECIES_SHELLDER },
    { .lvl = 52, .species = SPECIES_CLOYSTER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerLester[] = {
    { .lvl = 54, .species = SPECIES_JELLICENT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerWendy[] = {
    { .lvl = 52, .species = SPECIES_MAREANIE },
    { .lvl = 52, .species = SPECIES_CURSOLA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberCody[] = {
    { .lvl = 51, .species = SPECIES_LYCANROC },
    { .lvl = 52, .species = SPECIES_CHESNAUGHT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_TuberLeslie[] = {
    { .lvl = 51, .species = SPECIES_KIRLIA },
    { .lvl = 52, .species = SPECIES_VESPIQUEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route16_SwimmerClementine[] = {
    { .lvl = 52, .species = SPECIES_GASTRODON_EAST },
    { .lvl = 52, .species = SPECIES_GASTRODON }
};
// #endregion

// #region Route 14
const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerIvan[] = {
    { .lvl = 48, .species = SPECIES_MAGIKARP },
    { .lvl = 48, .species = SPECIES_MARSHTOMP },
    { .lvl = 48, .species = SPECIES_GYARADOS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_HikerClifford[] = {
    { .lvl = 47, .species = SPECIES_ROGGENROLA },
    { .lvl = 48, .species = SPECIES_CARBINK },
    { .lvl = 49, .species = SPECIES_MUDSDALE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanEsteban[] = {
    { .lvl = 48, .species = SPECIES_DRATINI },
    { .lvl = 49, .species = SPECIES_DRAGONAIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_FishermanTucker[] = {
    { .lvl = 50, .species = SPECIES_TOXAPEX }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerEleanor[] = {
    { .lvl = 46, .species = SPECIES_HORSEA },
    { .lvl = 46, .species = SPECIES_HORSEA },
    { .lvl = 46, .species = SPECIES_CHINCHOU },
    { .lvl = 47, .species = SPECIES_SEADRA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_BlackbeltJoaquin[] = {
    { .lvl = 47, .species = SPECIES_PASSIMIAN },
    { .lvl = 48, .species = SPECIES_CRABRAWLER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerChris[] = {
    { .lvl = 47, .species = SPECIES_BINACLE },
    { .lvl = 47, .species = SPECIES_LANTURN },
    { .lvl = 48, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_YoungsterFreddie[] = {
    { .lvl = 46, .species = SPECIES_RATTATA_A },
    { .lvl = 46, .species = SPECIES_RATICATE_A },
    { .lvl = 46, .species = SPECIES_BOLTUND },
    { .lvl = 47, .species = SPECIES_TRUMBEAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_PsychicTobin[] = {
    { .lvl = 48, .species = SPECIES_ELGYEM },
    { .lvl = 48, .species = SPECIES_ORANGURU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route14_SwimmerMacie[] = {
    { .lvl = 46, .species = SPECIES_SHELLDER },
    { .lvl = 47, .species = SPECIES_OSHAWOTT },
    { .lvl = 47, .species = SPECIES_DEWOTT }
};

// #endregion

// #region Route 15 North and South
const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerMiles[] = {
    { .lvl = 50, .species = SPECIES_SHELLDER },
    { .lvl = 49, .species = SPECIES_SHELLDER },
    { .lvl = 50, .species = SPECIES_CLOYSTER },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerFiona[] = {
    { .lvl = 52, .species = SPECIES_LAPRAS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_HikerKlaus[] = {
    { .lvl = 50, .species = SPECIES_STONJOURNER },
    { .lvl = 50, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerUrsula[] = {
    { .lvl = 50, .species = SPECIES_CARVANHA },
    { .lvl = 51, .species = SPECIES_SHARPEDO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SwimmerQuincy[] = {
    { .lvl = 51, .species = SPECIES_PRINPLUP },
    { .lvl = 52, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_CoolTrainerWesley[] = {
    { .lvl = 52, .species = SPECIES_ROTOM_HEAT },
    { .lvl = 52, .species = SPECIES_GARCHOMP },
    { .lvl = 53, .species = SPECIES_TOGEKISS }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_SuperNerdEthan[] = {
    { .lvl = 52, .species = SPECIES_GOODRA },
    { .lvl = 52, .species = SPECIES_RAICHU_A }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15North_ChannelerLila[] = {
    { .lvl = 49, .species = SPECIES_MISDREAVUS },
    { .lvl = 49, .species = SPECIES_MISDREAVUS },
    { .lvl = 50, .species = SPECIES_SABLEYE },
    { .lvl = 50, .species = SPECIES_CURSOLA }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerGerald[] = {
    { .lvl = 51, .species = SPECIES_FERALIGATR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerAlexandra[] = {
    { .lvl = 49, .species = SPECIES_CHINCHOU },
    { .lvl = 49, .species = SPECIES_WINGULL },
    { .lvl = 50, .species = SPECIES_LANTURN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerBernard[] = {
    { .lvl = 52, .species = SPECIES_CRABOMINABLE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerHarold[] = {
    { .lvl = 49, .species = SPECIES_CORPHISH },
    { .lvl = 51, .species = SPECIES_CRAWDAUNT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerMelinda[] = {
    { .lvl = 48, .species = SPECIES_SQUIRTLE },
    { .lvl = 48, .species = SPECIES_HORSEA },
    { .lvl = 48, .species = SPECIES_BINACLE },
    { .lvl = 50, .species = SPECIES_SWAMPERT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_BlackbeltFranklin[] = {
    { .lvl = 50, .species = SPECIES_FALINKS },
    { .lvl = 51, .species = SPECIES_SCRAFTY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route15South_SwimmerPatricia[] = {
    { .lvl = 50, .species = SPECIES_DRATINI },
    { .lvl = 52, .species = SPECIES_DRAGONAIR },
};
// #endregion

// #region Seppire Cove
const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerValerie[] = {
    { .lvl = 52, .species = SPECIES_LAPRAS },
    { .lvl = 52, .species = SPECIES_PINCURCHIN },
    { .lvl = 53, .species = SPECIES_CLOYSTER },
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_SwimmerIchabod[] = {
    { .lvl = 54, .species = SPECIES_DHELMISE }
};

const struct TrainerMonNoItemDefaultMoves sParty_SeppireCove_RuinManiacCarter[] = {
    { .lvl = 53, .species = SPECIES_COFAGRIGUS },
    { .lvl = 53, .species = SPECIES_STONJOURNER },
};
// #endregion

// #region Route 19
const struct TrainerMonNoItemDefaultMoves sParty_Route19_LassSamantha[] = {
    { .lvl = 48, .species = SPECIES_COMFEY },
    { .lvl = 49, .species = SPECIES_VESPIQUEN },
    { .lvl = 48, .species = SPECIES_FROSMOTH }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_CoolTrainerRose[] = {
    { .lvl = 50, .species = SPECIES_SALAZZLE },
    { .lvl = 50, .species = SPECIES_DRAGONAIR },
    { .lvl = 50, .species = SPECIES_EMPOLEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhineas[] = {
    { .lvl = 49, .species = SPECIES_JELLICENT },
    { .lvl = 50, .species = SPECIES_TURTONATOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route19_PokefanPhoebe[] = {
    { .lvl = 49, .species = SPECIES_JELLICENT_F },
    { .lvl = 50, .species = SPECIES_ORANGURU }
};
// #endregion

// #region Emraldin Quay
const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_ChannelerMarguerite[] = {
    {
        .lvl = 1,
        .species = SPECIES_QUILLADIN, // Steel / Ground
        .moves = {
            MOVE_METALCLAW,
            MOVE_BULLDOZE,
            MOVE_BRICKBREAK,
            MOVE_SPIKES
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_PRIMEAPE, // Bug / Dark
        .moves = {
            MOVE_UTURN,
            MOVE_THROATCHOP,
            MOVE_SCREECH,
            MOVE_CROSSCHOP
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_MISMAGIUS, // Fire / Fairy
        .moves = {
            MOVE_MYSTICALFIRE,
            MOVE_DAZZLINGGLEAM,
            MOVE_NASTYPLOT,
            MOVE_POWERGEM
        },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_NinjaBoyJulien[] = {
    {
        .lvl = 1,
        .species = SPECIES_LILEEP, // Normal / Ghost
        .moves = {
            MOVE_CURSE,
            MOVE_ATTRACT,
            MOVE_GIGADRAIN,
            MOVE_BULLDOZE
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_FRILLISH, // Ice / Poison
        .moves = {
            MOVE_ICEBEAM,
            MOVE_TOXIC,
            MOVE_RAINDANCE,
            MOVE_BRINE
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_NIDOKING, // Water / Fighting
        .moves = {
            MOVE_SURF,
            MOVE_BRICKBREAK,
            MOVE_BODYSLAM,
            MOVE_SUBSTITUTE
        },
        .ability = Ability_Random_1_2
    },
};

const struct TrainerMonNoItemCustomMoves sParty_EmraldinQuay_BugCatcherPerry[] = {
    {
        .lvl = 1,
        .species = SPECIES_SUNFLORA, // Grass / Fire
        .moves = {
            MOVE_SYNTHESIS,
            MOVE_SUNNYDAY,
            MOVE_WEATHERBALL,
            MOVE_SOLARBEAM
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_SLOWBRO, // Electric / Fire
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_FLAMETHROWER,
            MOVE_SURF,
            MOVE_PSYSHOCK
        },
        .ability = Ability_Random_1_2
    },
    {
        .lvl = 1,
        .species = SPECIES_FLYGON, // Bug / Dragon
        .moves = {
            MOVE_BUGBITE,
            MOVE_DRAGONDANCE,
            MOVE_THUNDERPUNCH,
            MOVE_EARTHQUAKE
        },
        .ability = Ability_Random_1_2
    },
};
// #endregion

// #region Route 23
const struct TrainerMonNoItemDefaultMoves sParty_Route23_BirdKeeperTyrone[] = {
    { .lvl = 52, .species = SPECIES_PELIPPER },
    { .lvl = 52, .species = SPECIES_FLETCHINDER },
    { .lvl = 53, .species = SPECIES_DECIDUEYE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GamblerGordon[] = {
    { .lvl = 50, .species = SPECIES_YAMASK_G },
    { .lvl = 50, .species = SPECIES_GURDURR },
    { .lvl = 51, .species = SPECIES_HERACROSS },
    { .lvl = 51, .species = SPECIES_MIMIKYU },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_SuperNerdEmmett[] = {
    { .lvl = 53, .species = SPECIES_DRAGONAIR },
    { .lvl = 53, .species = SPECIES_DHELMISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_GentlemanRussell[] = {
    { .lvl = 53, .species = SPECIES_STOUTLAND },
    { .lvl = 53, .species = SPECIES_MANDIBUZZ },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_CrushGirlLily[] = {
    { .lvl = 50, .species = SPECIES_SCRAGGY },
    { .lvl = 51, .species = SPECIES_FALINKS },
    { .lvl = 52, .species = SPECIES_CONKELDURR },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route23_BeautyMiranda[] = {
    { .lvl = 52, .species = SPECIES_SLOWPOKE },
    { .lvl = 52, .species = SPECIES_SLOWPOKE_G },
    { .lvl = 53, .species = SPECIES_SLOWPOKE },
};
// #endregion

// #region Route 20
const struct TrainerMonNoItemDefaultMoves sParty_Route20_PsychicMcKenzie[] = {
    { .lvl = 49, .species = SPECIES_BEHEEYEM },
    { .lvl = 50, .species = SPECIES_ORBEETLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_PicknickerWhitney[] = {
    { .lvl = 48, .species = SPECIES_FLETCHINDER },
    { .lvl = 48, .species = SPECIES_RIBOMBEE },
    { .lvl = 50, .species = SPECIES_TOXICROAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_TriathleteLena[] = {
    { .lvl = 50, .species = SPECIES_MEGANIUM },
    { .lvl = 50, .species = SPECIES_WHIMSICOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_EngineerHomer[] = {
    { .lvl = 50, .species = SPECIES_HELIOLISK },
    { .lvl = 51, .species = SPECIES_KLINKLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_CrushGirlRoxy[] = {
    { .lvl = 53, .species = SPECIES_LUCARIO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_HikerRoyce[] = {
    { .lvl = 50, .species = SPECIES_CARBINK },
    { .lvl = 50, .species = SPECIES_SHUCKLE },
    { .lvl = 51, .species = SPECIES_STUNFISK_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_SuperNerdElliot[] = {
    { .lvl = 52, .species = SPECIES_CARNIVINE },
    { .lvl = 52, .species = SPECIES_KANGASKHAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_YoungsterDewey[] = {
    { .lvl = 50, .species = SPECIES_HERDIER },
    { .lvl = 50, .species = SPECIES_LYCANROC_N },
    { .lvl = 51, .species = SPECIES_VIKAVOLT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_JugglerHiram[] = {
    { .lvl = 52, .species = SPECIES_MAWILE },
    { .lvl = 53, .species = SPECIES_MR_MIME_G }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route20_NurseJessie[] = {
    { .lvl = 52, .species = SPECIES_COMFEY },
    { .lvl = 52, .species = SPECIES_CHANSEY }
};
// #endregion

// #region Route 22
const struct TrainerMonNoItemDefaultMoves sParty_Route22_CoolTrainer_Gail[] = {
    { .lvl = 51, .species = SPECIES_GASTRODON },
    { .lvl = 52, .species = SPECIES_SKARMORY },
    { .lvl = 53, .species = SPECIES_GARCHOMP }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_ScientistLarry[] = {
    { .lvl = 52, .species = SPECIES_WEEZING_G },
    { .lvl = 52, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_SrAndJr_AlmaAndMai[] = {
    { .lvl = 51, .species = SPECIES_LEAFEON },
    { .lvl = 51, .species = SPECIES_ORANGURU },
    { .lvl = 52, .species = SPECIES_RIBOMBEE },
    { .lvl = 52, .species = SPECIES_SABLEYE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_JugglerChauncy[] = {
    { .lvl = 52, .species = SPECIES_BRIONNE },
    { .lvl = 52, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route22_BurglarMose[] = {
    { .lvl = 53, .species = SPECIES_BISHARP },
    { .lvl = 54, .species = SPECIES_TOXICROAK },
    { .lvl = 54, .species = SPECIES_SCRAFTY }
};
// #endregion

// #region Route 21
const struct TrainerMonNoItemDefaultMoves sParty_Route21_PokefanWalter[] = {
    { .lvl = 51, .species = SPECIES_BIBAREL },
    { .lvl = 51, .species = SPECIES_PIGNITE },
    { .lvl = 52, .species = SPECIES_MAGCARGO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_CollectorEric[] = {
    { .lvl = 53, .species = SPECIES_ROTOM },
    { .lvl = 53, .species = SPECIES_KANGASKHAN }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_HikerRicardo[] = {
    { .lvl = 52, .species = SPECIES_CARKOL },
    { .lvl = 53, .species = SPECIES_GOGOAT },
    { .lvl = 52, .species = SPECIES_MUDSDALE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_DragonTamerTanner[] = {
    { .lvl = 55, .species = SPECIES_DRAGONITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_ParasolLadyKatrina[] = {
    { .lvl = 52, .species = SPECIES_FLAAFFY },
    { .lvl = 52, .species = SPECIES_EMOLGA },
    { .lvl = 53, .species = SPECIES_SYLVEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_NinjaBoyIshan[] = {
    { .lvl = 51, .species = SPECIES_MIMIKYU },
    { .lvl = 51, .species = SPECIES_WOBBUFFET },
    { .lvl = 52, .species = SPECIES_SUDOWOODO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route21_RockerAxel[] = {
    { .lvl = 51, .species = SPECIES_VIBRAVA },
    { .lvl = 51, .species = SPECIES_TOXTRICITY },
    { .lvl = 52, .species = SPECIES_RILLABOOM }
};
// #endregion

// #region Secret Trail
const struct TrainerMonNoItemDefaultMoves sParty_SecretTrail_ChannelerHeather[] = {
    { .lvl = 54, .species = SPECIES_NOCTOWL },
    { .lvl = 54, .species = SPECIES_PHANTUMP },
    { .lvl = 54, .species = SPECIES_SABLEYE }
};
// #endregion

// #region Mimmett Jungle
const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ScientistSilas[] = {
    { .lvl = 51, .species = SPECIES_ESPEON },
    { .lvl = 52, .species = SPECIES_SERPERIOR },
    { .lvl = 52, .species = SPECIES_KLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_RuinManiacWinston[] = {
    { .lvl = 51, .species = SPECIES_VULLABY },
    { .lvl = 53, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BlackbeltLouis[] = {
    { .lvl = 54, .species = SPECIES_CONKELDURR }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_ChannelerFreyja[] = {
    { .lvl = 51, .species = SPECIES_MISDREAVUS },
    { .lvl = 51, .species = SPECIES_MISDREAVUS },
    { .lvl = 52, .species = SPECIES_SABLEYE },
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_BugCatcherNeil[] = {
    { .lvl = 52, .species = SPECIES_GALVANTULA },
    { .lvl = 53, .species = SPECIES_VIKAVOLT }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_FishermanJerry[] = {
    { .lvl = 52, .species = SPECIES_JELLICENT },
    { .lvl = 53, .species = SPECIES_GASTRODON }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PokefanSusan[] = {
    { .lvl = 52, .species = SPECIES_LOPUNNY },
    { .lvl = 53, .species = SPECIES_FROSMOTH }
};

const struct TrainerMonNoItemDefaultMoves sParty_MimmettJungle_PsychicWanda[] = {
    { .lvl = 54, .species = SPECIES_HATTERENE }
};
// #endregion

// #region Tsarvosa City
const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_StatsDojo_Kaito[] = {
    {
        .lvl = 51,
        .species = SPECIES_GOGOAT,
        .moves = {
            MOVE_SEEDBOMB,
            MOVE_BULKUP,
            MOVE_HORNLEECH,
            MOVE_BULLDOZE
        },
        .ability = Ability_1 // Sap Sipper
    },
    {
        .lvl = 52,
        .species = SPECIES_TURTONATOR,
        .moves = {
            MOVE_SHELLTRAP,
            MOVE_FLAMETHROWER,
            MOVE_OUTRAGE,
            MOVE_IRONDEFENSE
        },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 52,
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_RETALIATE,
            MOVE_NIGHTSLASH,
            MOVE_IRONHEAD,
            MOVE_XSCISSOR
        },
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 53,
        .species = SPECIES_CONKELDURR,
        .moves = {
            MOVE_STONEEDGE,
            MOVE_HAMMERARM,
            MOVE_BULKUP,
            MOVE_FIREPUNCH
        },
        .ability = Ability_2 // Sheer Force
    }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP1[] = {
    { .lvl = 1, .species = SPECIES_SLAKOTH },
    { .lvl = 1, .species = SPECIES_SHROOMISH },
    { .lvl = 1, .species = SPECIES_HAPPINY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP2[] = {
    { .lvl = 1, .species = SPECIES_NOCTOWL },
    { .lvl = 1, .species = SPECIES_VAPOREON },
    { .lvl = 1, .species = SPECIES_CHANSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_ZacharyHP3[] = {
    { .lvl = 1, .species = SPECIES_SLAKING },
    { .lvl = 1, .species = SPECIES_SLAKING },
    { .lvl = 1, .species = SPECIES_BLISSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack1[] = {
    { .lvl = 1, .species = SPECIES_NIDORAN_M },
    { .lvl = 1, .species = SPECIES_MUDKIP },
    { .lvl = 1, .species = SPECIES_PIKIPEK }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack2[] = {
    { .lvl = 1, .species = SPECIES_NIDORINO },
    { .lvl = 1, .species = SPECIES_MARSHTOMP },
    { .lvl = 1, .species = SPECIES_TRUMBEAK }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_NelsonAttack3[] = {
    { .lvl = 1, .species = SPECIES_NIDOKING },
    { .lvl = 1, .species = SPECIES_SWAMPERT },
    { .lvl = 1, .species = SPECIES_TOUCANNON }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense1[] = {
    { .lvl = 1, .species = SPECIES_KLINK },
    { .lvl = 1, .species = SPECIES_CHESPIN },
    { .lvl = 1, .species = SPECIES_ROLYCOLY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense2[] = {
    { .lvl = 1, .species = SPECIES_KLANG },
    { .lvl = 1, .species = SPECIES_QUILLADIN },
    { .lvl = 1, .species = SPECIES_CARKOL }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_DionDefense3[] = {
    { .lvl = 1, .species = SPECIES_KLINKLANG },
    { .lvl = 1, .species = SPECIES_CHESNAUGHT },
    { .lvl = 1, .species = SPECIES_COALOSSAL }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1[] = {
    { .lvl = 1, .species = SPECIES_MAREEP },
    { .lvl = 1, .species = SPECIES_RALTS },
    { .lvl = 1, .species = SPECIES_OSHAWOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2[] = {
    { .lvl = 1, .species = SPECIES_FLAAFFY },
    { .lvl = 1, .species = SPECIES_KIRLIA },
    { .lvl = 1, .species = SPECIES_DEWOTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3[] = {
    { .lvl = 1, .species = SPECIES_AMPHAROS },
    { .lvl = 1, .species = SPECIES_GARDEVOIR },
    { .lvl = 1, .species = SPECIES_SAMUROTT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1[] = {
    { .lvl = 1, .species = SPECIES_FLABEBE_ORANGE },
    { .lvl = 1, .species = SPECIES_BLIPBUG },
    { .lvl = 1, .species = SPECIES_GOOMY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2[] = {
    { .lvl = 1, .species = SPECIES_FLOETTE_ORANGE },
    { .lvl = 1, .species = SPECIES_DOTTLER },
    { .lvl = 1, .species = SPECIES_SLIGGOO }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3[] = {
    { .lvl = 1, .species = SPECIES_FLORGES_ORANGE },
    { .lvl = 1, .species = SPECIES_ORBEETLE },
    { .lvl = 1, .species = SPECIES_GOODRA }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed1[] = {
    { .lvl = 1, .species = SPECIES_SNIVY },
    { .lvl = 1, .species = SPECIES_ZUBAT },
    { .lvl = 1, .species = SPECIES_SCORBUNNY }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed2[] = {
    { .lvl = 1, .species = SPECIES_SERVINE },
    { .lvl = 1, .species = SPECIES_GOLBAT },
    { .lvl = 1, .species = SPECIES_RABOOT }
};

const struct TrainerMonNoItemDefaultMoves sParty_TsarvosaCity_StatsDojo_SidneySpeed3[] = {
    { .lvl = 1, .species = SPECIES_SERPERIOR },
    { .lvl = 1, .species = SPECIES_CROBAT },
    { .lvl = 1, .species = SPECIES_CINDERACE }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin1[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYPHLOSION,
        .moves = {
            MOVE_LAVAPLUME,
            MOVE_HIDDENPOWER,
            MOVE_AERIALACE,
            MOVE_EXTRASENSORY
        },
        .heldItem = ITEM_CHARCOAL,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GALLADE,
        .moves = {
            MOVE_PSYCHOCUT,
            MOVE_LEAFBLADE,
            MOVE_CLOSECOMBAT,
            MOVE_SWORDSDANCE
        },
        .heldItem = ITEM_GALLADITE,
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NIDOKING,
        .moves = {
            MOVE_TOXIC,
            MOVE_VENOSHOCK,
            MOVE_DRILLRUN,
            MOVE_SURF
        },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_2 // Rivalry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JELLICENT,
        .moves = {
            MOVE_SCALD,
            MOVE_ICEBEAM,
            MOVE_OMINOUSWIND,
            MOVE_RECOVER
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SHIINOTIC,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_MOONBLAST,
            MOVE_CHARGEBEAM,
            MOVE_STRENGTHSAP
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Effect Spore
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Collin2[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAMOSWINE,
        .moves = {
            MOVE_EARTHQUAKE,
            MOVE_ICICLECRASH,
            MOVE_ICESHARD,
            MOVE_ROCKTOMB
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TREVENANT,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_HORNLEECH,
            MOVE_SHADOWCLAW,
            MOVE_GROWTH
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_Hidden // Harvest
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VOLCARONA,
        .moves = {
            MOVE_FIERYDANCE,
            MOVE_QUIVERDANCE,
            MOVE_BUGBUZZ,
            MOVE_HURRICANE
        },
        .heldItem = ITEM_CHARTI_BERRY,
        .ability = Ability_1 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYRANTRUM,
        .moves = {
            MOVE_HEADSMASH,
            MOVE_EARTHQUAKE,
            MOVE_CRUNCH,
            MOVE_DRAGONCLAW
        },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_Hidden // Rock Head
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BLASTOISE,
        .moves = {
            MOVE_WAVECRASH,
            MOVE_SHELLSMASH,
            MOVE_CRUNCH,
            MOVE_EARTHQUAKE
        },
        .heldItem = ITEM_BLASTOISINITE_G,
        .ability = Ability_Hidden // Rain Dish
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal1[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_AIRSLASH,
            MOVE_DAZZLINGGLEAM,
            MOVE_FIREBLAST,
            MOVE_NASTYPLOT
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VENUSAUR,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_SLUDGEBOMB,
            MOVE_TOXIC,
            MOVE_PROTECT
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Chlorophyll
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CHARIZARD,
        .moves = {
            MOVE_FLAMETHROWER,
            MOVE_SOLARBEAM,
            MOVE_TAILWIND,
            MOVE_PROTECT
        },
        .heldItem = ITEM_CHARIZARDITE_Y,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARCHOMP,
        .moves = {
            MOVE_SCALESHOT,
            MOVE_EARTHQUAKE,
            MOVE_FIREFANG,
            MOVE_SWORDSDANCE
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Rough Skin
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CORVIKNIGHT,
        .moves = {
            MOVE_BRAVEBIRD,
            MOVE_UTURN,
            MOVE_TAUNT,
            MOVE_ROOST
        },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Pressure
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCity_DevTeam_Crystal2[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EMBOAR,
        .moves = {
            MOVE_FLAREBLITZ,
            MOVE_SUPERPOWER,
            MOVE_HEADSMASH,
            MOVE_WILDCHARGE
        },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Reckless
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_WATERFALL,
            MOVE_ICEFANG,
            MOVE_EARTHQUAKE,
            MOVE_CRUNCH
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_Hidden // Moxie
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROTOM_WASH,
        .moves = {
            MOVE_HYDROPUMP,
            MOVE_VOLTSWITCH,
            MOVE_NASTYPLOT,
            MOVE_WILLOWISP
        },
        .heldItem = ITEM_SITRUS_BERRY,
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_SPORE,
            MOVE_RAGEPOWDER,
            MOVE_PROTECT
        },
        .heldItem = ITEM_MENTAL_HERB,
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARDEVOIR,
        .moves = {
            MOVE_HYPERVOICE,
            MOVE_PSYCHIC,
            MOVE_HIDDENPOWER,
            MOVE_PROTECT
        },
        .heldItem = ITEM_GARDEVOIRITE,
        .ability = Ability_Hidden // Telepathy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Noam[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DITTO,
        .moves = {
            MOVE_TRANSFORM,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STOUTLAND,
        .moves = {
            MOVE_RETALIATE,
            MOVE_FIREFANG,
            MOVE_PLAYROUGH,
            MOVE_ROAR
        },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LOPUNNY,
        .moves = {
            MOVE_REVERSAL,
            MOVE_HEADBUTT,
            MOVE_REST,
            MOVE_SLEEPTALK
        },
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KANGASKHAN,
        .moves = {
            MOVE_CRUNCH,
            MOVE_FAKEOUT,
            MOVE_BODYSLAM,
            MOVE_WORKUP
        },
        .ability = Ability_2 // Scrappy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ashley[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAGCARGO,
        .moves = {
            MOVE_SHELLSMASH,
            MOVE_ROCKSLIDE,
            MOVE_RECOVER,
            MOVE_FLAMETHROWER
        },
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HOUNDOOM,
        .moves = {
            MOVE_NASTYPLOT,
            MOVE_CRUNCH,
            MOVE_FLAMETHROWER,
            MOVE_MUDSHOT
        },
        .ability = Ability_Hidden // Unnerve
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SALAZZLE,
        .moves = {
            MOVE_FIREBLAST,
            MOVE_TOXIC,
            MOVE_DRAGONPULSE,
            MOVE_VENOSHOCK
        },
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLAREON,
        .moves = {
            MOVE_FLAREBLITZ,
            MOVE_LASTRESORT,
            MOVE_DIG,
            MOVE_WILLOWISP
        },
        .ability = Ability_Hidden // Guts
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Chelsea[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BIBAREL,
        .moves = {
            MOVE_CURSE,
            MOVE_SUPERFANG,
            MOVE_AQUATAIL,
            MOVE_AQUAJET
        },
        .ability = Ability_1 // Simple
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_RAINDANCE,
            MOVE_HURRICANE,
            MOVE_WATERFALL,
            MOVE_ICEFANG
        },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GASTRODON,
        .moves = {
            MOVE_MUDDYWATER,
            MOVE_EARTHPOWER,
            MOVE_RECOVER,
            MOVE_BODYSLAM
        },
        .ability = Ability_2 // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LAPRAS,
        .moves = {
            MOVE_ICEBEAM,
            MOVE_RAINDANCE,
            MOVE_HYDROPUMP,
            MOVE_DRAGONPULSE
        },
        .ability = Ability_Hidden // Hydration
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Buddy[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CACTURNE,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_SPIKYSHIELD,
            MOVE_SUCKERPUNCH,
            MOVE_SPIKES
        },
        .ability = Ability_Hidden // Water Absorb
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROSERADE,
        .moves = {
            MOVE_TOXICSPIKES,
            MOVE_GIGADRAIN,
            MOVE_SWIFT,
            MOVE_VENOSHOCK
        },
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CRADILY,
        .moves = {
            MOVE_ANCIENTPOWER,
            MOVE_AMNESIA,
            MOVE_GIGADRAIN,
            MOVE_WRAP
        },
        .ability = Ability_Hidden // Storm Drain
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DHELMISE,
        .moves = {
            MOVE_ANCHORSHOT,
            MOVE_WHIRLPOOL,
            MOVE_SHADOWCLAW,
            MOVE_LIQUIDATION
        },
        .ability = Ability_1 // Steelworker
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Gawain[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FALINKS,
        .moves = {
            MOVE_NORETREAT,
            MOVE_CLOSECOMBAT,
            MOVE_FIRSTIMPRESSION,
            MOVE_HEADBUTT
        },
        .ability = Ability_Hidden // Defiant
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_PRIMEAPE,
        .moves = {
            MOVE_STOMPINGTANTRUM,
            MOVE_CROSSCHOP,
            MOVE_FOCUSENERGY,
            MOVE_SCREECH
        },
        .ability = Ability_2 // Anger Point
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIENSHAO,
        .moves = {
            MOVE_UTURN,
            MOVE_DRAINPUNCH,
            MOVE_BOUNCE,
            MOVE_DETECT
        },
        .ability = Ability_2 // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SIRFETCHD,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_BRICKBREAK,
            MOVE_BRUTALSWING,
            MOVE_STEELWING
        },
        .ability = Ability_Hidden // Scrappy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Skylar[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_EMOLGA,
        .moves = {
            MOVE_VOLTSWITCH,
            MOVE_LIGHTSCREEN,
            MOVE_DISCHARGE,
            MOVE_ACROBATICS
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOUCANNON,
        .moves = {
            MOVE_ROOST,
            MOVE_BULLETSEED,
            MOVE_ROCKBLAST,
            MOVE_DRILLPECK
        },
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MANDIBUZZ,
        .moves = {
            MOVE_DARKPULSE,
            MOVE_AIRSLASH,
            MOVE_IRONDEFENSE,
            MOVE_KNOCKOFF
        },
        .ability = Ability_2 // Overcoat
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TALONFLAME,
        .moves = {
            MOVE_AERIALACE,
            MOVE_FLAREBLITZ,
            MOVE_TAILWIND,
            MOVE_STEELWING
        },
        .ability = Ability_1 // Flame Body
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Bella[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CROBAT,
        .moves = {
            MOVE_CROSSPOISON,
            MOVE_TAILWIND,
            MOVE_LEECHLIFE,
            MOVE_ACROBATICS
        },
        .ability = Ability_Hidden // Inflitrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_TOXIC,
            MOVE_GIGADRAIN,
            MOVE_CLEARSMOG,
            MOVE_ASTONISH
        },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXICROAK,
        .moves = {
            MOVE_POISONJAB,
            MOVE_SUCKERPUNCH,
            MOVE_ROCKSLIDE,
            MOVE_PROTECT
        },
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXAPEX,
        .moves = {
            MOVE_BANEFULBUNKER,
            MOVE_TOXICSPIKES,
            MOVE_RECOVER,
            MOVE_SURF
        },
        .ability = Ability_1 // Merciless
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Flash[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RAICHU,
        .moves = {
            MOVE_NASTYPLOT,
            MOVE_DISCHARGE,
            MOVE_LIGHTSCREEN,
            MOVE_IRONTAIL
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GALVANTULA,
        .moves = {
            MOVE_THUNDER,
            MOVE_SUCKERPUNCH,
            MOVE_BUGBUZZ,
            MOVE_THUNDERWAVE
        },
        .ability = Ability_1 // Compound Eyes
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOXTRICITY_LOW_KEY,
        .moves = {
            MOVE_CHARGE,
            MOVE_DISCHARGE,
            MOVE_POISONJAB,
            MOVE_BOOMBURST
        },
        .ability = Ability_1 // Punk Rock
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VIKAVOLT,
        .moves = {
            MOVE_CRUNCH,
            MOVE_THUNDERBOLT,
            MOVE_BUGBUZZ,
            MOVE_FLY
        },
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Terra[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HIPPOWDON_F,
        .moves = {
            MOVE_EARTHQUAKE,
            MOVE_CRUNCH,
            MOVE_ICEFANG,
            MOVE_YAWN
        },
        .ability = Ability_1 // Sand Stream
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_HEAVYSLAM,
            MOVE_HIGHHORSEPOWER,
            MOVE_STOMP,
            MOVE_STEALTHROCK
        },
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STUNFISK_G,
        .moves = {
            MOVE_SNAPTRAP,
            MOVE_MUDDYWATER,
            MOVE_BOUNCE,
            MOVE_IRONDEFENSE
        },
        .ability = Ability_1 // Mimicry
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLYGON,
        .moves = {
            MOVE_DRAGONCLAW,
            MOVE_DRAGONDANCE,
            MOVE_EARTHQUAKE,
            MOVE_BUGBUZZ
        },
        .ability = Ability_1 // Levitate
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Seifa[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MALAMAR,
        .moves = {
            MOVE_SUPERPOWER,
            MOVE_PSYCHOCUT,
            MOVE_NIGHTSLASH,
            MOVE_LIQUIDATION
        },
        .ability = Ability_1 // Contrary
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WOBBUFFET,
        .moves = {
            MOVE_COUNTER,
            MOVE_MIRRORCOAT,
            MOVE_ENCORE,
            MOVE_SAFEGUARD
        },
        .ability = Ability_1 // Shadow Tag
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MR_RIME,
        .moves = {
            MOVE_DAZZLINGGLEAM,
            MOVE_MISTYTERRAIN,
            MOVE_FREEZEDRY,
            MOVE_PSYCHIC
        },
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_MORNINGSUN,
            MOVE_PSYCHIC,
            MOVE_PSYCHUP,
            MOVE_SHADOWBALL
        },
        .ability = Ability_Hidden // Magic Bounce
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Rocco[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LYCANROC_DUSK,
        .moves = {
            MOVE_ACCELEROCK,
            MOVE_STEALTHROCK,
            MOVE_CRUNCH,
            MOVE_SUCKERPUNCH
        },
        .ability = Ability_1 // Tough Claws
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BASTIODON,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_PROTECT,
            MOVE_BULLDOZE
        },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_COALOSSAL,
        .moves = {
            MOVE_HEATCRASH,
            MOVE_TARSHOT,
            MOVE_SMACKDOWN,
            MOVE_BODYPRESS
        },
        .ability = Ability_1 // Steam Engine
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_STONJOURNER,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_BODYSLAM,
            MOVE_SANDTOMB,
            MOVE_CURSE
        },
        .ability = Ability_1 // Power Spot
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Janice[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_CLOYSTER,
        .moves = {
            MOVE_ICICLESPEAR,
            MOVE_RAZORSHELL,
            MOVE_SHELLSMASH,
            MOVE_TOXICSPIKES
        },
        .ability = Ability_2 // Skill Link
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AVALUGG,
        .moves = {
            MOVE_HAIL,
            MOVE_BLIZZARD,
            MOVE_RECOVER,
            MOVE_CRUNCH
        },
        .ability = Ability_2 // Ice Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MAMOSWINE,
        .moves = {
            MOVE_EARTHQUAKE,
            MOVE_ICESHARD,
            MOVE_ICEFANG,
            MOVE_KNOCKOFF
        },
        .ability = Ability_2 // Snow Cloak
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_AURORUS,
        .moves = {
            MOVE_AURORAVEIL,
            MOVE_THUNDERWAVE,
            MOVE_FREEZEDRY,
            MOVE_ANCIENTPOWER
        },
        .ability = Ability_Hidden // Snow Warning
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Antoinette[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_VESPIQUEN,
        .moves = {
            MOVE_DEFENDORDER,
            MOVE_ATTACKORDER,
            MOVE_POWERGEM,
            MOVE_AIRSLASH
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_HERACROSS,
        .moves = {
            MOVE_BRICKBREAK,
            MOVE_MEGAHORN,
            MOVE_THROATCHOP,
            MOVE_SWORDSDANCE
        },
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SCOLIPEDE,
        .moves = {
            MOVE_TOXIC,
            MOVE_VENOSHOCK,
            MOVE_BUGBITE,
            MOVE_BATONPASS
        },
        .ability = Ability_Hidden // Speed Boost
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FROSMOTH,
        .moves = {
            MOVE_STRUGGLEBUG,
            MOVE_AURORABEAM,
            MOVE_QUIVERDANCE,
            MOVE_STUNSPORE
        },
        .ability = Ability_Hidden // Ice Scales
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Ryu[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TURTONATOR,
        .moves = {
            MOVE_SMOG,
            MOVE_FLAMETHROWER,
            MOVE_SHELLSMASH,
            MOVE_DRAGONPULSE
        },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_NOIVERN,
        .moves = {
            MOVE_DRAGONPULSE,
            MOVE_MOONLIGHT,
            MOVE_ROOST,
            MOVE_AIRSLASH
        },
        .ability = Ability_2 // Infiltrator
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TYRANTRUM,
        .moves = {
            MOVE_CRUNCH,
            MOVE_DRAGONCLAW,
            MOVE_FIREFANG,
            MOVE_THUNDERFANG
        },
        .ability = Ability_1 // Strong Jaw
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_GARCHOMP,
        .moves = {
            MOVE_DRAGONDANCE,
            MOVE_DRAGONCLAW,
            MOVE_EARTHQUAKE,
            MOVE_POISONJAB
        },
        .ability = Ability_Hidden // Rough Skin
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Caspar[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_JELLICENT,
        .moves = {
            MOVE_RECOVER,
            MOVE_WILLOWISP,
            MOVE_HEX,
            MOVE_SCALD
        },
        .ability = Ability_2 // Cursed Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_RUNERIGUS,
        .moves = {
            MOVE_SHADOWCLAW,
            MOVE_CURSE,
            MOVE_EARTHQUAKE,
            MOVE_ENERGYBALL
        },
        .ability = Ability_1 // Wandering Spirit
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_ROTOM_HEAT,
        .moves = {
            MOVE_REST,
            MOVE_THUNDERBOLT,
            MOVE_OVERHEAT,
            MOVE_SUBSTITUTE
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_DUSKNOIR,
        .moves = {
            MOVE_SHADOWBALL,
            MOVE_FUTURESIGHT,
            MOVE_THUNDERPUNCH,
            MOVE_ICEPUNCH
        },
        .ability = Ability_Hidden // Frisk
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Darcy[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEAVILE,
        .moves = {
            MOVE_ICESHARD,
            MOVE_BEATUP,
            MOVE_METALCLAW,
            MOVE_KNOCKOFF
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KROOKODILE,
        .moves = {
            MOVE_HONECLAWS,
            MOVE_CRUNCH,
            MOVE_EARTHQUAKE,
            MOVE_FIREFANG
        },
        .ability = Ability_1 // Intimidate
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MUK_A,
        .moves = {
            MOVE_GUNKSHOT,
            MOVE_CRUNCH,
            MOVE_TOXIC,
            MOVE_MINIMIZE
        },
        .ability = Ability_1 // Poison Touch
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_SLASH,
            MOVE_IRONDEFENSE,
            MOVE_NIGHTSLASH,
            MOVE_FURYCUTTER
        },
        .ability = Ability_1 // Defiant
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Mason[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_SKARMORY,
        .moves = {
            MOVE_SPIKES,
            MOVE_ROOST,
            MOVE_DRILLPECK,
            MOVE_STEELWING
        },
        .ability = Ability_2 // Sturdy
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_POWERWHIP,
            MOVE_CURSE,
            MOVE_GYROBALL,
            MOVE_INGRAIN
        },
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_KLINKLANG,
        .moves = {
            MOVE_SHIFTGEAR,
            MOVE_GEARGRIND,
            MOVE_CHARGEBEAM,
            MOVE_METALSOUND
        },
        .ability = Ability_Hidden // Clear Body
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_AURASPHERE,
            MOVE_METEORMASH,
            MOVE_BONERUSH,
            MOVE_SWORDSDANCE
        },
        .ability = Ability_1 // Steadfast
    }
};

const struct TrainerMonNoItemCustomMoves sParty_TsarvosaCity_GymTrainees_Faye[] = {
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_FLORGES_YELLOW,
        .moves = {
            MOVE_MOONBLAST,
            MOVE_SYNTHESIS,
            MOVE_PETALDANCE,
            MOVE_MISTYTERRAIN
        },
        .ability = Ability_1 // Flower Veil
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_WEEZING_G,
        .moves = {
            MOVE_STRANGESTEAM,
            MOVE_TOXIC,
            MOVE_SLUDGEBOMB,
            MOVE_HEATWAVE
        },
        .ability = Ability_2 // Neutralizing Gas
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_AIRSLASH,
            MOVE_MOONBLAST,
            MOVE_CALMMIND
        },
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 50, // Minimum, scales to player
        .species = SPECIES_MIMIKYU,
        .moves = {
            MOVE_WOODHAMMER,
            MOVE_SHADOWCLAW,
            MOVE_CHARM,
            MOVE_PLAYROUGH
        },
        .ability = Ability_1 // Disguise
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_PokefanMarci[] = {
    {
        .lvl = 54,
        .species = SPECIES_DELPHOX,
        .moves = {
            MOVE_TRICK,
            MOVE_PSYSHOCK,
            MOVE_MYSTICALFIRE,
            MOVE_LIGHTSCREEN
        },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Blaze
    },
    {
        .lvl = 54,
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_SUCKERPUNCH,
            MOVE_NIGHTSLASH,
            MOVE_EMBARGO,
            MOVE_METALBURST
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_1 // Defiant
    },
    {
        .lvl = 54,
        .species = SPECIES_MR_MIME_G,
        .moves = {
            MOVE_TRICK,
            MOVE_RECYCLE,
            MOVE_FLING,
            MOVE_FREEZEDRY
        },
        .heldItem = ITEM_LAGGING_TAIL,
        .ability = Ability_1 // Screen Cleaner
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_ChannelerJamila[] = {
    {
        .lvl = 56,
        .species = SPECIES_FROSLASS,
        .moves = {
            MOVE_FROSTBREATH,
            MOVE_DESTINYBOND,
            MOVE_CRUNCH,
            MOVE_SHADOWBALL
        },
        .heldItem = ITEM_FOCUS_SASH,
        .ability = Ability_Hidden // Cursed Body
    }
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_CoolTrainerNorbert[] = {
    {
        .lvl = 55,
        .species = SPECIES_JOLTEON,
        .moves = {
            MOVE_ELECTROBALL,
            MOVE_HIDDENPOWER,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_CHOICE_SCARF,
        .ability = Ability_Hidden // Quick Feet
    },
    {
        .lvl = 55,
        .species = SPECIES_CONKELDURR,
        .moves = {
            MOVE_HAMMERARM,
            MOVE_ROCKSLIDE,
            MOVE_BULKUP,
            MOVE_THUNDERPUNCH
        },
        .heldItem = ITEM_FLAME_ORB,
        .ability = Ability_1 // Guts
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_BurglarMarion[] = {
    {
        .lvl = 53,
        .species = SPECIES_SCOLIPEDE,
        .moves = {
            MOVE_SPIKES,
            MOVE_TOXICSPIKES,
            MOVE_BUGBITE,
            MOVE_POISONTAIL
        },
        .heldItem = ITEM_RED_CARD,
        .ability = Ability_1 // Poison Point
    },
    {
        .lvl = 53,
        .species = SPECIES_BARBARACLE,
        .moves = {
            MOVE_RAZORSHELL,
            MOVE_ROCKPOLISH,
            MOVE_SLASH,
            MOVE_ANCIENTPOWER
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_Hidden // Pickpocket
    },
    {
        .lvl = 54,
        .species = SPECIES_COFAGRIGUS,
        .moves = {
            MOVE_WILLOWISP,
            MOVE_SHADOWBALL,
            MOVE_DISABLE,
            MOVE_MEANLOOK
        },
        .heldItem = ITEM_EJECT_BUTTON,
        .ability = Ability_1 // Mummy
    },
    {
        .lvl = 54,
        .species = SPECIES_SCEPTILE,
        .moves = {
            MOVE_FLING,
            MOVE_THIEF,
            MOVE_LEAFBLADE,
            MOVE_XSCISSOR
        },
        .heldItem = ITEM_IRON_BALL,
        .ability = Ability_Hidden // Unburden
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LassAlanah[] = {
    {
        .lvl = 54,
        .species = SPECIES_LOPUNNY,
        .moves = {
            MOVE_FACADE,
            MOVE_PLAYROUGH,
            MOVE_UTURN,
            MOVE_RETALIATE
        },
        .heldItem = ITEM_TOXIC_ORB,
        .ability = Ability_1 // Cute Charm
    },
    {
        .lvl = 54,
        .species = SPECIES_COALOSSAL,
        .moves = {
            MOVE_TARSHOT,
            MOVE_INCINERATE,
            MOVE_STEALTHROCK,
            MOVE_ANCIENTPOWER
        },
        .heldItem = ITEM_QUICK_CLAW,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 54,
        .species = SPECIES_SHIINOTIC,
        .moves = {
            MOVE_STRENGTHSAP,
            MOVE_SPORE,
            MOVE_DAZZLINGGLEAM,
            MOVE_SWAGGER
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Effect Spore
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_GentlemanPaul[] = {
    {
        .lvl = 53,
        .species = SPECIES_CARBINK,
        .moves = {
            MOVE_LIGHTSCREEN,
            MOVE_REFLECT,
            MOVE_STEALTHROCK,
            MOVE_ANCIENTPOWER
        },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 54,
        .species = SPECIES_RAICHU,
        .moves = {
            MOVE_NUZZLE,
            MOVE_THUNDERBOLT,
            MOVE_IRONTAIL,
            MOVE_NASTYPLOT
        },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_1 // Static
    },
    {
        .lvl = 53,
        .species = SPECIES_DARMANITAN_G,
        .moves = {
            MOVE_ICEPUNCH,
            MOVE_EARTHQUAKE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_CHOICE_BAND,
        .ability = Ability_1 // Gorilla Tactics
    },
    {
        .lvl = 54,
        .species = SPECIES_TOXICROAK,
        .moves = {
            MOVE_POISONJAB,
            MOVE_SUCKERPUNCH,
            MOVE_DRAINPUNCH,
            MOVE_NONE
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_Hidden // Poison Touch
    },
};

const struct TrainerMonItemCustomMoves sParty_TsarvosaCityGym_LeaderIris[] = {
    {
        .lvl = 55,
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_CURSE,
            MOVE_IRONHEAD,
            MOVE_POWERWHIP,
            MOVE_SPIKES
        },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 55,
        .species = SPECIES_CHANSEY,
        .moves = {
            MOVE_MINIMIZE,
            MOVE_THUNDERWAVE,
            MOVE_ECHOEDVOICE,
            MOVE_SEISMICTOSS
        },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 56,
        .species = SPECIES_PALOSSAND,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_SHADOWBALL,
            MOVE_IRONDEFENSE,
            MOVE_SCORCHINGSANDS
        },
        .heldItem = ITEM_ABSORB_BULB,
        .ability = Ability_1 // Water Compaction
    },
    {
        .lvl = 58,
        .species = SPECIES_GIGALITH,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_FACADE,
            MOVE_IRONHEAD,
            MOVE_EARTHQUAKE
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sand Stream
    },
};
// #endregion

// #region Daimyn City Restaurant event
const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Iris[] = {
    {
        .lvl = 57,
        .species = SPECIES_FERROTHORN,
        .moves = {
            MOVE_CURSE,
            MOVE_GYROBALL,
            MOVE_POWERWHIP,
            MOVE_SPIKES
        },
        .heldItem = ITEM_ROCKY_HELMET,
        .ability = Ability_1 // Iron Barbs
    },
    {
        .lvl = 58,
        .species = SPECIES_CHANSEY,
        .moves = {
            MOVE_MINIMIZE,
            MOVE_THUNDERWAVE,
            MOVE_SOFTBOILED,
            MOVE_SEISMICTOSS
        },
        .heldItem = ITEM_EVIOLITE,
        .ability = Ability_2 // Serene Grace
    },
    {
        .lvl = 59,
        .species = SPECIES_GIGALITH,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_FACADE,
            MOVE_IRONHEAD,
            MOVE_EARTHQUAKE
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_2 // Sand Stream
    },
};

const struct TrainerMonItemCustomMoves sParty_DaimynCityRestaurant_Stella[] = {
    {
        .lvl = 56,
        .species = SPECIES_TOXAPEX,
        .moves = {
            MOVE_SCALD,
            MOVE_BANEFULBUNKER,
            MOVE_TOXICSPIKES,
            MOVE_VENOSHOCK
        },
        .heldItem = ITEM_BLACK_SLUDGE,
        .ability = Ability_1 // Merciless
    },
    {
        .lvl = 57,
        .species = SPECIES_COALOSSAL,
        .moves = {
            MOVE_TARSHOT,
            MOVE_HEATCRASH,
            MOVE_STONEEDGE,
            MOVE_WILLOWISP
        },
        .heldItem = ITEM_WEAKNESS_POLICY,
        .ability = Ability_2 // Flame Body
    },
    {
        .lvl = 58,
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_THUNDERWAVE,
            MOVE_FOLLOWME,
            MOVE_ROOST,
            MOVE_AIRSLASH
        },
        .heldItem = ITEM_LIFE_ORB,
        .ability = Ability_2 // Serene Grace
    },
};
// #endregion

// #region Daimyn Factory
const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BurglarSly[] = {
    { .lvl = 54, .species = SPECIES_CROAGUNK },
    { .lvl = 55, .species = SPECIES_WEAVILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerHasan[] = {
    { .lvl = 54, .species = SPECIES_KLINK },
    { .lvl = 54, .species = SPECIES_KLANG },
    { .lvl = 54, .species = SPECIES_KLINKLANG }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BurglarWill[] = {
    { .lvl = 53, .species = SPECIES_SCRAGGY },
    { .lvl = 54, .species = SPECIES_THIEVUL },
    { .lvl = 55, .species = SPECIES_SERPERIOR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerElroy[] = {
    { .lvl = 54, .species = SPECIES_MAWILE },
    { .lvl = 54, .species = SPECIES_RAICHU }
};
// #endregion

// #region Carnelidge Volcano
const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerBjorn[] = {
    { .lvl = 54, .species = SPECIES_STONJOURNER },
    { .lvl = 54, .species = SPECIES_GURDURR },
    { .lvl = 54, .species = SPECIES_MUDSDALE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ChannelerKelsey[] = {
    { .lvl = 53, .species = SPECIES_DUSKULL },
    { .lvl = 53, .species = SPECIES_MISDREAVUS },
    { .lvl = 53, .species = SPECIES_SABLEYE },
    { .lvl = 54, .species = SPECIES_MISMAGIUS },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_JugglerSeth[] = {
    { .lvl = 55, .species = SPECIES_MR_MIME_G },
    { .lvl = 55, .species = SPECIES_DELPHOX },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_DragonTamerFlynn[] = {
    { .lvl = 54, .species = SPECIES_SLIGGOO },
    { .lvl = 55, .species = SPECIES_GABITE },
    { .lvl = 55, .species = SPECIES_DRAGONITE },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_BirdKeepeFalco[] = {
    { .lvl = 55, .species = SPECIES_CORVISQUIRE },
    { .lvl = 55, .species = SPECIES_TALONFLAME },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_CrushGirlEunice[] = {
    { .lvl = 56, .species = SPECIES_SIRFETCHD },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_SuperNerdNathan[] = {
    { .lvl = 54, .species = SPECIES_PINCURCHIN },
    { .lvl = 54, .species = SPECIES_CRABOMINABLE },
    { .lvl = 55, .species = SPECIES_SKARMORY },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_HikerHugh[] = {
    { .lvl = 55, .species = SPECIES_MINIOR_SHIELD },
    { .lvl = 56, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_CarnelidgeVolcano_ScientistXander[] = {
    { .lvl = 55, .species = SPECIES_LILEEP },
    { .lvl = 55, .species = SPECIES_WEEZING_G },
    { .lvl = 55, .species = SPECIES_LUCARIO },
};
// #endregion

// #region Uteya Village
const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_PicknickerLisa[] = {
    { .lvl = 1, .species = SPECIES_CURSOLA },
    { .lvl = 1, .species = SPECIES_BRELOOM },
    { .lvl = 1, .species = SPECIES_MR_RIME }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_SwimmerTyson[] = {
    { .lvl = 1, .species = SPECIES_FLAREON },
    { .lvl = 1, .species = SPECIES_NINJASK },
    { .lvl = 1, .species = SPECIES_FLORGES }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyaVillage_ScientistWilford[] = {
    { .lvl = 1, .species = SPECIES_KROOKODILE },
    { .lvl = 1, .species = SPECIES_NOIVERN },
    { .lvl = 1, .species = SPECIES_DECIDUEYE }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Michael[] = {
    {
        .lvl = 60,
        .species = SPECIES_CARBINK,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_REFLECT,
            MOVE_LIGHTSCREEN,
            MOVE_STEALTHROCK
        },
        .heldItem = ITEM_LIGHT_CLAY,
        .ability = Ability_1 // Clear Body
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Leo[] = {
    {
        .lvl = 60,
        .species = SPECIES_SCRAFTY,
        .moves = {
            MOVE_ROCKSLIDE,
            MOVE_SNARL,
            MOVE_COACHING,
            MOVE_BRICKBREAK
        },
        .ability = Ability_Hidden // Intimidate
    }    
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Bonnie[] = {
    {
        .lvl = 59,
        .species = SPECIES_STONJOURNER,
        .moves = {
            MOVE_WIDEGUARD,
            MOVE_BLOCK,
            MOVE_ROCKSLIDE,
            MOVE_CURSE
        },
        .ability = Ability_1 // Power Spot
    },
    {
        .lvl = 59,
        .species = SPECIES_FROSMOTH,
        .moves = {
            MOVE_TAILWIND,
            MOVE_HAIL,
            MOVE_BLIZZARD,
            MOVE_AURORAVEIL
        },
        .ability = Ability_Hidden // Ice Scales
    },
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Clyde[] = {
    {
        .lvl = 60,
        .species = SPECIES_INFERNAPE,
        .moves = {
            MOVE_BRICKBREAK,
            MOVE_MACHPUNCH,
            MOVE_FLAREBLITZ,
            MOVE_ACROBATICS
        },
        .ability = Ability_Hidden // Iron Fist
    },
    {
        .lvl = 60,
        .species = SPECIES_MR_RIME,
        .moves = {
            MOVE_SAFEGUARD,
            MOVE_REFLECT,
            MOVE_PSYCHIC,
            MOVE_FREEZEDRY
        },
        .ability = Ability_Hidden // Ice Body
    },
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Jessie[] = {
    {
        .lvl = 60,
        .species = SPECIES_SLAKING,
        .moves = {
            MOVE_KNOCKOFF,
            MOVE_GIGAIMPACT,
            MOVE_HAMMERARM,
            MOVE_PLAYROUGH
        },
        .ability = Ability_1 // Truant
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_James[] = {
    {
        .lvl = 59,
        .species = SPECIES_WEEZING_G,
        .moves = {
            MOVE_AROMATICMIST,
            MOVE_AROMATHERAPY,
            MOVE_HEATWAVE,
            MOVE_STRANGESTEAM
        },
        .ability = Ability_2 // Neutralizing Gas
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Mike[] = {
    {
        .lvl = 60,
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_WATERFALL,
            MOVE_ICEFANG,
            MOVE_DRAGONDANCE,
            MOVE_EARTHQUAKE
        },
        .ability = Ability_1 // Intimidate
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Diane[] = {
    {
        .lvl = 61,
        .species = SPECIES_PINCURCHIN,
        .moves = {
            MOVE_RECOVER,
            MOVE_PROTECT,
            MOVE_ZINGZAP,
            MOVE_ELECTRICTERRAIN
        },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_1 // Lightning Rod
    }
};

const struct TrainerMonNoItemCustomMoves sParty_UteyaVillageGym_Hannibal[] = {
    {
        .lvl = 58,
        .species = SPECIES_FLYGON,
        .moves = {
            MOVE_HEATWAVE,
            MOVE_BUGBUZZ,
            MOVE_EARTHQUAKE,
            MOVE_DRAGONPULSE
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 59,
        .species = SPECIES_TOGEKISS,
        .moves = {
            MOVE_FOLLOWME,
            MOVE_AIRSLASH,
            MOVE_CHARM,
            MOVE_AURASPHERE
        },
        .ability = Ability_2 // Serene Grace
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_Clarice[] = {
    {
        .lvl = 58,
        .species = SPECIES_ORANGURU,
        .moves = {
            MOVE_INSTRUCT,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_LEFTOVERS,
        .ability = Ability_2 // Telepathy
    },
    {
        .lvl = 59,
        .species = SPECIES_BLISSEY,
        .moves = {
            MOVE_HELPINGHAND,
            MOVE_LIFEDEW,
            MOVE_MINIMIZE,
            MOVE_THUNDERBOLT
        },
        .ability = Ability_Hidden // Healer
    }
};

const struct TrainerMonItemCustomMoves sParty_UteyaVillageGym_LeadersDennisAndDee[] = {
    {
        .lvl = 61,
        .species = SPECIES_KLINKLANG,
        .moves = {
            MOVE_MAGNETICFLUX,
            MOVE_GEARUP,
            MOVE_ZAPCANNON,
            MOVE_GEARGRIND
        },
        .heldItem = ITEM_AIR_BALLOON,
        .ability = Ability_2 // Minus
    },
    {
        .lvl = 61,
        .species = SPECIES_TOXTRICITY,
        .moves = {
            MOVE_TOXIC,
            MOVE_VENOSHOCK,
            MOVE_OVERDRIVE,
            MOVE_BOOMBURST
        },
        .ability = Ability_2 // Plus
    },
    {
        .lvl = 60,
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_FOLLOWME,
            MOVE_QUICKGUARD,
            MOVE_HEALPULSE,
            MOVE_BRICKBREAK
        },
        .ability = Ability_2 // Inner Focus
    },
    {
        .lvl = 62,
        .species = SPECIES_ROTOM_FROST,
        .moves = {
            MOVE_HELPINGHAND,
            MOVE_BLIZZARD,
            MOVE_LIGHTSCREEN,
            MOVE_DISCHARGE
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 63,
        .species = SPECIES_GARCHOMP,
        .moves = {
            MOVE_EARTHQUAKE,
            MOVE_ROCKSLIDE,
            MOVE_POISONJAB,
            MOVE_DRAGONCLAW
        },
        .heldItem = ITEM_ASSAULT_VEST,
        .ability = Ability_Hidden // Rough Skin
    }
};

// #endregion

// #region Route 24
const struct TrainerMonNoItemDefaultMoves sParty_Route24_PsychicRaya[] = {
    { .lvl = 60, .species = SPECIES_HATTREM },
    { .lvl = 61, .species = SPECIES_HATTERENE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_DragonTamerDavid[] = {
    { .lvl = 61, .species = SPECIES_TURTONATOR },
    { .lvl = 61, .species = SPECIES_TYRANTRUM },
    { .lvl = 62, .species = SPECIES_CHARIZARD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_PsychicJeff[] = {
    { .lvl = 61, .species = SPECIES_WOBBUFFET },
    { .lvl = 61, .species = SPECIES_BEHEEYEM },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_FishermanHumphrey[] = {
    { .lvl = 63, .species = SPECIES_DHELMISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_TriathleteWillow[] = {
    { .lvl = 60, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 61, .species = SPECIES_LOPUNNY },
    { .lvl = 61, .species = SPECIES_WHIMSICOTT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route24_BlackbeltIrvine[] = {
    { .lvl = 58, .species = SPECIES_MIENFOO },
    { .lvl = 58, .species = SPECIES_MIENFOO },
    { .lvl = 59, .species = SPECIES_MIENFOO },
    { .lvl = 60, .species = SPECIES_MIENSHAO },
};
// #endregion

// #region Uteyan Ruins
const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacKristian[] = {
    { .lvl = 59, .species = SPECIES_STONJOURNER },
    { .lvl = 60, .species = SPECIES_WOBBUFFET }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_PsychicHaley[] = {
    { .lvl = 63, .species = SPECIES_BEHEEYEM }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_RuinManiacCyril[] = {
    { .lvl = 58, .species = SPECIES_YAMASK_G },
    { .lvl = 59, .species = SPECIES_COFAGRIGUS },
    { .lvl = 60, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_SuperNerdMorty[] = {
    { .lvl = 59, .species = SPECIES_GOGOAT },
    { .lvl = 59, .species = SPECIES_DRAGONAIR },
    { .lvl = 59, .species = SPECIES_GALLADE }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_ChannelerAgatha[] = {
    { .lvl = 60, .species = SPECIES_MIMIKYU },
    { .lvl = 60, .species = SPECIES_UMBREON }
};

const struct TrainerMonNoItemDefaultMoves sParty_UteyanRuins_LassDorothy[] = {
    { .lvl = 57, .species = SPECIES_FLAAFFY },
    { .lvl = 57, .species = SPECIES_KIRLIA },
    { .lvl = 58, .species = SPECIES_RIBOMBEE },
    { .lvl = 59, .species = SPECIES_WHIMSICOTT },
};
// #endregion

// #region Victory Road
const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerTimothy[] = {
    {
        .lvl = 61,
        .species = SPECIES_TORKOAL,
        .moves = {
            MOVE_BODYSLAM,
            MOVE_AMNESIA,
            MOVE_HEATWAVE,
            MOVE_PROTECT
        },
        .ability = Ability_1 // White smoke
    },
    {
        .lvl = 61,
        .species = SPECIES_TURTONATOR,
        .moves = {
            MOVE_SHELLTRAP,
            MOVE_SHELLSMASH,
            MOVE_EXPLOSION,
            MOVE_FLAIL
        },
        .ability = Ability_1 // Shell Armor
    },
    {
        .lvl = 62,
        .species = SPECIES_TORTERRA,
        .moves = {
            MOVE_WOODHAMMER,
            MOVE_LEECHSEED,
            MOVE_CRUNCH,
            MOVE_HEADLONGRUSH
        },
        .ability = Ability_1 // Overgrow
    },
    {
        .lvl = 62,
        .species = SPECIES_SHUCKLE,
        .moves = {
            MOVE_POWERSPLIT,
            MOVE_ROCKSLIDE,
            MOVE_INFESTATION,
            MOVE_STICKYWEB
        },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 63,
        .species = SPECIES_BLASTOISE,
        .moves = {
            MOVE_HYDROCANNON,
            MOVE_RAINDANCE,
            MOVE_IRONDEFENSE,
            MOVE_ICEBEAM
        },
        .ability = Ability_Hidden // Rain dish
    },
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerJonathan[] = {
    {
        .lvl = 63,
        .species = SPECIES_CRAWDAUNT,
        .moves = {
            MOVE_SWORDSDANCE,
            MOVE_CRABHAMMER,
            MOVE_CRUNCH,
            MOVE_DIG
        },
        .ability = Ability_Hidden // Adaptability
    },
    {
        .lvl = 63,
        .species = SPECIES_MAMOSWINE,
        .moves = {
            MOVE_ICICLECRASH,
            MOVE_EARTHQUAKE,
            MOVE_FLAIL,
            MOVE_ROCKTOMB
        },
        .ability = Ability_Hidden // Thick Fat
    },
    {
        .lvl = 64,
        .species = SPECIES_DELIBIRD,
        .moves = {
            MOVE_DRILLPECK,
            MOVE_ICYWIND,
            MOVE_SEEDBOMB,
            MOVE_SPIKES
        },
        .ability = Ability_1 // Vital Spirit
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerSatoshi[] = {
    {
        .lvl = 61,
        .species = SPECIES_MUK,
        .moves = {
            MOVE_TOXIC,
            MOVE_ACIDARMOR,
            MOVE_SLUDGEBOMB,
            MOVE_ZENHEADBUTT
        },
        .ability = Ability_Hidden // Poison Touch
    },
    {
        .lvl = 62,
        .species = SPECIES_HERACROSS,
        .moves = {
            MOVE_MEGAHORN,
            MOVE_BRICKBREAK,
            MOVE_THROATCHOP,
            MOVE_SWORDSDANCE
        },
        .ability = Ability_2 // Guts
    },
    {
        .lvl = 62,
        .species = SPECIES_KROOKODILE,
        .moves = {
            MOVE_CRUNCH,
            MOVE_SANDSTORM,
            MOVE_EARTHQUAKE,
            MOVE_THUNDERFANG
        },
        .ability = Ability_2 // Moxie
    },
    {
        .lvl = 63,
        .species = SPECIES_NOIVERN,
        .moves = {
            MOVE_BOOMBURST,
            MOVE_HURRICANE,
            MOVE_ROOST,
            MOVE_TAILWIND
        },
        .ability = Ability_2 // Infiltrator
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerCourtney[] = {
    {
        .lvl = 60,
        .species = SPECIES_PALOSSAND,
        .moves = {
            MOVE_SHOREUP,
            MOVE_SHADOWBALL,
            MOVE_EARTHPOWER,
            MOVE_GIGADRAIN
        },
        .ability = Ability_1 // Water Compaction
    },
    {
        .lvl = 60,
        .species = SPECIES_SLOWKING,
        .moves = {
            MOVE_POWERGEM,
            MOVE_FUTURESIGHT,
            MOVE_SURF,
            MOVE_PSYCHUP
        },
        .ability = Ability_2 // Own Tempo
    },
    {
        .lvl = 60,
        .species = SPECIES_VESPIQUEN,
        .moves = {
            MOVE_STRUGGLEBUG,
            MOVE_ROOST,
            MOVE_TOXIC,
            MOVE_DEFENDORDER
        },
        .ability = Ability_Hidden // Unnerve
    },
    {
        .lvl = 61,
        .species = SPECIES_GALLADE,
        .moves = {
            MOVE_LEAFBLADE,
            MOVE_SACREDSWORD,
            MOVE_NIGHTSLASH,
            MOVE_THUNDERPUNCH
        },
        .ability = Ability_1 // Steadfast
    },
    {
        .lvl = 61,
        .species = SPECIES_BISHARP,
        .moves = {
            MOVE_NIGHTSLASH,
            MOVE_IRONDEFENSE,
            MOVE_FURYCUTTER,
            MOVE_POISONJAB
        },
        .ability = Ability_Hidden // Pressure
    },
    {
        .lvl = 62,
        .species = SPECIES_NIDOKING,
        .moves = {
            MOVE_MEGAHORN,
            MOVE_SLUDGEWAVE,
            MOVE_EARTHPOWER,
            MOVE_THUNDERBOLT
        },
        .ability = Ability_2 // Rivalry
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerTheresa[] = {
    {
        .lvl = 63,
        .species = SPECIES_MUDSDALE,
        .moves = {
            MOVE_COUNTER,
            MOVE_EARTHQUAKE,
            MOVE_IRONHEAD,
            MOVE_ROCKSLIDE
        },
        .ability = Ability_2 // Stamina
    },
    {
        .lvl = 63,
        .species = SPECIES_AMPHAROS,
        .moves = {
            MOVE_COTTONGUARD,
            MOVE_DAZZLINGGLEAM,
            MOVE_THUNDER,
            MOVE_RAINDANCE
        },
        .ability = Ability_1 // Static
    },
    {
        .lvl = 64,
        .species = SPECIES_STOUTLAND,
        .moves = {
            MOVE_PLAYROUGH,
            MOVE_TAKEDOWN,
            MOVE_ICEFANG,
            MOVE_FIREFANG
        },
        .ability = Ability_Hidden // Scrappy
    },
    {
        .lvl = 64,
        .species = SPECIES_BLAZIKEN,
        .moves = {
            MOVE_BLAZEKICK,
            MOVE_BOUNCE,
            MOVE_SKYUPPERCUT,
            MOVE_FEATHERDANCE
        },
        .ability = Ability_Hidden // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerAbdul[] = {
    {
        .lvl = 63,
        .species = SPECIES_NIDOKING,
        .moves = {
            MOVE_SLUDGEBOMB,
            MOVE_HIGHHORSEPOWER,
            MOVE_SHADOWBALL,
            MOVE_THROATCHOP
        },
        .ability = Ability_Hidden // Sheer Force
    },
    {
        .lvl = 63,
        .species = SPECIES_SHARPEDO,
        .moves = {
            MOVE_LIQUIDATION,
            MOVE_AGILITY,
            MOVE_CRUNCH,
            MOVE_SWAGGER
        },
        .ability = Ability_1 // Rough Skin
    },
    {
        .lvl = 64,
        .species = SPECIES_CROBAT,
        .moves = {
            MOVE_LEECHLIFE,
            MOVE_CROSSPOISON,
            MOVE_MEANLOOK,
            MOVE_BRAVEBIRD
        },
        .ability = Ability_Hidden // Infiltrator
    },
    {
        .lvl = 64,
        .species = SPECIES_GYARADOS,
        .moves = {
            MOVE_DRAGONDANCE,
            MOVE_WATERFALL,
            MOVE_EARTHQUAKE,
            MOVE_ICEFANG
        },
        .ability = Ability_Hidden // Moxie
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerArthur[] = {
    {
        .lvl = 62,
        .species = SPECIES_BLISSEY,
        .moves = {
            MOVE_SOFTBOILED,
            MOVE_LIGHTSCREEN,
            MOVE_THUNDERWAVE,
            MOVE_SEISMICTOSS
        },
        .ability = Ability_1 // Natural Cure
    },
    {
        .lvl = 62,
        .species = SPECIES_SLAKING,
        .moves = {
            MOVE_SLACKOFF,
            MOVE_YAWN,
            MOVE_COVET,
            MOVE_FLING
        },
        .ability = Ability_1 // Truant
    },
    {
        .lvl = 62,
        .species = SPECIES_BASTIODON,
        .moves = {
            MOVE_ANCIENTPOWER,
            MOVE_IRONHEAD,
            MOVE_IRONDEFENSE,
            MOVE_SCORCHINGSANDS
        },
        .ability = Ability_1 // Sturdy
    },
    {
        .lvl = 62,
        .species = SPECIES_ESPEON,
        .moves = {
            MOVE_MORNINGSUN,
            MOVE_CALMMIND,
            MOVE_PSYCHIC,
            MOVE_SHADOWBALL
        },
        .ability = Ability_Hidden // Magic Bounce
    },
    {
        .lvl = 63,
        .species = SPECIES_DUSKNOIR,
        .moves = {
            MOVE_SHADOWPUNCH,
            MOVE_WILLOWISP,
            MOVE_HEX,
            MOVE_MEANLOOK
        },
        .ability = Ability_1 // Pressure
    },
    {
        .lvl = 63,
        .species = SPECIES_NINJASK,
        .moves = {
            MOVE_BATONPASS,
            MOVE_SWORDSDANCE,
            MOVE_XSCISSOR,
            MOVE_SLASH
        },
        .ability = Ability_1 // Speed Boost
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerKelly[] = {
    {
        .lvl = 61,
        .species = SPECIES_MR_RIME,
        .moves = {
            MOVE_MIRRORCOAT,
            MOVE_FREEZEDRY,
            MOVE_PSYCHIC,
            MOVE_TEETERDANCE
        },
        .ability = Ability_1 // Screen Cleaner
    },
    {
        .lvl = 61,
        .species = SPECIES_SALAZZLE,
        .moves = {
            MOVE_TOXIC,
            MOVE_VENOSHOCK,
            MOVE_FLAMETHROWER,
            MOVE_NASTYPLOT
        },
        .ability = Ability_1 // Corrosion
    },
    {
        .lvl = 61,
        .species = SPECIES_CONKELDURR,
        .moves = {
            MOVE_HAMMERARM,
            MOVE_STONEEDGE,
            MOVE_FOCUSPUNCH,
            MOVE_ROCKTOMB
        },
        .ability = Ability_1 // Guts
    },
    {
        .lvl = 62,
        .species = SPECIES_PRIMARINA,
        .moves = {
            MOVE_HYPERVOICE,
            MOVE_MOONBLAST,
            MOVE_SPARKLINGARIA,
            MOVE_ENERGYBALL
        },
        .ability = Ability_Hidden // Liquid Voice
    },
    {
        .lvl = 63,
        .species = SPECIES_COPPERAJAH,
        .moves = {
            MOVE_IRONHEAD,
            MOVE_BULLDOZE,
            MOVE_PLAYROUGH,
            MOVE_HIGHHORSEPOWER
        },
        .ability = Ability_1 // Sheer Force
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLydia[] = {
    {
        .lvl = 62,
        .species = SPECIES_CARBINK,
        .moves = {
            MOVE_LIGHTSCREEN,
            MOVE_POWERGEM,
            MOVE_STEALTHROCK,
            MOVE_FLASHCANNON
        },
        .ability = Ability_1 // Clear Body
    },
    {
        .lvl = 62,
        .species = SPECIES_DHELMISE,
        .moves = {
            MOVE_SHADOWCLAW,
            MOVE_ENERGYBALL,
            MOVE_ANCHORSHOT,
            MOVE_BULLDOZE
        },
        .ability = Ability_1 // Steelworker
    },
    {
        .lvl = 63,
        .species = SPECIES_ROTOM_MOW,
        .moves = {
            MOVE_LEAFSTORM,
            MOVE_DISCHARGE,
            MOVE_HEX,
            MOVE_WILLOWISP
        },
        .ability = Ability_1 // Levitate
    },
    {
        .lvl = 63,
        .species = SPECIES_FALINKS,
        .moves = {
            MOVE_NORETREAT,
            MOVE_FIRSTIMPRESSION,
            MOVE_MEGAHORN,
            MOVE_HEADBUTT
        },
        .ability = Ability_Hidden // Battle Armor
    },
    {
        .lvl = 64,
        .species = SPECIES_SHEDINJA,
        .moves = {
            MOVE_CONFUSERAY,
            MOVE_MUDSLAP,
            MOVE_GRUDGE,
            MOVE_LEECHLIFE
        },
        .ability = Ability_1 // Wonder Guard
    },
    {
        .lvl = 64,
        .species = SPECIES_MINIOR_SHIELD,
        .moves = {
            MOVE_EXPLOSION,
            MOVE_SHELLSMASH,
            MOVE_POWERGEM,
            MOVE_COSMICPOWER
        },
        .ability = Ability_1 // Shields Down
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerRobin[] = {
    {
        .lvl = 63,
        .species = SPECIES_DITTO,
        .moves = {
            MOVE_TRANSFORM,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 64,
        .species = SPECIES_DITTO,
        .moves = {
            MOVE_TRANSFORM,
            MOVE_NONE,
            MOVE_NONE,
            MOVE_NONE
        },
        .ability = Ability_Hidden // Imposter
    },
    {
        .lvl = 64,
        .species = SPECIES_LUCARIO,
        .moves = {
            MOVE_COPYCAT,
            MOVE_BONERUSH,
            MOVE_SWORDSDANCE,
            MOVE_FORCEPALM
        },
        .ability = Ability_Hidden // Justified
    },
    {
        .lvl = 65,
        .species = SPECIES_SUDOWOODO,
        .moves = {
            MOVE_MIMIC,
            MOVE_HAMMERARM,
            MOVE_STONEEDGE,
            MOVE_WOODHAMMER
        },
        .ability = Ability_1 // Sturdy
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerLuigi[] = {
    {
        .lvl = 65,
        .species = SPECIES_RILLABOOM,
        .moves = {
            MOVE_DRUMBEATING,
            MOVE_BOOMBURST,
            MOVE_DRAINPUNCH,
            MOVE_SCREECH
        },
        .ability = Ability_Hidden // Grassy Surge
    },
    {
        .lvl = 65,
        .species = SPECIES_CINDERACE,
        .moves = {
            MOVE_PYROBALL,
            MOVE_COUNTER,
            MOVE_BOUNCE,
            MOVE_QUICKATTACK
        },
        .ability = Ability_Hidden // Libero
    },
    {
        .lvl = 65,
        .species = SPECIES_INTELEON,
        .moves = {
            MOVE_SNIPESHOT,
            MOVE_UTURN,
            MOVE_SHADOWBALL,
            MOVE_ICEBEAM
        },
        .ability = Ability_Hidden // Sniper
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_CoolTrainerDahlia[] = {
    {
        .lvl = 65,
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_TOXIC,
            MOVE_SLUDGEBOMB,
            MOVE_HEX,
            MOVE_REST
        },
        .ability = Ability_Hidden // Regenerator
    },
    {
        .lvl = 65,
        .species = SPECIES_BRELOOM,
        .moves = {
            MOVE_FORCEPALM,
            MOVE_BULLETSEED,
            MOVE_MACHPUNCH,
            MOVE_ROCKTOMB
        },
        .ability = Ability_Hidden // Technician
    },
    {
        .lvl = 65,
        .species = SPECIES_SIRFETCHD,
        .moves = {
            MOVE_BRICKBREAK,
            MOVE_BRAVEBIRD,
            MOVE_FIRSTIMPRESSION,
            MOVE_KNOCKOFF
        },
        .ability = Ability_1 // Steadfast
    }
};

const struct TrainerMonNoItemCustomMoves sParty_VictoryRoad_NurseCelia[] = {
    {
        .lvl = 66,
        .species = SPECIES_CHANSEY,
        .moves = {
            MOVE_SWEETKISS,
            MOVE_COVET,
            MOVE_SOFTBOILED,
            MOVE_SING
        },
        .ability = Ability_Hidden // Healer
    },
    {
        .lvl = 66,
        .species = SPECIES_MEGANIUM,
        .moves = {
            MOVE_SUNNYDAY,
            MOVE_SOLARBEAM,
            MOVE_SYNTHESIS,
            MOVE_BODYSLAM
        },
        .ability = Ability_1 // Overgrow
    }
};
// #endregion

// #endregion

#define NO_NAME                                                                                      \
    {                                                                                                \
        _END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE \
    }

// #region Trainer Definitions 
const struct Trainer gTrainers[] = {
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
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_FIRST_BATTLE,
        .partySize = NELEMS(sParty_Rival1),
        .party = {.NoItemDefaultMoves = sParty_Rival1}
    },
    [TRAINER_RIVAL2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival2),
        .party = {.NoItemDefaultMoves = sParty_Rival2}
    },
    [TRAINER_RUBARR_DESERT_PARTNER_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_PartnerRival1),
        .party = {.NoItemCustomMoves = sParty_PartnerRival1}
    },
    [TRAINER_RIVAL3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival3),
        .party = {.ItemCustomMoves = sParty_Rival3}
    },
    [TRAINER_TORMA_CAVE_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1),
        .party = {.ItemCustomMoves = sParty_Casey1}
    },
    [TRAINER_TORMA_CAVE_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey1),
        .party = {.ItemCustomMoves = sParty_Casey1}
    },
    [TRAINER_ROUTE_10_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2),
        .party = {.ItemCustomMoves = sParty_Casey2}
    },
    [TRAINER_ROUTE_10_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Casey2),
        .party = {.ItemCustomMoves = sParty_Casey2}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Vaporeon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Vaporeon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Jolteon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Jolteon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Flareon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Flareon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Espeon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Espeon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Umbreon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Umbreon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Leafeon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Leafeon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Glaceon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Glaceon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Route11RivalPartner_Sylveon),
        .party = {.ItemCustomMoves = sParty_Route11RivalPartner_Sylveon}
    },
    [TRAINER_ROUTE_11_SOUTH_PARTNER_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_1,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAKE, // Do not see his front at this time
        .trainerName = { _A, _l, _i, _s, _t, _a, _i, _r, _END },  // Name replaced from RIVAL trainer classes
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Route11_Alistair),
        .party = {.ItemCustomMoves = sParty_Route11_Alistair}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Vaporeon),
        .party = {.ItemCustomMoves = sParty_Rival4_Vaporeon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Jolteon),
        .party = {.ItemCustomMoves = sParty_Rival4_Jolteon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Flareon),
        .party = {.ItemCustomMoves = sParty_Rival4_Flareon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Espeon),
        .party = {.ItemCustomMoves = sParty_Rival4_Espeon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Umbreon),
        .party = {.ItemCustomMoves = sParty_Rival4_Umbreon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Leafeon),
        .party = {.ItemCustomMoves = sParty_Rival4_Leafeon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Glaceon),
        .party = {.ItemCustomMoves = sParty_Rival4_Glaceon}
    },
    [TRAINER_ROUTE_11_SOUTH_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival4_Sylveon),
        .party = {.ItemCustomMoves = sParty_Rival4_Sylveon}
    },

    [TRAINER_BRUCCIE_VILLAGE_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Vaporeon),
        .party = {.ItemCustomMoves = sParty_Rival5_Vaporeon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Jolteon),
        .party = {.ItemCustomMoves = sParty_Rival5_Jolteon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Flareon),
        .party = {.ItemCustomMoves = sParty_Rival5_Flareon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Espeon),
        .party = {.ItemCustomMoves = sParty_Rival5_Espeon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Umbreon),
        .party = {.ItemCustomMoves = sParty_Rival5_Umbreon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Leafeon),
        .party = {.ItemCustomMoves = sParty_Rival5_Leafeon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Glaceon),
        .party = {.ItemCustomMoves = sParty_Rival5_Glaceon}
    },
    [TRAINER_BRUCCIE_VILLAGE_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival5_Sylveon),
        .party = {.ItemCustomMoves = sParty_Rival5_Sylveon}
    },
    [TRAINER_EMRALDIN_QUAY_OPTIONAL_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_EmraldinQuayEvent),
        .party = {.ItemCustomMoves = sParty_Rival_EmraldinQuayEvent}
    },
    [TRAINER_CARNELIDGE_VOLCANO_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_3,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Rival),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Rival}
    },
    [TRAINER_CARNELIDGE_VOLCANO_ALISTAIR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_PKMN_TRAINER_4,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_ALISTAIR,
        .trainerName = {_A, _l, _i, _s, _t, _a, _i, _r, _END},
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_Alistair),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_Alistair}
    },
    // #endregion
    // #region Route 1
    [TRAINER_ROUTE_1_YOUNGSTER_PETER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_P, _e, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route1_YoungsterPeter),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterPeter}
    },
    [TRAINER_ROUTE_1_LASS_HELENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_H, _e, _l, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route1_LassHelena),
        .party = {.NoItemDefaultMoves = sParty_Route1_LassHelena}
    },
    [TRAINER_ROUTE_1_YOUNGSTER_HARLAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_H, _a, _r, _l, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route1_YoungsterHarlan),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterHarlan}
    },
    [TRAINER_ROUTE_1_BURGLAR_BRYCE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_B, _r, _y, _c, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_Route1_BurglarBryce),
        .party = {.NoItemDefaultMoves = sParty_Route1_BurglarBryce}
    },
    [TRAINER_ROUTE_1_SWIMMER_REBECCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_R, _e, _b, _e, _c, _c, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route1_SwimmerRebecca),
        .party = {.NoItemDefaultMoves = sParty_Route1_SwimmerRebecca}
    },
    // #endregion
    // #region Route 2
    [TRAINER_ROUTE_2_YOUNGSTER_JOEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_J, _o, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route2_YoungsterJoey),
        .party = {.NoItemDefaultMoves = sParty_Route2_YoungsterJoey}
    },
    [TRAINER_ROUTE_2_LASS_KIMBERLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_K, _i, _m, _b, _e, _r, _l, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route2_LassKimberly),
        .party = {.NoItemDefaultMoves = sParty_Route2_LassKimberly}
    },
    [TRAINER_ROUTE_2_LASS_RIKKI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_R, _i, _k, _k, _i, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route2_LassRikki),
        .party = {.NoItemDefaultMoves = sParty_Route2_LassRikki}
    },
    [TRAINER_ROUTE_2_COOL_TRAINER_ANDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _n, _d, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route2_CoolTrainerAndy),
        .party = {.NoItemDefaultMoves = sParty_Route2_CoolTrainerAndy}
    },
    // #endregion
    // #region Varisi Forest
    [TRAINER_VARISI_FOREST_BUG_CATCHER_KENDELL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_K, _e, _n, _d, _e, _l, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_VarisiForest_BugCatcherKendell),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_BugCatcherKendell}
    },
    [TRAINER_VARISI_FOREST_BUG_CATCHER_BRADEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _r, _a, _d, _e, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_VarisiForest_BugCatcherBraden),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_BugCatcherBraden}
    },
    [TRAINER_VARISI_FOREST_LASS_BREANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_B, _r, _e, _a, _n, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_VarisiForest_LassBreanna),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_LassBreanna}
    },
    [TRAINER_VARISI_FOREST_LASS_MIMI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_M, _i, _m, _i, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_VarisiForest_LassMimi),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_LassMimi}
    },
    // #endregion
    // #region Rhodanzi City
    [TRAINER_RHODANZI_GYM_ALONSO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_A, _l, _o, _n, _s, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_RhodanziCity_Alonso),
        .party = {.NoItemCustomMoves = sParty_RhodanziCity_Alonso}
    },
    [TRAINER_RHODANZI_GYM_BRANDON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_B, _r, _a, _n, _d, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_RhodanziCity_Brandon),
        .party = {.NoItemCustomMoves = sParty_RhodanziCity_Brandon}
    },
    [TRAINER_RHODANZI_GYM_LEADER_TERRENCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_TERRENCE,
        .trainerName = {_T, _e, _r, _r, _e, _n, _c, _e, _END},
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_RhodanziCity_LeaderTerrence),
        .party = {.ItemCustomMoves = sParty_RhodanziCity_LeaderTerrence}
    },
    // #endregion
    // #region Route 3
    [TRAINER_ROUTE_3_PICKNICKER_TANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_T, _a, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route3_PicknickerTana),
        .party = {.NoItemDefaultMoves = sParty_Route3_PicknickerTana}
    },
    [TRAINER_ROUTE_3_BUG_CATCHER_IRWIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_I, _r, _w, _i, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route3_BugCatcherIrwin),
        .party = {.NoItemDefaultMoves = sParty_Route3_BugCatcherIrwin}
    },
    [TRAINER_ROUTE_3_YOUNGSTER_LOGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_L, _o, _g, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route3_YoungsterLogan),
        .party = {.NoItemDefaultMoves = sParty_Route3_YoungsterLogan}
    },
    [TRAINER_ROUTE_3_TWINS_NINA_AND_MEG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_N, _i, _n, _a, _SPACE, _AMPERSAND, _SPACE, _M, _e, _g, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route3_TwinsNinaAndMeg),
        .party = {.NoItemDefaultMoves = sParty_Route3_TwinsNinaAndMeg}
    },
    [TRAINER_ROUTE_3_NINJA_BOY_BOTAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_B, _o, _t, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route3_NinjaBoyBotan),
        .party = {.NoItemDefaultMoves = sParty_Route3_NinjaBoyBotan}
    },
    [TRAINER_ROUTE_3_ROCKER_JUDE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_J, _u, _d, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route3_RockerJude),
        .party = {.NoItemDefaultMoves = sParty_Route3_RockerJude}
    },
    [TRAINER_ROUTE_3_TEAM_PLUTO_RAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _a, _u, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_Route3_TeamPlutoRaul),
        .party = {.NoItemDefaultMoves = sParty_Route3_TeamPlutoRaul}
    },
    // #endregion
    // #region Rubarr Desert
    [TRAINER_RUBARR_DESERT_NURSE_JAINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_J, _a, _i, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_NurseJaina),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_NurseJaina}
    },
    [TRAINER_RUBARR_DESERT_BIRD_KEEPER_NOLAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_N, _o, _l, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_BirdKeeperNolan),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_BirdKeeperNolan}
    },
    [TRAINER_RUBARR_DESERT_RUIN_MANIAC_KENT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_K, _e, _n, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_RuinManiacKent),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_RuinManiacKent}
    },
    [TRAINER_RUBARR_DESERT_BLACK_BELT_KOBIYASHI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_K, _o, _b, _i, _y, _a, _s, _h, _i, _END},
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_BlackbeltKobiyashi),
        .party = {.ItemDefaultMoves = sParty_RubarrDesert_BlackbeltKobiyashi}
    },
    [TRAINER_RUBARR_DESERT_RUIN_MANIAC_ALBERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_A, _l, _b, _e, _r, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_RubarrDesert_RuinManiacAlbert),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_RuinManiacAlbert}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_MIKA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_M, _i, _k, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoMika),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoMika}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_MARCEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _a, _r, _c, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoMarcel),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoMarcel}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_TANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_T, _a, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoTana),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoTana}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoClancy),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoClancy}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoEna),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoEna}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoAdminIrene),
        .party = {.NoItemCustomMoves = sParty_RubarrDesert_TeamPlutoAdminIrene}
    },
    // #endregion
    // #region Route 4
    [TRAINER_ROUTE_4_CAMPER_PIETRO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_P, _i, _e, _t, _r, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route4_Camper_Pietro),
        .party = {.NoItemDefaultMoves = sParty_Route4_Camper_Pietro}
    },
    [TRAINER_ROUTE_4_PSYCHIC_ADRIANO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_A, _d, _r, _i, _a, _n, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route4_Psychic_Adriano),
        .party = {.NoItemDefaultMoves = sParty_Route4_Psychic_Adriano}
    },
    [TRAINER_ROUTE_4_BEAUTY_BEATRICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_B, _e, _a, _t, _r, _i, _c, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route4_Beauty_Beatrice),
        .party = {.NoItemDefaultMoves = sParty_Route4_Beauty_Beatrice}
    },
    [TRAINER_ROUTE_4_LADY_ALDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_A, _l, _d, _a, _END},
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route4_Lady_Alda),
        .party = {.ItemDefaultMoves = sParty_Route4_Lady_Alda}
    },
    [TRAINER_ROUTE_4_LASS_ISABELA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_I, _s, _a, _b, _e, _l, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route4_Lass_Isabela),
        .party = {.NoItemDefaultMoves = sParty_Route4_Lass_Isabela}
    },
    [TRAINER_ROUTE_4_BIRD_KEEPER_ROWLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_R, _o, _w, _l, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route4_Bird_Keeper_Rowley),
        .party = {.NoItemDefaultMoves = sParty_Route4_Bird_Keeper_Rowley}
    },
    [TRAINER_ROUTE_4_CRUSH_GIRL_ELISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _l, _i, _s, _e, _END},
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route4_Crush_Girl_Elise),
        .party = {.ItemDefaultMoves = sParty_Route4_Crush_Girl_Elise}
    },
    [TRAINER_ROUTE_4_GENTLEMAN_PORTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_P, _o, _r, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route4_Gentleman_Porter),
        .party = {.NoItemDefaultMoves = sParty_Route4_Gentleman_Porter}
    },
    [TRAINER_ROUTE_4_BIRD_KEEPER_LUCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_L, _u, _c, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route4_Bird_Keeper_Luca),
        .party = {.NoItemDefaultMoves = sParty_Route4_Bird_Keeper_Luca}
    },
    // #endregion
    // #region Torma Cave
    [TRAINER_TORMA_CAVE_FISHERMAN_ALFIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_A, _l, _f, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_TormaCave_Fisherman_Alfie),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Fisherman_Alfie}
    },
    [TRAINER_TORMA_CAVE_HIKER_NOB] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_N, _o, _b, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_TormaCave_Hiker_Nob),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Hiker_Nob}
    },
    [TRAINER_TORMA_CAVE_HIKER_SAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_S, _a, _u, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_TormaCave_Hiker_Saul),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Hiker_Saul}
    },
    [TRAINER_TORMA_CAVE_ENGINEER_WYATT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_W, _y, _a, _t, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_TormaCave_Engineer_Wyatt),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Engineer_Wyatt}
    },
    [TRAINER_TORMA_CAVE_ENGINEER_SHANE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_S, _h, _a, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_TormaCave_Engineer_Shane),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Engineer_Shane}
    },
    [TRAINER_TORMA_CAVE_POKEFAN_COREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_C, _o, _r, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_TormaCave_Pokefan_Corey),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Pokefan_Corey}
    },
    [TRAINER_TORMA_CAVE_LASS_HARMONY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_H, _a, _r, _m, _o, _n, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_TormaCave_Lass_Harmony),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Lass_Harmony}
    },
    // #endregion
    // #region Route 7
    [TRAINER_ROUTE_7_CAMPER_CARLISLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_C, _a, _r, _l, _i, _s, _l, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route7_CamperCarlisle),
        .party = {.NoItemDefaultMoves = sParty_Route7_CamperCarlisle}
    },    
    // #endregion
    // #region Route 13
    [TRAINER_ROUTE_13_GAMBLER_DALTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _a, _l, _t, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route13_GamblerDalton),
        .party = {.NoItemDefaultMoves = sParty_Route13_GamblerDalton}
    },
    [TRAINER_ROUTE_13_COLLECTOR_CHARLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_C, _h, _a, _r, _l, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route13_CollectorCharlie),
        .party = {.NoItemDefaultMoves = sParty_Route13_CollectorCharlie}
    },
    [TRAINER_ROUTE_13_HIKER_DWAYNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _w, _a, _y, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route13_HikerDwayne),
        .party = {.NoItemDefaultMoves = sParty_Route13_HikerDwayne}
    },
    [TRAINER_ROUTE_13_BLACK_BELT_HECTOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_H, _e, _c, _t, _o, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route13_BlackBeltHector),
        .party = {.NoItemDefaultMoves = sParty_Route13_BlackBeltHector}
    },
    [TRAINER_ROUTE_13_PICKNICKER_ETIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_E, _t, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route13_PicknickerEtie),
        .party = {.NoItemDefaultMoves = sParty_Route13_PicknickerEtie}
    },
    [TRAINER_ROUTE_13_BEAUTY_CANDICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_C, _a, _n, _d, _i, _c, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route13_BeautyCandice),
        .party = {.NoItemDefaultMoves = sParty_Route13_BeautyCandice}
    },
    [TRAINER_ROUTE_13_GAMBLER_OWAIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_O, _w, _a, _i, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route13_GamblerOwain),
        .party = {.NoItemDefaultMoves = sParty_Route13_GamblerOwain}
    },
    [TRAINER_ROUTE_13_COLLECTOR_BENJI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_B, _e, _n, _j, _i, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route13_CollectorBenji),
        .party = {.NoItemDefaultMoves = sParty_Route13_CollectorBenji}
    },
    // #endregion
    // #region Ferrox Village
    [TRAINER_FERROX_LIBRARY_LAURENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _a, _u, _r, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerLaurena),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerLaurena}
    },
    [TRAINER_FERROX_LIBRARY_LONA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_L, _o, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerLona),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerLona}
    },
    [TRAINER_FERROX_LIBRARY_CHET] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_C, _h, _e, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerChet),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerChet}
    },
    [TRAINER_FERROX_LIBRARY_VINCENT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_V, _i, _n, _c, _e, _n, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_FerroxGym_PokemonTrainerVincent),
        .party = {.NoItemCustomMoves = sParty_FerroxGym_PokemonTrainerVincent}
    },
    [TRAINER_FERROX_GYM_LEADER_STELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .items = { ITEM_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_FerroxGym_GymLeaderStella),
        .party = {.ItemCustomMoves = sParty_FerroxGym_GymLeaderStella}
    },
    // #endregion
    // #region Route 5
    [TRAINER_ROUTE_5_LADY_FAITH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_F, _a, _i, _t, _h, _END},
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route5_LadyFaith),
        .party = {.ItemDefaultMoves = sParty_Route5_LadyFaith}
    },
    [TRAINER_ROUTE_5_BUG_CATCHER_BEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _e, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route5_BugCatcher_Ben),
        .party = {.NoItemDefaultMoves = sParty_Route5_BugCatcher_Ben}
    },
    [TRAINER_ROUTE_5_PSYCHIC_ALYSSIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_A, _l, _y, _s, _s, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route5_Psychic_Alyssia),
        .party = {.NoItemDefaultMoves = sParty_Route5_Psychic_Alyssia}
    },
    [TRAINER_ROUTE_5_BREEDER_BRENDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_B, _r, _e, _n, _d, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_Route5_Breeder_Brenda),
        .party = {.NoItemDefaultMoves = sParty_Route5_Breeder_Brenda}
    },
    [TRAINER_ROUTE_5_BLACKBELT_RAHEEM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _a, _h, _e, _e, _m, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route5_Blackbelt_Raheem),
        .party = {.NoItemDefaultMoves = sParty_Route5_Blackbelt_Raheem}
    },
    [TRAINER_ROUTE_5_GAMBLER_DOMINIK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _o, _m, _i, _n, _i, _k, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route5_Gambler_Dominik),
        .party = {.NoItemDefaultMoves = sParty_Route5_Gambler_Dominik}
    },
    [TRAINER_ROUTE_5_LADY_JULIET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_J, _u, _l, _i, _e, _t, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route5_Lady_Juliet),
        .party = {.NoItemDefaultMoves = sParty_Route5_Lady_Juliet}
    },
    [TRAINER_ROUTE_5_GENTLEMAN_MARCUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_M, _a, _r, _c, _u, _s, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route5_Gentleman_Marcus),
        .party = {.NoItemDefaultMoves = sParty_Route5_Gentleman_Marcus}
    },
    // #endregion
    // #region Heleo Ranch
    [TRAINER_HELEO_RANCH_BURGLAR_COLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _o, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Burglar_Cole),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Burglar_Cole}
    },
    [TRAINER_HELEO_RANCH_CAMPER_TROY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_T, _r, _o, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Camper_Troy),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Camper_Troy}
    },
    [TRAINER_HELEO_RANCH_BREEDER_LAURA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_L, _a, _u, _r, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Breeder_Laura),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Breeder_Laura}
    },
    [TRAINER_HELEO_RANCH_PICKNICKER_CARLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_C, _a, _r, _l, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_HeleoRanch_Picknicker_Carly),
        .party = {.NoItemDefaultMoves = sParty_HeleoRanch_Picknicker_Carly}
    },
    // #endregion
    // #region Route 7 (Continued)
    [TRAINER_ROUTE_7_ROCKER_JONAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_J, _o, _n, _a, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route7_RockerJonas),
        .party = {.NoItemDefaultMoves = sParty_Route7_RockerJonas}
    },
    [TRAINER_ROUTE_7_LASS_EDEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_E, _d, _e, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route7_LassEden),
        .party = {.NoItemDefaultMoves = sParty_Route7_LassEden}
    },
    [TRAINER_ROUTE_7_HIKER_DANNY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _a, _n, _n, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route7_HikerDanny),
        .party = {.NoItemDefaultMoves = sParty_Route7_HikerDanny}
    },
    [TRAINER_ROUTE_7_CRUSH_GIRL_ERIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _r, _i, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route7_CrushGirlEden),
        .party = {.NoItemDefaultMoves = sParty_Route7_CrushGirlEden}
    },
    [TRAINER_ROUTE_7_PSYCHIC_ISHAAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_I, _s, _h, _a, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route7_PsychicIshaan),
        .party = {.NoItemDefaultMoves = sParty_Route7_PsychicIshaan}
    },
    // #endregion
    // #region Route 6
    [TRAINER_ROUTE_6_YOUNGSTER_NED] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_N, _e, _d, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route6_Youngster_Ned),
        .party = {.NoItemDefaultMoves = sParty_Route6_Youngster_Ned}
    },
    [TRAINER_ROUTE_6_NINJABOY_RAJAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_R, _a, _j, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route6_NinjaBoy_Rajan),
        .party = {.NoItemDefaultMoves = sParty_Route6_NinjaBoy_Rajan}
    },
    [TRAINER_ROUTE_6_HIKER_ROMERO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _m, _e, _r, _o, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route6_Hiker_Romero),
        .party = {.NoItemDefaultMoves = sParty_Route6_Hiker_Romero}
    },
    [TRAINER_ROUTE_6_SUPERNERD_ESTEVAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _s, _t, _e, _v, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route6_SuperNerd_Estevan),
        .party = {.NoItemDefaultMoves = sParty_Route6_SuperNerd_Estevan}
    },
    [TRAINER_ROUTE_6_ENGINEER_HARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _a, _r, _r, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route6_Engineer_Harry),
        .party = {.NoItemDefaultMoves = sParty_Route6_Engineer_Harry}
    },
    [TRAINER_ROUTE_6_GAMBLER_MICK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_M, _i, _c, _k, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route6_Gambler_Mick),
        .party = {.NoItemDefaultMoves = sParty_Route6_Gambler_Mick}
    },
    [TRAINER_ROUTE_6_FISHERMAN_TAYLOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_T, _a, _y, _l, _o, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route6_Fisherman_Taylor),
        .party = {.NoItemDefaultMoves = sParty_Route6_Fisherman_Taylor}
    },
    [TRAINER_ROUTE_6_NURSE_LEANNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_L, _e, _a, _n, _n, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_Route6_Nurse_Leanne),
        .party = {.NoItemDefaultMoves = sParty_Route6_Nurse_Leanne}
    },
    [TRAINER_ROUTE_6_SUPERNERD_DANTE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_D, _a, _n, _t, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route6_SuperNerd_Dante),
        .party = {.NoItemDefaultMoves = sParty_Route6_SuperNerd_Dante}
    },
    [TRAINER_ROUTE_6_BUGCATCHER_BILIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _i, _l, _l, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route6_BugCatcher_Billie),
        .party = {.NoItemDefaultMoves = sParty_Route6_BugCatcher_Billie}
    },
    [TRAINER_ROUTE_6_GENTLEMAN_LINCOLN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_L, _i, _n, _c, _o, _l, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route6_Gentleman_Lincoln),
        .party = {.NoItemDefaultMoves = sParty_Route6_Gentleman_Lincoln}
    },
    [TRAINER_ROUTE_6_BLACKBELT_RAFAEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _a, _f, _a, _e, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route6_BlackBelt_Raphael),
        .party = {.NoItemDefaultMoves = sParty_Route6_BlackBelt_Raphael}
    },
    [TRAINER_ROUTE_6_LASS_ANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_A, _n, _n, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route6_Lass_Anna),
        .party = {.NoItemDefaultMoves = sParty_Route6_Lass_Anna}
    },
    [TRAINER_ROUTE_6_SWIMMER_DANIKA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_D, _a, _n, _i, _k, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route6_Swimmer_Danika),
        .party = {.NoItemDefaultMoves = sParty_Route6_Swimmer_Danika}
    },
    [TRAINER_ROUTE_6_SRANDJR_SUEANDKAT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_S, _u, _e, _SPACE, _AMPERSAND, _SPACE, _K, _a, _t, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route6_SrAndJr_SueAndKat),
        .party = {.NoItemDefaultMoves = sParty_Route6_SrAndJr_SueAndKat}
    },
    [TRAINER_ROUTE_6_HIKER_DARRYL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _a, _r, _r, _y, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route6_HikerDarryl),
        .party = {.NoItemDefaultMoves = sParty_Route6_HikerDarryl}
    },
    // #endregion
    // #region Heleo City
    [TRAINER_HELEO_TRAINER_HOUSE_PSYCHIC_BIANCA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_B, _i, _a, _n, _c, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_PsychicBianca),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_PsychicBianca}
    },
    [TRAINER_HELEO_TRAINER_HOUSE_SUPERNERD_GALEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_G, _a, _l, _e, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_SupernerdGalen),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_SupernerdGalen}
    },
    [TRAINER_HELEO_TRAINER_HOUSE_COOL_TRAINER_JET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _e, _t, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCity_CoolTrainerJet),
        .party = {.NoItemDefaultMoves = sParty_HeleoCity_CoolTrainerJet}
    },
    [TRAINER_HELEO_CITY_GYM_TESSA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_T, _e, _s, _s, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerTessa),
        .party = {.NoItemCustomMoves = sParty_HeleoCityGym_SwimmerTessa}
    },
    [TRAINER_HELEO_CITY_GYM_BYRON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _y, _r, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerByron),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerByron}
    },
    [TRAINER_HELEO_CITY_GYM_DANETTE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_D, _a, _n, _e, _t, _t, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerDanette),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerDanette}
    },
    [TRAINER_HELEO_CITY_GYM_MAISEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _i, _s, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_HeleoCityGym_SwimmerMaisey),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_SwimmerMaisey}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine2),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine2}
    },
    [TRAINER_HELEO_CITY_GYM_LEADER_RAINE_3] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RAINE,
        .trainerName = {_R, _a, _i, _n, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_HeleoCityGym_LeaderRaine3),
        .party = {.ItemCustomMoves = sParty_HeleoCityGym_LeaderRaine3}
    },
    // #endregion
    // #region Route 8
    [TRAINER_ROUTE_8_CAMPER_DREW] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_D, _r, _e, _w, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route8_Camper_Drew),
        .party = {.NoItemDefaultMoves = sParty_Route8_Camper_Drew}
    },
    [TRAINER_ROUTE_8_NINJA_BOY_ZEKE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_Z, _e, _k, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route8_NinjaBoyZeke),
        .party = {.NoItemDefaultMoves = sParty_Route8_NinjaBoyZeke}
    },
    [TRAINER_ROUTE_8_SUPER_NERD_SAUL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_S, _a, _u, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route8_SuperNerdSaul),
        .party = {.NoItemDefaultMoves = sParty_Route8_SuperNerdSaul}
    },
    [TRAINER_ROUTE_8_ROCKER_PARKER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_P, _a, _r, _k, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route8_RockerParker),
        .party = {.NoItemDefaultMoves = sParty_Route8_RockerParker}
    },
    [TRAINER_ROUTE_8_PARASOL_LADY_ANNABELLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_A, _n, _n, _a, _b, _e, _l, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route8_ParasolLadyAnnabelle),
        .party = {.NoItemDefaultMoves = sParty_Route8_ParasolLadyAnnabelle}
    },
    [TRAINER_ROUTE_8_CHANNELER_MORGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _o, _r, _g, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route8_ChannelerMorgan),
        .party = {.NoItemDefaultMoves = sParty_Route8_ChannelerMorgan}
    },
    [TRAINER_ROUTE_8_BUG_CATCHER_ARNOLD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_A, _r, _n, _o, _l, _d, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route8_BugCatcherArnold),
        .party = {.NoItemDefaultMoves = sParty_Route8_BugCatcherArnold}
    },
    [TRAINER_ROUTE_8_LASS_LILIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_L, _i, _l, _i, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route8_LassLilian),
        .party = {.NoItemDefaultMoves = sParty_Route8_LassLilian}
    },
    [TRAINER_ROUTE_8_NINJA_BOY_NATTO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_N, _a, _t, _t, _o, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route8_NinjaBoyNatto),
        .party = {.NoItemDefaultMoves = sParty_Route8_NinjaBoyNatto}
    },
    [TRAINER_ROUTE_8_TUBER_MICAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_MALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = {_M, _i, _c, _a, _h, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route8_TuberMicah),
        .party = {.NoItemDefaultMoves = sParty_Route8_TuberMicah}
    },
    [TRAINER_ROUTE_8_TUBER_NANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_FEMALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = {_N, _a, _n, _c, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route8_TuberNancy),
        .party = {.NoItemDefaultMoves = sParty_Route8_TuberNancy}
    },
    [TRAINER_ROUTE_8_SWIMMER_MAYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _y, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerMaya),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerMaya}
    },
    [TRAINER_ROUTE_8_SWIMMER_HUEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_H, _u, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerHuey),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerHuey}
    },
    [TRAINER_ROUTE_8_SWIMMER_BOB] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _o, _b, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route8_SwimmerBob),
        .party = {.NoItemDefaultMoves = sParty_Route8_SwimmerBob}
    },
    [TRAINER_ROUTE_8_COOL_TRAINER_HARRIET] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_H, _a, _r, _r, _i, _e, _t, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route8_CoolTrainerHarriet),
        .party = {.NoItemDefaultMoves = sParty_Route8_CoolTrainerHarriet}
    },
    // #endregion
    // #region Forgotten Manse
    [TRAINER_FORGOTTEN_MANSE_CHANNELER_MONA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _o, _n, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_ChannelerMona),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_ChannelerMona}
    },
    [TRAINER_FORGOTTEN_MANSE_BURGLAR_CHAD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _h, _a, _d, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BurglarChad),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BurglarChad}
    },
    [TRAINER_FORGOTTEN_MANSE_NURSE_LUCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_L, _u, _c, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_NurseLucy),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_NurseLucy}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_BEAUTY_LULU] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _u, _l, _u, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_BeautyLulu),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_BeautyLulu}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_CHANNELER_ESTHER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_E, _s, _t, _h, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_ChannelerEsther),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_ChannelerEsther}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_SUPERNERD_AUSTIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_A, _u, _s, _t, _i, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_SuperNerdAustin),
        .party = {.NoItemCustomMoves = sParty_ForgottenManse_1F_SuperNerdAustin}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_BURGLAR_JACQUES] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_J, _a, _c, _q, _u, _e, _s, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_BurglarJacques),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_BurglarJacques}
    },
    [TRAINER_FORGOTTEN_MANSE_1F_PYSCHIC_CORBIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_C, _o, _r, _b, _i, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_1F_PsychicCorbin),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_1F_PsychicCorbin}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_BURGLAR_BARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_B, _a, _r, _r, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_BurglarBarry),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_BurglarBarry}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_YOUNGSTER_CHESTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_C, _h, _e, _s, _t, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_YoungsterChester),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_YoungsterChester}
    },
    [TRAINER_FORGOTTEN_MANSE_2F_CHANNELER_ELAINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_E, _l, _a, _i, _n, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_2F_ChannelerElaine),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_2F_ChannelerElaine}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_SUPERNERD_GLENN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_G, _l, _e, _n, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_SuperNerdGlenn),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_SuperNerdGlenn}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_BURGLAR_PAVLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_P, _e, _t, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_BurglarPavle),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_BurglarPavle}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_PSYCHIC_NOELLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_N, _o, _e, _l, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_PsychicNoelle),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_PsychicNoelle}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_CHANNELER_SANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_S, _a, _n, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_ChannelerSana),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_ChannelerSana}
    },
    // #endregion
    // #region Daimyn Factory
    [TRAINER_DAIMYN_FACTORY_BIRDKEEPER_MARIUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_M, _a, _r, _i, _u, _s, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BirdkeeperMarius),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BirdkeeperMarius}
    },
    [TRAINER_DAIMYN_FACTORY_ROCKER_BENSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_B, _e, _n, _s, _o, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_RockerBenson),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_RockerBenson}
    },
    [TRAINER_DAIMYN_FACTORY_LASS_NATALIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_N, _a, _t, _a, _l, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynFactory_LassNatalie),
        .party = {.ItemCustomMoves = sParty_DaimynFactory_LassNatalie}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_JAMISON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_J, _a, _m, _i, _s, _o, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerJamison),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerJamison}
    },
    [TRAINER_DAIMYN_FACTORY_HIKER_PERCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_P, _e, _r, _c, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_HikerPercy),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_HikerPercy}
    },
    [TRAINER_DAIMYN_FACTORY_BLACKBELT_RORY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _o, _r, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BlackbeltRory),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BlackbeltRory}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_WILSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_W, _i, _l, _s, _o, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerWilson),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerWilson}
    },
    [TRAINER_DAIMYN_FACTORY_YOUNGSTER_NATE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_N, _a, _t, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_YoungsterNate),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_YoungsterNate}
    },
    [TRAINER_DAIMYN_FACTORY_PICKNICKER_SHANNA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_S, _h, _a, _n, _n, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_PicknickerShanna),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_PicknickerShanna}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_KLIFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_K, _l, _i, _f, _f, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerKliff),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerKliff}
    },
    // #endregion
    // #region Daimyn City Gym
    [TRAINER_DAIMYN_CITY_GYM_YOUNGSTER_JACOB] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_J, _a, _c, _o, _b, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_YoungsterJacob),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_YoungsterJacob}
    },
    [TRAINER_DAIMYN_CITY_GYM_POKEFAN_KANESHA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_K, _a, _n, _e, _s, _h, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_PokefanKanesha),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_PokefanKanesha}
    },
    [TRAINER_DAIMYN_CITY_GYM_BEAUTY_EMILIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_E, _m, _i, _l, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_BeautyEmilie),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_BeautyEmilie}
    },
    [TRAINER_DAIMYN_CITY_GYM_BEAUTY_LEANNE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_L, _e, _a, _n, _n, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_BeautyLeanne),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_BeautyLeanne}
    },
    [TRAINER_DAIMYN_CITY_GYM_CHANNELER_ROSITA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_R, _o, _s, _i, _t, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_ChannelerRosita),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_ChannelerRosita}
    },
    [TRAINER_DAIMYN_CITY_GYM_GAMBLER_CHUCK] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_C, _h, _u, _c, _k, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_DaimynCityGym_GamblerChuck),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_GamblerChuck}
    },
    [TRAINER_DAIMYN_CITY_GYM_BURGLAR_DEXTER] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_D, _e, _x, _t, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_DaimynCityGym_BurglarDexter),
        .party = {.NoItemCustomMoves = sParty_DaimynCityGym_BurglarDexter}
    },
    [TRAINER_DAIMYN_CITY_GYM_LEADER_CHANCE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance}
    },
    [TRAINER_DAIMYN_CITY_GYM_LEADER_CHANCE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CHANCE,
        .trainerName = {_C, _h, _a, _n, _c, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityGym_LeaderChance2),
        .party = {.ItemCustomMoves = sParty_DaimynCityGym_LeaderChance2}
    },
    // #endregion
    // #region Route 9
    [TRAINER_ROUTE_9_COLLECTOR_MARSHALL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_M, _a, _r, _s, _h, _a, _l, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route9_Collector_Marshall),
        .party = {.NoItemDefaultMoves = sParty_Route9_Collector_Marshall}
    },
    [TRAINER_ROUTE_9_COOL_TRAINER_ANDREA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_A, _n, _d, _r, _e, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route9_CoolTrainer_Andrea),
        .party = {.NoItemDefaultMoves = sParty_Route9_CoolTrainer_Andrea}
    },
    [TRAINER_ROUTE_9_FISHERMAN_YUSUF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_Y, _u, _s, _u, _f, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route9_Fisherman_Yusuf),
        .party = {.NoItemDefaultMoves = sParty_Route9_Fisherman_Yusuf}
    },
    [TRAINER_ROUTE_9_GENTLEMAN_GAVIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _a, _v, _i, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route9_Gentleman_Gavin),
        .party = {.NoItemCustomMoves = sParty_Route9_Gentleman_Gavin}
    },
    [TRAINER_ROUTE_9_NINJA_BOY_AYRTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_A, _y, _r, _t, _o, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route9_NinjaBoy_Ayrton),
        .party = {.NoItemDefaultMoves = sParty_Route9_NinjaBoy_Ayrton}
    },
    [TRAINER_ROUTE_9_BREEDER_TALIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_BREEDER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_T, _a, _l, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_PokemonBreeder_Standard,
        .partySize = NELEMS(sParty_Route9_Breeder_Talia),
        .party = {.NoItemDefaultMoves = sParty_Route9_Breeder_Talia}
    },
    [TRAINER_ROUTE_9_PICKNICKER_ZOE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_Z, _o, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route9_Picknicker_Zoe),
        .party = {.NoItemDefaultMoves = sParty_Route9_Picknicker_Zoe}
    },
    [TRAINER_ROUTE_9_COOL_TRAINER_KINGSLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_K, _i, _n, _g, _s, _l, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route9_CoolTrainer_Kingsley),
        .party = {.NoItemDefaultMoves = sParty_Route9_CoolTrainer_Kingsley}
    },
    // #endregion
    // #region Route 10
    [TRAINER_ROUTE_10_PSYCHIC_DARIUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_D, _a, _r, _i, _u, _s, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route10_PsychicDarius),
        .party = {.NoItemDefaultMoves = sParty_Route10_PsychicDarius}
    },
    [TRAINER_ROUTE_10_BIRDKEEPER_MARIO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_M, _a, _r, _i, _o, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route10_BirdKeeperMario),
        .party = {.NoItemDefaultMoves = sParty_Route10_BirdKeeperMario}
    },
    [TRAINER_ROUTE_10_GAMBLER_DARREN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_D, _a, _r, _r, _e, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route10_GamblerDarren),
        .party = {.NoItemDefaultMoves = sParty_Route10_GamblerDarren}
    },
    [TRAINER_ROUTE_10_PARASOLLADY_GWEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_G, _w, _e, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route10_ParasolLadyGwen),
        .party = {.NoItemDefaultMoves = sParty_Route10_ParasolLadyGwen}
    },
    [TRAINER_ROUTE_10_CAMPER_JACKSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_J, _a, _c, _k, _s, _o, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_Route10_CamperJackson),
        .party = {.NoItemDefaultMoves = sParty_Route10_CamperJackson}
    },
    [TRAINER_ROUTE_10_ROCKER_BERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_B, _e, _r, _t, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route10_RockerBert),
        .party = {.NoItemDefaultMoves = sParty_Route10_RockerBert}
    },
    [TRAINER_ROUTE_10_SWIMMER_ALBERTO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_A, _l, _b, _e, _r, _t, _o, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerAlberto),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerAlberto}
    },
    [TRAINER_ROUTE_10_SWIMMER_ROSIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_R, _o, _s, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerRosie),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerRosie}
    },
    [TRAINER_ROUTE_10_SWIMMER_DOUG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_D, _o, _u, _g, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route10_SwimmerDoug),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerDoug}
    },
    [TRAINER_ROUTE_10_CAVE_HIKER_HARLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_H, _a, _r, _l, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route10Cave_HikerHarley),
        .party = {.NoItemDefaultMoves = sParty_Route10Cave_HikerHarley}
    },
    [TRAINER_ROUTE_10_CAVE_BLACKBELT_XAVIER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_X, _a, _v, _i, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route10Cave_BlackbeltXavier),
        .party = {.NoItemDefaultMoves = sParty_Route10Cave_BlackbeltXavier}
    },
    // #endregion
    // #region Route 11 South
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_ROSS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _o, _s, _s, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Ross),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Ross}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_GRETA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_G, _r, _e, _t, _a, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Greta),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Greta}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_NELLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_N, _e, _l, _l, _i, _e, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Nellie),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Nellie}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_HELGA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_H, _e, _l, _g, _a, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Helga),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Helga}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_KAREEM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_K, _a, _r, _e, _e, _m, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Kareem),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Kareem}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_CHUNG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _h, _u, _n, _g, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPluto_Chung),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPluto_Chung}
    },
    [TRAINER_ROUTE_11_SOUTH_LASS_TABITHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_T, _a, _b, _i, _t, _h, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route11South_Lass_Tabitha),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Lass_Tabitha}
    },
    [TRAINER_ROUTE_11_SOUTH_CRUSH_GIRL_ALISA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_A, _l, _i, _s, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route11South_CrushGirl_Alisa),
        .party = {.NoItemDefaultMoves = sParty_Route11South_CrushGirl_Alisa}
    },
    [TRAINER_ROUTE_11_SOUTH_ENGINEER_DALE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_D, _a, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route11South_Engineer_Dale),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Engineer_Dale}
    },
    [TRAINER_ROUTE_11_SOUTH_COLLECTOR_ORVILLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_O, _r, _v, _i, _l, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route11South_Collector_Orville),
        .party = {.NoItemDefaultMoves = sParty_Route11South_Collector_Orville}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoClancy),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPlutoClancy}
    },
    [TRAINER_ROUTE_11_SOUTH_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoEna),
        .party = {.NoItemDefaultMoves = sParty_Route11South_TeamPlutoEna}
    },
    [TRAINER_ROUTE_11_SOUTH_PLUTO_ADMIN_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_Route11South_TeamPlutoAdminRonald),
        .party = {.NoItemCustomMoves = sParty_Route11South_TeamPlutoAdminRonald}
    },
    // #endregion
    // #region Hesson Pass
    [TRAINER_HESSON_PASS_HIKER_LUKE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_L, _u, _k, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_HessonPass_HikerLuke),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_HikerLuke}
    },
    [TRAINER_HESSON_PASS_SCIENTIST_HARVEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_H, _a, _r, _v, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_HessonPass_ScientistHarvey),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_ScientistHarvey}
    },
    [TRAINER_HESSON_PASS_PSYCHIC_KIMIKO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_K, _i, _m, _i, _k, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_HessonPass_PsychicKimiko),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_PsychicKimiko}
    },
    [TRAINER_HESSON_PASS_COOL_TRAINER_COLT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _t, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_HessonPass_CoolTrainerColt),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_CoolTrainerColt}
    },
    [TRAINER_HESSON_PASS_BLACK_BELT_HAYTHAM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_H, _a, _y, _t, _h, _a, _m, _END},
        .items = { ITEM_DIRE_HIT },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_HessonPass_BlackbeltHaytham),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_BlackbeltHaytham}
    },
    [TRAINER_HESSON_PASS_COLLECTOR_ZEUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_Z, _e, _u, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_HessonPass_CollectorZeus),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_CollectorZeus}
    },
    [TRAINER_HESSON_PASS_NURSE_MINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_M, _i, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_HessonPass_NurseMina),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_NurseMina}
    },
    [TRAINER_HESSON_PASS_GENTLEMAN_GORDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _o, _r, _d, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_HessonPass_GentlemanGordy),
        .party = {.NoItemDefaultMoves = sParty_HessonPass_GentlemanGordy}
    },
    // #endregion
    // #region Route 11 North
    [TRAINER_ROUTE_11_NORTH_PAINTER_ISOBEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_I, _s, _o, _b, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_Route11North_PainterIsobel),
        .party = {.NoItemDefaultMoves = sParty_Route11North_PainterIsobel}
    },
    [TRAINER_ROUTE_11_NORTH_FISHERMAN_CLINT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_C, _l, _i, _n, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route11North_FishermanClint),
        .party = {.NoItemDefaultMoves = sParty_Route11North_FishermanClint}
    },
    [TRAINER_ROUTE_11_NORTH_PARASOL_LADY_TINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_T, _i, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route11North_ParaoslLadyTina),
        .party = {.NoItemDefaultMoves = sParty_Route11North_ParaoslLadyTina}
    },
    [TRAINER_ROUTE_11_NORTH_CHANNELER_KATYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_K, _a, _t, _y, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route11North_ChanellerKatya),
        .party = {.NoItemDefaultMoves = sParty_Route11North_ChanellerKatya}
    },
    [TRAINER_ROUTE_11_NORTH_ROCKER_NATHANIEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_N, _a, _t, _h, _a, _n, _i, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_Route11North_RockerNathaniel),
        .party = {.NoItemDefaultMoves = sParty_Route11North_RockerNathaniel}
    },
    [TRAINER_ROUTE_11_NORTH_NINJA_BOY_YAO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_Y, _a, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route11North_NinjaBoyYao),
        .party = {.NoItemDefaultMoves = sParty_Route11North_NinjaBoyYao}
    },
    [TRAINER_ROUTE_11_NORTH_FISHERMAN_JONAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_J, _o, _n, _a, _h, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route11North_FishermanJonah),
        .party = {.NoItemDefaultMoves = sParty_Route11North_FishermanJonah}
    },
    // #endregion
    // #region Laplaz Town
    [TRAINER_LAPLAZ_TRAINER_HOUSE_BIRD_KEEPER_TOBY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _o, _b, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_BirdKeeperToby),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_BirdKeeperToby}
    },
    [TRAINER_LAPLAZ_TRAINER_HOUSE_COLLECTOR_DIRK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_D, _i, _r, _k, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_CollectorDirk),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_CollectorDirk}
    },
    [TRAINER_LAPLAZ_TRAINER_HOUSE_COOL_TRAINER_VANESSA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_V, _a, _n, _e, _s, _s, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_LaplazTown_CoolTrainerVanessa),
        .party = {.NoItemDefaultMoves = sParty_LaplazTown_CoolTrainerVanessa}
    },
    [TRAINER_LAPLAZ_GYM_JEREMIAH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_J, _e, _r, _e, _m, _i, _a, _h, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_PsychicJeremiah),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_PsychicJeremiah}
    },
    [TRAINER_LAPLAZ_GYM_EXIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_E, _x, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_PicnickerExie),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_PicnickerExie}
    },
    [TRAINER_LAPLAZ_GYM_VIRGINIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_V, _i, _r, _g, _i, _n, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_ChannelerVirginia),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_ChannelerVirginia}
    },
    [TRAINER_LAPLAZ_GYM_NISHA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_N, _i, _s, _h, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_LadyNisha),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_LadyNisha}
    },
    [TRAINER_LAPLAZ_GYM_KENT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_K, _e, _n, _t, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_ScientistKent),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_ScientistKent}
    },
    [TRAINER_LAPLAZ_GYM_TOMAS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_T, _o, _m, _a, _s, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_LaplazTownGym_RockerTomas),
        .party = {.NoItemCustomMoves = sParty_LaplazTownGym_RockerTomas}
    },
    [TRAINER_LAPLAZ_GYM_LEADER_CASEY_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_F,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey}
    },
    [TRAINER_LAPLAZ_GYM_LEADER_CASEY_M] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CASEY_M,
        .trainerName = {_C, _a, _s, _e, _y, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_PREFER_BATON_PASS | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_LaplazTownGym_LeaderCasey),
        .party = {.ItemCustomMoves = sParty_LaplazTownGym_LeaderCasey}
    },
    // #endregion
    // #region Peradon Forest
    [TRAINER_PERADON_FOREST_POKEFAN_CLARK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_C, _l, _a, _r, _k, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_PeradonForest_PokefanClark),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_PokefanClark}
    },
    [TRAINER_PERADON_FOREST_COLLECTOR_FERNANDO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_F, _e, _r, _n, _a, _n, _d, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_PeradonForest_CollectorFernando),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_CollectorFernando}
    },
    [TRAINER_PERADON_FOREST_BUG_CATCHER_LYLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_L, _y, _l, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_PeradonForest_BugCatcherLyle),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BugCatcherLyle}
    },
    [TRAINER_PERADON_FOREST_BEAUTY_ERICA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_E, _r, _i, _c, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_PeradonForest_BeautyErica),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BeautyErica}
    },
    [TRAINER_PERADON_FOREST_PAINTER_SHEENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PAINTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = {_S, _h, _e, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Painter_Standard,
        .partySize = NELEMS(sParty_PeradonForest_PainterSheena),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_PainterSheena}
    },
    [TRAINER_PERADON_FOREST_CAMPER_RUPERT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CAMPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = {_R, _u, _p, _e, _r, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Camper_Standard,
        .partySize = NELEMS(sParty_PeradonForest_CamperRupert),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_CamperRupert}
    },
    [TRAINER_PERADON_FOREST_SCIENTIST_SEAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _e, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_PeradonForest_ScientistSean),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_ScientistSean}
    },
    [TRAINER_PERADON_FOREST_ROCKER_RAPHAEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_R, _a, _p, _h, _a, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_PeradonForest_RockerRaphael),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_RockerRaphael}
    },
    [TRAINER_PERADON_FOREST_CHANNELER_RENEE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_R, _e, _n, _e, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_PeradonForest_ChannelerRenee),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_ChannelerRenee}
    },
    [TRAINER_PERADON_FOREST_BLACKBELT_BRAD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_B, _r, _a, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_PeradonForest_BlackbeltBrad),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_BlackbeltBrad}
    },
    [TRAINER_PERADON_FOREST_RUIN_MANIAC_ALEX] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_A, _l, _e, _x, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_PeradonForest_RuinManiacAlex),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_RuinManiacAlex}
    },
    // #endregion
    // #region Route 12 & Scalding Spa
    [TRAINER_ROUTE_12_EAST_TRIATHLETE_JOANNE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_J, _o, _a, _n, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route12East_TriathleteJoanne),
        .party = {.NoItemDefaultMoves = sParty_Route12East_TriathleteJoanne}
    },
    [TRAINER_ROUTE_12_EAST_PSYCHIC_TONY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_T, _o, _n, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route12East_PsychicTony),
        .party = {.NoItemDefaultMoves = sParty_Route12East_PsychicTony}
    },
    [TRAINER_ROUTE_12_EAST_HIKER_DWIGHT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_D, _w, _i, _g, _h, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route12East_HikerDwight),
        .party = {.NoItemDefaultMoves = sParty_Route12East_HikerDwight}
    },
    [TRAINER_ROUTE_12_EAST_TRIATHLETE_TRIXIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_T, _r, _i, _x, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route12East_TriathleteTrixie),
        .party = {.NoItemDefaultMoves = sParty_Route12East_TriathleteTrixie}
    },
    [TRAINER_ROUTE_12_EAST_GENTLEMAN_GEOFFREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_G, _e, _o, _f, _f, _r, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route12East_GentlemanGeoffrey),
        .party = {.NoItemDefaultMoves = sParty_Route12East_GentlemanGeoffrey}
    },
    [TRAINER_SCALDING_SPA_HIKER_EUGENE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_E, _u, _g, _e, _n, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_HikerEugene),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_HikerEugene}
    },
    [TRAINER_SCALDING_SPA_SUPERNERD_STEPHEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_S, _t, _e, _p, _h, _e, _n, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_SupernerdStephen),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_SupernerdStephen}
    },
    [TRAINER_SCALDING_SPA_JUGGLER_JOHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_J, _o, _h, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_ScaldingSpa_JugglerJohan),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_JugglerJohan}
    },
    [TRAINER_SCALDING_SPA_BLACKBELT_KIERAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_K, _i, _e, _r, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_ScaldingSpa_BlackbeltKieran),
        .party = {.NoItemDefaultMoves = sParty_ScaldingSpa_BlackbeltKieran}
    },
    [TRAINER_SCALDING_SPA_TEAM_PLUTO_YOLENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_Y, _o, _l, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_ScaldingSpa_TeamPlutoYolena),
        .party = {.ItemCustomMoves = sParty_ScaldingSpa_TeamPlutoYolena}
    },
    [TRAINER_ROUTE_12_WEST_BUG_CATCHER_BRENDAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _r, _e, _n, _d, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_Route12West_BugCatcherBrenan),
        .party = {.NoItemDefaultMoves = sParty_Route12West_BugCatcherBrenan}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_CHANTAL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_C, _h, _a, _n, _t, _a, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierChantal),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierChantal}
    },
    [TRAINER_ROUTE_12_WEST_HIKER_KUMAR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_K, _u, _m, _a, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route12West_HikerKumar),
        .party = {.NoItemDefaultMoves = sParty_Route12West_HikerKumar}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_AUBREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_A, _u, _b, _r, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierAubrey),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierAubrey}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_LENORA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_L, _e, _n, _o, _r, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierLenora),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierLenora}
    },
    [TRAINER_ROUTE_12_WEST_SKIER_MEGAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_M, _e, _g, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_Route12West_SkierMegan),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SkierMegan}
    },
    [TRAINER_ROUTE_12_WEST_SWIMMER_M_GREG] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _r, _e, _g, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route12West_SwimmerMGreg),
        .party = {.NoItemDefaultMoves = sParty_Route12West_SwimmerMGreg}
    },
    // #endregion
    // #region Bruccie Village & Calicin Bay
    [TRAINER_BRUCCIE_VILLAGE_GYM_MEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_M, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_LassMel),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_LassMel}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_OWEN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_O, _w, _e, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_BirdKeeperOwen),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_BirdKeeperOwen}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_TOMMY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_T, _o, _m, _m, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_EngineerTommy),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_EngineerTommy}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_JOEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_J, _o, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_HikerJoel),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_HikerJoel}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_ELLIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _l, _l, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_BruccieVillageGym_CrushGirlEllie),
        .party = {.NoItemCustomMoves = sParty_BruccieVillageGym_CrushGirlEllie}
    },
    [TRAINER_BRUCCIE_VILLAGE_GYM_LEADER_ABBY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_ABBY,
        .trainerName = {_A, _b, _b, _y, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_BruccieVillageGym_LeaderAbby),
        .party = {.ItemCustomMoves = sParty_BruccieVillageGym_LeaderAbby}
    },
    [TRAINER_CALICIN_BAY_SKIER_RITA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SKIER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_R, _i, _t, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Skier_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SkierRita),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SkierRita}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_F_FRAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_F, _r, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerFFran),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerFFran}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_M_ANGELO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_A, _n, _g, _e, _l, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerMAngelo),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerMAngelo}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_M_SEBASTIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_S, _e, _b, _a, _s, _t, _i, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerMSebastian),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerMSebastian}
    },
    [TRAINER_CALICIN_BAY_SWIMMER_F_CORRINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _o, _r, _r, _i, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_CalicinBay_SwimmerFCorrine),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_SwimmerFCorrine}
    },
    [TRAINER_CALICIN_BAY_FISHERMAN_OLIVER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_O, _l, _i, _v, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_CalicinBay_FishermanOliver),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_FishermanOliver}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_HUGO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_H, _u, _g, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoHugo),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoHugo}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_ANISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_A, _n, _i, _s, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoAnise),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoAnise}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_YOLENA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_Y, _o, _l, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoYolena),
        .party = {.ItemCustomMoves = sParty_CalicinBay_TeamPlutoYolena}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_CLANCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _n, _c, _y, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoClancy),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoClancy}
    },
    [TRAINER_CALICIN_BAY_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_CalicinBay_TeamPlutoEna),
        .party = {.NoItemDefaultMoves = sParty_CalicinBay_TeamPlutoEna}
    },
    // #endregion
    // #region Pluto HQ
    [TRAINER_PLUTO_HQ_B1F_TEAM_PLUTO_HEATHCLIFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_H, _e, _a, _t, _h, _c, _l, _i, _f, _f, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoHeathcliff),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B1F_TeamPlutoHeathcliff}
    },
    [TRAINER_PLUTO_HQ_B1F_SCIENTIST_SEAMUS] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _e, _a, _m, _u, _s, _END},
        .items = { ITEM_X_SP_ATK },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_ScientistSeamus),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B1F_ScientistSeamus}
    },
    [TRAINER_PLUTO_HQ_B1F_TEAM_PLUTO_COLTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _o, _l, _t, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoColton),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B1F_TeamPlutoColton}
    },
    [TRAINER_PLUTO_HQ_B2F_SCIENTIST_WAYNE] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_W, _a, _y, _n, _e, _END},
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_ScientistWayne),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B2F_ScientistWayne}
    },
    [TRAINER_PLUTO_HQ_B2F_TEAM_PLUTO_DENISE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_D, _e, _n, _i, _s, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_TeamPlutoDenise),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B2F_TeamPlutoDenise}
    },
    [TRAINER_PLUTO_HQ_B2F_TEAM_PLUTO_THEODORE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_T, _h, _e, _o, _d, _o, _r, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B2F_TeamPlutoTheodore),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B2F_TeamPlutoTheodore}
    },
    [TRAINER_PLUTO_HQ_B3F_TEAM_PLUTO_YEON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_Y, _e, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B3F_TeamPlutoYeon),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B3F_TeamPlutoYeon}
    },
    [TRAINER_PLUTO_HQ_B4F_TEAM_PLUTO_MATTY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _a, _t, _t, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoMatty),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B4F_TeamPlutoMatty}
    },
    [TRAINER_PLUTO_HQ_B4F_SCIENTIST_GARY] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_G, _a, _r, _y, _END},
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_ScientistGary),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B4F_ScientistGary}
    },
    [TRAINER_PLUTO_HQ_B4F_TEAM_PLUTO_MAY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_M, _a, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoMay),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B4F_TeamPlutoMay}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_CLAY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_C, _l, _a, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoClay),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoClay}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_VICTOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_V, _i, _c, _t, _o, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoVictor),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoVictor}
    },
    [TRAINER_PLUTO_HQ_B5F_TEAM_PLUTO_PAULA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_P, _a, _u, _l, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B5F_TeamPlutoPaula),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B5F_TeamPlutoPaula}
    },
    [TRAINER_PLUTO_HQ_B6F_TEAM_PLUTO_GIANA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_G, _i, _a, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_TeamPlutoGiana),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B6F_TeamPlutoGiana}
    },
    [TRAINER_PLUTO_HQ_B6F_SCIENTIST_ORSON] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_O, _r, _s, _o, _n, _END},
        .items = { ITEM_X_SP_ATK },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_ScientistOrson),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B6F_ScientistOrson}
    },
    [TRAINER_PLUTO_HQ_B6F_TEAM_PLUTO_QUINN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_Q, _u, _i, _n, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B6F_TeamPlutoQuinn),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B6F_TeamPlutoQuinn}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_LAYLA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_L, _a, _y, _l, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoLayla),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoLayla}
    },
    [TRAINER_PLUTO_HQ_B7F_SCIENTIST_NICO] = {
        .partyFlags = PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_N, _i, _c, _o, _END},
        .items = { ITEM_X_SP_DEF },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_ScientistNico),
        .party = {.ItemDefaultMoves = sParty_PlutoHQ_B7F_ScientistNico}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_MITCH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_M, _i, _t, _c, _h, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoMitch),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoMitch}
    },
    [TRAINER_PLUTO_HQ_B7F_TEAM_PLUTO_RICHARD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_M,
        .trainerName = {_R, _i, _c, _h, _a, _r, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoRichard),
        .party = {.NoItemDefaultMoves = sParty_PlutoHQ_B7F_TeamPlutoRichard}
    },
    [TRAINER_PLUTO_HQ_B4F_PLUTO_ADMIN_IRENE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_IRENE,
        .trainerName = {_I, _r, _e, _n, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B4F_TeamPlutoAdminIrene),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B4F_TeamPlutoAdminIrene}
    },
    [TRAINER_PLUTO_HQ_B7F_PLUTO_ADMIN_RONALD] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_ADMIN,
        .trainerPic = TRAINER_PIC_PLUTO_ADMIN_RONALD,
        .trainerName = {_R, _o, _n, _a, _l, _d, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_PlutoHQ_B7F_TeamPlutoAdminRonald),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B7F_TeamPlutoAdminRonald}
    },
    [TRAINER_PLUTO_HQ_B1F_PLUTO_LEADER_KURTIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_TEAM_PLUTO_LEADER,
        .trainerPic = TRAINER_PIC_PLUTO_LEADER_KURTIS,
        .trainerName = {_K, _u, _r, _t, _i, _s, _END},
        .items = { ITEM_FULL_RESTORE, ITEM_MEGA_RING },
        .doubleBattle = FALSE,
        .aiFlags =  AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis),
        .party = {.ItemCustomMoves = sParty_PlutoHQ_B1F_TeamPlutoLeaderKurtis}
    },
    // #endregion
    // #region Route 18
    [TRAINER_ROUTE_18_SWIMMER_JASPER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_J, _a, _s, _p, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route18_SwimmerJasper),
        .party = {.NoItemDefaultMoves = sParty_Route18_SwimmerJasper}
    },
    [TRAINER_ROUTE_18_TRIATHLETE_DEBORAH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_D, _e, _b, _o, _r, _a, _h, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route18_TriathleteDeborah),
        .party = {.NoItemDefaultMoves = sParty_Route18_TriathleteDeborah}
    },
    [TRAINER_ROUTE_18_SWIMMER_JUDIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_J, _u, _d, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route18_SwimmerJudie),
        .party = {.NoItemDefaultMoves = sParty_Route18_SwimmerJudie}
    },
    [TRAINER_ROUTE_18_BIRD_KEEPER_KIRK] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_K, _i, _r, _k, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route18_BirdKeeperKirk),
        .party = {.NoItemDefaultMoves = sParty_Route18_BirdKeeperKirk}
    },
    [TRAINER_ROUTE_18_LASS_EMMA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_E, _m, _m, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route18_LassEmma),
        .party = {.NoItemDefaultMoves = sParty_Route18_LassEmma}
    },
    [TRAINER_ROUTE_18_CAVE_BLACKBELT_ROHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _o, _h, _a, _n, _END},
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route18_BlackbeltRohan),
        .party = {.NoItemDefaultMoves = sParty_Route18_BlackbeltRohan}
    },
    // #endregion
    // #region Route 16
    [TRAINER_ROUTE_16_SWIMMER_M_GALE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _a, _l, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerGale),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerGale}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_AMY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_A, _m, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerAmy),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerAmy}
    },
    [TRAINER_ROUTE_16_BIRD_KEEPER_TREVOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _r, _e, _v, _o, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route16_BirdKeeperTrevor),
        .party = {.NoItemDefaultMoves = sParty_Route16_BirdKeeperTrevor}
    },
    [TRAINER_ROUTE_16_LADY_MARIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = {_M, _a, _r, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lady_Standard,
        .partySize = NELEMS(sParty_Route16_LadyMaria),
        .party = {.NoItemDefaultMoves = sParty_Route16_LadyMaria}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_CHRISTINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _h, _r, _i, _s, _t, _i, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerChristina),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerChristina}
    },
    [TRAINER_ROUTE_16_SWIMMER_M_PHILLIP] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_P, _h, _i, _l, _l, _i, _p, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerPhillip),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerPhillip}
    },
    [TRAINER_ROUTE_16_SWIMMER_M_LESTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_L, _e, _s, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerLester),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerLester}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_WENDY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_W, _e, _n, _d, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerWendy),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerWendy}
    },
    [TRAINER_ROUTE_16_TUBER_CODY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_MALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = {_C, _o, _d, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route16_TuberCody),
        .party = {.NoItemDefaultMoves = sParty_Route16_TuberCody}
    },
    [TRAINER_ROUTE_16_TUBER_LESLIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TUBER_RS_FEMALE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = {_L, _e, _s, _l, _i, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Tuber_Standard,
        .partySize = NELEMS(sParty_Route16_TuberLeslie),
        .party = {.NoItemDefaultMoves = sParty_Route16_TuberLeslie}
    },
    [TRAINER_ROUTE_16_SWIMMER_F_CLEMENTINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _l, _e, _m, _e, _n, _t, _i, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route16_SwimmerClementine),
        .party = {.NoItemDefaultMoves = sParty_Route16_SwimmerClementine}
    },
    // #endregion
    // #region Route 14
    [TRAINER_ROUTE_14_SWIMMER_M_IVAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_I, _v, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerIvan),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerIvan}
    },
    [TRAINER_ROUTE_14_HIKER_CLIFFORD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_C, _l, _i, _f, _f, _o, _r, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route14_HikerClifford),
        .party = {.NoItemDefaultMoves = sParty_Route14_HikerClifford}
    },
    [TRAINER_ROUTE_14_FISHERMAN_ESTEBAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_E, _s, _t, _e, _b, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route14_FishermanEsteban),
        .party = {.NoItemDefaultMoves = sParty_Route14_FishermanEsteban}
    },
    [TRAINER_ROUTE_14_FISHERMAN_TUCKER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_T, _u, _c, _k, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route14_FishermanTucker),
        .party = {.NoItemDefaultMoves = sParty_Route14_FishermanTucker}
    },
    [TRAINER_ROUTE_14_SWIMMER_F_ELEANOR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_E, _l, _e, _a, _n, _o, _r, _END},
        .items = { ITEM_SUPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerEleanor),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerEleanor}
    },
    [TRAINER_ROUTE_14_BLACKBELT_JOAQUIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_J, _o, _a, _q, _u, _i, _n, _END},
        .items = { ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route14_BlackbeltJoaquin),
        .party = {.NoItemDefaultMoves = sParty_Route14_BlackbeltJoaquin}
    },
    [TRAINER_ROUTE_14_SWIMMER_M_CHRIS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_C, _h, _r, _i, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerChris),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerChris}
    },
    [TRAINER_ROUTE_14_YOUNGSTER_FREDDIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_F, _r, _e, _d, _d, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route14_YoungsterFreddie),
        .party = {.NoItemDefaultMoves = sParty_Route14_YoungsterFreddie}
    },
    [TRAINER_ROUTE_14_PSYCHIC_TOBIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_T, _o, _b, _i, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route14_PsychicTobin),
        .party = {.NoItemDefaultMoves = sParty_Route14_PsychicTobin}
    },
    [TRAINER_ROUTE_14_SWIMMER_F_MACIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _a, _c, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route14_SwimmerMacie),
        .party = {.NoItemDefaultMoves = sParty_Route14_SwimmerMacie}
    },    
    // #endregion
    // #region Route 15 North and South
    [TRAINER_ROUTE_15_NORTH_SWIMMER_MILES] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_M, _i, _l, _e, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerMiles),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerMiles}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_FIONA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_F, _i, _o, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerFiona),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerFiona}
    },
    [TRAINER_ROUTE_15_NORTH_HIKER_KLAUS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_K, _l, _a, _u, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route15North_HikerKlaus),
        .party = {.NoItemDefaultMoves = sParty_Route15North_HikerKlaus}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_URSULA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_U, _r, _s, _u, _l, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerUrsula),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerUrsula}
    },
    [TRAINER_ROUTE_15_NORTH_SWIMMER_QUINCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_Q, _u, _i, _n, _c, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15North_SwimmerQuincy),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SwimmerQuincy}
    },
    [TRAINER_ROUTE_15_NORTH_COOL_TRAINER_WESLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_W, _e, _s, _l, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route15North_CoolTrainerWesley),
        .party = {.NoItemDefaultMoves = sParty_Route15North_CoolTrainerWesley}
    },
    [TRAINER_ROUTE_15_NORTH_SUPER_NERD_ETHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _t, _h, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route15North_SuperNerdEthan),
        .party = {.NoItemDefaultMoves = sParty_Route15North_SuperNerdEthan}
    },
    [TRAINER_ROUTE_15_NORTH_CHANNELER_LILA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_L, _i, _l, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_Route15North_ChannelerLila),
        .party = {.NoItemDefaultMoves = sParty_Route15North_ChannelerLila}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_GERALD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_G, _e, _r, _a, _l, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerGerald),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerGerald}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_ALEXANDRA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_A, _l, _e, _x, _a, _n, _d, _r, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerAlexandra),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerAlexandra}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_BERNARD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_B, _e, _r, _n, _a, _r, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerBernard),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerBernard}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_HAROLD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_H, _a, _r, _o, _l, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerHarold),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerHarold}
    },
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_MELINDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_M, _e, _l, _i, _n, _d, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerMelinda),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerMelinda}
    },
    [TRAINER_ROUTE_15_SOUTH_BLACKBELT_FRANKLIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_F, _r, _a, _n, _k, _l, _i, _n, _END},
        .items = {ITEM_X_DEFEND},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route15South_BlackbeltFranklin),
        .party = {.NoItemDefaultMoves = sParty_Route15South_BlackbeltFranklin}
    },    
    [TRAINER_ROUTE_15_SOUTH_SWIMMER_PATRICIA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_P, _a, _t, _r, _i, _c, _i, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_Route15South_SwimmerPatricia),
        .party = {.NoItemDefaultMoves = sParty_Route15South_SwimmerPatricia}
    },
    // #endregion
    // #region Seppire Cove
    [TRAINER_SEPPIRE_COVE_SWIMMER_VALERIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_V, _a, _l, _e, _r, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_SeppireCove_SwimmerValerie),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_SwimmerValerie}
    },
    [TRAINER_SEPPIRE_COVE_SWIMMER_ICHABOD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SWIMMER_M,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_I, _c, _h, _a, _b, _o, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Swimmer_Standard,
        .partySize = NELEMS(sParty_SeppireCove_SwimmerIchabod),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_SwimmerIchabod}
    },
    [TRAINER_SEPPIRE_COVE_RUIN_MANIAC_CARTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_C, _a, _r, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_SeppireCove_RuinManiacCarter),
        .party = {.NoItemDefaultMoves = sParty_SeppireCove_RuinManiacCarter}
    },    
    // #endregion
    // #region Route 19
    [TRAINER_ROUTE_19_LASS_SAMANTHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_S, _a, _m, _a, _n, _t, _h, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_Route19_LassSamantha),
        .party = {.NoItemDefaultMoves = sParty_Route19_LassSamantha}
    },
    [TRAINER_ROUTE_19_COOLTRAINER_ROSE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_R, _o, _s, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route19_CoolTrainerRose),
        .party = {.NoItemDefaultMoves = sParty_Route19_CoolTrainerRose}
    },
    [TRAINER_ROUTE_19_POKEFAN_PHINEAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_P, _h, _i, _n, _e, _a, _s, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route19_PokefanPhineas),
        .party = {.NoItemDefaultMoves = sParty_Route19_PokefanPhineas}
    },
    [TRAINER_ROUTE_19_POKEFAN_PHOEBE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_P, _h, _o, _e, _b, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_Route19_PokefanPhoebe),
        .party = {.NoItemDefaultMoves = sParty_Route19_PokefanPhoebe}
    },
    // #endregion
    // #region Emraldin Quay
    [TRAINER_EMRALDIN_TRAINER_HOUSE_CHANNELER_MARGUERITE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_M, _a, _r, _g, _u, _e, _r, _i, _t, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_ChannelerMarguerite),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_ChannelerMarguerite}
    },
    [TRAINER_EMRALDIN_TRAINER_HOUSE_NINJA_BOY_JULIEN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_J, _u, _l, _i, _e, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_NinjaBoyJulien),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_NinjaBoyJulien}
    },
    [TRAINER_EMRALDIN_TRAINER_HOUSE_BUG_CATCHER_PERRY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_P, _e, _r, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_EmraldinQuay_BugCatcherPerry),
        .party = {.NoItemCustomMoves = sParty_EmraldinQuay_BugCatcherPerry}
    },    
    // #endregion
    // #region Route 23
    [TRAINER_ROUTE_23_BIRD_KEEPER_TYRONE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_T, _y, _r, _o, _n, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_Route23_BirdKeeperTyrone),
        .party = {.NoItemDefaultMoves = sParty_Route23_BirdKeeperTyrone}
    },
    [TRAINER_ROUTE_23_GAMBLER_GORDON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GAMBLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMBLER,
        .trainerName = {_G, _o, _r, _d, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gambler_Standard,
        .partySize = NELEMS(sParty_Route23_GamblerGordon),
        .party = {.NoItemDefaultMoves = sParty_Route23_GamblerGordon}
    },
    [TRAINER_ROUTE_23_SUPER_NERD_EMMETT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _m, _m, _e, _t, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route23_SuperNerdEmmett),
        .party = {.NoItemDefaultMoves = sParty_Route23_SuperNerdEmmett}
    },
    [TRAINER_ROUTE_23_GENTLEMAN_RUSSELL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_R, _u, _s, _s, _e, _l, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Gentleman_Standard,
        .partySize = NELEMS(sParty_Route23_GentlemanRussell),
        .party = {.NoItemDefaultMoves = sParty_Route23_GentlemanRussell}
    },
    [TRAINER_ROUTE_23_CRUSH_GIRL_LILY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_L, _i, _l, _y, _END},
        .items = { ITEM_X_ATTACK },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route23_CrushGirlLily),
        .party = {.NoItemDefaultMoves = sParty_Route23_CrushGirlLily}
    },
    [TRAINER_ROUTE_23_BEAUTY_MIRANDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_M, _i, _r, _a, _n, _d, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Beauty_Standard,
        .partySize = NELEMS(sParty_Route23_BeautyMiranda),
        .party = {.NoItemDefaultMoves = sParty_Route23_BeautyMiranda}
    },
    // #endregion
    // #region Route 20
    [TRAINER_ROUTE_20_PSYCHIC_MCKENZIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_M, _c, _K, _e, _n, _z, _i, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route20_PsychicMcKenzie),
        .party = {.NoItemDefaultMoves = sParty_Route20_PsychicMcKenzie}
    },
    [TRAINER_ROUTE_20_PICNICKER_WHITNEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PICNICKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_W, _h, _i, _t, _n, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Picnicker_Standard,
        .partySize = NELEMS(sParty_Route20_PicknickerWhitney),
        .party = {.NoItemDefaultMoves = sParty_Route20_PicknickerWhitney}
    },
    [TRAINER_ROUTE_20_TRIATHLETE_LENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_L, _e, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route20_TriathleteLena),
        .party = {.NoItemDefaultMoves = sParty_Route20_TriathleteLena}
    },
    [TRAINER_ROUTE_20_ENGINEER_HOMER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _o, _m, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_Route20_EngineerHomer),
        .party = {.NoItemDefaultMoves = sParty_Route20_EngineerHomer}
    },
    [TRAINER_ROUTE_20_CRUSH_GIRL_ROXY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_R, _o, _x, _y, _END},
        .items = { ITEM_X_SPEED },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_Route20_CrushGirlRoxy),
        .party = {.NoItemDefaultMoves = sParty_Route20_CrushGirlRoxy}
    },
    [TRAINER_ROUTE_20_HIKER_ROYCE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _y, _c, _e, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route20_HikerRoyce),
        .party = {.NoItemDefaultMoves = sParty_Route20_HikerRoyce}
    },
    [TRAINER_ROUTE_20_SUPER_NERD_ELLIOT] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_E, _l, _l, _i, _o, _t, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_Route20_SuperNerdElliot),
        .party = {.NoItemDefaultMoves = sParty_Route20_SuperNerdElliot}
    },
    [TRAINER_ROUTE_20_YOUNGSTER_DEWEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_D, _e, _w, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Youngster_Standard,
        .partySize = NELEMS(sParty_Route20_YoungsterDewey),
        .party = {.NoItemDefaultMoves = sParty_Route20_YoungsterDewey}
    },
    [TRAINER_ROUTE_20_JUGGLER_HIRAM] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_H, _i, _r, _a, _m, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_Route20_JugglerHiram),
        .party = {.NoItemDefaultMoves = sParty_Route20_JugglerHiram}
    },
    [TRAINER_ROUTE_20_NURSE_JESSIE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_J, _e, _s, _s, _i, _e, _END},
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_Route20_NurseJessie),
        .party = {.NoItemDefaultMoves = sParty_Route20_NurseJessie}
    },
    // #endregion
    // #region Route 22
    [TRAINER_ROUTE_22_COOL_TRAINER_GAIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_G, _a, _i, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_Route22_CoolTrainer_Gail),
        .party = {.NoItemDefaultMoves = sParty_Route22_CoolTrainer_Gail}
    },
    [TRAINER_ROUTE_22_SCIENTIST_LARRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_L, _a, _r, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_Route22_ScientistLarry),
        .party = {.NoItemDefaultMoves = sParty_Route22_ScientistLarry}
    },
    [TRAINER_ROUTE_22_SRANDJR_ALMA_AND_MAI] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SR_AND_JR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = {_A, _l, _m, _a, _SPACE, _AMPERSAND, _SPACE, _M, _a, _i, _END},
        .items = { },
        .doubleBattle = TRUE,
        .aiFlags = TrainerAIFlags_SrAndJr_Standard,
        .partySize = NELEMS(sParty_Route22_SrAndJr_AlmaAndMai),
        .party = {.NoItemDefaultMoves = sParty_Route22_SrAndJr_AlmaAndMai}
    },
    [TRAINER_ROUTE_22_JUGGLER_CHAUNCY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_C, _h, _a, _u, _n, _c, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_Route22_JugglerChauncy),
        .party = {.NoItemDefaultMoves = sParty_Route22_JugglerChauncy}
    },
    [TRAINER_ROUTE_22_BURGLAR_MOSE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_M, _o, _s, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_Route22_BurglarMose),
        .party = {.NoItemDefaultMoves = sParty_Route22_BurglarMose}
    },
    // #endregion
    // #region Route 21
    [TRAINER_ROUTE_21_POKEFAN_WALTER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_W, _a, _l, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_Route21_PokefanWalter),
        .party = {.NoItemDefaultMoves = sParty_Route21_PokefanWalter}
    },
    [TRAINER_ROUTE_21_COLLECTOR_ERIC] = {
        .partyFlags = 0,
        .trainerClass = CLASS_COLLECTOR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = {_E, _r, _i, _c, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Collector_Standard,
        .partySize = NELEMS(sParty_Route21_CollectorEric),
        .party = {.NoItemDefaultMoves = sParty_Route21_CollectorEric}
    },
    [TRAINER_ROUTE_21_HIKER_RICARDO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _i, _c, _a, _r, _d, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_Route21_HikerRicardo),
        .party = {.NoItemDefaultMoves = sParty_Route21_HikerRicardo}
    },
    [TRAINER_ROUTE_21_DRAGON_TAMER_TANNER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_T, _a, _n, _n, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_Route21_DragonTamerTanner),
        .party = {.NoItemDefaultMoves = sParty_Route21_DragonTamerTanner}
    },
    [TRAINER_ROUTE_21_PARASOL_LADY_KATRINA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PARASOL_LADY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_K, _a, _t, _r, _i, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_ParasolLady_Standard,
        .partySize = NELEMS(sParty_Route21_ParasolLadyKatrina),
        .party = {.NoItemDefaultMoves = sParty_Route21_ParasolLadyKatrina}
    },
    [TRAINER_ROUTE_21_NINJA_BOY_ISHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_NINJA_BOY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = {_I, _s, _h, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_NinjaBoy_Standard,
        .partySize = NELEMS(sParty_Route21_NinjaBoyIshan),
        .party = {.NoItemDefaultMoves = sParty_Route21_NinjaBoyIshan}
    },
    [TRAINER_ROUTE_21_ROCKER_AXEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_GUITARIST_RS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_A, _x, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Guitarist_Standard,
        .partySize = NELEMS(sParty_Route21_RockerAxel),
        .party = {.NoItemDefaultMoves = sParty_Route21_RockerAxel}
    },
    // #endregion
    // #region Secret Trail
    [TRAINER_SECRET_TRAIL_CHANNELER_HEATHER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_H, _e, _a, _t, _h, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_SecretTrail_ChannelerHeather),
        .party = {.NoItemDefaultMoves = sParty_SecretTrail_ChannelerHeather}
    },
    // #endregion
    // #region Mimmett Jungle
    [TRAINER_MIMMETT_JUNGLE_SCIENTIST_SILAS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_S, _i, _l, _a, _s, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_ScientistSilas),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_ScientistSilas}
    },
    [TRAINER_MIMMETT_JUNGLE_RUIN_MANIAC_WINSTON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_W, _i, _n, _s, _t, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_RuinManiacWinston),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_RuinManiacWinston}
    },
    [TRAINER_MIMMETT_JUNGLE_BLACKBELT_LOUIS] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_L, _o, _u, _i, _s, _END},
        .items = { ITEM_X_SP_DEF },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_BlackbeltLouis),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_BlackbeltLouis}
    },
    [TRAINER_MIMMETT_JUNGLE_CHANNELER_FREYJA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_F, _r, _e, _y, _j, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_ChannelerFreyja),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_ChannelerFreyja}
    },
    [TRAINER_MIMMETT_JUNGLE_BUG_CATCHER_NEIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_N, _e, _i, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BugCatcher_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_BugCatcherNeil),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_BugCatcherNeil}
    },
    [TRAINER_MIMMETT_JUNGLE_FISHERMAN_JERRY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_J, _e, _r, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_FishermanJerry),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_FishermanJerry}
    },
    [TRAINER_MIMMETT_JUNGLE_POKEFAN_SUSAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_S, _u, _s, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Pokefan_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_PokefanSusan),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_PokefanSusan}
    },
    [TRAINER_MIMMETT_JUNGLE_PSYCHIC_WANDA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_W, _a, _n, _d, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_MimmettJungle_PsychicWanda),
        .party = {.NoItemDefaultMoves = sParty_MimmettJungle_PsychicWanda}
    },
    // #endregion
    // #region Tsarvosa City
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_KAITO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SENSEI,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerName = {_K, _a, _i, _t, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_Kaito),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_StatsDojo_Kaito}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_ZACHARY_HP_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_Z, _a, _c, _h, _a, _r, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_ZacharyHP3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_ZacharyHP3}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_NELSON_ATK_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_N, _e, _l, _s, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_NelsonAttack3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_NelsonAttack3}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_DION_DEF_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_D, _i, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_DionDefense3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_DionDefense3}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SEYMOUR_SPATK_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _e, _y, _m, _o, _u, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SeymourSpecialAttack3}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_GARLAND_SPDEF_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_G, _a, _r, _l, _a, _n, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_GarlandSpecialDefense3}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed1),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed1}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_2] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed2),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed2}
    },
    [TRAINER_TSARVOSA_CITY_STATS_DOJO_SIDNEY_SPEED_3] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DISCIPLE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = {_S, _i, _d, _n, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Disciple_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_StatsDojo_SidneySpeed3),
        .party = {.NoItemDefaultMoves = sParty_TsarvosaCity_StatsDojo_SidneySpeed3}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_COLLIN_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _l, _i, _n, _END},
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin1),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin1}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_COLLIN_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = {_C, _o, _l, _l, _i, _n, _END},
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Collin2),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Collin2}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_CRYSTAL_1] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = {_C, _r, _y, _s, _t, _a, _l, _END },
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal1),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal1}
    },
    [TRAINER_TSARVOSA_CITY_DEV_TEAM_CRYSTAL_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_DEVELOPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = {_C, _r, _y, _s, _t, _a, _l, _END },
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Developer_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_DevTeam_Crystal2),
        .party = {.ItemCustomMoves = sParty_TsarvosaCity_DevTeam_Crystal2}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_NOAM] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_N, _o, _a, _m, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Noam),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Noam}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ASHLEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_A, _s, _h, _l, _e, _y, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ashley),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ashley}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CHELSEA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_C, _h, _e, _l, _s, _e, _a, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Chelsea),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Chelsea}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BUDDY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _u, _d, _d, _y, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Buddy),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Buddy}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_GAWAIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_G, _a, _w, _a, _i, _n, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Gawain),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Gawain}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SKYLAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_S, _k, _y, _l, _a, _r, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Skylar),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Skylar}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_BELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_BREEDER_F,
        .trainerName = {_B, _e, _l, _l, _a, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Bella),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Bella}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FLASH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_F, _l, _a, _s, _h, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Flash),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Flash}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_TERRA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PKMN_RANGER_F,
        .trainerName = {_T, _e, _r, _r, _a, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Terra),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Terra}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_SEIFA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_S, _e, _i, _f, _a, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Seifa),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Seifa}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ROCCO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_R, _o, _c, _c, _o, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Rocco),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Rocco}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_JANICE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SKIER,
        .trainerName = {_J, _a, _n, _i, _c, _e, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Janice),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Janice}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_ANTOINETTE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_A, _n, _t, _o, _i, _n, _e, _t, _t, _e, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Antoinette),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Antoinette}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_RYU] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_R, _y, _u, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Ryu),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Ryu}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_CASPAR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_C, _a, _s, _p, _a, _r, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Caspar),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Caspar}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_DARCY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_D, _a, _r, _c, _y, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Darcy),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Darcy}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_MASON] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_M, _a, _s, _o, _n, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Mason),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Mason}
    },
    [TRAINER_TSARVOSA_CITY_GYM_TRAINEE_FAYE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_GYM_TRAINEE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = {_F, _a, _y, _e, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_GymTrainees_Standard,
        .partySize = NELEMS(sParty_TsarvosaCity_GymTrainees_Faye),
        .party = {.NoItemCustomMoves = sParty_TsarvosaCity_GymTrainees_Faye}
    },
    [TRAINER_TSARVOSA_CITY_GYM_MARCI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_M, _a, _r, _c, _i, _END },
        .items = { ITEM_HYPER_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN,
        .partySize = NELEMS(sParty_TsarvosaCityGym_PokefanMarci),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_PokefanMarci}
    },
    [TRAINER_TSARVOSA_CITY_GYM_JAMILA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_J, _a, _m, _i, _l, _a, _END },
        .items = { ITEM_MAX_POTION },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_TsarvosaCityGym_ChannelerJamila),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_ChannelerJamila}
    },
    [TRAINER_TSARVOSA_CITY_GYM_NORBERT] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_N, _o, _r, _b, _e, _r, _t, _END },
        .items = { ITEM_X_SP_ATK, ITEM_LEMONADE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_CoolTrainerNorbert),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_CoolTrainerNorbert}
    },
    [TRAINER_TSARVOSA_CITY_GYM_MARION] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_M, _a, _r, _i, _o, _n, _END },
        .items = { ITEM_MOOMOO_MILK, ITEM_X_DEFEND },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY,
        .partySize = NELEMS(sParty_TsarvosaCityGym_BurglarMarion),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_BurglarMarion}
    },
    [TRAINER_TSARVOSA_CITY_GYM_ALANAH] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_A, _l, _a, _n, _a, _h, _END },
        .items = { ITEM_MOOMOO_MILK, ITEM_FULL_HEAL },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_LassAlanah),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_LassAlanah}
    },
    [TRAINER_TSARVOSA_CITY_GYM_PAUL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_GENTLEMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = {_P, _a, _u, _l, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_HP_AWARE,
        .partySize = NELEMS(sParty_TsarvosaCityGym_GentlemanPaul),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_GentlemanPaul}
    },
    [TRAINER_TSARVOSA_CITY_GYM_LEADER_IRIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END },
        .items = { ITEM_MAX_POTION, ITEM_FULL_HEAL },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_TsarvosaCityGym_LeaderIris),
        .party = {.ItemCustomMoves = sParty_TsarvosaCityGym_LeaderIris}
    },
    // #endregion
    // #region Daimyn City Restaurant
    [TRAINER_DAIMYN_CITY_RESTAURANT_IRIS] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_IRIS,
        .trainerName = {_I, _r, _i, _s, _END },
        .items = { ITEM_FULL_RESTORE },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Iris),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Iris}
    },
    [TRAINER_DAIMYN_CITY_RESTAURANT_STELLA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_STELLA,
        .trainerName = {_S, _t, _e, _l, _l, _a, _END},
        .items = { ITEM_FULL_HEAL },
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_DaimynCityRestaurant_Stella),
        .party = {.ItemCustomMoves = sParty_DaimynCityRestaurant_Stella}
    },
    // #endregion
    // #region Daimyn Factory
    [TRAINER_DAIMYN_FACTORY_BURGLAR_SLY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_S, _l, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BurglarSly),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BurglarSly}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_HASAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_H, _a, _s, _a, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerHasan),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerHasan}
    },
    [TRAINER_DAIMYN_FACTORY_BURGLAR_WILL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_W, _i, _l, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Burglar_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_BurglarWill),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_BurglarWill}
    },
    [TRAINER_DAIMYN_FACTORY_ENGINEER_ELROY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ENGINEER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WORKER,
        .trainerName = {_E, _l, _r, _o, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Engineer_Standard,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerElroy),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerElroy}
    },
    // #endregion
    // #region Carnelidge Volcano
    [TRAINER_CARNELIDGE_VOLCANO_HIKER_BJORN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_B, _j, _o, _r, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_HikerBjorn),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_HikerBjorn}
    },
    [TRAINER_CARNELIDGE_VOLCANO_CHANNELER_KELSEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_K, _e, _l, _s, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_ChannelerKelsey),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_ChannelerKelsey}
    },
    [TRAINER_CARNELIDGE_VOLCANO_JUGGLER_SETH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_JUGGLER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = {_S, _e, _t, _h, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Juggler_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_JugglerSeth),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_JugglerSeth}
    },
    [TRAINER_CARNELIDGE_VOLCANO_DRAGON_TAMER_FLYNN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_F, _l, _y, _n, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_DragonTamerFlynn),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_DragonTamerFlynn}
    },
    [TRAINER_CARNELIDGE_VOLCANO_BIRD_KEEPER_FALCO] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BIRD_KEEPER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = {_F, _a, _l, _c, _o, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BirdKeeper_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_BirdKeepeFalco),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_BirdKeepeFalco}
    },
    [TRAINER_CARNELIDGE_VOLCANO_CRUSH_GIRL_EUNICE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CRUSH_GIRL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = {_E, _u, _n, _i, _c, _e, _END},
        .items = { ITEM_X_SPEED },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CrushGirl_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_CrushGirlEunice),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_CrushGirlEunice}
    },
    [TRAINER_CARNELIDGE_VOLCANO_SUPER_NERD_NATHAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_N, _a, _t, _h, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_SuperNerdNathan),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_SuperNerdNathan}
    },
    [TRAINER_CARNELIDGE_VOLCANO_HIKER_HUGH] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_H, _u, _g, _h, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Hiker_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_HikerHugh),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_HikerHugh}
    },
    [TRAINER_CARNELIDGE_VOLCANO_SCIENTIST_XANDER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SCIENTIST,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_X, _a, _n, _d, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Scientist_Standard,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_ScientistXander),
        .party = {.NoItemDefaultMoves = sParty_CarnelidgeVolcano_ScientistXander}
    },
    [TRAINER_CARNELIDGE_VOLCANO_PARTNER_RIVAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .items = {ITEM_MEGA_RING, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_SEMI_SMART | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_CarnelidgeVolcano_PartnerRival),
        .party = {.ItemCustomMoves = sParty_CarnelidgeVolcano_PartnerRival}
    },
    // #endregion
    // #region Uteya Village
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_PICKNICKER_LISA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = {_L, _i, _s, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_PicknickerLisa),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_PicknickerLisa}
    },
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_SWIMMER_TYSON] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = {_T, _y, _s, _o, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_SwimmerTyson),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_SwimmerTyson}
    },
    [TRAINER_UTEYA_VILLAGE_TRAINER_HOUSE_SCIENTIST_WILFORD] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PKMN_TRAINER_3,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST_M,
        .trainerName = {_W, _i, _l, _f, _o, _r, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_UteyaVillage_ScientistWilford),
        .party = {.NoItemDefaultMoves = sParty_UteyaVillage_ScientistWilford}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_MICHAEL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_M, _i, _c, _h, _a, _e, _l, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Michael),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Michael}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_LEO] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_L, _e, _o, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Leo),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Leo}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_BONNIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = {_B, _o, _n, _n, _i, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Bonnie),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Bonnie}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_CLYDE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_C, _l, _y, _d, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Clyde),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Clyde}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_JESSIE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SWIMMER_F,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = {_J, _e, _s, _s, _i, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Jessie),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Jessie}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_JAMES] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _a, _m, _e, _s, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_James),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_James}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_MIKE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_M, _i, _k, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Mike),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Mike}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_DIANE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = {_D, _i, _a, _n, _n, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Diane),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Diane}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_HANNIBAL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_H, _a, _n, _n, _i, _b, _a, _l, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Hannibal),
        .party = {.NoItemCustomMoves = sParty_UteyaVillageGym_Hannibal}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_CLARICE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_C, _l, _a, _r, _i, _c, _e, _END},
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_Clarice),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_Clarice}
    },
    [TRAINER_UTEYA_VILLAGE_GYM_LEADERS_DENNIS_AND_DEE] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_LEADER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DENNIS_AND_DEE,
        .trainerName = {_D, _e, _n, _n, _i, _s, _AMPERSAND, _D, _e, _e, _END},
        .items = {ITEM_MAX_POTION},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SEMI_SMART | AI_SCRIPT_DOUBLE_BATTLE,
        .partySize = NELEMS(sParty_UteyaVillageGym_LeadersDennisAndDee),
        .party = {.ItemCustomMoves = sParty_UteyaVillageGym_LeadersDennisAndDee}
    },
    // #endregion
    // #region Route 24
    [TRAINER_ROUTE_24_PSYCHIC_RAYA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_R, _a, _y, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route24_PsychicRaya),
        .party = {.NoItemDefaultMoves = sParty_Route24_PsychicRaya}
    },
    [TRAINER_ROUTE_24_DRAGON_TAMER_DAVID] = {
        .partyFlags = 0,
        .trainerClass = CLASS_DRAGON_TAMER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = {_D, _a, _v, _i, _d, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_DragonTamer_Standard,
        .partySize = NELEMS(sParty_Route24_DragonTamerDavid),
        .party = {.NoItemDefaultMoves = sParty_Route24_DragonTamerDavid}
    },
    [TRAINER_ROUTE_24_PSYCHIC_JEFF] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = {_J, _e, _f, _f, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_Route24_PsychicJeff),
        .party = {.NoItemDefaultMoves = sParty_Route24_PsychicJeff}
    },
    [TRAINER_ROUTE_24_FISHERMAN_HUMPHREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_FISHERMAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = {_H, _u, _m, _p, _h, _r, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Fisherman_Standard,
        .partySize = NELEMS(sParty_Route24_FishermanHumphrey),
        .party = {.NoItemDefaultMoves = sParty_Route24_FishermanHumphrey}
    },
    [TRAINER_ROUTE_24_TRIATHLETE_WILLOW] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TRIATHLETE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = {_W, _i, _l, _l, _o, _w, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Triathlete_Standard,
        .partySize = NELEMS(sParty_Route24_TriathleteWillow),
        .party = {.NoItemDefaultMoves = sParty_Route24_TriathleteWillow}
    },
    [TRAINER_ROUTE_24_BLACKBELT_IRVINE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_I, _r, _v, _i, _n, _e, _END},
        .items = { ITEM_DIRE_HIT },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_BlackBelt_Standard,
        .partySize = NELEMS(sParty_Route24_BlackbeltIrvine),
        .party = {.NoItemDefaultMoves = sParty_Route24_BlackbeltIrvine}
    },
    // #endregion
    // #region Uteyan Ruins
    [TRAINER_UTEYAN_RUINS_RUIN_MANIAC_KRISTIAN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_K, _r, _i, _s, _t, _i, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_RuinManiacKristian),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_RuinManiacKristian}
    },
    [TRAINER_UTEYAN_RUINS_PSYCHIC_HALEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_H, _a, _l, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Psychic_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_PsychicHaley),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_PsychicHaley}
    },
    [TRAINER_UTEYAN_RUINS_RUIN_MANIAC_CYRIL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RUIN_MANIAC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = {_C, _y, _r, _i, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_RuinManiac_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_RuinManiacCyril),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_RuinManiacCyril}
    },
    [TRAINER_UTEYAN_RUINS_SUPER_NERD_MORTY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_SUPER_NERD,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = {_M, _o, _r, _t, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_SuperNerd_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_SuperNerdMorty),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_SuperNerdMorty}
    },
    [TRAINER_UTEYAN_RUINS_CHANNELER_AGATHA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_CHANNELER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = {_A, _g, _a, _t, _h, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Channeler_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_ChannelerAgatha),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_ChannelerAgatha}
    },
    [TRAINER_UTEYAN_RUINS_LASS_DOROTHY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_LASS,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = {_D, _o, _r, _o, _t, _h, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Lass_Standard,
        .partySize = NELEMS(sParty_UteyanRuins_LassDorothy),
        .party = {.NoItemDefaultMoves = sParty_UteyanRuins_LassDorothy}
    },
    // #endregion
    // #region Victory Road
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_TIMOTHY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_T, _i, _m, _o, _t, _h, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerTimothy),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerTimothy}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_JONATHAN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_J, _o, _n, _a, _t, _h, _a, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerJonathan),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerJonathan}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_SATOSHI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_S, _a, _t, _o, _s, _h, _i, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerSatoshi),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerSatoshi}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_COURTNEY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_C, _o, _u, _r, _t, _n, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerCourtney),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerCourtney}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_THERESA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_T, _h, _e, _r, _e, _s, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerTheresa),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerTheresa}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ABDUL] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _b, _d, _u, _l, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerAbdul),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerAbdul}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ARTHUR] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_A, _r, _t, _h, _u, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerArthur),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerArthur}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_KELLY] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_K, _e, _l, _l, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerKelly),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerKelly}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_LYDIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_L, _y, _d, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerLydia),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerLydia}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_ROBIN] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_R, _o, _b, _i, _n, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerRobin),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerRobin}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_LUIGI] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = {_L, _u, _i, _g, _i, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerLuigi),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerLuigi}
    },
    [TRAINER_VICTORY_ROAD_COOL_TRAINER_DAHLIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_COOLTRAINER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = {_D, _a, _h, _l, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_CoolTrainer_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_CoolTrainerDahlia),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_CoolTrainerDahlia}
    },
    [TRAINER_VICTORY_ROAD_NURSE_CELIA] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES,
        .trainerClass = CLASS_NURSE,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_NURSE,
        .trainerName = {_C, _e, _l, _i, _a, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = TrainerAIFlags_Nurse_Standard,
        .partySize = NELEMS(sParty_VictoryRoad_NurseCelia),
        .party = {.NoItemCustomMoves = sParty_VictoryRoad_NurseCelia}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_V] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Vaporeon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Vaporeon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_J] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Jolteon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Jolteon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_F] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Flareon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Flareon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_E] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Espeon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Espeon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_U] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Umbreon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Umbreon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_L] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Leafeon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Leafeon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_G] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Glaceon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Glaceon}
    },
    [TRAINER_VICTORY_ROAD_RIVAL_S] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_VictoryRoad_Rival_Sylveon),
        .party = {.ItemCustomMoves = sParty_VictoryRoad_Rival_Sylveon}
    },
    // #endregion
    // #region Ascension Tower
    [TRAINER_DAIMYN_CITY_RIVAL_EXHIBITION_BATTLE_2] = {
        .partyFlags = PARTY_FLAG_CUSTOM_MOVES | PARTY_FLAG_HAS_ITEM,
        .trainerClass = CLASS_RIVAL_2,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RIVAL_2,
        .trainerName = NO_NAME,  // Name replaced from RIVAL trainer classes
        .items = { ITEM_MEGA_RING, ITEM_FULL_RESTORE },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_Rival_ExhibitionBattle_SecondaryTeam),
        .party = {.ItemCustomMoves = sParty_Rival_ExhibitionBattle_SecondaryTeam}
    },
    // #endregion
};
