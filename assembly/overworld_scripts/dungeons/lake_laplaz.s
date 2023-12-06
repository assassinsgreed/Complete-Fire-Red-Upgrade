.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ GalarianBirdsFlag, 0x043
.equ GalarianBirdsVariable, 0x405B
.equ Articuno, 0x3
.equ Zapdos, 0x4
.equ Moltres, 0x5

.global MapScript_LakeLaplaz
MapScript_LakeLaplaz:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LakeLaplaz_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_LakeLaplaz_FlightFlag:
    setworldmapflag 0x8A9
    end

.global EventScript_LakeLaplaz_TM08_BulkUp
EventScript_LakeLaplaz_TM08_BulkUp:
    setvar CHOSEN_ITEM ITEM_TM08
    call ItemScript_Common_FindTM
    end

.global SignScript_LakeLaplaz_CleanlinessReminder
SignScript_LakeLaplaz_CleanlinessReminder:
    msgbox gText_LakeLaplaz_CleanlinessReminderSign MSG_SIGN
    end

.global SignScript_LakeLaplaz_FlowerOffering
SignScript_LakeLaplaz_FlowerOffering:
    msgbox gText_LakeLaplaz_FlowerGiftSign MSG_SIGN
    end

.global TileScript_LakeLaplaz_GalarianBirdsLeft
TileScript_LakeLaplaz_GalarianBirdsLeft:
    special 0xAF @ Dismount bike if on it
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    goto TileScript_LakeLaplaz_GalarianBirdsCommon

.global TileScript_LakeLaplaz_GalarianBirdsCommon
TileScript_LakeLaplaz_GalarianBirdsCommon:
    special 0xAF @ Dismount bike if on it
    applymovement PLAYER m_PlayerWalksUp
    waitmovement PLAYER
    sound 0x15 @ Exclaim
	applymovement PLAYER m_Surprise
    msgbox gText_LakeLaplaz_GalarianBirdsDiscovered MSG_NORMAL
    applymovement PLAYER m_PlayerWalksUp
    waitmovement PLAYER
    applymovement Articuno m_LookDown
    applymovement Zapdos m_LookDown
    applymovement Moltres m_LookDown
    waitmovement Moltres
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
	applymovement Articuno m_Surprise
    applymovement Zapdos m_Surprise
    applymovement Moltres m_Surprise
    msgbox gText_LakeLaplaz_GalarianBirdsSeePlayer MSG_NORMAL
    call ZapdosMovement
    applymovement PLAYER m_LookUp
    call ArticunoMovement
    call MoltresMovement
    setflag GalarianBirdsFlag
    setvar GalarianBirdsVariable 0x1
    hidesprite Articuno
    hidesprite Zapdos
    hidesprite Moltres
    callasm MarkGalarianBirdsAsSeen
    call SetupRoamers
    msgbox gText_LakeLaplaz_GalarianBirdsFled MSG_NORMAL
    end

ZapdosMovement:
    cry SPECIES_ZAPDOS_G 0x0
    waitcry
    applymovement Zapdos m_ZapdosJump
    playse 0xA @ Hop
    waitmovement Zapdos
    applymovement Zapdos m_ZapdosJump
    playse 0xA @ Hop
    waitmovement Zapdos
    pause DELAY_HALFSECOND
    applymovement Zapdos m_ZapdosCirclesPlayer
    waitmovement Zapdos
    applymovement Zapdos m_ZapdosJump
    playse 0xA @ Hop
    waitmovement Zapdos
    applymovement Zapdos m_ZapdosJump
    playse 0xA @ Hop
    waitmovement Zapdos
    pause DELAY_HALFSECOND
    showpokepic SPECIES_ZAPDOS_G
    waitkeypress
    hidepokepic
    pause DELAY_HALFSECOND
    applymovement Zapdos m_ZapdosRunsAway
    pause DELAY_1SECOND
    waitmovement Zapdos
    pause DELAY_HALFSECOND
    return

ArticunoMovement:
    applymovement Articuno m_ArticunoRaisesUp
    waitmovement Articuno
    cry SPECIES_ARTICUNO_G 0x0
    waitcry
    setobjectmovementtype Articuno 0x8 @ Look Down
    call teleportAnimaton
    movesprite Articuno 0x1A 0x1E
    call teleportAnimaton
    movesprite Articuno 0x20 0x1B
    call teleportAnimaton
    movesprite Articuno 0x1F 0x1F
    call teleportAnimaton
    movesprite Articuno 0x1B 0x1C
    call teleportAnimaton
    movesprite Articuno 0x1D 0x1A
    playse 0x28 @ Warp in
	dofieldeffect 69 @ Screen flash
    applymovement Articuno m_ArticunoShow
    pause DELAY_HALFSECOND
    waitfieldeffect 69
    waitse
    showpokepic SPECIES_ARTICUNO_G
    waitkeypress
    hidepokepic
    call teleportAnimaton
    movesprite Articuno 0xC0 0xC0 @ Just out of view
    pause DELAY_HALFSECOND
    return

teleportAnimaton:
    applymovement Articuno m_ArticunoShow
    playse 0x28 @ Warp in
	dofieldeffect 69 @ Screen flash
    pause DELAY_HALFSECOND
    applymovement Articuno m_ArticunoHide
    waitfieldeffect 69
    waitse
    return

MoltresMovement:
    cry SPECIES_MOLTRES_G 0x0
    waitcry
    applymovement Moltres m_MoltresFliesUp
    waitmovement Moltres
    pause DELAY_HALFSECOND
    showpokepic SPECIES_MOLTRES_G
    waitkeypress
    hidepokepic
    applymovement Moltres m_MoltresFliesAway
    waitmovement Moltres
    pause DELAY_HALFSECOND
    return

SetupRoamers:
    setvar 0x8000 SPECIES_ARTICUNO_G
    setvar 0x8001 50 @ Level 50
    setvar 0x8002 0x1 @ Can roam on land
    setvar 0x8003 0x0 @ Cannot roam on water
    special 0x129 @ Create roaming Pokemon
    setvar 0x8000 SPECIES_ZAPDOS_G
    special 0x129 @ Create roaming Pokemon
    setvar 0x8000 SPECIES_MOLTRES_G
    special 0x129 @ Create roaming Pokemon
    return

m_PlayerWalksUp: .byte walk_up, walk_up, end_m
m_ZapdosJump: .byte jump_onspot_down, end_m
m_ZapdosCirclesPlayer: .byte run_down, run_left, run_down, run_down, run_right, run_right, run_up, run_up, slide_left_fast, slide_left_fast, slide_down_fast, slide_down_fast, slide_right_fast, slide_right_fast, slide_up_fast, slide_up_fast, slide_left_fast, look_down, end_m
m_ZapdosRunsAway: .byte run_left, run_down, slide_down_fast, slide_down_fast, slide_down_fast, slide_down_fast, slide_down_fast, slide_down_fast, end_m
m_ArticunoRaisesUp: .byte lock_facing, walk_up, end_m
m_ArticunoHide: .byte set_invisible, end_m
m_ArticunoShow: .byte set_visible, end_m
m_MoltresFliesUp: .byte lock_facing, walk_up_very_slow, walk_up_very_slow, unlock_facing, run_left, run_left, run_left, run_left, run_down, run_down, run_right, run_right, look_down, end_m
m_MoltresFliesAway: .byte run_right, run_up, run_up, run_up, run_up, run_up, end_m
