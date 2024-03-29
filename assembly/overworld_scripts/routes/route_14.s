.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route14_SwimmerIvan
EventScript_Route14_SwimmerIvan:
    trainerbattle0 0x0 333 0x0 gText_Route14_SwimmerIvan_Intro gText_Route14_SwimmerIvan_Defeat
    msgbox gText_Route14_SwimmerIvan_Chat MSG_NORMAL
    end

.global EventScript_Route14_HikerClifford
EventScript_Route14_HikerClifford:
    trainerbattle0 0x0 334 0x0 gText_Route14_HikerClifford_Intro gText_Route14_HikerClifford_Defeat
    msgbox gText_Route14_HikerClifford_Chat MSG_NORMAL
    end

.global EventScript_Route14_FishermanEsteban
EventScript_Route14_FishermanEsteban:
    trainerbattle0 0x0 335 0x0 gText_Route14_FishermanEsteban_Intro gText_Route14_FishermanEsteban_Defeat
    msgbox gText_Route14_FishermanEsteban_Chat MSG_NORMAL
    end

.global EventScript_Route14_FishermanTucker
EventScript_Route14_FishermanTucker:
    trainerbattle0 0x0 336 0x0 gText_Route14_FishermanTucker_Intro gText_Route14_FishermanTucker_Defeat
    msgbox gText_Route14_FishermanTucker_Chat MSG_NORMAL
    end

.global EventScript_Route14_SwimmerEleanor
EventScript_Route14_SwimmerEleanor:
    trainerbattle0 0x0 337 0x0 gText_Route14_SwimmerEleanor_Intro gText_Route14_SwimmerEleanor_Defeat
    msgbox gText_Route14_SwimmerEleanor_Chat MSG_NORMAL
    end

.global EventScript_Route14_BlackbeltJoaquin
EventScript_Route14_BlackbeltJoaquin:
    trainerbattle0 0x0 338 0x0 gText_Route14_BlackbeltJoaquin_Intro gText_Route14_BlackbeltJoaquin_Defeat
    msgbox gText_Route14_BlackbeltJoaquin_Chat MSG_NORMAL
    end

.global EventScript_Route14_SwimmerChris
EventScript_Route14_SwimmerChris:
    trainerbattle0 0x0 339 0x0 gText_Route14_SwimmerChris_Intro gText_Route14_SwimmerChris_Defeat
    msgbox gText_Route14_SwimmerChris_Chat MSG_NORMAL
    end

.global EventScript_Route14_YoungsterFreddie
EventScript_Route14_YoungsterFreddie:
    trainerbattle0 0x0 340 0x0 gText_Route14_YoungsterFreddie_Intro gText_Route14_YoungsterFreddie_Defeat
    msgbox gText_Route14_YoungsterFreddie_Chat MSG_NORMAL
    end

.global EventScript_Route14_PsychicTobin
EventScript_Route14_PsychicTobin:
    trainerbattle0 0x0 341 0x0 gText_Route14_PsychicTobin_Intro gText_Route14_PsychicTobin_Defeat
    msgbox gText_Route14_PsychicTobin_Chat MSG_NORMAL
    end

.global EventScript_Route14_SwimmerMacie
EventScript_Route14_SwimmerMacie:
    trainerbattle0 0x0 342 0x0 gText_Route14_SwimmerMacie_Intro gText_Route14_SwimmerMacie_Defeat
    msgbox gText_Route14_SwimmerMacie_Chat MSG_NORMAL
    end

.global EventScript_Route14_FindTM27Return
EventScript_Route14_FindTM27Return:
    setvar CHOSEN_ITEM ITEM_TM27
    call ItemScript_Common_FindTM
    end

.global SignScript_Route14_TrainerTipsFastSurfing
SignScript_Route14_TrainerTipsFastSurfing:
    msgbox gText_Route14_TrainerTipsFastSurfing MSG_SIGN
    end
