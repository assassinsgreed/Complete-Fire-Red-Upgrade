.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ PlutoEncounterVar, 0x4059
.equ PartnerVar, 0x4099 @ 0 for none, 1 for Rival, 2 for Alistair
.equ PartnerRival, 0x1
.equ PartnerAlistair, 0x2
.equ Rival, 0x19
.equ Alistair, 0x1A

# Includes both Route 11 South and North

@ TODO: Maybe buff up the pluto trainers since you'll always have a decent partner

.global MapScript_Route11South
MapScript_Route11South:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_SetPartnerPositions
    mapscript MAP_SCRIPT_ON_RESUME LevelScripts_Route11South_PartnerBattles
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_SetPartnerPositions:
    compare PlutoEncounterVar 0x1 @ Exit if story events havne't kicked off
    if lessthan _goto End
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x15
    if lessthan _goto End @ Player did not warp from a partner change, do not change facing
    movesprite2 Rival 0x1C 0x2E @ Update position of Rival permanently
    movesprite2 Alistair 0x1D 0x2E @ Update position of Alistair permanently
    applymovement PLAYER m_LookUp
    end

LevelScripts_Route11South_PartnerBattles:
    levelscript PlutoEncounterVar 0x2 LevelScript_PartnerBattles
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_PartnerBattles:
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
    
SetRivalBacksprite:
    setvar 0x5012 0x6
    return

SetAlistairBacksprite:
    setvar 0x5012 0x7
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

.global SignScript_Route11South_TrainerTips
SignScript_Route11South_TrainerTips:
    msgbox gText_Route11South_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route11South_MegaStoneRefiner
SignScript_Route11South_MegaStoneRefiner:
    msgbox gText_Route11South_MegaStoneRefinerSign MSG_SIGN
    end

.global EventScript_Route11South_Rival
EventScript_Route11South_Rival:
    faceplayer
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

.global EventScript_Route11South_Alistair
EventScript_Route11South_Alistair:
    faceplayer
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

RemovePartner:
    clearflag 0x908 @ End tag battles
    clearflag 0x910 @ Do not trigger wild double battles
    setvar 0x5011 0x0 @ Reset partner trainer ID
    setvar 0x5012 0x0 @ Reset partner trainer backsprite
    special 0xD2 @ Remove follower
    clearflag 0x42
    compare PartnerVar PartnerRival
    if greaterthan _call MovePlayerInFrontOfRival @ Had Alistair
    if equal _call MovePlayerInFrontOfAlistair @ Had Rival
    if lessthan _call ResetPlayerOnTileScript @ Reposition player after trying to leave the map
    return

MovePlayerInFrontOfRival:
    warpmuted 3 29 0xFF 0x1C 0x2F @ In front of rival
    return

MovePlayerInFrontOfAlistair:
    warpmuted 3 29 0xFF 0x1D 0x2F @ In front of Alistair
    return

ResetPlayerOnTileScript:
    getplayerpos 0x4000 0x4001
    warpmuted 3 29 0xFF 0x4000 0x4001 @ Same spot, done to reset partners
    return

.global TileScript_Route11South_North
TileScript_Route11South_North:
    lock
    compare PlutoEncounterVar 0xFF @ TODO: Change to real var for event end
    if equal _goto End
    compare PlutoEncounterVar 0xFF @ TODO: Change to real var for Rival battle
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
    compare PlutoEncounterVar 0xFF @ TODO: Change to real var
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
    playbgm 0x156 @ Alistair's Theme
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

m_RivalWalksToMeetPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_RivalAndPlayerWalkToAlistair: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_down, end_m
m_AlistairWalksToMeetingPlace: .byte walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_up, look_left, end_m
m_AlistairLinesUpWithRival: .byte walk_up, look_down, end_m
