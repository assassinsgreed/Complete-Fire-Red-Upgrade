.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route8
MapScript_Route8:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route8_SetWeather
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route8_SetWeather:
    @ Check player position, to see if they spawned from the north gate or fisherman's hut
    getplayerpos 0x4000 0x4001
    compare 0x4001 0xB @ Either north gate (0xA) or Fisherman's hut (0xB), no need to set weather
    if greaterthan _goto TileScript_Route8_SetWeather    
    end

.global TileScript_Route8_ClearWeather
TileScript_Route8_ClearWeather:
    call SetWeatherClear
    End

.global TileScript_Route8_SetWeather
TileScript_Route8_SetWeather:
    call SetWeatherFog
    random 0x64 @ Between 0 and 100
    compare LASTRESULT 0xF @ "15"
    if lessorequal _goto SetWeatherMistyAndEnd
    compare LASTRESULT 0x32 @ "50"
    if greaterorequal _goto SetWeatherRainyAndEnd
    goto TileScript_Route8_ClearWeather

SetWeatherMistyAndEnd:
    call SetWeatherFog
    goto End

SetWeatherRainyAndEnd:
    call SetWeatherRain
    goto End

.global SignScript_Route8_FishermanCommittee
SignScript_Route8_FishermanCommittee:
    msgbox gText_Route8_FishingCommittee MSG_SIGN
    end

.global SignScript_Route8_TrainerTips_LongGrass
SignScript_Route8_TrainerTips_LongGrass:
    msgbox gText_Route8_LongGrass MSG_SIGN
    end

.global SignScript_Route8_TrainerTips_FoggyWeather
SignScript_Route8_TrainerTips_FoggyWeather:
    msgbox gText_Route8_FoggyWeather MSG_SIGN
    end

.global EventScript_Route8_SandygastEncounter1
EventScript_Route8_SandygastEncounter1:
    call SandygastEncounter
    setflag 0xE0C
    end

.global EventScript_Route8_SandygastEncounter2
EventScript_Route8_SandygastEncounter2:
    call SandygastEncounter
    setflag 0xE0D
    end

SandygastEncounter:
    lock
    checksound
    cry SPECIES_SANDYGAST 0x0
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    wildbattle SPECIES_SANDYGAST 0x14 0x0 @ Level 20
    hidesprite LASTTALKED
    release
    return

.global EventScript_Route8_Swampertite
EventScript_Route8_Swampertite:
    finditem ITEM_SWAMPERTITE 0x1
    end

.global EventScript_Route8_FindTM40AerialAce
EventScript_Route8_FindTM40AerialAce:
    setvar CHOSEN_ITEM ITEM_TM40
    call ItemScript_Common_FindTM
    end

.global EventScript_Route8_FindTM48Round
EventScript_Route8_FindTM48Round:
    setvar CHOSEN_ITEM ITEM_TM48
    call ItemScript_Common_FindTM
    end

.global EventScript_Route8_FindTM34SludgeWave
EventScript_Route8_FindTM34SludgeWave:
    setvar CHOSEN_ITEM ITEM_TM34
    call ItemScript_Common_FindTM
    end
