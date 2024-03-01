.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Kurtis, 0x1
.equ Alistair, 0x3
.equ Irene, 0x4
.equ Ronald, 0x5
.equ PlutoStoryEventVar, 0x405D

## B1F
.global EventScript_PlutoHQ_B1F_TM59BrutalSwing
EventScript_PlutoHQ_B1F_TM59BrutalSwing:
    setvar CHOSEN_ITEM ITEM_TM59
    call ItemScript_Common_FindTM
    end

.global EventScript_PlutoHQ_B1F_TeamPlutoHeathcliff
EventScript_PlutoHQ_B1F_TeamPlutoHeathcliff:
    trainerbattle0 0x0 291 0x0 gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Intro gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Defeat
    msgbox gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B1F_ScientistSeamus
EventScript_PlutoHQ_B1F_ScientistSeamus:
    trainerbattle0 0x0 292 0x0 gText_PlutoHQ_B1F_ScientistSeamus_Intro gText_PlutoHQ_B1F_ScientistSeamus_Defeat
    msgbox gText_PlutoHQ_B1F_ScientistSeamus_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B1F_TeamPlutoColton
EventScript_PlutoHQ_B1F_TeamPlutoColton:
    trainerbattle0 0x0 293 0x0 gText_PlutoHQ_B1F_TeamPlutoColton_Intro gText_PlutoHQ_B1F_TeamPlutoColton_Defeat
    msgbox gText_PlutoHQ_B1F_TeamPlutoColton_Chat MSG_NORMAL
    end

## B1F Hall
.global TileScript_PlutoHQ_B1F_Hall_KurtisWarning
TileScript_PlutoHQ_B1F_Hall_KurtisWarning:
    lock
    msgbox gText_PlutoHQ_B1F_Hall_KurtissWarning MSG_NORMAL
    setvar 0x409C 0x1
    release
    end

## B2F
.global EventScript_PlutoHQ_B2F_ScientistWayne
EventScript_PlutoHQ_B2F_ScientistWayne:
    trainerbattle0 0x0 294 0x0 gText_PlutoHQ_B2F_ScientistWayne_Intro gText_PlutoHQ_B2F_ScientistWayne_Defeat
    msgbox gText_PlutoHQ_B2F_ScientistWayne_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B2F_TeamPlutoDenise
EventScript_PlutoHQ_B2F_TeamPlutoDenise:
    trainerbattle0 0x0 295 0x0 gText_PlutoHQ_B2F_TeamPlutoDenise_Intro gText_PlutoHQ_B2F_TeamPlutoDenise_Defeat
    msgbox gText_PlutoHQ_B2F_TeamPlutoDenise_Chat MSG_NORMAL
    end
    
.global EventScript_PlutoHQ_B2F_TeamPlutoTheodore
EventScript_PlutoHQ_B2F_TeamPlutoTheodore:
    trainerbattle0 0x0 296 0x0 gText_PlutoHQ_B2F_TeamPlutoTheodore_Intro gText_PlutoHQ_B2F_TeamPlutoTheodore_Defeat
    msgbox gText_PlutoHQ_B2F_TeamPlutoTheodore_Chat MSG_NORMAL
    end

## B3F
.global EventScript_PlutoHQ_B3F_RestGrunt
EventScript_PlutoHQ_B3F_RestGrunt:
    faceplayer
    msgbox gText_PlutoHQ_B2F_RestGrunt_Intro MSG_NORMAL
    showmoney 0x0 0x0
    msgbox gText_PlutoHQ_B2F_RestGrunt_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToHeal
    checkmoney 500
    compare LASTRESULT FALSE
    if equal _goto NotEnoughMoney
    removemoney 500
    updatemoney 0x0 0x0
    sound 0xF8 @ Money SE
    waitse
    msgbox gText_PlutoHQ_B2F_RestGrunt_PaymentReceived MSG_NORMAL
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_ChoseYes MSG_NORMAL
    call PlayerHeal
    msgbox gText_PlutoHQ_B2F_RestGrunt_AfterHeal MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

NotEnoughMoney:
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_NotEnoughMoney MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

ChoseNotToHeal:
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_ChoseNo MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

.global EventScript_PlutoHQ_B3F_TeamPlutoYeon
EventScript_PlutoHQ_B3F_TeamPlutoYeon:
    trainerbattle0 0x0 297 0x0 gText_PlutoHQ_B3F_TeamPlutoYeon_Intro gText_PlutoHQ_B3F_TeamPlutoYeon_Defeat
    msgbox gText_PlutoHQ_B3F_TeamPlutoYeon_Chat MSG_NORMAL
    end

## B4F
.global EventScript_PlutoHQ_B4F_CypressKey
EventScript_PlutoHQ_B4F_CypressKey:
    finditem ITEM_CYPRESS_KEY 0x1
    end

.global EventScript_PlutoHQ_B4F_CoffeBreakFemaleGrunt
EventScript_PlutoHQ_B4F_CoffeBreakFemaleGrunt:
    npcchatwithmovement gText_PlutoHQ_B3F_CoffeeBreakFemaleGrunt m_LookLeft
    end

.global EventScript_PlutoHQ_B4F_CoffeeBreakMaleGrunt    
EventScript_PlutoHQ_B4F_CoffeeBreakMaleGrunt:
    npcchatwithmovement gText_PlutoHQ_B3F_CoffeeBreakMaleGrunt m_LookRight
    end

.global EventScript_PlutoHQ_B4F_TeamPlutoMatty
EventScript_PlutoHQ_B4F_TeamPlutoMatty:
    trainerbattle0 0x0 298 0x0 gText_PlutoHQ_B4F_TeamPlutoMatty_Intro gText_PlutoHQ_B4F_TeamPlutoMatty_Defeat
    msgbox gText_PlutoHQ_B4F_TeamPlutoMatty_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B4F_ScientistGary
EventScript_PlutoHQ_B4F_ScientistGary:
    trainerbattle0 0x0 299 0x0 gText_PlutoHQ_B4F_ScientistGary_Intro gText_PlutoHQ_B4F_ScientistGary_Defeat
    msgbox gText_PlutoHQ_B4F_ScientistGary_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B4F_TeamPlutoMay
EventScript_PlutoHQ_B4F_TeamPlutoMay:
    trainerbattle0 0x0 300 0x0 gText_PlutoHQ_B4F_TeamPlutoMay_Intro gText_PlutoHQ_B4F_TeamPlutoMay_Defeat
    msgbox gText_PlutoHQ_B4F_TeamPlutoMay_Chat MSG_NORMAL
    end

## B5F
.global EventScript_PlutoHQ_B5F_OwlKey
EventScript_PlutoHQ_B5F_OwlKey:
    finditem ITEM_OWL_KEY 0x1
    end

.global EventScript_PlutoHQ_B5F_TM100Confide
EventScript_PlutoHQ_B5F_TM100Confide:
    setvar CHOSEN_ITEM ITEM_TM100
    call ItemScript_Common_FindTM
    end

.global EventScript_PlutoHQ_B5F_TeamPlutoClay
EventScript_PlutoHQ_B5F_TeamPlutoClay:
    trainerbattle0 0x0 301 0x0 gText_PlutoHQ_B5F_TeamPlutoClay_Intro gText_PlutoHQ_B5F_TeamPlutoClay_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoClay_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B5F_TeamPlutoVictor
EventScript_PlutoHQ_B5F_TeamPlutoVictor:
    trainerbattle0 0x0 302 0x0 gText_PlutoHQ_B5F_TeamPlutoVictor_Intro gText_PlutoHQ_B5F_TeamPlutoVictor_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoVictor_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B5F_TeamPluto_Paula
EventScript_PlutoHQ_B5F_TeamPluto_Paula:
    trainerbattle0 0x0 303 0x0 gText_PlutoHQ_B5F_TeamPlutoPaula_Intro gText_PlutoHQ_B5F_TeamPlutoPaula_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoPaula_Chat MSG_NORMAL
    end

## B6F
.global EventScript_PlutoHQ_B6F_TeamPlutoGiana
EventScript_PlutoHQ_B6F_TeamPlutoGiana:
    trainerbattle0 0x0 304 0x0 gText_PlutoHQ_B6F_TeamPlutoGiana_Intro gText_PlutoHQ_B6F_TeamPlutoGiana_Defeat
    msgbox gText_PlutoHQ_B6F_TeamPlutoGiana_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B6F_ScientistOrson
EventScript_PlutoHQ_B6F_ScientistOrson:
    trainerbattle0 0x0 305 0x0 gText_PlutoHQ_B6F_ScientistOrson_Intro gText_PlutoHQ_B6F_ScientistOrson_Defeat
    msgbox gText_PlutoHQ_B6F_ScientistOrson_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B6F_TeamPlutoQuinn
EventScript_PlutoHQ_B6F_TeamPlutoQuinn:
    trainerbattle0 0x0 306 0x0 gText_PlutoHQ_B6F_TeamPlutoQuinn_Intro gText_PlutoHQ_B6F_TeamPlutoQuinn_Defeat
    msgbox gText_PlutoHQ_B6F_TeamPlutoQuinn_Chat MSG_NORMAL
    end

## B7F
.global EventScript_PlutoHQ_B7F_TeamPlutoLayla
EventScript_PlutoHQ_B7F_TeamPlutoLayla:
    trainerbattle0 0x0 307 0x0 gText_PlutoHQ_B7F_TeamPlutoLayla_Intro gText_PlutoHQ_B7F_TeamPlutoLayla_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoLayla_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_ScientistNico
EventScript_PlutoHQ_B7F_ScientistNico:
    trainerbattle0 0x0 308 0x0 gText_PlutoHQ_B7F_ScientistNico_Intro gText_PlutoHQ_B7F_ScientistNico_Defeat
    msgbox gText_PlutoHQ_B7F_ScientistNico_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_TeamPlutoMitch
EventScript_PlutoHQ_B7F_TeamPlutoMitch:
    trainerbattle0 0x0 309 0x0 gText_PlutoHQ_B7F_TeamPlutoMitch_Intro gText_PlutoHQ_B7F_TeamPlutoMitch_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoMitch_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_TeamPlutoRichard
EventScript_PlutoHQ_B7F_TeamPlutoRichard:
    trainerbattle0 0x0 310 0x0 gText_PlutoHQ_B7F_TeamPlutoRichard_Intro gText_PlutoHQ_B7F_TeamPlutoRichard_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoRichard_Chat MSG_NORMAL
    end

## Irene's office
.global EventScript_PlutoHQ_B4F_Irene
EventScript_PlutoHQ_B4F_Irene:
    faceplayer
    checkitem ITEM_SERPENT_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto IreneDefeated
    playbgm 0x19A @ Team Pluto Theme
    msgbox gText_PlutoHQ_B4F_AdminIreneConversation MSG_NORMAL
    msgbox gText_PlutoHQ_B4F_AdminIreneConversation_PreBattle MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 311 0x100 gText_PlutoHQ_B4F_AdminIreneConversation_BattleLost
    msgbox gText_PlutoHQ_B4F_AdminIreneConversation_PostBattle MSG_NORMAL
    obtainitem ITEM_SERPENT_KEY 0x1
    goto IreneDefeated
    end

IreneDefeated:
    msgbox gText_PlutoHQ_B4F_AdminIreneConversation_AfterSerpentKey MSG_NORMAL
    end

## Ronald's office
.global EventScript_PlutoHQ_B7F_Ronald
EventScript_PlutoHQ_B7F_Ronald:
    faceplayer
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT TRUE
    if equal _goto RonaldDefeated
    playbgm 0x19A @ Team Pluto Theme
    msgbox gText_PlutoHQ_B7F_AdminRonaldConversation MSG_NORMAL
    msgbox gText_PlutoHQ_B7F_AdminRonaldConversation_PreBattle MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 312 0x100 gText_PlutoHQ_B7F_AdminRonaldConversation_BattleLost
    msgbox gText_PlutoHQ_B4F_AdminRonaldConversation_PostBattle MSG_NORMAL
    obtainitem ITEM_CERBERUS_KEY 0x1
    goto RonaldDefeated
    end

RonaldDefeated:
    msgbox gText_PlutoHQ_B7F_AdminRonaldConversation_AfterCerberusKey MSG_NORMAL
    end

## Kurtis's Office
.global MapScript_PlutoHQ_KurtisOffice
MapScript_PlutoHQ_KurtisOffice:
    mapscript MAP_SCRIPT_ON_TRANSITION MapScript_FixGyaradosite
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_PlutoHQKurtisEvent
    .byte MAP_SCRIPT_TERMIN

MapScript_FixGyaradosite:
    compare PlutoStoryEventVar 0x4
    if notequal _goto End
    clearflag 0x21B
    showsprite 0x2
    end

LevelScripts_PlutoHQKurtisEvent:
    levelscript PlutoStoryEventVar 0x3 LevelScript_ChallengingKurtis
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_ChallengingKurtis:
    hidesprite 0x2 @ Gyaradosite
    pause DELAY_HALFSECOND
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisSeesPlayer MSG_NORMAL
    applymovement PLAYER m_PlayerApproachesKurtis
    waitmovement PLAYER
    special CAMERA_START
    applymovement CAMERA m_PlayerApproachesKurtis
    waitmovement CAMERA
    special CAMERA_END
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisIntroduction MSG_NORMAL
    playbgm 0x185 @ Encounter Ghetsis
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisAnnouncesHimself MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairAnnouncesArrival MSG_NORMAL
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    showsprite Alistair
    applymovement Alistair m_AlistairMeetsWithPlayer
    playse 0x26 @ Door shut
    waitmovement Alistair
    applymovement PLAYER m_LookLeft
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairArrives MSG_NORMAL
    applymovement PLAYER m_LookUp
    applymovement Alistair m_LookUp
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisUpsetWithAlistairsArrival MSG_NORMAL
    applymovement Kurtis m_KurtisWalksToPhone
    waitmovement Kurtis
    playse 0x4 @ PC On
    waitse
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisCallsForIreneAndAlistair MSG_NORMAL
    playse 0x3 @ PC Off
    waitse
    applymovement Kurtis m_KurtisWalksBackToDesk
    waitmovement Kurtis
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisDenouncesThePlayerAndAlistair MSG_NORMAL
    applymovement Alistair m_AlistairWalksUpToKurtis
    waitmovement Alistair
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairInterrupts MSG_NORMAL
    applymovement Kurtis m_LookLeft
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisRespondsToAlistair MSG_NORMAL
    applymovement Kurtis m_LookDown
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisRevealsPlutosAmbitions MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairRespondsToKurtisGoals MSG_NORMAL
    applymovement Kurtis m_LookLeft
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisRespondsToAlistairsDisdain MSG_NORMAL
    applymovement Kurtis m_LookDown
    playse 0x8 @ Door open
    pause DELAY_HALFSECOND
    showsprite Irene
    applymovement Irene m_IreneArrives
    pause DELAY_HALFSECOND
    showsprite Ronald
    applymovement Ronald m_RonaldArrives
    playse 0x26 @ Door shut
    waitmovement Ronald
    applymovement PLAYER m_LookDown
    applymovement Alistair m_LookDown
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_IreneArrives MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_RonaldArrives MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisInitiatesFight MSG_NORMAL
    applymovement PLAYER m_LookUp
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairChallengesIreneAndRonald MSG_NORMAL
    applymovement Alistair m_WalkLeft
    waitmovement Alistair 
    applymovement Alistair m_LookDown
    applymovement Irene m_IreneChallengesAlistair
    applymovement Ronald m_RonaldChallengesAlistair
    pause DELAY_1SECOND
    applymovement PLAYER m_LookLeft
    waitmovement Ronald
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_IreneBattlesAlistair MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_RonaldBattlesAlistair MSG_NORMAL
    applymovement PLAYER m_LookUp
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_PreparesToChallengePlayer MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisPreBattle MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 313 0x100 gText_PlutoHQ_B1F_KurtisEncounter_KurtisLosesBattle
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisCommentsOnLoss MSG_NORMAL
    applymovement Irene m_LookRight
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_IreneCommentsOnLoss MSG_NORMAL
    applymovement Ronald m_LookRight
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_RonaldCommentsOnLoss MSG_NORMAL
    applymovement Irene m_LookUp
    applymovement Ronald m_LookUp
    applymovement Alistair m_LookRight
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairCommentsOnHisVictory MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisRemindsTheTwoAboutHisPlans MSG_NORMAL
    applymovement Alistair m_AlistairApproachesKurtis
    waitmovement Alistair
    applymovement Kurtis m_LookLeft
    playbgm 0x173 @ Alistair's Theme
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairRevealsHisPlan MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement Kurtis m_Surprise
    applymovement Irene m_Surprise
    applymovement Ronald m_Surprise
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairExplainsPlan MSG_NORMAL
    applymovement Kurtis m_LookDown
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_KurtisFlees MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_IreneFlees MSG_NORMAL
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_RonaldFlees MSG_NORMAL
    fadescreen FADEOUT_BLACK
    hidesprite Kurtis
    hidesprite Irene
    hidesprite Ronald
    clearflag 0x21B @ Show Gyaradosite
    showsprite 0x2 @ Gyaradosite
    fadescreen FADEIN_BLACK
    fadedefaultbgm
    pause DELAY_HALFSECOND
    applymovement Alistair m_LookDown
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairCommentsOnPlutosRetreat MSG_NORMAL
    applymovement Alistair m_AlistairReturnsToPlayer
    waitmovement Alistair
    applymovement PLAYER m_LookLeft
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairGivesPlayerSurfGift MSG_NORMAL
    obtainitem ITEM_HM03 0x1 @ Surf
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairExplainsGift MSG_NORMAL
    applymovement Alistair m_LookUp
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairPreparesToDestroyTheBase MSG_NORMAL
    fadescreen FADEOUT_BLACK
    hidesprite 0x2 @ Gyaradosite
    playse 0x9 @ Exit room
    waitse
    pause DELAY_HALFSECOND
    applymovement PLAYER m_PlayerAsCameraMovesUp
    applymovement Alistair m_AlistairMovesToBoxes
    waitmovement Alistair
    showsprite 0x2 @ Gyaradosite
    fadescreen FADEIN_BLACK
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairDestroysSnagMachines MSG_NORMAL
    applymovement Alistair m_AlistairMovesToPC
    waitmovement Alistair
    playse 0x2 @ PC Login
    waitse
    pause DELAY_1SECOND
    sound 0x15 @ Exclaim
    applymovement Alistair m_Surprise
    playbgm 0x17A @ The day I became king
    msgbox gText_PlutoHQ_B1F_KurtisEncounter_AlistairReadsAboutJirachi MSG_NORMAL
    pause DELAY_HALFSECOND
    fadescreen FADEOUT_BLACK
    setflag 0x4A @ Pluto grunts and admins should all disappear
    setvar PlutoStoryEventVar 0x4 @ Pluto events complete
    warpmuted 3 5 5 @ Warp back to Daimyn City outside the building 
    end

.global EventScript_PlutoHQ_B1F_Gyaradosite
EventScript_PlutoHQ_B1F_Gyaradosite:
    @ Note: These are workarounds because the gyaradosite keeps behaving oddly
    finditem ITEM_GYARADOSITE 0x1
    setvar PlutoStoryEventVar 0x5
    end

m_PlayerApproachesKurtis: .byte walk_up, walk_up, end_m
m_AlistairMeetsWithPlayer: .byte walk_up, walk_left, walk_up, look_right, end_m
m_KurtisWalksToPhone: .byte walk_down_slow, walk_left_slow, walk_left_slow, walk_left_slow, walk_up_slow, walk_up_slow, end_m
m_KurtisWalksBackToDesk: .byte walk_down_slow, walk_down_slow, walk_right_slow, walk_right_slow, walk_right_slow, walk_up_slow, look_down, end_m
m_AlistairWalksUpToKurtis: .byte walk_left, walk_left, walk_up, walk_up, walk_up, end_m
m_IreneArrives: .byte walk_up, walk_left, look_up, end_m
m_RonaldArrives: .byte walk_up, walk_right, look_up, end_m
m_IreneChallengesAlistair: .byte walk_left, walk_left, walk_up, walk_left, look_up, end_m
m_RonaldChallengesAlistair: .byte walk_left, walk_left, walk_left, walk_left, walk_up, end_m
m_AlistairApproachesKurtis: .byte walk_up, walk_right, walk_up, walk_right, end_m
m_AlistairReturnsToPlayer: .byte walk_left, walk_down, walk_down, walk_down, walk_down, walk_down, walk_right, walk_right, end_m
m_PlayerAsCameraMovesUp: .byte set_invisible, walk_up, walk_up, end_m
m_AlistairMovesToBoxes: .byte run_left, run_left, run_left, run_left, run_up, run_up, run_up, run_up, end_m
m_AlistairMovesToPC: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_up, walk_up, end_m
