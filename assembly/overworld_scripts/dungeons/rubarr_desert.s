.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global MapScript_RubarrDesert
MapScript_RubarrDesert:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RubarrDesert_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_RubarrDesert_SetWeather
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RubarrDesert_FlightFlag:
    setworldmapflag 0x8A5
    end

MapEntryScript_RubarrDesert_SetWeather:
    @ TODO: Setting weather breaks DNS for some reason
    @ Check time of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x02 @ Evening
    if lessthan _goto SetAllWeatherTypes @ Is morning or day, set clear, sandstorm, or sunny
    @ Is evening or night, set clear skies or sandstorm only
    random 0x9 @ Between 0 and 9
    compare 0x800D 0x5 @ "6"
    if lessthan _call SetWeatherClear
    compare 0x800D 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    end

SetAllWeatherTypes:
    random 0x9 @ Between 0 and 9
    compare 0x800D 0x4 @ "5"
    if lessthan _call SetWeatherSunny
    compare 0x800D 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    @ Otherwise, leave as regular weather
    end
