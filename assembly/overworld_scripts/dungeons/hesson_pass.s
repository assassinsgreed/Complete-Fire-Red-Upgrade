.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HessonPass
MapScript_HessonPass:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HessonPass_FlightFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_HessonPass_FlightFlag:
    setworldmapflag 0x8B0 @ Been to Hesson Pass
    end

.global SignScript_HessonPass_HolesInGround
SignScript_HessonPass_HolesInGround:
    msgbox gText_HessonPass_HolesInGroundSign MSG_SIGN
    end

.global EventScript_HessonPass_TM67SmartStrike
EventScript_HessonPass_TM67SmartStrike:
    setvar CHOSEN_ITEM ITEM_TM67
    call ItemScript_Common_FindTM
    end

.global EventScript_HessonPass_CharizarditeX
EventScript_HessonPass_CharizarditeX:
    finditem ITEM_CHARIZARDITE_X 0x1
    end

.global EventScript_HessonPass_HikerLuke
EventScript_HessonPass_HikerLuke:
    trainerbattle0 0x0 0xD1 0x0 gText_HessonPass_HikerLuke_Intro gText_HessonPass_HikerLuke_Defeat
    msgbox gText_HessonPass_HikerLuke_Chat MSG_NORMAL
    end

.global EventScript_HessonPass_ScientistHarvey
EventScript_HessonPass_ScientistHarvey:
    trainerbattle0 0x0 0xD2 0x0 gText_HessonPass_ScientistHarvey_Intro gText_HessonPass_ScientistHarvey_Defeat
    msgbox gText_HessonPass_ScientistHarvey_Chat MSG_NORMAL
    end

.global EventSCript_HessonPass_PsychicKimiko
EventSCript_HessonPass_PsychicKimiko:
    trainerbattle0 0x0 0xD3 0x0 gText_HessonPass_PsychicKimiko_Intro gText_HessonPass_PsychicKimiko_Defeat
    msgbox gText_HessonPass_PsychicKimiko_Chat MSG_NORMAL
    end

.global EventSCript_HessonPass_CoolTrainerColt
EventSCript_HessonPass_CoolTrainerColt:
    trainerbattle0 0x0 0xD4 0x0 gText_HessonPass_CoolTrainerColt_Intro gText_HessonPass_CoolTrainerColt_Defeat
    msgbox gText_HessonPass_CoolTrainerColt_Chat MSG_NORMAL
    end

.global EventScript_HessonPass_NurseMina
EventScript_HessonPass_NurseMina:
    faceplayer
    checktrainerflag 0x5D7
    if SET _goto NurseMinaHeal
    trainerbattle2 0x0 0xD7 0x0 gText_HessonPass_NurseMina_Intro gText_HessonPass_NurseMina_Defeat NurseMinaHeal
    call NurseMinaHeal
    end

NurseMinaHeal:
    msgbox gText_HessonPass_NurseMina_Chat MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_HessonPass_NurseMina_HealComplete MSG_NORMAL
    end

.global EventScript_HessonPass_GentlemanGordy
EventScript_HessonPass_GentlemanGordy:
    trainerbattle0 0x0 0xD8 0x0 gText_HessonPass_GentlemanGordy_Intro gText_HessonPass_GentlemanGordy_Defeat
    msgbox gText_HessonPass_GentlemanGordy_Chat MSG_NORMAL
    end

.global EventScript_HessonPass_BlackbeltHaytham
EventScript_HessonPass_BlackbeltHaytham:
    trainerbattle0 0x0 0xD5 0x0 gText_HessonPass_BlackbeltHaytham_Intro gText_HessonPass_BlackbeltHaytham_Defeat
    msgbox gText_HessonPass_BlackbeltHaytham_Chat MSG_NORMAL
    end

.global EventScript_HessonPass_Collector_Zeus
EventScript_HessonPass_Collector_Zeus:
    trainerbattle0 0x0 0xD6 0x0 gText_HessonPass_CollectorZeus_Intro gText_HessonPass_CollectorZeus_Defeat
    msgbox gText_HessonPass_CollectorZeus_Chat MSG_NORMAL
    end
