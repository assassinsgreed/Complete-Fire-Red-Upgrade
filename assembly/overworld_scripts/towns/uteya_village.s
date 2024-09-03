.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_UteyaVillage
MapScript_UteyaVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_UteyaVillage_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UteyaVillage_FlightSpot:
    setworldmapflag 0x89A @ Visited Uteya Village
    end

.global EventScript_UteyaVillage_HessonPassKid
EventScript_UteyaVillage_HessonPassKid:
    npcchat gText_UteyaVillage_HessonPassBoy
    end

.global EventScript_UteyaVillage_GymGirl
EventScript_UteyaVillage_GymGirl:
    npcchatwithmovement gText_UteyaVillage_GymGirl m_LookUp
    end

.global EventScript_UteyaVillage_UteyaRuinsMan
EventScript_UteyaVillage_UteyaRuinsMan:
    npcchat gText_UteyaVillage_UteyaRuinsMan
    end

.global EventScript_UteyaVillage_TrainerHouseOldMan
EventScript_UteyaVillage_TrainerHouseOldMan:
    npcchatwithmovement gText_UteyaVillage_TrainerHouseOldMan m_LookLeft
    end

.global EventScript_UteyaVillage_TM30_ShadowBall
EventScript_UteyaVillage_TM30_ShadowBall:
    setvar CHOSEN_ITEM ITEM_TM30
    call ItemScript_Common_FindTM
    end

.global SignScript_UteyaVillage_HessonPass
SignScript_UteyaVillage_HessonPass:
    msgbox gText_UteyaVillage_HessonPass MSG_SIGN
    end

.global SignScript_UteyaVillage_TownPlacard
SignScript_UteyaVillage_TownPlacard:
    msgbox gText_UteyaVillage_TownPlacard MSG_SIGN
    end

.global SignScript_UteyaVillage_GymSign
SignScript_UteyaVillage_GymSign:
    msgbox gText_UteyaVillage_GymSign MSG_SIGN
    end

.global SignScript_UteyaVillage_TrainerHouse
SignScript_UteyaVillage_TrainerHouse:
    msgbox gText_UteyaVillage_TrainerHouse MSG_SIGN
    end

// Facilities
.global MapScript_UteyaVillage_PokemonCenter
MapScript_UteyaVillage_PokemonCenter:   
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_UteyaVillageFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_UteyaVillageFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0xE
    end

.global EventScript_PokemonCenter_Woman
EventScript_PokemonCenter_Woman:
    npcchatwithmovement gText_UteyaVillage_PokemonCenter_Woman m_LookLeft
    end

.global EventScript_PokemonCenter_SuperNerd
EventScript_PokemonCenter_SuperNerd:
    npcchatwithmovement gText_UteyaVillage_PokemonCenter_SuperNerd m_LookUp
    end

.global EventScript_PokemonCenter_BirdKeeper
EventScript_PokemonCenter_BirdKeeper:
    npcchat gText_UteyaVillage_PokemonCenter_BirdKeeper
    end

.global EventScript_Pokemart_StatBoostingBerriesShop
EventScript_Pokemart_StatBoostingBerriesShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart UteyaVillagePokemart_StatBoostingBerryStock
    goto EventScript_EndMart

.align 1
UteyaVillagePokemart_StatBoostingBerryStock:
    .hword ITEM_LIECHI_BERRY  // Attack, when below 1/4 hp
    .hword ITEM_GANLON_BERRY  // Defense, when below 1/4 hp
    .hword ITEM_PETAYA_BERRY  // Sp. Attack, when below 1/4 hp
    .hword ITEM_APICOT_BERRY  // Sp. Defense, when below 1/4 hp
    .hword ITEM_SALAC_BERRY   // Speed, when below 1/4 hp
    .hword ITEM_LANSAT_BERRY  // Crit rate, when below 1/4 hp
    .hword ITEM_STARF_BERRY   // Random stat, when below 1/4 hp
    .hword ITEM_KEE_BERRY     // Defense, when hit by a physical move
    .hword ITEM_MARANGA_BERRY // Sp. Defense, when hit by a special move
    .hword ITEM_NONE

.global EventScript_Pokemart_Girl
EventScript_Pokemart_Girl:
    npcchatwithmovement gText_UteyaVillage_Pokemart_Girl m_LookRight
    end

.global EventScript_Pokemart_OldWoman
EventScript_Pokemart_OldWoman:
    npcchatwithmovement gText_UteyaVillage_Pokemart_Woman m_LookUp
    end

