.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Pokemart stock is based on Gen 8 SW/SH list
.global EventScript_Pokemart
EventScript_Pokemart:
    lock
    faceplayer
    special 0x187
    compare LASTRESULT 0x2
    if 0x1 _goto End
    checkflag 0x829 @ Has Pokedex
    if NOT_SET _goto EventScript_PokemartNotReady
    checkflag 0x25C @ New Pokemart Stock
    if SET _call EventScript_PokemartNewStock
    msgbox gText_Common_PokemartIntro MSG_KEEPOPEN
    checkflag 0x827 @ Eight Badges
    if SET _goto EventScript_EightBadges
    checkflag 0x826 @ Seven Badges
    if SET _goto EventScript_SevenBadges
    checkflag 0x825 @ Six Badges
    if SET _goto EventScript_SixBadges
    checkflag 0x824 @ Five Badges
    if SET _goto EventScript_FiveBadges
    checkflag 0x823 @ Four Badges
    if SET _goto EventScript_FourBadges
    checkflag 0x822 @ Three Badges
    if SET _goto EventScript_ThreeBadges
    checkflag 0x821 @ Two Badges
    if SET _goto EventScript_TwoBadges
    checkflag 0x820 @ One Badge
    if SET _goto EventScript_OneBadge
    goto EventScript_NoBadges @ No badges

EventScript_PokemartNewStock:
    msgbox gText_Common_PokemartNewStock MSG_NORMAL
    clearflag 0x25C @ New stock
    return

EventScript_NoBadges:
    pokemart NoBadges_Stock
    goto EventScript_EndMart

EventScript_OneBadge:
    pokemart OneBadge_Stock
    goto EventScript_EndMart

EventScript_TwoBadges:
    pokemart TwoBadges_Stock
    goto EventScript_EndMart

EventScript_ThreeBadges:
    pokemart ThreeBadges_Stock
    goto EventScript_EndMart

EventScript_FourBadges:
    pokemart FourBadges_Stock
    goto EventScript_EndMart

EventScript_FiveBadges:
    pokemart FiveBadges_Stock
    goto EventScript_EndMart

EventScript_SixBadges:
    pokemart SixBadges_Stock
    goto EventScript_EndMart

EventScript_SevenBadges:
    pokemart SevenBadges_Stock
    goto EventScript_EndMart

EventScript_EightBadges:
    pokemart EightBadges_Stock
    goto EventScript_EndMart

.align 1
NoBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_POTION
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_NONE

.align 1
OneBadge_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
TwoBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
ThreeBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
FourBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
FiveBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
SixBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
SevenBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_MAX_POTION
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_MAX_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.align 1
EightBadges_Stock:
    .hword ITEM_POKE_BALL
    .hword ITEM_GREAT_BALL
    .hword ITEM_ULTRA_BALL
    .hword ITEM_POTION
    .hword ITEM_SUPER_POTION
    .hword ITEM_HYPER_POTION
    .hword ITEM_MAX_POTION
    .hword ITEM_FULL_RESTORE
    .hword ITEM_POKE_DOLL
    .hword ITEM_ANTIDOTE
    .hword ITEM_BURN_HEAL
    .hword ITEM_ICE_HEAL
    .hword ITEM_AWAKENING
    .hword ITEM_PARALYZE_HEAL
    .hword ITEM_FULL_HEAL
    .hword ITEM_REPEL
    .hword ITEM_SUPER_REPEL
    .hword ITEM_MAX_REPEL
    .hword ITEM_HONEY
    .hword ITEM_REVIVE
    .hword ITEM_ESCAPE_ROPE
    .hword ITEM_NONE

.global EventScript_EndMart    
EventScript_EndMart:
    msgbox gText_Common_PokemartEnd MSG_NORMAL
    textcolor 0xFF @ Reset color to OW default
    goto End

EventScript_PokemartNotReady:
    msgbox gText_Common_PokemartNotReady MSG_NORMAL
    goto End

@@ Common shops used in multiple places
.align 1
.global VitaminsShop
VitaminsShop:
    .hword ITEM_HP_UP
    .hword ITEM_PROTEIN
    .hword ITEM_IRON
    .hword ITEM_CALCIUM
    .hword ITEM_ZINC
    .hword ITEM_CARBOS
    .hword ITEM_PP_UP
    .hword ITEM_NONE

.global EVReducingBerriesShop
.align 1
EVReducingBerriesShop:
    .hword ITEM_POMEG_BERRY
    .hword ITEM_KELPSY_BERRY
    .hword ITEM_QUALOT_BERRY
    .hword ITEM_HONDEW_BERRY
    .hword ITEM_GREPA_BERRY
    .hword ITEM_TAMATO_BERRY
    .hword ITEM_NONE

// Pokemon Center

.global EventScript_PokemonCenter_Main
EventScript_PokemonCenter_Main:
    lock
    faceplayer
    special 0x187
	compare LASTRESULT 0x2
	if TRUE _goto EventScript_PokemonCenter_End
    msgbox gText_Common_PokemonCenterHealChoice MSG_YESNO
	compare LASTRESULT YES
	if TRUE _goto EventScript_PokemonCenter_Heal
	goto EventScript_PokemonCenter_Farewell
	goto EventScript_PokemonCenter_End

EventScript_PokemonCenter_End:
	release
	end

EventScript_PokemonCenter_Heal:
	msgbox gText_Common_PokemonCenterTakePokemon MSG_KEEPOPEN
	applymovement LASTTALKED m_NurseLookLeft
	waitmovement 0x0
	doanimation 0x19
	waitanimation 0x19
	applymovement LASTTALKED m_NurseLookDown
	waitmovement 0x0
	special 0x0
	special 0x169
	special2 LASTRESULT 0x1B1
	compare LASTRESULT TRUE
	if TRUE _goto EventScript_PokemonCenter_HealComplete
	special2 LASTRESULT 0x183
	copyvar 0x8008 LASTRESULT
	compare 0x8008 TRUE
	if TRUE _goto EventScript_PokemonCenter_HealComplete
	end

EventScript_PokemonCenter_Farewell:
	msgbox gText_Common_PokemonFarewell MSG_NORMAL
	return

EventScript_PokemonCenter_HealComplete:
	incrementgamestat 15
	msgbox gText_Common_PokemonCenterHealed MSG_NORMAL
	applymovement LASTTALKED m_NurseBow
	waitmovement 0x0
	call EventScript_PokemonCenter_Farewell
    return

@ Movements
m_NurseLookLeft:
.byte walk_left_onspot_fastest, end_m

m_NurseLookDown:
.byte walk_down_onspot_fastest, end_m

m_NurseBow:
.byte nurse_bow, pause_short, end_m

// Trainer House

.global TrainerHouse_Common_AlreadyBattledToday
TrainerHouse_Common_AlreadyBattledToday:
    msgbox gText_TrainerHouse_AlreadyChallengedToday MSG_NORMAL
    goto End

.global TrainerHouse_Common_MoveToBattlePosition
TrainerHouse_Common_MoveToBattlePosition:
    getplayerpos 0x4000 0x4001 @ Get player x y into variables
    compare 0x4000 0xA
    if equal _call MovePlayerFromRight
    compare 0x4000 0x9
    if equal _call MovePlayerFromBelow
    applymovement PLAYER m_WalkToBattlefield
    waitmovement ALLEVENTS
    special CAMERA_START
    applymovement CAMERA m_CameraPanRight
    waitmovement CAMERA
    special CAMERA_END
    return

MovePlayerFromRight:
    applymovement PLAYER m_WalkFromRight
    waitmovement ALLEVENTS
    getplayerpos 0x4000 0x4001 @ Get player's new x y into variables
    return

MovePlayerFromBelow:
    applymovement PLAYER m_WalkFromBelow
    waitmovement ALLEVENTS
    return

.global TrainerHouse_Common_OpponentArrives
TrainerHouse_Common_OpponentArrives:
    movesprite 0x8001 0x8 0xC @ Center of the room
    clearflag 0x37 @ Show opponent
    showsprite 0x8001
    applymovement 0x8001 m_OpponentWalkToBattlefield
    waitmovement ALLEVENTS
    playbgm 0x156 @ Cool trainer
    return

.global TrainerHouse_Common_OpponentLeaves
TrainerHouse_Common_OpponentLeaves:
    applymovement 0x8001 m_OpponentWalkAway
    waitmovement ALLEVENTS
    hidesprite 0x8001
    setflag 0x37 @ Hide opponent
    return

.global TrainerHouse_Common_ReturnToHost
TrainerHouse_Common_ReturnToHost:
    special CAMERA_START
    applymovement CAMERA m_CameraPanLeft
    waitmovement CAMERA
    special CAMERA_END
    applymovement PLAYER m_ReturnToHost
    waitmovement ALLEVENTS
    applymovement 0x1 m_LookDown
    return

.global TrainerHouse_Common_End
TrainerHouse_Common_End:
    msgbox gText_TrainerHouse_Exit MSG_NORMAL
    goto End

// Prizes
.global TrainerHouse_Common_GivePokeball
TrainerHouse_Common_GivePokeball:
    obtainitem ITEM_POKE_BALL 0x1
    return

.global TrainerHouse_Common_GivePotion
TrainerHouse_Common_GivePotion:
    obtainitem ITEM_POTION 0x1
    return

.global TrainerHouse_Common_GiveGreatBall
TrainerHouse_Common_GiveGreatBall:
    obtainitem ITEM_GREAT_BALL 0x1
    return

.global TrainerHouse_Common_GiveSuperPotion
TrainerHouse_Common_GiveSuperPotion:
    obtainitem ITEM_SUPER_POTION 0x1
    return

.global TrainerHouse_Common_GiveRepel
TrainerHouse_Common_GiveRepel:
    obtainitem ITEM_REPEL 0x1
    return

.global TrainerHouse_Common_GiveUltraBall
TrainerHouse_Common_GiveUltraBall:
    obtainitem ITEM_ULTRA_BALL 0x1
    return

.global TrainerHouse_Common_GiveMoomooMilk
TrainerHouse_Common_GiveMoomooMilk:
    obtainitem ITEM_MOOMOO_MILK 0x1
    return

.global TrainerHouse_Common_GiveFullHeal
TrainerHouse_Common_GiveFullHeal:
    obtainitem ITEM_FULL_HEAL 0x1
    return

.global TrainerHouse_Common_GiveHyperPotion
TrainerHouse_Common_GiveHyperPotion:
    obtainitem ITEM_HYPER_POTION 0x1
    return

.global TrainerHouse_Common_GiveRevive
TrainerHouse_Common_GiveRevive:
    obtainitem ITEM_REVIVE 0x1
    return

.global TrainerHouse_Common_GiveQuickBall
TrainerHouse_Common_GiveQuickBall:
    obtainitem ITEM_QUICK_BALL 0x1
    return

.global TrainerHouse_Common_GiveMaxPotion
TrainerHouse_Common_GiveMaxPotion:
    obtainitem ITEM_MAX_POTION 0x1
    return

.global TrainerHouse_Common_GiveFullRestore
TrainerHouse_Common_GiveFullRestore:
    obtainitem ITEM_FULL_RESTORE 0x1
    return

.global TrainerHouse_Common_GiveMaxRevive
TrainerHouse_Common_GiveMaxRevive:
    obtainitem ITEM_MAX_REVIVE 0x1
    return

.global TrainerHouse_Common_GivePPMax
TrainerHouse_Common_GivePPMax:
    obtainitem ITEM_PP_MAX 0x1
    return

m_WalkFromRight: .byte walk_down, walk_left, end_m
m_WalkFromBelow: .byte walk_left, walk_up, end_m
m_WalkToBattlefield: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, look_right, end_m
m_OpponentWalkToBattlefield: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, walk_up, look_left, end_m
m_OpponentWalkAway: .byte walk_down, walk_down, walk_left, walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, end_m
m_ReturnToHost: .byte walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_right, look_up, end_m
m_CameraPanRight: .byte walk_right, walk_right, walk_right, end_m
m_CameraPanLeft: .byte walk_left, walk_left, walk_left, end_m
