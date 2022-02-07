import json
import os.path
import shutil
from subprocess import call

ERROR_COLOR = "\033[1;31m"
SUCCESS_COLOR = "\033[92m"

print("-----------------------------------")
print("Pokemon Shooting Stars Build Script")
print("-----------------------------------\n")
print("Checking config.json contents...")

# Load config file and store paths for later use
configFilePath = './automation/config.json'
if not (os.path.exists(configFilePath)):
    print(ERROR_COLOR + "\nError: config.json not found! Exiting with status code: 1")
    exit(1)

configFile = open(configFilePath)
config = json.load(configFile)

if (not ("paths" in config) or not (config["paths"])) \
    or (not ("CFRUDir" in config["paths"]) or not (os.path.isdir(config["paths"]["CFRUDir"]))) \
    or (not ("DPEDir" in config["paths"]) or not (os.path.isdir(config["paths"]["DPEDir"]))) \
    or (not ("EditedGbaRom" in config["paths"]) or not (os.path.isfile(config["paths"]["EditedGbaRom"]))) \
    or (not ("VisualBoyAdvanceExe" in config["paths"]) or not (os.path.isfile(config["paths"]["VisualBoyAdvanceExe"]))):
    print(ERROR_COLOR + "config.json is poorly formatted, or missing values required for script! Exiting with status code: 2")
    exit (1)

configFile.close()
CFRU_PATH = config["paths"]["CFRUDir"]
DPE_PATH = config["paths"]["DPEDir"]
EDITED_GBA_PATH = config["paths"]["EditedGbaRom"]
VBA_PATH = config["paths"]["VisualBoyAdvanceExe"]

# Begin build process
print("Config found! Proceeding to build Test.gba...")
print("Copying edited GBA ROM to DPE directory...")
shutil.copy(EDITED_GBA_PATH, DPE_PATH + "/BPRE0.gba")

print("Applying DPE...")
result = call(["python", DPE_PATH + "/scripts/make.py"])
if (result != 0):
    print(ERROR_COLOR + "Error applying DPE. See output for details. Exiting with status code: 3")
    exit(3)

print("Copying built GBA ROM to CFRU directory...")
shutil.copy(DPE_PATH + "/test.gba", CFRU_PATH + "./BPRE0.gba")

print("Appyling CFRU...")
# TODO: Add clean.py script as an optional command?
result = call(["python", CFRU_PATH + "/scripts/make.py"])
if (result != 0):
    print(ERROR_COLOR + "Error applying CFRU. See output for details. Exiting with status code: 4")
    exit(4)

print(SUCCESS_COLOR + "Success! Launching built Test.gba in VBA. Happy Testing :)")
call([VBA_PATH, CFRU_PATH + "/test.gba"])
