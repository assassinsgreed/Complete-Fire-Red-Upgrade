.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ TileSpriteLeft, 0x2C1
.equ TileSpriteRight, 0x2C2
.equ TileSpriteDown, 0x2C3
.equ TileSpriteUp, 0x2C4

.global MapScript_LaplazGym_RotatingFloorTiles
MapScript_LaplazGym_RotatingFloorTiles:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LaplazGym_SetWalkingScript
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_LaplazGym_SetWalkingScript:
    setvar 0x500B 0x1 @ Use walking script 1, which is defined below
    end

@ Assigned as a walking script, to trigger on each step
.global LaplazGym_RotationSteps
LaplazGym_RotationSteps:
    @ Tiles do not rotate if the player's step results in them stopping on a movement tile    
    compare 0x4000 0x4
    if equal _goto RotateTiles
    if notequal _goto TimerTickUpSound

TimerTickUpSound:
    addvar 0x4000 0x1
    release
    end

RotateTiles:
    playse 0x2A @ Turn switch flip
    @ The following 3 calls are called for every rotatable tile
    setvar 0x8004 0x8 @ X var of tile
    setvar 0x8005 0x34 @ Y var of tile
    call HandleRotationCW @ Gym entrance
    setvar 0x8004 0xC
    setvar 0x8005 0x32
    call HandleRotationCW @ Right of gym entrance
    setvar 0x8004 0x5
    setvar 0x8005 0x31
    call HandleRotationCCW @ Left of gym entrance
    setvar 0x8004 0x6
    setvar 0x8005 0x28
    call HandleRotationHorizontal @ Left in area 2
    setvar 0x8004 0x7
    setvar 0x8005 0x28
    call HandleRotationRightUpDown @ Right in area 2
    setvar 0x8004 0xE
    setvar 0x8005 0x1E
    call HandleRotationLeftUpRight @ Right in area 3
    setvar 0x8004 0x8
    setvar 0x8005 0x1C
    call HandleRotationVertical @ Middle-Right in area 3
    setvar 0x8004 0x6
    setvar 0x8005 0x1C
    call HandleRotationCCW @ Middle-Left in area 3
    setvar 0x8004 0x4
    setvar 0x8005 0x1C
    call HandleRotationCW @ Left in area 3
    setvar 0x8004 0x6
    setvar 0x8005 0x13
    call HandleRotationCW @ Bottom Left in area 4
    setvar 0x8004 0x8
    setvar 0x8005 0xF
    call HandleRotationLeftUpDown @ Left in area 4
    setvar 0x8004 0x9
    setvar 0x8005 0xE
    call HandleRotationLeftUpRight @ Middle in area 4
    setvar 0x8004 0xA
    setvar 0x8005 0xF
    call HandleRotationRightUpDown @ Right in area 4
    setvar 0x4000 0x0
    special 0x8E @ Refresh map changes
    release
    end

HandleRotationCW:
    @ Tiles rotate clockwise every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateLeft
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    return

HandleRotationCCW:
    @ Tiles rotate counterclockwise every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateLeft
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateUp
    return

HandleRotationHorizontal:
    @ Tiles rotate left-right every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateLeft
    return

HandleRotationVertical:
    @ Tiles rotate up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateUp
    return

HandleRotationLeftUpRight:
    @ Tiles rotate left-up-right-left every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateLeft
    return

HandleRotationLeftUpDown:
    @ Tiles rotate left-up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateLeft
    return

HandleRotationRightUpDown:
    @ Tiles rotate right-up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteRight
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateRight
    return

RotateRight:
    setmaptile 0x8004 0x8005 TileSpriteRight 0x0
    return

RotateDown:
    setmaptile 0x8004 0x8005 TileSpriteDown 0x0
    return

RotateLeft:
    setmaptile 0x8004 0x8005 TileSpriteLeft 0x0
    return

RotateUp:
    setmaptile 0x8004 0x8005 TileSpriteUp 0x0
    return
