.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DaimynCityNPCHouses_SuspiciousMan1
EventScript_DaimynCityNPCHouses_SuspiciousMan1:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan1
    end

.global EventScript_DaimynCityNPCHouses_SuspiciousMan2
EventScript_DaimynCityNPCHouses_SuspiciousMan2:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan2
    end

.global EventScript_DaimynCity_MoveTutor
EventScript_DaimynCity_MoveTutor:
    lock
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_DaimynNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    loadpointer 0x0 gText_DaimynNPCHouses_Complete
    call EventScript_Tutors_Daimyn
    release
    end

TutoringRejected:
    msgbox gText_DaimynNPCHouses_TutoringRejected MSG_NORMAL
    goto End

NotEnoughPokeChips:
    msgbox gText_DaimynNPCHouses_NotEnoughPokeChips MSG_NORMAL
    goto End

.global EventScript_DaimynCityNPCHouses_TutorsDaughter
EventScript_DaimynCityNPCHouses_TutorsDaughter:
    npcchat gText_DaimynCityNPCHouses_TutorsDaughter
    end

.global EventScript_DaimynCityNPCHouses_TutorsSon
EventScript_DaimynCityNPCHouses_TutorsSon:
    npcchat gText_DaimynCityNPCHouses_TutorsSon
    end

.global EventScript_DaimynCity_FindTM46Thief
EventScript_DaimynCity_FindTM46Thief:
    setvar CHOSEN_ITEM ITEM_TM46
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynCityNPCHouses_OldTrainer
EventScript_DaimynCityNPCHouses_OldTrainer:
    lock
    faceplayer
    checkflag 0x040 @ Pikachu gift received
    if SET _goto OldTrainer_GiftReceived
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Intro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto OldTrainer_Denied
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Grateful MSG_NORMAL
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto OldTrainer_NoSpace
    applymovement 0x1 m_LookLeft
    applymovement 0x2 m_LookRight
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuGiven MSG_NORMAL
    cry SPECIES_PIKACHU 0x0
    msgbox gText_DaimynCityNPCHouses_PikachuJoins MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA @ Above or below
    if equal _call MovePikachuAboveBelow
    compare 0x4000 0xA @ Above or below
    if notequal _call MovePikachuBeside
    playse 0x10 @ Pokeball closes
    pause DELAY_HALFSECOND
    hidesprite 0x2
    setflag 0x040 @ Pikachu gift received
    fanfare 0x101
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuObtained MSG_KEEPOPEN
    waitfanfare
    setvar 0x8000 MOVE_VOLTTACKLE
    setvar 0x8001 MOVE_IRONTAIL
    setvar 0x8002 MOVE_ELECTROBALL
    setvar 0x8003 MOVE_QUICKATTACK
    setvar 0x8004 0x0 @ Ingame gift 0, Pikachu
    setvar 0x8005 0x1E @ Level 30
    callasm CreateInGameGiftPokemon
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA @ Above or below
    if equal _call PlayerFaceOldManAboveBelow
    compare 0x4000 0xA @ Above or below
    if notequal _call PlayerFaceOldManBeside
    waitmovement PLAYER
    faceplayer
    goto OldTrainer_GiftReceived
    end

OldTrainer_NoSpace:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_NoSpace MSG_NORMAL
    release
    end

MovePikachuAboveBelow:
    compare 0x4001 0x4
    if equal _call MovePikachuAbove
    if notequal _call MovePikachuBelow
    return

MovePikachuBelow:
    applymovement 0x2 m_PikachuWalksToPlayer_Below
    waitmovement 0x2
    applymovement PLAYER m_LookDown
    return

MovePikachuAbove:
    applymovement 0x2 m_PikachuWalksToPlayer_Above
    waitmovement 0x2
    applymovement PLAYER m_LookLeft
    return

MovePikachuBeside:
    applymovement 0x2 m_PikachuWalksToPlayer_Beside
    waitmovement 0x2
    applymovement PLAYER m_LookDown
    return

PlayerFaceOldManAboveBelow:
    compare 0x4001 0x4
    if equal _call LookDown
    if notequal _call LookUp
    return

PlayerFaceOldManBeside:
    applymovement PLAYER m_LookLeft
    return

OldTrainer_GiftReceived:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuAlreadyGifted MSG_NORMAL
    release
    end

OldTrainer_Denied:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Denied MSG_NORMAL
    release
    end

.global EventScript_DaimynCityNPCHouses_Pikachu
EventScript_DaimynCityNPCHouses_Pikachu:
    lock
    faceplayer
    cry SPECIES_PIKACHU 0x0
    msgbox gText_DaimynCityNPCHouses_Pikachu MSG_NORMAL
    release
    end

.global EventScript_DaimynCityNPCHouses_TradeBuddy
EventScript_DaimynCityNPCHouses_TradeBuddy:
    npcchat gText_DaimynCityNPCHouses_TraderBuddy
    end

.global EventScript_DaimynCityNPCHouses_Trader
EventScript_DaimynCityNPCHouses_Trader:
    lock
    faceplayer
    checkflag 0x254 @ Did starter based trade
    if SET _goto DaimynTradeComplete
    msgbox gText_DaimynCityNPCHouses_TraderIntro MSG_NORMAL
    switch 0x408D @ Fire starter generation
    case 0, TradeRequestMrMime
    case 1, TradeRequestDratini
    case 2, TradeRequestCorsolaG
    case 3, TradeRequestFrillishF
    case 4, TradeRequestEmolga
    case 5, TradeRequestEevee
    case 6, TradeRequestNoibat
    case 7, TradeRequestHatenna
    end

TradeRequestMrMime:
    msgbox gText_DaimynCityNPCHouses_TraderRequestMrMime MSG_YESNO
    setvar 0x8008 0x1 @ Give mon in slot 1 (Mr Mime-G)
    goto HandleTrade

TradeRequestDratini:
    msgbox gText_DaimynCityNPCHouses_TraderRequestDratini MSG_YESNO
    setvar 0x8008 0x2 @ Give mon in slot 2 (Dratini)
    goto HandleTrade

TradeRequestCorsolaG:
    msgbox gText_DaimynCityNPCHouses_TraderRequestCorsola MSG_YESNO
    setvar 0x8008 0x3 @ Give mon in slot 3 (Corsola-G)
    goto HandleTrade

TradeRequestFrillishF:
    msgbox gText_DaimynCityNPCHouses_TraderRequestFrillish MSG_YESNO
    setvar 0x8008 0x4 @ Give mon in slot 4 (Frillish)
    goto HandleTrade

TradeRequestEmolga:
    msgbox gText_DaimynCityNPCHouses_TraderRequestEmolga MSG_YESNO
    setvar 0x8008 0x5 @ Give mon in slot 5 (Emolga)
    goto HandleTrade

TradeRequestEevee:
    msgbox gText_DaimynCityNPCHouses_TraderRequestEevee MSG_YESNO
    setvar 0x8008 0x6 @ Give mon in slot 6 (Eevee)
    goto HandleTrade

TradeRequestNoibat:
    msgbox gText_DaimynCityNPCHouses_TraderRequestNoibat MSG_YESNO
    setvar 0x8008 0x7 @ Give mon in slot 7 (Noibat)
    goto HandleTrade

TradeRequestHatenna:
    msgbox gText_DaimynCityNPCHouses_TraderRequestHatenna MSG_YESNO
    setvar 0x8008 0x8 @ Give mon in slot 8 (Hatenna)
    goto HandleTrade

HandleTrade:
    copyvar 0x8004 0x8008 @ Copy expected mon from same trade slot as given mon
    compare LASTRESULT NO
    if TRUE _goto TradeRejected
    special2 LASTRESULT 0xFC // Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto TradeRejected
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto TraderWrongPokemon
    msgbox gText_DaimynCityNPCHouses_TraderTradeInitiated MSG_NORMAL
    call InitiateTrade
    goto DaimynTradeComplete

TradeRejected:
    msgbox gText_DaimynCityNPCHouses_TraderRejected MSG_NORMAL
    release
    end

TraderWrongPokemon:
    msgbox gText_DaimynCityNPCHouses_TraderWrongPokemon MSG_NORMAL
    release
    end

DaimynTradeComplete:
    setflag 0x254 @ Did starter based trade
    msgbox gText_DaimynCityNPCHouses_TraderTradeComplete MSG_NORMAL
    release
    end

m_PikachuWalksToPlayer_Below: .byte walk_down, walk_down, walk_right, walk_right, walk_right, look_up, end_m
m_PikachuWalksToPlayer_Above: .byte walk_up, walk_right, walk_right, end_m
m_PikachuWalksToPlayer_Beside: .byte walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_up, end_m
