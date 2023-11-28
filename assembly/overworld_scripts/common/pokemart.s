.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Pokemart stock is based on Gen 8 SW/SH list
.global EventScript_Pokemart
EventScript_Pokemart:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    checkflag 0x829 @ Has Pokedex
    if NOT_SET _goto EventScript_PokemartNotReady
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    checkflag 0x827 @ Eight Badges
    if SET _goto EventScript_EightBadges
    checkflag 0x826 @ Seven Badges
    if SET _goto EventScript_SevenBadges
    checkflag 0x825 @ Six Badges
    if SET _goto EventScript_SixBadges
    checkflag 0x824 @ Five Badges
    if SET _goto EventScript_FiveBadges
    checkflag 0x823 @ Four Badges
    if SET _goto EventScript_FourBadges
    checkflag 0x822 @ Three Badges
    if SET _goto EventScript_ThreeBadges
    checkflag 0x821 @ Two Badges
    if SET _goto EventScript_TwoBadges
    checkflag 0x820 @ One Badge
    if SET _goto EventScript_OneBadge
    goto EventScript_NoBadges @ No badges

EventScript_NoBadges:
    pokemart NoBadges_Stock
    goto EventScript_EndMart

EventScript_OneBadge:
    pokemart OneBadge_Stock
    goto EventScript_EndMart

EventScript_TwoBadges:
    pokemart TwoBadges_Stock
    goto EventScript_EndMart

EventScript_ThreeBadges:
    pokemart ThreeBadges_Stock
    goto EventScript_EndMart

EventScript_FourBadges:
    pokemart FourBadges_Stock
    goto EventScript_EndMart

EventScript_FiveBadges:
    pokemart FiveBadges_Stock
    goto EventScript_EndMart

EventScript_SixBadges:
    pokemart SixBadges_Stock
    goto EventScript_EndMart

EventScript_SevenBadges:
    pokemart SevenBadges_Stock
    goto EventScript_EndMart

EventScript_EightBadges:
    pokemart EightBadges_Stock
    goto EventScript_EndMart

.align 1
NoBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_POTION
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_NONE

.align 1
OneBadge_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
TwoBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
ThreeBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
FourBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
FiveBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
SixBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
SevenBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_MAX_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_MAX_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
EightBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_MAX_POTION
    .hword ITEM_FULL_RESTORE
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_MAX_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.global EventScript_EndMart    
EventScript_EndMart:
    msgbox gText_Common_PokemartEnd MSG_NORMAL
    textcolor 0xFF @ Reset color to OW default
    goto End

EventScript_PokemartNotReady:
    msgbox gText_Common_PokemartNotReady MSG_NORMAL
    goto End
