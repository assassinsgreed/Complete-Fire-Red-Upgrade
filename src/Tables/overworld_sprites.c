#include "../defines.h"
#include "../../include/constants/event_objects.h"

// MC
extern const u8 MCStandingTiles[];
extern const u8 MCCyclingTiles[];
extern const u8 MCSurfingTiles[];
extern const u8 MCFieldMoveTiles[];
extern const u8 MCFishingTiles[];
extern const u8 MCVSSeekerBikeTiles[];

extern const u8 FeMCStandingTiles[];

// Characters
extern const u8 PlutoGruntMaleTiles[];
extern const u8 LeaderTerrenceTiles[];
extern const u8 ChampionSeleneTiles[];

// Overworld Events
extern const u8 SandygastTiles[];
extern const u8 FoongusTiles[];
extern const u8 StunfiskTiles[];
extern const u8 TMPokeballTiles[];

#define EVENT_OBJ_PAL_TAG_NONE 0x1102
#define gEventObjectBaseOam_16x16 ((const struct OamData*) 0x83A36F8)
#define gEventObjectBaseOam_16x32 ((const struct OamData*) 0x83A3710)
#define gEventObjectBaseOam_32x32 ((const struct OamData*) 0x83A3718)
#define gEventObjectBaseOam_64x64 ((const struct OamData*) 0x83A3720)
#define gEventObjectSpriteOamTables_16x16 ((const struct SubspriteTable*) 0x83A3748)
#define gEventObjectSpriteOamTables_16x32 ((const struct SubspriteTable*) 0x83A379C)
#define gEventObjectSpriteOamTables_32x32 ((const struct SubspriteTable*) 0x83A37F0)
#define gEventObjectSpriteOamTables_64x64 ((const struct SubspriteTable*) 0x83A38D0)
#define gEventObjectImageAnimTable_PlayerNormal ((const union AnimCmd* const*) 0x83A3470)
#define gEventObjectImageAnimTable_Standard ((const union AnimCmd* const*) 0x83A3368)
#define gEventObjectImageAnimTable_Surfing ((const union AnimCmd* const*) 0x83A3584)
#define gEventObjectImageAnimTable_FieldMove ((const union AnimCmd* const*) 0x83A3638)
#define gEventObjectImageAnimTable_Fishing ((const union AnimCmd* const*) 0x83A3668)
#define gEventObjectImageAnimTable_VsSeekerBike ((const union AnimCmd* const*) 0x83A3640)

// #region MC
static const struct SpriteFrameImage Table_MCStanding[] =
{
    overworld_frame(MCStandingTiles, 2, 4, 0),
    overworld_frame(MCStandingTiles, 2, 4, 1),
    overworld_frame(MCStandingTiles, 2, 4, 2),
    overworld_frame(MCStandingTiles, 2, 4, 3),
    overworld_frame(MCStandingTiles, 2, 4, 4),
    overworld_frame(MCStandingTiles, 2, 4, 5),
    overworld_frame(MCStandingTiles, 2, 4, 6),
    overworld_frame(MCStandingTiles, 2, 4, 7),
    overworld_frame(MCStandingTiles, 2, 4, 8),
    overworld_frame(MCStandingTiles, 2, 4, 9),
    overworld_frame(MCStandingTiles, 2, 4, 10),
    overworld_frame(MCStandingTiles, 2, 4, 11),
    overworld_frame(MCStandingTiles, 2, 4, 12),
    overworld_frame(MCStandingTiles, 2, 4, 13),
    overworld_frame(MCStandingTiles, 2, 4, 14),
    overworld_frame(MCStandingTiles, 2, 4, 15),
    overworld_frame(MCStandingTiles, 2, 4, 16),
    overworld_frame(MCStandingTiles, 2, 4, 17),
    overworld_frame(MCStandingTiles, 2, 4, 18),
    overworld_frame(MCStandingTiles, 2, 4, 19),
};

static const struct SpriteFrameImage Table_MCCycling[] =
{
    overworld_frame(MCCyclingTiles, 4, 4, 0),
    overworld_frame(MCCyclingTiles, 4, 4, 1),
    overworld_frame(MCCyclingTiles, 4, 4, 2),
    overworld_frame(MCCyclingTiles, 4, 4, 3),
    overworld_frame(MCCyclingTiles, 4, 4, 4),
    overworld_frame(MCCyclingTiles, 4, 4, 5),
    overworld_frame(MCCyclingTiles, 4, 4, 6),
    overworld_frame(MCCyclingTiles, 4, 4, 7),
    overworld_frame(MCCyclingTiles, 4, 4, 8),
};

static const struct SpriteFrameImage Table_MCSurfing[] =
{
    overworld_frame(MCSurfingTiles, 2, 4, 0),
    overworld_frame(MCSurfingTiles, 2, 4, 1),
    overworld_frame(MCSurfingTiles, 2, 4, 2),
    overworld_frame(MCSurfingTiles, 2, 4, 3),
    overworld_frame(MCSurfingTiles, 2, 4, 4),
    overworld_frame(MCSurfingTiles, 2, 4, 5),
    overworld_frame(MCSurfingTiles, 2, 4, 6),
    overworld_frame(MCSurfingTiles, 2, 4, 7),
    overworld_frame(MCSurfingTiles, 2, 4, 8),
    overworld_frame(MCSurfingTiles, 2, 4, 9),
    overworld_frame(MCSurfingTiles, 2, 4, 10),
    overworld_frame(MCSurfingTiles, 2, 4, 11),
};

static const struct SpriteFrameImage Table_MCFieldMove[] =
{
    overworld_frame(MCFieldMoveTiles, 4, 4, 0),
    overworld_frame(MCFieldMoveTiles, 4, 4, 1),
    overworld_frame(MCFieldMoveTiles, 4, 4, 2),
    overworld_frame(MCFieldMoveTiles, 4, 4, 3),
    overworld_frame(MCFieldMoveTiles, 4, 4, 4),
    overworld_frame(MCFieldMoveTiles, 4, 4, 5),
    overworld_frame(MCFieldMoveTiles, 4, 4, 6),
    overworld_frame(MCFieldMoveTiles, 4, 4, 7),
    overworld_frame(MCFieldMoveTiles, 4, 4, 8),
};

static const struct SpriteFrameImage Table_MCFishing[] =
{
    overworld_frame(MCFishingTiles, 4, 4, 0),
    overworld_frame(MCFishingTiles, 4, 4, 1),
    overworld_frame(MCFishingTiles, 4, 4, 2),
    overworld_frame(MCFishingTiles, 4, 4, 3),
    overworld_frame(MCFishingTiles, 4, 4, 4),
    overworld_frame(MCFishingTiles, 4, 4, 5),
    overworld_frame(MCFishingTiles, 4, 4, 6),
    overworld_frame(MCFishingTiles, 4, 4, 7),
    overworld_frame(MCFishingTiles, 4, 4, 8),
    overworld_frame(MCFishingTiles, 4, 4, 9),
    overworld_frame(MCFishingTiles, 4, 4, 10),
    overworld_frame(MCFishingTiles, 4, 4, 11),
};

static const struct SpriteFrameImage Table_MCVSSeekerBike[] =
{
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 0),
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 1),
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 2),
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 3),
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 4),
    overworld_frame(MCVSSeekerBikeTiles, 4, 4, 5),
};

static const struct SpriteFrameImage Table_FeMCStanding[] =
{
    overworld_frame(FeMCStandingTiles, 2, 4, 0),
    overworld_frame(FeMCStandingTiles, 2, 4, 1),
    overworld_frame(FeMCStandingTiles, 2, 4, 2),
    overworld_frame(FeMCStandingTiles, 2, 4, 3),
    overworld_frame(FeMCStandingTiles, 2, 4, 4),
    overworld_frame(FeMCStandingTiles, 2, 4, 5),
    overworld_frame(FeMCStandingTiles, 2, 4, 6),
    overworld_frame(FeMCStandingTiles, 2, 4, 7),
    overworld_frame(FeMCStandingTiles, 2, 4, 8),
    overworld_frame(FeMCStandingTiles, 2, 4, 9),
    overworld_frame(FeMCStandingTiles, 2, 4, 10),
    overworld_frame(FeMCStandingTiles, 2, 4, 11),
    overworld_frame(FeMCStandingTiles, 2, 4, 12),
    overworld_frame(FeMCStandingTiles, 2, 4, 13),
    overworld_frame(FeMCStandingTiles, 2, 4, 14),
    overworld_frame(FeMCStandingTiles, 2, 4, 15),
    overworld_frame(FeMCStandingTiles, 2, 4, 16),
    overworld_frame(FeMCStandingTiles, 2, 4, 17),
    overworld_frame(FeMCStandingTiles, 2, 4, 18),
    overworld_frame(FeMCStandingTiles, 2, 4, 19),
};
// #endregion MC

static const struct SpriteFrameImage Table_PlutoGruntMale[] =
{
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 0),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 1),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 2),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 3),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 4),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 5),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 6),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 7),
    overworld_frame(PlutoGruntMaleTiles, 2, 4, 8),
};

static const struct SpriteFrameImage Table_LeaderTerrence[] =
{
    overworld_frame(LeaderTerrenceTiles, 2, 4, 0),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 1),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 2),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 3),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 4),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 5),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 6),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 7),
    overworld_frame(LeaderTerrenceTiles, 2, 4, 8),
};

static const struct SpriteFrameImage Table_ChampionSelene[] =
{
    overworld_frame(ChampionSeleneTiles, 2, 4, 0),
    overworld_frame(ChampionSeleneTiles, 2, 4, 1),
    overworld_frame(ChampionSeleneTiles, 2, 4, 2),
    overworld_frame(ChampionSeleneTiles, 2, 4, 3),
    overworld_frame(ChampionSeleneTiles, 2, 4, 4),
    overworld_frame(ChampionSeleneTiles, 2, 4, 5),
    overworld_frame(ChampionSeleneTiles, 2, 4, 6),
    overworld_frame(ChampionSeleneTiles, 2, 4, 7),
    overworld_frame(ChampionSeleneTiles, 2, 4, 8),
};

static const struct SpriteFrameImage Table_Sandygast[] =
{
    overworld_frame(SandygastTiles, 2, 2, 0),
    overworld_frame(SandygastTiles, 2, 2, 1),
    overworld_frame(SandygastTiles, 2, 2, 2),
    overworld_frame(SandygastTiles, 2, 2, 3),
    overworld_frame(SandygastTiles, 2, 2, 4),
    overworld_frame(SandygastTiles, 2, 2, 5),
    overworld_frame(SandygastTiles, 2, 2, 6),
    overworld_frame(SandygastTiles, 2, 2, 7),
    overworld_frame(SandygastTiles, 2, 2, 8),
};

static const struct SpriteFrameImage Table_Foongus[] =
{
    overworld_frame(FoongusTiles, 2, 2, 0),
};

static const struct SpriteFrameImage Table_Stunfisk[] =
{
    overworld_frame(StunfiskTiles, 2, 2, 0),
};

static const struct SpriteFrameImage Table_TMPokeball[] =
{
    overworld_frame(TMPokeballTiles, 2, 2, 0),
};

// #region MC
const struct EventObjectGraphicsInfo GraphicsInfo_MCStanding =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_PlayerNormal,
    .images = Table_MCStanding,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_MCCycling =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (32 * 32) / 2,
    .width = 32,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_32x32,
    .subspriteTables = gEventObjectSpriteOamTables_32x32,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_MCCycling,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_MCSurfing =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_Surfing,
    .images = Table_MCSurfing,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_MCFieldMove =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_FieldMove,
    .images = Table_MCFieldMove,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_MCFishing =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (32 * 32) / 2,
    .width = 32,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_32x32,
    .subspriteTables = gEventObjectSpriteOamTables_32x32,
    .anims = gEventObjectImageAnimTable_Fishing,
    .images = Table_MCFishing,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_MCVSSeekerBike =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1207,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (32 * 32) / 2,
    .width = 32,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_32x32,
    .subspriteTables = gEventObjectSpriteOamTables_32x32,
    .anims = gEventObjectImageAnimTable_VsSeekerBike,
    .images = Table_MCVSSeekerBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_FeMCStanding =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1208,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .gender = FEMALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_PlayerNormal,
    .images = Table_FeMCStanding,
    .affineAnims = gDummySpriteAffineAnimTable,
};
// #endregion MC

const struct EventObjectGraphicsInfo GraphicsInfo_PlutoGruntMale =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1201,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_PlutoGruntMale,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_LeaderTerrence =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1206,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_LeaderTerrence,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_ChampionSelene =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1202,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 32) / 2,
    .width = 16,
    .height = 32,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .gender = FEMALE,
    .oam = gEventObjectBaseOam_16x32,
    .subspriteTables = gEventObjectSpriteOamTables_16x32,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_ChampionSelene,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_Sandygast =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1203,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 16) / 2,
    .width = 16,
    .height = 16,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x16,
    .subspriteTables = gEventObjectSpriteOamTables_16x16,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_Sandygast,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_Foongus =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1204,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 16) / 2,
    .width = 16,
    .height = 16,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x16,
    .subspriteTables = gEventObjectSpriteOamTables_16x16,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_Foongus,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_Stunfisk =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1204,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 16) / 2,
    .width = 16,
    .height = 16,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x16,
    .subspriteTables = gEventObjectSpriteOamTables_16x16,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_Stunfisk,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct EventObjectGraphicsInfo GraphicsInfo_TMPokeball =
{
    .tileTag = 0xFFFF,
    .paletteTag1 = 0x1205,
    .paletteTag2 = EVENT_OBJ_PAL_TAG_NONE,
    .size = (16 * 16) / 2,
    .width = 16,
    .height = 16,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .gender = MALE,
    .oam = gEventObjectBaseOam_16x16,
    .subspriteTables = gEventObjectSpriteOamTables_16x16,
    .anims = gEventObjectImageAnimTable_Standard,
    .images = Table_TMPokeball,
    .affineAnims = gDummySpriteAffineAnimTable,
};
