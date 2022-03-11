.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_RhodanziTrainerSchool_Receptionist
EventScript_RhodanziTrainerSchool_Receptionist:
    lock
    msgbox gText_RhodanziTrainerSchool_Receptionist MSG_FACE
    applymovement 0x1 m_LookLeft
    applymovement PLAYER m_LookLeft
    msgbox gText_RhodanziTrainerSchool_Receptionist_Basic MSG_NORMAL
    applymovement 0x1 m_LookRight
    applymovement PLAYER m_LookRight
    msgbox gText_RhodanziTrainerSchool_Receptionist_Advanced MSG_NORMAL
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    msgbox gText_RhodanziTrainerSchool_Receptionist_Conclude MSG_FACE
    release
    end
