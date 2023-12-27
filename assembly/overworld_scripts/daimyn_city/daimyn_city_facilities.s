.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4054
.equ FlagHideRival, 0x03C
.equ SpriteRival, 0x2

.global MapScript_DaimynCity_GuardHouseWest
MapScript_DaimynCity_GuardHouseWest:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_DaimynCity_GuardHouses_HideRival
	.byte MAP_SCRIPT_TERMIN

.global MapScript_DaimynCity_GuardHouseSouth
MapScript_DaimynCity_GuardHouseSouth:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_DaimynCity_GuardHouses_HideRival
	.byte MAP_SCRIPT_TERMIN

MapScript_DaimynCity_GuardHouses_HideRival:
    setflag 0x3C @ Hide rival in case player lost to them
    end

.global MapScript_DaimynFacilities_PokemonCenter
MapScript_DaimynFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_DaimynFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_DaimynFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x06 @ Originally Vermillion City
    call ResetRoute11PlutoEventOnWhiteout
    end

.global EventScript_DaimynCity_GuardHouseWest_Guard
EventScript_DaimynCity_GuardHouseWest_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseWest_Guard MSG_NORMAL
    end

.global EventScript_DaimynCity_GuardHouseSouth_Guard
EventScript_DaimynCity_GuardHouseSouth_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseSouth_Guard MSG_NORMAL
    end

.global EventScript_DaimynCity_GuardHouseEast_Guard
EventScript_DaimynCity_GuardHouseEast_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseEast_Guard MSG_NORMAL
    end

.global EventScript_DaimynCity_GuardHouseNorth_Guard
EventScript_DaimynCity_GuardHouseNorth_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseNorth_Guard MSG_NORMAL
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
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalIntroduction MSG_NORMAL
    return

RivalBattleCommon:
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalExplainsDaimynCity MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement SpriteRival m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalInitiatesBattle MSG_NORMAL
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    trainerbattle3 0x0 0x88 0x100 gText_DaimynCityFacilities_GuardHouse_RivalLoses
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalConcludesBattle MSG_NORMAL
    obtainitem ITEM_MACHO_BRACE 0x1
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalExplainsMachoBrace MSG_NORMAL
    sound 0x15 @ Exclaim
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
    npcchatwithmovement gText_DaimynCityFacilities_PokemonCenter_OldWoman m_LookLeft
    end

.global EventScript_DaimynCityFacilities_PokemonCenterWoman
EventScript_DaimynCityFacilities_PokemonCenterWoman:
    npcchatwithmovement gText_DaimynCityFacilities_PokemonCenter_Woman m_LookLeft
    end

.global EventScript_DaimynCityFacilities_PokemonCenterGirl
EventScript_DaimynCityFacilities_PokemonCenterGirl:
    npcchatwithmovement gText_DaimynCityFacilities_PokemonCenter_Girl m_LookLeft
    end

.global EventScript_DaimynCityFacilities_PCResearcher
EventScript_DaimynCityFacilities_PCResearcher:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_PCResearcher m_LookUp
    end

.global EventScript_DaimynCityFacilities_MachineryResearcher
EventScript_DaimynCityFacilities_MachineryResearcher:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_MachineryResearcher m_LookUp
    end

.global EventScript_DaimynCityFacilities_WanderingResearcher
EventScript_DaimynCityFacilities_WanderingResearcher:
    npcchat gText_DaimynCityFacilities_IRF_WanderingResearcher
    end

.global EventScript_DaimynCityFacilities_TableBottomRightResearcher
EventScript_DaimynCityFacilities_TableBottomRightResearcher:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_TableBottomRightResearcher m_LookUp
    end

.global EventScript_DaimynCityFacilities_TableLeftResearcher
EventScript_DaimynCityFacilities_TableLeftResearcher:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_TableTopLeftResearcher m_LookRight
    end

.global EventScript_DaimynCityFacilities_Pokeball
EventScript_DaimynCityFacilities_Pokeball:
    msgbox gText_DaimynCityFacilities_IRF_TypeNullPrompt MSG_NORMAL
    applymovement 0x3 m_LookUp
    msgbox gText_DaimynCityFacilities_IRF_TypeNullPlayerdenied MSG_NORMAL
    end

.global EventScript_DaimynCityFacilities_ProfessorSakura
EventScript_DaimynCityFacilities_ProfessorSakura:
    msgbox gText_DaimynCityFacilities_IRF_SakuraPreoccupied MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement 0x7 m_Surprise
    msgbox gText_DaimynCityFacilities_IRF_SakuraNoticesPlayer MSG_NORMAL
    faceplayer
    msgbox gText_DaimynCityFacilities_IRF_SakuraTurnsPlayerDown MSG_NORMAL
    applymovement 0x7 m_LookLeft
    end

.global SignScript_DaimynCityFacilities_UltraSpaceMachine
SignScript_DaimynCityFacilities_UltraSpaceMachine:
    msgbox gText_DaimynCityFacilities_IRF_UltraMachine MSG_SIGN
    end

.global SignScript_DaimynCityFacilities_UltraSpaceSafetyTipsSign
SignScript_DaimynCityFacilities_UltraSpaceSafetyTipsSign:
    msgbox gText_DaimynCityFacilities_IRF_SafetyTips MSG_SIGN
    end

.global SignScript_DaimynCityFacilities_BeastBallsCase
SignScript_DaimynCityFacilities_BeastBallsCase:
    msgbox gText_DaimynCityFacilities_IRF_BeastBallsShelf MSG_SIGN
    end

.global SignScript_DaimynCityFacilities_PC
SignScript_DaimynCityFacilities_PC:
    msgbox gText_DaimynCityFacilities_IRF_PC MSG_SIGN
    end

m_RivalMeetsPlayer_West: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_RivalMeetsPlayer_South: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerMovesOutOfWay_West: .byte walk_up, look_down, end_m
m_PlayerMovesOutOfWay_South: .byte walk_right, look_left, end_m
m_RivalLeaves_West: .byte walk_right, walk_right, walk_right, set_invisible, end_m
m_RivalLeaves_South: .byte walk_up, walk_up, walk_up, set_invisible, end_m
m_PlayerLeavesWithRival_West: .byte walk_down, walk_right, walk_right, end_m
m_PlayerLeavesWithRival_South: .byte walk_left, walk_up, walk_up, end_m
