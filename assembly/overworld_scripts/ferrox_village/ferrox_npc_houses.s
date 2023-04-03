.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_FerroxNPCHouses_SmallestVillage
EventScript_FerroxNPCHouses_SmallestVillage:
    npcchat2 0x1 m_LookRight gText_FerroxNPCHouses_SmallestVillage
    end

.global EventScript_FerroxNPCHouses_DailyBerry
EventScript_FerroxNPCHouses_DailyBerry:
    lock
    faceplayer
    checkflag 0xE06
    if SET _goto BerryGirlEnd
    msgbox gText_FerroxNPCHouses_BerryGirl_FreeBerry MSG_NORMAL
    random 0xA
    addvar LASTRESULT 0x85 @ Cheri Berry to Sitrus Berry
    obtainitem LASTRESULT 0x1 
    setflag 0xE06
    goto BerryGirlEnd

BerryGirlEnd:
    msgbox gText_FerroxNPCHouses_BerryGirl_ComeBackTomorrow MSG_NORMAL
    release
    end

.global EventScript_FerroxNPCHouses_MoveTutor
EventScript_FerroxNPCHouses_MoveTutor:
    lock
    faceplayer
    msgbox gText_FerroxNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_FerroxNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Ferrox
    msgbox gText_FerroxNPCHouses_Complete MSG_NORMAL
    release
    end

TutoringRejected:
    msgbox gText_FerroxNPCHouses_TutoringRejected MSG_NORMAL
    release
    end

NotEnoughPokeChips:
    msgbox gText_FerroxNPCHouses_NotEnoughPokeChips MSG_NORMAL
    release
    end

.global EventScript_FerroxNPCHouses_TutorsInTowns
EventScript_FerroxNPCHouses_TutorsInTowns:
    npcchat gText_FerroxNPCHouses_TutorsInTowns
    end
