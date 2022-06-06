.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_Route1_YoungsterPeter
EventScript_Route1_YoungsterPeter:
    trainerbattle0 0x0 0x1 0x0 gText_Route1_YoungsterPeter_Intro gText_Route1_YoungsterPeter_Defeat
    msgbox gText_Route1_YoungsterPeter_Chat MSG_NORMAL
    end
