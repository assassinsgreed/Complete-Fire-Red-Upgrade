.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_HeleoFacilities_Mart_PokeballShop
EventScript_HeleoFacilities_Mart_PokeballShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart HeleoPokemart_PokeballStock
    goto EventScript_EndMart

HeleoPokemart_PokeballStock:
    .hword ITEM_HEAL_BALL
    .hword ITEM_NEST_BALL
    .hword ITEM_NET_BALL
    .hword ITEM_REPEAT_BALL
    .hword ITEM_DUSK_BALL
    .hword ITEM_QUICK_BALL
    .hword ITEM_TIMER_BALL
    .hword ITEM_NONE