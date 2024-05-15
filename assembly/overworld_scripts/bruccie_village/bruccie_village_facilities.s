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

.global EventScript_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl
EventScript_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl:
    faceplayer
    setvar 0x8003 0x0 @ From party
    setvar 0x8004 0x0 @ First slot
    bufferfirstpokemon 0x0 @ Buffer first pokemon's species (not nickname) to the first buffer
    special2 LASTRESULT 0xC @ Store the caught location in LASTRESULT
    callasm BufferMapNameFromLastResult @ Convert it from it's numeric representation to it's name
    msgbox gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl MSG_NORMAL
    @ Display flavour text based on the caught location
    switch LASTRESULT
    @ Urban Places
    case MAPSEC_ANTHRA_TOWN, UrbanDescription
    case MAPSEC_OLENIC_TOWN, UrbanDescription
    case MAPSEC_RHODANZI_CITY, UrbanDescription
    case MAPSEC_FERROX_VILLAGE, UrbanDescription
    case MAPSEC_HELEO_CITY, UrbanDescription
    case MAPSEC_DAIMYN_CITY, UrbanDescription
    case MAPSEC_LAPLAZ_TOWN, UrbanDescription
    case MAPSEC_BRUCCIE_VILLAGE, UrbanDescription
    case MAPSEC_EMRALDIN_QUAY, UrbanDescription
    case MAPSEC_TSARVOSA_CITY, UrbanDescription
    case MAPSEC_UTEYA_VILLAGE, UrbanDescription
    case MAPSEC_ROUTE_12_REST_HOUSE, UrbanDescription
    case MAPSEC_ROUTE_13_REST_HOUSE, UrbanDescription
    case MAPSEC_HELEO_RANCH, UrbanDescription
    case MAPSEC_ASCENSION_TOWER, UrbanDescription
    case MAPSEC_DAIMYN_FACTORY, UrbanDescription
    @ Desert
    case MAPSEC_RUBARR_DESERT, DesertDescription
    @ Hot places
    case MAPSEC_ROUTE_13, HotDescription
    case MAPSEC_CARNELIDGE_VOLCANO, HotDescription
    @ Cold Places
    case MAPSEC_TORMA_CAVE, ColdDescription
    case MAPSEC_ROUTE_12_EAST, ColdDescription
    case MAPSEC_ROUTE_12_WEST, ColdDescription
    @ Grassy Places (Most routes)
    case MAPSEC_ROUTE_1, GrassyDescription
    case MAPSEC_ROUTE_2, GrassyDescription
    case MAPSEC_ROUTE_3, GrassyDescription
    case MAPSEC_ROUTE_5, GrassyDescription
    case MAPSEC_ROUTE_9, GrassyDescription
    case MAPSEC_ROUTE_17, GrassyDescription
    case MAPSEC_ROUTE_18, GrassyDescription
    case MAPSEC_ROUTE_20, GrassyDescription
    case MAPSEC_ROUTE_22, CraggyDescription
    case MAPSEC_ORICHELLE_GARDEN, GrassyDescription
    @ Craggy Places
    case MAPSEC_ROUTE_4, CraggyDescription
    case MAPSEC_ROUTE_7, CraggyDescription
    case MAPSEC_ROUTE_11_SOUTH, CraggyDescription
    case MAPSEC_ROUTE_21, CraggyDescription
    case MAPSEC_ROUTE_24, CraggyDescription
    @ Places with a lot of water
    case MAPSEC_ROUTE_6, WateryDescription
    case MAPSEC_ROUTE_10, WateryDescription
    case MAPSEC_ROUTE_11_NORTH, WateryDescription
    case MAPSEC_LAKE_LAPLAZ, WateryDescription
    case MAPSEC_SEPPIRE_COVE, WateryDescription
    @ Beach Locations
    case MAPSEC_ROUTE_19, BeachDescription
    case MAPSEC_ROUTE_23, BeachDescription
    @ Rocky Places
    case MAPSEC_VICTORY_ROAD, CaveDescription
    case MAPSEC_HESSON_PASS, CaveDescription
    @ Sea Places
    case MAPSEC_ROUTE_14, SeaDescription
    case MAPSEC_ROUTE_15, SeaDescription
    case MAPSEC_ROUTE_16, SeaDescription
    @ Spooky Places
    case MAPSEC_FORGOTTEN_MANSE, SpookyDescription
    case MAPSEC_UTEYAN_RUINS, SpookyDescription
    @ Marshy Places
    case MAPSEC_ROUTE_8, MarshyDescription
    @ Forests and Jungles
    case MAPSEC_VARISI_FOREST, ForestDescription
    case MAPSEC_PERADON_FOREST, ForestDescription
    case MAPSEC_MIMMETT_JUNGLE, ForestDescription
    @ Default, when no cases are met (ex. trades, ultra space, etc.)
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Default m_LookLeft
    end

UrbanDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Urban m_LookLeft
    end

DesertDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Desert m_LookLeft
    end

HotDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Hot m_LookLeft
    end

ColdDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Cold m_LookLeft
    end

GrassyDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Grassy m_LookLeft
    end

CraggyDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Craggy m_LookLeft
    end

WateryDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Watery m_LookLeft
    end

BeachDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Beach m_LookLeft
    end

CaveDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Cave m_LookLeft
    end

SeaDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Sea m_LookLeft
    end

SpookyDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Spooky m_LookLeft
    end

MarshyDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Marshy m_LookLeft
    end

ForestDescription:
    npcchatwithmovement gText_BruccieVillageFacilities_PokemonCenter_CaughtLocationGirl_Forest m_LookLeft
    end

.global EventScript_BruccieVillageFacilities_Pokemart_IceHealsGirl
EventScript_BruccieVillageFacilities_Pokemart_IceHealsGirl:
    npcchatwithmovement gText_BruccieVillageFacilities_Pokemart_IceHealGirl m_LookLeft
    end

.global EventScript_BruccieVillageFacilities_Pokemart_StockBoy
EventScript_BruccieVillageFacilities_Pokemart_StockBoy:
    npcchatwithmovement gText_BruccieVillageFacilities_Pokemart_StockBoy m_LookUp
    end    
