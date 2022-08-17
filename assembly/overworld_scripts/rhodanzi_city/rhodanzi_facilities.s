.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_RhodanziFacilities_PokemonCenter
MapScript_RhodanziFacilities_PokemonCenter:
	mapscript MAP_SCRIPT_ON_TRANSITION MapScript_RhodanziFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_RhodanziFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x03 @ Originally Pewter City
    end

.global EventScript_RhodanziFacilities_Mart_BadgeStock
EventScript_RhodanziFacilities_Mart_BadgeStock:
    npcchat gText_RhodanziFacilities_Mart_BadgeStock
    end

.global EventScript_RhodanziFacilities_Mart_EscapeRope
EventScript_RhodanziFacilities_Mart_EscapeRope:
    npcchat gText_RhodanziFacilities_Mart_EscapeRope
    end

.global EventScript_RhodanziFacilities_Center_UsingFacility
EventScript_RhodanziFacilities_Center_UsingFacility:
    npcchat gText_RhodanziFacilities_Center_UsingFacility
    end

.global EventScript_RhodanziFacilities_Center_Trade
EventScript_RhodanziFacilities_Center_Trade:
    npcchat gText_RhodanziFacilities_Center_Trade
    end

.global EventScript_RhodanziFacilities_Center_PokemonTreatment
EventScript_RhodanziFacilities_Center_PokemonTreatment:
    npcchat gText_RhodanziFacilities_Center_PokemonTreatment
    end
