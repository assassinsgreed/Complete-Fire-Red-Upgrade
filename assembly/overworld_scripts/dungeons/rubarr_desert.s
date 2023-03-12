.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ PlutoGruntClancy, 0x1E @ Person # 30
.equ PlutoGruntEna, 0x1F @ Person # 31
.equ PlutoAdminIrene, 0x20 @ Person # 32
.equ Rival, 0x21 @ Person # 33
.equ Route3RubarrStoryEventVar, 0x4057
.equ VarStoryPlayerBeatPluto, 0x2

.global MapScript_RubarrDesert
MapScript_RubarrDesert:
	mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_RubarrDesert_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_RubarrDesert_SetWeather
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RubarrDesert_FlightFlag:
    setworldmapflag 0x8A5
    setflag 0x34 @ Hide Rival and Irene
    end

MapEntryScript_RubarrDesert_SetWeather:
    @ Check time of day
    setvar 0x8001 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto SetAllWeatherTypes @ Is morning or day, set clear, sandstorm, or sunny
    @ Is evening or night, set clear skies or sandstorm only
    random 0x9 @ Between 0 and 9
    compare 0x800D 0x5 @ "6"
    if lessthan _call SetWeatherClear
    compare 0x800D 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    end

SetAllWeatherTypes:
    random 0x9 @ Between 0 and 9
    compare 0x800D 0x4 @ "5"
    if lessthan _call SetWeatherSunny
    compare 0x800D 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    @ Otherwise, leave as regular weather
    end

.global EventScript_RubarrDesert_NurseJaina
EventScript_RubarrDesert_NurseJaina:
    faceplayer
    checktrainerflag 0x517
    if SET _goto NurseJainaHeal
    trainerbattle1 0x0 0x17 0x0 gText_RubarrDesert_NurseJaina_Intro gText_RubarrDesert_NurseJaina_Defeat NurseJainaHeal
    call NurseJainaHeal

NurseJainaHeal:
    msgbox gText_RubarrDesert_NurseJaina_Chat MSG_NORMAL
    call PlayerHeal
    msgbox gText_RubarrDesert_NurseJaina_HealingComplete MSG_NORMAL
    end

.global EventScript_RubarrDesert_BirdKeeperNolan
EventScript_RubarrDesert_BirdKeeperNolan:
    trainerbattle0 0x0 0x18 0x0 gText_RubarrDesert_BirdKeeperNolan_Intro gText_RubarrDesert_BirdKeeperNolan_Defeat
    msgbox gText_RubarrDesert_BirdKeeperNolan_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_RuinManiacKent
EventScript_RubarrDesert_RuinManiacKent:
    trainerbattle0 0x0 0x19 0x0 gText_RubarrDesert_RuinManiacKent_Intro gText_RubarrDesert_RuinManiacKent_Defeat
    msgbox gText_RubarrDesert_RuinManiacKent_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_BlackBeltKobiyashi
EventScript_RubarrDesert_BlackBeltKobiyashi:
    trainerbattle0 0x0 0x1A 0x0 gText_RubarrDesert_BlackBeltKobiyashi_Intro gText_RubarrDesert_BlackBeltKobiyashi_Defeat
    msgbox gText_RubarrDesert_BlackBeltKobiyashi_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_RuinManiacAlbert
EventScript_RubarrDesert_RuinManiacAlbert:
    trainerbattle0 0x0 0x1B 0x0 gText_RubarrDesert_RuinManiacAlbert_Intro gText_RubarrDesert_RuinManiacAlbert_Defeat
    msgbox gText_RubarrDesert_RuinManiacAlbert_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TMFlameCharge
EventScript_RubarrDesert_TMFlameCharge:
    setvar CHOSEN_ITEM ITEM_TM43
    call ItemScript_Common_FindTM
    end

.global EventScript_RubarrDesert_CaveGuide
EventScript_RubarrDesert_CaveGuide:
    faceplayer
    lockall    
    msgbox gText_RubarrDesert_TourGuideIntro MSG_YESNO
    compare LASTRESULT YES
    if true _call EventScript_RubarrDesert_CaveGuide_Info
    msgbox gText_RubarrDesert_TourGuideFarewell MSG_NORMAL
    release
    end

EventScript_RubarrDesert_CaveGuide_Info:
    msgbox gText_RubarrDesert_TourGuideDetails MSG_NORMAL
    return

.global SignScript_RubarrDesert_Oasis
SignScript_RubarrDesert_Oasis:
    msgbox gText_RubarrDesert_OasisSign MSG_SIGN
    end

.global EventScript_RubarrDesert_TeamPlutoMika
EventScript_RubarrDesert_TeamPlutoMika:
    trainerbattle0 0x0 0x1E 0x0 gText_RubarrDesert_TeamPlutoMika_Intro gText_RubarrDesert_TeamPlutoMika_Defeat
    msgbox gText_RubarrDesert_TeamPlutoMika_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TeamPlutoMarcel
EventScript_RubarrDesert_TeamPlutoMarcel:
    trainerbattle0 0x0 0x1F 0x0 gText_RubarrDesert_TeamPlutoMarcel_Intro gText_RubarrDesert_TeamPlutoMarcel_Defeat
    msgbox gText_RubarrDesert_TeamPlutoMarcel_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_TeamPlutoTana
EventScript_RubarrDesert_TeamPlutoTana:
    trainerbattle0 0x0 0x20 0x0 gText_RubarrDesert_TeamPlutoTana_Intro gText_RubarrDesert_TeamPlutoTana_Defeat
    msgbox gText_RubarrDesert_TeamPlutoTana_Chat MSG_NORMAL
    end

.global EventScript_RubarrDesert_StoryEvents
EventScript_RubarrDesert_StoryEvents:
    lock
    playbgm 0x19A @ Encounter Team Pluto
    msgbox gText_RubarrDesert_ClancyIntro MSG_NORMAL
    msgbox gText_RubarrDesert_EnaIntro MSG_NORMAL
    faceplayer
    compare LASTTALKED PlutoGruntClancy
    if equal _call ClancyComment
    compare LASTTALKED PlutoGruntEna
    if equal _call EnaComment
    call PositionPlayerForRubarrStoryEventsMain
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    msgbox gText_RubarrDersert_ClancyCommentsOnPlayer MSG_NORMAL
    msgbox gText_RubarrDersert_EnaCommentsOnPlayer MSG_NORMAL
    clearflag 0x34 @ Show Rival and Irene
    showsprite Rival
    showsprite PlutoAdminIrene
    movesprite Rival 0x30 0x1B
    movesprite PlutoAdminIrene 0x30 0x1C
    applymovement Rival m_RivalRunsToMeetPlayer
    waitmovement ALLEVENTS
    applymovement PLAYER m_LookLeft
    msgbox gText_RubarrDesert_RivalArrives MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    msgbox gText_RubarrDesert_RivalNoticesThugs MSG_NORMAL
    applymovement PlutoGruntClancy m_ClancyAngry
    msgbox gText_RubarrDesert_ClancyBeratesRival MSG_NORMAL
    msgbox gText_RubarrDesert_RivalDemandsDexNavs MSG_NORMAL
    msgbox gText_RubarrDesert_EnaBeratesRival MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_RubarrDesert_RivalReadyToFight MSG_NORMAL
    call PlayerHeal
    msgbox gText_RubarrDesert_RivalStartsFight MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    @ Start a tag battle (0x10) against Clancy (0x21) and Ena (0x22), with Rival (0x1C) using backsprite (0x6)
    trainerbattle10 0x10 0x21 0x22 0x1C 0x6 0x0 gText_RubarrDesert_ClancyLoses gText_RubarrDesert_EnaLoses
    playbgm 0x19A @ Encounter Team Pluto
    msgbox gText_RubarrDesert_ClancyPoorLoser MSG_NORMAL
    applymovement PlutoGruntClancy m_Surprise
    applymovement PlutoGruntEna m_Surprise
    msgbox gText_RubarrDesert_IreneArrives MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_RubarrDesert_ClancyScared MSG_NORMAL
    msgbox gText_RubarrDesert_EnaScared MSG_NORMAL
    applymovement Rival m_Surprise
    msgbox gText_RubarrDesert_RivalConfused MSG_NORMAL
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    msgbox gText_RubarrDesert_ClancyHushesRival MSG_NORMAL
    applymovement PlutoGruntClancy m_LookLeft
    applymovement PlutoGruntEna m_LookLeft
    applymovement PlutoAdminIrene m_IreneWalksUp
    waitmovement ALLEVENTS
    msgbox gText_RubarrDesert_IreneDemandsReport MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyBootlicks MSG_NORMAL
    msgbox gText_RubarrDesert_IreneRepeats MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyReport MSG_NORMAL
    applymovement PlutoGruntClancy m_Surprise
    msgbox gText_RubarrDesert_ClancySurprise MSG_NORMAL
    msgbox gText_RubarrDesert_EnaResponse MSG_NORMAL
    msgbox gText_RubarrDesert_IreneFollowsUpEnasQuestion MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyMentionsPokemonIsGone MSG_NORMAL
    msgbox gText_RubarrDesert_IreneClarifies MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyBlamesThePlayer MSG_NORMAL
    applymovement PlutoAdminIrene m_LookDown
    applymovement PlutoAdminIrene m_Question
    msgbox gText_RubarrDesert_IreneAlsoBlamesThePlayer MSG_NORMAL
    applymovement PlutoAdminIrene m_LookRight
    msgbox gText_RubarrDesert_IreneDemandsGruntsMove MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyAndEnaMove MSG_NORMAL
    applymovement PlutoGruntEna m_IreneApproachesPlayer
    applymovement PlutoGruntClancy m_IreneApproachesPlayer
    applymovement PlutoAdminIrene m_IreneApproachesPlayer
    msgbox gText_RubarrDesert_IreneIntroduction MSG_YESNO
    compare LASTRESULT YES
    if equal _call PlayerTakesTheBlame
    compare LASTRESULT NO
    if equal _call PlayerDeflectsTheBlame
    msgbox gText_RubarrDesert_IreneBattles MSG_NORMAL
    msgbox gText_RubarrDesert_RivalFightsWithPlayer MSG_NORMAL
    setvar 0x503A 0x1
    setvar 0x503B 0x1
    @ Start a tag battle against Admin Irene
    trainerbattle12 0x0 0x23 0x1C 0x6 0x100 gText_RubarrDesert_IreneBattleDefeat
    playbgm 0x19A @ Encounter Team Pluto
    msgbox gText_RubarrDesert_IreneSurprisedByPlayer MSG_NORMAL
    applymovement PlutoAdminIrene m_LookRight
    applymovement PlutoGruntClancy m_LookLeft
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_RubarrDesert_IreneConfirmsPokemonIsGone MSG_NORMAL
    msgbox gText_RubarrDesert_ClancyConfirmsPokemonIsGone MSG_NORMAL
    msgbox gText_RubarrDesert_IreneTellsGruntsTheyAreLeaving MSG_NORMAL
    applymovement PlutoAdminIrene m_LookDown
    msgbox gText_RubarrDesert_IreneThreatensPlayer MSG_NORMAL
    applymovement Rival m_LookLeft
    applymovement PLAYER m_LookLeft
    applymovement PlutoAdminIrene m_IreneLeaves
    waitmovement ALLEVENTS
    applymovement Rival m_LookRight
    msgbox gText_RubarrDesert_RivalCommentsOnBattle MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_RubarrDesert_ClancyCommentsOnDay MSG_NORMAL
    msgbox gText_RubarrDesert_EnaCallsDexNavsDefects MSG_NORMAL
    applymovement PlutoGruntClancy m_Surprise
    msgbox gText_RubarrDesert_ClancyAgreesAboutDefects MSG_NORMAL
    applymovement PlutoGruntEna m_Joy
    msgbox gText_RubarrDesert_EnaAcceptsCompliment MSG_NORMAL
    applymovement PlutoGruntClancy m_WalkLeft
    waitmovement ALLEVENTS
    applymovement PlutoGruntClancy m_LookDown
    applymovement PlutoGruntEna m_LookDown
    applymovement PLAYER m_LookUp
    applymovement Rival m_LookUp
    msgbox gText_RubarrDesert_ClancyGivesUpDexNavs MSG_NORMAL
    fanfare 0x13E
    msgbox gText_RubarrDesert_GetDexNavs MSG_KEEPOPEN
    waitfanfare
    applymovement PlutoGruntClancy m_LookRight
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_RubarrDesert_ClancyLeaves MSG_NORMAL
    msgbox gText_RubarrDesert_EnaLeaves MSG_NORMAL
    fadescreenswapbuffers 0x01 @ Fade out
    playse 0x11 @ SE Flee
    hidesprite PlutoGruntClancy
    hidesprite PlutoGruntEna
    fadedefaultbgm
    fadescreenswapbuffers 0x00 @ Fade in
    msgbox gText_RubarrDesert_RivalCommentsOnDexNavs MSG_NORMAL
    applymovement Rival m_LookRight
    applymovement PLAYER m_LookLeft
    msgbox gText_RubarrDesert_RivalHealsAgain MSG_NORMAL
    call PlayerHeal
    msgbox gText_RubarrDesert_RivalLeaves MSG_NORMAL
    applymovement Rival m_RivalLeaves
    waitmovement ALLEVENTS
    hidesprite Rival
    hidesprite PlutoAdminIrene
    setflag 0x33 @ Hide Team Pluto
    setflag 0x34 @ Hide Rival and Irene
    setvar Route3RubarrStoryEventVar VarStoryPlayerBeatPluto
    end

ClancyComment:
    msgbox gText_RubarrDesert_ClancyRecognizesPlayer MSG_NORMAL
    return

EnaComment:
    msgbox gText_RubarrDesert_EnaRecognizesPlayer MSG_NORMAL
    return

PositionPlayerForRubarrStoryEventsMain:
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x15
    if lessorequal _call PositionPlayerForRubarrStoryEventsCheckAboveGrunts
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x37
    if equal _call PlayerWalkRight_Return
    applymovement PLAYER m_LookUp
    waitmovement ALLEVENTS
    return

PositionPlayerForRubarrStoryEventsCheckAboveGrunts:
    compare 0x4000 0x38
    if equal _call PlayerWalkRight_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x37
    if equal _call PlayerWalkLeft_Return
    call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0x15
    if equal _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x39
    if equal _call PlayerWalkLeft_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4000 0x36
    if equal _call PlayerWalkRight_Return
    return

PlayerTakesTheBlame:
    applymovement PlutoAdminIrene m_Joy
    msgbox gText_RubarrDesert_IreneAcceptsBlame MSG_NORMAL
    applymovement Rival m_Surprise
    msgbox gText_RubarrDesert_RivalCritizesPlayer MSG_NORMAL
    applymovement Rival m_LookUp
    return

PlayerDeflectsTheBlame:
    msgbox gText_RubarrDesert_IreneRejectsBlameDeflection MSG_NORMAL
    return

m_RivalRunsToMeetPlayer: .byte run_right, run_up, run_up, run_up, run_right, run_right, run_right, run_up, run_up, run_right, run_right, run_right, end_m 
m_ClancyAngry: .byte jump_onspot_down, pause_short, jump_onspot_down, end_m
m_IreneWalksUp: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, walk_up, walk_right, walk_up, walk_right, walk_right, end_m 
m_IreneApproachesPlayer: .byte walk_right, walk_right, look_down, end_m
m_IreneLeaves: .byte walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m 
m_RivalLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
