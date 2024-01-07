.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_BruccieVillageFacilities_PokemonCenter
MapScript_BruccieVillageFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_BruccieVillageFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_BruccieVillageFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x08
    end

.global EventScript_BruccieVillageFacilities_PokemonCenter_GameboyKidLeft
EventScript_BruccieVillageFacilities_PokemonCenter_GameboyKidLeft:
    msgbox gText_BruccieVillageFacilities_PokemonCenter_GameboyKidLeft MSG_NORMAL
    call GameboyKidRightLooksLeft
    call GameboyKidLeftLooksRight
    call GameboyKidsLookDown
    end

.global EventScript_BruccieVillageFacilities_PokemonCenter_GameboyKidRight
EventScript_BruccieVillageFacilities_PokemonCenter_GameboyKidRight:
    msgbox gText_BruccieVillageFacilities_PokemonCenter_GameboyKidRight MSG_NORMAL
    call GameboyKidLeftLooksRight
    call GameboyKidRightLooksLeft
    call GameboyKidsLookDown
    end

GameboyKidLeftLooksRight:
    applymovement 0x2 m_LookRight
    msgbox gText_BruccieVillageFacilities_PokemonCenter_GameboyKidCommon MSG_NORMAL
    return

GameboyKidRightLooksLeft:
    applymovement 0x3 m_LookLeft
    msgbox gText_BruccieVillageFacilities_PokemonCenter_GameboyKidCommon MSG_NORMAL
    return

GameboyKidsLookDown:
    applymovement 0x2 m_LookDown
    applymovement 0x3 m_LookDown
    return

.global EventScript_BruccieVillageFacilities_Pokemart_IceHealsGirl
EventScript_BruccieVillageFacilities_Pokemart_IceHealsGirl:
    npcchatwithmovement gText_BruccieVillageFacilities_Pokemart_IceHealGirl m_LookLeft
    end

.global EventScript_BruccieVillageFacilities_Pokemart_StockBoy
EventScript_BruccieVillageFacilities_Pokemart_StockBoy:
    npcchatwithmovement gText_BruccieVillageFacilities_Pokemart_StockBoy m_LookUp
    end
