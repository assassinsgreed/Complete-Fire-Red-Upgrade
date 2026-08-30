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

.global MapScript_CarnelidgeVolcano_VolcanionRoom
MapScript_CarnelidgeVolcano_VolcanionRoom:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_SetLegendarySprite
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_CarnelidgeVolcano_FlightFlagAndWalkingScript
    mapscript MAP_SCRIPT_ON_RESUME HideVolcanionOnResume
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_SetLegendarySprite:
    setvar 0x5029 150 @ Volcanion
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _goto End
    setvar 0x5029 139 @ Heatran
    end

HideVolcanionOnResume:
    checkflag 0x945 @ Divergent Mode
    if SET _goto HideHeatranOnResume
    setvar LASTRESULT SPECIES_VOLCANION
    callasm CheckIfCaught
    compare LASTRESULT 0x1
    if notequal _goto End
    hidesprite 8
    end

HideHeatranOnResume:
    setvar LASTRESULT SPECIES_HEATRAN
    callasm CheckIfCaught
    compare LASTRESULT 0x1
    if notequal _goto End
    hidesprite 8
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
    checkflag 0x945 @ Divergent Mode
    if SET _goto FalcoChatDivergent
    msgbox gText_CarnelidgeVolcano_BirdKeeperFalco_Chat MSG_NORMAL
    end

FalcoChatDivergent:
    msgbox gText_CarnelidgeVolcano_BirdKeeperFalco_ChatDivergent MSG_NORMAL
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

.global EventScript_CarnelidgeVolcano_MagmaStone
EventScript_CarnelidgeVolcano_MagmaStone:
    finditem ITEM_MAGMA_STONE 0x1
    end

.global TileScript_CarnelidgeVolcano_VolcanionRoom
TileScript_CarnelidgeVolcano_VolcanionRoom:
    checkflag 0x73 @ Volcanion caught or defeated
    if SET _goto End
    checkitem ITEM_VICTORY_FLAG 0x1
    compare LASTRESULT TRUE
    if notequal _goto VolcanionConditionsNotMet
    checkflag 0x82C @ Game cleared
    if SET _goto VolcanionEmerges
    goto VolcanionConditionsNotMet
    end

VolcanionConditionsNotMet:
    lock
    msgbox gText_CarnelidgeVolcano_VolcanionPresenceFelt MSG_NORMAL
    setvar 0x4000 0x1 @ Don't trigger this until the player returns
    end

.global TileScript_CarnelidgeVolcano_VolcanionRoom_ResetVolcanionEntrance
TileScript_CarnelidgeVolcano_VolcanionRoom_ResetVolcanionEntrance:
    setvar 0x4000 0x0 @ Reset Volcanion tile event, so it triggers if the player walks away and returns while on this map
    release
    end

VolcanionEmerges:
    lock
    msgbox gText_CarnelidgeVolcano_VolcanionEmerging MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_CameraPanUpForVolcanion
    waitmovement CAMERA
    special CAMERA_END
    pause DELAY_HALFSECOND
    setvar 0x4002 0x1
    setvar 0x8004 0x3 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x15 @ This controls how long the overall animation lasts
	setvar 0x8007 0x3 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    showsprite 0x8 @ Volcanion
    playse 0xA @ Hop
    applymovement 0x8 m_VolcanionJumpOutOfLava
    waitmovement 0x8
    special CAMERA_START
    applymovement CAMERA m_CameraPanDownForVolcanion
    waitmovement CAMERA
    special CAMERA_END
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _call VolcanionCry
    if SET _call HeatranCry 
    waitcry
    msgbox gText_CarnelidgeVolcano_VolcanionEmerged MSG_NORMAL
    setvar 0x4000 0x1 @ Don't trigger this until the player returns
    end

VolcanionCry:
    cry SPECIES_VOLCANION 0x0
    msgbox gText_CarnelidgeVolcano_VolcanionCry MSG_NORMAL
    return

HeatranCry:
    cry SPECIES_HEATRAN 0x0
    msgbox gText_CarnelidgeVolcano_HeatranCry MSG_NORMAL
    return

EventScript_CarnelidgeVolcano_Volcanion:
    lock
    faceplayer
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _call VolcanionCry
    if SET _call HeatranCry 
    waitcry
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _call SetupVolcanionBattle
    if SET _call SetupHeatranBattle
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    setflag 0x73 @ Volcanion caught, defeated, or fled from
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedVolcanion
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call FledFromVolcanion
    end

SetupVolcanionBattle:
    setvar 0x8000 MOVE_STEAMERUPTION
    setvar 0x8001 MOVE_MIST
    setvar 0x8002 MOVE_FIRESPIN
    setvar 0x8003 MOVE_EARTHPOWER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_VOLCANION 75 ITEM_NONE
    return

SetupHeatranBattle:
    setvar 0x8000 MOVE_MAGMASTORM
    setvar 0x8001 MOVE_STONEEDGE
    setvar 0x8002 MOVE_EARTHPOWER
    setvar 0x8003 MOVE_CRUNCH
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_HEATRAN 75 ITEM_NONE
    return

DefeatedVolcanion:
    call VolcanionLeavesCommon
    msgbox gtext_VolcanionRoom_VolcanionDefeated MSG_NORMAL
    return

FledFromVolcanion:
    call VolcanionLeavesCommon
    msgbox gtext_VolcanionRoom_VolcanionFledFromBattle MSG_NORMAL
    return

VolcanionLeavesCommon:
    showsprite 8
    pause DELAY_HALFSECOND
    playse 0xA @ Hop
    applymovement 0x8 m_VolcanionJumpIntoLava
    waitmovement 0x8
    hidesprite 0x8
    return

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
    mapscript MAP_SCRIPT_ON_RESUME HideJirachiOnResume
	.byte MAP_SCRIPT_TERMIN

MapScript_SetCarnelidgeVolcanoPeakState:
    playbgm 0x14B 0x1 @ Regular peak theme, set as permanent on the map (in case the player lost to Rival or Alistair)
    end

HideJirachiOnResume:
    setvar LASTRESULT SPECIES_JIRACHI
    callasm CheckIfCaught
    compare LASTRESULT 0x1
    if notequal _goto End
    hidesprite 5
    end

LevelScripts_CarnelidgeVolcanoPeak_StoryEvents:
    levelscript VarStorySequence 0x0 LevelScript_InitiateStoryConclusion @ New saves
    levelscript VarStorySequence 0x1 LevelScript_InitiateStoryConclusion @ Historic saves that stepped on tile already
    levelscript VarStorySequence 0xE LevelScript_StoryConclusionCutscene
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_InitiateStoryConclusion:
    special 0xAF @ Dismount bike if on it
    setvar VarStorySequence 0x1 @ Sequence started
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA
    if equal _call PlayerWalkRight_Return
    compare 0x4000 0xC
    if equal _call PlayerWalkLeft_Return
    applymovement PLAYER m_PlayerWalksToConfrontAlistair
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    checkflag 0x93D @ Skipping Cutscenes
    if SET _goto SkippingCutscenes_CarnelidgeVolcanoPeak_StoppingAlistair
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
    callasm RestorePartyFromSafeBackup @ Rebuild the party stashed in gSaveBlock1->safeBackupParty when entering the empty world
    special 0x0 @ Heal player party (also tops off HP/PP after the box-format restore)
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
    waitmovement Selene
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
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _call ObtainHoundoominite
    if SET _call ObtainTyranitarite
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
    addvar VarStorySequence 0x5 @ Conclude the story event. This is incremented dramatically to ensure Flying/Teleporting/etc will be usable again
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    end

.global HandleJirachisAwakening
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

.global ObtainHoundoominite
ObtainHoundoominite:
    obtainitem ITEM_HOUNDOOMINITE 0x1
    return

.global ObtainTyranitarite
ObtainTyranitarite:
    obtainitem ITEM_TYRANITARITE 0x1
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
    lock
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

.global EventScript_CarnelidgeVolcano_UltraWormhole_Celesteela
EventScript_CarnelidgeVolcano_UltraWormhole_Celesteela:
    call UltraWormholePrompt
    cry SPECIES_CELESTEELA 0x0
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_DOUBLEEDGE
    setvar 0x8001 MOVE_AUTOTOMIZE
    setvar 0x8002 MOVE_LEECHSEED
    setvar 0x8003 MOVE_FLASHCANNON
    setwildbattle SPECIES_CELESTEELA 75 ITEM_NONE
    call UltraWormholeBattle
    setflag 0x67 @ Celesteela caught
    setvar LASTRESULT SPECIES_NECROZMA
    callasm CheckIfCaught
    compare LASTRESULT 0x1
    if notequal _call HandleUltraWormholeEclipse
    end

m_JirachiFloatsAway: .byte slide_up, slide_up, slide_up, slide_up, slide_up, slide_up, slide_up, end_m
m_CameraPanUpForVolcanion: .byte walk_up, walk_up, walk_up, end_m
m_CameraPanDownForVolcanion: .byte walk_down, walk_down, walk_down, end_m
m_VolcanionJumpOutOfLava: .byte jump_2_down, end_m
m_VolcanionJumpIntoLava: .byte jump_2_up, end_m
