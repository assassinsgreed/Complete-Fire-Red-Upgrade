.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global ItemScript_Common_Potion
ItemScript_Common_Potion:
    finditem ITEM_POTION 0x1
    end
