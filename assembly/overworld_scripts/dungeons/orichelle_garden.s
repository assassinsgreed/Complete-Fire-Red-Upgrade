.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global MapScript_OrichelleGarden
MapScript_OrichelleGarden:
    mapscript MAP_SCRIPT_ON_LOAD MapEntryScript_OrichelleGarden_SetTerrain
    mapscript MAP_SCRIPT_ON_RESUME HideLegendary
    .byte MAP_SCRIPT_TERMIN

MapEntryScript_OrichelleGarden_SetTerrain:
    setworldmapflag 0x8AD @ Been to Orichelle Garden
    end

HideLegendary:
    checkflag 0x4B
    if SET _call HideShaymin
    end

HideShaymin:
    hidesprite 3
    end

.global EventScript_OrichelleGarden_Shaymin
EventScript_OrichelleGarden_Shaymin:
    faceplayer
    cry SPECIES_SHAYMIN 0x0
    waitcry
    msgbox gtext_OrichelleGarden_ShayminBattleStart MSG_NORMAL
    setflag 0x90B @ Wild custom moves, cleared at the end of battle
    setvar 0x8000 MOVE_DAZZLINGGLEAM
    setvar 0x8001 MOVE_SYNTHESIS
    setvar 0x8002 MOVE_SEEDBOMB
    setvar 0x8003 MOVE_EARTHPOWER
    setflag 0x90C @ Smarter wild battle, cleared at the end of battle
    setwildbattle SPECIES_SHAYMIN 50 ITEM_NONE
    setflag 0x807
    special 0x138 @ Setup a legendary encounter (blurred screen transition)
    waitstate
    clearflag 0x807
    special2 LASTRESULT 0xB4 @ Check the result of the battle
    compare LASTRESULT 0x1 @ Defeated in battle
    if equal _call DefeatedShaymin
    compare LASTRESULT 0x4 @ Fled from battle
    if equal _call FledFromShaymin
    compare LASTRESULT 0x7 @ Caught
    if equal _call CaughtShaymin
    end

DefeatedShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminDefeated MSG_NORMAL
    end

FledFromShaymin:
    setflag 0x4B @ Shaymin hidden
    msgbox gtext_OrichelleGarden_ShayminFledFromBattle MSG_NORMAL
    end

CaughtShaymin:
    setflag 0x4B @ Shaymin hidden
    end
