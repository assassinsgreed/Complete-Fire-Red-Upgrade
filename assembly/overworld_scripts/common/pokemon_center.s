.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_PokemonCenter_Main
EventScript_PokemonCenter_Main:
    lock
    faceplayer
    special 0x187
	compare LASTRESULT 0x2
	if TRUE _goto EventScript_PokemonCenter_End
    msgbox gText_Common_PokemonCenterHealChoice MSG_YESNO
	compare LASTRESULT YES
	if TRUE _goto EventScript_PokemonCenter_Heal
	goto EventScript_PokemonCenter_Farewell
	goto EventScript_PokemonCenter_End

EventScript_PokemonCenter_End:
	release
	end

EventScript_PokemonCenter_Heal:
	msgbox gText_Common_PokemonCenterTakePokemon MSG_KEEPOPEN
	applymovement LASTTALKED m_NurseLookLeft
	waitmovement 0x0
	doanimation 0x19
	waitanimation 0x19
	applymovement LASTTALKED m_NurseLookDown
	waitmovement 0x0
	special 0x0
	special 0x169
	special2 LASTRESULT 0x1B1
	compare LASTRESULT TRUE
	if TRUE _goto EventScript_PokemonCenter_HealComplete
	special2 LASTRESULT 0x183
	copyvar 0x8008 LASTRESULT
	compare 0x8008 TRUE
	if TRUE _goto EventScript_PokemonCenter_HealComplete
	end

EventScript_PokemonCenter_Farewell:
	msgbox gText_Common_PokemonFarewell MSG_NORMAL
	return

EventScript_PokemonCenter_HealComplete:
	incrementgamestat 15
	msgbox gText_Common_PokemonCenterHealed MSG_NORMAL
	applymovement LASTTALKED m_NurseBow
	waitmovement 0x0
	call EventScript_PokemonCenter_Farewell
    return

@ Movements
m_NurseLookLeft:
.byte walk_left_onspot_fastest, end_m

m_NurseLookDown:
.byte walk_down_onspot_fastest, end_m

m_NurseBow:
.byte nurse_bow, pause_short, end_m
