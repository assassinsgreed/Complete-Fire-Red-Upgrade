.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_HeleoCity_Foreman
EventScript_HeleoCity_Foreman:
    lock
    faceplayer
    checkflag 0x235 @ Received rock smash
    if SET _goto ForemanGiftGiven
    msgbox gText_HeleoCity_ForemanHMGift MSG_NORMAL
    obtainitem ITEM_HM05 0x1
    setflag 0x235 @ Received rock smash
    goto ForemanGiftGiven
    end

ForemanGiftGiven:
    npcchatwithmovement gText_HeleoCity_ForemanBadgeComment m_LookRight 
    goto End

.global EventScript_HeleoCity_ForemanAssistant
EventScript_HeleoCity_ForemanAssistant:
    npcchat gText_HeleoCity_ForemanAssistant
    end

.global EventScript_HeleoCity_MoveTutor
EventScript_HeleoCity_MoveTutor:
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_HeleoNPCHouses_TutorConfirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_HeleoNPCHouses_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Heleo
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookRight
    end

TutoringComplete:
    msgbox gText_HeleoNPCHouses_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_HeleoNPCHouses_TutoringRejected m_LookRight
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_HeleoNPCHouses_NotEnoughPokeChips m_LookRight
    goto End

.global EventScript_HeleoCity_MoveTutorSon
EventScript_HeleoCity_MoveTutorSon:
    npcchat gText_HeleoCity_MoveTutorSon
    end

.global EventScript_HeleoCity_SwarmSwami
EventScript_HeleoCity_SwarmSwami:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_SwarmSwamiIntro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto EventScript_HeleoCity_SwarmSwami_Rejected
    msgbox gText_HeleoNPCHouses_SwarmSwamiStarting MSG_NORMAL
    fadescreen FADEOUT_BLACK
    pause DELAY_1SECOND
    special 0x58 @ Buffer the location (buffer1) and pokemon (buffer2) swarming now
    pause DELAY_HALFSECOND
    fadescreen FADEIN_BLACK
    sound 0x15 @ Exclaim
    applymovement 0x1 m_Surprise
    msgbox gText_HeleoNPCHouses_SwarmSwamiComplete MSG_NORMAL
    goto End

EventScript_HeleoCity_SwarmSwami_Rejected:
    msgbox gText_HeleoNPCHouses_SwarmSwamiRejected MSG_NORMAL
    goto End

.global EventScript_HeleoCity_SwamiFan
EventScript_HeleoCity_SwamiFan:
    npcchat gText_HeleoNPCHouses_SwamiFan
    end

.global EventScript_HeleoCity_SwamiResearcher
EventScript_HeleoCity_SwamiResearcher:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_SwamiResearcher MSG_NORMAL
    compare 0x4053 0x11 @ 17 swarm pokemon
    if equal _goto End
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto SwamiResearcherRejected
    setvar 0x8003 0x0 @ From Party
    setvar 0x8004 0x0 @ First Slot
    special2 LASTRESULT 0x18 @ Check species
    switch LASTRESULT
    case SPECIES_RATTATA, ResearcherRattata
    case SPECIES_RATICATE, ResearcherRaticate
    case SPECIES_RAICHU_A, ResearcherRaichuA
    case SPECIES_GRIMER, ResearcherGrimer
    case SPECIES_MUK, ResearcherMuk
    case SPECIES_SLOWPOKE_G, ResearcherSlowpokeG
    case SPECIES_SLOWBRO_G, ResearcherSlowbroG
    case SPECIES_SLOWKING_G, ResearcherSlowkingG
    case SPECIES_FARFETCHD, ResearcherFarfetchd
    case SPECIES_KOFFING, ResearcherKoffing
    case SPECIES_WEEZING, ResearcherWeezing
    case SPECIES_MIME_JR, ResearcherMimeJr
    case SPECIES_MR_MIME, ResearcherMrMime
    case SPECIES_CORSOLA, ResearcherCorsola
    case SPECIES_DARUMAKA, ResearcherDarumaka
    case SPECIES_DARMANITAN, ResearcherDarmanitan
    case SPECIES_STUNFISK, ResearcherStunfisk
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestWrongPokemon MSG_NORMAL
    goto End

SwamiResearcherRejected:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestDenied MSG_NORMAL
    goto End

ResearcherRattata:
    checkflag 0x236 @ Shown Rattata
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x236 @ Shown Rattata
    goto End

ResearcherRaticate:
    checkflag 0x237 @ Shown Raticate
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x237 @ Shown Raticate
    goto End

ResearcherRaichuA:
    checkflag 0x238 @ Shown Alolan Raichu
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x238 @ Shown Alolan Raichu
    goto End

ResearcherGrimer:
    checkflag 0x239 @ Shown Grimer
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x239 @ Shown Grimer
    goto End

ResearcherMuk:
    checkflag 0x23A @ Shown Muk
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23A @ Shown Muk
    goto End

ResearcherSlowpokeG:
    checkflag 0x23B @ Shown Galarian Slowpoke
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23B @ Shown Galarian Slowpoke
    goto End

ResearcherSlowbroG:
    checkflag 0x23C @ Shown Galarian Slowbro
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23C @ Shown Galarian Slowbro
    goto End

ResearcherSlowkingG:
    checkflag 0x23D @ Shown Galarian Slowking
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23D @ Shown Galarian Slowking
    goto End

ResearcherFarfetchd:
    checkflag 0x23E @ Shown Farfetch'd
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23E @ Shown Farfetch'd
    goto End

ResearcherKoffing:
    checkflag 0x23F @ Shown Koffing
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x23F @ Shown Koffing
    goto End

ResearcherWeezing:
    checkflag 0x240 @ Shown Weezing
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x240 @ Shown Weezing
    goto End

ResearcherMimeJr:
    checkflag 0x241 @ Shown Mime Jr
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x241 @ Shown Mime Jr
    goto End

ResearcherMrMime:
    checkflag 0x242 @ Shown Mr Mime
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x242 @ Shown Mr Mime
    goto End

ResearcherCorsola:
    checkflag 0x243 @ Shown Corsola
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x243 @ Shown Corsola
    goto End

ResearcherDarumaka:
    checkflag 0x244 @ Shown Darumaka
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x244 @ Shown Darumaka
    goto End

ResearcherDarmanitan:
    checkflag 0x245 @ Shown Darmanitan
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x245 @ Shown Darmanitan
    goto End

ResearcherStunfisk:
    checkflag 0x246 @ Shown Stunfisk
    if SET _goto AlreadyShownPokemon
    call GiveSwarmItem
    setflag 0x246 @ Shown Stunfisk
    goto End

GiveSwarmItem:
    bufferpartypokemon 0x0 0x0
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestShownPokemon MSG_NORMAL
    addvar 0x4053 0x1
    compare 0x4053 0x11 @ 17 swarm pokemon
    if equal _goto AllSwarmPokemonShown
    obtainitem ITEM_BOTTLE_CAP 0x1
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestShownPokemonConclusion MSG_NORMAL
    return

AlreadyShownPokemon:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestAlreadyShown MSG_NORMAL
    goto End

AllSwarmPokemonShown:
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestAllSwarmPokemonShown MSG_NORMAL
    obtainitem ITEM_GOLD_BOTTLE_CAP 0x1
    msgbox gText_HeleoNPCHouses_SwamiResearcherRequestGratitude MSG_NORMAL
    goto End

.global EventScript_HeleoCity_RainesGrandfather
EventScript_HeleoCity_RainesGrandfather:
    npcchatwithmovement gText_HeleoNPCHouses_RainesGrandfather m_LookLeft
    end

.global EventScript_HeleoCity_RainesCastform
EventScript_HeleoCity_RainesCastform:
    lock
    faceplayer
    checksound
    cry SPECIES_CASTFORM 0x0
    msgbox gText_HeleoNPCHouses_RainesCastform MSG_NORMAL
    waitcry
    goto End

.global EventScript_HeleoCity_TrainersMom
EventScript_HeleoCity_TrainersMom:
    npcchatwithmovement gText_HeleoNPCHouses_TrainersMom m_LookLeft
    end

.global EventScript_HeleoCity_TrainersYoungKid
EventScript_HeleoCity_TrainersYoungKid:
    npcchatwithmovement gText_HeleoNPCHouses_TrainersYoungKid m_LookUp
    end

.global EventScript_HeleoCity_TrainersKid
EventScript_HeleoCity_TrainersKid:
    npcchat gText_HeleoNPCHouses_TrainersKid
    end

.global EventScript_HeleoCity_PokemonFanClubChairman
EventScript_HeleoCity_PokemonFanClubChairman:
    lock
    faceplayer
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokemonAreLame
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman_PokemonAreGood MSG_NORMAL
    applymovement 0x1 m_LookDown
    goto End

PokemonAreLame:
    msgbox gText_HeleoNPCHouses_PokemonFanClubChairman_PokemonAreLame MSG_NORMAL
    applymovement 0x1 m_LookDown
    goto End

.global EventScript_HeleoCity_PokemonGroomer
EventScript_HeleoCity_PokemonGroomer:
    lock
    faceplayer
    msgbox gText_HeleoCityNpcHouses_GroomerIntro MSG_NORMAL
    checkflag 0xE0A @ Has groomed today
    if SET _goto PokemonGroomer_AlreadyGroomed
    showmoney 0x0 0x0
    msgbox gText_HeleoCityNpcHouses_GroomerConfirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PokemonGroomer_Denied
    checkmoney 0x3E8 @ 1000
    compare LASTRESULT TRUE
    if FALSE _goto PokemonGroomer_NotEnoughMoney
    special 0x9F @ Select a Pokemon and store it's position in 0x8004
    waitstate
    compare 0x8004 0x6 @ Don't continue if user backed out
    if greaterorequal _goto PokemonGroomer_Denied
    callasm StoreIsPartyMonEgg
    compare LASTRESULT TRUE
    if TRUE _goto PokemonGroomer_InvalidPokemon
    removemoney 0x3E8
    sound 0xF8 @ Money SE
    waitse
    updatemoney
    pause DELAY_HALFSECOND
    hidemoney
    bufferpartypokemon 0x0 0x8004
    msgbox gText_HeleoCityNpcHouses_GroomerStarting MSG_NORMAL
    setvar 0x8003 0x0 @ Apply happiness to party pokemon, 0x8004 already holds index
    setvar 0x8005 0x0032 @ Add 50 (out of 255) friendship points (00xx adds, 01xx subtracts)
    fadescreen FADEOUT_BLACK
    fanfare 0x100
	waitfanfare
    special 0x13
    fadescreen FADEIN_BLACK
    setflag 0xE0A @ Daily grooming complete
    checkflag 0x24E @ Got soothe bell gift
    if NOT_SET _call PokemonGroomer_FriendshipAssessment
    msgbox gText_HeleoCityNpcHouses_GroomerGroomAgainTomorrow MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_AlreadyGroomed:
    msgbox gText_HeleoCityNpcHouses_GroomerAlreadyGroomedToday MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_Denied:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerDenied MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_NotEnoughMoney:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerNotEnoughMoney MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_InvalidPokemon:
    hidemoney
    msgbox gText_HeleoCityNpcHouses_GroomerCannotGroomEgg MSG_NORMAL
    goto PokemonGroomer_End

PokemonGroomer_FriendshipAssessment:
    special2 LASTRESULT 0xD @ Check if selected Pokemon has at least 175 happiness. (0x8003 already set to select from party, and 0x8004 the selected index)
    compare LASTRESULT 175
    if greaterorequal _call PokemonGroomer_GiveSootheBell
    return

PokemonGroomer_GiveSootheBell:
    msgbox gText_HeleoCityNpcHouses_GroomerPokemonFriendshipThresholdMet MSG_NORMAL
    obtainitem ITEM_SOOTHE_BELL 0x1
    msgbox gText_HeleoCityNpcHouses_GroomerSootheBellExplained MSG_NORMAL
    setflag 0x24E @ Got soothe bell gift
    return

PokemonGroomer_End:
    applymovement 0x2 m_LookDown
    goto End

.global EventScript_HeleoCity_PokemonFanClubSuperfan
EventScript_HeleoCity_PokemonFanClubSuperfan:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubSuperfan m_LookUp
    end

.global EventScript_HeleoCity_PokemonFanClubSwimmer
EventScript_HeleoCity_PokemonFanClubSwimmer:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubSwimmer m_LookRight
    end

.global EventScript_HeleoCity_PokemonFanClubMother
EventScript_HeleoCity_PokemonFanClubMother:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubMother m_LookLeft
    end

.global EventScript_HeleoCity_HallwayBoy
EventScript_HeleoCity_HallwayBoy:
    npcchatwithmovement gText_HeleoNPCHouses_PokemonFanClubHallwayBoy m_LookLeft
    end

.global EventScript_HeleoCity_TerraceDad
EventScript_HeleoCity_TerraceDad:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceDad m_LookLeft
    end

.global EventScript_HeleoCity_TerraceMom
EventScript_HeleoCity_TerraceMom:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceMom m_LookLeft
    end

.global EventScript_HeleoCity_TerraceSon
EventScript_HeleoCity_TerraceSon:
    npcchatwithmovement gText_HeleoNPCHouses_TerraceSon m_LookRight
    end

.global EventScript_HeleoCity_SodaMachineGirl
EventScript_HeleoCity_SodaMachineGirl:
    npcchat gText_HeleoNPCHouses_VendingMachineGirl
    end
