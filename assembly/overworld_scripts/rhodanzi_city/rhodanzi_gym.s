.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global SignScript_RhodanziGym_Placard
SignScript_RhodanziGym_Placard:
    lockall
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto SignScript_RhodanziGym_PlacardWithBadge
    checkflag 0x232 @ DexNav event triggered
    if SET _goto SignScript_RhodanziGym_PlacardWithBadgeAndDexNavEvent
    msgbox gText_RhodanziGym_Winners MSG_SIGN
    releaseall
    end

SignScript_RhodanziGym_PlacardWithBadge:
    msgbox gText_RhodanziGym_WinnersWithBadge MSG_SIGN
    releaseall
    end

SignScript_RhodanziGym_PlacardWithBadgeAndDexNavEvent:
    msgbox gText_RhodanziGym_WinnersWithBadgeAndDexNavEvent MSG_SIGN
    releaseall
    end

.global EventScript_RhodanziGym_GymExpert
EventScript_RhodanziGym_GymExpert:
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto EventScript_RhodanziGym_GymExpertBadgeObtained
    npcchat gText_RhodanziGym_ExpertTips
    end

EventScript_RhodanziGym_GymExpertBadgeObtained:
    npcchat gText_RhodanziGym_ExpertBadgeObtained
    end

.global EventScript_RhodanziGym_Alonso
EventScript_RhodanziGym_Alonso:
    trainerbattle0 0x0 0xC 0x0 gText_RhodanziGym_Alonso_Intro gText_RhodanziGym_Alonso_Defeat
    msgbox gText_RhodanziGym_Alonso_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Brandon
EventScript_RhodanziGym_Brandon:
    trainerbattle0 0x0 0xD 0x0 gText_RhodanziGym_Brandon_Intro gText_RhodanziGym_Brandon_Defeat
    msgbox gText_RhodanziGym_Brandon_Chat MSG_NORMAL
    end

.global EventScript_RhodanziGym_Leader_Terrence
EventScript_RhodanziGym_Leader_Terrence:
    lockall
    faceplayer
    checkflag 0x820 @ Rhodanzi gym badge
    if SET _goto EventScript_RhodanziGym_Leader_TerrenceChat
    msgbox gText_RhodanziGym_Leader_Terrence_Talk MSG_NORMAL
    setvar 0x503A 0x1
    setvar 0x503B 0x1
    trainerbattle1 0x1 0xE 0x100 gText_RhodanziGym_Leader_Terrence_Intro gText_RhodanziGym_Leader_Terrence_Defeat EventScript_RhodanziGym_Leader_TerrenceDefeated
    end

EventScript_RhodanziGym_Leader_TerrenceDefeated:
    msgbox gText_RhodanziGym_Leader_Terrence_BadgeAwarded MSG_NORMAL
    fanfare 0x13D @ Gym victory
    msgbox gText_RhodanziGym_BadgeReceived MSG_KEEPOPEN
    waitfanfare
    setflag 0x820 @ Rhodanzi gym badge
    settrainerflag 0xC @ Alonso cannot be battled now
    settrainerflag 0xD @ Brandon cannot be battled now
    msgbox gText_RhodanziGym_Leader_Terrence_BadgeDescription MSG_NORMAL
    msgbox gText_RhodanziGym_Leader_Terrence_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_RhodanziGym_BadgeReceived
    additem ITEM_TM05 0x1
    giveitemwithfanfare ITEM_TM05 0x1 0x101 @ MUS_FANFA1
    setflag 0x254 @ Received TM 05 from Terrence
    setflag 0x4B0 @ Defeated Terrence
    msgbox gText_RhodanziGym_Leader_Terrence_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_RhodanziGym_Leader_TerrenceChat:
    npcchat gText_RhodanziGym_Leader_Terrence_Chat
    end
