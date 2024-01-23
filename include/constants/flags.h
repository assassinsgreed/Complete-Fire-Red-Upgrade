#pragma once

#define FLAG_TEMP_1 0x001
#define FLAG_TEMP_2 0x002
#define FLAG_TEMP_3 0x003
#define FLAG_TEMP_4 0x004
#define FLAG_TEMP_5 0x005
#define FLAG_TEMP_6 0x006
#define FLAG_TEMP_7 0x007
#define FLAG_TEMP_8 0x008
#define FLAG_TEMP_9 0x009
#define FLAG_TEMP_A 0x00A
#define FLAG_TEMP_B 0x00B
#define FLAG_TEMP_C 0x00C
#define FLAG_TEMP_D 0x00D
#define FLAG_TEMP_E 0x00E
#define FLAG_TEMP_F 0x00F
#define FLAG_TEMP_10 0x010
#define FLAG_TEMP_11 0x011
#define FLAG_TEMP_12 0x012
#define FLAG_TEMP_13 0x013
#define FLAG_TEMP_14 0x014
#define FLAG_TEMP_15 0x015
#define FLAG_TEMP_16 0x016
#define FLAG_TEMP_17 0x017
#define FLAG_TEMP_18 0x018
#define FLAG_TEMP_19 0x019
#define FLAG_TEMP_1A 0x01A
#define FLAG_TEMP_1B 0x01B
#define FLAG_TEMP_1C 0x01C
#define FLAG_TEMP_1D 0x01D
#define FLAG_TEMP_1E 0x01E
#define FLAG_TEMP_1F 0x01F

#define FLAG_0x020 0x020
#define FLAG_0x021 0x021
#define FLAG_0x022 0x022
#define FLAG_0x023 0x023
#define FLAG_0x024 0x024
#define FLAG_0x025 0x025
#define FLAG_0x026 0x026
#define FLAG_0x027 0x027

// Hide/show flags
/*
#define FLAG_HIDE_GRASS_STARTER_BALL                       0x028
#define FLAG_HIDE_WATER_STARTER_BALL                       0x029
#define FLAG_HIDE_FIRE_STARTER_BALL                        0x02A
#define FLAG_HIDE_PEOPLE_IN_ROUTE_17_AND_ANTHRA            0x02B
#define FLAG_HIDE_RIVAL_IN_PLAYERS_HOUSE                   0x02C
#define FLAG_HIDE_RIVAL_ON_ROUTE_17                        0x02D
#define FLAG_HIDE_RIVAL_IN_THEIR_HOUSE                     0x02E
#define FLAG_HIDE_RIVAL_IN_ANTHRA                          0x02F
#define FLAG_HIDE_REPORTERS_IN_ANTHRA                      0x030
#define FLAG_HIDE_RIVAL_AND_THUGS_ON_ROUTE_3               0x031
#define FLAG_HIDE_AIDE_ON_ROUTE_3                          0x032
#define FLAG_HIDE_PLUTO_GRUNTS_ON_ROUTE_3_AND_RUBARR       0x033
#define FLAG_HIDE_RIVAL_AND_IRENE_IN_RUBARR                0x034
#define FLAG_HIDE_ROUTE_4_BOULDERS_AND_NPCS                0x035
#define FLAG_HIDE_ROUTE_4_FOREMAN                          0x036
#define FLAG_TRAINER_HOUSE_OPPONENT_ON_BY_DEFAULT          0x037
#define FLAG_HIDE_ROUTE_5_BIKERS                           0x038
#define FLAG_HIDE_STELLA_AND_ALISTAIR_IN_FERROX_LIBRARY    0x039
#define FLAG_HIDE_POKEDEX_SPRITE_IN_HAWTHORNES_LAB         0x03A
#define FLAG_HIDE_STELLA_IN_FERROX_GYM                     0x03B
#define FLAG_HIDE_RIVAL_IN_DAIMYN_GUARDHOUSES_ON_BY_DEFAULT 0x03C
#define FLAG_HIDE_CASEY_IN_CUTSCENES_ON_BY_DEFAULT         0x03D
#define FLAG_HIDE_HELEO_RANCH_AMPHAROS                     0x03E
#define FLAG_HIDE_CASEY_IN_LAPLAZ_GYM_ON_BY_DEFAULT        0x03F
#define FLAG_HIDE_PIKACHU_GIFT_IN_DAIMYN_CTIY              0x040
#define FLAG_HIDE_ROUTE_11_PLUTO                           0x041
#define FLAG_HIDE_ROUTE_11_ALISTAIR_AND_RIVAL_AND_RT9_BLOCKER 0x042
#define FLAG_HIDE_LAKE_LAPLAZ_GALARIAN_BIRDS               0x043
#define FLAG_HIDE_ROUTE_12_REST_HOUSE_SELENE_AND_ALISTAIR  0x044
#define FLAG_HIDE_SCALDING_SPA_PLUTO_GRUNT                 0x045
#define FLAG_HIDE_GLASTRIER_WHEN_CAUGHT                    0x046
#define FLAG_HIDE_ABBY_IN_BRUCCIE_VILLAGE                  0x047
#define FLAG_HIDE_SEAFOAM_B3F_BOULDER_3                    0x048
#define FLAG_HIDE_SEAFOAM_B3F_BOULDER_4                    0x049
#define FLAG_HIDE_SEAFOAM_B3F_BOULDER_5                    0x04A
#define FLAG_HIDE_SEAFOAM_B3F_BOULDER_6                    0x04B
#define FLAG_HIDE_SEAFOAM_B4F_BOULDER_1                    0x04C
#define FLAG_HIDE_SEAFOAM_B4F_BOULDER_2                    0x04D
#define FLAG_HIDE_SILPH_RIVAL                              0x04E
#define FLAG_HIDE_ROUTE_22_RIVAL                           0x04F
#define FLAG_HIDE_PEWTER_MUSEUM_GUIDE                      0x050
#define FLAG_HIDE_TOWER_RIVAL                              0x051
#define FLAG_HIDE_MOLTRES                                  0x052
#define FLAG_HIDE_SILPH_ROCKETS                            0x053
#define FLAG_HIDE_ROUTE_12_SNORLAX                         0x054
#define FLAG_HIDE_VIRIDIAN_GIOVANNI                        0x055
#define FLAG_HIDE_OLD_AMBER                                0x056
#define FLAG_HIDE_EEVEE_BALL                               0x057
#define FLAG_HIDE_VICTORY_ROAD_2F_BOULDER                  0x058
#define FLAG_HIDE_VICTORY_ROAD_3F_BOULDER                  0x059
#define FLAG_HIDE_OAK_IN_CHAMP_ROOM                        0x05A
#define FLAG_HIDE_GAME_CORNER_ROCKET                       0x05B
#define FLAG_HIDE_CERULEAN_CAVE_GUARD                      0x05C
#define FLAG_HIDE_ZAPDOS                                   0x05D
#define FLAG_HIDE_TOWER_ROCKET_1                           0x05E
#define FLAG_HIDE_CELADON_ROCKETS                          0x05F
#define FLAG_HIDE_DOJO_HITMONLEE_BALL                      0x060
#define FLAG_HIDE_DOJO_HITMONCHAN_BALL                     0x061
#define FLAG_HIDE_CINNABAR_BILL                            0x062
#define FLAG_HIDE_UNION_ROOM_PLAYER_1                      0x063
#define FLAG_HIDE_UNION_ROOM_PLAYER_2                      0x064
#define FLAG_HIDE_UNION_ROOM_PLAYER_3                      0x065
#define FLAG_HIDE_UNION_ROOM_PLAYER_4                      0x066
#define FLAG_HIDE_UNION_ROOM_PLAYER_5                      0x067
#define FLAG_HIDE_UNION_ROOM_PLAYER_6                      0x068
#define FLAG_HIDE_UNION_ROOM_PLAYER_7                      0x069
#define FLAG_HIDE_UNION_ROOM_PLAYER_8                      0x06A
#define FLAG_HIDE_CINNABAR_SEAGALLOP                       0x06B
#define FLAG_HIDE_SAFFRON_FAN_CLUB_BLACKBELT               0x06C
#define FLAG_HIDE_SAFFRON_FAN_CLUB_ROCKER                  0x06D
#define FLAG_HIDE_SAFFRON_FAN_CLUB_WOMAN                   0x06E
#define FLAG_HIDE_SAFFRON_FAN_CLUB_BEAUTY                  0x06F
#define FLAG_HIDE_MG_DELIVERYMEN                           0x070
#define FLAG_HIDE_ONE_ISLAND_BILL                          0x071
#define FLAG_HIDE_ONE_ISLAND_POKECENTER_BILL               0x072
#define FLAG_HIDE_ONE_ISLAND_POKECENTER_CELIO              0x073
#define FLAG_HIDE_TWO_ISLAND_GAME_CORNER_BIKER             0x074
#define FLAG_HIDE_TWO_ISLAND_GAME_CORNER_LOSTELLE          0x075
#define FLAG_HIDE_LOSTELLE_IN_HER_HOME                     0x076
#define FLAG_0x077                                         0x077
#define FLAG_0x078                                         0x078
#define FLAG_HIDE_THREE_ISLAND_BIKERS                      0x079
#define FLAG_HIDE_LOSTELLE_IN_BERRY_FOREST                 0x07A
#define FLAG_HIDE_TWO_ISLAND_WOMAN                         0x07B
#define FLAG_HIDE_TWO_ISLAND_BEAUTY                        0x07C
#define FLAG_HIDE_TWO_ISLAND_SUPER_NERD                    0x07D
#define FLAG_HIDE_THREE_ISLAND_ANTIBIKERS                  0x07E
#define FLAG_0x07F                                         0x07F
#define FLAG_HIDE_ROUTE_16_SNORLAX                         0x080
#define FLAG_HIDE_MEWTWO                                   0x081
#define FLAG_HIDE_ARTICUNO                                 0x082
#define FLAG_HIDE_TOWER_ROCKET_2                           0x083
#define FLAG_HIDE_TOWER_ROCKET_3                           0x084
#define FLAG_HIDE_POWER_PLANT_ELECTRODE_1                  0x085
#define FLAG_HIDE_POWER_PLANT_ELECTRODE_2                  0x086
#define FLAG_HIDE_SS_ANNE                                  0x087
#define FLAG_HIDE_FIVE_ISLAND_ROCKETS                      0x088
#define FLAG_HIDE_MT_EMBER_EXTERIOR_ROCKETS                0x089
#define FLAG_HIDE_RUBY                                     0x08A
#define FLAG_HIDE_ICEFALL_CAVE_LORELEI                     0x08B
#define FLAG_HIDE_LORELEI_IN_HER_HOUSE                     0x08C
#define FLAG_HIDE_ICEFALL_CAVE_ROCKETS                     0x08D
#define FLAG_HIDE_RUIN_VALLEY_SCIENTIST                    0x08E
#define FLAG_HIDE_SAPPHIRE                                 0x08F
#define FLAG_HIDE_DOTTED_HOLE_SCIENTIST                    0x090
#define FLAG_HIDE_THREE_ISLAND_LONE_BIKER                  0x091
#define FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY            0x092
#define FLAG_HIDE_LOST_CAVE_SELPHY                         0x093
#define FLAG_HIDE_RESORT_GORGEOUS_SELPHY                   0x094
#define FLAG_HIDE_RESORT_GORGEOUS_INSIDE_SELPHY            0x095
#define FLAG_HIDE_SELPHYS_BUTLER                           0x096
#define FLAG_HIDE_FOUR_ISLAND_RIVAL                        0x097
#define FLAG_HIDE_SIX_ISLAND_POKECENTER_RIVAL              0x098
#define FLAG_HIDE_DEOXYS                                   0x099  Note: On by default
#define FLAG_HIDE_BIRTH_ISLAND_METEORITE                   0x09A
#define FLAG_HIDE_LUGIA                                    0x09B
#define FLAG_HIDE_HO_OH                                    0x09C
#define FLAG_HIDE_POSTGAME_GOSSIPERS                       0x09D
#define FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS              0x09E
#define FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL                0x09F
#define FLAG_HIDE_FAME_CHECKER_LT_SURGE_JOURNAL            0x0A0
#define FLAG_HIDE_VERMILION_CITY_OAKS_AIDE                 0x0A1
#define FLAG_HIDE_CINNABAR_POKECENTER_BILL                 0x0A2
#define FLAG_HIDE_CREDITS_RIVAL                            0x0A3
#define FLAG_HIDE_CREDITS_OAK                              0x0A4
#define FLAG_HIDE_LORELEI_HOUSE_MEOWTH_DOLL                0x0A5
#define FLAG_HIDE_LORELEI_HOUSE_CHANSEY_DOLL               0x0A6
#define FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_F_DOLL            0x0A7
#define FLAG_HIDE_LORELEI_HOUSE_JIGGLYPUFF_DOLL            0x0A8
#define FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_M_DOLL            0x0A9
#define FLAG_HIDE_LORELEIS_HOUSE_FEAROW_DOLL               0x0AA
#define FLAG_HIDE_LORELEIS_HOUSE_PIDGEOT_DOLL              0x0AB
#define FLAG_HIDE_LORELEIS_HOUSE_LAPRAS_DOLL               0x0AC
#define FLAG_HIDE_MISC_PLUTO_GRUNTS                        0x0AD
#define FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS 0x0AE

// Unused?
#define FLAG_0x0AF               0x0AF
#define FLAG_0x0B0               0x0B0
#define FLAG_0x0B1               0x0B1
#define FLAG_0x0B2               0x0B2
#define FLAG_0x0B3               0x0B3
#define FLAG_0x0B4               0x0B4
#define FLAG_0x0B5               0x0B5
#define FLAG_0x0B6               0x0B6
#define FLAG_0x0B7               0x0B7
#define FLAG_0x0B8               0x0B8
#define FLAG_0x0B9               0x0B9
#define FLAG_0x0BA               0x0BA
#define FLAG_0x0BB               0x0BB
#define FLAG_0x0BC               0x0BC
#define FLAG_0x0BD               0x0BD
#define FLAG_0x0BE               0x0BE
#define FLAG_0x0BF               0x0BF
#define FLAG_0x0C0               0x0C0
#define FLAG_0x0C1               0x0C1
#define FLAG_0x0C2               0x0C2
#define FLAG_0x0C3               0x0C3
#define FLAG_0x0C4               0x0C4
#define FLAG_0x0C5               0x0C5
#define FLAG_0x0C6               0x0C6
#define FLAG_0x0C7               0x0C7
#define FLAG_0x0C8               0x0C8
#define FLAG_0x0C9               0x0C9
#define FLAG_0x0CA               0x0CA
#define FLAG_0x0CB               0x0CB
#define FLAG_0x0CC               0x0CC
#define FLAG_0x0CD               0x0CD
#define FLAG_0x0CE               0x0CE
#define FLAG_0x0CF               0x0CF
#define FLAG_0x0D0               0x0D0
#define FLAG_0x0D1               0x0D1
#define FLAG_0x0D2               0x0D2
#define FLAG_0x0D3               0x0D3
#define FLAG_0x0D4               0x0D4
#define FLAG_0x0D5               0x0D5
#define FLAG_0x0D6               0x0D6
#define FLAG_0x0D7               0x0D7
#define FLAG_0x0D8               0x0D8
#define FLAG_0x0D9               0x0D9
#define FLAG_0x0DA               0x0DA
#define FLAG_0x0DB               0x0DB
#define FLAG_0x0DC               0x0DC
#define FLAG_0x0DD               0x0DD
#define FLAG_0x0DE               0x0DE
#define FLAG_0x0DF               0x0DF
#define FLAG_0x0E0               0x0E0
#define FLAG_0x0E1               0x0E1
#define FLAG_0x0E2               0x0E2
#define FLAG_0x0E3               0x0E3
#define FLAG_0x0E4               0x0E4
#define FLAG_0x0E5               0x0E5
#define FLAG_0x0E6               0x0E6
#define FLAG_0x0E7               0x0E7
#define FLAG_0x0E8               0x0E8
#define FLAG_0x0E9               0x0E9
#define FLAG_0x0EA               0x0EA
#define FLAG_0x0EB               0x0EB
#define FLAG_0x0EC               0x0EC
#define FLAG_0x0ED               0x0ED
#define FLAG_0x0EE               0x0EE
#define FLAG_0x0EF               0x0EF
#define FLAG_0x0F0               0x0F0
#define FLAG_0x0F1               0x0F1
#define FLAG_0x0F2               0x0F2
#define FLAG_0x0F3               0x0F3
#define FLAG_0x0F4               0x0F4
#define FLAG_0x0F5               0x0F5
#define FLAG_0x0F6               0x0F6
#define FLAG_0x0F7               0x0F7
#define FLAG_0x0F8               0x0F8
#define FLAG_0x0F9               0x0F9
#define FLAG_0x0FA               0x0FA
#define FLAG_0x0FB               0x0FB
#define FLAG_0x0FC               0x0FC
#define FLAG_0x0FD               0x0FD
#define FLAG_0x0FE               0x0FE
#define FLAG_0x0FF               0x0FF
#define FLAG_0x100               0x100
#define FLAG_0x101               0x101
#define FLAG_0x102               0x102
#define FLAG_0x103               0x103
#define FLAG_0x104               0x104
#define FLAG_0x105               0x105
#define FLAG_0x106               0x106
#define FLAG_0x107               0x107
#define FLAG_0x108               0x108
#define FLAG_0x109               0x109
#define FLAG_0x10A               0x10A
#define FLAG_0x10B               0x10B
#define FLAG_0x10C               0x10C
#define FLAG_0x10D               0x10D
#define FLAG_0x10E               0x10E
#define FLAG_0x10F               0x10F
#define FLAG_0x110               0x110
#define FLAG_0x111               0x111
#define FLAG_0x112               0x112
#define FLAG_0x113               0x113
#define FLAG_0x114               0x114
#define FLAG_0x115               0x115
#define FLAG_0x116               0x116
#define FLAG_0x117               0x117
#define FLAG_0x118               0x118
#define FLAG_0x119               0x119
#define FLAG_0x11A               0x11A
#define FLAG_0x11B               0x11B
#define FLAG_0x11C               0x11C
#define FLAG_0x11D               0x11D
#define FLAG_0x11E               0x11E
#define FLAG_0x11F               0x11F
#define FLAG_0x120               0x120
#define FLAG_0x121               0x121
#define FLAG_0x122               0x122
#define FLAG_0x123               0x123
#define FLAG_0x124               0x124
#define FLAG_0x125               0x125
#define FLAG_0x126               0x126
#define FLAG_0x127               0x127
#define FLAG_0x128               0x128
#define FLAG_0x129               0x129
#define FLAG_0x12A               0x12A
#define FLAG_0x12B               0x12B
#define FLAG_0x12C               0x12C
#define FLAG_0x12D               0x12D
#define FLAG_0x12E               0x12E
#define FLAG_0x12F               0x12F
#define FLAG_0x130               0x130
#define FLAG_0x131               0x131
#define FLAG_0x132               0x132
#define FLAG_0x133               0x133
#define FLAG_0x134               0x134
#define FLAG_0x135               0x135
#define FLAG_0x136               0x136
#define FLAG_0x137               0x137
#define FLAG_0x138               0x138
#define FLAG_0x139               0x139
#define FLAG_0x13A               0x13A
#define FLAG_0x13B               0x13B
#define FLAG_0x13C               0x13C
#define FLAG_0x13D               0x13D
#define FLAG_0x13E               0x13E
#define FLAG_0x13F               0x13F
#define FLAG_0x140               0x140
#define FLAG_0x141               0x141
#define FLAG_0x142               0x142
#define FLAG_0x143               0x143
#define FLAG_0x144               0x144
#define FLAG_0x145               0x145
#define FLAG_0x146               0x146
#define FLAG_0x147               0x147
#define FLAG_0x148               0x148
#define FLAG_0x149               0x149
#define FLAG_0x14A               0x14A
#define FLAG_0x14B               0x14B
#define FLAG_0x14C               0x14C
#define FLAG_0x14D               0x14D
#define FLAG_0x14E               0x14E
#define FLAG_0x14F               0x14F
#define FLAG_0x150               0x150
#define FLAG_0x151               0x151
#define FLAG_0x152               0x152
#define FLAG_0x153               0x153

// Item ball hide/show
#define FLAG_HIDE_ROUTE1_POKEBALL                               0x154
#define FLAG_HIDE_ROUTE1_TM53_ENERGY_BALL                       0x155
#define FLAG_HIDE_ROUTE17_POTION                                0x156
#define FLAG_HIDE_ROUTE_2_ANTIDOTE                              0x157
#define FLAG_HIDE_ROUTE_2_TM83_INFESTATION                      0x158
#define FLAG_HIDE_ROUTE_2_NUGGET                                0x159
#define FLAG_HIDE_ROUTE_2_TM96_NATURE_POWER                     0x15A
#define FLAG_HIDE_ROUTE_2_CHOICE_SCARF                          0x15B
#define FLAG_HIDE_ROUTE_2_LAX_INCENSE                           0x15C
#define FLAG_HIDE_ANTHRA_TOWN_POTION                            0x15D
#define FLAG_HIDE_VARISI_FOREST_TINYMUSHROOM                    0x15E
#define FLAG_HIDE_VARISI_FOREST_ANTIDOTE                        0x15F
#define FLAG_HIDE_VARISI_FOREST_POKEBALL                        0x160
#define FLAG_HIDE_RHODANZI_CITY_TM49_ECHOEDVOICE                0x161
#define FLAG_HIDE_RHODANZI_CITY_SODA_POP                        0x162
#define FLAG_HIDE_OLENIC_TOWN_TM87_SWAGGER                      0x163
#define FLAG_HIDE_ROUTE_3_POTION                                0x164
#define FLAG_HIDE_ROUTE_3_ESCAPE_ROPE                           0x165
#define FLAG_HIDE_ROUTE_3_DIRE_HIT                              0x166
#define FLAG_HIDE_ROUTE_3_POKEBALL                              0x167
#define FLAG_HIDE_ROUTE_3_STAR_PIECE                            0x168
#define FLAG_HIDE_ROUTE_3_TM12_TAUNT                            0x169
#define FLAG_HIDE_RUBARR_DESERT_MYSTIC_WATER                    0x16A
#define FLAG_HIDE_RUBARR_DESERT_TM43_FLAME_CHARGE               0x16B
#define FLAG_HIDE_RUBARR_DESERT_GREAT_BALL                      0x16C
#define FLAG_HIDE_RUBARR_DESERT_SOFT_SAND                       0x16D
#define FLAG_HIDE_RUBARR_DESERT_STAR_PIECE                      0x16E
#define FLAG_HIDE_RUBARR_DESERT_FOCUS_SASH                      0x16F
#define FLAG_HIDE_ROUTE_4_SUPER_POTION                          0x170
#define FLAG_HIDE_ROUTE_4_QUICK_CLAW                            0x171
#define FLAG_HIDE_ROUTE_4_TM01_WORK_UP                          0x172
#define FLAG_HIDE_ROUTE_4_GRASSY_SEED                           0x173
#define FLAG_HIDE_ROUTE_4_ROSE_INCENSE                          0x174
#define FLAG_HIDE_TORMA_CAVE_BF1_REPEL                          0x175
#define FLAG_HIDE_TORMA_CAVE_BF1_SMOOTH_ROCK                    0x176
#define FLAG_HIDE_TORMA_CAVE_BF1_GLALITITE                      0x177
#define FLAG_HIDE_TORMA_CAVE_BF1_SUPER_POTION                   0x178
#define FLAG_HIDE_TORMA_CAVE_BF1_ROCKY_HELMET                   0x179
#define FLAG_HIDE_TORMA_CAVE_BF1_GREAT_BALL                     0x17A
#define FLAG_HIDE_TORMA_CAVE_BF1_ESCAPE_ROPE                    0x17B
#define FLAG_HIDE_TORMA_CAVE_BF2_SNOWBALL                       0x17C
#define FLAG_HIDE_TORMA_CAVE_BF2_CALCIUM                        0x17D
#define FLAG_HIDE_TORMA_CAVE_BF2_NEVERMELTICE                   0x17E
#define FLAG_HIDE_TORMA_CAVE_BF2_ICE_STONE                      0x17F
#define FLAG_HIDE_ROUTE_4_TM71_STONE_EDGE                       0x180
#define FLAG_HIDE_ROUTE_13_METAL_COAT                           0x181
#define FLAG_HIDE_ROUTE_13_HYPER_POTION                         0x182
#define FLAG_HIDE_ROUTE_13_MAX_ELIXER                           0x183
#define FLAG_HIDE_ROUTE_13_CHARIZARDITE_Y                       0x184
#define FLAG_HIDE_ROUTE_13_TM39_ROCK_TOMB                       0x185
#define FLAG_HIDE_ROUTE_13_PROTEIN                              0x186
#define FLAG_HIDE_ROUTE_13_HEAVY_DUTY_BOOTS                     0x187
#define FLAG_HIDE_FERROX_VILLAGE_ABSORB_BULB                    0x188
#define FLAG_HIDE_FERROX_VILLAGE_FULL_HEAL                      0x189
#define FLAG_HIDE_ROUTE_5_TM58_ENDURE                           0x18A
#define FLAG_HIDE_ROUTE_5_HEAL_BALL                             0x18B
#define FLAG_HIDE_ROUTE_5_METAL_POWDER                          0x18C
#define FLAG_HIDE_ROUTE_5_SILVER_POWDER                         0x18D
#define FLAG_HIDE_HELEO_RANCH_MIRACLE_SEED                      0x18E
#define FLAG_HIDE_HELEO_RANCH_NEST_BALL                         0x18F
#define FLAG_HIDE_HELEO_RANCH_TM45_ATTRACT                      0x190
#define FLAG_HIDE_HELEO_RANCH_TERRAIN_EXTENDER                  0x191
#define FLAG_HIDE_HELEO_RANCH_AMPHAROSITE                       0x192
#define FLAG_HIDE_ROUTE_11_ELECTRIC_SEED                        0x193
#define FLAG_HIDE_ROUTE_7_STICK                                 0x194
#define FLAG_HIDE_ROUTE_7_GREAT_BALL                            0x195
#define FLAG_HIDE_ROUTE_7_BLACK_BELT                            0x196
#define FLAG_HIDE_ROUTE_7_TM09_VENOSHOCK                        0x197
#define FLAG_HIDE_ROUTE_6_AMPHAROSITE                           0x198
#define FLAG_HIDE_ROUTE_6_TM78_BULLDOZE                         0x199
#define FLAG_HIDE_ROUTE_6_FRESH_WATER                           0x19A
#define FLAG_HIDE_ROUTE_6_LINK_CORD                             0x19B
#define FLAG_HIDE_ROUTE_6_DAMP_ROCK                             0x19C
#define FLAG_HIDE_ROUTE_6_CHOICE_BAND                           0x19D
#define FLAG_HIDE_ROUTE_6_TM88_STEALTH_ROCK                     0x19E
#define FLAG_HIDE_ROUTE_6_IRON                                  0x19F
#define FLAG_HIDE_ROUTE_6_RARE_CANDY                            0x1A0
#define FLAG_HIDE_ROUTE_6_NUGGET                                0x1A1
#define FLAG_HIDE_HELEO_CITY_CELL_BATTERY                       0x1A2
#define FLAG_HIDE_ROUTE_8_TM40_AERIAL_ACE                       0x1A3
#define FLAG_HIDE_ROUTE_8_TM48_ROUND                            0x1A4
#define FLAG_HIDE_ROUTE_8_TM34_SLUDGE_WAVE                      0x1A5
#define FLAG_0x1A6                                              0x1A6
#define FLAG_HIDE_ROUTE_8_SHELL_BELL                            0x1A7
#define FLAG_HIDE_ROUTE_8_SUPER_POTION                          0x1A8
#define FLAG_HIDE_ROUTE_8_KINGS_ROCK                            0x1A9
#define FLAG_HIDE_ROUTE_8_POISON_BARB                           0x1AA
#define FLAG_HIDE_ROUTE_8_GREAT_BALL                            0x1AB
#define FLAG_HIDE_ROUTE_8_MISTY_SEED                            0x1AC
#define FLAG_HIDE_FORGOTTEN_MANSE_CAVE_RARE_CANDY               0x1AD
#define FLAG_HIDE_FORGOTTEN_MANSE_EXT_ODD_INCENSE               0x1AE
#define FLAG_HIDE_FORGOTTEN_MANSE_EXT_FRONT_DOOR_KEY            0x1AF
#define FLAG_HIDE_FORGOTTEN_MANSE_1F_CLEANSE_TAG                0x1B0
#define FLAG_HIDE_FORGOTTEN_MANSE_1F_GREAT_BALL                 0x1B1
#define FLAG_HIDE_FORGOTTEN_MANSE_1F_STORAGE_KEY                0x1B2
#define FLAG_HIDE_FORGOTTEN_MANSE_2F_SPELL_TAG                  0x1B3
#define FLAG_HIDE_FORGOTTEN_MANSE_2F_DUSK_STONE                 0x1B4
#define FLAG_HIDE_FORGOTTEN_MANSE_BF1_ESCAPE_ROPE               0x1B5
#define FLAG_HIDE_FORGOTTEN_MANSE_BF1_DESTINY_KNOT              0x1B6
#define FLAG_HIDE_FORGOTTEN_MANSE_2F_TM60_HEX                   0x1B7
#define FLAG_HIDE_FORGOTTEN_MANSE_BF1_TM61_WILL_O_WISP          0x1B8
#define FLAG_HIDE_FORGOTTEN_MANSE_1F_SABLENITE                  0x1B9
#define FLAG_HIDE_DAIMYN_CITY_TM46_THIEF                        0x1BA
#define FLAG_HIDE_DAIMYN_CITY_TM54_FALSE_SWIPE                  0x1BB
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_SUPER_POTION         0x1BC
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_TM93_WILD_CHARGE     0x1BD
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_SUPER_REPEL          0x1BE
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_MAGNET               0x1BF
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_REVIVE               0x1C0
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_LUCARIONITE          0x1C1
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_TM57_CHARGE_BEAM     0x1C2
#define FLAG_HIDE_DAIMYN_FACTORY_OVERWORLD_EJECT_BUTTON         0x1C3
#define FLAG_HIDE_ROUTE9_SCEPTILITE                             0x1C4
#define FLAG_HIDE_ROUTE9_SHARP_BEAK                             0x1C5
#define FLAG_HIDE_ROUTE9_THUNDER_STONE                          0x1C6
#define FLAG_HIDE_ROUTE9_TM62_ACROBATICS                        0x1C7
#define FLAG_HIDE_ROUTE10_ROCK_INCENSE                          0x1C8
#define FLAG_HIDE_ROUTE10_PSYCHIC_SEED                          0x1C9
#define FLAG_HIDE_ROUTE10_TM64_EXPLOSION                        0x1CA
#define FLAG_HIDE_ROUTE10_TM41_TORMENT                          0x1CB
#define FLAG_HIDE_ROUTE10_LOPUNNITE                             0x1CC
#define FLAG_HIDE_ROUTE10_DRAGON_SCALE                          0x1CD
#define FLAG_HIDE_ROUTE10_ELIXER                                0x1CE
#define FLAG_HIDE_ROUTE10_TM23_SMACK_DOWN                       0x1CF
#define FLAG_HIDE_ROUTE11_SOUTH_RAZOR_CLAW                      0x1D0
#define FLAG_HIDE_ROUTE11_SOUTH_TM68_GIGA_IMPACT                0x1D1
#define FLAG_HIDE_ROUTE11_SOUTH_TM51_STEEL_WING                 0x1D2
#define FLAG_HIDE_ROUTE11_SOUTH_HEAT_ROCK                       0x1D3
#define FLAG_HIDE_ROUTE11_SOUTH_MAWILITE                        0x1D4
#define FLAG_HIDE_ROUTE11_SOUTH_CARBOS                          0x1D5
#define FLAG_HIDE_HESSON_PASS_F1_HYPER_POTION                   0x1D6
#define FLAG_HIDE_HESSON_PASS_F1_HP_UP                          0x1D7
#define FLAG_HIDE_HESSON_PASS_F1_ULTRA_BALL                     0x1D8
#define FLAG_HIDE_HESSON_PASS_BF1_STAR_PIECE                    0x1D9
#define FLAG_HIDE_HESSON_PASS_BF1_CHARIZARDITE_X                0x1DA
#define FLAG_HIDE_HESSON_PASS_F2_TM67_SMART_STRIKE              0x1DB
#define FLAG_HIDE_HESSON_PASS_F2_ELIXIR                         0x1DC
#define FLAG_HIDE_ROUTE11_NORTH_TM03_PSYSHOCK                   0x1DD
#define FLAG_HIDE_ROUTE11_NORTH_REAPER_CLOTH                    0x1DE
#define FLAG_HIDE_ROUTE11_NORTH_ULTRA_BALL                      0x1DF
#define FLAG_HIDE_ROUTE11_NORTH_RED_CARD                        0x1E0
#define FLAG_HIDE_ROUTE11_NORTH_TM47_LOW_SWEEP                  0x1E1
#define FLAG_HIDE_LAPLAZ_TOWN_LAGGING_TAIL                      0x1E2
#define FLAG_HIDE_PERADON_FOREST_BLACK_SLUDGE                   0x1E3
#define FLAG_HIDE_PERADON_FOREST_HYPER_POTION                   0x1E4
#define FLAG_HIDE_PERADON_FOREST_HERACRONITE                    0x1E5
#define FLAG_HIDE_PERADON_FOREST_LEAF_STONE                     0x1E6
#define FLAG_HIDE_PERADON_FOREST_TM86_GRASS_KNOT                0x1E7
#define FLAG_HIDE_PERADON_FOREST_TM81_X_SCISSOR                 0x1E8
#define FLAG_HIDE_PERADON_FOREST_FULL_RESTORE                   0x1E9
#define FLAG_HIDE_PERADON_FOREST_POKE_DOLL                      0x1EA
#define FLAG_HIDE_PERADON_FOREST_MAX_ELIXIR                     0x1EB
#define FLAG_HIDE_LAKE_LAPLAZ_BLACK_GLASSES                     0x1EC
#define FLAG_HIDE_LAKE_LAPLAZ_TM08_BULK_UP                      0x1ED
#define FLAG_HIDE_ROUTE12_EAST_HARD_STONE                       0x1EE
#define FLAG_HIDE_ROUTE12_EAST_ICY_ROCK                         0x1EF
#define FLAG_HIDE_ROUTE12_EAST_HYPER_POTION                     0x1F0
#define FLAG_HIDE_ROUTE12_EAST_TM95_SNARL                       0x1F1
#define FLAG_HIDE_SCALDING_SPA_TM35_FLAMETHROWER                0x1F2
#define FLAG_HIDE_SCALDING_SPA_BLAZIKENITE                      0x1F3
#define FLAG_HIDE_SCALDING_SPA_FIRE_STONE                       0x1F4
#define FLAG_HIDE_TORMA_CAVE_TM79_FROST_BREATH                  0x1F5
#define FLAG_HIDE_ROUTE_12_WEST_ULTRA_BALL                      0x1F6
#define FLAG_HIDE_ROUTE_12_WEST_ZINC                            0x1F7
#define FLAG_HIDE_ROUTE_12_WEST_TM13_ICE_BEAM                   0x1F8
#define FLAG_HIDE_ROUTE_12_WEST_REVIVE                          0x1F9
#define FLAG_HIDE_ROUTE_12_WEST_SLOWBRONITE                     0x1FA
#define FLAG_HIDE_ROUTE_12_WEST_ICE_STONE                       0x1FB
#define FLAG_HIDE_BRUCCIE_VILLAGE_RARE_CANDY                    0x1FC
#define FLAG_HIDE_SEVEN_ISLAND_SEVAULT_CANYON_HOUSE_LUCKY_PUNCH 0x1FD
#define FLAG_HIDE_SILPH_CO_4F_TM41                              0x1FE

// Unused?
#define FLAG_0x1FF               0x1FF
#define FLAG_0x200               0x200
#define FLAG_0x201               0x201
#define FLAG_0x202               0x202
#define FLAG_0x203               0x203
#define FLAG_0x204               0x204
#define FLAG_0x205               0x205
#define FLAG_0x206               0x206
#define FLAG_0x207               0x207
#define FLAG_0x208               0x208
#define FLAG_0x209               0x209
#define FLAG_0x20A               0x20A
#define FLAG_0x20B               0x20B
#define FLAG_0x20C               0x20C
#define FLAG_0x20D               0x20D
#define FLAG_0x20E               0x20E
#define FLAG_0x20F               0x20F
#define FLAG_0x210               0x210
#define FLAG_0x211               0x211
#define FLAG_0x212               0x212
#define FLAG_0x213               0x213
#define FLAG_0x214               0x214
#define FLAG_0x215               0x215
#define FLAG_0x216               0x216
#define FLAG_0x217               0x217
#define FLAG_0x218               0x218
#define FLAG_0x219               0x219
#define FLAG_0x21A               0x21A
#define FLAG_0x21B               0x21B
#define FLAG_0x21C               0x21C
#define FLAG_0x21D               0x21D
#define FLAG_0x21E               0x21E
#define FLAG_0x21F               0x21F
#define FLAG_0x220               0x220
#define FLAG_0x221               0x221
#define FLAG_0x222               0x222
#define FLAG_0x223               0x223
#define FLAG_0x224               0x224
#define FLAG_0x225               0x225
#define FLAG_0x226               0x226
#define FLAG_0x227               0x227
#define FLAG_0x228               0x228
#define FLAG_0x229               0x229
#define FLAG_0x22A               0x22A
#define FLAG_0x22B               0x22B
#define FLAG_0x22C               0x22C
#define FLAG_0x22D               0x22D
#define FLAG_0x22E               0x22E
#define FLAG_0x22F               0x22F
*/

// Story flags
/*
#define STORY_FLAGS_START 0x230
#define FLAG_COMPLETED_TYPE_TRAINER_QUIZ                 0x230
#define FLAG_RECEIVED_ANTIDOTE_GIFT                      0x231
#define FLAG_INITIATED_DEXNAV_EVENT                      0x232
#define FLAG_GOT_POKEMON_EGG_FROM_DAYCARE                0x233
#define FLAG_GOT_OVAL_CHARM                              0x234
#define FLAG_GOT_ROCK_SMASH_HM                           0x235
#define FLAG_GOT_SWARM_GIFT_RATTATA                      0x236
#define FLAG_GOT_SWARM_GIFT_RATICATE                     0x237
#define FLAG_GOT_SWARM_GIFT_RAICHU_A                     0x238
#define FLAG_GOT_SWARM_GIFT_GRIMER                       0x239
#define FLAG_GOT_SWARM_GIFT_MUK                          0x23A
#define FLAG_GOT_SWARM_GIFT_SLOWPOKE_G                   0x23B
#define FLAG_GOT_SWARM_GIFT_SLOWBRO_G                    0x23C
#define FLAG_GOT_SWARM_GIFT_SLOWKING_G                   0x23D
#define FLAG_GOT_SWARM_GIFT_FARFETCHD                    0x23E
#define FLAG_GOT_SWARM_GIFT_KOFFING                      0x23F
#define FLAG_GOT_SWARM_GIFT_WEEZING                      0x240
#define FLAG_GOT_SWARM_GIFT_MIME_JR                      0x241
#define FLAG_GOT_SWARM_GIFT_MR_MIME                      0x242
#define FLAG_GOT_SWARM_GIFT_CORSOLA                      0x243
#define FLAG_GOT_SWARM_GIFT_DARUMAKA                     0x244
#define FLAG_GOT_SWARM_GIFT_DARMANITAN                   0x245
#define FLAG_GOT_SWARM_GIFT_STUNFISK                     0x246
#define FLAG_GOT_QUICK_TIMER_BALL_GIFT_IN_HELEO_CITY     0x247
#define FLAG_DID_COSMO_TRADE                             0x248
#define FLAG_GOT_AIR_BALLOON_IN_HELEO_CITY               0x249
#define FLAG_GOT_OLD_ROD                                 0x24A
#define FLAG_GOT_GOOD_ROD                                0x24B
#define FLAG_GOT_SUPER_ROD                               0x24C
#define FLAG_GOT_LEFTOVERS_GIFT                          0x24D
#define FLAG_GOT_SOOTHE_BELL_GIFT                        0x24E
#define FLAG_GOT_BIKE                                    0x24F
#define FLAG_DAIMYN_RESTAURANT_EXPLAINED                 0x250
#define FLAG_HIDE_DAIMYN_CITY_STORY_NPCS                 0x251
#define FLAG_GOT_ITEMFINDER                              0x252
#define FLAG_BOUGHT_CARVANHA                             0x253
#define FLAG_DID_STARTER_BASED_TRADE                     0x254
#define FLAG_BATTLED_CASEY_IN_TORMA_CAVE                 0x255
#define FLAG_BATTLED_CASEY_ON_ROUTE_10                   0x256
#define FLAG_GOT_HIDDEN_POWER_FROM_PSYCHIC_SIBLINGS      0x257
#define FLAG_BEAT_RIVAL_ON_ROUTE_17                      0x258
#define FLAG_GOT_TM06_FROM_KOGA                          0x259
#define FLAG_0x25A                                       0x25A
#define FLAG_GOT_TM27                                    0x25B
#define FLAG_0x25C                                       0x25C
#define FLAG_0x25D                                       0x25D
#define FLAG_GOT_OLD_AMBER                               0x25E
#define FLAG_0x25F                                       0x25F
#define FLAG_0x260                                       0x260
#define FLAG_0x261                                       0x261
#define FLAG_0x262                                       0x262
#define FLAG_GOT_EEVEE                                   0x263
#define FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES           0x264
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_1             0x265
*/
#define FLAG_PENDING_DAYCARE_EGG                         0x266
/*
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_2             0x267
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_3             0x268
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_4             0x269
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_5             0x26A
#define FLAG_FORGOTTEN_MANSE_SECURITY_GATE_6             0x26B
#define FLAG_GOT_LUCKY_EGG                               0x26C
#define FLAG_OPENED_ROCKET_HIDEOUT                       0x26D
#define FLAG_GOT_10_COINS_FROM_GAMBLER                   0x26E
#define FLAG_GOT_20_COINS_FROM_GAMBLER                   0x26F
#define FLAG_GOT_20_COINS_FROM_GAMBLER_2                 0x270
#define FLAG_GOT_BICYCLE                                 0x271
#define FLAG_GOT_DOME_FOSSIL                             0x272
#define FLAG_GOT_HELIX_FOSSIL                            0x273
#define FLAG_DID_ESPHERE_TRADE                           0x274
#define FLAG_DID_TANGENY_TRADE                           0x275
#define FLAG_DID_SEELOR_TRADE                            0x276
#define FLAG_0x277                                       0x277
#define FLAG_GOT_HITMON_FROM_DOJO                        0x278
#define FLAG_0x279                                       0x279
#define FLAG_SILPH_2F_DOOR_1                             0x27A
#define FLAG_SILPH_2F_DOOR_2                             0x27B
#define FLAG_SILPH_3F_DOOR_1                             0x27C
#define FLAG_SILPH_3F_DOOR_2                             0x27D
#define FLAG_SILPH_4F_DOOR_1                             0x27E
#define FLAG_SILPH_4F_DOOR_2                             0x27F
#define FLAG_SILPH_5F_DOOR_1                             0x280
#define FLAG_SILPH_5F_DOOR_2                             0x281
#define FLAG_SILPH_5F_DOOR_3                             0x282
#define FLAG_SILPH_6F_DOOR                               0x283
#define FLAG_SILPH_7F_DOOR_1                             0x284
#define FLAG_SILPH_7F_DOOR_2                             0x285
#define FLAG_SILPH_7F_DOOR_3                             0x286
#define FLAG_SILPH_8F_DOOR                               0x287
#define FLAG_SILPH_9F_DOOR_1                             0x288
#define FLAG_SILPH_9F_DOOR_2                             0x289
#define FLAG_SILPH_9F_DOOR_3                             0x28A
#define FLAG_SILPH_9F_DOOR_4                             0x28B
#define FLAG_SILPH_10F_DOOR                              0x28C
#define FLAG_SILPH_11F_DOOR                              0x28D
#define FLAG_0x28E                                       0x28E
#define FLAG_0x28F                                       0x28F
#define FLAG_MET_STICKER_LADY                            0x290
#define FLAG_PALLET_LADY_NOT_BLOCKING_SIGN               0x291
#define FLAG_GOT_VS_SEEKER                               0x292
#define FLAG_GOT_TM19_FROM_ERIKA                         0x293
#define FLAG_GOT_TM33_FROM_THIRSTY_GIRL                  0x294
#define FLAG_GOT_TM20_FROM_THIRSTY_GIRL                  0x295
#define FLAG_GOT_TM16_FROM_THIRSTY_GIRL                  0x296
#define FLAG_GOT_TM06_FROM_STELLA                        0x297
#define FLAG_GOT_TM26_FROM_GIOVANNI                      0x298
#define FLAG_0x299                                       0x299
#define FLAG_GOT_TM04_FROM_SABRINA                       0x29A
#define FLAG_GOT_FAME_CHECKER                            0x29B
#define FLAG_GOT_RECORD_SETTING_MAGIKARP                 0x29C
#define FLAG_TWO_ISLAND_SHOP_INTRODUCED                  0x29D
#define FLAG_TWO_ISLAND_SHOP_EXPANDED_1                  0x29E
#define FLAG_TWO_ISLAND_SHOP_EXPANDED_2                  0x29F
#define FLAG_TWO_ISLAND_SHOP_EXPANDED_3                  0x2A0
#define FLAG_SEVII_DETOUR_FINISHED                       0x2A1
#define FLAG_VISITED_TWO_ISLAND                          0x2A2
#define FLAG_RESCUED_LOSTELLE                            0x2A3
#define FLAG_0x2A4                                       0x2A4
#define FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT                 0x2A5
#define FLAG_GOT_TEA                                     0x2A6
#define FLAG_GOT_AURORA_TICKET                           0x2A7
#define FLAG_GOT_MYSTIC_TICKET                           0x2A8
#define FLAG_0x2A9                                       0x2A9
#define FLAG_0x2AA                                       0x2AA
#define FLAG_0x2AB                                       0x2AB
#define FLAG_0x2AC                                       0x2AC
#define FLAG_0x2AD                                       0x2AD
#define FLAG_0x2AE                                       0x2AE
#define FLAG_0x2AF                                       0x2AF
#define FLAG_0x2B0                                       0x2B0
#define FLAG_0x2B1                                       0x2B1
#define FLAG_0x2B2                                       0x2B2
#define FLAG_0x2B3                                       0x2B3
#define FLAG_0x2B4                                       0x2B4
#define FLAG_0x2B5                                       0x2B5
#define FLAG_0x2B6                                       0x2B6
#define FLAG_0x2B7                                       0x2B7
#define FLAG_0x2B8                                       0x2B8
#define FLAG_0x2B9                                       0x2B9
#define FLAG_0x2BA                                       0x2BA
#define FLAG_GOT_POWDER_JAR                              0x2BB
#define FLAG_FOUGHT_MEWTWO                               0x2BC
#define FLAG_FOUGHT_MOLTRES                              0x2BD
#define FLAG_FOUGHT_ARTICUNO                             0x2BE
#define FLAG_FOUGHT_ZAPDOS                               0x2BF
#define FLAG_RIVAL_EVENT_1                               0x2C0
#define FLAG_RIVAL_EVENT_2                               0x2C1
#define FLAG_RIVAL_EVENT_3                               0x2C2
#define FLAG_RIVAL_EVENT_4                               0x2C3
#define FLAG_RIVAL_EVENT_5                               0x2C4
#define FLAG_RIVAL_EVENT_6                               0x2C5
#define FLAG_RIVAL_EVENT_7                               0x2C6
#define FLAG_RIVAL_EVENT_8                               0x2C7
#define FLAG_RIVAL_EVENT_9                               0x2C8
#define FLAG_RIVAL_EVENT_10                              0x2C9
#define FLAG_TUTOR_SEISMIC_TOSS                          0x2CA
#define FLAG_TUTOR_COUNTER                               0x2CB
#define FLAG_TUTOR_METRONOME                             0x2CC
#define FLAG_TUTOR_MIMIC                                 0x2CD
#define FLAG_TUTOR_BODY_SLAM                             0x2CE
#define FLAG_VISITED_OAKS_LAB                            0x2CF
#define FLAG_FOUGHT_POWER_PLANT_ELECTRODE_1              0x2D0
#define FLAG_FOUGHT_POWER_PLANT_ELECTRODE_2              0x2D1
#define FLAG_STOPPED_SEAFOAM_B3F_CURRENT                 0x2D2
#define FLAG_STOPPED_SEAFOAM_B4F_CURRENT                 0x2D3
#define FLAG_TALKED_TO_LORELEI_AFTER_WAREHOUSE           0x2D4
#define FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE               0x2D5
#define FLAG_UNLOCKED_ROCKET_WAREHOUSE                   0x2D6
#define FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR         0x2D7
#define FLAG_LEARNED_YES_NAH_CHANSEY                     0x2D8
#define FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1       0x2D9
#define FLAG_GOT_TOGEPI_EGG                              0x2DA
#define FLAG_NO_ROOM_FOR_TOGEPI_EGG                      0x2DB
#define FLAG_RECOVERED_SAPPHIRE                          0x2DC
#define FLAG_GOT_RUBY                                    0x2DD
#define FLAG_TUTOR_FRENZY_PLANT                          0x2DE
#define FLAG_TUTOR_BLAST_BURN                            0x2DF
#define FLAG_TUTOR_HYDRO_CANNON                          0x2E0
#define FLAG_LEARNED_ALL_MOVES_AT_CAPE_BRINK             0x2E1
#define FLAG_GOT_NUGGET_FROM_DUNSPARCE_TUNNEL            0x2E2
#define FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE             0x2E3
#define FLAG_FOUGHT_DEOXYS                               0x2E4
#define FLAG_0x2E5                                       0x2E5
#define FLAG_0x2E6                                       0x2E6
#define FLAG_0x2E7                                       0x2E7
#define FLAG_0x2E8                                       0x2E8
#define FLAG_0x2E9                                       0x2E9
#define FLAG_0x2EA                                       0x2EA
#define FLAG_0x2EB                                       0x2EB
#define FLAG_REVIVED_DOME                                0x2EC
#define FLAG_REVIVED_HELIX                               0x2ED
#define FLAG_REVIVED_AMBER                               0x2EE
#define FLAG_GOT_HM06                                    0x2EF
#define FLAG_SHOWED_MYSTICTICKET_TO_CAPTAIN              0x2F0
#define FLAG_SHOWED_AURORATICKET_TO_CAPTAIN              0x2F1
#define FLAG_FOUGHT_LUGIA                                0x2F2
#define FLAG_FOUGHT_HO_OH                                0x2F3
#define FLAG_OAK_SAW_DEX_COMPLETION                      0x2F4
#define FLAG_LUGIA_FLEW_AWAY                             0x2F5
#define FLAG_HO_OH_FLEW_AWAY                             0x2F6
#define FLAG_DEOXYS_FLEW_AWAY                            0x2F7
#define FLAG_TALKED_TO_TEA_LADY_AFTER_HOF                0x2F8
#define FLAG_TALKED_TO_OAKS_AIDE_IN_VERMILION            0x2F9
#define FLAG_GOT_EVERSTONE_FROM_OAKS_AIDE                0x2FA
#define FLAG_GOT_MOON_STONE_FROM_JOYFUL_GAME_CORNER      0x2FB
#define FLAG_GOT_FULL_RESTORE_FROM_THREE_ISLAND_DEFENDER 0x2FC
#define FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE              0x2FD
#define FLAG_NO_ROOM_FOR_JOYFUL_GAME_CORNER_MOON_STONE   0x2FE
*/
#define FLAG_OAKS_RATING_IS_VIA_PC                       0x2FF

// Unused?
/*
#define FLAG_0x300               0x300
#define FLAG_0x301               0x301
#define FLAG_0x302               0x302
#define FLAG_0x303               0x303
#define FLAG_0x304               0x304
#define FLAG_0x305               0x305
#define FLAG_0x306               0x306
#define FLAG_0x307               0x307
#define FLAG_0x308               0x308
#define FLAG_0x309               0x309
#define FLAG_0x30A               0x30A
#define FLAG_0x30B               0x30B
#define FLAG_0x30C               0x30C
#define FLAG_0x30D               0x30D
#define FLAG_0x30E               0x30E
#define FLAG_0x30F               0x30F
#define FLAG_0x310               0x310
#define FLAG_0x311               0x311
#define FLAG_0x312               0x312
#define FLAG_0x313               0x313
#define FLAG_0x314               0x314
#define FLAG_0x315               0x315
#define FLAG_0x316               0x316
#define FLAG_0x317               0x317
#define FLAG_0x318               0x318
#define FLAG_0x319               0x319
#define FLAG_0x31A               0x31A
#define FLAG_0x31B               0x31B
#define FLAG_0x31C               0x31C
#define FLAG_0x31D               0x31D
#define FLAG_0x31E               0x31E
#define FLAG_0x31F               0x31F
#define FLAG_0x320               0x320
#define FLAG_0x321               0x321
#define FLAG_0x322               0x322
#define FLAG_0x323               0x323
#define FLAG_0x324               0x324
#define FLAG_0x325               0x325
#define FLAG_0x326               0x326
#define FLAG_0x327               0x327
#define FLAG_0x328               0x328
#define FLAG_0x329               0x329
#define FLAG_0x32A               0x32A
#define FLAG_0x32B               0x32B
#define FLAG_0x32C               0x32C
#define FLAG_0x32D               0x32D
#define FLAG_0x32E               0x32E
#define FLAG_0x32F               0x32F
#define FLAG_0x330               0x330
#define FLAG_0x331               0x331
#define FLAG_0x332               0x332
#define FLAG_0x333               0x333
#define FLAG_0x334               0x334
#define FLAG_0x335               0x335
#define FLAG_0x336               0x336
#define FLAG_0x337               0x337
#define FLAG_0x338               0x338
#define FLAG_0x339               0x339
#define FLAG_0x33A               0x33A
#define FLAG_0x33B               0x33B
#define FLAG_0x33C               0x33C
#define FLAG_0x33D               0x33D
#define FLAG_0x33E               0x33E
#define FLAG_0x33F               0x33F
#define FLAG_0x340               0x340
#define FLAG_0x341               0x341
#define FLAG_0x342               0x342
#define FLAG_0x343               0x343
#define FLAG_0x344               0x344
#define FLAG_0x345               0x345
#define FLAG_0x346               0x346
#define FLAG_0x347               0x347
#define FLAG_0x348               0x348
#define FLAG_0x349               0x349
#define FLAG_0x34A               0x34A
#define FLAG_0x34B               0x34B
#define FLAG_0x34C               0x34C
#define FLAG_0x34D               0x34D
#define FLAG_0x34E               0x34E
#define FLAG_0x34F               0x34F
#define FLAG_0x350               0x350
#define FLAG_0x351               0x351
#define FLAG_0x352               0x352
#define FLAG_0x353               0x353
#define FLAG_0x354               0x354
#define FLAG_0x355               0x355
#define FLAG_0x356               0x356
#define FLAG_0x357               0x357
#define FLAG_0x358               0x358
#define FLAG_0x359               0x359
#define FLAG_0x35A               0x35A
#define FLAG_0x35B               0x35B
#define FLAG_0x35C               0x35C
#define FLAG_0x35D               0x35D
#define FLAG_0x35E               0x35E
#define FLAG_0x35F               0x35F
#define FLAG_0x360               0x360
#define FLAG_0x361               0x361
#define FLAG_0x362               0x362
#define FLAG_0x363               0x363
#define FLAG_0x364               0x364
#define FLAG_0x365               0x365
#define FLAG_0x366               0x366
#define FLAG_0x367               0x367
#define FLAG_0x368               0x368
#define FLAG_0x369               0x369
#define FLAG_0x36A               0x36A
#define FLAG_0x36B               0x36B
#define FLAG_0x36C               0x36C
#define FLAG_0x36D               0x36D
#define FLAG_0x36E               0x36E
#define FLAG_0x36F               0x36F
#define FLAG_0x370               0x370
#define FLAG_0x371               0x371
#define FLAG_0x372               0x372
#define FLAG_0x373               0x373
#define FLAG_0x374               0x374
#define FLAG_0x375               0x375
#define FLAG_0x376               0x376
#define FLAG_0x377               0x377
#define FLAG_0x378               0x378
#define FLAG_0x379               0x379
#define FLAG_0x37A               0x37A
#define FLAG_0x37B               0x37B
#define FLAG_0x37C               0x37C
#define FLAG_0x37D               0x37D
#define FLAG_0x37E               0x37E
#define FLAG_0x37F               0x37F
#define FLAG_0x380               0x380
#define FLAG_0x381               0x381
#define FLAG_0x382               0x382
#define FLAG_0x383               0x383
#define FLAG_0x384               0x384
#define FLAG_0x385               0x385
#define FLAG_0x386               0x386
#define FLAG_0x387               0x387
#define FLAG_0x388               0x388
#define FLAG_0x389               0x389
#define FLAG_0x38A               0x38A
#define FLAG_0x38B               0x38B
#define FLAG_0x38C               0x38C
#define FLAG_0x38D               0x38D
#define FLAG_0x38E               0x38E
#define FLAG_0x38F               0x38F
#define FLAG_0x390               0x390
#define FLAG_0x391               0x391
#define FLAG_0x392               0x392
#define FLAG_0x393               0x393
#define FLAG_0x394               0x394
#define FLAG_0x395               0x395
#define FLAG_0x396               0x396
#define FLAG_0x397               0x397
#define FLAG_0x398               0x398
#define FLAG_0x399               0x399
#define FLAG_0x39A               0x39A
#define FLAG_0x39B               0x39B
#define FLAG_0x39C               0x39C
#define FLAG_0x39D               0x39D
#define FLAG_0x39E               0x39E
#define FLAG_0x39F               0x39F
#define FLAG_0x3A0               0x3A0
#define FLAG_0x3A1               0x3A1
#define FLAG_0x3A2               0x3A2
#define FLAG_0x3A3               0x3A3
#define FLAG_0x3A4               0x3A4
#define FLAG_0x3A5               0x3A5
#define FLAG_0x3A6               0x3A6
#define FLAG_0x3A7               0x3A7
#define FLAG_0x3A8               0x3A8
#define FLAG_0x3A9               0x3A9
#define FLAG_0x3AA               0x3AA
#define FLAG_0x3AB               0x3AB
#define FLAG_0x3AC               0x3AC
#define FLAG_0x3AD               0x3AD
#define FLAG_0x3AE               0x3AE
#define FLAG_0x3AF               0x3AF
#define FLAG_0x3B0               0x3B0
#define FLAG_0x3B1               0x3B1
#define FLAG_0x3B2               0x3B2
#define FLAG_0x3B3               0x3B3
#define FLAG_0x3B4               0x3B4
#define FLAG_0x3B5               0x3B5
#define FLAG_0x3B6               0x3B6
#define FLAG_0x3B7               0x3B7
#define FLAG_0x3B8               0x3B8
#define FLAG_0x3B9               0x3B9
#define FLAG_0x3BA               0x3BA
#define FLAG_0x3BB               0x3BB
#define FLAG_0x3BC               0x3BC
#define FLAG_0x3BD               0x3BD
#define FLAG_0x3BE               0x3BE
#define FLAG_0x3BF               0x3BF
#define FLAG_0x3C0               0x3C0
#define FLAG_0x3C1               0x3C1
#define FLAG_0x3C2               0x3C2
#define FLAG_0x3C3               0x3C3
#define FLAG_0x3C4               0x3C4
#define FLAG_0x3C5               0x3C5
#define FLAG_0x3C6               0x3C6
#define FLAG_0x3C7               0x3C7
#define FLAG_0x3C8               0x3C8
#define FLAG_0x3C9               0x3C9
#define FLAG_0x3CA               0x3CA
#define FLAG_0x3CB               0x3CB
#define FLAG_0x3CC               0x3CC
#define FLAG_0x3CD               0x3CD
#define FLAG_0x3CE               0x3CE
#define FLAG_0x3CF               0x3CF
#define FLAG_0x3D0               0x3D0
#define FLAG_0x3D1               0x3D1
#define FLAG_0x3D2               0x3D2
#define FLAG_0x3D3               0x3D3
#define FLAG_0x3D4               0x3D4
#define FLAG_0x3D5               0x3D5
#define FLAG_0x3D6               0x3D6
#define FLAG_0x3D7               0x3D7
#define FLAG_MYSTERY_EVENT_DONE  0x3D8
#define FLAG_0x3D9               0x3D9
#define FLAG_0x3DA               0x3DA
#define FLAG_0x3DB               0x3DB
#define FLAG_0x3DC               0x3DC
#define FLAG_0x3DD               0x3DD
#define FLAG_0x3DE               0x3DE
#define FLAG_0x3DF               0x3DF
#define FLAG_0x3E0               0x3E0
#define FLAG_0x3E1               0x3E1
#define FLAG_0x3E2               0x3E2
#define FLAG_0x3E3               0x3E3
#define FLAG_0x3E4               0x3E4
#define FLAG_0x3E5               0x3E5
#define FLAG_0x3E6               0x3E6
#define FLAG_0x3E7               0x3E7
*/

#define FLAG_HIDDEN_ITEMS_START 1000 // 0x3E8
#define FLAG_HIDDEN_ITEM(map, item) (FLAG_HIDDEN_ITEMS_START + HIDDEN_ITEM_##map##_##item)

/*
#define HIDDEN_ITEM_ROUTE_1_PECHA_BERRY                                 0
#define HIDDEN_ITEM_ROUTE_17_ORAN_BERRY                                 1
#define HIDDEN_ITEM_ROUTE_2_CHESTO_BERRY                                2
#define HIDDEN_ITEM_RHODANZI_CITY_RARE_CANDY                            3
#define HIDDEN_ITEM_VARISI_FOREST_CHERI_BERRY                           4
#define HIDDEN_ITEM_VARISI_FOREST_RAWST_BERRY                           5
#define HIDDEN_ITEM_OLENIC_TOWN_ASPEAR_BERRY                            6
#define HIDDEN_ITEM_ROUTE_3_ETHER                                       7
#define HIDDEN_ITEM_ROUTE_3_MOON_STONE                                  8
#define HIDDEN_ITEM_ROUTE_4_ESCAPE_ROPE                                 9
#define HIDDEN_ITEM_ROUTE_4_REVIVE                                     10
#define HIDDEN_ITEM_ROUTE_13_SITRUS_BERRY                              11
#define HIDDEN_ITEM_ROUTE_13_SHINY_STONE                               12
#define HIDDEN_ITEM_ROUTE_13_NUGGET                                    13
#define HIDDEN_ITEM_FERROX_VILLAGE_PP_UP                               14
#define HIDDEN_ITEM_ROUTE3_IRON                                        15
#define HIDDEN_ITEM_ROUTE2_X_SPECIAL                                   16
#define HIDDEN_ITEM_ROUTE4_SUPER_POTION                                17
#define HIDDEN_ITEM_TORMA_CAVE_EVERSTONE                               18
#define HIDDEN_ITEM_RUBARR_DESERT_SUN_STONE                            19
#define HIDDEN_ITEM_ROUTE5_GREAT_BALL                                  20
#define HIDDEN_ITEM_ROUTE5_CARBOS                                      21
#define HIDDEN_ITEM_ROUTE5_LEAF_STONE                                  22
#define HIDDEN_ITEM_ROUTE7_REPEAT_BALL                                 23
#define HIDDEN_ITEM_ROUTE6_ETHER                                       24
#define HIDDEN_ITEM_ROUTE6_WATER_STONE                                 25
#define HIDDEN_ITEM_ROUTE6_PP_UP                                       26
#define HIDDEN_ITEM_ROUTE6_BIG_MUSHROOM                                27
#define HIDDEN_ITEM_ROUTE6_BIG_ROOT                                    28
#define HIDDEN_ITEM_ROUTE6_WHITE_HERB                                  29
#define HIDDEN_ITEM_ROUTE6_QUICK_BALL                                  30
#define HIDDEN_ITEM_ROUTE6_STAR_PIECE                                  31
#define HIDDEN_ITEM_ROUTE6_HP_UP                                       32
#define HIDDEN_ITEM_ROUTE6_ELIXIR                                      33
#define HIDDEN_ITEM_HELEO_CITY_FRESH_WATER                             34
#define HIDDEN_ITEM_ROUTE8_NET_BALL                                    35
#define HIDDEN_ITEM_ROUTE8_RARE_CANDY                                  36
#define HIDDEN_ITEM_ROUTE8_ETHER                                       37
#define HIDDEN_ITEM_ROUTE8_STAR_PIECE                                  38
#define HIDDEN_ITEM_ROUTE8_ENERGY_ROOT                                 39
#define HIDDEN_ITEM_ROUTE8_EVERSTONE                                   40
#define HIDDEN_ITEM_FORGOTTEN_MANSE_AGUAV_BERRY                        41
#define HIDDEN_ITEM_FORGOTTEN_MANSE_SMOKE_BALL                         42
#define HIDDEN_ITEM_FORGOTTEN_MANSE_ESCAPE_ROPE                        43
#define HIDDEN_ITEM_DAIMYN_CITY_ULTRA_BALL                             44
#define HIDDEN_ITEM_DAIMYN_MALL_PEARL                                  45
#define HIDDEN_ITEM_DAIMYN_MALL_STARDUST                               46
#define HIDDEN_ITEM_DAIMYN_MALL_GREAT_BALL                             47
#define HIDDEN_ITEM_DAIMYN_MALL_ELIXER                                 48
#define HIDDEN_ITEM_DAIMYN_FACTORY_OVERWORLD_LUM_BERRY                 49
#define HIDDEN_ITEM_DAIMYN_FACTORY_OVERWORLD_RARE_CANDY                50
#define HIDDEN_ITEM_DAIMYN_FACTORY_OVERWORLD_HARD_STONE                51
#define HIDDEN_ITEM_DAIMYN_FACTORY_OVERWORLD_NUGGET                    52
#define HIDDEN_ITEM_ROUTE9_NEST_BALL                                   53
#define HIDDEN_ITEM_ROUTE9_TOXIC_ORB                                   54
#define HIDDEN_ITEM_ROUTE10_SITRUS_BERRY                               55
#define HIDDEN_ITEM_ROUTE10_DAWN_STONE                                 56
#define HIDDEN_ITEM_ROUTE11SOUTH_NUGGET                                57
#define HIDDEN_ITEM_ROUTE11SOUTH_QUICK_BALL                            58
#define HIDDEN_ITEM_ROUTE11SOUTH_TAMATO_BERRY                          59
#define HIDDEN_ITEM_HESSON_PASS_F1_CALCIUM                             60
#define HIDDEN_ITEM_HESSON_PASS_F1_SOFT_SAND                           61
#define HIDDEN_ITEM_HESSON_PASS_F1_EVERSTONE                           62
#define HIDDEN_ITEM_HESSON_PASS_F1_MAX_REVIVE                          63
#define HIDDEN_ITEM_HESSON_PASS_BF1_LIGHTCLAY                          64
#define HIDDEN_ITEM_HESSON_PASS_BF1_XDEFEND                            65
#define HIDDEN_ITEM_HESSON_PASS_F2_FULL_RESTORE                        66
#define HIDDEN_ITEM_HESSON_PASS_F2_NEST_BALL                           67
#define HIDDEN_ITEM_HESSON_PASS_F2_NUGGET                              68
#define HIDDEN_ITEM_ROUTE11NORTH_QUALOT_BERRY                          69
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   70 // These items are configured to randomly spawn as the player walks, starting after the player visits the SS Anne in Vanilla FR
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   71 // See here for more information: https://www.pokecommunity.com/threads/list-of-hidden-item-flags-used-in-fire-red.399026/
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   72
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   73
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   74
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   75
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   76
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   77
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   78
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   79
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   80
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   81
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   82
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   83
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   84
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   85
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   86
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   87
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   88
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   89
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   90
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   91
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   92
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   93
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   94
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   95
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   96
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   97
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   98
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT   99
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  100
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  101
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  102
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  103
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  104
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  105
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  106
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  107
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  108
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  109
#define HIDDEN_ITEM_RANDOMLY_REFRESHES_AS_PLAYER_WALKS_ON_BY_DEFAULT  110
#define HIDDEN_ITEM_HIDDEN_ITEM_ROUTE11NORTH_REVIVE                   111
#define HIDDEN_ITEM_HIDDEN_ITEM_ROUTE11NORTH_SITRUS_BERRY             112
#define HIDDEN_ITEM_HIDDEN_ITEM_ROUTE11NORTH_HYPER_POTION             113
#define HIDDEN_ITEM_HIDDEN_ITEM_ROUTE11NORTH_MAX_ETHER                114
#define HIDDEN_ITEM_LAPLAZ_TOWN_PP_UP                                 115
#define HIDDEN_ITEM_PERADON_FOREST_HONDEW_BERRY                       116
#define HIDDEN_ITEM_PERADON_FOREST_POMEG_BERRY                        117
#define HIDDEN_ITEM_PERADON_FOREST_RARE_CANDY                         118
#define HIDDEN_ITEM_PERADON_FOREST_SITRUS_BERRY                       119
#define HIDDEN_ITEM_PERADON_FOREST_REVIVE                             120
#define HIDDEN_ITEM_PERADON_FOREST_BIG_MUSHROOM                       121
#define HIDDEN_ITEM_PERADON_FOREST_ORAN_BERRY                         122
#define HIDDEN_ITEM_PERADON_FOREST_GREAT_BALL                         123
#define HIDDEN_ITEM_PERADON_FOREST_THREE_SITRUS_BERRIES               124
#define HIDDEN_ITEM_PERADON_FOREST_ETHER                              125
#define HIDDEN_ITEM_PERADON_FOREST_PECHA_BERRY                        126
#define HIDDEN_ITEM_PERADON_FOREST_SUPER_REPEL                        127
#define HIDDEN_ITEM_PERADON_FOREST_KELPSY_BERRY                       128
#define HIDDEN_ITEM_PERADON_FOREST_CHERI_BERRY                        129
#define HIDDEN_ITEM_PERADON_FOREST_BIG_MUSHROOM                       130
#define HIDDEN_ITEM_LAKE_LAPLAZ_DUSK_BALL                             131
#define HIDDEN_ITEM_LAKE_LAPLAZ_OVAL_STONE                            132
#define HIDDEN_ITEM_DAIMYN_CITY_GYM_AMULET_COIN                       133
#define HIDDEN_ITEM_ROUTE_12_EAST_LINK_CORD                           134
#define HIDDEN_ITEM_ROUTE_12_EAST_PROTEIN                             135
#define HIDDEN_ITEM_ROUTE_12_EAST_STARDUST                            136
#define HIDDEN_ITEM_SCALDING_SPA_LAVA_COOKIE                          137
#define HIDDEN_ITEM_ROUTE_12_WEST_FULL_RESTORE                        138
#define HIDDEN_ITEM_ROUTE_12_WEST_RARE_CANDY                          139
#define HIDDEN_ITEM_ROUTE_12_WEST_NUGGET                              140
#define HIDDEN_ITEM_ROUTE_12_WEST_ELIXIR                              141
#define HIDDEN_ITEM_SILPH_CO_9F_CALCIUM                               142
#define HIDDEN_ITEM_SILPH_CO_10F_HP_UP                                143
#define HIDDEN_ITEM_SILPH_CO_11F_REVIVE                               144
#define HIDDEN_ITEM_ROUTE23_LUM_BERRY                                 145
#define HIDDEN_ITEM_ROUTE23_SITRUS_BERRY                              146
#define HIDDEN_ITEM_ROUTE23_ASPEAR_BERRY                              147
#define HIDDEN_ITEM_ROUTE23_LEPPA_BERRY                               148
#define HIDDEN_ITEM_ROUTE14_ZINC                                      149
#define HIDDEN_ITEM_ROUTE9_CHESTO_BERRY                               150
#define HIDDEN_ITEM_ROUTE10_NANAB_BERRY                               151
#define HIDDEN_ITEM_ROUTE7_WEPEAR_BERRY                               152
#define HIDDEN_ITEM_ROUTE20_STARDUST                                  153
#define HIDDEN_ITEM_ROUTE21_NORTH_PEARL                               154
#define HIDDEN_ITEM_ROUTE23_MAX_ELIXIR                                155
#define HIDDEN_ITEM_ROUTE4_RAZZ_BERRY                                 156
#define HIDDEN_ITEM_ROUTE14_PINAP_BERRY                               157
#define HIDDEN_ITEM_MT_EMBER_EXTERIOR_FIRE_STONE                      158
#define HIDDEN_ITEM_POKEMON_TOWER_7F_SOOTHE_BELL                      159
#define HIDDEN_ITEM_NAVEL_ROCK_SUMMIT_SACRED_ASH                      160
#define HIDDEN_ITEM_TWO_ISLAND_CAPE_BRINK_PP_MAX                      161
#define HIDDEN_ITEM_MT_EMBER_EXTERIOR_ULTRA_BALL                      162
#define HIDDEN_ITEM_THREE_ISLAND_DUNSPARCE_TUNNEL_NUGGET              163
#define HIDDEN_ITEM_THREE_ISLAND_PP_UP                                164
#define HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_MAX_REPEL                165
#define HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_PEARL                    166
#define HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_STARDUST                 167
#define HIDDEN_ITEM_FOUR_ISLAND_PEARL                                 168
#define HIDDEN_ITEM_FOUR_ISLAND_ULTRA_BALL                            169
#define HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_BIG_PEARL             170
#define HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_RAZZ_BERRY            171
#define HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_SITRUS_BERRY          172
#define HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_BLUK_BERRY            173
#define HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_NEST_BALL             174
#define HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STARDUST              175
#define HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STAR_PIECE            176
#define HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STARDUST_2            177
#define HIDDEN_ITEM_SIX_ISLAND_OUTCAST_ISLAND_STAR_PIECE              178
#define HIDDEN_ITEM_SIX_ISLAND_OUTCAST_ISLAND_NET_BALL                179
#define HIDDEN_ITEM_SIX_ISLAND_GREEN_PATH_ULTRA_BALL                  180
#define HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_ASPEAR_BERRY                181
#define HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_ORAN_BERRY                  182
#define HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_PINAP_BERRY                 183
#define HIDDEN_ITEM_SIX_ISLAND_LEPPA_BERRY                            184
#define HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_BIG_PEARL              185
#define HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_PEARL                  186
#define HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_NANAB_BERRY            187
#define HIDDEN_ITEM_SEVEN_ISLAND_SEVAULT_CANYON_ENTRANCE_RAWST_BERRY  188
#define HIDDEN_ITEM_VIRIDIAN_CITY_GYM_MACHO_BRACE                     189
#define HIDDEN_ITEM_SSANNE_EXTERIOR_LAVA_COOKIE                       190

// Unused?
#define FLAG_0x4A7               0x4A7
#define FLAG_0x4A8               0x4A8
#define FLAG_0x4A9               0x4A9
#define FLAG_0x4AA               0x4AA
#define FLAG_0x4AB               0x4AB
#define FLAG_0x4AC               0x4AC
#define FLAG_0x4AD               0x4AD
#define FLAG_0x4AE               0x4AE
#define FLAG_0x4AF               0x4AF

// Boss clear flags, 1200
#define FLAG_DEFEATED_TERRENCE        0x4B0
#define FLAG_DEFEATED_STELLA          0x4B1
#define FLAG_DEFEATED_RAINE           0x4B2
#define FLAG_DEFEATED_CHANCE          0x4B3
#define FLAG_DEFEATED_CHANDLER        0x4B4
#define FLAG_DEFEATED_ABBY            0x4B5
#define FLAG_DEFEATED_IRIS            0x4B6
#define FLAG_DEFEATED_DENNIS_AND_DEE  0x4B7
#define FLAG_DEFEATED_E4_HANNAH       0x4B8
#define FLAG_DEFEATED_E4_LIAM         0x4B9
#define FLAG_DEFEATED_E4_JASMINE      0x4BA
#define FLAG_DEFEATED_E4_THOMAS       0x4BB
#define FLAG_DEFEATED_CHAMPION_SELENE 0x4BC

// Unused?
#define FLAG_0x4BD                            0x4BD
#define FLAG_0x4BE                            0x4BE
#define FLAG_0x4BF                            0x4BF
#define FLAG_0x4C0                            0x4C0
#define FLAG_0x4C1                            0x4C1
#define FLAG_0x4C2                            0x4C2
#define FLAG_0x4C3                            0x4C3
#define FLAG_0x4C4                            0x4C4
#define FLAG_0x4C5                            0x4C5
#define FLAG_0x4C6                            0x4C6
#define FLAG_0x4C7                            0x4C7
#define FLAG_0x4C8                            0x4C8
#define FLAG_0x4C9                            0x4C9
#define FLAG_0x4CA                            0x4CA
#define FLAG_0x4CB                            0x4CB
#define FLAG_0x4CC                            0x4CC
#define FLAG_0x4CD                            0x4CD
#define FLAG_0x4CE                            0x4CE
#define FLAG_0x4CF                            0x4CF
#define FLAG_0x4D0                            0x4D0
#define FLAG_0x4D1                            0x4D1
#define FLAG_0x4D2                            0x4D2
#define FLAG_0x4D3                            0x4D3
#define FLAG_0x4D4                            0x4D4
#define FLAG_0x4D5                            0x4D5
#define FLAG_0x4D6                            0x4D6
#define FLAG_0x4D7                            0x4D7
#define FLAG_0x4D8                            0x4D8
#define FLAG_0x4D9                            0x4D9
#define FLAG_0x4DA                            0x4DA
#define FLAG_0x4DB                            0x4DB
#define FLAG_0x4DC                            0x4DC
#define FLAG_0x4DD                            0x4DD
#define FLAG_0x4DE                            0x4DE
#define FLAG_0x4DF                            0x4DF
#define FLAG_0x4E0                            0x4E0
#define FLAG_0x4E1                            0x4E1
#define FLAG_0x4E2                            0x4E2
#define FLAG_0x4E3                            0x4E3
#define FLAG_0x4E4                            0x4E4
#define FLAG_0x4E5                            0x4E5
#define FLAG_0x4E6                            0x4E6
#define FLAG_0x4E7                            0x4E7
#define FLAG_0x4E8                            0x4E8
#define FLAG_0x4E9                            0x4E9
#define FLAG_0x4EA                            0x4EA
#define FLAG_0x4EB                            0x4EB
#define FLAG_0x4EC                            0x4EC
#define FLAG_0x4ED                            0x4ED
#define FLAG_0x4EE                            0x4EE
#define FLAG_0x4EF                            0x4EF
#define FLAG_0x4F0                            0x4F0
#define FLAG_0x4F1                            0x4F1
#define FLAG_0x4F2                            0x4F2
#define FLAG_0x4F3                            0x4F3
#define FLAG_0x4F4                            0x4F4
#define FLAG_0x4F5                            0x4F5
#define FLAG_0x4F6                            0x4F6
#define FLAG_0x4F7                            0x4F7
#define FLAG_0x4F8                            0x4F8
#define FLAG_0x4F9                            0x4F9
#define FLAG_0x4FA                            0x4FA
#define FLAG_0x4FB                            0x4FB
#define FLAG_0x4FC                            0x4FC
#define FLAG_0x4FD                            0x4FD
#define FLAG_DO_NOT_RESET_INVERSE_BATTLES     0x4FE
#define FLAG_DO_NOT_RESET_TRAINER_SCALING     0x4FF
*/

/*
Daily Flags, cleared at the start of each day.  Goes up to 0xEFF
#define FLAG_ROUTE_1_SANDYGAST                0xE00
#define FLAG_VARISI_FOREST_FOONGUS_1          0xE01
#define FLAG_VARISI_FOREST_FOONGUS_2          0xE02
#define FLAG_TORMA_CAVE_STUNFISK_G_1          0xE03
#define FLAG_TORMA_CAVE_STUNFISK_G_2          0xE04
#define FLAG_TORMA_CAVE_STUNFISK_G_3          0xE05
#define FLAG_FERROX_VILLAGE_BERRY             0xE06
#define FLAG_HELEO_RANCH_MAREEP_VISIBILITY    0xE07
#define FLAG_HELEO_RANCH_MOM_VISIBILITY       0xE08
#define FLAG_HELEO_CITY_SHADY_DEALER          0xE09
#define FLAG_HELEO_CITY_POKEMON_GROOMER       0xE0A
#define FLAG_HELEO_CITY_TRAINER_HOUSE         0xE0B
#define FLAG_ROUTE_8_SANDYGAST_1              0xE0C
#define FLAG_ROUTE_8_SANDYGAST_2              0xE0D
#define FLAG_DAIMYN_CITY_LUCKY_DRAW_SPECIES   0xE0E
#define FLAG_DAIMYN_CITY_DAILY_DEAL_SET       0xE0F
#define FLAG_DAIMYN_CITY_DAILY_DEAL_BOUGHT    0xE10
#define FLAG_LAPLAZ_TOWN_APRICORN_BALL_BOUGHT 0xE11
#define FLAG_LAPLAZ_TOWN_TRAINER_HOUSE        0xE12
#define FLAG_PERADON_FOREST_AMOONGUSS_1       0xE13
#define FLAG_PERADON_FOREST_AMOONGUSS_2       0xE14
#define FLAG_PERADON_FOREST_AMOONGUSS_3       0xE15
#define FLAG_PERADON_FOREST_FOONGUS_4         0xE16
#define FLAG_PERADON_FOREST_FOONGUS_5         0xE17
#define FLAG_BRUCCIE_VILLAGE_WINGULL_GIFT     0xE18
*/

#define FLAG_TRAINER_FLAG_START 0x500

// Vanilla: SYS_FLAGS = 0x800
//#define SYS_FLAGS (FLAG_TRAINER_FLAG_START + ((NUM_TRAINERS) + 31) / 32 * 32)
#define SYS_FLAGS 0x800

// SYSTEM FLAGS

// 0x800

#define FLAG_SYS_SAFARI_MODE (SYS_FLAGS + 0x0)
#define FLAG_SYS_VS_SEEKER_CHARGING (SYS_FLAGS + 0x1)
#define FLAG_SYS_WHITE_FLUTE_ACTIVE (SYS_FLAGS + 0x3)
#define FLAG_SYS_BLACK_FLUTE_ACTIVE (SYS_FLAGS + 0x4)
#define FLAG_SYS_STRENGTH_ACTIVE (SYS_FLAGS + 0x5)
#define FLAG_SYS_FLASH_ACTIVE (SYS_FLAGS + 0x6)
#define FLAG_SYS_SPECIAL_WILD_BATTLE (SYS_FLAGS + 0x7)
#define FLAG_0x808 (SYS_FLAGS + 0x8)

#define PERMA_SYS_FLAGS_START 0x820
#define FLAG_BADGE01_GET (SYS_FLAGS + 0x20)
#define FLAG_BADGE02_GET (SYS_FLAGS + 0x21)
#define FLAG_BADGE03_GET (SYS_FLAGS + 0x22)
#define FLAG_BADGE04_GET (SYS_FLAGS + 0x23)
#define FLAG_BADGE05_GET (SYS_FLAGS + 0x24)
#define FLAG_BADGE06_GET (SYS_FLAGS + 0x25)
#define FLAG_BADGE07_GET (SYS_FLAGS + 0x26)
#define FLAG_BADGE08_GET (SYS_FLAGS + 0x27)
#define FLAG_SYS_POKEMON_GET (SYS_FLAGS + 0x28)
#define FLAG_SYS_POKEDEX_GET (SYS_FLAGS + 0x29)
#define FLAG_0x82A (SYS_FLAGS + 0x2A)
#define FLAG_0x82B (SYS_FLAGS + 0x2B)
#define FLAG_SYS_GAME_CLEAR (SYS_FLAGS + 0x2C)
#define FLAG_SYS_SET_TRAINER_CARD_PROFILE (SYS_FLAGS + 0x2D)
#define FLAG_0x82E (SYS_FLAGS + 0x2E)
#define FLAG_SYS_B_DASH (SYS_FLAGS + 0x2F)
#define FLAG_SYS_ON_CYCLING_ROAD (SYS_FLAGS + 0x30)
#define FLAG_0x831 (SYS_FLAGS + 0x31)
#define FLAG_0x832 (SYS_FLAGS + 0x32)
#define FLAG_0x833 (SYS_FLAGS + 0x33)
#define FLAG_SYS_NOT_SOMEONES_PC (SYS_FLAGS + 0x34)
#define FLAG_0x835 (SYS_FLAGS + 0x35)
#define FLAG_0x836 (SYS_FLAGS + 0x36)
#define FLAG_0x837 (SYS_FLAGS + 0x37)
#define FLAG_0x838 (SYS_FLAGS + 0x38)
#define FLAG_SYS_MYSTERY_GIFT_ENABLED (SYS_FLAGS + 0x39)
#define FLAG_0x83A (SYS_FLAGS + 0x3A)
#define FLAG_SYS_RIBBON_GET (SYS_FLAGS + 0x3B)
#define FLAG_SYS_SAW_HELP_SYSTEM_INTRO (SYS_FLAGS + 0x3C)
#define FLAG_0x83D (SYS_FLAGS + 0x3D)
#define FLAG_OPENED_START_MENU (SYS_FLAGS + 0x3E)
#define FLAG_0x83F (SYS_FLAGS + 0x3F)
#define FLAG_SYS_NATIONAL_DEX (SYS_FLAGS + 0x40)
#define FLAG_SYS_PC_STORAGE_DISABLED (SYS_FLAGS + 0x41)
#define FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER (SYS_FLAGS + 0x42)
#define FLAG_SHOWN_BOX_WAS_FULL_MESSAGE (SYS_FLAGS + 0x43)
#define FLAG_SYS_CAN_LINK_WITH_RS (SYS_FLAGS + 0x44)
#define FLAG_SYS_SEVII_MAP_123 (SYS_FLAGS + 0x45)
#define FLAG_SYS_SEVII_MAP_4567 (SYS_FLAGS + 0x46)
#define FLAG_SYS_GOT_BERRY_POUCH (SYS_FLAGS + 0x47)
#define FLAG_SYS_DEOXYS_AWAKENED (SYS_FLAGS + 0x48)
#define FLAG_SYS_UNLOCKED_TANOBY_RUINS (SYS_FLAGS + 0x49)
#define FLAG_ENABLE_SHIP_NAVEL_ROCK (SYS_FLAGS + 0x4A)
#define FLAG_ENABLE_SHIP_BIRTH_ISLAND (SYS_FLAGS + 0x4B)

// World Map Flags
/*
#define FLAG_WORLD_MAP_ANTHRA_TOWN                                  (SYS_FLAGS + 0x90)
#define FLAG_WORLD_MAP_OLENIC_TOWN                                  (SYS_FLAGS + 0x91)
#define FLAG_WORLD_MAP_RHODANZI_CITY                                (SYS_FLAGS + 0x92)
#define FLAG_WORLD_MAP_CERULEAN_CITY                                (SYS_FLAGS + 0x93)
#define FLAG_WORLD_MAP_LAVENDER_TOWN                                (SYS_FLAGS + 0x94)
#define FLAG_WORLD_MAP_VERMILION_CITY                               (SYS_FLAGS + 0x95)
#define FLAG_WORLD_MAP_CELADON_CITY                                 (SYS_FLAGS + 0x96)
#define FLAG_WORLD_MAP_FUCHSIA_CITY                                 (SYS_FLAGS + 0x97)
#define FLAG_WORLD_MAP_CINNABAR_ISLAND                              (SYS_FLAGS + 0x98)
#define FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR                      (SYS_FLAGS + 0x99)
#define FLAG_WORLD_MAP_SAFFRON_CITY                                 (SYS_FLAGS + 0x9A)
#define FLAG_WORLD_MAP_ONE_ISLAND                                   (SYS_FLAGS + 0x9B)
#define FLAG_WORLD_MAP_TWO_ISLAND                                   (SYS_FLAGS + 0x9C)
#define FLAG_WORLD_MAP_THREE_ISLAND                                 (SYS_FLAGS + 0x9D)
#define FLAG_WORLD_MAP_FOUR_ISLAND                                  (SYS_FLAGS + 0x9E)
#define FLAG_WORLD_MAP_FIVE_ISLAND                                  (SYS_FLAGS + 0x9F)
#define FLAG_WORLD_MAP_SEVEN_ISLAND                                 (SYS_FLAGS + 0xA0)
#define FLAG_WORLD_MAP_SIX_ISLAND                                   (SYS_FLAGS + 0xA1)
#define FLAG_WORLD_MAP_ROUTE13_REST_HOUSE                           (SYS_FLAGS + 0xA2)
#define FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F                    (SYS_FLAGS + 0xA3)
#define FLAG_WORLD_MAP_VARISI_FOREST                                (SYS_FLAGS + 0xA4)
#define FLAG_WORLD_MAP_MT_MOON_1F                                   (SYS_FLAGS + 0xA5)
#define FLAG_WORLD_MAP_SSANNE_EXTERIOR                              (SYS_FLAGS + 0xA6)
#define FLAG_WORLD_MAP_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL          (SYS_FLAGS + 0xA7)
#define FLAG_WORLD_MAP_UNDERGROUND_PATH_EAST_WEST_TUNNEL            (SYS_FLAGS + 0xA8)
#define FLAG_WORLD_MAP_DIGLETTS_CAVE_B1F                            (SYS_FLAGS + 0xA9)
#define FLAG_WORLD_MAP_VICTORY_ROAD_1F                              (SYS_FLAGS + 0xAA)
#define FLAG_WORLD_MAP_ROCKET_HIDEOUT_B1F                           (SYS_FLAGS + 0xAB)
#define FLAG_WORLD_MAP_SILPH_CO_1F                                  (SYS_FLAGS + 0xAC)
#define FLAG_WORLD_MAP_POKEMON_MANSION_1F                           (SYS_FLAGS + 0xAD)
#define FLAG_WORLD_MAP_SAFARI_ZONE_CENTER                           (SYS_FLAGS + 0xAE)
#define FLAG_WORLD_MAP_POKEMON_LEAGUE_LORELEIS_ROOM                 (SYS_FLAGS + 0xAF)
#define FLAG_WORLD_MAP_ROCK_TUNNEL_1F                               (SYS_FLAGS + 0xB0)
#define FLAG_WORLD_MAP_SEAFOAM_ISLANDS_1F                           (SYS_FLAGS + 0xB1)
#define FLAG_WORLD_MAP_POKEMON_TOWER_1F                             (SYS_FLAGS + 0xB2)
#define FLAG_WORLD_MAP_CERULEAN_CAVE_1F                             (SYS_FLAGS + 0xB3)
#define FLAG_WORLD_MAP_POWER_PLANT                                  (SYS_FLAGS + 0xB4)
#define FLAG_WORLD_MAP_NAVEL_ROCK_EXTERIOR                          (SYS_FLAGS + 0xB5)
#define FLAG_WORLD_MAP_MT_EMBER_EXTERIOR                            (SYS_FLAGS + 0xB6)
#define FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST                    (SYS_FLAGS + 0xB7)
#define FLAG_WORLD_MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE            (SYS_FLAGS + 0xB8)
#define FLAG_WORLD_MAP_FIVE_ISLAND_ROCKET_WAREHOUSE                 (SYS_FLAGS + 0xB9)
#define FLAG_WORLD_MAP_SEVEN_ISLAND_TRAINER_TOWER_LOBBY             (SYS_FLAGS + 0xBA)
#define FLAG_WORLD_MAP_SIX_ISLAND_DOTTED_HOLE_1F                    (SYS_FLAGS + 0xBB)
#define FLAG_WORLD_MAP_FIVE_ISLAND_LOST_CAVE_ENTRANCE               (SYS_FLAGS + 0xBC)
#define FLAG_WORLD_MAP_SIX_ISLAND_PATTERN_BUSH                      (SYS_FLAGS + 0xBD)
#define FLAG_WORLD_MAP_SIX_ISLAND_ALTERING_CAVE                     (SYS_FLAGS + 0xBE)
#define FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER     (SYS_FLAGS + 0xBF)
#define FLAG_WORLD_MAP_THREE_ISLAND_DUNSPARCE_TUNNEL                (SYS_FLAGS + 0xC0)
#define FLAG_WORLD_MAP_SEVEN_ISLAND_SEVAULT_CANYON_TANOBY_KEY       (SYS_FLAGS + 0xC1)
#define FLAG_WORLD_MAP_BIRTH_ISLAND_EXTERIOR                        (SYS_FLAGS + 0xC2)
*/

#define FLAG_0x8D5 (SYS_FLAGS + 0xD5)
#define FLAG_0x8D6 (SYS_FLAGS + 0xD6)

#define FLAG_0x8E0 (SYS_FLAGS + 0xE0)

// SPECIAL FLAGS (unknown purpose)
#define SPECIAL_FLAGS_START 0x4000
#define SPECIAL_FLAGS_COUNT 16
#define FLAG_HIDE_MAP_NAME_POPUP        0x4000
#define FLAG_DONT_TRANSITION_MUSIC      0x4001
#define FLAG_SPECIAL_FLAG_0x4002        0x4002
#define FLAG_SPECIAL_FLAG_0x4003        0x4003
#define FLAG_SPECIAL_FLAG_0x4004        0x4004
