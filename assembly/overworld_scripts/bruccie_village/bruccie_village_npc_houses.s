.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_BruccieVillageNPCHouses_MoveTutor
EventScript_BruccieVillageNPCHouses_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BruccieVillageNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 10
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_BruccieVillageNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Bruccie
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookUp
    end

TutoringComplete:
    msgbox gText_BruccieVillageNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_BruccieVillageNPCHouses_TutoringRejected m_LookUp
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_BruccieVillageNPCHouses_NotEnoughPokeChips m_LookUp
    goto End

.global EventScript_BruccieVillageNPCHouses_PokeballSwapper
EventScript_BruccieVillageNPCHouses_PokeballSwapper:
    faceplayer
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Intro MSG_NORMAL
    compare 0x409A 5
    if lessthan _call NotSkilled
    if greaterorequal _call Skilled
    @ Get pokechip count and confirm
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChangeBall
    compare 0x8005 0x2
    if lessthan _goto NotEnoughPokeChipsForBallSwap
    goto ChoosePokemon

ChoosePokemon:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_AskToChoosePokemon MSG_NORMAL
    special 0x9F
    waitstate
    copyvar 0x4001 0x8004
    compare 0x4001 0x6 @ Don't continue if user backed out
    if greaterorequal _goto ChoseNotToChangeBall
    bufferpartypokemon 0x0 0x8004 @ Buffer pokemon nickname
    setvar 0x8003 0x0 @ Read pokeball from party
    special2 0x4000 0xB
    addvar 0x4000 0x1 @ Add 1 - This vanilla special reads the ball in a 0 based format instead of 1 based (#0 is None)
    compare 0x4000 ITEM_CHERISH_BALL
    if equal _goto CannotChangeCherishBall
    bufferitem 0x1 0x4000
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokemonChoiceConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoosePokemon
    goto ChoosePokeball

ChoosePokeball:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokeballConfirmation MSG_NORMAL
    setvar 0x8000 0x2 @ Choose from Pokeball menu
    fadescreen FADEOUT_BLACK @ Fade screen to circumvent a UI bug when opening the bag
    special 0xB1
    waitstate
    compare CHOSEN_ITEM 0x0
    if equal _goto ChoseNotToChangeBall
    @ Handle same ball chosen
    comparevars 0x4000 CHOSEN_ITEM @ Original ball compared to new
    if equal _goto ChoseSamePokeball
    @ Setup ball swapping special based on selected item
    switch CHOSEN_ITEM
    case ITEM_MASTER_BALL, ChoseMasterBall
    case ITEM_ULTRA_BALL, ChoseUltraBall
    case ITEM_GREAT_BALL, ChoseGreatBall
    case ITEM_POKE_BALL, ChosePokeBall
    case ITEM_SAFARI_BALL, ChoseSafariBall
    case ITEM_NET_BALL, ChoseNetBall
    case ITEM_DIVE_BALL, ChoseDiveBall
    case ITEM_NEST_BALL, ChoseNestBall
    case ITEM_REPEAT_BALL, ChoseRepeatBall
    case ITEM_TIMER_BALL, ChoseTimerBall
    case ITEM_LUXURY_BALL, ChoseLuxuryBall
    case ITEM_PREMIER_BALL, ChosePremierBall
    case ITEM_DUSK_BALL, ChoseDuskBall
    case ITEM_HEAL_BALL, ChoseHealBall
    case ITEM_QUICK_BALL, ChoseQuickBall
    case ITEM_PARK_BALL, ChoseParkBall
    case ITEM_FAST_BALL, ChoseFastBall
    case ITEM_LEVEL_BALL, ChoseLevelBall
    case ITEM_LURE_BALL, ChoseLureBall
    case ITEM_HEAVY_BALL, ChoseHeavyBall
    case ITEM_LOVE_BALL, ChoseLoveBall
    case ITEM_FRIEND_BALL, ChoseFriendBall
    case ITEM_MOON_BALL, ChoseMoonBall
    case ITEM_SPORT_BALL, ChoseSportBall
    case ITEM_BEAST_BALL, ChoseBestBall
    case ITEM_DREAM_BALL, ChoseDreamBall
    @ For all non-pokeball items, as well as Dynamax and Cherish balls, default to not being able to process it
    bufferitem 0x0 CHOSEN_ITEM
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseANonPokeball m_LookLeft
    end

@ These balls come from catching.h's ball types
ChoseMasterBall:
    setvar 0x8005 0x0
    goto BallConfirmation

ChoseUltraBall:
    setvar 0x8005 0x1
    goto BallConfirmation

ChoseGreatBall:
    setvar 0x8005 0x2
    goto BallConfirmation

ChosePokeBall:
    setvar 0x8005 0x3
    goto BallConfirmation

ChoseSafariBall:
    setvar 0x8005 0x4
    goto BallConfirmation

ChoseNetBall:
    setvar 0x8005 0x5
    goto BallConfirmation

ChoseDiveBall:
    setvar 0x8005 0x6
    goto BallConfirmation

ChoseNestBall:
    setvar 0x8005 0x7
    goto BallConfirmation

ChoseRepeatBall:
    setvar 0x8005 0x8
    goto BallConfirmation

ChoseTimerBall:
    setvar 0x8005 0x9
    goto BallConfirmation

ChoseLuxuryBall:
    setvar 0x8005 0xA
    goto BallConfirmation

ChosePremierBall:
    setvar 0x8005 0xB
    goto BallConfirmation

ChoseDuskBall:
    setvar 0x8005 0xC
    goto BallConfirmation

ChoseHealBall:
    setvar 0x8005 0xD
    goto BallConfirmation

ChoseQuickBall:
    setvar 0x8005 0xE
    goto BallConfirmation

ChoseParkBall:
    setvar 0x8005 0x10
    goto BallConfirmation

ChoseFastBall:
    setvar 0x8005 0x11
    goto BallConfirmation

ChoseLevelBall:
    setvar 0x8005 0x12
    goto BallConfirmation

ChoseLureBall:
    setvar 0x8005 0x13
    goto BallConfirmation

ChoseHeavyBall:
    setvar 0x8005 0x14
    goto BallConfirmation

ChoseLoveBall:
    setvar 0x8005 0x15
    goto BallConfirmation

ChoseFriendBall:
    setvar 0x8005 0x16
    goto BallConfirmation

ChoseMoonBall:
    setvar 0x8005 0x17
    goto BallConfirmation

ChoseSportBall:
    setvar 0x8005 0x18
    goto BallConfirmation

ChoseBestBall:
    setvar 0x8005 0x19
    goto BallConfirmation

ChoseDreamBall:
    setvar 0x8005 0x1A
    goto BallConfirmation

BallConfirmation:
    @ Handle confirmation
    bufferpartypokemon 0x0 0x8004 @ Buffer pokemon nickname again; replaced by special 0xB1
    bufferitem 0x2 CHOSEN_ITEM
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_BallSwapConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToChangeBall
    goto PerformBallSwap

PerformBallSwap:
    @ Deduct pokechips and process
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_CollectPokechips MSG_NORMAL
    sound 0xF8 @ Money SE
    waitse
    removeitem ITEM_POKE_CHIP 0x2
    removeitem CHOSEN_ITEM 0x1
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_StartingProcess MSG_NORMAL
    fadescreen FADEOUT_BLACK
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Working MSG_NORMAL
    fadescreen FADEIN_BLACK
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_ProcessComplete MSG_KEEPOPEN
    waitfanfare
    @ Change ball
    special 0x14 @ Perform the ball change
    addvar 0x409A 0x1
    @ Give old ball back if skilled enough
    compare 0x409A 5
    if lessthan _call BrokeBall
    if equal _call BecameSkilled
    if greaterorequal _call GiveOldBall
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_Completed m_LookLeft
    end

NotSkilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_NotSkilled MSG_NORMAL
    return

Skilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Skilled MSG_NORMAL
    return

ChoseNotToChangeBall:
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseNotToChangePokeball m_LookLeft
    end

NotEnoughPokeChipsForBallSwap:
    npcchatwithmovement gText_BruccieVillageNPCHouses_PokeballSwapper_NotEnoughChips m_LookLeft
    end

CannotChangeCherishBall:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_PokemonInCherishBall MSG_NORMAL
    goto ChoseNotToChangeBall

ChoseSamePokeball:
    bufferitem 0x0 CHOSEN_ITEM
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_ChoseSamePokeball MSG_NORMAL
    goto ChoseNotToChangeBall

BrokeBall:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_OldBallBroke MSG_NORMAL
    return

BecameSkilled:
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_Improved MSG_NORMAL
    return

GiveOldBall:
    additem 0x4000 0x1
    bufferitem 0x1 0x4000
    msgbox gText_BruccieVillageNPCHouses_PokeballSwapper_BallReturned MSG_NORMAL
    return
