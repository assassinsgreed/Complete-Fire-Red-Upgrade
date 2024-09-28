.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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
