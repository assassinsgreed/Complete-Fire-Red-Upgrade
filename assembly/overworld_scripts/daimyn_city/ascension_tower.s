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
    sethealingplace 0xA @ Originally Indigo Plateau
    call ResetRoute11PlutoEventOnWhiteout
    call ResetUteyaVillageGymFlagsOnWhiteout
    end

LevelScripts_AscensionTower:
    levelscript 0x406C 0x1 LevelScript_AscensionTower_RegisteringForEliteFourChallenge
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_AscensionTower_RegisteringForEliteFourChallenge:
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
    msgbox gText_AscensionTower_EliteFourChallengeRegistration_RivalUnderstandsChallenge MSG_NORMAL
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
    msgbox gText_AscensionTower_BattleTowerAttendant_Introduction MSG_KEEPOPEN
    multichoiceoption gText_Yes 0
	multichoiceoption gText_Info 1
	multichoiceoption gText_No 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, TakeBattleTowerChallenge
	case 1, BattleTowerInfo
	case 2, AttendantChoseNo
    goto AttendantChoseNo

TakeBattleTowerChallenge:
    @ Later, perform a check here for the champions flag
    msgbox gText_AscensionTower_BattleTowerAttendant_NotChampion MSG_NORMAL
    release
    end

BattleTowerInfo:
    msgbox gText_AscensionTower_EliteFourAttendant_BattleTowerInfo MSG_NORMAL
    goto EventScript_AscensionTower_BattleTowerAttendant

.global EventScript_AscensionTower_EliteFourAttendant
EventScript_AscensionTower_EliteFourAttendant:
    lock
    msgbox gText_AscensionTower_EliteFourAttendant_Introduction MSG_KEEPOPEN
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

TakeEliteFourChallenge:
    checkitem ITEM_VICTORY_FLAG 0x1
    compare LASTRESULT TRUE
    if notequal _goto NoVictoryFlag
    clearflag 0x4B8 @ E4 Hannah defeated
    clearflag 0x4B9 @ E4 Lucas defeated
    clearflag 0x4BA @ E4 Jenna defeated
    clearflag 0x4BB @ E4 Thomas defeated 
    msgbox gText_AscensionTower_EliteFourAttendant_GettingTheGate MSG_NORMAL
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
    release
    end

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
    checkflag 0x4BC @ Beat Selene
    if SET _goto RecordsBoard_PostChampion
    msgbox gText_AscensionTower_RecordsSign_NotOnBoard MSG_SIGN
    end

RecordsBoard_PostChampion:
    @ TODO: Populate later. Should track # of times player has defended their title and battle tower records
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
    msgbox gText_AscensionTower_ElevatorAttendant_FirstFloor MSG_NORMAL
    setdynamicwarp 1 75 0
    goto AscensionTowerElevatorTravel

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
    @ TODO Later: Handle when player is already champion
    npcchatwithmovement gText_AscensionTower_ElevatorAttendant_PriorToChampion m_LookDown
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
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_AscensionTower_E4_OnWarp
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AscensionTower_E4_ChallengingEliteFour
    .byte MAP_SCRIPT_TERMIN

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
    playbgm 345 @ N's farewell
    msgbox gText_AscensionTower_ChampionSelene_PostBattle MSG_NORMAL
    applymovement 0x1 m_ReigningChampionWalksToHallOfFame
    applymovement PLAYER m_PlayerWalksToHallOfFame
    waitmovement PLAYER
    setflag 0x4BC @ Champion Selene defeated. This is never reset as it's used to determine if the player is in the postgame
    clearflag 0x6C @ Post-Credits NPCs will appear
    clearflag 0x9D @ Postgame NPCs will now appear
    setvar 0x4070 0x1 @ Trigger postcredits upon returning to Anthra Town
    warp 1 80 0
    end

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
    checkflag 0x4B8 @ Hannah Defeated
    if SET _goto HannahChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_HannahIntro MSG_NORMAL
    trainerbattle3 0x0 520 0x100 gText_AscensionTower_EliteFour_HannahDefeat
    setflag 0x4B8 @ Hannah Defeated
    msgbox gText_AscensionTower_EliteFour_HannahChat MSG_NORMAL
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomOneFloor Passable
    setmaptile 0x6 0xC RoomOneFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    end

HannahChat:
    msgbox gText_AscensionTower_EliteFour_HannahChat MSG_NORMAL
    end

.global EventScript_AscensionTower_EliteFourLucas
EventScript_AscensionTower_EliteFourLucas:
    lock
    faceplayer
    checkflag 0x4B9 @ Lucas Defeated
    if SET _goto LucasChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_LucasIntro MSG_NORMAL
    trainerbattle3 0x0 521 0x100 gText_AscensionTower_EliteFour_LucasDefeat
    setflag 0x4B9 @ Lucas Defeated
    msgbox gText_AscensionTower_EliteFour_LucasChat MSG_NORMAL
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomTwoFloor Passable
    setmaptile 0x6 0xC RoomTwoFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    end

LucasChat:
    msgbox gText_AscensionTower_EliteFour_LucasChat MSG_NORMAL
    end

.global EventScript_AscensionTower_EliteFourJenna
EventScript_AscensionTower_EliteFourJenna:
    lock
    faceplayer
    checkflag 0x4BA @ Jenna Defeated
    if SET _goto JennaChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_JennaIntro MSG_NORMAL
    trainerbattle3 0x0 522 0x100 gText_AscensionTower_EliteFour_JennaDefeat
    setflag 0x4BA @ Jenna Defeated
    msgbox gText_AscensionTower_EliteFour_JennaChat MSG_NORMAL
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomThreeFloor Passable
    setmaptile 0x6 0xC RoomThreeFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    end

JennaChat:
    msgbox gText_AscensionTower_EliteFour_JennaChat MSG_NORMAL
    end

@ TODO Later: Thomas will need unique dialog if the player has become champion already
.global EventScript_AscensionTower_EliteFourThomas
EventScript_AscensionTower_EliteFourThomas:
    lock
    faceplayer
    checkflag 0x4BB @ Thomas Defeated
    if SET _goto ThomasChat
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_AscensionTower_EliteFour_ThomasIntro MSG_NORMAL
    trainerbattle3 0x0 523 0x100 gText_AscensionTower_EliteFour_ThomasDefeat
    setflag 0x4BB @ Thomas Defeated
    msgbox gText_AscensionTower_EliteFour_ThomasChat MSG_NORMAL
    pause DELAY_HALFSECOND
    playse 0x8 @ Door Open
    setmaptile 0x6 0xB RoomFourFloor Passable
    setmaptile 0x6 0xC RoomFourFloorShaded Passable
    special 0x8E
    addvar 0x406C 0x1 @ Elevator will take player to the next floor
    end

ThomasChat:
    msgbox gText_AscensionTower_EliteFour_ThomasChat MSG_NORMAL
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
