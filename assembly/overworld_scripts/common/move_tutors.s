.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Vars are set to the tutor number in hex.  Ex #63, psychic terrain, is 0x3F

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
    return

grassyterrain:
    setvar 0x8005 0x3C
    call teach5ChipMove
    return

mistyterrain:
    setvar 0x8005 0x3D
    call teach5ChipMove
    return

electricterrain:
    setvar 0x8005 0x3E
    call teach5ChipMove
    return

psychicterrain:
    setvar 0x8005 0x3F
    call teach5ChipMove
    return

.global EventScript_Tutors_Ferrox
EventScript_Tutors_Ferrox:
    setvar 0x8000 0x0
    setvar 0x8001 0x5
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, snore
	case 1, worryseed
	case 2, covet
	case 3, gravity
    case 4, telekinesis
	case 5, icywind
	case 6, gastroacid
	case 7, afteryou
    case 8, cancelled
    return

snore:
    setvar 0x8005 0x3
    call teach5ChipMove
    return

worryseed:
    setvar 0x8005 0xB
    call teach5ChipMove
    return

covet:
    setvar 0x8005 0xC
    call teach5ChipMove
    return

gravity:
    setvar 0x8005 0x13
    call teach5ChipMove
    return

telekinesis:
    setvar 0x8005 0x15
    call teach5ChipMove
    return

icywind:
    setvar 0x8005 0x1E
    call teach5ChipMove
    return

gastroacid:
    setvar 0x8005 0x28
    call teach5ChipMove
    return

afteryou:
    setvar 0x8005 0x10
    call teach5ChipMove
    return

teach5ChipMove:
    call teachmove
    removeitem ITEM_POKE_CHIP 0x5
    return

teachmove:
    special 0x18D
    waitstate
    compare LASTRESULT NO
    if TRUE _goto cancelled @ Pokemon couldn't learn move, or player cancelled
    sound 0x40 @ Cash Register SE
    return

cancelled:
    return
