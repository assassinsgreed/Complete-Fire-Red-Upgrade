.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

// Common
.global SignScript_AnthraTown_GameModifiersPC
SignScript_AnthraTown_GameModifiersPC:
	lock
	sound 0x4 @Log on SE
	setmaptile 0x1 0x1 0x28A 0x1 @ PC On, impassable
	special 0x8E @ Refresh map tiles
	callasm ComputeCompletedGameModifierRequirements
	msgboxsign
	msgbox gText_GameModifiers_BootingUpPC MSG_NORMAL
	goto ChoosingModifier

ChoosingModifier:
	msgbox gText_GameModifiers_ChooseAModifierPrompt MSG_KEEPOPEN
	setvar 0x8000 0x12 @ Game Modifiers
    setvar 0x8001 0x8 @ Show 8 at a time
    setvar 0x8004 0x0
	special 0x158
    waitstate
	copyvar 0x4000 LASTRESULT
    switch 0x4000
	case 0, GameModifiers_RandomizerSpecies
	case 1, GameModifiers_RandomizerMovesets
	case 2, GameModifiers_RandomizerAbilities
	case 3, GameModifiers_InverseBattles
	case 4, GameModifiers_CamomonBattles
	case 5, GameModifiers_DoubleBattles
	case 6, GameModifiers_GuaranteedCaptures
	case 7, GameModifiers_CatchTrainerPokemon
	case 8, GameModifiers_ScaleWildPokemon
	case 9, GameModifiers_ScaleTrainerPokemon
	case 10, GameModifiers_HiddenAbilities
	case 11, GameModifiers_Shinies
	case 12, GameModifiers_MoveReminderAllMoves
	case 13, GameModifiers_KeepHeldConsumables
	case 14, GameModifiers_DexNavShowAll
	case 15, GameModifiers_InstantBattleWeather
	case 16, GameModifiers_InstantBattleTerrain
	case 17, GameModifiers_InstantFriendship
	case 18, GameModifiers_PerfectWildIVs
	case 19, GameModifiers_EVIVViewer
	case 20, GameModifiers_RepeatedMegaEvolution
	case 21, GameModifiers_DivergentToggle
	case 0x7F, GameModifiers_End @ When player hits B to close
	goto GameModifiers_End

EnterUnlockPassword:
	setvar 0x8000 0x1 @ Prompt is "Enter Password"
    special 0x12C @ Prompt for entry
    waitstate
	return

@ Switch command not used, because choosing a modifier with multiple states (such as species randomization or permanent weather) will override var 0x4000's internal value, resulting in other modifiers being changed without warning.
GameModifiers_PromptToTurnOff:
	msgbox gText_GameModifiers_TurnOffPrompt MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	compare 0x4000 0
	if equal _call GameModifiers_RandomizerSpecies_ClearModifier
	compare 0x4000 1
	if equal _call GameModifiers_RandomizerMovesets_ClearModifier
	compare 0x4000 2
	if equal _call GameModifiers_RandomizerAbilities_ClearModifier
	compare 0x4000 3
	if equal _call GameModifiers_InverseBattles_ClearModifier
	compare 0x4000 4
	if equal _call GameModifiers_CamomonBattles_ClearModifier
	compare 0x4000 5
	if equal _call GameModifiers_DoubleBattles_ClearModifier
	compare 0x4000 6
	if equal _call GameModifiers_GuaranteedCaptures_ClearModifier
	compare 0x4000 7
	if equal _call GameModifiers_CatchTrainerPokemon_ClearModifier
	compare 0x4000 8
	if equal _call GameModifiers_ScaleWildPokemon_ClearModifier
	compare 0x4000 9
	if equal _call GameModifiers_ScaleTrainerPokemon_ClearModifier
	compare 0x4000 10
	if equal _call GameModifiers_HiddenAbilities_ClearModifier
	compare 0x4000 11
	if equal _call GameModifiers_Shinies_ClearModifier
	compare 0x4000 12
	if equal _call GameModifiers_MoveReminderAllMoves_ClearModifier
	compare 0x4000 13
	if equal _call GameModifiers_KeepHeldConsumables_ClearModifier
	compare 0x4000 14
	if equal _call GameModifiers_DexNavShowAll_ClearModifier
	compare 0x4000 15
	if equal _call GameModifiers_InstantBattleWeather_ClearModifier
	compare 0x4000 16
	if equal _call GameModifiers_InstantBattleTerrain_ClearModifier
	compare 0x4000 17
	if equal _call GameModifiers_InstantFriendship_ClearModifier
	compare 0x4000 18
	if equal _call GameModifiers_PerfectWildIVs_ClearModifier
	compare 0x4000 19
	if equal _call GameModifiers_EVIVViewer_ClearModifier
	compare 0x4000 20
	if equal _call GameModifiers_RepeatedMegaEvolution_ClearModifier
	compare 0x4000 21
	if equal _call GameModifiers_DivergentToggle_ClearModifier
	playse 0x30 @ Save
	msgbox gText_GameModifiers_ModifierNowOff MSG_NORMAL
	goto ChoosingModifier

@ Switch command not used, because choosing a modifier with multiple states (such as species randomization or permanent weather) will override var 0x4000's internal value, resulting in other modifiers being changed without warning.
GameModifiers_PromptToTurnOn:
	msgbox gText_GameModifiers_TurnOnPrompt MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	compare 0x4000 0
	if equal _call GameModifiers_RandomizerSpecies_SetModifier
	compare 0x4000 1
	if equal _call GameModifiers_RandomizerMovesets_SetModifier
	compare 0x4000 2
	if equal _call GameModifiers_RandomizerAbilities_SetModifier
	compare 0x4000 3
	if equal _call GameModifiers_InverseBattles_SetModifier
	compare 0x4000 4
	if equal _call GameModifiers_CamomonBattles_SetModifier
	compare 0x4000 5
	if equal _call GameModifiers_DoubleBattles_SetModifier
	compare 0x4000 6
	if equal _call GameModifiers_GuaranteedCaptures_SetModifier
	compare 0x4000 7
	if equal _call GameModifiers_CatchTrainerPokemon_SetModifier
	compare 0x4000 8
	if equal _call GameModifiers_ScaleWildPokemon_SetModifier
	compare 0x4000 9
	if equal _call GameModifiers_ScaleTrainerPokemon_SetModifier
	compare 0x4000 10
	if equal _call GameModifiers_HiddenAbilities_SetModifier
	compare 0x4000 11
	if equal _call GameModifiers_Shinies_SetModifier
	compare 0x4000 12
	if equal _call GameModifiers_MoveReminderAllMoves_SetModifier
	compare 0x4000 13
	if equal _call GameModifiers_KeepHeldConsumables_SetModifier
	compare 0x4000 14
	if equal _call GameModifiers_DexNavShowAll_SetModifier
	compare 0x4000 15
	if equal _call GameModifiers_InstantBattleWeather_SetModifier
	compare 0x4000 16
	if equal _call GameModifiers_InstantBattleTerrain_SetModifier
	compare 0x4000 17
	if equal _call GameModifiers_InstantFriendship_SetModifier
	compare 0x4000 18
	if equal _call GameModifiers_PerfectWildIVs_SetModifier
	compare 0x4000 19
	if equal _call GameModifiers_EVIVViewer_SetModifier
	compare 0x4000 20
	if equal _call GameModifiers_RepeatedMegaEvolution_SetModifier
	compare 0x4000 21
	if equal _call GameModifiers_DivergentToggle_SetModifier
	playse 0x30 @ Save
	msgbox gText_GameModifiers_ModifierNowOn MSG_NORMAL
	goto ChoosingModifier

GameModifiers_End:
	sound 0x3 @Log off SE
	setmaptile 0x1 0x1 0x288 0x1 @ PC Off, impassable
	special 0x8E @ Refresh map tiles
	msgbox gText_GameModifiers_LoggingOff MSG_KEEPOPEN
	msgboxnormal
	release
	end



// Modifiers
GameModifiers_RandomizerSpecies:
	msgbox gText_GameModifiers_RandomizerSpecies_Description MSG_NORMAL
	msgbox gText_GameModifiers_RandomizerCommon_Details MSG_NORMAL
	checkflag 0xAF @ Randomizer Species modifier unlocked
	if NOT_SET _goto GameModifiers_RandomizerSpecies_NotUnlocked
	msgbox gText_GameModifiers_RandomizerSpecies_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_RandomizerSpecies_TogglePrompt

GameModifiers_RandomizerSpecies_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteThePokedex MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_RandomizerSpecies_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_RandomizerSpecies_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_RandomizerSpecies_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xAF @ Randomizer Species modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_RandomizerSpecies_TogglePrompt

GameModifiers_RandomizerSpecies_TogglePrompt:
	checkflag 0x940 @ Randomizer Species active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_RandomizerMovesets:
	msgbox gText_GameModifiers_RandomizerMovesets_Description MSG_NORMAL
	msgbox gText_GameModifiers_RandomizerCommon_Details MSG_NORMAL
	checkflag 0xBF @ Randomizer Movesets modifier unlocked
	if NOT_SET _goto GameModifiers_RandomizerMovesets_NotUnlocked
	msgbox gText_GameModifiers_RandomizerMovesets_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_RandomizerMovesets_TogglePrompt

GameModifiers_RandomizerMovesets_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteThePokedex MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_RandomizerMovesets_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_RandomizerMovesets_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_RandomizerMovesets_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBF @ Randomizer Movesets modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_RandomizerMovesets_TogglePrompt

GameModifiers_RandomizerMovesets_TogglePrompt:
	checkflag 0x941 @ Randomizer Movesets active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_RandomizerAbilities:
	msgbox gText_GameModifiers_RandomizerAbilities_Description MSG_NORMAL
	msgbox gText_GameModifiers_RandomizerCommon_Details MSG_NORMAL
	checkflag 0xC0 @ Randomizer Abilities modifier unlocked
	if NOT_SET _goto GameModifiers_RandomizerAbilities_NotUnlocked
	msgbox gText_GameModifiers_RandomizerAbilities_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_RandomizerAbilities_TogglePrompt

GameModifiers_RandomizerAbilities_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteThePokedex MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_RandomizerAbilities_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_RandomizerAbilities_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_RandomizerAbilities_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xC0 @ Randomizer Abilities modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_RandomizerAbilities_TogglePrompt

GameModifiers_RandomizerAbilities_TogglePrompt:
	checkflag 0x942 @ Randomizer Abilities active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_InverseBattles:
	msgbox gText_GameModifiers_InverseBattles_Description MSG_NORMAL
	checkflag 0xB0 @ Inverse Battles modifier unlocked
	if NOT_SET _goto GameModifiers_InverseBattles_NotUnlocked
	msgbox gText_GameModifiers_InverseBattles_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_InverseBattles_TogglePrompt

GameModifiers_InverseBattles_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllTrainerHouses MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_InverseBattles_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_InverseBattles_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_InverseBattles_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB0 @ Inverse Battles modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_InverseBattles_TogglePrompt

GameModifiers_InverseBattles_TogglePrompt:
	checkflag 0x900 @ Inverse battles active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_CamomonBattles:
	msgbox gText_GameModifiers_CamomonBattles_Description MSG_NORMAL
	checkflag 0xB0 @ Camomon Battles modifier unlocked
	if NOT_SET _goto GameModifiers_CamomonBattles_NotUnlocked
	msgbox gText_GameModifiers_CamomonBattles_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_CamomonBattles_TogglePrompt

GameModifiers_CamomonBattles_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllTrainerHouses MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_CamomonBattles_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_CamomonBattles_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_CamomonBattles_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB0 @ Camomon Battles modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_CamomonBattles_TogglePrompt

GameModifiers_CamomonBattles_TogglePrompt:
	checkflag 0x92C @ Camomon Battles active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_DoubleBattles:
	msgbox gText_GameModifiers_DoubleBattles_Description MSG_NORMAL
	checkflag 0xB2 @ Double Battles modifier unlocked
	if NOT_SET _goto GameModifiers_DoubleBattles_NotUnlocked
	msgbox gText_GameModifiers_DoubleBattles_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_DoubleBattles_TogglePrompt

GameModifiers_DoubleBattles_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllTrainerHouses MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_DoubleBattles_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_DoubleBattles_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_DoubleBattles_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB2 @ Double Battles modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_DoubleBattles_TogglePrompt

GameModifiers_DoubleBattles_TogglePrompt:
	checkflag 0x907 @ Double Battles active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_GuaranteedCaptures:
	msgbox gText_GameModifiers_GuaranteedCaptures_Description MSG_NORMAL
	checkflag 0xB3 @ Guaranteed Captures modifier unlocked
	if NOT_SET _goto GameModifiers_GuaranteedCaptures_NotUnlocked
	msgbox gText_GameModifiers_GuaranteedCaptures_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_GuaranteedCaptures_TogglePrompt

GameModifiers_GuaranteedCaptures_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteThePokedex MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_GuaranteedCaptures_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_GuaranteedCaptures_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_GuaranteedCaptures_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB3 @ Guaranteed Captures modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_GuaranteedCaptures_TogglePrompt

GameModifiers_GuaranteedCaptures_TogglePrompt:
	checkflag 0x92F @ Guaranteed Captures active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_CatchTrainerPokemon:
	msgbox gText_GameModifiers_CatchTrainerPokemon_Description MSG_NORMAL
	checkflag 0xB4 @ Catch Trainer Pokemon modifier unlocked
	if NOT_SET _goto GameModifiers_CatchTrainerPokemon_NotUnlocked
	msgbox gText_GameModifiers_CatchTrainerPokemon_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_CatchTrainerPokemon_TogglePrompt

GameModifiers_CatchTrainerPokemon_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_DefeatKurtis MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_CatchTrainerPokemon_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_CatchTrainerPokemon_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_CatchTrainerPokemon_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB4 @ Catch Trainer Pokemon modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_CatchTrainerPokemon_TogglePrompt

GameModifiers_CatchTrainerPokemon_TogglePrompt:
	checkflag 0x905 @ Catch Trainer Pokemon active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_ScaleWildPokemon:
	msgbox gText_GameModifiers_ScaleWildPokemon_Description MSG_NORMAL
	checkflag 0xB5 @ Scale Wild Pokemon modifier unlocked
	if NOT_SET _goto GameModifiers_ScaleWildPokemon_NotUnlocked
	msgbox gText_GameModifiers_ScaleWildPokemon_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_ScaleWildPokemon_TogglePrompt

GameModifiers_ScaleWildPokemon_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CatchAllLegendaries MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_ScaleWildPokemon_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_ScaleWildPokemon_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_ScaleWildPokemon_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB5 @ Scale Wild Pokemon modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_ScaleWildPokemon_TogglePrompt

GameModifiers_ScaleWildPokemon_TogglePrompt:
	checkflag 0x90D @ Scale Wild Pokemon active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_ScaleTrainerPokemon:
	msgbox gText_GameModifiers_ScaleTrainerPokemon_Description MSG_NORMAL
	checkflag 0xB6 @ Scale Trainer Pokemon modifier unlocked
	if NOT_SET _goto GameModifiers_ScaleTrainerPokemon_NotUnlocked
	msgbox gText_GameModifiers_ScaleTrainerPokemon_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_ScaleTrainerPokemon_TogglePrompt

GameModifiers_ScaleTrainerPokemon_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_ChampionDefense MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_ScaleTrainerPokemon_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_ScaleTrainerPokemon_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_ScaleTrainerPokemon_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB6 @ Scale Trainer Pokemon modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_ScaleTrainerPokemon_TogglePrompt

GameModifiers_ScaleTrainerPokemon_TogglePrompt:
	checkflag 0x90E @ Scale Trainer Pokemon active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_HiddenAbilities:
	msgbox gText_GameModifiers_HiddenAbilities_Description MSG_NORMAL
	checkflag 0xB7 @ Hidden Abilities modifier unlocked
	if NOT_SET _goto GameModifiers_HiddenAbilities_NotUnlocked
	msgbox gText_GameModifiers_HiddenAbilities_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_HiddenAbilities_TogglePrompt

GameModifiers_HiddenAbilities_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_GymLeaderRematches MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_HiddenAbilities_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_HiddenAbilities_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_HiddenAbilities_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB7 @ Hidden Abilities modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_HiddenAbilities_TogglePrompt

GameModifiers_HiddenAbilities_TogglePrompt:
	checkflag 0x90F @ Hidden Abilities active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_Shinies:
	msgbox gText_GameModifiers_Shinies_Description MSG_NORMAL
	checkflag 0xB8 @ Shiny wild pokemon modifier unlocked
	if NOT_SET _goto GameModifiers_Shinies_NotUnlocked
	msgbox gText_GameModifiers_Shinies_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_Shinies_TogglePrompt

GameModifiers_Shinies_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteThePokedex MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_Shinies_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_Shinies_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_Shinies_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB8 @ Shiny wild pokemon modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_Shinies_TogglePrompt

GameModifiers_Shinies_TogglePrompt:
	checkflag 0x931 @ Shiny wild pokemon active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_MoveReminderAllMoves:
	msgbox gText_GameModifiers_MoveReminderAllMoves_Description MSG_NORMAL
	checkflag 0xB9 @ Move Reminder All Moves modifier unlocked
	if NOT_SET _goto GameModifiers_MoveReminderAllMoves_NotUnlocked
	msgbox gText_GameModifiers_MoveReminderAllMoves_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_MoveReminderAllMoves_TogglePrompt

GameModifiers_MoveReminderAllMoves_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_LevelOneHundred MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_MoveReminderAllMoves_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_MoveReminderAllMoves_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_MoveReminderAllMoves_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xB9 @ Move Reminder All Moves modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_MoveReminderAllMoves_TogglePrompt

GameModifiers_MoveReminderAllMoves_TogglePrompt:
	checkflag 0x916 @ Move Reminder All Moves active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_KeepHeldConsumables:
	msgbox gText_GameModifiers_KeepHeldConsumables_Description MSG_NORMAL
	checkflag 0xBA @ Keep Held Consumables modifier unlocked
	if NOT_SET _goto GameModifiers_KeepHeldConsumables_NotUnlocked
	msgbox gText_GameModifiers_KeepHeldConsumables_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_KeepHeldConsumables_TogglePrompt

GameModifiers_KeepHeldConsumables_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllTMsAndHMs MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_KeepHeldConsumables_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_KeepHeldConsumables_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_KeepHeldConsumables_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBA @ Keep Held Consumables modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_KeepHeldConsumables_TogglePrompt

GameModifiers_KeepHeldConsumables_TogglePrompt:
	checkflag 0x927 @ Keep Held Consumables active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_DexNavShowAll:
	msgbox gText_GameModifiers_DexNavShowAll_Description MSG_NORMAL
	checkflag 0xBB @ Dex Nav Show All modifier unlocked
	if NOT_SET _goto GameModifiers_DexNavShowAll_NotUnlocked
	msgbox gText_GameModifiers_DexNavShowAll_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_DexNavShowAll_TogglePrompt

GameModifiers_DexNavShowAll_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_3OrMoreLevel25DexNavSearches MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_DexNavShowAll_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_DexNavShowAll_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_DexNavShowAll_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBB @ Dex Nav Show All modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_DexNavShowAll_TogglePrompt

GameModifiers_DexNavShowAll_TogglePrompt:
	checkflag 0x932 @ Dex Nav Show All active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_InstantBattleWeather:
	msgbox gText_GameModifiers_InstantBattleWeather_Description MSG_NORMAL
	checkflag 0xBC @ Instant Battle Weather modifier unlocked
	if NOT_SET _goto GameModifiers_InstantBattleWeather_NotUnlocked
	msgbox gText_GameModifiers_InstantBattleWeather_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_InstantBattleWeather_TogglePrompt

GameModifiers_InstantBattleWeather_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_BattleBondGreninja MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_InstantBattleWeather_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_InstantBattleWeather_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_InstantBattleWeather_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBC @ Instant Battle Weather modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_InstantBattleWeather_TogglePrompt

GameModifiers_InstantBattleWeather_TogglePrompt:
	compare 0x40AC 0x0 @ Instant Battle Weather active
	if greaterthan _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_InstantBattleTerrain:
	msgbox gText_GameModifiers_InstantBattleTerrain_Description MSG_NORMAL
	checkflag 0xBD @ Instant Battle Terrain modifier unlocked
	if NOT_SET _goto GameModifiers_InstantBattleTerrain_NotUnlocked
	msgbox gText_GameModifiers_InstantBattleTerrain_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_InstantBattleTerrain_TogglePrompt

GameModifiers_InstantBattleTerrain_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllUteyanRuinPuzzles MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_InstantBattleTerrain_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_InstantBattleTerrain_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_InstantBattleTerrain_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBD @ Instant Battle Terrain modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_InstantBattleTerrain_TogglePrompt

GameModifiers_InstantBattleTerrain_TogglePrompt:
	compare 0x40AD 0x0 @ Instant Battle Terrain active
	if greaterthan _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_InstantFriendship:
	msgbox gText_GameModifiers_InstantFriendship_Description MSG_NORMAL
	checkflag 0xBE @ Instant Friendship modifier unlocked
	if NOT_SET _goto GameModifiers_InstantFriendship_NotUnlocked
	msgbox gText_GameModifiers_InstantFriendship_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_InstantFriendship_TogglePrompt

GameModifiers_InstantFriendship_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_CompleteUltraSpaceEpisode MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_InstantFriendship_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_InstantFriendship_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_InstantFriendship_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0xBE @ Instant Friendship modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_InstantFriendship_TogglePrompt

GameModifiers_InstantFriendship_TogglePrompt:
	checkflag 0x943 @ Instant Friendship active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_PerfectWildIVs:
	msgbox gText_GameModifiers_PerfectWildIVs_Description MSG_NORMAL
	checkflag 0x0C3 @ Perfect Wild IVs game modifier unlocked
	if NOT_SET _goto GameModifiers_PerfectWildIVs_NotUnlocked
	msgbox gText_GameModifiers_PerfectWildIVs_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_PerfectWildIVs_TogglePrompt

GameModifiers_PerfectWildIVs_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_BattleFacilityStreak MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_PerfectWildIVs_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_PerfectWildIVs_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_PerfectWildIVs_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0x0C3 @ Perfect Wild IVs game modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_PerfectWildIVs_TogglePrompt

GameModifiers_PerfectWildIVs_TogglePrompt:
	checkflag 0x94A @ Perfect Wild IVs active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_EVIVViewer:
	msgbox gText_GameModifiers_EVIVViewer_Description MSG_NORMAL
	checkflag 0x0C1 @ EV/IV Viewer game modifier unlocked
	if NOT_SET _goto GameModifiers_EVIVViewer_NotUnlocked
	msgbox gText_GameModifiers_EVIVViewer_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_EVIVViewer_TogglePrompt

GameModifiers_EVIVViewer_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_150IVPokemon MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_EVIVViewer_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_EVIVViewer_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_EVIVViewer_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0x0C1 @ EV/IV Viewer modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_EVIVViewer_TogglePrompt

GameModifiers_EVIVViewer_TogglePrompt:
	checkflag 0x944 @ EV/IV Viewer active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_RepeatedMegaEvolution:
	msgbox gText_GameModifiers_RepeatedMegaEvolution_Description MSG_NORMAL
	checkflag 0x0C4 @ Repeated Mega Evolution game modifier unlocked
	if NOT_SET _goto GameModifiers_RepeatedMegaEvolution_NotUnlocked
	msgbox gText_GameModifiers_RepeatedMegaEvolution_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_RepeatedMegaEvolution_TogglePrompt

GameModifiers_RepeatedMegaEvolution_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_AllMegaStones MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_RepeatedMegaEvolution_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_RepeatedMegaEvolution_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_RepeatedMegaEvolution_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0x0C4 @ Repeated Mega Evolution game modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_RepeatedMegaEvolution_TogglePrompt

GameModifiers_RepeatedMegaEvolution_TogglePrompt:
	checkflag 0x94B @ Repeated Mega Evolution active
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

GameModifiers_DivergentToggle:
	msgbox gText_GameModifiers_DivergentToggle_Description MSG_NORMAL
	checkflag 0x0C2 @ Divergent toggle game modifier unlocked
	if NOT_SET _goto GameModifiers_DivergentToggle_NotUnlocked
	msgbox gText_GameModifiers_DivergentToggle_PasswordDeclaration MSG_NORMAL
	goto GameModifiers_DivergentToggle_TogglePrompt

GameModifiers_DivergentToggle_NotUnlocked:
	msgbox gText_GameModifiers_UnlockCriteria_SwarmingPokemon MSG_NORMAL
	msgbox gText_GameModifiers_ModifierNotYetAchieved MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	call EnterUnlockPassword
	loadpointer 0x0 gText_GameModifiers_DivergentToggle_Password
    special 0x12D
    compare LASTRESULT 0x0
    if equal _goto GameModifiers_DivergentToggle_UnlockedWithPassword
	playse 0x1A @ Error
    msgbox gText_GameModifiers_PasswordIncorrect MSG_NORMAL
	goto ChoosingModifier

GameModifiers_DivergentToggle_UnlockedWithPassword:
	playse 0x19 @ Correct
	setflag 0x0C2 @ Divergent Toggle game modifier unlocked
	msgbox gText_GameModifiers_PasswordCorrect MSG_NORMAL
	goto GameModifiers_DivergentToggle_TogglePrompt

GameModifiers_DivergentToggle_TogglePrompt:
	checkflag 0x946 @ Divergent Toggle active in options menu
	if SET _goto GameModifiers_PromptToTurnOff
	goto GameModifiers_PromptToTurnOn

// Set / Clear functions
GameModifiers_RandomizerSpecies_SetModifier:
	msgbox gText_GameModifiers_RandomizerSpecies_RandomizationQuestion MSG_KEEPOPEN
	multichoiceoption gText_GameModifiers_RandomizerSpecies_Kulure 0
	multichoiceoption gText_GameModifiers_RandomizerSpecies_AllGens 1
	multichoiceoption gText_GameModifiers_Common_Cancel 2
	multichoice 0x0 0x0 THREE_MULTICHOICE_OPTIONS FALSE
	switch LASTRESULT
	case 0, GameModifiers_RandomizerSpecies_Kulure_SetModifier _call
	case 1, GameModifiers_RandomizerSpecies_AllGens_SetModifier _call
	case 2, ChoosingModifier _goto
	case 0x7F, ChoosingModifier _goto
	clearflag 0x930 @ Hack: turn off the battle facility (which disables randomizer)
	return

GameModifiers_RandomizerSpecies_Kulure_SetModifier:
	setflag 0x940 @ Turn on Randomizer Species
	setflag 0x933 @ Randomize in Kulure dex only
	return

GameModifiers_RandomizerSpecies_AllGens_SetModifier:
	setflag 0x940 @ Turn on Randomizer Species
	clearflag 0x933 @ Randomize across all gens
	return

GameModifiers_RandomizerSpecies_ClearModifier:
	clearflag 0x940 @ Turn off Randomizer Species
	clearflag 0x933 @ Turn off Kulure-specific randomization
	return

GameModifiers_RandomizerMovesets_SetModifier:
	setflag 0x941 @ Turn on Randomizer Movesets
	return

GameModifiers_RandomizerMovesets_ClearModifier:
	clearflag 0x941 @ Turn off Randomizer Movesets
	return

GameModifiers_RandomizerAbilities_SetModifier:
	setflag 0x942 @ Turn on Randomizer Abilities
	return

GameModifiers_RandomizerAbilities_ClearModifier:
	clearflag 0x942 @ Turn off Randomizer Abilities
	return

GameModifiers_InverseBattles_SetModifier:
	setflag 0x900 @ Turn on inverse
	setflag 0x151 @ Do not turn off inverse battles in trainer houses
	return

GameModifiers_InverseBattles_ClearModifier:
	clearflag 0x900 @ Turn off inverse
	clearflag 0x151 @ Do not turn off inverse battles in trainer houses
	return

GameModifiers_CamomonBattles_SetModifier:
	setflag 0x92C @ Turn on Camomon Battles
	setflag 0x152 @ Do not turn off camomon battles in trainer houses
	return

GameModifiers_CamomonBattles_ClearModifier:
	clearflag 0x92C @ Turn off Camomon Battles
	clearflag 0x152 @ Do not turn off camomon battles in trainer houses
	return

GameModifiers_DoubleBattles_SetModifier:
	setflag 0x907 @ Turn on Trainer Double Battles
	setflag 0x910 @ Turn on Wild Double Battles
	setflag 0x934 @ Double battles modifier active
	return

GameModifiers_DoubleBattles_ClearModifier:
	clearflag 0x907 @ Turn off Double Battles
	clearflag 0x910 @ Turn off Wild Double Battles
	clearflag 0x934 @ Double battles modifier active
	return

GameModifiers_GuaranteedCaptures_SetModifier:
	setflag 0x92F @ Turn on Guaranteed Captures
	return

GameModifiers_GuaranteedCaptures_ClearModifier:
	clearflag 0x92F @ Turn off Guaranteed Captures
	return

GameModifiers_CatchTrainerPokemon_SetModifier:
	setflag 0x905 @ Turn on Catch Trainer Pokemon
	return

GameModifiers_CatchTrainerPokemon_ClearModifier:
	clearflag 0x905 @ Turn off Catch Trainer Pokemon
	return

GameModifiers_ScaleWildPokemon_SetModifier:
	setflag 0x90D @ Turn on Scale Wild Pokemon
	return

GameModifiers_ScaleWildPokemon_ClearModifier:
	clearflag 0x90D @ Turn off Scale Wild Pokemon
	return

GameModifiers_ScaleTrainerPokemon_SetModifier:
	setflag 0x90E @ Turn on Scale Trainer Pokemon
	setflag 0x93F @ Do not turn off scaling after battles
	return

GameModifiers_ScaleTrainerPokemon_ClearModifier:
	clearflag 0x90E @ Turn off Scale Trainer Pokemon
	clearflag 0x93F @ Scaling can be turned off after certain battles again
	return

GameModifiers_HiddenAbilities_SetModifier:
	setflag 0x90F @ Turn on Hidden Abilities
	return

GameModifiers_HiddenAbilities_ClearModifier:
	clearflag 0x90F @ Turn off Hidden Abilities
	return

GameModifiers_Shinies_SetModifier:
	setflag 0x913 @ Turn on Shiny wild pokemon
	setflag 0x931 @ Do not cause the modifier to be disabled after battle
	return

GameModifiers_Shinies_ClearModifier:
	clearflag 0x913 @ Turn off Shiny wild pokemon
	clearflag 0x931 @ Cause the modifier to be disabled after battle
	return

GameModifiers_MoveReminderAllMoves_SetModifier:
	setflag 0x916 @ Turn on Move Reminder All Moves
	return

GameModifiers_MoveReminderAllMoves_ClearModifier:
	clearflag 0x916 @ Turn off Move Reminder All Moves
	return

GameModifiers_KeepHeldConsumables_SetModifier:
	setflag 0x927 @ Turn on Keep Held Consumables
	return

GameModifiers_KeepHeldConsumables_ClearModifier:
	clearflag 0x927 @ Turn off Keep Held Consumables
	return

GameModifiers_DexNavShowAll_SetModifier:
	setflag 0x932 @ Turn on Dex Nav Show All
	return

GameModifiers_DexNavShowAll_ClearModifier:
	clearflag 0x932 @ Turn off Dex Nav Show All
	return

GameModifiers_InstantBattleWeather_SetModifier:
	msgbox gText_GameModifiers_InstantBattleWeather_ChosenWeatherChoice MSG_KEEPOPEN
	multichoiceoption gText_GameModifiers_InstantBattleWeather_Sun 0
	multichoiceoption gText_GameModifiers_InstantBattleWeather_Rain 1
	multichoiceoption gText_GameModifiers_InstantBattleWeather_Sandstorm 2
	multichoiceoption gText_GameModifiers_InstantBattleWeather_Hail 3
	multichoiceoption gText_GameModifiers_InstantBattleWeather_Fog 4
	multichoiceoption gText_GameModifiers_Common_Cancel 5
	multichoice 0x0 0x0 SIX_MULTICHOICE_OPTIONS FALSE
	compare LASTRESULT 5
	if greaterorequal _goto ChoosingModifier
	copyvar 0x40AC LASTRESULT @ Do not directly use LASTRESULT as it will break
	addvar 0x40AC 1 @ To get correct weather index
	return

GameModifiers_InstantBattleWeather_ClearModifier:
	setvar 0x40AC 0 @ Turn off Instant Battle Weather
	return

GameModifiers_InstantBattleTerrain_SetModifier:
	msgbox gText_GameModifiers_InstantBattleTerrain_ChosenTerrainChoice MSG_KEEPOPEN
	multichoiceoption gText_ElectricTerrain 0
	multichoiceoption gText_GrassyTerrain 1
	multichoiceoption gText_MistyTerrain 2
	multichoiceoption gText_PsychicTerrain 3
	multichoiceoption gText_GameModifiers_Common_Cancel 4
	multichoice 0x0 0x0 FIVE_MULTICHOICE_OPTIONS FALSE
	compare LASTRESULT 4
	if greaterorequal _goto ChoosingModifier
	copyvar 0x40AD LASTRESULT @ Store into the terrain var
	addvar 0x40AD 1 @ To get correct terrain index
	return

GameModifiers_InstantBattleTerrain_ClearModifier:
	setvar 0x40AD 0 @ Turn off Instant Battle Terrain
	return

GameModifiers_InstantFriendship_SetModifier:
	setflag 0x943 @ Turn on Instant Friendship
	callasm RunOnResumeMapScript @ Set max friendship for any pokemon already in the party
	return

GameModifiers_InstantFriendship_ClearModifier:
	clearflag 0x943 @ Turn off Instant Friendship
	return

GameModifiers_PerfectWildIVs_SetModifier:
	setflag 0x94A @ Turn on Perfect Wild IVs
	return

GameModifiers_PerfectWildIVs_ClearModifier:
	clearflag 0x94A @ Turn off Perfect Wild IVs
	return

GameModifiers_EVIVViewer_SetModifier:
	setflag 0x944 @ Turn on EV/IV Viewer
	return

GameModifiers_EVIVViewer_ClearModifier:
	clearflag 0x944 @ Turn off EV/IV Viewer
	return

GameModifiers_RepeatedMegaEvolution_SetModifier:
	setflag 0x94B @ Turn on Repeated Mega Evolution
	return

GameModifiers_RepeatedMegaEvolution_ClearModifier:
	clearflag 0x94B @ Turn off Repeated Mega Evolution
	return

GameModifiers_DivergentToggle_SetModifier:
	setflag 0x946 @ Turn on Divergent Toggle option in the options menu
	return

GameModifiers_DivergentToggle_ClearModifier:
	clearflag 0x946 @ Turn off Divergent Toggle option in the options menu
	return
