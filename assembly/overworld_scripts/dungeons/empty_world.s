.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

## Story sequences

.equ VarStorySequence, 0x4062
.equ Alistair, 0x2
.equ Rival, 0x3
.equ Selene, 0x4

.global MapScript_EmptyWorld_CarnelidgeVolcanoPeak
MapScript_EmptyWorld_CarnelidgeVolcanoPeak:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_EmptyWorld_CarnelidgeVolcano_PlayerPositioning
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_EmptyWorld_CarnelidgeVolcano_StoryEvents
    .byte MAP_SCRIPT_TERMIN

LevelScripts_EmptyWorld_CarnelidgeVolcano_PlayerPositioning:
    levelscript VarStorySequence 0x2 LevelScript_PlayerPosition
	.hword LEVEL_SCRIPT_TERMIN

LevelScripts_EmptyWorld_CarnelidgeVolcano_StoryEvents:
    levelscript VarStorySequence 0x2 LevelScript_ContinueStoryConclusion
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_PlayerPosition:
    applymovement PLAYER m_LookUp
    end

LevelScript_ContinueStoryConclusion:
    pause DELAY_1SECOND
    applymovement Rival m_WalkUp
    waitmovement Rival
    applymovement Rival m_LookLeft
    msgbox gText_EmptyWorld_RivalAsksAlistairWhatHappened MSG_NORMAL
    applymovement Alistair m_LookRight
    msgbox gText_EmptyWorld_AlistairRespondsToRivalsQuestion MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Selene m_Surprise
    waitmovement Selene
    applymovement Selene m_WalkUp
    applymovement Rival m_LookDown
    applymovement Alistair m_LookDown
    msgbox gText_EmptyWorld_SeleneCommentsOnWhatHeDid MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_EmptyWorld_AlistairJustifiesHimself1 MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_EmptyWorld_AlistairJustifiesHimself2 MSG_NORMAL
    applymovement Alistair m_LookRight
    msgbox gText_EmptyWorld_AlistairJustifiesHimself3 MSG_NORMAL
    msgbox gText_EmptyWorld_RivalChallengesAlistairsDecision MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairConfirmsHisDecision MSG_NORMAL
    msgbox gText_EmptyWorld_RivalAttemptsToBattle MSG_NORMAL
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    msgbox gText_EmptyWorld_RivalRealizesWhatHappened MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairConcludesHisPoint1 MSG_NORMAL
    applymovement Alistair m_LookDown
    msgbox gText_EmptyWorld_AlistairConcludesHisPoint2 MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    applymovement Selene m_LookRight
    applymovement Alistair m_LookLeft
    msgbox gText_EmptyWorld_SeleneCondemnsAlistair MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairRebukesSelene MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneApprehendsAlistair MSG_NORMAL
    msgbox gText_EmptyWorld_AlistairAcceptsHisFate MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneGivesAlistairHisSentence MSG_NORMAL
    applymovement Selene m_WalkUp
    waitmovement Selene
    applymovement Selene m_LookDown
    msgbox gText_EmptyWorld_SeleneLeavesWithAlistair MSG_NORMAL
    applymovement Alistair m_WalkLeft
    waitmovement Alistair
    applymovement Alistair m_SeleneAndAlistairStartToLeave
    applymovement Selene m_SeleneAndAlistairStartToLeave
    waitmovement Selene
    applymovement Selene m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_EmptyWorld_SeleneTalksToPlayer MSG_NORMAL
    applymovement Rival m_WalkToSelene
    waitmovement Rival
    applymovement Selene m_LookUp
    msgbox gText_EmptyWorld_RivalAsksSeleneHowToFixThings MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneExplainsUltraSpace MSG_NORMAL
    msgbox gText_EmptyWorld_RivalWillGoToUltraSpace MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneDisapprovesOfRivalsChoice MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_EmptyWorld_AlistairRebukesRival MSG_NORMAL
    msgbox gText_EmptyWorld_RivalReaffirmsTheirChoice MSG_NORMAL
    msgbox gText_EmptyWorld_SeleneGivesIn MSG_NORMAL
    applymovement Selene m_LookDown
    msgbox gText_EmptyWorld_SeleneTakesAlistairAway MSG_NORMAL
    applymovement Alistair m_SeleneAndAlistairLeave
    applymovement Selene m_SeleneAndAlistairLeave
    waitmovement Selene
    hidesprite Selene
    hidesprite Alistair
    playse 0x9 @ Exit room
    msgbox gText_EmptyWorld_RivalCommentsOnTheirDeparture MSG_NORMAL
    applymovement Rival m_WalkRight
    waitmovement Rival
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_EmptyWorld_RivalAddressesPlayer MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookRight
    msgbox gText_EmptyWorld_RivalCommentsOnWorldState MSG_NORMAL
    applymovement Rival m_LookDown
    applymovement PLAYER m_LookUp
    msgbox gText_EmptyWorld_RivalAsksPlayerFavor MSG_YESNO
    compare LASTRESULT NO
    if equal _call PlayerSaidNoToRivalsRequest
    if notequal _call PlayerSaidYesToRivalsRequest
    msgboxsign
    msgbox gText_EmptyWorld_SystemMessageAboutWorldState MSG_SIGN
    msgboxnormal
    addvar VarStorySequence 0x1
    setflag 0x271 @ In the empty world
    clearflag 0x829 @ Hide Pokedex in menu
    clearflag 0x828 @ Disable Pokemon Menu
	setflag 0x911 @ Disable wild encounters
    @ setflag 0x91D @ Hide Save in the menu (TODO: reenable after all dev is complete)
    end

PlayerSaidNoToRivalsRequest:
    msgbox gText_EmptyWorld_PlayerDoesNotWantToGoToUltraSpace MSG_NORMAL
    applymovement Rival m_WalkLeft
    waitmovement Rival
    applymovement Rival m_SeleneAndAlistairStartToLeave
    waitmovement Rival
    applymovement PLAYER m_LookLeft
    applymovement Rival m_SeleneAndAlistairLeave
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookDown
    waitmovement Rival
    playse 0x9 @ Exit room
    hidesprite Rival
    return

PlayerSaidYesToRivalsRequest:
    applymovement Rival m_Joy
    msgbox gText_EmptyWorld_PlayerWillGoToUltraSpaceWithRival MSG_NORMAL
    applymovement Rival m_WalkDown
    applymovement PLAYER m_LookDown
    waitmovement PLAYER
    setvar 0x8000 0x3 @ Rival follows player
    special 0xD1 @ Set up rival follower
    return

m_WalkToSelene: .byte walk_left, walk_left, walk_down, end_m
m_SeleneAndAlistairStartToLeave: .byte walk_down, walk_down, walk_down, end_m
m_SeleneAndAlistairLeave: .byte walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m

## Events in the Empty World
.global MapScript_EmptyWorld_CarnelidgeVolcano
MapScript_EmptyWorld_CarnelidgeVolcano:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_EmptyWorld_CarnelidgeVolcano_WalkingScript
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_EmptyWorld_CarnelidgeVolcano_WalkingScript:
    setflag 0x926 @ Follower ignores active scripts
    setvar 0x500B 0x3 @ Use walking script #3, i.e. "mountain tremors in empty world." This is cleared if the player the first time it executes, if the player isn't on a mount carnelidge map
    setvar 0x400E 0x1 @ Used to control whether the tremor is active or not
    end

.global EmptyWorld_CarnelidgeVolcano_Tremors
EmptyWorld_CarnelidgeVolcano_Tremors:
    call DisableWalkingScriptIfOnInvalidMap
    release
    compare 0x4002 0x1
    if equal _goto End @ Don't trigger a tremor while another one is live
    random 100 @ 5% chance for heavy tremor, 15% chance for light tremor
    compare LASTRESULT 5
    if lessthan _goto HeavyTremor
    compare LASTRESULT 15
    if lessthan _goto LightTremor
    end

HeavyTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x3 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x15 @ This controls how long the overall animation lasts
	setvar 0x8007 0x3 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

LightTremor:
    setvar 0x4002 0x1
    setvar 0x8004 0x1 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x0 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x10 @ This controls how long the overall animation lasts
	setvar 0x8007 0x1 @ This controls how long one screen shake lasts
    playse 0x21 @ Small tremor
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    setvar 0x4002 0x0
    end

.global EventScript_EmptyWorld_CarnelidgeVolcano_Scientist
EventScript_EmptyWorld_CarnelidgeVolcano_Scientist:
    npcchat gText_EmptyWorld_CarnelidgeVolcano_Scientist
    end

.global EventScript_EmptyWorld_CarnelidgeVolcano_CrushGirl
EventScript_EmptyWorld_CarnelidgeVolcano_CrushGirl:
    npcchat gText_EmptyWorld_CarnelidgeVolcano_CrushGirl
    end

.global EventScript_EmptyWorld_CarnelidgeVolcano_BirdKeeper
EventScript_EmptyWorld_CarnelidgeVolcano_BirdKeeper:
    npcchat gText_EmptyWorld_CarnelidgeVolcano_BirdKeeper
    end

.global EventScript_EmptyWorld_CarnelidgeVolcano_Hiker
EventScript_EmptyWorld_CarnelidgeVolcano_Hiker:
    npcchat gText_EmptyWorld_CarnelidgeVolcano_Hiker
    end

.global EventScript_EmptyWorld_Route13_Gambler
EventScript_EmptyWorld_Route13_Gambler:
    npcchat gText_EmptyWorld_Route13_Gambler
    end

.global EventScript_EmptyWorld_Route13_SuperNerd
EventScript_EmptyWorld_Route13_SuperNerd:
    npcchat gText_EmptyWorld_Route13_SuperNerd
    end

.global EventScript_EmptyWorld_Route13_Hiker
EventScript_EmptyWorld_Route13_Hiker:
    npcchat gText_EmptyWorld_Route13_Hiker
    end

.global EventScript_EmptyWorld_Route13_Blackbelt
EventScript_EmptyWorld_Route13_Blackbelt:
    npcchat gText_EmptyWorld_Route13_Blackbelt
    end

.global EventScript_EmptyWorld_Route13_Picknicker
EventScript_EmptyWorld_Route13_Picknicker:
    npcchat gText_EmptyWorld_Route13_Picknicker
    end

.global EventScript_EmptyWorld_Route13_LycanrocGirl
EventScript_EmptyWorld_Route13_LycanrocGirl:
    npcchat gText_EmptyWorld_Route13_LycanrocGirl
    end

.global EventScript_EmptyWorld_Route13RestHouse_PCGuy
EventScript_EmptyWorld_Route13RestHouse_PCGuy:
    npcchat gText_EmptyWorld_Route13RestHouse_PCGuy
    end

.global EventScript_EmptyWorld_Route13RestHouse_Hiker
EventScript_EmptyWorld_Route13RestHouse_Hiker:
    npcchat gText_EmptyWorld_Route13RestHouse_Hiker
    end

.global EventScript_EmptyWorld_Route13RestHouse_Nurse
EventScript_EmptyWorld_Route13RestHouse_Nurse:
    npcchat gText_EmptyWorld_Route13RestHouse_Nurse
    end

.global EventScript_EmptyWorld_Route13RestHouse_BookshelfGirl
EventScript_EmptyWorld_Route13RestHouse_BookshelfGirl:
    npcchat gText_EmptyWorld_Route13RestHouse_BookshelfGirl
    end

.global SignScript_EmptyWorld_MalfunctioningPC
SignScript_EmptyWorld_MalfunctioningPC:
    msgbox gText_EmptyWorld_MalfunctioningPC MSG_SIGN
    end

.global EventScript_EmptyWorld_Route4_FatGuy
EventScript_EmptyWorld_Route4_FatGuy:
    npcchatwithmovement gText_EmptyWorld_Route4_FatGuy m_LookDown
    end

.global EventScript_EmptyWorld_Route4_ParasolLady
EventScript_EmptyWorld_Route4_ParasolLady:
    npcchatwithmovement gText_EmptyWorld_Route4_ParasolLady m_LookDown
    end

.global EventScript_EmptyWorld_Route4_Camper
EventScript_EmptyWorld_Route4_Camper:
    npcchat gText_EmptyWorld_Route4_Camper
    end

.global EventScript_EmptyWorld_Route4_Psychic
EventScript_EmptyWorld_Route4_Psychic:
    npcchat gText_EmptyWorld_Route4_Psychic
    end

.global EventScript_EmptyWorld_Route4_Beauty
EventScript_EmptyWorld_Route4_Beauty:
    npcchat gText_EmptyWorld_Route4_Beauty
    end

.global EventScript_EmptyWorld_Route4_Beauty2
EventScript_EmptyWorld_Route4_Beauty2:
    npcchat gText_EmptyWorld_Route4_Beauty2
    end

.global EventScript_EmptyWorld_Route4_Lass
EventScript_EmptyWorld_Route4_Lass:
    npcchat gText_EmptyWorld_Route4_Lass
    end

.global EventScript_EmptyWorld_Route4_BirdKeeper
EventScript_EmptyWorld_Route4_BirdKeeper:
    npcchat gText_EmptyWorld_Route4_BirdKeeper
    end

.global EventScript_EmptyWorld_Route4_CrushGirl
EventScript_EmptyWorld_Route4_CrushGirl:
    npcchat gText_EmptyWorld_Route4_CrushGirl
    end

.global EventScript_EmptyWorld_Route4_Gentleman
EventScript_EmptyWorld_Route4_Gentleman:
    npcchat gText_EmptyWorld_Route4_Gentleman
    end

.global EventScript_EmptyWorld_Route4_BirdKeeper2
EventScript_EmptyWorld_Route4_BirdKeeper2:
    npcchat gText_EmptyWorld_Route4_BirdKeeper2
    end

.global EventScript_EmptyWorld_Route4_OldLady
EventScript_EmptyWorld_Route4_OldLady:
    npcchat gText_EmptyWorld_Route4_OldLady
    end

.global EventScript_EmptyWorld_Route4_Boy
EventScript_EmptyWorld_Route4_Boy:
    npcchat gText_EmptyWorld_Route4_Boy
    end

.global EventScript_EmptyWorld_FerroxVillage_Blackbelt
EventScript_EmptyWorld_FerroxVillage_Blackbelt:
    npcchat gText_EmptyWorld_FerroxVillage_Blackbelt
    end

.global EventScript_EmptyWorld_FerroxVillage_Biker1
EventScript_EmptyWorld_FerroxVillage_Biker1:
    npcchat gText_EmptyWorld_FerroxVillage_Biker1
    end

.global EventScript_EmptyWorld_FerroxVillage_Girl
EventScript_EmptyWorld_FerroxVillage_Girl:
    npcchat gText_EmptyWorld_FerroxVillage_Girl
    end

.global EventScript_EmptyWorld_FerroxVillage_FatGuy
EventScript_EmptyWorld_FerroxVillage_FatGuy:
    npcchat gText_EmptyWorld_FerroxVillage_FatGuy
    end

.global EventScript_EmptyWorld_FerroxVillage_Policeman
EventScript_EmptyWorld_FerroxVillage_Policeman:
    npcchat gText_EmptyWorld_FerroxVillage_Policeman
    end

.global EventScript_EmptyWorld_FerroxVillage_Biker2
EventScript_EmptyWorld_FerroxVillage_Biker2:
    npcchat gText_EmptyWorld_FerroxVillage_Biker2
    end

.global EventScript_EmptyWorld_FerroxVillage_BikerBoss
EventScript_EmptyWorld_FerroxVillage_BikerBoss:
    npcchat gText_EmptyWorld_FerroxVillage_BikerBoss
    end

.global EventScript_EmptyWorld_FerroxVillage_Biker3
EventScript_EmptyWorld_FerroxVillage_Biker3:
    npcchat gText_EmptyWorld_FerroxVillage_Biker3
    end

.global EventScript_EmptyWorld_FerroxVillage_Biker4
EventScript_EmptyWorld_FerroxVillage_Biker4:
    npcchat gText_EmptyWorld_FerroxVillage_Biker4
    end

.global EventScript_EmptyWorld_FerroxVillage_Biker5
EventScript_EmptyWorld_FerroxVillage_Biker5:
    npcchat gText_EmptyWorld_FerroxVillage_Biker5
    end

.global EventScript_EmptyWorld_FerroxVillage_NPCHouses_BerryMom
EventScript_EmptyWorld_FerroxVillage_NPCHouses_BerryMom:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_NPCHouses_BerryMom m_LookRight
    end

.global EventScript_EmptyWorld_FerroxVillage_NPCHouses_BerryDaughter
EventScript_EmptyWorld_FerroxVillage_NPCHouses_BerryDaughter:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_NPCHouses_BerryDaughter m_LookLeft
    end

.global EventScript_EmptyWorld_FerroxVillage_Pokemart_MainShop
EventScript_EmptyWorld_FerroxVillage_Pokemart_MainShop:
    npcchat EmptyWorld_FerroxVillage_Pokemart_MainShop
    end

.global EventScript_EmptyWorld_FerroxVillage_Pokemart_BerryShop
EventScript_EmptyWorld_FerroxVillage_Pokemart_BerryShop:
    npcchat EmptyWorld_FerroxVillage_Pokemart_BerryShop
    end

.global EventScript_EmptyWorld_FerroxVillage_Pokemart_ShoppingGirl
EventScript_EmptyWorld_FerroxVillage_Pokemart_ShoppingGirl:
    npcchat EmptyWorld_FerroxVillage_Pokemart_ShoppingGirl
    end

.global EventScript_EmptyWorld_FerroxVillage_Pokemart_ShoppingMan
EventScript_EmptyWorld_FerroxVillage_Pokemart_ShoppingMan:
    npcchat EmptyWorld_FerroxVillage_Pokemart_ShoppingMan
    end

.global EventScript_EmptyWorld_FerroxVillage_ChinchouHouse_Dad
EventScript_EmptyWorld_FerroxVillage_ChinchouHouse_Dad:
    msgbox EmptyWorld_FerroxVillage_ChinchouHouse_Dad MSG_NORMAL
    npcchat EmptyWorld_FerroxVillage_ChinchouHouse_DadPleads
    applymovement LASTTALKED m_LookRight
    end

.global EventScript_EmptyWorld_FerroxVillage_ChinchouHouse_Daughter
EventScript_EmptyWorld_FerroxVillage_ChinchouHouse_Daughter:
    checkflag 0x248 @ Did Cosmo trade
    if SET _goto DaughterSnom
    msgbox EmptyWorld_FerroxVillage_ChinchouHouse_DaughterChinchou MSG_NORMAL
    end

DaughterSnom:
    msgbox EmptyWorld_FerroxVillage_ChinchouHouse_DaughterSnom MSG_NORMAL
    end

.global EventScript_EmptyWorld_FerroxVillage_Gym_Attendee
EventScript_EmptyWorld_FerroxVillage_Gym_Attendee:
    npcchat gText_EmptyWorld_FerroxVillage_Gym_Attendee
    end

.global EventScript_EmptyWorld_FerroxVillage_Gym_Stella
EventScript_EmptyWorld_FerroxVillage_Gym_Stella:
    npcchat gText_EmptyWorld_FerroxVillage_Gym_Stella
    end

.global EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Nurse
EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Nurse:
    npcchat gText_EmptyWorld_FerroxVillage_PokemonCenter_Nurse
    end

.global EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Picknicker
EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Picknicker:
    npcchat gText_EmptyWorld_FerroxVillage_PokemonCenter_Picknicker
    end

.global EventScript_EmptyWorld_FerroxVillage_PokemonCenter_SuperNerd
EventScript_EmptyWorld_FerroxVillage_PokemonCenter_SuperNerd:
    npcchat gText_EmptyWorld_FerroxVillage_PokemonCenter_SuperNerd
    end

.global EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Boy
EventScript_EmptyWorld_FerroxVillage_PokemonCenter_Boy:
    npcchat gText_EmptyWorld_FerroxVillage_PokemonCenter_Boy
    end

.global EventScript_EmptyWorld_FerroxVillage_TutorHouse_Tutor
EventScript_EmptyWorld_FerroxVillage_TutorHouse_Tutor:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_TutorHouse_Tutor m_LookLeft
    end

.global EventScript_EmptyWorld_FerroxVillage_TutorHouse_TutorWife
EventScript_EmptyWorld_FerroxVillage_TutorHouse_TutorWife:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_TutorHouse_TutorWife m_LookUp
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Attendant1
EventScript_EmptyWorld_FerroxVillage_Library_Attendant1:
    npcchat gText_EmptyWorld_FerroxVillage_Library_Attendant1
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Attendant2
EventScript_EmptyWorld_FerroxVillage_Library_Attendant2:
    npcchat gText_EmptyWorld_FerroxVillage_Library_Attendant2
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_PCRocker
EventScript_EmptyWorld_FerroxVillage_Library_PCRocker:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_PCRocker m_LookRight
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_TableBoy
EventScript_EmptyWorld_FerroxVillage_Library_TableBoy:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_TableBoy m_LookUp
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_TableGirl
EventScript_EmptyWorld_FerroxVillage_Library_TableGirl:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_TableGirl m_LookDown
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Lady
EventScript_EmptyWorld_FerroxVillage_Library_Lady:
    npcchat gText_EmptyWorld_FerroxVillage_Library_Lady
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Psychic
EventScript_EmptyWorld_FerroxVillage_Library_Psychic:
    npcchat gText_EmptyWorld_FerroxVillage_Library_Psychic
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_BirdKeeper
EventScript_EmptyWorld_FerroxVillage_Library_BirdKeeper:
    npcchat gText_EmptyWorld_FerroxVillage_Library_BirdKeeper
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Gentleman
EventScript_EmptyWorld_FerroxVillage_Library_Gentleman:
    npcchat gText_EmptyWorld_FerroxVillage_Library_Gentleman
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_SuperNerd
EventScript_EmptyWorld_FerroxVillage_Library_SuperNerd:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_SuperNerd m_LookLeft
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_Picknicker
EventScript_EmptyWorld_FerroxVillage_Library_Picknicker:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_Picknicker m_LookUp
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_CoupleBoy
EventScript_EmptyWorld_FerroxVillage_Library_CoupleBoy:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_CoupleBoy m_LookDown
    end

.global EventScript_EmptyWorld_FerroxVillage_Library_CoupleGirl
EventScript_EmptyWorld_FerroxVillage_Library_CoupleGirl:
    npcchatwithmovement gText_EmptyWorld_FerroxVillage_Library_CoupleGirl m_LookUp
    end

.global EventScript_EmptyWorld_Route11South_Lass
EventScript_EmptyWorld_Route11South_Lass:
    npcchat gText_EmptyWorld_Route11South_Lass
    end

.global EventScript_EmptyWorld_Route11South_HessonPassGirl
EventScript_EmptyWorld_Route11South_HessonPassGirl:
    npcchat gText_EmptyWorld_Route11South_HessonPassGirl
    end

.global EventScript_EmptyWorld_Route11South_BaldMan
EventScript_EmptyWorld_Route11South_BaldMan:
    npcchat gText_EmptyWorld_Route11South_BaldMan
    end

.global EventScript_EmptyWorld_Route11South_SuperNerd
EventScript_EmptyWorld_Route11South_SuperNerd:
    npcchat gText_EmptyWorld_Route11South_SuperNerd
    end

.global EventScript_EmptyWorld_Route11South_Channeler
EventScript_EmptyWorld_Route11South_Channeler:
    npcchat gText_EmptyWorld_Route11South_Channeler
    end

.global EventScript_EmptyWorld_Route11South_BugCatcher
EventScript_EmptyWorld_Route11South_BugCatcher:
    npcchat gText_EmptyWorld_Route11South_BugCatcher
    end

.global EventScript_EmptyWorld_Route11South_RefinersHouse_MegaStoneRefiner
EventScript_EmptyWorld_Route11South_RefinersHouse_MegaStoneRefiner:
    npcchat gText_EmptyWorld_Route11South_RefinersHouse_MegaStoneRefiner
    end

.global EventScript_EmptyWorld_Route10_Psychic
EventScript_EmptyWorld_Route10_Psychic:
    npcchatwithmovement gText_EmptyWorld_Route10_Psychic m_LookUp
    end

.global EventScript_EmptyWorld_Route10_BirdKeeper
EventScript_EmptyWorld_Route10_BirdKeeper:
    npcchat gText_EmptyWorld_Route10_BirdKeeper
    end

.global EventScript_EmptyWorld_Route10_Gambler
EventScript_EmptyWorld_Route10_Gambler:
    npcchat gText_EmptyWorld_Route10_Gambler
    end

.global EventScript_EmptyWorld_Route10_Lady
EventScript_EmptyWorld_Route10_Lady:
    npcchat gText_EmptyWorld_Route10_Lady
    end

.global EventScript_EmptyWorld_Route10_Camper
EventScript_EmptyWorld_Route10_Camper:
    npcchat gText_EmptyWorld_Route10_Camper
    end

.global EventScript_EmptyWorld_Route10_Rocker
EventScript_EmptyWorld_Route10_Rocker:
    npcchat gText_EmptyWorld_Route10_Rocker
    end

.global EventScript_EmptyWorld_Route10Guardhouse_Guard
EventScript_EmptyWorld_Route10Guardhouse_Guard:
    npcchat gText_EmptyWorld_Route10Guardhouse_Guard
    end

.global EventScript_EmptyWorld_DaimynCity_LittleGirlGuard
EventScript_EmptyWorld_DaimynCity_LittleGirlGuard:
    msgbox gText_EmptyWorld_DaimynCity_LittleGirlGuard MSG_NORMAL
    end

.global EventScript_EmptyWorld_DaimynCity_LittleGirl
EventScript_EmptyWorld_DaimynCity_LittleGirl:
    msgbox gText_EmptyWorld_DaimynCity_LittleGirl MSG_NORMAL
    end

.global EventScript_EmptyWorld_DaimynCity_Boy
EventScript_EmptyWorld_DaimynCity_Boy:
    npcchat gText_EmptyWorld_DaimynCity_Boy
    end

.global EventScript_EmptyWorld_DaimynCity_Girl
EventScript_EmptyWorld_DaimynCity_Girl:
    npcchat gText_EmptyWorld_DaimynCity_Girl
    end

.global EventScript_EmptyWorld_DaimynCity_CoupleGuard
EventScript_EmptyWorld_DaimynCity_CoupleGuard:
    npcchat gText_EmptyWorld_DaimynCity_CoupleGuard
    end

.global EventScript_EmptyWorld_DaimynCity_GuardTop
EventScript_EmptyWorld_DaimynCity_GuardTop:
    npcchat gText_EmptyWorld_DaimynCity_GuardTop
    end

.global EventScript_EmptyWorld_DaimynCity_GuardMiddle
EventScript_EmptyWorld_DaimynCity_GuardMiddle:
    npcchat gText_EmptyWorld_DaimynCity_GuardMiddle
    end

.global EventScript_EmptyWorld_DaimynCity_GuardBottom
EventScript_EmptyWorld_DaimynCity_GuardBottom:
    npcchat gText_EmptyWorld_DaimynCity_GuardBottom
    end

.global TileScript_EmptyWorld_Common_HandleRivalComments
TileScript_EmptyWorld_Common_HandleRivalComments:
    special 0xE1 @ Check if player has a follower
    compare LASTRESULT TRUE
    if notequal _goto ReleaseAndEndRivalTileEvent
    lock
    switch 0x40A4
    case 0, RivalComment1
    case 1, RivalComment2
    case 2, RivalComment3
    case 3, RivalComment4
    case 4, RivalComment5
    case 5, RivalComment6
    case 6, RivalComment7
    end

RivalComment1:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent1 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

RivalComment2:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent2 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

RivalComment3:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent3 MSG_YESNO
    compare LASTRESULT NO
    if equal _call CannotBeForgiven
    if notequal _call CanBeForgiven
    msgbox gText_EmptyWorld_Common_RivalTileEvent3_Common MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

CannotBeForgiven:
    msgbox gText_EmptyWorld_Common_RivalTileEvent3_No MSG_NORMAL
    return

CanBeForgiven:
    msgbox gText_EmptyWorld_Common_RivalTileEvent3_Yes MSG_NORMAL
    return

RivalComment4:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent4 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

RivalComment5:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent5 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

RivalComment6:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent6 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

RivalComment7:
    special 0xD3 @ Face follower
    msgbox gText_EmptyWorld_Common_RivalTileEvent7 MSG_NORMAL
    addvar 0x40A4 0x1
    goto ReleaseAndEndRivalTileEvent

ReleaseAndEndRivalTileEvent:
    release
    end

## Interdimensional Research Facility story sequences
.equ SakuraInIDF, 0x7
.equ RivalInIDF, 0x8
.equ SeleneInIDF, 0x9

.global MapScript_EmptyWorld_InterdimensionalResearchFacility
MapScript_EmptyWorld_InterdimensionalResearchFacility:
    mapscript MAP_SCRIPT_ON_LOAD Level_Script_ShowAllNPCsInInterdimensionalResearchFacility
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_EmptyWorld_InterdimensionalResearchFacility_StoryEvents
    .byte MAP_SCRIPT_TERMIN

LevelScripts_EmptyWorld_InterdimensionalResearchFacility_SetNPCPositions:
    levelscript VarStorySequence 0x4 Level_Script_ShowAllNPCsInInterdimensionalResearchFacility
	.hword LEVEL_SCRIPT_TERMIN

Level_Script_ShowAllNPCsInInterdimensionalResearchFacility:
    compare VarStorySequence 0x4
    if lessthan _goto End
    movesprite2 SakuraInIDF 0x6 0x7
    setobjectmovementtype SakuraInIDF look_down
    movesprite2 RivalInIDF 0x6 0x8
    movesprite2 SeleneInIDF 0x7 0x8
    return

LevelScripts_EmptyWorld_InterdimensionalResearchFacility_StoryEvents:
    levelscript VarStorySequence 0x3 LevelScript_InterdimensionalResearchFacilityStory
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_InterdimensionalResearchFacilityStory:
    special 0xE1 @ Check if player has a follower
    compare LASTRESULT TRUE
    if equal _call StopRivalFollower
    if notequal _call RivalWalksIn
    applymovement PLAYER m_PlayerAndRivalWalkToSakura
    applymovement RivalInIDF m_PlayerAndRivalWalkToSakura
    waitmovement RivalInIDF
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_RivalAsksWhoIsInCharge MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement SakuraInIDF m_Surprise
    pause DELAY_HALFSECOND
    applymovement SakuraInIDF m_SakuraWalksToRival
    waitmovement SakuraInIDF
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_RespondsToRivalsRequest MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_RespondsToSakura MSG_NORMAL
    applymovement SakuraInIDF m_Question
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_ListensToRival MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_AsksForSakurasHelp MSG_NORMAL
    applymovement SakuraInIDF m_LookLeft
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_ConsidersRivalsRequest MSG_NORMAL
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_RejectsRivalsRequest MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_PleadsWithSakura MSG_NORMAL
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_EntranceComment MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    applymovement RivalInIDF m_Surprise
    applymovement SakuraInIDF m_Surprise
    showsprite SeleneInIDF
    applymovement SeleneInIDF m_SeleneWalksToSakura
    pause DELAY_1SECOND
    applymovement PLAYER m_LookDown
    applymovement RivalInIDF m_LookDown
    pause DELAY_1SECOND
    applymovement PLAYER m_LookRight
    applymovement RivalInIDF m_LookRight
    waitmovement SeleneInIDF
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_CommentsOnSelenesArrival MSG_NORMAL
    applymovement SeleneInIDF m_LookLeft
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_GreetsPlayerAndRival MSG_NORMAL
    applymovement SeleneInIDF m_LookUp
    applymovement PLAYER m_LookUp
    applymovement RivalInIDF m_LookUp
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_VouchesForRival MSG_NORMAL
    applymovement SakuraInIDF m_WalkRight
    waitmovement SakuraInIDF
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_ScoldsSelene MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_Insists MSG_NORMAL
    applymovement SakuraInIDF m_WalkUp
    waitmovement SakuraInIDF
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_StartsToConsider MSG_NORMAL
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_GivesInToSelenesRequest MSG_NORMAL
    applymovement SakuraInIDF m_WalkLeft
    waitmovement SakuraInIDF
    applymovement SakuraInIDF m_WalkDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_AsksRivalsCommitment MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_Commits MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_AcceptsRivalsRequest MSG_NORMAL
    applymovement RivalInIDF m_LookRight
    applymovement SeleneInIDF m_LookLeft
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_CannotGoToUltraSpace MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_AcceptsSeleneBeingUnableToGo MSG_NORMAL
    applymovement PLAYER m_LookRight
    applymovement RivalInIDF m_LookLeft
    applymovement SeleneInIDF m_LookUp
    addvar VarStorySequence 0x1
    clearflag 0x03D @ Show Casey in cutscenes; reused for cutscenes in empty world
    call Level_Script_ShowAllNPCsInInterdimensionalResearchFacility
    goto EventScript_EmptyWorld_InterdimensionalResearchFacility_Rival
    end

RivalWalksIn:
    applymovement PLAYER m_PlayerWalksToRivalInterruption
    waitmovement PLAYER
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    showsprite RivalInIDF
    applymovement RivalInIDF m_RivalWalksToPlayer
    waitmovement RivalInIDF
    applymovement PLAYER m_LookRight
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_PlayerMetTheRival MSG_NORMAL
    return

StopRivalFollower:
    showsprite RivalInIDF
    special 0x8E
    special 0xD2 @ Stop follower
    applymovement PLAYER m_PlayerWalksToRivalInterruption
    pause 0x10 @ Pause 1/4 second to ensure rival follows player
    applymovement RivalInIDF m_RivalWalksToPlayer
    waitmovement RivalInIDF
    applymovement PLAYER m_LookRight
    waitmovement PLAYER
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_PlayerTravelledWithRival MSG_NORMAL
    return

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_PCResearcherLeft
EventScript_EmptyWorld_InterdimensionalResearchFacility_PCResearcherLeft:
    npcchatwithmovement gText_EmptyWorld_IDF_PCResearcherLeft m_LookUp
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherRight
EventScript_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherRight:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherRight m_LookUp
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_PCResearcherRight
EventScript_EmptyWorld_InterdimensionalResearchFacility_PCResearcherRight:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_PCResearcherRight m_LookUp
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_PlantResearcher
EventScript_EmptyWorld_InterdimensionalResearchFacility_PlantResearcher:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_PlantResearcher m_LookLeft
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherLeft
EventScript_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherLeft:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_MachineResearcherLeft m_LookUp
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_BeastKillerBall
EventScript_EmptyWorld_InterdimensionalResearchFacility_BeastKillerBall:
    msgbox gText_DaimynCityFacilities_IRF_TypeNullPrompt MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_BeastKillerBall MSG_NORMAL
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_Sakura
EventScript_EmptyWorld_InterdimensionalResearchFacility_Sakura:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_Sakura m_LookDown
    end

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_Rival
EventScript_EmptyWorld_InterdimensionalResearchFacility_Rival:
    faceplayer
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_AsksForPlayersHelp MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotReadyToGoToUltraSpace
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_PlayerIsReady MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x9
    if equal _call PlayerWalksToBeBesideRival
    applymovement RivalInIDF m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_SaysHeAndPlayerAreReady MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_LeadsPlayerAndRivalToMachine MSG_NORMAL
    applymovement SeleneInIDF m_LookLeft
    applymovement SakuraInIDF m_SakuraWalksToMachine
    applymovement PLAYER m_OthersWalkToMachine
    applymovement RivalInIDF m_OthersWalkToMachine
    waitmovement RivalInIDF
    applymovement PLAYER m_LookUp
    applymovement RivalInIDF m_LookUp
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_ExplainsMachine MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_ShowsConfidenceInThePlan MSG_NORMAL
    applymovement SeleneInIDF m_OthersWalkToMachine
    waitmovement SeleneInIDF
    applymovement PLAYER m_LookRight
    applymovement RivalInIDF m_LookRight
    applymovement SakuraInIDF m_LookRight
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_SendsOffPlayerAndRival MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_RespondsToSelenesSendoff MSG_NORMAL
    applymovement RivalInIDF m_LookLeft
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_AcknowledgesPlayer MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement RivalInIDF m_LookUp
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_AsksSakuraWhatToDo MSG_NORMAL
    applymovement SakuraInIDF m_LookLeft
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_GivesInstructions MSG_NORMAL
    applymovement PLAYER m_PlayerAndRivalWalkInFrontOfMachine
    applymovement RivalInIDF m_PlayerAndRivalWalkInFrontOfMachine
    waitmovement RivalInIDF
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_PreparingToStartMachine MSG_NORMAL
    applymovement SakuraInIDF m_LookUp
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_SendingOffOne MSG_NORMAL
    sound 0x26 @ Door Shut
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Researcher_SendingOffOne MSG_NORMAL
    applymovement SakuraInIDF m_LookDown
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_SendingOffTwo MSG_NORMAL
    sound 0x54 @ Exp Max
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Researcher_SendingOffTwo MSG_NORMAL
    applymovement SakuraInIDF m_LookLeft
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_SendingOffSoon MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_FeelingPull MSG_NORMAL
    applymovement SakuraInIDF m_LookDown
    sound 0x52 @ Elevator
    pause 0x10
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_SendingOffThree MSG_NORMAL
    sound 0xE8 @ Stat increase
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Researcher_SendingOffThree MSG_NORMAL
    applymovement SakuraInIDF m_LookLeft
    sound 0x49 @ Escalator
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Sakura_SendingOffFour MSG_NORMAL
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Rival_SendingOffFour MSG_NORMAL
    sound 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement PLAYER m_HideSprite
    applymovement RivalInIDF m_HideSprite
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    msgbox gText_EmptyWorld_InterdimensionalResearchFacility_Selene_CountingOnPlayerAndRival MSG_NORMAL
    addvar VarStorySequence 0x1
    setflag 0x03D @ Hide Casey in cutscenes again; reused for cutscenes in empty world
    warpmuted 2 31 0xFF 0x5 0x6 @ Warp to the landing space in ultra space
    end

NotReadyToGoToUltraSpace:
    npcchat gText_EmptyWorld_InterdimensionalResearchFacility_Rival_PlayerIsNotReady
    applymovement RivalInIDF m_LookUp @ Not using npcchatwithmovement in case player says no during cutscene
    end

PlayerWalksToBeBesideRival:
    applymovement PLAYER m_PlayerStandsBesideRivalAgain
    waitmovement PLAYER
    return

.global EventScript_EmptyWorld_InterdimensionalResearchFacility_Selene
EventScript_EmptyWorld_InterdimensionalResearchFacility_Selene:
    npcchatwithmovement gText_EmptyWorld_InterdimensionalResearchFacility_Selene m_LookUp
    end

m_PlayerWalksToRivalInterruption: .byte walk_up, walk_up, walk_up, walk_left, end_m
m_RivalWalksToPlayer: .byte walk_up, walk_up, walk_up, look_left, end_m
m_PlayerAndRivalWalkToSakura: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, end_m
m_SakuraWalksToRival: .byte walk_right, walk_right, walk_right, walk_down, walk_down, end_m
m_SeleneWalksToSakura: .byte walk_up, walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, end_m
m_PlayerStandsBesideRivalAgain: .byte walk_left, walk_up, end_m
m_SakuraWalksToMachine: .byte walk_up, walk_up, walk_left, walk_left, walk_left, end_m
m_OthersWalkToMachine: .byte walk_up, walk_up, walk_left, walk_left, end_m
m_PlayerAndRivalWalkInFrontOfMachine: .byte walk_left, walk_left, look_down, end_m
