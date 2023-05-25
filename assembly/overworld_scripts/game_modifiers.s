.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

@ TODO: Trigger this only on game clear. See how system_scripts.s uses callasm DebugMenu_ProcessSetFlag
.global EventScript_Modifiers_Main
EventScript_Modifiers_Main:
	lock
	sound 0x2 @Log on SE
	msgbox gText_Modifiers_Msginteract MSG_KEEPOPEN
	multichoiceoption gText_Modifiers_OptionInverse 0
	multichoiceoption gText_Modifiers_OptionCatchTrainer 1
	multichoiceoption gText_Modifiers_OptionScaleWild 2
	multichoiceoption gText_Modifiers_OptionScaleTrainer 3
	multichoiceoption gText_Modifiers_OptionHiddenAbilities 4
	multichoiceoption gText_Modifiers_OptionShinies 5
	multichoiceoption gText_Modifiers_OptionRandomizer 6
	multichoice 0x60 0x0 SEVEN_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, EventScript_Modifiers_Inversebattle
	case 1, EventScript_Modifiers_Catchtrainer
	case 2, EventScript_Modifiers_Scalewild
	case 3, EventScript_Modifiers_Scaletrainer
	case 4, EventScript_Modifiers_Hiddenability
	case 5, EventScript_Modifiers_Shiny
	case 6, EventScript_Modifiers_Randomizer
	call EventScript_Modifiers_End
	end

.global EventScript_Modifiers_Inversebattle
EventScript_Modifiers_Inversebattle:
	msgbox gText_Modifiers_Msginverse MSG_KEEPOPEN
	checkflag 0x900
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Catchtrainer
EventScript_Modifiers_Catchtrainer:
	msgbox gText_Modifiers_Msgcatchtrainer MSG_KEEPOPEN
	checkflag 0x905
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Scalewild
EventScript_Modifiers_Scalewild:
	msgbox gText_Modifiers_Msgscalewild MSG_KEEPOPEN
	checkflag 0x90D
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Scaletrainer
EventScript_Modifiers_Scaletrainer:
	msgbox gText_Modifiers_Msgscaletrainer MSG_KEEPOPEN
	checkflag 0x90E
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Hiddenability
EventScript_Modifiers_Hiddenability:
	msgbox gText_Modifiers_Msghiddenability MSG_KEEPOPEN
	checkflag 0x90F
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Shiny
EventScript_Modifiers_Shiny:
	msgbox gText_Modifiers_Msgshiny MSG_KEEPOPEN
	checkflag 0x913
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Randomizer
EventScript_Modifiers_Randomizer:
	msgbox gText_Modifiers_Msgrandomizer MSG_KEEPOPEN
	checkflag 0x940
	if NOT_SET _call EventScript_Modifiers_Flagisoff
	call EventScript_Modifiers_Flagison
	end

.global EventScript_Modifiers_Flagisoff
EventScript_Modifiers_Flagisoff:
	msgbox gText_Modifiers_Msgflagisoff MSG_YESNO
	compare LASTRESULT 0x1
	if 0x0 _call EventScript_Modifiers_Main
	call EventScript_Modifiers_Flagnowon

.global EventScript_Modifiers_Flagison
EventScript_Modifiers_Flagison:
	msgbox gText_Modifiers_Msgflagison MSG_YESNO
	compare LASTRESULT 0x1
	if 0x0 _call EventScript_Modifiers_Main
	call EventScript_Modifiers_Flagnowoff

.global EventScript_Modifiers_Flagnowoff
EventScript_Modifiers_Flagnowoff:
	sound 0x30 @Save
	msgbox gText_Modifiers_Msgflagnowoff MSG_KEEPOPEN
	switch MULTICHOICE_SELECTION
	case 0, EventScript_Modifiers_Clearinverse
	case 1, EventScript_Modifiers_Clearcatchtrainer
	case 2, EventScript_Modifiers_Clearscalewild
	case 3, EventScript_Modifiers_Clearscaletrainer
	case 4, EventScript_Modifiers_Clearhiddenability
	case 5, EventScript_Modifiers_Clearshiny
	case 6, EventScript_Modifiers_Clearrandomizer
	call EventScript_Modifiers_Main

.global EventScript_Modifiers_Flagnowon
EventScript_Modifiers_Flagnowon:
	sound 0x30 @Save
	msgbox gText_Modifiers_Msgflagnowon MSG_KEEPOPEN
	switch MULTICHOICE_SELECTION
	case 0, EventScript_Modifiers_Setinverse
	case 1, EventScript_Modifiers_Setcatchtrainer
	case 2, EventScript_Modifiers_Setscalewild
	case 3, EventScript_Modifiers_Setscaletrainer
	case 4, EventScript_Modifiers_Sethiddenability
	case 5, EventScript_Modifiers_Setshiny
	case 6, EventScript_Modifiers_Setrandomizer
	call EventScript_Modifiers_Main

.global EventScript_Modifiers_Clearinverse
EventScript_Modifiers_Clearinverse:
	clearflag 0x900 @ Turn off inverse
	return

.global EventScript_Modifiers_Clearcatchtrainer
EventScript_Modifiers_Clearcatchtrainer:
	clearflag 0x905 @ Turn off catch trainer
	return

.global EventScript_Modifiers_Clearscalewild
EventScript_Modifiers_Clearscalewild:
	clearflag 0x90D @ Turn off scale wild
	return

.global EventScript_Modifiers_Clearscaletrainer
EventScript_Modifiers_Clearscaletrainer:
	clearflag 0x90E @ Turn off scale trainer
	clearflag 0x4FF @ Do not turn off level scaling in trainer houses
	return

.global EventScript_Modifiers_Clearhiddenability
EventScript_Modifiers_Clearhiddenability:
	clearflag 0x90F @ Turn off hidden ability
	return

.global EventScript_Modifiers_Clearshiny
EventScript_Modifiers_Clearshiny:
	clearflag 0x913 @ Turn off shiny
	return

.global EventScript_Modifiers_Clearrandomizer
EventScript_Modifiers_Clearrandomizer:
	clearflag 0x940 @ Turn off randomizer
	return

.global EventScript_Modifiers_Setinverse
EventScript_Modifiers_Setinverse:
	setflag 0x900 @ Turn on inverse
	return

.global EventScript_Modifiers_Setcatchtrainer
EventScript_Modifiers_Setcatchtrainer:
	setflag 0x905 @ Turn on catch trainer
	return

.global EventScript_Modifiers_Setscalewild
EventScript_Modifiers_Setscalewild:
	setflag 0x90D @ Turn on scale wild
	return

.global EventScript_Modifiers_Setscaletrainer
EventScript_Modifiers_Setscaletrainer:
	setflag 0x90E @ Turn on scale trainer
	setflag 0x4FF @ Do not turn off level scaling in trainer houses
	return

.global EventScript_Modifiers_Sethiddenability
EventScript_Modifiers_Sethiddenability:
	setflag 0x90F @ Turn on hidden ability
	return

.global EventScript_Modifiers_Setshiny
EventScript_Modifiers_Setshiny:
	setflag 0x913 @ Turn on shiny
	return

.global EventScript_Modifiers_Setrandomizer
EventScript_Modifiers_Setrandomizer:
	setflag 0x940 @ Turn on randomizer
	clearflag 0x930 @ Hack: turn off the battle facility (which disables randomizer)
	return

.global EventScript_Modifiers_End
EventScript_Modifiers_End:
	setvar MULTICHOICE_SELECTION 0x0
	sound 0x4 @Log off SE
	msgbox gText_Modifiers_Msgend MSG_KEEPOPEN
	release
	end
