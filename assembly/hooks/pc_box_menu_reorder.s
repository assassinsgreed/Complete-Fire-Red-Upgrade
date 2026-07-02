.text
.align 2
.thumb
.thumb_func

.include "../asm_defines.s"

@@ Reorder PC Box main menu: Move Pokemon > Move Items > Withdraw > Deposit > See Ya!

.global pcBoxMenu_ReorderedTexts
.global pcBoxMenu_RemapInput
.global pcBoxMenu_ReturnCursorRemap


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Remap Menu Position -> Box Option
@	hook at 8c45c via r0
@
@ Task_PCMainMenu uses the raw row index as the box option
@ (0 = withdraw party check, 1 = deposit last-mon check,
@ 4 = exit, and the arg to EnterPokeStorage). With the rows
@ reordered, position^2 converts back to the box option
@ (0<->2, 1<->3). Skipped for the direct PC selection hack,
@ which forces position 0 and expects withdraw.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
pcBoxMenu_RemapInput:
	bl ProcessMenuInput
	lsl r0, r0, #0x18
	asr r0, r0, #0x18
	cmp r0, #0x0
	blt ReturnInput		@ -1/-2: no selection made
	cmp r0, #0x3
	bgt ReturnInput		@ 4: See Ya!
	ldr r1, =pcSelect_StateTracker
	ldrb r1, [r1]
	cmp r1, #0x0
	bne ReturnInput		@ in direct selection hack - forced position 0 must stay withdraw
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
@ so it needs the same option -> position conversion.
@ r0 (task id) and r1 (&task) must survive until sub_81E3BB8.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.align 2
.pool
pcBoxMenu_ReturnCursorRemap:
	ldr r2, =(0x020397A8)
	ldrb r2, [r2]
	cmp r2, #0x3
	bhi StoreCursorPos
	mov r3, #0x2
	eor r2, r3		@ box option -> menu position
StoreCursorPos:
	strh r2, [r1, #0xA]
	bl CallSub81E3BB8
	ldr r2, =(0x0808c70a +1)
	bx r2

CallSub81E3BB8:
	ldr r2, =(0x081e3bb8 +1)
	bx r2


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Reordered PC Box Main Menu Texts
@	replaces table at 0x83CDA20 - {name, description} pairs
@	pointers 8c444, 8c508, 8c5d4, 8c620, 8c67c, 8c7b0
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.align 2
.pool
pcBoxMenu_ReorderedTexts:
.word 0x0841858D, 0x08418611	@Move Pokemon
.word 0x0841859A, 0x08418642	@Move Items
.word 0x0841856C, 0x084185AD	@Withdraw Pokemon
.word 0x0841857D, 0x084185E2	@Deposit Pokemon
.word 0x084185A5, 0x08418681	@See Ya!
