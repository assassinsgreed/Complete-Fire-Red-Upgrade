.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Tutors_Terrain
EventScript_Tutors_Terrain:
    multichoiceoption gText_GrassyTerrain 0
	multichoiceoption gText_MistyTerrain 1
	multichoiceoption gText_ElectricTerrain 2
	multichoiceoption gText_PsychicTerrain 3
    multichoiceoption gText_End 4
	multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, grassyterrain
	case 1, mistyterrain
	case 2, electricterrain
	case 3, psychicterrain
    case 4, cancelled
    compare LASTRESULT FALSE
    if TRUE _goto cancelled
    return

grassyterrain:
    setvar 0x8005 0x3C
    call teachmove
    return

mistyterrain:
    setvar 0x8005 0x3D
    call teachmove
    return

electricterrain:
    setvar 0x8005 0x3E
    call teachmove
    return

psychicterrain:
    setvar 0x8005 0x3F
    call teachmove
    return

teachmove:
    special 0x18D
    waitstate
    compare LASTRESULT NO
    if TRUE _goto cancelled @ Pokemon couldn't learn move, or player cancelled
    removemoney 0x3E8 @ 1000 Pokedollars
    sound 0x40 @ Cash Register SE
    return

cancelled:
    return
