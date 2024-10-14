.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Route 21
.global MapScript_Route21
MapScript_Route21:
    mapscript MAP_SCRIPT_ON_LOAD MapLoadScript_Route21_MoveVictoryRoadGuard
    .byte MAP_SCRIPT_TERMIN

MapLoadScript_Route21_MoveVictoryRoadGuard:
    checkflag 0x280 @ Victory Road guard has stepped aside
    if NOT_SET _goto End
    movesprite2 21 0x27 0x6 @ Permanent position
    end

.global EventScript_Route21_TM56_Fling
EventScript_Route21_TM56_Fling:
    setvar CHOSEN_ITEM ITEM_TM56
    call ItemScript_Common_FindTM
    end

.global EventScript_Route21_PokefanWalter
EventScript_Route21_PokefanWalter:
    trainerbattle0 0x0 390 0x0 gText_Route21_PokefanWalter_Intro gText_Route21_PokefanWalter_Defeat
    msgbox gText_Route21_PokefanWalter_Chat MSG_NORMAL
    end

.global EventScript_Route21_CollectorEric
EventScript_Route21_CollectorEric:
    trainerbattle0 0x0 391 0x0 gText_Route21_CollectorEric_Intro gText_Route21_CollectorEric_Defeat
    msgbox gText_Route21_CollectorEric_Chat MSG_NORMAL
    end

.global EventScript_Route21_HikerRicardo
EventScript_Route21_HikerRicardo:
    trainerbattle0 0x0 392 0x0 gText_Route21_HikerRicardo_Intro gText_Route21_HikerRicardo_Defeat
    msgbox gText_Route21_HikerRicardo_Chat MSG_NORMAL
    end

.global EventScript_Route21_DragonTamerTanner
EventScript_Route21_DragonTamerTanner:
    trainerbattle0 0x0 393 0x0 gText_Route21_DragonTamerTanner_Intro gText_Route21_DragonTamerTanner_Defeat
    msgbox gText_Route21_DragonTamerTanner_Chat MSG_NORMAL
    end

.global EventScript_Route21_ParasolLadyKatrina
EventScript_Route21_ParasolLadyKatrina:
    trainerbattle0 0x0 394 0x0 gText_Route21_ParasolLadyKatrina_Intro gText_Route21_ParasolLadyKatrina_Defeat
    msgbox gText_Route21_ParasolLadyKatrina_Chat MSG_NORMAL
    end

.global EventScript_Route21_NinjaBoyIshan
EventScript_Route21_NinjaBoyIshan:
    trainerbattle0 0x0 395 0x0 gText_Route21_NinjaBoyIshan_Intro gText_Route21_NinjaBoyIshan_Defeat
    msgbox gText_Route21_NinjaBoyIshan_Chat MSG_NORMAL
    end

.global EventScript_Route21_RockerAxel
EventScript_Route21_RockerAxel:
    trainerbattle0 0x0 396 0x0 gText_Route21_RockerAxel_Intro gText_Route21_RockerAxel_Defeat
    msgbox gText_Route21_RockerAxel_Chat MSG_NORMAL
    end

.global EventScript_Route21_VictoryRoadGuard
EventScript_Route21_VictoryRoadGuard:
    faceplayer
    msgbox gText_Route21_VictoryRoadGuard MSG_NORMAL
    checkflag 0x27F @ Registered for Victory Road challenge
    if SET _goto CanTakeVictoryRoadChallenge
    playse 0x1A @ Error
    msgbox gText_Route21_VictoryRoadGuard_NotEnoughBadges MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

CanTakeVictoryRoadChallenge:
    fanfare 0x10D @ Celebration
    msgbox gText_Route21_VictoryRoadGuard_HasEnoughBadges MSG_NORMAL
    waitfanfare
    msgbox gText_Route21_VictoryRoadGuard_WishesLuck MSG_NORMAL
    checkflag 0x280 @ Victory Road guard has stepped aside
    if SET _goto End
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x27
    if equal _call PlayerMovesOutOfGuardsWay
    applymovement LASTTALKED m_WalkRight
    waitmovement LASTTALKED
    applymovement LASTTALKED m_LookDown
    movesprite LASTTALKED 0x27 0x6 @ Location while on map
    movesprite2 LASTTALKED 0x27 0x6 @ Permanent position
    setflag 0x280 @ Victory Road guard has stepped aside
    end

PlayerMovesOutOfGuardsWay:
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    return

.global SignScript_Route21_TrainerTips
SignScript_Route21_TrainerTips:
    msgbox gText_Route21_TrainerTips MSG_SIGN
    end

.global SignScript_Route21_VictoryRoad
SignScript_Route21_VictoryRoad:
    msgbox gText_Route21_VictoryRoad MSG_SIGN
    end

// Secret Trail
.global EventScript_SecretTrail_TM77_PsychUp
EventScript_SecretTrail_TM77_PsychUp:
    setvar CHOSEN_ITEM ITEM_TM77
    call ItemScript_Common_FindTM
    end

.global EventScript_SecretTrail_ChannelerHeather
EventScript_SecretTrail_ChannelerHeather:
    trainerbattle0 0x0 397 0x0 gText_SecretTrail_ChannelerHeather_Intro gText_SecretTrail_ChannelerHeather_Defeat
    msgbox gText_SecretTrail_ChannelerHeather_Chat MSG_NORMAL
    end

@ Route 22
.global EventScript_Route22_TM74GyroBall
EventScript_Route22_TM74GyroBall:
    setvar CHOSEN_ITEM ITEM_TM74
    call ItemScript_Common_FindTM
    end

.global EventScript_Route22_TM90Substitute
EventScript_Route22_TM90Substitute:
    setvar CHOSEN_ITEM ITEM_TM90
    call ItemScript_Common_FindTM
    end

.global EventScript_Route22_CoolTrainerGail
EventScript_Route22_CoolTrainerGail:
    trainerbattle0 0x0 385 0x0 gText_Route22_CoolTrainerGail_Intro gText_Route22_CoolTrainerGail_Defeat
    msgbox gText_Route22_CoolTrainerGail_Chat MSG_NORMAL
    end

.global EventScript_Route22_ScientistLarry
EventScript_Route22_ScientistLarry:
    trainerbattle0 0x0 386 0x0 gText_Route22_ScientistLarry_Intro gText_Route22_ScientistLarry_Defeat
    msgbox gText_Route22_ScientistLarry_Chat MSG_NORMAL
    end

.global EventScript_Route22_SrAndJr_Alma
EventScript_Route22_SrAndJr_Alma:
    checktrainerflag 387
    if SET _goto AlmaDefeated
    trainerbattle0 0x0 387 0x0 gText_Route22_SrAndJr_Alma_Intro gText_Route22_SrAndJr_Alma_Defeat
    goto AlmaDefeated
    end

AlmaDefeated:
    npcchatwithmovement gText_Route22_SrAndJr_Alma_Chat m_LookDown
    end

.global EventScript_Route22_SrAndJr_Mai
EventScript_Route22_SrAndJr_Mai:
    checktrainerflag 387
    if SET _goto MaiDefeated
    trainerbattle0 0x0 387 0x0 gText_Route22_SrAndJr_Mai_Intro gText_Route22_SrAndJr_Mai_Defeat
    goto MaiDefeated
    end

MaiDefeated:
    npcchatwithmovement gText_Route22_SrAndJr_Mai_Chat m_LookDown
    end

.global EventScript_Route22_JugglerChauncy
EventScript_Route22_JugglerChauncy:
    trainerbattle0 0x0 388 0x0 gText_Route22_JugglerChauncy_Intro gText_Route22_JugglerChauncy_Defeat
    msgbox gText_Route22_JugglerChauncy_Chat MSG_NORMAL
    end

.global EventScript_Route22_BurglarMose
EventScript_Route22_BurglarMose:
    trainerbattle0 0x0 389 0x0 gText_Route22_BurglarMose_Intro gText_Route22_BurglarMose_Defeat
    msgbox gText_Route22_BurglarMose_Chat MSG_NORMAL
    end

.global SignScript_Route22_MimmettJungle
SignScript_Route22_MimmettJungle:
    msgbox gText_Route22_MimmettJungleSign MSG_SIGN
    end

@ Route 23
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

@ Route 24
.global EventScript_Route24_FindTM85_DreamEater
EventScript_Route24_FindTM85_DreamEater:
    setvar CHOSEN_ITEM ITEM_TM85
    call ItemScript_Common_FindTM
    end

.global EventScript_Route24_FindTM63_DrainPunch
EventScript_Route24_FindTM63_DrainPunch:
    setvar CHOSEN_ITEM ITEM_TM63
    call ItemScript_Common_FindTM
    end

.global EventScript_Route24_PsychicRaya
EventScript_Route24_PsychicRaya:
    trainerbattle0 0x0 486 0x0 gText_Route24_PsychicRaya_Intro gText_Route24_PsychicRaya_Defeat
    msgbox gText_Route24_PsychicRaya_Chat MSG_NORMAL
    end

.global EventScript_Route24_DragonTamerDavid
EventScript_Route24_DragonTamerDavid:
    trainerbattle0 0x0 487 0x0 gText_Route24_DragonTamerDavid_Intro gText_Route24_DragonTamerDavid_Defeat
    msgbox gText_Route24_DragonTamerDavid_Chat MSG_NORMAL
    end

.global EventScript_Route24_PsychicJeff
EventScript_Route24_PsychicJeff:
    trainerbattle0 0x0 488 0x0 gText_Route24_PsychicJeff_Intro gText_Route24_PsychicJeff_Defeat
    msgbox gText_Route24_PsychicJeff_Chat MSG_NORMAL
    end

.global EventScript_Route24_FishermanHumphrey
EventScript_Route24_FishermanHumphrey:
    trainerbattle0 0x0 489 0x0 gText_Route24_FishermanHumphrey_Intro gText_Route24_FishermanHumphrey_Defeat
    msgbox gText_Route24_FishermanHumphrey_Chat MSG_NORMAL
    end

.global EventScript_Route24_TriathleteWillow
EventScript_Route24_TriathleteWillow:
    trainerbattle0 0x0 490 0x0 gText_Route24_TriathleteWillow_Intro gText_Route24_TriathleteWillow_Defeat
    msgbox gText_Route24_TriathleteWillow_Chat MSG_NORMAL
    end

.global EventScript_Route24_BlackbeltIrvine
EventScript_Route24_BlackbeltIrvine:
    trainerbattle0 0x0 491 0x0 gText_Route24_BlackbeltIrvine_Intro gText_Route24_BlackbeltIrvine_Defeat
    msgbox gText_Route24_BlackbeltIrvine_Chat MSG_NORMAL
    end

.global SignScript_Route24_UteyanRuinsSign
SignScript_Route24_UteyanRuinsSign:
    msgbox gText_Route24_UteyanRuinsSign MSG_SIGN
    end

.global SignScript_Route24_TrainerTips
SignScript_Route24_TrainerTips:
    msgbox gText_Route24_TrainerTipsSign MSG_SIGN
    end

.global EventScript_Route24_House_DragonMaster
EventScript_Route24_House_DragonMaster:
    faceplayer
    msgbox gText_Route24_House_DragonMaster_Intro MSG_NORMAL
    callasm CountBadges
    compare LASTRESULT 0x8
    if lessthan _goto DragonMaster_NotEnoughBadges
    msgbox gText_Route24_House_DragonMaster_OfferToTeachDracoMeteor MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DragonMaster_ChoseNo
    special 0xCC @ Check if any pokemon can learn draco meteor
    compare LASTRESULT 0x0
    if equal _goto DragonMaster_NoDragons
    msgbox gText_Route24_House_DragonMaster_ChosePokemonPrompt MSG_NORMAL
    setvar 0x8005 64 @ Draco Meteor
    special 0x18D
    waitstate
    compare LASTRESULT YES
    if false _goto DragonMaster_ChoseNo @ Pokemon couldn't learn, or player chose not to
    npcchatwithmovement gText_Route24_House_DragonMaster_TutoringComplete m_LookDown
    end

DragonMaster_NotEnoughBadges:
    npcchatwithmovement gText_Route24_House_DragonMaster_NotEnoughBadges m_LookDown
    end

DragonMaster_ChoseNo:
    npcchatwithmovement gText_Route24_House_DragonMaster_ChoseNo m_LookDown
    end

DragonMaster_NoDragons:
    npcchatwithmovement gText_Route24_House_DragonMaster_NoDragons m_LookDown
    end
