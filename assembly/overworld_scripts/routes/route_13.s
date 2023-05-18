.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route13_CharizarditeY
EventScript_Route13_CharizarditeY:
    finditem ITEM_CHARIZARDITE_Y 0x1
    end

.global EventScript_Route13_FindTM39RockTomb
EventScript_Route13_FindTM39RockTomb:
    setvar CHOSEN_ITEM ITEM_TM39
    call ItemScript_Common_FindTM
    end

.global SignScript_Route13_RestHouse
SignScript_Route13_RestHouse:
    msgbox gText_Route13_RestHouse MSG_SIGN
    end

.global SignScript_Route13_TrainerTips
SignScript_Route13_TrainerTips:
    msgbox gText_Route13_TrainerTips MSG_SIGN
    end

.global EventScript_Route13_GamblerDalton
EventScript_Route13_GamblerDalton:
    trainerbattle0 0x0 0x34 0x0 gText_Route13_GamblerDalton_Intro gText_Route13_GamblerDalton_Defeat
    msgbox gText_Route13_GamblerDalton_Chat MSG_NORMAL
    end

.global EventScript_Route13_CollectorCharlie
EventScript_Route13_CollectorCharlie:
    trainerbattle0 0x0 0x35 0x0 gText_Route13_CollectorCharlie_Intro gText_Route13_CollectorCharlie_Defeat
    msgbox gText_Route13_CollectorCharlie_Chat MSG_NORMAL
    end

.global EventScript_Route13_HikerDwayne
EventScript_Route13_HikerDwayne:
    trainerbattle0 0x0 0x36 0x0 gText_Route13_HikerDwayne_Intro gText_Route13_HikerDwayne_Defeat
    msgbox gText_Route13_HikerDwayne_Chat MSG_NORMAL
    end

.global EventScript_Route13_BlackBeltHector
EventScript_Route13_BlackBeltHector:
    trainerbattle0 0x0 0x37 0x0 gText_Route13_BlackBeltHector_Intro gText_Route13_BlackBeltHector_Defeat
    msgbox gText_Route13_BlackBeltHector_Chat MSG_NORMAL
    end

.global EventScript_Route13_CamperEtie
EventScript_Route13_CamperEtie:
    trainerbattle0 0x0 0x38 0x0 gText_Route13_CamperEtie_Intro gText_Route13_CamperEtie_Defeat
    msgbox gText_Route13_CamperEtie_Chat MSG_NORMAL
    end

.global EventScript_Route13_BeautyCandice
EventScript_Route13_BeautyCandice:
    trainerbattle0 0x0 0x39 0x0 gText_Route13_BeautyCandice_Intro gText_Route13_BeautyCandice_Defeat
    msgbox gText_Route13_BeautyCandice_Chat MSG_NORMAL
    end

.global EventScript_Route13_GamblerOwain
EventScript_Route13_GamblerOwain:
    trainerbattle0 0x0 0x3A 0x0 gText_Route13_GamblerOwain_Intro gText_Route13_GamblerOwain_Defeat
    msgbox gText_Route13_GamblerOwain_Chat MSG_NORMAL
    end

.global EventScript_Route13_CollectorBenji
EventScript_Route13_CollectorBenji:
    trainerbattle0 0x0 0x3B 0x0 gText_Route13_CollectorBenji_Intro gText_Route13_CollectorBenji_Defeat
    msgbox gText_Route13_CollectorBenji_Chat MSG_NORMAL
    end

@@@@@@@@@@ Route 13 Rest House @@@@@@@@@@
.global MapScript_Route13_RestHouse
MapScript_Route13_RestHouse:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_Route13_RestHouse_FlightFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route13_RestHouse_FlightFlag:
    setworldmapflag 0x8A2
    end

.global EventScript_Route13_RestHouse_PCGuy
EventScript_Route13_RestHouse_PCGuy:
    npcchat2 0x1 m_LookDown gText_Route13_RestHouse_PCGuy
    end

.global EventScript_Route13_RestHouse_Hiker
EventScript_Route13_RestHouse_Hiker:
    npcchat2 0x2 m_LookLeft gText_Route13_RestHouse_Hiker
    end

.global EventScript_Route13_RestHouse_Merchant
EventScript_Route13_RestHouse_Merchant:
    faceplayer
    msgbox gText_Route13_RestHouse_Merchant MSG_YESNO
    compare LASTRESULT YES
    If equal _call MerchantShop
    msgbox gText_Route13_RestHouse_MerchantFarewell MSG_NORMAL
    applymovement 0x3 m_LookRight
    end

MerchantShop:
    msgbox gText_Route13_RestHouse_MerchantOpensShop MSG_KEEPOPEN
    pokemart RestHouseItems
    return

RestHouseItems:
    .hword ITEM_POKE_BALL
    .hword ITEM_FRESH_WATER
    .hword ITEM_FULL_HEAL
    .hword ITEM_REVIVE
    .hword ITEM_REPEL
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.global EventScript_Route13_RestHouse_Nurse
EventScript_Route13_RestHouse_Nurse:
    faceplayer
    msgbox gText_Route13_RestHouse_Nurse MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route13_RestHouse_NurseHealed MSG_NORMAL
    applymovement 0x4 m_LookDown
    end

.global EventScript_Route13_RestHouse_GuestBookGirl
EventScript_Route13_RestHouse_GuestBookGirl:
    npcchat2 0x5 m_LookUp gText_Route13_RestHouse_GuestBookGirl
    end

.global EventScript_Route13_RestHouse_RestHouseRep
EventScript_Route13_RestHouse_RestHouseRep:
    npcchat2 0x6 m_LookLeft gText_Route13_RestHouse_RestHouseRep
    end
