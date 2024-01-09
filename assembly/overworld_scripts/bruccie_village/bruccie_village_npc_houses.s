.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_BruccieVillageNPCHouses_MoveTutor
EventScript_BruccieVillageNPCHouses_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BruccieVillageNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_BruccieVillageNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Bruccie
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookUp
    end

TutoringComplete:
    msgbox gText_BruccieVillageNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_BruccieVillageNPCHouses_TutoringRejected m_LookUp
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_BruccieVillageNPCHouses_NotEnoughPokeChips m_LookUp
    goto End
