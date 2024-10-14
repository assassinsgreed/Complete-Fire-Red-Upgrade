.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Route 16
.global EventScript_Route16_SwimmerMGale
EventScript_Route16_SwimmerMGale:
    trainerbattle0 0x0 322 0x0 gText_Route16_SwimmerGale_Intro gText_Route16_SwimmerGale_Defeat
    msgbox gText_Route16_SwimmerGale_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFAmy
EventScript_Route16_SwimmerFAmy:
    trainerbattle0 0x0 323 0x0 gText_Route16_SwimmerAmy_Intro gText_Route16_SwimmerAmy_Defeat
    msgbox gText_Route16_SwimmerAmy_Chat MSG_NORMAL
    end

.global EventScript_Route16_BirdKeeperTrevor
EventScript_Route16_BirdKeeperTrevor:
    trainerbattle0 0x0 324 0x0 gText_Route16_BirdKeeperTrevor_Intro gText_Route16_BirdKeeperTrevor_Defeat
    msgbox gText_Route16_BirdKeeperTrevor_Chat MSG_NORMAL
    end

.global EventScript_Route16_LadyMaria
EventScript_Route16_LadyMaria:
    trainerbattle0 0x0 325 0x0 gText_Route16_LadyMaria_Intro gText_Route16_LadyMaria_Defeat
    msgbox gText_Route16_LadyMaria_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFChristina
EventScript_Route16_SwimmerFChristina:
    trainerbattle0 0x0 326 0x0 gText_Route16_SwimmerChristina_Intro gText_Route16_SwimmerChristina_Defeat
    msgbox gText_Route16_SwimmerChristina_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerMPhillip
EventScript_Route16_SwimmerMPhillip:
    trainerbattle0 0x0 327 0x0 gText_Route16_SwimmerPhillip_Intro gText_Route16_SwimmerPhillip_Defeat
    msgbox gText_Route16_SwimmerPhillip_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerMLester
EventScript_Route16_SwimmerMLester:
    trainerbattle0 0x0 328 0x0 gText_Route16_SwimmerLester_Intro gText_Route16_SwimmerLester_Defeat
    msgbox gText_Route16_SwimmerLester_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFWendy
EventScript_Route16_SwimmerFWendy:
    trainerbattle0 0x0 329 0x0 gText_Route16_SwimmerWendy_Intro gText_Route16_SwimmerWendy_Defeat
    msgbox gText_Route16_SwimmerWendy_Chat MSG_NORMAL
    end

.global EventScript_Route16_TuberCody
EventScript_Route16_TuberCody:
    trainerbattle0 0x0 330 0x0 gText_Route16_TuberCody_Intro gText_Route16_TuberCody_Defeat
    msgbox gText_Route16_TuberCody_Chat MSG_NORMAL
    end

.global EventScript_Route16_TuberLeslie
EventScript_Route16_TuberLeslie:
    trainerbattle0 0x0 331 0x0 gText_Route16_TuberLeslie_Intro gText_Route16_TuberLeslie_Defeat
    msgbox gText_Route16_TuberLeslie_Chat MSG_NORMAL
    end

.global EventScript_Route16_SwimmerFClementine
EventScript_Route16_SwimmerFClementine:
    trainerbattle0 0x0 332 0x0 gText_Route16_SwimmerClementine_Intro gText_Route16_SwimmerClementine_Defeat
    msgbox gText_Route16_SwimmerClementine_Chat MSG_NORMAL
    end

.global EventScript_Route16_Sharpedonite
EventScript_Route16_Sharpedonite:
    finditem ITEM_SHARPEDONITE 0x1
    end

@ Route 17
.equ Hawthorne, 0x02
.equ Selene, 0x03
.equ Rival, 0x04
.equ StoryEventVar, 0x4055
.equ PlayerMetWithRivalAtHouse, 0x2
.equ PlayerMetWithRival, 0x3
.equ PlayerAndRivalCanGoOnJourney, 0x5
.equ PlayerChoosingStarter, 0x6
.equ PlayerJourneyHasStarted, 0x7

.global MapScript_Route17
MapScript_Route17:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_Route17
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_Route17:
    compare StoryEventVar PlayerAndRivalCanGoOnJourney
    if notequal _goto End
    movesprite2 Rival 0x12 0x0A @ Facing Selene
    setobjectmovementtype Selene look_down
    setobjectmovementtype Hawthorne look_down
	end

.global SignScript_Route17_CaveSign
SignScript_Route17_CaveSign:
    msgbox gText_Route17_CaveSign MSG_SIGN
    end

.global EventScript_Route17_Rival
EventScript_Route17_Rival:
    compare StoryEventVar PlayerAndRivalCanGoOnJourney
    if greaterorequal _goto EventScript_Route17_Rival_BeforeChoosingStarter
    lock
    faceplayer
    msgbox gText_Route17_MetWithRival MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_JoinRivalBelow
    waitmovement ALLEVENTS
    goto StoryEvents_TalkingWithHawthorneAndSelene

EventScript_Route17_Rival_BeforeChoosingStarter:
    npcchatwithmovement gText_Route17_RivalExcitedToBecomeTrainer m_LookUp
    end

.global TileScript_Route17_StoryBlockersNorth
TileScript_Route17_StoryBlockersNorth:
    goto PlayerMustChooseStarter
    end

.global TileScript_Route17_StoryBlockersSouth
TileScript_Route17_StoryBlockersSouth:
    compare StoryEventVar PlayerMetWithRivalAtHouse
    if equal _goto TileEvent_MeetingRival
    compare StoryEventVar PlayerChoosingStarter
    if equal _goto PlayerMustChooseStarter
    @ Else, do nothing
    end

.global TileScript_Route17_StoryCaveBlocker
TileScript_Route17_StoryCaveBlocker:
    compare StoryEventVar PlayerJourneyHasStarted
    if equal _goto End @ Do not block the player if they have chosen a starter
    applymovement Hawthorne m_LookUp
    msgbox gText_Route17_HawthorneBlocker MSG_NORMAL
    applymovement PLAYER m_WalkDown
    compare StoryEventVar PlayerAndRivalCanGoOnJourney
    if greaterorequal _goto HawthorneLookDown
    applymovement Hawthorne m_LookRight
    end

HawthorneLookDown:
    applymovement Hawthorne m_LookDown
    end

.global EventScript_Route17_ProfessorHawthorne
EventScript_Route17_ProfessorHawthorne:
    compare StoryEventVar PlayerAndRivalCanGoOnJourney
    if equal _goto EventScript_Route17_HawthorneChooseStarter
    compare StoryEventVar PlayerChoosingStarter
    if equal _goto EventScript_Route17_PlayerChoosingStarter
    npcchatwithmovement gText_Route17_HawthorneChat m_LookRight 
    end

EventScript_Route17_HawthorneChooseStarter:
    setvar StoryEventVar PlayerChoosingStarter
    lock
    faceplayer
    msgbox gText_Route17_HawthorneDialogWhenChoosingStarter MSG_NORMAL
    compareplayerfacing INTERNAL_RIGHT
    if equal _call EventScript_Route17_PlayerMovesForHawthornePokeballs
    applymovement Hawthorne m_WalkLeft
    waitmovement ALLEVENTS
    playse 0x17 @ Ball shake sound
    pause DELAY_HALFSECOND
    clearflag 0x028
    showsprite 0x5 @ Show grass starter ball on route 17
	clearflag 0x029
    showsprite 0x6 @ Show water starter ball on route 17
	clearflag 0x02A
    showsprite 0x7 @ Show fire starter ball on route 17
    applymovement Hawthorne m_WalkRight
    waitmovement Hawthorne
    faceplayer
    playbgm 0x180 @ Let's go together!
    msgbox gText_Route17_HawthorneChooseAPokemon MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement Hawthorne m_LookRight
    msgbox gText_Route17_RivalWantsToTakeEevee MSG_NORMAL
    msgbox gText_Route17_HawthorneRespondsToRivalsEeveeChoice MSG_NORMAL
    msgbox gText_Route17_RivalWillTakeEevee MSG_NORMAL
    msgbox gText_Route17_HawthorneAcceptsRivalsEeveeChoice MSG_NORMAL
    applymovement Rival m_LookUp
    msgbox gText_Route17_SeleneAdviceOnChoosingPartner MSG_NORMAL
    goto EventScript_Route17_PlayerChoosingStarter
    release
    end

EventScript_Route17_PlayerChoosingStarter:
    lock
    faceplayer
    msgbox gText_Route17_HawthorneInvitesPlayerToChooseStarter MSG_NORMAL
    release
    end

EventScript_Route17_PlayerMovesForHawthornePokeballs:
    msgbox gText_Route17_HawthorneAsksPlayerToMove MSG_NORMAL
    applymovement PLAYER m_PlayerMoveOutOfHawthornesWay
    waitmovement PLAYER
    return

.global EventScript_Route17_ChampionSelene
EventScript_Route17_ChampionSelene:
    compare StoryEventVar PlayerAndRivalCanGoOnJourney
    if equal _goto EventScript_Route17_ChampionSelene_BeforeChoosingStarter 
    npcchatwithmovement gText_Route17_SeleneChat m_LookLeft
    end

EventScript_Route17_ChampionSelene_BeforeChoosingStarter:
    npcchatwithmovement gText_Route17_SeleneBeforeChoosingStarter m_LookDown
    end

TileEvent_MeetingRival:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    lock
    compare 0x4000 0x11
    if equal _call SetPlayerFacingLeft
    compare 0x4000 0x11
    if notequal _call SetPlayerFacingRight
    waitmovement ALLEVENTS
    msgbox gText_Route17_MetWithRival MSG_NORMAL
    applymovement PLAYER m_LookUp
    goto StoryEvents_TalkingWithHawthorneAndSelene

StoryEvents_TalkingWithHawthorneAndSelene:
    applymovement Rival m_WalkUp
    playbgm 0x17F @ The first day
    msgbox gText_Route17_RivalCallingToChampion MSG_NORMAL
    applymovement Hawthorne m_FacePlayer
    applymovement Selene m_FacePlayer
    waitmovement ALLEVENTS
    msgbox gText_Route17_ChampionResponse MSG_NORMAL
    msgbox gText_Route17_RivalStammer MSG_NORMAL
    applymovement Hawthorne m_WalkToPlayer
    waitmovement ALLEVENTS
    msgbox gText_Route17_HawthorneDismisses MSG_NORMAL
    msgbox gText_Route17_RivalProtest MSG_NORMAL
    applymovement Selene m_JoinHawthorne
    applymovement Hawthorne m_LookRight
    waitmovement ALLEVENTS
    playbgm 0x196 @ Bianca Encounter
    msgbox gText_Route17_SeleneInterjection MSG_NORMAL
    msgbox gText_Route17_HawthorneYields MSG_NORMAL
    applymovement Hawthorne m_LookDown
    applymovement Selene m_LookDown
    msgbox gText_Route17_HawthornePromptsRival MSG_NORMAL
    applymovement Rival m_Joy
    msgbox gText_Route17_RivalGratitude MSG_NORMAL
    msgbox gText_Route17_HawthorneIntroduction MSG_NORMAL
    msgbox gText_Route17_RivalStartsExplanation MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_Route17_UrgePlayerToJoin MSG_NORMAL
    compare 0x4000 0x11
    if notequal _call PlayerWalkUp_Return
    compare 0x4000 0x11
    if equal _call PlayerWalkToFaceHawthorne
    applymovement Rival m_LookUp
    msgbox gText_Route17_RivalsRequest MSG_NORMAL
    applymovement Selene m_Question
    msgbox gText_Route17_SelenesResponse MSG_NORMAL
    msgbox gText_Route17_RivalEmbarrassed MSG_NORMAL
    msgbox gText_Route17_SeleneFollowUp MSG_NORMAL
    msgbox gText_Route17_RivalTrainerInterest MSG_NORMAL
    applymovement Hawthorne m_LookRight
    applymovement Selene m_LookLeft
    waitmovement ALLEVENTS
    msgbox gText_Route17_SeleneProposesStarterPokemon MSG_NORMAL
    msgbox gText_Route17_HawthorneHesitant MSG_NORMAL
    msgbox gText_Route17_SeleneRespondsToHesitation MSG_NORMAL
    msgbox gText_Route17_HawthorneDigsIn MSG_NORMAL
    msgbox gText_Route17_SelenesProposal MSG_NORMAL
    msgbox gText_Route17_HawthorneAccepts MSG_NORMAL
    applymovement Hawthorne m_LookDown
    applymovement Selene m_LookDown
    msgbox gText_Route17_SeleneSendsPlayerOff MSG_NORMAL
    applymovement Rival m_Joy
    msgbox gText_Route17_RivalExcited MSG_NORMAL
    applymovement Rival m_RivalStartsToLeave
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookDown
    msgbox gText_Route17_RivalHeadsOut MSG_NORMAL
    applymovement Rival m_RivalLeavesToTalkToMom
    waitmovement ALLEVENTS
    hidesprite Rival
    setflag 0x02D @ Hide rival on route 17
    clearflag 0x02E @ Show rival in their house
    movesprite2 Hawthorne 0x0F 0x0A @ Update position of Hawthorne while on the route
    movesprite2 Selene 0x10 0x0A @ Update position of Selene while on the route
    setvar StoryEventVar PlayerMetWithRival
    applymovement Hawthorne m_LookRight
    applymovement Selene m_LookLeft
    fadedefaultbgm
    end

SetPlayerFacingLeft:
    applymovement PLAYER m_LookLeft
    applymovement Rival m_LookRight
    return

SetPlayerFacingRight:
    applymovement Rival m_LookLeft
    compare 0x4000 0x0E
    if equal _call PlayerWalkRight_Return
    compare 0x4000 0x0D
    if equal _call WalkRightTwice
    applymovement PLAYER m_LookRight
    return

WalkRightTwice:
    call PlayerWalkRight_Return
    call PlayerWalkRight_Return
    return

PlayerWalkToFaceHawthorne:
    applymovement PLAYER m_PlayerFaceHawthorne
    return

PlayerMustChooseStarter:
    lock
    msgbox gText_Route17_ChooseAStarterWarning MSG_NORMAL
    special 0x1AA @ Get player facing
    compareplayerfacing INTERNAL_DOWN
    if equal _goto PlayerWalkUp
    compareplayerfacing INTERNAL_UP
    if equal _goto PlayerWalkDown
    end

.global EventScript_StarterChoice_Grass
EventScript_StarterChoice_Grass:
	lock
	@ Grass starter
	compare 0x408C 0x0
	if equal _call EventScript_StarterChoice_SetBulbasaur
	compare 0x408C 0x1
	if equal _call EventScript_StarterChoice_SetChikorita
	compare 0x408C 0x2
	if equal _call EventScript_StarterChoice_SetTreecko
	compare 0x408C 0x3
	if equal _call EventScript_StarterChoice_SetTurtwig
	compare 0x408C 0x4
	if equal _call EventScript_StarterChoice_SetSnivy
	compare 0x408C 0x5
	if equal _call EventScript_StarterChoice_SetChespin
	compare 0x408C 0x6
	if equal _call EventScript_StarterChoice_SetRowlet
	compare 0x408C 0x7
	if equal _call EventScript_StarterChoice_SetGrookey

	bufferpokemon 0x0 0x4000
	showpokepic 0x4000
    applymovement Hawthorne m_LookLeft
	msgbox gText_StarterChoice_Confirmation MSG_YESNO
	hidepokepic
	compare LASTRESULT YES
	IF FALSE _call EventScript_StarterChoice_Declined
	givepokemon 0x4000 0x5 0x8B 0x0 0x0 0x0
    fanfare 0x10D
	msgbox gText_StarterChoice_Confirmed MSG_KEEPOPEN
    waitfanfare
    setvar 0x4031 0x0 @ Grass starter chosen
	setflag 0x028 @ Hide Grass Pokeball
    hidesprite 0x5 @ Hide Grass starter ball on route 17
    goto EventScript_StarterChoice_SelectionMade
	end

.global EventScript_StarterChoice_Fire
EventScript_StarterChoice_Fire:
	@ Fire starter
	compare 0x408D 0x0
	if equal _call EventScript_StarterChoice_SetCharmander
	compare 0x408D 0x1
	if equal _call EventScript_StarterChoice_SetCyndaquil
	compare 0x408D 0x2
	if equal _call EventScript_StarterChoice_SetTorchic
	compare 0x408D 0x3
	if equal _call EventScript_StarterChoice_SetChimchar
	compare 0x408D 0x4
	if equal _call EventScript_StarterChoice_SetTepig
	compare 0x408D 0x5
	if equal _call EventScript_StarterChoice_SetFennekin
	compare 0x408D 0x6
	if equal _call EventScript_StarterChoice_SetLitten
	compare 0x408D 0x7
	if equal _call EventScript_StarterChoice_SetScorbunny
	
    bufferpokemon 0x0 0x4001
	showpokepic 0x4001
    applymovement Hawthorne m_LookLeft
	msgbox gText_StarterChoice_Confirmation MSG_YESNO
	hidepokepic
	compare LASTRESULT YES
	IF FALSE _call EventScript_StarterChoice_Declined
	givepokemon 0x4001 0x5 0x8B 0x0 0x0 0x0
    fanfare 0x10D
	msgbox gText_StarterChoice_Confirmed MSG_KEEPOPEN
    waitfanfare
    setvar 0x4031 0x1 @ Fire starter chosen
	setflag 0x02A @ Hide Fire Pokeball
    hidesprite 0x6 @ Hide Fire starter ball on route 17
    goto EventScript_StarterChoice_SelectionMade
	end

.global EventScript_StarterChoice_Water
EventScript_StarterChoice_Water:
	@ Water starter
	compare 0x408E 0x0
	if equal _call EventScript_StarterChoice_SetSquirtle
	compare 0x408E 0x1
	if equal _call EventScript_StarterChoice_SetTotodile
	compare 0x408E 0x2
	if equal _call EventScript_StarterChoice_SetMudkip
	compare 0x408E 0x3
	if equal _call EventScript_StarterChoice_SetPiplup
	compare 0x408E 0x4
	if equal _call EventScript_StarterChoice_SetOshawott
	compare 0x408E 0x5
	if equal _call EventScript_StarterChoice_SetFroakie
	compare 0x408E 0x6
	if equal _call EventScript_StarterChoice_SetPopplio
	compare 0x408E 0x7
	if equal _call EventScript_StarterChoice_SetSobble
	
    bufferpokemon 0x0 0x4002
	showpokepic 0x4002
    applymovement Hawthorne m_LookLeft
	msgbox gText_StarterChoice_Confirmation MSG_YESNO
	hidepokepic
	compare LASTRESULT YES
	IF FALSE _call EventScript_StarterChoice_Declined
	givepokemon 0x4002 0x5 0x8B 0x0 0x0 0x0
    fanfare 0x10D
	msgbox gText_StarterChoice_Confirmed MSG_KEEPOPEN
    waitfanfare
    setvar 0x4031 0x2 @ Water starter chosen
	setflag 0x029 @ Hide Water Pokeball
    hidesprite 0x7 @ Hide Water starter ball on route 17
    goto EventScript_StarterChoice_SelectionMade
	end

EventScript_StarterChoice_SelectionMade:
    waitmsg
    setmonobedient 0x0 @ Starter should never disobey
	msgbox gText_StarterChoice_Nickname MSG_YESNO
	compare LASTRESULT YES
	if TRUE _call EventScript_StarterChoice_Nickname
	bufferpartypokemon 0x0 0x0
	msgbox gText_StarterChoice_Finalized MSG_NORMAL
	setflag 0x828 @ Enable Pokemon Menu
	clearflag 0x911 @ Enable wild encounters
    msgbox gText_Route17_HawthorneGettingPokeballs MSG_NORMAL
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x0F @ Above, below, or to the left of pokeballs
    if lessorequal _call MovePlayerToRejoinRival
    compare 0x4000 0x10 @ To the right of pokeballs
    if equal _call MovePlayerToRejoinRival_Right
    applymovement Hawthorne m_WalkLeft
    playse 0x17 @ Ball shake sound
    pause DELAY_HALFSECOND
    setflag 0x028
    hidesprite 0x5 @ Hide grass starter ball on route 17
	setflag 0x029
    hidesprite 0x6 @ Hide water starter ball on route 17
	setflag 0x02A
    hidesprite 0x7 @ Hide fire starter ball on route 17
    applymovement Hawthorne m_WalkRight
    waitmovement Hawthorne
    applymovement Hawthorne m_LookDown
    goto EventScript_Route17_PlayerHasChosenStarter
    end

EventScript_Route17_PlayerHasChosenStarter:
    msgbox gText_Route17_HawthornePreparingToLeave MSG_NORMAL
    applymovement Hawthorne m_LookRight
    applymovement Selene m_LookLeft
    msgbox gText_Route17_HawthorneThankingSeleneForTime MSG_NORMAL
    msgbox gText_Route17_SeleneRespondingToHawthornesThanks MSG_NORMAL
    msgbox gText_Route17_HawthorneRespondingToSelene MSG_NORMAL
    applymovement Hawthorne m_LookDown
    applymovement Selene m_LookDown
    msgbox gText_Route17_HawthorneDeparts MSG_NORMAL
    applymovement Hawthorne m_NPCLeavesRoute17
    waitmovement Hawthorne
    msgbox gText_Route17_SeleneSuggestsBattle MSG_NORMAL
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookLeft
    msgbox gText_Route17_RivalWantsToBattle MSG_NORMAL
    @ Set up environment to continue game if battle is lost
    setvar 0x8000 0xFEFE
    call SetupMugshotRival
    trainerbattle9 0x1 0x1 0x100 gText_Route17_RivalBattleConcludes gText_Route17_RivalBattleConcludes
    clearflag 0x90A @ Tutorials off (if it was never set, nothing will change)
    setvar 0x8000 0x0
    applymovement PLAYER m_LookUp
    applymovement Rival m_LookUp
    special 0x0 @ Heal player party
    msgbox gText_Route17_SeleneCommentsOnBattle MSG_NORMAL
    msgbox gText_Route17_SeleneDeparture MSG_NORMAL
    applymovement Selene m_NPCLeavesRoute17
    waitmovement Selene
    setflag 0x02B @ Hide Hawthorne, Selene, and Footprint kid in Anthra
    hidesprite Hawthorne
    hidesprite Selene
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_Route17_RivalDepartsForHawthornesLab MSG_NORMAL
    applymovement PLAYER m_LookDown
    applymovement Rival m_RivalLeavesRoute17
    waitmovement ALLEVENTS
    setflag 0x258 @ Rival beaten on Route 17
    setflag 0x02D @ Hide Rival on Route 17
    hidesprite Rival
    setvar StoryEventVar PlayerJourneyHasStarted
    setvar 0x4098 0x1 @ Turn off Anthra Tile events
    fadedefaultbgm
    release
    end

MovePlayerToRejoinRival:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x10
    if lessthan _call PlayerWalkRight_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x10
    if lessthan _call PlayerWalkRight_Return
    compare 0x4001 0x0B @ Below Pokeball
    if equal _call PlayerWalkUp_Return
    call MovePlayerToRejoinRival_Right
    return

MovePlayerToRejoinRival_Right:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x0A
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ If player still isn't in correct location, keep moving
    compare 0x4001 0x0A
    if lessthan _call PlayerWalkDown_Return
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    applymovement PLAYER m_LookUp
    return

EventScript_StarterChoice_Declined:
	msgbox gText_StarterChoice_Decline MSG_NORMAL
    applymovement Hawthorne m_LookDown
	release
	end

EventScript_StarterChoice_Nickname:
	setvar 0x8004 0x0
	fadescreen 0x1
	special 0x9E
	waitstate
	return

EventScript_StarterChoice_SetBulbasaur:
	setvar 0x4000 SPECIES_BULBASAUR
	return

EventScript_StarterChoice_SetChikorita:
	setvar 0x4000 SPECIES_CHIKORITA
	return

EventScript_StarterChoice_SetTreecko:
	setvar 0x4000 SPECIES_TREECKO
	return

EventScript_StarterChoice_SetTurtwig:
	setvar 0x4000 SPECIES_TURTWIG
	return

EventScript_StarterChoice_SetSnivy:
	setvar 0x4000 SPECIES_SNIVY
	return

EventScript_StarterChoice_SetChespin:
	setvar 0x4000 SPECIES_CHESPIN
	return

EventScript_StarterChoice_SetRowlet:
	setvar 0x4000 SPECIES_ROWLET
	return

EventScript_StarterChoice_SetGrookey:
	setvar 0x4000 SPECIES_GROOKEY
	return

EventScript_StarterChoice_SetCharmander:
	setvar 0x4001 SPECIES_CHARMANDER
	return

EventScript_StarterChoice_SetCyndaquil:
	setvar 0x4001 SPECIES_CYNDAQUIL
	return

EventScript_StarterChoice_SetTorchic:
	setvar 0x4001 SPECIES_TORCHIC
	return

EventScript_StarterChoice_SetChimchar:
	setvar 0x4001 SPECIES_CHIMCHAR
	return

EventScript_StarterChoice_SetTepig:
	setvar 0x4001 SPECIES_TEPIG
	return

EventScript_StarterChoice_SetFennekin:
	setvar 0x4001 SPECIES_FENNEKIN
	return

EventScript_StarterChoice_SetLitten:
	setvar 0x4001 SPECIES_LITTEN
	return

EventScript_StarterChoice_SetScorbunny:
	setvar 0x4001 SPECIES_SCORBUNNY
	return

EventScript_StarterChoice_SetSquirtle:
	setvar 0x4002 SPECIES_SQUIRTLE
	return

EventScript_StarterChoice_SetTotodile:
	setvar 0x4002 SPECIES_TOTODILE
	return

EventScript_StarterChoice_SetMudkip:
	setvar 0x4002 SPECIES_MUDKIP
	return

EventScript_StarterChoice_SetPiplup:
	setvar 0x4002 SPECIES_PIPLUP
	return

EventScript_StarterChoice_SetOshawott:
	setvar 0x4002 SPECIES_OSHAWOTT
	return

EventScript_StarterChoice_SetFroakie:
	setvar 0x4002 SPECIES_FROAKIE
	return

EventScript_StarterChoice_SetPopplio:
	setvar 0x4002 SPECIES_POPPLIO
	return

EventScript_StarterChoice_SetSobble:
	setvar 0x4002 SPECIES_SOBBLE
	return

.global EventScript_Route17Cave_TM80_RockSlide
EventScript_Route17Cave_TM80_RockSlide:
    setvar CHOSEN_ITEM ITEM_TM80
    call ItemScript_Common_FindTM
    end

.global SignScript_Route17Cave_DeadEndAheadSign
SignScript_Route17Cave_DeadEndAheadSign:
    msgbox gText_Route17Cave_DeadEndWarningSign MSG_SIGN
    end

m_JoinRivalBelow: .byte walk_left, walk_up, end_m
m_FacePlayer: .byte exclaim, look_down, end_m
m_WalkToPlayer: .byte walk_down, walk_left, walk_left, look_down, end_m 
m_JoinHawthorne: .byte walk_down, walk_left, walk_left, look_left, end_m
m_PlayerFaceHawthorne: .byte walk_left, walk_left, walk_up, end_m
m_RivalStartsToLeave: .byte run_down, run_down, run_left, run_left, look_right, end_m
m_RivalLeavesToTalkToMom: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
m_PlayerMoveOutOfHawthornesWay: .byte walk_down, walk_right, look_up, end_m
m_NPCLeavesRoute17: .byte walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
m_RivalLeavesRoute17: .byte walk_down, walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m

@ Route 18
.global EventScript_Route18_SwimmerJasper
EventScript_Route18_SwimmerJasper:
    trainerbattle0 0x0 314 0x0 gText_Route18_SwimmerJasper_Intro gText_Route18_SwimmerJasper_Defeat
    msgbox gText_Route18_SwimmerJasper_Chat MSG_NORMAL
    end

.global EventScript_Route18_TriathleteDeborah
EventScript_Route18_TriathleteDeborah:
    trainerbattle0 0x0 315 0x0 gText_Route18_TriathleteDeborah_Intro gText_Route18_TriathleteDeborah_Defeat
    msgbox gText_Route18_TriathleteDeborah_Chat MSG_NORMAL
    end

.global EventScript_Route18_SwimmerJudie
EventScript_Route18_SwimmerJudie:
    trainerbattle0 0x0 316 0x0 gText_Route18_SwimmerJudie_Intro gText_Route18_SwimmerJudie_Defeat
    msgbox gText_Route18_SwimmerJudie_Chat MSG_NORMAL
    end

.global EventScript_Route18_BirdKeeperKirk
EventScript_Route18_BirdKeeperKirk:
    trainerbattle0 0x0 317 0x0 gText_Route18_BirdKeeperKirk_Intro gText_Route18_BirdKeeperKirk_Defeat
    msgbox gText_Route18_BirdKeeperKirk_Chat MSG_NORMAL
    end

.global EventScript_Route18_LassEmma
EventScript_Route18_LassEmma:
    trainerbattle0 0x0 318 0x0 gText_Route18_LassEmma_Intro gText_Route18_LassEmma_Defeat
    msgbox gText_Route18_LassEmma_Chat MSG_NORMAL
    end

.global EventScript_Route18_BlackbeltRohan
EventScript_Route18_BlackbeltRohan:
    trainerbattle0 0x0 319 0x0 gText_Route18_BlackbeltRohan_Intro gText_Route18_BlackbeltRohan_Defeat
    msgbox gText_Route18_BlackbeltRohan_Chat MSG_NORMAL
    end

.global EventScript_Route18_TM31_BrickBreak
EventScript_Route18_TM31_BrickBreak:
    setvar CHOSEN_ITEM ITEM_TM31
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_TM99_DazzlingGleam
EventScript_Route18_TM99_DazzlingGleam:
    setvar CHOSEN_ITEM ITEM_TM99
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_TM92_TrickRoom
EventScript_Route18_TM92_TrickRoom:
    setvar CHOSEN_ITEM ITEM_TM92
    call ItemScript_Common_FindTM
    end

.global EventScript_Route18_Galladite
EventScript_Route18_Galladite:
    finditem ITEM_GALLADITE 0x1
    end

.global EventScript_Route18_Fisherman
EventScript_Route18_Fisherman:
    npcchatwithmovement gText_Route18_Fisherman m_LookDown
    end

.global SignScript_Route18_PreserveFlowersSign
SignScript_Route18_PreserveFlowersSign:
    msgbox gText_Route18_PreserveFlowersSign MSG_SIGN
    end

.global SignScript_Route18_OrichelleGarden
SignScript_Route18_OrichelleGarden:
    msgbox gText_Route18_OrichelleGardenSign MSG_SIGN
    end

.global EventScript_Route18_ShayminFormChangeGirl
EventScript_Route18_ShayminFormChangeGirl:
    faceplayer
    checkflag 0x25A @ Gracidea given
    if SET _goto ExplainGracideaUsage
    msgbox gText_Route18_ShayminGirl_IntroductoryText MSG_NORMAL
    setvar 0x8005 SPECIES_SHAYMIN
    callasm HasSpeciesInParty
    compare LASTRESULT TRUE
    if TRUE _goto GiveGracidea
    applymovement LASTTALKED m_LookLeft
    end

GiveGracidea:
    msgbox gText_Route18_ShayminGirl_ShayminRecognized MSG_NORMAL
    obtainitem ITEM_GRACIDEA 0x1
    setflag 0x25A @ Gracidea given
    goto ExplainGracideaUsage 

ExplainGracideaUsage:
    msgbox gText_Route18_ShayminGirl_GracideaExplanation MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_Route18_RestWoman
EventScript_Route18_RestWoman:
    faceplayer
    msgbox gText_Route18_RestWoman_RestPrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto Rest
    msgbox gText_Route18_RestWoman_RestNo MSG_NORMAL
    applymovement LASTTALKED m_LookUp
    end

Rest:
    msgbox gText_Route18_RestWoman_RestYes MSG_NORMAL
    call PlayerHeal
    msgbox gText_Route18_RestWoman_AfterRest MSG_NORMAL
    applymovement LASTTALKED m_LookUp
    end

.global EventScript_Route18_LocalLegendGirl
EventScript_Route18_LocalLegendGirl:
    npcchatwithmovement gText_Route18_LocalLegendGirl m_LookRight
    end

// Orichelle Garden
.global MapScript_OrichelleGarden
MapScript_OrichelleGarden:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_OrichelleGarden_SetWorldMapFlag
    mapscript MAP_SCRIPT_ON_RESUME HideLegendary
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_OrichelleGarden_SetWorldMapFlag:
    setworldmapflag 0x8AD @ Been to Orichelle Garden
    end

HideLegendary:
    checkflag 0x4B
    if SET _call HideShaymin
    end

HideShaymin:
    hidesprite 3
    end

.global EventScript_OrichelleGarden_Shaymin
EventScript_OrichelleGarden_Shaymin:
    faceplayer
    cry SPECIES_SHAYMIN 0x0
    waitcry
    msgbox gtext_OrichelleGarden_ShayminBattleStart MSG_NORMAL
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_DAZZLINGGLEAM
    setvar 0x8001 MOVE_SYNTHESIS
    setvar 0x8002 MOVE_SEEDBOMB
    setvar 0x8003 MOVE_EARTHPOWER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_SHAYMIN 50 ITEM_NONE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedShaymin
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call FledFromShaymin
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtShaymin
    end

DefeatedShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminDefeated MSG_NORMAL
    end

FledFromShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminFledFromBattle MSG_NORMAL
    end

CaughtShaymin:
    setflag 0x4B @ Shaymin hidden
    end

@ Route 19
.global MapScript_Route19
MapScript_Route19:
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

HideTrapPokemon:
    checkflag 0xE19
    if SET _call HidePalossand
    end

HidePalossand:
    hidesprite 10
    return

.global EventScript_Route19_LassSamantha
EventScript_Route19_LassSamantha:
    trainerbattle0 0x0 361 0x0 gText_Route19_LassSamantha_Intro gText_Route19_LassSamantha_Defeat
    msgbox gText_Route19_LassSamantha_Chat MSG_NORMAL
    end

.global EventScript_Route19_CoolTrainerRose
EventScript_Route19_CoolTrainerRose:
    trainerbattle0 0x0 362 0x0 gText_Route19_CoolTrainerRose_Intro gText_Route19_CoolTrainerRose_Defeat
    msgbox gText_Route19_CoolTrainerRose_Chat MSG_NORMAL
    end

.global EventScript_Route19_PokefanPhineas
EventScript_Route19_PokefanPhineas:
    // Double battle with Phoebe
    compare PLAYERFACING RIGHT
    if equal _call PhineasAndPhoebeLookLeft
    trainerbattle11 0x0 363 364 5 6 0x0 gText_Route19_PokefanPhineas_Intro gText_Route19_PokefanPhoebe_Intro gText_Route19_PokefanPhineas_Defeat gText_Route19_PokefanPhoebe_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route19_PokefanPhineas_Chat MSG_NORMAL
    end

.global EventScript_Route19_PokefanPhoebe
EventScript_Route19_PokefanPhoebe:
    // Double battle with Phineas
    compare PLAYERFACING LEFT
    if equal _call PhineasAndPhoebeLookRight
    trainerbattle11 0x0 363 364 5 6 0x0 gText_Route19_PokefanPhineas_Intro gText_Route19_PokefanPhoebe_Intro gText_Route19_PokefanPhineas_Defeat gText_Route19_PokefanPhoebe_Defeat gText_Common_CannotDoubleBattle_Male gText_Common_CannotDoubleBattle_Female
    msgbox gText_Route19_PokefanPhoebe_Chat MSG_NORMAL
    end

PhineasAndPhoebeLookRight:
    applymovement 5 m_LookRight
    applymovement 6 m_LookRight
    return

PhineasAndPhoebeLookLeft:
    applymovement 5 m_LookLeft
    applymovement 6 m_LookLeft
    return

.global EventScript_Route19_TM84PoisonJab
EventScript_Route19_TM84PoisonJab:
    setvar CHOSEN_ITEM ITEM_TM84
    call ItemScript_Common_FindTM
    end

.global EventScript_Route19_Palossand
EventScript_Route19_Palossand:
    lock
    checksound
    cry SPECIES_PALOSSAND 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    setflag 0xE19
    wildbattle SPECIES_PALOSSAND 50 0x0
    release
    end

.global SignScript_Route19_LookoutPointSign
SignScript_Route19_LookoutPointSign:
    msgbox gText_Route19_LookoutPoint_Sign MSG_SIGN
    end

@ Route 20
.global EventScript_Route20_Kangaskhanite
EventScript_Route20_Kangaskhanite:
    finditem ITEM_KANGASKHANITE 0x1
    end

.global EventScript_Route20_TM19Roost
EventScript_Route20_TM19Roost:
    setvar CHOSEN_ITEM ITEM_TM19
    call ItemScript_Common_FindTM
    end

.global EventScript_Route20_PsychicMcKenzie
EventScript_Route20_PsychicMcKenzie:
    trainerbattle0 0x0 375 0x0 gText_Route20_PsychicMcKenzie_Intro gText_Route20_PsychicMcKenzie_Defeat
    msgbox gText_Route20_PsychicMcKenzie_Chat MSG_NORMAL
    end

.global EventScript_Route20_PicnickerWhitney
EventScript_Route20_PicnickerWhitney:
    trainerbattle0 0x0 376 0x0 gText_Route20_PicnickerWhitney_Intro gText_Route20_PicnickerWhitney_Defeat
    msgbox gText_Route20_PicnickerWhitney_Chat MSG_NORMAL
    end

.global EventScript_Route20_TriathleteLena
EventScript_Route20_TriathleteLena:
    trainerbattle0 0x0 377 0x0 gText_Route20_TriathleteLena_Intro gText_Route20_TriathleteLena_Defeat
    msgbox gText_Route20_TriathleteLena_Chat MSG_NORMAL
    end

.global EventScript_Route20_EngineerHomer
EventScript_Route20_EngineerHomer:
    trainerbattle0 0x0 378 0x0 gText_Route20_EngineerHomer_Intro gText_Route20_EngineerHomer_Defeat
    msgbox gText_Route20_EngineerHomer_Chat MSG_NORMAL
    end

.global EventScript_Route20_CrushGirlRoxy
EventScript_Route20_CrushGirlRoxy:
    trainerbattle0 0x0 379 0x0 gText_Route20_CrushGirlRoxy_Intro gText_Route20_CrushGirlRoxy_Defeat
    msgbox gText_Route20_CrushGirlRoxy_Chat MSG_NORMAL
    end

.global EventScript_Route20_HikerRoyce
EventScript_Route20_HikerRoyce:
    trainerbattle0 0x0 380 0x0 gText_Route20_HikerRoyce_Intro gText_Route20_HikerRoyce_Defeat
    msgbox gText_Route20_HikerRoyce_Chat MSG_NORMAL
    end

.global EventScript_Route20_SuperNerdElliot
EventScript_Route20_SuperNerdElliot:
    trainerbattle0 0x0 381 0x0 gText_Route20_SuperNerdElliot_Intro gText_Route20_SuperNerdElliot_Defeat
    msgbox gText_Route20_SuperNerdElliot_Chat MSG_NORMAL
    end

.global EventScript_Route20_YoungsterDewey
EventScript_Route20_YoungsterDewey:
    trainerbattle0 0x0 382 0x0 gText_Route20_YoungsterDewey_Intro gText_Route20_YoungsterDewey_Defeat
    msgbox gText_Route20_YoungsterDewey_Chat MSG_NORMAL
    end

.global EventScript_Route20_JugglerHiram
EventScript_Route20_JugglerHiram:
    trainerbattle0 0x0 383 0x0 gText_Route20_JugglerHiram_Intro gText_Route20_JugglerHiram_Defeat
    msgbox gText_Route20_JugglerHiram_Chat MSG_NORMAL
    end

.global EventScript_Route20_NurseJessie
EventScript_Route20_NurseJessie:
    faceplayer
    checktrainerflag 384
    if SET _goto NurseJessieHeal
    trainerbattle2 0x0 384 0x0 gText_Route20_NurseJessie_Intro gText_Route20_NurseJessie_Defeat NurseJessieHeal
    call NurseJessieHeal
    end

NurseJessieHeal:
    msgbox gText_Route20_NurseJessie_Chat MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_Route20_NurseJessie_HealingComplete MSG_NORMAL
    end

.global SignScript_Route20_VictoryRoadNavigation
SignScript_Route20_VictoryRoadNavigation:
    msgbox gText_Route20_VictoryRoadNavigationSign MSG_SIGN
    end

.global SignScript_Route20_TrainerTips
SignScript_Route20_TrainerTips:
    msgbox gText_Route20_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route20_MimmettJungle
SignScript_Route20_MimmettJungle:
    msgbox gText_Route20_MimmettJungleSign MSG_SIGN
    end

.global EventScript_Route20Cave_TM69RockPolish
EventScript_Route20Cave_TM69RockPolish:
    setvar CHOSEN_ITEM ITEM_TM69
    call ItemScript_Common_FindTM
    end

@ Treasure Beach
.global MapScript_Route20_TreasureBeach
MapScript_Route20_TreasureBeach:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route20_TreasureBeach_InitializeTreasures
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_Route20_TreasureBeach_InitializeTreasures:
    checkflag 0x25E @ Treasure Beach has been initialized
    if SET _goto End
    callasm InitializeTreasureBeach
    setflag 0x25E @ Treasure Beach has been initialized
    end

.global EventScript_Route20_TreasureBeach_YoungGirl
EventScript_Route20_TreasureBeach_YoungGirl:
    npcchat Route20_TreasureBeach_YoungGirl
    end

.global EventScript_Route20_TreasureBeach_CapBoy
EventScript_Route20_TreasureBeach_CapBoy:
    npcchat Route20_TreasureBeach_CapBoy
    end

.global EventScript_Route20_TreasureBeach_GrownMan
EventScript_Route20_TreasureBeach_GrownMan:
    npcchat Route20_TreasureBeach_GrownMan
    end

.global EventScript_Route20_TreasureBeach_Beauty
EventScript_Route20_TreasureBeach_Beauty:
    npcchat Route20_TreasureBeach_Beauty
    end

.global EventScript_Route20_TreasureBeach_TM73ThunderWave
EventScript_Route20_TreasureBeach_TM73ThunderWave:
    setvar CHOSEN_ITEM ITEM_TM73
    call ItemScript_Common_FindTM
    end

.global SignScript_Route20_TreasureBeach_BeachSign
SignScript_Route20_TreasureBeach_BeachSign:
    msgbox gText_Route20_TreasureBeach_Sign MSG_SIGN
    end
