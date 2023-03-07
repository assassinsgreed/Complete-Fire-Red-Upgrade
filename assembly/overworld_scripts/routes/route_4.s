.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route4_Foreman
EventScript_Route4_Foreman:
    npcchat2 0x1 m_LookUp gText_Route4_ForemanChat
    end

.global EventScript_Route4_Worker
EventScript_Route4_Worker:
    npcchat2 0x2 m_LookUp gText_Route4_WorkerChat
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
    msgbox gText_Route4_TormaCaveSign MSG_NORMAL
    end

.global ItemScript_Route4_FindTM01WorkUp
ItemScript_Route4_FindTM01WorkUp:
    setvar CHOSEN_ITEM ITEM_TM01
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
