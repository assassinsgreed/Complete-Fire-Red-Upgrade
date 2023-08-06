.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Rival, 0xF
.equ Selene, 0x10
.equ Alistair, 0x11
.equ AscensionTowerEmployee, 0x12
.equ StoryEventVar, 0x4054

.global MapScript_DaimynCity
MapScript_DaimynCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_DaimynCity_FlightSpot
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_DaimynCity_StoryEvents
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_DaimynCity_FlightSpot:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x1
    if equal _call SetupStoryEventWest
    compare 0x4000 0x1
    if notequal _call SetupStoryEventSouth
    setworldmapflag 0x895
    end

LevelScripts_DaimynCity_StoryEvents:
    levelscript StoryEventVar 0x1 LevelScript_RivalsTour
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_RivalsTour:
    lock
    compare 0x4000 0x1
    if equal _call RivalFacePlayerWest
    if notequal _call RivalFacePlayerSouth
    msgbox gText_DaimynCityOverworld_Story_RivalStartsTour MSG_NORMAL
    playbgm 0x180 @ Let's go together
    compare 0x4000 0x1
    if equal _call MoveToRestaurantWest
    if notequal _call MoveToRestaurantSouth
    msgbox gText_DaimynCityOverworld_Story_RivalTour1 MSG_KEEPOPEN @ Keep box open, so reaching the end of text doesn't kill movement
    waitmovement Rival @ Wait for rival instead of all events; a biker moves forever and will lock the script
    msgbox gText_DaimynCityOverworld_Story_RivalTour2 MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DaimynCityOverworld_Story_RivalTour3 MSG_NORMAL
    applymovement Rival m_WalkToInterdimensionalResearchLab_Rival
    applymovement PLAYER m_WalkToInterdimensionalResearchLab_Player
    msgbox gText_DaimynCityOverworld_Story_RivalTour4 MSG_KEEPOPEN
    waitmovement Rival
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_DaimynCityOverworld_Story_RivalTour5 MSG_NORMAL
    applymovement Rival m_WalkToPark_Rival
    applymovement PLAYER m_WalkToPark_Player
    msgbox gText_DaimynCityOverworld_Story_RivalTour6 MSG_KEEPOPEN
    waitmovement Rival
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour7 MSG_NORMAL
    applymovement Rival m_WalkToMall_Rival
    applymovement PLAYER m_WalkToMall_Player
    msgbox gText_DaimynCityOverworld_Story_RivalTour8 MSG_KEEPOPEN
    waitmovement Rival
    showsprite Selene
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    applymovement Selene m_SeleneVisitsThePlayer
    msgbox gText_DaimynCityOverworld_Story_RivalTour9 MSG_NORMAL
    waitmovement Selene
    playbgm 0x196 @ Bianca Encounter
    msgbox gText_DaimynCityOverworld_Story_RivalTour10 MSG_NORMAL
    applymovement Rival m_Surprise
    applymovement PLAYER m_Surprise
    msgbox gText_DaimynCityOverworld_Story_RivalTour11 MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_DaimynCityOverworld_Story_RivalTour12 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour13 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour14 MSG_NORMAL
    applymovement Rival m_LookRight
    msgbox gText_DaimynCityOverworld_Story_RivalTour15 MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_DaimynCityOverworld_Story_RivalTour16 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour17 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour18 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour19 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour20 MSG_NORMAL
    playbgm 0x180 @ Let's go together
    applymovement Selene m_WalkToPokemonCenter_Selene
    applymovement Rival m_WalkToPokemonCenter_Rival
    applymovement PLAYER m_WalkToPokemonCenter_Player
    msgbox gText_DaimynCityOverworld_Story_RivalTour21 MSG_KEEPOPEN
    waitmovement Selene
    msgbox gText_DaimynCityOverworld_Story_RivalTour22 MSG_NORMAL
    applymovement Selene m_WalkToGym_All
    applymovement Rival m_WalkToGym_All
    applymovement PLAYER m_WalkToGym_All
    waitmovement Selene
    msgbox gText_DaimynCityOverworld_Story_RivalTour23 MSG_NORMAL
    applymovement Selene m_WalkToAscensionTower_Selene
    applymovement Rival m_WalkToAscensionTower_Rival
    applymovement PLAYER m_WalkToAscensionTower_Player
    msgbox gText_DaimynCityOverworld_Story_RivalTour24 MSG_KEEPOPEN
    waitmovement PLAYER
    playbgm 0x156 @ Alistair Encounter
    msgbox gText_DaimynCityOverworld_Story_RivalTour25 MSG_NORMAL
    applymovement Selene m_Question
    applymovement Rival m_Question
    applymovement PLAYER m_Question
    applymovement Alistair m_AlistairArrives
    waitmovement Alistair
    applymovement Selene m_LookUp
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour26 MSG_NORMAL
    applymovement Selene m_Question
    msgbox gText_DaimynCityOverworld_Story_RivalTour27 MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour28 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour29 MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_DaimynCityOverworld_Story_RivalTour30 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour31 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour32 MSG_NORMAL
    applymovement Alistair m_AlistairLeaves
    applymovement Selene m_LookRight
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookRight
    waitmovement Alistair
    hidesprite Alistair
    playbgm 0x196 @ Bianca Encounter
    applymovement Selene m_SeleneAddressesPlayerAndRival
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour33 MSG_NORMAL
    clearflag 0x03C @ Temporary, used to hide rival in guardhouse
    opendoor 0x1D 0x9
    waitdooranim
    showsprite AscensionTowerEmployee
    applymovement AscensionTowerEmployee m_WalkDown
    waitmovement AscensionTowerEmployee
    closedoor 0x1D 0x9
    waitdooranim
    msgbox gText_DaimynCityOverworld_Story_RivalTour34 MSG_NORMAL
    applymovement Selene m_Surprise
    msgbox gText_DaimynCityOverworld_Story_RivalTour35 MSG_NORMAL
    applymovement Selene m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour36 MSG_NORMAL
    applymovement AscensionTowerEmployee m_LookUp
    opendoor 0x1D 0x9
    waitdooranim
    applymovement AscensionTowerEmployee m_WalkUp
    pause DELAY_HALFSECOND
    playse 0x8 @ door open
    hidesprite AscensionTowerEmployee
    setflag 0x03C @ Hide employee and rival in guardhouse again
    closedoor 0x1D 0x9
    waitdooranim
    applymovement Selene m_LookDown
    msgbox gText_DaimynCityOverworld_Story_RivalTour37 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour38 MSG_NORMAL
    msgbox gText_DaimynCityOverworld_Story_RivalTour39 MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    applymovement Selene m_LookRight
    msgbox gText_DaimynCityOverworld_Story_RivalTour40 MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    opendoor 0x1D 0x9
    waitdooranim
    applymovement Selene m_WalkUp
    pause DELAY_HALFSECOND
    playse 0x8 @ door open
    hidesprite Selene
    closedoor 0x1D 0x9
    waitdooranim
    fadedefaultbgm
    applymovement Rival m_WalkRight
    applymovement PLAYER m_LookLeft
    msgbox gText_DaimynCityOverworld_Story_RivalTour41 MSG_YESNO
    compare LASTRESULT YES
    if equal _call RecognizedAlistair
    if notequal _call DidNotRecognizeAlistair
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_DaimynCityOverworld_Story_RivalTour42 MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_DaimynCityOverworld_Story_RivalTour43 MSG_NORMAL
    applymovement Rival m_WalkUp
    waitmovement Rival
    applymovement Rival m_AlistairLeaves
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookRight
    waitmovement Rival
    hidesprite Rival
    setflag 0x251 @ Hide story events
    setvar StoryEventVar 0x2
    release
    end

RecognizedAlistair:
    msgbox gText_DaimynCityOverworld_Story_RecognizedAlistair MSG_NORMAL
    return

DidNotRecognizeAlistair:
    msgbox gText_DaimynCityOverworld_Story_DidNotRecognizeAlistair MSG_NORMAL
    return

SetupStoryEventWest:
    movesprite2 Rival, 0x2, 0x23 @ In front of player
    return

RivalFacePlayerWest:
    applymovement Rival m_LookLeft
    return

MoveToRestaurantWest:
    applymovement Rival m_WalkToRestaurant_West_Rival
    applymovement PLAYER m_WalkToRestaurant_West_Player
    return

SetupStoryEventSouth:
    movesprite2 Rival, 0x26, 0x41 @ In front of player
    return

RivalFacePlayerSouth:
    applymovement Rival m_LookDown
    return

MoveToRestaurantSouth:
    applymovement Rival m_WalkToRestaurant_South_Rival
    applymovement PLAYER m_WalkToRestaurant_South_Player
    return

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

.global EventScript_DaimynCity_FindTM54FalseSwipe
EventScript_DaimynCity_FindTM54FalseSwipe:
    setvar CHOSEN_ITEM ITEM_TM54
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

.global SignScript_DaimynCityOverworld_FactorySign
SignScript_DaimynCityOverworld_FactorySign:
    msgbox gText_DaimynCityOverworld_DaimynFactorySign MSG_SIGN
    end

m_WalkToRestaurant_West_Rival: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_WalkToRestaurant_West_Player: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_WalkToRestaurant_South_Rival: .byte walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_WalkToRestaurant_South_Player: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_up, end_m
m_WalkToInterdimensionalResearchLab_Rival: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_left, look_up, end_m
m_WalkToInterdimensionalResearchLab_Player: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, end_m
m_WalkToPark_Rival: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, look_left, end_m
m_WalkToPark_Player: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_WalkToMall_Rival: .byte walk_up, walk_left, walk_left, walk_up, walk_up, walk_left, walk_left, walk_up, walk_up, walk_left, walk_left, walk_left, look_up, end_m
m_WalkToMall_Player: .byte walk_up, walk_up, walk_left, walk_left, walk_up, walk_up, walk_left, walk_left, walk_up, walk_up, walk_left, walk_left, look_up, end_m
m_SeleneVisitsThePlayer: .byte walk_right, walk_up, walk_up, walk_right, walk_right, walk_up, walk_up, walk_right, walk_up, look_right, end_m
m_WalkToPokemonCenter_Selene: .byte walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_left, walk_left, look_up, end_m
m_WalkToPokemonCenter_Rival: .byte walk_left, walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_left, look_up, end_m
m_WalkToPokemonCenter_Player: .byte walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, look_up, end_m
m_WalkToGym_All: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, look_up, end_m
m_WalkToAscensionTower_Selene: .byte walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, end_m
m_WalkToAscensionTower_Rival: .byte walk_left, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_left, walk_up, end_m
m_WalkToAscensionTower_Player: .byte walk_left, walk_left, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, walk_right, walk_up, end_m
m_AlistairArrives: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, look_down, end_m
m_AlistairLeaves: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_SeleneAddressesPlayerAndRival: .byte walk_up, look_down, end_m
