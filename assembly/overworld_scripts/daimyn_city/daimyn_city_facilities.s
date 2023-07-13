.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4054
.equ FlagHideRival, 0x03C
.equ SpriteRival, 0x2
.equ RestaurantChipsTotalVar, 0x4091
.equ RestaurantMoneyTotalVar, 0x4092
.equ RestaurantChipsNextVar, 0x4093
.equ RestaurantMoneyNextVar, 0x4094
.equ RestaurantBuffBattlesDuration, 0x4095
.equ MealPartySlot1Var, 0x5001
.equ MealPartySlot2Var, 0x5003
.equ MealDurationVar, 0x4095
.equ MathNum1, 0x4001
.equ MathNum2, 0x4002

.global EventScript_DaimynCity_GuardHouseWest_Guard
EventScript_DaimynCity_GuardHouseWest_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseWest_Guard MSG_NORMAL
    end

.global EventScript_DaimynCity_GuardHouseSouth_Guard
EventScript_DaimynCity_GuardHouseSouth_Guard:
    msgbox gText_DaimynCityFacilities_GuardHouseSouth_Guard MSG_NORMAL
    end

.global TileScript_DaimynCity_GuardHouseWest_TriggerRival
TileScript_DaimynCity_GuardHouseWest_TriggerRival:
    lock
    call RivalBattleCommon_Intro
    applymovement PLAYER m_WalkLeft
    applymovement SpriteRival m_RivalMeetsPlayer_West
    waitmovement ALLEVENTS
    call RivalBattleCommon
    applymovement PLAYER m_PlayerMovesOutOfWay_West
    waitmovement ALLEVENTS
    applymovement SpriteRival m_RivalLeaves_West
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    setflag FlagHideRival
    applymovement PLAYER m_PlayerLeavesWithRival_West
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    @ TODO: Warp and continue event in Daimyn City
    release
    end

.global TileScript_DaimynCity_GuardHouseSouth_TriggerRival
TileScript_DaimynCity_GuardHouseSouth_TriggerRival:
    lock
    call RivalBattleCommon_Intro
    applymovement PLAYER m_WalkDown
    applymovement SpriteRival m_RivalMeetsPlayer_South
    waitmovement ALLEVENTS
    call RivalBattleCommon
    applymovement PLAYER m_PlayerMovesOutOfWay_South
    waitmovement ALLEVENTS
    applymovement SpriteRival m_RivalLeaves_South
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    setflag FlagHideRival
    applymovement PLAYER m_PlayerLeavesWithRival_South
    waitmovement ALLEVENTS
    playse 0x8 @ door open
    @ TODO: Warp and continue event in Daimyn City
    release
    end

RivalBattleCommon_Intro:
    clearflag FlagHideRival
    showsprite SpriteRival
    playbgm 0x195
    applymovement PLAYER m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalIntroduction MSG_NORMAL
    return

RivalBattleCommon:
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalExplainsDaimynCity MSG_NORMAL
    applymovement SpriteRival m_Surprise
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalInitiatesBattle MSG_NORMAL
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    trainerbattle3 0x0 0x88 0x100 gText_DaimynCityFacilities_GuardHouse_RivalLoses
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalConcludesBattle MSG_NORMAL
    applymovement SpriteRival m_Surprise
    waitmovement ALLEVENTS
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalNoItems MSG_NORMAL
    pause DELAY_HALFSECOND
    msgbox gText_DaimynCityFacilities_GuardHouse_RivalOffersTourOfDaimynCity MSG_NORMAL
    setvar StoryEventVar 0x1 @ Prevent from happening again in either guard house
    return

.global EventScript_DaimynCityFacilities_RestaurauntBoy
EventScript_DaimynCityFacilities_RestaurauntBoy:
    npcchat gText_DaimynCityOverworld_RestaurantBoy
    end

.global EventScript_DaimynCityFacilities_RestaurauntBigMan
EventScript_DaimynCityFacilities_RestaurauntBigMan:
    lock
    faceplayer
    checkflag 0x24D @ Got leftovers
    If SET _goto LeftoversDescription
    msgbox gText_DaimynCityOverworld_RestaurantBigMan MSG_NORMAL
    obtainitem ITEM_LEFTOVERS 0x1
    setflag 0x24D @ Got Leftovers
    goto LeftoversDescription

LeftoversDescription:
    msgbox gText_DaimynCityOverworld_RestaurantBigMan_LeftoversDescription MSG_NORMAL
    release
    end

.global EventScript_DaimynCityFacilities_RestaurauntGentleman
EventScript_DaimynCityFacilities_RestaurauntGentleman:
    msgbox gText_DaimynCityOverworld_RestaurantGentleman MSG_NORMAL
    end

.global EventScript_DaimynCityFacilities_RestaurauntGirl
EventScript_DaimynCityFacilities_RestaurauntGirl:
    npcchat gText_DaimynCityOverworld_RestaurantGirl
    end

.global EventScript_DaimynCityFacilities_RestaurauntChef
EventScript_DaimynCityFacilities_RestaurauntChef:
    checkflag 0x250 @ Restaurant has been explained
    setvar 0x8004 0x0 @ Ensure multiselect doesn't blow up when reopened
    if NOT_SET _call FirstRestaurantVisit
    msgbox gText_DaimynCityOverworld_RestaurantChef_Intro MSG_KEEPOPEN
    goto RestaurantOptions

FirstRestaurantVisit:
    msgbox gText_DaimynCityOverworld_RestaurantChef_FirstVisit MSG_NORMAL
    setvar RestaurantChipsNextVar 0x1 @ 0x19 @ 25
    setvar RestaurantChipsTotalVar 0x0
    setvar RestaurantMoneyNextVar 0x1388 @ 5000
    setvar RestaurantMoneyTotalVar 0x0
    call RestaurantExplaination
    return

@ TODOs:
@   Fix graphical bugs with menu
@   Investigate how to prevent "doubles" aura message from appearing in singles battle (ie. ignore var 5003 if not in double battle)
@   Investigate a message when the effect wears off
@   Investigate changing the string used when it activates
@   Implement sound effects and fanfares
@   Move all logic to dedicated .s and .string files
@   Test
@   Reset test donation costs

RestaurantOptions:
    multichoiceoption gText_DaimynCityOverworld_RestaurantChef_OptionOrder 0
    multichoiceoption gText_DaimynCityOverworld_RestaurantChef_OptionProgress 1
	multichoiceoption gText_DaimynCityOverworld_RestaurantChef_OptionDonate 2
	multichoiceoption gText_DaimynCityOverworld_RestaurantChef_OptionExplaination 3
	multichoiceoption gText_DaimynCityOverworld_RestaurantChef_OptionEnd 4
	multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
	case 0, RestaurantMenu
    case 1, RestaurantProgress
	case 2, RestaurantDonate
	case 3, RestaurantExplaination
	case 4, RestaurantEnd
    goto RestaurantEnd

RestaurantMenu:
    setvar 0x8001 0x6 @ Show 6 menu items
    setvar 0x8004 0x0 @ Ensure multiselect doesn't blow up when reopened  TODO: Is this the key???? Setting to 1 has the menu work as desired, but it loads the wrong table.
    @ setvar MealPartySlot1Var 0x0 @ Apply totem buff to Player party slot 1
    @ setvar MealPartySlot2Var 0x2 @ Apply totem buff to Player party slot 2 (in doubles)
    msgbox gText_DaimynCityOverworld_RestaurantChef_MenuPresented MSG_KEEPOPEN
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _goto MenuWithAll
    goto MenuStandard

MenuStandard:
    setvar 0x8000 0x2 @ Standard Menu
    special 0x158
    waitstate
    switch LASTRESULT
	case 0, MealChoiceAttack
	case 1, MealChoiceDefense
	case 2, MealChoiceSpAttack
	case 3, MealChoiceSpDefense
    case 4, MealChoiceSpeed
	case 5, MealChoiceAccuracy
	case 6, MealChoiceEvasion
	case 7, RestaurantChoseNo
    case 0x7F, RestaurantChoseNo @ When player hit B to close
    goto FinishMeal

MenuWithAll:
    setvar 0x8000 0x3 @ Menu with All Food
    special 0x158
    waitstate
    switch LASTRESULT
    case 0, MealChoiceAttack
	case 1, MealChoiceDefense
	case 2, MealChoiceSpAttack
	case 3, MealChoiceSpDefense
    case 4, MealChoiceSpeed
	case 5, MealChoiceAccuracy
	case 6, MealChoiceEvasion
    case 7, MealChoiceAll
	case 8, RestaurantChoseNo
    case 0x7F, RestaurantChoseNo @ When player hit B to close
    goto FinishMeal

MealLevel12:
    multichoiceoption gText_Level1 0
    multichoiceoption gText_Level2 1
	multichoiceoption gText_ChangeMind 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, SetLevelOneMeal
    case 1, SetLevelTwoMeal
	case 2, EventScript_DaimynCityFacilities_RestaurauntChef
    return

MealLevel123:
    multichoiceoption gText_Level1 0
    multichoiceoption gText_Level2 1
    multichoiceoption gText_Level3 2
	multichoiceoption gText_ChangeMind 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, SetLevelOneMeal
    case 1, SetLevelTwoMeal
    case 2, SetLevelThreeMeal
	case 3, EventScript_DaimynCityFacilities_RestaurauntChef
    return

SetLevelOneMeal:
    addvar MealPartySlot1Var 0x10 @ 1 stage
    addvar MealPartySlot2Var 0x10 @ 1 stage
    setvar MathNum2 0xA @ Cost multiplier (10x)
    return

SetLevelTwoMeal:
    addvar MealPartySlot1Var 0x20 @ 2 stages
    addvar MealPartySlot2Var 0x20 @ 2 stages
    setvar MathNum2 0x14 @ Cost multiplier (20x)
    return

SetLevelThreeMeal:
    addvar MealPartySlot1Var 0x30 @ 3 stages
    addvar MealPartySlot2Var 0x30 @ 3 stages
    setvar MathNum2 0x1E @ Cost multiplier (30x)
    return

MealChoiceAttack:
    msgbox gText_DaimynCityOverworld_RestaurantChef_AttackMealDesc MSG_NORMAL
    setvar MathNum1 0x96 @ 150, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x1 @ Attack Stat
    addvar MealPartySlot2Var 0x1 @ Attack Stat
    return

MealChoiceDefense:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DefenseMealDesc MSG_NORMAL
    setvar MathNum1 0x96 @ 150, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x2 @ Defense Stat
    addvar MealPartySlot2Var 0x2 @ Defense Stat
    return

MealChoiceSpAttack:
    msgbox gText_DaimynCityOverworld_RestaurantChef_SpAttackMealDesc MSG_NORMAL
    setvar MathNum1 0x96 @ 150, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x3 @ Special Attack Stat
    addvar MealPartySlot2Var 0x3 @ Special Attack Stat
    return

MealChoiceSpDefense:
    msgbox gText_DaimynCityOverworld_RestaurantChef_SpDefenseMealDesc MSG_NORMAL
    setvar MathNum1 0x96 @ 150, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x4 @ Special Defense Stat
    addvar MealPartySlot2Var 0x4 @ Special Defense Stat
    return

MealChoiceSpeed:
    msgbox gText_DaimynCityOverworld_RestaurantChef_SpeedMealDesc MSG_NORMAL
    setvar MathNum1 0x96 @ 150, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x5 @ Speed Stat
    addvar MealPartySlot2Var 0x5 @ Speed Stat
    return

MealChoiceAccuracy:
    msgbox gText_DaimynCityOverworld_RestaurantChef_AccuracyMealDesc MSG_NORMAL
    setvar MathNum1 0xC8 @ 200, base cost
    call HandleMealLevelChoice
    addvar MealPartySlot1Var 0x6 @ Accuracy Stat
    addvar MealPartySlot2Var 0x6 @ Accuracy Stat
    return

MealChoiceEvasion:
    setvar MathNum1 0xC8 @ 200, base cost
    call SetLevelOneMeal @ Default
    compare RestaurantChipsTotalVar 0x1 @ 0x19 @ 25
    if greaterorequal _call MealLevel12
    call HandleMealConfirmationMessage
    addvar MealPartySlot1Var 0x7 @ Evasion Stat
    addvar MealPartySlot2Var 0x7 @ Evasion Stat
    return

MealChoiceAll:
    setvar MathNum1 0x3EB @ 1000, base cost
    call SetLevelOneMeal
    call HandleMealConfirmationMessage
    setvar MealPartySlot1Var 0xFFFF @ All stats
    setvar MealPartySlot2Var 0xFFFF @ All stats
    return

HandleMealLevelChoice:
    call SetLevelOneMeal @ Default
    call HandleMealConfirmationMessage
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _call MealLevel123
    if notequal _call HandleMeal12Confirmation
    return

HandleMealConfirmationMessage:
    compare MealDurationVar 0x0
    if greaterthan _call PromptForCurrentMealReplacement
    setvar 0x8004 MathNum1
    setvar 0x8005 MathNum2
    special2 LASTRESULT 0x40 @ Calculate the meal cost as (level * base), ie (20 * 150). Result gets stored in first var, so MathNum1
    showmoney 0x0 0x0
    buffernumber 0x0 MathNum1 @ Have to buffer after showing money, or else BUFFER1 becomes the player's total money...
    msgbox gText_DaimynCityOverworld_RestaurantChef_MealConfirm MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RestaurantChoseNo
    copyvar 0x8004 MathNum1
    callasm CheckMoneyFromVar @ Checks if player has enough money based on var 0x8004 value
    compare LASTRESULT TRUE
    if notequal _goto NotEnoughMoney
    playse 0xF8 @ Money
    callasm RemoveMoneyFromVar @ Removes based on var 0x8004 value
    updatemoney 0x0 0x0
    waitse
    pause DELAY_1SECOND
    hidemoney
    msgbox gText_DaimynCityOverworld_RestaurantChef_PaidForMeal MSG_NORMAL
    call HandleMoneyTotal
    call HandleDuration
    return

PromptForCurrentMealReplacement:
    msgbox gText_DaimynCityOverworld_RestaurantChef_MealReplacement MSG_NORMAL
    return

HandleMeal12Confirmation:
    compare RestaurantChipsTotalVar 0x1 @ 0x19 @ 25
    if equal _call MealLevel12
    return

NotEnoughMoney:
    msgbox gText_DaimynCityOverworld_RestaurantChef_NotEnoughMoney MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

HandleMoneyTotal:
    copyvar MathNum1 0x8004
    setvar 0x8004 RestaurantMoneyTotalVar
    setvar 0x8005 MathNum1
    special 0x3E @ Add two vars above, result stored in RestaurantMoneyTotalVar
    comparevars RestaurantMoneyTotalVar RestaurantMoneyNextVar
    if greaterorequal _goto MoneyAboveNextThreshold
    return

MoneyAboveNextThreshold:
    @ Return if money is above 0
    compare RestaurantMoneyNextVar 0x0
    if equal _goto Return

    compare RestaurantMoneyTotalVar 0xC350 @ 50,000
    if greaterorequal _goto MoneyAboveFinalThreshold
    compare RestaurantMoneyTotalVar 0x7530 @ 30,000
    if greaterorequal _goto MoneyAboveThirdThreshold
    compare RestaurantMoneyTotalVar 0x3A98 @ 15,000
    if greaterorequal _goto MoneyAboveSecondThreshold
    compare RestaurantMoneyTotalVar 0x1388 @ 5,000
    if greaterorequal _goto MoneyAboveFirstThreshold
    return

MoneyAboveFinalThreshold:
    setvar RestaurantMoneyNextVar 0x0 @ Set to 0, no next
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_IngredientsFinalLevelUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveThirdThreshold:
    setvar RestaurantMoneyNextVar 0xC350 @ 50,000
    buffernumber 0x0 0x4
    buffernumber 0x1 0x5
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_IngredientsNextUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveSecondThreshold:
    setvar RestaurantMoneyNextVar 0x7530 @ 30,000
    buffernumber 0x0 0x3
    buffernumber 0x1 0x4
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_IngredientsNextUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveFirstThreshold:
    setvar RestaurantMoneyNextVar 0x3A98 @ 15,000
    buffernumber 0x0 0x2
    buffernumber 0x1 0x3
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_IngredientsNextUnlocked MSG_NORMAL
    waitfanfare
    return

HandleDuration:
    compare RestaurantMoneyTotalVar 0xC350 @ 50,000
    if greaterorequal _goto Duration5
    compare RestaurantMoneyTotalVar 0x7530 @ 30,000
    if greaterorequal _goto Duration4
    compare RestaurantMoneyTotalVar 0x3A98 @ 15,000
    if greaterorequal _goto Duration3
    compare RestaurantMoneyTotalVar 0x1388 @ 5,000
    if greaterorequal _goto Duration2
    goto Duration1

Duration1:
    setvar MealDurationVar 0x1
    buffernumber 0x0 0x1
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1
    msgbox gText_DaimynCityOverworld_RestaurantChef_DurationNotMax MSG_NORMAL
    return

Duration2:
    setvar MealDurationVar 0x2
    buffernumber 0x0 0x2
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1
    msgbox gText_DaimynCityOverworld_RestaurantChef_DurationNotMax MSG_NORMAL
    return

Duration3:
    setvar MealDurationVar 0x3
    buffernumber 0x0 0x3
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1
    msgbox gText_DaimynCityOverworld_RestaurantChef_DurationNotMax MSG_NORMAL
    return

Duration4:
    setvar MealDurationVar 0x4
    buffernumber 0x0 0x4
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1
    msgbox gText_DaimynCityOverworld_RestaurantChef_DurationNotMax MSG_NORMAL
    return

Duration5:
    setvar MealDurationVar 0x5
    buffernumber 0x0 0x5
    msgbox gText_DaimynCityOverworld_RestaurantChef_DurationAtMax MSG_NORMAL
    return

CalculateMoneyRemaining:
    compare RestaurantMoneyTotalVar 0x0
    if equal _goto NoMoneySpentYet
    copyvar MathNum1 RestaurantMoneyNextVar @ Copy, so we don't overwrite the real total during calculation
    setvar 0x8004 MathNum1
    setvar 0x8005 RestaurantMoneyTotalVar
    special2 LASTRESULT 0x3F @ Subtract 2 numbers above, result stored in LASTRESULT
    return

NoMoneySpentYet:
    copyvar MathNum1 RestaurantMoneyNextVar
    return

RestaurantProgress:
    buffernumber 0x0 RestaurantChipsTotalVar
    buffernumber 0x1 RestaurantChipsNextVar
    compare RestaurantChipsNextVar 0x0
    if equal _call DisplayNoChipsLeft
    if greaterthan _call DisplayChipsLeft
    buffernumber 0x0 RestaurantMoneyTotalVar
    compare RestaurantMoneyNextVar 0x0
    if equal _call DisplayNoMoneyLeft
    if greaterthan _call DisplayMoneyLeft
    goto EventScript_DaimynCityFacilities_RestaurauntChef

DisplayNoChipsLeft:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationComplete MSG_NORMAL
    return

DisplayChipsLeft:
    msgbox gText_DaimynCityOverworld_RestaurantChef_ChipsDonated MSG_NORMAL
    return

DisplayNoMoneyLeft:
    msgbox gText_DaimynCityOverworld_RestaurantChef_MoneyRemaining MSG_NORMAL
    return

DisplayMoneyLeft:
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1
    msgbox gText_DaimynCityOverworld_RestaurantChef_MoneySpent MSG_NORMAL
    return

FinishMeal:
    msgbox gText_DaimynCityOverworld_RestaurantChef_MealConclusion MSG_NORMAL
    release
    end

RestaurantDonate:
    compare RestaurantChipsNextVar 0x0 @ Remaining set to 0 when there are no more tiers
    if equal _goto DonationComplete
    buffernumber 0x0 RestaurantChipsTotalVar
    buffernumber 0x1 RestaurantChipsNextVar
    callasm StorePokeChipCount
    compare 0x8005 0x0
    if equal _goto RestaurantNoPokeChips
	buffernumber 0x2 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynCityOverworld_RestaurantChef_ChipsDonated MSG_NORMAL
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationRequirement MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RestaurantChoseNo
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationRequest MSG_NORMAL
    special 0xB3 @ Choose number, stored in LASTRESULT
    waitstate
    compare LASTRESULT 0x0
    if equal _goto RestaurantChoseNo
    comparevars LASTRESULT 0x8005
    if greaterthan _goto ChoseTooManyChips
    comparevars LASTRESULT RestaurantChipsNextVar
    if greaterthan _goto ChoseMoreChipsThanNeeded
    removeitem ITEM_POKE_CHIP LASTRESULT
    setvar 0x8004 RestaurantChipsTotalVar
    setvar 0x8005 LASTRESULT
    special 0x3E @ Add two vars above
    setvar 0x8004 RestaurantChipsNextVar
    setvar 0x8005 LASTRESULT
    special 0x3F @ Subtract two vars above
    compare RestaurantChipsNextVar 0x0
    if equal _call RestaurantDonationMet
    compare RestaurantChipsNextVar 0x0
    if equal _goto DonationComplete
    buffernumber 0x1 RestaurantChipsNextVar
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationLevel2Unlocked MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

RestaurantNoPokeChips:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationNoPokeChips MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

ChoseTooManyChips:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationTooManyPokeChips MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

ChoseMoreChipsThanNeeded:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationMorePokeChipsThanNeeded MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

RestaurantDonationMet:
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationMet MSG_KEEPOPEN
    waitfanfare
    setvar RestaurantChipsNextVar 0x1 @ 0x32 @ 50 more
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _call SetChipsComplete
    return

SetChipsComplete:
    setvar RestaurantChipsNextVar 0x0 @ 0 more
    fanfare 0x102
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationLevel3Unlocked MSG_KEEPOPEN
    waitfanfare
    return

DonationComplete:
    msgbox gText_DaimynCityOverworld_RestaurantChef_DonationComplete MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

RestaurantExplaination:
    msgbox gText_DaimynCityOverworld_RestaurantChef_Explaination MSG_NORMAL
    setflag 0x250 @ Restaurant has been explained
    goto EventScript_DaimynCityFacilities_RestaurauntChef

RestaurantChoseNo:
    msgbox gText_DaimynCityOverworld_RestaurantChef_ChoseNo MSG_NORMAL
    goto EventScript_DaimynCityFacilities_RestaurauntChef

RestaurantEnd:
    msgbox gText_DaimynCityOverworld_RestaurantChef_End MSG_NORMAL
    setvar 0x8004 0x0 @ Ensure multiselect doesn't blow up when reopened
    release
    end

Return:
    return

m_RivalMeetsPlayer_West: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_RivalMeetsPlayer_South: .byte walk_up, walk_up, walk_up, walk_up, end_m
m_PlayerMovesOutOfWay_West: .byte walk_up, look_down, end_m
m_PlayerMovesOutOfWay_South: .byte walk_right, look_left, end_m
m_RivalLeaves_West: .byte walk_right, walk_right, walk_right, set_invisible, end_m
m_RivalLeaves_South: .byte walk_up, walk_up, walk_up, set_invisible, end_m
m_PlayerLeavesWithRival_West: .byte walk_down, walk_right, walk_right, end_m
m_PlayerLeavesWithRival_South: .byte walk_left, walk_up, walk_up, end_m
