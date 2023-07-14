.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_FerroxNPCHouses_SmallestVillage
EventScript_FerroxNPCHouses_SmallestVillage:
    npcchat2 0x1 m_LookRight gText_FerroxNPCHouses_SmallestVillage
    end

.global EventScript_FerroxNPCHouses_DailyBerry
EventScript_FerroxNPCHouses_DailyBerry:
    lock
    faceplayer
    checkflag 0xE06
    if SET _goto BerryGirlEnd
    msgbox gText_FerroxNPCHouses_BerryGirl_FreeBerry MSG_NORMAL
    random 0xA
    addvar LASTRESULT 0x85 @ Cheri Berry to Sitrus Berry
    obtainitem LASTRESULT 0x1 
    setflag 0xE06
    goto BerryGirlEnd

BerryGirlEnd:
    msgbox gText_FerroxNPCHouses_BerryGirl_ComeBackTomorrow MSG_NORMAL
    release
    end

.global EventScript_FerroxNPCHouses_MoveTutor
EventScript_FerroxNPCHouses_MoveTutor:
    lock
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_FerroxNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_FerroxNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Ferrox
    msgbox gText_FerroxNPCHouses_Complete MSG_NORMAL
    release
    end

TutoringRejected:
    msgbox gText_FerroxNPCHouses_TutoringRejected MSG_NORMAL
    release
    end

NotEnoughPokeChips:
    msgbox gText_FerroxNPCHouses_NotEnoughPokeChips MSG_NORMAL
    release
    end

.global EventScript_FerroxNPCHouses_TutorsInTowns
EventScript_FerroxNPCHouses_TutorsInTowns:
    npcchat gText_FerroxNPCHouses_TutorsInTowns
    end

.global EventScript_FerroxNPCHouses_TradeGirlDad
EventScript_FerroxNPCHouses_TradeGirlDad:
    npcchat2 0x1 m_LookRight gText_FerroxNPCHouses_TradeGirlDad
    end

.global EventScript_FerroxNPCHouses_ChinchouTrade
EventScript_FerroxNPCHouses_ChinchouTrade:
    lock
    faceplayer
    checkflag 0x248
    if SET _goto EventScript_ChinchouTradeComplete
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Request MSG_YESNO
    compare LASTRESULT NO
    if TRUE _goto EventScript_ChinchouTradeDeclined
    // Set up vars needed for trade
    copyvar 0x8004 0x8008
    special2 LASTRESULT 0xFC // Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    setvar 0x8004 0x0 @ Set Trade #0 (Chinchou)
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto EventScript_ChinchouTradeDeclined
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto EventScript_ChinchouTradeWrongPokemon
    msgbox gText_FerroxNPCHouses_ChinchouTrade_InitiatingTrade MSG_NORMAL
    call InitiateTrade
    setflag 0x248
    goto EventScript_ChinchouTradeComplete

EventScript_ChinchouTradeDeclined:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Declined MSG_NORMAL
    goto End

EventScript_ChinchouTradeWrongPokemon:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_WrongPokemon MSG_NORMAL
    goto End

EventScript_ChinchouTradeComplete:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Complete MSG_NORMAL
    goto End
