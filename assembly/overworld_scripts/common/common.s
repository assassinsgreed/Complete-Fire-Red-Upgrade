.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global SetWeatherClear
SetWeatherClear:
    setweather WEATHER_NORMAL
    doweather
    return

.global SetWeatherSunny
SetWeatherSunny:
    setweather WEATHER_HARSH_SUNLIGHT
    doweather
    return

.global SetWeatherRain
SetWeatherRain:
    setweather WEATHER_RAIN
    doweather
    return

.global SetWeatherSandstorm
SetWeatherSandstorm:
    setweather WEATHER_SANDSTORM
    doweather
    return

.global SetWeatherFog
SetWeatherFog:
    setweather WEATHER_FOG
    doweather
    return

.global SetWeatherThinFog
SetWeatherThinFog:
    @ Weather intentionally does not have battle effect
    setweather WEATHER_THIN_FOG
    doweather
    return

.global ClearTerrain
ClearTerrain:
    setvar 0x5000 0x0
    return

.global SetElectricTerrain
SetElectricTerrain:
    setvar 0x5000 0x1
    return

.global SetGrassyTerrain
SetGrassyTerrain:
    setvar 0x5000 0x2
    return

.global SetMistyTerrain
SetMistyTerrain:
    setvar 0x5000 0x3
    return

.global SetPsychicTerrain
SetPsychicTerrain:
    setvar 0x5000 0x4
    return

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

.global LookUp
LookUp:
    applymovement PLAYER m_LookUp
    return

.global LookDown
LookDown:
    applymovement PLAYER m_LookDown
    return

.global LookLeft
LookLeft:
    applymovement PLAYER m_LookLeft
    return

.global LookRight
LookRight:
    applymovement PLAYER m_LookRight
    return

.global PlayerWalkUp_Return
PlayerWalkUp_Return:
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    return

.global PlayerWalkLeft_Return
PlayerWalkLeft_Return:
    applymovement PLAYER m_WalkLeft
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
    fadescreenswapbuffers 0x1
	fanfare 0x100
	waitfanfare
	special 0x0
    fadescreenswapbuffers 0x0
    return

.global SetupRoute11RivalPartner
SetupRoute11RivalPartner:
    call SetupPartner
    copyvar 0x5011 0x408E
    setvar 0x4002 189 @ trainer ID, which is 189 + 0-7 depending on value in 0x408E
    setvar 0x8004 0x5011
    setvar 0x8005 0x4002
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    setvar 0x5012 0x6 @ Set trainer backsprite
    return

.global SetupRoute11AlistairPartner
SetupRoute11AlistairPartner:
    call SetupPartner
    setvar 0x5011 197 @ Set partner trainer ID
    setvar 0x5012 0x7 @ Set trainer backsprite
    return

SetupPartner:
    setflag 0x908 @ Start tag battles
    setflag 0x910 @ Initiate wild double battles
    setvar 0x8000 LASTTALKED @ Team up with whomever was last talked to
    setvar 0x8001 0x80 @ Return to original spot on whiteout. No special movement animations, cannot use HMs or Fly/Teleport/Dig/Escape Rope
    special 0xD1
    return

.global ResetRoute11PlutoEventOnWhiteout
ResetRoute11PlutoEventOnWhiteout:
    compare 0x4099 0x0
    if equal _goto End
    setvar 0x4099 0x0 @ No follower
    setvar 0x4059 0x1 @ Need to pick partner
    return

.global PokedexEvaluation_Introduction
PokedexEvaluation_Introduction:
    @ Note: This script is also located at 0x81A73E0 for ratings from the PC.
    @ Not ideal, but worth keeping separately while these are actively developed, and until repointing effectively can be figured out
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
    goto PokedexEvaluation_Rating

PokedexEvaluation_Rating:
    copyvar 0x8004 0x8009
    comparevartovalue 0x8009 0x32 @ 50
    if lessorequal _goto FiftyOrLessCaught
    comparevartovalue 0x8009 0x64 @ OneHundred
    if lessorequal _goto OneHundredOrLessCaught
    comparevartovalue 0x8009 0x96 @ 150
    if lessorequal _goto OneHundredFiftyOrLessCaught
    comparevartovalue 0x8009 0xC8 @ 200
    if lessorequal _goto TwoHundredOrLessCaught
    comparevartovalue 0x8009 0xFA @ 250
    if lessorequal _goto TwoHundredFiftyOrLessCaught
    comparevartovalue 0x8009 0x12C @ 300
    if lessorequal _goto ThreeHundredOrLessCaught
    comparevartovalue 0x8009 0x15E @ 350
    if lessorequal _goto ThreeHundredFiftyOrLessCaught
    comparevartovar 0x8009 0x800A @ All Pokemon
    if equal _goto AllCaught

PokedexEvaluation_Conclusion:
    compare 0x800A 0x0
    if notequal _call PokedexEvaluation_PokedexIncomplete
    msgbox gText_PokedexAssessment_EvaluationComplete MSG_NORMAL
    end

FiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_FiftyOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

OneHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_OneHundredOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

OneHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_OneHundredFiftyOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

TwoHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_TwoHundredOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

TwoHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_TwoHundredFiftyOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

ThreeHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_ThreeHundredOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

ThreeHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_ThreeHundredFiftyOrLessCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

AllCaught:
    call PokedexEvaluationFanfare2
    msgbox gText_PokedexAssessment_AllCaught MSG_NORMAL
    waitfanfare
    goto PokedexEvaluation_Conclusion

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

.global SelectTradePokemon
SelectTradePokemon:
    special 0x9F
    waitstate
    copyvar 0x800A 0x8004
    return

.global CheckTradePokemonSelected
CheckTradePokemonSelected:
    copyvar 0x8005 0x800A
    special2 LASTRESULT 0xFF
    copyvar 0x800B LASTRESULT
    return

.global InitiateTrade
InitiateTrade:
    copyvar 0x8004 0x8008
    copyvar 0x8005 0x800A
    special 0xFD
    special 0xFE
    waitstate
    return

.global EventScript_Common_VendingMachine
EventScript_Common_VendingMachine:
    preparemsg gText_VendingMachinesChoice
    waitmsg
    showmoney 0x0 0x0
    multichoice 0x60 0x0 0x1A 0x0 @ Vanilla vending machine multichoice
    copyvar 0x4001 LASTRESULT
    copyvar 0x8000 0x4001
    compare 0x8000 0x0
    if equal _goto FreshWater
    compare 0x8000 0x1
    if equal _goto SodaPop
    compare 0x8000 0x2
    if equal _goto Lemonade
    msgbox gText_VendingMachinesChoseNotTo MSG_NORMAL
    goto StopVending

FreshWater:
    setvar 0x4000 0x1A @ Fresh Water
    checkmoney 0xC8 0x0 @ 200
    compare LASTRESULT 0x0
    if equal _goto NotEnoughMoney
    removemoney 0xC8
    goto CompleteTransaction

SodaPop:
    setvar 0x4000 0x1B @ Soda Pop
    checkmoney 0x12C 0x0 @ 300
    compare LASTRESULT 0x0
    if equal _goto NotEnoughMoney
    removemoney 0x12C
    goto CompleteTransaction

Lemonade:
    setvar 0x4000 0x1C @ Lemonade
    checkmoney 0x15E 0x0 @ 350
    compare LASTRESULT 0x0
    if equal _goto NotEnoughMoney
    removemoney 0x15E
    goto CompleteTransaction

CompleteTransaction:
    sound 0xF8 @ Money SE
    updatemoney 0x0 0x0
    pause DELAY_HALFSECOND
    bufferitem 0x0 0x4000
    random 0x3 @ 1 in 3
    compare LASTRESULT 0x0
    if equal _goto GiveDoubleItem
    msgbox gText_VendingMachinesOneItem MSG_NORMAL
    additem 0x4000 0x1
    goto StopVending

NotEnoughMoney:
    msgbox gText_VendingMachinesNotEnoughMoney MSG_NORMAL
    goto StopVending

GiveDoubleItem:
    msgbox gText_VendingMachinesTwoItems MSG_NORMAL
    additem 0x4000 0x2
    goto StopVending

StopVending:
    hidemoney
    goto End

.global SetCaseyFemale
SetCaseyFemale:
    setvar 0x5029 84
    textcolor RED
    return

.global SetCaseyMale
SetCaseyMale:
    setvar 0x5029 59
    textcolor BLUE
    return

.global End
End:
    release
    end
