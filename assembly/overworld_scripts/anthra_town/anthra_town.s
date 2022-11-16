.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.equ Mom, 0x1
.equ Rival, 0x2

.global MapScript_AnthraTown_FlightSpot
MapScript_AnthraTown_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_AnthraTown_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_AnthraTown_FlightFlag:
    setworldmapflag 0x890
    end

.global EventScript_AnthraTown_FlowerGirl
EventScript_AnthraTown_FlowerGirl:
    msgbox gText_AnthraTown_FlowerGirl MSG_FACE
    end

.global EventScript_AnthraTown_TechnologyMan
EventScript_AnthraTown_TechnologyMan:
	npcchat gText_AnthraTown_TechnologyMan
	end

.global EventScript_AnthraTown_OldMan
EventScript_AnthraTown_OldMan:
    msgbox gText_AnthraTown_OldMan MSG_FACE
    end

.global EventScript_AnthraTown_MomMain
EventScript_AnthraTown_MomMain:
	lock
	faceplayer
	checkflag 0x258 @ First rival battle completed
	if SET _goto EventScript_AnthraTown_MomRestPrompt
	msgbox gText_AnthraTown_MomLeaveHome MSG_KEEPOPEN
	closeonkeypress
	applymovement Mom m_LookLeft
	waitmovement 0x0
	goto End

EventScript_AnthraTown_MomRestPrompt:
	msgbox gText_AnthraTown_MomRestPrompt MSG_KEEPOPEN
	closeonkeypress
	call EventScript_AnthraTown_MomRestAnimation
	msgbox gText_AnthraTown_MomPokemonAreHealthy MSG_KEEPOPEN
	release
	end

EventScript_AnthraTown_MomRestAnimation:
	fadescreen 0x1
	fanfare 0x100
	waitfanfare
	special 0x0
	fadescreen 0x0
	return

.global MapScript_AnthraTown_GameStartup
MapScript_AnthraTown_GameStartup:
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AnthraTown_GenChoice
	.byte MAP_SCRIPT_TERMIN

LevelScripts_AnthraTown_GenChoice:
	levelscript 0x4056 0 LevelScript_GenChoice_Main
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_GenChoice_Main:
	lock
	spriteface PLAYER look_down
	setvar 0x4056 0x1
	sethealingplace 0x01 @ Player's house
	setflag 0x911 @ Disable wild encounters
	clearflag 0x82F @ Ability to run
	msgbox gText_GenChoice_Msgwelcome MSG_YESNO
	compare LASTRESULT YES
	if TRUE _call EventScript_GenChoice_Favoritegen
	call EventScript_GenChoice_Shuffle
	end

EventScript_GenChoice_Favoritegen:
	msgbox gText_GenChoice_Msgfavoritegen MSG_KEEPOPEN
	multichoice 0x60 0x0 0x1 0x1
	copyvar 0x4011 LASTRESULT
	compare 0x4011 0x0
	if TRUE _call EventScript_GenChoice_Kantoconfirm
	compare 0x4011 0x1
	if TRUE _call EventScript_GenChoice_Johtoconfirm
	compare 0x4011 0x2
	if TRUE _call EventScript_GenChoice_Hoennconfirm
	compare 0x4011 0x3
	if TRUE _call EventScript_GenChoice_Sinnohconfirm
	compare 0x4011 0x4
	if TRUE _call EventScript_GenChoice_Unovaconfirm
	compare 0x4011 0x5
	if TRUE _call EventScript_GenChoice_Kalosconfirm
	compare 0x4011 0x6
	if TRUE _call EventScript_GenChoice_Alolaconfirm
	compare 0x4011 0x7
	if TRUE _call EventScript_GenChoice_Galarconfirm
	end

EventScript_GenChoice_Shuffle:
	msgbox gText_GenChoice_Msgshuffleconfirm MSG_YESNO
	compare LASTRESULT 0x1
	if 0x0 _call LevelScript_GenChoice_Main
	random 0x8
	copyvar 0x4011 LASTRESULT
	random 0x8
	copyvar 0x4012 LASTRESULT
	random 0x8
	copyvar 0x4013 LASTRESULT
	call EventScript_GenChoice_End
	end

EventScript_GenChoice_Kantoconfirm:
	msgbox gText_GenChoice_Msgkantoconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x0
	setvar 0x4013 0x0
	call EventScript_GenChoice_End

EventScript_GenChoice_Johtoconfirm:
	msgbox gText_GenChoice_Msgjohtoconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x1
	setvar 0x4013 0x1
	call EventScript_GenChoice_End

EventScript_GenChoice_Hoennconfirm:
	msgbox gText_GenChoice_Msghoennconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x2
	setvar 0x4013 0x2
	call EventScript_GenChoice_End

EventScript_GenChoice_Sinnohconfirm:
	msgbox gText_GenChoice_Msgsinnohconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x3
	setvar 0x4013 0x3
	call EventScript_GenChoice_End

EventScript_GenChoice_Unovaconfirm:
	msgbox gText_GenChoice_Msgunovaconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x4
	setvar 0x4013 0x4
	call EventScript_GenChoice_End

EventScript_GenChoice_Kalosconfirm:
	msgbox gText_GenChoice_Msgkalosconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x5
	setvar 0x4013 0x5
	call EventScript_GenChoice_End

EventScript_GenChoice_Alolaconfirm:
	msgbox gText_GenChoice_Msgalolaconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x6
	setvar 0x4013 0x6
	call EventScript_GenChoice_End

EventScript_GenChoice_Galarconfirm:
	msgbox gText_GenChoice_Msggalarconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x4012 0x7
	setvar 0x4013 0x7
	call EventScript_GenChoice_End

EventScript_GenChoice_Genchoiceconfirm:
	compare LASTRESULT 0x1
	if 0x0 _call EventScript_GenChoice_Reset
	return

EventScript_GenChoice_Reset:
	setvar 0x4011 0x0
	call LevelScript_GenChoice_Main

EventScript_GenChoice_End:
	sound 0x30 @Save
	msgbox gText_GenChoice_Msgcomplete MSG_KEEPOPEN
	release
	end

TileScript_AnthraTown_RivalArrival:
	compare 0x4055 0x1
	IF greaterorequal _goto End
	sound 0x15 @ Exclaim
	applymovement PLAYER m_Surprise
	msgbox gText_AnthraTown_RivalArrival MSG_NORMAL
	setvar 0x4055 0x1
	clearflag 0x02C @ Show the rival from this point forward (hidden by default by game startup)
	goto End

.global MapScript_AnthraTown_MeetingRival
MapScript_AnthraTown_MeetingRival:
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AnthraTown_MeetingRival
	.byte MAP_SCRIPT_TERMIN

LevelScripts_AnthraTown_MeetingRival:
	levelscript 0x4055 1 LevelScript_AnthraTown_MeetingRival
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_AnthraTown_MeetingRival:
	compare 0x4055 0x2
	if equal _goto End
	sound 0x15 @ Exclaim
	applymovement Rival m_Surprise
	pause DELAY_HALFSECOND
	applymovement Rival m_RivalWalkUp
	waitmovement ALLEVENTS
	msgbox gText_AnthraTown_MeetingRival MSG_YESNO
	switch LASTRESULT
	case YES, RememberingToday _call
	case NO, NotRememberingToday _call
	msgbox gText_AnthraTown_RivalExplainingChampionSeleneComing MSG_NORMAL
	applymovement Rival m_RivalRunOut
	waitmovement ALLEVENTS
	msgbox gText_AnthraTown_RivalPause MSG_NORMAL
	sound 0x15 @ Exclaim
	applymovement Rival m_Surprise
	waitmovement ALLEVENTS
	pause DELAY_HALFSECOND
	applymovement Rival m_RivalReturn
	waitmovement ALLEVENTS
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_RivalThanksMom MSG_NORMAL
	applymovement Rival m_LookUp
	msgbox gText_AnthraTown_RivalUrgesPlayer MSG_NORMAL
	applymovement Rival m_RivalRunOutAgain
	waitmovement ALLEVENTS
	sound 0x8 @ Door opening
	pause DELAY_HALFSECOND
	hidesprite Rival
	pause DELAY_HALFSECOND
	applymovement Mom m_LookUp
	applymovement PLAYER m_LookDown
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_MomEncouragesPlayer MSG_NORMAL
	applymovement Mom m_LookLeft
	setvar 0x4055 0x2
	setflag 0x02C @ Hide the rival from this point forward
	end

RememberingToday:
	msgbox gText_AnthraTown_RivalRememberingToday MSG_NORMAL
	return

NotRememberingToday:
	msgbox gText_AnthraTown_RivalNotRememberingToday MSG_NORMAL
	return

m_RivalWalkUp:
	.byte walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, look_right, end_m

m_RivalRunOut:
	.byte run_left, run_down, run_left, run_left, run_left, run_left, run_down, run_down, run_down, run_down, end_m

m_RivalReturn:
	.byte walk_up, walk_up, look_right, end_m

m_RivalRunOutAgain:
	.byte run_down, run_down, run_down, end_m
