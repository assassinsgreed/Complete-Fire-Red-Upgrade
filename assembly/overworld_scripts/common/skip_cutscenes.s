.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Common logic for cutscene skipping

@ Template:
@.global SkippingCutscene_GameStart
@SkippingCutscene_GameStart:
@    lock
@    fadescreen FADEOUT_BLACK
@    msgbox gText_SkippingCutscenes_Header MSG_SIGN
@    msgbox gText_SkippingCutscenes_AnthraTown_StartOfNewGame MSG_SIGN
@    @ Flags, vars, items, placement, etc.
@    fadescreen FADEIN_BLACK
@    release
@    end

.global SkippingCutscene_GameStart_InPlayersRoom
SkippingCutscene_GameStart_InPlayersRoom:
    @ Don't show a skip message here; no point as the player just started and can only go downstairs
    setvar 0x4055 0x1
	clearflag 0x02B @ Show the professor, champion, and tv crew from this point forward (hidden by default by game setup)
	clearflag 0x02C @ Show the rival from this point forward (hidden by default by game startup)
    end

.global SkippingCutscene_GameStart_MeetingRivalDownstairs
SkippingCutscene_GameStart_MeetingRivalDownstairs:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_AnthraTown_StartOfNewGame_MeetingRivalDownstairs MSG_SIGN
    setvar 0x4055 0x2
    setflag 0x02C @ Hide the rival from this point forward
    call SetGameInitializationFlags
    hidesprite 0x2 @ Rival
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_Route17_MeetingHawthorneAndSelene
SkippingCutscene_Route17_MeetingHawthorneAndSelene:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route17_MeetingHawthorneAndSelene MSG_SIGN
    setvar 0x4055 0x3 @ Met with Rival
    additem ITEM_TOWN_MAP 0x1
    hidesprite 4 @ Rival
    setflag 0x02D @ Hide rival on route 17
    clearflag 0x02E @ Show rival in their house
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_AnthraTown_AskingMomToGoOnJourney
SkippingCutscene_AnthraTown_AskingMomToGoOnJourney:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_AnthraTown_ReceivedMothersBlessing MSG_SIGN
    applymovement 0x1 m_LookLeft
    additem ITEM_TOWN_MAP 0x1
    setflag 0x82F @ Player can now run
    setflag 0x914 @ Enable auto run
    setflag 0x002E @ Hide rival in their home
    clearflag 0x02D @ Show rival on route 17
    setvar 0x4055 0x5 @ Talked to mom & move rival to Route 17
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_Route17_ChoosingStarter
SkippingCutscene_Route17_ChoosingStarter:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route17_ChooseStarter MSG_SIGN
    setvar 0x4055 0x6 @ Choosing starter
    clearflag 0x028
    showsprite 0x5 @ Show grass starter ball on route 17
	clearflag 0x029
    showsprite 0x6 @ Show water starter ball on route 17
	clearflag 0x02A
    showsprite 0x7 @ Show fire starter ball on route 17
    playbgm 0x180 @ Let's go together!
    applymovement 0x2 m_LookRight @ Hawthorne
    applymovement 0x3 m_LookLeft @ Selene
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscenes_Route17_BattleRival
SkippingCutscenes_Route17_BattleRival:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route17_HasChosenStarter MSG_SIGN
    setflag 0x028
    hidesprite 0x5 @ Hide grass starter ball on route 17
	setflag 0x029
    hidesprite 0x6 @ Hide water starter ball on route 17
	setflag 0x02A
    hidesprite 0x7 @ Hide fire starter ball on route 17
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars

    @ Player and rival positioning
    compare 0x4001 0xA
    if greaterthan _call PlayerWalkUp_Return
    compare 0x4001 0xA
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0xA
    if lessthan _call PlayerWalkDown_Return
    getplayerpos 0x4000 0x4001 @ Get player x and y in throwaway vars
    compare 0x4001 0xA
    if lessthan _call PlayerWalkDown_Return
    applymovement PLAYER m_LookRight
    applymovement 0x4 m_LookLeft
    fadescreen FADEIN_BLACK
    
    @ Battle Rival
    setvar 0x8000 0xFEFE
    call SetupMugshotRival
    trainerbattle9 0x1 0x1 0x100 gText_Route17_RivalBattleConcludes gText_Route17_RivalBattleConcludes
    clearflag 0x90A @ Tutorials off (if it was never set, nothing will change)
    setvar 0x8000 0x0
    special 0x0 @ Heal the player @ Heal player party

    @ Cleanup Route 17 and prompt to go to Olenic Town
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route17_HeadToOlenicTown MSG_SIGN
    setflag 0x02B @ Hide Hawthorne, Selene, and Footprint kid in Anthra
    hidesprite 0x2 @ Hawthorne
    hidesprite 0x3 @ Selene
    setflag 0x258 @ Rival beaten on Route 17
    setflag 0x02D @ Hide Rival on Route 17
    hidesprite 0x4 @ Rival
    setvar 0x4055 0x7 @ The journey has started
    setvar 0x4098 0x1 @ Turn off Anthra Tile events
    fadedefaultbgm
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_OlenicTown_ReceivingPokedex
SkippingCutscene_OlenicTown_ReceivingPokedex:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_OlenicTown_ReceivingPokedex MSG_SIGN
    hidesprite 0x2 @ Pokedex, in map
    setflag 0x03A @ Hide Pokedex sprite
    setflag 0x829 @ Show Pokedex menu
    additem ITEM_POKE_BALL 0xA @ Get 10 Pokeballs
    setflag 0x030 @ Hide blocking events in Anthra Town
	setvar 0x4050 0x1
    addvar 0x40FF 0x1 @ Enable catching event on Route 2, if player requested tutorialization
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_Route3_InitiatingDexNavEvent
SkippingCutscene_Route3_InitiatingDexNavEvent:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route3_BattlingRival MSG_SIGN
    fadescreen FADEIN_BLACK
    call SetupMugshotRival
    trainerbattle3 0x0 0x1C 0x100 gText_Route3_BeatRival
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route3_InitiatingDexNav MSG_SIGN
    clearflag 0x32 @ Show Assistant
    showsprite 0x16 @ Assistant
    hidesprite 0x12 @ Rival
    hidesprite 0x13 @ Clancy
    hidesprite 0x14 @ Ena
    movesprite 0x16 0x04A 0x000E @ Update position of Assistant temporarily (for after cutscene)
    movesprite2 0x16 0x04A 0x000E @ Update position of Assistant permanently
    setflag 0x31 @ Hide rival on Route 3
    setflag 0x232 @ Initiated DexNav event (for Rhodanzi Gym placard)
    clearflag 0x33 @ Show Pluto grunts on route 3 & Rubarr Desert
    setvar 0x4057 0x1
    applymovement PLAYER m_LookRight
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_RubarrDesert_ConfrontingTeamPluto
SkippingCutscene_RubarrDesert_ConfrontingTeamPluto:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_RubarrDesert_StoppingTeamPluto MSG_SIGN
    
    @ Clancy & Ena fight 
    clearflag 0x34 @ Show Rival and Irene
    showsprite 0x21 @ Rival
    showsprite 0x20 @ Irene
    movesprite 0x21 0x37 0x16 @ Rival
    movesprite 0x20 0x30 0x1C @ Irene
    applymovement 0x21 m_LookUp @ Rival
    fadescreen FADEIN_BLACK
    special 0x0 @ Heal the player
    call RivalTagBattlePromptAndPartyOrganization
    trainerbattle10 0xA 0x21 0x22 0xB2 0x6 0x0 gText_RubarrDesert_ClancyLoses gText_RubarrDesert_EnaLoses
    
    @ Irene fight
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_RubarrDesert_StoppingTeamPlutoIrene MSG_SIGN
    movesprite 0x1E 0x38 0x15 @ Clancy
    movesprite 0x1F 0x39 0x15 @ Ena
    movesprite 0x20 0x37 0x15
    
    applymovement 0x1E m_LookDown @ Clancy
    applymovement 0x1F m_LookDown @ Ena
    applymovement 0x20 m_LookDown @ Irene
    fadescreen FADEIN_BLACK
    trainerbattle12 0xC 0x23 0xB2 0x6 0x100 gText_RubarrDesert_IreneBattleDefeat
    
    @ Conclusion to Rubarr Desert events
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_RubarrDesert_ReturnDexNavs MSG_SIGN
    hidesprite 0x21 @ Rival
    hidesprite 0x20 @ Irene
    hidesprite 0x1E @ Clancy
    hidesprite 0x1F @ Ena
    setflag 0x33 @ Hide Team Pluto
    setflag 0x34 @ Hide Rival and Irene
    setflag 0x291 @ Beat Irene in Rubarr Desert
    setvar 0x4057 0x2
    special 0x0 @ Heal the player
    playbgm 0x1B4 0x1 @ Play default Rubarr Desert track (Replace override from cutscene)
    fadescreen FADEIN_BLACK
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    release
    end

.global SkippingCutscene_Route3_ReturningDexNavs
SkippingCutscene_Route3_ReturningDexNavs:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route3_ReturningDexNavs MSG_SIGN
    additem ITEM_DEX_NAV 0x1
    setflag 0x91E @ Show DexNav
    setflag 0x92A @ Show held items in DexNav UI
    hidesprite 0x12 @ Rival
    hidesprite 0x16 @ Assistant
    setflag 0x32 @ Hide assistant
    clearflag 0x35 @ Show NPCs on Route 4
    clearflag 0x36 @ Show Foreman on Route 4
    setvar 0x4057 0x3
    fadescreen FADEIN_BLACK
    release
    end

@ Torma Cave Casey does not have an event due to all the gender setup

.global SkippingCutscene_Route4_PathCleared
SkippingCutscene_Route4_PathCleared:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route4_ForemanEvent MSG_SIGN
    hidesprite 0x1 @ Foreman
    addvar 0x4051 0x1 @ Now 2 (Foreman cutscene)
    setflag 0x36 @ Foreman has left
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_FerroxVillage_ApproachingGym
SkippingCutscene_FerroxVillage_ApproachingGym:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_FerroxVillage_ApproachedGymWhileEmpty MSG_SIGN
    call MoveLoudMan
    setvar 0x4052 0x1 @ Met rival at the gym
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_FerroxVillage_AlistairInFerroxLibrary
SkippingCutscene_FerroxVillage_AlistairInFerroxLibrary:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_FerroxVillage_AlistairAtTheLibrary MSG_SIGN
    additem ITEM_HM01 0x1
    setflag 0x39 @ Hide Stella and Rival in library
    setflag 0x2F @ Hide Rival
    clearflag 0x3B @ Show Stella in gym
    setvar 0x4052 0x3 @ Met Alistair at the library
    hidesprite 0xB @ Stella
    hidesprite 0xC @ Alistair
    hidesprite 0x10 @ Rival
    fadescreen FADEIN_BLACK
    release
    end

DaimynCityGuardHouseCommon:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_DaimynCityGuardHouses_BattleRival MSG_SIGN
    fadescreen FADEIN_BLACK
    
    @ Battle
    call SetupMugshotRival
    trainerbattle3 0x0 0x88 0x100 gText_DaimynCityFacilities_GuardHouse_RivalLoses
    additem ITEM_MACHO_BRACE 0x1
    
    @ Going to Daimyn City 
    setvar 0x4054 0x1 @ Prevent rival battles in guard house 
    setflag 0x03C
    return

.global SkippingCutscene_DaimynCityGuardHouseSouth_RivalBattle
SkippingCutscene_DaimynCityGuardHouseSouth_RivalBattle:
    call DaimynCityGuardHouseCommon
    warp 3 5 1 @ South gate
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_DaimynCityGuardHouseWest_RivalBattle
SkippingCutscene_DaimynCityGuardHouseWest_RivalBattle:
    call DaimynCityGuardHouseCommon
    warp 3 5 0 @ West gate
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_DaimynCity_Tour
SkippingCutscene_DaimynCity_Tour:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_DaimynCity_ChallengeGym MSG_SIGN
    setflag 0x251 @ Hide story events
    setvar 0x4054 0x2
    hidesprite 0xF @ Rival
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_DaimynCity_GymPuzzleIntroduction
SkippingCutscene_DaimynCity_GymPuzzleIntroduction:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_DaimynCity_GymPuzzleIntroduction MSG_SIGN
    additem ITEM_COIN_CASE 0x1
    addcoins 500
    setvar 0x4096 2000 @ "Coin debt" to be paid before challenging gym leader
    setvar 0x4058 0x2 @ Gym explained
    movesprite 0x1 0x10 0x3 @ Chance, temporary while player in map
    movesprite2 0x1 0x10 0x3 @ Chance, permanently
    setobjectmovementtype 0x1 look_down
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_Route11South_StartingTeamPlutoEvent
SkippingCutscene_Route11South_StartingTeamPlutoEvent:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_TeamUpToStopPluto MSG_SIGN
    showsprite 0x19 @ Rival
    movesprite 0x19 0x1C 0x2E @ Update position of Rival permanently
    movesprite2 0x19 0x1C 0x2E @ Update position of Rival permanently
    applymovement 0x19 m_LookDown

    showsprite 0x1A @ Alistair
    movesprite 0x1A 0x1D 0x2E @ Update position of Alistair permanently
    movesprite2 0x1A 0x1D 0x2E @ Update position of Alistair permanently
    applymovement 0x1A m_LookDown

    setvar 0x4059 0x1 @ Pluto Encounter
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_Route11South_TalkingToClancyAndEna
SkippingCutscene_Route11South_TalkingToClancyAndEna:
    lock
    applymovement 0x1B m_LookDown @ Clancy
    applymovement 0x1C m_LookDown @ Ena
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_StopClancyAndEna MSG_SIGN
    fadescreen FADEIN_BLACK
    clearflag 0x926 @ Follower will not move during active script
    setflag 0x909 @ Two opponents
    setvar 0x5010 0xC7 @ Ena
    loadpointer 0x0 gText_Route11South_PlutoEvent_EnaLoses @ Ena's loss text
    special 0xAC @ Load second opponent's text into buffer
    trainerbattle3 0x3 0xC6 0x0 gText_Route11South_PlutoEvent_ClancyLoses @ Tag battle with current partner
    setvar 0x4059 0x2 @ Pluto Encounter
    special 0x0 @ Heal player
    special 0xD2 @ Remove follower
    warp 20 0 0 @ Event continued in house
    release
    end

.global SkippingCutscene_Route11South_BattleRonald
SkippingCutscene_Route11South_BattleRonald:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_BattleRonald MSG_SIGN
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    applymovement 0x2 m_WalkRight @ Ronald
    waitmovement ALLEVENTS
    applymovement 0x2 m_LookDown @ Ronald
    fadescreen FADEIN_BLACK
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 0xC8 0x100 gText_Route11SouthHouse_PlutoEvent_RonaldBattleIntro gText_Route11SouthHouse_PlutoEvent_RonaldBattleLoss PostRonaldBattle
    release
    end

.global SkippingCutscene_Route11South_AfterRonaldBattle
SkippingCutscene_Route11South_AfterRonaldBattle:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_AfterRonaldBattle MSG_SIGN
    
    setvar 0x4059 0x4
    setflag 0x41 @ Hide team pluto
    hidesprite 0x2 @ Ronald leaves
    fadedefaultbgm
    additem ITEM_MEGA_RING 0x1
    special 0x0 @ Heal player

    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    warp 3 29 0xFF 0x1D 0x2F
    release
    end

.global SkippingCutscene_Route11South_BattlingRival
SkippingCutscene_Route11South_BattlingRival:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN

    @ Setup rival battle
    call SetupMugshotRival
    copyvar 0x4001 0x408E
    setvar 0x4000 201 @ trainer ID, which is 201 + 0-7 depending on value in 0x408E
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    fadescreen FADEIN_BLACK
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_Route11SouthHouse_PlutoEvent_RivalLoses
    
    @ Skip post battle cutscene
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_AfterRivalBattle MSG_SIGN
    additem ITEM_HM02 0x1
    setvar 0x4059 0x5
    hidesprite 0x19 @ Rival
    hidesprite 0x1A @ Alistair
    setflag 0x42 @ Hide Rival and Alistair on Route 11 south
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_LaplazTown_IntroducingCasey
SkippingCutscene_LaplazTown_IntroducingCasey:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_LaplazTown_ChallengeCasey MSG_SIGN

    @ Setup Casey
    call SetCaseyGender
    clearflag 0x3F @ Casey is now revealed as leader
    showsprite 0x1 @ Casey
    setvar 0x405A 0x1
    getplayerpos 0x4000 0x4001 @ HACK: Move the player to the same map to force the tile script to release the player
    warpmuted 10 8 0xFF 0x4000 0x4001 @ Warp to same spot in the gym
    release
    end

.global SkippingCutscene_Route12RestHouse_SeleneAndAlistair
SkippingCutscene_Route12RestHouse_SeleneAndAlistair:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route12RestHouse_SeleneAndAlistair MSG_SIGN
    hidesprite 14 @ Selene
    setflag 0x44 @ Hide Selene and Alistair in Rest House
    setvar 0x405C 0x1 @ Route 12 Rest House scene
    special 0x8E @ Refresh map
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscene_BruccieVillage_BattlingRival
SkippingCutscene_BruccieVillage_BattlingRival:
    lock
    applymovement PLAYER m_LookUp
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_BruccieVillage_BattlingRival MSG_SIGN

    @ Positioning
    applymovement 0x7 m_LookDown @ Abby
    showsprite 0x8 @ Rival
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    applymovement PLAYER m_LookLeft
    movesprite 0x8 0xA 0x10
    applymovement 0x8 m_LookRight
    fadescreen FADEIN_BLACK
    
    @ Rival battle
    call SetupMugshotRival
    copyvar 0x4001 0x408E
    setvar 0x4000 266 @ trainer ID, which is 266 + 0-7 depending on value in 0x408E (Water starter generation)
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_BruccieVillage_Abby_RivalLoses
    
    @ Post battle Cleanup
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_BruccieVillage_ChallengeAbby MSG_SIGN
    checkitem ITEM_HM03 0x1
    compare LASTRESULT TRUE
    if FALSE _call SkippingCutscenes_CalicinBayTip
    hidesprite 0x7 @ Abby
    hidesprite 0x8 @ Rival
    setflag 0x47 @ Abby hidden from overworld
    fadescreen FADEIN_BLACK
    release
    end

SkippingCutscenes_CalicinBayTip:
    msgbox gText_SkippingCutscenes_CalicinBayTip MSG_SIGN
    return

.global SkippingCutscenes_CalicinBay_ConfrontingTeamPluto
SkippingCutscenes_CalicinBay_ConfrontingTeamPluto:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    
    @ Setup battle
    fadescreen FADEIN_BLACK
    setflag 0x909 @ Two opponents
    setvar 0x5010 290 @ Ena
    loadpointer 0x0 gText_CalicinBay_TeamPlutoEna_LosesBattle @ Ena's loss text
    special 0xAC @ Load second opponent's text into buffer
    trainerbattle3 0x3 289 0x0 gText_CalicinBay_TeamPlutoClancy_LosesBattle
    
    @ Post-battle events
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_CalicinBay_StormTeamPlutosBase MSG_SIGN
    hidesprite 0x8 @ Grunt 1
    hidesprite 0x9 @ Grunt 2
    hidesprite 0xB @ Clancy
    hidesprite 0xC @ Ena
    setflag 0x48 @ Hide all grunts in Calicin Bay
    setvar 0x405D 0x1 @ Allow story events at Pluto Hideout building to initiate
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscenes_DaimynCity_RevealingPlutoHQ
SkippingCutscenes_DaimynCity_RevealingPlutoHQ:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    call RevealStairs
    special 0x8E
    setvar 0x405D 0x2
    hidesprite 0x4 @ Alistair
    applymovement 0x1 m_LookRight @ Grunt talking to Alistair
    fadescreen FADEIN_BLACK
    release
    end

.global SkippingCutscenes_PlutoHQ_ConfrontingKurtis
SkippingCutscenes_PlutoHQ_ConfrontingKurtis:
    lock
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_DaimynCity_ConfrontingKurtis MSG_SIGN
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    showsprite 0x3 @ Alistair
    movesprite 0x3 0x1 0x5
    applymovement 0x3 m_LookDown
    showsprite 0x5 @ Ronald
    movesprite 0x5 0x2 0x8
    applymovement 0x5 m_LookUp
    showsprite 0x4 @ Irene
    movesprite 0x4 0x1 0x8
    applymovement 0x4 m_LookUp
    fadescreen FADEIN_BLACK

    @ Battle against Kurtis
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 313 0x100 gText_PlutoHQ_B1F_KurtisEncounter_KurtisLosesBattle
    
    @ Obtain items and clean up event
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_DaimynCity_SurfToTsarvosa MSG_SIGN
    hidesprite 0x3 @ Alistair
    hidesprite 0x1 @ Kurtis
    hidesprite 0x4 @ Irene
    hidesprite 0x5 @ Ronald
    clearflag 0x21B @ Show Gyaradosite
    showsprite 0x2 @ Gyaradosite
    additem ITEM_HM03 0x1 @ Surf
    setflag 0x4A @ Pluto grunts and admins should all disappear
    setvar 0x405D 0x4 @ Pluto events complete
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    warpmuted 3 5 5 @ Warp back to Daimyn City outside the building 
    release
    end

.global SkippingCutscenes_Route11South_EncounteringEna
SkippingCutscenes_Route11South_EncounteringEna:
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_Route11South_HeadToMountCarnelidge MSG_SIGN
    applymovement PLAYER m_WalkDown
    applymovement 29 m_WalkDown
    waitmovement 29
    setflag 0x26F @ Spoke to Ena
    movesprite 29 0x2A 0x36
    movesprite2 29 0x2A 0x36
    clearflag 0x56 @ Show Ena
    showsprite 29
    fadescreen FADEIN_BLACK
    end

.global SkippingCutscenes_CarnelidgeVolcanoPeak_StoppingAlistair
SkippingCutscenes_CarnelidgeVolcanoPeak_StoppingAlistair:
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_CarnelidgeVolcanoPeak_StoppingRivalAndAlistair MSG_SIGN
    movesprite 0x3 0xB 0x8 @ Rival
    movesprite2 0x3 0xB 0x8 @ Rival
    showsprite 0x3
    applymovement 0x3 m_LookDown
    applymovement 0x2 m_LookDown @ Alistair
    fadescreen FADEIN_BLACK

    @ Battles
    call SetupMugshotRival
    trainerbattle3 0x0 469 0x100 gText_CarnelidgeVolcanoPeak_RivalLosesToPlayer
    call SetupMugshotGymLeaderAndBosses
    trainerbattle3 0x0 470 0x100 gText_CarnelidgeVolcanoPeak_AlistairLosesToPlayer
    
    @ Skip Ultra Space
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_CarnelidgeVolcanoPeak_SkippingUltraSpace MSG_SIGN
    
    @ EmptyWorld and Ultra Space Events
    setflag 0x70 @ Hide Cosmog here when revisiting
    setflag 0x71 @ Hide Wingulls, in case the player walks away and come back
    setflag 0x77 @ Hide Taken Cosmog in ultra space
    clearflag 0x62 @ Show the return home researcher in ultra space
    setflag 0x272 @ Hide Cosmog when reloading ultra space
    setvar 0x40A6 0x8 @ Spoke to someone in Eclipse Village
    addvar 0x40A5 0x1 @ Skip rival commenting on rude people in ultra space

    @ Normal world events
    checkflag 0x945 @ Divergent Mode
    if NOT_SET _call ObtainHoundoominite
    if SET _call ObtainTyranitarite
    special 0x0 @ Heal player party
    hidesprite 0x2 @ Rival
    hidesprite 0x3 @ Alistair
    setflag 0x56 @ Hide Ena on Route 11 South and Alistair here
    setflag 0x273 @ Has completed the Carnelidge Volcano events
    call HandleJirachisAwakening
    fadescreen FADEIN_BLACK
    addvar 0x4062 0xF @ Conclude the story event. This is incremented dramatically to ensure Flying/Teleporting/etc will be usable again
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    end

.global SkippingCutscenes_UteyaVillage_PromptedToGoToAscensionTower
SkippingCutscenes_UteyaVillage_PromptedToGoToAscensionTower:
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_UteyaVillage_GoToAscensionTower MSG_SIGN
    addvar 0x406D 0x1
    fadescreen FADEIN_BLACK
    end

.global SkippingCutscenes_AscensionTower_GoToVictoryRoad
SkippingCutscenes_AscensionTower_GoToVictoryRoad:
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    msgbox gText_SkippingCutscenes_AscensionTower_GoToVictoryRoad MSG_SIGN
    hidesprite 8 @ Selene
    hidesprite 7 @ Rival
    setflag 0x3C @ Hide Selene and Rival again
    setflag 0x27F @ Victory Road challenge started
    addvar 0x406C 0x1
    fadescreen FADEIN_BLACK
    end

m_PlayerAndRivalWalkToVictoryFlag: .byte walk_up, walk_up, walk_up, end_m
m_RivalTakesPosition: .byte walk_left, look_right, end_m
m_PlayerTakesPosition: .byte walk_right, look_left, end_m
.global SkippingCutscenes_VictoryRoad_RivalEncounter
SkippingCutscenes_VictoryRoad_RivalEncounter:
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_Header MSG_SIGN
    applymovement PLAYER m_PlayerAndRivalWalkToVictoryFlag
    waitmovement ALLEVENTS
    applymovement PLAYER m_PlayerTakesPosition
    waitmovement ALLEVENTS
    showsprite 0x1
    movesprite 0x1 0x7 0xC @ For victory road battle
    applymovement 0x1 m_LookRight
    fadescreen FADEIN_BLACK

    @ Battle
    call SetupMugshotRival
    @ Figure out which team the rival uses
    copyvar 0x4001 0x408E
    setvar 0x4000 511 @ trainer ID, which is 511 + 0-7 depending on value in 0x408E
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x4000 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_VictoryRoad_RivalLosesBattle
    
    @ After battle
    fadescreen FADEOUT_BLACK
    msgbox gText_SkippingCutscenes_VictoryRoad_GoToAscensionTower MSG_SIGN
    hidesprite 0x1 @ Rival
    hidesprite 0x2 @ Flag
    additem ITEM_VICTORY_FLAG 0x1
    clearflag 0x4BC @ Champion Selene has not been beaten, in case this was somehow set by another script or cheats
    setflag 0x72 @ Victory Flag claimed
    clearflag 0x06B @ Rival appears in Daimyn City for training battle 
    setvar 0x4072 0x1 @ cutscenes over
    fadescreen FADEIN_BLACK
    checkflag 0x93B @ Hard level caps
    if SET _call PrintUpdatedLevelCaps
    end

