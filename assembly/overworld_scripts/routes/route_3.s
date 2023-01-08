.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global SignScript_Route3_TrainerTips
SignScript_Route3_TrainerTips:
    msgbox gText_Route3_TrainerTips MSG_SIGN
    end

.global SignScript_Route3_Navigation
SignScript_Route3_Navigation:
    msgbox gText_Route3_Navigation MSG_SIGN
    end

.global EventScript_Route3_FindTMTaunt
EventScript_Route3_FindTMTaunt:
    setvar CHOSEN_ITEM ITEM_TM12
    call ItemScript_Common_FindTM
    end
