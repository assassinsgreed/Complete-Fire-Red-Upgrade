.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoCityGym
MapScript_HeleoCityGym:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_HeleoCityGym
    .byte MAP_SCRIPT_TERMIN

LevelScripts_HeleoCityGym:
    @ Trigger this when the Ferrox story var indicates Alistair has been talked to (ie. always, when this gym is accessible)  
    levelscript 0x4052 0x3 LevelScripts_HeleoCityGym_SetPlayerFacing
    .hword LEVEL_SCRIPT_TERMIN

LevelScripts_HeleoCityGym_SetPlayerFacing:
    compare PLAYERFACING DOWN
    if equal _goto FaceDown
    compare PLAYERFACING UP
    if equal _goto FaceUp
    compare PLAYERFACING LEFT
    if equal _goto FaceLeft
    compare PLAYERFACING RIGHT
    if equal _goto FaceRight
    end

FaceLeft:
    spriteface PLAYER LEFT
    spriteface LASTTALKED RIGHT @ Last talked is one of the Castform
    end

FaceRight:
    spriteface PLAYER RIGHT
    spriteface LASTTALKED LEFT 
    end

FaceUp:
    spriteface PLAYER UP
    spriteface LASTTALKED DOWN 
    end

FaceDown:
    spriteface PLAYER DOWN
    spriteface LASTTALKED UP 
    end

.global EventScript_HeleoGym_CastformWater
EventScript_HeleoGym_CastformWater:
    call CastformCommon
    msgbox gText_HeleoCityGym_CastformSunnyDay MSG_NORMAL
    call SetWeatherSunny
    call CastformCommon_WeatherChanging
    warpmuted 1 93 0xFF 0x4000 0x4001 @ Warp to same spot in drained map
    end

.global EventScript_HeleoGym_CastformDrained
EventScript_HeleoGym_CastformDrained:
    call CastformCommon
    msgbox gText_HeleoCityGym_CastformRainDance MSG_NORMAL
    call SetWeatherRain
    call CastformCommon_WeatherChanging
    warpmuted 1 92 0xFF 0x4000 0x4001 @ Warp to same spot in flooded map
    end

CastformCommon:
    lock
    faceplayer
    checksound
    cry SPECIES_CASTFORM 0x0
    waitcry
    return

CastformCommon_WeatherChanging:
    pause DELAY_1SECOND
    fadescreenswapbuffers 0x1
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    return
