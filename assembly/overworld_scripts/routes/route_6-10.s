.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

@ Route 6
.global EventScript_Route6_DirectionsGirl
EventScript_Route6_DirectionsGirl:
    npcchat gText_Route6_DirectionsGirl
    end

.global EventScript_Route6_YoungsterNed
EventScript_Route6_YoungsterNed:
    trainerbattle0 0x0 0x52 0x0 gText_Route6_YoungsterNed_Intro gText_Route6_YoungsterNed_Defeat
    msgbox gText_Route6_YoungsterNed_Chat MSG_NORMAL
    end

.global EventScript_Route6_NinjaBoyRajan
EventScript_Route6_NinjaBoyRajan:
    trainerbattle0 0x0 0x53 0x0 gText_Route6_NinjaBoyRajan_Intro gText_Route6_NinjaBoyRajan_Defeat
    msgbox gText_Route6_NinjaBoyRajan_Chat MSG_NORMAL
    end

.global EventScript_Route6_HikerRomero
EventScript_Route6_HikerRomero:
    trainerbattle0 0x0 0x54 0x0 gText_Route6_HikerRomero_Intro gText_Route6_HikerRomero_Defeat
    msgbox gText_Route6_HikerRomero_Chat MSG_NORMAL
    end

.global EventScript_Route6_SuperNerdEstevan
EventScript_Route6_SuperNerdEstevan:
    trainerbattle0 0x0 0x55 0x0 gText_Route6_SuperNerdEstevan_Intro gText_Route6_SuperNerdEstevan_Defeat
    msgbox gText_Route6_SuperNerdEstevan_Chat MSG_NORMAL
    end

.global EventScript_Route6_EngineerHarry
EventScript_Route6_EngineerHarry:
    trainerbattle0 0x0 0x56 0x0 gText_Route6_EngineerHarry_Intro gText_Route6_EngineerHarry_Defeat
    msgbox gText_Route6_EngineerHarry_Chat MSG_NORMAL
    end

.global EventScript_Route6_GamblerMick
EventScript_Route6_GamblerMick:
    trainerbattle0 0x0 0x57 0x0 gText_Route6_GamblerMick_Intro gText_Route6_GamblerMick_Defeat
    msgbox gText_Route6_GamblerMick_Chat MSG_NORMAL
    end

.global EventScript_Route6_FishermanTaylor
EventScript_Route6_FishermanTaylor:
    trainerbattle0 0x0 0x58 0x0 gText_Route6_FishermanTaylor_Intro gText_Route6_FishermanTaylor_Defeat
    msgbox gText_Route6_FishermanTaylor_Chat MSG_NORMAL
    end

.global EventScript_Route6_NurseLeanne
EventScript_Route6_NurseLeanne:
    faceplayer
    checktrainerflag 0x559
    if SET _goto NurseLeanneHeal
    trainerbattle2 0x0 0x59 0x0 gText_Route6_NurseLeanne_Intro gText_Route6_NurseLeanne_Defeat NurseLeanneHeal
    call NurseLeanneHeal
    end

NurseLeanneHeal:
    msgbox gText_Route6_NurseLeanne_Chat MSG_NORMAL
    call PlayerHealNurse
    msgbox gText_Route6_NurseLeanne_HealingComplete MSG_NORMAL
    end

.global EventScript_Route6_SuperNerdDante
EventScript_Route6_SuperNerdDante:
    trainerbattle0 0x0 0x5A 0x0 gText_Route6_SuperNerdDante_Intro gText_Route6_SuperNerdDante_Defeat
    msgbox gText_Route6_SuperNerdDante_Chat MSG_NORMAL
    end

.global EventScript_Route6_BugCatcherBillie
EventScript_Route6_BugCatcherBillie:
    trainerbattle0 0x0 0x5B 0x0 gText_Route6_BugCatcherBillie_Intro gText_Route6_BugCatcherBillie_Defeat
    msgbox gText_Route6_BugCatcherBillie_Chat MSG_NORMAL
    end

.global EventScript_Route6_GentlemanLincoln
EventScript_Route6_GentlemanLincoln:
    trainerbattle0 0x0 0x5C 0x0 gText_Route6_GentlemanLincoln_Intro gText_Route6_GentlemanLincoln_Defeat
    msgbox gText_Route6_GentlemanLincoln_Chat MSG_NORMAL
    end

.global EventScript_Route6_BlackbeltRafael
EventScript_Route6_BlackbeltRafael:
    trainerbattle0 0x0 0x5D 0x0 gText_Route6_BlackbeltRafael_Intro gText_Route6_BlackbeltRafael_Defeat
    msgbox gText_Route6_BlackbeltRafael_Chat MSG_NORMAL
    end

.global EventScript_Route6_LassAnna
EventScript_Route6_LassAnna:
    trainerbattle0 0x0 0x5E 0x0 gText_Route6_LassAnna_Intro gText_Route6_LassAnna_Defeat
    msgbox gText_Route6_LassAnna_Chat MSG_NORMAL
    end

.global EventScript_Route6_SwimmerDanika
EventScript_Route6_SwimmerDanika:
    trainerbattle0 0x0 0x5F 0x0 gText_Route6_SwimmerDanika_Intro gText_Route6_SwimmerDanika_Defeat
    msgbox gText_Route6_SwimmerDanika_Chat MSG_NORMAL
    end

.global EventScript_Route6_SrAndJr_Sue
EventScript_Route6_SrAndJr_Sue:
    faceplayer
    trainerbattle0 0x0 0x60 0x0 gText_Route6_SrAndJrSueAndKat_Sue_Intro gText_Route6_SrAndJrSueAndKat_Sue_Defeat
    msgbox gText_Route6_SrAndJrSueAndKat_Sue_Chat MSG_NORMAL
    end

.global EventScript_Route6_SrAndJr_Kat
EventScript_Route6_SrAndJr_Kat:
    faceplayer
    trainerbattle0 0x0 0x60 0x0 gText_Route6_SrAndJrSueAndKat_Kat_Intro gText_Route6_SrAndJrSueAndKat_Kat_Defeat
    msgbox gText_Route6_SrAndJrSueAndKat_Kat_Chat MSG_NORMAL
    end

.global EventScript_Route6_HikerDarryl
EventScript_Route6_HikerDarryl:
    trainerbattle0 0x0 0x61 0x0 gText_Route6_HikerDarryl_Intro gText_Route6_HikerDarryl_Defeat
    msgbox gText_Route6_HikerDarryl_Chat MSG_NORMAL
    end

.global EventScript_Route6_Blastoisinite
EventScript_Route6_Blastoisinite:
    finditem ITEM_BLASTOISINITE 0x1
    end

.global EventScript_Route6_FindTM78Bulldoze
EventScript_Route6_FindTM78Bulldoze:
    setvar CHOSEN_ITEM ITEM_TM78
    call ItemScript_Common_FindTM
    end

.global EventScript_Route6_FindTM88StealthRock
EventScript_Route6_FindTM88StealthRock:
    setvar CHOSEN_ITEM ITEM_TM88
    call ItemScript_Common_FindTM
    end

.global SignScript_Route6_Directions
SignScript_Route6_Directions:
    msgbox gText_Route6_DirectionsSign MSG_SIGN
    end

.global SignScript_Route6_ItemFinder
SignScript_Route6_ItemFinder:
    msgbox gText_Route6_ItemFinderSign MSG_SIGN
    end

.global SignScript_Route6_WrongWay
SignScript_Route6_WrongWay:
    msgbox gText_Route6_WrongWaySign MSG_SIGN
    end

@ Route 7
.global EventScript_Route7_CamperCarlisle
EventScript_Route7_CamperCarlisle:
    trainerbattle0 0x0 0xF 0x0 gText_Route7_CamperCarlisle_Intro gText_Route7_CamperCarlisle_Defeat
    msgbox gText_Route7_CamperCarlisle_Chat MSG_NORMAL
    end

.global EventScript_Route7_RockerJonas
EventScript_Route7_RockerJonas:
    trainerbattle0 0x0 0x4D 0x0 gText_Route7_RockerJonas_Intro gText_Route7_RockerJonas_Defeat
    msgbox gText_Route7_RockerJonas_Chat MSG_NORMAL
    end

.global EventScript_Route7_LassEden
EventScript_Route7_LassEden:
    trainerbattle0 0x0 0x4E 0x0 gText_Route7_LassEden_Intro gText_Route7_LassEden_Defeat
    msgbox gText_Route7_LassEden_Chat MSG_NORMAL
    end

.global EventScript_Route7_HikerDanny
EventScript_Route7_HikerDanny:
    trainerbattle0 0x0 0x4F 0x0 gText_Route7_HikerDanny_Intro gText_Route7_HikerDanny_Defeat
    msgbox gText_Route7_HikerDanny_Chat MSG_NORMAL
    end

.global EventScript_Route7_CrushGirlErin
EventScript_Route7_CrushGirlErin:
    trainerbattle0 0x0 0x50 0x0 gText_Route7_CrushGirlErin_Intro gText_Route7_CrushGirlErin_Defeat
    msgbox gText_Route7_CrushGirlErin_Chat MSG_NORMAL
    end

.global EventScript_Route7_PsychicIshaan
EventScript_Route7_PsychicIshaan:
    trainerbattle0 0x0 0x51 0x0 gText_Route7_PsychicIshaan_Intro gText_Route7_PsychicIshaan_Defeat
    msgbox gText_Route7_PsychicIshaan_Chat MSG_NORMAL
    end

.global EventScript_Route7_FindTM09Venoshock
EventScript_Route7_FindTM09Venoshock:
    setvar CHOSEN_ITEM ITEM_TM09
    call ItemScript_Common_FindTM
    end

.global SignScript_Route7_TrainerTips
SignScript_Route7_TrainerTips:
    msgbox gText_Route7_TrainerTips MSG_SIGN
    end

@ Route 8
.global MapScript_Route8
MapScript_Route8:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_Route8_SetWeather
    mapscript MAP_SCRIPT_ON_RESUME HideTrapPokemon
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_Route8_SetWeather:
    @ Check player position, to see if they spawned from the north gate or fisherman's hut
    getplayerpos 0x4000 0x4001
    compare 0x4001 0x2D @ Above the weather stairs, no need to set weather
    if greaterthan _goto TileScript_Route8_SetWeather
    end

HideTrapPokemon:
    checkflag 0xE0C
    if SET _call HideSandygast1
    checkflag 0xE0D
    if SET _call HideSandygast2
    end

HideSandygast1:
    hidesprite 14
    return

HideSandygast2:
    hidesprite 15
    return

.global TileScript_Route8_ClearWeather
TileScript_Route8_ClearWeather:
    setvar 0x400D 0x0 @ Enable weather setting again
    call SetWeatherClear
    End

.global TileScript_Route8_SetWeather
TileScript_Route8_SetWeather:
    compare 0x400D 0x1
    if equal _goto End
    setvar 0x400D 0x1 @ Prevent future weather until var is cleared
    call SetWeatherFog
    random 0x64 @ Between 0 and 100
    compare LASTRESULT 0xF @ "15"
    if lessorequal _goto SetWeatherMistyAndEnd
    compare LASTRESULT 0x2D @ "45"
    if greaterorequal _goto SetWeatherRainyAndEnd
    goto TileScript_Route8_ClearWeather

SetWeatherMistyAndEnd:
    call SetWeatherFog
    end

SetWeatherRainyAndEnd:
    call SetWeatherRain
    end

.global SignScript_Route8_FishermanCommittee
SignScript_Route8_FishermanCommittee:
    msgbox gText_Route8_FishingCommittee MSG_SIGN
    end

.global SignScript_Route8_TrainerTips_LongGrass
SignScript_Route8_TrainerTips_LongGrass:
    msgbox gText_Route8_LongGrass MSG_SIGN
    end

.global SignScript_Route8_TrainerTips_FoggyWeather
SignScript_Route8_TrainerTips_FoggyWeather:
    msgbox gText_Route8_FoggyWeather MSG_SIGN
    end

.global EventScript_Route8_SandygastEncounter1
EventScript_Route8_SandygastEncounter1:
    setflag 0xE0C
    call SandygastEncounter
    end

.global EventScript_Route8_SandygastEncounter2
EventScript_Route8_SandygastEncounter2:
    setflag 0xE0D
    call SandygastEncounter
    end

SandygastEncounter:
    lock
    checksound
    cry SPECIES_SANDYGAST 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_Route1_SandygastEncounter MSG_KEEPOPEN
    wildbattle SPECIES_SANDYGAST 0x19 0x0 @ Level 25
    release
    return

.global EventScript_Route8_Swampertite
EventScript_Route8_Swampertite:
    finditem ITEM_SWAMPERTITE 0x1
    end

.global EventScript_Route8_FindTM40AerialAce
EventScript_Route8_FindTM40AerialAce:
    setvar CHOSEN_ITEM ITEM_TM40
    call ItemScript_Common_FindTM
    end

.global EventScript_Route8_FindTM48Round
EventScript_Route8_FindTM48Round:
    setvar CHOSEN_ITEM ITEM_TM48
    call ItemScript_Common_FindTM
    end

.global EventScript_Route8_FindTM34SludgeWave
EventScript_Route8_FindTM34SludgeWave:
    setvar CHOSEN_ITEM ITEM_TM34
    call ItemScript_Common_FindTM
    end

.global EventScript_Route8_CamperDrew
EventScript_Route8_CamperDrew:
    trainerbattle0 0x0 0x6A 0x0 gText_Route8_CamperDrew_Intro gText_Route8_CamperDrew_Defeat
    msgbox gText_Route8_CamperDrew_Chat MSG_NORMAL
    end

.global EventScript_Route8_NinjaBoyZeke
EventScript_Route8_NinjaBoyZeke:
    trainerbattle0 0x0 0x6B 0x0 gText_Route8_NinjaBoyZeke_Intro gText_Route8_NinjaBoyZeke_Defeat
    msgbox gText_Route8_NinjaBoyZeke_Chat MSG_NORMAL
    end

.global EventScript_Route8_SuperNerdSaul
EventScript_Route8_SuperNerdSaul:
    trainerbattle0 0x0 0x6C 0x0 gText_Route8_SuperNerdSaul_Intro gText_Route8_SuperNerdSaul_Defeat
    msgbox gText_Route8_SuperNerdSaul_Chat MSG_NORMAL
    end

.global EventScript_Route8_RockerParker
EventScript_Route8_RockerParker:
    trainerbattle0 0x0 0x6D 0x0 gText_Route8_RockerParker_Intro gText_Route8_RockerParker_Defeat
    msgbox gText_Route8_RockerParker_Chat MSG_NORMAL
    end

.global EventScript_Route8_ParasolLadyAnnabelle
EventScript_Route8_ParasolLadyAnnabelle:
    trainerbattle0 0x0 0x6E 0x0 gText_Route8_ParasolLadyAnnabelle_Intro gText_Route8_ParasolLadyAnnabelle_Defeat
    msgbox gText_Route8_ParasolLadyAnnabelle_Chat MSG_NORMAL
    end

.global EventScript_Route8_ChannelerMorgan
EventScript_Route8_ChannelerMorgan:
    trainerbattle0 0x0 0x6F 0x0 gText_Route8_ChannelerMorgan_Intro gText_Route8_ChannelerMorgan_Defeat
    msgbox gText_Route8_ChannelerMorgan_Chat MSG_NORMAL
    end

.global EventScript_Route8_BugCatcherArnold
EventScript_Route8_BugCatcherArnold:
    trainerbattle0 0x0 0x70 0x0 gText_Route8_BugCatcherArnold_Intro gText_Route8_BugCatcherArnold_Defeat
    msgbox gText_Route8_BugCatcherArnold_Chat MSG_NORMAL
    end

.global EventScript_Route8_LassLilian
EventScript_Route8_LassLilian:
    trainerbattle0 0x0 0x71 0x0 gText_Route8_LassLilian_Intro gText_Route8_LassLilian_Defeat
    msgbox gText_Route8_LassLilian_Chat MSG_NORMAL
    end

.global EventScript_Route8_NinjaBoyNatto
EventScript_Route8_NinjaBoyNatto:
    trainerbattle0 0x0 0x72 0x0 gText_Route8_NinjaBoyNatto_Intro gText_Route8_NinjaBoyNatto_Defeat
    msgbox gText_Route8_NinjaBoyNatto_Chat MSG_NORMAL
    end

.global EventScript_Route8_TuberMicah
EventScript_Route8_TuberMicah:
    trainerbattle0 0x0 0x73 0x0 gText_Route8_TuberMicah_Intro gText_Route8_TuberMicah_Defeat
    msgbox gText_Route8_TuberMicah_Chat MSG_NORMAL
    end

.global EventScript_Route8_TuberNancy
EventScript_Route8_TuberNancy:
    trainerbattle0 0x0 0x74 0x0 gText_Route8_TuberNancy_Intro gText_Route8_TuberNancy_Defeat
    msgbox gText_Route8_TuberNancy_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerMaya
EventScript_Route8_SwimmerMaya:
    trainerbattle0 0x0 0x75 0x0 gText_Route8_SwimmerMaya_Intro gText_Route8_SwimmerMaya_Defeat
    msgbox gText_Route8_SwimmerMaya_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerHuey
EventScript_Route8_SwimmerHuey:
    trainerbattle0 0x0 0x76 0x0 gText_Route8_SwimmerHuey_Intro gText_Route8_SwimmerHuey_Defeat
    msgbox gText_Route8_SwimmerHuey_Chat MSG_NORMAL
    end

.global EventScript_Route8_SwimmerBob
EventScript_Route8_SwimmerBob:
    trainerbattle0 0x0 0x77 0x0 gText_Route8_SwimmerBob_Intro gText_Route8_SwimmerBob_Defeat
    msgbox gText_Route8_SwimmerBob_Chat MSG_NORMAL
    end

.global EventScript_Route8_CoolTrainerHarriet
EventScript_Route8_CoolTrainerHarriet:
    trainerbattle0 0x0 0x78 0x0 gText_Route8_CoolTrainerHarriet_Intro gText_Route8_CoolTrainerHarriet_Defeat
    msgbox gText_Route8_CoolTrainerHarriet_Chat MSG_NORMAL
    end

.global EventScript_Route8_FishermansHut_Fisherman
EventScript_Route8_FishermansHut_Fisherman:
    lock
    faceplayer
    checkflag 0x24B @ Got Good Rod
    if SET _goto FishermanFarewell
    msgbox gText_Route8_FishermansHut_FishermanIntro MSG_YESNO
    compare LASTRESULT YES
    IF TRUE _goto FishermanYes
    msgbox gText_Route8_FishermansHut_FishermanNo MSG_NORMAL
    release
    end

FishermanYes:
    msgbox gText_Route8_FishermansHut_FishermanYes MSG_NORMAL
    obtainitem ITEM_GOOD_ROD 0x1
    setflag 0x24B @ Got Good Rod
    msgbox gText_Route8_FishermansHut_FishermanGift MSG_NORMAL
    goto FishermanFarewell

FishermanFarewell:
    msgbox gText_Route8_FishermansHut_FishermanFarewell MSG_NORMAL
    release
    end

@ Route 9
.global EventScript_Route9_Flutist
EventScript_Route9_Flutist:
    faceplayer
    msgbox gText_Route9_FlutistShopIntroduction MSG_KEEPOPEN
    pokemart FluteShop
    msgbox gText_Route9_FlutistShopThanks MSG_NORMAL
    applymovement LASTTALKED m_LookDown
    end

.align 1
FluteShop:
    .hword ITEM_BLUE_FLUTE
    .hword ITEM_YELLOW_FLUTE
    .hword ITEM_RED_FLUTE
    .hword ITEM_BLACK_FLUTE
    .hword ITEM_WHITE_FLUTE
    .hword ITEM_NONE

.global EventScript_Route9_Sceptilite
EventScript_Route9_Sceptilite:
    finditem ITEM_SCEPTILITE 0x1
    end

.global EventScript_Route9_TM62_Acrobatics
EventScript_Route9_TM62_Acrobatics:
    setvar CHOSEN_ITEM ITEM_TM62
    call ItemScript_Common_FindTM
    end

.global EventScript_Route9_TM66_Payback
EventScript_Route9_TM66_Payback:
    setvar CHOSEN_ITEM ITEM_TM66
    call ItemScript_Common_FindTM
    end

.global EventScript_Route9_SlowbroGirl
EventScript_Route9_SlowbroGirl:
    msgbox gText_Route9_SlowbroGirlFrustration MSG_NORMAL
    faceplayer
    msgbox gText_Route9_SlowbroGirlApology MSG_NORMAL
    applymovement LASTTALKED m_LookLeft
    end

.global EventScript_Route9_Slowbro
EventScript_Route9_Slowbro:
    cry SPECIES_SLOWBRO 0x0
    applymovement LASTTALKED m_Question
    msgbox gText_Route9_Slowbro MSG_NORMAL
    end

.global EventScript_Route9_CollectorMarshall
EventScript_Route9_CollectorMarshall:
    trainerbattle0 0x0 0x9D 0x0 gText_Route9_CollectorMarshall_Intro gText_Route9_CollectorMarshall_Defeat
    msgbox gText_Route9_CollectorMarshall_Chat MSG_NORMAL
    end

.global EventScript_Route9_CoolTrainerAndrea
EventScript_Route9_CoolTrainerAndrea:
    trainerbattle0 0x0 0x9E 0x0 gText_Route9_CoolTrainerAndrea_Intro gText_Route9_CoolTrainerAndrea_Defeat
    msgbox gText_Route9_CoolTrainerAndrea_Chat MSG_NORMAL
    end

.global EventScript_Route9_FishermanYusuf
EventScript_Route9_FishermanYusuf:
    trainerbattle0 0x0 0x9F 0x0 gText_Route9_FishermanYusuf_Intro gText_Route9_FishermanYusuf_Defeat
    msgbox gText_Route9_FishermanYusuf_Chat MSG_NORMAL
    end

.global EventScript_Route9_GentlemanGavin
EventScript_Route9_GentlemanGavin:
    trainerbattle0 0x0 0xA0 0x0 gText_Route9_GentlemanGavin_Intro gText_Route9_GentlemanGavin_Defeat
    msgbox gText_Route9_GentlemanGavin_Chat MSG_NORMAL
    end

.global EventScript_Route9_NinjaBoyAyrton
EventScript_Route9_NinjaBoyAyrton:
    trainerbattle0 0x0 0xA1 0x0 gText_Route9_NinjaBoyAyrton_Intro gText_Route9_NinjaBoyAyrton_Defeat
    msgbox gText_Route9_NinjaBoyAyrton_Chat MSG_NORMAL
    end

.global EventScript_Route9_BreederTalia
EventScript_Route9_BreederTalia:
    trainerbattle0 0x0 0xA2 0x0 gText_Route9_BreederTalia_Intro gText_Route9_BreederTalia_Defeat
    msgbox gText_Route9_BreederTalia_Chat MSG_NORMAL
    end

.global EventScript_Route9_PicknickerZoe
EventScript_Route9_PicknickerZoe:
    trainerbattle0 0x0 0xA3 0x0 gText_Route9_PicknickerZoe_Intro gText_Route9_PicknickerZoe_Defeat
    msgbox gText_Route9_PicknickerZoe_Chat MSG_NORMAL
    end

.global EventScript_Route9_CoolTrainerKingsley
EventScript_Route9_CoolTrainerKingsley:
    trainerbattle0 0x0 0xA4 0x0 gText_Route9_CoolTrainerKingsley_Intro gText_Route9_CoolTrainerKingsley_Defeat
    msgbox gText_Route9_CoolTrainerKingsley_Chat MSG_NORMAL
    end

.global SignScript_Route9_TrainerTips
SignScript_Route9_TrainerTips:
    msgbox gText_Route9_TrainerTipsSign MSG_SIGN
    end

.global SignScript_Route9_FlutistsHouse
SignScript_Route9_FlutistsHouse:
    msgbox gText_Route9_FlutistsSign MSG_SIGN
    end

.global SignScript_Route9_Route12RestHouse
SignScript_Route9_Route12RestHouse:
    msgbox gText_Route9_RestHouseSign MSG_SIGN
    end

@ Route 10
.equ Casey, 0x11

.global EventScript_Route10_TM64_Explosion
EventScript_Route10_TM64_Explosion:
    setvar CHOSEN_ITEM ITEM_TM64
    call ItemScript_Common_FindTM
    end

.global EventScript_Route10_TM41_Torment
EventScript_Route10_TM41_Torment:
    setvar CHOSEN_ITEM ITEM_TM41
    call ItemScript_Common_FindTM
    end

.global EventScript_Route10_Lopunnite
EventScript_Route10_Lopunnite:
    finditem ITEM_LOPUNNITE 0x1
    end

.global EventScript_Route10_PsychicDarius
EventScript_Route10_PsychicDarius:
    trainerbattle0 0x0 0xA5 0x0 gText_Route10_PsychicDarius_Intro gText_Route10_PsychicDarius_Defeat
    msgbox gText_Route10_PsychicDarius_Chat MSG_NORMAL
    end

.global EventScript_Route10_BirdKeeperMario
EventScript_Route10_BirdKeeperMario:
    trainerbattle0 0x0 0xA6 0x0 gText_Route10_BirdKeeperMario_Intro gText_Route10_BirdKeeperMario_Defeat
    msgbox gText_Route10_BirdKeeperMario_Chat MSG_NORMAL
    end

.global EventScript_Route10_GamblerDarren
EventScript_Route10_GamblerDarren:
    trainerbattle0 0x0 0xA7 0x0 gText_Route10_GamblerDarren_Intro gText_Route10_GamblerDarren_Defeat
    msgbox gText_Route10_GamblerDarren_Chat MSG_NORMAL
    end

.global EventScript_Route10_ParasolLadyGwen
EventScript_Route10_ParasolLadyGwen:
    trainerbattle0 0x0 0xA8 0x0 gText_Route10_ParasolLady_Intro gText_Route10_ParasolLady_Defeat
    msgbox gText_Route10_ParasolLady_Chat MSG_NORMAL
    end

.global EventScript_Route10_CamperJackson
EventScript_Route10_CamperJackson:
    trainerbattle0 0x0 0xA9 0x0 gText_Route10_CamperJackson_Intro gText_Route10_CamperJackson_Defeat
    msgbox gText_Route10_CamperJackson_Chat MSG_NORMAL
    end

.global EventScript_Route10_RockerBert
EventScript_Route10_RockerBert:
    trainerbattle0 0x0 0xAA 0x0 gText_Route10_RockerBert_Intro gText_Route10_RockerBert_Defeat
    msgbox gText_Route10_RockerBert_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerAlberto
EventScript_Route10_SwimmerAlberto:
    trainerbattle0 0x0 0xAB 0x0 gText_Route10_SwimmerAlberto_Intro gText_Route10_SwimmerAlberto_Defeat
    msgbox gText_Route10_SwimmerAlberto_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerRosie
EventScript_Route10_SwimmerRosie:
    trainerbattle0 0x0 0xAC 0x0 gText_Route10_SwimmerRosie_Intro gText_Route10_SwimmerRosie_Defeat
    msgbox gText_Route10_SwimmerRosie_Chat MSG_NORMAL
    end

.global EventScript_Route10_SwimmerDoug
EventScript_Route10_SwimmerDoug:
    trainerbattle0 0x0 0xAD 0x0 gText_Route10_SwimmerDoug_Intro gText_Route10_SwimmerDoug_Defeat
    msgbox gText_Route10_SwimmerDoug_Chat MSG_NORMAL
    end

.global SignScript_Route10_TrainerTips_EvolutionTypes
SignScript_Route10_TrainerTips_EvolutionTypes:
    msgbox gText_Route10_TrainerTipsSign_Evolution MSG_SIGN
    end

.global SignScript_Route10_TrainerTips_TimeOfDay
SignScript_Route10_TrainerTips_TimeOfDay:
    msgbox gText_Route10_TrainerTipsSign_TimeOfDay MSG_SIGN
    end

.global SignScript_Route10_Route11Path
SignScript_Route10_Route11Path:
    msgbox gText_Route10_Route11Sign MSG_SIGN
    end

.global EventScript_Route10Cave_HikerHarley
EventScript_Route10Cave_HikerHarley:
    trainerbattle0 0x0 0xB0 0x0 gText_Route10Cave_HikerHarley_Intro gText_Route10Cave_HikerHarley_Defeat
    msgbox gText_Route10Cave_HikerHarley_Chat MSG_NORMAL
    end

.global EventScript_Route10Cave_BlackbeltXavier
EventScript_Route10Cave_BlackbeltXavier:
    trainerbattle0 0x0 0xB1 0x0 gText_Route10Cave_BlackbeltXavier_Intro gText_Route10Cave_BlackbeltXavier_Defeat
    msgbox gText_Route10Cave_BlackbeltXavier_Chat MSG_NORMAL
    end

.global EventScript_Route10Cave_TM23_SmackDown
EventScript_Route10Cave_TM23_SmackDown:
    setvar CHOSEN_ITEM ITEM_TM23
    call ItemScript_Common_FindTM
    end

.global TileScript_Route10_TriggerCaseyBattle_Above
TileScript_Route10_TriggerCaseyBattle_Above:
    checkflag 0x256 @ Battled Casey on Route 10
    if SET _goto End
    special 0xAF @ Dismount bike if on it
    lock
    call SetCaseyGender
    clearflag 0x03D @ Show Casey
    showsprite Casey
    playbgm 0x169 0x1 @ Alder encounter (Permanently replaces map music for cutscene)
    applymovement Casey m_WalkToPlayer
    waitmovement Casey
    call SetupMugshotRival
    checkgender
    compare LASTRESULT 0x0
    if equal _goto FCaseyEvent
    if notequal _goto MCaseyEvent

.global TileScript_Route10_TriggerCaseyBattle_Below
TileScript_Route10_TriggerCaseyBattle_Below:
    checkflag 0x256 @ Battled Casey on Route 10
    if SET _goto End
    special 0xAF @ Dismount bike if on it
    applymovement PLAYER m_WalkUp
    waitmovement PLAYER
    applymovement PLAYER m_LookRight
    waitmovement PLAYER
    goto TileScript_Route10_TriggerCaseyBattle_Above

FCaseyEvent:
    msgbox gText_Route10_CaseyFIntroduction MSG_NORMAL
    trainerbattle2 0x0 0xAE 0x100 gText_Route10_CaseyFBattleIntro gText_Route10_CaseyFBattleDefeat FCaseyEventPostBattle

FCaseyEventPostBattle:
    msgbox gText_Route10_CaseyFExpShareGift MSG_NORMAL
    obtainitem ITEM_EXP_SHARE 0x1
    msgbox gText_Route10_CaseyFExpShareExplained MSG_NORMAL
    msgbox gText_Route10_CaseyFPostBattle MSG_NORMAL
    applymovement Casey m_LookRight
    msgbox gText_Route10_CaseyFReflection MSG_NORMAL
    applymovement Casey m_LookLeft
    msgbox gText_Route10_CaseyFLeaves MSG_NORMAL
    goto CaseyLeavesCommon

MCaseyEvent:
    msgbox gText_Route10_CaseyMIntroduction MSG_NORMAL
    trainerbattle2 0x0 0xAF 0x100 gText_Route10_CaseyMBattleIntro gText_Route10_CaseyMBattleDefeat MCaseyEventPostBattle

MCaseyEventPostBattle:
    msgbox gText_Route10_CaseyMExpShareGift MSG_NORMAL
    obtainitem ITEM_EXP_SHARE 0x1
    msgbox gText_Route10_CaseyMExpShareExplained MSG_NORMAL
    msgbox gText_Route10_CaseyMPostBattle MSG_NORMAL
    applymovement Casey m_LookRight
    msgbox gText_Route10_CaseyMReflection MSG_NORMAL
    applymovement Casey m_LookLeft
    msgbox gText_Route10_CaseyMLeaves MSG_NORMAL
    goto CaseyLeavesCommon

CaseyLeavesCommon:
    applymovement Casey m_WalkAwayFromPlayer
    waitmovement Casey
    hidesprite Casey
    setflag 0x03D @ Hide Casey
    setflag 0x256 @ Battled Casey on route 10
    playbgm 0x15E 0x1 @ Regular route 10 track (Replace override from cutscene)
    signmsg
    msgbox gText_Route10_ExpShareHint MSG_SIGN
    normalmsg
    end

m_WalkToPlayer: .byte walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, walk_left, end_m
m_WalkAwayFromPlayer: .byte walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, walk_right, end_m
