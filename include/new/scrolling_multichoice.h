#pragma once

#include "../global.h"

/**
 * \file scrolling_multichoice.h
 * \brief Contains functions and data structures relating to custom scrollable list menus.
 */

//Exported Functions
extern u32 GetSizeOfMultiList(void);
extern u32 GetScrollingMultiAllocSize(u32 count);
extern const u8* const* GetScrollingMultiList(void);
extern void SetScrollingListSize(u8 taskId);

//Exported Constants
struct ScrollingMulti
{
	const u8* const* set;
	u8 count;

	// Optional, and NULL for a list that has nothing to highlight. A list that names a setting
	// rather than an action gives the entry that setting is currently on, and that one entry is
	// drawn green; anything at or past count highlights nothing.
	u8 (*getHighlightedIndex)(void);
};

//Exported Data Structures
extern const struct ScrollingMulti gScrollingSets[];
