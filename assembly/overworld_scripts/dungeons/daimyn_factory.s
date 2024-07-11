.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

## Exterior
.global MapScript_DaimynFactoryOverworld
MapScript_DaimynFactoryOverworld:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_DaimynFactoryOverworld_SetDoorState
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_DaimynFactoryOverworld_SetDoorState:
    getplayerpos 0x4003 0x4004
    compare 0x4003 0x16 @ At factory door, horizontally
    if notequal _goto End
    compare 0x4004 0x7
    if notequal _goto End
    goto SetDoorOpen

SetDoorOpen:
    setmaptile 0x16 0x7 0x31A 0x0 @ set to open door sprite
    special 0x8E
    setvar 0x4001 0x1 @ Stop this event from firing again until the player revisits the map
    release
    end

.global EventScript_DaimynFactoryOverworld_BirdKeeperMarius
EventScript_DaimynFactoryOverworld_BirdKeeperMarius:
    trainerbattle0 0x0 0x89 0x0 gText_DaimynFactoryOverworld_BirdKeeperMarius_Intro gText_DaimynFactoryOverworld_BirdKeeperMarius_Defeat
    msgbox gText_DaimynFactoryOverworld_BirdKeeperMarius_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_RockerBenson
EventScript_DaimynFactoryOverworld_RockerBenson:
    trainerbattle0 0x0 0x8A 0x0 gText_DaimynFactoryOverworld_RockerBenson_Intro gText_DaimynFactoryOverworld_RockerBenson_Defeat
    msgbox gText_DaimynFactoryOverworld_RockerBenson_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_LassNatalie
EventScript_DaimynFactoryOverworld_LassNatalie:
    trainerbattle0 0x0 0x8B 0x0 gText_DaimynFactoryOverworld_LassNatalie_Intro gText_DaimynFactoryOverworld_LassNatalie_Defeat
    msgbox gText_DaimynFactoryOverworld_LassNatalie_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerJamison
EventScript_DaimynFactoryOverworld_EngineerJamison:
    trainerbattle0 0x0 0x8C 0x0 gText_DaimynFactoryOverworld_EngineerJamison_Intro gText_DaimynFactoryOverworld_EngineerJamison_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerJamison_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_HikerMike
EventScript_DaimynFactoryOverworld_HikerMike:
    trainerbattle0 0x0 0x8D 0x0 gText_DaimynFactoryOverworld_HikerMike_Intro gText_DaimynFactoryOverworld_HikerMike_Defeat
    msgbox gText_DaimynFactoryOverworld_HikerMike_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_BlackBeltRory
EventScript_DaimynFactoryOverworld_BlackBeltRory:
    trainerbattle0 0x0 0x8E 0x0 gText_DaimynFactoryOverworld_BlackbeltRory_Intro gText_DaimynFactoryOverworld_BlackbeltRory_Defeat
    msgbox gText_DaimynFactoryOverworld_BlackbeltRory_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerWilson
EventScript_DaimynFactoryOverworld_EngineerWilson:
    trainerbattle0 0x0 0x8F 0x0 gText_DaimynFactoryOverworld_EngineerWilson_Intro gText_DaimynFactoryOverworld_EngineerWilson_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerWilson_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_YoungsterNate
EventScript_DaimynFactoryOverworld_YoungsterNate:
    trainerbattle0 0x0 0x90 0x0 gText_DaimynFactoryOverworld_YoungsterNate_Intro gText_DaimynFactoryOverworld_YoungsterNate_Defeat
    msgbox gText_DaimynFactoryOverworld_YoungsterNate_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_PicknickerShanna
EventScript_DaimynFactoryOverworld_PicknickerShanna:
    trainerbattle0 0x0 0x91 0x0 gText_DaimynFactoryOverworld_PicknickerShanna_Intro gText_DaimynFactoryOverworld_PicknickerShanna_Defeat
    msgbox gText_DaimynFactoryOverworld_PicknickerShanna_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerKliff
EventScript_DaimynFactoryOverworld_EngineerKliff:
    trainerbattle0 0x0 0x92 0x0 gText_DaimynFactoryOverworld_EngineerKliff_Intro gText_DaimynFactoryOverworld_EngineerKliff_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerKliff_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_Lucarionite
EventScript_DaimynFactoryOverworld_Lucarionite:
    finditem ITEM_LUCARIONITE 0x1
    end

.global EventScript_DaimynFactoryOverworld_FindTM57_WildCharge
EventScript_DaimynFactoryOverworld_FindTM57_WildCharge:
    setvar CHOSEN_ITEM ITEM_TM57
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynFactoryOverworld_FindTM93_Wild_Charge
EventScript_DaimynFactoryOverworld_FindTM93_Wild_Charge:
    setvar CHOSEN_ITEM ITEM_TM93
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynFactoryOverworld_ReminiscingOldMan
EventScript_DaimynFactoryOverworld_ReminiscingOldMan:
    npcchat gText_DaimynFactoryOverworld_ReminiscingOldMan
    applymovement LASTTALKED m_LookUp
    end

.global EventScript_DaimynFactoryOverworld_StrongTrainersGirl
EventScript_DaimynFactoryOverworld_StrongTrainersGirl:
    npcchat gText_DaimynFactoryOverworld_StrongTrainersWarning
    end

.global SignScript_DaimynFactoryOverworld_EntranceSign
SignScript_DaimynFactoryOverworld_EntranceSign:
    msgbox gText_DaimynFactoryOverworld_EntranceSign MSG_SIGN
    end

.global SignScript_DaimynFactoryOverworld_TrainerTipsStats
SignScript_DaimynFactoryOverworld_TrainerTipsStats:
    msgbox gText_DaimynFactoryOverworld_TrainerTipsStats MSG_SIGN
    end

.global SignScript_DaimynFactoryOverworld_TrainerTipsDailyEvents
SignScript_DaimynFactoryOverworld_TrainerTipsDailyEvents:
    msgbox gText_DaimynFactoryOverworld_DailyEvents MSG_SIGN
    end

.global TileScript_DaimynFactoryOverworld_DaimynFactoryLocked
TileScript_DaimynFactoryOverworld_DaimynFactoryLocked:
    lock
    compareplayerfacing INTERNAL_DOWN @ Exiting the factory
    if equal _goto End
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    checkitem ITEM_FACTORY_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto OpenDoor
    pause 0x10
    msgbox gText_DoorIsLocked MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    release
    end

OpenDoor:
    playse 0x12 @ Sliding door opening
    opendoor 0x16 0x7
    waitdooranim
    waitse
    pause 0x10
    goto SetDoorOpen

## Interior
.equ VarMeltanEvents, 0x4061
.equ Meltan, 0x3

.equ FloorLeftShaded, 0x29B
.equ FloorUpShaded, 0x29D
.equ FloorUnshaded, 0x29F
.equ WallUpper, 0x28D
.equ WallLower, 0x295

.equ HorizontalDoorUpperLeft, 0x309
.equ HorizontalDoorUpperMiddle, 0x30A
.equ HorizontalDoorUpperRight, 0x30B
.equ HorizontalDoorLowerLeft, 0x311
.equ HorizontalDoorLowerMiddle, 0x312
.equ HorizontalDoorLowerRight, 0x313

.equ VerticalDoorUpperWall, 0x2FF
.equ VerticalDoorLowerWall, 0x307
.equ VerticalDoorShadedFloor, 0x30F
.equ VerticalDoorUnshadedFloor, 0x317

.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_DaimynFactoryInterior
MapScript_DaimynFactoryInterior:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_SetMeltanLocationAndBreakerState
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_DaimynFactory_FlightFlag
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_DaimynFactory
    mapscript MAP_SCRIPT_ON_RESUME MapResumeScript_HideLegendary
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_SetMeltanLocationAndBreakerState:
    compare VarMeltanEvents 0x1
    if lessthan _goto End
    movesprite2 Meltan 0x18 0x6
    setobjectmovementtype Meltan 64 @ Walk down on the spot, facing down
    clearflag 0x264 @ Power is off
    special 0x8E
    compare VarMeltanEvents 0x2
    if notequal _goto End
    @ Handle the breaker state
    call SetWeatherClear
    call OpenADoors
    call OpenBDoors
    setflag 0x264 @ Power is on
    end

MapEntryScript_DaimynFactory_FlightFlag:
    setworldmapflag 0x8B4 @ Been to Daimyn Factory
    end

LevelScripts_DaimynFactory:
    levelscript VarMeltanEvents 0x0 LevelScript_PlayerSurprisesMeltan
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerSurprisesMeltan:
    applymovement PLAYER m_PlayerWalksUp
    waitmovement PLAYER
    sound 0x15 @ Exclaim
    applymovement Meltan m_Surprise
    waitmovement Meltan
    applymovement Meltan m_LookDown
    pause 0x10
    cry SPECIES_MELTAN 0x0
    applymovement Meltan m_MeltanSurprise
    waitmovement Meltan
    pause DELAY_HALFSECOND
    applymovement Meltan m_MeltanRunsLeft
    waitmovement Meltan
    pause 0x10
    call SetWeatherClear
    playse 0x2A
    waitse
    call OpenADoors
    call DoorStateChangeCommon
    setflag 0x264 @ Power is on
    applymovement Meltan m_MeltanRunsRight
    waitmovement Meltan
    cry SPECIES_MELTAN 0x0
    pause DELAY_HALFSECOND
    applymovement Meltan m_MeltanRunsUp
    waitmovement Meltan
    setvar VarMeltanEvents 0x1
    movesprite Meltan 0x18 0x6 @ Move if the player remains on this map
    movesprite2 Meltan 0x18 0x6 @ Set permanent position
    setobjectmovementtype Meltan 64 @ Walk on the spot, facing down
    special 0x8E
    end

MapResumeScript_HideLegendary:
    checkflag 0x55
    if SET _goto HideMeltan
    end

HideMeltan:    
    hidesprite Meltan
    end

DoorStateChangeCommon:
    playse 0x8 @ Door open
    waitse
    special 0x8E
    return

OpenADoors:
    call OpenEntranceDoorA
    call OpenTopLeftDoor1A
    call OpenTopLeftDoor2A
    call OpenTopRightDoor1A
    call OpenTopRightDoor2A
    call OpenBottomLeftDoor2A
    call OpenBottomRightDoor1A
    call OpenBottomRightDoor2A
    return

CloseADoors:
    call CloseEntranceDoorA
    call CloseTopLeftDoor1A
    call CloseTopLeftDoor2A
    call CloseTopRightDoor1A
    call CloseTopRightDoor2A
    call CloseBottomLeftDoor2A
    call CloseBottomRightDoor1A
    call CloseBottomRightDoor2A
    return

OpenBDoors:
    call OpenLeftDoorB
    call OpenBottomLeftDoorB1
    call OpenBottomLeftDoorB2
    call OpenCentralUpperDoorB
    call OpenCentralLowerDoorB
    call OpenUpperVerticalDoorB
    call OpenLowerVerticalDoorB
    call OpenUpperRightDoorB
    call OpenLowerRightDoorB
    return

CloseBDoors:
    call CloseLeftDoorB
    call CloseBottomLeftDoorB1
    call CloseBottomLeftDoorB2
    call CloseCentralUpperDoorB
    call CloseCentralLowerDoorB
    call CloseUpperVerticalDoorB
    call CloseLowerVerticalDoorB
    call CloseUpperRightDoorB
    call CloseLowerRightDoorB
    return

OpenEntranceDoorA:
    setmaptile 0x17 0x1F FloorLeftShaded Passable
    setmaptile 0x18 0x1F FloorUnshaded Passable
    setmaptile 0x19 0x1F FloorUnshaded Passable
    setmaptile 0x17 0x20 FloorLeftShaded Passable
    setmaptile 0x18 0x20 FloorUnshaded Passable
    setmaptile 0x19 0x20 FloorUnshaded Passable
    return

CloseEntranceDoorA:
    setmaptile 0x17 0x1F HorizontalDoorUpperLeft Impassable
    setmaptile 0x18 0x1F HorizontalDoorUpperMiddle Impassable
    setmaptile 0x19 0x1F HorizontalDoorUpperRight Impassable
    setmaptile 0x17 0x20 HorizontalDoorLowerLeft Impassable
    setmaptile 0x18 0x20 HorizontalDoorLowerMiddle Impassable
    setmaptile 0x19 0x20 HorizontalDoorLowerRight Impassable
    return

OpenTopLeftDoor1A:
    setmaptile 0x5 0x9 FloorLeftShaded Passable
    setmaptile 0x6 0x9 FloorUnshaded Passable
    setmaptile 0x7 0x9 FloorUnshaded Passable
    setmaptile 0x5 0xA FloorLeftShaded Passable
    setmaptile 0x6 0xA FloorUnshaded Passable
    setmaptile 0x7 0xA FloorUnshaded Passable
    return

CloseTopLeftDoor1A:
    setmaptile 0x5 0x9 HorizontalDoorUpperLeft Impassable
    setmaptile 0x6 0x9 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x7 0x9 HorizontalDoorUpperRight Impassable
    setmaptile 0x5 0xA HorizontalDoorLowerLeft Impassable
    setmaptile 0x6 0xA HorizontalDoorLowerMiddle Impassable
    setmaptile 0x7 0xA HorizontalDoorLowerRight Impassable
    return

OpenTopLeftDoor2A:
    setmaptile 0xA 0x3 WallUpper Impassable
    setmaptile 0xA 0x4 WallLower Impassable
    setmaptile 0xA 0x5 FloorUpShaded Passable
    setmaptile 0xA 0x6 FloorUnshaded Passable
    return

CloseTopLeftDoor2A:
    setmaptile 0xA 0x3 VerticalDoorUpperWall Impassable
    setmaptile 0xA 0x4 VerticalDoorLowerWall Impassable
    setmaptile 0xA 0x5 VerticalDoorShadedFloor Impassable
    setmaptile 0xA 0x6 VerticalDoorUnshadedFloor Impassable
    return

OpenTopRightDoor1A:
    setmaptile 0x1F 0x8 FloorLeftShaded Passable
    setmaptile 0x20 0x8 FloorUnshaded Passable
    setmaptile 0x21 0x8 FloorUnshaded Passable
    setmaptile 0x1F 0x9 FloorLeftShaded Passable
    setmaptile 0x20 0x9 FloorUnshaded Passable
    setmaptile 0x21 0x9 FloorUnshaded Passable
    return

CloseTopRightDoor1A:
    setmaptile 0x1F 0x8 HorizontalDoorUpperLeft Impassable
    setmaptile 0x20 0x8 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x21 0x8 HorizontalDoorUpperRight Impassable
    setmaptile 0x1F 0x9 HorizontalDoorLowerLeft Impassable
    setmaptile 0x20 0x9 HorizontalDoorLowerMiddle Impassable
    setmaptile 0x21 0x9 HorizontalDoorLowerRight Impassable
    return

OpenTopRightDoor2A:
    setmaptile 0x1F 0xE FloorLeftShaded Passable
    setmaptile 0x20 0xE FloorUnshaded Passable
    setmaptile 0x21 0xE FloorUnshaded Passable
    setmaptile 0x1F 0xD FloorLeftShaded Passable
    setmaptile 0x20 0xD FloorUnshaded Passable
    setmaptile 0x21 0xD FloorUnshaded Passable
    return

CloseTopRightDoor2A:
    setmaptile 0x1F 0xD HorizontalDoorUpperLeft Impassable
    setmaptile 0x20 0xD HorizontalDoorUpperMiddle Impassable
    setmaptile 0x21 0xD HorizontalDoorUpperRight Impassable
    setmaptile 0x1F 0xE HorizontalDoorLowerLeft Impassable
    setmaptile 0x20 0xE HorizontalDoorLowerMiddle Impassable
    setmaptile 0x21 0xE HorizontalDoorLowerRight Impassable
    return

OpenBottomLeftDoor2A:
    setmaptile 0xB 0x21 WallUpper Impassable
    setmaptile 0xB 0x22 WallLower Impassable
    setmaptile 0xB 0x23 FloorUpShaded Passable
    setmaptile 0xB 0x24 FloorUnshaded Passable
    setmaptile 0xB 0x25 FloorUnshaded Passable
    return

CloseBottomLeftDoor2A:
    setmaptile 0xB 0x21 VerticalDoorUpperWall Impassable
    setmaptile 0xB 0x22 VerticalDoorLowerWall Impassable
    setmaptile 0xB 0x23 VerticalDoorShadedFloor Impassable
    setmaptile 0xB 0x24 VerticalDoorUnshadedFloor Impassable
    setmaptile 0xB 0x25 VerticalDoorUnshadedFloor Impassable
    return

OpenBottomRightDoor1A:
    setmaptile 0x23 0x1C FloorLeftShaded Passable
    setmaptile 0x24 0x1C FloorUnshaded Passable
    setmaptile 0x25 0x1C FloorUnshaded Passable
    setmaptile 0x23 0x1D FloorLeftShaded Passable
    setmaptile 0x24 0x1D FloorUnshaded Passable
    setmaptile 0x25 0x1D FloorUnshaded Passable
    return

CloseBottomRightDoor1A:
    setmaptile 0x23 0x1C HorizontalDoorUpperLeft Impassable
    setmaptile 0x24 0x1C HorizontalDoorUpperMiddle Impassable
    setmaptile 0x25 0x1C HorizontalDoorUpperRight Impassable
    setmaptile 0x23 0x1D HorizontalDoorLowerLeft Impassable
    setmaptile 0x24 0x1D HorizontalDoorLowerMiddle Impassable
    setmaptile 0x25 0x1D HorizontalDoorLowerRight Impassable
    return

OpenBottomRightDoor2A:
    setmaptile 0x27 0x22 FloorLeftShaded Passable
    setmaptile 0x28 0x22 FloorUnshaded Passable
    setmaptile 0x29 0x22 FloorUnshaded Passable
    setmaptile 0x27 0x23 FloorLeftShaded Passable
    setmaptile 0x28 0x23 FloorUnshaded Passable
    setmaptile 0x29 0x23 FloorUnshaded Passable
    return

CloseBottomRightDoor2A:
    setmaptile 0x27 0x22 HorizontalDoorUpperLeft Impassable
    setmaptile 0x28 0x22 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x29 0x22 HorizontalDoorUpperRight Impassable
    setmaptile 0x27 0x23 HorizontalDoorLowerLeft Impassable
    setmaptile 0x28 0x23 HorizontalDoorLowerMiddle Impassable
    setmaptile 0x29 0x23 HorizontalDoorLowerRight Impassable
    return

OpenLeftDoorB:
    setmaptile 0x1 0xE FloorLeftShaded Passable
    setmaptile 0x2 0xE FloorUnshaded Passable
    setmaptile 0x3 0xE FloorUnshaded Passable
    setmaptile 0x1 0xF FloorLeftShaded Passable
    setmaptile 0x2 0xF FloorUnshaded Passable
    setmaptile 0x3 0xF FloorUnshaded Passable
    return

CloseLeftDoorB:
    setmaptile 0x1 0xE HorizontalDoorUpperLeft Impassable
    setmaptile 0x2 0xE HorizontalDoorUpperMiddle Impassable
    setmaptile 0x3 0xE HorizontalDoorUpperRight Impassable
    setmaptile 0x1 0xF HorizontalDoorLowerLeft Impassable
    setmaptile 0x2 0xF HorizontalDoorLowerMiddle Impassable
    setmaptile 0x3 0xF HorizontalDoorLowerRight Impassable
    return

OpenBottomLeftDoorB1:
    setmaptile 0xA 0x17 FloorLeftShaded Passable
    setmaptile 0xB 0x17 FloorUnshaded Passable
    setmaptile 0xC 0x17 FloorUnshaded Passable
    setmaptile 0xA 0x18 FloorLeftShaded Passable
    setmaptile 0xB 0x18 FloorUnshaded Passable
    setmaptile 0xC 0x18 FloorUnshaded Passable
    return

CloseBottomLeftDoorB1:
    setmaptile 0xA 0x17 HorizontalDoorUpperLeft Impassable
    setmaptile 0xB 0x17 HorizontalDoorUpperMiddle Impassable
    setmaptile 0xC 0x17 HorizontalDoorUpperRight Impassable
    setmaptile 0xA 0x18 HorizontalDoorLowerLeft Impassable
    setmaptile 0xB 0x18 HorizontalDoorLowerMiddle Impassable
    setmaptile 0xC 0x18 HorizontalDoorLowerRight Impassable
    return

OpenBottomLeftDoorB2:
    setmaptile 0x8 0x20 FloorLeftShaded Passable
    setmaptile 0x9 0x20 FloorUnshaded Passable
    setmaptile 0xA 0x20 FloorUnshaded Passable
    setmaptile 0x8 0x21 FloorLeftShaded Passable
    setmaptile 0x9 0x21 FloorUnshaded Passable
    setmaptile 0xA 0x21 FloorUnshaded Passable
    return

CloseBottomLeftDoorB2:
    setmaptile 0x8 0x20 HorizontalDoorUpperLeft Impassable
    setmaptile 0x9 0x20 HorizontalDoorUpperMiddle Impassable
    setmaptile 0xA 0x20 HorizontalDoorUpperRight Impassable
    setmaptile 0x8 0x21 HorizontalDoorLowerLeft Impassable
    setmaptile 0x9 0x21 HorizontalDoorLowerMiddle Impassable
    setmaptile 0xA 0x21 HorizontalDoorLowerRight Impassable
    return

OpenCentralUpperDoorB:
    setmaptile 0x17 0x9 FloorLeftShaded Passable
    setmaptile 0x18 0x9 FloorUnshaded Passable
    setmaptile 0x19 0x9 FloorUnshaded Passable
    setmaptile 0x17 0xA FloorLeftShaded Passable
    setmaptile 0x18 0xA FloorUnshaded Passable
    setmaptile 0x19 0xA FloorUnshaded Passable
    return

CloseCentralUpperDoorB:
    setmaptile 0x17 0x9 HorizontalDoorUpperLeft Impassable
    setmaptile 0x18 0x9 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x19 0x9 HorizontalDoorUpperRight Impassable
    setmaptile 0x17 0xA HorizontalDoorLowerLeft Impassable
    setmaptile 0x18 0xA HorizontalDoorLowerMiddle Impassable
    setmaptile 0x19 0xA HorizontalDoorLowerRight Impassable
    return

OpenCentralLowerDoorB:
    setmaptile 0x1B 0x19 FloorLeftShaded Passable
    setmaptile 0x1C 0x19 FloorUnshaded Passable
    setmaptile 0x1D 0x19 FloorUnshaded Passable
    setmaptile 0x1B 0x1A FloorLeftShaded Passable
    setmaptile 0x1C 0x1A FloorUnshaded Passable
    setmaptile 0x1D 0x1A FloorUnshaded Passable
    return

CloseCentralLowerDoorB:
    setmaptile 0x1B 0x19 HorizontalDoorUpperLeft Impassable
    setmaptile 0x1C 0x19 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x1D 0x19 HorizontalDoorUpperRight Impassable
    setmaptile 0x1B 0x1A HorizontalDoorLowerLeft Impassable
    setmaptile 0x1C 0x1A HorizontalDoorLowerMiddle Impassable
    setmaptile 0x1D 0x1A HorizontalDoorLowerRight Impassable
    return

OpenUpperVerticalDoorB:
    setmaptile 0x25 0x8 WallUpper Impassable
    setmaptile 0x25 0x9 WallLower Impassable
    setmaptile 0x25 0xA FloorUpShaded Passable
    setmaptile 0x25 0xB FloorUnshaded Passable
    setmaptile 0x25 0xC FloorUnshaded Passable
    return

CloseUpperVerticalDoorB:
    setmaptile 0x25 0x8 VerticalDoorUpperWall Impassable
    setmaptile 0x25 0x9 VerticalDoorLowerWall Impassable
    setmaptile 0x25 0xA VerticalDoorShadedFloor Impassable
    setmaptile 0x25 0xB VerticalDoorUnshadedFloor Impassable
    setmaptile 0x25 0xC VerticalDoorUnshadedFloor Impassable
    return

OpenLowerVerticalDoorB:
    setmaptile 0x26 0x14 WallUpper Impassable
    setmaptile 0x26 0x15 WallLower Impassable
    setmaptile 0x26 0x16 FloorUpShaded Passable
    setmaptile 0x26 0x17 FloorUnshaded Passable
    setmaptile 0x26 0x18 FloorUnshaded Passable
    return

CloseLowerVerticalDoorB:
    setmaptile 0x26 0x14 VerticalDoorUpperWall Impassable
    setmaptile 0x26 0x15 VerticalDoorLowerWall Impassable
    setmaptile 0x26 0x16 VerticalDoorShadedFloor Passable
    setmaptile 0x26 0x17 VerticalDoorUnshadedFloor Passable
    setmaptile 0x26 0x18 VerticalDoorUnshadedFloor Passable
    return

OpenUpperRightDoorB:
    setmaptile 0x1F 0x14 FloorLeftShaded Passable
    setmaptile 0x20 0x14 FloorUnshaded Passable
    setmaptile 0x21 0x14 FloorUnshaded Passable
    setmaptile 0x1F 0x15 FloorLeftShaded Passable
    setmaptile 0x20 0x15 FloorUnshaded Passable
    setmaptile 0x21 0x15 FloorUnshaded Passable
    return

CloseUpperRightDoorB:
    setmaptile 0x1F 0x14 HorizontalDoorUpperLeft Impassable
    setmaptile 0x20 0x14 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x21 0x14 HorizontalDoorUpperRight Impassable
    setmaptile 0x1F 0x15 HorizontalDoorLowerLeft Impassable
    setmaptile 0x20 0x15 HorizontalDoorLowerMiddle Impassable
    setmaptile 0x21 0x15 HorizontalDoorLowerRight Impassable
    return

OpenLowerRightDoorB:
    setmaptile 0x1F 0x21 FloorLeftShaded Passable
    setmaptile 0x20 0x21 FloorUnshaded Passable
    setmaptile 0x21 0x21 FloorUnshaded Passable
    setmaptile 0x1F 0x22 FloorLeftShaded Passable
    setmaptile 0x20 0x22 FloorUnshaded Passable
    setmaptile 0x21 0x22 FloorUnshaded Passable
    return

CloseLowerRightDoorB:
    setmaptile 0x1F 0x21 HorizontalDoorUpperLeft Impassable
    setmaptile 0x20 0x21 HorizontalDoorUpperMiddle Impassable
    setmaptile 0x21 0x21 HorizontalDoorUpperRight Impassable
    setmaptile 0x1F 0x22 HorizontalDoorLowerLeft Impassable
    setmaptile 0x20 0x22 HorizontalDoorLowerMiddle Impassable
    setmaptile 0x21 0x22 HorizontalDoorLowerRight Impassable
    return

.global EventScript_DaimynFactory_Meltan
EventScript_DaimynFactory_Meltan:
    faceplayer
    cry SPECIES_MELTAN 0x0
    waitcry
    msgbox gtext_DaimynFactory_MeltanBattleStart MSG_NORMAL
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_THUNDERWAVE
    setvar 0x8001 MOVE_THUNDERBOLT
    setvar 0x8002 MOVE_ACIDARMOR
    setvar 0x8003 MOVE_FLASHCANNON
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_MELTAN 60 ITEM_PETAYA_BERRY
    setflag 0x55 @ Meltan hidden
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _goto DefeatedMeltan
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _goto FledFromMeltan
    end

DefeatedMeltan:
    msgbox gtext_DaimynFactory_MeltanDefeated MSG_NORMAL
    end

FledFromMeltan:
    msgbox gtext_DaimynFactory_MeltanFledFromBattle MSG_NORMAL
    end

.global EventScript_DaimynFactory_FindTM25Thunder
EventScript_DaimynFactory_FindTM25Thunder:
    setvar CHOSEN_ITEM ITEM_TM25
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynFactory_BurglarSly
EventScript_DaimynFactory_BurglarSly:
    trainerbattle0 0x0 456 0x0 gText_DaimynFactory_BurglarSly_Intro gText_DaimynFactory_BurglarSly_Defeat
    msgbox gText_DaimynFactory_BurglarSly_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactory_EngineerHasan
EventScript_DaimynFactory_EngineerHasan:
    trainerbattle0 0x0 457 0x0 gText_DaimynFactory_EngineerHasan_Intro gText_DaimynFactory_EngineerHasan_Defeat
    msgbox gText_DaimynFactory_EngineerHasan_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactory_BurglarWill
EventScript_DaimynFactory_BurglarWill:
    trainerbattle0 0x0 458 0x0 gText_DaimynFactory_BurglarWill_Intro gText_DaimynFactory_BurglarWill_Defeat
    msgbox gText_DaimynFactory_BurglarWill_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactory_EngineerElroy
EventScript_DaimynFactory_EngineerElroy:
    trainerbattle0 0x0 459 0x0 gText_DaimynFactory_EngineerElroy_Intro gText_DaimynFactory_EngineerElroy_Defeat
    msgbox gText_DaimynFactory_EngineerElroy_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactory_RustedData
EventScript_DaimynFactory_RustedData:
    finditem ITEM_RUSTED_DATA 0x1
    end

.global SignScript_DaimynFactory_BreakersNotice
SignScript_DaimynFactory_BreakersNotice:
    msgbox gText_DaimynFactory_BreakerNotice MSG_SIGN
    end

.global SignScript_DaimynFacatory_Breaker
SignScript_DaimynFacatory_Breaker:
    compare VarMeltanEvents 0x2
    if equal _goto NoNeedToFlipBreaker
    checkflag 0x264 @ Breaker state
    if NOT_SET _goto BreakerIsOff
    goto BreakerIsOn

BreakerIsOff:
    bufferstring 0x0 gText_DaimynFactory_BreakerOff
    bufferstring 0x1 gText_DaimynFactory_BreakerOn
    call ChangeBreakerCommon
    call SetWeatherClear
    playse 0x2A
    waitse
    call OpenADoors
    call CloseBDoors
    call DoorStateChangeCommon 
    setflag 0x264 @ Power is on
    msgbox gText_DaimynFactory_BreakerFlipped MSG_NORMAL
    end

BreakerIsOn:
    bufferstring 0x0 gText_DaimynFactory_BreakerOn
    bufferstring 0x1 gText_DaimynFactory_BreakerOff
    call ChangeBreakerCommon
    call SetWeatherDark
    playse 0x2A
    waitse
    call OpenBDoors
    call CloseADoors
    call DoorStateChangeCommon 
    clearflag 0x264 @ Power is off
    msgbox gText_DaimynFactory_BreakerFlipped MSG_NORMAL
    end

ChangeBreakerCommon:
    msgbox gText_DaimynFactory_BreakerPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChangeBreaker
    return

ChoseNotToChangeBreaker:
    msgbox gText_DaimynFactory_BreakerChoseNotTo MSG_NORMAL
    end

NoNeedToFlipBreaker:
    msgbox gText_DaimynFactory_NoNeedToFlipBreaker MSG_NORMAL
    end

TileScript_EncounterMeltan_Left:
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    goto TileScript_EncounterMeltan_Middle

TileScript_EncounterMeltan_Middle:
    applymovement PLAYER m_LookUp
    sound 0x15 @ Exclaim
    applymovement Meltan m_Surprise
    waitmovement Meltan
    cry SPECIES_MELTAN 0x0
    applymovement Meltan m_MeltanJumps
    waitmovement Meltan
    pause DELAY_HALFSECOND
    dofieldeffect 69 @ Screen flash
    waitfieldeffect 69
    playse 0x51 @ Thunder2
    waitse
    call SetWeatherClear
    dofieldeffect 69 @ Screen flash
    waitfieldeffect 69
    call OpenADoors
    call OpenBDoors
    call DoorStateChangeCommon
    special 0x8E
    setflag 0x264 @ Power is on
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Meltan m_MeltanBigSurprise
    cry SPECIES_MELTAN 0x0
    msgbox gText_DaimynFactory_GeneratorOn MSG_NORMAL
    setvar VarMeltanEvents 0x2
    end

TileScript_EncounterMeltan_Right:
    applymovement PLAYER m_WalkLeft
    waitmovement PLAYER
    goto TileScript_EncounterMeltan_Middle

m_PlayerWalksUp: .byte walk_up, walk_up, walk_up, end_m
m_MeltanSurprise: .byte jump_onspot_down, end_m
m_MeltanRunsLeft: .byte run_left, run_left, run_left, look_up, end_m
m_MeltanRunsRight: .byte run_right, run_right, run_right, run_up, look_down, jump_onspot_down, end_m
m_MeltanRunsUp: .byte run_up, run_up, run_up, end_m
m_MeltanJumps: .byte jump_onspot_down, pause_long, jump_onspot_down, pause_long, end_m
m_MeltanBigSurprise: .byte say_double_exclaim, end_m
