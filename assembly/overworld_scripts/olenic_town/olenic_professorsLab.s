.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Hawthorne, 0x1

.global MapScript_OlenicLab
MapScript_OlenicLab:
	mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_OlenicLab_ObtainingPokedex
	.byte MAP_SCRIPT_TERMIN

LevelScripts_OlenicLab_ObtainingPokedex:
	levelscript 0x4050 0x0 LevelScript_ReceivingPokedex
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
    call PokedexEvaluation_Introduction
    release
    end

.global EventScript_OlenicLab_HawthornesConservatoryAide
EventScript_OlenicLab_HawthornesConservatoryAide:
    @ TODO: Check if player has become champion
    npcchatwithmovement gText_OlenicProfessorsLab_ConservatoryAide m_LookDown
    end

.global EventScript_OlenicLab_Researcher
EventScript_OlenicLab_Researcher:
    npcchat gText_OlenicProfessorsLab_Researcher
    end

m_HawthorneMeetsPlayer: .byte walk_up, walk_up, walk_right, walk_right, walk_right, walk_down, walk_down, end_m
m_HawthorneGoesToPokedex: .byte walk_up, walk_right, end_m
m_HawthorneReturnsToPlayer: .byte walk_left, walk_down, end_m
m_HawthorneReturnsToDesk: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_down, walk_down, look_right, end_m
m_CameraPanUp: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_CameraPanDown: .byte walk_down, walk_down, walk_down, walk_down, end_m
