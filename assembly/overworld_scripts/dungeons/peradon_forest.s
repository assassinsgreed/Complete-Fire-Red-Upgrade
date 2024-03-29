.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_PerdaonForest
MapScript_PerdaonForest:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_PeradonForest_FlightFlag
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_PeradonForest_FlightFlag:
    setworldmapflag 0x8AA
    end

HideTrapPokemon:
    checkflag 0xE13
    if SET _call HideAmoonguss1
    checkflag 0xE14
    if SET _call HideAmoonguss2
    checkflag 0xE15
    if SET _call HideAmoonguss3
    checkflag 0xE16
    if SET _call HideFoongus1
    checkflag 0xE17
    if SET _call HideFoongus2
    end

HideAmoonguss1:
    hidesprite 5
    return

HideAmoonguss2:
    hidesprite 6
    return

HideAmoonguss3:
    hidesprite 8
    return

HideFoongus1:
    hidesprite 7
    return

HideFoongus2:
    hidesprite 9
    return


.global EventScript_PeradonForest_GuardHouse_Guard
EventScript_PeradonForest_GuardHouse_Guard:
    npcchat gText_PeradonForest_GuardHouse_Guard
    end

.global EventScript_PeradonForest_GuardHouse_Girl
EventScript_PeradonForest_GuardHouse_Girl:
    npcchat gText_PeradonForest_GuardHouse_Girl
    end

.global EventScript_PeradonForest_AmoongussEncounter1
EventScript_PeradonForest_AmoongussEncounter1:
    setflag 0xE13
    call AmoongussEncounter
    end

.global EventScript_PeradonForest_AmoongussEncounter2
EventScript_PeradonForest_AmoongussEncounter2:
    setflag 0xE14
    call AmoongussEncounter
    end

.global EventScript_PeradonForest_AmoongussEncounter3
EventScript_PeradonForest_AmoongussEncounter3:
    setflag 0xE15
    call AmoongussEncounter
    end

.global EventScript_PeradonForest_FoongusEncounter1
EventScript_PeradonForest_FoongusEncounter1:
    setflag 0xE16
    call FoongusEncounter
    end

.global EventScript_PeradonForest_FoongusEncounter2
EventScript_PeradonForest_FoongusEncounter2:
    setflag 0xE17
    call FoongusEncounter
    end

AmoongussEncounter:
    lock
    checksound
    cry SPECIES_AMOONGUSS 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Common_FoongusOrAmoongussTrap MSG_KEEPOPEN
    wildbattle SPECIES_AMOONGUSS 40 0x0
    hidesprite LASTTALKED
    release
    return

FoongusEncounter:
    lock
    checksound
    cry SPECIES_FOONGUS 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Common_FoongusOrAmoongussTrap MSG_KEEPOPEN
    wildbattle SPECIES_FOONGUS 38 0x0
    hidesprite LASTTALKED
    release
    return

.global EventScript_PeradonForest_Heracronite
EventScript_PeradonForest_Heracronite:
    finditem ITEM_HERACRONITE 0x1
    end

.global EventScript_PeradonForest_TM86_GrassKnot
EventScript_PeradonForest_TM86_GrassKnot:
    setvar CHOSEN_ITEM ITEM_TM86
    call ItemScript_Common_FindTM
    end

.global EventScript_PeradonForest_PokefanClark
EventScript_PeradonForest_PokefanClark:
    trainerbattle0 0x0 235 0x0 gText_PeradonForest_PokefanClark_Intro gText_PeradonForest_PokefanClark_Defeat
    msgbox gText_PeradonForest_PokefanClark_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_CollectorFernando
EventScript_PeradonForest_CollectorFernando:
    trainerbattle0 0x0 236 0x0 gText_PeradonForest_CollectorFernando_Intro gText_PeradonForest_CollectorFernando_Defeat
    msgbox gText_PeradonForest_CollectorFernando_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_BugCatcherLyle
EventScript_PeradonForest_BugCatcherLyle:
    compare PLAYERFACING LEFT
    if equal _call LyleAndEricaLookRight
    @ Perform a double battle with Lyle & Erica's teams (237 and 238), referencing their overworld NPC IDs (17 and 18), with their respective intro/defeat/chat text
    trainerbattle11 0x0 237 238 17 18 0x0 gText_PeradonForest_BugCatcherLyle_Intro gText_PeradonForest_BeautyErica_Intro gText_PeradonForest_BugCatcherLyle_Defeat gText_PeradonForest_BeautyErica_Defeat gText_PeradonForest_BugCatcherLyle_Chat gText_PeradonForest_BeautyErica_Chat
    msgbox gText_PeradonForest_BugCatcherLyle_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_BeautyErica
EventScript_PeradonForest_BeautyErica:
    compare PLAYERFACING RIGHT
    if equal _call LyleAndEricaLookLeft
    @ Perform a double battle with Lyle & Erica's teams (237 and 238), referencing their overworld NPC IDs (17 and 18), with their respective intro/defeat/chat text
    trainerbattle11 0x0 237 238 17 18 0x0 gText_PeradonForest_BugCatcherLyle_Intro gText_PeradonForest_BeautyErica_Intro gText_PeradonForest_BugCatcherLyle_Defeat gText_PeradonForest_BeautyErica_Defeat gText_PeradonForest_BugCatcherLyle_Chat gText_PeradonForest_BeautyErica_Chat
    msgbox gText_PeradonForest_BeautyErica_Chat MSG_NORMAL
    end

LyleAndEricaLookRight:
    applymovement 17 m_LookRight
    applymovement 18 m_LookRight
    waitmovement ALLEVENTS
    return

LyleAndEricaLookLeft:
    applymovement 17 m_LookLeft
    applymovement 18 m_LookLeft
    waitmovement ALLEVENTS
    return

.global EventScript_PeradonForest_PainterSheena
EventScript_PeradonForest_PainterSheena:
    trainerbattle0 0x0 239 0x0 gText_PeradonForest_PainterSheena_Intro gText_PeradonForest_PainterSheena_Defeat
    msgbox gText_PeradonForest_PainterSheena_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_CamperRupert
EventScript_PeradonForest_CamperRupert:
    trainerbattle0 0x0 240 0x0 gText_PeradonForest_CamperRupert_Intro gText_PeradonForest_CamperRupert_Defeat
    msgbox gText_PeradonForest_CamperRupert_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_ScientistSean
EventScript_PeradonForest_ScientistSean:
    trainerbattle0 0x0 241 0x0 gText_PeradonForest_ScientistSean_Intro gText_PeradonForest_ScientistSean_Defeat
    msgbox gText_PeradonForest_ScientistSean_Chat MSG_NORMAL
    end

.global SignScript_PeradonForest_LaplazExit
SignScript_PeradonForest_LaplazExit:
    msgbox gText_PeradonForest_LaplazExit MSG_SIGN
    end

.global SignScript_PeradonForest_LakeLaplazExit
SignScript_PeradonForest_LakeLaplazExit:
    msgbox gText_PeradonForest_LakeLaplazExit MSG_SIGN
    end

.global SignScript_PeradonForest_LowLevelMoreExpTrainerTips
SignScript_PeradonForest_LowLevelMoreExpTrainerTips:
    msgbox gText_PeradonForest_LowLevelMoreExpTrainerTips MSG_SIGN
    end

.global EventScript_PeradonForest_TM81_XScsissor
EventScript_PeradonForest_TM81_XScsissor:
    setvar CHOSEN_ITEM ITEM_TM81
    call ItemScript_Common_FindTM
    end

.global EventScript_PeradonForest_RockerRaphael
EventScript_PeradonForest_RockerRaphael:
    trainerbattle0 0x0 242 0x0 gText_PeradonForest_RockerRaphael_Intro gText_PeradonForest_RockerRaphael_Defeat
    msgbox gText_PeradonForest_RockerRaphael_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_ChanellerRenee
EventScript_PeradonForest_ChanellerRenee:
    trainerbattle0 0x0 243 0x0 gText_PeradonForest_ChanellerRenee_Intro gText_PeradonForest_ChanellerRenee_Defeat
    msgbox gText_PeradonForest_ChanellerRenee_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_BlackbeltBrad
EventScript_PeradonForest_BlackbeltBrad:
    trainerbattle0 0x0 244 0x0 gText_PeradonForest_BlackbeltBrad_Intro gText_PeradonForest_BlackbeltBrad_Defeat
    msgbox gText_PeradonForest_BlackbeltBrad_Chat MSG_NORMAL
    end

.global EventScript_PeradonForest_RuinManiacAlex
EventScript_PeradonForest_RuinManiacAlex:
    trainerbattle0 0x0 245 0x0 gText_PeradonForest_RuinManiacAlex_Intro gText_PeradonForest_RuinManiacAlex_Defeat
    msgbox gText_PeradonForest_RuinManiacAlex_Chat MSG_NORMAL
    end
