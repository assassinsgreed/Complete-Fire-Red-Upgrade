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
