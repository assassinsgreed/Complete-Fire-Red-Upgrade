.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_LaplazTown
MapScript_LaplazTown:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_LaplazTown_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_LaplazTown_FlightSpot:
    setworldmapflag 0x896 @ Visited Laplaz Town
    end

.global EventScript_LaplazTown_Girl
EventScript_LaplazTown_Girl:
    npcchat gText_LaplazTown_Overworld_Girl
    end

.global EventScript_LaplazTown_OldMan
EventScript_LaplazTown_OldMan:
    faceplayer
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto OldManNoGymLeader
    msgbox gText_LaplazTown_Overworld_OldMan_MetCaseyInGym MSG_NORMAL
    end

OldManNoGymLeader:
    msgbox gText_LaplazTown_Overworld_OldMan_NotMetCaseyInGym MSG_NORMAL
    end

.global EventScript_LaplazTown_FatMan
EventScript_LaplazTown_FatMan:
    npcchat gText_LaplazTown_Overworld_FatMan
    end

.global EventScript_LaplazTown_YoungBoy
EventScript_LaplazTown_YoungBoy:
    npcchat gText_LaplazTown_Overworld_YoungBoy
    end

.global SignScript_LaplazTown_TrainerHouse
SignScript_LaplazTown_TrainerHouse:
    msgbox gText_LaplazTown_Overworld_TrainerHouseSign MSG_SIGN
    end

.global SignScript_LaplazTown_PeradonForest
SignScript_LaplazTown_PeradonForest:
    msgbox gText_LaplazTown_Overworld_PeradonForestSign MSG_SIGN
    end

.global SignScript_LaplazTown_ApricornBallShop
SignScript_LaplazTown_ApricornBallShop:
    msgbox gText_LaplazTown_Overworld_ApricornBallShopSign MSG_SIGN
    end

.global SignScript_LaplazTown_PsychicsHouse
SignScript_LaplazTown_PsychicsHouse:
    msgbox gText_LaplazTown_Overworld_PsychicsHouseSign MSG_SIGN
    end

.global SignScript_LaplazTown_GymSign
SignScript_LaplazTown_GymSign:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto GymSignNotMetCasey
    msgbox gText_LaplazTown_Overworld_GymSign_MetCaseyInGym MSG_NORMAL
    end

GymSignNotMetCasey:
    msgbox gText_LaplazTown_Overworld_GymSign_NotMetCaseyInGym MSG_SIGN
    end
