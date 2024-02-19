.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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
    setvar 0x503A 0x1
    setvar 0x503B 0x1
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
    playbgm 0x156 @ Alistair's Theme
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
