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
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_LadyJuliet_Intro gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Route5_LadyJuliet_Chat gText_Route5_GentlemanMarcus_Chat
    msgbox gText_Route5_LadyJuliet_Chat MSG_NORMAL
    end

.global EventScript_Route5_GentlemanMarcus
EventScript_Route5_GentlemanMarcus:
    @ Perform a double battle with Juliet & Marcus' teams (0x47 and 0x48), referencing their overworld NPC IDs (0x10 and 0x11), with their respective intro/defeat/chat text
    trainerbattle11 0x0 0x47 0x48 0x10 0x11 0x0 gText_Route5_LadyJuliet_Intro gText_Route5_GentlemanMarcus_Intro gText_Route5_LadyJuliet_Defeat gText_Route5_GentlemanMarcus_Defeat gText_Route5_LadyJuliet_Chat gText_Route5_GentlemanMarcus_Chat
    msgbox gText_Route5_GentlemanMarcus_Chat MSG_NORMAL
    end

.global EventScript_Route5_AffectionGirl
EventScript_Route5_AffectionGirl:
    npcchat2 0x2 m_LookRight gText_Route5_AffectionGirl
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
