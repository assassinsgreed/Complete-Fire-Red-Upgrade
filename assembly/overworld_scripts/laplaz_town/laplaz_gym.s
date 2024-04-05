.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ TileSpriteLeft, 0x2C1
.equ TileSpriteRight, 0x2C2
.equ TileSpriteDown, 0x2C3
.equ TileSpriteUp, 0x2C4
.equ Casey, 0x1

.global MapScript_LaplazGym_RotatingFloorTiles
MapScript_LaplazGym_RotatingFloorTiles:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LaplazGym_SetWalkingScript
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_LaplazGym
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_LaplazGym_SetWalkingScript:
    setvar 0x500B 0x1 @ Use walking script 1, which is defined below
    call SetCaseyGender
    checkflag 0x3F @ Casey is not revealed as leader
    if SET _goto End
    movesprite2 Casey 0x8 0x2 @ Update position of Casey permanently
    end

LevelScripts_LaplazGym:
    levelscript 0x405A 0x1 LevelScripts_LaplazGym_SetPlayerFacing
    .hword LEVEL_SCRIPT_TERMIN

LevelScripts_LaplazGym_SetPlayerFacing:
    @ Player may warp here after tile event, due to engine limitations. Set their facing to up
    spriteface PLAYER UP
    end

@ Assigned as a walking script, to trigger on each step
.global LaplazGym_RotationSteps
LaplazGym_RotationSteps:
    @ Tiles do not rotate if the player's step results in them stopping on a movement tile    
    compare 0x4000 0x4
    if equal _goto RotateTiles
    if notequal _goto TimerTickUpSound

TimerTickUpSound:
    addvar 0x4000 0x1
    release
    end

RotateTiles:
    playse 0x2A @ Turn switch flip
    @ The following 3 calls are called for every rotatable tile
    setvar 0x8004 0x8 @ X var of tile
    setvar 0x8005 0x34 @ Y var of tile
    call HandleRotationCW @ Gym entrance
    setvar 0x8004 0xC
    setvar 0x8005 0x32
    call HandleRotationCW @ Right of gym entrance
    setvar 0x8004 0x5
    setvar 0x8005 0x31
    call HandleRotationCCW @ Left of gym entrance
    setvar 0x8004 0x6
    setvar 0x8005 0x28
    call HandleRotationHorizontal @ Left in area 2
    setvar 0x8004 0x7
    setvar 0x8005 0x28
    call HandleRotationRightUpDown @ Right in area 2
    setvar 0x8004 0xE
    setvar 0x8005 0x1E
    call HandleRotationLeftUpRight @ Right in area 3
    setvar 0x8004 0x8
    setvar 0x8005 0x1C
    call HandleRotationVertical @ Middle-Right in area 3
    setvar 0x8004 0x6
    setvar 0x8005 0x1C
    call HandleRotationCCW @ Middle-Left in area 3
    setvar 0x8004 0x4
    setvar 0x8005 0x1C
    call HandleRotationCW @ Left in area 3
    setvar 0x8004 0x6
    setvar 0x8005 0x13
    call HandleRotationCW @ Bottom Left in area 4
    setvar 0x8004 0x8
    setvar 0x8005 0xF
    call HandleRotationLeftUpDown @ Left in area 4
    setvar 0x8004 0x9
    setvar 0x8005 0xE
    call HandleRotationLeftUpRight @ Middle in area 4
    setvar 0x8004 0xA
    setvar 0x8005 0xF
    call HandleRotationRightUpDown @ Right in area 4
    setvar 0x4000 0x0
    special 0x8E @ Refresh map changes
    release
    end

HandleRotationCW:
    @ Tiles rotate clockwise every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateLeft
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    return

HandleRotationCCW:
    @ Tiles rotate counterclockwise every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateLeft
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateUp
    return

HandleRotationHorizontal:
    @ Tiles rotate left-right every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateLeft
    return

HandleRotationVertical:
    @ Tiles rotate up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateUp
    return

HandleRotationLeftUpRight:
    @ Tiles rotate left-up-right-left every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateRight
    compare LASTRESULT TileSpriteRight
    if equal _call RotateLeft
    return

HandleRotationLeftUpDown:
    @ Tiles rotate left-up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteLeft
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateLeft
    return

HandleRotationRightUpDown:
    @ Tiles rotate right-up-down every 5 steps
    special2 LASTRESULT 0x7E @ Get the number of the tile at 0x8004 0x8005
    compare LASTRESULT TileSpriteRight
    if equal _call RotateUp
    compare LASTRESULT TileSpriteUp
    if equal _call RotateDown
    compare LASTRESULT TileSpriteDown
    if equal _call RotateRight
    return

RotateRight:
    setmaptile 0x8004 0x8005 TileSpriteRight 0x0
    return

RotateDown:
    setmaptile 0x8004 0x8005 TileSpriteDown 0x0
    return

RotateLeft:
    setmaptile 0x8004 0x8005 TileSpriteLeft 0x0
    return

RotateUp:
    setmaptile 0x8004 0x8005 TileSpriteUp 0x0
    return


.global EventScript_LaplazGym_LeaderCasey
EventScript_LaplazGym_LeaderCasey:
    faceplayer
    call SetCaseyGender
    checkflag 0x824 @ Laplaz gym badge
    if SET _goto EventScript_LaplazTownGym_LeaderCasey_Chat
    msgbox gText_LaplazGym_LeaderCasey_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _goto FemaleCaseyBattle
    trainerbattle1 0x1 0xEA 0x100 gText_LaplazGym_LeaderCaseyM_Intro gText_LaplazGym_LeaderCaseyM_Defeat EventScript_LaplazGym_LeaderCasey_Defeated
    end

FemaleCaseyBattle:
    trainerbattle1 0x1 0xE9 0x100 gText_LaplazGym_LeaderCaseyF_Intro gText_LaplazGym_LeaderCaseyF_Defeat EventScript_LaplazGym_LeaderCasey_Defeated

EventScript_LaplazGym_LeaderCasey_Defeated:
    msgbox gText_LaplazGym_LeaderCasey_BadgeAwarded MSG_NORMAL
    setflag 0x824 @ Laplaz gym badge
    fanfare 0x13D @ Gym victory
    textcolor BLACK
    msgbox gText_LaplazGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    settrainerflag 0xE3 @ Jeremiah cannot be battled now
    settrainerflag 0xE4 @ Exie cannot be battled now
    settrainerflag 0xE5 @ Virginia cannot be battled now
    settrainerflag 0xE6 @ Nisha cannot be battled now
    settrainerflag 0xE7 @ Kent cannot be battled now
    settrainerflag 0xE8 @ Tomas cannot be battled now
    call SetCaseyGender @ Reset text color
    msgbox gText_LaplazGym_LeaderCasey_BadgeDescription MSG_NORMAL
    msgbox gText_LaplazGym_LeaderCasey_TMReceived MSG_NORMAL
    fanfare 0x101
    additem ITEM_TM75 0x1 @ Swords Dance
    textcolor BLACK
    msgbox gText_LaplazGym_TMReceived MSG_KEEPOPEN
    setflag 0x4B4 @ Defeated Casey
    setflag 0x25C @ New Pokemart Stock
    call SetCaseyGender @ Reset text color
    msgbox gText_LaplazGym_LeaderCasey_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_LaplazTownGym_LeaderCasey_Chat:
    npcchat gText_LaplazGym_LeaderCasey_Chat
    end

.global EventScript_LaplazGym_GymExpert
EventScript_LaplazGym_GymExpert:
    npcchat gText_LaplazGym_GymExpertCommonIntro
    checkflag 0x3F @ Casey is not revealed as leader yet
    if SET _goto GymExpert_MontyDescription
    msgbox gText_LaplazGym_GymExpertCaseyIntro MSG_NORMAL
    end

GymExpert_MontyDescription:
    msgbox gText_LaplazGym_GymExpertMontyIntro MSG_NORMAL
    end

.global EventScript_LaplazGym_Jeremiah
EventScript_LaplazGym_Jeremiah:
    trainerbattle0 0x0 0xE3 0x0 gText_LaplazGym_Jeremiah_Intro gText_LaplazGym_Jeremiah_Defeat
    msgbox gText_LaplazGym_Jeremiah_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Exie
EventScript_LaplazGym_Exie:
    trainerbattle0 0x0 0xE4 0x0 gText_LaplazGym_Exie_Intro gText_LaplazGym_Exie_Defeat
    msgbox gText_LaplazGym_Exie_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Virginia
EventScript_LaplazGym_Virginia:
    trainerbattle0 0x0 0xE5 0x0 gText_LaplazGym_Virginia_Intro gText_LaplazGym_Virginia_Defeat
    msgbox gText_LaplazGym_Virginia_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Nisha
EventScript_LaplazGym_Nisha:
    trainerbattle0 0x0 0xE6 0x0 gText_LaplazGym_Nisha_Intro gText_LaplazGym_Nisha_Defeat
    msgbox gText_LaplazGym_Nisha_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Kent
EventScript_LaplazGym_Kent:
    trainerbattle0 0x0 0xE7 0x0 gText_LaplazGym_Kent_Intro gText_LaplazGym_Kent_Defeat
    msgbox gText_LaplazGym_Kent_Chat MSG_NORMAL
    end

.global EventScript_LaplazGym_Tomas
EventScript_LaplazGym_Tomas:
    trainerbattle0 0x0 0xE8 0x0 gText_LaplazGym_Tomas_Intro gText_LaplazGym_Tomas_Defeat
    msgbox gText_LaplazGym_Tomas_Chat MSG_NORMAL
    end

.global SignScript_LaplazGym_GymPlacard
SignScript_LaplazGym_GymPlacard:
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto GymPlacard_WithRival
    checkflag 0x824 @ Laplaz gym badge
    if SET _goto GymPlacard_JustPlayer
    msgbox gText_LaplazGym_Placard_NoBadge MSG_SIGN
    end

GymPlacard_WithRival:
    msgbox gText_LaplazGym_Placard_BadgeWithRival MSG_SIGN
    end

GymPlacard_JustPlayer:
    msgbox gText_LaplazGym_Placard_Badge MSG_SIGN
    end

.global TileScript_LaplazGym_IntroduceCasey
TileScript_LaplazGym_IntroduceCasey:
    lock
    checkflag 0x3F @ Casey is revealed as leader
    if NOT_SET _goto End @ Event already played
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    call SetCaseyGender
    playbgm 0x169 @ Alder encounter
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_LaplazGym_CaseyAsksForTilesToBeTurnedOff MSG_NORMAL
    clearflag 0x3F @ Casey is now revealed as leader
    showsprite Casey
    applymovement PLAYER m_LookDown
    applymovement Casey m_CaseyWalksToPlayer
    waitmovement Casey
    checkgender
    compare LASTRESULT 0x0
    if equal _call FemaleCaseyBackstory
    if notequal _call MaleCaseyBackstory
    fadedefaultbgm
    applymovement Casey m_CaseyWalksToPodium
    pause DELAY_1SECOND
    applymovement PLAYER m_LookUp
    waitmovement Casey
    setvar 0x405A 0x1
    getplayerpos 0x4000 0x4001 @ HACK: Move the player to the same map to force the tile script to release the player
    warpmuted 10 8 0xFF 0x4000 0x4001 @ Warp to same spot in the gym
    release
    end

FemaleCaseyBackstory:
    msgbox gText_LaplazGym_FemaleCaseyAddressesPlayer MSG_NORMAL
    playbgm 0x159 @ N's Farewell
    applymovement Casey m_LookDown
    msgbox gText_LaplazGym_FemaleCaseyBackstory MSG_NORMAL
    applymovement Casey m_LookUp
    msgbox gText_LaplazGym_FemaleCaseyCommitment MSG_NORMAL
    return

MaleCaseyBackstory:
    msgbox gText_LaplazGym_MaleCaseyAddressesPlayer MSG_NORMAL
    playbgm 0x159 @ N's Farewell
    applymovement Casey m_LookDown
    msgbox gText_LaplazGym_MaleCaseyBackstory MSG_NORMAL
    applymovement Casey m_LookUp
    msgbox gText_LaplazGym_MaleCaseyCommitment MSG_NORMAL
    return

m_CaseyWalksToPlayer: .byte walk_up, walk_up, walk_up, walk_up, walk_up, end_m
m_CaseyWalksToPodium: .byte walk_right, walk_up, walk_up, walk_left, walk_up, walk_up, walk_up, walk_up, look_down, end_m
