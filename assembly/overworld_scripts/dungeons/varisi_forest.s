.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

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
