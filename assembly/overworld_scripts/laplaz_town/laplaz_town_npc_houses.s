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
