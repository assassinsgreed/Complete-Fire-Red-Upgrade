.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

EndMovementAndEvent:
    waitmovement ALLEVENTS
    release
    end

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
    lock
    msgbox gText_RhodanziTrainerSchool_MainRoom_FossilStudent MSG_FACE
    applymovement 0x2 m_LookUp
    goto EndMovementAndEvent

.global EventScript_RhodanziTrainerSchool_MainRoom_Librarian
EventScript_RhodanziTrainerSchool_MainRoom_Librarian:
    lock
    msgbox gText_RhodanziTrainerSchool_MainRoom_Librarian MSG_FACE
    applymovement 0x3 m_LookUp
    goto EndMovementAndEvent

.global EventScript_RhodanziTrainerSchool_MainRoom_Professor
EventScript_RhodanziTrainerSchool_MainRoom_Professor:
    lock
    msgbox gText_RhodanziTrainerSchool_MainRoom_Professor MSG_FACE
    applymovement 0x4 m_LookRight
    goto EndMovementAndEvent

.global EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent
EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent:
    @ TODO: Document flag usage. Reference this script. We can overwrite some FR flags since they're not used
    lock
    faceplayer
    checkflag 0x230
    if FALSE _call EventScript_TypeStudentQuiz
    checkflag 0x230
    if TRUE _call EventScript_TypeStudentQuizComplete
    applymovement 0x1 m_LookUp
    waitmovement ALLEVENTS
    release
    end

EventScript_TypeStudentQuiz:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizIntro MSG_YESNO
    compare LASTRESULT YES
    if NO _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected
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
    multichoice 0x60 0x0 THREE_MULTICHOICE_OPTIONS 0x1
    copyvar 0x40FE LASTRESULT
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
    compare LASTRESULT 0
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_MYSTIC_WATER 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess MSG_FACE
    setflag 0x230
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected MSG_FACE
    applymovement 0x1 m_LookUp
    waitmovement ALLEVENTS
    release
    end

EventScript_TypeStudentQuizComplete:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizComplete MSG_FACE
    return
