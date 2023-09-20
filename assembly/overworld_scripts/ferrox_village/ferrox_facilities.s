.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_FerroxFacilities_PokemonCenter
MapScript_FerroxFacilities_PokemonCenter:
	mapscript MAP_SCRIPT_ON_TRANSITION MapScript_FerroxFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_FerroxFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x04 @ Originally Cerulean City
    call ResetRoute11PlutoEventOnWhiteout
    end

.global EventScript_FerroxFacilities_Mart_BerryShop
EventScript_FerroxFacilities_Mart_BerryShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart FerroxPokemart_BerryStock
    goto EventScript_EndMart

FerroxPokemart_BerryStock:
    .hword ITEM_ORAN_BERRY
    .hword ITEM_SITRUS_BERRY
    .hword ITEM_CHERI_BERRY
    .hword ITEM_CHESTO_BERRY
    .hword ITEM_PECHA_BERRY
    .hword ITEM_RAWST_BERRY
    .hword ITEM_ASPEAR_BERRY
    .hword ITEM_PERSIM_BERRY
    .hword ITEM_LEPPA_BERRY
    .hword ITEM_NONE

.global EventScript_FerroxFacilities_Mart_UniqueShops
EventScript_FerroxFacilities_Mart_UniqueShops:
    npcchat gText_FerroxFacilities_Mart_UniqueShops
    end

.global EventScript_FerroxFacilities_Mart_Berries
EventScript_FerroxFacilities_Mart_Berries:
    npcchat gText_FerroxFacilities_Mart_Berries
    end

.global EventScript_FerroxFacilities_Center_FerroxHikers
EventScript_FerroxFacilities_Center_FerroxHikers:
    npcchat gText_FerroxFacilities_Mart_FerroxHikers
    end

.global EventScript_FerroxFacilities_Center_StellaSibling
EventScript_FerroxFacilities_Center_StellaSibling:
    npcchat gText_FerroxFacilities_Mart_StellaSibling
    end

.global EventScript_FerroxFacilities_Center_FerroxBadge
EventScript_FerroxFacilities_Center_FerroxBadge:
    npcchat gText_FerroxFacilities_Mart_FerroxBadge
    end
