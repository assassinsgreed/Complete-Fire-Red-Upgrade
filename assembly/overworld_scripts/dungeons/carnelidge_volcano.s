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
	.byte MAP_SCRIPT_TERMIN

MapScript_SetCarnelidgeVolcanoPeakState:
    playbgm 0x14B 0x1 @ Regular peak theme, set as permanent on the map (in case the player lost to Rival or Alistair)
    @ TODO later: Show Jirachi in it's correct sprite if it has yet to be caught
    end

LevelScripts_CarnelidgeVolcanoPeak_StoryEvents:
    levelscript VarStorySequence 0x1 LevelScript_InitiateStoryConclusion
    @ TODO Later: Level script for story's conclusion
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
    playse 0x5F @ Shiny
	dofieldeffect 69 @ Screen flash
    hidesprite JirachiDormant
    setflag 0x270 @ Jirachi has been awakened
    clearflag 0x05A @ Animated Jirachi is now shown
    showsprite Jirachi
    waitfieldeffect 69
    waitse
    cry SPECIES_JIRACHI 0x0
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
    @ TODO later: Transport player, set vars and flags, end event
    addvar VarStorySequence 0x1
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

m_PlayerWalksToConfrontAlistair: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_RivalWalksToStallPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, look_down, end_m
