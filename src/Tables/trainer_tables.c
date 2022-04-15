#include "../defines_battle.h"
#include "../../include/battle.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/opponents.h"
#include "../../include/constants/battle_ai.h"
#include "../../include/easy_text.h"

const struct TrainerMonNoItemDefaultMoves sParty_RivalLabFire[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_TORCHIC,
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_RivalLabGrass[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_TREECKO,
    },
};

const struct TrainerMonNoItemDefaultMoves sParty_RivalLabWater[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_MUDKIP,
    },
};

#define NO_NAME {_END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE}
#define RIVAL_NAME {_G, _a, _r, _y, _END}


const struct Trainer gTrainers[] = {
    [TRAINER_NONE] = {
        .trainerName = NO_NAME,
    },
    [TRAINER_RIVAL_OAKS_LAB_CHARMANDER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BLUE,
        .trainerName = RIVAL_NAME,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_RivalLabFire),
        .party = {.NoItemDefaultMoves = sParty_RivalLabFire}
    },
    [TRAINER_RIVAL_OAKS_LAB_BULBASAUR] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BLUE,
        .trainerName = RIVAL_NAME,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_RivalLabGrass),
        .party = {.NoItemDefaultMoves = sParty_RivalLabGrass}
    },
    [TRAINER_RIVAL_OAKS_LAB_SQUIRTLE] = {
        .partyFlags = 0,
        .trainerClass = CLASS_BEAUTY,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_BLUE,
        .trainerName = RIVAL_NAME,
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_RivalLabWater),
        .party = {.NoItemDefaultMoves = sParty_RivalLabWater}
    }
};