.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route9_Flutist
EventScript_Route9_Flutist:
    faceplayer
    msgbox gText_Route9_FlutistShopIntroduction MSG_KEEPOPEN
    pokemart FluteShop
    msgbox gText_Route9_FlutistShopThanks MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

FluteShop:
    .hword ITEM_BLUE_FLUTE
    .hword ITEM_YELLOW_FLUTE
    .hword ITEM_RED_FLUTE
    .hword ITEM_BLACK_FLUTE
    .hword ITEM_WHITE_FLUTE
    .hword ITEM_NONE
