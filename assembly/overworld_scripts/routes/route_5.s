.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route5_Biker
EventScript_Route5_Biker:
    msgbox gText_Route5_Biker MSG_NORMAL
    goto FindAnotherRoute

.global EventScript_Route5_BikerLeader
EventScript_Route5_BikerLeader:
    msgbox gText_Route5_BikerLeader MSG_NORMAL
    goto FindAnotherRoute

FindAnotherRoute:
    msgbox gText_Route5_AnotherRoute MSG_NORMAL
    end
