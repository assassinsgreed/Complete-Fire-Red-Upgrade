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

.global EventScript_Route5_FindTM58Endure
EventScript_Route5_FindTM58Endure:
    setvar CHOSEN_ITEM ITEM_TM58
    call ItemScript_Common_FindTM
    end

.global SignScript_Route5_Daycare
SignScript_Route5_Daycare:
    msgbox gText_Route5_DaycareSign MSG_SIGN
    end
