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

.global EventScript_MimmettJungle_Zeraora
EventScript_MimmettJungle_Zeraora:
    msgbox gText_MimmettJungle_Zeraora_BattleConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ZeraoraChoseNo
    faceplayer
    cry SPECIES_ZERAORA 0x0
    msgbox gText_MimmettJungle_Zeraora_ChoseYes MSG_NORMAL
    waitcry
    @ Legendary battle setup
    setflag 0x904 @ Can't run or catch, cleared after battle
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_HONECLAWS
    setvar 0x8001 MOVE_PLASMAFISTS
    setvar 0x8002 MOVE_KNOCKOFF
    setvar 0x8003 MOVE_BRICKBREAK
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_ZERAORA 70 ITEM_SITRUS_BERRY
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    @ After battle
    cry SPECIES_ZERAORA 0x0
    msgbox gText_MimmettJungle_Zeraora_AfterBattle MSG_NORMAL
    waitcry
    compare PLAYERFACING UP
    if equal _call ZeraoraJumpsAroundPlayer
    applymovement LASTTALKED m_ZeraoraLeaves
    waitmovement LASTTALKED
    setflag 0x054 @ Zeraora Calmed
    @ Set up roaming
    msgbox gText_MimmettJungle_Zeraora_Roaming MSG_NORMAL
    setvar 0x8000 SPECIES_ZERAORA
    setvar 0x8001 70
    setvar 0x8002 0x1 @ Can roam on land
    setvar 0x8003 0x0 @ Cannot roam on water
    special 0x129 @ Create roaming Pokemon
    hidesprite LASTTALKED
    end

ZeraoraChoseNo:
    msgbox gText_MimmettJungle_Zeraora_ChoseNo MSG_NORMAL
    end

ZeraoraJumpsAroundPlayer:
    applymovement LASTTALKED m_ZeraoraGoesAroundPlayer
    waitmovement LASTTALKED
    return

.global SignScript_MimmettJungle_PokerusSign
SignScript_MimmettJungle_PokerusSign:
    msgbox gText_MimmettJungle_PokerusSign MSG_SIGN
    end

.global SignScript_MimmettJungle_SwampSign
SignScript_MimmettJungle_SwampSign:
    msgbox gText_MimmettJungle_SwampSign MSG_SIGN
    end

m_ZeraoraGoesAroundPlayer: .byte run_right, run_down, jump_2_down, run_left, end_m
m_ZeraoraLeaves: .byte run_down, run_down, run_down, run_down, run_down, run_down, end_m
