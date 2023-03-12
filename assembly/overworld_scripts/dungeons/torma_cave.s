.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_TormaCave
MapScript_TormaCave:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_TormaCave_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_TormaCave_FlightFlag:
    setworldmapflag 0x8A6
    end

.global EventScript_TormaCave_RockyHelmet
EventScript_TormaCave_RockyHelmet:
    finditem ITEM_ROCKY_HELMET 0x1
    end

.global EventScript_TormaCave_Glalitite
EventScript_TormaCave_Glalitite:
    finditem ITEM_GLALITITE 0x1
    end

.global EventScript_TormaCave_FishermanAlfie
EventScript_TormaCave_FishermanAlfie:
    trainerbattle0 0x0 0x2D 0x0 gText_TormaCave_FishermanAlfie_Intro gText_TormaCave_FishermanAlfie_Defeat
    msgbox gText_TormaCave_FishermanAlfie_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_HikerNob
EventScript_TormaCave_HikerNob:
    trainerbattle0 0x0 0x2E 0x0 gText_TormaCave_HikerNob_Intro gText_TormaCave_HikerNob_Defeat
    msgbox gText_TormaCave_HikerNob_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_HikerSaul
EventScript_TormaCave_HikerSaul:
    trainerbattle0 0x0 0x2F 0x0 gText_TormaCave_HikerSaul_Intro gText_TormaCave_HikerSaul_Defeat
    msgbox gText_TormaCave_HikerSaul_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_EngineerWyatt
EventScript_TormaCave_EngineerWyatt:
    trainerbattle0 0x0 0x30 0x0 gText_TormaCave_EngineerWyatt_Intro gText_TormaCave_EngineerWyatt_Defeat
    msgbox gText_TormaCave_EngineerWyatt_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_EngineerShane
EventScript_TormaCave_EngineerShane:
    trainerbattle0 0x0 0x31 0x0 gText_TormaCave_EngineerShane_Intro gText_TormaCave_EngineerShane_Defeat
    msgbox gText_TormaCave_EngineerShane_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_PokefanCorey
EventScript_TormaCave_PokefanCorey:
    trainerbattle0 0x0 0x32 0x0 gText_TormaCave_PokefanCorey_Intro gText_TormaCave_PokefanCorey_Defeat
    msgbox gText_TormaCave_PokefanCorey_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_LassHarmony
EventScript_TormaCave_LassHarmony:
    trainerbattle0 0x0 0x33 0x0 gText_TormaCave_LassHarmony_Intro gText_TormaCave_LassHarmony_Defeat
    msgbox gText_TormaCave_LassHarmony_Chat MSG_NORMAL
    end

.global SignScript_TormaCave_TrainerTips
SignScript_TormaCave_TrainerTips:
    msgbox gText_TormaCave_TrainerTips MSG_SIGN
    end

.global EventScript_TormaCave_SetPathCleared
EventScript_TormaCave_SetPathCleared:
    setflag 0x035 @ Cleared Torma Cave
    end

.global EventScript_TormaCave_ClearPathCleared
EventScript_TormaCave_ClearPathCleared:
    # Only clear the flag indicating that Torma Cave has been cleared if the player hasn't spoken with the Foreman upon leaving
    # This avoids a case where the player goes to the end of the cave, leaves from the start, and breaks the cutscene
    checkflag 0x036 @ Met with Foreman
    if SET _goto End
    clearflag 0x035 @ Cleared Torma Cave
    end
