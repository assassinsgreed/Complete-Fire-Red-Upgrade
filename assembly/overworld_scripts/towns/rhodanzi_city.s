.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Overworld
.global MapScript_RhodanziOverworld_FlightSpot
MapScript_RhodanziOverworld_FlightSpot:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RhodanziOverworld_FlightFlag
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RhodanziOverworld_FlightFlag:
    setworldmapflag 0x892
    setflag 0x31 @ Hide Rival and Team Pluto on route 3
    checkflag 0x820 @ Obtained Rhodanzi City Gym
    IF SET _call HideThugs
    end

HideThugs:
    hidesprite 0x6
    hidesprite 0x7
    return

.global EventScript_RhodanziOverworld_SunSightMan
EventScript_RhodanziOverworld_SunSightMan:
    npcchat gText_RhodanziOverworld_SunSightMan
    end

.global EventScript_RhodanziOverworld_FirstStop
EventScript_RhodanziOverworld_FirstStop:
    npcchat gText_RhodanziOverworld_FirstStop
    end

.global EventScript_RhodanziOverworld_PokemonVariety
EventScript_RhodanziOverworld_PokemonVariety:
    npcchat gText_RhodanziOverworld_PokemonVariety
    end

.global EventScript_RhodanziOverworld_TreeGuy
EventScript_RhodanziOverworld_TreeGuy:
    npcchat gText_RhodanziOverworld_TreeGuy
    end

.global SignScript_RhodanziCity_EntranceSign
SignScript_RhodanziCity_EntranceSign:
    msgbox gText_RhodanziCity_EntranceSign MSG_SIGN
    end

.global SignScript_RhodanziCity_FishermanSign
SignScript_RhodanziCity_FishermanSign:
    msgbox gText_RhodanziCity_FishermanSign MSG_SIGN
    end

.global TileScript_RhodanziOverworld_ThugsCaught
TileScript_RhodanziOverworld_ThugsCaught:
    checkflag 0x820
    if SET _goto End
    lock
    msgbox gText_RhodanziOverworld_ThugsRumour MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement 0x6 m_Surprise
    applymovement 0x7 m_Surprise
    waitmovement ALLEVENTS
    msgbox gText_RhodanziOverworld_Thugs MSG_NORMAL
    applymovement 0x6 m_ThugBottomMoveToPush
    applymovement 0x7 m_ThugTopMoveToPush
    waitmovement ALLEVENTS
    sound 0x7 @Bumping into wall
    applymovement 0x6 m_ThugPush
    applymovement 0x7 m_ThugPush
    applymovement PLAYER m_PlayerJump
    waitmovement ALLEVENTS
    applymovement 0x6 m_ThugBottomMoveBack
    applymovement 0x7 m_ThugTopMoveBack
    waitmovement ALLEVENTS
    msgbox gText_RhodanziOverworld_ThugsThreat MSG_NORMAL
    release
    end

.global EventScript_RhodanziOverworld_ThugBottomSpokenTo
EventScript_RhodanziOverworld_ThugBottomSpokenTo:
    npcchatwithmovement gText_RhodanziOverworld_ThugsEna m_LookUp
    end

.global EventScript_RhodanziOverworld_ThugTopSpokenTo
EventScript_RhodanziOverworld_ThugTopSpokenTo:
    npcchatwithmovement gText_RhodanziOverworld_Thugs m_LookDown
    end

.global EventScript_RhodanziOverworld_FindTMEchoedVoice
EventScript_RhodanziOverworld_FindTMEchoedVoice:
    setvar CHOSEN_ITEM ITEM_TM49
    call ItemScript_Common_FindTM
    end

.global EventScript_RhodanziOverworld_PokeChipMan
EventScript_RhodanziOverworld_PokeChipMan:
    npcchat gText_RhodanziOverworld_PokeChipMan
    end

.global EventScript_RhodanziOverworld_HoneyMan
EventScript_RhodanziOverworld_HoneyMan:
    npcchat gText_RhodanziOverworld_Honey
    end

m_ThugTopMoveToPush:
    .byte run_right, run_down, look_left, end_m

m_ThugBottomMoveToPush:
    .byte run_right, run_up, look_left, end_m

m_ThugPush:
    .byte say_cross, jump_onspot_left, end_m

m_PlayerJump:
    .byte jump_left, end_m

m_ThugTopMoveBack:
    .byte run_up, run_left, look_down, end_m

m_ThugBottomMoveBack:
    .byte run_down, run_left, look_up, end_m

@ Facilities
.global MapScript_RhodanziFacilities_PokemonCenter
MapScript_RhodanziFacilities_PokemonCenter:
	mapscript MAP_SCRIPT_ON_TRANSITION MapScript_RhodanziFacilities_PokemonCenter_SetHealingSpot
	.byte MAP_SCRIPT_TERMIN

MapScript_RhodanziFacilities_PokemonCenter_SetHealingSpot:
    sethealingplace 0x03 @ Originally Pewter City
    call ResetRoute11PlutoEventOnWhiteout
    end

.global EventScript_RhodanziFacilities_Mart_BadgeStock
EventScript_RhodanziFacilities_Mart_BadgeStock:
    npcchat gText_RhodanziFacilities_Mart_BadgeStock
    end

.global EventScript_RhodanziFacilities_Mart_EscapeRope
EventScript_RhodanziFacilities_Mart_EscapeRope:
    npcchat gText_RhodanziFacilities_Mart_EscapeRope
    end

.global EventScript_RhodanziFacilities_Center_UsingFacility
EventScript_RhodanziFacilities_Center_UsingFacility:
    npcchat gText_RhodanziFacilities_Center_UsingFacility
    end

.global EventScript_RhodanziFacilities_Center_Trade
EventScript_RhodanziFacilities_Center_Trade:
    npcchat gText_RhodanziFacilities_Center_Trade
    end

.global EventScript_RhodanziFacilities_Center_PokemonTreatment
EventScript_RhodanziFacilities_Center_PokemonTreatment:
    npcchat gText_RhodanziFacilities_Center_PokemonTreatment
    end

@ NPC Houses
.global EventScript_RhodanziNPCHouses_Fisherman
EventScript_RhodanziNPCHouses_Fisherman:
    lock
    faceplayer
    checkflag 0x24A @ Has Old Rod?
    if SET _goto EventScript_RhodanziNPCHouses_FishermanFarewell
    msgbox gText_RhodanziNPCHouses_FishermanIntro MSG_YESNO
    compare LASTRESULT YES
    IF TRUE _goto EventScript_RhodanziNPCHouses_FishermanYes
    msgbox gText_RhodanziNPCHouses_FishermanNo MSG_NORMAL
    release
    end

EventScript_RhodanziNPCHouses_FishermanYes:
    msgbox gText_RhodanziNPCHouses_FishermanYes MSG_NORMAL
    obtainitem ITEM_OLD_ROD 0x1
    setflag 0x24A @ Has Old Rod?
    msgbox gText_RhodanziNPCHouses_FishermanTip MSG_NORMAL
    goto EventScript_RhodanziNPCHouses_FishermanFarewell

EventScript_RhodanziNPCHouses_FishermanFarewell:
    npcchat gText_RhodanziNPCHouses_FishermanFarewell
    release
    end

.global EventScript_RhodanziNPCHouses_TerrenceSister
EventScript_RhodanziNPCHouses_TerrenceSister:
    checkflag 0x820 @ Beat Terrence
    if SET _goto TerrenceSister_BadgeObtained
    npcchat gText_RhodanziNPCHouses_TerrenceSister
    end

TerrenceSister_BadgeObtained:
    npcchat gText_RhodanziNPCHouses_TerrenceSister_BadgeObtained
    end

.global EventScript_RhodanziNPCHouses_TerrenceLittleBrother
EventScript_RhodanziNPCHouses_TerrenceLittleBrother:
    lock
    faceplayer
    checkflag 0x820 @ Beat Terrence
    if SET _goto TerrenceBrother_BadgeObtained
    msgbox gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestion MSG_YESNO
    compare LASTRESULT YES
    if TRUE _goto EventScript_RhodanziNPCHouses_TerrenceLittleBrotherYes
    msgbox gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionNo MSG_NORMAL
    release
    end

TerrenceBrother_BadgeObtained:
    npcchatwithmovement gText_RhodanziNPCHouses_TerrenceBrother_BadgeObtained m_LookUp
    release
    end

EventScript_RhodanziNPCHouses_TerrenceLittleBrotherYes:
    npcchat gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionYes
    applymovement LASTTALKED m_LookUp
    end

EventScript_RhodanziNPCHouses_TerrenceLittleBrotherNo:
    npcchat gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionNo
    applymovement LASTTALKED m_LookUp
    end

.global EventScript_RhodanziNPCHouses_Evolution
EventScript_RhodanziNPCHouses_Evolution:
    npcchatwithmovement gText_RhodanziNPCHouses_Evolution m_LookRight
    end

.global EventScript_RhodanziNPCHouses_OldTrainer
EventScript_RhodanziNPCHouses_OldTrainer:
    npcchatwithmovement gText_RhodanziNPCHouses_OldTrainer m_LookLeft
    end

.global EventScript_RhodanziNPCHouses_NidoranTrainer
EventScript_RhodanziNPCHouses_NidoranTrainer:
    npcchat gText_RhodanziNPCHouses_NidoranTrainer
    end

.global EventScript_RhodanziNPCHouses_Nidoran
EventScript_RhodanziNPCHouses_Nidoran:
    lock
    faceplayer
    checksound
    cry SPECIES_NIDORAN_M 0x0
    msgbox gText_RhodanziNPCHouses_Nidoran MSG_FACE
    waitcry
    release
    end

.global EventScript_RhodanziNPCHouses_PokedexTrainer
EventScript_RhodanziNPCHouses_PokedexTrainer:
    lock
    faceplayer
    msgbox gText_RhodanziNPCHouses_PokedexTrainerQuestion MSG_YESNO
    compare LASTRESULT YES
    if TRUE _goto EventScript_RhodanziNPCHouses_PokedexTrainerYes
    goto EventScript_RhodanziNPCHouses_PokedexTrainerNo

EventScript_RhodanziNPCHouses_PokedexTrainerYes:
    npcchatwithmovement gText_RhodanziNPCHouses_PokedexTrainerYes m_LookRight
    end

EventScript_RhodanziNPCHouses_PokedexTrainerNo:
    npcchatwithmovement gText_RhodanziNPCHouses_PokedexTrainerNo m_LookRight
    end

.global EventScript_RhodanziNPCHouses_PlantGirl
EventScript_RhodanziNPCHouses_PlantGirl:
    npcchatwithmovement gText_RhodanziNPCHouses_PlantGirl m_LookLeft
    end

.global EventScript_RhodanziNPCHouses_MailTrainer
EventScript_RhodanziNPCHouses_MailTrainer:
    npcchatwithmovement gText_RhodanziNPCHouses_MailTrainer m_LookDown
    end

@ Gym
.global SignScript_RhodanziGym_Placard
SignScript_RhodanziGym_Placard:
    checkflag 0x232 @ DexNav event triggered
    if SET _goto SignScript_RhodanziGym_PlacardWithBadgeAndDexNavEvent
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto SignScript_RhodanziGym_PlacardWithBadge
    msgbox gText_RhodanziGym_Winners MSG_SIGN
    end

SignScript_RhodanziGym_PlacardWithBadge:
    msgbox gText_RhodanziGym_WinnersWithBadge MSG_SIGN
    end

SignScript_RhodanziGym_PlacardWithBadgeAndDexNavEvent:
    msgbox gText_RhodanziGym_WinnersWithBadgeAndDexNavEvent MSG_SIGN
    end

.global EventScript_RhodanziGym_GymExpert
EventScript_RhodanziGym_GymExpert:
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto EventScript_RhodanziGym_GymExpertBadgeObtained
    npcchat gText_RhodanziGym_ExpertTips
    end

EventScript_RhodanziGym_GymExpertBadgeObtained:
    npcchat gText_RhodanziGym_ExpertBadgeObtained
    end

.global EventScript_RhodanziGym_Alonso
EventScript_RhodanziGym_Alonso:
    trainerbattle0 0x0 0xC 0x0 gText_RhodanziGym_Alonso_Intro gText_RhodanziGym_Alonso_Defeat
    msgbox gText_RhodanziGym_Alonso_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Brandon
EventScript_RhodanziGym_Brandon:
    trainerbattle0 0x0 0xD 0x0 gText_RhodanziGym_Brandon_Intro gText_RhodanziGym_Brandon_Defeat
    msgbox gText_RhodanziGym_Brandon_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Leader_Terrence
EventScript_RhodanziGym_Leader_Terrence:
    lockall
    faceplayer
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto EventScript_RhodanziGym_Leader_TerrenceChat
    msgbox gText_RhodanziGym_Leader_Terrence_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 0xE 0x100 gText_RhodanziGym_Leader_Terrence_Intro gText_RhodanziGym_Leader_Terrence_Defeat EventScript_RhodanziGym_Leader_TerrenceDefeated
    end

EventScript_RhodanziGym_Leader_TerrenceDefeated:
    msgbox gText_RhodanziGym_Leader_Terrence_BadgeAwarded MSG_NORMAL
    setflag 0x820 @ Rhodanzi gym badge
    fanfare 0x13D @ Gym victory
    msgbox gText_RhodanziGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    setvar 0x4097 0x1 @ Disable Team Pluto tile event  
    settrainerflag 0xC @ Alonso cannot be battled now
    settrainerflag 0xD @ Brandon cannot be battled now
    msgbox gText_RhodanziGym_Leader_Terrence_BadgeDescription MSG_NORMAL
    msgbox gText_RhodanziGym_Leader_Terrence_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_RhodanziGym_TMReceived
    additem ITEM_TM05 0x1
    giveitemwithfanfare ITEM_TM05 0x1 0x101 @ MUS_FANFA1
    setflag 0x254 @ Received TM 05 from Terrence
    setflag 0x4B0 @ Defeated Terrence
    setflag 0x25C @ New Pokemart Stock
    msgbox gText_RhodanziGym_Leader_Terrence_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_RhodanziGym_Leader_TerrenceChat:
    npcchat gText_RhodanziGym_Leader_Terrence_Chat
    end

@ Trainer House
EndMovementAndEvent:
    waitmovement ALLEVENTS
    release
    end

@ Main room events
.global EventScript_RhodanziTrainerSchool_MainRoom_Receptionist
EventScript_RhodanziTrainerSchool_MainRoom_Receptionist:
    lock
    compare PLAYERFACING UP
    if TRUE _goto ReceptionistHelp
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_GoToDesk MSG_FACE
    applymovement 0x1 m_LookDown
    goto EndMovementAndEvent

ReceptionistHelp:
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist MSG_FACE
    applymovement 0x1 m_LookLeft
    applymovement PLAYER m_LookLeft
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Basic MSG_NORMAL
    applymovement 0x1 m_LookRight
    applymovement PLAYER m_LookRight
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Advanced MSG_NORMAL
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    msgbox gText_RhodanziTrainerSchool_MainRoom_Receptionist_Conclude MSG_FACE
    release
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_FossilStudent
EventScript_RhodanziTrainerSchool_MainRoom_FossilStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_FossilStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_Librarian
EventScript_RhodanziTrainerSchool_MainRoom_Librarian:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_Librarian m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_MainRoom_Professor
EventScript_RhodanziTrainerSchool_MainRoom_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_Professor m_LookRight
    end

.global EventScript_RhodanziTrainerSchool_TerrainTutor
EventScript_RhodanziTrainerSchool_TerrainTutor:
    faceplayer
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Intro MSG_NORMAL
    checkflag 0x820 @ Has Terrain Badge
    IF SET _goto TerrainTutor
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_DoesNotHaveBadge MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

TerrainTutor:
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Confirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 0x5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_ConfirmationAccepted MSG_KEEPOPEN
    call EventScript_Tutors_Terrain
    compare LASTRESULT TRUE
    if equal _call TutoringComplete
    applymovement LASTTALKED m_LookDown
    end

TutoringComplete:
    msgbox gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_ConfirmationRejected m_LookDown
    end

NotEnoughPokeChips:
    npcchatwithmovement gText_RhodanziTrainerSchool_MainRoom_TerrainTutor_NotEnoughPokeChips m_LookDown
    end

@ Basic Course
.global EventScript_RhodanziTrainerSchool_BasicCourse_Professor
EventScript_RhodanziTrainerSchool_BasicCourse_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_Professor m_LookDown
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent
EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent:
    lock
    faceplayer
    checkflag 0x230
    if NOT_SET _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuiz
    checkflag 0x230
    if SET _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuizComplete
    applymovement 0x2 m_LookUp
    waitmovement ALLEVENTS
    release
    end

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuiz:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizIntro MSG_YESNO
    compare LASTRESULT YES
    if FALSE _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestion
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestion:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizAccepted MSG_FACE
    compare 0x4031 0 @ Grass
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionGrass
    compare 0x4031 1 @ Fire
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionFire
    compare 0x4031 2 @ Water
    if TRUE _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionWater
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices:
    multichoiceoption gText_TypeGrass 0
    multichoiceoption gText_TypeFire 1
    multichoiceoption gText_TypeWater 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS 0x1
    copyvar MULTICHOICE_SELECTION LASTRESULT
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionGrass:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_GrassQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 2
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_MIRACLE_SEED 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionFire:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_FireQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 0
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_CHARCOAL 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizQuestionWater:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_WaterQuestion MSG_KEEPOPEN
    call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizChoices
    compare LASTRESULT 1
    if notequal _goto EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail
    if equal _call EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess
    obtainitem ITEM_MYSTIC_WATER 0x1
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_ItemInfo MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess:
    applymovement LASTTALKED m_Joy
    playse 0x19 @ Correct
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizSuccess MSG_FACE
    setflag 0x230
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail:
    applymovement LASTTALKED m_Wrong
    playse 0x1A @ Error
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizFail MSG_FACE
    return

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizRejected MSG_FACE
    applymovement 0x2 m_LookUp
    goto EndMovementAndEvent

EventScript_RhodanziTrainerSchool_BasicCourse_TypeStudentQuizComplete:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_TypeStudent_QuizComplete MSG_FACE
    return

.global EventScript_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent
EventScript_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_AbilitiesStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_KOStudent
EventScript_RhodanziTrainerSchool_BasicCourse_KOStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_KOStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent
EventScript_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_BasicCourse_HeldItemsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent
EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent:
    lock
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent MSG_FACE
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question
    end

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question MSG_KEEPOPEN
    multichoiceoption gText_Burn 0
    multichoiceoption gText_Frostbite 1
    multichoiceoption gText_Paralysis 2
    multichoiceoption gText_Poison 3
    multichoiceoption gText_Sleep 4
    multichoiceoption gText_End 5
    multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
    copyvar MULTICHOICE_SELECTION LASTRESULT
    switch LASTRESULT
    case 0, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Burn
    case 1, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Frostbite
    case 2, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Paralysis
    case 3, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Poison
    case 4, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Sleep
    case 5, EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done
    end

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Burn:
    msgbox gText_BurnDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Frostbite:
    msgbox gText_FrostbiteDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Paralysis:
    msgbox gText_ParalysisDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Poison:
    msgbox gText_PoisonDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Sleep:
    msgbox gText_SleepDetails MSG_NORMAL
    goto EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Question

EventScript_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done:
    msgbox gText_RhodanziTrainerSchool_BasicCourse_StatusStudent_Done MSG_NORMAL
    applymovement 0x6 m_LookUp
    goto EndMovementAndEvent

@ Advanced Course
.global EventScript_RhodanziTrainerSchool_AdvancedCourse_Professor
EventScript_RhodanziTrainerSchool_AdvancedCourse_Professor:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_Professor m_LookDown
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_BattleMovesStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_AutoRunStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_PokemonTypeStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_MegaEvolutionStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_TMsStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_TMsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_TMsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_HMsStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_HMsStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_HMsStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_DexNavStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent
EventScript_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_BadgeObedienceStudent m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_LastPokeball
EventScript_RhodanziTrainerSchool_AdvancedCourse_LastPokeball:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_LastPokeball m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_QuickRun
EventScript_RhodanziTrainerSchool_AdvancedCourse_QuickRun:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_QuickRun m_LookUp
    end

.global EventScript_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems
EventScript_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems:
    npcchatwithmovement gText_RhodanziTrainerSchool_AdvancedCourse_RegisterMultipleItems m_LookDown
    end
