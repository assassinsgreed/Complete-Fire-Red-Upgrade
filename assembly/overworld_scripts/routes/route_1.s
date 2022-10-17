.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route1_YoungsterPeter
EventScript_Route1_YoungsterPeter:
    trainerbattle0 0x0 0x2 0x0 gText_Route1_YoungsterPeter_Intro gText_Route1_YoungsterPeter_Defeat
    msgbox gText_Route1_YoungsterPeter_Chat MSG_NORMAL
    end

.global EventScript_Route1_LassHelena
EventScript_Route1_LassHelena:
    trainerbattle0 0x0 0x3 0x0 gText_Route1_LassHelena_Intro gText_Route1_LassHelena_Defeat
    msgbox gText_Route1_LassHelena_Chat MSG_NORMAL
    end

.global EventScript_Route1_YoungsterHarlan
EventScript_Route1_YoungsterHarlan:
    trainerbattle0 0x0 0x4 0x0 gText_Route1_YoungsterHarlan_Intro gText_Route1_YoungsterHarlan_Defeat
    msgbox gText_Route1_YoungsterHarlan_Chat MSG_NORMAL
    end

.global EventScript_Route1_LonelyMan
EventScript_Route1_LonelyMan:
    msgbox gText_Route1_LonelyMan MSG_NORMAL
    end

.global EventScript_Route1_SandygastEncounter
EventScript_Route1_SandygastEncounter:
    lock
    checksound
    cry SPECIES_SANDYGAST 0x0
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    wildbattle SPECIES_SANDYGAST 0x5 0x0
    hidesprite LASTTALKED
    setflag 0x054
    release
    end
