#include "defines.h"
#include "defines_battle.h"
#include "../include/main.h"
#include "../include/gba/m4a_internal.h"
#include "../include/sound.h"
#include "../include/text.h"

#include "../include/new/battle_speed.h"

/*
battle_speed.c
	Replaces the vanilla battle main callback so that the entire per-frame battle step -
	the script engine, the battler controllers, tasks, sprites and text - can be run
	several times per V-Blank, as chosen by the Battle Speed option.

	Music and sound are untouched by this. m4aSoundMain is called from the V-Blank
	interrupt, not from the main loop, so the sound engine still ticks exactly once per
	frame no matter how many times the main callbacks run.

	That split is also what the two sound helpers at the bottom of this file are for. Running
	the main callbacks several times per frame leaves the main loop still executing when the
	V-Blank interrupt fires, where at 1x it would have been idling in the V-Blank wait, so
	interrupts start landing inside main loop code that was written assuming they never do.
*/

//Vanilla callback the Poke Dude tutorial hands off to when the player backs out of it
#define CB2_QuitPokeDudeBattle ((MainCallback) (0x080111BC | 1))

static void RunBattleFrame(void);
static u8 GetBattleStepsPerFrame(void);

static void RunBattleFrame(void)
{
	AnimateSprites();
	BuildOamBuffer();
	RunTextPrinters();

	//V-Blank ends a fade by reading a one bit "finishing" flag that this call toggles, so an
	//even number of calls per frame hides it and the fade back in after the bag or party menu
	//never clears gPaletteFade.active, hanging every controller that waits on it
	if (!gInBattleSpeedExtraPass)
		UpdatePaletteFade();

	RunTasks();
}

static u8 GetBattleStepsPerFrame(void)
{
	u16 setting;

	//Both consoles advance one battle step per V-Blank, so extra steps desync the link
	if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_LINK_ESTABLISHED))
		return 1;

	//The scripted tutorials pace their voiceover frames against the text engine
	if (gBattleTypeFlags & (BATTLE_TYPE_OAK_TUTORIAL | BATTLE_TYPE_OLD_MAN | BATTLE_TYPE_POKE_DUDE))
		return 1;

	setting = VarGet(VAR_BATTLE_SPEED);
	if (setting >= OPTIONS_BATTLE_SPEED_COUNT)
		setting = OPTIONS_BATTLE_SPEED_NORMAL;

	return setting + 1;
}

/*
	A cry only starts during V-Blank, so on an extra pass a cry queued this frame hasn't
	started yet. Vanilla IsCryPlayingOrClearCrySongs would see "not playing" and throw the
	cry away before it ever sounded, so answer TRUE and let next frame's first pass decide.
	Cries then take the same real time at every battle speed.
*/
bool8 IsCryPlayingOrClearCrySongsSafe(void)
{
	if (gInBattleSpeedExtraPass)
		return TRUE;

	return IsCryPlayingOrClearCrySongs();
}

void NewBattleMainCB2(void)
{
	u8 i, steps;

	RunBattleFrame();

	steps = GetBattleStepsPerFrame();
	if (steps > 1)
	{
		u16 newKeys = gMain.newKeys;
		u16 newKeysRaw = gMain.newKeysRaw;
		u16 newAndRepeatedKeys = gMain.newAndRepeatedKeys;

		//ReadKeys only runs once per V-Blank, so without this every extra step sees the same press and triggers it again
		gMain.newKeys = 0;
		gMain.newKeysRaw = 0;
		gMain.newAndRepeatedKeys = 0;
		gInBattleSpeedExtraPass = TRUE;

		for (i = 1; i < steps; ++i)
		{
			if (gMain.callback2 != BattleMainCB2)
				break; //The battle handed the screen off mid-step, so stop stepping it

			BattleMainCB1(); //gBattleMainFunc + every gBattlerControllerFuncs entry

			if (gMain.callback2 != BattleMainCB2)
				break; //Opening the bag or party menu frees the battle's windows, so RunTextPrinters would render into freed memory

			RunBattleFrame();
		}

		gInBattleSpeedExtraPass = FALSE;
		gMain.newKeys = newKeys;
		gMain.newKeysRaw = newKeysRaw;
		gMain.newAndRepeatedKeys = newAndRepeatedKeys;
	}

	if (JOY_HELD(B_BUTTON) && gBattleTypeFlags & BATTLE_TYPE_POKE_DUDE)
	{
		gBattleOutcome = B_OUTCOME_DREW;
		Var800D = 3;
		ResetPaletteFadeControl();
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
		SetMainCallback2(CB2_QuitPokeDudeBattle);
	}
}

// There's a very rare chance that certain battle actions like mega evolution will result in
// a constant ringing sound when used which remains after battle. This code replaces the vanilla  sound effect
// loop with one that handles sound effect locks better. 
#define TRACK_WIPE_WORDS (64 / sizeof(u32)) // Vanilla clears exactly 64 bytes, leaving cmdPtr at 0x40 intact

void MPlayImmInitSafe(struct MusicPlayerInfo* mplayInfo)
{
	s32 trackCount;
	struct MusicPlayerTrack* track;
	volatile u32* ident = (volatile u32*) &mplayInfo->ident;

	if (*ident != ID_NUMBER)
		return; // Another m4a routine already owns this player

	*ident = ID_NUMBER + 1; // Locks MPlayMain out until the tracks are consistent again
	asm volatile ("" ::: "memory"); // The lock is worthless if the compiler sinks this store past the wipe below

	trackCount = mplayInfo->trackCount;
	track = mplayInfo->tracks;

	while (trackCount > 0)
	{
		if ((track->flags & MPT_FLG_EXIST) && (track->flags & MPT_FLG_START))
		{
			u32 i;
			u32* wipe = (u32*) track;

			for (i = 0; i < TRACK_WIPE_WORDS; ++i)
				wipe[i] = 0;

			track->flags = MPT_FLG_EXIST;
			track->bendRange = 2;
			track->volX = 64;
			track->lfoSpeed = 22;
			track->tone.type = 1;
		}

		--trackCount;
		++track;
	}

	asm volatile ("" ::: "memory");
	*ident = ID_NUMBER;
}
