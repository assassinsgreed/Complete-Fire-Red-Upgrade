.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_BruccieVillage
MapScript_BruccieVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_BruccieVillage_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_BruccieVillage_FlightSpot:
    setworldmapflag 0x897 @ Visited Bruccie Village
    end

.global EventScript_BruccieVillage_Hiker
EventScript_BruccieVillage_Hiker:
    npcchat gText_BruccieVillage_Hiker
    end

.global EventScript_BruccieVillage_Skier
EventScript_BruccieVillage_Skier:
    npcchat gText_BruccieVillage_Skier
    end

.global EventScript_BruccieVillage_Psychic
EventScript_BruccieVillage_Psychic:
    npcchat gText_BruccieVillage_Psychic
    end

.global SignScript_BruccieVillage_TownPlacard
SignScript_BruccieVillage_TownPlacard:
    msgbox gText_BruccieVillage_TownPlacardSign MSG_SIGN
    end

.global SignScript_BruccieVillage_GymSign
SignScript_BruccieVillage_GymSign:
    msgbox gText_BruccieVillage_GymSign MSG_SIGN
    end
