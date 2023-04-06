.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ StoryEventVar, 0x4052
.equ MetAlistairAtLibrary, 0x2

.global SignScript_FerroxGym_Placard
SignScript_FerroxGym_Placard:
    checkflag 0x821 @ Ferrox gym badge
    if SET _goto SignScript_FerroxGym_PlacardWithBadge
    checkflag 0x039 @ Hide Stella in Ferrox Library
    if SET _goto SignScript_FerroxGym_PlacardAfterLibrary
    msgbox gText_FerroxGym_Winners MSG_SIGN
    end

SignScript_FerroxGym_PlacardWithBadge:
    msgbox gText_FerroxGym_WinnersWithBadge MSG_SIGN
    end

SignScript_FerroxGym_PlacardAfterLibrary:
    msgbox gText_FerroxGym_WinnersAfterLibrary MSG_SIGN
    end

.global EventScript_FerroxGym_GymExpert
EventScript_FerroxGym_GymExpert:
    checkflag 0x821 @ Ferrox gym badge
    if SET _goto EventScript_FerroxGym_GymExpertBadgeObtained
    checkflag 0x039 @ Hide Stella in Ferrox Library
    if SET _goto EventScript_FerroxGym_GymExpertTips
    npcchat gText_FerroxGym_ExpertLeaderOut
    end

EventScript_FerroxGym_GymExpertBadgeObtained:
    npcchat gText_FerroxGym_ExpertBadgeObtained
    end

EventScript_FerroxGym_GymExpertTips:
    npcchat gText_FerroxGym_ExpertTips
    end
