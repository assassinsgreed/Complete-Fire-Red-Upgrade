#include "defines.h"
#include "defines_battle.h"
#include "../include/event_data.h"
#include "../include/field_weather.h"
#include "../include/item.h"
#include "../include/random.h"
#include "../include/script.h"
#include "../include/string_util.h"
#include "../include/constants/event_objects.h"
#include "../include/constants/items.h"
#include "../include/constants/trainers.h"

#include "../include/new/battle_start_turn_start.h"
#include "../include/new/build_pokemon.h"
#include "../include/new/damage_calc.h"
#include "../include/new/frontier.h"
#include "../include/new/mega.h"
#include "../include/new/pokemon_storage_system.h"
#include "../include/new/species_tables.h"
#include "../include/new/util.h"
#include "../include/new/battle_util.h"

/*
frontier.c
	all supporting and master functions for developing a battle frontier

tables to edit:
	gBattleFacilityNames
	gBattleFrontierTierNames
	gBattleFrontierFormats
	sBattleSimEffectDescriptions

*/

extern u8* gMaleFrontierNamesTable[];
extern u8* gFemaleFrontierNamesTable[];

extern const u8 sTrainerName_Rival[]; //Sentinel - swapped for the player's chosen rival name below

extern const u8 gText_BattleTower[];
extern const u8 gText_BattleSands[];
extern const u8 gText_BattleQuarry[];
extern const u8 gText_BattleSim[];
extern const u8 gText_BattleFactory[];
extern const u8 gText_BattleObservatory[];
extern const u8 gText_BattleIsle[];
extern const u8 gText_BattleMaze[];

extern const u8 gText_SingleBattle[];
extern const u8 gText_DoubleBattle[];
extern const u8 gText_MultiBattle[];
extern const u8 gText_LinkMultiBattle[];
extern const u8 gText_RandomSingleBattle[];
extern const u8 gText_RandomDoubleBattle[];
extern const u8 gText_RandomMultiBattle[];

extern const u8 gText_BattleTowerStandard[];
extern const u8 gText_NoRestrictions[];
extern const u8 gText_SmogonGen7OU[];
extern const u8 gText_SmogonOUDoubles[];
extern const u8 gText_SmogonGen7Uber[];
extern const u8 gText_SmogonLittleCup[];
extern const u8 gText_MiddleCup[];
extern const u8 gText_SmogonMonotype[];
extern const u8 gText_GSCup[];
extern const u8 gText_GSCupCamomons[];
extern const u8 gText_SmogonCamomons[];
extern const u8 gText_UberCamomons[];
extern const u8 gText_LittleCupCamomons[];
extern const u8 gText_MiddleCupCamomons[];
extern const u8 gText_SmogonScalemons[];
extern const u8 gText_Smogon350Cup[];
extern const u8 gText_SmogonAveragemons[];
extern const u8 gText_SmogonBenjaminButterfree[];
extern const u8 gText_MegaBrawl[];
extern const u8 gText_DynamaxStandard[];
extern const u8 gText_NationalDexOU[];
extern const u8 gText_SmogonMetronome[];
extern const u8 gText_SmogonGen7UU[];
extern const u8 gText_SmogonGen7RU[];
extern const u8 gText_SmogonGen7NU[];
extern const u8 gText_On[];
extern const u8 gText_Off[];
extern const u8 gText_BeAble[];
extern const u8 gText_NotBeAble[];
extern const u8 gText_Previous[];
extern const u8 gText_Current[];
extern const u8 gText_Max[];
extern const u8 gText_None[];

extern const u8 gText_BattleSimDescriptionElectricTerrain[];
extern const u8 gText_BattleSimDescriptionGrassyTerrain[];
extern const u8 gText_BattleSimDescriptionMistyTerrain[];
extern const u8 gText_BattleSimDescriptionPsychicTerrain[];
extern const u8 gText_BattleSimDescriptionRain[];
extern const u8 gText_BattleSimDescriptionSun[];
extern const u8 gText_BattleSimDescriptionSandstorm[];
extern const u8 gText_BattleSimDescriptionHail[];
extern const u8 gText_BattleSimDescriptionDeltaStream[];
extern const u8 gText_BattleSimDescriptionTrickRoom[];
extern const u8 gText_BattleSimDescriptionMagicRoom[];
extern const u8 gText_BattleSimDescriptionWonderRoom[];
extern const u8 gText_BattleSimDescriptionGravity[];
extern const u8 gText_BattleSimDescriptionMagnetRise[];
extern const u8 gText_BattleSimDescriptionFairyLock[];
extern const u8 gText_BattleSimDescriptionPixies[];
extern const u8 gText_BattleSimDescriptionBadThoughts[];
extern const u8 gText_BattleSimDescriptionInverseBattle[];
extern const u8 gText_BattleSimDescriptionDynamax[];
extern const u8 gText_BattleSimDescriptionTradeMon[];
extern const u8 gText_BattleSimDescriptionSafeguard[];
extern const u8 gText_BattleSimDescriptionMist[];
extern const u8 gText_BattleSimDescriptionSeaOfFire[];
extern const u8 gText_BattleSimDescriptionRainbow[];
extern const u8 gText_BattleSimDescriptionConfused[];
extern const u8 gText_BattleSimDescriptionTaunt[];
extern const u8 gText_BattleSimDescriptionTorment[];
extern const u8 gText_BattleSimDescriptionHealBlock[];
extern const u8 gText_BattleSimDescriptionThroatChop[];
extern const u8 gText_BattleSimDescriptionAlwaysCrit[];
extern const u8 gText_BattleSimDescriptionNoCrits[];
extern const u8 gText_BattleSimDescriptionAbilitySuppression[];

// The battle frontier does not use tiers in Amethyst.

const u8* const gBattleFacilityNames[NUM_BATTLE_FACILITIES] =
{
	[IN_BATTLE_TOWER] = gText_BattleTower,
	[IN_BATTLE_SANDS] = gText_BattleSands,
	[IN_BATTLE_QUARRY] = gText_BattleQuarry,
	[IN_BATTLE_SIM] = gText_BattleSim,
	[IN_BATTLE_FACTORY] = gText_BattleFactory,
	[IN_BATTLE_OBSERVATORY] = gText_BattleObservatory,
	[IN_BATTLE_ISLE] = gText_BattleIsle,
	[IN_BATTLE_MAZE] = gText_BattleMaze,
};

const u8* const gBattleFrontierTierNames[NUM_TIERS] =
{
	[BATTLE_FACILITY_STANDARD] = gText_BattleTowerStandard,
	[BATTLE_FACILITY_NO_RESTRICTIONS] = gText_NoRestrictions,
	[BATTLE_FACILITY_OU] = gText_SmogonGen7OU,
	[BATTLE_FACILITY_UBER] gText_SmogonGen7Uber,
	[BATTLE_FACILITY_LITTLE_CUP] = gText_SmogonLittleCup,
	[BATTLE_FACILITY_MIDDLE_CUP] = gText_MiddleCup,
	[BATTLE_FACILITY_MONOTYPE] = gText_SmogonMonotype,
	[BATTLE_FACILITY_CAMOMONS] = gText_SmogonCamomons,
	[BATTLE_FACILITY_UBER_CAMOMONS] = gText_UberCamomons,
	[BATTLE_FACILITY_LC_CAMOMONS] = gText_LittleCupCamomons,
	[BATTLE_FACILITY_MC_CAMOMONS] = gText_MiddleCupCamomons,
	[BATTLE_FACILITY_SCALEMONS] = gText_SmogonScalemons,
	[BATTLE_FACILITY_350_CUP] = gText_Smogon350Cup,
	[BATTLE_FACILITY_AVERAGE_MONS] = gText_SmogonAveragemons,
	[BATTLE_FACILITY_BENJAMIN_BUTTERFREE] = gText_SmogonBenjaminButterfree,
	[BATTLE_FACILITY_MEGA_BRAWL] = gText_MegaBrawl,
	[BATTLE_FACILITY_DYNAMAX_STANDARD] = gText_DynamaxStandard,
	[BATTLE_FACILITY_NATIONAL_DEX_OU] = gText_NationalDexOU,
	[BATTLE_FACILITY_METRONOME] = gText_SmogonMetronome,
	[BATTLE_FACILITY_UU] = gText_SmogonGen7UU,
	[BATTLE_FACILITY_NU] = gText_SmogonGen7RU,
	[BATTLE_FACILITY_RU] = gText_SmogonGen7NU,
};

const u8* const gBattleFrontierFormats[NUM_TOWER_BATTLE_TYPES] =
{
	[BATTLE_FACILITY_SINGLE] = gText_SingleBattle,
	[BATTLE_FACILITY_DOUBLE] = gText_DoubleBattle,
	[BATTLE_FACILITY_MULTI] = gText_MultiBattle,
	[BATTLE_FACILITY_LINK_MULTI] = gText_LinkMultiBattle,
	[BATTLE_FACILITY_SINGLE_RANDOM] = gText_RandomSingleBattle,
	[BATTLE_FACILITY_DOUBLE_RANDOM] = gText_RandomDoubleBattle,
	[BATTLE_FACILITY_MULTI_RANDOM] = gText_RandomMultiBattle,
};

const u8* const sBattleSimEffectDescriptions[] =
{
	gText_BattleSimDescriptionElectricTerrain,
	gText_BattleSimDescriptionGrassyTerrain,
	gText_BattleSimDescriptionMistyTerrain,
	gText_BattleSimDescriptionPsychicTerrain,
	gText_BattleSimDescriptionRain,
	gText_BattleSimDescriptionSun,
	gText_BattleSimDescriptionSandstorm,
	gText_BattleSimDescriptionHail,
	gText_BattleSimDescriptionDeltaStream,
	gText_BattleSimDescriptionTrickRoom,
	gText_BattleSimDescriptionMagicRoom,
	gText_BattleSimDescriptionWonderRoom,
	gText_BattleSimDescriptionGravity,
	gText_BattleSimDescriptionMagnetRise,
	gText_BattleSimDescriptionFairyLock,
	gText_BattleSimDescriptionPixies,
	gText_BattleSimDescriptionBadThoughts,
	gText_BattleSimDescriptionInverseBattle,
	gText_BattleSimDescriptionDynamax,
	gText_BattleSimDescriptionTradeMon,
	//Side Effects
	gText_BattleSimDescriptionSafeguard,
	gText_BattleSimDescriptionMist,
	gText_BattleSimDescriptionSeaOfFire,
	gText_BattleSimDescriptionRainbow,
	//Personal Effects
	gText_BattleSimDescriptionConfused,
	gText_BattleSimDescriptionTaunt,
	gText_BattleSimDescriptionTorment,
	gText_BattleSimDescriptionHealBlock,
	gText_BattleSimDescriptionThroatChop,
	gText_BattleSimDescriptionAlwaysCrit,
	gText_BattleSimDescriptionNoCrits,
	gText_BattleSimDescriptionAbilitySuppression,
};


// The trainer table holds Male Casey, but needs to be flipped based on player gender
static bool8 UseFemaleCaseyFrontierBrain(u16 brainId)
{
	return gFrontierBrains[brainId].owNum == EVENT_OBJ_GFX_CASEY_M && gSaveBlock2->playerGender == MALE;
}

u16 GetFrontierBrainOwNum(u16 brainId)
{
	return UseFemaleCaseyFrontierBrain(brainId) ? EVENT_OBJ_GFX_CASEY_F : gFrontierBrains[brainId].owNum;
}

u8 GetFrontierBrainFrontSpriteId(u16 brainId)
{
	return UseFemaleCaseyFrontierBrain(brainId) ? TRAINER_PIC_CASEY_F : gFrontierBrains[brainId].trainerSprite;
}

u8 GetFrontierBrainGender(u16 brainId)
{
	return UseFemaleCaseyFrontierBrain(brainId) ? BATTLE_FACILITY_FEMALE : gFrontierBrains[brainId].gender;
}

u8 GetFrontierTrainerClassId(u16 trainerId, u8 battlerNum)
{
	switch (trainerId) {
		case BATTLE_TOWER_TID:
			return gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].trainerClass;
		case BATTLE_TOWER_SPECIAL_TID:
			return gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].trainerClass;
		case FRONTIER_BRAIN_TID:
			return gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].trainerClass;
		case BATTLE_FACILITY_MULTI_TRAINER_TID:
			return gFrontierMultiBattleTrainers[VarGet(VAR_FACILITY_TRAINER_ID_PARTNER)].trainerClass;
		case RAID_BATTLE_MULTI_TRAINER_TID:
			return gRaidPartners[VarGet(VAR_FACILITY_TRAINER_ID_PARTNER)].trainerClass;
		default:
			return GET_TRAINER(trainerId).trainerClass;
	}
}

bool8 IsFrontierTrainerId(u16 trainerId)
{
	switch (trainerId) {
		case BATTLE_TOWER_TID:
		case BATTLE_TOWER_SPECIAL_TID:
		case FRONTIER_BRAIN_TID:
		case BATTLE_FACILITY_MULTI_TRAINER_TID:
		case RAID_BATTLE_MULTI_TRAINER_TID:
			return TRUE;
	}
	
	return FALSE;
}

void CopyFrontierTrainerName(u8* dst, u16 trainerId, u8 battlerNum)
{
	int i;
	const u8* name = GetFrontierTrainerName(trainerId, battlerNum);

	for (i = 0; name[i] != EOS; ++i)
		dst[i] = name[i];

	dst[i] = EOS;
}

const u8* GetFrontierTrainerName(u16 trainerId, u8 battlerNum)
{
	const u8* name;
	u16 partnerId;

	switch (trainerId) {
		case BATTLE_TOWER_TID: ;
			u16 nameId = (battlerNum == 0) ? VarGet(VAR_BATTLE_FACILITY_TRAINER1_NAME) : VarGet(VAR_BATTLE_FACILITY_TRAINER2_NAME);

			if (gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].gender == BATTLE_FACILITY_MALE)
			{
				if (nameId == 0xFFFF)
					nameId = Random() % NUM_MALE_NAMES;

				name = gMaleFrontierNamesTable[nameId];
			}
			else
			{
				if (nameId == 0xFFFF)
					nameId = Random() % NUM_FEMALE_NAMES;

				name = gFemaleFrontierNamesTable[nameId];
			}

			if (battlerNum == 0)
				VarSet(VAR_BATTLE_FACILITY_TRAINER1_NAME, nameId);
			else
				VarSet(VAR_BATTLE_FACILITY_TRAINER2_NAME, nameId);
			break;
		case BATTLE_TOWER_SPECIAL_TID:
			name = gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].name;
			break;
		case FRONTIER_BRAIN_TID:
			name = gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].name;
			break;
		case BATTLE_FACILITY_MULTI_TRAINER_TID:
			partnerId = VarGet(VAR_FACILITY_TRAINER_ID_PARTNER);
			name = TryGetRivalNameByTrainerClass(gFrontierMultiBattleTrainers[partnerId].trainerClass);

			if (name == NULL) //Rival name isn't tied to a trainer class
				name = gFrontierMultiBattleTrainers[partnerId].name;
			break;
		case RAID_BATTLE_MULTI_TRAINER_TID:
			partnerId = VarGet(VAR_FACILITY_TRAINER_ID_PARTNER);
			name = TryGetRivalNameByTrainerClass(gRaidPartners[partnerId].trainerClass);

			if (name == NULL) //Rival name isn't tied to a trainer class
				name = gRaidPartners[partnerId].name;
			break;
		default:
			name = TryGetRivalNameByTrainerClass(GET_TRAINER(trainerId).trainerClass);
			if (name == NULL) //Rival name isn't tied to a trainer class
				name = GET_TRAINER(trainerId).trainerName;
			break;
	}

	// Any trainer with this name will have it replaced with the player-given rival name.
	// Realistically, this is only used for the actual rival.
	if (name == sTrainerName_Rival)
		name = GetExpandedPlaceholder(ExpandPlaceholder_RivalName);

	return ReturnEmptyStringIfNull(name);
}

void CopyFrontierTrainerText(u8 whichText, u16 trainerId, u8 battlerNum)
{
	switch (trainerId) {
		case BATTLE_TOWER_TID:
			switch (whichText) {
				case FRONTIER_BEFORE_TEXT:
					StringCopy(gStringVar4, (gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].preBattleText));
					break;

				case FRONTIER_PLAYER_LOST_TEXT:
					StringCopy(gStringVar4, (gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerLoseText));
					break;

				case FRONTIER_PLAYER_WON_TEXT:
					StringCopy(gStringVar4, (gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerWinText));
			}
			break;
		case BATTLE_TOWER_SPECIAL_TID:
			switch (whichText) {
				case FRONTIER_BEFORE_TEXT:
					StringCopy(gStringVar4, (gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].preBattleText));
					break;

				case FRONTIER_PLAYER_LOST_TEXT:
					StringCopy(gStringVar4, (gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerLoseText));
					break;

				case FRONTIER_PLAYER_WON_TEXT:
					StringCopy(gStringVar4, (gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerWinText));
			}
			break;
		case FRONTIER_BRAIN_TID:
		default:
			switch (whichText) {
				case FRONTIER_BEFORE_TEXT:
					if (gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].preBattleText != NULL)
						StringCopy(gStringVar4, gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].preBattleText);
					break;

				case FRONTIER_PLAYER_LOST_TEXT:
					if (gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerLoseText != NULL)
						StringCopy(gStringVar4, (gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerLoseText));
					else //Frontier Brain text can be loaded from the OW
						StringCopy(gStringVar4, GetTrainerAWinText());
					break;

				case FRONTIER_PLAYER_WON_TEXT:
					if (gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerWinText != NULL)
						StringCopy(gStringVar4, (gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].playerWinText));
					else //Frontier Brain text can be loaded from the OW
						StringCopy(gStringVar4, GetTrainerALoseText());
			}
			break;
	}
}

u8 GetFrontierTrainerFrontSpriteId(u16 trainerId, u8 battlerNum)
{
	switch (trainerId) {
		case BATTLE_TOWER_TID:
			return gTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].trainerSprite;
		case BATTLE_TOWER_SPECIAL_TID:
			return gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].trainerSprite;
		case FRONTIER_BRAIN_TID:
			return GetFrontierBrainFrontSpriteId(VarGet(VAR_FACILITY_TRAINER_ID + battlerNum));
		default:
			return GET_TRAINER(trainerId).trainerPic;
	}
}

u16 TryGetSpecialFrontierTrainerMusic(u16 trainerId, u8 battlerNum)
{
	switch (trainerId) {
		case BATTLE_TOWER_SPECIAL_TID:
			return gSpecialTowerTrainers[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].songId;
		case FRONTIER_BRAIN_TID:
			return gFrontierBrains[VarGet(VAR_FACILITY_TRAINER_ID + battlerNum)].songId;
		default:
			return 0;
	}
}

u32 GetAIFlagsInBattleFrontier(unusedArg u8 bank)
{
	return AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_CHECK_GOOD_MOVE;
}

u8 GetNumMonsOnTeamInFrontier(void)
{
	if (FlagGet(FLAG_BATTLE_FACILITY))
		return MathMin(MathMax(1, VarGet(VAR_BATTLE_FACILITY_POKE_NUM)), PARTY_SIZE);
	else
		return 3; //Regular multi battle
}

bool8 IsFrontierSingles(u8 battleType)
{
	return battleType == BATTLE_FACILITY_SINGLE
		|| battleType == BATTLE_FACILITY_SINGLE_RANDOM;
}

bool8 IsFrontierDoubles(u8 battleType)
{
	return battleType == BATTLE_FACILITY_DOUBLE
		|| battleType == BATTLE_FACILITY_DOUBLE_RANDOM;
}

bool8 IsFrontierMulti(u8 battleType)
{
	return battleType == BATTLE_FACILITY_MULTI
		|| battleType == BATTLE_FACILITY_MULTI_RANDOM
		|| battleType == BATTLE_FACILITY_LINK_MULTI;
}

bool8 IsRandomBattleTowerBattle()
{
	u8 battleType = VarGet(VAR_BATTLE_FACILITY_BATTLE_TYPE);

	return battleType == BATTLE_FACILITY_SINGLE_RANDOM
		|| battleType == BATTLE_FACILITY_DOUBLE_RANDOM
		|| battleType == BATTLE_FACILITY_MULTI_RANDOM;
}

bool8 IsGSCupBattle()
{
	u8 battleType = VarGet(VAR_BATTLE_FACILITY_BATTLE_TYPE);

	return (IsFrontierDoubles(battleType) || IsFrontierMulti(battleType))
		&&  VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_GS_CUP;
}

bool8 DuplicateItemsAreBannedInTier(u8 tier, u8 battleType)
{
	if (tier == BATTLE_FACILITY_STANDARD
	||  tier == BATTLE_FACILITY_MEGA_BRAWL
	||  tier == BATTLE_FACILITY_DYNAMAX_STANDARD)
		return TRUE;

	return !IsFrontierSingles(battleType) && tier == BATTLE_FACILITY_GS_CUP;
}

bool8 RayquazaCanMegaEvolveInFrontierBattle(void)
{
	return IsGSCupBattle()
		|| VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_NO_RESTRICTIONS
		|| IsScaleMonsBattle();
}

bool8 DynamaxAllowedInTier(u8 tier)
{
	return FALSE;
}

// Everything fights at FRONTIER_LEVEL.
u8 GetBattleFacilityLevel(unusedArg u8 tier)
{
	u8 level = VarGet(VAR_BATTLE_FACILITY_POKE_LEVEL);

	return MathMax(1, MathMin(level, MAX_LEVEL));
}

u8 GetHiddenPowerSafeCamomonMoveType(struct Pokemon* mon, u16 move)
{
	return move == MOVE_HIDDENPOWER ? CalcMonHiddenPowerType(mon) : gBattleMoves[move].type;
}

// Updated from base CFRU functionality - if a move is hidden power, get it's proper type instead of Normal
void UpdateTypesForCamomons(u8 bank)
{
	struct Pokemon* mon = GetBankPartyData(bank);

	u16 firstMove = gBattleMons[bank].moves[0];
	gBattleMons[bank].type1 = GetHiddenPowerSafeCamomonMoveType(mon, firstMove);
	u16 secondMove = gBattleMons[bank].moves[1];

	if (secondMove != MOVE_NONE)
		gBattleMons[bank].type2 = GetHiddenPowerSafeCamomonMoveType(mon, secondMove);
	else
		gBattleMons[bank].type2 = GetHiddenPowerSafeCamomonMoveType(mon, firstMove);
}

// Updated from base CFRU functionality - if a move is hidden power, get it's proper type instead of Normal
u8 GetCamomonsTypeByMon(struct Pokemon* mon, u8 whichType)
{
	if (whichType == 0)
	{
		u16 move = GetMonData(mon, MON_DATA_MOVE1, NULL);
		return GetHiddenPowerSafeCamomonMoveType(mon, move);
	}
	else
	{
		u16 move2 = GetMonData(mon, MON_DATA_MOVE2, NULL);
		if (move2 != MOVE_NONE)
			return GetHiddenPowerSafeCamomonMoveType(mon, move2);

		u16 move = GetMonData(mon, MON_DATA_MOVE1, NULL);
		return GetHiddenPowerSafeCamomonMoveType(mon, move);
	}
}

u8 GetCamomonsTypeBySpread(const struct BattleTowerSpread* spread, u8 whichType)
{
	if (whichType == 0)
	{
		return gBattleMoves[spread->moves[0]].type;
	}
	else
	{
		if (spread->moves[1] != MOVE_NONE)
			return gBattleMoves[spread->moves[1]].type;

		return gBattleMoves[spread->moves[0]].type;
	}
}

u8 ShouldReplaceTypesWithCamomons(void)
{
	return (gMain.inBattle && gBattleTypeFlags & BATTLE_TYPE_CAMOMONS) || IsCamomonsBattle();
}

bool8 TryUpdateOutcomeForFrontierBattle(void)
{
	u32 i;
	u32 playerHPCount, enemyHPCount;

	if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
	{

		for (playerHPCount = 0, i = 0; i < PARTY_SIZE; ++i)
		{
			if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
			&& !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, NULL))
				playerHPCount += GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL);
		}

		for (enemyHPCount = 0, i = 0; i < PARTY_SIZE; ++i)
		{
			if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
			&& !GetMonData(&gEnemyParty[i], MON_DATA_IS_EGG, NULL))
				enemyHPCount += GetMonData(&gEnemyParty[i], MON_DATA_HP, NULL);
		}

		if (playerHPCount == 0 && enemyHPCount > 0)
			gBattleOutcome |= B_OUTCOME_LOST;
		else if (playerHPCount > 0 && enemyHPCount == 0)
			gBattleOutcome |= B_OUTCOME_WON;
		else if (playerHPCount == 0 && enemyHPCount == 0)
		{
			if (SIDE(gNewBS->lastFainted) == B_SIDE_PLAYER)
				gBattleOutcome |= B_OUTCOME_WON;
			else
				gBattleOutcome |= B_OUTCOME_LOST;
		}

		gBattlescriptCurrInstr += 5;
		return TRUE;
	}

	return FALSE;
}

bool8 ShouldDisablePartyMenuItemsBattleTower(void)
{
	return FlagGet(FLAG_BATTLE_FACILITY);
}

const u8* GetFrontierTierName(u8 tier, u8 format)
{
	const u8* string = gBattleFrontierTierNames[tier];

	if (!IsFrontierSingles(format))
	{
		if (tier == BATTLE_FACILITY_OU)
			string = gText_SmogonOUDoubles;
		else if (tier == BATTLE_FACILITY_MIDDLE_CUP)
			string = gText_GSCup;
		else if (tier == BATTLE_FACILITY_MC_CAMOMONS)
			string = gText_GSCupCamomons;
	}

	return string;
}

bool8 InBattleSands(void)
{
	return (gBattleTypeFlags & BATTLE_TYPE_BATTLE_SANDS) != 0;
}

bool8 IsBattleIsleBattle(void)
{
	return (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
		&& FlagGet(FLAG_BATTLE_FACILITY)
		&& BATTLE_FACILITY_NUM == IN_BATTLE_ISLE;
}

bool8 IsAIControlledBattle(void)
{
	return InBattleSands() || (gBattleTypeFlags & BATTLE_TYPE_MOCK_BATTLE) != 0;
}

bool8 IsStandardTier(u8 tier)
{
	return tier == BATTLE_FACILITY_STANDARD
		|| tier == BATTLE_FACILITY_DYNAMAX_STANDARD;
}

// For Amethyst, the streak always ramps up:
// 	- Legendaries only if the player has them
//  - Megas at streak 20+
//  - Z-Crystals at any streak
//  - BST based on streak progress:
//		- 520 under 10
//		- 540 under 20
//		- 570 under 30
//		- 570 + dupes under 50
//		- no BST cap at 50+
bool8 StreakRampAppliesInTier(u8 tier)
{
	return IsStandardTier(tier)
		|| tier == BATTLE_FACILITY_NO_RESTRICTIONS;
}

bool8 IsCamomonsTier(u8 tier)
{
	return tier == BATTLE_FACILITY_CAMOMONS
		|| tier == BATTLE_FACILITY_UBER_CAMOMONS
		|| tier == BATTLE_FACILITY_LC_CAMOMONS
		|| tier == BATTLE_FACILITY_MC_CAMOMONS;
}

bool8 IsLittleCupTier(u8 tier)
{
	return tier == BATTLE_FACILITY_LITTLE_CUP
		|| tier == BATTLE_FACILITY_LC_CAMOMONS;
}

bool8 IsMiddleCupTier(u8 tier)
{
	return tier == BATTLE_FACILITY_MIDDLE_CUP || tier == BATTLE_FACILITY_MC_CAMOMONS;
}

bool8 IsAverageMonsBattle(void)
{
	return FlagGet(FLAG_BATTLE_FACILITY) && VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_AVERAGE_MONS;
}

bool8 Is350CupBattle(void)
{
	return FlagGet(FLAG_BATTLE_FACILITY) && VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_350_CUP;
}

bool8 IsScaleMonsBattle(void)
{
	return (FlagGet(FLAG_BATTLE_FACILITY) && VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_SCALEMONS)
		#ifdef FLAG_SCALEMONS_GAME
		|| FlagGet(FLAG_SCALEMONS_GAME)
		#endif
		;
}

bool8 IsOnlyScalemonsGame(void)
{
	#ifdef FLAG_SCALEMONS_GAME
	if (FlagGet(FLAG_SCALEMONS_GAME)
	&& !(FlagGet(FLAG_BATTLE_FACILITY) && VarGet(VAR_BATTLE_FACILITY_TIER) == BATTLE_FACILITY_SCALEMONS))
		return TRUE;
	#endif

	return FALSE;
}

bool8 IsCamomonsBattle(void)
{
	return FlagGet(FLAG_BATTLE_FACILITY) && IsCamomonsTier(VarGet(VAR_BATTLE_FACILITY_TIER));
}

bool8 IsBenjaminButterfreeBattle(void)
{
	return (gBattleTypeFlags & BATTLE_TYPE_BENJAMIN_BUTTERFREE) != 0;
}

bool8 AreMegasZMovesBannedInTier(u8 tier)
{
	return tier == BATTLE_FACILITY_DYNAMAX_STANDARD;
}

bool8 IsMegaZMoveBannedBattle(void)
{
	return gBattleTypeFlags & BATTLE_TYPE_TRAINER //Excludes Raid Battles
	&& FlagGet(FLAG_BATTLE_FACILITY)
	&& (AreMegasZMovesBannedInTier(VarGet(VAR_BATTLE_FACILITY_TIER))
	 || BATTLE_FACILITY_NUM == IN_BATTLE_ISLE // Mega Stones and Z-Crystals are held items like any other here
	 || BATTLE_FACILITY_NUM == IN_BATTLE_OBSERVATORY // One Pokemon a side is lopsided enough without them
	 || (gBattleTypeFlags & BATTLE_TYPE_BATTLE_SIM && gBattleSimFlags & BATTLE_SIM_DYNAMAX));
}

// A Battle Observatory battle, which is fought one Pokemon a side after both trainers reveal their team.
bool8 IsBattleObservatoryBattle(void)
{
	return (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
		&& FlagGet(FLAG_BATTLE_FACILITY)
		&& BATTLE_FACILITY_NUM == IN_BATTLE_OBSERVATORY;
}

#define LOAD_TIER_CHECKING_ABILITY										\
{																		\
	if (spread->ability == 0 && gBaseStats[species].hiddenAbility != 0)	\
		ability = GetHiddenAbility(species);							\
	else if (spread->ability == 2 && gBaseStats[species].ability2 != 0)	\
		ability = GetAbility2(species);									\
	else																\
		ability = GetAbility1(species);									\
}
bool8 PokemonTierBan(const u16 species, const u16 item, const struct BattleTowerSpread* const spread, const struct Pokemon* const mon, const u8 tier, const u8 checkFromLocationType)
{
	u32 i;
	u8 ability;
	const u16* moveLoc;

	if (species == SPECIES_EGG
	#ifdef SPECIES_ETERNATUS_ETERNAMAX
	|| species == SPECIES_ETERNATUS_ETERNAMAX
	#endif
	) //Hackmon
		return TRUE;

	u16 battleFormat = VarGet(VAR_BATTLE_FACILITY_BATTLE_TYPE);

	switch (tier) {
		case BATTLE_FACILITY_STANDARD:
		case BATTLE_FACILITY_MEGA_BRAWL:
		case BATTLE_FACILITY_DYNAMAX_STANDARD:
			//Load correct ability
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			if (gSpecialSpeciesFlags[species].battleTowerStandardBan
			||  CheckTableForItem(item, gBattleTowerStandard_ItemBanList)
			|| (ability == ABILITY_BATTLEBOND && tier != BATTLE_FACILITY_MEGA_BRAWL && BATTLE_FACILITY_NUM != IN_BATTLE_OBSERVATORY)) //Battle Bond is banned in Standard
				return TRUE;

			if (BATTLE_FACILITY_NUM == IN_BATTLE_OBSERVATORY) //1v1
			{
				#ifdef UNBOUND
				if (species == SPECIES_REGIGIGAS && ability == ABILITY_STALL && !FlagGet(FLAG_ABILITY_RANDOMIZER)) //Too OP 1v1
					return TRUE;
				#endif

				if (item == ITEM_FOCUS_SASH) //No Focus Sash in a 1v1
					return TRUE;

				//Check Banned Moves
				for (i = 0; i < MAX_MON_MOVES; ++i)
				{
					if (CheckTableForMove(moveLoc[i], gBattleObservatory_MoveBanList))
						return TRUE;
				}
			}
			break;

		case BATTLE_FACILITY_OU:
		case BATTLE_FACILITY_NATIONAL_DEX_OU:
		STANDARD_OU_CHECK:
		//For OU, there's a species, item, ability, and move ban list
			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			if (IsFrontierSingles(battleFormat))
			{
				if (tier == BATTLE_FACILITY_NATIONAL_DEX_OU)
				{
					if (gSpecialSpeciesFlags[species].smogonNationalDexOUBan
					||  CheckTableForItem(item, gSmogonNationalDexOU_ItemBanList))
						return TRUE;
				}
				else //Gen 7 OU
				{
					if (gSpecialSpeciesFlags[species].smogonOUBan
					||  CheckTableForItem(item, gSmogonOU_ItemBanList))
						return TRUE;
				}

				//Check Banned Abilities
				if (CheckTableForAbility(ability, gSmogonOU_AbilityBanList))
					return TRUE;

				//Check Banned Moves
				for (i = 0; i < MAX_MON_MOVES; ++i)
				{
					if (CheckTableForMove(moveLoc[i], gSmogon_MoveBanList)
					|| moveLoc[i] == MOVE_BATONPASS)
						return TRUE;
				}
			}
			else //Double Battles
			{
				bool8 knowsRecycle = FALSE;
				bool8 knowsPainSplit = FALSE;
				bool8 knowsFling = FALSE;
				bool8 knowsHealingMove = FALSE;

				if (gSpecialSpeciesFlags[species].smogonOUDoublesBan
				||  CheckTableForItem(item, gSmogonOUDoubles_ItemBanList))
					return TRUE;

				//Check Banned Abilities
				if (CheckTableForAbility(ability, gSmogonOUDoubles_AbilityBanList))
					return TRUE;

				//Check Banned Moves
				for (i = 0; i < MAX_MON_MOVES; ++i)
				{
					if (CheckTableForMove(moveLoc[i], gSmogon_MoveBanList)
					||  CheckTableForMove(moveLoc[i], gSmogonOUDoubles_MoveBanList))
						return TRUE;

					switch (moveLoc[i]) {
						case MOVE_HEALPULSE:
						case MOVE_MILKDRINK:
						case MOVE_MOONLIGHT:
						case MOVE_MORNINGSUN:
						case MOVE_RECOVER:
						case MOVE_ROOST:
						case MOVE_SLACKOFF:
						case MOVE_SOFTBOILED:
						case MOVE_WISH:
							knowsHealingMove = TRUE;
							break;
						case MOVE_RECYCLE:
							knowsRecycle = TRUE;
							break;
						case MOVE_PAINSPLIT:
							knowsPainSplit = TRUE;
							break;
						case MOVE_FLING:
							knowsFling = TRUE;
							break;
					}

					if (knowsRecycle && ItemId_GetHoldEffect(item) == ITEM_EFFECT_RESTORE_PP) //Leppa Berry
					{
						if (knowsHealingMove
						||  knowsPainSplit
						||  knowsFling)
							return TRUE;
					}
				}
			}
			break;

		case BATTLE_FACILITY_UBER:
		case BATTLE_FACILITY_UBER_CAMOMONS:
		//For Ubers ban Rayquaza with Dragon Ascent (handled in mega.c), Zacian, Moody, and some moves
		if (species == SPECIES_ZACIAN || species == SPECIES_ZACIAN_CROWNED)
			return TRUE;

		STANDARD_UBER_CHECK:
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (ability == ABILITY_MOODY)
				return 1;

			//Check Banned Moves
			for (i = 0; i < MAX_MON_MOVES; ++i)
			{
				if (CheckTableForMove(moveLoc[i], gSmogon_MoveBanList))
					return TRUE;
			}
			break;

		case BATTLE_FACILITY_LITTLE_CUP:
		case BATTLE_FACILITY_LC_CAMOMONS:
			if (!gSpecialSpeciesFlags[species].smogonLittleCup
			||  CheckTableForItem(item, gSmogonLittleCup_ItemBanList))
				return TRUE; //Banned

			if (checkFromLocationType == CHECK_BATTLE_TOWER_SPREADS)
				moveLoc = spread->moves;
			else
				moveLoc = mon->moves;

			for (i = 0; i < MAX_MON_MOVES; ++i)
			{
				if (CheckTableForMove(moveLoc[i], gSmogonLittleCup_MoveBanList))
					return TRUE;
			}
			break;

		case BATTLE_FACILITY_MIDDLE_CUP:
		case BATTLE_FACILITY_MC_CAMOMONS:
			if (IsFrontierSingles(battleFormat)) //Middle Cup in Singles
			{
				if (!gSpecialSpeciesFlags[species].middleCup
				||   CheckTableForItem(item, gMiddleCup_ItemBanList))
					return TRUE; //Banned

				//Load correct ability and moves
				switch (checkFromLocationType) {
					case CHECK_BATTLE_TOWER_SPREADS:
						LOAD_TIER_CHECKING_ABILITY;
						break;
					default:
						ability = GetMonAbility(mon);
				}

				//Check Banned Abilities
				if (CheckTableForAbility(ability, gMiddleCup_AbilityBanList))
					return TRUE;
			}
			else //GS Cup
			{
				if (CheckTableForItem(item, gBattleTowerStandard_ItemBanList))
					return TRUE;

				if (gSpecialSpeciesFlags[species].battleTowerStandardBan
				&& !gSpecialSpeciesFlags[species].gsCupLegendaries)
					return TRUE;
			}
			break;

		case BATTLE_FACILITY_MONOTYPE:
		//For Monotype, there's a species, item, ability, and move ban list
			if (gSpecialSpeciesFlags[species].smogonMonotypeBan
			||  CheckTableForItem(item, gSmogonMonotype_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogonMonotype_AbilityBanList))
				return TRUE;

			//Check Banned Moves
			for (i = 0; i < MAX_MON_MOVES; ++i)
			{
				if (CheckTableForMove(moveLoc[i], gSmogon_MoveBanList)
				|| moveLoc[i] == MOVE_BATONPASS
				|| moveLoc[i] == MOVE_SWAGGER)
					return TRUE;
			}
			break;

		case BATTLE_FACILITY_CAMOMONS:
			if (gSpecialSpeciesFlags[species].smogonCamomonsBan)
				return TRUE;

			goto STANDARD_OU_CHECK;

		case BATTLE_FACILITY_SCALEMONS:
			if (gSpecialSpeciesFlags[species].smogonScalemonsBan
			||  CheckTableForItem(item, gSmogonScalemons_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogonScalemons_AbilityBanList))
				return TRUE;

			goto STANDARD_UBER_CHECK;

		case BATTLE_FACILITY_350_CUP:
			if (gSpecialSpeciesFlags[species].smogon350CupBan
			||  CheckTableForItem(item, gSmogon350Cup_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogon350Cup_AbilityBanList))
				return TRUE;

			goto STANDARD_UBER_CHECK;

		case BATTLE_FACILITY_AVERAGE_MONS:
			if (gSpecialSpeciesFlags[species].smogonAverageMonsBan
			||  CheckTableForItem(item, gSmogonAverageMons_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogonAverageMons_AbilityBanList))
				return TRUE;
			break;

		case BATTLE_FACILITY_BENJAMIN_BUTTERFREE:
			if (gSpecialSpeciesFlags[species].smogonBenjaminButterfreeBan)
				return TRUE;

			goto STANDARD_OU_CHECK;

		case BATTLE_FACILITY_METRONOME:
			//No Steel Types, Pokemon with BST > 625 (including Megas), and banned items or abilities
			if (gBaseStats[species].type1 == TYPE_STEEL
			||  gBaseStats[species].type2 == TYPE_STEEL
			||  GetBaseStatsTotal(species) > 625)
				return TRUE;

			//Check banned items
			if (CheckTableForItem(item, gSmogonMetronome_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			//Check if can Mega Evolve and if that species should be banned
			u16 megaSpecies = GetMegaSpecies(species, item, moveLoc);
			if (megaSpecies != SPECIES_NONE)
			{
				if (gBaseStats[megaSpecies].type1 == TYPE_STEEL
				||  gBaseStats[megaSpecies].type2 == TYPE_STEEL
				||  GetBaseStatsTotal(megaSpecies) > 625)
					return TRUE;
			}

			//Check banned abilities
			if (CheckTableForAbility(ability, gSmogonMetronome_AbilityBanList))
				return TRUE;

			//Check specific item-ability combination
			if (ability == ABILITY_HARVEST
			&& (item == ITEM_JABOCA_BERRY || item == ITEM_ROWAP_BERRY))
				return TRUE;
			break;

		case BATTLE_FACILITY_UU:
			if (gSpecialSpeciesFlags[species].smogonUUBan
			||  CheckTableForItem(item, gSmogonUU_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogonUU_AbilityBanList))
				return TRUE;

			goto STANDARD_OU_CHECK;

		case BATTLE_FACILITY_RU:
			if (gSpecialSpeciesFlags[species].smogonRUBan
			||  gSpecialSpeciesFlags[species].smogonUUBan
			||  CheckTableForItem(item, gSmogonRU_ItemBanList)
			||  CheckTableForItem(item, gSmogonUU_ItemBanList))
				return TRUE;

			//Load correct ability and moves
			switch (checkFromLocationType) {
				case CHECK_BATTLE_TOWER_SPREADS:
					moveLoc = spread->moves;
					LOAD_TIER_CHECKING_ABILITY;
					break;
				default:
					moveLoc = mon->moves;
					ability = GetMonAbility(mon);
			}

			//Check Banned Abilities
			if (CheckTableForAbility(ability, gSmogonRU_AbilityBanList))
				return TRUE;

			//Check Banned Moves
			for (i = 0; i < MAX_MON_MOVES; ++i)
			{
				if (moveLoc[i] == MOVE_AURORAVEIL)
					return TRUE;
			}

			goto STANDARD_OU_CHECK;
	
		case BATTLE_FACILITY_NU:
			if (gSpecialSpeciesFlags[species].smogonNUBan
			||  gSpecialSpeciesFlags[species].smogonRUBan
			||  gSpecialSpeciesFlags[species].smogonUUBan
			||  CheckTableForItem(item, gSmogonNU_ItemBanList)
			||  CheckTableForItem(item, gSmogonRU_ItemBanList)
			||  CheckTableForItem(item, gSmogonUU_ItemBanList))
				return TRUE;

			goto STANDARD_OU_CHECK;
	}

	return FALSE; //Not banned
}

bool8 IsMonBannedInTier(struct Pokemon* mon, u8 tier)
{
	u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
	u16 item = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);

	return PokemonTierBan(species, item, NULL, mon, tier, CHECK_PARTY_OFFSET);
}

bool8 IsSpeciesBannedInTier(u16 species, u16 tier, u16 battleFormat)
{
	switch (tier)
	{
		case BATTLE_FACILITY_STANDARD:
		case BATTLE_FACILITY_MEGA_BRAWL:
		case BATTLE_FACILITY_DYNAMAX_STANDARD:
			if (gSpecialSpeciesFlags[species].battleTowerStandardBan)
				return TRUE;

			return species == SPECIES_ASHGRENINJA && tier != BATTLE_FACILITY_MEGA_BRAWL && BATTLE_FACILITY_NUM != IN_BATTLE_OBSERVATORY;

		case BATTLE_FACILITY_OU:
		case BATTLE_FACILITY_NATIONAL_DEX_OU:
		STANDARD_OU_CHECK:
			if (IsFrontierSingles(battleFormat))
			{
				if (tier == BATTLE_FACILITY_NATIONAL_DEX_OU)
					return gSpecialSpeciesFlags[species].smogonNationalDexOUBan;
				else
					return gSpecialSpeciesFlags[species].smogonOUBan;
			}
			else
				return gSpecialSpeciesFlags[species].smogonOUDoublesBan;

		case BATTLE_FACILITY_UBER:
		case BATTLE_FACILITY_UBER_CAMOMONS:
			return species == SPECIES_RAYQUAZA_MEGA
				|| species == SPECIES_ZACIAN
				|| species == SPECIES_ZACIAN_CROWNED;

		case BATTLE_FACILITY_LITTLE_CUP:
		case BATTLE_FACILITY_LC_CAMOMONS:
			return !gSpecialSpeciesFlags[species].smogonLittleCup;

		case BATTLE_FACILITY_MIDDLE_CUP:
		case BATTLE_FACILITY_MC_CAMOMONS:
			if (IsFrontierSingles(battleFormat)) //Middle Cup in Singles
				return !gSpecialSpeciesFlags[species].middleCup;
			else //GS Cup in Doubles
			{
				return gSpecialSpeciesFlags[species].battleTowerStandardBan
					&& !gSpecialSpeciesFlags[species].gsCupLegendaries;
			}
		
		case BATTLE_FACILITY_MONOTYPE:
			return gSpecialSpeciesFlags[species].smogonMonotypeBan;
		
		case BATTLE_FACILITY_CAMOMONS:
			if (gSpecialSpeciesFlags[species].smogonCamomonsBan)
				return TRUE;
			goto STANDARD_OU_CHECK;
		
		case BATTLE_FACILITY_SCALEMONS:
			return gSpecialSpeciesFlags[species].smogonScalemonsBan;

		case BATTLE_FACILITY_350_CUP:
			return gSpecialSpeciesFlags[species].smogon350CupBan;
		
		case BATTLE_FACILITY_AVERAGE_MONS:
			return gSpecialSpeciesFlags[species].smogonAverageMonsBan;
		
		case BATTLE_FACILITY_BENJAMIN_BUTTERFREE:
			if (gSpecialSpeciesFlags[species].smogonBenjaminButterfreeBan)
				return TRUE;
			goto STANDARD_OU_CHECK;
	}

	return FALSE;
}

//@Details: Generates a tower trainer id and name for the requested trainer.
//			Also buffers the trainer name to gStringVar1 (BUFFER1).
//@Inputs:
//		Var8000: 0 = Trainer Opponent A
//				 1 = Trainer Opponent B
//				 2 = Partner Trainer
//		Var8001: 0 = Regular Trainers
//				 1 = Special Trainers
//				 2 = Frontier Brain
//		Var8002: If Var8001 == Frontier Brain: Frontier Brain Id
//@Returns: To given var OW sprite num of generated trainer.
u16 sp052_GenerateFacilityTrainer(void)
{
	u8 battler = Var8000;
	u16 id = Random();

	if (Var8001 == 0)
	{
		id %= NUM_TOWER_TRAINERS;
		VarSet(VAR_FACILITY_TRAINER_ID + battler, id);

		if (gTowerTrainers[id].gender == BATTLE_FACILITY_MALE)
		{
			if (battler == 0)
				VarSet(VAR_BATTLE_FACILITY_TRAINER1_NAME, Random() % NUM_MALE_NAMES);
			else
				VarSet(VAR_BATTLE_FACILITY_TRAINER2_NAME, Random() % NUM_MALE_NAMES);
		}
		else
		{
			if (battler == 0)
				VarSet(VAR_BATTLE_FACILITY_TRAINER1_NAME, Random() % NUM_FEMALE_NAMES);
			else
				VarSet(VAR_BATTLE_FACILITY_TRAINER2_NAME, Random() % NUM_FEMALE_NAMES);
		}

		StringCopy(gStringVar1, GetFrontierTrainerName(BATTLE_TOWER_TID, battler));
		return gTowerTrainers[id].owNum;
	}
	else if (Var8001 == 1) //Special Trainer
	{
		u8 tier = VarGet(VAR_BATTLE_FACILITY_TIER);

		do
		{
			id = Random();
			id %= NUM_SPECIAL_TOWER_TRAINERS;
		}	while (tier == BATTLE_FACILITY_MONOTYPE && !gSpecialTowerTrainers[id].isMonotype);

		VarSet(VAR_FACILITY_TRAINER_ID + battler, id);
		StringCopy(gStringVar1, GetFrontierTrainerName(BATTLE_TOWER_SPECIAL_TID, battler));
		return gSpecialTowerTrainers[id].owNum;
	}
	else
	{
		id = Var8002;
		VarSet(VAR_FACILITY_TRAINER_ID + battler, id);
		StringCopy(gStringVar1, GetFrontierTrainerName(FRONTIER_BRAIN_TID, battler));
		return GetFrontierBrainOwNum(id);
	}
}

//@Details: Loads the battle intro message of the requested trainer.
//@Inputs:
//		Var8000: 0 = Trainer Opponent A
//				 1 = Trainer Opponent B
//		Var8001: 0 = Regular Trainers
//				 1 = Special Trainers
//				 2 = Frontier Brain
void sp053_LoadFrontierIntroBattleMessage(void)
{
	u8 gender;
	u16 id = VarGet(VAR_FACILITY_TRAINER_ID + Var8000);

	const u8* text;
	if (Var8001 == 0)
	{
		text = gTowerTrainers[id].preBattleText;
		gender = gTowerTrainers[id].gender;
	}
	else if (Var8001 == 1)
	{
		text = gSpecialTowerTrainers[id].preBattleText;
		gender = gSpecialTowerTrainers[id].gender;
	}
	else
	{
		text = gFrontierBrains[id].preBattleText;
		gender = GetFrontierBrainGender(id);
	}

	gLoadPointer = text;

	//Change text colour
	if (gender == BATTLE_FACILITY_MALE)
	{
		gTextColourBackup = gTextColourCurrent;
		gTextColourCurrent = 0; //Blue
	}
	else
	{
		gTextColourBackup = gTextColourCurrent;
		gTextColourCurrent = 1; //Red
	}
}

u8 GetCurrentFrontierFormat(void)
{
	return IsFrontierSingles(VarGet(VAR_BATTLE_FACILITY_BATTLE_TYPE)) ? FRONTIER_FORMAT_SINGLES : FRONTIER_FORMAT_DOUBLES;
}

u16 GetFrontierStreak(u8 facility, u8 format, u8 currentOrMax)
{
	if (facility >= NUM_BATTLE_FACILITIES)
		facility = IN_BATTLE_TOWER;

	return gFrontierStreaks[facility][MathMin(format, FRONTIER_FORMAT_DOUBLES)][MathMin(currentOrMax, MAX_STREAK)];
}

void SetFrontierStreak(u8 facility, u8 format, u8 currentOrMax, u16 value)
{
	if (facility >= NUM_BATTLE_FACILITIES)
		return;

	gFrontierStreaks[facility][MathMin(format, FRONTIER_FORMAT_DOUBLES)][MathMin(currentOrMax, MAX_STREAK)] = value;
}

//@Details: Gets the streak for a Battle Frontier facility.
//@Input:
//		Var8000: 0 = Current Streak
//				 1 = Max Streak
//		Var8001: 0xFFFF = Use the facility the player is currently in
//				 0+ = Given facility
//		Var8002: 0xFFFF = Use the format currently selected
//				 0 = Singles, 1 = Doubles
u16 sp054_GetBattleFacilityStreak(void)
{
	u8 facility = (Var8001 == 0xFFFF) ? BATTLE_FACILITY_NUM : Var8001;
	u8 format = (Var8002 == 0xFFFF) ? GetCurrentFrontierFormat() : Var8002;

	return GetFrontierStreak(facility, format, Var8000);
}

// Reads the max streaks rather than the current ones, so reaching the target once is enough - losing the streak afterwards doesn't take it back.
bool8 HasAchievedFrontierStreak(u16 target)
{
	for (u32 facility = 0; facility < NUM_BATTLE_FACILITIES; ++facility)
	{
		for (u32 format = 0; format < NUM_FRONTIER_FORMATS; ++format)
		{
			if (GetFrontierStreak(facility, format, MAX_STREAK) >= target)
				return TRUE;
		}
	}

	return FALSE;
}

// Stores whether the player has ever reached a streak of Var8000 at any facility in LASTRESULT
void StoreHasAchievedFrontierStreak(void)
{
	Var800D = HasAchievedFrontierStreak(Var8000);
}

u16 GetCurrentBattleFacilityStreak(void)
{
	return GetFrontierStreak(BATTLE_FACILITY_NUM, GetCurrentFrontierFormat(), CURR_STREAK);
}

//@Details: Updates the streak for the facility and format the player is currently in.
//@Input:
//		Var8000: 0 = Increment by 1
//				 1 = Reset
void sp055_UpdateBattleFacilityStreak(void)
{
	u8 facility = BATTLE_FACILITY_NUM;
	u8 format = GetCurrentFrontierFormat();

	if (facility >= NUM_BATTLE_FACILITIES)
		return;

	u16* currentStreak = &gFrontierStreaks[facility][format][CURR_STREAK];
	u16* maxStreak = &gFrontierStreaks[facility][format][MAX_STREAK];

	switch (Var8000) {
		case 0: //Increment by 1
			if (*currentStreak < 0xFFFF) //Prevent overflow
				*currentStreak += 1;

			if (*maxStreak < *currentStreak)
			{
				*maxStreak = *currentStreak;
				if (GetGameStat(GAME_STAT_BATTLE_FACILITY_BEST_STREAK) < *currentStreak)
					SetGameStat(GAME_STAT_BATTLE_FACILITY_BEST_STREAK, *currentStreak);
			}
			break;

		case 1: //Reset
			*currentStreak = 0;
			break;
	}
}

//@Details: Determines how many PokeChips to award for the win that just happened (BP is not a currency in Amethyst)
//@Returns: The number of PokeChips to give, trimmed to what the player can still hold.
u16 sp056_DetermineChipsToGive(void)
{
	u16 toGive;
	u16 streakLength = GetCurrentBattleFacilityStreak();
	u16 held = CountTotalItemQuantityInBag(ITEM_POKE_CHIP);

	//Milestone challengers pay out their streak number.
	if (streakLength == FRONTIER_FIRST_MILESTONE_STREAK)
		toGive = FRONTIER_FIRST_MILESTONE_STREAK;
	else if (streakLength == FRONTIER_SECOND_MILESTONE_STREAK)
		toGive = FRONTIER_SECOND_MILESTONE_STREAK;
	else
		toGive = 2 + (streakLength / 10); //Win 9 -> 2, win 10 -> 3, win 20 -> 4, ...

	if (held >= 999)
		return 0;

	return MathMin(toGive, 999 - held);
}

//@Details: To be used after sp06B. Merges the player's choice of partner Pokemon onto their team.
void sp06C_SpliceFrontierTeamWithPlayerTeam(void)
{
	struct Pokemon partnerPokes[3];
	Memset(partnerPokes, 0, sizeof(struct Pokemon) * 3);

	for (int i = 0; i < 3; ++i)
	{
		if (gSelectedOrderFromParty[i] != 0)
			partnerPokes[i] = gPlayerParty[i]; //Player's party has already been remodeled by the special so call indices directly
	}

	RestorePartyFromTempTeam(0, 3);
	Memcpy(&gPlayerParty[3], partnerPokes, sizeof(struct Pokemon) * 3); //Fill second half of team with multi mons

	//Recalculate party count the special way because there may be a gap in the party
	gPlayerPartyCount = 0;
	for (int i = 0; i < PARTY_SIZE; ++i)
	{
		if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE)
			++gPlayerPartyCount;
	}
}

//@Details: Loads any relevant multi trainer data by the given Id value.
//			Also buffers the multi trainer name to gStringVar2 ([BUFFER2] / bufferstring 0x1).
//@Inputs:
//		Var8000: 0xFF - Random Id.
//				 0-0xFE - Given Id.
//@Returns: The OW id of the trainer.
u16 sp06D_LoadFrontierMultiTrainerById(void)
{
	u16 id = Var8000;

	if (id == 0xFF)
		id = Random() % gNumFrontierMultiTrainers;
	else if (id > 0xFF) //Invalid value
		id = 0;

	VarSet(VAR_FACILITY_TRAINER_ID_PARTNER, id);
	VarSet(VAR_PARTNER, BATTLE_FACILITY_MULTI_TRAINER_TID);
	VarSet(VAR_PARTNER_BACKSPRITE, gFrontierMultiBattleTrainers[id].backSpriteId);

	StringCopy(gStringVar2, GetFrontierTrainerName(BATTLE_FACILITY_MULTI_TRAINER_TID, 0));
	return gFrontierMultiBattleTrainers[id].owNum;
}

//@Details: Loads random effects for Battle Sim battles.
//@Returns: Lastresult: TRUE if all effects loaded.
//			gStringVarC: A description of the effect just activated.
void sp072_LoadBattleSimEffects(void)
{
	u32 i;
	u8 numActive = 0;
	gSpecialVar_LastResult = TRUE;

	for (i = 0; ; ++i)
	{
		if (gBattleSimFlags & gBitTable[i])
			++numActive;

		if (gBitTable[i] == LAST_BATTLE_SIM_FLAG)
			break;
	}

	u8 totalEffects = 1;
	u8 playerPartyCount = CalculatePlayerPartyCount();
	bool8 sideEffectsAllowed = FALSE;
	bool8 personalEffectsAllowed = FALSE;
	bool8 tradeMonAllowed = FALSE;
	u16 streak = GetCurrentBattleFacilityStreak();

	switch (streak) {
		case 0 ... 9:
			break;
		case 10 ... 19:
			if (playerPartyCount >= 5) //Basically 6v6 only
				tradeMonAllowed = TRUE;
			sideEffectsAllowed = TRUE;
			break;
		case 20 ... 29:
			if (playerPartyCount >= 4) //6v6 and Doubles only
				tradeMonAllowed = TRUE;
			sideEffectsAllowed = TRUE;
			totalEffects = 2;
			break;
		case 30 ... 39:
			sideEffectsAllowed = TRUE;
			personalEffectsAllowed = TRUE;
			tradeMonAllowed = TRUE;
			totalEffects = 2;
			break;
		case 40 ... 49:
			sideEffectsAllowed = TRUE;
			personalEffectsAllowed = TRUE;
			tradeMonAllowed = TRUE;
			totalEffects = 3;
			break;
		case 50 ... 70:
			sideEffectsAllowed = TRUE;
			personalEffectsAllowed = TRUE;
			tradeMonAllowed = TRUE;
			totalEffects = 4;
			break;
		default:
			sideEffectsAllowed = TRUE;
			personalEffectsAllowed = TRUE;
			tradeMonAllowed = TRUE;
			totalEffects = 5;
			break;
	}

	if (numActive < totalEffects)
	{
		bool8 weatherActive = (gBattleSimFlags & BATTLE_SIM_WEATHER) != 0;
		bool8 terrainActive = (gBattleSimFlags & BATTLE_SIM_TERRAIN) != 0;
		bool8 critEffectActive = (gBattleSimFlags & BATTLE_SIM_CRIT_EFFECT) != 0;
		bool8 randomBattleActive = VarGet(VAR_BATTLE_FACILITY_BATTLE_TYPE) >= BATTLE_FACILITY_SINGLE_RANDOM;

		u8 effectNum;
		do
		{
			effectNum = Random() % (i + 1);
		} while (gBattleSimFlags & gBitTable[effectNum] //Only add non active effects
			|| (weatherActive && gBitTable[effectNum] & BATTLE_SIM_WEATHER) //One weather effect at a time
			|| (terrainActive && gBitTable[effectNum] & BATTLE_SIM_TERRAIN) //One terrain effect at a time
			|| (critEffectActive && gBitTable[effectNum] & BATTLE_SIM_CRIT_EFFECT) //One critical hit effect at a time
			|| (gBitTable[effectNum] & BATTLE_SIM_DYNAMAX) // Prevent Dynamax from being rolled. It also can't silently ban megas or Z-Moves
			|| (randomBattleActive && gBitTable[effectNum] & BATTLE_SIM_TRADE_MON) //No point in swapping mons in a random battle
			|| (!tradeMonAllowed && gBitTable[effectNum] & BATTLE_SIM_TRADE_MON) //Swapping mons becomes available later on depending on team size
			|| (!sideEffectsAllowed && gBitTable[effectNum] >= FIRST_BATTLE_SIM_SIDE_EFFECT_FLAG && gBitTable[effectNum] <= LAST_BATTLE_SIM_SIDE_EFFECT_FLAG)
			|| (!personalEffectsAllowed && gBitTable[effectNum] >= FIRST_BATTLE_SIM_PERSONAL_EFFECT_FLAG));

		if (gBitTable[effectNum] & BATTLE_SIM_WEATHER)
		{
			u8 weather = 0;
			if (gBitTable[effectNum] == BATTLE_SIM_RAIN)
				weather = WEATHER_RAIN_LIGHT;
			else if (gBitTable[effectNum] == BATTLE_SIM_SUN)
				weather = WEATHER_DROUGHT;
			else if (gBitTable[effectNum] == BATTLE_SIM_SANDSTORM)
				weather = WEATHER_SANDSTORM;
			else if (gBitTable[effectNum] == BATTLE_SIM_HAIL)
				weather = WEATHER_STEADY_SNOW;

			SetSav1Weather(weather); //Followed up by a doweather in the script
		}

		gBattleSimFlags |= gBitTable[effectNum];
		StringCopy(gStringVarC, sBattleSimEffectDescriptions[effectNum]);
		gSpecialVar_LastResult = FALSE;
	}
}

//@Details: Sets the appropriate team levels for the battle facility.
void sp073_ModifyTeamForBattleTower(void)
{
	// Skip modifying the player's team for any facilities that use borrowed Pokemon (Maze & Factory)
	if (IsRandomBattleTowerBattle())
		return;

	//Scales in both directions. gPlayerParty is replaced with the entered copies, so nothing
	//may save between here and the end of the run without restoring the real team first - it
	//is waiting in SaveBlock1.playerParty, and special 0x28 brings it back when the run ends.
	u8 level = GetBattleFacilityLevel(VarGet(VAR_BATTLE_FACILITY_TIER));
	struct Pokemon* enteredMons = Calloc(sizeof(struct Pokemon) * PARTY_SIZE);

	for (int i = 0; i < PARTY_SIZE && gSelectedOrderFromParty[i] != 0; ++i) //Copy mons entered
	{
		Memcpy(&enteredMons[i], &gPlayerParty[gSelectedOrderFromParty[i] - 1], sizeof(struct Pokemon));

		u16 species = enteredMons[i].species;
		SetMonData(&enteredMons[i], MON_DATA_EXP, &gExperienceTables[gBaseStats[species].growthRate][level]);
		CalculateMonStats(&enteredMons[i]);
		HealMon(&enteredMons[i]);
	}

	Memcpy(gPlayerParty, enteredMons, sizeof(struct Pokemon) * PARTY_SIZE); //Overwrite old team
	Free(enteredMons);
}
