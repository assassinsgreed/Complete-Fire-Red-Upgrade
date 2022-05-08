.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global MapScript_RhodanziOverworld_FlightSpot
MapScript_RhodanziOverworld_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RhodanziOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RhodanziOverworld_FlightFlag:
    setworldmapflag 0x892
    sethealingplace 0x03 @ Originally Pewter City
    @TODO: Later, add a script for hiding Pluto grunts when player has first badge
    end

.global EventScript_RhodanziOverworld_SunSightMan
EventScript_RhodanziOverworld_SunSightMan:
    npcchat gText_RhodanziOverworld_SunSightMan
    end

.global EventScript_RhodanziOverworld_FirstStop
EventScript_RhodanziOverworld_FirstStop:
    npcchat gText_RhodanziOverworld_FirstStop
    end

.global EventScript_RhodanziOverworld_PokemonVariety
EventScript_RhodanziOverworld_PokemonVariety:
    npcchat gText_RhodanziOverworld_PokemonVariety
    end

.global EventScript_RhodanziOverworld_TreeGuy
EventScript_RhodanziOverworld_TreeGuy:
    npcchat gText_RhodanziOverworld_TreeGuy
    end

@ Todo: Finish this event. Should show talk text when spoken to, then moved. If walk on the tiles in between, move player
.global EventScript_RhodanziOverworld_ThugsCaught
EventScript_RhodanziOverworld_ThugsCaught:

    npcchat gText_RhodanziOverworld_ThugsCaught
    end
