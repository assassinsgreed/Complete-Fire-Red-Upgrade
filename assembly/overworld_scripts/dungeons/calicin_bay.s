.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_CalicinBay_SkierRita
EventScript_CalicinBay_SkierRita:
    trainerbattle0 0x0 280 0x0 gText_CalicinBay_SkierRita_Intro gText_CalicinBay_SkierRita_Defeat
    msgbox gText_CalicinBay_SkierRita_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerFFran
EventScript_CalicinBay_SwimmerFFran:
    trainerbattle0 0x0 281 0x0 gText_CalicinBay_SwimmerFran_Intro gText_CalicinBay_SwimmerFran_Defeat
    msgbox gText_CalicinBay_SwimmerFran_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerMAngelo
EventScript_CalicinBay_SwimmerMAngelo:
    trainerbattle0 0x0 282 0x0 gText_CalicinBay_SwimmerAngelo_Intro gText_CalicinBay_SwimmerAngelo_Defeat
    msgbox gText_CalicinBay_SwimmerAngelo_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerMSebastian
EventScript_CalicinBay_SwimmerMSebastian:
    trainerbattle0 0x0 283 0x0 gText_CalicinBay_SwimmerSebastian_Intro gText_CalicinBay_SwimmerSebastian_Defeat
    msgbox gText_CalicinBay_SwimmerSebastian_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_SwimmerFCorrine
EventScript_CalicinBay_SwimmerFCorrine:
    trainerbattle0 0x0 284 0x0 gText_CalicinBay_SwimmerCorrine_Intro gText_CalicinBay_SwimmerCorrine_Defeat
    msgbox gText_CalicinBay_SwimmerCorrine_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_FishermanOliver
EventScript_CalicinBay_FishermanOliver:
    trainerbattle0 0x0 285 0x0 gText_CalicinBay_FishermanOliver_Intro gText_CalicinBay_FishermanOliver_Defeat
    msgbox gText_CalicinBay_FishermanOliver_Chat MSG_NORMAL
    end

.global EventScript_CalicinBay_TM14Blizzard
EventScript_CalicinBay_TM14Blizzard:
    setvar CHOSEN_ITEM ITEM_TM14
    call ItemScript_Common_FindTM
    end

.global EventScript_CalicinBay_CalicinBaySign
EventScript_CalicinBay_CalicinBaySign:
    msgbox gText_CalicinBay_CalicinBaySign MSG_SIGN
    end