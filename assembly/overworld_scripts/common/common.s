.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

// HMs

/*
    Move Name indexes:
    Cut         0xF
    Fly         0x13
    Surf        0x39
    Strength    0x46
    Rock Smash  0xF9
 */

.global EventScript_Common_Cut
EventScript_Common_Cut:
    lockall
    checkflag 0x821 @ Patch Badge, Gym 2
    if NOT_SET _goto EventScript_Common_CutFillerText
    special 0x10A @ Check if party Pokemon can learn Cut
    compare 0x8004 0x6
    IF equal _goto EventScript_Common_CutFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Cut
    bufferattack 0x1 0xF @ Store Cut attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x2
    waitstate
    applymovement LASTTALKED m_CutTree
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    goto ReleaseAll

EventScript_Common_CutFillerText:
    msgbox gText_Common_CuttableTree MSG_SIGN
    goto ReleaseAll

.global EventScript_Common_RockSmash
EventScript_Common_RockSmash:
    lockall
    checkflag 0x822 @ Stormcloud Badge, Gym 3
    if NOT_SET _goto EventScript_Common_RockFillerText
    special 0x10B @ Check if party Pokemon can learn Rock Smash
    compare 0x8004 0x6
    if equal _goto EventScript_Common_RockFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Rock Smash
    bufferattack 0x1 0xF9 @ Store Rock Smash attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x25
    waitstate
    applymovement LASTTALKED m_SmashRock
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    special 0xAB @ Attempt to trigger battle
    goto ReleaseAll

EventScript_Common_RockFillerText:
    msgbox gText_Common_SmashableRock MSG_SIGN
    goto ReleaseAll

.global EventScript_Common_Strength
EventScript_Common_Strength:
    checkflag 0x805
    if SET _goto AlreadyAbleToPushBoulders
    lockall
    checkflag 0x826 @ Support Badge, Gym 7
    if NOT_SET _goto EventScript_Common_StrengthFillerText
    special 0x10C @ Check if party Pokemon can learn Strength
    compare 0x8004 0x6
    if equal _goto EventScript_Common_StrengthFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Rock Smash
    bufferattack 0x1 0x46 @ Store Strength attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x28
    waitstate
    setflag 0x805 @ Can now push boulders while on this map
    goto ReleaseAll

AlreadyAbleToPushBoulders:
    msgbox gText_Common_CanAlreadyPushBoulders MSG_SIGN
    goto ReleaseAll

EventScript_Common_StrengthFillerText:
    msgbox gText_Common_PushableRock MSG_SIGN
    goto ReleaseAll

ReleaseAll:
    releaseall
    end

.global EventScript_EmptyWorld_Common_Cut
EventScript_EmptyWorld_Common_Cut:
    msgbox gText_EmptyWorld_Common_CuttableTree MSG_SIGN
    end

.global EventScript_EmptyWorld_Common_RockSmash
EventScript_EmptyWorld_Common_RockSmash:
    msgbox gText_EmptyWorld_Common_SmashableRock MSG_SIGN
    end

.global EventScript_EmptyWorld_Common_Strength
EventScript_EmptyWorld_Common_Strength:
    msgbox gText_EmptyWorld_Common_PushableRock MSG_SIGN
    end

m_CutTree: .byte cut_tree, end_m
m_SmashRock: .byte smash_rock, end_m

// Common Funcs

.global MapScript_WaterRoutes_SetRivalBruccieGymFlag
MapScript_WaterRoutes_SetRivalBruccieGymFlag:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_OceanMaps_SetRivalBruccieGymFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_OceanMaps_SetRivalBruccieGymFlag:
    setflag 0x25B @ Player has surfed into the ocean
    end

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

.global SetWeatherThreeSnowflakes
SetWeatherThreeSnowflakes:
    setweather WEATHER_THREE_SNOWFLAKES
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

.global SetWeatherSnowstorm
SetWeatherSnowstorm:
    setweather WEATHER_SNOW
    doweather
    return

.global SetWeatherDark
SetWeatherDark:
    setweather WEATHER_BIT_DARK
    doweather
    return

// Terrains are all once per battle and cleared. See battle_start_turn_start for map based permanent terrain
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
    fanfare 0x102 @ Play obtain item jingle
    msgbox gText_ReceiveRunningShoes MSG_KEEPOPEN
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

.global PlayerHealNurse
PlayerHealNurse:
    incrementgamestat 15
    call PlayerHeal
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

.global ResetUteyaVillageGymFlagsOnWhiteout
ResetUteyaVillageGymFlagsOnWhiteout:
    checkflag 0x3C
    if SET _goto End
    setflag 0x82F @ Player can run again
    setflag 0x3C @ Hide Copycat again
    return

@ Note: This script clunkily replaces the call to vanilla script located at 0x81A73E0 (called through 0x1A6AA5) for ratings from the PC via ApplyCustomHacks() in make.py
.global PokedexEvaluation_Introduction
PokedexEvaluation_Introduction:
    setvar 0x8004 0x1F
    special 0x17E
    special 0x17D
    setvar 0x8004 0x0
    special2 LASTRESULT 0xD4
    copyvar 0x8008 0x8005
    copyvar 0x8009 0x8006
    setvar 0x800A 390 @ National Dex Count
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
    comparevartovalue 0x8009 0x64 @ 100
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
    comparevartovalue 0x8009 389 @ Full Pokedex - 1
    if lessorequal _goto ThreeHundredFiftyOrMoreCaught
    goto AllCaught

PokedexEvaluation_Conclusion:
    checkflag 0x2FF @ Assessment is from PC
	if SET _call PokedexEvaluation_PCConclusion
    if NOT_SET _call HawthorneInPersonAssessmentComplete
    end

PokedexEvaluation_PCConclusion:
	compare 0x800A 0x0
    if notequal _call PokedexEvaluation_FromPC_PokedexIncomplete
    if equal _call PokedexEvaluation_FromPC_GiftAvailable
    goto 0x81A6AB2 @ Vanilla close link & return to PC script
	return

PokedexEvaluation_FromPC_PokedexIncomplete:
    checkitem ITEM_SHINY_CHARM 0x1
    compare LASTRESULT TRUE
    if TRUE _call PokedexEvaluation_PokedexIncomplete
    checkitem ITEM_SHINY_CHARM 0x1
    compare LASTRESULT FALSE
    if TRUE _call PCShinyCharmAwardCheck
    return

PokedexEvaluation_PokedexIncomplete:
    msgbox gText_PokedexAssessment_IncompletePokedex MSG_KEEPOPEN
    return

PCShinyCharmAwardCheck:
    compare 0x8009 292 @ 3/4 of 390
    if greaterorequal _goto PokedexEvaluation_FromPC_GiftAvailable
    msgbox gText_PokedexAssessment_LessThanSeventyFivePercentPokedex MSG_KEEPOPEN
    return

PokedexEvaluation_FromPC_GiftAvailable:
    msgbox gText_PokedexAssessment_GiftAvailable MSG_KEEPOPEN
    return

HawthorneInPersonAssessmentComplete:
    checkitem ITEM_SHINY_CHARM 0x1
    compare LASTRESULT FALSE
    if TRUE _call ShinyCharmAwardCheck
	compare 0x4001 TRUE
	if TRUE _goto HawthornePresentsDiploma

    compare 0x8009 292 @ 3/4 of 390
    if greaterorequal _call PokedexEvaluation_PokedexIncomplete
    if lessthan _call HawthornePromptForSeventyFivePercentPokedex
	npcchatwithmovement gText_PokedexAssessment_EvaluationComplete m_LookRight
    return

ShinyCharmAwardCheck:
    compare 0x8009 292 @ 3/4 of 390
    if greaterorequal _call GiveShinyCharm
    return

GiveShinyCharm: 
    msgbox gText_PokedexAssessment_ShinyCharmAward MSG_NORMAL
    obtainitem ITEM_SHINY_CHARM 0x1
	msgbox gText_PokedexAssessment_ShinyCharmDescription MSG_NORMAL
    return

HawthornePromptForSeventyFivePercentPokedex:
    msgbox gText_PokedexAssessment_LessThanSeventyFivePercentPokedex MSG_NORMAL
    return

FiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_FiftyOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_FiftyOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

OneHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_OneHundredOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_OneHundredOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

OneHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_OneHundredFiftyOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_OneHundredFiftyOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

TwoHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_TwoHundredOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_TwoHundredOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

TwoHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_TwoHundredFiftyOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_TwoHundredFiftyOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

ThreeHundredOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_ThreeHundredOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_ThreeHundredOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

ThreeHundredFiftyOrLessCaught:
    call PokedexEvaluationFanfare1
    msgbox gText_PokedexAssessment_ThreeHundredFiftyOrLessCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_ThreeHundredFiftyOrLessCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

ThreeHundredFiftyOrMoreCaught:
    call PokedexEvaluationFanfare2
    msgbox gText_PokedexAssessment_ThreeHundredFiftyOrMoreCaught MSG_KEEPOPEN
    waitfanfare
    msgbox gText_PokedexAssessment_AdvicePrompt MSG_NORMAL
    msgbox gText_PokedexAssessment_ThreeHundredFiftyOrMoreCaught_Advice MSG_NORMAL
    goto PokedexEvaluation_Conclusion

AllCaught:
    call PokedexEvaluationFanfare2
    msgbox gText_PokedexAssessment_AllCaught MSG_KEEPOPEN
    waitfanfare
    setvar 0x4001 TRUE
    goto PokedexEvaluation_Conclusion

HawthornePresentsDiploma:
	msgbox gText_PokedexAssessment_EvaluationComplete MSG_NORMAL
    npcchatwithmovement gText_PokedexAssessment_AllCaughtDiploma m_LookRight
    special 0x108 @ Show diploma
    waitstate
    end

PokedexEvaluationFanfare1:
    fanfare 0x13D
    return

PokedexEvaluationFanfare2:
    fanfare 0x103
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
    incrementgamestat 21
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

.global SetCaseyGender
SetCaseyGender:
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _call SetCaseyFemale
    if notequal _call SetCaseyMale
    return

SetCaseyFemale:
    setvar 0x5029 84
    textcolor RED
    return

SetCaseyMale:
    setvar 0x5029 59
    textcolor BLUE
    return

.global BadgeObedienceMessage
BadgeObedienceMessage:
    callasm CountBadges
    switch LASTRESULT
    case 0, NoBadges _call
    case 1, OneBadge _call
    case 2, TwoBadges _call
    case 3, ThreeBadges _call
    case 4, FourBadges _call
    case 5, FiveBadges _call
    case 6, SixBadges _call
    case 7, SevenBadges _call
    case 8, EightBadges _call
    msgbox gText_Common_BadgeObedience MSG_KEEPOPEN
    return

NoBadges:
    buffernumber 0x0 15
    return

OneBadge:
    buffernumber 0x0 25
    return

TwoBadges:
    buffernumber 0x0 35
    return

ThreeBadges:
    buffernumber 0x0 45
    return

FourBadges:
    buffernumber 0x0 55
    return

FiveBadges:
    buffernumber 0x0 65
    return

SixBadges:
    buffernumber 0x0 75
    return

SevenBadges:
    buffernumber 0x0 85
    return

EightBadges:
    buffernumber 0x0 100
    return

.global End
End:
    release
    end

.global DisableTrainerScalingFlag
DisableTrainerScalingFlag:
    clearflag 0x90E @ Disable trainer level scaling
    return

.global SetupMugshotRival
SetupMugshotRival:
    setvar 0x503A 0x2 @ Two small bars with half trainer sprites
    setvar 0x503B 0x0 @ Player picture
    return

.global SetupMugshotGymLeaderAndBosses
SetupMugshotGymLeaderAndBosses:
    setvar 0x503A 0x1 @ One small bar with half trainer sprites
    setvar 0x503B 0x1 @ VS picture
    return

.global SetupMugshotChampionAndTitleDefense
SetupMugshotChampionAndTitleDefense:
    setvar 0x503A 0x0 @ One big bar with full trainer sprite
    setvar 0x503B 0x1 @ VS picture
    return

.global RivalTagBattlePromptAndPartyOrganization
RivalTagBattlePromptAndPartyOrganization:
    signmsg
    msgbox gText_Common_RivalTagBattleExplaination MSG_SIGN
    callasm InitPartyMenuFromField
    pause DELAY_HALFSECOND
    normalmsg
    return

@ This control function disables walking scripts if the player isn't on a map that set temp var 0x400E
@ This should only happen if the player is on an eligible map, but then warps/flies away.
.global DisableWalkingScriptIfOnInvalidMap
DisableWalkingScriptIfOnInvalidMap:
    compare 0x400E 0x1
    if notequal _goto DisableWalkingScript
    return

DisableWalkingScript:
    setvar 0x500B 0x0
    end

.global UltraSpaceWarpEffect
UltraSpaceWarpEffect:
    playse 0x49 @ Escalator
    waitse
    pause DELAY_1SECOND
    playse 0x51 @ Thunder2
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement PLAYER m_HideSprite
    fadescreenspeed FADEIN_WHITE 0x64 @ Slow fade
    return

.global GymLeaderRematch_HandleAllCleared
GymLeaderRematch_HandleAllCleared:
    checkflag 0xE37 @ Terrence
    if NOT_SET _goto End
    checkflag 0xE38 @ Stella
    if NOT_SET _goto End
    checkflag 0xE39 @ Raine
    if NOT_SET _goto End
    checkflag 0xE3A @ Chance
    if NOT_SET _goto End
    checkflag 0xE3B @ Casey
    if NOT_SET _goto End
    checkflag 0xE3C @ Abby
    if NOT_SET _goto End
    checkflag 0xE3D @ Iris
    if NOT_SET _goto End
    checkflag 0xE3E @ Dennis & Dee
    if NOT_SET _goto End
    setflag 0xB7 @ Game modifier for all wilds with hidden abilities
    end

//////////////
// Menu Utils
//////////////

.global EventScript_Common_PocketPC
EventScript_Common_PocketPC:
    playse 0x2 @ Log on
    special 0x3C
    waitstate
    setvar 0x8004 0x0
	release
    playse 0x3 @ Log off
    end

.global EventScript_Common_PokeVial
EventScript_Common_PokeVial:
    msgboxsign
    compare 0x40AE 0x0
    if equal _goto PokeVialNoMoreCharges
    subvar 0x40AE 0x1
    buffernumber 0x0 0x40AE
    playse 0x1 @ Use item
    msgbox gText_Common_PokeVialUsed MSG_NORMAL
    special 0x0
    end

PokeVialNoMoreCharges:
    playse 0x1A @ Error
    msgbox gText_Common_PokeVialNoUsesLeft MSG_NORMAL
    msgboxnormal
    end

.global EventScript_Common_InfiniteRepel
EventScript_Common_InfiniteRepel:
    checkflag 0x93A
    if SET _goto TurnOffInfiniteRepel
    playse 0x29 @ Repel
    msgboxsign
	msgbox gText_Common_InfiniteRepelActivated MSG_SIGN
    msgboxnormal
    setflag 0x93A @ Infinite Repel on
    end

TurnOffInfiniteRepel:
    playse 0x1E @ Unlock
    msgboxsign
	msgbox gText_Common_InfiniteRepelDeactivated MSG_SIGN
    msgboxnormal
    clearflag 0x93A @ Infinite Repel off
    end

////////////
// GAME CUSTOMIZATION
////////////

.global GameCustomizationMain
GameCustomizationMain:
	lock
	setflag 0x056 @ Hide Ena on Route 11 South
	spriteface PLAYER look_down
	setvar 0x4056 0x1 @ Prevent Game Customization level script from running again
	sethealingplace 0x01 @ Player's house
    setflag 0x911 @ Disable wild encounters
	clearflag 0x82F @ Ability to run
	call ShuffleStarterGenerations
    setvar 0x4000 0x0 @ Standard difficulty on
	msgboxsign
	msgbox gText_GameCustomization_CustomizationPrompt MSG_YESNO
	compare LASTRESULT NO
	if equal _goto GameCustomizationComplete
	goto GameCustomizationMenu

ShuffleStarterGenerations:
	random 0x8
	copyvar 0x408C LASTRESULT @ Grass
	random 0x8
	copyvar 0x408D LASTRESULT @ Fire
	random 0x8
	copyvar 0x408E LASTRESULT @ Water
	return

GameCustomizationMenu:
    msgboxsign
    msgbox gText_GameCustomization_CustomizationMenu MSG_KEEPOPEN
	multichoiceoption gText_GameCustomizationMenu_GameMode 0
    multichoiceoption gText_GameCustomizationMenu_Tutorials 1
    multichoiceoption gText_GameCustomizationMenu_StarterSelection 2
    multichoiceoption gText_GameCustomizationMenu_QuickStart 3
    multichoiceoption gText_GameCustomizationMenu_Done 4
    multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, GameCustomization_GameMode _goto
    case 1, GameCustomization_Tutorials _goto
    case 2, GameCustomization_StarterSelection _goto
    case 3, GameCustomization_QuickStart _goto
    // Case n-1 and 0x7F fall through to completion
    goto GameCustomizationComplete

GameCustomizationComplete:
    sound 0x30 @Save
	msgbox gText_GameCustomization_Complete MSG_KEEPOPEN
    compare 0x4000 0x1 @ In casual mode
    if equal _call GiveCasualModeItems
	msgboxnormal
	release
	end

GameCustomization_GameMode:
    msgbox gText_GameCustomization_GameMode_Prompt MSG_KEEPOPEN
    multichoiceoption gText_GameCustomization_GameModeOption_Standard 0
    multichoiceoption gText_GameCustomization_GameModeOption_Casual 1
    multichoice 0x0 0x0 TWO_MULTICHOICE_OPTIONS TRUE
    switch LASTRESULT
    case 0, EnableStandardMode _call
    case 1, EnableCasualMode _call
    goto GameCustomizationMenu

EnableStandardMode:
    setvar 0x4000 0x0
    sound 0x30 @Save
    msgbox gText_GameCustomization_GameMode_StandardSet MSG_NORMAL
    return

EnableCasualMode:
    setvar 0x4000 0x1
    sound 0x30 @Save
    msgbox gText_GameCustomization_GameMode_CasualSet MSG_NORMAL
    return

GiveCasualModeItems:
    additem ITEM_EXP_SHARE 0x1
    additem ITEM_PORTA_PC 0x1
    additem ITEM_POKE_VIAL 0x1
    additem ITEM_INFINITE_REPEL 0x1
    additem ITEM_ADM 0x1
    additem ITEM_MACH_BIKE 0x1
    additem ITEM_ITEMFINDER 0x1
    additem ITEM_POKE_CHIP_CHARM 0x1
    @ Flags for Trainer House rewards
    setflag 0x24F @ For Mach Bike
    setflag 0x252 @ For Item Finder
    setflag 0x277 @ For Poke Chip Charm
    addmoney 2000 @ 5000 total
    setvar 0x4000 0x0 @ Reset control var
    return

GameCustomization_Tutorials:
    msgbox gText_GameCustomization_TutorializationQuestion MSG_YESNO
    compare LASTRESULT NO
    if notequal _call EnableTutorialization
    if equal _call DisableTutorialization
    goto GameCustomizationMenu

EnableTutorialization:
	setflag 0x90A @ Tutorial battles on
	setvar 0x40FF 0x1 @ Catching tutorial cutscene on (+1 in Hawthorne event, triggers map event)
    sound 0x30 @Save
    msgbox gText_GameCustomization_TutorializationTurnedOn MSG_NORMAL
	return

DisableTutorialization:
	clearflag 0x90A @ Tutorial battles off
	setvar 0x40FF 0x0 @ Catching tutorial cutscene on (+1 in Hawthorne event, triggers map event)
    sound 0x30 @Save
    msgbox gText_GameCustomization_TutorializationTurnedOff MSG_NORMAL
	return

GameCustomization_StarterSelection:
    msgbox gText_GameCustomization_StarterGenerationPrompt MSG_KEEPOPEN
    setvar 0x8000 0x5
    setvar 0x8001 0x4
    setvar 0x8004 0x0
	special 0x158
    waitstate
    switch LASTRESULT
	case 0, GameCustomization_GenChoice_Kanto _call
	case 1, GameCustomization_GenChoice_Johto _call
	case 2, GameCustomization_GenChoice_Hoenn _call
	case 3, GameCustomization_GenChoice_Sinnoh _call
	case 4, GameCustomization_GenChoice_Unova _call
	case 5, GameCustomization_GenChoice_Kalos _call
	case 6, GameCustomization_GenChoice_Alola _call
	case 7, GameCustomization_GenChoice_Galar _call
    case 8, GameCustomization_GenChoice_Shuffle _call
    case 0x7F, GameCustomizationMenu _goto
    sound 0x30 @Save
	msgbox gText_GameCustomization_StarterGenerationSaved MSG_KEEPOPEN
    goto GameCustomizationMenu

GameCustomization_GenChoice_Kanto:
	setvar 0x408C 0x0
	setvar 0x408D 0x0
	setvar 0x408E 0x0
    return

GameCustomization_GenChoice_Johto:
	setvar 0x408C 0x1
	setvar 0x408D 0x1
	setvar 0x408E 0x1
    return

GameCustomization_GenChoice_Hoenn:
	setvar 0x408C 0x2
	setvar 0x408D 0x2
	setvar 0x408E 0x2
    return

GameCustomization_GenChoice_Sinnoh:
	setvar 0x408C 0x3
	setvar 0x408D 0x3
	setvar 0x408E 0x3
    return

GameCustomization_GenChoice_Unova:
	setvar 0x408C 0x4
	setvar 0x408D 0x4
	setvar 0x408E 0x4
    return

GameCustomization_GenChoice_Kalos:
	setvar 0x408C 0x5
	setvar 0x408D 0x5
	setvar 0x408E 0x5
    return

GameCustomization_GenChoice_Alola:
	setvar 0x408C 0x6
	setvar 0x408D 0x6
	setvar 0x408E 0x6
    return

GameCustomization_GenChoice_Galar:
	setvar 0x408C 0x7
	setvar 0x408D 0x7
	setvar 0x408E 0x7
    return

GameCustomization_GenChoice_Shuffle:
    call ShuffleStarterGenerations
    return

GameCustomization_QuickStart:
    msgbox gText_GameCustomization_QuickStartQuestion MSG_YESNO
    compare LASTRESULT NO
    if notequal _call EnableQuickStart
    if equal _call DisableQuickStart
    goto GameCustomizationMenu

EnableQuickStart:
    setvar 0x4055 0x5 @ Anthra / Route 17 story events
    additem ITEM_TOWN_MAP 0x1
    setflag 0x82F @ Player can now run
    setflag 0x914 @ Enable auto run
    clearflag 0x02B @ Show the professor, champion, and tv crew
    call SetGameInitializationFlags
    setflag 0x2F @ Hide Rival in Anthra Town (Not cleared in Disable script as it is set by other game initialization scripts)
    sound 0x30 @Save
    msgbox gText_GameCustomization_QuickStartTurnedOn MSG_NORMAL
	return

.global SetGameInitializationFlags
SetGameInitializationFlags:
    setflag 0x02E @ Hide rival in their house
	setflag 0x02F @ Hide rival in Anthra Town overworld
	setflag 0x028 @ Hide grass starter ball on route 17
	setflag 0x029 @ Hide water starter ball on route 17
	setflag 0x02A @ Hide fire starter ball on route 17
    return

DisableQuickStart:
    setvar 0x4055 0x0 @ Anthra / Route 17 story events
    removeitem ITEM_TOWN_MAP 0x1
    clearflag 0x82F @ Player can no longer run
    clearflag 0x914 @ Disable auto run
    setflag 0x02B @ Hide the professor, champion, and tv crew
    sound 0x30 @Save
    msgbox gText_GameCustomization_QuickStartTurnedOff MSG_NORMAL
	return

////////////
// CREDITS
////////////

.global MapScript_Common_Credits
MapScript_Common_Credits:
    mapscript MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE LevelScripts_Credits_OnWarp
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_Credits
    .byte MAP_SCRIPT_TERMIN

LevelScripts_Credits_OnWarp:
    levelscript 0x406F 0x3 LevelScript_Credits_OnWarp_FaceRight
    levelscript 0x406F 0x6 LevelScript_Credits_OnWarp_FaceRight
    levelscript 0x406F 0x8 LevelScript_Credits_OnWarp_MoveMom
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_Credits_OnWarp_FaceRight:
    applymovement PLAYER m_LookRight
    end

@ Need the mom sprite to be close so it is loaded into memory, then moved to the right spot before the screen transitions
LevelScript_Credits_OnWarp_MoveMom:
    movesprite 0x2 0x6 0x7
    end

LevelScripts_Credits:
    levelscript 0x406F 0x2 LevelScript_Credits_1
    levelscript 0x406F 0x3 LevelScript_Credits_2
    levelscript 0x406F 0x4 LevelScript_Credits_3
    levelscript 0x406F 0x5 LevelScript_Credits_4
    levelscript 0x406F 0x6 LevelScript_Credits_5
    levelscript 0x406F 0x7 LevelScript_Credits_6
    levelscript 0x406F 0x8 LevelScript_Credits_7
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_Credits_1:
    msgboxsign
    applymovement PLAYER m_Credits_PlayerWalksOutOfAscensionTower
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    msgbox gText_Common_Credits_EngineAndGameplay MSG_NORMAL
    applymovement PLAYER m_Credits_PlayerLeavesDaimynCity
    msgbox gText_Common_Credits_LookAndFeel_1 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    applymovement PLAYER m_Credits_PlayerLeavesDaimynCity2
    msgbox gText_Common_Credits_LookAndFeel_2 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    pause DELAY_1SECOND
    applymovement PLAYER m_Credits_PlayerWalkDownFadeout
    pause DELAY_1SECOND
    addvar 0x406F 0x1
    warpmuted 31 1 0
    waitstate
    end

LevelScript_Credits_2:
    msgboxsign
    applymovement 0x1 m_Credits_DittoRunAway
    applymovement 0x2 m_Credits_DittoNerdRunAway
    applymovement PLAYER m_Credits_PlayerWalks_ToRoute6Nurse
    msgbox gText_Common_Credits_OWGraphics_1 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    applymovement 0x3 m_Joy
    pause DELAY_1SECOND
    applymovement PLAYER m_Credits_PlayerWalks_ToFisherman
    msgbox gText_Common_Credits_OWGraphics_2 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    pause DELAY_HALFSECOND
    applymovement 0x4 m_LookLeft
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookUp
    applymovement 0x4 m_LookUp
    waitmovement 0x5
    applymovement PLAYER m_Surprise
    applymovement 0x4 m_Surprise
    pause DELAY_1SECOND
    applymovement 0x4 m_LookLeft
    applymovement PLAYER m_LookRight
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    applymovement 0x4 m_Wrong
    pause DELAY_1SECOND
    applymovement 0x4 m_LookUp
    applymovement PLAYER m_Credits_PlayerWalks_ToFlyingCoolTrainer
    msgbox gText_Common_Credits_OWGraphics_3 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    pause DELAY_HALFSECOND
    applymovement 0x5 m_LookDown
    pause DELAY_HALFSECOND
    setfieldeffectarg 0, 0x27 @ Cooltrainer X
	setfieldeffectarg 1, 0x10 @ Cooltrainer Y
	dofieldeffect 30 @FLDEFF_NPCFLY_OUT
    pause 0x3 @ Delay just long enough for the bird to connect with the cooltrainer
    applymovement 0x5 m_Credits_CoolTrainer_JumpsOntoBird
	waitfieldeffect 30 @FLDEFF_NPCFLY_OUT
    waitmovement 0x5
    pause DELAY_HALFSECOND
    applymovement PLAYER m_Credits_PlayerWalkDownFadeout
    pause DELAY_1SECOND
    addvar 0x406F 0x1
    warpmuted 31 7 0
    waitstate
    end

LevelScript_Credits_3:
    msgboxsign
    applymovement PLAYER m_Credits_PlayerWalksToGroup
    msgbox gText_Common_Credits_GameplayFeatures1 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    applymovement 0x1 m_Joy
    applymovement 0x2 m_Joy
    applymovement 0x3 m_Joy
    pause DELAY_1SECOND
    applymovement 0x1 m_Credits_GateBoyRuns
    applymovement 0x2 m_Credits_GateBugCatcherRuns
    applymovement 0x3 m_Credits_GateGirlRuns
    waitmovement 0x3
    pause DELAY_1SECOND
    applymovement PLAYER m_Credits_PlayerWalksToUpsetGirl
    msgbox gText_Common_Credits_GameplayFeatures2 MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    pause DELAY_HALFSECOND
    applymovement 0x4 m_Wrong
    waitmovement 0x4
    pause DELAY_HALFSECOND
    applymovement 0x4 m_Credits_UpsetGirlWalksAway
    applymovement 0x5 m_Surprise
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    applymovement 0x5 m_Credits_UpsetGirlsBoyfriendFollows
    waitmovement 0x5
    closeonkeypress
    pause DELAY_1SECOND
    applymovement PLAYER m_Credits_PlayerWalkDownFadeout
    pause DELAY_1SECOND
    addvar 0x406F 0x1
    warpmuted 31 3 0
    waitstate
    end

LevelScript_Credits_4:
    msgboxsign
    applymovement PLAYER m_Credits_PlayerWalksPastBlackBelt
    applymovement 0x3 m_Credits_HikerWalksAcrossBridge
    msgbox gText_Common_Credits_BattleBackgrounds MSG_KEEPOPEN
    waitmovement PLAYER
    closeonkeypress
    pause DELAY_1SECOND
    applymovement 0x2 m_Credits_BlackbeltJumpsDown
    waitmovement 0x2
    pause DELAY_HALFSECOND
    applymovement 0x1 m_LookLeft
    applymovement 0x2 m_LookRight
    pause DELAY_HALFSECOND
    applymovement PLAYER m_Credits_PlayerWalkRightFadeout
    pause DELAY_1SECOND
    addvar 0x406F 0x1
    warpmuted 31 8 0
    waitstate
    end

LevelScript_Credits_5:
    msgboxsign
    applymovement PLAYER m_Credits_PlayerWalksToPikachuKid
    msgbox gText_Common_Credits_BattleSprites MSG_KEEPOPEN
    waitmovement PLAYER
    pause DELAY_HALFSECOND
    applymovement 0x1 m_Credits_PikachuAndKidLeave
    applymovement 0x2 m_Credits_PikachuAndKidLeave
    pause DELAY_1SECOND
    closeonkeypress
    applymovement PLAYER m_Credits_PlayerWalksToRival
    applymovement 0x3 m_Credits_RivalWalksToPlayer
    waitmovement 0x3
    pause DELAY_HALFSECOND
    applymovement PLAYER m_Surprise
    applymovement 0x3 m_Surprise
    waitmovement 0x3
    pause DELAY_1SECOND
    applymovement PLAYER m_WalkDown
    applymovement 0x3 m_WalkUp
    waitmovement 0x3
    applymovement 0x3 m_Joy
    pause DELAY_1SECOND
    pause DELAY_HALFSECOND
    applymovement 0x3 m_Credits_PlayerRunsDownFadeout
    applymovement PLAYER m_Credits_PlayerRunsDownFadeout
    pause DELAY_1SECOND
    addvar 0x406F 0x1
    warpmuted 31 9 0
    waitstate
    end

LevelScript_Credits_6:
    msgboxsign
    applymovement 0x1 m_Credits_RivalRunsThroughForest
    applymovement PLAYER m_Credits_PlayerRunsThroughForest
    msgbox gText_Common_Credits_Tools MSG_KEEPOPEN
    pause DELAY_1SECOND
    applymovement 0x1 m_Credits_PlayerRunsLeftFadeout
    applymovement PLAYER m_Credits_PlayerRunsLeftFadeout
    pause DELAY_HALFSECOND
    addvar 0x406F 0x1
    warpmuted 31 6 0
    waitstate
    end

LevelScript_Credits_7:
    msgboxsign
    applymovement 0x1 m_Credits_RivalWalksToSeparationPoint
    applymovement PLAYER m_Credits_PlayerWalksToSeparationPoint
    msgbox gText_Common_Credits_SpecialThanks MSG_KEEPOPEN
    waitmovement PLAYER
    applymovement PLAYER m_LookRight
    applymovement 0x1 m_LookLeft
    waitmovement 0x1
    pause DELAY_HALFSECOND
    closeonkeypress
    applymovement 0x1 m_Credits_RivalReturnsHome
    applymovement PLAYER m_Credits_PlayerReturnsHome
    waitmovement PLAYER
    pause DELAY_1SECOND
    applymovement PLAYER m_Joy
    applymovement 0x2 m_Joy
    pause DELAY_1SECOND
    applymovement 0x2 m_LookUp
    waitmovement 0x2
    opendoor 0x6 0x6
    waitdooranim
    applymovement 0x2 m_Credits_MomGoesInside
    pause DELAY_HALFSECOND
    applymovement PLAYER m_LookRight
    pause DELAY_HALFSECOND
    applymovement PLAYER m_Credits_PlayerGoesInside
    waitmovement PLAYER
    closedoor 0x6 0x6
    waitdooranim
    fadescreenspeed FADEOUT_BLACK 0x64 @ Slow fade
    msgboxnormal
    msgbox gText_Common_Credits_PlayerReturnsHome MSG_NORMAL
    pause DELAY_1SECOND
    callasm DoSoftReset
    waitstate
    end

m_Credits_PlayerWalkDownFadeout: .byte walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, end_m
m_Credits_PlayerWalkRightFadeout: .byte walk_right_very_slow, walk_right_very_slow, walk_right_very_slow, walk_right_very_slow, walk_right_very_slow, end_m
m_Credits_PlayerRunsDownFadeout: .byte run_down, run_down, run_down, run_down, run_down, run_down, run_down, run_down, run_down, run_down, end_m
m_Credits_PlayerRunsLeftFadeout: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
// First Scene (Daimyn City)
m_Credits_PlayerWalksOutOfAscensionTower: .byte walk_down_slow, walk_down_slow, look_up, end_m
m_Credits_PlayerLeavesDaimynCity: .byte walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, look_right, end_m
m_Credits_PlayerLeavesDaimynCity2: .byte walk_left_very_slow, walk_left_very_slow, walk_left_very_slow, walk_left_very_slow, walk_left_very_slow, walk_down_very_slow, walk_down_very_slow, walk_down_very_slow, look_left, end_m
// Second Scene (Route 6)
m_Credits_DittoRunAway: .byte run_right, run_right, run_right, run_right, run_right, run_up, run_up, run_up, run_up, run_up, run_up, run_up,  end_m
m_Credits_DittoNerdRunAway: .byte run_right, run_right, run_right, run_right, run_right, run_right, run_up, run_up, run_up, run_up, run_up, run_up, run_up,  end_m
m_Credits_PlayerWalks_ToRoute6Nurse: .byte walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_right_slow, walk_right_slow, walk_right_slow, look_up, end_m
m_Credits_PlayerWalks_ToFisherman: .byte walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, look_right, end_m
m_Credits_PlayerWalks_ToFlyingCoolTrainer: .byte walk_down_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_down_slow, walk_down_slow, walk_down_slow, look_right, end_m
m_Credits_CoolTrainer_JumpsOntoBird: .byte jump_onspot_down, set_invisible, end_m
// Third Scene (Heleo City)
m_Credits_PlayerWalksToGroup: .byte walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, look_left, end_m
m_Credits_GateBoyRuns: .byte run_left, set_invisible, end_m
m_Credits_GateBugCatcherRuns: .byte run_down, run_left, run_left, set_invisible, end_m
m_Credits_GateGirlRuns: .byte pause_long, run_left, run_left, run_left, set_invisible, end_m
m_Credits_PlayerWalksToUpsetGirl: .byte walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, look_right, end_m
m_Credits_UpsetGirlWalksAway: .byte walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_right, set_invisible, end_m
m_Credits_UpsetGirlsBoyfriendFollows: .byte run_up, run_up, run_up, run_up, run_right, run_right, run_right, run_right, set_invisible, end_m
// Fourth Scene (Route 7)
m_Credits_PlayerWalksPastBlackBelt: .byte walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_down_slow, walk_right_slow, walk_right_slow, walk_down_slow, walk_down_slow, walk_right_slow, walk_right_slow, walk_right_slow, look_up, end_m
m_Credits_HikerWalksAcrossBridge: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_Credits_BlackbeltJumpsDown: .byte look_left, pause_short, look_right, pause_short, look_down, pause_long, pause_long, slide_down, jump_2_down, end_m
// Fifth Scene (Rhodanzi City)
m_Credits_PlayerWalksToPikachuKid: .byte walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, look_right, end_m
m_Credits_PikachuAndKidLeave: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_Credits_PlayerWalksToRival: .byte walk_down_slow, walk_down_slow, look_down, end_m
m_Credits_RivalWalksToPlayer: .byte walk_up_slow, walk_up_slow, look_up, end_m
// Sixth Scene (Varisi Forest)
m_Credits_RivalRunsThroughForest: .byte run_down, jump_2_down, run_down, run_down, run_down, run_down, run_down, run_down, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_up, run_up, run_up, run_up, run_up, run_up, run_up, run_up, run_up, run_left, look_right, end_m
m_Credits_PlayerRunsThroughForest: .byte run_down, run_down, jump_2_down, run_down, run_down, run_down, run_down, run_down, run_down, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_up, run_up, run_up, run_up, run_up, run_up, run_up, run_up, run_up, look_left, end_m
// Seventh Scene (Anthra Town)
m_Credits_PlayerWalksToSeparationPoint: .byte walk_down_slow, walk_down_slow, walk_down_slow, look_right, end_m
m_Credits_RivalWalksToSeparationPoint: .byte walk_down_slow, walk_down_slow, walk_down_slow, look_left, end_m
m_Credits_RivalReturnsHome: .byte walk_down_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_right_slow, look_up, end_m
m_Credits_PlayerReturnsHome: .byte walk_left_slow, walk_left_slow, walk_left_slow, walk_left_slow, walk_left_slow, walk_left_slow, look_up, end_m
m_Credits_MomGoesInside: .byte walk_up, set_invisible, end_m
m_Credits_PlayerGoesInside: .byte walk_up, walk_up, set_invisible, end_m
