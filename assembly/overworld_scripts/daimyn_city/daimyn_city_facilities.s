.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4054
.equ FlagHideRival, 0x03C
.equ SpriteRival, 0x2

.global MapScript_DaimynFacilities_PokemonCenter
MapScript_DaimynFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_DaimynFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_DaimynFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x06 @ Originally Vermillion City
    end

.global EventScript_DaimynCity_GuardHouseWest_Guard
EventScript_DaimynCity_GuardHouseWest_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseWest_Guard MSG_NORMAL
    end

.global EventScript_DaimynCity_GuardHouseSouth_Guard
EventScript_DaimynCity_GuardHouseSouth_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseSouth_Guard MSG_NORMAL
    end

.global TileScript_DaimynCity_GuardHouseWest_TriggerRival
TileScript_DaimynCity_GuardHouseWest_TriggerRival:
    lock
    call RivalBattleCommon_Intro
    applymovement PLAYER m_WalkLeft
    applymovement SpriteRival m_RivalMeetsPlayer_West
    waitmovement ALLEVENTS
    call RivalBattleCommon
    applymovement PLAYER m_PlayerMovesOutOfWay_West
    waitmovement ALLEVENTS
    applymovement SpriteRival m_RivalLeaves_West
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    setflag FlagHideRival
    applymovement PLAYER m_PlayerLeavesWithRival_West
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    warp 3 5 0 @ West gate
    release
    end

.global TileScript_DaimynCity_GuardHouseSouth_TriggerRival
TileScript_DaimynCity_GuardHouseSouth_TriggerRival:
    lock
    call RivalBattleCommon_Intro
    applymovement PLAYER m_WalkDown
    applymovement SpriteRival m_RivalMeetsPlayer_South
    waitmovement ALLEVENTS
    call RivalBattleCommon
    applymovement PLAYER m_PlayerMovesOutOfWay_South
    waitmovement ALLEVENTS
    applymovement SpriteRival m_RivalLeaves_South
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    setflag FlagHideRival
    applymovement PLAYER m_PlayerLeavesWithRival_South
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    warp 3 5 1 @ South gate
    release
    end

RivalBattleCommon_Intro:
    clearflag FlagHideRival
    showsprite SpriteRival
    playbgm 0x195
    applymovement PLAYER m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalIntroduction MSG_NORMAL
    return

RivalBattleCommon:
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalExplainsDaimynCity MSG_NORMAL
    applymovement SpriteRival m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalInitiatesBattle MSG_NORMAL
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    trainerbattle3 0x0 0x88 0x100 gText_DaimynCityFacilities_GuardHouse_RivalLoses
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalConcludesBattle MSG_NORMAL
    obtainitem ITEM_MACHO_BRACE 0x1
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalExplainsMachoBrace MSG_NORMAL
    applymovement SpriteRival m_Surprise
    waitmovement ALLEVENTS
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalNoItems MSG_NORMAL
    pause DELAY_HALFSECOND
    applymovement SpriteRival m_Joy
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalOffersTourOfDaimynCity MSG_NORMAL
    setvar StoryEventVar 0x1 @ Prevent from happening again in either guard house
    return

.global EventScript_DaimynCityFacilities_RestaurauntBoy
EventScript_DaimynCityFacilities_RestaurauntBoy:
    npcchat gText_DaimynCityFacilities_RestaurantBoy
    end

.global EventScript_DaimynCityFacilities_RestaurauntBigMan
EventScript_DaimynCityFacilities_RestaurauntBigMan:
    lock
    faceplayer
    checkflag 0x24D @ Got leftovers
    If SET _goto LeftoversDescription
    msgbox gText_DaimynCityFacilities_RestaurantBigMan MSG_NORMAL
    obtainitem ITEM_LEFTOVERS 0x1
    setflag 0x24D @ Got Leftovers
    goto LeftoversDescription

LeftoversDescription:
    msgbox gText_DaimynCityFacilities_RestaurantBigMan_LeftoversDescription MSG_NORMAL
    release
    end

.global EventScript_DaimynCityFacilities_RestaurauntGentleman
EventScript_DaimynCityFacilities_RestaurauntGentleman:
    msgbox gText_DaimynCityFacilities_RestaurantGentleman MSG_NORMAL
    end

.global EventScript_DaimynCityFacilities_RestaurauntGirl
EventScript_DaimynCityFacilities_RestaurauntGirl:
    npcchat gText_DaimynCityFacilities_RestaurantGirl
    end

.global EventScript_DaimynCityFacilities_PokemonCenterOldWoman
EventScript_DaimynCityFacilities_PokemonCenterOldWoman:
    npcchat2 0x2 m_LookLeft gText_DaimynCityFacilities_PokemonCenter_OldWoman
    end

.global EventScript_DaimynCityFacilities_PokemonCenterWoman
EventScript_DaimynCityFacilities_PokemonCenterWoman:
    npcchat2 0x3 m_LookLeft gText_DaimynCityFacilities_PokemonCenter_Woman
    end

.global EventScript_DaimynCityFacilities_PokemonCenterGirl
EventScript_DaimynCityFacilities_PokemonCenterGirl:
    npcchat2 0x4 m_LookLeft gText_DaimynCityFacilities_PokemonCenter_Girl
    end

m_RivalMeetsPlayer_West: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_RivalMeetsPlayer_South: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerMovesOutOfWay_West: .byte walk_up, look_down, end_m
m_PlayerMovesOutOfWay_South: .byte walk_right, look_left, end_m
m_RivalLeaves_West: .byte walk_right, walk_right, walk_right, set_invisible, end_m
m_RivalLeaves_South: .byte walk_up, walk_up, walk_up, set_invisible, end_m
m_PlayerLeavesWithRival_West: .byte walk_down, walk_right, walk_right, end_m
m_PlayerLeavesWithRival_South: .byte walk_left, walk_up, walk_up, end_m
