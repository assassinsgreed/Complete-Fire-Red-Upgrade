.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route12East_TriathleteJoanne
EventScript_Route12East_TriathleteJoanne:
    trainerbattle0 0x0 246 0x0 gText_Route12East_TriathleteJoanne_Intro gText_Route12East_TriathleteJoanne_Defeat
    msgbox gText_Route12East_TriathleteJoanne_Chat MSG_NORMAL
    end

.global EventScript_Route12East_PsychicTony
EventScript_Route12East_PsychicTony:
    trainerbattle0 0x0 247 0x0 gText_Route12East_PsychicTony_Intro gText_Route12East_PsychicTony_Defeat
    msgbox gText_Route12East_PsychicTony_Chat MSG_NORMAL
    end

.global EventScript_Route12East_HikerDwight
EventScript_Route12East_HikerDwight:
    trainerbattle0 0x0 248 0x0 gText_Route12East_HikerDwight_Intro gText_Route12East_HikerDwight_Defeat
    msgbox gText_Route12East_HikerDwight_Chat MSG_NORMAL
    end

.global EventScript_Route12East_TriathleteTrixie
EventScript_Route12East_TriathleteTrixie:
    trainerbattle0 0x0 249 0x0 gText_Route12East_TriathleteTrixie_Intro gText_Route12East_TriathleteTrixie_Defeat
    msgbox gText_Route12East_TriathleteTrixie_Chat MSG_NORMAL
    end

.global EventScript_Route12East_GentlemanGeoffrey
EventScript_Route12East_GentlemanGeoffrey:
    trainerbattle0 0x0 250 0x0 gText_Route12East_GentlemanGeoffrey_Intro gText_Route12East_GentlemanGeoffrey_Defeat
    msgbox gText_Route12East_GentlemanGeoffrey_Chat MSG_NORMAL
    end

.global EventScript_Route12East_TM95_Snarl
EventScript_Route12East_TM95_Snarl:
    setvar CHOSEN_ITEM ITEM_TM95
    call ItemScript_Common_FindTM
    end

.global SignScript_Route12East_TrainerTipsHeldEvolutions
SignScript_Route12East_TrainerTipsHeldEvolutions:
    msgbox gText_Route12East_TrainerTipsHeldEvolutions MSG_SIGN
    end

.global SignScript_Route12East_TrainerTipsPremierBalls
SignScript_Route12East_TrainerTipsPremierBalls:
    msgbox gText_Route12East_TrainerTipsPremierBalls MSG_SIGN
    end

.global SignScript_Route12East_Route12Spa
SignScript_Route12East_Route12Spa:
    msgbox gText_Route12East_Route12Spa MSG_SIGN
    end
