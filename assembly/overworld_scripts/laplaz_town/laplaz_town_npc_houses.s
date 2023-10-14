.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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
    applymovement LASTTALKED m_LookLeft
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
