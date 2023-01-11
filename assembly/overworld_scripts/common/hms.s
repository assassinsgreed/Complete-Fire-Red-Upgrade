.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Common_Cut
EventScript_Common_Cut:
    lockall
    checkflag 0x821 @ Patch Badge, Gym 2
    if FALSE _goto EventScript_Common_CutFillerText
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
    applymovement LASTTALKED 0x81BDF85 @ Cut animation
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    goto ReleaseAll

.global EventScript_Common_RockSmash
EventScript_Common_RockSmash:
    lockall
    checkflag 0x822 @ Stormcloud Badge, Gym 3
    if FALSE _goto EventScript_Common_RockFillerText

EventScript_Common_RockFillerText:
    msgbox gText_Common_SmashableRock MSG_SIGN
    goto ReleaseAll
    special 0x10B @ Check if party Pokemon can learn Rock Smash
    compare 0x8004 0x6
    if equal _goto EventScript_Common_RockFillerText
    setanimation 0x0 0x8004 @ Show Pokeball raising animation
    bufferpartypokemon 0x0 0x8004 @ Store first Pokemon compatible with Cut
    bufferattack 0x1 0xF9 @ Store Rock Smash attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x25
    waitstate
    goto EventScript_Common_SmashRock

EventScript_Common_SmashRock:
    applymovement LASTTALKED 0x81BE08F @ Rock Smash animation
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    goto ReleaseAll

ReleaseAll:
    releaseall
    end
