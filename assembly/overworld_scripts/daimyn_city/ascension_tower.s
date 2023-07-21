.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_AscensionTower
MapScript_AscensionTower:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_AscensionTower_FlightFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_AscensionTower_FlightFlag:
    setworldmapflag 0x8B2 @ Been to Ascension Tower
    end

.global EventScript_AscensionTower_BattleTowerAttendant
EventScript_AscensionTower_BattleTowerAttendant:
    lock
    msgbox gText_AscensionTower_BattleTowerAttendant_Introduction MSG_KEEPOPEN
    multichoiceoption gText_Yes 0
	multichoiceoption gText_Info 1
	multichoiceoption gText_No 2
    multichoice 0x60 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, TakeBattleTowerChallenge
	case 1, BattleTowerInfo
	case 2, AttendantChoseNo
    goto AttendantChoseNo

TakeBattleTowerChallenge:
    @ Later, perform a check here for the champions flag
    msgbox gText_AscensionTower_BattleTowerAttendant_NotChampion MSG_NORMAL
    release
    end

BattleTowerInfo:
    msgbox gText_AscensionTower_EliteFourAttendant_BattleTowerInfo MSG_NORMAL
    goto EventScript_AscensionTower_BattleTowerAttendant

.global EventScript_AscensionTower_EliteFourAttendant
EventScript_AscensionTower_EliteFourAttendant:
    lock
    msgbox gText_AscensionTower_EliteFourAttendant_Introduction MSG_KEEPOPEN
    multichoiceoption gText_Yes 0
	multichoiceoption gText_Info 1
	multichoiceoption gText_No 2
    multichoice 0x60 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, TakeEliteFourChallenge
	case 1, EliteFourInfo
	case 2, AttendantChoseNo
    goto AttendantChoseNo

TakeEliteFourChallenge:
    @ Later, perform a check here for the champions flag
    msgbox gText_AscensionTower_BattleTowerAttendant_NotChampion MSG_NORMAL
    release
    end

EliteFourInfo:
    msgbox gText_AscensionTower_EliteFourAttendant_NoChampionsFlag MSG_NORMAL
    goto EventScript_AscensionTower_EliteFourAttendant

AttendantChoseNo:
    msgbox gText_AscensionTower_AttendantChoseNo MSG_NORMAL
    release
    end

.global EventScript_AscensionTower_Blackbelt
EventScript_AscensionTower_Blackbelt:
    npcchat gText_AscensionTower_KarateMan
    end

.global EventScript_AscensionTower_Girl
EventScript_AscensionTower_Girl:
    npcchat gText_AscensionTower_Girl
    end

.global EventScript_AscensionTower_BigMan
EventScript_AscensionTower_BigMan:
    npcchat gText_AscensionTower_BigMan
    end

.global SignScript_AscensionTower_RecordsBoard
SignScript_AscensionTower_RecordsBoard:
    @ Later, show player's E4 and Battle Tower records
    msgbox gText_AscensionTower_RecordsSign MSG_SIGN
    end
