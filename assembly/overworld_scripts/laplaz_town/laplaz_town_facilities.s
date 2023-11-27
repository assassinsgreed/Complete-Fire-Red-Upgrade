.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_LaplazFacilities_PokemonCenter
MapScript_LaplazFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_LaplazFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_LaplazFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x07 @ Originally Fucshia City
    end

.global EventScript_LaplazFacilities_GalarBirdsGirl
EventScript_LaplazFacilities_GalarBirdsGirl:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGirl m_LookDown
    end

.global EventScript_LaplazFacilities_GalarBirdsGirlsSister
EventScript_LaplazFacilities_GalarBirdsGirlsSister:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGirlsSister m_LookLeft
    end

.global EventScript_LaplazFacilities_Gentleman
EventScript_LaplazFacilities_Gentleman:
    npcchatwithmovement gText_LaplazTownFacilities_GalarBirdsGentleman m_LookDown
    end

.global EventScript_LaplazFacilities_XItemsShop
EventScript_LaplazFacilities_XItemsShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart LaplazPokemart_XItemStock
    goto EventScript_EndMart

.align 1
LaplazPokemart_XItemStock:
    .hword ITEM_X_ATTACK
    .hword ITEM_X_DEFEND
    .hword ITEM_X_SP_ATK
    .hword ITEM_X_SP_DEF
    .hword ITEM_X_SPEED
    .hword ITEM_X_ACCURACY
    .hword ITEM_DIRE_HIT
    .hword ITEM_GUARD_SPEC
    .hword ITEM_NONE

.global EventScript_LaplazFacilities_XItemsTip
EventScript_LaplazFacilities_XItemsTip:
    npcchatwithmovement gText_LaplazFacilities_XItemsTip m_LookUp
    end

.global EventScript_LaplazFacilities_TrainerHouse_Host
EventScript_LaplazFacilities_TrainerHouse_Host:
    faceplayer
    msgbox gText_LaplazFacilities_TrainerHouse_HostIntro MSG_NORMAL
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
    checkflag 0xE12 @ Already battled today
    if SET _goto TrainerHouse_Common_AlreadyBattledToday
    call TrainerHousePreBattleSetup
    call TrainerHouse_Common_MoveToBattlePosition
    setflag 0x90E @ Scale trainer levels
    applymovement 0x1 m_LookUp
    @ First Opponent
    msgbox gText_LaplazFacilities_TrainerHouse_FirstOpponentArriving MSG_NORMAL
    setflag 0x901 @ Turn on sky battles, cleared after battle
    setvar 0x8001 0x5
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_LaplazFacilities_TrainerHouse_B1BirdKeeperTobyIntro MSG_NORMAL
    trainerbattle9 0x0 0xE0 0x0 gText_LaplazFacilities_TrainerHouse_B1BirdKeeperTobyWin gText_LaplazFacilities_TrainerHouse_B1BirdKeeperTobyLose
    call HandleBattleEnded
    @ Second Opponent
    msgbox gText_LaplazFacilities_TrainerHouse_SecondOpponentArriving MSG_NORMAL
    setflag 0x901 @ Turn on sky battles, cleared after battle
    setvar 0x8001 0x6
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_LaplazFacilities_TrainerHouse_B2CollectorDirkIntro MSG_NORMAL
    trainerbattle9 0x0 0xE1 0x0 gText_LaplazFacilities_TrainerHouse_B2CollectorDirkWin gText_LaplazFacilities_TrainerHouse_B2CollectorDirkLose
    call HandleBattleEnded
    @ Third Opponent
    msgbox gText_LaplazFacilities_TrainerHouse_ThirdOpponentArriving MSG_NORMAL
    setflag 0x901 @ Turn on sky battles, cleared after battle
    setvar 0x8001 0x7
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_LaplazFacilities_TrainerHouse_CooltrainerVanessaIntro MSG_NORMAL
    trainerbattle9 0x0 0xE2 0x0 gText_LaplazFacilities_TrainerHouse_CooltrainerVanessaWin gText_LaplazFacilities_TrainerHouse_CooltrainerVanessaLose
    call HandleBattleEnded
    msgbox gText_LaplazFacilities_TrainerHouse_AllOpponentsDefeated MSG_NORMAL
    call TrainerHouse_Common_ReturnToHost
    goto TrainerHouseGivePrizes

TrainerHousePreBattleSetup:
    special2 LASTRESULT 0x51 @ Can sky battle
    compare LASTRESULT 0x0
    if equal _goto CannotParticipate
    msgbox gText_LaplazFacilities_TrainerHouse_BattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto TrainerHouse_Common_End
    msgbox gText_LaplazFacilities_TrainerHouse_ChoseBattle MSG_NORMAL
    setflag 0xE12 @ Already battled today
    setvar 0x8000 0xFEFE @ Continue lost battles
    msgbox gText_LaplazFacilities_TrainerHouse_HealingPokemon MSG_NORMAL
    call PlayerHeal
    msgbox gText_LaplazFacilities_TrainerHouse_PreChallengeComment MSG_NORMAL
    setvar 0x4090 0x0 @ 0 win streak
    return

CannotParticipate:
    msgbox gText_LaplazFacilities_TrainerHouse_CannotParticipate MSG_NORMAL
    end

TrainerHouseStreakLost:
    fanfare 0x10F @ Failure
    msgbox gText_LaplazFacilities_TrainerHouse_StreakLost MSG_KEEPOPEN
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
    if equal _call TrainerHouse_Common_GiveGreatBall
    compare 0x8002 0x1
    if equal _call TrainerHouse_Common_GiveSuperPotion
    return

TrainerHouseTier2Prizes:
    random 0x3
    copyvar 0x8003 LASTRESULT
    compare 0x8003 0x0
    if equal _call TrainerHouse_Common_GiveUltraBall
    compare 0x8003 0x1
    if equal _call TrainerHouse_Common_GiveMoomooMilk
    compare 0x8003 0x2
    if equal _call TrainerHouse_Common_GiveFullHeal
    pause DELAY_HALFSECOND
    call TrainerHouseTier1Prizes
    return

TrainerHouseTier3Prizes:
    random 0x3
    copyvar 0x8004 LASTRESULT
    compare 0x8004 0x0
    if equal _call TrainerHouse_Common_GiveHyperPotion
    compare 0x8004 0x1
    if equal _call TrainerHouse_Common_GiveRevive
    compare 0x8004 0x2
    if equal _call TrainerHouse_Common_GiveQuickBall
    pause DELAY_HALFSECOND
    call TrainerHouseTier2Prizes
    call TrainerHouseCheckForGrandPrize
    return

TrainerHouseCheckForGrandPrize:
    checkflag 0x26C @ Got the lucky egg
    if NOT_SET _call TrainerHouseGiveGrandPrize
    return

TrainerHouseGiveGrandPrize:
    msgbox gText_LaplazFacilities_TrainerHouse_GrandPrizeAwarded MSG_NORMAL
    fanfare 0x10C @ Big Celebration
    obtainitem ITEM_LUCKY_EGG 0x1
    waitfanfare
    setflag 0x26C @ Got the lucky egg
    return 

TrainerHouseDidNotBeatAnyTrainers:
    msgbox gText_TrainerHouse_AnalysisBeatNoTrainers MSG_NORMAL
    goto Trainerhouse_ResetStateAtEnd

Trainerhouse_trainerhouserules:
    msgbox gText_TrainerHouse_ChoseTrainerHouseRules MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_ruleset:
    msgbox gText_LaplazFacilities_TrainerHouse_ChoseRuleset MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_grandprize:
    msgbox gText_LaplazFacilities_TrainerHouse_ChoseGrandPrize MSG_NORMAL
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
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call TrainerHouse_Common_DisableScalingFlag
    msgbox gText_TrainerHouse_HealingPokemonAtEnd MSG_NORMAL
    call PlayerHeal
    goto TrainerHouse_Common_End

.global EventScript_LaplazFacilities_TrainerHouse_Blackbelt
EventScript_LaplazFacilities_TrainerHouse_Blackbelt:
    npcchatwithmovement gText_LaplazFacilities_TrainerHouse_Blackbelt m_LookRight
    end

.global EventScript_LaplazFacilities_TrainerHouse_Rocker
EventScript_LaplazFacilities_TrainerHouse_Rocker:
    npcchatwithmovement gText_LaplazFacilities_TrainerHouse_Rocker m_LookLeft
    end

.global EventScript_LaplazFacilities_TrainerHouse_Girl
EventScript_LaplazFacilities_TrainerHouse_Girl:
    npcchat gText_LaplazFacilities_TrainerHouse_Girl
    end
