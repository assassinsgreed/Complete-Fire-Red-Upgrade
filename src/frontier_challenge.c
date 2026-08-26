#include "defines.h"
#include "defines_battle.h"
#include "../include/battle.h"
#include "../include/event_data.h"
#include "../include/main.h"
#include "../include/random.h"
#include "../include/script.h"
#include "../include/string_util.h"
#include "../include/constants/battle.h"
#include "../include/constants/items.h"
#include "../include/constants/songs.h"
#include "../include/pokemon.h"

#include "../include/new/battle_start_turn_start.h"
#include "../include/new/build_pokemon.h"
#include "../include/new/damage_calc.h"
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

	The Battle Factory is the one facility that owns state of its own: it rents the player a
	team instead of letting them bring one, so the rented team must be restored after resting. It lives in
	gFrontierRentalTeams, keyed by format so a held Singles run and a held Doubles run cannot overwrite each other.

	All functionality callable via callasm instead of new specials, for simplicity
*/

// Amethyst does not support tiers, cups, or format restrictions (i.e. "No Restrictions" in Unbound)
#define FRONTIER_TIER BATTLE_FACILITY_NO_RESTRICTIONS

#define NUM_MONS_SINGLES 3
#define NUM_MONS_DOUBLES 4

// gFrontierRentalTeams is sized for the larger format rather than per format, so growing a team
// past MAX_FRONTIER_TEAM_SIZE would silently drop Pokemon off the end of a rested Battle Factory run.
#if NUM_MONS_DOUBLES > MAX_FRONTIER_TEAM_SIZE
#error "MAX_FRONTIER_TEAM_SIZE in frontier.h must cover the largest format's team"
#endif

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
extern const u8 gText_ObservatoryNameJoiner[];
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
extern const u8 gText_BattleFrontier_BackgroundGymArena[];
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
	gText_BattleFrontier_BackgroundGymArena,
	gText_BattleFrontier_BackgroundChampionsRoom,
	gText_BattleFrontier_BackgroundDaisOfLight,
	gText_BattleFrontier_ChoiceCancel,
};

const u8 gFrontierBackgroundChoiceTerrains[NUM_FRONTIER_BACKGROUND_CHOICES] =
{
	BATTLE_TERRAIN_GYM, // Unused - Default resolves through gFacilityDefaultBackgrounds instead
	BATTLE_TERRAIN_GYM, // Unused - Random resolves through gFrontierBackground.rolledChoice instead
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
	BATTLE_TERRAIN_GYM,
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
	FLAG_PERFECT_WILD_IVS,
	FLAG_REPEATED_MEGA_EVOLUTION,
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

static void ClearRentalTeam(u8 format);
static void ClearObservatoryTeam(void);
static u8 NumObservatoryPicks(void);

static u8 SanitizeFacility(u8 facility)
{
	return (facility < NUM_BATTLE_FACILITIES) ? facility : IN_BATTLE_TOWER;
}

// What the Default row draws, per facility
static const u8 gFacilityDefaultBackgrounds[NUM_BATTLE_FACILITIES] =
{
	[IN_BATTLE_TOWER]   = BATTLE_TERRAIN_GYM,
	[IN_BATTLE_SANDS]   = BATTLE_TERRAIN_SAND,
	[IN_BATTLE_QUARRY]  = BATTLE_TERRAIN_CAVE,
	[IN_BATTLE_SIM]  	= BATTLE_TERRAIN_CHAMPION,
	[IN_BATTLE_FACTORY] = BATTLE_TERRAIN_INSIDE,
	[IN_BATTLE_OBSERVATORY] = BATTLE_TERRAIN_PLUTO_LEADER,
	[IN_BATTLE_ISLE]    = BATTLE_TERRAIN_GRASS,
	[IN_BATTLE_MAZE]    = BATTLE_TERRAIN_GRASS,
};

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
	// Default and Random are UI rows with no background of their own, and occupy the first two slots
	u8 numRealChoices = NUM_FRONTIER_BACKGROUND_CHOICES - FIRST_REAL_FRONTIER_BACKGROUND_CHOICE;

	return FIRST_REAL_FRONTIER_BACKGROUND_CHOICE + (Random() % numRealChoices);
}

// The background a facility battle should draw, done at runtime through GetBattleBackgroundToDraw in battle_terrain.c.
u8 GetFrontierBattleBackground(void)
{
	u8 choice = SanitizeBackgroundChoice(gFrontierBackground.choice);

	if (choice == FRONTIER_BACKGROUND_RANDOM_CHOICE)
		choice = SanitizeBackgroundChoice(gFrontierBackground.rolledChoice);

	// A frontier battle fought outside a facility clamps to the Tower's background rather than reading garbage
	if (choice == FRONTIER_BACKGROUND_DEFAULT_CHOICE)
		return gFacilityDefaultBackgrounds[SanitizeFacility(BATTLE_FACILITY_NUM)];

	return gFrontierBackgroundChoiceTerrains[choice];
}

static u8 SanitizeFormat(u8 format)
{
	return (format < NUM_FRONTIER_FORMATS) ? format : FRONTIER_FORMAT_SINGLES;
}

static u8 NumMonsInFormat(u8 format)
{
	return (format == FRONTIER_FORMAT_DOUBLES) ? NUM_MONS_DOUBLES : NUM_MONS_SINGLES;
}

// The Battle Maze and Battle Factory use Pokemon from the opponents' pool
static bool8 FacilityRollsItsOwnTeams(u8 facility)
{
	return facility == IN_BATTLE_MAZE;
}

// The Battle Factory rents a team once and keeps it for the whole run, so unlike the Maze it stays on the
// non-random battle types - that is what stops BuildTrainerPartySetup re-rolling gPlayerParty before every battle.
static bool8 FacilityRentsItsTeam(u8 facility)
{
	return facility == IN_BATTLE_FACTORY;
}

static u8 BattleTypeForFormat(u8 facility, u8 format)
{
	if (FacilityRollsItsOwnTeams(facility))
		return (format == FRONTIER_FORMAT_DOUBLES) ? BATTLE_FACILITY_DOUBLE_RANDOM : BATTLE_FACILITY_SINGLE_RANDOM;

	return (format == FRONTIER_FORMAT_DOUBLES) ? BATTLE_FACILITY_DOUBLE : BATTLE_FACILITY_SINGLE;
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
	VarSet(VAR_BATTLE_FACILITY_BATTLE_TYPE, BattleTypeForFormat(facility, format));
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
	gFrontierPartyScreen = FRONTIER_SCREEN_NONE;

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
		Memset(gFrontierRentalTeams, 0, sizeof(gFrontierRentalTeams));
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

				if (facility == IN_BATTLE_FACTORY)
					ClearRentalTeam(format); // The forfeited run's rented team goes with it

				if (facility == IN_BATTLE_OBSERVATORY)
					ClearObservatoryTeam(); // Not per format - only one run is ever mid-battle
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

	if (FacilityRentsItsTeam(SanitizeFacility(BATTLE_FACILITY_NUM)))
		ClearRentalTeam(GetCurrentFrontierFormat()); // The rented team is only ever on loan for one run

	if (SanitizeFacility(BATTLE_FACILITY_NUM) == IN_BATTLE_OBSERVATORY)
		ClearObservatoryTeam();

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

// ============================================================================
// Battle Factory rentals
// ============================================================================

// The slot holding the rented team for the run currently selected. The facility vars name that run, so this is only meaningful once LoadFacilityVars has run.
static struct Pokemon* GetRentalTeam(void)
{
	return gFrontierRentalTeams[GetCurrentFrontierFormat()];
}

static void ClearRentalTeam(u8 format)
{
	Memset(gFrontierRentalTeams[SanitizeFormat(format)], 0, sizeof(gFrontierRentalTeams[0]));
}

// How many slots of an entered/rented team are in play.
// Clamped because the save slot is sized for the larger of the two formats rather than per format.
static u8 NumEnteredMons(void)
{
	return MathMin(GetNumMonsOnTeamInFrontier(), MAX_FRONTIER_TEAM_SIZE);
}

// Banks the live team. gPlayerParty is compacted by the time any of this runs, so slot i of the party is slot i of the team.
static void StoreRentalTeam(void)
{
	Memset(GetRentalTeam(), 0, sizeof(gFrontierRentalTeams[0]));
	Memcpy(GetRentalTeam(), gPlayerParty, sizeof(struct Pokemon) * NumEnteredMons());
}

static void RestoreRentalTeam(void)
{
	ZeroPlayerPartyMons();
	Memcpy(gPlayerParty, GetRentalTeam(), sizeof(struct Pokemon) * NumEnteredMons());
	CalculatePlayerPartyCount();
}

// Whether the selected facility hands the player a team instead of asking them to bring one.
// Returns: LastResult: TRUE at the Battle Factory.
void FrontierChallenge_IsRentalFacility(void)
{
	gSpecialVar_LastResult = FacilityRentsItsTeam(SanitizeFacility(BATTLE_FACILITY_NUM));
}

// Whether the facility supplies the team rather than asking the player to bring one - the Maze rolls
// a fresh one every battle, the Factory rents one for the whole run. Either way there is no team for
// the player to re-enter when they pick a held run back up.
// Returns: LastResult: TRUE at the Battle Maze and the Battle Factory.
void FrontierChallenge_IsProvidedTeamFacility(void)
{
	u8 facility = SanitizeFacility(BATTLE_FACILITY_NUM);

	gSpecialVar_LastResult = FacilityRollsItsOwnTeams(facility) || FacilityRentsItsTeam(facility);
}

// Fills gPlayerParty with the six rentals the player picks their team out of, and keeps a copy. The
// real party must already be backed up (special 0x27); special 0x28 brings it back once the choice is made.
//
// The copy is not redundant. Special 0xF5 does not merely reorder gPlayerParty - it CpuFastSets all
// six slots to zero and then refills three of them from an uninitialised Alloc buffer, because the
// vanilla routine still reads the selection order from 0x203B0D4 and CFRU moved that array to
// 0x203C750. Every other caller gets away with it by restoring the real party straight afterwards;
// the rental pool has nowhere to be restored from, so it is snapshotted here instead.
void FrontierChallenge_GenerateRentalPool(void)
{
	BuildBattleFactoryRentalPool();
	Memcpy(gFrontierRentalPool, gPlayerParty, sizeof(gFrontierRentalPool));
}

// Banks the team the player just picked out of the pool.
// Reads the snapshot rather than gPlayerParty, which special 0xF5 has already destroyed, and which
// only ever gets three slots written back - Doubles enters four.
void FrontierChallenge_StoreRentalPoolChoice(void)
{
	u32 i;
	u8 numMons = NumEnteredMons();
	struct Pokemon* team = GetRentalTeam();

	Memset(team, 0, sizeof(gFrontierRentalTeams[0]));

	for (i = 0; i < numMons && gSelectedOrderFromParty[i] != 0; ++i)
		Memcpy(&team[i], &gFrontierRentalPool[gSelectedOrderFromParty[i] - 1], sizeof(struct Pokemon));

	Memset(gFrontierRentalPool, 0, sizeof(gFrontierRentalPool)); // Done with, and it rides the save file
}

// Puts the rented team into gPlayerParty. Stands in for sp073 at the Factory, whose team is already
// built and level-adjusted and whose gSelectedOrderFromParty points at a rental pool long gone.
void FrontierChallenge_RestoreRentalTeam(void)
{
	RestoreRentalTeam();
}

// Banks the live team so a Rest can be picked back up with it. A no-op away from the Factory, so the
// shared Rest path can call it without asking which facility it is in.
void FrontierChallenge_StoreRentalTeam(void)
{
	if (FacilityRentsItsTeam(SanitizeFacility(BATTLE_FACILITY_NUM)))
		StoreRentalTeam();
}

// Whether the party menu should present one of the frontier's own lists rather than the default.
bool8 IsFrontierPartySubmenuOpen(void)
{
	u8 facility = SanitizeFacility(BATTLE_FACILITY_NUM);

	return (gFrontierPartyScreen == FRONTIER_SCREEN_FACTORY_GIVE
		 || gFrontierPartyScreen == FRONTIER_SCREEN_FACTORY_TAKE
		 || gFrontierPartyScreen == FRONTIER_SCREEN_OBSERVATORY_VIEW)
		&& (facility == IN_BATTLE_FACTORY || facility == IN_BATTLE_OBSERVATORY);
}

// How many Pokemon the party screen should ask for. Normally the whole team the format takes, but
// the Observatory reuses that same screen to choose which of an already-entered team is sent out.
u8 GetNumMonsToSelectInFrontier(void)
{
	if (gFrontierPartyScreen == FRONTIER_SCREEN_OBSERVATORY_PICK
	&& SanitizeFacility(BATTLE_FACILITY_NUM) == IN_BATTLE_OBSERVATORY)
		return NumObservatoryPicks();

	return GetNumMonsOnTeamInFrontier();
}

void FrontierChallenge_BeginSwapScreenOwn(void)
{
	gFrontierPartyScreen = FRONTIER_SCREEN_FACTORY_GIVE;
}

void FrontierChallenge_BeginSwapScreenOpponent(void)
{
	gFrontierPartyScreen = FRONTIER_SCREEN_FACTORY_TAKE;
}

void FrontierChallenge_EndSwapScreen(void)
{
	gFrontierPartyScreen = FRONTIER_SCREEN_NONE;
}

// Swaps the opponent's team into gPlayerParty so the party screen can show it off. The player's own
// team is banked on the way out, which is where the swap and every back-out path read it back from.
// Inputs:
//		Var8004: slot of the Pokemon the player is giving up, from the first party screen. Handled
//				 here rather than left in a script var, which the second screen is free to reuse.
void FrontierChallenge_LoadOpponentTeamForSwap(void)
{
	u32 i;
	u8 numMons = NumEnteredMons();

	gFrontierPendingSwapSlot = Var8004;

	StoreRentalTeam();
	ZeroPlayerPartyMons();

	for (i = 0; i < numMons; ++i)
	{
		if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
			break;

		gPlayerParty[i] = gEnemyParty[i];
		HealMon(&gPlayerParty[i]); // Shown, and handed over, in the state the player would receive it
	}

	CalculatePlayerPartyCount();
}

// Trades one of the player's Pokemon for one of the opponent's and banks the result.
// Inputs:
//		Var8004: slot of the opponent's Pokemon the player is taking, from the second party screen.
//		gFrontierPendingSwapSlot: slot they are giving up, handled by the call before this one.
// Returns: LastResult: TRUE if a trade actually happened. FALSE means nothing changed and the
//			     player still owes the caller a decision - never report a trade they did not make.
//			gStringVar1: the Pokemon given up.
//			gStringVar2: the Pokemon taken.
void FrontierChallenge_ApplySwap(void)
{
	u8 numMons = NumEnteredMons();
	u8 giveUp = gFrontierPendingSwapSlot;
	u8 takeOn = Var8004;
	struct Pokemon taken;

	// gPlayerParty still holds the opponent's team at this point, and the player's is banked.
	if (giveUp >= numMons || takeOn >= numMons
	|| GetMonData(&gPlayerParty[takeOn], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
	{
		RestoreRentalTeam(); // Nothing to trade, so put the player's team back untouched
		gSpecialVar_LastResult = FALSE;
		return;
	}

	taken = gPlayerParty[takeOn]; // Already healed by FrontierChallenge_LoadOpponentTeamForSwap
	RestoreRentalTeam();

	GetSpeciesName(gStringVar1, GetMonData(&gPlayerParty[giveUp], MON_DATA_SPECIES, NULL));
	GetSpeciesName(gStringVar2, GetMonData(&taken, MON_DATA_SPECIES, NULL));

	gPlayerParty[giveUp] = taken;
	CalculateMonStats(&gPlayerParty[giveUp]); // Before the heal, so the HP it is topped up to is right
	HealMon(&gPlayerParty[giveUp]);

	StoreRentalTeam();
	CalculatePlayerPartyCount();

	gSpecialVar_LastResult = TRUE;
}

/* ============================================================================
 * Battle Observatory specific functionality
 * ============================================================================
 *
 * Both trainers reveal their whole team, then send out one Pokemon each (two in Doubles) to
 * battle with. The team the player entered is stored in gObservatoryEnteredTeam for the battle
 * because gPlayerParty has to be cut down to what is actually fighting.
 */

#define OBSERVATORY_MAX_PICKS 2 // Doubles sends out two

// A Pokemon with nothing to attack with. Still pickable, so a team of them cannot leave the AI
// with no one to send out, but it loses to anything that can hit back.
#define OBSERVATORY_SCORE_NO_OFFENCE -100

// How many of the revealed Pokemon are actually sent out.
static u8 NumObservatoryPicks(void)
{
	return (GetCurrentFrontierFormat() == FRONTIER_FORMAT_DOUBLES) ? 2 : 1;
}

static void StoreObservatoryTeam(void)
{
	Memset(gObservatoryEnteredTeam, 0, sizeof(gObservatoryEnteredTeam));
	Memcpy(gObservatoryEnteredTeam, gPlayerParty, sizeof(struct Pokemon) * NumEnteredMons());
}

static void RestoreObservatoryTeam(void)
{
	ZeroPlayerPartyMons();
	Memcpy(gPlayerParty, gObservatoryEnteredTeam, sizeof(struct Pokemon) * NumEnteredMons());
	CalculatePlayerPartyCount();
}

static void ClearObservatoryTeam(void)
{
	Memset(gObservatoryEnteredTeam, 0, sizeof(gObservatoryEnteredTeam));
	Memset(gObservatoryChosenSlots, 0, sizeof(gObservatoryChosenSlots));
}

// How many Pokemon each side sends out. Used to drive the party selection screen & follow-up pre-battle messages
void FrontierChallenge_NumObservatoryPicks(void)
{
	gSpecialVar_LastResult = NumObservatoryPicks();
}

// Opens the reveal: builds the opponent's team where the player can be shown it, stores the
// player's own team, and names every Pokemon it revealed for the reveal message.
//
// The order here is load-bearing in both directions. The team has to be built while gPlayerParty
// still holds the whole entered team, because the team builder reads it to counter the player -
// and it has to be stored before anything cuts gPlayerParty down, because the stored copy is the only
// copy the picks, the AI and the post-battle merge all read from.
// Doubles reveal 4, captured in gStringVar1 (the only one big enough to hold 2 names).
// Returns: gStringVar1/2/3: the revealed Pokemon, as one message's worth of names.
void FrontierChallenge_RevealObservatoryTeams(void)
{
	u8 kind = GetNextOpponentKind();
	u16 trainerId = (kind == FRONTIER_OPPONENT_BRAIN) ? FRONTIER_BRAIN_TID
				  : (kind == FRONTIER_OPPONENT_ACE) ? BATTLE_TOWER_SPECIAL_TID
				  : BATTLE_TOWER_TID;
	u8 numMons = NumEnteredMons();

	ZeroEnemyPartyMons();
	BuildFrontierOpponentTeam(trainerId);
	StoreObservatoryTeam();

	if (numMons > 3)
	{
		u8 name[POKEMON_NAME_LENGTH + 1];

		GetSpeciesName(gStringVar2, GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL));
		GetSpeciesName(gStringVar3, GetMonData(&gEnemyParty[1], MON_DATA_SPECIES, NULL));
		GetSpeciesName(gStringVar1, GetMonData(&gEnemyParty[2], MON_DATA_SPECIES, NULL));
		GetSpeciesName(name, GetMonData(&gEnemyParty[3], MON_DATA_SPECIES, NULL));
		StringAppend(gStringVar1, gText_ObservatoryNameJoiner);
		StringAppend(gStringVar1, name);
	}
	else
	{
		GetSpeciesName(gStringVar1, GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL));
		GetSpeciesName(gStringVar2, GetMonData(&gEnemyParty[1], MON_DATA_SPECIES, NULL));
		GetSpeciesName(gStringVar3, GetMonData(&gEnemyParty[2], MON_DATA_SPECIES, NULL));
	}
}

// Swaps the opponent's revealed team into gPlayerParty so the party screen can show it off, with
// the summaries the player needs to choose against it.
void FrontierChallenge_BeginObservatoryView(void)
{
	u32 i;
	u8 numMons = NumEnteredMons();

	ZeroPlayerPartyMons();

	for (i = 0; i < numMons; ++i)
	{
		if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
			break;

		gPlayerParty[i] = gEnemyParty[i];
	}

	CalculatePlayerPartyCount();
	gFrontierPartyScreen = FRONTIER_SCREEN_OBSERVATORY_VIEW;
}

// Puts the player's own team back.
void FrontierChallenge_EndObservatoryView(void)
{
	gFrontierPartyScreen = FRONTIER_SCREEN_NONE;
	RestoreObservatoryTeam();
}

// Opens the screen the player sends out from - the same multi-select the frontier team is entered
// on, so Doubles picks both of its Pokemon at once and either format can read a summary first.
// GetNumMonsToSelectInFrontier reads the screen mode set here to ask for one or two rather than
// for a whole team.
void FrontierChallenge_BeginObservatoryPick(void)
{
	Memset(gSelectedOrderFromParty, 0, PARTY_SIZE);
	gFrontierPartyScreen = FRONTIER_SCREEN_OBSERVATORY_PICK;
}

// Cuts gPlayerParty down to the Pokemon being sent out, and says whether the player picked at all.
// gPlayerParty is rebuilt from the stored data rather than read: special 0xF5 zeroes it and refills three
// slots from an uninitialised buffer on the way out, which is exactly why the stored data exists.
//
// Returns: LastResult: FALSE if the player backed out without filling every slot, in which case
//			the team is put back and the script asks again.
//			gStringVar1 (and gStringVar2 in Doubles): the Pokemon being sent out.
void FrontierChallenge_SendOutObservatoryPicks(void)
{
	u32 i;
	u8 numPicks = NumObservatoryPicks();
	struct Pokemon picks[OBSERVATORY_MAX_PICKS];

	gFrontierPartyScreen = FRONTIER_SCREEN_NONE;

	for (i = 0; i < numPicks; ++i)
	{
		u32 j;
		u8 slot = gSelectedOrderFromParty[i];

		// 1-indexed, 0 meaning nothing was picked here. The screen will not offer the same
		// Pokemon twice, but two copies of one slot would be a whole battle fought wrong.
		if (slot == 0 || slot > NumEnteredMons())
			break;

		for (j = 0; j < i; ++j)
		{
			if (gSelectedOrderFromParty[j] == slot)
				break;
		}

		if (j < i)
			break;

		gObservatoryChosenSlots[i] = slot - 1;
		picks[i] = gObservatoryEnteredTeam[slot - 1];
	}

	if (i < numPicks)
	{
		RestoreObservatoryTeam();
		gSpecialVar_LastResult = FALSE;
		return;
	}

	ZeroPlayerPartyMons();

	for (i = 0; i < numPicks; ++i)
		gPlayerParty[i] = picks[i];

	CalculatePlayerPartyCount();

	GetSpeciesName(gStringVar1, GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL));
	GetSpeciesName(gStringVar2, GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL));
	gSpecialVar_LastResult = TRUE;
}

// Rebuilds the entered team after the battle, with whatever fought put back in the slot it came
// from. The frontier heals its Pokemon between battles, but end_battle.c only ever saw the one or
// two that were sent out, so the rest of the team is healed here.
void FrontierChallenge_RestoreObservatoryTeam(void)
{
	u32 i;
	u8 numPicks = NumObservatoryPicks();
	struct Pokemon fought[OBSERVATORY_MAX_PICKS];

	for (i = 0; i < numPicks; ++i)
		fought[i] = gPlayerParty[i];

	RestoreObservatoryTeam();

	for (i = 0; i < numPicks; ++i)
	{
		u8 slot = gObservatoryChosenSlots[i];

		if (slot < NumEnteredMons())
			gPlayerParty[slot] = fought[i];
	}

	for (i = 0; i < PARTY_SIZE; ++i)
	{
		if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE)
			HealMon(&gPlayerParty[i]);
	}

	CalculatePlayerPartyCount();
}

// Scores one of the AI's Pokemon against the team the player revealed.
// It can only read the same information the player could: the revealed Pokemon's species, types, ability and
// item, never which of them the player is actually sending out.
static s16 ScoreObservatoryMon(struct Pokemon* mon, struct Pokemon* revealed, u8 numRevealed)
{
	u32 i, j;
	s16 score = 0;
	u8 ability = GetMonAbility(mon);
	u8 damagingMoves = 0;
	bool8 hasPriority = FALSE;
	bool8 endures = GetMonData(mon, MON_DATA_HELD_ITEM, NULL) == ITEM_FOCUS_SASH
				 || ability == ABILITY_STURDY;

	for (j = 0; j < MAX_MON_MOVES; ++j)
	{
		u16 move = GetMonData(mon, MON_DATA_MOVE1 + j, NULL);

		if (move == MOVE_NONE || SPLIT(move) == SPLIT_STATUS)
			continue;

		++damagingMoves;

		if (PriorityCalcMon(mon, move) > 0)
			hasPriority = TRUE;
	}

	if (damagingMoves == 0)
		return OBSERVATORY_SCORE_NO_OFFENCE;

	for (i = 0; i < numRevealed; ++i)
	{
		struct Pokemon* foe = &revealed[i];
		u8 foeAbility;
		u8 best = 0; // 0 = cannot touch it, 1 = hits it for normal damage, 2 = super effective

		if (GetMonData(foe, MON_DATA_SPECIES, NULL) == SPECIES_NONE)
			continue;

		for (j = 0; j < MAX_MON_MOVES; ++j)
		{
			u16 move = GetMonData(mon, MON_DATA_MOVE1 + j, NULL);
			u8 moveType, flags = 0;

			if (move == MOVE_NONE || SPLIT(move) == SPLIT_STATUS)
				continue;

			moveType = GetMonMoveTypeSpecial(mon, move);
			TypeDamageModificationPartyMon(ability, foe, move, moveType, &flags);

			// Counter and Mirror Coat ignore the type chart; landing at all is the whole trick.
			if (gBattleMoves[move].effect == EFFECT_COUNTER || gBattleMoves[move].effect == EFFECT_MIRROR_COAT)
			{
				if (!(flags & MOVE_RESULT_NO_EFFECT))
					best = 2;
			}
			else if (flags & MOVE_RESULT_SUPER_EFFECTIVE)
				best = 2;
			else if (!(flags & (MOVE_RESULT_NO_EFFECT | MOVE_RESULT_NOT_VERY_EFFECTIVE)) && best < 1)
				best = 1;

			if (best == 2)
				break;
		}

		score += best;

		if (best == 2)
			score += 1; // Threatening a Pokemon outright is worth more than chipping it

		// And the other half of the matchup: a revealed Pokemon whose own types would come off it
		// super effectively is one this Pokemon would rather not be looking at.
		foeAbility = GetMonAbility(foe);

		for (j = 0; j < 2; ++j)
		{
			u8 flags = 0;
			u8 foeType = GetMonType(foe, j);

			if (j == 1 && foeType == GetMonType(foe, 0))
				break; // Single-typed

			TypeDamageModificationPartyMon(foeAbility, mon, MOVE_NONE, foeType, &flags);

			if (flags & MOVE_RESULT_SUPER_EFFECTIVE)
			{
				score -= 2;
				break;
			}
		}
	}

	if (endures)
		score += hasPriority ? 3 : 1;
	else if (hasPriority)
		score += 1;

	return score;
}

// Whether a beats b for the purposes of picking. Speed settles equal matchups, because moving
// first matters most in a battle neither side can switch out of, and a coin flip settles the rest
// so identical spreads do not always send out the same slot.
static bool8 IsBetterObservatoryPick(s16 scoreA, struct Pokemon* a, s16 scoreB, struct Pokemon* b)
{
	u16 speedA, speedB;

	if (scoreA != scoreB)
		return scoreA > scoreB;

	speedA = GetMonData(a, MON_DATA_SPEED, NULL);
	speedB = GetMonData(b, MON_DATA_SPEED, NULL);

	if (speedA != speedB)
		return speedA > speedB;

	return (Random() & 1) != 0;
}

// Picks who the AI sends out and cuts gEnemyParty down to them, the same way the player's picks
// cut down gPlayerParty. Doubles takes the two best.
// Returns: gStringVar1 (and gStringVar2 in Doubles): the Pokemon the opponent is sending out.
void FrontierChallenge_ChooseObservatoryOpponentMons(void)
{
	u32 i, j;
	u8 count = 0;
	u8 numPicks = NumObservatoryPicks();
	u8 numMons = NumEnteredMons();
	s16 scores[MAX_FRONTIER_TEAM_SIZE];
	u8 order[MAX_FRONTIER_TEAM_SIZE];
	struct Pokemon picks[OBSERVATORY_MAX_PICKS];

	for (i = 0; i < numMons; ++i)
	{
		if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
			continue;

		scores[count] = ScoreObservatoryMon(&gEnemyParty[i], gObservatoryEnteredTeam, numMons);
		order[count] = i;
		++count;
	}

	if (count == 0)
		return; // Nothing was built, so leave the team alone rather than emptying it

	// Selection sort, best first. Never more than four entries.
	for (i = 0; i < count; ++i)
	{
		for (j = i + 1; j < count; ++j)
		{
			if (IsBetterObservatoryPick(scores[j], &gEnemyParty[order[j]], scores[i], &gEnemyParty[order[i]]))
			{
				s16 score = scores[i];
				u8 slot = order[i];

				scores[i] = scores[j];
				order[i] = order[j];
				scores[j] = score;
				order[j] = slot;
			}
		}
	}

	if (numPicks > count)
		numPicks = count;

	for (i = 0; i < numPicks; ++i)
		picks[i] = gEnemyParty[order[i]];

	ZeroEnemyPartyMons();

	for (i = 0; i < numPicks; ++i)
		gEnemyParty[i] = picks[i];

	GetSpeciesName(gStringVar1, GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL));
	GetSpeciesName(gStringVar2, GetMonData(&gEnemyParty[1], MON_DATA_SPECIES, NULL));
}
