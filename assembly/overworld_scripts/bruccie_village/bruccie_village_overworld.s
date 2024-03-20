.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ Abby, 0x7
.equ Rival, 0x8

.global MapScript_BruccieVillage
MapScript_BruccieVillage:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_BruccieVillage_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_BruccieVillage_FlightSpot:
    setworldmapflag 0x897 @ Visited Bruccie Village
    end

.global EventScript_BruccieVillage_Hiker
EventScript_BruccieVillage_Hiker:
    npcchat gText_BruccieVillage_Hiker
    end

.global EventScript_BruccieVillage_Skier
EventScript_BruccieVillage_Skier:
    npcchat gText_BruccieVillage_Skier
    end

.global EventScript_BruccieVillage_Kid
EventScript_BruccieVillage_Kid:
    npcchat gText_BruccieVillage_Kid
    end

.global EventScript_BruccieVillage_OldMan
EventScript_BruccieVillage_OldMan:
    checkflag 0xE18 @ Wingull event done
    if SET _goto OldMan_DailyEventDone
    faceplayer
    msgbox gText_BruccieVillage_OldMan_WingullEventStarting MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    applymovement 0x6 m_WalkFacingRight
    pause DELAY_HALFSECOND
    msgbox gText_BruccieVillage_OldMan_RequestsTreasure MSG_NORMAL
    cry SPECIES_WINGULL 0x0
    msgbox gText_BruccieVillage_Wingull MSG_NORMAL
    faceplayer
    msgbox gText_BruccieVillage_OldMan_GivesTreasure MSG_NORMAL
    goto GiveWingullGift

GiveWingullGift:
    random 100
    compare LASTRESULT 2
    if lessthan _goto GiveBottleCapGift
    compare LASTRESULT 5
    if lessthan _goto GiveRareCandyGift
    compare LASTRESULT 10
    if lessthan _goto GiveUltraBallGift
    compare LASTRESULT 20
    if lessthan _goto GivePokeChipGift
    compare LASTRESULT 35
    if lessthan _goto GiveSuperRepelGift
    compare LASTRESULT 50
    if lessthan _goto GivePearlGift
    compare LASTRESULT 70
    if lessthan _goto GiveGreatBallGift
    goto GiveSuperPotionGift

GiveBottleCapGift:
    obtainitem ITEM_BOTTLE_CAP 0x1
    goto WingullGiftComplete

GiveRareCandyGift:
    obtainitem ITEM_RARE_CANDY 0x1
    goto WingullGiftComplete

GiveUltraBallGift:
    obtainitem ITEM_ULTRA_BALL 0x1
    goto WingullGiftComplete

GivePokeChipGift:
    obtainitem ITEM_POKE_CHIP 0x1
    goto WingullGiftComplete

GiveSuperRepelGift:
    obtainitem ITEM_SUPER_REPEL 0x1
    goto WingullGiftComplete

GivePearlGift:
    obtainitem ITEM_PEARL 0x1
    goto WingullGiftComplete

GiveGreatBallGift:
    obtainitem ITEM_GREAT_BALL 0x1
    goto WingullGiftComplete

GiveSuperPotionGift:
    obtainitem ITEM_SUPER_POTION 0x1
    goto WingullGiftComplete

WingullGiftComplete:
    applymovement 0x6 m_WingullFliesAway
    pause DELAY_HALFSECOND
    applymovement LASTTALKED m_LookLeft
    waitmovement 0x6
    hidesprite 0x6
    pause DELAY_1SECOND
    setflag 0xE18 @ Wingull event done
    goto OldMan_DailyEventDone

OldMan_DailyEventDone:
    npcchatwithmovement gText_BruccieVillage_OldMan_WingullEventDone m_LookUp
    end

.global EventScript_BruccieVillage_Wingull
EventScript_BruccieVillage_Wingull:
    cry SPECIES_WINGULL 0x0
    npcchatwithmovement gText_BruccieVillage_Wingull m_WalkFacingUp
    end

.global EventScript_BruccieVillage_Abby
EventScript_BruccieVillage_Abby:
    faceplayer
    msgbox gText_BruccieVillage_Abby_Question MSG_YESNO
    compare LASTRESULT NO
    if equal _goto NotHereForTheGym
    call MovePlayerBeforeAbby
    callasm CountBadges
    compare LASTRESULT 0x5
    if lessthan _goto NotReadyForGym
    msgbox gText_BruccieVillage_Abby_EnoughBadges MSG_NORMAL
    playbgm 0x195 @ Rival's theme
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    applymovement Abby m_Surprise
    msgbox gText_BruccieVillage_Abby_RivalInterrupt MSG_NORMAL
    showsprite Rival
    applymovement Rival m_RivalWalksToPlayer
    pause DELAY_1SECOND
    applymovement PLAYER m_LookRight
    applymovement Abby m_LookRight
    waitmovement Rival
    msgbox gText_BruccieVillage_Abby_RivalChallengesPlayer MSG_NORMAL
    applymovement Abby m_WalkRight
    waitmovement Abby
    applymovement Abby m_LookDown
    applymovement Rival m_LookUp
    msgbox gText_BruccieVillage_Abby_AbbyAcknowledgesRival MSG_NORMAL
    msgbox gText_BruccieVillage_Abby_RivalApologizesToAbby MSG_NORMAL
    msgbox gText_BruccieVillage_Abby_AbbyOverseesBattle MSG_NORMAL
    applymovement Rival m_LookLeft
    msgbox gText_BruccieVillage_Abby_RivalIssuesChallenge MSG_NORMAL
    applymovement Abby m_WalkLeft
    waitmovement Abby
    applymovement Abby m_LookDown
    applymovement Rival m_RivalTakesPosition
    applymovement PLAYER m_PlayerTakesPosition
    waitmovement PLAYER
    msgbox gText_BruccieVillage_Abby_RivalPreBattle MSG_NORMAL
    call SetupMugshotRival
    copyvar 0x4001 0x408E
    setvar 0x4000 266 @ trainer ID, which is 266 + 0-7 depending on value in 0x408E (Water starter generation)
    setvar 0x8004 0x4000
    setvar 0x8005 0x4001
    special 0x3E @ Add two vars above, result stored in 0x5011 which is loaded as trainer ID
    trainerbattle3 0x0 0x4000 0x100 gText_BruccieVillage_Abby_RivalLoses
    msgbox gText_BruccieVillage_Abby_RivalCommentsOnLoss MSG_NORMAL
    applymovement Rival m_RivalWalksToPlayerAfterBattle
    waitmovement Rival
    msgbox gText_BruccieVillage_Abby_RivalLeaves MSG_NORMAL
    applymovement Rival m_RivalLeavesAfterBattle
    pause DELAY_1SECOND
    applymovement Abby m_LookRight
    waitmovement Rival
    hidesprite Rival
    applymovement PLAYER m_PlayerReturnsToAbby
    waitmovement PLAYER
    msgbox gText_BruccieVillage_Abby_CommentsOnRival MSG_NORMAL
    applymovement Abby m_LookDown
    msgbox gText_BruccieVillage_Abby_AcceptsPlayersChallenge MSG_NORMAL
    applymovement Abby m_LookUp
    opendoor 0xB 0xE
    waitdooranim
    pause DELAY_HALFSECOND
    applymovement Abby m_WalkUp
    waitmovement Abby
    hidesprite Abby
    closedoor 0xB 0xE
    waitdooranim
    setflag 0x47 @ Abby hidden from overworld
    fadedefaultbgm
    end

NotHereForTheGym:
    npcchatwithmovement gText_BruccieVillage_Abby_SaidNo m_LookDown
    end

MovePlayerBeforeAbby:
    special 0xAF @ Dismount bike if on it
    compareplayerfacing INTERNAL_RIGHT
    if equal _call MoveFromLeft
    compareplayerfacing INTERNAL_LEFT
    if equal _call MoveFromRight
    applymovement PLAYER m_LookUp
    applymovement Abby m_LookDown
    return

MoveFromLeft:
    msgbox gText_BruccieVillage_Abby_MoveToFront MSG_NORMAL
    call PlayerWalkDown_Return
    call PlayerWalkRight_Return
    return

MoveFromRight:
    msgbox gText_BruccieVillage_Abby_MoveToFront MSG_NORMAL
    call PlayerWalkDown_Return
    call PlayerWalkLeft_Return
    return

NotReadyForGym:
    msgbox gText_BruccieVillage_Abby_NotEnoughBadges MSG_NORMAL
    end

.global EventScript_BruccieVillage_AbbyCommenter
EventScript_BruccieVillage_AbbyCommenter:
    npcchatwithmovement gText_BruccieVillage_AbbyCommenter m_LookRight
    end

.global SignScript_BruccieVillage_TownPlacard
SignScript_BruccieVillage_TownPlacard:
    msgbox gText_BruccieVillage_TownPlacardSign MSG_SIGN
    end

.global SignScript_BruccieVillage_GymSign
SignScript_BruccieVillage_GymSign:
    msgbox gText_BruccieVillage_GymSign MSG_SIGN
    end

m_WingullFliesAway: .byte run_left, run_left, run_left, run_left, run_left, run_left, run_left, run_left, end_m
m_RivalWalksToPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_RivalTakesPosition: .byte walk_down, walk_right, look_left, end_m
m_PlayerTakesPosition: .byte walk_down, walk_left, walk_left, look_right, end_m
m_RivalWalksToPlayerAfterBattle: .byte walk_left, walk_left, walk_left, end_m
m_RivalLeavesAfterBattle: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
m_PlayerReturnsToAbby: .byte walk_right, walk_right, walk_up, end_m
