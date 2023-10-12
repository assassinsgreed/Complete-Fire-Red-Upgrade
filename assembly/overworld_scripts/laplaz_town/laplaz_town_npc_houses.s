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
