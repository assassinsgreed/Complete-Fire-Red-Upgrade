#include "defines.h"
#include "../include/event_data.h"
#include "../include/string_util.h"
#include "../include/task.h"
#include "../include/text.h"

/*
text_accessibility.c - Options menu accessibility toggles for overworld message boxes.
*/

#define sMsgIsSignPost (*(u8*) 0x3000FA1)
#define Task_DrawFieldMessage ((TaskFunc) (0x8069370 | 1))

u8 __attribute__((long_call)) GetExtCtrlCodeLength(u8 code);

// Decides if the current message box is a sign post or not. Can be overridden by accessibility preferences.
bool8 IsMsgSignPost(void)
{
	if (FlagGet(FLAG_OPTIONS_PLAIN_SIGN_BOX))
		return FALSE;

	return sMsgIsSignPost == TRUE;
}

static void StripColourCodes(u8* str)
{
	u8* dest = str;

	while (*str != EOS)
	{
		u8 length;

		switch (*str)
		{
			case EXT_CTRL_CODE_BEGIN:
				length = 1 + GetExtCtrlCodeLength(str[1]);
				switch (str[1])
				{
					case EXT_CTRL_CODE_COLOR:
					case EXT_CTRL_CODE_HIGHLIGHT:
					case EXT_CTRL_CODE_SHADOW:
					case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
						str += length;
						continue;
				}
				break;
			//Their argument byte can look like a control code, so it has to be copied with them
			case CHAR_SPECIAL_F7:
			case CHAR_SPECIAL_F8:
			case CHAR_SPECIAL_F9:
			case PLACEHOLDER_BEGIN:
				length = 2;
				break;
			default:
				length = 1;
		}

		while (length-- > 0)
			*dest++ = *str++;
	}

	*dest = EOS;
}

//Every field message, whether expanded here or pre-filled in gStringVar4, starts printing through this
void CreateTask_DrawFieldMessage(void)
{
	if (FlagGet(FLAG_OPTIONS_BLACK_TEXT))
		StripColourCodes(gStringVar4);

	CreateTask(Task_DrawFieldMessage, 0x50);
}
