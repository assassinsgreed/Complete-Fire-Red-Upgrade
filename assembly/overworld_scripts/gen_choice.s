.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global gMapScripts_GenChoice
gMapScripts_GenChoice:
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_GenChoice
	.byte MAP_SCRIPT_TERMIN

LevelScripts_GenChoice:
	levelscript 0x4056 0 LevelScript_GenChoice_Main
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_GenChoice_Main:
	lock
	spriteface PLAYER look_down
	setvar 0x4056 0x1
	msgbox gText_GenChoice_Msgwelcome MSG_YESNO
	compare LASTRESULT 0x1
	if 0x1 _call EventScript_GenChoice_Favoritegen
	call EventScript_GenChoice_Shuffle
	end

EventScript_GenChoice_Favoritegen:
	msgbox gText_GenChoice_Msgfavoritegen MSG_KEEPOPEN
	multichoice 0x60 0x0 0x1 0x1
	copyvar 0x4011 LASTRESULT
	compare 0x4011 0x0
	if 0x1 _call EventScript_GenChoice_Kantoconfirm
	compare 0x4011 0x1
	if 0x1 _call EventScript_GenChoice_Johtoconfirm
	compare 0x4011 0x2
	if 0x1 _call EventScript_GenChoice_Hoennconfirm
	compare 0x4011 0x3
	if 0x1 _call EventScript_GenChoice_Sinnohconfirm
	compare 0x4011 0x4
	if 0x1 _call EventScript_GenChoice_Unovaconfirm
	compare 0x4011 0x5
	if 0x1 _call EventScript_GenChoice_Kalosconfirm
	compare 0x4011 0x6
	if 0x1 _call EventScript_GenChoice_Alolaconfirm
	compare 0x4011 0x7
	if 0x1 _call EventScript_GenChoice_Galarconfirm
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
	msgbox gText_GenChoice_Msgcomplete MSG_KEEPOPEN
	release
	end
