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
    setflag 0x3C @ Safety check - hide copycat in the gym when revisiting the overworld (and NPCs in many other places)
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
    call ResetUteyaVillageGymFlagsOnWhiteout
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

// NPC houses
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

.equ Clancy, 0x1
.equ Ena, 0x2

.global MapScript_UteyaVillage_ClancyAndEnasHouse
MapScript_UteyaVillage_ClancyAndEnasHouse:  
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_UteyaVillage_ClancyAndEnasHouse
    .byte MAP_SCRIPT_TERMIN

LevelScripts_UteyaVillage_ClancyAndEnasHouse:
    levelscript 0x4063 0x0 LevelScript_MeetingClancyAndEnaInTheirHome
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_MeetingClancyAndEnaInTheirHome:
    applymovement Clancy m_LookDown
    waitmovement Clancy
    pause DELAY_HALFSECOND
    applymovement Clancy m_Question
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancySeesPlayer MSG_NORMAL
    applymovement Ena m_LookDown
    pause DELAY_HALFSECOND
    applymovement Ena m_Surprise
    sound 0x15 @ Exclaim
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaSeesPlayer MSG_NORMAL
    applymovement Ena m_EnaWalksToPlayer
    applymovement Clancy m_ClancyWalksToPlayer
    waitmovement Ena
    pause DELAY_HALFSECOND
    applymovement Ena m_LookRight
    applymovement Clancy m_LookLeft
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancyAsksEnaIfSheRecognizesPlayer MSG_NORMAL
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaMentionsWhoPlayerIs MSG_NORMAL
    applymovement Ena m_LookDown
    applymovement Clancy m_LookDown
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement Clancy m_Question
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    sound 0x15 @ Exclaim
    applymovement Clancy m_Surprise
    waitmovement Clancy
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancyTellsPlayerTheyArentFriends MSG_NORMAL
    applymovement Ena m_LookRight
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaScoldsClancy MSG_NORMAL
    applymovement Clancy m_LookLeft
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancyPraisesEna MSG_NORMAL
    applymovement Ena m_Joy
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaAcceptsClancysPraise MSG_NORMAL
    applymovement Ena m_LookDown
    applymovement Clancy m_LookDown
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancyStartsOver MSG_NORMAL
    applymovement Ena m_LookRight
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaPraisesClancy MSG_NORMAL
    applymovement Ena m_LookDown
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_ClancyMentionsHisSkillset MSG_NORMAL
    applymovement Clancy m_ClancyReturnsToSeat
    waitmovement Clancy
    applymovement Ena m_EnaTakesClancysPlace
    waitmovement Ena
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Cutscene_EnaTalksAboutClancysSkills MSG_NORMAL
    applymovement Ena m_EnaReturnsToSeat
    waitmovement Ena
    addvar 0x4063 0x1
    end

.global EventScript_UteyaVillage_Clancy
EventScript_UteyaVillage_Clancy:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_OfferToChangePokemonNature MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChoseNature
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChipsForNatureChange
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_ChoosePokemon MSG_NORMAL
    special 0x9F @ Choose pokemon from party
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto ChoseNotToChoseNature
    bufferpartypokemon 0x0 0x8004
    copyvar 0x8005 0x8004 @ 0x8004 reset by scrolling multichoice
    special2 LASTRESULT 0x18 @ Check species
    compare LASTRESULT SPECIES_EGG
    if equal _goto ChoseEggToChangeNatureOf
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_PlayerChoseAPokemon MSG_NORMAL
    goto ChooseNature

ChooseNature:
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_AskingToChoseNature MSG_KEEPOPEN
    setvar 0x8000 0x10
    setvar 0x8001 0x8
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
    case 0, Adamant _call
    case 1, Bashful _call
    case 2, Bold _call
    case 3, Brave _call
    case 4, Calm _call
    case 5, Careful _call
    case 6, Docile _call
    case 7, Gentle _call
    case 8, Hardy _call
    case 9, Hasty _call
    case 10, Impish _call
    case 11, Jolly _call
    case 12, Lax _call
    case 13, Lonely _call
    case 14, Mild _call
    case 15, Modest _call
    case 16, Naive _call
    case 17, Naughty _call
    case 18, Quiet _call
    case 19, Quirky _call
    case 20, Rash _call
    case 21, Relaxed _call
    case 22, Sassy _call
    case 23, Serious _call
    case 24, Timid _call
    case 25, ChoseNotToChoseNature
    case 0x7F, ChoseNotToChoseNature @ When player hits B to close
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_NatureConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChooseNature
    callasm SwitchMonNature @ Nature change technically happens here, if LASTRESULT is true
    compare LASTRESULT FALSE @ Check if the pokemon is already this nature
    if equal _goto ChosenPokemonIsAlreadyChosenNature
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_StartingNatureChange MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_ChangingNature MSG_NORMAL
    fanfare 0x100
	waitfanfare
    fadescreen FADEIN_BLACK
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_NatureChangeComplete MSG_NORMAL
    removeitem ITEM_POKE_CHIP 10
    sound 0xF8 @ Money SE
    waitse
    npcchatwithmovement gText_UteyaVillage_ClancyAndEnasHouse_Clancy_TransactionComplete m_LookLeft
    end

Adamant:
    setvar 0x8006 NATURE_ADAMANT
    return

Bashful:
    setvar 0x8006 NATURE_BASHFUL
    return

Bold:
    setvar 0x8006 NATURE_BOLD
    return

Brave:
    setvar 0x8006 NATURE_BRAVE
    return

Calm:
    setvar 0x8006 NATURE_CALM
    return

Careful:
    setvar 0x8006 NATURE_CAREFUL
    return

Docile:
    setvar 0x8006 NATURE_DOCILE
    return

Gentle:
    setvar 0x8006 NATURE_GENTLE
    return

Hardy:
    setvar 0x8006 NATURE_HARDY
    return

Hasty:
    setvar 0x8006 NATURE_HASTY
    return

Impish:
    setvar 0x8006 NATURE_IMPISH
    return

Jolly:
    setvar 0x8006 NATURE_JOLLY
    return

Lax:
    setvar 0x8006 NATURE_LAX
    return

Lonely:
    setvar 0x8006 NATURE_LONELY
    return

Mild:
    setvar 0x8006 NATURE_MILD
    return

Modest:
    setvar 0x8006 NATURE_MODEST
    return

Naive:
    setvar 0x8006 NATURE_NAIVE
    return

Naughty:
    setvar 0x8006 NATURE_NAUGHTY
    return

Quiet:
    setvar 0x8006 NATURE_QUIET
    return

Quirky:
    setvar 0x8006 NATURE_QUIRKY
    return

Rash:
    setvar 0x8006 NATURE_RASH
    return

Relaxed:
    setvar 0x8006 NATURE_RELAXED
    return

Sassy:
    setvar 0x8006 NATURE_SASSY
    return

Serious:
    setvar 0x8006 NATURE_SERIOUS
    return

Timid:
    setvar 0x8006 NATURE_TIMID
    return

ChoseNotToChoseNature:
    npcchatwithmovement gText_UteyaVillage_ClancyAndEnasHouse_Clancy_PlayerChoseNotToChangeNature m_LookLeft
    end

NotEnoughPokeChipsForNatureChange:
    npcchatwithmovement gText_UteyaVillage_ClancyAndEnasHouse_Clancy_NotEnoughPokeChips m_LookLeft
    end

ChoseEggToChangeNatureOf:
    npcchatwithmovement gText_UteyaVillage_ClancyAndEnasHouse_Clancy_ChoseAnEgg m_LookLeft
    end

ChosenPokemonIsAlreadyChosenNature:
    msgbox gText_UteyaVillage_ClancyAndEnasHouse_Clancy_ChoseTheSameNatureItAlreadyIs MSG_NORMAL
    goto ChooseNature

.global EventScript_UteyaVillage_Ena
EventScript_UteyaVillage_Ena:
    npcchatwithmovement gText_UteyaVillage_ClancyAndEnasHouse_EnaChat m_LookRight
    end

m_EnaWalksToPlayer: .byte walk_down, walk_down, walk_right, walk_right, look_down, end_m
m_ClancyWalksToPlayer: .byte walk_down, walk_down, end_m
m_EnaTakesClancysPlace: .byte walk_right, look_down, end_m
m_EnaReturnsToSeat: .byte walk_left, walk_left, walk_left, walk_up, walk_up, look_right, end_m
m_ClancyReturnsToSeat: .byte walk_up, walk_up, look_left, end_m

// Trainer House
.global EventScript_UteyaVillage_TrainerHouse_Host
EventScript_UteyaVillage_TrainerHouse_Host:
    faceplayer
    msgbox gText_UteyaVillage_TrainerHouse_HostIntro MSG_NORMAL
    goto TrainerHouse_Menu
    end

TrainerHouse_Menu:
    msgbox gText_TrainerHouse_MenuIntro MSG_KEEPOPEN
    multichoiceoption gText_TrainerHouse_BattleChoice 0
	multichoiceoption gText_TrainerHouse_TrainerHouseRulesChoice 1
	multichoiceoption gText_TrainerHouse_RulesetChoice 2
    multichoiceoption gText_TrainerHouse_GrandPrizeChoice 3
    multichoiceoption gText_End 4
	multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
	case 0, Trainerhouse_battle
	case 1, Trainerhouse_trainerhouserules
	case 2, Trainerhouse_ruleset
	case 3, Trainerhouse_grandprize
	case 4, TrainerHouse_Common_End
    goto TrainerHouse_Common_End @ Cancelled with B

Trainerhouse_battle:
    checkflag 0xE34 @ Already battled here today
    if SET _goto TrainerHouse_Common_AlreadyBattledToday
    call TrainerHousePreBattleSetup
    call TrainerHouse_Common_MoveToBattlePosition
    setflag 0x90E @ Scale trainer levels
    setflag 0x92E @ Benjamin Butterfree battles
    applymovement 0x1 m_LookUp
    @ First Opponent
    msgbox gText_UteyaVillage_TrainerHouse_FirstOpponentArriving MSG_NORMAL
    setvar 0x8001 0x5
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_UteyaVillage_TrainerHouse_B1PicknickerLisaIntro MSG_NORMAL
    trainerbattle9 0x0 472 0x0 gText_UteyaVillage_TrainerHouse_B1PicknickerLisaWin gText_UteyaVillage_TrainerHouse_B1PicknickerLisaLose
    call HandleBattleEnded
    @ Second Opponent
    msgbox gText_UteyaVillage_TrainerHouse_SecondOpponentArriving MSG_NORMAL
    setvar 0x8001 0x6
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_UteyaVillage_TrainerHouse_B2SwimmerTysonIntro MSG_NORMAL
    trainerbattle9 0x0 473 0x0 gText_UteyaVillage_TrainerHouse_B2SwimmerTysonWin gText_UteyaVillage_TrainerHouse_B2SwimmerTysonLose
    call HandleBattleEnded
    @ Third Opponent
    msgbox gText_UteyaVillage_TrainerHouse_ThirdOpponentArriving MSG_NORMAL
    setvar 0x8001 0x7
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_UteyaVillage_TrainerHouse_B3ScientistWilfordIntro MSG_NORMAL
    trainerbattle9 0x0 474 0x0 gText_UteyaVillage_TrainerHouse_B3ScientistWilfordWin gText_UteyaVillage_TrainerHouse_B3ScientistWilfordLose
    call HandleBattleEnded
    msgbox gText_UteyaVillage_TrainerHouse_AllOpponentsDefeated MSG_NORMAL
    call TrainerHouse_Common_ReturnToHost
    goto TrainerHouseGivePrizes

TrainerHousePreBattleSetup:
    msgbox gText_UteyaVillage_TrainerHouse_BattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto TrainerHouse_Common_End
    msgbox gText_UteyaVillage_TrainerHouse_ChoseBattle MSG_NORMAL
    setflag 0xE34 @ Already battled today
    setvar 0x8000 0xFEFE @ Continue lost battles
    msgbox gText_UteyaVillage_TrainerHouse_HealingPokemon MSG_NORMAL
    call PlayerHeal
    msgbox gText_UteyaVillage_TrainerHouse_PreChallengeComment MSG_NORMAL
    setvar 0x4090 0x0 @ 0 win streak
    return

HandleBattleEnded:
    compare LASTRESULT TRUE
    if equal _goto TrainerHouseStreakLost
    fanfare 0x10D @ Victory
    msgbox gText_TrainerHouse_StreakContinues MSG_KEEPOPEN
    waitfanfare
    call TrainerHouse_Common_OpponentLeaves
    addvar 0x4090 0x1
    return

TrainerHouseStreakLost:
    fanfare 0x10F @ Failure
    msgbox gText_UteyaVillage_TrainerHouse_StreakLost MSG_KEEPOPEN
    waitfanfare
    fadescreen FADEOUT_BLACK
    hidesprite 0x5
    hidesprite 0x6
    hidesprite 0x7
    setflag 0x37 @ Hide opponents
    fadescreen FADEIN_BLACK
    call TrainerHouse_Common_ReturnToHost
    compare 0x4090 0x0
    if equal _goto TrainerHouseDidNotBeatAnyTrainers
    goto TrainerHouseGivePrizes

TrainerHouseGivePrizes:
    buffernumber 0x0 0x4090
    fanfare 0x13D @ Gym victory
    msgbox gText_TrainerHouse_AnalysisBeatTrainers MSG_KEEPOPEN
    waitfanfare
    compare 0x4090 0x1
    if equal _call TrainerHouseTier1Prizes
    compare 0x4090 0x2
    if equal _call TrainerHouseTier2Prizes
    compare 0x4090 0x3
    if equal _call TrainerHouseTier3Prizes
    msgbox gText_TrainerHouse_EndOfBattles MSG_NORMAL
    goto Trainerhouse_ResetStateAtEnd

TrainerHouseTier1Prizes:
    random 0x2
    copyvar 0x8002 LASTRESULT
    compare 0x8002 0x0
    if equal _call TrainerHouse_Common_GiveUltraBall
    compare 0x8002 0x1
    if equal _call TrainerHouse_Common_GiveMaxPotion
    return

TrainerHouseTier2Prizes:
    random 0x3
    copyvar 0x8003 LASTRESULT
    compare 0x8003 0x0
    if equal _call TrainerHouse_Common_GiveUltraBall
    compare 0x8003 0x1
    if equal _call TrainerHouse_Common_GiveFullRestore
    compare 0x8003 0x2
    if equal _call TrainerHouse_Common_GiveRevive
    pause DELAY_HALFSECOND
    call TrainerHouseTier1Prizes
    return

TrainerHouseTier3Prizes:
    random 0x3
    copyvar 0x8004 LASTRESULT
    compare 0x8004 0x0
    if equal _call TrainerHouse_Common_GiveFullRestore
    compare 0x8004 0x1
    if equal _call TrainerHouse_Common_GiveMaxRevive
    compare 0x8004 0x2
    if equal _call TrainerHouse_Common_GivePPMax
    pause DELAY_HALFSECOND
    call TrainerHouseTier2Prizes
    call TrainerHouseCheckForGrandPrize
    return

TrainerHouseCheckForGrandPrize:
    incrementgamestat 25
    checkflag 0x277 @ Got the Pokechip charm
    if NOT_SET _call TrainerHouseGiveGrandPrize
    return

TrainerHouseGiveGrandPrize:
    msgbox gText_UteyaVillage_TrainerHouse_GrandPrizeAwarded MSG_NORMAL
    fanfare 0x10C @ Big Celebration
    obtainitem ITEM_POKE_CHIP_CHARM 0x1
    waitfanfare
    setflag 0x277 @ Got the Pokechip charm
    return

TrainerHouseDidNotBeatAnyTrainers:
    msgbox gText_TrainerHouse_AnalysisBeatNoTrainers MSG_NORMAL
    goto Trainerhouse_ResetStateAtEnd

Trainerhouse_ResetStateAtEnd:
    setvar 0x4090 0x0 @ Reset win streak
    setvar 0x8000 0x0 @ Turn off continuing after losing
    setvar 0x8001 0x0 @ Reset temp trainer var
    setvar 0x8002 0x0 @ Reset prize 1 pool var
    setvar 0x8003 0x0 @ Reset prize 2 pool var
    setvar 0x8004 0x0 @ Reset prize 3 pool var
    clearflag 0x92E @ Turn off Benjamin Butterfree battles
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call DisableTrainerScalingFlag
    msgbox gText_TrainerHouse_HealingPokemonAtEnd MSG_NORMAL
    call PlayerHeal
    goto TrainerHouse_Common_End

Trainerhouse_trainerhouserules:
    msgbox gText_TrainerHouse_ChoseTrainerHouseRules MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_ruleset:
    msgbox gText_UteyaVillage_TrainerHouse_ChoseRuleset MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_grandprize:
    msgbox gText_UteyaVillage_TrainerHouse_ChoseGrandPrize MSG_NORMAL
    goto TrainerHouse_Menu

.global EventScript_UteyaVillage_TrainerHouse_Man
EventScript_UteyaVillage_TrainerHouse_Man:
    msgbox gText_UteyaVillage_TrainerHouse_Man MSG_NORMAL
    faceplayer
    npcchatwithmovement gText_UteyaVillage_TrainerHouse_ManAfterFacingPlayer m_LookUp
    end

.global EventScript_UteyaVillage_TrainerHouse_Boy
EventScript_UteyaVillage_TrainerHouse_Boy:
    npcchat gText_UteyaVillage_TrainerHouse_Boy
    end

.global EventScript_UteyaVillage_TrainerHouse_Girl
EventScript_UteyaVillage_TrainerHouse_Girl:
    npcchatwithmovement gText_UteyaVillage_TrainerHouse_Girl m_LookLeft
    end

// Gym

.equ CopyCatNPC, 0x1
.equ VarGymProgress, 0x40A8

.equ FloorTile, 0x281
.equ LeftShadedFloorTile, 0x288
.equ ThreeQuarterShadedFloorTile, 0x28A
.equ WallUpper, 0x295
.equ WallLower, 0x29D
.equ WallDividerTop, 0x291
.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_UteyaVillage_Gym
MapScript_UteyaVillage_Gym:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_UteyaVillageGym_UpdateMapTiles
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UteyaVillageGym_UpdateMapTiles:
    compare VarGymProgress 0x1
    if greaterorequal _call PuzzleOneComplete
    compare VarGymProgress 0x2
    if greaterorequal _call PuzzleTwoComplete
    compare VarGymProgress 0x3
    if greaterorequal _call PuzzleThreeComplete
    compare VarGymProgress 0x4
    if greaterorequal _call PuzzleFourComplete
    compare VarGymProgress 0x5
    if greaterorequal _call PuzzleFiveComplete
    end

HandleSwitchesPressed:
    setvar 0x8004 CopyCatNPC
    callasm CalculateEventPosition
    comparevartovar 0x4000 0x4002 @ X coords
    if notequal _goto End
    comparevartovar 0x4001 0x4003 @ Y coords
    if notequal _goto End
    @ Both switches pressed at the same time
    addvar VarGymProgress 0x1
    playse 0x19 @ Correct
    applymovement CopyCatNPC m_Joy @ TODO: only shows sometimes? waiting for movement or putting a delay in does weird things
    waitse
    pause DELAY_HALFSECOND
    call SetCopyCatGender
    compare VarGymProgress 0x5
    if equal _call AllPuzzlesCompleteMessage
    if notequal _call PuzzlesRemainingMessage 
    return

AllPuzzlesCompleteMessage:
    msgbox gText_UteyaVillage_Gym_Copycat_BothSwitchesPressed_FinalPuzzle MSG_NORMAL
    return

PuzzlesRemainingMessage:
    msgbox gText_UteyaVillage_Gym_Copycat_BothSwitchesPressed MSG_NORMAL
    return

PuzzleOneComplete:
    call HideFirstWall
    setflag 0x3C @ Copycat NPC is hidden
    setflag 0x82F @ Player can run again
    setvar 0x4000 0x5 @ New X coord to move copycat to
    setvar 0x4001 0x8 @ New Y coord to move copycat to
    call MoveCopyCatToPuzzle
    return

HideFirstWall:
    setmaptile 0x4 0x8 FloorTile Passable
    setmaptile 0x4 0x9 LeftShadedFloorTile Passable
    setmaptile 0x4 0xA LeftShadedFloorTile Passable
    setmaptile 0x4 0xB FloorTile Passable
    return

PuzzleTwoComplete:
    call HideSecondWall
    setflag 0x3C @ Copycat NPC is hidden
    setflag 0x82F @ Player can run again
    setvar 0x4000 0xA @ New X coord to move copycat to
    setvar 0x4001 0x6 @ New Y coord to move copycat to
    call MoveCopyCatToPuzzle
    return

HideSecondWall:
    setmaptile 0x8 0x3 WallUpper Impassable
    setmaptile 0x8 0x4 WallLower Impassable
    setmaptile 0x8 0x5 WallDividerTop Passable
    setmaptile 0x9 0x3 WallUpper Impassable
    setmaptile 0x9 0x4 WallLower Impassable
    setmaptile 0x9 0x5 WallDividerTop Passable
    setmaptile 0xA 0x5 FloorTile Passable
    return

PuzzleThreeComplete:
    call HideThirdWall
    setflag 0x3C @ Copycat NPC is hidden
    setflag 0x82F @ Player can run again
    setvar 0x4000 0xE @ New X coord to move copycat to
    setvar 0x4001 0xB @ New Y coord to move copycat to
    call MoveCopyCatToPuzzle
    return

HideThirdWall:
    setmaptile 0xD 0x8 FloorTile Passable
    setmaptile 0xD 0x9 LeftShadedFloorTile Passable
    setmaptile 0xD 0xA LeftShadedFloorTile Passable
    setmaptile 0xD 0xB FloorTile Passable
    return

PuzzleFourComplete:
    call HideFourthWall
    setflag 0x3C @ Copycat NPC is hidden
    setflag 0x82F @ Player can run again
    setvar 0x4000 0x13 @ New X coord to move copycat to
    setvar 0x4001 0xE @ New Y coord to move copycat to
    call MoveCopyCatToPuzzle
    return

HideFourthWall:
    setmaptile 0x11 0xB WallUpper Impassable
    setmaptile 0x11 0xC WallLower Impassable
    setmaptile 0x11 0xD WallDividerTop Passable
    setmaptile 0x12 0xB WallUpper Impassable
    setmaptile 0x12 0xC WallLower Impassable
    setmaptile 0x12 0xD WallDividerTop Passable
    setmaptile 0x13 0xD FloorTile Passable
    return

PuzzleFiveComplete:
    call HideFifthWallAndGymShortcuts
    setflag 0x3C @ Copycat NPC is hidden
    setflag 0x82F @ Player can run again
    return

HideFifthWallAndGymShortcuts:
    @ Fifth wall
    setmaptile 0x16 0x6 FloorTile Passable
    setmaptile 0x16 0x7 LeftShadedFloorTile Passable
    setmaptile 0x16 0x8 LeftShadedFloorTile Passable
    setmaptile 0x16 0x9 FloorTile Passable
    @ Gym Shortcut at entrance
    setmaptile 0x8 0x11 WallUpper Impassable
    setmaptile 0x8 0x12 WallLower Impassable
    setmaptile 0x8 0x13 ThreeQuarterShadedFloorTile Passable
    setmaptile 0x9 0x13 FloorTile Passable
    @ Gym Shortcut at leaders
    setmaptile 0x1A 0x2 WallUpper Impassable
    setmaptile 0x1A 0x3 WallLower Impassable
    setmaptile 0x1A 0x4 ThreeQuarterShadedFloorTile Passable
    setmaptile 0x1A 0x5 FloorTile Passable
    setmaptile 0x1B 0x5 FloorTile Passable
    return

MoveCopyCatToPuzzle:
    movesprite2 CopyCatNPC 0x4000 0x4001
    warpmuted 14 9 0xFF 0x4004 0x4005 @ Warp into the middle of the puzzle room. If the map is not reloaded in this way, the copycat's coordinates get locked and will not update as the player moves
    return

@ NOTE: For a copycat NPC to work, they must have movement type 53 (Copy Player),
@ and also have a movment value up to FF (15x15 movement grid). If it is 00 they'll have a default radius of 3! 
.global EventScript_UteyaVillage_Gym_Copycat
EventScript_UteyaVillage_Gym_Copycat:
    faceplayer
    call SetCopyCatGender
    msgbox gText_UteyaVillage_Gym_Copycat_AskPlayerWhatTheyNeed MSG_YESNO
    compare LASTRESULT NO
    if equal _goto TakeABreak
    msgbox gText_UteyaVillage_Gym_Copycat_ContinuingChallenge MSG_NORMAL
    switch PLAYERFACING
    case INTERNAL_DOWN, CopyCatLookDown
    case INTERNAL_UP, CopyCatLookUp
    case INTERNAL_LEFT, CopyCatLookLeft
    case INTERNAL_RIGHT, CopyCatLookRight
    return

CopyCatLookDown:
    applymovement LASTTALKED m_LookDown
    return

CopyCatLookUp:
    applymovement LASTTALKED m_LookUp
    return

CopyCatLookLeft:
    applymovement LASTTALKED m_LookLeft
    return

CopyCatLookRight:
    applymovement LASTTALKED m_LookRight
    return

.global TileScript_UteyaVillage_Gym_FirstPuzzle
TileScript_UteyaVillage_Gym_FirstPuzzle:
    lockall
    checkflag 0x82F @ Player cannot run
    if NOT_SET _goto GymPuzzleConfirmationCheckRoomOneAndTwo
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    fadescreen FADEOUT_BLACK
    call ShowCopyCat
    lockall @ Second lock needed to prevent the copycat from mimicking the player's last input before triggering the tile event
    fadescreen FADEIN_BLACK
    applymovement PLAYER m_LookRight
    applymovement CopyCatNPC m_LookLeft
    msgbox gText_UteyaVillage_Gym_Copycat_IntroducesThemselves MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement CopyCatNPC m_LookUp @ Need to reset orientation of both player and copycat so they walk in the same direction (if not facing the same direction, copycat's movement will be rotated 90/180/270 degrees)
    waitmovement CopyCatNPC
    releaseall
    end

.global TileScript_UteyaVillage_Gym_SecondPuzzle
TileScript_UteyaVillage_Gym_SecondPuzzle:
    lockall
    checkflag 0x82F @ Player cannot run
    if NOT_SET _goto GymPuzzleConfirmationCheckRoomOneAndTwo
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    fadescreen FADEOUT_BLACK
    call ShowCopyCat
    lockall @ Second lock needed to prevent the copycat from mimicking the player's last input before triggering the tile event
    fadescreen FADEIN_BLACK
    applymovement PLAYER m_LookRight
    applymovement CopyCatNPC m_LookLeft
    msgbox gText_UteyaVillage_Gym_Copycat_SubsequentRooms MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement CopyCatNPC m_LookUp @ Need to reset orientation of both player and copycat so they walk in the same direction (if not facing the same direction, copycat's movement will be rotated 90/180/270 degrees)
    waitmovement CopyCatNPC
    releaseall
    end

.global TileScript_UteyaVillage_Gym_ThirdAndFifthPuzzles
TileScript_UteyaVillage_Gym_ThirdAndFifthPuzzles:
    lockall
    checkflag 0x82F @ Player cannot run
    if NOT_SET _goto GymPuzzleConfirmationCheckRoomThreeAndFive
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    fadescreen FADEOUT_BLACK
    call ShowCopyCat
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    lockall @ Second lock needed to prevent the copycat from mimicking the player's last input before triggering the tile event
    applymovement PLAYER m_LookRight
    fadescreen FADEIN_BLACK
    msgbox gText_UteyaVillage_Gym_Copycat_SubsequentRooms MSG_NORMAL
    releaseall
    end

.global TileScript_UteyaVillage_Gym_FourthPuzzle
TileScript_UteyaVillage_Gym_FourthPuzzle:
    lockall
    checkflag 0x82F @ Player cannot run
    if NOT_SET _goto GymPuzzleConfirmationCheckRoomFour
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    fadescreen FADEOUT_BLACK
    call ShowCopyCat
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    applymovement PLAYER m_LookDown
    applymovement CopyCatNPC m_LookDown
    fadescreen FADEIN_BLACK
    msgbox gText_UteyaVillage_Gym_Copycat_SubsequentRooms MSG_NORMAL
    end

GymPuzzleConfirmationCheckRoomOneAndTwo:
    call EventScript_UteyaVillage_Gym_Copycat
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    end

GymPuzzleConfirmationCheckRoomThreeAndFive:
    call EventScript_UteyaVillage_Gym_Copycat
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    end

GymPuzzleConfirmationCheckRoomFour:
    call EventScript_UteyaVillage_Gym_Copycat
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    end

TakeABreak:
    msgbox gText_UteyaVillage_Gym_Copycat_PausingChallenge MSG_NORMAL
    setflag 0x82F @ Player can run again
    setflag 0x3C @ Hide Copycat again
    warpmuted 14 9 0xFF 0x4 0x14
    end

ShowCopyCat:
    call SetCopyCatGender
    clearflag 0x82F @ Player cannot run for duration of gym puzzle
    clearflag 0x3C @ Show copycat on map reload
    showsprite CopyCatNPC
    return

SetCopyCatGender:
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _call SetCopycatFemale
    if notequal _call SetCopycatMale
    return

SetCopycatFemale:
    setvar 0x5029 7
    textcolor RED
    bufferstring 0x0 gText_CopycatName_Female
    return

SetCopycatMale:
    setvar 0x5029 0
    textcolor BLUE
    bufferstring 0x0 gText_CopycatName_Male
    return

.global TileScript_UteyaVillage_Gym_Puzzle1BottomLeft
TileScript_UteyaVillage_Gym_Puzzle1BottomLeft:
    lock
    setvar 0x4000 0x3 @ Set required NPC positions to the other switch
    setvar 0x4001 0xD
    setvar 0x4004 0x2 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xE
    call HandleSwitchesPressed
    call PuzzleOneComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle1TopRight
TileScript_UteyaVillage_Gym_Puzzle1TopRight:
    lock
    setvar 0x4000 0x2 @ Set required NPC positions to the other switch
    setvar 0x4001 0xE
    setvar 0x4004 0x3 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xD
    call HandleSwitchesPressed
    call PuzzleOneComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle2TopRight
TileScript_UteyaVillage_Gym_Puzzle2TopRight:
    lock
    setvar 0x4000 0x4 @ Set required NPC positions to the other switch
    setvar 0x4001 0x6
    setvar 0x4004 0x6 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0x4
    call HandleSwitchesPressed
    call PuzzleTwoComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle2BottomLeft
TileScript_UteyaVillage_Gym_Puzzle2BottomLeft:
    lock
    setvar 0x4000 0x6 @ Set required NPC positions to the other switch
    setvar 0x4001 0x4
    setvar 0x4004 0x4 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0x6
    call HandleSwitchesPressed
    call PuzzleTwoComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle3TopLeft
TileScript_UteyaVillage_Gym_Puzzle3TopLeft:
    lock
    setvar 0x4000 0xF @ Set required NPC positions to the other switch
    setvar 0x4001 0x6
    setvar 0x4004 0xC @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0x4
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle3BottomRight
TileScript_UteyaVillage_Gym_Puzzle3BottomRight:
    lock
    setvar 0x4000 0xC @ Set required NPC positions to the other switch
    setvar 0x4001 0x4
    setvar 0x4004 0xF @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0x6
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle4TopRight
TileScript_UteyaVillage_Gym_Puzzle4TopRight:
    lock
    setvar 0x4000 0xD @ Set required NPC positions to the other switch
    setvar 0x4001 0xE
    setvar 0x4004 0xE @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xD
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle4BottomLeft
TileScript_UteyaVillage_Gym_Puzzle4BottomLeft:
    lock
    setvar 0x4000 0xE @ Set required NPC positions to the other switch
    setvar 0x4001 0xD
    setvar 0x4004 0xD @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xE
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle5BottomLeft
TileScript_UteyaVillage_Gym_Puzzle5BottomLeft:
    lock
    setvar 0x4000 0x17 @ Set required NPC positions to the other switch
    setvar 0x4001 0xB
    setvar 0x4004 0x14 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xE
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global TileScript_UteyaVillage_Gym_Puzzle5TopRight
TileScript_UteyaVillage_Gym_Puzzle5TopRight:
    lock
    setvar 0x4000 0x14 @ Set required NPC positions to the other switch
    setvar 0x4001 0xE
    setvar 0x4004 0x17 @ Set player's intended reset point after the puzzle's completion
    setvar 0x4005 0xB
    call HandleSwitchesPressed
    call PuzzleThreeComplete
    end

.global EventScript_UteyaVillage_Gym_GymExpert
EventScript_UteyaVillage_Gym_GymExpert:
    checkflag 0x827 @ Uteya gym badge
    if SET _goto EventScript_UteyaVillage_Gym_ExpertBadgeObtained
    npcchat gText_UteyaVillage_Gym_ExpertTips
    end

EventScript_UteyaVillage_Gym_ExpertBadgeObtained:
    npcchat gText_UteyaVillage_Gym_ExpertBadgeObtained
    end

.global EventScript_UteyaVillage_Gym_Michael
EventScript_UteyaVillage_Gym_Michael:
    trainerbattle11 0xB 475 476 3 4 0x0 gText_UteyaVillageGym_Michael_Intro gText_UteyaVillageGym_Leo_Intro gText_UteyaVillageGym_Michael_Defeat gText_UteyaVillageGym_Leo_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Michael_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Leo
EventScript_UteyaVillage_Gym_Leo:
    trainerbattle11 0xB 476 475 4 3 0x0 gText_UteyaVillageGym_Leo_Intro gText_UteyaVillageGym_Michael_Intro gText_UteyaVillageGym_Leo_Defeat gText_UteyaVillageGym_Michael_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Leo_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Bonnie
EventScript_UteyaVillage_Gym_Bonnie:
    trainerbattle11 0xB 478 477 6 5 0x0 gText_UteyaVillageGym_Bonnie_Intro gText_UteyaVillageGym_Clyde_Intro gText_UteyaVillageGym_Bonnie_Defeat gText_UteyaVillageGym_Clyde_Defeat gText_Common_CannotDoubleBattle_Female gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Bonnie_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Clyde
EventScript_UteyaVillage_Gym_Clyde:
    trainerbattle11 0xB 477 478 5 6 0x0 gText_UteyaVillageGym_Bonnie_Intro gText_UteyaVillageGym_Clyde_Intro gText_UteyaVillageGym_Bonnie_Defeat gText_UteyaVillageGym_Clyde_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_UteyaVillageGym_Clyde_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Jessie
EventScript_UteyaVillage_Gym_Jessie:
    trainerbattle11 0xB 479 480 7 8 0x0 gText_UteyaVillageGym_James_Intro gText_UteyaVillageGym_Jessie_Intro gText_UteyaVillageGym_Jessie_Defeat gText_UteyaVillageGym_James_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_UteyaVillageGym_Jessie_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_James
EventScript_UteyaVillage_Gym_James:
    trainerbattle11 0xB 480 479 8 7 0x0 gText_UteyaVillageGym_Jessie_Intro gText_UteyaVillageGym_James_Intro gText_UteyaVillageGym_James_Defeat gText_UteyaVillageGym_Jessie_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_UteyaVillageGym_James_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Mike
EventScript_UteyaVillage_Gym_Mike:
    trainerbattle11 0xB 481 482 9 10 0x0 gText_UteyaVillageGym_Diane_Intro gText_UteyaVillageGym_Mike_Intro gText_UteyaVillageGym_Mike_Defeat gText_UteyaVillageGym_Diane_Defeat gText_Common_CannotDoubleBattle_Female gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Mike_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Diane
EventScript_UteyaVillage_Gym_Diane:
    trainerbattle11 0xB 482 481 10 9 0x0 gText_UteyaVillageGym_Mike_Intro gText_UteyaVillageGym_Diane_Intro gText_UteyaVillageGym_Diane_Defeat gText_UteyaVillageGym_Mike_Defeat gText_Common_CannotDoubleBattle_Female gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Diane_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Hannibal
EventScript_UteyaVillage_Gym_Hannibal:
    trainerbattle11 0xB 483 484 11 12 0x0 gText_UteyaVillageGym_Clarice_Intro gText_UteyaVillageGym_Hannibal_Intro gText_UteyaVillageGym_Hannibal_Defeat gText_UteyaVillageGym_Clarice_Defeat gText_Common_CannotDoubleBattle_Female gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Hannibal_Chat MSG_NORMAL
    end

.global EventScript_UteyaVillage_Gym_Clarice
EventScript_UteyaVillage_Gym_Clarice:
    trainerbattle11 0xB 484 483 12 11 0x0 gText_UteyaVillageGym_Hannibal_Intro gText_UteyaVillageGym_Clarice_Intro gText_UteyaVillageGym_Clarice_Defeat gText_UteyaVillageGym_Hannibal_Defeat gText_Common_CannotDoubleBattle_Female gText_Common_CannotDoubleBattle_Male
    msgbox gText_UteyaVillageGym_Clarice_Chat MSG_NORMAL
    end

.global SignScript_UteyaVillageGym_Placard
SignScript_UteyaVillageGym_Placard:
    checkflag 0x827 @ Uteya gym badge
    if SET _goto SignScript_UteyaVillageGym_Placard_AfterBadge
    msgbox gText_UteyaVillageGym_Winners MSG_SIGN
    end

SignScript_UteyaVillageGym_Placard_AfterBadge:
    msgbox gText_UteyaVillageGym_WinnersWithBadge MSG_SIGN
    end
