#ifndef GUARD_CONSTANTS_GAME_STAT_H
#define GUARD_CONSTANTS_GAME_STAT_H

//Flags start at 0x202672C

#define GAME_STAT_SAVED_GAME                 0
#define GAME_STAT_FIRST_HOF_PLAY_TIME        1
#define GAME_STAT_POKECHIPS_FOUND            2 //Repurposed for Pokemon Amethyst
#define GAME_STAT_TUTOR_MOVES_TAUGHT         3 //Repurposed for Pokemon Amethyst
#define GAME_STAT_CHANGED_IV_NATURE          4
#define GAME_STAT_STEPS                      5
#define GAME_STAT_PICKUP_ITEMS               6 //NEW
#define GAME_STAT_TOTAL_BATTLES              7
#define GAME_STAT_WILD_BATTLES               8
#define GAME_STAT_TRAINER_BATTLES            9
#define GAME_STAT_ENTERED_HOF               10
#define GAME_STAT_POKEMON_CAPTURES          11
#define GAME_STAT_FISHING_CAPTURES          12
#define GAME_STAT_HATCHED_EGGS              13
#define GAME_STAT_EVOLVED_POKEMON           14
#define GAME_STAT_USED_POKECENTER_OR_NURSE  15
#define GAME_STAT_RESTED_AT_HOME            16
#define GAME_STAT_ENTERED_SAFARI_ZONE       17 //Not used by Pokemon Amethyst
#define GAME_STAT_USED_CUT                  18
#define GAME_STAT_USED_ROCK_SMASH           19
#define GAME_STAT_FOUND_HIDDEN_ITEM         20 //NEW!
#define GAME_STAT_POKEMON_TRADES            21 //0x2026780
#define GAME_STAT_POKECHIP_ITEMS_CREATED    22 //Repurposed for Pokemon Amethyst
#define GAME_STAT_CRITICAL_CAPTURES         23 //Repurposed for Pokemon Amethyst
#define GAME_STAT_MEALS_EATEN               24 //Repurposed for Pokemon Amethyst
#define GAME_STAT_TRAINER_HOUSES_CLEARED    25 //Repurposed for Pokemon Amethyst
#define GAME_STAT_USED_SPLASH               26
#define GAME_STAT_USED_STRUGGLE             27
#define GAME_STAT_SLOT_JACKPOTS             28
#define GAME_STAT_APRICORN_BALLS_MADE       29 //Repurposed for Pokemon Amethyst
#define GAME_STAT_WON_FRONTIER_BATTLE       30 //NEW! (Not integrated yet!)
#define GAME_STAT_POKE_BALLS_SWAPPED        31 //Repurposed for Pokemon Amethyst
#define GAME_STAT_BATTLE_FACILITY_BEST_STREAK  32
#define GAME_STAT_CAUGHT_TODAY              33 //NEW!
#define GAME_STAT_EXP_EARNED_TODAY          34 //NEW!
#define GAME_STAT_TIMES_SURF_WAS_USED       35 //Repurposed for Pokemon Amethyst
#define GAME_STAT_REVIVED_FOSSIL            36 //NEW! (Not used by Pokemon Amethyst)
#define GAME_STAT_HEADBUTT_WILD_ENCOUNTERS  37 //NEW! (Not used by Pokemon Amethyst)
#define GAME_STAT_SHOPPED                   38
#define GAME_STAT_USED_ITEMFINDER           39
#define GAME_STAT_GOT_RAINED_ON             40
#define GAME_STAT_CHECKED_POKEDEX           41
#define GAME_STAT_RECEIVED_RIBBONS          42 //Not used by Pokemon Amethyst
#define GAME_STAT_JUMPED_DOWN_LEDGES        43
#define GAME_STAT_WATCHED_TV                44 //Not used by Pokemon Amethyst
#define GAME_STAT_DEXNAV_SCANNED            45 //NEW!
#define GAME_STAT_WON_LUCKY_DRAW            46
#define GAME_STAT_POKEMON_PUT_IN_DAYCARE    47 // TODO: Not sure this is implemented
#define GAME_STAT_RAID_BATTLES              48 //NEW! (Not used by Pokemon Amethyst)
#define GAME_STAT_ENTERED_HOT_SPRINGS       49
#define GAME_STAT_RARE_CANDIES_USED         50 //Repurposed for Pokemon Amethyst
#define GAME_STAT_BERRY_CRUSH_POINTS        51 //Not used by Pokemon Amethyst

#define NUM_USED_GAME_STATS                 52
#define NUM_GAME_STATS                      64

#endif // GUARD_CONSTANTS_GAME_STAT_H
