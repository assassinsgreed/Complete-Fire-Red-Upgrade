.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ OpenChamberTop, 0x2D9
.equ OpenChamberBottom, 0x2E1

.global MapScript_UteyanRuins
MapScript_UteyanRuins:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_UteyanRuins_SetChamberDoorPassability
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_UteyanRuins_SetWorldMapFlag
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_UteyanRuins_SetChamberDoorPassability:
    checkflag 0x27A @ Top chamber
    if SET _call OpenTopChamber
    checkflag 0x27B @ Middle chamber
    if SET _call OpenMiddleChamber
    checkflag 0x27C @ Left chamber
    if SET _call OpenLeftChamber
    checkflag 0x27D @ Right chamber
    if SET _call OpenRightChamber
    checkflag 0x27E @ Bottom chamber
    if SET _call OpenBottomChamber
    end

MapEntryScript_UteyanRuins_SetWorldMapFlag:
    setworldmapflag 0x8B1 @ Been to Uteyan Ruins
    end

.global EventScript_UteyanRuins_TM04CalmMind
EventScript_UteyanRuins_TM04CalmMind:
    setvar CHOSEN_ITEM ITEM_TM04
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_RuinManiacKristian
EventScript_UteyanRuins_RuinManiacKristian:
    trainerbattle0 0x0 492 0x0 gText_UteyanRuins_RuinManiacKristian_Intro gText_UteyanRuins_RuinManiacKristian_Defeat
    msgbox gText_UteyanRuins_RuinManiacKristian_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_PsychicHaley
EventScript_UteyanRuins_PsychicHaley:
    trainerbattle0 0x0 493 0x0 gText_UteyanRuins_PsychicHaley_Intro gText_UteyanRuins_PsychicHaley_Defeat
    msgbox gText_UteyanRuins_PsychicHaley_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_RuinManiacCyril
EventScript_UteyanRuins_RuinManiacCyril:
    trainerbattle0 0x0 494 0x0 gText_UteyanRuins_RuinManiacCyril_Intro gText_UteyanRuins_RuinManiacCyril_Defeat
    msgbox gText_UteyanRuins_RuinManiacCyril_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_BrailleMan
EventScript_UteyanRuins_BrailleMan:
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if equal _goto BrailleMan_WithDecoder
    npcchat gText_UteyanRuins_BrailleMan
    setflag 0x279 @ Decoder is willing to talk about his device
    end

BrailleMan_WithDecoder:
    npcchat gText_UteyanRuins_BrailleMan_WithDecoder
    end

UteyanRuins_ChambersCommon_Decoding:
    playse 0x69 @ Dex Nav searching
    msgbox gText_UteyanRuins_ChamberCommon_Decoding MSG_NORMAL
    waitse
    playse 0x68 @ Dex Nav off
    waitse
    return

UtyeanRuins_ChambersCommon_DoorOpening:
    call TriggerDoorOpening
    applymovement PLAYER m_PlayerRunsFromChamberDoor
    waitstate
    playse 0x8 @ Door Open
    waitmovement PLAYER
    return

TriggerDoorOpening:
    applymovement PLAYER m_Surprise
    sound 0x15 @ Exclaim
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    setvar 0x8004 0x0 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x3 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x20 @ This controls how long the overall animation lasts
	setvar 0x8007 0x2 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    return

UtyeanRuins_ChambersCommon_ChamberHasBeenOpened:
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

.global SignScript_UteyanRuins_ChamberDoor_Bottom
SignScript_UteyanRuins_ChamberDoor_Bottom:
    checkflag 0x27E @ Bottom chamber solved
    if SET _goto UtyeanRuins_ChambersCommon_ChamberHasBeenOpened
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call ChamberDoor_Bottom
    if equal _call ChamberDoor_Bottom_Decoded
    @ Check for solved puzzle
    setvar 0x4000 0x0
    checkflag 0x2
    if SET _call AddBrokenRockToVar
    checkflag 0x3
    if SET _call AddBrokenRockToVar
    checkflag 0x4
    if SET _call AddBrokenRockToVar
    checkflag 0x5
    if SET _call AddBrokenRockToVar
    checkflag 0x6
    if SET _call AddBrokenRockToVar
    checkflag 0x7
    if SET _call AddBrokenRockToVar
    checkflag 0x8
    if SET _call AddBrokenRockToVar
    compare 0x4000 0x5
    if notequal _goto End
    @ Puzzle solved!
    setflag 0x27E @ Bottom chamber solved
    call UtyeanRuins_ChambersCommon_DoorOpening
    call OpenBottomChamber
    special 0x8E
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

ChamberDoor_Bottom:
    braillemsgbox gText_UteyanRuins_ChamberBottom_1
    braillemsgbox gText_UteyanRuins_ChamberBottom_2
    return

ChamberDoor_Bottom_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_ChamberBottomDecoded MSG_NORMAL
    return

AddBrokenRockToVar:
    addvar 0x4000 0x1
    return

OpenBottomChamber:
    setmaptile 0xB 0x24 OpenChamberTop 0x0
    setmaptile 0xB 0x25 OpenChamberBottom 0x0
    return

.global SignScript_UteyanRuins_ChamberDoor_Left
SignScript_UteyanRuins_ChamberDoor_Left:
    checkflag 0x27C @ Left chamber solved
    if SET _goto UtyeanRuins_ChambersCommon_ChamberHasBeenOpened
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call ChamberDoor_Left
    if equal _call ChamberDoor_Left_Decoded
    @ Check for solved puzzle
    special 0x9F @ Choose pokemon from party
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto End
    setvar 0x8003 0x0 @ Check from party; 0x8004 holds index
    special2 LASTRESULT 0x18 @ Get species from chosen index
    compare LASTRESULT SPECIES_SHEDINJA
    if notequal _goto End
    @ Puzzle solved!
    setflag 0x27C @ Left chamber solved
    call UtyeanRuins_ChambersCommon_DoorOpening
    call OpenLeftChamber
    special 0x8E
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

ChamberDoor_Left:
    braillemsgbox gText_UteyanRuins_ChamberLeft_1
    braillemsgbox gText_UteyanRuins_ChamberLeft_2
    braillemsgbox gText_UteyanRuins_ChamberLeft_3
    return

ChamberDoor_Left_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_ChamberLeftDecoded MSG_NORMAL
    return

OpenLeftChamber:
    setmaptile 0xC 0x16 OpenChamberTop 0x0
    setmaptile 0xC 0x17 OpenChamberBottom 0x0
    return

.global SignScript_UteyanRuins_ChamberDoor_Middle
SignScript_UteyanRuins_ChamberDoor_Middle:
    checkflag 0x27B @ Middle chamber solved
    if SET _goto UtyeanRuins_ChambersCommon_ChamberHasBeenOpened
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call ChamberDoor_Middle
    if equal _call ChamberDoor_Middle_Decoded
    end @ Solved puzzle happens in a different tile event

ChamberDoor_Middle:
    braillemsgbox gText_UteyanRuins_ChamberMiddle_1
    braillemsgbox gText_UteyanRuins_ChamberMiddle_2
    braillemsgbox gText_UteyanRuins_ChamberMiddle_3
    return

ChamberDoor_Middle_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_ChamberMiddleDecoded MSG_NORMAL
    return

OpenMiddleChamber:
    setmaptile 0x18 0x14 OpenChamberTop 0x0
    setmaptile 0x18 0x15 OpenChamberBottom 0x0
    return

.global SignScript_UteyanRuins_ChamberMiddle_SolutionTile
SignScript_UteyanRuins_ChamberMiddle_SolutionTile:
    checkflag 0x27B
    if SET _goto End
    setflag 0x27B @ Middle chamber solved
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    call TriggerDoorOpening
    waitstate
    playse 0x8 @ Door Open
    call OpenMiddleChamber
    special 0x8E
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

.global SignScript_UteyanRuins_ChamberDoor_Right
SignScript_UteyanRuins_ChamberDoor_Right:
    checkflag 0x27D @ Right chamber solved
    if SET _goto UtyeanRuins_ChambersCommon_ChamberHasBeenOpened
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call ChamberDoor_Right
    if equal _call ChamberDoor_Right_Decoded
    @ Check for solved puzzle (Remember: 0x8004 needs to be set to the Person Event Number)
    setvar 0x8004 15 @ Boulder 1
    callasm CalculateEventPosition
    comparevartovalue 0x4002 0x35
    if notequal _goto End
    setvar 0x8004 16 @ Boulder 2
    callasm CalculateEventPosition
    compare 0x4002 0x35
    if notequal _goto End
    setvar 0x8004 17 @ Boulder 3
    callasm CalculateEventPosition
    compare 0x4002 0x35
    if notequal _goto End
    setvar 0x8004 18 @ Boulder 4
    callasm CalculateEventPosition
    compare 0x4002 0x35
    if notequal _goto End
    setvar 0x8004 19 @ Boulder 5
    callasm CalculateEventPosition
    compare 0x4002 0x35
    if notequal _goto End
    @ Puzzle solved!
    setflag 0x27D @ Right chamber solved
    call UtyeanRuins_ChambersCommon_DoorOpening
    call OpenRightChamber
    special 0x8E
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

ChamberDoor_Right:
    braillemsgbox gText_UteyanRuins_ChamberRight_1
    braillemsgbox gText_UteyanRuins_ChamberRight_2
    braillemsgbox gText_UteyanRuins_ChamberRight_3
    braillemsgbox gText_UteyanRuins_ChamberRight_4
    return

ChamberDoor_Right_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_ChamberRightDecoded MSG_NORMAL
    return

OpenRightChamber:
    setmaptile 0x2E 0x1A OpenChamberTop 0x0
    setmaptile 0x2E 0x1B OpenChamberBottom 0x0
    return

.global SignScript_UteyanRuins_ChamberDoor_Top
SignScript_UteyanRuins_ChamberDoor_Top:
    checkflag 0x27A @ Top chamber solved
    if SET _goto UtyeanRuins_ChambersCommon_ChamberHasBeenOpened
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call ChamberDoor_Top
    if equal _call ChamberDoor_Top_Decoded
    @ Check for solved puzzle
    compare 0x40A9 0x4
    if notequal _goto End
    @ Puzzle solved!
    setflag 0x27A @ Top chamber solved
    call UtyeanRuins_ChambersCommon_DoorOpening
    call OpenTopChamber
    special 0x8E
    msgbox gText_UteyanRuins_ChamberCommon_ChamberOpened MSG_NORMAL
    end

ChamberDoor_Top:
    braillemsgbox gText_UteyanRuins_ChamberTop_1
    braillemsgbox gText_UteyanRuins_ChamberTop_2
    braillemsgbox gText_UteyanRuins_ChamberTop_3
    braillemsgbox gText_UteyanRuins_ChamberTop_4
    return

ChamberDoor_Top_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_ChamberTopDecoded MSG_NORMAL
    return

OpenTopChamber:
    setmaptile 0x20 0x7 OpenChamberTop 0x0
    setmaptile 0x20 0x8 OpenChamberBottom 0x0
    return

ResetHistory:
    setvar 0x40A9 0x0
    end

.global SignScript_UteyanRuins_History1
SignScript_UteyanRuins_History1:
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call History1
    if equal _call History1_Decoded
    setvar 0x40A9 0x1 @ First history read
    end

History1:
    braillemsgbox gText_UteyanRuins_History_First_1
    braillemsgbox gText_UteyanRuins_History_First_2
    braillemsgbox gText_UteyanRuins_History_First_3
    return

History1_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_History_First_Decoded MSG_NORMAL
    return

.global SignScript_UteyanRuins_History2
SignScript_UteyanRuins_History2:
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call History2
    if equal _call History2_Decoded
    compare 0x40A9 0x1
    if notequal _goto ResetHistory @ Player read out of order
    addvar 0x40A9 0x1 @ Second history read
    end

History2:
    braillemsgbox gText_UteyanRuins_History_Second_1
    braillemsgbox gText_UteyanRuins_History_Second_2
    braillemsgbox gText_UteyanRuins_History_Second_3
    return

History2_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_History_Second_Decoded MSG_NORMAL
    return

.global SignScript_UteyanRuins_History3
SignScript_UteyanRuins_History3:
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call History3
    if equal _call History3_Decoded
    compare 0x40A9 0x2
    if notequal _goto ResetHistory @ Player read out of order
    addvar 0x40A9 0x1 @ Third history read
    end

History3:
    braillemsgbox gText_UteyanRuins_History_Third_1
    braillemsgbox gText_UteyanRuins_History_Third_2
    braillemsgbox gText_UteyanRuins_History_Third_3
    return

History3_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_History_Third_Decoded MSG_NORMAL
    return

.global SignScript_UteyanRuins_History4
SignScript_UteyanRuins_History4:
    checkitem ITEM_DECODER 0x1
    compare LASTRESULT TRUE
    if notequal _call History4
    if equal _call History4_Decoded
    compare 0x40A9 0x3
    if notequal _goto ResetHistory @ Player read out of order
    addvar 0x40A9 0x1 @ Fourth history read
    end

History4:
    braillemsgbox gText_UteyanRuins_History_Fourth_1
    braillemsgbox gText_UteyanRuins_History_Fourth_2
    braillemsgbox gText_UteyanRuins_History_Fourth_3
    return

History4_Decoded:
    call UteyanRuins_ChambersCommon_Decoding
    msgbox gText_UteyanRuins_History_Fourth_Decoded MSG_NORMAL
    return

.global EventScript_UteyanRuins_PuzzleGirl
EventScript_UteyanRuins_PuzzleGirl:
    npcchat gText_UteyanRuins_PuzzleGirl
    end

.global EventScript_UteyanRuins_TM29Psychic
EventScript_UteyanRuins_TM29Psychic:
    setvar CHOSEN_ITEM ITEM_TM29
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_HM06RockClimb
EventScript_UteyanRuins_HM06RockClimb:
    setvar CHOSEN_ITEM ITEM_HM06
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_SuperNerdMorty
EventScript_UteyanRuins_SuperNerdMorty:
    trainerbattle0 0x0 495 0x0 gText_UteyanRuins_SuperNerdMorty_Intro gText_UteyanRuins_SuperNerdMorty_Defeat
    msgbox gText_UteyanRuins_SuperNerdMorty_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_ChannelerAgatha
EventScript_UteyanRuins_ChannelerAgatha:
    trainerbattle0 0x0 496 0x0 gText_UteyanRuins_ChannelerAgatha_Intro gText_UteyanRuins_ChannelerAgatha_Defeat
    msgbox gText_UteyanRuins_ChannelerAgatha_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_LassDorothy
EventScript_UteyanRuins_LassDorothy:
    trainerbattle0 0x0 497 0x0 gText_UteyanRuins_LassDorothy_Intro gText_UteyanRuins_LassDorothy_Defeat
    msgbox gText_UteyanRuins_LassDorothy_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_Gardevoirite
EventScript_UteyanRuins_Gardevoirite:
    finditem ITEM_GARDEVOIRITE 0x1
    end

.global EventScript_UteyanRuins_SacredAsh
EventScript_UteyanRuins_SacredAsh:
    finditem ITEM_SACRED_ASH 0x1
    end

.global EventScript_UteyanRuins_RedOrb
EventScript_UteyanRuins_RedOrb:
    finditem ITEM_RED_ORB 0x1
    end

.global EventScript_UteyanRuins_BlueOrb
EventScript_UteyanRuins_BlueOrb:
    finditem ITEM_BLUE_ORB 0x1
    end

m_PlayerRunsFromChamberDoor: .byte run_down, run_down, look_up, end_m
