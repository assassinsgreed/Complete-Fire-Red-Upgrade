.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_BattleFrontier
MapScript_BattleFrontier:
    mapscript MAP_SCRIPT_ON_TRANSITION MapEntryScript_BattleFrontier_FlightSpot
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_BattleFrontier_FlightSpot:
    setworldmapflag 0x8B3 @ Visited the Battle Frontier
    end

.global EventScript_BattleFrontier_SE_Tutor1
EventScript_BattleFrontier_SE_Tutor1:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier1
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SE_Tutor2
EventScript_BattleFrontier_SE_Tutor2:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier2
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SE_Tutor3
EventScript_BattleFrontier_SE_Tutor3:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier3
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

.global EventScript_BattleFrontier_SE_Tutor4
EventScript_BattleFrontier_SE_Tutor4:
    call TutorIntro
    call EventScript_Tutors_BattleFrontier4
    compare LASTRESULT TRUE
    if equal _goto TutoringComplete
    end

TutorIntro:
    lock
    faceplayer
    callasm StorePokeChipCount
    buffernumber 0x0 0x8005 @ Take stored PokeChip count
    msgbox gText_BattleFrontier_MoveTutor_Confirmation MSG_YESNO
    compare LASTRESULT YES
    IF FALSE _goto TutoringRejected
    checkitem ITEM_POKE_CHIP 5
    compare LASTRESULT TRUE
    if FALSE _goto NotEnoughPokeChips
    msgbox gText_BattleFrontier_MoveTutor_ConfirmationAccepted MSG_KEEPOPEN
    return

TutoringComplete:
    msgbox gText_BattleFrontier_MoveTutor_Complete MSG_NORMAL
    return

TutoringRejected:
    npcchatwithmovement gText_BattleFrontier_MoveTutor_Rejected m_LookDown
    goto End

NotEnoughPokeChips:
    npcchatwithmovement gText_BattleFrontier_MoveTutor_NotEnoughPokeChips m_LookDown
    goto End

@ ============================================================================
@ Battle Frontier Facility scripts
@
@ One shared attendant script drives every facility. A facility is identified only by
@ VAR_BATTLE_FACILITY_NUM, so the format choice, party entry, battle loop,
@ Continue/Rest/Give up prompts and records board below are all shared. The only
@ per-facility code is the hook each one runs before a battle, dispatched from
@ BattleFrontier_Common_PerBattleSetup.
@
@ A run belongs to one facility/format pair, allowing every facility to hold onto
@ a paused streak that can be resumed at any time. The player is free to wanter while a
@ streak is paused.
@
@ Adding a facility is: an entry point that sets VAR_BATTLE_FACILITY_NUM and jumps to
@ BattleFrontier_Common_Attendant, a case in BattleFrontier_Common_PerBattleSetup, and a rules
@ string with a case in BattleFrontier_Common_FacilityRules. See the Battle Tower as a reference.
@ ============================================================================

@ enum BattleFacilities, from include/new/frontier.h
.equ IN_BATTLE_TOWER, 0x0
.equ IN_BATTLE_SANDS, 0x1
.equ IN_BATTLE_MINE, 0x2
.equ IN_BATTLE_CIRCUS, 0x3
.equ IN_BATTLE_FACTORY, 0x4
.equ IN_RING_CHALLENGE, 0x5
.equ IN_ISLE_CHALLENGE, 0x6
.equ IN_BATTLE_MAZE, 0x7

@ enum FrontierStreakFormats
.equ FRONTIER_FORMAT_SINGLES, 0x0
.equ FRONTIER_FORMAT_DOUBLES, 0x1

@ enum FrontierChallengeStates
.equ FRONTIER_NONE, 0x0
.equ FRONTIER_ACTIVE, 0x1
.equ FRONTIER_RESTING, 0x2

@ enum FrontierOpponentKinds
.equ FRONTIER_OPPONENT_REGULAR, 0x0
.equ FRONTIER_OPPONENT_ACE, 0x1
.equ FRONTIER_OPPONENT_BRAIN, 0x2

@ Reserved trainer IDs, from include/new/frontier.h
.equ FRONTIER_BRAIN_TID, 0x397
.equ BATTLE_TOWER_SPECIAL_TID, 0x398
.equ BATTLE_TOWER_TID, 0x399

.equ VAR_BATTLE_FACILITY_NUM, 0x403A
.equ FLAG_GAME_CLEARED, 0x82C

.equ SPECIAL_SAVE_PLAYER_PARTY, 0x27
.equ SPECIAL_LOAD_PLAYER_PARTY, 0x28
.equ SPECIAL_CHOOSE_FRONTIER_TEAM, 0xF5
.equ SPECIAL_GENERATE_FACILITY_TRAINER, 0x52
.equ SPECIAL_LOAD_FRONTIER_INTRO_MESSAGE, 0x53
.equ SPECIAL_UPDATE_FACILITY_STREAK, 0x55
.equ SPECIAL_SHOW_FRONTIER_RECORDS, 0x57
.equ SPECIAL_MODIFY_TEAM_FOR_FRONTIER, 0x73

.equ STREAK_INCREMENT, 0x0
.equ STREAK_RESET, 0x1

@ Indices into gScrollingSets in src/scripting.c
.equ MULTICHOICE_SET_FRONTIER_MUSIC, 0x15
.equ MULTICHOICE_SET_FRONTIER_BACKGROUND, 0x16
.equ SPECIAL_SCROLLING_MULTICHOICE, 0x158

@ Var8000 value that makes trainerbattle9 continue the script after a loss (no white out)
.equ CONTINUE_AFTER_LOSS, 0xFEFE

@ ============================================================================
@ Per-facility entry points
@ ============================================================================

.global EventScript_BattleFrontier_TowerAttendant
EventScript_BattleFrontier_TowerAttendant:
    setvar VAR_BATTLE_FACILITY_NUM IN_BATTLE_TOWER
    goto BattleFrontier_Common_Attendant

@ ============================================================================
@ Shared attendant flow
@ ============================================================================

BattleFrontier_Common_Attendant:
    lock
    faceplayer
    @ Must run before anything reads a streak or a run's state.
    callasm FrontierChallenge_InitDataIfNeeded
    goto BattleFrontier_Common_LobbyMenu

@ Every way out of the attendant goes through here, so nothing can leave the overworld with
@ FLAG_BATTLE_FACILITY still set - see FrontierChallenge_ClearFacilityVars.
BattleFrontier_Common_Exit:
    callasm FrontierChallenge_ClearFacilityVars
    goto End

BattleFrontier_Common_LobbyMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_Welcome MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceChallenge 0
    multichoiceoption gText_BattleFrontier_ChoiceRules 1
    multichoiceoption gText_BattleFrontier_ChoiceRecords 2
    multichoiceoption gText_BattleFrontier_ChoiceBackground 3
    multichoiceoption gText_BattleFrontier_ChoiceMusic 4
    multichoiceoption gText_BattleFrontier_ChoiceLeave 5
    multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_ChooseFormat
    case 1, BattleFrontier_Common_Rules
    case 2, BattleFrontier_Common_Records
    case 3, BattleFrontier_Common_Background
    case 4, BattleFrontier_Common_Music
    goto BattleFrontier_Common_Farewell

BattleFrontier_Common_Farewell:
    msgbox gText_BattleFrontier_Farewell MSG_NORMAL
    goto BattleFrontier_Common_Exit

@ ============================================================================
@ Rules and records
@ ============================================================================

@ Prompt for Frontier (common) rules or Facility-specific
BattleFrontier_Common_Rules:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_RulesPrompt MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceFrontierRules 0
    multichoiceoption gText_BattleFrontier_ChoiceFacilityRules 1
    multichoiceoption gText_BattleFrontier_ChoiceCancel 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_FrontierRules
    case 1, BattleFrontier_Common_FacilityRules
    goto BattleFrontier_Common_LobbyMenu

BattleFrontier_Common_FrontierRules:
    msgbox gText_BattleFrontier_CommonRules MSG_KEEPOPEN
    goto BattleFrontier_Common_Rules

@ A facility with no case here shows nothing at all, so every facility owes this switch a line.
BattleFrontier_Common_FacilityRules:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_Rules, _call
    goto BattleFrontier_Common_Rules

BattleFrontier_Tower_Rules:
    msgbox gText_BattleFrontier_TowerRules MSG_KEEPOPEN
    return

BattleFrontier_Common_Records:
    special SPECIAL_SHOW_FRONTIER_RECORDS
    waitstate
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Battle background
@ ============================================================================

BattleFrontier_Common_Background:
    callasm FrontierChallenge_BufferBattleBackgroundName
    msgbox gText_BattleFrontier_ChooseBackground MSG_KEEPOPEN
    setvar SCROLL_MULTICHOICE_NUM MULTICHOICE_SET_FRONTIER_BACKGROUND
    setvar SCROLL_MULTICHOICE_HEIGHT 0x6
    setvar 0x8004 0x0 @ Always 0, so the menu cleans itself up when called again
    special SPECIAL_SCROLLING_MULTICHOICE
    waitstate
    copyvar 0x8000 LASTRESULT
    callasm FrontierChallenge_SetBattleBackground
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    msgbox gText_BattleFrontier_BackgroundChosen MSG_KEEPOPEN
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Battle music
@ ============================================================================

BattleFrontier_Common_Music:
    callasm FrontierChallenge_BufferBattleMusicName
    msgbox gText_BattleFrontier_ChooseMusic MSG_KEEPOPEN
    setvar SCROLL_MULTICHOICE_NUM MULTICHOICE_SET_FRONTIER_MUSIC
    setvar SCROLL_MULTICHOICE_HEIGHT 0x6
    setvar 0x8004 0x0 @ Always 0, so the menu cleans itself up when called again
    special SPECIAL_SCROLLING_MULTICHOICE
    waitstate
    copyvar 0x8000 LASTRESULT
    callasm FrontierChallenge_SetBattleMusic
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    msgbox gText_BattleFrontier_MusicChosen MSG_KEEPOPEN
    goto BattleFrontier_Common_LobbyMenu

@ ============================================================================
@ Starting a challenge
@ ============================================================================

@ Each challenge is facility/format specific (e.x. Battle Tower Singles & Battle Tower Doubles)
BattleFrontier_Common_ChooseFormat:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_ChooseFormat MSG_KEEPOPEN
    multichoiceoption gText_BattleFrontier_ChoiceSingles 0
    multichoiceoption gText_BattleFrontier_ChoiceDoubles 1
    multichoiceoption gText_BattleFrontier_ChoiceCancel 2
    @ Handle format multichoice text for runs that are in progress
    setvar 0x8000 FRONTIER_FORMAT_SINGLES
    callasm FrontierChallenge_IsFormatPaused
    compare LASTRESULT TRUE
    if equal _call BattleFrontier_Common_LabelSinglesOnHold
    setvar 0x8000 FRONTIER_FORMAT_DOUBLES
    callasm FrontierChallenge_IsFormatPaused
    compare LASTRESULT TRUE
    if equal _call BattleFrontier_Common_LabelDoublesOnHold
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_FormatSingles
    case 1, BattleFrontier_Common_FormatDoubles
    goto BattleFrontier_Common_LobbyMenu

BattleFrontier_Common_LabelSinglesOnHold:
    multichoiceoption gText_BattleFrontier_ChoiceSinglesOnHold 0
    return

BattleFrontier_Common_LabelDoublesOnHold:
    multichoiceoption gText_BattleFrontier_ChoiceDoublesOnHold 1
    return

BattleFrontier_Common_FormatSingles:
    setvar 0x8000 FRONTIER_FORMAT_SINGLES
    goto BattleFrontier_Common_FormatChosen

BattleFrontier_Common_FormatDoubles:
    setvar 0x8000 FRONTIER_FORMAT_DOUBLES
    goto BattleFrontier_Common_FormatChosen

@ Load the format so the party selection screen can prompt for the right number of pokemon (3 vs 4)
BattleFrontier_Common_FormatChosen:
    callasm FrontierChallenge_LoadFacilityVars
    callasm FrontierChallenge_GetState
    compare LASTRESULT FRONTIER_RESTING
    if equal _goto BattleFrontier_Common_RunOnHold
    goto BattleFrontier_Common_BeginChallenge

BattleFrontier_Common_BeginChallenge:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_BufferNumMonsToEnter
    msgbox gText_BattleFrontier_ConfirmChallenge MSG_YESNO
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_LobbyMenu
    call BattleFrontier_Common_EnterTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_LobbyMenu
    callasm FrontierChallenge_Begin
    goto BattleFrontier_Common_StartRun

@ The last steps before a run's first battle, shared by a new run and one picked back up.
@ The order of these three is load-bearing and must not be shuffled:
@
@   - the save must occur while gPlayerParty still holds the player's real team. Saving
@     serialises gPlayerParty into SaveBlock1.playerParty (SaveSerializedGame calls
@     SavePlayerParty), so a save made after sp073 writes the Level 50 entered copies over
@     both the live party and the backup special 0x28 restores from. A reset after that
@     strands the player with the frontier team and no way back to their own.
@   - the modifier override has to follow the save, so the player's preferred modifiers
@     remain set in the save file - see FrontierChallenge_OverrideGameModifiers.
@   - sp073 goes last, because replacing the party is exactly what it does.
BattleFrontier_Common_StartRun:
    call BattleFrontier_Common_CommitRun
    callasm FrontierChallenge_OverrideGameModifiers
    special SPECIAL_MODIFY_TEAM_FOR_FRONTIER
    goto BattleFrontier_Common_BattleLoop

@ Handles both a new run and a resumed run.
@ The run is set to ACTIVE in the player save so FrontierChallenge_InitDataIfNeeded will cancel
@ its streak if the player soft resets to try and game the randomized trainers.
BattleFrontier_Common_CommitRun:
    callasm FrontierChallenge_NeedsCommitting
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_CommitRunDone
    msgbox gText_BattleFrontier_ResumeWarning MSG_KEEPOPEN
    callasm FrontierChallenge_Commit
    callasm FrontierChallenge_ClearFacilityVars
    callasm FrontierChallenge_ForceSave
    waitstate
    callasm FrontierChallenge_SetFacilityFlag

BattleFrontier_Common_CommitRunDone:
    return

@ Backs up the real party, has the player pick their entered team, then puts the real
@ party back so sp073 can build the level-adjusted copies from the chosen slots.
@ Returns FALSE if the player backed out.
BattleFrontier_Common_EnterTeam:
    special SPECIAL_SAVE_PLAYER_PARTY
    msgbox gText_BattleFrontier_ChooseTeam MSG_KEEPOPEN
    special SPECIAL_CHOOSE_FRONTIER_TEAM
    waitstate
    callasm FrontierChallenge_DidChooseTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_EnterTeamCancelled
    special SPECIAL_LOAD_PLAYER_PARTY
    setvar LASTRESULT TRUE
    return

BattleFrontier_Common_EnterTeamCancelled:
    setvar LASTRESULT FALSE
    return

@ ============================================================================
@ Battle loop
@ ============================================================================

BattleFrontier_Common_BattleLoop:
    call BattleFrontier_Common_PerBattleSetup
    callasm FrontierChallenge_SetUpNextOpponent
    special2 LASTRESULT SPECIAL_GENERATE_FACILITY_TRAINER
    special SPECIAL_LOAD_FRONTIER_INTRO_MESSAGE
    callstd MSG_KEEPOPEN @ Prints the line sp053 left in gLoadPointer
    callasm FrontierChallenge_RestoreTextColour
    compare 0x8001 FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_BattleSpecialTrainer
    compare 0x8001 FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_BattleFrontierBrain
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 BATTLE_TOWER_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleSpecialTrainer:
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 BATTLE_TOWER_SPECIAL_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleFrontierBrain:
    setvar 0x8000 CONTINUE_AFTER_LOSS
    trainerbattle9 0x9 FRONTIER_BRAIN_TID 0x0 gText_BattleFrontier_OpponentDefeated gText_BattleFrontier_OpponentVictorious
    goto BattleFrontier_Common_BattleEnded

BattleFrontier_Common_BattleEnded:
    setvar 0x8000 0x0
    callasm FrontierChallenge_DidPlayerWin
    compare LASTRESULT TRUE
    if notequal _goto BattleFrontier_Common_Loss
    goto BattleFrontier_Common_Win

@ Circus randomizes its field effects here (special 0x72), Mine its battle options (0x70),
@ Factory and Maze swap or reroll the team. The Tower is the baseline and does nothing.
BattleFrontier_Common_PerBattleSetup:
    switch VAR_BATTLE_FACILITY_NUM
    case IN_BATTLE_TOWER, BattleFrontier_Tower_PerBattleSetup, _call
    return

BattleFrontier_Tower_PerBattleSetup:
    @ TODO: Handle NPC walking in, leaving, etc.
    return

@ ============================================================================
@ Winning, and the Continue / Rest / Give up prompt
@ ============================================================================

BattleFrontier_Common_Win:
    setvar 0x8000 STREAK_INCREMENT
    special SPECIAL_UPDATE_FACILITY_STREAK
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_StoreChipsToGive
    compare LASTRESULT 0
    if equal _goto BattleFrontier_Common_WinNoRoomForChips
    msgbox gText_BattleFrontier_WinReward MSG_KEEPOPEN
    setvar 0x8000 ITEM_POKE_CHIP
    copyvar 0x8001 LASTRESULT
    callstd MSG_OBTAIN
    goto BattleFrontier_Common_ChallengeMenu

@ Reminder: Player can only hold 999 PokeChips so they may get reduced (or no) rewards based on bag stock
BattleFrontier_Common_WinNoRoomForChips:
    msgbox gText_BattleFrontier_WinRewardCaseFull MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenu

@ Offer to continue, rest, or abandon (can't press B to choose)
@ This handles special text for Ace / Brain battles
BattleFrontier_Common_ChallengeMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_GetNextOpponentKind
    compare LASTRESULT FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_ChallengeMenuAceNext
    compare LASTRESULT FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_ChallengeMenuBrainNext
    msgbox gText_BattleFrontier_ChallengeMenuPrompt MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuAceNext:
    msgbox gText_BattleFrontier_ChallengeMenuPromptAce MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuBrainNext:
    msgbox gText_BattleFrontier_ChallengeMenuPromptBrain MSG_KEEPOPEN
    goto BattleFrontier_Common_ChallengeMenuOptions

BattleFrontier_Common_ChallengeMenuOptions:
    multichoiceoption gText_BattleFrontier_ChoiceContinue 0
    multichoiceoption gText_BattleFrontier_ChoiceRest 1
    multichoiceoption gText_BattleFrontier_ChoiceAbandon 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS TRUE
    switch LASTRESULT
    case 0, BattleFrontier_Common_BattleLoop @ The entered team carries over
    case 1, BattleFrontier_Common_Rest
    case 2, BattleFrontier_Common_ConfirmAbandon
    goto BattleFrontier_Common_ChallengeMenu

@ ============================================================================
@ Runs left on hold
@ ============================================================================

@ Only hit when choosing a paused run. Player can still choose to cancel out without losing their streak
BattleFrontier_Common_RunOnHold:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_WelcomeBackRested MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenu

@ Warned about the same way as the mid-run menu. The streak is whatever Rest left behind and the
@ facility vars naming the run are already loaded by BattleFrontier_Common_FormatChosen, so the
@ lookahead reads the held run rather than a stale one.
BattleFrontier_Common_OnHoldMenu:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_GetNextOpponentKind
    compare LASTRESULT FRONTIER_OPPONENT_ACE
    if equal _goto BattleFrontier_Common_OnHoldMenuSpecialNext
    compare LASTRESULT FRONTIER_OPPONENT_BRAIN
    if equal _goto BattleFrontier_Common_OnHoldMenuBrainNext
    msgbox gText_BattleFrontier_OnHoldMenuPrompt MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuSpecialNext:
    msgbox gText_BattleFrontier_OnHoldMenuPromptSpecial MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuBrainNext:
    msgbox gText_BattleFrontier_OnHoldMenuPromptBrain MSG_KEEPOPEN
    goto BattleFrontier_Common_OnHoldMenuOptions

BattleFrontier_Common_OnHoldMenuOptions:
    multichoiceoption gText_BattleFrontier_ChoiceContinue 0
    multichoiceoption gText_BattleFrontier_ChoiceAbandon 1
    multichoiceoption gText_BattleFrontier_ChoiceKeepOnHold 2
    multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
    switch LASTRESULT
    case 0, BattleFrontier_Common_ResumeRun
    case 1, BattleFrontier_Common_ConfirmAbandonOnHold
    goto BattleFrontier_Common_LobbyMenu

@ Reminder: The player can leave and return with a different team, so we handle
@ party selection as though it were their first run
BattleFrontier_Common_ResumeRun:
    callasm FrontierChallenge_BufferFacilityInfo
    callasm FrontierChallenge_BufferNumMonsToEnter
    call BattleFrontier_Common_EnterTeam
    compare LASTRESULT FALSE
    if equal _goto BattleFrontier_Common_OnHoldMenu
    goto BattleFrontier_Common_StartRun

@ When resting, the streak is saved and game modifiers are restored. The player
@ can choose to go to any other facility or just explore without losing their streak
BattleFrontier_Common_Rest:
    msgbox gText_BattleFrontier_ConfirmRest MSG_YESNO
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_ChallengeMenu
    special SPECIAL_LOAD_PLAYER_PARTY
    callasm FrontierChallenge_SetResting
    @ Before the save, or the facility state would be on disk as well as in RAM.
    callasm FrontierChallenge_ClearFacilityVars
    msgbox gText_BattleFrontier_Resting MSG_KEEPOPEN
    callasm FrontierChallenge_ForceSave
    waitstate
    goto BattleFrontier_Common_Exit

@ ============================================================================
@ Giving up and losing
@ ============================================================================

BattleFrontier_Common_ConfirmAbandon:
    call BattleFrontier_Common_AskAbandon
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_ChallengeMenu
    call BattleFrontier_Common_EndLiveRun
    goto BattleFrontier_Common_Abandoned

BattleFrontier_Common_ConfirmAbandonOnHold:
    call BattleFrontier_Common_AskAbandon
    compare LASTRESULT NO
    if equal _goto BattleFrontier_Common_OnHoldMenu
    call BattleFrontier_Common_EndRunOnHold
    goto BattleFrontier_Common_Abandoned

BattleFrontier_Common_AskAbandon:
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_ConfirmAbandon MSG_YESNO
    return

BattleFrontier_Common_Abandoned:
    msgbox gText_BattleFrontier_Abandoned MSG_KEEPOPEN
    goto BattleFrontier_Common_Exit

BattleFrontier_Common_Loss:
    call BattleFrontier_Common_EndLiveRun
    callasm FrontierChallenge_BufferFacilityInfo
    msgbox gText_BattleFrontier_Lost MSG_KEEPOPEN
    goto BattleFrontier_Common_Exit

@ Losing and giving up mid-run end in exactly the same state. The team the player entered
@ with is still live in gPlayerParty on this path, so their real party has to come back.
BattleFrontier_Common_EndLiveRun:
    setvar 0x8000 STREAK_RESET
    special SPECIAL_UPDATE_FACILITY_STREAK
    special SPECIAL_LOAD_PLAYER_PARTY
    callasm FrontierChallenge_End
    return

@ Giving up on a held run instead. No entered team is live, and the player's party must be
@ left alone - special 0x28 would overwrite it with SaveBlock1.playerParty, which tracks the
@ player's last save and by now can be well behind the team they're carrying.
BattleFrontier_Common_EndRunOnHold:
    setvar 0x8000 STREAK_RESET
    special SPECIAL_UPDATE_FACILITY_STREAK
    callasm FrontierChallenge_End
    return

.align 1
