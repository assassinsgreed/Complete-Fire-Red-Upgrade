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
	case 1, GameModifiers_RandomizerMoveset
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
	case 15, GameModifiers_PermanentWeather
	case 16, GameModifiers_PermanentTerrain
	case 0x7F, GameModifiers_End @ When player hits B to close
	goto GameModifiers_End

EnterUnlockPassword:
	setvar 0x8000 0x0 @ Prompt is "Enter Phrase"
    special 0x12C @ Prompt for entry
    waitstate
	return

GameModifiers_PromptToTurnOff:
	msgbox gText_GameModifiers_TurnOffPrompt MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	switch 0x4000
	case 0, GameModifiers_RandomizerSpecies_ClearModifier _call
	@ case 1, GameModifiers_RandomizerMoveset_ClearModifier _call
	@ case 2, GameModifiers_RandomizerAbilities_ClearModifier _call
	case 3, GameModifiers_InverseBattles_ClearModifier _call
	@ case 4, GameModifiers_CamomonBattles_ClearModifier _call
	@ case 5, GameModifiers_DoubleBattles_ClearModifier _call
	@ case 6, GameModifiers_GuaranteedCaptures_ClearModifier _call
	@ case 7, GameModifiers_CatchTrainerPokemon_ClearModifier _call
	@ case 8, GameModifiers_ScaleWildPokemon_ClearModifier _call
	@ case 9, GameModifiers_ScaleTrainerPokemon_ClearModifier _call
	@ case 10, GameModifiers_HiddenAbilities_ClearModifier _call
	@ case 11, GameModifiers_Shinies_ClearModifier _call
	@ case 12, GameModifiers_MoveReminderAllMoves_ClearModifier _call
	@ case 13, GameModifiers_KeepHeldConsumables_ClearModifier _call
	@ case 14, GameModifiers_DexNavShowAll_ClearModifier _call
	@ case 15, GameModifiers_PermanentWeather_ClearModifier _call
	@ case 16, GameModifiers_PermanentTerrain_ClearModifier _call
	playse 0x30 @ Save
	msgbox gText_GameModifiers_ModifierNowOff MSG_NORMAL
	goto ChoosingModifier

GameModifiers_PromptToTurnOn:
	msgbox gText_GameModifiers_TurnOnPrompt MSG_YESNO
	compare LASTRESULT NO
	if equal _goto ChoosingModifier
	switch 0x4000
	case 0, GameModifiers_RandomizerSpecies_SetModifier _call
	@ case 1, GameModifiers_RandomizerMoveset_SetModifier _call
	@ case 2, GameModifiers_RandomizerAbilities_SetModifier _call
	case 3, GameModifiers_InverseBattles_SetModifier _call
	@ case 4, GameModifiers_CamomonBattles_SetModifier _call
	@ case 5, GameModifiers_DoubleBattles_SetModifier _call
	@ case 6, GameModifiers_GuaranteedCaptures_SetModifier _call
	@ case 7, GameModifiers_CatchTrainerPokemon_SetModifier _call
	@ case 8, GameModifiers_ScaleWildPokemon_SetModifier _call
	@ case 9, GameModifiers_ScaleTrainerPokemon_SetModifier _call
	@ case 10, GameModifiers_HiddenAbilities_SetModifier _call
	@ case 11, GameModifiers_Shinies_SetModifier _call
	@ case 12, GameModifiers_MoveReminderAllMoves_SetModifier _call
	@ case 13, GameModifiers_KeepHeldConsumables_SetModifier _call
	@ case 14, GameModifiers_DexNavShowAll_SetModifier _call
	@ case 15, GameModifiers_PermanentWeather_SetModifier _call
	@ case 16, GameModifiers_PermanentTerrain_SetModifier _call
	playse 0x30 @ Save
	msgbox gText_GameModifiers_ModifierNowOn MSG_NORMAL
	goto ChoosingModifier

GameModifiers_End:
	sound 0x3 @Log off SE
	setmaptile 0x1 0x1 0x288 0x1 @ PC Off, impassable
	special 0x8E @ Refresh map tiles
	msgbox gText_GameModifiers_LoggingOff MSG_KEEPOPEN
	release
	end



// Modifiers
GameModifiers_RandomizerSpecies:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_RandomizerMoveset:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_RandomizerAbilities:
	// TODO Later: Implement Something!
	goto ChoosingModifier

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
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_DoubleBattles:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_GuaranteedCaptures:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_CatchTrainerPokemon:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_ScaleWildPokemon:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_ScaleTrainerPokemon:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_HiddenAbilities:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_Shinies:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_MoveReminderAllMoves:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_KeepHeldConsumables:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_DexNavShowAll:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_PermanentWeather:
	// TODO Later: Implement Something!
	goto ChoosingModifier

GameModifiers_PermanentTerrain:
	// TODO Later: Implement Something!
	goto ChoosingModifier



// Set / Clear functions
.global GameModifiers_RandomizerSpecies_SetModifier
GameModifiers_RandomizerSpecies_SetModifier:
	setflag 0x940 @ Turn on randomizer
	clearflag 0x930 @ Hack: turn off the battle facility (which disables randomizer)
	return

.global GameModifiers_RandomizerSpecies_ClearModifier
GameModifiers_RandomizerSpecies_ClearModifier:
	clearflag 0x940 @ Turn off randomizer
	return

.global GameModifiers_InverseBattles_SetModifier
GameModifiers_InverseBattles_SetModifier:
	setflag 0x900 @ Turn on inverse
	setflag 0x151 @ Do not turn off inverse battles in trainer houses
	return

.global GameModifiers_InverseBattles_ClearModifier
GameModifiers_InverseBattles_ClearModifier:
	clearflag 0x900 @ Turn off inverse
	clearflag 0x151 @ Do not turn off inverse battles in trainer houses
	return

// TODO Later: Others!
