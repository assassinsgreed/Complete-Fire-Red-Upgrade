.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Vars are set to the tutor number in hex.  Ex #63, psychic terrain, is 0x3F

.global EventScript_Tutors_Terrain
EventScript_Tutors_Terrain:
    setvar 0x8000 0x8
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, grassyterrain
	case 1, mistyterrain
	case 2, electricterrain
	case 3, psychicterrain
    case 4, cancelled
    case 0x7F, cancelled @ When player hit B to close
    return

grassyterrain:
    bufferattack 0x0 MOVE_GRASSYTERRAIN
    setvar 0x8005 0x3C
    call teach5ChipMove
    return

mistyterrain:
    bufferattack 0x0 MOVE_MISTYTERRAIN
    setvar 0x8005 0x3D
    call teach5ChipMove
    return

electricterrain:
    bufferattack 0x0 MOVE_ELECTRICTERRAIN
    setvar 0x8005 0x3E
    call teach5ChipMove
    return

psychicterrain:
    bufferattack 0x0 MOVE_PSYCHICTERRAIN
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
    bufferattack 0x0 MOVE_SNORE
    setvar 0x8005 0x3
    call teach5ChipMove
    return

worryseed:
    bufferattack 0x0 MOVE_WORRYSEED
    setvar 0x8005 0xB
    call teach5ChipMove
    return

covet:
    bufferattack 0x0 MOVE_COVET
    setvar 0x8005 0xC
    call teach5ChipMove
    return

gravity:
    bufferattack 0x0 MOVE_GRAVITY
    setvar 0x8005 0x13
    call teach5ChipMove
    return

telekinesis:
    bufferattack 0x0 MOVE_TELEKINESIS
    setvar 0x8005 0x15
    call teach5ChipMove
    return

icywind:
    bufferattack 0x0 MOVE_ICYWIND
    setvar 0x8005 0x1E
    call teach5ChipMove
    return

gastroacid:
    bufferattack 0x0 MOVE_GASTROACID
    setvar 0x8005 0x28
    call teach5ChipMove
    return

afteryou:
    bufferattack 0x0 MOVE_AFTERYOU
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
    bufferattack 0x0 MOVE_GRASSPLEDGE
    setvar 0x8005 0x35
    call teach5ChipMove
    return

firepledge:
    bufferattack 0x0 MOVE_FIREPLEDGE
    setvar 0x8005 0x36
    call teach5ChipMove
    return

waterpledge:
    bufferattack 0x0 MOVE_WATERPLEDGE
    setvar 0x8005 0x37
    call teach5ChipMove
    return

lowkick:
    bufferattack 0x0 MOVE_LOWKICK
    setvar 0x8005 0x6
    call teach5ChipMove
    return

bind:
    bufferattack 0x0 MOVE_BIND
    setvar 0x8005 0x8
    call teach5ChipMove
    return

block:
    bufferattack 0x0 MOVE_BLOCK
    setvar 0x8005 0xA
    call teach5ChipMove
    return

laserfocus:
    bufferattack 0x0 MOVE_LASERFOCUS
    setvar 0x8005 0x21
    call teach5ChipMove
    return

uproar:
    bufferattack 0x0 MOVE_UPROAR
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
    bufferattack 0x0 MOVE_FIREPUNCH
    setvar 0x8005 0x0
    call teach5ChipMove
    return

IcePunch:
    bufferattack 0x0 MOVE_ICEPUNCH
    setvar 0x8005 0x1
    call teach5ChipMove
    return

ThunderPunch:
    bufferattack 0x0 MOVE_THUNDERPUNCH
    setvar 0x8005 0x2
    call teach5ChipMove
    return

HealBell:
    bufferattack 0x0 MOVE_HEALBELL
    setvar 0x8005 0x4
    call teach5ChipMove
    return

HelpingHand:
    bufferattack 0x0 MOVE_HELPINGHAND
    setvar 0x8005 0x9
    call teach5ChipMove
    return

Spite:
    bufferattack 0x0 MOVE_SPITE
    setvar 0x8005 0xF
    call teach5ChipMove
    return

PainSplit:
    bufferattack 0x0 MOVE_PAINSPLIT
    setvar 0x8005 0x1B
    call teach5ChipMove
    return

MagicRoom:
    bufferattack 0x0 MOVE_MAGICROOM
    setvar 0x8005 0x25
    call teach5ChipMove
    return

.global EventScript_Tutors_Laplaz
EventScript_Tutors_Laplaz:
    setvar 0x8000 0xA
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, ElectroWeb
	case 1, Snatch
	case 2, MagnetRise
	case 3, Bounce
    case 4, Tailwind
	case 5, Endeavor
	case 6, MagicCoat
	case 7, WonderRoom
    case 8, cancelled
    case 0x7F, cancelled @ When player hit B to close

ElectroWeb:
    bufferattack 0x0 MOVE_ELECTROWEB
    setvar 0x8005 0x5
    call teach5ChipMove
    return

Snatch:
    bufferattack 0x0 MOVE_SNATCH
    setvar 0x8005 0xE
    call teach5ChipMove
    return

MagnetRise:
    bufferattack 0x0 MOVE_MAGNETRISE
    setvar 0x8005 0x16
    call teach5ChipMove
    return

Bounce:
    bufferattack 0x0 MOVE_BOUNCE
    setvar 0x8005 0x17
    call teach5ChipMove
    return

Tailwind:
    bufferattack 0x0 MOVE_TAILWIND
    setvar 0x8005 0x1C
    call teach5ChipMove
    return

Endeavor:
    bufferattack 0x0 MOVE_ENDEAVOR
    setvar 0x8005 0x1D
    call teach5ChipMove
    return

MagicCoat:
    bufferattack 0x0 MOVE_MAGICCOAT
    setvar 0x8005 0x24
    call teach5ChipMove
    return

WonderRoom:
    bufferattack 0x0 MOVE_WONDERROOM
    setvar 0x8005 0x26
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
    msgbox gText_Tutors_ChoosePokemon MSG_NORMAL
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
