.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_TormaCave
MapScript_TormaCave:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_TormaCave_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_TormaCave_FlightFlag:
    setworldmapflag 0x8A6
    end