.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ LoudMan, 0x2
.equ Rival, 0x9
.equ StoryEventVar, 0x4052
.equ MetRivalAtGym, 0x1

.global MapScript_FerroxOverworld
MapScript_FerroxOverworld:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_FerroxOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_FerroxOverworld_FlightFlag:
    setworldmapflag 0x893
    compare StoryEventVar MetRivalAtGym
    if greaterorequal _call MoveLoudMan
    compare StoryEventVar MetRivalAtGym
    if lessorequal _call HideStellaInGym
    end

MoveLoudMan:
    movesprite2 LoudMan 0xA 0xD
    setobjectmovementtype LoudMan 0x2 @ Walk around
    return

HideStellaInGym:
    setflag 0x03B @ Hide Stella in Ferrox Gym
    return

.global EventScript_FerroxVillage_AngryLibraryVisitor
EventScript_FerroxVillage_AngryLibraryVisitor:
    npcchat gText_FerroxOverworld_AngryLibraryVisitor
    end

.global EventScript_FerroxVillage_EggFan
EventScript_FerroxVillage_EggFan:
    npcchat gText_FerroxOverworld_EggFan
    end

.global EventScript_FerroxVillage_FlowerKid
EventScript_FerroxVillage_FlowerKid:
    npcchat gText_FerroxOverworld_FlowerKid
    end

.global EventScript_FerroxVillage_AppleMan
EventScript_FerroxVillage_AppleMan:
    npcchat gText_FerroxOverworld_AppleMan
    end

.global EventScript_FerroxVillage_Policeman
EventScript_FerroxVillage_Policeman:
    npcchat gText_FerroxOverworld_Policeman
    end

.global SignScript_FerroxVillage_Library
SignScript_FerroxVillage_Library:
    msgbox gText_FerroxOverworld_LibrarySign MSG_SIGN
    end

.global SignScript_FerroxVillage_Gym
SignScript_FerroxVillage_Gym:
    msgbox gText_FerroxOverworld_GymSign MSG_SIGN
    end

.global SignScript_FerroxVillage_TownEntrance
SignScript_FerroxVillage_TownEntrance:
    msgbox gText_FerroxOverworld_TownEntranceSign MSG_SIGN
    end

.global TileScript_FerroxVillage_ApproachedGym
TileScript_FerroxVillage_ApproachedGym:
    lock
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    opendoor 0x25 0x10
    waitdooranim
	playbgm 0x195
    clearflag 0x2F @ Show Rival
    showsprite Rival
    pause DELAY_1SECOND
    applymovement PLAYER m_backup
    waitmovement ALLEVENTS
    applymovement Rival m_WalkDown
    waitmovement ALLEVENTS
    closedoor 0x25 0x10
    waitdooranim
    msgbox gText_FerroxOverworld_MeetingRival MSG_NORMAL
    applymovement Rival m_rivalLeaves
    waitmovement ALLEVENTS
    setflag 0x2F @ Hide Rival
    setvar StoryEventVar MetRivalAtGym
    hidesprite Rival
    fadedefaultbgm
    call MoveLoudMan
    release
	end

m_backup: .byte slide_down, look_up, end_m
m_rivalLeaves: .byte walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
