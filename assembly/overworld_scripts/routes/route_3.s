.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global SignScript_Route3_TrainerTips
SignScript_Route3_TrainerTips:
    msgbox gText_Route3_TrainerTips MSG_SIGN
    end

.global SignScript_Route3_Navigation
SignScript_Route3_Navigation:
    msgbox gText_Route3_Navigation MSG_SIGN
    end

.global EventScript_Route3_FindTMTaunt
EventScript_Route3_FindTMTaunt:
    setvar CHOSEN_ITEM ITEM_TM12
    call ItemScript_Common_FindTM
    end

.global EventScript_Route3_PicknickerTana
EventScript_Route3_PicknickerTana:
    trainerbattle0 0x0 0x11 0x0 gText_Route3_PicknickerTana_Intro gText_Route3_PicknickerTana_Defeat
    msgbox gText_Route3_PicknickerTana_Chat MSG_NORMAL
    end

.global EventScript_Route3_BugCatcherIrwin
EventScript_Route3_BugCatcherIrwin:
    trainerbattle0 0x0 0x12 0x0 gText_Route3_BugCatcherIrwin_Intro gText_Route3_BugCatcherIrwin_Defeat
    msgbox gText_Route3_BugCatcherIrwin_Chat MSG_NORMAL
    end

.global EventScript_Route3_YoungsterLogan
EventScript_Route3_YoungsterLogan:
    trainerbattle0 0x0 0x13 0x0 gText_Route3_YoungsterLogan_Intro gText_Route3_YoungsterLogan_Defeat
    msgbox gText_Route3_YoungsterLogan_Chat MSG_NORMAL
    end

.global EventScript_Route3_TwinsNinaAndMeg_Nina
EventScript_Route3_TwinsNinaAndMeg_Nina:
    checktrainerflag 0x513 @ 500 + 13
    if SET _goto NinaDefeated
    trainerbattle0 0x0 0x14 0x0 gText_Route3_TwinsNinaAndMeg_Nina_Intro gText_Route3_TwinsNinaAndMeg_Nina_Defeat
    settrainerflag 0x513
    goto NinaDefeated

NinaDefeated:
    msgbox gText_Route3_TwinsNinaAndMeg_Nina_Chat MSG_NORMAL
    end

.global EventScript_Route3_TwinsNinaAndMeg_Meg
EventScript_Route3_TwinsNinaAndMeg_Meg:
    checktrainerflag 0x513 @ 500 + 13
    if SET _goto MegDefeated
    trainerbattle0 0x0 0x14 0x0 gText_Route3_TwinsNinaAndMeg_Meg_Intro gText_Route3_TwinsNinaAndMeg_Meg_Defeat
    settrainerflag 0x513
    goto MegDefeated

MegDefeated:
    msgbox gText_Route3_TwinsNinaAndMeg_Meg_Chat MSG_NORMAL
    end

.global EventScript_Route3_NinjaBoyBotan
EventScript_Route3_NinjaBoyBotan:
    trainerbattle0 0x0 0x15 0x0 gText_Route3_NinjaBoyBotan_Intro gText_Route3_NinjaBoyBotan_Defeat
    msgbox gText_Route3_NinjaBoyBotan_Chat MSG_NORMAL
    end

.global EventScript_Route3_RockerJude
EventScript_Route3_RockerJude:
    trainerbattle0 0x0 0x16 0x0 gText_Route3_RockerJude_Intro gText_Route3_RockerJude_Defeat
    msgbox gText_Route3_RockerJude_Chat MSG_NORMAL
    end
