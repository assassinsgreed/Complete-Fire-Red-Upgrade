#include "defines.h"
#include "defines_battle.h"
#include "../include/battle.h"
#include "../include/event_data.h"
#include "../include/main.h"
#include "../include/random.h"
#include "../include/script.h"
#include "../include/string_util.h"
#include "../include/constants/battle.h"
#include "../include/constants/songs.h"

#include "../include/new/frontier.h"
#include "../include/new/util.h"
#include "../include/new/Vanilla_functions.h"

/*
frontier_challenge.c
	Run lifecycle for the Battle Frontier: first-visit initialisation, starting a
	challenge, putting one on hold, picking one back up, ending one, and choosing the
	next opponent.

	Each facility/format pair records it's own streak; players are welcome to suspend
	a run at any of them and start/resume at another without losing that progress.
	All of it is facility-agnostic. A facility is identified only by
	BATTLE_FACILITY_NUM, and the format only by VAR_BATTLE_FACILITY_BATTLE_TYPE, so
	these same functions drive all eight facilities. The only per-facility work is the
	hook each one runs before a battle, which lives in battle_frontier.s.

	All functionality callable via callasm instead of new specials, for simplicity
*/

// Amethyst does not support tiers, cups, or format restrictions (i.e. "No Restrictions" in Unbound)
#define FRONTIER_TIER BATTLE_FACILITY_NO_RESTRICTIONS

#define NUM_MONS_SINGLES 3
#define NUM_MONS_DOUBLES 4

enum FrontierOpponentKinds
{
	FRONTIER_OPPONENT_REGULAR,
	FRONTIER_OPPONENT_ACE,
	FRONTIER_OPPONENT_BRAIN,
};

extern u8 (*sSaveDialogCallback)(void);
void __attribute__((long_call)) Field_AskSaveTheGame(void);
u8 __attribute__((long_call)) SaveDialogCB_PrintAskSaveText(void);
u8 __attribute__((long_call)) SaveDialogCB_DisplaySavingMessage(void);

extern const u8 gText_FrontierRecordSingles[];
extern const u8 gText_FrontierRecordDoubles[];

// Music customization options (Ace/Brain trainers do not get overriden)
extern const u8 gText_BattleFrontier_ChoiceCancel[];
extern const u8 gText_BattleFrontier_MusicDefault[]; // Battle Subway Trainer
extern const u8 gText_BattleFrontier_MusicRandom[];
extern const u8 gText_BattleFrontier_MusicTrainer[];
extern const u8 gText_BattleFrontier_MusicGymLeader[];
extern const u8 gText_BattleFrontier_MusicKantoGymTrainee[];
extern const u8 gText_BattleFrontier_MusicJohtoGymTrainee[];
extern const u8 gText_BattleFrontier_MusicHoennGymTrainee[];
extern const u8 gText_BattleFrontier_MusicSinnohGymTrainee[];
extern const u8 gText_BattleFrontier_MusicRival[];
extern const u8 gText_BattleFrontier_MusicAlistair[];
extern const u8 gText_BattleFrontier_MusicCasey[];
extern const u8 gText_BattleFrontier_MusicKurtis[];
extern const u8 gText_BattleFrontier_MusicEliteFour[];
extern const u8 gText_BattleFrontier_MusicChampion[];
extern const u8 gText_BattleFrontier_MusicLegendary[];
extern const u8 gText_BattleFrontier_MusicJirachi[];
extern const u8 gText_BattleFrontier_MusicUnwaveringHeart[];

// Background customization options
extern const u8 gText_BattleFrontier_BackgroundGym[];
extern const u8 gText_BattleFrontier_BackgroundRandom[];
extern const u8 gText_BattleFrontier_BackgroundGrassland[];
extern const u8 gText_BattleFrontier_BackgroundTallGrass[];
extern const u8 gText_BattleFrontier_BackgroundForest[];
extern const u8 gText_BattleFrontier_BackgroundPeradonForest[];
extern const u8 gText_BattleFrontier_BackgroundJungle[];
extern const u8 gText_BattleFrontier_BackgroundMountain[];
extern const u8 gText_BattleFrontier_BackgroundVolcanoPeak[];
extern const u8 gText_BattleFrontier_BackgroundCave[];
extern const u8 gText_BattleFrontier_BackgroundTormaCave[];
extern const u8 gText_BattleFrontier_BackgroundTormaDepths[];
extern const u8 gText_BattleFrontier_BackgroundLavaPool[];
extern const u8 gText_BattleFrontier_BackgroundHotSpring[];
extern const u8 gText_BattleFrontier_BackgroundBeach[];
extern const u8 gText_BattleFrontier_BackgroundDesert[];
extern const u8 gText_BattleFrontier_BackgroundSnowfield[];
extern const u8 gText_BattleFrontier_BackgroundOcean[];
extern const u8 gText_BattleFrontier_BackgroundPond[];
extern const u8 gText_BattleFrontier_BackgroundUndergroundLake[];
extern const u8 gText_BattleFrontier_BackgroundHauntedHouse[];
extern const u8 gText_BattleFrontier_BackgroundBuilding[];
extern const u8 gText_BattleFrontier_BackgroundPlutoHQ[];
extern const u8 gText_BattleFrontier_BackgroundChampionsRoom[];
extern const u8 gText_BattleFrontier_BackgroundDaisOfLight[];

const u8* const gFrontierMusicChoiceNames[NUM_FRONTIER_MUSIC_CHOICES + 1] =
{
	gText_BattleFrontier_MusicDefault,
	gText_BattleFrontier_MusicRandom,
	gText_BattleFrontier_MusicTrainer,
	gText_BattleFrontier_MusicGymLeader,
	gText_BattleFrontier_MusicKantoGymTrainee,
	gText_BattleFrontier_MusicJohtoGymTrainee,
	gText_BattleFrontier_MusicHoennGymTrainee,
	gText_BattleFrontier_MusicSinnohGymTrainee,
	gText_BattleFrontier_MusicRival,
	gText_BattleFrontier_MusicAlistair,
	gText_BattleFrontier_MusicCasey,
	gText_BattleFrontier_MusicKurtis,
	gText_BattleFrontier_MusicEliteFour,
	gText_BattleFrontier_MusicChampion,
	gText_BattleFrontier_MusicLegendary,
	gText_BattleFrontier_MusicJirachi,
	gText_BattleFrontier_MusicUnwaveringHeart,
	gText_BattleFrontier_ChoiceCancel,
};

const u16 gFrontierMusicChoiceSongs[NUM_FRONTIER_MUSIC_CHOICES] =
{
	BGM_BATTLE_FRONTIER_TRAINER,
	BGM_RANDOM_BATTLE_MUSIC,
	BGM_BATTLE_TRAINER,
	BGM_BATTLE_GYM_LEADER,
	BGM_BATTLE_KANTO_LEADER,
	BGM_BATTLE_JOHTO_LEADER,
	BGM_BATTLE_HOENN_LEADER,
	BGM_BATTLE_SINNOH_LEADER,
	BGM_BATTLE_RIVAL,
	BGM_BATTLE_ALISTAIR,
	BGM_BATTLE_CASEY,
	BGM_BATTLE_TEAM_PLUTO_KURTIS,
	BGM_BATTLE_ELITE_FOUR,
	BGM_BATTLE_CHAMPION,
	BGM_BATTLE_LEGENDARY_BIRDS,
	BGM_BATTLE_MEWTWO,
	BGM_BATTLE_UNWAVERING_HEART,
};

const u8* const gFrontierBackgroundChoiceNames[NUM_FRONTIER_BACKGROUND_CHOICES + 1] =
{
	gText_BattleFrontier_BackgroundGym,
	gText_BattleFrontier_BackgroundRandom,
	gText_BattleFrontier_BackgroundGrassland,
	gText_BattleFrontier_BackgroundTallGrass,
	gText_BattleFrontier_BackgroundForest,
	gText_BattleFrontier_BackgroundPeradonForest,
	gText_BattleFrontier_BackgroundJungle,
	gText_BattleFrontier_BackgroundMountain,
	gText_BattleFrontier_BackgroundVolcanoPeak,
	gText_BattleFrontier_BackgroundCave,
	gText_BattleFrontier_BackgroundTormaCave,
	gText_BattleFrontier_BackgroundTormaDepths,
	gText_BattleFrontier_BackgroundLavaPool,
	gText_BattleFrontier_BackgroundHotSpring,
	gText_BattleFrontier_BackgroundBeach,
	gText_BattleFrontier_BackgroundDesert,
	gText_BattleFrontier_BackgroundSnowfield,
	gText_BattleFrontier_BackgroundOcean,
	gText_BattleFrontier_BackgroundPond,
	gText_BattleFrontier_BackgroundUndergroundLake,
	gText_BattleFrontier_BackgroundHauntedHouse,
	gText_BattleFrontier_BackgroundBuilding,
	gText_BattleFrontier_BackgroundPlutoHQ,
	gText_BattleFrontier_BackgroundChampionsRoom,
	gText_BattleFrontier_BackgroundDaisOfLight,
	gText_BattleFrontier_ChoiceCancel,
};

const u8 gFrontierBackgroundChoiceTerrains[NUM_FRONTIER_BACKGROUND_CHOICES] =
{
	BATTLE_TERRAIN_GYM,
	BATTLE_TERRAIN_GYM, // To handle a case where random (in this slot in the UI) rolls this same index
	BATTLE_TERRAIN_GRASS,
	BATTLE_TERRAIN_LONG_GRASS,
	BATTLE_TERRAIN_FOREST,
	BATTLE_TERRAIN_FOREST_PERADON,
	BATTLE_TERRAIN_JUNGLE,
	BATTLE_TERRAIN_MOUNTAIN,
	BATTLE_TERRAIN_CARNELIDGE_PEAK,
	BATTLE_TERRAIN_CAVE,
	BATTLE_TERRAIN_TORMA,
	BATTLE_TERRAIN_TORMA_DEPTHS,
	BATTLE_TERRAIN_LAVA_POOL,
	BATTLE_TERRAIN_SCALDING_SPA,
	BATTLE_TERRAIN_SAND,
	BATTLE_TERRAIN_DESERT,
	BATTLE_TERRAIN_SNOWY,
	BATTLE_TERRAIN_WATER,
	BATTLE_TERRAIN_POND,
	BATTLE_TERRAIN_POND_CAVE,
	BATTLE_TERRAIN_SPOOKY,
	BATTLE_TERRAIN_INSIDE,
	BATTLE_TERRAIN_PLUTO_LEADER,
	BATTLE_TERRAIN_CHAMPION,
	BATTLE_TERRAIN_DAIS_OF_LIGHT,
};

// Track the game modifiers that should be disabled while in a battle frontier challenge.
// Notably the Restore Held Consumeables modifier is missing - this should always be ON in frontiers!
static const u16 gFrontierOverriddenModifierFlags[] =
{
	FLAG_POKEMON_RANDOMIZER,
	FLAG_POKEMON_RANDOMIZER_KULURE_ONLY,
	FLAG_POKEMON_LEARNSET_RANDOMIZER,
	FLAG_ABILITY_RANDOMIZER,
	FLAG_INVERSE,
	FLAG_DO_NOT_DISABLE_INVERSE_BATTLES,
	FLAG_CAMOMONS_BATTLE,
	FLAG_DO_NOT_DISABLE_CAMOMON_BATTLES,
	FLAG_DOUBLE_BATTLE,
	FLAG_DOUBLE_WILD_BATTLE,
	FLAG_DOUBLE_WILD_BATTLES_MODIFIER_ACTIVE,
	FLAG_ALWAYS_CATCHABLE,
	FLAG_CATCH_TRAINERS_POKEMON,
	FLAG_SCALE_WILD_POKEMON_LEVELS,
	FLAG_SCALE_TRAINER_LEVELS,
	FLAG_SCALING_TRAINERS_MODIFIER_ACTIVE,
	FLAG_HIDDEN_ABILITY,
	FLAG_SHINY_CREATION,
	FLAG_SHINY_GAME_MODIFIER_ON,
	FLAG_MOVE_RELEARNER_IGNORE_LEVEL,
	FLAG_DEXNAV_SHOW_ALL_SPECIES,
	FLAG_INSTANT_FRIENDSHIP,
	FLAG_ENABLE_EV_IV_VIEWER,
	FLAG_DIVERGENT_WILD_ENCOUNTERS_OPTION_SHOWN,
};

#define NUM_OVERRIDDEN_MODIFIER_FLAGS ARRAY_COUNT(gFrontierOverriddenModifierFlags)

static void OverrideGameModifiers(void)
{
	u32 i;

	// We do not attempt to override if we have already overridden; doing so would wipe player-chosen modifiers
	if (gFrontierModifierBackup.overridden)
		return;

	gFrontierModifierBackup.flags = 0;

	for (i = 0; i < NUM_OVERRIDDEN_MODIFIER_FLAGS; ++i)
	{
		if (FlagGet(gFrontierOverriddenModifierFlags[i]))
		{
			gFrontierModifierBackup.flags |= 1 << i;
			FlagClear(gFrontierOverriddenModifierFlags[i]);
		}
	}

	gFrontierModifierBackup.weather = VarGet(VAR_INSTANT_BATTLE_WEATHER);
	gFrontierModifierBackup.terrain = VarGet(VAR_INSTANT_BATTLE_TERRAIN);
	VarSet(VAR_INSTANT_BATTLE_WEATHER, 0);
	VarSet(VAR_INSTANT_BATTLE_TERRAIN, 0);

	gFrontierModifierBackup.overridden = TRUE;
}

// Restore anything the run itself overwrote, to restore player preferences
static void RestoreGameModifiers(void)
{
	u32 i;

	if (!gFrontierModifierBackup.overridden)
		return;

	for (i = 0; i < NUM_OVERRIDDEN_MODIFIER_FLAGS; ++i)
	{
		if (gFrontierModifierBackup.flags & (1 << i))
			FlagSet(gFrontierOverriddenModifierFlags[i]);
		else
			FlagClear(gFrontierOverriddenModifierFlags[i]);
	}

	VarSet(VAR_INSTANT_BATTLE_WEATHER, gFrontierModifierBackup.weather);
	VarSet(VAR_INSTANT_BATTLE_TERRAIN, gFrontierModifierBackup.terrain);

	gFrontierModifierBackup.overridden = FALSE;
	gFrontierModifierBackup.flags = 0;
}

static u8 SanitizeBackgroundChoice(u8 choice)
{
	return (choice < NUM_FRONTIER_BACKGROUND_CHOICES) ? choice : FRONTIER_BACKGROUND_DEFAULT_CHOICE;
}

// Finds the selected background choice, to highlight it in green
u8 GetCurrentFrontierBackgroundChoice(void)
{
	return SanitizeBackgroundChoice(gFrontierBackground.choice);
}

static u8 RollBattleBackground(void)
{
	u8 choice = Random() % (NUM_FRONTIER_BACKGROUND_CHOICES - 1);

	if (choice >= FRONTIER_BACKGROUND_RANDOM_CHOICE) // Don't land on Random (a UI item with no matching background)
		++choice;

	return choice;
}

// The background a facility battle should draw, done at runtime through GetBattleBackgroundToDraw in battle_terrain.c.
u8 GetFrontierBattleBackground(void)
{
	u8 choice = SanitizeBackgroundChoice(gFrontierBackground.choice);

	if (choice == FRONTIER_BACKGROUND_RANDOM_CHOICE)
		choice = SanitizeBackgroundChoice(gFrontierBackground.rolledChoice);

	return gFrontierBackgroundChoiceTerrains[choice];
}

static u8 SanitizeFacility(u8 facility)
{
	return (facility < NUM_BATTLE_FACILITIES) ? facility : IN_BATTLE_TOWER;
}

static u8 SanitizeFormat(u8 format)
{
	return (format < NUM_FRONTIER_FORMATS) ? format : FRONTIER_FORMAT_SINGLES;
}

static u8 NumMonsInFormat(u8 format)
{
	return (format == FRONTIER_FORMAT_DOUBLES) ? NUM_MONS_DOUBLES : NUM_MONS_SINGLES;
}

static u8* GetRunState(u8 facility, u8 format)
{
	return &gFrontierRunStates[SanitizeFacility(facility)][SanitizeFormat(format)];
}

// The run the facility vars point at. A facility must set BATTLE_FACILITY_NUM for this to work.
static u8* GetSelectedRunState(void)
{
	return GetRunState(BATTLE_FACILITY_NUM, GetCurrentFrontierFormat());
}

// Loads the vars the engine reads a facility off. Run on a new challenge, on Continue, and
// before the party screen so it asks for the right number of Pokemon.
static void LoadFacilityVars(u8 facility, u8 format)
{
	SET_BATTLE_FACILITY_NUM(facility);
	VarSet(VAR_BATTLE_FACILITY_TIER, FRONTIER_TIER); // Fixed as No Restrictions in Amethyst
	VarSet(VAR_BATTLE_FACILITY_POKE_LEVEL, FRONTIER_LEVEL); // Fixed as Lvl 50 in Amethyst
	VarSet(VAR_BATTLE_FACILITY_BATTLE_TYPE, (format == FRONTIER_FORMAT_DOUBLES) ? BATTLE_FACILITY_DOUBLE : BATTLE_FACILITY_SINGLE);
	VarSet(VAR_BATTLE_FACILITY_POKE_NUM, NumMonsInFormat(format));

	FlagSet(FLAG_BATTLE_FACILITY);

	#ifdef FLAG_DYNAMAX_BATTLE
	FlagClear(FLAG_DYNAMAX_BATTLE); // Amethyst does not support Dynamax
	#endif

	// SaveBlock1.playerParty holds the player's real team for the whole run - special 0x27 puts
	// it there - and the Benjamin Butterfree battle hooks call SavePlayerParty()/LoadPlayerParty()
	// over that same buffer, so one BB battle during a run would destroy the backup permanently.
	// The Uteya Trainer House sets this flag and clears it on the way out, so this only matters
	// if that script was interrupted.
	#ifdef FLAG_BENJAMIN_BUTTERFREE_BATTLE
	FlagClear(FLAG_BENJAMIN_BUTTERFREE_BATTLE);
	#endif
}

void FrontierChallenge_InitDataIfNeeded(void)
{
	u32 facility, format;

	// Initializes default song to Frontier Trainer
	// This will not conflict with Alistair's post-credits battle because the facility is only accessible after it
	if (VarGet(VAR_BATTLE_FACILITY_SONG_OVERRIDE) == 0)
		VarSet(VAR_BATTLE_FACILITY_SONG_OVERRIDE, gFrontierMusicChoiceSongs[FRONTIER_MUSIC_DEFAULT_CHOICE]);

	if (!FlagGet(FLAG_FRONTIER_DATA_INITIALISED))
	{
		Memset(gFrontierStreaks, 0, sizeof(gFrontierStreaks));
		Memset(gFrontierRunStates, 0, sizeof(gFrontierRunStates));
		Memset(&gFrontierModifierBackup, 0, sizeof(gFrontierModifierBackup));
		Memset(&gFrontierBackground, 0, sizeof(gFrontierBackground));
		FlagSet(FLAG_FRONTIER_DATA_INITIALISED);
		return;
	}

	for (facility = 0; facility < NUM_BATTLE_FACILITIES; ++facility)
	{
		for (format = 0; format < NUM_FRONTIER_FORMATS; ++format)
		{
			u8* state = &gFrontierRunStates[facility][format];

			if (*state == FRONTIER_ACTIVE || *state > FRONTIER_RESTING)
			{
				SetFrontierStreak(facility, format, CURR_STREAK, 0);
				*state = FRONTIER_NONE;
			}
		}
	}

	RestoreGameModifiers();
}

// Returns FRONTIER_NONE / FRONTIER_ACTIVE / FRONTIER_RESTING.
void FrontierChallenge_GetState(void)
{
	gSpecialVar_LastResult = *GetSelectedRunState();
}

// Whether one of this facility's formats has a run on hold, so it can be labelled as On Hold in the selection menu.
// Inputs:
//		Var8000: format (0 = Singles, 1 = Doubles). Passed in rather than read off the facility vars, which aren't loaded yet at the point the menu is built.
// Returns: TRUE if that run is on hold.
void FrontierChallenge_IsFormatPaused(void)
{
	gSpecialVar_LastResult = (*GetRunState(BATTLE_FACILITY_NUM, Var8000) == FRONTIER_RESTING);
}

// Sets up the format vars before the player has committed to a run, so the party screen asks for the right number of Pokemon.
// Inputs:
//		Var8000: format (0 = Singles, 1 = Doubles)
void FrontierChallenge_LoadFacilityVars(void)
{
	LoadFacilityVars(SanitizeFacility(BATTLE_FACILITY_NUM), SanitizeFormat(Var8000));
}

// Starts a new run. The real party must already be backed up (special 0x27) and the entered team chosen before this is called.
void FrontierChallenge_Begin(void)
{
	SetFrontierStreak(SanitizeFacility(BATTLE_FACILITY_NUM), GetCurrentFrontierFormat(), CURR_STREAK, 0);

	*GetSelectedRunState() = FRONTIER_ACTIVE;
}

// Whether the chosen run needs to save before starting.
// Primarily to detect a run resuming from Resting, which needs to mark the run as abandoned and save, in case the user soft resets.
// Returns: TRUE if the run needs to save.
void FrontierChallenge_NeedsCommitting(void)
{
	gSpecialVar_LastResult = (*GetSelectedRunState() == FRONTIER_RESTING);
}

// Marks a held run live, one battle away from starting.
// The script saves immediately after, and that save is what makes the streak forfeitable from here on.
void FrontierChallenge_Commit(void)
{
	*GetSelectedRunState() = FRONTIER_ACTIVE;
}

// Disables game modifiers for the duration of a frontier run
void FrontierChallenge_OverrideGameModifiers(void)
{
	OverrideGameModifiers();
}

// Puts the run on hold and restores the player's preferred game modifiers
void FrontierChallenge_SetResting(void)
{
	*GetSelectedRunState() = FRONTIER_RESTING;

	RestoreGameModifiers();
}

// Ends the selected run (by loss and abandon).
// Current streak gets set to 0 and the max streak is updated if needed. 
void FrontierChallenge_End(void)
{
	SetFrontierStreak(SanitizeFacility(BATTLE_FACILITY_NUM), GetCurrentFrontierFormat(), CURR_STREAK, 0);

	*GetSelectedRunState() = FRONTIER_NONE;

	RestoreGameModifiers();
}

// Clean up facility vars
void FrontierChallenge_ClearFacilityVars(void)
{
	FlagClear(FLAG_BATTLE_FACILITY);
	VarSet(VAR_BATTLE_FACILITY_TRAINER1_NAME, 0xFFFF);
	VarSet(VAR_BATTLE_FACILITY_TRAINER2_NAME, 0xFFFF);
}

// Puts the facility flag back once a run's save is written, so the battles that follow run under facility rules again.
void FrontierChallenge_SetFacilityFlag(void)
{
	FlagSet(FLAG_BATTLE_FACILITY);
}

// (Internal) Force the player to save without prompting (needed for resuming a rested run)
static u8 SaveDialogCB_ForceSave(void)
{
	SaveDialogCB_PrintAskSaveText();
	return SaveDialogCB_DisplaySavingMessage();
}

// Saves without asking, supporting resuming a Rested run without needing to handle funky Yes/No dialog paths.
void FrontierChallenge_ForceSave(void)
{
	Field_AskSaveTheGame();
	sSaveDialogCallback = SaveDialogCB_ForceSave;
}

// Buffers the values the shared attendant dialogue needs, so generic code can support any facility. Must be called before NPC scripts
// Returns: gStringVar1: facility name
//			gStringVar2: format name
//			gStringVar3: current streak
void FrontierChallenge_BufferFacilityInfo(void)
{
	u8 facility = SanitizeFacility(BATTLE_FACILITY_NUM);
	u8 format = GetCurrentFrontierFormat();

	StringCopy(gStringVar1, gBattleFacilityNames[facility]);
	StringCopy(gStringVar2, (format == FRONTIER_FORMAT_DOUBLES) ? gText_FrontierRecordDoubles : gText_FrontierRecordSingles);
	ConvertIntToDecimalStringN(gStringVar3, GetFrontierStreak(facility, format, CURR_STREAK), 0, 5);
}

// The current music customization choice, to allow highlighting it in green in the UI
u8 GetCurrentFrontierMusicChoice(void)
{
	u16 song = VarGet(VAR_BATTLE_FACILITY_SONG_OVERRIDE);

	for (u32 i = 0; i < NUM_FRONTIER_MUSIC_CHOICES; ++i)
	{
		if (gFrontierMusicChoiceSongs[i] == song)
			return i;
	}

	return FRONTIER_MUSIC_DEFAULT_CHOICE;
}

// Names the track facility battles are currently set to play for UI presentation.
// Returns: gStringVar1: the chosen entry's name.
void FrontierChallenge_BufferBattleMusicName(void)
{
	StringCopy(gStringVar1, gFrontierMusicChoiceNames[GetCurrentFrontierMusicChoice()]);
}

// Applies a pick from the music list. This is agnostic to the run so it applies to all facilities.
// Inputs:
//		Var8000: the list's result. Anything past the last track is the Cancel row or a B press.
// Returns: LastResult: TRUE if a track was chosen.
//			gStringVar1: that track's name, for the confirmation line.
void FrontierChallenge_SetBattleMusic(void)
{
	u16 choice = Var8000;

	if (choice >= NUM_FRONTIER_MUSIC_CHOICES)
	{
		gSpecialVar_LastResult = FALSE;
		return;
	}

	VarSet(VAR_BATTLE_FACILITY_SONG_OVERRIDE, gFrontierMusicChoiceSongs[choice]);
	StringCopy(gStringVar1, gFrontierMusicChoiceNames[choice]);
	gSpecialVar_LastResult = TRUE;
}

// Names the background facility battles are currently drawn on, for presentation in the customization UI.
// Returns: gStringVar1: the chosen entry's name.
void FrontierChallenge_BufferBattleBackgroundName(void)
{
	StringCopy(gStringVar1, gFrontierBackgroundChoiceNames[GetCurrentFrontierBackgroundChoice()]);
}

// Applies a pick from the background list. This is run agnostic and will apply to all facilities.
// Inputs:
//		Var8000: the list's result. Anything past the last background is the Cancel row or a B press.
// Returns: LastResult: TRUE if a background was chosen.
//			gStringVar1: that background's name, for the confirmation line.
void FrontierChallenge_SetBattleBackground(void)
{
	u16 choice = Var8000;

	if (choice >= NUM_FRONTIER_BACKGROUND_CHOICES)
	{
		gSpecialVar_LastResult = FALSE;
		return;
	}

	gFrontierBackground.choice = choice;
	StringCopy(gStringVar1, gFrontierBackgroundChoiceNames[choice]);
	gSpecialVar_LastResult = TRUE;
}

// How many Pokemon the chosen format asks the player to enter. (3 for singles, 4 for doubles)
// Returns: gStringVar3: the number.
void FrontierChallenge_BufferNumMonsToEnter(void)
{
	ConvertIntToDecimalStringN(gStringVar3, GetNumMonsOnTeamInFrontier(), 0, 1);
}

// Whether the player picked a team or cancelled. (The player's party is restored when backing out)
// Returns: LastResult: TRUE if a team was entered.
void FrontierChallenge_DidChooseTeam(void)
{
	gSpecialVar_LastResult = gSelectedOrderFromParty[0] != 0;
}

// The outcome of the battle that just finished.
// Returns: LastResult: TRUE if the player won.
void FrontierChallenge_DidPlayerWin(void)
{
	gSpecialVar_LastResult = (gBattleOutcome == B_OUTCOME_WON);
}

// Determines whether an Ace (20th battle) or Brain (50th) is next, so the attendant
// can display the correct "strong trainer coming" warning text.
static u8 GetNextOpponentKind(void)
{
	u16 nextWin = GetCurrentBattleFacilityStreak() + 1;

	if (nextWin == FRONTIER_SECOND_MILESTONE_STREAK && NUM_FRONTIER_BRAINS > 0)
		return FRONTIER_OPPONENT_BRAIN;

	if (nextWin == FRONTIER_FIRST_MILESTONE_STREAK && NUM_SPECIAL_TOWER_TRAINERS > 0)
		return FRONTIER_OPPONENT_ACE;

	return FRONTIER_OPPONENT_REGULAR;
}

// What kind of opponent the next battle would be against (regular, ace, brain)
// Returns: LastResult: 0 = regular trainer, 1 = special trainer, 2 = Frontier Brain.
void FrontierChallenge_GetNextOpponentKind(void)
{
	gSpecialVar_LastResult = GetNextOpponentKind();
}

// Decides who the next battle is against and loads the inputs sp052 and sp053 expect.
// Returns: LastResult: 0 = regular trainer, 1 = special trainer, 2 = Frontier Brain.
//			Var8000/Var8001/Var8002: set up for sp052 and sp053.
void FrontierChallenge_SetUpNextOpponent(void)
{
	u8 kind = GetNextOpponentKind();

	gFrontierBackground.rolledChoice = RollBattleBackground();

	//The script uses trainerbattle9 so that losing returns to the attendant instead of whiting
	//the player out. That relies on CONTINUE_LOST_BATTLES, whose patch to CB2_EndTrainerBattle
	//only skips the whiteout when sTrainerBattleOakTutorialHelper has bit 0 clear. Nothing
	//resets it after Oak's tutorial, so clear it here.
	sTrainerBattleOakTutorialHelper = 0;

	Var8000 = BATTLE_FACILITY_TRAINER_A;
	Var8001 = kind;
	// gFrontierBrains is one brain per facility, in facility order, so this is a direct index.
	// The modulo only matters if the table ever holds fewer entries than there are facilities.
	Var8002 = (kind == FRONTIER_OPPONENT_BRAIN) ? (SanitizeFacility(BATTLE_FACILITY_NUM) % NUM_FRONTIER_BRAINS) : 0;

	gSpecialVar_LastResult = kind;
}

// Calculates the PokeChip reward for the win just earned.
// Returns: LastResult: chips to award, for the script's obtainitem.
//			gStringVar2: the same number, overwriting the format name the reward text doesn't need.
void FrontierChallenge_StoreChipsToGive(void)
{
	u16 chips = sp056_DetermineChipsToGive();

	ConvertIntToDecimalStringN(gStringVar2, chips, 0, 3);
	gSpecialVar_LastResult = chips;
}

// Restores the text colour sp053 swaps out when it prints an opponent's line.
void FrontierChallenge_RestoreTextColour(void)
{
	gTextColourCurrent = gTextColourBackup;
}
