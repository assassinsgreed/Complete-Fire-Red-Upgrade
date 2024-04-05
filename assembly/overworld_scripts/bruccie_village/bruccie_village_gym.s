.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_BruccieVillageGym_GymExpert
EventScript_BruccieVillageGym_GymExpert:
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto EventScript_BruccieVillageGym_GymExpertBadgeObtained
    npcchat gText_BruccieVillageGym_ExpertTips
    end

EventScript_BruccieVillageGym_GymExpertBadgeObtained:
    npcchat gText_BruccieVillageGym_ExpertBadgeObtained
    end

.global EventScript_BruccieVillageGym_Mel
EventScript_BruccieVillageGym_Mel:
    trainerbattle0 0x0 274 0x0 gText_BruccieVillageGym_LassMel_Intro gText_BruccieVillageGym_LassMel_Defeat
    msgbox gText_BruccieVillageGym_LassMel_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Owen
EventScript_BruccieVillageGym_Owen:
    trainerbattle0 0x0 275 0x0 gText_BruccieVillageGym_BirdKeeperOwen_Intro gText_BruccieVillageGym_BirdKeeperOwen_Defeat
    msgbox gText_BruccieVillageGym_BirdKeeperOwen_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Tommy
EventScript_BruccieVillageGym_Tommy:
    trainerbattle0 0x0 276 0x0 gText_BruccieVillageGym_EngineerTommy_Intro gText_BruccieVillageGym_EngineerTommy_Defeat
    msgbox gText_BruccieVillageGym_EngineerTommy_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Joel
EventScript_BruccieVillageGym_Joel:
    trainerbattle0 0x0 277 0x0 gText_BruccieVillageGym_HikerJoel_Intro gText_BruccieVillageGym_HikerJoel_Defeat
    msgbox gText_BruccieVillageGym_HikerJoel_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Ellie
EventScript_BruccieVillageGym_Ellie:
    trainerbattle0 0x0 278 0x0 gText_BruccieVillageGym_CrushGirlEllie_Intro gText_BruccieVillageGym_CrushGirlEllie_Defeat
    msgbox gText_BruccieVillageGym_CrushGirlEllie_Chat MSG_NORMAL
    end

.global EventScript_BruccieVillageGym_Abby
EventScript_BruccieVillageGym_Abby:
    faceplayer
    checkflag 0x825 @ BruccieVillage gym badge
    if SET _goto EventScript_BruccieVillageGym_LeaderAbby_Chat
    msgbox gText_BruccieVillageGym_LeaderAbby_Talk MSG_NORMAL
    call SetupMugshotGymLeaderAndBosses
    trainerbattle1 0x1 279 0x100 gText_BruccieVillageGym_LeaderAbby_Intro gText_BruccieVillageGym_LeaderAbby_Defeat EventScript_BruccieVillageGym_LeaderAbby_Defeated
    end

EventScript_BruccieVillageGym_LeaderAbby_Defeated:
    msgbox gText_BruccieVillageGym_LeaderAbby_BadgeAwarded MSG_NORMAL
    setflag 0x825 @ Bruccie Village gym badge
    fanfare 0x13D @ Gym victory
    msgbox gText_BruccieVillageGym_BadgeReceived MSG_NORMAL
    call BadgeObedienceMessage
    waitfanfare
    msgbox gText_BruccieVillageGym_LeaderAbby_BadgeDescription MSG_NORMAL
    msgbox gText_BruccieVillageGym_LeaderAbby_TMReceived MSG_NORMAL
    loadpointer 0x0 gText_BruccieVillageGym_TMReceived
    additem ITEM_TM76 0x1
    giveitemwithfanfare ITEM_TM76 0x1 0x101 @ MUS_FANFA1
    setflag 0x29A @ Received TM 76 from Abby
    setflag 0x4B5 @ Defeated Abby
    setflag 0x25C @ New Pokemart Stock
    msgbox gText_BruccieVillageGym_LeaderAbby_Chat MSG_KEEPOPEN
    releaseall
    end

EventScript_BruccieVillageGym_LeaderAbby_Chat:
    npcchat gText_BruccieVillageGym_LeaderAbby_Chat
    end

.global SignScript_BruccieVillageGym_Placard
SignScript_BruccieVillageGym_Placard:
    checkflag 0x25B
    if SET _goto SignScript_BruccieVillageGym_PlacardWithBadgeAfterSurfing
    checkflag 0x825 @ Bruccie gym badge
    if SET _goto SignScript_BruccieVillageGym_PlacardWithBadge
    msgbox gText_BruccieVillageGym_Winners MSG_SIGN
    end

SignScript_BruccieVillageGym_PlacardWithBadgeAfterSurfing:
    msgbox gText_BruccieVillageGym_WinnersWithBadgeAfterSurfing MSG_SIGN
    end

SignScript_BruccieVillageGym_PlacardWithBadge:
    msgbox gText_BruccieVillageGym_WinnersWithBadge MSG_SIGN
    end
