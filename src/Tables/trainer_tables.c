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
// #region Important
const struct TrainerMonNoItemDefaultMoves sParty_Rival1[] = {
    { .iv = 0, .lvl = 5, .species = SPECIES_EEVEE },
};
// #endregion

// #region Route 1 
const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterPeter[] = {
    { .iv = 0, .lvl = 4, .species = SPECIES_BIDOOF },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_LassHelena[] = {
    { .iv = 0, .lvl = 4, .species = SPECIES_FLETCHLING },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterHarlan[] = {
    { .iv = 0, .lvl = 4, .species = SPECIES_YAMPER },
};
// #endregion

// #region Route 2
const struct TrainerMonNoItemDefaultMoves sParty_Route2_YoungsterJoey[] = {
    { .iv = 0, .lvl = 7, .species = SPECIES_RATTATA_A },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassKimberly[] = {
    { .iv = 0, .lvl = 6, .species = SPECIES_RALTS },
    { .iv = 0, .lvl = 6, .species = SPECIES_CUTIEFLY },
};

const struct TrainerMonNoItemDefaultMoves sParty_Route2_LassRikki[] = {
    { .iv = 0, .lvl = 8, .species = SPECIES_FLABEBE_BLUE },
    { .iv = 0, .lvl = 8, .species = SPECIES_FLABEBE_YELLOW },
};
// #endregion

// #region Varisi Forest
const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherKendell[] = {
    { .iv = 0, .lvl = 6, .species = SPECIES_BLIPBUG },
    { .iv = 0, .lvl = 6, .species = SPECIES_BLIPBUG },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_BugCatcherBraden[] = {
    { .iv = 0, .lvl = 6, .species = SPECIES_BLIPBUG },
    { .iv = 0, .lvl = 6, .species = SPECIES_VENIPEDE },
    { .iv = 0, .lvl = 6, .species = SPECIES_VENIPEDE },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassBreanna[] = {
    { .iv = 0, .lvl = 7, .species = SPECIES_PICHU },
    { .iv = 0, .lvl = 7, .species = SPECIES_BUDEW },
};

const struct TrainerMonNoItemDefaultMoves sParty_VarisiForest_LassMimi[] = {
    { .iv = 0, .lvl = 6, .species = SPECIES_BUNEARY },
    { .iv = 0, .lvl = 7, .species = SPECIES_PIKIPEK },
    { .iv = 0, .lvl = 7, .species = SPECIES_SHROOMISH },
};
// #endregion

// #region Rhodanzi City
const struct TrainerMonNoItemCustomMoves sParty_RhodanziCity_Alonso[] = {
    {
        .iv = 10,
        .lvl = 10,
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
        .iv = 10,
        .lvl = 9,
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
        .iv = 10,
        .lvl = 12,
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
        .iv = 20,
        .lvl = 12,
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
        .iv = 20,
        .lvl = 14,
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

// #region Route 7
const struct TrainerMonNoItemDefaultMoves sParty_Route7_CamperCarlisle[] = {
    { .iv = 0, .lvl = 9, .species = SPECIES_NIDORAN_M },
    { .iv = 0, .lvl = 10, .species = SPECIES_DOTTLER },
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
