.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route5_Biker
EventScript_Route5_Biker:
    msgbox gText_Route5_Biker MSG_NORMAL
    goto FindAnotherRoute

.global EventScript_Route5_BikerLeader
EventScript_Route5_BikerLeader:
    msgbox gText_Route5_BikerLeader MSG_NORMAL
    goto FindAnotherRoute

FindAnotherRoute:
    msgbox gText_Route5_AnotherRoute MSG_NORMAL
    end

.global EventScript_Route5And7_Cut
EventScript_Route5And7_Cut:
    setflag 0x38 @ Hide Route 5 bikers
    goto EventScript_Common_Cut

.global EventScript_Route5_LadyFaith
EventScript_Route5_LadyFaith:
    trainerbattle0 0x0 0x41 0x0 gText_Route5_LadyFaith_Intro gText_Route5_LadyFaith_Defeat
    msgbox gText_Route5_LadyFaith_Chat MSG_NORMAL
    end

.global EventScript_Route5_BugCatcherBen
EventScript_Route5_BugCatcherBen:
    trainerbattle0 0x0 0x42 0x0 gText_Route5_BugCatcherBen_Intro gText_Route5_BugCatcherBen_Defeat
    msgbox gText_Route5_BugCatcherBen_Chat MSG_NORMAL
    end

.global EventScript_Route5_PsychicAlyssia
EventScript_Route5_PsychicAlyssia:
    trainerbattle0 0x0 0x43 0x0 gText_Route5_PsychicAlyssia_Intro gText_Route5_PsychicAlyssia_Defeat
    msgbox gText_Route5_PsychicAlyssia_Chat MSG_NORMAL
    end

.global EventScript_Route5_BreederBrenda
EventScript_Route5_BreederBrenda:
    trainerbattle0 0x0 0x44 0x0 gText_Route5_BreederBrenda_Intro gText_Route5_BreederBrenda_Defeat
    msgbox gText_Route5_BreederBrenda_Chat MSG_NORMAL
    end

.global EventScript_Route5_BlackbeltRaheem
EventScript_Route5_BlackbeltRaheem:
    trainerbattle0 0x0 0x45 0x0 gText_Route5_BlackbeltRaheem_Intro gText_Route5_BlackbeltRaheem_Defeat
    msgbox gText_Route5_BlackbeltRaheem_Chat MSG_NORMAL
    end

.global EventScript_Route5_GamblerDominik
EventScript_Route5_GamblerDominik:
    trainerbattle0 0x0 0x46 0x0 gText_Route5_GamblerDominik_Intro gText_Route5_GamblerDominik_Defeat
    msgbox gText_Route5_GamblerDominik_Chat MSG_NORMAL
    end

.global EventScript_Route5_LadyJuliet
EventScript_Route5_LadyJuliet:
    compare PLAYERFACING LEFT
    if equal _call JulietAndMarcusLookRight
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_LadyJuliet_Intro gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Route5_LadyJuliet_Chat gText_Route5_GentlemanMarcus_Chat
    msgbox gText_Route5_LadyJuliet_Chat MSG_NORMAL
    end

.global EventScript_Route5_GentlemanMarcus
EventScript_Route5_GentlemanMarcus:
    compare PLAYERFACING RIGHT
    if equal _call JulietAndMarcusLookLeft
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_LadyJuliet_Intro gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Route5_LadyJuliet_Chat gText_Route5_GentlemanMarcus_Chat
    msgbox gText_Route5_GentlemanMarcus_Chat MSG_NORMAL
    end

JulietAndMarcusLookRight:
    applymovement 0x11 m_LookRight
    applymovement 0x12 m_LookRight
    return

JulietAndMarcusLookLeft:
    applymovement 0x11 m_LookLeft
    applymovement 0x12 m_LookLeft
    return

.global EventScript_Route5_AffectionGirl
EventScript_Route5_AffectionGirl:
    npcchatwithmovement gText_Route5_AffectionGirl m_LookRight
    end

.global EventScript_Route5_EggGiver
EventScript_Route5_EggGiver:
    lock
    faceplayer
    msgbox gText_Route5_EggGiver_Introduction MSG_NORMAL
    checkflag 0x233 @ Received custom egg
    if NOT_SET _call ReceivePokemonEgg
    msgbox gText_Route5_EggGiver_EggInstructions MSG_NORMAL
    checkflag 0x234 @ Received oval charm
    if NOT_SET _goto CheckForOvalCharmGift
    goto ResetEggMan

ReceivePokemonEgg:
    msgbox gText_Route5_EggGiver_Prompt MSG_YESNO
    compare LASTRESULT YES
    if FALSE _goto EggRejection
    msgbox gText_Route5_EggGiver_EggPun MSG_NORMAL
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto PartyFull
    fanfare 0x10D @ Fanfare 2
    msgbox gText_Route5_EggGiver_ReceivedEgg MSG_NORMAL
    waitfanfare
    msgbox gText_Route5_EggGiver_ReceiveEggComment MSG_NORMAL
    copyvar 0x8006 0x408C @ Copy index of the player's grass starter gen into egg var
    compare 0x8006 0x0
    if equal _call SetPichu
    compare 0x8006 0x1
    if equal _call SetTogepi
    compare 0x8006 0x2
    if equal _call SetWynaut
    compare 0x8006 0x3
    if equal _call SetRiolu
    compare 0x8006 0x4
    if equal _call SetLarvesta
    compare 0x8006 0x5
    if equal _call SetHappiny
    compare 0x8006 0x6
    if equal _call SetEevee
    compare 0x8006 0x7
    if equal _call SetToxel
    callasm GiveCustomEgg
    setflag 0x233 @ Received custom egg
    return

EggRejection:
    msgbox gText_Route5_EggGiver_EggRejected MSG_NORMAL
    goto ResetEggMan

PartyFull:
    msgbox gText_Route5_EggGiver_NoRoomForEgg MSG_NORMAL
    goto ResetEggMan

SetPichu:
    setvar 0x8005 SPECIES_PICHU
    return

SetTogepi:
    setvar 0x8005 SPECIES_TOGEPI
    return

SetWynaut:
    setvar 0x8005 SPECIES_WYNAUT
    return

SetRiolu:
    setvar 0x8005 SPECIES_RIOLU
    return

SetLarvesta:
    setvar 0x8005 SPECIES_LARVESTA
    return

SetHappiny:
    setvar 0x8005 SPECIES_HAPPINY
    return

SetEevee:
    setvar 0x8005 SPECIES_EEVEE
    return

SetToxel:
    setvar 0x8005 SPECIES_TOXEL
    return

CheckForOvalCharmGift:
    setvar 0x8004 0xD @ Number of eggs hatched
    callasm StoreGameStat
    buffernumber 0x0 LASTRESULT
    compare LASTRESULT 0xA
    if lessthan _goto NotEnoughEggsHatched
    msgbox gText_Route5_EggGiver_HatchedAtLeastTenEggs MSG_NORMAL
    loadpointer 0x0 gText_Route5_EggGiver_ReceivedOvalCharm
    obtainitem ITEM_OVAL_CHARM 0x1
    msgbox gText_Route5_EggGiver_TenEggGiftReceived MSG_NORMAL
    setflag 0x234 @ Oval charm received
    goto ResetEggMan

NotEnoughEggsHatched:
    msgbox gText_Route5_EggGiver_TenEggGiftComment MSG_NORMAL
    goto ResetEggMan

ResetEggMan:
    applymovement 0x3 m_LookLeft
    waitmovement ALLEVENTS
    release
    end

.global EventScript_Route5_FindTM58Endure
EventScript_Route5_FindTM58Endure:
    setvar CHOSEN_ITEM ITEM_TM58
    call ItemScript_Common_FindTM
    end

.global SignScript_Route5_Daycare
SignScript_Route5_Daycare:
    msgbox gText_Route5_DaycareSign MSG_SIGN
    end

@@ Heleo Ranch
.global MapScript_HeleoRanchExterior
MapScript_HeleoRanchExterior:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoRanch_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMareepVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_FlightFlag:
    setworldmapflag 0x8A7 @ Been to Heleo Ranch
    end

MapEntryScript_HeleoRanch_HandleMareepVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto End
    setflag 0xE07 @ Evenining or night, hide all mareeps on field and Moomoo Milk seller, by setting daily flag
    end

.global MapScript_HeleoRanchInterior
MapScript_HeleoRanchInterior:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMomVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_HandleMomVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto HideMom
    clearflag 0xE08 
    end

HideMom:
    setflag 0xE08 @ Hide mom in house during morning and day
    end

.global EvenScript_HeleoRanch_Mareep
EvenScript_HeleoRanch_Mareep:
    lock
    faceplayer
    checksound
    cry SPECIES_MAREEP 0x0
    msgbox gText_HeleoRanch_Mareep MSG_NORMAL
    release
    end

.global EvenScript_HeleoRanch_MoomooMilkSeller
EvenScript_HeleoRanch_MoomooMilkSeller:
    lock
    faceplayer
    msgbox gText_HeleoRanch_MoomooMilkSeller_PurchaseRequest MSG_KEEPOPEN
    showmoney 0x0 0x0
    multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseOne 0
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseADozen 1
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseNone 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, BuyOneMoomooMilk
	case 1, BuyADozenMoomooMilk
	case 2, BuyNoMoomooMilk
    goto BuyNoMoomooMilk

BuyOneMoomooMilk:
    checkmoney 0x1F4 @ Has 500 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1F4
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0x1
    goto EndMoomooMilkSeller

BuyADozenMoomooMilk:
    checkmoney 0x1770 @ Has 6,000 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1770
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0xC
    goto EndMoomooMilkSeller

BuyNoMoomooMilk:
    msgbox gText_HeleoRanch_MoomooMilkSeller_ChoseNotToBuy MSG_NORMAL
    goto EndMoomooMilkSeller

PurchaseMoomooMilk:
    updatemoney
    playse 0xF8 @ Money SE
    msgbox gText_HeleoRanch_MoomooMilkSeller_PuchaseComplete MSG_NORMAL
    return

NotEnoughCash:
    msgbox gText_HeleoRanch_MoomooMilkSeller_NotEnoughCash MSG_NORMAL
    goto EndMoomooMilkSeller

EndMoomooMilkSeller:
    hidemoney
    release
    end

.global EvenScript_HeleoRanch_Ampharos
EvenScript_HeleoRanch_Ampharos:
    lock
    faceplayer
    checksound
    cry SPECIES_AMPHAROS 0x0
    msgbox gText_HeleoRanch_AgitatedAmpharos_Sound MSG_NORMAL
    msgbox gText_HeleoRanch_AgitatedAmpharos_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto AmpharosLeftAlone
    setflag 0x903 @ Disable running
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleStarted MSG_NORMAL
    wildbattle SPECIES_AMPHAROS 0x1E ITEM_SITRUS_BERRY
    setflag 0x03E @ Hide Ampharos
    hidesprite LASTTALKED
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleEnded MSG_NORMAL
    clearflag 0x903 @ Enable running
    release
    end

AmpharosLeftAlone:
    msgbox gText_HeleoRanch_AgitatedAmpharos_LeftAlone MSG_NORMAL
    applymovement 0xA m_LookDown
    end

.global EvenScript_HeleoRanch_BurglarCole
EvenScript_HeleoRanch_BurglarCole:
    trainerbattle0 0x0 0x49 0x0 gText_HeleoRanch_BurglarCole_Intro gText_HeleoRanch_BurglarCole_Defeat
    msgbox gText_HeleoRanch_BurglarCole_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_CamperTroy
EvenScript_HeleoRanch_CamperTroy:
    trainerbattle0 0x0 0x4A 0x0 gText_HeleoRanch_CamperTroy_Intro gText_HeleoRanch_CamperTroy_Defeat
    msgbox gText_HeleoRanch_CamperTroy_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_BreederLaura
EvenScript_HeleoRanch_BreederLaura:
    trainerbattle0 0x0 0x4B 0x0 gText_HeleoRanch_BreederLaura_Intro gText_HeleoRanch_BreederLaura_Defeat
    msgbox gText_HeleoRanch_BreederLaura_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_PicknickerCarly
EvenScript_HeleoRanch_PicknickerCarly:
    trainerbattle0 0x0 0x4C 0x0 gText_HeleoRanch_PicknickerCarly_Intro gText_HeleoRanch_PicknickerCarly_Defeat
    msgbox gText_HeleoRanch_PicknickerCarly_Chat MSG_NORMAL
    end

.global EventScript_HeleoRanch_FindTM45Attract
EventScript_HeleoRanch_FindTM45Attract:
    setvar CHOSEN_ITEM ITEM_TM45
    call ItemScript_Common_FindTM
    end

.global EventScript_HeleoRanch_Ampharosite
EventScript_HeleoRanch_Ampharosite:
    finditem ITEM_AMPHAROSITE 0x1
    end

.global SignScript_HeleoRanch_RanchGlade
SignScript_HeleoRanch_RanchGlade:
    msgbox gText_HeleoRanch_GladeSign MSG_SIGN
    end

.global SignScript_HeleoRanch_RanchEntrance
SignScript_HeleoRanch_RanchEntrance:
    msgbox gText_HeleoRanch_EntranceSign MSG_SIGN
    end

.global EventScript_HeleoRanch_Dad
EventScript_HeleoRanch_Dad:
    npcchat gText_HeleoRanch_Dad
    end

.global EventScript_HeleoRanch_Daughter
EventScript_HeleoRanch_Daughter:
    npcchatwithmovement gText_HeleoRanch_Daughter m_LookUp
    end

.global EventScript_HeleoRanch_Mom
EventScript_HeleoRanch_Mom:
    npcchat gText_HeleoRanch_Mom
    end

.global EventScript_HeleoRanch_Son
EventScript_HeleoRanch_Son:
    npcchat gText_HeleoRanch_Son
    end
