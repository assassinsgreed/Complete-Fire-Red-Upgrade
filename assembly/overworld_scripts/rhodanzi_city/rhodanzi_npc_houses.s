.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_RhodanziNPCHouses_Fisherman
EventScript_RhodanziNPCHouses_Fisherman:
    checkflag 0x240 @ Has Old Rod?
    if SET _goto EventScript_RhodanziNPCHouses_FishermanFarewell
    lock
    faceplayer
    msgbox gText_RhodanziNPCHouses_FishermanIntro MSG_YESNO
    compare LASTRESULT YES
    IF YES _goto EventScript_RhodanziNPCHouses_FishermanYes
    msgbox gText_RhodanziNPCHouses_FishermanNo MSG_NORMAL
    release
    end

EventScript_RhodanziNPCHouses_FishermanYes:
    msgbox gText_RhodanziNPCHouses_FishermanYes MSG_NORMAL
    obtainitem ITEM_OLD_ROD 0x1
    setflag 0x240 @ Has Old Rod?
    msgbox gText_RhodanziNPCHouses_FishermanTip MSG_NORMAL
    goto EventScript_RhodanziNPCHouses_FishermanFarewell

EventScript_RhodanziNPCHouses_FishermanFarewell:
    npcchat gText_RhodanziNPCHouses_FishermanFarewell
    release
    end

.global EventScript_RhodanziNPCHouses_TerrenceSister
EventScript_RhodanziNPCHouses_TerrenceSister:
    npcchat gText_RhodanziNPCHouses_TerrenceSister
    end

.global EventScript_RhodanziNPCHouses_TerrenceLittleBrother
EventScript_RhodanziNPCHouses_TerrenceLittleBrother:
    lock
    faceplayer
    msgbox gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestion MSG_YESNO
    compare LASTRESULT YES
    if YES _goto EventScript_RhodanziNPCHouses_TerrenceLittleBrotherYes
    msgbox gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionNo MSG_NORMAL
    release
    end

EventScript_RhodanziNPCHouses_TerrenceLittleBrotherYes:
    npcchat gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionYes
    end

EventScript_RhodanziNPCHouses_TerrenceLittleBrotherNo:
    npcchat gText_RhodanziNPCHouses_TerrenceLittleBrotherQuestionNo
    end

.global EventScript_RhodanziNPCHouses_Evolution
EventScript_RhodanziNPCHouses_Evolution:
    npcchat2 0x1 m_LookRight gText_RhodanziNPCHouses_Evolution
    end

.global EventScript_RhodanziNPCHouses_OldTrainer
EventScript_RhodanziNPCHouses_OldTrainer:
    npcchat2 0x2 m_LookLeft gText_RhodanziNPCHouses_OldTrainer
    end

.global EventScript_RhodanziNPCHouses_NidoranTrainer
EventScript_RhodanziNPCHouses_NidoranTrainer:
    npcchat gText_RhodanziNPCHouses_NidoranTrainer
    end

.global EventScript_RhodanziNPCHouses_Nidoran
EventScript_RhodanziNPCHouses_Nidoran:
    lock
    faceplayer
    checksound
    cry SPECIES_NIDORAN_M 0x0
    msgbox gText_RhodanziNPCHouses_Nidoran MSG_FACE
    waitcry
    release
    end

.global EventScript_RhodanziNPCHouses_PokedexTrainer
EventScript_RhodanziNPCHouses_PokedexTrainer:
    lock
    faceplayer
    msgbox gText_RhodanziNPCHouses_PokedexTrainerQuestion MSG_YESNO
    compare LASTRESULT YES
    if YES _goto EventScript_RhodanziNPCHouses_PokedexTrainerYes
    goto EventScript_RhodanziNPCHouses_PokedexTrainerNo

EventScript_RhodanziNPCHouses_PokedexTrainerYes:
    npcchat2 0x1 m_LookRight gText_RhodanziNPCHouses_PokedexTrainerYes
    end

EventScript_RhodanziNPCHouses_PokedexTrainerNo:
    npcchat2 0x1 m_LookRight gText_RhodanziNPCHouses_PokedexTrainerNo
    end

.global EventScript_RhodanziNPCHouses_PlantGirl
EventScript_RhodanziNPCHouses_PlantGirl:
    npcchat2 0x1 m_LookLeft gText_RhodanziNPCHouses_PlantGirl
    end

.global EventScript_RhodanziNPCHouses_MailTrainer
EventScript_RhodanziNPCHouses_MailTrainer:
    npcchat2 0x1 m_LookDown gText_RhodanziNPCHouses_MailTrainer
    end
