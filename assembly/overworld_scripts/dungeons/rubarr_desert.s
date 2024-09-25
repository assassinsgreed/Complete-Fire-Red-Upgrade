.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@@ Overworld @@

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
    mapscript MAP_SCRIPT_ON_RESUME MapResumeScript_HideGroudon
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_RubarrDesert_FlightFlag:
    setworldmapflag 0x8A5 @ Been to Rubarr Desert
    setflag 0x34 @ Hide Rival and Irene
    end

MapEntryScript_RubarrDesert_SetWeather:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto SetAllWeatherTypes @ Is morning or day, set clear, sandstorm, or sunny
    @ Is evening or night, set clear skies or sandstorm only
    random 0xA @ Between 0 and 10
    compare LASTRESULT 0x5 @ "6"
    if lessthan _call SetWeatherClear
    compare LASTRESULT 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    end

SetAllWeatherTypes:
    random 0xA @ Between 0 and 10
    compare LASTRESULT 0x4 @ "5"
    if lessthan _call SetWeatherSunny
    compare LASTRESULT 0x5 @ "6"
    if greaterorequal _call SetWeatherSandstorm
    @ Otherwise, leave as regular weather
    end

MapResumeScript_HideGroudon:
    checkflag 0x57 @ Groudon caught, defeated, or run from
    if NOT_SET _goto End
    hidesprite 41
    end

.global EventScript_RubarrDesert_NurseJaina
EventScript_RubarrDesert_NurseJaina:
    faceplayer
    checktrainerflag 0x517
    if SET _goto NurseJainaHeal
    trainerbattle2 0x0 0x17 0x0 gText_RubarrDesert_NurseJaina_Intro gText_RubarrDesert_NurseJaina_Defeat NurseJainaHeal
    call NurseJainaHeal

NurseJainaHeal:
    msgbox gText_RubarrDesert_NurseJaina_Chat MSG_NORMAL
    call PlayerHealNurse
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
    playbgm 0x19A 0x1 @ Encounter Team Pluto (permanent, needs to be overidden to default track later)
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
    call RivalTagBattlePromptAndPartyOrganization
    msgbox gText_RubarrDesert_RivalStartsFight MSG_NORMAL
    applymovement Rival m_LookUp
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    @ Start a tag battle (0xA) against Clancy (0x21) and Ena (0x22), with Partner Rival (0xB2) using backsprite (0x6)
    trainerbattle10 0xA 0x21 0x22 0xB2 0x6 0x0 gText_RubarrDesert_ClancyLoses gText_RubarrDesert_EnaLoses
    msgbox gText_RubarrDesert_ClancyPoorLoser MSG_NORMAL
    sound 0x15 @ Exclaim
    applymovement PlutoGruntClancy m_Surprise
    applymovement PlutoGruntEna m_Surprise
    msgbox gText_RubarrDesert_IreneArrives MSG_NORMAL
    applymovement PlutoGruntClancy m_LookRight
    applymovement PlutoGruntEna m_LookLeft
    msgbox gText_RubarrDesert_ClancyScared MSG_NORMAL
    msgbox gText_RubarrDesert_EnaScared MSG_NORMAL
    sound 0x15 @ Exclaim
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
    applymovement PlutoGruntClancy m_LookUp
    sound 0x69 @ DexNav search
    waitse
    pause DELAY_HALFSECOND
    sound 0x1A @ Error
    waitse
    pause DELAY_HALFSECOND
    sound 0x15 @ Exclaim
    applymovement PlutoGruntClancy m_Surprise
    msgbox gText_RubarrDesert_ClancySurprise MSG_NORMAL
    msgbox gText_RubarrDesert_EnaResponse MSG_NORMAL
    msgbox gText_RubarrDesert_IreneFollowsUpEnasQuestion MSG_NORMAL
    applymovement PlutoGruntClancy m_LookLeft
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
    @ Start a tag battle against Admin Irene
    trainerbattle12 0xC 0x23 0xB2 0x6 0x100 gText_RubarrDesert_IreneBattleDefeat
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
    sound 0x15 @ Exclaim
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
    playbgm 0x1B4 0x1 @ Play default Rubarr Desert track (Replace override from cutscene)
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
    sound 0x15 @ Exclaim
    applymovement Rival m_Surprise
    msgbox gText_RubarrDesert_RivalCritizesPlayer MSG_NORMAL
    applymovement Rival m_LookUp
    return

PlayerDeflectsTheBlame:
    msgbox gText_RubarrDesert_IreneRejectsBlameDeflection MSG_NORMAL
    return

.global EventScript_RubarrDesert_Groudon
EventScript_RubarrDesert_Groudon:
    msgbox gText_Common_EncounterKyogreGroudon MSG_NORMAL
    checkitem ITEM_RED_ORB 0x1
    compare LASTRESULT TRUE
    if equal _goto GroudonAwakens
    msgbox gText_Common_KyogreGroudonDormant MSG_NORMAL
    end

GroudonAwakens:
    @ Awakening
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    playse 0x24 @ Ice crack
    waitse
    pause DELAY_HALFSECOND
    bufferitem 0x0 ITEM_RED_ORB
    msgbox gText_Common_KyogreGroudonAwakens MSG_NORMAL
    playse 0x23 @ Ice break
    waitse
    @ Earthquake
    setvar 0x8004 0x0 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x3 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x20 @ This controls how long the overall animation lasts
	setvar 0x8007 0x2 @ This controls how long one screen shake lasts
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    waitstate
    @ Groudon awakened
    applymovement LASTTALKED m_KyogreGroudonAnimateOnSpotActive @ Walk on the spot, facing down (regular groudon)
    cry SPECIES_GROUDON 0x0
    msgbox gText_RubarrDesert_GroudonCry MSG_NORMAL
    waitcry
    pause DELAY_1SECOND
    @ Red Orb reacting further
    applymovement PLAYER m_Surprise
    msgbox gText_Common_KyogreGroudonOrbGlowing MSG_NORMAL
    fadescreenspeed FADEOUT_WHITE 0x96 @ fast fade
    applymovement LASTTALKED m_KyogreGroudonAnimateOnSpotPrimal @ Walk on the spot, facing right (primal groudon)
    call SetWeatherSunny
    fadescreen FADEIN_WHITE
    @ Primal Groudon awakened
    cry SPECIES_GROUDON_PRIMAL 0x0
    msgbox gText_RubarrDesert_PrimalGroudonCry MSG_NORMAL
    msgbox gText_Common_KyogreGroudonPreBattle MSG_NORMAL
    waitcry
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_PRECIPICEBLADES
    setvar 0x8001 MOVE_LAVAPLUME
    setvar 0x8002 MOVE_BULKUP
    setvar 0x8003 MOVE_HAMMERARM
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_GROUDON_PRIMAL 70
    setflag 0x57 @ Hide Groudon
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedOrFledFromGroudon
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call DefeatedOrFledFromGroudon
    bufferitem 0x0 ITEM_RED_ORB
    msgbox gText_Common_OrbCalmed MSG_NORMAL
    end

DefeatedOrFledFromGroudon:
    msgbox gText_Common_KyogreGroudonFledOrDefeated MSG_NORMAL
    return

m_RivalRunsToMeetPlayer: .byte run_right, run_up, run_up, run_up, run_right, run_right, run_right, run_up, run_up, run_right, run_right, run_right, end_m 
m_ClancyAngry: .byte jump_onspot_down, pause_short, jump_onspot_down, end_m
m_IreneWalksUp: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, walk_up, walk_right, walk_up, walk_right, walk_right, end_m 
m_IreneApproachesPlayer: .byte walk_right, walk_right, look_down, end_m
m_IreneLeaves: .byte walk_left, walk_left, walk_down, walk_down, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m 
m_RivalLeaves: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m

@@ Caves @@

.equ Ground, 0x2D9
.equ SandTopLeft, 0x2F3
.equ SandTopCenter, 0x2F4
.equ SandTopRight, 0x2F5
.equ SandCenterLeft, 0x2FB
.equ SandCenter, 0x2FC
.equ SandCenterRight, 0x2FD
.equ SandBottomLeft, 0x303
.equ SandBottomCenter, 0x304
.equ SandBottomRight, 0x305
.equ SandCornerTopLeft, 0x2F8
.equ SandCornerTopRight, 0x2F9
.equ SandCornerBottomLeft, 0x300
.equ SandCornerBottomRight, 0x301
.equ Passable, 0x0
.equ Impassable, 0x1

.global MapScript_RubarrDesertB2F
MapScript_RubarrDesertB2F:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_RubarrDesertBF2_SetSand
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_RubarrDesertBF2_SetSand:
    setflag 0x15 @ Hide Boulder
    checkflag 0x61
    if SET _call ShowBF2Boulder
    checkflag 0x058
    if SET _call FillLeftHole
    checkflag 0x059
    if SET _call FillTopLeftHole
    checkflag 0x060
    if SET _call FillCenterUpperHole
    checkflag 0x05B
    if SET _call FillCenterHole
    checkflag 0x05C
    if SET _call FillCenterLowerHole
    compare 0x40A3 0x3
    if equal _goto FillBigHole_Level3
    compare 0x40A3 0x2
    if equal _goto FillBigHole_Level2
    compare 0x40A3 0x1
    if equal _goto FillBigHole_Level1
    end

ShowBF2Boulder:
    clearflag 0x15 @ Show boulder
    return

FillLeftHole:
    setmaptile 0x2 0x5 SandTopLeft Passable
    setmaptile 0x3 0x5 SandTopCenter Passable
    setmaptile 0x4 0x5 SandTopRight Passable
    setmaptile 0x2 0x6 SandCenterLeft Passable
    setmaptile 0x3 0x6 SandCenter Passable
    setmaptile 0x4 0x6 SandCornerTopRight Passable
    setmaptile 0x5 0x6 SandTopRight Passable
    setmaptile 0x2 0x7 SandCenterLeft Passable
    setmaptile 0x3 0x7 SandCenter Passable
    setmaptile 0x4 0x7 SandCenter Passable
    setmaptile 0x5 0x7 SandCenterRight Passable
    setmaptile 0x2 0x8 SandBottomLeft Passable
    setmaptile 0x3 0x8 SandBottomCenter Passable
    setmaptile 0x4 0x8 SandBottomCenter Passable
    setmaptile 0x5 0x8 SandBottomRight Passable
    setmaptile 0x2 0x9 Ground Passable
    setmaptile 0x3 0x9 Ground Passable
    setmaptile 0x4 0x9 Ground Passable
    setmaptile 0x5 0x9 Ground Passable
    setmaptile 0x3 0x4 Ground Passable
    setmaptile 0x4 0x4 Ground Passable
    setmaptile 0x5 0x4 Ground Passable
    setmaptile 0x5 0x5 Ground Passable
    return

FillTopLeftHole:
    setmaptile 0x9 0x3 SandTopLeft Passable
    setmaptile 0xA 0x3 SandTopCenter Passable
    setmaptile 0xB 0x3 SandTopCenter Passable
    setmaptile 0xC 0x3 SandTopRight Passable
    setmaptile 0x9 0x4 SandCenterLeft Passable
    setmaptile 0xA 0x4 SandCenter Passable
    setmaptile 0xB 0x4 SandCenter Passable
    setmaptile 0xC 0x4 SandCenterRight Passable
    setmaptile 0x9 0x5 SandBottomLeft Passable
    setmaptile 0xA 0x5 SandBottomCenter Passable
    setmaptile 0xB 0x5 SandBottomCenter Passable
    setmaptile 0xC 0x5 SandBottomRight Passable
    setmaptile 0x8 0x3 Ground Passable
    setmaptile 0xD 0x3 Ground Passable
    setmaptile 0x8 0x4 Ground Passable
    setmaptile 0xD 0x4 Ground Passable
    setmaptile 0xD 0x5 Ground Passable
    return

FillCenterUpperHole:
    setmaptile 0x7 0x1C SandTopLeft Passable
    setmaptile 0x8 0x1C SandTopCenter Passable
    setmaptile 0x9 0x1C SandTopCenter Passable
    setmaptile 0xA 0x1C SandTopRight Passable
    setmaptile 0x7 0x1D SandCenterLeft Passable
    setmaptile 0x8 0x1D SandCenter Passable
    setmaptile 0x9 0x1D SandCenter Passable
    setmaptile 0xA 0x1D SandCornerTopRight Passable
    setmaptile 0xB 0x1D SandTopRight Passable
    setmaptile 0x7 0x1E SandBottomLeft Passable
    setmaptile 0x8 0x1E SandCornerBottomLeft Passable
    setmaptile 0x9 0x1E SandCenter Passable
    setmaptile 0xA 0x1E SandCenter Passable
    setmaptile 0xB 0x1E SandCenterRight Passable
    setmaptile 0x8 0x1F SandBottomLeft Passable
    setmaptile 0x9 0x1F SandBottomCenter Passable
    setmaptile 0xA 0x1F SandBottomCenter Passable
    setmaptile 0xB 0x1F SandBottomRight Passable
    setmaptile 0x6 0x1E Ground Passable
    setmaptile 0x6 0x1F Ground Passable
    setmaptile 0x7 0x1F Ground Passable
    setmaptile 0xB 0x1C Ground Passable
    setmaptile 0xC 0x1C Ground Passable
    setmaptile 0xC 0x1D Ground Passable
    setmaptile 0xC 0x1E Ground Passable
    setmaptile 0xC 0x1F Ground Passable
    return

FillCenterHole:
    setmaptile 0x1C 0x2C SandTopLeft Passable
    setmaptile 0x1D 0x2C SandTopCenter Passable
    setmaptile 0x1E 0x2C SandTopRight Passable
    setmaptile 0x1C 0x2D SandCenterLeft Passable
    setmaptile 0x1D 0x2D SandCenter Passable
    setmaptile 0x1E 0x2D SandCornerTopRight Passable
    setmaptile 0x1F 0x2D SandTopRight Passable
    setmaptile 0x1C 0x2E SandBottomLeft Passable
    setmaptile 0x1D 0x2E SandBottomCenter Passable
    setmaptile 0x1E 0x2E SandBottomCenter Passable
    setmaptile 0x1F 0x2E SandBottomRight Passable
    setmaptile 0x1C 0x2B Ground Passable
    setmaptile 0x1D 0x2B Ground Passable
    setmaptile 0x1E 0x2B Ground Passable
    setmaptile 0x1F 0x2B Ground Passable
    setmaptile 0x1F 0x2C Ground Passable
    setmaptile 0x1C 0x2F Ground Passable
    setmaptile 0x1D 0x2F Ground Passable
    setmaptile 0x1E 0x2F Ground Passable
    setmaptile 0x1F 0x2F 0x2DA Passable @ Right ground border side
    return

FillCenterLowerHole:
    setmaptile 0x20 0x2F SandTopLeft Passable
    setmaptile 0x21 0x2F SandTopCenter Passable
    setmaptile 0x22 0x2F SandTopCenter Passable
    setmaptile 0x23 0x2F SandTopRight Passable
    setmaptile 0x20 0x30 SandCenterLeft Passable
    setmaptile 0x21 0x30 SandCenter Passable
    setmaptile 0x22 0x30 SandCenter Passable
    setmaptile 0x23 0x30 SandCenterRight Passable
    setmaptile 0x20 0x31 SandBottomLeft Passable
    setmaptile 0x21 0x31 SandBottomCenter Passable
    setmaptile 0x22 0x31 SandBottomCenter Passable
    setmaptile 0x23 0x31 SandBottomRight Passable
    setmaptile 0x1F 0x2F Ground Passable
    setmaptile 0x1F 0x30 Ground Passable
    setmaptile 0x1F 0x31 Ground Passable
    setmaptile 0x24 0x2F Ground Passable
    setmaptile 0x24 0x30 Ground Passable
    setmaptile 0x24 0x31 Ground Passable
    return

FillBigHole_Level3:
    setmaptile 0x3A 0x20 SandCenter Passable
    setmaptile 0x3B 0x20 SandCenter Passable
    setmaptile 0x3C 0x20 SandCenter Passable
    setmaptile 0x3D 0x20 SandCenter Passable
    setmaptile 0x3E 0x20 SandCenter Passable
    setmaptile 0x3F 0x20 SandCenter Passable
    setmaptile 0x40 0x20 SandCenter Passable
    setmaptile 0x41 0x20 SandCenter Passable
    setmaptile 0x42 0x20 SandCenter Passable
    setmaptile 0x43 0x20 SandCenter Passable
    setmaptile 0x43 0x21 SandCenter Passable
    setmaptile 0x43 0x22 SandCenter Passable
    setmaptile 0x43 0x23 SandCenter Passable
    setmaptile 0x44 0x23 SandCenter Passable
    setmaptile 0x45 0x23 SandCenter Passable
    setmaptile 0x46 0x23 SandCenter Passable
    setmaptile 0x47 0x23 SandCenter Passable
    setmaptile 0x48 0x23 SandCenter Passable
    setmaptile 0x49 0x23 SandCenter Passable
    setmaptile 0x4A 0x23 SandCenter Passable
    setmaptile 0x4A 0x24 SandCenter Passable
    setmaptile 0x4A 0x25 SandCenter Passable
    setmaptile 0x4A 0x26 SandCenter Passable
    setmaptile 0x4A 0x27 SandCenterRight Passable
    setmaptile 0x4A 0x28 SandCenterRight Passable
    setmaptile 0x4A 0x29 SandCenterRight Passable
    setmaptile 0x4A 0x2A SandCornerTopRight Passable
    setmaptile 0x4B 0x2A SandTopCenter Passable
    setmaptile 0x4C 0x2A SandTopCenter Passable
    setmaptile 0x4D 0x2A SandTopCenter Passable
    setmaptile 0x4E 0x2A SandTopCenter Passable
    setmaptile 0x4F 0x2A SandTopCenter Passable
    setmaptile 0x50 0x2A SandTopCenter Passable
    setmaptile 0x50 0x2B SandCenter Passable
    setmaptile 0x50 0x2C SandCenter Passable
    setmaptile 0x50 0x2D SandCenter Passable
    setmaptile 0x51 0x2A SandTopCenter Passable
    setmaptile 0x51 0x2B SandCenter Passable
    setmaptile 0x51 0x2C SandCenter Passable
    setmaptile 0x51 0x2D SandCenter Passable
    setmaptile 0x51 0x2E SandCenter Passable
    setmaptile 0x33 0x2E SandCenter Passable
    setmaptile 0x34 0x2E SandCenter Passable
    setmaptile 0x35 0x2E SandCenter Passable
    setmaptile 0x36 0x2E SandCenter Passable
    setmaptile 0x37 0x2E SandCenter Passable
    setmaptile 0x38 0x2E SandCenter Passable
    setmaptile 0x39 0x2E SandCenter Passable
    setmaptile 0x3A 0x2E SandCenter Passable
    setmaptile 0x3B 0x2E SandCenter Passable
    setmaptile 0x3C 0x2E SandCenter Passable
    setmaptile 0x3D 0x2E SandCenter Passable
    setmaptile 0x3E 0x2E SandCenter Passable
    setmaptile 0x3F 0x2E SandCenter Passable
    setmaptile 0x40 0x2E SandCenter Passable
    setmaptile 0x41 0x2E SandCenter Passable
    setmaptile 0x42 0x2E SandCenter Passable
    setmaptile 0x43 0x2E SandCenter Passable
    setmaptile 0x44 0x2E SandCenter Passable
    setmaptile 0x45 0x2E SandCenter Passable
    setmaptile 0x46 0x2E SandCenter Passable
    setmaptile 0x47 0x2E SandCenter Passable
    setmaptile 0x48 0x2E SandCenter Passable
    setmaptile 0x49 0x2E SandCenter Passable
    setmaptile 0x4A 0x2E SandCenter Passable
    setmaptile 0x4B 0x2E SandCenter Passable
    setmaptile 0x4C 0x2E SandCenter Passable
    setmaptile 0x4D 0x2E SandCenter Passable
    setmaptile 0x4E 0x2E SandCenter Passable
    setmaptile 0x4F 0x2E SandCenter Passable
    setmaptile 0x50 0x2E SandCenter Passable
    setmaptile 0x33 0x27 SandCenter Passable
    setmaptile 0x33 0x28 SandCenter Passable
    setmaptile 0x33 0x29 SandCenter Passable
    setmaptile 0x33 0x2A SandCenter Passable
    setmaptile 0x33 0x2B SandCenter Passable
    setmaptile 0x33 0x2C SandCenter Passable
    setmaptile 0x33 0x2D SandCenter Passable
    setmaptile 0x34 0x27 SandCenter Passable
    setmaptile 0x35 0x27 SandCenter Passable
    setmaptile 0x36 0x27 SandCenter Passable
    setmaptile 0x37 0x27 SandCenter Passable
    setmaptile 0x38 0x27 SandCenter Passable
    setmaptile 0x39 0x27 SandCenter Passable
    setmaptile 0x3A 0x27 SandCenter Passable
    setmaptile 0x3A 0x21 SandCenter Passable
    setmaptile 0x3A 0x22 SandCenter Passable
    setmaptile 0x3A 0x23 SandCenter Passable
    setmaptile 0x3A 0x24 SandCenter Passable
    setmaptile 0x3A 0x25 SandCenter Passable
    setmaptile 0x3A 0x26 SandCenter Passable
    @ Fill ground level 2
    setmaptile 0x42 0x2B SandCenter Passable
    setmaptile 0x43 0x2B SandCenter Passable
    setmaptile 0x44 0x2B SandCenter Passable
    setmaptile 0x45 0x2B SandCenter Passable
    setmaptile 0x46 0x2B SandCenter Passable
    setmaptile 0x47 0x2B SandCenter Passable
    setmaptile 0x48 0x2B SandCenter Passable
    setmaptile 0x49 0x2B SandCenter Passable
    setmaptile 0x4A 0x2B SandCenter Passable
    setmaptile 0x4B 0x2B SandCenter Passable
    setmaptile 0x4C 0x2B SandCenter Passable
    setmaptile 0x4D 0x2B SandCenter Passable
    setmaptile 0x4E 0x2B SandCenter Passable
    setmaptile 0x4F 0x2B SandCenter Passable
    setmaptile 0x450 0x2B SandCenter Passable
    setmaptile 0x42 0x2C SandCenter Passable
    setmaptile 0x43 0x2C SandCenter Passable
    setmaptile 0x44 0x2C SandCenter Passable
    setmaptile 0x45 0x2C SandCenter Passable
    setmaptile 0x46 0x2C SandCenter Passable
    setmaptile 0x47 0x2C SandCenter Passable
    setmaptile 0x48 0x2C SandCenter Passable
    setmaptile 0x49 0x2C SandCenter Passable
    setmaptile 0x4A 0x2C SandCenter Passable
    setmaptile 0x4B 0x2C SandCenter Passable
    setmaptile 0x4C 0x2C SandCenter Passable
    setmaptile 0x4D 0x2C SandCenter Passable
    setmaptile 0x4E 0x2C SandCenter Passable
    setmaptile 0x4F 0x2C SandCenter Passable
    setmaptile 0x450 0x2C SandCenter Passable
    setmaptile 0x42 0x2D SandCenter Passable
    setmaptile 0x43 0x2D SandCenter Passable
    setmaptile 0x44 0x2D SandCenter Passable
    setmaptile 0x45 0x2D SandCenter Passable
    setmaptile 0x46 0x2D SandCenter Passable
    setmaptile 0x47 0x2D SandCenter Passable
    setmaptile 0x48 0x2D SandCenter Passable
    setmaptile 0x49 0x2D SandCenter Passable
    setmaptile 0x4A 0x2D SandCenter Passable
    setmaptile 0x4B 0x2D SandCenter Passable
    setmaptile 0x4C 0x2D SandCenter Passable
    setmaptile 0x4D 0x2D SandCenter Passable
    setmaptile 0x4E 0x2D SandCenter Passable
    setmaptile 0x4F 0x2D SandCenter Passable
    setmaptile 0x450 0x2D SandCenter Passable
    goto FillBigHole_Level2

FillBigHole_Level2:
    setmaptile 0x3B 0x21 SandCenter Passable
    setmaptile 0x3C 0x21 SandCenter Passable
    setmaptile 0x3D 0x21 SandCenter Passable
    setmaptile 0x3E 0x21 SandCenter Passable
    setmaptile 0x3F 0x21 SandCenter Passable
    setmaptile 0x40 0x21 SandCenter Passable
    setmaptile 0x41 0x21 SandCenter Passable
    setmaptile 0x42 0x21 SandCenter Passable
    setmaptile 0x42 0x22 SandCenter Passable
    setmaptile 0x42 0x23 SandCenter Passable
    setmaptile 0x42 0x24 SandCenter Passable
    setmaptile 0x43 0x24 SandCenter Passable
    setmaptile 0x44 0x24 SandCenter Passable
    setmaptile 0x45 0x24 SandCenter Passable
    setmaptile 0x46 0x24 SandCenter Passable
    setmaptile 0x47 0x24 SandCenter Passable
    setmaptile 0x48 0x24 SandCenter Passable
    setmaptile 0x49 0x24 SandCenter Passable
    setmaptile 0x43 0x25 SandCenter Passable
    setmaptile 0x44 0x25 SandCenter Passable
    setmaptile 0x45 0x25 SandCenter Passable
    setmaptile 0x46 0x25 SandCenter Passable
    setmaptile 0x47 0x25 SandCenter Passable
    setmaptile 0x48 0x25 SandCenter Passable
    setmaptile 0x49 0x25 SandCenter Passable
    setmaptile 0x49 0x26 SandCenter Passable
    setmaptile 0x49 0x27 SandCenter Passable
    setmaptile 0x49 0x28 SandCenter Passable
    setmaptile 0x40 0x29 SandCenter Passable
    setmaptile 0x41 0x29 SandCenter Passable
    setmaptile 0x42 0x29 SandCenter Passable
    setmaptile 0x43 0x29 SandCenter Passable
    setmaptile 0x44 0x29 SandCenter Passable
    setmaptile 0x45 0x29 SandCenter Passable
    setmaptile 0x46 0x29 SandCenter Passable
    setmaptile 0x47 0x29 SandCenter Passable
    setmaptile 0x48 0x29 SandCenter Passable
    setmaptile 0x49 0x29 SandCenter Passable
    setmaptile 0x40 0x2A SandCenter Passable
    setmaptile 0x41 0x2A SandCenter Passable
    setmaptile 0x42 0x2A SandCenter Passable
    setmaptile 0x43 0x2A SandCenter Passable
    setmaptile 0x44 0x2A SandCenter Passable
    setmaptile 0x45 0x2A SandCenter Passable
    setmaptile 0x46 0x2A SandCenter Passable
    setmaptile 0x47 0x2A SandCenter Passable
    setmaptile 0x48 0x2A SandCenter Passable
    setmaptile 0x49 0x2A SandCenter Passable
    setmaptile 0x41 0x2B SandCenter Passable
    setmaptile 0x41 0x2C SandCenter Passable
    setmaptile 0x34 0x2D SandCenter Passable
    setmaptile 0x35 0x2D SandCenter Passable
    setmaptile 0x36 0x2D SandCenter Passable
    setmaptile 0x37 0x2D SandCenter Passable
    setmaptile 0x38 0x2D SandCenter Passable
    setmaptile 0x39 0x2D SandCenter Passable
    setmaptile 0x3A 0x2D SandCenter Passable
    setmaptile 0x3B 0x2D SandCenter Passable
    setmaptile 0x3C 0x2D SandCenter Passable
    setmaptile 0x3D 0x2D SandCenter Passable
    setmaptile 0x3E 0x2D SandCenter Passable
    setmaptile 0x3F 0x2D SandCenter Passable
    setmaptile 0x40 0x2D SandCenter Passable
    setmaptile 0x41 0x2D SandCenter Passable
    setmaptile 0x34 0x28 SandCenter Passable
    setmaptile 0x34 0x29 SandCenter Passable
    setmaptile 0x34 0x2A SandCenter Passable
    setmaptile 0x34 0x2B SandCenter Passable
    setmaptile 0x34 0x2C SandCenter Passable
    setmaptile 0x35 0x28 SandCenter Passable
    setmaptile 0x36 0x28 SandCenter Passable
    setmaptile 0x37 0x28 SandCenter Passable
    setmaptile 0x38 0x28 SandCenter Passable
    setmaptile 0x39 0x28 SandCenter Passable
    setmaptile 0x3A 0x28 SandCenter Passable
    setmaptile 0x3B 0x28 SandCenter Passable
    setmaptile 0x3B 0x22 SandCenter Passable
    setmaptile 0x3B 0x23 SandCenter Passable
    setmaptile 0x3B 0x24 SandCenter Passable
    setmaptile 0x3B 0x25 SandCenter Passable
    setmaptile 0x3B 0x26 SandCenter Passable
    setmaptile 0x3B 0x27 SandCenter Passable
    compare 0x40A3 0x2
    if equal _call SetSecondLevelGround
    goto FillBigHole_Level1

SetSecondLevelGround:
    setmaptile 0x42 0x2B SandCornerBottomRight Passable
    setmaptile 0x43 0x2B SandBottomCenter Passable
    setmaptile 0x44 0x2B SandBottomCenter Passable
    setmaptile 0x45 0x2B SandBottomCenter Passable
    setmaptile 0x46 0x2B SandBottomCenter Passable
    setmaptile 0x47 0x2B SandBottomCenter Passable
    setmaptile 0x48 0x2B SandBottomCenter Passable
    setmaptile 0x49 0x2B SandBottomCenter Passable
    setmaptile 0x4A 0x2B SandBottomRight Passable
    setmaptile 0x42 0x2C SandCenterRight Passable
    setmaptile 0x42 0x2D SandCenterRight Passable
    return

FillBigHole_Level1:
    setmaptile 0x3C 0x22 SandCenter Passable
    setmaptile 0x3D 0x22 SandCenter Passable
    setmaptile 0x3E 0x22 SandCenter Passable
    setmaptile 0x3F 0x22 SandCenter Passable
    setmaptile 0x40 0x22 SandCenter Passable
    setmaptile 0x41 0x22 SandCenter Passable
    setmaptile 0x3C 0x23 SandCenter Passable
    setmaptile 0x3D 0x23 SandCenter Passable
    setmaptile 0x3E 0x23 SandCenter Passable
    setmaptile 0x3F 0x23 SandCenter Passable
    setmaptile 0x40 0x23 SandCenter Passable
    setmaptile 0x41 0x23 SandCenter Passable
    setmaptile 0x3C 0x24 SandCenter Passable
    setmaptile 0x3D 0x24 SandCenter Passable
    setmaptile 0x3E 0x24 SandCenter Passable
    setmaptile 0x3F 0x24 SandCenter Passable
    setmaptile 0x40 0x24 SandCenter Passable
    setmaptile 0x41 0x24 SandCenter Passable
    setmaptile 0x3C 0x25 SandCenter Passable
    setmaptile 0x3D 0x25 SandCenter Passable
    setmaptile 0x3E 0x25 SandCenter Passable
    setmaptile 0x3F 0x25 SandCenter Passable
    setmaptile 0x40 0x25 SandCenter Passable
    setmaptile 0x41 0x25 SandCenter Passable
    setmaptile 0x42 0x25 SandCenter Passable
    setmaptile 0x43 0x25 SandCenter Passable
    setmaptile 0x3C 0x26 SandCenter Passable
    setmaptile 0x3D 0x26 SandCenter Passable
    setmaptile 0x3E 0x26 SandCenter Passable
    setmaptile 0x3F 0x26 SandCenter Passable
    setmaptile 0x40 0x26 SandCenter Passable
    setmaptile 0x41 0x26 SandCenter Passable
    setmaptile 0x42 0x26 SandCenter Passable
    setmaptile 0x43 0x26 SandCenter Passable
    setmaptile 0x44 0x26 SandCenter Passable
    setmaptile 0x45 0x26 SandCenter Passable
    setmaptile 0x46 0x26 SandCenter Passable
    setmaptile 0x47 0x26 SandCenter Passable
    setmaptile 0x48 0x26 SandCenter Passable
    setmaptile 0x3C 0x27 SandCenter Passable
    setmaptile 0x3D 0x27 SandCenter Passable
    setmaptile 0x3E 0x27 SandCenter Passable
    setmaptile 0x3F 0x27 SandCenter Passable
    setmaptile 0x40 0x27 SandCenter Passable
    setmaptile 0x41 0x27 SandCenter Passable
    setmaptile 0x42 0x27 SandCenter Passable
    setmaptile 0x43 0x27 SandCenter Passable
    setmaptile 0x44 0x27 SandCenter Passable
    setmaptile 0x45 0x27 SandCenter Passable
    setmaptile 0x46 0x27 SandCenter Passable
    setmaptile 0x47 0x27 SandCenter Passable
    setmaptile 0x48 0x27 SandCenter Passable
    setmaptile 0x3C 0x28 SandCenter Passable
    setmaptile 0x3D 0x28 SandCenter Passable
    setmaptile 0x3E 0x28 SandCenter Passable
    setmaptile 0x3F 0x28 SandCenter Passable
    setmaptile 0x40 0x28 SandCenter Passable
    setmaptile 0x41 0x28 SandCenter Passable
    setmaptile 0x42 0x28 SandCenter Passable
    setmaptile 0x43 0x28 SandCenter Passable
    setmaptile 0x44 0x28 SandCenter Passable
    setmaptile 0x45 0x28 SandCenter Passable
    setmaptile 0x46 0x28 SandCenter Passable
    setmaptile 0x47 0x28 SandCenter Passable
    setmaptile 0x48 0x28 SandCenter Passable
    setmaptile 0x35 0x29 SandCenter Passable
    setmaptile 0x36 0x29 SandCenter Passable
    setmaptile 0x37 0x29 SandCenter Passable
    setmaptile 0x38 0x29 SandCenter Passable
    setmaptile 0x39 0x29 SandCenter Passable
    setmaptile 0x3A 0x29 SandCenter Passable
    setmaptile 0x3B 0x29 SandCenter Passable
    setmaptile 0x3C 0x29 SandCenter Passable
    setmaptile 0x3D 0x29 SandCenter Passable
    setmaptile 0x3E 0x29 SandCenter Passable
    setmaptile 0x3F 0x29 SandCenter Passable
    setmaptile 0x40 0x29 SandCenter Passable
    setmaptile 0x41 0x29 SandCenter Passable
    setmaptile 0x42 0x29 SandCenter Passable
    setmaptile 0x43 0x29 SandCenter Passable
    setmaptile 0x44 0x29 SandCenter Passable
    setmaptile 0x45 0x29 SandCenter Passable
    setmaptile 0x46 0x29 SandCenter Passable
    setmaptile 0x47 0x29 SandCenter Passable
    setmaptile 0x48 0x29 SandCenter Passable
    setmaptile 0x35 0x2A SandCenter Passable
    setmaptile 0x36 0x2A SandCenter Passable
    setmaptile 0x37 0x2A SandCenter Passable
    setmaptile 0x38 0x2A SandCenter Passable
    setmaptile 0x39 0x2A SandCenter Passable
    setmaptile 0x3A 0x2A SandCenter Passable
    setmaptile 0x3B 0x2A SandCenter Passable
    setmaptile 0x3C 0x2A SandCenter Passable
    setmaptile 0x3D 0x2A SandCenter Passable
    setmaptile 0x3E 0x2A SandCenter Passable
    setmaptile 0x3F 0x2A SandCenter Passable
    setmaptile 0x40 0x2A SandCenter Passable
    setmaptile 0x35 0x2B SandCenter Passable
    setmaptile 0x36 0x2B SandCenter Passable
    setmaptile 0x37 0x2B SandCenter Passable
    setmaptile 0x38 0x2B SandCenter Passable
    setmaptile 0x39 0x2B SandCenter Passable
    setmaptile 0x3A 0x2B SandCenter Passable
    setmaptile 0x3B 0x2B SandCenter Passable
    setmaptile 0x3C 0x2B SandCenter Passable
    setmaptile 0x3D 0x2B SandCenter Passable
    setmaptile 0x3E 0x2B SandCenter Passable
    setmaptile 0x3F 0x2B SandCenter Passable
    setmaptile 0x40 0x2B SandCenter Passable
    setmaptile 0x35 0x2C SandCenter Passable
    setmaptile 0x36 0x2C SandCenter Passable
    setmaptile 0x37 0x2C SandCenter Passable
    setmaptile 0x38 0x2C SandCenter Passable
    setmaptile 0x39 0x2C SandCenter Passable
    setmaptile 0x3A 0x2C SandCenter Passable
    setmaptile 0x3B 0x2C SandCenter Passable
    setmaptile 0x3C 0x2C SandCenter Passable
    setmaptile 0x3D 0x2C SandCenter Passable
    setmaptile 0x3E 0x2C SandCenter Passable
    setmaptile 0x3F 0x2C SandCenter Passable
    setmaptile 0x40 0x2C SandCenter Passable
    compare 0x40A3 0x1
    if equal _call SetMountainCornerForLevel1Pit
    setflag 0xE @ Hide temp boulder
    end

SetMountainCornerForLevel1Pit:
    setmaptile 0x41 0x2A 0x319 Impassable @ Mountain on desert
    return

.global EventScript_RubarrDesertCaves_Garchompite
EventScript_RubarrDesertCaves_Garchompite:
    finditem ITEM_GARCHOMPITE 0x1
    end

@ TODO: For some reason this soft locks the game??????
.global EventScript_RubarrDesertCaves_TM91FlashCannon
EventScript_RubarrDesertCaves_TM91FlashCannon:
    setvar CHOSEN_ITEM ITEM_TM91
    call ItemScript_Common_FindTM
    end

.global EventScript_RubarrDesertCaves_TM02DragonClaw
EventScript_RubarrDesertCaves_TM02DragonClaw:
    setvar CHOSEN_ITEM ITEM_TM02
    call ItemScript_Common_FindTM
    end

StatueCommon:
    msgbox gText_RubarrDesertCaves_PeculiarStatue_Confirmation MSG_YESNO
    compare LASTRESULT NO
    if equal _goto StatueChoseNotToMove
    msgbox gText_RubarrDesertCaves_PeculiarStatue_ChoseYes MSG_NORMAL
    return

StatueTakenCommon:
    hidesprite LASTTALKED
    playse 0x1E @ Unlock
    waitse
    applymovement PLAYER m_Surprise
    sound 0x15 @ Exclaim
    pause DELAY_HALFSECOND
    setvar 0x8004 0x0 @ This controls how far the screen shakes vertically
	setvar 0x8005 0x5 @ This controls how far the screen shakes horizontally
	setvar 0x8006 0x30 @ This controls how long the overall animation lasts
	setvar 0x8007 0x3 @ This controls how long one screen shake lasts
    playse 0xE3 @ Earthquake
    special 0x136 @ SPECIAL_SHAKE_SCREEN
    waitstate
    msgbox gText_RubarrDesertCaves_PeculiarStatue_SandMoved MSG_NORMAL
    return

StatueChoseNotToMove:
    msgbox gText_RubarrDesertCaves_PeculiarStatue_ChoseNo MSG_NORMAL
    end

.global EventScript_RubarrDesertCaves_Statue_Left
EventScript_RubarrDesertCaves_Statue_Left:
    call StatueCommon
    setflag 0x058
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_LeftUpper
EventScript_RubarrDesertCaves_Statue_LeftUpper:
    call StatueCommon
    setflag 0x059
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_CenterUpper
EventScript_RubarrDesertCaves_Statue_CenterUpper:
    call StatueCommon
    setflag 0x060
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_Center
EventScript_RubarrDesertCaves_Statue_Center:
    call StatueCommon
    setflag 0x05B
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_CenterLower
EventScript_RubarrDesertCaves_Statue_CenterLower:
    call StatueCommon
    setflag 0x05C
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_RightUpper
EventScript_RubarrDesertCaves_Statue_RightUpper:
    call StatueCommon
    setflag 0x05D
    addvar 0x40A3 0x1
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_RightCenter
EventScript_RubarrDesertCaves_Statue_RightCenter:
    call StatueCommon
    setflag 0x05E
    addvar 0x40A3 0x1
    call StatueTakenCommon
    end

.global EventScript_RubarrDesertCaves_Statue_RightLower
EventScript_RubarrDesertCaves_Statue_RightLower:
    call StatueCommon
    setflag 0x05F
    addvar 0x40A3 0x1
    call StatueTakenCommon
    end

