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
    lock
    faceplayer
    checkflag 0x25D @ Player healed at this location
    if SET _goto HealPromptAfterInitialVisit
    msgbox gText_PlutoHQ_B2F_RestGrunt_Intro MSG_NORMAL
    goto HealingPromptAndHandling
    end

HealPromptAfterInitialVisit:
    msgbox gText_PlutoHQ_B2F_RestGrunt_IntroAfterAlreadyUsed MSG_NORMAL
    goto HealingPromptAndHandling
    end
    
HealingPromptAndHandling:
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
    setflag 0x25D @ Player healed at this location
    release
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

// Doors and Traps

.equ VeritcalTopLeftTile, 0x347
.equ VeritcalTopRightTile, 0x346
.equ VeritcalBottomLeftTile, 0x339
.equ VeritcalBottomRightTile, 0x33A
.equ HorizontalTiles_DarkBlue, 0x335
.equ HorizontalTiles_LightBlue, 0x334
.equ HorizontalTiles_DarkYellow, 0x282
.equ HorizontalTiles_LightYellow, 0x281
.equ Passable, 0x0
.equ Impassable, 0x1

.equ PlutoStoryEventVar, 0x405D

.global MapScript_PlutoBaseHQ_B1F
MapScript_PlutoBaseHQ_B1F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B1F_SecurityGates
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_PlutoBaseHQ_B1F_ShowAlistair
    mapscript MAP_SCRIPT_ON_FRAME_TABLE LevelScripts_PlutoHQEvents
    .byte MAP_SCRIPT_TERMIN

LevelScripts_PlutoHQEvents:
    levelscript PlutoStoryEventVar 0x2 LevelScript_AlistairApproachesPlayerInsideBase
    .hword LEVEL_SCRIPT_TERMIN

LevelScript_AlistairApproachesPlayerInsideBase:
    pause DELAY_HALFSECOND
    applymovement PLAYER m_PlayerWalkIntoBase
    waitmovement PLAYER
    applymovement 0x5 m_LookLeft
    pause DELAY_HALFSECOND
    applymovement 0x5 m_LookRight
    pause DELAY_HALFSECOND
    applymovement 0x5 m_AlistairWalksToPlayer
    waitmovement 0x5
    msgbox gText_PlutoHQ_AlistairMeetsWithPlayer MSG_NORMAL
    applymovement 0x5 m_AlistairLeaves
    waitmovement 0x5
    hidesprite 0x5
    setflag 0x3C @ Hide Alistair
    setvar PlutoStoryEventVar 0x3
    end

.global MapScript_PlutoBaseHQ_B1FHall
MapScript_PlutoBaseHQ_B1FHall:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B1FHall_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B2F
MapScript_PlutoBaseHQ_B2F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B2F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B3F
MapScript_PlutoBaseHQ_B3F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B3F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B4F
MapScript_PlutoBaseHQ_B4F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B4F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B5F
MapScript_PlutoBaseHQ_B5F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B5F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B6F
MapScript_PlutoBaseHQ_B6F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B6F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

.global MapScript_PlutoBaseHQ_B7F
MapScript_PlutoBaseHQ_B7F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_PlutoBaseHQ_B7F_SecurityGates
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_PlutoBaseHQ_B1F_SecurityGates:
    checkflag 0x200
    if SET _call HideB1FCerberusDoor
    end    

MapEntryScript_PlutoBaseHQ_B1F_ShowAlistair:
    compare PlutoStoryEventVar 0x2
    if equal _call ShowAlistairInBase
    end

ShowAlistairInBase:
    clearflag 0x3C @ Temporarily show Alistair
    showsprite 0x5 @ Alistair
    return

MapEntryScript_PlutoBaseHQ_B1FHall_SecurityGates:
    checkflag 0x201
    if SET _call HideB1FHallOwlDoor
    checkflag 0x202
    if SET _call HideB1FHallCypressDoor
    checkflag 0x203
    if SET _call HideB1FHallSerpentDoor
    checkflag 0x204
    if SET _call HideB1FHallCerberusDoor
    end

MapEntryScript_PlutoBaseHQ_B2F_SecurityGates:
    checkflag 0x205
    if SET _call HideB2FOwlDoor
    end

MapEntryScript_PlutoBaseHQ_B3F_SecurityGates:
    checkflag 0x206
    if SET _call HideB3FCypressDoor
    end

MapEntryScript_PlutoBaseHQ_B4F_SecurityGates:
    checkflag 0x207
    if SET _call HideB4FOwlDoor
    checkflag 0x208
    if SET _call HideB4FCerberusDoor
    end

MapEntryScript_PlutoBaseHQ_B5F_SecurityGates:
    checkflag 0x209
    if SET _call HideB5FCypressDoor
    end

MapEntryScript_PlutoBaseHQ_B6F_SecurityGates:
    checkflag 0x20A
    if SET _call HideB6FOwlDoor
    end

MapEntryScript_PlutoBaseHQ_B7F_SecurityGates:
    checkflag 0x20B
    if SET _call HideB7FCypressDoor
    checkflag 0x20C
    if SET _call HideB7FSerpentDoor
    end

.global SignScript_PlutoHQ_B1F_Floor
SignScript_PlutoHQ_B1F_Floor:
    msgbox PlutoHQ_B1F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B2F_Floor
SignScript_PlutoHQ_B2F_Floor:
    msgbox PlutoHQ_B2F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B3F_Floor
SignScript_PlutoHQ_B3F_Floor:
    msgbox PlutoHQ_B3F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B4F_Floor
SignScript_PlutoHQ_B4F_Floor:
    msgbox PlutoHQ_B4F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B5F_Floor
SignScript_PlutoHQ_B5F_Floor:
    msgbox PlutoHQ_B5F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B6F_Floor
SignScript_PlutoHQ_B6F_Floor:
    msgbox PlutoHQ_B6F_FloorSign MSG_SIGN
    end

.global SignScript_PlutoHQ_B1F_CerberusDoor
SignScript_PlutoHQ_B1F_CerberusDoor:
    checkflag 0x200
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x200
    end

.global SignScript_PlutoHQ_B1F_Hall_OwlDoor
SignScript_PlutoHQ_B1F_Hall_OwlDoor:
    checkflag 0x201
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x201
    end

.global SignScript_PlutoHQ_B1F_Hall_CypressDoor
SignScript_PlutoHQ_B1F_Hall_CypressDoor:
    checkflag 0x202
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x202
    end

.global SignScript_PlutoHQ_B1F_Hall_SerpentDoor
SignScript_PlutoHQ_B1F_Hall_SerpentDoor:
    checkflag 0x203
    if SET _goto End
    msgbox PlutoHQ_SerpentDoorSign MSG_NORMAL
    checkitem ITEM_SERPENT_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallSerpentDoor
    special 0x8E
    bufferitem 0x0 ITEM_SERPENT_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x203
    end

.global SignScript_PlutoHQ_B1F_Hall_CerberusDoor
SignScript_PlutoHQ_B1F_Hall_CerberusDoor:
    checkflag 0x204
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB1FHallCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x204
    end

.global SignScript_PlutoHQ_B2F_OwlDoor
SignScript_PlutoHQ_B2F_OwlDoor:
    checkflag 0x205
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB2FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x205
    end

.global SignScript_PlutoHQ_B3F_CypressDoor
SignScript_PlutoHQ_B3F_CypressDoor:
    checkflag 0x206
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB3FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x206
    end

.global SignScript_PlutoHQ_B4F_OwlDoor
SignScript_PlutoHQ_B4F_OwlDoor:
    checkflag 0x207
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB4FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x207
    end

.global SignScript_PlutoHQ_B4F_CerberusDoor
SignScript_PlutoHQ_B4F_CerberusDoor:
    checkflag 0x208
    if SET _goto End
    msgbox PlutoHQ_CerberusDoorSign MSG_NORMAL
    checkitem ITEM_CERBERUS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB4FCerberusDoor
    special 0x8E
    bufferitem 0x0 ITEM_CERBERUS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x208
    end

.global SignScript_PlutoHQ_B5F_CypressDoor
SignScript_PlutoHQ_B5F_CypressDoor:
    checkflag 0x209
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB5FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x209
    end

.global SignScript_PlutoHQ_B6F_OwlDoor
SignScript_PlutoHQ_B6F_OwlDoor:
    checkflag 0x20A
    if SET _goto End
    msgbox PlutoHQ_OwlDoorSign MSG_NORMAL
    checkitem ITEM_OWL_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB6FOwlDoor
    special 0x8E
    bufferitem 0x0 ITEM_OWL_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20A
    end

.global SignScript_PlutoHQ_B7F_CypressDoor
SignScript_PlutoHQ_B7F_CypressDoor:
    checkflag 0x20B
    if SET _goto End
    msgbox PlutoHQ_CypressDoorSign MSG_NORMAL
    checkitem ITEM_CYPRESS_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB7FCypressDoor
    special 0x8E
    bufferitem 0x0 ITEM_CYPRESS_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20B
    end

.global SignScript_PlutoHQ_B7F_SerpentDoor
SignScript_PlutoHQ_B7F_SerpentDoor:
    checkflag 0x20C
    if SET _goto End
    msgbox PlutoHQ_SerpentDoorSign MSG_NORMAL
    checkitem ITEM_SERPENT_KEY 0x1
    compare LASTRESULT FALSE
    if equal _goto End
    playse 0x8 @ Door open
    waitse
    call HideB7FSerpentDoor
    special 0x8E
    bufferitem 0x0 ITEM_SERPENT_KEY
    msgbox PlutoHQ_DoorOpened MSG_NORMAL
    setflag 0x20C
    end

HideB1FCerberusDoor:
    setmaptile 0x1A 0xA VeritcalTopLeftTile Impassable
    setmaptile 0x1B 0xA VeritcalTopRightTile Impassable
    setmaptile 0x1A 0xB HorizontalTiles_DarkBlue Passable
    setmaptile 0x1B 0xB HorizontalTiles_DarkBlue Passable
    setmaptile 0x1A 0xC VeritcalBottomLeftTile Passable
    setmaptile 0x1B 0xC VeritcalBottomRightTile Passable
    return

HideB1FHallOwlDoor:
    setmaptile 0x2 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x10 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x11 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x11 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x11 HorizontalTiles_LightBlue Passable
    return

HideB1FHallCypressDoor:
    setmaptile 0x2 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xC HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xD HorizontalTiles_LightBlue Passable
    return

HideB1FHallSerpentDoor:
    setmaptile 0x2 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x9 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x9 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x9 HorizontalTiles_LightBlue Passable
    return

HideB1FHallCerberusDoor:
    setmaptile 0x2 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x4 HorizontalTiles_LightBlue Passable
    setmaptile 0x2 0x5 HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0x5 HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0x5 HorizontalTiles_LightBlue Passable
    return

HideB2FOwlDoor:
    setmaptile 0x9 0xC VeritcalTopLeftTile Impassable
    setmaptile 0xA 0xC VeritcalTopRightTile Impassable
    setmaptile 0x9 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0xA 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0x9 0xE VeritcalBottomLeftTile Passable
    setmaptile 0xA 0xE VeritcalBottomRightTile Passable
    return

HideB3FCypressDoor:
    setmaptile 0x1D 0x10 VeritcalTopLeftTile Impassable
    setmaptile 0x1E 0x10 VeritcalTopRightTile Impassable
    setmaptile 0x1D 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1E 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1D 0x12 VeritcalBottomLeftTile Passable
    setmaptile 0x1E 0x12 VeritcalBottomRightTile Passable
    return

HideB4FOwlDoor:
    setmaptile 0x11 0x6 HorizontalTiles_DarkBlue Passable
    setmaptile 0x12 0x6 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x6 HorizontalTiles_LightBlue Passable
    setmaptile 0x11 0x7 HorizontalTiles_DarkBlue Passable
    setmaptile 0x12 0x7 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x7 HorizontalTiles_LightBlue Passable
    setmaptile 0x12 0x8 HorizontalTiles_LightBlue Passable
    setmaptile 0x13 0x8 HorizontalTiles_LightBlue Passable
    return

HideB4FCerberusDoor:
    setmaptile 0x3 0xD HorizontalTiles_DarkBlue Passable
    setmaptile 0x4 0xD HorizontalTiles_LightBlue Passable
    setmaptile 0x3 0xE HorizontalTiles_DarkBlue Passable
    setmaptile 0x4 0xE HorizontalTiles_LightBlue Passable
    setmaptile 0x4 0xF HorizontalTiles_LightBlue Passable
    return

HideB5FCypressDoor:
    setmaptile 0x20 0x12 HorizontalTiles_DarkBlue Passable
    setmaptile 0x21 0x12 HorizontalTiles_LightBlue Passable
    setmaptile 0x20 0x13 HorizontalTiles_DarkBlue Passable
    setmaptile 0x21 0x13 HorizontalTiles_LightBlue Passable
    setmaptile 0x21 0x14 HorizontalTiles_LightBlue Passable
    return

HideB6FOwlDoor:
    setmaptile 0x1C 0x10 VeritcalTopLeftTile Impassable
    setmaptile 0x1D 0x10 VeritcalTopRightTile Impassable
    setmaptile 0x1C 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1D 0x11 HorizontalTiles_DarkBlue Passable
    setmaptile 0x1C 0x12 VeritcalBottomLeftTile Passable
    setmaptile 0x1D 0x12 VeritcalBottomRightTile Passable
    return

HideB7FCypressDoor:
    setmaptile 0x11 0x6 HorizontalTiles_DarkYellow Passable
    setmaptile 0x12 0x6 HorizontalTiles_LightYellow Passable
    setmaptile 0x13 0x6 HorizontalTiles_LightYellow Passable
    return

HideB7FSerpentDoor:
    setmaptile 0x1E 0xD HorizontalTiles_DarkYellow Passable
    setmaptile 0x1F 0xD HorizontalTiles_LightYellow Passable
    setmaptile 0x1E 0xE HorizontalTiles_DarkYellow Passable
    setmaptile 0x1F 0xE HorizontalTiles_LightYellow Passable
    setmaptile 0x1F 0xF HorizontalTiles_LightYellow Passable
    return

# Door code logic ends here!

.global SignScript_PlutoHQ_B3F_StatueSwitch
SignScript_PlutoHQ_B3F_StatueSwitch:
    msgbox gText_PlutoHQ_StatueTrapMachine MSG_NORMAL
    compare 0x409B 0x0
    if equal _goto MachineIsOn
    goto MachineIsOff
    end

MachineIsOn:
    msgbox gText_PlutoHQ_StatueTrapMachine_IsOn MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotChangingMachineState
    playse 0x2A @ Turn switch flip
    msgbox gText_PlutoHQ_StatueTrapMachine_TurnedOff MSG_NORMAL
    setvar 0x409B 0x1 @ Off
    end

MachineIsOff:
    msgbox gText_PlutoHQ_StatueTrapMachine_IsOff MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotChangingMachineState
    playse 0x2A @ Turn switch flip
    msgbox gText_PlutoHQ_StatueTrapMachine_TurnedOn MSG_NORMAL
    setvar 0x409B 0x0 @ On
    end

NotChangingMachineState:
    msgbox gText_PlutoHQ_StatueTrapMachine_ChoseNotTo MSG_NORMAL
    end

.global TileScript_PlutoHQ_WildBattle
TileScript_PlutoHQ_WildBattle:
    lock
    call ChooseWildSpecies
    checksound
    cry 0x4000 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_PlutoHQ_WildPokemon MSG_KEEPOPEN
    wildbattle 0x4000 40 0x0
    release
    end

ChooseWildSpecies:
    random 0x3
    compare LASTRESULT 0x0
    if equal _call SetKoffing
    compare LASTRESULT 0x1
    if equal _call SetRattata
    compare LASTRESULT 0x2
    if equal _call SetZubat
    return

SetKoffing:
    setvar 0x4000 SPECIES_KOFFING_G
    return

SetRattata:
    setvar 0x4000 SPECIES_RATTATA_A
    return

SetZubat:
    setvar 0x4000 SPECIES_ZUBAT
    return

m_PlayerWalkIntoBase: .byte walk_left, walk_left, look_up, end_m
m_AlistairWalksToPlayer: .byte walk_down, walk_down, end_m
m_AlistairLeaves: .byte walk_up, walk_up, walk_up, walk_up, walk_up, end_m
