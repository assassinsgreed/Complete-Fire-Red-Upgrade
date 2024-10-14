.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Route 1
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

@ Route 2
.equ CatchingTutorialRival, 12

.global EventScript_Route2_YoungsterJoey
EventScript_Route2_YoungsterJoey:
    trainerbattle0 0x0 0x5 0x0 gText_Route2_YoungsterJoey_Intro gText_Route2_YoungsterJoey_Defeat
    msgbox gText_Route2_YoungsterJoey_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassKimberly
EventScript_Route2_LassKimberly:
    trainerbattle0 0x0 0x6 0x0 gText_Route2_LassKimberly_Intro gText_Route2_LassKimberly_Defeat
    msgbox gText_Route2_LassKimberly_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassRikki
EventScript_Route2_LassRikki:
    trainerbattle0 0x0 0x7 0x0 gText_Route2_LassRikki_Intro gText_Route2_LassRikki_Defeat
    msgbox gText_Route2_LassRikki_Chat MSG_NORMAL
    end

.global EventScript_Route2_FindTMInfestation
EventScript_Route2_FindTMInfestation:
    setvar CHOSEN_ITEM ITEM_TM83
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_FindTMNaturePower
EventScript_Route2_FindTMNaturePower:
    setvar CHOSEN_ITEM ITEM_TM96
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_CoolTrainerAndy
EventScript_Route2_CoolTrainerAndy:
    trainerbattle0 0x0 0x10 0x0 gText_Route2_CoolTrainerAndy_Intro gText_Route2_CoolTrainerAndy_Defeat
    msgbox gText_Route2_CoolTrainerAndy_Chat MSG_NORMAL
    end

.global SignScript_Route2_TrainerTipsFishing
SignScript_Route2_TrainerTipsFishing:
    msgbox gText_Route2_TrainerTips MSG_SIGN
    end

.global TileScript_Route2_CapturingPokemonLeft
TileScript_Route2_CapturingPokemonLeft:
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    goto TileScript_Route2_CapturingPokemonRight

.global TileScript_Route2_CapturingPokemonRight
TileScript_Route2_CapturingPokemonRight:
    lock
    showsprite CatchingTutorialRival
    applymovement CatchingTutorialRival m_RivalWalkDownTowardPlayer
    waitmovement CatchingTutorialRival
    sound 0x15 @ Exclaim
    applymovement CatchingTutorialRival m_Surprise
    waitmovement CatchingTutorialRival
    msgbox gText_Route2_CatchingTutorial_RivalGreetsPlayer MSG_NORMAL
    applymovement CatchingTutorialRival m_RivalMeetsPlayerForCapturingTutorial
    waitmovement CatchingTutorialRival
    msgbox gText_Route2_CatchingTutorial_RivalCommentsOnPokedexAndPokeballs MSG_NORMAL
    playbgm 0x180 0x1 @ Let's go together, permanent on map
    applymovement CatchingTutorialRival m_RivalWalksIntoGrass
    applymovement PLAYER m_PlayerWalksIntoGrass
    waitmovement PLAYER
    msgbox gText_Route2_CatchingTutorialIntro_RivalTalksAboutHowToFindAPokemon MSG_NORMAL
    applymovement CatchingTutorialRival m_LookUp
    waitmovement CatchingTutorialRival
    pause DELAY_HALFSECOND
    applymovement CatchingTutorialRival m_LookDown
    waitmovement CatchingTutorialRival
    pause DELAY_HALFSECOND
    applymovement CatchingTutorialRival m_LookRight
    pause 0x10
    sound 0x15 @ Exclaim
    applymovement CatchingTutorialRival m_Surprise
    msgbox gText_Route2_CatchingTutorialIntro_RivalFindsAPokemon MSG_NORMAL
    setvar 0x8004 SPECIES_ROOKIDEE
    setvar 0x8005 5
    special 0x9C @ Catching tutorial
    waitstate
    applymovement CatchingTutorialRival m_LookLeft
    msgbox gText_Route2_CatchingTutorialIntro_RivalAfterTutorial MSG_NORMAL
    applymovement CatchingTutorialRival m_RivalLeaves
    pause 0x10
    applymovement PLAYER m_LookUp
    waitmovement CatchingTutorialRival
    hidesprite CatchingTutorialRival
    playbgm 0x123 0x1 @ Main route theme, permanent
    addvar 0x40FF 0x1
    end

m_RivalWalkDownTowardPlayer: .byte walk_down, walk_down, walk_down, walk_down, end_m
m_RivalMeetsPlayerForCapturingTutorial: .byte walk_down, walk_down, end_m
m_RivalWalksIntoGrass: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, end_m
m_PlayerWalksIntoGrass: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, end_m
m_RivalLeaves: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m

@ Route 3
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
    sound 0x15 @ Exclaim
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
    clearflag 0x35 @ Show NPCs on Route 4
    clearflag 0x36 @ Show Foreman on Route 4
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
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
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
    call SetupMugshotRival
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
    sound 0x15 @ Exclaim
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
    setflag 0x232 @ Initiated DexNav event (for Rhodanzi Gym placard)
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
    sound 0x15 @ Exclaim
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

m_RivalMeetsPlayer: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
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

@ Route 4
.equ Foreman, 0x1
.equ FormanEventVar, 0x4051

.global MapScript_Route4
MapScript_Route4:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route4
	.byte MAP_SCRIPT_TERMIN

LevelScripts_Route4:
	levelscript FormanEventVar 0x0 LevelScript_Rotue4_ForemanEvent
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_Rotue4_ForemanEvent:
    checkflag 0x35 @ Boulders are cleared
    if NOT_SET _goto ClearForemanEvent
    checkflag 0x36 @ Foreman has left
    if SET _goto ClearForemanEvent
    lock
    sound 0x15 @ Exclaim
    applymovement Foreman m_Surprise
    waitmovement ALLEVENTS
    applymovement Foreman m_MeetPlayer
    waitmovement ALLEVENTS
    msgbox gText_Route4_ForemanConfrontsPlayer MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerHonest
    compare LASTRESULT NO
    if equal _call PlayerDishonest
    msgbox gText_Route4_ForemanBeratesPlayer MSG_NORMAL
    applymovement Foreman m_LookDown
    msgbox gText_Route4_ForemanConcedes MSG_NORMAL
    applymovement Foreman m_LookUp
    msgbox gText_Route4_ForemanLeaves MSG_NORMAL
    applymovement Foreman m_ForemanLeaves
    waitmovement ALLEVENTS
    hidesprite Foreman
    setvar FormanEventVar 0x1
    setflag 0x36 @ Foreman has left
    release
    end

PlayerHonest:
    msgbox gText_Route4_PlayerHonest MSG_NORMAL
    return

PlayerDishonest:
    msgbox gText_Route4_PlayerDishonest MSG_NORMAL
    return

ClearForemanEvent:
    setvar FormanEventVar 0x1
    end

.global EventScript_Route4_Foreman
EventScript_Route4_Foreman:
    npcchatwithmovement gText_Route4_ForemanChat m_LookUp
    end

.global EventScript_Route4_Worker
EventScript_Route4_Worker:
    npcchatwithmovement gText_Route4_WorkerChat m_LookUp
    end

.global EventScript_Route4_LargeMan
EventScript_Route4_LargeMan:
    npcchat gText_Route4_LargeManChat
    end

.global EventScript_Route4_Lass
EventScript_Route4_Lass:
    npcchat gText_Route4_LassChat
    end

.global SignScript_Route4_TormaCaveSign
SignScript_Route4_TormaCaveSign:
    msgbox gText_Route4_TormaCaveSign MSG_NORMAL
    end

.global SignScript_Route4_TrainerTips
SignScript_Route4_TrainerTips:
    msgbox gText_Route4_TrainerTipsSign MSG_NORMAL
    end

.global EventScript_Route4_FindTM01WorkUp
EventScript_Route4_FindTM01WorkUp:
    setvar CHOSEN_ITEM ITEM_TM01
    call ItemScript_Common_FindTM
    end

.global EventScript_Route4_FindTM71StoneEdge
EventScript_Route4_FindTM71StoneEdge:
    setvar CHOSEN_ITEM ITEM_TM71
    call ItemScript_Common_FindTM
    end

.global EventScript_Route4_CamperPietro
EventScript_Route4_CamperPietro:
    trainerbattle0 0x0 0x24 0x0 gText_Route4_CamperPietro_Intro gText_Route4_CamperPietro_Defeat
    msgbox gText_Route4_CamperPietro_Chat MSG_NORMAL
    end

.global EventScript_Route4_PsychicAdriano
EventScript_Route4_PsychicAdriano:
    trainerbattle0 0x0 0x25 0x0 gText_Route4_PsychicAdriano_Intro gText_Route4_PsychicAdriano_Defeat
    msgbox gText_Route4_PsychicAdriano_Chat MSG_NORMAL
    end

.global EventScript_Route4_BeautyBeatrice
EventScript_Route4_BeautyBeatrice:
    trainerbattle0 0x0 0x26 0x0 gText_Route4_BeautyBeatrice_Intro gText_Route4_BeautyBeatrice_Defeat
    msgbox gText_Route4_BeautyBeatrice_Chat MSG_NORMAL
    end

.global EventScript_Route4_LadyAlda
EventScript_Route4_LadyAlda:
    trainerbattle0 0x0 0x27 0x0 gText_Route4_LadyAlda_Intro gText_Route4_LadyAlda_Defeat
    msgbox gText_Route4_LadyAlda_Chat MSG_NORMAL
    end

.global EventScript_Route4_LassIsabela
EventScript_Route4_LassIsabela:
    trainerbattle0 0x0 0x28 0x0 gText_Route4_LassIsabela_Intro gText_Route4_LassIsabela_Defeat
    msgbox gText_Route4_LassIsabela_Chat MSG_NORMAL
    end

.global EventScript_Route4_BirdKeeperRowley
EventScript_Route4_BirdKeeperRowley:
    trainerbattle0 0x0 0x29 0x0 gText_Route4_BirdKeeperRowley_Intro gText_Route4_BirdKeeperRowley_Defeat
    msgbox gText_Route4_BirdKeeperRowley_Chat MSG_NORMAL
    end

.global EventScript_Route4_CrushGirlElise
EventScript_Route4_CrushGirlElise:
    trainerbattle0 0x0 0x2A 0x0 gText_Route4_CrushGirlElise_Intro gText_Route4_CrushGirlElise_Defeat
    msgbox gText_Route4_CrushGirlElise_Chat MSG_NORMAL
    end

.global EventScript_Route4_GentlemanPorter
EventScript_Route4_GentlemanPorter:
    trainerbattle0 0x0 0x2B 0x0 gText_Route4_GentlemanPorter_Intro gText_Route4_GentlemanPorter_Defeat
    msgbox gText_Route4_GentlemanPorter_Chat MSG_NORMAL
    end

.global EventScript_Route4_BirdKeeperLuca
EventScript_Route4_BirdKeeperLuca:
    trainerbattle0 0x0 0x2C 0x0 gText_Route4_BirdKeeperLuca_Intro gText_Route4_BirdKeeperLuca_Defeat
    msgbox gText_Route4_BirdKeeperLuca_Chat MSG_NORMAL
    end

m_MeetPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_ForemanLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m

@ Route 5
.global EventScript_Route5_Biker
EventScript_Route5_Biker:
    msgbox gText_Route5_Biker MSG_NORMAL
    goto FindAnotherRoute

.global EventScript_Route5_BikerLeader
EventScript_Route5_BikerLeader:
    msgbox gText_Route5_BikerLeader MSG_NORMAL
    goto FindAnotherRoute

FindAnotherRoute:
    msgbox gText_Route5_AnotherRoute MSG_NORMAL
    end

.global EventScript_Route5And7_Cut
EventScript_Route5And7_Cut:
    setflag 0x38 @ Hide Route 5 bikers
    goto EventScript_Common_Cut

.global EventScript_Route5_LadyFaith
EventScript_Route5_LadyFaith:
    trainerbattle0 0x0 0x41 0x0 gText_Route5_LadyFaith_Intro gText_Route5_LadyFaith_Defeat
    msgbox gText_Route5_LadyFaith_Chat MSG_NORMAL
    end

.global EventScript_Route5_BugCatcherBen
EventScript_Route5_BugCatcherBen:
    trainerbattle0 0x0 0x42 0x0 gText_Route5_BugCatcherBen_Intro gText_Route5_BugCatcherBen_Defeat
    msgbox gText_Route5_BugCatcherBen_Chat MSG_NORMAL
    end

.global EventScript_Route5_PsychicAlyssia
EventScript_Route5_PsychicAlyssia:
    trainerbattle0 0x0 0x43 0x0 gText_Route5_PsychicAlyssia_Intro gText_Route5_PsychicAlyssia_Defeat
    msgbox gText_Route5_PsychicAlyssia_Chat MSG_NORMAL
    end

.global EventScript_Route5_BreederBrenda
EventScript_Route5_BreederBrenda:
    trainerbattle0 0x0 0x44 0x0 gText_Route5_BreederBrenda_Intro gText_Route5_BreederBrenda_Defeat
    msgbox gText_Route5_BreederBrenda_Chat MSG_NORMAL
    end

.global EventScript_Route5_BlackbeltRaheem
EventScript_Route5_BlackbeltRaheem:
    trainerbattle0 0x0 0x45 0x0 gText_Route5_BlackbeltRaheem_Intro gText_Route5_BlackbeltRaheem_Defeat
    msgbox gText_Route5_BlackbeltRaheem_Chat MSG_NORMAL
    end

.global EventScript_Route5_GamblerDominik
EventScript_Route5_GamblerDominik:
    trainerbattle0 0x0 0x46 0x0 gText_Route5_GamblerDominik_Intro gText_Route5_GamblerDominik_Defeat
    msgbox gText_Route5_GamblerDominik_Chat MSG_NORMAL
    end

.global EventScript_Route5_LadyJuliet
EventScript_Route5_LadyJuliet:
    compare PLAYERFACING LEFT
    if equal _call JulietAndMarcusLookRight
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route5_LadyJuliet_Chat MSG_NORMAL
    end
    
.global EventScript_Route5_GentlemanMarcus
EventScript_Route5_GentlemanMarcus:
    compare PLAYERFACING RIGHT
    if equal _call JulietAndMarcusLookLeft
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_LadyJuliet_Intro gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route5_GentlemanMarcus_Chat MSG_NORMAL
    end

JulietAndMarcusLookRight:
    applymovement 0x11 m_LookRight
    applymovement 0x12 m_LookRight
    return

JulietAndMarcusLookLeft:
    applymovement 0x11 m_LookLeft
    applymovement 0x12 m_LookLeft
    return

.global EventScript_Route5_AffectionGirl
EventScript_Route5_AffectionGirl:
    npcchatwithmovement gText_Route5_AffectionGirl m_LookRight
    end

.global EventScript_Route5_EggGiver
EventScript_Route5_EggGiver:
    lock
    faceplayer
    msgbox gText_Route5_EggGiver_Introduction MSG_NORMAL
    checkflag 0x233 @ Received custom egg
    if NOT_SET _call ReceivePokemonEgg
    msgbox gText_Route5_EggGiver_EggInstructions MSG_NORMAL
    checkflag 0x234 @ Received oval charm
    if NOT_SET _goto CheckForOvalCharmGift
    goto ResetEggMan

ReceivePokemonEgg:
    msgbox gText_Route5_EggGiver_Prompt MSG_YESNO
    compare LASTRESULT YES
    if FALSE _goto EggRejection
    msgbox gText_Route5_EggGiver_EggPun MSG_NORMAL
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto PartyFull
    fanfare 0x10D @ Fanfare 2
    msgbox gText_Route5_EggGiver_ReceivedEgg MSG_NORMAL
    waitfanfare
    msgbox gText_Route5_EggGiver_ReceiveEggComment MSG_NORMAL
    copyvar 0x8006 0x408C @ Copy index of the player's grass starter gen into egg var
    compare 0x8006 0x0
    if equal _call SetPichu
    compare 0x8006 0x1
    if equal _call SetTogepi
    compare 0x8006 0x2
    if equal _call SetWynaut
    compare 0x8006 0x3
    if equal _call SetRiolu
    compare 0x8006 0x4
    if equal _call SetLarvesta
    compare 0x8006 0x5
    if equal _call SetHappiny
    compare 0x8006 0x6
    if equal _call SetEevee
    compare 0x8006 0x7
    if equal _call SetToxel
    callasm GiveCustomEgg
    setflag 0x233 @ Received custom egg
    return

EggRejection:
    msgbox gText_Route5_EggGiver_EggRejected MSG_NORMAL
    goto ResetEggMan

PartyFull:
    msgbox gText_Route5_EggGiver_NoRoomForEgg MSG_NORMAL
    goto ResetEggMan

SetPichu:
    setvar 0x8005 SPECIES_PICHU
    return

SetTogepi:
    setvar 0x8005 SPECIES_TOGEPI
    return

SetWynaut:
    setvar 0x8005 SPECIES_WYNAUT
    return

SetRiolu:
    setvar 0x8005 SPECIES_RIOLU
    return

SetLarvesta:
    setvar 0x8005 SPECIES_LARVESTA
    return

SetHappiny:
    setvar 0x8005 SPECIES_HAPPINY
    return

SetEevee:
    setvar 0x8005 SPECIES_EEVEE
    return

SetToxel:
    setvar 0x8005 SPECIES_TOXEL
    return

CheckForOvalCharmGift:
    setvar 0x8004 0xD @ Number of eggs hatched
    callasm StoreGameStat
    buffernumber 0x0 LASTRESULT
    compare LASTRESULT 0xA
    if lessthan _goto NotEnoughEggsHatched
    msgbox gText_Route5_EggGiver_HatchedAtLeastTenEggs MSG_NORMAL
    loadpointer 0x0 gText_Route5_EggGiver_ReceivedOvalCharm
    obtainitem ITEM_OVAL_CHARM 0x1
    msgbox gText_Route5_EggGiver_TenEggGiftReceived MSG_NORMAL
    setflag 0x234 @ Oval charm received
    goto ResetEggMan

NotEnoughEggsHatched:
    msgbox gText_Route5_EggGiver_TenEggGiftComment MSG_NORMAL
    goto ResetEggMan

ResetEggMan:
    applymovement 0x3 m_LookLeft
    waitmovement ALLEVENTS
    release
    end

.global EventScript_Route5_FindTM58Endure
EventScript_Route5_FindTM58Endure:
    setvar CHOSEN_ITEM ITEM_TM58
    call ItemScript_Common_FindTM
    end

.global SignScript_Route5_Daycare
SignScript_Route5_Daycare:
    msgbox gText_Route5_DaycareSign MSG_SIGN
    end

@@ Heleo Ranch
.global MapScript_HeleoRanchExterior
MapScript_HeleoRanchExterior:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoRanch_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMareepVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_FlightFlag:
    setworldmapflag 0x8A7 @ Been to Heleo Ranch
    end

MapEntryScript_HeleoRanch_HandleMareepVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto End
    setflag 0xE07 @ Evenining or night, hide all mareeps on field and Moomoo Milk seller, by setting daily flag
    end

.global MapScript_HeleoRanchInterior
MapScript_HeleoRanchInterior:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMomVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_HandleMomVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto HideMom
    clearflag 0xE08 
    end

HideMom:
    setflag 0xE08 @ Hide mom in house during morning and day
    end

.global EvenScript_HeleoRanch_Mareep
EvenScript_HeleoRanch_Mareep:
    lock
    faceplayer
    checksound
    cry SPECIES_MAREEP 0x0
    msgbox gText_HeleoRanch_Mareep MSG_NORMAL
    release
    end

.global EvenScript_HeleoRanch_MoomooMilkSeller
EvenScript_HeleoRanch_MoomooMilkSeller:
    lock
    faceplayer
    msgbox gText_HeleoRanch_MoomooMilkSeller_PurchaseRequest MSG_KEEPOPEN
    showmoney 0x0 0x0
    multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseOne 0
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseADozen 1
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseNone 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, BuyOneMoomooMilk
	case 1, BuyADozenMoomooMilk
	case 2, BuyNoMoomooMilk
    goto BuyNoMoomooMilk

BuyOneMoomooMilk:
    checkmoney 0x1F4 @ Has 500 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1F4
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0x1
    goto EndMoomooMilkSeller

BuyADozenMoomooMilk:
    checkmoney 0x1770 @ Has 6,000 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1770
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0xC
    goto EndMoomooMilkSeller

BuyNoMoomooMilk:
    msgbox gText_HeleoRanch_MoomooMilkSeller_ChoseNotToBuy MSG_NORMAL
    goto EndMoomooMilkSeller

PurchaseMoomooMilk:
    updatemoney
    playse 0xF8 @ Money SE
    waitse
    msgbox gText_HeleoRanch_MoomooMilkSeller_PuchaseComplete MSG_NORMAL
    return

NotEnoughCash:
    msgbox gText_HeleoRanch_MoomooMilkSeller_NotEnoughCash MSG_NORMAL
    goto EndMoomooMilkSeller

EndMoomooMilkSeller:
    hidemoney
    release
    end

.global EvenScript_HeleoRanch_Ampharos
EvenScript_HeleoRanch_Ampharos:
    lock
    faceplayer
    checksound
    cry SPECIES_AMPHAROS 0x0
    msgbox gText_HeleoRanch_AgitatedAmpharos_Sound MSG_NORMAL
    msgbox gText_HeleoRanch_AgitatedAmpharos_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto AmpharosLeftAlone
    setflag 0x903 @ Disable running
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleStarted MSG_NORMAL
    wildbattle SPECIES_AMPHAROS 0x1E ITEM_SITRUS_BERRY
    setflag 0x03E @ Hide Ampharos
    hidesprite LASTTALKED
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleEnded MSG_NORMAL
    clearflag 0x903 @ Enable running
    release
    end

AmpharosLeftAlone:
    msgbox gText_HeleoRanch_AgitatedAmpharos_LeftAlone MSG_NORMAL
    applymovement 0xA m_LookDown
    end

.global EvenScript_HeleoRanch_BurglarCole
EvenScript_HeleoRanch_BurglarCole:
    trainerbattle0 0x0 0x49 0x0 gText_HeleoRanch_BurglarCole_Intro gText_HeleoRanch_BurglarCole_Defeat
    msgbox gText_HeleoRanch_BurglarCole_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_CamperTroy
EvenScript_HeleoRanch_CamperTroy:
    trainerbattle0 0x0 0x4A 0x0 gText_HeleoRanch_CamperTroy_Intro gText_HeleoRanch_CamperTroy_Defeat
    msgbox gText_HeleoRanch_CamperTroy_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_BreederLaura
EvenScript_HeleoRanch_BreederLaura:
    trainerbattle0 0x0 0x4B 0x0 gText_HeleoRanch_BreederLaura_Intro gText_HeleoRanch_BreederLaura_Defeat
    msgbox gText_HeleoRanch_BreederLaura_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_PicknickerCarly
EvenScript_HeleoRanch_PicknickerCarly:
    trainerbattle0 0x0 0x4C 0x0 gText_HeleoRanch_PicknickerCarly_Intro gText_HeleoRanch_PicknickerCarly_Defeat
    msgbox gText_HeleoRanch_PicknickerCarly_Chat MSG_NORMAL
    end

.global EventScript_HeleoRanch_FindTM45Attract
EventScript_HeleoRanch_FindTM45Attract:
    setvar CHOSEN_ITEM ITEM_TM45
    call ItemScript_Common_FindTM
    end

.global EventScript_HeleoRanch_Ampharosite
EventScript_HeleoRanch_Ampharosite:
    finditem ITEM_AMPHAROSITE 0x1
    end

.global SignScript_HeleoRanch_RanchGlade
SignScript_HeleoRanch_RanchGlade:
    msgbox gText_HeleoRanch_GladeSign MSG_SIGN
    end

.global SignScript_HeleoRanch_RanchEntrance
SignScript_HeleoRanch_RanchEntrance:
    msgbox gText_HeleoRanch_EntranceSign MSG_SIGN
    end

.global EventScript_HeleoRanch_Dad
EventScript_HeleoRanch_Dad:
    npcchat gText_HeleoRanch_Dad
    end

.global EventScript_HeleoRanch_Daughter
EventScript_HeleoRanch_Daughter:
    npcchatwithmovement gText_HeleoRanch_Daughter m_LookUp
    end

.global EventScript_HeleoRanch_Mom
EventScript_HeleoRanch_Mom:
    npcchat gText_HeleoRanch_Mom
    end

.global EventScript_HeleoRanch_Son
EventScript_HeleoRanch_Son:
    npcchat gText_HeleoRanch_Son
    end
