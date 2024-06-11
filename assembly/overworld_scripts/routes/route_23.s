.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route23
MapScript_Route23:
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

HideTrapPokemon:
    checkflag 0xE1B
    if SET _call HidePalossand1
    checkflag 0xE1C
    if SET _call HidePalossand2
    end

HidePalossand1:
    hidesprite 21
    return

HidePalossand2:
    hidesprite 22
    return

.global EventScript_Route23_TM24Thunderbolt
EventScript_Route23_TM24Thunderbolt:
    setvar CHOSEN_ITEM ITEM_TM24
    call ItemScript_Common_FindTM
    end

.global EventScript_Route23_TM15HyperBeam
EventScript_Route23_TM15HyperBeam:
    setvar CHOSEN_ITEM ITEM_TM15
    call ItemScript_Common_FindTM
    end

.global EventScript_Route23_BirdKeeperTyrone
EventScript_Route23_BirdKeeperTyrone:
    trainerbattle0 0x0 369 0x0 gText_Route23_BirdKeeperTyrone_Intro gText_Route23_BirdKeeperTyrone_Defeat
    msgbox gText_Route23_BirdKeeperTyrone_Chat MSG_NORMAL
    end

.global EventScript_Route23_GamblerGordon
EventScript_Route23_GamblerGordon:
    trainerbattle0 0x0 370 0x0 gText_Route23_GamblerGordon_Intro gText_Route23_GamblerGordon_Defeat
    msgbox gText_Route23_GamblerGordon_Chat MSG_NORMAL
    end

.global EventScript_Route23_SuperNerdEmmett
EventScript_Route23_SuperNerdEmmett:
    trainerbattle0 0x0 371 0x0 gText_Route23_SuperNerdEmmett_Intro gText_Route23_SuperNerdEmmett_Defeat
    msgbox gText_Route23_SuperNerdEmmett_Chat MSG_NORMAL
    end

.global EventScript_Route23_GentlemanRussell
EventScript_Route23_GentlemanRussell:
    trainerbattle0 0x0 372 0x0 gText_Route23_GentlemanRussell_Intro gText_Route23_GentlemanRussell_Defeat
    msgbox gText_Route23_GentlemanRussell_Chat MSG_NORMAL
    end

.global EventScript_Route23_CrushGirlLily
EventScript_Route23_CrushGirlLily:
    trainerbattle0 0x0 373 0x0 gText_Route23_CrushGirlLily_Intro gText_Route23_CrushGirlLily_Defeat
    msgbox gText_Route23_CrushGirlLily_Chat MSG_NORMAL
    end

.global EventScript_Route23_BeautyMiranda
EventScript_Route23_BeautyMiranda:
    trainerbattle0 0x0 374 0x0 gText_Route23_BeautyMiranda_Intro gText_Route23_BeautyMiranda_Defeat
    msgbox gText_Route23_BeautyMiranda_Chat MSG_NORMAL
    end

.global EventScript_Route23_Palossand1
EventScript_Route23_Palossand1:
    lock
    checksound
    cry SPECIES_PALOSSAND 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    setflag 0xE1B
    wildbattle SPECIES_PALOSSAND 52 0x0
    release
    end

.global EventScript_Route23_Palossand2
EventScript_Route23_Palossand2:
    lock
    checksound
    cry SPECIES_PALOSSAND 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    setflag 0xE1C
    wildbattle SPECIES_PALOSSAND 53 0x0
    release
    end

.global EventScript_Route23_RocksMan
EventScript_Route23_RocksMan:
    npcchatwithmovement gText_Route23_RocksMan m_LookLeft
    end

.global SignScript_Route23_TsarvosaAnthraDirections
SignScript_Route23_TsarvosaAnthraDirections:
    msgbox gText_Route23_TsarvosaAnthraDirectionsSign MSG_SIGN
    end

.global SignScript_Route23_FishermanMasterHouse
SignScript_Route23_FishermanMasterHouse:
    msgbox gText_Route23_FishingMastersSign MSG_SIGN
    end

.global SignScript_Route23_TrainerTips
SignScript_Route23_TrainerTips:
    msgbox gText_Route23_TrainerTipsSign MSG_SIGN
    end

.global EventScript_Route23_FishermansHouse_FishermanMaster
EventScript_Route23_FishermansHouse_FishermanMaster:
    faceplayer
    checkflag 0x24C @ Has Super Rod
    if SET _goto SuperRodExplaination
    msgbox gText_Route23_FishermansHouse_Master_PreAssessment MSG_NORMAL
    checkitem ITEM_OLD_ROD 0x1
    compare LASTRESULT TRUE
    if FALSE _goto DoesNotHaveRods
    checkitem ITEM_GOOD_ROD 0x1
    compare LASTRESULT TRUE
    if FALSE _goto DoesNotHaveRods
    msgbox gText_Route23_FishermansHouse_Master_HasOldAndGoodRod MSG_NORMAL
    msgbox gText_Route23_FishermansHouse_Master_Question MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DoesNotLikeFishing
    msgbox gText_Route23_FishermansHouse_Master_QuestionYes MSG_NORMAL
    obtainitem ITEM_SUPER_ROD 0x1
    setflag 0x24C @ Has Super Rod
    goto SuperRodExplaination
    end

DoesNotHaveRods:
    msgbox gText_Route23_FishermansHouse_Master_DoesNotHaveOldAndGoodRod MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    end

DoesNotLikeFishing:
    msgbox gText_Route23_FishermansHouse_Master_QuestionNo MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    end

SuperRodExplaination:
    msgbox gText_Route23_FishermansHouse_Master_SuperRodExplaination MSG_NORMAL
    applymovement LASTTALKED m_LookRight
    end

.global EventScript_Route23_FishermansHouse_FishermanStudentA
EventScript_Route23_FishermansHouse_FishermanStudentA:
    npcchatwithmovement gText_Route23_FishermansHouse_StudentA m_LookUp
    end

.global EventScript_Route23_FishermansHouse_FishermanStudentB
EventScript_Route23_FishermansHouse_FishermanStudentB:
    npcchat gText_Route23_FishermansHouse_StudentB
    end

.global EventScript_Route23_FishermansHouse_FishermanStudent
EventScript_Route23_FishermansHouse_FishermanStudentC:
    npcchat gText_Route23_FishermansHouse_StudentC
    end
