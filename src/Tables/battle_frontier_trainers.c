#include "../config.h"
#include "../../include/global.h"
#include "../../include/new/frontier.h"
#include "../../include/new/text.h"
#include "../../include/constants/event_objects.h"
#include "../../include/constants/trainer_classes.h"
#include "../../include/constants/trainers.h"
#include "../../include/constants/songs.h"

#include "frontier_trainer_names.h"
#include "frontier_special_trainer_spreads.h"
#include "frontier_multi_spreads.h"
/*
battle_frontier_trainers.c
	set up the battle frontier trainer structure

	struct BattleTowerTrainer
	{
		u16 owNum;
		u8 trainerClass;
		u8 trainerSprite;
		u8 gender;
		u8* preBattleText;
		u8* playerWinText;
		u8* playerLoseText;
	};

tables to edit:
	gTowerTrainers
	gSpecialTowerTrainers
	gFrontierBrains
	gFrontierMultiBattleTrainers
*/

extern const u8 sFrontierText_Youngster_PreBattle_1[];
extern const u8 sFrontierText_Youngster_PlayerWin_1[];
extern const u8 sFrontierText_Youngster_PlayerLose_1[];
extern const u8 sFrontierText_Youngster_PreBattle_2[];
extern const u8 sFrontierText_Youngster_PlayerWin_2[];
extern const u8 sFrontierText_Youngster_PlayerLose_2[];
extern const u8 sFrontierText_Youngster_PreBattle_3[];
extern const u8 sFrontierText_Youngster_PlayerWin_3[];
extern const u8 sFrontierText_Youngster_PlayerLose_3[];
extern const u8 sFrontierText_Bugcatcher_PreBattle_1[];
extern const u8 sFrontierText_Bugcatcher_PlayerWin_1[];
extern const u8 sFrontierText_Bugcatcher_PlayerLose_1[];
extern const u8 sFrontierText_Bugcatcher_PreBattle_2[];
extern const u8 sFrontierText_Bugcatcher_PlayerWin_2[];
extern const u8 sFrontierText_Bugcatcher_PlayerLose_2[];
extern const u8 sFrontierText_Bugcatcher_PreBattle_3[];
extern const u8 sFrontierText_Bugcatcher_PlayerWin_3[];
extern const u8 sFrontierText_Bugcatcher_PlayerLose_3[];
extern const u8 sFrontierText_Lass_PreBattle_1[];
extern const u8 sFrontierText_Lass_PlayerWin_1[];
extern const u8 sFrontierText_Lass_PlayerLose_1[];
extern const u8 sFrontierText_Lass_PreBattle_2[];
extern const u8 sFrontierText_Lass_PlayerWin_2[];
extern const u8 sFrontierText_Lass_PlayerLose_2[];
extern const u8 sFrontierText_Lass_PreBattle_3[];
extern const u8 sFrontierText_Lass_PlayerWin_3[];
extern const u8 sFrontierText_Lass_PlayerLose_3[];
extern const u8 sFrontierText_Sailor_PreBattle_1[];
extern const u8 sFrontierText_Sailor_PlayerWin_1[];
extern const u8 sFrontierText_Sailor_PlayerLose_1[];
extern const u8 sFrontierText_Sailor_PreBattle_2[];
extern const u8 sFrontierText_Sailor_PlayerWin_2[];
extern const u8 sFrontierText_Sailor_PlayerLose_2[];
extern const u8 sFrontierText_Sailor_PreBattle_3[];
extern const u8 sFrontierText_Sailor_PlayerWin_3[];
extern const u8 sFrontierText_Sailor_PlayerLose_3[];
extern const u8 sFrontierText_Camper_PreBattle_1[];
extern const u8 sFrontierText_Camper_PlayerWin_1[];
extern const u8 sFrontierText_Camper_PlayerLose_1[];
extern const u8 sFrontierText_Camper_PreBattle_2[];
extern const u8 sFrontierText_Camper_PlayerWin_2[];
extern const u8 sFrontierText_Camper_PlayerLose_2[];
extern const u8 sFrontierText_Camper_PreBattle_3[];
extern const u8 sFrontierText_Camper_PlayerWin_3[];
extern const u8 sFrontierText_Camper_PlayerLose_3[];
extern const u8 sFrontierText_Picnicker_PreBattle_1[];
extern const u8 sFrontierText_Picnicker_PlayerWin_1[];
extern const u8 sFrontierText_Picnicker_PlayerLose_1[];
extern const u8 sFrontierText_Picnicker_PreBattle_2[];
extern const u8 sFrontierText_Picnicker_PlayerWin_2[];
extern const u8 sFrontierText_Picnicker_PlayerLose_2[];
extern const u8 sFrontierText_Picnicker_PreBattle_3[];
extern const u8 sFrontierText_Picnicker_PlayerWin_3[];
extern const u8 sFrontierText_Picnicker_PlayerLose_3[];
extern const u8 sFrontierText_Pokemaniac_PreBattle_1[];
extern const u8 sFrontierText_Pokemaniac_PlayerWin_1[];
extern const u8 sFrontierText_Pokemaniac_PlayerLose_1[];
extern const u8 sFrontierText_Pokemaniac_PreBattle_2[];
extern const u8 sFrontierText_Pokemaniac_PlayerWin_2[];
extern const u8 sFrontierText_Pokemaniac_PlayerLose_2[];
extern const u8 sFrontierText_Pokemaniac_PreBattle_3[];
extern const u8 sFrontierText_Pokemaniac_PlayerWin_3[];
extern const u8 sFrontierText_Pokemaniac_PlayerLose_3[];
extern const u8 sFrontierText_Supernerd_PreBattle_1[];
extern const u8 sFrontierText_Supernerd_PlayerWin_1[];
extern const u8 sFrontierText_Supernerd_PlayerLose_1[];
extern const u8 sFrontierText_Supernerd_PreBattle_2[];
extern const u8 sFrontierText_Supernerd_PlayerWin_2[];
extern const u8 sFrontierText_Supernerd_PlayerLose_2[];
extern const u8 sFrontierText_Supernerd_PreBattle_3[];
extern const u8 sFrontierText_Supernerd_PlayerWin_3[];
extern const u8 sFrontierText_Supernerd_PlayerLose_3[];
extern const u8 sFrontierText_Hiker_PreBattle_1[];
extern const u8 sFrontierText_Hiker_PlayerWin_1[];
extern const u8 sFrontierText_Hiker_PlayerLose_1[];
extern const u8 sFrontierText_Hiker_PreBattle_2[];
extern const u8 sFrontierText_Hiker_PlayerWin_2[];
extern const u8 sFrontierText_Hiker_PlayerLose_2[];
extern const u8 sFrontierText_Hiker_PreBattle_3[];
extern const u8 sFrontierText_Hiker_PlayerWin_3[];
extern const u8 sFrontierText_Hiker_PlayerLose_3[];
extern const u8 sFrontierText_Biker_PreBattle_1[];
extern const u8 sFrontierText_Biker_PlayerWin_1[];
extern const u8 sFrontierText_Biker_PlayerLose_1[];
extern const u8 sFrontierText_Biker_PreBattle_2[];
extern const u8 sFrontierText_Biker_PlayerWin_2[];
extern const u8 sFrontierText_Biker_PlayerLose_2[];
extern const u8 sFrontierText_Biker_PreBattle_3[];
extern const u8 sFrontierText_Biker_PlayerWin_3[];
extern const u8 sFrontierText_Biker_PlayerLose_3[];
extern const u8 sFrontierText_Worker_PreBattle_1[];
extern const u8 sFrontierText_Worker_PlayerWin_1[];
extern const u8 sFrontierText_Worker_PlayerLose_1[];
extern const u8 sFrontierText_Worker_PreBattle_2[];
extern const u8 sFrontierText_Worker_PlayerWin_2[];
extern const u8 sFrontierText_Worker_PlayerLose_2[];
extern const u8 sFrontierText_Worker_PreBattle_3[];
extern const u8 sFrontierText_Worker_PlayerWin_3[];
extern const u8 sFrontierText_Worker_PlayerLose_3[];
extern const u8 sFrontierText_Burglar_PreBattle_1[];
extern const u8 sFrontierText_Burglar_PlayerWin_1[];
extern const u8 sFrontierText_Burglar_PlayerLose_1[];
extern const u8 sFrontierText_Burglar_PreBattle_2[];
extern const u8 sFrontierText_Burglar_PlayerWin_2[];
extern const u8 sFrontierText_Burglar_PlayerLose_2[];
extern const u8 sFrontierText_Burglar_PreBattle_3[];
extern const u8 sFrontierText_Burglar_PlayerWin_3[];
extern const u8 sFrontierText_Burglar_PlayerLose_3[];
extern const u8 sFrontierText_Fisherman_PreBattle_1[];
extern const u8 sFrontierText_Fisherman_PlayerWin_1[];
extern const u8 sFrontierText_Fisherman_PlayerLose_1[];
extern const u8 sFrontierText_Fisherman_PreBattle_2[];
extern const u8 sFrontierText_Fisherman_PlayerWin_2[];
extern const u8 sFrontierText_Fisherman_PlayerLose_2[];
extern const u8 sFrontierText_Fisherman_PreBattle_3[];
extern const u8 sFrontierText_Fisherman_PlayerWin_3[];
extern const u8 sFrontierText_Fisherman_PlayerLose_3[];
extern const u8 sFrontierText_Gambler_PreBattle_1[];
extern const u8 sFrontierText_Gambler_PlayerWin_1[];
extern const u8 sFrontierText_Gambler_PlayerLose_1[];
extern const u8 sFrontierText_Gambler_PreBattle_2[];
extern const u8 sFrontierText_Gambler_PlayerWin_2[];
extern const u8 sFrontierText_Gambler_PlayerLose_2[];
extern const u8 sFrontierText_Gambler_PreBattle_3[];
extern const u8 sFrontierText_Gambler_PlayerWin_3[];
extern const u8 sFrontierText_Gambler_PlayerLose_3[];
extern const u8 sFrontierText_Beauty_PreBattle_1[];
extern const u8 sFrontierText_Beauty_PlayerWin_1[];
extern const u8 sFrontierText_Beauty_PlayerLose_1[];
extern const u8 sFrontierText_Beauty_PreBattle_2[];
extern const u8 sFrontierText_Beauty_PlayerWin_2[];
extern const u8 sFrontierText_Beauty_PlayerLose_2[];
extern const u8 sFrontierText_Beauty_PreBattle_3[];
extern const u8 sFrontierText_Beauty_PlayerWin_3[];
extern const u8 sFrontierText_Beauty_PlayerLose_3[];
extern const u8 sFrontierText_Psychic_PreBattle_1[];
extern const u8 sFrontierText_Psychic_PlayerWin_1[];
extern const u8 sFrontierText_Psychic_PlayerLose_1[];
extern const u8 sFrontierText_Psychic_PreBattle_2[];
extern const u8 sFrontierText_Psychic_PlayerWin_2[];
extern const u8 sFrontierText_Psychic_PlayerLose_2[];
extern const u8 sFrontierText_Psychic_PreBattle_3[];
extern const u8 sFrontierText_Psychic_PlayerWin_3[];
extern const u8 sFrontierText_Psychic_PlayerLose_3[];
extern const u8 sFrontierText_Psychic_PreBattle_4[];
extern const u8 sFrontierText_Psychic_PlayerWin_4[];
extern const u8 sFrontierText_Psychic_PlayerLose_4[];
extern const u8 sFrontierText_Psychic_PreBattle_5[];
extern const u8 sFrontierText_Psychic_PlayerWin_5[];
extern const u8 sFrontierText_Psychic_PlayerLose_5[];
extern const u8 sFrontierText_Psychic_PreBattle_6[];
extern const u8 sFrontierText_Psychic_PlayerWin_6[];
extern const u8 sFrontierText_Psychic_PlayerLose_6[];
extern const u8 sFrontierText_Guitarist_PreBattle_1[];
extern const u8 sFrontierText_Guitarist_PlayerWin_1[];
extern const u8 sFrontierText_Guitarist_PlayerLose_1[];
extern const u8 sFrontierText_Guitarist_PreBattle_2[];
extern const u8 sFrontierText_Guitarist_PlayerWin_2[];
extern const u8 sFrontierText_Guitarist_PlayerLose_2[];
extern const u8 sFrontierText_Guitarist_PreBattle_3[];
extern const u8 sFrontierText_Guitarist_PlayerWin_3[];
extern const u8 sFrontierText_Guitarist_PlayerLose_3[];
extern const u8 sFrontierText_Juggler_PreBattle_1[];
extern const u8 sFrontierText_Juggler_PlayerWin_1[];
extern const u8 sFrontierText_Juggler_PlayerLose_1[];
extern const u8 sFrontierText_Juggler_PreBattle_2[];
extern const u8 sFrontierText_Juggler_PlayerWin_2[];
extern const u8 sFrontierText_Juggler_PlayerLose_2[];
extern const u8 sFrontierText_Juggler_PreBattle_3[];
extern const u8 sFrontierText_Juggler_PlayerWin_3[];
extern const u8 sFrontierText_Juggler_PlayerLose_3[];
extern const u8 sFrontierText_DragonTamer_PreBattle_1[];
extern const u8 sFrontierText_DragonTamer_PlayerWin_1[];
extern const u8 sFrontierText_DragonTamer_PlayerLose_1[];
extern const u8 sFrontierText_DragonTamer_PreBattle_2[];
extern const u8 sFrontierText_DragonTamer_PlayerWin_2[];
extern const u8 sFrontierText_DragonTamer_PlayerLose_2[];
extern const u8 sFrontierText_DragonTamer_PreBattle_3[];
extern const u8 sFrontierText_DragonTamer_PlayerWin_3[];
extern const u8 sFrontierText_DragonTamer_PlayerLose_3[];
extern const u8 sFrontierText_Birdkeeper_PreBattle_1[];
extern const u8 sFrontierText_Birdkeeper_PlayerWin_1[];
extern const u8 sFrontierText_Birdkeeper_PlayerLose_1[];
extern const u8 sFrontierText_Birdkeeper_PreBattle_2[];
extern const u8 sFrontierText_Birdkeeper_PlayerWin_2[];
extern const u8 sFrontierText_Birdkeeper_PlayerLose_2[];
extern const u8 sFrontierText_Birdkeeper_PreBattle_3[];
extern const u8 sFrontierText_Birdkeeper_PlayerWin_3[];
extern const u8 sFrontierText_Birdkeeper_PlayerLose_3[];
extern const u8 sFrontierText_Blackbelt_PreBattle_1[];
extern const u8 sFrontierText_Blackbelt_PlayerWin_1[];
extern const u8 sFrontierText_Blackbelt_PlayerLose_1[];
extern const u8 sFrontierText_Blackbelt_PreBattle_2[];
extern const u8 sFrontierText_Blackbelt_PlayerWin_2[];
extern const u8 sFrontierText_Blackbelt_PlayerLose_2[];
extern const u8 sFrontierText_Blackbelt_PreBattle_3[];
extern const u8 sFrontierText_Blackbelt_PlayerWin_3[];
extern const u8 sFrontierText_Blackbelt_PlayerLose_3[];
extern const u8 sFrontierText_BattleGirl_PreBattle_1[];
extern const u8 sFrontierText_BattleGirl_PlayerWin_1[];
extern const u8 sFrontierText_BattleGirl_PlayerLose_1[];
extern const u8 sFrontierText_BattleGirl_PreBattle_2[];
extern const u8 sFrontierText_BattleGirl_PlayerWin_2[];
extern const u8 sFrontierText_BattleGirl_PlayerLose_2[];
extern const u8 sFrontierText_BattleGirl_PreBattle_3[];
extern const u8 sFrontierText_BattleGirl_PlayerWin_3[];
extern const u8 sFrontierText_BattleGirl_PlayerLose_3[];
extern const u8 sFrontierText_Scientist_PreBattle_1[];
extern const u8 sFrontierText_Scientist_PlayerWin_1[];
extern const u8 sFrontierText_Scientist_PlayerLose_1[];
extern const u8 sFrontierText_Scientist_PreBattle_2[];
extern const u8 sFrontierText_Scientist_PlayerWin_2[];
extern const u8 sFrontierText_Scientist_PlayerLose_2[];
extern const u8 sFrontierText_Scientist_PreBattle_3[];
extern const u8 sFrontierText_Scientist_PlayerWin_3[];
extern const u8 sFrontierText_Scientist_PlayerLose_3[];
extern const u8 sFrontierText_Scientist_PreBattle_4[];
extern const u8 sFrontierText_Scientist_PlayerWin_4[];
extern const u8 sFrontierText_Scientist_PlayerLose_4[];
extern const u8 sFrontierText_Acetrainer_PreBattle_1[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_1[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_1[];
extern const u8 sFrontierText_Acetrainer_PreBattle_2[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_2[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_2[];
extern const u8 sFrontierText_Acetrainer_PreBattle_3[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_3[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_3[];
extern const u8 sFrontierText_Acetrainer_PreBattle_4[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_4[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_4[];
extern const u8 sFrontierText_Acetrainer_PreBattle_5[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_5[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_5[];
extern const u8 sFrontierText_Acetrainer_PreBattle_6[];
extern const u8 sFrontierText_Acetrainer_PlayerWin_6[];
extern const u8 sFrontierText_Acetrainer_PlayerLose_6[];
extern const u8 sFrontierText_Gentleman_PreBattle_1[];
extern const u8 sFrontierText_Gentleman_PlayerWin_1[];
extern const u8 sFrontierText_Gentleman_PlayerLose_1[];
extern const u8 sFrontierText_Gentleman_PreBattle_2[];
extern const u8 sFrontierText_Gentleman_PlayerWin_2[];
extern const u8 sFrontierText_Gentleman_PlayerLose_2[];
extern const u8 sFrontierText_Gentleman_PreBattle_3[];
extern const u8 sFrontierText_Gentleman_PlayerWin_3[];
extern const u8 sFrontierText_Gentleman_PlayerLose_3[];
extern const u8 sFrontierText_Tuber_PreBattle_1[];
extern const u8 sFrontierText_Tuber_PlayerWin_1[];
extern const u8 sFrontierText_Tuber_PlayerLose_1[];
extern const u8 sFrontierText_Tuber_PreBattle_2[];
extern const u8 sFrontierText_Tuber_PlayerWin_2[];
extern const u8 sFrontierText_Tuber_PlayerLose_2[];
extern const u8 sFrontierText_Tuber_PreBattle_3[];
extern const u8 sFrontierText_Tuber_PlayerWin_3[];
extern const u8 sFrontierText_Tuber_PlayerLose_3[];
extern const u8 sFrontierText_Tuber_PreBattle_4[];
extern const u8 sFrontierText_Tuber_PlayerWin_4[];
extern const u8 sFrontierText_Tuber_PlayerLose_4[];
extern const u8 sFrontierText_Tuber_PreBattle_5[];
extern const u8 sFrontierText_Tuber_PlayerWin_5[];
extern const u8 sFrontierText_Tuber_PlayerLose_5[];
extern const u8 sFrontierText_Tuber_PreBattle_6[];
extern const u8 sFrontierText_Tuber_PlayerWin_6[];
extern const u8 sFrontierText_Tuber_PlayerLose_6[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_1[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_1[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_1[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_2[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_2[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_2[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_3[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_3[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_3[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_4[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_4[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_4[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_5[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_5[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_5[];
extern const u8 sFrontierText_Pkmnbreeder_PreBattle_6[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerWin_6[];
extern const u8 sFrontierText_Pkmnbreeder_PlayerLose_6[];
extern const u8 sFrontierText_Aromalady_PreBattle_1[];
extern const u8 sFrontierText_Aromalady_PlayerWin_1[];
extern const u8 sFrontierText_Aromalady_PlayerLose_1[];
extern const u8 sFrontierText_Aromalady_PreBattle_2[];
extern const u8 sFrontierText_Aromalady_PlayerWin_2[];
extern const u8 sFrontierText_Aromalady_PlayerLose_2[];
extern const u8 sFrontierText_Aromalady_PreBattle_3[];
extern const u8 sFrontierText_Aromalady_PlayerWin_3[];
extern const u8 sFrontierText_Aromalady_PlayerLose_3[];
extern const u8 sFrontierText_Ruinmaniac_PreBattle_1[];
extern const u8 sFrontierText_Ruinmaniac_PlayerWin_1[];
extern const u8 sFrontierText_Ruinmaniac_PlayerLose_1[];
extern const u8 sFrontierText_Ruinmaniac_PreBattle_2[];
extern const u8 sFrontierText_Ruinmaniac_PlayerWin_2[];
extern const u8 sFrontierText_Ruinmaniac_PlayerLose_2[];
extern const u8 sFrontierText_Ruinmaniac_PreBattle_3[];
extern const u8 sFrontierText_Ruinmaniac_PlayerWin_3[];
extern const u8 sFrontierText_Ruinmaniac_PlayerLose_3[];
extern const u8 sFrontierText_Painter_PreBattle_1[];
extern const u8 sFrontierText_Painter_PlayerWin_1[];
extern const u8 sFrontierText_Painter_PlayerLose_1[];
extern const u8 sFrontierText_Painter_PreBattle_2[];
extern const u8 sFrontierText_Painter_PlayerWin_2[];
extern const u8 sFrontierText_Painter_PlayerLose_2[];
extern const u8 sFrontierText_Painter_PreBattle_3[];
extern const u8 sFrontierText_Painter_PlayerWin_3[];
extern const u8 sFrontierText_Painter_PlayerLose_3[];
extern const u8 sFrontierText_ExpertM_PreBattle_1[];
extern const u8 sFrontierText_ExpertM_PlayerWin_1[];
extern const u8 sFrontierText_ExpertM_PlayerLose_1[];
extern const u8 sFrontierText_ExpertM_PreBattle_2[];
extern const u8 sFrontierText_ExpertM_PlayerWin_2[];
extern const u8 sFrontierText_ExpertM_PlayerLose_2[];
extern const u8 sFrontierText_ExpertM_PreBattle_3[];
extern const u8 sFrontierText_ExpertM_PlayerWin_3[];
extern const u8 sFrontierText_ExpertM_PlayerLose_3[];
extern const u8 sFrontierText_ExpertF_PreBattle_1[];
extern const u8 sFrontierText_ExpertF_PlayerWin_1[];
extern const u8 sFrontierText_ExpertF_PlayerLose_1[];
extern const u8 sFrontierText_ExpertF_PreBattle_2[];
extern const u8 sFrontierText_ExpertF_PlayerWin_2[];
extern const u8 sFrontierText_ExpertF_PlayerLose_2[];
extern const u8 sFrontierText_ExpertF_PreBattle_3[];
extern const u8 sFrontierText_ExpertF_PlayerWin_3[];
extern const u8 sFrontierText_ExpertF_PlayerLose_3[];
extern const u8 sFrontierText_PokefanM_PreBattle_1[];
extern const u8 sFrontierText_PokefanM_PlayerWin_1[];
extern const u8 sFrontierText_PokefanM_PlayerLose_1[];
extern const u8 sFrontierText_PokefanM_PreBattle_2[];
extern const u8 sFrontierText_PokefanM_PlayerWin_2[];
extern const u8 sFrontierText_PokefanM_PlayerLose_2[];
extern const u8 sFrontierText_PokefanM_PreBattle_3[];
extern const u8 sFrontierText_PokefanM_PlayerWin_3[];
extern const u8 sFrontierText_PokefanM_PlayerLose_3[];
extern const u8 sFrontierText_Nurse_PreBattle_1[];
extern const u8 sFrontierText_Nurse_PlayerWin_1[];
extern const u8 sFrontierText_Nurse_PlayerLose_1[];
extern const u8 sFrontierText_Nurse_PreBattle_2[];
extern const u8 sFrontierText_Nurse_PlayerWin_2[];
extern const u8 sFrontierText_Nurse_PlayerLose_2[];
extern const u8 sFrontierText_Nurse_PreBattle_3[];
extern const u8 sFrontierText_Nurse_PlayerWin_3[];
extern const u8 sFrontierText_Nurse_PlayerLose_3[];
extern const u8 sFrontierText_Swimmer_PreBattle_1[];
extern const u8 sFrontierText_Swimmer_PlayerWin_1[];
extern const u8 sFrontierText_Swimmer_PlayerLose_1[];
extern const u8 sFrontierText_Swimmer_PreBattle_2[];
extern const u8 sFrontierText_Swimmer_PlayerWin_2[];
extern const u8 sFrontierText_Swimmer_PlayerLose_2[];
extern const u8 sFrontierText_Swimmer_PreBattle_3[];
extern const u8 sFrontierText_Swimmer_PlayerWin_3[];
extern const u8 sFrontierText_Swimmer_PlayerLose_3[];
extern const u8 sFrontierText_Swimmer_PreBattle_1[];
extern const u8 sFrontierText_Swimmer_PlayerWin_1[];
extern const u8 sFrontierText_Swimmer_PlayerLose_1[];
extern const u8 sFrontierText_Swimmer_PreBattle_2[];
extern const u8 sFrontierText_Swimmer_PlayerWin_2[];
extern const u8 sFrontierText_Swimmer_PlayerLose_2[];
extern const u8 sFrontierText_Swimmer_PreBattle_3[];
extern const u8 sFrontierText_Swimmer_PlayerWin_3[];
extern const u8 sFrontierText_Swimmer_PlayerLose_3[];
extern const u8 sFrontierText_NinjaBoy_PreBattle_1[];
extern const u8 sFrontierText_NinjaBoy_PlayerWin_1[];
extern const u8 sFrontierText_NinjaBoy_PlayerLose_1[];
extern const u8 sFrontierText_NinjaBoy_PreBattle_2[];
extern const u8 sFrontierText_NinjaBoy_PlayerWin_2[];
extern const u8 sFrontierText_NinjaBoy_PlayerLose_2[];
extern const u8 sFrontierText_NinjaBoy_PreBattle_3[];
extern const u8 sFrontierText_NinjaBoy_PlayerWin_3[];
extern const u8 sFrontierText_NinjaBoy_PlayerLose_3[];
extern const u8 sFrontierText_Channeler_PreBattle_1[];
extern const u8 sFrontierText_Channeler_PlayerWin_1[];
extern const u8 sFrontierText_Channeler_PlayerLose_1[];
extern const u8 sFrontierText_Channeler_PreBattle_2[];
extern const u8 sFrontierText_Channeler_PlayerWin_2[];
extern const u8 sFrontierText_Channeler_PlayerLose_2[];
extern const u8 sFrontierText_Channeler_PreBattle_3[];
extern const u8 sFrontierText_Channeler_PlayerWin_3[];
extern const u8 sFrontierText_Channeler_PlayerLose_3[];
extern const u8 sFrontierText_Skier_PreBattle_1[];
extern const u8 sFrontierText_Skier_PlayerWin_1[];
extern const u8 sFrontierText_Skier_PlayerLose_1[];
extern const u8 sFrontierText_Skier_PreBattle_2[];
extern const u8 sFrontierText_Skier_PlayerWin_2[];
extern const u8 sFrontierText_Skier_PlayerLose_2[];
extern const u8 sFrontierText_Skier_PreBattle_3[];
extern const u8 sFrontierText_Skier_PlayerWin_3[];
extern const u8 sFrontierText_Skier_PlayerLose_3[];

extern const u8 sTrainerName_Mort[];
extern const u8 sTrainerName_Rival[];
extern const u8 sTrainerName_Selene[];
extern const u8 sTrainerName_Alistair[];
extern const u8 sTrainerName_Collin[];
extern const u8 sTrainerName_Crystal[];
extern const u8 sTrainerName_Brendan[];
extern const u8 sTrainerName_May[];
extern const u8 sTrainerName_Terrence[];
extern const u8 sTrainerName_Stella[];
extern const u8 sTrainerName_Raine[];
extern const u8 sTrainerName_Chance[];
extern const u8 sTrainerName_Casey[];
extern const u8 sTrainerName_Abby[];
extern const u8 sTrainerName_Iris[];
extern const u8 sTrainerName_Dennis[];

// Aces - Randomly chosen at streak 20
extern const u8 sFrontierText_Mort_PreBattle[];
extern const u8 sFrontierText_Mort_PlayerWin[];
extern const u8 sFrontierText_Mort_PlayerLose[];
extern const u8 sFrontierText_Rival_PreBattle[];
extern const u8 sFrontierText_Rival_PlayerWin[];
extern const u8 sFrontierText_Rival_PlayerLose[];
extern const u8 sFrontierText_Selene_PreBattle[];
extern const u8 sFrontierText_Selene_PlayerWin[];
extern const u8 sFrontierText_Selene_PlayerLose[];
extern const u8 sFrontierText_Alistair_PreBattle[];
extern const u8 sFrontierText_Alistair_PlayerWin[];
extern const u8 sFrontierText_Alistair_PlayerLose[];
extern const u8 sFrontierText_Collin_PreBattle[];
extern const u8 sFrontierText_Collin_PlayerWin[];
extern const u8 sFrontierText_Collin_PlayerLose[];
extern const u8 sFrontierText_Crystal_PreBattle[];
extern const u8 sFrontierText_Crystal_PlayerWin[];
extern const u8 sFrontierText_Crystal_PlayerLose[];
extern const u8 sFrontierText_Brendan_PreBattle[];
extern const u8 sFrontierText_Brendan_PlayerWin[];
extern const u8 sFrontierText_Brendan_PlayerLose[];
extern const u8 sFrontierText_May_PreBattle[];
extern const u8 sFrontierText_May_PlayerWin[];
extern const u8 sFrontierText_May_PlayerLose[];

// Brains - Specifically chosen by facility ID at streak 50
extern const u8 sFrontierText_Terrence_PreBattle[];
extern const u8 sFrontierText_Terrence_PlayerWin[];
extern const u8 sFrontierText_Terrence_PlayerLose[];
extern const u8 sFrontierText_Stella_PreBattle[];
extern const u8 sFrontierText_Stella_PlayerWin[];
extern const u8 sFrontierText_Stella_PlayerLose[];
extern const u8 sFrontierText_Raine_PreBattle[];
extern const u8 sFrontierText_Raine_PlayerWin[];
extern const u8 sFrontierText_Raine_PlayerLose[];
extern const u8 sFrontierText_Chance_PreBattle[];
extern const u8 sFrontierText_Chance_PlayerWin[];
extern const u8 sFrontierText_Chance_PlayerLose[];
extern const u8 sFrontierText_Casey_PreBattle[];
extern const u8 sFrontierText_Casey_PlayerWin[];
extern const u8 sFrontierText_Casey_PlayerLose[];
extern const u8 sFrontierText_Abby_PreBattle[];
extern const u8 sFrontierText_Abby_PlayerWin[];
extern const u8 sFrontierText_Abby_PlayerLose[];
extern const u8 sFrontierText_Iris_PreBattle[];
extern const u8 sFrontierText_Iris_PlayerWin[];
extern const u8 sFrontierText_Iris_PlayerLose[];
extern const u8 sFrontierText_Dennis_PreBattle[];
extern const u8 sFrontierText_Dennis_PlayerWin[];
extern const u8 sFrontierText_Dennis_PlayerLose[];

const struct BattleTowerTrainer gTowerTrainers[] =
{
	{
		.owNum = 			EVENT_OBJ_GFX_YOUNGSTER,
		.trainerClass = 	CLASS_YOUNGSTER,
		.trainerSprite = 	TRAINER_PIC_YOUNGSTER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Youngster_PreBattle_1,
		.playerWinText = 	sFrontierText_Youngster_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Youngster_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_YOUNGSTER,
		.trainerClass = 	CLASS_YOUNGSTER,
		.trainerSprite = 	TRAINER_PIC_YOUNGSTER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Youngster_PreBattle_2,
		.playerWinText = 	sFrontierText_Youngster_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Youngster_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_YOUNGSTER,
		.trainerClass = 	CLASS_YOUNGSTER,
		.trainerSprite = 	TRAINER_PIC_YOUNGSTER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Youngster_PreBattle_3,
		.playerWinText = 	sFrontierText_Youngster_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Youngster_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BUG_CATCHER,
		.trainerClass = 	CLASS_BUG_CATCHER,
		.trainerSprite = 	TRAINER_PIC_BUG_CATCHER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Bugcatcher_PreBattle_1,
		.playerWinText = 	sFrontierText_Bugcatcher_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Bugcatcher_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BUG_CATCHER,
		.trainerClass = 	CLASS_BUG_CATCHER,
		.trainerSprite = 	TRAINER_PIC_BUG_CATCHER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Bugcatcher_PreBattle_2,
		.playerWinText = 	sFrontierText_Bugcatcher_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Bugcatcher_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BUG_CATCHER,
		.trainerClass = 	CLASS_BUG_CATCHER,
		.trainerSprite = 	TRAINER_PIC_BUG_CATCHER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Bugcatcher_PreBattle_3,
		.playerWinText = 	sFrontierText_Bugcatcher_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Bugcatcher_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_LASS,
		.trainerSprite = 	TRAINER_PIC_LASS,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Lass_PreBattle_1,
		.playerWinText = 	sFrontierText_Lass_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Lass_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_LASS,
		.trainerSprite = 	TRAINER_PIC_LASS,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Lass_PreBattle_2,
		.playerWinText = 	sFrontierText_Lass_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Lass_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_LASS,
		.trainerSprite = 	TRAINER_PIC_LASS,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Lass_PreBattle_3,
		.playerWinText = 	sFrontierText_Lass_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Lass_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SAILOR,
		.trainerClass = 	CLASS_SAILOR,
		.trainerSprite = 	TRAINER_PIC_SAILOR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Sailor_PreBattle_1,
		.playerWinText = 	sFrontierText_Sailor_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Sailor_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SAILOR,
		.trainerClass = 	CLASS_SAILOR,
		.trainerSprite = 	TRAINER_PIC_SAILOR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Sailor_PreBattle_2,
		.playerWinText = 	sFrontierText_Sailor_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Sailor_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SAILOR,
		.trainerClass = 	CLASS_SAILOR,
		.trainerSprite = 	TRAINER_PIC_SAILOR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Sailor_PreBattle_3,
		.playerWinText = 	sFrontierText_Sailor_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Sailor_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CAMPER,
		.trainerClass = 	CLASS_CAMPER,
		.trainerSprite = 	TRAINER_PIC_CAMPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Camper_PreBattle_1,
		.playerWinText = 	sFrontierText_Camper_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Camper_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CAMPER,
		.trainerClass = 	CLASS_CAMPER,
		.trainerSprite = 	TRAINER_PIC_CAMPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Camper_PreBattle_2,
		.playerWinText = 	sFrontierText_Camper_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Camper_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CAMPER,
		.trainerClass = 	CLASS_CAMPER,
		.trainerSprite = 	TRAINER_PIC_CAMPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Camper_PreBattle_3,
		.playerWinText = 	sFrontierText_Camper_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Camper_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_PICNICKER,
		.trainerClass = 	CLASS_PICNICKER,
		.trainerSprite = 	TRAINER_PIC_PICNICKER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Picnicker_PreBattle_1,
		.playerWinText = 	sFrontierText_Picnicker_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Picnicker_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_PICNICKER,
		.trainerClass = 	CLASS_PICNICKER,
		.trainerSprite = 	TRAINER_PIC_PICNICKER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Picnicker_PreBattle_2,
		.playerWinText = 	sFrontierText_Picnicker_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Picnicker_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_PICNICKER,
		.trainerClass = 	CLASS_PICNICKER,
		.trainerSprite = 	TRAINER_PIC_PICNICKER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Picnicker_PreBattle_3,
		.playerWinText = 	sFrontierText_Picnicker_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Picnicker_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_POKEMANIAC,
		.trainerSprite = 	TRAINER_PIC_POKEMANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Pokemaniac_PreBattle_1,
		.playerWinText = 	sFrontierText_Pokemaniac_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Pokemaniac_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_POKEMANIAC,
		.trainerSprite = 	TRAINER_PIC_POKEMANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Pokemaniac_PreBattle_2,
		.playerWinText = 	sFrontierText_Pokemaniac_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Pokemaniac_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_POKEMANIAC,
		.trainerSprite = 	TRAINER_PIC_POKEMANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Pokemaniac_PreBattle_3,
		.playerWinText = 	sFrontierText_Pokemaniac_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Pokemaniac_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SUPER_NERD,
		.trainerClass = 	CLASS_SUPER_NERD,
		.trainerSprite = 	TRAINER_PIC_SUPER_NERD,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Supernerd_PreBattle_1,
		.playerWinText = 	sFrontierText_Supernerd_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Supernerd_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SUPER_NERD,
		.trainerClass = 	CLASS_SUPER_NERD,
		.trainerSprite = 	TRAINER_PIC_SUPER_NERD,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Supernerd_PreBattle_2,
		.playerWinText = 	sFrontierText_Supernerd_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Supernerd_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SUPER_NERD,
		.trainerClass = 	CLASS_SUPER_NERD,
		.trainerSprite = 	TRAINER_PIC_SUPER_NERD,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Supernerd_PreBattle_3,
		.playerWinText = 	sFrontierText_Supernerd_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Supernerd_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_HIKER,
		.trainerSprite = 	TRAINER_PIC_HIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Hiker_PreBattle_1,
		.playerWinText = 	sFrontierText_Hiker_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Hiker_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_HIKER,
		.trainerSprite = 	TRAINER_PIC_HIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Hiker_PreBattle_2,
		.playerWinText = 	sFrontierText_Hiker_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Hiker_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_HIKER,
		.trainerSprite = 	TRAINER_PIC_HIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Hiker_PreBattle_3,
		.playerWinText = 	sFrontierText_Hiker_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Hiker_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BIKER_BALL,
		.trainerClass = 	CLASS_BIKER,
		.trainerSprite = 	TRAINER_PIC_BIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Biker_PreBattle_1,
		.playerWinText = 	sFrontierText_Biker_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Biker_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BIKER_BALL,
		.trainerClass = 	CLASS_BIKER,
		.trainerSprite = 	TRAINER_PIC_BIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Biker_PreBattle_2,
		.playerWinText = 	sFrontierText_Biker_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Biker_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BIKER_BALL,
		.trainerClass = 	CLASS_BIKER,
		.trainerSprite = 	TRAINER_PIC_BIKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Biker_PreBattle_3,
		.playerWinText = 	sFrontierText_Biker_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Biker_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_BURGLAR,
		.trainerSprite = 	TRAINER_PIC_BURGLAR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Burglar_PreBattle_1,
		.playerWinText = 	sFrontierText_Burglar_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Burglar_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_BURGLAR,
		.trainerSprite = 	TRAINER_PIC_BURGLAR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Burglar_PreBattle_2,
		.playerWinText = 	sFrontierText_Burglar_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Burglar_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_BURGLAR,
		.trainerSprite = 	TRAINER_PIC_BURGLAR,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Burglar_PreBattle_3,
		.playerWinText = 	sFrontierText_Burglar_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Burglar_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_ENGINEER,
		.trainerSprite = 	TRAINER_PIC_WORKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Worker_PreBattle_1,
		.playerWinText = 	sFrontierText_Worker_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Worker_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_ENGINEER,
		.trainerSprite = 	TRAINER_PIC_WORKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Worker_PreBattle_2,
		.playerWinText = 	sFrontierText_Worker_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Worker_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_ENGINEER,
		.trainerSprite = 	TRAINER_PIC_WORKER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Worker_PreBattle_3,
		.playerWinText = 	sFrontierText_Worker_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Worker_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FISHERMAN,
		.trainerClass = 	CLASS_FISHERMAN,
		.trainerSprite = 	TRAINER_PIC_FISHERMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Fisherman_PreBattle_1,
		.playerWinText = 	sFrontierText_Fisherman_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Fisherman_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FISHERMAN,
		.trainerClass = 	CLASS_FISHERMAN,
		.trainerSprite = 	TRAINER_PIC_FISHERMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Fisherman_PreBattle_2,
		.playerWinText = 	sFrontierText_Fisherman_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Fisherman_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FISHERMAN,
		.trainerClass = 	CLASS_FISHERMAN,
		.trainerSprite = 	TRAINER_PIC_FISHERMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Fisherman_PreBattle_3,
		.playerWinText = 	sFrontierText_Fisherman_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Fisherman_PlayerLose_3,
	},

	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_GAMBLER,
		.trainerSprite = 	TRAINER_PIC_GAMBLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gambler_PreBattle_1,
		.playerWinText = 	sFrontierText_Gambler_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Gambler_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_GAMBLER,
		.trainerSprite = 	TRAINER_PIC_GAMBLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gambler_PreBattle_2,
		.playerWinText = 	sFrontierText_Gambler_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Gambler_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_GAMBLER,
		.trainerSprite = 	TRAINER_PIC_GAMBLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gambler_PreBattle_3,
		.playerWinText = 	sFrontierText_Gambler_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Gambler_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BEAUTY,
		.trainerClass = 	CLASS_BEAUTY,
		.trainerSprite = 	TRAINER_PIC_BEAUTY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Beauty_PreBattle_1,
		.playerWinText = 	sFrontierText_Beauty_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Beauty_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BEAUTY,
		.trainerClass = 	CLASS_BEAUTY,
		.trainerSprite = 	TRAINER_PIC_BEAUTY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Beauty_PreBattle_2,
		.playerWinText = 	sFrontierText_Beauty_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Beauty_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BEAUTY,
		.trainerClass = 	CLASS_BEAUTY,
		.trainerSprite = 	TRAINER_PIC_BEAUTY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Beauty_PreBattle_3,
		.playerWinText = 	sFrontierText_Beauty_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Beauty_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_1,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_2,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_3,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_4,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_4,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_4,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_5,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_5,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_5,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_PSYCHIC,
		.trainerSprite = 	TRAINER_PIC_PSYCHIC_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Psychic_PreBattle_6,
		.playerWinText = 	sFrontierText_Psychic_PlayerWin_6,
		.playerLoseText = 	sFrontierText_Psychic_PlayerLose_6,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GUITARIST,
		.trainerClass = 	CLASS_GUITARIST_RS,
		.trainerSprite = 	TRAINER_PIC_GUITARIST,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Guitarist_PreBattle_1,
		.playerWinText = 	sFrontierText_Guitarist_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Guitarist_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GUITARIST,
		.trainerClass = 	CLASS_GUITARIST_RS,
		.trainerSprite = 	TRAINER_PIC_GUITARIST,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Guitarist_PreBattle_2,
		.playerWinText = 	sFrontierText_Guitarist_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Guitarist_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GUITARIST,
		.trainerClass = 	CLASS_GUITARIST_RS,
		.trainerSprite = 	TRAINER_PIC_GUITARIST,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Guitarist_PreBattle_3,
		.playerWinText = 	sFrontierText_Guitarist_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Guitarist_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_JUGGLER,
		.trainerSprite = 	TRAINER_PIC_JUGGLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Juggler_PreBattle_1,
		.playerWinText = 	sFrontierText_Juggler_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Juggler_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_JUGGLER,
		.trainerSprite = 	TRAINER_PIC_JUGGLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Juggler_PreBattle_2,
		.playerWinText = 	sFrontierText_Juggler_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Juggler_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_FAT_GUY,
		.trainerClass = 	CLASS_JUGGLER,
		.trainerSprite = 	TRAINER_PIC_JUGGLER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Juggler_PreBattle_3,
		.playerWinText = 	sFrontierText_Juggler_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Juggler_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_DRAGON_TAMER,
		.trainerSprite = 	TRAINER_PIC_DRAGON_TAMER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_DragonTamer_PreBattle_1,
		.playerWinText = 	sFrontierText_DragonTamer_PlayerWin_1,
		.playerLoseText = 	sFrontierText_DragonTamer_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_DRAGON_TAMER,
		.trainerSprite = 	TRAINER_PIC_DRAGON_TAMER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_DragonTamer_PreBattle_2,
		.playerWinText = 	sFrontierText_DragonTamer_PlayerWin_2,
		.playerLoseText = 	sFrontierText_DragonTamer_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_POKEMANIAC,
		.trainerClass = 	CLASS_DRAGON_TAMER,
		.trainerSprite = 	TRAINER_PIC_DRAGON_TAMER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_DragonTamer_PreBattle_3,
		.playerWinText = 	sFrontierText_DragonTamer_PlayerWin_3,
		.playerLoseText = 	sFrontierText_DragonTamer_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_RANDOM_GUY,
		.trainerClass = 	CLASS_BIRD_KEEPER,
		.trainerSprite = 	TRAINER_PIC_BIRD_KEEPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Birdkeeper_PreBattle_1,
		.playerWinText = 	sFrontierText_Birdkeeper_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Birdkeeper_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_RANDOM_GUY,
		.trainerClass = 	CLASS_BIRD_KEEPER,
		.trainerSprite = 	TRAINER_PIC_BIRD_KEEPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Birdkeeper_PreBattle_2,
		.playerWinText = 	sFrontierText_Birdkeeper_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Birdkeeper_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_RANDOM_GUY,
		.trainerClass = 	CLASS_BIRD_KEEPER,
		.trainerSprite = 	TRAINER_PIC_BIRD_KEEPER,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Birdkeeper_PreBattle_3,
		.playerWinText = 	sFrontierText_Birdkeeper_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Birdkeeper_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BLACK_BELT,
		.trainerClass = 	CLASS_BLACK_BELT,
		.trainerSprite = 	TRAINER_PIC_BLACK_BELT,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Blackbelt_PreBattle_1,
		.playerWinText = 	sFrontierText_Blackbelt_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Blackbelt_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BLACK_BELT,
		.trainerClass = 	CLASS_BLACK_BELT,
		.trainerSprite = 	TRAINER_PIC_BLACK_BELT,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Blackbelt_PreBattle_2,
		.playerWinText = 	sFrontierText_Blackbelt_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Blackbelt_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BLACK_BELT,
		.trainerClass = 	CLASS_BLACK_BELT,
		.trainerSprite = 	TRAINER_PIC_BLACK_BELT,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Blackbelt_PreBattle_3,
		.playerWinText = 	sFrontierText_Blackbelt_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Blackbelt_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CRUSH_GIRL,
		.trainerClass = 	CLASS_CRUSH_GIRL,
		.trainerSprite = 	TRAINER_PIC_CRUSH_GIRL,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_BattleGirl_PreBattle_1,
		.playerWinText = 	sFrontierText_BattleGirl_PlayerWin_1,
		.playerLoseText = 	sFrontierText_BattleGirl_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CRUSH_GIRL,
		.trainerClass = 	CLASS_CRUSH_GIRL,
		.trainerSprite = 	TRAINER_PIC_CRUSH_GIRL,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_BattleGirl_PreBattle_2,
		.playerWinText = 	sFrontierText_BattleGirl_PlayerWin_2,
		.playerLoseText = 	sFrontierText_BattleGirl_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CRUSH_GIRL,
		.trainerClass = 	CLASS_CRUSH_GIRL,
		.trainerSprite = 	TRAINER_PIC_CRUSH_GIRL,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_BattleGirl_PreBattle_3,
		.playerWinText = 	sFrontierText_BattleGirl_PlayerWin_3,
		.playerLoseText = 	sFrontierText_BattleGirl_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SCIENTIST_MALE,
		.trainerClass = 	CLASS_SCIENTIST,
		.trainerSprite = 	TRAINER_PIC_SCIENTIST_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Scientist_PreBattle_1,
		.playerWinText = 	sFrontierText_Scientist_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Scientist_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SCIENTIST_MALE,
		.trainerClass = 	CLASS_SCIENTIST,
		.trainerSprite = 	TRAINER_PIC_SCIENTIST_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Scientist_PreBattle_2,
		.playerWinText = 	sFrontierText_Scientist_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Scientist_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SCIENTIST_MALE,
		.trainerClass = 	CLASS_SCIENTIST,
		.trainerSprite = 	TRAINER_PIC_SCIENTIST_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Scientist_PreBattle_3,
		.playerWinText = 	sFrontierText_Scientist_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Scientist_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SCIENTIST_MALE,
		.trainerClass = 	CLASS_SCIENTIST,
		.trainerSprite = 	TRAINER_PIC_SCIENTIST_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Scientist_PreBattle_4,
		.playerWinText = 	sFrontierText_Scientist_PlayerWin_4,
		.playerLoseText = 	sFrontierText_Scientist_PlayerLose_4,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_1,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_2,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_3,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_4,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_4,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_4,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_5,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_5,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_5,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_COOLTRAINER,
		.trainerSprite = 	TRAINER_PIC_COOLTRAINER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Acetrainer_PreBattle_6,
		.playerWinText = 	sFrontierText_Acetrainer_PlayerWin_6,
		.playerLoseText = 	sFrontierText_Acetrainer_PlayerLose_6,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GENTLEMAN,
		.trainerClass = 	CLASS_GENTLEMAN,
		.trainerSprite = 	TRAINER_PIC_GENTLEMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gentleman_PreBattle_1,
		.playerWinText = 	sFrontierText_Gentleman_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Gentleman_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GENTLEMAN,
		.trainerClass = 	CLASS_GENTLEMAN,
		.trainerSprite = 	TRAINER_PIC_GENTLEMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gentleman_PreBattle_2,
		.playerWinText = 	sFrontierText_Gentleman_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Gentleman_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_GENTLEMAN,
		.trainerClass = 	CLASS_GENTLEMAN,
		.trainerSprite = 	TRAINER_PIC_GENTLEMAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Gentleman_PreBattle_3,
		.playerWinText = 	sFrontierText_Gentleman_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Gentleman_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_M,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_1,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_M,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_2,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_M,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_3,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_F,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_4,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_4,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_4,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_F,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_5,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_5,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_5,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_TUBER_F,
		.trainerClass = 	CLASS_TUBER,
		.trainerSprite = 	TRAINER_PIC_RS_TUBER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Tuber_PreBattle_6,
		.playerWinText = 	sFrontierText_Tuber_PlayerWin_6,
		.playerLoseText = 	sFrontierText_Tuber_PlayerLose_6,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_1,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_2,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_3,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_4,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_4,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_4,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_5,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_5,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_5,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_WOMAN,
		.trainerClass = 	CLASS_PKMN_BREEDER,
		.trainerSprite = 	TRAINER_PIC_PKMN_BREEDER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Pkmnbreeder_PreBattle_6,
		.playerWinText = 	sFrontierText_Pkmnbreeder_PlayerWin_6,
		.playerLoseText = 	sFrontierText_Pkmnbreeder_PlayerLose_6,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_AROMA_LADY,
		.trainerClass = 	CLASS_AROMA_LADY,
		.trainerSprite = 	TRAINER_PIC_AROMA_LADY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Aromalady_PreBattle_1,
		.playerWinText = 	sFrontierText_Aromalady_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Aromalady_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_AROMA_LADY,
		.trainerClass = 	CLASS_AROMA_LADY,
		.trainerSprite = 	TRAINER_PIC_AROMA_LADY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Aromalady_PreBattle_2,
		.playerWinText = 	sFrontierText_Aromalady_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Aromalady_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_AROMA_LADY,
		.trainerClass = 	CLASS_AROMA_LADY,
		.trainerSprite = 	TRAINER_PIC_AROMA_LADY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Aromalady_PreBattle_3,
		.playerWinText = 	sFrontierText_Aromalady_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Aromalady_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_RUIN_MANIAC,
		.trainerSprite = 	TRAINER_PIC_RUIN_MANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Ruinmaniac_PreBattle_1,
		.playerWinText = 	sFrontierText_Ruinmaniac_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Ruinmaniac_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_RUIN_MANIAC,
		.trainerSprite = 	TRAINER_PIC_RUIN_MANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Ruinmaniac_PreBattle_2,
		.playerWinText = 	sFrontierText_Ruinmaniac_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Ruinmaniac_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_HIKER,
		.trainerClass = 	CLASS_RUIN_MANIAC,
		.trainerSprite = 	TRAINER_PIC_RUIN_MANIAC,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Ruinmaniac_PreBattle_3,
		.playerWinText = 	sFrontierText_Ruinmaniac_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Ruinmaniac_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_PAINTER,
		.trainerSprite = 	TRAINER_PIC_PAINTER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Painter_PreBattle_1,
		.playerWinText = 	sFrontierText_Painter_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Painter_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_PAINTER,
		.trainerSprite = 	TRAINER_PIC_PAINTER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Painter_PreBattle_2,
		.playerWinText = 	sFrontierText_Painter_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Painter_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LASS,
		.trainerClass = 	CLASS_PAINTER,
		.trainerSprite = 	TRAINER_PIC_PAINTER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Painter_PreBattle_3,
		.playerWinText = 	sFrontierText_Painter_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Painter_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_ExpertM_PreBattle_1,
		.playerWinText = 	sFrontierText_ExpertM_PlayerWin_1,
		.playerLoseText = 	sFrontierText_ExpertM_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_ExpertM_PreBattle_2,
		.playerWinText = 	sFrontierText_ExpertM_PlayerWin_2,
		.playerLoseText = 	sFrontierText_ExpertM_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_MAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_ExpertM_PreBattle_3,
		.playerWinText = 	sFrontierText_ExpertM_PlayerWin_3,
		.playerLoseText = 	sFrontierText_ExpertM_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_WOMAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_ExpertF_PreBattle_1,
		.playerWinText = 	sFrontierText_ExpertF_PlayerWin_1,
		.playerLoseText = 	sFrontierText_ExpertF_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_WOMAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_ExpertF_PreBattle_2,
		.playerWinText = 	sFrontierText_ExpertF_PlayerWin_2,
		.playerLoseText = 	sFrontierText_ExpertF_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_OLD_WOMAN,
		.trainerClass = 	CLASS_EXPERT,
		.trainerSprite = 	TRAINER_PIC_EXPERT_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_ExpertF_PreBattle_3,
		.playerWinText = 	sFrontierText_ExpertF_PlayerWin_3,
		.playerLoseText = 	sFrontierText_ExpertF_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_POKEFAN,
		.trainerSprite = 	TRAINER_PIC_POKEFAN_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_PokefanM_PreBattle_1,
		.playerWinText = 	sFrontierText_PokefanM_PlayerWin_1,
		.playerLoseText = 	sFrontierText_PokefanM_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_POKEFAN,
		.trainerSprite = 	TRAINER_PIC_POKEFAN_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_PokefanM_PreBattle_2,
		.playerWinText = 	sFrontierText_PokefanM_PlayerWin_2,
		.playerLoseText = 	sFrontierText_PokefanM_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MIDDLE_AGED_MAN,
		.trainerClass = 	CLASS_POKEFAN,
		.trainerSprite = 	TRAINER_PIC_POKEFAN_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_PokefanM_PreBattle_3,
		.playerWinText = 	sFrontierText_PokefanM_PlayerWin_3,
		.playerLoseText = 	sFrontierText_PokefanM_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MEDIC_FEMALE,
		.trainerClass = 	CLASS_NURSE,
		.trainerSprite = 	TRAINER_PIC_NURSE,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Nurse_PreBattle_1,
		.playerWinText = 	sFrontierText_Nurse_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Nurse_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MEDIC_FEMALE,
		.trainerClass = 	CLASS_NURSE,
		.trainerSprite = 	TRAINER_PIC_NURSE,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Nurse_PreBattle_2,
		.playerWinText = 	sFrontierText_Nurse_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Nurse_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MEDIC_FEMALE,
		.trainerClass = 	CLASS_NURSE,
		.trainerSprite = 	TRAINER_PIC_NURSE,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Nurse_PreBattle_3,
		.playerWinText = 	sFrontierText_Nurse_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Nurse_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_M,
		.trainerClass = 	CLASS_SWIMMER_M,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_1,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_M,
		.trainerClass = 	CLASS_SWIMMER_M,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_2,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_M,
		.trainerClass = 	CLASS_SWIMMER_M,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_3,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_F,
		.trainerClass = 	CLASS_SWIMMER_F,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_1,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_F,
		.trainerClass = 	CLASS_SWIMMER_F,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_2,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_STANDING_SWIMMER_F,
		.trainerClass = 	CLASS_SWIMMER_F,
		.trainerSprite = 	TRAINER_PIC_SWIMMER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Swimmer_PreBattle_3,
		.playerWinText = 	sFrontierText_Swimmer_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Swimmer_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LITTLE_BOY,
		.trainerClass = 	CLASS_NINJA_BOY,
		.trainerSprite = 	TRAINER_PIC_NINJA_BOY,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_NinjaBoy_PreBattle_1,
		.playerWinText = 	sFrontierText_NinjaBoy_PlayerWin_1,
		.playerLoseText = 	sFrontierText_NinjaBoy_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LITTLE_BOY,
		.trainerClass = 	CLASS_NINJA_BOY,
		.trainerSprite = 	TRAINER_PIC_NINJA_BOY,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_NinjaBoy_PreBattle_2,
		.playerWinText = 	sFrontierText_NinjaBoy_PlayerWin_2,
		.playerLoseText = 	sFrontierText_NinjaBoy_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_LITTLE_BOY,
		.trainerClass = 	CLASS_NINJA_BOY,
		.trainerSprite = 	TRAINER_PIC_NINJA_BOY,
		.gender = 			BATTLE_FACILITY_MALE,
		.preBattleText = 	sFrontierText_NinjaBoy_PreBattle_3,
		.playerWinText = 	sFrontierText_NinjaBoy_PlayerWin_3,
		.playerLoseText = 	sFrontierText_NinjaBoy_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CHANELLER,
		.trainerClass = 	CLASS_CHANNELER,
		.trainerSprite = 	TRAINER_PIC_CHANNELER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Channeler_PreBattle_1,
		.playerWinText = 	sFrontierText_Channeler_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Channeler_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CHANELLER,
		.trainerClass = 	CLASS_CHANNELER,
		.trainerSprite = 	TRAINER_PIC_CHANNELER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Channeler_PreBattle_2,
		.playerWinText = 	sFrontierText_Channeler_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Channeler_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_CHANELLER,
		.trainerClass = 	CLASS_CHANNELER,
		.trainerSprite = 	TRAINER_PIC_CHANNELER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Channeler_PreBattle_3,
		.playerWinText = 	sFrontierText_Channeler_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Channeler_PlayerLose_3,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SKIER,
		.trainerClass = 	CLASS_SKIER,
		.trainerSprite = 	TRAINER_PIC_SKIER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Skier_PreBattle_1,
		.playerWinText = 	sFrontierText_Skier_PlayerWin_1,
		.playerLoseText = 	sFrontierText_Skier_PlayerLose_1,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SKIER,
		.trainerClass = 	CLASS_SKIER,
		.trainerSprite = 	TRAINER_PIC_SKIER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Skier_PreBattle_2,
		.playerWinText = 	sFrontierText_Skier_PlayerWin_2,
		.playerLoseText = 	sFrontierText_Skier_PlayerLose_2,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SKIER,
		.trainerClass = 	CLASS_SKIER,
		.trainerSprite = 	TRAINER_PIC_SKIER,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.preBattleText = 	sFrontierText_Skier_PreBattle_3,
		.playerWinText = 	sFrontierText_Skier_PlayerWin_3,
		.playerLoseText = 	sFrontierText_Skier_PlayerLose_3,
	},
};

const struct SpecialBattleFrontierTrainer gSpecialTowerTrainers[] =
{
	// Used for streak 20 trainers
	{
		.owNum = 			EVENT_OBJ_GFX_MORT,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_MORT,
		.gender = 			BATTLE_FACILITY_MALE,
		.name =				sTrainerName_Mort,
		.preBattleText = 	sFrontierText_Mort_PreBattle,
		.playerWinText = 	sFrontierText_Mort_PlayerWin,
		.playerLoseText = 	sFrontierText_Mort_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Mort,
		.middleCupSpreads = gSpecialTowerSpread_Mort,
		.littleCupSpreads = gSpecialTowerSpread_Mort,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Mort),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Mort),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Mort),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_RIVAL,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_RIVAL,
		.gender = 			BATTLE_FACILITY_MALE,
		.name =				sTrainerName_Rival,
		.preBattleText = 	sFrontierText_Rival_PreBattle,
		.playerWinText = 	sFrontierText_Rival_PlayerWin,
		.playerLoseText = 	sFrontierText_Rival_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Rival,
		.middleCupSpreads = gSpecialTowerSpread_Rival,
		.littleCupSpreads = gSpecialTowerSpread_Rival,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Rival),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Rival),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Rival),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_SELENE,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_CHAMPION_SELENE,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.name =				sTrainerName_Selene,
		.preBattleText = 	sFrontierText_Selene_PreBattle,
		.playerWinText = 	sFrontierText_Selene_PlayerWin,
		.playerLoseText = 	sFrontierText_Selene_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Selene,
		.middleCupSpreads = gSpecialTowerSpread_Selene,
		.littleCupSpreads = gSpecialTowerSpread_Selene,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Selene),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Selene),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Selene),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_ALISTAIR,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_ALISTAIR,
		.gender = 			BATTLE_FACILITY_MALE,
		.name =				sTrainerName_Alistair,
		.preBattleText = 	sFrontierText_Alistair_PreBattle,
		.playerWinText = 	sFrontierText_Alistair_PlayerWin,
		.playerLoseText = 	sFrontierText_Alistair_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Alistair,
		.middleCupSpreads = gSpecialTowerSpread_Alistair,
		.littleCupSpreads = gSpecialTowerSpread_Alistair,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Alistair),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Alistair),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Alistair),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_M,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_RS_COOLTRAINER_M,
		.gender = 			BATTLE_FACILITY_MALE,
		.name =				sTrainerName_Collin,
		.preBattleText = 	sFrontierText_Collin_PreBattle,
		.playerWinText = 	sFrontierText_Collin_PlayerWin,
		.playerLoseText = 	sFrontierText_Collin_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Collin,
		.middleCupSpreads = gSpecialTowerSpread_Collin,
		.littleCupSpreads = gSpecialTowerSpread_Collin,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Collin),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Collin),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Collin),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_COOLTRAINER_F,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_RS_COOLTRAINER_F,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.name =				sTrainerName_Crystal,
		.preBattleText = 	sFrontierText_Crystal_PreBattle,
		.playerWinText = 	sFrontierText_Crystal_PlayerWin,
		.playerLoseText = 	sFrontierText_Crystal_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Crystal,
		.middleCupSpreads = gSpecialTowerSpread_Crystal,
		.littleCupSpreads = gSpecialTowerSpread_Crystal,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Crystal),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Crystal),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Crystal),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_BRENDAN,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_BRENDAN,
		.gender = 			BATTLE_FACILITY_MALE,
		.name =				sTrainerName_Brendan,
		.preBattleText = 	sFrontierText_Brendan_PreBattle,
		.playerWinText = 	sFrontierText_Brendan_PlayerWin,
		.playerLoseText = 	sFrontierText_Brendan_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_Brendan,
		.middleCupSpreads = gSpecialTowerSpread_Brendan,
		.littleCupSpreads = gSpecialTowerSpread_Brendan,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Brendan),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Brendan),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Brendan),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
	{
		.owNum = 			EVENT_OBJ_GFX_MAY,
		.trainerClass = 	CLASS_BATTLE_FRONTIER_ACE,
		.trainerSprite = 	TRAINER_PIC_MAY,
		.gender = 			BATTLE_FACILITY_FEMALE,
		.name =				sTrainerName_May,
		.preBattleText = 	sFrontierText_May_PreBattle,
		.playerWinText = 	sFrontierText_May_PlayerWin,
		.playerLoseText = 	sFrontierText_May_PlayerLose,
		.regularSpreads =	gSpecialTowerSpread_May,
		.middleCupSpreads = gSpecialTowerSpread_May,
		.littleCupSpreads = gSpecialTowerSpread_May,
		.legendarySpreads = gLegendaryTowerSpread,
		.regSpreadSize = 	NELEMS(gSpecialTowerSpread_May),
		.mcSpreadSize =		NELEMS(gSpecialTowerSpread_May),
		.lcSpreadSize =		NELEMS(gSpecialTowerSpread_May),
		.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
		.songId = 			BGM_BATTLE_FRONTIER_BOSS,
		.isMonotype = 		FALSE,
	},
};

const struct SpecialBattleFrontierTrainer gFrontierBrains[] =
{
	[0] =
		{
			.owNum = 			EVENT_OBJ_GFX_TERRENCE,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_TERRENCE,
			.gender = 			BATTLE_FACILITY_MALE,
			.name =				sTrainerName_Terrence,
			.preBattleText = 	sFrontierText_Terrence_PreBattle,
			.playerWinText = 	sFrontierText_Terrence_PlayerWin,
			.playerLoseText = 	sFrontierText_Terrence_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Terrence,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Terrence,
			.littleCupSpreads = gSpecialTowerSpread_Terrence,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Terrence),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Terrence),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Terrence),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[1] =
		{
			.owNum = 			EVENT_OBJ_GFX_STELLA,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_STELLA,
			.gender = 			BATTLE_FACILITY_FEMALE,
			.name =				sTrainerName_Stella,
			.preBattleText = 	sFrontierText_Stella_PreBattle,
			.playerWinText = 	sFrontierText_Stella_PlayerWin,
			.playerLoseText = 	sFrontierText_Stella_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Stella,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Stella,
			.littleCupSpreads = gSpecialTowerSpread_Stella,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Stella),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Stella),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Stella),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[2] =
		{
			.owNum = 			EVENT_OBJ_GFX_RAINE,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_RAINE,
			.gender = 			BATTLE_FACILITY_FEMALE,
			.name =				sTrainerName_Raine,
			.preBattleText = 	sFrontierText_Raine_PreBattle,
			.playerWinText = 	sFrontierText_Raine_PlayerWin,
			.playerLoseText = 	sFrontierText_Raine_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Raine,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Raine,
			.littleCupSpreads = gSpecialTowerSpread_Raine,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Raine),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Raine),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Raine),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[3] =
		{
			.owNum = 			EVENT_OBJ_GFX_CHANCE,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_CHANCE,
			.gender = 			BATTLE_FACILITY_MALE,
			.name =				sTrainerName_Chance,
			.preBattleText = 	sFrontierText_Chance_PreBattle,
			.playerWinText = 	sFrontierText_Chance_PlayerWin,
			.playerLoseText = 	sFrontierText_Chance_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Chance,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Chance,
			.littleCupSpreads = gSpecialTowerSpread_Chance,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Chance),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Chance),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Chance),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[4] = //Swapped to the female graphics at runtime if the player is male - see UseFemaleCaseyFrontierBrain
		{
			.owNum = 			EVENT_OBJ_GFX_CASEY_M,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_CASEY_M,
			.gender = 			BATTLE_FACILITY_MALE,
			.name =				sTrainerName_Casey,
			.preBattleText = 	sFrontierText_Casey_PreBattle,
			.playerWinText = 	sFrontierText_Casey_PlayerWin,
			.playerLoseText = 	sFrontierText_Casey_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Casey,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Casey,
			.littleCupSpreads = gSpecialTowerSpread_Casey,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Casey),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Casey),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Casey),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[5] =
		{
			.owNum = 			EVENT_OBJ_GFX_ABBY,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_ABBY,
			.gender = 			BATTLE_FACILITY_FEMALE,
			.name =				sTrainerName_Abby,
			.preBattleText = 	sFrontierText_Abby_PreBattle,
			.playerWinText = 	sFrontierText_Abby_PlayerWin,
			.playerLoseText = 	sFrontierText_Abby_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Abby,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Abby,
			.littleCupSpreads = gSpecialTowerSpread_Abby,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Abby),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Abby),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Abby),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[6] =
		{
			.owNum = 			EVENT_OBJ_GFX_IRIS,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_IRIS,
			.gender = 			BATTLE_FACILITY_FEMALE,
			.name =				sTrainerName_Iris,
			.preBattleText = 	sFrontierText_Iris_PreBattle,
			.playerWinText = 	sFrontierText_Iris_PlayerWin,
			.playerLoseText = 	sFrontierText_Iris_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Iris,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Iris,
			.littleCupSpreads = gSpecialTowerSpread_Iris,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Iris),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Iris),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Iris),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		},
	[7] =
		{
			.owNum = 			EVENT_OBJ_GFX_DENNIS,
			.trainerClass = 	CLASS_BATTLE_FRONTIER_BRAIN,
			.trainerSprite = 	TRAINER_PIC_LEADER_DENNIS,
			.gender = 			BATTLE_FACILITY_MALE,
			.name =				sTrainerName_Dennis,
			.preBattleText = 	sFrontierText_Dennis_PreBattle,
			.playerWinText = 	sFrontierText_Dennis_PlayerWin,
			.playerLoseText = 	sFrontierText_Dennis_PlayerLose,
			.regularSpreads =	gSpecialTowerSpread_Dennis,
			.legendarySpreads = gLegendaryTowerSpread,
			.middleCupSpreads = gSpecialTowerSpread_Dennis,
			.littleCupSpreads = gSpecialTowerSpread_Dennis,
			.regSpreadSize = 	NELEMS(gSpecialTowerSpread_Dennis),
			.legSpreadSize =	NELEMS(gLegendaryTowerSpread),
			.mcSpreadSize =		NELEMS(gSpecialTowerSpread_Dennis),
			.lcSpreadSize =		NELEMS(gSpecialTowerSpread_Dennis),
			.songId = 			BGM_BATTLE_FRONTIER_BOSS,
			.isMonotype = 		FALSE,
		}
};

// Not supported in Amethyst. An example multi trainer is kept here in case that changes someday.
const struct MultiBattleTowerTrainer gFrontierMultiBattleTrainers[] =
{
	// {
	// 	.owNum = EVENT_OBJ_GFX_POKE_KID,
	// 	.trainerClass = CLASS_POKE_KID,
	// 	.backSpriteId = TRAINER_BACK_PIC_POKE_KID,
	// 	.gender = MALE,
	// 	.name = sTrainerName_Milo,
	// 	.otId = 0x3E16ECA,
	// 	.regularSpreads = gMultiTowerSpread_Milo,
	// 	.legendarySpreads = gMultiLegendaryTowerSpread_Milo,
	// 	.littleCupSpreads = gMultiLittleCupTowerSpread_Milo,
	// 	.regSpreadSize = NELEMS(gMultiTowerSpread_Milo),
	// 	.legSpreadSize = NELEMS(gMultiLegendaryTowerSpread_Milo),
	// 	.lcSpreadSize = NELEMS(gMultiLittleCupTowerSpread_Milo),
	// },
};

const u8 gNumFrontierMultiTrainers = NELEMS(gFrontierMultiBattleTrainers);

const u16 gNumTowerTrainers = NELEMS(gTowerTrainers);
const u16 gNumSpecialTowerTrainers = NELEMS(gSpecialTowerTrainers);
const u16 gNumFrontierBrains = NELEMS(gFrontierBrains);
