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

.global EventScript_ForgottenManse1F_StorageKey
EventScript_ForgottenManse1F_StorageKey:
    finditem ITEM_STORAGE_KEY 0x1
    end
