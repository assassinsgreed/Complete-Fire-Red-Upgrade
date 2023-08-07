.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_RhodanziNPCHouses_Fisherman
EventScript_RhodanziNPCHouses_Fisherman:
    lock
    faceplayer
    checkflag 0x24A @ Has Old Rod?
    if SET _goto EventScript_RhodanziNPCHouses_FishermanFarewell
    msgbox gText_RhodanziNPCHouses_FishermanIntro MSG_YESNO
    compare LASTRESULT YES
    IF TRUE _goto EventScript_RhodanziNPCHouses_FishermanYes
    msgbox gText_RhodanziNPCHouses_FishermanNo MSG_NORMAL
    release
    end

EventScript_RhodanziNPCHouses_FishermanYes:
    msgbox gText_RhodanziNPCHouses_FishermanYes MSG_NORMAL
    obtainitem ITEM_OLD_ROD 0x1
    setflag 0x24A @ Has Old Rod?
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
    if TRUE _goto EventScript_RhodanziNPCHouses_TerrenceLittleBrotherYes
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
    npcchatwithmovement gText_RhodanziNPCHouses_Evolution m_LookRight
    end

.global EventScript_RhodanziNPCHouses_OldTrainer
EventScript_RhodanziNPCHouses_OldTrainer:
    npcchatwithmovement gText_RhodanziNPCHouses_OldTrainer m_LookLeft
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
    if TRUE _goto EventScript_RhodanziNPCHouses_PokedexTrainerYes
    goto EventScript_RhodanziNPCHouses_PokedexTrainerNo

EventScript_RhodanziNPCHouses_PokedexTrainerYes:
    npcchatwithmovement gText_RhodanziNPCHouses_PokedexTrainerYes m_LookRight
    end

EventScript_RhodanziNPCHouses_PokedexTrainerNo:
    npcchatwithmovement gText_RhodanziNPCHouses_PokedexTrainerNo m_LookRight
    end

.global EventScript_RhodanziNPCHouses_PlantGirl
EventScript_RhodanziNPCHouses_PlantGirl:
    npcchatwithmovement gText_RhodanziNPCHouses_PlantGirl m_LookLeft
    end

.global EventScript_RhodanziNPCHouses_MailTrainer
EventScript_RhodanziNPCHouses_MailTrainer:
    npcchatwithmovement gText_RhodanziNPCHouses_MailTrainer m_LookDown
    end
