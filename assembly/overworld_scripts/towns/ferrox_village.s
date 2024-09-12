.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ LoudMan, 0x2
.equ Rival, 0x9
.equ StoryEventVar, 0x4052
.equ MetRivalAtGym, 0x1

@ Overworld
.global MapScript_FerroxOverworld
MapScript_FerroxOverworld:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_FerroxOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_FerroxOverworld_FlightFlag:
    setworldmapflag 0x893
    compare StoryEventVar MetRivalAtGym
    if greaterorequal _call MoveLoudMan
    compare StoryEventVar MetRivalAtGym
    if lessorequal _call HideStellaInGym
    end

MoveLoudMan:
    movesprite2 LoudMan 0xA 0xD
    setobjectmovementtype LoudMan 0x2 @ Walk around
    return

HideStellaInGym:
    setflag 0x03B @ Hide Stella in Ferrox Gym
    return

.global EventScript_FerroxVillage_AngryLibraryVisitor
EventScript_FerroxVillage_AngryLibraryVisitor:
    npcchat gText_FerroxOverworld_AngryLibraryVisitor
    end

.global EventScript_FerroxVillage_EggFan
EventScript_FerroxVillage_EggFan:
    npcchat gText_FerroxOverworld_EggFan
    end

.global EventScript_FerroxVillage_FlowerKid
EventScript_FerroxVillage_FlowerKid:
    npcchat gText_FerroxOverworld_FlowerKid
    end

.global EventScript_FerroxVillage_AppleMan
EventScript_FerroxVillage_AppleMan:
    npcchat gText_FerroxOverworld_AppleMan
    end

.global EventScript_FerroxVillage_Policeman
EventScript_FerroxVillage_Policeman:
    checkflag 0x4A @ Pluto Defeated
    if SET _goto Policeman_PlutoDefeated
    npcchat gText_FerroxOverworld_Policeman
    end

Policeman_PlutoDefeated:
    npcchat gText_FerroxOverworld_Policeman_PlutoDefeated
    end

.global SignScript_FerroxVillage_Library
SignScript_FerroxVillage_Library:
    msgbox gText_FerroxOverworld_LibrarySign MSG_SIGN
    end

.global SignScript_FerroxVillage_Gym
SignScript_FerroxVillage_Gym:
    msgbox gText_FerroxOverworld_GymSign MSG_SIGN
    end

.global SignScript_FerroxVillage_TownEntrance
SignScript_FerroxVillage_TownEntrance:
    msgbox gText_FerroxOverworld_TownEntranceSign MSG_SIGN
    end

.global TileScript_FerroxVillage_ApproachedGym
TileScript_FerroxVillage_ApproachedGym:
    lock
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    opendoor 0x25 0x10
    waitdooranim
	playbgm 0x195
    clearflag 0x2F @ Show Rival
    showsprite Rival
    pause DELAY_1SECOND
    applymovement PLAYER m_backup
    waitmovement ALLEVENTS
    applymovement Rival m_WalkDown
    waitmovement ALLEVENTS
    closedoor 0x25 0x10
    waitdooranim
    msgbox gText_FerroxOverworld_MeetingRival MSG_NORMAL
    applymovement Rival m_rivalLeaves
    waitmovement ALLEVENTS
    setflag 0x2F @ Hide Rival
    setvar StoryEventVar MetRivalAtGym
    hidesprite Rival
    fadedefaultbgm
    call MoveLoudMan
    release
	end

m_backup: .byte slide_down, look_up, end_m
m_rivalLeaves: .byte walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down, end_m

@ Facilities
.global MapScript_FerroxFacilities_PokemonCenter
MapScript_FerroxFacilities_PokemonCenter:
	mapscript MAP_SCRIPT_ON_TRANSITION MapScript_FerroxFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_FerroxFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x04 @ Originally Cerulean City
    call ResetRoute11PlutoEventOnWhiteout
    call ResetUteyaVillageGymFlagsOnWhiteout
    end

.global EventScript_FerroxFacilities_Mart_BerryShop
EventScript_FerroxFacilities_Mart_BerryShop:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    pokemart FerroxPokemart_BerryStock
    goto EventScript_EndMart

.align 1
FerroxPokemart_BerryStock:
    .hword ITEM_ORAN_BERRY
    .hword ITEM_SITRUS_BERRY
    .hword ITEM_CHERI_BERRY
    .hword ITEM_CHESTO_BERRY
    .hword ITEM_PECHA_BERRY
    .hword ITEM_RAWST_BERRY
    .hword ITEM_ASPEAR_BERRY
    .hword ITEM_PERSIM_BERRY
    .hword ITEM_LEPPA_BERRY
    .hword ITEM_NONE

.global EventScript_FerroxFacilities_Mart_UniqueShops
EventScript_FerroxFacilities_Mart_UniqueShops:
    npcchat gText_FerroxFacilities_Mart_UniqueShops
    end

.global EventScript_FerroxFacilities_Mart_Berries
EventScript_FerroxFacilities_Mart_Berries:
    npcchat gText_FerroxFacilities_Mart_Berries
    end

.global EventScript_FerroxFacilities_Center_FerroxHikers
EventScript_FerroxFacilities_Center_FerroxHikers:
    npcchat gText_FerroxFacilities_Mart_FerroxHikers
    end

.global EventScript_FerroxFacilities_Center_StellaSibling
EventScript_FerroxFacilities_Center_StellaSibling:
    npcchat gText_FerroxFacilities_Mart_StellaSibling
    end

.global EventScript_FerroxFacilities_Center_FerroxBadge
EventScript_FerroxFacilities_Center_FerroxBadge:
    npcchat gText_FerroxFacilities_Mart_FerroxBadge
    end

@ NPC Houses
.global EventScript_FerroxNPCHouses_SmallestVillage
EventScript_FerroxNPCHouses_SmallestVillage:
    npcchatwithmovement gText_FerroxNPCHouses_SmallestVillage m_LookRight
    end

.global EventScript_FerroxNPCHouses_DailyBerry
EventScript_FerroxNPCHouses_DailyBerry:
    lock
    faceplayer
    checkflag 0xE06
    if SET _goto BerryGirlEnd
    msgbox gText_FerroxNPCHouses_BerryGirl_FreeBerry MSG_NORMAL
    random 0xA
    addvar LASTRESULT 0x85 @ Cheri Berry to Sitrus Berry
    obtainitem LASTRESULT 0x1 
    setflag 0xE06
    goto BerryGirlEnd

BerryGirlEnd:
    msgbox gText_FerroxNPCHouses_BerryGirl_ComeBackTomorrow MSG_NORMAL
    release
    end

.global EventScript_FerroxNPCHouses_MoveTutor
EventScript_FerroxNPCHouses_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_FerroxNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_FerroxNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Ferrox
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookLeft
    end

TutoringComplete:
    msgbox gText_FerroxNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_FerroxNPCHouses_TutoringRejected m_LookLeft
    end

NotEnoughPokeChips:
    npcchatwithmovement gText_FerroxNPCHouses_NotEnoughPokeChips m_LookLeft
    end

.global EventScript_FerroxNPCHouses_TutorsInTowns
EventScript_FerroxNPCHouses_TutorsInTowns:
    npcchat gText_FerroxNPCHouses_TutorsInTowns
    end

.global EventScript_FerroxNPCHouses_TradeGirlDad
EventScript_FerroxNPCHouses_TradeGirlDad:
    npcchatwithmovement gText_FerroxNPCHouses_TradeGirlDad m_LookRight
    end

.global EventScript_FerroxNPCHouses_ChinchouTrade
EventScript_FerroxNPCHouses_ChinchouTrade:
    lock
    faceplayer
    checkflag 0x248
    if SET _goto EventScript_ChinchouTradeComplete
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Request MSG_YESNO
    compare LASTRESULT NO
    if TRUE _goto EventScript_ChinchouTradeDeclined
    // Set up vars needed for trade
    setvar 0x8008 0x0 @ Set Trade #0 (Chinchou)
    copyvar 0x8004 0x8008 @ Set expected mon from Trade #0 (Snom)
    special2 LASTRESULT 0xFC // Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto EventScript_ChinchouTradeDeclined
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto EventScript_ChinchouTradeWrongPokemon
    msgbox gText_FerroxNPCHouses_ChinchouTrade_InitiatingTrade MSG_NORMAL
    call InitiateTrade
    setflag 0x248
    goto EventScript_ChinchouTradeComplete

EventScript_ChinchouTradeDeclined:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Declined MSG_NORMAL
    goto End

EventScript_ChinchouTradeWrongPokemon:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_WrongPokemon MSG_NORMAL
    goto End

EventScript_ChinchouTradeComplete:
    msgbox gText_FerroxNPCHouses_ChinchouTrade_Complete MSG_NORMAL
    goto End

@ Gym
.equ StoryEventVar, 0x4052
.equ SolvedGymRiddle, 0x2
.equ MetAlistairAtLibrary, 0x3

.equ Stella, 0xB
.equ Alistair, 0xC
.equ Rival, 0x10

.global MapScript_FerroxLibrary
MapScript_FerroxLibrary:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_FerroxLibrary_RiddleManFacing
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_FerroxLibrary_RiddleManFacing:
    compare StoryEventVar SolvedGymRiddle
    if lessthan _goto End
    movesprite2 0xA 0xD 0x6
    setobjectmovementtype 0xA 0xA @ Look Right
    end

.global SignScript_FerroxGym_Placard
SignScript_FerroxGym_Placard:
    checkflag 0x821 @ Ferrox gym badge
    if SET _goto SignScript_FerroxGym_PlacardWithBadge
    checkflag 0x039 @ Hide Stella in Ferrox Library
    if SET _goto SignScript_FerroxGym_PlacardAfterLibrary
    msgbox gText_FerroxGym_Winners MSG_SIGN
    end

SignScript_FerroxGym_PlacardWithBadge:
    msgbox gText_FerroxGym_WinnersWithBadge MSG_SIGN
    end

SignScript_FerroxGym_PlacardAfterLibrary:
    msgbox gText_FerroxGym_WinnersAfterLibrary MSG_SIGN
    end

.global EventScript_FerroxGym_GymExpert
EventScript_FerroxGym_GymExpert:
    checkflag 0x821 @ Ferrox gym badge
    if SET _goto EventScript_FerroxGym_GymExpertBadgeObtained
    checkflag 0x039 @ Hide Stella in Ferrox Library
    if SET _goto EventScript_FerroxGym_GymExpertTips
    npcchat gText_FerroxGym_ExpertLeaderOut
    end

EventScript_FerroxGym_GymExpertBadgeObtained:
    npcchat gText_FerroxGym_ExpertBadgeObtained
    end

EventScript_FerroxGym_GymExpertTips:
    npcchat gText_FerroxGym_ExpertTips
    end

.global EventScript_FerroxGym_LeaderStella
EventScript_FerroxGym_LeaderStella:
    lockall
    faceplayer
    checkflag 0x821 @ Ferrox gym badge
    if SET _goto EventScript_FerroxGym_LeaderStella_Chat
    msgbox gText_FerroxGym_LeaderStella_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 0x40 0x100 gText_FerroxGym_LeaderStella_Intro gText_FerroxGym_LeaderStella_Defeat EventScript_FerroxGym_LeaderStella_Defeated
    end

EventScript_FerroxGym_LeaderStella_Defeated:
    msgbox gText_FerroxGym_LeaderStella_BadgeAwarded MSG_NORMAL
    setflag 0x821 @ Ferrox gym badge
    fanfare 0x13D @ Gym victory
    msgbox gText_FerroxGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    settrainerflag 0x3C @ Lorena cannot be battled now
    settrainerflag 0x3D @ Lona cannot be battled now
    settrainerflag 0x3E @ Chet cannot be battled now
    settrainerflag 0x3F @ Vincent cannot be battled now
    msgbox gText_FerroxGym_LeaderStella_BadgeDescription MSG_NORMAL
    msgbox gText_FerroxGym_LeaderStella_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_FerroxGym_TMReceived
    additem ITEM_TM06 0x1
    giveitemwithfanfare ITEM_TM06 0x1 0x101 @ MUS_FANFA1
    setflag 0x297 @ Received TM 06 from Stella
    setflag 0x4B1 @ Defeated Stella
    setflag 0x25C @ New Pokemart Stock
    msgbox gText_FerroxGym_LeaderStella_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_FerroxGym_LeaderStella_Chat:
    npcchat gText_FerroxGym_LeaderStella_Chat
    end

.global EventScript_FerroxLibrary_ReadBookPromptL
EventScript_FerroxLibrary_ReadBookPromptL:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_L MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptI
EventScript_FerroxLibrary_ReadBookPromptI:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_I MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptB
EventScript_FerroxLibrary_ReadBookPromptB:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_B MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptR
EventScript_FerroxLibrary_ReadBookPromptR:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_R MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptA
EventScript_FerroxLibrary_ReadBookPromptA:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_A MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptR2
EventScript_FerroxLibrary_ReadBookPromptR2:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_R2 MSG_SIGN
    end

.global EventScript_FerroxLibrary_ReadBookPromptY
EventScript_FerroxLibrary_ReadBookPromptY:
    msgbox gText_FerroxLibrary_ReadBookPrompt MSG_NORMAL
    msgboxsign
    msgbox gText_FerroxLibrary_ReadBookPrompt_Y MSG_SIGN
    end

.global EventScript_FerroxLibrary_Receptionist1
EventScript_FerroxLibrary_Receptionist1:
    npcchat gText_FerroxLibrary_Receptionist1
    end

.global EventScript_FerroxLibrary_Receptionist2
EventScript_FerroxLibrary_Receptionist2:
    npcchat gText_FerroxLibrary_Receptionist2
    end

.global EventScript_FerroxLibrary_PCUser
EventScript_FerroxLibrary_PCUser:
    npcchatwithmovement gText_FerroxLibrary_PCUser m_LookRight
    end

.global EventScript_FerroxLibrary_TableReader1
EventScript_FerroxLibrary_TableReader1:
    npcchatwithmovement gText_FerroxLibrary_TableReader1 m_LookUp
    end

.global EventScript_FerroxLibrary_TableReader2
EventScript_FerroxLibrary_TableReader2:
    npcchatwithmovement gText_FerroxLibrary_TableReader2 m_LookDown
    end

.global EventScript_FerroxLibrary_RiddleMan
EventScript_FerroxLibrary_RiddleMan:
    compare StoryEventVar SolvedGymRiddle
    if greaterorequal _goto RiddleSolved
    msgbox gText_FerroxLibrary_RiddleMan_RiddlePrompt MSG_YESNO
    compare LASTRESULT YES
    if equal _goto RiddlePrompt
    msgbox gText_FerroxLibrary_RiddleMan_RiddleDeclined MSG_NORMAL
    end

RiddleSolved:
    msgbox gText_FerroxGym_RiddleMan_AfterSuccessfulRiddle MSG_NORMAL
    end

RiddlePrompt:
    msgbox gText_FerroxLibrary_RiddleMan_RiddleGiven MSG_NORMAL
    setvar 0x8000 0x0 @ Prompt is "Enter Phrase"
    special 0x12C @ Prompt for entry
    waitstate
    @ Check if player entered correct answer, in any casing, by comparing against pointer 0
    loadpointer 0x0 gText_FerroxGym_RiddleMan_RiddleAnswer
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto RiddleCorrect
    loadpointer 0x0 gText_FerroxGym_RiddleMan_RiddleAnswer_Lowercase
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto RiddleCorrect
    loadpointer 0x0 gText_FerroxGym_RiddleMan_RiddleAnswer_Uppercase
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto RiddleCorrect
    sound 0x1A @ Incorrect
    applymovement 0xA m_Wrong
    msgbox gText_FerroxGym_RiddleMan_GotRiddleAnswerWrong MSG_NORMAL
    end

RiddleCorrect:
    sound 0x19 @ Correct
    applymovement 0xA m_Surprise
    msgbox gText_FerroxGym_RiddleMan_GotRiddleAnswerRight MSG_NORMAL
    applymovement 0xA m_RiddleManMoves
    waitmovement ALLEVENTS
    setvar StoryEventVar SolvedGymRiddle
    movesprite2 0xA 0xD 0x6
    setobjectmovementtype 0xA 0xA @ Look Right
    end

.global EventScript_FerroxLibrary_RiddleHintGirl
EventScript_FerroxLibrary_RiddleHintGirl:
    compare StoryEventVar SolvedGymRiddle
    if greaterorequal _goto RiddleHintGirl_RiddleSolved
    npcchatwithmovement gText_FerroxLibrary_RiddleHintGirl m_LookUp
    end

RiddleHintGirl_RiddleSolved:
    npcchatwithmovement gText_FerroxLibrary_RiddleHintGirl_RiddleSolved m_LookUp
    end

.global EventScript_FerroxLibrary_DateBoy
EventScript_FerroxLibrary_DateBoy:
    npcchatwithmovement gText_FerroxLibrary_DateBoy m_LookDown
    end

.global EventScript_FerroxLibrary_DateGirl
EventScript_FerroxLibrary_DateGirl:
    npcchatwithmovement gText_FerroxLibrary_DateGirl m_LookUp
    end

.global EventScript_FerroxLibrary_Stella
EventScript_FerroxLibrary_Stella:
    msgbox gText_FerroxLibrary_StellaChat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_PokemonTrainerLaurena
EventScript_FerroxLibrary_PokemonTrainerLaurena:
    trainerbattle0 0x0 0x3C 0x0 gText_FerroxLibrary_PokemonTrainerLaurena_Intro gText_FerroxLibrary_PokemonTrainerLaurena_Defeat
    msgbox gText_FerroxLibrary_PokemonTrainerLaurena_Chat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_PokemonTrainerLona
EventScript_FerroxLibrary_PokemonTrainerLona:
    trainerbattle0 0x0 0x3D 0x0 gText_FerroxLibrary_PokemonTrainerLona_Intro gText_FerroxLibrary_PokemonTrainerLona_Defeat
    msgbox gText_FerroxLibrary_PokemonTrainerLona_Chat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_PokemonTrainerChet
EventScript_FerroxLibrary_PokemonTrainerChet:
    trainerbattle0 0x0 0x3E 0x0 gText_FerroxLibrary_PokemonTrainerChet_Intro gText_FerroxLibrary_PokemonTrainerChet_Defeat
    msgbox gText_FerroxLibrary_PokemonTrainerChet_Chat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_PokemonTrainerVincent
EventScript_FerroxLibrary_PokemonTrainerVincent:
    trainerbattle0 0x0 0x3F 0x0 gText_FerroxLibrary_PokemonTrainerVincent_Intro gText_FerroxLibrary_PokemonTrainerVincent_Defeat
    msgbox gText_FerroxLibrary_PokemonTrainerVincent_Chat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_Alistair
EventScript_FerroxLibrary_Alistair:
    call AlignPlayerForPlot
    clearflag 0x2F @ Show Rival
    showsprite Rival
    applymovement Rival m_RivalMeetsPlayer
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookDown
    msgbox gText_FerroxLibrary_Plot_RivalMeetsPlayer MSG_YESNO
    compare LASTRESULT YES
    if equal _call AgreeWithRival
    compare LASTRESULT NO
    if equal _call DisagreeWithRival
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookRight
    msgbox gText_FerroxLibrary_Plot_RivalApproachesAlistair MSG_NORMAL
    applymovement Alistair m_Question
    msgbox gText_FerroxLibrary_Plot_AlistairResponds MSG_NORMAL
    applymovement Alistair m_LookLeft
    msgbox gText_FerroxLibrary_Plot_AlistairAsksWhatHeCanHelpWith MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_RivalAsksIfAlistairIsGymLeader MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_AlistairSaysNo MSG_NORMAL
    playbgm 0x173 @ Alistair's Theme
    msgbox gText_FerroxLibrary_Plot_AlistairIntroducesHimself MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_RivalAsksWhatAlistairIsStudying MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_AlistairDeadEnds MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Alistair m_Surprise
    msgbox gText_FerroxLibrary_Plot_AlistairNoticesTheTime MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_RivalRespondsToAlistairLeaving MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_AlistairAsksAboutGymChallenge MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_RivalRespondsToGymChallengeQuestion MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_AlistairGivesCutGift MSG_NORMAL
    obtainitem ITEM_HM01 0x1
    msgbox gText_FerroxLibrary_Plot_AlistairExplainsCut MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_RivalThanksAlistair MSG_NORMAL
    msgbox gText_FerroxLibrary_Plot_AlistairLeaves MSG_NORMAL
    applymovement PLAYER m_PlayerGetsOutOfAlistairsWay
    applymovement Rival m_RivalGetsOutOfAlistairsWay
    waitmovement ALLEVENTS
    applymovement Alistair m_AlistairLeaves
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookRight
    applymovement Rival m_LookLeft
    fadedefaultbgm
    msgbox gText_FerroxLibrary_Plot_RivalCommentsOnAlistair MSG_NORMAL
    applymovement Stella m_StellaMeetsPlayerAndRival
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookLeft
    msgbox gText_FerroxLibrary_Plot_StellaConfirmsPlayersGoal MSG_YESNO
    compare LASTRESULT NO
    if equal _call AnsweredNoToStella
    msgbox gText_FerroxLibrary_Plot_StellaIntroducesHerself MSG_NORMAL
    applymovement PLAYER m_PlayerAndRivalMoveOutOfStellasWay
    applymovement Rival m_PlayerAndRivalMoveOutOfStellasWay
    waitmovement ALLEVENTS
    applymovement Stella m_StellaLeaves
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookRight
    msgbox gText_FerroxLibrary_Plot_RivalCommentsOnLuck MSG_NORMAL
    applymovement Rival m_LookDown
    msgbox gText_FerroxLibrary_Plot_RivalCommentsOnStella MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_FerroxLibrary_Plot_RivalLeaves MSG_NORMAL
    applymovement PLAYER m_PlayerMovesOutOfRivalsWay
    waitmovement ALLEVENTS
    applymovement Rival m_RivalLeaves
    waitmovement ALLEVENTS
    setflag 0x39 @ Hide Stella and Rival in library
    setflag 0x2F @ Hide Rival
    clearflag 0x3B @ Show Stella in gym
    setvar StoryEventVar MetAlistairAtLibrary
    hidesprite Stella
    hidesprite Alistair
    hidesprite Rival
    end

AlignPlayerForPlot:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x10
    if equal _call MovePlayerLeft
    compare 0x4001 0x3
    if equal _call MovePlayerDown
    compare 0x4001 0x5
    if equal _call MovePlayerUp
    applymovement PLAYER m_LookRight
    return

MovePlayerLeft:
    applymovement PLAYER m_WalkLeft
    waitmovement ALLEVENTS
    return

MovePlayerDown:
    applymovement PLAYER m_WalkDown
    waitmovement ALLEVENTS
    return

MovePlayerUp:
    applymovement PLAYER m_WalkUp
    waitmovement ALLEVENTS
    return

AgreeWithRival:
    msgbox gText_FerroxLibrary_Plot_AgreeWithRival MSG_NORMAL
    return

DisagreeWithRival:
    msgbox gText_FerroxLibrary_Plot_DisagreeWithRival MSG_NORMAL
    return

AnsweredNoToStella:
    applymovement PLAYER m_LookRight
    msgbox gText_FerroxLibrary_Plot_RivalWhenPlayerSaysNo MSG_NORMAL
    applymovement PLAYER m_LookLeft
    return

m_MoveOutOfRiddleMansWay: .byte slide_down, end_m
m_RiddleManMoves: .byte walk_up, walk_left, look_right, end_m
m_RivalMeetsPlayer: .byte walk_up, walk_up, walk_up, walk_right, walk_up, end_m
m_PlayerGetsOutOfAlistairsWay: .byte walk_up, walk_left, look_down, end_m
m_RivalGetsOutOfAlistairsWay: .byte walk_up, walk_up, look_down, end_m
m_AlistairLeaves: .byte walk_left, walk_down, walk_down, walk_left, walk_down, walk_down, walk_down, end_m
m_StellaMeetsPlayerAndRival: .byte walk_up, walk_right, walk_right, end_m
m_PlayerAndRivalMoveOutOfStellasWay: .byte walk_right, walk_right, look_left, end_m
m_StellaLeaves: .byte walk_right, walk_right, walk_down, walk_down, walk_down, walk_left, walk_down, walk_down, walk_down, end_m
m_PlayerMovesOutOfRivalsWay: .byte walk_left, walk_left, look_down, end_m
m_RivalLeaves: .byte walk_left, walk_left, walk_down, walk_down, walk_down, walk_left, walk_down, walk_down, walk_down, end_m
