.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global WalkUp
WalkUp:
    applymovement PLAYER m_WalkUp
    return

.global WalkDown
WalkDown:
    applymovement PLAYER m_WalkDown
    return

.global LookDown
LookDown:
    applymovement PLAYER m_LookDown
    return

.global End
End:
    release
    end
