.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"


.global EventScript_DaimynCityMall_LuckyDrawLady
EventScript_DaimynCityMall_LuckyDrawLady:


.global EventScript_DaimynCityMall_Greeter
EventScript_DaimynCityMall_Greeter:


.global EventScript_DaimynCityMall_Shop_Herbalist
EventScript_DaimynCityMall_Shop_Herbalist:


.global EventScript_DaimynCityMall_Shop_Consumables
EventScript_DaimynCityMall_Shop_Consumables:


.global EventScript_DaimynCityMall_Shop_DealOfTheDay
EventScript_DaimynCityMall_Shop_DealOfTheDay:


.global EventScript_DaimynCityMall_MagazineSeller
EventScript_DaimynCityMall_MagazineSeller:


.global EventScript_DaimynCityMall_Shop_Pokeballs
EventScript_DaimynCityMall_Shop_Pokeballs:


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


.global EventScript_DaimynCityMall_Shop_TMs
EventScript_DaimynCityMall_Shop_TMs:


.global EventScript_DaimynCityMall_Shop_SeedSeller
EventScript_DaimynCityMall_Shop_SeedSeller:


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


.global EventScript_DaimynCityMall_Shop_TypeBoosterItems
EventScript_DaimynCityMall_Shop_TypeBoosterItems:


.global EventScript_DaimynCityMall_FishSeller
EventScript_DaimynCityMall_FishSeller:


.global EventScript_DaimynCityMall_Shop_MoomooMilkDistributor
EventScript_DaimynCityMall_Shop_MoomooMilkDistributor:


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


.global EventScript_DaimynCityMall_OldLady
EventScript_DaimynCityMall_OldLady:


.global EventScript_DaimynCityMall_LostPearlsWoman
EventScript_DaimynCityMall_LostPearlsWoman:


.global EventScript_DaimynCityMall_UndecidedGirl
EventScript_DaimynCityMall_UndecidedGirl:


.global EventScript_DaimynCityMall_Picknicker
EventScript_DaimynCityMall_Picknicker:


.global EventScript_DaimynCityMall_Blackbelt
EventScript_DaimynCityMall_Blackbelt:


.global EventScript_DaimynCityMall_BugCatcher
EventScript_DaimynCityMall_BugCatcher:


.global EventScript_DaimynCityMall_DateBoy
EventScript_DaimynCityMall_DateBoy:


.global EventScript_DaimynCityMall_DateGirl
EventScript_DaimynCityMall_DateGirl:


.global EventScript_DaimynCityMall_TiredOldMan
EventScript_DaimynCityMall_TiredOldMan:


.global EventScript_DaimynCityMall_WaitingGirl
EventScript_DaimynCityMall_WaitingGirl:


.global EventScript_DaimynCityMall_Shop_EvolutionaryStones
EventScript_DaimynCityMall_Shop_EvolutionaryStones:


.global EventScript_DaimynCityMall_Shop_UncommonHeldItems
EventScript_DaimynCityMall_Shop_UncommonHeldItems:


.global EventScript_DaimynCityMall_Rocker
EventScript_DaimynCityMall_Rocker:


.global SignScript_DaimynCityMall_TallTV
SignScript_DaimynCityMall_TallTV:


.global SignScript_DaimynCityMall_RetroGame
SignScript_DaimynCityMall_RetroGame:


.global SignScript_DaimynCityMall_CampingTV
SignScript_DaimynCityMall_CampingTV:


.global SignScript_DaimynCityMall_Phone
SignScript_DaimynCityMall_Phone:


.global SignScript_DaimynCityMall_ChancePoster
SignScript_DaimynCityMall_ChancePoster:


.global SignScript_DaimynCityMall_StoreDirectory
SignScript_DaimynCityMall_StoreDirectory:

