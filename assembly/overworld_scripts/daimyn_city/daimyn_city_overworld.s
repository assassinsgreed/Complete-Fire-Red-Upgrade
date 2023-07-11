.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_DaimynCity
MapScript_DaimynCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_DaimynCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_DaimynCity_FlightSpot:
    setworldmapflag 0x895
    end
