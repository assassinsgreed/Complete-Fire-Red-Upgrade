#include "defines.h"
#include "../include/event_object_movement.h"
#include "../include/fieldmap.h"
#include "../include/main.h"
#include "../include/sprite.h"
#include "../include/constants/maps.h"

/*
Per-map-coordinate and per-metatile overrides of a metatile's layer type, for when a
shared metatile's attributes can't be edited but it needs to draw differently.

NORMAL puts the top layer on BG1 (priority 1), above the overworld fog sprites
(OAM priority 2). COVERED moves it to BG2, where the fog draws over it, but a
priority-2 sprite would then draw over it too. BuildOamBufferWithOcclusion puts the
overlapping parts of those sprites back underneath, so overridden COVERED tiles
still hide sprites the way they did as NORMAL.
*/

#define METATILE_ATTRIBUTE_LAYER_TYPE 6 // Attribute bits 28-30

// Not vanilla's numbering: the base ROM's triple-layer DrawMetatile (jump table @0x885058C)
// renumbers layer types as 0/1 normal, 2 covered, 3 triple, 4 split.
#define METATILE_LAYER_TYPE_NORMAL_MAX 1
#define METATILE_LAYER_TYPE_COVERED    2
#define METATILE_LAYER_TYPE_SPLIT      4 // Bottom on BG3, top on BG1, BG2 empty
#define NO_LAYER_OVERRIDE              0xFF
#define MAP_OFFSET                     7

struct MetatileLayerOverride
{
	u8 mapGroup;
	u8 mapNum;
	u8 x, y, width, height;
	u8 layerType;
};

static const struct MetatileLayerOverride sMetatileLayerOverrides[] =
{
	{MAP_GROUP(ROUTE_8), MAP_NUM(ROUTE_8), 27, 94, 3, 11, METATILE_LAYER_TYPE_COVERED}, // Bridge planks
	// The white corner pillar above the doorway (31,158)-(31,159) stays on BG1: the player in the
	// doorway overlaps it, and moving it under the fog would hide the player behind the fog too.
	{MAP_GROUP(ROUTE_8), MAP_NUM(ROUTE_8), 32, 159, 1, 2, METATILE_LAYER_TYPE_COVERED}, // Southern building's tan brick column
};

struct MetatileIdLayerOverride
{
	u16 metatileId;
	u8 layerType;
};

// Applied on every map.
static const struct MetatileIdLayerOverride sMetatileIdLayerOverrides[] =
{
	{0x0FA, METATILE_LAYER_TYPE_COVERED}, // Tree crown over a ledge, left
	{0x0FB, METATILE_LAYER_TYPE_COVERED}, // Tree crown over a ledge, right
	{0x04F, METATILE_LAYER_TYPE_COVERED}, // Bottom edge of a building's windows
};

static u8 GetLayerTypeOverride(s16 x, s16 y)
{
	u32 i;
	s32 mapX = x - MAP_OFFSET;
	s32 mapY = y - MAP_OFFSET;
	u32 metatileId = MapGridGetMetatileIdAt(x, y);

	for (i = 0; i < ARRAY_COUNT(sMetatileIdLayerOverrides); ++i)
	{
		if (metatileId == sMetatileIdLayerOverrides[i].metatileId)
			return sMetatileIdLayerOverrides[i].layerType;
	}

	for (i = 0; i < ARRAY_COUNT(sMetatileLayerOverrides); ++i)
	{
		const struct MetatileLayerOverride* override = &sMetatileLayerOverrides[i];

		if (gSaveBlock1->location.mapGroup == override->mapGroup
		&& gSaveBlock1->location.mapNum == override->mapNum
		&& mapX >= override->x && mapX < override->x + override->width
		&& mapY >= override->y && mapY < override->y + override->height)
			return override->layerType;
	}

	return NO_LAYER_OVERRIDE;
}

// A NORMAL metatile moved to COVERED: its top layer hid sprites from BG1 and must keep doing so.
// One that was already COVERED never hid sprites, e.g. a doorway the player stands in.
static bool8 IsSpriteOccluderAt(s16 x, s16 y)
{
	return GetLayerTypeOverride(x, y) == METATILE_LAYER_TYPE_COVERED
		&& MapGridGetMetatileField(x, y, METATILE_ATTRIBUTE_LAYER_TYPE) <= METATILE_LAYER_TYPE_NORMAL_MAX;
}

static bool8 IsNextToSpriteOccluder(s16 x, s16 y)
{
	s32 dx, dy;

	for (dy = -1; dy <= 1; ++dy)
	{
		for (dx = -1; dx <= 1; ++dx)
		{
			if ((dx != 0 || dy != 0) && IsSpriteOccluderAt(x + dx, y + dy))
				return TRUE;
		}
	}

	return FALSE;
}

u8 MapGridGetMetatileLayerTypeAt(s16 x, s16 y)
{
	u8 layerType = GetLayerTypeOverride(x, y);

	if (layerType != NO_LAYER_OVERRIDE)
		return layerType;

	layerType = MapGridGetMetatileField(x, y, METATILE_ATTRIBUTE_LAYER_TYPE);

	// A sprite piece pushed under an occluder can stick out up to 7px onto its neighbours.
	// SPLIT draws exactly like NORMAL for everything at priority 2 and above, but keeps the
	// bottom layer off BG2 so that overhang isn't cut off by it.
	if (layerType <= METATILE_LAYER_TYPE_NORMAL_MAX && IsNextToSpriteOccluder(x, y))
		return METATILE_LAYER_TYPE_SPLIT;

	return layerType;
}

/*
Sprites under overridden COVERED tiles (Route 8 bridge, tree crowns 0FA/0FB, ...).

Those top layers have to be under the fog but over a sprite such as a surfer or its surf
blob. The fog is a priority-2 sprite, the surfer is a priority-2 sprite drawn in front of
it, and no BG layer can sit between two sprites of the same priority. So every frame each
priority-2 sprite overlapping an occluder tile is split into 8x8 pieces:
- Pieces clear of occluder tiles stay in the sprite at priority 2, in front of the fog as usual.
- A copy of the whole sprite is appended after every other OAM entry at priority 3, under
  BG2. Where the priority-2 pieces exist they win, so only the occluded pieces show.

The copy has to come after the fog in OAM. A priority-3 piece earlier in OAM than the fog
would either punch a hole in the fog or get raised back over BG2, depending on how the
hardware resolves sprite-vs-sprite overlap at different priorities.

Everything is rebuilt from scratch each frame and restored before returning, so there is
no state to clean up on warps, battles or saves.
*/

#define MAX_SPLIT_SPRITES 4  // Player, surf blob, follower, follower's surf blob
#define MAX_SPLIT_PIECES  16 // 32x32 in 8x8 pieces; larger sprites aren't split
#define MAX_SPAN_TILES    3  // A sprite up to 32px wide or tall touches at most 3 tiles
#define OCCLUDED_PRIORITY 3

extern u8 gOamLimit;

struct SplitSprite
{
	struct Sprite* sprite;
	const struct SubspriteTable* subspriteTables;
	u8 subspriteTableNum;
	u8 subspriteMode;
};

struct SplitBuffers
{
	struct SplitSprite saved[MAX_SPLIT_SPRITES];
	struct SubspriteTable tables[MAX_SPLIT_SPRITES][2]; // [0] unused: table 0 means "no subsprites"
	struct Subsprite pieces[MAX_SPLIT_SPRITES][MAX_SPLIT_PIECES];
};

// The sprite is drawn as one block at a single priority, or it isn't a split candidate.
static bool8 GetSingleBlockPriority(const struct Sprite* sprite, u8* priority)
{
	if (sprite->subspriteMode != SUBSPRITES_OFF && sprite->subspriteTableNum != 0 && sprite->subspriteTables != NULL)
	{
		const struct SubspriteTable* table = &sprite->subspriteTables[sprite->subspriteTableNum];

		if (table->subsprites != NULL)
		{
			if (table->subspriteCount != 1)
				return FALSE;

			*priority = (sprite->subspriteMode == SUBSPRITES_IGNORE_PRIORITY) ? sprite->oam.priority : table->subsprites[0].priority;
			return TRUE;
		}
	}

	*priority = sprite->oam.priority;
	return TRUE;
}

// gridOriginX/Y: screen position of grid tile (0,0). Returns how many pieces stay in
// front, or -1 if the sprite touches no occluder.
static s32 SplitSpriteAroundOccluders(const struct Sprite* sprite, s32 gridOriginX, s32 gridOriginY, struct Subsprite* pieces)
{
	u32 row, col, cols, rows;
	s32 centerX, centerY, width, height, firstTileX, firstTileY, tx, ty;
	bool8 hFlip, vFlip, anyOccluded = FALSE, anyOccluder = FALSE;
	bool8 occluder[MAX_SPAN_TILES][MAX_SPAN_TILES];
	s32 count = 0;

	width = gOamDimensions[sprite->oam.shape][sprite->oam.size].width;
	height = gOamDimensions[sprite->oam.shape][sprite->oam.size].height;
	centerX = sprite->pos1.x + sprite->pos2.x;
	centerY = sprite->pos1.y + sprite->pos2.y;

	if (sprite->coordOffsetEnabled)
	{
		centerX += gSpriteCoordOffsetX;
		centerY += gSpriteCoordOffsetY;
	}

	// Arithmetic shifts floor, so this is right left of / above the grid origin too.
	firstTileX = (centerX + sprite->centerToCornerVecX - gridOriginX) >> 4;
	firstTileY = (centerY + sprite->centerToCornerVecY - gridOriginY) >> 4;

	for (ty = 0; ty < MAX_SPAN_TILES; ++ty)
	{
		for (tx = 0; tx < MAX_SPAN_TILES; ++tx)
		{
			occluder[ty][tx] = IsSpriteOccluderAt(firstTileX + tx, firstTileY + ty);
			anyOccluder |= occluder[ty][tx];
		}
	}

	if (!anyOccluder)
		return -1;

	cols = width / 8;
	rows = height / 8;
	hFlip = (sprite->oam.matrixNum & ST_OAM_HFLIP) != 0;
	vFlip = (sprite->oam.matrixNum & ST_OAM_VFLIP) != 0;

	for (row = 0; row < rows; ++row)
	{
		for (col = 0; col < cols; ++col)
		{
			// Offsets from the centre, flipped the same way AddSubspritesToOamBuffer flips them.
			s32 pieceX = sprite->centerToCornerVecX + col * 8;
			s32 pieceY = sprite->centerToCornerVecY + row * 8;
			s32 left = centerX + (hFlip ? -(pieceX + 8) : pieceX) - gridOriginX;
			s32 top = centerY + (vFlip ? -(pieceY + 8) : pieceY) - gridOriginY;
			bool8 occluded = FALSE;

			for (ty = (top >> 4) - firstTileY; ty <= ((top + 7) >> 4) - firstTileY; ++ty)
			{
				for (tx = (left >> 4) - firstTileX; tx <= ((left + 7) >> 4) - firstTileX; ++tx)
				{
					if (ty >= 0 && ty < MAX_SPAN_TILES && tx >= 0 && tx < MAX_SPAN_TILES && occluder[ty][tx])
						occluded = TRUE;
				}
			}

			if (occluded)
			{
				anyOccluded = TRUE;
				continue;
			}

			pieces[count].x = pieceX;
			pieces[count].y = pieceY;
			pieces[count].shape = ST_OAM_SQUARE;
			pieces[count].size = 0; // 8x8
			pieces[count].tileOffset = row * cols + col;
			pieces[count].priority = sprite->oam.priority; // Unused under SUBSPRITES_IGNORE_PRIORITY
			++count;
		}
	}

	return anyOccluded ? count : -1;
}

static bool8 IsDummyOamEntry(const struct OamData* oam)
{
	const u16* entry = (const u16*) oam;
	const u16* dummy = (const u16*) &gDummyOamData;

	// The fourth halfword holds affine matrix data, not attributes.
	return entry[0] == dummy[0] && entry[1] == dummy[1] && entry[2] == dummy[2];
}

static void AppendOccludedCopies(const struct SplitBuffers* buffers, u32 numSplit)
{
	u32 i, freeIndex = gOamLimit;

	while (freeIndex > 0 && IsDummyOamEntry(&gMain.oamBuffer[freeIndex - 1]))
		--freeIndex;

	for (i = 0; i < numSplit && freeIndex < gOamLimit; ++i, ++freeIndex)
	{
		// BuildOamBuffer has just set oam.x/y for this frame.
		const u16* src = (const u16*) &buffers->saved[i].sprite->oam;
		u16* dst = (u16*) &gMain.oamBuffer[freeIndex];

		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = (src[2] & ~0x0C00) | (OCCLUDED_PRIORITY << 10);
	}
}

void BuildOamBufferWithOcclusion(void)
{
	struct SplitBuffers buffers;
	u32 i, numSplit = 0;
	s32 gridOriginX = 0, gridOriginY = 0;
	bool8 oamLoadDisabled;

	// The engine function writes halfwords, so the upper halves must be discarded.
	SetSpritePosToOffsetMapCoords(&gridOriginX, &gridOriginY, 0, 0);
	gridOriginX = (s16) gridOriginX + gSpriteCoordOffsetX;
	gridOriginY = (s16) gridOriginY + gSpriteCoordOffsetY;

	for (i = 0; i < MAX_SPRITES && numSplit < MAX_SPLIT_SPRITES; ++i)
	{
		struct Sprite* sprite = &gSprites[i];
		s32 numFront;
		u8 priority;

		if (!sprite->inUse || sprite->invisible
		|| sprite->oam.affineMode != ST_OAM_AFFINE_OFF
		|| sprite->oam.objMode != ST_OAM_OBJ_NORMAL // Excludes the fog itself
		|| sprite->oam.bpp != ST_OAM_4BPP
		|| gOamDimensions[sprite->oam.shape][sprite->oam.size].width > 32
		|| gOamDimensions[sprite->oam.shape][sprite->oam.size].height > 32
		|| !GetSingleBlockPriority(sprite, &priority)
		|| priority != 2) // Priority 1 (e.g. walkers on the bridge) is already above BG1
			continue;

		numFront = SplitSpriteAroundOccluders(sprite, gridOriginX, gridOriginY, buffers.pieces[numSplit]);
		if (numFront < 0)
			continue;

		buffers.saved[numSplit].sprite = sprite;
		buffers.saved[numSplit].subspriteTables = sprite->subspriteTables;
		buffers.saved[numSplit].subspriteTableNum = sprite->subspriteTableNum;
		buffers.saved[numSplit].subspriteMode = sprite->subspriteMode;

		// A count of 0 with a non-null list draws nothing, while still updating oam.x/y.
		buffers.tables[numSplit][0].subspriteCount = 0;
		buffers.tables[numSplit][0].subsprites = NULL;
		buffers.tables[numSplit][1].subspriteCount = numFront;
		buffers.tables[numSplit][1].subsprites = buffers.pieces[numSplit];
		sprite->subspriteTables = buffers.tables[numSplit];
		sprite->subspriteTableNum = 1;
		sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
		++numSplit;
	}

	if (numSplit == 0)
	{
		BuildOamBuffer();
		return;
	}

	// Keep VBlank from copying a buffer that doesn't have the copies yet.
	oamLoadDisabled = gMain.oamLoadDisabled;
	gMain.oamLoadDisabled = TRUE;

	BuildOamBuffer();

	for (i = 0; i < numSplit; ++i)
	{
		struct Sprite* sprite = buffers.saved[i].sprite;

		sprite->subspriteTables = buffers.saved[i].subspriteTables;
		sprite->subspriteTableNum = buffers.saved[i].subspriteTableNum;
		sprite->subspriteMode = buffers.saved[i].subspriteMode;
	}

	AppendOccludedCopies(&buffers, numSplit);
	gMain.oamLoadDisabled = oamLoadDisabled;
}

// Replaces OverworldBasic's tail call to BuildOamBuffer (0x805659A, see hooks).
// OverworldBasic pushed lr on entry, so this returns straight to its caller.
void __attribute__((naked)) OverworldBasic_BuildOamBufferHook(void)
{
	asm_unified(
		"bl BuildOamBufferWithOcclusion\n"
		"pop {r0}\n"
		"bx r0\n");
}
