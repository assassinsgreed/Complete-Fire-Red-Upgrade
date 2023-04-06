.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4052
.equ SolvedGymRiddle, 0x2
.equ MetAlistairAtLibrary, 0x3

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

.global EventScript_FerroxLibrary_Receiptionist1
EventScript_FerroxLibrary_Receiptionist1:
    npcchat gText_FerroxLibrary_Receiptionist1
    end

.global EventScript_FerroxLibrary_Receiptionist2
EventScript_FerroxLibrary_Receiptionist2:
    npcchat gText_FerroxLibrary_Receiptionist2
    end

.global EventScript_FerroxLibrary_PCUser
EventScript_FerroxLibrary_PCUser:
    npcchat2 0x3 m_LookRight gText_FerroxLibrary_PCUser
    end

.global EventScript_FerroxLibrary_TableReader1
EventScript_FerroxLibrary_TableReader1:
    npcchat2 0x4 m_LookUp gText_FerroxLibrary_TableReader1
    end

.global EventScript_FerroxLibrary_TableReader2
EventScript_FerroxLibrary_TableReader2:
    npcchat2 0x5 m_LookDown gText_FerroxLibrary_TableReader2
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

.global EventScript_FerroxLibrary_RiddleHintMan
EventScript_FerroxLibrary_RiddleHintMan:
    msgbox gText_FerroxLibrary_RiddleHintMan MSG_NORMAL
    end

.global EventScript_FerroxLibrary_DateBoy
EventScript_FerroxLibrary_DateBoy:
    npcchat2 0xE m_LookDown gText_FerroxLibrary_DateBoy
    end

.global EventScript_FerroxLibrary_DateGirl
EventScript_FerroxLibrary_DateGirl:
    npcchat2 0xF m_LookUp gText_FerroxLibrary_DateGirl
    end

.global EventScript_FerroxLibrary_Stella
EventScript_FerroxLibrary_Stella:
    msgbox gText_FerroxLibrary_StellaChat MSG_NORMAL
    end

.global EventScript_FerroxLibrary_PokemonTrainerLaurena
EventScript_FerroxLibrary_PokemonTrainerLaurena:
    end

.global EventScript_FerroxLibrary_PokemonTrainerLona
EventScript_FerroxLibrary_PokemonTrainerLona:
    end

.global EventScript_FerroxLibrary_PokemonTrainerChet
EventScript_FerroxLibrary_PokemonTrainerChet:
    end

.global EventScript_FerroxLibrary_PokemonTrainerVincent
EventScript_FerroxLibrary_PokemonTrainerVincent:
    end

.global EventScript_FerroxLibrary_Alistair
EventScript_FerroxLibrary_Alistair:
    end

m_MoveOutOfRiddleMansWay: .byte slide_down, end_m
m_RiddleManMoves: .byte walk_up, walk_left, look_right, end_m
