.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_EmraldinQuay
MapScript_EmraldinQuay:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_EmraldinQuay_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_EmraldinQuay_FlightSpot:
    setworldmapflag 0x898 @ Visited Emraldin Quay
    end

.global EventScript_EmraldinQuay_FarmersMarketWoman
EventScript_EmraldinQuay_FarmersMarketWoman:
    msgbox gText_EmraldinQuay_Overworld_FarmersMarketWomanIntro MSG_NORMAL
    pokemart FarmersMarket
    msgbox gText_EmraldinQuay_Overworld_FarmersMarketWomanOutro MSG_NORMAL
    end

.align 1
FarmersMarket:
    .hword ITEM_HYPER_POTION
    .hword ITEM_FULL_HEAL
    .hword ITEM_MAX_REPEL
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.global EventScript_EmraldinQuay_GalaricaGirl
EventScript_EmraldinQuay_GalaricaGirl:
    msgbox gText_EmraldinQuay_Overworld_GalaricaGirlIntro MSG_NORMAL
    pokemart GalaricaMart
    msgbox gText_EmraldinQuay_Overworld_GalaricaGirlOutro MSG_NORMAL
    end

.align 1
GalaricaMart:
    .hword ITEM_GALARICA_CUFF
    .hword ITEM_GALARICA_WREATH
    .hword ITEM_NONE

.global EventScript_EmraldinQuay_Boy
EventScript_EmraldinQuay_Boy:
    npcchat gText_EmraldinQuay_Overworld_Boy
    end

.global EventScript_EmraldinQuay_Girl
EventScript_EmraldinQuay_Girl:
    npcchat gText_EmraldinQuay_Overworld_Girl
    end

.global SignScript_EmraldinQuay_TownSign
SignScript_EmraldinQuay_TownSign:
    msgbox gText_EmraldinQuay_Overworld_TownSign MSG_SIGN
    end

.global SignScript_EmraldinQuay_FarmersMarketSign
SignScript_EmraldinQuay_FarmersMarketSign:
    msgbox gText_EmraldinQuay_Overworld_FarmersMarketSign MSG_SIGN
    end

.global MapScript_EmraldinQuayFacilities_PokemonCenter
MapScript_EmraldinQuayFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_EmraldinQuayFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_EmraldinQuayFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x09
    end

.global EventScript_EmraldinQuayFacilities_PokemonCenter_TreasureBeachGirl
EventScript_EmraldinQuayFacilities_PokemonCenter_TreasureBeachGirl:
    npcchatwithmovement gText_EmraldinQuay_PokemonCenter_TreasureBeachGirl m_LookLeft
    end

.global EventScript_EmraldinQuayFacilities_PokemonCenter_OldWoman
EventScript_EmraldinQuayFacilities_PokemonCenter_OldWoman:
    npcchatwithmovement gText_EmraldinQuay_PokemonCenter_OldWoman m_LookDown
    end

.global EventScript_EmraldinQuayFacilities_PokemonCenter_Blackbelt
EventScript_EmraldinQuayFacilities_PokemonCenter_Blackbelt:
    npcchatwithmovement gText_EmraldinQuay_PokemonCenter_Blackbelt m_LookLeft
    end

.global EventScript_EmraldinQuayNPCHouses_Camper
EventScript_EmraldinQuayNPCHouses_Camper:
    npcchatwithmovement gText_EmraldinQuay_NPCHouses_Camper m_LookLeft
    end

.global EventScript_EmraldinQuayNPCHouses_CamperMom
EventScript_EmraldinQuayNPCHouses_CamperMom:
    npcchatwithmovement gText_EmraldinQuay_NPCHouses_CamperMom m_LookUp
    end

.global EventScript_EmraldinQuayNPCHouses_Tutor
EventScript_EmraldinQuayNPCHouses_Tutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_EmraldinQuayNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_EmraldinQuayNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Emraldin
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_EmraldinQuayNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_EmraldinQuayNPCHouses_TutoringRejected m_LookUp
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_EmraldinQuayNPCHouses_NotEnoughPokeChips m_LookUp
    goto End

.global EventScript_EmraldinQuayNPCHouses_TutorSon
EventScript_EmraldinQuayNPCHouses_TutorSon:
    npcchatwithmovement gText_EmraldinQuay_NPCHouses_TutorSon m_LookLeft
    end

.global EventScript_EmraldinQuayNPCHouses_TutorYoungSon
EventScript_EmraldinQuayNPCHouses_TutorYoungSon:
    npcchat gText_EmraldinQuay_NPCHouses_TutorYoungSon
    end
