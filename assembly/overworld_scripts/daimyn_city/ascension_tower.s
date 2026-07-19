.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ RivalOnFirstFloor, 7
.equ SeleneOnFirstFloor, 8

.global MapScript_AscensionTower
MapScript_AscensionTower:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_AscensionTower_ShowRivalAndSelene
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_AscensionTower_FlightFlag
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AscensionTower
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_AscensionTower_ShowRivalAndSelene:
    checkflag 0x27F @ Victory Road challenge started
    if SET _goto End
    callasm CountBadges
    compare LASTRESULT 8
    if notequal _goto End
    clearflag 0x3C @ Show Selene and Rival
    setvar 0x406C 0x1 @ Trigger level script on entry
    end

MapEntryScript_AscensionTower_FlightFlag:
    setworldmapflag 0x8B2 @ Been to Ascension Tower
    call ResetRoute11PlutoEventOnWhiteout
    call ResetUteyaVillageGymFlagsOnWhiteout
    end

LevelScripts_AscensionTower:
    levelscript 0x406C 0x1 LevelScript_AscensionTower_RegisteringForEliteFourChallenge
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_RegisteringForEliteFourChallenge:
    checkflag 0x93D @ Skipping Cutscenes
    if SET _goto SkippingCutscenes_AscensionTower_GoToVictoryRoad
    applymovement PLAYER m_PlayerWalksToRival
    waitmovement PLAYER
    applymovement RivalOnFirstFloor m_LookLeft
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalGreetsPlayer MSG_NORMAL
    applymovement RivalOnFirstFloor m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalAsksToRegister MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_AttendantAsksToSeeChampionsFlag MSG_NORMAL
    applymovement RivalOnFirstFloor m_Question
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalConfusedAboutFlag MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_AttendantExplainsVictoryRoadChallenge MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalAsksToTakeVictoryRoadChallenge MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_AttendantAsksToSeeBadges MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalPresentsBadges MSG_NORMAL
    fanfare 0x13D @ Gym victory
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_PlayerPresentsBadges MSG_KEEPOPEN
    waitfanfare
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_AttendantCongratulatesPlayerAndRival MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_AttendantCallsForEliteFourMember MSG_NORMAL
    applymovement RivalOnFirstFloor m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalWaitingForEliteFourMember MSG_NORMAL
    fadescreen FADEOUT_BLACK
    playse 0x52 @ Elevator
    waitse
    playse 0x42 @ Ding dong
    waitse
    pause DELAY_HALFSECOND
    fadescreen FADEIN_BLACK
    applymovement SeleneOnFirstFloor m_WalkDownToDivider
    waitmovement SeleneOnFirstFloor
    call OpenFloorBarrier
    applymovement PLAYER m_LookUp
    applymovement RivalOnFirstFloor m_LookUp
    waitmovement RivalOnFirstFloor
    applymovement PLAYER m_Surprise
    applymovement RivalOnFirstFloor m_Surprise
    waitmovement RivalOnFirstFloor
    sound 0x15 @ Exclaim
    applymovement RivalOnFirstFloor m_RivalWalksBesidePlayer
    applymovement PLAYER m_LookLeft
    applymovement SeleneOnFirstFloor m_SeleneWalksToDuo
    waitmovement ALLEVENTS
    playbgm 0x196 @ Bianca Encounter
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneGreetsPlayerAndRival MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalGreetingSelene MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneExplainsHerself MSG_NORMAL
    applymovement RivalOnFirstFloor m_Joy
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalUnderstands MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneExplainsVictoryRoadChallenge MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneExplainsEliteFourChallenge MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalHasNoQuestions MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneBidsPlayerAndRivalFarewell MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalIsReady MSG_NORMAL
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_SeleneLeaves MSG_NORMAL
    applymovement SeleneOnFirstFloor m_SeleneLeaves
    waitmovement SeleneOnFirstFloor
    playse 0x26 @ Door shut
    waitse
    setmaptile 0x9 0x8 0x2B4 0x1 @ door barrier tile
    special 0x8E
    fadedefaultbgm
    applymovement PLAYER m_LookDown
    applymovement RivalOnFirstFloor m_LookUp
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalRecapsTheChallenges MSG_NORMAL
    applymovement RivalOnFirstFloor m_RivalLeaves
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookDown
    waitmovement RivalOnFirstFloor
    playse 0x9 @ Exit room
    waitse
    hidesprite SeleneOnFirstFloor
    hidesprite RivalOnFirstFloor
    setflag 0x3C @ Hide Selene and Rival again
    setflag 0x27F @ Victory Road challenge started
    addvar 0x406C 0x1
    end

OpenFloorBarrier:
    pause 0x10
    playse 0x26 @ Door shut
    setmaptile 0x9 0x8 0x284 0x0 @ shaded floor tile
    special 0x8E
    pause 0x10
    return

.global EventScript_AscensionTower_BattleTowerAttendant
EventScript_AscensionTower_BattleTowerAttendant:
    lock
    msgbox gText_AscensionTower_BattleTowerAttendant_GatheringFunding MSG_NORMAL
    end
    @ msgbox gText_AscensionTower_BattleTowerAttendant_Introduction MSG_KEEPOPEN
    @ multichoiceoption gText_Yes 0
	@ multichoiceoption gText_Info 1
	@ multichoiceoption gText_No 2
    @ multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	@ copyvar MULTICHOICE_SELECTION LASTRESULT
	@ switch LASTRESULT
	@ case 0, TakeBattleTowerChallenge
	@ case 1, BattleTowerInfo
	@ case 2, AttendantChoseNo
    @ goto AttendantChoseNo

@ TakeBattleTowerChallenge:
@     @ Later, perform a check here for the champions flag
@     msgbox gText_AscensionTower_BattleTowerAttendant_NotChampion MSG_NORMAL
@     release
@     end

@ BattleTowerInfo:
@     msgbox gText_AscensionTower_EliteFourAttendant_BattleTowerInfo MSG_NORMAL
@     goto EventScript_AscensionTower_BattleTowerAttendant

.global EventScript_AscensionTower_EliteFourAttendant
EventScript_AscensionTower_EliteFourAttendant:
    lock
    checkflag 0x82C @ Game cleared
    if SET _call EliteFourAttendantIntro_PlayerIsChampion
    if NOT_SET _call EliteFourAttendantIntro_PlayerIsChallenging
    multichoiceoption gText_Yes 0
	multichoiceoption gText_Info 1
	multichoiceoption gText_No 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, TakeEliteFourChallenge
	case 1, EliteFourInfo
	case 2, AttendantChoseNo
    goto AttendantChoseNo

EliteFourAttendantIntro_PlayerIsChampion:
    msgbox gText_AscensionTower_EliteFourAttendant_Introduction_PlayerIsChampion MSG_KEEPOPEN
    return

EliteFourAttendantIntro_PlayerIsChallenging:
    msgbox gText_AscensionTower_EliteFourAttendant_Introduction MSG_KEEPOPEN
    return

TakeEliteFourChallenge:
    checkitem ITEM_VICTORY_FLAG 0x1
    compare LASTRESULT TRUE
    if notequal _goto NoVictoryFlag
    clearflag 0x4B8 @ E4 Hannah defeated
    clearflag 0x4B9 @ E4 Lucas defeated
    clearflag 0x4BA @ E4 Jenna defeated
    clearflag 0x4BB @ E4 Thomas defeated 
    checkflag 0x82C @ Game cleared
    if SET _call EliteFourAttendantGettingTheGate_PlayerIsChampion
    if NOT_SET _call EliteFourAttendantGettingTheGate_PlayerIsChallenging
    applymovement LASTTALKED m_LookLeft
    call OpenFloorBarrier
    applymovement LASTTALKED m_LookDown
    msgbox gText_AscensionTower_EliteFourAttendant_WishingLuck MSG_NORMAL
    applymovement PLAYER m_PlayerWalksToElevator
    waitmovement PLAYER
    playse 0x8 @ door open
    opendoor 0x9 0x1
    waitdooranim
    applymovement PLAYER m_PlayerEntersElevator
    waitmovement PLAYER
    playse 0x26 @ door close
    closedoor 0x9 0x1
    waitdooranim
    setvar 0x406C 0x2 @ Starting E4 challenge
    warp 1 107 0
    end

NoVictoryFlag:
    msgbox gText_AscensionTower_EliteFourAttendant_NoChampionsFlag MSG_NORMAL
    checkflag 0x27F @ Victory Road challenge started
    if SET _goto NoVictoryFlag_AlreadyRegisteredForVictoryRoad
    msgbox gText_AscensionTower_EliteFourAttendant_NoChampionsFlag_HasNotEarnedRightToEnterVictoryRoad MSG_NORMAL
    release
    end

NoVictoryFlag_AlreadyRegisteredForVictoryRoad:
    msgbox gText_AscensionTower_EliteFourAttendant_NoChampionsFlag_HasEarnedRightToEnterVictoryRoad MSG_NORMAL
    release
    end

EliteFourAttendantGettingTheGate_PlayerIsChampion:
    msgbox gText_AscensionTower_EliteFourAttendant_GettingTheGate_PlayerIsChampion MSG_NORMAL
    return

EliteFourAttendantGettingTheGate_PlayerIsChallenging:
    msgbox gText_AscensionTower_EliteFourAttendant_GettingTheGate MSG_NORMAL
    return

EliteFourInfo:
    msgbox gText_AscensionTower_EliteFourAttendant_ChallengeInfo MSG_NORMAL
    goto EventScript_AscensionTower_EliteFourAttendant

AttendantChoseNo:
    msgbox gText_AscensionTower_AttendantChoseNo MSG_NORMAL
    release
    end

.global EventScript_AscensionTower_Blackbelt
EventScript_AscensionTower_Blackbelt:
    npcchat gText_AscensionTower_KarateMan
    end

.global EventScript_AscensionTower_Girl
EventScript_AscensionTower_Girl:
    npcchat gText_AscensionTower_Girl
    end

.global EventScript_AscensionTower_BigMan
EventScript_AscensionTower_BigMan:
    npcchat gText_AscensionTower_BigMan
    end

.global SignScript_AscensionTower_RecordsBoard
SignScript_AscensionTower_RecordsBoard:
    msgbox gText_AscensionTower_RecordsSign MSG_SIGN
    checkflag 0x82C @ Game cleared
    if SET _goto RecordsBoard_PostChampion
    msgbox gText_AscensionTower_RecordsSign_NotOnBoard MSG_SIGN
    end

RecordsBoard_PostChampion:
    setvar 0x8004 10 @ Times entered the hall of fame
    callasm StoreGameStat
    subvar LASTRESULT 0x1 @ First time is entry into the hall of fame
    buffernumber 0x0 LASTRESULT
    msgbox gText_AscensionTower_RecordsSign_ChampionTitleDefenses MSG_SIGN
    end

m_PlayerWalksToRival: .byte walk_up, walk_up, walk_right, walk_right, walk_up, walk_up, look_right, end_m
m_WalkDownToDivider: .byte walk_down, walk_down, end_m
m_SeleneWalksToDuo: .byte walk_down, walk_down, walk_down, walk_down, walk_right, end_m
m_RivalWalksBesidePlayer: .byte walk_down, walk_left, end_m
m_SeleneLeaves: .byte walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_RivalLeaves: .byte walk_down, walk_down, walk_down, walk_left, walk_left, look_down, end_m
m_PlayerWalksToElevator: .byte walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerEntersElevator: .byte walk_up, set_invisible, end_m

// Elite Four Challenge
.global MapScript_AscensionTower_Elevator
MapScript_AscensionTower_Elevator:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AscensionTower_Elevator
    .byte MAP_SCRIPT_TERMIN

LevelScripts_AscensionTower_Elevator:
    levelscript 0x406C 0x2 LevelScript_AscensionTower_Elevator_FirstChallenger
    levelscript 0x406C 0x5 LevelScript_AscensionTower_Elevator_SecondChallenger
    levelscript 0x406C 0x8 LevelScript_AscensionTower_Elevator_ThirdChallenger
    levelscript 0x406C 0xB LevelScript_AscensionTower_Elevator_FourthChallenger
    levelscript 0x406C 0xE LevelScript_AscensionTower_Elevator_ChampionChallenger
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_Elevator_FirstChallenger:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    checkflag 0x82C @ Game is cleared
    if SET _call EleveatorAttendant_FirstFloor_Rematch
    if NOT_SET _call EleveatorAttendant_FirstFloor
    setdynamicwarp 1 75 0
    goto AscensionTowerElevatorTravel

EleveatorAttendant_FirstFloor:
    msgbox gText_AscensionTower_ElevatorAttendant_FirstFloor MSG_NORMAL
    return

EleveatorAttendant_FirstFloor_Rematch:
    msgbox gText_AscensionTower_ElevatorAttendant_FirstFloor_PerformingRematch MSG_NORMAL
    return

LevelScript_AscensionTower_Elevator_SecondChallenger:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    msgbox gText_AscensionTower_ElevatorAttendant_SecondFloor MSG_NORMAL
    setdynamicwarp 1 76 0
    goto AscensionTowerElevatorTravel

LevelScript_AscensionTower_Elevator_ThirdChallenger:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    msgbox gText_AscensionTower_ElevatorAttendant_ThirdFloor MSG_NORMAL
    setdynamicwarp 1 77 0
    goto AscensionTowerElevatorTravel

LevelScript_AscensionTower_Elevator_FourthChallenger:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    msgbox gText_AscensionTower_ElevatorAttendant_FourthFloor MSG_NORMAL
    setdynamicwarp 1 78 0
    goto AscensionTowerElevatorTravel

LevelScript_AscensionTower_Elevator_ChampionChallenger:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    msgbox gText_AscensionTower_ElevatorAttendant_ChampionsFloor MSG_NORMAL
    setdynamicwarp 1 79 0
    goto AscensionTowerElevatorTravel

AscensionTowerElevatorTravel:
    addvar 0x406C 0x1
    applymovement 0x1 m_YaelStartsElevator
    waitmovement ALLEVENTS
    pause DELAY_HALFSECOND
    special 0x111 @ Elevator animation
    waitstate
    pause DELAY_HALFSECOND
    applymovement 0x1 m_YaelReturnsFromElevator
    waitmovement ALLEVENTS
    compare 0x406C 0xF
    if equal _goto YaelBeforeChampion
    msgbox gText_AscensionTower_ElevatorAttendant_WishesLuck MSG_NORMAL
    end

YaelBeforeChampion:
    checkflag 0x82C @ Game cleared
    if SET _goto YaelBeforeChampion_PlayerIsChampion
    npcchatwithmovement gText_AscensionTower_ElevatorAttendant_PriorToChampion m_LookDown
    end

YaelBeforeChampion_PlayerIsChampion:
    npcchatwithmovement gText_AscensionTower_ElevatorAttendant_PriorToChampion_PlayerIsChampion m_LookDown
    end

.global EventScript_AscensionTower_Elevator_Attendant
EventScript_AscensionTower_Elevator_Attendant:
    compare 0x406C 0xF
    if equal _goto YaelBeforeChampion
    npcchatwithmovement gText_AscensionTower_ElevatorAttendant_Chat m_LookDown
    end

.equ WallLeftUpper, 0x29D
.equ WallMiddleUpper, 0x29E
.equ WallRightUpper, 0x29F
.equ WallLeftLower, 0x2A5
.equ WallMiddleLower, 0x2A6
.equ WallRightLower, 0x2A7
.equ RoomOneFloor, 0x29B
.equ RoomOneFloorShaded, 0x2A3
.equ RoomTwoFloor, 0x331
.equ RoomTwoFloorShaded, 0x339
.equ RoomThreeFloor, 0x334
.equ RoomThreeFloorShaded, 0x33C
.equ RoomFourFloor, 0x337
.equ RoomFourFloorShaded, 0x33F
.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_AscensionTower_E4Room
MapScript_AscensionTower_E4Room:
    mapscript MAP_SCRIPT_ON_RESUME LevelScript_AscensionTower_E4Room_FloorLighting
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_AscensionTower_E4_OnWarp
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AscensionTower_E4_ChallengingEliteFour
    .byte MAP_SCRIPT_TERMIN

LevelScript_AscensionTower_E4Room_FloorLighting:
    setflag 0x2 @ Temp flag gating the light pulse task; cleared on every map load, so re-set here
    special 0x1A1 @ DoPokemonLeagueLightingEffect - pulses the floor lights, choosing the champion or E4 palette by current map
    end

LevelScripts_AscensionTower_E4_OnWarp:
    levelscript 0x406C 0x3 LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle @ Hannah
    levelscript 0x406C 0x6 LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle @ Lucas
    levelscript 0x406C 0x9 LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle @ Jenna
    levelscript 0x406C 0xC LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle @ Thomas
    levelscript 0x406C 0xF LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle @ Selene
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_SetPlayerFacing_ForE4Battle:
    applymovement PLAYER m_LookUp
    end

LevelScripts_AscensionTower_E4_ChallengingEliteFour:
    levelscript 0x406C 0x3 LevelScript_AscensionTower_WalkForward_ForE4Battle_Common @ Hannah
    levelscript 0x406C 0x6 LevelScript_AscensionTower_WalkForward_ForE4Battle_Common @ Lucas
    levelscript 0x406C 0x9 LevelScript_AscensionTower_WalkForward_ForE4Battle_Common @ Jenna
    levelscript 0x406C 0xC LevelScript_AscensionTower_WalkForward_ForE4Battle_Common @ Thomas
    levelscript 0x406C 0xF LevelScript_AscensionTower_WalkForward_ForChampionBattle @ Selene
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_WalkForward_ForE4Battle_Common:
    applymovement PLAYER m_ApproachEliteFour
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    playse 0x26 @ Door shut
    setmaptile 0x5 0xB WallLeftUpper Impassable
    setmaptile 0x6 0xB WallMiddleUpper Impassable
    setmaptile 0x7 0xB WallRightUpper Impassable
    setmaptile 0x5 0xC WallLeftLower Impassable
    setmaptile 0x6 0xC WallMiddleLower Impassable
    setmaptile 0x7 0xC WallRightLower Impassable
    special 0x8E
    addvar 0x406C 0x1 @ Prevent replaying the levelscript
    release
    end

LevelScript_AscensionTower_WalkForward_ForChampionBattle:
    pause DELAY_HALFSECOND
    checkflag 0x82C @ Game cleared
    if SET _goto AscensionTower_ChampionsQuarters_TitleDefense
    applymovement PLAYER m_ApproachChampion
    waitmovement PLAYER
    lock
    pause DELAY_HALFSECOND
    msgbox gText_AscensionTower_ChampionSelene_PreBattle1 MSG_NORMAL
    applymovement 0x1 m_LookLeft
    msgbox gText_AscensionTower_ChampionSelene_PreBattle2 MSG_NORMAL
    applymovement 0x1 m_LookDown
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_ChampionSelene_PreBattle3 MSG_NORMAL
    call SetupMugshotChampionAndTitleDefense
    trainerbattle3 0x0 524 0x100 gText_AscensionTower_ChampionSelene_Defeat
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    playbgm 345 @ N's farewell
    msgbox gText_AscensionTower_ChampionSelene_PostBattle MSG_NORMAL
    applymovement 0x1 m_ReigningChampionWalksToHallOfFame
    applymovement PLAYER m_PlayerWalksToHallOfFame
    waitmovement PLAYER
    setflag 0x4BC @ Champion Selene defeated. This is never reset as it's used to determine if the player is in the postgame
    clearflag 0x6C @ Post-Credits NPCs will appear
    clearflag 0x9D @ Postgame NPCs will now appear
    clearflag 0x3C @ Show Selene in HoF Room
    setvar 0x4070 0x1 @ Trigger postcredits upon returning to Anthra Town
    setvar 0x4071 0x1 @ Trigger Hawthorne's Conservatory event
    warp 1 80 0
    end

AscensionTower_ChampionsQuarters_TitleDefense:
    applymovement PLAYER m_PlayerWalksToTakeChampionsPlace
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    msgbox gText_AscensionTower_TitleDefense_WaitingForChallenger MSG_NORMAL
    pause DELAY_HALFSECOND
    playse 0x52 @ Elevator
    waitse
    playse 0x42 @ Ding dong
    waitse
    pause DELAY_HALFSECOND
    playse 0x8 @ door open
    call SetupMugshotChampionAndTitleDefense
    special CAMERA_START
    applymovement CAMERA m_CameraTitleDefensePanDown
    waitmovement CAMERA
    special CAMERA_END
    checkflag 0x288 @ Defeated Kurtis in postgame
    random 11
    copyvar 0x4002 LASTRESULT
    if SET _call AscensionTower_ChampionsQuarters_TitleDefense_AfterBeatingKurtis
    switch 0x4002
    case 0, TitleDefense_Rival _call
    case 1, TitleDefense_Joey _call
    case 2, TitleDefense_Selene _call
    case 3, TitleDefense_Alistair _call
    case 4, TitleDefense_Hawthorne _call
    case 5, TitleDefense_Clancy _call
    case 6, TitleDefense_Ena _call
    case 7, TitleDefense_Copycat _call
    case 8, TitleDefense_Foreigner _call
    case 9, TitleDefense_Collin _call
    case 10, TitleDefense_Crystal _call
    case 11, TitleDefense_Irene _call
    case 12, TitleDefense_Ronald _call
    case 13, TitleDefense_Kurtis _call
    applymovement 0x2 m_ChallengerLeavesTheRoom
    waitmovement 0x2
    pause DELAY_HALFSECOND
    playse 0x8 @ door open
    special CAMERA_START
    applymovement CAMERA m_CameraTitleDefensePanUp
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_AscensionTower_TitleDefense_PlayerSucceeded MSG_NORMAL
    applymovement PLAYER m_ReigningChampionWalksToHallOfFame
    waitmovement PLAYER
    addvar 0x40AA 0x1 @ Player has defended their title one more time
    clearflag 0x9D @ Postgame NPCs will now appear (in case they weren't before)
    compare 0x4071 0x2 @ Hawthorne's Conservatory event
    if lessthan _call PrepareHawthornesConservatoryEvent
    warp 1 80 0
    end

@ This is a repair script for legacy saves. Force Hawthorne's Conservatory cutscene to play in postgame
PrepareHawthornesConservatoryEvent:
    setvar 0x4071 0x1
    return

AscensionTower_ChampionsQuarters_TitleDefense_AfterBeatingKurtis:
    random 14 @ Include Irene, Ronald, and Kurtis
    copyvar 0x4002 LASTRESULT
    return

TitleDefense_Rival:
    setvar 0x5029 72
    showsprite 0x2
    @ Figure out the rival's team
    copyvar 0x4001 0x408E
    setvar 0x4000 568 @ trainer ID, which is 568 + 0-7 depending on value in 0x408E (Water starter generation)
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Rival_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Rival_PreBattle MSG_NORMAL
    trainerbattle3 0x0 0x4000 0x100 gText_AscensionTower_TitleDefenseChallenger_Rival_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Rival_Defeat MSG_NORMAL
    return

TitleDefense_Joey:
    setvar 0x5029 18
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Joey_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Joey_PreBattle MSG_NORMAL
    trainerbattle3 0x0 576 0x100 gText_AscensionTower_TitleDefenseChallenger_Joey_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Joey_Defeat MSG_NORMAL
    return

TitleDefense_Selene:
    setvar 0x4000 577
    checkflag 0x278 @ Got Victini Gift
    if SET _call TitleDefense_Selene_SetNoVictiniTeam
    setvar 0x5029 74
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Selene_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Selene_PreBattle MSG_NORMAL
    trainerbattle3 0x0 0x4000 0x100 gText_AscensionTower_TitleDefenseChallenger_Selene_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Selene_Defeat MSG_NORMAL
    return

TitleDefense_Selene_SetNoVictiniTeam:
    setvar 0x4000 578
    return

TitleDefense_Alistair:
    setvar 0x5029 78
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Alistair_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Alistair_PreBattle MSG_NORMAL
    trainerbattle3 0x0 579 0x100 gText_AscensionTower_TitleDefenseChallenger_Alistair_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Alistair_Defeat MSG_NORMAL
    return

TitleDefense_Hawthorne:
    setvar 0x5029 71
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Hawthorne_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Hawthorne_PreBattle MSG_NORMAL
    trainerbattle3 0x0 580 0x100 gText_AscensionTower_TitleDefenseChallenger_Hawthorne_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Hawthorne_Defeat MSG_NORMAL
    return

TitleDefense_Clancy:
    setvar 0x5029 26
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Clancy_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Clancy_PreBattle MSG_NORMAL
    trainerbattle3 0x0 581 0x100 gText_AscensionTower_TitleDefenseChallenger_Clancy_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Clancy_Defeat MSG_NORMAL
    return

TitleDefense_Ena:
    setvar 0x5029 22
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ena_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ena_PreBattle MSG_NORMAL
    trainerbattle3 0x0 582 0x100 gText_AscensionTower_TitleDefenseChallenger_Ena_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ena_Defeat MSG_NORMAL
    return

TitleDefense_Copycat:
    setflag 0x936 @ Battle a copy of the player's team, cleared after battle
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _call TitleDefense_Copycat_Male
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if notequal _call TitleDefense_Copycat_Female
    return

TitleDefense_Copycat_Male:
    setvar 0x5029 0
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatM_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatM_PreBattle MSG_NORMAL
    trainerbattle3 0x0 583 0x100 gText_AscensionTower_TitleDefenseChallenger_CopycatM_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatM_Defeat MSG_NORMAL
    return

TitleDefense_Copycat_Female:
    setvar 0x5029 7
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatF_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatF_PreBattle MSG_NORMAL
    trainerbattle3 0x0 584 0x100 gText_AscensionTower_TitleDefenseChallenger_CopycatF_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_CopycatF_Defeat MSG_NORMAL
    return

TitleDefense_Foreigner:
    setvar 0x5029 52
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Foreigner_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Foreigner_PreBattle MSG_NORMAL
    trainerbattle3 0x0 585 0x100 gText_AscensionTower_TitleDefenseChallenger_Foreigner_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Foreigner_Defeat MSG_NORMAL
    return

TitleDefense_Collin:
    setvar 0x5029 25
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Collin_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Collin_PreBattle MSG_NORMAL
    trainerbattle3 0x0 586 0x100 gText_AscensionTower_TitleDefenseChallenger_Collin_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Collin_Defeat MSG_NORMAL
    return

TitleDefense_Crystal:
    setvar 0x5029 28
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Crystal_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Crystal_PreBattle MSG_NORMAL
    trainerbattle3 0x0 587 0x100 gText_AscensionTower_TitleDefenseChallenger_Crystal_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Crystal_Defeat MSG_NORMAL
    return

TitleDefense_Irene:
    setvar 0x5029 89
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Irene_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Irene_PreBattle MSG_NORMAL
    trainerbattle3 0x0 588 0x100 gText_AscensionTower_TitleDefenseChallenger_Irene_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Irene_Defeat MSG_NORMAL
    return

TitleDefense_Ronald:
    setvar 0x5029 90
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ronald_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ronald_PreBattle MSG_NORMAL
    trainerbattle3 0x0 589 0x100 gText_AscensionTower_TitleDefenseChallenger_Ronald_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Ronald_Defeat MSG_NORMAL
    return

TitleDefense_Kurtis:
    setvar 0x5029 87
    showsprite 0x2
    applymovement 0x2 m_ChallengerWalksToPlayerAsChampion
    waitmovement 0x2
    msgbox gText_AscensionTower_TitleDefenseChallenger_Kurtis_Intro MSG_NORMAL
    playbgm 344 @ PWT Lobby
    msgbox gText_AscensionTower_TitleDefenseChallenger_Kurtis_PreBattle MSG_NORMAL
    trainerbattle3 0x0 590 0x100 gText_AscensionTower_TitleDefenseChallenger_Kurtis_PostBattle
    msgbox gText_AscensionTower_TitleDefenseChallenger_Kurtis_Defeat MSG_NORMAL
    return

.global MapScript_AscensionTower_HallOfFame
MapScript_AscensionTower_HallOfFame:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_AscensionTower_E4_OnWarp
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AscensionTower_HallOfFame
    .byte MAP_SCRIPT_TERMIN

LevelScripts_AscensionTower_HallOfFame:
    levelscript 0x406C 0xF LevelScript_AscensionTower_HallOfFame_Registration
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_HallOfFame_Registration:
    lockall
    pause DELAY_HALFSECOND
    setflag 0x3C @ Hide Selene in HoF Room in repeat visits
    compare 0x4070 0x3 @ Player has completed the postcredits sequence (i.e. they are now defending their title)
    if equal _goto HallOfFame_RegistrationTitleDefense
    applymovement 0x1 m_SeleneWalksToHallOfFameMachine 
    applymovement PLAYER m_PlayerWalksToHallOfFameMachine
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    applymovement 0x1 m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_AscensionTower_ChampionSelene_ExplainingHallOfFame MSG_NORMAL
    applymovement 0x1 m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_AscensionTower_ChampionSelene_UrgingPlayerToEnterHallOfFame MSG_NORMAL
    applymovement PLAYER m_PlayerApproachesHallOfFameMachine
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    goto HallOfFameCommon
    end

HallOfFame_RegistrationTitleDefense:
    applymovement PLAYER m_PlayerWalksToHallOfFameMachine
    waitmovement PLAYER
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    msgbox gText_AscensionTower_HallOfFame_PlayerIsDefendingTheirTitle MSG_NORMAL
    goto HallOfFameCommon
    end

HallOfFameCommon:
    doanimation 0x3E @ Place pokeballs into the machine
    waitanimation 0x3E
    pause 0x28
    special 0xA9 @ Unclear, but Vanilla FR does it here
    special 0x0 @ Heal the party
    callasm ResetAllLegendaries
    sethealingplace 0x1 @ Player healing place is now their home
    fadescreenspeed FADEOUT_BLACK 0x18
    setvar 0x406F 0x1 @ Credits are active
    special 0x110 @ Trigger HoF, which will warp the player to Tsarvosa City (Indigo Plateau, in Vanilla FR)
    waitstate
    releaseall
    end

@ This is a workaround for the warp back to the elevator being buggy with warp tiles...
.global TileScript_AscensionTower_ReturnToElevator
TileScript_AscensionTower_ReturnToElevator:
    setvar 0x4000 0x1
    warp 1 107 0
    end

.global EventScript_AscensionTower_EliteFourHannah
EventScript_AscensionTower_EliteFourHannah:
    lock
    faceplayer
    checkflag 0x82C @ Game is cleared
    if SET _goto HannahRematch
    checkflag 0x4B8 @ Hannah Defeated
    if SET _goto HannahChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_HannahIntro MSG_NORMAL
    trainerbattle3 0x0 520 0x100 gText_AscensionTower_EliteFour_HannahDefeat
    setflag 0x4B8 @ Hannah Defeated
    msgbox gText_AscensionTower_EliteFour_HannahChat MSG_NORMAL
    call OpenHannahDoor
    end

OpenHannahDoor:
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomOneFloor Passable
    setmaptile 0x6 0xC RoomOneFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    return

HannahChat:
    msgbox gText_AscensionTower_EliteFour_HannahChat MSG_NORMAL
    end

HannahRematch:
    checkflag 0x4B8 @ Hannah Defeated
    if SET _goto HannahRematchChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_HannahRematchIntro MSG_NORMAL
    trainerbattle3 0x0 564 0x100 gText_AscensionTower_EliteFour_HannahRematchDefeat
    setflag 0x4B8 @ Hannah Defeated
    msgbox gText_AscensionTower_EliteFour_HannahRematchChat MSG_NORMAL
    call OpenHannahDoor
    end

HannahRematchChat:
    msgbox gText_AscensionTower_EliteFour_HannahRematchChat MSG_NORMAL
    end

.global EventScript_AscensionTower_EliteFourLucas
EventScript_AscensionTower_EliteFourLucas:
    lock
    faceplayer
    checkflag 0x82C @ Game is cleared
    if SET _goto LucasRematch
    checkflag 0x4B9 @ Lucas Defeated
    if SET _goto LucasChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_LucasIntro MSG_NORMAL
    trainerbattle3 0x0 521 0x100 gText_AscensionTower_EliteFour_LucasDefeat
    setflag 0x4B9 @ Lucas Defeated
    msgbox gText_AscensionTower_EliteFour_LucasChat MSG_NORMAL
    call OpenLucasDoor
    end

OpenLucasDoor:
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomTwoFloor Passable
    setmaptile 0x6 0xC RoomTwoFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    return

LucasChat:
    msgbox gText_AscensionTower_EliteFour_LucasChat MSG_NORMAL
    end

LucasRematch:
    checkflag 0x4B9 @ Lucas Defeated
    if SET _goto LucasRematchChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_LucasRematchIntro MSG_NORMAL
    trainerbattle3 0x0 565 0x100 gText_AscensionTower_EliteFour_LucasRematchDefeat
    setflag 0x4B9 @ Lucas Defeated
    msgbox gText_AscensionTower_EliteFour_LucasRematchChat MSG_NORMAL
    call OpenLucasDoor
    end

LucasRematchChat:
    msgbox gText_AscensionTower_EliteFour_LucasRematchChat MSG_NORMAL
    end

.global EventScript_AscensionTower_EliteFourJenna
EventScript_AscensionTower_EliteFourJenna:
    lock
    faceplayer
    checkflag 0x82C @ Game is cleared
    if SET _goto JennaRematch
    checkflag 0x4BA @ Jenna Defeated
    if SET _goto JennaChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_JennaIntro MSG_NORMAL
    trainerbattle3 0x0 522 0x100 gText_AscensionTower_EliteFour_JennaDefeat
    setflag 0x4BA @ Jenna Defeated
    msgbox gText_AscensionTower_EliteFour_JennaChat MSG_NORMAL
    call OpenJennaDoor
    end

OpenJennaDoor:
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomThreeFloor Passable
    setmaptile 0x6 0xC RoomThreeFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    return

JennaChat:
    msgbox gText_AscensionTower_EliteFour_JennaChat MSG_NORMAL
    end

JennaRematch:
    checkflag 0x4BA @ Jenna Defeated
    if SET _goto JennaRematchChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_JennaRematchIntro MSG_NORMAL
    trainerbattle3 0x0 566 0x100 gText_AscensionTower_EliteFour_JennaRematchDefeat
    setflag 0x4BA @ Jenna Defeated
    msgbox gText_AscensionTower_EliteFour_JennaRematchChat MSG_NORMAL
    call OpenJennaDoor
    end

JennaRematchChat:
    msgbox gText_AscensionTower_EliteFour_JennaRematchChat MSG_NORMAL
    end

.global EventScript_AscensionTower_EliteFourThomas
EventScript_AscensionTower_EliteFourThomas:
    lock
    faceplayer
    checkflag 0x82C @ Game is cleared
    if SET _goto ThomasRematch
    checkflag 0x4BB @ Thomas Defeated
    if SET _goto ThomasChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_ThomasIntro MSG_NORMAL
    trainerbattle3 0x0 523 0x100 gText_AscensionTower_EliteFour_ThomasDefeat
    setflag 0x4BB @ Thomas Defeated
    msgbox gText_AscensionTower_EliteFour_ThomasChat MSG_NORMAL
    call OpenThomasDoor
    end

OpenThomasDoor:
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomFourFloor Passable
    setmaptile 0x6 0xC RoomFourFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    return

ThomasChat:
    msgbox gText_AscensionTower_EliteFour_ThomasChat MSG_NORMAL
    end

ThomasRematch:
    checkflag 0x4BB @ Thomas Defeated
    if SET _goto ThomasRematchChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_ThomasRematchIntro MSG_NORMAL
    trainerbattle3 0x0 567 0x100 gText_AscensionTower_EliteFour_ThomasRematchDefeat
    setflag 0x4BB @ Thomas Defeated
    msgbox gText_AscensionTower_EliteFour_ThomasRematchChat MSG_NORMAL
    call OpenThomasDoor
    end

ThomasRematchChat:
    msgbox gText_AscensionTower_EliteFour_ThomasRematchChat MSG_NORMAL
    end

m_YaelStartsElevator: .byte walk_left, walk_left, look_up, end_m
m_YaelReturnsFromElevator: .byte walk_right, walk_right, look_down, end_m
m_ApproachEliteFour: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_ApproachChampion: .byte walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, end_m
m_ReigningChampionWalksToHallOfFame: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, set_invisible, end_m
m_PlayerWalksToHallOfFame: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_SeleneWalksToHallOfFameMachine: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, look_up, end_m 
m_PlayerWalksToHallOfFameMachine: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerApproachesHallOfFameMachine: .byte walk_up_very_slow, end_m
m_PlayerWalksToTakeChampionsPlace: .byte  walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, look_down, end_m
m_ChallengerWalksToPlayerAsChampion: .byte walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, look_up, pause_long, pause_long, pause_long, pause_long, pause_long, end_m
m_ChallengerLeavesTheRoom: .byte walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, look_down, end_m
m_CameraTitleDefensePanDown: .byte walk_down, walk_down, end_m
m_CameraTitleDefensePanUp: .byte walk_up, walk_up, end_m
