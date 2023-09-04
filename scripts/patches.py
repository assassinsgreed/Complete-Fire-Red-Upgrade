import glob
from subprocess import call

ERROR_COLOR = "\033[1;31m"
ROM_NAME = 'BPRE0.gba'

def main():
    """ Load all .ips patches from patches subdirectory and apply them """
    for file in glob.glob(".\\automation\\patches\\*.ips"):
        result = call(["python", ".\\automation\\ips.py", file, ROM_NAME])
        if (result != 0):
            print(ERROR_COLOR + "Error applying patch: {}. See output for details. Exiting with status code: 1".format(file))
            exit(1)

        # If the patch is the BW Music patch, we need to apply additional logic
        # if "B2W2 Music Patch" in file: ApplyBWMusicPatch()
    
    ## What I was trying to do:
    ## Take the 1.5.1 music patch and apply it to a clean rom
    ## Using Sappy (xml file updated with the one from the patch's zip archive), find the songs and their voice tables
    ## Copy those to the music instruments .bit file, using the following reference: https://github.com/LukeZGD/B2W2-Music-Patch/blob/master/txt%20info/bw%20voicegroup%20instruments.txt
    ## Take copies of the music MIDIs from the repo: https://github.com/LukeZGD/B2W2-Music-Patch/tree/master
    ## Configure the flags file acccording to Greenphx's guide
    ## Try.  
    
    ## Some worked well (Virbank City), some were close (battle theme), and some were not close (Unwavering Emotions)


    # Music Instruments
    ApplyBWMusicPatch() # TODO: Missing most instruments, it seems?

    # Fix bug in scrolling multichoice windows
    with open(ROM_NAME, 'rb+') as romfile:
        romfile.seek(0xCBB84)
        romfile.write(b'\x00\x00\x00\x00')
        romfile.close()

def ApplyBWMusicPatch():
    # Open BW/B2W2 Music Patch hex
    with open(".\\automation\\B2W2 Instruments.bit", 'rb') as musicpatch:
        bytes = bytearray(musicpatch.read())
        musicpatch.close()

    with open(ROM_NAME, 'rb+') as romfile:
        romfile.seek(0x1200000)
        romfile.write(bytes)

        # Update bytes recommended by CFRU docs
        # romfile.seek(0x4A32A0)
        # romfile.write(b'\xA0\xFA\x03\x02')

        # Set obtained Item fanfare duration to 0s, to avoid awkward silence when learning a new move. This is to bypass a problem with the music patch
        romfile.seek(0x3AC992)
        romfile.write(b'\x00\x00')
        
        romfile.close()

if __name__ == '__main__':
    main()
