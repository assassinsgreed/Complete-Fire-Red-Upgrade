.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route16_SwimmerMGale
EventScript_Route16_SwimmerMGale:
    trainerbattle0 0x0 322 0x0 gText_Route16_SwimmerGale_Intro gText_Route16_SwimmerGale_Defeat
    msgbox gText_Route16_SwimmerGale_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFAmy
EventScript_Route16_SwimmerFAmy:
    trainerbattle0 0x0 323 0x0 gText_Route16_SwimmerAmy_Intro gText_Route16_SwimmerAmy_Defeat
    msgbox gText_Route16_SwimmerAmy_Chat MSG_NORMAL
    end

.global EventScript_Route16_BirdKeeperTrevor
EventScript_Route16_BirdKeeperTrevor:
    trainerbattle0 0x0 324 0x0 gText_Route16_BirdKeeperTrevor_Intro gText_Route16_BirdKeeperTrevor_Defeat
    msgbox gText_Route16_BirdKeeperTrevor_Chat MSG_NORMAL
    end

.global EventScript_Route16_LadyMaria
EventScript_Route16_LadyMaria:
    trainerbattle0 0x0 325 0x0 gText_Route16_LadyMaria_Intro gText_Route16_LadyMaria_Defeat
    msgbox gText_Route16_LadyMaria_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFChristina
EventScript_Route16_SwimmerFChristina:
    trainerbattle0 0x0 326 0x0 gText_Route16_SwimmerChristina_Intro gText_Route16_SwimmerChristina_Defeat
    msgbox gText_Route16_SwimmerChristina_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerMPhillip
EventScript_Route16_SwimmerMPhillip:
    trainerbattle0 0x0 327 0x0 gText_Route16_SwimmerPhillip_Intro gText_Route16_SwimmerPhillip_Defeat
    msgbox gText_Route16_SwimmerPhillip_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerMLester
EventScript_Route16_SwimmerMLester:
    trainerbattle0 0x0 328 0x0 gText_Route16_SwimmerLester_Intro gText_Route16_SwimmerLester_Defeat
    msgbox gText_Route16_SwimmerLester_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFWendy
EventScript_Route16_SwimmerFWendy:
    trainerbattle0 0x0 329 0x0 gText_Route16_SwimmerWendy_Intro gText_Route16_SwimmerWendy_Defeat
    msgbox gText_Route16_SwimmerWendy_Chat MSG_NORMAL
    end

.global EventScript_Route16_TuberCody
EventScript_Route16_TuberCody:
    trainerbattle0 0x0 330 0x0 gText_Route16_TuberCody_Intro gText_Route16_TuberCody_Defeat
    msgbox gText_Route16_TuberCody_Chat MSG_NORMAL
    end

.global EventScript_Route16_TuberLeslie
EventScript_Route16_TuberLeslie:
    trainerbattle0 0x0 331 0x0 gText_Route16_TuberLeslie_Intro gText_Route16_TuberLeslie_Defeat
    msgbox gText_Route16_TuberLeslie_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFClementine
EventScript_Route16_SwimmerFClementine:
    trainerbattle0 0x0 332 0x0 gText_Route16_SwimmerClementine_Intro gText_Route16_SwimmerClementine_Defeat
    msgbox gText_Route16_SwimmerClementine_Chat MSG_NORMAL
    end

.global EventScript_Route16_Sharpedonite
EventScript_Route16_Sharpedonite:
    finditem ITEM_SHARPEDONITE 0x1
    end
