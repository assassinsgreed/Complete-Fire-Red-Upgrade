.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ CatchingTutorialRival, 12

.global EventScript_Route2_YoungsterJoey
EventScript_Route2_YoungsterJoey:
    trainerbattle0 0x0 0x5 0x0 gText_Route2_YoungsterJoey_Intro gText_Route2_YoungsterJoey_Defeat
    msgbox gText_Route2_YoungsterJoey_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassKimberly
EventScript_Route2_LassKimberly:
    trainerbattle0 0x0 0x6 0x0 gText_Route2_LassKimberly_Intro gText_Route2_LassKimberly_Defeat
    msgbox gText_Route2_LassKimberly_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassRikki
EventScript_Route2_LassRikki:
    trainerbattle0 0x0 0x7 0x0 gText_Route2_LassRikki_Intro gText_Route2_LassRikki_Defeat
    msgbox gText_Route2_LassRikki_Chat MSG_NORMAL
    end

.global EventScript_Route2_FindTMInfestation
EventScript_Route2_FindTMInfestation:
    setvar CHOSEN_ITEM ITEM_TM83
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_FindTMNaturePower
EventScript_Route2_FindTMNaturePower:
    setvar CHOSEN_ITEM ITEM_TM96
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_CoolTrainerAndy
EventScript_Route2_CoolTrainerAndy:
    trainerbattle0 0x0 0x10 0x0 gText_Route2_CoolTrainerAndy_Intro gText_Route2_CoolTrainerAndy_Defeat
    msgbox gText_Route2_CoolTrainerAndy_Chat MSG_NORMAL
    end

.global SignScript_Route2_TrainerTipsFishing
SignScript_Route2_TrainerTipsFishing:
    msgbox gText_Route2_TrainerTips MSG_SIGN
    end

.global TileScript_Route2_CapturingPokemonLeft
TileScript_Route2_CapturingPokemonLeft:
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    applymovement PLAYER m_LookUp
    waitmovement PLAYER
    goto TileScript_Route2_CapturingPokemonRight

.global TileScript_Route2_CapturingPokemonRight
TileScript_Route2_CapturingPokemonRight:
    lock
    showsprite CatchingTutorialRival
    applymovement CatchingTutorialRival m_RivalWalkDownTowardPlayer
    waitmovement CatchingTutorialRival
    sound 0x15 @ Exclaim
    applymovement CatchingTutorialRival m_Surprise
    waitmovement CatchingTutorialRival
    msgbox gText_Route2_CatchingTutorial_RivalGreetsPlayer MSG_NORMAL
    applymovement CatchingTutorialRival m_RivalMeetsPlayer
    waitmovement CatchingTutorialRival
    msgbox gText_Route2_CatchingTutorial_RivalCommentsOnPokedexAndPokeballs MSG_NORMAL
    playbgm 0x180 0x1 @ Let's go together, permanent on map
    applymovement CatchingTutorialRival m_RivalWalksIntoGrass
    applymovement PLAYER m_PlayerWalksIntoGrass
    waitmovement PLAYER
    msgbox gText_Route2_CatchingTutorialIntro_RivalTalksAboutHowToFindAPokemon MSG_NORMAL
    applymovement CatchingTutorialRival m_LookUp
    waitmovement CatchingTutorialRival
    pause DELAY_HALFSECOND
    applymovement CatchingTutorialRival m_LookDown
    waitmovement CatchingTutorialRival
    pause DELAY_HALFSECOND
    applymovement CatchingTutorialRival m_LookRight
    pause 0x10
    sound 0x15 @ Exclaim
    applymovement CatchingTutorialRival m_Surprise
    msgbox gText_Route2_CatchingTutorialIntro_RivalFindsAPokemon MSG_NORMAL
    setvar 0x8004 SPECIES_ROOKIDEE
    setvar 0x8005 5
    special 0x9C @ Catching tutorial
    waitstate
    applymovement CatchingTutorialRival m_LookLeft
    msgbox gText_Route2_CatchingTutorialIntro_RivalAfterTutorial MSG_NORMAL
    applymovement CatchingTutorialRival m_RivalLeaves
    pause 0x10
    applymovement PLAYER m_LookUp
    waitmovement CatchingTutorialRival
    hidesprite CatchingTutorialRival
    playbgm 0x123 0x1 @ Main route theme, permanent
    addvar 0x40FF 0x1
    end

m_RivalWalkDownTowardPlayer: .byte walk_down, walk_down, walk_down, walk_down, end_m
m_RivalMeetsPlayer: .byte walk_down, walk_down, end_m
m_RivalWalksIntoGrass: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, end_m
m_PlayerWalksIntoGrass: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, end_m
m_RivalLeaves: .byte walk_up, walk_up, walk_up, walk_up, walk_up, walk_up, end_m
