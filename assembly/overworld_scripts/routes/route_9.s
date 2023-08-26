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

.global EventScript_Route9_Sceptilite
EventScript_Route9_Sceptilite:
    finditem ITEM_SCEPTILITE 0x1
    end

.global EventScript_Route9_TM62_Acrobatics
EventScript_Route9_TM62_Acrobatics:
    setvar CHOSEN_ITEM ITEM_TM62
    call ItemScript_Common_FindTM
    end

.global EventScript_Route9_SlowbroGirl
EventScript_Route9_SlowbroGirl:
    msgbox gText_Route9_SlowbroGirlFrustration MSG_NORMAL
    faceplayer
    msgbox gText_Route9_SlowbroGirlApology MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_Route9_Slowbro
EventScript_Route9_Slowbro:
    cry SPECIES_SLOWBRO 0x0
    applymovement LASTTALKED m_Question
    msgbox gText_Route9_Slowbro MSG_NORMAL
    end

.global EventScript_Route9_CollectorMarshall
EventScript_Route9_CollectorMarshall:
    trainerbattle0 0x0 0x9D 0x0 gText_Route9_CollectorMarshall_Intro gText_Route9_CollectorMarshall_Defeat
    msgbox gText_Route9_CollectorMarshall_Chat MSG_NORMAL
    end

.global EventScript_Route9_CoolTrainerAndrea
EventScript_Route9_CoolTrainerAndrea:
    trainerbattle0 0x0 0x9E 0x0 gText_Route9_CoolTrainerAndrea_Intro gText_Route9_CoolTrainerAndrea_Defeat
    msgbox gText_Route9_CoolTrainerAndrea_Chat MSG_NORMAL
    end

.global EventScript_Route9_FishermanYusuf
EventScript_Route9_FishermanYusuf:
    trainerbattle0 0x0 0x9F 0x0 gText_Route9_FishermanYusuf_Intro gText_Route9_FishermanYusuf_Defeat
    msgbox gText_Route9_FishermanYusuf_Chat MSG_NORMAL
    end

.global EventScript_Route9_GentlemanGavin
EventScript_Route9_GentlemanGavin:
    trainerbattle0 0x0 0xA0 0x0 gText_Route9_GentlemanGavin_Intro gText_Route9_GentlemanGavin_Defeat
    msgbox gText_Route9_GentlemanGavin_Chat MSG_NORMAL
    end

.global EventScript_Route9_NinjaBoyAyrton
EventScript_Route9_NinjaBoyAyrton:
    trainerbattle0 0x0 0xA1 0x0 gText_Route9_NinjaBoyAyrton_Intro gText_Route9_NinjaBoyAyrton_Defeat
    msgbox gText_Route9_NinjaBoyAyrton_Chat MSG_NORMAL
    end

.global EventScript_Route9_BreederTalia
EventScript_Route9_BreederTalia:
    trainerbattle0 0x0 0xA2 0x0 gText_Route9_BreederTalia_Intro gText_Route9_BreederTalia_Defeat
    msgbox gText_Route9_BreederTalia_Chat MSG_NORMAL
    end

.global EventScript_Route9_PicknickerZoe
EventScript_Route9_PicknickerZoe:
    trainerbattle0 0x0 0xA3 0x0 gText_Route9_PicknickerZoe_Intro gText_Route9_PicknickerZoe_Defeat
    msgbox gText_Route9_PicknickerZoe_Chat MSG_NORMAL
    end

.global EventScript_Route9_CoolTrainerKingsley
EventScript_Route9_CoolTrainerKingsley:
    trainerbattle0 0x0 0xA4 0x0 gText_Route9_CoolTrainerKingsley_Intro gText_Route9_CoolTrainerKingsley_Defeat
    msgbox gText_Route9_CoolTrainerKingsley_Chat MSG_NORMAL
    end

.global SignScript_Route9_TrainerTips
SignScript_Route9_TrainerTips:
    msgbox gText_Route9_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route9_FlutistsHouse
SignScript_Route9_FlutistsHouse:
    msgbox gText_Route9_FlutistsSign MSG_SIGN
    end

.global SignScript_Route9_Route12RestHouse
SignScript_Route9_Route12RestHouse:
    msgbox gText_Route9_RestHouseSign MSG_SIGN
    end
