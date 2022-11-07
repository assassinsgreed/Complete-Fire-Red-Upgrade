from io import BufferedRandom
import json

# Configuration - Change these if you need!
ROM_NAME = 'test.gba'                                    # The name of the built rom to modify
ENCOUNTERS_FILE = '.\\automation\\WildEncounters.json'   # File containing the encounters and species to parse
ENCOUNTERS_TABLE_OFFSET = 0x7296E4                       # Location of the Kanto encounter table (0x7296E4 in vanilla FR rom)
REMOVE_ENCOUNTERS_WITHOUT_REPLACEMENT = True             # Whether encounters found without replacements in WildEncounters.json should be removed 

ENCOUNTER_SLOTS = {
    'grass': 12,
    'surfing': 5,
    'rocks': 5,
    'fishing': 10
}

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
            print('End of file reached. Not enough free space.')
            return 0

        numFoundBytes += 1
        rom.seek(offset + numFoundBytes)
        if rom.read(1) != b'\xFF':
            offset = MakeOffset0x100Aligned(offset + numFoundBytes)
            numFoundBytes = 0

    return offset


def GetNextBytesAsOffset(rom: BufferedRandom, numBytes: int = 4):
    """ Takes the specified number of bytes (default 4) and converts them to a decimal equivalent of the offset they represent """
    offset = bytearray(rom.read(numBytes))[::-1] # Read bytes in reversed order
    offsetDecimal = int(offset.hex()[2:], 16) # convert bytearray like b'\x08<\x8e\x90' to address like 0x3C8E90, in decimal (3968656)
    return offsetDecimal


def GetReversedByteArrayFromPokemonHexCode(hex: str):
    """ Converts a hex code to a reversed byte array, 0-padding if needed (eg. 0x1C4 becomes 0x01C4, returned as b'\x01\xc4) """
    formattedhex = '0x%04X'[2::] % int(hex, 16)
    bytes = bytearray.fromhex(formattedhex)
    bytes.reverse()
    return bytes


def RemoveEncounterTable(rom: BufferedRandom, offset: int, encounterType: str):
    """ Replaces the encounter table at the specified offset with empty data, to be reused elsewhere """
    rom.seek(offset + 4) # Pass over the encounter rate to get the encounters pointer
    encountertableoffset = GetNextBytesAsOffset(rom)
    rom.seek(offset) # Jump back to start of encounter data
    rom.write(b'\xff'*8) # Remove encounter rate and encounters pointer
    rom.seek(encountertableoffset)
    rom.write(b'\xff' * ENCOUNTER_SLOTS[encounterType] * 4) # Remove encounter data, based on encounter type


def InsertEncounterTable(rom: BufferedRandom, offset: int, encounterrate: int, encounterType: str):
    """ Inserts an empty encounter table wherever there is free space and return the offset, to be populated by ModifyEncounterTable(). Returns the pointer to the encounters"""
    encounterOffset = FindOffsetToPut(rom, 8, 0)
    tableOffset = FindOffsetToPut(rom, ENCOUNTER_SLOTS[encounterType]*4, encounterOffset + 8) # Find free space large enough to handle this encounter type, starting after the encounter data (rate & pointer)

    # Write encounter rate
    rom.seek(encounterOffset)
    rom.write(int.to_bytes(encounterrate, 1, 'little'))
    rom.write(b'\x00'*3)

    # Write pointer to encounters table
    pointer = bytearray.fromhex('08' + '0x%06X'[2::] % tableOffset) # Format hex code as 08123456 and convert to byte array
    pointer.reverse()
    rom.write(pointer)

    # Write pointer to encounter table
    pointer = bytearray.fromhex('08' + '0x%06X'[2::] % encounterOffset) # Format hex code as 08123456 and convert to byte array
    pointer.reverse()
    rom.seek(offset)
    rom.write(pointer)
    
    return tableOffset


def ModifyExistingEncounterRate(rom: BufferedRandom, offset: int, encounterRate: int):
    """ Modifies an existing encounter in the encounter table. Returns the pointer to the encounters """
    rom.seek(offset)
    rom.write(int.to_bytes(encounterRate, 1, 'little')) # Write encounter rate (stored as decimal) in hex
    rom.write(b'\x00'*3)
    return GetNextBytesAsOffset(rom)


def ModifyEncounterTable(rom: BufferedRandom, offset: int, encounterType: str, encounters: any, species: any):
    """ Populate the encounters at the passed in offset with data from the wild encounters json file """
    rom.seek(offset)
    for i in range(0, ENCOUNTER_SLOTS[encounterType]):
        encounter = encounters['pokemon'][i]
        rom.write(int.to_bytes(encounter['low'], 1, 'little'))
        rom.write(int.to_bytes(encounter['high'], 1, 'little'))
        rom.write(GetReversedByteArrayFromPokemonHexCode(species[encounter['species']]))


def ProcessEncounter(rom: BufferedRandom, offset: int, encountertype: str, foundencounter: any, species: any, skip: int):
    """ Processes an encounter: inserts if new, replaces if existing, and (optionally, from config) clears existing data if there is no replacement """
    if foundencounter is not None and encountertype in foundencounter:
        rate = foundencounter[encountertype]['rate']

        if offset == 0:
            offset = InsertEncounterTable(rom, ENCOUNTERS_TABLE_OFFSET + skip, rate, encountertype)
        else:
            offset = ModifyExistingEncounterRate(rom, offset, rate)
        ModifyEncounterTable(rom, offset, encountertype, foundencounter[encountertype], species)
    elif offset > 0 and REMOVE_ENCOUNTERS_WITHOUT_REPLACEMENT:
        RemoveEncounterTable(rom, offset, encountertype)
        # Null out pointer to encounter data
        rom.seek(ENCOUNTERS_TABLE_OFFSET + skip)
        rom.write(b'\x00'*4)


# Encounter table is in format: <map group> <map number> <unused> <grass pointer> <surf pointer> <tree pointer> <fish pointer>
def main():
    try:
        with open(ENCOUNTERS_FILE, 'r') as f:
            encounterdata = json.loads(f.read())

    except FileNotFoundError:
        print('Error: Could not find encounters file: "' + ENCOUNTERS_FILE + '"')

    try:
        with open(ROM_NAME, 'rb+') as rom:
            skip = 0
            rom.seek(ENCOUNTERS_TABLE_OFFSET)
            mapgroup = rom.read(1)

            # Process encounter data, while the data fetched matches the format we expect. If first two bytes are FF, we are at the end of the table
            while mapgroup != b'\xFF':
                mapnum = rom.read(1)
                rom.seek(2, 1) # Skip 2 unused bytes

                # Load the offsets for each encounter in the game
                grassencountersoffset = GetNextBytesAsOffset(rom)
                surfingencountersoffset = GetNextBytesAsOffset(rom)
                rocksencountersoffset = GetNextBytesAsOffset(rom)
                fishingencountersoffset = GetNextBytesAsOffset(rom)

                # Get encounter information based on set map group and number and pass forward, or None if not found
                foundencounter = next((x for x in encounterdata['encounters'] if x['mapgroup'] == ord(mapgroup) and x['mapnum'] == ord(mapnum)), None)

                ProcessEncounter(rom, grassencountersoffset, 'grass', foundencounter, encounterdata['species'], skip + 4)   # Skip first 4 bytes for map group and num
                ProcessEncounter(rom, surfingencountersoffset, 'surfing', foundencounter, encounterdata['species'], skip + 8) # Skip grass encounter too
                ProcessEncounter(rom, rocksencountersoffset, 'rocks', foundencounter, encounterdata['species'], skip + 12) # Skip surfing encounter too
                ProcessEncounter(rom, fishingencountersoffset, 'fishing', foundencounter, encounterdata['species'], skip + 16) # Skip rocks encounter too

                skip += 20 # Each encounter record is 0x16 (20) bytes
                rom.seek(ENCOUNTERS_TABLE_OFFSET + skip)
                mapgroup = rom.read(1)

            rom.close()

    except FileNotFoundError:
        print('Error: Could not find source rom: "' + ROM_NAME + '".\n'
              + 'Please make sure a rom with this name exists in the root.')


if __name__ == '__main__':
    main()
