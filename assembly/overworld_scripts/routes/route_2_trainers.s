.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_Route2_YoungsterJoey
EventScript_Route2_YoungsterJoey:
    trainerbattle0 0x0 0x5 0x0 gText_Route2_YoungsterJoey_Intro gText_Route2_YoungsterJoey_Defeat
    msgbox gText_Route2_YoungsterJoey_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassKimberly
EventScript_Route2_LassKimberly:
    trainerbattle0 0x0 0x6 0x0 gText_Route2_LassKimberly_Intro gText_Route2_LassKimberly_Defeat
    msgbox gText_Route2_LassKimberly_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassRikki
EventScript_Route2_LassRikki:
    trainerbattle0 0x0 0x7 0x0 gText_Route2_LassRikki_Intro gText_Route2_LassRikki_Defeat
    msgbox gText_Route2_LassRikki_Chat MSG_NORMAL
    end
