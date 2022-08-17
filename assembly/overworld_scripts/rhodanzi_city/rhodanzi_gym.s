.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_RhodanziGym_GymExpert
EventScript_RhodanziGym_GymExpert:
    // TODO: Fill out
    end

.global EventScript_RhodanziGym_Alonso
EventScript_RhodanziGym_Alonso:
    trainerbattle0 0x0 0xC 0x0 gText_RhodanziGym_Alonso_Intro gText_RhodanziGym_Alonso_Defeat
    msgbox gText_RhodanziGym_Alonso_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Brandon
EventScript_RhodanziGym_Brandon:
    trainerbattle0 0x0 0xD 0x0 gText_RhodanziGym_Brandon_Intro gText_RhodanziGym_Brandon_Defeat
    msgbox gText_RhodanziGym_Brandon_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Leader_Terrence
EventScript_RhodanziGym_Leader_Terrence:
    // TODO: Flesh Terrence out more; he's a normal encounter at the moment
    trainerbattle0 0x0 0xE 0x0 gText_RhodanziGym_Leader_Terrence_Intro gText_RhodanziGym_Leader_Terrence_Defeat
    msgbox gText_RhodanziGym_Leader_Terrence_Chat MSG_NORMAL
    end
