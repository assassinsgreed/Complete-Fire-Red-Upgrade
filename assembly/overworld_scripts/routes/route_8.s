.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route8
MapScript_Route8:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route8_SetWeather
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route8_SetWeather:
    @ Check player position, to see if they spawned from the north gate or fisherman's hut
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2D @ Above the weather stairs, no need to set weather
    if greaterthan _goto TileScript_Route8_SetWeather
    end

HideTrapPokemon:
    checkflag 0xE0C
    if SET _call HideSandygast1
    checkflag 0xE0D
    if SET _call HideSandygast2
    end

HideSandygast1:
    hidesprite 14
    return

HideSandygast2:
    hidesprite 15
    return

.global TileScript_Route8_ClearWeather
TileScript_Route8_ClearWeather:
    setvar 0x400E 0x0 @ Enable weather setting again
    call SetWeatherClear
    End

.global TileScript_Route8_SetWeather
TileScript_Route8_SetWeather:
    compare 0x400E 0x1
    if equal _goto End
    setvar 0x400E 0x1 @ Prevent future weather until var is cleared
    call SetWeatherFog
    random 0x64 @ Between 0 and 100
    compare LASTRESULT 0xF @ "15"
    if lessorequal _goto SetWeatherMistyAndEnd
    compare LASTRESULT 0x2D @ "45"
    if greaterorequal _goto SetWeatherRainyAndEnd
    goto TileScript_Route8_ClearWeather

SetWeatherMistyAndEnd:
    call SetWeatherFog
    end

SetWeatherRainyAndEnd:
    call SetWeatherRain
    end

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
    setflag 0xE0C
    call SandygastEncounter
    end

.global EventScript_Route8_SandygastEncounter2
EventScript_Route8_SandygastEncounter2:
    setflag 0xE0D
    call SandygastEncounter
    end

SandygastEncounter:
    lock
    checksound
    cry SPECIES_SANDYGAST 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    wildbattle SPECIES_SANDYGAST 0x19 0x0 @ Level 25
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

.global EventScript_Route8_CamperDrew
EventScript_Route8_CamperDrew:
    trainerbattle0 0x0 0x6A 0x0 gText_Route8_CamperDrew_Intro gText_Route8_CamperDrew_Defeat
    msgbox gText_Route8_CamperDrew_Chat MSG_NORMAL
    end

.global EventScript_Route8_NinjaBoyZeke
EventScript_Route8_NinjaBoyZeke:
    trainerbattle0 0x0 0x6B 0x0 gText_Route8_NinjaBoyZeke_Intro gText_Route8_NinjaBoyZeke_Defeat
    msgbox gText_Route8_NinjaBoyZeke_Chat MSG_NORMAL
    end

.global EventScript_Route8_SuperNerdSaul
EventScript_Route8_SuperNerdSaul:
    trainerbattle0 0x0 0x6C 0x0 gText_Route8_SuperNerdSaul_Intro gText_Route8_SuperNerdSaul_Defeat
    msgbox gText_Route8_SuperNerdSaul_Chat MSG_NORMAL
    end

.global EventScript_Route8_RockerParker
EventScript_Route8_RockerParker:
    trainerbattle0 0x0 0x6D 0x0 gText_Route8_RockerParker_Intro gText_Route8_RockerParker_Defeat
    msgbox gText_Route8_RockerParker_Chat MSG_NORMAL
    end

.global EventScript_Route8_ParasolLadyAnnabelle
EventScript_Route8_ParasolLadyAnnabelle:
    trainerbattle0 0x0 0x6E 0x0 gText_Route8_ParasolLadyAnnabelle_Intro gText_Route8_ParasolLadyAnnabelle_Defeat
    msgbox gText_Route8_ParasolLadyAnnabelle_Chat MSG_NORMAL
    end

.global EventScript_Route8_ChannelerMorgan
EventScript_Route8_ChannelerMorgan:
    trainerbattle0 0x0 0x6F 0x0 gText_Route8_ChannelerMorgan_Intro gText_Route8_ChannelerMorgan_Defeat
    msgbox gText_Route8_ChannelerMorgan_Chat MSG_NORMAL
    end

.global EventScript_Route8_BugCatcherArnold
EventScript_Route8_BugCatcherArnold:
    trainerbattle0 0x0 0x70 0x0 gText_Route8_BugCatcherArnold_Intro gText_Route8_BugCatcherArnold_Defeat
    msgbox gText_Route8_BugCatcherArnold_Chat MSG_NORMAL
    end

.global EventScript_Route8_LassLilian
EventScript_Route8_LassLilian:
    trainerbattle0 0x0 0x71 0x0 gText_Route8_LassLilian_Intro gText_Route8_LassLilian_Defeat
    msgbox gText_Route8_LassLilian_Chat MSG_NORMAL
    end

.global EventScript_Route8_NinjaBoyNatto
EventScript_Route8_NinjaBoyNatto:
    trainerbattle0 0x0 0x72 0x0 gText_Route8_NinjaBoyNatto_Intro gText_Route8_NinjaBoyNatto_Defeat
    msgbox gText_Route8_NinjaBoyNatto_Chat MSG_NORMAL
    end

.global EventScript_Route8_TuberMicah
EventScript_Route8_TuberMicah:
    trainerbattle0 0x0 0x73 0x0 gText_Route8_TuberMicah_Intro gText_Route8_TuberMicah_Defeat
    msgbox gText_Route8_TuberMicah_Chat MSG_NORMAL
    end

.global EventScript_Route8_TuberNancy
EventScript_Route8_TuberNancy:
    trainerbattle0 0x0 0x74 0x0 gText_Route8_TuberNancy_Intro gText_Route8_TuberNancy_Defeat
    msgbox gText_Route8_TuberNancy_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerMaya
EventScript_Route8_SwimmerMaya:
    trainerbattle0 0x0 0x75 0x0 gText_Route8_SwimmerMaya_Intro gText_Route8_SwimmerMaya_Defeat
    msgbox gText_Route8_SwimmerMaya_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerHuey
EventScript_Route8_SwimmerHuey:
    trainerbattle0 0x0 0x76 0x0 gText_Route8_SwimmerHuey_Intro gText_Route8_SwimmerHuey_Defeat
    msgbox gText_Route8_SwimmerHuey_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerBob
EventScript_Route8_SwimmerBob:
    trainerbattle0 0x0 0x77 0x0 gText_Route8_SwimmerBob_Intro gText_Route8_SwimmerBob_Defeat
    msgbox gText_Route8_SwimmerBob_Chat MSG_NORMAL
    end

.global EventScript_Route8_CoolTrainerHarriet
EventScript_Route8_CoolTrainerHarriet:
    trainerbattle0 0x0 0x78 0x0 gText_Route8_CoolTrainerHarriet_Intro gText_Route8_CoolTrainerHarriet_Defeat
    msgbox gText_Route8_CoolTrainerHarriet_Chat MSG_NORMAL
    end

.global EventScript_Route8_FishermansHut_Fisherman
EventScript_Route8_FishermansHut_Fisherman:
    lock
    faceplayer
    checkflag 0x24B @ Got Good Rod
    if SET _goto FishermanFarewell
    msgbox gText_Route8_FishermansHut_FishermanIntro MSG_YESNO
    compare LASTRESULT YES
    IF TRUE _goto FishermanYes
    msgbox gText_Route8_FishermansHut_FishermanNo MSG_NORMAL
    release
    end

FishermanYes:
    msgbox gText_Route8_FishermansHut_FishermanYes MSG_NORMAL
    obtainitem ITEM_GOOD_ROD 0x1
    setflag 0x24B @ Got Good Rod
    msgbox gText_Route8_FishermansHut_FishermanGift MSG_NORMAL
    goto FishermanFarewell

FishermanFarewell:
    msgbox gText_Route8_FishermansHut_FishermanFarewell MSG_NORMAL
    release
    end
