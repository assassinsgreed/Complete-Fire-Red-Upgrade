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

.global Pokedex_Evaluation
Pokedex_Evaluation:
    setvar 0x8004 0x1F
    special 0x17E
    special 0x17D
    setvar 0x8004 0x0
    special2 LASTRESULT 0xD4
    copyvar 0x8008 0x8005
    copyvar 0x8009 0x8006
    copyvar 0x800A LASTRESULT
    buffernumber 0x0 0x8008
    buffernumber 0x1 0x8009

/*
msgbox 0x81A6CA3 MSG_KEEPOPEN '"The amount of progress you've made..."
checkflag 0x2FF
if 0x0 call 0x81A746D
call 0x81A73B6
compare 0x800A 0x0
if 0x1 goto 0x81A748F
setvar 0x8004 0x1
special2 LASTRESULT 0xD4
copyvar 0x8008 0x8005
copyvar 0x8009 0x8006
buffernumber 0x0 0x8008
buffernumber 0x1 0x8009
msgbox 0x81A71AA MSG_KEEPOPEN '"And your NATIONAL POKéDEX is:\p[bu..."
special2 LASTRESULT 0x1B0
compare LASTRESULT 0x0
if 0x1 goto 0x81A7470
compare LASTRESULT 0x1
if 0x1 goto 0x81A747E
 */
    return

.global End
End:
    release
    end
