.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_TsarvosaCity
MapScript_TsarvosaCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_TsarvosaCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_TsarvosaCity_FlightSpot:
    setworldmapflag 0x899 @ Visited Tsarvosa City
    clearflag 0x91D @ Enable saving when leaving the Gym Trainee Cafe
    end

.global EventScript_TsarvosaCity_Captain
EventScript_TsarvosaCity_Captain:
    npcchatwithmovement gText_TsarvosaCity_Captain m_LookUp
    end

.global EventScript_TsarvosaCity_DockWorker
EventScript_TsarvosaCity_DockWorker:
    npcchatwithmovement gText_TsarvosaCity_DockWorker m_LookLeft
    end

.global EventScript_TsarvosaCity_StatsDojoFan
EventScript_TsarvosaCity_StatsDojoFan:
    npcchat gText_TsarvosaCity_StatsDojoFan
    end

.global EventScript_TsarvosaCity_DirectionsGirl
EventScript_TsarvosaCity_DirectionsGirl:
    npcchat gText_TsarvosaCity_DirectionsGirl
    end

.global EventScript_TsarvosaCity_GymFan
EventScript_TsarvosaCity_GymFan:
    npcchatwithmovement gText_TsarvosaCity_GymFan m_LookDown
    end

.global EventScript_TsarvosaCity_GymsFeudMan
EventScript_TsarvosaCity_GymsFeudMan:
    npcchat gText_TsarvosaCity_GymsFeudMan
    end

.global EventScript_TsarvosaCity_MarketWoman
EventScript_TsarvosaCity_MarketWoman:
    npcchat gText_TsarvosaCity_MarketWoman 
    end

.global EventScript_TsarvosaCity_OldMan
EventScript_TsarvosaCity_OldMan:
    npcchat gText_TsarvosaCity_OldMan
    end

.global EventScript_TsarvosaCity_MimmettJungleGirl
EventScript_TsarvosaCity_MimmettJungleGirl:
    npcchat gText_TsarvosaCity_MimmettJungleGirl
    end

.global SignScript_TsarvosaCity_TownPlacard
SignScript_TsarvosaCity_TownPlacard:
    msgbox gText_TsarvosaCity_TownPlacard MSG_SIGN
    end

.global SignScript_TsarvosaCity_StatsDojo
SignScript_TsarvosaCity_StatsDojo:
    msgbox gText_TsarvosaCity_StatsDojoSign MSG_SIGN
    end

.global SignScript_TsarvosaCity_DevStudioSign
SignScript_TsarvosaCity_DevStudioSign:
    msgbox gText_TsarvosaCity_DevStudioSign MSG_SIGN
    end

.global SignScript_TsarvosaCity_GymTraineesCafeSign
SignScript_TsarvosaCity_GymTraineesCafeSign:
    msgbox gText_TsarvosaCity_GymTraineeCafeSign MSG_SIGN
    end

.global EventScript_TsarvosaCity_DaimynFactoryPresident
EventScript_TsarvosaCity_DaimynFactoryPresident:
    faceplayer
    checkitem ITEM_FACTORY_KEY 0x1
    compare LASTRESULT TRUE
    if TRUE _goto AlreadyHaveKey
    msgbox gText_TsarvosaCity_DaimynFactoryMan MSG_NORMAL
    end

AlreadyHaveKey:
    msgbox gText_TsarvosaCity_DaimynFactoryMan_HaveKey MSG_NORMAL
    end

@ Pokemon Center
.global MapScript_TsarvosaCity_PokemonCenter
MapScript_TsarvosaCity_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot:
    sethealingplace 0xB
    call ResetUteyaVillageGymFlagsOnWhiteout
    end

.global EventScript_TsarvosaCity_PokemonCenter_FatGuy
EventScript_TsarvosaCity_PokemonCenter_FatGuy:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_FatGuy m_LookLeft
    end

.global EventScript_TsarvosaCity_PokemonCenter_Policeman
EventScript_TsarvosaCity_PokemonCenter_Policeman:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_Policeman m_LookDown
    end

.global EventScript_TsarvosaCity_PokemonCenter_Girl
EventScript_TsarvosaCity_PokemonCenter_Girl:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_Girl m_LookLeft
    end

@ Stats Dojo
.equ Attendant, 0x1
.equ Kaito, 0x2

.global MapScript_TsarvosaCity_StatsDojo
MapScript_TsarvosaCity_StatsDojo:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_StatsDojo_AttendantCutscene
	mapscript MAP_SCRIPT_ON_TRANSITION MapScript_StatsDojo_PositionAttendant
    mapscript MAP_SCRIPT_ON_RESUME MapResumeScript_ResetEVDiscipleFlags
    .byte MAP_SCRIPT_TERMIN

LevelScripts_StatsDojo_AttendantCutscene:
    levelscript 0x405E 0x0 LevelScript_AttendantWelcomesPlayer
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_AttendantWelcomesPlayer:
    pause DELAY_HALFSECOND
    applymovement Attendant m_LookLeft
    pause DELAY_HALFSECOND
    applymovement Attendant m_LookRight
    pause DELAY_HALFSECOND
    applymovement Attendant m_LookDown
    waitmovement Attendant
    sound 0x15 @ Exclaim
    applymovement Attendant m_Surprise
    waitmovement Attendant
    pause DELAY_HALFSECOND
    applymovement Attendant m_AttendantWalksToPlayer
    waitmovement Attendant
    msgbox gText_TsarvosaCity_StatsDojo_AttendantIntro MSG_NORMAL
    msgbox gText_TsarvosaCity_StatsDojo_AttendantRegularChat MSG_NORMAL
    applymovement Attendant m_AttendantReturnsToRegularSpot
    waitmovement ALLEVENTS
    setvar 0x405E 0x1
    end

MapScript_StatsDojo_PositionAttendant:
    compare 0x405E 0x0
    if equal _goto End
    movesprite2 Attendant 0xB 0xB @ Beside the right podium
    setobjectmovementtype Attendant look_down
    end

MapResumeScript_ResetEVDiscipleFlags:
    cleartrainerflag 407 @ Level 1 HP
    cleartrainerflag 408 @ Level 2 HP
    cleartrainerflag 409 @ Level 3 HP
    cleartrainerflag 410 @ Level 1 Attack
    cleartrainerflag 411 @ Level 2 Attack
    cleartrainerflag 412 @ Level 3 Attack
    cleartrainerflag 413 @ Level 1 Defense
    cleartrainerflag 414 @ Level 2 Defense
    cleartrainerflag 415 @ Level 3 Defense
    cleartrainerflag 416 @ Level 1 Special Attack
    cleartrainerflag 417 @ Level 2 Special Attack
    cleartrainerflag 418 @ Level 3 Special Attack
    cleartrainerflag 419 @ Level 1 Special Defense
    cleartrainerflag 420 @ Level 2 Special Defense
    cleartrainerflag 421 @ Level 3 Special Defense
    cleartrainerflag 422 @ Level 1 Speed
    cleartrainerflag 423 @ Level 2 Speed
    cleartrainerflag 424 @ Level 3 Speed
    end

.global EventScript_TsarvosaCity_StatsDojo_Attendant
EventScript_TsarvosaCity_StatsDojo_Attendant:
    npcchatwithmovement gText_TsarvosaCity_StatsDojo_AttendantRegularChat m_LookDown
    end

.global EventScript_TsarvosaCity_StatsDojo_Kaito
EventScript_TsarvosaCity_StatsDojo_Kaito:
    faceplayer
    checktrainerflag 406
    if SET _goto KaitoWelcomesPlayer
    msgbox gText_TsarvosaCity_StatsDojo_KaitoIntroduction MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleKaito
    call PrepareKaitoBattle
    call SetupMugshotGymLeaderAndBosses
    msgbox gText_TsarvosaCity_StatsDojo_KaitoChoseYes MSG_NORMAL
    trainerbattle9 0x1 406 0x100 gText_TsarvosaCity_StatsDojo_KaitoLoses gText_TsarvosaCity_StatsDojo_KaitoWins    
    clearflag 0x915 @ Can use items again
    setvar 0x8000 0x0 @ Does not continue after lost battles
    compare LASTRESULT TRUE
    if equal _goto LostToKaito
    goto KaitoDefeated
    end

ChoseNotToBattleKaito:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoChoseNo MSG_NORMAL
    applymovement Kaito m_LookDown
    end

PrepareKaitoBattle:
    setflag 0x915 @ Can't use items
    setvar 0x8003 0x0 @ Remove held items from party (Failures are ignored, such as eggs or empty slots)
    setvar 0x8005 0x0 @ 0 = Removal
    setvar 0x8004 0x0 @ First slot
    special 0x15
    setvar 0x8004 0x1 @ Second slot
    special 0x15
    setvar 0x8004 0x2 @ Third slot
    special 0x15
    setvar 0x8004 0x3 @ Fourth slot
    special 0x15
    setvar 0x8004 0x4 @ Fifth slot
    special 0x15
    setvar 0x8004 0x5 @ Sixth slot
    special 0x15
    setvar 0x8000 0xFEFE @ Continue lost battles
    return

LostToKaito:
    msgbox gText_TsarvosaCity_StatsDojo_LostToKaito MSG_NORMAL
    call PlayerHeal
    cleartrainerflag 406 @ Player needs to battle Kaito again to proceed
    msgbox gText_TsarvosaCity_StatsDojo_KaitoUrgesThePlayerToReturn MSG_NORMAL
    applymovement Kaito m_LookDown
    end

KaitoDefeated:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoGivesStrength MSG_NORMAL
    setflag 0x25F @ Defeated Kaito and got Strength
    obtainitem ITEM_HM04 0x1 @ Strength
    msgbox gText_TsarvosaCity_StatsDojo_KaitoCommentsOnBadge MSG_NORMAL
    setvar 0x405E 0x2 @ Kaito defeated
    msgbox gText_TsarvosaCity_StatsDojo_KaitoAsksToExplainServices MSG_YESNO
    compare LASTRESULT NO
    if equal _goto KaitoChoseToDoNothing
    call ExplainFacilities
    end

KaitoWelcomesPlayer:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoWelcomesPlayer MSG_KEEPOPEN
    goto KaitoDojoOptions

KaitoDojoOptions:
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_InvestInShops 0
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_InvestInPowerItems 1
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_InvestInIVMaxer 2
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_InvestInDisciples 3
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_ExplainFacilities 4
    multichoiceoption gText_TsarvosaCity_StatsDojo_KaitoOptions_Nothing 5
    multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
	case 0, ShopInvestment
    case 1, PowerItemInvestment
	case 2, IVMaxerInvestment
    case 3, DisciplesInvestment
	case 4, ExplainFacilities
	case 5, KaitoChoseToDoNothing
    goto KaitoChoseToDoNothing
    end

ShopInvestment:
    compare 0x409D 0x2 @ Shop level
    if equal _goto AllItemsUnlockedWithReturnToMenu
    copyvar 0x4000 0x409D
    addvar 0x4000 0x1 @ +1 for readability
    compare 0x409D 0x0 @ Level 1
    if equal _call SetupLevelTwoShopCost
    compare 0x409D 0x1 @ Level 2
    if equal _call SetupLevelThreeShopCost
    buffernumber 0x0 0x4000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_ShopInvestmentCost MSG_NORMAL
    call HandleInvestmentPayment
    addvar 0x405E 0x1 @ Total Investment in the dojo
    addvar 0x409D 0x1 @ Internal number
    addvar 0x4000 0x1 @ Number shown in dialog
    buffernumber 0x0 0x4000
    fanfare 0x101 @ Level Up
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_ShopLevelledUp MSG_NORMAL
    waitfanfare
    compare 0x409D 0x1
    if equal _call ShopIsLevel2Now
    compare 0x409D 0x2
    if equal _call ShopIsLevel3Now
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_FinishedInvestingAndReturningToMenu MSG_NORMAL
    goto KaitoDojoOptions

SetupLevelTwoShopCost:
    setvar 0x8004 20000
    return

SetupLevelThreeShopCost:
    setvar 0x8004 50000
    return

ShopIsLevel2Now:
    setvar 0x8004 50000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_ShopLevel2Unlocked MSG_NORMAL
    return

ShopIsLevel3Now:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_ShopLevel3Unlocked MSG_NORMAL
    call AllItemsUnlocked
    return

PowerItemInvestment:
    compare 0x409E 0x2 @ Power Item investment
    if equal _goto PowerItemLevelsMaxedOutWithReturnToMenu
    copyvar 0x4000 0x409E
    addvar 0x4000 0x1 @ + 1 for readability
    compare 0x409E 0x0 @ Level 1
    if equal _call SetupLevelTwoResearchCost
    compare 0x409E 0x1 @ Level 2
    if equal _call SetupLevelThreeResearchCost
    buffernumber 0x0 0x4000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_PowerItemInvestmentCost MSG_NORMAL
    compare 0x409D 0x2 @ Shop level
    if lessthan _call ShopsAreNotMaxedYet
    call HandleInvestmentPayment
    addvar 0x405E 0x1 @ Total Investment in the dojo
    addvar 0x409E 0x1 @ Internal number
    addvar 0x4000 0x1 @ Number shown in dialog
    copyvar 0x40A1 0x409E @ Setup Power Item level, which is +1 on the shop level to double/triple EVs
    addvar 0x40A1 0x1
    buffernumber 0x0 0x4000
    fanfare 0x101 @ Level Up
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_PowerItemsLevelledUp MSG_NORMAL
    waitfanfare
    compare 0x409E 0x1
    if equal _call PowerItemsAreLevel2Now
    compare 0x409E 0x2
    if equal _call PowerItemsAreLevel3Now
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_FinishedInvestingAndReturningToMenu MSG_NORMAL
    goto KaitoDojoOptions

SetupLevelTwoResearchCost:
    setvar 0x8004 40000
    return

SetupLevelThreeResearchCost:
    setvar 0x8004 60000
    return

ShopsAreNotMaxedYet:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_PowerItemInvestmentShopsNotLevelledUp MSG_NORMAL
    return

PowerItemsAreLevel2Now:
    setvar 0x8004 60000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_PowerItemsLevel2Unlocked MSG_NORMAL
    return

PowerItemsAreLevel3Now:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_PowerItemsLevel3Unlocked MSG_NORMAL
    call PowerItemLevelsMaxedOut
    return

IVMaxerInvestment:
    compare 0x409F 0x2 @ IV Maxer Level
    if equal _goto IVMaxingAtMaxLevelReturnToMenu
    copyvar 0x4000 0x409F
    addvar 0x4000 0x1 @ +1 for readability
    compare 0x409F 0x0 @ Level 1
    if equal _call SetupLevelTwoResearchCost
    compare 0x409F 0x1 @ Level 2
    if equal _call SetupLevelThreeShopCost
    buffernumber 0x0 0x4000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_IVMaxingInvestmentCost MSG_NORMAL
    call HandleInvestmentPayment
    addvar 0x405E 0x1 @ Total Investment in the dojo
    addvar 0x409F 0x1 @ Internal number
    addvar 0x4000 0x1 @ Number shown in dialog
    buffernumber 0x0 0x4000
    fanfare 0x101 @ Level Up
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_IVMaxingLevelledUp MSG_NORMAL
    waitfanfare
    compare 0x409F 0x1
    if equal _call IVMaxingIsLevel2Now
    compare 0x409F 0x2
    if equal _call IVMaxingIsLevel3Now
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_FinishedInvestingAndReturningToMenu MSG_NORMAL
    goto KaitoDojoOptions

IVMaxingIsLevel2Now:
    setvar 0x8004 60000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_IVMaxingLevel2Unlocked MSG_NORMAL
    return

IVMaxingIsLevel3Now:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_IVMaxingLevel3Unlocked MSG_NORMAL
    call IVMaxingAtMaxLevel
    return

DisciplesInvestment:
    compare 0x40A0 0x2 @ Disciples Level
    if equal _goto DisciplesAtMaxLevelReturnToMenu
    copyvar 0x4000 0x40A0
    addvar 0x4000 0x1 @ +1 for readability
    compare 0x40A0 0x0 @ Level 1
    if equal _call SetupLevelTwoDisciplesCost
    compare 0x40A0 0x1 @ Level 2
    if equal _call SetupLevelThreeDisciplesCost
    buffernumber 0x0 0x4000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_DisciplesInvestmentCost MSG_NORMAL
    call HandleInvestmentPayment
    addvar 0x405E 0x1 @ Total Investment in the dojo
    addvar 0x40A0 0x1 @ Internal number
    addvar 0x4000 0x1 @ Number shown in dialog
    buffernumber 0x0 0x4000
    fanfare 0x101 @ Level Up
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_DisciplesLevelledUp MSG_NORMAL
    waitfanfare
    compare 0x40A0 0x1
    if equal _call DisciplesAreLevel2Now
    compare 0x40A0 0x2
    if equal _call DisciplesAreLevel3Now
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_FinishedInvestingAndReturningToMenu MSG_NORMAL
    goto KaitoDojoOptions

SetupLevelTwoDisciplesCost:
    setvar 0x8004 30000
    return

SetupLevelThreeDisciplesCost:
    setvar 0x8004 60000
    return

DisciplesAreLevel2Now:
    setvar 0x8004 60000
    buffernumber 0x1 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_DisciplesLevel2Unlocked MSG_NORMAL
    return

DisciplesAreLevel3Now:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_DisciplesLevel3Unlocked MSG_NORMAL
    call DisciplesAtMaxLevel
    return

HandleInvestmentPayment:
    showmoney 0x0 0x0
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_CostConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToInvest
    callasm CheckMoneyFromVar @ Check if player has enough money (from var 0x8004)
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughMoney
    playse 0xF8 @ Money
    callasm RemoveMoneyFromVar @ Removes based on var 0x8004 value
    updatemoney 0x0 0x0
    waitse
    pause DELAY_1SECOND
    hidemoney
    return

ExplainFacilities:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsGeneralPurpose MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_CameraMovesLeft
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsItemShop MSG_NORMAL
    compare 0x409D 0x2 @ Shop level, maxes at 3
    if lessthan _call MoreItemsToUnlock
    if greaterthan _call AllItemsUnlocked
    special CAMERA_START
    applymovement CAMERA m_CameraMovesRight
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsIVMaxerAndPowerItems MSG_NORMAL
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsPowerItems MSG_NORMAL
    compare 0x409E 0x2 @ Power Item level, maxes at 3
    if lessthan _call PowerItemLevelsNotMaxedOut
    if greaterthan _call PowerItemLevelsMaxedOut
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsIVMaxer MSG_NORMAL
    compare 0x409F 0x2 @ IV Maxer level, maxes at 3
    if lessthan _call IVMaxingNotAtMaxLevel
    if greaterthan _call IVMaxingAtMaxLevel
    special CAMERA_START
    applymovement CAMERA m_CameraMovesLeft
    waitmovement CAMERA
    applymovement CAMERA m_CameraMovesDown
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsEVDisciples MSG_NORMAL
    compare 0x40A0 0x2 @ EV Disciple level, maxes at 3
    if lessthan _call DisciplesNotAtMaxLevel
    if greaterthan _call DisciplesAtMaxLevel
    special CAMERA_START
    applymovement CAMERA m_CameraMovesUp
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsHimself MSG_NORMAL
    compare 0x405E 0xA @ 2 levels per shop, plus 2 initial events
    if lessthan _call FundingRemains
    if greaterthan _call FundingIsComplete
    applymovement Kaito m_LookDown
    end

MoreItemsToUnlock:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsItemsShop_NotFunded MSG_NORMAL
    return

AllItemsUnlocked:
    fanfare 0x10D @ Fanfare 2
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsItemsShop_Funded MSG_NORMAL
    waitfanfare
    return

AllItemsUnlockedWithReturnToMenu:
    call AllItemsUnlocked
    goto KaitoDojoOptions
    end

PowerItemLevelsNotMaxedOut:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsPowerItems_NotFunded MSG_NORMAL
    return

PowerItemLevelsMaxedOut:
    fanfare 0x10D @ Fanfare 2
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsPowerItems_Funded MSG_NORMAL
    waitfanfare
    return

PowerItemLevelsMaxedOutWithReturnToMenu:
    call PowerItemLevelsMaxedOut
    goto KaitoDojoOptions
    end

IVMaxingNotAtMaxLevel:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsIVMaxer_NotFunded MSG_NORMAL
    return

IVMaxingAtMaxLevel:
    fanfare 0x10D @ Fanfare 2
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsIVMaxer_Funded MSG_NORMAL
    waitfanfare
    return

IVMaxingAtMaxLevelReturnToMenu:
    call IVMaxingAtMaxLevel
    goto KaitoDojoOptions
    end

DisciplesNotAtMaxLevel:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsEVDisciples_NotFunded MSG_NORMAL
    return

DisciplesAtMaxLevel:
    fanfare 0x10D @ Fanfare 2
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsEVDisciples_Funded MSG_NORMAL
    waitfanfare
    return

DisciplesAtMaxLevelReturnToMenu:
    call DisciplesAtMaxLevel
    goto KaitoDojoOptions
    end

FundingRemains:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsHimself_FundingRemains MSG_NORMAL
    return

FundingIsComplete:
    fanfare 0x102
    msgbox gText_TsarvosaCity_StatsDojo_KaitoExplainsHimself_NoFundingRemains MSG_NORMAL
    waitfanfare
    return

KaitoChoseToDoNothing:
    msgbox gText_TsarvosaCity_StatsDojo_KaitoAsksToExplainServices_PlayerChoseNo MSG_NORMAL
    applymovement Kaito m_LookDown
    end

ChoseNotToInvest:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_ChoseNotToInvest MSG_KEEPOPEN
    goto KaitoDojoOptions

NotEnoughMoney:
    msgbox gText_TsarvosaCity_StatsDojo_Kaito_NotEnoughMoney MSG_KEEPOPEN
    goto KaitoDojoOptions

FacilitiesCannotOfferServices:
    msgbox gText_TsarvosaCity_StatsDojo_Common_FacilitiesBeforeBeatingKaito MSG_NORMAL
    end

ShopLevelTooLow:
    msgbox gText_TsarvosaCity_StatsDojo_Common_ShopLevelTooLow MSG_NORMAL
    end

.global EventScript_TsarvosaCity_StatsDojo_VitaminShop
EventScript_TsarvosaCity_StatsDojo_VitaminShop:
    msgbox gText_TsarvosaCity_StatsDojo_VitaminsShop MSG_KEEPOPEN
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    pokemart VitaminsShop @ Common shop
    goto EventScript_EndMart
    end

.global EventScript_TsarvosaCity_StatsDojo_EVReducingBerryShop
EventScript_TsarvosaCity_StatsDojo_EVReducingBerryShop:
    compare 0x409D 0x1 @ Shop level
    if lessthan _goto ShopLevelTooLow
    msgbox gText_TsarvosaCity_StatsDojo_EVBerriesShop MSG_KEEPOPEN
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    pokemart EVReducingBerriesShop @ Common Shop
    goto EventScript_EndMart
    end

.global EventScript_TsarvosaCity_StatsDojo_PowerItemShop
EventScript_TsarvosaCity_StatsDojo_PowerItemShop:
    compare 0x409D 0x2 @ Shop level
    if lessthan _goto ShopLevelTooLow
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsShop MSG_KEEPOPEN
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    pokemart PowerItemsShop
    goto EventScript_EndMart
    end

.align 1
PowerItemsShop:
    .hword ITEM_POWER_WEIGHT
    .hword ITEM_POWER_BRACER
    .hword ITEM_POWER_BELT
    .hword ITEM_POWER_LENS
    .hword ITEM_POWER_BAND
    .hword ITEM_POWER_ANKLET
    .hword ITEM_NONE

.global EventScript_TsarvosaCity_StatsDojo_PowerItemScientist
EventScript_TsarvosaCity_StatsDojo_PowerItemScientist:  
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemResearchIntro MSG_NORMAL
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    compare 0x409D 0x2 @ Shop Level
    if notequal _goto PowerItemsNotUnlockedYet
    copyvar 0x4000 0x409E @ Power Items level
    addvar 0x4000 0x1 @ For display
    buffernumber 0x0 0x4000
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsResearchLevel MSG_NORMAL
    compare 0x409E 0x2
    if lessthan _call PowerItemsCanBeImproved
    if equal _call PowerItemsAtMaxLevel
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsEVAssessmentQuestion MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToAssess
    goto AssessPokemonsEVs
    end

PowerItemsNotUnlockedYet:
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsNotUnlockedYet MSG_NORMAL
    end

PowerItemsCanBeImproved:
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsCanBeStrengthenedFurther MSG_NORMAL
    return

PowerItemsAtMaxLevel:
    msgbox gText_TsarvosaCity_StatsDojo_PowerItemsAtMaxLevel MSG_NORMAL
    return

AssessPokemonsEVs:
    msgbox gText_TsarvosaCity_StatsDojo_ChooseAPokemonToAssessEVsFor MSG_NORMAL
    call ChoosePokemon
    callasm CalculateEVTotal
    compare LASTRESULT 100
    if lessthan _goto EVAssessmentVeryPoor
    compare LASTRESULT 200
    if lessthan _goto EVAssessmentPoor
    compare LASTRESULT 300
    if lessthan _goto EVAssessmentGood
    compare LASTRESULT 400
    if lessthan _goto EVAssessmentGreat
    compare LASTRESULT 509
    if lessthan _goto EVAssessmentExcellent
    @ At 510, full
    fanfare 0x10C @ Big Celebration
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentExcellent MSG_NORMAL
    waitfanfare
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentFullFollowUp MSG_NORMAL
    goto AskToAssessMore

ChoosePokemon:
    special 0x9F @ Select a Pokemon and store it's position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if user backed out
    if greaterorequal _goto ChoseNotToAssess
    bufferpartypokemon 0x0 0x8004
    callasm StoreIsPartyMonEgg
    compare LASTRESULT TRUE
    if TRUE _goto ChoseAnEgg
    return

ChoseAnEgg:
    msgbox gText_TsarvosaCity_StatsDojo_ChoseAnEgg MSG_NORMAL
    goto AssessPokemonsEVs

EVAssessmentVeryPoor:
    fanfare 0x10F @ Big Failure
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentVeryPoor MSG_NORMAL
    waitfanfare
    goto AskToAssessMore

EVAssessmentPoor:
    fanfare 0x10F @ Big Failure
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentPoor MSG_NORMAL
    waitfanfare
    goto AskToAssessMore

EVAssessmentGood:
    fanfare 0x10E @ Small Failure
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentGood MSG_NORMAL
    waitfanfare
    goto AskToAssessMore

EVAssessmentGreat:
    fanfare 0x13E @ Obtain Item
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentGreat MSG_NORMAL
    waitfanfare
    goto AskToAssessMore

EVAssessmentExcellent:
    fanfare 0x10D @ Celebration
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentExcellent MSG_NORMAL
    waitfanfare
    goto AskToAssessMore

AskToAssessMore:
    msgbox gText_TsarvosaCity_StatsDojo_EVAssessmentAgainQuestion MSG_YESNO
    compare LASTRESULT YES
    if equal _goto AssessPokemonsEVs
    goto ChoseNotToAssess

ChoseNotToAssess:
    msgbox gText_TsarvosaCity_StatsDojo_NotAssessing MSG_NORMAL
    end

.global EventScript_TsarvosaCity_StatsDojo_IVMaxingScientist
EventScript_TsarvosaCity_StatsDojo_IVMaxingScientist:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_Intro MSG_NORMAL
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    compare 0x409F 0x0 @ IV Maxer Level 1
    if equal _goto CannotMaximizeIVs
    compare 0x409F 0x2 @ IV Maxer Level 3
    if lessthan _call IVMaxerNotFullyInvested
    if equal _call IVMaxerFullyInvested
    goto AskToMaximizeAPokemonsStats

AskToMaximizeAPokemonsStats:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ProceedWithServicesConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToMax
    goto ChoosePokemonToMaxIVsOf

ChoosePokemonToMaxIVsOf:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_PokemonChoice MSG_NORMAL
    call ChoosePokemon
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_PokemonChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoosePokemonToMaxIVsOf
    compare 0x409F 0x1 @ IV Maxer Level 2
    if equal _goto ResearchLevel2Services
    goto ResearchLevel3Services

ResearchLevel2Services:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ResearchLevel2Services MSG_NORMAL
    callasm StoreBottleCapCount
	buffernumber 0x0 0x8005 @ Take stored Bottlecap count
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_BottlecapChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoosePokemonToMaxIVsOf
    checkitem ITEM_BOTTLE_CAP 0x1
    compare LASTRESULT TRUE
    if TRUE _goto ChooseStatToMaximize
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_InsufficientCaps MSG_NORMAL
    end

ResearchLevel3Services:
    callasm StoreBottleCapCount
	buffernumber 0x0 0x8005 @ Take stored Bottlecap count
    callasm StoreGoldBottleCapCount
	buffernumber 0x1 0x8005 @ Take stored Gold Bottlecap count
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ResearchLevel3Services MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_StatsDojo_IVMaxingScientist_Choice_BottleCap 0
	multichoiceoption gText_TsarvosaCity_StatsDojo_IVMaxingScientist_Choice_GoldBottleCap 1
    multichoiceoption gText_TsarvosaCity_StatsDojo_IVMaxingScientist_Choice_ChangedMind 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, ChooseStatToMaximize
	case 1, MaximizeAllIVs
    case 2, ResearchLevel3Services
	case 0xF, ResearchLevel3Services
	goto ResearchLevel3Services

ChooseStatToMaximize:
    checkitem ITEM_BOTTLE_CAP 0x1
    compare LASTRESULT TRUE
    if FALSE _goto InsufficentCaps
    callasm CheckIfAllIVsAreMaxed
    compare LASTRESULT 186 @ Perfect IVs
    if equal _goto AllIVsAreAlreadyMaxed
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_StatChoiceQuestion MSG_KEEPOPEN
    setvar 0x8003 0x0 @ Check IVs from party
    @ var 0x8004 represents the party slot
    setvar 0x8005 0x0 @ Check HP
    call SetHpText
    setvar 0x8005 0x1 @ Check Attack
    call SetAttackText
    setvar 0x8005 0x2 @ Check Defense
    call SetDefenseText
    setvar 0x8005 0x4 @ Check Special Attack
    call SetSpecialAttackText
    setvar 0x8005 0x5 @ Check Special Defense
    call SetSpecialDefenseText
    setvar 0x8005 0x3 @ Check Speed
    call SetSpeedText
    multichoiceoption gText_TsarvosaCity_StatsDojo_IVMaxingScientist_Choice_ChangedMind 6
    multichoice 0x0 0x0 SEVEN_MULTICHOICE_OPTIONS FALSE
    copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
    case 0, MaxHPConfirmation
	case 1, MaxAttackConfirmation
    case 2, MaxDefenseConfirmation
    case 3, MaxSpecialAttackConfirmation
    case 4, MaxSpecialDefenseConfirmation
    case 5, MaxSpeedConfirmation
    case 6, ChoseNotToMax
	case 0xF, ChoseNotToMax
    goto ChoseNotToMax

MaxHPConfirmation:
    bufferstring 0x0 gText_Common_StatHP
    setvar 0x8005 0x0
    goto Maximize1IV

MaxAttackConfirmation:
    bufferstring 0x0 gText_Common_StatAttack
    setvar 0x8005 0x1
    goto Maximize1IV

MaxDefenseConfirmation:
    bufferstring 0x0 gText_Common_StatDefense
    setvar 0x8005 0x2
    goto Maximize1IV

MaxSpecialAttackConfirmation:
    bufferstring 0x0 gText_Common_StatSpecialAttack
    setvar 0x8005 0x4
    goto Maximize1IV

MaxSpecialDefenseConfirmation:
    bufferstring 0x0 gText_Common_StatSpecialDefense
    setvar 0x8005 0x5
    goto Maximize1IV

MaxSpeedConfirmation:
    bufferstring 0x0 gText_Common_StatSpeed
    setvar 0x8005 0x3
    goto Maximize1IV

Maximize1IV:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _goto IVIsAlreadyMaxed
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ChosenStatConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChooseStatToMaximize
    setvar 0x8006 31
    special 0x10 @ Maximize the chosen IV
    removeitem ITEM_BOTTLE_CAP 0x1
    sound 0x30 @Save
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_StatIsMaxedOut MSG_KEEPOPEN
    goto AskToMaximizeAPokemonsStats

MaximizeAllIVs:
    checkitem ITEM_GOLD_BOTTLE_CAP 0x1
    compare LASTRESULT TRUE
    if FALSE _goto InsufficentCaps
    callasm CheckIfAllIVsAreMaxed
    compare LASTRESULT 186 @ Perfect IVs
    if equal _goto AllIVsAreAlreadyMaxed
    bufferpartypokemon 0x0 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_AllStatsConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ResearchLevel3Services
    setvar 0x8006 31 @ Maxing IVs
    setvar 0x8005 0x0 @ HP
    special 0x10 @ Maximize the chosen IV
    setvar 0x8005 0x1 @ Attack
    special 0x10 @ Maximize the chosen IV
    setvar 0x8005 0x2 @ Defense
    special 0x10 @ Maximize the chosen IV
    setvar 0x8005 0x3 @ Speed
    special 0x10 @ Maximize the chosen IV
    setvar 0x8005 0x4 @ Special Attack
    special 0x10 @ Maximize the chosen IV
    setvar 0x8005 0x5 @ Special Defense
    special 0x10 @ Maximize the chosen IV
    removeitem ITEM_GOLD_BOTTLE_CAP 0x1
    sound 0x30 @Save
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_AllStatsAreMaxedOut MSG_KEEPOPEN
    goto AskToMaximizeAPokemonsStats

IVIsAlreadyMaxed:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ChosenStatIsAlreadyMaxed MSG_NORMAL
    goto ChooseStatToMaximize

AllIVsAreAlreadyMaxed:
    bufferpartypokemon 0x0 0x8004
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_AllStatsArelreadyMaxed MSG_NORMAL
    goto ChoosePokemonToMaxIVsOf

CannotMaximizeIVs:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_NoInvestment MSG_NORMAL
    end

InsufficentCaps:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_InsufficientCaps MSG_NORMAL
    end

IVMaxerNotFullyInvested:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_NotFullyInvested MSG_NORMAL
    return

IVMaxerFullyInvested:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_FullyInvested MSG_NORMAL
    return

SetHpText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call HPMaxed
    if notequal _call HPNotMaxed
    return

HPMaxed:
    multichoiceoption gText_Common_StatHPMaxed 0
    return

HPNotMaxed:
    multichoiceoption gText_Common_StatHP 0
    return

SetAttackText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call AttackMaxed
    if notequal _call AttackNotMaxed
    return

AttackMaxed:
    multichoiceoption gText_Common_StatAttackMaxed 1
    return

AttackNotMaxed:
    multichoiceoption gText_Common_StatAttack 1
    return

SetDefenseText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call DefenseMaxed
    if notequal _call DefenseNotMaxed
    return

DefenseMaxed:
    multichoiceoption gText_Common_StatDefenseMaxed 2
    return

DefenseNotMaxed:
    multichoiceoption gText_Common_StatDefense 2
    return

SetSpecialAttackText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call SpecialAttackMaxed
    if notequal _call SpecialAttackNotMaxed
    return

SpecialAttackMaxed:
    multichoiceoption gText_Common_StatSpecialAttackMaxed 3
    return

SpecialAttackNotMaxed:
    multichoiceoption gText_Common_StatSpecialAttack 3
    return

SetSpecialDefenseText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call SpecialDefenseMaxed
    if notequal _call SpecialDefenseNotMaxed
    return

SpecialDefenseMaxed:
    multichoiceoption gText_Common_StatSpecialDefenseMaxed 4
    return

SpecialDefenseNotMaxed:
    multichoiceoption gText_Common_StatSpecialDefense 4
    return

SetSpeedText:
    special2 LASTRESULT 0x8
    compare LASTRESULT 31
    if equal _call SpeedMaxed
    if notequal _call SpeedNotMaxed
    return

SpeedMaxed:
    multichoiceoption gText_Common_StatSpeedMaxed 5
    return

SpeedNotMaxed:
    multichoiceoption gText_Common_StatSpeed 5
    return

ChoseNotToMax:
    msgbox gText_TsarvosaCity_StatsDojo_IVMaxingScientist_ChoseNotToProceed MSG_NORMAL
    end

.global EventScript_TsarvosaCity_StatsDojo_HPDisciple
EventScript_TsarvosaCity_StatsDojo_HPDisciple:
    bufferstring 0x0 gText_Common_StatHP
    setvar 0x4000 407 @ Level 1 HP trainer
    goto EVDiscipleCommon
    end

.global EventScript_TsarvosaCity_StatsDojo_AttackDisciple
EventScript_TsarvosaCity_StatsDojo_AttackDisciple:
    bufferstring 0x0 gText_Common_StatAttack
    setvar 0x4000 410 @ Level 1 Attack trainer
    goto EVDiscipleCommon
    end

.global EventScript_TsarvosaCity_StatsDojo_DefenseDisciple
EventScript_TsarvosaCity_StatsDojo_DefenseDisciple:
    bufferstring 0x0 gText_Common_StatDefense
    setvar 0x4000 413 @ Level 1 Defense trainer
    goto EVDiscipleCommon
    end

.global EventScript_TsarvosaCity_StatsDojo_SpecialAttackDisciple
EventScript_TsarvosaCity_StatsDojo_SpecialAttackDisciple:
    bufferstring 0x0 gText_Common_StatSpecialAttack
    setvar 0x4000 416 @ Level 1 Special Attack trainer
    goto EVDiscipleCommon
    end

.global EventScript_TsarvosaCity_StatsDojo_SpecialDefenseDisciple
EventScript_TsarvosaCity_StatsDojo_SpecialDefenseDisciple:
    bufferstring 0x0 gText_Common_StatSpecialDefense
    setvar 0x4000 419 @ Level 1 Special Defense trainer
    goto EVDiscipleCommon
    end

.global EventScript_TsarvosaCity_StatsDojo_SpeedDisciple
EventScript_TsarvosaCity_StatsDojo_SpeedDisciple:
    bufferstring 0x0 gText_Common_StatSpeed
    setvar 0x4000 422 @ Level 1 Speed trainer
    goto EVDiscipleCommon
    end

EVDiscipleCommon:
    faceplayer
    lock
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleIntro MSG_NORMAL
    checktrainerflag 406
    if NOT_SET _goto FacilitiesCannotOfferServices
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleEVDisciple
    goto ChooseBattleLevel

ChooseBattleLevel:
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleAccepted MSG_KEEPOPEN
    multichoiceoption gText_Level1 0
    multichoiceoption gText_Level2 1
    multichoiceoption gText_Level3 2
	multichoiceoption gText_ChangeMind 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
	case 0, DoLevel1Battle
    case 1, DoLevel2Battle
    case 2, DoLevel3Battle
	case 3, ChoseNotToBattleEVDisciple
    goto ChoseNotToBattleEVDisciple

DoLevel1Battle:
    buffernumber 0x0 0x1
    copyvar 0x4001 0x4000 @ Stay at the level they're at
    goto DoBattleCommon

DoLevel2Battle:
    compare 0x40A0 0x1 @ Level 2
    if lessthan _goto CannotBattleChosenLevel
    buffernumber 0x0 0x2
    copyvar 0x4001 0x4000
    addvar 0x4001 0x1 @ For level 2
    goto DoBattleCommon

DoLevel3Battle:
    compare 0x40A0 0x2 @ Level 3
    if lessthan _goto CannotBattleChosenLevel
    buffernumber 0x0 0x3
    copyvar 0x4001 0x4000
    addvar 0x4001 0x2 @ For level 3
    goto DoBattleCommon

CannotBattleChosenLevel:
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleLevelChoiceIsTooHigh MSG_NORMAL
    goto ChooseBattleLevel

DoBattleCommon:
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleLevelConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChooseBattleLevel
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleLevelConfirmationYes MSG_NORMAL
    setvar 0x8000 0xFEFE @ Continue lost battles
    setflag 0x90E @ Scale disciple teams
    trainerbattle9 0x0 0x4001 0x0 gText_TsarvosaCity_StatsDojo_EVDiscipleBattlePostBattle gText_TsarvosaCity_StatsDojo_EVDiscipleBattlePostBattle
    setvar 0x8000 0x0 @ Does not continue after lost battles
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call DisableTrainerScalingFlag
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattlePostBattleHealing MSG_NORMAL
    call PlayerHeal
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleAskToBattleAgainSometime MSG_NORMAL
    release
    end

ChoseNotToBattleEVDisciple:
    msgbox gText_TsarvosaCity_StatsDojo_EVDiscipleBattleRejected MSG_NORMAL
    release
    end

.global SignScript_TsarvosaCity_StatsDojo_WallScroll
SignScript_TsarvosaCity_StatsDojo_WallScroll:
    msgbox gText_TsarvosaCity_StatsDojo_WallScroll MSG_SIGN
    end

.global SignScript_TsarvosaCity_StatsDojo_GymPlacard
SignScript_TsarvosaCity_StatsDojo_GymPlacard:
    msgbox gText_TsarvosaCity_StatsDojo_GymPlacard MSG_SIGN
    end

m_AttendantWalksToPlayer: .byte walk_down, walk_down, end_m
m_AttendantReturnsToRegularSpot: .byte walk_right, walk_right, walk_up, look_down, end_m
m_CameraMovesLeft: .byte walk_left, walk_left, walk_left, walk_left, end_m
m_CameraMovesRight: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_CameraMovesDown: .byte walk_down, walk_down, walk_down, end_m
m_CameraMovesUp: .byte walk_up, walk_up, walk_up, end_m

@ NPC Houses
.global EventScript_TsarvosaCity_NPCHouses_MoveTutor
EventScript_TsarvosaCity_NPCHouses_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_TsarvosaCityNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_TsarvosaCityNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Tsarvosa
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_TsarvosaCityNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_TutoringRejected m_LookRight
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_NotEnoughPokeChips m_LookRight
    goto End

.global EventScript_TsarvosaCity_NPCHouses_MoveTutorGirlfriend
EventScript_TsarvosaCity_NPCHouses_MoveTutorGirlfriend:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_TutorGirlfriend m_LookLeft
    end

.global EventScript_TsarvosaCity_NPCHouses_SlowbroGTrade
EventScript_TsarvosaCity_NPCHouses_SlowbroGTrade:
    lock
    faceplayer
    checkflag 0x260
    if SET _goto EventScript_SlowbroGTradeComplete
    msgbox gText_TsarvosaCityNPCHouses_SlowbroTrade_Request MSG_YESNO @ THIS
    compare LASTRESULT NO
    if TRUE _goto EventScript_SlowbroGTradeDeclined
    // Set up vars needed for trade
    setvar 0x8008 12 @ Set Trade #12 (Slowbro-G)
    copyvar 0x8004 0x8008 @ Set expected mon from Trade #12 (Slowbro)
    special2 LASTRESULT 0xFC // Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    msgbox gText_TsarvosaCityNPCHouses_SlowbroTrade_ChoosingPokemon MSG_NORMAL
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto EventScript_SlowbroGTradeDeclined
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto EventScript_SlowbroGTradeWrongPokemon
    msgbox gText_TsarvosaCityNPCHouses_SlowbroTrade_PokemonChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto EventScript_SlowbroGTradeDeclined
    msgbox gText_TsarvosaCityNPCHouses_SlowbroTrade_InitiatingTrade MSG_NORMAL
    call InitiateTrade
    setflag 0x260
    goto EventScript_SlowbroGTradeComplete

EventScript_SlowbroGTradeDeclined:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_SlowbroTrade_Declined m_LookRight
    goto End

EventScript_SlowbroGTradeWrongPokemon:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_SlowbroTrade_WrongPokemon m_LookRight
    goto End

EventScript_SlowbroGTradeComplete:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_SlowbroTrade_Complete m_LookRight
    goto End

.global EventScript_TsarvosaCity_NPCHouses_SlowbroGTradeMother
EventScript_TsarvosaCity_NPCHouses_SlowbroGTradeMother:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_SlowbroTradeMother m_LookUp
    end

.global EventScript_TsarvosaCity_NPCHouses_DevTeamCollin
EventScript_TsarvosaCity_NPCHouses_DevTeamCollin:
    faceplayer
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinIntro MSG_NORMAL
    checkflag 0xE1D @ Battled Collin today
    if SET _goto CollinBattled
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinBattleRequest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleCollin
    call SetupDevTeamBattle
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinPreBattle MSG_NORMAL
    random 2 @ Randomize between + 0 (first team) and + 1 (second team)
    compare LASTRESULT 0
    if equal _call FightCollinTeam1
    if notequal _call FightCollinTeam2
    trainerbattle9 0x1 0x4005 0x100 gText_TsarvosaCityNPCHouses_DevTeam_CollinPostBattle gText_TsarvosaCityNPCHouses_DevTeam_CollinPostBattle
    call PostDevTeamBattle
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinGivesReward MSG_NORMAL
    obtainitem ITEM_POKE_CHIP 0x4000
    setflag 0xE1D
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinHealsTeam MSG_NORMAL
    call PlayerHeal
    goto CollinBattled
    end

CollinBattled:
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinBattled MSG_NORMAL
    goto CollinClosingStatement

ChoseNotToBattleCollin:
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CollinBattleRequestDenied MSG_NORMAL
    goto CollinClosingStatement

FightCollinTeam1:
    setvar 0x4005 425
    return

FightCollinTeam2:
    setvar 0x4005 426
    return

CollinClosingStatement:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_DevTeam_CollinClosing m_LookRight
    end

.global EventScript_TsarvosaCity_NPCHouses_DevTeamCrystal
EventScript_TsarvosaCity_NPCHouses_DevTeamCrystal:
    faceplayer
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalIntro MSG_NORMAL
    checkflag 0xE1E @ Battled Crystal today
    if SET _goto CrystalBattled
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalBattleRequest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleCrystal
    call SetupDevTeamBattle
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalPreBattle MSG_NORMAL
    random 2 @ Randomize between + 0 (first team) and + 1 (second team)
    compare LASTRESULT 0
    if equal _call FightCrystalTeam1
    if notequal _call FightCrystalTeam2
    trainerbattle9 0x1 0x4005 0x100 gText_TsarvosaCityNPCHouses_DevTeam_CrystalPostBattle_PlayerWins gText_TsarvosaCityNPCHouses_DevTeam_CrystalPostBattle_PlayerLoses
    call PostDevTeamBattle
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalGivesReward MSG_NORMAL
    obtainitem ITEM_POKE_CHIP 0x4000
    setflag 0xE1E
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalHealsTeam MSG_NORMAL
    call PlayerHeal
    goto CrystalBattled
    end

CrystalBattled:
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalBattled MSG_NORMAL
    goto CrystalClosingStatement

ChoseNotToBattleCrystal:
    msgbox gText_TsarvosaCityNPCHouses_DevTeam_CrystalBattleRequestDenied MSG_NORMAL
    goto CrystalClosingStatement

FightCrystalTeam1:
    setvar 0x4005 427
    return

FightCrystalTeam2:
    setvar 0x4005 428
    return

CrystalClosingStatement:
    npcchatwithmovement gText_TsarvosaCityNPCHouses_DevTeam_CrystalClosing m_LookLeft
    end

SetupDevTeamBattle:
    call SetupMugshotRival
    setflag 0x90E @ Scale teams
    setvar 0x8000 0xFEFE @ Continue lost battles
    return

PostDevTeamBattle:
    setvar 0x8000 0x0
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call DisableTrainerScalingFlag
    setvar 0x4000 0x1 @ 1 PokeChip reward (loss)
    compare LASTRESULT TRUE
    if notequal _call IncreaseDevTeamReward
    return

IncreaseDevTeamReward:
    setvar 0x4000 0x5 @ 5 PokeChip reward
    return

@ Gym Trainee Cafe
.equ TraineeMoveChoice, 0x40A2

.global MapScript_GymTraineeCafe
MapScript_GymTraineeCafe:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_GymTraineeCafe_RotateTrainers
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_GymTraineeCafe_AttendantCutscene
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_GymTraineeCafe_RotateTrainers:
    setflag 0x91D @ Disable saving while inside the Gym Trainee Cafe, to prevent weirdness when loading a save there
    checkflag 0xE1F @ Trainees have been rotated today
    if SET _goto End
    @ Clear all trainer flags
    cleartrainerflag 429 @ Noam
    cleartrainerflag 430 @ Ashley
    cleartrainerflag 431 @ Chelsea
    cleartrainerflag 432 @ Buddy
    cleartrainerflag 433 @ Gawain
    cleartrainerflag 434 @ Skylar
    cleartrainerflag 435 @ Bella
    cleartrainerflag 436 @ Flash
    cleartrainerflag 437 @ Terra
    cleartrainerflag 438 @ Seifa
    cleartrainerflag 439 @ Rocco
    cleartrainerflag 440 @ Janice
    cleartrainerflag 441 @ Antoinette
    cleartrainerflag 442 @ Ryu
    cleartrainerflag 443 @ Caspar
    cleartrainerflag 444 @ Darcy
    cleartrainerflag 445 @ Mason
    cleartrainerflag 446 @ Faye
    random 3
    copyvar TraineeMoveChoice LASTRESULT
    callasm InitializeGymTraineesCafe
    setflag 0xE1F @ Trainees have been rotated today
    end

LevelScripts_GymTraineeCafe_AttendantCutscene:
    levelscript 0x405F 0x0 LevelScript_CafeAttendantWelcomesPlayer
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_CafeAttendantWelcomesPlayer:
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Attendant m_Surprise
    waitmovement Attendant
    msgbox gText_TsarvosaCity_GymTraineeCafe_AttendantSpotsPlayer MSG_NORMAL
    applymovement Attendant m_CafeAttendantWalksToPlayer
    waitmovement Attendant
    msgbox gText_TsarvosaCity_GymTraineeCafe_AttendantExplainsServices MSG_NORMAL
    applymovement Attendant m_CafeAttendnatReturnsToPosition
    waitmovement Attendant
    setvar 0x405F 0x1 @ Prevent the event from playing again
    end

.global EventScript_TsarvosaCity_GymTraineeCafe_Attendant
EventScript_TsarvosaCity_GymTraineeCafe_Attendant:
    npcchatwithmovement gText_TsarvosaCity_GymTraineeCafe_AttendantExplainsServices m_LookDown
    end

.global EventScript_TsarvosaCity_GymTraineeCafe_Noam
EventScript_TsarvosaCity_GymTraineeCafe_Noam:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeNoam
    bufferstring 0x1 gText_Common_TypeNormal
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeNoam_TrainedUnder
    setvar 0x4000 429
    setvar 0x4001 ITEM_SILK_SCARF
    setvar 0x4002 ITEM_NORMAL_GEM
    setvar 0x4003 ITEM_CHILAN_BERRY
    faceplayer
    checktrainerflag 429
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeNormal @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorNormal1
    case 1, TutorNormal2
    case 2, TutorNormal3
    end

TutorNormal1:
    setvar 0x8005 73
    bufferattack 0x2 MOVE_ASSIST
    goto TutorPokemon

TutorNormal2:
    setvar 0x8005 74
    bufferattack 0x2 MOVE_SECRETPOWER
    goto TutorPokemon

TutorNormal3:
    setvar 0x8005 75
    bufferattack 0x2 MOVE_PAYDAY
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Ashley
EventScript_TsarvosaCity_GymTraineeCafe_Ashley:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeAshley
    bufferstring 0x1 gText_Common_TypeFire
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeAshley_TrainedUnder
    setvar 0x4000 430
    setvar 0x4001 ITEM_CHARCOAL
    setvar 0x4002 ITEM_FIRE_GEM
    setvar 0x4003 ITEM_OCCA_BERRY
    faceplayer
    checktrainerflag 430
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeFire @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorFire1
    case 1, TutorFire2
    case 2, TutorFire3
    end

TutorFire1:
    setvar 0x8005 76
    bufferattack 0x2 MOVE_FIREFANG
    goto TutorPokemon

TutorFire2:
    setvar 0x8005 77
    bufferattack 0x2 MOVE_MYSTICALFIRE
    goto TutorPokemon

TutorFire3:
    setvar 0x8005 78
    bufferattack 0x2 MOVE_INCINERATE
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Chelsea
EventScript_TsarvosaCity_GymTraineeCafe_Chelsea:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeChelsea
    bufferstring 0x1 gText_Common_TypeWater
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeChelsea_TrainedUnder
    setvar 0x4000 431
    setvar 0x4001 ITEM_MYSTIC_WATER
    setvar 0x4002 ITEM_WATER_GEM
    setvar 0x4003 ITEM_PASSHO_BERRY
    faceplayer
    checktrainerflag 431
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeWater @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorWater1
    case 1, TutorWater2
    case 2, TutorWater3
    end

TutorWater1:
    setvar 0x8005 79
    bufferattack 0x2 MOVE_AQUARING
    goto TutorPokemon

TutorWater2:
    setvar 0x8005 80
    bufferattack 0x2 MOVE_BRINE
    goto TutorPokemon

TutorWater3:
    setvar 0x8005 81
    bufferattack 0x2 MOVE_RAZORSHELL
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Buddy
EventScript_TsarvosaCity_GymTraineeCafe_Buddy:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeBuddy
    bufferstring 0x1 gText_Common_TypeGrass
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeBuddy_TrainedUnder
    setvar 0x4000 432
    setvar 0x4001 ITEM_MIRACLE_SEED
    setvar 0x4002 ITEM_GRASS_GEM
    setvar 0x4003 ITEM_RINDO_BERRY
    faceplayer
    checktrainerflag 432
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeGrass @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorGrass1
    case 1, TutorGrass2
    case 2, TutorGrass3
    end

TutorGrass1:
    setvar 0x8005 85
    bufferattack 0x2 MOVE_COTTONSPORE
    goto TutorPokemon

TutorGrass2:
    setvar 0x8005 86
    bufferattack 0x2 MOVE_FORESTSCURSE
    goto TutorPokemon

TutorGrass3:
    setvar 0x8005 87
    bufferattack 0x2 MOVE_MEGADRAIN
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Gawain
EventScript_TsarvosaCity_GymTraineeCafe_Gawain:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeGawain
    bufferstring 0x1 gText_Common_TypeFighting
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeGawain_TrainedUnder
    setvar 0x4000 433
    setvar 0x4001 ITEM_BLACK_BELT
    setvar 0x4002 ITEM_FIGHTING_GEM
    setvar 0x4003 ITEM_CHOPLE_BERRY
    faceplayer
    checktrainerflag 433
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeFighting @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorFighting1
    case 1, TutorFighting2
    case 2, TutorFighting3
    end

TutorFighting1:
    setvar 0x8005 91
    bufferattack 0x2 MOVE_KARATECHOP
    goto TutorPokemon

TutorFighting2:
    setvar 0x8005 92
    bufferattack 0x2 MOVE_AURASPHERE
    goto TutorPokemon

TutorFighting3:
    setvar 0x8005 93
    bufferattack 0x2 MOVE_STORMTHROW
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Skylar
EventScript_TsarvosaCity_GymTraineeCafe_Skylar:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeSkylar
    bufferstring 0x1 gText_Common_TypeFlying
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeSkylar_TrainedUnder
    setvar 0x4000 434
    setvar 0x4001 ITEM_SHARP_BEAK
    setvar 0x4002 ITEM_FLYING_GEM
    setvar 0x4003 ITEM_COBA_BERRY
    faceplayer
    checktrainerflag 434
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeFlying @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorFlying1
    case 1, TutorFlying2
    case 2, TutorFlying3
    end

TutorFlying1:
    setvar 0x8005 100
    bufferattack 0x2 MOVE_CHATTER
    goto TutorPokemon

TutorFlying2:
    setvar 0x8005 101
    bufferattack 0x2 MOVE_DUALWINGBEAT
    goto TutorPokemon

TutorFlying3:
    setvar 0x8005 102
    bufferattack 0x2 MOVE_SKYDROP
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Bella
EventScript_TsarvosaCity_GymTraineeCafe_Bella:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeBella
    bufferstring 0x1 gText_Common_TypePoison
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeBella_TrainedUnder
    setvar 0x4000 435
    setvar 0x4001 ITEM_POISON_BARB
    setvar 0x4002 ITEM_POISON_GEM
    setvar 0x4003 ITEM_KEBIA_BERRY
    faceplayer
    checktrainerflag 435
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypePoison @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorPoison1
    case 1, TutorPoison2
    case 2, TutorPoison3
    end

TutorPoison1:
    setvar 0x8005 94
    bufferattack 0x2 MOVE_SLUDGE
    goto TutorPokemon

TutorPoison2:
    setvar 0x8005 95
    bufferattack 0x2 MOVE_ACIDSPRAY
    goto TutorPokemon

TutorPoison3:
    setvar 0x8005 96
    bufferattack 0x2 MOVE_COIL
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Flash
EventScript_TsarvosaCity_GymTraineeCafe_Flash:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeFlash
    bufferstring 0x1 gText_Common_TypeElectric
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeFlash_TrainedUnder
    setvar 0x4000 436
    setvar 0x4001 ITEM_MAGNET
    setvar 0x4002 ITEM_ELECTRIC_GEM
    setvar 0x4003 ITEM_WACAN_BERRY
    faceplayer
    checktrainerflag 436
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeElectric @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorElectric1
    case 1, TutorElectric2
    case 2, TutorElectric3
    end

TutorElectric1:
    setvar 0x8005 82
    bufferattack 0x2 MOVE_SPARK
    goto TutorPokemon

TutorElectric2:
    setvar 0x8005 83
    bufferattack 0x2 MOVE_SHOCKWAVE
    goto TutorPokemon

TutorElectric3:
    setvar 0x8005 84
    bufferattack 0x2 MOVE_PARABOLICCHARGE
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Terra
EventScript_TsarvosaCity_GymTraineeCafe_Terra:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeTerra
    bufferstring 0x1 gText_Common_TypeGround
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeTerra_TrainedUnder
    setvar 0x4000 437
    setvar 0x4001 ITEM_SOFT_SAND
    setvar 0x4002 ITEM_GROUND_GEM
    setvar 0x4003 ITEM_SHUCA_BERRY
    faceplayer
    checktrainerflag 437
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeGround @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorGround1
    case 1, TutorGround2
    case 2, TutorGround3
    end

TutorGround1:
    setvar 0x8005 97
    bufferattack 0x2 MOVE_MUDSHOT
    goto TutorPokemon

TutorGround2:
    setvar 0x8005 98
    bufferattack 0x2 MOVE_SPIKES
    goto TutorPokemon

TutorGround3:
    setvar 0x8005 99
    bufferattack 0x2 MOVE_MAGNITUDE
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Seifa
EventScript_TsarvosaCity_GymTraineeCafe_Seifa:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeSeifa
    bufferstring 0x1 gText_Common_TypePsychic
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeSeifa_TrainedUnder
    setvar 0x4000 438
    setvar 0x4001 ITEM_TWISTED_SPOON
    setvar 0x4002 ITEM_PSYCHIC_GEM
    setvar 0x4003 ITEM_PAYAPA_BERRY
    faceplayer
    checktrainerflag 438
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypePsychic @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorPsychic1
    case 1, TutorPsychic2
    case 2, TutorPsychic3
    end

TutorPsychic1:
    setvar 0x8005 103
    bufferattack 0x2 MOVE_HEALBLOCK
    goto TutorPokemon

TutorPsychic2:
    setvar 0x8005 104
    bufferattack 0x2 MOVE_PSYWAVE
    goto TutorPokemon

TutorPsychic3:
    setvar 0x8005 105
    bufferattack 0x2 MOVE_MAGICPOWDER
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Rocco
EventScript_TsarvosaCity_GymTraineeCafe_Rocco:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeRocco
    bufferstring 0x1 gText_Common_TypeRock
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeRocco_TrainedUnder
    setvar 0x4000 439
    setvar 0x4001 ITEM_HARD_STONE
    setvar 0x4002 ITEM_ROCK_GEM
    setvar 0x4003 ITEM_CHARTI_BERRY
    faceplayer
    checktrainerflag 439
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeRock @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorRock1
    case 1, TutorRock2
    case 2, TutorRock3
    end

TutorRock1:
    setvar 0x8005 109
    bufferattack 0x2 MOVE_ROLLOUT
    goto TutorPokemon

TutorRock2:
    setvar 0x8005 110
    bufferattack 0x2 MOVE_WIDEGUARD
    goto TutorPokemon

TutorRock3:
    setvar 0x8005 111
    bufferattack 0x2 MOVE_ANCIENTPOWER
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Janice
EventScript_TsarvosaCity_GymTraineeCafe_Janice:
    lock
    textcolor RED
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeJanice
    bufferstring 0x1 gText_Common_TypeIce
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeJanice_TrainedUnder
    setvar 0x4000 440
    setvar 0x4001 ITEM_NEVER_MELT_ICE
    setvar 0x4002 ITEM_ICE_GEM
    setvar 0x4003 ITEM_YACHE_BERRY
    faceplayer
    checktrainerflag 440
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeIce @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorIce1
    case 1, TutorIce2
    case 2, TutorIce3
    end

TutorIce1:
    setvar 0x8005 88
    bufferattack 0x2 MOVE_ICESHARD
    goto TutorPokemon

TutorIce2:
    setvar 0x8005 89
    bufferattack 0x2 MOVE_FREEZEDRY
    goto TutorPokemon

TutorIce3:
    setvar 0x8005 90
    bufferattack 0x2 MOVE_AURORABEAM
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Antoinette
EventScript_TsarvosaCity_GymTraineeCafe_Antoinette:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeAntoinette
    bufferstring 0x1 gText_Common_TypeBug
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeAntoinette_TrainedUnder
    setvar 0x4000 441
    setvar 0x4001 ITEM_SILVER_POWDER
    setvar 0x4002 ITEM_BUG_GEM
    setvar 0x4003 ITEM_TANGA_BERRY
    faceplayer
    checktrainerflag 441
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeBug @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorBug1
    case 1, TutorBug2
    case 2, TutorBug3
    end

TutorBug1:
    setvar 0x8005 106
    bufferattack 0x2 MOVE_FURYCUTTER
    goto TutorPokemon

TutorBug2:
    setvar 0x8005 107
    bufferattack 0x2 MOVE_FELLSTINGER
    goto TutorPokemon

TutorBug3:
    setvar 0x8005 108
    bufferattack 0x2 MOVE_RAGEPOWDER
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Ryu
EventScript_TsarvosaCity_GymTraineeCafe_Ryu:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeRyu
    bufferstring 0x1 gText_Common_TypeDragon
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeRyu_TrainedUnder
    setvar 0x4000 442
    setvar 0x4001 ITEM_DRAGON_FANG
    setvar 0x4002 ITEM_DRAGON_GEM
    setvar 0x4003 ITEM_HABAN_BERRY
    faceplayer
    checktrainerflag 442
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeDragon @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorDragon1
    case 1, TutorDragon2
    case 2, TutorDragon3
    end

TutorDragon1:
    setvar 0x8005 115
    bufferattack 0x2 MOVE_BREAKINGSWIPE
    goto TutorPokemon

TutorDragon2:
    setvar 0x8005 116
    bufferattack 0x2 MOVE_SCALESHOT
    goto TutorPokemon

TutorDragon3:
    setvar 0x8005 117
    bufferattack 0x2 MOVE_DRAGONRUSH
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Caspar
EventScript_TsarvosaCity_GymTraineeCafe_Caspar:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeCaspar
    bufferstring 0x1 gText_Common_TypeGhost
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeCaspar_TrainedUnder
    setvar 0x4000 443
    setvar 0x4001 ITEM_SPELL_TAG
    setvar 0x4002 ITEM_GHOST_GEM
    setvar 0x4003 ITEM_KASIB_BERRY
    faceplayer
    checktrainerflag 443
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeGhost @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorGhost1
    case 1, TutorGhost2
    case 2, TutorGhost3
    end

TutorGhost1:
    setvar 0x8005 112
    bufferattack 0x2 MOVE_DESTINYBOND
    goto TutorPokemon

TutorGhost2:
    setvar 0x8005 113
    bufferattack 0x2 MOVE_SHADOWSNEAK
    goto TutorPokemon

TutorGhost3:
    setvar 0x8005 114
    bufferattack 0x2 MOVE_GRUDGE
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Darcy
EventScript_TsarvosaCity_GymTraineeCafe_Darcy:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeDarcy
    bufferstring 0x1 gText_Common_TypeDark
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeDarcy_TrainedUnder
    setvar 0x4000 444
    setvar 0x4001 ITEM_BLACK_GLASSES
    setvar 0x4002 ITEM_DARK_GEM
    setvar 0x4003 ITEM_COLBUR_BERRY
    faceplayer
    checktrainerflag 444
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeDark @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorDark1
    case 1, TutorDark2
    case 2, TutorDark3
    end

TutorDark1:
    setvar 0x8005 118
    bufferattack 0x2 MOVE_FAKETEARS
    goto TutorPokemon

TutorDark2:
    setvar 0x8005 119
    bufferattack 0x2 MOVE_SUCKERPUNCH
    goto TutorPokemon

TutorDark3:
    setvar 0x8005 120
    bufferattack 0x2 MOVE_PURSUIT
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Mason
EventScript_TsarvosaCity_GymTraineeCafe_Mason:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeMason
    bufferstring 0x1 gText_Common_TypeSteel
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeMason_TrainedUnder
    setvar 0x4000 445
    setvar 0x4001 ITEM_METAL_COAT
    setvar 0x4002 ITEM_STEEL_GEM
    setvar 0x4003 ITEM_BABIRI_BERRY
    faceplayer
    checktrainerflag 445
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeSteel @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorSteel1
    case 1, TutorSteel2
    case 2, TutorSteel3
    end

TutorSteel1:
    setvar 0x8005 121
    bufferattack 0x2 MOVE_AUTOTOMIZE
    goto TutorPokemon

TutorSteel2:
    setvar 0x8005 122
    bufferattack 0x2 MOVE_METALBURST
    goto TutorPokemon

TutorSteel3:
    setvar 0x8005 123
    bufferattack 0x2 MOVE_GYROBALL
    goto TutorPokemon

.global EventScript_TsarvosaCity_GymTraineeCafe_Faye
EventScript_TsarvosaCity_GymTraineeCafe_Faye:
    lock
    bufferstring 0x0 gText_TsarvosaCity_GymTraineeCafe_TraineeFaye
    bufferstring 0x1 gText_Common_TypeFairy
    bufferstring 0x2 gText_TsarvosaCity_GymTraineeCafe_TraineeFaye_TrainedUnder
    setvar 0x4000 446
    setvar 0x4001 ITEM_PIXIE_PLATE
    setvar 0x4002 ITEM_FAIRY_GEM
    setvar 0x4003 ITEM_ROSELI_BERRY
    faceplayer
    checktrainerflag 446
    if NOT_SET _call BattleGymTrainee
    bufferstring 0x1 gText_Common_TypeFairy @ Gets reset if tutoring right after battle
    switch TraineeMoveChoice
    case 0, TutorFairy1
    case 1, TutorFairy2
    case 2, TutorFairy3
    end

TutorFairy1:
    setvar 0x8005 124
    bufferattack 0x2 MOVE_CRAFTYSHIELD
    goto TutorPokemon

TutorFairy2:
    setvar 0x8005 125
    bufferattack 0x2 MOVE_DRAININGKISS
    goto TutorPokemon

TutorFairy3:
    setvar 0x8005 126
    bufferattack 0x2 MOVE_SPIRITBREAK
    goto TutorPokemon

BattleGymTrainee:
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_Intro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleTrainee
    setvar 0x8000 0xFEFE @ Continue lost battles
    setflag 0x90E @ Scale gym trainee teams
    call SetupMugshotRival
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_PreBattle MSG_NORMAL
    trainerbattle9 0x0 0x4000 0x100 gText_TsarvosaCity_GymTraineeCafe_Trainee_BattleWon gText_TsarvosaCity_GymTraineeCafe_Trainee_BattleLost
    setvar 0x8000 0x0 @ Does not continue after lost battles    
    checkflag 0x4FF @ Trainer level scaling modifier
    if NOT_SET _call DisableTrainerScalingFlag
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_PostBattleHeal MSG_NORMAL
    call PlayerHeal
    compare LASTRESULT TRUE
    if equal _goto LostToTrainee
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_WonAgainstTrainee MSG_NORMAL
    obtainitem 0x4001 0x1
    pause DELAY_HALFSECOND
    obtainitem 0x4002 0x1
    pause DELAY_HALFSECOND
    obtainitem 0x4003 0x3
    return

ChoseNotToBattleTrainee:
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_ChoseNotToBattle MSG_NORMAL
    end

LostToTrainee:
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_LostToTrainee MSG_NORMAL
    end

TutorPokemon:
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_OfferingMove MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToTutor
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_ChoosePokemonPrompt MSG_NORMAL
    special 0x18D
    waitstate
    compare LASTRESULT YES
    if false _goto ChoseNotToTutor @ Pokemon couldn't learn move, or player cancelled
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_OfferingToTeachMore MSG_NORMAL
    end

ChoseNotToTutor:
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_ChoseNotToTutor MSG_NORMAL
    msgbox gText_TsarvosaCity_GymTraineeCafe_Trainee_LeavingAtEndOfDay MSG_NORMAL
    end

m_CafeAttendantWalksToPlayer: .byte walk_down, walk_down, end_m
m_CafeAttendnatReturnsToPosition: .byte walk_up, walk_up, look_down, end_m

.global EventScript_TsarvosaCity_NPCHouses_PokeChipCrusher
EventScript_TsarvosaCity_NPCHouses_PokeChipCrusher:
    faceplayer
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherIntro MSG_KEEPOPEN
    setvar 0x8000 0xE @ Pokechip crusher
    setvar 0x8001 0x5
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, MaxRevive
	case 1, PPMax
	case 2, RareCandy
	case 3, BottleCap
    case 4, AbilityCapsule
	case 5, AbilityPatch
	case 6, GoldBottleCap
	case 7, MasterBall
    case 8, ChoseNotToCrush
    case 0x7F, ChoseNotToCrush @ When player hit B to close
    goto ChoseNotToCrush

MaxRevive:
    setvar 0x4000 ITEM_MAX_REVIVE
    bufferitem 0x0 ITEM_MAX_REVIVE
    setvar 0x4001 5
    buffernumber 0x1 5
    goto CrushingConfirmation

PPMax:
    setvar 0x4000 ITEM_PP_MAX
    bufferitem 0x0 ITEM_PP_MAX
    setvar 0x4001 10
    buffernumber 0x1 10
    goto CrushingConfirmation

RareCandy:
    setvar 0x4000 ITEM_RARE_CANDY
    bufferitem 0x0 ITEM_RARE_CANDY
    setvar 0x4001 10
    buffernumber 0x1 10
    goto CrushingConfirmation

BottleCap:
    setvar 0x4000 ITEM_BOTTLE_CAP
    bufferitem 0x0 ITEM_BOTTLE_CAP
    setvar 0x4001 15
    buffernumber 0x1 15
    goto CrushingConfirmation

AbilityCapsule:
    setvar 0x4000 ITEM_ABILITY_CAPSULE
    bufferitem 0x0 ITEM_ABILITY_CAPSULE
    setvar 0x4001 15
    buffernumber 0x1 15
    goto CrushingConfirmation

AbilityPatch:
    setvar 0x4000 ITEM_ABILITY_PATCH
    bufferitem 0x0 ITEM_ABILITY_PATCH
    setvar 0x4001 25
    buffernumber 0x1 25
    goto CrushingConfirmation

GoldBottleCap:
    setvar 0x4000 ITEM_GOLD_BOTTLE_CAP
    bufferitem 0x0 ITEM_GOLD_BOTTLE_CAP
    setvar 0x4001 35
    buffernumber 0x1 35
    goto CrushingConfirmation

MasterBall:
    setvar 0x4000 ITEM_MASTER_BALL
    bufferitem 0x0 ITEM_MASTER_BALL
    setvar 0x4001 50
    buffernumber 0x1 50
    goto CrushingConfirmation

CrushingConfirmation:
    callasm StorePokeChipCount
    buffernumber 0x2 0x8005 @ Take stored PokeChip count
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemConfirmationQuestion MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToCrush
    comparevars 0x8005 0x4001
    if lessthan _goto NotEnoughPokeChipsToCrush
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemConfirmationMade MSG_NORMAL
    fadescreen FADEOUT_BLACK
    playse 0x17 @ Pokeball shake
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemCrushing1 MSG_NORMAL
	waitse
    playse 0x17 @ Pokeball shake
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemCrushing2 MSG_NORMAL
	waitse
    playse 0x7C @ Rock Smash
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemCrushing3 MSG_NORMAL
	waitse
    fadescreen FADEIN_BLACK
    fanfare 0x101 @ Level Up
    msgbox gText_TsarvosaCity_NPCHouses_PokeCrusherItemCrushingComplete MSG_NORMAL
    waitfanfare
    obtainitem 0x4000 0x1
    removeitem ITEM_POKE_CHIP 0x4001
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_PokeCrusherItemComeAgain m_LookLeft
    end

NotEnoughPokeChipsToCrush:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_PokeCrusherNotEnoughChips m_LookLeft
    end

ChoseNotToCrush:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_PokeCrusherDeclined m_LookLeft
    end

.global EventScript_TsarvosaCity_NPCHouses_PokeChipCrusherFriend
EventScript_TsarvosaCity_NPCHouses_PokeChipCrusherFriend:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_PokeCrusherFriend m_LookRight
    end

.global EventScript_TsarvosaCity_NPCHouses_MarketBoy
EventScript_TsarvosaCity_NPCHouses_MarketBoy:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_MarketBoy m_LookRight
    end

.global EventScript_TsarvosaCity_NPCHouses_WildernessGirl
EventScript_TsarvosaCity_NPCHouses_WildernessGirl:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_WildnernessGirl m_LookUp
    end

.global EventScript_TsarvosaCity_NPCHouses_IrisAndStellaMom
EventScript_TsarvosaCity_NPCHouses_IrisAndStellaMom:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_IrisAndStellaMom m_LookLeft
    end

.global EventScript_TsarvosaCity_NPCHouses_IrisAndStellaGrandpa
EventScript_TsarvosaCity_NPCHouses_IrisAndStellaGrandpa:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_IrisAndStellaGrandpa m_LookUp
    end

.global EventScript_TsarvosaCity_NPCHouses_IrisFanClubPresident
EventScript_TsarvosaCity_NPCHouses_IrisFanClubPresident:
    faceplayer
    checkflag 0x261 @ Received Flame Orb
    if SET _goto ReceivedFlameOrb
    msgbox gText_TsarvosaCity_NPCHouses_IrisFanClubPresident MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PresidentChoseNo
    msgbox gText_TsarvosaCity_NPCHouses_IrisFanClubPresident_Yes MSG_NORMAL
    obtainitem ITEM_FLAME_ORB 0x1
    setflag 0x261 @ Received Flame Orb
    goto ReceivedFlameOrb

ReceivedFlameOrb:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_IrisFanClubPresident_FlameOrbComment m_LookLeft
    end

PresidentChoseNo:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_IrisFanClubPresident_No m_LookLeft
    end

.global EventScript_TsarvosaCity_NPCHouses_HoennGirl
EventScript_TsarvosaCity_NPCHouses_HoennGirl:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_HoennGirl m_LookRight
    end

.global EventScript_TsarvosaCity_NPCHouses_HoennBoy
EventScript_TsarvosaCity_NPCHouses_HoennBoy:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_HoennBoy m_LookLeft
    end

.global EventScript_TsarvosaCity_NPCHouses_BattlingFanGirl
EventScript_TsarvosaCity_NPCHouses_BattlingFanGirl:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_BattlingFanGirl m_LookRight
    end

.global EventScript_TsarvosaCity_NPCHouses_BattlingFanBoy
EventScript_TsarvosaCity_NPCHouses_BattlingFanBoy:
    npcchatwithmovement gText_TsarvosaCity_NPCHouses_BattlingFanBoy m_LookLeft
    end

@ Gym
.equ VarGymChallengeProgress, 0x4060
.equ GymTrainer, 28

.global EventScript_TsarvosaCity_Gym_Attendant
EventScript_TsarvosaCity_Gym_Attendant:
    checkflag 0x826 @ Tsarvosa gym badge
    if SET _goto SignScript_TsarvosaCity_Gym_AttendantPostVictory
    npcchat gText_TsarvosaCity_Gym_Attendant
    end

SignScript_TsarvosaCity_Gym_AttendantPostVictory:
    npcchat gText_TsarvosaCity_Gym_AttendantPostVictory
    end

.global EventScript_TsarvosaCity_Gym_Merchant1
EventScript_TsarvosaCity_Gym_Merchant1:
    call MerchantShopIntro
    pokemart HeldItemsShop2
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant2
EventScript_TsarvosaCity_Gym_Merchant2:
    call MerchantShopIntro
    pokemart SpecialXItemsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant3
EventScript_TsarvosaCity_Gym_Merchant3:
    call MerchantShopIntro
    pokemart SeedsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant4
EventScript_TsarvosaCity_Gym_Merchant4:
    call MerchantShopIntro
    pokemart HealingItemsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant5
EventScript_TsarvosaCity_Gym_Merchant5:
    call MerchantShopIntro
    pokemart RepelsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant6
EventScript_TsarvosaCity_Gym_Merchant6:
    call MerchantShopIntro
    pokemart HeldItemsShop4
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant7
EventScript_TsarvosaCity_Gym_Merchant7:
    call MerchantShopIntro
    pokemart BitterItemsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant8
EventScript_TsarvosaCity_Gym_Merchant8:
    call MerchantShopIntro
    pokemart BerryShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant9
EventScript_TsarvosaCity_Gym_Merchant9:
    call MerchantShopIntro
    pokemart PokeBallShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant10
EventScript_TsarvosaCity_Gym_Merchant10:
    call MerchantShopIntro
    pokemart PhysicalXItemsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant11
EventScript_TsarvosaCity_Gym_Merchant11:
    call MerchantShopIntro
    pokemart HerbsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant12
EventScript_TsarvosaCity_Gym_Merchant12:
    call MerchantShopIntro
    pokemart HeldItemsShop1
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant13
EventScript_TsarvosaCity_Gym_Merchant13:
    call MerchantShopIntro
    pokemart PPItemsShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant14
EventScript_TsarvosaCity_Gym_Merchant14:
    call MerchantShopIntro
    pokemart HeldItemsShop3
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant15
EventScript_TsarvosaCity_Gym_Merchant15:
    call MerchantShopIntro
    pokemart RocksShop
    call MerchantShopOutro
    end

.global EventScript_TsarvosaCity_Gym_Merchant16
EventScript_TsarvosaCity_Gym_Merchant16:
    call MerchantShopIntro
    pokemart DrinksShop
    call MerchantShopOutro
    end

MerchantShopIntro:
    msgbox gText_TsarvosaCity_Gym_MerchantIntro MSG_KEEPOPEN
    return

MerchantShopOutro:
    msgbox gText_TsarvosaCity_Gym_MerchantOutro MSG_NORMAL
    return

.align 1
PokeBallShop:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_NONE

.align 1
RepelsShop:
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_MAX_REPEL
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
PPItemsShop:
    .hword ITEM_ETHER
    .hword ITEM_ELIXIR
    .hword ITEM_REVIVE
    .hword ITEM_NONE

.align 1
HealingItemsShop:
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_NONE

.align 1
PhysicalXItemsShop:
    .hword ITEM_X_ATTACK
    .hword ITEM_X_DEFEND
    .hword ITEM_X_SPEED
    .hword ITEM_NONE

.align 1
SpecialXItemsShop:
    .hword ITEM_X_SP_ATK
    .hword ITEM_X_SP_DEF
    .hword ITEM_X_ACCURACY
    .hword ITEM_NONE

.align 1
BitterItemsShop:
    .hword ITEM_ENERGY_POWDER
    .hword ITEM_ENERGY_ROOT
    .hword ITEM_HEAL_POWDER
    .hword ITEM_REVIVAL_HERB
    .hword ITEM_NONE

.align 1 
SeedsShop:
    .hword ITEM_GRASSY_SEED
    .hword ITEM_ELECTRIC_SEED
    .hword ITEM_MISTY_SEED
    .hword ITEM_PSYCHIC_SEED
    .hword ITEM_NONE

.align 1
HerbsShop:
    .hword ITEM_WHITE_HERB
    .hword ITEM_MENTAL_HERB
    .hword ITEM_POWER_HERB
    .hword ITEM_NONE

.align 1
BerryShop:
    .hword ITEM_ORAN_BERRY
    .hword ITEM_CHERI_BERRY
    .hword ITEM_PECHA_BERRY
    .hword ITEM_CHESTO_BERRY
    .hword ITEM_RAWST_BERRY
    .hword ITEM_ASPEAR_BERRY
    .hword ITEM_LEPPA_BERRY
    .hword ITEM_SITRUS_BERRY
    .hword ITEM_NONE

.align 1
DrinksShop:
    .hword ITEM_FRESH_WATER
    .hword ITEM_LEMONADE
    .hword ITEM_MOOMOO_MILK
    .hword ITEM_NONE

.align 1
RocksShop:
    .hword ITEM_ICY_ROCK
    .hword ITEM_HEAT_ROCK
    .hword ITEM_DAMP_ROCK
    .hword ITEM_SMOOTH_ROCK
    .hword ITEM_NONE

.align 1
HeldItemsShop1:
    .hword ITEM_ROCKY_HELMET
    .hword ITEM_RED_CARD
    .hword ITEM_AIR_BALLOON
    .hword ITEM_CELL_BATTERY
    .hword ITEM_ABSORB_BULB
    .hword ITEM_SNOWBALL
    .hword ITEM_NONE

.align 1
HeldItemsShop2:
    .hword ITEM_TERRAIN_EXTENDER
    .hword ITEM_BLACK_SLUDGE
    .hword ITEM_LIGHT_CLAY
    .hword ITEM_WIDE_LENS
    .hword ITEM_QUICK_CLAW
    .hword ITEM_NONE

.align 1
HeldItemsShop3:
    .hword ITEM_EJECT_BUTTON
    .hword ITEM_BIG_ROOT
    .hword ITEM_BRIGHT_POWDER
    .hword ITEM_TOXIC_ORB
    .hword ITEM_FLAME_ORB
    .hword ITEM_NONE

.align 1
HeldItemsShop4:
    .hword ITEM_STICKY_BARB
    .hword ITEM_IRON_BALL
    .hword ITEM_LAGGING_TAIL
    .hword ITEM_SHED_SHELL
    .hword ITEM_HEAVY_DUTY_BOOTS
    .hword ITEM_NONE

.global EventScript_TsarvosaCity_Gym_LeaderIris
EventScript_TsarvosaCity_Gym_LeaderIris:
    faceplayer
    checkflag 0x826 @ Tsarvosa City gym badge obtained
    if SET _goto EventScript_TsarvosaCity_Gym_LeaderIris_Chat
    buffernumber 0x0 VarGymChallengeProgress
    switch VarGymChallengeProgress
    case 1, GymChallenge1
    case 2, GymChallenge2
    case 3, GymChallenge3
    case 4, GymChallenge4
    case 5, GymChallenge5
    case 6, GymChallenge6
    case 7, GymChallenge7  @ This is a joke question asking who your favorite gym leader is, with all options being Iris and being correct.
    case 8, GymChallengeBattleIris
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallengeIntroduction MSG_NORMAL
    setvar VarGymChallengeProgress 0x1
    goto TsarvosaGymChallengeRules
    end

@ Common Gym Logic
TsarvosaGymChallengeStarting:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Starting MSG_NORMAL
    return

TsarvosaGymChallengeRules:
    npcchatwithmovement gText_TsarvosaCity_Gym_Iris_GymChallengeRules m_LookDown
    end

TsarvosaGymChallengeChoseNotToTakeNextQuestion:
    npcchatwithmovement gText_TsarvosaCity_Gym_Iris_GymChallenge_NotReadyForQuestion m_LookDown
    end

GymChallengeQuestionSetupCommon:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_NextChallengeQuestion MSG_KEEPOPEN
    multichoiceoption gText_Yes 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_RulesMenuChoice 1
	multichoiceoption gText_No 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, TsarvosaGymChallengeStarting _call
	case 1, TsarvosaGymChallengeRules
	case 2, TsarvosaGymChallengeChoseNotToTakeNextQuestion
    case 0x7F, TsarvosaGymChallengeChoseNotToTakeNextQuestion @ When player hit B to close
    return

GymChallengeTriggerStart:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_QuestionTimer MSG_NORMAL
    npcchatwithmovement gText_TsarvosaCity_Gym_Iris_GymChallenge_IrisStartsTheClock m_LookDown
    call GymChallengeNowActiveCommon
    return

GymChallengeNowActiveCommon:
    setflag 0x262 @ Gym Challenge active
    setflag 0x91D @ Hide Save option
    setvar 0x4000 0x1 @ Tile events are active
    playbgm 0x113 @ Gym Challenge
    special 0x46 @ Timer start
    return

GymChallengeDeactivatedCommon:
    clearflag 0x262 @ Gym Challenge inactive
    clearflag 0x91D @ Show Save option
    setvar 0x4000 0x0 @ Tile events are inactive
    special 0x49 @ Timer stop
    return

GymChallengeHandleWhenRemainingTime:
    @ Calculate how much time the player has left
    special2 0x4004 0x4A
    copyvar 0x4003 0x8010
    setvar 0x8004 0x4003
    setvar 0x8005 0x4004
    special2 LASTRESULT 0x3F
    @ Present it to them
    buffernumber 0x1 0x4003
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_TimerValue MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToAnswer
    return

GymChallengeHandleRanOutOfTime:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_RanOutOfTime MSG_NORMAL
    call GymChallengeMustBattle
    return

GymChallengeMustBattle:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_MustBattle MSG_NORMAL
    return

AnswerWasIncorrect:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ConfirmingAnswerLeadIn MSG_NORMAL
    fanfare 0x10F @ Failure
    applymovement LASTTALKED m_Wrong
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_GivenAnswerWasIncorrect MSG_NORMAL
    waitfanfare
    call GymChallengeMustBattle
    return

AnswerWasCorrect:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ConfirmingAnswerLeadIn MSG_NORMAL
    fanfare 0x10D @ Celebration
    applymovement LASTTALKED m_Joy
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_GivenAnswerWasCorrect MSG_NORMAL
    waitfanfare
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ItemReward MSG_NORMAL
    obtainitem 0x4002 0x1
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AskToBattle MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToBattleOptionalTrainer
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ChoseToBattle MSG_NORMAL
    return

ChoseNotToAnswer:
    npcchatwithmovement gText_TsarvosaCity_Gym_Iris_GymChallenge_ChoseNotToAnswer m_LookDown
    end

ChoseNotToBattleOptionalTrainer:
    call GymChallengeDeactivatedCommon
    fadedefaultbgm
    npcchatwithmovement gText_TsarvosaCity_Gym_Iris_GymChallenge_ChoseNotToBattle m_LookDown
    addvar VarGymChallengeProgress 0x1
    end

HandlePreGymBattle:
    special 0xAF @ Dismount bike if on it
    applymovement LASTTALKED m_LookDown
    getplayerpos 0x4005 0x4006
    compare 0x4006 0xB @ Above
    if equal _call PlayerWalkLeft_Return
    waitmovement PLAYER
    getplayerpos 0x4005 0x4006
    compare 0x4005 0x24
    if equal _call PlayerWalkDown_Return
    compare 0x4005 0x26
    if equal _call PlayerWalkDown_Return
    waitmovement PLAYER
    compare 0x4006 0xB
    if equal _call PlayerWalkDown_Return
    getplayerpos 0x4005 0x4006
    compare 0x4005 0x25
    if lessthan _call PlayerWalkRight_Return
    if greaterthan _call PlayerWalkLeft_Return
    waitmovement PLAYER
    applymovement PLAYER m_LookDown
    showsprite GymTrainer
    applymovement GymTrainer m_OpponentWalksToPlayer
    waitmovement GymTrainer
    playbgm 342 @ Encounter Ace Trainer
    call GymChallengeDeactivatedCommon @ Reset states in case the player loses to the trainer
    return

HandlePostGymBattle:
    applymovement GymTrainer m_OpponentLeaves
    waitmovement GymTrainer
    hidesprite GymTrainer
    applymovement PLAYER m_LookUp
    fadedefaultbgm
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_PlayerClearedBattle MSG_NORMAL
    addvar VarGymChallengeProgress 0x1
    return

@ Challenge specific logic
GymChallenge1:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge1AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1 MSG_NORMAL
    buffernumber 0x0 180
    call GymChallengeTriggerStart
    end

GymChallenge1AnswerConfirmation:
    setvar 0x8010 180
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge1RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_LEMONADE
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question1Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasIncorrect _call
	case 2, AnswerWasIncorrect _call
    case 3, AnswerWasCorrect _call
    goto BattlingGymTrainer1

GymChallenge1RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer1

BattlingGymTrainer1:
    setvar 0x5029 31
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Marci_Intro MSG_NORMAL
    trainerbattle3 0x1 447 0x0 gText_TsarvosaCity_Gym_Marci_Defeat
    msgbox gText_TsarvosaCity_Gym_Marci_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge2:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge2AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2 MSG_NORMAL
    buffernumber 0x0 150
    call GymChallengeTriggerStart
    end

GymChallenge2AnswerConfirmation:
    setvar 0x8010 150
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge2RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_HYPER_POTION
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question2Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasCorrect _call
	case 2, AnswerWasIncorrect _call
    case 3, AnswerWasIncorrect _call
    goto BattlingGymTrainer2

GymChallenge2RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer2

BattlingGymTrainer2:
    setvar 0x5029 58
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Jamila_Intro MSG_NORMAL
    trainerbattle3 0x1 448 0x0 gText_TsarvosaCity_Gym_Jamila_Defeat
    msgbox gText_TsarvosaCity_Gym_Jamila_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge3:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge3AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3 MSG_NORMAL
    buffernumber 0x0 120
    call GymChallengeTriggerStart
    end

GymChallenge3AnswerConfirmation:
    setvar 0x8010 120
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge3RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_REVIVE
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question3Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
    copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasIncorrect _call
	case 2, AnswerWasCorrect _call
    case 3, AnswerWasIncorrect _call
    goto BattlingGymTrainer3

GymChallenge3RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer3

BattlingGymTrainer3:
    setvar 0x5029 47
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Norbert_Intro MSG_NORMAL
    trainerbattle3 0x1 449 0x0 gText_TsarvosaCity_Gym_Norbert_Defeat
    msgbox gText_TsarvosaCity_Gym_Norbert_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge4:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge4AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4 MSG_NORMAL
    buffernumber 0x0 90
    call GymChallengeTriggerStart
    end

GymChallenge4AnswerConfirmation:
    setvar 0x8010 90
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge4RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_MAX_POTION
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question4Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasCorrect _call
	case 2, AnswerWasIncorrect _call
    case 3, AnswerWasIncorrect _call
    goto BattlingGymTrainer4

GymChallenge4RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer4

BattlingGymTrainer4:
    setvar 0x5029 27
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Marion_Intro MSG_NORMAL
    trainerbattle3 0x1 450 0x0 gText_TsarvosaCity_Gym_Marion_Defeat
    msgbox gText_TsarvosaCity_Gym_Marion_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge5:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge5AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5 MSG_NORMAL
    buffernumber 0x0 60
    call GymChallengeTriggerStart
    end

GymChallenge5AnswerConfirmation:
    setvar 0x8010 60
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge5RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_FULL_RESTORE
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question5Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasCorrect _call
	case 2, AnswerWasIncorrect _call
    case 3, AnswerWasIncorrect _call
    goto BattlingGymTrainer5

GymChallenge5RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer5

BattlingGymTrainer5:
    setvar 0x5029 22
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Alanah_Intro MSG_NORMAL
    trainerbattle3 0x1 451 0x0 gText_TsarvosaCity_Gym_Alanah_Defeat
    msgbox gText_TsarvosaCity_Gym_Alanah_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge6:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge6AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6 MSG_NORMAL
    buffernumber 0x0 45
    call GymChallengeTriggerStart
    end

GymChallenge6AnswerConfirmation:
    setvar 0x8010 45
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _goto GymChallenge6RanOutOfTime
    call GymChallengeHandleWhenRemainingTime
    @ This is the start of less generic logic
    setvar 0x4002 ITEM_MAX_REVIVE
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6Choice1 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6Choice2 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6Choice3 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question6Choice4 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, AnswerWasIncorrect _call
	case 1, AnswerWasIncorrect _call
	case 2, AnswerWasCorrect _call
    case 3, AnswerWasIncorrect _call
    goto BattlingGymTrainer6

GymChallenge6RanOutOfTime:
    call GymChallengeHandleRanOutOfTime
    goto BattlingGymTrainer6

BattlingGymTrainer6:
    setvar 0x5029 61
    call HandlePreGymBattle
    msgbox gText_TsarvosaCity_Gym_Paul_Intro MSG_NORMAL
    trainerbattle3 0x1 452 0x0 gText_TsarvosaCity_Gym_Paul_Defeat
    msgbox gText_TsarvosaCity_Gym_Paul_Chat MSG_NORMAL
    call HandlePostGymBattle
    end

GymChallenge7:
    checkflag 0x262 @ Gym Challenge active
    if SET _goto GymChallenge7AnswerConfirmation
    call GymChallengeQuestionSetupCommon
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7 MSG_NORMAL
    buffernumber 0x0 10
    call GymChallengeTriggerStart
    end

GymChallenge7AnswerConfirmation:
    setvar 0x8010 10
    special2 0x4004 0x4D @ Handle if player has passed the time limit in var 8010
    compare 0x4004 TRUE
    if equal _call GymChallenge7RanOutOfTime
    if notequal _call GymChallengeHandleWhenRemainingTime
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_AnswerLeadIn MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7 MSG_KEEPOPEN
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7ChoiceAll 0
	multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7ChoiceAll 1
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7ChoiceAll 2
    multichoiceoption gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7ChoiceAll 3
    multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, GymChallenge7JokeAnswerIsCorrect
	case 1, GymChallenge7JokeAnswerIsCorrect
	case 2, GymChallenge7JokeAnswerIsCorrect
    case 3, GymChallenge7JokeAnswerIsCorrect
    end

GymChallenge7JokeAnswerIsCorrect:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ConfirmingAnswerLeadIn MSG_NORMAL
    fanfare 0x10D @ Celebration
    applymovement LASTTALKED m_Joy
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_GivenAnswerWasCorrect MSG_NORMAL
    waitfanfare
    call GymChallengeDeactivatedCommon
    fadedefaultbgm
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_ReadyForBadgeBattle MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    addvar VarGymChallengeProgress 0x1
    end

GymChallenge7RanOutOfTime:
    msgbox gText_TsarvosaCity_Gym_Iris_GymChallenge_Question7TimesUpPrompt MSG_NORMAL
    return

GymChallengeBattleIris:
    msgbox gText_TsarvosaCity_Gym_LeaderIris_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 453 0x100 gText_TsarvosaCity_Gym_LeaderIris_Intro gText_TsarvosaCity_Gym_LeaderIris_Defeat EventScript_TsarvosaCity_Gym_LeaderIris_Defeated
    end

EventScript_TsarvosaCity_Gym_LeaderIris_Defeated:
    msgbox gText_TsarvosaCity_Gym_LeaderIris_BadgeAwarded MSG_NORMAL
    setflag 0x826 @ Tsarvosa City gym badge
    setflag 0x4B6 @ Defeated Iris
    setflag 0x25C @ New Pokemart Stock
    clearflag 0x04F @ Enable Iris & Stella battle in Daimyn City restaurant
    fanfare 0x13D @ Gym victory
    msgbox gText_TsarvosaCity_Gym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    msgbox gText_TsarvosaCity_Gym_LeaderIris_BadgeDescription MSG_NORMAL
    msgbox gText_TsarvosaCity_Gym_LeaderIris_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_TsarvosaCity_Gym_TMReceived
    additem ITEM_TM21 0x1
    giveitemwithfanfare ITEM_TM21 0x1 0x101 @ MUS_FANFA1
    goto EventScript_TsarvosaCity_Gym_LeaderIris_Chat
    end

EventScript_TsarvosaCity_Gym_LeaderIris_Chat:
    msgbox gText_TsarvosaCity_Gym_LeaderIris_Chat MSG_NORMAL
    checkflag 0x04F
    if NOT_SET _goto IrisCommentsOnLunchWithStella
    applymovement LASTTALKED m_LookDown
    end

IrisCommentsOnLunchWithStella:
    npcchatwithmovement gText_TsarvosaCity_Gym_LeaderIris_CommentOnStellaLunch m_LookDown
    end

.global TileScript_TsarvosaCity_Gym_BarricadeSouth
TileScript_TsarvosaCity_Gym_BarricadeSouth:
    call GymBarricadeCommon
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    release
    end

.global TileScript_TsarvosaCity_Gym_BarricadeWest
TileScript_TsarvosaCity_Gym_BarricadeWest:
    call GymBarricadeCommon
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    release
    end

GymBarricadeCommon:
    checkflag 0x262 @ Gym Challenge active
    if NOT_SET _goto End
    lock
    msgbox gText_TsarvosaCity_Gym_GymChallengeActiveCannotLeave MSG_NORMAL
    return

.global SignScript_TsarvosaCity_Gym_GymSign
SignScript_TsarvosaCity_Gym_GymSign:
    msgbox gText_TsarvosaCity_Gym_GymSign MSG_SIGN
    end

.global SignScript_TsarvosaCity_Gym_GymVictorsSign
SignScript_TsarvosaCity_Gym_GymVictorsSign:
    checkflag 0x826 @ Tsarvosa gym badge
    if SET _goto SignScript_TsarvosaCity_Gym_GymVictorsSignPostVictory
    msgbox gText_TsarvosaCity_Gym_GymVictorsSignPreVictory MSG_SIGN
    end

SignScript_TsarvosaCity_Gym_GymVictorsSignPostVictory:
    msgbox gText_TsarvosaCity_Gym_GymVictorsSignPostVictory MSG_SIGN
    end

m_OpponentWalksToPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_OpponentLeaves: .byte walk_down, walk_down, walk_down, walk_down, walk_down, end_m
