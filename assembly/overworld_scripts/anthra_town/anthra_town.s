.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_AnthraTown_FlowerGirl
EventScript_AnthraTown_FlowerGirl:
    msgbox gText_AnthraTown_FlowerGirl MSG_FACE
    end

.global EventScript_AnthraTown_OldMan
EventScript_AnthraTown_OldMan:
    msgbox gText_AnthraTown_OldMan MSG_FACE
    end

.global EventScript_AnthraTown_MomMain
EventScript_AnthraTown_MomMain:
	lock
	faceplayer
	checkflag 0x258
	if TRUE _goto EventScript_AnthraTown_MomRestPrompt
	msgbox gText_AnthraTown_MomLeaveHome MSG_KEEPOPEN
	closeonkeypress
	applymovement 0x1 m_LookLeft
	waitmovement 0x0
	release
	end

EventScript_AnthraTown_MomRestPrompt:
	msgbox gText_AnthraTown_MomRestPrompt MSG_KEEPOPEN
	closeonkeypress
	call EventScript_AnthraTown_MomRestAnimation
	msgbox gText_AnthraTown_MomPokemonAreHealthy MSG_KEEPOPEN
	release
	end

EventScript_AnthraTown_MomRestAnimation:
	fadescreen 0x1
	fanfare 0x100
	waitfanfare
	special 0x0
	fadescreen 0x0
	return
