.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Rival, 0x12 @ Person # 18
.equ PlutoGruntA, 0x13 @ Person # 19
.equ PlutoGruntB, 0x14 @ Person # 20
.equ PlutoGruntTrainer, 0x15 @ Person # 21
.equ Assistant, 0x16 @ Person # 22
.equ Route3RubarrStoryEventVar, 0x4057

.equ VarStoryMetAssistant, 0x1
.equ VarStoryPlayerBeatPluto, 0x2
.equ VarStoryPlayerGotDexNav, 0x3

.global MapScript_Route3
MapScript_Route3:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_Route3
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_Route3:
    compare Route3RubarrStoryEventVar VarStoryMetAssistant
    if lessthan _goto HideAssistant
    movesprite2 Assistant 0x04A 0x000E @ Update position of Assistant permanently
    compare Route3RubarrStoryEventVar VarStoryMetAssistant
    if greaterorequal _goto End
    goto HideAssistant

HideAssistant:
    setflag 0x32 @ hide assistant
    goto End

.global SignScript_Route3_TrainerTips
SignScript_Route3_TrainerTips:
    msgbox gText_Route3_TrainerTips MSG_SIGN
    end

.global SignScript_Route3_Navigation
SignScript_Route3_Navigation:
    msgbox gText_Route3_Navigation MSG_SIGN
    end

.global EventScript_Route3_FindTMTaunt
EventScript_Route3_FindTMTaunt:
    setvar CHOSEN_ITEM ITEM_TM12
    call ItemScript_Common_FindTM
    end

.global EventScript_Route3_PicknickerTana
EventScript_Route3_PicknickerTana:
    trainerbattle0 0x0 0x11 0x0 gText_Route3_PicknickerTana_Intro gText_Route3_PicknickerTana_Defeat
    msgbox gText_Route3_PicknickerTana_Chat MSG_NORMAL
    end

.global EventScript_Route3_BugCatcherIrwin
EventScript_Route3_BugCatcherIrwin:
    trainerbattle0 0x0 0x12 0x0 gText_Route3_BugCatcherIrwin_Intro gText_Route3_BugCatcherIrwin_Defeat
    msgbox gText_Route3_BugCatcherIrwin_Chat MSG_NORMAL
    end

.global EventScript_Route3_YoungsterLogan
EventScript_Route3_YoungsterLogan:
    trainerbattle0 0x0 0x13 0x0 gText_Route3_YoungsterLogan_Intro gText_Route3_YoungsterLogan_Defeat
    msgbox gText_Route3_YoungsterLogan_Chat MSG_NORMAL
    end

.global EventScript_Route3_TwinsNinaAndMeg_Nina
EventScript_Route3_TwinsNinaAndMeg_Nina:
    checktrainerflag 0x514 @ 500 + 14
    if SET _goto NinaDefeated
    trainerbattle0 0x0 0x14 0x0 gText_Route3_TwinsNinaAndMeg_Nina_Intro gText_Route3_TwinsNinaAndMeg_Nina_Defeat
    settrainerflag 0x514
    goto NinaDefeated

NinaDefeated:
    msgbox gText_Route3_TwinsNinaAndMeg_Nina_Chat MSG_NORMAL
    end

.global EventScript_Route3_TwinsNinaAndMeg_Meg
EventScript_Route3_TwinsNinaAndMeg_Meg:
    checktrainerflag 0x514 @ 500 + 14
    if SET _goto MegDefeated
    trainerbattle0 0x0 0x14 0x0 gText_Route3_TwinsNinaAndMeg_Meg_Intro gText_Route3_TwinsNinaAndMeg_Meg_Defeat
    settrainerflag 0x514
    goto MegDefeated

MegDefeated:
    msgbox gText_Route3_TwinsNinaAndMeg_Meg_Chat MSG_NORMAL
    end

.global EventScript_Route3_NinjaBoyBotan
EventScript_Route3_NinjaBoyBotan:
    trainerbattle0 0x0 0x15 0x0 gText_Route3_NinjaBoyBotan_Intro gText_Route3_NinjaBoyBotan_Defeat
    msgbox gText_Route3_NinjaBoyBotan_Chat MSG_NORMAL
    end

.global EventScript_Route3_RockerJude
EventScript_Route3_RockerJude:
    trainerbattle0 0x0 0x16 0x0 gText_Route3_RockerJude_Intro gText_Route3_RockerJude_Defeat
    msgbox gText_Route3_RockerJude_Chat MSG_NORMAL
    end

.global EventScript_Route3_TeamPlutoRaul
EventScript_Route3_TeamPlutoRaul:
    trainerbattle0 0x0 0x1D 0x0 gText_Route3_TeamPlutoRaul_Intro gText_Route3_TeamPlutoRaul_Defeat
    msgbox gText_Route3_TeamPlutoRaul_Chat MSG_NORMAL
    end

.global EventScript_Route3_Assistant
EventScript_Route3_Assistant:
    compare Route3RubarrStoryEventVar VarStoryPlayerBeatPluto
    if equal _goto ReturningDexNavs
    npcchat gText_Route3_Assistant
    end

ReturningDexNavs:
    compareplayerfacing INTERNAL_LEFT
    if equal _call MovePlayerBelowAssistantRight
    compareplayerfacing INTERNAL_RIGHT
    if equal _call MovePlayerBelowAssistantLeft
    waitmovement ALLEVENTS
    faceplayer
    msgbox gText_Route3_AssistantWelcomesPlayerBack MSG_NORMAL
    showsprite Rival
    movesprite Rival 0x49 0x14
    applymovement Rival m_RivalWalksUp
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookLeft
    msgbox gText_Route3_RivalJoinsPlayer MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    fanfare 0x13E
    msgbox gText_Route3_ReturningDexNavs MSG_KEEPOPEN
    waitfanfare
    msgbox gText_Route3_AssistantThanksPlayer MSG_NORMAL
    applymovement Assistant m_Question
    msgbox gText_Route3_AssistantClarifiesNames MSG_NORMAL
    applymovement Rival m_Joy
    msgbox gText_Route3_RivalConfirmsNames MSG_NORMAL
    applymovement Assistant m_Surprise
    msgbox gText_Route3_AssistantGivesDexNavs MSG_NORMAL
    fanfare 0x13E
    msgbox gText_Route3_ReceiveDexNav MSG_KEEPOPEN
    waitfanfare
    setflag 0x91E @ Show DexNav
    setflag 0x92A @ Show held items in DexNav UI
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_Route3_RivalCommentsOnDexNav MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_Route3_AssistantAsksIfYouNeedDexNavInstructions MSG_YESNO
    compare LASTRESULT YES
    if equal _call DexNavInstructions
    if notequal _call NoDexNavInstructions
    msgbox gText_Route3_AssistantContinuesOn MSG_NORMAL
    applymovement Assistant m_WalkRight
    waitmovement ALLEVENTS
    applymovement Assistant m_AssistantLeaves
    waitmovement ALLEVENTS
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    playbgm 0x195 @ Rival theme
    msgbox gText_Route3_RivalWantsToBattleAgain MSG_NORMAL
    fadedefaultbgm
    msgbox gText_Route3_RivalContinuesOn MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Rival m_WalkUp
    waitmovement ALLEVENTS
    applymovement Rival m_RivalWalksUp
    waitmovement ALLEVENTS
    setvar Route3RubarrStoryEventVar VarStoryPlayerGotDexNav
    hidesprite Rival
    hidesprite Assistant
    setflag 0x32 @ Hide assistant
    end

MovePlayerBelowAssistantRight:
    applymovement PLAYER m_TalkWithAssistantRight
    return

MovePlayerBelowAssistantLeft:
    applymovement PLAYER m_TalkWithAssistantLeft
    return

DexNavInstructions:
    playbgm 0x110 @ Follow me (instructions)
    msgbox gText_Route3_AssistantGivesDexNavInstructions MSG_NORMAL
    return

NoDexNavInstructions:
    msgbox gText_Route3_AssistantNoDexNavInstructions MSG_NORMAL
    return

.global TileScript_Route3_InitiateDexNavEvent
TileScript_Route3_InitiateDexNavEvent:
    lockall
    clearflag 0x31 @ Show rival and pluto grunts on route 3
    showsprite Rival
    playbgm 0x195
    msgbox gText_Route3_RivalArrives MSG_NORMAL
    call MovePlayerToLineUpWithRival
    applymovement Rival m_RivalMeetsPlayer
    waitmovement ALLEVENTS
    msgbox gText_Route3_RivalGymBadgeAcknowledgement MSG_YESNO
    compare LASTRESULT NO
    if equal _call PlayerDoesNotKnowWhyRivalIsHere
    compare LASTRESULT YES
    if equal _call PlayerKnowsWhyRivalIsHere
    msgbox gText_Route3_RivalInitiatesBattle MSG_NORMAL
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    trainerbattle3 0x0 0x1C 0x100 gText_Route3_BeatRival
    pause DELAY_HALFSECOND
    clearflag 0x32 @ Show Assistant
    showsprite Assistant
    msgbox gText_Route3_RivalAcceptsDefeat MSG_NORMAL
    applymovement PLAYER m_PlayerMoveToEncounterAssistant
    applymovement Rival m_RivalMoveToEncounterAssistant
    waitmovement ALLEVENTS
    applymovement PLAYER m_PlayerMovesUp
    applymovement Rival m_RivalMovesUp
    @ Assistant must be nearby, but offscreen, or else they can't move, so we spawn them out of sight, move them to the correct XY coords, then apply movement
    movesprite Assistant 0x4A 0x09
    applymovement Assistant m_AssistantWalkToAmbush
    waitmovement ALLEVENTS
    playbgm 0x19A @ Team Pluto encounter
    applymovement Assistant m_Surprise
    applymovement PLAYER m_Surprise
    applymovement Rival m_Surprise
    applymovement PlutoGruntA m_RunRight
    applymovement PlutoGruntB m_RunLeft
    waitmovement ALLEVENTS
    msgbox gText_Route3_PlutoGruntStopsAssistant MSG_NORMAL
    applymovement Assistant m_AssistantQuestioningAmbush
    waitmovement ALLEVENTS
    msgbox gText_Route3_AssistantQuestioningAmbush MSG_NORMAL
    msgbox gText_Route3_PlutoThreat MSG_NORMAL
    msgbox gText_Route3_AssistantRecognizesPluto MSG_NORMAL
    applymovement Assistant m_LookLeft
    msgbox gText_Route3_PlutoThreat2 MSG_NORMAL
    msgbox gText_Route3_AssistantSurrenders MSG_NORMAL
    applymovement Assistant m_LookRight
    applymovement PlutoGruntB m_Joy
    msgbox gText_Route3_PlutoDeparts MSG_NORMAL
    applymovement Assistant m_LookDown
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookRight
    applymovement PlutoGruntA m_PlutoRunsAway
    applymovement PlutoGruntB m_PlutoRunsAway
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookDown
    applymovement Rival m_LookDown
    applymovement PlutoGruntA m_PlutoRunsAway
    applymovement PlutoGruntB m_PlutoRunsAway
    waitmovement ALLEVENTS
    pause DELAY_1SECOND
    hidesprite PlutoGruntA
    hidesprite PlutoGruntB
    applymovement Rival m_LookUp
    msgbox gText_Route3_RivalCommentsOnPluto MSG_NORMAL
    playbgm 0x0124 @ Route 3 music
    applymovement PLAYER m_MeetAssistant
    applymovement Rival m_MeetAssistant
    waitmovement ALLEVENTS
    applymovement Assistant m_LookLeft
    msgbox gText_Route3_RivalSpeaksToAssistant MSG_NORMAL
    msgbox gText_Route3_AssistantRespondsToRival MSG_NORMAL
    applymovement PLAYER m_LookDown
    applymovement Rival m_LookUp
    msgbox gText_Route3_RivalRecruitsPlayer MSG_YESNO
    compare LASTRESULT NO
    if equal _call PlayerDoesNotWantToStopPluto
    compare LASTRESULT YES
    if equal _call PlayerWantsToStopPluto
    applymovement Rival m_LookDown
    waitmovement ALLEVENTS
    applymovement Rival m_Question
    pause DELAY_1SECOND
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookRight
    msgbox gText_Route3_RivalTracksPluto MSG_NORMAL
    msgbox gText_Route3_AssistantConfirms MSG_NORMAL
    msgbox gText_Route3_RivalSaysYoureTrainers MSG_NORMAL
    msgbox gText_Route3_AssistantExplainsRubarrDesert MSG_NORMAL
    msgbox gText_Route3_RivalThanksAssistant MSG_NORMAL
    applymovement PLAYER m_LookDown
    applymovement Rival m_LookUp
    msgbox gText_Route3_RivalUrgesPlayerToHurry MSG_NORMAL
    applymovement Rival m_PlutoRunsAway
    waitmovement ALLEVENTS
    hidesprite Rival
    movesprite2 Assistant 0x04A 0x000E @ Update position of Assistant permanently
    setflag 0x31 @ Hide rival on Route 3
    clearflag 0x33 @ Show Pluto grunts on route 3 & Rubarr Desert
    setvar Route3RubarrStoryEventVar VarStoryMetAssistant
    release
    end

MovePlayerToLineUpWithRival:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x12
    if equal _call PlayerWalkDown_Return
    compare 0x4001 0x14
    if greaterorequal _call PlayerWalkUp_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x14
    if greaterorequal _call PlayerWalkUp_Return
    applymovement PLAYER m_LookLeft
    return

PlayerDoesNotKnowWhyRivalIsHere:
    msgbox gText_Route3_PlayerDoesNotKnowWhyRivalIsHere MSG_NORMAL
    return

PlayerKnowsWhyRivalIsHere:
    msgbox gText_Route3_PlayerKnowsWhyRivalIsHere MSG_NORMAL
    return

PlayerDoesNotWantToStopPluto:
    msgbox gText_Route3_PlayerDoesNotAgreeToChallengePluto MSG_NORMAL
    return

PlayerWantsToStopPluto:
    msgbox gText_Route3_PlayerAgreesToChallengePluto MSG_NORMAL
    return

.global TileScript_Route3_PlayerHasNotDefeatedPluto
TileScript_Route3_PlayerHasNotDefeatedPluto:
    lockall
    compare Route3RubarrStoryEventVar VarStoryPlayerGotDexNav
    if greaterorequal _goto End
    applymovement Assistant m_Surprise
    waitmovement ALLEVENTS
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x004E
    if greaterorequal _call AssistantLookRight
    compare 0x4000 0x004E
    if lessthan _call AssistantLookUp
    msgbox gText_Route3_AssistantWhenPlayerHasToBeatPluto MSG_NORMAL
    applymovement PLAYER m_WalkDown
    applymovement Assistant m_LookDown
    waitmovement ALLEVENTS
    releaseall
    end

AssistantLookRight:
    applymovement Assistant m_LookRight
    waitmovement ALLEVENTS
    return

AssistantLookUp:
    applymovement Assistant m_LookUp
    waitmovement ALLEVENTS
    return

m_RivalMeetsPlayer: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_PlayerMoveToEncounterAssistant: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_RivalMoveToEncounterAssistant: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_PlayerMovesUp: .byte walk_up, walk_up, end_m
m_RivalMovesUp: .byte walk_right, walk_up, end_m
m_AssistantWalkToAmbush: .byte walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_AssistantQuestioningAmbush: .byte look_left, pause_long, pause_long, look_right, end_m
m_PlutoRunsAway: .byte run_down, run_down, run_down, run_down, run_down, run_down, end_m
m_MeetAssistant: .byte walk_up, walk_up, walk_left, walk_up, look_right, end_m
m_TalkWithAssistantRight: .byte walk_down, walk_left, look_up, end_m
m_TalkWithAssistantLeft: .byte walk_down, walk_right, look_up, end_m
m_RivalWalksUp: .byte walk_up, walk_up, walk_up, walk_up, walk_up, look_right, end_m
m_AssistantLeaves: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
