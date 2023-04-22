.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_RivalEvent1
EventScript_RivalEvent1:
    lock
    faceplayer
    checkflag 0x2C0
    IF SET _goto RivalEvent1_ThankPlayer
    msgbox gText_RivalEvent1_RequestPokeballs MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto RivalEvent1_Declined
    checkitem ITEM_POKE_BALL 0x5
    compare LASTRESULT TRUE
    IF FALSE _goto RivalEvent1_NotEnoughPokeballs
    showmoney 0x0 0x0
    msgbox gText_RivalEvent1_GiveMoney MSG_NORMAL
    removeitem ITEM_POKE_BALL 0x5
    addmoney 0x5DC @ 1,500 Pokedollars
    updatemoney 0x0 0x0
    sound 0xF8 @ Money SE
    waitse
    setflag 0x2C0
    call RivalEvent1_ThankPlayer

RivalEvent1_Declined:
    msgbox gText_RivalEvent1_Declined MSG_NORMAL
    call RivalEvent1_ResetPosition

RivalEvent1_NotEnoughPokeballs:
    msgbox gText_RivalEvent1_NotEnoughPokeballs MSG_NORMAL
    call RivalEvent1_ResetPosition

RivalEvent1_ThankPlayer:
    hidemoney
    msgbox gText_RivalEvent1_ThankPlayer MSG_NORMAL
    call RivalEvent1_ResetPosition

RivalEvent1_ResetPosition:
    applymovement LASTTALKED m_LookRight
    release
    end

.global EventScript_RivalEvent2
EventScript_RivalEvent2:
    lock
    faceplayer
    checkflag 0x2C1
    if SET _goto RivalEvent2_ThankPlayer
    msgbox gText_RivalEvent2_RequestRevive MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto RivalEvent2_Declined
    checkitem ITEM_REVIVE 0x1
    compare LASTRESULT TRUE
    IF FALSE _goto RivalEvent2_NotEnoughRevives
    removeitem ITEM_REVIVE 0x1
    msgbox gText_RivalEvent2_GiveRevive MSG_NORMAL
    obtainitem ITEM_ULTRA_BALL 0x3
    setflag 0x2C1
    goto RivalEvent2_ThankPlayer

RivalEvent2_Declined:
    msgbox gText_RivalEvent2_Declined MSG_NORMAL
    goto End

RivalEvent2_NotEnoughRevives:
    msgbox gText_RivalEvent2_NotEnoughRevives MSG_NORMAL
    goto End

RivalEvent2_ThankPlayer:
    msgbox gText_RivalEvent2_EventComplete MSG_NORMAL
    goto End

.global EventScript_RivalEvent3
EventScript_RivalEvent3:
    lock
    faceplayer
    checkflag 0x2C2 @ Traded with Rival
    if SET _goto RivalEvent3_TradeConcluded
    msgbox gText_RivalEvent3_RequestEgg MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RivalEvent3_Declined
    msgbox gText_RivalEvent3_ChooseEgg MSG_NORMAL
    special 0x9F @ Select a Pokemon and store it's position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if user backed out
    if greaterorequal _goto RivalEvent3_BackedOutOnEgg
    callasm StoreIsPartyMonEgg
    compare LASTRESULT TRUE
    if FALSE _goto RivalEvent3_DidNotSelectEgg
    msgbox gText_RivalEvent3_ConfirmEggChoice MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RivalEvent3_BackedOutOnEgg
    special 0x62 @ Remove egg from party
    msgbox gText_RivalEvent3_AcceptedEggChoice MSG_NORMAL
    pause DELAY_1SECOND
    playse 0x35 @ SE Pokeball trade
    pause DELAY_1SECOND
    fanfare 0x101 @ Fanfare 1
    msgbox gText_RivalEvent3_EggTradeCompleted MSG_NORMAL
    waitfanfare
    random 0x3 @ Random between 0 and 3
    compare LASTRESULT 0x0
    if equal _call RivalEvent3_SetLitleoEgg
    compare LASTRESULT 0x1
    if equal _call RivalEvent3_SetShellosEgg
    compare LASTRESULT 0x2
    if equal _call RivalEvent3_SetScraggyEgg
    callasm GiveCustomEgg
    setflag 0x2C2 @ Traded with Rival
    goto RivalEvent3_TradeConcluded

RivalEvent3_Declined:
    msgbox gText_RivalEvent3_Declined MSG_NORMAL
    goto End

RivalEvent3_DidNotSelectEgg:
    msgbox gText_RivalEvent3_DidNotChooseEgg MSG_NORMAL
    goto End

RivalEvent3_BackedOutOnEgg:
    msgbox gText_RivalEvent3_RejectedEggChoice MSG_NORMAL
    goto End

RivalEvent3_SetLitleoEgg:
    setvar 0x8005 SPECIES_LITLEO
    setvar 0x8006 0x8
    return

RivalEvent3_SetShellosEgg:
    setvar 0x8005 SPECIES_SHELLOS
    setvar 0x8006 0x9
    return

RivalEvent3_SetScraggyEgg:
    setvar 0x8005 SPECIES_SCRAGGY
    setvar 0x8006 0xA
    return

RivalEvent3_TradeConcluded:
    applymovement 0x4 m_Joy
    msgbox gText_RivalEvent3_EggTradeConcluded MSG_NORMAL
    goto End
