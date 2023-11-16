.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route12RestHouse
MapScript_Route12RestHouse:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_Route12_RestHouse_FlightFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route12_RestHouse_FlightFlag:
    setworldmapflag 0x89B @ Visited Route 12 Rest House
    sethealingplace 0xD @ Route 12 Rest House
    end

.global EventScript_Route12RestHouse_Boy
EventScript_Route12RestHouse_Boy:
    npcchatwithmovement gText_Route12RestHouse_Boy m_LookDown
    end

.global EventScript_Route12RestHouse_YoungGirl
EventScript_Route12RestHouse_YoungGirl:
    npcchatwithmovement gText_Route12RestHouse_YoungGirl m_LookDown
    end

.global EventScript_Route12RestHouse_PoliceOfficer
EventScript_Route12RestHouse_PoliceOfficer:
    npcchatwithmovement gText_Route12RestHouse_PoliceOfficer m_LookDown
    end

.global EventScript_Route12RestHouse_PsychicGirl
EventScript_Route12RestHouse_PsychicGirl:
    npcchatwithmovement gText_Route12RestHouse_PsychicGirl m_LookDown
    end

.global EventScript_Route12RestHouse_OldMan
EventScript_Route12RestHouse_OldMan:
    npcchatwithmovement gText_Route12RestHouse_OldMan m_LookLeft
    end

.global EventScript_Route12RestHouse_Girl
EventScript_Route12RestHouse_Girl:
    npcchatwithmovement gText_Route12RestHouse_Girl m_LookRight
    end

.global EventScript_Route12RestHouse_Dad
EventScript_Route12RestHouse_Dad:
    npcchatwithmovement gText_Route12RestHouse_Dad m_LookLeft
    end

.global EventScript_Route12RestHouse_GameboyKid
EventScript_Route12RestHouse_GameboyKid:
    npcchatwithmovement gText_Route12RestHouse_GameboyKid m_LookDown
    end

.global EventScript_Route12RestHouse_Hiker
EventScript_Route12RestHouse_Hiker:
    npcchat gText_Route12RestHouse_Hiker
    end

.global EventScript_Route12RestHouse_PokemartMan
EventScript_Route12RestHouse_PokemartMan:
    npcchat gText_Route12RestHouse_PokemartMan
    end

.global EventScript_Route12RestHouse_Beauty
EventScript_Route12RestHouse_Beauty:
    npcchatwithmovement gText_Route12RestHouse_Beauty m_LookUp
    end
