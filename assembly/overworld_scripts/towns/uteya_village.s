.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_UteyaVillage
MapScript_UteyaVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_UteyaVillage_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UteyaVillage_FlightSpot:
    setworldmapflag 0x89A @ Visited Uteya Village
    end

.global EventScript_UteyaVillage_HessonPassKid
EventScript_UteyaVillage_HessonPassKid:
    npcchat gText_UteyaVillage_HessonPassBoy
    end

.global EventScript_UteyaVillage_GymGirl
EventScript_UteyaVillage_GymGirl:
    npcchatwithmovement gText_UteyaVillage_GymGirl m_LookUp
    end

.global EventScript_UteyaVillage_UteyaRuinsMan
EventScript_UteyaVillage_UteyaRuinsMan:
    npcchat gText_UteyaVillage_UteyaRuinsMan
    end

.global EventScript_UteyaVillage_TrainerHouseOldMan
EventScript_UteyaVillage_TrainerHouseOldMan:
    npcchatwithmovement gText_UteyaVillage_TrainerHouseOldMan m_LookLeft
    end

.global EventScript_UteyaVillage_TM30_ShadowBall
EventScript_UteyaVillage_TM30_ShadowBall:
    setvar CHOSEN_ITEM ITEM_TM30
    call ItemScript_Common_FindTM
    end

.global SignScript_UteyaVillage_HessonPass
SignScript_UteyaVillage_HessonPass:
    msgbox gText_UteyaVillage_HessonPass MSG_SIGN
    end

.global SignScript_UteyaVillage_TownPlacard
SignScript_UteyaVillage_TownPlacard:
    msgbox gText_UteyaVillage_TownPlacard MSG_SIGN
    end

.global SignScript_UteyaVillage_GymSign
SignScript_UteyaVillage_GymSign:
    msgbox gText_UteyaVillage_GymSign MSG_SIGN
    end

.global SignScript_UteyaVillage_TrainerHouse
SignScript_UteyaVillage_TrainerHouse:
    msgbox gText_UteyaVillage_TrainerHouse MSG_SIGN
    end

// Facilities
.global MapScript_UteyaVillage_PokemonCenter
MapScript_UteyaVillage_PokemonCenter:   
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_UteyaVillageFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_UteyaVillageFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0xE
    end

.global EventScript_PokemonCenter_Woman
EventScript_PokemonCenter_Woman:
    npcchatwithmovement gText_UteyaVillage_PokemonCenter_Woman m_LookLeft
    end

.global EventScript_PokemonCenter_SuperNerd
EventScript_PokemonCenter_SuperNerd:
    npcchatwithmovement gText_UteyaVillage_PokemonCenter_SuperNerd m_LookUp
    end

.global EventScript_PokemonCenter_BirdKeeper
EventScript_PokemonCenter_BirdKeeper:
    npcchat gText_UteyaVillage_PokemonCenter_BirdKeeper
    end

.global EventScript_UteyaVillage_Pokemart_StatBoostingBerriesShop
EventScript_UteyaVillage_Pokemart_StatBoostingBerriesShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart UteyaVillagePokemart_StatBoostingBerryStock
    goto EventScript_EndMart

.align 1
UteyaVillagePokemart_StatBoostingBerryStock:
    .hword ITEM_LIECHI_BERRY  // Attack, when below 1/4 hp
    .hword ITEM_GANLON_BERRY  // Defense, when below 1/4 hp
    .hword ITEM_PETAYA_BERRY  // Sp. Attack, when below 1/4 hp
    .hword ITEM_APICOT_BERRY  // Sp. Defense, when below 1/4 hp
    .hword ITEM_SALAC_BERRY   // Speed, when below 1/4 hp
    .hword ITEM_LANSAT_BERRY  // Crit rate, when below 1/4 hp
    .hword ITEM_STARF_BERRY   // Random stat, when below 1/4 hp
    .hword ITEM_KEE_BERRY     // Defense, when hit by a physical move
    .hword ITEM_MARANGA_BERRY // Sp. Defense, when hit by a special move
    .hword ITEM_NONE

.global EventScript_UteyaVillage_Pokemart_Girl
EventScript_UteyaVillage_Pokemart_Girl:
    npcchatwithmovement gText_UteyaVillage_Pokemart_Girl m_LookRight
    end

.global EventScript_UteyaVillage_Pokemart_OldWoman
EventScript_UteyaVillage_Pokemart_OldWoman:
    npcchatwithmovement gText_UteyaVillage_Pokemart_Woman m_LookUp
    end

.global EventScript_UteyaVillage_MoveTutor
EventScript_UteyaVillage_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_UteyaVillage_MoveTutor_Confirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_UteyaVillage_MoveTutor_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Uteya
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_UteyaVillage_MoveTutor_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_UteyaVillage_MoveTutor_Rejected m_LookRight
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_UteyaVillage_MoveTutor_NotEnoughPokeChips m_LookRight
    goto End

.global MapScript_UteyaVillage_SlowpokeNews
MapScript_UteyaVillage_SlowpokeNews:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_UteyaVillage_SlowpokeNews_SetSpecies
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UteyaVillage_SlowpokeNews_SetSpecies:
    call BufferSpeciesName    
    checkflag 0xE32 @ Species has been set
    if SET _goto End
    random 0x11F @ up to #287 to avoid exposing starters and legendaries, stored in LastResult
    copyvar 0x40ED LASTRESULT @ Slowpoke news dex #
    setflag 0xE32 @ Species has been set
    call BufferSpeciesName @ Get the species name belonging to this pokedex #
    copyvar 0x40EE LASTRESULT @ Get the species # out
    end

BufferSpeciesName:
    copyvar LASTRESULT 0x40ED @ Slowpoke news species
    callasm GetSlowpokeNewsSpecies @ Var result not used; used to buffer species name
    return

.global EventScript_UteyaVillage_SlowpokeNews_Producer
EventScript_UteyaVillage_SlowpokeNews_Producer:
    checkflag 0xE33 @ Slowpoke News completed today
    if SET _goto SlowpokeNewsCompleted_Producer
    faceplayer
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_Intro MSG_NORMAL
    showpokepic 0x40EE
    cry 0x40EE 0x0
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_PokemonAllTheRage MSG_NORMAL
    hidepokepic
    sound 0x15 @ Exclaim
    applymovement LASTTALKED m_Surprise
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_AsksPlayerToShowPokemon MSG_YESNO
    compare LASTRESULT NO
    if equal _goto SlowpokeNews_ChoseNotToShowPokemon
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_PromptingToShowPokemon MSG_NORMAL
    special 0x9F @ Choose pokemon from party
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto SlowpokeNews_ChoseNotToShowPokemon
    call BufferSpeciesName @ Buffer the name again, because it is overwritten when choosing a pokemon
    setvar 0x8003 0x0 @ Check species from party (0x8004 set by special 0x9F above)
    special2 LASTRESULT 0x18 @ Check species
    comparevartovar LASTRESULT 0x40EE @ Compare value of chosen pokemon to the daily pokemon
    if notequal _goto SlowpokeNews_ChoseWrongPokemon
    sound 0x15 @ Exclaim
    applymovement LASTTALKED m_Surprise
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_ChoseRightPokemon MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_CommentingOnPokemon MSG_NORMAL
    fadescreen FADEIN_BLACK
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_PokemonShown MSG_NORMAL
    compare 0x40EF 5
    if lessthan _call IncrementSlowpokeNewsReward
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_GivingReward MSG_NORMAL
    obtainitem ITEM_POKE_CHIP 0x40EF
    msgbox gText_UteyaVillage_SlowpokeNews_Producer_TalkingAboutIncreasingReward MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    setflag 0xE33 @ Slowpoke News completed today
    end

IncrementSlowpokeNewsReward:
    addvar 0x40EF 0x1
    return

SlowpokeNews_ChoseNotToShowPokemon:
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Producer_PlayerChoseNotToShow m_LookRight
    end

SlowpokeNews_ChoseWrongPokemon:
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Producer_ChoseWrongPokemon m_LookRight
    end

SlowpokeNewsCompleted_Producer:
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Producer_PokemonShown m_LookRight
    end

.global EventScript_UteyaVillage_SlowpokeNews_Reporter
EventScript_UteyaVillage_SlowpokeNews_Reporter:
    checkflag 0xE33 @ Slowpoke News completed today
    if SET _goto SlowpokeNewsCompleted_Reporter
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Reporter_PokemonNotShown m_LookUp
    end

SlowpokeNewsCompleted_Reporter:
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Reporter_PokemonShown m_LookUp
    end

.global EventScript_UteyaVillage_SlowpokeNews_Editor
EventScript_UteyaVillage_SlowpokeNews_Editor:
    checkflag 0xE33 @ Slowpoke News completed today
    if SET _goto SlowpokeNewsCompleted_Editor
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Editor_PokemonNotShown m_LookLeft
    end

SlowpokeNewsCompleted_Editor:
    npcchatwithmovement gText_UteyaVillage_SlowpokeNews_Editor_PokemonShown m_LookLeft
    end
