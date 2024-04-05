.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ PlutoGruntYolena, 0xA
.equ PlutoGruntClancy, 0xB
.equ PlutoGruntEna, 0xC

.global EventScript_CalicinBay_SkierRita
EventScript_CalicinBay_SkierRita:
    trainerbattle0 0x0 280 0x0 gText_CalicinBay_SkierRita_Intro gText_CalicinBay_SkierRita_Defeat
    msgbox gText_CalicinBay_SkierRita_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerFFran
EventScript_CalicinBay_SwimmerFFran:
    trainerbattle0 0x0 281 0x0 gText_CalicinBay_SwimmerFran_Intro gText_CalicinBay_SwimmerFran_Defeat
    msgbox gText_CalicinBay_SwimmerFran_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerMAngelo
EventScript_CalicinBay_SwimmerMAngelo:
    trainerbattle0 0x0 282 0x0 gText_CalicinBay_SwimmerAngelo_Intro gText_CalicinBay_SwimmerAngelo_Defeat
    msgbox gText_CalicinBay_SwimmerAngelo_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerMSebastian
EventScript_CalicinBay_SwimmerMSebastian:
    trainerbattle0 0x0 283 0x0 gText_CalicinBay_SwimmerSebastian_Intro gText_CalicinBay_SwimmerSebastian_Defeat
    msgbox gText_CalicinBay_SwimmerSebastian_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerFCorrine
EventScript_CalicinBay_SwimmerFCorrine:
    trainerbattle0 0x0 284 0x0 gText_CalicinBay_SwimmerCorrine_Intro gText_CalicinBay_SwimmerCorrine_Defeat
    msgbox gText_CalicinBay_SwimmerCorrine_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_FishermanOliver
EventScript_CalicinBay_FishermanOliver:
    trainerbattle0 0x0 285 0x0 gText_CalicinBay_FishermanOliver_Intro gText_CalicinBay_FishermanOliver_Defeat
    msgbox gText_CalicinBay_FishermanOliver_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_TM14Blizzard
EventScript_CalicinBay_TM14Blizzard:
    setvar CHOSEN_ITEM ITEM_TM14
    call ItemScript_Common_FindTM
    end

.global EventScript_CalicinBay_TeamPlutoHugo
EventScript_CalicinBay_TeamPlutoHugo:
    trainerbattle0 0x0 286 0x0 gText_CalicinBay_TeamPlutoHugo_Intro gText_CalicinBay_TeamPlutoHugo_Defeat
    msgbox gText_CalicinBay_TeamPlutoHugo_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_TeamPlutoAnise
EventScript_CalicinBay_TeamPlutoAnise:
    trainerbattle0 0x0 287 0x0 gText_CalicinBay_TeamPlutoAnise_Intro gText_CalicinBay_TeamPlutoAnise_Defeat
    checktrainerflag 288 @ Beat Yolena
    if SET _goto Anise_YolenaBeat
    msgbox gText_CalicinBay_TeamPlutoAnise_Chat MSG_NORMAL
    end

Anise_YolenaBeat:
    msgbox gText_CalicinBay_TeamPlutoAnise_YolenaBeatChat MSG_NORMAL
    end

.global EventScript_CalicinBay_TeamPlutoYolena
EventScript_CalicinBay_TeamPlutoYolena:
    trainerbattle2 0x0 288 0x0 gText_CalicinBay_TeamPlutoYolena_Intro gText_CalicinBay_TeamPlutoYolena_Defeat PostYolenaBattle
    end

PostYolenaBattle:
    msgbox gText_CalicinBay_TeamPlutoYolena_Leaves MSG_NORMAL
    compareplayerfacing INTERNAL_UP
    if equal _call YolenaMovesRight
    applymovement LASTTALKED m_PlutoGruntsLeave
    pause DELAY_1SECOND
    applymovement PLAYER m_LookDown
    waitmovement PlutoGruntYolena
    hidesprite LASTTALKED
    setflag 0x49 @ Yolena no longer at Calicin Bay
    applymovement PLAYER m_LookUp
    end

YolenaMovesRight:
    applymovement LASTTALKED m_WalkRight
    waitmovement PlutoGruntYolena
    return

.global EventScript_CalicinBay_StoryEvents
EventScript_CalicinBay_StoryEvents:
    playbgm 0x19A @ Team Pluto Theme
    special 0xAF @ Dismount bike if on it
    compare LASTTALKED PlutoGruntClancy
    if equal _call ClancyComment
    compare LASTTALKED PlutoGruntEna
    if equal _call EnaComment
    call PositionPlayerForCalicinStoryEventsMain
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    waitmovement PlutoGruntEna
    sound 0x15 @ Exclaim
    applymovement PlutoGruntClancy m_Surprise
    applymovement PlutoGruntEna m_Surprise
    msgbox gText_CalicinBay_TeamPlutoClancy_RecognizesPlayer MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoEna_AcknowledgesPlayer MSG_NORMAL
    applymovement PlutoGruntClancy m_ClancyFrustratedJumps
    waitmovement PlutoGruntClancy
    msgbox gText_CalicinBay_TeamPlutoClancy_PreparesForBattle MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoEna_PreparesForBattle MSG_NORMAL
    setflag 0x909 @ Two opponents
    setvar 0x5010 290 @ Ena
    loadpointer 0x0 gText_CalicinBay_TeamPlutoEna_LosesBattle @ Ena's loss text
    special 0xAC @ Load second opponent's text into buffer
    trainerbattle3 0x3 289 0x0 gText_CalicinBay_TeamPlutoClancy_LosesBattle
    msgbox gText_CalicinBay_TeamPlutoClancy_PostBattleCommentary MSG_NORMAL
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_CalicinBay_TeamPlutoEna_PostBattleCommentary MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    waitmovement PlutoGruntClancy
    sound 0x15 @ Exclaim
    applymovement PlutoGruntClancy m_Surprise
    msgbox gText_CalicinBay_TeamPlutoClancy_RemembersMission MSG_NORMAL
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    waitmovement PlutoGruntClancy
    pause DELAY_HALFSECOND
    applymovement PlutoGruntClancy m_Joy
    msgbox gText_CalicinBay_TeamPlutoClancy_ScoldsPlayer MSG_NORMAL
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_CalicinBay_TeamPlutoEna_Panics MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    msgbox gText_CalicinBay_TeamPlutoClancy_AsksEnaAboutPanic MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoEna_CommentsOnHQ MSG_NORMAL
    applymovement PlutoGruntClancy m_Question
    msgbox gText_CalicinBay_TeamPlutoClancy_Recollecting MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement PlutoGruntClancy m_Surprise
    msgbox gText_CalicinBay_TeamPlutoClancy_ComesToRealization MSG_NORMAL
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    msgbox gText_CalicinBay_TeamPlutoClancy_PleadsWithThePlayer MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerPromisedNotToGoToHQ
    if notequal _call PlayerDidNotPromiseNotToGoToHQ
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_CalicinBay_TeamPlutoEna_GettingClancysAttention MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    msgbox gText_CalicinBay_TeamPlutoClancy_RespondsToEna MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoEna_SetsClancyUpForProposal MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoClancy_CommentsOnNoPaperworkPlans MSG_NORMAL
    playbgm 0x159 @ N's Farewell
    msgbox gText_CalicinBay_TeamPlutoEna_ProposesGoingClean MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoClancy_CommentsOnEnasGenius MSG_NORMAL
    applymovement PlutoGruntEna m_Joy
    msgbox gText_CalicinBay_TeamPlutoEna_EnaKnows MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoClancy_TalksAboutPlutoOrigins MSG_NORMAL
    applymovement PlutoGruntClancy m_LookDown
    waitmovement PlutoGruntClancy
    applymovement PlutoGruntClancy m_ClancyFrustratedJumps
    waitmovement PlutoGruntClancy
    msgbox gText_CalicinBay_TeamPlutoClancy_HatesPlayer MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    msgbox gText_CalicinBay_TeamPlutoClancy_ResolvesToQuitPluto MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoEna_HappyClancySaidYes MSG_NORMAL
    msgbox gText_CalicinBay_TeamPlutoClancy_FiredUp MSG_NORMAL
    applymovement PlutoGruntClancy m_LookDown
    msgbox gText_CalicinBay_TeamPlutoClancy_Leaves MSG_NORMAL
    applymovement PlutoGruntClancy m_WalkLeft
    waitmovement PlutoGruntClancy
    applymovement PlutoGruntClancy m_PlutoGruntsLeave
    waitmovement PlutoGruntClancy
    applymovement PlutoGruntEna m_WalkLeft
    waitmovement PlutoGruntEna
    applymovement PlutoGruntEna m_LookDown
    msgbox gText_CalicinBay_TeamPlutoEna_Leaves MSG_NORMAL
    applymovement PlutoGruntEna m_WalkLeft
    waitmovement PlutoGruntEna
    applymovement PlutoGruntEna m_PlutoGruntsLeave
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement PLAYER m_LookDown
    waitmovement PlutoGruntEna
    fadedefaultbgm
    hidesprite 0x8 @ Grunt 1
    hidesprite 0x9 @ Grunt 2
    hidesprite PlutoGruntClancy
    hidesprite PlutoGruntEna
    setflag 0x48 @ Hide all grunts in Calicin Bay
    setvar 0x405D 0x1 @ Allow story events at Pluto Hideout building to initiate
    end

ClancyComment:
    msgbox gText_CalicinBay_TeamPlutoClancy_Comment MSG_NORMAL
    return

EnaComment:
    msgbox gText_CalicinBay_TeamPlutoEna_Comment MSG_NORMAL
    return

PositionPlayerForCalicinStoryEventsMain:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x17
    if lessorequal _call PositionPlayerForRubarrStoryEventsCheckAboveGrunts
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x3A
    if equal _call PlayerWalkLeft_Return
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    return

PositionPlayerForRubarrStoryEventsCheckAboveGrunts:
    compare 0x4000 0x3A
    if equal _call PlayerWalkRight_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x39
    if equal _call PlayerWalkLeft_Return
    call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x17
    if equal _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x3B
    if equal _call PlayerAlignsWithClancy
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x38
    if equal _call PlayerWalkRight_Return
    return

PlayerAlignsWithClancy:
    call PlayerWalkLeft_Return
    call PlayerWalkLeft_Return
    return

PlayerPromisedNotToGoToHQ:
    msgbox gText_CalicinBay_TeamPlutoClancy_PlayerSaidNotGoingToHQ MSG_NORMAL
    return

PlayerDidNotPromiseNotToGoToHQ:
    msgbox gText_CalicinBay_TeamPlutoClancy_PlayerSaidGoingToHQ MSG_NORMAL
    return

.global EventScript_CalicinBay_CalicinBaySign
EventScript_CalicinBay_CalicinBaySign:
    msgbox gText_CalicinBay_CalicinBaySign MSG_SIGN
    end

m_PlutoGruntsLeave: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_ClancyFrustratedJumps: .byte jump_onspot_down, jump_onspot_down, end_m
