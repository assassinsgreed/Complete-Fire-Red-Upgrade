.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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
    npcchat2 0x0 m_LookRight gText_HeleoCity_ForemanBadgeComment 
    release
    end

.global EventScript_HeleoCity_ForemanAssistant
EventScript_HeleoCity_ForemanAssistant:
    npcchat gText_HeleoCity_ForemanAssistant
    end

.global EventScript_HeleoCity_MoveTutor
EventScript_HeleoCity_MoveTutor:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_HeleoNPCHouses_ConfirmationAccepted MSG_NORMAL
    call EventScript_Tutors_Heleo
    msgbox gText_HeleoNPCHouses_Complete MSG_NORMAL
    release
    end

TutoringRejected:
    msgbox gText_HeleoNPCHouses_TutoringRejected MSG_NORMAL
    release
    end

NotEnoughPokeChips:
    msgbox gText_HeleoNPCHouses_NotEnoughPokeChips MSG_NORMAL
    release
    end

.global EventScript_HeleoCity_MoveTutorSon
EventScript_HeleoCity_MoveTutorSon:
    npcchat gText_HeleoCity_MoveTutorSon
    end

