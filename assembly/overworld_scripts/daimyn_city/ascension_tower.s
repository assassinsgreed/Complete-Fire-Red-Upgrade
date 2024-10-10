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
    pause 0x10
    playse 0x26 @ Door shut
    setmaptile 0x9 0x8 0x284 0x0 @ shaded floor tile
    special 0x8E
    pause 0x10
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
    @ Later, perform a check here for the champions flag
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
    @ Later, show player's E4 and Battle Tower records
    msgbox gText_AscensionTower_RecordsSign MSG_SIGN
    end

m_PlayerWalksToRival: .byte walk_up, walk_up, walk_right, walk_right, walk_up, walk_up, look_right, end_m
m_WalkDownToDivider: .byte walk_down, walk_down, end_m
m_SeleneWalksToDuo: .byte walk_down, walk_down, walk_down, walk_down, walk_right, end_m
m_RivalWalksBesidePlayer: .byte walk_down, walk_left, end_m
m_SeleneLeaves: .byte walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_RivalLeaves: .byte walk_down, walk_down, walk_down, walk_left, walk_left, look_down, end_m
