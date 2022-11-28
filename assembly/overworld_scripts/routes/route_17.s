.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.equ Hawthorne, 0x02
.equ Selene, 0x03
.equ Rival, 0x04
.equ StoryEventVar, 0x4055
.equ PlayerHasNotMetWithRival, 0x2
.equ PlayerMetWithRival, 0x3

.global SignScript_Route17_CaveSign
SignScript_Route17_CaveSign:
    msgbox gText_Route17_CaveSign MSG_SIGN
    end

.global EventScript_Route17_MeetingRival
EventScript_Route17_MeetingRival:
    lock
    faceplayer
    msgbox gText_Route17_MetWithRival MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_JoinRivalBelow
    waitmovement ALLEVENTS
    goto StoryEvents_TalkingWithHawthorneAndSelene

.global TileScript_Route17_StoryBlockersNorth
TileScript_Route17_StoryBlockersNorth:
    end

.global TileScript_Route17_StoryBlockersSouth
TileScript_Route17_StoryBlockersSouth:
    compare StoryEventVar PlayerHasNotMetWithRival
    if equal _goto TileEvent_MeetingRival
    compare StoryEventVar PlayerMetWithRival
    if equal _goto PlayerMustChooseStarter
    @ Else, do nothing
    end

.global TileScript_Route17_StoryCaveBlocker
TileScript_Route17_StoryCaveBlocker:
    @ TODO: Don't run this script if the player has chosen their starter!
    applymovement Hawthorne m_LookUp
    msgbox gText_Route17_HawthorneBlocker MSG_NORMAL
    applymovement PLAYER m_WalkDown
    applymovement Hawthorne m_LookRight
    end

.global EventScript_Route17_ProfessorHawthorne
EventScript_Route17_ProfessorHawthorne:
    npcchat2 Hawthorne m_LookRight gText_Route17_HawthorneChat
    @ TODO: Call starter choice script, if the correct var is set 
    end

.global EventScript_Route17_ChampionSelene
EventScript_Route17_ChampionSelene:
    npcchat2 Selene m_LookLeft gText_Route17_SeleneChat
    end

TileEvent_MeetingRival:
    compare StoryEventVar PlayerMetWithRival
    if equal _goto PlayerMustChooseStarter
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    lock
    compare 0x4000 0x11
    if equal _call SetPlayerFacingLeft
    compare 0x4000 0x11
    if notequal _call SetPlayerFacingRight
    waitmovement ALLEVENTS
    msgbox gText_Route17_MetWithRival MSG_NORMAL
    applymovement PLAYER m_LookUp
    goto StoryEvents_TalkingWithHawthorneAndSelene

StoryEvents_TalkingWithHawthorneAndSelene:
    applymovement Rival m_WalkUp
    playbgm 0x17F @ The first day
    msgbox gText_Route17_RivalCallingToChampion MSG_NORMAL
    applymovement Hawthorne m_FacePlayer
    applymovement Selene m_FacePlayer
    waitmovement ALLEVENTS
    msgbox gText_Route17_ChampionResponse MSG_NORMAL
    msgbox gText_Route17_RivalStammer MSG_NORMAL
    applymovement Hawthorne m_WalkToPlayer
    waitmovement ALLEVENTS
    msgbox gText_Route17_HawthorneDismisses MSG_NORMAL
    msgbox gText_Route17_RivalProtest MSG_NORMAL
    applymovement Selene m_JoinHawthorne
    applymovement Hawthorne m_LookRight
    waitmovement ALLEVENTS
    playbgm 0x196 @ Bianca Encounter
    msgbox gText_Route17_SeleneInterjection MSG_NORMAL
    msgbox gText_Route17_HawthorneYields MSG_NORMAL
    applymovement Hawthorne m_LookDown
    applymovement Selene m_LookDown
    msgbox gText_Route17_HawthornePromptsRival MSG_NORMAL
    applymovement Rival m_Joy
    msgbox gText_Route17_RivalGratitude MSG_NORMAL
    msgbox gText_Route17_HawthorneIntroduction MSG_NORMAL
    msgbox gText_Route17_RivalStartsExplanation MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_Route17_UrgePlayerToJoin MSG_NORMAL
    compare 0x4000 0x11
    if notequal _call WalkUp
    compare 0x4000 0x11
    if equal _call PlayerWalkToFaceHawthorne
    applymovement Rival m_LookUp
    msgbox gText_Route17_RivalsRequest MSG_NORMAL
    applymovement Selene m_Question
    msgbox gText_Route17_SelenesResponse MSG_NORMAL
    msgbox gText_Route17_RivalEmbarrassed MSG_NORMAL
    msgbox gText_Route17_SeleneFollowUp MSG_NORMAL
    msgbox gText_Route17_RivalTrainerInterest MSG_NORMAL
    applymovement Hawthorne m_LookRight
    applymovement Selene m_LookLeft
    waitmovement ALLEVENTS
    msgbox gText_Route17_SeleneProposesStarterPokemon MSG_NORMAL
    msgbox gText_Route17_HawthorneHesitant MSG_NORMAL
    msgbox gText_Route17_SeleneRespondsToHesitation MSG_NORMAL
    msgbox gText_Route17_HawthorneDigsIn MSG_NORMAL
    msgbox gText_Route17_SelenesProposal MSG_NORMAL
    msgbox gText_Route17_HawthorneAccepts MSG_NORMAL
    applymovement Hawthorne m_LookDown
    applymovement Selene m_LookDown
    msgbox gText_Route17_SeleneSendsPlayerOff MSG_NORMAL
    applymovement Rival m_Joy
    msgbox gText_Route17_RivalExcited MSG_NORMAL
    applymovement Rival m_RivalStartsToLeave
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookDown
    msgbox gText_Route17_RivalHeadsOut MSG_NORMAL
    applymovement Rival m_RivalLeavesToTalkToMom
    waitmovement ALLEVENTS
    hidesprite Rival
    setflag 0x02D @ Hide rival on route 17
    clearflag 0x02E @ Show rival in their house
    setvar StoryEventVar PlayerMetWithRival
    applymovement Hawthorne m_LookRight
    applymovement Selene m_LookLeft
    fadedefaultbgm
    end

SetPlayerFacingLeft:
    applymovement PLAYER m_LookLeft
    applymovement Rival m_LookRight
    return

SetPlayerFacingRight:
    applymovement Rival m_LookLeft
    compare 0x4000 0x0E
    if equal _call WalkRightOnce
    compare 0x4000 0x0D
    if equal _call WalkRightTwice
    applymovement PLAYER m_LookRight
    return

WalkRightOnce:
    applymovement PLAYER m_WalkRight
    return

WalkRightTwice:
    call WalkRightOnce
    waitmovement ALLEVENTS
    call WalkRightOnce
    waitmovement ALLEVENTS
    return

PlayerWalkToFaceHawthorne:
    applymovement PLAYER m_PlayerFaceHawthorne
    return

PlayerMustChooseStarter:
    compare PLAYERFACING look_down
    if equal _goto WalkUp
    goto WalkDown

m_JoinRivalBelow: .byte walk_left, walk_up, end_m
m_FacePlayer: .byte exclaim, look_down, end_m
m_WalkToPlayer: .byte walk_down, walk_left, walk_left, look_down, end_m 
m_JoinHawthorne: .byte walk_down, walk_left, walk_left, look_left, end_m
m_PlayerFaceHawthorne: .byte walk_left, walk_left, walk_up, end_m
m_RivalStartsToLeave: .byte run_down, run_down, run_left, run_left, look_right, end_m
m_RivalLeavesToTalkToMom: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
