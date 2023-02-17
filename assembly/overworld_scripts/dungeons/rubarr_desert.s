.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_RubarrDesert
MapScript_RubarrDesert:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RubarrDesert_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_RubarrDesert_SetWeather
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RubarrDesert_FlightFlag:
    setworldmapflag 0x8A5
    end

MapEntryScript_RubarrDesert_SetWeather:
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

.global EventScript_RubarrDesert_NurseJaina
EventScript_RubarrDesert_NurseJaina:
    faceplayer
    checktrainerflag 0x517
    if SET _goto NurseJainaHeal
    trainerbattle1 0x0 0x17 0x0 gText_RubarrDesert_NurseJaina_Intro gText_RubarrDesert_NurseJaina_Defeat NurseJainaHeal
    call NurseJainaHeal

NurseJainaHeal:
    msgbox gText_RubarrDesert_NurseJaina_Chat MSG_NORMAL
    call PlayerHeal
    msgbox gText_RubarrDesert_NurseJaina_HealingComplete MSG_NORMAL
    end

.global EventScript_RubarrDesert_BirdKeeperNolan
EventScript_RubarrDesert_BirdKeeperNolan:
    trainerbattle0 0x0 0x18 0x0 gText_RubarrDesert_BirdKeeperNolan_Intro gText_RubarrDesert_BirdKeeperNolan_Defeat
    msgbox gText_RubarrDesert_BirdKeeperNolan_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_RuinManiacKent
EventScript_RubarrDesert_RuinManiacKent:
    trainerbattle0 0x0 0x19 0x0 gText_RubarrDesert_RuinManiacKent_Intro gText_RubarrDesert_RuinManiacKent_Defeat
    msgbox gText_RubarrDesert_RuinManiacKent_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_BlackBeltKobiyashi
EventScript_RubarrDesert_BlackBeltKobiyashi:
    trainerbattle0 0x0 0x1A 0x0 gText_RubarrDesert_BlackBeltKobiyashi_Intro gText_RubarrDesert_BlackBeltKobiyashi_Defeat
    msgbox gText_RubarrDesert_BlackBeltKobiyashi_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_RuinManiacAlbert
EventScript_RubarrDesert_RuinManiacAlbert:
    trainerbattle0 0x0 0x1B 0x0 gText_RubarrDesert_RuinManiacAlbert_Intro gText_RubarrDesert_RuinManiacAlbert_Defeat
    msgbox gText_RubarrDesert_RuinManiacAlbert_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TMFlameCharge
EventScript_RubarrDesert_TMFlameCharge:
    setvar CHOSEN_ITEM ITEM_TM43
    call ItemScript_Common_FindTM
    end

.global EventScript_RubarrDesert_CaveGuide
EventScript_RubarrDesert_CaveGuide:
    faceplayer
    lockall    
    msgbox gText_RubarrDesert_TourGuideIntro MSG_YESNO
    compare LASTRESULT YES
    if true _call EventScript_RubarrDesert_CaveGuide_Info
    msgbox gText_RubarrDesert_TourGuideFarewell MSG_NORMAL
    release
    end

EventScript_RubarrDesert_CaveGuide_Info:
    msgbox gText_RubarrDesert_TourGuideDetails MSG_NORMAL
    return

.global SignScript_RubarrDesert_Oasis
SignScript_RubarrDesert_Oasis:
    msgbox gText_RubarrDesert_OasisSign MSG_SIGN
    end

.global EventScript_RubarrDesert_TeamPlutoMika
EventScript_RubarrDesert_TeamPlutoMika:
    trainerbattle0 0x0 0x1E 0x0 gText_RubarrDesert_TeamPlutoMika_Intro gText_RubarrDesert_TeamPlutoMika_Defeat
    msgbox gText_RubarrDesert_TeamPlutoMika_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TeamPlutoMarcel
EventScript_RubarrDesert_TeamPlutoMarcel:
    trainerbattle0 0x0 0x1F 0x0 gText_RubarrDesert_TeamPlutoMarcel_Intro gText_RubarrDesert_TeamPlutoMarcel_Defeat
    msgbox gText_RubarrDesert_TeamPlutoMarcel_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TeamPlutoTana
EventScript_RubarrDesert_TeamPlutoTana:
    trainerbattle0 0x0 0x20 0x0 gText_RubarrDesert_TeamPlutoTana_Intro gText_RubarrDesert_TeamPlutoTana_Defeat
    msgbox gText_RubarrDesert_TeamPlutoTana_Chat MSG_NORMAL
    end
