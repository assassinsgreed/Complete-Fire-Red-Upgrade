.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_StarterChoice_Main
EventScript_StarterChoice_Main:
	lock
	@ Grass starter
	compare 0x4011 0x0
	if equal _call EventScript_StarterChoice_SetBulbasaur
	compare 0x4011 0x1
	if equal _call EventScript_StarterChoice_SetChikorita
	compare 0x4011 0x2
	if equal _call EventScript_StarterChoice_SetTreecko
	compare 0x4011 0x3
	if equal _call EventScript_StarterChoice_SetTurtwig
	compare 0x4011 0x4
	if equal _call EventScript_StarterChoice_SetSnivy
	compare 0x4011 0x5
	if equal _call EventScript_StarterChoice_SetChespin
	compare 0x4011 0x6
	if equal _call EventScript_StarterChoice_SetRowlet
	compare 0x4011 0x7
	if equal _call EventScript_StarterChoice_SetGrookey

	bufferpokemon 0x0 0x4000
	showpokepic 0x4000
	msgbox gText_StarterChoice_Confirmation MSG_YESNO
	hidepokepic
	compare LASTRESULT YES
	IF FALSE _call EventScript_StarterChoice_Declined
	givepokemon 0x4000 0x5 0x0 0x0 0x0 0x0
	msgbox gText_StarterChoice_Confirmed MSG_KEEPOPEN
	@ Hide corresponding pokeball
	waitmsg
	fanfare 0x13E
	waitfanfare
	msgbox gText_StarterChoice_Nickname MSG_YESNO
	compare LASTRESULT YES
	if TRUE _call EventScript_StarterChoice_Nickname
	bufferpartypokemon 0x0 0x0
	msgbox gText_StarterChoice_Finalized MSG_NORMAL
	setflag 0x828 @ Enable Pokemon Menu
	release
	end

	@@ Fire starter
	@ compare 0x4012 0x0
	@ if equal _call EventScript_StarterChoice_SetCharmander
	@ compare 0x4012 0x1
	@ if equal _call EventScript_StarterChoice_SetCyndaquil
	@ compare 0x4012 0x2
	@ if equal _call EventScript_StarterChoice_SetTorchic
	@ compare 0x4012 0x3
	@ if equal _call EventScript_StarterChoice_SetChimchar
	@ compare 0x4012 0x4
	@ if equal _call EventScript_StarterChoice_SetTepig
	@ compare 0x4012 0x5
	@ if equal _call EventScript_StarterChoice_SetFennekin
	@ compare 0x4012 0x6
	@ if equal _call EventScript_StarterChoice_SetLitten
	@ compare 0x4012 0x7
	@ if equal _call EventScript_StarterChoice_SetScorbunny

	@ @ Water starter
	@ compare 0x4013 0x0
	@ if equal _call EventScript_StarterChoice_SetSquirtle
	@ compare 0x4013 0x1
	@ if equal _call EventScript_StarterChoice_SetTotodile
	@ compare 0x4013 0x2
	@ if equal _call EventScript_StarterChoice_SetMudkip
	@ compare 0x4013 0x3
	@ if equal _call EventScript_StarterChoice_SetPiplup
	@ compare 0x4013 0x4
	@ if equal _call EventScript_StarterChoice_SetOshawott
	@ compare 0x4013 0x5
	@ if equal _call EventScript_StarterChoice_SetFroakie
	@ compare 0x4013 0x6
	@ if equal _call EventScript_StarterChoice_SetPopplio
	@ compare 0x4013 0x7
	@ if equal _call EventScript_StarterChoice_SetSobble

	@ showpokepic 0x4001
	@ showpokepic 0x4002
	end

EventScript_StarterChoice_Declined:
	msgbox gText_StarterChoice_Decline MSG_NORMAL
	release
	end

EventScript_StarterChoice_Nickname:
	setvar 0x8004 0x0
	fadescreen 0x1
	special 0x9E
	waitstate
	return

EventScript_StarterChoice_SetBulbasaur:
	setvar 0x4000 SPECIES_BULBASAUR
	return

EventScript_StarterChoice_SetChikorita:
	setvar 0x4000 SPECIES_CHIKORITA
	return

EventScript_StarterChoice_SetTreecko:
	setvar 0x4000 SPECIES_TREECKO
	return

EventScript_StarterChoice_SetTurtwig:
	setvar 0x4000 SPECIES_TURTWIG
	return

EventScript_StarterChoice_SetSnivy:
	setvar 0x4000 SPECIES_SNIVY
	return

EventScript_StarterChoice_SetChespin:
	setvar 0x4000 SPECIES_CHESPIN
	return

EventScript_StarterChoice_SetRowlet:
	setvar 0x4000 SPECIES_ROWLET
	return

EventScript_StarterChoice_SetGrookey:
	setvar 0x4000 SPECIES_GROOKEY
	return

EventScript_StarterChoice_SetCharmander:
	setvar 0x4001 SPECIES_CHARMANDER
	return

EventScript_StarterChoice_SetCyndaquil:
	setvar 0x4001 SPECIES_CYNDAQUIL
	return

EventScript_StarterChoice_SetTorchic:
	setvar 0x4001 SPECIES_TORCHIC
	return

EventScript_StarterChoice_SetChimchar:
	setvar 0x4001 SPECIES_CHIMCHAR
	return

EventScript_StarterChoice_SetTepig:
	setvar 0x4001 SPECIES_TEPIG
	return

EventScript_StarterChoice_SetFennekin:
	setvar 0x4001 SPECIES_FENNEKIN
	return

EventScript_StarterChoice_SetLitten:
	setvar 0x4001 SPECIES_LITTEN
	return

EventScript_StarterChoice_SetScorbunny:
	setvar 0x4001 SPECIES_SCORBUNNY
	return

EventScript_StarterChoice_SetSquirtle:
	setvar 0x4002 SPECIES_SQUIRTLE
	return

EventScript_StarterChoice_SetTotodile:
	setvar 0x4002 SPECIES_TOTODILE
	return

EventScript_StarterChoice_SetMudkip:
	setvar 0x4002 SPECIES_MUDKIP
	return

EventScript_StarterChoice_SetPiplup:
	setvar 0x4002 SPECIES_PIPLUP
	return

EventScript_StarterChoice_SetOshawott:
	setvar 0x4002 SPECIES_OSHAWOTT
	return

EventScript_StarterChoice_SetFroakie:
	setvar 0x4002 SPECIES_FROAKIE
	return

EventScript_StarterChoice_SetPopplio:
	setvar 0x4002 SPECIES_POPPLIO
	return

EventScript_StarterChoice_SetSobble:
	setvar 0x4002 SPECIES_SOBBLE
	return
