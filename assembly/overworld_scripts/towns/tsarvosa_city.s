.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_TsarvosaCity
MapScript_TsarvosaCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_TsarvosaCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_TsarvosaCity_FlightSpot:
    setworldmapflag 0x899 @ Visited Tsarvosa City
    end

.global EventScript_TsarvosaCity_Captain
EventScript_TsarvosaCity_Captain:
    npcchatwithmovement gText_TsarvosaCity_Captain m_LookUp
    end

.global EventScript_TsarvosaCity_DockWorker
EventScript_TsarvosaCity_DockWorker:
    npcchatwithmovement gText_TsarvosaCity_DockWorker m_LookLeft
    end

.global EventScript_TsarvosaCity_FightingDojoFan
EventScript_TsarvosaCity_FightingDojoFan:
    npcchat gText_TsarvosaCity_FightingDojoFan
    end

.global EventScript_TsarvosaCity_DirectionsGirl
EventScript_TsarvosaCity_DirectionsGirl:
    npcchat gText_TsarvosaCity_DirectionsGirl
    end

.global EventScript_TsarvosaCity_GymFan
EventScript_TsarvosaCity_GymFan:
    npcchatwithmovement gText_TsarvosaCity_GymFan m_LookDown
    end

.global EventScript_TsarvosaCity_GymsFeudMan
EventScript_TsarvosaCity_GymsFeudMan:
    npcchat gText_TsarvosaCity_GymsFeudMan
    end

.global EventScript_TsarvosaCity_MarketWoman
EventScript_TsarvosaCity_MarketWoman:
    npcchat gText_TsarvosaCity_MarketWoman 
    end

.global EventScript_TsarvosaCity_OldMan
EventScript_TsarvosaCity_OldMan:
    npcchat gText_TsarvosaCity_OldMan
    end

.global EventScript_TsarvosaCity_MimmettJungleGirl
EventScript_TsarvosaCity_MimmettJungleGirl:
    npcchat gText_TsarvosaCity_MimmettJungleGirl
    end

.global SignScript_TsarvosaCity_TownPlacard
SignScript_TsarvosaCity_TownPlacard:
    msgbox gText_TsarvosaCity_TownPlacard MSG_SIGN
    end

@ Pokemon Center
.global MapScript_TsarvosaCity_PokemonCenter
MapScript_TsarvosaCity_PokemonCenter:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_TsarvosaCity_PokemonCenter_SetHealingSpot:
    sethealingplace 0xB
    end

.global EventScript_TsarvosaCity_PokemonCenter_FatGuy
EventScript_TsarvosaCity_PokemonCenter_FatGuy:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_FatGuy m_LookLeft
    end

.global EventScript_TsarvosaCity_PokemonCenter_Policeman
EventScript_TsarvosaCity_PokemonCenter_Policeman:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_Policeman m_LookDown
    end

.global EventScript_TsarvosaCity_PokemonCenter_Girl
EventScript_TsarvosaCity_PokemonCenter_Girl:
    npcchatwithmovement gText_TsarvosaCity_PokemonCenter_Girl m_LookLeft
    end
