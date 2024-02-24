.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

## B1F
.global EventScript_PlutoHQ_B1F_TM59BrutalSwing
EventScript_PlutoHQ_B1F_TM59BrutalSwing:
    setvar CHOSEN_ITEM ITEM_TM59
    call ItemScript_Common_FindTM
    end

.global EventScript_PlutoHQ_B1F_TeamPlutoHeathcliff
EventScript_PlutoHQ_B1F_TeamPlutoHeathcliff:
    trainerbattle0 0x0 291 0x0 gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Intro gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Defeat
    msgbox gText_PlutoHQ_B1F_TeamPlutoHeathcliff_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B1F_ScientistSeamus
EventScript_PlutoHQ_B1F_ScientistSeamus:
    trainerbattle0 0x0 292 0x0 gText_PlutoHQ_B1F_ScientistSeamus_Intro gText_PlutoHQ_B1F_ScientistSeamus_Defeat
    msgbox gText_PlutoHQ_B1F_ScientistSeamus_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B1F_TeamPlutoColton
EventScript_PlutoHQ_B1F_TeamPlutoColton:
    trainerbattle0 0x0 293 0x0 gText_PlutoHQ_B1F_TeamPlutoColton_Intro gText_PlutoHQ_B1F_TeamPlutoColton_Defeat
    msgbox gText_PlutoHQ_B1F_TeamPlutoColton_Chat MSG_NORMAL
    end

## B1F Hall
.global TileScript_PlutoHQ_B1F_Hall_KurtisWarning
TileScript_PlutoHQ_B1F_Hall_KurtisWarning:
    lock
    msgbox gText_PlutoHQ_B1F_Hall_KurtissWarning MSG_NORMAL
    setvar 0x409C 0x1
    release
    end

## B2F
.global EventScript_PlutoHQ_B2F_ScientistWayne
EventScript_PlutoHQ_B2F_ScientistWayne:
    trainerbattle0 0x0 294 0x0 gText_PlutoHQ_B2F_ScientistWayne_Intro gText_PlutoHQ_B2F_ScientistWayne_Defeat
    msgbox gText_PlutoHQ_B2F_ScientistWayne_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B2F_TeamPlutoDenise
EventScript_PlutoHQ_B2F_TeamPlutoDenise:
    trainerbattle0 0x0 295 0x0 gText_PlutoHQ_B2F_TeamPlutoDenise_Intro gText_PlutoHQ_B2F_TeamPlutoDenise_Defeat
    msgbox gText_PlutoHQ_B2F_TeamPlutoDenise_Chat MSG_NORMAL
    end
    
.global EventScript_PlutoHQ_B2F_TeamPlutoTheodore
EventScript_PlutoHQ_B2F_TeamPlutoTheodore:
    trainerbattle0 0x0 296 0x0 gText_PlutoHQ_B2F_TeamPlutoTheodore_Intro gText_PlutoHQ_B2F_TeamPlutoTheodore_Defeat
    msgbox gText_PlutoHQ_B2F_TeamPlutoTheodore_Chat MSG_NORMAL
    end

## B3F
.global EventScript_PlutoHQ_B3F_RestGrunt
EventScript_PlutoHQ_B3F_RestGrunt:
    faceplayer
    msgbox gText_PlutoHQ_B2F_RestGrunt_Intro MSG_NORMAL
    showmoney 0x0 0x0
    msgbox gText_PlutoHQ_B2F_RestGrunt_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto ChoseNotToHeal
    checkmoney 500
    compare LASTRESULT FALSE
    if equal _goto NotEnoughMoney
    removemoney 500
    updatemoney 0x0 0x0
    sound 0xF8 @ Money SE
    waitse
    msgbox gText_PlutoHQ_B2F_RestGrunt_PaymentReceived MSG_NORMAL
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_ChoseYes MSG_NORMAL
    call PlayerHeal
    msgbox gText_PlutoHQ_B2F_RestGrunt_AfterHeal MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

NotEnoughMoney:
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_NotEnoughMoney MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

ChoseNotToHeal:
    hidemoney
    msgbox gText_PlutoHQ_B2F_RestGrunt_ChoseNo MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

.global EventScript_PlutoHQ_B3F_TeamPlutoYeon
EventScript_PlutoHQ_B3F_TeamPlutoYeon:
    trainerbattle0 0x0 297 0x0 gText_PlutoHQ_B3F_TeamPlutoYeon_Intro gText_PlutoHQ_B3F_TeamPlutoYeon_Defeat
    msgbox gText_PlutoHQ_B3F_TeamPlutoYeon_Chat MSG_NORMAL
    end

## B4F
.global EventScript_PlutoHQ_B4F_CypressKey
EventScript_PlutoHQ_B4F_CypressKey:
    finditem ITEM_CYPRESS_KEY 0x1
    end

.global EventScript_PlutoHQ_B4F_CoffeBreakFemaleGrunt
EventScript_PlutoHQ_B4F_CoffeBreakFemaleGrunt:
    npcchatwithmovement gText_PlutoHQ_B3F_CoffeeBreakFemaleGrunt m_LookLeft
    end

.global EventScript_PlutoHQ_B4F_CoffeeBreakMaleGrunt    
EventScript_PlutoHQ_B4F_CoffeeBreakMaleGrunt:
    npcchatwithmovement gText_PlutoHQ_B3F_CoffeeBreakMaleGrunt m_LookRight
    end

.global EventScript_PlutoHQ_B4F_TeamPlutoMatty
EventScript_PlutoHQ_B4F_TeamPlutoMatty:
    trainerbattle0 0x0 298 0x0 gText_PlutoHQ_B4F_TeamPlutoMatty_Intro gText_PlutoHQ_B4F_TeamPlutoMatty_Defeat
    msgbox gText_PlutoHQ_B4F_TeamPlutoMatty_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B4F_ScientistGary
EventScript_PlutoHQ_B4F_ScientistGary:
    trainerbattle0 0x0 299 0x0 gText_PlutoHQ_B4F_ScientistGary_Intro gText_PlutoHQ_B4F_ScientistGary_Defeat
    msgbox gText_PlutoHQ_B4F_ScientistGary_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B4F_TeamPlutoMay
EventScript_PlutoHQ_B4F_TeamPlutoMay:
    trainerbattle0 0x0 300 0x0 gText_PlutoHQ_B4F_TeamPlutoMay_Intro gText_PlutoHQ_B4F_TeamPlutoMay_Defeat
    msgbox gText_PlutoHQ_B4F_TeamPlutoMay_Chat MSG_NORMAL
    end

## B5F
.global EventScript_PlutoHQ_B5F_OwlKey
EventScript_PlutoHQ_B5F_OwlKey:
    finditem ITEM_OWL_KEY 0x1
    end

.global EventScript_PlutoHQ_B5F_TM100Confide
EventScript_PlutoHQ_B5F_TM100Confide:
    setvar CHOSEN_ITEM ITEM_TM100
    call ItemScript_Common_FindTM
    end

.global EventScript_PlutoHQ_B5F_TeamPlutoClay
EventScript_PlutoHQ_B5F_TeamPlutoClay:
    trainerbattle0 0x0 301 0x0 gText_PlutoHQ_B5F_TeamPlutoClay_Intro gText_PlutoHQ_B5F_TeamPlutoClay_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoClay_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B5F_TeamPlutoVictor
EventScript_PlutoHQ_B5F_TeamPlutoVictor:
    trainerbattle0 0x0 302 0x0 gText_PlutoHQ_B5F_TeamPlutoVictor_Intro gText_PlutoHQ_B5F_TeamPlutoVictor_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoVictor_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B5F_TeamPluto_Paula
EventScript_PlutoHQ_B5F_TeamPluto_Paula:
    trainerbattle0 0x0 303 0x0 gText_PlutoHQ_B5F_TeamPlutoPaula_Intro gText_PlutoHQ_B5F_TeamPlutoPaula_Defeat
    msgbox gText_PlutoHQ_B5F_TeamPlutoPaula_Chat MSG_NORMAL
    end

## B6F
.global EventScript_PlutoHQ_B6F_TeamPlutoGiana
EventScript_PlutoHQ_B6F_TeamPlutoGiana:
    trainerbattle0 0x0 304 0x0 gText_PlutoHQ_B6F_TeamPlutoGiana_Intro gText_PlutoHQ_B6F_TeamPlutoGiana_Defeat
    msgbox gText_PlutoHQ_B6F_TeamPlutoGiana_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B6F_ScientistOrson
EventScript_PlutoHQ_B6F_ScientistOrson:
    trainerbattle0 0x0 305 0x0 gText_PlutoHQ_B6F_ScientistOrson_Intro gText_PlutoHQ_B6F_ScientistOrson_Defeat
    msgbox gText_PlutoHQ_B6F_ScientistOrson_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B6F_TeamPlutoQuinn
EventScript_PlutoHQ_B6F_TeamPlutoQuinn:
    trainerbattle0 0x0 306 0x0 gText_PlutoHQ_B6F_TeamPlutoQuinn_Intro gText_PlutoHQ_B6F_TeamPlutoQuinn_Defeat
    msgbox gText_PlutoHQ_B6F_TeamPlutoQuinn_Chat MSG_NORMAL
    end

## B7F
.global EventScript_PlutoHQ_B7F_TeamPlutoLayla
EventScript_PlutoHQ_B7F_TeamPlutoLayla:
    trainerbattle0 0x0 307 0x0 gText_PlutoHQ_B7F_TeamPlutoLayla_Intro gText_PlutoHQ_B7F_TeamPlutoLayla_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoLayla_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_ScientistNico
EventScript_PlutoHQ_B7F_ScientistNico:
    trainerbattle0 0x0 308 0x0 gText_PlutoHQ_B7F_ScientistNico_Intro gText_PlutoHQ_B7F_ScientistNico_Defeat
    msgbox gText_PlutoHQ_B7F_ScientistNico_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_TeamPlutoMitch
EventScript_PlutoHQ_B7F_TeamPlutoMitch:
    trainerbattle0 0x0 309 0x0 gText_PlutoHQ_B7F_TeamPlutoMitch_Intro gText_PlutoHQ_B7F_TeamPlutoMitch_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoMitch_Chat MSG_NORMAL
    end

.global EventScript_PlutoHQ_B7F_TeamPlutoRichard
EventScript_PlutoHQ_B7F_TeamPlutoRichard:
    trainerbattle0 0x0 310 0x0 gText_PlutoHQ_B7F_TeamPlutoRichard_Intro gText_PlutoHQ_B7F_TeamPlutoRichard_Defeat
    msgbox gText_PlutoHQ_B7F_TeamPlutoRichard_Chat MSG_NORMAL
    end

## Irene's office
## Ronald's office
## Kurtis's Office
.global EventScript_PlutoHQ_B1F_Gyaradosite
EventScript_PlutoHQ_B1F_Gyaradosite:
    obtainitem ITEM_GYARADOSITE 0x1
    end
