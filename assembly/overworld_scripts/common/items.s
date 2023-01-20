.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global ItemScript_Common_FindTM
ItemScript_Common_FindTM:
    @ Expects variable CHOSEN_ITEM to be set to the Item ID
    finditem CHOSEN_ITEM 0x1
    return

.global ItemScript_Common_Potion
ItemScript_Common_Potion:
    finditem ITEM_POTION 0x1
    end

.global ItemScript_Common_Antidote
ItemScript_Common_Antidote:
    finditem ITEM_ANTIDOTE 0x1
    end

.global ItemScript_Common_SodaPop
ItemScript_Common_SodaPop:
    finditem ITEM_SODA_POP 0x1
    end

.global ItemScript_Common_EscapeRope
ItemScript_Common_EscapeRope:
    finditem ITEM_ESCAPE_ROPE 0x1
    end

.global ItemScript_Common_TinyMushroom
ItemScript_Common_TinyMushroom:
    finditem ITEM_TINY_MUSHROOM 0x1
    end

.global ItemScript_Common_StarPiece
ItemScript_Common_StarPiece:
    finditem ITEM_STAR_PIECE 0x1
    end

.global ItemScript_Common_Nugget
ItemScript_Common_Nugget:
    finditem ITEM_NUGGET 0x1
    end

.global ItemScript_Common_MysticWater
ItemScript_Common_MysticWater:
    finditem ITEM_MYSTIC_WATER 0x1
    end

.global ItemScript_Common_SoftSand
ItemScript_Common_SoftSand:
    finditem ITEM_SOFT_SAND 0x1
    end

.global ItemScript_Common_FocusSash
ItemScript_Common_FocusSash:
    finditem ITEM_FOCUS_SASH 0x1
    end

.global ItemScript_Common_ChoiceScarf
ItemScript_Common_ChoiceScarf:
    finditem ITEM_CHOICE_SCARF 0x1
    end

.global ItemScript_Common_Stick
ItemScript_Common_Stick:
    finditem ITEM_STICK 0x1
    end

.global ItemScript_Common_LaxIncense
ItemScript_Common_LaxIncense:
    finditem ITEM_LAX_INCENSE 0x1
    end

.global ItemScript_Common_DireHit
ItemScript_Common_DireHit:
    finditem ITEM_DIRE_HIT 0x1
    end

.global ItemScript_Common_Pokeball
ItemScript_Common_Pokeball:
    finditem ITEM_POKE_BALL 0x1
    end

.global ItemScript_Common_Greatball
ItemScript_Common_Greatball:
    finditem ITEM_GREAT_BALL 0x1
    end
