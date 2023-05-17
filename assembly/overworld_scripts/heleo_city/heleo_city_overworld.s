.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoCity
MapScript_HeleoCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoCity_FlightSpot:
    setworldmapflag 0x894
    setvar PLAYERFACING 0x0 @ Reset facing from the gym
    end
