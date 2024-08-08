#include "defines.h"
#include "defines_battle.h"
#include "../include/string_util.h"

#include "../include/new/battle_util.h"
#include "../include/new/mega.h"
#include "../include/new/multi.h"
#include "../include/new/trainer_sliding.h"
#include "../include/new/trainer_sliding_data.h"

#include "../include/constants/songs.h"
#include "../include/constants/trainer_classes.h"
/*
trainer_sliding.c
	handles mid-battle trainer sliding and related message.
*/

struct TrainerSlide
{
	u16 trainerId;
	const u8* msgFirstDown;
	const u8* msgLastSwitchIn;
	const u8* msgLastLowHp;
};

struct DynamaxTrainerSlide
{
	u16 trainerId;
	const u8* dynamaxMsg;
};

static const struct TrainerSlide sTrainerSlides[] =
{
	// Format {Trainer hex index, msg on first faint, msg on last switch in, msg on last pkmn low hp}
	{}, // Rival battle 1
	{0x1, NULL, sText_Rival1_LastSwitchIn, sText_Rival1_LowHP}, // First rival battle
	{0xE, NULL /*sText_Leader1_FirstMonDown*/, sText_Leader1_LastSwitchIn, sText_Leader1_LowHP}, // Gym Leader Terrence
	{0x1C, NULL, sText_Rival2_LastSwitchIn, sText_Rival2_LowHP}, // Second rival battle
	{0x23, NULL, sText_Irene_LastSwitchIn, sText_Irene_LowHP}, // Pluto Admin Irene (double battle)
	{0x40, sText_Leader2_FirstMonDown, sText_Leader2_LastSwitchIn, sText_Leader2_LowHP}, // Gym Leader Stella
	{0x69, sText_Leader3_FirstMonDown, sText_Leader3_LastSwitchIn, sText_Leader3_LowHP}, // Gym Leader Raine
	{0x88, sText_Rival3_FirstMonDown, sText_Rival3_LastSwitchIn, sText_Rival3_LowHP}, // Third rival battle
	{0x9A, sText_Leader4_FirstMonDown, sText_Leader4_LastSwitchIn, sText_Leader4_LowHP}, // Gym Leader Chance
	{0x9B, NULL, sText_Casey1_LastSwitchIn, sText_Casey1_LowHP}, // Female Casey battle 1
	{0x9C, NULL, sText_Casey1_LastSwitchIn, sText_Casey1_LowHP}, // Male Casey battle 1
	{0xAE, NULL, sText_Casey2_LastSwitchIn, sText_Casey2_LowHP}, // Female Casey battle 2
	{0xAF, NULL, sText_Casey2_LastSwitchIn, sText_Casey2_LowHP}, // Female Casey battle 2
	{0xC8, sText_Ronald_FirstMonDown, sText_Ronald_LastSwitchIn, sText_Ronald_LowHP}, // Pluto Admin Ronald
	{0xC9, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Vaporeon
	{0xCA, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Jolteon
	{0xCB, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Flareon
	{0xCC, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Espeon
	{0xCD, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Umbreon
	{0xCE, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Leafeon
	{0xCF, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Glaceon
	{0xD0, sText_Rival4_FirstMonDown, sText_Rival4_LastSwitchIn, sText_Rival4_LowHP}, // Fourth rival battle, Sylveon
	{0xE9, sText_Leader5F_FirstMonDown, sText_Leader5F_LastSwitchIn, sText_Leader5F_LowHP}, // Gym Leader Casey (F)
	{0xEA, sText_Leader5M_FirstMonDown, sText_Leader5M_LastSwitchIn, sText_Leader5M_LowHP}, // Gym Leader Casey (M)
	{0x10A, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Vaporeon
	{0x10B, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Jolteon
	{0x10C, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Flareon
	{0x10D, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Espeon
	{0x10E, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Umbreon
	{0x10F, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Leafeon
	{0x110, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Glaceon
	{0x111, sText_Rival5_FirstMonDown, sText_Rival5_LastSwitchIn, sText_Rival5_LowHP}, // Fifth rival battle, Sylveon
	{0x117, sText_Leader6_FirstMonDown, sText_Leader6_LastSwitchIn, sText_Leader6_LowHP}, // Gym Leader Abby
	{0x137, sText_Irene_PlutoHQ_FirstMonDown, sText_Irene_PlutoHQ_LastSwitchIn, sText_Irene_PlutoHQ_LowHP}, // Pluto Admin Irene (Pluto HQ)
	{0x138, sText_Ronald_PlutoHQ_FirstMonDown, sText_Ronald_PlutoHQ_LastSwitchIn, sText_Ronald_PlutoHQ_LowHP}, // Pluto Admin Ronald (Pluto HQ)
	{0x139, sText_Kurtis_FirstMonDown, sText_Kurtis_LastSwitchIn, sText_Kurtis_LowHP}, // Pluto Leader Kurtis
	{0x16D, sText_EmraldinRivalEvent_FirstMonDown, sText_EmraldinRivalEvent_LastSwitchIn, sText_EmraldinRivalEvent_LowHP}, // Rival event in Emraldin Quay
	{0x1A9, sText_DeveloperCollin_FirstMonDown, sText_DeveloperCollin_LastSwitchIn, sText_DeveloperCollin_LowHP}, // Developer Collin 1
	{0x1AA, sText_DeveloperCollin_FirstMonDown, sText_DeveloperCollin_LastSwitchIn, sText_DeveloperCollin_LowHP}, // Developer Collin 2
	{0x1AB, sText_DeveloperCrystal_FirstMonDown, sText_DeveloperCrystal_LastSwitchIn, sText_DeveloperCrystal_LowHP}, // Developer Crystal 1
	{0x1AC, sText_DeveloperCrystal_FirstMonDown, sText_DeveloperCrystal_LastSwitchIn, sText_DeveloperCrystal_LowHP}, // Developer Crystal 2
	{0x1AD, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Noam
	{0x1AE, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Ashley
	{0x1AF, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Chelsea
	{0x1B0, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Buddy
	{0x1B1, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Gawain
	{0x1B2, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Skylar
	{0x1B3, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Bella
	{0x1B4, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Flash
	{0x1B5, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Terra
	{0x1B6, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Seifa
	{0x1B7, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Rocco
	{0x1B8, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Janice
	{0x1B9, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Antoinette
	{0x1BA, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Ryu
	{0x1BB, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Caspar
	{0x1BC, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Darcy
	{0x1BD, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Mason
	{0x1BE, sText_GymLeaderTrainee_FirstMonDown, sText_GymLeaderTrainee_LastSwitchIn, sText_GymLeaderTrainee_LowHP}, // Gym Trainee Faye
	{0x1C5, sText_Leader7_FirstMonDown, sText_Leader7_LastSwitchIn, sText_Leader7_LowHP}, // Gym Leader Iris
	{0x1D5, sText_Rival6_FirstMonDown, sText_Rival6_FirstMonDown, sText_Rival6_LowHP}, // Carnelidge Volcano Rival
	{0x1D6, sText_Alistair_FirstMonDown, sText_Alistair_LastSwitchIn, sText_Alistair_LowHP}, // Carnelidge Volcano Alistair
	{}, // Champion Selene
};

static const struct DynamaxTrainerSlide sDynamaxTrainerSlides[] =
{
	{0x17, gText_TestTrainerDynamaxMsg}, //Test data
	#ifdef UNBOUND
	{0x1D5, sText_RogueElectivire_DynamaxMsg},
	#endif
};

//This file's functions:
static bool8 IsBankHpLow(u8 bank);
static u8 GetEnemyMonCount(bool8 onlyAlive);

void atk53_trainerslidein(void)
{
	gActiveBattler = GetBattlerAtPosition(gBattlescriptCurrInstr[1]);
	EmitTrainerSlide(0);
	MarkBufferBankForExecution(gActiveBattler);
	gBattlescriptCurrInstr += 2;
}

void TrainerSlideInScriptingBank(void)
{
	gActiveBattler = gBattleScripting.bank;
	EmitTrainerSlide(0);
	MarkBufferBankForExecution(gActiveBattler);
}

void TrainerSlideOutScriptingBank(void)
{
	gActiveBattler = gBattleScripting.bank;
	EmitTrainerSlideBack(0);
	MarkBufferBankForExecution(gActiveBattler);
}

//The modifications made to this function don't affect
//sliding in anyway. They allow expanded Battle Backgrounds.
void HandleIntroSlide(u8 terrain)
{
	u8 taskId, bank;

	if (!AreAbilitiesSuppressed())
	{
		for (bank = 0; bank < gBattlersCount; ++bank)
		{
			if (((gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(bank) == B_SIDE_PLAYER) //Wild Pokemon can't be hidden
			&& GetMonAbility(GetBankPartyData(bank)) == ABILITY_ILLUSION)
			{
				gStatuses3[bank] |= STATUS3_ILLUSION;
				if (GetIllusionPartyData(bank) == GetBankPartyData(bank)) //Is trying to hide as itself
					gStatuses3[bank] &= ~STATUS3_ILLUSION; //Remove the Illusion
			}
		}
	}

	if (gBattleTypeFlags & BATTLE_TYPE_LINK)
	{
		taskId = CreateTask(BattleIntroSlideLink, 0);
	}
	else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
	{
		taskId = CreateTask(BattleIntroSlide3, 0);
	}
	else if (terrain > BATTLE_TERRAIN_CHAMPION)
	{
		taskId = CreateTask(BattleIntroSlide3, 0);
	}
	else
	{
		taskId = CreateTask(sBattleIntroSlideFuncs[terrain], 0);
	}

	gTasks[taskId].data[0] = 0;
	gTasks[taskId].data[1] = terrain;
	gTasks[taskId].data[2] = 0;
	gTasks[taskId].data[3] = 0;
	gTasks[taskId].data[4] = 0;
	gTasks[taskId].data[5] = 0;
	gTasks[taskId].data[6] = 0;
}

static u8 GetEnemyMonCount(bool8 onlyAlive)
{
	u8 i, count = 0;

	for (i = 0; i < PARTY_SIZE; i++)
	{
		u32 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES2, NULL);
		if (species != SPECIES_NONE
		&&  species != SPECIES_EGG
		&& (!onlyAlive || gEnemyParty[i].hp))
			++count;
	}

	return count;
}

static bool8 IsBankHpLow(u8 bank)
{
	return udivsi((gBattleMons[bank].hp * 100), gBattleMons[bank].maxHP) < 25;
}

bool8 ShouldDoTrainerSlide(u8 bank, u16 trainerId, u8 caseId)
{
	u32 i;

	if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(bank) != B_SIDE_OPPONENT)
		return FALSE;

	for (i = 0; i < ARRAY_COUNT(sTrainerSlides); ++i)
	{
		if (trainerId == sTrainerSlides[i].trainerId)
		{
			gBattleScripting.bank = bank;
			switch (caseId) {
				case TRAINER_SLIDE_LAST_SWITCHIN:
					if (sTrainerSlides[i].msgLastSwitchIn != NULL
					&& ((IS_SINGLE_BATTLE && GetEnemyMonCount(TRUE) == 1)
					 || (IS_DOUBLE_BATTLE && GetEnemyMonCount(TRUE) <= 2)))
					{
						gBattleStringLoader = sTrainerSlides[i].msgLastSwitchIn;

						// If the player is challenging a gym leader and they've switched in their last pokemon, change the music when their slide in text displays
						u8 class = gTrainers[gTrainerBattleOpponent_A].trainerClass;
						if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER) == (BATTLE_TYPE_TRAINER)
							&& !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_TRAINER_TOWER))
							&& (class == CLASS_LEADER || class == CLASS_ELITE_4 || class == CLASS_CHAMPION ))
							{
								PlayBGM(BGM_BATTLE_GYM_LEADER_LAST_POKEMON);
							}

						FlagSet(FLAG_TEMP_1); // Prevent more switch in text this turn
						return TRUE;
					}
					break;

				case TRAINER_SLIDE_LAST_LOW_HP:
					if (sTrainerSlides[i].msgLastLowHp != NULL
					&& GetEnemyMonCount(TRUE) == 1
					&& IsBankHpLow(bank)
					&& !gNewBS->trainerSlideLowHpMsgDone)
					{
						gNewBS->trainerSlideLowHpMsgDone = TRUE;
						gBattleStringLoader = sTrainerSlides[i].msgLastLowHp;
						return TRUE;
					}
					break;

				case TRAINER_SLIDE_FIRST_DOWN:
					if (sTrainerSlides[i].msgFirstDown != NULL && GetEnemyMonCount(TRUE) == GetEnemyMonCount(FALSE) - 1)
					{
						gBattleStringLoader = sTrainerSlides[i].msgFirstDown;
						return TRUE;
					}
					break;
			}
			break;
		}
	}

	return FALSE;
}

void TryDoDynamaxTrainerSlide(void)
{
	u32 i;
	u16 trainerId;

	if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || SIDE(gBattleScripting.bank) != B_SIDE_OPPONENT)
		return;

	if (IsTwoOpponentBattle() && GetBattlerPosition(gBattleScripting.bank) == B_POSITION_OPPONENT_RIGHT)
		trainerId = gTrainerBattleOpponent_B;
	else
		trainerId = gTrainerBattleOpponent_A;

	gBattleStringLoader = gText_DefaultTrainerDynamaxMsg;
	for (i = 0; i < NELEMS(sDynamaxTrainerSlides); ++i)
	{
		if (trainerId == sDynamaxTrainerSlides[i].trainerId)
			gBattleStringLoader = sDynamaxTrainerSlides[i].dynamaxMsg;
	}

	// //Try giving any Trainer named "Red" a special string
	// if (i >= NELEMS(sDynamaxTrainerSlides))
	// {
	// 	u8 redName[] = {CHAR_R, CHAR_e, CHAR_d, EOS};

	// 	if (StringCompare(GetTrainerName(gBattleScripting.bank), redName) == 0) //Trainer's name is "Red"
	// 		gBattleStringLoader = gText_RedDynamaxMsg;
	// }

	BattleScriptPush(gBattlescriptCurrInstr + 5); //After callasm
	gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet - 5;
}

//Hook in Battle Main
void CheckLastMonLowHPSlide(void)
{
	if (!FlagGet(FLAG_TEMP_1) && (
		ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)
		|| (IsTwoOpponentBattle() && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_B, TRAINER_SLIDE_LAST_LOW_HP))
		|| (IS_DOUBLE_BATTLE && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)))
	)
		BattleScriptExecute(BattleScript_TrainerSlideMsgEnd2);
}

//handletrainerslidemsg BANK CASE
void atkFF1C_handletrainerslidemsg(void)
{
	gActiveBattler = GetBankForBattleScript(gBattlescriptCurrInstr[1]);

	if (IS_DOUBLE_BATTLE)
		gActiveBattler &= BIT_SIDE; //Always mon on enemy left in doubles

	u8 caseId = gBattlescriptCurrInstr[2];

	switch(caseId) {
		case 0:
			gNewBS->trainerSlideInProgress = TRUE; //Prevent's the foe's shadow from having problems
			gNewBS->savedObjId = gBattlerSpriteIds[gActiveBattler];
			break;

		case 1:
			gNewBS->trainerSlideInProgress = FALSE;
			gBattlerSpriteIds[gActiveBattler] = gNewBS->savedObjId;
			if (BATTLER_ALIVE(gActiveBattler))
				BattleLoadOpponentMonSpriteGfx(GetBankPartyData(gActiveBattler), gActiveBattler);
	}

	gBattlescriptCurrInstr += 3;
}

//trytrainerslidefirstdownmsg BANK
void atkFF1D_trytrainerslidefirstdownmsg(void)
{
	u8 pos, shouldDo;

	gActiveBattler = GetBankForBattleScript(gBattlescriptCurrInstr[1]);
	pos = GetBattlerPosition(gActiveBattler);

	if (IsTwoOpponentBattle() && pos == B_POSITION_OPPONENT_RIGHT)
		shouldDo = ShouldDoTrainerSlide(gActiveBattler, gTrainerBattleOpponent_B, TRAINER_SLIDE_FIRST_DOWN);
	else
		shouldDo = ShouldDoTrainerSlide(gActiveBattler, gTrainerBattleOpponent_A, TRAINER_SLIDE_FIRST_DOWN);

	if (shouldDo)
	{
		BattleScriptPush(gBattlescriptCurrInstr + 2);
		gBattlescriptCurrInstr = BattleScript_TrainerSlideMsgRet;
		return;
	}

	gBattlescriptCurrInstr += 2;
}

void atkFF1E_trainerslideout(void)
{
	gActiveBattler = GetBattlerAtPosition(gBattlescriptCurrInstr[1]);
	EmitTrainerSlideBack(0);
	MarkBufferBankForExecution(gActiveBattler);
	gBattlescriptCurrInstr += 2;
}
