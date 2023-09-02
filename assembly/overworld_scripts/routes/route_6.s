.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route6_DirectionsGirl
EventScript_Route6_DirectionsGirl:
    npcchat gText_Route6_DirectionsGirl
    end

.global EventScript_Route6_YoungsterNed
EventScript_Route6_YoungsterNed:
    trainerbattle0 0x0 0x52 0x0 gText_Route6_YoungsterNed_Intro gText_Route6_YoungsterNed_Defeat
    msgbox gText_Route6_YoungsterNed_Chat MSG_NORMAL
    end

.global EventScript_Route6_NinjaBoyRajan
EventScript_Route6_NinjaBoyRajan:
    trainerbattle0 0x0 0x53 0x0 gText_Route6_NinjaBoyRajan_Intro gText_Route6_NinjaBoyRajan_Defeat
    msgbox gText_Route6_NinjaBoyRajan_Chat MSG_NORMAL
    end

.global EventScript_Route6_HikerRomero
EventScript_Route6_HikerRomero:
    trainerbattle0 0x0 0x54 0x0 gText_Route6_HikerRomero_Intro gText_Route6_HikerRomero_Defeat
    msgbox gText_Route6_HikerRomero_Chat MSG_NORMAL
    end

.global EventScript_Route6_SuperNerdEstevan
EventScript_Route6_SuperNerdEstevan:
    trainerbattle0 0x0 0x55 0x0 gText_Route6_SuperNerdEstevan_Intro gText_Route6_SuperNerdEstevan_Defeat
    msgbox gText_Route6_SuperNerdEstevan_Chat MSG_NORMAL
    end

.global EventScript_Route6_EngineerHarry
EventScript_Route6_EngineerHarry:
    trainerbattle0 0x0 0x56 0x0 gText_Route6_EngineerHarry_Intro gText_Route6_EngineerHarry_Defeat
    msgbox gText_Route6_EngineerHarry_Chat MSG_NORMAL
    end

.global EventScript_Route6_GamblerMick
EventScript_Route6_GamblerMick:
    trainerbattle0 0x0 0x57 0x0 gText_Route6_GamblerMick_Intro gText_Route6_GamblerMick_Defeat
    msgbox gText_Route6_GamblerMick_Chat MSG_NORMAL
    end

.global EventScript_Route6_FishermanTaylor
EventScript_Route6_FishermanTaylor:
    trainerbattle0 0x0 0x58 0x0 gText_Route6_FishermanTaylor_Intro gText_Route6_FishermanTaylor_Defeat
    msgbox gText_Route6_FishermanTaylor_Chat MSG_NORMAL
    end

.global EventScript_Route6_NurseLeanne
EventScript_Route6_NurseLeanne:
    faceplayer
    checktrainerflag 0x559
    if SET _goto NurseLeanneHeal
    trainerbattle2 0x0 0x59 0x0 gText_Route6_NurseLeanne_Intro gText_Route6_NurseLeanne_Defeat NurseLeanneHeal
    call NurseLeanneHeal
    end

NurseLeanneHeal:
    msgbox gText_Route6_NurseLeanne_Chat MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route6_NurseLeanne_HealingComplete MSG_NORMAL
    end

.global EventScript_Route6_SuperNerdDante
EventScript_Route6_SuperNerdDante:
    trainerbattle0 0x0 0x5A 0x0 gText_Route6_SuperNerdDante_Intro gText_Route6_SuperNerdDante_Defeat
    msgbox gText_Route6_SuperNerdDante_Chat MSG_NORMAL
    end

.global EventScript_Route6_BugCatcherBillie
EventScript_Route6_BugCatcherBillie:
    trainerbattle0 0x0 0x5B 0x0 gText_Route6_BugCatcherBillie_Intro gText_Route6_BugCatcherBillie_Defeat
    msgbox gText_Route6_BugCatcherBillie_Chat MSG_NORMAL
    end

.global EventScript_Route6_GentlemanLincoln
EventScript_Route6_GentlemanLincoln:
    trainerbattle0 0x0 0x5C 0x0 gText_Route6_GentlemanLincoln_Intro gText_Route6_GentlemanLincoln_Defeat
    msgbox gText_Route6_GentlemanLincoln_Chat MSG_NORMAL
    end

.global EventScript_Route6_BlackbeltRafael
EventScript_Route6_BlackbeltRafael:
    trainerbattle0 0x0 0x5D 0x0 gText_Route6_BlackbeltRafael_Intro gText_Route6_BlackbeltRafael_Defeat
    msgbox gText_Route6_BlackbeltRafael_Chat MSG_NORMAL
    end

.global EventScript_Route6_LassAnna
EventScript_Route6_LassAnna:
    trainerbattle0 0x0 0x5E 0x0 gText_Route6_LassAnna_Intro gText_Route6_LassAnna_Defeat
    msgbox gText_Route6_LassAnna_Chat MSG_NORMAL
    end

.global EventScript_Route6_SwimmerDanika
EventScript_Route6_SwimmerDanika:
    trainerbattle0 0x0 0x5F 0x0 gText_Route6_SwimmerDanika_Intro gText_Route6_SwimmerDanika_Defeat
    msgbox gText_Route6_SwimmerDanika_Chat MSG_NORMAL
    end

.global EventScript_Route6_SrAndJr_Sue
EventScript_Route6_SrAndJr_Sue:
    faceplayer
    trainerbattle0 0x0 0x60 0x0 gText_Route6_SrAndJrSueAndKat_Sue_Intro gText_Route6_SrAndJrSueAndKat_Sue_Defeat
    msgbox gText_Route6_SrAndJrSueAndKat_Sue_Chat MSG_NORMAL
    end

.global EventScript_Route6_SrAndJr_Kat
EventScript_Route6_SrAndJr_Kat:
    faceplayer
    trainerbattle0 0x0 0x60 0x0 gText_Route6_SrAndJrSueAndKat_Kat_Intro gText_Route6_SrAndJrSueAndKat_Kat_Defeat
    msgbox gText_Route6_SrAndJrSueAndKat_Kat_Chat MSG_NORMAL
    end

.global EventScript_Route6_HikerDarryl
EventScript_Route6_HikerDarryl:
    trainerbattle0 0x0 0x61 0x0 gText_Route6_HikerDarryl_Intro gText_Route6_HikerDarryl_Defeat
    msgbox gText_Route6_HikerDarryl_Chat MSG_NORMAL
    end

.global EventScript_Route6_Blastoisinite
EventScript_Route6_Blastoisinite:
    finditem ITEM_BLASTOISINITE 0x1
    end

.global EventScript_Route6_FindTM78Bulldoze
EventScript_Route6_FindTM78Bulldoze:
    setvar CHOSEN_ITEM ITEM_TM78
    call ItemScript_Common_FindTM
    end

.global EventScript_Route6_FindTM88StealthRock
EventScript_Route6_FindTM88StealthRock:
    setvar CHOSEN_ITEM ITEM_TM88
    call ItemScript_Common_FindTM
    end

.global SignScript_Route6_Directions
SignScript_Route6_Directions:
    msgbox gText_Route6_DirectionsSign MSG_SIGN
    end

.global SignScript_Route6_ItemFinder
SignScript_Route6_ItemFinder:
    msgbox gText_Route6_ItemFinderSign MSG_SIGN
    end

.global SignScript_Route6_WrongWay
SignScript_Route6_WrongWay:
    msgbox gText_Route6_WrongWaySign MSG_SIGN
    end
