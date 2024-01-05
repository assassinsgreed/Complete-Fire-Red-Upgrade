.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.equ FormanEventVar, 0x4051
.equ Casey, 0x14

.global MapScript_TormaCave
MapScript_TormaCave:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_TormaCave_FlightFlag
    mapscript MAP_SCRIPT_ON_LOAD SetStunfiskTrapsVisbility
	.byte MAP_SCRIPT_TERMIN

MapEntryScript_TormaCave_FlightFlag:
    setworldmapflag 0x8A6 @ Been to Torma Cave
    setvar FormanEventVar 0x0
    end

SetStunfiskTrapsVisbility:
    checkflag 0xE03
    if NOT_SET _call SetStunfisk1Visibility
    if SET _call HideStunfisk1
    checkflag 0xE04
    if NOT_SET _call SetStunfisk2Visibility
    if SET _call HideStunfisk2
    checkflag 0xE05
    if NOT_SET _call SetStunfisk3Visibility
    if SET _call HideStunfisk3
    end

SetStunfisk1Visibility:
    setmaptile 0x10 0x20 0x30B 0x0
    return

HideStunfisk1:
    setmaptile 0x10 0x20 0x281 0x0
    special 0x8E
    return

HideStunfisk2:
    setmaptile 0x30 0xF 0x281 0x0
    special 0x8E
    return

HideStunfisk3:
    setmaptile 0x1C 0xA 0x281 0x0
    special 0x8E
    return

SetStunfisk2Visibility:
    setmaptile 0x30 0xF 0x30B 0x0
    return

SetStunfisk3Visibility:
    setmaptile 0x1C 0xA 0x30B 0x0
    return

.global EventScript_TormaCave_RockyHelmet
EventScript_TormaCave_RockyHelmet:
    finditem ITEM_ROCKY_HELMET 0x1
    end

.global EventScript_TormaCave_Glalitite
EventScript_TormaCave_Glalitite:
    finditem ITEM_GLALITITE 0x1
    end

.global EventScript_TormaCave_FishermanAlfie
EventScript_TormaCave_FishermanAlfie:
    trainerbattle0 0x0 0x2D 0x0 gText_TormaCave_FishermanAlfie_Intro gText_TormaCave_FishermanAlfie_Defeat
    msgbox gText_TormaCave_FishermanAlfie_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_HikerNob
EventScript_TormaCave_HikerNob:
    trainerbattle0 0x0 0x2E 0x0 gText_TormaCave_HikerNob_Intro gText_TormaCave_HikerNob_Defeat
    msgbox gText_TormaCave_HikerNob_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_HikerSaul
EventScript_TormaCave_HikerSaul:
    trainerbattle0 0x0 0x2F 0x0 gText_TormaCave_HikerSaul_Intro gText_TormaCave_HikerSaul_Defeat
    msgbox gText_TormaCave_HikerSaul_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_EngineerWyatt
EventScript_TormaCave_EngineerWyatt:
    trainerbattle0 0x0 0x30 0x0 gText_TormaCave_EngineerWyatt_Intro gText_TormaCave_EngineerWyatt_Defeat
    msgbox gText_TormaCave_EngineerWyatt_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_EngineerShane
EventScript_TormaCave_EngineerShane:
    trainerbattle0 0x0 0x31 0x0 gText_TormaCave_EngineerShane_Intro gText_TormaCave_EngineerShane_Defeat
    msgbox gText_TormaCave_EngineerShane_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_PokefanCorey
EventScript_TormaCave_PokefanCorey:
    trainerbattle0 0x0 0x32 0x0 gText_TormaCave_PokefanCorey_Intro gText_TormaCave_PokefanCorey_Defeat
    msgbox gText_TormaCave_PokefanCorey_Chat MSG_NORMAL
    end

.global EventScript_TormaCave_LassHarmony
EventScript_TormaCave_LassHarmony:
    trainerbattle0 0x0 0x33 0x0 gText_TormaCave_LassHarmony_Intro gText_TormaCave_LassHarmony_Defeat
    msgbox gText_TormaCave_LassHarmony_Chat MSG_NORMAL
    end

.global SignScript_TormaCave_TrainerTips
SignScript_TormaCave_TrainerTips:
    msgbox gText_TormaCave_TrainerTips MSG_SIGN
    end

.global EventScript_TormaCave_TM79_FrostBreath
EventScript_TormaCave_TM79_FrostBreath:
    setvar CHOSEN_ITEM ITEM_TM79
    call ItemScript_Common_FindTM
    end

.global TileScript_TormaCave_StunfiskEncounter1
TileScript_TormaCave_StunfiskEncounter1:
    checkflag 0xE03
    if SET _goto End
    call StunfiskEncounter
    setflag 0xE03
    call HideStunfisk1
    end

.global TileScript_TormaCave_StunfiskEncounter2
TileScript_TormaCave_StunfiskEncounter2:
    checkflag 0xE04
    if SET _goto End
    call StunfiskEncounter
    setflag 0xE04
    call HideStunfisk2
    end

.global TileScript_TormaCave_StunfiskEncounter3
TileScript_TormaCave_StunfiskEncounter3:
    checkflag 0xE05
    if SET _goto End
    call StunfiskEncounter
    setflag 0xE05
    call HideStunfisk3
    end

StunfiskEncounter:
    lock
    checksound
    cry SPECIES_STUNFISK_G 0x0
    sound 0x15 @ Exclaim
    applymovement PLAYER m_Surprise
    msgbox gText_TormaCave_StunfiskEncounter MSG_KEEPOPEN
    wildbattle SPECIES_STUNFISK_G 0xE 0x0
    hidesprite LASTTALKED
    release
    return

.global TileScript_TormaCave_SetPathCleared
TileScript_TormaCave_SetPathCleared:
    setflag 0x35 @ Cleared Torma Cave
    @ Set the other tile event up to execute
    setvar 0x4000 0x1
    setvar 0x4001 0x0
    end

.global TileScript_TormaCave_ClearPathCleared
TileScript_TormaCave_ClearPathCleared:
    # Only clear the flag indicating that Torma Cave has been cleared if the player hasn't spoken with the Foreman upon leaving
    # This avoids a case where the player goes to the end of the cave, leaves from the start, and breaks the cutscene
    checkflag 0x36 @ Met with Foreman
    if SET _goto End
    clearflag 0x35 @ Cleared Torma Cave
    @ Set the other tile event up to execute
    setvar 0x4000 0x0
    setvar 0x4001 0x1
    end

.global TileScript_TormaCave_TriggerCaseyBattleL
TileScript_TormaCave_TriggerCaseyBattleL:
    checkflag 0x255 @ Battled Casey
    if SET _goto End
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    goto TileScript_TormaCave_TriggerCaseyBattleM

.global TileScript_TormaCave_TriggerCaseyBattleM
TileScript_TormaCave_TriggerCaseyBattleM:
    checkflag 0x255 @ Battled Casey
    if SET _goto End
    applymovement PLAYER m_WalkRight
    waitmovement PLAYER
    goto TileScript_TormaCave_TriggerCaseyBattleR

.global TileScript_TormaCave_TriggerCaseyBattleR
TileScript_TormaCave_TriggerCaseyBattleR:
    checkflag 0x255 @ Battled Casey
    if SET _goto End
    call SetCaseyGender
    applymovement PLAYER m_LookUp
    playse 0x9 @ Exit room
    pause DELAY_HALFSECOND
    clearflag 0x03D @ Show Casey
    showsprite Casey
    playbgm 0x169 0x1 @ Alder encounter (Permanently replaces map music for cutscene)
    setvar 0x503A 0x2
    setvar 0x503B 0x0
    checkgender
    compare LASTRESULT 0x0
    if equal _goto FCaseyEvent
    if notequal _goto MCaseyEvent

MCaseyEvent:
    msgbox gText_TormaCave_MCaseyFirstMessage MSG_NORMAL
    applymovement Casey m_CaseyWalksToPlayer
    waitmovement Casey
    msgbox gText_TormaCave_MCaseyIntroduction MSG_NORMAL
    trainerbattle2 0x0 0x9C 0x100 gText_TormaCave_MCaseyBattleIntro gText_TormaCave_MCaseyBattleDefeat MCaseyEventPostBattle
    end

MCaseyEventPostBattle:
    msgbox gText_TormaCave_MCaseyCommentsOnBeingLost MSG_NORMAL
    applymovement Casey m_Question
    msgbox gText_TormaCave_MCaseyLeaves MSG_NORMAL
    goto CaseyLeaves

FCaseyEvent:
    msgbox gText_TormaCave_FCaseyFirstMessage MSG_NORMAL
    applymovement Casey m_CaseyWalksToPlayer
    waitmovement ALLEVENTS
    msgbox gText_TormaCave_FCaseyTrainerQuestion MSG_YESNO
    compare LASTRESULT NO
    if equal _call SaidNoToFCasey
    if notequal _call SaidYesToFCasey
    msgbox gText_TormaCave_FCaseyIntroduction MSG_NORMAL
    trainerbattle2 0x0 0x9B 0x100 gText_TormaCave_FCaseyBattleIntro gText_TormaCave_FCaseyBattleDefeat FCaseyEventPostBattle
    end

FCaseyEventPostBattle:
    msgbox gText_TormaCave_FCaseyRecallingWhatTheyAreDoing MSG_NORMAL
    sound 0x15 @ Exclaim
	applymovement Casey m_Surprise
    msgbox gText_TormaCave_FCaseyRemembers MSG_NORMAL
    applymovement Casey m_Question
    msgbox gText_TormaCave_FCaseyLeaves MSG_NORMAL
    goto CaseyLeaves

SaidNoToFCasey:
    applymovement Casey m_Question
    msgbox gText_TormaCave_FCaseySaidNo MSG_NORMAL
    return

SaidYesToFCasey:
    sound 0x15 @ Exclaim
	applymovement Casey m_Surprise
    msgbox gText_TormaCave_FCaseySaidYes MSG_NORMAL
    return

CaseyLeaves:
    applymovement Casey m_CaseyWalksAway
    waitmovement Casey
    playse 0x9 @ Exit room
    pause DELAY_HALFSECOND
    setflag 0x03D @ Hide Casey
    setflag 0x255 @ Battled Casey
    hidesprite Casey
    playbgm 0x133 0x1 @ Play regular Torma Cave track (Replace override from cutscene)
    textcolor BLACK
    end

m_CaseyWalksToPlayer: .byte walk_down, walk_down, pause_long, look_left, pause_long, pause_long, pause_long, look_right, pause_long, pause_long, pause_long, pause_long, look_down, exclaim, walk_down, walk_down, end_m
m_CaseyWalksAway: .byte walk_up, walk_up, walk_up, walk_up, end_m
