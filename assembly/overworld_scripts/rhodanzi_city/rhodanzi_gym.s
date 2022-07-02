.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_RhodanziGym_Alonso
EventScript_RhodanziGym_Alonso:
    trainerbattle0 0x0 0xc 0x0 gText_RhodanziGym_Alonso_Intro gText_RhodanziGym_Alonso_Defeat
    msgbox gText_RhodanziGym_Alonso_Chat MSG_NORMAL
    end