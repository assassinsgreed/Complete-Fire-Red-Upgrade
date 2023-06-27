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
