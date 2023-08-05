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
    setvar 0x8004 0x0
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
    case 0x7F, cancelled @ When player hit B to close
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

.global EventScript_Tutors_Heleo
EventScript_Tutors_Heleo:
    setvar 0x8000 0x1
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, grasspledge
	case 1, firepledge
	case 2, waterpledge
	case 3, lowkick
    case 4, bind
	case 5, block
	case 6, laserfocus
	case 7, uproar
    case 8, cancelled
    case 0x7F, cancelled @ When player hit B to close

grasspledge:
    setvar 0x8005 0x35
    call teach5ChipMove
    return

firepledge:
    setvar 0x8005 0x36
    call teach5ChipMove
    return

waterpledge:
    setvar 0x8005 0x37
    call teach5ChipMove
    return

lowkick:
    setvar 0x8005 0x6
    call teach5ChipMove
    return

bind:
    setvar 0x8005 0x8
    call teach5ChipMove
    return

block:
    setvar 0x8005 0xA
    call teach5ChipMove
    return

laserfocus:
    setvar 0x8005 0x21
    call teach5ChipMove
    return

uproar:
    setvar 0x8005 0x7
    call teach5ChipMove
    return

.global EventScript_Tutors_Daimyn
EventScript_Tutors_Daimyn:
    setvar 0x8000 0x4
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, FirePunch
	case 1, IcePunch
	case 2, ThunderPunch
	case 3, HealBell
    case 4, HelpingHand
	case 5, Spite
	case 6, PainSplit
	case 7, MagicRoom
    case 8, cancelled
    case 0x7F, cancelled @ When player hit B to close

FirePunch:
    setvar 0x8005 0x0
    call teach5ChipMove
    return

IcePunch:
    setvar 0x8005 0x1
    call teach5ChipMove
    return

ThunderPunch:
    setvar 0x8005 0x2
    call teach5ChipMove
    return

HealBell:
    setvar 0x8005 0x4
    call teach5ChipMove
    return

HelpingHand:
    setvar 0x8005 0x9
    call teach5ChipMove
    return

Spite:
    setvar 0x8005 0xF
    call teach5ChipMove
    return

PainSplit:
    setvar 0x8005 0x1B
    call teach5ChipMove
    return

MagicRoom:
    setvar 0x8005 0x25
    call teach5ChipMove
    return

teach5ChipMove:
    call teachmove
    compare LASTRESULT YES
    if false _goto return
    preparemsg 0x0
    waitmsg
    removeitem ITEM_POKE_CHIP 0x5
    return

teachmove:
    special 0x18D
    waitstate
    compare LASTRESULT YES
    if false _goto cancelled @ Pokemon couldn't learn move, or player cancelled
    sound 0xF8 @ Money SE
    waitse
    return

cancelled:
    msgbox gText_TutoringRejected MSG_NORMAL
    return

return:
    return
