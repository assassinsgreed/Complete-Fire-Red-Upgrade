.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route1
MapScript_Route1:
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

HideTrapPokemon:
    checkflag 0xE00
    if SET _call HideSandygast
    end

HideSandygast:
    hidesprite 5
    return    

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
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    setflag 0xE00
    wildbattle SPECIES_SANDYGAST 0x5 0x0
    release
    end

.global ItemScript_Route1_FindTMEnergyBall
ItemScript_Route1_FindTMEnergyBall:
    setvar CHOSEN_ITEM ITEM_TM53
    call ItemScript_Common_FindTM
    end

.global EventScript_Route1_SwimmerRebecca
EventScript_Route1_SwimmerRebecca:
    trainerbattle0 0x0 320 0x0 gText_Route1_SwimmerRebecca_Intro gText_Route1_SwimmerRebecca_Defeat
    msgbox gText_Route1_SwimmerRebecca_Chat MSG_NORMAL
    end

.global EventScript_Route1_BurglarBryce
EventScript_Route1_BurglarBryce:
    trainerbattle0 0x0 321 0x0 gText_Route1_BurglarBryce_Intro gText_Route1_BurglarBryce_Defeat
    msgbox gText_Route1_BurglarBryce_Chat MSG_NORMAL
    end
