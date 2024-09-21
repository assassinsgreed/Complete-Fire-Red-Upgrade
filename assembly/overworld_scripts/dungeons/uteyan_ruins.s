.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_UteyanRuins
MapScript_UteyanRuins:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_UteyanRuins_SetWorldMapFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UteyanRuins_SetWorldMapFlag:
    setworldmapflag 0x8B1 @ Been to Uteyan Ruins
    end

.global EventScript_UteyanRuins_TM04CalmMind
EventScript_UteyanRuins_TM04CalmMind:
    setvar CHOSEN_ITEM ITEM_TM04
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_RuinManiacKristian
EventScript_UteyanRuins_RuinManiacKristian:
    trainerbattle0 0x0 492 0x0 gText_UteyanRuins_RuinManiacKristian_Intro gText_UteyanRuins_RuinManiacKristian_Defeat
    msgbox gText_UteyanRuins_RuinManiacKristian_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_PsychicHaley
EventScript_UteyanRuins_PsychicHaley:
    trainerbattle0 0x0 493 0x0 gText_UteyanRuins_PsychicHaley_Intro gText_UteyanRuins_PsychicHaley_Defeat
    msgbox gText_UteyanRuins_PsychicHaley_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_RuinManiacCyril
EventScript_UteyanRuins_RuinManiacCyril:
    trainerbattle0 0x0 494 0x0 gText_UteyanRuins_RuinManiacCyril_Intro gText_UteyanRuins_RuinManiacCyril_Defeat
    msgbox gText_UteyanRuins_RuinManiacCyril_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_BrailleMan
EventScript_UteyanRuins_BrailleMan:
    @ Later: Uncomment and test this
    @ checkitem ITEM_BRAILLE_DECODER 0x1
    @ if equal _goto BrailleMan_WithDecoder 
    npcchat gText_UteyanRuins_BrailleMan
    setflag 0x279
    end

BrailleMan_WithDecoder:
    npcchat gText_UteyanRuins_BrailleMan_WithDecoder
    end

.global EventScript_UteyanRuins_PuzzleGirl
EventScript_UteyanRuins_PuzzleGirl:
    npcchat gText_UteyanRuins_PuzzleGirl
    end

.global EventScript_UteyanRuins_TM29Psychic
EventScript_UteyanRuins_TM29Psychic:
    setvar CHOSEN_ITEM ITEM_TM29
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_HM06RockClimb
EventScript_UteyanRuins_HM06RockClimb:
    setvar CHOSEN_ITEM ITEM_HM06
    call ItemScript_Common_FindTM
    end

.global EventScript_UteyanRuins_SuperNerdMorty
EventScript_UteyanRuins_SuperNerdMorty:
    trainerbattle0 0x0 495 0x0 gText_UteyanRuins_SuperNerdMorty_Intro gText_UteyanRuins_SuperNerdMorty_Defeat
    msgbox gText_UteyanRuins_SuperNerdMorty_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_ChannelerAgatha
EventScript_UteyanRuins_ChannelerAgatha:
    trainerbattle0 0x0 496 0x0 gText_UteyanRuins_ChannelerAgatha_Intro gText_UteyanRuins_ChannelerAgatha_Defeat
    msgbox gText_UteyanRuins_ChannelerAgatha_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_LassDorothy
EventScript_UteyanRuins_LassDorothy:
    trainerbattle0 0x0 497 0x0 gText_UteyanRuins_LassDorothy_Intro gText_UteyanRuins_LassDorothy_Defeat
    msgbox gText_UteyanRuins_LassDorothy_Chat MSG_NORMAL
    end

.global EventScript_UteyanRuins_Gardevoirite
EventScript_UteyanRuins_Gardevoirite:
    finditem ITEM_GARDEVOIRITE 0x1
    end

.global EventScript_UteyanRuins_SacredAsh
EventScript_UteyanRuins_SacredAsh:
    finditem ITEM_SACRED_ASH 0x1
    end

.global EventScript_UteyanRuins_RedOrb
EventScript_UteyanRuins_RedOrb:
    finditem ITEM_RED_ORB 0x1
    end

.global EventScript_UteyanRuins_BlueOrb
EventScript_UteyanRuins_BlueOrb:
    finditem ITEM_BLUE_ORB 0x1
    end
