.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route7_CamperCarlisle
EventScript_Route7_CamperCarlisle:
    trainerbattle0 0x0 0xF 0x0 gText_Route7_CamperCarlisle_Intro gText_Route7_CamperCarlisle_Defeat
    msgbox gText_Route7_CamperCarlisle_Chat MSG_NORMAL
    end

.global EventScript_Route7_RockerJonas
EventScript_Route7_RockerJonas:
    trainerbattle0 0x0 0x4D 0x0 gText_Route7_RockerJonas_Intro gText_Route7_RockerJonas_Defeat
    msgbox gText_Route7_RockerJonas_Chat MSG_NORMAL
    end

.global EventScript_Route7_LassEden
EventScript_Route7_LassEden:
    trainerbattle0 0x0 0x4E 0x0 gText_Route7_LassEden_Intro gText_Route7_LassEden_Defeat
    msgbox gText_Route7_LassEden_Chat MSG_NORMAL
    end

.global EventScript_Route7_HikerDanny
EventScript_Route7_HikerDanny:
    trainerbattle0 0x0 0x4F 0x0 gText_Route7_HikerDanny_Intro gText_Route7_HikerDanny_Defeat
    msgbox gText_Route7_HikerDanny_Chat MSG_NORMAL
    end

.global EventScript_Route7_CrushGirlErin
EventScript_Route7_CrushGirlErin:
    trainerbattle0 0x0 0x50 0x0 gText_Route7_CrushGirlErin_Intro gText_Route7_CrushGirlErin_Defeat
    msgbox gText_Route7_CrushGirlErin_Chat MSG_NORMAL
    end

.global EventScript_Route7_PsychicIshaan
EventScript_Route7_PsychicIshaan:
    trainerbattle0 0x0 0x51 0x0 gText_Route7_PsychicIshaan_Intro gText_Route7_PsychicIshaan_Defeat
    msgbox gText_Route7_PsychicIshaan_Chat MSG_NORMAL
    end

.global EventScript_Route7_FindTM09Venoshock
EventScript_Route7_FindTM09Venoshock:
    setvar CHOSEN_ITEM ITEM_TM09
    call ItemScript_Common_FindTM
    end

.global SignScript_Route7_TrainerTips
SignScript_Route7_TrainerTips:
    msgbox gText_Route7_TrainerTips MSG_SIGN
    end
