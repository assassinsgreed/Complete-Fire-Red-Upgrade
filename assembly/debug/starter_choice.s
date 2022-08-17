.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_StarterChoice_Main
EventScript_StarterChoice_Main:
	buffernumber 0x0 0x4011
	msgbox gText_StarterChoice_Npctextg MSG_FACE
	buffernumber 0x0 0x4012
	msgbox gText_StarterChoice_Npctextf MSG_FACE
	buffernumber 0x0 0x4013
	msgbox gText_StarterChoice_Npctextw MSG_FACE
	end

