.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route18_SwimmerJasper
EventScript_Route18_SwimmerJasper:
    trainerbattle0 0x0 314 0x0 gText_Route18_SwimmerJasper_Intro gText_Route18_SwimmerJasper_Defeat
    msgbox gText_Route18_SwimmerJasper_Chat MSG_NORMAL
    end

.global EventScript_Route18_TriathleteDeborah
EventScript_Route18_TriathleteDeborah:
    trainerbattle0 0x0 315 0x0 gText_Route18_TriathleteDeborah_Intro gText_Route18_TriathleteDeborah_Defeat
    msgbox gText_Route18_TriathleteDeborah_Chat MSG_NORMAL
    end

.global EventScript_Route18_SwimmerJudie
EventScript_Route18_SwimmerJudie:
    trainerbattle0 0x0 316 0x0 gText_Route18_SwimmerJudie_Intro gText_Route18_SwimmerJudie_Defeat
    msgbox gText_Route18_SwimmerJudie_Chat MSG_NORMAL
    end

.global EventScript_Route18_BirdKeeperKirk
EventScript_Route18_BirdKeeperKirk:
    trainerbattle0 0x0 317 0x0 gText_Route18_BirdKeeperKirk_Intro gText_Route18_BirdKeeperKirk_Defeat
    msgbox gText_Route18_BirdKeeperKirk_Chat MSG_NORMAL
    end

.global EventScript_Route18_LassEmma
EventScript_Route18_LassEmma:
    trainerbattle0 0x0 318 0x0 gText_Route18_LassEmma_Intro gText_Route18_LassEmma_Defeat
    msgbox gText_Route18_LassEmma_Chat MSG_NORMAL
    end

.global EventScript_Route18_BlackbeltRohan
EventScript_Route18_BlackbeltRohan:
    trainerbattle0 0x0 319 0x0 gText_Route18_BlackbeltRohan_Intro gText_Route18_BlackbeltRohan_Defeat
    msgbox gText_Route18_BlackbeltRohan_Chat MSG_NORMAL
    end

.global EventScript_Route18_TM31_BrickBreak
EventScript_Route18_TM31_BrickBreak:
    setvar CHOSEN_ITEM ITEM_TM31
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_TM99_DazzlingGleam
EventScript_Route18_TM99_DazzlingGleam:
    setvar CHOSEN_ITEM ITEM_TM99
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_Galladite
EventScript_Route18_Galladite:
    finditem ITEM_GALLADITE 0x1
    end

.global EventScript_Route18_Fisherman
EventScript_Route18_Fisherman:
    npcchatwithmovement gText_Route18_Fisherman m_LookDown
    end

.global SignScript_Route18_PreserveFlowersSign
SignScript_Route18_PreserveFlowersSign:
    msgbox gText_Route18_PreserveFlowersSign MSG_SIGN
    end

.global SignScript_Route18_OrichelleGarden
SignScript_Route18_OrichelleGarden:
    msgbox gText_Route18_OrichelleGardenSign MSG_SIGN
    end

