#include "defines.h"
#include "../include/bg.h"

/*
battle_tutorial.c
	replaces the tutorial "voiceover" message frame functions used by the
	first battle (Oak), the old man catch demo, and the Poke Dude.
	The vanilla functions assume the vanilla battle textbox layout: the frame
	is drawn with tiles 0x30-0x3D (empty in the custom textbox tileset) and
	removed by rebuilding the textbox from tiles 0x3-0x11 in the vanilla
	arrangement, which corrupts the custom textbox for the rest of the battle.
*/

void BtlCtrl_DrawVoiceoverMessageFrame(void);
void BtlCtrl_RemoveVoiceoverMessageFrame(void);

//Rows 14-19 of this game's battle textbox tilemap
static void DrawCustomBattleTextboxFrame(void)
{
	FillBgTilemapBufferRect(0, 0x3, 0, 14, 1, 1, 0);
	FillBgTilemapBufferRect(0, 0x4, 1, 14, 28, 1, 0);
	FillBgTilemapBufferRect(0, BG_TILE_H_FLIP(0x3), 29, 14, 1, 1, 0);
	FillBgTilemapBufferRect(0, 0x5, 0, 15, 1, 4, 0);
	FillBgTilemapBufferRect(0, 0x9, 1, 15, 28, 4, 0);
	FillBgTilemapBufferRect(0, BG_TILE_H_FLIP(0x5), 29, 15, 1, 4, 0);
	FillBgTilemapBufferRect(0, 0x7, 0, 19, 1, 1, 0);
	FillBgTilemapBufferRect(0, 0x6, 1, 19, 28, 1, 0);
	FillBgTilemapBufferRect(0, BG_TILE_H_FLIP(0x7), 29, 19, 1, 1, 0);
}

//Hooked in at 0x80EB30C
void BtlCtrl_DrawVoiceoverMessageFrame(void)
{
	DrawCustomBattleTextboxFrame();
}

//Hooked in at 0x80EB524
void BtlCtrl_RemoveVoiceoverMessageFrame(void)
{
	DrawCustomBattleTextboxFrame();
}
