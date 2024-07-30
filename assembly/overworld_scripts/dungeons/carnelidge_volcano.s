.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_CarnelidgeVolcano
MapScript_CarnelidgeVolcano:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_CarnelidgeVolcano_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_CarnelidgeVolcano_FlightFlag:
    setworldmapflag 0x8AB
    end
