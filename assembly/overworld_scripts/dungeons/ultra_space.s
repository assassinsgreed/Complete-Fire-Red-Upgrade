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
    setflag 0x272 @ Travelled to Ultra Space
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

.global EventScript_UltraSpace_AzurasVillage_Shopkeeper
EventScript_UltraSpace_AzurasVillage_Shopkeeper:
    npcchat gText_UltraSpace_AzurasVillage_Shopkeeper
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_Man
EventScript_UltraSpace_AzurasVillage_Man:
    npcchat gText_UltraSpace_AzurasVillage_Man
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_Lass
EventScript_UltraSpace_AzurasVillage_Lass:
    npcchat gText_UltraSpace_AzurasVillage_Lass
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global TileScript_UltraSpace_AzurasVillage_EmptyWorldCutscenes
TileScript_UltraSpace_AzurasVillage_EmptyWorldCutscenes:
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

.global TileScript_UltraSpace_AzurasVillage_EmptyWorldTalkingToAzurasVillageNPCs
TileScript_UltraSpace_AzurasVillage_EmptyWorldTalkingToAzurasVillageNPCs:
    lock
    special 0xD3 @ Face follower
    compare 0x40A6 0x5 @ Spoke to 5 people in Azuras Village (even the same one 5 times)
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

.global SignScript_UltraSpace_AzurasVillage_TownPlacard
SignScript_UltraSpace_AzurasVillage_TownPlacard:
    msgbox gText_UltraSpace_AzurasVillage_TownPlacard MSG_SIGN
    end

## Azuras Village NPC Houses
.global EventScript_UltraSpace_AzurasVillage_NPCHouses1_Girl
EventScript_UltraSpace_AzurasVillage_NPCHouses1_Girl:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_NPCHouses1_Girl m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses1_Boy
EventScript_UltraSpace_AzurasVillage_NPCHouses1_Boy:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_NPCHouses1_Boy m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses1_Mom
EventScript_UltraSpace_AzurasVillage_NPCHouses1_Mom:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_NPCHouses1_Mom m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses2_Dad
EventScript_UltraSpace_AzurasVillage_NPCHouses2_Dad:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_NPCHouses2_Dad m_LookRight
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses2_Daughter
EventScript_UltraSpace_AzurasVillage_NPCHouses2_Daughter:
    npcchat gText_UltraSpace_AzurasVillage_NPCHouses2_Daughter
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses3_Girl
EventScript_UltraSpace_AzurasVillage_NPCHouses3_Girl:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_NPCHouses3_Girl m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_NPCHouses3_Boy
EventScript_UltraSpace_AzurasVillage_NPCHouses3_Boy:
    npcchat gText_UltraSpace_AzurasVillage_NPCHouses3_Boy
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_BikeShop_Shopkeeper
EventScript_UltraSpace_AzurasVillage_BikeShop_Shopkeeper:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_BikeShop_Shopkeeper m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_BikeShop_Boy
EventScript_UltraSpace_AzurasVillage_BikeShop_Boy:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_BikeShop_Boy m_LookLeft
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

.global EventScript_UltraSpace_AzurasVillage_BikeShop_Man
EventScript_UltraSpace_AzurasVillage_BikeShop_Man:
    npcchatwithmovement gText_UltraSpace_AzurasVillage_BikeShop_Man m_LookUp
    addvar 0x40A6 0x1 @ Spoke to someone in Azuras Village
    end

m_PlayerWalksIntoTown: .byte walk_right, walk_right, walk_right, end_m
