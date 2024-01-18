.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ PlutoGrunt, 0x1
.equ OldMan, 0x2
.equ StoryFlag, 0x045

.global MapScript_ScaldingSpa_SpaRoom
MapScript_ScaldingSpa_SpaRoom:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_ScaldingSpa
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_ScaldingSpa:
    checkflag StoryFlag
    if NOT_SET _goto End
    call SetOldManLocation
    end

.global MapScript_GlastrierRoom
MapScript_GlastrierRoom:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HandleGlastrierWeather
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_HandleGlastrierWeather:
    @ HACK: For some reason, Glastrier's flag gets set when talking to it, even if it isn't set by code... So we check if it's caught and reset the flag if not
    setvar LASTRESULT SPECIES_GLASTRIER
    callasm CheckIfCaught
    compare LASTRESULT 0x0
    if equal _goto ResetGlastrier
    call SetWeatherSnowstorm
    end

ResetGlastrier:
    clearflag 0x46 @ Glastrier caught
    call SetWeatherSnowstorm
    end

.global EventScript_ScaldingSpa_SpaRoom_PlutoGrunt
EventScript_ScaldingSpa_SpaRoom_PlutoGrunt:
    special 0xAF @ Dismount bike if on it
    playbgm 0x19A 0x1 @ Encounter Team Pluto (permanent, needs to be overidden to default track later)
    msgbox gtext_ScaldingSpa_SpaRoom_GruntShakesTheOldManDown MSG_NORMAL
    faceplayer
    msgbox gtext_ScaldingSpa_SpaRoom_GruntAcknowledgesPlayer MSG_NORMAL
    goto PlutoGruntEvent
    end

.global TileScript_ScaldingSpa_SpaRoom_PlutoTriggerAbove
TileScript_ScaldingSpa_SpaRoom_PlutoTriggerAbove:
    call PlayerWalksPastGrunt
    call PlayerWalkDown_Return
    goto MoveGruntToPlayer
    end

.global TileScript_ScaldingSpa_SpaRoom_PlutoTriggerCentered
TileScript_ScaldingSpa_SpaRoom_PlutoTriggerCentered:
    call PlayerWalksPastGrunt
    goto MoveGruntToPlayer
    end

.global TileScript_ScaldingSpa_SpaRoom_PlutoTriggerBelow
TileScript_ScaldingSpa_SpaRoom_PlutoTriggerBelow:
    call PlayerWalksPastGrunt
    call PlayerWalkUp_Return
    goto MoveGruntToPlayer
    end

PlayerWalksPastGrunt:
    checkflag StoryFlag
    if SET _goto End
    lock
    special 0xAF @ Dismount bike if on it
    playbgm 0x19A 0x1 @ Encounter Team Pluto (permanent, needs to be overidden to default track later)
    applymovement PlutoGrunt m_LookLeft
    applymovement PLAYER m_Surprise
    sound 0x15 @ Exclaim
    msgbox gtext_ScaldingSpa_SpaRoom_PlayerWalksPastPlutoGrunt MSG_NORMAL
    return

MoveGruntToPlayer:
    applymovement PLAYER m_LookRight
    applymovement PlutoGrunt m_GruntWalksToPlayer
    waitmovement PlutoGrunt
    goto PlutoGruntEvent

PlutoGruntEvent:
    msgbox gtext_ScaldingSpa_SpaRoom_GruntLooksAtPlayer MSG_NORMAL
    applymovement PlutoGrunt m_Surprise
    sound 0x15 @ Exclaim
    msgbox gtext_ScaldingSpa_SpaRoom_GruntInitiatesBattle MSG_NORMAL
    trainerbattle2 0x0 255 0x0 gtext_ScaldingSpa_SpaRoom_GruntBattleIntro gtext_ScaldingSpa_SpaRoom_GruntLosesBattle PostPlutoBattle

PostPlutoBattle:
    msgbox gtext_ScaldingSpa_SpaRoom_GruntCommentsOnCalicinBayAgain MSG_NORMAL
    applymovement PlutoGrunt m_Joy
    msgbox gtext_ScaldingSpa_SpaRoom_GruntLeavesForCalicinBay MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xC @ Player is on tile event
    if equal _call PlutoGruntLeavesFromTile
    if notequal _call PlutoGruntLeavesFromInteraction
    playbgm 0x1A1 0x1 @ Reset permanent music
    hidesprite PlutoGrunt
    setflag StoryFlag
    pause DELAY_1SECOND
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xC
    if equal _call PlayerReturnsToOldMan
    if notequal _call PlayerFacesOldMan
    call OldManThanksPlayer
    applymovement OldMan m_OldManLeaves
    waitmovement OldMan
    call SetOldManLocation
    setvar 0x4000 0x0 @ Reset for spa healing
    end

PlutoGruntLeavesFromTile:
    applymovement PlutoGrunt m_GruntLeavesFromTileEvent
    call PlayerWatchesGruntLeave
    playse 0x9 @ Exit room
    waitse
    return

PlutoGruntLeavesFromInteraction:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x10 @ Left of grunt
    if equal _call PlutoGruntMovesAroundPlayer
    applymovement PlutoGrunt m_GruntLeavesFromInteraction
    call PlayerWatchesGruntLeave
    return

PlayerWatchesGruntLeave:
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement PLAYER m_LookLeft
    waitmovement PlutoGrunt
    return

PlutoGruntMovesAroundPlayer:
    applymovement PlutoGrunt m_WalkUp
    waitmovement PlutoGrunt
    return

PlayerReturnsToOldMan:
    applymovement PLAYER m_PlayerReturnsToOldMan
    waitmovement PLAYER
    return

PlayerFacesOldMan:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x11 @ Above old man
    if equal _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x10 @ Left of old man
    if equal _call PlayerWalkRight_Return
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x12 @ Left of old man
    if equal _call PlayerWalkLeft_Return
    applymovement PLAYER m_LookDown
    return

OldManThanksPlayer:
    msgbox gtext_ScaldingSpa_SpaRoom_OldManThanksPlayer MSG_NORMAL
    obtainitem ITEM_LAVA_COOKIE 0x3
    msgbox gtext_ScaldingSpa_SpaRoom_OldManGoesToHotsprings MSG_NORMAL
    call PlayerWalkUp_Return
    applymovement PLAYER m_LookDown
    return

SetOldManLocation:
    movesprite OldMan 0x4 0xA @ For while on this map after event
    movesprite2 OldMan 0x4 0xA @ For permanent position
    setobjectmovementtype OldMan look_down
    return

.global EventScript_ScaldingSpa_SpaRoom_OldMan
EventScript_ScaldingSpa_SpaRoom_OldMan:
    checkflag StoryFlag
    if SET _goto OldManPostBattle
    msgbox gtext_ScaldingSpa_SpaRoom_OldManBeingBothered MSG_NORMAL
    end

OldManPostBattle:
    npcchat gtext_ScaldingSpa_SpaRoom_OldManAfterBeingHelped
    end

.global EventScript_ScaldingSpa_SpaRoom_Blackbelt
EventScript_ScaldingSpa_SpaRoom_Blackbelt:
    npcchat gtext_ScaldingSpa_SpaRoom_Blackbelt
    end

.global EventScript_ScaldingSpa_SpaRoom_Picknicker
EventScript_ScaldingSpa_SpaRoom_Picknicker:
    npcchatwithmovement gtext_ScaldingSpa_SpaRoom_Picknicker m_LookUp
    end

.global EventScript_ScaldingSpa_SpaRoom_Nurse
EventScript_ScaldingSpa_SpaRoom_Nurse:
    npcchatwithmovement gtext_ScaldingSpa_SpaRoom_Nurse m_LookDown
    end

.global EventScript_ScaldingSpa_SpaRoom_OldWoman
EventScript_ScaldingSpa_SpaRoom_OldWoman:
    npcchatwithmovement gtext_ScaldingSpa_SpaRoom_OldWoman m_LookDown
    end

.global EventScript_ScaldingSpa_SpaRoom_Swimmer
EventScript_ScaldingSpa_SpaRoom_Swimmer:
    npcchat gtext_ScaldingSpa_SpaRoom_Swimmer
    end

.global EventScript_ScaldingSpa_SpaRoom_GameboyKid
EventScript_ScaldingSpa_SpaRoom_GameboyKid:
    npcchatwithmovement gtext_ScaldingSpa_SpaRoom_GameboyKid m_LookDown
    end

.global TileScript_ScaldingSpa_SpaRoom_Heal
TileScript_ScaldingSpa_SpaRoom_Heal:
    lock
    call PlayerWalkDown_Return
    call SetWeatherThinFog
    pause DELAY_HALFSECOND
    incrementgamestat 49
    playse 0x1 @ Use item
    waitse
    msgbox gtext_ScaldingSpa_SpaRoom_HealingSpa MSG_NORMAL
    special 0x0
    call SetWeatherClear
    pause DELAY_HALFSECOND
    setvar 0x4000 0x1
    release
    end

.global TileScript_ScaldingSpa_SpaRoom_ResetHeal
TileScript_ScaldingSpa_SpaRoom_ResetHeal:
    setvar 0x4000 0x0
    end

.global EventScript_ScaldingSpa_Blazikenite
EventScript_ScaldingSpa_Blazikenite:
    finditem ITEM_BLAZIKENITE 0x1
    end

.global EventScript_ScaldingSpa_TM35_Flamethrower
EventScript_ScaldingSpa_TM35_Flamethrower:
    setvar CHOSEN_ITEM ITEM_TM35
    call ItemScript_Common_FindTM
    end

.global EventScript_ScaldingSpa_HikerEugene
EventScript_ScaldingSpa_HikerEugene:
    // Double battle with Stephen
    compare PLAYERFACING LEFT
    if equal _call EugeneAndStephenLookRight
    trainerbattle11 0x0 251 252 14 15 0x0 gtext_ScaldingSpa_HikerEugene_Intro gtext_ScaldingSpa_SupernerdStephen_Intro gtext_ScaldingSpa_HikerEugene_Defeat gtext_ScaldingSpa_SupernerdStephen_Defeat gtext_ScaldingSpa_HikerEugene_Chat gtext_ScaldingSpa_SupernerdStephen_Chat
    msgbox gtext_ScaldingSpa_HikerEugene_Chat MSG_NORMAL
    end

.global EventScript_ScaldingSpa_SuperNerdStephen
EventScript_ScaldingSpa_SuperNerdStephen:
    // Double battle with Eugene
    compare PLAYERFACING RIGHT
    trainerbattle11 0x0 251 252 14 15 0x0 gtext_ScaldingSpa_HikerEugene_Intro gtext_ScaldingSpa_SupernerdStephen_Intro gtext_ScaldingSpa_HikerEugene_Defeat gtext_ScaldingSpa_SupernerdStephen_Defeat gtext_ScaldingSpa_HikerEugene_Chat gtext_ScaldingSpa_SupernerdStephen_Chat
    msgbox gtext_ScaldingSpa_SupernerdStephen_Chat MSG_NORMAL
    end

EugeneAndStephenLookRight:
    applymovement 14 m_LookRight
    applymovement 15 m_LookRight
    return

EugeneAndStephenLookLeft:
    applymovement 14 m_LookLeft
    applymovement 15 m_LookLeft
    return 

.global EventScript_ScaldingSpa_JugglerJohan
EventScript_ScaldingSpa_JugglerJohan:
    trainerbattle0 0x0 253 0x0 gtext_ScaldingSpa_JugglerJohan_Intro gtext_ScaldingSpa_JugglerJohan_Defeat
    msgbox gtext_ScaldingSpa_JugglerJohan_Chat MSG_NORMAL
    end

.global EventScript_ScaldingSpa_BlackbeltKieran
EventScript_ScaldingSpa_BlackbeltKieran:
    trainerbattle0 0x0 254 0x0 gtext_ScaldingSpa_BlackbeltKieran_Intro gtext_ScaldingSpa_BlackbeltKieran_Defeat
    msgbox gtext_ScaldingSpa_BlackbeltKieran_Chat MSG_NORMAL
    end

.global EventScript_GlastrierRoom_Glastrier
EventScript_GlastrierRoom_Glastrier:
    faceplayer
    cry SPECIES_GLASTRIER 0x0
    waitcry
    msgbox gtext_GlastrierRoom_GlastrierBattleStart MSG_NORMAL
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_ICICLECRASH
    setvar 0x8001 MOVE_IRONDEFENSE
    setvar 0x8002 MOVE_DOUBLEEDGE
    setvar 0x8003 MOVE_TAUNT
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_GLASTRIER 70 ITEM_NONE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedGlastrier
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call FledFromGlastrier
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtGlastrier
    end

DefeatedGlastrier:
    call GlastrierLeavesCommon
    msgbox gtext_GlastrierRoom_GlastrierDefeated MSG_NORMAL
    return

FledFromGlastrier:
    call GlastrierLeavesCommon
    msgbox gtext_GlastrierRoom_GlastrierFledFromBattle MSG_NORMAL
    return

CaughtGlastrier:
    fadescreen FADEOUT_BLACK
    hidesprite 0x1
    setflag 0x46 @ Glastrier caught
    fadescreen FADEIN_BLACK
    return

GlastrierLeavesCommon:
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x8 @ Right of Glastrier
    if equal _call MovePlayerOutOfGlastriersWay
    applymovement 0x1 m_GlastrierRetreats
    waitmovement 0x1
    hidesprite 0x1
    call SetWeatherThreeSnowflakes
    return

MovePlayerOutOfGlastriersWay:
    call PlayerWalkDown_Return
    applymovement PLAYER m_LookUp
    return

.global TileScript_GlastrierRoom_LeftTile
TileScript_GlastrierRoom_LeftTile:
    checkflag 0x46 @ Glastrier caught
    if SET _goto End
    compare 0x4000 0x1 @ Event already triggered while on map
    if equal _goto End
    lock
    setvar 0x4000 0x1 @ Temp var to indicate the tile events shouldn't run again
    special 0xAF @ Dismount bike if on it
    applymovement PLAYER m_WalkToGlastrier
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    cry SPECIES_GLASTRIER 0x0
    waitcry
    msgbox gtext_GlastrierRoom_GlastrierEvaluation MSG_NORMAL
    checkflag 0x4BC @ Defeated Champion Selene
    if SET _goto GlastrierAcceptsPlayer
    msgbox gtext_GlastrierRoom_GlastrierEvaluationFailed MSG_NORMAL
    call GlastrierLeavesCommon
    end

GlastrierAcceptsPlayer:
    msgbox gtext_GlastrierRoom_GlastrierEvaluationSucceeded MSG_NORMAL
    end

.global TileScript_GlastrierRoom_RightTile
TileScript_GlastrierRoom_RightTile:
    checkflag 0x46 @ Glastrier caught
    if SET _goto End
    compare 0x4000 0x1 @ Event already triggered while on map
    if equal _goto End
    lock
    call PlayerWalkLeft_Return
    goto TileScript_GlastrierRoom_LeftTile

m_GruntWalksToPlayer: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, end_m
m_GruntLeavesFromTileEvent: .byte walk_down, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_down, walk_down, walk_down, end_m
m_GruntLeavesFromInteraction: .byte walk_left, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_PlayerReturnsToOldMan: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, end_m
m_OldManLeaves: .byte walk_up, walk_left, walk_left, walk_up, walk_up, walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_WalkToGlastrier: .byte walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_GlastrierRetreats: .byte walk_right, walk_up, walk_up, walk_up, jump_2_up, walk_up, walk_up, walk_up, end_m 
