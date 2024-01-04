.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_Route12West
MapScript_Route12West:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route12West_SetWeather
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route12West_SetWeather:
    random 0xA @ Between 0 and 10
    compare LASTRESULT 0x4 @ 50%
    if lessorequal _call SetWeatherSnowstorm
    compare LASTRESULT 0x9 @ 10%
    if greaterorequal _call SetWeatherClear
    @ Otherwise, leave as default weather (steady snowfall)
    end

.global EventScript_Route12West_TM13IceBeam
EventScript_Route12West_TM13IceBeam:
    setvar CHOSEN_ITEM ITEM_TM13
    call ItemScript_Common_FindTM
    end

.global EventScript_Route12West_Slowbronite
EventScript_Route12West_Slowbronite:
    finditem ITEM_SLOWBRONITE 0x1
    end

.global EventScript_Route12West_BugCatcherBrendan
EventScript_Route12West_BugCatcherBrendan:
    trainerbattle0 0x0 259 0x0 gText_Route12West_BugCatcherBrendan_Intro gText_Route12West_BugCatcherBrendan_Defeat
    msgbox gText_Route12West_BugCatcherBrendan_Chat MSG_NORMAL
    end

.global EventScript_Route12West_SkierChantal
EventScript_Route12West_SkierChantal:
    trainerbattle0 0x0 260 0x0 gText_Route12West_SkierChantal_Intro gText_Route12West_SkierChantal_Defeat
    msgbox gText_Route12West_SkierChantal_Chat MSG_NORMAL
    end

.global EventScript_Route12West_HikerKumar
EventScript_Route12West_HikerKumar:
    trainerbattle0 0x0 261 0x0 gText_Route12West_HikerKumar_Intro gText_Route12West_HikerKumar_Defeat
    msgbox gText_Route12West_HikerKumar_Chat MSG_NORMAL
    end

.global EventScript_Route12West_SkierAubrey
EventScript_Route12West_SkierAubrey:
    trainerbattle0 0x0 262 0x0 gText_Route12West_SkierAubrey_Intro gText_Route12West_SkierAubrey_Defeat
    msgbox gText_Route12West_SkierAubrey_Chat MSG_NORMAL
    end

.global EventScript_Route12West_SkierLenora
EventScript_Route12West_SkierLenora:
    trainerbattle0 0x0 263 0x0 gText_Route12West_SkierLenora_Intro gText_Route12West_SkierLenora_Defeat
    msgbox gText_Route12West_SkierLenora_Chat MSG_NORMAL
    end

.global EventScript_Route12West_SkierMegan
EventScript_Route12West_SkierMegan:
    trainerbattle0 0x0 264 0x0 gText_Route12West_SkierMegan_Intro gText_Route12West_SkierMegan_Defeat
    msgbox gText_Route12West_SkierMegan_Chat MSG_NORMAL
    end

.global EventScript_Route12West_SwimmerGreg
EventScript_Route12West_SwimmerGreg:
    trainerbattle0 0x0 265 0x0 gText_Route12West_SwimmerGreg_Intro gText_Route12West_SwimmerGreg_Defeat
    msgbox gText_Route12West_SwimmerGreg_Chat MSG_NORMAL
    end

.global SignScript_Route12West_TrainerTips
SignScript_Route12West_TrainerTips:
    msgbox gText_Route12West_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route12West_Navigation
SignScript_Route12West_Navigation:
    msgbox gText_Route12West_NavigationSign MSG_SIGN
    end
