.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_FerroxOverworld_FlightSpot
MapScript_FerroxOverworld_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_FerroxOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_FerroxOverworld_FlightFlag:
    setworldmapflag 0x893
    end

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
