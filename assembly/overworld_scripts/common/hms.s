.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

/*
    Move Name indexes:
    Cut         0xF
    Fly         0x13
    Surf        0x39
    Strength    0x46
    Rock Smash  0xF9
 */

.global EventScript_Common_Cut
EventScript_Common_Cut:
    lockall
    checkflag 0x821 @ Patch Badge, Gym 2
    if NOT_SET _goto EventScript_Common_CutFillerText
    special 0x10A @ Check if party Pokemon can learn Cut
    compare 0x8004 0x6
    IF equal _goto EventScript_Common_CutFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Cut
    bufferattack 0x1 0xF @ Store Cut attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x2
    waitstate
    goto EventScript_Common_CutTree

EventScript_Common_CutFillerText:
    msgbox gText_Common_CuttableTree MSG_SIGN
    goto ReleaseAll

EventScript_Common_CutTree:
    applymovement LASTTALKED m_CutTree
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    goto ReleaseAll

.global EventScript_Common_RockSmash
EventScript_Common_RockSmash:
    lockall
    checkflag 0x822 @ Stormcloud Badge, Gym 3
    if NOT_SET _goto EventScript_Common_RockFillerText
    special 0x10B @ Check if party Pokemon can learn Rock Smash
    compare 0x8004 0x6
    if equal _goto EventScript_Common_RockFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Rock Smash
    bufferattack 0x1 0xF9 @ Store Rock Smash attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x25
    waitstate
    goto EventScript_Common_SmashRock


EventScript_Common_RockFillerText:
    msgbox gText_Common_SmashableRock MSG_SIGN
    goto ReleaseAll

EventScript_Common_SmashRock:
    applymovement LASTTALKED m_SmashRock
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    goto ReleaseAll

.global EventScript_Common_Strength
EventScript_Common_Strength:
    checkflag 0x805
    if SET _goto ReleaseAll
    lockall
    checkflag 0x826 @ Support Badge, Gym 7
    if NOT_SET _goto EventScript_Common_StrengthFillerText
    special 0x10C @ Check if party Pokemon can learn Strength
    compare 0x8004 0x6
    if equal _goto EventScript_Common_StrengthFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Rock Smash
    bufferattack 0x1 0x46 @ Store Strength attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x28
    waitstate
    setflag 0x805 @ Can now push boulders while on this map
    goto ReleaseAll

EventScript_Common_StrengthFillerText:
    msgbox gText_Common_PushableRock MSG_SIGN
    goto ReleaseAll

ReleaseAll:
    releaseall
    end

m_CutTree: .byte cut_tree, end_m
m_SmashRock: .byte smash_rock, end_m
