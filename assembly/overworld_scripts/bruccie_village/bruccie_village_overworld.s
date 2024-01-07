.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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

.global EventScript_BruccieVillage_Psychic
EventScript_BruccieVillage_Psychic:
    npcchat gText_BruccieVillage_Psychic
    end

.global EventScript_BruccieVillage_OldMan
EventScript_BruccieVillage_OldMan:
    checkflag 0x1E8 @ Wingull event done
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
    setflag 0x1E8 @ Wingull event done
    goto OldMan_DailyEventDone

OldMan_DailyEventDone:
    npcchatwithmovement gText_BruccieVillage_OldMan_WingullEventDone m_LookUp
    end

.global EventScript_BruccieVillage_Wingull
EventScript_BruccieVillage_Wingull:
    cry SPECIES_WINGULL 0x0
    npcchatwithmovement gText_BruccieVillage_Wingull m_WalkFacingUp
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
