.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_Route7_CamperCarlisle
EventScript_Route7_CamperCarlisle:
    trainerbattle0 0x0 0xF 0x0 gText_Route1_CamperCarlisle_Intro gText_Route1_CamperCarlisle_Defeat
    msgbox gText_Route1_CamperCarlisle_Chat MSG_NORMAL
    end

.global SignScript_Route7_TrainerTips
SignScript_Route7_TrainerTips:
    msgbox gText_Route7_TrainerTips MSG_SIGN
    end
