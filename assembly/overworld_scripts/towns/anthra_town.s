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
	setvar 0x406F 0x0 @ Disable credits, in case the player exited the game after entering the Hall of Fame
    end

LevelScripts_AnthraTown_MeetingWithRival:
	levelscript StoryEventVar PlayerAllowedToGoOnJourney LevelScript_DepartingWithRival
	levelscript 0x4070 0x1 LevelScript_PostCreditsParty
	levelscript 0x4070 0x2 LevelScript_PostCreditsEclipse
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
	call ResetRoute11PlutoEventOnWhiteout
	call ResetUteyaVillageGymFlagsOnWhiteout
    end

.global EventScript_AnthraTown_PlayersPoster
EventScript_AnthraTown_PlayersPoster:
	lock
	msgbox gText_AnthraTown_PlayersPoster MSG_NORMAL
	end

.global EventScript_AnthraTown_NESClassic
EventScript_AnthraTown_NESClassic:
	lock
	msgbox gText_AnthraTown_NESClassic MSG_NORMAL
	end

.global EventScript_AnthraTown_FlowerGirl
EventScript_AnthraTown_FlowerGirl:
    npcchatwithmovement gText_AnthraTown_FlowerGirl m_LookLeft
    end

.global EventScript_AnthraTown_TechnologyMan
EventScript_AnthraTown_TechnologyMan:
	npcchat gText_AnthraTown_TechnologyMan
	end

.global EventScript_AnthraTown_OldMan
EventScript_AnthraTown_OldMan:
    npcchatwithmovement gText_AnthraTown_OldMan m_LookRight
    end

.global EventScript_AnthraTown_Gabby
EventScript_AnthraTown_Gabby:
	npcchatwithmovement gText_AnthraTown_Gabby m_LookUp
	end

.global EventScript_AnthraTown_Ty
EventScript_AnthraTown_Ty:
	npcchatwithmovement gText_AnthraTown_Ty m_LookLeft
	end

.global EventScript_AnthraTown_FootprintGuy
EventScript_AnthraTown_FootprintGuy:
	compare StoryEventVar 0x7 @ Player can go on journey
	if equal _goto End
	getplayerpos 0x4001 0x4002
	compare 0x4001 0x1
	if equal _call PlayerAlarmed
	npcchatwithmovement gText_AnthraTown_FootprintGuy m_LookUp
	compare 0x4001 0x1
	if equal _call PlayerWalkBack
	end

PlayerAlarmed:
	sound 0x15 @ Exclaim
	applymovement PLAYER m_LookDown
	waitmovement PLAYER
	applymovement PLAYER m_Surprise
	waitmovement PLAYER
	return

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
	npcchatwithmovement gText_AnthraTown_RivalMomAfterJourneyStarts m_LookRight
	release
	end

EventScript_AnthraTown_RivalMomBeforeProfessor:
	faceplayer
	npcchatwithmovement gText_AnthraTown_RivalMom m_LookRight
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
	compare StoryEventVar PlayerAllowedToGoOnJourney
	if equal _goto MomWishesSafeJourney
	msgbox gText_AnthraTown_MomLeaveHome MSG_KEEPOPEN
	closeonkeypress
	applymovement Mom m_LookLeft
	waitmovement 0x0
	goto End

MomWishesSafeJourney:
	npcchatwithmovement gText_AnthraTown_MomLeaveHomeAfterRunningShoes m_LookLeft
	goto End

EventScript_AnthraTown_MomRestPrompt:
	msgbox gText_AnthraTown_MomRestPrompt MSG_KEEPOPEN
	closeonkeypress
	call PlayerHeal
	incrementgamestat 16
	setvar 0x40AE 0x3 @ Fully charge the Poke Vial
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
	levelscript 0x4056 0 GameCustomizationMain
	.hword LEVEL_SCRIPT_TERMIN

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
	call SetGameInitializationFlags
	end

RememberingToday:
	msgbox gText_AnthraTown_RivalRememberingToday MSG_NORMAL
	return

NotRememberingToday:
	msgbox gText_AnthraTown_RivalNotRememberingToday MSG_NORMAL
	return

.global SignScript_AnthraTown_PlayersHouse
SignScript_AnthraTown_PlayersHouse:
	lock
	msgbox gText_AnthraTown_PlayersHouseMailbox MSG_SIGN
	end

.global SignScript_AnthraTown_RivalsHouse
SignScript_AnthraTown_RivalsHouse:
	lock
	msgbox gText_AnthraTown_RivalsHouseMailbox MSG_SIGN
	end

.global SignScript_AnthraTown_TownPlacard
SignScript_AnthraTown_TownPlacard:
	lock
	msgbox gText_AnthraTown_TownPlacardSign MSG_SIGN
	end

.global SignScript_AnthraTown_RivalsBooks
SignScript_AnthraTown_RivalsBooks:
	lock
	msgbox gText_AnthraTown_RivalsBooks MSG_SIGN
	end

.global SignScript_AnthraTown_RivalsFamilyPictures
SignScript_AnthraTown_RivalsFamilyPictures:
	lock
	msgbox gText_AnthraTown_RivalsFamilyPicture MSG_SIGN
	end

.global EventScript_AnthraTown_ChampionFanatic
EventScript_AnthraTown_ChampionFanatic:
	lock
	faceplayer
	msgbox gText_AnthraTown_ChampionFanatic_Intro MSG_YESNO
	compare LASTRESULT NO
	if equal _goto DoNotWantToKnowStats
	goto LearnGameStats
	end

DoNotWantToKnowStats:
	msgbox gText_AnthraTown_ChampionFanatic_DoNotWantToKnowStats MSG_NORMAL
	goto DoneHearingStats

DoneHearingStats:
	npcchatwithmovement gText_AnthraTown_ChampionFanatic_AfterStatsChat m_LookDown
	release
	end

LearnGameStats:
	msgbox gText_AnthraTown_ChampionFanatic_WantToKnowStats MSG_KEEPOPEN
	setvar 0x8000 0x11 @ Game stats
    setvar 0x8001 0x8 @ Show 8 at a time
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
    case 0, GameStats_TimesSaved _goto
    case 1, GameStats_StepsTaken _goto
    case 2, GameStats_PokeChipsFound _goto
    case 3, GameStats_NumberOfBattles _goto
    case 4, GameStats_TutorMovesTaught _goto
    case 5, GameStats_TimesEnteredHoF _goto
    case 6, GameStats_SaveTimeOnFirstHoF _goto
    case 7, GameStats_TimesPokedexWasChecked _goto
    case 8, GameStats_PokemonCaughtTotal _goto
    case 9, GameStats_PokemonCaughtToday _goto
    case 10, GameStats_CriticalCaptures _goto
    case 11, GameStats_PokemonEvolved _goto
    case 12, GameStats_FishCaught _goto
    case 13, GameStats_EXPEarnedToday _goto
    case 14, GameStats_NumberOfTrades _goto
    case 15, GameStats_ItemsPickedUp _goto
    case 16, GameStats_HiddenItemsFound _goto
    case 17, GameStats_TimesItemFinderWasUsed _goto
	case 18, GameStats_ApricornBallsMade _goto
	case 19, GameStats_PokeballsSwapped _goto
	case 20, GameStats_PokeChipItemsCrafted _goto
    case 21, GameStats_PokemonLeftAtDaycare _goto
    case 22, GameStats_EggsHatched _goto
    case 23, GameStats_TimesHealedAtPokemonCenterOrNurse _goto
    case 24, GameStats_TimesRestedAtHome _goto
    case 25, GameStats_TimesEnteredAHotSpring _goto
    case 26, GameStats_TimesCutWasUsed _goto
    case 27, GameStats_TimesRockSmashWasUsed _goto
	case 28, GameStats_TimesSurfWasUsed _goto
	case 29, GameStats_NumberOfMealsEaten _goto
	case 30, GameStats_NumberOfTrainerHousesBeaten _goto
	case 31, GameStats_TimesLuckyDrawWasWon _goto
	case 32, GameStats_ChangedIVsAndNature _goto
	case 33, GameStats_RareCandiesUsed _goto
	case 34, GameStats_NumberOfJackpots _goto
	case 35, GameStats_TimesShopped _goto
	case 36, GameStats_TimesSplashWasUsed _goto
	case 37, GameStats_TimesStruggleWasUsed _goto
	case 38, GameStats_TimesLedgesWereHoppedOffOf _goto
	case 39, GameStats_TimesPlayerWasRainedOn _goto
    case 40, DoneHearingStats
    case 0x7F, DoneHearingStats @ When player hits B to close
	goto DoneHearingStats
	end

	GameStats_TimesSaved:
		setvar 0x8004 0 @ Times saved
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesSaved MSG_NORMAL
		goto LearnGameStats

	GameStats_StepsTaken:
		setvar 0x8004 5 @ Steps taken
		callasm StoreStepsGameStat
		buffernumber 0x0 LASTRESULT
		buffernumber 0x1 0x4000
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_StepsTaken MSG_NORMAL
		goto LearnGameStats

	GameStats_PokeChipsFound:
		setvar 0x8004 2 @ PokeChips found
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_PokeChipsFound MSG_NORMAL
		goto LearnGameStats

	GameStats_NumberOfBattles:
		setvar 0x8004 7 @ Total battles
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		setvar 0x8004 8 @ Wild battles
		callasm StoreGameStat
		buffernumber 0x1 LASTRESULT
		setvar 0x8004 9 @ Trainer battles
		callasm StoreGameStat
		buffernumber 0x2 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfBattles MSG_NORMAL
		goto LearnGameStats

	GameStats_TutorMovesTaught:
		setvar 0x8004 3 @ Tutor moves taught
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TutorMovesTaught MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesEnteredHoF:
		setvar 0x8004 10 @ Times entered the hall of fame
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesEnteredHoF MSG_NORMAL
		goto LearnGameStats

	GameStats_SaveTimeOnFirstHoF:
		callasm StoreHoFTimeGameStat
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_SaveTimeOnFirstHoF MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesPokedexWasChecked:
		setvar 0x8004 41 @ Times pokedex was checked
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesPokedexWasChecked MSG_NORMAL
		goto LearnGameStats

	GameStats_PokemonCaughtTotal:
		setvar 0x8004 11 @ Pokemon caught (Total)
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_PokemonCaughtTotal MSG_NORMAL
		goto LearnGameStats

	GameStats_PokemonCaughtToday:
		setvar 0x8004 33 @ Pokemon caught (Today)
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_PokemonCaughtToday MSG_NORMAL
		goto LearnGameStats

	GameStats_CriticalCaptures:
		setvar 0x8004 23 @ Critical Captures
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_CriticalCaptures MSG_NORMAL
		goto LearnGameStats

	GameStats_PokemonEvolved:
		setvar 0x8004 14 @ Evolved Pokemon
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_PokemonEvolved MSG_NORMAL
		goto LearnGameStats

	GameStats_FishCaught:
		setvar 0x8004 12 @ Pokemon hooked while fishing
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_FishCaught MSG_NORMAL
		goto LearnGameStats

	GameStats_EXPEarnedToday:
		setvar 0x8004 34 @ EXP earned today
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_EXPEarnedToday MSG_NORMAL
		goto LearnGameStats

	GameStats_NumberOfTrades:
		setvar 0x8004 21 @ Pokemon trades completed
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfTrades MSG_NORMAL
		goto LearnGameStats

	GameStats_ItemsPickedUp:
		setvar 0x8004 6 @ Items picked up
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_ItemsPickedUp MSG_NORMAL
		goto LearnGameStats

	GameStats_HiddenItemsFound:
		setvar 0x8004 20 @ Hidden items found
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_HiddenItemsFound MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesItemFinderWasUsed:
		setvar 0x8004 39 @ Times the ItemFinder was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesItemFinderWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_ApricornBallsMade:
		setvar 0x8004 29 @ Number of apricorn balls made
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfApricornBallsMade MSG_NORMAL
		goto LearnGameStats

	GameStats_PokeballsSwapped:
		setvar 0x8004 31 @ Number of pokeballs swapped
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfPokeballsSwapped MSG_NORMAL
		goto LearnGameStats

	GameStats_PokeChipItemsCrafted:
		setvar 0x8004 22 @ Number of items crafted by crushing PokeChips
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfPokeChipItemsCrafted MSG_NORMAL
		goto LearnGameStats

	GameStats_PokemonLeftAtDaycare:
		setvar 0x8004 47 @ Pokemon left at the daycare
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_PokemonLeftAtDaycare MSG_NORMAL
		goto LearnGameStats

	GameStats_EggsHatched:
		setvar 0x8004 13 @ Eggs hatched
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_EggsHatched MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesHealedAtPokemonCenterOrNurse:
		setvar 0x8004 15 @ Times healed at a pokemon center or nurse
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesHealedAtPokemonCenterOrNurse MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesRestedAtHome:
		setvar 0x8004 16 @ Times rested at home
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesRestedAtHome MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesEnteredAHotSpring:
		setvar 0x8004 49 @ Times entered a hot spring
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesEnteredAHotSpring MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesCutWasUsed:
		setvar 0x8004 18 @ Times Cut was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesCutWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesRockSmashWasUsed:
		setvar 0x8004 19 @ Times Rock Smash was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesRockSmashWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesSurfWasUsed:
		setvar 0x8004 35 @ Times Surf was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesSurfWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_NumberOfMealsEaten:
		setvar 0x8004 24 @ Number of meals eaten
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfMealsEaten MSG_NORMAL
		goto LearnGameStats

	GameStats_NumberOfTrainerHousesBeaten:
		setvar 0x8004 25 @ Trainer Houses challenges completed
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfTrainerHousesBeaten MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesLuckyDrawWasWon:
		setvar 0x8004 46 @ Lucky Draw
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesLuckyDrawWasWon MSG_NORMAL
		goto LearnGameStats

	GameStats_ChangedIVsAndNature:
		setvar 0x8004 4 @ Times a Pokemon's IVs or Nature were changed
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_ChangedIVsAndNature MSG_NORMAL
		goto LearnGameStats

	GameStats_RareCandiesUsed:
		setvar 0x8004 50 @ Number of Rare Candies used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_RareCandiesUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_NumberOfJackpots:
		setvar 0x8004 28 @ Jackpots on the slots
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_NumberOfJackpots MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesShopped:
		setvar 0x8004 38 @ Times Shopped
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesShopped MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesSplashWasUsed:
		setvar 0x8004 26 @ Times splash was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesSplashWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesStruggleWasUsed:
		setvar 0x8004 27 @ Times struggle was used
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesStruggleWasUsed MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesLedgesWereHoppedOffOf:
		setvar 0x8004 43 @ Times hopped off of ledges
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesLedgesWereHoppedOffOf MSG_NORMAL
		goto LearnGameStats

	GameStats_TimesPlayerWasRainedOn:
		setvar 0x8004 40 @ Times the player was rained on
		callasm StoreGameStat
		buffernumber 0x0 LASTRESULT
		msgbox gText_AnthraTown_ChampionFanatic_GameStats_TimesPlayerWasRainedOn MSG_NORMAL
		goto LearnGameStats

m_RivalWalkUp: .byte walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, look_right, end_m
m_RivalRunOut: .byte run_left, run_down, run_left, run_left, run_left, run_left, run_down, run_down, run_down, run_down, end_m
m_RivalReturn: .byte walk_up, walk_up, look_right, end_m
m_RivalRunOutAgain: .byte run_down, run_down, run_down, end_m
m_RivalMeetPlayerAtJourneyStart: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, look_up, end_m
m_RivalReturnsToRoute17: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m

// Post-Credits Party
LevelScript_PostCreditsParty:
	showsprite 0x9 @ Mom
	showsprite 0xA @ Rival
	showsprite 0xB @ Old man
	showsprite 0xC @ Youngster
	showsprite 0xD @ Alistair
	applymovement 0xA m_RivalMeetPlayerAtJourneyStart
	waitmovement 0xA
	msgbox gText_AnthraTown_PostCredits_RivalCollectingPlayer MSG_NORMAL
	applymovement 0xA m_RivalBringsPlayerToParty
	applymovement PLAYER m_PlayerArrivesAtTheParty
	waitmovement PLAYER
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_PostCredits_RivalStartingParty MSG_NORMAL
	applymovement 0xA m_LookUp
	pause DELAY_HALFSECOND
	applymovement 0xA m_LookDown
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_PostCredits_RivalCallsForEveryoneToGather MSG_NORMAL
	applymovement 0x9 m_Surprise
	applymovement 0xB m_Surprise
	applymovement 0xC m_Surprise
	sound 0x15 @ Exclaim
	pause DELAY_1SECOND
	applymovement 0xA m_LookLeft
	applymovement 0x9 m_MomWalksToPlayer
	applymovement 0xB m_OldManWalksToPlayer
	applymovement 0xC m_YoungsterWalksToPlayer
	waitmovement ALLEVENTS
	applymovement PLAYER m_LookLeft
	playbgm 416 0x1 @ Accumula Town, permanent
	msgbox gText_AnthraTown_PostCredits_MomCongratulatesPlayer MSG_NORMAL
	applymovement PLAYER m_LookUp
	msgbox gText_AnthraTown_PostCredits_OldManCongratulatesPlayer MSG_NORMAL
	applymovement PLAYER m_LookDown
	msgbox gText_AnthraTown_PostCredits_YoungsterCongratulatesPlayer MSG_NORMAL
	applymovement PLAYER m_LookRight
	msgbox gText_AnthraTown_PostCredits_RivalCongratulatesPlayer MSG_NORMAL
	applymovement PLAYER m_Surprise
	applymovement 0xA m_Surprise
	applymovement 0x9 m_Surprise
	applymovement 0xB m_Surprise
	applymovement 0xC m_Surprise
	msgbox gText_AnthraTown_PostCredits_AlistairArrives MSG_NORMAL
	showsprite 0xD
	applymovement PLAYER m_LookDown
	applymovement 0xA m_LookDown
	applymovement 0x9 m_LookDown
	applymovement 0xB m_LookDown
	applymovement 0xC m_YoungsterMovesAside
	applymovement 0xD m_AlistairWalksUp
	waitmovement ALLEVENTS
	msgbox gText_AnthraTown_PostCredits_RivalConfirmsAlistairsArrival MSG_NORMAL
	playbgm 0x173 0x1 @ Unwavering Emotions
	msgbox gText_AnthraTown_PostCredits_AlistairAsksToBattle MSG_NORMAL
	applymovement PLAYER m_LookRight
	applymovement 0xA m_LookLeft
	msgbox gText_AnthraTown_PostCredits_RivalAsksIfPlayerWantsToBattle MSG_NORMAL
	applymovement PLAYER m_WalkDown
	applymovement 0xA m_LookDown
	msgbox gText_AnthraTown_PostCredits_RivalCommentsOnPlayerBattlingAlistair MSG_NORMAL
	setvar 0x8000 0xFEFE @ Continue lost battles
	setvar 0x40F0 276 @ Unwavering emotions overrides battle theme 
	msgbox gText_AnthraTown_PostCredits_AlistairPreBattle MSG_NORMAL
	trainerbattle9 0x0 525 0x0 gText_AnthraTown_PostCredits_AlistairWinsOrLoses gText_AnthraTown_PostCredits_AlistairWinsOrLoses
	setvar 0x40F0 0x0
	setvar 0x8000 0x0 @ Do not continue lost battles
	special 0x0 @ Heal the party
	msgbox gText_AnthraTown_PostCredits_AlistairLeaves MSG_NORMAL
	applymovement 0xD m_AlistairWalksAway
	waitmovement 0xD
	applymovement PLAYER m_WalkUp
	waitmovement PLAYER
	applymovement PLAYER m_LookRight
	applymovement 0xA m_LookLeft
	applymovement 0x9 m_LookRight
	applymovement 0xC m_LookLeft
	msgbox gText_AnthraTown_PostCredits_RivalCommentsOnAlistairBattle MSG_NORMAL
	fadescreenspeed FADEOUT_BLACK 0x64 @ Slow fade
	msgboxsign
	msgbox gText_AnthraTown_PostCredits_NextSteps MSG_NORMAL
	msgboxnormal
	hidesprite 0x9
	hidesprite 0xA
	hidesprite 0xB
	hidesprite 0xC
	hidesprite 0xD
	setflag 0x9D @ Temp disable game clear to hide champion fanatic
	hidesprite 0xE @ Champion Fanatic, hidden because we are moving the player during the fadeout
	applymovement PLAYER m_PlayerReturnsToHouse
	waitmovement PLAYER
	fadescreen FADEIN_BLACK
	addvar 0x4070 0x1
	showsprite 0xE @ Champion Fanatic
	clearflag 0x9D @ Restore game clear flag
	playbgm 0x12C 0x1 @ Default theme, permanent
	setvar 0x4073 0x1 @ Trigger Ultra Episode sequences
	end

LevelScript_PostCreditsEclipse:
	pause DELAY_HALFSECOND
	call StartEclipse
	pause DELAY_1SECOND
	call StopEclipse
	pause DELAY_HALFSECOND
	msgbox gText_AnthraTown_PostCredits_PromptToSeeProfessorSakura MSG_NORMAL
	addvar 0x4070 0x1
	end

m_RivalBringsPlayerToParty: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_left, end_m
m_PlayerArrivesAtTheParty: .byte walk_down, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, look_right, end_m
m_MomWalksToPlayer: .byte walk_left, walk_up, walk_left, walk_up, look_right, end_m
m_OldManWalksToPlayer: .byte walk_left, walk_down, walk_down, look_down, end_m
m_YoungsterWalksToPlayer: .byte walk_left, walk_left, walk_left, walk_up, end_m
m_YoungsterMovesAside: .byte walk_right, look_down, end_m
m_AlistairWalksUp: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_AlistairWalksAway: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_PlayerReturnsToHouse: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_up, look_down, end_m
