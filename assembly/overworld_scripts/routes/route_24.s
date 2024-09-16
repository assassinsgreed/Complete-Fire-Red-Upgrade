.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route24_FindTM85_DreamEater
EventScript_Route24_FindTM85_DreamEater:
    setvar CHOSEN_ITEM ITEM_TM85
    call ItemScript_Common_FindTM
    end

.global EventScript_Route24_FindTM63_DrainPunch
EventScript_Route24_FindTM63_DrainPunch:
    setvar CHOSEN_ITEM ITEM_TM63
    call ItemScript_Common_FindTM
    end

.global EventScript_Route24_PsychicRaya
EventScript_Route24_PsychicRaya:
    trainerbattle0 0x0 486 0x0 gText_Route24_PsychicRaya_Intro gText_Route24_PsychicRaya_Defeat
    msgbox gText_Route24_PsychicRaya_Chat MSG_NORMAL
    end

.global EventScript_Route24_DragonTamerDavid
EventScript_Route24_DragonTamerDavid:
    trainerbattle0 0x0 487 0x0 gText_Route24_DragonTamerDavid_Intro gText_Route24_DragonTamerDavid_Defeat
    msgbox gText_Route24_DragonTamerDavid_Chat MSG_NORMAL
    end

.global EventScript_Route24_PsychicJeff
EventScript_Route24_PsychicJeff:
    trainerbattle0 0x0 488 0x0 gText_Route24_PsychicJeff_Intro gText_Route24_PsychicJeff_Defeat
    msgbox gText_Route24_PsychicJeff_Chat MSG_NORMAL
    end

.global EventScript_Route24_FishermanHumphrey
EventScript_Route24_FishermanHumphrey:
    trainerbattle0 0x0 489 0x0 gText_Route24_FishermanHumphrey_Intro gText_Route24_FishermanHumphrey_Defeat
    msgbox gText_Route24_FishermanHumphrey_Chat MSG_NORMAL
    end

.global EventScript_Route24_TriathleteWillow
EventScript_Route24_TriathleteWillow:
    trainerbattle0 0x0 490 0x0 gText_Route24_TriathleteWillow_Intro gText_Route24_TriathleteWillow_Defeat
    msgbox gText_Route24_TriathleteWillow_Chat MSG_NORMAL
    end

.global EventScript_Route24_BlackbeltIrvine
EventScript_Route24_BlackbeltIrvine:
    trainerbattle0 0x0 491 0x0 gText_Route24_BlackbeltIrvine_Intro gText_Route24_BlackbeltIrvine_Defeat
    msgbox gText_Route24_BlackbeltIrvine_Chat MSG_NORMAL
    end

.global SignScript_Route24_UteyanRuinsSign
SignScript_Route24_UteyanRuinsSign:
    msgbox gText_Route24_UteyanRuinsSign MSG_SIGN
    end

.global SignScript_Route24_TrainerTips
SignScript_Route24_TrainerTips:
    msgbox gText_Route24_TrainerTipsSign MSG_SIGN
    end
