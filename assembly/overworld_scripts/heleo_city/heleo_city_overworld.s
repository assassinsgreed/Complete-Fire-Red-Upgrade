.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoCity
MapScript_HeleoCity:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoCity_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoCity_FlightSpot:
    setworldmapflag 0x894
    setvar PLAYERFACING 0x0 @ Reset facing from the gym
    end

.global EventScript_HeleoCity_JumpingKid
EventScript_HeleoCity_JumpingKid:
    lock
    faceplayer
    msgbox gText_HeleoCityOverworld_JumpingKidPrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DoNotLikeJumping
    applymovement 0x1 m_Joy
    checkflag 0x249 @ Received Air Balloon
    if SET _goto JumpingKidDone
    msgbox gText_HeleoCityOverworld_JumpingKidLikeJumping MSG_NORMAL
    setvar 0x8004 0x2B @ Ledges jumped down
    callasm StoreGameStat
    buffernumber 0x0 LASTRESULT
    compare LASTRESULT 0x64 @ 100
    if lessthan _goto NotEnoughJumps
    faceplayer @ TODO: Needed?
    msgbox gText_HeleoCityOverworld_JumpingKidCountExceeded MSG_NORMAL
    fanfare 0x13E
    waitfanfare
    msgbox gText_HeleoCityOverworld_JumpingKidGift MSG_NORMAL
    obtainitem ITEM_AIR_BALLOON 0x1
    setflag 0x249 @ Got Air Balloon
    goto JumpingKidDone

DoNotLikeJumping:
    msgbox gText_HeleoCityOverworld_JumpingKidHateJumping MSG_NORMAL
    goto End

NotEnoughJumps:
    msgbox gText_HeleoCityOverworld_JumpingKidCount MSG_NORMAL
    goto End

JumpingKidDone:
    msgbox gText_HeleoCityOverworld_JumpingKidDone MSG_NORMAL
    goto End

.global EventScript_HeleoCity_ShadyDealer
EventScript_HeleoCity_ShadyDealer:
    lock
    faceplayer
    callasm StorePokeChipCount
	buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_HeleoCityOverworld_ShadyDealerProposition MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ShadyDealerRejected
    checkitem ITEM_POKE_CHIP 0x1
    compare LASTRESULT TRUE
    if FALSE _goto ShadyDealerNotEnoughPokeChips
    removeitem ITEM_POKE_CHIP 0x1
    sound 0xF8 @ Money SE
    random 0xE @ 15 items
    switch LASTRESULT
    case 0, ShadyDealerObtainPotion
    case 1, ShadyDealerObtainSuperPotion
    case 2, ShadyDealerObtainHyperPotion
    case 3, ShadyDealerObtainRevive
    case 4, ShadyDealerObtainRevive
    case 5, ShadyDealerObtainMaxRevive
    case 6, ShadyDealerObtainPPUp
    case 7, ShadyDealerObtainPokeball
    case 8, ShadyDealerObtainPokeball
    case 9, ShadyDealerObtainGreatBall
    case 10, ShadyDealerObtainUltraball
    case 11, ShadyDealerObtainNormalGem
    case 12, ShadyDealerObtainAmuletCoin
    case 13, ShadyDealerObtainStarPiece
    case 14, ShadyDealerObtainNugget
    goto End

ShadyDealerObtainPotion:
    obtainitem ITEM_POTION 0x3
    goto ShadyDealerTradeComplete

ShadyDealerObtainSuperPotion:
    obtainitem ITEM_SUPER_POTION 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainHyperPotion:
    obtainitem ITEM_HYPER_POTION 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainRevive:
    obtainitem ITEM_REVIVE 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainMaxRevive:
    obtainitem ITEM_MAX_REVIVE 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainPPUp:
    obtainitem ITEM_PP_UP 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainPokeball:
    obtainitem ITEM_POKE_BALL 0x3
    goto ShadyDealerTradeComplete

ShadyDealerObtainGreatBall:
    obtainitem ITEM_GREAT_BALL 0x2
    goto ShadyDealerTradeComplete

ShadyDealerObtainUltraball:
    obtainitem ITEM_ULTRA_BALL 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainNormalGem:
    obtainitem ITEM_NORMAL_GEM 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainAmuletCoin:
    obtainitem ITEM_AMULET_COIN 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainStarPiece:
    obtainitem ITEM_STAR_PIECE 0x1
    goto ShadyDealerTradeComplete

ShadyDealerObtainNugget:
    obtainitem ITEM_NUGGET 0x1
    goto ShadyDealerTradeComplete

ShadyDealerRejected:
    msgbox gText_HeleoCityOverworld_ShadyDealerDeclined MSG_NORMAL
    goto End

ShadyDealerNotEnoughPokeChips:
    msgbox gText_HeleoCityOverworld_ShadyDealerNotEnoughChips MSG_NORMAL
    goto End

ShadyDealerTradeComplete:
    msgbox gText_HeleoCityOverworld_ShadyDealerTradeComplete MSG_NORMAL
    fadescreen FADEOUT_BLACK
    setflag 0xE09 @ Hide shady dealer
    hidesprite LASTTALKED
    pause DELAY_1SECOND
    fadescreen FADEIN_BLACK
    goto End

.global EventScript_HeleoCity_Route8Girl
EventScript_HeleoCity_Route8Girl:
    npcchat gText_HeleoCityOverworld_Route8Girl
    end

.global EventScript_HeleoCity_FountainKid
EventScript_HeleoCity_FountainKid:
    npcchatwithmovement gText_HeleoCityOverworld_FountainKid m_LookUp
    end

.global EventScript_HeleoCity_BigGuy
EventScript_HeleoCity_BigGuy:
    npcchat gText_HeleoCityOverworld_BigGuy
    end

.global EventScript_HeleoCity_TrainerHouseGirl
EventScript_HeleoCity_TrainerHouseGirl:
    npcchat gText_HeleoCityOverworld_TrainerHouseGirl
    end

.global EventScript_HeleoCity_RaineFan
EventScript_HeleoCity_RaineFan:
    npcchat gText_HeleoCityOverworld_RaineFan
    end

.global EventScript_HeleoCity_BadgeBasedGyms
EventScript_HeleoCity_BadgeBasedGyms:
    npcchat gText_HeleoCityOverworld_BadgeBasedGyms
    end

.global SignScript_HeleoCity_CitySign
SignScript_HeleoCity_CitySign:
    msgbox gText_HeleoCityOverworld_HeleoCitySign MSG_SIGN
    end

.global SignScript_HeleoCity_GymSign
SignScript_HeleoCity_GymSign:
    msgbox gText_HeleoCityOverworld_GymSign MSG_SIGN
    end

.global SignScript_HeleoCity_TrainerHouseSign
SignScript_HeleoCity_TrainerHouseSign:
    msgbox gText_HeleoCityOverworld_TrainerHouseSign MSG_SIGN
    end
