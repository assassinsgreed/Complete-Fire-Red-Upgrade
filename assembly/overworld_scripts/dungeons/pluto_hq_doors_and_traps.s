.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ VeritcalTopLeftTile, 0x347
.equ VeritcalTopRightTile, 0x346
.equ VeritcalBottomLeftTile, 0x339
.equ VeritcalBottomRightTile, 0x33A
.equ HorizontalTiles_DarkBlue, 0x335
.equ HorizontalTiles_LightBlue, 0x334
.equ HorizontalTiles_DarkYellow, 0x282
.equ HorizontalTiles_LightYellow, 0x281
.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_PlutoBaseHQ_B1F
MapScript_PlutoBaseHQ_B1F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B1F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B1FHall
MapScript_PlutoBaseHQ_B1FHall:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B1FHall_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B2F
MapScript_PlutoBaseHQ_B2F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B2F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B3F
MapScript_PlutoBaseHQ_B3F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B3F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B4F
MapScript_PlutoBaseHQ_B4F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B4F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B5F
MapScript_PlutoBaseHQ_B5F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B5F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B6F
MapScript_PlutoBaseHQ_B6F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B6F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B7F
MapScript_PlutoBaseHQ_B7F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B7F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_PlutoBaseHQ_B1F_SecurityGates:
    checkflag 0x200
    if SET _call HideB1FCerberusDoor
    end

MapEntryScript_PlutoBaseHQ_B1FHall_SecurityGates:
    checkflag 0x201
    if SET _call HideB1FHallOwlDoor
    checkflag 0x202
    if SET _call HideB1FHallCypressDoor
    checkflag 0x203
    if SET _call HideB1FHallSerpentDoor
    checkflag 0x204
    if SET _call HideB1FHallCerberusDoor
    end

MapEntryScript_PlutoBaseHQ_B2F_SecurityGates:
    checkflag 0x205
    if SET _call HideB2FOwlDoor
    end

MapEntryScript_PlutoBaseHQ_B3F_SecurityGates:
    checkflag 0x206
    if SET _call HideB3FCypressDoor
    end

MapEntryScript_PlutoBaseHQ_B4F_SecurityGates:
    checkflag 0x207
    if SET _call HideB4FOwlDoor
    checkflag 0x208
    if SET _call HideB4FCerberusDoor
    end

MapEntryScript_PlutoBaseHQ_B5F_SecurityGates:
    checkflag 0x209
    if SET _call HideB5FCypressDoor
    end

MapEntryScript_PlutoBaseHQ_B6F_SecurityGates:
    checkflag 0x20A
    if SET _call HideB6FOwlDoor
    end

MapEntryScript_PlutoBaseHQ_B7F_SecurityGates:
    checkflag 0x20B
    if SET _call HideB7FCypressDoor
    checkflag 0x20C
    if SET _call HideB7FSerpentDoor
    end

.global SignScript_PlutoHQ_B1F_Floor
SignScript_PlutoHQ_B1F_Floor:
    msgbox PlutoHQ_B1F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B2F_Floor
SignScript_PlutoHQ_B2F_Floor:
    msgbox PlutoHQ_B2F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B3F_Floor
SignScript_PlutoHQ_B3F_Floor:
    msgbox PlutoHQ_B3F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B4F_Floor
SignScript_PlutoHQ_B4F_Floor:
    msgbox PlutoHQ_B4F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B5F_Floor
SignScript_PlutoHQ_B5F_Floor:
    msgbox PlutoHQ_B5F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B6F_Floor
SignScript_PlutoHQ_B6F_Floor:
    msgbox PlutoHQ_B6F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B1F_CerberusDoor
SignScript_PlutoHQ_B1F_CerberusDoor:
    checkflag 0x200
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x200
    end

.global SignScript_PlutoHQ_B1F_Hall_OwlDoor
SignScript_PlutoHQ_B1F_Hall_OwlDoor:
    checkflag 0x201
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x201
    end

.global SignScript_PlutoHQ_B1F_Hall_CypressDoor
SignScript_PlutoHQ_B1F_Hall_CypressDoor:
    checkflag 0x202
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x202
    end

.global SignScript_PlutoHQ_B1F_Hall_SerpentDoor
SignScript_PlutoHQ_B1F_Hall_SerpentDoor:
    checkflag 0x203
    if SET _goto End
    msgbox PlutoHQ_SerpentDoorSign MSG_NORMAL
    checkitem ITEM_SERPENT_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallSerpentDoor
    special 0x8E
    bufferitem 0x0 ITEM_SERPENT_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x203
    end

.global SignScript_PlutoHQ_B1F_Hall_CerberusDoor
SignScript_PlutoHQ_B1F_Hall_CerberusDoor:
    checkflag 0x204
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x204
    end

.global SignScript_PlutoHQ_B2F_OwlDoor
SignScript_PlutoHQ_B2F_OwlDoor:
    checkflag 0x205
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB2FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x205
    end

.global SignScript_PlutoHQ_B3F_CypressDoor
SignScript_PlutoHQ_B3F_CypressDoor:
    checkflag 0x206
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB3FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x206
    end

.global SignScript_PlutoHQ_B4F_OwlDoor
SignScript_PlutoHQ_B4F_OwlDoor:
    checkflag 0x207
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB4FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x207
    end

.global SignScript_PlutoHQ_B4F_CerberusDoor
SignScript_PlutoHQ_B4F_CerberusDoor:
    checkflag 0x208
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB4FCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x208
    end

.global SignScript_PlutoHQ_B5F_CypressDoor
SignScript_PlutoHQ_B5F_CypressDoor:
    checkflag 0x209
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB5FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x209
    end

.global SignScript_PlutoHQ_B6F_OwlDoor
SignScript_PlutoHQ_B6F_OwlDoor:
    checkflag 0x20A
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB6FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20A
    end

.global SignScript_PlutoHQ_B7F_CypressDoor
SignScript_PlutoHQ_B7F_CypressDoor:
    checkflag 0x20B
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB7FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20B
    end

.global SignScript_PlutoHQ_B7F_SerpentDoor
SignScript_PlutoHQ_B7F_SerpentDoor:
    checkflag 0x20C
    if SET _goto End
    msgbox PlutoHQ_SerpentDoorSign MSG_NORMAL
    checkitem ITEM_SERPENT_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB7FSerpentDoor
    special 0x8E
    bufferitem 0x0 ITEM_SERPENT_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20C
    end

HideB1FCerberusDoor:
    setmaptile 0x1A 0xA VeritcalTopLeftTile Impassable
    setmaptile 0x1B 0xA VeritcalTopRightTile Impassable
    setmaptile 0x1A 0xB HorizontalTiles_DarkBlue Passable
    setmaptile 0x1B 0xB HorizontalTiles_DarkBlue Passable
    setmaptile 0x1A 0xC VeritcalBottomLeftTile Passable
    setmaptile 0x1B 0xC VeritcalBottomRightTile Passable
    return

HideB1FHallOwlDoor:
    setmaptile 0x2 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x11 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x11 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x11 HorizontalTiles_LightBlue Passable
    return

HideB1FHallCypressDoor:
    setmaptile 0x2 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xD HorizontalTiles_LightBlue Passable
    return

HideB1FHallSerpentDoor:
    setmaptile 0x2 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x9 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x9 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x9 HorizontalTiles_LightBlue Passable
    return

HideB1FHallCerberusDoor:
    setmaptile 0x2 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x5 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x5 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x5 HorizontalTiles_LightBlue Passable
    return

HideB2FOwlDoor:
    setmaptile 0x9 0xC VeritcalTopLeftTile Impassable
    setmaptile 0xA 0xC VeritcalTopRightTile Impassable
    setmaptile 0x9 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0xA 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0x9 0xE VeritcalBottomLeftTile Passable
    setmaptile 0xA 0xE VeritcalBottomRightTile Passable
    return

HideB3FCypressDoor:
    setmaptile 0x1D 0x10 VeritcalTopLeftTile Impassable
    setmaptile 0x1E 0x10 VeritcalTopRightTile Impassable
    setmaptile 0x1D 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1E 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1D 0x12 VeritcalBottomLeftTile Passable
    setmaptile 0x1E 0x12 VeritcalBottomRightTile Passable
    return

HideB4FOwlDoor:
    setmaptile 0x11 0x6 HorizontalTiles_DarkBlue Passable
    setmaptile 0x12 0x6 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x6 HorizontalTiles_LightBlue Passable
    setmaptile 0x11 0x7 HorizontalTiles_DarkBlue Passable
    setmaptile 0x12 0x7 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x7 HorizontalTiles_LightBlue Passable
    setmaptile 0x12 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x8 HorizontalTiles_LightBlue Passable
    return

HideB4FCerberusDoor:
    setmaptile 0x3 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0x4 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xE HorizontalTiles_DarkBlue Passable
    setmaptile 0x4 0xE HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xF HorizontalTiles_LightBlue Passable
    return

HideB5FCypressDoor:
    setmaptile 0x20 0x12 HorizontalTiles_DarkBlue Passable
    setmaptile 0x21 0x12 HorizontalTiles_LightBlue Passable
    setmaptile 0x20 0x13 HorizontalTiles_DarkBlue Passable
    setmaptile 0x21 0x13 HorizontalTiles_LightBlue Passable
    setmaptile 0x21 0x14 HorizontalTiles_LightBlue Passable
    return

HideB6FOwlDoor:
    setmaptile 0x1C 0x10 VeritcalTopLeftTile Impassable
    setmaptile 0x1D 0x10 VeritcalTopRightTile Impassable
    setmaptile 0x1C 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1D 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1C 0x12 VeritcalBottomLeftTile Passable
    setmaptile 0x1D 0x12 VeritcalBottomRightTile Passable
    return

HideB7FCypressDoor:
    setmaptile 0x11 0x6 HorizontalTiles_DarkYellow Passable
    setmaptile 0x12 0x6 HorizontalTiles_LightYellow Passable
    setmaptile 0x13 0x6 HorizontalTiles_LightYellow Passable
    return

HideB7FSerpentDoor:
    setmaptile 0x1E 0xD HorizontalTiles_DarkYellow Passable
    setmaptile 0xB1F 0xD HorizontalTiles_LightYellow Passable
    setmaptile 0x1E 0xE HorizontalTiles_DarkYellow Passable
    setmaptile 0xB1F 0xE HorizontalTiles_LightYellow Passable
    return

# Door code logic ends here!

.global SignScript_PlutoHQ_B3F_StatueSwitch
SignScript_PlutoHQ_B3F_StatueSwitch:
    msgbox gText_PlutoHQ_StatueTrapMachine MSG_NORMAL
    compare 0x409B 0x0
    if equal _goto MachineIsOn
    goto MachineIsOff
    end

MachineIsOn:
    msgbox gText_PlutoHQ_StatueTrapMachine_IsOn MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotChangingMachineState
    playse 0x2A @ Turn switch flip
    msgbox gText_PlutoHQ_StatueTrapMachine_TurnedOff MSG_NORMAL
    setvar 0x409B 0x1 @ Off
    end

MachineIsOff:
    msgbox gText_PlutoHQ_StatueTrapMachine_IsOff MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotChangingMachineState
    playse 0x2A @ Turn switch flip
    msgbox gText_PlutoHQ_StatueTrapMachine_TurnedOn MSG_NORMAL
    setvar 0x409B 0x0 @ On
    end

NotChangingMachineState:
    msgbox gText_PlutoHQ_StatueTrapMachine_ChoseNotTo MSG_NORMAL
    end

.global TileScript_PlutoHQ_WildBattle
TileScript_PlutoHQ_WildBattle:
    lock
    call ChooseWildSpecies
    checksound
    cry 0x4000 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_PlutoHQ_WildPokemon MSG_KEEPOPEN
    wildbattle 0x4000 40 0x0
    release
    end

ChooseWildSpecies:
    random 0x3
    compare LASTRESULT 0x0
    if equal _call SetKoffing
    compare LASTRESULT 0x1
    if equal _call SetRattata
    compare LASTRESULT 0x2
    if equal _call SetZubat
    return

SetKoffing:
    setvar 0x4000 SPECIES_KOFFING_G
    return

SetRattata:
    setvar 0x4000 SPECIES_RATTATA_A
    return

SetZubat:
    setvar 0x4000 SPECIES_ZUBAT
    return
