.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DaimynCityNPCHouses_SuspiciousMan1
EventScript_DaimynCityNPCHouses_SuspiciousMan1:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan1
    end

.global EventScript_DaimynCityNPCHouses_SuspiciousMan2
EventScript_DaimynCityNPCHouses_SuspiciousMan2:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan2
    end

.global EventScript_DaimynCity_MoveTutor
EventScript_DaimynCity_MoveTutor:
    lock
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_DaimynNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    loadpointer 0x0 gText_DaimynNPCHouses_Complete
    call EventScript_Tutors_Daimyn
    release
    end

TutoringRejected:
    msgbox gText_DaimynNPCHouses_TutoringRejected MSG_NORMAL
    goto End

NotEnoughPokeChips:
    msgbox gText_DaimynNPCHouses_NotEnoughPokeChips MSG_NORMAL
    goto End

.global EventScript_DaimynCityNPCHouses_TutorsDaughter
EventScript_DaimynCityNPCHouses_TutorsDaughter:
    npcchat gText_DaimynCityNPCHouses_TutorsDaughter
    end

.global EventScript_DaimynCityNPCHouses_TutorsSon
EventScript_DaimynCityNPCHouses_TutorsSon:
    npcchat gText_DaimynCityNPCHouses_TutorsSon
    end
