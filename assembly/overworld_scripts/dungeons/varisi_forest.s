.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_VarisiForest_FlightSpot
MapScript_VarisiForest_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_VarisiForest_FlightFlag
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_VarisiForest_FlightFlag:
    setworldmapflag 0x8A4
    end

HideTrapPokemon:
    checkflag 0xE01
    if SET _call HideFoongus1
    checkflag 0xE02
    if SET _call HideFoongus2
    end

HideFoongus1:
    hidesprite 8
    return

HideFoongus2:
    hidesprite 9
    return

.global EventScript_VarisiForest_BugCatcherKendell
EventScript_VarisiForest_BugCatcherKendell:
    trainerbattle0 0x0 0x8 0x0 gText_VarisiForest_BugCatcherKendell_Intro gText_VarisiForest_BugCatcherKendell_Defeat
    msgbox gText_VarisiForest_BugCatcherKendell_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_BugCatcherBraden
EventScript_VarisiForest_BugCatcherBraden:
    trainerbattle0 0x0 0x9 0x0 gText_VarisiForest_BugCatcherBraden_Intro gText_VarisiForest_BugCatcherBraden_Defeat
    msgbox gText_VarisiForest_BugCatcherBraden_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_LassBreanna
EventScript_VarisiForest_LassBreanna:
    trainerbattle0 0x0 0xa 0x0 gText_VarisiForest_LassBreanna_Intro gText_VarisiForest_LassBreanna_Defeat
    msgbox gText_VarisiForest_LassBreanna_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_LassMimi
EventScript_VarisiForest_LassMimi:
    trainerbattle0 0x0 0xb 0x0 gText_VarisiForest_LassMimi_Intro gText_VarisiForest_LassMimi_Defeat
    msgbox gText_VarisiForest_LassMimi_Chat MSG_NORMAL
    end

.global EventScript_VarisiForest_TrainerTip
EventScript_VarisiForest_TrainerTip:
    npcchat gText_VarisiForest_TrainerTip
    end

.global EventScript_VarisiForest_PoisonWarning
EventScript_VarisiForest_PoisonWarning:
    lock
    faceplayer
    msgbox gText_VarisiForest_PoisonWarning MSG_NORMAL
    checkflag 0x231 @ Has received Antidote gift
    if NOT_SET _goto EventScript_VarisiForest_AntidoteGift
    goto EventScript_VarisiForest_PoisonWarningEnd

EventScript_VarisiForest_AntidoteGift:
    msgbox gText_VarisiForest_AntidoteGift MSG_NORMAL
    obtainitem ITEM_ANTIDOTE 0x1
    setflag 0x231 @ Has received Antidote gift
    goto EventScript_VarisiForest_PoisonWarningEnd
    
EventScript_VarisiForest_PoisonWarningEnd:
    applymovement 0x1 m_LookRight
	waitmovement ALLEVENTS
    release
    end

.global EventScript_VarisiForest_SurprisedTrainer
EventScript_VarisiForest_SurprisedTrainer:
    npcchat gText_VarisiForest_SurprisedTrainer
    end

.global EventScript_VarisiForest_TimeOfDay
EventScript_VarisiForest_TimeOfDay:
    npcchatwithmovement gText_VarisiForest_TimeOfDay m_LookRight
    end

.global EventScript_VarisiForest_FriendlyTrainer
EventScript_VarisiForest_FriendlyTrainer:
    npcchatwithmovement gText_VarisiForest_FriendlyTrainer m_LookUp
    end

.global EventScript_VarisiForest_FoongusEncounter1
EventScript_VarisiForest_FoongusEncounter1:
    setflag 0xE01
    call FoongusEncounter
    end

.global EventScript_VarisiForest_FoongusEncounter2
EventScript_VarisiForest_FoongusEncounter2:
    setflag 0xE02
    call FoongusEncounter
    end

FoongusEncounter:
    lock
    checksound
    cry SPECIES_FOONGUS 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Common_FoongusOrAmoongussTrap MSG_KEEPOPEN
    wildbattle SPECIES_FOONGUS 0x7 0x0
    hidesprite LASTTALKED
    release
    return

.global SignScript_VarisiForest_AntidoteSign
SignScript_VarisiForest_AntidoteSign:
    msgbox gText_VarisiForest_AntidoteSign MSG_SIGN
    end

.global SignScript_VarisiForest_RhodanziSign
SignScript_VarisiForest_RhodanziSign:
    msgbox gText_VarisiForest_RhodanziSign MSG_SIGN
    end

.global SignScript_VarisiForest_TrainerTips
SignScript_VarisiForest_TrainerTips:
    msgbox gText_VarisiForest_TrainerTips MSG_SIGN
    end
