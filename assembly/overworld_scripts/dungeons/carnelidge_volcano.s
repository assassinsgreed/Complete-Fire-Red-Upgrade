.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_CarnelidgeVolcano
MapScript_CarnelidgeVolcano:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_CarnelidgeVolcano_FlightFlagAndWalkingScript
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_CarnelidgeVolcano_FlightFlagAndWalkingScript:
    setworldmapflag 0x8AB
    setvar 0x500B 0x2 @ Use walking script #2, i.e. "mountain tremors." This is cleared if the player the first time it executes, if the player isn't on a mount carnelidge map
    setvar 0x400E 0x1 @ Used to control whether the tremor is active or not
    end

.global CarnelidgeVolcano_Tremors
CarnelidgeVolcano_Tremors:
    call DisableWalkingScriptIfOnInvalidMap
    release
    compare 0x4002 0x1
    if equal _goto End @ Don't trigger a tremor while another one is live
    random 100 @ 1% chance for heavy tremor, 4% chance for light tremor
    compare LASTRESULT 1
    if lessthan _goto HeavyTremor
    compare LASTRESULT 5
    if lessthan _goto LightTremor
    end

HeavyTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x3 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x15 @ This controls how long the overall animation lasts
	setvar 0x8007 0x3 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

LightTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x1 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x10 @ This controls how long the overall animation lasts
	setvar 0x8007 0x1 @ This controls how long one screen shake lasts
    playse 0x21 @ Small tremor
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

.global EventScript_CarnelidgeVolcano_HikerBjorn
EventScript_CarnelidgeVolcano_HikerBjorn:
    trainerbattle0 0x0 460 0x0 gText_CarnelidgeVolcano_HikerBjorn_Intro gText_CarnelidgeVolcano_HikerBjorn_Defeat
    msgbox gText_CarnelidgeVolcano_HikerBjorn_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_ChannelerKelsey
EventScript_CarnelidgeVolcano_ChannelerKelsey:
    trainerbattle0 0x0 461 0x0 gText_CarnelidgeVolcano_ChannelerKelsey_Intro gText_CarnelidgeVolcano_ChannelerKelsey_Defeat
    msgbox gText_CarnelidgeVolcano_ChannelerKelsey_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_JugglerSeth
EventScript_CarnelidgeVolcano_JugglerSeth:
    trainerbattle0 0x0 462 0x0 gText_CarnelidgeVolcano_JugglerSeth_Intro gText_CarnelidgeVolcano_JugglerSeth_Defeat
    msgbox gText_CarnelidgeVolcano_JugglerSeth_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_DragonTamerFlynn
EventScript_CarnelidgeVolcano_DragonTamerFlynn:
    trainerbattle0 0x0 463 0x0 gText_CarnelidgeVolcano_DragonTamerFlynn_Intro gText_CarnelidgeVolcano_DragonTamerFlynn_Defeat
    msgbox gText_CarnelidgeVolcano_DragonTamerFlynn_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_BirdKeeperFalco
EventScript_CarnelidgeVolcano_BirdKeeperFalco:
    trainerbattle0 0x0 464 0x0 gText_CarnelidgeVolcano_BirdKeeperFalco_Intro gText_CarnelidgeVolcano_BirdKeeperFalco_Defeat
    msgbox gText_CarnelidgeVolcano_BirdKeeperFalco_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_CrushGirlEunice
EventScript_CarnelidgeVolcano_CrushGirlEunice:
    trainerbattle0 0x0 465 0x0 gText_CarnelidgeVolcano_CrushGirlEunice_Intro gText_CarnelidgeVolcano_CrushGirlEunice_Defeat
    msgbox gText_CarnelidgeVolcano_CrushGirlEunice_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_SuperNerdNathan
EventScript_CarnelidgeVolcano_SuperNerdNathan:
    trainerbattle0 0x0 466 0x0 gText_CarnelidgeVolcano_SuperNerdNathan_Intro gText_CarnelidgeVolcano_SuperNerdNathan_Defeat
    msgbox gText_CarnelidgeVolcano_SuperNerdNathan_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_HikerHugh
EventScript_CarnelidgeVolcano_HikerHugh:
    trainerbattle0 0x0 467 0x0 gText_CarnelidgeVolcano_HikerHugh_Intro gText_CarnelidgeVolcano_HikerHugh_Defeat
    msgbox gText_CarnelidgeVolcano_HikerHugh_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_ScientistXander
EventScript_CarnelidgeVolcano_ScientistXander:
    trainerbattle0 0x0 468 0x0 gText_CarnelidgeVolcano_ScientistXander_Intro gText_CarnelidgeVolcano_ScientistXander_Defeat
    msgbox gText_CarnelidgeVolcano_ScientistXander_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_CharizarditeY
EventScript_CarnelidgeVolcano_CharizarditeY:
    finditem ITEM_CHARIZARDITE_Y 0x1
    end

.global EventScript_CarnelidgeVolcano_TM50_Overheat
EventScript_CarnelidgeVolcano_TM50_Overheat:
    setvar CHOSEN_ITEM ITEM_TM50
    call ItemScript_Common_FindTM
    end

.global EventScript_CarnelidgeVolcano_TM38_FireBlast
EventScript_CarnelidgeVolcano_TM38_FireBlast:
    setvar CHOSEN_ITEM ITEM_TM38
    call ItemScript_Common_FindTM
    end

.global TileScript_CarnelidgeVolcano_VolcanionRoom
TileScript_CarnelidgeVolcano_VolcanionRoom:
    checkflag 0x4BC @ Became champion
    if SET _goto End
    lock
    msgbox gText_CarnelidgeVolcano_VolcanionPresenceFelt MSG_NORMAL
    setvar 0x4000 0x1 @ Don't trigger this until the player returns
    end

.global SignScript_CarnelidgeVolcano_EntrySign
SignScript_CarnelidgeVolcano_EntrySign:
    msgbox gText_CarnelidgeVolcano_EntranceSign MSG_SIGN
    end    

.global SignScript_CarnelidgeVolcano_TrainerTips
SignScript_CarnelidgeVolcano_TrainerTips:
    msgbox gText_CarnelidgeVolcano_TrainerTipsSign MSG_SIGN
    end

.global SignScript_CarnelidgeVolcano_HotSpringSign
SignScript_CarnelidgeVolcano_HotSpringSign:
    msgbox gText_CarnelidgeVolcano_HotSpringsSign MSG_SIGN
    end

.global TileScript_CarnelidgeVolcano_ExtendedSequenceWarning
TileScript_CarnelidgeVolcano_ExtendedSequenceWarning:
    lock
    msgboxsign
    msgbox gText_CarnelidgeVolcano_ExtendedSequenceWarning MSG_SIGN
    msgboxnormal
    addvar VarStorySequence 1
    release
    end

### Carnelidge Volcano Peak
.equ VarStorySequence, 0x4062
.equ JirachiDormant, 0x1
.equ Alistair, 0x2
.equ Rival, 0x3
.equ Selene, 0x4
.equ Jirachi, 0x5

.global MapScript_CarnelidgeVolcano_Peak
MapScript_CarnelidgeVolcano_Peak:
    mapscript MAP_SCRIPT_ON_LOAD MapScript_SetCarnelidgeVolcanoPeakState
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_CarnelidgeVolcanoPeak_StoryEvents
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_CarnelidgeVolcanoPeak_StoryEvents_AfterUltraSpace
    mapscript MAP_SCRIPT_ON_RESUME HideLegendary
	.byte MAP_SCRIPT_TERMIN

MapScript_SetCarnelidgeVolcanoPeakState:
    playbgm 0x14B 0x1 @ Regular peak theme, set as permanent on the map (in case the player lost to Rival or Alistair)
    end

HideLegendary:
    checkflag 0x5A @ Jirachi
    if SET _call HideJirachi
    end

HideJirachi:
    hidesprite 5
    end

LevelScripts_CarnelidgeVolcanoPeak_StoryEvents:
    levelscript VarStorySequence 0x1 LevelScript_InitiateStoryConclusion
    levelscript VarStorySequence 0xE LevelScript_StoryConclusionCutscene
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_InitiateStoryConclusion:
    special 0xAF @ Dismount bike if on it
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA
    if equal _call PlayerWalkRight_Return
    compare 0x4000 0xC
    if equal _call PlayerWalkLeft_Return
    applymovement PLAYER m_PlayerWalksToConfrontAlistair
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    msgbox gText_CarnelidgeVolcanoPeak_AlistairGreetsPlayer MSG_NORMAL
    applymovement Alistair m_LookDown
    playbgm 0x173 @ Alistair's theme
    msgbox gText_CarnelidgeVolcanoPeak_AlistairFacesPlayer MSG_NORMAL
    applymovement Alistair m_WalkLeft
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations1 MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations2 MSG_NORMAL
    applymovement Alistair m_WalkRight
    waitmovement Alistair
    applymovement Alistair m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations3 MSG_YESNO
    compare LASTRESULT NO
    if equal _call DoNotUnderstandMotivations
    if notequal _call DoUnderstandMotivations
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations4 MSG_NORMAL
    applymovement Alistair m_WalkLeft
    waitmovement Alistair
    applymovement Alistair m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations5 MSG_NORMAL
    applymovement Alistair m_WalkRight
    waitmovement Alistair
    applymovement Alistair m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations6 MSG_YESNO
    compare LASTRESULT NO
    if equal _call WillNotOpposeAlistair
    if notequal _call WillOpposeAlistair
    showsprite Rival
    msgbox gText_CarnelidgeVolcanoPeak_AlistairCallsForRival MSG_NORMAL
    playbgm 0x185 0x1 @ Ghetsis encounter, set as permanent on the map
    applymovement Rival m_RivalWalksToStallPlayer
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookDown
    pause DELAY_1SECOND
    applymovement PLAYER m_LookRight
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    waitmovement Rival
    msgbox gText_CarnelidgeVolcanoPeak_RivalChallengesPlayer MSG_NORMAL
    call SetupMugshotRival
    trainerbattle3 0x0 469 0x100 gText_CarnelidgeVolcanoPeak_RivalLosesToPlayer
    showsprite Rival
    msgbox gText_CarnelidgeVolcanoPeak_RivalCannotHandleLoss MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_AlistairCommentsOnRivalsLoss MSG_NORMAL
    applymovement Rival m_WalkRight
    waitmovement Rival
    applymovement Rival m_LookLeft
    applymovement Alistair m_WalkDown
    msgbox gText_CarnelidgeVolcanoPeak_AlistairPreparesToBattle MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 470 0x100 gText_CarnelidgeVolcanoPeak_AlistairLosesToPlayer
    msgbox gText_CarnelidgeVolcanoPeak_AlistairCommentsOnDelays MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_SeleneArrives MSG_NORMAL
    applymovement Alistair m_LookDown
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookDown
    showsprite Selene
    applymovement Selene m_PlayerWalksToConfrontAlistair
    pause DELAY_1SECOND
    applymovement PLAYER m_LookLeft
    waitmovement Selene
    applymovement Selene m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_SeleneAcknowledgesPlayerAndRival MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Selene m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_AlistairAddressesSelene MSG_NORMAL
    call HandleJirachisAwakening
    applymovement Rival m_LookUp
    applymovement Alistair m_WalkUp
    waitmovement Alistair
    applymovement Alistair m_Surprise
    msgbox gText_CarnelidgeVolcanoPeak_AlistairCommentsOnJirachiAwakening MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_RivalCommentsOnWish MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_AlistairCommentsOnRivalsResponse MSG_NORMAL
    fadescreen FADEOUT_WHITE
    cry SPECIES_JIRACHI 0x0
    waitcry
    msgbox gText_CarnelidgeVolcanoPeak_AlistairsWish MSG_NORMAL
    addvar VarStorySequence 0x1
    getplayerpos 0x4000 0x4001
    warpmuted 2 12 0xFF 0x4000 0x4001 @ Warp to same position in the empty world
    end

DoNotUnderstandMotivations:
    msgbox gText_CarnelidgeVolcanoPeak_PlayerDoesNotUnderstandAlistairsMotivation MSG_NORMAL
    return

DoUnderstandMotivations:
    msgbox gText_CarnelidgeVolcanoPeak_PlayerUnderstandsAlistairsMotivation MSG_NORMAL
    return

WillOpposeAlistair:
    msgbox gText_CarnelidgeVolcanoPeak_PlayerWillOpposeAlistair MSG_NORMAL
    return

WillNotOpposeAlistair:
    msgbox gText_CarnelidgeVolcanoPeak_PlayerWillNotOpposeAlistair MSG_NORMAL
    return

LevelScripts_CarnelidgeVolcanoPeak_StoryEvents_AfterUltraSpace:
    levelscript VarStorySequence 0xE LevelScript_PlayerPositionDuringFinalStoryEvent
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerPositionDuringFinalStoryEvent:
    applymovement PLAYER m_LookUp
    end

LevelScript_StoryConclusionCutscene:
    pause DELAY_HALFSECOND
    msgbox gText_CarnelidgeVolcanoPeak_AlistairGreetsPlayer MSG_NORMAL
    applymovement Alistair m_LookDown
    playbgm 0x173 @ Alistair's theme
    msgbox gText_CarnelidgeVolcanoPeak_AlistairFacesPlayer MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_AlistairExplainsMotivations1 MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairGetsDejaVu MSG_NORMAL
    showsprite Rival
    applymovement Rival m_RivalWalksToPlayersSide
    waitmovement Rival
    applymovement PLAYER m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalArrives MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Rival m_LookUp
    applymovement Alistair m_Question
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairQuestionsRivalsMotivations MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalPleadsToAlistair MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairDisagreesWithRival MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalExplainsTheStakes MSG_NORMAL
    goto BattleAlistair
    
BattleAlistair:
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    @ Set up vars to return the player here in case they throw against Alistair (TODO later: This causes the pokemon center text and animation to play. Not ideal, but not breaking)
    setvar 0x5037 0x3A01 @ Bank 1, map 58
    setvar 0x5038 0xB @ X coordinate
    setvar 0x5039 0x9 @ Y coordinate
    setflag 0x92D @ Just a dream whiteout text
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalInitiatesBattle MSG_NORMAL
    special 0x28 @ Restore party
    special 0x0 @ Heal player party
    addvar VarStorySequence 0x1 @ Big hack - add 1 so the cutscene doesn't reset when exiting the party menu
    call RivalTagBattlePromptAndPartyOrganization
    subvar VarStorySequence 0x1 @ Big hack - subtract 1 so the cutscene does play again if the player loses to Alistair
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalPreBattle MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    @ Start a tag battle against Alistair
    trainerbattle12 0xC 470 471 0x6 0x100 gText_CarnelidgeVolcanoPeak_Conclusion_AlistairLosesToPlayerAndRival
    setvar 0x5037 0x0 @ Disable custom warp
    setvar 0x5038 0x0 @ Disable custom warp
    setvar 0x5039 0x0 @ Disable custom warp
    clearflag 0x92D @ Just a dream whiteout text
    playbgm 0x114 0x0 @ Unwavering emotions
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairLamentsLoss MSG_NORMAL
    applymovement Rival m_WalkUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalCommentsOnLoss MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalCommentsOnHisJourney MSG_NORMAL
    applymovement Rival m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalConcludesHisThoughtsOnHisJourney MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairAsksWhatMotivatesTheRival MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalExplainsMotivations MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Alistair m_Surprise
    waitmovement Alistair
    applymovement Alistair m_LookLeft
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairRealizesRivalIsTellingTheTruth MSG_NORMAL
    applymovement Alistair m_LookDown
    applymovement Rival m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalExplainsHimself MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalPraisesPlayer MSG_NORMAL
    applymovement Rival m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalPleadsToAlistairToReconsiderWish MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairAcknowledgesJirachisPower MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairPreparesHisWish MSG_NORMAL
    pause DELAY_HALFSECOND
    call HandleJirachisAwakening
    fadescreen FADEOUT_WHITE
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairErasesHisWish MSG_NORMAL
    fadescreen FADEIN_WHITE
    pause DELAY_1SECOND
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairAsksRivalAboutHisMotivations MSG_NORMAL
    applymovement Alistair m_WalkDown
    applymovement Rival m_LookLeft
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairSharesHisNewMotivations MSG_NORMAL
    showsprite Selene
    applymovement Selene m_SeleneWalksTowardGroup
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalAcknowledgesAlistairsMotivations MSG_NORMAL
    applymovement Selene m_SeleneApproachesAlistair
    waitmovement Selene
    applymovement Selene m_Question
    applymovement Alistair m_LookLeft
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SeleneFollowsUpOnRumours MSG_NORMAL
    applymovement Selene m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SeleneSeesJirachi MSG_NORMAL
    applymovement Selene m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairCommentsOnSelenesArrival MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SeleneAsksAlistairToGoToRestaurant MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairAgreesToRestaurant MSG_NORMAL
    applymovement Selene m_LookDown
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairThanksPlayerAndRival MSG_NORMAL
    applymovement Alistair m_LookRight
    applymovement Selene m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalRespondsToAlistairsThanks MSG_NORMAL
    applymovement Alistair m_LookDown
    pause DELAY_HALFSECOND
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairGivesMegaStones MSG_NORMAL
    applymovement Alistair m_LookRight
    pause DELAY_1SECOND
    applymovement Alistair m_LookDown
    pause DELAY_HALFSECOND
    obtainitem ITEM_HOUNDOOMINITE 0x1
    applymovement Alistair m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalThanksAlistairForMegaStones MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairCommentsOnGoingBackToUltraSpace MSG_NORMAL
    applymovement Selene m_LookRight
    applymovement Alistair m_LookLeft
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SeleneIsConfused MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_AlistairMentionsALotToDiscuss MSG_NORMAL
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SelenePreparingToLeave MSG_NORMAL
    applymovement Selene m_LookDown
    applymovement Alistair m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_SeleneEncouragesPlayerAndRival MSG_NORMAL
    applymovement Selene m_SeleneLeaves
    applymovement Alistair m_AlistairLeaves
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookLeft
    applymovement Rival m_LookLeft
    pause DELAY_1SECOND
    applymovement PLAYER m_LookDown
    applymovement Rival m_LookDown
    waitmovement Alistair
    playse 0x9 @ Exit room
    hidesprite Alistair
    hidesprite Selene
    fadedefaultbgm
    applymovement Rival m_RivalWalksInFrontOfPlayer
    waitmovement Rival
    applymovement PLAYER m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalCommentsOnTheirSuccess MSG_NORMAL
    applymovement Rival m_LookUp
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalMentionsJirachi MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalEncouragesPlayerToFaceJirachi MSG_NORMAL
    applymovement Rival m_LookRight
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalPondersWhatToDoNext MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_RivalLeaves MSG_NORMAL
    applymovement Rival m_AlistairLeaves
    waitmovement Rival
    playse 0x9 @ Exit room
    hidesprite Rival
    fanfare 0x10C @ Big Celebration
    msgboxsign
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_PlayerAvertedTragedy MSG_KEEPOPEN
    waitfanfare
    msgbox gText_CarnelidgeVolcanoPeak_Conclusion_PlayerCanSaveAgain MSG_NORMAL
    msgboxnormal
    special 0x0 @ Heal player party
    setflag 0x829 @ ShowHide Pokedex in menu
    setflag 0x828 @ Enable Pokemon Menu
	clearflag 0x911 @ Enable wild encounters
    clearflag 0x91D @ Show Save in the menu
    clearflag 0x271 @ No longer in the empty world
    setflag 0x56 @ Hide Ena on Route 11 South and Alistair here
    setflag 0x273 @ Has completed the Carnelidge Volcano events
    addvar VarStorySequence 0x1 @ Conclude the story event
    end

HandleJirachisAwakening:
    playse 0x5F @ Shiny
	dofieldeffect 69 @ Screen flash
    hidesprite JirachiDormant
    setflag 0x270 @ Jirachi has been awakened
    clearflag 0x05A @ Animated Jirachi is now shown
    showsprite Jirachi
    waitfieldeffect 69
    waitse
    cry SPECIES_JIRACHI 0x0
    return

m_PlayerWalksToConfrontAlistair: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_RivalWalksToStallPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, look_down, end_m
m_RivalWalksToPlayersSide: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, look_left, end_m
m_SeleneWalksTowardGroup: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_SeleneApproachesAlistair: .byte walk_up, walk_up, walk_up, look_right, end_m
m_SeleneLeaves: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_AlistairLeaves: .byte walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_RivalWalksInFrontOfPlayer: .byte walk_left, look_down, end_m

@ Jirachi events
.global EventScript_CarnelidgeVolcano_Jirachi
EventScript_CarnelidgeVolcano_Jirachi:
    faceplayer
    cry SPECIES_JIRACHI 0x0
    msgbox gText_UltraSpace_Hoenn_FindingJirachi10 MSG_NORMAL
    waitcry
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_METEORMASH
    setvar 0x8001 MOVE_PSYCHIC
    setvar 0x8002 MOVE_WISH
    setvar 0x8003 MOVE_COSMICPOWER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_JIRACHI 60 ITEM_STAR_PIECE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedOrFledFromJirachi
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call DefeatedOrFledFromJirachi
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtJirachi
    end

DefeatedOrFledFromJirachi:
    applymovement Jirachi m_LookDown
    cry SPECIES_JIRACHI 0x0
    waitcry
    applymovement Jirachi m_JirachiFloatsAway
    waitmovement Jirachi
    hidesprite LASTTALKED
    setflag 0x5A @ Jirachi hidden
    msgbox gtext_OrichelleGarden_JirachiDefeatedOrPlayerFled MSG_NORMAL
    end

CaughtJirachi:
    setflag 0x5A @ Jirachi hidden
    return

m_JirachiFloatsAway: .byte slide_up, slide_up, slide_up, slide_up, slide_up, slide_up, slide_up, end_m
