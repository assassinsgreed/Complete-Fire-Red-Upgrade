.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_HeleoRanchExterior
MapScript_HeleoRanchExterior:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_HeleoRanch_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMareepVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_FlightFlag:
    setworldmapflag 0x8A7 @ Been to Heleo Ranch
    end

MapEntryScript_HeleoRanch_HandleMareepVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto End
    setflag 0xE07 @ Evenining or night, hide all mareeps on field and Moomoo Milk seller, by setting daily flag
    end

.global MapScript_HeleoRanchInterior
MapScript_HeleoRanchInterior:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_HeleoRanch_HandleMomVisibility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_HeleoRanch_HandleMomVisibility:
    @ Check time of day
    setvar 0x8000 0x0 @ Return distinct times of day
    special2 LASTRESULT 0xAD
    compare LASTRESULT 0x2 @ Evening
    if lessthan _goto HideMom
    clearflag 0xE08 
    end

HideMom:
    setflag 0xE08 @ Hide mom in house during morning and day
    end

.global EvenScript_HeleoRanch_Mareep
EvenScript_HeleoRanch_Mareep:
    lock
    faceplayer
    checksound
    cry SPECIES_MAREEP 0x0
    msgbox gText_HeleoRanch_Mareep MSG_NORMAL
    release
    end

.global EvenScript_HeleoRanch_MoomooMilkSeller
EvenScript_HeleoRanch_MoomooMilkSeller:
    lock
    faceplayer
    msgbox gText_HeleoRanch_MoomooMilkSeller_PurchaseRequest MSG_KEEPOPEN
    showmoney 0x0 0x0
    multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseOne 0
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseADozen 1
	multichoiceoption gText_HeleoRanch_MoomooMilkSeller_PuchaseNone 2
	multichoice 0x60 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	copyvar MULTICHOICE_SELECTION LASTRESULT
	switch LASTRESULT
	case 0, BuyOneMoomooMilk
	case 1, BuyADozenMoomooMilk
	case 2, BuyNoMoomooMilk
    goto BuyNoMoomooMilk

BuyOneMoomooMilk:
    checkmoney 0x1F4 @ Has 500 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1F4
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0x1
    goto EndMoomooMilkSeller

BuyADozenMoomooMilk:
    checkmoney 0x1770 @ Has 6,000 pokedollars
    compare LASTRESULT TRUE
    IF FALSE _goto NotEnoughCash
    removemoney 0x1770
    call PurchaseMoomooMilk
    additem ITEM_MOOMOO_MILK 0xC
    goto EndMoomooMilkSeller

BuyNoMoomooMilk:
    msgbox gText_HeleoRanch_MoomooMilkSeller_ChoseNotToBuy MSG_NORMAL
    goto EndMoomooMilkSeller

PurchaseMoomooMilk:
    updatemoney
    playse 0xF8 @ Money SE
    msgbox gText_HeleoRanch_MoomooMilkSeller_PuchaseComplete MSG_NORMAL
    return

NotEnoughCash:
    msgbox gText_HeleoRanch_MoomooMilkSeller_NotEnoughCash MSG_NORMAL
    goto EndMoomooMilkSeller

EndMoomooMilkSeller:
    hidemoney
    release
    end

.global EvenScript_HeleoRanch_Ampharos
EvenScript_HeleoRanch_Ampharos:
    lock
    faceplayer
    checksound
    cry SPECIES_AMPHAROS 0x0
    msgbox gText_HeleoRanch_AgitatedAmpharos_Sound MSG_NORMAL
    msgbox gText_HeleoRanch_AgitatedAmpharos_Prompt MSG_YESNO
    compare LASTRESULT NO
    if equal _goto AmpharosLeftAlone
    setflag 0x903 @ Disable running
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleStarted MSG_NORMAL
    wildbattle SPECIES_AMPHAROS 0x1E ITEM_SITRUS_BERRY
    setflag 0x03E @ Hide Ampharos
    hidesprite LASTTALKED
    msgbox gText_HeleoRanch_AgitatedAmpharos_BattleEnded MSG_NORMAL
    clearflag 0x903 @ Enable running
    release
    end

AmpharosLeftAlone:
    msgbox gText_HeleoRanch_AgitatedAmpharos_LeftAlone MSG_NORMAL
    applymovement 0xA m_LookDown
    end

.global EvenScript_HeleoRanch_BurglarCole
EvenScript_HeleoRanch_BurglarCole:
    trainerbattle0 0x0 0x49 0x0 gText_HeleoRanch_BurglarCole_Intro gText_HeleoRanch_BurglarCole_Defeat
    msgbox gText_HeleoRanch_BurglarCole_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_CamperTroy
EvenScript_HeleoRanch_CamperTroy:
    trainerbattle0 0x0 0x4A 0x0 gText_HeleoRanch_CamperTroy_Intro gText_HeleoRanch_CamperTroy_Defeat
    msgbox gText_HeleoRanch_CamperTroy_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_BreederLaura
EvenScript_HeleoRanch_BreederLaura:
    trainerbattle0 0x0 0x4B 0x0 gText_HeleoRanch_BreederLaura_Intro gText_HeleoRanch_BreederLaura_Defeat
    msgbox gText_HeleoRanch_BreederLaura_Chat MSG_NORMAL
    end

.global EvenScript_HeleoRanch_PicknickerCasey
EvenScript_HeleoRanch_PicknickerCasey:
    trainerbattle0 0x0 0x4C 0x0 gText_HeleoRanch_PicknickerCasey_Intro gText_HeleoRanch_PicknickerCasey_Defeat
    msgbox gText_HeleoRanch_PicknickerCasey_Chat MSG_NORMAL
    end

.global EventScript_HeleoRanch_FindTM45Attract
EventScript_HeleoRanch_FindTM45Attract:
    setvar CHOSEN_ITEM ITEM_TM45
    call ItemScript_Common_FindTM
    end

.global EventScript_HeleoRanch_Ampharosite
EventScript_HeleoRanch_Ampharosite:
    finditem ITEM_AMPHAROSITE 0x1
    end

.global SignScript_HeleoRanch_RanchGlade
SignScript_HeleoRanch_RanchGlade:
    msgbox gText_HeleoRanch_GladeSign MSG_SIGN
    end

.global SignScript_HeleoRanch_RanchEntrance
SignScript_HeleoRanch_RanchEntrance:
    msgbox gText_HeleoRanch_EntranceSign MSG_SIGN
    end

.global EventScript_HeleoRanch_Dad
EventScript_HeleoRanch_Dad:
    npcchat gText_HeleoRanch_Dad
    end

.global EventScript_HeleoRanch_Daughter
EventScript_HeleoRanch_Daughter:
    npcchat2 0x2 m_LookUp gText_HeleoRanch_Daughter
    end

.global EventScript_HeleoRanch_Mom
EventScript_HeleoRanch_Mom:
    npcchat gText_HeleoRanch_Mom
    end

.global EventScript_HeleoRanch_Son
EventScript_HeleoRanch_Son:
    npcchat gText_HeleoRanch_Son
    end
