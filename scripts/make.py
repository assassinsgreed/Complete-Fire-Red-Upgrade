#!/usr/bin/env python3

import os
import re
import shutil
import sys

############
# Options go here.
############

ROM_NAME = "BPRE0.gba"  # The name of your rom
ROM_NAME_OUT = "test.gba"  # The rom the build writes out
CART_SIZE = 0x2000000  # 32MB, the largest size a GBA cart can be
OFFSET_TO_PUT = 0x850000
DPE_OFFSETS_INI = "../Dynamic-Pokemon-Expansion/offsets.ini"  # Where the regional dex table addresses are read from
SEARCH_FREE_SPACE = False  # Set to True if you want the script to search for free space
                           # Set to False if you don't want to search for free space as you for example update the engine

#############
# Options end here.
#############

###############
# Functions start here.
###############


def MakeOffset0x100Aligned(offset: int) -> int:
    while offset % 16 != 0:
        offset += 1

    return offset


def FindOffsetToPut(rom, neededBytes: int, startOffset: int) -> int:
    offset = startOffset
    rom.seek(0, 2)
    maxPosition = rom.tell()
    numFoundBytes = 0

    while numFoundBytes < neededBytes:
        if offset + numFoundBytes >= maxPosition:
            print("End of file reached. Not enough free space.")
            return 0

        numFoundBytes += 1
        rom.seek(offset + numFoundBytes)
        if rom.read(1) != b'\xFF':
            offset = MakeOffset0x100Aligned(offset + numFoundBytes)
            numFoundBytes = 0

    return offset


def ChangeFileLine(filePath: str, lineToChange: int, replacement: str):
    with open(filePath, 'r') as file:
        copy = file.read()
        file.seek(0x0)
        lineNum = 1
        for line in file:
            if lineNum == lineToChange:
                copy = copy.replace(line, replacement)
                break
            lineNum += 1

    with open(filePath, 'w') as file:
        file.write(copy)


def EditLinker(offset: int):
    ChangeFileLine("linker.ld", 4, "\t\trom     : ORIGIN = (0x08000000 + " + hex(offset) + "), LENGTH = 32M\n")


def EditInsert(offset: int):
    ChangeFileLine("./scripts/insert.py", 10, "OFFSET_TO_PUT = " + hex(offset) + '\n')
    ChangeFileLine("./scripts/insert.py", 11, 'SOURCE_ROM = "' + ROM_NAME + '"\n')


# BPRE.ld symbol -> the DPE symbol naming the u16 count each species list starts with
REGIONAL_DEX_TABLES = {
    "gRegionalDexTableStandard": "gRegionalDexCount",
    "gRegionalDexTableDivergent": "gDivergentRegionalDexCount",
}
MAX_REGIONAL_DEX_ENTRIES = 1000  # The dex flag arrays in SaveBlock1 are sized for 999 species


def ReadDPEOffsets(wantedSymbols: set):
    """Return {symbol: address} for the wanted symbols, or None if DPE's offsets.ini isn't there."""
    offsets = {}

    try:
        with open(DPE_OFFSETS_INI, 'r') as file:
            for line in file:
                symbol, separator, address = line.partition(':')
                if separator and symbol.strip() in wantedSymbols:
                    offsets[symbol.strip()] = int(address.strip(), 16)
    except (FileNotFoundError, ValueError):
        return None

    return offsets


def ReadLinkerSymbol(symbol: str):
    with open("BPRE.ld", 'r') as file:
        match = re.search(r'^' + symbol + r'\s*=\s*(0x[0-9A-Fa-f]+)\s*;', file.read(), re.MULTILINE)

    return int(match.group(1), 16) if match is not None else None


def WriteLinkerSymbol(symbol: str, address: int):
    with open("BPRE.ld", 'r') as file:
        contents = file.read()

    updated = re.sub(r'^' + symbol + r'\s*=\s*0x[0-9A-Fa-f]+\s*;',
                     symbol + ' = 0x' + format(address, 'X') + ';', contents, count=1, flags=re.MULTILINE)

    if updated != contents:
        with open("BPRE.ld", 'w') as file:
            file.write(updated)


def IsRegionalDexTable(rom: bytes, address: int) -> bool:
    """A valid table is a u16 count followed by that many distinct, non-zero species."""
    offset = address - 0x08000000
    if offset < 0 or offset + 2 > len(rom):
        return False

    count = int.from_bytes(rom[offset:offset + 2], byteorder='little')
    if count == 0 or count > MAX_REGIONAL_DEX_ENTRIES or offset + 2 + count * 2 > len(rom):
        return False

    species = [int.from_bytes(rom[i:i + 2], byteorder='little')
               for i in range(offset + 2, offset + 2 + count * 2, 2)]

    return 0 not in species and len(set(species)) == count


def SyncRegionalDexTables():
    """Point BPRE.ld at the regional dex species lists and prove they are still where it says.

    The lists are base ROM data, so they move whenever it is rebuilt. Nothing reading them faults on
    a stale address, it just walks garbage and reports every dex as incomplete, so a bad address has
    to stop the build rather than ship."""
    with open(ROM_NAME, 'rb') as rom:
        romData = rom.read()

    dpeOffsets = ReadDPEOffsets(set(REGIONAL_DEX_TABLES.values()))
    if dpeOffsets is None:
        print('Warning: could not read "' + DPE_OFFSETS_INI + '".')
        print('Verifying the addresses already in BPRE.ld instead of updating them.')

    for linkerSymbol, dpeSymbol in sorted(REGIONAL_DEX_TABLES.items()):
        address = ReadLinkerSymbol(linkerSymbol) if dpeOffsets is None else dpeOffsets.get(dpeSymbol)

        if address is None:
            missing = linkerSymbol + ' in BPRE.ld' if dpeOffsets is None \
                else dpeSymbol + ' in "' + DPE_OFFSETS_INI + '"'
            print('Error: could not find ' + missing + '.')
            sys.exit(1)

        if not IsRegionalDexTable(romData, address):
            print('Error: ' + hex(address) + ' does not hold ' + linkerSymbol
                  + ' in "' + ROM_NAME + '".')
            print('The regional dex tables have moved. Rebuild DPE so that')
            print('"' + DPE_OFFSETS_INI + '" lists their new addresses,')
            print('or correct ' + linkerSymbol + ' in BPRE.ld by hand.')
            sys.exit(1)

        WriteLinkerSymbol(linkerSymbol, address)


def BuildCode():
    if shutil.which('python3') is not None:
        result = os.system("python3 scripts/build.py")
    else:
        result = os.system("python scripts/build.py")

    if result != 0:  # Build wasn't sucessful
        sys.exit(1)


def InsertCode():
    if shutil.which('python3') is not None:
        os.system("python3 scripts/insert.py")
    else:
        os.system("python scripts/insert.py")


def ApplyCustomHacks():
    with open(ROM_NAME_OUT, 'rb+') as romfile:
        originalPokedexEvalAddress = b'\xE0\x73\x1A\x08'
        updatedPokedexEvalAddress = b''
        
        with open("offsets.ini", 'r') as generatedOffsets:
            for line in generatedOffsets:
                if line.startswith("PokedexEvaluation_Introduction"):
                    address = line[-9:-1]
                    updatedPokedexEvalAddress = int(address, 16).to_bytes(4, byteorder='little')
                    break
        
        romData = romfile.read()
        romData = romData.replace(originalPokedexEvalAddress, updatedPokedexEvalAddress)
        romfile.seek(0)
        romfile.write(romData)


def InjectWildEncounters():
    print("Injecting wild encounter data...")
    if shutil.which('python3') is not None:
        result = os.system("python3 scripts/inject_wild_encounters.py")
    else:
        result = os.system("python scripts/inject_wild_encounters.py")

    if result != 0:  # Build wasn't sucessful
        sys.exit(1)

    print("Done!")


def PadRomToCartSize():
    # Pad the game to 32MB to ensure cart flashers can handle the game data properly
    with open(ROM_NAME_OUT, 'rb+') as rom:
        rom.seek(0, 2)
        size = rom.tell()

        if size > CART_SIZE:
            print("Error: " + ROM_NAME_OUT + " is " + hex(size)
                  + " bytes, past the " + hex(CART_SIZE) + " a GBA cart can address.")
            sys.exit(1)

        if size < CART_SIZE:
            rom.write(b'\xFF' * (CART_SIZE - size))
            print("Padded " + ROM_NAME_OUT + " from " + hex(size) + " to " + hex(CART_SIZE) + " bytes.")


def ClearFromTo(rom, from_: int, to_: int):
    rom.seek(from_)
    for i in range(0, to_ - from_):
        rom.write(b'\xFF')

##############
# Functions end here.
##############


def main():
    try:
        with open(ROM_NAME, 'rb+') as rom:
            offset = OFFSET_TO_PUT
            if SEARCH_FREE_SPACE is True:
                offset = FindOffsetToPut(rom, 0x50000, MakeOffset0x100Aligned(offset))

            EditLinker(offset)
            EditInsert(offset)
            SyncRegionalDexTables()
            BuildCode()
            InsertCode()
            ApplyCustomHacks()
            InjectWildEncounters()
            PadRomToCartSize()  # Must stay last; everything above assumes the base ROM's length
            rom.close()

    except FileNotFoundError:
        print('Error: Could not find source rom: "' + ROM_NAME + '".\n'
              + 'Please make sure a rom with this name exists in the root.')


if __name__ == '__main__':
    main()
    