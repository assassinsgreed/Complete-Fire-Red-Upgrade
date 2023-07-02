.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_ForgottenManse_Exterior
MapScript_ForgottenManse_Exterior:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_ForgottenManseExterior_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManseExterior_SetWeather
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManseExterior_FlightFlag:
    setworldmapflag 0x8A8 @ Been to Forgotten Manse
    end

MapEntryScript_ForgottenManseExterior_SetWeather:
    random 0xA @ Between 0 and 10
    compare LASTRESULT 0x8
    if lessorequal _call SetWeatherFog
    getplayerpos 0x4003 0x4004
    compare 0x4003 0xA @ On Manse door
    if equal _goto SetDoorOpen
    end

.global MapScript_ForgottenManse_Basement
MapScript_ForgottenManse_Basement:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManseBasement_SetTerrain
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManseBasement_SetTerrain:
    call SetWeatherThinFog @ No battle effect, just visual
    call SetMistyTerrain
    end

.global SignScript_ForgottenManseExterior_MansePlacard
SignScript_ForgottenManseExterior_MansePlacard:
    msgbox gText_ForgottenManseExterior_Sign MSG_SIGN
    end

.global EventScript_ForgottenManseExterior_FrontDoorKey
EventScript_ForgottenManseExterior_FrontDoorKey:
    finditem ITEM_MANSE_KEY 0x1
    end

.global TileScript_ForgottenManseExterior_FrontDoor
TileScript_ForgottenManseExterior_FrontDoor:
    lock
    compareplayerfacing INTERNAL_DOWN @ Exiting the Manse
    if equal _goto End
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    checkitem ITEM_MANSE_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto OpenDoor
    pause 0x14
    msgbox gText_ForgottenManse_DoorLocked MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement ALLEVENTS
    release
    end

OpenDoor:
    playse 0x8 @ Door opening
    waitse
    pause 0x14
    goto SetDoorOpen

SetDoorOpen:
    setmaptile 0xA 0x9 0x293 0x0 @ set to open door sprite
    special 0x8E
    setvar 0x4001 0x1 @ Stop this event from firing again until the player revisits the map
    release
    end

.global SignScript_ForgottenManse_Journal1
SignScript_ForgottenManse_Journal1:
    msgbox gText_ForgottenManse_Journal1 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal2
SignScript_ForgottenManse_Journal2:
    msgbox gText_ForgottenManse_Journal2 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal3
SignScript_ForgottenManse_Journal3:
    msgbox gText_ForgottenManse_Journal3 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal4
SignScript_ForgottenManse_Journal4:
    msgbox gText_ForgottenManse_Journal4 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal5
SignScript_ForgottenManse_Journal5:
    msgbox gText_ForgottenManse_Journal5 MSG_SIGN
    end

.global SignScript_ForgottenManse_Journal6
SignScript_ForgottenManse_Journal6:
    msgbox gText_ForgottenManse_Journal6 MSG_SIGN
    end

.global EventScript_ForgottenManseExterior_ChannelerMona
EventScript_ForgottenManseExterior_ChannelerMona:
    trainerbattle0 0x0 0x79 0x0 gText_ForgottenManseExterior_ChannelerMona_Intro gText_ForgottenManseExterior_ChannelerMona_Defeat
    msgbox gText_ForgottenManseExterior_ChannelerMona_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseExterior_BurglarChad
EventScript_ForgottenManseExterior_BurglarChad:
    trainerbattle0 0x0 0x7A 0x0 gText_ForgottenManseExterior_BurglarChad_Intro gText_ForgottenManseExterior_BurglarChad_Defeat
    msgbox gText_ForgottenManseExterior_BurglarChad_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseExterior_NurseLucy
EventScript_ForgottenManseExterior_NurseLucy:
    faceplayer
    checktrainerflag 0x57B
    if SET _goto NurseLucyHeal
    trainerbattle1 0x0 0x7B 0x0 gText_ForgottenManseExterior_NurseLucy_Intro gText_ForgottenManseExterior_NurseLucy_Defeat NurseLucyHeal
    goto NurseLucyHeal

NurseLucyHeal:
    msgbox gText_ForgottenManseExterior_NurseLucy_Chat MSG_NORMAL
    call PlayerHeal
    msgbox gText_ForgottenManseExterior_NurseLucy_HealingComplete MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_Sablenite
EventScript_ForgottenManse1F_Sablenite:
    finditem ITEM_SABLENITE 0x1
    end

.global EventScript_ForgottenManse2F_TM60Hex
EventScript_ForgottenManse2F_TM60Hex:
    setvar CHOSEN_ITEM ITEM_TM60
    call ItemScript_Common_FindTM
    end

.global EventScript_ForgottenManseBF1_TM61WillOWisp
EventScript_ForgottenManseBF1_TM61WillOWisp:
    setvar CHOSEN_ITEM ITEM_TM61
    call ItemScript_Common_FindTM
    end

.global EventScript_ForgottenManse1F_BeautyLulu
EventScript_ForgottenManse1F_BeautyLulu:
    trainerbattle0 0x0 0x7C 0x0 gText_ForgottenManse1F_BeautyLulu_Intro gText_ForgottenManse1F_BeautyLulu_Defeat
    msgbox gText_ForgottenManse1F_BeautyLulu_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_ChannelerEsther
EventScript_ForgottenManse1F_ChannelerEsther:
    trainerbattle0 0x0 0x7D 0x0 gText_ForgottenManse1F_ChannelerEsther_Intro gText_ForgottenManse1F_ChannelerEsther_Defeat
    msgbox gText_ForgottenManse1F_ChannelerEsther_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_SuperNerdAustin
EventScript_ForgottenManse1F_SuperNerdAustin:
    trainerbattle0 0x0 0x7E 0x0 gText_ForgottenManse1F_SuperNerdAustin_Intro gText_ForgottenManse1F_SuperNerdAustin_Defeat
    msgbox gText_ForgottenManse1F_SuperNerdAustin_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_BurglarJacques
EventScript_ForgottenManse1F_BurglarJacques:
    trainerbattle0 0x0 0x7F 0x0 gText_ForgottenManse1F_BurglarJacques_Intro gText_ForgottenManse1F_BurglarJacques_Defeat
    msgbox gText_ForgottenManse1F_BurglarJacques_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_PsychicCorbin
EventScript_ForgottenManse1F_PsychicCorbin:
    trainerbattle0 0x0 0x80 0x0 gText_ForgottenManse1F_PsychicCorbin_Intro gText_ForgottenManse1F_PsychicCorbin_Defeat
    msgbox gText_ForgottenManse1F_PsychicCorbin_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_BurglarBarry
EventScript_ForgottenManse2F_BurglarBarry:
    trainerbattle0 0x0 0x81 0x0 gText_ForgottenManse2F_BurglarBarry_Intro gText_ForgottenManse2F_BurglarBarry_Defeat
    msgbox gText_ForgottenManse2F_BurglarBarry_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_YoungsterChester
EventScript_ForgottenManse2F_YoungsterChester:
    trainerbattle0 0x0 0x82 0x0 gText_ForgottenManse2F_YoungsterChester_Intro gText_ForgottenManse2F_YoungsterChester_Defeat
    msgbox gText_ForgottenManse2F_YoungsterChester_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse2F_ChannelerElaine
EventScript_ForgottenManse2F_ChannelerElaine:
    trainerbattle0 0x0 0x83 0x0 gText_ForgottenManse2F_ChannelerElaine_Intro gText_ForgottenManse2F_ChannelerElaine_Defeat
    msgbox gText_ForgottenManse2F_ChannelerElaine_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_SuperNerdGlenn
EventScript_ForgottenManseBF1_SuperNerdGlenn:
    trainerbattle0 0x0 0x84 0x0 gText_ForgottenManseBF1_SuperNerdGlenn_Intro gText_ForgottenManseBF1_SuperNerdGlenn_Defeat
    msgbox gText_ForgottenManseBF1_SuperNerdGlenn_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_BurglarPeter
EventScript_ForgottenManseBF1_BurglarPeter:
    trainerbattle0 0x0 0x85 0x0 gText_ForgottenManseBF1_BurglarPeter_Intro gText_ForgottenManseBF1_BurglarPeter_Defeat
    msgbox gText_ForgottenManseBF1_BurglarPeter_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_PsychicNoelle
EventScript_ForgottenManseBF1_PsychicNoelle:
    trainerbattle0 0x0 0x86 0x0 gText_ForgottenManseBF1_PsychicNoelle_Intro gText_ForgottenManseBF1_PsychicNoelle_Defeat
    msgbox gText_ForgottenManseBF1_PsychicNoelle_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManseBF1_ChannelerSana
EventScript_ForgottenManseBF1_ChannelerSana:
    trainerbattle0 0x0 0x87 0x0 gText_ForgottenManseBF1_ChannelerSana_Intro gText_ForgottenManseBF1_ChannelerSana_Defeat
    msgbox gText_ForgottenManseBF1_ChannelerSana_Chat MSG_NORMAL
    end

.global EventScript_ForgottenManse1F_StorageKey
EventScript_ForgottenManse1F_StorageKey:
    finditem ITEM_STORAGE_KEY 0x1
    end
