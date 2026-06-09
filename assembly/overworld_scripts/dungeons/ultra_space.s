.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ VarEmptyWorldStorySequence, 0x4062
.equ Rival, 0x1

.global MapScript_UltraSpace_FirstVisit
MapScript_UltraSpace_FirstVisit:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_UltraSpace_FirstVisit
    .byte MAP_SCRIPT_TERMIN

LevelScripts_UltraSpace_FirstVisit:
    levelscript VarEmptyWorldStorySequence 0x5 LevelScript_PlayerAndRivalArriveInUltraSpace
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerAndRivalArriveInUltraSpace:
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    applymovement PLAYER m_Surprise
    msgbox gText_UltraSpace_IntroCutscene_Rival_SurprisedAtArrival MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    call BufferTimeOfDay
    msgbox gText_UltraSpace_IntroCutscene_Rival_CommentsOnTimeOfDay MSG_NORMAL
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookLeft
    msgbox gText_UltraSpace_IntroCutscene_Rival_PreparingToLeave MSG_NORMAL
    applymovement Rival m_WalkLeft
    waitmovement Rival
    setvar 0x8000 Rival @ Rival follows player
    setvar 0x8001 0x80 @ Return here on white out (should never happen)
    special 0xD1 @ Set up rival follower
    setflag 0x62 @ Hide researchers in case they weren't hidden for some reason (some players experience this)
    addvar VarEmptyWorldStorySequence 0x1
    end

BufferTimeOfDay:
    setvar 0x8000 0x1 @ Merge morning, day, and evening into "Day"
    special2 LASTRESULT 0xAD @ Get time of day int
    compare LASTRESULT 0x1 @ Morning/Day/Evening
    if equal _call BufferDay
    if notequal _call BufferNight
    return

BufferDay:
    bufferstring 0x0 gText_Common_Day
    bufferstring 0x1 gText_Common_Night
    return

BufferNight:
    bufferstring 0x0 gText_Common_Night
    bufferstring 0x1 gText_Common_Day
    return

@ This is a hacky fix to show the researcher in Ultra Space
.global MapScript_UltraSpace_EclipseVillage
MapScript_UltraSpace_EclipseVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_UltraSpace_EclipseVillage_ShowReturnHomeResearcher
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_UltraSpace_EclipseVillage_ShowReturnHomeResearcher:
    checkflag 0x273 @ Completed Carnelidge Volcano story events
    if NOT_SET _goto End
    clearflag 0x62 @ Show the return home researcher
    end

.global EventScript_UltraSpace_EclipseVillage_Shopkeeper
EventScript_UltraSpace_EclipseVillage_Shopkeeper:
    npcchat gText_UltraSpace_EclipseVillage_Shopkeeper
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_Man
EventScript_UltraSpace_EclipseVillage_Man:
    npcchat gText_UltraSpace_EclipseVillage_Man
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_Lass
EventScript_UltraSpace_EclipseVillage_Lass:
    npcchat gText_UltraSpace_EclipseVillage_Lass
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global TileScript_UltraSpace_EclipseVillage_EmptyWorldCutscenes
TileScript_UltraSpace_EclipseVillage_EmptyWorldCutscenes:
    lock
    msgbox gText_UltraSpace_IntroCutscene_Rival_ApproachingVillage MSG_NORMAL
    applymovement PLAYER m_PlayerWalksIntoTown
    waitmovement PLAYER
    msgbox gText_UltraSpace_IntroCutscene_Rival_ApproachingVillage2 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_IntroCutscene_Rival_ApproachingVillage3 MSG_NORMAL
    applymovement PLAYER m_LookRight
    addvar VarEmptyWorldStorySequence 0x1
    release
    end

.global TileScript_UltraSpace_EclipseVillage_EmptyWorldTalkingToEclipseVillageNPCs
TileScript_UltraSpace_EclipseVillage_EmptyWorldTalkingToEclipseVillageNPCs:
    lock
    special 0xD3 @ Face follower
    compare 0x40A6 0x5 @ Spoke to 5 people in Eclipse Village (even the same one 5 times)
    if greaterorequal _goto RivalCommentsOnRudeness
    msgbox gText_UltraSpace_IntroCutscene_Rival_LeavingVillage MSG_NORMAL
    applymovement PLAYER m_WalkLeft
    waitmovement PLAYER
    release
    end

RivalCommentsOnRudeness:
    msgbox gText_UltraSpace_IntroCutscene_Rival_LeavingVillage2 MSG_NORMAL
    applymovement PLAYER m_LookRight
    waitmovement PLAYER
    addvar 0x40A5 0x1
    end

.global SignScript_UltraSpace_EclipseVillage_TownPlacard
SignScript_UltraSpace_EclipseVillage_TownPlacard:
    msgbox gText_UltraSpace_EclipseVillage_TownPlacard MSG_SIGN
    end

## Eclipse Village NPC Houses
.global EventScript_UltraSpace_EclipseVillage_NPCHouses1_Girl
EventScript_UltraSpace_EclipseVillage_NPCHouses1_Girl:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_NPCHouses1_Girl m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses1_Boy
EventScript_UltraSpace_EclipseVillage_NPCHouses1_Boy:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_NPCHouses1_Boy m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses1_Mom
EventScript_UltraSpace_EclipseVillage_NPCHouses1_Mom:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_NPCHouses1_Mom m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses2_Dad
EventScript_UltraSpace_EclipseVillage_NPCHouses2_Dad:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_NPCHouses2_Dad m_LookRight
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses2_Daughter
EventScript_UltraSpace_EclipseVillage_NPCHouses2_Daughter:
    npcchat gText_UltraSpace_EclipseVillage_NPCHouses2_Daughter
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses3_Girl
EventScript_UltraSpace_EclipseVillage_NPCHouses3_Girl:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_NPCHouses3_Girl m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_NPCHouses3_Boy
EventScript_UltraSpace_EclipseVillage_NPCHouses3_Boy:
    npcchat gText_UltraSpace_EclipseVillage_NPCHouses3_Boy
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_BikeShop_Shopkeeper
EventScript_UltraSpace_EclipseVillage_BikeShop_Shopkeeper:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_BikeShop_Shopkeeper m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_BikeShop_Boy
EventScript_UltraSpace_EclipseVillage_BikeShop_Boy:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_BikeShop_Boy m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_BikeShop_Man
EventScript_UltraSpace_EclipseVillage_BikeShop_Man:
    npcchatwithmovement gText_UltraSpace_EclipseVillage_BikeShop_Man m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Eclipse Village
    end

.global EventScript_UltraSpace_EclipseVillage_ReturnHomeResearcher
EventScript_UltraSpace_EclipseVillage_ReturnHomeResearcher:
    lock
    faceplayer
    msgbox gText_UltraSpace_Common_ResearcherGoHome MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PlayerChoseNotToGoHome
    msgbox gText_UltraSpace_Common_ResearcherPlayerGoingHome MSG_NORMAL
    call UltraSpaceWarpEffect
    warpmuted 9 17 1 @ In front of the ultra space wormhole machine
    end

PlayerChoseNotToGoHome:
    msgbox gText_UltraSpace_Common_ResearcherPlayerChoseToStayInUltraSpace MSG_NORMAL
    end    

.global EventScript_UltraSpace_EclipseVillage_PoipoleResearcher
EventScript_UltraSpace_EclipseVillage_PoipoleResearcher:
    lock
    faceplayer
    checkflag 0x276 @ Received Poipole
    if SET _goto PlayerReceivedPoipoleAlready
    checkflag 0x275 @ Poipole explained
    if SET _goto CheckIfPoipoleCanBeGifted
    msgbox gText_UltraSpace_PoipoleResearcher_IntroducesPoipole MSG_NORMAL
    setflag 0x275 @ Poipole explained
    goto CheckIfPoipoleCanBeGifted
    end

CheckIfPoipoleCanBeGifted:
    msgbox gText_UltraSpace_PoipoleResearcher_LeadingUpToPoipoleGift MSG_NORMAL
    special 0xD4 @ Seen in 8005, caught in 8006
    compare 0x8006 150
    if lessthan _goto NotEnoughPokemonCaughtForPoipole
    applymovement LASTTALKED m_Joy
    playse 0x19 @ Correct
    msgbox gText_UltraSpace_PoipoleResearcher_EnoughPokemon MSG_NORMAL
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto NotEnoughPartySpaceForPoipole
    setflag 0x276 @ Received Poipole
    fanfare 0x102
    msgbox gText_UltraSpace_PoipoleResearcher_PlayerReceivesPoipole MSG_KEEPOPEN
    waitfanfare
    givepokemon SPECIES_POIPOLE 60 ITEM_NONE @ Give Poipole
    msgbox gText_UltraSpace_PoipoleResearcher_PoipoleNicknameConfirmation MSG_YESNO
    compare LASTRESULT YES
    if equal _call NicknamePoipole
    msgbox gText_UltraSpace_PoipoleResearcher_PlayerAlreadyHasPoipole MSG_NORMAL
    end

NotEnoughPokemonCaughtForPoipole:
    applymovement LASTTALKED m_Wrong
    playse 0x1A @ Error
    buffernumber 0x0 0x8006
    msgbox gText_UltraSpace_PoipoleResearcher_NotEnoughPokemon MSG_NORMAL
    end

NotEnoughPartySpaceForPoipole:
    msgbox gText_UltraSpace_PoipoleResearcher_NotEnoughRoomInParty MSG_NORMAL
    end

NicknamePoipole:
    setvar 0x8003 0x0 @ Nickname from the party
    setvar 0x8005 SPECIES_POIPOLE @ Get Poipole for nicknaming (0x8004 will contain party index)
    callasm GetPokemonPartyIndex
    @ Note: No need to check var8004 <= 5, because player just received Poipole
    fadescreen 0x1
    special 0x9E @ Nickname Poipole at found index
	waitstate
    end

PlayerReceivedPoipoleAlready:
    msgbox gText_UltraSpace_PoipoleResearcher_PlayerAlreadyHasPoipole MSG_NORMAL
    end

m_PlayerWalksIntoTown: .byte walk_right, walk_right, walk_right, end_m

## Ultra Space Wilds
.equ Cosmog, 0x1
.equ UltraEpisodeCosmog, 0x2
.equ UltraEpisodeTakenCosmog, 0x3

.global MapScript_UltraSpaceWilds
MapScript_UltraSpaceWilds:
    mapscript MAP_SCRIPT_ON_LOAD MapScript_UltraSpaceWilds_SetCosmogLocation
    .byte MAP_SCRIPT_TERMIN

MapScript_UltraSpaceWilds_SetCosmogLocation:
    switch VarEmptyWorldStorySequence
    case 7, End
    case 8, MoveCosmogAfterFirstEncounter
    case 9, MoveCosmogAfterSecondEncounter
    case 10, MoveCosmogAfterThirdEncounter
    end

MoveCosmogAfterFirstEncounter:
    movesprite2 Cosmog 0x9 0x1B @ Permanent location
    setobjectmovementtype Cosmog 64 @ Walk down on the spot, facing down
    end

MoveCosmogAfterSecondEncounter:
    movesprite2 Cosmog 0x1B 0x11 @ Permanent location
    setobjectmovementtype Cosmog 64 @ Walk down on the spot, facing down
    end

MoveCosmogAfterThirdEncounter:
    movesprite2 Cosmog 0x1A 0x01 @ Permanent location
    setobjectmovementtype Cosmog 64 @ Walk down on the spot, facing down
    end

CosmogSurpriseCommon:
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Cosmog m_Surprise
    waitmovement Cosmog
    pause DELAY_HALFSECOND
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    waitcry
    return

.global TileScript_UltraSpaceWilds_CosmogEvent1
TileScript_UltraSpaceWilds_CosmogEvent1:
    lock
    release @ Lock so player stands still, then release so cosmog keeps animating
    msgbox gText_UltraSpaceWilds_CosmogChase1 MSG_NORMAL
    applymovement Cosmog m_LookLeft
    waitmovement Cosmog
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsFirstEncounter
    applymovement PLAYER m_PlayerAndRivalChaseCosmogFirstEncounter
    waitmovement Cosmog
    msgbox gText_UltraSpaceWilds_CosmogChase2 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpaceWilds_CosmogChase3 MSG_YESNO
    compare LASTRESULT YES
    if equal _call CosmogLooksLikePokemon
    if notequal _call CosmogDoesNotLookLikePokemon
    msgbox gText_UltraSpaceWilds_CosmogChase5 MSG_NORMAL
    addvar VarEmptyWorldStorySequence 0x1
    applymovement PLAYER m_LookUp
    movesprite Cosmog 0x9 0x1B @ While on map
    goto MoveCosmogAfterFirstEncounter @ Permanent location, if player runs through map and returns here

CosmogLooksLikePokemon:
    msgbox gText_UltraSpaceWilds_CosmogChase4_Yes MSG_NORMAL
    return

CosmogDoesNotLookLikePokemon:
    msgbox gText_UltraSpaceWilds_CosmogChase4_No MSG_NORMAL
    return

.global TileScript_UltraSpaceWilds_CosmogEvent2
TileScript_UltraSpaceWilds_CosmogEvent2:
    lock
    release @ Lock so player stands still, then release so cosmog keeps animating
    msgbox gText_UltraSpaceWilds_CosmogChase6 MSG_NORMAL
    applymovement Cosmog m_LookUp
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsSecondEncounterJump
    pause 5
    playse 0xA @ Ledge hop
    waitmovement Cosmog
    applymovement Cosmog m_CosmogRunsSecondEncounter
    waitmovement Cosmog
    msgbox gText_UltraSpaceWilds_CosmogChase7 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpaceWilds_CosmogChase8 MSG_NORMAL
    applymovement PLAYER m_LookRight
    addvar VarEmptyWorldStorySequence 0x1
    movesprite Cosmog 0x1B 0x11 @ While on map
    goto MoveCosmogAfterSecondEncounter @ Set permanent location, due to being outside of loaded memory

.global TileScript_UltraSpaceWilds_CosmogEvent3
TileScript_UltraSpaceWilds_CosmogEvent3:
    lock
    release @ Lock so player stands still, then release so cosmog keeps animating
    msgbox gText_UltraSpaceWilds_CosmogChase9 MSG_NORMAL
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsThirdEncounterJump
    pause 10
    playse 0xA @ Ledge hop
    waitmovement Cosmog
    applymovement Cosmog m_CosmogRunsThirdEncounter
    applymovement PLAYER m_LookRight
    waitmovement Cosmog
    msgbox gText_UltraSpaceWilds_CosmogChase10 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpaceWilds_CosmogChase11 MSG_NORMAL
    applymovement PLAYER m_LookUp
    addvar VarEmptyWorldStorySequence 0x1
    movesprite Cosmog 0x1A 0x1 @ While on map
    goto MoveCosmogAfterThirdEncounter @ Set permanent location, due to being outside of loaded memory

.global TileScript_UltraSpaceWilds_CosmogEvent4
TileScript_UltraSpaceWilds_CosmogEvent4:
    lock
    release @ Lock so player stands still, then release so cosmog keeps animating
    msgbox gText_UltraSpaceWilds_CosmogChase12 MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0x18
    if equal _call CosmogEvent4_PlayerOnLeft
    if greaterthan _call CosmogEvent4_PlayerOnRight
    applymovement Cosmog m_CosmogRunsFourthEncounterDown
    waitmovement Cosmog
    msgbox gText_UltraSpaceWilds_CosmogChase13 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpaceWilds_CosmogChase14 MSG_NORMAL
    addvar VarEmptyWorldStorySequence 0x1
    setflag 0x272 @ Hide Cosmog when reloading map
    hidesprite Cosmog @ Hide Cosmog while on map
    end

CosmogEvent4_PlayerOnLeft:
    applymovement Cosmog m_LookLeft
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsFourthEncounterRight
    waitmovement Cosmog
    return

CosmogEvent4_PlayerOnRight:
    applymovement Cosmog m_LookRight
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsFourthEncounterLeft
    waitmovement Cosmog
    return

.global TileScript_UltraSpaceWilds_CosmogEventIncomplete
TileScript_UltraSpaceWilds_CosmogEventIncomplete:
    compare VarEmptyWorldStorySequence 0xB
    if greaterorequal _goto End
    lock
    special 0xD3 @ Face follower
    msgbox gText_UltraSpaceWilds_CosmogChaseIncomplete MSG_NORMAL
    applymovement PLAYER m_WalkLeft
    waitmovement PLAYER
    end

.global SignScript_UltraSpaceWilds_BridgeSign
SignScript_UltraSpaceWilds_BridgeSign:
    msgbox gText_UltraSpaceWilds_BridgeSign MSG_SIGN
    end

.global MapScript_UltraSpaceWilds_AltarOfEclipse
MapScript_UltraSpaceWilds_AltarOfEclipse:
    mapscript MAP_SCRIPT_ON_LOAD HandleUltraEpisodeCosmogVisibility
    mapscript MAP_SCRIPT_ON_RESUME HideLegendary
    .byte MAP_SCRIPT_TERMIN

HandleUltraEpisodeCosmogVisibility:
    compare 0x4073 0x3 @ Ultra Episode initial cutscene concluded
    if notequal _goto End
    movesprite2 UltraEpisodeCosmog 0x9 0xC @ Permanent location
    end

HideLegendary:
    setvar LASTRESULT SPECIES_COSMOG
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if equal _goto HideCosmog
    end

HideCosmog:
    hidesprite UltraEpisodeCosmog
    end

.global SignScript_UltraSpaceWilds_AltarOfEclipseSign
SignScript_UltraSpaceWilds_AltarOfEclipseSign:
    msgbox gText_UltraSpaceWilds_AltarOfEclipseSign MSG_SIGN
    end

.global TileScript_UltraSpaceWilds_AltarOfEclipse_CosmogEvent
TileScript_UltraSpaceWilds_AltarOfEclipse_CosmogEvent:
    lock
    release @ Lock so player stands still, then release so cosmog keeps animating
    msgbox gText_UltraSpace_AltarOfEclipse_FirstVisit_RivalSeesCosmog MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_AltarOfEclipse_FirstVisit_RivalFeelsBadAboutHarassingCosmog MSG_NORMAL
    applymovement PLAYER m_WalkUp
    applymovement Cosmog m_LookDown
    call CosmogSurpriseCommon
    applymovement Cosmog m_CosmogRunsAtAltarOfEclipse
    pause 0x5 @ Pause quarter second
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA @ Right tile event
    if equal _call PlayerRunLeft
    applymovement PLAYER m_PlayerRunsAtAltarOfEclipse
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    msgbox gText_UltraSpace_AltarOfEclipse_FirstVisit_CosmogCornered MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Cosmog m_CosmogBigSurprise
    waitmovement Cosmog
    pause DELAY_HALFSECOND
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    waitcry
    msgbox gText_UltraSpace_AltarOfEclipse_FirstVisit_RivalBeforeWarp MSG_NORMAL
    sound 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement PLAYER m_HideSprite
    special 0xD2 @ Destroy follower
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    setflag 0x70 @ Hide Cosmog here when revisiting
    addvar VarEmptyWorldStorySequence 0x1
    pause DELAY_HALFSECOND
    applymovement Cosmog m_Joy
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    pause DELAY_HALFSECOND
    warpmuted 2 39 0xFF 0x13 0x1D @ Warp to Hoenn's Mirage Island in an alternate dimension
    end

PlayerRunLeft:
    applymovement PLAYER m_RunLeft
    waitmovement PLAYER
    return

.global TileScript_UltraSpaceWilds_AltarOfEclipse_UltraEpisodeIntroduction
TileScript_UltraSpaceWilds_AltarOfEclipse_UltraEpisodeIntroduction:
    lock
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA
    if equal _call PlayerRunLeft
    applymovement PLAYER m_LookUp
    applymovement UltraEpisodeCosmog m_Surprise
    applymovement UltraEpisodeTakenCosmog m_Surprise
    playse 0x15 @ Exclaim
    waitse
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_CosmogSighted MSG_NORMAL
    applymovement PLAYER m_WalkUp
    pause DELAY_HALFSECOND
    applymovement UltraEpisodeCosmog m_UltraEpisodeCosmogRunsAtAltarOfEclipse
    applymovement UltraEpisodeTakenCosmog m_UltraEpisodeTakenCosmogRunsAtAltarOfEclipse
    pause 0x5 @ Pause quarter second
    @ Note: The player MUST finish animating after the Cosmogs or else the releaseall hack below will not animate them
    applymovement PLAYER m_UltraEpisodePlayerChasesCosmogs
    waitmovement ALLEVENTS
    releaseall @ Hackaround - releaseall to reanimate cosmogs, but keep player locked with messagebox
    pause DELAY_HALFSECOND
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_CosmogPreparingToCatch MSG_NORMAL
    applymovement PLAYER m_WalkUp
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    playse 0x23 @ Ice shatter
    waitmovement PLAYER
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    showsprite 4 @ Show wormhole
    fadescreenspeed FADEIN_WHITE 0x80 @ Slower fade
    pause 0x5 @ Pause quarter second
    playbgm 0x181 @ Necrozma appearance
    applymovement PLAYER m_Surprise
    applymovement UltraEpisodeCosmog m_Surprise
    applymovement UltraEpisodeTakenCosmog m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_UltraWormholeOpened MSG_NORMAL
    cry SPECIES_NECROZMA 0x0
    setflag 0x150
    pause DELAY_HALFSECOND
    setvar 0x40AF 1
    pause DELAY_HALFSECOND
    setvar 0x40AF 2
    pause DELAY_HALFSECOND
    setvar 0x40AF 3
    pause DELAY_HALFSECOND
    setvar 0x40AF 4
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_EclipseStarted MSG_NORMAL
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    applymovement UltraEpisodeCosmog m_UltraEpisodeCosmogPanic
    playse 0x52 @ Elevator
    applymovement UltraEpisodeTakenCosmog m_UltraEpisodeTakenCosmogFloatUp
    waitmovement ALLEVENTS
    pause DELAY_HALFSECOND
    waitse
    hidesprite UltraEpisodeTakenCosmog
    setflag 0x74 @ Hide Taken Cosmog
    applymovement UltraEpisodeCosmog m_Surprise
    playse 0x15 @ Exclaim
    waitse
    pause DELAY_HALFSECOND
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    playse 0x23 @ Ice shatter
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    hidesprite 4 @ Hide wormhole
    fadescreenspeed FADEIN_WHITE 0x80 @ Slower fade
    pause DELAY_HALFSECOND
    setvar 0x40AF 3
    pause DELAY_HALFSECOND
    setvar 0x40AF 2
    pause DELAY_HALFSECOND
    setvar 0x40AF 1
    pause DELAY_HALFSECOND
    setvar 0x40AF 0
    clearflag 0x150
    cry SPECIES_COSMOG 0x3 @ Lower pitch, fainted sound
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_UltraWormholeCosmogCry MSG_NORMAL
    applymovement UltraEpisodeCosmog m_LookDown
    fadedefaultbgm
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_UltraWormholeClosed MSG_NORMAL
    movesprite2 UltraEpisodeCosmog 0x9 0xC @ Permanent location
    setvar 0x4073 0x3 @ Tile event concluded
    end

.global EventScript_UltraSpaceWilds_Cosmog
EventScript_UltraSpaceWilds_Cosmog:
    lock
    faceplayer
    applymovement Cosmog m_Surprise
    playse 0x15 @ Exclaim
    pause DELAY_HALFSECOND
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    waitcry
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_CosmogFight MSG_NORMAL
    setvar 0x4073 0x4 @ Cosmog challenged
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_SPLASH
    setvar 0x8001 MOVE_NONE
    setvar 0x8002 MOVE_NONE
    setvar 0x8003 MOVE_NONE
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_COSMOG 70 ITEM_NONE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _goto DefeatedOrFledFromCosmog
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _goto DefeatedOrFledFromCosmog
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtCosmog
    end

DefeatedOrFledFromCosmog:
    cry SPECIES_COSMOG 0x0
    msgbox gText_UltraSpaceWilds_CosmogPew MSG_NORMAL
    waitcry
    pause DELAY_HALFSECOND
    playse 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement LASTTALKED m_HideSprite
    hidesprite LASTTALKED
    setflag 0x06E @ Cosmog hidden
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_CosmogDefeatedOrFled MSG_NORMAL
    end

CaughtCosmog:
    @ Cosmog hidden in map resume script
    msgbox gText_UltraSpaceWilds_AltarOfEclipse_CosmogCaught MSG_NORMAL
    return

m_CosmogRunsFirstEncounter: .byte run_up, run_up, run_up, run_up, run_up, run_up, walk_down_onspot, end_m
m_PlayerAndRivalChaseCosmogFirstEncounter: .byte run_right, run_right, run_right, run_right, run_right, end_m
m_CosmogRunsSecondEncounterJump: .byte jump_2_down, end_m
m_CosmogRunsSecondEncounter: .byte run_down, run_right, run_right, run_right, run_right, run_right, run_right, run_right, walk_down_onspot, end_m
m_CosmogRunsThirdEncounterJump: .byte run_right, jump_2_right, end_m
m_CosmogRunsThirdEncounter: .byte run_right, run_right, run_right, run_right, run_right, run_right, run_right, walk_down_onspot, end_m
m_CosmogRunsFourthEncounterRight: .byte run_right, run_right, run_right, run_right, end_m
m_CosmogRunsFourthEncounterLeft: .byte run_left, run_left, run_left, run_left, end_m
m_CosmogRunsFourthEncounterDown: .byte run_down, run_down, run_down, run_down, run_down, run_down, end_m
m_CosmogRunsAtAltarOfEclipse: .byte run_up, run_up, run_left, run_up, run_up, run_up, run_up, run_up, run_right, run_right, walk_down_onspot, end_m
m_PlayerRunsAtAltarOfEclipse: .byte run_up, run_up, run_left, run_up, run_up, run_up, run_up, run_right, run_up, run_right, look_up, end_m
m_UltraEpisodeCosmogRunsAtAltarOfEclipse: .byte run_up, run_up, run_left, run_up, run_up, run_up, run_up, run_up, run_right, look_down, end_m
m_UltraEpisodeTakenCosmogRunsAtAltarOfEclipse: .byte run_up, run_up, run_right, run_up, run_up, run_up, run_up, run_up, run_left, look_down, end_m
m_UltraEpisodePlayerChasesCosmogs: .byte walk_up, run_up, run_left, run_up, run_up, run_up, run_up, run_right, look_up, end_m
m_UltraEpisodeCosmogPanic: .byte look_right, jump_onspot_right, jump_onspot_right, pause_long, jump_onspot_right, jump_onspot_right, pause_long, jump_onspot_right, jump_onspot_right, pause_long, jump_onspot_right, jump_onspot_right, pause_long, jump_onspot_right, jump_onspot_right, pause_long, end_m
m_UltraEpisodeTakenCosmogFloatUp: .byte walk_down_slow, pause_long, walk_down_very_slow, pause_long, pause_long, pause_long, pause_long, pause_long, lock_facing, walk_up_very_slow, walk_up_very_slow, walk_up_very_slow, end_m
m_CosmogBigSurprise: .byte say_double_exclaim, end_m

## Ultra Space Hoenn
.equ Wingull1, 0x2
.equ Wingull2, 0x3
.equ Wingull3, 0x4
.equ JirachiDormant, 12
.equ JirachiAwakened, 13

.global MapScript_UltraSpaceHoenn
MapScript_UltraSpaceHoenn:
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_UltraSpace_Hoenn
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_UltraSpace_Hoenn_PlayerFacing
    .byte MAP_SCRIPT_TERMIN

LevelScripts_UltraSpace_Hoenn:
    levelscript VarEmptyWorldStorySequence 0xC LevelScript_PlayerAndRivalArriveInHoenn
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerAndRivalArriveInHoenn:
    pause DELAY_HALFSECOND
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene1 MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookLeft
    pause DELAY_HALFSECOND
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookRight
    pause DELAY_HALFSECOND
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene2 MSG_NORMAL
    applymovement Rival m_PlayerAndRivalApproachWingulls
    applymovement PLAYER m_PlayerAndRivalApproachWingulls
    waitmovement PLAYER
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    applymovement PLAYER m_Surprise
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene3 MSG_NORMAL
    applymovement Wingull1 m_LookDown
    applymovement Wingull2 m_LookDown
    applymovement Wingull3 m_LookDown
    cry SPECIES_WINGULL 0x0
    msgbox gText_UltraSpace_Hoenn_Wingulls MSG_NORMAL
    applymovement Wingull1 m_WingullFlyAway
    applymovement Wingull2 m_WingullFlyAway
    applymovement Wingull3 m_WingullFlyAway
    applymovement Rival m_RivalRunToWingulls
    applymovement PLAYER m_WalkUp
    waitmovement Wingull3
    hidesprite Wingull1
    hidesprite Wingull2
    hidesprite Wingull3
    setflag 0x71 @ Hide Wingulls, in case the player walks away and come back
    pause DELAY_1SECOND
    applymovement Rival m_LookDown
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene4 MSG_NORMAL
    applymovement Rival m_LookUp
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene5 MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_UltraSpace_Hoenn_ArrivalCutscene6 MSG_NORMAL
    applymovement Rival m_RivalReturnsToPlayer
    waitmovement Rival
    setvar 0x8000 Rival @ Rival follows player
    setvar 0x8001 0x80 @ Return here on white out (should never happen)
    special 0xD1 @ Set up rival follower
    addvar VarEmptyWorldStorySequence 0x1
    end

LevelScripts_UltraSpace_Hoenn_PlayerFacing:
    levelscript VarEmptyWorldStorySequence 0xC LevelScript_UltraSpace_Hoenn_SetPlayerFacing
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_UltraSpace_Hoenn_SetPlayerFacing:
    applymovement PLAYER m_LookUp
    end

.global EventScript_UltraSpaceHoenn_Wingull1
EventScript_UltraSpaceHoenn_Wingull1:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0x8
    end

.global EventScript_UltraSpaceHoenn_Wingull2
EventScript_UltraSpaceHoenn_Wingull2:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0x9
    end

.global EventScript_UltraSpaceHoenn_Wingull3
EventScript_UltraSpaceHoenn_Wingull3:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0xA
    end

.global EventScript_UltraSpaceHoenn_Wingull4
EventScript_UltraSpaceHoenn_Wingull4:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0xB
    end

.global EventScript_UltraSpaceHoenn_Wingull5
EventScript_UltraSpaceHoenn_Wingull5:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0xC
    end

.global EventScript_UltraSpaceHoenn_Wingull6
EventScript_UltraSpaceHoenn_Wingull6:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0xD
    end

.global EventScript_UltraSpaceHoenn_Wingull7
EventScript_UltraSpaceHoenn_Wingull7:
    call WingullCommon
    hidesprite LASTTALKED
    setflag 0xE
    end

WingullCommon:
    lock
    faceplayer
    cry SPECIES_WINGULL 0x0
    msgbox gText_UltraSpace_Hoenn_Wingulls MSG_NORMAL
    applymovement LASTTALKED m_WingullFlyAway
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookRight
    waitmovement LASTTALKED
    return

.global EventScript_UltraSpaceHoenn_Jirachi
EventScript_UltraSpaceHoenn_Jirachi:
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_Hoenn_FindingJirachi1 MSG_NORMAL
    call HandlePlayerPositioningAtJirachi
    msgbox gText_UltraSpace_Hoenn_FindingJirachi2 MSG_NORMAL
    applymovement Rival m_Surprise
    sound 0x15 @ Exclaim
    msgbox gText_UltraSpace_Hoenn_FindingJirachi3 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_Hoenn_FindingJirachi4 MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_UltraSpace_Hoenn_FindingJirachi5 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_Hoenn_FindingJirachi6 MSG_YESNO
    compare LASTRESULT NO
    if equal _call PlayerDoesNotWantToWish
    msgbox gText_UltraSpace_Hoenn_FindingJirachi7_Yes MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Rival m_LookUp
    msgbox gText_UltraSpace_Hoenn_FindingJirachi8 MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_UltraSpace_Hoenn_FindingJirachiWishes MSG_NORMAL
    fadescreen FADEIN_BLACK
    msgbox gText_UltraSpace_Hoenn_FindingJirachi9 MSG_NORMAL
    playse 0x5F @ Shiny
	dofieldeffect 69 @ Screen flash
    hidesprite JirachiDormant
    showsprite JirachiAwakened
    waitfieldeffect 69
    waitse
    cry SPECIES_JIRACHI 0x0
    msgbox gText_UltraSpace_Hoenn_FindingJirachi10 MSG_KEEPOPEN
    waitcry
    applymovement Rival m_Surprise
    applymovement PLAYER m_Surprise
    sound 0x15 @ Exclaim
    msgbox gText_UltraSpace_Hoenn_FindingJirachi11 MSG_NORMAL
    special 0xD3 @ Face follower
    msgbox gText_UltraSpace_Hoenn_FindingJirachi12 MSG_NORMAL
    fadescreen FADEOUT_WHITE
    cry SPECIES_JIRACHI 0x0
    waitcry
    pause DELAY_HALFSECOND
    addvar VarEmptyWorldStorySequence 0x1
    special 0xD2 @ Destroy follower
    clearflag 0x270 @ Jirachi is dormant again in the home dimension
    setflag 0x05A @ Animated Jirachi is hidden
    warpmuted 1 58 0xFF 0xB 0x9 @ Warp to Carnelidge Volcano in the home dimension
    end

HandlePlayerPositioningAtJirachi:
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x7 @ Above
    if equal _call PlayerWalkToJirachiFromAbove
    compare 0x4000 0x1D @ Centered with Jirach
    if lessthan _call PlayerWalkToJirachiFromLeft
    if greaterthan _call PlayerWalkToJirachiFromRight
    applymovement PLAYER m_LookUp
    applymovement Rival m_LookUp
    return

PlayerWalkToJirachiFromAbove:
    applymovement PLAYER m_PlayerWalksToJirachiFromAbove
    waitmovement PLAYER
    return

PlayerWalkToJirachiFromLeft:
    applymovement PLAYER m_PlayerWalksToJirachiFromLeft
    waitmovement PLAYER
    return

PlayerWalkToJirachiFromRight:
    applymovement PLAYER m_PlayerWalksToJirachiFromRight
    waitmovement PLAYER
    return

PlayerDoesNotWantToWish:
    msgbox gText_UltraSpace_Hoenn_FindingJirachi7_No MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PlayerDoesNotWantToWish
    return

m_WingullFlyAway: .byte run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, run_right, end_m
m_PlayerAndRivalApproachWingulls: .byte walk_up, walk_up, walk_up, end_m
m_RivalRunToWingulls: .byte run_up, run_up, run_up, look_right, end_m
m_RivalReturnsToPlayer: .byte walk_down, walk_down, walk_right, look_up, end_m
m_PlayerWalksToJirachiFromAbove: .byte walk_left, walk_down, walk_down, walk_right, look_up, end_m
m_PlayerWalksToJirachiFromLeft: .byte walk_down, walk_right, look_up, end_m
m_PlayerWalksToJirachiFromRight: .byte walk_down, walk_left, look_up, end_m

////////////////
// Dias of Light
////////////////
.equ Sakura, 0x2

.global MapScript_UltraSpace_DiasOfLight
MapScript_UltraSpace_DiasOfLight:
    mapscript MAP_SCRIPT_ON_LOAD MapScript_UltraSpace_DiasOfLight_SetNecrozmaVisibilityAndForm
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_UltraSpace_DiasOfLight
    mapscript MAP_SCRIPT_ON_RESUME MapResumeScript_HideNecrozma
    .byte MAP_SCRIPT_TERMIN

MapScript_UltraSpace_DiasOfLight_SetNecrozmaVisibilityAndForm:
    checkflag 0x28B @ Eclipses active
    if SET _call TriggerEclipseOnLoad
    checkflag 0x06F @ Necrozma caught
    if SET _goto End
    call HandleNecrozmaForm
    end

@ Should only happen if the player loses to the first Necrozma form
TriggerEclipseOnLoad:
    setflag 0x150
    setvar 0x40AF 4
    return

HandleNecrozmaForm:
    setvar LASTRESULT SPECIES_SOLGALEO
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if TRUE _call ShowDawnWingsNecrozma @ Solgaleo caught, need to show Lunala
    if FALSE _call ShowDuskManeNecrozma
    return

ShowDuskManeNecrozma:
    setvar 0x5029 141 @ Dusk Mane Necrozma (Solgaleo)
    return

ShowDawnWingsNecrozma:
    setvar 0x5029 142 @ Dawn Wings Necrozma (Lunala)
    return

HandleNecrozmaCry:
    setvar LASTRESULT SPECIES_SOLGALEO
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if TRUE _call DawnWingsCry
    if FALSE _call DuskManeCry
    return

DuskManeCry:
    cry SPECIES_NECROZMA_DUSK_MANE 0x0
    msgbox gText_DiasOfLight_DuskManeNecrozmaCry MSG_NORMAL
    waitcry
    return

DawnWingsCry:
    cry SPECIES_NECROZMA_DAWN_WINGS 0x0
    msgbox gText_DiasOfLight_DawnWingsNecrozmaCry MSG_NORMAL
    waitcry
    return

LevelScripts_UltraSpace_DiasOfLight:
    levelscript 0x4073 0x7 LevelScript_UltraSpace_DiasOfLight_FirstArrival
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_UltraSpace_DiasOfLight_FirstArrival:
    pause DELAY_HALFSECOND
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DiasOfLight_ArrivedAtDiasOfLight MSG_NORMAL
    applymovement Sakura m_WalkUp
    applymovement PLAYER m_LookUp
    msgbox gText_DiasOfLight_SakuraCommentsOnDiasOfLight MSG_NORMAL
    call HandleNecrozmaCry
    applymovement PLAYER m_Surprise
    applymovement Sakura m_Surprise
    playse 0x15 @ Exclaim
    call PlayEclipseAnimation
    setflag 0x28B @ Eclipses active here (in the event of failure)
    pause DELAY_HALFSECOND
    applymovement Sakura m_WalkDown
    waitmovement Sakura
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DiasOfLight_SakuraCommentsOnEclipse MSG_NORMAL
    applymovement Sakura m_SakuraWalksToFirstStoppingPoint
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    waitmovement Sakura
    movesprite Sakura 0xE 0x1D @ Beside first stairs
    movesprite2 Sakura 0xE 0x1D @ Beside first stairs
    addvar 0x4073 0x1 @ Now at 8
    end

MapResumeScript_HideNecrozma:
    checkflag 0x6F @ Necrozma caught
    if NOT_SET _goto End
    hidesprite 1
    end

.global EventScript_UltraSpace_DiasOfLight_Necrozma
EventScript_UltraSpace_DiasOfLight_Necrozma:
    lock
    faceplayer
    call HandleNecrozmaCry
    checkflag 0x289 @ Ultra Necrozma Defeated
    if SET _goto ChallengeCatchableNecrozma
    setflag 0x28B @ Eclipses active here (in the event of failure)
    msgbox gText_DiasOfLight_ApproachingNecrozma MSG_NORMAL
    callasm CheckBeastKillerInFirstSlot
    compare LASTRESULT 1
    if lessthan _goto NeedBeastKillerInFirstSlot
    setflag 0x904 @ Cannot catch or run from battle; cleared after battle
    setvar LASTRESULT SPECIES_SOLGALEO @ Setup fight based on which Cosmog form the player has
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if TRUE _call TriggerDawnWingsNecrozmaFight
    if FALSE _call TriggerDuskManeNecrozmaFight
    msgbox gText_DiasOfLight_NecrozmaDefeatedFakeOut MSG_NORMAL
    sound 0x51 @ Thunder2
    call HandleNecrozmaCry
    fadescreen FADEOUT_BLACK
    hidesprite LASTTALKED
    setvar 0x5029 143 @ Ultra Necrozma
    showsprite LASTTALKED
    clearflag 0x6F @ Show fused Necrozma again if the player loses (gets set by hide/show sprite commands)
    faceplayer @ Reappears facing down when sprite changes
    playbgm 0x181 @ Necrozma appearance
    fadescreenspeed FADEIN_WHITE 0x80 @ faster fade
    setvar 0x40AF 0 @ Instantly stop eclipse
    clearflag 0x150
    cry SPECIES_NECROZMA_ULTRA 0x0
    msgbox gText_DiasOfLight_UltraNecrozmaCry MSG_NORMAL
    waitcry
    applymovement PLAYER m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_DiasOfLight_NecrozmaTransformed MSG_NORMAL
    checkflag 0x28A @ Evolved Type Null
    if NOT_SET _call TriggerTypeNullEvolution
    special 0x0 @ Heal party
    msgbox gText_DiasOfLight_SilvallyCourage MSG_NORMAL
    setflag 0x904 @ Cannot catch or run from battle; cleared after battle
    call TriggerUltraNecrozmaFight
    clearflag 0x28B @ No eclipses active here (in the event of future failure)
    pause 0x10 @ Quarter second
    cry SPECIES_NECROZMA_ULTRA 0x3
    msgbox gText_DiasOfLight_UltraNecrozmaCry_Defeated MSG_NORMAL
    waitcry
    fadescreenspeed FADEOUT_WHITE 0x80 @ Faster fade
    hidesprite LASTTALKED
    call HandleNecrozmaForm
    showsprite LASTTALKED
    clearflag 0x6F @ Show fused Necrozma again if the player loses (gets set by hide/show sprite commands)
    faceplayer @ Reappears facing down when sprite changes
    fadescreen FADEIN_WHITE
    msgbox gText_DiasOfLight_UltraNecrozmaStopped MSG_NORMAL
    signmsg
    msgbox gText_DiasOfLight_UltraNecrozmaCatchablePrompt MSG_SIGN
    normalmsg
    setflag 0x289 @ Ultra Necrozma Defeated
    addvar 0x4073 0x1 @ Now at 11
    setflag 0xBE @ Instant friendship game modifier unlocked
    end

NeedBeastKillerInFirstSlot:
    checkflag 0x28A @ Evolved Type Null
    bufferstring 0x0 gText_Common_TypeNull
    if SET _call BufferSilvallyName
    npcchatwithmovement gText_DiasOfLight_TypeNullNotAtFrontOfParty m_LookDown
    end

BufferSilvallyName:
    bufferstring 0x0 gText_Common_Silvally
    return

TriggerDuskManeNecrozmaFight:
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_SUNSTEELSTRIKE
    setvar 0x8001 MOVE_MORNINGSUN
    setvar 0x8002 MOVE_POWERGEM
    setvar 0x8003 MOVE_PHOTONGEYSER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_NECROZMA_DUSK_MANE 80 ITEM_ULTRANECROZIUM_Z
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    return

TriggerDawnWingsNecrozmaFight:
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_MOONGEISTBEAM
    setvar 0x8001 MOVE_MOONLIGHT
    setvar 0x8002 MOVE_POWERGEM
    setvar 0x8003 MOVE_PHOTONGEYSER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_NECROZMA_DAWN_WINGS 80 ITEM_ULTRANECROZIUM_Z
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    return

TriggerUltraNecrozmaFight:
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_PRISMATICLASER
    setvar 0x8001 MOVE_NIGHTSLASH
    setvar 0x8002 MOVE_POWERGEM
    setvar 0x8003 MOVE_PHOTONGEYSER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_NECROZMA_ULTRA 80 ITEM_ULTRANECROZIUM_Z
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    return

TriggerTypeNullEvolution:
    cry SPECIES_TYPE_NULL 0x0
    msgbox gText_DiasOfLight_TypeNullCry MSG_NORMAL
    waitcry
    msgbox gText_DiasOfLight_TypeNullEvolving MSG_KEEPOPEN
    setvar 0x8003 0x0 @ From party
    setvar 0x8004 0x0 @ First slot
    callasm EvolveTypeNull
    waitstate
    playbgm  0x181 @ Necrozma appearance
    msgbox gText_DiasOfLight_SilvallyEvolved MSG_NORMAL
    setvar 0x8005 0x00FF @ Max friendship
    special 0x13 @ Set friendship on Silvally
    setflag 0x28A @ Evolved Type Null
    return

ChallengeCatchableNecrozma:
    setflag 0x6F @ Hide Necrozma
    setvar LASTRESULT SPECIES_SOLGALEO @ Setup fight based on which Cosmog form the player has
    callasm CheckIfCaught
    compare LASTRESULT TRUE
    if TRUE _call TriggerDawnWingsNecrozmaFight
    if FALSE _call TriggerDuskManeNecrozmaFight
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _goto DefeatedOrFledFromNecrozma
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _goto DefeatedOrFledFromNecrozma
    compare LASTRESULT 0x7 @ Caught
    if equal _goto CaughtNecrozma
    end

DefeatedOrFledFromNecrozma:
    msgbox gText_DiasOfLight_NecrozmaFled MSG_NORMAL
    end

CaughtNecrozma:
    msgbox gText_DiasOfLight_NecrozmaCaught MSG_NORMAL
    setflag 0x28D @ Necrozma caught (this is easier to check than the various forms!)
    end

.global EventScript_UltraSpace_DiasOfLight_ProfessorSakura
EventScript_UltraSpace_DiasOfLight_ProfessorSakura:
    checkflag 0x289 @ Ultra Necrozma defeated
    if NOT_SET _goto SakuraBeforeUltraNecrozma
    lock
    faceplayer
    checkflag 0x28C @ Sakura congratulated player
    if NOT_SET _call Sakura_UltraNecrozmaDefeated
    msgbox gText_DiasOfLight_Sakura_ReturnHomePrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto ReturnHome
    msgbox gText_DiasOfLight_Sakura_ReturnHomePrompt_ChoseNo MSG_NORMAL
    end

SakuraBeforeUltraNecrozma:
    compare 0x4073 10
    if lessthan _goto SakuraBeforeApproachingDias
    npcchat gText_DiasOfLight_Sakura_BeforeDefeatingUltraNecrozma
    end

SakuraBeforeApproachingDias:
    npcchat gText_DiasOfLight_Sakura_BeforeReachingDias
    end

Sakura_UltraNecrozmaDefeated:
    msgbox gText_DiasOfLight_Sakura_UltraNecrozmaDefeated MSG_NORMAL
    checkflag 0x6F @ Necrozma hidden
    if NOT_SET _call Sakura_NecrozmaNotCaughtYet
    setflag 0x28C @ Sakura congratulated player
    return

Sakura_NecrozmaNotCaughtYet:
    msgbox gText_DiasOfLight_Sakura_UltraNecrozmaNotCaught MSG_NORMAL
    return

ReturnHome:
    msgbox gText_DiasOfLight_Sakura_ReturnHomePrompt_ChoseYes MSG_NORMAL
    playse 0x49 @ Escalator
    waitse
    pause DELAY_1SECOND
    playse 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement PLAYER m_HideSprite
    applymovement Sakura m_HideSprite
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    warpmuted 9 17 1 @ In front of the ultra space wormhole machine
    end

.global TileScript_UltraSpace_DiasOfLight_FirstEvent
TileScript_UltraSpace_DiasOfLight_FirstEvent:
    lock
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DiasOfLight_SakuraCommentsOnUltraSpace MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xD
    if equal _call PlayerMovesOutOfSakurasWay
    applymovement Sakura m_SakuraWalksToSecondStoppingPoint
    waitmovement Sakura
    movesprite Sakura 0x11 0x10 @ Beside second stairs
    movesprite2 Sakura 0x11 0x10 @ Beside second stairs
    addvar 0x4073 0x1 @ Now at 9
    end

.global TileScript_UltraSpace_DiasOfLight_SecondEvent
TileScript_UltraSpace_DiasOfLight_SecondEvent:
    lock
    applymovement Sakura m_LookLeft
    applymovement PLAYER m_LookRight
    msgbox gText_DiasOfLight_SakuraCommentsOnSourceOfEclipses MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xE
    if equal _call PlayerWalkRight_Return
    compare 0x4000 0x10
    if equal _call PlayerMovesOutOfSakurasWay
    applymovement Sakura m_WalkLeft
    waitmovement Sakura
    applymovement PLAYER m_SakuraAndPlayerApproachTheDias
    applymovement Sakura m_SakuraAndPlayerApproachTheDias
    waitmovement Sakura
    playbgm 0x181 @ Necrozma appearance
    call HandleNecrozmaCry
    applymovement PLAYER m_Surprise
    applymovement Sakura m_Surprise
    playse 0x15 @ Exclaim
    msgbox gText_DiasOfLight_Sakura_SeeingNecrozma MSG_NORMAL
    applymovement PLAYER m_LookRight
    applymovement Sakura m_LookLeft
    msgbox gText_DiasOfLight_Sakura_PreparingToFightNecrozma MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Sakura m_SakuraDeparts
    waitmovement Sakura
    movesprite Sakura 0x10 0x2A @ Beside second stairs
    movesprite2 Sakura 0x10 0x2A @ Beside second stairs
    addvar 0x4073 0x1 @ Now at 10
    fadedefaultbgm
    end

PlayerMovesOutOfSakurasWay:
    call PlayerWalkLeft_Return
    applymovement PLAYER m_LookUp
    return

.global EventScript_UltraSpaceCommon_InteractableBookshelf
EventScript_UltraSpaceCommon_InteractableBookshelf:
    msgbox gText_UltraSpaceCommon_InteractableBookshelf MSG_NORMAL
    end

.global EventScript_UltraSpaceCommon_InteractablePainting
EventScript_UltraSpaceCommon_InteractablePainting:
    msgbox gText_UltraSpaceCommon_InteractablePainting MSG_NORMAL
    end

.global EventScript_UltraSpaceCommon_InteractableTV
EventScript_UltraSpaceCommon_InteractableTV:
    msgbox gText_UltraSpaceCommon_InteractableTelevision MSG_NORMAL
    end

m_SakuraWalksToFirstStoppingPoint: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, look_down, end_m
m_SakuraWalksToSecondStoppingPoint: .byte walk_left, walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, look_down, end_m
m_SakuraAndPlayerApproachTheDias: .byte walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, walk_up_slow, look_up, end_m
m_SakuraDeparts: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m
