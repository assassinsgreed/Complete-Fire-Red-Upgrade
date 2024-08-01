.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_CarnelidgeVolcano
MapScript_CarnelidgeVolcano:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_CarnelidgeVolcano_FlightFlagAndWalkingScript
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_CarnelidgeVolcano_FlightFlagAndWalkingScript:
    setworldmapflag 0x8AB
    setvar 0x500B 0x2 @ Use walking script #2, i.e. "mountain tremors." This is cleared if the player the first time it executes, if the player isn't on a mount carnelidge map
    setvar 0x400E 0x1 @ Used to control whether the tremor is active or not
    end

.global CarnelidgeVolcano_Tremors
CarnelidgeVolcano_Tremors:
    call DisableWalkingScriptIfOnInvalidMap
    release
    compare 0x4002 0x1
    if equal _goto End @ Don't trigger a tremor while another one is live
    random 100 @ 1% chance for heavy tremor, 4% chance for light tremor
    compare LASTRESULT 1
    if lessthan _goto HeavyTremor
    compare LASTRESULT 5
    if lessthan _goto LightTremor
    end

HeavyTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x3 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x15 @ This controls how long the overall animation lasts
	setvar 0x8007 0x3 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

LightTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x1 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x10 @ This controls how long the overall animation lasts
	setvar 0x8007 0x1 @ This controls how long one screen shake lasts
    playse 0x21 @ Small tremor
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

.global EventScript_CarnelidgeVolcano_HikerBjorn
EventScript_CarnelidgeVolcano_HikerBjorn:
    trainerbattle0 0x0 460 0x0 gText_CarnelidgeVolcano_HikerBjorn_Intro gText_CarnelidgeVolcano_HikerBjorn_Defeat
    msgbox gText_CarnelidgeVolcano_HikerBjorn_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_ChannelerKelsey
EventScript_CarnelidgeVolcano_ChannelerKelsey:
    trainerbattle0 0x0 461 0x0 gText_CarnelidgeVolcano_ChannelerKelsey_Intro gText_CarnelidgeVolcano_ChannelerKelsey_Defeat
    msgbox gText_CarnelidgeVolcano_ChannelerKelsey_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_JugglerSeth
EventScript_CarnelidgeVolcano_JugglerSeth:
    trainerbattle0 0x0 462 0x0 gText_CarnelidgeVolcano_JugglerSeth_Intro gText_CarnelidgeVolcano_JugglerSeth_Defeat
    msgbox gText_CarnelidgeVolcano_JugglerSeth_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_DragonTamerFlynn
EventScript_CarnelidgeVolcano_DragonTamerFlynn:
    trainerbattle0 0x0 463 0x0 gText_CarnelidgeVolcano_DragonTamerFlynn_Intro gText_CarnelidgeVolcano_DragonTamerFlynn_Defeat
    msgbox gText_CarnelidgeVolcano_DragonTamerFlynn_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_BirdKeeperFalco
EventScript_CarnelidgeVolcano_BirdKeeperFalco:
    trainerbattle0 0x0 464 0x0 gText_CarnelidgeVolcano_BirdKeeperFalco_Intro gText_CarnelidgeVolcano_BirdKeeperFalco_Defeat
    msgbox gText_CarnelidgeVolcano_BirdKeeperFalco_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_CrushGirlEunice
EventScript_CarnelidgeVolcano_CrushGirlEunice:
    trainerbattle0 0x0 465 0x0 gText_CarnelidgeVolcano_CrushGirlEunice_Intro gText_CarnelidgeVolcano_CrushGirlEunice_Defeat
    msgbox gText_CarnelidgeVolcano_CrushGirlEunice_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_SuperNerdNathan
EventScript_CarnelidgeVolcano_SuperNerdNathan:
    trainerbattle0 0x0 466 0x0 gText_CarnelidgeVolcano_SuperNerdNathan_Intro gText_CarnelidgeVolcano_SuperNerdNathan_Defeat
    msgbox gText_CarnelidgeVolcano_SuperNerdNathan_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_HikerHugh
EventScript_CarnelidgeVolcano_HikerHugh:
    trainerbattle0 0x0 467 0x0 gText_CarnelidgeVolcano_HikerHugh_Intro gText_CarnelidgeVolcano_HikerHugh_Defeat
    msgbox gText_CarnelidgeVolcano_HikerHugh_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_ScientistXander
EventScript_CarnelidgeVolcano_ScientistXander:
    trainerbattle0 0x0 468 0x0 gText_CarnelidgeVolcano_ScientistXander_Intro gText_CarnelidgeVolcano_ScientistXander_Defeat
    msgbox gText_CarnelidgeVolcano_ScientistXander_Chat MSG_NORMAL
    end

.global EventScript_CarnelidgeVolcano_CharizarditeY
EventScript_CarnelidgeVolcano_CharizarditeY:
    finditem ITEM_CHARIZARDITE_Y 0x1
    end

.global EventScript_CarnelidgeVolcano_TM50_Overheat
EventScript_CarnelidgeVolcano_TM50_Overheat:
    setvar CHOSEN_ITEM ITEM_TM50
    call ItemScript_Common_FindTM
    end

.global EventScript_CarnelidgeVolcano_TM38_FireBlast
EventScript_CarnelidgeVolcano_TM38_FireBlast:
    setvar CHOSEN_ITEM ITEM_TM38
    call ItemScript_Common_FindTM
    end

.global TileScript_CarnelidgeVolcano_VolcanionRoom
TileScript_CarnelidgeVolcano_VolcanionRoom:
    checkflag 0x4BC @ Became champion
    if SET _goto End
    lock
    msgbox gText_CarnelidgeVolcano_VolcanionPresenceFelt MSG_NORMAL
    setvar 0x4000 0x1 @ Don't trigger this until the player returns
    end

.global SignScript_CarnelidgeVolcano_EntrySign
SignScript_CarnelidgeVolcano_EntrySign:
    msgbox gText_CarnelidgeVolcano_EntranceSign MSG_SIGN
    end    

.global SignScript_CarnelidgeVolcano_TrainerTips
SignScript_CarnelidgeVolcano_TrainerTips:
    msgbox gText_CarnelidgeVolcano_TrainerTipsSign MSG_SIGN
    end

.global SignScript_CarnelidgeVolcano_HotSpringSign
SignScript_CarnelidgeVolcano_HotSpringSign:
    msgbox gText_CarnelidgeVolcano_HotSpringsSign MSG_SIGN
    end
