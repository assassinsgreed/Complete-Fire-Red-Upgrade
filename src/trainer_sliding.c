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
	if (ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)
	|| (IsTwoOpponentBattle() && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_B, TRAINER_SLIDE_LAST_LOW_HP))
	|| (IS_DOUBLE_BATTLE && ShouldDoTrainerSlide(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), gTrainerBattleOpponent_A, TRAINER_SLIDE_LAST_LOW_HP)))
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
