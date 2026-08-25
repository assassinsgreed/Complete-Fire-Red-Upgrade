.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_BattleFrontier
MapScript_BattleFrontier:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_BattleFrontier_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_BattleFrontier_FlightSpot:
    setworldmapflag 0x8B3 @ Visited the Battle Frontier
    end

.global EventScript_BattleFrontier_PokemonCenterResearcher
EventScript_BattleFrontier_PokemonCenterResearcher:
    npcchatwithmovement gText_BattleFrontier_Researcher m_LookDown
    end

.global EventScript_BattleFrontier_PokemonCenterPokeChipBuyer
EventScript_BattleFrontier_PokemonCenterPokeChipBuyer:
    lock
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BattleFrontier_PokeChipBuyer_Prompt MSG_YESNO
    compare LASTRESULT YES
    if notequal _goto PokeChipBuyer_ChoseNo
    compare 0x8005 0
    if equal _goto PokeChipBuyer_HaveZero
    msgbox gText_BattleFrontier_PokeChipBuyer_YesToSell MSG_NORMAL
    special 0xB3 @ Choose number, stored in LASTRESULT
    waitstate
    compare LASTRESULT 0x0
    if equal _goto PokeChipBuyer_ChoseZero
    comparevars LASTRESULT 0x8005
    if greaterthan _goto PokeChipBuyer_ChoseMoreChipsThanHeld
    buffernumber 0x1 LASTRESULT
    copyvar 0x4006 LASTRESULT @ Chips being sold; both sale helpers read this
    callasm StorePokeChipSaleValue @ BUFFER3 = 2000 per chip, buffered as a string since the total passes 0xFFFF
    showmoney 0x0 0x0
    msgbox gText_BattleFrontier_PokeChipBuyer_YesToConfirmChipsChosen MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokeChipBuyer_ChoseNoDuringPayment
    playse 0xF8 @ Money
    callasm PayForPokeChipSale @ Pays out var 0x4006 chips and removes them from the bag
    updatemoney 0x0 0x0
    waitse
    pause DELAY_HALFSECOND
    hidemoney
    npcchatwithmovement gText_BattleFrontier_PokeChipBuyer_SaleCompleted m_LookDown
    end

PokeChipBuyer_HaveZero:
    npcchatwithmovement gText_BattleFrontier_PokeChipBuyer_HaveZeroChips m_LookDown
    release
    end

PokeChipBuyer_ChoseNo:
    npcchatwithmovement gText_BattleFrontier_PokeChipBuyer_No m_LookDown
    release
    end

PokeChipBuyer_ChoseZero:
    npcchatwithmovement gText_BattleFrontier_PokeChipBuyer_ChoseZeroChips m_LookDown
    release
    end

PokeChipBuyer_ChoseMoreChipsThanHeld:
    npcchatwithmovement gText_BattleFrontier_PokeChipBuyer_ChoseMoreChipsThanPlayerHas m_LookDown
    release
    end

PokeChipBuyer_ChoseNoDuringPayment:
    hidemoney
    goto PokeChipBuyer_ChoseNo

.global EventScript_BattleFrontier_PokemonCenterCosplayPikachuLady
EventScript_BattleFrontier_PokemonCenterCosplayPikachuLady:
    lock
    faceplayer
    checkflag 0x29B @ Received Cosplay Pikachu
    if SET _goto CosplayLady_OfferCostumeChange
    msgbox gText_BattleFrontier_CosplayLady_Intro MSG_NORMAL
    showpokepic SPECIES_PIKACHU_POP_STAR
    msgbox gText_BattleFrontier_CosplayLady_OffersPikachu MSG_YESNO
    hidepokepic
    compare LASTRESULT NO
    if equal _goto CosplayLady_DeclinedGift
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto CosplayLady_NoPartyRoom
    msgbox gText_BattleFrontier_CosplayLady_GivesPikachu MSG_NORMAL
    setvar 0x8000 MOVE_THUNDERBOLT
    setvar 0x8001 MOVE_NUZZLE
    setvar 0x8002 MOVE_DRAININGKISS
    setvar 0x8003 MOVE_QUICKATTACK
    setvar 0x8004 0x3 @ Ingame gift 3, Cosplay Pikachu
    setvar 0x8005 50 @ Level 50
    setflag 0x29B @ Received Cosplay Pikachu
    fanfare 0x101
    callasm CreateInGameGiftPokemon
    msgbox gText_BattleFrontier_CosplayLady_PikachuObtained MSG_KEEPOPEN
    waitfanfare
    npcchatwithmovement gText_BattleFrontier_CosplayLady_ExplainsCostumes m_LookLeft
    end

CosplayLady_DeclinedGift:
    npcchatwithmovement gText_BattleFrontier_CosplayLady_DeclinedGift m_LookLeft
    end

CosplayLady_NoPartyRoom:
    npcchatwithmovement gText_BattleFrontier_CosplayLady_NoPartyRoom m_LookLeft
    end

CosplayLady_OfferCostumeChange:
    msgbox gText_BattleFrontier_CosplayLady_CostumePrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto CosplayLady_DeclinedCostume
    msgbox gText_BattleFrontier_CosplayLady_ChoosePikiPrompt MSG_NORMAL
    special 0x9F @ Select a Pokemon and store its position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if the player backed out
    if greaterorequal _goto CosplayLady_DeclinedCostume
    bufferpartypokemon 0x0 0x8004
    callasm StoreIsPartyMonCosplayPikachu
    compare LASTRESULT TRUE
    if notequal _goto CosplayLady_WrongPokemon
    msgbox gText_BattleFrontier_CosplayLady_ChooseCostume MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoiceEveryday 0
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoiceRockStar 1
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoiceBelle 2
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoicePopStar 3
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoicePhD 4
    multichoiceoption gText_BattleFrontier_CosplayLady_ChoiceLibre 5
    multichoiceoption gText_End 6
    multichoice 0x0 0x0 SEVEN_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, SetCosplayPikachuEveryday
    case 1, SetCosplayPikachuRockStar
    case 2, SetCosplayPikachuBelle
    case 3, SetCosplayPikachuPopStar
    case 4, SetCosplayPikachuPhD
    case 5, SetCosplayPikachuLibre
    goto CosplayLady_CostumeCancelled
    end

CosplayLady_DeclinedCostume:
    npcchatwithmovement gText_BattleFrontier_CosplayLady_DeclinedCostume m_LookLeft
    end

CosplayLady_WrongPokemon:
    npcchatwithmovement gText_BattleFrontier_CosplayLady_WrongPokemon m_LookLeft
    end

CosplayLady_CostumeCancelled:
    npcchatwithmovement gText_BattleFrontier_CosplayLady_DeclinedCostume m_LookLeft
    end

SetCosplayPikachuEveryday:
    checksound
    cry SPECIES_PIKACHU_COSPLAY 0x0
    msgbox gText_BattleFrontier_CosplayLady_CostumeRemoved MSG_NORMAL
    setvar 0x8005 SPECIES_PIKACHU_COSPLAY
    goto FinalizeCosplayPikachuFormChange

SetCosplayPikachuRockStar:
    call ChangeCosplayPikachuFormCommon
    setvar 0x8005 SPECIES_PIKACHU_ROCK_STAR
    goto FinalizeCosplayPikachuFormChange

SetCosplayPikachuBelle:
    call ChangeCosplayPikachuFormCommon
    setvar 0x8005 SPECIES_PIKACHU_BELLE
    goto FinalizeCosplayPikachuFormChange

SetCosplayPikachuPopStar:
    call ChangeCosplayPikachuFormCommon
    setvar 0x8005 SPECIES_PIKACHU_POP_STAR
    goto FinalizeCosplayPikachuFormChange

SetCosplayPikachuPhD:
    call ChangeCosplayPikachuFormCommon
    setvar 0x8005 SPECIES_PIKACHU_PHD
    goto FinalizeCosplayPikachuFormChange

SetCosplayPikachuLibre:
    call ChangeCosplayPikachuFormCommon
    setvar 0x8005 SPECIES_PIKACHU_LIBRE
    goto FinalizeCosplayPikachuFormChange

ChangeCosplayPikachuFormCommon:
    checksound
    cry SPECIES_PIKACHU_COSPLAY 0x0
    fanfare 0x101 @ Get Item / Level Up
    msgbox gText_BattleFrontier_CosplayLady_CostumeChanging MSG_NORMAL
    waitfanfare
    return

FinalizeCosplayPikachuFormChange:
    callasm ChangeCosplayPikachuFormInOverworld
    release
    end

.global EventScript_BattleFrontier_PokemonCenterOldMan
EventScript_BattleFrontier_PokemonCenterOldMan:
    npcchatwithmovement gText_BattleFrontier_PokemonCenterOldMan m_LookUp
    end

.global EventScript_BattleFrontier_PokemonCenterDittoTrader
EventScript_BattleFrontier_PokemonCenterDittoTrader:
    lock
    faceplayer
    checkflag 0x29C @ Did the Junichi trade
    if SET _goto Junichi_TradeComplete
    msgbox gText_BattleFrontier_MasudaDittoTrader_Intro MSG_NORMAL
    setvar 0x8000 2 @ Streak at any facility/format required for trade
    callasm StoreHasAchievedFrontierStreak
    compare LASTRESULT TRUE
    if notequal _goto End
    checkflag 0x945 @ Divergent Mode
    if SET _goto Junichi_SetDivergentTrade
    setvar 0x8008 13 @ Set Trade #13 (Junichi the Ditto)
    goto Junichi_Offer

Junichi_SetDivergentTrade:
    setvar 0x8008 26 @ Set Trade #26 (Junichi the Ditto)
    goto Junichi_Offer

Junichi_Offer:
    copyvar 0x8004 0x8008 @ Set expected mon from Junichi's trade (Rotom-Heat)
    special2 LASTRESULT 0xFC @ Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    msgbox gText_BattleFrontier_MasudaDittoTrader_TradeOffer MSG_YESNO
    compare LASTRESULT NO
    if TRUE _goto Junichi_TradeDeclined
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto Junichi_TradeDeclined
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto Junichi_WrongPokemon
    msgbox gText_BattleFrontier_Junichi_InitiatingTrade MSG_NORMAL
    call InitiateTrade
    setflag 0x29C @ Did the Junichi trade
    goto Junichi_TradeComplete

Junichi_TradeDeclined:
    msgbox gText_BattleFrontier_Junichi_Declined MSG_NORMAL
    goto End

Junichi_WrongPokemon:
    msgbox gText_BattleFrontier_Junichi_WrongPokemon MSG_NORMAL
    goto End

Junichi_TradeComplete:
    msgbox gText_BattleFrontier_Junichi_TradeComplete MSG_NORMAL
    goto End

.global EventScript_BattleFrontier_SWTutor1
EventScript_BattleFrontier_SWTutor1:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier1
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SWTutor2
EventScript_BattleFrontier_SWTutor2:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier2
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SWTutor3
EventScript_BattleFrontier_SWTutor3:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier3
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SWTutor4
EventScript_BattleFrontier_SWTutor4:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier4
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

TutorIntro:
    lock
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BattleFrontier_MoveTutor_Confirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_BattleFrontier_MoveTutor_ConfirmationAccepted MSG_KEEPOPEN
    return

TutoringComplete:
    msgbox gText_BattleFrontier_MoveTutor_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_BattleFrontier_MoveTutor_Rejected m_LookDown
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_BattleFrontier_MoveTutor_NotEnoughPokeChips m_LookDown
    goto End

.global EventScript_BattleFrontier_SWBattleItems1
EventScript_BattleFrontier_SWBattleItems1:
    lock
    faceplayer
    msgbox gText_BattleFrontier_BattleItems_Intro MSG_NORMAL
    pokemart BattleItems1
    msgbox gText_BattleFrontier_BattleItems_Outro MSG_NORMAL
    release
    end

.global EventScript_BattleFrontier_SWBattleItems2
EventScript_BattleFrontier_SWBattleItems2:
    lock
    faceplayer
    msgbox gText_BattleFrontier_BattleItems_Intro MSG_NORMAL
    pokemart BattleItems2
    msgbox gText_BattleFrontier_BattleItems_Outro MSG_NORMAL
    release
    end

.global EventScript_BattleFrontier_SWZCrystals
EventScript_BattleFrontier_SWZCrystals:
    lock
    faceplayer
    msgbox gText_BattleFrontier_ZCrystals_Intro MSG_NORMAL
    pokemart ZCrystals
    msgbox gText_BattleFrontier_ZCrystals_Outro MSG_NORMAL
    release
    end

.global EventScript_BattleFrontier_SWSpecialItems
EventScript_BattleFrontier_SWSpecialItems:
    lock
    faceplayer
    msgbox gText_BattleFrontier_SpecialItems_Intro MSG_NORMAL
    pokemart SpecialItems
    msgbox gText_BattleFrontier_SpecialItems_Outro MSG_NORMAL
    release
    end

.align 1
BattleItems1:
    .hword ITEM_LIFE_ORB
    .hword ITEM_FLAME_ORB
    .hword ITEM_TOXIC_ORB
    .hword ITEM_WEAKNESS_POLICY
    .hword ITEM_BLUNDER_POLICY
    .hword ITEM_FOCUS_SASH
    .hword ITEM_LEFTOVERS
    .hword ITEM_HEAVY_DUTY_BOOTS
    .hword ITEM_NONE

.align 1
BattleItems2:
    .hword ITEM_CHOICE_BAND
    .hword ITEM_CHOICE_SPECS
    .hword ITEM_CHOICE_SCARF
    .hword ITEM_PROTECTIVE_PADS
    .hword ITEM_RED_CARD
    .hword ITEM_EJECT_PACK
    .hword ITEM_EVIOLITE
    .hword ITEM_SAFETY_GOGGLES
    .hword ITEM_NONE

.align 1
ZCrystals:
    .hword ITEM_PIKANIUM_Z
    .hword ITEM_PIKASHUNIUM_Z
    .hword ITEM_ALORAICHIUM_Z
    .hword ITEM_EEVIUM_Z
    .hword ITEM_DECIDIUM_Z
    .hword ITEM_INCINIUM_Z
    .hword ITEM_PRIMARIUM_Z
    .hword ITEM_KOMMONIUM_Z
    .hword ITEM_MIMIKIUM_Z
    .hword ITEM_SNORLIUM_Z
    .hword ITEM_LYCANIUM_Z
    .hword ITEM_LUNALIUM_Z
    .hword ITEM_SOLGANIUM_Z
    .hword ITEM_NONE

.align 1
SpecialItems:
    .hword ITEM_SHIMMER_STONE
    .hword ITEM_ZEROMIN
    .hword ITEM_HEALTH_WING
    .hword ITEM_MUSCLE_WING
    .hword ITEM_RESIST_WING
    .hword ITEM_GENIUS_WING
    .hword ITEM_CLEVER_WING
    .hword ITEM_SWIFT_WING
    .hword ITEM_NONE

.global EventScript_BattleFrontier_SWShadyRelicSeller
EventScript_BattleFrontier_SWShadyRelicSeller:
    lock
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BattleFrontier_RelicSellerIntro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RelicSellerRejected
    checkitem ITEM_POKE_CHIP 0x2
    compare LASTRESULT TRUE
    if FALSE _goto RelicSellerNotEnoughPokeChips
    removeitem ITEM_POKE_CHIP 0x2
    sound 0xF8 @ Money SE
    waitse
    random 7
    switch LASTRESULT
    case 0, RelicSellerCopper
    case 1, RelicSellerSilver
    case 2, RelicSellerGold
    case 3, RelicSellerVase
    case 4, RelicSellerBand
    case 5, RelicSellerStatue
    case 6, RelicSellerCrown
    goto End

RelicSellerCopper:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_COPPER 1
    goto RelicSellerTradeComplete

RelicSellerSilver:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_SILVER 1
    goto RelicSellerTradeComplete

RelicSellerGold:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_GOLD 1
    goto RelicSellerTradeComplete

RelicSellerVase:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_VASE 1
    goto RelicSellerTradeComplete

RelicSellerBand:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_BAND 1
    goto RelicSellerTradeComplete

RelicSellerStatue:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_STATUE 1
    goto RelicSellerTradeComplete

RelicSellerCrown:
    msgbox gText_BattleFrontier_RelicSellerChoseYes MSG_NORMAL
    obtainitem ITEM_RELIC_CROWN 1
    goto RelicSellerTradeComplete

RelicSellerRejected:
    msgbox gText_BattleFrontier_RelicSellerChoseNo MSG_NORMAL
    goto End

RelicSellerNotEnoughPokeChips:
    msgbox gText_BattleFrontier_RelicSellerNotEnoughChips MSG_NORMAL
    goto End

RelicSellerTradeComplete:
    msgbox gText_BattleFrontier_RelicSellerLeavingForTheDay MSG_NORMAL
    fadescreen FADEOUT_BLACK
    setflag 0xE40 @ Hide relic seller
    hidesprite LASTTALKED
    pause DELAY_1SECOND
    fadescreen FADEIN_BLACK
    goto End

.global EventScript_BattleFrontier_SWMarketGirl
EventScript_BattleFrontier_SWMarketGirl:
    npcchat gText_BattleFrontier_MarketGirl
    end

.global EventScript_BattleFrontier_SWBlackbelt
EventScript_BattleFrontier_SWBlackbelt:
    npcchatwithmovement gText_BattleFrontier_SE_Blackbelt m_LookUp
    end

.global EventScript_BattleFrontier_SEPsychic
EventScript_BattleFrontier_SEPsychic:
    npcchat gText_BattleFrontier_SEPsychic
    end

.global EventScript_BattleFrontier_SEChanneler
EventScript_BattleFrontier_SEChanneler:
    npcchat gText_BattleFrontier_SEChanneler
    end

.global EventScript_BattleFrontier_SEWoman
EventScript_BattleFrontier_SEWoman:
    npcchat gText_BattleFrontier_SEWoman
    end

.global EventScript_BattleFrontier_TowerBoy
EventScript_BattleFrontier_TowerBoy:
    npcchat gText_BattleFrontier_TowerBoy
    end

.global EventScript_BattleFrontier_TowerChild
EventScript_BattleFrontier_TowerChild:
    npcchatwithmovement gText_BattleFrontier_TowerChild m_LookUp
    end

.global EventScript_BattleFrontier_TowerRocker
EventScript_BattleFrontier_TowerRocker:
    npcchat gText_BattleFrontier_TowerRocker
    end

.global EventScript_BattleFrontier_QuarryHiker
EventScript_BattleFrontier_QuarryHiker:
    npcchat gText_BattleFrontier_QuarryHiker
    end

.global EventScript_BattleFrontier_QuarryBlackbelt
EventScript_BattleFrontier_QuarryBlackbelt:
    npcchatwithmovement gText_BattleFrontier_QuarryBlackbelt m_LookDown
    end

.global EventScript_BattleFrontier_NWOldWoman
EventScript_BattleFrontier_NWOldWoman:
    npcchat gText_BattleFrontier_NWOldWoman
    end

.global EventScript_BattleFrontier_NWBoy
EventScript_BattleFrontier_NWBoy:
    npcchat gText_BattleFrontier_NWBoy
    end

.global EventScript_BattleFrontier_NWFisherman
EventScript_BattleFrontier_NWFisherman:
    npcchat gText_BattleFrontier_NWFisherman
    end

.global EventScript_BattleFrontier_NWFatGuy
EventScript_BattleFrontier_NWFatGuy:
    npcchat gText_BattleFrontier_NWFatGuy
    end

.global EventScript_BattleFrontier_NEOldMan
EventScript_BattleFrontier_NEOldMan:
    npcchatwithmovement gText_BattleFrontier_NEOldMan m_LookDown
    end

.global EventScript_BattleFrontier_NEFisherman
EventScript_BattleFrontier_NEFisherman:
    npcchatwithmovement gText_BattleFrontier_NEFisherman m_LookLeft
    end

.global EventScript_BattleFrontier_NELittleBoy
EventScript_BattleFrontier_NELittleBoy:
    npcchat gText_BattleFrontier_NELittleBoy
    end

.global EventScript_BattleFrontier_NEBoy
EventScript_BattleFrontier_NEBoy:
    npcchat gText_BattleFrontier_NEBoy
    end

.global EventScript_BattleFrontier_NEBugCatcher
EventScript_BattleFrontier_NEBugCatcher:
    npcchatwithmovement gText_BattleFrontier_NEBugCatcher m_LookRight
    end

.global EventScript_BattleFrontier_SimPicknicker
EventScript_BattleFrontier_SimPicknicker:
    npcchat gText_BattleFrontier_SimPicknicker
    end

.global EventScript_BattleFrontier_SimScientist
EventScript_BattleFrontier_SimScientist:
    npcchatwithmovement gText_BattleFrontier_SimScientist m_LookDown
    end

.global EventScript_BattleFrontier_SimSuperNerd
EventScript_BattleFrontier_SimSuperNerd:
    npcchat gText_BattleFrontier_SimSuperNerd
    end

.global EventScript_BattleFrontier_FactoryWorker
EventScript_BattleFrontier_FactoryWorker:
    npcchatwithmovement gText_BattleFrontier_FactoryWorker m_LookDown
    end

.global EventScript_BattleFrontier_FactoryFatGuy
EventScript_BattleFrontier_FactoryFatGuy:
    npcchat gText_BattleFrontier_FactoryFatGuy
    end

.global EventScript_BattleFrontier_ObservatoryGirl
EventScript_BattleFrontier_ObservatoryGirl:
    npcchatwithmovement gText_BattleFrontier_ObservatoryGirl m_LookLeft
    end

.global EventScript_BattleFrontier_ObservatoryGentleman
EventScript_BattleFrontier_ObservatoryGentleman:
    npcchat gText_BattleFrontier_ObservatoryGentleman
    end

.global EventScript_BattleFrontier_ObservatoryCamper
EventScript_BattleFrontier_ObservatoryCamper:
    npcchatwithmovement gText_BattleFrontier_ObservatoryCamper m_LookUp
    end

.global SignScript_BattleFrontier_BattleTower
SignScript_BattleFrontier_BattleTower:
    msgbox gText_BattleFrontier_BattleTowerSign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleQuarry
SignScript_BattleFrontier_BattleQuarry:
    msgbox gText_BattleFrontier_BattleQuarrySign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleSands
SignScript_BattleFrontier_BattleSands:
    msgbox gText_BattleFrontier_BattleSandsSign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleIsle
SignScript_BattleFrontier_BattleIsle:
    msgbox gText_BattleFrontier_BattleIsleSign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleMaze
SignScript_BattleFrontier_BattleMaze:
    msgbox gText_BattleFrontier_BattleMazeSign MSG_SIGN
    end

.global SignScript_BattleFrontier_SWBattleSim
SignScript_BattleFrontier_SWBattleSim:
    msgbox gText_BattleFrontier_SE_BattleSimSign MSG_SIGN
    end

.global SignScript_BattleFrontier_SWBattleFrontierMarket
SignScript_BattleFrontier_SWBattleFrontierMarket:
    msgbox gText_BattleFrontier_SE_BattleFrontierMarketSign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleFactory
SignScript_BattleFrontier_BattleFactory:
    msgbox gText_BattleFrontier_BattleFactorySign MSG_SIGN
    end

.global SignScript_BattleFrontier_BattleObservatory
SignScript_BattleFrontier_BattleObservatory:
    msgbox gText_BattleFrontier_BattleObservatorySign MSG_SIGN
    end

@ ============================================================================
@ Battle Frontier Facility scripts
@
@ One shared attendant script drives every facility. A facility is identified only by
@ VAR_BATTLE_FACILITY_NUM, so the format choice, party entry, battle loop,
@ Continue/Rest/Give up prompts and records board below are all shared. The only
@ per-facility code sits behind the hooks dispatched from the "Per-facility hooks"
@ section, which is where each facility's own cutscene and movements live.
@
@ A run belongs to one facility/format pair, allowing every facility to hold onto
@ a paused streak that can be resumed at any time. The player is free to wanter while a
@ streak is paused.
@
@ Adding a facility is: an entry point that sets VAR_BATTLE_FACILITY_NUM and jumps to
@ BattleFrontier_Common_Attendant, a rules string with a case in
@ BattleFrontier_Common_FacilityRules, and a case in each per-facility hook it needs. See the
@ Battle Tower as a reference.
@ ============================================================================

@ enum BattleFacilities, from include/new/frontier.h
.equ IN_BATTLE_TOWER, 0x0
.equ IN_BATTLE_SANDS, 0x1
.equ IN_BATTLE_QUARRY, 0x2
.equ IN_BATTLE_SIM, 0x3
.equ IN_BATTLE_FACTORY, 0x4
.equ IN_RING_CHALLENGE, 0x5
.equ IN_ISLE_CHALLENGE, 0x6
.equ IN_BATTLE_MAZE, 0x7

@ enum FrontierStreakFormats
.equ FRONTIER_FORMAT_SINGLES, 0x0
.equ FRONTIER_FORMAT_DOUBLES, 0x1

@ enum FrontierChallengeStates
.equ FRONTIER_NONE, 0x0
.equ FRONTIER_ACTIVE, 0x1
.equ FRONTIER_RESTING, 0x2

@ enum FrontierOpponentKinds
.equ FRONTIER_OPPONENT_REGULAR, 0x0
.equ FRONTIER_OPPONENT_ACE, 0x1
.equ FRONTIER_OPPONENT_BRAIN, 0x2

@ Reserved trainer IDs, from include/new/frontier.h
.equ FRONTIER_BRAIN_TID, 0x397
.equ BATTLE_TOWER_SPECIAL_TID, 0x398
.equ BATTLE_TOWER_TID, 0x399

.equ VAR_BATTLE_FACILITY_NUM, 0x403A
.equ FLAG_GAME_CLEARED, 0x82C

.equ SPECIAL_SAVE_PLAYER_PARTY, 0x27
.equ SPECIAL_LOAD_PLAYER_PARTY, 0x28
.equ SPECIAL_CHOOSE_FRONTIER_TEAM, 0xF5
.equ SPECIAL_GENERATE_FACILITY_TRAINER, 0x52
.equ SPECIAL_LOAD_FRONTIER_INTRO_MESSAGE, 0x53
.equ SPECIAL_UPDATE_FACILITY_STREAK, 0x55
.equ SPECIAL_SHOW_FRONTIER_RECORDS, 0x57
.equ SPECIAL_MODIFY_TEAM_FOR_FRONTIER, 0x73
.equ SPECIAL_LOAD_BATTLE_SIM_EFFECTS, 0x72

@ From include/constants/songs.h
.equ MUS_BIG_CELEBRATION, 0x10C
.equ MUS_CELEBRATION, 0x10D
.equ MUS_FAILED, 0x10E

.equ STREAK_INCREMENT, 0x0
.equ STREAK_RESET, 0x1

@ Indices into gScrollingSets in src/scripting.c
.equ MULTICHOICE_SET_FRONTIER_MUSIC, 0x15
.equ MULTICHOICE_SET_FRONTIER_BACKGROUND, 0x16
.equ SPECIAL_SCROLLING_MULTICHOICE, 0x158

@ Var8000 value that makes trainerbattle9 continue the script after a loss (no white out)
.equ CONTINUE_AFTER_LOSS, 0xFEFE
.equ VAR_DYNAMIC_OW_SPRITE, 0x5029

@ Each battle facilities key NPC IDs
.equ BATTLE_TOWER_ATTENDANT, 0x1
.equ BATTLE_TOWER_OPPONENT, 0x2
.equ BATTLE_SANDS_ATTENDANT, 0x1
.equ BATTLE_SANDS_OPPONENT, 0x2
.equ BATTLE_QUARRY_ATTENDANT, 0x1
.equ BATTLE_QUARRY_OPPONENT, 0x2
.equ BATTLE_SIM_ATTENDANT, 0x1
.equ BATTLE_SIM_OPPONENT, 0x2
.equ BATTLE_MAZE_ATTENDANT, 0x5
.equ BATTLE_MAZE_OPPONENT, 0x6

@ ============================================================================
@ Per-facility entry points
@ ============================================================================

.global EventScript_BattleFrontier_TowerAttendant
EventScript_BattleFrontier_TowerAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_TOWER
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_QuarryAttendant
EventScript_BattleFrontier_QuarryAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_QUARRY
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_SandsAttendant
EventScript_BattleFrontier_SandsAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_SANDS
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_IsleAttendant
EventScript_BattleFrontier_IsleAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_ISLE_CHALLENGE @ TODO: Rename to Battle Isle
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_MazeAttendant
EventScript_BattleFrontier_MazeAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_MAZE
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_SimAttendant
EventScript_BattleFrontier_SimAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_SIM
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_FactoryAttendant
EventScript_BattleFrontier_FactoryAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_FACTORY
    goto BattleFrontier_Common_Attendant

.global EventScript_BattleFrontier_ObservatoryAttendant
EventScript_BattleFrontier_ObservatoryAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_RING_CHALLENGE @ TODO: Becomes battle observatory
    goto BattleFrontier_Common_Attendant

@ ============================================================================
@ Shared attendant flow
@ ============================================================================

BattleFrontier_Common_Attendant:
    lock
    faceplayer
    @ Must run before anything reads a streak or a run's state.
    callasm FrontierChallenge_InitDataIfNeeded
    goto BattleFrontier_Common_LobbyMenu

@ Every way out of the attendant goes through here, so nothing can leave the overworld with
@ FLAG_BATTLE_FACILITY still set - see FrontierChallenge_ClearFacilityVars.
BattleFrontier_Common_Exit:
    callasm FrontierChallenge_ClearFacilityVars
    goto End

BattleFrontier_Common_LobbyMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_Welcome MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceChallenge 0
    multichoiceoption gText_BattleFrontier_ChoiceRules 1
    multichoiceoption gText_BattleFrontier_ChoiceRecords 2
    multichoiceoption gText_BattleFrontier_ChoiceBackground 3
    multichoiceoption gText_BattleFrontier_ChoiceMusic 4
    multichoiceoption gText_BattleFrontier_ChoiceLeave 5
    multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_ChooseFormat
    case 1, BattleFrontier_Common_Rules
    case 2, BattleFrontier_Common_Records
    case 3, BattleFrontier_Common_Background
    case 4, BattleFrontier_Common_Music
    goto BattleFrontier_Common_Farewell

BattleFrontier_Common_Farewell:
    msgbox gText_BattleFrontier_Farewell MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    goto BattleFrontier_Common_Exit

@ ============================================================================
@ Rules and records
@ ============================================================================

@ Prompt for Frontier (common) rules or Facility-specific
BattleFrontier_Common_Rules:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_RulesPrompt MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceFrontierRules 0
    multichoiceoption gText_BattleFrontier_ChoiceFacilityRules 1
    multichoiceoption gText_BattleFrontier_ChoiceCancel 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_FrontierRules
    case 1, BattleFrontier_Common_FacilityRules
    goto BattleFrontier_Common_LobbyMenu

BattleFrontier_Common_FrontierRules:
    msgbox gText_BattleFrontier_CommonRules MSG_KEEPOPEN
    goto BattleFrontier_Common_Rules

@ A facility with no case here shows nothing at all, so every facility owes this switch a line.
BattleFrontier_Common_FacilityRules:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_Rules, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_Rules, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_Rules, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_Rules, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_Rules, _call
    goto BattleFrontier_Common_Rules

BattleFrontier_Tower_Rules:
    msgbox gText_BattleFrontier_TowerRules MSG_KEEPOPEN
    return

BattleFrontier_Sands_Rules:
    msgbox gText_BattleFrontier_SandsRules MSG_KEEPOPEN
    return

BattleFrontier_Quarry_Rules:
    msgbox gText_BattleFrontier_QuarryRules MSG_KEEPOPEN
    return

BattleFrontier_Sim_Rules:
    msgbox gText_BattleFrontier_SimRules MSG_KEEPOPEN
    return

BattleFrontier_Maze_Rules:
    msgbox gText_BattleFrontier_MazeRules MSG_KEEPOPEN
    return

BattleFrontier_Common_Records:
    special SPECIAL_SHOW_FRONTIER_RECORDS
    waitstate
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Battle background
@ ============================================================================

BattleFrontier_Common_Background:
    callasm FrontierChallenge_BufferBattleBackgroundName
    msgbox gText_BattleFrontier_ChooseBackground MSG_KEEPOPEN
    setvar SCROLL_MULTICHOICE_NUM MULTICHOICE_SET_FRONTIER_BACKGROUND
    setvar SCROLL_MULTICHOICE_HEIGHT 0x6
    setvar 0x8004 0x0 @ Always 0, so the menu cleans itself up when called again
    special SPECIAL_SCROLLING_MULTICHOICE
    waitstate
    copyvar 0x8000 LASTRESULT
    callasm FrontierChallenge_SetBattleBackground
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    msgbox gText_BattleFrontier_BackgroundChosen MSG_KEEPOPEN
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Battle music
@ ============================================================================

BattleFrontier_Common_Music:
    callasm FrontierChallenge_BufferBattleMusicName
    msgbox gText_BattleFrontier_ChooseMusic MSG_KEEPOPEN
    setvar SCROLL_MULTICHOICE_NUM MULTICHOICE_SET_FRONTIER_MUSIC
    setvar SCROLL_MULTICHOICE_HEIGHT 0x6
    setvar 0x8004 0x0 @ Always 0, so the menu cleans itself up when called again
    special SPECIAL_SCROLLING_MULTICHOICE
    waitstate
    copyvar 0x8000 LASTRESULT
    callasm FrontierChallenge_SetBattleMusic
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    msgbox gText_BattleFrontier_MusicChosen MSG_KEEPOPEN
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Starting a challenge
@ ============================================================================

@ Each challenge is facility/format specific (e.x. Battle Tower Singles & Battle Tower Doubles)
BattleFrontier_Common_ChooseFormat:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_ChooseFormat MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceSingles 0
    multichoiceoption gText_BattleFrontier_ChoiceDoubles 1
    multichoiceoption gText_BattleFrontier_ChoiceCancel 2
    @ Handle format multichoice text for runs that are in progress
    setvar 0x8000 FRONTIER_FORMAT_SINGLES
    callasm FrontierChallenge_IsFormatPaused
    compare LASTRESULT TRUE
    if equal _call BattleFrontier_Common_LabelSinglesOnHold
    setvar 0x8000 FRONTIER_FORMAT_DOUBLES
    callasm FrontierChallenge_IsFormatPaused
    compare LASTRESULT TRUE
    if equal _call BattleFrontier_Common_LabelDoublesOnHold
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_FormatSingles
    case 1, BattleFrontier_Common_FormatDoubles
    goto BattleFrontier_Common_LobbyMenu

BattleFrontier_Common_LabelSinglesOnHold:
    multichoiceoption gText_BattleFrontier_ChoiceSinglesOnHold 0
    return

BattleFrontier_Common_LabelDoublesOnHold:
    multichoiceoption gText_BattleFrontier_ChoiceDoublesOnHold 1
    return

BattleFrontier_Common_FormatSingles:
    setvar 0x8000 FRONTIER_FORMAT_SINGLES
    goto BattleFrontier_Common_FormatChosen

BattleFrontier_Common_FormatDoubles:
    setvar 0x8000 FRONTIER_FORMAT_DOUBLES
    goto BattleFrontier_Common_FormatChosen

@ Load the format so the party selection screen can prompt for the right number of pokemon (3 vs 4)
BattleFrontier_Common_FormatChosen:
    callasm FrontierChallenge_LoadFacilityVars
    callasm FrontierChallenge_GetState
    compare LASTRESULT FRONTIER_RESTING
    if equal _goto BattleFrontier_Common_RunOnHold
    goto BattleFrontier_Common_BeginChallenge

BattleFrontier_Common_BeginChallenge:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_BufferNumMonsToEnter
    compare VAR_BATTLE_FACILITY_NUM IN_BATTLE_MAZE
    if equal _goto BattleFrontier_Common_ConfirmRandomTeamChallenge
    msgbox gText_BattleFrontier_ConfirmChallenge MSG_YESNO
    goto BattleFrontier_Common_ChallengeConfirmed

@ The Battle Maze and Battle Factory don't ask the player to bring their own teams
BattleFrontier_Common_ConfirmRandomTeamChallenge:
    msgbox gText_BattleFrontier_ConfirmChallengeRandom MSG_YESNO

BattleFrontier_Common_ChallengeConfirmed:
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_LobbyMenu
    call BattleFrontier_Common_EnterTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    callasm FrontierChallenge_Begin
    goto BattleFrontier_Common_StartRun

@ The last steps before a run's first battle, shared by a new run and one picked back up.
@ The order of these three is load-bearing and must not be shuffled:
@
@   - the save must occur while gPlayerParty still is the player's real team. Saving
@     serialises gPlayerParty into SaveBlock1.playerParty, effectively replacing their party
@     with the level 50 normalized copy.
@   - the modifier override has to follow the save, so the player's preferred modifiers
@     remain set in the save file - see FrontierChallenge_OverrideGameModifiers.
@   - sp073 goes last, because replacing the party is exactly what it does.
BattleFrontier_Common_StartRun:
    call BattleFrontier_Common_CommitRun
    callasm FrontierChallenge_OverrideGameModifiers
    special SPECIAL_MODIFY_TEAM_FOR_FRONTIER
    call BattleFrontier_Common_EnterBattlePosition @ After CommitRun's save, so a reset returns the player to the lobby
    goto BattleFrontier_Common_BattleLoop

@ Handles both a new run and a resumed run.
@ The run is set to ACTIVE in the player save so FrontierChallenge_InitDataIfNeeded will cancel
@ its streak if the player soft resets to try and game the randomized trainers.
BattleFrontier_Common_CommitRun:
    callasm FrontierChallenge_NeedsCommitting
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_CommitRunDone
    msgbox gText_BattleFrontier_ResumeWarning MSG_KEEPOPEN
    callasm FrontierChallenge_Commit
    callasm FrontierChallenge_ClearFacilityVars
    callasm FrontierChallenge_ForceSave
    waitstate
    callasm FrontierChallenge_SetFacilityFlag

BattleFrontier_Common_CommitRunDone:
    return

@ Backs up the real party, has the player pick their entered team, then puts the real
@ party back so sp073 can build the level-adjusted copies from the chosen slots.
@ Returns FALSE if the player backed out.
BattleFrontier_Common_EnterTeam:
    special SPECIAL_SAVE_PLAYER_PARTY
    compare VAR_BATTLE_FACILITY_NUM IN_BATTLE_MAZE
    if equal _goto BattleFrontier_Common_EnterTeamRolled
    msgbox gText_BattleFrontier_ChooseTeam MSG_KEEPOPEN
    special SPECIAL_CHOOSE_FRONTIER_TEAM
    waitstate
    callasm FrontierChallenge_DidChooseTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_EnterTeamCancelled
    special SPECIAL_LOAD_PLAYER_PARTY
    setvar LASTRESULT TRUE
    return

BattleFrontier_Common_EnterTeamCancelled:
    setvar LASTRESULT FALSE
    return

@ The Battle Maze picks a random team so we skip the party selection.
@ The player's party is still saved & restored.
BattleFrontier_Common_EnterTeamRolled:
    setvar LASTRESULT TRUE
    return

@ ============================================================================
@ Battle loop
@ ============================================================================

BattleFrontier_Common_BattleLoop:
    call BattleFrontier_Common_PerBattleSetup
    callasm FrontierChallenge_SetUpNextOpponent
    special2 LASTRESULT SPECIAL_GENERATE_FACILITY_TRAINER
    copyvar VAR_DYNAMIC_OW_SPRITE LASTRESULT
    call BattleFrontier_Common_OpponentArrives
    setvar 0x8000 0x0
    special SPECIAL_LOAD_FRONTIER_INTRO_MESSAGE
    callstd MSG_KEEPOPEN @ Prints the line sp053 left in gLoadPointer
    callasm FrontierChallenge_RestoreTextColour
    compare 0x8001 FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_BattleSpecialTrainer
    compare 0x8001 FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_BattleFrontierBrain
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 BATTLE_TOWER_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleSpecialTrainer:
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 BATTLE_TOWER_SPECIAL_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleFrontierBrain:
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 FRONTIER_BRAIN_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleEnded:
    call BattleFrontier_Common_PostBattleReset
    setvar 0x8000 0x0
    callasm FrontierChallenge_DidPlayerWin
    compare LASTRESULT TRUE
    if notequal _goto BattleFrontier_Common_Loss
    goto BattleFrontier_Common_Win

@ Once per run, as it starts. Both a new run and one picked back up come through here.
BattleFrontier_Common_EnterBattlePosition:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_EnterBattlePosition, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_EnterBattlePosition, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_EnterBattlePosition, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_EnterBattlePosition, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_EnterBattlePosition, _call
    return

@ Before every battle. Sim randomizes its field effects here (special 0x72), Factory swaps the team.
@ The Maze picks a random team via BuildTrainerPartySetup every time.
BattleFrontier_Common_PerBattleSetup:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_PerBattleSetup, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_PerBattleSetup, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_PerBattleSetup, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_PerBattleSetup, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_PerBattleSetup, _call
    return

BattleFrontier_Common_OpponentArrives:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_OpponentArrives, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_OpponentArrives, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_OpponentArrives, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_OpponentArrives, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_OpponentArrives, _call
    return

BattleFrontier_Common_PostBattleReset:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_PostBattleReset, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_PostBattleReset, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_PostBattleReset, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_PostBattleReset, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_PostBattleReset, _call
    return

BattleFrontier_Common_LeaveBattlePosition:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_LeaveBattlePosition, _call
    case IN_BATTLE_SANDS, BattleFrontier_Sands_LeaveBattlePosition, _call
    case IN_BATTLE_QUARRY, BattleFrontier_Quarry_LeaveBattlePosition, _call
    case IN_BATTLE_SIM, BattleFrontier_Sim_LeaveBattlePosition, _call
    case IN_BATTLE_MAZE, BattleFrontier_Maze_LeaveBattlePosition, _call
    return

@ These three MUST stay MSG_KEEPOPEN. The opponent is already walking offscreen, and MSG_NORMAL ends
@ in a release call that would destroy the task for the opponent's movement, resulting in a soft crash!
BattleFrontier_Common_CommentOnResult:
    callasm FrontierChallenge_DidPlayerWin
    compare LASTRESULT TRUE
    if notequal _goto BattleFrontier_Common_CommentOnLoss
    callasm FrontierChallenge_GetNextOpponentKind
    compare LASTRESULT FRONTIER_OPPONENT_REGULAR
    if notequal _goto BattleFrontier_Common_CommentOnMilestoneWin
    fanfare MUS_CELEBRATION
    msgbox gText_BattleFrontier_AttendantWin MSG_KEEPOPEN
    return

BattleFrontier_Common_CommentOnMilestoneWin:
    fanfare MUS_BIG_CELEBRATION
    msgbox gText_BattleFrontier_AttendantWinMilestone MSG_KEEPOPEN
    return

BattleFrontier_Common_CommentOnLoss:
    fanfare MUS_FAILED
    msgbox gText_BattleFrontier_AttendantLoss MSG_KEEPOPEN
    return

@ ----------------------------------------------------------------------------
@ Battle Tower Movements
@ ----------------------------------------------------------------------------
BattleFrontier_Tower_EnterBattlePosition:
    msgbox gText_BattleFrontier_LeadToBattlePosition MSG_NORMAL
    applymovement PLAYER m_BattleTower_PlayerToBattlePosition
    applymovement BATTLE_TOWER_ATTENDANT m_BattleTower_AttendantToBattlePosition
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveRight
    waitmovement CAMERA
    special CAMERA_END
    return

BattleFrontier_Tower_PerBattleSetup:
    applymovement PLAYER m_LookRight
    applymovement BATTLE_TOWER_ATTENDANT m_LookRight
    return

BattleFrontier_Tower_OpponentArrives:
    msgbox gText_BattleFrontier_CallingOpponent MSG_NORMAL
    showsprite BATTLE_TOWER_OPPONENT
    applymovement BATTLE_TOWER_OPPONENT m_BattleTower_OpponentToBattlePosition
    waitmovement ALLEVENTS
    return

BattleFrontier_Tower_PostBattleReset:
    applymovement PLAYER m_LookDown
    applymovement BATTLE_TOWER_ATTENDANT m_LookUp
    applymovement BATTLE_TOWER_OPPONENT m_BattleTower_OpponentLeaves
    call BattleFrontier_Common_CommentOnResult @ Before the wait, so it plays over the opponent leaving
    waitmovement ALLEVENTS
    closeonkeypress
    hidesprite BATTLE_TOWER_OPPONENT
    return

BattleFrontier_Tower_LeaveBattlePosition:
    msgbox gText_BattleFrontier_LeadToLobby MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveLeft
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_BattleTower_PlayerToLobby
    applymovement BATTLE_TOWER_ATTENDANT m_BattleTower_AttendantToLobby
    waitmovement ALLEVENTS
    return

@ Movements
m_BattleTower_PlayerToBattlePosition: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, look_right, end_m
m_BattleTower_AttendantToBattlePosition: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, pause_long, pause_long, walk_left, walk_left, look_right, end_m
m_BattleTower_OpponentToBattlePosition: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, look_left, end_m
m_BattleTower_OpponentLeaves: .byte walk_left, walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_BattleTower_PlayerToLobby: .byte walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, look_up, end_m
m_BattleTower_AttendantToLobby: .byte walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_left, look_right, pause_long, walk_right, walk_down, look_down, end_m

@ ----------------------------------------------------------------------------
@ Battle Sands Movements
@ ----------------------------------------------------------------------------

BattleFrontier_Sands_EnterBattlePosition:
    msgbox gText_BattleFrontier_SandsLeadToArena MSG_NORMAL
    getplayerpos 0x8004 0x8005
    compare 0x8005 34 @ Above attendant
    if equal _goto BattleFrontier_Sands_EnterBattlePositionFromNorth
    applymovement PLAYER m_BattleSands_PlayerToArenaFromSouth
    goto BattleFrontier_Sands_EnterBattlePositionAttendant

BattleFrontier_Sands_EnterBattlePositionFromNorth:
    applymovement PLAYER m_BattleSands_PlayerToArenaFromNorth

BattleFrontier_Sands_EnterBattlePositionAttendant:
    applymovement BATTLE_SANDS_ATTENDANT m_BattleSands_AttendantToArena
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveLeft
    waitmovement CAMERA
    special CAMERA_END
    return

BattleFrontier_Sands_PerBattleSetup:
    applymovement PLAYER m_LookLeft
    applymovement BATTLE_SANDS_ATTENDANT m_LookLeft
    return

BattleFrontier_Sands_OpponentArrives:
    msgbox gText_BattleFrontier_CallingOpponent MSG_NORMAL
    showsprite BATTLE_SANDS_OPPONENT
    applymovement BATTLE_SANDS_OPPONENT m_BattleSands_OpponentToArena
    waitmovement ALLEVENTS
    return

BattleFrontier_Sands_PostBattleReset:
    applymovement PLAYER m_LookDown
    applymovement BATTLE_SANDS_ATTENDANT m_LookUp
    applymovement BATTLE_SANDS_OPPONENT m_BattleSands_OpponentLeaves
    call BattleFrontier_Common_CommentOnResult @ Before the wait, so it plays over the opponent leaving
    waitmovement ALLEVENTS
    closeonkeypress
    hidesprite BATTLE_SANDS_OPPONENT
    return

BattleFrontier_Sands_LeaveBattlePosition:
    msgbox gText_BattleFrontier_LeadToLobby MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveRight
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_BattleSands_PlayerToLobby
    applymovement BATTLE_SANDS_ATTENDANT m_BattleSands_AttendantToLobby
    waitmovement ALLEVENTS
    return

@ Movements
m_BattleSands_PlayerToArenaFromSouth: .byte walk_left, walk_left, walk_left, look_left, end_m
m_BattleSands_PlayerToArenaFromNorth: .byte walk_left, walk_left, walk_down, walk_down, walk_left, look_left, end_m
m_BattleSands_AttendantToArena: .byte walk_down, walk_left, walk_left, walk_down, walk_left, look_left, end_m
m_BattleSands_OpponentToArena: .byte walk_right, walk_right, walk_right, walk_right, walk_right, look_right, end_m
m_BattleSands_OpponentLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_BattleSands_PlayerToLobby: .byte pause_long, look_right, pause_long, walk_right, walk_right, walk_right, look_up, end_m
m_BattleSands_AttendantToLobby: .byte walk_right, walk_up, walk_right, walk_right, walk_up, look_down, end_m

@ ----------------------------------------------------------------------------
@ Battle Quarry Movements
@ ----------------------------------------------------------------------------

BattleFrontier_Quarry_EnterBattlePosition:
    msgbox gText_BattleFrontier_LeadToBattlePosition MSG_NORMAL
    applymovement PLAYER m_BattleQuarry_PlayerToPit
    applymovement BATTLE_QUARRY_ATTENDANT m_BattleQuarry_AttendantToPit
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveRight_2
    waitmovement CAMERA
    special CAMERA_END
    return

BattleFrontier_Quarry_PerBattleSetup:
    applymovement PLAYER m_LookRight
    applymovement BATTLE_QUARRY_ATTENDANT m_LookRight
    return

BattleFrontier_Quarry_OpponentArrives:
    msgbox gText_BattleFrontier_CallingOpponent MSG_NORMAL
    showsprite BATTLE_QUARRY_OPPONENT
    applymovement BATTLE_QUARRY_OPPONENT m_BattleQuarry_OpponentToPit
    waitmovement ALLEVENTS
    return

BattleFrontier_Quarry_PostBattleReset:
    applymovement PLAYER m_LookDown
    applymovement BATTLE_QUARRY_ATTENDANT m_LookUp
    applymovement BATTLE_QUARRY_OPPONENT m_BattleQuarry_OpponentLeaves
    call BattleFrontier_Common_CommentOnResult @ Before the wait, so it plays over the opponent leaving
    waitmovement ALLEVENTS
    closeonkeypress
    hidesprite BATTLE_QUARRY_OPPONENT
    return

BattleFrontier_Quarry_LeaveBattlePosition:
    msgbox gText_BattleFrontier_LeadToLobby MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveLeft_2
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_BattleQuarry_PlayerToLobby
    applymovement BATTLE_QUARRY_ATTENDANT m_BattleQuarry_AttendantToLobby
    waitmovement ALLEVENTS
    return

@ Movements
m_BattleQuarry_PlayerToPit: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, look_right, end_m
m_BattleQuarry_AttendantToPit: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, pause_long, pause_long, walk_left, look_right, end_m
m_BattleQuarry_OpponentToPit: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, look_left, end_m
m_BattleQuarry_OpponentLeaves: .byte walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_BattleQuarry_PlayerToLobby: .byte walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, look_up, end_m
m_BattleQuarry_AttendantToLobby: .byte walk_right, walk_right, walk_down, walk_down, walk_down, walk_left, look_right, pause_long, walk_right, walk_down, walk_down, look_down, end_m

@ ----------------------------------------------------------------------------
@ Battle Sim Movements
@ ----------------------------------------------------------------------------

BattleFrontier_Sim_EnterBattlePosition:
    msgbox gText_BattleFrontier_LeadToBattlePosition MSG_NORMAL
    applymovement PLAYER m_BattleSim_PlayerToStage
    applymovement BATTLE_SIM_ATTENDANT m_BattleSim_AttendantToStage
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveRight_2
    waitmovement CAMERA
    special CAMERA_END
    return

@ sp072 adds one effect per call, describes it in gStringVarC and returns TRUE once the
@ streak's quota is full, so the roll has to be a loop rather than a single call.
@ It can trigger weather which needs to be set & reset here for overworld effects
BattleFrontier_Sim_PerBattleSetup:
    applymovement PLAYER m_LookRight
    applymovement BATTLE_SIM_ATTENDANT m_LookRight
    resetweather
    msgbox gText_BattleFrontier_SimCalibrating MSG_KEEPOPEN

BattleFrontier_Sim_RollEffect:
    special SPECIAL_LOAD_BATTLE_SIM_EFFECTS
    compare LASTRESULT TRUE
    if equal _goto BattleFrontier_Sim_RollEffectsDone
    msgbox gText_BattleFrontier_SimEffectRolled MSG_KEEPOPEN
    goto BattleFrontier_Sim_RollEffect

BattleFrontier_Sim_RollEffectsDone:
    doweather
    return

BattleFrontier_Sim_OpponentArrives:
    msgbox gText_BattleFrontier_CallingOpponent MSG_NORMAL
    showsprite BATTLE_SIM_OPPONENT
    applymovement BATTLE_SIM_OPPONENT m_BattleSim_OpponentToStage
    waitmovement ALLEVENTS
    return

BattleFrontier_Sim_PostBattleReset:
    applymovement PLAYER m_LookDown
    applymovement BATTLE_SIM_ATTENDANT m_LookUp
    applymovement BATTLE_SIM_OPPONENT m_BattleSim_OpponentLeaves
    call BattleFrontier_Common_CommentOnResult @ Before the wait, so it plays over the opponent leaving
    waitmovement ALLEVENTS
    closeonkeypress
    hidesprite BATTLE_SIM_OPPONENT
    return

@ The run is over, so the last battle's simulated weather gets torn down here rather than
@ being left running over the salon.
BattleFrontier_Sim_LeaveBattlePosition:
    msgbox gText_BattleFrontier_LeadToLobby MSG_NORMAL
    resetweather
    doweather
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveLeft_2
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_BattleSim_PlayerToLobby
    applymovement BATTLE_SIM_ATTENDANT m_BattleSim_AttendantToLobby
    waitmovement ALLEVENTS
    return

@ Movements
m_BattleSim_PlayerToStage: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, look_right, end_m
m_BattleSim_AttendantToStage: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_left, pause_long, pause_long, walk_left, walk_left, look_right, end_m
m_BattleSim_OpponentToStage: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, look_left, end_m
m_BattleSim_OpponentLeaves: .byte walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_BattleSim_PlayerToLobby: .byte walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, look_up, end_m
m_BattleSim_AttendantToLobby: .byte walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_down, walk_down, walk_left, look_right, pause_long, walk_right, walk_down, look_down, end_m

@ ----------------------------------------------------------------------------
@ Battle Maze Movements
@ ----------------------------------------------------------------------------

BattleFrontier_Maze_EnterBattlePosition:
    msgbox gText_BattleFrontier_LeadToBattlePosition MSG_NORMAL
    getplayerpos 0x8004 0x8005
    compare 0x8005 35 @ Beside the attendant rather than below them
    if equal _goto BattleFrontier_Maze_EnterBattlePositionFromEast
    applymovement PLAYER m_BattleMaze_PlayerToArenaFromSouth
    applymovement BATTLE_MAZE_ATTENDANT m_BattleMaze_AttendantToArena
    goto BattleFrontier_Maze_EnterBattlePositionCamera

BattleFrontier_Maze_EnterBattlePositionFromEast:
    applymovement PLAYER m_BattleMaze_PlayerToArenaFromEast
    applymovement BATTLE_MAZE_ATTENDANT m_BattleMaze_AttendantToArena

BattleFrontier_Maze_EnterBattlePositionCamera:
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveRight
    waitmovement CAMERA
    special CAMERA_END
    return

BattleFrontier_Maze_PerBattleSetup:
    applymovement PLAYER m_LookRight
    applymovement BATTLE_MAZE_ATTENDANT m_LookRight
    return

BattleFrontier_Maze_OpponentArrives:
    msgbox gText_BattleFrontier_CallingOpponent MSG_NORMAL
    showsprite BATTLE_MAZE_OPPONENT
    applymovement BATTLE_MAZE_OPPONENT m_BattleMaze_OpponentToArena
    waitmovement ALLEVENTS
    return

BattleFrontier_Maze_PostBattleReset:
    applymovement PLAYER m_LookDown
    applymovement BATTLE_MAZE_ATTENDANT m_LookUp
    applymovement BATTLE_MAZE_OPPONENT m_BattleMaze_OpponentLeaves
    call BattleFrontier_Common_CommentOnResult @ Before the wait, so it plays over the opponent leaving
    waitmovement ALLEVENTS
    closeonkeypress
    hidesprite BATTLE_MAZE_OPPONENT
    return

BattleFrontier_Maze_LeaveBattlePosition:
    msgbox gText_BattleFrontier_LeadToLobby MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_BattleFacility_CameraMoveLeft
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_BattleMaze_PlayerToLobby
    applymovement BATTLE_MAZE_ATTENDANT m_BattleMaze_AttendantToLobby
    waitmovement ALLEVENTS
    return

@ Movements
m_BattleMaze_PlayerToArenaFromEast: .byte walk_down, walk_down, pause_long, pause_long, walk_right, walk_right, end_m
m_BattleMaze_PlayerToArenaFromSouth: .byte walk_down, walk_right, pause_long, pause_long, walk_right, walk_right, end_m
m_BattleMaze_AttendantToArena: .byte walk_down, walk_down, walk_down, walk_right, walk_right, walk_right, end_m
m_BattleMaze_OpponentToArena: .byte walk_left, walk_left, walk_left, walk_left, walk_left, look_left, end_m
m_BattleMaze_OpponentLeaves: .byte walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_BattleMaze_PlayerToLobby: .byte walk_left, walk_left, pause_long, pause_long, walk_left, walk_up, end_m
m_BattleMaze_AttendantToLobby: .byte walk_left, walk_left, walk_left, walk_up, walk_up, walk_up, look_down, end_m

@ ============================================================================
@ Common Movements
@ ============================================================================

m_BattleFacility_CameraMoveRight_2: .byte walk_right, walk_right, end_m
m_BattleFacility_CameraMoveLeft_2: .byte walk_left, walk_left, end_m
m_BattleFacility_CameraMoveRight: .byte walk_right, walk_right, walk_right, end_m
m_BattleFacility_CameraMoveLeft: .byte walk_left, walk_left, walk_left, end_m

@ ============================================================================
@ Winning, and the Continue / Rest / Give up prompt
@ ============================================================================

BattleFrontier_Common_Win:
    setvar 0x8000 STREAK_INCREMENT
    special SPECIAL_UPDATE_FACILITY_STREAK
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_StoreChipsToGive
    compare LASTRESULT 0
    if equal _goto BattleFrontier_Common_WinNoRoomForChips
    msgbox gText_BattleFrontier_WinReward MSG_KEEPOPEN
    setvar 0x8000 ITEM_POKE_CHIP
    copyvar 0x8001 LASTRESULT
    callstd MSG_OBTAIN
    goto BattleFrontier_Common_ChallengeMenu

@ Reminder: Player can only hold 999 PokeChips so they may get reduced (or no) rewards based on bag stock
BattleFrontier_Common_WinNoRoomForChips:
    msgbox gText_BattleFrontier_WinRewardCaseFull MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenu

@ Offer to continue, rest, or abandon (can't press B to choose)
@ This handles special text for Ace / Brain battles
BattleFrontier_Common_ChallengeMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_GetNextOpponentKind
    compare LASTRESULT FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_ChallengeMenuAceNext
    compare LASTRESULT FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_ChallengeMenuBrainNext
    msgbox gText_BattleFrontier_ChallengeMenuPrompt MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuAceNext:
    msgbox gText_BattleFrontier_ChallengeMenuPromptAce MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuBrainNext:
    msgbox gText_BattleFrontier_ChallengeMenuPromptBrain MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuOptions:
    multichoiceoption gText_BattleFrontier_ChoiceContinue 0
    multichoiceoption gText_BattleFrontier_ChoiceRest 1
    multichoiceoption gText_BattleFrontier_ChoiceAbandon 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
    switch LASTRESULT
    case 0, BattleFrontier_Common_BattleLoop @ The entered team carries over
    case 1, BattleFrontier_Common_Rest
    case 2, BattleFrontier_Common_ConfirmAbandon
    goto BattleFrontier_Common_ChallengeMenu

@ ============================================================================
@ Runs left on hold
@ ============================================================================

@ Only hit when choosing a paused run. Player can still choose to cancel out without losing their streak
BattleFrontier_Common_RunOnHold:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_WelcomeBackRested MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenu

@ Warned about the same way as the mid-run menu. The streak is whatever Rest left behind and the
@ facility vars naming the run are already loaded by BattleFrontier_Common_FormatChosen, so the
@ lookahead reads the held run rather than a stale one.
BattleFrontier_Common_OnHoldMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_GetNextOpponentKind
    compare LASTRESULT FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_OnHoldMenuSpecialNext
    compare LASTRESULT FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_OnHoldMenuBrainNext
    msgbox gText_BattleFrontier_OnHoldMenuPrompt MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuSpecialNext:
    msgbox gText_BattleFrontier_OnHoldMenuPromptSpecial MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuBrainNext:
    msgbox gText_BattleFrontier_OnHoldMenuPromptBrain MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuOptions:
    multichoiceoption gText_BattleFrontier_ChoiceContinue 0
    multichoiceoption gText_BattleFrontier_ChoiceAbandon 1
    multichoiceoption gText_BattleFrontier_ChoiceKeepOnHold 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_ResumeRun
    case 1, BattleFrontier_Common_ConfirmAbandonOnHold
    goto BattleFrontier_Common_LobbyMenu

@ Reminder: The player can leave and return with a different team, so we handle
@ party selection as though it were their first run
BattleFrontier_Common_ResumeRun:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_BufferNumMonsToEnter
    call BattleFrontier_Common_EnterTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_OnHoldMenu
    goto BattleFrontier_Common_StartRun

@ When resting, the streak is saved and game modifiers are restored. The player
@ can choose to go to any other facility or just explore without losing their streak
BattleFrontier_Common_Rest:
    msgbox gText_BattleFrontier_ConfirmRest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_ChallengeMenu
    special SPECIAL_LOAD_PLAYER_PARTY
    callasm FrontierChallenge_SetResting
    callasm FrontierChallenge_ClearFacilityVars @ Before the save, or the facility state would be on disk as well as in RAM.
    call BattleFrontier_Common_LeaveBattlePosition @ Also before the save, so the run is picked back up from the lobby.
    msgbox gText_BattleFrontier_Resting MSG_KEEPOPEN
    callasm FrontierChallenge_ForceSave
    waitstate
    goto BattleFrontier_Common_Exit

@ ============================================================================
@ Giving up and losing
@ ============================================================================

BattleFrontier_Common_ConfirmAbandon:
    call BattleFrontier_Common_AskAbandon
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_ChallengeMenu
    call BattleFrontier_Common_EndLiveRun
    call BattleFrontier_Common_LeaveBattlePosition
    goto BattleFrontier_Common_Abandoned

BattleFrontier_Common_ConfirmAbandonOnHold:
    call BattleFrontier_Common_AskAbandon
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_OnHoldMenu
    call BattleFrontier_Common_EndRunOnHold
    goto BattleFrontier_Common_Abandoned

BattleFrontier_Common_AskAbandon:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_ConfirmAbandon MSG_YESNO
    return

BattleFrontier_Common_Abandoned:
    msgbox gText_BattleFrontier_Abandoned MSG_KEEPOPEN
    goto BattleFrontier_Common_Exit

BattleFrontier_Common_Loss:
    call BattleFrontier_Common_EndLiveRun
    call BattleFrontier_Common_LeaveBattlePosition
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_Lost MSG_KEEPOPEN
    goto BattleFrontier_Common_Exit

@ Losing and giving up mid-run end in exactly the same state. The team the player entered
@ with is still live in gPlayerParty on this path, so their real party has to come back.
BattleFrontier_Common_EndLiveRun:
    setvar 0x8000 STREAK_RESET
    special SPECIAL_UPDATE_FACILITY_STREAK
    special SPECIAL_LOAD_PLAYER_PARTY
    callasm FrontierChallenge_End
    return

@ Giving up on a held run instead. No entered team is live, and the player's party must be
@ left alone - special 0x28 would overwrite it with SaveBlock1.playerParty, which tracks the
@ player's last save and by now can be well behind the team they're carrying.
BattleFrontier_Common_EndRunOnHold:
    setvar 0x8000 STREAK_RESET
    special SPECIAL_UPDATE_FACILITY_STREAK
    callasm FrontierChallenge_End
    return

.align 1
