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

.global SignScript_DaimynCityOverworld_Restaurant
SignScript_DaimynCityOverworld_Restaurant:
    msgbox gText_DaimynCityOverworld_RestaurantSign MSG_SIGN
    end
