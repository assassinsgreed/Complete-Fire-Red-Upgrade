.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_Tutors_Terrain
EventScript_Tutors_Terrain:
    multichoiceoption gText_GrassyTerrain 0
	multichoiceoption gText_MistyTerrain 1
	multichoiceoption gText_ElectricTerrain 2
	multichoiceoption gText_PsychicTerrain 3
	multichoice 0x0 0x0 FOUR_MULTICHOICE_OPTIONS TRUE
    compare LASTRESULT 0x5 @ Chose end
    if greaterorequal _goto cancelled
	switch LASTRESULT
	case 0, grassyterrain
	case 1, mistyterrain
	case 2, electricterrain
	case 3, psychicterrain
    special 0x171
    copyvar 0x8012 0x8013
    special 0x18D
    waitstate
    return

grassyterrain:
    setvar 0x8005 0x3C
    return

mistyterrain:
    setvar 0x8005 0x3D
    return

electricterrain:
    setvar 0x8005 0x3E
    return

psychicterrain:
    setvar 0x8005 0x3F
    return

cancelled:
    release
    end
