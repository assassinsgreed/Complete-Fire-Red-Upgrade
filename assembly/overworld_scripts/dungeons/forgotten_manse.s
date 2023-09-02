.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_ForgottenManse_Exterior
MapScript_ForgottenManse_Exterior:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_ForgottenManseExterior_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManseExterior_SetWeather
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManseExterior_FlightFlag:
    setworldmapflag 0x8A8 @ Been to Forgotten Manse
    end

MapEntryScript_ForgottenManseExterior_SetWeather:
    random 0xA @ Between 0 and 10
    compare LASTRESULT 0x8
    if lessorequal _call SetWeatherFog
    getplayerpos 0x4003 0x4004
    compare 0x4003 0xA @ On Manse door
    if equal _goto SetDoorOpen
    end

.global MapScript_ForgottenManse_1F
MapScript_ForgottenManse_1F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManse1F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManse1F_SecurityGates:
    checkflag 0x267 @ Switch 2 has been flipped
    if NOT_SET _goto End
    call SetSwitch2Tiles
    checkflag 0x269 @ Switch 4 has been flipped
    if NOT_SET _goto End
    call SetSwitch4Tiles
    checkflag 0x26B @ Switch 6 has been flipped
    if NOT_SET _goto End
    call SetSwitch6Tiles
    getplayerpos 0x4003 0x4004
    compare 0x4003 0x19 @ On storage door
    if equal _goto SetDoorOpenInterior
    end

.global MapScript_ForgottenManse_2F
MapScript_ForgottenManse_2F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManse2F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManse2F_SecurityGates:
    checkflag 0x265 @ Switch 1 has been flipped
    if NOT_SET _goto End
    setmaptile 0x1F 0x7 0x284 0x0 @ Floor
    setmaptile 0x20 0x7 0x284 0x0 @ Floor
    setmaptile 0x21 0x7 0x284 0x0 @ Floor
    setmaptile 0x1F 0x8 0x284 0x0 @ Floor
    setmaptile 0x20 0x8 0x284 0x0 @ Floor
    setmaptile 0x21 0x8 0x284 0x0 @ Floor
    checkflag 0x268 @ Switch 3 has been flipped
    if NOT_SET _goto End
    setmaptile 0x8 0x10 0x2AA 0x1 @ Upper wall
    setmaptile 0x8 0x11 0x2B2 0x1 @ Lower wall
    setmaptile 0x8 0x12 0x284 0x0 @ Floor
    setmaptile 0x8 0x13 0x284 0x0 @ Floor
    setmaptile 0x8 0x14 0x284 0x0 @ Floor
    setmaptile 0x8 0x15 0x2B5 0x0 @ Floor & top of wall
    end

.global MapScript_ForgottenManse_Basement
MapScript_ForgottenManse_Basement:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManseBasement_SetTerrain
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManseBasement_SetTerrain:
    call SetWeatherThinFog @ No battle effect, just visual
    call SetMistyTerrain
    checkflag 0x26A @ Switch 5 has been flipped
    if NOT_SET _goto End
    call SetSwitch5Tiles
    end

.global SignScript_ForgottenManseExterior_MansePlacard
SignScript_ForgottenManseExterior_MansePlacard:
    msgbox gText_ForgottenManseExterior_Sign MSG_SIGN
    end

.global EventScript_ForgottenManseExterior_FrontDoorKey
EventScript_ForgottenManseExterior_FrontDoorKey:
    finditem ITEM_MANSE_KEY 0x1
    end

.global TileScript_ForgottenManseExterior_FrontDoor
TileScript_ForgottenManseExterior_FrontDoor:
    lock
    compareplayerfacing INTERNAL_DOWN @ Exiting the Manse
    if equal _goto End
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    checkitem ITEM_MANSE_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto OpenDoor
    pause 0x14
    msgbox gText_DoorIsLocked MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement ALLEVENTS
    release
    end

OpenDoor:
    playse 0x8 @ Door opening
    waitse
    pause 0x14
    goto SetDoorOpen

SetDoorOpen:
    setmaptile 0xA 0x9 0x293 0x0 @ set to open door sprite
    special 0x8E
    setvar 0x4001 0x1 @ Stop this event from firing again until the player revisits the map
    release
    end

.global TileScript_ForgottenManse1F_StorageDoor
TileScript_ForgottenManse1F_StorageDoor:
    lock
    compareplayerfacing INTERNAL_DOWN @ Exiting the Manse
    if equal _goto End
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    checkitem ITEM_STORAGE_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto OpenDoorInterior
    pause 0x14
    msgbox gText_DoorIsLocked MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement ALLEVENTS
    release
    end

OpenDoorInterior:
    playse 0x8 @ Door opening
    waitse
    pause 0x14
    goto SetDoorOpenInterior

SetDoorOpenInterior:
    setmaptile 0x19 0x12 0x16B 0x0 @ set to open door sprite
    special 0x8E
    setvar 0x4001 0x1 @ Stop this event from firing again until the player revisits the map
    release
    end

.global SignScript_ForgottenManse_Journal1
SignScript_ForgottenManse_Journal1:
    msgbox gText_ForgottenManse_Journal1 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal2
SignScript_ForgottenManse_Journal2:
    msgbox gText_ForgottenManse_Journal2 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal3
SignScript_ForgottenManse_Journal3:
    msgbox gText_ForgottenManse_Journal3 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal4
SignScript_ForgottenManse_Journal4:
    msgbox gText_ForgottenManse_Journal4 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal5
SignScript_ForgottenManse_Journal5:
    msgbox gText_ForgottenManse_Journal5 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal6
SignScript_ForgottenManse_Journal6:
    msgbox gText_ForgottenManse_Journal6 MSG_SIGN
    end

.global EventScript_ForgottenManseExterior_ChannelerMona
EventScript_ForgottenManseExterior_ChannelerMona:
    trainerbattle0 0x0 0x79 0x0 gText_ForgottenManseExterior_ChannelerMona_Intro gText_ForgottenManseExterior_ChannelerMona_Defeat
    msgbox gText_ForgottenManseExterior_ChannelerMona_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseExterior_BurglarChad
EventScript_ForgottenManseExterior_BurglarChad:
    trainerbattle0 0x0 0x7A 0x0 gText_ForgottenManseExterior_BurglarChad_Intro gText_ForgottenManseExterior_BurglarChad_Defeat
    msgbox gText_ForgottenManseExterior_BurglarChad_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseExterior_NurseLucy
EventScript_ForgottenManseExterior_NurseLucy:
    faceplayer
    checktrainerflag 0x57B
    if SET _goto NurseLucyHeal
    trainerbattle2 0x0 0x7B 0x0 gText_ForgottenManseExterior_NurseLucy_Intro gText_ForgottenManseExterior_NurseLucy_Defeat NurseLucyHeal
    goto NurseLucyHeal

NurseLucyHeal:
    msgbox gText_ForgottenManseExterior_NurseLucy_Chat MSG_NORMAL
    call PlayerHeal
    msgbox gText_ForgottenManseExterior_NurseLucy_HealingComplete MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_Sablenite
EventScript_ForgottenManse1F_Sablenite:
    finditem ITEM_SABLENITE 0x1
    end

.global EventScript_ForgottenManse2F_TM60Hex
EventScript_ForgottenManse2F_TM60Hex:
    setvar CHOSEN_ITEM ITEM_TM60
    call ItemScript_Common_FindTM
    end

.global EventScript_ForgottenManseBF1_TM61WillOWisp
EventScript_ForgottenManseBF1_TM61WillOWisp:
    setvar CHOSEN_ITEM ITEM_TM61
    call ItemScript_Common_FindTM
    end

.global EventScript_ForgottenManse1F_BeautyLulu
EventScript_ForgottenManse1F_BeautyLulu:
    trainerbattle0 0x0 0x7C 0x0 gText_ForgottenManse1F_BeautyLulu_Intro gText_ForgottenManse1F_BeautyLulu_Defeat
    msgbox gText_ForgottenManse1F_BeautyLulu_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_ChannelerEsther
EventScript_ForgottenManse1F_ChannelerEsther:
    trainerbattle0 0x0 0x7D 0x0 gText_ForgottenManse1F_ChannelerEsther_Intro gText_ForgottenManse1F_ChannelerEsther_Defeat
    msgbox gText_ForgottenManse1F_ChannelerEsther_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_SuperNerdAustin
EventScript_ForgottenManse1F_SuperNerdAustin:
    trainerbattle0 0x0 0x7E 0x0 gText_ForgottenManse1F_SuperNerdAustin_Intro gText_ForgottenManse1F_SuperNerdAustin_Defeat
    msgbox gText_ForgottenManse1F_SuperNerdAustin_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_BurglarJacques
EventScript_ForgottenManse1F_BurglarJacques:
    trainerbattle0 0x0 0x7F 0x0 gText_ForgottenManse1F_BurglarJacques_Intro gText_ForgottenManse1F_BurglarJacques_Defeat
    msgbox gText_ForgottenManse1F_BurglarJacques_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_PsychicCorbin
EventScript_ForgottenManse1F_PsychicCorbin:
    trainerbattle0 0x0 0x80 0x0 gText_ForgottenManse1F_PsychicCorbin_Intro gText_ForgottenManse1F_PsychicCorbin_Defeat
    msgbox gText_ForgottenManse1F_PsychicCorbin_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_BurglarBarry
EventScript_ForgottenManse2F_BurglarBarry:
    trainerbattle0 0x0 0x81 0x0 gText_ForgottenManse2F_BurglarBarry_Intro gText_ForgottenManse2F_BurglarBarry_Defeat
    msgbox gText_ForgottenManse2F_BurglarBarry_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_YoungsterChester
EventScript_ForgottenManse2F_YoungsterChester:
    trainerbattle0 0x0 0x82 0x0 gText_ForgottenManse2F_YoungsterChester_Intro gText_ForgottenManse2F_YoungsterChester_Defeat
    msgbox gText_ForgottenManse2F_YoungsterChester_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_ChannelerElaine
EventScript_ForgottenManse2F_ChannelerElaine:
    trainerbattle0 0x0 0x83 0x0 gText_ForgottenManse2F_ChannelerElaine_Intro gText_ForgottenManse2F_ChannelerElaine_Defeat
    msgbox gText_ForgottenManse2F_ChannelerElaine_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_SuperNerdGlenn
EventScript_ForgottenManseBF1_SuperNerdGlenn:
    trainerbattle0 0x0 0x84 0x0 gText_ForgottenManseBF1_SuperNerdGlenn_Intro gText_ForgottenManseBF1_SuperNerdGlenn_Defeat
    msgbox gText_ForgottenManseBF1_SuperNerdGlenn_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_BurglarPeter
EventScript_ForgottenManseBF1_BurglarPeter:
    trainerbattle0 0x0 0x85 0x0 gText_ForgottenManseBF1_BurglarPeter_Intro gText_ForgottenManseBF1_BurglarPeter_Defeat
    msgbox gText_ForgottenManseBF1_BurglarPeter_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_PsychicNoelle
EventScript_ForgottenManseBF1_PsychicNoelle:
    trainerbattle0 0x0 0x86 0x0 gText_ForgottenManseBF1_PsychicNoelle_Intro gText_ForgottenManseBF1_PsychicNoelle_Defeat
    msgbox gText_ForgottenManseBF1_PsychicNoelle_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_ChannelerSana
EventScript_ForgottenManseBF1_ChannelerSana:
    trainerbattle0 0x0 0x87 0x0 gText_ForgottenManseBF1_ChannelerSana_Intro gText_ForgottenManseBF1_ChannelerSana_Defeat
    msgbox gText_ForgottenManseBF1_ChannelerSana_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_StorageKey
EventScript_ForgottenManse1F_StorageKey:
    finditem ITEM_STORAGE_KEY 0x1
    end

.global SignScript_ForgottenManse_Gate1Switch
SignScript_ForgottenManse_Gate1Switch:
    lock
    msgbox gText_ForgottenManse_Switch1 MSG_NORMAL
    checkflag 0x265 @ Switch 1 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    @ Tiles changed in map script
    call SecurityGate_FlipSwitchComplete
    setflag 0x265 @ Switch 1 has been flipped
    release
    end

.global SignScript_ForgottenManse_Gate2Switch
SignScript_ForgottenManse_Gate2Switch:
    lock
    msgbox gText_ForgottenManse_Switch2 MSG_NORMAL
    checkflag 0x267 @ Switch 2 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    call SetSwitch2Tiles
    call SecurityGate_FlipSwitchComplete
    setflag 0x267 @ Switch 2 has been flipped
    release
    end

SetSwitch2Tiles:
    @ By dining room
    setmaptile 0xD 0x1 0x2AA 0x1 @ Upper wall
    setmaptile 0xD 0x2 0x2B2 0x1 @ Lower wall
    setmaptile 0xD 0x3 0x285 0x0 @ Shadowed Floor
    setmaptile 0xD 0x4 0x284 0x0 @ Floor
    setmaptile 0xD 0x5 0x29C 0x0 @ Flat wall
    @ By switch
    setmaptile 0x21 0x8 0x284 0x0 @ Floor
    setmaptile 0x22 0x8 0x284 0x0 @ Floor
    setmaptile 0x23 0x8 0x284 0x0 @ Floor
    setmaptile 0x21 0x9 0x284 0x0 @ Floor
    setmaptile 0x22 0x9 0x284 0x0 @ Floor
    setmaptile 0x23 0x9 0x284 0x0 @ Floor
    @ Upper hall
    setmaptile 0x1B 0x8 0x2C8 0x0 @ Floor, with cracked floor tiles
    setmaptile 0x1C 0x8 0x2C9 0x0 @ Floor, with cracked floor tiles
    setmaptile 0x1D 0x8 0x2CA 0x0 @ Floor, with cracked floor tiles
    setmaptile 0x1B 0x9 0x284 0x0 @ Floor
    setmaptile 0x1C 0x9 0x284 0x0 @ Floor
    setmaptile 0x1D 0x9 0x284 0x0 @ Floor
    @ Lower hall
    setmaptile 0x1B 0x10 0x284 0x0 @ Floor
    setmaptile 0x1C 0x10 0x284 0x0 @ Floor
    setmaptile 0x1D 0x10 0x284 0x0 @ Floor
    setmaptile 0x1B 0x11 0x284 0x0 @ Floor
    setmaptile 0x1C 0x11 0x284 0x0 @ Floor
    setmaptile 0x1D 0x11 0x284 0x0 @ Floor
    return

.global SignScript_ForgottenManse_Gate3Switch
SignScript_ForgottenManse_Gate3Switch:
    lock
    msgbox gText_ForgottenManse_Switch3 MSG_NORMAL
    checkflag 0x268 @ Switch 3 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    @ Tiles changed in map script
    call SecurityGate_FlipSwitchComplete
    setflag 0x268 @ Switch 3 has been flipped
    release
    end

.global SignScript_ForgottenManse_Gate4Switch
SignScript_ForgottenManse_Gate4Switch:
    lock
    msgbox gText_ForgottenManse_Switch4 MSG_NORMAL
    checkflag 0x269 @ Switch 4 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    call SetSwitch4Tiles
    call SecurityGate_FlipSwitchComplete
    setflag 0x269 @ Switch 4 has been flipped
    release
    end

SetSwitch4Tiles:
    setmaptile 0xC 0xA 0x2FC 0x1 @ Upper wall, angled
    setmaptile 0xC 0xB 0x304 0x1 @ Lower wall, angled
    setmaptile 0xC 0xC 0x284 0x0 @ Floor
    setmaptile 0xC 0xD 0x284 0x0 @ Floor
    setmaptile 0xC 0xE 0x2B5 0x0 @ Floor & top of wall
    return

.global SignScript_ForgottenManse_Gate5Switch
SignScript_ForgottenManse_Gate5Switch:
    lock
    msgbox gText_ForgottenManse_Switch5 MSG_NORMAL
    checkflag 0x26A @ Switch 5 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    call SetSwitch5Tiles
    call SecurityGate_FlipSwitchComplete
    setflag 0x26A @ Switch 5 has been flipped
    release
    end

SetSwitch5Tiles:
    setmaptile 0x10 0xF 0x28E 0x0 @ Floor
    setmaptile 0x11 0xF 0x286 0x0 @ Floor
    setmaptile 0x12 0xF 0x286 0x0 @ Floor
    setmaptile 0x10 0x10 0x28E 0x0 @ Floor
    setmaptile 0x11 0x10 0x286 0x0 @ Floor
    setmaptile 0x12 0x10 0x286 0x0 @ Floor
    return

.global SignScript_ForgottenManse_Gate6Switch
SignScript_ForgottenManse_Gate6Switch:
    lock
    msgbox gText_ForgottenManse_Switch6 MSG_NORMAL
    checkflag 0x26B @ Switch 6 has been flipped
    if SET _goto SecurityGate_SwitchAlreadyFlipped
    call SecurityGate_FlipSwitchConfirmPrompt
    call SetSwitch6Tiles
    call SecurityGate_FlipSwitchComplete
    setflag 0x26B @ Switch 6 has been flipped
    release
    end

SetSwitch6Tiles:
    setmaptile 0x21 0xF 0x284 0x0 @ Floor
    setmaptile 0x22 0xF 0x284 0x0 @ Floor
    setmaptile 0x23 0xF 0x284 0x0 @ Floor
    setmaptile 0x21 0x10 0x284 0x0 @ Floor
    setmaptile 0x22 0x10 0x284 0x0 @ Floor
    setmaptile 0x23 0x10 0x284 0x0 @ Floor
    return

SecurityGate_FlipSwitchConfirmPrompt:
    msgbox gText_ForgottenManse_FlipSwitchConfirmPrompt MSG_YESNO
    compare LASTRESULT YES
    if notequal _goto SecurityGate_FlipSwitchDenied
    return

SecurityGate_FlipSwitchConfirmed:
    msgbox gText_ForgottenManse_FlipSwitchConfirmed MSG_NORMAL
    return

SecurityGate_FlipSwitchComplete:
    playse 0x8 @ Door open
    waitse
    special 0x8E
    msgbox gText_ForgottenManse_FlipSwitchGateOpened MSG_NORMAL
    return

SecurityGate_FlipSwitchDenied:
    msgbox gText_ForgottenManse_FlipSwitchDenied MSG_NORMAL
    release
    end

SecurityGate_SwitchAlreadyFlipped:
    msgbox gText_ForgottenManse_SwitchAlreadyFlipped MSG_NORMAL
    release
    end

.global SignScript_ForgottenManseStorage_ApplianceCatalog
SignScript_ForgottenManseStorage_ApplianceCatalog:
    lock
    msgbox gText_ForgottenManse_ApplianceCatalog MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ApplianceCatalog_ChoseNo
    special 0x9F @ Select a Pokemon and store it's position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if user backed out
    if greaterorequal _goto ApplianceCatalog_ChoseNo
    bufferpartypokemon 0x0 0x8004
    callasm StoreIsPartyMonRotom
    compare LASTRESULT TRUE
    if FALSE _goto ApplianceCatalog_WrongPokemon
    msgbox gText_ForgottenManse_ApplianceCatalog_ChooseAppliance MSG_KEEPOPEN
    multichoiceoption gText_ForgottenManse_ApplianceCatalog_Revert 0
	multichoiceoption gText_ForgottenManse_ApplianceCatalog_Fan 1
	multichoiceoption gText_ForgottenManse_ApplianceCatalog_Refrigerator 2
	multichoiceoption gText_ForgottenManse_ApplianceCatalog_Oven 3
    multichoiceoption gText_ForgottenManse_ApplianceCatalog_Mower 4
    multichoiceoption gText_ForgottenManse_ApplianceCatalog_Washer 5
    multichoiceoption gText_End 6
	multichoice 0x0 0x0 SEVEN_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, RevertRotom
	case 1, SetRotomFan
	case 2, SetRotomFrost
	case 3, SetRotomHeat
    case 4, SetRotomMow
    case 5, SetRotomWash
    case 6, Cancelled
    end

ApplianceCatalog_ChoseNo:
    msgbox gText_ForgottenManse_ApplianceCatalog_ChoseNo MSG_NORMAL
    release
    end

ApplianceCatalog_WrongPokemon:
    msgbox gText_ForgottenManse_ApplianceCatalog_WrongPokemon MSG_NORMAL
    release
    end

RevertRotom:
    checksound
    cry SPECIES_ROTOM 0x0
    msgbox gText_ForgottenManse_ApplianceCatalog_RotomReverting MSG_NORMAL
    setvar 0x8005 SPECIES_ROTOM
    goto FinalizeRotomFormChange

SetRotomFan:
    call ChangeRotomFormCommon
    setvar 0x8005 SPECIES_ROTOM_FAN
    goto FinalizeRotomFormChange

SetRotomFrost:
    call ChangeRotomFormCommon
    setvar 0x8005 SPECIES_ROTOM_FROST
    goto FinalizeRotomFormChange

SetRotomHeat:
    call ChangeRotomFormCommon
    setvar 0x8005 SPECIES_ROTOM_HEAT
    goto FinalizeRotomFormChange

SetRotomMow:
    call ChangeRotomFormCommon
    setvar 0x8005 SPECIES_ROTOM_MOW
    goto FinalizeRotomFormChange

SetRotomWash:
    call ChangeRotomFormCommon
    setvar 0x8005 SPECIES_ROTOM_WASH
    goto FinalizeRotomFormChange

ChangeRotomFormCommon:
    checksound
    cry SPECIES_ROTOM 0x0
    fanfare 0x101 @ Get Item / Level Up
    msgbox gText_ForgottenManse_ApplianceCatalog_RotomChanging MSG_NORMAL
    waitfanfare
    return

FinalizeRotomFormChange:
    callasm ChangeRotomFormInOverworld
    release
    end

Cancelled:
    msgbox gText_ForgottenManse_ApplianceCatalog_ChoseNo MSG_NORMAL
    return
