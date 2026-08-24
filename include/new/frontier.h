#pragma once

#include "../global.h"
#include "dynamax.h"
#include "pokemon_storage_system.h"

//Exported Functions
bool8 IsFrontierTrainerId(u16 trainerId);
u8 GetFrontierTrainerClassId(u16 trainerId, u8 battlerNum);
void CopyFrontierTrainerName(u8* dst, u16 trainerId, u8 battlerNum);
const u8* GetFrontierTrainerName(u16 trainerId, u8 battlerNum);
void CopyFrontierTrainerText(u8 whichText, u16 trainerId, u8 battlerNum);
u8 GetFrontierTrainerFrontSpriteId(u16 trainerId, u8 battlerNum);
u16 GetFrontierBrainOwNum(u16 brainId);
u8 GetFrontierBrainFrontSpriteId(u16 brainId);
u8 GetFrontierBrainGender(u16 brainId);
u16 TryGetSpecialFrontierTrainerMusic(u16 trainerId, u8 battlerNum);
u32 GetAIFlagsInBattleFrontier(unusedArg u8 bank);
u8 GetNumMonsOnTeamInFrontier(void);
bool8 IsFrontierSingles(u8 battleType);
bool8 IsFrontierDoubles(u8 battleType);
bool8 IsFrontierMulti(u8 battleType);
bool8 IsGSCupBattle();
bool8 IsRandomBattleTowerBattle();
bool8 RayquazaCanMegaEvolveInFrontierBattle();
bool8 DynamaxAllowedInTier(u8 tier);
u8 GetBattleFacilityLevel(u8 tier);
void UpdateTypesForCamomons(u8 bank);
u8 GetCamomonsTypeByMon(struct Pokemon* mon, u8 whichType);
//u8 GetCamomonsTypeBySpread(struct BattleTowerSpread* spread, u8 whichType); - Defined further down
u8 ShouldReplaceTypesWithCamomons(void);
bool8 DuplicateItemsAreBannedInTier(u8 tier, u8 battleType);
bool8 ShouldDisablePartyMenuItemsBattleTower(void);
const u8* GetFrontierTierName(u8 tier, u8 format);
bool8 InBattleSands(void);
bool8 IsAIControlledBattle(void);
bool8 IsStandardTier(u8 tier);
bool8 IsCamomonsTier(u8 tier);
bool8 IsLittleCupTier(u8 tier);
bool8 IsMiddleCupTier(u8 tier);
bool8 IsAverageMonsBattle(void);
bool8 Is350CupBattle(void);
bool8 IsScaleMonsBattle(void);
bool8 IsOnlyScalemonsGame(void);
bool8 IsCamomonsBattle(void);
bool8 IsBenjaminButterfreeBattle(void);
bool8 AreMegasZMovesBannedInTier(u8 tier);
bool8 IsMegaZMoveBannedBattle(void);
bool8 IsMoveBannedInRingChallenge(u16 move, u8 bank);
bool8 IsMoveBannedInRingChallengeByMon(u16 move, struct Pokemon* mon);
bool8 PokemonTierBan(const u16 species, const u16 item, const struct BattleTowerSpread* const spread, const struct Pokemon* const mon, const u8 tier, const u8 checkFromLocationType);
bool8 IsMonBannedInTier(struct Pokemon* mon, u8 tier);
bool8 IsSpeciesBannedInTier(u16 species, u16 tier, u16 battleFormat);
bool8 StreakRampAppliesInTier(u8 tier);
u8 GetCurrentFrontierFormat(void);
u16 GetFrontierStreak(u8 facility, u8 format, u8 currentOrMax);
void SetFrontierStreak(u8 facility, u8 format, u8 currentOrMax, u16 value);
u16 GetCurrentBattleFacilityStreak(void);
bool8 HasAchievedFrontierStreak(u16 target);
u8 GetFrontierBattleBackground(void);

//Functions Hooked In:
u16 sp052_GenerateFacilityTrainer(void);
void sp053_LoadFrontierIntroBattleMessage(void);
u16 sp054_GetBattleFacilityStreak(void);
void sp055_UpdateBattleFacilityStreak(void);
u16 sp056_DetermineChipsToGive(void);
void sp06C_SpliceFrontierTeamWithPlayerTeam(void);
u16 sp06D_LoadFrontierMultiTrainerById(void);
void sp06F_CanTeamParticipateInBattleMine(void);
u8 sp070_RandomizeBattleMineBattleOptions(void);

//Exported Constants
//#define TOTAL_SPREADS 0x4A0 //sizeof(gFrontierSpreads) / sizeof(struct BattleTowerSpreads)

#define NUM_MALE_NAMES gNumMaleFrontierTrainerNames
#define NUM_FEMALE_NAMES gNumFemaleFrontierTrainerNames
#define NUM_TOWER_TRAINERS gNumTowerTrainers
#define NUM_SPECIAL_TOWER_TRAINERS gNumSpecialTowerTrainers
#define NUM_FRONTIER_BRAINS gNumFrontierBrains

#define RAID_BATTLE_MULTI_TRAINER_TID 0x395 //Trainer Index
#define BATTLE_FACILITY_MULTI_TRAINER_TID 0x396 //Trainer Index
#define FRONTIER_BRAIN_TID 0x397 //Trainer Index
#define BATTLE_TOWER_SPECIAL_TID 0x398 //Trainer Index
#define BATTLE_TOWER_TID 0x399 //Trainer Index


enum BattleFacilities
{
	IN_BATTLE_TOWER,
	IN_BATTLE_SANDS,
	IN_BATTLE_MINE,
	IN_BATTLE_CIRCUS,
	IN_BATTLE_FACTORY,
	IN_RING_CHALLENGE,
	IN_ISLE_CHALLENGE,
	IN_BATTLE_MAZE,
	NUM_BATTLE_FACILITIES,
};

#define BATTLE_FACILITY_NUM VarGet(0x403A)
#define SET_BATTLE_FACILITY_NUM(num) VarSet(0x403A, (num))

enum
{
	FRONTIER_BEFORE_TEXT,
	FRONTIER_PLAYER_LOST_TEXT,
	FRONTIER_PLAYER_WON_TEXT,
};

enum BattleTowerBattleTypes
{
	BATTLE_FACILITY_SINGLE,
	BATTLE_FACILITY_DOUBLE,
	BATTLE_FACILITY_MULTI,
	BATTLE_FACILITY_LINK_MULTI,
	BATTLE_FACILITY_SINGLE_RANDOM,
	BATTLE_FACILITY_DOUBLE_RANDOM,
	BATTLE_FACILITY_MULTI_RANDOM,
};

#define NUM_TOWER_BATTLE_TYPES (BATTLE_FACILITY_MULTI_RANDOM + 1)

enum BattleTowerFormats
{
	BATTLE_FACILITY_STANDARD,
	BATTLE_FACILITY_NO_RESTRICTIONS,
	BATTLE_FACILITY_OU,
	BATTLE_FACILITY_UBER,
	BATTLE_FACILITY_LITTLE_CUP,
	BATTLE_FACILITY_MIDDLE_CUP, //GS Cup in Doubles
	BATTLE_FACILITY_MONOTYPE,
	BATTLE_FACILITY_CAMOMONS,
	BATTLE_FACILITY_UBER_CAMOMONS,
	BATTLE_FACILITY_LC_CAMOMONS,
	BATTLE_FACILITY_MC_CAMOMONS,
	BATTLE_FACILITY_SCALEMONS,
	BATTLE_FACILITY_350_CUP,
	BATTLE_FACILITY_AVERAGE_MONS,
	BATTLE_FACILITY_BENJAMIN_BUTTERFREE,
	BATTLE_FACILITY_MEGA_BRAWL,
	BATTLE_FACILITY_DYNAMAX_STANDARD,
	BATTLE_FACILITY_NATIONAL_DEX_OU,
	BATTLE_FACILITY_METRONOME,
	BATTLE_FACILITY_UU,
	BATTLE_FACILITY_RU,
	BATTLE_FACILITY_NU,
	BATTLE_MINE_FORMAT_1, //OU, Camomons, Benjamin Butterfree
	BATTLE_MINE_FORMAT_2, //Scalemons, 350 Cup, Averagemons
	BATTLE_MINE_FORMAT_3, //Little Cup, Little Cup Camomons
	BATTLE_MINE_FORMAT_4, //Ubers, Ubers Camomons
	NUM_TIERS
};

#define NUM_FORMATS_OLD (BATTLE_FACILITY_MIDDLE_CUP + 1) //Monotype not included b/c wasn't included in Battle Tower Demo original release

#define BATTLE_FACILITY_GS_CUP BATTLE_FACILITY_MIDDLE_CUP //Replaces Middle Cup in Doubles

#define NUM_BATTLE_TOWER_TIERS 8
#define NUM_BATTLE_MINE_TIERS 3
#define NUM_BATTLE_CIRCUS_TIERS 14
#define IS_SINGLE_100_RECORD_TIER(tier) (BATTLE_FACILITY_NUM == IN_BATTLE_TOWER && (tier == BATTLE_FACILITY_MONOTYPE || tier == BATTLE_FACILITY_DYNAMAX_STANDARD))

enum BattleTowerGenders
{
	BATTLE_FACILITY_MALE,
	BATTLE_FACILITY_FEMALE,
};

enum BattlerIds
{
	BATTLE_FACILITY_TRAINER_A,
	BATTLE_FACILITY_TRAINER_B,
	BATTLE_FACILITY_PARTNER,
};

enum FrontierSpreadAbilityNumbers
{
	FRONTIER_ABILITY_HIDDEN,
	FRONTIER_ABILITY_1,
	FRONTIER_ABILITY_2,
};

enum
{
	CURR_STREAK,
	MAX_STREAK,
};

#define FRONTIER_FIRST_MILESTONE_STREAK 20
#define FRONTIER_SECOND_MILESTONE_STREAK 50

enum
{
	DOUBLES_ANY_TEAM,
	DOUBLES_SUN_TEAM,
	DOUBLES_SAND_TEAM,
	DOUBLES_RAIN_TEAM,
	DOUBLES_HAIL_TEAM,
	DOUBLES_ELECTRIC_TERRAIN_TEAM,
	DOUBLES_PSYCHIC_TERRAIN_TEAM,
	DOUBLES_TRICK_ROOM_TEAM,
	DOUBLES_TAILWIND_TEAM,
	DOUBLES_HYPER_OFFENSE_TEAM,
	DOUBLES_JUSTIFIED_TEAM,
};

//Exported Data Structures
extern const u16 gNumMaleFrontierTrainerNames;
extern const u16 gNumFemaleFrontierTrainerNames;
extern const u16 gNumTowerTrainers;
extern const u16 gNumSpecialTowerTrainers;
extern const u16 gNumFrontierBrains;

struct BattleTowerSpread
{
    u16 species;
	u8 nature;
	u8 ball;
	u32 hpIv : 5;
	u32 atkIv : 5;
	u32 defIv : 5;
	u32 spdIv : 5;
	u32 spAtkIv : 5;
	u32 spDefIv : 5;
	u8 hpEv;
	u8 atkEv;
	u8 defEv;
	u8 spdEv;
	u8 spAtkEv;
	u8 spDefEv;
	u16 item;
	u16 moves[MAX_MON_MOVES];
	u8 specificTeamType;
	u8 shiny : 1;
	u8 forSingles : 1;
	u8 forDoubles : 1;
	u8 modifyMovesDoubles : 1;
	u8 ability : 2;
	u8 gigantamax : 1;
};

extern const struct BattleTowerSpread gFrontierSpreads[];
extern const struct BattleTowerSpread gFrontierLegendarySpreads[];
extern const u16 gNumFrontierSpreads;
extern const u16 gNumFrontierLegendarySpreads;
//#define gFrontierSpreads ((const struct BattleTowerSpread*) 0x89DFA00)

struct BattleTowerTrainer
{
    u16 owNum;
	u8 trainerClass;
	u8 trainerSprite;
	u8 gender;
	const u8* preBattleText;
	const u8* playerWinText;
	const u8* playerLoseText;
};

extern const struct BattleTowerTrainer gTowerTrainers[];

struct SpecialBattleFrontierTrainer //Also for Frontier Brains
{
    u16 owNum;
	u8 trainerClass;
	u8 trainerSprite;
	u8 gender;
	u8 isMonotype;
	const u8* name;
	const u8* preBattleText;
	const u8* playerWinText;
	const u8* playerLoseText;
	const struct BattleTowerSpread* regularSpreads;
	const struct BattleTowerSpread* middleCupSpreads;
	const struct BattleTowerSpread* littleCupSpreads;
	const struct BattleTowerSpread* legendarySpreads;
	u16 regSpreadSize;
	u16 mcSpreadSize;
	u16 lcSpreadSize;
	u16 legSpreadSize;
	u16 songId;
};

extern const struct SpecialBattleFrontierTrainer gSpecialTowerTrainers[];
extern const struct SpecialBattleFrontierTrainer gFrontierBrains[];

struct MultiBattleTowerTrainer
{
	u16 owNum;
	u8 trainerClass;
	u8 backSpriteId;
	u8 gender;
	const u8* name;
	u32 otId;
	const struct BattleTowerSpread* regularSpreads;
	const struct BattleTowerSpread* legendarySpreads;
	const struct BattleTowerSpread* littleCupSpreads;
	u16 regSpreadSize;
	u16 legSpreadSize;
	u16 lcSpreadSize;
};

extern const struct MultiBattleTowerTrainer gFrontierMultiBattleTrainers[];
extern const u8 gNumFrontierMultiTrainers;

struct MultiRaidTrainer
{
	u16 owNum;
	u8 trainerClass;
	u8 backSpriteId;
	u8 gender;
	u32 otId;
	const u8* name;
	const struct BattleTowerSpread* spreads[RAID_STAR_COUNT];
	u16 spreadSizes[RAID_STAR_COUNT];
};

extern const struct MultiRaidTrainer gRaidPartners[];
extern const u8 gNumRaidPartners;

// Amethyst only supports a single tier per facility/format
enum FrontierStreakFormats
{
	FRONTIER_FORMAT_SINGLES,
	FRONTIER_FORMAT_DOUBLES,
	NUM_FRONTIER_FORMATS,
};

enum FrontierChallengeStates
{
	FRONTIER_NONE,
	FRONTIER_ACTIVE,	//Only ever seen on disk after a session that ended without Resting
	FRONTIER_RESTING,
};

// The number of music choices - enforced by a #define so newly added songs trigger compilation errors
// if they are not fully configured (ex. here, in multichoice lists, etc.)
#define NUM_FRONTIER_MUSIC_CHOICES 17
#define FRONTIER_MUSIC_DEFAULT_CHOICE 0

extern const u8* const gFrontierMusicChoiceNames[NUM_FRONTIER_MUSIC_CHOICES + 1];
extern const u16 gFrontierMusicChoiceSongs[NUM_FRONTIER_MUSIC_CHOICES];

// Which song is currently selected (highlighted in green)
u8 GetCurrentFrontierMusicChoice(void);
u8 GetCurrentFrontierBackgroundChoice(void);

// Like music above, but with the default background called out explicitly so it can be referenced
// in scripts setting the background graphic (since Random isn't a background itself)
#define NUM_FRONTIER_BACKGROUND_CHOICES 25
#define FRONTIER_BACKGROUND_DEFAULT_CHOICE 0
#define FRONTIER_BACKGROUND_RANDOM_CHOICE 1

extern const u8* const gFrontierBackgroundChoiceNames[NUM_FRONTIER_BACKGROUND_CHOICES + 1];
extern const u8 gFrontierBackgroundChoiceTerrains[NUM_FRONTIER_BACKGROUND_CHOICES];

// The player's pick, and what "Random" turned into for the battle about to be fought.
struct FrontierBackground
{
	u8 choice;			// Index into gFrontierBackgroundChoiceNames
	u8 rolledChoice;	// The same, standing in for choice while it reads Random
};

// Game modifiers are disabled during the frontier and restored after; this captures the state
// of modifiers for restoration (incl. which are overridden and which choices are selected for things like weather)
struct FrontierModifierBackup
{
	/*0x0*/ u8 overridden;
	/*0x1*/ u8 weather;
	/*0x2*/ u8 terrain;
	/*0x4*/ u32 flags; //Bit n = gFrontierOverriddenModifierFlags[n] was set
}; /*SIZE = 0x8*/

//Addresses in BPRE.ld. SaveBlock1.frontierRecords free space is 0x202682C - 0x2027434.
extern u16 gFrontierStreaks[NUM_BATTLE_FACILITIES][NUM_FRONTIER_FORMATS][/*CURRENT_OR_MAX*/ 2]; //0x2026840
// Every facility/format/streak is saved individually, to allow the player to pause and resume any streak without interrupting others
extern u8 gFrontierRunStates[NUM_BATTLE_FACILITIES][NUM_FRONTIER_FORMATS]; //0x2026880
extern struct FrontierModifierBackup gFrontierModifierBackup; //0x2026890
extern struct FrontierBackground gFrontierBackground; //0x2026898

extern const u8* const gBattleFrontierTierNames[NUM_TIERS];
extern const u8* const gBattleFacilityNames[NUM_BATTLE_FACILITIES];

extern const species_t gGSCup_LegendarySpeciesList[];
extern const species_t gSmogonLittleCup_SpeciesList[];
extern const species_t gMiddleCup_SpeciesList[];
extern const ability_t gSmogonOU_AbilityBanList[];
extern const ability_t gSmogonOUDoubles_AbilityBanList[];
extern const ability_t gSmogonMonotype_AbilityBanList[];
extern const ability_t gMiddleCup_AbilityBanList[];
extern const ability_t gSmogonAverageMons_AbilityBanList[];
extern const ability_t gSmogon350Cup_AbilityBanList[];
extern const ability_t gSmogonScalemons_AbilityBanList[];
extern const ability_t gSmogonMetronome_AbilityBanList[];
extern const ability_t gSmogonUU_AbilityBanList[];
extern const ability_t gSmogonRU_AbilityBanList[];
extern const item_t gBattleTowerStandard_ItemBanList[];
extern const item_t gSmogonOU_ItemBanList[];
extern const item_t gSmogonNationalDexOU_ItemBanList[];
extern const item_t gSmogonOUDoubles_ItemBanList[];
extern const item_t gSmogonLittleCup_ItemBanList[];
extern const item_t gSmogonMonotype_ItemBanList[];
extern const item_t gMiddleCup_ItemBanList[];
extern const item_t gSmogonAverageMons_ItemBanList[];
extern const item_t gSmogon350Cup_ItemBanList[];
extern const item_t gSmogonScalemons_ItemBanList[];
extern const item_t gSmogonMetronome_ItemBanList[];
extern const item_t gSmogonUU_ItemBanList[];
extern const item_t gSmogonRU_ItemBanList[];
extern const item_t gSmogonNU_ItemBanList[];
extern const move_t gRingChallenge_MoveBanList[];
extern const move_t gSmogon_MoveBanList[];
extern const move_t gSmogonOUDoubles_MoveBanList[];
extern const move_t gSmogonLittleCup_MoveBanList[];
extern const move_t gSmogonAverageMons_MoveBanList[];

u8 GetCamomonsTypeBySpread(const struct BattleTowerSpread* spread, u8 whichType);
