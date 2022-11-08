import glob
from subprocess import call

ERROR_COLOR = "\033[1;31m"
ROM_NAME = 'test.gba'

def main():
    """ Load all .ips patches from patches subdirectory and apply them """
    for file in glob.glob(".\\automation\\patches\\*.ips"):
        result = call(["python", ".\\automation\\ips.py", file, ROM_NAME])
        if (result != 0):
            print(ERROR_COLOR + "Error applying patch: {}. See output for details. Exiting with status code: 1".format(file))
            exit(1)

    # If the patch is the BW Music patch, we need to apply additional logic
    # if "BW-Music" in file: ApplyBWMusicPatch()
    # TODO: The bw hp bars will require the type icons to be moved!!

# def ApplyBWMusicPatch():



if __name__ == '__main__':
    main()
