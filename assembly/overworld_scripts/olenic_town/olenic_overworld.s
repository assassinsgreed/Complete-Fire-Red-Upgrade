.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_OlenicTown
MapScript_OlenicTown:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_OlenicTown_FlightSpot
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_OlenicTown_FlightSpot:
    setworldmapflag 0x891
    end

.global SignScript_OlenicOverworld_HawthornesLab
SignScript_OlenicOverworld_HawthornesLab:
    msgbox gText_OlenicOverworld_HawthornsLabSign MSG_SIGN
    end

.global EventScript_OlenicOverworld_NewTrainers
EventScript_OlenicOverworld_NewTrainers:
    npcchat gText_OlenicOverworld_NewTrainers
    end

.global EventScript_OlenicOverworld_GameKid
EventScript_OlenicOverworld_GameKid:
    npcchat2 0x2 m_LookDown gText_OlenicOverworld_GameKid
    end

.global EventScript_OlenicOverworld_OldLady
EventScript_OlenicOverworld_OldLady:
    npcchat gText_OlenicOverworld_OldLady
    end

.global EventScript_OlenicOverworld_HawthorneFan
EventScript_OlenicOverworld_HawthorneFan:
    npcchat gText_OlenicOverworld_HawthorneFan
    end

.global EventScript_OlenicOverworld_FindTMSwagger
EventScript_OlenicOverworld_FindTMSwagger:
    setvar CHOSEN_ITEM ITEM_TM87
    call ItemScript_Common_FindTM
    end
    
