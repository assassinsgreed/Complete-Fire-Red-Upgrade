.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route13
MapScript_Route13:
    mapscript MAP_SCRIPT_ON_LOAD Route13_HandleGruntVisibility
    .byte MAP_SCRIPT_TERMIN

Route13_HandleGruntVisibility:
    checkflag 0x826 @ Has Tsarvosa City gym badge
    if SET _goto MoveGruntsIntoPosition
    end

MoveGruntsIntoPosition:
    movesprite2 26 0x47 0x15
    movesprite2 27 0x48 0x15
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

.global EventScript_Route13_Hiker_Left
EventScript_Route13_Hiker_Left:
    msgbox gText_Route13_HikerLeft MSG_NORMAL
    faceplayer
    npcchatwithmovement gText_Route13_HikerCommon m_LookRight
    end

.global EventScript_Route13_Hiker_Right
EventScript_Route13_Hiker_Right:
    msgbox gText_Route13_HikerRight MSG_NORMAL
    faceplayer
    npcchatwithmovement gText_Route13_HikerCommon m_LookLeft
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
    npcchatwithmovement gText_Route13_RestHouse_PCGuy m_LookDown
    end

.global EventScript_Route13_RestHouse_Hiker
EventScript_Route13_RestHouse_Hiker:
    npcchatwithmovement gText_Route13_RestHouse_Hiker m_LookLeft
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

.align 1
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
    call PlayerHealNurse
    msgbox gText_Route13_RestHouse_NurseHealed MSG_NORMAL
    applymovement 0x4 m_LookDown
    end

.global EventScript_Route13_RestHouse_GuestBookGirl
EventScript_Route13_RestHouse_GuestBookGirl:
    npcchatwithmovement gText_Route13_RestHouse_GuestBookGirl m_LookUp
    end

.global EventScript_Route13_RestHouse_RestHouseRep
EventScript_Route13_RestHouse_RestHouseRep:
    npcchatwithmovement gText_Route13_RestHouse_RestHouseRep m_LookLeft
    end

@@@@@@@@@@ Route 13 Cave @@@@@@@@@@
.global MapScript_Route13Cave
MapScript_Route13Cave:
    mapscript MAP_SCRIPT_ON_RESUME Route13Cave_SetupBreakableIce
    mapscript MAP_SCRIPT_ON_LOAD Route13Cave_SetupBreakableFloorsInIceRoom
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route13Cave
    .byte MAP_SCRIPT_TERMIN

Route13Cave_SetupBreakableIce:
    cmda6 0x4 @ Taken from XSE load of Vanilla FR scripts
    end

Route13Cave_SetupBreakableFloorsInIceRoom:
    special 0x135 @ Setup cracked ice floors
    end

LevelScripts_Route13Cave:
    levelscript 0x4001 0x1 LevelScript_HandleBreakableIce
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_HandleBreakableIce:
    lockall
    pause DELAY_HALFSECOND
    applymovement PLAYER m_HideSprite
    waitmovement ALLEVENTS
    sound 0x25 @ Fall
    pause DELAY_1SECOND
    warphole 2 61
    waitstate
    releaseall
    end

.global EventScript_Route13Cave_TM65ShadowClaw
EventScript_Route13Cave_TM65ShadowClaw:
    setvar CHOSEN_ITEM ITEM_TM65
    call ItemScript_Common_FindTM
    end
