.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Foreman, 0x1
.equ FormanEventVar, 0x4051

.global MapScript_Route4
MapScript_Route4:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Route4
	.byte MAP_SCRIPT_TERMIN

LevelScripts_Route4:
	levelscript FormanEventVar 0x0 LevelScript_Rotue4_ForemanEvent
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_Rotue4_ForemanEvent:
    checkflag 0x35 @ Boulders are cleared
    if NOT_SET _goto ClearForemanEvent
    checkflag 0x36 @ Foreman has left
    if SET _goto ClearForemanEvent
    lock
    sound 0x15 @ Exclaim
    applymovement Foreman m_Surprise
    waitmovement ALLEVENTS
    applymovement Foreman m_MeetPlayer
    waitmovement ALLEVENTS
    msgbox gText_Route4_ForemanConfrontsPlayer MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerHonest
    compare LASTRESULT NO
    if equal _call PlayerDishonest
    msgbox gText_Route4_ForemanBeratesPlayer MSG_NORMAL
    applymovement Foreman m_LookDown
    msgbox gText_Route4_ForemanConcedes MSG_NORMAL
    applymovement Foreman m_LookUp
    msgbox gText_Route4_ForemanLeaves MSG_NORMAL
    applymovement Foreman m_ForemanLeaves
    waitmovement ALLEVENTS
    hidesprite Foreman
    setvar FormanEventVar 0x1
    setflag 0x36 @ Foreman has left
    release
    end

PlayerHonest:
    msgbox gText_Route4_PlayerHonest MSG_NORMAL
    return

PlayerDishonest:
    msgbox gText_Route4_PlayerDishonest MSG_NORMAL
    return

ClearForemanEvent:
    setvar FormanEventVar 0x1
    end

.global EventScript_Route4_Foreman
EventScript_Route4_Foreman:
    npcchatwithmovement gText_Route4_ForemanChat m_LookUp
    end

.global EventScript_Route4_Worker
EventScript_Route4_Worker:
    npcchatwithmovement gText_Route4_WorkerChat m_LookUp
    end

.global EventScript_Route4_LargeMan
EventScript_Route4_LargeMan:
    npcchat gText_Route4_LargeManChat
    end

.global EventScript_Route4_Lass
EventScript_Route4_Lass:
    npcchat gText_Route4_LassChat
    end

.global SignScript_Route4_TormaCaveSign
SignScript_Route4_TormaCaveSign:
    msgbox gText_Route4_TormaCaveSign MSG_NORMAL
    end

.global SignScript_Route4_TrainerTips
SignScript_Route4_TrainerTips:
    msgbox gText_Route4_TrainerTipsSign MSG_NORMAL
    end

.global EventScript_Route4_FindTM01WorkUp
EventScript_Route4_FindTM01WorkUp:
    setvar CHOSEN_ITEM ITEM_TM01
    call ItemScript_Common_FindTM
    end

.global EventScript_Route4_FindTM71StoneEdge
EventScript_Route4_FindTM71StoneEdge:
    setvar CHOSEN_ITEM ITEM_TM71
    call ItemScript_Common_FindTM
    end

.global EventScript_Route4_CamperPietro
EventScript_Route4_CamperPietro:
    trainerbattle0 0x0 0x24 0x0 gText_Route4_CamperPietro_Intro gText_Route4_CamperPietro_Defeat
    msgbox gText_Route4_CamperPietro_Chat MSG_NORMAL
    end

.global EventScript_Route4_PsychicAdriano
EventScript_Route4_PsychicAdriano:
    trainerbattle0 0x0 0x25 0x0 gText_Route4_PsychicAdriano_Intro gText_Route4_PsychicAdriano_Defeat
    msgbox gText_Route4_PsychicAdriano_Chat MSG_NORMAL
    end

.global EventScript_Route4_BeautyBeatrice
EventScript_Route4_BeautyBeatrice:
    trainerbattle0 0x0 0x26 0x0 gText_Route4_BeautyBeatrice_Intro gText_Route4_BeautyBeatrice_Defeat
    msgbox gText_Route4_BeautyBeatrice_Chat MSG_NORMAL
    end

.global EventScript_Route4_LadyAlda
EventScript_Route4_LadyAlda:
    trainerbattle0 0x0 0x27 0x0 gText_Route4_LadyAlda_Intro gText_Route4_LadyAlda_Defeat
    msgbox gText_Route4_LadyAlda_Chat MSG_NORMAL
    end

.global EventScript_Route4_LassIsabela
EventScript_Route4_LassIsabela:
    trainerbattle0 0x0 0x28 0x0 gText_Route4_LassIsabela_Intro gText_Route4_LassIsabela_Defeat
    msgbox gText_Route4_LassIsabela_Chat MSG_NORMAL
    end

.global EventScript_Route4_BirdKeeperRowley
EventScript_Route4_BirdKeeperRowley:
    trainerbattle0 0x0 0x29 0x0 gText_Route4_BirdKeeperRowley_Intro gText_Route4_BirdKeeperRowley_Defeat
    msgbox gText_Route4_BirdKeeperRowley_Chat MSG_NORMAL
    end

.global EventScript_Route4_CrushGirlElise
EventScript_Route4_CrushGirlElise:
    trainerbattle0 0x0 0x2A 0x0 gText_Route4_CrushGirlElise_Intro gText_Route4_CrushGirlElise_Defeat
    msgbox gText_Route4_CrushGirlElise_Chat MSG_NORMAL
    end

.global EventScript_Route4_GentlemanPorter
EventScript_Route4_GentlemanPorter:
    trainerbattle0 0x0 0x2B 0x0 gText_Route4_GentlemanPorter_Intro gText_Route4_GentlemanPorter_Defeat
    msgbox gText_Route4_GentlemanPorter_Chat MSG_NORMAL
    end

.global EventScript_Route4_BirdKeeperLuca
EventScript_Route4_BirdKeeperLuca:
    trainerbattle0 0x0 0x2C 0x0 gText_Route4_BirdKeeperLuca_Intro gText_Route4_BirdKeeperLuca_Defeat
    msgbox gText_Route4_BirdKeeperLuca_Chat MSG_NORMAL
    end

m_MeetPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_ForemanLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
