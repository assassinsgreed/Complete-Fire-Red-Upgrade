.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ OceanTile, 0x12B
.equ OceanWithNorthEdgeTile, 0x123
.equ OceanWithWestEdgeTile, 0x12A
.equ OceanWithEastEdgeTile, 0x12C
.equ OceanSWCornerTile, 0x131
.equ MountainWallTile, 0x299
.equ CaveDoorTile, 0x0A9
.equ GroundTile, 0x281
.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_SeppireCove
MapScript_SeppireCove:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_SeppireCove_SetWorldMapFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_SeppireCove_SetWorldMapFlag:
    setworldmapflag 0x8AC @ Been to Seppire Cove
    end

.global MapScript_SeppireCoveB1F
MapScript_SeppireCoveB1F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_SeppireCoveB1F_SetBoulderVisibilityAndCurrents
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_SeppireCoveB1F_SetBoulderVisibilityAndCurrents:
    setflag 0xA @ BoulderN
    setflag 0xB @ BoulderNW
    setflag 0xC @ BoulderNE
    setflag 0xD @ BoulderE
    setflag 0xE @ BoulderSW
    setflag 0xF @ BoulderSE
    checkflag 0x4D
    if SET _call SetWaterfallTiles
    checkflag 0x4E
    if SET _call SetNWCurrent
    checkflag 0x53
    if SET _call SetNECurrent
    checkflag 0x50
    if SET _call SetSWCurrent
    checkflag 0x51
    if SET _call SetECurrent
    checkflag 0x52
    if SET _call SetSECurrent
    end

@ Map tile events
SetWaterfallTiles:
    clearflag 0xA @ BoulderN
    setmaptile 0x12 0x2 MountainWallTile Impassable
    setmaptile 0x12 0x3 MountainWallTile Impassable
    setmaptile 0x12 0x4 CaveDoorTile Passable
    setmaptile 0x12 0x5 GroundTile Passable
    setmaptile 0x11 0x6 OceanTile Passable
    setmaptile 0x12 0x6 OceanWithNorthEdgeTile Passable
    setmaptile 0x13 0x6 OceanTile Passable
    return

SetNWCurrent:
    clearflag 0xB @ BoulderNW
    setmaptile 0xD 0x5 OceanWithNorthEdgeTile Impassable
    setmaptile 0xD 0x6 OceanTile Passable
    setmaptile 0xE 0x6 OceanTile Passable
    setmaptile 0xF 0x6 OceanTile Passable
    setmaptile 0x10 0x6 OceanTile Passable
    setmaptile 0x10 0x7 OceanTile Passable
    setmaptile 0x10 0x8 OceanTile Passable
    setmaptile 0xF 0x8 OceanTile Passable
    setmaptile 0xE 0x8 OceanTile Passable
    setmaptile 0xD 0x8 OceanTile Passable
    setmaptile 0xC 0x8 OceanTile Passable
    setmaptile 0xC 0x9 OceanTile Passable
    setmaptile 0xB 0x9 OceanTile Passable
    setmaptile 0xB 0xA OceanWithWestEdgeTile Passable
    setmaptile 0xB 0xB OceanWithWestEdgeTile Passable
    setmaptile 0xB 0xC OceanWithWestEdgeTile Passable
    setmaptile 0xB 0xD OceanSWCornerTile Passable
    setmaptile 0xB 0xE OceanTile Passable
    return

SetNECurrent:
    clearflag 0xC @ BoulderNE
    setmaptile 0x15 0x5 OceanWithNorthEdgeTile Impassable
    setmaptile 0x15 0x6 OceanTile Passable
    setmaptile 0x16 0x6 OceanTile Passable
    setmaptile 0x17 0x6 OceanTile Passable
    setmaptile 0x18 0x6 OceanTile Passable
    setmaptile 0x18 0x7 OceanTile Passable
    setmaptile 0x18 0x8 OceanTile Passable
    setmaptile 0x18 0x9 OceanTile Passable
    setmaptile 0x19 0x9 OceanTile Passable
    setmaptile 0x1A 0x9 OceanTile Passable
    setmaptile 0x1A 0xA OceanTile Passable
    setmaptile 0x1A 0xB OceanTile Passable
    setmaptile 0x1B 0xB OceanTile Passable
    setmaptile 0x1C 0xB OceanTile Passable
    setmaptile 0x1C 0xC OceanTile Passable
    setmaptile 0x1C 0xD OceanTile Passable
    setmaptile 0x1D 0xD OceanTile Passable
    setmaptile 0x1E 0xD OceanTile Passable
    setmaptile 0x1F 0xD OceanTile Passable
    setmaptile 0x20 0xD OceanWithEastEdgeTile Passable
    setmaptile 0x20 0xE OceanWithEastEdgeTile Passable
    setmaptile 0x20 0xF OceanWithEastEdgeTile Passable
    return

SetECurrent:
    clearflag 0xD @ BoulderE
    setmaptile 0x1A 0xC OceanTile Passable
    setmaptile 0x19 0xC OceanTile Passable
    setmaptile 0x19 0xD OceanTile Passable
    setmaptile 0x19 0xE OceanTile Passable
    setmaptile 0x19 0xF OceanTile Passable
    setmaptile 0x19 0x10 OceanTile Passable
    setmaptile 0x19 0x11 OceanTile Passable
    setmaptile 0x18 0x11 OceanTile Passable
    setmaptile 0x17 0x11 OceanTile Passable
    setmaptile 0x16 0x11 OceanTile Passable
    setmaptile 0x15 0x11 OceanTile Passable
    setmaptile 0x14 0x11 OceanTile Passable
    setmaptile 0x13 0x11 OceanTile Passable
    setmaptile 0x12 0x11 OceanTile Passable
    setmaptile 0x11 0x11 OceanTile Passable
    setmaptile 0x10 0x11 OceanTile Passable
    setmaptile 0xF 0x11 OceanTile Passable
    setmaptile 0xE 0x11 OceanTile Passable
    setmaptile 0xE 0x10 OceanTile Passable
    setmaptile 0xD 0x10 OceanTile Passable
    setmaptile 0xC 0x10 OceanTile Passable
    setmaptile 0xB 0x10 OceanTile Passable
    setmaptile 0xB 0xF OceanTile Passable
    setmaptile 0xA 0xF OceanTile Passable
    setmaptile 0x9 0xF OceanTile Passable
    setmaptile 0x8 0xF OceanTile Passable
    setmaptile 0x7 0xF OceanTile Passable
    setmaptile 0x6 0xF OceanWithWestEdgeTile Passable
    return

SetSWCurrent:
    clearflag 0xE @ BoulderSW
    setmaptile 0x4 0x1B OceanWithWestEdgeTile Impassable
    setmaptile 0x5 0x1B OceanTile Passable
    setmaptile 0x6 0x1B OceanTile Passable
    setmaptile 0x7 0x1B OceanTile Passable
    setmaptile 0x8 0x1B OceanTile Passable
    setmaptile 0x9 0x1B OceanTile Passable
    setmaptile 0xA 0x1B OceanTile Passable
    setmaptile 0xB 0x1B OceanTile Passable
    setmaptile 0xC 0x1B OceanTile Passable
    setmaptile 0xD 0x1B OceanTile Passable
    setmaptile 0xD 0x1A OceanTile Passable
    setmaptile 0xD 0x19 OceanTile Passable
    setmaptile 0xE 0x19 OceanTile Passable
    setmaptile 0xE 0x18 OceanTile Passable
    setmaptile 0xE 0x17 OceanTile Passable
    setmaptile 0xE 0x16 OceanTile Passable
    setmaptile 0xE 0x15 OceanTile Passable
    setmaptile 0xE 0x14 OceanTile Passable
    setmaptile 0xF 0x14 OceanWithEastEdgeTile Passable
    return

SetSECurrent:
    clearflag 0xF @ BoulderSE
    setmaptile 0x20 0x19 OceanWithWestEdgeTile Impassable
    setmaptile 0x1F 0x19 OceanTile Passable
    setmaptile 0x1E 0x19 OceanTile Passable
    setmaptile 0x1D 0x19 OceanTile Passable
    setmaptile 0x1C 0x19 OceanTile Passable
    setmaptile 0x1B 0x19 OceanTile Passable
    setmaptile 0x1A 0x19 OceanTile Passable
    setmaptile 0x19 0x19 OceanTile Passable
    setmaptile 0x18 0x19 OceanTile Passable
    setmaptile 0x17 0x19 OceanTile Passable
    setmaptile 0x16 0x19 OceanTile Passable
    setmaptile 0x15 0x19 OceanTile Passable
    setmaptile 0x14 0x19 OceanTile Passable
    setmaptile 0x13 0x19 OceanTile Passable
    setmaptile 0x13 0x18 OceanTile Passable
    setmaptile 0x12 0x18 OceanTile Passable
    setmaptile 0x11 0x18 OceanTile Passable
    setmaptile 0x10 0x18 OceanTile Passable
    setmaptile 0xF 0x18 OceanTile Passable
    return

// Events
.global EventScript_SeppireCove_SwimmerValerie
EventScript_SeppireCove_SwimmerValerie:
    trainerbattle0 0x0 358 0x0 gText_SeppireCove_SwimmerValerie_Intro gText_SeppireCove_SwimmerValerie_Defeat
    msgbox gText_SeppireCove_SwimmerValerie_Chat MSG_NORMAL    
    end

.global EventScript_SeppireCove_SwimmerIchabod
EventScript_SeppireCove_SwimmerIchabod:
    trainerbattle0 0x0 359 0x0 gText_SeppireCove_SwimmerIchabod_Intro gText_SeppireCove_SwimmerIchabod_Defeat
    msgbox gText_SeppireCove_SwimmerIchabod_Chat MSG_NORMAL
    end

.global EventScript_SeppireCove_RuinManiacCarter
EventScript_SeppireCove_RuinManiacCarter:
    trainerbattle0 0x0 360 0x0 gText_SeppireCove_RuinManiacCarter_Intro gText_SeppireCove_RuinManiacCarter_Defeat
    msgbox gText_SeppireCove_RuinManiacCarter_Chat MSG_NORMAL
    end

.global ItemScript_SeppireCove_TM98_Waterfall
ItemScript_SeppireCove_TM98_Waterfall:
    setvar CHOSEN_ITEM ITEM_TM98
    call ItemScript_Common_FindTM
    end

.global EventScript_SeppireCove_Kyogre
EventScript_SeppireCove_Kyogre:
    msgbox gText_SeppireCove_EncounterKyogre MSG_NORMAL
    @ Todo later: Check for the blue orb and trigger a legendary battle
    msgbox gText_SeppireCove_KyogreDormant MSG_NORMAL
    end

.global SignScript_SeppireCove_Sign
SignScript_SeppireCove_Sign:
    msgbox gText_SeppireCove_Overworld_Sign MSG_SIGN
    end
