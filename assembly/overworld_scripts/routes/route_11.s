.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ South
.equ PlutoEncounterVar, 0x4059
.equ PartnerVar, 0x4099 @ 0 for none, 1 for Rival, 2 for Alistair
.equ PartnerRival, 0x1
.equ PartnerAlistair, 0x2
.equ Rival, 0x19
.equ Alistair, 0x1A
.equ Clancy, 0x1B
.equ Ena, 0x1C

.global MapScript_Route11South
MapScript_Route11South:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_SetPartnerPositions
    mapscript MAP_SCRIPT_ON_RESUME MapResumeScript_SetupPartnerBattles
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route11South_PostRonaldBattleCutscenes
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_SetPartnerPositions:
    compare PlutoEncounterVar 0x1 @ Exit if story events haven't kicked off
    if lessthan _goto End
    checkflag 0x26F @ Spoke to Ena
    if SET _call SetEnaLocationPostBadge7
    movesprite2 Rival 0x1C 0x2E @ Update position of Rival permanently
    movesprite2 Alistair 0x1D 0x2E @ Update position of Alistair permanently
    compare PlutoEncounterVar 0x4 @ Exit if player has beaten Team Pluto (i.e. no more partnering)
    if greaterorequal _goto End
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x15
    if lessthan _goto End @ Player did not warp from a partner change, do not change facing
    applymovement PLAYER m_LookUp
    end

MapResumeScript_SetupPartnerBattles:
    compare PlutoEncounterVar 0x2
    if notequal _goto End
    special 0xE1 @ Check if player has follower
    compare LASTRESULT FALSE
    if equal _goto End
    setflag 0x910 @ Double wild battle
    setflag 0x908 @ Set tag battle
    special 0x0 @ Heal party
    compare PartnerVar PartnerRival
    if equal _call SetRivalBacksprite
    if greaterthan _call SetAlistairBacksprite    
    end

SetEnaLocationPostBadge7:
    movesprite 29 0x2A 0x36
    movesprite2 29 0x2A 0x36
    return

SetRivalBacksprite:
    setvar 0x5012 0x6
    return

SetAlistairBacksprite:
    setvar 0x5012 0x7
    return

LevelScripts_Route11South_PostRonaldBattleCutscenes:
    levelscript PlutoEncounterVar 0x3 LevelScript_PlayerReturnsToRivalAndAlistair
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerReturnsToRivalAndAlistair:
    applymovement PLAYER m_LookUp
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalCommentsOnPlayersReturn MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairCommentsOnPlayersReturn MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Alistair m_Surprise
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairCommentsOnMegaRing MSG_NORMAL
    call PlayerWalkLeft_Return
    applymovement PLAYER m_LookUp
    fanfare 0x13E
    msgbox gText_Route11SouthHouse_PlutoEvent_GiveRivalHisMegaStone MSG_KEEPOPEN
    waitfanfare
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalAppreciatesMegaRing MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairCommentsOnOldMan MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalWantsToBattle MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairWillSuperviseBattle MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalHealsPlayer MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalWaitsToBattle MSG_NORMAL
    setvar PlutoEncounterVar 0x4
    end

.global MapScript_Route11SouthHouse
MapScript_Route11SouthHouse:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_SetRefinerFacing
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route11SouthHouse_RonaldCutscene
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_SetRefinerFacing:
    compare PlutoEncounterVar 0x3
    if lessthan _goto End
    setobjectmovementtype 0x1 look_down
    end

LevelScripts_Route11SouthHouse_RonaldCutscene:
    levelscript PlutoEncounterVar 0x2 LevelScript_RonaldEncounterCutscene
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_RonaldEncounterCutscene:
    setvar PartnerVar 0x0
    setvar PlutoEncounterVar 0x1
    call ResetParnerState
    playbgm 0x19A 0x1 @ Encounter Team Pluto (Permanent for the cutscene; player warps mean this doesn't need to be overridden again)
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldThreatensRefiner MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerRefuses MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldAccepts MSG_NORMAL
    applymovement 0x2 m_WalkRight
    applymovement PLAYER m_ApproachRonald
    waitmovement PLAYER
    applymovement 0x2 m_LookDown
    waitmovement 0x2
    applymovement 0x2 m_Question
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldAccusesPlayer MSG_YESNO
    compare LASTRESULT YES
    if equal _call SaidYesToRonald
    if notequal _call SaidNoToRonald
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldStartsToRecognizePlayer MSG_NORMAL
    checkgender
    compare LASTRESULT 0x0 @ Male
    if equal _call RonaldChecksMaleDescription
    if notequal _call RonaldChecksFemaleDescription
    applymovement 0x2 m_Joy
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldIsReadyToBattle MSG_NORMAL
    applymovement 0x2 m_LookRight
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldTellsRefinerToMove MSG_NORMAL
    applymovement 0x1 m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerWarnsPlayer MSG_NORMAL
    applymovement 0x1 m_WalkToTheSide
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldScoldsRefiner MSG_NORMAL
    applymovement 0x2 m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldChallengesPlayer MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 0xC8 0x100 gText_Route11SouthHouse_PlutoEvent_RonaldBattleIntro gText_Route11SouthHouse_PlutoEvent_RonaldBattleLoss PostRonaldBattle
    end

SaidYesToRonald:
    sound 0x15 @ Exclaim
    applymovement 0x2 m_Surprise
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldAppreciatesHonesty MSG_NORMAL
    return

SaidNoToRonald:
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldDoesNotAppreciateDishonesty MSG_NORMAL
    return

RonaldChecksMaleDescription:
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldGivesMaleDescriptor MSG_NORMAL
    return

RonaldChecksFemaleDescription:
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldGivesFemaleDescriptor MSG_NORMAL
    return

PostRonaldBattle:
    setvar PlutoEncounterVar 0x3
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldAsksPlayerToJoin MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerSaidYesToJoining
    if notequal _call PlayerSaidNoToJoining
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldThreatensThePlayer MSG_NORMAL
    applymovement 0x1 m_LookLeft
    applymovement 0x2 m_LookRight
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldThreatensOldMan MSG_NORMAL
    applymovement 0x2 m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldLeaves MSG_NORMAL
    fadescreen FADEOUT_BLACK
    setflag 0x41 @ Hide team pluto
    hidesprite 0x2 @ Ronald leaves
    playse 0x9 @ Exit room
    waitse 
    fadedefaultbgm
    fadescreen FADEIN_BLACK
    pause DELAY_HALFSECOND
    applymovement 0x1 m_RefinerWalksToPlayer
    waitmovement 0x1
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerThanksPlayer MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement 0x1 m_Surprise
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerLearnsOfAlistairsInvolvement MSG_NORMAL
    applymovement 0x1 m_RefinerGetsMegaRing
    waitmovement 0x1
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerGivesMegaRing MSG_NORMAL
    obtainitem ITEM_MEGA_RING 0x1
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerExplainsMegaRing MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RefinerBidsPlayerFarewell MSG_NORMAL
    pause DELAY_HALFSECOND
    warp 3 29 0xFF 0x1D 0x2F
    end

PlayerSaidYesToJoining:
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldWhenPlayerSaysYes MSG_NORMAL
    return

PlayerSaidNoToJoining:
    msgbox gText_Route11SouthHouse_PlutoEvent_RonaldWhenPlayerSaysNo MSG_NORMAL
    return

.global EventScript_Route11South_TM68GigaImpact
EventScript_Route11South_TM68GigaImpact:
    setvar CHOSEN_ITEM ITEM_TM68
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11South_TM51SteelWing
EventScript_Route11South_TM51SteelWing:
    setvar CHOSEN_ITEM ITEM_TM51
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11South_Mawilite
EventScript_Route11South_Mawilite:
    finditem ITEM_MAWILITE 0x1
    end

.global EventScript_Route11South_TeamPlutoRoss
EventScript_Route11South_TeamPlutoRoss:
    trainerbattle0 0x0 0xB3 0x0 gText_Route11South_TeamPlutoRoss_Intro gText_Route11South_TeamPlutoRoss_Defeat
    msgbox gText_Route11South_TeamPlutoRoss_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoGreta
EventScript_Route11South_TeamPlutoGreta:
    trainerbattle0 0x0 0xB4 0x0 gText_Route11South_TeamPlutoGreta_Intro gText_Route11South_TeamPlutoGreta_Defeat
    msgbox gText_Route11South_TeamPlutoGreta_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoNellie
EventScript_Route11South_TeamPlutoNellie:
    trainerbattle0 0x0 0xB5 0x0 gText_Route11South_TeamPlutoNellie_Intro gText_Route11South_TeamPlutoNellie_Defeat
    msgbox gText_Route11South_TeamPlutoNellie_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoHelga
EventScript_Route11South_TeamPlutoHelga:
    trainerbattle0 0x0 0xB6 0x0 gText_Route11South_TeamPlutoHelga_Intro gText_Route11South_TeamPlutoHelga_Defeat
    msgbox gText_Route11South_TeamPlutoHelga_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoKareem
EventScript_Route11South_TeamPlutoKareem:
    trainerbattle0 0x0 0xB7 0x0 gText_Route11South_TeamPlutoKareem_Intro gText_Route11South_TeamPlutoKareem_Defeat
    msgbox gText_Route11South_TeamPlutoKareem_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoChung
EventScript_Route11South_TeamPlutoChung:
    trainerbattle0 0x0 0xB8 0x0 gText_Route11South_TeamPlutoChung_Intro gText_Route11South_TeamPlutoChung_Defeat
    msgbox gText_Route11South_TeamPlutoChung_Chat MSG_NORMAL
    end

.global EventScript_Route11South_LassTabitha
EventScript_Route11South_LassTabitha:
    trainerbattle0 0x0 0xB9 0x0 gText_Route11South_LassTabitha_Intro gText_Route11South_LassTabitha_Defeat
    msgbox gText_Route11South_LassTabitha_Chat MSG_NORMAL
    end

.global EventScript_Route11South_CrushGirlAlisa
EventScript_Route11South_CrushGirlAlisa:
    trainerbattle0 0x0 0xBA 0x0 gText_Route11South_CrushGirlAlisa_Intro gText_Route11South_CrushGirlAlisa_Defeat
    msgbox gText_Route11South_CrushGirlAlisa_Chat MSG_NORMAL
    end

.global EventScript_Route11South_EngineerDale
EventScript_Route11South_EngineerDale:
    trainerbattle0 0x0 0xBB 0x0 gText_Route11South_EngineerDale_Intro gText_Route11South_EngineerDale_Defeat
    msgbox gText_Route11South_EngineerDale_Chat MSG_NORMAL
    end

.global EventScript_Route11South_CollectorOrville
EventScript_Route11South_CollectorOrville:
    trainerbattle0 0x0 0xBC 0x0 gText_Route11South_CollectorOrville_Intro gText_Route11South_CollectorOrville_Defeat
    msgbox gText_Route11South_CollectorOrville_Chat MSG_NORMAL
    end

.global SignScript_Route11South_HessonPass
SignScript_Route11South_HessonPass:
    msgbox gText_Route11South_HessonPassSign MSG_SIGN
    end

.global SignScript_Route11South_TrainerTips_WildDoubleBattles
SignScript_Route11South_TrainerTips_WildDoubleBattles:
    msgbox gText_Route11South_TrainerTipsWildDoubleBattlesSign MSG_SIGN
    end

.global SignScript_Route11South_MegaStoneRefiner
SignScript_Route11South_MegaStoneRefiner:
    msgbox gText_Route11South_MegaStoneRefinerSign MSG_SIGN
    end

.global SignScript_Route11South_TrainerTips_MegaEvolution
SignScript_Route11South_TrainerTips_MegaEvolution:
    msgbox gText_Route11South_TrainerTipsMegaEvolution MSG_SIGN
    end

.global EventScript_Route11South_Rival
EventScript_Route11South_Rival:
    faceplayer
    compare PlutoEncounterVar 0x4
    if equal _goto RivalBattlePrompt
    compare PartnerVar PartnerRival
    if equal _goto RivalPromptToReturn
    msgbox gText_Route11South_PlutoEvent_TeamUpWithRivalPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _call TeamUpWithRival
    if notequal _call DoNotTeamUpWithRival
    end

RivalPromptToReturn:
    msgbox gText_Route11South_PlutoEvent_RivalReturnToStartingPointPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto RivalReturnToStartingPoint
    msgbox gText_Route11South_PlutoEvent_RivalReturnToStartingPointNo MSG_NORMAL
    end

RivalReturnToStartingPoint:
    msgbox gText_Route11South_PlutoEvent_RivalReturnToStartingPointYes MSG_NORMAL
    call MovePlayerInFrontOfRival
    end

TeamUpWithRival:
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_Route11South_PlutoEvent_TeamUpWithRivalYes MSG_NORMAL
    waitfanfare
    special 0xE1 @ Check if player has a partner already
    compare LASTRESULT TRUE
    if equal _call RemovePartner
    call SetupRoute11RivalPartner
    setvar PartnerVar PartnerRival
    setvar PlutoEncounterVar 0x2
    end

DoNotTeamUpWithRival:
    msgbox gText_Route11South_PlutoEvent_TeamUpWithRivalNo MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

RivalBattlePrompt:
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalBattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DeniedRivalBattle
    playbgm 0x195
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalEagerToBattle MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairAsksPlayerAndRivalToTakePlaces MSG_NORMAL
    special 0xAF @ Dismount bike if on it
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x1C
    if equal _call PlayerWalkLeft_Return
    compare 0x4001 0x2F
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2F
    if lessthan _call PlayerWalkDown_Return
    call PlayerWalkDown_Return
    applymovement PLAYER m_LookRight
    applymovement Rival m_RivalPositionsForBattle
    waitmovement Rival
    applymovement Alistair m_AlistairTakesSupervisionPosition
    waitmovement Alistair
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalInitiatesBattle MSG_NORMAL
    call SetupMugshotRival
    copyvar 0x4001 0x408E
    setvar 0x4000 201 @ trainer ID, which is 201 + 0-7 depending on value in 0x408E
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_Route11SouthHouse_PlutoEvent_RivalLoses
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalCommentsOnLossAfterBattle MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairConcludesBattle MSG_NORMAL
    applymovement Alistair m_AlistairGivesHMFly
    waitmovement Alistair
    obtainitem ITEM_HM02 0x1
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairExplainsFly MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalAppreciatesFly MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalPreparesToLeave MSG_NORMAL
    applymovement Rival m_RivalLeaves
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement Alistair m_LookLeft
    applymovement PLAYER m_LookUp
    waitmovement Rival
    applymovement Alistair m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairPreparesToLeave MSG_NORMAL
    applymovement Alistair m_AlistairLeaves
    pause DELAY_1SECOND
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookLeft
    waitmovement Alistair
    applymovement PLAYER m_PlayerLeavingAfterPlutoEvents
    waitmovement PLAYER
    fadescreen FADEOUT_BLACK
    pause DELAY_HALFSECOND
    applymovement PLAYER m_PlayerAsCameraMovesToAlistairAndRival
    waitmovement PLAYER
    fadescreen FADEIN_BLACK
    pause DELAY_HALFSECOND
    playbgm 0x159 @ N's Farewell
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairPleadsForRivalToStop MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    waitmovement Rival
    applymovement Rival m_LookRight
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalRespondsToAlistair MSG_NORMAL
    applymovement Alistair m_WalkLeft
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairAsksAboutPlayer MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalExplainsRelationship MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairAsksAboutDream MSG_NORMAL
    applymovement Rival m_Question
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalCommentsOnFriendship MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairCommentsOnRivalsRelationship MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalUpset MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalConsideringGivingUp MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairRevealsHisHistory MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairReallyRevealsHisHistory MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement Alistair m_LookLeft
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairMakesAnOfferToRival MSG_NORMAL
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalAcceptsTheOffer MSG_NORMAL
    fadescreen FADEOUT_BLACK
    pause DELAY_HALFSECOND
    fadedefaultbgm
    applymovement PLAYER m_PlayerAsCameraMovesBack
    waitmovement PLAYER
    setvar PlutoEncounterVar 0x5
    hidesprite Rival
    hidesprite Alistair
    setflag 0x42 @ Hide Rival and Alistair on Route 11 south
    fadescreen FADEIN_BLACK
    end

DeniedRivalBattle:
    msgbox gText_Route11SouthHouse_PlutoEvent_RivalWaitsToBattle MSG_NORMAL
    end

.global EventScript_Route11South_Alistair
EventScript_Route11South_Alistair:
    faceplayer
    compare PlutoEncounterVar 0x4
    if equal _goto AlistairBattleSupervision
    compare PartnerVar PartnerAlistair
    if equal _goto AlistairPromptToReturn
    msgbox gText_Route11South_PlutoEvent_TeamUpWithAlistairPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _call TeamUpWithAlistair
    if notequal _call DoNotTeamUpWithAlistair
    end

AlistairPromptToReturn:
    msgbox gText_Route11South_PlutoEvent_AlistairReturnToStartingPointPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto AlistairReturnToStartingPoint
    msgbox gText_Route11South_PlutoEvent_AlistairReturnToStartingPointNo MSG_NORMAL
    end

AlistairReturnToStartingPoint:
    msgbox gText_Route11South_PlutoEvent_AlistairReturnToStartingPointYes MSG_NORMAL
    call MovePlayerInFrontOfAlistair
    end

TeamUpWithAlistair:
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_Route11South_PlutoEvent_TeamUpWithAlistairYes MSG_NORMAL
    waitfanfare
    special 0xE1 @ Check if player has a partner already
    compare LASTRESULT TRUE
    if equal _call RemovePartner
    call SetupRoute11AlistairPartner
    setvar PartnerVar PartnerAlistair
    setvar PlutoEncounterVar 0x2
    end

DoNotTeamUpWithAlistair:
    msgbox gText_Route11South_PlutoEvent_TeamUpWithAlistairNo MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

AlistairBattleSupervision:
    msgbox gText_Route11SouthHouse_PlutoEvent_AlistairBattleSupervision MSG_NORMAL
    end

ResetParnerState:
    clearflag 0x908 @ End tag battles
    clearflag 0x910 @ Do not trigger wild double battles
    setvar 0x5011 0x0 @ Reset partner trainer ID
    setvar 0x5012 0x0 @ Reset partner trainer backsprite
    special 0xD2 @ Remove follower
    clearflag 0x42
    return

RemovePartner:
    compare PartnerVar PartnerRival
    if lessthan _call FadeScreenForLeavingRouteReset
    call ResetParnerState
    compare PartnerVar PartnerRival
    if greaterthan _call MovePlayerInFrontOfRival @ Had Alistair
    if equal _call MovePlayerInFrontOfAlistair @ Had Rival
    if lessthan _call ResetPlayerOnTileScript @ Reposition player after trying to leave the map
    return

FadeScreenForLeavingRouteReset:
    fadescreen FADEOUT_BLACK
    return

MovePlayerInFrontOfRival:
    warpmuted 3 29 0xFF 0x1C 0x2F @ In front of rival
    return

MovePlayerInFrontOfAlistair:
    warpmuted 3 29 0xFF 0x1D 0x2F @ In front of Alistair
    return

ResetPlayerOnTileScript:
    special 0x8E
    fadescreen FADEIN_BLACK
    return

.global TileScript_Route11South_North
TileScript_Route11South_North:
    lock
    compare PlutoEncounterVar 0x5
    if equal _goto End
    compare PlutoEncounterVar 0x4
    if equal _goto NeedToBattleRivalFirst
    msgbox gText_Route11South_PlutoEvent_HeadingNorth_PlutoNotDefeated MSG_NORMAL
    call PlayerWalksAwayFromHessonAndNorthTiles
    release
    end

NeedToBattleRivalFirst:
    msgbox gText_Route11South_PlutoEvent_HeadingNorth_RivalNotBattled MSG_NORMAL
    call PlayerWalksAwayFromHessonAndNorthTiles
    end

.global TileScript_Route11South_SouthByFerrox
TileScript_Route11South_SouthByFerrox:
    special 0xE1 @ Check if the player has a follower
    compare LASTRESULT TRUE
    if equal _goto RemoveFollowerWhenLeavingRoute11
    release
    end

.global TileScript_Route11South_SouthByHesson
TileScript_Route11South_SouthByHesson:
    special 0xE1 @ Check if the player has a follower
    compare LASTRESULT TRUE
    if equal _goto End
    lock
    msgbox gText_Route11South_PlutoEvent_HeadingSouth_WithoutPartner MSG_NORMAL
    call PlayerWalkUp_Return
    release
    end

.global TileScript_Route11South_HessonPass
TileScript_Route11South_HessonPass:
    lock
    compare PlutoEncounterVar 0x5
    if equal _goto HandleEnaEvent
    compare PlutoEncounterVar 0x4
    if equal _goto NeedToBattleRivalFirst
    special 0xE1 @ Check if the player has a follower
    compare LASTRESULT FALSE
    if equal _goto End
    special 0xD3 @ Face partner
    msgbox gText_Route11South_PlutoEvent_HessonPassWithPartnerCommon MSG_NORMAL
    compareplayerfacing INTERNAL_DOWN
    if equal _call PlayerWalksAwayFromHessonAndNorthTiles
    if notequal _call PlayerWalksAwayFromHessonLeft
    release
    end

HandleEnaEvent:
    checkflag 0x826 @ Has Tsarvosa City gym badge
    if NOT_SET _goto End
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    applymovement PLAYER m_LookUp
    playse 0x9 @ Exit room
    pause DELAY_HALFSECOND
    clearflag 0x56 @ Show Ena
    showsprite 29
    applymovement 29 m_WalkDown
    waitmovement 29
    msgbox gText_Route11South_BumpingIntoEna MSG_NORMAL
    msgbox gText_Route11South_EnaAsksPlayerIfRecognizes MSG_YESNO
    compare LASTRESULT NO
    if notequal _call RecognizesEna
    if equal _call DoesNotRecognizeEna
    msgbox gText_Route11South_EnaExplainsWhatHappenedSinceBattle MSG_NORMAL
    applymovement Ena m_LookLeft
    playbgm 0x159 @ N's Farewell
    applymovement 29 m_LookLeft
    msgbox gText_Route11South_EnaAsksForHelp MSG_NORMAL
    applymovement 29 m_LookDown
    fadedefaultbgm
    call SetEnaLocationPostBadge7
    setflag 0x26F @ Spoke to Ena
    goto EventScript_Route11South_EnaPostGym7

RecognizesEna:
    msgbox gText_Route11South_EnaRecognized MSG_NORMAL
    return

DoesNotRecognizeEna:
    msgbox gText_Route11South_EnaNotRecognized MSG_NORMAL
    return

PlayerWalksAwayFromHessonLeft:
    call PlayerWalkLeft_Return
    call PlayerWalkLeft_Return
    return

PlayerWalksAwayFromHessonAndNorthTiles:
    call PlayerWalkDown_Return
    call PlayerWalkDown_Return
    return

.global TileScript_Route11South_West
TileScript_Route11South_West:
    compare PlutoEncounterVar 0x5
    if equal _goto End
    compare PlutoEncounterVar 0x0 @ Event hasn't started
    if equal _goto InitiatePlutoEncounter
    special 0xE1 @ Check if the player has a follower
    compare LASTRESULT TRUE
    if equal _goto RemoveFollowerWhenLeavingRoute11
    release
    end

RemoveFollowerWhenLeavingRoute11:
    compare PartnerVar PartnerRival
    if equal _call RemoveRivalPartnerPrompt
    if greaterthan _call RemoveAlistairPartnerPrompt
    end

RemoveRivalPartnerPrompt:
    special 0xD3 @ Face partner
    msgbox gText_Route11South_PlutoEvent_LeavingRoute11WithRivalPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ReturnToRoute11Rival
    msgbox gText_Route11South_PlutoEvent_LeavingRoute11WithRivalYes MSG_NORMAL
    setvar PartnerVar 0x0
    setvar PlutoEncounterVar 0x1
    call RemovePartner
    end

ReturnToRoute11Rival:
    msgbox gText_Route11South_PlutoEvent_RivalReturnToStartingPointNo MSG_NORMAL
    call ReturnToRoute11Common
    end

RemoveAlistairPartnerPrompt:
    special 0xD3 @ Face partner
    msgbox gText_Route11South_PlutoEvent_LeavingRoute11WithAlistairPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ReturnToRoute11Alistair
    msgbox gText_Route11South_PlutoEvent_LeavingRoute11WithAlistairYes MSG_NORMAL
    setvar PartnerVar 0x0
    setvar PlutoEncounterVar 0x1
    call RemovePartner
    end

ReturnToRoute11Alistair:
    msgbox gText_Route11South_PlutoEvent_AlistairReturnToStartingPointNo MSG_NORMAL
    call ReturnToRoute11Common
    end

ReturnToRoute11Common:
    compareplayerfacing INTERNAL_UP
    if equal _call PlayerWalkUp_Return
    if equal _call PlayerWalkUp_Return @ Move twice to reset partner
    compareplayerfacing INTERNAL_RIGHT
    if equal _call PlayerWalkRight_Return
    if equal _call PlayerWalkRight_Return @ Move twice to reset partner
    end

InitiatePlutoEncounter:
    special 0xAF @ Dismount bike if on it
    lock
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route11South_PlutoEvent_RivalSpotsPlayer MSG_NORMAL
    applymovement Rival m_RivalWalksToMeetPlayer
    call PositionPlayerForPlutoEventInitialization
    waitmovement Rival
    msgbox gText_Route11South_PlutoEvent_RivalExplainsPlutoTrouble MSG_NORMAL
    applymovement Rival m_RivalAndPlayerWalkToAlistair
    applymovement PLAYER m_RivalAndPlayerWalkToAlistair
    waitmovement PLAYER
    applymovement Alistair m_AlistairWalksToMeetingPlace
    waitmovement Alistair
    playbgm 0x173 @ Alistair's Theme
    msgbox gText_Route11South_PlutoEvent_AlistairAcknowledgesRival MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_Route11South_PlutoEvent_AlistairAcknowledgesPlayer MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    applymovement PLAYER m_LookRight
    msgbox gText_Route11South_PlutoEvent_AlistairAsksForHelp MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_Route11South_PlutoEvent_RivalAgreesToHelp MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement Alistair m_LookLeft
    msgbox gText_Route11South_PlutoEvent_RivalAsksPlayerToHelp MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerAgreedToHelp
    if notequal _call PlayerDidNotAgreeToHelp
    applymovement Rival m_LookDown
    applymovement Alistair m_LookLeft
    msgbox gText_Route11South_PlutoEvent_RivalFinalizesAgreementToHelp MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_AlistairMakesAPlan MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_RivalSignsPlayerUpToFight MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_AlistairAgrees MSG_NORMAL
    applymovement Alistair m_AlistairLinesUpWithRival
    waitmovement Alistair
    msgboxsign
    playbgm 0x110 @ Follow me (instructions)
    msgbox gText_Route11South_PlutoEvent_GameplayTip MSG_SIGN
    msgboxnormal
    movesprite2 Rival 0x1C 0x2E @ Update position of Rival permanently
    movesprite2 Alistair 0x1D 0x2E @ Update position of Alistair permanently
    setvar PlutoEncounterVar 0x1
    fadedefaultbgm
    release
    end

PositionPlayerForPlutoEventInitialization:
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2E
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2E
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2E
    if greaterthan _call PlayerWalkUp_Return
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2E
    if greaterthan _call PlayerWalkUp_Return
    applymovement PLAYER m_LookRight
    return

PlayerAgreedToHelp:
    msgbox gText_Route11South_PlutoEvent_PlayerAgreedToHelp MSG_NORMAL
    return

PlayerDidNotAgreeToHelp:
    msgbox gText_Route11South_PlutoEvent_PlayerDoesNotAgreeToHelp MSG_NORMAL
    return

.global EventScript_Route11South_TeamPlutoClancy
EventScript_Route11South_TeamPlutoClancy:
    faceplayer
    playbgm 0x19A 0x1 @ Encounter Team Pluto (Permanent for the cutscene; player warps mean this doesn't need to be overridden again)
    setflag 0x926 @ Follower will move during active script
    msgbox gText_Route11South_PlutoEvent_Clancy_InitiateConversationWithClancy MSG_NORMAL
    applymovement Clancy m_Surprise
    waitmovement Clancy
    msgbox gText_Route11South_PlutoEvent_Clancy_ClancySortOfRecognizesThePlayer MSG_NORMAL
    compare PLAYERFACING RIGHT
    if equal _call PlayerWalkToInFrontOfClancy
    call PlayerWalkRight_Return
    applymovement PLAYER m_LookUp
    compare PartnerVar PartnerRival
    if equal _call RivalLookUp
    if notequal _call AlistairLookUp
    applymovement Clancy m_LookRight
    applymovement Ena m_LookLeft
    msgbox gText_Route11South_PlutoEvent_Clancy_EnaDoesRecognizePlayer MSG_NORMAL
    goto ClancyAndEnaSharedEvent

PlayerWalkToInFrontOfClancy:
    call PlayerWalkDown_Return
    call PlayerWalkRight_Return
    return

RivalLookUp:
    applymovement Rival m_LookUp
    return

AlistairLookUp:
    applymovement Alistair m_LookUp
    return

.global EventScript_Route11South_TeamPlutoEna
EventScript_Route11South_TeamPlutoEna:
    faceplayer
    playbgm 0x19A 0x1 @ Encounter Team Pluto (Permanent for the cutscene; player warps mean this doesn't need to be overridden again)
    setflag 0x926 @ Follower will move during active script
    msgbox gText_Route11South_PlutoEvent_Ena_InitiateConversationWithEna MSG_NORMAL
    compare PLAYERFACING LEFT
    if equal _call PlayerWalkToInFrontOfEna
    call PlayerWalkLeft_Return
    applymovement PLAYER m_LookUp
    compare PartnerVar PartnerRival
    if equal _call RivalLookUp
    if notequal _call AlistairLookUp
    applymovement Clancy m_LookRight
    applymovement Ena m_LookLeft
    msgbox gText_Route11South_PlutoEvent_Ena_ClancyHearsTheCommotion MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_Ena_EnaRecognizesThePlayer MSG_NORMAL
    goto ClancyAndEnaSharedEvent

PlayerWalkToInFrontOfEna:
    call PlayerWalkDown_Return
    call PlayerWalkLeft_Return
    return

ClancyAndEnaSharedEvent:
    applymovement Clancy m_LookDown
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement Clancy m_Question
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    sound 0x15 @ Exclaim
    applymovement Clancy m_Surprise
    waitmovement Clancy
    applymovement Clancy m_LookRight
    msgbox gText_Route11South_PlutoEvent_Clancy_ClancyFinallyRecognizesPlayer MSG_NORMAL
    applymovement Ena m_Joy
    msgbox gText_Route11South_PlutoEvent_EnaHappy MSG_NORMAL
    applymovement Clancy m_LookDown
    applymovement Ena m_LookDown
    msgbox gText_Route11South_PlutoEvent_ClancyComplainsAboutPlayer MSG_NORMAL
    applymovement Clancy m_ClancyFrustratedJumps
    msgbox gText_Route11South_PlutoEvent_ClancyChallengesPlayer MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_EnaAgreesToTheChallenge MSG_NORMAL
    special 0xD3 @ Face partner
    compare PartnerVar PartnerRival
    if equal _call RivalCommentsOnPlutoBeforeBattle
    if notequal _call AlistairCommentsOnPlutoBeforeBattle
    applymovement PLAYER m_LookUp
    clearflag 0x926 @ Follower will not move during active script
    setflag 0x909 @ Two opponents
    setvar 0x5010 0xC7 @ Ena
    loadpointer 0x0 gText_Route11South_PlutoEvent_EnaLoses @ Ena's loss text
    special 0xAC @ Load second opponent's text into buffer
    trainerbattle3 0x3 0xC6 0x0 gText_Route11South_PlutoEvent_ClancyLoses @ Tag battle with current partner
    msgbox gText_Route11South_PlutoEvent_PostBattleClancyComplains MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_PostBattleEnaComplains MSG_NORMAL
    msgbox gText_Route11South_PlutoEvent_ClancyBacksDown MSG_NORMAL
    applymovement Clancy m_WalkLeft
    waitmovement Clancy
    applymovement Clancy m_LookRight
    applymovement Ena m_WalkRight
    waitmovement Ena
    applymovement Ena m_LookLeft
    special 0xD3 @ Face partner
    compare PartnerVar PartnerRival
    if equal _call RivalHealsAfterBattle
    compare PartnerVar PartnerAlistair
    if equal _call AlistairHealsAfterBattle
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    warpwalk 20 0 0 @ Event continued in house
    end

RivalCommentsOnPlutoBeforeBattle:
    msgbox gText_Route11South_PlutoEvent_RivalPreBattle MSG_NORMAL
    applymovement Rival m_LookUp
    return

AlistairCommentsOnPlutoBeforeBattle:
    msgbox gText_Route11South_PlutoEvent_AlistairPreBattle MSG_NORMAL
    applymovement Alistair m_LookUp
    return

RivalHealsAfterBattle:
    msgbox gText_Route11South_PlutoEvent_RivalHealsPlayer MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route11South_PlutoEvent_RivalCheersPlayerOn MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x24 @ Facing Ena
    if equal _call MoveRivalAndPlayerAfterClancyAndEna 
    return

MoveRivalAndPlayerAfterClancyAndEna:
    applymovement Rival m_WalkLeft
    waitmovement Rival
    applymovement Rival m_LookRight
    applymovement PLAYER m_WalkLeft
    waitmovement PLAYER
    return

AlistairHealsAfterBattle:
    msgbox gText_Route11South_PlutoEvent_AlistairHealsPlayer MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route11South_PlutoEvent_AlistairCheersPlayerOn MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x24 @ Facing Ena
    if equal _call MoveAlistairAndPlayerAfterClancyAndEna
    return

MoveAlistairAndPlayerAfterClancyAndEna:
    applymovement Alistair m_WalkLeft
    waitmovement Alistair
    applymovement Alistair m_LookRight
    applymovement PLAYER m_WalkLeft
    waitmovement PLAYER
    return

.global EventScript_Route11SouthRefiner_RefinerShop
EventScript_Route11SouthRefiner_RefinerShop:
    faceplayer
    msgbox gText_Route11SouthHouse_RefinerShopWelcome MSG_NORMAL
    checkitem ITEM_RUSTED_DATA 0x1
    compare LASTRESULT TRUE
    if TRUE _call RefinerExpandStock
    goto RefinerShopCommon

RefinerExpandStock:
    checkflag 0x26D @ Melmetalite explained
    if SET _goto RefinerShopCommon
    msgbox gText_Route11SouthHouse_RefinerHoldingRustedData MSG_NORMAL
    setflag 0x26D @ Melmetalite explained
    goto RefinerShopCommon

RefinerShopCommon:
    msgbox gText_Route11SouthHouse_RefinerShop MSG_KEEPOPEN
    checkitem ITEM_RUSTED_DATA 0x1
    compare LASTRESULT TRUE
    if equal _call HandleExpandedMegaStoneShop
    if notequal _call HandleMegaStoneShop
    msgbox gText_Route11SouthHouse_RefinerFarewell MSG_NORMAL
    end

HandleExpandedMegaStoneShop:
    pokemart ExpandedMegaStoneShop
    return

HandleMegaStoneShop:
    pokemart MegaStoneShop
    return

.align 1
ExpandedMegaStoneShop:
    .hword ITEM_VENUSAURITE_G
    .hword ITEM_CHARIZARDITE_G
    .hword ITEM_BLASTOISINITE_G
    .hword ITEM_LAPRASITE
    .hword ITEM_MELMETALITE @ Exclusive to this shop
    .hword ITEM_RILLABITE
    .hword ITEM_CINDERITE
    .hword ITEM_INTELLEITE
    .hword ITEM_CORVIKNITE
    .hword ITEM_ORBEETLITE
    .hword ITEM_COALOSSITE
    .hword ITEM_TOXTRICITE
    .hword ITEM_CENTISKORITE
    .hword ITEM_HATTERITE
    .hword ITEM_COPPERITE
    .hword ITEM_DURALUDITE
    .hword ITEM_NONE

.align 1
MegaStoneShop:
    .hword ITEM_VENUSAURITE_G
    .hword ITEM_CHARIZARDITE_G
    .hword ITEM_BLASTOISINITE_G
    .hword ITEM_LAPRASITE
    .hword ITEM_RILLABITE
    .hword ITEM_CINDERITE
    .hword ITEM_INTELLEITE
    .hword ITEM_CORVIKNITE
    .hword ITEM_ORBEETLITE
    .hword ITEM_COALOSSITE
    .hword ITEM_TOXTRICITE
    .hword ITEM_CENTISKORITE
    .hword ITEM_HATTERITE
    .hword ITEM_COPPERITE
    .hword ITEM_DURALUDITE
    .hword ITEM_NONE

m_RivalWalksToMeetPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_RivalAndPlayerWalkToAlistair: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_down, end_m
m_AlistairWalksToMeetingPlace: .byte walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_up, look_left, end_m
m_AlistairLinesUpWithRival: .byte walk_up, look_down, end_m
m_ClancyFrustratedJumps: .byte jump_onspot_down, jump_onspot_down, end_m
m_ApproachRonald: .byte walk_up, walk_up, end_m
m_WalkToTheSide: .byte walk_right, walk_right, look_down, end_m
m_RefinerWalksToPlayer: .byte walk_left, walk_left, walk_left, look_down, end_m
m_RefinerGetsMegaRing: .byte walk_left, walk_left, walk_left, walk_up, walk_up, pause_long, pause_long, walk_down, walk_down, walk_right, walk_right, walk_right, look_down, end_m
m_RivalPositionsForBattle: .byte walk_down, walk_right, walk_right, walk_down, look_left, end_m
m_AlistairTakesSupervisionPosition: .byte walk_left, look_down, end_m
m_AlistairGivesHMFly: .byte walk_right, walk_down, walk_down, look_right, pause_long, walk_left, pause_long, walk_up, walk_up, look_down, end_m
m_RivalLeaves: .byte walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_AlistairLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_PlayerLeavingAfterPlutoEvents: .byte walk_up, walk_right, walk_right, walk_right, end_m
m_PlayerAsCameraMovesToAlistairAndRival: .byte set_invisible, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
m_PlayerAsCameraMovesBack: .byte run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, set_visible, end_m

.global EventScript_Route11South_EnaPostGym7
EventScript_Route11South_EnaPostGym7:
    npcchatwithmovement gText_Route11South_EnaChat m_LookDown
    end

@ North
.global SignScript_LaplazTown_Entrance
SignScript_LaplazTown_Entrance:
    msgbox gText_LaplazTown_EntranceSign MSG_SIGN
    end

.global SignScript_Route11North_LaplazTenets
SignScript_Route11North_LaplazTenets:
    msgbox gText_Route11North_LaplazTenetsSign MSG_SIGN
    end

.global EventScript_Route11North_TM03Psyshock
EventScript_Route11North_TM03Psyshock:
    setvar CHOSEN_ITEM ITEM_TM03
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11North_TM47LowSweep
EventScript_Route11North_TM47LowSweep:
    setvar CHOSEN_ITEM ITEM_TM47
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11North_PainterIsobel
EventScript_Route11North_PainterIsobel:
    trainerbattle0 0x0 0xD9 0x0 gText_Route11North_PainterIsobel_Intro gText_Route11North_PainterIsobel_Defeat
    msgbox gText_Route11North_PainterIsobel_Chat MSG_NORMAL
    end

.global EventScript_Route11North_FishermanClint
EventScript_Route11North_FishermanClint:
    trainerbattle0 0x0 0xDA 0x0 gText_Route11North_FishermanClint_Intro gText_Route11North_FishermanClint_Defeat
    msgbox gText_Route11North_FishermanClint_Chat MSG_NORMAL
    end

.global EventScript_Route11North_ChannelerKatya
EventScript_Route11North_ChannelerKatya:
    trainerbattle0 0x0 0xDB 0x0 gText_Route11North_ChannelerKatya_Intro gText_Route11North_ChannelerKatya_Defeat
    msgbox gText_Route11North_ChannelerKatya_Chat MSG_NORMAL
    end

.global EventScript_Route11North_RockerNathaniel
EventScript_Route11North_RockerNathaniel:
    trainerbattle0 0x0 0xDC 0x0 gText_Route11North_RockerNathaniel_Intro gText_Route11North_RockerNathaniel_Defeat
    msgbox gText_Route11North_RockerNathaniel_Chat MSG_NORMAL
    end

.global EventScript_Route11North_NinjaBoyYao
EventScript_Route11North_NinjaBoyYao:
    trainerbattle0 0x0 0xDD 0x0 gText_Route11North_NinjaBoyYao_Intro gText_Route11North_NinjaBoyYao_Defeat
    msgbox gText_Route11North_NinjaBoyYao_Chat MSG_NORMAL
    end

.global EventScript_Route11North_ParasolLadyTina
EventScript_Route11North_ParasolLadyTina:
    trainerbattle0 0x0 0xDE 0x0 gText_Route11North_ParasolLadyTina_Intro gText_Route11North_ParasolLadyTina_Defeat
    msgbox gText_Route11North_ParasolLadyTina_Chat MSG_NORMAL
    end

.global EventScript_Route11North_FishermanJonah
EventScript_Route11North_FishermanJonah:
    trainerbattle0 0x0 0xDF 0x0 gText_Route11North_FishermanJonah_Intro gText_Route11North_FishermanJonah_Defeat
    msgbox gText_Route11North_FishermanJonah_Chat MSG_NORMAL
    end
