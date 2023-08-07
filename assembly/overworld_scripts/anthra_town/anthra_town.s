.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Mom, 0x1
.equ Rival, 0x2
.equ RivalInAnthraOverworld, 0x8
.equ StoryEventVar, 0x4055
.equ PlayerCalledDownstairs, 0x1
.equ PlayerMetWithRivalAtHouse, 0x2
.equ PlayerMetWithRival, 0x3
.equ PlayerAllowedToGoOnJourney, 0x4
.equ PlayerAndRivalCanGoOnJourney, 0x5

.global MapScript_AnthraTown
MapScript_AnthraTown:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_AnthraTown_FlightSpot
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AnthraTown_MeetingWithRival
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_AnthraTown_FlightSpot:
    setworldmapflag 0x890
    end

LevelScripts_AnthraTown_MeetingWithRival:
	levelscript StoryEventVar PlayerAllowedToGoOnJourney LevelScript_DepartingWithRival
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_DepartingWithRival:
	pause DELAY_HALFSECOND
	playbgm 0x195
	applymovement RivalInAnthraOverworld m_RivalMeetPlayerAtJourneyStart
	waitmovement ALLEVENTS
	msgbox gText_AnthraTown_RivalCanGoOnJourney MSG_NORMAL
	sound 0x15 @ Exclaim
	applymovement RivalInAnthraOverworld m_Surprise
	msgbox gText_AnthraTown_ReturnToSeleneAndHawthorne MSG_NORMAL
	applymovement RivalInAnthraOverworld m_RivalReturnsToRoute17
	waitmovement ALLEVENTS
	hidesprite RivalInAnthraOverworld
	setflag 0x02F @ Hide rival in Anthra overworld
	clearflag 0x02D @ Show rival on route 17
	setvar StoryEventVar PlayerAndRivalCanGoOnJourney
	fadedefaultbgm
	end

MapEntryScript_PlayersHouse_HealingSpot:
    sethealingplace 0x01 @ Player's House
    end

.global EventScript_AnthraTown_PlayersPoster
EventScript_AnthraTown_PlayersPoster:
	msgbox gText_AnthraTown_PlayersPoster MSG_NORMAL
	end

.global EventScript_AnthraTown_NESClassic
EventScript_AnthraTown_NESClassic:
	msgbox gText_AnthraTown_NESClassic MSG_NORMAL
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

.global EventScript_AnthraTown_Gabby
EventScript_AnthraTown_Gabby:
	npcchat gText_AnthraTown_Gabby
	end

.global EventScript_AnthraTown_Ty
EventScript_AnthraTown_Ty:
	npcchat gText_AnthraTown_Ty
	end

.global EventScript_AnthraTown_FootprintGuy
EventScript_AnthraTown_FootprintGuy:
	compare StoryEventVar 0x7 @ Player can go on journey
	if equal _goto End
	compare LASTTALKED 0x6
	if equal _call LookDown
	npcchatwithmovement gText_AnthraTown_FootprintGuy m_LookUp
	compare LASTTALKED 0x6
	if notequal _call PlayerWalkBack
	setvar LASTTALKED 0xFF
	end

PlayerWalkBack:
	applymovement PLAYER m_WalkRight
	return

.global EventScript_AnthraTown_RivalMom
EventScript_AnthraTown_RivalMom:
	lock
	compare StoryEventVar PlayerMetWithRivalAtHouse
	if lessorequal _goto EventScript_AnthraTown_RivalMomBeforeProfessor
	compare StoryEventVar PlayerMetWithRival
	if lessorequal _goto EventScript_AnthraTown_RivalMomPersuaded
	faceplayer
	msgbox gText_AnthraTown_RivalMomAfterJourneyStarts MSG_NORMAL
	release
	end

EventScript_AnthraTown_RivalMomBeforeProfessor:
	faceplayer
	msgbox gText_AnthraTown_RivalMom MSG_NORMAL
	release
	end

EventScript_AnthraTown_RivalMomPersuaded:
	msgbox gText_AnthraTown_RivalMomBeingPersuaded MSG_NORMAL
	release
	end

.global EventScript_AnthraTown_RivalInTheirHome
EventScript_AnthraTown_RivalInTheirHome:
	msgbox gText_AnthraTown_RivalPersuadingMom MSG_NORMAL
	release
	end

.global EventScript_AnthraTown_MomMain
EventScript_AnthraTown_MomMain:
	lock
	faceplayer
	checkflag 0x258 @ First rival battle completed
	if SET _goto EventScript_AnthraTown_MomRestPrompt
	compare StoryEventVar PlayerMetWithRival
	if equal _goto EventScript_AnthraTown_PersuadingMomToGoOnJourney
	msgbox gText_AnthraTown_MomLeaveHome MSG_KEEPOPEN
	closeonkeypress
	applymovement Mom m_LookLeft
	waitmovement 0x0
	goto End

EventScript_AnthraTown_MomRestPrompt:
	msgbox gText_AnthraTown_MomRestPrompt MSG_KEEPOPEN
	closeonkeypress
	call PlayerHeal
	msgbox gText_AnthraTown_MomPokemonAreHealthy MSG_KEEPOPEN
	release
	end

EventScript_AnthraTown_PersuadingMomToGoOnJourney:
	msgbox gText_AnthraTown_ConvincingPlayerMom MSG_YESNO
	compare LASTRESULT YES
	if notequal _goto EventScript_AnthraTown_MomPlayerSaidNoToAccompanyingRival
	msgbox gText_AnthraTown_MomGivesRunningShoes MSG_NORMAL
	call EnableRunningShoes
	normalmsg
	msgbox gText_AnthraTown_MomGivesTownMap MSG_NORMAL
	obtainitem ITEM_TOWN_MAP 0x1
	msgbox gText_AnthraTown_MomSendsPlayerOff MSG_NORMAL
	setvar StoryEventVar PlayerAllowedToGoOnJourney
	setflag 0x002E @ Hide rival in their home
	clearflag 0x02F @ Show rival in Anthra Overworld
	end

EventScript_AnthraTown_MomPlayerSaidNoToAccompanyingRival:
	msgbox gText_AnthraTown_ConvincingPlayerMom_PlayerDeclined MSG_NORMAL
	applymovement Mom m_LookLeft
	end

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
	clearflag 0x82F @ Ability to run
	msgboxsign
	msgbox gText_GenChoice_Msgwelcome MSG_YESNO
	compare LASTRESULT YES
	if TRUE _call EventScript_GenChoice_Favoritegen
	call EventScript_GenChoice_Shuffle
	end

EventScript_GenChoice_Favoritegen:
	msgbox gText_GenChoice_Msgfavoritegen MSG_KEEPOPEN
	setvar 0x8000 0x5
    setvar 0x8001 0x4
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, EventScript_GenChoice_Kantoconfirm
	case 1, EventScript_GenChoice_Johtoconfirm
	case 2, EventScript_GenChoice_Hoennconfirm
	case 3, EventScript_GenChoice_Sinnohconfirm
	case 4, EventScript_GenChoice_Unovaconfirm
	case 5, EventScript_GenChoice_Kalosconfirm
	case 6, EventScript_GenChoice_Alolaconfirm
	case 7, EventScript_GenChoice_Galarconfirm
	end

EventScript_GenChoice_Shuffle:
	msgbox gText_GenChoice_Msgshuffleconfirm MSG_YESNO
	compare LASTRESULT 0x1
	if 0x0 _call LevelScript_GenChoice_Main
	random 0x8
	copyvar 0x408C LASTRESULT
	random 0x8
	copyvar 0x408D LASTRESULT
	random 0x8
	copyvar 0x408E LASTRESULT
	call EventScript_GenChoice_End
	end

EventScript_GenChoice_Kantoconfirm:
	msgbox gText_GenChoice_Msgkantoconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x0
	setvar 0x408D 0x0
	setvar 0x408E 0x0
	call EventScript_GenChoice_End

EventScript_GenChoice_Johtoconfirm:
	msgbox gText_GenChoice_Msgjohtoconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x1
	setvar 0x408D 0x1
	setvar 0x408E 0x1
	call EventScript_GenChoice_End

EventScript_GenChoice_Hoennconfirm:
	msgbox gText_GenChoice_Msghoennconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x2
	setvar 0x408D 0x2
	setvar 0x408E 0x2
	call EventScript_GenChoice_End

EventScript_GenChoice_Sinnohconfirm:
	msgbox gText_GenChoice_Msgsinnohconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x3
	setvar 0x408D 0x3
	setvar 0x408E 0x3
	call EventScript_GenChoice_End

EventScript_GenChoice_Unovaconfirm:
	msgbox gText_GenChoice_Msgunovaconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x4
	setvar 0x408D 0x4
	setvar 0x408E 0x4
	call EventScript_GenChoice_End

EventScript_GenChoice_Kalosconfirm:
	msgbox gText_GenChoice_Msgkalosconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x5
	setvar 0x408D 0x5
	setvar 0x408E 0x5
	call EventScript_GenChoice_End

EventScript_GenChoice_Alolaconfirm:
	msgbox gText_GenChoice_Msgalolaconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x6
	setvar 0x408D 0x6
	setvar 0x408E 0x6
	call EventScript_GenChoice_End

EventScript_GenChoice_Galarconfirm:
	msgbox gText_GenChoice_Msggalarconfirm MSG_YESNO
	call EventScript_GenChoice_Genchoiceconfirm
	setvar 0x408C 0x7
	setvar 0x408D 0x7
	setvar 0x408E 0x7
	call EventScript_GenChoice_End

EventScript_GenChoice_Genchoiceconfirm:
	compare LASTRESULT 0x1
	if 0x0 _call EventScript_GenChoice_Reset
	return

EventScript_GenChoice_Reset:
	setvar 0x408C 0x0
	setvar 0x408D 0x0
	setvar 0x408E 0x0
	call LevelScript_GenChoice_Main

EventScript_GenChoice_End:
	sound 0x30 @Save
	msgbox gText_GenChoice_Msgcomplete MSG_KEEPOPEN
	normalmsg
	release
	end

TileScript_AnthraTown_RivalArrival:
	compare StoryEventVar PlayerCalledDownstairs
	IF greaterorequal _goto End
	sound 0x15 @ Exclaim
	applymovement PLAYER m_Surprise
	msgbox gText_AnthraTown_RivalArrival MSG_NORMAL
	setvar StoryEventVar PlayerCalledDownstairs
	clearflag 0x02B @ Show the professor, champion, and tv crew from this point forward (hidden by default by game setup)
	clearflag 0x02C @ Show the rival from this point forward (hidden by default by game startup)
	goto End

.global MapScript_AnthraTown_MeetingRival
MapScript_AnthraTown_MeetingRival:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_PlayersHouse_HealingSpot
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_AnthraTown_MeetingRival
	.byte MAP_SCRIPT_TERMIN

LevelScripts_AnthraTown_MeetingRival:
	levelscript StoryEventVar PlayerCalledDownstairs LevelScript_AnthraTown_MeetingRival
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_AnthraTown_MeetingRival:
	compare StoryEventVar PlayerMetWithRivalAtHouse
	if equal _goto End
	sound 0x15 @ Exclaim
	applymovement Rival m_Surprise
	pause DELAY_HALFSECOND
	playbgm 0x195
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
	fadedefaultbgm
	pause DELAY_HALFSECOND
	applymovement Mom m_LookUp
	applymovement PLAYER m_LookDown
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_MomEncouragesPlayer MSG_NORMAL
	applymovement Mom m_LookLeft
	setvar StoryEventVar PlayerMetWithRivalAtHouse
	setflag 0x02C @ Hide the rival from this point forward
	setflag 0x02E @ Hide rival in their house
	setflag 0x02F @ Hide rival in Anthra Town overworld
	setflag 0x028 @ Hide grass starter ball on route 17
	setflag 0x029 @ Hide water starter ball on route 17
	setflag 0x02A @ Hide fire starter ball on route 17
	setflag 0x911 @ Disable wild encounters
	end

RememberingToday:
	msgbox gText_AnthraTown_RivalRememberingToday MSG_NORMAL
	return

NotRememberingToday:
	msgbox gText_AnthraTown_RivalNotRememberingToday MSG_NORMAL
	return

m_RivalWalkUp: .byte walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, look_right, end_m
m_RivalRunOut: .byte run_left, run_down, run_left, run_left, run_left, run_left, run_down, run_down, run_down, run_down, end_m
m_RivalReturn: .byte walk_up, walk_up, look_right, end_m
m_RivalRunOutAgain: .byte run_down, run_down, run_down, end_m
m_RivalMeetPlayerAtJourneyStart: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, look_up, end_m
m_RivalReturnsToRoute17: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
