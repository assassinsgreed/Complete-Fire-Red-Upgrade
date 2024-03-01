.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Selene, 14
.equ Alistair, 15
.equ StoryEventVar, 0x405C

.global MapScript_Route12RestHouse
MapScript_Route12RestHouse:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_Route12_RestHouse_FlightFlag
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route12_RestHouse_StoryEvents
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route12_RestHouse_FlightFlag:
    setworldmapflag 0x89B @ Visited Route 12 Rest House
    sethealingplace 0xD @ Route 12 Rest House
    end

LevelScripts_Route12_RestHouse_StoryEvents:
    levelscript StoryEventVar 0x0 LevelScript_RestHouse_Cutscene
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_RestHouse_Cutscene:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xD
    if lessorequal _call MovePlayerFromSouthEntrance
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xD
    if greaterthan _call MovePlayerFromEastEntrance
    sound 0x15 @ Exclaim
    applymovement Selene m_Surprise
    waitse
	applymovement Selene m_LookDown
    playbgm 0x196 @ Bianca Encounter
    msgbox gText_Route12RestHouse_Cutscene_SeleneGreetsPlayer MSG_NORMAL
    applymovement Selene m_Question
    msgbox gText_Route12RestHouse_Cutscene_SeleneAsksAboutBadges MSG_NORMAL
    call CountBadgesForAppraisal
    applymovement Alistair m_AlistairArrives
    msgbox gText_Route12RestHouse_Cutscene_SeleneCommentsOnGymThemes MSG_NORMAL
    waitmovement Alistair
    playbgm 0x173 @ Alistair's Theme
    applymovement PLAYER m_LookLeft
    msgbox gText_Route12RestHouse_Cutscene_AlistairArrives MSG_NORMAL
    applymovement Selene m_LookLeft
    msgbox gText_Route12RestHouse_Cutscene_SeleneRepliesToAlistairsComment MSG_NORMAL
    applymovement Alistair m_WalkUp
    waitmovement Alistair
    applymovement Alistair m_LookRight
    applymovement PLAYER m_LookUp
    msgbox gText_Route12RestHouse_Cutscene_AlistairRetortsToSelenesComment MSG_NORMAL
    checkflag 0x3F @ Casey hidden in gym
    if SET _call AlistairCommentsOnLaplazBeingVacant
    if NOT_SET _call AlistairCommentsOnLaplazAlmostShuttingDown
    msgbox gText_Route12RestHouse_Cutscene_SeleneDismissesAlistairsClaim MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_AlistairDismissesSelenesClaim MSG_NORMAL
    applymovement Alistair m_WalkDown
    waitmovement Alistair
    applymovement Alistair m_LookRight
    applymovement Selene m_LookDown
    applymovement PLAYER m_LookLeft
    msgbox gText_Route12RestHouse_Cutscene_AlistairTriesToLeave MSG_NORMAL
    applymovement Alistair m_AlistairStartsToLeave
    applymovement Selene m_SeleneStopsAlistair
    waitmovement Selene
    playbgm 0x159 @ N's Farewell
    msgbox gText_Route12RestHouse_Cutscene_SeleneStopsAlistair MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_Route12RestHouse_Cutscene_AlistairAcknowledgesBeingRecognized MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_SeleneAsksWhereAlistairWent MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_AlistairSharesSomeHistory MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_SeleneTalksAboutHerJourney MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_AlistairTalksAboutEmboar MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_SeleneTalksAboutHerResponsibilities MSG_NORMAL
    msgbox gText_Route12RestHouse_Cutscene_AlistairRejectsSelenesResponsibilities MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_Route12RestHouse_Cutscene_AlistairLeaves MSG_NORMAL
    applymovement Alistair m_NPCsLeave
    waitmovement Alistair
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    hidesprite Alistair
    pause DELAY_HALFSECOND
    applymovement Selene m_SeleneReturnsToPlayer
    waitmovement Selene
    applymovement PLAYER m_LookUp
    msgbox gText_Route12RestHouse_Cutscene_SeleneLeaves MSG_NORMAL
    applymovement Selene m_SeleneStopsAlistair
    waitmovement Selene
    applymovement PLAYER m_LookLeft
    applymovement Selene m_WalkDown
    waitmovement Selene
    applymovement Selene m_WalkDown
    waitmovement Selene
    applymovement Selene m_NPCsLeave
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookDown
    waitmovement Selene
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    hidesprite Selene
    fadedefaultbgm
    setflag 0x44 @ Hide Selene and Alistair in Rest House
    setvar StoryEventVar 0x1
    special 0x8E @ Refresh map
    end

MovePlayerFromSouthEntrance:
    compare 0x4000 0xC @ Player is on left entrance
    if equal _call PlayerWalkRight_Return
    applymovement PLAYER m_PlayerWalksUp
    waitmovement PLAYER
    return

MovePlayerFromEastEntrance:
    applymovement PLAYER m_PlayerWalksLeft
    waitmovement PLAYER
    return

CountBadgesForAppraisal:
    callasm CountBadges
    switch LASTRESULT
    case 0, LessThanTwoBadges
    case 1, LessThanTwoBadges
    case 2, TwoBadges
    case 3, ThreeBadges
    case 4, FourBadges
    case 5, FiveBadges
    return

LessThanTwoBadges:
    fanfare 0x10F @ Big Failure
    msgbox gText_Route12RestHouse_Cutscene_SeleneLessThanTwoBadges MSG_KEEPOPEN
    waitfanfare
    return

TwoBadges:
    fanfare 0x10F @ Big Failure
    msgbox gText_Route12RestHouse_Cutscene_SeleneTwoBadges MSG_KEEPOPEN
    waitfanfare
    return

ThreeBadges:
    fanfare 0x10E @ Small Failure
    msgbox gText_Route12RestHouse_Cutscene_SeleneThreeBadges MSG_KEEPOPEN
    waitfanfare
    return

FourBadges:
    fanfare 0x13E @ Obtain Item
    msgbox gText_Route12RestHouse_Cutscene_SeleneFourBadges MSG_KEEPOPEN
    waitfanfare
    return

FiveBadges:
    fanfare 0x13D @ Gym Victory
    msgbox gText_Route12RestHouse_Cutscene_SeleneFiveBadges MSG_KEEPOPEN
    waitfanfare
    return

AlistairCommentsOnLaplazBeingVacant:
    msgbox gText_Route12RestHouse_Cutscene_AlistairCommentsOnLaplazGymShuttingDown MSG_NORMAL
    return

AlistairCommentsOnLaplazAlmostShuttingDown:
    msgbox gText_Route12RestHouse_Cutscene_AlistairCommentsOnLaplazGymReopening MSG_NORMAL
    return

.global EventScript_Route12RestHouse_Boy
EventScript_Route12RestHouse_Boy:
    npcchatwithmovement gText_Route12RestHouse_Boy m_LookDown
    end

.global EventScript_Route12RestHouse_YoungGirl
EventScript_Route12RestHouse_YoungGirl:
    npcchatwithmovement gText_Route12RestHouse_YoungGirl m_LookDown
    end

.global EventScript_Route12RestHouse_PoliceOfficer
EventScript_Route12RestHouse_PoliceOfficer:
    npcchatwithmovement gText_Route12RestHouse_PoliceOfficer m_LookDown
    end

.global EventScript_Route12RestHouse_PsychicGirl
EventScript_Route12RestHouse_PsychicGirl:
    npcchatwithmovement gText_Route12RestHouse_PsychicGirl m_LookDown
    end

.global EventScript_Route12RestHouse_OldMan
EventScript_Route12RestHouse_OldMan:
    npcchatwithmovement gText_Route12RestHouse_OldMan m_LookLeft
    end

.global EventScript_Route12RestHouse_Girl
EventScript_Route12RestHouse_Girl:
    npcchatwithmovement gText_Route12RestHouse_Girl m_LookRight
    end

.global EventScript_Route12RestHouse_Dad
EventScript_Route12RestHouse_Dad:
    npcchatwithmovement gText_Route12RestHouse_Dad m_LookLeft
    end

.global EventScript_Route12RestHouse_GameboyKid
EventScript_Route12RestHouse_GameboyKid:
    npcchatwithmovement gText_Route12RestHouse_GameboyKid m_LookDown
    end

.global EventScript_Route12RestHouse_Hiker
EventScript_Route12RestHouse_Hiker:
    npcchat gText_Route12RestHouse_Hiker
    end

.global EventScript_Route12RestHouse_PokemartMan
EventScript_Route12RestHouse_PokemartMan:
    npcchat gText_Route12RestHouse_PokemartMan
    end

.global EventScript_Route12RestHouse_Beauty
EventScript_Route12RestHouse_Beauty:
    npcchatwithmovement gText_Route12RestHouse_Beauty m_LookUp
    end

m_PlayerWalksUp: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerWalksLeft: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, look_up, end_m
m_AlistairArrives: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_AlistairStartsToLeave: .byte walk_down, end_m
m_SeleneStopsAlistair: .byte walk_left, look_down, end_m
m_NPCsLeave: .byte walk_down, walk_down, walk_down, end_m
m_SeleneReturnsToPlayer: .byte walk_right, look_down, end_m
