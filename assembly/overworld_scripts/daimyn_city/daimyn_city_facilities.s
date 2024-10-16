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
    call ResetUteyaVillageGymFlagsOnWhiteout
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
    call SetupMugshotRival
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

.global EventScript_DaimynCityFacilities_PokeballTraveller
EventScript_DaimynCityFacilities_PokeballTraveller: 
    lock
    faceplayer
    msgbox gText_DaimynCityFacilities_PokemonCenter_TravellingMan_Intro MSG_NORMAL
    showmoney 0x0 0x0
    msgbox gText_DaimynCityFacilities_PokemonCenter_TravellingMan_SaleOffer MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokeballTraveller_ChoseNotToBuy
    checkmoney 1500
    compare LASTRESULT NO
    if equal _goto PokeballTraveller_NotEnoughMoney
    playse 0xF8 @ Money
    removemoney 1500
    updatemoney 0x0 0x0
    waitse
    pause DELAY_1SECOND
    hidemoney
    msgbox gText_DaimynCityFacilities_PokemonCenter_TravellingMan_Purchased MSG_NORMAL
    random 0x4
    switch LASTRESULT
    case 0, GiveSafariBall
    case 1, GiveSportBall
    case 2, GiveParkBall
    case 3, GiveDreamBall
    end

GiveSafariBall:
    obtainitem ITEM_SAFARI_BALL 0x1
    goto PokeballTraveller_AfterPurchase

GiveSportBall:
    obtainitem ITEM_SPORT_BALL 0x1
    goto PokeballTraveller_AfterPurchase

GiveParkBall:
    obtainitem ITEM_PARK_BALL 0x1
    goto PokeballTraveller_AfterPurchase

GiveDreamBall:
    obtainitem ITEM_DREAM_BALL 0x1
    goto PokeballTraveller_AfterPurchase

PokeballTraveller_AfterPurchase:
    msgbox gText_DaimynCityFacilities_PokemonCenter_TravellingMan_ReturningTomorrow MSG_NORMAL
    setflag 0xE35 @ Hide traveller man
    fadescreen FADEOUT_BLACK
    hidesprite LASTTALKED
    fadescreen FADEIN_BLACK
    end

PokeballTraveller_ChoseNotToBuy:
    hidemoney
    npcchatwithmovement gText_DaimynCityFacilities_PokemonCenter_TravellingMan_ChoseNotToBuy m_LookUp
    end

PokeballTraveller_NotEnoughMoney:
    hidemoney
    npcchatwithmovement gText_DaimynCityFacilities_PokemonCenter_TravellingMan_NotEnoughMoney m_LookUp
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
    checkflag 0x274 @ Permitted to go to ultra space
    if SET _goto SakuraAsksToGoToUltraSpace
    msgbox gText_DaimynCityFacilities_IRF_SakuraPreoccupied MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement 0x7 m_Surprise
    msgbox gText_DaimynCityFacilities_IRF_SakuraNoticesPlayer MSG_NORMAL
    checkflag 0x273 @ Completed Carnelidge Volcano story events
    if SET _goto SakuraTalksAboutAlistairsRecommendation
    faceplayer
    msgbox gText_DaimynCityFacilities_IRF_SakuraTurnsPlayerDown MSG_NORMAL
    applymovement 0x7 m_LookLeft
    end

SakuraTalksAboutAlistairsRecommendation:
    faceplayer
    msgbox gText_DaimynCityFacilities_IRF_SakuraTalksToPlayerFollowingAlistairsRecommendation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToHelpWithUltraSpace
    msgbox gText_DaimynCityFacilities_IRF_Sakura_PlayerWillingToGoToUltraSpace MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    setflag 0x274 @ Permitted to go to ultra space
    clearflag 0x062 @ Show the researcher in Eclipse Village
    end

ChoseNotToHelpWithUltraSpace:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_Sakura_PlayerUnwillingToGoToUltraSpace m_LookLeft
    end

SakuraAsksToGoToUltraSpace:
    faceplayer
    msgbox gText_DaimynCityFacilities_IRF_Sakura_AskingPlayerIfTheyWantToTravelToUltraSpace MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToGoToUltraSpace
    compare 0x40A7 0x0
    if notequal _goto SakuraAsksPlayerWhereTheyWantToGo
    if equal _goto SakuraConfirmsEclipseVillageDestination
    end

ChoseNotToGoToUltraSpace:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_Sakura_PlayerChoseNotToTravelToUltraSpace m_LookLeft
    end

UltraSpaceWarpCommon:
    msgbox gText_DaimynCityFacilities_IRF_Sakura_DirectsPlayerToMachine MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x5 @ Beside
    if lessthan _call PlayerWalksToMachineFromAbove
    if equal _call PlayerWalksToMachineFromRight
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromBelow
    waitmovement PLAYER
    applymovement 0x7 m_LookDown
    msgbox gText_DaimynCityFacilities_IRF_Sakura_StartingMachine MSG_NORMAL
    call UltraSpaceWarpEffect
    return

PlayerWalksToMachineFromAbove:
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromAbove
    waitmovement PLAYER
    call PlayerWalksToMachineFromRight
    return

PlayerWalksToMachineFromRight:
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromRight
    waitmovement PLAYER
    return

SakuraAsksPlayerWhereTheyWantToGo:
    @ TODO Later: Choosing ultra space destination
    return

SakuraConfirmsEclipseVillageDestination:
    msgbox gText_DaimynCityFacilities_IRF_Sakura_CanOnlyGoToEclipseVillage_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToGoToUltraSpace
    call UltraSpaceWarpCommon
    warpmuted 2 32 0xFF 0xB 0x9
    return

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
m_PlayerWalksToUltraSpaceMachineFromAbove: .byte walk_right, walk_down, end_m
m_PlayerWalksToUltraSpaceMachineFromRight: .byte walk_down, walk_left, end_m
m_PlayerWalksToUltraSpaceMachineFromBelow: .byte walk_left, walk_left, look_down, end_m
