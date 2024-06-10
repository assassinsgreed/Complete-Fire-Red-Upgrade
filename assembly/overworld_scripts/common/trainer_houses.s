.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

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

m_WalkFromRight: .byte walk_down, walk_left, end_m
m_WalkFromBelow: .byte walk_left, walk_up, end_m
m_WalkToBattlefield: .byte walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_up, walk_up, look_right, end_m
m_OpponentWalkToBattlefield: .byte walk_up, walk_up, walk_up, walk_up, walk_right, walk_right, walk_right, walk_up, walk_up, look_left, end_m
m_OpponentWalkAway: .byte walk_down, walk_down, walk_left, walk_left, walk_left, walk_down, walk_down, walk_down, walk_down, end_m
m_ReturnToHost: .byte walk_down, walk_down, walk_right, walk_right, walk_right, walk_right, walk_down, walk_down, walk_down, walk_right, look_up, end_m
m_CameraPanRight: .byte walk_right, walk_right, walk_right, end_m
m_CameraPanLeft: .byte walk_left, walk_left, walk_left, end_m
