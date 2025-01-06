.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_OlenicTown
MapScript_OlenicTown:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_OlenicTown_FlightSpot
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_OlenicTown_FlightSpot:
    setworldmapflag 0x891
    sethealingplace 0x01 @ Player's House
    call ResetRoute11PlutoEventOnWhiteout
    call ResetUteyaVillageGymFlagsOnWhiteout
    end

.global SignScript_OlenicOverworld_HawthornesLab
SignScript_OlenicOverworld_HawthornesLab:
    msgbox gText_OlenicOverworld_HawthornsLabSign MSG_SIGN
    end

.global EventScript_OlenicOverworld_NewTrainers
EventScript_OlenicOverworld_NewTrainers:
    npcchat gText_OlenicOverworld_NewTrainers
    end

.global EventScript_OlenicOverworld_GameKid
EventScript_OlenicOverworld_GameKid:
    npcchatwithmovement gText_OlenicOverworld_GameKid m_LookDown
    end

.global EventScript_OlenicOverworld_OldLady
EventScript_OlenicOverworld_OldLady:
    npcchat gText_OlenicOverworld_OldLady
    end

.global EventScript_OlenicOverworld_HawthorneFan
EventScript_OlenicOverworld_HawthorneFan:
    npcchat gText_OlenicOverworld_HawthorneFan
    end

.global EventScript_OlenicOverworld_FindTMSwagger
EventScript_OlenicOverworld_FindTMSwagger:
    setvar CHOSEN_ITEM ITEM_TM87
    call ItemScript_Common_FindTM
    end

.global SignScript_OlenicOverworld_TrainerTips
SignScript_OlenicOverworld_TrainerTips:
    msgbox gText_OlenicOverworld_TrainerTips MSG_SIGN
    end

@ Facilities
.global EventScript_OlenicFacilities_Mart_StockUp
EventScript_OlenicFacilities_Mart_StockUp:
    npcchat gText_OlenicFacilities_Mart_StockUp
    end

@ NPC Houses
.global EventScript_OlenicNPCHouses_FatherOfTrainer
EventScript_OlenicNPCHouses_FatherOfTrainer:
    npcchatwithmovement gText_OlenicNPCHouses_FatherOfTrainer m_LookRight
    end

.global EventScript_OlenicNPCHouses_MotherOfTrainer
EventScript_OlenicNPCHouses_MotherOfTrainer:
    npcchatwithmovement gText_OlenicNPCHouses_MotherOfTrainer m_LookLeft
    end

.global EventScript_OlenicNPCHouses_GrassTrainer
EventScript_OlenicNPCHouses_GrassTrainer:
    npcchatwithmovement gText_OlenicNPCHouses_GrassTrainer m_LookLeft
    end

.global EventScript_OlenicNPCHouses_FireTrainer
EventScript_OlenicNPCHouses_FireTrainer:
    npcchatwithmovement gText_OlenicNPCHouses_FireTrainer m_LookUp
    end

.global EventScript_OlenicNPCHouses_WaterTrainer
EventScript_OlenicNPCHouses_WaterTrainer:
    npcchatwithmovement gText_OlenicNPCHouses_WaterTrainer m_LookUp
    end

.global EventScript_OlenicNPCHouses_SinnohMother
EventScript_OlenicNPCHouses_SinnohMother:
    npcchatwithmovement gText_OlenicNPCHouses_SinnohMother m_LookRight
    end

.global EventScript_OlenicNPCHouses_SinnohChild
EventScript_OlenicNPCHouses_SinnohChild:
    npcchatwithmovement gText_OlenicNPCHouses_SinnohChild m_LookUp
    end

.global EventScript_OlenicNPCHouses_ProfessorBoy
EventScript_OlenicNPCHouses_ProfessorBoy:
    npcchatwithmovement gText_OlenicNPCHouses_ProfessorBoy m_LookRight
    end

.global EventScript_OlenicNPCHouses_ProfessorGirl
EventScript_OlenicNPCHouses_ProfessorGirl:
    npcchatwithmovement gText_OlenicNPCHouses_ProfessorGirl m_LookLeft
    end

@ Professor's Lab
.equ Hawthorne, 0x1

.global MapScript_OlenicLab
MapScript_OlenicLab:
    mapscript MAP_SCRIPT_ON_LOAD MapScript_MoveConservatoryAide
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_OlenicLab_ObtainingPokedex
	.byte MAP_SCRIPT_TERMIN

MapScript_MoveConservatoryAide:
    compare 0x4071 0x2
    if notequal _goto End
    movesprite2 0x3 0x3 0x2
    end

LevelScripts_OlenicLab_ObtainingPokedex:
	levelscript 0x4050 0x0 LevelScript_ReceivingPokedex
    levelscript 0x4071 0x1 LevelScript_GainingAccessToConservatory
	.hword LEVEL_SCRIPT_TERMIN

LevelScript_ReceivingPokedex:
    sound 0x15 @ Exclaim
	applymovement Hawthorne m_Surprise
    waitmovement Hawthorne
    pause DELAY_HALFSECOND
    msgbox gText_OlenicProfessorsLab_MeetingHawthorne MSG_NORMAL
    applymovement Hawthorne m_HawthorneMeetsPlayer
    waitmovement Hawthorne
    bufferpartypokemon 0x0 0x0
    msgbox gText_OlenicProfessorsLab_HawthorneAsksAboutStarter MSG_NORMAL
    msgbox gText_OlenicProfessorsLab_HawthorneMentionsGift MSG_NORMAL
    applymovement Hawthorne m_HawthorneGoesToPokedex
    waitmovement Hawthorne
    pause DELAY_HALFSECOND
    hidesprite 0x2
    setflag 0x03A @ Hide Pokedex sprite
    setflag 0x829 @ Show Pokedex menu
    applymovement Hawthorne m_HawthorneReturnsToPlayer
    waitmovement Hawthorne
    fanfare 0x13E
    msgbox gText_OlenicProfessorsLab_PlayerGetsPokedex MSG_KEEPOPEN
	waitfanfare
    msgbox gText_OlenicProfessorsLab_HawthorneExplainsPokedex MSG_NORMAL
    msgbox gText_OlenicProfessorsLab_HawthorneFillingPokedexRequest MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Hawthorne m_Surprise
    msgbox gText_OlenicProfessorsLab_HawthorneGivesPokeballs MSG_NORMAL
    obtainitem ITEM_POKE_BALL 0xA @ Get 10 Pokeballs
    msgbox gText_OlenicProfessorsLab_HawthornePokeballExplanation MSG_NORMAL
    applymovement Hawthorne m_LookUp
    special CAMERA_START
    applymovement CAMERA m_CameraPanUp
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_OlenicProfessorsLab_HawthorneUsePC MSG_NORMAL
    special CAMERA_START
    applymovement CAMERA m_CameraPanDown
    waitmovement CAMERA
    special CAMERA_END
    applymovement Hawthorne m_LookDown
    msgbox gText_OlenicProfessorsLab_HawthorneExplainsGyms MSG_NORMAL
    msgbox gText_OlenicProfessorsLab_HawthorneBidsFarewell MSG_NORMAL
    applymovement Hawthorne m_HawthorneReturnsToDesk
    waitmovement Hawthorne
    setflag 0x030 @ Hide blocking events in Anthra Town
	setvar 0x4050 0x1
    addvar 0x40FF 0x1 @ Enable catching event on Route 2, if player requested tutorialization
	end

LevelScript_GainingAccessToConservatory:
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
	applymovement Hawthorne m_Surprise
    waitmovement Hawthorne
    pause DELAY_HALFSECOND
    msgbox gText_OlenicProfessorsLab_HawthorneWelcomesPlayerAsChampion MSG_NORMAL
    applymovement Hawthorne m_HawthorneMeetsPlayer
    waitmovement Hawthorne
    msgbox gText_OlenicProfessorsLab_HawthorneCongratulatesPlayer MSG_NORMAL
    applymovement Hawthorne m_HawthorneWalksToConservatoryEntrance
    applymovement PLAYER m_PlayerWalksToConservatoryEntrance
    waitmovement PLAYER
    msgbox gText_OlenicProfessorsLab_HawthorneIntroducesTheConservatory MSG_NORMAL
    applymovement Hawthorne m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_OlenicProfessorsLab_HawthorneTalksAboutConservatory MSG_NORMAL
    applymovement Hawthorne m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_OlenicProfessorsLab_HawthorneGivesPlayerAccessToTheConservatory MSG_NORMAL
    msgbox gText_OlenicProfessorsLab_AideMovesAside MSG_NORMAL
    applymovement 0x3 m_WalkLeft
    waitmovement 0x3
    applymovement 0x3 m_LookDown
    movesprite2 0x3 0x3 0x2
    applymovement Hawthorne m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_OlenicProfessorsLab_HawthorneGivesPlayerBlessingToCatchPokemonInGarden MSG_NORMAL
    applymovement Hawthorne m_HawthorneReturnsToDeskFromConservatory
    waitmovement Hawthorne
    addvar 0x4071 0x1 @ End cutscene
    end

.global SignScript_OlenicLab_Conservatory
SignScript_OlenicLab_Conservatory:
    msgbox gText_OlenicProfessorsLab_ConservatorySign MSG_SIGN
    end

.global EventScript_OlenicLab_Hawthorne
EventScript_OlenicLab_Hawthorne:
    lock
    faceplayer
    msgbox gText_OlenicProfessorsLab_HawthornePokedexEvaluation MSG_NORMAL
    clearflag 0x2FF @ Assessment is in person (prevents bug when evaluating at PC, then with Hawthorne)
    call PokedexEvaluation_Introduction
    release
    end

.global EventScript_OlenicLab_HawthornesConservatoryAide
EventScript_OlenicLab_HawthornesConservatoryAide:
    checkflag 0x4BC @ Player is champion
    if SET _goto ConservatoryAide_AfterChampion
    npcchatwithmovement gText_OlenicProfessorsLab_ConservatoryAide m_LookDown
    end

ConservatoryAide_AfterChampion:
    npcchatwithmovement gText_OlenicProfessorsLab_ConservatoryAide_AfterBecomingChampion m_LookDown
    end

.global EventScript_OlenicLab_Researcher
EventScript_OlenicLab_Researcher:
    npcchatwithmovement gText_OlenicProfessorsLab_Researcher m_LookUp
    end

.global SignScript_OlenicTown_HawthornesConservatory_GrassAreaSign
SignScript_OlenicTown_HawthornesConservatory_GrassAreaSign:
    msgbox gText_OlenicTown_HawthornesConservatory_GrassAreaSign MSG_SIGN
    end

.global SignScript_OlenicTown_HawthornesConservatory_FireAreaSign
SignScript_OlenicTown_HawthornesConservatory_FireAreaSign:
    msgbox gText_OlenicTown_HawthornesConservatory_FireAreaSign MSG_SIGN
    end

.global SignScript_OlenicTown_HawthornesConservatory_WaterAreaSign
SignScript_OlenicTown_HawthornesConservatory_WaterAreaSign:
    msgbox gText_OlenicTown_HawthornesConservatory_WaterAreaSign MSG_SIGN
    end

.global EventScript_OlenicLab_ToolsDeveloper
EventScript_OlenicLab_ToolsDeveloper:
    lock
    faceplayer
    msgbox gText_OlenicLab_ToolDeveloper_Intro MSG_NORMAL
    checkflag 0x4BC @ Beat Selene, became champion
    if NOT_SET _goto ToolsDeveloper_NotChampion
    msgbox gText_OlenicLab_ToolDeveloper_PlayerIsChampion MSG_NORMAL
PromptForTool:
    msgbox gText_OlenicLab_ToolDeveloper_PromptForTool MSG_NORMAL
    multichoiceoption gText_OlenicLab_ToolDeveloper_PokeVialChoice 0
	multichoiceoption gText_OlenicLab_ToolDeveloper_InfiniteRepelChoice 1
	multichoiceoption gText_OlenicLab_ToolDeveloper_ADMChoice 2
	multichoiceoption gText_OlenicLab_ToolDeveloper_ExitChoice 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
    case 0, ToolDeveloper_PokeVial _goto
    case 1, ToolDeveloper_InfiniteRepel _goto
    case 2, ToolDeveloper_ADM _goto
    case 3, ToolDeveloper_Exit _goto
    goto ToolDeveloper_Exit @ If player presses B

ToolsDeveloper_NotChampion:
    npcchatwithmovement gText_OlenicLab_ToolDeveloper_PlayerNotChampion m_LookLeft
    end

ToolsDeveloper_PurchaseTool:
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchasePrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ToolDeveloper_Exit
    compare 0x8005 30
    if lessthan _goto ToolsDeveloper_NotEnoughPokeChips
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseHaveEnoughChips MSG_NORMAL
    playse 0xF8 @ Money SE
    waitse
    removeitem ITEM_POKE_CHIP 30
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseStarting MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseWorking MSG_NORMAL
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseWorking2 MSG_NORMAL
    fadescreen FADEIN_BLACK
    return

ToolsDeveloper_NotEnoughPokeChips:
    npcchatwithmovement gText_OlenicLab_ToolDeveloper_ToolPurchaseNotEnoughChips m_LookLeft
    end

ToolDeveloper_PokeVial:
    msgbox gText_OlenicLab_ToolDeveloper_PokeVialDescription MSG_NORMAL
    checkflag 0x938 @ PokeVial active in menu
    if SET _goto PromptForTool
    call ToolsDeveloper_PurchaseTool
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseComplete MSG_NORMAL
    setflag 0x938 @ PokeVial active in menu
    setvar 0x40AE 0x3 @ Fully fill the pokevial
    obtainitem ITEM_POKE_VIAL 0x1
    msgbox gText_OlenicLab_ToolDeveloper_CommentingOnToolCreation MSG_NORMAL
    goto PromptForTool

ToolDeveloper_InfiniteRepel:
    msgbox gText_OlenicLab_ToolDeveloper_InfiniteRepelDescription MSG_NORMAL
    checkflag 0x937 @ Obtained Infinite Repel
    if SET _goto PromptForTool
    call ToolsDeveloper_PurchaseTool
    msgbox gText_OlenicLab_ToolDeveloper_ToolPurchaseComplete MSG_NORMAL
    setflag 0x937 @ Obtained Infinite Repel
    obtainitem ITEM_INFINITE_REPEL 0x1
    msgbox gText_OlenicLab_ToolDeveloper_CommentingOnToolCreation MSG_NORMAL
    goto PromptForTool

ToolDeveloper_ADM:
    msgbox gText_OlenicLab_ToolDeveloper_ADMDescription MSG_NORMAL
    checkflag 0x939 @ Obtained ADM
    if SET _goto PromptForTool
    call ToolsDeveloper_PurchaseTool
    msgbox gText_OlenicLab_ToolDeveloper_ADMPurchaseComplete MSG_NORMAL
    setflag 0x939 @ Obtained ADM
    fanfare 0x101 @ Got Item / Level up
    obtainitem ITEM_ADM 0x1
    waitfanfare
    msgbox gText_OlenicLab_ToolDeveloper_CommentingOnToolCreation MSG_NORMAL
    goto PromptForTool

ToolDeveloper_Exit:
    npcchatwithmovement gText_OlenicLab_ToolDeveloper_ChoseQuit m_LookLeft
    end

m_HawthorneMeetsPlayer: .byte walk_up, walk_up, walk_right, walk_right, walk_right, walk_down, walk_down, end_m
m_HawthorneGoesToPokedex: .byte walk_up, walk_right, end_m
m_HawthorneReturnsToPlayer: .byte walk_left, walk_down, end_m
m_HawthorneReturnsToDesk: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_down, walk_down, look_right, end_m
m_CameraPanUp: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_CameraPanDown: .byte walk_down, walk_down, walk_down, walk_down, end_m
m_HawthorneWalksToConservatoryEntrance: .byte walk_up, walk_up, walk_up, walk_left, look_up, end_m
m_PlayerWalksToConservatoryEntrance: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_HawthorneReturnsToDeskFromConservatory: .byte walk_left, walk_down, walk_left, walk_down, walk_down, look_right, end_m
