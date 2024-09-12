.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Abby, 0x7
.equ Rival, 0x8

@ Overworld
.global MapScript_BruccieVillage
MapScript_BruccieVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_BruccieVillage_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_BruccieVillage_FlightSpot:
    setworldmapflag 0x897 @ Visited Bruccie Village
    end

.global EventScript_BruccieVillage_Hiker
EventScript_BruccieVillage_Hiker:
    npcchat gText_BruccieVillage_Hiker
    end

.global EventScript_BruccieVillage_Skier
EventScript_BruccieVillage_Skier:
    npcchat gText_BruccieVillage_Skier
    end

.global EventScript_BruccieVillage_Kid
EventScript_BruccieVillage_Kid:
    npcchat gText_BruccieVillage_Kid
    end

.global EventScript_BruccieVillage_OldMan
EventScript_BruccieVillage_OldMan:
    checkflag 0xE18 @ Wingull event done
    if SET _goto OldMan_DailyEventDone
    faceplayer
    msgbox gText_BruccieVillage_OldMan_WingullEventStarting MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    applymovement 0x6 m_WalkFacingRight
    pause DELAY_HALFSECOND
    msgbox gText_BruccieVillage_OldMan_RequestsTreasure MSG_NORMAL
    cry SPECIES_WINGULL 0x0
    msgbox gText_BruccieVillage_Wingull MSG_NORMAL
    faceplayer
    msgbox gText_BruccieVillage_OldMan_GivesTreasure MSG_NORMAL
    goto GiveWingullGift

GiveWingullGift:
    random 100
    compare LASTRESULT 2
    if lessthan _goto GiveBottleCapGift
    compare LASTRESULT 5
    if lessthan _goto GiveRareCandyGift
    compare LASTRESULT 10
    if lessthan _goto GiveUltraBallGift
    compare LASTRESULT 20
    if lessthan _goto GivePokeChipGift
    compare LASTRESULT 35
    if lessthan _goto GiveSuperRepelGift
    compare LASTRESULT 50
    if lessthan _goto GivePearlGift
    compare LASTRESULT 70
    if lessthan _goto GiveGreatBallGift
    goto GiveSuperPotionGift

GiveBottleCapGift:
    obtainitem ITEM_BOTTLE_CAP 0x1
    goto WingullGiftComplete

GiveRareCandyGift:
    obtainitem ITEM_RARE_CANDY 0x1
    goto WingullGiftComplete

GiveUltraBallGift:
    obtainitem ITEM_ULTRA_BALL 0x1
    goto WingullGiftComplete

GivePokeChipGift:
    obtainitem ITEM_POKE_CHIP 0x1
    goto WingullGiftComplete

GiveSuperRepelGift:
    obtainitem ITEM_SUPER_REPEL 0x1
    goto WingullGiftComplete

GivePearlGift:
    obtainitem ITEM_PEARL 0x1
    goto WingullGiftComplete

GiveGreatBallGift:
    obtainitem ITEM_GREAT_BALL 0x1
    goto WingullGiftComplete

GiveSuperPotionGift:
    obtainitem ITEM_SUPER_POTION 0x1
    goto WingullGiftComplete

WingullGiftComplete:
    applymovement 0x6 m_WingullFliesAway
    pause DELAY_HALFSECOND
    applymovement LASTTALKED m_LookLeft
    waitmovement 0x6
    hidesprite 0x6
    pause DELAY_1SECOND
    setflag 0xE18 @ Wingull event done
    goto OldMan_DailyEventDone

OldMan_DailyEventDone:
    npcchatwithmovement gText_BruccieVillage_OldMan_WingullEventDone m_LookUp
    end

.global EventScript_BruccieVillage_Wingull
EventScript_BruccieVillage_Wingull:
    cry SPECIES_WINGULL 0x0
    npcchatwithmovement gText_BruccieVillage_Wingull m_WalkFacingUp
    end

.global EventScript_BruccieVillage_Abby
EventScript_BruccieVillage_Abby:
    faceplayer
    msgbox gText_BruccieVillage_Abby_Question MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotHereForTheGym
    call MovePlayerBeforeAbby
    callasm CountBadges
    compare LASTRESULT 0x5
    if lessthan _goto NotReadyForGym
    msgbox gText_BruccieVillage_Abby_EnoughBadges MSG_NORMAL
    playbgm 0x195 @ Rival's theme
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    applymovement Abby m_Surprise
    msgbox gText_BruccieVillage_Abby_RivalInterrupt MSG_NORMAL
    showsprite Rival
    applymovement Rival m_RivalWalksToPlayer
    pause DELAY_1SECOND
    applymovement PLAYER m_LookRight
    applymovement Abby m_LookRight
    waitmovement Rival
    msgbox gText_BruccieVillage_Abby_RivalChallengesPlayer MSG_NORMAL
    applymovement Abby m_WalkRight
    waitmovement Abby
    applymovement Abby m_LookDown
    applymovement Rival m_LookUp
    msgbox gText_BruccieVillage_Abby_AbbyAcknowledgesRival MSG_NORMAL
    msgbox gText_BruccieVillage_Abby_RivalApologizesToAbby MSG_NORMAL
    msgbox gText_BruccieVillage_Abby_AbbyOverseesBattle MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_BruccieVillage_Abby_RivalIssuesChallenge MSG_NORMAL
    applymovement Abby m_WalkLeft
    waitmovement Abby
    applymovement Abby m_LookDown
    applymovement Rival m_RivalTakesPosition
    applymovement PLAYER m_PlayerTakesPosition
    waitmovement PLAYER
    msgbox gText_BruccieVillage_Abby_RivalPreBattle MSG_NORMAL
    call SetupMugshotRival
    copyvar 0x4001 0x408E
    setvar 0x4000 266 @ trainer ID, which is 266 + 0-7 depending on value in 0x408E (Water starter generation)
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_BruccieVillage_Abby_RivalLoses
    msgbox gText_BruccieVillage_Abby_RivalCommentsOnLoss MSG_NORMAL
    applymovement Rival m_RivalWalksToPlayerAfterBattle
    waitmovement Rival
    msgbox gText_BruccieVillage_Abby_RivalLeaves MSG_NORMAL
    applymovement Rival m_RivalLeavesAfterBattle
    pause DELAY_1SECOND
    applymovement Abby m_LookRight
    waitmovement Rival
    hidesprite Rival
    applymovement PLAYER m_PlayerReturnsToAbby
    waitmovement PLAYER
    msgbox gText_BruccieVillage_Abby_CommentsOnRival MSG_NORMAL
    applymovement Abby m_LookDown
    msgbox gText_BruccieVillage_Abby_AcceptsPlayersChallenge MSG_NORMAL
    applymovement Abby m_LookUp
    opendoor 0xB 0xE
    waitdooranim
    pause DELAY_HALFSECOND
    applymovement Abby m_WalkUp
    waitmovement Abby
    hidesprite Abby
    closedoor 0xB 0xE
    waitdooranim
    setflag 0x47 @ Abby hidden from overworld
    fadedefaultbgm
    end

NotHereForTheGym:
    npcchatwithmovement gText_BruccieVillage_Abby_SaidNo m_LookDown
    end

MovePlayerBeforeAbby:
    special 0xAF @ Dismount bike if on it
    compareplayerfacing INTERNAL_RIGHT
    if equal _call MoveFromLeft
    compareplayerfacing INTERNAL_LEFT
    if equal _call MoveFromRight
    applymovement PLAYER m_LookUp
    applymovement Abby m_LookDown
    return

MoveFromLeft:
    msgbox gText_BruccieVillage_Abby_MoveToFront MSG_NORMAL
    call PlayerWalkDown_Return
    call PlayerWalkRight_Return
    return

MoveFromRight:
    msgbox gText_BruccieVillage_Abby_MoveToFront MSG_NORMAL
    call PlayerWalkDown_Return
    call PlayerWalkLeft_Return
    return

NotReadyForGym:
    msgbox gText_BruccieVillage_Abby_NotEnoughBadges MSG_NORMAL
    end

.global EventScript_BruccieVillage_AbbyCommenter
EventScript_BruccieVillage_AbbyCommenter:
    npcchatwithmovement gText_BruccieVillage_AbbyCommenter m_LookRight
    end

.global SignScript_BruccieVillage_TownPlacard
SignScript_BruccieVillage_TownPlacard:
    msgbox gText_BruccieVillage_TownPlacardSign MSG_SIGN
    end

.global SignScript_BruccieVillage_GymSign
SignScript_BruccieVillage_GymSign:
    msgbox gText_BruccieVillage_GymSign MSG_SIGN
    end

m_WingullFliesAway: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
m_RivalWalksToPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_RivalTakesPosition: .byte walk_down, walk_right, look_left, end_m
m_PlayerTakesPosition: .byte walk_down, walk_left, walk_left, look_right, end_m
m_RivalWalksToPlayerAfterBattle: .byte walk_left, walk_left, walk_left, end_m
m_RivalLeavesAfterBattle: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_PlayerReturnsToAbby: .byte walk_right, walk_right, walk_up, end_m

@ Facilities
.global MapScript_BruccieVillageFacilities_PokemonCenter
MapScript_BruccieVillageFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_BruccieVillageFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_BruccieVillageFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x08
    call ResetUteyaVillageGymFlagsOnWhiteout
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

@ NPC Houses
.global EventScript_BruccieVillageNPCHouses_MoveTutor
EventScript_BruccieVillageNPCHouses_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BruccieVillageNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_BruccieVillageNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Bruccie
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookUp
    end

TutoringComplete:
    msgbox gText_BruccieVillageNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_BruccieVillageNPCHouses_TutoringRejected m_LookUp
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_BruccieVillageNPCHouses_NotEnoughPokeChips m_LookUp
    goto End

.global EventScript_BruccieVillageNPCHouses_PokeballSwapper
EventScript_BruccieVillageNPCHouses_PokeballSwapper:
    faceplayer
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Intro MSG_NORMAL
    compare 0x409A 5
    if lessthan _call NotSkilled
    if greaterorequal _call Skilled
    @ Get pokechip count and confirm
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChangeBall
    compare 0x8005 0x2
    if lessthan _goto NotEnoughPokeChipsForBallSwap
    goto ChoosePokemon

ChoosePokemon:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_AskToChoosePokemon MSG_NORMAL
    special 0x9F
    waitstate
    copyvar 0x4001 0x8004
    compare 0x4001 0x6 @ Don't continue if user backed out
    if greaterorequal _goto ChoseNotToChangeBall
    bufferpartypokemon 0x0 0x8004 @ Buffer pokemon nickname
    setvar 0x8003 0x0 @ Read pokeball from party
    special2 LASTRESULT 0x7D @ Check if it's a traded pokemon
    compare LASTRESULT TRUE
    if equal _goto CannotChangeForTradedPokemon
    special2 0x4000 0xB
    addvar 0x4000 0x1 @ Add 1 - This vanilla special reads the ball in a 0 based format instead of 1 based (#0 is None)
    compare 0x4000 ITEM_CHERISH_BALL
    if equal _goto CannotChangeCherishBall
    bufferitem 0x1 0x4000
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokemonChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoosePokemon
    goto ChoosePokeball

ChoosePokeball:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokeballConfirmation MSG_NORMAL
    setvar 0x8000 0x2 @ Choose from Pokeball menu
    fadescreen FADEOUT_BLACK @ Fade screen to circumvent a UI bug when opening the bag
    special 0xB1
    waitstate
    compare CHOSEN_ITEM 0x0
    if equal _goto ChoseNotToChangeBall
    @ Handle same ball chosen
    comparevars 0x4000 CHOSEN_ITEM @ Original ball compared to new
    if equal _goto ChoseSamePokeball
    @ Setup ball swapping special based on selected item
    switch CHOSEN_ITEM
    case ITEM_MASTER_BALL, ChoseMasterBall
    case ITEM_ULTRA_BALL, ChoseUltraBall
    case ITEM_GREAT_BALL, ChoseGreatBall
    case ITEM_POKE_BALL, ChosePokeBall
    case ITEM_SAFARI_BALL, ChoseSafariBall
    case ITEM_NET_BALL, ChoseNetBall
    case ITEM_DIVE_BALL, ChoseDiveBall
    case ITEM_NEST_BALL, ChoseNestBall
    case ITEM_REPEAT_BALL, ChoseRepeatBall
    case ITEM_TIMER_BALL, ChoseTimerBall
    case ITEM_LUXURY_BALL, ChoseLuxuryBall
    case ITEM_PREMIER_BALL, ChosePremierBall
    case ITEM_DUSK_BALL, ChoseDuskBall
    case ITEM_HEAL_BALL, ChoseHealBall
    case ITEM_QUICK_BALL, ChoseQuickBall
    case ITEM_PARK_BALL, ChoseParkBall
    case ITEM_FAST_BALL, ChoseFastBall
    case ITEM_LEVEL_BALL, ChoseLevelBall
    case ITEM_LURE_BALL, ChoseLureBall
    case ITEM_HEAVY_BALL, ChoseHeavyBall
    case ITEM_LOVE_BALL, ChoseLoveBall
    case ITEM_FRIEND_BALL, ChoseFriendBall
    case ITEM_MOON_BALL, ChoseMoonBall
    case ITEM_SPORT_BALL, ChoseSportBall
    case ITEM_BEAST_BALL, ChoseBestBall
    case ITEM_DREAM_BALL, ChoseDreamBall
    @ For all non-pokeball items, as well as Dynamax and Cherish balls, default to not being able to process it
    bufferitem 0x0 CHOSEN_ITEM
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseANonPokeball m_LookLeft
    end

@ These balls come from catching.h's ball types
ChoseMasterBall:
    setvar 0x8005 0x0
    goto BallConfirmation

ChoseUltraBall:
    setvar 0x8005 0x1
    goto BallConfirmation

ChoseGreatBall:
    setvar 0x8005 0x2
    goto BallConfirmation

ChosePokeBall:
    setvar 0x8005 0x3
    goto BallConfirmation

ChoseSafariBall:
    setvar 0x8005 0x4
    goto BallConfirmation

ChoseNetBall:
    setvar 0x8005 0x5
    goto BallConfirmation

ChoseDiveBall:
    setvar 0x8005 0x6
    goto BallConfirmation

ChoseNestBall:
    setvar 0x8005 0x7
    goto BallConfirmation

ChoseRepeatBall:
    setvar 0x8005 0x8
    goto BallConfirmation

ChoseTimerBall:
    setvar 0x8005 0x9
    goto BallConfirmation

ChoseLuxuryBall:
    setvar 0x8005 0xA
    goto BallConfirmation

ChosePremierBall:
    setvar 0x8005 0xB
    goto BallConfirmation

ChoseDuskBall:
    setvar 0x8005 0xC
    goto BallConfirmation

ChoseHealBall:
    setvar 0x8005 0xD
    goto BallConfirmation

ChoseQuickBall:
    setvar 0x8005 0xE
    goto BallConfirmation

ChoseParkBall:
    setvar 0x8005 0x10
    goto BallConfirmation

ChoseFastBall:
    setvar 0x8005 0x11
    goto BallConfirmation

ChoseLevelBall:
    setvar 0x8005 0x12
    goto BallConfirmation

ChoseLureBall:
    setvar 0x8005 0x13
    goto BallConfirmation

ChoseHeavyBall:
    setvar 0x8005 0x14
    goto BallConfirmation

ChoseLoveBall:
    setvar 0x8005 0x15
    goto BallConfirmation

ChoseFriendBall:
    setvar 0x8005 0x16
    goto BallConfirmation

ChoseMoonBall:
    setvar 0x8005 0x17
    goto BallConfirmation

ChoseSportBall:
    setvar 0x8005 0x18
    goto BallConfirmation

ChoseBestBall:
    setvar 0x8005 0x19
    goto BallConfirmation

ChoseDreamBall:
    setvar 0x8005 0x1A
    goto BallConfirmation

BallConfirmation:
    @ Handle confirmation
    bufferpartypokemon 0x0 0x8004 @ Buffer pokemon nickname again; replaced by special 0xB1
    bufferitem 0x2 CHOSEN_ITEM
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_BallSwapConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChangeBall
    goto PerformBallSwap

PerformBallSwap:
    @ Deduct pokechips and process
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_CollectPokechips MSG_NORMAL
    sound 0xF8 @ Money SE
    waitse
    removeitem ITEM_POKE_CHIP 0x2
    removeitem CHOSEN_ITEM 0x1
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_StartingProcess MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Working MSG_NORMAL
    fadescreen FADEIN_BLACK
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_ProcessComplete MSG_KEEPOPEN
    waitfanfare
    @ Change ball
    special 0x14 @ Perform the ball change
    addvar 0x409A 0x1
    @ Give old ball back if skilled enough
    compare 0x409A 5
    if lessthan _call BrokeBall
    if equal _call BecameSkilled
    if greaterorequal _call GiveOldBall
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_Completed m_LookLeft
    end

NotSkilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_NotSkilled MSG_NORMAL
    return

Skilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Skilled MSG_NORMAL
    return

ChoseNotToChangeBall:
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseNotToChangePokeball m_LookLeft
    end

NotEnoughPokeChipsForBallSwap:
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_NotEnoughChips m_LookLeft
    end

CannotChangeForTradedPokemon:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_TradedPokemon MSG_NORMAL
    goto ChoseNotToChangeBall

CannotChangeCherishBall:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokemonInCherishBall MSG_NORMAL
    goto ChoseNotToChangeBall

ChoseSamePokeball:
    bufferitem 0x0 CHOSEN_ITEM
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseSamePokeball MSG_NORMAL
    goto ChoseNotToChangeBall

BrokeBall:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_OldBallBroke MSG_NORMAL
    return

BecameSkilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Improved MSG_NORMAL
    return

GiveOldBall:
    additem 0x4000 0x1
    bufferitem 0x1 0x4000
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_BallReturned MSG_NORMAL
    return

.global EventScript_BruccieVillageNPCHouses_CherishBallGuy
EventScript_BruccieVillageNPCHouses_CherishBallGuy:
    npcchatwithmovement gText_BruccieVillageNPCHouses_CherishBallGuy m_LookLeft
    end

.global EventScript_BruccieVillageNPCHouses_TutorWife
EventScript_BruccieVillageNPCHouses_TutorWife:
    npcchatwithmovement gText_BruccieVillageNPCHouses_TutorWife m_LookLeft
    end

.global EventScript_BruccieVillageNPCHouses_TutorKid
EventScript_BruccieVillageNPCHouses_TutorKid:
    npcchatwithmovement gText_BruccieVillageNPCHouses_TutorKid m_LookUp
    end

@ Gym
.global EventScript_BruccieVillageGym_GymExpert
EventScript_BruccieVillageGym_GymExpert:
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto EventScript_BruccieVillageGym_GymExpertBadgeObtained
    npcchat gText_BruccieVillageGym_ExpertTips
    end

EventScript_BruccieVillageGym_GymExpertBadgeObtained:
    npcchat gText_BruccieVillageGym_ExpertBadgeObtained
    end

.global EventScript_BruccieVillageGym_Mel
EventScript_BruccieVillageGym_Mel:
    trainerbattle0 0x0 274 0x0 gText_BruccieVillageGym_LassMel_Intro gText_BruccieVillageGym_LassMel_Defeat
    msgbox gText_BruccieVillageGym_LassMel_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Owen
EventScript_BruccieVillageGym_Owen:
    trainerbattle0 0x0 275 0x0 gText_BruccieVillageGym_BirdKeeperOwen_Intro gText_BruccieVillageGym_BirdKeeperOwen_Defeat
    msgbox gText_BruccieVillageGym_BirdKeeperOwen_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Tommy
EventScript_BruccieVillageGym_Tommy:
    trainerbattle0 0x0 276 0x0 gText_BruccieVillageGym_EngineerTommy_Intro gText_BruccieVillageGym_EngineerTommy_Defeat
    msgbox gText_BruccieVillageGym_EngineerTommy_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Joel
EventScript_BruccieVillageGym_Joel:
    trainerbattle0 0x0 277 0x0 gText_BruccieVillageGym_HikerJoel_Intro gText_BruccieVillageGym_HikerJoel_Defeat
    msgbox gText_BruccieVillageGym_HikerJoel_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Ellie
EventScript_BruccieVillageGym_Ellie:
    trainerbattle0 0x0 278 0x0 gText_BruccieVillageGym_CrushGirlEllie_Intro gText_BruccieVillageGym_CrushGirlEllie_Defeat
    msgbox gText_BruccieVillageGym_CrushGirlEllie_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Abby
EventScript_BruccieVillageGym_Abby:
    faceplayer
    checkflag 0x825 @ Bruccie Village gym badge
    if SET _goto EventScript_BruccieVillageGym_LeaderAbby_Chat
    msgbox gText_BruccieVillageGym_LeaderAbby_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 279 0x100 gText_BruccieVillageGym_LeaderAbby_Intro gText_BruccieVillageGym_LeaderAbby_Defeat EventScript_BruccieVillageGym_LeaderAbby_Defeated
    end

EventScript_BruccieVillageGym_LeaderAbby_Defeated:
    msgbox gText_BruccieVillageGym_LeaderAbby_BadgeAwarded MSG_NORMAL
    setflag 0x825 @ Bruccie Village gym badge
    fanfare 0x13D @ Gym victory
    msgbox gText_BruccieVillageGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    msgbox gText_BruccieVillageGym_LeaderAbby_BadgeDescription MSG_NORMAL
    msgbox gText_BruccieVillageGym_LeaderAbby_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_BruccieVillageGym_TMReceived
    additem ITEM_TM76 0x1
    giveitemwithfanfare ITEM_TM76 0x1 0x101 @ MUS_FANFA1
    setflag 0x29A @ Received TM 76 from Abby
    setflag 0x4B5 @ Defeated Abby
    setflag 0x25C @ New Pokemart Stock
    msgbox gText_BruccieVillageGym_LeaderAbby_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_BruccieVillageGym_LeaderAbby_Chat:
    npcchat gText_BruccieVillageGym_LeaderAbby_Chat
    end

.global SignScript_BruccieVillageGym_Placard
SignScript_BruccieVillageGym_Placard:
    checkflag 0x25B
    if SET _goto SignScript_BruccieVillageGym_PlacardWithBadgeAfterSurfing
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto SignScript_BruccieVillageGym_PlacardWithBadge
    msgbox gText_BruccieVillageGym_Winners MSG_SIGN
    end

SignScript_BruccieVillageGym_PlacardWithBadgeAfterSurfing:
    msgbox gText_BruccieVillageGym_WinnersWithBadgeAfterSurfing MSG_SIGN
    end

SignScript_BruccieVillageGym_PlacardWithBadge:
    msgbox gText_BruccieVillageGym_WinnersWithBadge MSG_SIGN
    end
