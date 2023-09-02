.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route2_YoungsterJoey
EventScript_Route2_YoungsterJoey:
    trainerbattle0 0x0 0x5 0x0 gText_Route2_YoungsterJoey_Intro gText_Route2_YoungsterJoey_Defeat
    msgbox gText_Route2_YoungsterJoey_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassKimberly
EventScript_Route2_LassKimberly:
    trainerbattle0 0x0 0x6 0x0 gText_Route2_LassKimberly_Intro gText_Route2_LassKimberly_Defeat
    msgbox gText_Route2_LassKimberly_Chat MSG_NORMAL
    end

.global EventScript_Route2_LassRikki
EventScript_Route2_LassRikki:
    trainerbattle0 0x0 0x7 0x0 gText_Route2_LassRikki_Intro gText_Route2_LassRikki_Defeat
    msgbox gText_Route2_LassRikki_Chat MSG_NORMAL
    end

.global EventScript_Route2_FindTMInfestation
EventScript_Route2_FindTMInfestation:
    setvar CHOSEN_ITEM ITEM_TM83
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_FindTMNaturePower
EventScript_Route2_FindTMNaturePower:
    setvar CHOSEN_ITEM ITEM_TM96
    call ItemScript_Common_FindTM
    end

.global EventScript_Route2_CoolTrainerAndy
EventScript_Route2_CoolTrainerAndy:
    trainerbattle0 0x0 0x10 0x0 gText_Route2_CoolTrainerAndy_Intro gText_Route2_CoolTrainerAndy_Defeat
    msgbox gText_Route2_CoolTrainerAndy_Chat MSG_NORMAL
    end

.global SignScript_Route2_TrainerTipsFishing
SignScript_Route2_TrainerTipsFishing:
    msgbox gText_Route2_TrainerTips MSG_SIGN
    end
