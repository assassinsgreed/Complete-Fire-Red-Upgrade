.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoFacilities_PokemonCenter
MapScript_HeleoFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x05 @ Originally Lavender Town
    end

.global EventScript_HeleoFacilities_BoredKid
EventScript_HeleoFacilities_BoredKid:
    msgbox gText_HeleoCityFacilities_BoredKid MSG_NORMAL
    end

.global EventScript_HeleoFacilities_KidsMom
EventScript_HeleoFacilities_KidsMom:
    npcchat gText_HeleoCityFacilities_KidsMom
    end

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

.global EventScript_HeleoFacilities_Mart_QuickTimerBallQuiz
EventScript_HeleoFacilities_Mart_QuickTimerBallQuiz:
    lock
    faceplayer
    msgbox gText_HeleoCityFacilities_QuickTimerBallQuiz MSG_YESNO
    msgbox gText_HeleoCityFacilities_QuickTimerBallAnswer MSG_NORMAL
    checkflag 0x247 @ Received Quick and Timer ball gift
    if NOT_SET _goto QuickTimerBallGift
    goto End

QuickTimerBallGift:
    msgbox gText_HeleoCityFacilities_QuickTimerBallGift MSG_NORMAL
    obtainitem ITEM_QUICK_BALL 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_TIMER_BALL 0x1
    setflag 0x247 @ Received Quick and Timer ball gift
    goto End
