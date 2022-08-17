.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_VarisiForest_BugCatcherKendell
EventScript_VarisiForest_BugCatcherKendell:
    trainerbattle0 0x0 0x8 0x0 gText_VarisiForest_BugCatcherKendell_Intro gText_VarisiForest_BugCatcherKendell_Defeat
    msgbox gText_VarisiForest_BugCatcherKendell_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_BugCatcherBraden
EventScript_VarisiForest_BugCatcherBraden:
    trainerbattle0 0x0 0x9 0x0 gText_VarisiForest_BugCatcherBraden_Intro gText_VarisiForest_BugCatcherBraden_Defeat
    msgbox gText_VarisiForest_BugCatcherBraden_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_LassBreanna
EventScript_VarisiForest_LassBreanna:
    trainerbattle0 0x0 0xa 0x0 gText_VarisiForest_LassBreanna_Intro gText_VarisiForest_LassBreanna_Defeat
    msgbox gText_VarisiForest_LassBreanna_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_LassMimi
EventScript_VarisiForest_LassMimi:
    trainerbattle0 0x0 0xb 0x0 gText_VarisiForest_LassMimi_Intro gText_VarisiForest_LassMimi_Defeat
    msgbox gText_VarisiForest_LassMimi_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_TrainerTip
EventScript_VarisiForest_TrainerTip:
    npcchat gText_VarisiForest_TrainerTip
    end

.global EventScript_VarisiForest_PoisonWarning
EventScript_VarisiForest_PoisonWarning:
    lock
    faceplayer
    msgbox gText_VarisiForest_PoisonWarning MSG_NORMAL
    checkflag 0x230 @ Has received Antidote gift
    if NOT_SET _goto EventScript_VarisiForest_AntidoteGift
    goto EventScript_VarisiForest_PoisonWarningEnd

EventScript_VarisiForest_AntidoteGift:
    msgbox gText_VarisiForest_AntidoteGift MSG_NORMAL
    obtainitem ITEM_ANTIDOTE 0x1
    setflag 0x230 @ Has received Antidote gift
    goto EventScript_VarisiForest_PoisonWarningEnd
    
EventScript_VarisiForest_PoisonWarningEnd:
    applymovement 0x1 m_LookRight
	waitmovement ALLEVENTS
    release
    end

.global EventScript_VarisiForest_SurprisedTrainer
EventScript_VarisiForest_SurprisedTrainer:
    npcchat gText_VarisiForest_SurprisedTrainer
    end

.global EventScript_VarisiForest_TimeOfDay
EventScript_VarisiForest_TimeOfDay:
    npcchat2 0x1 m_LookRight gText_VarisiForest_TimeOfDay
    end

.global EventScript_VarisiForest_FriendlyTrainer
EventScript_VarisiForest_FriendlyTrainer:
    npcchat2 0x2 m_LookUp gText_VarisiForest_FriendlyTrainer
    end
