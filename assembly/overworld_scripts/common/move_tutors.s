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
    setvar 0x4000 5
    call teachmove
    return

mistyterrain:
    bufferattack 0x0 MOVE_MISTYTERRAIN
    setvar 0x8005 0x3D
    setvar 0x4000 5
    call teachmove
    return

electricterrain:
    bufferattack 0x0 MOVE_ELECTRICTERRAIN
    setvar 0x8005 0x3E
    setvar 0x4000 5
    call teachmove
    return

psychicterrain:
    bufferattack 0x0 MOVE_PSYCHICTERRAIN
    setvar 0x8005 0x3F
    setvar 0x4000 5
    call teachmove
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
    setvar 0x4000 5
    call teachmove
    return

worryseed:
    bufferattack 0x0 MOVE_WORRYSEED
    setvar 0x8005 0xB
    setvar 0x4000 5
    call teachmove
    return

covet:
    bufferattack 0x0 MOVE_COVET
    setvar 0x8005 0xC
    setvar 0x4000 5
    call teachmove
    return

gravity:
    bufferattack 0x0 MOVE_GRAVITY
    setvar 0x8005 0x13
    setvar 0x4000 5
    call teachmove
    return

telekinesis:
    bufferattack 0x0 MOVE_TELEKINESIS
    setvar 0x8005 0x15
    setvar 0x4000 5
    call teachmove
    return

icywind:
    bufferattack 0x0 MOVE_ICYWIND
    setvar 0x8005 0x1E
    setvar 0x4000 5
    call teachmove
    return

gastroacid:
    bufferattack 0x0 MOVE_GASTROACID
    setvar 0x8005 0x28
    setvar 0x4000 5
    call teachmove
    return

afteryou:
    bufferattack 0x0 MOVE_AFTERYOU
    setvar 0x8005 0x10
    setvar 0x4000 5
    call teachmove
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
    setvar 0x4000 5
    call teachmove
    return

firepledge:
    bufferattack 0x0 MOVE_FIREPLEDGE
    setvar 0x8005 0x36
    setvar 0x4000 5
    call teachmove
    return

waterpledge:
    bufferattack 0x0 MOVE_WATERPLEDGE
    setvar 0x8005 0x37
    setvar 0x4000 5
    call teachmove
    return

lowkick:
    bufferattack 0x0 MOVE_LOWKICK
    setvar 0x8005 0x6
    setvar 0x4000 5
    call teachmove
    return

bind:
    bufferattack 0x0 MOVE_BIND
    setvar 0x8005 0x8
    setvar 0x4000 5
    call teachmove
    return

block:
    bufferattack 0x0 MOVE_BLOCK
    setvar 0x8005 0xA
    setvar 0x4000 5
    call teachmove
    return

laserfocus:
    bufferattack 0x0 MOVE_LASERFOCUS
    setvar 0x8005 0x21
    setvar 0x4000 5
    call teachmove
    return

uproar:
    bufferattack 0x0 MOVE_UPROAR
    setvar 0x8005 0x7
    setvar 0x4000 5
    call teachmove
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
    setvar 0x4000 5
    call teachmove
    return

IcePunch:
    bufferattack 0x0 MOVE_ICEPUNCH
    setvar 0x8005 0x1
    setvar 0x4000 5
    call teachmove
    return

ThunderPunch:
    bufferattack 0x0 MOVE_THUNDERPUNCH
    setvar 0x8005 0x2
    setvar 0x4000 5
    call teachmove
    return

HealBell:
    bufferattack 0x0 MOVE_HEALBELL
    setvar 0x8005 0x4
    setvar 0x4000 5
    call teachmove
    return

HelpingHand:
    bufferattack 0x0 MOVE_HELPINGHAND
    setvar 0x8005 0x9
    setvar 0x4000 5
    call teachmove
    return

Spite:
    bufferattack 0x0 MOVE_SPITE
    setvar 0x8005 0xF
    setvar 0x4000 5
    call teachmove
    return

PainSplit:
    bufferattack 0x0 MOVE_PAINSPLIT
    setvar 0x8005 0x1B
    setvar 0x4000 5
    call teachmove
    return

MagicRoom:
    bufferattack 0x0 MOVE_MAGICROOM
    setvar 0x8005 0x25
    setvar 0x4000 5
    call teachmove
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
    setvar 0x4000 5
    call teachmove
    return

Snatch:
    bufferattack 0x0 MOVE_SNATCH
    setvar 0x8005 0xE
    setvar 0x4000 5
    call teachmove
    return

MagnetRise:
    bufferattack 0x0 MOVE_MAGNETRISE
    setvar 0x8005 0x16
    setvar 0x4000 5
    call teachmove
    return

Bounce:
    bufferattack 0x0 MOVE_BOUNCE
    setvar 0x8005 0x17
    setvar 0x4000 5
    call teachmove
    return

Tailwind:
    bufferattack 0x0 MOVE_TAILWIND
    setvar 0x8005 0x1C
    setvar 0x4000 5
    call teachmove
    return

Endeavor:
    bufferattack 0x0 MOVE_ENDEAVOR
    setvar 0x8005 0x1D
    setvar 0x4000 5
    call teachmove
    return

MagicCoat:
    bufferattack 0x0 MOVE_MAGICCOAT
    setvar 0x8005 0x24
    setvar 0x4000 5
    call teachmove
    return

WonderRoom:
    bufferattack 0x0 MOVE_WONDERROOM
    setvar 0x8005 0x26
    setvar 0x4000 5
    call teachmove
    return

.global EventScript_Tutors_Bruccie
EventScript_Tutors_Bruccie:
    setvar 0x8000 0xB
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, BugBite
	case 1, IronDefense
	case 2, LastResort
	case 3, DrillRun
    case 4, FoulPlay
	case 5, SuperFang
	case 6, ThroatChop
	case 7, DualChop
    case 8, cancelled
    case 0x7F, cancelled @ When player hit B to close
    return

BugBite:
    bufferattack 0x0 MOVE_BUGBITE
    setvar 0x8005 13
    setvar 0x4000 10
    call teachmove
    return

IronDefense:
    bufferattack 0x0 MOVE_IRONDEFENSE
    setvar 0x8005 20
    setvar 0x4000 10
    call teachmove
    return

LastResort:
    bufferattack 0x0 MOVE_LASTRESORT
    setvar 0x8005 24
    setvar 0x4000 10
    call teachmove
    return

DrillRun:
    bufferattack 0x0 MOVE_DRILLRUN
    setvar 0x8005 35
    setvar 0x4000 10
    call teachmove
    return

FoulPlay:
    bufferattack 0x0 MOVE_FOULPLAY
    setvar 0x8005 41
    setvar 0x4000 10
    call teachmove
    return

SuperFang:
    bufferattack 0x0 MOVE_SUPERFANG
    setvar 0x8005 42
    setvar 0x4000 10
    call teachmove
    return

ThroatChop:
    bufferattack 0x0 MOVE_THROATCHOP
    setvar 0x8005 45
    setvar 0x4000 10
    call teachmove
    return

DualChop:
    bufferattack 0x0 MOVE_DUALCHOP
    setvar 0x8005 49
    setvar 0x4000 10
    call teachmove
    return

teachmove:
    msgbox gText_Tutors_ChoosePokemon MSG_NORMAL
    special 0x18D
    waitstate
    compare LASTRESULT YES
    if false _goto cancelled @ Pokemon couldn't learn move, or player cancelled
    sound 0xF8 @ Money SE
    waitse
    removeitem ITEM_POKE_CHIP 0x4000
    incrementgamestat 3
    return

cancelled:
    msgbox gText_TutoringRejected MSG_NORMAL
    return

return:
    return
