.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_OrichelleGarden
MapScript_OrichelleGarden:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_OrichelleGarden_SetTerrain
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_OrichelleGarden_SetTerrain:
    setworldmapflag 0x8AD @ Been to Orichelle Garden
    call SetGrassyTerrain
    end
