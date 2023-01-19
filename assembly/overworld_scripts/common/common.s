.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global SetWeatherClear
SetWeatherClear:
    setweather WEATHER_NORMAL
    doweather
    end

.global SetWeatherSunny
SetWeatherSunny:
    setweather WEATHER_HARSH_SUNLIGHT
    doweather
    end

.global SetWeatherSandstorm
SetWeatherSandstorm:
    setweather WEATHER_SANDSTORM
    doweather
    end

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

.global PlayerHeal
PlayerHeal:
    fadescreen 0x1
	fanfare 0x100
	waitfanfare
	special 0x0
	fadescreen 0x0
    return

.global PokedexEvaluation_Introduction
PokedexEvaluation_Introduction:
    @ Note: This script is also located at 0x81A73E0 for ratings from the PC.
    @ Not ideal, but worth keeping separately while these are actively developed
    setvar 0x8004 0x1F
    special 0x17E
    special 0x17D
    setvar 0x8004 0x0
    special2 LASTRESULT 0xD4
    copyvar 0x8008 0x8005
    copyvar 0x8009 0x8006
    setvar 0x800A 0x184 @ 388 Pokemon
    subvar 0x800A 0x8009 @ Subtract caught pokemon from total
    copyvar 0x800B LASTRESULT
    buffernumber 0x0 0x8008
    buffernumber 0x1 0x8009
    buffernumber 0x2 0x800A
    msgbox gText_PokedexAssessment_Introduction MSG_KEEPOPEN
    checkflag 0x2FF @ Assessment is from PC
    if TRUE _call SetTextColor_Black
    msgbox gText_PokedexAssessment_SeenCaughtLeft MSG_KEEPOPEN
    call PokedexEvaluation_Rating
    compare 0x800A 0x0
    if notequal _call PokedexEvaluation_PokedexIncomplete
    msgbox gText_PokedexAssessment_EvaluationComplete MSG_NORMAL
    end

PokedexEvaluation_Rating:
    copyvar 0x8004 0x8009
    special 0xD5
    waitmsg
    compare LASTRESULT 0x0
    if TRUE _call PokedexEvaluationFanfare1
    compare LASTRESULT 0x1
    if TRUE _call PokedexEvaluationFanfare2
    waitfanfare
    return

PokedexEvaluationFanfare1:
    fanfare 0x13D
    return

PokedexEvaluationFanfare2:
    fanfare 0x103
    return

PokedexEvaluation_PokedexIncomplete:
    msgbox gText_PokedexAssessment_IncompletePokedex MSG_KEEPOPEN
    return

SetTextColor_Black:
    textcolor 0x2
    return

.global End
End:
    release
    end
