.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global SignScript_Route17_CaveSign
SignScript_Route17_CaveSign:
    msgbox gText_Route17_CaveSign MSG_SIGN
    end

.global EventScript_Route17_Rival1
EventScript_Route17_Rival1:
    // TODO: Fill out
    @ trainerbattle0 0x0 0x1 0x0 gText_Route1_YoungsterPeter_Intro gText_Route1_YoungsterPeter_Defeat
    end
