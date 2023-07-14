.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ RestaurantChipsTotalVar, 0x4091
.equ RestaurantMoneyTotalVar, 0x4092
.equ RestaurantChipsNextVar, 0x4093
.equ RestaurantMoneyNextVar, 0x4094
.equ RestaurantBuffBattlesDuration, 0x4095
.equ MealPartySlot1Var, 0x5001
.equ MealPartySlot2Var, 0x5003
.equ MathNum1Var, 0x4001
.equ MathNum2Var, 0x4002
.equ StatBuffTypeVar, 0x4003
.equ StatBuffLevelVar, 0x4004
.equ MealLevelChosen, 0x4005

.global EventScript_DaimynRestaurant_Chef
EventScript_DaimynRestaurant_Chef:
    checkflag 0x250 @ Restaurant has been explained
    if NOT_SET _call FirstRestaurantVisit
    msgbox gText_Restaurant_Intro MSG_KEEPOPEN
    goto RestaurantOptions

FirstRestaurantVisit:
    msgbox gText_Restaurant_FirstVisit MSG_NORMAL
    setvar RestaurantChipsNextVar 0x1 @ 0x19 @ 25
    setvar RestaurantChipsTotalVar 0x0
    setvar RestaurantMoneyNextVar 0x1388 @ 5000
    setvar RestaurantMoneyTotalVar 0x0
    call RestaurantExplaination
    return

@ TODOs:
@   Investigate a message when the effect wears off
@   Implement sound effects and fanfares
@   Implement remaining meals and cleanup
@   Test
@   Reset test donation costs

RestaurantOptions:
    multichoiceoption gText_Restaurant_OptionOrder 0
    multichoiceoption gText_Restaurant_OptionProgress 1
	multichoiceoption gText_Restaurant_OptionDonate 2
	multichoiceoption gText_Restaurant_OptionExplaination 3
	multichoiceoption gText_Restaurant_OptionEnd 4
	multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
	case 0, RestaurantMenu
    case 1, RestaurantProgress
	case 2, RestaurantDonate
	case 3, RestaurantExplaination
	case 4, RestaurantEnd
    goto RestaurantEnd

RestaurantMenu:
    compare RestaurantBuffBattlesDuration 0x0
    if greaterthan _call PromptForCurrentMealReplacement
    setvar 0x8001 0x6 @ Show 6 menu items
    setvar 0x8004 0x0 @ Ensure multiselect doesn't blow up when reopened
    msgbox gText_Restaurant_MenuPresented MSG_KEEPOPEN
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _goto MenuWithAll
    goto MenuStandard

MenuStandard:
    setvar 0x8000 0x2 @ Standard Menu
    special 0x158
    waitstate
    switch LASTRESULT
	case 0, MealChoiceAttack
	@ case 1, MealChoiceDefense
	@ case 2, MealChoiceSpAttack
	@ case 3, MealChoiceSpDefense
    @ case 4, MealChoiceSpeed
	@ case 5, MealChoiceAccuracy
	@ case 6, MealChoiceEvasion
	@ case 7, RestaurantChoseNo
    case 0x7F, RestaurantChoseNo @ When player hit B to close
    goto FinishMeal

MenuWithAll:
    setvar 0x8000 0x3 @ Menu with All Food
    special 0x158
    waitstate
    switch LASTRESULT
    case 0, MealChoiceAttack
	@ case 1, MealChoiceDefense
	@ case 2, MealChoiceSpAttack
	@ case 3, MealChoiceSpDefense
    @ case 4, MealChoiceSpeed
	@ case 5, MealChoiceAccuracy
	@ case 6, MealChoiceEvasion
    @ case 7, MealChoiceAll
	@ case 8, RestaurantChoseNo
    case 0x7F, RestaurantChoseNo @ When player hit B to close
    goto FinishMeal

MealChoiceAttack:
    msgbox gText_Restaurant_AttackMealDesc MSG_NORMAL
    setvar MathNum1Var 0x96 @ 150, base cost
    setvar StatBuffTypeVar 0x1 @ Attack stat buff
    call HandleMealLevelChoice
    compare MealLevelChosen 0x3 @ Chose Level 3
    if equal _call DecreaseDefense
    return

DecreaseDefense:
    setvar StatBuffTypeVar 0x2 @ Defense stat debuff
    call SetStatDebuffVariables
    return

HandleMealLevelChoice:
    call SetupLevelOneMeal @ Default level 1
    compare RestaurantChipsTotalVar 0x1 @ 0x19 @ 25
    if greaterorequal _call PromptForTwoLevels
    call CalculateAndPresentMealCost
    return

SetupLevelOneMeal:
    setvar MathNum2Var 0xA @ Cost multiplier (10x)
    setvar StatBuffLevelVar 0x10 @ 1 stage
    setvar MealLevelChosen 0x1
    buffernumber 0x1 0x1
    return

SetupLevelTwoMeal:
    setvar MathNum2Var 0x14 @ Cost multiplier (20x)
    setvar StatBuffLevelVar 0x20 @ 2 stages
    setvar MealLevelChosen 0x2
    buffernumber 0x1 0x2
    return

SetupLevelThreeMeal:
    setvar MathNum2Var 0x1E @ Cost multiplier (30x)
    setvar StatBuffLevelVar 0x30 @ 3 stages
    setvar MealLevelChosen 0x3
    buffernumber 0x1 0x3
    return

PromptForTwoLevels:
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _goto PromptForThreeLevels
    msgbox gText_Restaurant_MenuLevelPrompt MSG_KEEPOPEN
    multichoiceoption gText_Level1 0
    multichoiceoption gText_Level2 1
	multichoiceoption gText_ChangeMind 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, SetupLevelOneMeal
    case 1, SetupLevelTwoMeal
	case 2, EventScript_DaimynRestaurant_Chef
    return

PromptForThreeLevels:
    msgbox gText_Restaurant_MenuLevelPrompt MSG_KEEPOPEN
    multichoiceoption gText_Level1 0
    multichoiceoption gText_Level2 1
    multichoiceoption gText_Level3 2
	multichoiceoption gText_ChangeMind 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
	switch LASTRESULT
	case 0, SetupLevelOneMeal
    case 1, SetupLevelTwoMeal
    case 2, SetupLevelThreeMeal
	case 3, EventScript_DaimynRestaurant_Chef
    return

CalculateAndPresentMealCost:
    setvar 0x8004 MathNum1Var
    setvar 0x8005 MathNum2Var
    special2 LASTRESULT 0x40 @ Calculate the meal cost as (level * base), ie (20 * 150). Result gets stored in first var, so MathNum1Var
    showmoney 0x0 0x0
    buffernumber 0x2 MathNum1Var @ Have to buffer after showing money, or else BUFFER1 becomes the player's total money...
    msgbox gText_Restaurant_MealLevelAndCostPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RestaurantChoseNo
    copyvar 0x8004 MathNum1Var
    callasm CheckMoneyFromVar @ Checks if player has enough money based on var 0x8004 value
    compare LASTRESULT TRUE
    if notequal _goto NotEnoughMoney
    playse 0xF8 @ Money
    callasm RemoveMoneyFromVar @ Removes based on var 0x8004 value
    updatemoney 0x0 0x0
    waitse
    pause DELAY_1SECOND
    hidemoney
    msgbox gText_Restaurant_PaidForMeal MSG_NORMAL
    call HandlePurchase
    call HandleDuration
    call SetMealStatBuffVariables
    return

HandlePurchase:
    copyvar MathNum1Var 0x8004
    setvar 0x8004 RestaurantMoneyTotalVar
    setvar 0x8005 MathNum1Var
    special 0x3E @ Add two vars above, result stored in RestaurantMoneyTotalVar
    comparevars RestaurantMoneyTotalVar RestaurantMoneyNextVar
    if greaterorequal _call MoneyAboveNextThreshold
    return

MoneyAboveNextThreshold:
    @ Return if there are no more payment tiers TODO: This likely doesn't work!!
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

SetMealStatBuffVariables:
    setvar MealPartySlot1Var 0x0 @ Reset in case a meal is currently active
    setvar MealPartySlot2Var 0x0 @ Apply to slot 2 & reset
    copyvar MathNum1Var StatBuffTypeVar
    copyvar MathNum2Var StatBuffLevelVar
    setvar 0x8004 MathNum1Var
    setvar 0x8005 MathNum2Var
    special 0x3E @ Add two vars above, result stored in MathNum1Var
    copyvar MealPartySlot1Var MathNum1Var
    copyvar MealPartySlot2Var MathNum1Var
    return

SetStatDebuffVariables:
    setvar MealPartySlot2Var 0x0 @ Apply to slot 2 & reset
    setvar StatBuffLevelVar 0x90 @ Decrease by 1 stage
    copyvar MathNum1Var StatBuffTypeVar
    copyvar MathNum2Var StatBuffLevelVar
    setvar 0x8004 MathNum1Var
    setvar 0x8005 MathNum2Var
    special 0x3E @ Add two vars above, result stored in MathNum1Var
    copyvar MealPartySlot2Var MathNum1Var
    return

@ MealLevel12:
@     msgbox gText_Restaurant_MenuLevelPrompt MSG_KEEPOPEN
@     multichoiceoption gText_Level1 0
@     multichoiceoption gText_Level2 1
@ 	multichoiceoption gText_ChangeMind 2
@ 	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
@ 	switch LASTRESULT
@ 	case 0, SetLevelOneMeal
@     case 1, SetLevelTwoMeal
@ 	case 2, EventScript_DaimynRestaurant_Chef
@     return

@ MealLevel123:
@     msgbox gText_Restaurant_MenuLevelPrompt MSG_KEEPOPEN
@     multichoiceoption gText_Level1 0
@     multichoiceoption gText_Level2 1
@     multichoiceoption gText_Level3 2
@ 	multichoiceoption gText_ChangeMind 3
@ 	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
@ 	switch LASTRESULT
@ 	case 0, SetLevelOneMeal
@     case 1, SetLevelTwoMeal
@     case 2, SetLevelThreeMeal
@ 	case 3, EventScript_DaimynRestaurant_Chef
@     return

@ SetLevelOneMeal:
@     addvar MealPartySlot1Var 0x10 @ 1 stage
@     addvar MealPartySlot2Var 0x10 @ 1 stage
@     setvar MathNum2Var 0xA @ Cost multiplier (10x)
@     return

@ SetLevelTwoMeal:
@     addvar MealPartySlot1Var 0x20 @ 2 stages
@     addvar MealPartySlot2Var 0x20 @ 2 stages
@     setvar MathNum2Var 0x14 @ Cost multiplier (20x)
@     return

@ SetLevelThreeMeal:
@     addvar MealPartySlot1Var 0x30 @ 3 stages
@     addvar MealPartySlot2Var 0x30 @ 3 stages
@     setvar MathNum2Var 0x1E @ Cost multiplier (30x)
@     return

@ MealChoiceAttack:
@     msgbox gText_Restaurant_AttackMealDesc MSG_NORMAL
@     setvar MathNum1Var 0x96 @ 150, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x1 @ Attack Stat
@     addvar MealPartySlot2Var 0x1 @ Attack Stat
@     return

@ MealChoiceDefense:
@     msgbox gText_Restaurant_DefenseMealDesc MSG_NORMAL
@     setvar MathNum1Var 0x96 @ 150, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x2 @ Defense Stat
@     addvar MealPartySlot2Var 0x2 @ Defense Stat
@     return

@ MealChoiceSpAttack:
@     msgbox gText_Restaurant_SpAttackMealDesc MSG_NORMAL
@     setvar MathNum1Var 0x96 @ 150, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x3 @ Special Attack Stat
@     addvar MealPartySlot2Var 0x3 @ Special Attack Stat
@     return

@ MealChoiceSpDefense:
@     msgbox gText_Restaurant_SpDefenseMealDesc MSG_NORMAL
@     setvar MathNum1Var 0x96 @ 150, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x4 @ Special Defense Stat
@     addvar MealPartySlot2Var 0x4 @ Special Defense Stat
@     return

@ MealChoiceSpeed:
@     msgbox gText_Restaurant_SpeedMealDesc MSG_NORMAL
@     setvar MathNum1Var 0x96 @ 150, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x5 @ Speed Stat
@     addvar MealPartySlot2Var 0x5 @ Speed Stat
@     return

@ MealChoiceAccuracy:
@     msgbox gText_Restaurant_AccuracyMealDesc MSG_NORMAL
@     setvar MathNum1Var 0xC8 @ 200, base cost
@     call HandleMealLevelChoice
@     addvar MealPartySlot1Var 0x6 @ Accuracy Stat
@     addvar MealPartySlot2Var 0x6 @ Accuracy Stat
@     return

@ MealChoiceEvasion:
@     setvar MathNum1Var 0xC8 @ 200, base cost
@     call InitializeMeal
@     compare RestaurantChipsTotalVar 0x1 @ 0x19 @ 25
@     if greaterorequal _call MealLevel12
@     call HandleMealConfirmationMessage
@     addvar MealPartySlot1Var 0x7 @ Evasion Stat
@     addvar MealPartySlot2Var 0x7 @ Evasion Stat
@     return

@ MealChoiceAll:
@     setvar MathNum1Var 0x3E8 @ 1000, base cost
@     call InitializeMeal
@     call HandleMealConfirmationMessage
@     setvar MealPartySlot1Var 0xFFFF @ All stats
@     setvar MealPartySlot2Var 0xFFFF @ All stats
@     return

@ InitializeMeal:
@     setvar MealPartySlot1Var 0x0 @ Reset in case a meal is currently active
@     setvar MealPartySlot2Var 0x0 @ Reset in case a meal is currently active
@     call SetLevelOneMeal
@     return

@ HandleMealLevelChoice:
@     compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
@     if equal _call MealLevel123
@     if notequal _call HandleMeal12Confirmation
@     call HandleMealConfirmationMessage
@     return

@ HandleMealConfirmationMessage:
@     compare RestaurantBuffBattlesDuration 0x0
@     if greaterthan _call PromptForCurrentMealReplacement
@     setvar 0x8004 MathNum1Var
@     setvar 0x8005 MathNum2Var
@     special2 LASTRESULT 0x40 @ Calculate the meal cost as (level * base), ie (20 * 150). Result gets stored in first var, so MathNum1Var
@     showmoney 0x0 0x0
@     buffernumber 0x0 MathNum1Var @ Have to buffer after showing money, or else BUFFER1 becomes the player's total money...
@     msgbox gText_Restaurant_MealConfirm MSG_YESNO
@     compare LASTRESULT NO
@     if equal _goto RestaurantChoseNo
@     copyvar 0x8004 MathNum1Var
@     callasm CheckMoneyFromVar @ Checks if player has enough money based on var 0x8004 value
@     compare LASTRESULT TRUE
@     if notequal _goto NotEnoughMoney
@     playse 0xF8 @ Money
@     callasm RemoveMoneyFromVar @ Removes based on var 0x8004 value
@     updatemoney 0x0 0x0
@     waitse
@     pause DELAY_1SECOND
@     hidemoney
@     msgbox gText_Restaurant_PaidForMeal MSG_NORMAL
@     call InitializeMeal
@     call HandleMoneyTotal
@     call HandleDuration
@     return

PromptForCurrentMealReplacement:
    msgbox gText_Restaurant_MealReplacement MSG_YESNO
    compare LASTRESULT NO
    if equal _goto gText_Restaurant_ChoseNo
    return

@ HandleMeal12Confirmation:
@     compare RestaurantChipsTotalVar 0x1 @ 0x19 @ 25
@     if equal _call MealLevel12
@     return

NotEnoughMoney:
    msgbox gText_Restaurant_NotEnoughMoney MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

@ HandleMoneyTotal:
@     copyvar MathNum1Var 0x8004
@     setvar 0x8004 RestaurantMoneyTotalVar
@     setvar 0x8005 MathNum1Var
@     special 0x3E @ Add two vars above, result stored in RestaurantMoneyTotalVar
@     comparevars RestaurantMoneyTotalVar RestaurantMoneyNextVar
@     if greaterorequal _goto MoneyAboveNextThreshold
@     return

@ MoneyAboveNextThreshold:
@     @ Return if money is above 0
@     compare RestaurantMoneyNextVar 0x0
@     if equal _goto Return

@     compare RestaurantMoneyTotalVar 0xC350 @ 50,000
@     if greaterorequal _goto MoneyAboveFinalThreshold
@     compare RestaurantMoneyTotalVar 0x7530 @ 30,000
@     if greaterorequal _goto MoneyAboveThirdThreshold
@     compare RestaurantMoneyTotalVar 0x3A98 @ 15,000
@     if greaterorequal _goto MoneyAboveSecondThreshold
@     compare RestaurantMoneyTotalVar 0x1388 @ 5,000
@     if greaterorequal _goto MoneyAboveFirstThreshold
@     return

MoneyAboveFinalThreshold:
    setvar RestaurantMoneyNextVar 0x0 @ Set to 0, no next
    fanfare 0x102
    msgbox gText_Restaurant_IngredientsFinalLevelUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveThirdThreshold:
    setvar RestaurantMoneyNextVar 0xC350 @ 50,000
    buffernumber 0x0 0x4
    buffernumber 0x1 0x5
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_Restaurant_IngredientsNextUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveSecondThreshold:
    setvar RestaurantMoneyNextVar 0x7530 @ 30,000
    buffernumber 0x0 0x3
    buffernumber 0x1 0x4
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_Restaurant_IngredientsNextUnlocked MSG_NORMAL
    waitfanfare
    return

MoneyAboveFirstThreshold:
    setvar RestaurantMoneyNextVar 0x3A98 @ 15,000
    buffernumber 0x0 0x2
    buffernumber 0x1 0x3
    buffernumber 0x2 RestaurantMoneyNextVar
    fanfare 0x102
    msgbox gText_Restaurant_IngredientsNextUnlocked MSG_NORMAL
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
    setvar RestaurantBuffBattlesDuration 0x1
    buffernumber 0x0 0x1
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1Var
    msgbox gText_Restaurant_DurationNotMax MSG_NORMAL
    return

Duration2:
    setvar RestaurantBuffBattlesDuration 0x2
    buffernumber 0x0 0x2
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1Var
    msgbox gText_Restaurant_DurationNotMax MSG_NORMAL
    return

Duration3:
    setvar RestaurantBuffBattlesDuration 0x3
    buffernumber 0x0 0x3
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1Var
    msgbox gText_Restaurant_DurationNotMax MSG_NORMAL
    return

Duration4:
    setvar RestaurantBuffBattlesDuration 0x4
    buffernumber 0x0 0x4
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1Var
    msgbox gText_Restaurant_DurationNotMax MSG_NORMAL
    return

Duration5:
    setvar RestaurantBuffBattlesDuration 0x5
    buffernumber 0x0 0x5
    msgbox gText_Restaurant_DurationAtMax MSG_NORMAL
    return

CalculateMoneyRemaining:
    compare RestaurantMoneyTotalVar 0x0
    if equal _goto NoMoneySpentYet
    copyvar MathNum1Var RestaurantMoneyNextVar @ Copy, so we don't overwrite the real total during calculation
    setvar 0x8004 MathNum1Var
    setvar 0x8005 RestaurantMoneyTotalVar
    special2 LASTRESULT 0x3F @ Subtract 2 numbers above, result stored in LASTRESULT
    return

NoMoneySpentYet:
    copyvar MathNum1Var RestaurantMoneyNextVar
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
    goto EventScript_DaimynRestaurant_Chef

DisplayNoChipsLeft:
    msgbox gText_Restaurant_DonationComplete MSG_NORMAL
    return

DisplayChipsLeft:
    msgbox gText_Restaurant_ChipsDonated MSG_NORMAL
    return

DisplayNoMoneyLeft:
    msgbox gText_Restaurant_MoneyRemaining MSG_NORMAL
    return

DisplayMoneyLeft:
    call CalculateMoneyRemaining
    buffernumber 0x1 MathNum1Var
    msgbox gText_Restaurant_MoneySpent MSG_NORMAL
    return

FinishMeal:
    msgbox gText_Restaurant_MealConclusion MSG_NORMAL
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
    msgbox gText_Restaurant_ChipsDonated MSG_NORMAL
    msgbox gText_Restaurant_DonationRequirement MSG_YESNO
    compare LASTRESULT NO
    if equal _goto RestaurantChoseNo
    msgbox gText_Restaurant_DonationRequest MSG_NORMAL
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
    msgbox gText_Restaurant_DonationLevel2Unlocked MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

RestaurantNoPokeChips:
    msgbox gText_Restaurant_DonationNoPokeChips MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

ChoseTooManyChips:
    msgbox gText_Restaurant_DonationTooManyPokeChips MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

ChoseMoreChipsThanNeeded:
    msgbox gText_Restaurant_DonationMorePokeChipsThanNeeded MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

RestaurantDonationMet:
    fanfare 0x102
    msgbox gText_Restaurant_DonationMet MSG_KEEPOPEN
    waitfanfare
    setvar RestaurantChipsNextVar 0x1 @ 0x32 @ 50 more
    compare RestaurantChipsTotalVar 0x2 @ 0x32 @ 50
    if equal _call SetChipsComplete
    return

SetChipsComplete:
    setvar RestaurantChipsNextVar 0x0 @ 0 more
    fanfare 0x102
    msgbox gText_Restaurant_DonationLevel3Unlocked MSG_KEEPOPEN
    waitfanfare
    return

DonationComplete:
    msgbox gText_Restaurant_DonationComplete MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

RestaurantExplaination:
    msgbox gText_Restaurant_Explaination MSG_NORMAL
    setflag 0x250 @ Restaurant has been explained
    goto EventScript_DaimynRestaurant_Chef

RestaurantChoseNo:
    msgbox gText_Restaurant_ChoseNo MSG_NORMAL
    goto EventScript_DaimynRestaurant_Chef

RestaurantEnd:
    msgbox gText_Restaurant_End MSG_NORMAL
    setvar 0x8004 0x0 @ Ensure multiselect doesn't blow up when reopened
    release
    end

Return:
    return
