.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route20_Kangaskhanite
EventScript_Route20_Kangaskhanite:
    finditem ITEM_KANGASKHANITE 0x1
    end

.global EventScript_Route20_TM19Roost
EventScript_Route20_TM19Roost:
    setvar CHOSEN_ITEM ITEM_TM19
    call ItemScript_Common_FindTM
    end

.global EventScript_Route20_PsychicMcKenzie
EventScript_Route20_PsychicMcKenzie:
    trainerbattle0 0x0 375 0x0 gText_Route20_PsychicMcKenzie_Intro gText_Route20_PsychicMcKenzie_Defeat
    msgbox gText_Route20_PsychicMcKenzie_Chat MSG_NORMAL
    end

.global EventScript_Route20_PicnickerWhitney
EventScript_Route20_PicnickerWhitney:
    trainerbattle0 0x0 376 0x0 gText_Route20_PicnickerWhitney_Intro gText_Route20_PicnickerWhitney_Defeat
    msgbox gText_Route20_PicnickerWhitney_Chat MSG_NORMAL
    end

.global EventScript_Route20_TriathleteLena
EventScript_Route20_TriathleteLena:
    trainerbattle0 0x0 377 0x0 gText_Route20_TriathleteLena_Intro gText_Route20_TriathleteLena_Defeat
    msgbox gText_Route20_TriathleteLena_Chat MSG_NORMAL
    end

.global EventScript_Route20_EngineerHomer
EventScript_Route20_EngineerHomer:
    trainerbattle0 0x0 378 0x0 gText_Route20_EngineerHomer_Intro gText_Route20_EngineerHomer_Defeat
    msgbox gText_Route20_EngineerHomer_Chat MSG_NORMAL
    end

.global EventScript_Route20_CrushGirlRoxy
EventScript_Route20_CrushGirlRoxy:
    trainerbattle0 0x0 379 0x0 gText_Route20_CrushGirlRoxy_Intro gText_Route20_CrushGirlRoxy_Defeat
    msgbox gText_Route20_CrushGirlRoxy_Chat MSG_NORMAL
    end

.global EventScript_Route20_HikerRoyce
EventScript_Route20_HikerRoyce:
    trainerbattle0 0x0 380 0x0 gText_Route20_HikerRoyce_Intro gText_Route20_HikerRoyce_Defeat
    msgbox gText_Route20_HikerRoyce_Chat MSG_NORMAL
    end

.global EventScript_Route20_SuperNerdElliot
EventScript_Route20_SuperNerdElliot:
    trainerbattle0 0x0 381 0x0 gText_Route20_SuperNerdElliot_Intro gText_Route20_SuperNerdElliot_Defeat
    msgbox gText_Route20_SuperNerdElliot_Chat MSG_NORMAL
    end

.global EventScript_Route20_YoungsterDewey
EventScript_Route20_YoungsterDewey:
    trainerbattle0 0x0 382 0x0 gText_Route20_YoungsterDewey_Intro gText_Route20_YoungsterDewey_Defeat
    msgbox gText_Route20_YoungsterDewey_Chat MSG_NORMAL
    end

.global EventScript_Route20_JugglerHiram
EventScript_Route20_JugglerHiram:
    trainerbattle0 0x0 383 0x0 gText_Route20_JugglerHiram_Intro gText_Route20_JugglerHiram_Defeat
    msgbox gText_Route20_JugglerHiram_Chat MSG_NORMAL
    end

.global EventScript_Route20_NurseJessie
EventScript_Route20_NurseJessie:
    faceplayer
    checktrainerflag 384
    if SET _goto NurseJessieHeal
    trainerbattle2 0x0 384 0x0 gText_Route20_NurseJessie_Intro gText_Route20_NurseJessie_Defeat NurseJessieHeal
    call NurseJessieHeal
    end

NurseJessieHeal:
    msgbox gText_Route20_NurseJessie_Chat MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_Route20_NurseJessie_HealingComplete MSG_NORMAL
    end

.global SignScript_Route20_VictoryRoadNavigation
SignScript_Route20_VictoryRoadNavigation:
    msgbox gText_Route20_VictoryRoadNavigationSign MSG_SIGN
    end

.global SignScript_Route20_TrainerTips
SignScript_Route20_TrainerTips:
    msgbox gText_Route20_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route20_MimmettJungle
SignScript_Route20_MimmettJungle:
    msgbox gText_Route20_MimmettJungleSign MSG_SIGN
    end

.global EventScript_Route20Cave_TM69RockPolish
EventScript_Route20Cave_TM69RockPolish:
    setvar CHOSEN_ITEM ITEM_TM69
    call ItemScript_Common_FindTM
    end

@ Treasure Beach
.global MapScript_Route20_TreasureBeach
MapScript_Route20_TreasureBeach:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route20_TreasureBeach_InitializeTreasures
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_Route20_TreasureBeach_InitializeTreasures:
    checkflag 0x25E @ Treasure Beach has been initialized
    if SET _goto End
    callasm InitializeTreasureBeach
    setflag 0x25E @ Treasure Beach has been initialized
    end

.global EventScript_Route20_TreasureBeach_YoungGirl
EventScript_Route20_TreasureBeach_YoungGirl:
    npcchat Route20_TreasureBeach_YoungGirl
    end

.global EventScript_Route20_TreasureBeach_CapBoy
EventScript_Route20_TreasureBeach_CapBoy:
    npcchat Route20_TreasureBeach_CapBoy
    end

.global EventScript_Route20_TreasureBeach_GrownMan
EventScript_Route20_TreasureBeach_GrownMan:
    npcchat Route20_TreasureBeach_GrownMan
    end

.global EventScript_Route20_TreasureBeach_Beauty
EventScript_Route20_TreasureBeach_Beauty:
    npcchat Route20_TreasureBeach_Beauty
    end

.global EventScript_Route20_TreasureBeach_TM73ThunderWave
EventScript_Route20_TreasureBeach_TM73ThunderWave:
    setvar CHOSEN_ITEM ITEM_TM73
    call ItemScript_Common_FindTM
    end

.global SignScript_Route20_TreasureBeach_BeachSign
SignScript_Route20_TreasureBeach_BeachSign:
    msgbox gText_Route20_TreasureBeach_Sign MSG_SIGN
    end
