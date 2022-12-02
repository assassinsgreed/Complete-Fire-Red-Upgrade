.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EnableRunningShoes
EnableRunningShoes:
    setflag 0x82F @ Enable running shoes
    playse 0x0102 @ Play obtain item jingle
    msgbox gText_ReceiveRunningShoes MSG_NORMAL
    waitfanfare
    msgbox gText_AutomaticallyEnableRunningShoes MSG_YESNO
    compare LASTRESULT YES
    if equal _goto TurnRunningShoesOn
    compare LASTRESULT NO
    if equal _goto TurnRunningShoesOff
    msgbox gText_RunningShoesToggle MSG_NORMAL
    return

TurnRunningShoesOn:
    msgbox gText_RunningShoesOn MSG_NORMAL
    setflag 0x914 @ Enable auto run
    return

TurnRunningShoesOff:
    msgbox gText_RunningShoesOff MSG_NORMAL
    clearflag 0x914 @ Disable auto run
    return

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
