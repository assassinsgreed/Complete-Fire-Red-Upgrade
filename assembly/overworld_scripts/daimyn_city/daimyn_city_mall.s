.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DaimynCityMall_LuckyDrawLady
EventScript_DaimynCityMall_LuckyDrawLady:
    lock
    faceplayer
    checkflag 0xE0E @ Daily lucky species flag
    if SET _goto LuckyDrawOver
    msgbox gText_DaimynCityMall_LuckyDrawIntro MSG_YESNO
    compare LASTRESULT NO
    if equal _goto LuckyDrawChoseNo
    msgbox gText_DaimynCityMall_LuckyDrawStarting MSG_NORMAL
    random 0x11F @ up to #287 to avoid exposing starters and legendaries, stored in LastResult
    callasm GetLuckyPokmeonSpecies
    setflag 0xE0E @ Daily lucky species flag
    msgbox gText_DaimynCityMall_LuckyDrawPokemonChosen MSG_NORMAL
    compare LASTRESULT 0x1 @ Seen
    if lessthan _goto LuckySpeciesDidNotWin
    if equal _goto LuckySpeciesSeen
    if greaterthan _goto LuckySpeciesCaught

LuckyDrawChoseNo:
    msgbox gText_DaimynCityMall_LuckyDrawChoseNo MSG_NORMAL
    release
    end

LuckySpeciesDidNotWin:
    playse 0x1A @ Error
    msgbox gText_DaimynCityMall_LuckyDrawLost MSG_NORMAL
    waitse
    goto LuckyDrawOver

LuckySpeciesSeen:
    fanfare 0x101 @ Got Item / Level up
    msgbox gText_DaimynCityMall_LuckyDrawWinSeen MSG_NORMAL
    waitfanfare
    obtainitem ITEM_PEARL 0x1
    goto LuckyDrawOver

LuckySpeciesCaught:
    fanfare 0x10D @ Fanfare 2
    msgbox gText_DaimynCityMall_LuckyDrawWinCaught MSG_NORMAL
    waitfanfare
    obtainitem ITEM_BIG_PEARL 0x1
    goto LuckyDrawOver

LuckyDrawOver:
    msgbox gText_DaimynCityMall_LuckyDrawComeAgainTomorrow MSG_NORMAL
    release
    end

.global EventScript_DaimynCityMall_Greeter
EventScript_DaimynCityMall_Greeter:
    npcchat gText_DaimynCityMall_Greeter
    end

.global EventScript_DaimynCityMall_Shop_Herbalist
EventScript_DaimynCityMall_Shop_Herbalist:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_HerbSeller MSG_KEEPOPEN
    pokemart HerbShop
    goto EventScript_EndMart

HerbShop:
    .hword ITEM_ENERGY_POWDER
    .hword ITEM_ENERGY_ROOT
    .hword ITEM_HEAL_POWDER
    .hword ITEM_REVIVAL_HERB
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_DealOfTheDay
EventScript_DaimynCityMall_Shop_DealOfTheDay:
    lock
    checkflag 0xE10 @ Daily deal bought
    if SET _goto DealAlreadyBought
    msgbox gText_DaimynCityMall_DealOfTheDayOffer MSG_NORMAL
    showmoney 0x0 0x0
    checkflag 0xE0F @ Daily deal set
    if NOT_SET _call SetDailyDeal
    switch 0x40EC
    case 0, DailyDealPremierBalls
    case 1, DailyDealSuperPotions
    case 2, DailyDealBerries
    case 3, DailyDealSeeds
    case 4, DailyDealUltraBalls
    case 5, DailyDealHyperPotions
    case 6, DailyDealStatusHealers
    case 7, DailyDealXItems
    case 8, DailyDealHerbs
    case 9, DailyDealGreatBalls
    case 10, DailyDealGems1
    case 11, DailyDealGems2
    case 12, DailyDealGems3
    case 13, DailyDealEvolutionaryStones1
    case 14, DailyDealEvolutionaryStones2

SetDailyDeal:
    random 0xE @ 15 Sets
    copyvar 0x40EC LASTRESULT
    setflag 0xE0F @ Daily deal set
    return

HandleDailyDealPurchase:
    updatemoney 0x0 0x0
    sound 0xF8 @ Money SE
    waitse
    hidemoney
    msgbox gText_DaimynCityMall_DealOfTheDayPurchasing MSG_KEEPOPEN
    return

FinishBuyingDailyDeal:
    setflag 0xE10 @ Daily deal bought
    msgbox gText_DaimynCityMall_DealOfTheDayBought MSG_NORMAL
    release
    end

DailyDealPremierBalls:
    msgbox gText_DaimynCityMall_DealPremierBalls MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1F4 @ 500
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1F4
    call HandleDailyDealPurchase
    obtainitem ITEM_PREMIER_BALL 0x5
    goto FinishBuyingDailyDeal

DailyDealSuperPotions:
    msgbox gText_DaimynCityMall_DealSuperPotions MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x5DC @ 1500
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x5DC
    call HandleDailyDealPurchase
    obtainitem ITEM_SUPER_POTION 0x3
    goto FinishBuyingDailyDeal

DailyDealBerries:
    msgbox gText_DaimynCityMall_DealBerries MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x3E8 @ 1000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x3E8
    call HandleDailyDealPurchase
    obtainitem ITEM_ORAN_BERRY 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_SITRUS_BERRY 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_CHERI_BERRY 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_CHESTO_BERRY 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_RAWST_BERRY 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ASPEAR_BERRY 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_PERSIM_BERRY 0x1
    pause DELAY_HALFSECOND
    goto FinishBuyingDailyDeal

DailyDealSeeds:
    msgbox gText_DaimynCityMall_DealSeeds MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x320 @ 800
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x320
    call HandleDailyDealPurchase
    obtainitem ITEM_ELECTRIC_SEED 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_GRASSY_SEED 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_PSYCHIC_SEED 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_MISTY_SEED 0x2
    goto FinishBuyingDailyDeal

DailyDealUltraBalls:
    msgbox gText_DaimynCityMall_DealUltraBalls MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0xBB8 @ 3000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0xBB8
    call HandleDailyDealPurchase
    obtainitem ITEM_ULTRA_BALL 0x3
    goto FinishBuyingDailyDeal

DailyDealHyperPotions:
    msgbox gText_DaimynCityMall_DealHyperPotions MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x9C4 @ 2500
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x9C4
    call HandleDailyDealPurchase
    obtainitem ITEM_HYPER_POTION 0x2
    goto FinishBuyingDailyDeal

DailyDealStatusHealers:
    msgbox gText_DaimynCityMall_DealStatusHealers MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x4B0 @ 1200
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x4B0
    call HandleDailyDealPurchase
    obtainitem ITEM_ANTIDOTE 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_BURN_HEAL 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_ICE_HEAL 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_AWAKENING 0x2
    pause DELAY_HALFSECOND
    obtainitem ITEM_PARALYZE_HEAL 0x2
    goto FinishBuyingDailyDeal

DailyDealXItems:
    msgbox gText_DaimynCityMall_DealXItems MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x7D0 @ 2000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x7D0
    call HandleDailyDealPurchase
    obtainitem ITEM_X_ATTACK 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_X_DEFEND 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_X_SP_ATK 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_X_SP_DEF 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_X_SPEED 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_DIRE_HIT 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_GUARD_SPEC 0x1
    goto FinishBuyingDailyDeal

DailyDealHerbs:
    msgbox gText_DaimynCityMall_DealHerbs MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x5DC @ 1500
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x5DC
    call HandleDailyDealPurchase
    obtainitem ITEM_ENERGY_POWDER 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ENERGY_ROOT 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_HEAL_POWDER 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_REVIVAL_HERB 0x1
    goto FinishBuyingDailyDeal

DailyDealGreatBalls:
    msgbox gText_DaimynCityMall_DealGreatBalls MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x4E2 @ 1250
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x4E2
    call HandleDailyDealPurchase
    obtainitem ITEM_GREAT_BALL 0x4
    goto FinishBuyingDailyDeal

DailyDealGems1:
    msgbox gText_DaimynCityMall_DealGems MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1388 @ 5000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1388
    call HandleDailyDealPurchase
    obtainitem ITEM_FIRE_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_WATER_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ELECTRIC_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_GRASS_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ICE_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_FIGHTING_GEM 0x1
    goto FinishBuyingDailyDeal

DailyDealGems2:
    msgbox gText_DaimynCityMall_DealGems MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1388 @ 5000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1388
    call HandleDailyDealPurchase
    obtainitem ITEM_POISON_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_GROUND_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_FLYING_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_PSYCHIC_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_BUG_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ROCK_GEM 0x1
    goto FinishBuyingDailyDeal

DailyDealGems3:
    msgbox gText_DaimynCityMall_DealGems MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1388 @ 5000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1388
    call HandleDailyDealPurchase
    obtainitem ITEM_GHOST_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_DRAGON_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_DARK_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_STEEL_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_NORMAL_GEM 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_FAIRY_GEM 0x1
    goto FinishBuyingDailyDeal

DailyDealEvolutionaryStones1:
    msgbox gText_DaimynCityMall_DealEvolutionaryStones MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1770 @ 6000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1770
    call HandleDailyDealPurchase
    obtainitem ITEM_FIRE_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_THUNDER_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_WATER_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_LEAF_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_ICE_STONE 0x1
    goto FinishBuyingDailyDeal

DailyDealEvolutionaryStones2:
    msgbox gText_DaimynCityMall_DealEvolutionaryStones MSG_YESNO
    compare LASTRESULT NO
    if equal _goto DailyDealChoseNo
    checkmoney 0x1770 @ 6000
    compare LASTRESULT TRUE
    if notequal _goto DailyDealNotEnoughMoney
    removemoney 0x1770
    call HandleDailyDealPurchase
    obtainitem ITEM_MOON_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_SUN_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_SHINY_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_DUSK_STONE 0x1
    pause DELAY_HALFSECOND
    obtainitem ITEM_DAWN_STONE 0x1
    goto FinishBuyingDailyDeal

DealAlreadyBought:  
    msgbox gText_DaimynCityMall_DealOfTheDayAlreadyBought MSG_NORMAL
    release
    end

DailyDealChoseNo:
    hidemoney
    msgbox gText_DaimynCityMall_DealOfTheDayChoseNo MSG_NORMAL
    end

DailyDealNotEnoughMoney:
    hidemoney
    msgbox gText_DaimynCityMall_DealOfTheDayNotEnoughMoney MSG_NORMAL
    end

.global EventScript_DaimynCityMall_MagazineSeller
EventScript_DaimynCityMall_MagazineSeller:
    npcchat gText_DaimynCityMall_MagazineSeller
    end

.global EventScript_DaimynCityMall_Shop_Pokeballs
EventScript_DaimynCityMall_Shop_Pokeballs:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_PokeballSeller MSG_KEEPOPEN
    pokemart PokeBallShop
    goto EventScript_EndMart

PokeBallShop:
    .hword ITEM_NET_BALL
    .hword ITEM_DIVE_BALL
    .hword ITEM_NEST_BALL
    .hword ITEM_REPEAT_BALL
    .hword ITEM_QUICK_BALL
    .hword ITEM_TIMER_BALL
    .hword ITEM_LUXURY_BALL
    .hword ITEM_DUSK_BALL
    .hword ITEM_HEAL_BALL
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_XItems
EventScript_DaimynCityMall_Shop_XItems:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_XItemsSeller MSG_KEEPOPEN
    pokemart XItemsShop
    goto EventScript_EndMart

XItemsShop:
    .hword ITEM_X_ATTACK
    .hword ITEM_X_DEFEND
    .hword ITEM_X_SP_ATK
    .hword ITEM_X_SP_DEF
    .hword ITEM_X_SPEED
    .hword ITEM_X_ACCURACY
    .hword ITEM_GUARD_SPEC
    .hword ITEM_DIRE_HIT
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_GarageSaleMan
EventScript_DaimynCityMall_GarageSaleMan:
    npcchat gText_DaimynCityMall_GarageSaleMan
    end

.global EventScript_DaimynCityMall_Shop_TMs
EventScript_DaimynCityMall_Shop_TMs:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_TMSeller MSG_KEEPOPEN
    pokemart TMShop
    goto EventScript_EndMart

TMShop:
    .hword ITEM_TM16
    .hword ITEM_TM17
    .hword ITEM_TM20
    .hword ITEM_TM33
    .hword ITEM_TM44
    .hword ITEM_TM70
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_SeedSeller
EventScript_DaimynCityMall_Shop_SeedSeller:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_SeedSeller MSG_KEEPOPEN
    pokemart SeedShop
    goto EventScript_EndMart

SeedShop:
    .hword ITEM_ELECTRIC_SEED
    .hword ITEM_GRASSY_SEED
    .hword ITEM_MISTY_SEED
    .hword ITEM_PSYCHIC_SEED
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_EVReducingBerries
EventScript_DaimynCityMall_Shop_EVReducingBerries:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_EVReducingBerriesSeller MSG_KEEPOPEN
    pokemart EVReducingBerriesShop
    goto EventScript_EndMart

EVReducingBerriesShop:
    .hword ITEM_POMEG_BERRY
    .hword ITEM_KELPSY_BERRY
    .hword ITEM_QUALOT_BERRY
    .hword ITEM_HONDEW_BERRY
    .hword ITEM_GREPA_BERRY
    .hword ITEM_TAMATO_BERRY
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_Vitamins
EventScript_DaimynCityMall_Shop_Vitamins:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_VitaminsSeller MSG_KEEPOPEN
    pokemart VitaminsShop
    goto EventScript_EndMart

VitaminsShop:
    .hword ITEM_HP_UP
    .hword ITEM_PROTEIN
    .hword ITEM_IRON
    .hword ITEM_CARBOS
    .hword ITEM_CALCIUM
    .hword ITEM_ZINC
    .hword ITEM_PP_UP
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_Gems
EventScript_DaimynCityMall_Shop_Gems:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_GemsSeller MSG_KEEPOPEN
    pokemart GemsShop
    goto EventScript_EndMart

GemsShop:
    .hword ITEM_NORMAL_GEM
    .hword ITEM_FIGHTING_GEM
    .hword ITEM_FLYING_GEM
    .hword ITEM_POISON_GEM
    .hword ITEM_GROUND_GEM
    .hword ITEM_ROCK_GEM
    .hword ITEM_BUG_GEM
    .hword ITEM_GHOST_GEM
    .hword ITEM_STEEL_GEM
    .hword ITEM_FIRE_GEM
    .hword ITEM_WATER_GEM
    .hword ITEM_GRASS_GEM
    .hword ITEM_ELECTRIC_GEM
    .hword ITEM_PSYCHIC_GEM
    .hword ITEM_ICE_GEM
    .hword ITEM_DRAGON_GEM
    .hword ITEM_DARK_GEM
    .hword ITEM_FAIRY_GEM
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_RareCollectiblesMan
EventScript_DaimynCityMall_RareCollectiblesMan:
    npcchat gText_DaimynCityMall_RareCollectiblesMan
    end

.global EventScript_DaimynCityMall_Shop_TypeBoosterItems
EventScript_DaimynCityMall_Shop_TypeBoosterItems:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_TypeBoostingItemsSeller MSG_KEEPOPEN
    pokemart TypeBoostingShop
    goto EventScript_EndMart

TypeBoostingShop:
    .hword ITEM_BLACK_BELT
    .hword ITEM_BLACK_GLASSES
    .hword ITEM_CHARCOAL
    .hword ITEM_DRAGON_FANG
    .hword ITEM_HARD_STONE
    .hword ITEM_MAGNET
    .hword ITEM_METAL_COAT
    .hword ITEM_MIRACLE_SEED
    .hword ITEM_MYSTIC_WATER
    .hword ITEM_NEVER_MELT_ICE
    .hword ITEM_POISON_BARB
    .hword ITEM_SHARP_BEAK
    .hword ITEM_SILK_SCARF
    .hword ITEM_SILVER_POWDER
    .hword ITEM_SOFT_SAND
    .hword ITEM_SPELL_TAG
    .hword ITEM_TWISTED_SPOON
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_FishSeller
EventScript_DaimynCityMall_FishSeller:
    lock
    faceplayer
    checkflag 0x253 @ Bough carvanha
    if SET _goto FishSellerBought
    showpokepic SPECIES_CARVANHA
    showmoney 0x0 0x0
    msgbox gText_DaimynCityMall_FishSeller_Question MSG_YESNO
    hidepokepic
    compare LASTRESULT NO
    if equal _goto FishSellerSaidNo
    checkmoney 0x7D0 @ 2000
    compare LASTRESULT FALSE
    if equal _goto FishSellerNotEnoughMoney
    countpokemon
    compare LASTRESULT 0x6
    if equal _goto FishSellerNoSpaceInParty
    removemoney 0x7D0
    updatemoney 0x0 0x0
    sound 0xF8 @ Money SE
    waitse
    hidemoney
    givepokemon SPECIES_CARVANHA 0x19 ITEM_NONE @ Give lvl 25 Carvanha
    fanfare 0x101
    msgbox gText_DaimynCityMall_FishSeller_BoughtCarvanhaFanfare MSG_NORMAL
    waitfanfare
    msgbox gText_DaimynCityMall_FishSeller_BoughtCarvanha MSG_NORMAL
    setflag 0x253 @ Bought Carvanha
    release
    end

FishSellerBought:
    msgbox gText_DaimynCityMall_FishSeller_CarvanhaAlreadyBought MSG_NORMAL
    release
    end

FishSellerSaidNo:
    hidemoney
    msgbox gText_DaimynCityMall_FishSeller_SaidNo MSG_NORMAL
    release
    end

FishSellerNotEnoughMoney:
    hidemoney
    msgbox gText_DaimynCityMall_FishSeller_NotEnoughMoney MSG_NORMAL
    release
    end

FishSellerNoSpaceInParty:
    hidemoney
    msgbox gText_DaimynCityMall_FishSeller_NoRoomInParty MSG_NORMAL
    release
    end

.global EventScript_DaimynCityMall_Shop_Incense
EventScript_DaimynCityMall_Shop_Incense:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_IncenseSeller MSG_KEEPOPEN
    pokemart IncenseShop
    goto EventScript_EndMart

IncenseShop:
    .hword ITEM_LAX_INCENSE
    .hword ITEM_LUCK_INCENSE
    .hword ITEM_ODD_INCENSE
    .hword ITEM_ROCK_INCENSE
    .hword ITEM_ROSE_INCENSE
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_TypeWeaknessBerries
EventScript_DaimynCityMall_Shop_TypeWeaknessBerries:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_TypeWeaknessBerriesSeller MSG_KEEPOPEN
    pokemart TypeBerryShop
    goto EventScript_EndMart

TypeBerryShop:
    .hword ITEM_OCCA_BERRY
    .hword ITEM_PASSHO_BERRY
    .hword ITEM_WACAN_BERRY
    .hword ITEM_RINDO_BERRY
    .hword ITEM_YACHE_BERRY
    .hword ITEM_CHOPLE_BERRY
    .hword ITEM_KEBIA_BERRY
    .hword ITEM_SHUCA_BERRY
    .hword ITEM_COBA_BERRY
    .hword ITEM_PAYAPA_BERRY
    .hword ITEM_TANGA_BERRY
    .hword ITEM_CHARTI_BERRY
    .hword ITEM_KASIB_BERRY
    .hword ITEM_HABAN_BERRY
    .hword ITEM_COLBUR_BERRY
    .hword ITEM_BABIRI_BERRY
    .hword ITEM_CHILAN_BERRY
    .hword ITEM_ROSELI_BERRY
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Fisherman
EventScript_DaimynCityMall_Fisherman:
    npcchat gText_DaimynCityMall_Fisherman
    end

.global EventScript_DaimynCityMall_OldLady
EventScript_DaimynCityMall_OldLady:
    npcchat gText_DaimynCityMall_OldLady
    end

.global EventScript_DaimynCityMall_LostPearlsWoman
EventScript_DaimynCityMall_LostPearlsWoman:
    npcchat gText_DaimynCityMall_LostPearlsWoman
    end

.global EventScript_DaimynCityMall_UndecidedGirl
EventScript_DaimynCityMall_UndecidedGirl:
    npcchat gText_DaimynCityMall_UndecidedGirl
    end

.global EventScript_DaimynCityMall_Camper
EventScript_DaimynCityMall_Camper:
    npcchat gText_DaimynCityMall_Camper
    end

.global EventScript_DaimynCityMall_Blackbelt
EventScript_DaimynCityMall_Blackbelt:
    npcchat gText_DaimynCityMall_Blackbelt
    end

.global EventScript_DaimynCityMall_BugCatcher
EventScript_DaimynCityMall_BugCatcher:
    npcchat gText_DaimynCityMall_BugCatcher
    end

.global EventScript_DaimynCityMall_DateBoy
EventScript_DaimynCityMall_DateBoy:
    npcchat gText_DaimynCityMall_DateBoy
    end

.global EventScript_DaimynCityMall_DateGirl
EventScript_DaimynCityMall_DateGirl:
    npcchat gText_DaimynCityMall_DateGirl
    end

.global EventScript_DaimynCityMall_TiredOldMan
EventScript_DaimynCityMall_TiredOldMan:
    npcchat gText_DaimynCityMall_TiredOldMan
    end

.global EventScript_DaimynCityMall_WaitingGirl
EventScript_DaimynCityMall_WaitingGirl:
    npcchat gText_DaimynCityMall_WaitingGirl
    end

.global EventScript_DaimynCityMall_Shop_EvolutionaryStones
EventScript_DaimynCityMall_Shop_EvolutionaryStones:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_EvolutionStonesSeller MSG_KEEPOPEN
    pokemart EvolutionaryStonesShop
    goto EventScript_EndMart

EvolutionaryStonesShop:
    .hword ITEM_FIRE_STONE
    .hword ITEM_WATER_STONE
    .hword ITEM_THUNDER_STONE
    .hword ITEM_LEAF_STONE
    .hword ITEM_ICE_STONE
    .hword ITEM_SUN_STONE
    .hword ITEM_MOON_STONE
    .hword ITEM_DAWN_STONE
    .hword ITEM_DUSK_STONE
    .hword ITEM_SHINY_STONE
    .hword ITEM_OVAL_STONE
    .hword ITEM_LINK_STONE
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Shop_UncommonHeldItems
EventScript_DaimynCityMall_Shop_UncommonHeldItems:
    lock
    faceplayer
    msgbox gText_DaimynCityMall_HeldItemSeller MSG_KEEPOPEN
    pokemart HeldItemShop
    goto EventScript_EndMart

HeldItemShop:
    .hword ITEM_TOXIC_ORB
    .hword ITEM_FLAME_ORB
    .hword ITEM_BLACK_SLUDGE
    .hword ITEM_LIGHT_CLAY
    .hword ITEM_WHITE_HERB
    .hword ITEM_QUICK_CLAW
    .hword ITEM_WIDE_LENS
    .hword ITEM_BRIGHT_POWDER
    .hword ITEM_BIG_ROOT
    .hword ITEM_NONE

.global EventScript_DaimynCityMall_Rocker
EventScript_DaimynCityMall_Rocker:
    npcchat gText_DaimynCityMall_Rocker
    end

.global SignScript_DaimynCityMall_TallTV
SignScript_DaimynCityMall_TallTV:
    msgbox gText_DaimynCityMall_TallTV MSG_NORMAL
    end

.global SignScript_DaimynCityMall_RetroGame
SignScript_DaimynCityMall_RetroGame:
    msgbox gText_DaimynCityMall_RetroGame MSG_NORMAL
    end

.global SignScript_DaimynCityMall_CampingTV
SignScript_DaimynCityMall_CampingTV:
msgbox gText_DaimynCityMall_CampingTV MSG_NORMAL
    end

.global SignScript_DaimynCityMall_Phone
SignScript_DaimynCityMall_Phone:
    lock
    msgbox gText_DaimynCityMall_PhonePrompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto PhoneChoseNo
    msgbox gText_DaimynCityMall_ChoseToCallMom MSG_NORMAL
    playse 0x2 @ PC Logon
    waitse
    pause DELAY_1SECOND
    playse 0x2 @ PC Logon
    waitse
    pause DELAY_1SECOND
    pause DELAY_1SECOND
    playse 0x4 @ PC On
    pause DELAY_HALFSECOND
    playbgm 0x173 @ Juniper's father's theme
    bufferpartypokemon 0x0 0x0
    msgbox gText_DaimynCityMall_Mom MSG_NORMAL
    playse 0x3 @ PC Off
    waitse
    fadedefaultbgm
    pause DELAY_1SECOND
    playse 0x1 @ Use Item
    msgbox gText_DaimynCityMall_PlayerFeelsBetter MSG_NORMAL
    release
    end

PhoneChoseNo:
    msgbox gText_DaimynCityMall_ChoseNotToCallMom MSG_NORMAL
    release
    end

.global SignScript_DaimynCityMall_ChancePoster
SignScript_DaimynCityMall_ChancePoster:
    msgbox gText_DaimynCityMall_ChancePoster MSG_SIGN
    end

.global SignScript_DaimynCityMall_StoreDirectory
SignScript_DaimynCityMall_StoreDirectory:
    msgbox gText_DaimynCityMall_StoreDirectory MSG_SIGN
    end
