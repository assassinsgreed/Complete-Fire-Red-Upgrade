.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Casey, 0x11

.global EventScript_Route10_TM64_Explosion
EventScript_Route10_TM64_Explosion:
    setvar CHOSEN_ITEM ITEM_TM64
    call ItemScript_Common_FindTM
    end

.global EventScript_Route10_TM41_Torment
EventScript_Route10_TM41_Torment:
    setvar CHOSEN_ITEM ITEM_TM41
    call ItemScript_Common_FindTM
    end

.global EventScript_Route10_Lopunnite
EventScript_Route10_Lopunnite:
    finditem ITEM_LOPUNNITE 0x1
    end

.global EventScript_Route10_PsychicDarius
EventScript_Route10_PsychicDarius:
    trainerbattle0 0x0 0xA5 0x0 gText_Route10_PsychicDarius_Intro gText_Route10_PsychicDarius_Defeat
    msgbox gText_Route10_PsychicDarius_Chat MSG_NORMAL
    end

.global EventScript_Route10_BirdKeeperMario
EventScript_Route10_BirdKeeperMario:
    trainerbattle0 0x0 0xA6 0x0 gText_Route10_BirdKeeperMario_Intro gText_Route10_BirdKeeperMario_Defeat
    msgbox gText_Route10_BirdKeeperMario_Chat MSG_NORMAL
    end

.global EventScript_Route10_GamblerDarren
EventScript_Route10_GamblerDarren:
    trainerbattle0 0x0 0xA7 0x0 gText_Route10_GamblerDarren_Intro gText_Route10_GamblerDarren_Defeat
    msgbox gText_Route10_GamblerDarren_Chat MSG_NORMAL
    end

.global EventScript_Route10_ParasolLadyGwen
EventScript_Route10_ParasolLadyGwen:
    trainerbattle0 0x0 0xA8 0x0 gText_Route10_ParasolLady_Intro gText_Route10_ParasolLady_Defeat
    msgbox gText_Route10_ParasolLady_Chat MSG_NORMAL
    end

.global EventScript_Route10_CamperJackson
EventScript_Route10_CamperJackson:
    trainerbattle0 0x0 0xA9 0x0 gText_Route10_CamperJackson_Intro gText_Route10_CamperJackson_Defeat
    msgbox gText_Route10_CamperJackson_Chat MSG_NORMAL
    end

.global EventScript_Route10_RockerBert
EventScript_Route10_RockerBert:
    trainerbattle0 0x0 0xAA 0x0 gText_Route10_RockerBert_Intro gText_Route10_RockerBert_Defeat
    msgbox gText_Route10_RockerBert_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerAlberto
EventScript_Route10_SwimmerAlberto:
    trainerbattle0 0x0 0xAB 0x0 gText_Route10_SwimmerAlberto_Intro gText_Route10_SwimmerAlberto_Defeat
    msgbox gText_Route10_SwimmerAlberto_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerRosie
EventScript_Route10_SwimmerRosie:
    trainerbattle0 0x0 0xAC 0x0 gText_Route10_SwimmerRosie_Intro gText_Route10_SwimmerRosie_Defeat
    msgbox gText_Route10_SwimmerRosie_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerDoug
EventScript_Route10_SwimmerDoug:
    trainerbattle0 0x0 0xAD 0x0 gText_Route10_SwimmerDoug_Intro gText_Route10_SwimmerDoug_Defeat
    msgbox gText_Route10_SwimmerDoug_Chat MSG_NORMAL
    end

.global SignScript_Route10_TrainerTips_EvolutionTypes
SignScript_Route10_TrainerTips_EvolutionTypes:
    msgbox gText_Route10_TrainerTipsSign_Evolution MSG_SIGN
    end

.global SignScript_Route10_TrainerTips_TimeOfDay
SignScript_Route10_TrainerTips_TimeOfDay:
    msgbox gText_Route10_TrainerTipsSign_TimeOfDay MSG_SIGN
    end

.global SignScript_Route10_Route11Path
SignScript_Route10_Route11Path:
    msgbox gText_Route10_Route11Sign MSG_SIGN
    end

.global EventScript_Route10Cave_HikerHarley
EventScript_Route10Cave_HikerHarley:
    trainerbattle0 0x0 0xB0 0x0 gText_Route10Cave_HikerHarley_Intro gText_Route10Cave_HikerHarley_Defeat
    msgbox gText_Route10Cave_HikerHarley_Chat MSG_NORMAL
    end

.global EventScript_Route10Cave_BlackbeltXavier
EventScript_Route10Cave_BlackbeltXavier:
    trainerbattle0 0x0 0xB1 0x0 gText_Route10Cave_BlackbeltXavier_Intro gText_Route10Cave_BlackbeltXavier_Defeat
    msgbox gText_Route10Cave_BlackbeltXavier_Chat MSG_NORMAL
    end

.global EventScript_Route10Cave_TM23_SmackDown
EventScript_Route10Cave_TM23_SmackDown:
    setvar CHOSEN_ITEM ITEM_TM23
    call ItemScript_Common_FindTM
    end

.global TileScript_Route10_TriggerCaseyBattle_Above
TileScript_Route10_TriggerCaseyBattle_Above:
    checkflag 0x256 @ Battled Casey on Route 10
    if SET _goto End
    special 0xAF @ Dismount bike if on it
    lock
    call SetCaseyGender
    clearflag 0x03D @ Show Casey
    showsprite Casey
    playbgm 0x169 0x1 @ Alder encounter (Permanently replaces map music for cutscene)
    applymovement Casey m_WalkToPlayer
    waitmovement Casey
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    checkgender
    compare LASTRESULT 0x0
    if equal _goto FCaseyEvent
    if notequal _goto MCaseyEvent

.global TileScript_Route10_TriggerCaseyBattle_Below
TileScript_Route10_TriggerCaseyBattle_Below:
    checkflag 0x256 @ Battled Casey on Route 10
    if SET _goto End
    special 0xAF @ Dismount bike if on it
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    applymovement PLAYER m_LookRight
    waitmovement PLAYER
    goto TileScript_Route10_TriggerCaseyBattle_Above

FCaseyEvent:
    msgbox gText_Route10_CaseyFIntroduction MSG_NORMAL
    trainerbattle2 0x0 0xAE 0x100 gText_Route10_CaseyFBattleIntro gText_Route10_CaseyFBattleDefeat FCaseyEventPostBattle

FCaseyEventPostBattle:
    msgbox gText_Route10_CaseyFExpShareGift MSG_NORMAL
    obtainitem ITEM_EXP_SHARE 0x1
    msgbox gText_Route10_CaseyFExpShareExplained MSG_NORMAL
    msgbox gText_Route10_CaseyFPostBattle MSG_NORMAL
    applymovement Casey m_LookRight
    msgbox gText_Route10_CaseyFReflection MSG_NORMAL
    applymovement Casey m_LookLeft
    msgbox gText_Route10_CaseyFLeaves MSG_NORMAL
    goto CaseyLeavesCommon

MCaseyEvent:
    msgbox gText_Route10_CaseyMIntroduction MSG_NORMAL
    trainerbattle2 0x0 0xAF 0x100 gText_Route10_CaseyMBattleIntro gText_Route10_CaseyMBattleDefeat MCaseyEventPostBattle

MCaseyEventPostBattle:
    msgbox gText_Route10_CaseyMExpShareGift MSG_NORMAL
    obtainitem ITEM_EXP_SHARE 0x1
    msgbox gText_Route10_CaseyMExpShareExplained MSG_NORMAL
    msgbox gText_Route10_CaseyMPostBattle MSG_NORMAL
    applymovement Casey m_LookRight
    msgbox gText_Route10_CaseyMReflection MSG_NORMAL
    applymovement Casey m_LookLeft
    msgbox gText_Route10_CaseyMLeaves MSG_NORMAL
    goto CaseyLeavesCommon

CaseyLeavesCommon:
    applymovement Casey m_WalkAwayFromPlayer
    waitmovement Casey
    hidesprite Casey
    setflag 0x03D @ Hide Casey
    setflag 0x256 @ Battled Casey on route 10
    playbgm 0x15E 0x1 @ Regular route 10 track (Replace override from cutscene)
    signmsg
    msgbox gText_Route10_ExpShareHint MSG_SIGN
    normalmsg
    end

m_WalkToPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_WalkAwayFromPlayer: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
