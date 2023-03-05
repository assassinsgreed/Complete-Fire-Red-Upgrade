.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Route4_Foreman
EventScript_Route4_Foreman:
    npcchat2 0x1 m_LookUp gText_Route4_ForemanChat
    end

.global EventScript_Route4_Worker
EventScript_Route4_Worker:
    npcchat2 0x2 m_LookUp gText_Route4_WorkerChat
    end

.global EventScript_Route4_LargeMan
EventScript_Route4_LargeMan:
    npcchat gText_Route4_LargeManChat
    end

.global EventScript_Route4_Lass
EventScript_Route4_Lass:
    npcchat gText_Route4_LassChat
    end

.global SignScript_Route4_TormaCaveSign
SignScript_Route4_TormaCaveSign:
    msgbox gText_Route4_TormaCaveSign MSG_NORMAL
    end

.global SignScript_Route4_TrainerTips
SignScript_Route4_TrainerTips:
    msgbox gText_Route4_TormaCaveSign MSG_NORMAL
    end
