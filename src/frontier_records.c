#include "defines.h"
#include "../include/bg.h"
#include "../include/event_data.h"
#include "../include/field_weather.h"
#include "../include/gpu_regs.h"
#include "../include/menu.h"
#include "../include/overworld.h"
#include "../include/palette.h"
#include "../include/region_map.h"
#include "../include/scanline_effect.h"
#include "../include/string_util.h"
#include "../include/text.h"
#include "../include/text_window.h"
#include "../include/window.h"
#include "../include/constants/songs.h"
#include "../include/gba/io_reg.h"

#include "../include/new/dns.h"
#include "../include/new/frontier.h"

/*
frontier_records.c
	Displays player's records in the Battle Frontier.
*/

#define BRONZE_STAR_STREAK 20
#define SILVER_STAR_STREAK 50
#define GOLD_STAR_STREAK 100
#define STAR_SPRITE_COUNT NUM_FRONTIER_FORMATS //One star per format block

// Amethyst has a single tier per facility/format pair
struct FrontierRecords
{
	u8* tilemapPtr;
	u8 facilityNum;
	u16 scrollArrowDummy;
	u8 starSpriteIds[STAR_SPRITE_COUNT];
};

#define sFrontierRecordsPtr (*((struct FrontierRecords**) 0x203E038))

extern const u8 gInterfaceGfx_FrontierRecordsTiles[];
extern const u8 gInterfaceGfx_FrontierRecordsPal[];
extern const u8 gInterfaceGfx_FrontierRecordsMap[];
extern const u8 Frontier_Record_BronzeStarTiles[];
extern const u8 Frontier_Record_BronzeStarPal[];
extern const u8 Frontier_Record_SilverStarPal[];
extern const u8 Frontier_Record_GoldStarPal[];

extern const u8 gText_FrontierRecordsTitle[];
extern const u8 gText_FrontierRecordSingles[];
extern const u8 gText_FrontierRecordDoubles[];
extern const u8 gText_CurrentStreak[];
extern const u8 gText_MaxStreak[];

enum Windows
{
	WIN_BATTLE_FACILITY_NAME,
	WIN_BATTLE_TYPE,
	WIN_SINGLES,
	WIN_SINGLES_CURRENT_STREAK,
	WIN_SINGLES_MAX_STREAK,
	WIN_DOUBLES,
	WIN_DOUBLES_CURRENT_STREAK,
	WIN_DOUBLES_MAX_STREAK,

//Buffered Data
	WIN_SINGLES_CURRENT_STREAK_NUM,
	WIN_SINGLES_MAX_STREAK_NUM,
	WIN_DOUBLES_CURRENT_STREAK_NUM,
	WIN_DOUBLES_MAX_STREAK_NUM,
	WINDOW_COUNT,
};

static const struct WindowTemplate sFrontierRecordsWinTemplates[WINDOW_COUNT + 1] __attribute__((aligned(4))) =
{
	[WIN_BATTLE_FACILITY_NAME] =
	{
		.bg = 0,
		.tilemapLeft = 1,
		.tilemapTop = 0,
		.width = 13,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 1,
	},
	[WIN_BATTLE_TYPE] =
	{
		.bg = 0,
		.tilemapLeft = 16,
		.tilemapTop = 0,
		.width = 14,
		.height = 3,
		.paletteNum = 15,
		.baseBlock = 40,
	},
	[WIN_SINGLES] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 4,
		.width = 6,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 82,
	},
	[WIN_SINGLES_CURRENT_STREAK] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 6,
		.width = 10,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 94,
	},
	[WIN_SINGLES_MAX_STREAK] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 8,
		.width = 10,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 114,
	},
	[WIN_DOUBLES] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 11,
		.width = 6,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 134,
	},
	[WIN_DOUBLES_CURRENT_STREAK] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 13,
		.width = 10,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 146,
	},
	[WIN_DOUBLES_MAX_STREAK] =
	{
		.bg = 0,
		.tilemapLeft = 2,
		.tilemapTop = 15,
		.width = 10,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 166,
	},

//Buffered Data Windows
	[WIN_SINGLES_CURRENT_STREAK_NUM] =
	{
		.bg = 0,
		.tilemapLeft = 15,
		.tilemapTop = 6,
		.width = 4,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 186,
	},
	[WIN_SINGLES_MAX_STREAK_NUM] =
	{
		.bg = 0,
		.tilemapLeft = 15,
		.tilemapTop = 8,
		.width = 4,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 194,
	},
	[WIN_DOUBLES_CURRENT_STREAK_NUM] =
	{
		.bg = 0,
		.tilemapLeft = 15,
		.tilemapTop = 13,
		.width = 4,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 202,
	},
	[WIN_DOUBLES_MAX_STREAK_NUM] =
	{
		.bg = 0,
		.tilemapLeft = 15,
		.tilemapTop = 15,
		.width = 4,
		.height = 2,
		.paletteNum = 15,
		.baseBlock = 210,
	},

	DUMMY_WIN_TEMPLATE,
};

static const struct BgTemplate sFrontierRecordsBgTemplates[] =
{
    { //Card Background
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0,
    },
    { //Text
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    { //Instructions
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 24,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    }
};

enum
{
	STAR_TAG_BRONZE = 0x2710,
	STAR_TAG_SILVER,
	STAR_TAG_GOLD,
};

static const struct OamData sStarOAM =
{
	.affineMode = ST_OAM_AFFINE_DOUBLE,
	.objMode = ST_OAM_OBJ_NORMAL,
	.shape = SPRITE_SHAPE(8x8),
	.size = SPRITE_SIZE(8x8),
	.priority = 0, //Above everything
};
static const struct SpriteTemplate sBronzeStarTemplate =
{
	.tileTag = STAR_TAG_BRONZE,
	.paletteTag = STAR_TAG_BRONZE,
	.oam = &sStarOAM,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSilverStarTemplate =
{
	.tileTag = STAR_TAG_BRONZE,
	.paletteTag = STAR_TAG_SILVER,
	.oam = &sStarOAM,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sGoldStarTemplate =
{
	.tileTag = STAR_TAG_BRONZE,
	.paletteTag = STAR_TAG_GOLD,
	.oam = &sStarOAM,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = SpriteCallbackDummy,
};

static const struct CompressedSpriteSheet sStarsSpriteSheet = {Frontier_Record_BronzeStarTiles, TILE_SIZE_4BPP, STAR_TAG_BRONZE};
static const struct CompressedSpritePalette sBronzeStarSpritePalette = {Frontier_Record_BronzeStarPal, STAR_TAG_BRONZE};
static const struct CompressedSpritePalette sSilverStarSpritePalette = {Frontier_Record_SilverStarPal, STAR_TAG_SILVER};
static const struct CompressedSpritePalette sGoldStarSpritePalette = {Frontier_Record_GoldStarPal, STAR_TAG_GOLD};

static const u16 sFrontierRecordsTextColour[] = {0x7FFF, 0x7FFF, 0x318C, 0x675A, 0x043C, 0x3AFF, 0x0664, 0x4BD2, 0x6546, 0x7B14, RGB(21, 23, 23)};

//This file's functions
static void CleanWindows(void);
static void CommitWindows(void);
static void Task_FrontierRecordsFadeOut(u8 taskId);
static void Task_FrontierRecordsWaitForKeyPress(u8 taskId);
static void Task_FrontierRecordsFadeIn(u8 taskId);
static void LoadStarGfx(void);
static void TryCreateStarSprite(s16 x, s16 y, u8 arrayIndex, u16 maxStreak);
static void DestroyStarSprites(void);
static void PrintCurrentRecords(void);
static void CreateScrollArrows(void);
static void MainCB2_FrontierRecords(void);
static void VBlankCB_FrontierRecords(void);
static void InitFrontierRecords(void);
static void LoadFrontierRecordsGfx(void);
static void ClearTasksAndGraphicalStructs(void);
static void ClearVramOamPlttRegs(void);
static void CB2_FrontierRecords(void);
static void Task_InitFrontierRecords(u8 taskId);

//General Util
static void CleanWindows(void)
{
	for (int i = 0; i < WINDOW_COUNT; ++i)
		FillWindowPixelBuffer(i, PIXEL_FILL(0));
}

static void CommitWindows(void)
{
	for (u8 i = 0; i < WINDOW_COUNT; ++i)
	{
		CopyWindowToVram(i, COPYWIN_BOTH);
		PutWindowTilemap(i);
	}
}

//GUI
static void Task_FrontierRecordsFadeOut(u8 taskId)
{
	if (!gPaletteFade->active)
	{
		SetMainCallback2(CB2_ReturnToFieldContinueScript);
		Free(sFrontierRecordsPtr->tilemapPtr);
		Free(sFrontierRecordsPtr);
		sFrontierRecordsPtr = NULL; //Shared with gNewBS, which battle code reads as "no battle struct" when NULL
		FreeAllWindowBuffers();
		DestroyTask(taskId);
	}
}

static void Task_FrontierRecordsWaitForKeyPress(u8 taskId)
{
	if (gMain.newKeys & (A_BUTTON | B_BUTTON))
	{
		PlaySE(SE_PC_OFF);
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
		gTasks[taskId].func = Task_FrontierRecordsFadeOut;
	}
	else if (gMain.newKeys & DPAD_LEFT)
	{
		if (sFrontierRecordsPtr->facilityNum == 0)
			sFrontierRecordsPtr->facilityNum = NUM_BATTLE_FACILITIES; //Wrap around

		--sFrontierRecordsPtr->facilityNum;

		DestroyStarSprites();
		PrintCurrentRecords();
		PlaySE(SE_WIN_OPEN);
	}
	else if (gMain.newKeys & DPAD_RIGHT)
	{
		if (sFrontierRecordsPtr->facilityNum == NUM_BATTLE_FACILITIES - 1)
			sFrontierRecordsPtr->facilityNum = 0; //Wrap around
		else
			++sFrontierRecordsPtr->facilityNum;

		DestroyStarSprites();
		PrintCurrentRecords();
		PlaySE(SE_WIN_OPEN);
	}
}

static void Task_FrontierRecordsFadeIn(u8 taskId)
{
	if (!gPaletteFade->active)
		gTasks[taskId].func = Task_FrontierRecordsWaitForKeyPress;
}

static void LoadStarGfx(void)
{
	LoadCompressedSpriteSheetUsingHeap(&sStarsSpriteSheet);
	LoadCompressedSpritePaletteUsingHeap(&sBronzeStarSpritePalette);
	LoadCompressedSpritePaletteUsingHeap(&sSilverStarSpritePalette);
	LoadCompressedSpritePaletteUsingHeap(&sGoldStarSpritePalette);
}

static void TryCreateStarSprite(s16 x, s16 y, u8 arrayIndex, u16 maxStreak)
{
	u8 spriteId = MAX_SPRITES;

	if (sFrontierRecordsPtr->starSpriteIds[arrayIndex] != MAX_SPRITES)
		return; //Star already exists - overwriting its id here would leak the sprite

	if (maxStreak >= GOLD_STAR_STREAK)
		spriteId = CreateSprite(&sGoldStarTemplate, x, y, 0);
	else if (maxStreak >= SILVER_STAR_STREAK)
		spriteId = CreateSprite(&sSilverStarTemplate, x, y, 0);
	else if (maxStreak >= BRONZE_STAR_STREAK)
		spriteId = CreateSprite(&sBronzeStarTemplate, x, y, 0);

	sFrontierRecordsPtr->starSpriteIds[arrayIndex] = spriteId;
}

static void DestroyStarSprites(void)
{
	u32 i;

	for (i = 0; i < NELEMS(sFrontierRecordsPtr->starSpriteIds); ++i)
	{
		if (sFrontierRecordsPtr->starSpriteIds[i] < MAX_SPRITES)
		{
			DestroySprite(&gSprites[sFrontierRecordsPtr->starSpriteIds[i]]);
			sFrontierRecordsPtr->starSpriteIds[i] = MAX_SPRITES;
		}
	}
}

static void PrintCurrentRecords(void)
{
	u32 format;

	static const struct TextColor titleColour =
	{
		.bgColor = 0, //Transparent
		.fgColor = 1, //White
		.shadowColor = 10, //Light Gray
	};

	static const struct TextColor formatColour =
	{
		.bgColor = 0, //Transparent
		.fgColor = 4, //Red
		.shadowColor = 5, //Orange
	};

	static const struct TextColor generalColour =
	{
		.bgColor = 0, //Transparent
		.fgColor = 2, //Gray
		.shadowColor = 3, //Light Gray
	};

	static const u8 sSinglesWindows[] = {WIN_SINGLES, WIN_SINGLES_CURRENT_STREAK, WIN_SINGLES_MAX_STREAK,
										 WIN_SINGLES_CURRENT_STREAK_NUM, WIN_SINGLES_MAX_STREAK_NUM};
	static const u8 sDoublesWindows[] = {WIN_DOUBLES, WIN_DOUBLES_CURRENT_STREAK, WIN_DOUBLES_MAX_STREAK,
										 WIN_DOUBLES_CURRENT_STREAK_NUM, WIN_DOUBLES_MAX_STREAK_NUM};

	CleanWindows();

	//Facility name and screen title
	WindowPrint(WIN_BATTLE_FACILITY_NAME, 1, 0, 6, &titleColour, 0, gBattleFacilityNames[sFrontierRecordsPtr->facilityNum]);
	WindowPrint(WIN_BATTLE_TYPE, 1, 0, 6, &titleColour, 0, gText_FrontierRecordsTitle);

	// One block per format: Singles on top, Doubles below.
	for (format = FRONTIER_FORMAT_SINGLES; format < NUM_FRONTIER_FORMATS; ++format)
	{
		const u8* const windows = (format == FRONTIER_FORMAT_SINGLES) ? sSinglesWindows : sDoublesWindows;
		u16 currStreak = GetFrontierStreak(sFrontierRecordsPtr->facilityNum, format, CURR_STREAK);
		u16 maxStreak = GetFrontierStreak(sFrontierRecordsPtr->facilityNum, format, MAX_STREAK);

		ConvertIntToDecimalStringN(gStringVar1, currStreak, 0, 5);
		ConvertIntToDecimalStringN(gStringVar2, maxStreak, 0, 5);

		WindowPrint(windows[0], 0, 0, 4, &formatColour, 0,
			(format == FRONTIER_FORMAT_SINGLES) ? gText_FrontierRecordSingles : gText_FrontierRecordDoubles);
		WindowPrint(windows[1], 0, 0, 4, &generalColour, 0, gText_CurrentStreak);
		WindowPrint(windows[2], 0, 0, 4, &generalColour, 0, gText_MaxStreak);
		WindowPrint(windows[3], 0, 0, 4, &generalColour, 0, gStringVar1);
		WindowPrint(windows[4], 0, 0, 4, &generalColour, 0, gStringVar2);

		TryCreateStarSprite(114, (format == FRONTIER_FORMAT_SINGLES) ? 76 : 132, format, maxStreak);
	}

	CommitWindows();
}

static void CreateScrollArrows(void)
{
	sFrontierRecordsPtr->scrollArrowDummy = 5;

	AddScrollIndicatorArrowPairParameterized(
		SCROLL_ARROW_RIGHT,
		80, //Y
		9, //Left X
		9 + 223, //Right X
		1000, //Ridiculously high number for Total Items
		110,
		110,
		&sFrontierRecordsPtr->scrollArrowDummy
	);
}

static void MainCB2_FrontierRecords(void)
{
	RunTasks();
	AnimateSprites();
	BuildOamBuffer();
	UpdatePaletteFade();
}

static void VBlankCB_FrontierRecords(void)
{
	LoadOam();
	ProcessSpriteCopyRequests();
	TransferPlttBuffer();
}

static void InitFrontierRecords(void)
{
	FillWindowPixelBuffer(0, PIXEL_FILL(0));
	LoadStarGfx();
	PrintCurrentRecords();
	CreateScrollArrows();
}

static void LoadFrontierRecordsGfx(void)
{
	decompress_and_copy_tile_data_to_vram(2, &gInterfaceGfx_FrontierRecordsTiles, 0, 0, 0);
	LZDecompressWram(gInterfaceGfx_FrontierRecordsMap, sFrontierRecordsPtr->tilemapPtr);
	LoadPalette(gInterfaceGfx_FrontierRecordsPal, 0, 0x20);
	LoadPalette(sFrontierRecordsTextColour, 0xF0, 0x20);
}

static void ClearTasksAndGraphicalStructs(void)
{
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetTempTileDataBuffers();
    ResetPaletteFade();
    FreeAllSpritePalettes();
}

static void ClearVramOamPlttRegs(void)
{
	DmaFill16(3, 0, VRAM, VRAM_SIZE);
	DmaFill32(3, 0, OAM, OAM_SIZE);
	DmaFill16(3, 0, PLTT, PLTT_SIZE);
	SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
	SetGpuReg(REG_OFFSET_BG3CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0CNT, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG3VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG2VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG1VOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0HOFS, DISPCNT_MODE_0);
	SetGpuReg(REG_OFFSET_BG0VOFS, DISPCNT_MODE_0);
}

static void CB2_FrontierRecords(void)
{
	switch (gMain.state) {
		case 0:
		default:
			SetVBlankCallback(NULL);
			ClearVramOamPlttRegs();
			gMain.state++;
			break;
		case 1:
			ClearTasksAndGraphicalStructs();
			gMain.state++;
			break;
		case 2:
			sFrontierRecordsPtr->tilemapPtr = Malloc(0x1000);
			ResetBgsAndClearDma3BusyFlags(0);
			InitBgsFromTemplates(0, sFrontierRecordsBgTemplates, NELEMS(sFrontierRecordsBgTemplates));
			SetBgTilemapBuffer(2, sFrontierRecordsPtr->tilemapPtr);
			gMain.state++;
			break;
		case 3:
			LoadFrontierRecordsGfx();
			gMain.state++;
			break;
		case 4:
			if (!free_temp_tile_data_buffers_if_possible())
			{
				ShowBg(0);
				ShowBg(1);
				ShowBg(2);
				CopyBgTilemapBufferToVram(2);
				gMain.state++;
			}
			break;
		case 5:
			InitWindows(sFrontierRecordsWinTemplates);
			DeactivateAllTextPrinters();
			gMain.state++;
			break;
		case 6:
			BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
			gMain.state++;
			break;
		case 7:
			SetVBlankCallback(VBlankCB_FrontierRecords);
			InitFrontierRecords();
			CreateTask(Task_FrontierRecordsFadeIn, 0);
			SetMainCallback2(MainCB2_FrontierRecords);
			gMain.state = 0;
			break;
	}
}

static void Task_InitFrontierRecords(u8 taskId)
{
	if (!gPaletteFade->active)
	{
		u8 facility = BATTLE_FACILITY_NUM;

		sFrontierRecordsPtr = Calloc(sizeof(struct FrontierRecords));
		// Open on the facility the player is in; left/right pages through the rest.
		sFrontierRecordsPtr->facilityNum = (facility < NUM_BATTLE_FACILITIES) ? facility : IN_BATTLE_TOWER;
		Memset(sFrontierRecordsPtr->starSpriteIds, MAX_SPRITES, sizeof(sFrontierRecordsPtr->starSpriteIds));

		PlayRainStoppingSoundEffect();
		SetMainCallback2(CB2_FrontierRecords);
		DestroyTask(taskId);
	}
}

//@Details: Opens up the Battle Frontier records screen. Shows the current and record streak
//			for both formats of the facility the player is in; left/right pages by facility.
void sp057_ShowFrontierRecords(void)
{
	FadeScreen(FADE_TO_BLACK, 0);
	CreateTask(Task_InitFrontierRecords, 0);
}
