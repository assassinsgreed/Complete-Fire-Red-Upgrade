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
    msgboxsign
    msgbox gText_AutomaticallyEnableRunningShoes MSG_YESNO
    compare LASTRESULT YES
    if equal _goto TurnRunningShoesOn
    compare LASTRESULT NO
    if equal _goto TurnRunningShoesOff
    msgbox gText_RunningShoesToggle MSG_SIGN
    return

TurnRunningShoesOn:
    msgbox gText_AutoRunEnable MSG_SIGN
    setflag 0x914 @ Enable auto run
    return

TurnRunningShoesOff:
    msgbox gText_AutoRunDisable MSG_SIGN
    clearflag 0x914 @ Disable auto run
    return

.global PlayerWalkUp
PlayerWalkUp:
    applymovement PLAYER m_WalkUp
    waitmovement ALLEVENTS
    end

.global PlayerWalkDown
PlayerWalkDown:
    applymovement PLAYER m_WalkDown
    waitmovement ALLEVENTS
    end

.global LookDown
LookDown:
    applymovement PLAYER m_LookDown
    return

.global PlayerWalkUp_Return
PlayerWalkUp_Return:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    return

.global PlayerWalkRight_Return
PlayerWalkRight_Return:
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    return

.global PlayerWalkDown_Return
PlayerWalkDown_Return:
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    return

.global End
End:
    release
    end
