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
    special 0xD1 @ Set up rival follower
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

m_PlayerWalksIntoTown: .byte walk_right, walk_right, walk_right, end_m

## Ultra Space Wilds
.equ Cosmog, 0x1

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
