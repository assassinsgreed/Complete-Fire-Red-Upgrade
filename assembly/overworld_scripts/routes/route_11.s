.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

# Includes both Route 11 South and North

.global EventScript_Route11South_TM68GigaImpact
EventScript_Route11South_TM68GigaImpact:
    setvar CHOSEN_ITEM ITEM_TM68
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11South_TM51SteelWing
EventScript_Route11South_TM51SteelWing:
    setvar CHOSEN_ITEM ITEM_TM51
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11South_Mawilite
EventScript_Route11South_Mawilite:
    finditem ITEM_MAWILITE 0x1
    end

.global EventScript_Route11South_TeamPlutoRoss
EventScript_Route11South_TeamPlutoRoss:
    trainerbattle0 0x0 0xB3 0x0 gText_Route11South_TeamPlutoRoss_Intro gText_Route11South_TeamPlutoRoss_Defeat
    msgbox gText_Route11South_TeamPlutoRoss_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoGreta
EventScript_Route11South_TeamPlutoGreta:
    trainerbattle0 0x0 0xB4 0x0 gText_Route11South_TeamPlutoGreta_Intro gText_Route11South_TeamPlutoGreta_Defeat
    msgbox gText_Route11South_TeamPlutoGreta_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoNellie
EventScript_Route11South_TeamPlutoNellie:
    trainerbattle0 0x0 0xB5 0x0 gText_Route11South_TeamPlutoNellie_Intro gText_Route11South_TeamPlutoNellie_Defeat
    msgbox gText_Route11South_TeamPlutoNellie_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoHelga
EventScript_Route11South_TeamPlutoHelga:
    trainerbattle0 0x0 0xB6 0x0 gText_Route11South_TeamPlutoHelga_Intro gText_Route11South_TeamPlutoHelga_Defeat
    msgbox gText_Route11South_TeamPlutoHelga_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoKareem
EventScript_Route11South_TeamPlutoKareem:
    trainerbattle0 0x0 0xB7 0x0 gText_Route11South_TeamPlutoKareem_Intro gText_Route11South_TeamPlutoKareem_Defeat
    msgbox gText_Route11South_TeamPlutoKareem_Chat MSG_NORMAL
    end

.global EventScript_Route11South_TeamPlutoChung
EventScript_Route11South_TeamPlutoChung:
    trainerbattle0 0x0 0xB8 0x0 gText_Route11South_TeamPlutoChung_Intro gText_Route11South_TeamPlutoChung_Defeat
    msgbox gText_Route11South_TeamPlutoChung_Chat MSG_NORMAL
    end

.global EventScript_Route11South_LassTabitha
EventScript_Route11South_LassTabitha:
    trainerbattle0 0x0 0xB9 0x0 gText_Route11South_LassTabitha_Intro gText_Route11South_LassTabitha_Defeat
    msgbox gText_Route11South_LassTabitha_Chat MSG_NORMAL
    end

.global EventScript_Route11South_CrushGirlAlisa
EventScript_Route11South_CrushGirlAlisa:
    trainerbattle0 0x0 0xBA 0x0 gText_Route11South_CrushGirlAlisa_Intro gText_Route11South_CrushGirlAlisa_Defeat
    msgbox gText_Route11South_CrushGirlAlisa_Chat MSG_NORMAL
    end

.global EventScript_Route11South_EngineerDale
EventScript_Route11South_EngineerDale:
    trainerbattle0 0x0 0xBB 0x0 gText_Route11South_EngineerDale_Intro gText_Route11South_EngineerDale_Defeat
    msgbox gText_Route11South_EngineerDale_Chat MSG_NORMAL
    end

.global EventScript_Route11South_CollectorOrville
EventScript_Route11South_CollectorOrville:
    trainerbattle0 0x0 0xBC 0x0 gText_Route11South_CollectorOrville_Intro gText_Route11South_CollectorOrville_Defeat
    msgbox gText_Route11South_CollectorOrville_Chat MSG_NORMAL
    end

.global SignScript_Route11South_HessonPass
SignScript_Route11South_HessonPass:
    msgbox gText_Route11South_HessonPassSign MSG_SIGN
    end

.global SignScript_Route11South_TrainerTips
SignScript_Route11South_TrainerTips:
    msgbox gText_Route11South_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route11South_MegaStoneRefiner
SignScript_Route11South_MegaStoneRefiner:
    msgbox gText_Route11South_MegaStoneRefinerSign MSG_SIGN
    end
