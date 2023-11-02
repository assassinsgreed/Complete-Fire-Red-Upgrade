.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_PerdaonForest
MapScript_PerdaonForest:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_PeradonForest_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_PeradonForest_FlightFlag:
    setworldmapflag 0x8AA
    end