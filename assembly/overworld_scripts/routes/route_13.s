.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route13_CharizarditeY
EventScript_Route13_CharizarditeY:
    finditem ITEM_CHARIZARDITE_Y 0x1
    end

.global EventScript_Route13_FindTM39RockTomb
EventScript_Route13_FindTM39RockTomb:
    setvar CHOSEN_ITEM ITEM_TM39
    call ItemScript_Common_FindTM
    end