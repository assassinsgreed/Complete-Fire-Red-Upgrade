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
    compare LASTRESULT NO
    IF NO _goto EventScript_Common_CutFillerText
    setanimation 0x0 LASTRESULT @ Show Pokeball raising animation
    bufferpartypokemon 0x0 LASTRESULT @ Store first Pokemon compatible with Cut
    bufferattack 0x1 0xF @ Store Cut attack name
    msgbox gText_Common_PokemonUsedHM MSG_KEEPOPEN
    closeonkeypress
    doanimation 0x2
    waitstate
    goto EventScript_Common_CutTree

EventScript_Common_CutFillerText:
    msgbox gText_Common_CuttableTree MSG_SIGN
    releaseall
    end

EventScript_Common_CutTree:
    applymovement LASTTALKED 0x81BDF85 @ cut animation
    waitmovement ALLEVENTS
    hidesprite LASTTALKED
    releaseall
    end
