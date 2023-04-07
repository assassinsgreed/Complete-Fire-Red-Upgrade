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
    { .iv = 25, .lvl = 12, .species = SPECIES_ROOKIDEE },
    { .iv = 25, .lvl = 14, .species = SPECIES_EEVEE },
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
    { .lvl = 12, .species = SPECIES_NICKIT },
    { .lvl = 13, .species = SPECIES_CROAGUNK },
};

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoEna[] = {
    { .lvl = 12, .species = SPECIES_ZUBAT },
    { .lvl = 13, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemCustomMoves sParty_RubarrDesert_TeamPlutoAdminIrene[] = {
    {
        .lvl = 13,
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
        .lvl = 13,
        .species = SPECIES_SANDILE,
        .moves = {
            MOVE_SCARYFACE,
            MOVE_HONECLAWS,
            MOVE_POWERTRIP,
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
        .lvl = 20,
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
        .lvl = 20,
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
        .lvl = 22,
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

#define NO_NAME                                                                                      \
    {                                                                                                \
        _END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE \
    }

const struct Trainer gTrainers[] = {
    [TRAINER_NONE] = {
        .trainerName = NO_NAME,
    },
    // #region Important trainers
    [TRAINER_RIVAL1] = {
        .partyFlags = 0,
        .trainerClass = CLASS_RIVAL,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLUE,
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
        .trainerPic = TRAINER_PIC_BLUE,
        .trainerName = NO_NAME, // Name replaced from RIVAL trainer classes
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_TRY_TO_FAINT,
        .partySize = NELEMS(sParty_Rival2),
        .party = {.NoItemDefaultMoves = sParty_Rival2}
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
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
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
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
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
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
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
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
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
        .trainerClass = CLASS_PKMN_TRAINER_1,
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
        .trainerClass = CLASS_PKMN_TRAINER_1,
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
        .trainerClass = CLASS_PKMN_TRAINER_1,
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
        .trainerClass = CLASS_PKMN_TRAINER_1,
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
        .aiFlags = AI_SCRIPT_SEMI_SMART,
        .partySize = NELEMS(sParty_FerroxGym_GymLeaderStella),
        .party = {.ItemCustomMoves = sParty_FerroxGym_GymLeaderStella}
    },
};
