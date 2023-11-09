.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_LakeLaplaz
MapScript_LakeLaplaz:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LakeLaplaz_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_LakeLaplaz_FlightFlag:
    setworldmapflag 0x8A9
    end

.global EventScript_LakeLaplaz_TM08_BulkUp
EventScript_LakeLaplaz_TM08_BulkUp:
    setvar CHOSEN_ITEM ITEM_TM08
    call ItemScript_Common_FindTM
    end

.global SignScript_LakeLaplaz_CleanlinessReminder
SignScript_LakeLaplaz_CleanlinessReminder:
    msgbox gText_LakeLaplaz_CleanlinessReminderSign MSG_SIGN
    end

.global SignScript_LakeLaplaz_FlowerOffering
SignScript_LakeLaplaz_FlowerOffering:
    msgbox gText_LakeLaplaz_FlowerGiftSign MSG_SIGN
    end
