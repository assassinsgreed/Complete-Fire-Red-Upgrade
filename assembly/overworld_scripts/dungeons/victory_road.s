.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ GroundTile, 0x281
.equ Passable, 0x0

@ Victory Road puzzles
.global MapScript_VictoryRoad_1F
MapScript_VictoryRoad_1F:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_VictoryRoad1F_Puzzles
    .byte MAP_SCRIPT_TERMIN

.global MapScript_VictoryRoad_2F
MapScript_VictoryRoad_2F:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_VictoryRoad2F_Puzzles
    .byte MAP_SCRIPT_TERMIN

.global MapScript_VictoryRoad_3F
MapScript_VictoryRoad_3F:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_VictoryRoad3F_Puzzles
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_VictoryRoad1F_Puzzles:
    setworldmapflag 0x8AF @ Been to Victory Road
    checkflag 0x281 @ 1F Left puzzle
    if SET _call Hide1FLeftPuzzleRock
    checkflag 0x282 @ 1F Middle puzzle
    if SET _call Hide1FMiddlePuzzleRock
    checkflag 0x283 @ 1F Right puzzle
    if SET _call Hide1FRightPuzzleRock
    end

MapLoadScript_VictoryRoad2F_Puzzles:
    checkflag 0x284 @ 2F Left puzzle
    if SET _call Hide2FLeftPuzzleRock
    checkflag 0x285 @ 2F Right puzzle
    if SET _call Hide2FRightPuzzleRock
    end

MapLoadScript_VictoryRoad3F_Puzzles:
    checkflag 0x286 @ 3F Left puzzle
    if SET _call Hide3FLeftPuzzleRock
    checkflag 0x287 @ 3F Right puzzle
    if SET _call Hide3FRightPuzzleRock
    end

.global TileEvent_VictoryRoad_1F_LeftPuzzleCheck
TileEvent_VictoryRoad_1F_LeftPuzzleCheck:
    checkflag 0x281 @ Left puzzle solved
    if equal _goto End
    lock
    call Hide1FLeftPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x281 @ Left puzzle solved
    release
    end

.global TileEvent_VictoryRoad_1F_MiddlePuzzleCheck
TileEvent_VictoryRoad_1F_MiddlePuzzleCheck:
    checkflag 0x282 @ Middle puzzle solved
    if equal _goto End
    lock
    call Hide1FMiddlePuzzleRock
    call PuzzleSolvedCommon
    setflag 0x282 @ Middle puzzle solved
    release
    end

.global TileEvent_VictoryRoad_1F_RightPuzzleCheck
TileEvent_VictoryRoad_1F_RightPuzzleCheck:
    checkflag 0x283 @ Right puzzle solved
    if equal _goto End
    lock
    call Hide1FRightPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x283 @ Right puzzle solved
    release
    end

.global TileEvent_VictoryRoad_2F_LeftPuzzleCheck
TileEvent_VictoryRoad_2F_LeftPuzzleCheck:
    checkflag 0x284 @ Left puzzle solved
    if equal _goto End
    lock
    call Hide2FLeftPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x284 @ Left puzzle solved
    release
    end

.global TileEvent_VictoryRoad_2F_RightPuzzleCheck
TileEvent_VictoryRoad_2F_RightPuzzleCheck:
    checkflag 0x285 @ Right puzzle solved
    if equal _goto End
    lock
    call Hide2FRightPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x285 @ Right puzzle solved
    release
    end

.global TileEvent_VictoryRoad_3F_LeftPuzzleCheck
TileEvent_VictoryRoad_3F_LeftPuzzleCheck:
    checkflag 0x286 @ Left puzzle solved
    if equal _goto End
    lock
    call Hide3FLeftPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x286 @ Left puzzle solved
    release
    end

.global TileEvent_VictoryRoad_3F_RightPuzzleCheck
TileEvent_VictoryRoad_3F_RightPuzzleCheck:
    checkflag 0x287 @ Right puzzle solved
    if equal _goto End
    lock
    call Hide3FRightPuzzleRock
    call PuzzleSolvedCommon
    setflag 0x287 @ Right puzzle solved
    release
    end

@ Puzzle is managed by var 0x4064 being 0x63 (on switch), which we need to reset after every puzzle
PuzzleSolvedCommon:
    setvar 0x8004 0x0 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x3 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x20 @ This controls how long the overall animation lasts
	setvar 0x8007 0x2 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    pause DELAY_HALFSECOND
    special 0x8E
    waitstate
    msgbox gText_VictoryRoad_PuzzleSolvedCommon MSG_NORMAL
    setvar 0x4064 0x0 @ Reset for other puzzles
    return

Hide1FLeftPuzzleRock:
    setmaptile 0xB 0xF GroundTile Passable
    setmaptile 0xC 0xF GroundTile Passable
    setmaptile 0xD 0xF GroundTile Passable
    setmaptile 0xB 0x10 GroundTile Passable
    setmaptile 0xC 0x10 GroundTile Passable
    setmaptile 0xD 0x10 GroundTile Passable
    setmaptile 0xB 0x11 GroundTile Passable
    setmaptile 0xC 0x11 GroundTile Passable
    setmaptile 0xD 0x11 GroundTile Passable
    movesprite 1 0xD 0xB
    movesprite2 1 0xD 0xB
    return

Hide1FMiddlePuzzleRock:
    setmaptile 0x1D 0xA GroundTile Passable
    setmaptile 0x1E 0xA GroundTile Passable
    setmaptile 0x1F 0xA GroundTile Passable
    setmaptile 0x1D 0xB GroundTile Passable
    setmaptile 0x1E 0xB GroundTile Passable
    setmaptile 0x1F 0xB GroundTile Passable
    setmaptile 0x1D 0xC GroundTile Passable
    setmaptile 0x1E 0xC GroundTile Passable
    setmaptile 0x1F 0xC GroundTile Passable
    movesprite 2 0x1C 0x9
    movesprite2 2 0x1C 0x9
    return

Hide1FRightPuzzleRock:
    setmaptile 0x20 0xF GroundTile Passable
    setmaptile 0x21 0xF GroundTile Passable
    setmaptile 0x22 0xF GroundTile Passable
    setmaptile 0x20 0x10 GroundTile Passable
    setmaptile 0x21 0x10 GroundTile Passable
    setmaptile 0x22 0x10 GroundTile Passable
    setmaptile 0x20 0x11 GroundTile Passable
    setmaptile 0x21 0x11 GroundTile Passable
    setmaptile 0x22 0x11 GroundTile Passable
    movesprite 3 0x25 0x12
    movesprite2 3 0x25 0x12
    return

Hide2FLeftPuzzleRock:
    setmaptile 0x8 0x10 GroundTile Passable
    setmaptile 0x9 0x10 GroundTile Passable
    setmaptile 0xA 0x10 GroundTile Passable
    setmaptile 0x8 0x11 GroundTile Passable
    setmaptile 0x9 0x11 GroundTile Passable
    setmaptile 0xA 0x11 GroundTile Passable
    setmaptile 0x8 0x12 GroundTile Passable
    setmaptile 0x9 0x12 GroundTile Passable
    setmaptile 0xA 0x12 GroundTile Passable
    movesprite 1 0x2 0x14
    movesprite2 1 0x2 0x14
    return

Hide2FRightPuzzleRock:
    setmaptile 0x1E 0x12 GroundTile Passable
    setmaptile 0x1F 0x12 GroundTile Passable
    setmaptile 0x20 0x12 GroundTile Passable
    setmaptile 0x1E 0x13 GroundTile Passable
    setmaptile 0x1F 0x13 GroundTile Passable
    setmaptile 0x20 0x13 GroundTile Passable
    setmaptile 0x1E 0x14 GroundTile Passable
    setmaptile 0x1F 0x14 GroundTile Passable
    setmaptile 0x20 0x14 GroundTile Passable
    movesprite 2 0x29 0xA
    movesprite2 2 0x29 0xA
    return

Hide3FLeftPuzzleRock:
    setmaptile 0x2 0xC GroundTile Passable
    setmaptile 0x3 0xC GroundTile Passable
    setmaptile 0x4 0xC GroundTile Passable
    setmaptile 0x2 0xD GroundTile Passable
    setmaptile 0x3 0xD GroundTile Passable
    setmaptile 0x4 0xD GroundTile Passable
    setmaptile 0x2 0xE GroundTile Passable
    setmaptile 0x3 0xE GroundTile Passable
    setmaptile 0x4 0xE GroundTile Passable
    movesprite 1 0x6 0x3
    movesprite2 1 0x6 0x3
    return

Hide3FRightPuzzleRock:
    setmaptile 0x17 0xA GroundTile Passable
    setmaptile 0x18 0xA GroundTile Passable
    setmaptile 0x19 0xA GroundTile Passable
    setmaptile 0x17 0xB GroundTile Passable
    setmaptile 0x18 0xB GroundTile Passable
    setmaptile 0x19 0xB GroundTile Passable
    setmaptile 0x17 0xC GroundTile Passable
    setmaptile 0x18 0xC GroundTile Passable
    setmaptile 0x19 0xC GroundTile Passable
    movesprite 2 0xB 0xD
    movesprite2 2 0xB 0xD
    return

@ NPCs, items, and signs
.global EventScript_VictoryRoad_CoolTrainerTimothy
EventScript_VictoryRoad_CoolTrainerTimothy:
    trainerbattle0 0x0 498 0x0 gText_VictoryRoad_CoolTrainerTimothy_Intro gText_VictoryRoad_CoolTrainerTimothy_Defeat
    msgbox gText_VictoryRoad_CoolTrainerTimothy_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerJonathan
EventScript_VictoryRoad_CoolTrainerJonathan:
    trainerbattle0 0x0 499 0x0 gText_VictoryRoad_CoolTrainerJonathan_Intro gText_VictoryRoad_CoolTrainerJonathan_Defeat
    msgbox gText_VictoryRoad_CoolTrainerJonathan_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerSatoshi
EventScript_VictoryRoad_CoolTrainerSatoshi:
    trainerbattle0 0x0 500 0x0 gText_VictoryRoad_CoolTrainerSatoshi_Intro gText_VictoryRoad_CoolTrainerSatoshi_Defeat
    msgbox gText_VictoryRoad_CoolTrainerSatoshi_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerCourtney
EventScript_VictoryRoad_CoolTrainerCourtney:
    trainerbattle0 0x0 501 0x0 gText_VictoryRoad_CoolTrainerCourtney_Intro gText_VictoryRoad_CoolTrainerCourtney_Defeat
    msgbox gText_VictoryRoad_CoolTrainerCourtney_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerTheresa
EventScript_VictoryRoad_CoolTrainerTheresa:
    trainerbattle0 0x0 502 0x0 gText_VictoryRoad_CoolTrainerTheresa_Intro gText_VictoryRoad_CoolTrainerTheresa_Defeat
    msgbox gText_VictoryRoad_CoolTrainerTheresa_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerAbdul
EventScript_VictoryRoad_CoolTrainerAbdul:
    trainerbattle0 0x0 503 0x0 gText_VictoryRoad_CoolTrainerAbdul_Intro gText_VictoryRoad_CoolTrainerAbdul_Defeat
    msgbox gText_VictoryRoad_CoolTrainerAbdul_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerArthur
EventScript_VictoryRoad_CoolTrainerArthur:
    trainerbattle0 0x0 504 0x0 gText_VictoryRoad_CoolTrainerArthur_Intro gText_VictoryRoad_CoolTrainerArthur_Defeat
    msgbox gText_VictoryRoad_CoolTrainerArthur_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerKelly
EventScript_VictoryRoad_CoolTrainerKelly:
    trainerbattle0 0x0 505 0x0 gText_VictoryRoad_CoolTrainerKelly_Intro gText_VictoryRoad_CoolTrainerKelly_Defeat
    msgbox gText_VictoryRoad_CoolTrainerKelly_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerLydia
EventScript_VictoryRoad_CoolTrainerLydia:
    trainerbattle0 0x0 506 0x0 gText_VictoryRoad_CoolTrainerLydia_Intro gText_VictoryRoad_CoolTrainerLydia_Defeat
    msgbox gText_VictoryRoad_CoolTrainerLydia_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerRobin
EventScript_VictoryRoad_CoolTrainerRobin:
    trainerbattle0 0x0 507 0x0 gText_VictoryRoad_CoolTrainerRobin_Intro gText_VictoryRoad_CoolTrainerRobin_Defeat
    msgbox gText_VictoryRoad_CoolTrainerRobin_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerLuigi
EventScript_VictoryRoad_CoolTrainerLuigi:
    trainerbattle0 0x0 508 0x0 gText_VictoryRoad_CoolTrainerLuigi_Intro gText_VictoryRoad_CoolTrainerLuigi_Defeat
    msgbox gText_VictoryRoad_CoolTrainerLuigi_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_CoolTrainerDahlia
EventScript_VictoryRoad_CoolTrainerDahlia:
    trainerbattle0 0x0 509 0x0 gText_VictoryRoad_CoolTrainerDahlia_Intro gText_VictoryRoad_CoolTrainerDahlia_Defeat
    msgbox gText_VictoryRoad_CoolTrainerDahlia_Chat MSG_NORMAL
    end

.global EventScript_VictoryRoad_NurseCelia
EventScript_VictoryRoad_NurseCelia:
    faceplayer
    checktrainerflag 510
    if SET _goto NurseCeliaHeal
    trainerbattle2 0x0 510 0x0 gText_VictoryRoad_NurseCelia_Intro gText_VictoryRoad_NurseCelia_Defeat NurseCeliaHeal
    end

NurseCeliaHeal:
    msgbox gText_VictoryRoad_NurseCelia_Chat MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_VictoryRoad_NurseCelia_HealingComplete MSG_NORMAL
    end

.global EventScript_VictoryRoad_TM82_DragonTail
EventScript_VictoryRoad_TM82_DragonTail:
    setvar CHOSEN_ITEM ITEM_TM82
    call ItemScript_Common_FindTM
    end

.global EventScript_VictoryRoad_TM52_FocusBlast
EventScript_VictoryRoad_TM52_FocusBlast:
    setvar CHOSEN_ITEM ITEM_TM52
    call ItemScript_Common_FindTM
    end

.global SignScript_VictoryRoad_PuzzleTips
SignScript_VictoryRoad_PuzzleTips:
    msgbox gText_VictoryRoad_PuzzleTipsSign MSG_SIGN
    end

@ Cutscenes
.equ Rival, 0x1

.global MapScript_VictoryRoadPeak
MapScript_VictoryRoadPeak:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_VictoryRoadPeak
	.byte MAP_SCRIPT_TERMIN

LevelScripts_VictoryRoadPeak:
	levelscript 0x406E 0x0 LevelScript_VictoryRoadPeak_BattleForVictoryFlag
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_VictoryRoadPeak_BattleForVictoryFlag:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x8
    if equal _call PlayerWalkRight_Return
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    playse 0x9 @ Exit Room
    showsprite Rival
    pause DELAY_HALFSECOND
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_VictoryRoad_RivalGreetsPlayer MSG_NORMAL
    applymovement PLAYER m_PlayerAndRivalWalkToVictoryFlag
    applymovement Rival m_PlayerAndRivalWalkToVictoryFlag
    waitmovement ALLEVENTS
    pause 0x10
    applymovement PLAYER m_Surprise
    applymovement Rival m_Surprise
    sound 0x15 @ Exclaim
    msgbox gText_VictoryRoad_RivalSeesSingleFlag MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_VictoryRoad_RivalUnderstandsSingleFlag MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_VictoryRoad_RivalAcknowledgesLoomingBattle MSG_YESNO
    compare LASTRESULT NO
    if notequal _call PlayerUnderstandsBattleIsComing
    if equal _call PlayerDoesNotUnderstandBattleIsComing
    msgbox gText_VictoryRoad_RivalIssuesBattle_TakingPositions MSG_NORMAL
    applymovement Rival m_RivalTakesPosition
    applymovement PLAYER m_PlayerTakesPosition
    waitmovement ALLEVENTS
    playbgm 0x195 @ Rival's theme
    msgbox gText_VictoryRoad_RivalIssuesBattle_AsksToTakeBattleSeriously MSG_NORMAL
    msgbox gText_VictoryRoad_RivalIssuesBattle_BattleIntro MSG_NORMAL
    call SetupMugshotRival
    @ Figure out which team the rival uses
    copyvar 0x4001 0x408E
    setvar 0x4000 511 @ trainer ID, which is 511 + 0-7 depending on value in 0x408E
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x4000 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_VictoryRoad_RivalLosesBattle
    msgbox gText_VictoryRoad_RivalAcceptsLoss MSG_NORMAL
    applymovement Rival m_WalkRight
    applymovement PLAYER m_WalkLeft
    waitmovement ALLEVENTS
    playbgm 0x114 0x0 @ Unwavering emotions
    msgbox gText_VictoryRoad_RivalCheersPlayerOn MSG_NORMAL
    applymovement Rival m_LookDown
    pause DELAY_HALFSECOND
    setfieldeffectarg 0, 0x8 @ Rival X
	setfieldeffectarg 1, 0xC @ Rival Y
	dofieldeffect 30 @FLDEFF_NPCFLY_OUT
    pause 0x9 @ Delay just long enough for the bird to connect with the rival
    applymovement Rival m_RivalJumpsOntoBird
	waitfieldeffect 30 @FLDEFF_NPCFLY_OUT
    fadedefaultbgm
    hidesprite Rival
    pause DELAY_1SECOND
    applymovement PLAYER m_SlowlyApproachVictoryFlag
    waitmovement PLAYER
    pause DELAY_1SECOND
    hidesprite 0x2 @ Flag
    fanfare 0x10C @ Big celebration
    msgbox gText_VictoryRoad_PlayerReceivesVictoryFlag MSG_KEEPOPEN
    waitfanfare
    closemessage
    additem ITEM_VICTORY_FLAG 0x1
    setflag 0x72 @ Victory Flag claimed
    clearflag 0x06B @ Rival appears in Daimyn City for training battle 
    setvar 0x406E 0x1 @ cutscenes over
    end

PlayerUnderstandsBattleIsComing:
    msgbox gText_VictoryRoad_RivalIssuesBattle_PlayerUnderstands MSG_NORMAL
    return

PlayerDoesNotUnderstandBattleIsComing:
    msgbox gText_VictoryRoad_RivalIssuesBattle_PlayerDoesNotUnderstand MSG_NORMAL
    return

m_PlayerAndRivalWalkToVictoryFlag: .byte walk_up, walk_up, walk_up, end_m
m_RivalTakesPosition: .byte walk_left, look_right, end_m
m_PlayerTakesPosition: .byte walk_right, look_left, end_m
m_RivalJumpsOntoBird: .byte jump_onspot_down, set_invisible, end_m
m_SlowlyApproachVictoryFlag: .byte walk_up_very_slow, end_m
