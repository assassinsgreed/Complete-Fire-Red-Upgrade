.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_LaplazNPCHouses_Monty
EventScript_LaplazNPCHouses_Monty:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto MontyCaseyNotMet
    msgbox gText_LaplazTownNPCHouses_MontyMetWithCasey MSG_NORMAL
    end

MontyCaseyNotMet:
    msgbox gText_LaplazTownNPCHouses_MontyHaventMetWithCasey MSG_NORMAL
    end

.global EventScript_LaplazNPCHouses_CaseysMom
EventScript_LaplazNPCHouses_CaseysMom:
    checkflag 0x03F @ Casey hidden in gym
    if SET _goto CaseysMomCaseyNotMet
    checkgender
    compare LASTRESULT 0x0 @ Gender is opposite of player
    if equal _goto FemaleCaseyWillLeadGym
    if notequal _goto MaleCaseyWillLeadGym

CaseysMomCaseyNotMet:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomHaventMetWithCasey m_LookRight
    end

FemaleCaseyWillLeadGym:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomMetWithCasey_Female m_LookRight
    end

MaleCaseyWillLeadGym:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysMomMetWithCasey_Male m_LookRight
    end

.global EventScript_LaplazNPCHouses_CaseysGrandmother
EventScript_LaplazNPCHouses_CaseysGrandmother:
    npcchatwithmovement gText_LaplazTownNPCHouses_CaseysGrandmother m_LookRight
    end

.global EventScript_LaplazNPCHouses_HeracrossKid
EventScript_LaplazNPCHouses_HeracrossKid:
    lock
    faceplayer
    msgbox gText_LaplazTownNPCHouses_HeracrossKid MSG_NORMAL
    showpokepic SPECIES_HERACROSS
    msgbox gText_LaplazTownNPCHouses_HeracrossKidDuringPic MSG_NORMAL
    hidepokepic
    msgbox gText_LaplazTownNPCHouses_HeracrossKidAfterPic MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_LaplazNPCHouses_HeracrossKidsSister
EventScript_LaplazNPCHouses_HeracrossKidsSister:
    npcchatwithmovement gText_LaplazTownNPCHouses_HeracrossKidsSister m_LookLeft
    end

.global EventScript_LaplazNPCHouses_ApricornGrandma
EventScript_LaplazNPCHouses_ApricornGrandma:
    npcchatwithmovement gText_LaplazTownNPCHouses_ApricornGrandma m_LookRight
    end

.global EventScript_LaplazNPCHouses_ApricornGrandpa
EventScript_LaplazNPCHouses_ApricornGrandpa:
    npcchatwithmovement gText_LaplazTownNPCHouses_ApricornGrandpa m_LookLeft
    end

.global EventScript_LaplazNPCHouses_MeasurementsGirl
EventScript_LaplazNPCHouses_MeasurementsGirl:
    lock
    faceplayer
    checkflag 0xE11 @ Daily measurement game flag
    if SET _goto MeasurementGameOver
    checkflag 0xE12 @ Daily measurement game flag 
    if NOT_SET _call SetDailyMeasurementSpecies
    setvar 0x8005 0x4001 @ Store measurements in var 4001 (temp var)
    copyvar 0x8006 0x40ED @ Copy the daily species into var 8006
    special 0x75 @ Buffer the species and it's average size
    msgbox gText_LaplazTownNPCHouses_MeasurementGameIntro MSG_NORMAL
    msgbox gText_LaplazTownNPCHouses_MeasurementGameRequest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto MeasurementGameNotPlaying
    msgbox gText_LaplazTownNPCHouses_MeasurementGameChoseYes MSG_NORMAL
    special 0x9F @ Choose a Pokemon
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto MeasurementGameNotPlaying
    special 0x148 @ Check if egg
    compare LASTRESULT 0x1
    if equal _goto CannotMeasureEggs
    special2 LASTRESULT 0x76 @ Measure the Pokemon
    compare LASTRESULT 0x1
    if equal _goto MeasurementGameIncorrectSpecies
    buffernumber 0x1 0x8005
    compare LASTRESULT 0x2
    if equal _goto MeasurementGameSmaller
    compare LASTRESULT 0x3
    if equal _goto MeasurementGameLarger
    compare LASTRESULT 0x4
    if equal _goto MeasurementGameEqual
    end

SetDailyMeasurementSpecies:
    random 0x11F @ up to #287 to avoid exposing starters and legendaries, stored in LastResult
    @ copyvar 0x40ED LASTRESULT @ Store, to recall later today if needed
    setvar 0x40ED 1143 @ Debug value
    callasm GetLuckyPokmeonSpecies @ Reuse the Lucky Pokemon assembly, to only pull from pokemon in the regional pokedex
    setflag 0xE12 @ Daily species chosen
    return

MeasurementGameOver:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameDone MSG_NORMAL
    goto ResetMeasurementsGirlPosition

MeasurementGameNotPlaying:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameChoseNo MSG_NORMAL
    goto ResetMeasurementsGirlPosition

CannotMeasureEggs:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameChoseEgg MSG_NORMAL
    goto ResetMeasurementsGirlPosition

MeasurementGameIncorrectSpecies:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameChoseWrongSpecies MSG_NORMAL
    goto ResetMeasurementsGirlPosition

MeasurementGameSmaller:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameSmaller MSG_NORMAL
    obtainitem ITEM_TINY_MUSHROOM 0x3
    goto MeasurementGameWon

MeasurementGameLarger:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameBigger MSG_NORMAL
    obtainitem ITEM_BIG_MUSHROOM 0x3
    goto MeasurementGameWon

MeasurementGameEqual:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameEqual MSG_NORMAL
    obtainitem ITEM_NUGGET 0x1
    goto MeasurementGameWon

MeasurementGameWon:
    msgbox gText_LaplazTownNPCHouses_MeasurementGameWon MSG_NORMAL
    setflag 0xE11 @ Daily measurement game flag
    goto ResetMeasurementsGirlPosition

ResetMeasurementsGirlPosition:
    applymovement LASTTALKED m_LookRight
    release
    end
