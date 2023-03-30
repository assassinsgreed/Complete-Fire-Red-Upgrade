.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_FerroxNPCHouses_SmallestVillage
EventScript_FerroxNPCHouses_SmallestVillage:
    npcchat2 0x1 m_LookRight gText_FerroxNPCHouses_SmallestVillage
    end
