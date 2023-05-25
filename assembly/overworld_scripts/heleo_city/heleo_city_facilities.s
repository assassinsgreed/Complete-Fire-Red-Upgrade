.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoFacilities_PokemonCenter
MapScript_HeleoFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x05 @ Originally Lavender Town
    end

.global EventScript_HeleoFacilities_BoredKid
EventScript_HeleoFacilities_BoredKid:
    msgbox gText_HeleoCityFacilities_BoredKid MSG_NORMAL
    end

.global EventScript_HeleoFacilities_KidsMom
EventScript_HeleoFacilities_KidsMom:
    npcchat gText_HeleoCityFacilities_KidsMom
    end

.global EventScript_HeleoFacilities_Mart_PokeballShop
EventScript_HeleoFacilities_Mart_PokeballShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart HeleoPokemart_PokeballStock
    goto EventScript_EndMart

HeleoPokemart_PokeballStock:
    .hword ITEM_HEAL_BALL
    .hword ITEM_NEST_BALL
    .hword ITEM_NET_BALL
    .hword ITEM_REPEAT_BALL
    .hword ITEM_DUSK_BALL
    .hword ITEM_QUICK_BALL
    .hword ITEM_TIMER_BALL
    .hword ITEM_NONE

.global EventScript_HeleoFacilities_Mart_QuickTimerBallQuiz
EventScript_HeleoFacilities_Mart_QuickTimerBallQuiz:
    lock
    faceplayer
    msgbox gText_HeleoCityFacilities_QuickTimerBallQuiz MSG_YESNO
    msgbox gText_HeleoCityFacilities_QuickTimerBallAnswer MSG_NORMAL
    checkflag 0x247 @ Received Quick and Timer ball gift
    if NOT_SET _goto QuickTimerBallGift
    goto End

QuickTimerBallGift:
    msgbox gText_HeleoCityFacilities_QuickTimerBallGift MSG_NORMAL
    obtainitem ITEM_QUICK_BALL 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_TIMER_BALL 0x1
    setflag 0x247 @ Received Quick and Timer ball gift
    goto End

.global EventScript_HeleoFacilities_TrainerHouse_Host
EventScript_HeleoFacilities_TrainerHouse_Host:
    lock
    faceplayer
    msgbox gText_HeleoCityFacilities_TrainerHouse_HostIntro MSG_NORMAL
    goto TrainerHouse_Menu
    
TrainerHouse_Menu:
    msgbox gText_HeleoCityFacilities_TrainerHouse_MenuIntro MSG_KEEPOPEN
    multichoiceoption gText_HeleoCityFacilities_TrainerHouse_BattleChoice 0
	multichoiceoption gText_HeleoCityFacilities_TrainerHouse_TrainerHouseRulesChoice 1
	multichoiceoption gText_HeleoCityFacilities_TrainerHouse_RulesetChoice 2
    multichoiceoption gText_End 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, Trainerhouse_battle
	case 1, Trainerhouse_trainerhouserules
	case 2, Trainerhouse_ruleset
	case 3, Trainerhouse_end

Trainerhouse_battle:
    checkflag 0xE0B @ Already battled today
    if SET _goto TrainerHouseAlreadyBattledToday
    call TrainerHouseChoosePokemon
    call MoveToBattlePosition
    setflag 0x90E @ Scale trainer levels
    applymovement 0x1 m_LookUp
    msgbox gText_HeleoCityFacilities_TrainerHouse_FirstOpponentArriving MSG_NORMAL
    @ First Opponent
    setvar 0x8001 0x2A @ Opponent trainer sprite (Female psychic)
    call OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaIntro MSG_NORMAL
    trainerbattle9 0x0 0x62 0x0 gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaWin gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaLose
    call OpponentLeaves
    compare LASTRESULT TRUE
    if equal _goto TrainerHouseStreakLost
    addvar 0x4090 0x1
    @ Second Opponent
    setvar 0x8001 0x34 @ Opponent trainer sprite (Supernerd)
    call OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenIntro MSG_NORMAL
    trainerbattle9 0x0 0x63 0x0 gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenWin gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenLose
    call OpponentLeaves
    compare LASTRESULT TRUE
    if equal _goto TrainerHouseStreakLost
    addvar 0x4090 0x1
    @ Third Opponent
    setvar 0x8001 0x2F @ Opponent trainer sprite (Male Cooltrainer)
    call OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetIntro MSG_NORMAL
    trainerbattle9 0x0 0x64 0x0 gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetWin gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetLose
    call OpponentLeaves
    compare LASTRESULT TRUE
    if equal _goto TrainerHouseStreakLost
    addvar 0x4090 0x1
    applymovement PLAYER m_ReturnToHost
    waitmovement ALLEVENTS
    applymovement 0x1 m_LookLeft
    goto TrainerHouseGivePrizes

TrainerHouseChoosePokemon:
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChooseThreePokemon MSG_NORMAL
    special 0x27 @ Back up the player's party
    special 0xF5 @ Choose 3 Pokemon
    waitstate
    compare LASTRESULT FALSE @ Cancelled
    if equal _goto Trainerhouse_end
    msgbox gText_HeleoCityFacilities_TrainerHouse_PokemonSelectionConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto Trainerhouse_end
    setflag 0xE0B @ Already battled today
    setvar 0x8000 0xFEFE @ Continue lost battles TODO: Revert this when battling finishes successfully or on failure
    msgbox gText_HeleoCityFacilities_TrainerHouse_HealingPokemon MSG_NORMAL
    call PlayerHeal
    msgbox gText_HeleoCityFacilities_TrainerHouse_PokemonSelectionFinalized MSG_NORMAL
    setvar 0x4090 0x0 @ 0 win streak
    return

TrainerHouseStreakLost:
    msgbox gText_HeleoCityFacilities_TrainerHouse_StreakLost MSG_NORMAL
    applymovement PLAYER m_ReturnToHost
    waitmovement ALLEVENTS
    applymovement 0x1 m_LookLeft
    compare 0x4090 0x0
    if equal _goto TrainerHouseDidNotBeatAnyTrainers
    goto TrainerHouseGivePrizes

TrainerHouseGivePrizes:
    buffernumber 0x0 0x4090
    msgbox gText_HeleoCityFacilities_TrainerHouse_AnalysisBeatTrainers MSG_NORMAL
    compare 0x4090 0x1
    if equal _call TrainerHouseTier1Prizes
    compare 0x4090 0x2
    if equal _call TrainerHouseTier2Prizes
    compare 0x4090 0x3
    if equal _call TrainerHouseTier3Prizes
    msgbox gText_HeleoCityFacilities_TrainerHouse_EndOfBattles MSG_NORMAL
    goto Trainerhouse_end

TrainerHouseTier1Prizes:
    random 0x2
    compare LASTRESULT 0x0
    if equal _call TrainerHouseGivePokeball
    compare LASTRESULT 0x1
    if equal _call TrainerHouseGivePotion
    return

TrainerHouseTier2Prizes:
    random 0x3
    compare LASTRESULT 0x0
    if equal _call TrainerHouseGiveGreatball
    compare LASTRESULT 0x1
    if equal _call TrainerHouseGiveSuperPotion
    compare LASTRESULT 0x2
    if equal _call TrainerHouseGiveRepel
    pause DELAY_HALFSECOND
    call TrainerHouseTier1Prizes
    return

TrainerHouseTier3Prizes:
    random 0x3
    compare LASTRESULT 0x0
    if equal _call TrainerHouseGiveUltraBall
    compare LASTRESULT 0x1
    if equal _call TrainerHouseGiveMoomooMilk
    compare LASTRESULT 0x2
    if equal _call TrainerHouseFullHeal
    pause DELAY_HALFSECOND
    call TrainerHouseTier2Prizes
    call TrainerHouseCheckForGrandPrize
    return

TrainerHouseGivePokeball:
    obtainitem ITEM_POKE_BALL 0x1
    return

TrainerHouseGivePotion:
    obtainitem ITEM_POTION 0x1
    return

TrainerHouseGiveGreatball:
    obtainitem ITEM_GREAT_BALL 0x1
    return

TrainerHouseGiveSuperPotion:
    obtainitem ITEM_SUPER_POTION 0x1
    return

TrainerHouseGiveRepel:
    obtainitem ITEM_REPEL 0x1
    return

TrainerHouseGiveUltraBall:
    obtainitem ITEM_ULTRA_BALL 0x1
    return

TrainerHouseGiveMoomooMilk:
    obtainitem ITEM_MOOMOO_MILK 0x1
    return

TrainerHouseFullHeal:
    obtainitem ITEM_FULL_HEAL 0x1
    return

TrainerHouseCheckForGrandPrize:
    checkflag 0x24F @ Got the bike
    if NOT_SET _call TrainerHouseGiveGrandPrize
    return

TrainerHouseGiveGrandPrize:
    msgbox gText_HeleoCityFacilities_TrainerHouse_GrandPrizeAwarded MSG_NORMAL
    fanfare 0x13E
    waitfanfare
    obtainitem ITEM_MACH_BIKE 0x1
    setflag 0x24F @ Got the bike
    return 

TrainerHouseDidNotBeatAnyTrainers:
    msgbox gText_HeleoCityFacilities_TrainerHouse_AnalysisBeatNoTrainers MSG_NORMAL
    goto Trainerhouse_end

TrainerHouseAlreadyBattledToday:
    msgbox gText_HeleoCityFacilities_TrainerHouse_AlreadyChallengedToday MSG_NORMAL
    goto End

Trainerhouse_trainerhouserules:
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseTrainerHouseRules MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_ruleset:
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseRuleset MSG_NORMAL
    goto TrainerHouse_Menu

MoveToBattlePosition:
    getplayerpos 0x4000 0x4001 @ Get player x y into variables
    compare 0x4000 0xA
    if equal _call MovePlayerFromRight
    compare 0x4000 0x9
    if equal _call MovePlayerFromBelow
    applymovement PLAYER m_WalkToBattlefield
    waitmovement ALLEVENTS
    return

MovePlayerFromRight:
    getplayerpos 0x4000 0x4001 @ Get player's new x y into variables
    applymovement PLAYER m_WalkFromRight
    waitmovement ALLEVENTS
    return

MovePlayerFromBelow:
    applymovement PLAYER m_WalkFromBelow
    waitmovement ALLEVENTS
    return

OpponentArrives:
    movesprite 0x1 0x8 0xC @ Center of the room
    clearflag 0x37 @ Show opponent
    showsprite 0x2
    applymovement 0x2 m_OpponentWalkToBattlefield
    waitmovement ALLEVENTS
    return

OpponentLeaves:
    applymovement 0x2 m_OpponentWalkAway
    waitmovement ALLEVENTS
    hidesprite 0x2
    setflag 0x37 @ Hide opponent
    return

Trainerhouse_end:
    special 0x28 @ Restore the player's party
    setvar 0x4090 0x0 @ Reset win streak
    setvar 0x8000 0x0 @ Turn off continuing after losing
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call DisableScalingFlag
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseEnd MSG_NORMAL
    goto End

DisableScalingFlag:
    clearflag 0x90E @ Disable trainer level scaling
    return

.global EventScript_HeleoFacilities_TrainerHouse_Boy
EventScript_HeleoFacilities_TrainerHouse_Boy:
    npcchat gText_HeleoCityFacilities_TrainerHouse_Boy
    end

.global EventScript_HeleoFacilities_TrainerHouse_Girl
EventScript_HeleoFacilities_TrainerHouse_Girl:
    npcchat gText_HeleoCityFacilities_TrainerHouse_Girl
    end

m_WalkFromRight: .byte walk_down, walk_left, end_m
m_WalkFromBelow: .byte walk_left, walk_up, end_m
m_WalkToBattlefield: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, look_right, end_m
m_OpponentWalkToBattlefield: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, look_left, end_m
m_OpponentWalkAway: .byte walk_down, walk_down, walk_left, walk_left, walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, end_m
m_ReturnToHost: .byte walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, look_right, end_m
