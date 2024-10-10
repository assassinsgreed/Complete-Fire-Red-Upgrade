.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route21
MapScript_Route21:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_Route21_MoveVictoryRoadGuard
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_Route21_MoveVictoryRoadGuard:
    checkflag 0x280 @ Victory Road guard has stepped aside
    if NOT_SET _goto End
    movesprite2 21 0x27 0x6 @ Permanent position
    end

.global EventScript_Route21_TM56_Fling
EventScript_Route21_TM56_Fling:
    setvar CHOSEN_ITEM ITEM_TM56
    call ItemScript_Common_FindTM
    end

.global EventScript_Route21_PokefanWalter
EventScript_Route21_PokefanWalter:
    trainerbattle0 0x0 390 0x0 gText_Route21_PokefanWalter_Intro gText_Route21_PokefanWalter_Defeat
    msgbox gText_Route21_PokefanWalter_Chat MSG_NORMAL
    end

.global EventScript_Route21_CollectorEric
EventScript_Route21_CollectorEric:
    trainerbattle0 0x0 391 0x0 gText_Route21_CollectorEric_Intro gText_Route21_CollectorEric_Defeat
    msgbox gText_Route21_CollectorEric_Chat MSG_NORMAL
    end

.global EventScript_Route21_HikerRicardo
EventScript_Route21_HikerRicardo:
    trainerbattle0 0x0 392 0x0 gText_Route21_HikerRicardo_Intro gText_Route21_HikerRicardo_Defeat
    msgbox gText_Route21_HikerRicardo_Chat MSG_NORMAL
    end

.global EventScript_Route21_DragonTamerTanner
EventScript_Route21_DragonTamerTanner:
    trainerbattle0 0x0 393 0x0 gText_Route21_DragonTamerTanner_Intro gText_Route21_DragonTamerTanner_Defeat
    msgbox gText_Route21_DragonTamerTanner_Chat MSG_NORMAL
    end

.global EventScript_Route21_ParasolLadyKatrina
EventScript_Route21_ParasolLadyKatrina:
    trainerbattle0 0x0 394 0x0 gText_Route21_ParasolLadyKatrina_Intro gText_Route21_ParasolLadyKatrina_Defeat
    msgbox gText_Route21_ParasolLadyKatrina_Chat MSG_NORMAL
    end

.global EventScript_Route21_NinjaBoyIshan
EventScript_Route21_NinjaBoyIshan:
    trainerbattle0 0x0 395 0x0 gText_Route21_NinjaBoyIshan_Intro gText_Route21_NinjaBoyIshan_Defeat
    msgbox gText_Route21_NinjaBoyIshan_Chat MSG_NORMAL
    end

.global EventScript_Route21_RockerAxel
EventScript_Route21_RockerAxel:
    trainerbattle0 0x0 396 0x0 gText_Route21_RockerAxel_Intro gText_Route21_RockerAxel_Defeat
    msgbox gText_Route21_RockerAxel_Chat MSG_NORMAL
    end

.global EventScript_Route21_VictoryRoadGuard
EventScript_Route21_VictoryRoadGuard:
    faceplayer
    msgbox gText_Route21_VictoryRoadGuard MSG_NORMAL
    checkflag 0x27F @ Registered for Victory Road challenge
    if SET _goto CanTakeVictoryRoadChallenge
    playse 0x1A @ Error
    msgbox gText_Route21_VictoryRoadGuard_NotEnoughBadges MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

CanTakeVictoryRoadChallenge:
    fanfare 0x10D @ Celebration
    msgbox gText_Route21_VictoryRoadGuard_HasEnoughBadges MSG_NORMAL
    waitfanfare
    msgbox gText_Route21_VictoryRoadGuard_WishesLuck MSG_NORMAL
    checkflag 0x280 @ Victory Road guard has stepped aside
    if SET _goto End
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x27
    if equal _call PlayerMovesOutOfGuardsWay
    applymovement LASTTALKED m_WalkRight
    waitmovement LASTTALKED
    applymovement LASTTALKED m_LookDown
    movesprite LASTTALKED 0x27 0x6 @ Location while on map
    movesprite2 LASTTALKED 0x27 0x6 @ Permanent position
    setflag 0x280 @ Victory Road guard has stepped aside
    end

PlayerMovesOutOfGuardsWay:
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    return

.global SignScript_Route21_TrainerTips
SignScript_Route21_TrainerTips:
    msgbox gText_Route21_TrainerTips MSG_SIGN
    end

.global SignScript_Route21_VictoryRoad
SignScript_Route21_VictoryRoad:
    msgbox gText_Route21_VictoryRoad MSG_SIGN
    end

// Secret Trail
.global EventScript_SecretTrail_TM77_PsychUp
EventScript_SecretTrail_TM77_PsychUp:
    setvar CHOSEN_ITEM ITEM_TM77
    call ItemScript_Common_FindTM
    end

.global EventScript_SecretTrail_ChannelerHeather
EventScript_SecretTrail_ChannelerHeather:
    trainerbattle0 0x0 397 0x0 gText_SecretTrail_ChannelerHeather_Intro gText_SecretTrail_ChannelerHeather_Defeat
    msgbox gText_SecretTrail_ChannelerHeather_Chat MSG_NORMAL
    end
