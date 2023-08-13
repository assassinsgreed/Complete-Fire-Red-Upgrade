.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4058
.equ Chance, 0x1
.equ DeskMan, 0x2

.global MapScript_DaimynCityGym
MapScript_DaimynCityGym:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_DaimynCityGym
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_DaimynCityGym
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_DaimynCityGym:
    compare StoryEventVar 0x1
    if lessthan _goto End
    movesprite2 Chance 0x10 0x3
    setobjectmovementtype Chance look_down
    compare StoryEventVar 0x3
    if lessthan _goto End
    @ TODO: Turn off barrier
    end

LevelScripts_DaimynCityGym:
    levelscript StoryEventVar 0x0 LevelScript_IntroduceChance
    levelscript StoryEventVar 0x1 LevelScript_ContinueCutsceneAfterChanceLeaves
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_IntroduceChance:
    applymovement Chance m_Joy
    msgbox gText_DaimynCityGym_Cutscene_ChanceLaughs MSG_NORMAL
    applymovement Chance m_ChanceMovesToMeetPlayer
    waitmovement Chance
    sound 0x15 @ Exclaim
    applymovement Chance m_Surprise
    msgbox gText_DaimynCityGym_Cutscene_ChanceSpotsPlayer MSG_NORMAL
    checkgender
    compare LASTRESULT 0x0 @ Male
    if equal _call ChanceAsksPlayerTheirIntentions_Male
    if notequal _call ChanceAsksPlayerTheirIntentions_Female
    msgbox gText_DaimynCityGym_Cutscene_ChanceAsksPlayersIntention MSG_KEEPOPEN
    multichoiceoption gText_DaimynCityGym_Cutscene_ChoiceGym 0
	multichoiceoption gText_DaimynCityGym_Cutscene_ChoiceSlots 1
	multichoiceoption gText_DaimynCityGym_Cutscene_ChoiceNeither 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, PlayerChoseGym
	case 1, PlayerChoseSlots
	case 2, PlayerChoseNeither
    end

ChanceAsksPlayerTheirIntentions_Male:
    msgbox gText_DaimynCityGym_Cutscene_ChanceAddressesMalePlayer MSG_NORMAL
    return

ChanceAsksPlayerTheirIntentions_Female:
    msgbox gText_DaimynCityGym_Cutscene_ChanceAddressesFemalePlayer MSG_NORMAL
    return

PlayerChoseGym:
    msgbox gText_DaimynCityGym_Cutscene_PlayerChoseGym MSG_NORMAL
    goto ChanceContinuesCutscene

PlayerChoseSlots:
    msgbox gText_DaimynCityGym_Cutscene_PlayerChoseSlots MSG_NORMAL
    goto ChanceContinuesCutscene

PlayerChoseNeither:
    msgbox gText_DaimynCityGym_Cutscene_PlayerChoseNeither MSG_NORMAL
    goto ChanceContinuesCutscene

ChanceContinuesCutscene:
    msgbox gText_DaimynCityGym_Cutscene_ChanceLeadsPlayerToDeskMan MSG_NORMAL
    applymovement Chance m_ChanceMovesToDesk
    applymovement PLAYER m_PlayerMovesToDesk
    waitmovement PLAYER
    msgbox gText_DaimynCityGym_Cutscene_ChanceAsksForCoins MSG_NORMAL
    msgbox gText_DaimynCityGym_Cutscene_DeskManResponds MSG_NORMAL
    obtainitem ITEM_COIN_CASE 0x1
    msgbox gText_DaimynCityGym_Cutscene_ChanceRespondsToDeskMan MSG_NORMAL
    applymovement Chance m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DaimynCityGym_Cutscene_ChanceExplainsTheGymRules MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Chance m_Surprise
    msgbox gText_DaimynCityGym_Cutscene_ChanceTakesHisLeave MSG_NORMAL
    applymovement Chance m_ChanceLeaves
    pause DELAY_1SECOND
    applymovement PLAYER m_LookDown
    waitmovement Chance
    getplayerpos 0x4000 0x4001 @ HACK: Move the player to the same map to force map transition script to fire
    warpmuted 9 18 0xFF 0x4000 0x4001 @ Warp to same spot in the gym
    setvar StoryEventVar 0x1
    end

LevelScript_ContinueCutsceneAfterChanceLeaves:
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    msgbox gText_DaimynCityGym_Cutscene_DeskManGives500Coins MSG_KEEPOPEN
    showcoins
    pause DELAY_HALFSECOND
    addcoins 500
    playse 248 @ SE Money
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    hidecoins
    msgbox gText_DaimynCityGym_Cutscene_DeskManExplainsCoins MSG_NORMAL
    applymovement PLAYER m_LookLeft
    applymovement DeskMan m_LookLeft
    msgbox gText_DaimynCityGym_Cutscene_DeskManExplainsPrizes MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement DeskMan m_LookDown
    msgbox gText_DaimynCityGym_Cutscene_DeskManExplainsPrizesAreLockedByGymLeader MSG_NORMAL
    applymovement PLAYER m_LookRight
    applymovement DeskMan m_LookRight
    msgbox gText_DaimynCityGym_Cutscene_DeskManExplainsCoinMachine MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement DeskMan m_LookDown
    msgbox gText_DaimynCityGym_Cutscene_DeskManConcludesExplaination MSG_NORMAL
    setvar StoryEventVar 0x2
    end

.global EventScript_DaimynCityGym_LeaderChance
EventScript_DaimynCityGym_LeaderChance:
    @ TODO
    end

.global EventScript_DaimynCityGym_CoinSeller
EventScript_DaimynCityGym_CoinSeller:
    showmoney 0x0 0x0
    showcoins 0x0 0x5
    msgbox gText_DaimynCityGym_CoinSeller_Welcome MSG_NORMAL
    checkmoney 0xA @ 10
    compare LASTRESULT FALSE
    if equal _goto CoinSellerGiveCoins
    // Check if player coin count is maxed out
    checkcoins 9999
    compare LASTRESULT TRUE
    if equal _goto CoinsSellerCaseFull
    msgbox gText_DaimynCityGym_CoinSeller_BuyCoinsPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto CoinSellerFarewell
    msgbox gText_DaimynCityGym_CoinSeller_CoinCountPrompt MSG_KEEPOPEN
    special 0xB3 @ Choose number, stored in LASTRESULT
    waitstate
    showmoney 0x0 0x0
    showcoins 0x0 0x5
    compare LASTRESULT 0x0
    if equal _goto CoinSellerFarewell
    copyvar 0x4001 LASTRESULT @ Selected coin count
    callasm CountCoinsIntoVar4002 @ Coins in players inventory
    setvar 0x4003 9999 @ Coin Case Limit
    setvar 0x4004 0xA @ Cost per coin 
    copyvar 0x4005 0x4001 @ The amount the player will buy
    setvar 0x8004 0x4001
    setvar 0x8005 0x4002
    special 0x3E @ Add two vars above
    comparevars 0x4001 0x4003
    if greaterthan _call ChoseTooManyCoins
    buffernumber 0x0 0x4005
    setvar 0x8004 0x4004
    setvar 0x8005 0x4005
    special 0x40 @ Multiply two numbers above
    buffernumber 0x1 0x4004
    msgbox gText_DaimynCityGym_CoinSeller_CoinPurchaseConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto CoinSellerFarewell
    copyvar 0x8004 0x4004 @ Copy value of 0x4004 (cost) into 0x8004
    callasm CheckMoneyFromVar @ Check if player has enough money
    compare LASTRESULT TRUE
    if notequal _goto CoinSeller_NotEnoughMoney
    playse 0xF8 @ Money
    callasm RemoveMoneyFromVar @ Removes based on var 0x8004 value
    updatemoney 0x0 0x0
    addcoins 0x4005
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    msgbox gText_DaimynCityGym_CoinSeller_PurchaseComplete MSG_NORMAL
    goto CoinSellerFarewell

ChoseTooManyCoins:
    copyvar 0x4001 0x4003 @ Copy max coins into requested coins
    setvar 0x8004 0x4001
    setvar 0x8005 0x4002
    special 0x3F @ Subtract excess coins from case max to get new total
    buffernumber 0x0 0x4001
    copyvar 0x4005 0x4001 @ The amount the player will buy
    msgbox gText_DaimynCityGym_CoinSeller_ChoseTooManyCoins MSG_YESNO
    compare LASTRESULT NO
    if equal _goto CoinSellerFarewell
    return

CoinSellerGiveCoins:
    checkcoins 1
    compare LASTRESULT TRUE
    if TRUE _goto CoinSeller_NotEnoughMoney @ Player has at least one coin, no gift
    msgbox gText_DaimynCityGym_CoinSeller_NoMoney MSG_NORMAL
    showcoins 0x0 0x5
    pause DELAY_HALFSECOND
    addcoins 10
    playse 248 @ SE Money
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    hidecoins
    goto CoinSellerFarewell

CoinsSellerCaseFull:
    msgbox gText_DaimynCityGym_CoinSeller_CoinCaseFull MSG_NORMAL
    goto CoinSellerFarewell

CoinSeller_NotEnoughMoney:
    msgbox gText_DaimynCityGym_CoinSeller_NotEnoughMoney MSG_NORMAL
    goto CoinSellerFarewell

CoinSellerFarewell:
    hidemoney
    hidecoins
    msgbox gText_DaimynCityGym_CoinSeller_Farewell MSG_NORMAL
    end

.global EventScript_DaimynCityGym_GymExpert
EventScript_DaimynCityGym_GymExpert:
    end

.global EventScript_DaimynCityGym_PokemonTrader
EventScript_DaimynCityGym_PokemonTrader:
    msgbox gText_DaimynCityGym_GenericTrader MSG_NORMAL
    msgbox gText_DaimynCityGym_PokemonTrader MSG_NORMAL
    @ checkflag 0x823 @ Received Chance's badge
    @ if NOT_SET _goto GeneralTraderDoNotHaveBadge
    goto PokemonTraderShopList

PokemonTraderShopList:
    msgbox gText_DaimynCityGym_GenericTrader_OpenShopPrompt MSG_KEEPOPEN
    showcoins 0x14 0x0
    setvar 0x8000 0x7 @ Pokemon exchange list
    setvar 0x8001 0x6 @ Show 6 at a time
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
    case 0, Joltik
    case 1, Mudbray
    case 2, Mankey
    case 3, Minior
    case 4, Turtonator
    case 5, Dratini
    case 6, DeclineTradeExchange
    case 0x7F, DeclineTradeExchange @ When player hits B to close
    end

Joltik:
    setvar 0x4001 SPECIES_JOLTIK
    setvar 0x4002 500
    goto PokemonTrader_AfterChoiceMade

Mudbray:
    setvar 0x4001 SPECIES_MUDBRAY
    setvar 0x4002 500
    goto PokemonTrader_AfterChoiceMade

Mankey:
    setvar 0x4001 SPECIES_MANKEY
    setvar 0x4002 500
    goto PokemonTrader_AfterChoiceMade

Minior:
    setvar 0x4001 SPECIES_MINIOR_SHIELD
    setvar 0x4002 1000
    goto PokemonTrader_AfterChoiceMade

Turtonator:
    setvar 0x4001 SPECIES_TURTONATOR
    setvar 0x4002 2000
    goto PokemonTrader_AfterChoiceMade

Dratini:
    setvar 0x4001 SPECIES_DRATINI
    setvar 0x4002 3000
    goto PokemonTrader_AfterChoiceMade

PokemonTrader_AfterChoiceMade:
    bufferpokemon 0x0 0x4001
    buffernumber 0x1 0x4002
    msgbox gText_DaimynCityGym_GenericTrader_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokemonTraderShopList
    checkcoins 0x4002
    compare LASTRESULT FALSE
    if TRUE _goto ItemTraderNotEnoughCoins
    playse 0xF8 @ Money
    removecoins 0x4002
    updatecoins 0x0 0x0
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    bufferpokemon 0x0 0x4001
    msgbox gText_DaimynCityGym_GenericTrader_PurchaseComplete MSG_NORMAL
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_DaimynCityGym_PokemonTrader_ReceivedPokemon MSG_KEEPOPEN
    waitfanfare
    countpokemon
    compare LASTRESULT 0x6
    if equal _call SentToBox
    if notequal _call SentToPary
    givepokemon 0x4001 20 ITEM_NONE
    hidecoins
    msgbox gText_DaimynCityGym_GenericTrader_ShopClosed MSG_NORMAL
    end

SentToBox:
    msgbox gText_DaimynCityGym_PokemonTrader_AddedToBox MSG_NORMAL
    return

SentToPary:
    msgbox gText_DaimynCityGym_PokemonTrader_AddedToParty MSG_NORMAL
    return

.global EventScript_DaimynCityGym_ItemTrader
EventScript_DaimynCityGym_ItemTrader:
    msgbox gText_DaimynCityGym_GenericTrader MSG_NORMAL
    msgbox gText_DaimynCityGym_ItemTrader MSG_NORMAL
    checkflag 0x823 @ Received Chance's badge
    if NOT_SET _goto GeneralTraderDoNotHaveBadge
    goto ItemTraderShopList

ItemTraderShopList:
    msgbox gText_DaimynCityGym_GenericTrader_OpenShopPrompt MSG_KEEPOPEN
    showcoins 0x14 0x0
    setvar 0x8000 0x6 @ Item exchange list
    setvar 0x8001 0x6 @ Show 6 at a time
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
    case 0, ToxicOrb
    case 1, FlameOrb
    case 2, LifeOrb
    case 3, AssaultVest
    case 4, FocusSash
    case 5, WeaknessPolicy
    case 6, ChoiceBand
    case 7, ChoiceSpecs
    case 8, ChoiceScarf
    case 9, Leftovers
    case 10, Eviolite
    case 11, DeclineTradeExchange
    case 0x7F, DeclineTradeExchange @ When player hits B to close
    end

ToxicOrb:
    setvar 0x4001 ITEM_TOXIC_ORB
    setvar 0x4002 1000
    goto ItemTrader_AfterChoiceMade

FlameOrb:
    setvar 0x4001 ITEM_FLAME_ORB
    setvar 0x4002 1000
    goto ItemTrader_AfterChoiceMade

LifeOrb:
    setvar 0x4001 ITEM_LIFE_ORB
    setvar 0x4002 2000
    goto ItemTrader_AfterChoiceMade

AssaultVest:
    setvar 0x4001 ITEM_ASSAULT_VEST
    setvar 0x4002 3000
    goto ItemTrader_AfterChoiceMade

FocusSash:
    setvar 0x4001 ITEM_FOCUS_SASH
    setvar 0x4002 2000
    goto ItemTrader_AfterChoiceMade

WeaknessPolicy:
    setvar 0x4001 ITEM_WEAKNESS_POLICY
    setvar 0x4002 2000
    goto ItemTrader_AfterChoiceMade

ChoiceBand:
    setvar 0x4001 ITEM_CHOICE_BAND
    setvar 0x4002 2500
    goto ItemTrader_AfterChoiceMade

ChoiceSpecs:
    setvar 0x4001 ITEM_CHOICE_SPECS
    setvar 0x4002 2500
    goto ItemTrader_AfterChoiceMade

ChoiceScarf:
    setvar 0x4001 ITEM_CHOICE_SCARF
    setvar 0x4002 2500
    goto ItemTrader_AfterChoiceMade

Leftovers:
    setvar 0x4001 ITEM_LEFTOVERS
    setvar 0x4002 3000
    goto ItemTrader_AfterChoiceMade

Eviolite:
    setvar 0x4001 ITEM_EVIOLITE
    setvar 0x4002 3000
    goto ItemTrader_AfterChoiceMade

ItemTrader_AfterChoiceMade:
    bufferitem 0x0 0x4001
    buffernumber 0x1 0x4002
    msgbox gText_DaimynCityGym_GenericTrader_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ItemTraderShopList
    checkcoins 0x4002
    compare LASTRESULT FALSE
    if TRUE _goto ItemTraderNotEnoughCoins
    playse 0xF8 @ Money
    removecoins 0x4002
    updatecoins 0x0 0x0
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    bufferitem 0x0 0x4001
    msgbox gText_DaimynCityGym_GenericTrader_PurchaseComplete MSG_KEEPOPEN
    fanfare 0x101 @ Got Item / Level up
    obtainitem 0x4001 0x1
    hidecoins
    msgbox gText_DaimynCityGym_GenericTrader_ShopClosed MSG_NORMAL
    end

ItemTraderNotEnoughCoins:
    msgbox gText_DaimynCityGym_GenericTrader_NotEnoughCoins MSG_NORMAL
    goto ItemTraderShopList

DeclineTradeExchange:
    hidecoins
    msgbox gText_DaimynCityGym_GenericTrader_Declined MSG_NORMAL
    end

GeneralTraderDoNotHaveBadge:    
    msgbox gText_DaimynCityGym_GenericTrader_DoNotHaveBadge MSG_NORMAL
    end

TrainerCoinPayout:
    setvar 0x4002 0xA @ mult by 10
    setvar 0x8004 0x4001
    setvar 0x8005 0x4002
    special 0x40 @ Multiply two numbers above
    showcoins
    buffernumber 0x0 0x4001
    msgbox gText_DaimynCityGym_TrainerCoinPayout MSG_KEEPOPEN
    pause DELAY_HALFSECOND
    addcoins 0x4001
    playse 248 @ SE Money
    updatecoins
    waitse
    pause DELAY_HALFSECOND
    hidecoins
    end

.global EventScript_DaimynCityGym_YoungsterJacob
EventScript_DaimynCityGym_YoungsterJacob:
    setvar 0x4001 23
    trainerbattle2 0x0 0x93 0x0 gText_DaimynCityGym_YoungsterJacob_Intro gText_DaimynCityGym_YoungsterJacob_Defeat TrainerCoinPayout
    msgbox gText_DaimynCityGym_YoungsterJacob_Chat MSG_NORMAL
    end

.global EventScript_DaimynCityGym_PokefanKanesha
EventScript_DaimynCityGym_PokefanKanesha:
    end

.global EventScript_DaimynCityGym_BeautyEmilie
EventScript_DaimynCityGym_BeautyEmilie:
    end

.global EventScript_DaimynCityGym_BeautyLeanne
EventScript_DaimynCityGym_BeautyLeanne:
    end

.global EventScript_DaimynCityGym_ChanellerRosita
EventScript_DaimynCityGym_ChanellerRosita:
    end

.global EventScript_DaimynCityGym_GamblerChuck
EventScript_DaimynCityGym_GamblerChuck:
    end

.global EventScript_DaimynCityGym_BurglarDexter
EventScript_DaimynCityGym_BurglarDexter:
    end

.global EventScript_DaimynCityGym_NPCWoman
EventScript_DaimynCityGym_NPCWoman:
    end

.global EventScript_DaimynCityGym_NPCPsychic
EventScript_DaimynCityGym_NPCPsychic:
    end

.global EventScript_DaimynCityGym_NPCFatGuy
EventScript_DaimynCityGym_NPCFatGuy:
    end

.global EventScript_DaimynCityGym_NPCRocker
EventScript_DaimynCityGym_NPCRocker:
    end

.global EventScript_DaimynCityGym_NPCBlackBelt
EventScript_DaimynCityGym_NPCBlackBelt:
    end

.global EventScript_DaimynCityGym_Gentleman
EventScript_DaimynCityGym_Gentleman:
    end

.global SignScript_DaimynCityGym_GymPlacard
SignScript_DaimynCityGym_GymPlacard:
    end

.global SignScript_DaimynCityGym_CoinDepositBox
SignScript_DaimynCityGym_CoinDepositBox:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds1
SignScript_DaimynCityGym_SlotMachine_Odds1:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds2
SignScript_DaimynCityGym_SlotMachine_Odds2:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds3
SignScript_DaimynCityGym_SlotMachine_Odds3:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds4
SignScript_DaimynCityGym_SlotMachine_Odds4:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds5
SignScript_DaimynCityGym_SlotMachine_Odds5:
    end

.global SignScript_DaimynCityGym_SlotMachine_Odds6
SignScript_DaimynCityGym_SlotMachine_Odds6:
    end

m_ChanceMovesToMeetPlayer: .byte walk_right, walk_right, walk_down, walk_down, end_m
m_ChanceMovesToDesk: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, look_up, end_m
m_PlayerMovesToDesk: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, look_up, end_m
m_ChanceLeaves: .byte walk_down, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
