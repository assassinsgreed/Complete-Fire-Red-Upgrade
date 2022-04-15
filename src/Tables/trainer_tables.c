#include "../defines_battle.h"
#include "../../include/battle.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/opponents.h"
#include "../../include/constants/battle_ai.h"
#include "../../include/easy_text.h"

// See battle.h for a list of struct types that can be used
const struct TrainerMonNoItemDefaultMoves sParty_Route1_YoungsterPeter[] = {
    {
        .iv = 0,
        .lvl = 3,
        .species = SPECIES_BIDOOF,
    },
};

#define NO_NAME {_END, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE}


const struct Trainer gTrainers[] = {
    [TRAINER_NONE] = {
        .trainerName = NO_NAME,
    },
    [TRAINER_ROUTE_1_YOUNGSTER_PETER] = {
        .partyFlags = 0,
        .trainerClass = CLASS_YOUNGSTER,
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = {_P, _e, _t, _e, _r, _END},
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE,
        .partySize = NELEMS(sParty_Route1_YoungsterPeter),
        .party = {.NoItemDefaultMoves = sParty_Route1_YoungsterPeter}
    },
};