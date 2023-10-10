.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_LaplazFacilities_PokemonCenter
MapScript_LaplazFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_LaplazFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_LaplazFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x07 @ Originally Fucshia City
    end

.global EventScript_LaplazFacilities_GalarBirdsGirl
EventScript_LaplazFacilities_GalarBirdsGirl:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGirl m_LookDown
    end

.global EventScript_LaplazFacilities_GalarBirdsGirlsSister
EventScript_LaplazFacilities_GalarBirdsGirlsSister:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGirlsSister m_LookLeft
    end

.global EventScript_LaplazFacilities_Gentleman
EventScript_LaplazFacilities_Gentleman:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGentleman m_LookDown
    end

.global EventScript_LaplazFacilities_XItemsShop
EventScript_LaplazFacilities_XItemsShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart LaplazPokemart_XItemStock
    goto EventScript_EndMart

LaplazPokemart_XItemStock:
    .hword ITEM_X_ATTACK
    .hword ITEM_X_DEFEND
    .hword ITEM_X_SP_ATK
    .hword ITEM_X_SP_DEF
    .hword ITEM_X_SPEED
    .hword ITEM_X_ACCURACY
    .hword ITEM_DIRE_HIT
    .hword ITEM_GUARD_SPEC
    .hword ITEM_NONE

.global EventScript_LaplazFacilities_XItemsTip
EventScript_LaplazFacilities_XItemsTip:
    npcchatwithmovement gText_LaplazFacilities_XItemsTip m_LookUp
    end
