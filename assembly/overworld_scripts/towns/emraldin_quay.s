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

.global EventScript_EmraldinQuayTrainerHouse_Host
EventScript_EmraldinQuayTrainerHouse_Host:
    faceplayer
    msgbox gText_EmraldinQuay_TrainerHouse_HostIntro MSG_NORMAL
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
    checkflag 0xE1A @ Already battled today
    if SET _goto TrainerHouse_Common_AlreadyBattledToday
    call TrainerHousePreBattleSetup
    call TrainerHouse_Common_MoveToBattlePosition
    setflag 0x90E @ Scale trainer levels
    applymovement 0x1 m_LookUp
    @ First Opponent
    msgbox gText_EmraldinQuay_TrainerHouse_FirstOpponentArriving MSG_NORMAL
    setflag 0x92C @ Turn on camomon battles
    setvar 0x8001 0x5
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_EmraldinQuay_TrainerHouse_B1ChannelerMargueriteIntro MSG_NORMAL
    trainerbattle9 0x0 366 0x0 gText_EmraldinQuay_TrainerHouse_B1ChannelerMargueriteWin gText_EmraldinQuay_TrainerHouse_B1ChannelerMargueriteLose
    call HandleBattleEnded
    @ Second Opponent
    msgbox gText_EmraldinQuay_TrainerHouse_SecondOpponentArriving MSG_NORMAL
    setvar 0x8001 0x6
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_EmraldinQuay_TrainerHouse_B2NinjaBoyJulienIntro MSG_NORMAL
    trainerbattle9 0x0 367 0x0 gText_EmraldinQuay_TrainerHouse_B2NinjaBoyJulienWin gText_EmraldinQuay_TrainerHouse_B2NinjaBoyJulienLose
    call HandleBattleEnded
    @ Third Opponent
    msgbox gText_EmraldinQuay_TrainerHouse_ThirdOpponentArriving MSG_NORMAL
    setvar 0x8001 0x7
    call TrainerHouse_Common_OpponentArrives
    msgbox gText_EmraldinQuay_TrainerHouse_B3BugCatcherPerryIntro MSG_NORMAL
    trainerbattle9 0x0 368 0x0 gText_EmraldinQuay_TrainerHouse_B3BugCatcherPerryWin gText_EmraldinQuay_TrainerHouse_B3BugCatcherPerryLose
    call HandleBattleEnded
    msgbox gText_EmraldinQuay_TrainerHouse_AllOpponentsDefeated MSG_NORMAL
    call TrainerHouse_Common_ReturnToHost
    goto TrainerHouseGivePrizes

TrainerHousePreBattleSetup:
    msgbox gText_EmraldinQuay_TrainerHouse_BattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto TrainerHouse_Common_End
    msgbox gText_EmraldinQuay_TrainerHouse_ChoseBattle MSG_NORMAL
    setflag 0xE1A @ Already battled today
    setvar 0x8000 0xFEFE @ Continue lost battles
    msgbox gText_EmraldinQuay_TrainerHouse_HealingPokemon MSG_NORMAL
    call PlayerHeal
    msgbox gText_EmraldinQuay_TrainerHouse_PreChallengeComment MSG_NORMAL
    setvar 0x4090 0x0 @ 0 win streak
    return

TrainerHouseStreakLost:
    fanfare 0x10F @ Failure
    msgbox gText_EmraldinQuay_TrainerHouse_StreakLost MSG_KEEPOPEN
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
    if equal _call TrainerHouse_Common_GiveHyperPotion
    return

TrainerHouseTier2Prizes:
    random 0x3
    copyvar 0x8003 LASTRESULT
    compare 0x8003 0x0
    if equal _call TrainerHouse_Common_GiveUltraBall
    compare 0x8003 0x1
    if equal _call TrainerHouse_Common_GiveMaxPotion
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
    if equal _call TrainerHouse_Common_GiveRevive
    compare 0x8004 0x2
    if equal _call TrainerHouse_Common_GiveQuickBall
    pause DELAY_HALFSECOND
    call TrainerHouseTier2Prizes
    call TrainerHouseCheckForGrandPrize
    return

TrainerHouseCheckForGrandPrize:
    incrementgamestat 25
    checkflag 0x252 @ Got the item finder
    if NOT_SET _call TrainerHouseGiveGrandPrize
    return

TrainerHouseGiveGrandPrize:
    msgbox gText_EmraldinQuay_TrainerHouse_GrandPrizeAwarded MSG_NORMAL
    fanfare 0x10C @ Big Celebration
    obtainitem ITEM_ITEMFINDER 0x1
    waitfanfare
    setflag 0x252 @ Got the item finder
    return 

TrainerHouseDidNotBeatAnyTrainers:
    msgbox gText_TrainerHouse_AnalysisBeatNoTrainers MSG_NORMAL
    goto Trainerhouse_ResetStateAtEnd

Trainerhouse_trainerhouserules:
    msgbox gText_TrainerHouse_ChoseTrainerHouseRules MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_ruleset:
    msgbox gText_EmraldinQuay_TrainerHouse_ChoseRuleset MSG_NORMAL
    goto TrainerHouse_Menu

Trainerhouse_grandprize:
    msgbox gText_EmraldinQuay_TrainerHouse_ChoseGrandPrize MSG_NORMAL
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
    clearflag 0x92C @ Turn off camomon battles
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call TrainerHouse_Common_DisableScalingFlag
    msgbox gText_TrainerHouse_HealingPokemonAtEnd MSG_NORMAL
    call PlayerHeal
    goto TrainerHouse_Common_End

.global EventScript_EmraldinQuayTrainerHouse_Boy
EventScript_EmraldinQuayTrainerHouse_Boy:
    npcchat gText_EmraldinQuay_TrainerHouse_Boy
    end

.global EventScript_EmraldinQuayTrainerHouse_FatGuy
EventScript_EmraldinQuayTrainerHouse_FatGuy:
    npcchatwithmovement gText_EmraldinQuay_TrainerHouse_FatGuy m_LookLeft
    end

.global EventScript_EmraldinQuayTrainerHouse_Girl
EventScript_EmraldinQuayTrainerHouse_Girl:
    faceplayer
    msgbox gText_EmraldinQuay_TrainerHouse_Girl MSG_YESNO
    compare LASTRESULT YES
    if TRUE _call TrainerHouseGirlAskedForTips
    if FALSE _call TrainerHouseGirlNoTips
    applymovement LASTTALKED m_LookDown
    end

TrainerHouseGirlAskedForTips:
    msgbox gText_EmraldinQuay_TrainerHouse_Girl_ChoseYes MSG_NORMAL
    return

TrainerHouseGirlNoTips:
    msgbox gText_EmraldinQuay_TrainerHouse_Girl_ChoseNo MSG_NORMAL
    return

.global SignScript_EmraldinQuay_TrainerHouseSign
SignScript_EmraldinQuay_TrainerHouseSign:
    msgbox gText_EmraldinQuay_TrainerHouse_SpecializationSign MSG_SIGN
    end
