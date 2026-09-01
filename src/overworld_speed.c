#include "defines.h"
#include "../include/event_object_movement.h"
#include "../include/script.h"
#include "../include/constants/event_object_movement_constants.h"
#include "../include/constants/maps.h"

#include "../include/field_effect.h"

#include "../include/new/dexnav.h"
#include "../include/new/follow_me.h"
#include "../include/new/overworld_speed.h"

/*
overworld_speed.c
	Scales how fast the player moves between tiles, as chosen by the Overworld Speed option.
	This applies to all player movement (ex. cycling, surfing, sliding on ice tiles) and followers.
	It does not affect NPCs or cutscene movement.
	It it also temporarily disabled in certain scenarios that require precision:
		- Using the DexNav Scan
		- The Uteya Gym (when puzzle is active) and Laplaz Gym (always)

	This logic has special handling for MC movement that does not have a full movement range (ex. cycling, surfing)
	to ensure they still appear to animate even at high speeds.
*/

#define VANILLA_STEP_TIER_COUNT 5

//Frames needed to cross one tile, indexed by speed tier. Tiers 0 - 4 are vanilla; tier 5
//is new and exists so the 3x setting can hold the vanilla 2:1 run-to-walk ratio, since
//neither 16 nor 8 frames divides by three.
#define STEP_TIER_16_FRAME 0
#define STEP_TIER_8_FRAME  1
#define STEP_TIER_6_FRAME  2
#define STEP_TIER_4_FRAME  3
#define STEP_TIER_2_FRAME  4
#define STEP_TIER_3_FRAME  5

//Vanilla step function rows, still used verbatim for tiers 0 - 4
#define sVanillaStepFuncs_16 ((const StepFunc*) 0x83A710C)
#define sVanillaStepFuncs_8  ((const StepFunc*) 0x83A714C)
#define sVanillaStepFuncs_6  ((const StepFunc*) 0x83A716C)
#define sVanillaStepFuncs_4  ((const StepFunc*) 0x83A7184)
#define sVanillaStepFuncs_2  ((const StepFunc*) 0x83A7194)

//Vanilla, one {s16 x, s16 y} unit vector per direction
#define sDirectionToVectors ((const struct Coords16*) 0x83A64C8)

//Vanilla table of animation number getters, one per speed tier, indexed the same way
typedef u8 (*AnimNumGetter)(u8 direction);
#define sAnimNumGetters ((const AnimNumGetter*) 0x83A6884)

typedef void (*StepFunc)(struct Sprite* sprite, u8 direction);

//Vanilla table pairing an animation set with the command indices its two step halves run
//between, searched by the sprite's own animation pointer. A step plays one half and the
//halves alternate, so the sprite leads with a different foot each tile.
struct StepAnimAlternation
{
	const union AnimCmd* const* anims;
	u8 firstHalfEnd;
	u8 secondHalfEnd;
	u8 firstHalfStart;
	u8 secondHalfStart;
};
#define sStepAnimAlternations ((const struct StepAnimAlternation*) 0x83A3698)

static void Step6px(struct Sprite* sprite, u8 direction);
static void Step5px(struct Sprite* sprite, u8 direction);
static u16 GetOverworldSpeedSetting(void);
static u8 RemapStepTier(struct EventObject* eventObject, u8 speed);
static bool8 ShouldEventObjectMatchPlayerSpeed(struct EventObject* eventObject);
static bool8 IsSpeedBoostAllowed(void);
static bool8 IsPrecisionMovementMap(void);
static const struct StepAnimAlternation* GetStepAnimAlternation(const union AnimCmd* const* anims);
static void DriveBoostedStepAnim(struct Sprite* sprite);
static void DriveBoostedSurfBob(struct EventObject* eventObject);

//6 then 5 then 5 covers a 16 pixel tile in three frames
static const StepFunc sStepFuncs_3[3] = {Step6px, Step5px, Step5px};

//Repointed over the two pointers NpcTakeStep reads, which are the only references to the
//vanilla tables anywhere in the ROM, so extending them cannot reach any other caller
const StepFunc* const gOverworldStepSpeeds[6] =
{
	[STEP_TIER_16_FRAME] = sVanillaStepFuncs_16,
	[STEP_TIER_8_FRAME]  = sVanillaStepFuncs_8,
	[STEP_TIER_6_FRAME]  = sVanillaStepFuncs_6,
	[STEP_TIER_4_FRAME]  = sVanillaStepFuncs_4,
	[STEP_TIER_2_FRAME]  = sVanillaStepFuncs_2,
	[STEP_TIER_3_FRAME]  = sStepFuncs_3,
};

const u16 gOverworldStepSeqLengths[6] =
{
	[STEP_TIER_16_FRAME] = 16,
	[STEP_TIER_8_FRAME]  = 8,
	[STEP_TIER_6_FRAME]  = 6,
	[STEP_TIER_4_FRAME]  = 4,
	[STEP_TIER_2_FRAME]  = 2,
	[STEP_TIER_3_FRAME]  = 3,
};

//The tier to use in place of each vanilla tier, per option. Walking is tier 0 and running is tier 1,
// so both hit an exact 2x and 4x; the 3x column is really 2.67x because 6 and 3 frames are the closest
// the pixel grid allows. Tiers already at or past the target clamp to the fastest row rather than slowing down.
static const u8 sBoostedStepTiers[OPTIONS_OVERWORLD_SPEED_COUNT][VANILLA_STEP_TIER_COUNT] =
{
	[OPTIONS_OVERWORLD_SPEED_NORMAL] = {STEP_TIER_16_FRAME, STEP_TIER_8_FRAME, STEP_TIER_6_FRAME, STEP_TIER_4_FRAME, STEP_TIER_2_FRAME},
	[OPTIONS_OVERWORLD_SPEED_2X]     = {STEP_TIER_8_FRAME,  STEP_TIER_4_FRAME, STEP_TIER_3_FRAME, STEP_TIER_2_FRAME, STEP_TIER_2_FRAME},
	[OPTIONS_OVERWORLD_SPEED_3X]     = {STEP_TIER_6_FRAME,  STEP_TIER_3_FRAME, STEP_TIER_2_FRAME, STEP_TIER_2_FRAME, STEP_TIER_2_FRAME},
	[OPTIONS_OVERWORLD_SPEED_4X]     = {STEP_TIER_4_FRAME,  STEP_TIER_2_FRAME, STEP_TIER_2_FRAME, STEP_TIER_2_FRAME, STEP_TIER_2_FRAME},
};

//How much faster the ground is passing at each setting. The 3x column is really 2.67x,
//but the bob is a loose visual rhythm rather than something that has to land on a frame.
static const u8 sSpeedMultipliers[OPTIONS_OVERWORLD_SPEED_COUNT] = {1, 2, 3, 4};

static void Step6px(struct Sprite* sprite, u8 direction)
{
	sprite->pos1.x += sDirectionToVectors[direction].x * 6;
	sprite->pos1.y += sDirectionToVectors[direction].y * 6;
}

static void Step5px(struct Sprite* sprite, u8 direction)
{
	sprite->pos1.x += sDirectionToVectors[direction].x * 5;
	sprite->pos1.y += sDirectionToVectors[direction].y * 5;
}

static u16 GetOverworldSpeedSetting(void)
{
	u16 setting = VarGet(VAR_OVERWORLD_SPEED);

	if (setting >= OPTIONS_OVERWORLD_SPEED_COUNT)
		return OPTIONS_OVERWORLD_SPEED_NORMAL;

	return setting;
}

static bool8 IsPrecisionMovementMap(void)
{
	if (MAP_IS(UTEYA_VILLAGE_GYM))
		return !FlagGet(0x3C);

	return MAP_IS(LAPLAZ_TOWN_GYM);
}

// Prevent boosted movement when player movement is controlled by a script (ex. cutscenes), using the DexNav, etc.
static bool8 IsSpeedBoostAllowed(void)
{
	if (ScriptContext2_IsEnabled())
		return FALSE;

	if (gPlayerAvatar->preventStep)
		return FALSE; // Follower sequences and field effects move the player from C, unlocked

	if (IsDexNavHudActive())
		return FALSE; // Running is already disallowed during a scan, so a boost would undo that

	if (IsPrecisionMovementMap())
		return FALSE;

	return TRUE;
}

static bool8 ShouldEventObjectMatchPlayerSpeed(struct EventObject* eventObject)
{
	if (eventObject == &gEventObjects[gPlayerAvatar->eventObjectId])
		return TRUE;

	if (gFollowerState.inProgress && eventObject == &gEventObjects[gFollowerState.objId])
		return TRUE;

	switch (eventObject->movementType) {
		case MOVEMENT_TYPE_COPY_PLAYER ... MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE:
		case MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS ... MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS:
			return TRUE; //Mirrors the player one step at a time, so it has to mirror the pace too
	}

	return FALSE;
}

static u8 RemapStepTier(struct EventObject* eventObject, u8 speed)
{
	if (speed >= VANILLA_STEP_TIER_COUNT)
		return speed;

	if (!ShouldEventObjectMatchPlayerSpeed(eventObject))
		return speed;

	if (!IsSpeedBoostAllowed())
		return speed;

	return sBoostedStepTiers[GetOverworldSpeedSetting()][speed];
}

static const struct StepAnimAlternation* GetStepAnimAlternation(const union AnimCmd* const* anims)
{
	const struct StepAnimAlternation* entry;

	for (entry = sStepAnimAlternations; entry->anims != NULL; ++entry)
	{
		if (entry->anims == anims)
			return entry;
	}

	return NULL;
}

static void DriveBoostedStepAnim(struct Sprite* sprite)
{
	const struct StepAnimAlternation* alt;
	const union AnimCmd* cmds;
	u16 stepFrames, offset;
	u8 commands, start;

	if (GetOverworldSpeedSetting() == OPTIONS_OVERWORLD_SPEED_NORMAL)
		return; //Leave the vanilla cadence alone

	alt = GetStepAnimAlternation(sprite->anims);
	if (alt == NULL)
		return; //Nothing declares halves for this set, so there is no step animation to drive

	commands = alt->firstHalfEnd + 1;
	cmds = sprite->anims[sprite->animNum];
	if (cmds[commands - 1].type < 0)
		return; //A single pose set, such as the surfing sprite - there is nothing to animate

	stepFrames = gOverworldStepSeqLengths[sprite->data[4]];
	if (stepFrames == 0)
		return;

	//Which half the alternation left us in. The driven index never leaves that half, so this
	//stays right for every frame of the step, and the step still ends on the half's last
	//command so the next alternation flips the way vanilla expects.
	start = (sprite->animCmdIndex >= alt->secondHalfStart) ? alt->secondHalfStart : alt->firstHalfStart;

	offset = ((u16) sprite->data[5] * commands) / stepFrames; //data[5] is the frame NpcTakeStep is about to run
	if (offset >= commands)
		offset = commands - 1;

	SeekSpriteAnim(sprite, start + offset);
}

//The surfing sprite is one static pose; all of its motion is the blob's bobbing, which runs on
//its own per frame counter and so falls behind once a tile takes fewer frames to cross.
//Ticking it by the speed multiplier keeps the same number of bobs per tile.
static void DriveBoostedSurfBob(struct EventObject* eventObject)
{
	struct Sprite* blob;
	u8 ticks;

	if (eventObject->fieldEffectSpriteId >= MAX_SPRITES)
		return;

	blob = &gSprites[eventObject->fieldEffectSpriteId];
	if (blob->callback != UpdateSurfBlobFieldEffect)
		return; //Some other field effect, or none at all

	for (ticks = sSpeedMultipliers[GetOverworldSpeedSetting()]; ticks > 1; --ticks)
		CreateBobbingEffect(eventObject, &gSprites[eventObject->spriteId], blob);
}

//Replaces the vanilla InitMovementNormal (0x80646FC), which every walk and slide movement action funnels through.
//The animation set stays the one vanilla would have picked; only the step tier moves.
void NewInitMovementNormal(struct EventObject* eventObject, struct Sprite* sprite, u8 direction, u8 speed)
{
	InitNpcForMovement(eventObject, sprite, direction, RemapStepTier(eventObject, speed));
	SetStepAnimHandleAlternation(eventObject, sprite, sAnimNumGetters[speed](eventObject->facingDirection));
}

//Replaces the vanilla StartRunningAnim (0x8064758), which the slide-right-foot movement actions funnel through
void NewStartRunningAnim(struct EventObject* eventObject, struct Sprite* sprite, u8 direction)
{
	InitNpcForMovement(eventObject, sprite, direction, RemapStepTier(eventObject, STEP_TIER_8_FRAME));
	SetStepAnimHandleAlternation(eventObject, sprite, GetRunningDirectionAnimNum(eventObject->facingDirection));
}

//Replaces the vanilla UpdateMovementNormal (0x8064788), the per frame step update every walk, slide and run movement action shares
bool8 NewUpdateMovementNormal(struct EventObject* eventObject, struct Sprite* sprite)
{
	if (ShouldEventObjectMatchPlayerSpeed(eventObject) && IsSpeedBoostAllowed())
	{
		DriveBoostedStepAnim(sprite);
		DriveBoostedSurfBob(eventObject);
	}

	if (!NpcTakeStep(sprite))
		return FALSE;

	ShiftStillEventObjectCoords(eventObject);
	eventObject->triggerGroundEffectsOnStop = TRUE;
	sprite->animPaused = TRUE;
	return TRUE;
}
