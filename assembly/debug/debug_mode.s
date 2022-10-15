.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"
.include "../asm_defines.s"

.global EventScript_DebugMode_Main
EventScript_DebugMode_Main:
	givepokemon SPECIES_BULBASAUR 0x32 0x0 0x0 0x0 0x0 @ lv 50
	givepokemon SPECIES_KYOGRE 0x32 0x0 0x0 0x0 0x0 @ lv 50
	givepokemon SPECIES_CORVIKNIGHT 0x32 0x0 0x0 0x0 0x0 @ lv 50
	givepokemon SPECIES_SHAYMIN 0x32 0x0 0x0 0x0 0x0 @ lv 50
	givepokemon SPECIES_BIBAREL 0x32 0x0 0x0 0x0 0x0 @ lv 50
	givepokemon SPECIES_NECROZMA 0x32 0x0 0x0 0x0 0x0 @ lv 50

	@ Mark Pokemon as seen/caught (0 - Seen, 1 - Caught)
	setvar LASTRESULT 0x0
	callasm DebugMenu_SetAllPokemonCaught

	@ Set flags
	setflag 0x828 @ Enable Pokemon Menu
	setflag 0x829 @ Enable Pokedex Menu
	setflag 0x914 @ Enable auto-run toggleable on L press. Running shoes always enabled
	setflag 0x91E @ Enable DexNav

	@ Set Flags: (0 - Badges obtained, 1 - Game clear, 2 - Pokedexes, 3 - Fly Spots, 4 - Custom)
	setvar LASTRESULT 0x0
	callasm DebugMenu_ProcessSetFlag
	setvar LASTRESULT 0x3
	callasm DebugMenu_ProcessSetFlag

	@ Give Items: (0 - useful key items, 1 - useful consumables, 2 - Pokeballs, 3 - Berries, 4 - TMs & HMs, 5 - All)
	setvar LASTRESULT 0x5
	callasm DebugMenu_ProcessGiveItem
