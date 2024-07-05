.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ North
.global EventScript_Route15North_SwimmerMiles
EventScript_Route15North_SwimmerMiles:
    trainerbattle0 0x0 343 0x0 gText_Route15North_SwimmerMiles_Intro gText_Route15North_SwimmerMiles_Defeat
    msgbox gText_Route15North_SwimmerMiles_Chat MSG_NORMAL
    end

.global EventScript_Route15North_SwimmerFiona
EventScript_Route15North_SwimmerFiona:
    trainerbattle0 0x0 344 0x0 gText_Route15North_SwimmerFiona_Intro gText_Route15North_SwimmerFiona_Defeat
    msgbox gText_Route15North_SwimmerFiona_Chat MSG_NORMAL
    end

.global EventScript_Route15North_HikerKlaus
EventScript_Route15North_HikerKlaus:
    trainerbattle0 0x0 345 0x0 gText_Route15North_HikerKlaus_Intro gText_Route15North_HikerKlaus_Defeat
    msgbox gText_Route15North_HikerKlaus_Chat MSG_NORMAL
    end

.global EventScript_Route15North_SwimmerUrsula
EventScript_Route15North_SwimmerUrsula:
    trainerbattle0 0x0 346 0x0 gText_Route15North_SwimmerUrsula_Intro gText_Route15North_SwimmerUrsula_Defeat
    msgbox gText_Route15North_SwimmerUrsula_Chat MSG_NORMAL
    end

.global EventScript_Route15North_SwimmerQuincy
EventScript_Route15North_SwimmerQuincy:
    trainerbattle0 0x0 347 0x0 gText_Route15North_SwimmerQuincy_Intro gText_Route15North_SwimmerQuincy_Defeat
    msgbox gText_Route15North_SwimmerQuincy_Chat MSG_NORMAL
    end

.global EventScript_Route15North_CoolTrainerWesley
EventScript_Route15North_CoolTrainerWesley:
    trainerbattle0 0x0 348 0x0 gText_Route15North_CoolTrainerWesley_Intro gText_Route15North_CoolTrainerWesley_Defeat
    msgbox gText_Route15North_CoolTrainerWesley_Chat MSG_NORMAL
    end

.global EventScript_Route15North_SuperNerdEthan
EventScript_Route15North_SuperNerdEthan:
    trainerbattle0 0x0 349 0x0 gText_Route15North_SuperNerdEthan_Intro gText_Route15North_SuperNerdEthan_Defeat
    msgbox gText_Route15North_SuperNerdEthan_Chat MSG_NORMAL
    end

.global EventScript_Route15North_ChannelerLila
EventScript_Route15North_ChannelerLila:
    trainerbattle0 0x0 350 0x0 gText_Route15North_ChannelerLila_Intro gText_Route15North_ChannelerLila_Defeat
    msgbox gText_Route15North_ChannelerLila_Chat MSG_NORMAL
    end

.global EventScript_Route15North_FindTM55Scald
EventScript_Route15North_FindTM55Scald:
    setvar CHOSEN_ITEM ITEM_TM55
    call ItemScript_Common_FindTM
    end

.global EventScript_Route15North_FindFactoryKey
EventScript_Route15North_FindFactoryKey:
    finditem ITEM_FACTORY_KEY 0x1
    end

.global SignScript_Route15North_RestStopAdvertisementSign
SignScript_Route15North_RestStopAdvertisementSign:
    msgbox gText_Route15North_RestStopAdvertisementSign MSG_SIGN
    end

@ South
.global EventScript_Route15South_Nurse
EventScript_Route15South_Nurse:
    msgbox gText_Route15South_NursePrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto HealingDone
    msgbox gText_Route15South_NurseHealing MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_Route15South_NurseHealingDone MSG_NORMAL
    goto HealingDone
    end

HealingDone:
    msgbox gText_Route15South_NurseOutro MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

.global EventScript_Route15South_Shopkeeper
EventScript_Route15South_Shopkeeper:
    msgbox gText_Route15South_Shopkeeper MSG_NORMAL
    pokemart Route15Shop
    npcchatwithmovement gText_Route15South_ShopkeeperDone m_LookDown
    end

.align 1
Route15Shop:
    .hword ITEM_GREAT_BALL
    .hword ITEM_LEMONADE
    .hword ITEM_LAVA_COOKIE
    .hword ITEM_REVIVE
    .hword ITEM_SUPER_REPEL
    .hword ITEM_NONE

.global EventScript_Route15South_Boy
EventScript_Route15South_Boy:
    npcchat gText_Route15South_Boy
    end

.global EventScript_Route15South_RuinManiac
EventScript_Route15South_RuinManiac:
    npcchat gText_Route15South_RuinManiac
    end

.global EventScript_Route15South_SwimmerGerald
EventScript_Route15South_SwimmerGerald:
    trainerbattle0 0x0 351 0x0 gText_Route15South_SwimmerGerald_Intro gText_Route15South_SwimmerGerald_Defeat
    msgbox gText_Route15South_SwimmerGerald_Chat MSG_NORMAL
    end

.global EventScript_Route15South_SwimmerAlexandra
EventScript_Route15South_SwimmerAlexandra:
    trainerbattle0 0x0 352 0x0 gText_Route15South_SwimmerAlexandra_Intro gText_Route15South_SwimmerAlexandra_Defeat
    msgbox gText_Route15South_SwimmerAlexandra_Chat MSG_NORMAL
    end

.global EventScript_Route15South_SwimmerBernard
EventScript_Route15South_SwimmerBernard:
    trainerbattle0 0x0 353 0x0 gText_Route15South_SwimmerBernard_Intro gText_Route15South_SwimmerBernard_Defeat
    msgbox gText_Route15South_SwimmerBernard_Chat MSG_NORMAL    
    end

.global EventScript_Route15South_SwimmerHarold
EventScript_Route15South_SwimmerHarold:
    trainerbattle0 0x0 354 0x0 gText_Route15South_SwimmerHarold_Intro gText_Route15South_SwimmerHarold_Defeat
    msgbox gText_Route15South_SwimmerHarold_Chat MSG_NORMAL
    end

.global EventScript_Route15South_SwimmerMelinda
EventScript_Route15South_SwimmerMelinda:
    trainerbattle0 0x0 355 0x0 gText_Route15South_SwimmerMelinda_Intro gText_Route15South_SwimmerMelinda_Defeat
    msgbox gText_Route15South_SwimmerMelinda_Chat MSG_NORMAL    
    end

.global EventScript_Route15South_BlackbeltFranklin
EventScript_Route15South_BlackbeltFranklin:
    trainerbattle0 0x0 356 0x0 gText_Route15South_BlackbeltFranklin_Intro gText_Route15South_BlackbeltFranklin_Defeat
    msgbox gText_Route15South_BlackbeltFranklin_Chat MSG_NORMAL
    end

.global EventScript_Route15South_SwimmerPatricia
EventScript_Route15South_SwimmerPatricia:
    trainerbattle0 0x0 357 0x0 gText_Route15South_SwimmerPatricia_Intro gText_Route15South_SwimmerPatricia_Defeat
    msgbox gText_Route15South_SwimmerPatricia_Chat MSG_NORMAL
    end

.global SignScript_Route15South_RestStopSign
SignScript_Route15South_RestStopSign:
    msgbox gText_Route15South_RestStopSign MSG_SIGN
    end
