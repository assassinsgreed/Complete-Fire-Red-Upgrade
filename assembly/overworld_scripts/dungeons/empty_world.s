.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ VarStorySequence, 0x4062
.equ Alistair, 0x2
.equ Rival, 0x3
.equ Selene, 0x4

.global MapScript_EmptyWorld_CarnelidgeVolcano
MapScript_EmptyWorld_CarnelidgeVolcano:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_EmptyWorld_CarnelidgeVolcano_PlayerPositioning
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_EmptyWorld_CarnelidgeVolcano_StoryEvents
    .byte MAP_SCRIPT_TERMIN

LevelScripts_EmptyWorld_CarnelidgeVolcano_PlayerPositioning:
    levelscript VarStorySequence 0x2 LevelScript_PlayerPosition
	.hword LEVEL_SCRIPT_TERMIN

LevelScripts_EmptyWorld_CarnelidgeVolcano_StoryEvents:
    levelscript VarStorySequence 0x2 LevelScript_ContinueStoryConclusion
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerPosition:
    applymovement PLAYER m_LookUp
    end

LevelScript_ContinueStoryConclusion:
    pause DELAY_1SECOND
    applymovement Rival m_WalkUp
    waitmovement Rival
    applymovement Rival m_LookLeft
    msgbox gText_EmptyWorld_RivalAsksAlistairWhatHappened MSG_NORMAL
    applymovement Alistair m_LookRight
    msgbox gText_EmptyWorld_AlistairRespondsToRivalsQuestion MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Selene m_Surprise
    waitmovement Selene
    applymovement Selene m_WalkUp
    applymovement Rival m_LookDown
    applymovement Alistair m_LookDown
    msgbox gText_EmptyWorld_SeleneCommentsOnWhatHeDid MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_EmptyWorld_AlistairJustifiesHimself1 MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_EmptyWorld_AlistairJustifiesHimself2 MSG_NORMAL
    applymovement Alistair m_LookRight
    msgbox gText_EmptyWorld_AlistairJustifiesHimself3 MSG_NORMAL
    msgbox gText_EmptyWorld_RivalChallengesAlistairsDecision MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairConfirmsHisDecision MSG_NORMAL
    msgbox gText_EmptyWorld_RivalAttemptsToBattle MSG_NORMAL
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    msgbox gText_EmptyWorld_RivalRealizesWhatHappened MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairConcludesHisPoint1 MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_EmptyWorld_AlistairConcludesHisPoint2 MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    applymovement Selene m_LookRight
    applymovement Alistair m_LookLeft
    msgbox gText_EmptyWorld_SeleneCondemnsAlistair MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairRebukesSelene MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneApprehendsAlistair MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairAcceptsHisFate MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneGivesAlistairHisSentence MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    applymovement Selene m_LookDown
    msgbox gText_EmptyWorld_SeleneLeavesWithAlistair MSG_NORMAL
    applymovement Alistair m_WalkLeft
    waitmovement Alistair
    applymovement Alistair m_SeleneAndAlistairStartToLeave
    applymovement Selene m_SeleneAndAlistairStartToLeave
    waitmovement Selene
    applymovement Selene m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_EmptyWorld_SeleneTalksToPlayer MSG_NORMAL
    applymovement Rival m_WalkToSelene
    waitmovement Rival
    applymovement Selene m_LookUp
    msgbox gText_EmptyWorld_RivalAsksSeleneHowToFixThings MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneExplainsUltraSpace MSG_NORMAL
    msgbox gText_EmptyWorld_RivalWillGoToUltraSpace MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneDisapprovesOfRivalsChoice MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_EmptyWorld_AlistairRebukesRival MSG_NORMAL
    msgbox gText_EmptyWorld_RivalReaffirmsTheirChoice MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneGivesIn MSG_NORMAL
    applymovement Selene m_LookDown
    msgbox gText_EmptyWorld_SeleneTakesAlistairAway MSG_NORMAL
    applymovement Alistair m_SeleneAndAlistairLeave
    applymovement Selene m_SeleneAndAlistairLeave
    waitmovement Selene
    hidesprite Selene
    hidesprite Alistair
    playse 0x9 @ Exit room
    msgbox gText_EmptyWorld_RivalCommentsOnTheirDeparture MSG_NORMAL
    applymovement Rival m_WalkRight
    waitmovement Rival
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_EmptyWorld_RivalAddressesPlayer MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookRight
    msgbox gText_EmptyWorld_RivalCommentsOnWorldState MSG_NORMAL
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_EmptyWorld_RivalAsksPlayerFavor MSG_YESNO
    compare LASTRESULT NO
    if equal _call PlayerSaidNoToRivalsRequest
    if notequal _call PlayerSaidYesToRivalsRequest
    msgboxsign
    msgbox gText_EmptyWorld_SystemMessageAboutWorldState MSG_SIGN
    msgboxnormal
    addvar VarStorySequence 0x1
    special 0x27 @ Copy player's party to memory (to be restored with special 0x28 later)
    special 0xEF @ Delete player's party
    setflag 0x271 @ In the empty world
    clearflag 0x829 @ Hide Pokedex in menu
    @ setflag 0x91D @ Hide Save in the menu (TODO: reenable after all dev is complete)
    end

PlayerSaidNoToRivalsRequest:
    msgbox gText_EmptyWorld_PlayerDoesNotWantToGoToUltraSpace MSG_NORMAL
    applymovement Rival m_WalkLeft
    waitmovement Rival
    applymovement Rival m_SeleneAndAlistairStartToLeave
    waitmovement Rival
    applymovement PLAYER m_LookLeft
    applymovement Rival m_SeleneAndAlistairLeave
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookDown
    waitmovement Rival
    playse 0x9 @ Exit room
    hidesprite Rival
    return

PlayerSaidYesToRivalsRequest:
    applymovement Rival m_Joy
    msgbox gText_EmptyWorld_PlayerWillGoToUltraSpaceWithRival MSG_NORMAL
    applymovement Rival m_WalkDown
    applymovement PLAYER m_LookDown
    waitmovement PLAYER
    setvar 0x8000 0x3 @ Rival follows player
    special 0xD1 @ Set up rival follower
    return

m_WalkToSelene: .byte walk_left, walk_left, walk_down, end_m
m_SeleneAndAlistairStartToLeave: .byte walk_down, walk_down, walk_down, end_m
m_SeleneAndAlistairLeave: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
