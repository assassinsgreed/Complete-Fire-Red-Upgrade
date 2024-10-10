.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route18_SwimmerJasper
EventScript_Route18_SwimmerJasper:
    trainerbattle0 0x0 314 0x0 gText_Route18_SwimmerJasper_Intro gText_Route18_SwimmerJasper_Defeat
    msgbox gText_Route18_SwimmerJasper_Chat MSG_NORMAL
    end

.global EventScript_Route18_TriathleteDeborah
EventScript_Route18_TriathleteDeborah:
    trainerbattle0 0x0 315 0x0 gText_Route18_TriathleteDeborah_Intro gText_Route18_TriathleteDeborah_Defeat
    msgbox gText_Route18_TriathleteDeborah_Chat MSG_NORMAL
    end

.global EventScript_Route18_SwimmerJudie
EventScript_Route18_SwimmerJudie:
    trainerbattle0 0x0 316 0x0 gText_Route18_SwimmerJudie_Intro gText_Route18_SwimmerJudie_Defeat
    msgbox gText_Route18_SwimmerJudie_Chat MSG_NORMAL
    end

.global EventScript_Route18_BirdKeeperKirk
EventScript_Route18_BirdKeeperKirk:
    trainerbattle0 0x0 317 0x0 gText_Route18_BirdKeeperKirk_Intro gText_Route18_BirdKeeperKirk_Defeat
    msgbox gText_Route18_BirdKeeperKirk_Chat MSG_NORMAL
    end

.global EventScript_Route18_LassEmma
EventScript_Route18_LassEmma:
    trainerbattle0 0x0 318 0x0 gText_Route18_LassEmma_Intro gText_Route18_LassEmma_Defeat
    msgbox gText_Route18_LassEmma_Chat MSG_NORMAL
    end

.global EventScript_Route18_BlackbeltRohan
EventScript_Route18_BlackbeltRohan:
    trainerbattle0 0x0 319 0x0 gText_Route18_BlackbeltRohan_Intro gText_Route18_BlackbeltRohan_Defeat
    msgbox gText_Route18_BlackbeltRohan_Chat MSG_NORMAL
    end

.global EventScript_Route18_TM31_BrickBreak
EventScript_Route18_TM31_BrickBreak:
    setvar CHOSEN_ITEM ITEM_TM31
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_TM99_DazzlingGleam
EventScript_Route18_TM99_DazzlingGleam:
    setvar CHOSEN_ITEM ITEM_TM99
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_TM92_TrickRoom
EventScript_Route18_TM92_TrickRoom:
    setvar CHOSEN_ITEM ITEM_TM92
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_Galladite
EventScript_Route18_Galladite:
    finditem ITEM_GALLADITE 0x1
    end

.global EventScript_Route18_Fisherman
EventScript_Route18_Fisherman:
    npcchatwithmovement gText_Route18_Fisherman m_LookDown
    end

.global SignScript_Route18_PreserveFlowersSign
SignScript_Route18_PreserveFlowersSign:
    msgbox gText_Route18_PreserveFlowersSign MSG_SIGN
    end

.global SignScript_Route18_OrichelleGarden
SignScript_Route18_OrichelleGarden:
    msgbox gText_Route18_OrichelleGardenSign MSG_SIGN
    end

.global EventScript_Route18_ShayminFormChangeGirl
EventScript_Route18_ShayminFormChangeGirl:
    faceplayer
    checkflag 0x25A @ Gracidea given
    if SET _goto ExplainGracideaUsage
    msgbox gText_Route18_ShayminGirl_IntroductoryText MSG_NORMAL
    setvar 0x8005 SPECIES_SHAYMIN
    callasm HasSpeciesInParty
    compare LASTRESULT TRUE
    if TRUE _goto GiveGracidea
    applymovement LASTTALKED m_LookLeft
    end

GiveGracidea:
    msgbox gText_Route18_ShayminGirl_ShayminRecognized MSG_NORMAL
    obtainitem ITEM_GRACIDEA 0x1
    setflag 0x25A @ Gracidea given
    goto ExplainGracideaUsage 

ExplainGracideaUsage:
    msgbox gText_Route18_ShayminGirl_GracideaExplanation MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_Route18_RestWoman
EventScript_Route18_RestWoman:
    faceplayer
    msgbox gText_Route18_RestWoman_RestPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto Rest
    msgbox gText_Route18_RestWoman_RestNo MSG_NORMAL
    applymovement LASTTALKED m_LookUp
    end

Rest:
    msgbox gText_Route18_RestWoman_RestYes MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route18_RestWoman_AfterRest MSG_NORMAL
    applymovement LASTTALKED m_LookUp
    end

.global EventScript_Route18_LocalLegendGirl
EventScript_Route18_LocalLegendGirl:
    npcchatwithmovement gText_Route18_LocalLegendGirl m_LookRight
    end

// Orichelle Garden
.global MapScript_OrichelleGarden
MapScript_OrichelleGarden:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_OrichelleGarden_SetWorldMapFlag
    mapscript MAP_SCRIPT_ON_RESUME HideLegendary
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_OrichelleGarden_SetWorldMapFlag:
    setworldmapflag 0x8AD @ Been to Orichelle Garden
    end

HideLegendary:
    checkflag 0x4B
    if SET _call HideShaymin
    end

HideShaymin:
    hidesprite 3
    end

.global EventScript_OrichelleGarden_Shaymin
EventScript_OrichelleGarden_Shaymin:
    faceplayer
    cry SPECIES_SHAYMIN 0x0
    waitcry
    msgbox gtext_OrichelleGarden_ShayminBattleStart MSG_NORMAL
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_DAZZLINGGLEAM
    setvar 0x8001 MOVE_SYNTHESIS
    setvar 0x8002 MOVE_SEEDBOMB
    setvar 0x8003 MOVE_EARTHPOWER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_SHAYMIN 50 ITEM_NONE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedShaymin
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call FledFromShaymin
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtShaymin
    end

DefeatedShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminDefeated MSG_NORMAL
    end

FledFromShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminFledFromBattle MSG_NORMAL
    end

CaughtShaymin:
    setflag 0x4B @ Shaymin hidden
    end
