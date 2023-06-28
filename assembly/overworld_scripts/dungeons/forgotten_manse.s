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
    end

.global MapScript_ForgottenManse_Basement
MapScript_ForgottenManse_Basement:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_ForgottenManseBasement_SetTerrain
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ForgottenManseBasement_SetTerrain:
    call SetWeatherThinFog @ No battle effect, just visual
    call SetMistyTerrain
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
