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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 34,
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
        .lvl = 35,
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
        .lvl = 37,
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
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Jolteon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Flareon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Espeon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Umbreon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Leafeon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Glaceon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11RivalPartner_Sylveon[] = {
    {
        .lvl = 35,
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
        .lvl = 35,
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

const struct TrainerMonItemCustomMoves sParty_Route11_Alistair[] = {
    {
        .lvl = 35,
        .species = SPECIES_GOLBAT,
        .moves = {
            MOVE_WINGATTACK,
            MOVE_POISONFANG,
            MOVE_ROOST,
            MOVE_MEANLOOK
        },
        .ability = Ability_1 // Inner Focus
    },
    {
        .lvl = 35,
        .species = SPECIES_AMOONGUSS,
        .moves = {
            MOVE_GIGADRAIN,
            MOVE_CLEARSMOG,
            MOVE_TOXIC,
            MOVE_VENOSHOCK
        },
        .ability = Ability_1 // Effect Spore
    },
    {
        .lvl = 37,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
        .lvl = 38,
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
        .lvl = 38,
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
        .lvl = 39,
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
    { .lvl = 40, .species = SPECIES_TORKOAL },
    { .lvl = 40, .species = SPECIES_CRAWDAUNT },
    { .lvl = 40, .species = SPECIES_SLAKING },
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
    { .lvl = 37, .species = SPECIES_HAKAMO_O },
    { .lvl = 38, .species = SPECIES_SABLEYE },
    { .lvl = 40, .species = SPECIES_SHEDINJA },
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
    { .lvl = 38, .species = SPECIES_DRATINI },
    { .lvl = 38, .species = SPECIES_SEADRA },
    { .lvl = 40, .species = SPECIES_SHARPEDO }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_SrAndJr_SueAndKat[] = {
    { .lvl = 29, .species = SPECIES_EEVEE },
    { .lvl = 30, .species = SPECIES_BRELOOM },
    { .lvl = 29, .species = SPECIES_MISDREAVUS },
    { .lvl = 30, .species = SPECIES_LOPUNNY }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route6_HikerDarryl[] = {
    { .lvl = 45, .species = SPECIES_BOLDORE },
    { .lvl = 45, .species = SPECIES_BARBARACLE },
    { .lvl = 46, .species = SPECIES_TYRANTRUM },
    { .lvl = 46, .species = SPECIES_CONKELDURR }
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
        .lvl = 33,
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
        .lvl = 33,
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
        .lvl = 35,
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
        .lvl = 41,
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
        .lvl = 42,
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
        .lvl = 42,
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
        .lvl = 43,
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
    { .lvl = 24, .species = SPECIES_MINIOR_INDIGO },
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
    { .lvl = 37, .species = SPECIES_BINACLE },
    { .lvl = 38, .species = SPECIES_CORSOLA_G },
    { .lvl = 38, .species = SPECIES_BARBARACLE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_SwimmerBob[] = {
    { .lvl = 36, .species = SPECIES_LANTURN },
    { .lvl = 36, .species = SPECIES_SHELLDER },
    { .lvl = 40, .species = SPECIES_PELIPPER }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route8_CoolTrainerHarriet[] = {
    { .lvl = 39, .species = SPECIES_UMBREON },
    { .lvl = 40, .species = SPECIES_GASTRODON_EAST },
    { .lvl = 40, .species = SPECIES_CROBAT }
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
const struct TrainerMonNoItemDefaultMoves sParty_ForgottenManse_BF1_BurglarPeter[] = {
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
    { .lvl = 34, .species = SPECIES_NOCTOWL }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_RockerBenson[] = {
    { .lvl = 30, .species = SPECIES_KLINK },
    { .lvl = 32, .species = SPECIES_CHARJABUG }
};

const struct TrainerMonItemCustomMoves sParty_DaimynFactory_LassNatalie[] = {
    {
        .lvl = 32,
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
        .lvl = 32,
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
    { .lvl = 30, .species = SPECIES_MAWILE },
    { .lvl = 29, .species = SPECIES_FLAAFFY },
    { .lvl = 31, .species = SPECIES_JOLTIK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_HikerMike[] = {
    { .lvl = 32, .species = SPECIES_CUFANT },
    { .lvl = 32, .species = SPECIES_DRILBUR },
    { .lvl = 32, .species = SPECIES_CARBINK }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_BlackbeltRory[] = {
    { .lvl = 34, .species = SPECIES_MIENFOO },
    { .lvl = 35, .species = SPECIES_HAKAMO_O }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerWilson[] = {
    { .lvl = 33, .species = SPECIES_PACHIRISU },
    { .lvl = 35, .species = SPECIES_HELIOPTILE }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_YoungsterNate[] = {
    { .lvl = 33, .species = SPECIES_VIGOROTH },
    { .lvl = 35, .species = SPECIES_VIBRAVA }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_PicknickerShanna[] = {
    { .lvl = 33, .species = SPECIES_FRILLISH_F },
    { .lvl = 35, .species = SPECIES_GARDEVOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_DaimynFactory_EngineerKliff[] = {
    { .lvl = 33, .species = SPECIES_EMOLGA },
    { .lvl = 35, .species = SPECIES_RAICHU },
    { .lvl = 35, .species = SPECIES_STUNFISK_G }
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
        .lvl = 34,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 30,
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
        .lvl = 30,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 33,
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
        .lvl = 32,
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
        .lvl = 32,
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
        .lvl = 33,
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
        .lvl = 33,
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
        .lvl = 33,
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
        .lvl = 35,
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
        .lvl = 41,
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
        .lvl = 42,
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
        .lvl = 42,
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
        .lvl = 43,
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
    { .lvl = 32, .species = SPECIES_MR_MIME },
    { .lvl = 33, .species = SPECIES_MIMIKYU }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Andrea[] = {
    { .lvl = 33, .species = SPECIES_HERACROSS },
    { .lvl = 33, .species = SPECIES_TOUCANNON },
    { .lvl = 33, .species = SPECIES_TORRACAT }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Fisherman_Yusuf[] = {
    { .lvl = 32, .species = SPECIES_GYARADOS },
    { .lvl = 32, .species = SPECIES_GASTRODON },
};

const struct TrainerMonNoItemCustomMoves sParty_Route9_Gentleman_Gavin[] = {
    {
        .lvl = 33,
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
        .lvl = 33,
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
    { .lvl = 31, .species = SPECIES_NINJASK },
    { .lvl = 31, .species = SPECIES_KROKOROK },
    { .lvl = 33, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Breeder_Talia[] = {
    { .lvl = 30, .species = SPECIES_PIKACHU },
    { .lvl = 30, .species = SPECIES_TOGETIC },
    { .lvl = 32, .species = SPECIES_ESPEON },
    { .lvl = 32, .species = SPECIES_UMBREON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_Picknicker_Zoe[] = {
    { .lvl = 33, .species = SPECIES_VESPIQUEN },
    { .lvl = 34, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route9_CoolTrainer_Kingsley[] = {
    { .lvl = 35, .species = SPECIES_DECIDUEYE },
    { .lvl = 35, .species = SPECIES_VIBRAVA },
    { .lvl = 36, .species = SPECIES_SIRFETCHD },
};
// #endregion

// #region Route 10
const struct TrainerMonNoItemDefaultMoves sParty_Route10_PsychicDarius[] = {
    { .lvl = 31, .species = SPECIES_KIRLIA },
    { .lvl = 32, .species = SPECIES_MR_MIME_G },
    { .lvl = 32, .species = SPECIES_WOBBUFFET },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_BirdKeeperMario[] = {
    { .lvl = 32, .species = SPECIES_NOCTOWL },
    { .lvl = 32, .species = SPECIES_PELIPPER },
    { .lvl = 32, .species = SPECIES_SKARMORY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_GamblerDarren[] = {
    { .lvl = 34, .species = SPECIES_LILEEP },
    { .lvl = 34, .species = SPECIES_GLACEON },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_ParasolLadyGwen[] = {
    { .lvl = 36, .species = SPECIES_FLORGES_YELLOW },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_CamperJackson[] = {
    { .lvl = 34, .species = SPECIES_NIDORINO },
    { .lvl = 36, .species = SPECIES_CHESNAUGHT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_RockerBert[] = {
    { .lvl = 33, .species = SPECIES_THWACKEY },
    { .lvl = 33, .species = SPECIES_NOIBAT },
    { .lvl = 35, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerAlberto[] = {
    { .lvl = 35, .species = SPECIES_CORSOLA_G },
    { .lvl = 35, .species = SPECIES_CORPHISH },
    { .lvl = 38, .species = SPECIES_CURSOLA },
    { .lvl = 38, .species = SPECIES_CRAWDAUNT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerRosie[] = {
    { .lvl = 40, .species = SPECIES_JELLICENT_F },
    { .lvl = 42, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10_SwimmerDoug[] = {
    { .lvl = 39, .species = SPECIES_CARVANHA },
    { .lvl = 39, .species = SPECIES_SLOWBRO },
    { .lvl = 40, .species = SPECIES_BLASTOISE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_HikerHarley[] = {
    { .lvl = 32, .species = SPECIES_BOLDORE },
    { .lvl = 32, .species = SPECIES_CARKOL },
    { .lvl = 34, .species = SPECIES_GIGALITH },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route10Cave_BlackbeltXavier[] = {
    { .lvl = 33, .species = SPECIES_MONFERNO },
    { .lvl = 34, .species = SPECIES_GURDURR },
};

// #endregion

// #region Route 11 South
const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Ross[] = {
    { .lvl = 35, .species = SPECIES_KOFFING_G },
    { .lvl = 36, .species = SPECIES_KROKOROK }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Greta[] = {
    { .lvl = 34, .species = SPECIES_SNEASEL },
    { .lvl = 35, .species = SPECIES_ZUBAT },
    { .lvl = 35, .species = SPECIES_GOLBAT },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Nellie[] = {
    { .lvl = 33, .species = SPECIES_ZUBAT },
    { .lvl = 33, .species = SPECIES_SANDILE },
    { .lvl = 34, .species = SPECIES_KOFFING_G },
    { .lvl = 35, .species = SPECIES_SNEASEL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Helga[] = {
    { .lvl = 36, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 37, .species = SPECIES_WEEZING_G },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Kareem[] = {
    { .lvl = 35, .species = SPECIES_WHIRLIPEDE },
    { .lvl = 35, .species = SPECIES_CROAGUNK },
    { .lvl = 37, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPluto_Chung[] = {
    { .lvl = 37, .species = SPECIES_SCRAGGY },
    { .lvl = 37, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Lass_Tabitha[] = {
    { .lvl = 35, .species = SPECIES_AMAURA },
    { .lvl = 36, .species = SPECIES_STOUTLAND },
    { .lvl = 36, .species = SPECIES_VESPIQUEN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_CrushGirl_Alisa[] = {
    { .lvl = 38, .species = SPECIES_SIRFETCHD },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Engineer_Dale[] = {
    { .lvl = 37, .species = SPECIES_PINCURCHIN },
    { .lvl = 37, .species = SPECIES_EMOLGA },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_Collector_Orville[] = {
    { .lvl = 37, .species = SPECIES_LILEEP },
    { .lvl = 37, .species = SPECIES_SLIGGOO },
    { .lvl = 37, .species = SPECIES_LAPRAS },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoClancy[] = {
    { .lvl = 37, .species = SPECIES_THIEVUL },
    { .lvl = 37, .species = SPECIES_TOXICROAK },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11South_TeamPlutoEna[] = {
    { .lvl = 38, .species = SPECIES_GOLBAT },
    { .lvl = 38, .species = SPECIES_SCOLIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_Route11South_TeamPlutoAdminRonald[] = {
    {
        .lvl = 37,
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
        .lvl = 37,
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
        .lvl = 38,
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
        .lvl = 39,
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
    { .lvl = 39, .species = SPECIES_GIGALITH }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_ScientistHarvey[] = {
    { .lvl = 36, .species = SPECIES_BERGMITE },
    { .lvl = 36, .species = SPECIES_LILEEP },
    { .lvl = 37, .species = SPECIES_CACTURNE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_PsychicKimiko[] = {
    { .lvl = 44, .species = SPECIES_HATTREM },
    { .lvl = 44, .species = SPECIES_MORPEKO },
    { .lvl = 46, .species = SPECIES_MANDIBUZZ }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CoolTrainerColt[] = {
    { .lvl = 46, .species = SPECIES_GLALIE },
    { .lvl = 46, .species = SPECIES_TOUCANNON },
    { .lvl = 48, .species = SPECIES_MAMOSWINE }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_BlackbeltHaytham[] = {
    { .lvl = 37, .species = SPECIES_CRABRAWLER },
    { .lvl = 38, .species = SPECIES_BLAZIKEN }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_CollectorZeus[] = {
    { .lvl = 46, .species = SPECIES_COFAGRIGUS },
    { .lvl = 46, .species = SPECIES_RUNERIGUS }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_NurseMina[] = {
    { .lvl = 40, .species = SPECIES_HAPPINY },
    { .lvl = 42, .species = SPECIES_CHANSEY },
    { .lvl = 44, .species = SPECIES_BLISSEY }
};

const struct TrainerMonNoItemDefaultMoves sParty_HessonPass_GentlemanGordy[] = {
    { .lvl = 45, .species = SPECIES_BOLTUND },
    { .lvl = 46, .species = SPECIES_STOUTLAND }
};
// #endregion

// #region Route 11 North
const struct TrainerMonNoItemDefaultMoves sParty_Route11North_PainterIsobel[] = {
    { .lvl = 37, .species = SPECIES_IVYSAUR },
    { .lvl = 38, .species = SPECIES_GLACEON }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanClint[] = {
    { .lvl = 37, .species = SPECIES_HORSEA },
    { .lvl = 37, .species = SPECIES_WARTORTLE },
    { .lvl = 38, .species = SPECIES_GASTRODON_EAST }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ChanellerKatya[] = {
    { .lvl = 38, .species = SPECIES_SABLEYE },
    { .lvl = 40, .species = SPECIES_DUSKNOIR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_RockerNathaniel[] = {
    { .lvl = 38, .species = SPECIES_VIBRAVA },
    { .lvl = 38, .species = SPECIES_TOXTRICITY_LOW_KEY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_NinjaBoyYao[] = {
    { .lvl = 36, .species = SPECIES_CARVANHA },
    { .lvl = 36, .species = SPECIES_EMOLGA },
    { .lvl = 38, .species = SPECIES_MALAMAR }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_ParaoslLadyTina[] = {
    { .lvl = 36, .species = SPECIES_FLOETTE_ORANGE },
    { .lvl = 37, .species = SPECIES_BRAIXEN },
    { .lvl = 37, .species = SPECIES_RIBOMBEE }
};

const struct TrainerMonNoItemDefaultMoves sParty_Route11North_FishermanJonah[] = {
    { .lvl = 38, .species = SPECIES_MAGIKARP },
    { .lvl = 40, .species = SPECIES_GYARADOS }
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
        .lvl = 40,
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
        .lvl = 40,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 40,
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
        .lvl = 42,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 39,
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
        .lvl = 40,
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
        .lvl = 40,
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
        .lvl = 40,
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
        .lvl = 41,
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
        .lvl = 41,
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
        .lvl = 42,
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
        .lvl = 42,
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
        .lvl = 43,
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
    { .lvl = 40, .species = SPECIES_MIMIKYU },
    { .lvl = 40, .species = SPECIES_SLIGGOO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CollectorFernando[] = {
    { .lvl = 41, .species = SPECIES_DHELMISE },
    { .lvl = 41, .species = SPECIES_RAICHU_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BugCatcherLyle[] = {
   { .lvl = 39, .species = SPECIES_JOLTIK },
   { .lvl = 40, .species = SPECIES_SHIINOTIC },
   { .lvl = 40, .species = SPECIES_VIBRAVA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BeautyErica[] = {
    { .lvl = 42, .species = SPECIES_PRIMARINA },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_PainterSheena[] = {
    { .lvl = 40, .species = SPECIES_ESPEON },
    { .lvl = 40, .species = SPECIES_MORPEKO },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_CamperRupert[] = {
    { .lvl = 42, .species = SPECIES_VENUSAUR },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ScientistSean[] = {
    { .lvl = 41, .species = SPECIES_BEARTIC },
    { .lvl = 41, .species = SPECIES_BARBARACLE },
    { .lvl = 41, .species = SPECIES_KROKOROK },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RockerRaphael[] = {
    { .lvl = 42, .species = SPECIES_VIBRAVA },
    { .lvl = 42, .species = SPECIES_RILLABOOM },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_ChannelerRenee[] = {
    { .lvl = 39, .species = SPECIES_DUSKULL },
    { .lvl = 39, .species = SPECIES_SABLEYE },
    { .lvl = 40, .species = SPECIES_PHANTUMP },
    { .lvl = 40, .species = SPECIES_TREVENANT },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_BlackbeltBrad[] = {
    { .lvl = 41, .species = SPECIES_TIMBURR },
    { .lvl = 42, .species = SPECIES_HERACROSS },
};

const struct TrainerMonNoItemDefaultMoves sParty_PeradonForest_RuinManiacAlex[] = {
    { .lvl = 41, .species = SPECIES_VULLABY },
    { .lvl = 42, .species = SPECIES_RUNERIGUS },
    { .lvl = 43, .species = SPECIES_EXCADRILL },
};
// #endregion

// #region Route 12 & Scalding Spa
const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteJoanne[] = {
    { .lvl = 41, .species = SPECIES_PACHIRISU },
    { .lvl = 42, .species = SPECIES_HAKAMO_O },
    { .lvl = 42, .species = SPECIES_MAGCARGO },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_PsychicTony[] = {
    { .lvl = 42, .species = SPECIES_MR_MIME_G },
    { .lvl = 44, .species = SPECIES_MR_RIME },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_HikerDwight[] = {
    { .lvl = 41, .species = SPECIES_ROGGENROLA },
    { .lvl = 41, .species = SPECIES_DRILBUR },
    { .lvl = 42, .species = SPECIES_CARBINK },
    { .lvl = 44, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_TriathleteTrixie[] = {
    { .lvl = 43, .species = SPECIES_INCINEROAR },
    { .lvl = 43, .species = SPECIES_KANGASKHAN },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route12East_GentlemanGeoffrey[] = {
    { .lvl = 43, .species = SPECIES_STOUTLAND },
    { .lvl = 43, .species = SPECIES_BOLTUND },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_HikerEugene[] = {
    { .lvl = 45, .species = SPECIES_TORKOAL },
    { .lvl = 45, .species = SPECIES_COALOSSAL },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_SupernerdStephen[] = {
    { .lvl = 44, .species = SPECIES_HAKAMO_O },
    { .lvl = 46, .species = SPECIES_CURSOLA },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_JugglerJohan[] = {
    { .lvl = 43, .species = SPECIES_ROLYCOLY },
    { .lvl = 43, .species = SPECIES_SALAZZLE },
    { .lvl = 44, .species = SPECIES_TURTONATOR },
};

const struct TrainerMonNoItemDefaultMoves sParty_ScaldingSpa_BlackbeltKieran[] = {
    { .lvl = 46, .species = SPECIES_EMBOAR },
};

const struct TrainerMonItemCustomMoves sParty_ScaldingSpa_TeamPlutoYolena[] = {
    {
        .lvl = 44,
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
        .lvl = 44,
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
        .lvl = 44,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_Route1_YoungsterHarlan),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterHarlan}
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_Route2_CoolTrainerAndy),
        .party = {.NoItemDefaultMoves = sParty_Route2_CoolTrainerAndy}
    },
    // #endregion
    // #region Varisi Forest
    [TRAINER_VARISI_FOREST_BUG_CATCHER_KENDELL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_K, _e, _n, _d, _e, _l, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_VarisiForest_BugCatcherKendell),
        .party = {.NoItemDefaultMoves = sParty_VarisiForest_BugCatcherKendell}
    },
    [TRAINER_VARISI_FOREST_BUG_CATCHER_BRADEN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_B, _r, _a, _d, _e, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_Route3_PicknickerTana),
        .party = {.NoItemDefaultMoves = sParty_Route3_PicknickerTana}
    },
    [TRAINER_ROUTE_3_BUG_CATCHER_IRWIN] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = {_I, _r, _w, _i, _n, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_DOUBLE_BATTLE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_HP_AWARE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_TormaCave_Engineer_Shane),
        .party = {.NoItemDefaultMoves = sParty_TormaCave_Engineer_Shane}
    },
    [TRAINER_TORMA_CAVE_POKEFAN_COREY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_POKEFAN,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = {_C, _o, _r, _e, _y, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_HP_AWARE,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_DOUBLE_BATTLE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_HP_AWARE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_SuperNerdGlenn),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_SuperNerdGlenn}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_BURGLAR_PETER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BURGLAR,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = {_P, _e, _t, _e, _r, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_ForgottenManse_BF1_BurglarPeter),
        .party = {.NoItemDefaultMoves = sParty_ForgottenManse_BF1_BurglarPeter}
    },
    [TRAINER_FORGOTTEN_MANSE_BF1_PSYCHIC_NOELLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_PSYCHIC,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = {_N, _o, _e, _l, _l, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_DaimynFactory_EngineerJamison),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_EngineerJamison}
    },
    [TRAINER_DAIMYN_FACTORY_HIKER_MIKE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_M, _i, _k, _e, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_DaimynFactory_HikerMike),
        .party = {.NoItemDefaultMoves = sParty_DaimynFactory_HikerMike}
    },
    [TRAINER_DAIMYN_FACTORY_BLACKBELT_RORY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BLACK_BELT,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = {_R, _o, _r, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .trainerPic = TRAINER_PIC_POKRFAN_F,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
        .partySize = NELEMS(sParty_Route10_SwimmerDoug),
        .party = {.NoItemDefaultMoves = sParty_Route10_SwimmerDoug}
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
    [TRAINER_ROUTE_10_CAVE_HIKER_HARLEY] = {
        .partyFlags = 0,
        .trainerClass = CLASS_HIKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = {_H, _a, _r, _l, _e, _y, _END},
        .items = { },
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_HP_AWARE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_HP_AWARE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_PREFER_STRONGEST_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .trainerClass = CLASS_ROCKER,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_SETUP_FIRST_TURN | AI_SCRIPT_SEMI_SMART,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
        .partySize = NELEMS(sParty_PeradonForest_CollectorFernando),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_CollectorFernando}
    },
    [TRAINER_PERADON_FOREST_BUG_CATCHER_LYLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BUG_CATCHER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_PeradonForest_ScientistSean),
        .party = {.NoItemDefaultMoves = sParty_PeradonForest_ScientistSean}
    },
    [TRAINER_PERADON_FOREST_ROCKER_RAPHAEL] = {
        .partyFlags = 0,
        .trainerClass = CLASS_ROCKER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = {_R, _a, _p, _h, _a, _e, _l, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_PREFER_STRONGEST_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_HP_AWARE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
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
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_RISKY | AI_SCRIPT_TRY_TO_FAINT,
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
    // #endregion
    // #endregion
};
