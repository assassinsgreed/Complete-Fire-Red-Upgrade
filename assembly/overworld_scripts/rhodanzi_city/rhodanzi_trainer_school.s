.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

EndMovementAndEvent:
    waitmovement ALLEVENTS
    release
    end

@ Main room events
.global EventScript_RhodanziTrainerSchool_MainRoom_Receptionist
EventScript_RhodanziTrainerSchool_MainRoom_Receptionist:
    lock
    compare PLAYERFACING UP
    if TRUE _goto ReceptionistHelp
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_GoToDesk MSG_FACE
    applymovement 0x1 m_LookDown
    goto EndMovementAndEvent

ReceptionistHelp:
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist MSG_FACE
    applymovement 0x1 m_LookLeft
    applymovement PLAYER m_LookLeft
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Basic MSG_NORMAL
    applymovement 0x1 m_LookRight
    applymovement PLAYER m_LookRight
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Advanced MSG_NORMAL
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Conclude MSG_FACE
    release
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_FossilStudent
EventScript_RhodanziTrainerSchool_MainRoom_FossilStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_FossilStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_Librarian
EventScript_RhodanziTrainerSchool_MainRoom_Librarian:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_Librarian m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_Professor
EventScript_RhodanziTrainerSchool_MainRoom_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_Professor m_LookRight
    end

.global EventScript_RhodanziTrainerSchool_TerrainTutor
EventScript_RhodanziTrainerSchool_TerrainTutor:
    faceplayer
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Intro MSG_NORMAL
    checkflag 0x820 @ Has Terrain Badge
    IF SET _goto TerrainTutor
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_DoesNotHaveBadge MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

TerrainTutor:
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Confirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Terrain
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookDown
    end

TutoringComplete:
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_ConfirmationRejected m_LookDown
    end

NotEnoughPokeChips:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_NotEnoughPokeChips m_LookDown
    end

@ Basic Course
.global EventScript_RhodanziTrainerSchool_BasicCourse_Professor
EventScript_RhodanziTrainerSchool_BasicCourse_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_Professor m_LookDown
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent
EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent:
    lock
    faceplayer
    checkflag 0x230
    if NOT_SET _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuiz
    checkflag 0x230
    if SET _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuizComplete
    applymovement 0x2 m_LookUp
    waitmovement ALLEVENTS
    release
    end

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuiz:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizIntro MSG_YESNO
    compare LASTRESULT YES
    if FALSE _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestion
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestion:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizAccepted MSG_FACE
    compare 0x4031 0 @ Grass
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionGrass
    compare 0x4031 1 @ Fire
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionFire
    compare 0x4031 2 @ Water
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionWater
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices:
    multichoiceoption gText_TypeGrass 0
    multichoiceoption gText_TypeFire 1
    multichoiceoption gText_TypeWater 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS 0x1
    copyvar MULTICHOICE_SELECTION LASTRESULT
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionGrass:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_GrassQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 2
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_MIRACLE_SEED 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionFire:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_FireQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 0
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_CHARCOAL 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionWater:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_WaterQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 1
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_MYSTIC_WATER 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess:
    applymovement LASTTALKED m_Joy
    playse 0x19 @ Correct
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess MSG_FACE
    setflag 0x230
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail:
    applymovement LASTTALKED m_Wrong
    playse 0x1A @ Error
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected MSG_FACE
    applymovement 0x2 m_LookUp
    goto EndMovementAndEvent

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuizComplete:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizComplete MSG_FACE
    return

.global EventScript_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent
EventScript_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_KOStudent
EventScript_RhodanziTrainerSchool_BasicCourse_KOStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_KOStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent
EventScript_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent
EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent:
    lock
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent MSG_FACE
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question
    end

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question MSG_KEEPOPEN
    multichoiceoption gText_Burn 0
    multichoiceoption gText_Frostbite 1
    multichoiceoption gText_Paralysis 2
    multichoiceoption gText_Poison 3
    multichoiceoption gText_Sleep 4
    multichoiceoption gText_End 5
    multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
    copyvar MULTICHOICE_SELECTION LASTRESULT
    switch LASTRESULT
    case 0, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Burn
    case 1, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Frostbite
    case 2, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Paralysis
    case 3, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Poison
    case 4, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Sleep
    case 5, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done
    end

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Burn:
    msgbox gText_BurnDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Frostbite:
    msgbox gText_FrostbiteDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Paralysis:
    msgbox gText_ParalysisDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Poison:
    msgbox gText_PoisonDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Sleep:
    msgbox gText_SleepDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done MSG_NORMAL
    applymovement 0x6 m_LookUp
    goto EndMovementAndEvent

@ Advanced Course
.global EventScript_RhodanziTrainerSchool_AdvancedCourse_Professor
EventScript_RhodanziTrainerSchool_AdvancedCourse_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_Professor m_LookDown
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_TMsStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_TMsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_TMsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_HMsStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_HMsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_HMsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_LastPokeball
EventScript_RhodanziTrainerSchool_AdvancedCourse_LastPokeball:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_LastPokeball m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_QuickRun
EventScript_RhodanziTrainerSchool_AdvancedCourse_QuickRun:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_QuickRun m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems
EventScript_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems m_LookDown
    end
