.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_RhodanziOverworld_FlightSpot
MapScript_RhodanziOverworld_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RhodanziOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RhodanziOverworld_FlightFlag:
    setworldmapflag 0x892
    sethealingplace 0x03 @ Originally Pewter City
    checkflag 0x820
    additem ITEM_MACH_BIKE
    IF SET _call HideThugs
    end

HideThugs:
    hidesprite 0x6
    hidesprite 0x7
    setflag 0x00AD
    return

.global EventScript_RhodanziOverworld_SunSightMan
EventScript_RhodanziOverworld_SunSightMan:
    npcchat gText_RhodanziOverworld_SunSightMan
    end

.global EventScript_RhodanziOverworld_FirstStop
EventScript_RhodanziOverworld_FirstStop:
    npcchat gText_RhodanziOverworld_FirstStop
    end

.global EventScript_RhodanziOverworld_PokemonVariety
EventScript_RhodanziOverworld_PokemonVariety:
    npcchat gText_RhodanziOverworld_PokemonVariety
    end

.global EventScript_RhodanziOverworld_TreeGuy
EventScript_RhodanziOverworld_TreeGuy:
    npcchat gText_RhodanziOverworld_TreeGuy
    end

.global SignScript_RhodanziCity_FishermanSign
SignScript_RhodanziCity_FishermanSign:
    msgbox gText_RhodanziCity_FishermanSign MSG_SIGN
    end

.global TileScript_RhodanziOverworld_ThugsCaught
TileScript_RhodanziOverworld_ThugsCaught:
    checkflag 0x820
    if SET _goto End
    lock @ TODO: Fix bug!  Event should not do anything when flag set
    msgbox gText_RhodanziOverworld_ThugsRumour MSG_NORMAL
    applymovement 0x6 m_Surprise
    applymovement 0x7 m_Surprise
    waitmovement ALLEVENTS
    msgbox gText_RhodanziOverworld_Thugs MSG_NORMAL
    applymovement 0x6 m_ThugBottomMoveToPush
    applymovement 0x7 m_ThugTopMoveToPush
    waitmovement ALLEVENTS
    sound 0x7 @Bumping into wall
    applymovement 0x6 m_ThugPush
    applymovement 0x7 m_ThugPush
    applymovement PLAYER m_PlayerJump
    waitmovement ALLEVENTS
    applymovement 0x6 m_ThugBottomMoveBack
    applymovement 0x7 m_ThugTopMoveBack
    waitmovement ALLEVENTS
    msgbox gText_RhodanziOverworld_ThugsThreat MSG_NORMAL
    release
    end

.global EventScript_RhodanziOverworld_ThugBottomSpokenTo
EventScript_RhodanziOverworld_ThugBottomSpokenTo:
    npcchat2 0x6 m_LookUp gText_RhodanziOverworld_Thugs
    end

.global EventScript_RhodanziOverworld_ThugTopSpokenTo
EventScript_RhodanziOverworld_ThugTopSpokenTo:
    npcchat2 0x7 m_LookDown gText_RhodanziOverworld_Thugs
    end

End:
    release
    end

m_ThugTopMoveToPush:
    .byte run_right, run_down, look_left, end_m

m_ThugBottomMoveToPush:
    .byte run_right, run_up, look_left, end_m

m_ThugPush:
    .byte say_cross, jump_onspot_left, end_m

m_PlayerJump:
    .byte jump_left, end_m

m_ThugTopMoveBack:
    .byte run_up, run_left, look_down, end_m

m_ThugBottomMoveBack:
    .byte run_down, run_left, look_up, end_m
