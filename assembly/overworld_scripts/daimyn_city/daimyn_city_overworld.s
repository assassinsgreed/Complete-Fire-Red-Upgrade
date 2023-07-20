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

.global EventScript_DaimynCityOverworld_GamblingMan
EventScript_DaimynCityOverworld_GamblingMan:
    npcchat gText_DaimynCityOverworld_GamblingMan
    end

.global EventScript_DaimynCityOverworld_Picknicker
EventScript_DaimynCityOverworld_Picknicker:
    npcchat gText_DaimynCityOverworld_Picknicker
    end

.global EventScript_DaimynCityOverworld_Hiker
EventScript_DaimynCityOverworld_Hiker:
    npcchat gText_DaimynCityOverworld_Hiker
    end

.global EventScript_DaimynCityOverworld_SuperNerd
EventScript_DaimynCityOverworld_SuperNerd:
    npcchat gText_DaimynCityOverworld_SuperNerd
    end

.global EventScript_DaimynCityOverworld_OldMan
EventScript_DaimynCityOverworld_OldMan:
    npcchat gText_DaimynCityOverworld_OldMan
    end

.global EventScript_DaimynCityOverworld_Boy
EventScript_DaimynCityOverworld_Boy:
    npcchat gText_DaimynCityOverworld_Boy
    end

.global EventScript_DaimynCityOverworld_Biker
EventScript_DaimynCityOverworld_Biker:
    npcchat gText_DaimynCityOverworld_Biker
    end

.global EventScript_DaimynCityOverworld_Girl
EventScript_DaimynCityOverworld_Girl:
    npcchat gText_DaimynCityOverworld_Girl
    end

.global EventScript_DaimynCityOverworld_Policeman
EventScript_DaimynCityOverworld_Policeman:
    npcchat gText_DaimynCityOverworld_Policeman
    end

.global EventScript_DaimynCityOverworld_PlutoNW
EventScript_DaimynCityOverworld_PlutoNW:
    npcchat gText_DaimynCityOverworld_PlutoNW
    end

.global EventScript_DaimynCityOverworld_PlutoSE
EventScript_DaimynCityOverworld_PlutoSE:
    npcchat gText_DaimynCityOverworld_PlutoSE
    end

.global EventScript_DaimynCityOverworld_PlutoSW
EventScript_DaimynCityOverworld_PlutoSW:
    npcchat gText_DaimynCityOverworld_PlutoSW
    end

.global EventScript_DaimynCity_FindTM46Thief
EventScript_DaimynCity_FindTM46Thief:
    setvar CHOSEN_ITEM ITEM_TM46
    call ItemScript_Common_FindTM
    end

.global SignScript_DaimynCityOverworld_Restaurant
SignScript_DaimynCityOverworld_Restaurant:
    msgbox gText_DaimynCityOverworld_RestaurantSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_AscensionTower
SignScript_DaimynCityOverworld_AscensionTower:
    msgbox gText_DaimynCityOverworld_AscensionTowerSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_ShoppingMall
SignScript_DaimynCityOverworld_ShoppingMall:
    msgbox gText_DaimynCityOverworld_ShoppingMallSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_LanasHouse
SignScript_DaimynCityOverworld_LanasHouse:
    msgbox gText_DaimynCityOverworld_LanasHouseSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_Gym
SignScript_DaimynCityOverworld_Gym:
    msgbox gText_DaimynCityOverworld_GymSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_InterdimensionalResearchLab
SignScript_DaimynCityOverworld_InterdimensionalResearchLab:
    msgbox gText_DaimynCityOverworld_InterdimensionalResearchLabSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_GuardHouseNorth
SignScript_DaimynCityOverworld_GuardHouseNorth:
    msgbox gText_DaimynCityOverworld_GuardHouseNorthSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_GuardHouseWest
SignScript_DaimynCityOverworld_GuardHouseWest:
    msgbox gText_DaimynCityOverworld_GuardHouseWestSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_GuardHouseEast
SignScript_DaimynCityOverworld_GuardHouseEast:
    msgbox gText_DaimynCityOverworld_GuardHouseEastSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_GuardHouseSouth
SignScript_DaimynCityOverworld_GuardHouseSouth:
    msgbox gText_DaimynCityOverworld_GuardHouseSouthSign MSG_SIGN
    end

.global SignScript_DaimynCityOverworld_DaimynCityPlacard
SignScript_DaimynCityOverworld_DaimynCityPlacard:
    msgbox gText_DaimynCityOverworld_CityPlacardSign MSG_SIGN
    end
