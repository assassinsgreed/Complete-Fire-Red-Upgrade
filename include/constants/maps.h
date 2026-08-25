#pragma once

#include "../../src/config.h"

#define MAP_NONE (0x7F | (0x7F << 8))
#define MAP_UNDEFINED (0xFF | (0xFF << 8))

#define MAP_GROUP(map) (MAP_##map >> 8)
#define MAP_NUM(map) (MAP_##map & 0xFF)
#define MAP_IS(map) (gSaveBlock1->location.mapGroup == MAP_GROUP(map) && gSaveBlock1->location.mapNum == MAP_NUM(map))

#define MAP(map) MAP_GROUP(map), MAP_NUM(map)

#ifndef UNBOUND //For FireRed

// Map Group 0
#define MAP_UNKNOWN_MAP_00_00 (0 | (0 << 8))
#define MAP_UNKNOWN_MAP_00_01 (1 | (0 << 8))
#define MAP_UNKNOWN_MAP_00_02 (2 | (0 << 8))
#define MAP_UNKNOWN_MAP_00_03 (3 | (0 << 8))
#define MAP_UNKNOWN_MAP_00_04 (4 | (0 << 8))

// Map Group 1
#define MAP_VARISI_FOREST                        (0 | (1 << 8))
#define MAP_RUBARR_DESERT                        (1 | (1 << 8))
#define MAP_RUBARR_DESERT_B2F                    (3 | (1 << 8))
#define MAP_TORMA_CAVE_B1F                       (4 | (1 << 8))
#define MAP_TORMA_CAVE_B2F                       (5 | (1 << 8))
#define MAP_HELEO_RANCH_EXTERIOR                 (6 | (1 << 8))
#define MAP_HELEO_RANCH_INTERIOR                 (7 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_TUNNEL               (8 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_EXTERIOR             (9 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_1F                   (10 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_2F                   (11 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_BASEMENT             (12 | (1 << 8))
#define MAP_FORGOTTEN_MANSE_CLOSET               (28 | (1 << 8))
#define MAP_DAIMYN_CITY_FACTORY                  (30 | (1 << 8))
#define MAP_ROUTE10_CAVE                         (31 | (1 << 8))
#define MAP_SEPPIRE_COVE_1F                      (34 | (1 << 8))
#define MAP_LAKE_LAPLAZ                          (37 | (1 << 8))
#define MAP_PERADON_FOREST_GUARD_HOUSE           (39 | (1 << 8))
#define MAP_PERADON_FOREST_NORTH                 (40 | (1 << 8))
#define MAP_PERADON_FOREST_SOUTH                 (41 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_EXTERIOR          (42 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_F1                (43 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_VOLCANION_ROOM    (44 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_F2                (45 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_F3                (46 | (1 << 8))
#define MAP_PLUTO_HQ_B1F                         (47 | (1 << 8))
#define MAP_PLUTO_HQ_B2F                         (48 | (1 << 8))
#define MAP_PLUTO_HQ_B3F                         (49 | (1 << 8))
#define MAP_PLUTO_HQ_B4F                         (50 | (1 << 8))
#define MAP_PLUTO_HQ_B5F                         (51 | (1 << 8))
#define MAP_PLUTO_HQ_B6F                         (52 | (1 << 8))
#define MAP_PLUTO_HQ_B7F                         (53 | (1 << 8))
#define MAP_PLUTO_HQ_B1F_HALL                    (54 | (1 << 8))
#define MAP_PLUTO_HQ_KURTIS_OFFICE               (55 | (1 << 8))
#define MAP_PLUTO_HQ_IRENE_OFFICE                (56 | (1 << 8))
#define MAP_PLUTO_HQ_RONALD_OFFICE               (57 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_PEAK              (58 | (1 << 8))
#define MAP_ORICHELLE_GARDEN                     (59 | (1 << 8))
#define MAP_SEPPIRE_COVE_OVERWORLD               (60 | (1 << 8))
#define MAP_SEPPIRE_COVE_B2F                     (61 | (1 << 8))
#define MAP_SEPPIRE_COVE_B1F                     (62 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_CENTER                (63 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_SOUTH                 (64 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_EAST                  (65 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_NORTHWEST             (66 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_NORTH                 (67 | (1 << 8))
#define MAP_MIMMETT_JUNGLE_ZERAORA_ROOM          (71 | (1 << 8))
#define MAP_SEPPIRE_COVE_SIDE_ROOM               (72 | (1 << 8))
#define MAP_SEPPIRE_COVE_KYOGRE_ROOM             (73 | (1 << 8))
#define MAP_CARNELIDGE_VOLCANO_BF1               (74 | (1 << 8))
#define MAP_ASCENSION_TOWER_HANNAHS_ROOM         (75 | (1 << 8))
#define MAP_ASCENSION_TOWER_LUCASS_ROOM          (76 | (1 << 8))
#define MAP_ASCENSION_TOWER_JENNAS_ROOM          (77 | (1 << 8))
#define MAP_ASCENSION_TOWER_THOMAS_ROOM          (78 | (1 << 8))
#define MAP_ASCENSION_TOWER_CHAMPIONS_ROOM       (79 | (1 << 8))
#define MAP_ASCENSION_TOWER_HALL_OF_FAME         (80 | (1 << 8))
#define MAP_HESSON_PASS_1F                       (81 | (1 << 8))
#define MAP_HESSON_PASS_2F                       (82 | (1 << 8))
#define MAP_HESSON_PASS_B1F                      (83 | (1 << 8))
#define MAP_CALICIN_BAY                          (84 | (1 << 8))
#define MAP_UTEYAN_RUINS_OVERWORLD               (85 | (1 << 8))
#define MAP_UTEYAN_RUINS_CAVE_1F                 (86 | (1 << 8))
#define MAP_UTEYAN_RUINS_CAVE_2F                 (87 | (1 << 8))
#define MAP_HELEO_CITY_SWARM_HOUSE               (88 | (1 << 8))
#define MAP_HELEO_CITY_FOREMAN_HOUSE             (89 | (1 << 8))
#define MAP_HELEO_CITY_POKEMON_FAN_CLUB          (90 | (1 << 8))
#define MAP_HELEO_CITY_POKEMON_FAN_CLUB_ROOF     (91 | (1 << 8))
#define MAP_HELEO_CITY_GYM_FLOODED               (92 | (1 << 8))
#define MAP_HELEO_CITY_GYM_DRAINED               (93 | (1 << 8))
#define MAP_HELEO_CITY_TRAINER_HOUSE             (94 | (1 << 8))
#define MAP_DAIMYN_FACTORY_INTERIOR              (95 | (1 << 8))
#define MAP_VICTORY_ROAD_1F                      (96 | (1 << 8))
#define MAP_VICTORY_ROAD_2F                      (97 | (1 << 8))
#define MAP_VICTORY_ROAD_3F                      (98 | (1 << 8))
#define MAP_VICTORY_ROAD_OUTSIDE                 (99 | (1 << 8))
#define MAP_VICTORY_ROAD_BACK_ROOM               (100 | (1 << 8))
#define MAP_VICTORY_ROAD_PEAK                    (101 | (1 << 8))
#define MAP_UTEYAN_RUINS_CHAMBER_1               (102 | (1 << 8))
#define MAP_UTEYAN_RUINS_CHAMBER_2               (103 | (1 << 8))
#define MAP_UTEYAN_RUINS_CHAMBER_3               (104 | (1 << 8))
#define MAP_UTEYAN_RUINS_CHAMBER_4               (105 | (1 << 8))
#define MAP_UTEYAN_RUINS_CHAMBER_5               (106 | (1 << 8))
#define MAP_ASCENSION_TOWER_ELEVATOR             (107 | (1 << 8))
#define MAP_RUBARR_DESERT_CONNECTING_ROOMS       (114 | (1 << 8))
#define MAP_RUBARR_DESERT_B1F                    (123 | (1 << 8))
#define MAP_ROUTE18_CAVE                         (124 | (1 << 8))
#define MAP_ROUTE13_CAVE_1F                      (125 | (1 << 8))
#define MAP_ROUTE13_CAVE_B1F                     (126 | (1 << 8))

// Map Group 2
#define MAP_TSARVOSA_CITY_GYM_TRAINEE_HOUSE           (0 | (2 << 8))
#define MAP_TSARVOSA_CITY_NPC_HOUSE_1                 (1 | (2 << 8))
#define MAP_TSARVOSA_CITY_NPC_HOUSE_2                 (2 | (2 << 8))
#define MAP_TSARVOSA_CITY_NPC_HOUSE_3                 (3 | (2 << 8))
#define MAP_TSARVOSA_CITY_NPC_HOUSE_4                 (4 | (2 << 8))
#define MAP_TSARVOSA_CITY_NPC_HOUSE5                  (5 | (2 << 8))
#define MAP_ASCENSION_TOWER_LOBBY                     (10 | (2 << 8))
#define MAP_EMPTY_WORLD_CARNELIDGE_VOLCANO_PEAK       (12 | (2 << 8))
#define MAP_EMPTY_WORLD_CARNELIDGE_VOLCANO            (13 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_13                      (14 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_13_REST_HOUSE           (15 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_4                       (16 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE                (17 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_11_SOUTH                (18 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_10                      (19 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_10_GUARDHOUSE           (20 | (2 << 8))
#define MAP_EMPTY_WORLD_DAIMYN_CITY                   (21 | (2 << 8))
#define MAP_EMPTY_WORLD_ROUTE_11_SOUTH_REFINER_HOUSE  (22 | (2 << 8))
#define MAP_EMPTY_WORLD_IDF                           (23 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_BERRY_HOUSE    (24 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_POKEMART       (25 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_CHINCHOU_HOUSE (26 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_GYM            (27 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_POKEMON_CENTER (28 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_TUTOR_HOUSE    (29 | (2 << 8))
#define MAP_EMPTY_WORLD_FERROX_VILLAGE_LIBRARY        (30 | (2 << 8))
#define MAP_ULTRA_SPACE_LANDING_PLACE                 (31 | (2 << 8))
#define MAP_ULTRA_SPACE_ECLIPSE_VILLAGE               (32 | (2 << 8))
#define MAP_ULTRA_SPACE_ECLIPSE_VILLAGE_NPC_HOUSE_1   (33 | (2 << 8))
#define MAP_ULTRA_SPACE_ECLIPSE_VILLAGE_NPC_HOUSE_2   (34 | (2 << 8))
#define MAP_ULTRA_SPACE_ECLIPSE_VILLAGE_NPC_HOUSE_3   (35 | (2 << 8))
#define MAP_ULTRA_SPACE_ECLIPSE_VILLAGE_BIKE_SHOP     (36 | (2 << 8))
#define MAP_ULTRA_SPACE_WILDS                         (37 | (2 << 8))
#define MAP_ULTRA_SPACE_ALTAR_OF_ECLIPSE              (38 | (2 << 8))
#define MAP_ULTRA_SPACE_HOENN                         (39 | (2 << 8))
#define MAP_ULTRA_SPACE_DAIS_OF_LIGHT                 (40 | (2 << 8))
#define MAP_ROUTE13_CAVE_KURTIS_ROOM                  (60 | (2 << 8))
#define MAP_ROUTE13_CAVE_B2F                          (61 | (2 << 8))

// Map Group 3
#define MAP_ANTHRA_TOWN                          (0 | (3 << 8))
#define MAP_OLENIC_TOWN                          (1 | (3 << 8))
#define MAP_RHODANZI_CITY                        (2 | (3 << 8))
#define MAP_FERROX_VILLAGE                       (3 | (3 << 8))
#define MAP_HELEO_CITY                           (4 | (3 << 8))
#define MAP_DAIMYN_CITY                          (5 | (3 << 8))
#define MAP_LAPLAZ_TOWN                          (6 | (3 << 8))
#define MAP_BRUCCIE_VILLAGE                      (7 | (3 << 8))
#define MAP_EMRALDIN_QUAY                        (8 | (3 << 8))
#define MAP_TSARVOSA_CITY                        (9 | (3 << 8))
#define MAP_UTEYA_VILLAGE                        (10 | (3 << 8))
#define MAP_ROUTE_12_WEST                        (11 | (3 << 8))
#define MAP_ROUTE_1                              ((3 << 8) | 19)
#define MAP_ROUTE_2                              ((3 << 8) | 20)
#define MAP_ROUTE_3                              ((3 << 8) | 21)
#define MAP_ROUTE_4                              ((3 << 8) | 22)
#define MAP_ROUTE_5                              ((3 << 8) | 23)
#define MAP_ROUTE_6                              ((3 << 8) | 24)
#define MAP_ROUTE_7                              ((3 << 8) | 25)
#define MAP_ROUTE_8                              ((3 << 8) | 26)
#define MAP_ROUTE_9                              ((3 << 8) | 27)
#define MAP_ROUTE_10                             ((3 << 8) | 28)
#define MAP_ROUTE_11_SOUTH                       ((3 << 8) | 29)
#define MAP_ROUTE_12_EAST                        ((3 << 8) | 30)
#define MAP_ROUTE_13                             ((3 << 8) | 31)
#define MAP_ROUTE_14                             ((3 << 8) | 32)
#define MAP_ROUTE_15_NORTH                       ((3 << 8) | 33)
#define MAP_ROUTE_16                             ((3 << 8) | 34)
#define MAP_ROUTE_17                             ((3 << 8) | 35)
#define MAP_ROUTE_18                             ((3 << 8) | 36)
#define MAP_ROUTE_19                             ((3 << 8) | 37)
#define MAP_ROUTE_20                             ((3 << 8) | 38)
#define MAP_ROUTE_21                             ((3 << 8) | 39)
#define MAP_SECRET_PATH                          ((3 << 8) | 40)
#define MAP_ROUTE_22                             ((3 << 8) | 41)
#define MAP_ROUTE_23                             ((3 << 8) | 42)
#define MAP_ROUTE_24                             ((3 << 8) | 43)
// #define MAP_UNUSED                               ((3 << 8) | 44) // Currently Route 24 in binary
#define MAP_TREASURE_BEACH                       ((3 << 8) | 46)
#define MAP_PROFESSORS_CONSERVATORY_GRASS_AREA   ((3 << 8) | 47)
#define MAP_PROFESSORS_CONSERVATORY_FIRE_AREA    ((3 << 8) | 48)
#define MAP_PROFESSORS_CONSERVATORY_WATER_AREA   ((3 << 8) | 49)
#define MAP_ROUTE_11_NORTH                       ((3 << 8) | 54)
#define MAP_ROUTE_15_SOUTH                       ((3 << 8) | 66)

// Map Group 4
#define MAP_PALLET_TOWN_PLAYERS_HOUSE_1F   (0 | (4 << 8))
#define MAP_PALLET_TOWN_PLAYERS_HOUSE_2F   (1 | (4 << 8))
#define MAP_PALLET_TOWN_RIVALS_HOUSE       (2 | (4 << 8))
#define MAP_PALLET_TOWN_OLD_MANS_HOUSE     (3 | (4 << 8))

// Map Group 5
#define MAP_OLENIC_TOWN_HOUSE1            (0 | (5 << 8))
#define MAP_OLENIC_TOWN_HOUSE2            (1 | (5 << 8))
#define MAP_OLENIC_TOWN_HOUSE3            (2 | (5 << 8))
#define MAP_OLENIC_TOWN_POKEMART          (6 | (5 << 8))
#define MAP_OLENIC_TOWN_HAWTHORNES_LAB    (7 | (5 << 8))
#define MAP_OLENIC_TOWN_HOUSE4            (8 | (5 << 8))
#define MAP_OLENIC_TOWN_HOUSE3_UPSTAIRS   (9 | (5 << 8))

// Map Group 6
#define MAP_RHODANZI_CITY_TRAINER_SCHOOL          (0 | (6 << 8))
#define MAP_RHODANZI_CITY_TRAINER_SCHOOL_BASIC    (1 | (6 << 8))
#define MAP_RHODANZI_CITY_TRAINER_SCHOOL_ADVANCED (2 | (6 << 8))
#define MAP_RHODANZI_CITY_FISHERMAN_HOUSE         (4 | (6 << 8))
#define MAP_RHODANZI_CITY_TERRENCES_HOUSE         (7 | (6 << 8))
#define MAP_RHODANZI_CITY_HOUSE1                  (8 | (6 << 8))
#define MAP_RHODANZI_CITY_HOUSE2                  (9 | (6 << 8))
#define MAP_RHODANZI_CITY_HOUSE3                  (10 | (6 << 8))
#define MAP_RHODANZI_CITY_HOUSE4                  (13 | (6 << 8))
#define MAP_RHODANZI_CITY_POKEMART                (14 | (6 << 8))
#define MAP_RHODANZI_CITY_POKEMON_CENTER          (15 | (6 << 8))
#define MAP_RHODANZI_CITY_GYM                     (16 | (6 << 8))
#define MAP_RHODANZI_CITY_HOUSE5                  (17 | (6 << 8))

// Map Group 7
#define MAP_FERROX_VILLAGE_HOUSE1            (0 | (7 << 8))
#define MAP_FERROX_VILLAGE_HOUSE2            (1 | (7 << 8))
#define MAP_FERROX_VILLAGE_GYM               (5 | (7 << 8))
#define MAP_FERROX_VILLAGE_MART              (6 | (7 << 8))
#define MAP_FERROX_VILLAGE_LIBRARY           (9 | (7 << 8))
#define MAP_FERROX_VILLAGE_HOUSE3            (10 | (7 << 8))
#define MAP_FERROX_VILLAGE_POKEMON_CENTER    (11 | (7 << 8))

// Map Group 8
#define MAP_HELEO_CITY_HOUSE1                  (1 | (8 << 8))
#define MAP_HELEO_CITY_POKEMON_CENTER          (2 | (8 << 8))
#define MAP_HELEO_CITY_OLD_MAN_HOUSE           (5 | (8 << 8))
#define MAP_HELEO_CITY_TUTOR_HOUSE             (6 | (8 << 8))
#define MAP_HELEO_CITY_MART                    (7 | (8 << 8))

// Map Group 9
#define MAP_DAIMYN_CITY_GUARDE_HOUSE_WEST    (3 | (9 << 8))
#define MAP_DAIMYN_CITY_GUARD_HOUSE_SOUTH    (6 | (9 << 8))
#define MAP_DAIMYN_RESTAURANT                (8 | (9 << 8))
#define MAP_DAIMYN_CITY_POKEMON_CENTER       (9 | (9 << 8))
#define MAP_DAIMYN_CITY_PLUTO_HQ             (10 | (9 << 8))
#define MAP_DAIMYN_CITY_LANAS_HOUSE          (11 | (9 << 8))
#define MAP_DAIMYN_CITY_ASHS_HOUSE           (12 | (9 << 8))
#define MAP_DAIMYN_CITY_TUTORS_HOUSE         (13 | (9 << 8))
#define MAP_DAIMYN_CITY_MOVE_DELETER_REMIND  (14 | (9 << 8))
#define MAP_DAIMYN_CITY_TRADE_HOUSE          (15 | (9 << 8))
#define MAP_DAIMYN_CITY_MALL                 (16 | (9 << 8))
#define MAP_DAIMYN_CITY_IDF                  (17 | (9 << 8))
#define MAP_DAIMYN_CITY_GYM                  (18 | (9 << 8))
#define MAP_DAIMYN_CITY_GUARD_HOUSE_EAST     (19 | (9 << 8))
#define MAP_DAIMYN_CITY_GUARD_HOUSE_NORTH    (20 | (9 << 8))

// Map Group 10
#define MAP_LAPLAZ_TOWN_MART                        (1 | (10 << 8))
#define MAP_LAPLAZ_TOWN_TRAINER_HOUSE               (2 | (10 << 8))
#define MAP_LAPLAZ_TOWN_CASEYS_HOUSE                (3 | (10 << 8))
#define MAP_LAPLAZ_TOWN_APRICORN_BALL_SHOP          (4 | (10 << 8))
#define MAP_LAPLAZ_TOWN_HOUSE1                      (5 | (10 << 8))
#define MAP_LAPLAZ_TOWN_HOUSE2                      (6 | (10 << 8))
#define MAP_LAPLAZ_TOWN_PSYCHIC_HOUSE               (7 | (10 << 8))
#define MAP_LAPLAZ_TOWN_GYM                         (8 | (10 << 8))
#define MAP_EMRALDIN_QUAY_POKEMON_CENTER            (9 | (10 << 8))
#define MAP_EMRALDIN_QUAY_HOUSE1                   (10 | (10 << 8))
#define MAP_EMRALDIN_QUAY_HOUSE2                   (11 | (10 << 8))
#define MAP_EMRALDIN_QUAY_TRAINER_HOUSE            (14 | (10 << 8))
#define MAP_ROUTE_23_FISHERMANS_HOUSE              (15 | (10 << 8))
#define MAP_ROUTE_23_CAVE                          (16 | (10 << 8))
#define MAP_ROUTE_20_CAVE                          (17 | (10 << 8))
#define MAP_TSARVOSA_CITY_HOUSE                    (19 | (10 << 8))
#define MAP_LAPLAZ_TOWN_POKEMON_CENTER             (20 | (10 << 8))

// Map Group 11
#define MAP_BRUCCIE_VILLAGE_POKEMON_CENTER   (0 | (11 << 8))
#define MAP_BRUCCIE_VILLAGE_MART             (2 | (11 << 8))
#define MAP_BRUCCIE_VILLAGE_GYM              (3 | (11 << 8))
#define MAP_BRUCCIE_VILLAGE_HOUSE1           (7 | (11 << 8))
#define MAP_BRUCCIE_VILLAGE_HOUSE2           (8 | (11 << 8))

// Map Group 12
#define MAP_TSARVOSA_CITY_POKEMON_CENTER     (0 | (12 << 8))
#define MAP_TSARVOSA_CITY_STATS_DOJO         (1 | (12 << 8))
#define MAP_TSARVOSA_CITY_HOUSE1             (2 | (12 << 8))
#define MAP_TSARVOSA_CITY_HOUSE2             (3 | (12 << 8))
#define MAP_TSARVOSA_CITY_HOUSE3             (4 | (12 << 8))

// Map Group 13 (Unused)

// Map Group 14
#define MAP_UTEYA_VILLAGE_POKEMON_CENTER  (0 | (14 << 8))
#define MAP_UTEYA_VILLAGE_MART            (1 | (14 << 8))
#define MAP_UTEYA_VILLAGE_HOUSE1          (2 | (14 << 8))
#define MAP_UTEYA_VILLAGE_HOUSE2          (3 | (14 << 8))
#define MAP_UTEYA_VILLAGE_TRAINER_HOUSE   (5 | (14 << 8))
#define MAP_UTEYA_VILLAGE_GYM             (9 | (14 << 8))

// Map Group 15
#define MAP_ROUTE2_VARISI_FOREST_SOUTH_ENTRANCE     (0 | (15 << 8))
#define MAP_ROUTE2_VARISI_FOREST_SOUTHEAST_ENTRANCE (2 | (15 << 8))
#define MAP_ROUTE2_VARISI_FOREST_NORTH_ENTRANCE     (3 | (15 << 8))

// Map Group 16 (Not used)

// Map Group 17
#define MAP_ROUTE5_POKEMON_DAY_CARE (0 | (17 << 8))
#define MAP_ROUTE13_REST_HOUSE      (1 | (17 << 8))

// Map Group 18 (Not used)

// Map Group 19
#define MAP_ROUTE9_FLUTIST_HOUSE (0 | (19 << 8))

// Map Group 20
#define MAP_ROUTE11_MEGA_STONE_REFINERS_HOUSE (0 | (20 << 8))

// Map Group 21 (Not used)

// Map Group 22
#define MAP_ROUTE12_REST_HOUSE (0 | (22 << 8))

// Map Group 23
#define MAP_ROUTE12_SCALDING_SPA_SPA_ROOM           (0 | (23 << 8))
#define MAP_ROUTE12_SCALDING_SPA_BACK_ROOM          (1 | (23 << 8))
#define MAP_ROUTE12_SCALDING_SPA_GLASTRIER_HALL     (2 | (23 << 8))
#define MAP_ROUTE12_SCALDING_SPA_GLASTRIER_ROOM     (3 | (23 << 8))

// Map Group 24 (Not used)

// Map Group 25
#define MAP_HELEO_CITY_GUARDHOUSE_1F (0 | (25 << 8))
#define MAP_ROUTE8_FISHERMANS_HOUSE  (1 | (25 << 8))
#define MAP_HELEO_CITY_GUARDHOUSE_2F (2 | (25 << 8))

// Map Group 26 (Not used)

// Map Group 27 (Not used)

// Map Group 28
#define MAP_ROUTE22_DRAGON_MASTER_HOUSE (0 | (28 << 8))

// Map Group 29 (Not used)

// Map Group 30
#define MAP_ROUTE17_CAVE_1F             (0 | (30 << 8))
#define MAP_ROUTE17_CAVE_1F_BACK_ROOM   (1 | (30 << 8))
#define MAP_ROUTE17_CAVE_B1F            (2 | (30 << 8))
#define MAP_ROUTE18_CARETAKER_HOUSE     (3 | (30 << 8))

// Map Group 31
#define MAP_CREDITS_DAIMYN_CITY (0 | (31 << 8))
#define MAP_CREDITS_ROUTE_6     (1 | (31 << 8))
#define MAP_CREDITS_ROUTE_7     (3 | (31 << 8))
#define MAP_CREDITS_ANTHRA_TOWN (6 | (31 << 8))
#define MAP_CREDITS_HELEO_CITY  (7 | (31 << 8))
#define MAP_CREDITS_RHODANZI_CITY (8 | (31 << 8))
#define MAP_CREDITS_VARISI_FOREST (9 | (31 << 8))

// Map Group 32 (Not used)

// Map Group 33 (Not used)

// Map Group 34 (Not used)

// Map Group 35 (Not used)

// Map Group 36 (Not used)

// Map Group 37 (Not used)

// Map Group 38 (Not used)

// Map Group 39 (Not used)

// Map Group 40 (Not used)

// Map Group 41 (Not used)

// Map Group 42 (Not used)

#define MAP_GROUPS_COUNT 43

#else //For Pokemon Unbound

//West Borrius
#define MAP_FROZEN_HEIGHTS         ((3 << 8) | 66)
#define MAP_ROUTE_1                ((3 << 8) | 67)
#define MAP_BELLIN_TOWN            ((3 << 8) | 68)
#define MAP_ROUTE_2                ((3 << 8) | 69)
#define MAP_ROUTE_3                ((3 << 8) | 70)
#define MAP_DRESCO_TOWN            ((3 << 8) | 71)
#define MAP_ROUTE_4                ((3 << 8) | 72)
#define MAP_GRIM_WOODS             ((45 << 8) | 1)
#define MAP_ROUTE_5                ((3 << 8) | 73)
#define MAP_CRATER_TOWN            ((3 << 8) | 74)
#define MAP_POKEMON_DAY_CARE       ((1 << 8) | 94)
#define MAP_ROUTE_6                ((3 << 8) | 75)
#define MAP_ROUTE_7                ((3 << 8) | 76)
#define MAP_ROUTE_8                ((3 << 8) | 77)
#define MAP_BLIZZARD_CITY          ((3 << 8) | 78)
#define MAP_FROZEN_FOREST          ((1 << 8) | 81)
#define MAP_ROUTE_9                ((3 << 8) | 79)
#define MAP_TEHL_TOWN              ((3 << 8) | 80)
#define MAP_ROUTE_10               ((3 << 8) | 81)
#define MAP_AUBURN_WATERWAY_A      ((3 << 8) | 82)
#define MAP_AUBURN_WATERWAY_B      ((3 << 8) | 83)
#define MAP_FALLSHORE_CITY         ((3 << 8) | 84)
#define MAP_ROUTE_11               ((3 << 8) | 85)
#define MAP_EPIDIMY_TOWN           ((3 << 8) | 86)
#define MAP_TARMIGAN_TOWN          ((3 << 8) | 87)
#define MAP_ROUTE_12               ((3 << 8) | 88)
#define MAP_DEHARA_CITY            ((3 << 8) | 89)
#define MAP_RUINS_OF_VOID_EXT      ((1 << 8) | 109)
#define MAP_GREAT_DESERT_A         ((3 << 8) | 90)
#define MAP_GREAT_DESERT_B         ((3 << 8) | 91)
#define MAP_GREAT_DESERT_C         ((3 << 8) | 92)
#define MAP_ROUTE_13_A             ((3 << 8) | 93)
#define MAP_ROUTE_13_B             ((3 << 8) | 94)
#define MAP_ROUTE_14_A             ((3 << 8) | 95)
#define MAP_ROUTE_14_B             ((3 << 8) | 96)
#define MAP_ROUTE_14_C             ((3 << 8) | 97)
#define MAP_GURUN_TOWN             ((3 << 8) | 98)
#define MAP_VIVILL_WOODS           ((1 << 8) | 99)
#define MAP_VIVILL_TOWN            ((3 << 8) | 99)
#define MAP_ROUTE_15               ((3 << 8) | 100)
#define MAP_ROUTE_16               ((3 << 8) | 101)
#define MAP_ANTISIS_CITY           ((3 << 8) | 102)
#define MAP_THUNDERCAP_MT_EXT      ((3 << 8) | 103)
#define MAP_ROUTE_17               ((3 << 8) | 104)
#define MAP_SEAPORT_CITY           ((3 << 8) | 105)
#define MAP_BATTLE_FRONTIER        ((3 << 8) | 3)
#define MAP_ROUTE_18_A             ((3 << 8) | 106)
#define MAP_ROUTE_18_B             ((3 << 8) | 107)
#define MAP_POKEMON_LEAGUE         ((3 << 8) | 108)

#define MAP_FLOWER_PARADISE_A      ((1 << 8) | 4)
#define MAP_FLOWER_PARADISE_B      ((1 << 8) | 5)
#define MAP_FLOWER_PARADISE_C      ((1 << 8) | 6)

#define MAP_HIDDEN_GROTTO          ((1 << 8) | 7)
#define MAP_HIDDEN_GROTTO_WINTER   ((1 << 8) | 8)
#define MAP_HIDDEN_GROTTO_AUTUMN   ((1 << 8) | 9)

//East Borrius
#define MAP_POLDER_TOWN            ((3 << 8) | 0)
#define MAP_COOTES_BOG             ((3 << 8) | 1)
#define MAP_MAGNOLIA_TOWN          ((3 << 8) | 2)
#define MAP_MAGNOLIA_FIELDS        ((3 << 8) | 4)
#define MAP_REDWOOD_VILLAGE        ((3 << 8) | 5)
#define MAP_REDWOOD_FOREST         ((1 << 8) | 98)
#define MAP_CUBE_CORP              ((3 << 8) | 6)

#define MAP_FULLMOON_ISLAND_A      ((1 << 8) | 0)
#define MAP_FULLMOON_ISLAND_B      ((1 << 8) | 1)
#define MAP_NEWMOON_ISLAND_A       ((1 << 8) | 2)
#define MAP_NEWMOON_ISLAND_B       ((1 << 8) | 3)

//Dungeons
#define MAP_ICICLE_CAVE_1F             ((43 << 8) | 0)
#define MAP_ICICLE_CAVE_B1F            ((43 << 8) | 1)
#define MAP_ICICLE_CAVE_B2F            ((43 << 8) | 2)
#define MAP_ICICLE_CAVE_B3F            ((43 << 8) | 3)
#define MAP_ICICLE_CAVE_B3F_ALT        ((43 << 8) | 4)
#define MAP_ICICLE_CAVE_1F_BACK        ((43 << 8) | 5)
#define MAP_ICICLE_CAVE_CLEARING       ((43 << 8) | 6)
#define MAP_ICICLE_CAVE_B4F            ((43 << 8) | 7)
#define MAP_ICICLE_CAVE_RAID_DEN       ((1 << 8) | 28)

#define MAP_CINDER_VOLCANO_F1          ((45 << 8) | 3)
#define MAP_CINDER_VOLCANO_2F          ((45 << 8) | 4)
#define MAP_CINDER_VOLCANO_SHADOW_1F   ((6 << 8) | 12)
#define MAP_CINDER_VOLCANO_3F_1        ((1 << 8) | 46)
#define MAP_CINDER_VOLCANO_SUMMIT      ((1 << 8) | 47)
#define MAP_CINDER_VOLCANO_4F_2        ((1 << 8) | 50)
#define MAP_CINDER_VOLCANO_SHADOW_B1F  ((1 << 8) | 51)
#define MAP_CINDER_VOLCANO_SHADOW_B2F  ((1 << 8) | 52)
#define MAP_CINDER_VOLCANO_SHADOW_STORAGE_1 ((1 << 8) | 53)
#define MAP_CINDER_VOLCANO_SHADOW_STORAGE_2 ((1 << 8) | 54)

#define MAP_VALLEY_CAVE_A              ((47 << 8) | 0)
#define MAP_VALLEY_CAVE_B              ((47 << 8) | 1)
#define MAP_VALLEY_CAVE_C              ((47 << 8) | 2)
#define MAP_VALLEY_CAVE_D              ((47 << 8) | 3)

#define MAP_FROST_MOUNTAIN_1F          ((50 << 8) | 0)
#define MAP_FROST_MOUNTAIN_2F          ((50 << 8) | 1)
#define MAP_FROST_MOUNTAIN_3F          ((48 << 8) | 1)

#define MAP_AUTL_WOODS_WEST            ((1 << 8) | 119)
#define MAP_AUTL_WOODS_EAST            ((1 << 8) | 120)

#define MAP_LOST_TUNNEL_B1F            ((1 << 8) | 121)

#define MAP_CLIFF_CAVE_1F              ((52 << 8) | 0)
#define MAP_CLIFF_CAVE_2F              ((52 << 8) | 1)
#define MAP_CLIFF_CAVE_3F              ((52 << 8) | 2)

#define MAP_THUNDERCAP_MT_SUMMIT       ((53 << 8) | 0)
#define MAP_THUNDERCAP_MT_1F           ((53 << 8) | 1)
#define MAP_THUNDERCAP_MT_2F           ((53 << 8) | 2)
#define MAP_THUNDERCAP_MT_3F_3         ((53 << 8) | 3)
#define MAP_THUNDERCAP_MT_3F_2         ((53 << 8) | 4)
#define MAP_THUNDERCAP_MT_3F_1         ((53 << 8) | 5)
#define MAP_THUNDERCAP_MT_3F_1_BACK    ((53 << 8) | 6)
#define MAP_THUNDERCAP_MT_4F_2         ((53 << 8) | 9)
#define MAP_THUNDERCAP_MT_CLIFFSIDE    ((53 << 8) | 10)

#define MAP_RIFT_CAVE_B1F              ((1 << 8) | 35)

#define MAP_RUINS_OF_VOID_B3F          ((1 << 8) | 114)
#define MAP_RUINS_OF_VOID_B3F_ALT      ((1 << 8) | 107)
#define MAP_ROV_POST_GAME_AKLOVE       ((1 << 8) | 108)

#define MAP_DISTORTION_WORLD_1         ((1 << 8) | 63)
#define MAP_DISTORTION_WORLD_2         ((1 << 8) | 64)
#define MAP_DISTORTION_WORLD_3         ((1 << 8) | 65)
#define MAP_DISTORTION_WORLD_4         ((1 << 8) | 66)
#define MAP_DISTORTION_WORLD_5         ((1 << 8) | 67)

#define MAP_ICY_HOLE_1F                ((2 << 8) | 0)
#define MAP_ICY_HOLE_B1F               ((2 << 8) | 14)

#define MAP_TOMB_OF_BORRIUS_1F         ((1 << 8) | 83)
#define MAP_TOMB_OF_BORRIUS_B3F        ((1 << 8) | 85)
#define MAP_TOMB_OF_BORRIUS_1F_BACK    ((1 << 8) | 90)

#define MAP_CRYSTAL_PEAK_BOG_ENTRANCE  ((56 << 8) | 0)
#define MAP_CRYSTAL_PEAK_B1F_LEFT      ((56 << 8) | 1)
#define MAP_CRYSTAL_PEAK_1F_MAIN_ROOM  ((56 << 8) | 2)
#define MAP_CRYSTAL_PEAK_1F_LEFT_ROOM  ((56 << 8) | 3)
#define MAP_CRYSTAL_PEAK_CUBE_ENTRANCE ((56 << 8) | 6)
#define MAP_CRYSTAL_PEAK_CLIFFSIDE     ((56 << 8) | 7)
#define MAP_CRYSTAL_PEAK_3F            ((56 << 8) | 9)
#define MAP_CRYSTAL_PEAK_5F            ((56 << 8) | 11)
#define MAP_CRYSTAL_PEAK_SUMMIT        ((56 << 8) | 12)

#define MAP_VICTORY_ROAD_CAVE_A        ((55 << 8) | 0)
#define MAP_VICTORY_ROAD_CAVE_B        ((55 << 8) | 1)
#define MAP_VICTORY_ROAD_VOLCANO       ((55 << 8) | 2)
#define MAP_VICTORY_ROAD_CAVE_C        ((55 << 8) | 3)
#define MAP_VICTORY_ROAD_GRASSY        ((55 << 8) | 4)
#define MAP_VICTORY_ROAD_CAVE_D        ((55 << 8) | 5)
#define MAP_VICTORY_ROAD_MOUNTAINSIDE  ((55 << 8) | 6)
#define MAP_VICTORY_ROAD_ICE_CAVE_A    ((55 << 8) | 7)
#define MAP_VICTORY_ROAD_ICE_CAVE_B    ((55 << 8) | 8)

#define MAP_UNDERWATER_VIVILL_TOWN     ((32 << 8) | 4)
#define MAP_UNDERWATER_ROUTE_17        ((32 << 8) | 6)

//Interior
#define MAP_PLAYER_ROOM                          ((4 << 8) | 1)
#define MAP_BELLIN_TOWN_MART                     ((5 << 8) | 3)
#define MAP_ROUTE_9_HOUSE_2                      ((51 << 8) | 1)

#define MAP_MIRSKLE_LAB_UNDERWATER_1             ((7 << 8) | 10)
#define MAP_MIRSKLE_LAB_UNDERWATER_2             ((7 << 8) | 11)

#define MAP_SHADOW_WAREHOUSE                     ((4 << 8) | 10)
#define MAP_SHADOW_BASE_B3F                      ((1 << 8) | 45)

#define MAP_UNDERGROUND_PASS_A                   ((1 << 8) | 31)
#define MAP_UNDERGROUND_PASS_B                   ((1 << 8) | 32)

#define MAP_FALLSHORE_CITY_EVOLUTION_HOUSE_LOWER ((14 << 8) | 2)

#define MAP_FALLSHORE_CITY_GYM_B1F               ((14 << 8) | 15)
#define MAP_FALLSHORE_CITY_GYM_B2F               ((14 << 8) | 14)

#define MAP_DEHARA_DEPT_1F                       ((10 << 8) | 0)
#define MAP_DEHARA_DEPT_2F                       ((10 << 8) | 1)
#define MAP_DEHARA_DEPT_3F                       ((10 << 8) | 2)
#define MAP_DEHARA_DEPT_4F                       ((10 << 8) | 3)
#define MAP_DEHARA_DEPT_5F                       ((10 << 8) | 4)
#define MAP_DEHARA_DEPT_6F                       ((10 << 8) | 5)
#define MAP_DEHARA_DEPT_ELEVATOR                 ((10 << 8) | 6)

#define MAP_DEHARA_CITY_GYM_1F                   ((10 << 8) | 23)
#define MAP_DEHARA_CITY_GYM_B1F                  ((10 << 8) | 24)
#define MAP_DEHARA_CITY_GYM_B2F                  ((10 << 8) | 25)

#define MAP_VIVILL_TOWN_POKEMON_CENTRE           ((44 << 8) | 3)
#define MAP_VIVILL_TOWN_POKEMON_CENTRE_TOP_FLOOR ((44 << 8) | 4)
#define MAP_VIVILL_TOWN_MART                     ((44 << 8) | 5)

#define MAP_VIVILL_WAREHOUSE_1F                  ((1 << 8) | 100)
#define MAP_VIVILL_WAREHOUSE_B1F                 ((1 << 8) | 101)
#define MAP_VIVILL_WAREHOUSE_RESEARCH_ROOM       ((1 << 8) | 102)
#define MAP_VIVILL_WAREHOUSE_B2F                 ((1 << 8) | 103)
#define MAP_VIVILL_WAREHOUSE_B3F                 ((1 << 8) | 104)
#define MAP_VIVILL_WAREHOUSE_COMMAND_ROOM        ((1 << 8) | 105)
#define MAP_VIVILL_WAREHOUSE_UNDERWATER          ((1 << 8) | 106)

#define MAP_ANTISIS_CITY_GYM_B1F                 ((54 << 8) | 4)

#define MAP_ANTISIS_SEWERS_NORTH                 ((1 << 8) | 68)
#define MAP_ANTISIS_SEWERS_SOUTH                 ((1 << 8) | 69)
#define MAP_ANTISIS_SEWERS_WEST_TUNNEL           ((1 << 8) | 70)
#define MAP_ANTISIS_SEWERS_EAST_TUNNEL           ((1 << 8) | 71)
#define MAP_ANTISIS_SEWERS_ROOM                  ((1 << 8) | 72)

#define MAP_SEAPORT_WAREHOUSE_WEST_1F            ((33 << 8) | 15)
#define MAP_SEAPORT_WAREHOUSE_WEST_B1F           ((33 << 8) | 16)

#define MAP_POLDER_TOWN_GYM                      ((34 << 8) | 4)

#define MAP_REDWOOD_VILLAGE_GYM_ROOM_1           ((36 << 8) | 7)
#define MAP_REDWOOD_VILLAGE_GYM_ROOM_2           ((36 << 8) | 8)
#define MAP_REDWOOD_VILLAGE_GYM_ROOM_3           ((36 << 8) | 9)
#define MAP_REDWOOD_VILLAGE_GYM_ROOM_4           ((36 << 8) | 10)

#define MAP_POKEMON_LEAGUE_E4_HALL               ((1 << 8) | 74)
#define MAP_POKEMON_LEAGUE_MOLEMAN_ROOM          ((1 << 8) | 75)
#define MAP_POKEMON_LEAGUE_ELIAS_ROOM            ((1 << 8) | 76)
#define MAP_POKEMON_LEAGUE_ANABELLE_ROOM         ((1 << 8) | 77)
#define MAP_POKEMON_LEAGUE_PENNY_ROOM            ((1 << 8) | 78)
#define MAP_POKEMON_LEAGUE_CHAMP_ROOM            ((1 << 8) | 79)
#define MAP_POKEMON_LEAGUE_HALL_OF_FAME          ((1 << 8) | 80)

#define MAP_BATTLE_SIM_SALON                  ((2 << 8) | 6)
#define MAP_BATTLE_TOWER_SALON                   ((2 << 8) | 7)

#define MAP_THE_NIGHTMARE                        ((2 << 8) | 36)

#define MAP_HISTORY_CUTSCENE                     ((31 << 8) | 5)

#endif
