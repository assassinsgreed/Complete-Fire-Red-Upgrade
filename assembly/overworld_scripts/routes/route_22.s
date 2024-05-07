.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route22_TM74GyroBall
EventScript_Route22_TM74GyroBall:
    setvar CHOSEN_ITEM ITEM_TM74
    call ItemScript_Common_FindTM
    end

.global EventScript_Route22_TM90Substitute
EventScript_Route22_TM90Substitute:
    setvar CHOSEN_ITEM ITEM_TM90
    call ItemScript_Common_FindTM
    end

.global EventScript_Route22_CoolTrainerGail
EventScript_Route22_CoolTrainerGail:
    trainerbattle0 0x0 385 0x0 gText_Route22_CoolTrainerGail_Intro gText_Route22_CoolTrainerGail_Defeat
    msgbox gText_Route22_CoolTrainerGail_Chat MSG_NORMAL
    end

.global EventScript_Route22_ScientistLarry
EventScript_Route22_ScientistLarry:
    trainerbattle0 0x0 386 0x0 gText_Route22_ScientistLarry_Intro gText_Route22_ScientistLarry_Defeat
    msgbox gText_Route22_ScientistLarry_Chat MSG_NORMAL
    end

.global EventScript_Route22_SrAndJr_Alma
EventScript_Route22_SrAndJr_Alma:
    checktrainerflag 387
    if SET _goto AlmaDefeated
    trainerbattle0 0x0 387 0x0 gText_Route22_SrAndJr_Alma_Intro gText_Route22_SrAndJr_Alma_Defeat
    goto AlmaDefeated
    end

AlmaDefeated:
    npcchatwithmovement gText_Route22_SrAndJr_Alma_Chat m_LookDown
    end

.global EventScript_Route22_SrAndJr_Mai
EventScript_Route22_SrAndJr_Mai:
    checktrainerflag 387
    if SET _goto MaiDefeated
    trainerbattle0 0x0 387 0x0 gText_Route22_SrAndJr_Mai_Intro gText_Route22_SrAndJr_Mai_Defeat
    goto MaiDefeated
    end

MaiDefeated:
    npcchatwithmovement gText_Route22_SrAndJr_Mai_Chat m_LookDown
    end

.global EventScript_Route22_JugglerChauncy
EventScript_Route22_JugglerChauncy:
    trainerbattle0 0x0 388 0x0 gText_Route22_JugglerChauncy_Intro gText_Route22_JugglerChauncy_Defeat
    msgbox gText_Route22_JugglerChauncy_Chat MSG_NORMAL
    end

.global EventScript_Route22_BurglarMose
EventScript_Route22_BurglarMose:
    trainerbattle0 0x0 389 0x0 gText_Route22_BurglarMose_Intro gText_Route22_BurglarMose_Defeat
    msgbox gText_Route22_BurglarMose_Chat MSG_NORMAL
    end

.global SignScript_Route22_MimmettJungle
SignScript_Route22_MimmettJungle:
    msgbox gText_Route22_MimmettJungleSign MSG_SIGN
    end
