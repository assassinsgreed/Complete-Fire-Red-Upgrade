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
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x14 @ Player warped to gym entrance
    if equal _goto SetPlayerPosForGymEntranceWarp
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

SetPlayerPosForGymEntranceWarp:
    spriteface PLAYER DOWN
    end

.global EventScript_HeleoGym_CastformWater
EventScript_HeleoGym_CastformWater:
    call CastformCommon
    playse 0xC3 @ Sunny day
    call SetWeatherSunny
    msgbox gText_HeleoCityGym_CastformSunnyDay MSG_NORMAL
    call CastformCommon_WeatherChanging
    warpmuted 1 93 0xFF 0x4000 0x4001 @ Warp to same spot in drained map
    end

.global EventScript_HeleoGym_CastformDrained
EventScript_HeleoGym_CastformDrained:
    call CastformCommon
    call SetWeatherRain
    msgbox gText_HeleoCityGym_CastformRainDance MSG_NORMAL
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
    fadescreenswapbuffers 0x1
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    return

.global EventScript_HeleoGym_SwimmerTessa
EventScript_HeleoGym_SwimmerTessa:
    trainerbattle0 0x0 0x65 0x0 gText_HeleoCityGym_SwimmerTessaIntro gText_HeleoCityGym_SwimmerTessaDefeat
    msgbox gText_HeleoCityGym_SwimmerTessaChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerByron
EventScript_HeleoGym_SwimmerByron:
    trainerbattle0 0x0 0x66 0x0 gText_HeleoCityGym_SwimmerByronIntro gText_HeleoCityGym_SwimmerByronDefeat
    msgbox gText_HeleoCityGym_SwimmerByronChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerDanette
EventScript_HeleoGym_SwimmerDanette:
    trainerbattle0 0x0 0x67 0x0 gText_HeleoCityGym_SwimmerDanetteIntro gText_HeleoCityGym_SwimmerDanetteDefeat
    msgbox gText_HeleoCityGym_SwimmerDanetteChat MSG_NORMAL
    end

.global EventScript_HeleoGym_SwimmerMaisey
EventScript_HeleoGym_SwimmerMaisey:
    trainerbattle0 0x0 0x68 0x0 gText_HeleoCityGym_SwimmerMaiseyIntro gText_HeleoCityGym_SwimmerMaiseyDefeat
    msgbox gText_HeleoCityGym_SwimmerMaiseyChat MSG_NORMAL
    end

.global EventScript_HeleoGym_LeaderRaine
EventScript_HeleoGym_LeaderRaine:
    lockall
    faceplayer
    checkflag 0x822 @ Heleo gym badge
    if SET _goto EventScript_HeleoGym_LeaderRaine_Chat
    msgbox gText_HeleoGym_LeaderRaine_Talk MSG_NORMAL
    setvar 0x503A 0x1
    setvar 0x503B 0x1
    callasm CountBadges
    compare LASTRESULT 0x2
    if equal _goto LeaderRaine_2Badges
    compare LASTRESULT 0x3
    if equal _goto LeaderRaine_3Badges
    compare LASTRESULT 0x4
    if equal _goto LeaderRaine_4Badges
    end

LeaderRaine_2Badges:
    trainerbattle1 0x1 105 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

LeaderRaine_3Badges:
    trainerbattle1 0x1 256 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

LeaderRaine_4Badges:
    trainerbattle1 0x1 257 0x100 gText_HeleoGym_LeaderRaine_Intro gText_HeleoGym_LeaderRaine_Defeat EventScript_HeleoGym_LeaderRaine_Defeated
    end

EventScript_HeleoGym_LeaderRaine_Defeated:
    msgbox gText_HeleoGym_LeaderRaine_BadgeAwarded MSG_NORMAL
    fanfare 0x13D @ Gym victory
    msgbox gText_HeleoGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    setflag 0x822 @ Heleo gym badge
    settrainerflag 0x65 @ Tessa cannot be battled now
    settrainerflag 0x66 @ Byron cannot be battled now
    settrainerflag 0x67 @ Danette cannot be battled now
    settrainerflag 0x68 @ Maisey cannot be battled now
    msgbox gText_HeleoGym_LeaderRaine_BadgeDescription MSG_NORMAL
    msgbox gText_HeleoGym_LeaderRaine_TMReceived MSG_NORMAL
    fanfare 0x101
    additem ITEM_TM07 0x1 @ Hail
    additem ITEM_TM11 0x1 @ Sunny Day
    additem ITEM_TM18 0x1 @ Rain Dance
    additem ITEM_TM37 0x1 @ Sandstorm
    msgbox gText_HeleoGym_TMReceived MSG_KEEPOPEN
    setflag 0x4B2 @ Defeated Raine
    msgbox gText_HeleoGym_LeaderRaine_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_HeleoGym_LeaderRaine_Chat:
    npcchat gText_HeleoGym_LeaderRaine_Chat
    end

.global EventScript_HeleoGym_GymExpert
EventScript_HeleoGym_GymExpert:
    checkflag 0x822 @ Heleo gym badge
    if SET _goto EventScript_HeleoGym_GymExpertBadgeObtained
    npcchat gText_HeleoGym_ExpertTips
    end

EventScript_HeleoGym_GymExpertBadgeObtained:
    npcchat gText_HeleoGym_ExpertBadgeObtained
    end

.global SignScript_HeleoGym_Placard
SignScript_HeleoGym_Placard:
    checkflag 0x822 @ Heleo gym badge
    if SET _goto SignScript_HeleoGym_PlacardWithBadge
    msgbox gText_HeleoGym_Winners MSG_SIGN
    end

SignScript_HeleoGym_PlacardWithBadge:
    msgbox gText_HeleoGym_WinnersWithBadge MSG_SIGN
    end

.global EventScript_HeleoGym_Slowbro
EventScript_HeleoGym_Slowbro:
    faceplayer
    cry SPECIES_SLOWBRO 0x0
    applymovement LASTTALKED m_Question 
    msgbox gText_HeleoGym_SlowbroQuestion MSG_NORMAL
    msgbox gText_HeleoGym_SlowbroConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto SlowbroNo
    cry SPECIES_SLOWBRO 0x0
    msgbox gText_HeleoGym_SlowbroYes MSG_NORMAL
    waitcry
    playse 0x27 @ Warp away
    pause DELAY_HALFSECOND
    warpmuted 1 92 0xFF 0xF 0x14 @ Warp to gym entrance, in flooded map
    end

SlowbroNo:
    cry SPECIES_SLOWBRO 0x3 @ Fainted sound, pitched down
    msgbox gText_HeleoGym_SlowbroNo MSG_NORMAL
    waitcry
    applymovement LASTTALKED m_LookDown
    end
