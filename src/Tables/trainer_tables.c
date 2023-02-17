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
    { .lvl = 6, .species = SPECIES_RATTATA_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassKimberly[] = {
    { .lvl = 5, .species = SPECIES_RALTS },
    { .lvl = 5, .species = SPECIES_CUTIEFLY },
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
    { .lvl = 5, .species = SPECIES_BLIPBUG },
    { .lvl = 6, .species = SPECIES_BLIPBUG },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherBraden[] = {
    { .lvl = 4, .species = SPECIES_BLIPBUG },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
    { .lvl = 5, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassBreanna[] = {
    { .lvl = 6, .species = SPECIES_PICHU },
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
        .ability = ABILITY_SOUNDPROOF
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
        .ability = ABILITY_MIMICRY
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
        .ability = Ability_Hidden
    }
};

const struct TrainerMonItemCustomMoves sParty_RhodanziCity_LeaderTerrence[] = {
    {
        .lvl = 10,
        .species = SPECIES_GROOKEY,
        .moves = {
            MOVE_SCRATCH,
            MOVE_BRANCHPOKE,
            MOVE_NONE,
            MOVE_NONE
        },
        .heldItem = ITEM_TERRAIN_EXTENDER,
        .ability = Ability_Hidden
    },
    {
        .lvl = 12,
        .species = SPECIES_SKIDDO,
        .moves = {
            MOVE_LEECHSEED,
            MOVE_VINEWHIP,
            MOVE_TAILWHIP,
            MOVE_NONE
        },
        .ability = Ability_Hidden
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

const struct TrainerMonNoItemDefaultMoves sParty_RubarrDesert_TeamPlutoEna[] = {
    { .lvl = 13, .species = SPECIES_ZUBAT },
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
        .ability = ABILITY_STAKEOUT
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
        .ability = ABILITY_INTIMIDATE
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
        .ability = ABILITY_CORROSION
    },
};
// #endregion

// #region Route 7
const struct TrainerMonNoItemDefaultMoves sParty_Route7_CamperCarlisle[] = {
    { .lvl = 8, .species = SPECIES_NIDORAN_M },
    { .lvl = 10, .species = SPECIES_DOTTLER },
};
// endregion

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
        .trainerPic = TRAINER_PIC_BROCK,
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
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ENA] = {
        .partyFlags = 0,
        .trainerClass = CLASS_TEAM_PLUTO,
        .trainerPic = TRAINER_PIC_PLUTO_GRUNT_F,
        .trainerName = {_E, _n, _a, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .partySize = NELEMS(sParty_RubarrDesert_TeamPlutoEna),
        .party = {.NoItemDefaultMoves = sParty_RubarrDesert_TeamPlutoEna}
    },
    [TRAINER_RUBARR_DESERT_TEAM_PLUTO_ADMIN_IRENE] = {
        .partyFlags = 0,
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
};
