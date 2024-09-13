.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_HeleoCity
MapScript_HeleoCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoCity_FlightSpot:
    setworldmapflag 0x894
    setvar PLAYERFACING 0x0 @ Reset facing from the gym
    end

.global EventScript_HeleoCity_JumpingKid
EventScript_HeleoCity_JumpingKid:
    lock
    faceplayer
    msgbox gText_HeleoCityOverworld_JumpingKidPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DoNotLikeJumping
    applymovement 0x1 m_Joy
    checkflag 0x249 @ Received Air Balloon
    if SET _goto JumpingKidDone
    msgbox gText_HeleoCityOverworld_JumpingKidLikeJumping MSG_NORMAL
    setvar 0x8004 0x2B @ Ledges jumped down
    callasm StoreGameStat
    buffernumber 0x0 LASTRESULT
    compare LASTRESULT 0x64 @ 100
    if lessthan _goto NotEnoughJumps
    faceplayer @ TODO: Needed?
    msgbox gText_HeleoCityOverworld_JumpingKidCountExceeded MSG_NORMAL
    fanfare 0x13E
    waitfanfare
    msgbox gText_HeleoCityOverworld_JumpingKidGift MSG_NORMAL
    obtainitem ITEM_AIR_BALLOON 0x1
    setflag 0x249 @ Got Air Balloon
    goto JumpingKidDone

DoNotLikeJumping:
    msgbox gText_HeleoCityOverworld_JumpingKidHateJumping MSG_NORMAL
    goto End

NotEnoughJumps:
    msgbox gText_HeleoCityOverworld_JumpingKidCount MSG_NORMAL
    goto End

JumpingKidDone:
    msgbox gText_HeleoCityOverworld_JumpingKidDone MSG_NORMAL
    goto End

.global EventScript_HeleoCity_ShadyDealer
EventScript_HeleoCity_ShadyDealer:
    lock
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_HeleoCityOverworld_ShadyDealerProposition MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ShadyDealerRejected
    checkitem ITEM_POKE_CHIP 0x1
    compare LASTRESULT TRUE
    if FALSE _goto ShadyDealerNotEnoughPokeChips
    removeitem ITEM_POKE_CHIP 0x1
    sound 0xF8 @ Money SE
    waitse
    random 0xE @ 15 items
    switch LASTRESULT
    case 0, ShadyDealerObtainPotion
    case 1, ShadyDealerObtainSuperPotion
    case 2, ShadyDealerObtainHyperPotion
    case 3, ShadyDealerObtainRevive
    case 4, ShadyDealerObtainRevive
    case 5, ShadyDealerObtainMaxRevive
    case 6, ShadyDealerObtainPPUp
    case 7, ShadyDealerObtainPokeball
    case 8, ShadyDealerObtainPokeball
    case 9, ShadyDealerObtainGreatBall
    case 10, ShadyDealerObtainUltraball
    case 11, ShadyDealerObtainNormalGem
    case 12, ShadyDealerObtainAmuletCoin
    case 13, ShadyDealerObtainStarPiece
    case 14, ShadyDealerObtainNugget
    goto End

ShadyDealerObtainPotion:
    obtainitem ITEM_POTION 0x3
    goto ShadyDealerTradeComplete

ShadyDealerObtainSuperPotion:
    obtainitem ITEM_SUPER_POTION 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainHyperPotion:
    obtainitem ITEM_HYPER_POTION 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainRevive:
    obtainitem ITEM_REVIVE 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainMaxRevive:
    obtainitem ITEM_MAX_REVIVE 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainPPUp:
    obtainitem ITEM_PP_UP 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainPokeball:
    obtainitem ITEM_POKE_BALL 0x3
    goto ShadyDealerTradeComplete

ShadyDealerObtainGreatBall:
    obtainitem ITEM_GREAT_BALL 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainUltraball:
    obtainitem ITEM_ULTRA_BALL 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainNormalGem:
    obtainitem ITEM_NORMAL_GEM 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainAmuletCoin:
    obtainitem ITEM_AMULET_COIN 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainStarPiece:
    obtainitem ITEM_STAR_PIECE 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainNugget:
    obtainitem ITEM_NUGGET 0x1
    goto ShadyDealerTradeComplete

ShadyDealerRejected:
    msgbox gText_HeleoCityOverworld_ShadyDealerDeclined MSG_NORMAL
    goto End

ShadyDealerNotEnoughPokeChips:
    msgbox gText_HeleoCityOverworld_ShadyDealerNotEnoughChips MSG_NORMAL
    goto End

ShadyDealerTradeComplete:
    msgbox gText_HeleoCityOverworld_ShadyDealerTradeComplete MSG_NORMAL
    fadescreen FADEOUT_BLACK
    setflag 0xE09 @ Hide shady dealer
    hidesprite LASTTALKED
    pause DELAY_1SECOND
    fadescreen FADEIN_BLACK
    goto End

.global EventScript_HeleoCity_Route8Girl
EventScript_HeleoCity_Route8Girl:
    npcchat gText_HeleoCityOverworld_Route8Girl
    end

.global EventScript_HeleoCity_FountainKid
EventScript_HeleoCity_FountainKid:
    npcchatwithmovement gText_HeleoCityOverworld_FountainKid m_LookUp
    end

.global EventScript_HeleoCity_BigGuy
EventScript_HeleoCity_BigGuy:
    npcchat gText_HeleoCityOverworld_BigGuy
    end

.global EventScript_HeleoCity_TrainerHouseGirl
EventScript_HeleoCity_TrainerHouseGirl:
    npcchat gText_HeleoCityOverworld_TrainerHouseGirl
    end

.global EventScript_HeleoCity_RaineFan
EventScript_HeleoCity_RaineFan:
    npcchat gText_HeleoCityOverworld_RaineFan
    end

.global EventScript_HeleoCity_BadgeBasedGyms
EventScript_HeleoCity_BadgeBasedGyms:
    npcchat gText_HeleoCityOverworld_BadgeBasedGyms
    end

.global SignScript_HeleoCity_CitySign
SignScript_HeleoCity_CitySign:
    msgbox gText_HeleoCityOverworld_HeleoCitySign MSG_SIGN
    end

.global SignScript_HeleoCity_GymSign
SignScript_HeleoCity_GymSign:
    msgbox gText_HeleoCityOverworld_GymSign MSG_SIGN
    end

.global SignScript_HeleoCity_TrainerHouseSign
SignScript_HeleoCity_TrainerHouseSign:
    msgbox gText_HeleoCityOverworld_TrainerHouseSign MSG_SIGN
    end

.global SignScript_HeleoCity_TrainerTips
SignScript_HeleoCity_TrainerTips:
    msgbox gText_HeleoCityOverworld_TrainerTips MSG_SIGN
    end

@ Facilities
.global MapScript_HeleoFacilities_PokemonCenter
MapScript_HeleoFacilities_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_HeleoFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x05 @ Originally Lavender Town
    call ResetRoute11PlutoEventOnWhiteout
    call ResetUteyaVillageGymFlagsOnWhiteout
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
    incrementgamestat 25
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
    if NOT_SET _call DisableTrainerScalingFlag
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

@ NPC Houses
.global EventScript_HeleoCity_Foreman
EventScript_HeleoCity_Foreman:
    lock
    faceplayer
    checkflag 0x235 @ Received rock smash
    if SET _goto ForemanGiftGiven
    msgbox gText_HeleoCity_ForemanHMGift MSG_NORMAL
    obtainitem ITEM_HM05 0x1
    setflag 0x235 @ Received rock smash
    goto ForemanGiftGiven
    end

ForemanGiftGiven:
    npcchatwithmovement gText_HeleoCity_ForemanBadgeComment m_LookRight 
    goto End

.global EventScript_HeleoCity_ForemanAssistant
EventScript_HeleoCity_ForemanAssistant:
    npcchat gText_HeleoCity_ForemanAssistant
    end

.global EventScript_HeleoCity_MoveTutor
EventScript_HeleoCity_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_HeleoNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_HeleoNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Heleo
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_HeleoNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_HeleoNPCHouses_TutoringRejected m_LookRight
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_HeleoNPCHouses_NotEnoughPokeChips m_LookRight
    goto End

.global EventScript_HeleoCity_MoveTutorSon
EventScript_HeleoCity_MoveTutorSon:
    npcchat gText_HeleoCity_MoveTutorSon
    end

.global EventScript_HeleoCity_SwarmSwami
EventScript_HeleoCity_SwarmSwami:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_SwarmSwamiIntro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto EventScript_HeleoCity_SwarmSwami_Rejected
    msgbox gText_HeleoNPCHouses_SwarmSwamiStarting MSG_NORMAL
    fadescreen FADEOUT_BLACK
    pause DELAY_1SECOND
    special 0x58 @ Buffer the location (buffer1) and pokemon (buffer2) swarming now
    pause DELAY_HALFSECOND
    fadescreen FADEIN_BLACK
    sound 0x15 @ Exclaim
    applymovement 0x1 m_Surprise
    msgbox gText_HeleoNPCHouses_SwarmSwamiComplete MSG_NORMAL
    goto End

EventScript_HeleoCity_SwarmSwami_Rejected:
    msgbox gText_HeleoNPCHouses_SwarmSwamiRejected MSG_NORMAL
    goto End

.global EventScript_HeleoCity_SwamiFan
EventScript_HeleoCity_SwamiFan:
    npcchat gText_HeleoNPCHouses_SwamiFan
    end

.global EventScript_HeleoCity_SwamiResearcher
EventScript_HeleoCity_SwamiResearcher:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_SwamiResearcher MSG_NORMAL
    compare 0x4053 0x11 @ 17 swarm pokemon
    if equal _goto End
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto SwamiResearcherRejected
    setvar 0x8003 0x0 @ From Party
    setvar 0x8004 0x0 @ First Slot
    special2 LASTRESULT 0x18 @ Check species
    switch LASTRESULT
    case SPECIES_RATTATA, ResearcherRattata
    case SPECIES_RATICATE, ResearcherRaticate
    case SPECIES_RAICHU_A, ResearcherRaichuA
    case SPECIES_GRIMER, ResearcherGrimer
    case SPECIES_MUK, ResearcherMuk
    case SPECIES_SLOWPOKE_G, ResearcherSlowpokeG
    case SPECIES_SLOWBRO_G, ResearcherSlowbroG
    case SPECIES_SLOWKING_G, ResearcherSlowkingG
    case SPECIES_FARFETCHD, ResearcherFarfetchd
    case SPECIES_KOFFING, ResearcherKoffing
    case SPECIES_WEEZING, ResearcherWeezing
    case SPECIES_MIME_JR, ResearcherMimeJr
    case SPECIES_MR_MIME, ResearcherMrMime
    case SPECIES_CORSOLA, ResearcherCorsola
    case SPECIES_DARUMAKA, ResearcherDarumaka
    case SPECIES_DARMANITAN, ResearcherDarmanitan
    case SPECIES_STUNFISK, ResearcherStunfisk
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestWrongPokemon MSG_NORMAL
    goto End

SwamiResearcherRejected:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestDenied MSG_NORMAL
    goto End

ResearcherRattata:
    checkflag 0x236 @ Shown Rattata
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x236 @ Shown Rattata
    goto End

ResearcherRaticate:
    checkflag 0x237 @ Shown Raticate
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x237 @ Shown Raticate
    goto End

ResearcherRaichuA:
    checkflag 0x238 @ Shown Alolan Raichu
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x238 @ Shown Alolan Raichu
    goto End

ResearcherGrimer:
    checkflag 0x239 @ Shown Grimer
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x239 @ Shown Grimer
    goto End

ResearcherMuk:
    checkflag 0x23A @ Shown Muk
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23A @ Shown Muk
    goto End

ResearcherSlowpokeG:
    checkflag 0x23B @ Shown Galarian Slowpoke
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23B @ Shown Galarian Slowpoke
    goto End

ResearcherSlowbroG:
    checkflag 0x23C @ Shown Galarian Slowbro
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23C @ Shown Galarian Slowbro
    goto End

ResearcherSlowkingG:
    checkflag 0x23D @ Shown Galarian Slowking
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23D @ Shown Galarian Slowking
    goto End

ResearcherFarfetchd:
    checkflag 0x23E @ Shown Farfetch'd
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23E @ Shown Farfetch'd
    goto End

ResearcherKoffing:
    checkflag 0x23F @ Shown Koffing
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23F @ Shown Koffing
    goto End

ResearcherWeezing:
    checkflag 0x240 @ Shown Weezing
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x240 @ Shown Weezing
    goto End

ResearcherMimeJr:
    checkflag 0x241 @ Shown Mime Jr
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x241 @ Shown Mime Jr
    goto End

ResearcherMrMime:
    checkflag 0x242 @ Shown Mr Mime
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x242 @ Shown Mr Mime
    goto End

ResearcherCorsola:
    checkflag 0x243 @ Shown Corsola
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x243 @ Shown Corsola
    goto End

ResearcherDarumaka:
    checkflag 0x244 @ Shown Darumaka
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x244 @ Shown Darumaka
    goto End

ResearcherDarmanitan:
    checkflag 0x245 @ Shown Darmanitan
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x245 @ Shown Darmanitan
    goto End

ResearcherStunfisk:
    checkflag 0x246 @ Shown Stunfisk
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x246 @ Shown Stunfisk
    goto End

GiveSwarmItem:
    bufferpartypokemon 0x0 0x0
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestShownPokemon MSG_NORMAL
    addvar 0x4053 0x1
    compare 0x4053 0x11 @ 17 swarm pokemon
    if equal _goto AllSwarmPokemonShown
    obtainitem ITEM_BOTTLE_CAP 0x1
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestShownPokemonConclusion MSG_NORMAL
    return

AlreadyShownPokemon:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestAlreadyShown MSG_NORMAL
    goto End

AllSwarmPokemonShown:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestAllSwarmPokemonShown MSG_NORMAL
    obtainitem ITEM_GOLD_BOTTLE_CAP 0x1
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestGratitude MSG_NORMAL
    goto End

.global EventScript_HeleoCity_RainesGrandfather
EventScript_HeleoCity_RainesGrandfather:
    npcchatwithmovement gText_HeleoNPCHouses_RainesGrandfather m_LookLeft
    end

.global EventScript_HeleoCity_RainesCastform
EventScript_HeleoCity_RainesCastform:
    lock
    faceplayer
    checksound
    cry SPECIES_CASTFORM 0x0
    msgbox gText_HeleoNPCHouses_RainesCastform MSG_NORMAL
    waitcry
    goto End

.global EventScript_HeleoCity_TrainersMom
EventScript_HeleoCity_TrainersMom:
    npcchatwithmovement gText_HeleoNPCHouses_TrainersMom m_LookLeft
    end

.global EventScript_HeleoCity_TrainersYoungKid
EventScript_HeleoCity_TrainersYoungKid:
    npcchatwithmovement gText_HeleoNPCHouses_TrainersYoungKid m_LookUp
    end

.global EventScript_HeleoCity_TrainersKid
EventScript_HeleoCity_TrainersKid:
    npcchat gText_HeleoNPCHouses_TrainersKid
    end

.global EventScript_HeleoCity_PokemonFanClubChairman
EventScript_HeleoCity_PokemonFanClubChairman:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokemonAreLame
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman_PokemonAreGood MSG_NORMAL
    applymovement 0x1 m_LookDown
    goto End

PokemonAreLame:
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman_PokemonAreLame MSG_NORMAL
    applymovement 0x1 m_LookDown
    goto End

.global EventScript_HeleoCity_PokemonGroomer
EventScript_HeleoCity_PokemonGroomer:
    lock
    faceplayer
    msgbox gText_HeleoCityNpcHouses_GroomerIntro MSG_NORMAL
    checkflag 0xE0A @ Has groomed today
    if SET _goto PokemonGroomer_AlreadyGroomed
    showmoney 0x0 0x0
    msgbox gText_HeleoCityNpcHouses_GroomerConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokemonGroomer_Denied
    checkmoney 0x3E8 @ 1000
    compare LASTRESULT TRUE
    if FALSE _goto PokemonGroomer_NotEnoughMoney
    goto GroomingChoice

GroomingChoice:
    msgbox gText_HeleoCityNpcHouses_GroomerChoosePokemon MSG_NORMAL
    special 0x9F @ Select a Pokemon and store it's position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if user backed out
    if greaterorequal _goto PokemonGroomer_Denied
    callasm StoreIsPartyMonEgg
    compare LASTRESULT TRUE
    if TRUE _goto PokemonGroomer_InvalidPokemon
    bufferpartypokemon 0x0 0x8004 @ Buffer pokemon nickname
    msgbox gText_HeleoCityNpcHouses_GroomerPokemonChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto GroomingChoice
    goto FinalizeGrooming

FinalizeGrooming:
    removemoney 0x3E8
    sound 0xF8 @ Money SE
    waitse
    updatemoney
    pause DELAY_HALFSECOND
    hidemoney
    bufferpartypokemon 0x0 0x8004
    msgbox gText_HeleoCityNpcHouses_GroomerStarting MSG_NORMAL
    setvar 0x8003 0x0 @ Apply happiness to party pokemon, 0x8004 already holds index
    setvar 0x8005 0x0032 @ Add 50 (out of 255) friendship points (00xx adds, 01xx subtracts)
    fadescreen FADEOUT_BLACK
    fanfare 0x100
	waitfanfare
    special 0x13
    fadescreen FADEIN_BLACK
    setflag 0xE0A @ Daily grooming complete
    msgbox gText_HeleoCityNpcHouses_GroomerComplete MSG_NORMAL
    checkflag 0x24E @ Got soothe bell gift
    if NOT_SET _call PokemonGroomer_FriendshipAssessment
    msgbox gText_HeleoCityNpcHouses_GroomerGroomAgainTomorrow MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_AlreadyGroomed:
    msgbox gText_HeleoCityNpcHouses_GroomerAlreadyGroomedToday MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_Denied:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerDenied MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_NotEnoughMoney:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerNotEnoughMoney MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_InvalidPokemon:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerCannotGroomEgg MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_FriendshipAssessment:
    special2 LASTRESULT 0xD @ Check if selected Pokemon has at least 175 happiness. (0x8003 already set to select from party, and 0x8004 the selected index)
    compare LASTRESULT 175
    if greaterorequal _call PokemonGroomer_GiveSootheBell
    return

PokemonGroomer_GiveSootheBell:
    msgbox gText_HeleoCityNpcHouses_GroomerPokemonFriendshipThresholdMet MSG_NORMAL
    obtainitem ITEM_SOOTHE_BELL 0x1
    msgbox gText_HeleoCityNpcHouses_GroomerSootheBellExplained MSG_NORMAL
    setflag 0x24E @ Got soothe bell gift
    return

PokemonGroomer_End:
    applymovement 0x2 m_LookDown
    goto End

.global EventScript_HeleoCity_PokemonFanClubSuperfan
EventScript_HeleoCity_PokemonFanClubSuperfan:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubSuperfan m_LookUp
    end

.global EventScript_HeleoCity_PokemonFanClubSwimmer
EventScript_HeleoCity_PokemonFanClubSwimmer:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubSwimmer m_LookRight
    end

.global EventScript_HeleoCity_PokemonFanClubMother
EventScript_HeleoCity_PokemonFanClubMother:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubMother m_LookLeft
    end

.global EventScript_HeleoCity_HallwayBoy
EventScript_HeleoCity_HallwayBoy:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubHallwayBoy m_LookLeft
    end

.global EventScript_HeleoCity_TerraceDad
EventScript_HeleoCity_TerraceDad:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceDad m_LookLeft
    end

.global EventScript_HeleoCity_TerraceMom
EventScript_HeleoCity_TerraceMom:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceMom m_LookLeft
    end

.global EventScript_HeleoCity_TerraceSon
EventScript_HeleoCity_TerraceSon:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceSon m_LookRight
    end

.global EventScript_HeleoCity_SodaMachineGirl
EventScript_HeleoCity_SodaMachineGirl:
    npcchat gText_HeleoNPCHouses_VendingMachineGirl
    end

@ Gym
.global MapScript_HeleoCityGym
MapScript_HeleoCityGym:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_HeleoCityGym
    .byte MAP_SCRIPT_TERMIN

LevelScripts_HeleoCityGym:
    @ Trigger this when the Ferrox story var indicates Alistair has been talked to (ie. always, when this gym is accessible)  
    levelscript 0x4052 0x3 LevelScripts_HeleoCityGym_SetPlayerFacing
    .hword LEVEL_SCRIPT_TERMIN

LevelScripts_HeleoCityGym_SetPlayerFacing:
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x14 @ Player warped to gym entrance
    if equal _goto SetPlayerPosForGymEntranceWarp
    compare PLAYERFACING DOWN
    if equal _goto FaceDown
    compare PLAYERFACING UP
    if equal _goto FaceUp
    compare PLAYERFACING LEFT
    if equal _goto FaceLeft
    compare PLAYERFACING RIGHT
    if equal _goto FaceRight
    end

FaceLeft:
    spriteface PLAYER LEFT
    spriteface LASTTALKED RIGHT @ Last talked is one of the Castform
    end

FaceRight:
    spriteface PLAYER RIGHT
    spriteface LASTTALKED LEFT 
    end

FaceUp:
    spriteface PLAYER UP
    spriteface LASTTALKED DOWN 
    end

FaceDown:
    spriteface PLAYER DOWN
    spriteface LASTTALKED UP 
    end

SetPlayerPosForGymEntranceWarp:
    spriteface PLAYER DOWN
    end

.global EventScript_HeleoGym_CastformWater
EventScript_HeleoGym_CastformWater:
    call CastformCommon
    playse 0xC3 @ Sunny day
    call SetWeatherSunny
    msgbox gText_HeleoCityGym_CastformSunnyDay MSG_NORMAL
    call CastformCommon_WeatherChanging
    warpmuted 1 93 0xFF 0x4000 0x4001 @ Warp to same spot in drained map
    end

.global EventScript_HeleoGym_CastformDrained
EventScript_HeleoGym_CastformDrained:
    call CastformCommon
    call SetWeatherRain
    msgbox gText_HeleoCityGym_CastformRainDance MSG_NORMAL
    call CastformCommon_WeatherChanging
    warpmuted 1 92 0xFF 0x4000 0x4001 @ Warp to same spot in flooded map
    end

CastformCommon:
    lock
    faceplayer
    checksound
    cry SPECIES_CASTFORM 0x0
    waitcry
    return

CastformCommon_WeatherChanging:
    fadescreenswapbuffers 0x1
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    return

.global EventScript_HeleoGym_SwimmerTessa
EventScript_HeleoGym_SwimmerTessa:
    trainerbattle0 0x0 0x65 0x0 gText_HeleoCityGym_SwimmerTessaIntro gText_HeleoCityGym_SwimmerTessaDefeat
    msgbox gText_HeleoCityGym_SwimmerTessaChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerByron
EventScript_HeleoGym_SwimmerByron:
    trainerbattle0 0x0 0x66 0x0 gText_HeleoCityGym_SwimmerByronIntro gText_HeleoCityGym_SwimmerByronDefeat
    msgbox gText_HeleoCityGym_SwimmerByronChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerDanette
EventScript_HeleoGym_SwimmerDanette:
    trainerbattle0 0x0 0x67 0x0 gText_HeleoCityGym_SwimmerDanetteIntro gText_HeleoCityGym_SwimmerDanetteDefeat
    msgbox gText_HeleoCityGym_SwimmerDanetteChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerMaisey
EventScript_HeleoGym_SwimmerMaisey:
    trainerbattle0 0x0 0x68 0x0 gText_HeleoCityGym_SwimmerMaiseyIntro gText_HeleoCityGym_SwimmerMaiseyDefeat
    msgbox gText_HeleoCityGym_SwimmerMaiseyChat MSG_NORMAL
    end

.global EventScript_HeleoGym_LeaderRaine
EventScript_HeleoGym_LeaderRaine:
    lockall
    faceplayer
    checkflag 0x822 @ Heleo gym badge
    if SET _goto EventScript_HeleoGym_LeaderRaine_Chat
    msgbox gText_HeleoGym_LeaderRaine_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    callasm CountBadges
    compare LASTRESULT 0x2
    if equal _goto LeaderRaine_2Badges
    compare LASTRESULT 0x3
    if equal _goto LeaderRaine_3Badges
    compare LASTRESULT 0x4
    if equal _goto LeaderRaine_4Badges
    end

LeaderRaine_2Badges:
    trainerbattle1 0x1 105 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

LeaderRaine_3Badges:
    trainerbattle1 0x1 256 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

LeaderRaine_4Badges:
    trainerbattle1 0x1 257 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

EventScript_HeleoGym_LeaderRaine_Defeated:
    msgbox gText_HeleoGym_LeaderRaine_BadgeAwarded MSG_NORMAL
    setflag 0x822 @ Heleo gym badge
    fanfare 0x13D @ Gym victory
    msgbox gText_HeleoGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    settrainerflag 0x65 @ Tessa cannot be battled now
    settrainerflag 0x66 @ Byron cannot be battled now
    settrainerflag 0x67 @ Danette cannot be battled now
    settrainerflag 0x68 @ Maisey cannot be battled now
    msgbox gText_HeleoGym_LeaderRaine_BadgeDescription MSG_NORMAL
    msgbox gText_HeleoGym_LeaderRaine_TMReceived MSG_NORMAL
    fanfare 0x101
    additem ITEM_TM07 0x1 @ Hail
    additem ITEM_TM11 0x1 @ Sunny Day
    additem ITEM_TM18 0x1 @ Rain Dance
    additem ITEM_TM37 0x1 @ Sandstorm
    msgbox gText_HeleoGym_TMReceived MSG_KEEPOPEN
    setflag 0x4B2 @ Defeated Raine
    setflag 0x25C @ New Pokemart Stock
    msgbox gText_HeleoGym_LeaderRaine_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_HeleoGym_LeaderRaine_Chat:
    npcchat gText_HeleoGym_LeaderRaine_Chat
    end

.global EventScript_HeleoGym_GymExpert
EventScript_HeleoGym_GymExpert:
    checkflag 0x822 @ Heleo gym badge
    if SET _goto EventScript_HeleoGym_GymExpertBadgeObtained
    npcchat gText_HeleoGym_ExpertTips
    end

EventScript_HeleoGym_GymExpertBadgeObtained:
    npcchat gText_HeleoGym_ExpertBadgeObtained
    end

.global SignScript_HeleoGym_Placard
SignScript_HeleoGym_Placard:
    checkflag 0x822 @ Heleo gym badge
    if SET _goto SignScript_HeleoGym_PlacardWithBadge
    msgbox gText_HeleoGym_Winners MSG_SIGN
    end

SignScript_HeleoGym_PlacardWithBadge:
    msgbox gText_HeleoGym_WinnersWithBadge MSG_SIGN
    end

.global EventScript_HeleoGym_Slowbro
EventScript_HeleoGym_Slowbro:
    faceplayer
    cry SPECIES_SLOWBRO 0x0
    applymovement LASTTALKED m_Question 
    msgbox gText_HeleoGym_SlowbroQuestion MSG_NORMAL
    msgbox gText_HeleoGym_SlowbroConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto SlowbroNo
    cry SPECIES_SLOWBRO 0x0
    msgbox gText_HeleoGym_SlowbroYes MSG_NORMAL
    waitcry
    playse 0x27 @ Warp away
    pause DELAY_HALFSECOND
    warpmuted 1 92 0xFF 0xF 0x14 @ Warp to gym entrance, in flooded map
    end

SlowbroNo:
    cry SPECIES_SLOWBRO 0x3 @ Fainted sound, pitched down
    msgbox gText_HeleoGym_SlowbroNo MSG_NORMAL
    waitcry
    applymovement LASTTALKED m_LookDown
    end
