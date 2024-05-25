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

@ Pokemon Center
.global MapScript_TsarvosaCity_PokemonCenter
MapScript_TsarvosaCity_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot:
    sethealingplace 0xB
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
    @ TODO in a future ticket: on menu close to reset trainers
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
    addvar 0x409E 0x1 @ Internal number
    addvar 0x4000 0x1 @ Number shown in dialog
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

m_AttendantWalksToPlayer: .byte walk_down, walk_down, end_m
m_AttendantReturnsToRegularSpot: .byte walk_right, walk_right, walk_up, look_down, end_m
m_CameraMovesLeft: .byte walk_left, walk_left, walk_left, walk_left, end_m
m_CameraMovesRight: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_CameraMovesDown: .byte walk_down, walk_down, walk_down, end_m
m_CameraMovesUp: .byte walk_up, walk_up, walk_up, end_m
