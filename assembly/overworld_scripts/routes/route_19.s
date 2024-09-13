.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route19
MapScript_Route19:
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

HideTrapPokemon:
    checkflag 0xE19
    if SET _call HidePalossand
    end

HidePalossand:
    hidesprite 10
    return

.global EventScript_Route19_LassSamantha
EventScript_Route19_LassSamantha:
    trainerbattle0 0x0 361 0x0 gText_Route19_LassSamantha_Intro gText_Route19_LassSamantha_Defeat
    msgbox gText_Route19_LassSamantha_Chat MSG_NORMAL
    end

.global EventScript_Route19_CoolTrainerRose
EventScript_Route19_CoolTrainerRose:
    trainerbattle0 0x0 362 0x0 gText_Route19_CoolTrainerRose_Intro gText_Route19_CoolTrainerRose_Defeat
    msgbox gText_Route19_CoolTrainerRose_Chat MSG_NORMAL
    end

.global EventScript_Route19_PokefanPhineas
EventScript_Route19_PokefanPhineas:
    // Double battle with Phoebe
    compare PLAYERFACING RIGHT
    if equal _call PhineasAndPhoebeLookLeft
    trainerbattle11 0x0 363 364 5 6 0x0 gText_Route19_PokefanPhineas_Intro gText_Route19_PokefanPhoebe_Intro gText_Route19_PokefanPhineas_Defeat gText_Route19_PokefanPhoebe_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route19_PokefanPhineas_Chat MSG_NORMAL
    end

.global EventScript_Route19_PokefanPhoebe
EventScript_Route19_PokefanPhoebe:
    // Double battle with Phineas
    compare PLAYERFACING LEFT
    if equal _call PhineasAndPhoebeLookRight
    trainerbattle11 0x0 363 364 5 6 0x0 gText_Route19_PokefanPhineas_Intro gText_Route19_PokefanPhoebe_Intro gText_Route19_PokefanPhineas_Defeat gText_Route19_PokefanPhoebe_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route19_PokefanPhoebe_Chat MSG_NORMAL
    end

PhineasAndPhoebeLookRight:
    applymovement 5 m_LookRight
    applymovement 6 m_LookRight
    return

PhineasAndPhoebeLookLeft:
    applymovement 5 m_LookLeft
    applymovement 6 m_LookLeft
    return

.global EventScript_Route19_TM84PoisonJab
EventScript_Route19_TM84PoisonJab:
    setvar CHOSEN_ITEM ITEM_TM84
    call ItemScript_Common_FindTM
    end

.global EventScript_Route19_Palossand
EventScript_Route19_Palossand:
    lock
    checksound
    cry SPECIES_PALOSSAND 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    setflag 0xE19
    wildbattle SPECIES_PALOSSAND 50 0x0
    release
    end

.global SignScript_Route19_LookoutPointSign
SignScript_Route19_LookoutPointSign:
    msgbox gText_Route19_LookoutPoint_Sign MSG_SIGN
    end
