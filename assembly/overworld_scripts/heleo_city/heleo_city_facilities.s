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
    call ResetRoute11PlutoEventOnWhiteout
    end

.global EventScript_HeleoFacilities_PokemonCenter_BoredKid
EventScript_HeleoFacilities_PokemonCenter_BoredKid:
    msgbox gText_HeleoCityFacilities_BoredKid MSG_NORMAL
    end

.global EventScript_HeleoFacilities_PokemonCenter_KidsMom
EventScript_HeleoFacilities_PokemonCenter_KidsMom:
    npcchat gText_HeleoCityFacilities_KidsMom
    end

.global EventScript_HeleoFacilities_PokemonCenter_CriticalCapture
EventScript_HeleoFacilities_PokemonCenter_CriticalCapture:
    npcchat gText_HeleoCityFacilities_CriticalCapture
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

.align 1
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
    checkflag 0xE0B @ Already battled today
    if SET _goto TrainerHouse_Common_AlreadyBattledToday
    call TrainerHousePreBattleSetup
    call TrainerHouse_Common_MoveToBattlePosition
    setflag 0x900 @ Turn on inverse battles
    setflag 0x90E @ Scale trainer levels
    applymovement 0x1 m_LookUp
    @ First Opponent
    msgbox gText_HeleoCityFacilities_TrainerHouse_FirstOpponentArriving MSG_NORMAL
    setvar 0x8001 0x2
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaIntro MSG_NORMAL
    trainerbattle9 0x0 0x62 0x0 gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaWin gText_HeleoCityFacilities_TrainerHouse_B1PsychicBiancaLose
    call HandleBattleEnded
    @ Second Opponent
    msgbox gText_HeleoCityFacilities_TrainerHouse_SecondOpponentArriving MSG_NORMAL
    setvar 0x8001 0x5
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenIntro MSG_NORMAL
    trainerbattle9 0x0 0x63 0x0 gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenWin gText_HeleoCityFacilities_TrainerHouse_B2SupernerdGalenLose
    call HandleBattleEnded
    @ Third Opponent
    msgbox gText_HeleoCityFacilities_TrainerHouse_ThirdOpponentArriving MSG_NORMAL
    setvar 0x8001 0x6
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetIntro MSG_NORMAL
    trainerbattle9 0x0 0x64 0x0 gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetWin gText_HeleoCityFacilities_TrainerHouse_CooltrainerJetLose
    call HandleBattleEnded
    msgbox gText_HeleoCityFacilities_TrainerHouse_AllOpponentsDefeated MSG_NORMAL
    call TrainerHouse_Common_ReturnToHost
    goto TrainerHouseGivePrizes

TrainerHousePreBattleSetup:
    msgbox gText_HeleoCityFacilities_TrainerHouse_BattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto TrainerHouse_Common_End
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseBattle MSG_NORMAL
    setflag 0xE0B @ Already battled today
    setvar 0x8000 0xFEFE @ Continue lost battles
    msgbox gText_HeleoCityFacilities_TrainerHouse_HealingPokemon MSG_NORMAL
    call PlayerHeal
    msgbox gText_HeleoCityFacilities_TrainerHouse_PokemonSelectionFinalized MSG_NORMAL
    setvar 0x4090 0x0 @ 0 win streak
    return

TrainerHouseStreakLost:
    fanfare 0x10F @ Failure
    msgbox gText_HeleoCityFacilities_TrainerHouse_StreakLost MSG_KEEPOPEN
    waitfanfare
    fadescreen FADEOUT_BLACK
    hidesprite 0x2
    hidesprite 0x5
    hidesprite 0x6
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
    if equal _call TrainerHouse_Common_GivePokeball
    compare 0x8002 0x1
    if equal _call TrainerHouse_Common_GivePotion
    return

TrainerHouseTier2Prizes:
    random 0x3
    copyvar 0x8003 LASTRESULT
    compare 0x8003 0x0
    if equal _call TrainerHouse_Common_GiveGreatBall
    compare 0x8003 0x1
    if equal _call TrainerHouse_Common_GiveSuperPotion
    compare 0x8003 0x2
    if equal _call TrainerHouse_Common_GiveRepel
    pause DELAY_HALFSECOND
    call TrainerHouseTier1Prizes
    return

TrainerHouseTier3Prizes:
    random 0x3
    copyvar 0x8004 LASTRESULT
    compare 0x8004 0x0
    if equal _call TrainerHouse_Common_GiveUltraBall
    compare 0x8004 0x1
    if equal _call TrainerHouse_Common_GiveMoomooMilk
    compare 0x8004 0x2
    if equal _call TrainerHouse_Common_GiveFullHeal
    pause DELAY_HALFSECOND
    call TrainerHouseTier2Prizes
    call TrainerHouseCheckForGrandPrize
    return

TrainerHouseCheckForGrandPrize:
    checkflag 0x24F @ Got the bike
    if NOT_SET _call TrainerHouseGiveGrandPrize
    return

TrainerHouseGiveGrandPrize:
    msgbox gText_HeleoCityFacilities_TrainerHouse_GrandPrizeAwarded MSG_NORMAL
    fanfare 0x10C @ Big Celebration
    obtainitem ITEM_MACH_BIKE 0x1
    waitfanfare
    setflag 0x24F @ Got the bike
    return 

TrainerHouseDidNotBeatAnyTrainers:
    msgbox gText_TrainerHouse_AnalysisBeatNoTrainers MSG_NORMAL
    goto Trainerhouse_ResetStateAtEnd

Trainerhouse_trainerhouserules:
    msgbox gText_TrainerHouse_ChoseTrainerHouseRules MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_ruleset:
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseRuleset MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_grandprize:
    msgbox gText_HeleoCityFacilities_TrainerHouse_ChoseGrandPrize MSG_NORMAL
    goto TrainerHouse_Menu

HandleBattleEnded:
    compare LASTRESULT TRUE
    if equal _goto TrainerHouseStreakLost
    fanfare 0x10D @ Victory
    msgbox gText_TrainerHouse_StreakContinues MSG_KEEPOPEN
    waitfanfare
    call TrainerHouse_Common_OpponentLeaves
    addvar 0x4090 0x1
    return

Trainerhouse_ResetStateAtEnd:
    setvar 0x4090 0x0 @ Reset win streak
    setvar 0x8000 0x0 @ Turn off continuing after losing
    setvar 0x8001 0x0 @ Reset temp trainer var
    setvar 0x8002 0x0 @ Reset prize 1 pool var
    setvar 0x8003 0x0 @ Reset prize 2 pool var
    setvar 0x8004 0x0 @ Reset prize 3 pool var
    checkflag 0x4FE @ Inverse battles modifier
    if NOT_SET _call DisableInverseFlag
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call TrainerHouse_Common_DisableScalingFlag
    msgbox gText_TrainerHouse_HealingPokemonAtEnd MSG_NORMAL
    call PlayerHeal
    goto TrainerHouse_Common_End

DisableInverseFlag:
    clearflag 0x900 @ Disable inverse battles
    return

.global EventScript_HeleoFacilities_TrainerHouse_Boy
EventScript_HeleoFacilities_TrainerHouse_Boy:
    npcchat gText_HeleoCityFacilities_TrainerHouse_Boy
    end

.global EventScript_HeleoFacilities_TrainerHouse_Girl
EventScript_HeleoFacilities_TrainerHouse_Girl:
    npcchat gText_HeleoCityFacilities_TrainerHouse_Girl
    end

.global EventScript_HeleoGuardHouse_Guard
EventScript_HeleoGuardHouse_Guard:
    npcchat gText_HeleoCityFacilities_GuardHouse_Guard
    end

.global EventScript_HeleoGuardHouse_DateBoy
EventScript_HeleoGuardHouse_DateBoy:
    npcchat gText_HeleoCityFacilities_GuardHouse_DateBoy
    end

.global EventScript_HeleoGuardHouse_DateGirl
EventScript_HeleoGuardHouse_DateGirl:
    npcchat gText_HeleoCityFacilities_GuardHouse_DateGirl
    end

.global EventScript_HeleoGuardHouse_Camper
EventScript_HeleoGuardHouse_Camper:
    npcchat gText_HeleoCityFacilities_GuardHouse_Camper
    end

.global SignScript_HeleoGuardHouse_ForgottenManseBinoculars
SignScript_HeleoGuardHouse_ForgottenManseBinoculars:
    msgbox gText_GuardHouseBinoculars MSG_NORMAL
    msgbox gText_HeleoCityFacilities_GuardHouse_ForgottenManseBinoculars MSG_NORMAL
    end

.global SignScript_HeleoGuardHouse_DaimynCityBinoculars
SignScript_HeleoGuardHouse_DaimynCityBinoculars:
    msgbox gText_GuardHouseBinoculars MSG_NORMAL
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto BinocularsDay
    goto BinocularsNight

BinocularsDay:
    msgbox gText_HeleoCityFacilities_GuardHouse_DaimynCityBinocularsDay MSG_NORMAL
    end

BinocularsNight:
    msgbox gText_HeleoCityFacilities_GuardHouse_DaimynCityBinocularsNight MSG_NORMAL
    end
