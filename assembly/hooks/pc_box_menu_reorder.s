.text
.align 2
.thumb
.thumb_func

.include "../asm_defines.s"

@@ Reorder PC Box main menu: Move Pokemon > Move Items > Withdraw > Deposit > Sort Boxes > See Ya!
@@ The row texts live in src/pc_box_sort.c as pcBoxMenu_ReorderedTexts.

.global pcBoxMenu_RemapInput
.global pcBoxMenu_ReturnCursorRemap
.global pcBoxMenu_CheckSortSelection


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Remap Menu Position -> Box Option
@	hook at 8c45c via r0
@
@ Task_PCMainMenu uses the raw row index as the box option
@ (0 = withdraw party check, 1 = deposit last-mon check,
@ 4 = exit, and the arg to EnterPokeStorage). With the rows
@ reordered, position^2 converts rows 0-3 back to the box
@ option (0<->2, 1<->3), and position^1 swaps the new Sort
@ row with See Ya! (4 -> 5, 5 -> 4). Sort's 5 is a sentinel
@ with no vanilla meaning: it falls through both party checks
@ untouched, and pcBoxMenu_CheckSortSelection picks it up.
@ Skipped for the direct PC selection hack, which forces
@ position 0 and expects withdraw.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
pcBoxMenu_RemapInput:
	bl ProcessMenuInput
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	cmp r0, #0x0
	blt ReturnInput		@ -1/-2: no selection made
	cmp r0, #0x5
	bgt ReturnInput		@ out of range for a 6 row menu
	ldr r1, =pcSelect_StateTracker
	ldrb r1, [r1]
	cmp r1, #0x0
	beq RemapRow @ In the direct selection hack: forced position 0 must stay withdraw, and the sort sentinel must never escape into it
	cmp r0, #0x3
	ble ReturnInput
	mov r0, #0x4
	b ReturnInput
RemapRow:
	cmp r0, #0x4
	blt RemapStorageRow
	mov r1, #0x1
	eor r0, r1		@ Sort <-> See Ya!
	b ReturnInput
RemapStorageRow:
	mov r1, #0x2
	eor r0, r1		@ menu position -> box option
ReturnInput:
	ldr r1, =(0x0808c464 +1)	@ strh r0, [r5, #0xC]
	bx r1

ProcessMenuInput:
	ldr r1, =(0x0810f998 +1)
	bx r1


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Remap Cursor Position on Return From Storage
@	hook at 8c700 via r2
@
@ The exit callback stores the used box option at 0x20397A8
@ and the re-created menu task seeds its cursor row from it,
@ so it needs the same option -> position conversion. Only
@ options 0-3 ever enter storage; anything else lands on
@ See Ya! rather than on the Sort row.
@ r0 (task id) and r1 (&task) must survive until sub_81E3BB8.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.align 2
.pool
pcBoxMenu_ReturnCursorRemap:
	ldr r2, =(0x020397A8)
	ldrb r2, [r2]
	cmp r2, #0x3
	bhi SeeYaCursorPos
	mov r3, #0x2
	eor r2, r3		@ box option -> menu position
	b StoreCursorPos
SeeYaCursorPos:
	mov r2, #0x5
StoreCursorPos:
	strh r2, [r1, #0xA]
	bl CallSub81E3BB8
	ldr r2, =(0x0808c70a +1)
	bx r2

CallSub81E3BB8:
	ldr r2, =(0x081e3bb8 +1)
	bx r2


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Divert the Sort Boxes Row Out of the Storage System
@	hook at 8c598 via r0
@
@ Replaces the 8 bytes that start the fade to black before
@ state 4 hands off to EnterPokeStorage. Option 5
@ must not fade - it stays in the overworld - so the task is
@ handed to Task_PCBoxSortMenuInit by overwriting its func
@ pointer (offset 0 of struct Task, still in r5) and dropping
@ into the task epilogue. No task is created or destroyed and
@ ScriptContext2 is left enabled, so the script waiting on
@ the PC stays parked and the menu window can be reused.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.align 2
.pool
pcBoxMenu_CheckSortSelection:
	ldrb r0, [r5, #0xC]	@ the remapped box option
	cmp r0, #0x5
	beq HandOffToSortMenu
	mov r0, #0x1
	mov r1, #0x0
	bl CallFadeScreen
	ldr r0, =(0x0808c5a0 +1)	@ movs r0, #4 - enter storage on state 4
	bx r0

HandOffToSortMenu:
	ldr r0, =(Task_PCBoxSortMenuInit)
	str r0, [r5, #0x0]
	ldr r0, =(0x0808c69c +1)	@ task epilogue
	bx r0

CallFadeScreen:
	ldr r2, =(0x0807a818 +1)
	bx r2

.align 2
.pool
