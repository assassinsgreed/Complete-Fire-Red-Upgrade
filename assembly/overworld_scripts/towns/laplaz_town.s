.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_LaplazTown
MapScript_LaplazTown:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LaplazTown_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_LaplazTown_FlightSpot:
    setworldmapflag 0x896 @ Visited Laplaz Town
    setvar 0x500B 0x0 @ Use walking script 0, i.e. None, for when the player leaves the gym
    end

.global EventScript_LaplazTown_Girl
EventScript_LaplazTown_Girl:
    npcchat gText_LaplazTown_Overworld_Girl
    end

.global EventScript_LaplazTown_OldMan
EventScript_LaplazTown_OldMan:
    faceplayer
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto OldManNoGymLeader
    msgbox gText_LaplazTown_Overworld_OldMan_MetCaseyInGym MSG_NORMAL
    end

OldManNoGymLeader:
    msgbox gText_LaplazTown_Overworld_OldMan_NotMetCaseyInGym MSG_NORMAL
    end

.global EventScript_LaplazTown_FatMan
EventScript_LaplazTown_FatMan:
    npcchat gText_LaplazTown_Overworld_FatMan
    end

.global EventScript_LaplazTown_YoungBoy
EventScript_LaplazTown_YoungBoy:
    npcchat gText_LaplazTown_Overworld_YoungBoy
    end

.global SignScript_LaplazTown_TrainerHouse
SignScript_LaplazTown_TrainerHouse:
    msgbox gText_LaplazTown_Overworld_TrainerHouseSign MSG_SIGN
    end

.global SignScript_LaplazTown_PeradonForest
SignScript_LaplazTown_PeradonForest:
    msgbox gText_LaplazTown_Overworld_PeradonForestSign MSG_SIGN
    end

.global SignScript_LaplazTown_ApricornBallShop
SignScript_LaplazTown_ApricornBallShop:
    msgbox gText_LaplazTown_Overworld_ApricornBallShopSign MSG_SIGN
    end

.global SignScript_LaplazTown_PsychicsHouse
SignScript_LaplazTown_PsychicsHouse:
    msgbox gText_LaplazTown_Overworld_PsychicsHouseSign MSG_SIGN
    end

.global SignScript_LaplazTown_GymSign
SignScript_LaplazTown_GymSign:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto GymSignNotMetCasey
    msgbox gText_LaplazTown_Overworld_GymSign_MetCaseyInGym MSG_NORMAL
    end

GymSignNotMetCasey:
    msgbox gText_LaplazTown_Overworld_GymSign_NotMetCaseyInGym MSG_SIGN
    end

.global SignScript_LaplazTown_LaplazTownSign
SignScript_LaplazTown_LaplazTownSign:
    msgbox gText_LaplazTown_Overworld_TownSign MSG_SIGN
    end

@ Facilities
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
    incrementgamestat 25
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

@ NPC Houses
.global EventScript_LaplazNPCHouses_Monty
EventScript_LaplazNPCHouses_Monty:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto MontyCaseyNotMet
    msgbox gText_LaplazTownNPCHouses_MontyMetWithCasey MSG_NORMAL
    end

MontyCaseyNotMet:
    msgbox gText_LaplazTownNPCHouses_MontyHaventMetWithCasey MSG_NORMAL
    end

.global EventScript_LaplazNPCHouses_CaseysMom
EventScript_LaplazNPCHouses_CaseysMom:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto CaseysMomCaseyNotMet
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _goto FemaleCaseyWillLeadGym
    if notequal _goto MaleCaseyWillLeadGym

CaseysMomCaseyNotMet:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomHaventMetWithCasey m_LookRight
    end

FemaleCaseyWillLeadGym:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomMetWithCasey_Female m_LookRight
    end

MaleCaseyWillLeadGym:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomMetWithCasey_Male m_LookRight
    end

.global EventScript_LaplazNPCHouses_CaseysGrandmother
EventScript_LaplazNPCHouses_CaseysGrandmother:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysGrandmother m_LookRight
    end

.global EventScript_LaplazNPCHouses_HeracrossKid
EventScript_LaplazNPCHouses_HeracrossKid:
    lock
    faceplayer
    msgbox gText_LaplazTownNPCHouses_HeracrossKid MSG_NORMAL
    showpokepic SPECIES_HERACROSS
    msgbox gText_LaplazTownNPCHouses_HeracrossKidDuringPic MSG_NORMAL
    hidepokepic
    msgbox gText_LaplazTownNPCHouses_HeracrossKidAfterPic MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    end

.global EventScript_LaplazNPCHouses_HeracrossKidsSister
EventScript_LaplazNPCHouses_HeracrossKidsSister:
    npcchatwithmovement gText_LaplazTownNPCHouses_HeracrossKidsSister m_LookLeft
    end

.global EventScript_LaplazNPCHouses_ApricornGrandma
EventScript_LaplazNPCHouses_ApricornGrandma:
    npcchatwithmovement gText_LaplazTownNPCHouses_ApricornGrandma m_LookRight
    end

.global EventScript_LaplazNPCHouses_ApricornGrandpa
EventScript_LaplazNPCHouses_ApricornGrandpa:
    npcchatwithmovement gText_LaplazTownNPCHouses_ApricornGrandpa m_LookLeft
    end

.global EventScript_LaplazNPCHouses_PsychicBrother
EventScript_LaplazNPCHouses_PsychicBrother:
    faceplayer
    checkflag 0x257 @ Got Hidden Power gift
    if SET _goto ExplainHiddenPower
    msgbox gText_LaplazTownNPCHouses_PsychicBrotherIntro MSG_NORMAL
    sound 0x15 @ Exclaim
	applymovement LASTTALKED m_Surprise
    msgbox gText_LaplazTownNPCHouses_PsychicBrotherRecognizesPotential MSG_NORMAL
    obtainitem ITEM_TM10 0x1 @ Hidden Power
    setflag 0x257 @ Got hidden power gift
    goto ExplainHiddenPower

ExplainHiddenPower:
    msgbox gText_LaplazTownNPCHouses_PsychicBrotherExplainsHiddenPower MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    end

.global EventScript_LaplazNPCHouses_PsychicSister
EventScript_LaplazNPCHouses_PsychicSister:
    faceplayer
    checkflag 0x257 @ Got Hidden Power gift
    if NOT_SET _goto PlayerHasNotReceivedHiddenPower
    msgbox gText_LaplazTownNPCHouses_PsychicSisterOffersHelp MSG_NORMAL
    checkflag 0x92B @ IV Ratings shown in summary
    if SET _goto AskToTurnOffRatings
    msgbox gText_LaplazTownNPCHouses_PsychicSisterOffersStatisticsOn MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToToggleStatistics
    call StatisticsAnimaton
    msgbox gText_LaplazTownNPCHouses_PsychicSisterStatisticsNowOn MSG_NORMAL
    setflag 0x92B @ IV Ratings shown in summary
    goto ResetPsychicSister

AskToTurnOffRatings:
    msgbox gText_LaplazTownNPCHouses_PsychicSisterOffersStatisticsOff MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToToggleStatistics
    call StatisticsAnimaton
    msgbox gText_LaplazTownNPCHouses_PsychicSisterStatisticsNowOff MSG_NORMAL
    clearflag 0x92B @ IV Ratings no longer shown in summary
    goto ResetPsychicSister

StatisticsAnimaton:
    playse 0x5F @ Shiny
	dofieldeffect 69 @ Screen flash
    waitfieldeffect 69
    waitse
    return

PlayerHasNotReceivedHiddenPower:
    msgbox gText_LaplazTownNPCHouses_PsychicSisterUnsureOfPlayer MSG_NORMAL
    goto ResetPsychicSister

ChoseNotToToggleStatistics:
    msgbox gText_LaplazTownNPCHouses_PsychicSisterSaidNo MSG_NORMAL
    goto ResetPsychicSister

ResetPsychicSister:
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_LaplazNPCHouses_ApricornSeller
EventScript_LaplazNPCHouses_ApricornSeller:
    faceplayer
    checkflag 0xE11 @ Apricorn ball bought today
    if SET _goto ApricornBallAlreadyBoughtToday
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_LaplazTownNPCHouses_ApricornSellerIntro MSG_NORMAL
    compare 0x8005 0x2
    if lessthan _goto NotEnoughPokeChipsForApricornBall
    msgbox gText_LaplazTownNPCHouses_ApricornSellerCost MSG_KEEPOPEN
    setvar 0x8000 0x9
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, fastball
	case 1, levelball
	case 2, lureball
	case 3, heavyball
    case 4, loveball
    case 5, friendball
    case 6, moonball
    case 7, cancelled
    case 0x7F, cancelled @ When player hit B to close
    end

PurchaseConfirmation:
    msgbox gText_LaplazTownNPCHouses_ApricornSellerConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto cancelled
    msgbox gText_LaplazTownNPCHouses_ApricornSellerPlayerConfirmed MSG_NORMAL
    fadescreen FADEOUT_BLACK
    playse 0x85 @ Recover
    waitse
    pause DELAY_HALFSECOND
    fadescreen FADEIN_BLACK
    msgbox gText_LaplazTownNPCHouses_ApricornSellerBallMade MSG_NORMAL
    obtainitem 0x4001 0x1
    removeitem ITEM_POKE_CHIP 0x2
    setflag 0xE11 @ Apricorn ball bought today
    goto ApricornBallAlreadyBoughtToday

NotEnoughPokeChipsForApricornBall:
    msgbox gText_LaplazTownNPCHouses_ApricornSellerNotEnoughChips MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

fastball:
    setvar 0x4001 ITEM_FAST_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerFastBallInfo MSG_NORMAL
    goto PurchaseConfirmation

levelball:
    setvar 0x4001 ITEM_LEVEL_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerLevelBallInfo MSG_NORMAL
    goto PurchaseConfirmation

lureball:
    setvar 0x4001 ITEM_LURE_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerLureBallInfo MSG_NORMAL
    goto PurchaseConfirmation

heavyball:
    setvar 0x4001 ITEM_HEAVY_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerHeavyBallInfo MSG_NORMAL
    goto PurchaseConfirmation

loveball:
    setvar 0x4001 ITEM_LOVE_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerLoveBallInfo MSG_NORMAL
    goto PurchaseConfirmation

friendball:
    setvar 0x4001 ITEM_FRIEND_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerFriendBallInfo MSG_NORMAL
    goto PurchaseConfirmation

moonball:
    setvar 0x4001 ITEM_MOON_BALL
    bufferitem 0x0 0x4001
    msgbox gText_LaplazTownNPCHouses_ApricornSellerMoonBallInfo MSG_NORMAL
    goto PurchaseConfirmation

cancelled:
    msgbox gText_LaplazTownNPCHouses_ApricornSellerCancelled MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

ApricornBallAlreadyBoughtToday:
    msgbox gText_LaplazTownNPCHouses_ApricornSellerAlreadyBought MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_LaplazNPCHouses_ApricornDescriber
EventScript_LaplazNPCHouses_ApricornDescriber:
    npcchatwithmovement gText_LaplazTownNPCHouses_ApricornDescriber m_LookRight
    end

.global EventScript_LaplazNPCHouses_Tutor
EventScript_LaplazNPCHouses_Tutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_LaplazTownNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_LaplazTownNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Laplaz
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_LaplazTownNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_LaplazTownNPCHouses_TutoringRejected m_LookRight
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_LaplazTownNPCHouses_NotEnoughPokeChips m_LookRight
    goto End

@ Gym
.equ TileSpriteLeft, 0x2C1
.equ TileSpriteRight, 0x2C2
.equ TileSpriteDown, 0x2C3
.equ TileSpriteUp, 0x2C4
.equ Casey, 0x1

.global MapScript_LaplazGym_RotatingFloorTiles
MapScript_LaplazGym_RotatingFloorTiles:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LaplazGym_SetWalkingScript
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_LaplazGym
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_LaplazGym_SetWalkingScript:
    setvar 0x500B 0x1 @ Use walking script 1, which is defined below
    call SetCaseyGender
    checkflag 0x3F @ Casey is not revealed as leader
    if SET _goto End
    movesprite2 Casey 0x8 0x2 @ Update position of Casey permanently
    end

LevelScripts_LaplazGym:
    levelscript 0x405A 0x1 LevelScripts_LaplazGym_SetPlayerFacing
    .hword LEVEL_SCRIPT_TERMIN

LevelScripts_LaplazGym_SetPlayerFacing:
    @ Player may warp here after tile event, due to engine limitations. Set their facing to up
    spriteface PLAYER UP
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


.global EventScript_LaplazGym_LeaderCasey
EventScript_LaplazGym_LeaderCasey:
    faceplayer
    call SetCaseyGender
    checkflag 0x824 @ Laplaz gym badge
    if SET _goto EventScript_LaplazTownGym_LeaderCasey_Chat
    msgbox gText_LaplazGym_LeaderCasey_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _goto FemaleCaseyBattle
    trainerbattle1 0x1 0xEA 0x100 gText_LaplazGym_LeaderCaseyM_Intro gText_LaplazGym_LeaderCaseyM_Defeat EventScript_LaplazGym_LeaderCasey_Defeated
    end

FemaleCaseyBattle:
    trainerbattle1 0x1 0xE9 0x100 gText_LaplazGym_LeaderCaseyF_Intro gText_LaplazGym_LeaderCaseyF_Defeat EventScript_LaplazGym_LeaderCasey_Defeated

EventScript_LaplazGym_LeaderCasey_Defeated:
    msgbox gText_LaplazGym_LeaderCasey_BadgeAwarded MSG_NORMAL
    setflag 0x824 @ Laplaz gym badge
    fanfare 0x13D @ Gym victory
    textcolor BLACK
    msgbox gText_LaplazGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    settrainerflag 0xE3 @ Jeremiah cannot be battled now
    settrainerflag 0xE4 @ Exie cannot be battled now
    settrainerflag 0xE5 @ Virginia cannot be battled now
    settrainerflag 0xE6 @ Nisha cannot be battled now
    settrainerflag 0xE7 @ Kent cannot be battled now
    settrainerflag 0xE8 @ Tomas cannot be battled now
    call SetCaseyGender @ Reset text color
    msgbox gText_LaplazGym_LeaderCasey_BadgeDescription MSG_NORMAL
    msgbox gText_LaplazGym_LeaderCasey_TMReceived MSG_NORMAL
    fanfare 0x101
    additem ITEM_TM75 0x1 @ Swords Dance
    textcolor BLACK
    msgbox gText_LaplazGym_TMReceived MSG_KEEPOPEN
    setflag 0x4B4 @ Defeated Casey
    setflag 0x25C @ New Pokemart Stock
    call SetCaseyGender @ Reset text color
    msgbox gText_LaplazGym_LeaderCasey_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_LaplazTownGym_LeaderCasey_Chat:
    npcchat gText_LaplazGym_LeaderCasey_Chat
    end

.global EventScript_LaplazGym_GymExpert
EventScript_LaplazGym_GymExpert:
    npcchat gText_LaplazGym_GymExpertCommonIntro
    checkflag 0x3F @ Casey is not revealed as leader yet
    if SET _goto GymExpert_MontyDescription
    msgbox gText_LaplazGym_GymExpertCaseyIntro MSG_NORMAL
    end

GymExpert_MontyDescription:
    msgbox gText_LaplazGym_GymExpertMontyIntro MSG_NORMAL
    end

.global EventScript_LaplazGym_Jeremiah
EventScript_LaplazGym_Jeremiah:
    trainerbattle0 0x0 0xE3 0x0 gText_LaplazGym_Jeremiah_Intro gText_LaplazGym_Jeremiah_Defeat
    msgbox gText_LaplazGym_Jeremiah_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Exie
EventScript_LaplazGym_Exie:
    trainerbattle0 0x0 0xE4 0x0 gText_LaplazGym_Exie_Intro gText_LaplazGym_Exie_Defeat
    msgbox gText_LaplazGym_Exie_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Virginia
EventScript_LaplazGym_Virginia:
    trainerbattle0 0x0 0xE5 0x0 gText_LaplazGym_Virginia_Intro gText_LaplazGym_Virginia_Defeat
    msgbox gText_LaplazGym_Virginia_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Nisha
EventScript_LaplazGym_Nisha:
    trainerbattle0 0x0 0xE6 0x0 gText_LaplazGym_Nisha_Intro gText_LaplazGym_Nisha_Defeat
    msgbox gText_LaplazGym_Nisha_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Kent
EventScript_LaplazGym_Kent:
    trainerbattle0 0x0 0xE7 0x0 gText_LaplazGym_Kent_Intro gText_LaplazGym_Kent_Defeat
    msgbox gText_LaplazGym_Kent_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Tomas
EventScript_LaplazGym_Tomas:
    trainerbattle0 0x0 0xE8 0x0 gText_LaplazGym_Tomas_Intro gText_LaplazGym_Tomas_Defeat
    msgbox gText_LaplazGym_Tomas_Chat MSG_NORMAL
    end

.global SignScript_LaplazGym_GymPlacard
SignScript_LaplazGym_GymPlacard:
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto GymPlacard_WithRival
    checkflag 0x824 @ Laplaz gym badge
    if SET _goto GymPlacard_JustPlayer
    msgbox gText_LaplazGym_Placard_NoBadge MSG_SIGN
    end

GymPlacard_WithRival:
    msgbox gText_LaplazGym_Placard_BadgeWithRival MSG_SIGN
    end

GymPlacard_JustPlayer:
    msgbox gText_LaplazGym_Placard_Badge MSG_SIGN
    end

.global TileScript_LaplazGym_IntroduceCasey
TileScript_LaplazGym_IntroduceCasey:
    lock
    checkflag 0x3F @ Casey is revealed as leader
    if NOT_SET _goto End @ Event already played
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    call SetCaseyGender
    playbgm 0x169 @ Alder encounter
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_LaplazGym_CaseyAsksForTilesToBeTurnedOff MSG_NORMAL
    clearflag 0x3F @ Casey is now revealed as leader
    showsprite Casey
    applymovement PLAYER m_LookDown
    applymovement Casey m_CaseyWalksToPlayer
    waitmovement Casey
    checkgender
    compare LASTRESULT 0x0
    if equal _call FemaleCaseyBackstory
    if notequal _call MaleCaseyBackstory
    fadedefaultbgm
    applymovement Casey m_CaseyWalksToPodium
    pause DELAY_1SECOND
    applymovement PLAYER m_LookUp
    waitmovement Casey
    setvar 0x405A 0x1
    getplayerpos 0x4000 0x4001 @ HACK: Move the player to the same map to force the tile script to release the player
    warpmuted 10 8 0xFF 0x4000 0x4001 @ Warp to same spot in the gym
    release
    end

FemaleCaseyBackstory:
    msgbox gText_LaplazGym_FemaleCaseyAddressesPlayer MSG_NORMAL
    playbgm 0x159 @ N's Farewell
    applymovement Casey m_LookDown
    msgbox gText_LaplazGym_FemaleCaseyBackstory MSG_NORMAL
    applymovement Casey m_LookUp
    msgbox gText_LaplazGym_FemaleCaseyCommitment MSG_NORMAL
    return

MaleCaseyBackstory:
    msgbox gText_LaplazGym_MaleCaseyAddressesPlayer MSG_NORMAL
    playbgm 0x159 @ N's Farewell
    applymovement Casey m_LookDown
    msgbox gText_LaplazGym_MaleCaseyBackstory MSG_NORMAL
    applymovement Casey m_LookUp
    msgbox gText_LaplazGym_MaleCaseyCommitment MSG_NORMAL
    return

m_CaseyWalksToPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_CaseyWalksToPodium: .byte walk_right, walk_up, walk_up, walk_left, walk_up, walk_up, walk_up, walk_up, look_down, end_m
