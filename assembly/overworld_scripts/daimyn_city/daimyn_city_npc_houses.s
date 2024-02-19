.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DaimynCityNPCHouses_SuspiciousMan1
EventScript_DaimynCityNPCHouses_SuspiciousMan1:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan1
    end

.global EventScript_DaimynCityNPCHouses_SuspiciousMan2
EventScript_DaimynCityNPCHouses_SuspiciousMan2:
    npcchat gText_DaimynCity_NPCHouses_SuspiciousMan2
    end

.global EventScript_DaimynCity_MoveTutor
EventScript_DaimynCity_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_DaimynNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Daimyn
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookLeft
    end

TutoringComplete:
    msgbox gText_DaimynNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_DaimynNPCHouses_TutoringRejected m_LookLeft
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_DaimynNPCHouses_NotEnoughPokeChips m_LookLeft
    goto End

.global EventScript_DaimynCityNPCHouses_TutorsDaughter
EventScript_DaimynCityNPCHouses_TutorsDaughter:
    npcchat gText_DaimynCityNPCHouses_TutorsDaughter
    end

.global EventScript_DaimynCityNPCHouses_TutorsSon
EventScript_DaimynCityNPCHouses_TutorsSon:
    npcchat gText_DaimynCityNPCHouses_TutorsSon
    end

.global EventScript_DaimynCity_FindTM46Thief
EventScript_DaimynCity_FindTM46Thief:
    setvar CHOSEN_ITEM ITEM_TM46
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynCityNPCHouses_OldTrainer
EventScript_DaimynCityNPCHouses_OldTrainer:
    lock
    faceplayer
    checkflag 0x040 @ Pikachu gift received
    if SET _goto OldTrainer_GiftReceived
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Intro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto OldTrainer_Denied
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Grateful MSG_NORMAL
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto OldTrainer_NoSpace
    applymovement 0x1 m_LookLeft
    applymovement 0x2 m_LookRight
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuGiven MSG_NORMAL
    cry SPECIES_PIKACHU 0x0
    msgbox gText_DaimynCityNPCHouses_PikachuJoins MSG_NORMAL
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA @ Above or below
    if equal _call MovePikachuAboveBelow
    compare 0x4000 0xA @ Above or below
    if notequal _call MovePikachuBeside
    playse 0x10 @ Pokeball closes
    pause DELAY_HALFSECOND
    hidesprite 0x2
    setflag 0x040 @ Pikachu gift received
    fanfare 0x101
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuObtained MSG_KEEPOPEN
    waitfanfare
    setvar 0x8000 MOVE_VOLTTACKLE
    setvar 0x8001 MOVE_IRONTAIL
    setvar 0x8002 MOVE_ELECTROBALL
    setvar 0x8003 MOVE_QUICKATTACK
    setvar 0x8004 0x0 @ Ingame gift 0, Pikachu
    setvar 0x8005 0x1E @ Level 30
    callasm CreateInGameGiftPokemon
    getplayerpos 0x4000 0x4001
    compare 0x4000 0xA @ Above or below
    if equal _call PlayerFaceOldManAboveBelow
    compare 0x4000 0xA @ Above or below
    if notequal _call PlayerFaceOldManBeside
    waitmovement PLAYER
    faceplayer
    goto OldTrainer_GiftReceived
    end

OldTrainer_NoSpace:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_NoSpace MSG_NORMAL
    release
    end

MovePikachuAboveBelow:
    compare 0x4001 0x4
    if equal _call MovePikachuAbove
    if notequal _call MovePikachuBelow
    return

MovePikachuBelow:
    applymovement 0x2 m_PikachuWalksToPlayer_Below
    waitmovement 0x2
    applymovement PLAYER m_LookDown
    return

MovePikachuAbove:
    applymovement 0x2 m_PikachuWalksToPlayer_Above
    waitmovement 0x2
    applymovement PLAYER m_LookLeft
    return

MovePikachuBeside:
    applymovement 0x2 m_PikachuWalksToPlayer_Beside
    waitmovement 0x2
    applymovement PLAYER m_LookDown
    return

PlayerFaceOldManAboveBelow:
    compare 0x4001 0x4
    if equal _call LookDown
    if notequal _call LookUp
    return

PlayerFaceOldManBeside:
    applymovement PLAYER m_LookLeft
    return

OldTrainer_GiftReceived:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_PikachuAlreadyGifted MSG_NORMAL
    release
    end

OldTrainer_Denied:
    msgbox gText_DaimynCityNPCHouses_OldTrainer_Denied MSG_NORMAL
    release
    end

.global EventScript_DaimynCityNPCHouses_Pikachu
EventScript_DaimynCityNPCHouses_Pikachu:
    lock
    faceplayer
    cry SPECIES_PIKACHU 0x0
    msgbox gText_DaimynCityNPCHouses_Pikachu MSG_NORMAL
    release
    end

.global EventScript_DaimynCityNPCHouses_TradeBuddy
EventScript_DaimynCityNPCHouses_TradeBuddy:
    npcchat gText_DaimynCityNPCHouses_TraderBuddy
    end

.global EventScript_DaimynCityNPCHouses_Trader
EventScript_DaimynCityNPCHouses_Trader:
    lock
    faceplayer
    checkflag 0x254 @ Did starter based trade
    if SET _goto DaimynTradeComplete
    msgbox gText_DaimynCityNPCHouses_TraderIntro MSG_NORMAL
    switch 0x408D @ Fire starter generation
    case 0, TradeRequestMrMime
    case 1, TradeRequestDratini
    case 2, TradeRequestCorsolaG
    case 3, TradeRequestFrillishF
    case 4, TradeRequestEmolga
    case 5, TradeRequestEevee
    case 6, TradeRequestNoibat
    case 7, TradeRequestHatenna
    end

TradeRequestMrMime:
    msgbox gText_DaimynCityNPCHouses_TraderRequestMrMime MSG_YESNO
    setvar 0x8008 0x1 @ Give mon in slot 1 (Mr Mime-G)
    goto HandleTrade

TradeRequestDratini:
    msgbox gText_DaimynCityNPCHouses_TraderRequestDratini MSG_YESNO
    setvar 0x8008 0x2 @ Give mon in slot 2 (Dratini)
    goto HandleTrade

TradeRequestCorsolaG:
    msgbox gText_DaimynCityNPCHouses_TraderRequestCorsola MSG_YESNO
    setvar 0x8008 0x3 @ Give mon in slot 3 (Corsola-G)
    goto HandleTrade

TradeRequestFrillishF:
    msgbox gText_DaimynCityNPCHouses_TraderRequestFrillish MSG_YESNO
    setvar 0x8008 0x4 @ Give mon in slot 4 (Frillish)
    goto HandleTrade

TradeRequestEmolga:
    msgbox gText_DaimynCityNPCHouses_TraderRequestEmolga MSG_YESNO
    setvar 0x8008 0x5 @ Give mon in slot 5 (Emolga)
    goto HandleTrade

TradeRequestEevee:
    msgbox gText_DaimynCityNPCHouses_TraderRequestEevee MSG_YESNO
    setvar 0x8008 0x6 @ Give mon in slot 6 (Eevee)
    goto HandleTrade

TradeRequestNoibat:
    msgbox gText_DaimynCityNPCHouses_TraderRequestNoibat MSG_YESNO
    setvar 0x8008 0x7 @ Give mon in slot 7 (Noibat)
    goto HandleTrade

TradeRequestHatenna:
    msgbox gText_DaimynCityNPCHouses_TraderRequestHatenna MSG_YESNO
    setvar 0x8008 0x8 @ Give mon in slot 8 (Hatenna)
    goto HandleTrade

HandleTrade:
    copyvar 0x8004 0x8008 @ Copy expected mon from same trade slot as given mon
    compare LASTRESULT NO
    if TRUE _goto TradeRejected
    special2 LASTRESULT 0xFC // Checks the trade set in 0x8004 and buffers the name of the Pokemon wanted and the given Pokemon
    copyvar 0x8009 LASTRESULT
    call SelectTradePokemon
    compare 0x8004 0x6
    if greaterorequal _goto TradeRejected
    call CheckTradePokemonSelected
    comparevars LASTRESULT 0x8009
    if notequal _goto TraderWrongPokemon
    msgbox gText_DaimynCityNPCHouses_TraderTradeInitiated MSG_NORMAL
    call InitiateTrade
    goto DaimynTradeComplete

TradeRejected:
    msgbox gText_DaimynCityNPCHouses_TraderRejected MSG_NORMAL
    release
    end

TraderWrongPokemon:
    msgbox gText_DaimynCityNPCHouses_TraderWrongPokemon MSG_NORMAL
    release
    end

DaimynTradeComplete:
    setflag 0x254 @ Did starter based trade
    msgbox gText_DaimynCityNPCHouses_TraderTradeComplete MSG_NORMAL
    release
    end

.global EventScript_DaimynCityNPCHouses_Lana
EventScript_DaimynCityNPCHouses_Lana:
    lock
    faceplayer
    checkflag 0x834 @ Renamed Someone's PC to Lana's PC
    if SET _goto RevisitingLana
    msgbox gText_DaimynCityNPCHouses_LanaIntroduction MSG_YESNO
    compare LASTRESULT NO
    if notequal _call UsesPC
    if equal _call DoesNotUsePC
    msgbox gText_DaimynCityNPCHouses_LanaIntroductionContinued MSG_NORMAL
    setflag 0x834 @ Rename Someone's PC to Lana's PC
    goto LearnAboutPCPrompt
    end

UsesPC:
    msgbox gText_DaimynCityNPCHouses_LanaUsesPC MSG_NORMAL
    return

DoesNotUsePC:
    msgbox gText_DaimynCityNPCHouses_LanaDoesNotUsePC MSG_NORMAL
    return

RevisitingLana:
    msgbox gText_DaimynCityNPCHouses_LanaRevisited MSG_NORMAL
    goto LearnAboutPCPrompt

LearnAboutPCPrompt:
    msgbox gText_DaimynCityNPCHouses_LanaLearnAboutPC MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToLearnAboutPC
    msgbox gText_DaimynCityNPCHouses_DoWantToLearnAboutPC MSG_NORMAL
    checkflag 0x4BC @ Is champion
    if SET _goto GivePocketPC
    msgbox gText_DaimynCityNPCHouses_PocketPCHint MSG_NORMAL
    msgbox gText_DaimynCityNPCHouses_LanaFarewell MSG_NORMAL
    release
    applymovement 0x1 m_LookRight
    end

ChoseNotToLearnAboutPC:
    msgbox gText_DaimynCityNPCHouses_DoNotWantToLearnAboutPC MSG_NORMAL
    release
    applymovement 0x1 m_LookRight
    end

GivePocketPC:
    # TODO later: Check if player is champ to give Pocket PC
    end

.global SignScript_DaimynCityNPCHouses_EntrancePC
SignScript_DaimynCityNPCHouses_EntrancePC:
    msgbox gText_DaimynCityNPCHouses_LanasPCEntrance MSG_SIGN
    end

.global SignScript_DaimynCityNPCHouses_TransferPC
SignScript_DaimynCityNPCHouses_TransferPC:
    msgbox gText_DaimynCityNPCHouses_TransferPC MSG_SIGN
    end

.global SignScript_DaimynCityNPCHouses_Poster
SignScript_DaimynCityNPCHouses_Poster:
    msgbox gText_DaimynCityNPCHouses_Poster MSG_SIGN
    end

.global SignScript_DaimynCityNPCHouses_TransferMachine
SignScript_DaimynCityNPCHouses_TransferMachine:
    msgbox gText_DaimynCityNPCHouses_TransferMachine MSG_SIGN
    end

.global EventScript_DaimynCityNPCHouses_MoveDeleterReminderSon
EventScript_DaimynCityNPCHouses_MoveDeleterReminderSon:
    npcchat gText_DaimynCityNPCHouses_MoveDeleterReminderSon
    applymovement LASTTALKED m_LookRight
    end

.global EventScript_DaimynCityNPCHouses_MoveDeleter
EventScript_DaimynCityNPCHouses_MoveDeleter:
    lock
    faceplayer
    msgbox gText_DaimynCityNPCHouses_MoveDeleterPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChangedMindAboutMoveDeleteOrRemember
    goto ChoosePokemonAndMoveToDelete

ChoosePokemonAndMoveToDelete:
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_ChoosePokemon MSG_KEEPOPEN
    special 0x9F @ Choose a Pokemon
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto ChangedMindAboutMoveDeleteOrRemember
    special 0x148 @ Check if egg
    compare LASTRESULT 0x1
    if equal _goto CannotDeleteEggsMove
    special 0xDF @ Check how many moves the Pokemon knows
    compare LASTRESULT 0x1
    if equal _goto CannotForgetLastMove
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_ChooseMove MSG_KEEPOPEN
    fadescreen FADEOUT_BLACK
    special 0xDC @ Show moves, move choice put in 0x8005
    fadescreen FADEIN_BLACK
    compare 0x8005 0x4
    if 0x1 _goto ChoosePokemonAndMoveToDelete @ If a move wasn't chosen, loop back
    special 0xDE @ Get Pokemon's name
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChangedMindAboutMoveDeleteOrRemember
    special 0xDD @ Delete chosen move
    pause DELAY_HALFSECOND
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_MoveDeleted MSG_KEEPOPEN
    waitfanfare
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_ComeToForgetMoreMoves MSG_NORMAL
    goto ResetMoveDeleterOrReminder

CannotDeleteEggsMove:
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_ChoiceIsEgg MSG_NORMAL
    goto ChangedMindAboutMoveDeleteOrRemember

CannotForgetLastMove:
    special 0xDE @ Get Pokemon's name
    msgbox gText_DaimynCityNPCHouses_MoveDeleter_ChoiceOnlyKnowsOneMove MSG_NORMAL
    goto ChangedMindAboutMoveDeleteOrRemember

.global EventScript_DaimynCityNPCHouses_MoveReminder
EventScript_DaimynCityNPCHouses_MoveReminder:
    lock
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynCityNPCHouses_MoveReminderPrompt MSG_KEEPOPEN
    @ Intentional fall through

TeachMovesMenuHandling:
    multichoiceoption gText_DaimynCityNPCHouses_MoveReminder_PastMovesChoice 0
	multichoiceoption gText_DaimynCityNPCHouses_MoveReminder_EggMovesChoice 1
	multichoiceoption gText_DaimynCityNPCHouses_MoveReminder_CancelChoice 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    copyvar MULTICHOICE_SELECTION LASTRESULT
	switch MULTICHOICE_SELECTION
	case 0, TeachPastMove
	case 1, TeachEggMove
	case 2, ChangedMindAboutMoveDeleteOrRemember
    case 0xF, ChangedMindAboutMoveDeleteOrRemember
	goto ChangedMindAboutMoveDeleteOrRemember

TeachPastMove:
    clearflag 0x917 @ Teach regular moves
    checkitem ITEM_POKE_CHIP 0x1
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChipsForTutoring
    goto TeachMove

TeachEggMove:
    setflag 0x917 @ Teach egg moves
    checkitem ITEM_POKE_CHIP 0xA
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChipsForTutoring
    goto TeachMove

TeachMove:
    msgbox gText_DaimynCityNPCHouses_MoveReminder_ChoosePokemon MSG_KEEPOPEN
    special 0x9F @ Choose a Pokemon
    waitstate
    compare 0x8004 0x6 @ Cancelled out
    if greaterorequal _goto ChangedMindAboutMoveDeleteOrRemember
    special 0x148 @ Check if egg
    compare LASTRESULT 0x1
    if equal _goto CannotTeachEgg
    callasm CanLearnAnyMoves
    compare LASTRESULT 0x0
    if equal _goto PokemonCannotLearnMoves
    msgbox gText_DaimynCityNPCHouses_MoveReminder_WhichMovePrompt MSG_KEEPOPEN
    special 0xE0 @ Chose move
    waitstate
    compare 0x8004 0x0
    if equal _goto TeachMove @ Loop until selection
    checkflag 0x917 @ Teaching egg move
    if NOT_SET _call Remove1Chip
    if SET _call Remove10Chips
    playse 0xF8 @ Money SE
    waitse
    copyvar 0x8012 0x8013
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_DaimynCityNPCHouses_MoveReminderPrompt_TeachMore MSG_NORMAL
    goto TeachMovesMenuHandling

Remove1Chip:
    removeitem ITEM_POKE_CHIP 0x1
    return

Remove10Chips:
    removeitem ITEM_POKE_CHIP 0xA
    return

NotEnoughPokeChipsForTutoring:
    msgbox gText_DaimynCityNPCHouses_MoveReminder_NotEnoughChips MSG_NORMAL
    textcolor RED
    goto ChangedMindAboutMoveDeleteOrRemember

CannotTeachEgg:
    msgbox gText_DaimynCityNPCHouses_MoveReminder_ChoseEgg MSG_NORMAL
    textcolor RED
    goto ChangedMindAboutMoveDeleteOrRemember

PokemonCannotLearnMoves:
    msgbox gText_DaimynCityNPCHouses_MoveReminder_ChoiceIsIneligible MSG_NORMAL
    textcolor RED
    goto ChangedMindAboutMoveDeleteOrRemember

ChangedMindAboutMoveDeleteOrRemember:
    msgbox gText_DaimynCityNPCHouses_MoveDeleterReminder_ChangedMind MSG_NORMAL
    textcolor RED
    goto ResetMoveDeleterOrReminder

ResetMoveDeleterOrReminder:
    release
    applymovement LASTTALKED m_LookLeft
    end

m_PikachuWalksToPlayer_Below: .byte walk_down, walk_down, walk_right, walk_right, walk_right, look_up, end_m
m_PikachuWalksToPlayer_Above: .byte walk_up, walk_right, walk_right, end_m
m_PikachuWalksToPlayer_Beside: .byte walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_up, end_m
