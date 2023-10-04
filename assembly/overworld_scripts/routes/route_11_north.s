.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global SignScript_LaplazTown_Entrance
SignScript_LaplazTown_Entrance:
    msgbox gText_LaplazTown_EntranceSign MSG_SIGN
    end

.global SignScript_Route11North_LaplazTenets
SignScript_Route11North_LaplazTenets:
    msgbox gText_Route11North_LaplazTenetsSign MSG_SIGN
    end

.global EventScript_Route11North_TM03Psyshock
EventScript_Route11North_TM03Psyshock:
    setvar CHOSEN_ITEM ITEM_TM03
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11North_TM47LowSweep
EventScript_Route11North_TM47LowSweep:
    setvar CHOSEN_ITEM ITEM_TM47
    call ItemScript_Common_FindTM
    end

.global EventScript_Route11North_PainterIsobel
EventScript_Route11North_PainterIsobel:
    trainerbattle0 0x0 0xD9 0x0 gText_Route11North_PainterIsobel_Intro gText_Route11North_PainterIsobel_Defeat
    msgbox gText_Route11North_PainterIsobel_Chat MSG_NORMAL
    end

.global EventScript_Route11North_FishermanClint
EventScript_Route11North_FishermanClint:
    trainerbattle0 0x0 0xDA 0x0 gText_Route11North_FishermanClint_Intro gText_Route11North_FishermanClint_Defeat
    msgbox gText_Route11North_FishermanClint_Chat MSG_NORMAL
    end

.global EventScript_Route11North_ChannelerKatya
EventScript_Route11North_ChannelerKatya:
    trainerbattle0 0x0 0xDB 0x0 gText_Route11North_ChannelerKatya_Intro gText_Route11North_ChannelerKatya_Defeat
    msgbox gText_Route11North_ChannelerKatya_Chat MSG_NORMAL
    end

.global EventScript_Route11North_RockerNathaniel
EventScript_Route11North_RockerNathaniel:
    trainerbattle0 0x0 0xDC 0x0 gText_Route11North_RockerNathaniel_Intro gText_Route11North_RockerNathaniel_Defeat
    msgbox gText_Route11North_RockerNathaniel_Chat MSG_NORMAL
    end

.global EventScript_Route11North_NinjaBoyYao
EventScript_Route11North_NinjaBoyYao:
    trainerbattle0 0x0 0xDD 0x0 gText_Route11North_NinjaBoyYao_Intro gText_Route11North_NinjaBoyYao_Defeat
    msgbox gText_Route11North_NinjaBoyYao_Chat MSG_NORMAL
    end

.global EventScript_Route11North_ParasolLadyTina
EventScript_Route11North_ParasolLadyTina:
    trainerbattle0 0x0 0xDE 0x0 gText_Route11North_ParasolLadyTina_Intro gText_Route11North_ParasolLadyTina_Defeat
    msgbox gText_Route11North_ParasolLadyTina_Chat MSG_NORMAL
    end

.global EventScript_Route11North_FishermanJonah
EventScript_Route11North_FishermanJonah:
    trainerbattle0 0x0 0xDF 0x0 gText_Route11North_FishermanJonah_Intro gText_Route11North_FishermanJonah_Defeat
    msgbox gText_Route11North_FishermanJonah_Chat MSG_NORMAL
    end
