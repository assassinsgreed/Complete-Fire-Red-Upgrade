.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_MimmettJungle
MapScript_MimmettJungle:
     mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_MimmettJungle_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_MimmettJungle_FlightFlag:
    setworldmapflag 0x8AE
    end

.global EventScript_MimmettJungle_TM28_LeechLife
EventScript_MimmettJungle_TM28_LeechLife:
    setvar CHOSEN_ITEM ITEM_TM28
    call ItemScript_Common_FindTM
    end

.global EventScript_MimmettJungle_Venusaurite
EventScript_MimmettJungle_Venusaurite:
    finditem ITEM_VENUSAURITE 0x1
    end

.global EventScript_MimmettJungle_TM22_SolarBeam
EventScript_MimmettJungle_TM22_SolarBeam:
    setvar CHOSEN_ITEM ITEM_TM22
    call ItemScript_Common_FindTM
    end

.global EventScript_MimmettJungle_ScientistSilas
EventScript_MimmettJungle_ScientistSilas:
    trainerbattle0 0x0 398 0x0 gText_MimmettJungle_ScientistSilas_Intro gText_MimmettJungle_ScientistSilas_Defeat
    msgbox gText_MimmettJungle_ScientistSilas_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_RuinManiacWinston
EventScript_MimmettJungle_RuinManiacWinston:
    trainerbattle0 0x0 399 0x0 gText_MimmettJungle_RuinManiacWinston_Intro gText_MimmettJungle_RuinManiacWinston_Defeat
    msgbox gText_MimmettJungle_RuinManiacWinston_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_BlackBeltLouis
EventScript_MimmettJungle_BlackBeltLouis:
    trainerbattle0 0x0 400 0x0 gText_MimmettJungle_BlackbeltLouis_Intro gText_MimmettJungle_BlackbeltLouis_Defeat
    msgbox gText_MimmettJungle_BlackbeltLouis_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_ChannelerFreyja
EventScript_MimmettJungle_ChannelerFreyja:
    trainerbattle0 0x0 401 0x0 gText_MimmettJungle_ChannelerFreyja_Intro gText_MimmettJungle_ChannelerFreyja_Defeat
    msgbox gText_MimmettJungle_ChannelerFreyja_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_BugCatcherNeil
EventScript_MimmettJungle_BugCatcherNeil:
    trainerbattle0 0x0 402 0x0 gText_MimmettJungle_BugCatcherNeil_Intro gText_MimmettJungle_BugCatcherNeil_Defeat
    msgbox gText_MimmettJungle_BugCatcherNeil_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_FishermanJerry
EventScript_MimmettJungle_FishermanJerry:
    trainerbattle0 0x0 403 0x0 gText_MimmettJungle_FishermanJerry_Intro gText_MimmettJungle_FishermanJerry_Defeat
    msgbox gText_MimmettJungle_FishermanJerry_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_PokefanSusan
EventScript_MimmettJungle_PokefanSusan:
    trainerbattle0 0x0 404 0x0 gText_MimmettJungle_PokefanSusan_Intro gText_MimmettJungle_PokefanSusan_Defeat
    msgbox gText_MimmettJungle_PokefanSusan_Chat MSG_NORMAL
    end

.global EventScript_MimmettJungle_PsychicWanda
EventScript_MimmettJungle_PsychicWanda:
    trainerbattle0 0x0 405 0x0 gText_MimmettJungle_PsychicWanda_Intro gText_MimmettJungle_PsychicWanda_Defeat
    msgbox gText_MimmettJungle_PsychicWanda_Chat MSG_NORMAL
    end

.global SignScript_MimmettJungle_PokerusSign
SignScript_MimmettJungle_PokerusSign:
    msgbox gText_MimmettJungle_PokerusSign MSG_SIGN
    end

.global SignScript_MimmettJungle_SwampSign
SignScript_MimmettJungle_SwampSign:
    msgbox gText_MimmettJungle_SwampSign MSG_SIGN
    end
