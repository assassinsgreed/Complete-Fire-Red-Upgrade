.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4054
.equ FlagHideRival, 0x03C
.equ SpriteRival, 0x2
.equ Sakura, 0x7
.equ PCResearcher, 0x1

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

.global MapScripts_InterdimensionalResearchFacility
MapScripts_InterdimensionalResearchFacility:
    mapscript MAP_SCRIPT_ON_LOAD MapScripts_InterdimensionalResearchFacility_MoveSakuraForUltraEpisodeInitialEvents
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_InterdimensionalResearchFacility
	.byte MAP_SCRIPT_TERMIN

MapScripts_InterdimensionalResearchFacility_MoveSakuraForUltraEpisodeInitialEvents:
    compare 0x4073 0x5
    if equal _call MoveTypeNullResearcher
    compare 0x4073 0x1
    if notequal _goto End
    movesprite2 0x7 0xC 0xA @ Move Sakura above player (permanent, because she is otherwise out of in-memory npcs)
    end

MoveTypeNullResearcher:
    movesprite2 0x3 0x14 0x3 @ Move researcher in front of Type:Null ball
    setobjectmovementtype 0x3 look_down
    end

LevelScripts_InterdimensionalResearchFacility:
    levelscript 0x4073 0x1 LevelScript_InterdimensionalResearchFacility_UltraEpisode_InitialEvents
    levelscript 0x4073 0x4 LevelScript_InterdimensionalResearchFacility_UltraEpisode_PostCosmogEvents
    levelscript 0x4073 0xB LevelScript_InterdimensionalResearchFacility_UltraEpisode_PostUltraNecrozma
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_InterdimensionalResearchFacility_UltraEpisode_InitialEvents:
    pause DELAY_HALFSECOND
    applymovement Sakura m_SakuraPacesLeft
    waitmovement Sakura
    msgbox gText_UltraEpisode_Intro_SakuraPondering MSG_NORMAL
    applymovement Sakura m_SakuraPacesRight
    waitmovement Sakura
    applymovement Sakura m_SakuraPacesRight
    waitmovement Sakura
    msgbox gText_UltraEpisode_Intro_SakuraPondering2 MSG_NORMAL
    applymovement Sakura m_SakuraPacesLeft
    waitmovement Sakura
    applymovement Sakura m_LookDown
    pause DELAY_HALFSECOND
    applymovement Sakura m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_UltraEpisode_Intro_SakuraAcknowledgesPlayer MSG_NORMAL
    applymovement Sakura m_SakuraApproachesPlayer
    waitmovement Sakura
    msgbox gText_UltraEpisode_Intro_SakuraAltarOfEclipseQuestion MSG_YESNO
    compare LASTRESULT YES
    if equal _call UltraEpisode_Intro_RememberAltarOfEclipse
    if notequal _call UltraEpisode_Intro_DoNotRememberAltarOfEclipse
    applymovement Sakura m_WalkLeft
    msgbox gText_UltraEpisode_Intro_Sakura_MentioningReadings MSG_NORMAL
    applymovement Sakura m_WalkRight
    waitmovement Sakura
    applymovement Sakura m_WalkRight
    msgbox gText_UltraEpisode_Intro_Sakura_ExtrapolatingOnFindings MSG_NORMAL
    applymovement Sakura m_WalkLeft
    waitmovement Sakura
    applymovement Sakura m_LookDown
    msgbox gText_UltraEpisode_Intro_Sakura_ConcludesFindings MSG_NORMAL
    obtainitem ITEM_BEAST_BALL 5
    msgbox gText_UltraEpisode_Intro_Sakura_GivesBeastBalls MSG_NORMAL
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookLeft
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_MoveToResearcher
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_UltraEpisode_Intro_Sakura_CommentsOnBuyingBeastBalls MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_MoveToPlayer
    waitmovement CAMERA
    special CAMERA_END
    applymovement Sakura m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_UltraEpisode_Intro_Sakura_PreparingToStart MSG_NORMAL
    applymovement Sakura m_SakuraReturnToMachine
    waitmovement Sakura
    movesprite Sakura 0x3 0x5 @ Move Sakura back to her original position (while in map)
    movesprite2 Sakura 0x3 0x5 @ Move Sakura back to her original position (permanently)
    setvar 0x4073 0x2 @ Ultra Episode has started
    clearflag 0x06E @ Show Challengable Cosmog at Altar of Eclipse
    clearflag 0x77 @ Show Taken Cosmog in ultra space
    end

UltraEpisode_Intro_RememberAltarOfEclipse:
    msgbox gText_UltraEpisode_Intro_Sakura_PlayerRecallsAltar MSG_NORMAL
    return

UltraEpisode_Intro_DoNotRememberAltarOfEclipse:
    msgbox gText_UltraEpisode_Intro_Sakura_PlayerDoesNotRecallAltar MSG_NORMAL
    return

LevelScript_InterdimensionalResearchFacility_UltraEpisode_PostCosmogEvents:
    applymovement Sakura m_LookDown
    msgbox gText_UltraEpisode_PostCosmog_Sakura_WelcomeBack MSG_NORMAL
    applymovement Sakura m_SakuraWelcomesPlayerBackAfterCosmog
    waitmovement Sakura
    applymovement PLAYER m_LookRight
    msgbox gText_UltraEpisode_PostCosmog_Sakura_AsksAboutSource MSG_NORMAL
    applymovement Sakura m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_UltraEpisode_PostCosmog_Sakura_LearnsOfWormholes MSG_NORMAL
    applymovement Sakura m_LookDown
    msgbox gText_UltraEpisode_PostCosmog_Sakura_Pondering MSG_NORMAL
    applymovement Sakura m_LookLeft
    msgbox gText_UltraEpisode_PostCosmog_Sakura_AsksToSeeCosmog MSG_NORMAL
    setvar LASTRESULT SPECIES_COSMOG
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if notequal _goto UltraEpisodeCosmogNotCaught
    playse 0x19 @ Correct
    msgbox gText_UltraEpisode_PostCosmog_Sakura_CaughtCosmog MSG_NORMAL
    pause DELAY_HALFSECOND
    applymovement Sakura m_LookDown
    msgbox gText_UltraEpisode_PostCosmog_Sakura_FindingsDoNotMatch MSG_NORMAL
    applymovement Sakura m_LookLeft
    msgbox gText_UltraEpisode_PostCosmog_Sakura_WrongUltraBeast MSG_NORMAL
    playbgm 0x181 @ Necrozma appearance
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_PostCosmog_MoveToResearcher
    waitmovement CAMERA
    special CAMERA_END
    applymovement PCResearcher m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_UltraEpisode_PostCosmog_PCResearcher_DetectingReadings MSG_NORMAL
    applymovement Sakura m_WalkDown
    applymovement PLAYER m_LookDown
    msgbox gText_UltraEpisode_PostCosmog_Sakura_ConfirmingReadings MSG_NORMAL
    msgbox gText_UltraEpisode_PostCosmog_PCResearcher_ConfirmedReadings MSG_NORMAL
    msgbox gText_UltraEpisode_PostCosmog_Sakura_CongratulatingResearcher MSG_NORMAL
    fadedefaultbgm
    applymovement Sakura m_WalkUp
    waitmovement Sakura
    applymovement PLAYER m_LookRight
    applymovement Sakura m_LookLeft
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_PostCosmog_ReturnToSakura
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_UltraEpisode_PostCosmog_Sakura_CommentingOnObligations MSG_NORMAL
    msgbox gText_UltraEpisode_PostCosmog_Sakura_RequestingWormholeClosure MSG_YESNO
    compare LASTRESULT NO
    if equal _goto UltraEpisode_PostCosmog_AskingToCloseWormholes
    goto UltraEpisode_PostCosmog_NextSteps

UltraEpisodeCosmogNotCaught:
    playse 0x1A @ Error
    msgbox gText_UltraEpisode_PostCosmog_Sakura_DidNotCatchCosmog MSG_NORMAL
    applymovement Sakura m_SakuraReturnsToMachineAfterCosmog
    waitmovement Sakura
    applymovement PLAYER m_LookDown
    subvar 0x4073 0x1 @ Roll the Ultra Episode back to when Cosmog is available
    clearflag 0x6E @ Show Challengable Cosmog at Altar of Eclipse
    end

UltraEpisode_PostCosmog_AskingToCloseWormholes:
    msgbox gText_UltraEpisode_PostCosmog_Sakura_RequestingWormholeClosure_PlayerTryingToRefuse MSG_YESNO
    compare LASTRESULT YES
    if equal _goto UltraEpisode_PostCosmog_NextSteps
    goto UltraEpisode_PostCosmog_AskingToCloseWormholes

UltraEpisode_PostCosmog_NextSteps:
    msgbox gText_UltraEpisode_PostCosmog_Sakura_NextSteps1 MSG_NORMAL
    msgbox gText_UltraEpisode_PostCosmog_Sakura_NextSteps2 MSG_NORMAL
    applymovement Sakura m_LookDown
    applymovement PLAYER m_LookDown
    movesprite2 0x3 0x14 0x3 @ Move researcher in front of Type:Null ball
    setobjectmovementtype 0x3 look_down
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_PostCosmog_MoveToResearcher
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_UltraEpisode_PostCosmog_Sakura_NextSteps3 MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_PostCosmog_MoveToTypeNull
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_UltraEpisode_PostCosmog_Sakura_NextSteps4 MSG_NORMAL
    applymovement PLAYER m_LookRight
    movesprite2 Sakura 0x2 0x6 @ For after the camera moves across the lab
    special CAMERA_START
    applymovement CAMERA m_UltraEpisodeCamera_PostCosmog_ReturnToSakuraFromNull
    waitmovement CAMERA
    special CAMERA_END
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_UltraEpisode_PostCosmog_Sakura_NextSteps5 MSG_NORMAL
    applymovement Sakura m_SakuraReturnsToMachineAfterCosmog
    waitmovement Sakura
    applymovement PLAYER m_LookDown
    movesprite2 Sakura 0x3 0x5 @ Sakura's usual position
    clearflag 0x063 @ Nihilego Ultra Wormhole
    clearflag 0x064 @ Buzzwole Ultra Wormhole
    clearflag 0x065 @ Pheromosa Ultra Wormhole
    clearflag 0x066 @ Xurkitree Ultra Wormhole
    clearflag 0x067 @ Celesteela Ultra Wormhole
    clearflag 0x068 @ Kartana Ultra Wormhole
    clearflag 0x069 @ Guzzlord Ultra Wormhole
    clearflag 0x06A @ Stakataka Ultra Wormhole
    clearflag 0x06D @ Blacephalon Ultra Wormhole
    addvar 0x4073 0x1 @ Onto the next part of the Ultra Episode: hunting down ultra wormholes
    end

LevelScript_InterdimensionalResearchFacility_UltraEpisode_PostUltraNecrozma:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xC @ Player is at the door, after losing to catchable Necrozma
    applymovement Sakura m_LookDown
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_WelcomeBack MSG_NORMAL
    if equal _call UltraEpisode_PostNecrozma_PlayerCalledToSakuraFromDoor
    if lessthan _call UltraEpisode_PostNecrozma_PlayerCalledToSakuraFromMachine
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_ExplainingResearcherSupport MSG_NORMAL
    compare 0x40A7 10
    if lessthan _call UltraEpisode_PostNecrozma_UltraWormholesRemain
    checkflag 0x28D @ Necrozma caught
    if NOT_SET _call UltraEpisode_PostNecrozma_NecrozmaNotCaught
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_ExplainingTravelToUltraSpace MSG_NORMAL
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_Farewell MSG_NORMAL
    applymovement Sakura m_LookLeft
    addvar 0x4073 0x1 @ Now at 12, end of Ultra Episode
    end

UltraEpisode_PostNecrozma_PlayerCalledToSakuraFromDoor:
    applymovement PLAYER m_UltraEpisode_PLayerWalksToSakuraFromDoor
    waitmovement PLAYER
    applymovement Sakura m_LookDown
    return

UltraEpisode_PostNecrozma_PlayerCalledToSakuraFromMachine:
    applymovement PLAYER m_UltraEpisode_PLayerWalksToSakuraFromMachine
    waitmovement PLAYER
    return

UltraEpisode_PostNecrozma_UltraWormholesRemain:
    setvar 0x4000 10
    copyvar 0x4001 0x40A7
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3F @ Subtract
    compare 0x4000 0
    buffernumber 0x0 0x4000
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_UltraWormholesRemain MSG_NORMAL
    return

UltraEpisode_PostNecrozma_NecrozmaNotCaught:
    msgbox gText_UltraEpisode_PostNecrozma_Sakura_NecrozmaUncaught MSG_NORMAL
    return

.global EventScript_DaimynCityFacilities_PCResearcher
EventScript_DaimynCityFacilities_PCResearcher:
    lock
    faceplayer
    compare 0x4073 2
    if equal _goto PCResearcher_UltraEpisodeStarted
    compare 0x4073 5
    if greaterorequal _goto PCResearcher_UltraWormholeHunt
    npcchatwithmovement gText_DaimynCityFacilities_IRF_PCResearcher m_LookUp
    end

PCResearcher_UltraEpisodeStarted:
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_BeastBallSales MSG_NORMAL
    pokemart BeastBallShop
    goto PCResearcher_Conclusion

PCResearcher_UltraWormholeHunt:
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_WelcomingPlayer MSG_NORMAL
    @ Intentional fallthrough
PCResearcher_UltraWormholeHunt_PromptForAssistance:
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormholeHunt_ChoicePrompt MSG_KEEPOPEN
    multichoiceoption gText_DaimynCityFacilities_IRF_PCResearcher_BuyBeastBallsChoice 0
	multichoiceoption gText_DaimynCityFacilities_IRF_PCResearcher_TrackUltraWormholesChoice 1
	multichoiceoption gText_End 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, BuyBeastBalls _goto
	case 1, TrackUltraWormholes _goto
	@ End ignored, to allow fallthrough to conclusion
    goto PCResearcher_Conclusion

PCResearcher_Conclusion:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_PCResearcher_ConversationConcluded m_LookUp
    end

BuyBeastBalls:
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_BuyingBeastBallsAfterIntroduction MSG_NORMAL
    pokemart BeastBallShop
    goto PCResearcher_UltraWormholeHunt_PromptForAssistance

TrackUltraWormholes:
    compare 0x40A7 10
    if equal _goto AllUltraWormholesClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_ChooseUltraWormholePrompt MSG_KEEPOPEN
    setvar 0x8000 0x13 @ Ultra Wormholes
    setvar 0x8001 0x8 @ Show 8 at a time
    setvar 0x8004 0x0
    special 0x158
    waitstate
    copyvar 0x4000 LASTRESULT
    switch 0x4000
    case 0, UltraWormholeCheck_Nihilego _call
    case 1, UltraWormholeCheck_Buzzwole _call
    case 2, UltraWormholeCheck_Pheromosa _call
    case 3, UltraWormholeCheck_Xurkitree _call
    case 4, UltraWormholeCheck_Celesteela _call
    case 5, UltraWormholeCheck_Kartana _call
    case 6, UltraWormholeCheck_Guzzlord _call
    case 7, UltraWormholeCheck_Stakataka _call
    case 8, UltraWormholeCheck_Blacephalon _call
    case 9, PCResearcher_UltraWormholeHunt_PromptForAssistance _goto @ End
    case 0x7F, PCResearcher_UltraWormholeHunt_PromptForAssistance _goto @ Cancelled
    goto TrackUltraWormholes

AllUltraWormholesClosed:
    fanfare 0x10C @ Big Celebration
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_AllUltraWormholesClosed MSG_KEEPOPEN
    waitfanfare
    goto PCResearcher_UltraWormholeHunt_PromptForAssistance

UltraWormholeClosed:
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormholeClosed MSG_NORMAL
    goto TrackUltraWormholes    

UltraWormholeCheck_Nihilego:
    checkflag 0x63
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Nihilego MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Buzzwole:
    checkflag 0x64
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Buzzwole MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Pheromosa:
    checkflag 0x65
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Pheromosa MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Xurkitree:
    checkflag 0x66
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Xurkitree MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Celesteela:
    checkflag 0x67
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Celesteela MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Kartana:
    checkflag 0x68
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Kartana MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Guzzlord:
    checkflag 0x69
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Guzzlord MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Stakataka:
    checkflag 0x6A
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Stakataka MSG_NORMAL
    goto TrackUltraWormholes

UltraWormholeCheck_Blacephalon:
    checkflag 0x6D
    if SET _goto UltraWormholeClosed
    msgbox gText_DaimynCityFacilities_IRF_PCResearcher_UltraWormhole_Blacephalon MSG_NORMAL
    goto TrackUltraWormholes

.align 1
BeastBallShop:
    .hword ITEM_BEAST_BALL
    .hword ITEM_NONE 

.global EventScript_DaimynCityFacilities_MachineryResearcher
EventScript_DaimynCityFacilities_MachineryResearcher:
    checkflag 0x28D @ Necrozma caught
    if equal _goto MachineryResearcher_PostNecrozma
    checkflag 0x289 @ Ultra Necrozma defeated
    if equal _goto MachineryResearcher_PostNecrozma_NotCaught
    npcchatwithmovement gText_DaimynCityFacilities_IRF_MachineryResearcher m_LookUp
    end

MachineryResearcher_PostNecrozma:
    checkflag 0x28F @ Necrozma items given
    if NOT_SET _call GiveNecrozmaItems
    npcchatwithmovement gText_DaimynCityFacilities_IRF_MachineryResearcher_PostNecrozma m_LookUp
    end

GiveNecrozmaItems:
    lock
    faceplayer
    msgbox gText_DaimynCityFacilities_IRF_MachineryResearcher_CongratulatingPlayer MSG_NORMAL
    additem ITEM_N_SOLARIZER 0x1
    additem ITEM_N_LUNARIZER 0x1
    fanfare 0x13E
    msgbox gText_DaimynCityFacilities_IRF_MachineryResearcher_ObtainedNecrozmaFusionItems MSG_KEEPOPEN
    waitfanfare
    msgbox gText_DaimynCityFacilities_IRF_MachineryResearcher_ExplainNecrozmaFusionItems MSG_NORMAL
    setflag 0x28F @ Necrozma items given
    return

MachineryResearcher_PostNecrozma_NotCaught:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_MachineryResearcher_PostNecrozma_NotCaught m_LookUp
    end

.global EventScript_DaimynCityFacilities_TypeNullResearcher
EventScript_DaimynCityFacilities_TypeNullResearcher:
    compare 0x4073 5
    if equal _goto GiveTypeNull
    setvar LASTRESULT SPECIES_SILVALLY
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if equal _goto PlayerEvolvedSilvally
    compare 0x4073 6
    if greaterorequal _goto WishingTypeNullTheBest
    npcchat gText_DaimynCityFacilities_IRF_TypeNullResearcher
    end

GiveTypeNull:
    lock
    faceplayer
    msgbox gText_UltraEpisode_TypeNullResearcher_RequestPlayersSupport MSG_YESNO
    compare LASTRESULT NO
    if equal _goto WillNotTakeCareOfTypeNull
    msgbox gText_UltraEpisode_TypeNullResearcher_RequestPlayerSupport_PlayerSaidYes MSG_NORMAL
    countpokemon
    compare LASTRESULT 6
    if equal _goto NotEnoughRoomForTypeNull
    applymovement LASTTALKED m_LookUp
    pause DELAY_HALFSECOND
    hidesprite 6
    setflag 0x78 @ Hide Type: Null ball
    pause DELAY_HALFSECOND
    faceplayer
    fanfare 0x101
    addvar 0x4073 1 @ Now at 6
    msgbox gText_UltraEpisode_TypeNullResearcher_RememberPromise MSG_NORMAL
    msgbox gText_UltraEpisode_TypeNullResearcher_ReceivedTypeNull MSG_KEEPOPEN
    waitfanfare
    setvar 0x8000 MOVE_AERIALACE
    setvar 0x8001 MOVE_XSCISSOR
    setvar 0x8002 MOVE_IRONHEAD
    setvar 0x8003 MOVE_TRIATTACK
    setvar 0x8004 2 @ Ingame gift 2, Type: Null
    setvar 0x8005 75 @ Level 75
    callasm CreateInGameGiftPokemon
    npcchatwithmovement gText_UltraEpisode_TypeNullResearcher_TakeCare m_LookDown
    end    

WillNotTakeCareOfTypeNull:
    npcchatwithmovement gText_UltraEpisode_TypeNullResearcher_RequestPlayerSupport_PlayerSaidNo m_LookDown
    end

NotEnoughRoomForTypeNull:
    npcchatwithmovement gText_UltraEpisode_TypeNullResearcher_NoRoomForTypeNull m_LookDown
    end

WishingTypeNullTheBest:
    npcchat gText_UltraEpisode_TypeNullResearcher_TakeCare
    end

PlayerEvolvedSilvally:
    checkflag 0x28E @ Silvally memory items given
    if NOT_SET _call GiveMemoryItems
    npcchat gText_UltraEpisode_TypeNullResearcher_TakeCareOfSilvally
    end

GiveMemoryItems:
    lock
    faceplayer
    applymovement LASTTALKED m_Surprise
    playse 0x15 @ Exclaim
    npcchat gText_UltraEpisode_TypeNullResearcher_RecognizeSilvally
    additem ITEM_FIGHTING_MEMORY 0x1
    additem ITEM_FLYING_MEMORY 0x1
    additem ITEM_POISON_MEMORY 0x1
    additem ITEM_GROUND_MEMORY 0x1
    additem ITEM_ROCK_MEMORY 0x1
    additem ITEM_BUG_MEMORY 0x1
    additem ITEM_GHOST_MEMORY 0x1
    additem ITEM_STEEL_MEMORY 0x1
    additem ITEM_FIRE_MEMORY 0x1
    additem ITEM_WATER_MEMORY 0x1
    additem ITEM_GRASS_MEMORY 0x1
    additem ITEM_ELECTRIC_MEMORY 0x1
    additem ITEM_PSYCHIC_MEMORY 0x1
    additem ITEM_ICE_MEMORY 0x1
    additem ITEM_DRAGON_MEMORY 0x1
    additem ITEM_DARK_MEMORY 0x1
    additem ITEM_FAIRY_MEMORY 0x1
    setflag 0x28E @ Silvally memory items given
    fanfare 0x13E
    lock @ Re-lock so he doesn't start wandering
    msgbox gText_UltraEpisode_TypeNullResearcher_ObtainedMemories MSG_KEEPOPEN
    waitfanfare
    msgbox gText_UltraEpisode_TypeNullResearcher_MemoryDiscsExplained MSG_NORMAL
    lock @ Re-lock so he doesn't start wandering
    msgbox gText_UltraEpisode_TypeNullResearcher_GivenSilvally MSG_NORMAL
    fanfare 0x13E
    lock @ Re-lock so he doesn't start wandering
    msgbox gText_UltraEpisode_TypeNullResearcher_ObtainedSilvally MSG_KEEPOPEN
    waitfanfare
    lock @ Re-lock so he doesn't start wandering
    msgbox gText_UltraEpisode_TypeNullResearcher_SilvallyCanBeNicknamed MSG_NORMAL
    callasm SetSivallyAsPlayers
    return

.global EventScript_DaimynCityFacilities_TableBottomRightResearcher
EventScript_DaimynCityFacilities_TableBottomRightResearcher:
    checkflag 0x289 @ Ultra Necrozma defeated
    if SET _goto EventScript_DaimynCityFacilities_TableBottomRightResearcher_PostNecrozma
    npcchatwithmovement gText_DaimynCityFacilities_IRF_TableBottomRightResearcher m_LookUp
    end

EventScript_DaimynCityFacilities_TableBottomRightResearcher_PostNecrozma:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_TableBottomRightResearcher_PostNecrozma m_LookUp
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
    lock
    faceplayer
    compare 0x4073 0x6
    if lessorequal _goto Sakura_UltraEpisode_UltraBeastHunt
    if greaterthan _goto Sakura_UltraEpisode_PromptForDiasOfLight
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

Sakura_UltraEpisode_UltraBeastHunt:
    msgbox gText_UltraEpisode_UltraBeastHunt_Sakura_PromptForDestination MSG_KEEPOPEN
    multichoiceoption gText_UltraEpisode_Sakura_GoToEclipseVillage 0
	multichoiceoption gText_UltraEpisode_Sakura_TrackTheDistrubances 1
	multichoiceoption gText_UltraEpisode_Sakura_Nothing 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, GoToEclipseVillage _goto
	case 1, TrackDisturbances _goto
    @ Nothing and cancel ignored, fall through to below
    npcchatwithmovement gText_UltraEpisode_UltraBeastHunt_Sakura_ChoseNothing m_LookLeft
    end

TrackDisturbances:
    msgbox gText_UltraEpisode_UltraBeastHunt_Sakura_RequirementsToTrackDisturbance MSG_NORMAL
    compare 0x40A7 5
    if lessthan _goto Sakura_UltraEpisode_UltraWormholeRequirement
    msgbox gText_UltraEpisode_PostUltraWormholes_Sakura_UltraBeastCount_Sufficient MSG_NORMAL
    goto Sakura_UltraEpisode_SolgaleoOrLunalaRequirement

Sakura_UltraEpisode_UltraWormholeRequirement:
    buffernumber 0x0 0x40A7 @ Number of beasts captured
    npcchatwithmovement gText_UltraEpisode_UltraBeastHunt_Sakura_UltraBeastCount_Requirement m_LookLeft
    end

Sakura_UltraEpisode_SolgaleoOrLunalaRequirement:
    setvar 0x8004 SPECIES_SOLGALEO
    callasm CheckSpeciesInParty
    compare LASTRESULT TRUE
    if equal _goto SolgaleoCaught
    setvar 0x8004 SPECIES_LUNALA
    callasm CheckSpeciesInParty
    compare LASTRESULT TRUE
    if equal _goto LunalaCaught
    npcchatwithmovement gText_UltraEpisode_PostUltraWormholes_Sakura_NoSolgaleoOrLunala m_LookLeft
    end

SolgaleoCaught:
    bufferstring 0x0 gText_Common_Solgaleo
    goto Sakura_PromptForUltraEpisodeConclusion

LunalaCaught:
    bufferstring 0x0 gText_Common_Lunala
    goto Sakura_PromptForUltraEpisodeConclusion

Sakura_PromptForUltraEpisodeConclusion:
    msgbox gText_UltraEpisode_PostUltraWormholes_Sakura_HasCaughtSolgaleoOrLunala MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_UltraEpisode_PostUltraWormholes_Sakura_StudyingSolgaleoOrLunala MSG_NORMAL
    fadescreen FADEIN_BLACK
    npcchatwithmovement gText_UltraEpisode_PostUltraWormholes_Sakura_FoundNecrozma m_LookLeft
    addvar 0x4073 0x1 @ Ultra Episode moving to final phase
    end

Sakura_UltraEpisode_PromptForDiasOfLight:
    msgbox gText_UltraEpisode_UltraBeastHunt_Sakura_PromptForDestination MSG_KEEPOPEN
    multichoiceoption gText_UltraEpisode_Sakura_GoToEclipseVillage 0
	multichoiceoption gText_UltraEpisode_Sakura_GoToDiasOfLight 1
	multichoiceoption gText_UltraEpisode_Sakura_Nothing 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, GoToEclipseVillage _goto
	case 1, GoToDiasOfLight _goto
    @ Nothing and cancel ignored, fall through to below
    npcchatwithmovement gText_UltraEpisode_UltraBeastHunt_Sakura_ChoseNothing m_LookLeft
    end

GoToDiasOfLight:
    msgbox gText_UltraEpisode_Sakura_GoingToDiasOfLight_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToGoToDiasOfLight
    checkflag 0x289 @ Ultra Necrozma defeated
    if NOT_SET _call PreDiasOfLightCheck
    msgbox gText_UltraEpisode_Sakura_GoingToDiasOfLight_ChoseYes MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x5 @ Beside
    if lessthan _call PlayerWalksToMachineFromAbove
    if equal _call PlayerWalksToMachineFromRight
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromBelow
    waitmovement PLAYER
    applymovement Sakura m_SakuraJoinsPlayerAtMachine
    waitmovement ALLEVENTS
    msgbox gText_UltraEpisode_Sakura_GoingToDiasOfLight MSG_NORMAL
    msgbox gText_UltraEpisode_Researcher_GoingToDiasOfLight MSG_NORMAL
    call UltraSpaceWarpEffect_WithSakura
    warpmuted 2 40 0xFF 0xF 0x2A
    end

ChoseNotToGoToDiasOfLight:
    npcchatwithmovement gText_UltraEpisode_Sakura_GoingToDiasOfLight_ChoseNo m_LookLeft
    end

PreDiasOfLightCheck:
    callasm CheckBeastKillerInParty
    compare LASTRESULT 0
    if equal _goto NoBeastKiller
    return

NoBeastKiller:
    npcchatwithmovement gText_UltraEpisode_Sakura_GoingToDiasOfLight_NoBeastKiller m_LookLeft
    end

UltraSpaceWarpEffect_WithSakura:
    playse 0x49 @ Escalator
    waitse
    pause DELAY_1SECOND
    playse 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement PLAYER m_HideSprite
    applymovement Sakura m_HideSprite
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    return

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
    goto GoToEclipseVillage

ChoseNotToGoToUltraSpace:
    npcchatwithmovement gText_DaimynCityFacilities_IRF_Sakura_PlayerChoseNotToTravelToUltraSpace m_LookLeft
    end

PlayerWalksToMachineFromAbove:
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromAbove
    waitmovement PLAYER
    call PlayerWalksToMachineFromRight
    return

PlayerWalksToMachineFromRight:
    applymovement PLAYER m_PlayerWalksToUltraSpaceMachineFromRight
    waitmovement PLAYER
    return

GoToEclipseVillage:
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
    warpmuted 2 32 0xFF 0xB 0x9
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
m_PlayerWalksToUltraSpaceMachineFromAbove: .byte walk_right, walk_down, end_m
m_PlayerWalksToUltraSpaceMachineFromRight: .byte walk_down, walk_left, end_m
m_PlayerWalksToUltraSpaceMachineFromBelow: .byte walk_left, walk_left, look_down, end_m
m_SakuraPacesLeft: .byte walk_left_slow, walk_left_slow, look_left, end_m
m_SakuraPacesRight: .byte walk_right_slow, walk_right_slow, look_right, end_m
m_SakuraApproachesPlayer: .byte walk_down, walk_down, end_m
m_UltraEpisodeCamera_MoveToResearcher: .byte run_up, run_up, run_left, run_left, run_left, run_left, run_left, end_m 
m_UltraEpisodeCamera_MoveToPlayer: .byte run_right, run_right, run_right, run_right, run_right, run_down, run_down, end_m
m_SakuraReturnToMachine: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, look_left, end_m
m_SakuraWelcomesPlayerBackAfterCosmog: .byte walk_down, walk_left, end_m
m_SakuraReturnsToMachineAfterCosmog: .byte walk_right, walk_up, look_left, end_m
m_UltraEpisodeCamera_PostCosmog_MoveToResearcher: .byte run_down, run_down, end_m
m_UltraEpisodeCamera_PostCosmog_ReturnToSakura: .byte run_up, run_up, end_m
m_UltraEpisodeCamera_PostCosmog_MoveToTypeNull: .byte run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_up, run_up, run_up, run_up, run_up, end_m
m_UltraEpisodeCamera_PostCosmog_ReturnToSakuraFromNull: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_down, run_down, run_down, end_m
m_SakuraJoinsPlayerAtMachine: .byte walk_down, walk_left, look_down, end_m
m_UltraEpisode_PLayerWalksToSakuraFromDoor: .byte walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, look_up, end_m
m_UltraEpisode_PLayerWalksToSakuraFromMachine: .byte walk_right, walk_right, look_up, end_m
