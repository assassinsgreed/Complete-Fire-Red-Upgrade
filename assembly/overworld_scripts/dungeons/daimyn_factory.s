.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_DaimynFactoryOverworld
MapScript_DaimynFactoryOverworld:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_DaimynFactoryOverworld_FlightFlag
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_DaimynFactoryOverworld_FlightFlag:
    setworldmapflag 0x8B4 @ Been to Daimyn Factory Overworld
    end

.global EventScript_DaimynFactoryOverworld_BirdKeeperMarius
EventScript_DaimynFactoryOverworld_BirdKeeperMarius:
    trainerbattle0 0x0 0x89 0x0 gText_DaimynFactoryOverworld_BirdKeeperMarius_Intro gText_DaimynFactoryOverworld_BirdKeeperMarius_Defeat
    msgbox gText_DaimynFactoryOverworld_BirdKeeperMarius_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_RockerBenson
EventScript_DaimynFactoryOverworld_RockerBenson:
    trainerbattle0 0x0 0x8A 0x0 gText_DaimynFactoryOverworld_RockerBenson_Intro gText_DaimynFactoryOverworld_RockerBenson_Defeat
    msgbox gText_DaimynFactoryOverworld_RockerBenson_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_LassMimi
EventScript_DaimynFactoryOverworld_LassMimi:
    trainerbattle0 0x0 0x8B 0x0 gText_DaimynFactoryOverworld_LassMimi_Intro gText_DaimynFactoryOverworld_LassMimi_Defeat
    msgbox gText_DaimynFactoryOverworld_LassMimi_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerJamison
EventScript_DaimynFactoryOverworld_EngineerJamison:
    trainerbattle0 0x0 0x8C 0x0 gText_DaimynFactoryOverworld_EngineerJamison_Intro gText_DaimynFactoryOverworld_EngineerJamison_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerJamison_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_HikerMike
EventScript_DaimynFactoryOverworld_HikerMike:
    trainerbattle0 0x0 0x8D 0x0 gText_DaimynFactoryOverworld_HikerMike_Intro gText_DaimynFactoryOverworld_HikerMike_Defeat
    msgbox gText_DaimynFactoryOverworld_HikerMike_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_BlackBeltRory
EventScript_DaimynFactoryOverworld_BlackBeltRory:
    trainerbattle0 0x0 0x8E 0x0 gText_DaimynFactoryOverworld_BlackbeltRory_Intro gText_DaimynFactoryOverworld_BlackbeltRory_Defeat
    msgbox gText_DaimynFactoryOverworld_BlackbeltRory_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerWilson
EventScript_DaimynFactoryOverworld_EngineerWilson:
    trainerbattle0 0x0 0x8F 0x0 gText_DaimynFactoryOverworld_EngineerWilson_Intro gText_DaimynFactoryOverworld_EngineerWilson_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerWilson_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_YoungsterNate
EventScript_DaimynFactoryOverworld_YoungsterNate:
    trainerbattle0 0x0 0x90 0x0 gText_DaimynFactoryOverworld_YoungsterNate_Intro gText_DaimynFactoryOverworld_YoungsterNate_Defeat
    msgbox gText_DaimynFactoryOverworld_YoungsterNate_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_PicknickerShanna
EventScript_DaimynFactoryOverworld_PicknickerShanna:
    trainerbattle0 0x0 0x91 0x0 gText_DaimynFactoryOverworld_PicknickerShanna_Intro gText_DaimynFactoryOverworld_PicknickerShanna_Defeat
    msgbox gText_DaimynFactoryOverworld_PicknickerShanna_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_EngineerKliff
EventScript_DaimynFactoryOverworld_EngineerKliff:
    trainerbattle0 0x0 0x92 0x0 gText_DaimynFactoryOverworld_EngineerKliff_Intro gText_DaimynFactoryOverworld_EngineerKliff_Defeat
    msgbox gText_DaimynFactoryOverworld_EngineerKliff_Chat MSG_NORMAL
    end

.global EventScript_DaimynFactoryOverworld_Lucarionite
EventScript_DaimynFactoryOverworld_Lucarionite:
    finditem ITEM_LUCARIONITE 0x1
    end

.global EventScript_DaimynFactoryOverworld_FindTM57_WildCharge
EventScript_DaimynFactoryOverworld_FindTM57_WildCharge:
    setvar CHOSEN_ITEM ITEM_TM57
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynFactoryOverworld_FindTM93_Wild_Charge
EventScript_DaimynFactoryOverworld_FindTM93_Wild_Charge:
    setvar CHOSEN_ITEM ITEM_TM93
    call ItemScript_Common_FindTM
    end

.global EventScript_DaimynFactoryOverworld_ReminiscingOldMan
EventScript_DaimynFactoryOverworld_ReminiscingOldMan:
    npcchat gText_DaimynFactoryOverworld_ReminiscingOldMan
    applymovement LASTTALKED m_LookUp
    end

.global EventScript_DaimynFactoryOverworld_StrongTrainersGirl
EventScript_DaimynFactoryOverworld_StrongTrainersGirl:
    npcchat gText_DaimynFactoryOverworld_StrongTrainersWarning
    end

.global SignScript_DaimynFactoryOverworld_EntranceSign
SignScript_DaimynFactoryOverworld_EntranceSign:
    msgbox gText_DaimynFactoryOverworld_EntranceSign MSG_SIGN
    end

.global SignScript_DaimynFactoryOverworld_TrainerTipsStats
SignScript_DaimynFactoryOverworld_TrainerTipsStats:
    msgbox gText_DaimynFactoryOverworld_TrainerTipsStats MSG_SIGN
    end

.global SignScript_DaimynFactoryOverworld_TrainerTipsFriendlyPokemonMoreExp
SignScript_DaimynFactoryOverworld_TrainerTipsFriendlyPokemonMoreExp:
    msgbox gText_DaimynFactoryOverworld_FriendlyPokemonMoreExp MSG_SIGN
    end

.global TileScript_DaimynFactoryOverworld_DaimynFactoryLocked
TileScript_DaimynFactoryOverworld_DaimynFactoryLocked:
    # TODO: Someday: check if the player has the factory key
    applymovement PLAYER m_LookUp
    msgbox gText_DoorIsLocked MSG_NORMAL
    applymovement PLAYER m_WalkDown
    waitmovement PLAYER
    end
